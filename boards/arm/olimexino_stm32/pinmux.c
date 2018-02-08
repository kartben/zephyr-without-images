/*
 * Copyright (c) 2016 Open-RnD Sp. z o.o.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <pinmux.h>
#include <sys_io.h>

#include <pinmux/stm32/pinmux_stm32.h>

/* pin assignments for NUCLEO-F103RB board */
static const struct pin_config pinconf[] = {
#ifdef CONFIG_UART_STM32_PORT_1
	{STM32_PIN_PA9,  STM32F1_PINMUX_FUNC_PA9_USART1_TX},
	{STM32_PIN_PA10, STM32F1_PINMUX_FUNC_PA10_USART1_RX},
#endif	/* CONFIG_UART_STM32_PORT_2 */
#ifdef CONFIG_UART_STM32_PORT_2
	{STM32_PIN_PA2, STM32F1_PINMUX_FUNC_PA2_USART2_TX},
	{STM32_PIN_PA3, STM32F1_PINMUX_FUNC_PA3_USART2_RX},
#endif	/* CONFIG_UART_STM32_PORT_2 */
#ifdef CONFIG_UART_STM32_PORT_3
	{STM32_PIN_PB10, STM32F1_PINMUX_FUNC_PB10_USART3_TX},
	{STM32_PIN_PB11, STM32F1_PINMUX_FUNC_PB11_USART3_RX},
#endif	/* CONFIG_UART_STM32_PORT_3 */
#ifdef CONFIG_I2C_2
	{STM32_PIN_PB10, STM32F1_PINMUX_FUNC_PB10_I2C2_SCL},
	{STM32_PIN_PB11, STM32F1_PINMUX_FUNC_PB11_I2C2_SDA},
#endif /* CONFIG_I2C_2 */
#ifdef CONFIG_SPI_1
	{STM32_PIN_PA4, STM32F1_PINMUX_FUNC_PA4_SPI1_MASTER_NSS_OE},
	{STM32_PIN_PA5, STM32F1_PINMUX_FUNC_PA5_SPI1_MASTER_SCK},
	{STM32_PIN_PA6, STM32F1_PINMUX_FUNC_PA6_SPI1_MASTER_MISO},
	{STM32_PIN_PA7, STM32F1_PINMUX_FUNC_PA7_SPI1_MASTER_MOSI},
#endif
#ifdef CONFIG_PWM_STM32_1
	{STM32_PIN_PA8, STM32F1_PINMUX_FUNC_PA8_PWM1_CH1},
#endif /* CONFIG_PWM_STM32_1 */
};

static int pinmux_stm32_init(struct device *port)
{
	ARG_UNUSED(port);

	stm32_setup_pins(pinconf, ARRAY_SIZE(pinconf));

	return 0;
}

SYS_INIT(pinmux_stm32_init, PRE_KERNEL_1, CONFIG_PINMUX_STM32_DEVICE_INITIALIZATION_PRIORITY);
