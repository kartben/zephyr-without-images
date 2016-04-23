/* gpio_sch.c - Driver implementation for Intel SCH GPIO controller */

/*
 * Copyright (c) 2015 Intel Corporation.
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

#include <errno.h>

#include <nanokernel.h>
#include <board.h>
#include <init.h>
#include <sys_io.h>
#include <misc/util.h>

#include "gpio_sch.h"
#include "gpio_utils.h"
#include "gpio_api_compat.h"

#ifndef CONFIG_GPIO_DEBUG
#define DBG(...)
#else
#if defined(CONFIG_STDOUT_CONSOLE)
#include <stdio.h>
#define DBG printf
#else
#include <misc/printk.h>
#define DBG printk
#endif /* CONFIG_STDOUT_CONSOLE */
#endif /* CONFIG_GPIO_DEBUG */

/* Define GPIO_SCH_LEGACY_IO_PORTS_ACCESS
 * inside soc.h if the GPIO controller
 * requires I/O port access instead of
 * memory mapped I/O.
 */
#ifdef GPIO_SCH_LEGACY_IO_PORTS_ACCESS
#define _REG_READ sys_in32
#define _REG_WRITE sys_out32
#define _REG_SET_BIT sys_io_set_bit
#define _REG_CLEAR_BIT sys_io_clear_bit
#else
#define _REG_READ sys_read32
#define _REG_WRITE sys_write32
#define _REG_SET_BIT sys_set_bit
#define _REG_CLEAR_BIT sys_clear_bit
#endif /* GPIO_SCH_LEGACY_IO_PORTS_ACCESS */

#define DEFINE_MM_REG_READ(__reg, __off)				\
	static inline uint32_t _read_##__reg(uint32_t addr)		\
	{								\
		return _REG_READ(addr + __off);				\
	}
#define DEFINE_MM_REG_WRITE(__reg, __off)				\
	static inline void _write_##__reg(uint32_t data, uint32_t addr)	\
	{								\
		_REG_WRITE(data, addr + __off);				\
	}

DEFINE_MM_REG_READ(glvl, GPIO_SCH_REG_GLVL)
DEFINE_MM_REG_WRITE(glvl, GPIO_SCH_REG_GLVL)
DEFINE_MM_REG_WRITE(gtpe, GPIO_SCH_REG_GTPE)
DEFINE_MM_REG_WRITE(gtne, GPIO_SCH_REG_GTNE)
DEFINE_MM_REG_READ(gts, GPIO_SCH_REG_GTS)
DEFINE_MM_REG_WRITE(gts, GPIO_SCH_REG_GTS)

static void _set_bit(uint32_t base_addr,
				uint32_t bit, uint8_t set)
{
	if (!set) {
		_REG_CLEAR_BIT(base_addr, bit);
	} else {
		_REG_SET_BIT(base_addr, bit);
	}
}

#define DEFINE_MM_REG_SET_BIT(__reg, __off)				\
	static inline void _set_bit_##__reg(uint32_t addr,		\
					    uint32_t bit, uint8_t set)	\
	{								\
		_set_bit(addr + __off, bit, set);			\
	}

DEFINE_MM_REG_SET_BIT(gen, GPIO_SCH_REG_GEN)
DEFINE_MM_REG_SET_BIT(gio, GPIO_SCH_REG_GIO)
DEFINE_MM_REG_SET_BIT(glvl, GPIO_SCH_REG_GLVL)
DEFINE_MM_REG_SET_BIT(gtpe, GPIO_SCH_REG_GTPE)
DEFINE_MM_REG_SET_BIT(gtne, GPIO_SCH_REG_GTNE)

static inline void _set_data_reg(uint32_t *reg, uint8_t pin, uint8_t set)
{
	*reg &= ~(BIT(pin));
	*reg |= (set << pin) & BIT(pin);
}

