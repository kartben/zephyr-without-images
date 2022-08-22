/*
 * Copyright (c) 2022 Teslabs Engineering S.L.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DT_BINDINGS_RESET_GD32E10X_H_
#define ZEPHYR_INCLUDE_DT_BINDINGS_RESET_GD32E10X_H_

#include "gd32-common.h"

/**
 * @name Register offsets
 * @{
 */

#define GD32_APB2RST_OFFSET       0x0CU
#define GD32_APB1RST_OFFSET       0x10U
#define GD32_AHBRST_OFFSET        0x28U
#define GD32_ADDAPB1RST_OFFSET    0xE0U

/** @} */

/**
 * @name Clock enable/disable definitions for peripherals
 * @{
 */

/* APB2 peripherals */
#define GD32_RESET_AFIO       GD32_RESET_CONFIG(APB2RST, 0U)
#define GD32_RESET_GPIOA      GD32_RESET_CONFIG(APB2RST, 2U)
#define GD32_RESET_GPIOB      GD32_RESET_CONFIG(APB2RST, 3U)
#define GD32_RESET_GPIOC      GD32_RESET_CONFIG(APB2RST, 4U)
#define GD32_RESET_GPIOD      GD32_RESET_CONFIG(APB2RST, 5U)
#define GD32_RESET_GPIOE      GD32_RESET_CONFIG(APB2RST, 6U)
#define GD32_RESET_ADC0       GD32_RESET_CONFIG(APB2RST, 9U)
#define GD32_RESET_ADC1       GD32_RESET_CONFIG(APB2RST, 10U)
#define GD32_RESET_TIMER0     GD32_RESET_CONFIG(APB2RST, 11U)
#define GD32_RESET_SPI0       GD32_RESET_CONFIG(APB2RST, 12U)
#define GD32_RESET_TIMER7     GD32_RESET_CONFIG(APB2RST, 13U)
#define GD32_RESET_USART0     GD32_RESET_CONFIG(APB2RST, 14U)
#define GD32_RESET_TIMER8     GD32_RESET_CONFIG(APB2RST, 19U)
#define GD32_RESET_TIMER9     GD32_RESET_CONFIG(APB2RST, 20U)
#define GD32_RESET_TIMER10    GD32_RESET_CONFIG(APB2RST, 21U)

/* APB1 peripherals */
#define GD32_RESET_TIMER1     GD32_RESET_CONFIG(APB1RST, 0U)
#define GD32_RESET_TIMER2     GD32_RESET_CONFIG(APB1RST, 1U)
#define GD32_RESET_TIMER3     GD32_RESET_CONFIG(APB1RST, 2U)
#define GD32_RESET_TIMER4     GD32_RESET_CONFIG(APB1RST, 3U)
#define GD32_RESET_TIMER5     GD32_RESET_CONFIG(APB1RST, 4U)
#define GD32_RESET_TIMER6     GD32_RESET_CONFIG(APB1RST, 5U)
#define GD32_RESET_TIMER11    GD32_RESET_CONFIG(APB1RST, 6U)
#define GD32_RESET_TIMER12    GD32_RESET_CONFIG(APB1RST, 7U)
#define GD32_RESET_TIMER13    GD32_RESET_CONFIG(APB1RST, 8U)
#define GD32_RESET_WWDGT      GD32_RESET_CONFIG(APB1RST, 11U)
#define GD32_RESET_SPI1       GD32_RESET_CONFIG(APB1RST, 14U)
#define GD32_RESET_SPI2       GD32_RESET_CONFIG(APB1RST, 15U)
#define GD32_RESET_USART1     GD32_RESET_CONFIG(APB1RST, 17U)
#define GD32_RESET_USART2     GD32_RESET_CONFIG(APB1RST, 18U)
#define GD32_RESET_UART3      GD32_RESET_CONFIG(APB1RST, 19U)
#define GD32_RESET_UART4      GD32_RESET_CONFIG(APB1RST, 20U)
#define GD32_RESET_I2C0       GD32_RESET_CONFIG(APB1RST, 21U)
#define GD32_RESET_I2C1       GD32_RESET_CONFIG(APB1RST, 22U)
#define GD32_RESET_CAN0       GD32_RESET_CONFIG(APB1RST, 25U)
#define GD32_RESET_CAN1       GD32_RESET_CONFIG(APB1RST, 26U)
#define GD32_RESET_BKPI       GD32_RESET_CONFIG(APB1RST, 27U)
#define GD32_RESET_PMU        GD32_RESET_CONFIG(APB1RST, 28U)
#define GD32_RESET_DAC        GD32_RESET_CONFIG(APB1RST, 29U)

/* AHB peripherals */
#define GD32_RESET_USBFS      GD32_RESET_CONFIG(AHBRST, 12U)

/* APB1 additional peripherals */
#define GD32_RESET_CTC        GD32_RESET_CONFIG(ADDAPB1RST, 27U)

/** @} */

#endif /* ZEPHYR_INCLUDE_DT_BINDINGS_RESET_GD32E10X_H_ */
