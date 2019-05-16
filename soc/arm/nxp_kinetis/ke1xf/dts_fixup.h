/*
 * Copyright (c) 2019 Vestas Wind Systems A/S
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* SoC level DTS fixup file */
#define DT_NUM_IRQ_PRIO_BITS			DT_ARM_V7M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS

#define DT_SIM_NAME				DT_NXP_KINETIS_SIM_40048000_LABEL
#ifdef DT_NXP_KINETIS_SIM_40048000_CLKOUT_DIVIDER
#define DT_SIM_CLKOUT_DIVIDER			DT_NXP_KINETIS_SIM_40048000_CLKOUT_DIVIDER
#endif /* DT_NXP_KINETIS_SIM_40048000_CLKOUT_DIVIDER */
#ifdef DT_NXP_KINETIS_SIM_40048000_CLKOUT_SOURCE
#define DT_SIM_CLKOUT_SOURCE			DT_NXP_KINETIS_SIM_40048000_CLKOUT_SOURCE
#endif /* DT_NXP_KINETIS_SIM_40048000_CLKOUT_SOURCE */

#define DT_MCUX_PCC_0_NAME			DT_NXP_KINETIS_PCC_40065000_LABEL
#define DT_MCUX_PCC_0_BASE_ADDRESS		DT_NXP_KINETIS_PCC_40065000_BASE_ADDRESS

#define CONFIG_RTC_0_NAME			DT_NXP_KINETIS_RTC_4003D000_LABEL
#define CONFIG_RTC_PRESCALER			DT_NXP_KINETIS_RTC_4003D000_PRESCALER
#define DT_RTC_0_NAME				DT_NXP_KINETIS_RTC_4003D000_LABEL
#define DT_RTC_MCUX_0_NAME			DT_NXP_KINETIS_RTC_4003D000_LABEL
#define DT_RTC_MCUX_0_BASE_ADDRESS		DT_NXP_KINETIS_RTC_4003D000_BASE_ADDRESS
#define DT_RTC_MCUX_0_IRQ			DT_NXP_KINETIS_RTC_4003D000_IRQ_ALARM
#define DT_RTC_MCUX_0_IRQ_PRI			DT_NXP_KINETIS_RTC_4003D000_IRQ_ALARM_PRIORITY

#define DT_FLASH_DEV_BASE_ADDRESS		DT_NXP_KINETIS_FTFE_40020000_BASE_ADDRESS
#define DT_FLASH_DEV_NAME			DT_NXP_KINETIS_FTFE_40020000_LABEL

#define DT_UART_MCUX_LPUART_0_BAUD_RATE		DT_NXP_KINETIS_LPUART_4006A000_CURRENT_SPEED
#define DT_UART_MCUX_LPUART_0_NAME		DT_NXP_KINETIS_LPUART_4006A000_LABEL
#define DT_UART_MCUX_LPUART_0_IRQ_0		DT_NXP_KINETIS_LPUART_4006A000_IRQ_RECEIVE
#define DT_UART_MCUX_LPUART_0_IRQ_0_PRI		DT_NXP_KINETIS_LPUART_4006A000_IRQ_RECEIVE_PRIORITY
#define DT_UART_MCUX_LPUART_0_IRQ_1		DT_NXP_KINETIS_LPUART_4006A000_IRQ_TRANSMIT
#define DT_UART_MCUX_LPUART_0_IRQ_1_PRI		DT_NXP_KINETIS_LPUART_4006A000_IRQ_TRANSMIT_PRIORITY
#define DT_UART_MCUX_LPUART_0_HW_FLOW_CONTROL	DT_NXP_KINETIS_LPUART_4006A000_HW_FLOW_CONTROL
#define DT_UART_MCUX_LPUART_0_CLOCK_NAME	DT_NXP_KINETIS_LPUART_4006A000_CLOCK_CONTROLLER
#define DT_UART_MCUX_LPUART_0_CLOCK_SUBSYS	DT_NXP_KINETIS_LPUART_4006A000_CLOCK_NAME

#define DT_UART_MCUX_LPUART_1_BAUD_RATE		DT_NXP_KINETIS_LPUART_4006B000_CURRENT_SPEED
#define DT_UART_MCUX_LPUART_1_NAME		DT_NXP_KINETIS_LPUART_4006B000_LABEL
#define DT_UART_MCUX_LPUART_1_IRQ_0		DT_NXP_KINETIS_LPUART_4006B000_IRQ_RECEIVE
#define DT_UART_MCUX_LPUART_1_IRQ_0_PRI		DT_NXP_KINETIS_LPUART_4006B000_IRQ_RECEIVE_PRIORITY
#define DT_UART_MCUX_LPUART_1_IRQ_1		DT_NXP_KINETIS_LPUART_4006B000_IRQ_TRANSMIT
#define DT_UART_MCUX_LPUART_1_IRQ_1_PRI		DT_NXP_KINETIS_LPUART_4006B000_IRQ_TRANSMIT_PRIORITY
#define DT_UART_MCUX_LPUART_1_HW_FLOW_CONTROL	DT_NXP_KINETIS_LPUART_4006B000_HW_FLOW_CONTROL
#define DT_UART_MCUX_LPUART_1_CLOCK_NAME	DT_NXP_KINETIS_LPUART_4006B000_CLOCK_CONTROLLER
#define DT_UART_MCUX_LPUART_1_CLOCK_SUBSYS	DT_NXP_KINETIS_LPUART_4006B000_CLOCK_NAME

#define DT_UART_MCUX_LPUART_2_BAUD_RATE		DT_NXP_KINETIS_LPUART_4006C000_CURRENT_SPEED
#define DT_UART_MCUX_LPUART_2_NAME		DT_NXP_KINETIS_LPUART_4006C000_LABEL
#define DT_UART_MCUX_LPUART_2_IRQ_0		DT_NXP_KINETIS_LPUART_4006C000_IRQ_RECEIVE
#define DT_UART_MCUX_LPUART_2_IRQ_0_PRI		DT_NXP_KINETIS_LPUART_4006C000_IRQ_RECEIVE_PRIORITY
#define DT_UART_MCUX_LPUART_2_IRQ_1		DT_NXP_KINETIS_LPUART_4006C000_IRQ_TRANSMIT
#define DT_UART_MCUX_LPUART_2_IRQ_1_PRI		DT_NXP_KINETIS_LPUART_4006C000_IRQ_TRANSMIT_PRIORITY
#define DT_UART_MCUX_LPUART_2_HW_FLOW_CONTROL	DT_NXP_KINETIS_LPUART_4006C000_HW_FLOW_CONTROL
#define DT_UART_MCUX_LPUART_2_CLOCK_NAME	DT_NXP_KINETIS_LPUART_4006C000_CLOCK_CONTROLLER
#define DT_UART_MCUX_LPUART_2_CLOCK_SUBSYS	DT_NXP_KINETIS_LPUART_4006C000_CLOCK_NAME

