/*
 * Copyright (c) 2019 Gerson Fernando Budke
 * SPDX-License-Identifier: Apache-2.0
 */

/* This file is a temporary workaround for mapping of the generated
 * information to the current driver definitions.  This will be removed
 * when the drivers are modified to handle the generated information,
 * or the mapping of generated data matches the driver definitions.
 */

/* SoC level DTS fixup file */

#define DT_NUM_IRQ_PRIO_BITS            DT_ARM_V7M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS

#define DT_GPIO_SAM_PORTA_LABEL         DT_ATMEL_SAM_GPIO_400E0E00_LABEL
#define DT_GPIO_SAM_PORTA_BASE_ADDRESS  DT_ATMEL_SAM_GPIO_400E0E00_BASE_ADDRESS
#define DT_GPIO_SAM_PORTA_IRQ           DT_ATMEL_SAM_GPIO_400E0E00_IRQ_0
#define DT_GPIO_SAM_PORTA_IRQ_PRIO      DT_ATMEL_SAM_GPIO_400E0E00_IRQ_0_PRIORITY
#define DT_GPIO_SAM_PORTA_PERIPHERAL_ID DT_ATMEL_SAM_GPIO_400E0E00_PERIPHERAL_ID
#define DT_GPIO_SAM_PORTB_LABEL         DT_ATMEL_SAM_GPIO_400E1000_LABEL
#define DT_GPIO_SAM_PORTB_BASE_ADDRESS  DT_ATMEL_SAM_GPIO_400E1000_BASE_ADDRESS
#define DT_GPIO_SAM_PORTB_IRQ           DT_ATMEL_SAM_GPIO_400E1000_IRQ_0
#define DT_GPIO_SAM_PORTB_IRQ_PRIO      DT_ATMEL_SAM_GPIO_400E1000_IRQ_0_PRIORITY
#define DT_GPIO_SAM_PORTB_PERIPHERAL_ID DT_ATMEL_SAM_GPIO_400E1000_PERIPHERAL_ID
#define DT_GPIO_SAM_PORTC_LABEL         DT_ATMEL_SAM_GPIO_400E1200_LABEL
#define DT_GPIO_SAM_PORTC_BASE_ADDRESS  DT_ATMEL_SAM_GPIO_400E1200_BASE_ADDRESS
#define DT_GPIO_SAM_PORTC_IRQ           DT_ATMEL_SAM_GPIO_400E1200_IRQ_0
#define DT_GPIO_SAM_PORTC_IRQ_PRIO      DT_ATMEL_SAM_GPIO_400E1200_IRQ_0_PRIORITY
#define DT_GPIO_SAM_PORTC_PERIPHERAL_ID DT_ATMEL_SAM_GPIO_400E1200_PERIPHERAL_ID
#define DT_GPIO_SAM_PORTD_LABEL         DT_ATMEL_SAM_GPIO_400E1400_LABEL
#define DT_GPIO_SAM_PORTD_BASE_ADDRESS  DT_ATMEL_SAM_GPIO_400E1400_BASE_ADDRESS
#define DT_GPIO_SAM_PORTD_IRQ           DT_ATMEL_SAM_GPIO_400E1400_IRQ_0
#define DT_GPIO_SAM_PORTD_IRQ_PRIO      DT_ATMEL_SAM_GPIO_400E1400_IRQ_0_PRIORITY
#define DT_GPIO_SAM_PORTD_PERIPHERAL_ID DT_ATMEL_SAM_GPIO_400E1400_PERIPHERAL_ID
#define DT_GPIO_SAM_PORTE_LABEL         DT_ATMEL_SAM_GPIO_400E1600_LABEL
#define DT_GPIO_SAM_PORTE_BASE_ADDRESS  DT_ATMEL_SAM_GPIO_400E1600_BASE_ADDRESS
#define DT_GPIO_SAM_PORTE_IRQ           DT_ATMEL_SAM_GPIO_400E1600_IRQ_0
#define DT_GPIO_SAM_PORTE_IRQ_PRIO      DT_ATMEL_SAM_GPIO_400E1600_IRQ_0_PRIORITY
#define DT_GPIO_SAM_PORTE_PERIPHERAL_ID DT_ATMEL_SAM_GPIO_400E1600_PERIPHERAL_ID

