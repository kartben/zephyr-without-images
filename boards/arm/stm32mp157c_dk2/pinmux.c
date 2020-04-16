/*
 * Copyright (c) 2019 STMicroelectronics
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <drivers/pinmux.h>
#include <sys/sys_io.h>

#include <pinmux/stm32/pinmux_stm32.h>

/* pin assignments for STM32MP157c_dk2 board */
static const struct pin_config pinconf[] = {
#ifdef CONFIG_UART_3
	{ STM32_PIN_PB10, STM32MP1X_PINMUX_FUNC_PB10_USART3_TX },
	{ STM32_PIN_PB12, STM32MP1X_PINMUX_FUNC_PB12_USART3_RX },
#endif  /* CONFIG_UART_3 */
#ifdef CONFIG_UART_7
	{ STM32_PIN_PE7, STM32MP1X_PINMUX_FUNC_PE7_UART7_RX },
	{ STM32_PIN_PE8, STM32MP1X_PINMUX_FUNC_PE8_UART7_TX },
#endif  /* CONFIG_UART_7 */
#if DT_HAS_NODE(DT_NODELABEL(i2c5))
	{ STM32_PIN_PA11, STM32MP1X_PINMUX_FUNC_PA11_I2C5_SCL },
	{ STM32_PIN_PA12, STM32MP1X_PINMUX_FUNC_PA12_I2C5_SDA },
#endif
#if DT_HAS_NODE(DT_NODELABEL(spi4))
#ifdef CONFIG_SPI_STM32_USE_HW_SS
	{STM32_PIN_PE11, STM32MP1X_PINMUX_FUNC_PE11_SPI4_NSS},
#endif /* CONFIG_SPI_STM32_USE_HW_SS */
	{STM32_PIN_PE12, STM32MP1X_PINMUX_FUNC_PE12_SPI4_SCK},
	{STM32_PIN_PE13, STM32MP1X_PINMUX_FUNC_PE13_SPI4_MISO |
		STM32_OSPEEDR_VERY_HIGH_SPEED},
	{STM32_PIN_PE14, STM32MP1X_PINMUX_FUNC_PE14_SPI4_MOSI},
#endif
#if DT_HAS_NODE(DT_NODELABEL(spi5))
#ifdef CONFIG_SPI_STM32_USE_HW_SS
	{STM32_PIN_PF6, STM32MP1X_PINMUX_FUNC_PF6_SPI5_NSS},
#endif /* CONFIG_SPI_STM32_USE_HW_SS */
	{STM32_PIN_PF7, STM32MP1X_PINMUX_FUNC_PF7_SPI5_SCK},
	{STM32_PIN_PF8, STM32MP1X_PINMUX_FUNC_PF8_SPI5_MISO |
		STM32_OSPEEDR_VERY_HIGH_SPEED},
	{STM32_PIN_PF9, STM32MP1X_PINMUX_FUNC_PF9_SPI5_MOSI},
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
