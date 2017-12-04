/*
 * Copyright (c) 2017 RnDity Sp. z o.o.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _STM32F3_PINMUX_H_
#define _STM32F3_PINMUX_H_

/**
 * @file Header for STM32F3 pin multiplexing helper
 */

#define STM32F3_PINMUX_FUNC_PA9_USART1_TX   (STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32F3_PINMUX_FUNC_PA10_USART1_RX  (STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#define STM32F3_PINMUX_FUNC_PC4_USART1_TX   (STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32F3_PINMUX_FUNC_PC5_USART1_RX   (STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#define STM32F3_PINMUX_FUNC_PA2_USART2_TX   (STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32F3_PINMUX_FUNC_PA3_USART2_RX   (STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)

#ifndef CONFIG_SOC_STM32F334X8
#define STM32F3_PINMUX_FUNC_PD5_USART2_TX   (STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32F3_PINMUX_FUNC_PD6_USART2_RX   (STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#endif

#if CONFIG_SOC_STM32F303XC
#define STM32F3_PINMUX_FUNC_PA9_I2C2_SCL    (STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32F3_PINMUX_FUNC_PA10_I2C2_SDA   (STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32F3_PINMUX_FUNC_PB6_I2C1_SCL    (STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32F3_PINMUX_FUNC_PB7_I2C1_SDA    (STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32F3_PINMUX_FUNC_PB10_USART3_TX  (STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32F3_PINMUX_FUNC_PB11_USART3_RX  (STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32F3_PINMUX_FUNC_PF0_I2C2_SDA    (STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32F3_PINMUX_FUNC_PF1_I2C2_SCL    (STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#elif CONFIG_SOC_STM32F334X8
#define STM32F3_PINMUX_FUNC_PB8_USART3_RX   (STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32F3_PINMUX_FUNC_PB9_USART3_TX   (STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32F3_PINMUX_FUNC_PB10_USART3_TX  (STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32F3_PINMUX_FUNC_PB11_USART3_RX  (STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#elif CONFIG_SOC_STM32F373XC
#define STM32F3_PINMUX_FUNC_PB8_USART3_TX   (STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32F3_PINMUX_FUNC_PB9_USART3_RX   (STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#define STM32F3_PINMUX_FUNC_PB10_USART3_TX  (STM32_PINMUX_ALT_FUNC_7 | STM32_PUSHPULL_PULLUP)
#endif

#define STM32F3_PINMUX_FUNC_PA4_SPI1_NSS    (STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32F3_PINMUX_FUNC_PA5_SPI1_SCK    (STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32F3_PINMUX_FUNC_PA6_SPI1_MISO   (STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)
#define STM32F3_PINMUX_FUNC_PA7_SPI1_MOSI   (STM32_PINMUX_ALT_FUNC_5 | STM32_PUSHPULL_NOPULL)

#define STM32F3_PINMUX_FUNC_PB8_I2C1_SCL    (STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)
#define STM32F3_PINMUX_FUNC_PB9_I2C1_SDA    (STM32_PINMUX_ALT_FUNC_4 | STM32_OPENDRAIN_PULLUP)

#endif /* _STM32F3_PINMUX_H_ */
