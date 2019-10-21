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
#define DT_RTC_MCUX_0_NAME			DT_NXP_KINETIS_RTC_4003D000_LABEL
#define DT_RTC_MCUX_0_BASE_ADDRESS		DT_NXP_KINETIS_RTC_4003D000_BASE_ADDRESS
#define DT_RTC_MCUX_0_IRQ			DT_NXP_KINETIS_RTC_4003D000_IRQ_ALARM
#define DT_RTC_MCUX_0_IRQ_PRI			DT_NXP_KINETIS_RTC_4003D000_IRQ_ALARM_PRIORITY

#define DT_FLASH_DEV_BASE_ADDRESS		DT_NXP_KINETIS_FTFE_40020000_BASE_ADDRESS
#define DT_FLASH_DEV_NAME			DT_NXP_KINETIS_FTFE_40020000_LABEL

#define DT_UART_MCUX_LPUART_0_BASE_ADDRESS	DT_NXP_KINETIS_LPUART_4006A000_BASE_ADDRESS
#define DT_UART_MCUX_LPUART_0_BAUD_RATE		DT_NXP_KINETIS_LPUART_4006A000_CURRENT_SPEED
#define DT_UART_MCUX_LPUART_0_NAME		DT_NXP_KINETIS_LPUART_4006A000_LABEL
#define DT_UART_MCUX_LPUART_0_IRQ_0		DT_NXP_KINETIS_LPUART_4006A000_IRQ_RECEIVE
#define DT_UART_MCUX_LPUART_0_IRQ_0_PRI		DT_NXP_KINETIS_LPUART_4006A000_IRQ_RECEIVE_PRIORITY
#define DT_UART_MCUX_LPUART_0_IRQ_1		DT_NXP_KINETIS_LPUART_4006A000_IRQ_TRANSMIT
#define DT_UART_MCUX_LPUART_0_IRQ_1_PRI		DT_NXP_KINETIS_LPUART_4006A000_IRQ_TRANSMIT_PRIORITY
#define DT_UART_MCUX_LPUART_0_HW_FLOW_CONTROL	DT_NXP_KINETIS_LPUART_4006A000_HW_FLOW_CONTROL
#define DT_UART_MCUX_LPUART_0_CLOCK_NAME	DT_NXP_KINETIS_LPUART_4006A000_CLOCK_CONTROLLER
#define DT_UART_MCUX_LPUART_0_CLOCK_SUBSYS	DT_NXP_KINETIS_LPUART_4006A000_CLOCK_NAME

#define DT_UART_MCUX_LPUART_1_BASE_ADDRESS	DT_NXP_KINETIS_LPUART_4006B000_BASE_ADDRESS
#define DT_UART_MCUX_LPUART_1_BAUD_RATE		DT_NXP_KINETIS_LPUART_4006B000_CURRENT_SPEED
#define DT_UART_MCUX_LPUART_1_NAME		DT_NXP_KINETIS_LPUART_4006B000_LABEL
#define DT_UART_MCUX_LPUART_1_IRQ_0		DT_NXP_KINETIS_LPUART_4006B000_IRQ_RECEIVE
#define DT_UART_MCUX_LPUART_1_IRQ_0_PRI		DT_NXP_KINETIS_LPUART_4006B000_IRQ_RECEIVE_PRIORITY
#define DT_UART_MCUX_LPUART_1_IRQ_1		DT_NXP_KINETIS_LPUART_4006B000_IRQ_TRANSMIT
#define DT_UART_MCUX_LPUART_1_IRQ_1_PRI		DT_NXP_KINETIS_LPUART_4006B000_IRQ_TRANSMIT_PRIORITY
#define DT_UART_MCUX_LPUART_1_HW_FLOW_CONTROL	DT_NXP_KINETIS_LPUART_4006B000_HW_FLOW_CONTROL
#define DT_UART_MCUX_LPUART_1_CLOCK_NAME	DT_NXP_KINETIS_LPUART_4006B000_CLOCK_CONTROLLER
#define DT_UART_MCUX_LPUART_1_CLOCK_SUBSYS	DT_NXP_KINETIS_LPUART_4006B000_CLOCK_NAME

#define DT_UART_MCUX_LPUART_2_BASE_ADDRESS	DT_NXP_KINETIS_LPUART_4006C000_BASE_ADDRESS
#define DT_UART_MCUX_LPUART_2_BAUD_RATE		DT_NXP_KINETIS_LPUART_4006C000_CURRENT_SPEED
#define DT_UART_MCUX_LPUART_2_NAME		DT_NXP_KINETIS_LPUART_4006C000_LABEL
#define DT_UART_MCUX_LPUART_2_IRQ_0		DT_NXP_KINETIS_LPUART_4006C000_IRQ_RECEIVE
#define DT_UART_MCUX_LPUART_2_IRQ_0_PRI		DT_NXP_KINETIS_LPUART_4006C000_IRQ_RECEIVE_PRIORITY
#define DT_UART_MCUX_LPUART_2_IRQ_1		DT_NXP_KINETIS_LPUART_4006C000_IRQ_TRANSMIT
#define DT_UART_MCUX_LPUART_2_IRQ_1_PRI		DT_NXP_KINETIS_LPUART_4006C000_IRQ_TRANSMIT_PRIORITY
#define DT_UART_MCUX_LPUART_2_HW_FLOW_CONTROL	DT_NXP_KINETIS_LPUART_4006C000_HW_FLOW_CONTROL
#define DT_UART_MCUX_LPUART_2_CLOCK_NAME	DT_NXP_KINETIS_LPUART_4006C000_CLOCK_CONTROLLER
#define DT_UART_MCUX_LPUART_2_CLOCK_SUBSYS	DT_NXP_KINETIS_LPUART_4006C000_CLOCK_NAME

