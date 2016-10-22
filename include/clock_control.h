/* clock_control.h - public clock controller driver API */

/*
 * Copyright (c) 2015 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __CLOCK_CONTROL_H__
#define __CLOCK_CONTROL_H__

#include <stdint.h>
#include <stddef.h>
#include <device.h>
#include <misc/__assert.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Clock control API */

/* Used to select all subsystem of a clock controller */
#define CLOCK_CONTROL_SUBSYS_ALL	NULL

/**
 * clock_control_subsys_t is a type to identify a clock controller sub-system.
 * Such data pointed is opaque and relevant only to the clock controller
 * driver instance being used.
 */
typedef void *clock_control_subsys_t;

typedef int (*clock_control)(struct device *dev, clock_control_subsys_t sys);

typedef int (*clock_control_get)(struct device *dev,
				 clock_control_subsys_t sys,
				 uint32_t *rate);

struct clock_control_driver_api {
	clock_control		on;
	clock_control		off;
	clock_control_get	get_rate;
};

/**
 * @brief Enable the clock of a sub-system controlled by the device
 * @param dev Pointer to the device structure for the clock controller driver
 * 	instance
 * @param sys A pointer to an opaque data representing the sub-system
 */
static inline int clock_control_on(struct device *dev,
				   clock_control_subsys_t sys)
{
	const struct clock_control_driver_api *api = dev->driver_api;

	return api->on(dev, sys);
}

/**
 * @brief Disable the clock of a sub-system controlled by the device
 * @param dev Pointer to the device structure for the clock controller driver
 * 	instance
 * @param sys A pointer to an opaque data representing the sub-system
 */
static inline int clock_control_off(struct device *dev,
				    clock_control_subsys_t sys)
{
	const struct clock_control_driver_api *api = dev->driver_api;

	return api->off(dev, sys);
}

/**
 * @brief Obtain the clock rate of given sub-system
 * @param dev Pointer to the device structure for the clock controller driver
 *        instance
 * @param sys A pointer to an opaque data representing the sub-system
 * @param[out] rate Subsystem clock rate
 */
static inline int clock_control_get_rate(struct device *dev,
					 clock_control_subsys_t sys,
					 uint32_t *rate)
{
	const struct clock_control_driver_api *api = dev->driver_api;

	__ASSERT(api->get_rate, "%s not implemented for device %s",
		__func__, dev->config->name);

	return api->get_rate(dev, sys, rate);
}

#ifdef __cplusplus
}
#endif

#endif /* __CLOCK_CONTROL_H__ */
