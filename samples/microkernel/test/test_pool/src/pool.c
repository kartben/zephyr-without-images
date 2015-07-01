/* pool.c - test microkernel memory pool APIs */

/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
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

/*
DESCRIPTION
This modules tests the following memory pool routines:

  task_mem_pool_alloc(), task_mem_pool_alloc_wait(), task_mem_pool_alloc_wait_timeout(),
  task_mem_pool_free()
 */

#include <tc_util.h>
#include <nanokernel.h>
#include <arch/cpu.h>
#include <zephyr.h>
#include <misc/util.h>

#define  ONE_SECOND     (sys_clock_ticks_per_sec)
#define  TENTH_SECOND   (sys_clock_ticks_per_sec / 10)

#define  NUM_BLOCKS     64

#define  DEFRAG_BLK_TEST 2222

typedef struct {
	struct k_block *block;    /* pointer to block data */
	kmemory_pool_t  poolId;   /* pool ID */
	int       size;     /* request size in bytes */
	int32_t   timeout;  /* # of ticks to wait */
	int       rcode;    /* expected return code */
} TEST_CASE;

typedef int (*poolBlockGetFunc_t)(struct k_block *, kmemory_pool_t, int, int32_t);
typedef int (*poolMoveBlockFunc_t)(struct k_block *, kmemory_pool_t);

static volatile int evidence = 0;

static struct k_block  blockList[NUM_BLOCKS];
static struct k_block  helperBlock;

static TEST_CASE getSet[] = {
	{&blockList[0], POOL_ID, 0, 0, RC_OK},
	{&blockList[1], POOL_ID, 1, 0, RC_OK},
	{&blockList[2], POOL_ID, 32, 0, RC_OK},
	{&blockList[3], POOL_ID, 64, 0, RC_OK},
	{&blockList[4], POOL_ID, 128, 0, RC_OK},
	{&blockList[5], POOL_ID, 256, 0, RC_OK},
	{&blockList[6], POOL_ID, 512, 0, RC_OK},
	{&blockList[7], POOL_ID, 1024, 0, RC_OK},
	{&blockList[8], POOL_ID, 2048, 0, RC_FAIL},
	{&blockList[9], POOL_ID, 4096, 0, RC_FAIL}
};

static TEST_CASE getSet2[] = {
	{&blockList[0], POOL_ID, 4096, 0, RC_OK},
	{&blockList[1], POOL_ID, 2048, 0, RC_FAIL},
	{&blockList[2], POOL_ID, 1024, 0, RC_FAIL},
	{&blockList[3], POOL_ID, 512, 0, RC_FAIL},
	{&blockList[4], POOL_ID, 256, 0, RC_FAIL}
};

static TEST_CASE getwtSet[] = {
	{&blockList[0], POOL_ID, 4096, TENTH_SECOND, RC_OK},
	{&blockList[1], POOL_ID, 2048, TENTH_SECOND, RC_TIME},
	{&blockList[2], POOL_ID, 1024, TENTH_SECOND, RC_TIME},
	{&blockList[3], POOL_ID, 512, TENTH_SECOND, RC_TIME},
	{&blockList[4], POOL_ID, 256, TENTH_SECOND, RC_TIME}
};

static TEST_CASE defrag[] = {
	{&blockList[0], POOL_ID, 64, 0, RC_OK},
	{&blockList[1], POOL_ID, 64, 0, RC_OK},
	{&blockList[2], POOL_ID, 64, 0, RC_OK},
	{&blockList[3], POOL_ID, 64, 0, RC_OK},
	{&blockList[4], POOL_ID, 256, 0, RC_OK},
	{&blockList[5], POOL_ID, 256, 0, RC_OK},
	{&blockList[6], POOL_ID, 256, 0, RC_OK},
	{&blockList[7], POOL_ID, 1024, 0, RC_OK},
	{&blockList[8], POOL_ID, 1024, 0, RC_OK},
	{&blockList[9], POOL_ID, 1024, 0, RC_OK}
};

/**
 *
 * blockCompare - compare the two blocks
 *
 * RETURNS: 0 if the same, non-zero if not the same
 */

int blockCompare(struct k_block *b1, struct k_block *b2)
{
	char *p1 = (char *) b1;
	char *p2 = (char *) b2;
	int  i;
	int  diff;

	for (i = 0; i < sizeof(struct k_block); i++) {
		diff = p2[i] - p1[i];
		if (diff != 0) {
			break;
		}
	}

	return diff;
}

/**
 *
 * poolBlockGetFunc - wrapper for task_mem_pool_alloc()
 *
 * RETURNS: task_mem_pool_alloc() return value
 */

int poolBlockGetFunc(struct k_block *block, kmemory_pool_t pool, int size,
					 int32_t unused)
{
	ARG_UNUSED(unused);

	return task_mem_pool_alloc(block, pool, size);
}

