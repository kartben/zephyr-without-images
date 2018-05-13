/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ztest.h>
extern void test_stack_thread2thread(void);
extern void test_stack_thread2isr(void);
extern void test_stack_pop_fail(void);
#ifdef CONFIG_USERSPACE
extern void test_stack_user_thread2thread(void);
extern void test_stack_user_pop_fail(void);

K_MEM_POOL_DEFINE(test_pool, 128, 128, 2, 4);
#else
#define dummy_test(_name) \
	static void _name(void) \
	{ \
		ztest_test_skip(); \
	}

dummy_test(test_stack_user_thread2thread);
dummy_test(test_stack_user_pop_fail);
#endif /* CONFIG_USERSPACE */

extern struct k_stack kstack;
extern struct k_stack stack;
extern struct k_thread thread_data;
extern struct k_sem end_sema;
K_THREAD_STACK_EXTERN(threadstack);

/*test case main entry*/
void test_main(void)
{
	k_thread_access_grant(k_current_get(), &kstack, &stack, &thread_data,
			      &end_sema, &threadstack, NULL);

#ifdef CONFIG_USERSPACE
	k_thread_resource_pool_assign(k_current_get(), &test_pool);
#endif

	ztest_test_suite(stack_api,
			 ztest_unit_test(test_stack_thread2thread),
			 ztest_user_unit_test(test_stack_user_thread2thread),
			 ztest_unit_test(test_stack_thread2isr),
			 ztest_unit_test(test_stack_pop_fail),
			 ztest_user_unit_test(test_stack_user_pop_fail));
	ztest_run_test_suite(stack_api);
}
