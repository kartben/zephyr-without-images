/*
 * Copyright (c) 2019 Linaro Limited
 * Copyright (c) 2020 Teslabs Engineering S.L.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_PINMUX_STM32_PINMUX_STM32H7_H_
#define ZEPHYR_DRIVERS_PINMUX_STM32_PINMUX_STM32H7_H_

/**
 * @file Header for STM32H7 pin multiplexing helper
 */

/* Port A */
#define STM32H7_PINMUX_FUNC_PA0_PWM2_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA0_PWM5_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA0_USART2_CTS __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA0_UART4_TX __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA0_ADC1_INP16 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PA0_C_ADC12_INN1 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PA0_C_ADC12_INP0 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE

#define STM32H7_PINMUX_FUNC_PA1_PWM2_CH2 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA1_PWM5_CH2 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA1_PWM15_CH1N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA1_USART2_RTS __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA1_UART4_RX __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)
#define STM32H7_PINMUX_FUNC_PA1_ADC1_INN16 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PA1_ADC1_INP17 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PA1_C_ADC12_INP1 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PA1_ETH_REF_CLK __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_11 | STM32_PUSHPULL_NOPULL | \
	 STM32_OSPEEDR_VERY_HIGH_SPEED)

#define STM32H7_PINMUX_FUNC_PA2_PWM2_CH3 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA2_PWM5_CH3 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA2_PWM15_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA2_USART2_TX __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA2_ADC12_INP14 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PA2_ETH_MDIO __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_11 | STM32_PUSHPULL_NOPULL | \
	 STM32_OSPEEDR_VERY_HIGH_SPEED)

#define STM32H7_PINMUX_FUNC_PA3_PWM2_CH4 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA3_PWM5_CH4 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA3_PWM15_CH2 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA3_USART2_RX __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)
#define STM32H7_PINMUX_FUNC_PA3_ADC12_INP15 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE

#define STM32H7_PINMUX_FUNC_PA4_ADC12_INP18 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE

#define STM32H7_PINMUX_FUNC_PA5_PWM2_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA5_PWM8_CH1N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA5_ADC12_INN18 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PA5_ADC12_INP19 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE

#define STM32H7_PINMUX_FUNC_PA6_PWM3_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA6_PWM13_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_9 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA6_ADC12_INP3 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE

#define STM32H7_PINMUX_FUNC_PA7_PWM1_CH1N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA7_PWM3_CH2 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA7_PWM8_CH1N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA7_PWM14_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_9 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA7_ADC12_INN3 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PA7_ADC12_INP7 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PA7_ETH_CRS_DV __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_11 | STM32_PUSHPULL_NOPULL | \
	 STM32_OSPEEDR_VERY_HIGH_SPEED)

#define STM32H7_PINMUX_FUNC_PA8_PWM1_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA8_I2C3_SCL __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

#define STM32H7_PINMUX_FUNC_PA9_PWM1_CH2 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA9_USART1_TX __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA9_SPI2_SCK __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PA10_PWM1_CH3 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA10_USART1_RX __DEPRECATED_MACRO  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PA11_PWM1_CH4 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA11_UART4_RX __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_6 | STM32_PUSHPULL_NOPULL)
#define STM32H7_PINMUX_FUNC_PA11_USART1_CTS __DEPRECATED_MACRO  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PA12_UART4_RX __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_6 | STM32_PUSHPULL_NOPULL)
#define STM32H7_PINMUX_FUNC_PA12_USART1_RTS __DEPRECATED_MACRO  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PA15_PWM2_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA15_USART4_RTS __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

/* Port B */
#define STM32H7_PINMUX_FUNC_PB0_PWM1_CH2N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PB0_PWM3_CH3 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PB0_PWM8_CH2N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PB0_ADC12_INN5 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PB0_ADC12_INP9 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE

#define STM32H7_PINMUX_FUNC_PB1_PWM1_CH3N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PB1_PWM3_CH4 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PB1_PWM8_CH3N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PB1_ADC12_INP5 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE

