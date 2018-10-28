/* SoC level DTS fixup file */

#define CONFIG_NUM_IRQ_PRIO_BITS                ARM_V7M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS

#define CONFIG_GPIO_STM32_GPIOA_BASE_ADDRESS		ST_STM32_GPIO_48000000_BASE_ADDRESS
#define CONFIG_GPIO_STM32_GPIOA_CLOCK_BITS_0		ST_STM32_GPIO_48000000_CLOCK_BITS_0
#define CONFIG_GPIO_STM32_GPIOA_CLOCK_BUS_0		ST_STM32_GPIO_48000000_CLOCK_BUS_0
#define CONFIG_GPIO_STM32_GPIOA_CLOCK_CONTROLLER	ST_STM32_GPIO_48000000_CLOCK_CONTROLLER
#define CONFIG_GPIO_STM32_GPIOA_LABEL			ST_STM32_GPIO_48000000_LABEL
#define CONFIG_GPIO_STM32_GPIOA_SIZE			ST_STM32_GPIO_48000000_SIZE
#define CONFIG_GPIO_STM32_GPIOA_CLOCK_BITS		ST_STM32_GPIO_48000000_CLOCK_BITS
#define CONFIG_GPIO_STM32_GPIOA_CLOCK_BUS		ST_STM32_GPIO_48000000_CLOCK_BUS

#define CONFIG_GPIO_STM32_GPIOB_BASE_ADDRESS		ST_STM32_GPIO_48000400_BASE_ADDRESS
#define CONFIG_GPIO_STM32_GPIOB_CLOCK_BITS_0		ST_STM32_GPIO_48000400_CLOCK_BITS_0
#define CONFIG_GPIO_STM32_GPIOB_CLOCK_BUS_0		ST_STM32_GPIO_48000400_CLOCK_BUS_0
#define CONFIG_GPIO_STM32_GPIOB_CLOCK_CONTROLLER	ST_STM32_GPIO_48000400_CLOCK_CONTROLLER
#define CONFIG_GPIO_STM32_GPIOB_LABEL			ST_STM32_GPIO_48000400_LABEL
#define CONFIG_GPIO_STM32_GPIOB_SIZE			ST_STM32_GPIO_48000400_SIZE
#define CONFIG_GPIO_STM32_GPIOB_CLOCK_BITS		ST_STM32_GPIO_48000400_CLOCK_BITS
#define CONFIG_GPIO_STM32_GPIOB_CLOCK_BUS		ST_STM32_GPIO_48000400_CLOCK_BUS

#define CONFIG_GPIO_STM32_GPIOC_BASE_ADDRESS		ST_STM32_GPIO_48000800_BASE_ADDRESS
#define CONFIG_GPIO_STM32_GPIOC_CLOCK_BITS_0		ST_STM32_GPIO_48000800_CLOCK_BITS_0
#define CONFIG_GPIO_STM32_GPIOC_CLOCK_BUS_0		ST_STM32_GPIO_48000800_CLOCK_BUS_0
#define CONFIG_GPIO_STM32_GPIOC_CLOCK_CONTROLLER	ST_STM32_GPIO_48000800_CLOCK_CONTROLLER
#define CONFIG_GPIO_STM32_GPIOC_LABEL			ST_STM32_GPIO_48000800_LABEL
#define CONFIG_GPIO_STM32_GPIOC_SIZE			ST_STM32_GPIO_48000800_SIZE
#define CONFIG_GPIO_STM32_GPIOC_CLOCK_BITS		ST_STM32_GPIO_48000800_CLOCK_BITS
#define CONFIG_GPIO_STM32_GPIOC_CLOCK_BUS		ST_STM32_GPIO_48000800_CLOCK_BUS

