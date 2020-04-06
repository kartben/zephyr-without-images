/*
 * Copyright (c) 2019 Lemonbeat GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* SoC level DTS fixup file */

#define DT_NUM_IRQ_PRIO_BITS	DT_ARM_V7M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS
#define DT_CPU_CLOCK_FREQUENCY	DT_ARM_CORTEX_M4F_0_CLOCK_FREQUENCY

#define DT_FLASH_DEV_BASE_ADDRESS		DT_SILABS_GECKO_FLASH_CONTROLLER_400E0000_BASE_ADDRESS
#define DT_FLASH_DEV_NAME			DT_SILABS_GECKO_FLASH_CONTROLLER_400E0000_LABEL

#define DT_GPIO_GECKO_SWO_LOCATION	DT_SILABS_GECKO_GPIO_4000A400_LOCATION_SWO

#define DT_WDT_0_NAME			DT_LABEL(DT_INST(0, silabs_gecko_wdog))
#define DT_WDT_1_NAME			DT_LABEL(DT_INST(1, silabs_gecko_wdog))

/* End of SoC Level DTS fixup file */
