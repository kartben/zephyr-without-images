/*
 * Copyright (c) 2017, NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* SoC level DTS fixup file */

#define DT_NUM_IRQ_PRIO_BITS		DT_ARM_V7M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS

#define DT_MCUX_CCM_BASE_ADDRESS		DT_NXP_IMX_CCM_400FC000_BASE_ADDRESS
#define DT_MCUX_CCM_NAME			DT_NXP_IMX_CCM_400FC000_LABEL

#define DT_MCUX_IGPIO_1_BASE_ADDRESS	DT_NXP_IMX_GPIO_401B8000_BASE_ADDRESS
#define DT_MCUX_IGPIO_1_NAME		DT_NXP_IMX_GPIO_401B8000_LABEL
#define DT_MCUX_IGPIO_1_IRQ_0		DT_NXP_IMX_GPIO_401B8000_IRQ_0
#define DT_MCUX_IGPIO_1_IRQ_0_PRI		DT_NXP_IMX_GPIO_401B8000_IRQ_0_PRIORITY
#define DT_MCUX_IGPIO_1_IRQ_1		DT_NXP_IMX_GPIO_401B8000_IRQ_1
#define DT_MCUX_IGPIO_1_IRQ_1_PRI		DT_NXP_IMX_GPIO_401B8000_IRQ_1_PRIORITY

#define DT_MCUX_IGPIO_5_BASE_ADDRESS	DT_NXP_IMX_GPIO_400C0000_BASE_ADDRESS
#define DT_MCUX_IGPIO_5_NAME		DT_NXP_IMX_GPIO_400C0000_LABEL
#define DT_MCUX_IGPIO_5_IRQ_0		DT_NXP_IMX_GPIO_400C0000_IRQ_0
#define DT_MCUX_IGPIO_5_IRQ_0_PRI		DT_NXP_IMX_GPIO_400C0000_IRQ_0_PRIORITY
#define DT_MCUX_IGPIO_5_IRQ_1		DT_NXP_IMX_GPIO_400C0000_IRQ_1
#define DT_MCUX_IGPIO_5_IRQ_1_PRI		DT_NXP_IMX_GPIO_400C0000_IRQ_1_PRIORITY

#define DT_UART_MCUX_LPUART_1_BASE_ADDRESS	DT_NXP_KINETIS_LPUART_40184000_BASE_ADDRESS
#define DT_UART_MCUX_LPUART_1_NAME		DT_NXP_KINETIS_LPUART_40184000_LABEL
#define DT_UART_MCUX_LPUART_1_IRQ		DT_NXP_KINETIS_LPUART_40184000_IRQ_0
#define DT_UART_MCUX_LPUART_1_IRQ_PRI	DT_NXP_KINETIS_LPUART_40184000_IRQ_0_PRIORITY
#define DT_UART_MCUX_LPUART_1_BAUD_RATE	DT_NXP_KINETIS_LPUART_40184000_CURRENT_SPEED
#define DT_UART_MCUX_LPUART_1_CLOCK_NAME	DT_NXP_KINETIS_LPUART_40184000_CLOCK_CONTROLLER
#define DT_UART_MCUX_LPUART_1_CLOCK_SUBSYS	DT_NXP_KINETIS_LPUART_40184000_CLOCK_NAME

#define DT_UART_MCUX_LPUART_2_BASE_ADDRESS	DT_NXP_KINETIS_LPUART_40188000_BASE_ADDRESS
#define DT_UART_MCUX_LPUART_2_NAME		DT_NXP_KINETIS_LPUART_40188000_LABEL
#define DT_UART_MCUX_LPUART_2_IRQ		DT_NXP_KINETIS_LPUART_40188000_IRQ_0
#define DT_UART_MCUX_LPUART_2_IRQ_PRI		DT_NXP_KINETIS_LPUART_40188000_IRQ_0_PRIORITY
#define DT_UART_MCUX_LPUART_2_BAUD_RATE		DT_NXP_KINETIS_LPUART_40188000_CURRENT_SPEED
#define DT_UART_MCUX_LPUART_2_CLOCK_NAME	DT_NXP_KINETIS_LPUART_40188000_CLOCK_CONTROLLER
#define DT_UART_MCUX_LPUART_2_CLOCK_SUBSYS	DT_NXP_KINETIS_LPUART_40188000_CLOCK_NAME

#define DT_UART_MCUX_LPUART_3_BASE_ADDRESS	DT_NXP_KINETIS_LPUART_4018C000_BASE_ADDRESS
#define DT_UART_MCUX_LPUART_3_NAME		DT_NXP_KINETIS_LPUART_4018C000_LABEL
#define DT_UART_MCUX_LPUART_3_IRQ		DT_NXP_KINETIS_LPUART_4018C000_IRQ_0
#define DT_UART_MCUX_LPUART_3_IRQ_PRI	DT_NXP_KINETIS_LPUART_4018C000_IRQ_0_PRIORITY
#define DT_UART_MCUX_LPUART_3_BAUD_RATE	DT_NXP_KINETIS_LPUART_4018C000_CURRENT_SPEED
#define DT_UART_MCUX_LPUART_3_CLOCK_NAME	DT_NXP_KINETIS_LPUART_4018C000_CLOCK_CONTROLLER
#define DT_UART_MCUX_LPUART_3_CLOCK_SUBSYS	DT_NXP_KINETIS_LPUART_4018C000_CLOCK_NAME

#define DT_ETH_MCUX_0_NAME  DT_NXP_KINETIS_ETHERNET_402D8000_LABEL

#define DT_ETH_MCUX_0_MAC3  DT_NXP_KINETIS_ETHERNET_402D8000_LOCAL_MAC_ADDRESS_3
#define DT_ETH_MCUX_0_MAC4  DT_NXP_KINETIS_ETHERNET_402D8000_LOCAL_MAC_ADDRESS_4
#define DT_ETH_MCUX_0_MAC5  DT_NXP_KINETIS_ETHERNET_402D8000_LOCAL_MAC_ADDRESS_5

#define DT_IRQ_ETH_COMMON   DT_NXP_KINETIS_ETHERNET_402D8000_IRQ_0
#define DT_IRQ_ETH_IEEE1588_TMR		DT_NXP_KINETIS_PTP_402D8000_PTP_IRQ_0
#define DT_ETH_MCUX_0_IRQ_PRI   DT_NXP_KINETIS_ETHERNET_402D8000_IRQ_0_PRIORITY

#define DT_ENTROPY_MCUX_TRNG_BASE_ADDRESS	DT_NXP_KINETIS_TRNG_400CC000_BASE_ADDRESS
#define DT_ENTROPY_MCUX_TRNG_IRQ		DT_NXP_KINETIS_TRNG_400CC000_IRQ_0
#define DT_ENTROPY_MCUX_TRNG_IRQ_PRI		DT_NXP_KINETIS_TRNG_400CC000_IRQ_0_PRIORITY
#define DT_ENTROPY_MCUX_TRNG_NAME		DT_NXP_KINETIS_TRNG_400CC000_LABEL
#define CONFIG_ENTROPY_NAME			DT_NXP_KINETIS_TRNG_400CC000_LABEL

/* End of SoC Level DTS fixup file */
