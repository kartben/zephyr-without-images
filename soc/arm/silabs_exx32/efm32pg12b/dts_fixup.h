/*
 * Copyright (c) 2018, Christian Taedcke <hacking@taedcke.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* SoC level DTS fixup file */

#define DT_NUM_IRQ_PRIO_BITS	DT_ARM_V7M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS
#define DT_CPU_CLOCK_FREQUENCY	DT_ARM_CORTEX_M4F_0_CLOCK_FREQUENCY

#define DT_FLASH_DEV_BASE_ADDRESS		DT_SILABS_GECKO_FLASH_CONTROLLER_400E0000_BASE_ADDRESS
#define DT_FLASH_DEV_NAME			DT_SILABS_GECKO_FLASH_CONTROLLER_400E0000_LABEL

#define DT_GPIO_GECKO_COMMON_NAME	DT_SILABS_EFM32_GPIO_4000A400_LABEL
#define DT_GPIO_GECKO_COMMON_EVEN_IRQ	DT_SILABS_EFM32_GPIO_4000A400_IRQ_GPIO_EVEN
#define DT_GPIO_GECKO_COMMON_EVEN_PRI	DT_SILABS_EFM32_GPIO_4000A400_IRQ_GPIO_EVEN_PRIORITY
#define DT_GPIO_GECKO_COMMON_ODD_IRQ	DT_SILABS_EFM32_GPIO_4000A400_IRQ_GPIO_ODD
#define DT_GPIO_GECKO_COMMON_ODD_PRI	DT_SILABS_EFM32_GPIO_4000A400_IRQ_GPIO_ODD_PRIORITY
#define DT_GPIO_GECKO_SWO_LOCATION	DT_SILABS_EFM32_GPIO_4000A400_LOCATION_SWO

#define DT_GPIO_GECKO_PORTA_NAME	DT_SILABS_EFM32_GPIO_PORT_4000A000_LABEL
#define DT_GPIO_GECKO_PORTB_NAME	DT_SILABS_EFM32_GPIO_PORT_4000A030_LABEL
#define DT_GPIO_GECKO_PORTC_NAME	DT_SILABS_EFM32_GPIO_PORT_4000A060_LABEL
#define DT_GPIO_GECKO_PORTD_NAME	DT_SILABS_EFM32_GPIO_PORT_4000A090_LABEL
#define DT_GPIO_GECKO_PORTE_NAME	DT_SILABS_EFM32_GPIO_PORT_4000A0C0_LABEL
#define DT_GPIO_GECKO_PORTF_NAME	DT_SILABS_EFM32_GPIO_PORT_4000A0F0_LABEL
#define DT_GPIO_GECKO_PORTI_NAME	DT_SILABS_EFM32_GPIO_PORT_4000A180_LABEL
#define DT_GPIO_GECKO_PORTJ_NAME	DT_SILABS_EFM32_GPIO_PORT_4000A1C0_LABEL
#define DT_GPIO_GECKO_PORTK_NAME	DT_SILABS_EFM32_GPIO_PORT_4000A1F0_LABEL

#define DT_WDT_0_NAME			DT_INST_0_SILABS_GECKO_WDOG_LABEL
#define DT_WDT_1_NAME			DT_INST_1_SILABS_GECKO_WDOG_LABEL

/* End of SoC Level DTS fixup file */
