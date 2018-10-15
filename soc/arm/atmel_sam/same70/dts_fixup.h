/* This file is a temporary workaround for mapping of the generated information
 * to the current driver definitions.  This will be removed when the drivers
 * are modified to handle the generated information, or the mapping of
 * generated data matches the driver definitions.
 */

/* SoC level DTS fixup file */

#define CONFIG_NUM_IRQ_PRIO_BITS	ARM_V7M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS

#define CONFIG_GPIO_SAM_PORTA_LABEL	ATMEL_SAM_GPIO_400E0E00_LABEL
#define CONFIG_GPIO_SAM_PORTA_BASE_ADDRESS	ATMEL_SAM_GPIO_400E0E00_BASE_ADDRESS
#define CONFIG_GPIO_SAM_PORTA_IRQ	ATMEL_SAM_GPIO_400E0E00_IRQ_0
#define CONFIG_GPIO_SAM_PORTA_IRQ_PRIO	ATMEL_SAM_GPIO_400E0E00_IRQ_0_PRIORITY
#define CONFIG_GPIO_SAM_PORTA_PERIPHERAL_ID	ATMEL_SAM_GPIO_400E0E00_PERIPHERAL_ID
#define CONFIG_GPIO_SAM_PORTB_LABEL	ATMEL_SAM_GPIO_400E1000_LABEL
#define CONFIG_GPIO_SAM_PORTB_BASE_ADDRESS	ATMEL_SAM_GPIO_400E1000_BASE_ADDRESS
#define CONFIG_GPIO_SAM_PORTB_IRQ	ATMEL_SAM_GPIO_400E1000_IRQ_0
#define CONFIG_GPIO_SAM_PORTB_IRQ_PRIO	ATMEL_SAM_GPIO_400E1000_IRQ_0_PRIORITY
#define CONFIG_GPIO_SAM_PORTB_PERIPHERAL_ID	ATMEL_SAM_GPIO_400E1000_PERIPHERAL_ID
#define CONFIG_GPIO_SAM_PORTC_LABEL	ATMEL_SAM_GPIO_400E1200_LABEL
#define CONFIG_GPIO_SAM_PORTC_BASE_ADDRESS	ATMEL_SAM_GPIO_400E1200_BASE_ADDRESS
#define CONFIG_GPIO_SAM_PORTC_IRQ	ATMEL_SAM_GPIO_400E1200_IRQ_0
#define CONFIG_GPIO_SAM_PORTC_IRQ_PRIO	ATMEL_SAM_GPIO_400E1200_IRQ_0_PRIORITY
#define CONFIG_GPIO_SAM_PORTC_PERIPHERAL_ID	ATMEL_SAM_GPIO_400E1200_PERIPHERAL_ID
#define CONFIG_GPIO_SAM_PORTD_LABEL	ATMEL_SAM_GPIO_400E1400_LABEL
#define CONFIG_GPIO_SAM_PORTD_BASE_ADDRESS	ATMEL_SAM_GPIO_400E1400_BASE_ADDRESS
#define CONFIG_GPIO_SAM_PORTD_IRQ	ATMEL_SAM_GPIO_400E1400_IRQ_0
#define CONFIG_GPIO_SAM_PORTD_IRQ_PRIO	ATMEL_SAM_GPIO_400E1400_IRQ_0_PRIORITY
#define CONFIG_GPIO_SAM_PORTD_PERIPHERAL_ID	ATMEL_SAM_GPIO_400E1400_PERIPHERAL_ID
#define CONFIG_GPIO_SAM_PORTE_LABEL	ATMEL_SAM_GPIO_400E1600_LABEL
#define CONFIG_GPIO_SAM_PORTE_BASE_ADDRESS	ATMEL_SAM_GPIO_400E1600_BASE_ADDRESS
#define CONFIG_GPIO_SAM_PORTE_IRQ	ATMEL_SAM_GPIO_400E1600_IRQ_0
#define CONFIG_GPIO_SAM_PORTE_IRQ_PRIO	ATMEL_SAM_GPIO_400E1600_IRQ_0_PRIORITY
#define CONFIG_GPIO_SAM_PORTE_PERIPHERAL_ID	ATMEL_SAM_GPIO_400E1600_PERIPHERAL_ID

#define CONFIG_I2C_0_BASE_ADDRESS	ATMEL_SAM_I2C_TWIHS_40018000_BASE_ADDRESS
#define CONFIG_I2C_0_NAME		ATMEL_SAM_I2C_TWIHS_40018000_LABEL
#define CONFIG_I2C_0_BITRATE		ATMEL_SAM_I2C_TWIHS_40018000_CLOCK_FREQUENCY
#define CONFIG_I2C_0_IRQ		ATMEL_SAM_I2C_TWIHS_40018000_IRQ_0
#define CONFIG_I2C_0_IRQ_PRI		ATMEL_SAM_I2C_TWIHS_40018000_IRQ_0_PRIORITY
#define CONFIG_I2C_0_PERIPHERAL_ID	ATMEL_SAM_I2C_TWIHS_40018000_PERIPHERAL_ID

