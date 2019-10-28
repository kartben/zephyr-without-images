/*
 * Copyright (c) 2015 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file Header file for the PCAL9535A driver.
 */

#ifndef ZEPHYR_DRIVERS_GPIO_GPIO_PCAL9535A_H_
#define ZEPHYR_DRIVERS_GPIO_GPIO_PCAL9535A_H_

#include <kernel.h>

#include <drivers/gpio.h>
#include <drivers/i2c.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Configuration data */
struct gpio_pcal9535a_config {
	/** The master I2C device's name */
	const char * const i2c_master_dev_name;

	/** The slave address of the chip */
	u16_t i2c_slave_addr;
};

/** Store the port 0/1 data for each register pair. */
union gpio_pcal9535a_port_data {
	u16_t all;
	u8_t port[2];
	u8_t byte[2];
};

/** Runtime driver data */
struct gpio_pcal9535a_drv_data {
	/* gpio_driver_data needs to be first */
	struct gpio_driver_data common;

	/** Master I2C device */
	struct device *i2c_master;

	struct {
		union gpio_pcal9535a_port_data output;
		union gpio_pcal9535a_port_data dir;
		union gpio_pcal9535a_port_data pud_en;
		union gpio_pcal9535a_port_data pud_sel;
	} reg_cache;
};

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_DRIVERS_GPIO_GPIO_PCAL9535A_H_ */
