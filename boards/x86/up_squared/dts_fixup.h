/*
 * Copyright (c) 2018 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Board level DTS fixup file */

#define CONFIG_UART_NS16550_PORT_0_BASE_ADDR	DT_NS16550_91524000_BASE_ADDRESS
#define CONFIG_UART_NS16550_PORT_0_BAUD_RATE	DT_NS16550_91524000_CURRENT_SPEED
#define CONFIG_UART_NS16550_PORT_0_NAME		DT_NS16550_91524000_LABEL
#define CONFIG_UART_NS16550_PORT_0_IRQ		DT_NS16550_91524000_IRQ_0
#define CONFIG_UART_NS16550_PORT_0_IRQ_PRI	DT_NS16550_91524000_IRQ_0_PRIORITY
#define CONFIG_UART_NS16550_PORT_0_IRQ_FLAGS	DT_NS16550_91524000_IRQ_0_SENSE
#define CONFIG_UART_NS16550_PORT_0_CLK_FREQ	DT_NS16550_91524000_CLOCK_FREQUENCY

#define CONFIG_UART_NS16550_PORT_1_BASE_ADDR	DT_NS16550_91522000_BASE_ADDRESS
#define CONFIG_UART_NS16550_PORT_1_BAUD_RATE	DT_NS16550_91522000_CURRENT_SPEED
#define CONFIG_UART_NS16550_PORT_1_NAME		DT_NS16550_91522000_LABEL
#define CONFIG_UART_NS16550_PORT_1_IRQ		DT_NS16550_91522000_IRQ_0
#define CONFIG_UART_NS16550_PORT_1_IRQ_PRI	DT_NS16550_91522000_IRQ_0_PRIORITY
#define CONFIG_UART_NS16550_PORT_1_IRQ_FLAGS	DT_NS16550_91522000_IRQ_0_SENSE
#define CONFIG_UART_NS16550_PORT_1_CLK_FREQ	DT_NS16550_91522000_CLOCK_FREQUENCY

#define CONFIG_I2C_0_NAME			DT_SNPS_DESIGNWARE_I2C_91534000_LABEL
#define CONFIG_I2C_0_BASE_ADDR			DT_SNPS_DESIGNWARE_I2C_91534000_BASE_ADDRESS
#define CONFIG_I2C_0_IRQ			DT_SNPS_DESIGNWARE_I2C_91534000_IRQ_0
#define CONFIG_I2C_0_IRQ_PRI			DT_SNPS_DESIGNWARE_I2C_91534000_IRQ_0_PRIORITY
#define CONFIG_I2C_0_IRQ_FLAGS			DT_SNPS_DESIGNWARE_I2C_91534000_IRQ_0_SENSE
#define CONFIG_I2C_0_BITRATE			DT_SNPS_DESIGNWARE_I2C_91534000_CLOCK_FREQUENCY

#define CONFIG_I2C_1_NAME			DT_SNPS_DESIGNWARE_I2C_91532000_LABEL
#define CONFIG_I2C_1_BASE_ADDR			DT_SNPS_DESIGNWARE_I2C_91532000_BASE_ADDRESS
#define CONFIG_I2C_1_IRQ			DT_SNPS_DESIGNWARE_I2C_91532000_IRQ_0
#define CONFIG_I2C_1_IRQ_PRI			DT_SNPS_DESIGNWARE_I2C_91532000_IRQ_0_PRIORITY
#define CONFIG_I2C_1_IRQ_FLAGS			DT_SNPS_DESIGNWARE_I2C_91532000_IRQ_0_SENSE
#define CONFIG_I2C_1_BITRATE			DT_SNPS_DESIGNWARE_I2C_91532000_CLOCK_FREQUENCY

#define CONFIG_I2C_2_NAME			DT_SNPS_DESIGNWARE_I2C_91530000_LABEL
#define CONFIG_I2C_2_BASE_ADDR			DT_SNPS_DESIGNWARE_I2C_91530000_BASE_ADDRESS
#define CONFIG_I2C_2_IRQ			DT_SNPS_DESIGNWARE_I2C_91530000_IRQ_0
#define CONFIG_I2C_2_IRQ_PRI			DT_SNPS_DESIGNWARE_I2C_91530000_IRQ_0_PRIORITY
#define CONFIG_I2C_2_IRQ_FLAGS			DT_SNPS_DESIGNWARE_I2C_91530000_IRQ_0_SENSE
#define CONFIG_I2C_2_BITRATE			DT_SNPS_DESIGNWARE_I2C_91530000_CLOCK_FREQUENCY