#define CONFIG_I2C_1_BASE_ADDRESS	ATMEL_SAM_I2C_TWIHS_4001C000_BASE_ADDRESS
#define CONFIG_I2C_1_NAME		ATMEL_SAM_I2C_TWIHS_4001C000_LABEL
#define CONFIG_I2C_1_BITRATE		ATMEL_SAM_I2C_TWIHS_4001C000_CLOCK_FREQUENCY
#define CONFIG_I2C_1_IRQ		ATMEL_SAM_I2C_TWIHS_4001C000_IRQ_0
#define CONFIG_I2C_1_IRQ_PRI		ATMEL_SAM_I2C_TWIHS_4001C000_IRQ_0_PRIORITY
#define CONFIG_I2C_1_PERIPHERAL_ID	ATMEL_SAM_I2C_TWIHS_4001C000_PERIPHERAL_ID

#define CONFIG_I2C_2_BASE_ADDRESS	ATMEL_SAM_I2C_TWIHS_40060000_BASE_ADDRESS
#define CONFIG_I2C_2_NAME		ATMEL_SAM_I2C_TWIHS_40060000_LABEL
#define CONFIG_I2C_2_BITRATE		ATMEL_SAM_I2C_TWIHS_40060000_CLOCK_FREQUENCY
#define CONFIG_I2C_2_IRQ		ATMEL_SAM_I2C_TWIHS_40060000_IRQ_0
#define CONFIG_I2C_2_IRQ_PRI		ATMEL_SAM_I2C_TWIHS_40060000_IRQ_0_PRIORITY
#define CONFIG_I2C_2_PERIPHERAL_ID	ATMEL_SAM_I2C_TWIHS_40060000_PERIPHERAL_ID

#define CONFIG_SPI_0_BASE_ADDRESS	ATMEL_SAM_SPI_40008000_BASE_ADDRESS
#define CONFIG_SPI_0_NAME		ATMEL_SAM_SPI_40008000_LABEL
#define CONFIG_SPI_0_IRQ		ATMEL_SAM_SPI_40008000_IRQ_0
#define CONFIG_SPI_0_IRQ_PRI		ATMEL_SAM_SPI_40008000_IRQ_0_PRIORITY
#define CONFIG_SPI_0_PERIPHERAL_ID	ATMEL_SAM_SPI_40008000_PERIPHERAL_ID

#define CONFIG_SPI_1_BASE_ADDRESS	ATMEL_SAM_SPI_40058000_BASE_ADDRESS
#define CONFIG_SPI_1_NAME		ATMEL_SAM_SPI_40058000_LABEL
#define CONFIG_SPI_1_IRQ		ATMEL_SAM_SPI_40058000_IRQ_0
#define CONFIG_SPI_1_IRQ_PRI		ATMEL_SAM_SPI_40058000_IRQ_0_PRIORITY
#define CONFIG_SPI_1_PERIPHERAL_ID	ATMEL_SAM_SPI_40058000_PERIPHERAL_ID