#define CONFIG_GPIO_STM32_GPIOD_BASE_ADDRESS		ST_STM32_GPIO_48000C00_BASE_ADDRESS
#define CONFIG_GPIO_STM32_GPIOD_CLOCK_BITS_0		ST_STM32_GPIO_48000C00_CLOCK_BITS_0
#define CONFIG_GPIO_STM32_GPIOD_CLOCK_BUS_0		ST_STM32_GPIO_48000C00_CLOCK_BUS_0
#define CONFIG_GPIO_STM32_GPIOD_CLOCK_CONTROLLER	ST_STM32_GPIO_48000C00_CLOCK_CONTROLLER
#define CONFIG_GPIO_STM32_GPIOD_LABEL			ST_STM32_GPIO_48000C00_LABEL
#define CONFIG_GPIO_STM32_GPIOD_SIZE			ST_STM32_GPIO_48000C00_SIZE
#define CONFIG_GPIO_STM32_GPIOD_CLOCK_BITS		ST_STM32_GPIO_48000C00_CLOCK_BITS
#define CONFIG_GPIO_STM32_GPIOD_CLOCK_BUS		ST_STM32_GPIO_48000C00_CLOCK_BUS

#define CONFIG_GPIO_STM32_GPIOE_BASE_ADDRESS		ST_STM32_GPIO_48001000_BASE_ADDRESS
#define CONFIG_GPIO_STM32_GPIOE_CLOCK_BITS_0		ST_STM32_GPIO_48001000_CLOCK_BITS_0
#define CONFIG_GPIO_STM32_GPIOE_CLOCK_BUS_0		ST_STM32_GPIO_48001000_CLOCK_BUS_0
#define CONFIG_GPIO_STM32_GPIOE_CLOCK_CONTROLLER	ST_STM32_GPIO_48001000_CLOCK_CONTROLLER
#define CONFIG_GPIO_STM32_GPIOE_LABEL			ST_STM32_GPIO_48001000_LABEL
#define CONFIG_GPIO_STM32_GPIOE_SIZE			ST_STM32_GPIO_48001000_SIZE
#define CONFIG_GPIO_STM32_GPIOE_CLOCK_BITS		ST_STM32_GPIO_48001000_CLOCK_BITS
#define CONFIG_GPIO_STM32_GPIOE_CLOCK_BUS		ST_STM32_GPIO_48001000_CLOCK_BUS

#define CONFIG_GPIO_STM32_GPIOF_BASE_ADDRESS		ST_STM32_GPIO_48001400_BASE_ADDRESS
#define CONFIG_GPIO_STM32_GPIOF_CLOCK_BITS_0		ST_STM32_GPIO_48001400_CLOCK_BITS_0
#define CONFIG_GPIO_STM32_GPIOF_CLOCK_BUS_0		ST_STM32_GPIO_48001400_CLOCK_BUS_0
#define CONFIG_GPIO_STM32_GPIOF_CLOCK_CONTROLLER	ST_STM32_GPIO_48001400_CLOCK_CONTROLLER
#define CONFIG_GPIO_STM32_GPIOF_LABEL			ST_STM32_GPIO_48001400_LABEL
#define CONFIG_GPIO_STM32_GPIOF_SIZE			ST_STM32_GPIO_48001400_SIZE
#define CONFIG_GPIO_STM32_GPIOF_CLOCK_BITS		ST_STM32_GPIO_48001400_CLOCK_BITS
#define CONFIG_GPIO_STM32_GPIOF_CLOCK_BUS		ST_STM32_GPIO_48001400_CLOCK_BUS

#define CONFIG_UART_STM32_USART_1_BASE_ADDRESS   ST_STM32_USART_40013800_BASE_ADDRESS
#define CONFIG_UART_STM32_USART_1_BAUD_RATE      ST_STM32_USART_40013800_CURRENT_SPEED
#define CONFIG_UART_STM32_USART_1_IRQ_PRI        ST_STM32_USART_40013800_IRQ_0_PRIORITY
#define CONFIG_UART_STM32_USART_1_NAME           ST_STM32_USART_40013800_LABEL
#define USART_1_IRQ                              ST_STM32_USART_40013800_IRQ_0

#define CONFIG_UART_STM32_USART_2_BASE_ADDRESS   ST_STM32_USART_40004400_BASE_ADDRESS
#define CONFIG_UART_STM32_USART_2_BAUD_RATE      ST_STM32_USART_40004400_CURRENT_SPEED
#define CONFIG_UART_STM32_USART_2_IRQ_PRI        ST_STM32_USART_40004400_IRQ_0_PRIORITY
#define CONFIG_UART_STM32_USART_2_NAME           ST_STM32_USART_40004400_LABEL
#define USART_2_IRQ                              ST_STM32_USART_40004400_IRQ_0

