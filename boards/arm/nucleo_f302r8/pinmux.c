/*
 * Copyright (c) 2018 Seitz & Associates
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <pinmux.h>
#include <sys_io.h>

#include <pinmux/stm32/pinmux_stm32.h>

/* pin assignments for NUCLEO-F302R8 board */
static const struct pin_config pinconf[] = {
#ifdef CONFIG_UART_1
	{STM32_PIN_PA9,  STM32F3_PINMUX_FUNC_PA9_USART1_TX},
	{STM32_PIN_PA10, STM32F3_PINMUX_FUNC_PA10_USART1_RX},
#endif	/* CONFIG_UART_1 */
#ifdef CONFIG_UART_2
	{STM32_PIN_PA2, STM32F3_PINMUX_FUNC_PA2_USART2_TX},
	{STM32_PIN_PA3, STM32F3_PINMUX_FUNC_PA3_USART2_RX},
#endif	/* CONFIG_UART_2 */
#ifdef CONFIG_UART_3
	{STM32_PIN_PC10, STM32F3_PINMUX_FUNC_PC10_USART3_TX},
	{STM32_PIN_PC11, STM32F3_PINMUX_FUNC_PC11_USART3_RX},
#endif	/* CONFIG_UART_3 */
#ifdef CONFIG_I2C_1
	{STM32_PIN_PB8, STM32F3_PINMUX_FUNC_PB8_I2C1_SCL},
	{STM32_PIN_PB9, STM32F3_PINMUX_FUNC_PB9_I2C1_SDA},
#endif /* CONFIG_I2C_1 */
#ifdef CONFIG_SPI_2
	{STM32_PIN_PB12, STM32F3_PINMUX_FUNC_PB12_SPI2_NSS},
	{STM32_PIN_PB13, STM32F3_PINMUX_FUNC_PB13_SPI2_SCK},
	{STM32_PIN_PB14, STM32F3_PINMUX_FUNC_PB14_SPI2_MISO},
	{STM32_PIN_PB15, STM32F3_PINMUX_FUNC_PB15_SPI2_MOSI},
#endif /* CONFIG_SPI_2 */
#ifdef CONFIG_PWM_STM32_2
	{STM32_PIN_PA0, STM32F3_PINMUX_FUNC_PA0_PWM2_CH1},
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
