/*
 * Copyright (c) 2018 Synopsys, Inc. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* SoC level DTS fixup file */

/* CCM configuration */
#define CONFIG_DCCM_BASE_ADDRESS       ARC_DCCM_80000000_BASE_ADDRESS
#define CONFIG_DCCM_SIZE               (ARC_DCCM_80000000_SIZE >> 10)

#define CONFIG_ICCM_BASE_ADDRESS       ARC_ICCM_20000000_BASE_ADDRESS
#define CONFIG_ICCM_SIZE               (ARC_ICCM_20000000_SIZE	 >> 10)

/*
 * UART configuration
 */
#define CONFIG_UART_NS16550_PORT_0_BASE_ADDR NS16550_80014000_BASE_ADDRESS
#define CONFIG_UART_NS16550_PORT_0_IRQ		 NS16550_80014000_IRQ_0
#define CONFIG_UART_NS16550_PORT_0_CLK_FREQ	 NS16550_80014000_CLOCK_FREQUENCY
#define CONFIG_UART_NS16550_PORT_0_BAUD_RATE NS16550_80014000_CURRENT_SPEED
#define CONFIG_UART_NS16550_PORT_0_NAME		 NS16550_80014000_LABEL
#define CONFIG_UART_NS16550_PORT_0_IRQ_PRI	 NS16550_80014000_IRQ_0_PRIORITY

#define CONFIG_UART_NS16550_PORT_1_BASE_ADDR NS16550_80014100_BASE_ADDRESS
#define CONFIG_UART_NS16550_PORT_1_IRQ		 NS16550_80014100_IRQ_0
#define CONFIG_UART_NS16550_PORT_1_CLK_FREQ	 NS16550_80014100_CLOCK_FREQUENCY
#define CONFIG_UART_NS16550_PORT_1_BAUD_RATE NS16550_80014100_CURRENT_SPEED
#define CONFIG_UART_NS16550_PORT_1_NAME		 NS16550_80014100_LABEL
#define CONFIG_UART_NS16550_PORT_1_IRQ_PRI	 NS16550_80014100_IRQ_0_PRIORITY

#define CONFIG_UART_NS16550_PORT_2_BASE_ADDR NS16550_80014200_BASE_ADDRESS
#define CONFIG_UART_NS16550_PORT_2_IRQ		 NS16550_80014200_IRQ_0
#define CONFIG_UART_NS16550_PORT_2_CLK_FREQ	 NS16550_80014200_CLOCK_FREQUENCY
#define CONFIG_UART_NS16550_PORT_2_BAUD_RATE NS16550_80014200_CURRENT_SPEED
#define CONFIG_UART_NS16550_PORT_2_NAME		 NS16550_80014200_LABEL
#define CONFIG_UART_NS16550_PORT_2_IRQ_PRI	 NS16550_80014200_IRQ_0_PRIORITY


#define CONFIG_UART_NS16550_PORT_3_BASE_ADDR NS16550_80014300_BASE_ADDRESS
#define CONFIG_UART_NS16550_PORT_3_IRQ		 NS16550_80014300_IRQ_0
#define CONFIG_UART_NS16550_PORT_3_CLK_FREQ	 NS16550_80014300_CLOCK_FREQUENCY
#define CONFIG_UART_NS16550_PORT_3_BAUD_RATE NS16550_80014300_CURRENT_SPEED
#define CONFIG_UART_NS16550_PORT_3_NAME		 NS16550_80014300_LABEL
#define CONFIG_UART_NS16550_PORT_3_IRQ_PRI	 NS16550_80014300_IRQ_0_PRIORITY


/* End of SoC Level DTS fixup file */
