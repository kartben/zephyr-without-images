/* k_pipe_buffer.c */

/*
 * Copyright (c) 1997-2015 Wind River Systems, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1) Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3) Neither the name of Wind River Systems nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


/* Implementation remarks:
- when using a floating end pointer: do not use pipe_desc->iBuffsize for
  (pipe_desc->end_ptr - pipe_desc->begin_ptr)
 */

#include <microkernel/base_api.h>
#include <k_pipe_buffer.h>
#include <string.h>
#include <toolchain.h>
#include <sections.h>
#include <misc/__assert.h>

#define STORE_NBR_MARKERS
/* NOTE: the number of pending write and read Xfers is always stored,
   as it is required for the pipes to function properly. It is stored in the
   pipe descriptor fields iNbrPendingWrites and iNbrPendingReads.

   In the Writer and Reader MarkersList, the number of markers (==nbr. of
   unreleased Xfers)
   is monitored as well. They actually equal iNbrPendingWrites and
   iNbrPendingReads.
   Their existence depends on STORE_NBR_MARKERS. A reason to have them
   additionally is that
   some extra consistency checking is performed in the markers manipulation
   functionality
   itself.
   Drawback: double storage of nbr. of pending write Xfers (but for test
   purposes this is
   acceptable I think)
 */

#define CHECK_BUFFER_POINTER(pData) \
	__ASSERT_NO_MSG(desc->begin_ptr <= pData && pData < desc->end_ptr)

static void pipe_intrusion_check(struct _k_pipe_desc *desc, unsigned char *begin_ptr, int iSize);

/**
 * Markers
 */

static int MarkerFindFree(struct _k_pipe_marker markers[])
{
	struct _k_pipe_marker *pM = markers;
	int i;

	for (i = 0; i < MAXNBR_PIPE_MARKERS; i++, pM++) {
		if (NULL == pM->pointer) {
			break;
		}
	}
	if (MAXNBR_PIPE_MARKERS == i) {
		i = -1;
	}

	return i;
}

static void MarkerLinkToListAfter(struct _k_pipe_marker markers[],
								  int iMarker, int iNewMarker)
{
	int iNextMarker; /* index of next marker in original list */

	/* let the original list be aware of the new marker */
	if (-1 != iMarker) {
		iNextMarker = markers[iMarker].next;
		markers[iMarker].next = iNewMarker;
		if (-1 != iNextMarker) {
			markers[iNextMarker].prev = iNewMarker;
		} else {
			/* there was no next marker */
		}
	} else {
		iNextMarker = -1; /* there wasn't even a marker */
	}

	/* link the new marker with the marker and next marker */
	markers[iNewMarker].prev = iMarker;
	markers[iNewMarker].next = iNextMarker;
}

static int MarkerAddLast(struct _k_pipe_marker_list *pMarkerList,
						 unsigned char *pointer, int iSize, bool buffer_xfer_busy)
{
	int i = MarkerFindFree(pMarkerList->markers);

	if (i == -1) {
		return i;
	}

	pMarkerList->markers[i].pointer = pointer;
	pMarkerList->markers[i].size = iSize;
	pMarkerList->markers[i].buffer_xfer_busy = buffer_xfer_busy;

	if (-1 == pMarkerList->first_marker) {
		__ASSERT_NO_MSG(-1 == pMarkerList->last_marker);
		pMarkerList->first_marker = i; /* we still need to set prev & next */
	} else {
		__ASSERT_NO_MSG(-1 != pMarkerList->last_marker);
		__ASSERT_NO_MSG(-1 ==
		       pMarkerList->markers[pMarkerList->last_marker].next);
	}

	MarkerLinkToListAfter(pMarkerList->markers, pMarkerList->last_marker, i);

	__ASSERT_NO_MSG(-1 == pMarkerList->markers[i].next);
	pMarkerList->last_marker = i;

#ifdef STORE_NBR_MARKERS
	pMarkerList->num_markers++;
	__ASSERT_NO_MSG(0 < pMarkerList->num_markers);
#endif

	return i;
}