/**
 *
 * poolBlockGetWFunc - wrapper for task_mem_pool_alloc_wait()
 *
 * RETURNS: task_mem_pool_alloc_wait() return value
 */

int poolBlockGetWFunc(struct k_block *block, kmemory_pool_t pool, int size,
					  int32_t unused)
{
	ARG_UNUSED(unused);

	return task_mem_pool_alloc_wait(block, pool, size);
}

/**
 *
 * poolBlockGetWTFunc - wrapper for task_mem_pool_alloc_wait_timeout()
 *
 * RETURNS: task_mem_pool_alloc_wait_timeout() return value
 */

int poolBlockGetWTFunc(struct k_block *block, kmemory_pool_t pool,
					   int size, int32_t timeout)
{
	return task_mem_pool_alloc_wait_timeout(block, pool, size, timeout);
}

/**
 *
 * freeBlocks - free any blocks allocated in the test set
 *
 * RETURNS: N/A
 */

void freeBlocks(TEST_CASE *tests, int nTests)
{
	int  i;

	for (i = 0; i < nTests; i++) {
		if (tests[i].rcode == RC_OK) {
			task_mem_pool_free(tests[i].block);
		}
	}
}

/**
 *
 * poolBlockGetWork - perform the work of getting blocks
 *
 * RETURNS: TC_PASS on success, TC_FAIL on failure
 */

int poolBlockGetWork(char *string, poolBlockGetFunc_t func,
					 TEST_CASE *tests, int nTests)
{
	int  i;
	int  rv;

	for (i = 0; i < nTests; i++) {
		rv = func(tests[i].block, tests[i].poolId, tests[i].size,
				  tests[i].timeout);
		if (rv != tests[i].rcode) {
			TC_ERROR("%s() expected %d, got %d\n"
					 "size: %d, timeout: %d\n", string, tests[i].rcode, rv,
					 tests[i].size, tests[i].timeout);
			return TC_FAIL;
		}
	}

	return TC_PASS;
}

/**
 *
 * poolBlockGetTest - test the task_mem_pool_alloc() API
 *
 * The pool is 4 kB in size.
 *
 * RETURNS: TC_PASS on success, TC_FAIL on failure
 */

int poolBlockGetTest(void)
{
	int  rv;   /* return value from task_mem_pool_alloc() */
	int  j;    /* loop counter */

	for (j = 0; j < 8; j++) {
		rv = poolBlockGetWork("task_mem_pool_alloc", poolBlockGetFunc,
							  getSet, ARRAY_SIZE(getSet));
		if (rv != TC_PASS) {
			return TC_FAIL;
		}

		freeBlocks(getSet, ARRAY_SIZE(getSet));

		rv = poolBlockGetWork("task_mem_pool_alloc", poolBlockGetFunc,
							  getSet2, ARRAY_SIZE(getSet2));
		if (rv != TC_PASS) {
			return TC_FAIL;
		}

		freeBlocks(getSet2, ARRAY_SIZE(getSet2));
	}

	return TC_PASS;
}

/**
 *
 * HelperTask - helper task to poolBlockGetTimeoutTest()
 *
 * RETURNS: N/A
 */

void HelperTask(void)
{
	task_sem_take_wait(HELPER_SEM);

	task_sem_give(REGRESS_SEM);
	task_mem_pool_free(&helperBlock);
}

/**
 *
 * poolBlockGetTimeoutTest - test task_mem_pool_alloc_wait_timeout()
 *
 * RETURNS: TC_PASS on success, TC_FAIL on failure
 */

int poolBlockGetTimeoutTest(void)
{
	struct k_block  block;
	int  rv;   /* return value from task_mem_pool_alloc_wait_timeout() */
	int  j;    /* loop counter */

	for (j = 0; j < 8; j++) {
		rv = poolBlockGetWork("task_mem_pool_alloc_wait_timeout", poolBlockGetWTFunc,
							  getwtSet, ARRAY_SIZE(getwtSet));
		if (rv != TC_PASS) {
			return TC_FAIL;
		}

		freeBlocks(getwtSet, ARRAY_SIZE(getwtSet));
	}

	rv = task_mem_pool_alloc_wait_timeout(&helperBlock, POOL_ID, 3148, 5);
	if (rv != RC_OK) {
		TC_ERROR("Failed to get size 3148 byte block from POOL_ID\n");
		return TC_FAIL;
	}

	rv = task_mem_pool_alloc(&block, POOL_ID, 3148);
	if (rv != RC_FAIL) {
		TC_ERROR("Unexpectedly got size 3148 byte block from POOL_ID\n");
		return TC_FAIL;
	}

	task_sem_give(HELPER_SEM);    /* Activate HelperTask */
	rv = task_mem_pool_alloc_wait_timeout(&block, POOL_ID, 3148, 20);
	if (rv != RC_OK) {
		TC_ERROR("Failed to get size 3148 byte block from POOL_ID\n");
		return TC_FAIL;
	}

	rv = task_sem_take(REGRESS_SEM);
	if (rv != RC_OK) {
		TC_ERROR("Failed to get size 3148 byte block within 20 ticks\n");
		return TC_FAIL;
	}

	task_mem_pool_free(&block);

	return TC_PASS;
}

