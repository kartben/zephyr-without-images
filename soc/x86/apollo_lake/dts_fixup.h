/*
 * Copyright (c) 2018-2019 Intel Corporation Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* SoC level DTS fixup file */

#define DT_PHYS_RAM_ADDR	CONFIG_SRAM_BASE_ADDRESS
#define DT_PHYS_LOAD_ADDR	CONFIG_FLASH_BASE_ADDRESS
#define DT_RAM_SIZE		CONFIG_SRAM_SIZE
#define DT_ROM_SIZE		CONFIG_FLASH_SIZE

#define DT_IOAPIC_BASE_ADDRESS       DT_INTEL_IOAPIC_FEC00000_BASE_ADDRESS
#define DT_APL_GPIO_BASE_ADDRESS_N   DT_INTEL_APL_GPIO_D0C50000_BASE_ADDRESS_0
#define DT_APL_GPIO_BASE_ADDRESS_NW  DT_INTEL_APL_GPIO_D0C50000_BASE_ADDRESS_1
#define DT_APL_GPIO_BASE_ADDRESS_W   DT_INTEL_APL_GPIO_D0C50000_BASE_ADDRESS_2
#define DT_APL_GPIO_BASE_ADDRESS_SW  DT_INTEL_APL_GPIO_D0C50000_BASE_ADDRESS_3

#define DT_APL_GPIO_IRQ		  DT_INTEL_APL_GPIO_D0C50000_IRQ_0
#define DT_APL_GPIO_IRQ_PRIORITY  DT_INTEL_APL_GPIO_D0C50000_IRQ_0_PRIORITY
#define DT_APL_GPIO_IRQ_SENSE	  DT_INTEL_APL_GPIO_D0C50000_IRQ_0_SENSE

#define DT_APL_GPIO_MEM_SIZE_N	  DT_INTEL_APL_GPIO_D0C50000_SIZE_0
#define DT_APL_GPIO_MEM_SIZE_NW	  DT_INTEL_APL_GPIO_D0C50000_SIZE_1
#define DT_APL_GPIO_MEM_SIZE_W	  DT_INTEL_APL_GPIO_D0C50000_SIZE_2
#define DT_APL_GPIO_MEM_SIZE_SW   DT_INTEL_APL_GPIO_D0C50000_SIZE_3

#define DT_APL_GPIO_LABEL_N_0	  DT_INTEL_APL_GPIO_D0C50000_LABEL "_N_0"
#define DT_APL_GPIO_LABEL_N_1	  DT_INTEL_APL_GPIO_D0C50000_LABEL "_N_1"
#define DT_APL_GPIO_LABEL_N_2	  DT_INTEL_APL_GPIO_D0C50000_LABEL "_N_2"
#define DT_APL_GPIO_LABEL_NW_0	  DT_INTEL_APL_GPIO_D0C50000_LABEL "_NW_0"
#define DT_APL_GPIO_LABEL_NW_1	  DT_INTEL_APL_GPIO_D0C50000_LABEL "_NW_1"
#define DT_APL_GPIO_LABEL_NW_2	  DT_INTEL_APL_GPIO_D0C50000_LABEL "_NW_2"
#define DT_APL_GPIO_LABEL_W_0	  DT_INTEL_APL_GPIO_D0C50000_LABEL "_W_0"
#define DT_APL_GPIO_LABEL_W_1	  DT_INTEL_APL_GPIO_D0C50000_LABEL "_W_1"
#define DT_APL_GPIO_LABEL_SW_0	  DT_INTEL_APL_GPIO_D0C50000_LABEL "_SW_0"
#define DT_APL_GPIO_LABEL_SW_1 	  DT_INTEL_APL_GPIO_D0C50000_LABEL "_SW_1"

#define DT_UART_NS16550_PORT_0_BASE_ADDR DT_INST_0_NS16550_BASE_ADDRESS
#define DT_UART_NS16550_PORT_0_SIZE	 DT_INST_0_NS16550_SIZE
#define DT_UART_NS16550_PORT_0_BAUD_RATE DT_INST_0_NS16550_CURRENT_SPEED
#define DT_UART_NS16550_PORT_0_NAME	 DT_INST_0_NS16550_LABEL
#define DT_UART_NS16550_PORT_0_IRQ	 DT_INST_0_NS16550_IRQ_0
#define DT_UART_NS16550_PORT_0_IRQ_PRI	 DT_INST_0_NS16550_IRQ_0_PRIORITY
#define DT_UART_NS16550_PORT_0_IRQ_FLAGS DT_INST_0_NS16550_IRQ_0_SENSE
#define DT_UART_NS16550_PORT_0_CLK_FREQ	 DT_INST_0_NS16550_CLOCK_FREQUENCY
#define DT_UART_NS16550_PORT_0_PCIE	 DT_INST_0_NS16550_PCIE

