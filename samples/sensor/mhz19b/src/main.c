/*
 * Copyright (c) 2021 G-Technologies Sdn. Bhd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>
#include <drivers/sensor.h>
#include <drivers/sensor/mhz19b.h>

void main(void)
{
	const struct device *dev;
	struct sensor_value val;
	int ret;

	printk("Winsen MH-Z19B CO2 sensor application\n");

	dev = DEVICE_DT_GET_ONE(winsen_mhz19b);
	if (!device_is_ready(dev)) {
		printk("sensor: device not found.\n");
		return;
	}

	printk("Configuring sensor - ");

	val.val1 = 5000;
	ret = sensor_attr_set(dev, SENSOR_CHAN_CO2, SENSOR_ATTR_FULL_SCALE, &val);
	if (ret != 0) {
		printk("failed to set range to %d\n", val.val1);
		return;
	}

	val.val1 = 1;
	ret = sensor_attr_set(dev, SENSOR_CHAN_CO2, SENSOR_ATTR_MHZ19B_ABC, &val);
	if (ret != 0) {
		printk("failed to set ABC to %d\n", val.val1);
		return;
	}

	printk("OK\n");

	printk("Reading configurations from sensor:\n");

	ret = sensor_attr_get(dev, SENSOR_CHAN_CO2, SENSOR_ATTR_FULL_SCALE, &val);
	if (ret != 0) {
		printk("failed to get range\n");
		return;
	}

	printk("Sensor range is set to %dppm\n", val.val1);

	ret = sensor_attr_get(dev, SENSOR_CHAN_CO2, SENSOR_ATTR_MHZ19B_ABC, &val);
	if (ret != 0) {
		printk("failed to get ABC\n");
		return;
	}

	printk("Sensor ABC is %s\n", val.val1 == 1 ? "enabled" : "disabled");

	while (1) {
		if (sensor_sample_fetch(dev) != 0) {
			printk("sensor: sample fetch fail.\n");
			return;
		}

		if (sensor_channel_get(dev, SENSOR_CHAN_CO2, &val) != 0) {
			printk("sensor: channel get fail.\n");
			return;
		}

		printk("sensor: co2 reading: %d\n", val.val1);

		k_msleep(2000);
	}
}
