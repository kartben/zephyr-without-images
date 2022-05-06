/*
 * Copyright (c) 2021, Commonwealth Scientific and Industrial Research
 * Organisation (CSIRO) ABN 41 687 119 230.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * This is not a real GPIO driver. It is used to instantiate struct
 * devices for the "vnd,gpio" devicetree compatible used in test code.
 */

#define DT_DRV_COMPAT vnd_gpio

#include <zephyr/drivers/gpio.h>

static int vnd_gpio_pin_configure(const struct device *port,
				  gpio_pin_t pin,
				  gpio_flags_t flags)
{
	return -ENOTSUP;
}

static int vnd_gpio_port_get_raw(const struct device *port,
				 gpio_port_value_t *value)
{
	return -ENOTSUP;
}

static int vnd_gpio_port_set_masked_raw(const struct device *port,
					gpio_port_pins_t mask,
					gpio_port_value_t value)
{
	return -ENOTSUP;
}

static int vnd_gpio_port_set_bits_raw(const struct device *port,
				      gpio_port_pins_t pins)
{
	return -ENOTSUP;
}

static int vnd_gpio_port_clear_bits_raw(const struct device *port,
					gpio_port_pins_t pins)
{
	return -ENOTSUP;
}

static int vnd_gpio_port_toggle_bits(const struct device *port,
				     gpio_port_pins_t pins)
{
	return -ENOTSUP;
}

static int vnd_gpio_pin_interrupt_configure(const struct device *port,
					    gpio_pin_t pin,
					    enum gpio_int_mode mode,
					    enum gpio_int_trig trig)
{
	return -ENOTSUP;
}

static int vnd_gpio_manage_callback(const struct device *port,
				    struct gpio_callback *cb,
				    bool set)
{
	return -ENOTSUP;
}

static uint32_t vnd_gpio_get_pending_int(const struct device *dev)
{
	return 0;
}

static const struct gpio_driver_api vnd_gpio_api = {
	.pin_configure = vnd_gpio_pin_configure,
	.port_get_raw = vnd_gpio_port_get_raw,
	.port_set_masked_raw = vnd_gpio_port_set_masked_raw,
	.port_set_bits_raw = vnd_gpio_port_set_bits_raw,
	.port_clear_bits_raw = vnd_gpio_port_clear_bits_raw,
	.port_toggle_bits = vnd_gpio_port_toggle_bits,
	.pin_interrupt_configure = vnd_gpio_pin_interrupt_configure,
	.manage_callback = vnd_gpio_manage_callback,
	.get_pending_int = vnd_gpio_get_pending_int
};

static int vnd_gpio_init(const struct device *dev)
{
	return 0;
}

#define VND_GPIO_INIT(n)					  \
	DEVICE_DT_INST_DEFINE(n, &vnd_gpio_init, NULL,		  \
			      NULL, NULL, POST_KERNEL,		  \
			      CONFIG_KERNEL_INIT_PRIORITY_DEVICE, \
			      &vnd_gpio_api);

DT_INST_FOREACH_STATUS_OKAY(VND_GPIO_INIT)
