/*
 * Copyright (c) 2016 Open-RnD Sp. z o.o.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_PINMUX_STM32_PINMUX_STM32F1_H_
#define ZEPHYR_DRIVERS_PINMUX_STM32_PINMUX_STM32F1_H_

/**
 * @file Header for STM32F1 pin multiplexing helper
 */

/*
 * Note:
 * The SPIx_SCK pin speed must be set to 50MHz ('11') to avoid last data bit
 * corruption which is a known issue of STM32F1 SPI peripheral (see errata
 * sheets).
 */

#define STM32F1_PINMUX_FUNC_PA9_USART1_TX __DEPRECATED_MACRO	     STM32_PIN_USART_TX
#define STM32F1_PINMUX_FUNC_PA10_USART1_RX __DEPRECATED_MACRO	     STM32_PIN_USART_RX

#define STM32F1_PINMUX_FUNC_PA2_USART2_TX __DEPRECATED_MACRO	     STM32_PIN_USART_TX
#define STM32F1_PINMUX_FUNC_PA3_USART2_RX __DEPRECATED_MACRO	     STM32_PIN_USART_RX

#define STM32F1_PINMUX_FUNC_PA4_SPI1_MASTER_NSS __DEPRECATED_MACRO      STM32_PIN_SPI_MASTER_NSS
#define STM32F1_PINMUX_FUNC_PA4_SPI1_MASTER_NSS_OE __DEPRECATED_MACRO   STM32_PIN_SPI_MASTER_NSS_OE
#define STM32F1_PINMUX_FUNC_PA4_SPI1_SLAVE_NSS __DEPRECATED_MACRO       STM32_PIN_SPI_SLAVE_NSS
#define STM32F1_PINMUX_FUNC_PA5_SPI1_MASTER_SCK __DEPRECATED_MACRO      STM32_PIN_SPI_MASTER_SCK | \
						     STM32_MODE_OUTPUT_MAX_50
#define STM32F1_PINMUX_FUNC_PA5_SPI1_SLAVE_SCK __DEPRECATED_MACRO       STM32_PIN_SPI_SLAVE_SCK | \
						     STM32_MODE_OUTPUT_MAX_50
#define STM32F1_PINMUX_FUNC_PA6_SPI1_MASTER_MISO __DEPRECATED_MACRO     STM32_PIN_SPI_MASTER_MISO
#define STM32F1_PINMUX_FUNC_PA6_SPI1_SLAVE_MISO __DEPRECATED_MACRO      STM32_PIN_SPI_SLAVE_MISO
#define STM32F1_PINMUX_FUNC_PA7_SPI1_MASTER_MOSI __DEPRECATED_MACRO     STM32_PIN_SPI_MASTER_MOSI
#define STM32F1_PINMUX_FUNC_PA7_SPI1_SLAVE_MOSI __DEPRECATED_MACRO      STM32_PIN_SPI_SLAVE_MOSI

#define STM32F1_PINMUX_FUNC_PA11_USB_DM		     STM32_PIN_USB
#define STM32F1_PINMUX_FUNC_PA12_USB_DP		     STM32_PIN_USB

#define STM32F1_PINMUX_FUNC_PD5_USART2_TX __DEPRECATED_MACRO	     STM32_PIN_USART_TX
#define STM32F1_PINMUX_FUNC_PD6_USART2_RX __DEPRECATED_MACRO	     STM32_PIN_USART_RX

#define STM32F1_PINMUX_FUNC_PB6_I2C1_SCL __DEPRECATED_MACRO	     STM32_PIN_I2C
#define STM32F1_PINMUX_FUNC_PB7_I2C1_SDA __DEPRECATED_MACRO	     STM32_PIN_I2C
#define STM32F1_PINMUX_FUNC_PB8_I2C1_SCL __DEPRECATED_MACRO	     STM32_PIN_I2C
#define STM32F1_PINMUX_FUNC_PB9_I2C1_SDA __DEPRECATED_MACRO	     STM32_PIN_I2C

#define STM32F1_PINMUX_FUNC_PB10_USART3_TX __DEPRECATED_MACRO	     STM32_PIN_USART_TX
#define STM32F1_PINMUX_FUNC_PB11_USART3_RX __DEPRECATED_MACRO	     STM32_PIN_USART_RX

#define STM32F1_PINMUX_FUNC_PC10_UART4_TX __DEPRECATED_MACRO            STM32_PIN_USART_TX
#define STM32F1_PINMUX_FUNC_PC11_UART4_RX __DEPRECATED_MACRO            STM32_PIN_USART_RX

#define STM32F1_PINMUX_FUNC_PC12_UART5_TX __DEPRECATED_MACRO            STM32_PIN_USART_TX
#define STM32F1_PINMUX_FUNC_PD2_UART5_RX __DEPRECATED_MACRO            STM32_PIN_USART_RX

#define STM32F1_PINMUX_FUNC_PB10_I2C2_SCL __DEPRECATED_MACRO	     STM32_PIN_I2C
#define STM32F1_PINMUX_FUNC_PB11_I2C2_SDA __DEPRECATED_MACRO	     STM32_PIN_I2C

