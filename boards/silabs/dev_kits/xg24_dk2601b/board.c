/*
 * Copyright (c) 2021 Sateesh Kotapati
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/init.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(efr32xg24_dk2601b, CONFIG_BOARD_EFR32MG24_LOG_LEVEL);

static int efr32xg24_dk2601b_init(void)
{
	int ret;

	static struct gpio_dt_spec wake_up_gpio_dev =
		GPIO_DT_SPEC_GET(DT_NODELABEL(wake_up_trigger), gpios);


	if (!gpio_is_ready_dt(&wake_up_gpio_dev)) {
		LOG_ERR("Wake-up GPIO device was not found!\n");
		return -ENODEV;
	}
	ret = gpio_pin_configure_dt(&wake_up_gpio_dev, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return ret;
	}

	return 0;
}

/* needs to be done after GPIO driver init */
SYS_INIT(efr32xg24_dk2601b_init, POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEVICE);
