/* hello.c - Hello World demo */

/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <stdio.h>
#include "profiler.h"

/*
 * Nanokernel version of hello world demo has a task and a fiber that utilize
 * semaphores and timers to take turns printing a greeting message at
 * a controlled rate.
 */


/* specify delay between greetings (in ms); compute equivalent in ticks */

#define SLEEPTIME  500
#define SLEEPTICKS (SLEEPTIME * sys_clock_ticks_per_sec / 1000)

#define STACKSIZE 2000

char __stack fiberStack[STACKSIZE];

struct nano_sem nanoSemTask;
struct nano_sem nanoSemFiber;

void fiberEntry(void)
{
	while (1) {
		/* wait for task to let us have a turn */
		nano_fiber_sem_take(&nanoSemFiber, TICKS_UNLIMITED);

		/* say "hello" */
		printf("%s: Hello World ! %d\n", __func__, sys_cycle_get_32());
		fiber_sleep(SLEEPTICKS);
		nano_fiber_sem_give(&nanoSemTask);
	}
}

void main(void)
{
	nano_sem_init(&nanoSemFiber);
	nano_sem_init(&nanoSemTask);

	task_fiber_start(&fiberStack[0], STACKSIZE,
			(nano_fiber_entry_t) fiberEntry, 0, 0, 7, 0);

	while (1) {
		/* say "hello" */
		printf("%s: Hello World ! %d\n", __func__, sys_cycle_get_32());

		/* wait a while, then let fiber have a turn */
		task_sleep(SLEEPTICKS);
		nano_task_sem_give(&nanoSemFiber);

		prof_flush();

		/* now wait for fiber to let us have a turn */
		nano_task_sem_take(&nanoSemTask, TICKS_UNLIMITED);
	}
}