static void MarkerUnlinkFromList(struct _k_pipe_marker markers[], int iMarker,
								 int *piPredecessor, int *piSuccessor)
{
	int iNextMarker = markers[iMarker].next;
	int iPrevMarker = markers[iMarker].prev;

	/* remove the marker from the list */
	markers[iMarker].next = -1;
	markers[iMarker].prev = -1;

	/* repair the chain */
	if (-1 != iPrevMarker) {
		markers[iPrevMarker].next = iNextMarker;
	}
	if (-1 != iNextMarker) {
		markers[iNextMarker].prev = iPrevMarker;
	}
	*piPredecessor = iPrevMarker;
	*piSuccessor = iNextMarker;
}

static void MarkerDelete(struct _k_pipe_marker_list *pMarkerList, int index)
{
	int i;
	int iPredecessor;
	int iSuccessor;

	i = index;

	__ASSERT_NO_MSG(-1 != i);

	pMarkerList->markers[i].pointer = NULL;
	MarkerUnlinkFromList(pMarkerList->markers, i, &iPredecessor, &iSuccessor);

	/* update first/last info */
	if (i == pMarkerList->last_marker) {
		pMarkerList->last_marker = iPredecessor;
	}
	if (i == pMarkerList->first_marker) {
		pMarkerList->first_marker = iSuccessor;
	}

#ifdef STORE_NBR_MARKERS
	pMarkerList->num_markers--;
	__ASSERT_NO_MSG(0 <= pMarkerList->num_markers);

	if (0 == pMarkerList->num_markers) {
		__ASSERT_NO_MSG(-1 == pMarkerList->first_marker);
		__ASSERT_NO_MSG(-1 == pMarkerList->last_marker);
	}
#endif
}

static void MarkersClear(struct _k_pipe_marker_list *pMarkerList)
{
	struct _k_pipe_marker *pM = pMarkerList->markers;
	int i;

	for (i = 0; i < MAXNBR_PIPE_MARKERS; i++, pM++) {
		memset(pM, 0, sizeof(struct _k_pipe_marker));
		pM->next = -1;
		pM->prev = -1;
	}
#ifdef STORE_NBR_MARKERS
	pMarkerList->num_markers = 0;
#endif
	pMarkerList->first_marker = -1;
	pMarkerList->last_marker = -1;
	pMarkerList->post_wrap_around_marker = -1;
}

/**/

/* note on setting/clearing markers/guards:

  If there is at least one marker, there is a guard and equals one of the
  markers; if there are no markers (*), there is no guard.
  Consequently, if a marker is add when there were none, the guard will equal
  it. If additional markers are add, the guard will not change.
  However, if a marker is deleted:
    if it equals the guard a new guard must be selected (**)
    if not, guard doesn't change

  (*) we need to housekeep how much markers there are or we can inspect the
  guard
  (**) for this, the complete markers table needs to be investigated
 */

/**/

/* This function will see if one or more 'areas' in the buffer
   can be made available (either for writing xor reading).
   Note: such a series of areas starts from the beginning.
 */
