/*
 * Copyright (c) 2016 Open-RnD Sp. z o.o.
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

#include <nanokernel.h>
#include <device.h>
#include <soc.h>
#include <gpio.h>
#include <clock_control/stm32_clock_control.h>
#include <pinmux/pinmux_stm32.h>
#include <pinmux.h>
#include <gpio/gpio_stm32.h>
#include <misc/util.h>
#include <interrupt_controller/exti_stm32.h>

/**
 * @brief Common GPIO driver for STM32 MCUs. Each SoC must implement a
 * SoC specific integration glue
 */

/**
 * @brief EXTI interrupt callback
 */
static void gpio_stm32_isr(int line, void *arg)
{
	struct device *dev = arg;
	struct gpio_stm32_data *data = dev->driver_data;
	int is_enabled;

	if (!data->cb) {
		return;
	}

	is_enabled = data->enabled_mask & (1 << line);

	if (!is_enabled) {
		return;
	}

	data->cb(dev, line);
}

/**
 * @brief Configure pin or port
 */
static int gpio_stm32_config(struct device *dev, int access_op,
			     uint32_t pin, int flags)
{
	struct gpio_stm32_config *cfg = dev->config->config_info;
	int pincfg;
	int map_res;

	if (access_op != GPIO_ACCESS_BY_PIN) {
		return DEV_NO_SUPPORT;
	}

	/* figure out if we can map the requested GPIO
	 * configuration
	 */
	map_res = stm32_gpio_flags_to_conf(flags, &pincfg);
	if (map_res) {
		return map_res;
	}

	if (stm32_gpio_configure(cfg->base, pin, pincfg)) {
		return -EIO;
	}

	if (flags & GPIO_INT) {
		struct device *exti = device_get_binding(STM32_EXTI_NAME);

		stm32_exti_set_callback(exti, pin, gpio_stm32_isr, dev);

		stm32_gpio_enable_int(cfg->port, pin);

		if (flags & GPIO_INT_EDGE) {
			int edge = 0;

			if (flags & GPIO_INT_DOUBLE_EDGE) {
				edge = STM32_EXTI_TRIG_RISING | STM32_EXTI_TRIG_FALLING;
			} else if (flags & GPIO_INT_ACTIVE_HIGH) {
				edge = STM32_EXTI_TRIG_RISING;
			} else {
				edge = STM32_EXTI_TRIG_FALLING;
			}
			stm32_exti_trigger(exti, pin, edge);
		}

		stm32_exti_enable(exti, pin);
	}

	return 0;
}

/**
 * @brief Set the pin or port output
 */
static int gpio_stm32_write(struct device *dev, int access_op,
			   uint32_t pin, uint32_t value)
{
	struct gpio_stm32_config *cfg = dev->config->config_info;

	if (access_op != GPIO_ACCESS_BY_PIN) {
		return -ENOTSUP;
	}

	return stm32_gpio_set(cfg->base, pin, value);
}

/**
 * @brief Read the pin or port status
 */
static int gpio_stm32_read(struct device *dev, int access_op,
			   uint32_t pin, uint32_t *value)
{
	struct gpio_stm32_config *cfg = dev->config->config_info;

	if (access_op != GPIO_ACCESS_BY_PIN) {
		return -ENOTSUP;
	}

	*value = stm32_gpio_get(cfg->base, pin);

	return 0;
}

static int gpio_stm32_set_callback(struct device *dev,
				   gpio_callback_t callback)
{
	struct gpio_stm32_data *data = dev->driver_data;

	data->cb = callback;

	return 0;
}

static int gpio_stm32_enable_callback(struct device *dev,
				      int access_op, uint32_t pin)
{
	struct gpio_stm32_data *data = dev->driver_data;

	if (access_op != GPIO_ACCESS_BY_PIN) {
		return -ENOTSUP;
	}

	data->enabled_mask |= 1 << pin;

	return 0;
}

static int gpio_stm32_disable_callback(struct device *dev,
				       int access_op, uint32_t pin)
{
	struct gpio_stm32_data *data = dev->driver_data;

	if (access_op != GPIO_ACCESS_BY_PIN) {
		return -ENOTSUP;
	}

	data->enabled_mask &= ~(1 << pin);

	return 0;
}