static void _gpio_pin_config(struct device *dev, uint32_t pin, int flags)
{
	struct gpio_sch_config *info = dev->config->config_info;
	struct gpio_sch_data *gpio = dev->driver_data;
	uint8_t active_high = 0;
	uint8_t active_low = 0;

	_set_bit_gen(info->regs, pin, 1);
	_set_bit_gio(info->regs, pin, !(flags & GPIO_DIR_MASK));

	if (flags & GPIO_INT) {
		if (flags & GPIO_INT_ACTIVE_HIGH) {
			active_high = 1;
		} else {
			active_low = 1;
		}

		DBG("Setting up pin %d to active_high %d and active_low %d\n",
		    active_high, active_low);
	}

	/* We store the gtpe/gtne settings. These will be used once
	 * we enable the callback for the pin, or the whole port
	 */
	_set_data_reg(&gpio->int_regs.gtpe, pin, active_high);
	_set_data_reg(&gpio->int_regs.gtne, pin, active_low);
}

static inline void _gpio_port_config(struct device *dev, int flags)
{
	struct gpio_sch_config *info = dev->config->config_info;
	int pin;

	for (pin = 0; pin < info->bits; pin++) {
		_gpio_pin_config(dev, pin, flags);
	}
}

static int gpio_sch_config(struct device *dev,
			   int access_op, uint32_t pin, int flags)
{
	struct gpio_sch_config *info = dev->config->config_info;

	if (access_op == GPIO_ACCESS_BY_PIN) {
		if (pin >= info->bits) {
			return -EINVAL;
		}

		_gpio_pin_config(dev, pin, flags);
	} else {
		_gpio_port_config(dev, flags);
	}

	return 0;
}

static int gpio_sch_write(struct device *dev,
			  int access_op, uint32_t pin, uint32_t value)
{
	struct gpio_sch_config *info = dev->config->config_info;

	if (access_op == GPIO_ACCESS_BY_PIN) {
		if (pin >= info->bits) {
			return -ENOTSUP;
		}

		_set_bit_glvl(info->regs, pin, value);
	} else {
		_write_glvl(info->regs, value);
	}

	return 0;
}

static int gpio_sch_read(struct device *dev,
			  int access_op, uint32_t pin, uint32_t *value)
{
	struct gpio_sch_config *info = dev->config->config_info;

	*value = _read_glvl(info->regs);

	if (access_op == GPIO_ACCESS_BY_PIN) {
		if (pin >= info->bits) {
			return -ENOTSUP;
		}

		*value = !!(*value & BIT(pin));
	}

	return 0;
}

static void _gpio_sch_poll_status(int data, int unused)
{
	struct device *dev = INT_TO_POINTER(data);
	struct gpio_sch_config *info = dev->config->config_info;
	struct gpio_sch_data *gpio = dev->driver_data;

	ARG_UNUSED(unused);

	/* Cleaning up GTS first */
	_write_gts(_read_gts(info->regs), info->regs);

	while (gpio->poll) {
		uint32_t status;

		status = _read_gts(info->regs);
		if (!status) {
			goto loop;
		}

		_gpio_fire_callbacks(&gpio->callbacks, dev, status);

		/* It's not documented but writing the same status value
		 * into GTS tells to the controller it got handled.
		 */
		_write_gts(status, info->regs);
loop:
		nano_fiber_timer_start(&gpio->poll_timer,
				       GPIO_SCH_POLLING_TICKS);
		nano_fiber_timer_test(&gpio->poll_timer, TICKS_UNLIMITED);
	}
}

static void _gpio_sch_manage_callback(struct device *dev)
{
	struct gpio_sch_data *gpio = dev->driver_data;

	/* Start the fiber only when relevant */
	if (!sys_slist_is_empty(&gpio->callbacks) && gpio->cb_enabled) {
		if (!gpio->poll) {
			DBG("Starting SCH GPIO polling fiber\n");
			gpio->poll = 1;
			fiber_start(gpio->polling_stack,
				    GPIO_SCH_POLLING_STACK_SIZE,
				    _gpio_sch_poll_status,
				    POINTER_TO_INT(dev), 0, 0, 0);
		}
	} else {
		gpio->poll = 0;
	}
}

static int gpio_sch_manage_callback(struct device *dev,
				    struct gpio_callback *callback, bool set)
{
	struct gpio_sch_data *gpio = dev->driver_data;

