/*
 * Copyright (c) 1997-1998, 2000-2002, 2004, 2006-2008, 2011-2015 Wind River
 * Systems, Inc.
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
 * @brief Intel IO APIC/xAPIC driver
 *
 * This module is a driver for the IO APIC/xAPIC (Advanced Programmable
 * Interrupt Controller) for P6 (PentiumPro, II, III) family processors
 * and P7 (Pentium4) family processors.  The IO APIC/xAPIC is included
 * in the Intel's system chip set, such as ICH2.  Software intervention
 * may be required to enable the IO APIC/xAPIC in some chip sets.
 * The 8259A interrupt controller is intended for use in a uni-processor
 * system, IO APIC can be used in either a uni-processor or multi-processor
 * system.  The IO APIC handles interrupts very differently than the 8259A.
 * Briefly, these differences are:
 *  - Method of Interrupt Transmission. The IO APIC transmits interrupts
 *    through a 3-wire bus and interrupts are handled without the need for
 *    the processor to run an interrupt acknowledge cycle.
 *  - Interrupt Priority. The priority of interrupts in the IO APIC is
 *    independent of the interrupt number.  For example, interrupt 10 can
 *    be given a higher priority than interrupt 3.
 *  - More Interrupts. The IO APIC supports a total of 24 interrupts.
 *
 * The IO APIC unit consists of a set of interrupt input signals, a 24-entry
 * by 64-bit Interrupt Redirection Table, programmable registers, and a message
 * unit for sending and receiving APIC messages over the APIC bus or the
 * Front-Side (system) bus.  IO devices inject interrupts into the system by
 * asserting one of the interrupt lines to the IO APIC.  The IO APIC selects the
 * corresponding entry in the Redirection Table and uses the information in that
 * entry to format an interrupt request message.  Each entry in the Redirection
 * Table can be individually programmed to indicate edge/level sensitive interrupt
 * signals, the interrupt vector and priority, the destination processor, and how
 * the processor is selected (statically and dynamically).  The information in
 * the table is used to transmit a message to other APIC units (via the APIC bus
 * or the Front-Side (system) bus).  IO APIC is used in the Symmetric IO Mode.
 * The base address of IO APIC is determined in loapic_init() and stored in the
 * global variable ioApicBase and ioApicData.
 * The lower 32 bit value of the redirection table entries for IRQ 0
 * to 15 are edge triggered positive high, and for IRQ 16 to 23 are level
 * triggered positive low.
 *
 * This implementation doesn't support multiple IO APICs.
 *
 * INCLUDE FILES: ioapic.h loapic.h
 *
 */

#include <nanokernel.h>
#include <arch/cpu.h>

#include "board.h"

#include <toolchain.h>
#include <sections.h>
#include <init.h>

#include <drivers/ioapic.h> /* public API declarations */
#include <drivers/loapic.h> /* public API declarations and registers */
#include "ioapic_priv.h"

static uint32_t __IoApicGet(int32_t offset);
static void __IoApicSet(int32_t offset, uint32_t value);
static void ioApicRedSetHi(unsigned int irq, uint32_t upper32);
static void ioApicRedSetLo(unsigned int irq, uint32_t lower32);
static uint32_t ioApicRedGetLo(unsigned int irq);
static void _IoApicRedUpdateLo(unsigned int irq, uint32_t value,
					uint32_t mask);

/*
 * The functions irq_enable() and irq_disable() are implemented in the
 * interrupt controller driver due to the IRQ virtualization imposed by
 * the x86 architecture.
 */

/**
 *
 * @brief Initialize the IO APIC or xAPIC
 *
 * This routine initializes the IO APIC or xAPIC.
 *
 * @return N/A
 */
int _ioapic_init(struct device *unused)
{
	ARG_UNUSED(unused);
	int32_t ix;	/* redirection table index */
	uint32_t rteValue; /* value to copy into redirection table entry */

	/*
	 * The platform must set the Kconfig option IOAPIC_NUM_RTES to indicate
	 * the number of redirection table entries supported by the IOAPIC.
	 *
	 * Note: The number of actual IRQs supported by the IOAPIC can be
	 * determined at runtime by computing:
	 *
	 * ((__IoApicGet(IOAPIC_VERS) & IOAPIC_MRE_MASK) >> 16) + 1
	 */

	/*
	 * Initialize the redirection table entries with default settings;
	 * actual interrupt vectors are specified during irq_connect_dynamic().
	 *
	 * A future enhancement should make this initialization "table driven":
	 * use data provided by the platform to specify the initial state
	 */

	rteValue = IOAPIC_EDGE | IOAPIC_HIGH | IOAPIC_FIXED | IOAPIC_INT_MASK |
		   IOAPIC_PHYSICAL | 0 /* dummy vector */;

	for (ix = 0; ix < CONFIG_IOAPIC_NUM_RTES; ix++) {
		ioApicRedSetHi(ix, 0);
		ioApicRedSetLo(ix, rteValue);
	}
	return 0;
}

/**
 *
 * @brief Enable a specified APIC interrupt input line
 *
 * This routine enables a specified APIC interrupt input line.
 * @param irq IRQ number to enable
 *
 * @return N/A
 */
void _ioapic_irq_enable(unsigned int irq)
{
	_IoApicRedUpdateLo(irq, 0, IOAPIC_INT_MASK);
}

