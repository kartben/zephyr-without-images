/* This file is a temporary workaround for mapping of the generated information
 * to the current driver definitions.  This will be removed when the drivers
 * are modified to handle the generated information, or the mapping of
 * generated data matches the driver definitions.
 */

/* SoC level DTS fixup file */

#define DT_NUM_IRQ_PRIO_BITS	DT_ARM_V7M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS

#define DT_FLASH_DEV_BASE_ADDRESS		DT_SILABS_GECKO_FLASH_CONTROLLER_400E0000_BASE_ADDRESS
#define DT_FLASH_DEV_NAME			DT_SILABS_GECKO_FLASH_CONTROLLER_400E0000_LABEL

#define DT_USART_GECKO_0_BASE_ADDRESS	DT_SILABS_GECKO_USART_40010000_BASE_ADDRESS
#define DT_USART_GECKO_0_CURRENT_SPEED	DT_SILABS_GECKO_USART_40010000_CURRENT_SPEED
#define DT_USART_GECKO_0_IRQ_RX		DT_SILABS_GECKO_USART_40010000_IRQ_0
#define DT_USART_GECKO_0_IRQ_RX_PRIORITY	DT_SILABS_GECKO_USART_40010000_IRQ_0_PRIORITY
#define DT_USART_GECKO_0_IRQ_TX		DT_SILABS_GECKO_USART_40010000_IRQ_1
#define DT_USART_GECKO_0_IRQ_TX_PRIORITY	DT_SILABS_GECKO_USART_40010000_IRQ_1_PRIORITY
#define DT_USART_GECKO_0_LABEL		DT_SILABS_GECKO_USART_40010000_LABEL
#define DT_USART_GECKO_0_LOCATION		DT_SILABS_GECKO_USART_40010000_LOCATION
#define DT_USART_GECKO_0_SIZE		DT_SILABS_GECKO_USART_40010000_SIZE

#define DT_USART_GECKO_1_BASE_ADDRESS	DT_SILABS_GECKO_USART_40010400_BASE_ADDRESS
#define DT_USART_GECKO_1_CURRENT_SPEED	DT_SILABS_GECKO_USART_40010400_CURRENT_SPEED
#define DT_USART_GECKO_1_IRQ_RX		DT_SILABS_GECKO_USART_40010400_IRQ_0
#define DT_USART_GECKO_1_IRQ_RX_PRIORITY	DT_SILABS_GECKO_USART_40010400_IRQ_0_PRIORITY
#define DT_USART_GECKO_1_IRQ_TX		DT_SILABS_GECKO_USART_40010400_IRQ_1
#define DT_USART_GECKO_1_IRQ_TX_PRIORITY	DT_SILABS_GECKO_USART_40010400_IRQ_1_PRIORITY
#define DT_USART_GECKO_1_LABEL		DT_SILABS_GECKO_USART_40010400_LABEL
#define DT_USART_GECKO_1_LOCATION		DT_SILABS_GECKO_USART_40010400_LOCATION
#define DT_USART_GECKO_1_SIZE		DT_SILABS_GECKO_USART_40010400_SIZE

#define DT_USART_GECKO_2_BASE_ADDRESS	DT_SILABS_GECKO_USART_40010800_BASE_ADDRESS
#define DT_USART_GECKO_2_CURRENT_SPEED	DT_SILABS_GECKO_USART_40010800_CURRENT_SPEED
#define DT_USART_GECKO_2_IRQ_RX		DT_SILABS_GECKO_USART_40010800_IRQ_0
#define DT_USART_GECKO_2_IRQ_RX_PRIORITY	DT_SILABS_GECKO_USART_40010800_IRQ_0_PRIORITY
#define DT_USART_GECKO_2_IRQ_TX		DT_SILABS_GECKO_USART_40010800_IRQ_1
#define DT_USART_GECKO_2_IRQ_TX_PRIORITY	DT_SILABS_GECKO_USART_40010800_IRQ_1_PRIORITY
#define DT_USART_GECKO_2_LABEL		DT_SILABS_GECKO_USART_40010800_LABEL
#define DT_USART_GECKO_2_LOCATION		DT_SILABS_GECKO_USART_40010800_LOCATION
#define DT_USART_GECKO_2_SIZE		DT_SILABS_GECKO_USART_40010800_SIZE

#define DT_USART_GECKO_3_BASE_ADDRESS	DT_SILABS_GECKO_USART_40010C00_BASE_ADDRESS
#define DT_USART_GECKO_3_CURRENT_SPEED	DT_SILABS_GECKO_USART_40010C00_CURRENT_SPEED
#define DT_USART_GECKO_3_IRQ_RX		DT_SILABS_GECKO_USART_40010C00_IRQ_0
#define DT_USART_GECKO_3_IRQ_RX_PRIORITY	DT_SILABS_GECKO_USART_40010C00_IRQ_0_PRIORITY
#define DT_USART_GECKO_3_IRQ_TX		DT_SILABS_GECKO_USART_40010C00_IRQ_1
#define DT_USART_GECKO_3_IRQ_TX_PRIORITY	DT_SILABS_GECKO_USART_40010C00_IRQ_1_PRIORITY
#define DT_USART_GECKO_3_LABEL		DT_SILABS_GECKO_USART_40010C00_LABEL
#define DT_USART_GECKO_3_LOCATION		DT_SILABS_GECKO_USART_40010C00_LOCATION
#define DT_USART_GECKO_3_SIZE		DT_SILABS_GECKO_USART_40010C00_SIZE

