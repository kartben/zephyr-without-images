/* SPDX-License-Identifier: Apache-2.0 */

/* SoC level DTS fixup file */

#define DT_UART_QMSI_0_CLOCK_FREQUENCY	DT_INTEL_QMSI_UART_B0002000_CLOCKS_CLOCK_FREQUENCY
#define DT_UART_QMSI_0_BAUDRATE		DT_INTEL_QMSI_UART_B0002000_CURRENT_SPEED
#define DT_UART_QMSI_0_NAME		DT_INTEL_QMSI_UART_B0002000_LABEL
#define DT_UART_QMSI_0_IRQ		DT_INTEL_QMSI_UART_B0002000_IRQ_0
#define DT_UART_QMSI_0_IRQ_PRI	DT_INTEL_QMSI_UART_B0002000_IRQ_0_PRIORITY

#define DT_UART_QMSI_1_CLOCK_FREQUENCY	DT_INTEL_QMSI_UART_B0002400_CLOCKS_CLOCK_FREQUENCY
#define DT_UART_QMSI_1_BAUDRATE		DT_INTEL_QMSI_UART_B0002400_CURRENT_SPEED
#define DT_UART_QMSI_1_NAME		DT_INTEL_QMSI_UART_B0002400_LABEL
#define DT_UART_QMSI_1_IRQ		DT_INTEL_QMSI_UART_B0002400_IRQ_0
#define DT_UART_QMSI_1_IRQ_PRI	DT_INTEL_QMSI_UART_B0002400_IRQ_0_PRIORITY

#define SRAM_START			CONFIG_SRAM_BASE_ADDRESS
#define SRAM_SIZE			CONFIG_SRAM_SIZE

#define FLASH_START			CONFIG_FLASH_BASE_ADDRESS
#define FLASH_SIZE      		CONFIG_FLASH_SIZE

#define DT_DCCM_BASE_ADDRESS       DT_ARC_DCCM_80000000_BASE_ADDRESS
#define DT_DCCM_SIZE               (DT_ARC_DCCM_80000000_SIZE >> 10)

#define DT_I2C_SS_0_NAME		DT_INTEL_QMSI_SS_I2C_80012000_LABEL
#define DT_I2C_SS_0_ERR_IRQ		DT_INTEL_QMSI_SS_I2C_80012000_IRQ_ERROR
#define DT_I2C_SS_0_ERR_IRQ_PRI	DT_INTEL_QMSI_SS_I2C_80012000_IRQ_ERROR_PRIORITY
#define DT_I2C_SS_0_RX_IRQ		DT_INTEL_QMSI_SS_I2C_80012000_IRQ_RX
#define DT_I2C_SS_0_RX_IRQ_PRI	DT_INTEL_QMSI_SS_I2C_80012000_IRQ_RX_PRIORITY
#define DT_I2C_SS_0_TX_IRQ		DT_INTEL_QMSI_SS_I2C_80012000_IRQ_TX
#define DT_I2C_SS_0_TX_IRQ_PRI	DT_INTEL_QMSI_SS_I2C_80012000_IRQ_TX_PRIORITY
#define DT_I2C_SS_0_STOP_IRQ	DT_INTEL_QMSI_SS_I2C_80012000_IRQ_STOP
#define DT_I2C_SS_0_STOP_IRQ_PRI	DT_INTEL_QMSI_SS_I2C_80012000_IRQ_STOP_PRIORITY
#define DT_I2C_SS_0_BITRATE		DT_INTEL_QMSI_SS_I2C_80012000_CLOCK_FREQUENCY
#define DT_I2C_SS_1_NAME		DT_INTEL_QMSI_SS_I2C_80012100_LABEL
#define DT_I2C_SS_1_ERR_IRQ		DT_INTEL_QMSI_SS_I2C_80012100_IRQ_ERROR
#define DT_I2C_SS_1_ERR_IRQ_PRI	DT_INTEL_QMSI_SS_I2C_80012100_IRQ_ERROR_PRIORITY
#define DT_I2C_SS_1_RX_IRQ		DT_INTEL_QMSI_SS_I2C_80012100_IRQ_RX
#define DT_I2C_SS_1_RX_IRQ_PRI	DT_INTEL_QMSI_SS_I2C_80012100_IRQ_RX_PRIORITY
#define DT_I2C_SS_1_TX_IRQ		DT_INTEL_QMSI_SS_I2C_80012100_IRQ_TX
#define DT_I2C_SS_1_TX_IRQ_PRI	DT_INTEL_QMSI_SS_I2C_80012100_IRQ_TX_PRIORITY
#define DT_I2C_SS_1_STOP_IRQ	DT_INTEL_QMSI_SS_I2C_80012100_IRQ_STOP
#define DT_I2C_SS_1_STOP_IRQ_PRI	DT_INTEL_QMSI_SS_I2C_80012100_IRQ_STOP_PRIORITY
#define DT_I2C_SS_1_BITRATE		DT_INTEL_QMSI_SS_I2C_80012100_CLOCK_FREQUENCY

