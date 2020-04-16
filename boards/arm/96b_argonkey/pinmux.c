/*
 * Copyright (c) 2018 STMicroelectronics.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <drivers/pinmux.h>
#include <sys/sys_io.h>

#include <pinmux/stm32/pinmux_stm32.h>

/* pin assignments for 96boards Argonkey board */
static const struct pin_config pinconf[] = {
#if DT_HAS_NODE(DT_NODELABEL(usart1))
	{STM32_PIN_PA9, STM32F4_PINMUX_FUNC_PA9_USART1_TX},
	{STM32_PIN_PA10, STM32F4_PINMUX_FUNC_PA10_USART1_RX},
#endif
#if DT_HAS_NODE(DT_NODELABEL(i2c1))
	{STM32_PIN_PB6, STM32F4_PINMUX_FUNC_PB6_I2C1_SCL},
	{STM32_PIN_PB7, STM32F4_PINMUX_FUNC_PB7_I2C1_SDA},
#endif
#if DT_HAS_NODE(DT_NODELABEL(i2c2))
	{STM32_PIN_PB10, STM32F4_PINMUX_FUNC_PB10_I2C2_SCL},
	{STM32_PIN_PB9, STM32F4_PINMUX_FUNC_PB9_I2C2_SDA},
#endif
#if DT_HAS_NODE(DT_NODELABEL(i2c3))
	{STM32_PIN_PA8, STM32F4_PINMUX_FUNC_PA8_I2C3_SCL},
	{STM32_PIN_PB4, STM32F4_PINMUX_FUNC_PB4_I2C3_SDA},
#endif
#if DT_HAS_NODE(DT_NODELABEL(spi1))
#ifdef CONFIG_SPI_STM32_USE_HW_SS
	{STM32_PIN_PA4, STM32F4_PINMUX_FUNC_PA4_SPI1_NSS |
			STM32_OSPEEDR_VERY_HIGH_SPEED},
#endif /* CONFIG_SPI_STM32_USE_HW_SS */
	{STM32_PIN_PA5, STM32F4_PINMUX_FUNC_PA5_SPI1_SCK |
			STM32_OSPEEDR_VERY_HIGH_SPEED},
	{STM32_PIN_PA6, STM32F4_PINMUX_FUNC_PA6_SPI1_MISO},
	{STM32_PIN_PA7, STM32F4_PINMUX_FUNC_PA7_SPI1_MOSI},
#endif
#if DT_HAS_NODE(DT_NODELABEL(spi2))
#ifdef CONFIG_SPI_STM32_USE_HW_SS
	{STM32_PIN_PB12, STM32F4_PINMUX_FUNC_PB12_SPI2_NSS |
			STM32_OSPEEDR_VERY_HIGH_SPEED},
#endif /* CONFIG_SPI_STM32_USE_HW_SS */
	{STM32_PIN_PB13, STM32F4_PINMUX_FUNC_PB13_SPI2_SCK |
			STM32_OSPEEDR_VERY_HIGH_SPEED},
	{STM32_PIN_PB14, STM32F4_PINMUX_FUNC_PB14_SPI2_MISO},
	{STM32_PIN_PB15, STM32F4_PINMUX_FUNC_PB15_SPI2_MOSI},
#endif
#ifdef CONFIG_I2S_5
	{STM32_PIN_PB0, STM32F4_PINMUX_FUNC_PB0_I2S5_CK},
	{STM32_PIN_PB8, STM32F4_PINMUX_FUNC_PB8_I2S5_SD},
#endif	/* CONFIG_I2S_5 */
};

static int pinmux_stm32_init(struct device *port)
{
	ARG_UNUSED(port);

	stm32_setup_pins(pinconf, ARRAY_SIZE(pinconf));

	return 0;
}

SYS_INIT(pinmux_stm32_init, PRE_KERNEL_1,
		CONFIG_PINMUX_STM32_DEVICE_INITIALIZATION_PRIORITY);
