/*
 * Copyright (c) 2019 Microchip Technology Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* This file is a temporary workaround for mapping of the generated information
 * to the current driver definitions.  This will be removed when the drivers
 * are modified to handle the generated information, or the mapping of
 * generated data matches the driver definitions.
 */


#define DT_NUM_IRQ_PRIO_BITS \
	DT_ARM_V7M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS
#if defined(DT_NS16550_400F2400_REG_SHIFT)
#define DT_NS16550_REG_SHIFT DT_NS16550_400F2400_REG_SHIFT
#elif defined(DT_NS16550_400F2800_REG_SHIFT)
#define DT_NS16550_REG_SHIFT DT_NS16550_400F2800_REG_SHIFT
#elif defined(DT_NS16550_400F2C00_REG_SHIFT)
#define DT_NS16550_REG_SHIFT DT_NS16550_400F2C00_REG_SHIFT
#endif

#define DT_UART_NS16550_PORT_0_BASE_ADDR \
	DT_NS16550_400F2400_BASE_ADDRESS
#define DT_UART_NS16550_PORT_0_CLK_FREQ		1843200
#define DT_UART_NS16550_PORT_0_NAME		DT_NS16550_400F2400_LABEL
#define DT_UART_NS16550_PORT_0_BAUD_RATE \
	DT_NS16550_400F2400_CURRENT_SPEED
#define DT_UART_NS16550_PORT_0_IRQ		DT_NS16550_400F2400_IRQ_0
#define DT_UART_NS16550_PORT_0_IRQ_PRI		DT_NS16550_400F2400_IRQ_0_PRIORITY
#define DT_UART_NS16550_PORT_0_IRQ_FLAGS	0 /* Deault */

#define DT_UART_NS16550_PORT_1_BASE_ADDR \
	DT_NS16550_400F2800_BASE_ADDRESS
#define DT_UART_NS16550_PORT_1_CLK_FREQ		1843200
#define DT_UART_NS16550_PORT_1_NAME		DT_NS16550_400F2800_LABEL
#define DT_UART_NS16550_PORT_1_BAUD_RATE \
	DT_NS16550_400F2800_CURRENT_SPEED
#define DT_UART_NS16550_PORT_1_IRQ		DT_NS16550_400F2800_IRQ_0
#define DT_UART_NS16550_PORT_1_IRQ_PRI		DT_NS16550_400F2800_IRQ_0_PRIORITY
#define DT_UART_NS16550_PORT_1_IRQ_FLAGS	0 /* Default */

#define DT_UART_NS16550_PORT_2_BASE_ADDR \
	DT_NS16550_400F2C00_BASE_ADDRESS
#define DT_UART_NS16550_PORT_2_CLK_FREQ		1843200
#define DT_UART_NS16550_PORT_2_NAME		DT_NS16550_400F2C00_LABEL
#define DT_UART_NS16550_PORT_2_BAUD_RATE \
	DT_NS16550_400F2C00_CURRENT_SPEED
#define DT_UART_NS16550_PORT_2_IRQ		DT_NS16550_400F2C00_IRQ_0
#define DT_UART_NS16550_PORT_2_IRQ_PRI		DT_NS16550_400F2C00_IRQ_0_PRIORITY
#define DT_UART_NS16550_PORT_2_IRQ_FLAGS	0 /* Default */

/* Pin multiplexing and GPIOs share the same registers in the HW */
#define DT_PINMUX_XEC_GPIO000_036_BASE_ADDR	DT_GPIO_XEC_GPIO000_036_BASE_ADDR
#define DT_PINMUX_XEC_GPIO040_076_BASE_ADDR	DT_GPIO_XEC_GPIO040_076_BASE_ADDR
#define DT_PINMUX_XEC_GPIO100_136_BASE_ADDR	DT_GPIO_XEC_GPIO100_136_BASE_ADDR
#define DT_PINMUX_XEC_GPIO140_176_BASE_ADDR	DT_GPIO_XEC_GPIO140_176_BASE_ADDR
#define DT_PINMUX_XEC_GPIO200_236_BASE_ADDR	DT_GPIO_XEC_GPIO200_236_BASE_ADDR
#define DT_PINMUX_XEC_GPIO240_276_BASE_ADDR	DT_GPIO_XEC_GPIO240_276_BASE_ADDR

#define DT_GPIO_XEC_GPIO000_036_BASE_ADDR	DT_MICROCHIP_XEC_GPIO_40081000_BASE_ADDRESS
#define DT_GPIO_XEC_GPIO000_036_IRQ		DT_MICROCHIP_XEC_GPIO_40081000_IRQ_0
#define DT_GPIO_XEC_GPIO000_036_IRQ_PRIORITY	DT_MICROCHIP_XEC_GPIO_40081000_IRQ_0_PRIORITY
#define DT_GPIO_XEC_GPIO000_036_LABEL		DT_MICROCHIP_XEC_GPIO_40081000_LABEL
#define DT_GPIO_XEC_GPIO000_036_SIZE		DT_MICROCHIP_XEC_GPIO_40081000_SIZE