#define CONFIG_I2C_0_NAME		DT_INTEL_QMSI_I2C_B0002800_LABEL
#define DT_I2C_0_BITRATE		DT_INTEL_QMSI_I2C_B0002800_CLOCK_FREQUENCY
#define DT_I2C_0_IRQ		DT_INTEL_QMSI_I2C_B0002800_IRQ_0
#define DT_I2C_0_IRQ_PRI		DT_INTEL_QMSI_I2C_B0002800_IRQ_0_PRIORITY
#define CONFIG_I2C_1_NAME		DT_INTEL_QMSI_I2C_B0002C00_LABEL
#define DT_I2C_1_BITRATE		DT_INTEL_QMSI_I2C_B0002C00_CLOCK_FREQUENCY
#define DT_I2C_1_IRQ		DT_INTEL_QMSI_I2C_B0002C00_IRQ_0
#define DT_I2C_1_IRQ_PRI		DT_INTEL_QMSI_I2C_B0002C00_IRQ_0_PRIORITY

#define DT_RTC_0_NAME		DT_INTEL_QMSI_RTC_B0000400_LABEL
#define DT_RTC_0_IRQ		DT_INTEL_QMSI_RTC_B0000400_IRQ_0
#define DT_RTC_0_IRQ_PRI		DT_INTEL_QMSI_RTC_B0000400_IRQ_0_PRIORITY

#define DT_GPIO_QMSI_SS_0_NAME	DT_INTEL_QMSI_SS_GPIO_80017800_LABEL
#define DT_GPIO_QMSI_SS_0_IRQ	DT_INTEL_QMSI_SS_GPIO_80017800_IRQ_0
#define DT_GPIO_QMSI_SS_0_IRQ_PRI	DT_INTEL_QMSI_SS_GPIO_80017800_IRQ_0_PRIORITY

#define DT_GPIO_QMSI_SS_1_NAME	DT_INTEL_QMSI_SS_GPIO_80017900_LABEL
#define DT_GPIO_QMSI_SS_1_IRQ	DT_INTEL_QMSI_SS_GPIO_80017900_IRQ_0
#define DT_GPIO_QMSI_SS_1_IRQ_PRI	DT_INTEL_QMSI_SS_GPIO_80017900_IRQ_0_PRIORITY

#define DT_GPIO_QMSI_0_NAME		DT_INTEL_QMSI_GPIO_B0000C00_LABEL
#define DT_GPIO_QMSI_0_IRQ		DT_INTEL_QMSI_GPIO_B0000C00_IRQ_0
#define DT_GPIO_QMSI_0_IRQ_PRI	DT_INTEL_QMSI_GPIO_B0000C00_IRQ_0_PRIORITY
#define DT_GPIO_QMSI_1_NAME		DT_INTEL_QMSI_GPIO_B0800B00_LABEL
#define DT_GPIO_QMSI_1_IRQ		DT_INTEL_QMSI_GPIO_B0800B00_IRQ_0
#define DT_GPIO_QMSI_1_IRQ_PRI	DT_INTEL_QMSI_GPIO_B0800B00_IRQ_0_PRIORITY