/**
 *
 * @brief Disable a specified APIC interrupt input line
 *
 * This routine disables a specified APIC interrupt input line.
 * @param irq IRQ number to disable
 *
 * @return N/A
 */
void _ioapic_irq_disable(unsigned int irq)
{
	_IoApicRedUpdateLo(irq, IOAPIC_INT_MASK, IOAPIC_INT_MASK);
}

/**
 *
 * @brief Programs the interrupt redirection table
 *
 * This routine sets up the redirection table entry for the specified IRQ
 * @param irq Virtualized IRQ
 * @param vector Vector number
 * @param flags Interrupt flags
 *
 * @return N/A
 */
void _ioapic_irq_set(unsigned int irq, unsigned int vector, uint32_t flags)
{
	uint32_t rteValue;   /* value to copy into redirection table entry */

	rteValue = IOAPIC_FIXED | IOAPIC_INT_MASK | IOAPIC_PHYSICAL |
		   (vector & IOAPIC_VEC_MASK) | flags;
	ioApicRedSetHi(irq, 0);
	ioApicRedSetLo(irq, rteValue);
}

/**
 *
 * @brief Program interrupt vector for specified irq
 *
 * The routine writes the interrupt vector in the Interrupt Redirection
 * Table for specified irq number
 *
 * @param irq Interrupt number
 * @param vector Vector number
 * @return N/A
 */
void _ioapic_int_vec_set(unsigned int irq, unsigned int vector)
{
	_IoApicRedUpdateLo(irq, vector, IOAPIC_VEC_MASK);
}

/**
 *
 * @brief Read a 32 bit IO APIC register
 *
 * This routine reads the specified IO APIC register using indirect addressing.
 * @param offset Register offset (8 bits)
 *
 * @return register value
 */
static uint32_t __IoApicGet(int32_t offset)
{
	uint32_t value; /* value */
	int key;	/* interrupt lock level */

	/* lock interrupts to ensure indirect addressing works "atomically" */

	key = irq_lock();

	*((volatile char *)
		(CONFIG_IOAPIC_BASE_ADDRESS + IOAPIC_IND)) = (char)offset;
	value = *((volatile uint32_t *)(CONFIG_IOAPIC_BASE_ADDRESS + IOAPIC_DATA));

	irq_unlock(key);

	return value;
}

/**
 *
 * @brief Write a 32 bit IO APIC register
 *
 * This routine writes the specified IO APIC register using indirect addressing.
 *
 * @param offset Register offset (8 bits)
 * @param value Value to set the register
 * @return N/A
 */
static void __IoApicSet(int32_t offset, uint32_t value)
{
	int key; /* interrupt lock level */

	/* lock interrupts to ensure indirect addressing works "atomically" */

	key = irq_lock();

	*(volatile char *)(CONFIG_IOAPIC_BASE_ADDRESS + IOAPIC_IND) = (char)offset;
	*((volatile uint32_t *)(CONFIG_IOAPIC_BASE_ADDRESS + IOAPIC_DATA)) = value;

	irq_unlock(key);
}

/**
 *
 * @brief Get low 32 bits of Redirection Table entry
 *
 * This routine reads the low-order 32 bits of a Redirection Table entry.
 *
 * @param irq INTIN number
 * @return 32 low-order bits
 */
static uint32_t ioApicRedGetLo(unsigned int irq)
{
	int32_t offset = IOAPIC_REDTBL + (irq << 1); /* register offset */

	return __IoApicGet(offset);
}

/**
 *
 * @brief Set low 32 bits of Redirection Table entry
 *
 * This routine writes the low-order 32 bits of a Redirection Table entry.
 *
 * @param irq INTIN number
 * @param lower32 Value to be written
 * @return N/A
 */
static void ioApicRedSetLo(unsigned int irq, uint32_t lower32)
{
	int32_t offset = IOAPIC_REDTBL + (irq << 1); /* register offset */

	__IoApicSet(offset, lower32);
}

/**
 *
 * @brief Set high 32 bits of Redirection Table entry
 *
 * This routine writes the high-order 32 bits of a Redirection Table entry.
 *
 * @param irq INTIN number
 * @param upper32 Value to be written
 * @return N/A
 */
static void ioApicRedSetHi(unsigned int irq, uint32_t upper32)
{
	int32_t offset = IOAPIC_REDTBL + (irq << 1) + 1; /* register offset */

	__IoApicSet(offset, upper32);
}

/**
 *
 * @brief Modify low 32 bits of Redirection Table entry
 *
 * This routine modifies selected portions of the low-order 32 bits of a
 * Redirection Table entry, as indicated by the associate bit mask.
 *
 * @param irq INTIN number
 * @param value Value to be written
 * @param mask  Mask of bits to be modified
 * @return N/A
 */
static void _IoApicRedUpdateLo(unsigned int irq,
				uint32_t value,
				uint32_t mask)
{
	ioApicRedSetLo(irq, (ioApicRedGetLo(irq) & ~mask) | (value & mask));
}

DEVICE_INIT_CONFIG_DEFINE(ioapic_0, "", _ioapic_init, NULL);
SYS_DEFINE_DEVICE(ioapic_0, NULL, PRIMARY,
		  CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
