/*
 * Copyright (c) 2016 Linaro Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/zephyr.h>
#include <errno.h>
#include <tc_util.h>
#include <ztest.h>
/**
 * @addtogroup kernel_common_tests
 * @{
 */

/**
 * @brief Test if correct multilib is selected
 *
 */
ZTEST(multilib, test_multilib)
{
	volatile long long a = 100;
	volatile long long b = 3;
	volatile long long c = a / b;

	zassert_equal(c, 33, "smoke-test failed: wrong multilib selected");
}

/**
 * @}
 */
