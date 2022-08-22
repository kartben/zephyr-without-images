/*
 * Copyright (c) 2022 Caspar Friedrich <c.s.w.friedrich@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/w1.h>
#include <zephyr/logging/log.h>
#include <zephyr/zephyr.h>

LOG_MODULE_REGISTER(main, CONFIG_LOG_DEFAULT_LEVEL);

void w1_search_callback(struct w1_rom rom, void *user_data)
{
	printk("Device found; family: 0x%02x, serial: 0x%016llx\n", rom.family,
	       w1_rom_to_uint64(&rom));
}

void main(void)
{
	const struct device *const dev = DEVICE_DT_GET(DT_NODELABEL(w1));

	if (!device_is_ready(dev)) {
		LOG_ERR("Device not ready");
		return;
	}

	int num_devices = w1_search_rom(dev, w1_search_callback, NULL);

	printk("Number of devices found on bus: %d\n", num_devices);
}
