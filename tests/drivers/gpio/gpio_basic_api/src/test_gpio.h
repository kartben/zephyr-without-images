/*
 * Copyright (c) 2015-2016 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __TEST_GPIO_H__
#define __TEST_GPIO_H__

#include <zephyr.h>
#include <drivers/gpio.h>
#include <sys/util.h>
#include <ztest.h>

#if DT_HAS_NODE_STATUS_OKAY(DT_INST(0, test_gpio_basic_api))

/* Execution of the test requires hardware configuration described in
 * devicetree.  See the test,gpio_basic_api binding local to this test
 * for details.
 *
 * If this is not present devices that have gpio-0, gpio-1, or gpio-2
 * aliases are supported for build-only tests.
 */
#define DEV_NAME DT_GPIO_LABEL(DT_INST(0, test_gpio_basic_api), out_gpios)
#define PIN_OUT DT_GPIO_PIN(DT_INST(0, test_gpio_basic_api), out_gpios)
#define PIN_IN DT_GPIO_PIN(DT_INST(0, test_gpio_basic_api), in_gpios)

#elif DT_HAS_NODE_STATUS_OKAY(DT_ALIAS(gpio_0))
#define DEV_NAME DT_LABEL(DT_ALIAS(gpio_0))
#elif DT_HAS_NODE_STATUS_OKAY(DT_ALIAS(gpio_1))
#define DEV_NAME DT_LABEL(DT_ALIAS(gpio_1))
#elif DT_HAS_NODE_STATUS_OKAY(DT_ALIAS(gpio_3))
#define DEV_NAME DT_LABEL(DT_ALIAS(gpio_3))
#else
#error Unsupported board
#endif

#ifndef PIN_OUT
/* For build-only testing use fixed pins. */
#define PIN_OUT 2
#define PIN_IN 3
#endif

#define MAX_INT_CNT 3
struct drv_data {
	struct gpio_callback gpio_cb;
	gpio_flags_t mode;
	int index;
	int aux;
};

void test_gpio_pin_read_write(void);
void test_gpio_callback_add_remove(void);
void test_gpio_callback_self_remove(void);
void test_gpio_callback_enable_disable(void);
void test_gpio_callback_variants(void);

void test_gpio_port(void);

void test_gpio_deprecated(void);

#endif /* __TEST_GPIO_H__ */