#define STM32H7_PINMUX_FUNC_PB3_PWM2_CH2 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PB4_PWM3_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PB5_PWM3_CH2 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PB6_PWM16_CH1N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PB6_PWM4_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PB6_I2C1_SCL __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32H7_PINMUX_FUNC_PB6_I2C4_SCL __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_6 | STM32_OPENDRAIN_PULLUP)
#define STM32H7_PINMUX_FUNC_PB6_USART1_TX __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PB6_LPUART1_TX __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_OPENDRAIN_PULLUP)

#define STM32H7_PINMUX_FUNC_PB7_PWM17_CH1N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PB7_PWM4_CH2 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PB7_I2C1_SDA __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32H7_PINMUX_FUNC_PB7_I2C4_SDA __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_6 | STM32_OPENDRAIN_PULLUP)
#define STM32H7_PINMUX_FUNC_PB7_USART1_RX __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)
#define STM32H7_PINMUX_FUNC_PB7_LPUART1_RX __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PB8_PWM16_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PB8_PWM4_CH3 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PB8_I2C1_SCL __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32H7_PINMUX_FUNC_PB8_I2C4_SCL __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_6 | STM32_OPENDRAIN_PULLUP)

#define STM32H7_PINMUX_FUNC_PB9_PWM17_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PB9_PWM4_CH4 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PB9_I2C1_SDA __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32H7_PINMUX_FUNC_PB9_I2C4_SDA __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_6 | STM32_OPENDRAIN_PULLUP)

#define STM32H7_PINMUX_FUNC_PB10_PWM2_CH3 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PB10_I2C2_SCL __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32H7_PINMUX_FUNC_PB10_USART3_TX __DEPRECATED_MACRO  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PB11_PWM2_CH4 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PB11_I2C2_SDA __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32H7_PINMUX_FUNC_PB11_USART3_RX __DEPRECATED_MACRO	\
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PB13_PWM1_CH1N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PB12_UART5_RX __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_14 | STM32_OPENDRAIN_PULLUP)
#define STM32H7_PINMUX_FUNC_PB13_UART5_TX __DEPRECATED_MACRO	\
	(STM32_PINMUX_ALT_FUNC_14 | STM32_PUSHPULL_NOPULL)
#define STM32H7_PINMUX_FUNC_PB13_ETH_TXD1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_11 | STM32_PUSHPULL_NOPULL | \
	 STM32_OSPEEDR_VERY_HIGH_SPEED)

#define STM32H7_PINMUX_FUNC_PB14_PWM1_CH2N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PB14_PWM12_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PB14_PWM8_CH2N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PB14_UART3_RTS __DEPRECATED_MACRO	\
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PB15_PWM1_CH3N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PB15_PWM12_CH2 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PB15_PWM8_CH3N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_PULLUP)

/* Port C */
#define STM32H7_PINMUX_FUNC_PC0_ADC123_INP10 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE

#define STM32H7_PINMUX_FUNC_PC1_ADC123_INN10 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PC1_ADC123_INP11 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PC1_ETH_MDC __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_11 | STM32_PUSHPULL_NOPULL | \
	 STM32_OSPEEDR_VERY_HIGH_SPEED)

#define STM32H7_PINMUX_FUNC_PC2_ADC123_INN11 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PC2_ADC123_INP12 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PC2_C_ADC3_INN1 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PC2_C_ADC3_INP0 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE

#define STM32H7_PINMUX_FUNC_PC3_ADC12_INN12 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PC3_ADC12_INP13 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PC3_C_ADC3_INP1 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE

#define STM32H7_PINMUX_FUNC_PC4_ADC12_INP4 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PC4_ETH_RXD0 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_11 | STM32_PUSHPULL_NOPULL | \
	 STM32_OSPEEDR_VERY_HIGH_SPEED)

