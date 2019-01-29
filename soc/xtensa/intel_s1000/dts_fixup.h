/* SoC level DTS fixup file */

#define DT_UART_NS16550_PORT_0_BASE_ADDR	DT_NS16550_80800_BASE_ADDRESS
#define CONFIG_UART_NS16550_PORT_0_BAUD_RATE	DT_NS16550_80800_CURRENT_SPEED
#define CONFIG_UART_NS16550_PORT_0_NAME		DT_NS16550_80800_LABEL
#define DT_UART_NS16550_PORT_0_IRQ		DT_NS16550_80800_IRQ_0
#define CONFIG_UART_NS16550_PORT_0_IRQ_PRI	DT_NS16550_80800_IRQ_0_PRIORITY
#define DT_UART_NS16550_PORT_0_IRQ_FLAGS	DT_NS16550_80800_IRQ_0_SENSE
#define DT_UART_NS16550_PORT_0_CLK_FREQ	DT_NS16550_80800_CLOCK_FREQUENCY

#define DT_L2_SRAM_BASE				CONFIG_SRAM_BASE_ADDRESS
#define DT_L2_SRAM_SIZE				CONFIG_SRAM_SIZE * 1024

#define DT_CAVS_ICTL_BASE_ADDR			DT_INTEL_CAVS_INTC_78800_BASE_ADDRESS
#define DT_CAVS_ICTL_0_IRQ				DT_INTEL_CAVS_INTC_78800_IRQ_0
#define DT_CAVS_ICTL_0_IRQ_PRI		DT_INTEL_CAVS_INTC_78800_IRQ_0_PRIORITY
#define DT_CAVS_ICTL_0_IRQ_FLAGS			DT_INTEL_CAVS_INTC_78800_IRQ_0_SENSE

#define DT_CAVS_ICTL_1_IRQ				DT_INTEL_CAVS_INTC_78810_IRQ_0
#define DT_CAVS_ICTL_1_IRQ_PRI		DT_INTEL_CAVS_INTC_78810_IRQ_0_PRIORITY
#define DT_CAVS_ICTL_1_IRQ_FLAGS			DT_INTEL_CAVS_INTC_78810_IRQ_0_SENSE

#define DT_CAVS_ICTL_2_IRQ				DT_INTEL_CAVS_INTC_78820_IRQ_0
#define DT_CAVS_ICTL_2_IRQ_PRI		DT_INTEL_CAVS_INTC_78820_IRQ_0_PRIORITY
#define DT_CAVS_ICTL_2_IRQ_FLAGS			DT_INTEL_CAVS_INTC_78820_IRQ_0_SENSE

#define DT_CAVS_ICTL_3_IRQ				DT_INTEL_CAVS_INTC_78830_IRQ_0
#define DT_CAVS_ICTL_3_IRQ_PRI		DT_INTEL_CAVS_INTC_78830_IRQ_0_PRIORITY
#define DT_CAVS_ICTL_3_IRQ_FLAGS			DT_INTEL_CAVS_INTC_78830_IRQ_0_SENSE

#define DT_DW_ICTL_BASE_ADDR			DT_SNPS_DESIGNWARE_INTC_81800_BASE_ADDRESS
#define DT_DW_ICTL_IRQ				((DT_SNPS_DESIGNWARE_INTC_81800_IRQ_0 << 8) | \
						 (DT_INTEL_CAVS_INTC_78800_IRQ_0 << 0))
#define DT_DW_ICTL_IRQ_PRI			DT_SNPS_DESIGNWARE_INTC_81800_IRQ_0_PRIORITY
#define DT_DW_ICTL_IRQ_FLAGS			DT_SNPS_DESIGNWARE_INTC_81800_IRQ_0_SENSE

#define DT_I2C_0_BASE_ADDR			DT_SNPS_DESIGNWARE_I2C_80400_BASE_ADDRESS
#define DT_I2C_0_BITRATE			DT_SNPS_DESIGNWARE_I2C_80400_CLOCK_FREQUENCY
#define CONFIG_I2C_0_NAME			DT_SNPS_DESIGNWARE_I2C_80400_LABEL
#define DT_I2C_0_IRQ				DT_SNPS_DESIGNWARE_I2C_80400_IRQ_0
#define DT_I2C_0_IRQ_FLAGS			DT_SNPS_DESIGNWARE_I2C_80400_IRQ_0_SENSE
#define DT_I2C_0_IRQ_PRI			DT_SNPS_DESIGNWARE_I2C_80400_IRQ_0_PRIORITY

#define DT_SPI_0_BASE_ADDRESS			DT_SNPS_DESIGNWARE_SPI_E000_BASE_ADDRESS
#define DT_SPI_0_NAME			DT_SNPS_DESIGNWARE_SPI_E000_LABEL
#define DT_SPI_0_IRQ				DT_SNPS_DESIGNWARE_SPI_E000_IRQ_0
#define DT_SPI_DW_IRQ_FLAGS			DT_SNPS_DESIGNWARE_SPI_E000_IRQ_0_SENSE

#define DT_SPI_0_IRQ_PRI			DT_SNPS_DESIGNWARE_SPI_E000_IRQ_0_PRIORITY

#define DT_GPIO_DW_0_BASE_ADDR		\
	DT_SNPS_DESIGNWARE_GPIO_80C00_BASE_ADDRESS
#define DT_GPIO_DW_0_BITS		\
	DT_SNPS_DESIGNWARE_GPIO_80C00_BITS
#define DT_GPIO_INTC_IRQ		\
	(DT_SNPS_DESIGNWARE_GPIO_80C00_IRQ_0 << INTR_CNTL_IRQ_NUM_SHIFT)
#define DT_GPIO_CAVS_IRQ		\
	(DT_SNPS_DESIGNWARE_INTC_81800_IRQ_0 << CAVS_IRQ_NUM_SHIFT)
#define DT_GPIO_XTENSA_IRQ		\
	(DT_INTEL_CAVS_INTC_78800_IRQ_0 << XTENSA_IRQ_NUM_SHIFT)
#define DT_GPIO_DW_0_IRQ		\
	(DT_GPIO_INTC_IRQ | DT_GPIO_CAVS_IRQ | DT_GPIO_XTENSA_IRQ)
#define CONFIG_GPIO_DW_0_IRQ_PRI	\
	DT_SNPS_DESIGNWARE_GPIO_80C00_IRQ_0_PRIORITY
#define DT_GPIO_DW_0_IRQ_FLAGS		0
#define CONFIG_GPIO_DW_0_NAME		\
	DT_SNPS_DESIGNWARE_GPIO_80C00_LABEL

#define DT_PINMUX_BASE_ADDR		\
	DT_INTEL_S1000_PINMUX_81C30_BASE_ADDRESS
#define DT_PINMUX_CTRL_REG_COUNT	\
	(DT_INTEL_S1000_PINMUX_81C30_SIZE / 4)

/* End of SoC Level DTS fixup file */