#define CONFIG_I2C_0_NAME			DT_NXP_IMX_LPI2C_40066000_LABEL
#define DT_I2C_MCUX_LPI2C_0_BASE_ADDRESS	DT_NXP_IMX_LPI2C_40066000_BASE_ADDRESS
#define DT_I2C_MCUX_LPI2C_0_IRQ			DT_NXP_IMX_LPI2C_40066000_IRQ_0
#define DT_I2C_MCUX_LPI2C_0_IRQ_PRI		DT_NXP_IMX_LPI2C_40066000_IRQ_0_PRIORITY
#define DT_I2C_MCUX_LPI2C_0_BITRATE		DT_NXP_IMX_LPI2C_40066000_CLOCK_FREQUENCY
#define DT_I2C_MCUX_LPI2C_0_CLOCK_NAME		DT_NXP_IMX_LPI2C_40066000_CLOCK_CONTROLLER
#define DT_I2C_MCUX_LPI2C_0_CLOCK_SUBSYS	DT_NXP_IMX_LPI2C_40066000_CLOCK_NAME

#define CONFIG_I2C_1_NAME			DT_NXP_IMX_LPI2C_40067000_LABEL
#define DT_I2C_MCUX_LPI2C_1_BASE_ADDRESS	DT_NXP_IMX_LPI2C_40067000_BASE_ADDRESS
#define DT_I2C_MCUX_LPI2C_1_IRQ			DT_NXP_IMX_LPI2C_40067000_IRQ_0
#define DT_I2C_MCUX_LPI2C_1_IRQ_PRI		DT_NXP_IMX_LPI2C_40067000_IRQ_0_PRIORITY
#define DT_I2C_MCUX_LPI2C_1_BITRATE		DT_NXP_IMX_LPI2C_40067000_CLOCK_FREQUENCY
#define DT_I2C_MCUX_LPI2C_1_CLOCK_NAME		DT_NXP_IMX_LPI2C_40067000_CLOCK_CONTROLLER
#define DT_I2C_MCUX_LPI2C_1_CLOCK_SUBSYS	DT_NXP_IMX_LPI2C_40067000_CLOCK_NAME

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

#define DT_FTM_0_NAME				DT_NXP_KINETIS_FTM_40038000_LABEL
#define DT_FTM_0_BASE_ADDRESS			DT_NXP_KINETIS_FTM_40038000_BASE_ADDRESS
#define DT_FTM_0_IRQ				DT_NXP_KINETIS_FTM_40038000_IRQ_0
#define DT_FTM_0_IRQ_PRI			DT_NXP_KINETIS_FTM_40038000_IRQ_0_PRIORITY
#define DT_FTM_0_CLOCK_NAME			DT_NXP_KINETIS_FTM_40038000_CLOCK_CONTROLLER
#define DT_FTM_0_CLOCK_SUBSYS			DT_NXP_KINETIS_FTM_40038000_CLOCK_NAME

#define DT_FTM_1_NAME				DT_NXP_KINETIS_FTM_40039000_LABEL
#define DT_FTM_1_BASE_ADDRESS			DT_NXP_KINETIS_FTM_40039000_BASE_ADDRESS
#define DT_FTM_1_IRQ				DT_NXP_KINETIS_FTM_40039000_IRQ_0
#define DT_FTM_1_IRQ_PRI			DT_NXP_KINETIS_FTM_40039000_IRQ_0_PRIORITY
#define DT_FTM_1_CLOCK_NAME			DT_NXP_KINETIS_FTM_40039000_CLOCK_CONTROLLER
#define DT_FTM_1_CLOCK_SUBSYS			DT_NXP_KINETIS_FTM_40039000_CLOCK_NAME

#define DT_FTM_2_NAME				DT_NXP_KINETIS_FTM_4003A000_LABEL
#define DT_FTM_2_BASE_ADDRESS			DT_NXP_KINETIS_FTM_4003A000_BASE_ADDRESS
#define DT_FTM_2_IRQ				DT_NXP_KINETIS_FTM_4003A000_IRQ_0
#define DT_FTM_2_IRQ_PRI			DT_NXP_KINETIS_FTM_4003A000_IRQ_0_PRIORITY
#define DT_FTM_2_CLOCK_NAME			DT_NXP_KINETIS_FTM_4003A000_CLOCK_CONTROLLER
#define DT_FTM_2_CLOCK_SUBSYS			DT_NXP_KINETIS_FTM_4003A000_CLOCK_NAME

#define DT_FTM_3_NAME				DT_NXP_KINETIS_FTM_40026000_LABEL
#define DT_FTM_3_BASE_ADDRESS			DT_NXP_KINETIS_FTM_40026000_BASE_ADDRESS
#define DT_FTM_3_IRQ				DT_NXP_KINETIS_FTM_40026000_IRQ_0
#define DT_FTM_3_IRQ_PRI			DT_NXP_KINETIS_FTM_40026000_IRQ_0_PRIORITY
#define DT_FTM_3_CLOCK_NAME			DT_NXP_KINETIS_FTM_40026000_CLOCK_CONTROLLER
#define DT_FTM_3_CLOCK_SUBSYS			DT_NXP_KINETIS_FTM_40026000_CLOCK_NAME


