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
#define STM32H7_PINMUX_FUNC_PA0_USART2_CTS    \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA0_UART4_TX    \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PA1_USART2_RTS    \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA1_UART4_RX    \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PA2_USART2_TX   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PA3_USART2_RX   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PA8_I2C3_SCL    \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

#define STM32H7_PINMUX_FUNC_PA9_USART1_TX   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PA9_SPI2_SCK   \
	(STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PA10_USART1_RX  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PA11_UART4_RX    \
	(STM32_PINMUX_ALT_FUNC_6 | STM32_PUSHPULL_NOPULL)
#define STM32H7_PINMUX_FUNC_PA11_USART1_CTS  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PA12_UART4_RX    \
	(STM32_PINMUX_ALT_FUNC_6 | STM32_PUSHPULL_NOPULL)
#define STM32H7_PINMUX_FUNC_PA12_USART1_RTS  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PA15_USART4_RTS \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

/* Port B */
#define STM32H7_PINMUX_FUNC_PB6_I2C1_SCL    \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32H7_PINMUX_FUNC_PB6_I2C4_SCL    \
	(STM32_PINMUX_ALT_FUNC_6 | STM32_OPENDRAIN_PULLUP)
#define STM32H7_PINMUX_FUNC_PB6_USART1_TX   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PB6_LPUART1_TX    \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_OPENDRAIN_PULLUP)

#define STM32H7_PINMUX_FUNC_PB7_I2C1_SDA    \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32H7_PINMUX_FUNC_PB7_I2C4_SDA    \
	(STM32_PINMUX_ALT_FUNC_6 | STM32_OPENDRAIN_PULLUP)
#define STM32H7_PINMUX_FUNC_PB7_USART1_RX   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)
#define STM32H7_PINMUX_FUNC_PB7_LPUART1_RX   \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PB8_I2C1_SCL    \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32H7_PINMUX_FUNC_PB8_I2C4_SCL    \
	(STM32_PINMUX_ALT_FUNC_6 | STM32_OPENDRAIN_PULLUP)

#define STM32H7_PINMUX_FUNC_PB9_I2C1_SDA    \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32H7_PINMUX_FUNC_PB9_I2C4_SDA    \
	(STM32_PINMUX_ALT_FUNC_6 | STM32_OPENDRAIN_PULLUP)

#define STM32H7_PINMUX_FUNC_PB10_I2C2_SCL    \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32H7_PINMUX_FUNC_PB10_USART3_TX  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PB11_I2C2_SDA    \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32H7_PINMUX_FUNC_PB11_USART3_RX	\
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PB14_UART3_RTS	\
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)

/* Port C */
#define STM32H7_PINMUX_FUNC_PC6_USART6_TX   \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PC7_USART6_RX   \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PC8_UART5_RTS  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PC9_I2C3_SDA   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32H7_PINMUX_FUNC_PC9_UART5_CTS  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PC10_USART3_TX  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32H7_PINMUX_FUNC_PC10_UART4_TX  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PC11_USART3_RX  \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)
#define STM32H7_PINMUX_FUNC_PC11_UART4_RX   \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PC12_UART5_TX   \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

/* Port D */
#define STM32H7_PINMUX_FUNC_PD2_UART5_RX    \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PD3_USART2_CTS   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PD4_USART2_RTS   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PD5_USART2_TX   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PD6_USART2_RX   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PD8_USART3_TX   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PD9_USART3_RX   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PD11_USART3_CTS   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PD12_I2C4_SCL   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32H7_PINMUX_FUNC_PD12_USART3_RTS   \
	(STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PD13_I2C4_SDA   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

#define STM32H7_PINMUX_FUNC_PD14_UART8_CTS  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PD15_UART8_RTS  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

/* Port E */
#define STM32H7_PINMUX_FUNC_PE0_UART8_RX    \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PE1_UART8_TX    \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PE7_UART7_RX    \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PE8_UART7_TX    \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PE9_UART7_RTS   \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PE10_UART7_CTS  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)


/* Port F */
#define STM32H7_PINMUX_FUNC_PF0_I2C2_SDA   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

#define STM32H7_PINMUX_FUNC_PF1_I2C2_SCL   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

#define STM32H7_PINMUX_FUNC_PF6_UART7_RX    \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PF7_UART7_TX    \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PF8_UART7_RTS    \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PF9_UART7_CTS    \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PF14_I2C4_SCL   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

#define STM32H7_PINMUX_FUNC_PF15_I2C4_SDA   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

/* Port G */
#define STM32H7_PINMUX_FUNC_PG8_USART6_RTS   \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PG9_USART6_RX   \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)

#define STM32H7_PINMUX_FUNC_PG12_USART6_RTS  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PG13_USART6_CTS  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PG14_USART6_TX  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PG15_USART6_CTS  \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

/* Port H */
#define STM32H7_PINMUX_FUNC_PH4_I2C2_SCL   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

#define STM32H7_PINMUX_FUNC_PH5_I2C2_SDA   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

#define STM32H7_PINMUX_FUNC_PH7_I2C3_SCL   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

#define STM32H7_PINMUX_FUNC_PH8_I2C3_SDA   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

#define STM32H7_PINMUX_FUNC_PH11_I2C4_SCL   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

#define STM32H7_PINMUX_FUNC_PH12_I2C4_SDA   \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

/* Port I */

/* Port J */
#define STM32H7_PINMUX_FUNC_PJ8_UART8_TX \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_PULLUP)

#define STM32H7_PINMUX_FUNC_PJ9_UART8_RX \
	(STM32_PINMUX_ALT_FUNC_8 | STM32_PUSHPULL_NOPULL)

/* Port K */

#endif /* ZEPHYR_DRIVERS_PINMUX_STM32_PINMUX_STM32H7_H_ */
