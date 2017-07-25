/*
 * Copyright (c) 2015 Wind River Systems, Inc.
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ztest.h>
#include <zephyr.h>
#include <errno.h>
#include <tc_util.h>

#define N_THREADS 2

#define STACK_SIZE 384
static K_THREAD_STACK_ARRAY_DEFINE(stacks, N_THREADS, STACK_SIZE);
static struct k_thread threads[N_THREADS];

static int errno_values[N_THREADS + 1] = {
	0xbabef00d,
	0xdeadbeef,
	0xabad1dea,
};

struct result {
	void *q;
	int pass;
};

struct result result[N_THREADS];

struct k_fifo fifo;

static void errno_fiber(int n, int my_errno)
{
	errno = my_errno;

	k_sleep(30 - (n * 10));
	if (errno == my_errno) {
		result[n].pass = 1;
	}

	zassert_equal(errno, my_errno, NULL);

	k_fifo_put(&fifo, &result[n]);
}

void test_thread_context(void)
{
	int rv = TC_PASS, test_errno;

	k_fifo_init(&fifo);

	errno = errno_values[N_THREADS];
	test_errno = errno;

	for (int ii = 0; ii < N_THREADS; ii++) {
		result[ii].pass = TC_FAIL;
	}

	/**TESTPOINT: thread- threads stacks are separate */
	for (int ii = 0; ii < N_THREADS; ii++) {
		k_thread_create(&threads[ii], stacks[ii], STACK_SIZE,
				(k_thread_entry_t) errno_fiber,
				(void *) ii, (void *) errno_values[ii], NULL,
				K_PRIO_PREEMPT(ii + 5), 0, K_NO_WAIT);
	}

	for (int ii = 0; ii < N_THREADS; ii++) {
		struct result *p = k_fifo_get(&fifo, 100);

		if (!p || !p->pass) {
			rv = TC_FAIL;
		}
	}

	zassert_equal(errno, test_errno, NULL);

	if (errno != errno_values[N_THREADS]) {
		rv = TC_FAIL;
	}
}
