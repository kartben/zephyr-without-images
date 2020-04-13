/*
 * Copyright (c) 2016 Open-RnD Sp. z o.o.
 * Copyright (c) 2016 BayLibre, SAS
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <drivers/pinmux.h>
#include <sys/sys_io.h>

#include <pinmux/stm32/pinmux_stm32.h>

/* pin assignments for STM32L476G-DISCO board */
static const struct pin_config pinconf[] = {
#ifdef CONFIG_UART_1
	{STM32_PIN_PB6,  STM32L4X_PINMUX_FUNC_PB6_USART1_TX},
	{STM32_PIN_PG10, STM32L4X_PINMUX_FUNC_PG10_USART1_RX},
#endif	/* CONFIG_UART_1 */
#ifdef CONFIG_UART_2
	{STM32_PIN_PA2, STM32L4X_PINMUX_FUNC_PA2_USART2_TX},
	{STM32_PIN_PD6, STM32L4X_PINMUX_FUNC_PD6_USART2_RX},
#endif	/* CONFIG_UART_2 */
#ifdef CONFIG_LPUART_1
	{STM32_PIN_PG7, STM32L4X_PINMUX_FUNC_PG7_LPUART1_TX},
	{STM32_PIN_PG8, STM32L4X_PINMUX_FUNC_PG8_LPUART1_RX},
#endif /* CONFIG_LPUART_1 */
#if DT_HAS_NODE(DT_NODELABEL(i2c1))
	{STM32_PIN_PB8, STM32L4X_PINMUX_FUNC_PB8_I2C1_SCL},
	{STM32_PIN_PB7, STM32L4X_PINMUX_FUNC_PB7_I2C1_SDA},
#endif
#ifdef CONFIG_SPI_1
	{STM32_PIN_PA5, STM32L4X_PINMUX_FUNC_PA5_SPI1_SCK},
	{STM32_PIN_PB4, STM32L4X_PINMUX_FUNC_PB4_SPI1_MISO},
	{STM32_PIN_PB5, STM32L4X_PINMUX_FUNC_PB5_SPI1_MOSI},
#endif /* CONFIG_SPI_1 */
#ifdef CONFIG_PWM_STM32_2
	{STM32_PIN_PA0, STM32L4X_PINMUX_FUNC_PA0_PWM2_CH1},
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