static int ScanMarkers(struct _k_pipe_marker_list *pMarkerList,
					   int *piSizeBWA, int *piSizeAWA, int *piNbrPendingXfers)
{
	struct _k_pipe_marker *pM;
	bool bMarkersAreNowAWA;
	int index;

	index = pMarkerList->first_marker;

	__ASSERT_NO_MSG(-1 != index);

	bMarkersAreNowAWA = false;
	do {
		int index_next;

		__ASSERT_NO_MSG(index == pMarkerList->first_marker);

		if (index == pMarkerList->post_wrap_around_marker) {
			bMarkersAreNowAWA = true; /* from now on, everything is AWA */
		}

		pM = &(pMarkerList->markers[index]);

		if (pM->buffer_xfer_busy == true) {
			break;
		}

		if (!bMarkersAreNowAWA) {
			*piSizeBWA += pM->size;
		} else {
			*piSizeAWA += pM->size;
		}

		index_next = pM->next;
		/* pMarkerList->first_marker will be updated */
		MarkerDelete(pMarkerList, index);
		/* adjust *piNbrPendingXfers */
		if (piNbrPendingXfers) {
			__ASSERT_NO_MSG(0 <= *piNbrPendingXfers);
			(*piNbrPendingXfers)--;
		}
		index = index_next;
	} while (-1 != index);

	__ASSERT_NO_MSG(index == pMarkerList->first_marker);

	if (bMarkersAreNowAWA) {
		pMarkerList->post_wrap_around_marker = pMarkerList->first_marker;
	}

#ifdef STORE_NBR_MARKERS
	if (0 == pMarkerList->num_markers) {
		__ASSERT_NO_MSG(-1 == pMarkerList->first_marker);
		__ASSERT_NO_MSG(-1 == pMarkerList->last_marker);
		__ASSERT_NO_MSG(-1 == pMarkerList->post_wrap_around_marker);
	}
#endif

	return pMarkerList->first_marker;
}

/**
 * General
 */

void BuffInit(unsigned char *pBuffer, int *piBuffSize, struct _k_pipe_desc *desc)
{
	desc->begin_ptr = pBuffer;

	desc->buffer_size = *piBuffSize;

	/* reset all pointers */

	desc->end_ptr = desc->begin_ptr + OCTET_TO_SIZEOFUNIT(desc->buffer_size);
	desc->original_end_ptr = desc->end_ptr;

	/* assumed it is allowed */
	desc->BuffState = BUFF_EMPTY;
	desc->end_ptr = desc->original_end_ptr;
	desc->write_ptr = desc->begin_ptr;
	desc->write_guard = NULL;
	desc->bWriteWA = false;
	desc->read_ptr = desc->begin_ptr;
	desc->read_guard = NULL;
	desc->bReadWA = true; /* YES!! */
	desc->free_space_count = desc->buffer_size;
	desc->free_space_post_wrap_around = 0;
	desc->iNbrPendingReads = 0;
	desc->iAvailDataCont = 0;
	desc->iAvailDataAWA = 0;
	desc->iNbrPendingWrites = 0;
	MarkersClear(&desc->WriteMarkers);
	MarkersClear(&desc->ReadMarkers);

}

int CalcFreeSpace(struct _k_pipe_desc *desc, int *free_space_count_ptr,
				  int *free_space_post_wrap_around_ptr)
{
	unsigned char *pStart = desc->write_ptr;
	unsigned char *pStop = desc->read_ptr;

	if (NULL != desc->write_guard) {
		pStop = desc->write_guard;
	} else {
		/*
		 * if BuffState==BUFF_EMPTY but we have a WriteGuard,
		 * we still need to calculate it as a normal [Start,Stop] interval
		 */

		if (BUFF_EMPTY == desc->BuffState) {
			*free_space_count_ptr = SIZEOFUNIT_TO_OCTET(desc->end_ptr - pStart);
			*free_space_post_wrap_around_ptr = SIZEOFUNIT_TO_OCTET(pStop - desc->begin_ptr);
			return (*free_space_count_ptr + *free_space_post_wrap_around_ptr);
			/* this sum equals end_ptr-begin_ptr */
		}
	}

	/*
	 * on the other hand, if BuffState is full, we do not need a special flow;
	 * it will be correct as (pStop - pStart) equals 0
	 */

	if (pStop >= pStart) {
		*free_space_count_ptr = SIZEOFUNIT_TO_OCTET(pStop - pStart);
		*free_space_post_wrap_around_ptr = 0;
	} else {
		*free_space_count_ptr = SIZEOFUNIT_TO_OCTET(desc->end_ptr - pStart);
		*free_space_post_wrap_around_ptr = SIZEOFUNIT_TO_OCTET(pStop - desc->begin_ptr);
	}
	return (*free_space_count_ptr + *free_space_post_wrap_around_ptr);
}

