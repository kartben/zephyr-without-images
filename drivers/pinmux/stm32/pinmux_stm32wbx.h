/*
 * Copyright (c) 2018 Linaro Limited
 * Copyright (c) 2019 Centaur Analytics, Inc
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _STM32WBX_PINMUX_H_
#define _STM32WBX_PINMUX_H_

/**
 * @file Header for STM32WBX pin multiplexing helper
 */

/* Port A */
/* ADC1 */
#define STM32WBX_PINMUX_FUNC_PA0_ADC1_IN5 STM32_MODER_ANALOG_MODE
#define STM32WBX_PINMUX_FUNC_PA1_ADC1_IN6 STM32_MODER_ANALOG_MODE
#define STM32WBX_PINMUX_FUNC_PA2_ADC1_IN7 STM32_MODER_ANALOG_MODE
#define STM32WBX_PINMUX_FUNC_PA3_ADC1_IN8 STM32_MODER_ANALOG_MODE
#define STM32WBX_PINMUX_FUNC_PA4_ADC1_IN9 STM32_MODER_ANALOG_MODE
#define STM32WBX_PINMUX_FUNC_PA5_ADC1_IN10 STM32_MODER_ANALOG_MODE
#define STM32WBX_PINMUX_FUNC_PA6_ADC1_IN11 STM32_MODER_ANALOG_MODE
#define STM32WBX_PINMUX_FUNC_PA7_ADC1_IN12 STM32_MODER_ANALOG_MODE
#define STM32WBX_PINMUX_FUNC_PA8_ADC1_IN15 STM32_MODER_ANALOG_MODE
#define STM32WBX_PINMUX_FUNC_PA9_ADC1_IN16 STM32_MODER_ANALOG_MODE

#define STM32WBX_PINMUX_FUNC_PA2_LPUART1_TX  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)
#define STM32WBX_PINMUX_FUNC_PA3_LPUART1_RX  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PA9_USART1_TX  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32WBX_PINMUX_FUNC_PA10_USART1_RX  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUPDR_NO_PULL)
#define STM32WBX_PINMUX_FUNC_PA12_LPUART1_RX  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)

/* SPI1 */
#define STM32WBX_PINMUX_FUNC_PA1_SPI1_SCK \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PA4_SPI1_NSS \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PA5_SPI1_SCK \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PA6_SPI1_MISO \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUPDR_PULL_DOWN)
#define STM32WBX_PINMUX_FUNC_PA7_SPI1_MOSI \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUPDR_PULL_DOWN)
#define STM32WBX_PINMUX_FUNC_PA11_SPI1_MISO \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUPDR_PULL_DOWN)
#define STM32WBX_PINMUX_FUNC_PA12_SPI1_MOSI \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUPDR_PULL_DOWN)
#define STM32WBX_PINMUX_FUNC_PA15_SPI1_NSS \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)

 /* SPI2 */
#define STM32WBX_PINMUX_FUNC_PA9_SPI2_SCK \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)

/* Timer 1 */
#define STM32WBX_PINMUX_FUNC_PA8_TMR1_CH1 \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PA9_TMR1_CH2 \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PA10_TMR1_CH3 \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PA11_TMR1_CH4 \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_NOPULL)

/* Timer 2 */
#define STM32WBX_PINMUX_FUNC_PA0_TMR2_CH1 \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PA1_TMR2_CH2 \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PA2_TMR2_CH3 \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PA3_TMR2_CH4 \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PA5_TMR2_CH1 \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PA15_TMR2_CH1 \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_NOPULL)

/* Timer 16 */
#define STM32WBX_PINMUX_FUNC_PA6_TMR16_CH1 \
	(STM32_PINMUX_ALT_FUNC_14 | STM32_PUSHPULL_NOPULL)

/* Timer 17 */
#define STM32WBX_PINMUX_FUNC_PA7_TMR17_CH1 \
	(STM32_PINMUX_ALT_FUNC_14 | STM32_PUSHPULL_NOPULL)

