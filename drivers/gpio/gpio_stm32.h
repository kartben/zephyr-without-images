/*
 * Copyright (c) 2016 Open-RnD Sp. z o.o.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_GPIO_GPIO_STM32_H_
#define ZEPHYR_DRIVERS_GPIO_GPIO_STM32_H_

/**
 * @file header for STM32 GPIO
 */

#include <zephyr/drivers/clock_control/stm32_clock_control.h>
#include <pinmux/pinmux_stm32.h>
#include <zephyr/drivers/gpio.h>

/* GPIO buses definitions */

#define STM32_PORT_NOT_AVAILABLE 0xFFFFFFFF

#ifdef CONFIG_SOC_SERIES_STM32F0X
#define STM32_CLOCK_BUS_GPIO STM32_CLOCK_BUS_AHB1
#define STM32_PERIPH_GPIOA LL_AHB1_GRP1_PERIPH_GPIOA
#define STM32_PERIPH_GPIOB LL_AHB1_GRP1_PERIPH_GPIOB
#define STM32_PERIPH_GPIOC LL_AHB1_GRP1_PERIPH_GPIOC
#define STM32_PERIPH_GPIOD LL_AHB1_GRP1_PERIPH_GPIOD
#define STM32_PERIPH_GPIOE LL_AHB1_GRP1_PERIPH_GPIOE
#define STM32_PERIPH_GPIOF LL_AHB1_GRP1_PERIPH_GPIOF
#elif CONFIG_SOC_SERIES_STM32F1X
#define STM32_CLOCK_BUS_GPIO STM32_CLOCK_BUS_APB2
#define STM32_PERIPH_GPIOA LL_APB2_GRP1_PERIPH_GPIOA
#define STM32_PERIPH_GPIOB LL_APB2_GRP1_PERIPH_GPIOB
#define STM32_PERIPH_GPIOC LL_APB2_GRP1_PERIPH_GPIOC
#define STM32_PERIPH_GPIOD LL_APB2_GRP1_PERIPH_GPIOD
#define STM32_PERIPH_GPIOE LL_APB2_GRP1_PERIPH_GPIOE
#define STM32_PERIPH_GPIOF LL_APB2_GRP1_PERIPH_GPIOF
#define STM32_PERIPH_GPIOG LL_APB2_GRP1_PERIPH_GPIOG
#elif CONFIG_SOC_SERIES_STM32F2X
#define STM32_CLOCK_BUS_GPIO STM32_CLOCK_BUS_AHB1
#define STM32_PERIPH_GPIOA LL_AHB1_GRP1_PERIPH_GPIOA
#define STM32_PERIPH_GPIOB LL_AHB1_GRP1_PERIPH_GPIOB
#define STM32_PERIPH_GPIOC LL_AHB1_GRP1_PERIPH_GPIOC
#define STM32_PERIPH_GPIOD LL_AHB1_GRP1_PERIPH_GPIOD
#define STM32_PERIPH_GPIOE LL_AHB1_GRP1_PERIPH_GPIOE
#define STM32_PERIPH_GPIOF LL_AHB1_GRP1_PERIPH_GPIOF
#define STM32_PERIPH_GPIOG LL_AHB1_GRP1_PERIPH_GPIOG
#define STM32_PERIPH_GPIOH LL_AHB1_GRP1_PERIPH_GPIOH
#define STM32_PERIPH_GPIOI LL_AHB1_GRP1_PERIPH_GPIOI
#elif CONFIG_SOC_SERIES_STM32F3X
#define STM32_CLOCK_BUS_GPIO STM32_CLOCK_BUS_AHB1
#define STM32_PERIPH_GPIOA LL_AHB1_GRP1_PERIPH_GPIOA
#define STM32_PERIPH_GPIOB LL_AHB1_GRP1_PERIPH_GPIOB
#define STM32_PERIPH_GPIOC LL_AHB1_GRP1_PERIPH_GPIOC
#define STM32_PERIPH_GPIOD LL_AHB1_GRP1_PERIPH_GPIOD
#define STM32_PERIPH_GPIOE LL_AHB1_GRP1_PERIPH_GPIOE
#define STM32_PERIPH_GPIOF LL_AHB1_GRP1_PERIPH_GPIOF
#define STM32_PERIPH_GPIOG LL_AHB1_GRP1_PERIPH_GPIOG
#define STM32_PERIPH_GPIOH LL_AHB1_GRP1_PERIPH_GPIOH
#elif CONFIG_SOC_SERIES_STM32F4X
#define STM32_CLOCK_BUS_GPIO STM32_CLOCK_BUS_AHB1
#define STM32_PERIPH_GPIOA LL_AHB1_GRP1_PERIPH_GPIOA
#define STM32_PERIPH_GPIOB LL_AHB1_GRP1_PERIPH_GPIOB
#define STM32_PERIPH_GPIOC LL_AHB1_GRP1_PERIPH_GPIOC
#define STM32_PERIPH_GPIOD LL_AHB1_GRP1_PERIPH_GPIOD
#define STM32_PERIPH_GPIOE LL_AHB1_GRP1_PERIPH_GPIOE
#define STM32_PERIPH_GPIOF LL_AHB1_GRP1_PERIPH_GPIOF
#define STM32_PERIPH_GPIOG LL_AHB1_GRP1_PERIPH_GPIOG
#define STM32_PERIPH_GPIOH LL_AHB1_GRP1_PERIPH_GPIOH
#define STM32_PERIPH_GPIOI LL_AHB1_GRP1_PERIPH_GPIOI
#define STM32_PERIPH_GPIOJ LL_AHB1_GRP1_PERIPH_GPIOJ
#define STM32_PERIPH_GPIOK LL_AHB1_GRP1_PERIPH_GPIOK
#elif CONFIG_SOC_SERIES_STM32F7X
#define STM32_CLOCK_BUS_GPIO STM32_CLOCK_BUS_AHB1
#define STM32_PERIPH_GPIOA LL_AHB1_GRP1_PERIPH_GPIOA
#define STM32_PERIPH_GPIOB LL_AHB1_GRP1_PERIPH_GPIOB
#define STM32_PERIPH_GPIOC LL_AHB1_GRP1_PERIPH_GPIOC
#define STM32_PERIPH_GPIOD LL_AHB1_GRP1_PERIPH_GPIOD
#define STM32_PERIPH_GPIOE LL_AHB1_GRP1_PERIPH_GPIOE
#define STM32_PERIPH_GPIOF LL_AHB1_GRP1_PERIPH_GPIOF
#define STM32_PERIPH_GPIOG LL_AHB1_GRP1_PERIPH_GPIOG
#define STM32_PERIPH_GPIOH LL_AHB1_GRP1_PERIPH_GPIOH
#define STM32_PERIPH_GPIOI LL_AHB1_GRP1_PERIPH_GPIOI
#define STM32_PERIPH_GPIOJ LL_AHB1_GRP1_PERIPH_GPIOJ
#define STM32_PERIPH_GPIOK LL_AHB1_GRP1_PERIPH_GPIOK
#elif CONFIG_SOC_SERIES_STM32H7X
#define STM32_CLOCK_BUS_GPIO STM32_CLOCK_BUS_AHB4
#define STM32_PERIPH_GPIOA LL_AHB4_GRP1_PERIPH_GPIOA
#define STM32_PERIPH_GPIOB LL_AHB4_GRP1_PERIPH_GPIOB
#define STM32_PERIPH_GPIOC LL_AHB4_GRP1_PERIPH_GPIOC
#define STM32_PERIPH_GPIOD LL_AHB4_GRP1_PERIPH_GPIOD
#define STM32_PERIPH_GPIOE LL_AHB4_GRP1_PERIPH_GPIOE
#define STM32_PERIPH_GPIOF LL_AHB4_GRP1_PERIPH_GPIOF
#define STM32_PERIPH_GPIOG LL_AHB4_GRP1_PERIPH_GPIOG
#define STM32_PERIPH_GPIOH LL_AHB4_GRP1_PERIPH_GPIOH
#define STM32_PERIPH_GPIOI LL_AHB4_GRP1_PERIPH_GPIOI
#define STM32_PERIPH_GPIOJ LL_AHB4_GRP1_PERIPH_GPIOJ
#define STM32_PERIPH_GPIOK LL_AHB4_GRP1_PERIPH_GPIOK
#elif CONFIG_SOC_SERIES_STM32G0X
#define STM32_CLOCK_BUS_GPIO STM32_CLOCK_BUS_IOP
#define STM32_PERIPH_GPIOA LL_IOP_GRP1_PERIPH_GPIOA
#define STM32_PERIPH_GPIOB LL_IOP_GRP1_PERIPH_GPIOB
#define STM32_PERIPH_GPIOC LL_IOP_GRP1_PERIPH_GPIOC
#define STM32_PERIPH_GPIOD LL_IOP_GRP1_PERIPH_GPIOD
#define STM32_PERIPH_GPIOE LL_IOP_GRP1_PERIPH_GPIOE
#define STM32_PERIPH_GPIOF LL_IOP_GRP1_PERIPH_GPIOF
#elif CONFIG_SOC_SERIES_STM32L0X
#define STM32_CLOCK_BUS_GPIO STM32_CLOCK_BUS_IOP
#define STM32_PERIPH_GPIOA LL_IOP_GRP1_PERIPH_GPIOA
#define STM32_PERIPH_GPIOB LL_IOP_GRP1_PERIPH_GPIOB
#define STM32_PERIPH_GPIOC LL_IOP_GRP1_PERIPH_GPIOC
#define STM32_PERIPH_GPIOD LL_IOP_GRP1_PERIPH_GPIOD
#define STM32_PERIPH_GPIOE LL_IOP_GRP1_PERIPH_GPIOE
#define STM32_PERIPH_GPIOH LL_IOP_GRP1_PERIPH_GPIOH
#elif CONFIG_SOC_SERIES_STM32L1X
#define STM32_CLOCK_BUS_GPIO STM32_CLOCK_BUS_AHB1
#define STM32_PERIPH_GPIOA LL_AHB1_GRP1_PERIPH_GPIOA
#define STM32_PERIPH_GPIOB LL_AHB1_GRP1_PERIPH_GPIOB
#define STM32_PERIPH_GPIOC LL_AHB1_GRP1_PERIPH_GPIOC
#define STM32_PERIPH_GPIOD LL_AHB1_GRP1_PERIPH_GPIOD
#define STM32_PERIPH_GPIOE LL_AHB1_GRP1_PERIPH_GPIOE
#define STM32_PERIPH_GPIOF LL_AHB1_GRP1_PERIPH_GPIOF
#define STM32_PERIPH_GPIOG LL_AHB1_GRP1_PERIPH_GPIOG
#define STM32_PERIPH_GPIOH LL_AHB1_GRP1_PERIPH_GPIOH
#elif CONFIG_SOC_SERIES_STM32L4X
#define STM32_CLOCK_BUS_GPIO STM32_CLOCK_BUS_AHB2
#define STM32_PERIPH_GPIOA LL_AHB2_GRP1_PERIPH_GPIOA
#define STM32_PERIPH_GPIOB LL_AHB2_GRP1_PERIPH_GPIOB
#define STM32_PERIPH_GPIOC LL_AHB2_GRP1_PERIPH_GPIOC
#define STM32_PERIPH_GPIOD LL_AHB2_GRP1_PERIPH_GPIOD
#define STM32_PERIPH_GPIOE LL_AHB2_GRP1_PERIPH_GPIOE
#define STM32_PERIPH_GPIOF LL_AHB2_GRP1_PERIPH_GPIOF
#define STM32_PERIPH_GPIOG LL_AHB2_GRP1_PERIPH_GPIOG
#define STM32_PERIPH_GPIOH LL_AHB2_GRP1_PERIPH_GPIOH
#define STM32_PERIPH_GPIOI LL_AHB2_GRP1_PERIPH_GPIOI
#elif CONFIG_SOC_SERIES_STM32L5X
#define STM32_CLOCK_BUS_GPIO STM32_CLOCK_BUS_AHB2
#define STM32_PERIPH_GPIOA LL_AHB2_GRP1_PERIPH_GPIOA
#define STM32_PERIPH_GPIOB LL_AHB2_GRP1_PERIPH_GPIOB
#define STM32_PERIPH_GPIOC LL_AHB2_GRP1_PERIPH_GPIOC
#define STM32_PERIPH_GPIOD LL_AHB2_GRP1_PERIPH_GPIOD
#define STM32_PERIPH_GPIOE LL_AHB2_GRP1_PERIPH_GPIOE
#define STM32_PERIPH_GPIOF LL_AHB2_GRP1_PERIPH_GPIOF
#define STM32_PERIPH_GPIOG LL_AHB2_GRP1_PERIPH_GPIOG
#define STM32_PERIPH_GPIOH LL_AHB2_GRP1_PERIPH_GPIOH
#elif CONFIG_SOC_SERIES_STM32MP1X
#define STM32_CLOCK_BUS_GPIO STM32_CLOCK_BUS_AHB4
#define STM32_PERIPH_GPIOA LL_AHB4_GRP1_PERIPH_GPIOA
#define STM32_PERIPH_GPIOB LL_AHB4_GRP1_PERIPH_GPIOB
#define STM32_PERIPH_GPIOC LL_AHB4_GRP1_PERIPH_GPIOC
#define STM32_PERIPH_GPIOD LL_AHB4_GRP1_PERIPH_GPIOD
#define STM32_PERIPH_GPIOE LL_AHB4_GRP1_PERIPH_GPIOE
#define STM32_PERIPH_GPIOF LL_AHB4_GRP1_PERIPH_GPIOF
#define STM32_PERIPH_GPIOG LL_AHB4_GRP1_PERIPH_GPIOG
#define STM32_PERIPH_GPIOH LL_AHB4_GRP1_PERIPH_GPIOH
#define STM32_PERIPH_GPIOI LL_AHB4_GRP1_PERIPH_GPIOI
#define STM32_PERIPH_GPIOJ LL_AHB4_GRP1_PERIPH_GPIOJ
#define STM32_PERIPH_GPIOK LL_AHB4_GRP1_PERIPH_GPIOK
#elif CONFIG_SOC_SERIES_STM32WBX
#define STM32_CLOCK_BUS_GPIO STM32_CLOCK_BUS_AHB2
#define STM32_PERIPH_GPIOA LL_AHB2_GRP1_PERIPH_GPIOA
#define STM32_PERIPH_GPIOB LL_AHB2_GRP1_PERIPH_GPIOB
#define STM32_PERIPH_GPIOC LL_AHB2_GRP1_PERIPH_GPIOC
#define STM32_PERIPH_GPIOD LL_AHB2_GRP1_PERIPH_GPIOD
#define STM32_PERIPH_GPIOE LL_AHB2_GRP1_PERIPH_GPIOE
#define STM32_PERIPH_GPIOH LL_AHB2_GRP1_PERIPH_GPIOH
#elif CONFIG_SOC_SERIES_STM32G4X
#define STM32_CLOCK_BUS_GPIO STM32_CLOCK_BUS_AHB2
#define STM32_PERIPH_GPIOA LL_AHB2_GRP1_PERIPH_GPIOA
#define STM32_PERIPH_GPIOB LL_AHB2_GRP1_PERIPH_GPIOB
#define STM32_PERIPH_GPIOC LL_AHB2_GRP1_PERIPH_GPIOC
#define STM32_PERIPH_GPIOD LL_AHB2_GRP1_PERIPH_GPIOD
#define STM32_PERIPH_GPIOE LL_AHB2_GRP1_PERIPH_GPIOE
#define STM32_PERIPH_GPIOF LL_AHB2_GRP1_PERIPH_GPIOF
#define STM32_PERIPH_GPIOG LL_AHB2_GRP1_PERIPH_GPIOG
#elif CONFIG_SOC_SERIES_STM32WLX
#define STM32_CLOCK_BUS_GPIO STM32_CLOCK_BUS_AHB2
#define STM32_PERIPH_GPIOA LL_AHB2_GRP1_PERIPH_GPIOA
#define STM32_PERIPH_GPIOB LL_AHB2_GRP1_PERIPH_GPIOB
#define STM32_PERIPH_GPIOC LL_AHB2_GRP1_PERIPH_GPIOC
#define STM32_PERIPH_GPIOH LL_AHB2_GRP1_PERIPH_GPIOH
#endif /* CONFIG_SOC_SERIES_* */

