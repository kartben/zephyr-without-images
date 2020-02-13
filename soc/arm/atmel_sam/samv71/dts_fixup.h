/*
 * Copyright (c) 2019 Gerson Fernando Budke
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* This file is a temporary workaround for mapping of the generated information
 * to the current driver definitions.  This will be removed when the drivers
 * are modified to handle the generated information, or the mapping of
 * generated data matches the driver definitions.
 */

/* SoC level DTS fixup file */

#define DT_NUM_IRQ_PRIO_BITS                 DT_ARM_V7M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS
#define DT_CPU_CLOCK_FREQUENCY               DT_ARM_CORTEX_M7_0_CLOCK_FREQUENCY

#define DT_NUM_MPU_REGIONS                   DT_ARM_ARMV7M_MPU_E000ED90_ARM_NUM_MPU_REGIONS

#define DT_GPIO_SAM_PORTA_LABEL              DT_ATMEL_SAM_GPIO_400E0E00_LABEL
#define DT_GPIO_SAM_PORTA_BASE_ADDRESS       DT_ATMEL_SAM_GPIO_400E0E00_BASE_ADDRESS
#define DT_GPIO_SAM_PORTA_IRQ                DT_ATMEL_SAM_GPIO_400E0E00_IRQ_0
#define DT_GPIO_SAM_PORTA_IRQ_PRIO           DT_ATMEL_SAM_GPIO_400E0E00_IRQ_0_PRIORITY
#define DT_GPIO_SAM_PORTA_PERIPHERAL_ID      DT_ATMEL_SAM_GPIO_400E0E00_PERIPHERAL_ID
#define DT_GPIO_SAM_PORTB_LABEL              DT_ATMEL_SAM_GPIO_400E1000_LABEL
#define DT_GPIO_SAM_PORTB_BASE_ADDRESS       DT_ATMEL_SAM_GPIO_400E1000_BASE_ADDRESS
#define DT_GPIO_SAM_PORTB_IRQ                DT_ATMEL_SAM_GPIO_400E1000_IRQ_0
#define DT_GPIO_SAM_PORTB_IRQ_PRIO           DT_ATMEL_SAM_GPIO_400E1000_IRQ_0_PRIORITY
#define DT_GPIO_SAM_PORTB_PERIPHERAL_ID      DT_ATMEL_SAM_GPIO_400E1000_PERIPHERAL_ID
#define DT_GPIO_SAM_PORTC_LABEL              DT_ATMEL_SAM_GPIO_400E1200_LABEL
#define DT_GPIO_SAM_PORTC_BASE_ADDRESS       DT_ATMEL_SAM_GPIO_400E1200_BASE_ADDRESS
#define DT_GPIO_SAM_PORTC_IRQ                DT_ATMEL_SAM_GPIO_400E1200_IRQ_0
#define DT_GPIO_SAM_PORTC_IRQ_PRIO           DT_ATMEL_SAM_GPIO_400E1200_IRQ_0_PRIORITY
#define DT_GPIO_SAM_PORTC_PERIPHERAL_ID      DT_ATMEL_SAM_GPIO_400E1200_PERIPHERAL_ID
#define DT_GPIO_SAM_PORTD_LABEL              DT_ATMEL_SAM_GPIO_400E1400_LABEL
#define DT_GPIO_SAM_PORTD_BASE_ADDRESS       DT_ATMEL_SAM_GPIO_400E1400_BASE_ADDRESS
#define DT_GPIO_SAM_PORTD_IRQ                DT_ATMEL_SAM_GPIO_400E1400_IRQ_0
#define DT_GPIO_SAM_PORTD_IRQ_PRIO           DT_ATMEL_SAM_GPIO_400E1400_IRQ_0_PRIORITY
#define DT_GPIO_SAM_PORTD_PERIPHERAL_ID      DT_ATMEL_SAM_GPIO_400E1400_PERIPHERAL_ID
#define DT_GPIO_SAM_PORTE_LABEL              DT_ATMEL_SAM_GPIO_400E1600_LABEL
#define DT_GPIO_SAM_PORTE_BASE_ADDRESS       DT_ATMEL_SAM_GPIO_400E1600_BASE_ADDRESS
#define DT_GPIO_SAM_PORTE_IRQ                DT_ATMEL_SAM_GPIO_400E1600_IRQ_0
#define DT_GPIO_SAM_PORTE_IRQ_PRIO           DT_ATMEL_SAM_GPIO_400E1600_IRQ_0_PRIORITY
#define DT_GPIO_SAM_PORTE_PERIPHERAL_ID      DT_ATMEL_SAM_GPIO_400E1600_PERIPHERAL_ID

