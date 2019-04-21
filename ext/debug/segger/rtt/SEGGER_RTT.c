/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*            (c) 1995 - 2019 SEGGER Microcontroller GmbH             *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
*       SEGGER SystemView * Real-time application analysis           *
*                                                                    *
**********************************************************************
*                                                                    *
* All rights reserved.                                               *
*                                                                    *
* SEGGER strongly recommends to not make any changes                 *
* to or modify the source code of this software in order to stay     *
* compatible with the RTT protocol and J-Link.                       *
*                                                                    *
* Redistribution and use in source and binary forms, with or         *
* without modification, are permitted provided that the following    *
* conditions are met:                                                *
*                                                                    *
* o Redistributions of source code must retain the above copyright   *
*   notice, this list of conditions and the following disclaimer.    *
*                                                                    *
* o Redistributions in binary form must reproduce the above          *
*   copyright notice, this list of conditions and the following      *
*   disclaimer in the documentation and/or other materials provided  *
*   with the distribution.                                           *
*                                                                    *
* o Neither the name of SEGGER Microcontroller GmbH         *
*   nor the names of its contributors may be used to endorse or      *
*   promote products derived from this software without specific     *
*   prior written permission.                                        *
*                                                                    *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND             *
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,        *
* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF           *
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE           *
* DISCLAIMED. IN NO EVENT SHALL SEGGER Microcontroller BE LIABLE FOR *
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR           *
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT  *
* OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;    *
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF      *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT          *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE  *
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH   *
* DAMAGE.                                                            *
*                                                                    *
**********************************************************************
*                                                                    *
*       SystemView version: V2.52h                                    *
*                                                                    *
**********************************************************************
---------------------------END-OF-HEADER------------------------------
File    : SEGGER_RTT.c
Purpose : Implementation of SEGGER real-time transfer (RTT) which
          allows real-time communication on targets which support
          debugger memory accesses while the CPU is running.
Revision: $Rev: 13375 $

Additional information:
          Type "int" is assumed to be 32-bits in size
          H->T    Host to target communication
          T->H    Target to host communication

          RTT channel 0 is always present and reserved for Terminal usage.
          Name is fixed to "Terminal"

          Effective buffer size: SizeOfBuffer - 1

          WrOff == RdOff:       Buffer is empty
          WrOff == (RdOff - 1): Buffer is full
          WrOff >  RdOff:       Free space includes wrap-around
          WrOff <  RdOff:       Used space includes wrap-around
          (WrOff == (SizeOfBuffer - 1)) && (RdOff == 0):  
                                Buffer full and wrap-around after next byte


----------------------------------------------------------------------
*/

#include "SEGGER_RTT.h"

#include <string.h>                 // for memcpy

/*********************************************************************
*
*       Configuration, default values
*
**********************************************************************
*/

#ifndef   BUFFER_SIZE_UP
  #define BUFFER_SIZE_UP                                  1024  // Size of the buffer for terminal output of target, up to host
#endif

#ifndef   BUFFER_SIZE_DOWN
  #define BUFFER_SIZE_DOWN                                16    // Size of the buffer for terminal input to target from host (Usually keyboard input)
#endif

#ifndef   SEGGER_RTT_MAX_NUM_UP_BUFFERS
  #define SEGGER_RTT_MAX_NUM_UP_BUFFERS                    2    // Number of up-buffers (T->H) available on this target
#endif

#ifndef   SEGGER_RTT_MAX_NUM_DOWN_BUFFERS
  #define SEGGER_RTT_MAX_NUM_DOWN_BUFFERS                  2    // Number of down-buffers (H->T) available on this target
#endif

#ifndef SEGGER_RTT_BUFFER_SECTION
  #if defined(SEGGER_RTT_SECTION)
    #define SEGGER_RTT_BUFFER_SECTION SEGGER_RTT_SECTION
  #endif
#endif

#ifndef   SEGGER_RTT_ALIGNMENT
  #define SEGGER_RTT_ALIGNMENT                            0
#endif

#ifndef   SEGGER_RTT_BUFFER_ALIGNMENT
  #define SEGGER_RTT_BUFFER_ALIGNMENT                     0
#endif

#ifndef   SEGGER_RTT_MODE_DEFAULT
  #define SEGGER_RTT_MODE_DEFAULT                         SEGGER_RTT_MODE_NO_BLOCK_SKIP
#endif

#ifndef   SEGGER_RTT_LOCK
  #define SEGGER_RTT_LOCK()
#endif

#ifndef   SEGGER_RTT_UNLOCK
  #define SEGGER_RTT_UNLOCK()
#endif

#ifndef   STRLEN
  #define STRLEN(a)                                       strlen((a))
#endif

#ifndef   SEGGER_RTT_MEMCPY_USE_BYTELOOP
  #define SEGGER_RTT_MEMCPY_USE_BYTELOOP                  0
#endif

#ifndef   SEGGER_RTT_MEMCPY
  #ifdef  MEMCPY
    #define SEGGER_RTT_MEMCPY(pDest, pSrc, NumBytes)      MEMCPY((pDest), (pSrc), (NumBytes))
  #else
    #define SEGGER_RTT_MEMCPY(pDest, pSrc, NumBytes)      memcpy((pDest), (pSrc), (NumBytes))
  #endif
#endif

#ifndef   MIN
  #define MIN(a, b)         (((a) < (b)) ? (a) : (b))
#endif

#ifndef   MAX
  #define MAX(a, b)         (((a) > (b)) ? (a) : (b))
#endif
//
// For some environments, NULL may not be defined until certain headers are included
//
#ifndef NULL
  #define NULL 0
#endif

/*********************************************************************
*
*       Defines, fixed
*
**********************************************************************
*/
#if (defined __ICCARM__) || (defined __ICCRX__)
  #define RTT_PRAGMA(P) _Pragma(#P)
#endif

#if SEGGER_RTT_ALIGNMENT || SEGGER_RTT_BUFFER_ALIGNMENT
  #if (defined __GNUC__)
    #define SEGGER_RTT_ALIGN(Var, Alignment) Var __attribute__ ((aligned (Alignment)))
  #elif (defined __ICCARM__) || (defined __ICCRX__)
    #define PRAGMA(A) _Pragma(#A)
#define SEGGER_RTT_ALIGN(Var, Alignment) RTT_PRAGMA(data_alignment=Alignment) \
                                  Var
  #elif (defined __CC_ARM)
    #define SEGGER_RTT_ALIGN(Var, Alignment) Var __attribute__ ((aligned (Alignment)))
  #else
    #error "Alignment not supported for this compiler."
  #endif
#else
  #define SEGGER_RTT_ALIGN(Var, Alignment) Var
#endif

#if defined(SEGGER_RTT_SECTION) || defined (SEGGER_RTT_BUFFER_SECTION)
  #if (defined __GNUC__)
    #define SEGGER_RTT_PUT_SECTION(Var, Section) __attribute__ ((section (Section))) Var
  #elif (defined __ICCARM__) || (defined __ICCRX__)
#define SEGGER_RTT_PUT_SECTION(Var, Section) RTT_PRAGMA(location=Section) \
                                        Var
  #elif (defined __CC_ARM)
    #define SEGGER_RTT_PUT_SECTION(Var, Section) __attribute__ ((section (Section), zero_init))  Var
  #else
    #error "Section placement not supported for this compiler."
  #endif
