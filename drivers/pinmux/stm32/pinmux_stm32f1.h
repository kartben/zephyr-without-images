/*
 * Copyright (c) 2016 Open-RnD Sp. z o.o.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _STM32F1_PINMUX_H_
#define _STM32F1_PINMUX_H_

/**
 * @file Header for STM32F1 pin multiplexing helper
 */

#define STM32F1_PINMUX_FUNC_PA9_USART1_TX	     STM32_PIN_USART_TX
#define STM32F1_PINMUX_FUNC_PA10_USART1_RX	     STM32_PIN_USART_RX

#define STM32F1_PINMUX_FUNC_PA2_USART2_TX	     STM32_PIN_USART_TX
#define STM32F1_PINMUX_FUNC_PA3_USART2_RX	     STM32_PIN_USART_RX

#define STM32F1_PINMUX_FUNC_PA4_SPI1_MASTER_NSS      STM32_PIN_SPI_MASTER_NSS
#define STM32F1_PINMUX_FUNC_PA4_SPI1_MASTER_NSS_OE   STM32_PIN_SPI_MASTER_NSS_OE
#define STM32F1_PINMUX_FUNC_PA4_SPI1_SLAVE_NSS       STM32_PIN_SPI_SLAVE_NSS
#define STM32F1_PINMUX_FUNC_PA5_SPI1_MASTER_SCK      STM32_PIN_SPI_MASTER_SCK
#define STM32F1_PINMUX_FUNC_PA5_SPI1_SLAVE_SCK       STM32_PIN_SPI_SLAVE_SCK
#define STM32F1_PINMUX_FUNC_PA6_SPI1_MASTER_MISO     STM32_PIN_SPI_MASTER_MISO
#define STM32F1_PINMUX_FUNC_PA6_SPI1_SLAVE_MISO      STM32_PIN_SPI_SLAVE_MISO
#define STM32F1_PINMUX_FUNC_PA7_SPI1_MASTER_MOSI     STM32_PIN_SPI_MASTER_MOSI
#define STM32F1_PINMUX_FUNC_PA7_SPI1_SLAVE_MOSI      STM32_PIN_SPI_SLAVE_MOSI

#define STM32F1_PINMUX_FUNC_PA11_USB_DM		     STM32_PIN_USB
#define STM32F1_PINMUX_FUNC_PA12_USB_DP		     STM32_PIN_USB

#define STM32F1_PINMUX_FUNC_PD5_USART2_TX	     STM32_PIN_USART_TX
#define STM32F1_PINMUX_FUNC_PD6_USART2_RX	     STM32_PIN_USART_RX

#define STM32F1_PINMUX_FUNC_PB6_I2C1_SCL	     STM32_PIN_I2C
#define STM32F1_PINMUX_FUNC_PB7_I2C1_SDA	     STM32_PIN_I2C
#define STM32F1_PINMUX_FUNC_PB8_I2C1_SCL	     STM32_PIN_I2C
#define STM32F1_PINMUX_FUNC_PB9_I2C1_SDA	     STM32_PIN_I2C

#define STM32F1_PINMUX_FUNC_PB10_USART3_TX	     STM32_PIN_USART_TX
#define STM32F1_PINMUX_FUNC_PB11_USART3_RX	     STM32_PIN_USART_RX

#define STM32F1_PINMUX_FUNC_PC10_UART4_TX            STM32_PIN_USART_TX
#define STM32F1_PINMUX_FUNC_PC11_UART4_RX            STM32_PIN_USART_RX

#define STM32F1_PINMUX_FUNC_PB10_I2C2_SCL	     STM32_PIN_I2C
#define STM32F1_PINMUX_FUNC_PB11_I2C2_SDA	     STM32_PIN_I2C

#define STM32F1_PINMUX_FUNC_PB12_SPI2_MASTER_NSS     STM32_PIN_SPI_MASTER_NSS
#define STM32F1_PINMUX_FUNC_PB12_SPI2_MASTER_NSS_OE  STM32_PIN_SPI_MASTER_NSS_OE
#define STM32F1_PINMUX_FUNC_PB12_SPI2_SLAVE_NSS      STM32_PIN_SPI_SLAVE_NSS
#define STM32F1_PINMUX_FUNC_PB13_SPI2_MASTER_SCK     STM32_PIN_SPI_MASTER_SCK
#define STM32F1_PINMUX_FUNC_PB13_SPI2_SLAVE_SCK      STM32_PIN_SPI_SLAVE_SCK
#define STM32F1_PINMUX_FUNC_PB14_SPI2_MASTER_MISO    STM32_PIN_SPI_MASTER_MISO
#define STM32F1_PINMUX_FUNC_PB14_SPI2_SLAVE_MISO     STM32_PIN_SPI_SLAVE_MISO
#define STM32F1_PINMUX_FUNC_PB15_SPI2_MASTER_MOSI    STM32_PIN_SPI_MASTER_MOSI
#define STM32F1_PINMUX_FUNC_PB15_SPI2_SLAVE_MOSI     STM32_PIN_SPI_SLAVE_MOSI

#define STM32F1_PINMUX_FUNC_PA8_PWM1_CH1	     STM32_PIN_PWM

#endif /* _STM32F1_PINMUX_H_ */