	_gpio_manage_callback(&gpio->callbacks, callback, set);

	_gpio_sch_manage_callback(dev);

	return 0;
}

static int gpio_sch_enable_callback(struct device *dev,
				    int access_op, uint32_t pin)
{
	struct gpio_sch_config *info = dev->config->config_info;
	struct gpio_sch_data *gpio = dev->driver_data;

	if (access_op == GPIO_ACCESS_BY_PIN) {
		uint32_t bits = BIT(pin);

		if (pin >= info->bits) {
			return -ENOTSUP;
		}

		_set_bit_gtpe(info->regs, pin, !!(bits & gpio->int_regs.gtpe));
		_set_bit_gtne(info->regs, pin, !!(bits & gpio->int_regs.gtne));

		gpio->cb_enabled |= bits;
	} else {
		_write_gtpe(gpio->int_regs.gtpe, info->regs);
		_write_gtne(gpio->int_regs.gtne, info->regs);

		gpio->cb_enabled = BIT_MASK(info->bits);
	}

	_gpio_enable_callback(dev, gpio->cb_enabled);
	_gpio_sch_manage_callback(dev);

	return 0;
}

static int gpio_sch_disable_callback(struct device *dev,
				     int access_op, uint32_t pin)
{
	struct gpio_sch_config *info = dev->config->config_info;
	struct gpio_sch_data *gpio = dev->driver_data;

	if (access_op == GPIO_ACCESS_BY_PIN) {
		if (pin >= info->bits) {
			return -ENOTSUP;
		}

		_set_bit_gtpe(info->regs, pin, 0);
		_set_bit_gtne(info->regs, pin, 0);

		gpio->cb_enabled &= ~BIT(pin);
		_gpio_disable_callback(dev, BIT(pin));
	} else {
		_write_gtpe(0, info->regs);
		_write_gtne(0, info->regs);

		gpio->cb_enabled = 0;
		_gpio_disable_callback(dev, BIT_MASK(info->bits));
	}

	_gpio_sch_manage_callback(dev);

	return 0;
}

static struct gpio_driver_api gpio_sch_api = {
	.config = gpio_sch_config,
	.write = gpio_sch_write,
	.read = gpio_sch_read,
	.manage_callback = gpio_sch_manage_callback,
	.enable_callback = gpio_sch_enable_callback,
	.disable_callback = gpio_sch_disable_callback,
};

int gpio_sch_init(struct device *dev)
{
	struct gpio_sch_data *gpio = dev->driver_data;

	dev->driver_api = &gpio_sch_api;

	nano_timer_init(&gpio->poll_timer, NULL);

	DBG("SCH GPIO Intel Driver initialized on device: %p\n", dev);

	return 0;
}

#if CONFIG_GPIO_SCH_0

struct gpio_sch_config gpio_sch_0_config = {
	.regs = GPIO_SCH_0_BASE_ADDR,
	.bits = GPIO_SCH_0_BITS,
};

struct gpio_sch_data gpio_data_0;

DEVICE_INIT(gpio_0, CONFIG_GPIO_SCH_0_DEV_NAME, gpio_sch_init,
	    &gpio_data_0, &gpio_sch_0_config,
	    SECONDARY, CONFIG_GPIO_SCH_INIT_PRIORITY);
GPIO_SETUP_COMPAT_DEV(gpio_0);

#endif /* CONFIG_GPIO_SCH_0 */
#if CONFIG_GPIO_SCH_1

struct gpio_sch_config gpio_sch_1_config = {
	.regs = GPIO_SCH_1_BASE_ADDR,
	.bits = GPIO_SCH_1_BITS,
};

struct gpio_sch_data gpio_data_1;

DEVICE_INIT(gpio_1, CONFIG_GPIO_SCH_1_DEV_NAME, gpio_sch_init,
	    &gpio_data_1, &gpio_sch_1_config,
	    SECONDARY, CONFIG_GPIO_SCH_INIT_PRIORITY);
GPIO_SETUP_COMPAT_DEV(gpio_1);

#endif /* CONFIG_GPIO_SCH_1 */