void BuffGetFreeSpace(struct _k_pipe_desc *desc, int *piFreeSpaceTotal,
					  int *free_space_count_ptr, int *free_space_post_wrap_around_ptr)
{
	int free_space_count;
	int free_space_post_wrap_around;
	int iFreeSpaceTotal;

	iFreeSpaceTotal =
		CalcFreeSpace(desc, &free_space_count, &free_space_post_wrap_around);
	__ASSERT_NO_MSG(free_space_count == desc->free_space_count);
	__ASSERT_NO_MSG(free_space_post_wrap_around == desc->free_space_post_wrap_around);
	*piFreeSpaceTotal = iFreeSpaceTotal;
	*free_space_count_ptr = desc->free_space_count;
	*free_space_post_wrap_around_ptr = desc->free_space_post_wrap_around;
}

void BuffGetFreeSpaceTotal(struct _k_pipe_desc *desc, int *piFreeSpaceTotal)
{
	int dummy1, dummy2;
	*piFreeSpaceTotal = CalcFreeSpace(desc, &dummy1, &dummy2);
	__ASSERT_NO_MSG(dummy1 == desc->free_space_count);
	__ASSERT_NO_MSG(dummy2 == desc->free_space_post_wrap_around);
}

int BuffEmpty(struct _k_pipe_desc *desc)
{
	/* 0==iAvailDataTotal is an INcorrect condition b/c of async behavior */

	int iTotalFreeSpace;

	BuffGetFreeSpaceTotal(desc, &iTotalFreeSpace);
	return (desc->buffer_size == iTotalFreeSpace);
}

int CalcAvailData(struct _k_pipe_desc *desc, int *piAvailDataCont,
				  int *piAvailDataAWA)
{
	unsigned char *pStart = desc->read_ptr;
	unsigned char *pStop = desc->write_ptr;

	if (NULL != desc->read_guard) {
		pStop = desc->read_guard;
	} else {
		/*
		 * if BuffState==BUFF_FULL but we have a ReadGuard,
		 * we still need to calculate it as a normal [Start,Stop] interval
		 */

		if (BUFF_FULL == desc->BuffState) {
			*piAvailDataCont = SIZEOFUNIT_TO_OCTET(desc->end_ptr - pStart);
			*piAvailDataAWA = SIZEOFUNIT_TO_OCTET(pStop - desc->begin_ptr);
			return (*piAvailDataCont + *piAvailDataAWA);
			/* this sum equals end_ptr-begin_ptr */
		}
	}

	/*
	 * on the other hand, if BuffState is empty, we do not need a special flow;
	 * it will be correct as (pStop - pStart) equals 0
	 */

	if (pStop >= pStart) {
		*piAvailDataCont = SIZEOFUNIT_TO_OCTET(pStop - pStart);
		*piAvailDataAWA = 0;
	} else {
		*piAvailDataCont = SIZEOFUNIT_TO_OCTET(desc->end_ptr - pStart);
		*piAvailDataAWA = SIZEOFUNIT_TO_OCTET(pStop - desc->begin_ptr);
	}
	return (*piAvailDataCont + *piAvailDataAWA);
}

void BuffGetAvailData(struct _k_pipe_desc *desc, int *piAvailDataTotal,
					  int *piAvailDataCont, int *piAvailDataAWA)
{
	int iAvailDataCont;
	int iAvailDataAWA;
	int iAvailDataTotal;

	iAvailDataTotal =
		CalcAvailData(desc, &iAvailDataCont, &iAvailDataAWA);
	__ASSERT_NO_MSG(iAvailDataCont == desc->iAvailDataCont);
	__ASSERT_NO_MSG(iAvailDataAWA == desc->iAvailDataAWA);
	*piAvailDataTotal = iAvailDataTotal;
	*piAvailDataCont = desc->iAvailDataCont;
	*piAvailDataAWA = desc->iAvailDataAWA;
}