#define STM32H7_PINMUX_FUNC_PC5_ADC12_INN4 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PC5_ADC12_INP8 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PC5_ETH_RXD1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_11 | STM32_PUSHPULL_NOPULL | \
	 STM32_OSPEEDR_VERY_HIGH_SPEED)

#define STM32H7_PINMUX_FUNC_PC6_PWM3_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PC6_PWM8_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PC6_USART6_TX __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PC7_PWM3_CH2 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PC7_PWM8_CH2 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PC7_USART6_RX __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PC8_PWM3_CH3 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PC8_PWM8_CH3 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PC8_UART5_RTS __DEPRECATED_MACRO  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PC9_PWM3_CH4 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PC9_PWM8_CH4 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PC9_I2C3_SDA __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32H7_PINMUX_FUNC_PC9_UART5_CTS __DEPRECATED_MACRO  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PC10_USART3_TX __DEPRECATED_MACRO  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PC10_UART4_TX __DEPRECATED_MACRO  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PC11_USART3_RX __DEPRECATED_MACRO  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)
#define STM32H7_PINMUX_FUNC_PC11_UART4_RX __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PC12_UART5_TX __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

/* Port D */
#define STM32H7_PINMUX_FUNC_PD2_UART5_RX __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PD3_USART2_CTS __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PD4_USART2_RTS __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PD5_USART2_TX __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PD6_USART2_RX __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PD8_USART3_TX __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PD9_USART3_RX __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PD11_USART3_CTS __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PD12_PWM4_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PD12_I2C4_SCL __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32H7_PINMUX_FUNC_PD12_USART3_RTS __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PD13_PWM4_CH2 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PD13_I2C4_SDA __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

#define STM32H7_PINMUX_FUNC_PD14_PWM4_CH3 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PD14_UART8_CTS __DEPRECATED_MACRO  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PD15_PWM4_CH4 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PD15_UART8_RTS __DEPRECATED_MACRO  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

/* Port E */
#define STM32H7_PINMUX_FUNC_PE0_UART8_RX __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PE1_UART8_TX __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PE4_PWM15_CH1N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PE5_PWM15_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PE6_PWM15_CH2 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PE7_UART7_RX __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PE8_PWM1_CH1N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PE8_UART7_TX __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PE9_PWM1_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PE9_UART7_RTS __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PE10_PWM1_CH2N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PE10_UART7_CTS __DEPRECATED_MACRO  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PE11_PWM1_CH2 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PE12_PWM1_CH3N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PE13_PWM1_CH3 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PE14_PWM1_CH4 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)

/* Port F */
#define STM32H7_PINMUX_FUNC_PF0_I2C2_SDA __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

#define STM32H7_PINMUX_FUNC_PF1_I2C2_SCL __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

#define STM32H7_PINMUX_FUNC_PF3_ADC3_INP5 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE

#define STM32H7_PINMUX_FUNC_PF4_ADC3_INN5 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PF4_ADC3_INP9 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE

#define STM32H7_PINMUX_FUNC_PF5_ADC3_INP4 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE

#define STM32H7_PINMUX_FUNC_PF6_PWM16_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PF6_UART7_RX __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)
#define STM32H7_PINMUX_FUNC_PF6_ADC3_INN4 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PF6_ADC3_INP8 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE

#define STM32H7_PINMUX_FUNC_PF7_PWM17_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PF7_UART7_TX __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PF7_ADC3_INP3 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE

#define STM32H7_PINMUX_FUNC_PF8_PWM16_CH1N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PF8_UART7_RTS __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PF8_PWM13_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_9 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PF8_ADC3_INN3 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PF8_ADC3_INP7 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE

#define STM32H7_PINMUX_FUNC_PF9_PWM17_CH1N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PF9_UART7_CTS __DEPRECATED_MACRO    \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PF9_PWM14_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_9 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PF9_ADC3_INP2 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE

#define STM32H7_PINMUX_FUNC_PF10_ADC3_INN2 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PF10_ADC3_INP6 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE

