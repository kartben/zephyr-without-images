/*
 * Copyright (c) 2017 I-SENSE group of ICCS
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <drivers/pinmux.h>
#include <sys/sys_io.h>

#include <pinmux/stm32/pinmux_stm32.h>

/* pin assignments for STM32F3DISCOVERY board */
static const struct pin_config pinconf[] = {
#ifdef CONFIG_UART_1
	{STM32_PIN_PC4, STM32F3_PINMUX_FUNC_PC4_USART1_TX},
	{STM32_PIN_PC5, STM32F3_PINMUX_FUNC_PC5_USART1_RX},
#endif	/* CONFIG_UART_1 */
#ifdef CONFIG_UART_2
	{STM32_PIN_PA2, STM32F3_PINMUX_FUNC_PA2_USART2_TX},
	{STM32_PIN_PA3, STM32F3_PINMUX_FUNC_PA3_USART2_RX},
#endif	/* CONFIG_UART_2 */
#if DT_HAS_NODE(DT_NODELABEL(i2c1))
	{STM32_PIN_PB6, STM32F3_PINMUX_FUNC_PB6_I2C1_SCL},
	{STM32_PIN_PB7, STM32F3_PINMUX_FUNC_PB7_I2C1_SDA},
#endif
#if DT_HAS_NODE(DT_NODELABEL(i2c2))
	{STM32_PIN_PA9, STM32F3_PINMUX_FUNC_PA9_I2C2_SCL},
	{STM32_PIN_PA10, STM32F3_PINMUX_FUNC_PA10_I2C2_SDA},
#endif
#if DT_HAS_NODE(DT_NODELABEL(spi1))
#ifdef CONFIG_SPI_STM32_USE_HW_SS
	{STM32_PIN_PA4, STM32F3_PINMUX_FUNC_PA4_SPI1_NSS},
#endif /* CONFIG_SPI_STM32_USE_HW_SS */
	{STM32_PIN_PA5, STM32F3_PINMUX_FUNC_PA5_SPI1_SCK},
	{STM32_PIN_PA6, STM32F3_PINMUX_FUNC_PA6_SPI1_MISO},
	{STM32_PIN_PA7, STM32F3_PINMUX_FUNC_PA7_SPI1_MOSI},
#endif
#if DT_HAS_NODE(DT_NODELABEL(spi2))
#ifdef CONFIG_SPI_STM32_USE_HW_SS
	{STM32_PIN_PB12, STM32F3_PINMUX_FUNC_PB12_SPI2_NSS},
#endif /* CONFIG_SPI_STM32_USE_HW_SS */
	{STM32_PIN_PB13, STM32F3_PINMUX_FUNC_PB13_SPI2_SCK},
	{STM32_PIN_PB14, STM32F3_PINMUX_FUNC_PB14_SPI2_MISO},
	{STM32_PIN_PB15, STM32F3_PINMUX_FUNC_PB15_SPI2_MOSI},
#endif
#ifdef CONFIG_USB_DC_STM32
	{STM32_PIN_PA11, STM32F3_PINMUX_FUNC_PA11_USB_DM},
	{STM32_PIN_PA12, STM32F3_PINMUX_FUNC_PA12_USB_DP},
#endif	/* CONFIG_USB_DC_STM32 */
#ifdef CONFIG_CAN_1
	{STM32_PIN_PD0, STM32F3_PINMUX_FUNC_PD0_CAN1_RX},
	{STM32_PIN_PD1, STM32F3_PINMUX_FUNC_PD1_CAN1_TX},
#endif /* CONFIG_CAN_1 */
};

static int pinmux_stm32_init(struct device *port)
{
	ARG_UNUSED(port);

	stm32_setup_pins(pinconf, ARRAY_SIZE(pinconf));

	return 0;
}

SYS_INIT(pinmux_stm32_init, PRE_KERNEL_1,
		CONFIG_PINMUX_STM32_DEVICE_INITIALIZATION_PRIORITY);
