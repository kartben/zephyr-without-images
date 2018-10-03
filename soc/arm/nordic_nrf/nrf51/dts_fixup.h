/* SoC level DTS fixup file */

#define DT_NUM_IRQ_PRIO_BITS	DT_ARM_V6M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS

#define DT_ADC_0_IRQ		DT_NORDIC_NRF_ADC_40007000_IRQ_0
#define CONFIG_ADC_0_IRQ_PRI		DT_NORDIC_NRF_ADC_40007000_IRQ_0_PRIORITY
#define CONFIG_ADC_0_NAME		DT_NORDIC_NRF_ADC_40007000_LABEL

#define DT_UART_0_BASE		DT_NORDIC_NRF_UART_40002000_BASE_ADDRESS
#define DT_UART_0_IRQ_PRI		DT_NORDIC_NRF_UART_40002000_IRQ_0_PRIORITY
#define DT_UART_0_IRQ_NUM		DT_NORDIC_NRF_UART_40002000_IRQ_0
#define DT_UART_0_BAUD_RATE		DT_NORDIC_NRF_UART_40002000_CURRENT_SPEED
#define DT_UART_0_NAME		DT_NORDIC_NRF_UART_40002000_LABEL
#define DT_UART_0_TX_PIN		DT_NORDIC_NRF_UART_40002000_TX_PIN
#define DT_UART_0_RX_PIN		DT_NORDIC_NRF_UART_40002000_RX_PIN
#if defined(DT_NORDIC_NRF_UART_40002000_RTS_PIN)
#define DT_UART_0_RTS_PIN		DT_NORDIC_NRF_UART_40002000_RTS_PIN
#endif
#if defined(DT_NORDIC_NRF_UART_40002000_CTS_PIN)
#define DT_UART_0_CTS_PIN		DT_NORDIC_NRF_UART_40002000_CTS_PIN
#endif

#define DT_FLASH_DEV_NAME			DT_NRF_NRF51_FLASH_CONTROLLER_4001E000_LABEL

#define DT_GPIO_P0_DEV_NAME		DT_NORDIC_NRF_GPIO_50000000_LABEL
#define DT_GPIOTE_IRQ_PRI		DT_NORDIC_NRF_GPIOTE_40006000_IRQ_0_PRIORITY
#define DT_GPIOTE_IRQ		DT_NORDIC_NRF_GPIOTE_40006000_IRQ_0

#define DT_I2C_0_NAME			DT_NORDIC_NRF_I2C_I2C_0_LABEL
#define DT_I2C_1_NAME			DT_NORDIC_NRF_I2C_I2C_1_LABEL

#define DT_QDEC_BASE_ADDR		DT_NORDIC_NRF_QDEC_40012000_BASE_ADDRESS
#define DT_QDEC_NAME		DT_NORDIC_NRF_QDEC_40012000_LABEL
#define DT_QDEC_IRQ_PRI		DT_NORDIC_NRF_QDEC_40012000_IRQ_0_PRIORITY
#define DT_QDEC_IRQ			DT_NORDIC_NRF_QDEC_40012000_IRQ_0
#define DT_QDEC_A_PIN		DT_NORDIC_NRF_QDEC_40012000_A_PIN
#define DT_QDEC_B_PIN		DT_NORDIC_NRF_QDEC_40012000_B_PIN
#if defined(DT_NORDIC_NRF_QDEC_40012000_LED_PIN)
#define DT_QDEC_LED_PIN		DT_NORDIC_NRF_QDEC_40012000_LED_PIN
#endif
#if defined(DT_NORDIC_NRF_QDEC_40012000_ENABLE_PIN)
#define DT_QDEC_ENABLE_PIN		DT_NORDIC_NRF_QDEC_40012000_ENABLE_PIN
#endif
#define DT_QDEC_LED_PRE		DT_NORDIC_NRF_QDEC_40012000_LED_PRE
#define DT_QDEC_STEPS		DT_NORDIC_NRF_QDEC_40012000_STEPS

#define DT_SPI_0_BASE_ADDRESS       DT_NORDIC_NRF_SPI_40003000_BASE_ADDRESS
#define DT_SPI_0_NAME               DT_NORDIC_NRF_SPI_40003000_LABEL
#define CONFIG_SPI_0_IRQ_PRI            DT_NORDIC_NRF_SPI_40003000_IRQ_0_PRIORITY
#define DT_SPI_0_IRQ                DT_NORDIC_NRF_SPI_40003000_IRQ_0
#define DT_SPI_0_NRF_SCK_PIN	DT_NORDIC_NRF_SPI_40003000_SCK_PIN
#define DT_SPI_0_NRF_MOSI_PIN	DT_NORDIC_NRF_SPI_40003000_MOSI_PIN
#define DT_SPI_0_NRF_MISO_PIN	DT_NORDIC_NRF_SPI_40003000_MISO_PIN
#define DT_SPI_0_NRF_CSN_PIN	DT_NORDIC_NRF_SPI_40003000_CSN_PIN

#define DT_SPI_1_BASE_ADDRESS       DT_NORDIC_NRF_SPI_40004000_BASE_ADDRESS
#define DT_SPI_1_NAME               DT_NORDIC_NRF_SPI_40004000_LABEL
#define CONFIG_SPI_1_IRQ_PRI            DT_NORDIC_NRF_SPI_40004000_IRQ_0_PRIORITY
#define DT_SPI_1_IRQ                DT_NORDIC_NRF_SPI_40004000_IRQ_0
#define DT_SPI_1_NRF_SCK_PIN	DT_NORDIC_NRF_SPI_40004000_SCK_PIN
#define DT_SPI_1_NRF_MOSI_PIN	DT_NORDIC_NRF_SPI_40004000_MOSI_PIN
#define DT_SPI_1_NRF_MISO_PIN	DT_NORDIC_NRF_SPI_40004000_MISO_PIN
#define DT_SPI_1_NRF_CSN_PIN	DT_NORDIC_NRF_SPI_40004000_CSN_PIN

#define CONFIG_WDT_0_NAME		DT_NORDIC_NRF_WATCHDOG_40010000_LABEL
#define DT_WDT_NRF_IRQ		DT_NORDIC_NRF_WATCHDOG_40010000_IRQ_WDT
#define DT_WDT_NRF_IRQ_PRI		DT_NORDIC_NRF_WATCHDOG_40010000_IRQ_WDT_PRIORITY

/* End of SoC Level DTS fixup file */
