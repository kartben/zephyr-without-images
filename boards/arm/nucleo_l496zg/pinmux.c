/*
 * Copyright (c) 2018 Centaur Analytics, Inc
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <pinmux.h>
#include <sys_io.h>

#include <pinmux/stm32/pinmux_stm32.h>

/* pin assignments for NUCLEO-L496ZG board */
static const struct pin_config pinconf[] = {
#ifdef CONFIG_UART_2
	{STM32_PIN_PD5, STM32L4X_PINMUX_FUNC_PD5_USART2_TX},
	{STM32_PIN_PD6, STM32L4X_PINMUX_FUNC_PD6_USART2_RX},
#endif /* CONFIG_UART_2 */
#ifdef CONFIG_LPUART_1
	{STM32_PIN_PG7, STM32L4X_PINMUX_FUNC_PG7_LPUART1_TX},
	{STM32_PIN_PG8, STM32L4X_PINMUX_FUNC_PG8_LPUART1_RX},
#endif  /* CONFIG_LPUART_1 */
#ifdef CONFIG_PWM_STM32_1
	{STM32_PIN_PE9, STM32L4X_PINMUX_FUNC_PE9_PWM1_CH1},
	{STM32_PIN_PE11, STM32L4X_PINMUX_FUNC_PE11_PWM1_CH2},
	{STM32_PIN_PE13, STM32L4X_PINMUX_FUNC_PE13_PWM1_CH3},
#endif /* CONFIG_PWM_STM32_1 */
#ifdef CONFIG_PWM_STM32_2
	{STM32_PIN_PA0, STM32L4X_PINMUX_FUNC_PA0_PWM2_CH1},
#endif /* CONFIG_PWM_STM32_2 */
#ifdef CONFIG_PWM_STM32_15
	{STM32_PIN_PB14, STM32L4X_PINMUX_FUNC_PB14_PWM15_CH1},
#endif /* CONFIG_PWM_STM32_15 */
};

static int pinmux_stm32_init(struct device *port)
{
	ARG_UNUSED(port);

	stm32_setup_pins(pinconf, ARRAY_SIZE(pinconf));

	return 0;
}

SYS_INIT(pinmux_stm32_init, PRE_KERNEL_1,
	 CONFIG_PINMUX_STM32_DEVICE_INITIALIZATION_PRIORITY);
