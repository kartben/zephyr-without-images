/*
 * Copyright (c) 2016 Intel Corporation
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file Sample app to demonstrate PWM-based LED fade
 */

#include <zephyr.h>
#include <sys/printk.h>
#include <device.h>
#include <drivers/pwm.h>

static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led0));

#define NUM_STEPS	50U
#define SLEEP_MSEC	25U

void main(void)
{
	uint32_t pulse_width = 0U;
	uint32_t step = pwm_led0.period / NUM_STEPS;
	uint8_t dir = 1U;
	int ret;

	printk("PWM-based LED fade\n");

	if (!device_is_ready(pwm_led0.dev)) {
		printk("Error: PWM device %s is not ready\n",
		       pwm_led0.dev->name);
		return;
	}

	while (1) {
		ret = pwm_set_pulse_dt(&pwm_led0, pulse_width);
		if (ret) {
			printk("Error %d: failed to set pulse width\n", ret);
			return;
		}

		if (dir) {
			pulse_width += step;
			if (pulse_width >= pwm_led0.period) {
				pulse_width = pwm_led0.period - step;
				dir = 0U;
			}
		} else {
			if (pulse_width >= step) {
				pulse_width -= step;
			} else {
				pulse_width = step;
				dir = 1U;
			}
		}

		k_sleep(K_MSEC(SLEEP_MSEC));
	}
}
