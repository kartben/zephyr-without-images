/*
 * Copyright (c) 2017 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <toolchain.h>
#include <sections.h>
#include <sw_isr_table.h>
#include <arch/cpu.h>

#if defined(CONFIG_GEN_SW_ISR_TABLE) && defined(CONFIG_GEN_IRQ_VECTOR_TABLE)
#define ISR_WRAPPER (&_isr_wrapper)
#else
#define ISR_WRAPPER NULL
#endif

/* There is an additional member at the end populated by the linker script
 * which indicates the number of interrupts specified
 */
struct int_list_header {
	void *spurious_ptr;
	void *handler_ptr;
	u32_t table_size;
	u32_t offset;
};

/* These values are not included in the resulting binary, but instead form the
 * header of the initList section, which is used by gen_isr_tables.py to create
 * the vector and sw isr tables,
 */
_GENERIC_SECTION(.irq_info) struct int_list_header _iheader = {
	.spurious_ptr = &_irq_spurious,
	.handler_ptr = ISR_WRAPPER,
	.table_size = IRQ_TABLE_SIZE,
	.offset = CONFIG_GEN_IRQ_START_VECTOR,
};

/* These are placeholder tables. They will be replaced by the real tables
 * generated by gen_isr_tables.py.
 */

/* Some arches don't use a vector table, they have a common exception entry
 * point for all interrupts. Don't generate a table in this case.
 */
#ifdef CONFIG_GEN_IRQ_VECTOR_TABLE
u32_t __irq_vector_table _irq_vector_table[IRQ_TABLE_SIZE] = {
	[0 ...(IRQ_TABLE_SIZE - 1)] = 0xabababab,
};
#endif

/* If there are no interrupts at all, or all interrupts are of the 'direct'
 * type and bypass the _sw_isr_table, then do not generate one.
 */
#ifdef CONFIG_GEN_SW_ISR_TABLE
struct _isr_table_entry __sw_isr_table _sw_isr_table[IRQ_TABLE_SIZE] = {
	[0 ...(IRQ_TABLE_SIZE - 1)] = {(void *)0xcdcdcdcd, (void *)0xcdcdcdcd},
};
#endif

/* Linker needs this */
GEN_ABS_SYM_BEGIN(isr_tables_syms)
GEN_ABSOLUTE_SYM(__ISR_LIST_SIZEOF, sizeof(struct _isr_list));
GEN_ABS_SYM_END

