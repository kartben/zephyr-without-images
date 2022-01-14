/*
 * Copyright (c) 2022 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef ZEPHYR_INCLUDE_DT_BINDINGS_CLOCK_STM32H7_CLOCK_H_
#define ZEPHYR_INCLUDE_DT_BINDINGS_CLOCK_STM32H7_CLOCK_H_

/* clock bus references */
#define STM32_CLOCK_BUS_AHB3    0x0D4
#define STM32_CLOCK_BUS_AHB1    0x0D8
#define STM32_CLOCK_BUS_AHB2    0x0DC
#define STM32_CLOCK_BUS_AHB4    0x0E0
#define STM32_CLOCK_BUS_APB3    0x0E4
#define STM32_CLOCK_BUS_APB1    0x0E8
#define STM32_CLOCK_BUS_APB1_2  0x0EC
#define STM32_CLOCK_BUS_APB2    0x0F0
#define STM32_CLOCK_BUS_APB4    0x0F4

#define STM32_PERIPH_BUS_MIN	STM32_CLOCK_BUS_AHB3
#define STM32_PERIPH_BUS_MAX	STM32_CLOCK_BUS_APB4

#endif /* ZEPHYR_INCLUDE_DT_BINDINGS_CLOCK_STM32H7_CLOCK_H_ */