#define CONFIG_UART_STM32_USART_3_BASE_ADDRESS   ST_STM32_USART_40004800_BASE_ADDRESS
#define CONFIG_UART_STM32_USART_3_BAUD_RATE      ST_STM32_USART_40004800_CURRENT_SPEED
#define CONFIG_UART_STM32_USART_3_IRQ_PRI        ST_STM32_USART_40004800_IRQ_0_PRIORITY
#define CONFIG_UART_STM32_USART_3_NAME           ST_STM32_USART_40004800_LABEL
#define USART_3_IRQ                              ST_STM32_USART_40004800_IRQ_0

#define CONFIG_I2C_1_BASE_ADDRESS               ST_STM32_I2C_V2_40005400_BASE_ADDRESS
#define CONFIG_I2C_1_EVENT_IRQ_PRI              ST_STM32_I2C_V2_40005400_IRQ_EVENT_PRIORITY
#define CONFIG_I2C_1_ERROR_IRQ_PRI              ST_STM32_I2C_V2_40005400_IRQ_ERROR_PRIORITY
#define CONFIG_I2C_1_NAME                       ST_STM32_I2C_V2_40005400_LABEL
#define CONFIG_I2C_1_EVENT_IRQ                  ST_STM32_I2C_V2_40005400_IRQ_EVENT
#define CONFIG_I2C_1_ERROR_IRQ                  ST_STM32_I2C_V2_40005400_IRQ_ERROR
#define CONFIG_I2C_1_BITRATE                    ST_STM32_I2C_V2_40005400_CLOCK_FREQUENCY
#define CONFIG_I2C_1_CLOCK_BITS			ST_STM32_I2C_V2_40005400_CLOCK_BITS
#define CONFIG_I2C_1_CLOCK_BUS			ST_STM32_I2C_V2_40005400_CLOCK_BUS

#define CONFIG_I2C_2_BASE_ADDRESS               ST_STM32_I2C_V2_40005800_BASE_ADDRESS
#define CONFIG_I2C_2_EVENT_IRQ_PRI              ST_STM32_I2C_V2_40005800_IRQ_EVENT_PRIORITY
#define CONFIG_I2C_2_ERROR_IRQ_PRI              ST_STM32_I2C_V2_40005800_IRQ_ERROR_PRIORITY
#define CONFIG_I2C_2_NAME                       ST_STM32_I2C_V2_40005800_LABEL
#define CONFIG_I2C_2_EVENT_IRQ                  ST_STM32_I2C_V2_40005800_IRQ_EVENT
#define CONFIG_I2C_2_ERROR_IRQ                  ST_STM32_I2C_V2_40005800_IRQ_ERROR
#define CONFIG_I2C_2_BITRATE                    ST_STM32_I2C_V2_40005800_CLOCK_FREQUENCY
#define CONFIG_I2C_2_CLOCK_BITS			ST_STM32_I2C_V2_40005800_CLOCK_BITS
#define CONFIG_I2C_2_CLOCK_BUS			ST_STM32_I2C_V2_40005800_CLOCK_BUS

#define CONFIG_I2C_3_BASE_ADDRESS               ST_STM32_I2C_V2_40007800_BASE_ADDRESS
#define CONFIG_I2C_3_EVENT_IRQ_PRI              ST_STM32_I2C_V2_40007800_IRQ_EVENT_PRIORITY
#define CONFIG_I2C_3_ERROR_IRQ_PRI              ST_STM32_I2C_V2_40007800_IRQ_ERROR_PRIORITY
#define CONFIG_I2C_3_NAME                       ST_STM32_I2C_V2_40007800_LABEL
#define CONFIG_I2C_3_EVENT_IRQ                  ST_STM32_I2C_V2_40007800_IRQ_EVENT
#define CONFIG_I2C_3_ERROR_IRQ                  ST_STM32_I2C_V2_40007800_IRQ_ERROR
#define CONFIG_I2C_3_BITRATE                    ST_STM32_I2C_V2_40007800_CLOCK_FREQUENCY
#define CONFIG_I2C_3_CLOCK_BITS			ST_STM32_I2C_V2_40007800_CLOCK_BITS
#define CONFIG_I2C_3_CLOCK_BUS			ST_STM32_I2C_V2_40007800_CLOCK_BUS

