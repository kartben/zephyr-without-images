/* SPDX-License-Identifier: Apache-2.0 */

/* SoC level DTS fixup file */
#define DT_NUM_IRQ_PRIO_BITS		DT_ARM_V6M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS
#define DT_UART_MCUX_LPSCI_0_NAME		DT_NXP_KINETIS_LPSCI_4006A000_LABEL
#define DT_UART_MCUX_LPSCI_0_CLOCK_NAME	DT_NXP_KINETIS_LPSCI_4006A000_CLOCK_CONTROLLER
#define DT_UART_MCUX_LPSCI_0_CLOCK_SUBSYS	DT_NXP_KINETIS_LPSCI_4006A000_CLOCK_NAME

#define DT_ADC_0_BASE_ADDRESS		DT_NXP_KINETIS_ADC16_4003B000_BASE_ADDRESS
#define DT_ADC_0_IRQ			DT_NXP_KINETIS_ADC16_4003B000_IRQ_0
#define DT_ADC_0_IRQ_PRI			DT_NXP_KINETIS_ADC16_4003B000_IRQ_0_PRIORITY
#define DT_ADC_0_NAME			DT_NXP_KINETIS_ADC16_4003B000_LABEL

#define DT_SIM_BASE_ADDRESS			DT_NXP_KINETIS_SIM_40047000_BASE_ADDRESS
#define DT_SIM_NAME				DT_NXP_KINETIS_SIM_40047000_LABEL

#define DT_I2C_0_NAME			DT_NXP_KINETIS_I2C_40066000_LABEL
#define DT_I2C_MCUX_0_BASE_ADDRESS		DT_NXP_KINETIS_I2C_40066000_BASE_ADDRESS
#define DT_I2C_MCUX_0_IRQ			DT_NXP_KINETIS_I2C_40066000_IRQ_0
#define DT_I2C_MCUX_0_IRQ_PRI		DT_NXP_KINETIS_I2C_40066000_IRQ_0_PRIORITY
#define DT_I2C_MCUX_0_BITRATE		DT_NXP_KINETIS_I2C_40066000_CLOCK_FREQUENCY

#define DT_I2C_1_NAME			DT_NXP_KINETIS_I2C_40067000_LABEL
#define DT_I2C_MCUX_1_BASE_ADDRESS		DT_NXP_KINETIS_I2C_40067000_BASE_ADDRESS
#define DT_I2C_MCUX_1_IRQ			DT_NXP_KINETIS_I2C_40067000_IRQ_0
#define DT_I2C_MCUX_1_IRQ_PRI		DT_NXP_KINETIS_I2C_40067000_IRQ_0_PRIORITY
#define DT_I2C_MCUX_1_BITRATE		DT_NXP_KINETIS_I2C_40067000_CLOCK_FREQUENCY

#define DT_FLASH_DEV_BASE_ADDRESS			DT_NXP_KINETIS_FTFA_40020000_BASE_ADDRESS
#define DT_FLASH_DEV_NAME				DT_NXP_KINETIS_FTFA_40020000_LABEL

#define DT_USBD_KINETIS_NAME		DT_NXP_KINETIS_USBD_40072000_LABEL
#define DT_USBD_KINETIS_IRQ			DT_NXP_KINETIS_USBD_40072000_IRQ_USB_OTG
#define DT_USBD_KINETIS_IRQ_PRI		DT_NXP_KINETIS_USBD_40072000_IRQ_USB_OTG_PRIORITY
#define DT_USBD_KINETIS_BASE_ADDRESS	DT_NXP_KINETIS_USBD_40072000_BASE_ADDRESS
#define DT_USBD_KINETIS_NUM_BIDIR_EP	DT_NXP_KINETIS_USBD_40072000_NUM_BIDIR_ENDPOINTS

/* End of SoC Level DTS fixup file */