#define DT_GPIO_XEC_GPIO040_076_BASE_ADDR	DT_MICROCHIP_XEC_GPIO_40081080_BASE_ADDRESS
#define DT_GPIO_XEC_GPIO040_076_IRQ		DT_MICROCHIP_XEC_GPIO_40081080_IRQ_0
#define DT_GPIO_XEC_GPIO040_076_IRQ_PRIORITY	DT_MICROCHIP_XEC_GPIO_40081080_IRQ_0_PRIORITY
#define DT_GPIO_XEC_GPIO040_076_LABEL		DT_MICROCHIP_XEC_GPIO_40081080_LABEL
#define DT_GPIO_XEC_GPIO040_076_SIZE		DT_MICROCHIP_XEC_GPIO_40081080_SIZE

#define DT_GPIO_XEC_GPIO100_136_BASE_ADDR	DT_MICROCHIP_XEC_GPIO_40081100_BASE_ADDRESS
#define DT_GPIO_XEC_GPIO100_136_IRQ		DT_MICROCHIP_XEC_GPIO_40081100_IRQ_0
#define DT_GPIO_XEC_GPIO100_136_IRQ_PRIORITY	DT_MICROCHIP_XEC_GPIO_40081100_IRQ_0_PRIORITY
#define DT_GPIO_XEC_GPIO100_136_LABEL		DT_MICROCHIP_XEC_GPIO_40081100_LABEL
#define DT_GPIO_XEC_GPIO100_136_SIZE		DT_MICROCHIP_XEC_GPIO_40081100_SIZE

#define DT_GPIO_XEC_GPIO140_176_BASE_ADDR	DT_MICROCHIP_XEC_GPIO_40081180_BASE_ADDRESS
#define DT_GPIO_XEC_GPIO140_176_IRQ		DT_MICROCHIP_XEC_GPIO_40081180_IRQ_0
#define DT_GPIO_XEC_GPIO140_176_IRQ_PRIORITY	DT_MICROCHIP_XEC_GPIO_40081180_IRQ_0_PRIORITY
#define DT_GPIO_XEC_GPIO140_176_LABEL		DT_MICROCHIP_XEC_GPIO_40081180_LABEL
#define DT_GPIO_XEC_GPIO140_176_SIZE		DT_MICROCHIP_XEC_GPIO_40081180_SIZE

#define DT_GPIO_XEC_GPIO200_236_BASE_ADDR	DT_MICROCHIP_XEC_GPIO_40081200_BASE_ADDRESS
#define DT_GPIO_XEC_GPIO200_236_IRQ		DT_MICROCHIP_XEC_GPIO_40081200_IRQ_0
#define DT_GPIO_XEC_GPIO200_236_IRQ_PRIORITY	DT_MICROCHIP_XEC_GPIO_40081200_IRQ_0_PRIORITY
#define DT_GPIO_XEC_GPIO200_236_LABEL		DT_MICROCHIP_XEC_GPIO_40081200_LABEL
#define DT_GPIO_XEC_GPIO200_236_SIZE		DT_MICROCHIP_XEC_GPIO_40081200_SIZE

#define DT_GPIO_XEC_GPIO240_276_BASE_ADDR	DT_MICROCHIP_XEC_GPIO_40081280_BASE_ADDRESS
#define DT_GPIO_XEC_GPIO240_276_IRQ		DT_MICROCHIP_XEC_GPIO_40081280_IRQ_0
#define DT_GPIO_XEC_GPIO240_276_IRQ_PRIORITY	DT_MICROCHIP_XEC_GPIO_40081280_IRQ_0_PRIORITY
#define DT_GPIO_XEC_GPIO240_276_LABEL		DT_MICROCHIP_XEC_GPIO_40081280_LABEL
#define DT_GPIO_XEC_GPIO240_276_SIZE		DT_MICROCHIP_XEC_GPIO_40081280_SIZE

#ifdef DT_MICROCHIP_XEC_TIMER_40000C00_BASE_ADDRESS

#define DT_COUNTER_MCHP_XEC_0			1
#define DT_COUNTER_MCHP_XEC_0_BASE_ADDR		DT_MICROCHIP_XEC_TIMER_40000C00_BASE_ADDRESS
#define DT_COUNTER_MCHP_XEC_0_IRQ		DT_MICROCHIP_XEC_TIMER_40000C00_IRQ_0
#define DT_COUNTER_MCHP_XEC_0_IRQ_PRIORITY	DT_MICROCHIP_XEC_TIMER_40000C00_IRQ_0_PRIORITY
#define DT_COUNTEX_MCHP_XEC_0_MAX_VALUE		DT_MICROCHIP_XEC_TIMER_40000C00_MAX_VALUE_0
#define DT_COUNTER_MCHP_XEC_0_CLOCK_FREQUENCY	DT_MICROCHIP_XEC_TIMER_40000C00_CLOCK_FREQUENCY
#define DT_COUNTER_MCHP_XEC_0_PRESCALER		DT_MICROCHIP_XEC_TIMER_40000C00_PRESCALER
#define DT_COUNTER_MCHP_XEC_0_LABEL		DT_MICROCHIP_XEC_TIMER_40000C00_LABEL