void BuffGetAvailDataTotal(struct _k_pipe_desc *desc, int *piAvailDataTotal)
{
	int dummy1, dummy2;

	*piAvailDataTotal = CalcAvailData(desc, &dummy1, &dummy2);
	__ASSERT_NO_MSG(dummy1 == desc->iAvailDataCont);
	__ASSERT_NO_MSG(dummy2 == desc->iAvailDataAWA);
}

int BuffFull(struct _k_pipe_desc *desc)
{
	/* 0==iTotalFreeSpace is an INcorrect condition b/c of async behavior */

	int iAvailDataTotal;

	BuffGetAvailDataTotal(desc, &iAvailDataTotal);
	return (desc->buffer_size == iAvailDataTotal);
}

/**
 * Buffer en-queuing:
 */

static int AsyncEnQRegstr(struct _k_pipe_desc *desc, int iSize)
{
	int i;

	pipe_intrusion_check(desc, desc->write_ptr, iSize);

	i = MarkerAddLast(&desc->WriteMarkers, desc->write_ptr, iSize, true);
	if (i != -1) {
		/* adjust iNbrPendingWrites */
		__ASSERT_NO_MSG(0 <= desc->iNbrPendingWrites);
		desc->iNbrPendingWrites++;
		/* read_guard changes? */
		if (NULL == desc->read_guard) {
			desc->read_guard = desc->write_ptr;
		}
		__ASSERT_NO_MSG(desc->WriteMarkers.markers
						[desc->WriteMarkers.first_marker].pointer ==
						desc->read_guard);
		/* post_wrap_around_marker changes? */
		if (-1 == desc->WriteMarkers.post_wrap_around_marker && desc->bWriteWA) {
			desc->WriteMarkers.post_wrap_around_marker = i;
		}
	}
	return i;
}

static void AsyncEnQFinished(struct _k_pipe_desc *desc, int iTransferID)
{
	desc->WriteMarkers.markers[iTransferID].buffer_xfer_busy = false;

	if (desc->WriteMarkers.first_marker == iTransferID) {
		int iNewFirstMarker = ScanMarkers(&desc->WriteMarkers,
										  &desc->iAvailDataCont,
										  &desc->iAvailDataAWA,
										  &desc->iNbrPendingWrites);
		if (-1 != iNewFirstMarker) {
			desc->read_guard =
				desc->WriteMarkers.markers[iNewFirstMarker].pointer;
		} else {
			desc->read_guard = NULL;
		}
	}
}

int BuffEnQ(struct _k_pipe_desc *desc, int iSize, unsigned char **ppWrite)
{
	int iTransferID;

	if (0 == BuffEnQA(desc, iSize, ppWrite, &iTransferID)) {
		return 0;
	}

	/* check ret value */

	BuffEnQA_End(desc, iTransferID, iSize /* optional */);
	return iSize;
}

int BuffEnQA(struct _k_pipe_desc *desc, int iSize, unsigned char **ppWrite,
			 int *piTransferID)
{
	if (iSize > desc->free_space_count) {
		return 0;
	}
	*piTransferID = AsyncEnQRegstr(desc, iSize);
	if (-1 == *piTransferID) {
		return 0;
	}

	*ppWrite = desc->write_ptr;

	/* adjust write pointer and free space*/

	desc->write_ptr += OCTET_TO_SIZEOFUNIT(iSize);
	if (desc->end_ptr == desc->write_ptr) {
		desc->write_ptr = desc->begin_ptr;
		desc->free_space_count = desc->free_space_post_wrap_around;
		desc->free_space_post_wrap_around = 0;
		desc->bWriteWA = true;
		desc->bReadWA = false;
		desc->ReadMarkers.post_wrap_around_marker = -1;
	} else {
		desc->free_space_count -= iSize;
	}

	if (desc->write_ptr == desc->read_ptr) {
		desc->BuffState = BUFF_FULL;
	} else {
		desc->BuffState = BUFF_OTHER;
	}

	CHECK_BUFFER_POINTER(desc->write_ptr);

	return iSize;
}

