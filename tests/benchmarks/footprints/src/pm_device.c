/*
 * Copyright (c) 2021 Google, LLC
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Stub driver to measure the footprint impact of power management
 *
 */
#include <device.h>
#include <pm/device.h>
#include <pm/device_runtime.h>

#define DUMMY_PM_DRIVER_NAME	"dummy_pm_driver"
#define DUMMY_DRIVER_NAME	"dummy_driver"

static int dummy_init(const struct device *dev)
{
	return 0;
}

static int dummy_device_pm_ctrl(const struct device *dev,
				enum pm_device_action action)
{
	return 0;
}

/* Define a driver with and without power management enabled */
DEVICE_DEFINE(dummy_pm_driver, DUMMY_PM_DRIVER_NAME, &dummy_init,
		    dummy_device_pm_ctrl, NULL, NULL, APPLICATION,
		    CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, NULL);

DEVICE_DEFINE(dummy_driver, DUMMY_DRIVER_NAME, &dummy_init,
		    NULL, NULL, NULL, APPLICATION,
		    CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, NULL);

void run_pm_device(void)
{
	const struct device *dev;
	enum pm_device_state pm_state;

	/* Get the PM state from a device with PM support */
	dev = device_get_binding(DUMMY_PM_DRIVER_NAME);
	if (pm_device_state_get(dev, &pm_state)) {
		printk("\n PM device get state failed\n");
		return;
	}

	if (pm_device_runtime_get(dev)) {
		printk("\n PM device runtime get failed\n");
		return;
	}

	if (pm_device_runtime_put(dev)) {
		printk("\n PM device runtime put failed\n");
		return;
	}

	/* Get the PM state from a device without PM support */
	dev = device_get_binding(DUMMY_DRIVER_NAME);
	if (pm_device_state_get(dev, &pm_state) != ENOSYS) {
		printk("\n PM device get state did not fail\n");
		return;
	}
}
