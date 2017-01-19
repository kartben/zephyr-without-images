/* fifo_r.c */

/*
 * Copyright (c) 1997-2010, 2013-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "receiver.h"
#include "master.h"

#ifdef FIFO_BENCH

/* queue transfer speed test */
/**
 *
 * @brief Data receive task
 *
 * @return N/A
 */
void dequtask(void)
{
	int x, i;

	for (i = 0; i < NR_OF_FIFO_RUNS; i++) {
		task_fifo_get(DEMOQX1, &x, TICKS_UNLIMITED);
	}

	for (i = 0; i < NR_OF_FIFO_RUNS; i++) {
		task_fifo_get(DEMOQX4, &x, TICKS_UNLIMITED);
	}
}

#endif /* FIFO_BENCH */
