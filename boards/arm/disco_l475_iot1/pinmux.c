/*
 * Copyright (c) 2017 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <pinmux.h>
#include <sys_io.h>

#include <pinmux/stm32/pinmux_stm32.h>

/* pin assignments for Disco L475 IOT1 board */
static const struct pin_config pinconf[] = {
#ifdef CONFIG_UART_1
	{STM32_PIN_PB6, STM32L4X_PINMUX_FUNC_PB6_USART1_TX},
	{STM32_PIN_PB7, STM32L4X_PINMUX_FUNC_PB7_USART1_RX},
#endif	/* CONFIG_UART_1 */
#ifdef CONFIG_UART_4
	{STM32_PIN_PA0, STM32L4X_PINMUX_FUNC_PA0_USART4_TX},
	{STM32_PIN_PA1, STM32L4X_PINMUX_FUNC_PA1_USART4_RX},
#endif	/* CONFIG_UART_4 */
#ifdef CONFIG_I2C_1
	{STM32_PIN_PB8, STM32L4X_PINMUX_FUNC_PB8_I2C1_SCL},
	{STM32_PIN_PB9, STM32L4X_PINMUX_FUNC_PB9_I2C1_SDA},
#endif /* CONFIG_I2C_1 */
#ifdef CONFIG_I2C_2
	/* I2C2 is used for NFC, STSAFE, ToF & MEMS sensors */
	{STM32_PIN_PB10, STM32L4X_PINMUX_FUNC_PB10_I2C2_SCL},
	{STM32_PIN_PB11, STM32L4X_PINMUX_FUNC_PB11_I2C2_SDA},
#endif /* CONFIG_I2C_2 */
#ifdef CONFIG_SPI_1
	{STM32_PIN_PA5, STM32L4X_PINMUX_FUNC_PA5_SPI1_SCK},
	{STM32_PIN_PA6, STM32L4X_PINMUX_FUNC_PA6_SPI1_MISO},
	{STM32_PIN_PA7, STM32L4X_PINMUX_FUNC_PA7_SPI1_MOSI},
#endif /* CONFIG_SPI_1 */
#ifdef CONFIG_SPI_3
	/* SPI3 is used for BT/WIFI, Sub GHZ communication */
	{STM32_PIN_PC10, STM32L4X_PINMUX_FUNC_PC10_SPI3_SCK},
	{STM32_PIN_PC11, STM32L4X_PINMUX_FUNC_PC11_SPI3_MISO | \
		STM32_OSPEEDR_VERY_HIGH_SPEED},
	{STM32_PIN_PC12, STM32L4X_PINMUX_FUNC_PC12_SPI3_MOSI},
#endif /* CONFIG_SPI_3 */
#ifdef CONFIG_PWM_STM32_2
	{STM32_PIN_PA15, STM32L4X_PINMUX_FUNC_PA15_PWM2_CH1},
#endif /* CONFIG_PWM_STM32_2 */
};

static int pinmux_stm32_init(struct device *port)
{
	ARG_UNUSED(port);

	stm32_setup_pins(pinconf, ARRAY_SIZE(pinconf));

	return 0;
}

SYS_INIT(pinmux_stm32_init, PRE_KERNEL_1,
	 CONFIG_PINMUX_STM32_DEVICE_INITIALIZATION_PRIORITY);