#define STM32F1_PINMUX_FUNC_PB12_SPI2_MASTER_NSS __DEPRECATED_MACRO     STM32_PIN_SPI_MASTER_NSS
#define STM32F1_PINMUX_FUNC_PB12_SPI2_MASTER_NSS_OE __DEPRECATED_MACRO  STM32_PIN_SPI_MASTER_NSS_OE
#define STM32F1_PINMUX_FUNC_PB12_SPI2_SLAVE_NSS __DEPRECATED_MACRO      STM32_PIN_SPI_SLAVE_NSS
#define STM32F1_PINMUX_FUNC_PB13_SPI2_MASTER_SCK __DEPRECATED_MACRO     STM32_PIN_SPI_MASTER_SCK | \
						     STM32_MODE_OUTPUT_MAX_50
#define STM32F1_PINMUX_FUNC_PB13_SPI2_SLAVE_SCK __DEPRECATED_MACRO      STM32_PIN_SPI_SLAVE_SCK | \
						     STM32_MODE_OUTPUT_MAX_50
#define STM32F1_PINMUX_FUNC_PB14_SPI2_MASTER_MISO __DEPRECATED_MACRO    STM32_PIN_SPI_MASTER_MISO
#define STM32F1_PINMUX_FUNC_PB14_SPI2_SLAVE_MISO __DEPRECATED_MACRO     STM32_PIN_SPI_SLAVE_MISO
#define STM32F1_PINMUX_FUNC_PB15_SPI2_MASTER_MOSI __DEPRECATED_MACRO    STM32_PIN_SPI_MASTER_MOSI
#define STM32F1_PINMUX_FUNC_PB15_SPI2_SLAVE_MOSI __DEPRECATED_MACRO     STM32_PIN_SPI_SLAVE_MOSI

#define STM32F1_PINMUX_FUNC_PA15_SPI3_MASTER_NSS __DEPRECATED_MACRO     STM32_PIN_SPI_MASTER_NSS
#define STM32F1_PINMUX_FUNC_PA15_SPI3_MASTER_NSS_OE __DEPRECATED_MACRO  STM32_PIN_SPI_MASTER_NSS_OE
#define STM32F1_PINMUX_FUNC_PA15_SPI3_SLAVE_NSS __DEPRECATED_MACRO      STM32_PIN_SPI_SLAVE_NSS
#define STM32F1_PINMUX_FUNC_PB3_SPI3_MASTER_SCK __DEPRECATED_MACRO     STM32_PIN_SPI_MASTER_SCK | \
						     STM32_MODE_OUTPUT_MAX_50
#define STM32F1_PINMUX_FUNC_PB3_SPI3_SLAVE_SCK __DEPRECATED_MACRO      STM32_PIN_SPI_SLAVE_SCK | \
						     STM32_MODE_OUTPUT_MAX_50
#define STM32F1_PINMUX_FUNC_PB4_SPI3_MASTER_MISO __DEPRECATED_MACRO    STM32_PIN_SPI_MASTER_MISO
#define STM32F1_PINMUX_FUNC_PB4_SPI3_SLAVE_MISO __DEPRECATED_MACRO     STM32_PIN_SPI_SLAVE_MISO
#define STM32F1_PINMUX_FUNC_PB5_SPI3_MASTER_MOSI __DEPRECATED_MACRO    STM32_PIN_SPI_MASTER_MOSI
#define STM32F1_PINMUX_FUNC_PB5_SPI3_SLAVE_MOSI __DEPRECATED_MACRO     STM32_PIN_SPI_SLAVE_MOSI

#define STM32F1_PINMUX_FUNC_PA8_PWM1_CH1 __DEPRECATED_MACRO    STM32_PIN_PWM

#define STM32F1_PINMUX_FUNC_PF6_ADC3_IN4 __DEPRECATED_MACRO             STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PF7_ADC3_IN5 __DEPRECATED_MACRO             STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PF8_ADC3_IN6 __DEPRECATED_MACRO             STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PF9_ADC3_IN7 __DEPRECATED_MACRO             STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PF10_ADC3_IN8 __DEPRECATED_MACRO            STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PC0_ADC123_IN10 __DEPRECATED_MACRO          STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PC1_ADC123_IN11 __DEPRECATED_MACRO          STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PC2_ADC123_IN12 __DEPRECATED_MACRO          STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PC3_ADC123_IN13 __DEPRECATED_MACRO          STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PA0_ADC123_IN0 __DEPRECATED_MACRO           STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PA1_ADC123_IN1 __DEPRECATED_MACRO           STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PA2_ADC123_IN2 __DEPRECATED_MACRO           STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PA3_ADC123_IN3 __DEPRECATED_MACRO           STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PA4_ADC12_IN4 __DEPRECATED_MACRO            STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PA5_ADC12_IN5 __DEPRECATED_MACRO            STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PA6_ADC12_IN6 __DEPRECATED_MACRO            STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PA7_ADC12_IN7 __DEPRECATED_MACRO            STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PC4_ADC12_IN14 __DEPRECATED_MACRO           STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PC5_ADC12_IN15 __DEPRECATED_MACRO           STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PB0_ADC12_IN8 __DEPRECATED_MACRO            STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PB1_ADC12_IN9 __DEPRECATED_MACRO            STM32_CNF_IN_ANALOG

#define STM32F1_PINMUX_FUNC_PB8_FDCAN_RX __DEPRECATED_MACRO               STM32_PIN_CAN_RX
#define STM32F1_PINMUX_FUNC_PB9_FDCAN_TX __DEPRECATED_MACRO               STM32_PIN_CAN_TX

#endif /* ZEPHYR_DRIVERS_PINMUX_STM32_PINMUX_STM32F1_H_ */