/**
 *
 * poolBlockGetWaitTest -
 *
 * RETURNS: TC_PASS on success, TC_FAIL on failure
 */

int poolBlockGetWaitTest(void)
{
	int  rv;

	rv = task_mem_pool_alloc_wait(&blockList[0], POOL_ID, 3000);
	if (rv != RC_OK) {
		TC_ERROR("task_mem_pool_alloc_wait(3000) expected %d, got %d\n", RC_OK, rv);
		return TC_FAIL;
	}

	task_sem_give(ALTERNATE_SEM);    /* Wake AlternateTask */
	evidence = 0;
	rv = task_mem_pool_alloc_wait(&blockList[1], POOL_ID, 128);
	if (rv != RC_OK) {
		TC_ERROR("task_mem_pool_alloc_wait (128) expected %d, got %d\n", RC_OK, rv);
		return TC_FAIL;
	}

	switch (evidence) {
	case 0:
		TC_ERROR("task_mem_pool_alloc_wait(128) did not block!\n");
		return TC_FAIL;
	case 1:
		break;
	case 2:
	default:
		TC_ERROR("Rescheduling did not occur after task_mem_pool_free()\n");
		return TC_FAIL;
	}

	task_mem_pool_free(&blockList[1]);

	return TC_PASS;
}

/**
 *
 * DefragTask - task responsible for defragmenting the pool POOL_ID
 *
 * RETURNS: N/A
 */

void DefragTask(void)
{
	task_sem_take_wait(DEFRAG_SEM);     /* Wait to be activated */

	task_mem_pool_defragment(POOL_ID);

	task_sem_give(REGRESS_SEM);   /* DefragTask is finished */
}

/**
 *
 * poolDefragTest -
 *
 * RETURNS: TC_PASS on success, TC_FAIL on failure
 */

int poolDefragTest(void)
{
	int      rv;
	struct k_block  newBlock;

	/* Get a bunch of blocks */

	rv = poolBlockGetWork("task_mem_pool_alloc", poolBlockGetFunc,
						  defrag, ARRAY_SIZE(defrag));
	if (rv != TC_PASS) {
		return TC_FAIL;
	}


	task_sem_give(DEFRAG_SEM);    /* Activate DefragTask */

	/*
	 * Block on getting another block from the pool.
	 * This will allow DefragTask to execute so that we can get some
	 * better code coverage.  50 ticks is expected to more than sufficient
	 * time for DefragTask to finish.
	 */

	rv = task_mem_pool_alloc_wait_timeout(&newBlock, POOL_ID, DEFRAG_BLK_TEST, 50);
	if (rv != RC_TIME) {
		TC_ERROR("task_mem_pool_alloc_wait_timeout() returned %d, not %d\n", rv, RC_TIME);
		return TC_FAIL;
	}

	rv = task_sem_take(REGRESS_SEM);
	if (rv != RC_OK) {
		TC_ERROR("DefragTask did not finish in allotted time!\n");
		return TC_FAIL;
	}

	/* Free the allocated blocks */

	freeBlocks(defrag, ARRAY_SIZE(defrag));

	return TC_PASS;
}

/**
 *
 * AlternateTask - alternate task in the test suite
 *
 * This routine runs at a lower priority than RegressionTask().
 *
 * RETURNS: N/A
 */

void AlternateTask(void)
{
	task_sem_take_wait(ALTERNATE_SEM);

	evidence = 1;

	task_mem_pool_free(&blockList[0]);

	evidence = 2;
}

/**
 *
 * RegressionTask - main task in the test suite
 *
 * This is the entry point to the memory pool test suite.
 *
 * RETURNS: N/A
 */

void RegressionTask(void)
{
	int  tcRC;    /* test case return code */

	TC_START("Test Microkernel Memory Pools");

	TC_PRINT("Testing task_mem_pool_alloc() ...\n");
	tcRC = poolBlockGetTest();
	if (tcRC != TC_PASS) {
		goto doneTests;
	}

	TC_PRINT("Testing task_mem_pool_alloc_wait_timeout() ...\n");
	tcRC = poolBlockGetTimeoutTest();
	if (tcRC != TC_PASS) {
		goto doneTests;
	}

	TC_PRINT("Testing task_mem_pool_alloc_wait() ...\n");
	tcRC = poolBlockGetWaitTest();
	if (tcRC != TC_PASS) {
		goto doneTests;
	}

	TC_PRINT("Testing task_mem_pool_defragment() ...\n");
	tcRC = poolDefragTest();
	if (tcRC != TC_PASS) {
		goto doneTests;
	}

doneTests:
	TC_END_RESULT(tcRC);
	TC_END_REPORT(tcRC);
}
