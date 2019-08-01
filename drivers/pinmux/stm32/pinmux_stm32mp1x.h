/*
 * Copyright (c) 2019 STMicroelectronics
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_PINMUX_STM32_PINMUX_STM32MP1X_H_
#define ZEPHYR_DRIVERS_PINMUX_STM32_PINMUX_STM32MP1X_H_

/**
 * @file Header for STM32MP1X pin multiplexing helper
 */

/* Port A */
#define STM32MP1X_PINMUX_FUNC_PA11_I2C5_SCL \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32MP1X_PINMUX_FUNC_PA12_I2C5_SDA \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

/* Port B */
#define STM32MP1X_PINMUX_FUNC_PB2_UART4_RX \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUPDR_PULL_DOWN)
#define STM32MP1X_PINMUX_FUNC_PB10_USART3_TX \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32MP1X_PINMUX_FUNC_PB12_USART3_RX \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUPDR_PULL_DOWN)

/* Port D */
#define STM32MP1X_PINMUX_FUNC_PD1_UART4_TX \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

/* Port E */
#define STM32MP1X_PINMUX_FUNC_PE7_UART7_RX \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUPDR_PULL_DOWN)
#define STM32MP1X_PINMUX_FUNC_PE8_UART7_TX \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32MP1X_PINMUX_FUNC_PE9_UART7_RTS \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32MP1X_PINMUX_FUNC_PE10_UART7_CTS \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32MP1X_PINMUX_FUNC_PE11_SPI4_NSS   \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32MP1X_PINMUX_FUNC_PE12_SPI4_SCK \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32MP1X_PINMUX_FUNC_PE13_SPI4_MISO \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32MP1X_PINMUX_FUNC_PE14_SPI4_MOSI \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)

/* Port F */
#define STM32MP1X_PINMUX_FUNC_PF6_SPI5_NSS   \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32MP1X_PINMUX_FUNC_PF7_SPI5_SCK \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32MP1X_PINMUX_FUNC_PF8_SPI5_MISO \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32MP1X_PINMUX_FUNC_PF9_SPI5_MOSI \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)

#endif /* ZEPHYR_DRIVERS_PINMUX_STM32_PINMUX_STM32MP1X_H_ */