#define DT_I2C_0_BASE_ADDRESS                DT_ATMEL_SAM_I2C_TWIHS_40018000_BASE_ADDRESS
#define DT_I2C_0_NAME                        DT_ATMEL_SAM_I2C_TWIHS_40018000_LABEL
#define DT_I2C_0_BITRATE                     DT_ATMEL_SAM_I2C_TWIHS_40018000_CLOCK_FREQUENCY
#define DT_I2C_0_IRQ                         DT_ATMEL_SAM_I2C_TWIHS_40018000_IRQ_0
#define DT_I2C_0_IRQ_PRI                     DT_ATMEL_SAM_I2C_TWIHS_40018000_IRQ_0_PRIORITY
#define DT_I2C_0_PERIPHERAL_ID               DT_ATMEL_SAM_I2C_TWIHS_40018000_PERIPHERAL_ID

#define DT_I2C_1_BASE_ADDRESS                DT_ATMEL_SAM_I2C_TWIHS_4001C000_BASE_ADDRESS
#define DT_I2C_1_NAME                        DT_ATMEL_SAM_I2C_TWIHS_4001C000_LABEL
#define DT_I2C_1_BITRATE                     DT_ATMEL_SAM_I2C_TWIHS_4001C000_CLOCK_FREQUENCY
#define DT_I2C_1_IRQ                         DT_ATMEL_SAM_I2C_TWIHS_4001C000_IRQ_0
#define DT_I2C_1_IRQ_PRI                     DT_ATMEL_SAM_I2C_TWIHS_4001C000_IRQ_0_PRIORITY
#define DT_I2C_1_PERIPHERAL_ID               DT_ATMEL_SAM_I2C_TWIHS_4001C000_PERIPHERAL_ID

#define DT_I2C_2_BASE_ADDRESS                DT_ATMEL_SAM_I2C_TWIHS_40060000_BASE_ADDRESS
#define DT_I2C_2_NAME                        DT_ATMEL_SAM_I2C_TWIHS_40060000_LABEL
#define DT_I2C_2_BITRATE                     DT_ATMEL_SAM_I2C_TWIHS_40060000_CLOCK_FREQUENCY
#define DT_I2C_2_IRQ                         DT_ATMEL_SAM_I2C_TWIHS_40060000_IRQ_0
#define DT_I2C_2_IRQ_PRI                     DT_ATMEL_SAM_I2C_TWIHS_40060000_IRQ_0_PRIORITY
#define DT_I2C_2_PERIPHERAL_ID               DT_ATMEL_SAM_I2C_TWIHS_40060000_PERIPHERAL_ID

#define DT_SPI_0_BASE_ADDRESS                DT_ATMEL_SAM_SPI_40008000_BASE_ADDRESS
#define DT_SPI_0_NAME                        DT_ATMEL_SAM_SPI_40008000_LABEL
#define DT_SPI_0_IRQ                         DT_ATMEL_SAM_SPI_40008000_IRQ_0
#define DT_SPI_0_IRQ_PRI                     DT_ATMEL_SAM_SPI_40008000_IRQ_0_PRIORITY
#define DT_SPI_0_PERIPHERAL_ID               DT_ATMEL_SAM_SPI_40008000_PERIPHERAL_ID

