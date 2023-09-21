/*
 * Copyright (c) 2023 Alvaro Garcia Gomez <maxpowel@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/fuel_gauge.h>



int main(void)
{
	const struct device *const dev = DEVICE_DT_GET_ANY(maxim_max17048);
	int ret = 0;

	if (dev == NULL) {
		printk("\nError: no device found.\n");
		return 0;
	}

	if (!device_is_ready(dev)) {
		printk("\nError: Device \"%s\" is not ready; "
		       "check the driver initialization logs for errors.\n",
		       dev->name);
		return 0;
	}



	printk("Found device \"%s\", getting fuel gauge data\n", dev->name);

	if (dev == NULL) {
		return 0;
	}

	while (1) {

		struct fuel_gauge_property props[] = {
			{
				.property_type = FUEL_GAUGE_RUNTIME_TO_EMPTY,
			},
			{
				.property_type = FUEL_GAUGE_RUNTIME_TO_FULL,
			},
			{
				.property_type = FUEL_GAUGE_RELATIVE_STATE_OF_CHARGE,
			},
			{
				.property_type = FUEL_GAUGE_VOLTAGE,
			}};

		ret = fuel_gauge_get_props(dev, props, ARRAY_SIZE(props));
		if (ret < 0) {
			printk("Error: cannot get properties\n");
		} else {
			printk("Time to empty %d\n", props[0].value.runtime_to_empty);

			printk("Time to full %d\n", props[1].value.runtime_to_full);

			printk("Charge %d%%\n", props[2].value.relative_state_of_charge);

			printk("Voltage %d\n", props[3].value.voltage);
		}

		k_sleep(K_MSEC(5000));
	}
	return 0;
}