#define CONFIG_SPI_1_BASE_ADDRESS		ST_STM32_SPI_FIFO_40013000_BASE_ADDRESS
#define CONFIG_SPI_1_IRQ_PRI			ST_STM32_SPI_FIFO_40013000_IRQ_0_PRIORITY
#define CONFIG_SPI_1_NAME			ST_STM32_SPI_FIFO_40013000_LABEL
#define CONFIG_SPI_1_IRQ			ST_STM32_SPI_FIFO_40013000_IRQ_0

#define CONFIG_SPI_2_BASE_ADDRESS		ST_STM32_SPI_FIFO_40003800_BASE_ADDRESS
#define CONFIG_SPI_2_IRQ_PRI			ST_STM32_SPI_FIFO_40003800_IRQ_0_PRIORITY
#define CONFIG_SPI_2_NAME			ST_STM32_SPI_FIFO_40003800_LABEL
#define CONFIG_SPI_2_IRQ			ST_STM32_SPI_FIFO_40003800_IRQ_0

#define CONFIG_SPI_3_BASE_ADDRESS		ST_STM32_SPI_FIFO_40003C00_BASE_ADDRESS
#define CONFIG_SPI_3_IRQ_PRI			ST_STM32_SPI_FIFO_40003C00_IRQ_0_PRIORITY
#define CONFIG_SPI_3_NAME			ST_STM32_SPI_FIFO_40003C00_LABEL
#define CONFIG_SPI_3_IRQ			ST_STM32_SPI_FIFO_40003C00_IRQ_0

#define CONFIG_SPI_4_BASE_ADDRESS		ST_STM32_SPI_FIFO_40013C00_BASE_ADDRESS
#define CONFIG_SPI_4_IRQ_PRI			ST_STM32_SPI_FIFO_40013C00_IRQ_0_PRIORITY
#define CONFIG_SPI_4_NAME			ST_STM32_SPI_FIFO_40013C00_LABEL
#define CONFIG_SPI_4_IRQ			ST_STM32_SPI_FIFO_40013C00_IRQ_0

#define FLASH_DEV_BASE_ADDRESS		        ST_STM32F3_FLASH_CONTROLLER_40022000_BASE_ADDRESS
#define FLASH_DEV_NAME			        ST_STM32F3_FLASH_CONTROLLER_40022000_LABEL

#define CONFIG_USB_BASE_ADDRESS			ST_STM32_USB_40005C00_BASE_ADDRESS
#define CONFIG_USB_IRQ				ST_STM32_USB_40005C00_IRQ_USB
#define CONFIG_USB_IRQ_PRI			ST_STM32_USB_40005C00_IRQ_USB_PRIORITY
#define CONFIG_USB_NUM_BIDIR_ENDPOINTS		ST_STM32_USB_40005C00_NUM_BIDIR_ENDPOINTS
#define CONFIG_USB_RAM_SIZE			ST_STM32_USB_40005C00_RAM_SIZE

#define CONFIG_PWM_STM32_1_DEV_NAME             ST_STM32_PWM_40012C00_PWM_LABEL
#define CONFIG_PWM_STM32_1_PRESCALER            ST_STM32_PWM_40012C00_PWM_ST_PRESCALER

#define CONFIG_PWM_STM32_2_DEV_NAME             ST_STM32_PWM_40000000_PWM_LABEL
#define CONFIG_PWM_STM32_2_PRESCALER            ST_STM32_PWM_40000000_PWM_ST_PRESCALER

#define CONFIG_PWM_STM32_3_DEV_NAME             ST_STM32_PWM_40000400_PWM_LABEL
#define CONFIG_PWM_STM32_3_PRESCALER            ST_STM32_PWM_40000400_PWM_ST_PRESCALER

#define CONFIG_PWM_STM32_4_DEV_NAME             ST_STM32_PWM_40000800_PWM_LABEL
#define CONFIG_PWM_STM32_4_PRESCALER            ST_STM32_PWM_40000800_PWM_ST_PRESCALER