#define DT_SPI_1_BASE_ADDRESS                DT_ATMEL_SAM_SPI_40058000_BASE_ADDRESS
#define DT_SPI_1_NAME                        DT_ATMEL_SAM_SPI_40058000_LABEL
#define DT_SPI_1_IRQ                         DT_ATMEL_SAM_SPI_40058000_IRQ_0
#define DT_SPI_1_IRQ_PRI                     DT_ATMEL_SAM_SPI_40058000_IRQ_0_PRIORITY
#define DT_SPI_1_PERIPHERAL_ID               DT_ATMEL_SAM_SPI_40058000_PERIPHERAL_ID

#define DT_UART_SAM_PORT_0_NAME              DT_ATMEL_SAM_UART_400E0800_LABEL
#define DT_UART_SAM_PORT_0_BAUD_RATE         DT_ATMEL_SAM_UART_400E0800_CURRENT_SPEED
#define DT_UART_SAM_PORT_0_IRQ               DT_ATMEL_SAM_UART_400E0800_IRQ_0
#define DT_UART_SAM_PORT_0_IRQ_PRIO          DT_ATMEL_SAM_UART_400E0800_IRQ_0_PRIORITY
#define DT_UART_SAM_PORT_1_NAME              DT_ATMEL_SAM_UART_400E0A00_LABEL
#define DT_UART_SAM_PORT_1_BAUD_RATE         DT_ATMEL_SAM_UART_400E0A00_CURRENT_SPEED
#define DT_UART_SAM_PORT_1_IRQ               DT_ATMEL_SAM_UART_400E0A00_IRQ_0
#define DT_UART_SAM_PORT_1_IRQ_PRIO          DT_ATMEL_SAM_UART_400E0A00_IRQ_0_PRIORITY
#define DT_UART_SAM_PORT_2_NAME              DT_ATMEL_SAM_UART_400E1A00_LABEL
#define DT_UART_SAM_PORT_2_BAUD_RATE         DT_ATMEL_SAM_UART_400E1A00_CURRENT_SPEED
#define DT_UART_SAM_PORT_2_IRQ               DT_ATMEL_SAM_UART_400E1A00_IRQ_0
#define DT_UART_SAM_PORT_2_IRQ_PRIO          DT_ATMEL_SAM_UART_400E1A00_IRQ_0_PRIORITY
#define DT_UART_SAM_PORT_3_NAME              DT_ATMEL_SAM_UART_400E1C00_LABEL
#define DT_UART_SAM_PORT_3_BAUD_RATE         DT_ATMEL_SAM_UART_400E1C00_CURRENT_SPEED
#define DT_UART_SAM_PORT_3_IRQ               DT_ATMEL_SAM_UART_400E1C00_IRQ_0
#define DT_UART_SAM_PORT_3_IRQ_PRIO          DT_ATMEL_SAM_UART_400E1C00_IRQ_0_PRIORITY
#define DT_UART_SAM_PORT_4_NAME              DT_ATMEL_SAM_UART_400E1E00_LABEL
#define DT_UART_SAM_PORT_4_BAUD_RATE         DT_ATMEL_SAM_UART_400E1E00_CURRENT_SPEED
#define DT_UART_SAM_PORT_4_IRQ               DT_ATMEL_SAM_UART_400E1E00_IRQ_0
#define DT_UART_SAM_PORT_4_IRQ_PRIO          DT_ATMEL_SAM_UART_400E1E00_IRQ_0_PRIORITY

