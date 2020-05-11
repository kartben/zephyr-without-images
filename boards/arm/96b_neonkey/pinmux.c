/*
 * Copyright (c) 2017 Linaro Limited.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <drivers/pinmux.h>
#include <sys/sys_io.h>

#include <pinmux/stm32/pinmux_stm32.h>

/* pin assignments for 96boards Neonkey board */
static const struct pin_config pinconf[] = {
#if DT_NODE_HAS_STATUS(DT_NODELABEL(usart1), okay)
	{STM32_PIN_PA9, STM32F4_PINMUX_FUNC_PA9_USART1_TX},
	{STM32_PIN_PA10, STM32F4_PINMUX_FUNC_PA10_USART1_RX},
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(i2c1), okay)
	{STM32_PIN_PB6, STM32F4_PINMUX_FUNC_PB6_I2C1_SCL},
	{STM32_PIN_PB7, STM32F4_PINMUX_FUNC_PB7_I2C1_SDA},
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(i2c2), okay)
	{STM32_PIN_PB10, STM32F4_PINMUX_FUNC_PB10_I2C2_SCL},
	{STM32_PIN_PB3, STM32F4_PINMUX_FUNC_PB3_I2C2_SDA},
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(i2c3), okay)
	{STM32_PIN_PA8, STM32F4_PINMUX_FUNC_PA8_I2C3_SCL},
	{STM32_PIN_PB4, STM32F4_PINMUX_FUNC_PB4_I2C3_SDA},
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(spi1), okay)
#ifdef CONFIG_SPI_STM32_USE_HW_SS
	{STM32_PIN_PA4, STM32F4_PINMUX_FUNC_PA4_SPI1_NSS},
#endif /* CONFIG_SPI_STM32_USE_HW_SS */
	{STM32_PIN_PA5, STM32F4_PINMUX_FUNC_PA5_SPI1_SCK},
	{STM32_PIN_PA6, STM32F4_PINMUX_FUNC_PA6_SPI1_MISO},
	{STM32_PIN_PA7, STM32F4_PINMUX_FUNC_PA7_SPI1_MOSI},
#endif
};

static int pinmux_stm32_init(struct device *port)
{
	ARG_UNUSED(port);

	stm32_setup_pins(pinconf, ARRAY_SIZE(pinconf));

	return 0;
}

SYS_INIT(pinmux_stm32_init, PRE_KERNEL_1,
		CONFIG_PINMUX_STM32_DEVICE_INITIALIZATION_PRIORITY);