#define CONFIG_I2C_3_NAME			DT_SNPS_DESIGNWARE_I2C_9152E000_LABEL
#define CONFIG_I2C_3_BASE_ADDR			DT_SNPS_DESIGNWARE_I2C_9152E000_BASE_ADDRESS
#define CONFIG_I2C_3_IRQ			DT_SNPS_DESIGNWARE_I2C_9152E000_IRQ_0
#define CONFIG_I2C_3_IRQ_PRI			DT_SNPS_DESIGNWARE_I2C_9152E000_IRQ_0_PRIORITY
#define CONFIG_I2C_3_IRQ_FLAGS			DT_SNPS_DESIGNWARE_I2C_9152E000_IRQ_0_SENSE
#define CONFIG_I2C_3_BITRATE			DT_SNPS_DESIGNWARE_I2C_9152E000_CLOCK_FREQUENCY

#define CONFIG_I2C_4_NAME			DT_SNPS_DESIGNWARE_I2C_9152C000_LABEL
#define CONFIG_I2C_4_BASE_ADDR			DT_SNPS_DESIGNWARE_I2C_9152C000_BASE_ADDRESS
#define CONFIG_I2C_4_IRQ			DT_SNPS_DESIGNWARE_I2C_9152C000_IRQ_0
#define CONFIG_I2C_4_IRQ_PRI			DT_SNPS_DESIGNWARE_I2C_9152C000_IRQ_0_PRIORITY
#define CONFIG_I2C_4_IRQ_FLAGS			DT_SNPS_DESIGNWARE_I2C_9152C000_IRQ_0_SENSE
#define CONFIG_I2C_4_BITRATE			DT_SNPS_DESIGNWARE_I2C_9152C000_CLOCK_FREQUENCY

#define CONFIG_I2C_5_NAME			DT_SNPS_DESIGNWARE_I2C_9152A000_LABEL
#define CONFIG_I2C_5_BASE_ADDR			DT_SNPS_DESIGNWARE_I2C_9152A000_BASE_ADDRESS
#define CONFIG_I2C_5_IRQ			DT_SNPS_DESIGNWARE_I2C_9152A000_IRQ_0
#define CONFIG_I2C_5_IRQ_PRI			DT_SNPS_DESIGNWARE_I2C_9152A000_IRQ_0_PRIORITY
#define CONFIG_I2C_5_IRQ_FLAGS			DT_SNPS_DESIGNWARE_I2C_9152A000_IRQ_0_SENSE
#define CONFIG_I2C_5_BITRATE			DT_SNPS_DESIGNWARE_I2C_9152A000_CLOCK_FREQUENCY

#define CONFIG_I2C_6_NAME			DT_SNPS_DESIGNWARE_I2C_91528000_LABEL
#define CONFIG_I2C_6_BASE_ADDR			DT_SNPS_DESIGNWARE_I2C_91528000_BASE_ADDRESS
#define CONFIG_I2C_6_IRQ			DT_SNPS_DESIGNWARE_I2C_91528000_IRQ_0
#define CONFIG_I2C_6_IRQ_PRI			DT_SNPS_DESIGNWARE_I2C_91528000_IRQ_0_PRIORITY
#define CONFIG_I2C_6_IRQ_FLAGS			DT_SNPS_DESIGNWARE_I2C_91528000_IRQ_0_SENSE
#define CONFIG_I2C_6_BITRATE			DT_SNPS_DESIGNWARE_I2C_91528000_CLOCK_FREQUENCY

#define CONFIG_I2C_7_NAME			DT_SNPS_DESIGNWARE_I2C_91526000_LABEL
#define CONFIG_I2C_7_BASE_ADDR			DT_SNPS_DESIGNWARE_I2C_91526000_BASE_ADDRESS
#define CONFIG_I2C_7_IRQ			DT_SNPS_DESIGNWARE_I2C_91526000_IRQ_0
#define CONFIG_I2C_7_IRQ_PRI			DT_SNPS_DESIGNWARE_I2C_91526000_IRQ_0_PRIORITY
#define CONFIG_I2C_7_IRQ_FLAGS			DT_SNPS_DESIGNWARE_I2C_91526000_IRQ_0_SENSE
#define CONFIG_I2C_7_BITRATE			DT_SNPS_DESIGNWARE_I2C_91526000_CLOCK_FREQUENCY

/* End of Board Level DTS fixup file */