#define CONFIG_UART_SAM_PORT_0_NAME	ATMEL_SAM_UART_400E0800_LABEL
#define CONFIG_UART_SAM_PORT_0_BAUD_RATE	ATMEL_SAM_UART_400E0800_CURRENT_SPEED
#define CONFIG_UART_SAM_PORT_0_IRQ	ATMEL_SAM_UART_400E0800_IRQ_0
#define CONFIG_UART_SAM_PORT_0_IRQ_PRIO	ATMEL_SAM_UART_400E0800_IRQ_0_PRIORITY
#define CONFIG_UART_SAM_PORT_1_NAME	ATMEL_SAM_UART_400E0A00_LABEL
#define CONFIG_UART_SAM_PORT_1_BAUD_RATE	ATMEL_SAM_UART_400E0A00_CURRENT_SPEED
#define CONFIG_UART_SAM_PORT_1_IRQ	ATMEL_SAM_UART_400E0A00_IRQ_0
#define CONFIG_UART_SAM_PORT_1_IRQ_PRIO	ATMEL_SAM_UART_400E0A00_IRQ_0_PRIORITY
#define CONFIG_UART_SAM_PORT_2_NAME	ATMEL_SAM_UART_400E1A00_LABEL
#define CONFIG_UART_SAM_PORT_2_BAUD_RATE	ATMEL_SAM_UART_400E1A00_CURRENT_SPEED
#define CONFIG_UART_SAM_PORT_2_IRQ	ATMEL_SAM_UART_400E1A00_IRQ_0
#define CONFIG_UART_SAM_PORT_2_IRQ_PRIO	ATMEL_SAM_UART_400E1A00_IRQ_0_PRIORITY
#define CONFIG_UART_SAM_PORT_3_NAME	ATMEL_SAM_UART_400E1C00_LABEL
#define CONFIG_UART_SAM_PORT_3_BAUD_RATE	ATMEL_SAM_UART_400E1C00_CURRENT_SPEED
#define CONFIG_UART_SAM_PORT_3_IRQ	ATMEL_SAM_UART_400E1C00_IRQ_0
#define CONFIG_UART_SAM_PORT_3_IRQ_PRIO	ATMEL_SAM_UART_400E1C00_IRQ_0_PRIORITY
#define CONFIG_UART_SAM_PORT_4_NAME	ATMEL_SAM_UART_400E1E00_LABEL
#define CONFIG_UART_SAM_PORT_4_BAUD_RATE	ATMEL_SAM_UART_400E1E00_CURRENT_SPEED
#define CONFIG_UART_SAM_PORT_4_IRQ	ATMEL_SAM_UART_400E1E00_IRQ_0
#define CONFIG_UART_SAM_PORT_4_IRQ_PRIO	ATMEL_SAM_UART_400E1E00_IRQ_0_PRIORITY
#define CONFIG_USART_SAM_PORT_0_NAME	ATMEL_SAM_USART_40024000_LABEL
#define CONFIG_USART_SAM_PORT_0_BAUD_RATE	ATMEL_SAM_USART_40024000_CURRENT_SPEED
#define CONFIG_USART_SAM_PORT_0_IRQ	ATMEL_SAM_USART_40024000_IRQ_0
#define CONFIG_USART_SAM_PORT_0_IRQ_PRIO	ATMEL_SAM_USART_40024000_IRQ_0_PRIORITY
#define CONFIG_USART_SAM_PORT_0_PERIPHERAL_ID	ATMEL_SAM_USART_40024000_PERIPHERAL_ID
#define CONFIG_USART_SAM_PORT_1_NAME	ATMEL_SAM_USART_40028000_LABEL
#define CONFIG_USART_SAM_PORT_1_BAUD_RATE	ATMEL_SAM_USART_40028000_CURRENT_SPEED
#define CONFIG_USART_SAM_PORT_1_IRQ	ATMEL_SAM_USART_40028000_IRQ_0
#define CONFIG_USART_SAM_PORT_1_IRQ_PRIO	ATMEL_SAM_USART_40028000_IRQ_0_PRIORITY
#define CONFIG_USART_SAM_PORT_1_PERIPHERAL_ID	ATMEL_SAM_USART_40028000_PERIPHERAL_ID
#define CONFIG_USART_SAM_PORT_2_NAME	ATMEL_SAM_USART_4002C000_LABEL
#define CONFIG_USART_SAM_PORT_2_BAUD_RATE	ATMEL_SAM_USART_4002C000_CURRENT_SPEED
#define CONFIG_USART_SAM_PORT_2_IRQ	ATMEL_SAM_USART_4002C000_IRQ_0
#define CONFIG_USART_SAM_PORT_2_IRQ_PRIO	ATMEL_SAM_USART_4002C000_IRQ_0_PRIORITY
#define CONFIG_USART_SAM_PORT_2_PERIPHERAL_ID	ATMEL_SAM_USART_4002C000_PERIPHERAL_ID

#define CONFIG_ADC_0_BASE_ADDRESS	ATMEL_SAM_AFEC_4003C000_BASE_ADDRESS
#define CONFIG_ADC_0_IRQ	ATMEL_SAM_AFEC_4003C000_IRQ_0
#define CONFIG_ADC_0_IRQ_PRI	ATMEL_SAM_AFEC_4003C000_IRQ_0_PRIORITY
#define CONFIG_ADC_0_NAME	ATMEL_SAM_AFEC_4003C000_LABEL
#define CONFIG_ADC_0_PERIPHERAL_ID	ATMEL_SAM_AFEC_4003C000_PERIPHERAL_ID

#define CONFIG_ADC_1_BASE_ADDRESS	ATMEL_SAM_AFEC_40064000_BASE_ADDRESS
#define CONFIG_ADC_1_IRQ	ATMEL_SAM_AFEC_40064000_IRQ_0
#define CONFIG_ADC_1_IRQ_PRI	ATMEL_SAM_AFEC_40064000_IRQ_0_PRIORITY
#define CONFIG_ADC_1_NAME	ATMEL_SAM_AFEC_40064000_LABEL
#define CONFIG_ADC_1_PERIPHERAL_ID	ATMEL_SAM_AFEC_40064000_PERIPHERAL_ID

/* End of SoC Level DTS fixup file */
