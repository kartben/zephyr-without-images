/*
 * Copyright (c) 2017 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <drivers/pinmux.h>
#include <sys/sys_io.h>

#include <pinmux/stm32/pinmux_stm32.h>

/* pin assignments for NUCLEO-F429ZI board */
static const struct pin_config pinconf[] = {
#if DT_NODE_HAS_STATUS(DT_NODELABEL(usart3), okay) && CONFIG_SERIAL
	{STM32_PIN_PD8, STM32F4_PINMUX_FUNC_PD8_USART3_TX},
	{STM32_PIN_PD9, STM32F4_PINMUX_FUNC_PD9_USART3_RX},
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(usart6), okay) && CONFIG_SERIAL
	{STM32_PIN_PG14, STM32F4_PINMUX_FUNC_PG14_USART6_TX},
	{STM32_PIN_PG9, STM32F4_PINMUX_FUNC_PG9_USART6_RX},
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(mac), okay) && CONFIG_NET_L2_ETHERNET
	{STM32_PIN_PC1, STM32F4_PINMUX_FUNC_PC1_ETH},
	{STM32_PIN_PC4, STM32F4_PINMUX_FUNC_PC4_ETH},
	{STM32_PIN_PC5, STM32F4_PINMUX_FUNC_PC5_ETH},

	{STM32_PIN_PA1, STM32F4_PINMUX_FUNC_PA1_ETH},
	{STM32_PIN_PA2, STM32F4_PINMUX_FUNC_PA2_ETH},
	{STM32_PIN_PA7, STM32F4_PINMUX_FUNC_PA7_ETH},

	{STM32_PIN_PG11, STM32F4_PINMUX_FUNC_PG11_ETH},
	{STM32_PIN_PG13, STM32F4_PINMUX_FUNC_PG13_ETH},
	{STM32_PIN_PB13, STM32F4_PINMUX_FUNC_PB13_ETH},
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(i2c1), okay) && CONFIG_I2C
	{STM32_PIN_PB8, STM32F4_PINMUX_FUNC_PB8_I2C1_SCL},
	{STM32_PIN_PB9, STM32F4_PINMUX_FUNC_PB9_I2C1_SDA},
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(spi1), okay) && CONFIG_SPI
#ifdef CONFIG_SPI_STM32_USE_HW_SS
	{STM32_PIN_PA4, STM32F4_PINMUX_FUNC_PA4_SPI1_NSS},
#endif /* CONFIG_SPI_STM32_USE_HW_SS */
	{STM32_PIN_PA5, STM32F4_PINMUX_FUNC_PA5_SPI1_SCK},
	{STM32_PIN_PA6, STM32F4_PINMUX_FUNC_PA6_SPI1_MISO},
	{STM32_PIN_PA7, STM32F4_PINMUX_FUNC_PA7_SPI1_MOSI},
#endif
#ifdef CONFIG_USB_DC_STM32
	{STM32_PIN_PA11, STM32F4_PINMUX_FUNC_PA11_OTG_FS_DM},
	{STM32_PIN_PA12, STM32F4_PINMUX_FUNC_PA12_OTG_FS_DP},
#endif	/* CONFIG_USB_DC_STM32 */
#if DT_NODE_HAS_STATUS(DT_NODELABEL(adc1), okay) && CONFIG_ADC
	{STM32_PIN_PA0, STM32F4_PINMUX_FUNC_PA0_ADC123_IN0},
#endif
};

static int pinmux_stm32_init(const struct device *port)
{
	ARG_UNUSED(port);

	stm32_setup_pins(pinconf, ARRAY_SIZE(pinconf));

	return 0;
}

SYS_INIT(pinmux_stm32_init, PRE_KERNEL_1,
		CONFIG_PINMUX_STM32_DEVICE_INITIALIZATION_PRIORITY);