#define STM32H7_PINMUX_FUNC_PF11_ADC1_INP2 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE

#define STM32H7_PINMUX_FUNC_PF12_ADC1_INN2 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PF12_ADC1_INP6 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE

#define STM32H7_PINMUX_FUNC_PF13_ADC1_INP2 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE

#define STM32H7_PINMUX_FUNC_PF14_I2C4_SCL __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32H7_PINMUX_FUNC_PF14_ADC2_INN2 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PF14_ADC2_INP6 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE

#define STM32H7_PINMUX_FUNC_PF15_I2C4_SDA __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

/* Port G */
#define STM32H7_PINMUX_FUNC_PG8_USART6_RTS __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PG9_USART6_RX __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PG11_ETH_TX_EN __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_11 | STM32_PUSHPULL_NOPULL | \
	 STM32_OSPEEDR_VERY_HIGH_SPEED)

#define STM32H7_PINMUX_FUNC_PG12_USART6_RTS __DEPRECATED_MACRO  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PG13_USART6_CTS __DEPRECATED_MACRO  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PG13_ETH_TXD0 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_11 | STM32_PUSHPULL_NOPULL | \
	 STM32_OSPEEDR_VERY_HIGH_SPEED)

#define STM32H7_PINMUX_FUNC_PG14_USART6_TX __DEPRECATED_MACRO  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PG15_USART6_CTS __DEPRECATED_MACRO  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

/* Port H */
#define STM32H7_PINMUX_FUNC_PH3_ADC3_INN13 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PH3_ADC3_INP14 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE

#define STM32H7_PINMUX_FUNC_PH4_I2C2_SCL __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32H7_PINMUX_FUNC_PH4_ADC3_INN14 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PH4_ADC3_INP15 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE

#define STM32H7_PINMUX_FUNC_PH5_I2C2_SDA __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32H7_PINMUX_FUNC_PH5_ADC3_INN15 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE
#define STM32H7_PINMUX_FUNC_PH5_ADC3_INP16 __DEPRECATED_MACRO \
	STM32_MODER_ANALOG_MODE

#define STM32H7_PINMUX_FUNC_PH6_PWM12_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PH7_I2C3_SCL __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

#define STM32H7_PINMUX_FUNC_PH8_I2C3_SDA __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

#define STM32H7_PINMUX_FUNC_PH9_PWM12_CH2 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PH10_PWM5_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PH11_PWM5_CH2 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PH11_I2C4_SCL __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

#define STM32H7_PINMUX_FUNC_PH12_PWM5_CH3 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PH12_I2C4_SDA __DEPRECATED_MACRO   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

#define STM32H7_PINMUX_FUNC_PH13_PWM8_CH1N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PH14_PWM8_CH2N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PH13_PWM8_CH3N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_PULLUP)

/* Port I */
#define STM32H7_PINMUX_FUNC_PI0_PWM5_CH4 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_2 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PI2_PWM8_CH4 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PI5_PWM8_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PI6_PWM8_CH2 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PI7_PWM8_CH3 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_PULLUP)

/* Port J */
#define STM32H7_PINMUX_FUNC_PJ6_PWM8_CH2 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PJ7_PWM8_CH2N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PJ8_PWM1_CH3N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PJ8_PWM8_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PJ8_UART8_TX __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PJ9_PWM1_CH3 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PJ9_PWM8_CH1N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PJ9_UART8_RX __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PJ10_PWM1_CH2N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PJ10_PWM8_CH2 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PJ11_PWM1_CH2 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PJ11_PWM8_CH2N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_PULLUP)

/* Port K */
#define STM32H7_PINMUX_FUNC_PK0_PWM1_CH1N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PK0_PWM8_CH3 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PK1_PWM1_CH1 __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PK1_PWM8_CH3N __DEPRECATED_MACRO \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_PULLUP)

#endif /* ZEPHYR_DRIVERS_PINMUX_STM32_PINMUX_STM32H7_H_ */
