/*
 * Copyright (c) 2019 Vestas Wind Systems A/S
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* SoC level DTS fixup file */
#define DT_NUM_IRQ_PRIO_BITS			DT_ARM_V7M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS

#define DT_SIM_NAME				DT_NXP_KINETIS_KE1XF_SIM_40048000_LABEL
#ifdef DT_NXP_KINETIS_KE1XF_SIM_40048000_CLKOUT_DIVIDER
#define DT_SIM_CLKOUT_DIVIDER			DT_NXP_KINETIS_KE1XF_SIM_40048000_CLKOUT_DIVIDER
#endif /* DT_NXP_KINETIS_KE1XF_SIM_40048000_CLKOUT_DIVIDER */
#ifdef DT_NXP_KINETIS_KE1XF_SIM_40048000_CLKOUT_SOURCE
#define DT_SIM_CLKOUT_SOURCE			DT_NXP_KINETIS_KE1XF_SIM_40048000_CLKOUT_SOURCE
#endif /* DT_NXP_KINETIS_KE1XF_SIM_40048000_CLKOUT_SOURCE */

#define DT_MCUX_PCC_0_NAME			DT_NXP_KINETIS_PCC_40065000_LABEL
#define DT_MCUX_PCC_0_BASE_ADDRESS		DT_NXP_KINETIS_PCC_40065000_BASE_ADDRESS

#define DT_RTC_0_NAME				DT_NXP_KINETIS_RTC_4003D000_LABEL

#define DT_FLASH_DEV_BASE_ADDRESS		DT_NXP_KINETIS_FTFE_40020000_BASE_ADDRESS
#define DT_FLASH_DEV_NAME			DT_NXP_KINETIS_FTFE_40020000_LABEL

#define DT_ADC_0_NAME				DT_NXP_KINETIS_ADC12_4003B000_LABEL
#define DT_ADC_1_NAME				DT_NXP_KINETIS_ADC12_40027000_LABEL
#define DT_ADC_2_NAME				DT_NXP_KINETIS_ADC12_4003C000_LABEL

#define DT_WDT_0_NAME				DT_NXP_KINETIS_WDOG32_40052000_LABEL

#define DT_SPI_0_NAME			DT_NXP_IMX_LPSPI_4002C000_LABEL
#define DT_SPI_0_BASE_ADDRESS		DT_NXP_IMX_LPSPI_4002C000_BASE_ADDRESS
#define DT_SPI_0_IRQ			DT_NXP_IMX_LPSPI_4002C000_IRQ_0
#define DT_SPI_0_IRQ_PRI		DT_NXP_IMX_LPSPI_4002C000_IRQ_0_PRIORITY
#define DT_SPI_0_CLOCK_NAME		DT_NXP_IMX_LPSPI_4002C000_CLOCK_CONTROLLER
#define DT_SPI_0_CLOCK_SUBSYS		DT_NXP_IMX_LPSPI_4002C000_CLOCK_NAME
#define DT_SPI_1_NAME			DT_NXP_IMX_LPSPI_4002D000_LABEL
#define DT_SPI_1_BASE_ADDRESS		DT_NXP_IMX_LPSPI_4002D000_BASE_ADDRESS
#define DT_SPI_1_IRQ			DT_NXP_IMX_LPSPI_4002D000_IRQ_0
#define DT_SPI_1_IRQ_PRI		DT_NXP_IMX_LPSPI_4002D000_IRQ_0_PRIORITY
#define DT_SPI_1_CLOCK_NAME		DT_NXP_IMX_LPSPI_4002D000_CLOCK_CONTROLLER
#define DT_SPI_1_CLOCK_SUBSYS		DT_NXP_IMX_LPSPI_4002D000_CLOCK_NAME

#define DT_CAN_0_NAME				DT_NXP_KINETIS_FLEXCAN_40024000_LABEL
#define DT_CAN_1_NAME				DT_NXP_KINETIS_FLEXCAN_40025000_LABEL
