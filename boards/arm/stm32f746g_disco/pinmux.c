/*
 * Copyright (c) 2018 Yurii Hamann
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <drivers/pinmux.h>
#include <sys/sys_io.h>

#include <pinmux/stm32/pinmux_stm32.h>

/* pin assignments for STM32F746G-DISCO board */
static const struct pin_config pinconf[] = {
#ifdef CONFIG_UART_1
	{STM32_PIN_PA9, STM32F7_PINMUX_FUNC_PA9_USART1_TX},
	{STM32_PIN_PB7, STM32F7_PINMUX_FUNC_PB7_USART1_RX},
#endif	/* CONFIG_UART_1 */
#ifdef CONFIG_UART_6
	{STM32_PIN_PC6, STM32F7_PINMUX_FUNC_PC6_USART6_TX},
	{STM32_PIN_PC7, STM32F7_PINMUX_FUNC_PC7_USART6_RX},
#endif	/* CONFIG_UART_6 */
#ifdef CONFIG_PWM_STM32_3
	{STM32_PIN_PB4, STM32F7_PINMUX_FUNC_PB4_PWM3_CH1},
#endif /* CONFIG_PWM_STM32_3 */
#ifdef CONFIG_ETH_STM32_HAL
	{STM32_PIN_PC1, STM32F7_PINMUX_FUNC_PC1_ETH},
	{STM32_PIN_PC4, STM32F7_PINMUX_FUNC_PC4_ETH},
	{STM32_PIN_PC5, STM32F7_PINMUX_FUNC_PC5_ETH},

	{STM32_PIN_PA1, STM32F7_PINMUX_FUNC_PA1_ETH},
	{STM32_PIN_PA2, STM32F7_PINMUX_FUNC_PA2_ETH},
	{STM32_PIN_PA7, STM32F7_PINMUX_FUNC_PA7_ETH},

	{STM32_PIN_PG11, STM32F7_PINMUX_FUNC_PG11_ETH},
	{STM32_PIN_PG13, STM32F7_PINMUX_FUNC_PG13_ETH},
	{STM32_PIN_PG14, STM32F7_PINMUX_FUNC_PG14_ETH},
#endif /* CONFIG_ETH_STM32_HAL */
#if DT_HAS_NODE(DT_NODELABEL(i2c1))
	{STM32_PIN_PB8, STM32F7_PINMUX_FUNC_PB8_I2C1_SCL},
	{STM32_PIN_PB9, STM32F7_PINMUX_FUNC_PB9_I2C1_SDA},
#endif
#if DT_HAS_NODE(DT_NODELABEL(spi2))
#ifdef CONFIG_SPI_STM32_USE_HW_SS
	{STM32_PIN_PI0,  STM32F7_PINMUX_FUNC_PI0_SPI2_NSS},
#endif /* CONFIG_SPI_STM32_USE_HW_SS */
	{STM32_PIN_PI1,  STM32F7_PINMUX_FUNC_PI1_SPI2_SCK},
	{STM32_PIN_PB14, STM32F7_PINMUX_FUNC_PB14_SPI2_MISO},
	{STM32_PIN_PB15, STM32F7_PINMUX_FUNC_PB15_SPI2_MOSI},
#endif
#ifdef CONFIG_USB_DC_STM32
	{STM32_PIN_PA11, STM32F7_PINMUX_FUNC_PA11_OTG_FS_DM},
	{STM32_PIN_PA12, STM32F7_PINMUX_FUNC_PA12_OTG_FS_DP},
#endif	/* CONFIG_USB_DC_STM32 */
};

static int pinmux_stm32_init(struct device *port)
{
	ARG_UNUSED(port);

	stm32_setup_pins(pinconf, ARRAY_SIZE(pinconf));

	return 0;
}

SYS_INIT(pinmux_stm32_init, PRE_KERNEL_1,
		CONFIG_PINMUX_STM32_DEVICE_INITIALIZATION_PRIORITY);
