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

#define STM32F1_PINMUX_FUNC_PA9_USART1_TX	     STM32_PIN_USART_TX
#define STM32F1_PINMUX_FUNC_PA10_USART1_RX	     STM32_PIN_USART_RX

#define STM32F1_PINMUX_FUNC_PA2_USART2_TX	     STM32_PIN_USART_TX
#define STM32F1_PINMUX_FUNC_PA3_USART2_RX	     STM32_PIN_USART_RX

#define STM32F1_PINMUX_FUNC_PA4_SPI1_MASTER_NSS      STM32_PIN_SPI_MASTER_NSS
#define STM32F1_PINMUX_FUNC_PA4_SPI1_MASTER_NSS_OE   STM32_PIN_SPI_MASTER_NSS_OE
#define STM32F1_PINMUX_FUNC_PA4_SPI1_SLAVE_NSS       STM32_PIN_SPI_SLAVE_NSS
#define STM32F1_PINMUX_FUNC_PA5_SPI1_MASTER_SCK      STM32_PIN_SPI_MASTER_SCK | \
						     STM32_MODE_OUTPUT_MAX_50
#define STM32F1_PINMUX_FUNC_PA5_SPI1_SLAVE_SCK       STM32_PIN_SPI_SLAVE_SCK | \
						     STM32_MODE_OUTPUT_MAX_50
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
#define STM32F1_PINMUX_FUNC_PB13_SPI2_MASTER_SCK     STM32_PIN_SPI_MASTER_SCK | \
						     STM32_MODE_OUTPUT_MAX_50
#define STM32F1_PINMUX_FUNC_PB13_SPI2_SLAVE_SCK      STM32_PIN_SPI_SLAVE_SCK | \
						     STM32_MODE_OUTPUT_MAX_50
#define STM32F1_PINMUX_FUNC_PB14_SPI2_MASTER_MISO    STM32_PIN_SPI_MASTER_MISO
#define STM32F1_PINMUX_FUNC_PB14_SPI2_SLAVE_MISO     STM32_PIN_SPI_SLAVE_MISO
#define STM32F1_PINMUX_FUNC_PB15_SPI2_MASTER_MOSI    STM32_PIN_SPI_MASTER_MOSI
#define STM32F1_PINMUX_FUNC_PB15_SPI2_SLAVE_MOSI     STM32_PIN_SPI_SLAVE_MOSI

#define STM32F1_PINMUX_FUNC_PA8_PWM1_CH1	     STM32_PIN_PWM

#define STM32F1_PINMUX_FUNC_PF6_ADC3_IN4             STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PF7_ADC3_IN5             STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PF8_ADC3_IN6             STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PF9_ADC3_IN7             STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PF10_ADC3_IN8            STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PC0_ADC123_IN10          STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PC1_ADC123_IN11          STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PC2_ADC123_IN12          STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PC3_ADC123_IN13          STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PA0_ADC123_IN0           STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PA1_ADC123_IN1           STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PA2_ADC123_IN2           STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PA3_ADC123_IN3           STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PA4_ADC12_IN4            STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PA5_ADC12_IN5            STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PA6_ADC12_IN6            STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PA7_ADC12_IN7            STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PC4_ADC12_IN14           STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PC4_ADC12_IN15           STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PB0_ADC12_IN8            STM32_CNF_IN_ANALOG
#define STM32F1_PINMUX_FUNC_PB1_ADC12_IN9            STM32_CNF_IN_ANALOG

#endif /* ZEPHYR_DRIVERS_PINMUX_STM32_PINMUX_STM32F1_H_ */