#else
  #define SEGGER_RTT_PUT_SECTION(Var, Section) Var
#endif


#if SEGGER_RTT_ALIGNMENT
  #define SEGGER_RTT_CB_ALIGN(Var)  SEGGER_RTT_ALIGN(Var, SEGGER_RTT_ALIGNMENT)
#else
  #define SEGGER_RTT_CB_ALIGN(Var)  Var
#endif

#if SEGGER_RTT_BUFFER_ALIGNMENT
  #define SEGGER_RTT_BUFFER_ALIGN(Var)  SEGGER_RTT_ALIGN(Var, SEGGER_RTT_BUFFER_ALIGNMENT)
#else
  #define SEGGER_RTT_BUFFER_ALIGN(Var)  Var
#endif


#if defined(SEGGER_RTT_SECTION)
  #define SEGGER_RTT_PUT_CB_SECTION(Var) SEGGER_RTT_PUT_SECTION(Var, SEGGER_RTT_SECTION)
#else
  #define SEGGER_RTT_PUT_CB_SECTION(Var) Var
#endif

#if defined(SEGGER_RTT_BUFFER_SECTION)
  #define SEGGER_RTT_PUT_BUFFER_SECTION(Var) SEGGER_RTT_PUT_SECTION(Var, SEGGER_RTT_BUFFER_SECTION)
#else
  #define SEGGER_RTT_PUT_BUFFER_SECTION(Var) Var
#endif

/*********************************************************************
*
*       Static const data
*
**********************************************************************
*/

static unsigned char _aTerminalId[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
//
// RTT Control Block and allocate buffers for channel 0
//
SEGGER_RTT_PUT_CB_SECTION(SEGGER_RTT_CB_ALIGN(SEGGER_RTT_CB _SEGGER_RTT));

SEGGER_RTT_PUT_BUFFER_SECTION(SEGGER_RTT_BUFFER_ALIGN(static char _acUpBuffer  [BUFFER_SIZE_UP]));
SEGGER_RTT_PUT_BUFFER_SECTION(SEGGER_RTT_BUFFER_ALIGN(static char _acDownBuffer[BUFFER_SIZE_DOWN]));

static char _ActiveTerminal;

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/

/*********************************************************************
*
*       _DoInit()
*
*  Function description
*    Initializes the control block an buffers.
*    May only be called via INIT() to avoid overriding settings.
*
*/
#define INIT()  do {                                            \
                  if (_SEGGER_RTT.acID[0] == '\0') { _DoInit(); }  \
                } while (0)
static void _DoInit(void) {
  SEGGER_RTT_CB* p;
  //
  // Initialize control block
  //
  p = &_SEGGER_RTT;
  p->MaxNumUpBuffers    = SEGGER_RTT_MAX_NUM_UP_BUFFERS;
  p->MaxNumDownBuffers  = SEGGER_RTT_MAX_NUM_DOWN_BUFFERS;
  //
  // Initialize up buffer 0
  //
  p->aUp[0].sName         = "Terminal";
  p->aUp[0].pBuffer       = _acUpBuffer;
  p->aUp[0].SizeOfBuffer  = sizeof(_acUpBuffer);
  p->aUp[0].RdOff         = 0u;
  p->aUp[0].WrOff         = 0u;
  p->aUp[0].Flags         = SEGGER_RTT_MODE_DEFAULT;
  //
  // Initialize down buffer 0
  //
  p->aDown[0].sName         = "Terminal";
  p->aDown[0].pBuffer       = _acDownBuffer;
  p->aDown[0].SizeOfBuffer  = sizeof(_acDownBuffer);
  p->aDown[0].RdOff         = 0u;
  p->aDown[0].WrOff         = 0u;
  p->aDown[0].Flags         = SEGGER_RTT_MODE_DEFAULT;
  //
  // Finish initialization of the control block.
  // Copy Id string in three steps to make sure "SEGGER RTT" is not found
  // in initializer memory (usually flash) by J-Link
  //
  strcpy(&p->acID[7], "RTT");
  strcpy(&p->acID[0], "SEGGER");
  p->acID[6] = ' ';
}

/*********************************************************************
*
*       _WriteBlocking()
*
*  Function description
*    Stores a specified number of characters in SEGGER RTT ring buffer
*    and updates the associated write pointer which is periodically
*    read by the host.
*    The caller is responsible for managing the write chunk sizes as
*    _WriteBlocking() will block until all data has been posted successfully.
*
*  Parameters
*    pRing        Ring buffer to post to.
*    pBuffer      Pointer to character array. Does not need to point to a \0 terminated string.
*    NumBytes     Number of bytes to be stored in the SEGGER RTT control block.
*
*  Return value
*    >= 0 - Number of bytes written into buffer.
*/
static unsigned _WriteBlocking(SEGGER_RTT_BUFFER_UP* pRing, const char* pBuffer, unsigned NumBytes) {
  unsigned NumBytesToWrite;
  unsigned NumBytesWritten;
  unsigned RdOff;
  unsigned WrOff;
#if SEGGER_RTT_MEMCPY_USE_BYTELOOP
  char*    pDst;
#endif
  //
  // Write data to buffer and handle wrap-around if necessary
  //
  NumBytesWritten = 0u;
  WrOff = pRing->WrOff;
  do {
    RdOff = pRing->RdOff;                         // May be changed by host (debug probe) in the meantime
    if (RdOff > WrOff) {
      NumBytesToWrite = RdOff - WrOff - 1u;
    } else {
      NumBytesToWrite = pRing->SizeOfBuffer - (WrOff - RdOff + 1u);
    }
    NumBytesToWrite = MIN(NumBytesToWrite, (pRing->SizeOfBuffer - WrOff));      // Number of bytes that can be written until buffer wrap-around
    NumBytesToWrite = MIN(NumBytesToWrite, NumBytes);
#if SEGGER_RTT_MEMCPY_USE_BYTELOOP
    pDst = pRing->pBuffer + WrOff;
    NumBytesWritten += NumBytesToWrite;
    NumBytes        -= NumBytesToWrite;
    WrOff           += NumBytesToWrite;
    while (NumBytesToWrite--) {
      *pDst++ = *pBuffer++;
    };
#else
    SEGGER_RTT_MEMCPY(pRing->pBuffer + WrOff, pBuffer, NumBytesToWrite);
    NumBytesWritten += NumBytesToWrite;
    pBuffer         += NumBytesToWrite;
    NumBytes        -= NumBytesToWrite;
    WrOff           += NumBytesToWrite;
#endif
    if (WrOff == pRing->SizeOfBuffer) {
      WrOff = 0u;
    }
    pRing->WrOff = WrOff;
  } while (NumBytes);
  //
  return NumBytesWritten;
}

