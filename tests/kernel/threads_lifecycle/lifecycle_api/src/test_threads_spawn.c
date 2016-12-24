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
 * @defgroup t_threads_spawn test_thread_spawn
 * @brief TestPurpose: verify basic thread spawn relevant apis
 * @}
 */

#include <ztest.h>

#define STACK_SIZE 256
static char __noinit __stack tstack[STACK_SIZE];

static char tp1[8];
static int tp2 = 100;
static struct k_sema *tp3;
static int spawn_prio;

static void thread_entry_params(void *p1, void *p2, void *p3)
{
	/* checkpoint: check parameter 1, 2, 3 */
	assert_equal((char *)p1, tp1, NULL);
	assert_equal((int)p2, tp2, NULL);
	assert_equal((struct k_sema *)p3, tp3, NULL);
}

static void thread_entry_priority(void *p1, void *p2, void *p3)
{
	/* checkpoint: check priority */
	assert_equal(k_thread_priority_get(k_current_get()), spawn_prio, NULL);
}

static void thread_entry_delay(void *p1, void *p2, void *p3)
{
	tp2 = 100;
}

/*test cases*/
void test_threads_spawn_params(void)
{
	k_tid_t tid = k_thread_spawn(tstack, STACK_SIZE,
				     thread_entry_params, (void *)tp1, (void *)tp2, (void *)tp3,
				     0, 0, 0);

	k_sleep(100);
	k_thread_abort(tid);
}

void test_threads_spawn_priority(void)
{
	/* spawn thread with higher priority */
	spawn_prio = k_thread_priority_get(k_current_get()) - 1;
	k_tid_t tid = k_thread_spawn(tstack, STACK_SIZE,
				     thread_entry_priority, NULL, NULL, NULL,
				     spawn_prio, 0, 0);
	k_sleep(100);
	k_thread_abort(tid);
}

void test_threads_spawn_delay(void)
{
	/* spawn thread with higher priority */
	tp2 = 10;
	k_tid_t tid = k_thread_spawn(tstack, STACK_SIZE,
				     thread_entry_delay, NULL, NULL, NULL,
				     0, 0, 120);
	/* 100 < 120 ensure spawn thread not start */
	k_sleep(100);
	/* checkpoint: check spawn thread not execute */
	assert_true(tp2 == 10, NULL);
	/* checkpoint: check spawn thread executed */
	k_sleep(100);
	assert_true(tp2 == 100, NULL);
	k_thread_abort(tid);
}