void BuffEnQA_End(struct _k_pipe_desc *desc, int iTransferID,
				  int iSize /* optional */)
{
	ARG_UNUSED(iSize);

	/* An asynchronous data transfer to the buffer has finished */

	AsyncEnQFinished(desc, iTransferID);
}

/**
 * Buffer de-queuing:
 */

static int AsyncDeQRegstr(struct _k_pipe_desc *desc, int iSize)
{
	int i;

	pipe_intrusion_check(desc, desc->read_ptr, iSize);

	i = MarkerAddLast(&desc->ReadMarkers, desc->read_ptr, iSize, true);
	if (i != -1) {
		/* adjust iNbrPendingReads */
		__ASSERT_NO_MSG(0 <= desc->iNbrPendingReads);
		desc->iNbrPendingReads++;
		/* write_guard changes? */
		if (NULL == desc->write_guard) {
			desc->write_guard = desc->read_ptr;
		}
		__ASSERT_NO_MSG(desc->ReadMarkers.markers
						[desc->ReadMarkers.first_marker].pointer ==
						desc->write_guard);
		/* post_wrap_around_marker changes? */
		if (-1 == desc->ReadMarkers.post_wrap_around_marker && desc->bReadWA) {
			desc->ReadMarkers.post_wrap_around_marker = i;
		}
	}
	return i;
}

static void AsyncDeQFinished(struct _k_pipe_desc *desc, int iTransferID)
{
	desc->ReadMarkers.markers[iTransferID].buffer_xfer_busy = false;

	if (desc->ReadMarkers.first_marker == iTransferID) {
		int iNewFirstMarker = ScanMarkers(&desc->ReadMarkers,
										  &desc->free_space_count,
										  &desc->free_space_post_wrap_around,
										  &desc->iNbrPendingReads);
		if (-1 != iNewFirstMarker) {
			desc->write_guard =
				desc->ReadMarkers.markers[iNewFirstMarker].pointer;
		} else {
			desc->write_guard = NULL;
		}
	}
}

int BuffDeQ(struct _k_pipe_desc *desc, int iSize, unsigned char **ppRead)
{
	int iTransferID;

	if (0 == BuffDeQA(desc, iSize, ppRead, &iTransferID)) {
		return 0;
	}
	BuffDeQA_End(desc, iTransferID, iSize /* optional */);
	return iSize;
}

int BuffDeQA(struct _k_pipe_desc *desc, int iSize, unsigned char **ppRead,
			 int *piTransferID)
{
	/* asynchronous data transfer; read guard pointers must be set */

	if (iSize > desc->iAvailDataCont) {
		/* free space is from read to guard pointer/end pointer */
		return 0;
	}
	*piTransferID = AsyncDeQRegstr(desc, iSize);
	if (-1 == *piTransferID) {
		return 0;
	}

	*ppRead = desc->read_ptr;

	/* adjust read pointer and avail data */

	desc->read_ptr += OCTET_TO_SIZEOFUNIT(iSize);
	if (desc->end_ptr == desc->read_ptr) {
		desc->read_ptr = desc->begin_ptr;
		desc->iAvailDataCont = desc->iAvailDataAWA;
		desc->iAvailDataAWA = 0;
		desc->bWriteWA = false;
		desc->bReadWA = true;
		desc->WriteMarkers.post_wrap_around_marker = -1;
	} else {
		desc->iAvailDataCont -= iSize;
	}

	if (desc->write_ptr == desc->read_ptr) {
		desc->BuffState = BUFF_EMPTY;
	} else {
		desc->BuffState = BUFF_OTHER;
	}

	CHECK_BUFFER_POINTER(desc->read_ptr);

	return iSize;
}