/*********************************************************************
*
*       _WriteNoCheck()
*
*  Function description
*    Stores a specified number of characters in SEGGER RTT ring buffer
*    and updates the associated write pointer which is periodically
*    read by the host.
*    It is callers responsibility to make sure data actually fits in buffer.
*
*  Parameters
*    pRing        Ring buffer to post to.
*    pBuffer      Pointer to character array. Does not need to point to a \0 terminated string.
*    NumBytes     Number of bytes to be stored in the SEGGER RTT control block.
*
*  Notes
*    (1) If there might not be enough space in the "Up"-buffer, call _WriteBlocking
*/
static void _WriteNoCheck(SEGGER_RTT_BUFFER_UP* pRing, const char* pData, unsigned NumBytes) {
  unsigned NumBytesAtOnce;
  unsigned WrOff;
  unsigned Rem;
#if SEGGER_RTT_MEMCPY_USE_BYTELOOP
  char*    pDst;
#endif

  WrOff = pRing->WrOff;
  Rem = pRing->SizeOfBuffer - WrOff;
  if (Rem > NumBytes) {
    //
    // All data fits before wrap around
    //
#if SEGGER_RTT_MEMCPY_USE_BYTELOOP
    pDst = pRing->pBuffer + WrOff;
    WrOff += NumBytes;
    while (NumBytes--) {
      *pDst++ = *pData++;
    };
    pRing->WrOff = WrOff;
#else
    SEGGER_RTT_MEMCPY(pRing->pBuffer + WrOff, pData, NumBytes);
    pRing->WrOff = WrOff + NumBytes;
#endif
  } else {
    //
    // We reach the end of the buffer, so need to wrap around
    //
#if SEGGER_RTT_MEMCPY_USE_BYTELOOP
    pDst = pRing->pBuffer + WrOff;
    NumBytesAtOnce = Rem;
    while (NumBytesAtOnce--) {
      *pDst++ = *pData++;
    };
    pDst = pRing->pBuffer;
    NumBytesAtOnce = NumBytes - Rem;
    while (NumBytesAtOnce--) {
      *pDst++ = *pData++;
    };
    pRing->WrOff = NumBytes - Rem;
#else
    NumBytesAtOnce = Rem;
    SEGGER_RTT_MEMCPY(pRing->pBuffer + WrOff, pData, NumBytesAtOnce);
    NumBytesAtOnce = NumBytes - Rem;
    SEGGER_RTT_MEMCPY(pRing->pBuffer, pData + Rem, NumBytesAtOnce);
    pRing->WrOff = NumBytesAtOnce;
#endif
  }
}

/*********************************************************************
*
*       _PostTerminalSwitch()
*
*  Function description
*    Switch terminal to the given terminal ID.  It is the caller's
*    responsibility to ensure the terminal ID is correct and there is
*    enough space in the buffer for this to complete successfully.
*
*  Parameters
*    pRing        Ring buffer to post to.
*    TerminalId   Terminal ID to switch to.
*/
static void _PostTerminalSwitch(SEGGER_RTT_BUFFER_UP* pRing, unsigned char TerminalId) {
  unsigned char ac[2];

  ac[0] = 0xFFu;
  ac[1] = _aTerminalId[TerminalId];  // Caller made already sure that TerminalId does not exceed our terminal limit
  _WriteBlocking(pRing, (const char*)ac, 2u);
}

