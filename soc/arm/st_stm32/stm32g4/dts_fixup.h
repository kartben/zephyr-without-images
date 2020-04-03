/*
 * Copyright (c) 2019 Richard Osterloh <richard.osterloh@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* SoC level DTS fixup file */

#define DT_NUM_IRQ_PRIO_BITS			DT_ARM_V7M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS

#define DT_FLASH_DEV_NAME			DT_LABEL(DT_INST(0, st_stm32g4_flash_controller))

#define DT_I2C_1_BASE_ADDRESS			DT_ST_STM32_I2C_V2_40005400_BASE_ADDRESS
#define DT_I2C_1_EVENT_IRQ_PRI			DT_ST_STM32_I2C_V2_40005400_IRQ_EVENT_PRIORITY
#define DT_I2C_1_ERROR_IRQ_PRI			DT_ST_STM32_I2C_V2_40005400_IRQ_ERROR_PRIORITY
#define DT_I2C_1_NAME			DT_ST_STM32_I2C_V2_40005400_LABEL
#define DT_I2C_1_EVENT_IRQ			DT_ST_STM32_I2C_V2_40005400_IRQ_EVENT
#define DT_I2C_1_ERROR_IRQ			DT_ST_STM32_I2C_V2_40005400_IRQ_ERROR
#define DT_I2C_1_BITRATE			DT_ST_STM32_I2C_V2_40005400_CLOCK_FREQUENCY
#define DT_I2C_1_CLOCK_BITS			DT_ST_STM32_I2C_V2_40005400_CLOCK_BITS
#define DT_I2C_1_CLOCK_BUS			DT_ST_STM32_I2C_V2_40005400_CLOCK_BUS

#define DT_I2C_2_BASE_ADDRESS			DT_ST_STM32_I2C_V2_40005800_BASE_ADDRESS
#define DT_I2C_2_EVENT_IRQ_PRI			DT_ST_STM32_I2C_V2_40005800_IRQ_EVENT_PRIORITY
#define DT_I2C_2_ERROR_IRQ_PRI			DT_ST_STM32_I2C_V2_40005800_IRQ_ERROR_PRIORITY
#define DT_I2C_2_NAME			DT_ST_STM32_I2C_V2_40005800_LABEL
#define DT_I2C_2_EVENT_IRQ			DT_ST_STM32_I2C_V2_40005800_IRQ_EVENT
#define DT_I2C_2_ERROR_IRQ			DT_ST_STM32_I2C_V2_40005800_IRQ_ERROR
#define DT_I2C_2_BITRATE			DT_ST_STM32_I2C_V2_40005800_CLOCK_FREQUENCY
#define DT_I2C_2_CLOCK_BITS			DT_ST_STM32_I2C_V2_40005800_CLOCK_BITS
#define DT_I2C_2_CLOCK_BUS			DT_ST_STM32_I2C_V2_40005800_CLOCK_BUS

#define DT_I2C_3_BASE_ADDRESS			DT_ST_STM32_I2C_V2_40007800_BASE_ADDRESS
#define DT_I2C_3_EVENT_IRQ_PRI			DT_ST_STM32_I2C_V2_40007800_IRQ_EVENT_PRIORITY
#define DT_I2C_3_ERROR_IRQ_PRI			DT_ST_STM32_I2C_V2_40007800_IRQ_ERROR_PRIORITY
#define DT_I2C_3_NAME			DT_ST_STM32_I2C_V2_40007800_LABEL
#define DT_I2C_3_EVENT_IRQ			DT_ST_STM32_I2C_V2_40007800_IRQ_EVENT
#define DT_I2C_3_ERROR_IRQ			DT_ST_STM32_I2C_V2_40007800_IRQ_ERROR
#define DT_I2C_3_BITRATE			DT_ST_STM32_I2C_V2_40007800_CLOCK_FREQUENCY
#define DT_I2C_3_CLOCK_BITS			DT_ST_STM32_I2C_V2_40007800_CLOCK_BITS
#define DT_I2C_3_CLOCK_BUS			DT_ST_STM32_I2C_V2_40007800_CLOCK_BUS

#define DT_RTC_0_NAME				DT_LABEL(DT_INST(0, st_stm32_rtc))

#define DT_WDT_0_NAME				DT_LABEL(DT_INST(0, st_stm32_watchdog))

#ifndef CONFIG_ENTROPY_NAME
#define CONFIG_ENTROPY_NAME		DT_LABEL(DT_INST(0, st_stm32_rng))
#endif

/* End of SoC Level DTS fixup file */
