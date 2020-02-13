/*
 * Copyright (c) 2019 Synopsys, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* SoC level DTS fixup file */

/*
 * UART configuration
 */
#define DT_UART_NS16550_PORT_0_BASE_ADDR DT_NS16550_F0005000_BASE_ADDRESS
#define DT_UART_NS16550_PORT_0_IRQ	 DT_NS16550_F0005000_IRQ_0
#define DT_UART_NS16550_PORT_0_CLK_FREQ	 DT_NS16550_F0005000_CLOCK_FREQUENCY
#define DT_UART_NS16550_PORT_0_BAUD_RATE DT_NS16550_F0005000_CURRENT_SPEED
#define DT_UART_NS16550_PORT_0_NAME	 DT_NS16550_F0005000_LABEL
#define DT_UART_NS16550_PORT_0_IRQ_PRI	 DT_NS16550_F0005000_IRQ_0_PRIORITY

/*
 * GPIO configuration
 */
#define DT_INST_0_SNPS_DESIGNWARE_GPIO_IRQ_0_FLAGS	0

/*
 * SPI configuration
 */

#define DT_SPI_DW_0_BASE_ADDRESS	\
	DT_SNPS_DESIGNWARE_SPI_F0020000_BASE_ADDRESS
#define DT_SPI_DW_0_CLOCK_FREQUENCY	\
	DT_SNPS_DESIGNWARE_SPI_F0020000_CLOCK_FREQUENCY
#define DT_SPI_DW_0_NAME		DT_SNPS_DESIGNWARE_SPI_F0020000_LABEL
#define DT_SPI_DW_0_IRQ			DT_SNPS_DESIGNWARE_SPI_F0020000_IRQ_0
#define DT_SPI_DW_0_IRQ_PRI		\
	DT_SNPS_DESIGNWARE_SPI_F0020000_IRQ_0_PRIORITY
#define DT_SPI_DW_0_IRQ_FLAGS		0


#define DT_SPI_DW_1_BASE_ADDRESS	\
	DT_SNPS_DESIGNWARE_SPI_F0021000_BASE_ADDRESS
#define DT_SPI_DW_1_CLOCK_FREQUENCY	\
	DT_SNPS_DESIGNWARE_SPI_F0021000_CLOCK_FREQUENCY
#define DT_SPI_DW_1_NAME		DT_SNPS_DESIGNWARE_SPI_F0021000_LABEL
#define DT_SPI_DW_1_IRQ			DT_SNPS_DESIGNWARE_SPI_F0021000_IRQ_0
#define DT_SPI_DW_1_IRQ_PRI		\
	DT_SNPS_DESIGNWARE_SPI_F0021000_IRQ_0_PRIORITY
#define DT_SPI_DW_1_IRQ_FLAGS		0


#define DT_SPI_DW_2_BASE_ADDRESS	\
	DT_SNPS_DESIGNWARE_SPI_F0022000_BASE_ADDRESS
#define DT_SPI_DW_2_CLOCK_FREQUENCY	\
	DT_SNPS_DESIGNWARE_SPI_F0022000_CLOCK_FREQUENCY
#define DT_SPI_DW_2_NAME		DT_SNPS_DESIGNWARE_SPI_F0022000_LABEL
#define DT_SPI_DW_2_IRQ			DT_SNPS_DESIGNWARE_SPI_F0022000_IRQ_0
#define DT_SPI_DW_2_IRQ_PRI		\
	DT_SNPS_DESIGNWARE_SPI_F0022000_IRQ_0_PRIORITY
#define DT_SPI_DW_2_IRQ_FLAGS		0

/* For spi_fujistu_fram sample */
#define DT_SPI_1_NAME			DT_SPI_DW_1_NAME

/* End of SoC Level DTS fixup file */