/*********************************************************************
*
*       _GetAvailWriteSpace()
*
*  Function description
*    Returns the number of bytes that can be written to the ring
*    buffer without blocking.
*
*  Parameters
*    pRing        Ring buffer to check.
*
*  Return value
*    Number of bytes that are free in the buffer.
*/
static unsigned _GetAvailWriteSpace(SEGGER_RTT_BUFFER_UP* pRing) {
  unsigned RdOff;
  unsigned WrOff;
  unsigned r;
  //
  // Avoid warnings regarding volatile access order.  It's not a problem
  // in this case, but dampen compiler enthusiasm.
  //
  RdOff = pRing->RdOff;
  WrOff = pRing->WrOff;
  if (RdOff <= WrOff) {
    r = pRing->SizeOfBuffer - 1u - WrOff + RdOff;
  } else {
    r = RdOff - WrOff - 1u;
  }
  return r;
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       SEGGER_RTT_ReadNoLock()
*
*  Function description
*    Reads characters from SEGGER real-time-terminal control block
*    which have been previously stored by the host.
*    Do not lock against interrupts and multiple access.
*
*  Parameters
*    BufferIndex  Index of Down-buffer to be used (e.g. 0 for "Terminal").
*    pBuffer      Pointer to buffer provided by target application, to copy characters from RTT-down-buffer to.
*    BufferSize   Size of the target application buffer.
*
*  Return value
*    Number of bytes that have been read.
*/
unsigned SEGGER_RTT_ReadNoLock(unsigned BufferIndex, void* pData, unsigned BufferSize) {
  unsigned                NumBytesRem;
  unsigned                NumBytesRead;
  unsigned                RdOff;
  unsigned                WrOff;
  unsigned char*          pBuffer;
  SEGGER_RTT_BUFFER_DOWN* pRing;
#if SEGGER_RTT_MEMCPY_USE_BYTELOOP
  const char*             pSrc;
#endif
  //
  INIT();
  pRing = &_SEGGER_RTT.aDown[BufferIndex];
  pBuffer = (unsigned char*)pData;
  RdOff = pRing->RdOff;
  WrOff = pRing->WrOff;
  NumBytesRead = 0u;
  //
  // Read from current read position to wrap-around of buffer, first
  //
  if (RdOff > WrOff) {
    NumBytesRem = pRing->SizeOfBuffer - RdOff;
    NumBytesRem = MIN(NumBytesRem, BufferSize);
#if SEGGER_RTT_MEMCPY_USE_BYTELOOP
    pSrc = pRing->pBuffer + RdOff;
    NumBytesRead += NumBytesRem;
    BufferSize   -= NumBytesRem;
    RdOff        += NumBytesRem;
    while (NumBytesRem--) {
      *pBuffer++ = *pSrc++;
    };
#else
    SEGGER_RTT_MEMCPY(pBuffer, pRing->pBuffer + RdOff, NumBytesRem);
    NumBytesRead += NumBytesRem;
    pBuffer      += NumBytesRem;
    BufferSize   -= NumBytesRem;
    RdOff        += NumBytesRem;
#endif
    //
    // Handle wrap-around of buffer
    //
    if (RdOff == pRing->SizeOfBuffer) {
      RdOff = 0u;
    }
  }
  //
  // Read remaining items of buffer
  //
  NumBytesRem = WrOff - RdOff;
  NumBytesRem = MIN(NumBytesRem, BufferSize);
  if (NumBytesRem > 0u) {
#if SEGGER_RTT_MEMCPY_USE_BYTELOOP
    pSrc = pRing->pBuffer + RdOff;
    NumBytesRead += NumBytesRem;
    BufferSize   -= NumBytesRem;
    RdOff        += NumBytesRem;
    while (NumBytesRem--) {
      *pBuffer++ = *pSrc++;
    };
#else
    SEGGER_RTT_MEMCPY(pBuffer, pRing->pBuffer + RdOff, NumBytesRem);
    NumBytesRead += NumBytesRem;
    pBuffer      += NumBytesRem;
    BufferSize   -= NumBytesRem;
    RdOff        += NumBytesRem;
#endif
  }
  if (NumBytesRead) {
    pRing->RdOff = RdOff;
  }
  //
  return NumBytesRead;
}

/*********************************************************************
*
*       SEGGER_RTT_Read
*
*  Function description
*    Reads characters from SEGGER real-time-terminal control block
*    which have been previously stored by the host.
*
*  Parameters
*    BufferIndex  Index of Down-buffer to be used (e.g. 0 for "Terminal").
*    pBuffer      Pointer to buffer provided by target application, to copy characters from RTT-down-buffer to.
*    BufferSize   Size of the target application buffer.
*
*  Return value
*    Number of bytes that have been read.
*/
unsigned SEGGER_RTT_Read(unsigned BufferIndex, void* pBuffer, unsigned BufferSize) {
  unsigned NumBytesRead;
  //
  SEGGER_RTT_LOCK();
  //
  // Call the non-locking read function
  //
  NumBytesRead = SEGGER_RTT_ReadNoLock(BufferIndex, pBuffer, BufferSize);
  //
  // Finish up.
  //
  SEGGER_RTT_UNLOCK();
  //
  return NumBytesRead;
}

/*********************************************************************
*
*       SEGGER_RTT_WriteWithOverwriteNoLock
*
*  Function description
*    Stores a specified number of characters in SEGGER RTT
*    control block.
*    SEGGER_RTT_WriteWithOverwriteNoLock does not lock the application 
*    and overwrites data if the data does not fit into the buffer.
*
*  Parameters
*    BufferIndex  Index of "Up"-buffer to be used (e.g. 0 for "Terminal").
*    pBuffer      Pointer to character array. Does not need to point to a \0 terminated string.
*    NumBytes     Number of bytes to be stored in the SEGGER RTT control block.
*
*  Notes
*    (1) If there is not enough space in the "Up"-buffer, data is overwritten.
*    (2) For performance reasons this function does not call Init()
*        and may only be called after RTT has been initialized.
*        Either by calling SEGGER_RTT_Init() or calling another RTT API function first.
*    (3) Do not use SEGGER_RTT_WriteWithOverwriteNoLock if a J-Link 
*        connection reads RTT data.
*/
void SEGGER_RTT_WriteWithOverwriteNoLock(unsigned BufferIndex, const void* pBuffer, unsigned NumBytes) {
  const char*           pData;
  SEGGER_RTT_BUFFER_UP* pRing;
  unsigned              Avail;
#if SEGGER_RTT_MEMCPY_USE_BYTELOOP
  char*                 pDst;
#endif

  pData = (const char *)pBuffer;
  //
  // Get "to-host" ring buffer and copy some elements into local variables.
  //
  pRing = &_SEGGER_RTT.aUp[BufferIndex];
  //
  // Check if we will overwrite data and need to adjust the RdOff.
  //
  if (pRing->WrOff == pRing->RdOff) {
    Avail = pRing->SizeOfBuffer - 1u;
  } else if ( pRing->WrOff < pRing->RdOff) {
    Avail = pRing->RdOff - pRing->WrOff - 1u;
  } else {
    Avail = pRing->RdOff - pRing->WrOff - 1u + pRing->SizeOfBuffer;
  }
  if (NumBytes > Avail) {
    pRing->RdOff += (NumBytes - Avail);
    while (pRing->RdOff >= pRing->SizeOfBuffer) {
      pRing->RdOff -= pRing->SizeOfBuffer;
    }
  }
  //
  // Write all data, no need to check the RdOff, but possibly handle multiple wrap-arounds
  //
  Avail = pRing->SizeOfBuffer - pRing->WrOff;
  do {
    if (Avail > NumBytes) {
      //
      // Last round
      //
#if SEGGER_RTT_MEMCPY_USE_BYTELOOP
      pDst = pRing->pBuffer + pRing->WrOff;
      Avail = NumBytes;
      while (NumBytes--) {
        *pDst++ = *pData++;
      };
      pRing->WrOff += Avail;
#else
      SEGGER_RTT_MEMCPY(pRing->pBuffer + pRing->WrOff, pData, NumBytes);
      pRing->WrOff += NumBytes;
#endif
      break;
    } else {
      //
      //  Wrap-around necessary, write until wrap-around and reset WrOff
      //
#if SEGGER_RTT_MEMCPY_USE_BYTELOOP
      pDst = pRing->pBuffer + pRing->WrOff;
      NumBytes -= Avail;
      while (Avail--) {
        *pDst++ = *pData++;
      };
      pRing->WrOff = 0;
#else
      SEGGER_RTT_MEMCPY(pRing->pBuffer + pRing->WrOff, pData, Avail);
      pData += Avail;
      pRing->WrOff = 0;
      NumBytes -= Avail;
#endif
      Avail = (pRing->SizeOfBuffer - 1);
    }
  } while (NumBytes);
}

/*********************************************************************
*
*       SEGGER_RTT_WriteSkipNoLock
*
*  Function description
*    Stores a specified number of characters in SEGGER RTT
*    control block which is then read by the host.
*    SEGGER_RTT_WriteSkipNoLock does not lock the application and
*    skips all data, if the data does not fit into the buffer.
*
*  Parameters
*    BufferIndex  Index of "Up"-buffer to be used (e.g. 0 for "Terminal").
*    pBuffer      Pointer to character array. Does not need to point to a \0 terminated string.
*    NumBytes     Number of bytes to be stored in the SEGGER RTT control block.
*                 MUST be > 0!!!
*                 This is done for performance reasons, so no initial check has do be done.
*
*  Return value
*    1: Data has been copied
*    0: No space, data has not been copied
*
*  Notes
*    (1) If there is not enough space in the "Up"-buffer, all data is dropped.
*    (2) For performance reasons this function does not call Init()
*        and may only be called after RTT has been initialized.
*        Either by calling SEGGER_RTT_Init() or calling another RTT API function first.
*/
#if (RTT_USE_ASM == 0)
unsigned SEGGER_RTT_WriteSkipNoLock(unsigned BufferIndex, const void* pBuffer, unsigned NumBytes) {
  const char*           pData;
  SEGGER_RTT_BUFFER_UP* pRing;
  unsigned              Avail;
  unsigned              RdOff;
  unsigned              WrOff;
  unsigned              Rem;
  //
  // Cases:
  //   1) RdOff <= WrOff => Space until wrap-around is sufficient
  //   2) RdOff <= WrOff => Space after wrap-around needed (copy in 2 chunks)
  //   3) RdOff <  WrOff => No space in buf
  //   4) RdOff >  WrOff => Space is sufficient
  //   5) RdOff >  WrOff => No space in buf
  //
  // 1) is the most common case for large buffers and assuming that J-Link reads the data fast enough
  //
  pData = (const char *)pBuffer;
  pRing = &_SEGGER_RTT.aUp[BufferIndex];
  RdOff = pRing->RdOff;
  WrOff = pRing->WrOff;
  if (RdOff <= WrOff) {                                 // Case 1), 2) or 3)
    Avail = pRing->SizeOfBuffer - WrOff - 1u;           // Space until wrap-around (assume 1 byte not usable for case that RdOff == 0)
    if (Avail >= NumBytes) {                            // Case 1)?
CopyStraight:
      memcpy(pRing->pBuffer + WrOff, pData, NumBytes);
      pRing->WrOff = WrOff + NumBytes;
      return 1;
    }
    Avail += RdOff;                                     // Space incl. wrap-around
    if (Avail >= NumBytes) {                            // Case 2? => If not, we have case 3) (does not fit)
      Rem = pRing->SizeOfBuffer - WrOff;                // Space until end of buffer
      memcpy(pRing->pBuffer + WrOff, pData, Rem);       // Copy 1st chunk
      NumBytes -= Rem;
      //
      // Special case: First check that assumed RdOff == 0 calculated that last element before wrap-around could not be used
      // But 2nd check (considering space until wrap-around and until RdOff) revealed that RdOff is not 0, so we can use the last element
      // In this case, we may use a copy straight until buffer end anyway without needing to copy 2 chunks
      // Therefore, check if 2nd memcpy is necessary at all
      //
      if (NumBytes) {
        memcpy(pRing->pBuffer, pData + Rem, NumBytes);
      }
      pRing->WrOff = NumBytes;
      return 1;
    }
  } else {                                             // Potential case 4)
    Avail = RdOff - WrOff - 1u;
    if (Avail >= NumBytes) {                           // Case 4)? => If not, we have case 5) (does not fit)
      goto CopyStraight;
    }
  }
  return 0;     // No space in buffer
}
#endif

/*********************************************************************
*
*       SEGGER_RTT_WriteNoLock
*
*  Function description
*    Stores a specified number of characters in SEGGER RTT
*    control block which is then read by the host.
*    SEGGER_RTT_WriteNoLock does not lock the application.
*
*  Parameters
*    BufferIndex  Index of "Up"-buffer to be used (e.g. 0 for "Terminal").
*    pBuffer      Pointer to character array. Does not need to point to a \0 terminated string.
*    NumBytes     Number of bytes to be stored in the SEGGER RTT control block.
*
*  Return value
*    Number of bytes which have been stored in the "Up"-buffer.
*
*  Notes
*    (1) Data is stored according to buffer flags.
*    (2) For performance reasons this function does not call Init()
*        and may only be called after RTT has been initialized.
*        Either by calling SEGGER_RTT_Init() or calling another RTT API function first.
*/
unsigned SEGGER_RTT_WriteNoLock(unsigned BufferIndex, const void* pBuffer, unsigned NumBytes) {
  unsigned              Status;
  unsigned              Avail;
  const char*           pData;
  SEGGER_RTT_BUFFER_UP* pRing;

  pData = (const char *)pBuffer;
  //
  // Get "to-host" ring buffer.
  //
  pRing = &_SEGGER_RTT.aUp[BufferIndex];
  //
  // How we output depends upon the mode...
  //
  switch (pRing->Flags) {
  case SEGGER_RTT_MODE_NO_BLOCK_SKIP:
    //
    // If we are in skip mode and there is no space for the whole
    // of this output, don't bother.
    //
    Avail = _GetAvailWriteSpace(pRing);
    if (Avail < NumBytes) {
      Status = 0u;
    } else {
      Status = NumBytes;
      _WriteNoCheck(pRing, pData, NumBytes);
    }
    break;
  case SEGGER_RTT_MODE_NO_BLOCK_TRIM:
    //
    // If we are in trim mode, trim to what we can output without blocking.
    //
    Avail = _GetAvailWriteSpace(pRing);
    Status = Avail < NumBytes ? Avail : NumBytes;
    _WriteNoCheck(pRing, pData, Status);
    break;
  case SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL:
    //
    // If we are in blocking mode, output everything.
    //
    Status = _WriteBlocking(pRing, pData, NumBytes);
    break;
  default:
    Status = 0u;
    break;
  }
  //
  // Finish up.
  //
  return Status;
}

/*********************************************************************
*
*       SEGGER_RTT_Write
*
*  Function description
*    Stores a specified number of characters in SEGGER RTT
*    control block which is then read by the host.
*
*  Parameters
*    BufferIndex  Index of "Up"-buffer to be used (e.g. 0 for "Terminal").
*    pBuffer      Pointer to character array. Does not need to point to a \0 terminated string.
*    NumBytes     Number of bytes to be stored in the SEGGER RTT control block.
*
*  Return value
*    Number of bytes which have been stored in the "Up"-buffer.
*
*  Notes
*    (1) Data is stored according to buffer flags.
*/
unsigned SEGGER_RTT_Write(unsigned BufferIndex, const void* pBuffer, unsigned NumBytes) {
  unsigned Status;
  //
  INIT();
  SEGGER_RTT_LOCK();
  //
  // Call the non-locking write function
  //
  Status = SEGGER_RTT_WriteNoLock(BufferIndex, pBuffer, NumBytes);
  //
  // Finish up.
  //
  SEGGER_RTT_UNLOCK();
  //
  return Status;
}

/*********************************************************************
*
*       SEGGER_RTT_WriteString
*
*  Function description
*    Stores string in SEGGER RTT control block.
*    This data is read by the host.
*
*  Parameters
*    BufferIndex  Index of "Up"-buffer to be used (e.g. 0 for "Terminal").
*    s            Pointer to string.
*
*  Return value
*    Number of bytes which have been stored in the "Up"-buffer.
*
*  Notes
*    (1) Data is stored according to buffer flags.
*    (2) String passed to this function has to be \0 terminated
*    (3) \0 termination character is *not* stored in RTT buffer
*/
unsigned SEGGER_RTT_WriteString(unsigned BufferIndex, const char* s) {
  unsigned Len;

  Len = STRLEN(s);
  return SEGGER_RTT_Write(BufferIndex, s, Len);
}

/*********************************************************************
*
*       SEGGER_RTT_PutCharSkipNoLock
*
*  Function description
*    Stores a single character/byte in SEGGER RTT buffer.
*    SEGGER_RTT_PutCharSkipNoLock does not lock the application and
*    skips the byte, if it does not fit into the buffer.
*
*  Parameters
*    BufferIndex  Index of "Up"-buffer to be used (e.g. 0 for "Terminal").
*    c            Byte to be stored.
*
*  Return value
*    Number of bytes which have been stored in the "Up"-buffer.
*
*  Notes
*    (1) If there is not enough space in the "Up"-buffer, the character is dropped.
*    (2) For performance reasons this function does not call Init()
*        and may only be called after RTT has been initialized.
*        Either by calling SEGGER_RTT_Init() or calling another RTT API function first.
*/

unsigned SEGGER_RTT_PutCharSkipNoLock(unsigned BufferIndex, char c) {
  SEGGER_RTT_BUFFER_UP* pRing;
  unsigned              WrOff;
  unsigned              Status;
  //
  // Get "to-host" ring buffer.
  //
  pRing = &_SEGGER_RTT.aUp[BufferIndex];
  //
  // Get write position and handle wrap-around if necessary
  //
  WrOff = pRing->WrOff + 1;
  if (WrOff == pRing->SizeOfBuffer) {
    WrOff = 0;
  }
  //
  // Output byte if free space is available
  //
  if (WrOff != pRing->RdOff) {
    pRing->pBuffer[pRing->WrOff] = c;
    pRing->WrOff = WrOff;
    Status = 1;
  } else {
    Status = 0;
  }
  //
  return Status;
}

/*********************************************************************
*
*       SEGGER_RTT_PutCharSkip
*
*  Function description
*    Stores a single character/byte in SEGGER RTT buffer.
*
*  Parameters
*    BufferIndex  Index of "Up"-buffer to be used (e.g. 0 for "Terminal").
*    c            Byte to be stored.
*
*  Return value
*    Number of bytes which have been stored in the "Up"-buffer.
*
*  Notes
*    (1) If there is not enough space in the "Up"-buffer, the character is dropped.
*/

unsigned SEGGER_RTT_PutCharSkip(unsigned BufferIndex, char c) {
  SEGGER_RTT_BUFFER_UP* pRing;
  unsigned              WrOff;
  unsigned              Status;
  //
  // Prepare
  //
  INIT();
  SEGGER_RTT_LOCK();
  //
  // Get "to-host" ring buffer.
  //
  pRing = &_SEGGER_RTT.aUp[BufferIndex];
  //
  // Get write position and handle wrap-around if necessary
  //
  WrOff = pRing->WrOff + 1;
  if (WrOff == pRing->SizeOfBuffer) {
    WrOff = 0;
  }
  //
  // Output byte if free space is available
  //
  if (WrOff != pRing->RdOff) {
    pRing->pBuffer[pRing->WrOff] = c;
    pRing->WrOff = WrOff;
    Status = 1;
  } else {
    Status = 0;
  }
  //
  // Finish up.
  //
  SEGGER_RTT_UNLOCK();
  //
  return Status;
}

 /*********************************************************************
*
*       SEGGER_RTT_PutChar
*
*  Function description
*    Stores a single character/byte in SEGGER RTT buffer.
*
*  Parameters
*    BufferIndex  Index of "Up"-buffer to be used (e.g. 0 for "Terminal").
*    c            Byte to be stored.
*
*  Return value
*    Number of bytes which have been stored in the "Up"-buffer.
*
*  Notes
*    (1) Data is stored according to buffer flags.
*/

unsigned SEGGER_RTT_PutChar(unsigned BufferIndex, char c) {
  SEGGER_RTT_BUFFER_UP* pRing;
  unsigned              WrOff;
  unsigned              Status;
  //
  // Prepare
  //
  INIT();
  SEGGER_RTT_LOCK();
  //
  // Get "to-host" ring buffer.
  //
  pRing = &_SEGGER_RTT.aUp[BufferIndex];
  //
  // Get write position and handle wrap-around if necessary
  //
  WrOff = pRing->WrOff + 1;
  if (WrOff == pRing->SizeOfBuffer) {
    WrOff = 0;
  }
  //
  // Wait for free space if mode is set to blocking
  //
  if (pRing->Flags == SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL) {
    while (WrOff == pRing->RdOff) {
      ;
    }
  }
  //
  // Output byte if free space is available
  //
  if (WrOff != pRing->RdOff) {
    pRing->pBuffer[pRing->WrOff] = c;
    pRing->WrOff = WrOff;
    Status = 1;
  } else {
    Status = 0;
  }
  //
  // Finish up.
  //
  SEGGER_RTT_UNLOCK();
  //
  return Status;
}

/*********************************************************************
*
*       SEGGER_RTT_GetKey
*
*  Function description
*    Reads one character from the SEGGER RTT buffer.
*    Host has previously stored data there.
*
*  Return value
*    <  0 -   No character available (buffer empty).
*    >= 0 -   Character which has been read. (Possible values: 0 - 255)
*
*  Notes
*    (1) This function is only specified for accesses to RTT buffer 0.
*/
int SEGGER_RTT_GetKey(void) {
  char c;
  int r;

  r = (int)SEGGER_RTT_Read(0u, &c, 1u);
  if (r == 1) {
    r = (int)(unsigned char)c;
  } else {
    r = -1;
  }
  return r;
}

/*********************************************************************
*
*       SEGGER_RTT_WaitKey
*
*  Function description
*    Waits until at least one character is avaible in the SEGGER RTT buffer.
*    Once a character is available, it is read and this function returns.
*
*  Return value
*    >=0 -   Character which has been read.
*
*  Notes
*    (1) This function is only specified for accesses to RTT buffer 0
*    (2) This function is blocking if no character is present in RTT buffer
*/
int SEGGER_RTT_WaitKey(void) {
  int r;

  do {
    r = SEGGER_RTT_GetKey();
  } while (r < 0);
  return r;
}

/*********************************************************************
*
*       SEGGER_RTT_HasKey
*
*  Function description
*    Checks if at least one character for reading is available in the SEGGER RTT buffer.
*
*  Return value
*    == 0 -     No characters are available to read.
*    == 1 -     At least one character is available.
*
*  Notes
*    (1) This function is only specified for accesses to RTT buffer 0
*/
int SEGGER_RTT_HasKey(void) {
  unsigned RdOff;
  int r;

  INIT();
  RdOff = _SEGGER_RTT.aDown[0].RdOff;
  if (RdOff != _SEGGER_RTT.aDown[0].WrOff) {
    r = 1;
  } else {
    r = 0;
  }
  return r;
}

/*********************************************************************
*
*       SEGGER_RTT_HasData
*
*  Function description
*    Check if there is data from the host in the given buffer.
*
*  Return value:
*  ==0:  No data
*  !=0:  Data in buffer
*
*/
unsigned SEGGER_RTT_HasData(unsigned BufferIndex) {
  SEGGER_RTT_BUFFER_DOWN* pRing;
  unsigned                v;

  pRing = &_SEGGER_RTT.aDown[BufferIndex];
  v = pRing->WrOff;
  return v - pRing->RdOff;
}

/*********************************************************************
*
*       SEGGER_RTT_HasDataUp
*
*  Function description
*    Check if there is data remaining to be sent in the given buffer.
*
*  Return value:
*  ==0:  No data
*  !=0:  Data in buffer
*
*/
unsigned SEGGER_RTT_HasDataUp(unsigned BufferIndex) {
  SEGGER_RTT_BUFFER_UP* pRing;
  unsigned                v;

  pRing = &_SEGGER_RTT.aUp[BufferIndex];
  v = pRing->RdOff;
  return pRing->WrOff - v;
}

/*********************************************************************
*
*       SEGGER_RTT_AllocDownBuffer
*
*  Function description
*    Run-time configuration of the next down-buffer (H->T).
*    The next buffer, which is not used yet is configured.
*    This includes: Buffer address, size, name, flags, ...
*
*  Parameters
*    sName        Pointer to a constant name string.
*    pBuffer      Pointer to a buffer to be used.
*    BufferSize   Size of the buffer.
*    Flags        Operating modes. Define behavior if buffer is full (not enough space for entire message).
*
*  Return value
*    >= 0 - O.K. Buffer Index
*     < 0 - Error
*/
int SEGGER_RTT_AllocDownBuffer(const char* sName, void* pBuffer, unsigned BufferSize, unsigned Flags) {
  int BufferIndex;

  INIT();
  SEGGER_RTT_LOCK();
  BufferIndex = 0;
  do {
    if (_SEGGER_RTT.aDown[BufferIndex].pBuffer == NULL) {
      break;
    }
    BufferIndex++;
  } while (BufferIndex < _SEGGER_RTT.MaxNumDownBuffers);
  if (BufferIndex < _SEGGER_RTT.MaxNumDownBuffers) {
    _SEGGER_RTT.aDown[BufferIndex].sName        = sName;
    _SEGGER_RTT.aDown[BufferIndex].pBuffer      = (char*)pBuffer;
    _SEGGER_RTT.aDown[BufferIndex].SizeOfBuffer = BufferSize;
    _SEGGER_RTT.aDown[BufferIndex].RdOff        = 0u;
    _SEGGER_RTT.aDown[BufferIndex].WrOff        = 0u;
    _SEGGER_RTT.aDown[BufferIndex].Flags        = Flags;
  } else {
    BufferIndex = -1;
  }
  SEGGER_RTT_UNLOCK();
  return BufferIndex;
}

/*********************************************************************
*
*       SEGGER_RTT_AllocUpBuffer
*
*  Function description
*    Run-time configuration of the next up-buffer (T->H).
*    The next buffer, which is not used yet is configured.
*    This includes: Buffer address, size, name, flags, ...
*
*  Parameters
*    sName        Pointer to a constant name string.
*    pBuffer      Pointer to a buffer to be used.
*    BufferSize   Size of the buffer.
*    Flags        Operating modes. Define behavior if buffer is full (not enough space for entire message).
*
*  Return value
*    >= 0 - O.K. Buffer Index
*     < 0 - Error
*/
int SEGGER_RTT_AllocUpBuffer(const char* sName, void* pBuffer, unsigned BufferSize, unsigned Flags) {
  int BufferIndex;

  INIT();
  SEGGER_RTT_LOCK();
  BufferIndex = 0;
  do {
    if (_SEGGER_RTT.aUp[BufferIndex].pBuffer == NULL) {
      break;
    }
    BufferIndex++;
  } while (BufferIndex < _SEGGER_RTT.MaxNumUpBuffers);
  if (BufferIndex < _SEGGER_RTT.MaxNumUpBuffers) {
    _SEGGER_RTT.aUp[BufferIndex].sName        = sName;
    _SEGGER_RTT.aUp[BufferIndex].pBuffer      = (char*)pBuffer;
    _SEGGER_RTT.aUp[BufferIndex].SizeOfBuffer = BufferSize;
    _SEGGER_RTT.aUp[BufferIndex].RdOff        = 0u;
    _SEGGER_RTT.aUp[BufferIndex].WrOff        = 0u;
    _SEGGER_RTT.aUp[BufferIndex].Flags        = Flags;
  } else {
    BufferIndex = -1;
  }
  SEGGER_RTT_UNLOCK();
  return BufferIndex;
}

/*********************************************************************
*
*       SEGGER_RTT_ConfigUpBuffer
*
*  Function description
*    Run-time configuration of a specific up-buffer (T->H).
*    Buffer to be configured is specified by index.
*    This includes: Buffer address, size, name, flags, ...
*
*  Parameters
*    BufferIndex  Index of the buffer to configure.
*    sName        Pointer to a constant name string.
*    pBuffer      Pointer to a buffer to be used.
*    BufferSize   Size of the buffer.
*    Flags        Operating modes. Define behavior if buffer is full (not enough space for entire message).
*
*  Return value
*    >= 0 - O.K.
*     < 0 - Error
*
*  Additional information
*    Buffer 0 is configured on compile-time.
*    May only be called once per buffer.
*    Buffer name and flags can be reconfigured using the appropriate functions.
*/
int SEGGER_RTT_ConfigUpBuffer(unsigned BufferIndex, const char* sName, void* pBuffer, unsigned BufferSize, unsigned Flags) {
  int r;

  INIT();
  if (BufferIndex < (unsigned)_SEGGER_RTT.MaxNumUpBuffers) {
    SEGGER_RTT_LOCK();
    if (BufferIndex > 0u) {
      _SEGGER_RTT.aUp[BufferIndex].sName        = sName;
      _SEGGER_RTT.aUp[BufferIndex].pBuffer      = (char*)pBuffer;
      _SEGGER_RTT.aUp[BufferIndex].SizeOfBuffer = BufferSize;
      _SEGGER_RTT.aUp[BufferIndex].RdOff        = 0u;
      _SEGGER_RTT.aUp[BufferIndex].WrOff        = 0u;
    }
    _SEGGER_RTT.aUp[BufferIndex].Flags          = Flags;
    SEGGER_RTT_UNLOCK();
    r =  0;
  } else {
    r = -1;
  }
  return r;
}

/*********************************************************************
*
*       SEGGER_RTT_ConfigDownBuffer
*
*  Function description
*    Run-time configuration of a specific down-buffer (H->T).
*    Buffer to be configured is specified by index.
*    This includes: Buffer address, size, name, flags, ...
*
*  Parameters
*    BufferIndex  Index of the buffer to configure.
*    sName        Pointer to a constant name string.
*    pBuffer      Pointer to a buffer to be used.
*    BufferSize   Size of the buffer.
*    Flags        Operating modes. Define behavior if buffer is full (not enough space for entire message).
*
*  Return value
*    >= 0  O.K.
*     < 0  Error
*
*  Additional information
*    Buffer 0 is configured on compile-time.
*    May only be called once per buffer.
*    Buffer name and flags can be reconfigured using the appropriate functions.
*/
int SEGGER_RTT_ConfigDownBuffer(unsigned BufferIndex, const char* sName, void* pBuffer, unsigned BufferSize, unsigned Flags) {
  int r;

  INIT();
  if (BufferIndex < (unsigned)_SEGGER_RTT.MaxNumDownBuffers) {
    SEGGER_RTT_LOCK();
    if (BufferIndex > 0u) {
      _SEGGER_RTT.aDown[BufferIndex].sName        = sName;
      _SEGGER_RTT.aDown[BufferIndex].pBuffer      = (char*)pBuffer;
      _SEGGER_RTT.aDown[BufferIndex].SizeOfBuffer = BufferSize;
      _SEGGER_RTT.aDown[BufferIndex].RdOff        = 0u;
      _SEGGER_RTT.aDown[BufferIndex].WrOff        = 0u;
    }
    _SEGGER_RTT.aDown[BufferIndex].Flags          = Flags;
    SEGGER_RTT_UNLOCK();
    r =  0;
  } else {
    r = -1;
  }
  return r;
}

/*********************************************************************
*
*       SEGGER_RTT_SetNameUpBuffer
*
*  Function description
*    Run-time configuration of a specific up-buffer name (T->H).
*    Buffer to be configured is specified by index.
*
*  Parameters
*    BufferIndex  Index of the buffer to renamed.
*    sName        Pointer to a constant name string.
*
*  Return value
*    >= 0  O.K.
*     < 0  Error
*/
int SEGGER_RTT_SetNameUpBuffer(unsigned BufferIndex, const char* sName) {
  int r;

  INIT();
  if (BufferIndex < (unsigned)_SEGGER_RTT.MaxNumUpBuffers) {
    SEGGER_RTT_LOCK();
    _SEGGER_RTT.aUp[BufferIndex].sName = sName;
    SEGGER_RTT_UNLOCK();
    r =  0;
  } else {
    r = -1;
  }
  return r;
}

/*********************************************************************
*
*       SEGGER_RTT_SetNameDownBuffer
*
*  Function description
*    Run-time configuration of a specific Down-buffer name (T->H).
*    Buffer to be configured is specified by index.
*
*  Parameters
*    BufferIndex  Index of the buffer to renamed.
*    sName        Pointer to a constant name string.
*
*  Return value
*    >= 0  O.K.
*     < 0  Error
*/
int SEGGER_RTT_SetNameDownBuffer(unsigned BufferIndex, const char* sName) {
  int r;

  INIT();
  if (BufferIndex < (unsigned)_SEGGER_RTT.MaxNumDownBuffers) {
    SEGGER_RTT_LOCK();
    _SEGGER_RTT.aDown[BufferIndex].sName = sName;
    SEGGER_RTT_UNLOCK();
    r =  0;
  } else {
    r = -1;
  }
  return r;
}

/*********************************************************************
*
*       SEGGER_RTT_SetFlagsUpBuffer
*
*  Function description
*    Run-time configuration of specific up-buffer flags (T->H).
*    Buffer to be configured is specified by index.
*
*  Parameters
*    BufferIndex  Index of the buffer.
*    Flags        Flags to set for the buffer.
*
*  Return value
*    >= 0  O.K.
*     < 0  Error
*/
int SEGGER_RTT_SetFlagsUpBuffer(unsigned BufferIndex, unsigned Flags) {
  int r;

  INIT();
  if (BufferIndex < (unsigned)_SEGGER_RTT.MaxNumUpBuffers) {
    SEGGER_RTT_LOCK();
    _SEGGER_RTT.aUp[BufferIndex].Flags = Flags;
    SEGGER_RTT_UNLOCK();
    r =  0;
  } else {
    r = -1;
  }
  return r;
}

/*********************************************************************
*
*       SEGGER_RTT_SetFlagsDownBuffer
*
*  Function description
*    Run-time configuration of specific Down-buffer flags (T->H).
*    Buffer to be configured is specified by index.
*
*  Parameters
*    BufferIndex  Index of the buffer to renamed.
*    Flags        Flags to set for the buffer.
*
*  Return value
*    >= 0  O.K.
*     < 0  Error
*/
int SEGGER_RTT_SetFlagsDownBuffer(unsigned BufferIndex, unsigned Flags) {
  int r;

  INIT();
  if (BufferIndex < (unsigned)_SEGGER_RTT.MaxNumDownBuffers) {
    SEGGER_RTT_LOCK();
    _SEGGER_RTT.aDown[BufferIndex].Flags = Flags;
    SEGGER_RTT_UNLOCK();
    r =  0;
  } else {
    r = -1;
  }
  return r;
}

/*********************************************************************
*
*       SEGGER_RTT_Init
*
*  Function description
*    Initializes the RTT Control Block.
*    Should be used in RAM targets, at start of the application.
*
*/
void SEGGER_RTT_Init (void) {
  _DoInit();
}

/*********************************************************************
*
*       SEGGER_RTT_SetTerminal
*
*  Function description
*    Sets the terminal to be used for output on channel 0.
*
*  Parameters
*    TerminalId  Index of the terminal.
*
*  Return value
*    >= 0  O.K.
*     < 0  Error (e.g. if RTT is configured for non-blocking mode and there was no space in the buffer to set the new terminal Id)
*/
int SEGGER_RTT_SetTerminal (char TerminalId) {
  unsigned char         ac[2];
  SEGGER_RTT_BUFFER_UP* pRing;
  unsigned Avail;
  int r;
  //
  INIT();
  //
  r = 0;
  ac[0] = 0xFFu;
  if ((unsigned char)TerminalId < (unsigned char)sizeof(_aTerminalId)) { // We only support a certain number of channels
    ac[1] = _aTerminalId[(unsigned char)TerminalId];
    pRing = &_SEGGER_RTT.aUp[0];    // Buffer 0 is always reserved for terminal I/O, so we can use index 0 here, fixed
    SEGGER_RTT_LOCK();    // Lock to make sure that no other task is writing into buffer, while we are and number of free bytes in buffer does not change downwards after checking and before writing
    if ((pRing->Flags & SEGGER_RTT_MODE_MASK) == SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL) {
      _ActiveTerminal = TerminalId;
      _WriteBlocking(pRing, (const char*)ac, 2u);
    } else {                                                                            // Skipping mode or trim mode? => We cannot trim this command so handling is the same for both modes
      Avail = _GetAvailWriteSpace(pRing);
      if (Avail >= 2) {
        _ActiveTerminal = TerminalId;    // Only change active terminal in case of success
        _WriteNoCheck(pRing, (const char*)ac, 2u);
      } else {
        r = -1;
      }
    }
    SEGGER_RTT_UNLOCK();
  } else {
    r = -1;
  }
  return r;
}

/*********************************************************************
*
*       SEGGER_RTT_TerminalOut
*
*  Function description
*    Writes a string to the given terminal
*     without changing the terminal for channel 0.
*
*  Parameters
*    TerminalId   Index of the terminal.
*    s            String to be printed on the terminal.
*
*  Return value
*    >= 0 - Number of bytes written.
*     < 0 - Error.
*
*/
int SEGGER_RTT_TerminalOut (char TerminalId, const char* s) {
  int                   Status;
  unsigned              FragLen;
  unsigned              Avail;
  SEGGER_RTT_BUFFER_UP* pRing;
  //
  INIT();
  //
  // Validate terminal ID.
  //
  if (TerminalId < (char)sizeof(_aTerminalId)) { // We only support a certain number of channels
    //
    // Get "to-host" ring buffer.
    //
    pRing = &_SEGGER_RTT.aUp[0];
    //
    // Need to be able to change terminal, write data, change back.
    // Compute the fixed and variable sizes.
    //
    FragLen = STRLEN(s);
    //
    // How we output depends upon the mode...
    //
    SEGGER_RTT_LOCK();
    Avail = _GetAvailWriteSpace(pRing);
    switch (pRing->Flags & SEGGER_RTT_MODE_MASK) {
    case SEGGER_RTT_MODE_NO_BLOCK_SKIP:
      //
      // If we are in skip mode and there is no space for the whole
      // of this output, don't bother switching terminals at all.
      //
      if (Avail < (FragLen + 4u)) {
        Status = 0;
      } else {
        _PostTerminalSwitch(pRing, TerminalId);
        Status = (int)_WriteBlocking(pRing, s, FragLen);
        _PostTerminalSwitch(pRing, _ActiveTerminal);
      }
      break;
    case SEGGER_RTT_MODE_NO_BLOCK_TRIM:
      //
      // If we are in trim mode and there is not enough space for everything,
      // trim the output but always include the terminal switch.  If no room
      // for terminal switch, skip that totally.
      //
      if (Avail < 4u) {
        Status = -1;
      } else {
        _PostTerminalSwitch(pRing, TerminalId);
        Status = (int)_WriteBlocking(pRing, s, (FragLen < (Avail - 4u)) ? FragLen : (Avail - 4u));
        _PostTerminalSwitch(pRing, _ActiveTerminal);
      }
      break;
    case SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL:
      //
      // If we are in blocking mode, output everything.
      //
      _PostTerminalSwitch(pRing, TerminalId);
      Status = (int)_WriteBlocking(pRing, s, FragLen);
      _PostTerminalSwitch(pRing, _ActiveTerminal);
      break;
    default:
      Status = -1;
      break;
    }
    //
    // Finish up.
    //
    SEGGER_RTT_UNLOCK();
  } else {
    Status = -1;
  }
  return Status;
}


/*************************** End of file ****************************/
