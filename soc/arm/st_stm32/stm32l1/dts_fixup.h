/*
 * Copyright (c) 2019 Linaro Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* SoC level DTS fixup file */

#define DT_NUM_IRQ_PRIO_BITS	DT_ARM_V7M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS

#define DT_I2C_1_BASE_ADDRESS		DT_ST_STM32_I2C_V1_40005400_BASE_ADDRESS
#define DT_I2C_1_EVENT_IRQ_PRI		DT_ST_STM32_I2C_V1_40005400_IRQ_EVENT_PRIORITY
#define DT_I2C_1_ERROR_IRQ_PRI		DT_ST_STM32_I2C_V1_40005400_IRQ_ERROR_PRIORITY
#define DT_I2C_1_EVENT_IRQ		DT_ST_STM32_I2C_V1_40005400_IRQ_EVENT
#define DT_I2C_1_ERROR_IRQ		DT_ST_STM32_I2C_V1_40005400_IRQ_ERROR
#define DT_I2C_1_BITRATE		DT_ST_STM32_I2C_V1_40005400_CLOCK_FREQUENCY
#define DT_I2C_1_CLOCK_BITS		DT_ST_STM32_I2C_V1_40005400_CLOCK_BITS
#define DT_I2C_1_CLOCK_BUS		DT_ST_STM32_I2C_V1_40005400_CLOCK_BUS

#define DT_I2C_2_BASE_ADDRESS		DT_ST_STM32_I2C_V1_40005800_BASE_ADDRESS
#define DT_I2C_2_EVENT_IRQ_PRI		DT_ST_STM32_I2C_V1_40005800_IRQ_EVENT_PRIORITY
#define DT_I2C_2_ERROR_IRQ_PRI		DT_ST_STM32_I2C_V1_40005800_IRQ_ERROR_PRIORITY
#define DT_I2C_2_EVENT_IRQ		DT_ST_STM32_I2C_V1_40005800_IRQ_EVENT
#define DT_I2C_2_ERROR_IRQ		DT_ST_STM32_I2C_V1_40005800_IRQ_ERROR
#define DT_I2C_2_BITRATE		DT_ST_STM32_I2C_V1_40005800_CLOCK_FREQUENCY
#define DT_I2C_2_CLOCK_BITS		DT_ST_STM32_I2C_V1_40005800_CLOCK_BITS
#define DT_I2C_2_CLOCK_BUS		DT_ST_STM32_I2C_V1_40005800_CLOCK_BUS

#define DT_WDT_0_NAME			DT_LABEL(DT_INST(0, st_stm32_watchdog))

#define DT_ADC_1_NAME			DT_ST_STM32_ADC_40012400_LABEL

#define DT_RTC_0_NAME                   DT_LABEL(DT_INST(0, st_stm32_rtc))
/* End of SoC Level DTS fixup file */