#define CONFIG_PWM_STM32_5_DEV_NAME             ST_STM32_PWM_40000C00_PWM_LABEL
#define CONFIG_PWM_STM32_5_PRESCALER            ST_STM32_PWM_40000C00_PWM_ST_PRESCALER

#define CONFIG_PWM_STM32_6_DEV_NAME             ST_STM32_PWM_40001000_PWM_LABEL
#define CONFIG_PWM_STM32_6_PRESCALER            ST_STM32_PWM_40001000_PWM_ST_PRESCALER

#define CONFIG_PWM_STM32_7_DEV_NAME             ST_STM32_PWM_40001400_PWM_LABEL
#define CONFIG_PWM_STM32_7_PRESCALER            ST_STM32_PWM_40001400_PWM_ST_PRESCALER

#define CONFIG_PWM_STM32_8_DEV_NAME             ST_STM32_PWM_40013400_PWM_LABEL
#define CONFIG_PWM_STM32_8_PRESCALER            ST_STM32_PWM_40013400_PWM_ST_PRESCALER

#define CONFIG_PWM_STM32_12_DEV_NAME            ST_STM32_PWM_40001800_PWM_LABEL
#define CONFIG_PWM_STM32_12_PRESCALER           ST_STM32_PWM_40001800_PWM_ST_PRESCALER

#define CONFIG_PWM_STM32_13_DEV_NAME            ST_STM32_PWM_40001C00_PWM_LABEL
#define CONFIG_PWM_STM32_13_PRESCALER           ST_STM32_PWM_40001C00_PWM_ST_PRESCALER

#define CONFIG_PWM_STM32_14_DEV_NAME            ST_STM32_PWM_40002000_PWM_LABEL
#define CONFIG_PWM_STM32_14_PRESCALER           ST_STM32_PWM_40002000_PWM_ST_PRESCALER

#define CONFIG_PWM_STM32_15_DEV_NAME            ST_STM32_PWM_40014000_PWM_LABEL
#define CONFIG_PWM_STM32_15_PRESCALER           ST_STM32_PWM_40014000_PWM_ST_PRESCALER

#define CONFIG_PWM_STM32_16_DEV_NAME            ST_STM32_PWM_40014400_PWM_LABEL
#define CONFIG_PWM_STM32_16_PRESCALER           ST_STM32_PWM_40014400_PWM_ST_PRESCALER

#define CONFIG_PWM_STM32_17_DEV_NAME            ST_STM32_PWM_40014800_PWM_LABEL
#define CONFIG_PWM_STM32_17_PRESCALER           ST_STM32_PWM_40014800_PWM_ST_PRESCALER

#define CONFIG_PWM_STM32_18_DEV_NAME            ST_STM32_PWM_40009C00_PWM_LABEL
#define CONFIG_PWM_STM32_18_PRESCALER           ST_STM32_PWM_40009C00_PWM_ST_PRESCALER

#define CONFIG_PWM_STM32_19_DEV_NAME            ST_STM32_PWM_40015C00_PWM_LABEL
#define CONFIG_PWM_STM32_19_PRESCALER           ST_STM32_PWM_40015C00_PWM_ST_PRESCALER

#define CONFIG_PWM_STM32_20_DEV_NAME            ST_STM32_PWM_40015000_PWM_LABEL
#define CONFIG_PWM_STM32_20_PRESCALER           ST_STM32_PWM_40015000_PWM_ST_PRESCALER

#define CONFIG_RTC_0_BASE_ADDRESS               ST_STM32_RTC_40002800_BASE_ADDRESS
#define CONFIG_RTC_0_IRQ_PRI                    ST_STM32_RTC_40002800_IRQ_0_PRIORITY
#define CONFIG_RTC_0_IRQ                        ST_STM32_RTC_40002800_IRQ_0
#define CONFIG_RTC_0_NAME                       ST_STM32_RTC_40002800_LABEL
#define CONFIG_RTC_PRESCALER                    ST_STM32_RTC_40002800_PRESCALER
/* End of SoC Level DTS fixup file */