void BuffDeQA_End(struct _k_pipe_desc *desc, int iTransferID,
				  int iSize /* optional */)
{
	ARG_UNUSED(iSize);

	/* An asynchronous data transfer from the buffer has finished */

	AsyncDeQFinished(desc, iTransferID);
}

/**
 * Buffer instrusion
 */

static bool AreasCheck4Intrusion(unsigned char *pBegin1, int iSize1,
								 unsigned char *pBegin2, int iSize2)
{
	unsigned char *pEnd1;
	unsigned char *pEnd2;

	pEnd1 = pBegin1 + OCTET_TO_SIZEOFUNIT(iSize1);
	pEnd2 = pBegin2 + OCTET_TO_SIZEOFUNIT(iSize2);

	/*
	 * 2 tests are required to determine the status of the 2 areas,
	 * in terms of their position wrt each other
	 */

	if (pBegin2 >= pBegin1) {
		/* check intrusion of pBegin2 in [pBegin1, pEnd1( */
		if (pBegin2 < pEnd1) {
			/* intrusion!! */
			return true;
		} else {
			/* pBegin2 lies outside and to the right of the first area,
			  intrusion is impossible */
			return false;
		}
	} else {
		/* pBegin2 lies to the left of (pBegin1, pEnd1) */
		/* check end pointer: is pEnd2 in (pBegin1, pEnd1( ?? */
		if (pEnd2 > pBegin1) {
			/* intrusion!! */
			return true;
		} else {
			/* pEnd2 lies outside and to the left of the first area,
			   intrusion is impossible */
			return false;
		}
	}
}

static void pipe_intrusion_check(struct _k_pipe_desc *desc, unsigned char *begin_ptr, int iSize)
{
	/*
	 * check possible collision with all existing data areas,
	 * both for read and write areas
	 */

	int index;
	struct _k_pipe_marker_list *pMarkerList;

	/* write markers */

#ifdef STORE_NBR_MARKERS
	/* first a small consistency check */

	if (0 == desc->WriteMarkers.num_markers) {
		__ASSERT_NO_MSG(-1 == desc->WriteMarkers.first_marker);
		__ASSERT_NO_MSG(-1 == desc->WriteMarkers.last_marker);
		__ASSERT_NO_MSG(-1 == desc->WriteMarkers.post_wrap_around_marker);
	}
#endif

	pMarkerList = &desc->WriteMarkers;
	index = pMarkerList->first_marker;

	while (-1 != index) {
		struct _k_pipe_marker *pM;

		pM = &(pMarkerList->markers[index]);

		if (0 != AreasCheck4Intrusion(begin_ptr, iSize, pM->pointer, pM->size)) {
			__ASSERT_NO_MSG(1 == 0);
		}
		index = pM->next;
	}

	/* read markers */

#ifdef STORE_NBR_MARKERS
	/* first a small consistency check */

	if (0 == desc->ReadMarkers.num_markers) {
		__ASSERT_NO_MSG(-1 == desc->ReadMarkers.first_marker);
		__ASSERT_NO_MSG(-1 == desc->ReadMarkers.last_marker);
		__ASSERT_NO_MSG(-1 == desc->ReadMarkers.post_wrap_around_marker);
	}
#endif

	pMarkerList = &desc->ReadMarkers;
	index = pMarkerList->first_marker;

	while (-1 != index) {
		struct _k_pipe_marker *pM;

		pM = &(pMarkerList->markers[index]);

		if (0 != AreasCheck4Intrusion(begin_ptr, iSize, pM->pointer, pM->size)) {
			__ASSERT_NO_MSG(1 == 0);
		}
		index = pM->next;
	}
}
