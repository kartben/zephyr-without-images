/*
 * Copyright (c) 2013-2015, Wind River Systems, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file
 * @brief Board configuration macros for the Quark X1000 SoC
 *
 * This header file is used to specify and describe SoC-level aspects for
 * the Quark X1000 SoC.
 */

#ifndef __SOC_H_
#define __SOC_H_

#include <misc/util.h>

#ifndef _ASMLANGUAGE
#include <device.h>
#include <drivers/rand32.h>
#endif

#ifdef CONFIG_IOAPIC
#include <drivers/ioapic.h>
#endif

/*
 * GPIO
 */
#define GPIO_SCH_LEGACY_IO_PORTS_ACCESS

#define GPIO_SCH_0_BASE_ADDR			0x1080
#define GPIO_SCH_0_BITS				2

#define GPIO_SCH_1_BASE_ADDR			0x10A0
#define GPIO_SCH_1_BITS				6

#define GPIO_DW_PCI_VENDOR_ID			0x8086
#define GPIO_DW_PCI_DEVICE_ID			0x0934
#define GPIO_DW_PCI_CLASS			0x0C

#define GPIO_DW_0_BASE_ADDR			0x90006000
#define GPIO_DW_0_IRQ				18
#define GPIO_DW_0_BITS				8

#define GPIO_DW_0_PCI_BUS			0
#define GPIO_DW_0_PCI_DEV			21
#define GPIO_DW_0_PCI_FUNCTION			2
#define GPIO_DW_0_PCI_BAR			1

#if defined(CONFIG_IOAPIC)
#define GPIO_DW_0_IRQ_FLAGS			(IOAPIC_LEVEL | IOAPIC_LOW)
#endif

/*
 * I2C
 */
#define I2C_DW_PCI_VENDOR_ID			0x8086
#define I2C_DW_PCI_DEVICE_ID			0x0934
#define I2C_DW_PCI_CLASS			0x0C

#define I2C_DW_0_BASE_ADDR			0x90007000
#define I2C_DW_0_IRQ				18

#define I2C_DW_0_PCI_BUS			0
#define I2C_DW_0_PCI_DEV			21
#define I2C_DW_0_PCI_FUNCTION			2
#define I2C_DW_0_PCI_BAR			0

#if defined(CONFIG_IOAPIC)
#define I2C_DW_IRQ_FLAGS			(IOAPIC_LEVEL | IOAPIC_LOW)
#endif

/*
 * UART
 */
#define UART_NS16550_PORT_0_BASE_ADDR		0x9000f000
#define UART_NS16550_PORT_0_IRQ			0
#define UART_NS16550_PORT_0_CLK_FREQ		44236800

#define UART_NS16550_PORT_0_PCI_CLASS		0x07
#define UART_NS16550_PORT_0_PCI_BUS		0
#define UART_NS16550_PORT_0_PCI_DEV		20
#define UART_NS16550_PORT_0_PCI_VENDOR_ID	0x8086
#define UART_NS16550_PORT_0_PCI_DEVICE_ID	0x0936
#define UART_NS16550_PORT_0_PCI_FUNC		1
#define UART_NS16550_PORT_0_PCI_BAR		0

#define UART_NS16550_PORT_1_BASE_ADDR		0x9000b000
#define UART_NS16550_PORT_1_IRQ			17
#define UART_NS16550_PORT_1_CLK_FREQ		44236800

#define UART_NS16550_PORT_1_PCI_CLASS		0x07
#define UART_NS16550_PORT_1_PCI_BUS		0
#define UART_NS16550_PORT_1_PCI_DEV		20
#define UART_NS16550_PORT_1_PCI_VENDOR_ID	0x8086
#define UART_NS16550_PORT_1_PCI_DEVICE_ID	0x0936
#define UART_NS16550_PORT_1_PCI_FUNC		5
#define UART_NS16550_PORT_1_PCI_BAR		0

#ifdef CONFIG_IOAPIC
#define UART_IRQ_FLAGS				(IOAPIC_LEVEL | IOAPIC_LOW)
#endif /* CONFIG_IOAPIC */


#ifdef __cplusplus
extern "C" {
#endif

#define NUM_STD_IRQS 16   /* number of "standard" IRQs on an x86 platform */
#define INT_VEC_IRQ0 0x20 /* Vector number for IRQ0 */

/*
 * The IRQ_CONNECT() API connects to a (virtualized) IRQ and the
 * associated interrupt controller is programmed with the allocated vector.
 * The Quark board virtualizes IRQs as follows:
 *
 *   - The first CONFIG_IOAPIC_NUM_RTES IRQs are provided by the IOAPIC
 *   - The remaining IRQs are provided by the LOAPIC.
 *
 * Thus, for example, if the IOAPIC supports 24 IRQs:
 *
 *   - IRQ0 to IRQ23   map to IOAPIC IRQ0 to IRQ23
 *   - IRQ24 to IRQ29  map to LOAPIC LVT entries as follows:
 *
 *       IRQ24 -> LOAPIC_TIMER
 *       IRQ25 -> LOAPIC_THERMAL
 *       IRQ26 -> LOAPIC_PMC
 *       IRQ27 -> LOAPIC_LINT0
 *       IRQ28 -> LOAPIC_LINT1
 *       IRQ29 -> LOAPIC_ERROR
 */

/* PCI definitions */
#define PCI_BUS_NUMBERS 2

#define PCI_CTRL_ADDR_REG 0xCF8
#define PCI_CTRL_DATA_REG 0xCFC

#define PCI_INTA 1
#define PCI_INTB 2
#define PCI_INTC 3
#define PCI_INTD 4


/**
 *
 * @brief Convert PCI interrupt PIN to IRQ
 *
 * The routine uses "standard design consideration" and implies that
 * INTA (pin 1) -> IRQ 16
 * INTB (pin 2) -> IRQ 17
 * INTC (pin 3) -> IRQ 18
 * INTD (pin 4) -> IRQ 19
 *
 * In case a mini-PCIe card is used, the IRQs are swizzled:
 * INTA (pin 1) -> IRQ 17
 * INTB (pin 2) -> IRQ 18
 * INTC (pin 3) -> IRQ 19
 * INTD (pin 4) -> IRQ 16
 *
 * @return IRQ number, -1 if the result is incorrect
 *
 */

static inline int pci_pin2irq(int bus, int dev, int pin)
{
	if (bus < 0 || bus > 1) {
		return -1;
	}
	if ((pin < PCI_INTA) || (pin > PCI_INTD)) {
		return -1;
	}
	return NUM_STD_IRQS + ((pin - 1 + bus) & 3);
}

#ifdef __cplusplus
}
#endif

#endif /* __SOC_H_ */