#ifdef DT_NS16550_0_PCP
#define DT_UART_NS16550_PORT_0_PCP	 DT_NS16550_0_PCP
#endif

#define DT_UART_NS16550_PORT_1_BASE_ADDR DT_INST_1_NS16550_BASE_ADDRESS
#define DT_UART_NS16550_PORT_1_SIZE	 DT_INST_1_NS16550_SIZE
#define DT_UART_NS16550_PORT_1_BAUD_RATE DT_INST_1_NS16550_CURRENT_SPEED
#define DT_UART_NS16550_PORT_1_NAME	 DT_INST_1_NS16550_LABEL
#define DT_UART_NS16550_PORT_1_IRQ	 DT_INST_1_NS16550_IRQ_0
#define DT_UART_NS16550_PORT_1_IRQ_PRI	 DT_INST_1_NS16550_IRQ_0_PRIORITY
#define DT_UART_NS16550_PORT_1_IRQ_FLAGS DT_INST_1_NS16550_IRQ_0_SENSE
#define DT_UART_NS16550_PORT_1_CLK_FREQ	 DT_INST_1_NS16550_CLOCK_FREQUENCY
#define DT_UART_NS16550_PORT_1_PCIE	 DT_INST_1_NS16550_PCIE

#ifdef DT_NS16550_1_PCP
#define DT_UART_NS16550_PORT_1_PCP	 DT_NS16550_1_PCP
#endif

#define DT_UART_NS16550_PORT_2_BASE_ADDR DT_INST_2_NS16550_BASE_ADDRESS
#define DT_UART_NS16550_PORT_2_SIZE	 DT_INST_2_NS16550_SIZE
#define DT_UART_NS16550_PORT_2_BAUD_RATE DT_INST_2_NS16550_CURRENT_SPEED
#define DT_UART_NS16550_PORT_2_NAME	 DT_INST_2_NS16550_LABEL
#define DT_UART_NS16550_PORT_2_IRQ	 DT_INST_2_NS16550_IRQ_0
#define DT_UART_NS16550_PORT_2_IRQ_PRI	 DT_INST_2_NS16550_IRQ_0_PRIORITY
#define DT_UART_NS16550_PORT_2_IRQ_FLAGS DT_INST_2_NS16550_IRQ_0_SENSE
#define DT_UART_NS16550_PORT_2_CLK_FREQ	 DT_INST_2_NS16550_CLOCK_FREQUENCY
#define DT_UART_NS16550_PORT_2_PCIE	 DT_INST_2_NS16550_PCIE

#ifdef DT_NS16550_2_PCP
#define DT_UART_NS16550_PORT_2_PCP	 DT_NS16550_2_PCP
#endif

#define DT_UART_NS16550_PORT_3_BASE_ADDR DT_INST_3_NS16550_BASE_ADDRESS
#define DT_UART_NS16550_PORT_3_SIZE	 DT_INST_3_NS16550_SIZE
#define DT_UART_NS16550_PORT_3_BAUD_RATE DT_INST_3_NS16550_CURRENT_SPEED
#define DT_UART_NS16550_PORT_3_NAME	 DT_INST_3_NS16550_LABEL
#define DT_UART_NS16550_PORT_3_IRQ	 DT_INST_3_NS16550_IRQ_0
#define DT_UART_NS16550_PORT_3_IRQ_PRI	 DT_INST_3_NS16550_IRQ_0_PRIORITY
#define DT_UART_NS16550_PORT_3_IRQ_FLAGS DT_INST_3_NS16550_IRQ_0_SENSE
#define DT_UART_NS16550_PORT_3_CLK_FREQ	 DT_INST_3_NS16550_CLOCK_FREQUENCY
#define DT_UART_NS16550_PORT_3_PCIE	 DT_INST_3_NS16550_PCIE

#ifdef DT_NS16550_3_PCP
#define DT_UART_NS16550_PORT_3_PCP	 DT_NS16550_3_PCP
#endif

/* End of SoC Level DTS fixup file */
