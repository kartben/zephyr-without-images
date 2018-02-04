/*
 * Copyright (c) 2018 Ilya Tagunov
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _STM32L0_PINMUX_H_
#define _STM32L0_PINMUX_H_

/**
 * @file Header for STM32L0 pin multiplexing helper
 */

#define STM32L0_PINMUX_FUNC_PB6_USART1_TX \
	(STM32_PINMUX_ALT_FUNC_0 | STM32_PUSHPULL_NOPULL)
#define STM32L0_PINMUX_FUNC_PB7_USART1_RX \
	(STM32_PINMUX_ALT_FUNC_0 | STM32_PUPDR_NO_PULL)

#define STM32L0_PINMUX_FUNC_PA9_USART1_TX \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_PUSHPULL_NOPULL)
#define STM32L0_PINMUX_FUNC_PA10_USART1_RX \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_PUPDR_NO_PULL)

#define STM32L0_PINMUX_FUNC_PA2_USART2_TX \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_PUSHPULL_NOPULL)
#define STM32L0_PINMUX_FUNC_PA3_USART2_RX \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_PUPDR_NO_PULL)

#define STM32L0_PINMUX_FUNC_PA14_USART2_TX \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_PUSHPULL_NOPULL)
#define STM32L0_PINMUX_FUNC_PA15_USART2_RX \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_PUPDR_NO_PULL)

#endif /* _STM32L0_PINMUX_H_ */
