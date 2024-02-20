/*
 * Copyright 2017-2022,2024 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DT_BINDINGS_CLOCK_IMX_CCM_H_
#define ZEPHYR_INCLUDE_DT_BINDINGS_CLOCK_IMX_CCM_H_

/*
 * Define 16 bits clock ID: 0xXXXX
 * The highest 8 bits is Peripheral ID
 * The lowest 8 bits is Instance ID
 */
#define IMX_CCM_PERIPHERAL_MASK		0xFF00UL
#define IMX_CCM_INSTANCE_MASK		0x00FFUL

#define IMX_CCM_CORESYS_CLK		0x0000UL
#define IMX_CCM_PLATFORM_CLK		0x0100UL
#define IMX_CCM_BUS_CLK			0x0200UL

#define IMX_CCM_LPUART_CLK		0x0300UL
#define IMX_CCM_LPUART1_CLK		0x0300UL
#define IMX_CCM_LPUART2_CLK		0x0301UL
#define IMX_CCM_LPUART3_CLK		0x0302UL
#define IMX_CCM_LPUART4_CLK		0x0303UL
#define IMX_CCM_LPUART5_CLK		0x0304UL
#define IMX_CCM_LPUART6_CLK		0x0305UL
#define IMX_CCM_LPUART7_CLK		0x0306UL
#define IMX_CCM_LPUART8_CLK		0x0307UL

#define IMX_CCM_LPI2C_CLK		0x0400UL

#define IMX_CCM_LPSPI_CLK		0x0500UL

#define IMX_CCM_USDHC1_CLK		0x0600UL
#define IMX_CCM_USDHC2_CLK		0x0601UL

#define IMX_CCM_EDMA_CLK		0x0700UL

#define IMX_CCM_UART1_CLK		0x0800UL
#define IMX_CCM_UART2_CLK		0x0801UL
#define IMX_CCM_UART3_CLK		0x0802UL
#define IMX_CCM_UART4_CLK		0x0803UL

#define IMX_CCM_CAN_CLK			0x0900UL

#define IMX_CCM_GPT_CLK			0x0A00UL

#define IMX_CCM_SAI1_CLK		0x0B00UL
#define IMX_CCM_SAI2_CLK		0x0B01UL
#define IMX_CCM_SAI3_CLK		0x0B02UL

#define IMX_CCM_PWM_CLK			0x0C00UL

#define IMX_CCM_QTMR_CLK		0x0D00UL

#define IMX_CCM_ENET_CLK		0x0E00UL
#define IMX_CCM_ENET_PLL		0x0E01UL

#define IMX_CCM_FLEXSPI_CLK		0x0F00UL
#define IMX_CCM_FLEXSPI2_CLK		0x0F01UL

#define IMX_CCM_PIT_CLK                 0x1000UL

#define IMX_CCM_FLEXIO1_CLK		0x1100UL
#define IMX_CCM_FLEXIO2_3_CLK		0x1101UL

#define IMX_CCM_ECSPI1_CLK		0x1200UL
#define IMX_CCM_ECSPI2_CLK		0x1201UL
#define IMX_CCM_ECSPI3_CLK		0x1202UL

#endif /* ZEPHYR_INCLUDE_DT_BINDINGS_CLOCK_IMX_CCM_H_ */