#define DT_USART_SAM_PORT_0_NAME             DT_ATMEL_SAM_USART_40024000_LABEL
#define DT_USART_SAM_PORT_0_BAUD_RATE        DT_ATMEL_SAM_USART_40024000_CURRENT_SPEED
#define DT_USART_SAM_PORT_0_IRQ              DT_ATMEL_SAM_USART_40024000_IRQ_0
#define DT_USART_SAM_PORT_0_IRQ_PRIO         DT_ATMEL_SAM_USART_40024000_IRQ_0_PRIORITY
#define DT_USART_SAM_PORT_0_PERIPHERAL_ID    DT_ATMEL_SAM_USART_40024000_PERIPHERAL_ID
#define DT_USART_SAM_PORT_1_NAME             DT_ATMEL_SAM_USART_40028000_LABEL
#define DT_USART_SAM_PORT_1_BAUD_RATE        DT_ATMEL_SAM_USART_40028000_CURRENT_SPEED
#define DT_USART_SAM_PORT_1_IRQ              DT_ATMEL_SAM_USART_40028000_IRQ_0
#define DT_USART_SAM_PORT_1_IRQ_PRIO         DT_ATMEL_SAM_USART_40028000_IRQ_0_PRIORITY
#define DT_USART_SAM_PORT_1_PERIPHERAL_ID    DT_ATMEL_SAM_USART_40028000_PERIPHERAL_ID
#define DT_USART_SAM_PORT_2_NAME             DT_ATMEL_SAM_USART_4002C000_LABEL
#define DT_USART_SAM_PORT_2_BAUD_RATE        DT_ATMEL_SAM_USART_4002C000_CURRENT_SPEED
#define DT_USART_SAM_PORT_2_IRQ              DT_ATMEL_SAM_USART_4002C000_IRQ_0
#define DT_USART_SAM_PORT_2_IRQ_PRIO         DT_ATMEL_SAM_USART_4002C000_IRQ_0_PRIORITY
#define DT_USART_SAM_PORT_2_PERIPHERAL_ID    DT_ATMEL_SAM_USART_4002C000_PERIPHERAL_ID

#define DT_ADC_0_BASE_ADDRESS                DT_ATMEL_SAM_AFEC_4003C000_BASE_ADDRESS
#define DT_ADC_0_IRQ                         DT_ATMEL_SAM_AFEC_4003C000_IRQ_0
#define DT_ADC_0_IRQ_PRI                     DT_ATMEL_SAM_AFEC_4003C000_IRQ_0_PRIORITY
#define DT_ADC_0_NAME                        DT_ATMEL_SAM_AFEC_4003C000_LABEL
#define DT_ADC_0_PERIPHERAL_ID               DT_ATMEL_SAM_AFEC_4003C000_PERIPHERAL_ID

#define DT_ADC_1_BASE_ADDRESS                DT_ATMEL_SAM_AFEC_40064000_BASE_ADDRESS
#define DT_ADC_1_IRQ                         DT_ATMEL_SAM_AFEC_40064000_IRQ_0
#define DT_ADC_1_IRQ_PRI                     DT_ATMEL_SAM_AFEC_40064000_IRQ_0_PRIORITY
#define DT_ADC_1_NAME                        DT_ATMEL_SAM_AFEC_40064000_LABEL
#define DT_ADC_1_PERIPHERAL_ID               DT_ATMEL_SAM_AFEC_40064000_PERIPHERAL_ID

#define DT_USBHS_IRQ                         DT_ATMEL_SAM_USBHS_40038000_IRQ_0
#define DT_USBHS_IRQ_PRI                     DT_ATMEL_SAM_USBHS_40038000_IRQ_0_PRIORITY
#define DT_USBHS_MAXIMUM_SPEED               DT_ATMEL_SAM_USBHS_40038000_MAXIMUM_SPEED
#define DT_USBHS_NUM_BIDIR_EP                DT_ATMEL_SAM_USBHS_40038000_NUM_BIDIR_ENDPOINTS
#define DT_USBHS_PERIPHERAL_ID               DT_ATMEL_SAM_USBHS_40038000_PERIPHERAL_ID
#define DT_USBHS_RAM_BASE_ADDRESS            DT_ATMEL_SAM_USBHS_40038000_RAM_0

#define CONFIG_ENTROPY_NAME                  DT_ATMEL_SAM_TRNG_40070000_LABEL

#define DT_FLASH_DEV_BASE_ADDRESS            DT_ATMEL_SAM_FLASH_CONTROLLER_400E0C00_BASE_ADDRESS
#define DT_FLASH_DEV_NAME                    DT_ATMEL_SAM_FLASH_CONTROLLER_400E0C00_LABEL

/* End of SoC Level DTS fixup file */
