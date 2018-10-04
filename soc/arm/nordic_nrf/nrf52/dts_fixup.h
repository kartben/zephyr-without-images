/* SoC level DTS fixup file */

#define DT_NUM_IRQ_PRIO_BITS	DT_ARM_V7M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS

#define DT_ADC_0_NAME			DT_NORDIC_NRF_SAADC_ADC_0_LABEL

#define DT_UART_0_NAME			DT_NORDIC_NRF_UART_UART_0_LABEL
#define DT_UART_1_NAME			DT_NORDIC_NRF_UART_UART_1_LABEL

#define DT_FLASH_DEV_NAME			DT_NRF_NRF52_FLASH_CONTROLLER_4001E000_LABEL

#define DT_GPIO_P0_DEV_NAME		DT_NORDIC_NRF_GPIO_GPIO_0_LABEL
#define DT_GPIO_P1_DEV_NAME		DT_NORDIC_NRF_GPIO_GPIO_1_LABEL

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

#define DT_SPI_0_NAME			DT_NORDIC_NRF_SPI_SPI_0_LABEL
#define DT_SPI_1_NAME			DT_NORDIC_NRF_SPI_SPI_1_LABEL
#define DT_SPI_2_NAME			DT_NORDIC_NRF_SPI_SPI_2_LABEL
#define DT_SPI_3_NAME			DT_NORDIC_NRF_SPI_SPI_3_LABEL

#define DT_USBD_NRF_IRQ		DT_NORDIC_NRF_USBD_40027000_IRQ_USBD
#define DT_USBD_NRF_IRQ_PRI		DT_NORDIC_NRF_USBD_40027000_IRQ_USBD_PRIORITY
#define DT_USBD_NRF_NUM_BIDIR_EP	DT_NORDIC_NRF_USBD_40027000_NUM_BIDIR_ENDPOINTS
#define DT_USBD_NRF_NUM_IN_EP	DT_NORDIC_NRF_USBD_40027000_NUM_IN_ENDPOINTS
#define DT_USBD_NRF_NUM_OUT_EP	DT_NORDIC_NRF_USBD_40027000_NUM_OUT_ENDPOINTS
#define DT_USBD_NRF_NUM_ISOIN_EP	DT_NORDIC_NRF_USBD_40027000_NUM_ISOIN_ENDPOINTS
#define DT_USBD_NRF_NUM_ISOOUT_EP	DT_NORDIC_NRF_USBD_40027000_NUM_ISOOUT_ENDPOINTS
#define DT_USBD_NRF_NAME		DT_NORDIC_NRF_USBD_40027000_LABEL

#define DT_WDT_0_NAME			DT_NORDIC_NRF_WATCHDOG_WDT_0_LABEL

#if defined(DT_NORDIC_NRF_CC310_5002A000_BASE_ADDRESS)
#define DT_CC310_CTL_BASE_ADDR	DT_NORDIC_NRF_CC310_5002A000_BASE_ADDRESS
#define DT_CC310_CTL_NAME		DT_NORDIC_NRF_CC310_5002A000_LABEL
#define DT_CC310_BASE_ADDR		DT_ARM_CRYPTOCELL_310_5002B000_BASE_ADDRESS
#define DT_CC310_NAME		DT_ARM_CRYPTOCELL_310_5002B000_LABEL
#define DT_CC310_IRQ		DT_ARM_CRYPTOCELL_310_5002B000_IRQ_0
#define DT_CC310_IRQ_PRI		DT_ARM_CRYPTOCELL_310_5002B000_IRQ_0_PRIORITY
#endif

/* End of SoC Level DTS fixup file */
