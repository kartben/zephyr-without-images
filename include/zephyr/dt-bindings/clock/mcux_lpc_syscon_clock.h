/*
 * Copyright 2020-2024 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DT_BINDINGS_CLOCK_MCUX_LPC_SYSCON_H_
#define ZEPHYR_INCLUDE_DT_BINDINGS_CLOCK_MCUX_LPC_SYSCON_H_

/* Note- clock identifiers in this file must be unique,
 * as the driver uses them in a switch case
 */

#define MCUX_LPC_CLK_ID(high, low) ((high << 8) | (low))

/* These IDs are used within SOC macros, and thus cannot be defined
 * using the standard MCUX_LPC_CLK_ID form
 */
#define MCUX_CTIMER0_CLK		0
#define MCUX_CTIMER1_CLK		1
#define MCUX_CTIMER2_CLK		2
#define MCUX_CTIMER3_CLK		3
#define MCUX_CTIMER4_CLK		4

#define MCUX_FLEXCOMM0_CLK		MCUX_LPC_CLK_ID(0x01, 0x00)
#define MCUX_FLEXCOMM1_CLK		MCUX_LPC_CLK_ID(0x01, 0x01)
#define MCUX_FLEXCOMM2_CLK		MCUX_LPC_CLK_ID(0x01, 0x02)
#define MCUX_FLEXCOMM3_CLK		MCUX_LPC_CLK_ID(0x01, 0x03)
#define MCUX_FLEXCOMM4_CLK		MCUX_LPC_CLK_ID(0x01, 0x04)
#define MCUX_FLEXCOMM5_CLK		MCUX_LPC_CLK_ID(0x01, 0x05)
#define MCUX_FLEXCOMM6_CLK		MCUX_LPC_CLK_ID(0x01, 0x06)
#define MCUX_FLEXCOMM7_CLK		MCUX_LPC_CLK_ID(0x01, 0x07)
#define MCUX_FLEXCOMM8_CLK		MCUX_LPC_CLK_ID(0x01, 0x08)
#define MCUX_FLEXCOMM9_CLK		MCUX_LPC_CLK_ID(0x01, 0x09)
#define MCUX_FLEXCOMM10_CLK		MCUX_LPC_CLK_ID(0x01, 0x0A)
#define MCUX_FLEXCOMM11_CLK		MCUX_LPC_CLK_ID(0x01, 0x0B)
#define MCUX_FLEXCOMM12_CLK		MCUX_LPC_CLK_ID(0x01, 0x0C)
#define MCUX_FLEXCOMM13_CLK		MCUX_LPC_CLK_ID(0x01, 0x0D)
#define MCUX_HS_SPI_CLK			MCUX_LPC_CLK_ID(0x01, 0x0E)
#define MCUX_FLEXCOMM14_CLK		MCUX_HS_SPI_CLK
#define MCUX_PMIC_I2C_CLK		MCUX_LPC_CLK_ID(0x01, 0x0F)
#define MCUX_HS_SPI1_CLK		MCUX_LPC_CLK_ID(0x01, 0x10)

#define MCUX_USDHC1_CLK			MCUX_LPC_CLK_ID(0x02, 0x00)
#define MCUX_USDHC2_CLK			MCUX_LPC_CLK_ID(0x02, 0x01)

#define MCUX_MCAN_CLK			MCUX_LPC_CLK_ID(0x03, 0x00)

#define MCUX_BUS_CLK			MCUX_LPC_CLK_ID(0x04, 0x00)

#define MCUX_SDIF_CLK			MCUX_LPC_CLK_ID(0x05, 0x00)

#define MCUX_I3C_CLK			MCUX_LPC_CLK_ID(0x06, 0x00)

#define MCUX_MIPI_DSI_DPHY_CLK		MCUX_LPC_CLK_ID(0x07, 0x00)
#define MCUX_MIPI_DSI_ESC_CLK		MCUX_LPC_CLK_ID(0x07, 0x01)

#define MCUX_LCDIF_PIXEL_CLK		MCUX_LPC_CLK_ID(0x08, 0x00)

#define MCUX_SCTIMER_CLK		MCUX_LPC_CLK_ID(0x09, 0x00)

#define MCUX_DMIC_CLK			MCUX_LPC_CLK_ID(0x0A, 0x00)

#define MCUX_FLEXSPI_CLK		MCUX_LPC_CLK_ID(0x0A, 0x00)
#define MCUX_FLEXSPI2_CLK		MCUX_LPC_CLK_ID(0x0A, 0x01)

#define MCUX_MRT_CLK			MCUX_LPC_CLK_ID(0x0B, 0x00)
#define MCUX_FREEMRT_CLK		MCUX_LPC_CLK_ID(0x0B, 0x01)

#define MCUX_PORT0_CLK			MCUX_LPC_CLK_ID(0x0C, 0x00)
#define MCUX_PORT1_CLK			MCUX_LPC_CLK_ID(0x0C, 0x01)
#define MCUX_PORT2_CLK			MCUX_LPC_CLK_ID(0x0C, 0x02)
#define MCUX_PORT3_CLK			MCUX_LPC_CLK_ID(0x0C, 0x03)
#define MCUX_PORT4_CLK			MCUX_LPC_CLK_ID(0x0C, 0x04)
#define MCUX_PORT5_CLK			MCUX_LPC_CLK_ID(0x0C, 0x05)

#define MCUX_ENET_QOS_CLK		MCUX_LPC_CLK_ID(0x0D, 0x00)

#define MCUX_LCDIC_CLK			MCUX_LPC_CLK_ID(0x0E, 0x00)

#define MCUX_LPADC1_CLK			MCUX_LPC_CLK_ID(0x0F, 0x00)
#define MCUX_LPADC2_CLK			MCUX_LPC_CLK_ID(0x0F, 0x01)

#endif /* ZEPHYR_INCLUDE_DT_BINDINGS_CLOCK_MCUX_LPC_SYSCON_H_ */
