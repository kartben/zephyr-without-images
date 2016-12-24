/*
 * Copyright (c) 2016 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @addtogroup t_threads_lifecycle
 * @{
 * @defgroup t_threads_cancel_abort test_threads_cancel_abort
 * @}
 */
#include <ztest.h>

#define STACK_SIZE 256
static char __noinit __stack tstack[STACK_SIZE];
static int execute_flag;

static void thread_entry(void *p1, void *p2, void *p3)
{
	execute_flag = 1;
	k_sleep(100);
	execute_flag = 2;
}

static void thread_entry_abort(void *p1, void *p2, void *p3)
{
	/**TESTPOINT: abort current thread*/
	execute_flag = 1;
	k_thread_abort(k_current_get());
	/*unreachable*/
	execute_flag = 2;
	assert_true(1 == 0, NULL);
}

/*test cases*/
void test_threads_cancel_undelayed(void)
{
	int cur_prio = k_thread_priority_get(k_current_get());

	/* spawn thread with lower priority */
	int spawn_prio = cur_prio + 1;

	k_tid_t tid = k_thread_spawn(tstack, STACK_SIZE,
				     thread_entry, NULL, NULL, NULL,
				     spawn_prio, 0, 0);

	/**TESTPOINT: check cancel retcode when thread is not delayed*/
	int cancel_ret = k_thread_cancel(tid);

	assert_equal(cancel_ret, -EINVAL, NULL);
	k_thread_abort(tid);
}

void test_threads_cancel_started(void)
{
	int cur_prio = k_thread_priority_get(k_current_get());

	/* spawn thread with lower priority */
	int spawn_prio = cur_prio + 1;

	k_tid_t tid = k_thread_spawn(tstack, STACK_SIZE,
				     thread_entry, NULL, NULL, NULL,
				     spawn_prio, 0, 0);

	k_sleep(50);
	/**TESTPOINT: check cancel retcode when thread is started*/
	int cancel_ret = k_thread_cancel(tid);

	assert_equal(cancel_ret, -EINVAL, NULL);
	k_thread_abort(tid);
}

void test_threads_cancel_delayed(void)
{
	int cur_prio = k_thread_priority_get(k_current_get());

	/* spawn thread with lower priority */
	int spawn_prio = cur_prio + 1;

	k_tid_t tid = k_thread_spawn(tstack, STACK_SIZE,
				     thread_entry, NULL, NULL, NULL,
				     spawn_prio, 0, 100);

	k_sleep(50);
	/**TESTPOINT: check cancel retcode when thread is started*/
	int cancel_ret = k_thread_cancel(tid);

	assert_equal(cancel_ret, 0, NULL);
	k_thread_abort(tid);
}

void test_threads_abort_self(void)
{
	execute_flag = 0;
	k_tid_t tid = k_thread_spawn(tstack, STACK_SIZE,
				     thread_entry_abort, NULL, NULL, NULL,
				     0, 0, 0);
	k_sleep(100);
	/**TESTPOINT: spawned thread executed but abort itself*/
	assert_true(execute_flag == 1, NULL);
	k_thread_abort(tid);
}

void test_threads_abort_others(void)
{
	execute_flag = 0;
	k_tid_t tid = k_thread_spawn(tstack, STACK_SIZE,
				     thread_entry, NULL, NULL, NULL,
				     0, 0, 0);

	k_thread_abort(tid);
	k_sleep(100);
	/**TESTPOINT: check not-started thread is aborted*/
	assert_true(execute_flag == 0, NULL);

	tid = k_thread_spawn(tstack, STACK_SIZE,
			     thread_entry, NULL, NULL, NULL,
			     0, 0, 0);
	k_sleep(50);
	k_thread_abort(tid);
	/**TESTPOINT: check running thread is aborted*/
	assert_true(execute_flag == 1, NULL);
	k_sleep(1000);
	assert_true(execute_flag == 1, NULL);
}
