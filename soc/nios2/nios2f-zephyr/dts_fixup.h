#define CONFIG_UART_NS16550_PORT_0_BAUD_RATE	DT_NS16550_F0008000_CURRENT_SPEED

#define CONFIG_UART_NS16550_PORT_0_NAME		DT_NS16550_F0008000_LABEL

#define _RAM_ADDR				CONFIG_SRAM_BASE_ADDRESS

#define _RAM_SIZE				(CONFIG_SRAM_SIZE * 1024)

#define _ROM_ADDR				CONFIG_FLASH_BASE_ADDRESS

#define _ROM_SIZE				(CONFIG_FLASH_SIZE *1024)
