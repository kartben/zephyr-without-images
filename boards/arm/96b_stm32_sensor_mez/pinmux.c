/*
 * Copyright (c) 2018 Linaro Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <pinmux.h>
#include <sys_io.h>

#include <pinmux/stm32/pinmux_stm32.h>

/* pin assignments for 96b_stm32_sensor_mez board */
static const struct pin_config pinconf[] = {
#ifdef CONFIG_UART_1
	{STM32_PIN_PA9, STM32F4_PINMUX_FUNC_PA9_USART1_TX},
	{STM32_PIN_PA10, STM32F4_PINMUX_FUNC_PA10_USART1_RX},
#endif	/* CONFIG_UART_1 */
#ifdef CONFIG_UART_2
	{STM32_PIN_PD5, STM32F4_PINMUX_FUNC_PD5_USART2_TX},
	{STM32_PIN_PD6, STM32F4_PINMUX_FUNC_PD6_USART2_RX},
#endif	/* CONFIG_UART_2 */
#ifdef CONFIG_UART_3
	{STM32_PIN_PD8, STM32F4_PINMUX_FUNC_PD8_USART3_TX},
	{STM32_PIN_PD9, STM32F4_PINMUX_FUNC_PD9_USART3_RX},
#endif	/* CONFIG_UART_3 */
#ifdef CONFIG_UART_4
	{STM32_PIN_PC10, STM32F4_PINMUX_FUNC_PC10_UART4_TX},
	{STM32_PIN_PC11, STM32F4_PINMUX_FUNC_PC11_UART4_RX},
#endif	/* CONFIG_UART_4 */
#ifdef CONFIG_I2C_1
	{STM32_PIN_PB6, STM32F4_PINMUX_FUNC_PB6_I2C1_SCL},
	{STM32_PIN_PB7, STM32F4_PINMUX_FUNC_PB7_I2C1_SDA},
#endif /* CONFIG_I2C_1 */
#ifdef CONFIG_I2C_2
	{STM32_PIN_PB10, STM32F4_PINMUX_FUNC_PB10_I2C2_SCL},
	{STM32_PIN_PC12, STM32F4_PINMUX_FUNC_PC12_I2C2_SDA},
#endif /* CONFIG_I2C_2 */
#ifdef CONFIG_SPI_1
	{STM32_PIN_PA4, STM32F4_PINMUX_FUNC_PA4_SPI1_NSS |
			STM32_OSPEEDR_VERY_HIGH_SPEED},
	{STM32_PIN_PA5, STM32F4_PINMUX_FUNC_PA5_SPI1_SCK |
			STM32_OSPEEDR_VERY_HIGH_SPEED},
	{STM32_PIN_PA6, STM32F4_PINMUX_FUNC_PA6_SPI1_MISO},
	{STM32_PIN_PA7, STM32F4_PINMUX_FUNC_PA7_SPI1_MOSI},
#endif	/* CONFIG_SPI_1 */
#ifdef CONFIG_SPI_2
	{STM32_PIN_PB9, STM32F4_PINMUX_FUNC_PB9_SPI2_NSS |
			STM32_OSPEEDR_VERY_HIGH_SPEED},
	{STM32_PIN_PD3, STM32F4_PINMUX_FUNC_PD3_SPI2_SCK |
			STM32_OSPEEDR_VERY_HIGH_SPEED},
	{STM32_PIN_PB14, STM32F4_PINMUX_FUNC_PB14_SPI2_MISO},
	{STM32_PIN_PB15, STM32F4_PINMUX_FUNC_PB15_SPI2_MOSI},
#endif	/* CONFIG_SPI_2 */
#ifdef CONFIG_I2S_2
	{STM32_PIN_PC7, STM32F4_PINMUX_FUNC_PC7_I2S2_CK},
	{STM32_PIN_PC1, STM32F4_PINMUX_FUNC_PC1_I2S2_SD},
#endif	/* CONFIG_I2S_2 */
#ifdef CONFIG_PWM_STM32_3
	{ STM32_PIN_PB4, STM32F4_PINMUX_FUNC_PB4_PWM3_CH1 },
	{ STM32_PIN_PC8, STM32F4_PINMUX_FUNC_PC8_PWM3_CH3 },
#endif /* CONFIG_PWM_STM32_3 */
#ifdef CONFIG_PWM_STM32_4
	{ STM32_PIN_PD14, STM32F4_PINMUX_FUNC_PD14_PWM4_CH3 },
	{ STM32_PIN_PD15, STM32F4_PINMUX_FUNC_PD15_PWM4_CH4 },
#endif /* CONFIG_PWM_STM32_4 */
#ifdef CONFIG_PWM_STM32_9
	{ STM32_PIN_PE5, STM32F4_PINMUX_FUNC_PE5_PWM9_CH1 },
	{ STM32_PIN_PE6, STM32F4_PINMUX_FUNC_PE6_PWM9_CH2 },
#endif /* CONFIG_PWM_STM32_9 */
};

static int pinmux_stm32_init(struct device *port)
{
	ARG_UNUSED(port);

	stm32_setup_pins(pinconf, ARRAY_SIZE(pinconf));

	return 0;
}

SYS_INIT(pinmux_stm32_init, PRE_KERNEL_1,
		CONFIG_PINMUX_STM32_DEVICE_INITIALIZATION_PRIORITY);