#define DT_ADC_0_IRQ		DT_SNPS_DW_ADC_80015000_IRQ_NORMAL
#define DT_ADC_IRQ_ERR		DT_SNPS_DW_ADC_80015000_IRQ_ERROR
#define DT_ADC_0_IRQ_PRI		DT_SNPS_DW_ADC_80015000_IRQ_0_PRIORITY
#define DT_ADC_0_NAME		DT_SNPS_DW_ADC_80015000_LABEL
#define DT_ADC_0_BASE_ADDRESS	DT_SNPS_DW_ADC_80015000_BASE_ADDRESS

#define DT_SPI_0_BASE_ADDRESS	DT_SNPS_DESIGNWARE_SPI_80010000_BASE_ADDRESS
#define DT_SPI_0_CLOCK_FREQUENCY DT_SNPS_DESIGNWARE_SPI_80010000_CLOCKS_CLOCK_FREQUENCY
#define DT_SPI_0_NAME		DT_SNPS_DESIGNWARE_SPI_80010000_LABEL
#define DT_SPI_0_IRQ_ERR_INT	DT_SNPS_DESIGNWARE_SPI_80010000_IRQ_ERR_INT
#define DT_SPI_0_IRQ_ERR_INT_PRI	DT_SNPS_DESIGNWARE_SPI_80010000_IRQ_ERR_INT_PRIORITY
#define DT_SPI_0_IRQ_RX_AVAIL	DT_SNPS_DESIGNWARE_SPI_80010000_IRQ_RX_AVAIL
#define DT_SPI_0_IRQ_RX_AVAIL_PRI	DT_SNPS_DESIGNWARE_SPI_80010000_IRQ_RX_AVAIL_PRIORITY
#define DT_SPI_0_IRQ_TX_REQ		DT_SNPS_DESIGNWARE_SPI_80010000_IRQ_TX_REQ
#define DT_SPI_0_IRQ_TX_REQ_PRI	DT_SNPS_DESIGNWARE_SPI_80010000_IRQ_TX_REQ_PRIORITY

#define DT_SPI_1_BASE_ADDRESS	DT_SNPS_DESIGNWARE_SPI_80010100_BASE_ADDRESS
#define DT_SPI_1_CLOCK_FREQUENCY DT_SNPS_DESIGNWARE_SPI_80010100_CLOCKS_CLOCK_FREQUENCY
#define DT_SPI_1_NAME		DT_SNPS_DESIGNWARE_SPI_80010100_LABEL
#define DT_SPI_1_IRQ_ERR_INT	DT_SNPS_DESIGNWARE_SPI_80010100_IRQ_ERR_INT
#define DT_SPI_1_IRQ_ERR_INT_PRI	DT_SNPS_DESIGNWARE_SPI_80010100_IRQ_ERR_INT_PRIORITY
#define DT_SPI_1_IRQ_RX_AVAIL	DT_SNPS_DESIGNWARE_SPI_80010100_IRQ_RX_AVAIL
#define DT_SPI_1_IRQ_RX_AVAIL_PRI	DT_SNPS_DESIGNWARE_SPI_80010100_IRQ_RX_AVAIL_PRIORITY
#define DT_SPI_1_IRQ_TX_REQ		DT_SNPS_DESIGNWARE_SPI_80010100_IRQ_TX_REQ
#define DT_SPI_1_IRQ_TX_REQ_PRI	DT_SNPS_DESIGNWARE_SPI_80010100_IRQ_TX_REQ_PRIORITY

#define CONFIG_WDT_0_NAME		DT_INTEL_QMSI_WATCHDOG_B0000000_LABEL
#define DT_WDT_0_IRQ		DT_INTEL_QMSI_WATCHDOG_B0000000_IRQ_0
#define DT_WDT_0_IRQ_PRI		DT_INTEL_QMSI_WATCHDOG_B0000000_IRQ_0_PRIORITY
#define DT_WDT_0_IRQ_FLAGS		0
/* End of SoC Level DTS fixup file */
