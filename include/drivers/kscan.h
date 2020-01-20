/*
 * Copyright (c) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Public API for Keyboard scan matrix devices.
 * The scope of this API is simply to report which key event was triggered
 * and users can later decode keys using their desired scan code tables in
 * their application. In addition, typematic rate and delay can easily be
 * implemented using a timer if desired.
 */

#ifndef ZEPHYR_INCLUDE_DRIVERS_KB_SCAN_H_
#define ZEPHYR_INCLUDE_DRIVERS_KB_SCAN_H_

#include <zephyr/types.h>
#include <stddef.h>
#include <device.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief KSCAN APIs
 * @defgroup kscan_interface Keyboard Scan Driver APIs
 * @ingroup io_interfaces
 * @{
 */

/**
 * @brief Keyboard scan callback called when user press/release
 * a key on a matrix keyboard.
 *
 * @param dev   Pointer to the device structure for the driver instance.
 * @param data  Data byte passed pack to the user.
 * @param col	Describes column change.
 * @param row	Describes row change.
 * @param pressed Describes the kind of key event.
 */
typedef void (*kscan_callback_t)(struct device *dev, u32_t row, u32_t column,
				 bool pressed);

/**
 * @cond INTERNAL_HIDDEN
 *
 * Keyboard scan driver API definition and system call entry points.
 *
 * (Internal use only.)
 */
typedef int (*kscan_config_t)(struct device *dev,
			    kscan_callback_t callback);
typedef int (*kscan_disable_callback_t)(struct device *dev);
typedef int (*kscan_enable_callback_t)(struct device *dev);

struct kscan_driver_api {
	kscan_config_t config;
	kscan_disable_callback_t disable_callback;
	kscan_enable_callback_t enable_callback;
};
/**
 * @endcond
 */

/**
 * @brief Configure a Keyboard scan instance.
 *
 * @param dev Pointer to the device structure for the driver instance.
 * @param callback called when keyboard devices reply to to a keyboard
 * event such as key pressed/released.
 *
 * @retval 0 If successful.
 * @retval Negative errno code if failure.
 */
__syscall int kscan_config(struct device *dev,
			     kscan_callback_t callback);

static inline int z_impl_kscan_config(struct device *dev,
					kscan_callback_t callback)
{
	const struct kscan_driver_api *api =
				(struct kscan_driver_api *)dev->driver_api;

	return api->config(dev, callback);
}
/**
 * @brief Enables callback.
 * @param dev Pointer to the device structure for the driver instance.
 *
 * @retval 0 If successful.
 * @retval Negative errno code if failure.
 */
__syscall int kscan_enable_callback(struct device *dev);

static inline int z_impl_kscan_enable_callback(struct device *dev)
{
	const struct kscan_driver_api *api =
			(const struct kscan_driver_api *)dev->driver_api;

	if (api->enable_callback == NULL) {
		return -ENOTSUP;
	}

	return api->enable_callback(dev);
}

/**
 * @brief Disables callback.
 * @param dev Pointer to the device structure for the driver instance.
 *
 * @retval 0 If successful.
 * @retval Negative errno code if failure.
 */
__syscall int kscan_disable_callback(struct device *dev);

static inline int z_impl_kscan_disable_callback(struct device *dev)
{
	const struct kscan_driver_api *api =
			(const struct kscan_driver_api *)dev->driver_api;

	if (api->disable_callback == NULL) {
		return -ENOTSUP;
	}

	return api->disable_callback(dev);
}

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#include <syscalls/kscan.h>

#endif /* ZEPHYR_INCLUDE_DRIVERS_KB_SCAN_H_ */
