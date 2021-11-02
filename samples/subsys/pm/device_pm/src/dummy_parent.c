/*
 * Copyright (c) 2018 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <pm/device_runtime.h>
#include <sys/printk.h>
#include "dummy_parent.h"

static uint32_t store_value;

static int dummy_transfer(const struct device *dev, uint32_t cmd,
			  uint32_t *val)
{
	printk("transfer()\n");

	if (cmd == DUMMY_PARENT_WR) {
		store_value = *val;
	} else {
		*val = store_value;
	}

	return 0;
}

static int dummy_parent_pm_ctrl(const struct device *dev,
				enum pm_device_action action)
{
	switch (action) {
	case PM_DEVICE_ACTION_RESUME:
		printk("parent resuming..\n");
		break;
	case PM_DEVICE_ACTION_SUSPEND:
		printk("parent suspending..\n");
		break;
	default:
		return -ENOTSUP;
	}

	return 0;
}

static const struct dummy_parent_api funcs = {
	.transfer = dummy_transfer,
};

int dummy_parent_init(const struct device *dev)
{
	pm_device_runtime_enable(dev);
	return 0;
}

DEVICE_DEFINE(dummy_parent, DUMMY_PARENT_NAME, &dummy_parent_init,
		    dummy_parent_pm_ctrl, NULL, NULL, POST_KERNEL,
		    CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &funcs);
