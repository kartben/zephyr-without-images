/*
 * Copyright (c) 2018 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ztest.h>

#define STACK_SIZE (384 + CONFIG_TEST_EXTRA_STACKSIZE)
K_THREAD_STACK_EXTERN(tstack);
extern struct k_thread tdata;
static int thread2_data;

K_SEM_DEFINE(sem_thread2, 0, 1);
K_SEM_DEFINE(sem_thread1, 0, 1);

/**
 *
 * @brief thread2 portion to test setting the priority
 *
 */
void thread2_set_prio_test(void)
{
	/* lower thread2 priority by 5 */
	k_sem_take(&sem_thread2, K_FOREVER);
	thread2_data = k_thread_priority_get(k_current_get());
	k_sem_give(&sem_thread1);

	/* raise thread2 priority by 10 */
	k_sem_take(&sem_thread2, K_FOREVER);
	thread2_data = k_thread_priority_get(k_current_get());
	k_sem_give(&sem_thread1);

	/* restore thread2 priority */
	k_sem_take(&sem_thread2, K_FOREVER);
	thread2_data = k_thread_priority_get(k_current_get());
	k_sem_give(&sem_thread1);
}

/**
 *
 * @brief Test the k_thread_priority_set() API
 *
 */

void test_threads_priority_set(void)
{
	int rv;
	int prio = k_thread_priority_get(k_current_get());

	/* Lower the priority of the current thread (thread1) */
	k_thread_priority_set(k_current_get(), prio + 2);
	rv = k_thread_priority_get(k_current_get());
	zassert_equal(rv, prio + 2,
		      "Expected priority to be changed to %d, not %d\n",
		      prio + 2, rv);

	/* Raise the priority of the current thread (thread1) */
	k_thread_priority_set(k_current_get(), prio - 2);
	rv = k_thread_priority_get(k_current_get());
	zassert_equal(rv, prio - 2,
		      "Expected priority to be changed to %d, not %d\n",
		      prio - 2, rv);

	/* Restore the priority of the current thread (thread1) */
	k_thread_priority_set(k_current_get(), prio);
	rv = k_thread_priority_get(k_current_get());
	zassert_equal(rv, prio,
		      "Expected priority to be changed to %d, not %d\n",
		      prio, rv);

	/* create thread with lower priority */
	int thread2_prio = prio + 1;

	k_tid_t thread2_id = k_thread_create(&tdata, tstack, STACK_SIZE,
					     (k_thread_entry_t)thread2_set_prio_test,
					     NULL, NULL, NULL, thread2_prio, 0, 0);

	/* Lower the priority of thread2 */
	k_thread_priority_set(thread2_id, thread2_prio + 2);
	k_sem_give(&sem_thread2);
	k_sem_take(&sem_thread1, K_FOREVER);
	zassert_equal(thread2_data, thread2_prio + 2,
		      "Expected priority to be changed to %d, not %d\n",
		      thread2_prio + 2, thread2_data);

	/* Raise the priority of thread2 */
	k_thread_priority_set(thread2_id, thread2_prio - 2);
	k_sem_give(&sem_thread2);
	k_sem_take(&sem_thread1, K_FOREVER);
	zassert_equal(thread2_data, thread2_prio - 2,
		      "Expected priority to be changed to %d, not %d\n",
		      thread2_prio - 2, thread2_data);

	/* Restore the priority of thread2 */
	k_thread_priority_set(thread2_id, thread2_prio);
	k_sem_give(&sem_thread2);
	k_sem_take(&sem_thread1, K_FOREVER);
	zassert_equal(thread2_data, thread2_prio,
		      "Expected priority to be changed to %d, not %d\n",
		      thread2_prio, thread2_data);
}