#define DT_I2C_0_BASE_ADDRESS           DT_ATMEL_SAM_I2C_TWI_400A8000_BASE_ADDRESS
#define DT_I2C_0_NAME                   DT_ATMEL_SAM_I2C_TWI_400A8000_LABEL
#define DT_I2C_0_BITRATE                DT_ATMEL_SAM_I2C_TWI_400A8000_CLOCK_FREQUENCY
#define DT_I2C_0_IRQ                    DT_ATMEL_SAM_I2C_TWI_400A8000_IRQ_0
#define DT_I2C_0_IRQ_PRI                DT_ATMEL_SAM_I2C_TWI_400A8000_IRQ_0_PRIORITY
#define DT_I2C_0_PERIPHERAL_ID          DT_ATMEL_SAM_I2C_TWI_400A8000_PERIPHERAL_ID
#define DT_I2C_1_BASE_ADDRESS           DT_ATMEL_SAM_I2C_TWI_400AC000_BASE_ADDRESS
#define DT_I2C_1_NAME                   DT_ATMEL_SAM_I2C_TWI_400AC000_LABEL
#define DT_I2C_1_BITRATE                DT_ATMEL_SAM_I2C_TWI_400AC000_CLOCK_FREQUENCY
#define DT_I2C_1_IRQ                    DT_ATMEL_SAM_I2C_TWI_400AC000_IRQ_0
#define DT_I2C_1_IRQ_PRI                DT_ATMEL_SAM_I2C_TWI_400AC000_IRQ_0_PRIORITY
#define DT_I2C_1_PERIPHERAL_ID          DT_ATMEL_SAM_I2C_TWI_400AC000_PERIPHERAL_ID

#define DT_SPI_0_BASE_ADDRESS           DT_ATMEL_SAM_SPI_40088000_BASE_ADDRESS
#define DT_SPI_0_NAME                   DT_ATMEL_SAM_SPI_40088000_LABEL
#define DT_SPI_0_IRQ                    DT_ATMEL_SAM_SPI_40088000_IRQ_0
#define DT_SPI_0_IRQ_PRI                DT_ATMEL_SAM_SPI_40088000_IRQ_0_PRIORITY
#define DT_SPI_0_PERIPHERAL_ID          DT_ATMEL_SAM_SPI_40088000_PERIPHERAL_ID

#define DT_UART_SAM_PORT_0_NAME         DT_ATMEL_SAM_UART_400E0600_LABEL
#define DT_UART_SAM_PORT_0_BAUD_RATE    DT_ATMEL_SAM_UART_400E0600_CURRENT_SPEED
#define DT_UART_SAM_PORT_0_IRQ          DT_ATMEL_SAM_UART_400E0600_IRQ_0
#define DT_UART_SAM_PORT_0_IRQ_PRIO     DT_ATMEL_SAM_UART_400E0600_IRQ_0_PRIORITY
#define DT_UART_SAM_PORT_1_NAME         DT_ATMEL_SAM_UART_40060600_LABEL
#define DT_UART_SAM_PORT_1_BAUD_RATE    DT_ATMEL_SAM_UART_40060600_CURRENT_SPEED
#define DT_UART_SAM_PORT_1_IRQ          DT_ATMEL_SAM_UART_40060600_IRQ_0
#define DT_UART_SAM_PORT_1_IRQ_PRIO     DT_ATMEL_SAM_UART_40060600_IRQ_0_PRIORITY
#define DT_USART_SAM_PORT_0_NAME        DT_ATMEL_SAM_USART_400A0000_LABEL
#define DT_USART_SAM_PORT_0_BAUD_RATE   DT_ATMEL_SAM_USART_400A0000_CURRENT_SPEED
#define DT_USART_SAM_PORT_1_NAME        DT_ATMEL_SAM_USART_400A4000_LABEL
#define DT_USART_SAM_PORT_1_BAUD_RATE   DT_ATMEL_SAM_USART_400A4000_CURRENT_SPEED

#define DT_WDT_SAM_IRQ                  DT_ATMEL_SAM_WATCHDOG_400E1850_IRQ_0
#define DT_WDT_SAM_IRQ_PRIORITY         DT_ATMEL_SAM_WATCHDOG_400E1850_IRQ_0_PRIORITY
#define DT_WDT_SAM_LABEL                DT_ATMEL_SAM_WATCHDOG_400E1850_LABEL
#define DT_WDT_SAM_BASE_ADDRESS         DT_ATMEL_SAM_WATCHDOG_400E1850_BASE_ADDRESS
/* End of SoC Level DTS fixup file */