/* Port B */
#define STM32WBX_PINMUX_FUNC_PB5_LPUART1_TX  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)
#define STM32WBX_PINMUX_FUNC_PB6_USART1_TX  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32WBX_PINMUX_FUNC_PB7_USART1_RX  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUPDR_NO_PULL)
#define STM32WBX_PINMUX_FUNC_PB8_I2C1_SCL  \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32WBX_PINMUX_FUNC_PB9_I2C1_SDA  \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32WBX_PINMUX_FUNC_PB10_LPUART1_RX  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PB11_LPUART1_TX  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

/* SPI1 */
#define STM32WBX_PINMUX_FUNC_PB2_SPI1_NSS  \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PB3_SPI1_SCK  \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PB4_SPI1_MISO \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUPDR_PULL_DOWN)
#define STM32WBX_PINMUX_FUNC_PB5_SPI1_MOSI \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUPDR_PULL_DOWN)

 /* SPI2 */
#define STM32WBX_PINMUX_FUNC_PB9_SPI2_NSS   \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PB10_SPI2_SCK  \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PB12_SPI2_NSS  \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PB13_SPI2_SCK  \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PB14_SPI2_MISO \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUPDR_PULL_DOWN)
#define STM32WBX_PINMUX_FUNC_PB15_SPI2_MOSI \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUPDR_PULL_DOWN)

/* Timer 2 */
#define STM32WBX_PINMUX_FUNC_PB3_TMR2_CH2 \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PB10_TMR2_CH3 \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PB11_TMR2_CH4 \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_NOPULL)

/* Timer 16 */
#define STM32WBX_PINMUX_FUNC_PB8_TMR16_CH1 \
	(STM32_PINMUX_ALT_FUNC_14 | STM32_PUSHPULL_NOPULL)

/* Timer 17 */
#define STM32WBX_PINMUX_FUNC_PB9_TMR17_CH1 \
	(STM32_PINMUX_ALT_FUNC_14 | STM32_PUSHPULL_NOPULL)

/* Port C */
/* ADC1 */
#define STM32WBX_PINMUX_FUNC_PC0_ADC1_IN1 STM32_MODER_ANALOG_MODE
#define STM32WBX_PINMUX_FUNC_PC1_ADC1_IN2 STM32_MODER_ANALOG_MODE
#define STM32WBX_PINMUX_FUNC_PC2_ADC1_IN3 STM32_MODER_ANALOG_MODE
#define STM32WBX_PINMUX_FUNC_PC3_ADC1_IN4 STM32_MODER_ANALOG_MODE
#define STM32WBX_PINMUX_FUNC_PC4_ADC1_IN13 STM32_MODER_ANALOG_MODE
#define STM32WBX_PINMUX_FUNC_PC5_ADC1_IN14 STM32_MODER_ANALOG_MODE

#define STM32WBX_PINMUX_FUNC_PC0_LPUART1_RX  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PC1_LPUART1_TX  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)
#define STM32WBX_PINMUX_FUNC_PC0_I2C3_SCL  \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32WBX_PINMUX_FUNC_PC1_I2C3_SDA  \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

/* SPI2 */
#define STM32WBX_PINMUX_FUNC_PC1_SPI2_MOSI \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUPDR_PULL_DOWN)
#define STM32WBX_PINMUX_FUNC_PC2_SPI2_MISO \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUPDR_PULL_DOWN)
#define STM32WBX_PINMUX_FUNC_PC3_SPI2_MOSI \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUPDR_PULL_DOWN)

/* Port D */
/* SPI2 */
#define STM32WBX_PINMUX_FUNC_PD0_SPI2_NSS \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PD1_SPI2_SCK \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PD3_SPI2_SCK \
	(STM32_PINMUX_ALT_FUNC_3 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PD3_SPI2_MISO \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUPDR_PULL_DOWN)
#define STM32WBX_PINMUX_FUNC_PD4_SPI2_MOSI \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUPDR_PULL_DOWN)

/* Timer 1 */
#define STM32WBX_PINMUX_FUNC_PD14_TMR1_CH1 \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_NOPULL)
#define STM32WBX_PINMUX_FUNC_PD15_TMR1_CH2 \
	(STM32_PINMUX_ALT_FUNC_1 | STM32_PUSHPULL_NOPULL)

/* Port E */

/* Port H */

#endif /* _STM32WBX_PINMUX_H_ */
