/* micro_task_switch_yield.c - measure task context switch time using yield */

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
 * DESCRIPTION
 * This file contains the benchmark that measure the average time it takes to
 * do context switches between microkernel tasks using task_yield () to force
 * context switch.
 */

#ifdef CONFIG_MICROKERNEL
#include <zephyr.h>
#include "timestamp.h"  /* reading time */
#include "utils.h"      /* PRINT () and other macros */

/* <stdlib.h> is not supported */
static int abs(int i) { return (i >= 0) ? i : -i; }

/* context switch enough time so our measurement is precise */
#define NB_OF_YIELD     1000

static uint32_t helper_task_iterations = 0;

/**
 *
 * yieldingTask - helper task for measuring task switch latency using yield
 *
 * This task is define in .mdef as SEMYIELDTSK
 *
 * RETURNS: N/A
 *
 * \NOMANUAL
 */

void yieldingTask(void)
{
	while (helper_task_iterations < NB_OF_YIELD) {
		task_yield();
		helper_task_iterations++;
	}
}

/**
 *
 * microTaskSwitchYield - entry point for task context switch using yield test
 *
 * RETURNS: N/A
 *
 * \NOMANUAL
 */

void microTaskSwitchYield(void)
{
	uint32_t iterations = 0;
	int32_t  delta;
	uint32_t timestamp;

	PRINT_FORMAT(" 5- Measure average context switch time between tasks using"
				 " (task_yield)");

	bench_test_start();

	/* launch helper task of the same priority than this routine */
	task_start(YIELDTASK);

	/* get initial timestamp */
	timestamp = TIME_STAMP_DELTA_GET(0);

	/* loop until either helper or this routine reaches number of yields */
	while (iterations < NB_OF_YIELD && helper_task_iterations < NB_OF_YIELD) {
		task_yield();
		iterations++;
	}

	/* get the number of cycles it took to do the test */
	timestamp = TIME_STAMP_DELTA_GET(timestamp);

	/* Ensure both helper and this routine were context switching back & forth.
	 * For execution to reach the line below, either this routine or helper
	 * routine reached NB_OF_YIELD. The other loop must be at most one
	 * iteration away from reaching NB_OF_YIELD if execute was switching back
	 * and forth.
	 */
	delta = iterations - helper_task_iterations;
	if (bench_test_end() < 0) {
		errorCount++;
		PRINT_OVERFLOW_ERROR();
	} else if (abs(delta) > 1) {
		/* expecting even alternating context switch, seems one routine
		 * called yield without the other having chance to execute
		 */
		errorCount++;
		PRINT_FORMAT(" Error, iteration:%lu, helper iteration:%lu",
					 iterations, helper_task_iterations);
	} else {
		/* task_yield is called (iterations + helper_task_iterations)
		 * times in total.
		 */
		PRINT_FORMAT(" Average task context switch using "
					 "yield %lu tcs = %lu nsec",
					 timestamp / (iterations + helper_task_iterations),
					 SYS_CLOCK_HW_CYCLES_TO_NS_AVG(timestamp,
					 (iterations + helper_task_iterations)));
	}
}

#endif
