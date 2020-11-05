/*
 *  Copyright (c) 2020 Intel Corporation.
 *
 *  SPDX-License-Identifier: Apache-2.0
 */

#include <ztest.h>
extern void test_k_heap_alloc(void);
extern void test_k_heap_alloc_fail(void);
extern void test_k_heap_free(void);

/**
 * @brief k heap api tests
 *
 * @defgroup k_heap api Tests
 *
 * @ingroup all_tests
 * @{
 * @}
 */
/*test case main entry*/
void test_main(void)
{
	ztest_test_suite(k_heap_api,
			 ztest_unit_test(test_k_heap_alloc),
			 ztest_unit_test(test_k_heap_alloc_fail),
			 ztest_unit_test(test_k_heap_free));
	ztest_run_test_suite(k_heap_api);
}