#define DT_LEUART_GECKO_0_BASE_ADDRESS	DT_SILABS_GECKO_LEUART_4004A000_BASE_ADDRESS
#define DT_LEUART_GECKO_0_CURRENT_SPEED	DT_SILABS_GECKO_LEUART_4004A000_CURRENT_SPEED
#define DT_LEUART_GECKO_0_IRQ		DT_SILABS_GECKO_LEUART_4004A000_IRQ_0
#define DT_LEUART_GECKO_0_IRQ_PRIORITY	DT_SILABS_GECKO_LEUART_4004A000_IRQ_0_PRIORITY
#define DT_LEUART_GECKO_0_LABEL		DT_SILABS_GECKO_LEUART_4004A000_LABEL
#define DT_LEUART_GECKO_0_LOCATION		DT_SILABS_GECKO_LEUART_4004A000_LOCATION
#define DT_LEUART_GECKO_0_SIZE		DT_SILABS_GECKO_LEUART_4004A000_SIZE

#define DT_GPIO_GECKO_COMMON_NAME		DT_SILABS_EFR32MG_GPIO_4000A400_LABEL
#define DT_GPIO_GECKO_COMMON_EVEN_IRQ	DT_SILABS_EFR32MG_GPIO_4000A400_IRQ_GPIO_EVEN
#define DT_GPIO_GECKO_COMMON_EVEN_PRI	DT_SILABS_EFR32MG_GPIO_4000A400_IRQ_GPIO_EVEN_PRIORITY
#define DT_GPIO_GECKO_COMMON_ODD_IRQ	DT_SILABS_EFR32MG_GPIO_4000A400_IRQ_GPIO_ODD
#define DT_GPIO_GECKO_COMMON_ODD_PRI	DT_SILABS_EFR32MG_GPIO_4000A400_IRQ_GPIO_ODD_PRIORITY

#define DT_GPIO_GECKO_PORTA_NAME	DT_SILABS_EFR32MG_GPIO_PORT_4000A000_LABEL
#define DT_GPIO_GECKO_PORTB_NAME	DT_SILABS_EFR32MG_GPIO_PORT_4000A030_LABEL
#define DT_GPIO_GECKO_PORTC_NAME	DT_SILABS_EFR32MG_GPIO_PORT_4000A060_LABEL
#define DT_GPIO_GECKO_PORTD_NAME	DT_SILABS_EFR32MG_GPIO_PORT_4000A090_LABEL
#define DT_GPIO_GECKO_PORTE_NAME	DT_SILABS_EFR32MG_GPIO_PORT_4000A0C0_LABEL
#define DT_GPIO_GECKO_PORTF_NAME	DT_SILABS_EFR32MG_GPIO_PORT_4000A0F0_LABEL

#define DT_I2C_GECKO_0_BASE_ADDRESS		DT_SILABS_GECKO_I2C_4000C000_BASE_ADDRESS
#define DT_I2C_GECKO_0_CLOCK_FREQUENCY	DT_SILABS_GECKO_I2C_4000C000_CLOCK_FREQUENCY
#define DT_I2C_GECKO_0_IRQ			DT_SILABS_GECKO_I2C_4000C000_IRQ_0
#define DT_I2C_GECKO_0_IRQ_PRIORITY		DT_SILABS_GECKO_I2C_4000C000_IRQ_0_PRIORITY
#define DT_I2C_GECKO_0_LABEL		DT_SILABS_GECKO_I2C_4000C000_LABEL
#define DT_I2C_GECKO_0_LOCATION		DT_SILABS_GECKO_I2C_4000C000_LOCATION
#define DT_I2C_GECKO_0_SIZE			DT_SILABS_GECKO_I2C_4000C000_SIZE

#define DT_I2C_GECKO_1_BASE_ADDRESS		DT_SILABS_GECKO_I2C_4000C400_BASE_ADDRESS
#define DT_I2C_GECKO_1_CLOCK_FREQUENCY	DT_SILABS_GECKO_I2C_4000C400_CLOCK_FREQUENCY
#define DT_I2C_GECKO_1_IRQ			DT_SILABS_GECKO_I2C_4000C400_IRQ_0
#define DT_I2C_GECKO_1_IRQ_PRIORITY		DT_SILABS_GECKO_I2C_4000C400_IRQ_0_PRIORITY
#define DT_I2C_GECKO_1_LABEL		DT_SILABS_GECKO_I2C_4000C400_LABEL
#define DT_I2C_GECKO_1_LOCATION		DT_SILABS_GECKO_I2C_4000C400_LOCATION
#define DT_I2C_GECKO_1_SIZE			DT_SILABS_GECKO_I2C_4000C400_SIZE

/* End of SoC Level DTS fixup file */
