/*
 * Copyright (c) 2018 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Public LED driver APIs
 */

#ifndef ZEPHYR_INCLUDE_DRIVERS_LED_H_
#define ZEPHYR_INCLUDE_DRIVERS_LED_H_

/**
 * @brief LED Interface
 * @defgroup led_interface LED Interface
 * @ingroup io_interfaces
 * @{
 */

#include <zephyr/types.h>
#include <device.h>

/**
 * @brief LED information structure
 *
 * This structure gathers useful information about LED controller.
 *
 * @param label LED label.
 * @param num_colors Number of colors per LED.
 * @param index Index of the LED on the controller.
 * @param color_mapping Mapping of the LED colors.
 */
struct led_info {
	const char *label;
	uint32_t index;
	uint8_t num_colors;
	const uint8_t *color_mapping;
};

/**
 * @typedef led_api_blink()
 * @brief Callback API for blinking an LED
 *
 * @see led_blink() for argument descriptions.
 */
typedef int (*led_api_blink)(struct device *dev, uint32_t led,
			     uint32_t delay_on, uint32_t delay_off);

/**
 * @typedef led_api_get_info()
 * @brief Optional API callback to get LED information
 *
 * @see led_get_info() for argument descriptions.
 */
typedef int (*led_api_get_info)(struct device *dev, uint32_t led,
				const struct led_info **info);

/**
 * @typedef led_api_set_brightness()
 * @brief Callback API for setting brightness of an LED
 *
 * @see led_set_brightness() for argument descriptions.
 */
typedef int (*led_api_set_brightness)(struct device *dev, uint32_t led,
				      uint8_t value);
/**
 * @typedef led_api_set_color()
 * @brief Optional API callback to set the colors of a LED.
 *
 * @see led_set_color() for argument descriptions.
 */
typedef int (*led_api_set_color)(struct device *dev, uint32_t led,
				 uint8_t num_colors, const uint8_t *color);

/**
 * @typedef led_api_on()
 * @brief Callback API for turning on an LED
 *
 * @see led_on() for argument descriptions.
 */
typedef int (*led_api_on)(struct device *dev, uint32_t led);

/**
 * @typedef led_api_off()
 * @brief Callback API for turning off an LED
 *
 * @see led_off() for argument descriptions.
 */
typedef int (*led_api_off)(struct device *dev, uint32_t led);

/**
 * @brief LED driver API
 */
__subsystem struct led_driver_api {
	/* Mandatory callbacks. */
	led_api_blink blink;
	led_api_set_brightness set_brightness;
	led_api_on on;
	led_api_off off;
	/* Optional callbacks. */
	led_api_get_info get_info;
	led_api_set_color set_color;
};

/**
 * @brief Blink an LED
 *
 * This routine starts blinking an LED forever with the given time period
 *
 * @param dev LED device
 * @param led LED number
 * @param delay_on Time period (in milliseconds) an LED should be ON
 * @param delay_off Time period (in milliseconds) an LED should be OFF
 * @return 0 on success, negative on error
 */
__syscall int led_blink(struct device *dev, uint32_t led,
			    uint32_t delay_on, uint32_t delay_off);

static inline int z_impl_led_blink(struct device *dev, uint32_t led,
			    uint32_t delay_on, uint32_t delay_off)
{
	const struct led_driver_api *api =
		(const struct led_driver_api *)dev->api;

	return api->blink(dev, led, delay_on, delay_off);
}

/**
 * @brief Get LED information
 *
 * This optional routine provides information about a LED.
 *
 * @param dev LED device
 * @param led LED number
 * @param info Pointer to a pointer filled with LED information
 * @return 0 on success, negative on error
 */
__syscall int led_get_info(struct device *dev, uint32_t led,
			   const struct led_info **info);

static inline int z_impl_led_get_info(struct device *dev, uint32_t led,
				      const struct led_info **info)
{
	const struct led_driver_api *api =
		(const struct led_driver_api *)dev->api;

	if (!api->get_info) {
		*info = NULL;
		return -ENOTSUP;
	}
	return api->get_info(dev, led, info);
}

/**
 * @brief Set LED brightness
 *
 * This routine sets the brightness of a LED to the given value.
 * Calling this function after led_blink() won't affect blinking.
 *
 * @param dev LED device
 * @param led LED number
 * @param value Brightness value to set in percent
 * @return 0 on success, negative on error
 */
__syscall int led_set_brightness(struct device *dev, uint32_t led,
				     uint8_t value);

static inline int z_impl_led_set_brightness(struct device *dev, uint32_t led,
				     uint8_t value)
{
	const struct led_driver_api *api =
		(const struct led_driver_api *)dev->api;

	return api->set_brightness(dev, led, value);
}

/**
 * @brief Set LED color
 *
 * This routine configures all the color channels of a LED with the given
 * color array.
 *
 * Calling this function after led_blink() won't affect blinking.
 *
 * @param dev LED device
 * @param led LED number
 * @param num_colors Number of colors in the array.
 * @param color Array of colors. It must be ordered following the color
 *        mapping of the LED controller. See the the color_mapping member
 *        in struct led_info.
 * @return 0 on success, negative on error
 */
__syscall int led_set_color(struct device *dev, uint32_t led,
			    uint8_t num_colors, const uint8_t *color);

static inline int z_impl_led_set_color(struct device *dev, uint32_t led,
				       uint8_t num_colors, const uint8_t *color)
{
	const struct led_driver_api *api =
		(const struct led_driver_api *)dev->api;

	if (!api->set_color) {
		return -ENOTSUP;
	}
	return api->set_color(dev, led, num_colors, color);
}

/**
 * @brief Turn on an LED
 *
 * This routine turns on an LED
 *
 * @param dev LED device
 * @param led LED number
 * @return 0 on success, negative on error
 */
__syscall int led_on(struct device *dev, uint32_t led);

static inline int z_impl_led_on(struct device *dev, uint32_t led)
{
	const struct led_driver_api *api =
		(const struct led_driver_api *)dev->api;

	return api->on(dev, led);
}

/**
 * @brief Turn off an LED
 *
 * This routine turns off an LED
 *
 * @param dev LED device
 * @param led LED number
 * @return 0 on success, negative on error
 */
__syscall int led_off(struct device *dev, uint32_t led);

static inline int z_impl_led_off(struct device *dev, uint32_t led)
{
	const struct led_driver_api *api =
		(const struct led_driver_api *)dev->api;

	return api->off(dev, led);
}

/**
 * @}
 */

#include <syscalls/led.h>

#endif	/* ZEPHYR_INCLUDE_DRIVERS_LED_H_ */