#endif /* DT_MICROCHIP_XEC_TIMER_40000C00_BASE_ADDRESS */

#ifdef DT_MICROCHIP_XEC_TIMER_40000C20_BASE_ADDRESS

#define DT_COUNTER_MCHP_XEC_1			1
#define DT_COUNTER_MCHP_XEC_1_BASE_ADDR		DT_MICROCHIP_XEC_TIMER_40000C20_BASE_ADDRESS
#define DT_COUNTER_MCHP_XEC_1_IRQ		DT_MICROCHIP_XEC_TIMER_40000C20_IRQ_0
#define DT_COUNTER_MCHP_XEC_1_IRQ_PRIORITY	DT_MICROCHIP_XEC_TIMER_40000C20_IRQ_0_PRIORITY
#define DT_COUNTEX_MCHP_XEC_1_MAX_VALUE		DT_MICROCHIP_XEC_TIMER_40000C20_MAX_VALUE_0
#define DT_COUNTER_MCHP_XEC_1_CLOCK_FREQUENCY	DT_MICROCHIP_XEC_TIMER_40000C20_CLOCK_FREQUENCY
#define DT_COUNTER_MCHP_XEC_1_PRESCALER		DT_MICROCHIP_XEC_TIMER_40000C20_PRESCALER
#define DT_COUNTER_MCHP_XEC_1_LABEL		DT_MICROCHIP_XEC_TIMER_40000C20_LABEL

#endif /* DT_MICROCHIP_XEC_TIMER_40000C20_BASE_ADDRESS */

#ifdef DT_MICROCHIP_XEC_TIMER_40000CA0_BASE_ADDRESS

#define DT_COUNTER_MCHP_XEC_3			1
#define DT_COUNTER_MCHP_XEC_3_BASE_ADDR		DT_MICROCHIP_XEC_TIMER_40000CA0_BASE_ADDRESS
#define DT_COUNTER_MCHP_XEC_3_IRQ		DT_MICROCHIP_XEC_TIMER_40000CA0_IRQ_0
#define DT_COUNTER_MCHP_XEC_3_IRQ_PRIORITY	DT_MICROCHIP_XEC_TIMER_40000CA0_IRQ_0_PRIORITY
#define DT_COUNTEX_MCHP_XEC_3_MAX_VALUE		DT_MICROCHIP_XEC_TIMER_40000CA0_MAX_VALUE_0
#define DT_COUNTER_MCHP_XEC_3_CLOCK_FREQUENCY	DT_MICROCHIP_XEC_TIMER_40000CA0_CLOCK_FREQUENCY
#define DT_COUNTER_MCHP_XEC_3_PRESCALER		DT_MICROCHIP_XEC_TIMER_40000CA0_PRESCALER
#define DT_COUNTER_MCHP_XEC_3_LABEL		DT_MICROCHIP_XEC_TIMER_40000CA0_LABEL

#endif /* DT_MICROCHIP_XEC_TIMER_40000CA0_BASE_ADDRESS */

#define DT_RTC_0_NAME				DT_MICROCHIP_XEC_TIMER_40000CA0_LABEL

#define DT_WDT_0_NAME				DT_INST_0_MICROCHIP_XEC_WATCHDOG_LABEL

#define DT_PS2_XEC_0_BASE_ADDR			DT_MICROCHIP_XEC_PS2_40009000_BASE_ADDRESS
#define DT_PS2_XEC_0_IRQ			DT_MICROCHIP_XEC_PS2_40009000_IRQ_0
#define DT_PS2_XEC_0_IRQ_PRIORITY		DT_MICROCHIP_XEC_PS2_40009000_IRQ_0_PRIORITY
#define DT_PS2_XEC_0_LABEL			DT_MICROCHIP_XEC_PS2_40009000_LABEL
#define DT_PS2_XEC_0_SIZE			DT_MICROCHIP_XEC_PS2_40009000_SIZE

#define DT_PS2_XEC_1_BASE_ADDR			DT_MICROCHIP_XEC_PS2_40009040_BASE_ADDRESS
#define DT_PS2_XEC_1_IRQ			DT_MICROCHIP_XEC_PS2_40009040_IRQ_0
#define DT_PS2_XEC_1_IRQ_PRIORITY		DT_MICROCHIP_XEC_PS2_40009040_IRQ_0_PRIORITY
#define DT_PS2_XEC_1_LABEL			DT_MICROCHIP_XEC_PS2_40009040_LABEL
#define DT_PS2_XEC_1_SIZE			DT_MICROCHIP_XEC_PS2_40009040_SIZE

