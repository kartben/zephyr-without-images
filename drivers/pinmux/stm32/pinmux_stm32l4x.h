/*
 * Copyright (c) 2016 Open-RnD Sp. z o.o.
 * Copyright (c) 2016 BayLibre, SAS
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _STM32L4X_PINMUX_H_
#define _STM32L4X_PINMUX_H_

/**
 * @file Header for STM32L4X pin multiplexing helper
 */

/* Port A */
#define STM32L4X_PINMUX_FUNC_PA0_PWM2_CH1 STM32_PINMUX_FUNC_ALT_1
#define STM32L4X_PINMUX_FUNC_PA2_USART2_TX STM32_PINMUX_FUNC_ALT_7
#define STM32L4X_PINMUX_FUNC_PA3_USART2_RX STM32_PINMUX_FUNC_ALT_7
#define STM32L4X_PINMUX_FUNC_PA4_SPI1_NSS STM32_PINMUX_FUNC_ALT_5
#define STM32L4X_PINMUX_FUNC_PA5_SPI1_SCK STM32_PINMUX_FUNC_ALT_5
#define STM32L4X_PINMUX_FUNC_PA6_SPI1_MISO STM32_PINMUX_FUNC_ALT_5
#define STM32L4X_PINMUX_FUNC_PA7_SPI1_MOSI STM32_PINMUX_FUNC_ALT_5
#define STM32L4X_PINMUX_FUNC_PA9_USART1_TX STM32_PINMUX_FUNC_ALT_7
#define STM32L4X_PINMUX_FUNC_PA10_USART1_RX STM32_PINMUX_FUNC_ALT_7
#define STM32L4X_PINMUX_FUNC_PA15_PWM2_CH1 STM32_PINMUX_FUNC_ALT_1
#define STM32L4X_PINMUX_FUNC_PA15_USART2_RX STM32_PINMUX_FUNC_ALT_3
#define STM32L4X_PINMUX_FUNC_PA15_SPI3_NSS STM32_PINMUX_FUNC_ALT_6

/* Port B */
#define STM32L4X_PINMUX_FUNC_PB3_SPI1_SCK STM32_PINMUX_FUNC_ALT_5
#define STM32L4X_PINMUX_FUNC_PB3_SPI3_SCK STM32_PINMUX_FUNC_ALT_6
#define STM32L4X_PINMUX_FUNC_PB4_SPI3_MISO STM32_PINMUX_FUNC_ALT_6
#define STM32L4X_PINMUX_FUNC_PB5_SPI3_MOSI STM32_PINMUX_FUNC_ALT_6
#define STM32L4X_PINMUX_FUNC_PB6_I2C1_SCL STM32_PINMUX_FUNC_ALT_4
#define STM32L4X_PINMUX_FUNC_PB6_USART1_TX STM32_PINMUX_FUNC_ALT_7
#define STM32L4X_PINMUX_FUNC_PB7_I2C1_SDA STM32_PINMUX_FUNC_ALT_4
#define STM32L4X_PINMUX_FUNC_PB7_USART1_RX STM32_PINMUX_FUNC_ALT_7
#define STM32L4X_PINMUX_FUNC_PB8_I2C1_SCL STM32_PINMUX_FUNC_ALT_4
#define STM32L4X_PINMUX_FUNC_PB9_I2C1_SDA STM32_PINMUX_FUNC_ALT_4
#define STM32L4X_PINMUX_FUNC_PB10_I2C2_SCL STM32_PINMUX_FUNC_ALT_4
#define STM32L4X_PINMUX_FUNC_PB10_USART3_TX STM32_PINMUX_FUNC_ALT_7
#define STM32L4X_PINMUX_FUNC_PB11_I2C2_SDA STM32_PINMUX_FUNC_ALT_4
#define STM32L4X_PINMUX_FUNC_PB11_USART3_RX STM32_PINMUX_FUNC_ALT_7
#define STM32L4X_PINMUX_FUNC_PB12_SPI2_NSS STM32_PINMUX_FUNC_ALT_5
#define STM32L4X_PINMUX_FUNC_PB13_I2C2_SCL STM32_PINMUX_FUNC_ALT_4
#define STM32L4X_PINMUX_FUNC_PB13_SPI2_SCK STM32_PINMUX_FUNC_ALT_5
#define STM32L4X_PINMUX_FUNC_PB14_I2C2_SDA STM32_PINMUX_FUNC_ALT_4
#define STM32L4X_PINMUX_FUNC_PB14_SPI2_MISO STM32_PINMUX_FUNC_ALT_5
#define STM32L4X_PINMUX_FUNC_PB15_SPI2_MOSI STM32_PINMUX_FUNC_ALT_5

/* Port C */
#define STM32L4X_PINMUX_FUNC_PC0_I2C3_SCL STM32_PINMUX_FUNC_ALT_4
#define STM32L4X_PINMUX_FUNC_PC1_I2C3_SDA STM32_PINMUX_FUNC_ALT_4
#define STM32L4X_PINMUX_FUNC_PC4_USART3_TX STM32_PINMUX_FUNC_ALT_7
#define STM32L4X_PINMUX_FUNC_PC5_USART3_RX STM32_PINMUX_FUNC_ALT_7
#define STM32L4X_PINMUX_FUNC_PC10_SPI3_SCK STM32_PINMUX_FUNC_ALT_6
#define STM32L4X_PINMUX_FUNC_PC10_USART3_TX STM32_PINMUX_FUNC_ALT_7
#define STM32L4X_PINMUX_FUNC_PC11_SPI3_MISO STM32_PINMUX_FUNC_ALT_6
#define STM32L4X_PINMUX_FUNC_PC11_USART3_RX STM32_PINMUX_FUNC_ALT_7
#define STM32L4X_PINMUX_FUNC_PC12_SPI3_MOSI STM32_PINMUX_FUNC_ALT_6

/* Port D */
#define STM32L4X_PINMUX_FUNC_PD5_USART2_TX STM32_PINMUX_FUNC_ALT_7
#define STM32L4X_PINMUX_FUNC_PD6_USART2_RX STM32_PINMUX_FUNC_ALT_7
#define STM32L4X_PINMUX_FUNC_PD8_USART3_TX STM32_PINMUX_FUNC_ALT_7
#define STM32L4X_PINMUX_FUNC_PD9_USART3_RX STM32_PINMUX_FUNC_ALT_7

/* Port F */
#define STM32L4X_PINMUX_FUNC_PF1_I2C3_SCL STM32_PINMUX_FUNC_ALT_4
#define STM32L4X_PINMUX_FUNC_PF0_I2C3_SDA STM32_PINMUX_FUNC_ALT_4

/* Port G */
#define STM32L4X_PINMUX_FUNC_PG7_I2C3_SCL STM32_PINMUX_FUNC_ALT_4
#define STM32L4X_PINMUX_FUNC_PG8_I2C3_SDA STM32_PINMUX_FUNC_ALT_4
#define STM32L4X_PINMUX_FUNC_PG9_USART1_TX STM32_PINMUX_FUNC_ALT_7
#define STM32L4X_PINMUX_FUNC_PG10_USART1_RX STM32_PINMUX_FUNC_ALT_7
#define STM32L4X_PINMUX_FUNC_PG14_I2C1_SCL STM32_PINMUX_FUNC_ALT_4
#define STM32L4X_PINMUX_FUNC_PG13_I2C1_SDA STM32_PINMUX_FUNC_ALT_4

#endif /* _STM32L4X_PINMUX_H_ */
