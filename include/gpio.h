/*
 * Copyright (c) 2015-2016 Intel Corporation.
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

/**
 * @file
 * @brief Public APIs for GPIO drivers
 */

#ifndef __GPIO_H__
#define __GPIO_H__

#include <misc/__assert.h>
#include <misc/slist.h>

#include <stdint.h>
#include <stddef.h>
#include <device.h>

/**
 * @brief GPIO Driver APIs
 * @defgroup gpio_interface GPIO Driver APIs
 * @ingroup io_interfaces
 * @{
 */
#ifdef __cplusplus
extern "C" {
#endif

/** @cond INTERNAL_HIDDEN */
#define GPIO_ACCESS_BY_PIN 0
#define GPIO_ACCESS_BY_PORT 1
/** @endcond */

/** GPIO pin to be input. */
#define GPIO_DIR_IN		(0 << 0)

/** GPIO pin to be output. */
#define GPIO_DIR_OUT		(1 << 0)

/** For internal use. */
#define GPIO_DIR_MASK		0x1

/** GPIO pin to trigger interrupt. */
#define GPIO_INT		(1 << 1)

/** GPIO pin trigger on level low or falling edge. */
#define GPIO_INT_ACTIVE_LOW	(0 << 2)

/** GPIO pin trigger on level high or rising edge. */
#define GPIO_INT_ACTIVE_HIGH	(1 << 2)

/** GPIO pin trggier to be synchronized to clock pulses. */
#define GPIO_INT_CLOCK_SYNC     (1 << 3)

/** Enable GPIO pin debounce. */
#define GPIO_INT_DEBOUNCE       (1 << 4)

/** Do Level trigger. */
#define GPIO_INT_LEVEL		(0 << 5)

/** Do Edge trigger. */
#define GPIO_INT_EDGE		(1 << 5)

/** Interrupt triggers on both rising and falling edge. */
#define GPIO_INT_DOUBLE_EDGE	(1 << 6)

/*
 * GPIO_POL_* define the polarity of the GPIO (1 bit).
 */

/** For internal use. */
#define GPIO_POL_POS		7

/** GPIO pin polarity is normal. */
#define GPIO_POL_NORMAL		(0 << GPIO_POL_POS)

/** GPIO pin polarity is inverted. */
#define GPIO_POL_INV		(1 << GPIO_POL_POS)

/** For internal use. */
#define GPIO_POL_MASK		(1 << GPIO_POL_POS)

/*
 * GPIO_PUD_* are related to pull-up/pull-down.
 */

/** For internal use. */
#define GPIO_PUD_POS		8

/** GPIO pin to have no pull-up or pull-down. */
#define GPIO_PUD_NORMAL		(0 << GPIO_PUD_POS)

/** Enable GPIO pin pull-up. */
#define GPIO_PUD_PULL_UP	(1 << GPIO_PUD_POS)

/** Enable GPIO pin pull-down. */
#define GPIO_PUD_PULL_DOWN	(2 << GPIO_PUD_POS)

/** For internal use. */
#define GPIO_PUD_MASK		(3 << GPIO_PUD_POS)

/*
 * GPIO_PIN_(EN-/DIS-)ABLE are for pin enable / disable.
 *
 * Individual pins can be enabled or disabled
 * if the controller supports this operation.
 */

/** Enable GPIO pin. */
#define GPIO_PIN_ENABLE		(1 << 10)

/** Disable GPIO pin. */
#define GPIO_PIN_DISABLE	(1 << 11)

/**
 * @brief Define the application callback function signature.
 *
 * @param port Device struct for the GPIO device.
 * @param pin The pin that triggers the callback.
 *
 * Note: This is the former callback signature used to set a unique
 *       callback (API v1.0) through gpio_set_callback(). The new
 *       struct gpio_callback below is now the preferred way.
 */
typedef void (*gpio_callback_t)(struct device *port, uint32_t pin);


struct gpio_callback;

/**
 * @brief Define the application callback handler function signature
 *
 * @param port Device struct for the GPIO device.
 * @param cb Original struct gpio_callback owning this handler
 * @param pins Mask of pins that triggers the callback handler
 *
 * Note: cb pointer can be used to retrieve private data through
 * CONTAINER_OF() if original struct gpio_callback is stored in
 * another private structure.
 */
typedef void (*gpio_callback_handler_t)(struct device *port,
					struct gpio_callback *cb,
					uint32_t pins);

/**
 * @brief GPIO callback structure
 *
 * Used to register a callback in the driver instance callback list.
 * As many callbacks as needed can be added as long as each of them
 * are unique pointers of struct gpio_callback.
 * Beware such structure should not be allocated on stack.
 *
 * Note: To help setting it, see gpio_init_callback() below
 */
struct gpio_callback {
	/** This is meant to be used in the driver and the user should not
	 * mess with it (see drivers/gpio/gpio_utils.h)
	 */
	sys_snode_t node;

	/** Actual callback function being called when relevant. */
	gpio_callback_handler_t handler;

	/** A mask of pins the callback is interested in, if 0 the callback
	 * will never be called. Such pin_mask can be modified whenever
	 * necessary by the owner, and thus will affect the handler being
	 * called or not. The selected pins must be configured to trigger
	 * an interrupt.
	 */
	uint32_t pin_mask;
};

/**
 * @cond INTERNAL_HIDDEN
 *
 * GPIO driver API definition.
 *
 * (Internal use only.)
 */
typedef int (*gpio_config_t)(struct device *port, int access_op,
			     uint32_t pin, int flags);
typedef int (*gpio_write_t)(struct device *port, int access_op,
			    uint32_t pin, uint32_t value);
typedef int (*gpio_read_t)(struct device *port, int access_op,
			   uint32_t pin, uint32_t *value);
typedef int (*gpio_manage_callback_t)(struct device *port,
				      struct gpio_callback *callback,
				      bool set);
typedef int (*gpio_enable_callback_t)(struct device *port,
				      int access_op,
				      uint32_t pin);
typedef int (*gpio_disable_callback_t)(struct device *port,
				       int access_op,
				       uint32_t pin);

struct gpio_driver_api {
	gpio_config_t config;
	gpio_write_t write;
	gpio_read_t read;
	gpio_manage_callback_t manage_callback;
	gpio_enable_callback_t enable_callback;
	gpio_disable_callback_t disable_callback;
};
/**
 * @endcond
 */

/**
 * @brief Configure a single pin.
 * @param port Pointer to device structure for the driver instance.
 * @param pin Pin number to configure.
 * @param flags Flags for pin configuration. IN/OUT, interrupt ...
 */
static inline int gpio_pin_configure(struct device *port, uint8_t pin,
				     int flags)
{
	struct gpio_driver_api *api;

	api = (struct gpio_driver_api *) port->driver_api;
	return api->config(port, GPIO_ACCESS_BY_PIN, pin, flags);
}

/**
 * @brief Write the data value to a single pin.
 * @param port Pointer to the device structure for the driver instance.
 * @param pin Pin number where the data is written.
 * @param value Value set on the pin.
 */
static inline int gpio_pin_write(struct device *port, uint32_t pin,
				 uint32_t value)
{
	struct gpio_driver_api *api;

	api = (struct gpio_driver_api *) port->driver_api;
	return api->write(port, GPIO_ACCESS_BY_PIN, pin, value);
}

/**
 * @brief Read the data value of a single pin.
 * @param port Pointer to the device structure for the driver instance.
 * @param pin Pin number where data is read.
 * @param value Integer pointer to receive the data vales from the pin.
 */
static inline int gpio_pin_read(struct device *port, uint32_t pin,
				uint32_t *value)
{
	struct gpio_driver_api *api;

	api = (struct gpio_driver_api *) port->driver_api;
	return api->read(port, GPIO_ACCESS_BY_PIN, pin, value);
}

/**
 * @brief Former way of setting the application's callback.
 * @param port Pointer to the device structure for the driver instance.
 * @param callback Application's callback (or NULL to unset).
 *
 * Note: This function sets a unique callback for the driver instance,
 *       i.e. another call to this function will overwrite it. This is
 *       the old way of doing things (API v1.0) and should be replaced
 *       by gpio_add_callback() and gpio_remove_callback().
 *       Using this function will not collide with the new ones.
 */
int __deprecated gpio_set_callback(struct device *port,
				   gpio_callback_t callback);

/**
 * @brief Helper to initialize a struct gpio_callback properly
 * @param callback A valid Application's callback structure pointer.
 * @param handler A valid handler function pointer.
 * @param pin_mask A bit mask of relevant pins for the handler
 */
static inline void gpio_init_callback(struct gpio_callback *callback,
				      gpio_callback_handler_t handler,
				      uint32_t pin_mask)
{
	__ASSERT(callback, "Callback pointer should not be NULL");
	__ASSERT(handler, "Callback handler pointer should not be NULL");

	callback->handler = handler;
	callback->pin_mask = pin_mask;
}

/**
 * @brief Add an application callback.
 * @param port Pointer to the device structure for the driver instance.
 * @param callback A valid Application's callback structure pointer.
 *
 * Note: enables to add as many callback as needed on the same port.
 *       This is the preferred way and is replacing gpio_set_callback().
 */
static inline int gpio_add_callback(struct device *port,
				    struct gpio_callback *callback)
{
	struct gpio_driver_api *api;

	__ASSERT(callback, "Callback pointer should not be NULL");

	api = (struct gpio_driver_api *) port->driver_api;
	return api->manage_callback(port, callback, true);
}

/**
 * @brief Remove an application callback.
 * @param port Pointer to the device structure for the driver instance.
 * @param callback A valid application's callback structure pointer.
 *
 * Note: enables to remove as many callacks as added through
 *       gpio_add_callback(). This is the preferred way and it's
 *       replacing gpio_set_callback() with a NULL pointer as a callback.
 */
static inline int gpio_remove_callback(struct device *port,
				       struct gpio_callback *callback)
{
	struct gpio_driver_api *api;

	__ASSERT(callback, "Callback pointer should not be NULL");

	api = (struct gpio_driver_api *) port->driver_api;
	return api->manage_callback(port, callback, false);
}

/**
 * @brief Enable callback(s) for a single pin.
 * @param port Pointer to the device structure for the driver instance.
 * @param pin Pin number where the callback function is enabled.
 *
 * Note: Depending on the driver implementation, this function will enable
 *       the pin to trigger an interruption. So as a semantic detail, if no
 *       callback is registered, of course none will be called.
 */
static inline int gpio_pin_enable_callback(struct device *port, uint32_t pin)
{
	struct gpio_driver_api *api;

	api = (struct gpio_driver_api *) port->driver_api;
	return api->enable_callback(port, GPIO_ACCESS_BY_PIN, pin);
}

/**
 * @brief Disable callback(s) for a single pin.
 * @param port Pointer to the device structure for the driver instance.
 * @param pin Pin number where the callback function is disabled.
 */
static inline int gpio_pin_disable_callback(struct device *port, uint32_t pin)
{
	struct gpio_driver_api *api;

	api = (struct gpio_driver_api *) port->driver_api;
	return api->disable_callback(port, GPIO_ACCESS_BY_PIN, pin);
}

/**
 * @brief Configure all the pins the same way in the port.
 *        List out all flags on the detailed description.
 *
 * @param port Pointer to the device structure for the driver instance.
 * @param flags Flags for the port configuration. IN/OUT, interrupt ...
 */
static inline int gpio_port_configure(struct device *port, int flags)
{
	struct gpio_driver_api *api;

	api = (struct gpio_driver_api *) port->driver_api;
	return api->config(port, GPIO_ACCESS_BY_PORT, 0, flags);
}

/**
 * @brief Write a data value to the port.
 * @param port Pointer to the device structure for the driver instance.
 * @param value Value to set on the port.
 */
static inline int gpio_port_write(struct device *port, uint32_t value)
{
	struct gpio_driver_api *api;

	api = (struct gpio_driver_api *) port->driver_api;
	return api->write(port, GPIO_ACCESS_BY_PORT, 0, value);
}

/**
 * @brief Read data value from the port.
 * @param port Pointer to the device structure for the driver instance.
 * @param value Integer pointer to receive the data value from the port.
 */
static inline int gpio_port_read(struct device *port, uint32_t *value)
{
	struct gpio_driver_api *api;

	api = (struct gpio_driver_api *) port->driver_api;
	return api->read(port, GPIO_ACCESS_BY_PORT, 0, value);
}

/**
 * @brief Enable callback(s) for the port.
 * @param port Pointer to the device structure for the driver instance.
 *
 * Note: Depending on the driver implementation, this function will enable
 *       the port to trigger an interruption on all pins, as long as these
 *       are configured properly. So as a semantic detail, if no callback
 *       is registered, of course none will be called.
 */
static inline int gpio_port_enable_callback(struct device *port)
{
	struct gpio_driver_api *api;

	api = (struct gpio_driver_api *) port->driver_api;
	return api->enable_callback(port, GPIO_ACCESS_BY_PORT, 0);
}

/**
 * @brief Disable callback(s) for the port.
 * @param port Pointer to the device structure for the driver instance.
 */
static inline int gpio_port_disable_callback(struct device *port)
{
	struct gpio_driver_api *api;

	api = (struct gpio_driver_api *) port->driver_api;
	return api->disable_callback(port, GPIO_ACCESS_BY_PORT, 0);
}

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* __GPIO_H__ */