#ifdef CONFIG_SOC_SERIES_STM32F1X
#define STM32_PINCFG_MODE_OUTPUT        (STM32_MODE_OUTPUT     \
					 | STM32_CNF_GP_OUTPUT \
					 | STM32_CNF_PUSH_PULL)
#define STM32_PINCFG_MODE_INPUT         STM32_MODE_INPUT
#define STM32_PINCFG_MODE_ANALOG        (STM32_MODE_INPUT	\
					 | STM32_CNF_IN_ANALOG)
#define STM32_PINCFG_PUSH_PULL          STM32_CNF_PUSH_PULL
#define STM32_PINCFG_OPEN_DRAIN         STM32_CNF_OPEN_DRAIN
#define STM32_PINCFG_PULL_UP            (STM32_CNF_IN_PUPD | STM32_PUPD_PULL_UP)
#define STM32_PINCFG_PULL_DOWN          (STM32_CNF_IN_PUPD | \
					STM32_PUPD_PULL_DOWN)
#define STM32_PINCFG_FLOATING           (STM32_CNF_IN_FLOAT | \
					STM32_PUPD_NO_PULL)
#else
#define STM32_PINCFG_MODE_OUTPUT        STM32_MODER_OUTPUT_MODE
#define STM32_PINCFG_MODE_INPUT         STM32_MODER_INPUT_MODE
#define STM32_PINCFG_MODE_ANALOG        STM32_MODER_ANALOG_MODE
#define STM32_PINCFG_PUSH_PULL          STM32_OTYPER_PUSH_PULL
#define STM32_PINCFG_OPEN_DRAIN         STM32_OTYPER_OPEN_DRAIN
#define STM32_PINCFG_PULL_UP            STM32_PUPDR_PULL_UP
#define STM32_PINCFG_PULL_DOWN          STM32_PUPDR_PULL_DOWN
#define STM32_PINCFG_FLOATING           STM32_PUPDR_NO_PULL
#endif /* CONFIG_SOC_SERIES_STM32F1X */

/**
 * @brief configuration of GPIO device
 */
struct gpio_stm32_config {
	/* gpio_driver_config needs to be first */
	struct gpio_driver_config common;
	/* port base address */
	uint32_t *base;
	/* IO port */
	int port;
	struct stm32_pclken pclken;
};

/**
 * @brief driver data
 */
struct gpio_stm32_data {
	/* gpio_driver_data needs to be first */
	struct gpio_driver_data common;
	/* device's owner of this data */
	const struct device *dev;
	/* user ISR cb */
	sys_slist_t cb;
};

/**
 * @brief helper for configuration of GPIO pin
 *
 * @param dev GPIO port device pointer
 * @param pin IO pin
 * @param conf GPIO mode
 * @param func Pin function
 *
 * @return 0 on success, negative errno code on failure
 */
int gpio_stm32_configure(const struct device *dev, int pin, int conf, int func);

#endif /* ZEPHYR_DRIVERS_GPIO_GPIO_STM32_H_ */