static int gpio_stm32_suspend_port(struct device *dev)
{
	ARG_UNUSED(dev);

	return -ENOTSUP;
}

static int gpio_stm32_resume_port(struct device *dev)
{
	ARG_UNUSED(dev);

	return -ENOTSUP;
}

static struct gpio_driver_api gpio_stm32_driver = {
	.config = gpio_stm32_config,
	.write = gpio_stm32_write,
	.read = gpio_stm32_read,
	.set_callback = gpio_stm32_set_callback,
	.enable_callback = gpio_stm32_enable_callback,
	.disable_callback = gpio_stm32_disable_callback,
	.suspend = gpio_stm32_suspend_port,
	.resume = gpio_stm32_resume_port,

};

/**
 * @brief Initialize GPIO port
 *
 * Perform basic initialization of a GPIO port. The code will
 * enable the clock for corresponding peripheral.
 *
 * @param dev GPIO device struct
 *
 * @return DEV_OK
 */
static int gpio_stm32_init(struct device *device)
{
	struct gpio_stm32_config *cfg = device->config->config_info;

	/* enable clock for subsystem */
	struct device *clk =
		device_get_binding(STM32_CLOCK_CONTROL_NAME);

	clock_control_on(clk, cfg->clock_subsys);

	device->driver_api = &gpio_stm32_driver;

	return 0;
}

#define GPIO_DEVICE_INIT(__name, __suffix, __base_addr, __port, __clock) \
static struct gpio_stm32_config gpio_stm32_cfg_## __suffix = {		\
	.base = (uint32_t *)__base_addr,				\
	.port = __port,							\
	.clock_subsys = UINT_TO_POINTER(__clock),			\
};									\
static struct gpio_stm32_data gpio_stm32_data_## __suffix;		\
DEVICE_INIT(gpio_stm32_## __suffix,					\
	__name,								\
	gpio_stm32_init,						\
	&gpio_stm32_data_## __suffix,					\
	&gpio_stm32_cfg_## __suffix,					\
	SECONDARY,							\
	CONFIG_KERNEL_INIT_PRIORITY_DEVICE)

#ifdef CONFIG_GPIO_STM32_PORTA
GPIO_DEVICE_INIT("GPIOA", a, GPIOA_BASE, STM32_PORTA,
#ifdef CONFIG_SOC_STM32F1X
		STM32F10X_CLOCK_SUBSYS_IOPA
		| STM32F10X_CLOCK_SUBSYS_AFIO
#endif
	);
#endif /* CONFIG_GPIO_STM32_PORTA */

#ifdef CONFIG_GPIO_STM32_PORTB
GPIO_DEVICE_INIT("GPIOB", b, GPIOB_BASE, STM32_PORTB,
#ifdef CONFIG_SOC_STM32F1X
		STM32F10X_CLOCK_SUBSYS_IOPB
		| STM32F10X_CLOCK_SUBSYS_AFIO
#endif
	);
#endif /* CONFIG_GPIO_STM32_PORTB */

#ifdef CONFIG_GPIO_STM32_PORTC
GPIO_DEVICE_INIT("GPIOC", c, GPIOC_BASE, STM32_PORTC,
#ifdef CONFIG_SOC_STM32F1X
		STM32F10X_CLOCK_SUBSYS_IOPC
		| STM32F10X_CLOCK_SUBSYS_AFIO
#endif
);
#endif /* CONFIG_GPIO_STM32_PORTC */

#ifdef CONFIG_GPIO_STM32_PORTD
GPIO_DEVICE_INIT("GPIOD", d, GPIOD_BASE, STM32_PORTD,
#ifdef CONFIG_SOC_STM32F1X
		STM32F10X_CLOCK_SUBSYS_IOPD
		| STM32F10X_CLOCK_SUBSYS_AFIO
#endif
	);
#endif /* CONFIG_GPIO_STM32_PORTD */

#ifdef CONFIG_GPIO_STM32_PORTE
GPIO_DEVICE_INIT("GPIOE", e, GPIOE_BASE, STM32_PORTE
#ifdef CONFIG_SOC_STM32F1X
		STM32F10X_CLOCK_SUBSYS_IOPE
		| STM32F10X_CLOCK_SUBSYS_AFIO
#endif
	);
#endif /* CONFIG_GPIO_STM32_PORTE */
