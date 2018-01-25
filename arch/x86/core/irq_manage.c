/*
 * Copyright (c) 2010-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Interrupt support for IA-32 arch
 *
 * INTERNAL
 * The _idt_base_address symbol is used to determine the base address of the IDT.
 * (It is generated by the linker script, and doesn't correspond to an actual
 * global variable.)
 */

#include <kernel.h>
#include <arch/cpu.h>
#include <kernel_structs.h>
#include <misc/__assert.h>
#include <misc/printk.h>
#include <irq.h>
#include <logging/kernel_event_logger.h>
#include <kswap.h>

extern void _SpuriousIntHandler(void *);
extern void _SpuriousIntNoErrCodeHandler(void *);

/*
 * Place the addresses of the spurious interrupt handlers into the intList
 * section. The genIdt tool can then populate any unused vectors with
 * these routines.
 */
void *__attribute__((section(".spurIsr"))) MK_ISR_NAME(_SpuriousIntHandler) =
	&_SpuriousIntHandler;
void *__attribute__((section(".spurNoErrIsr")))
	MK_ISR_NAME(_SpuriousIntNoErrCodeHandler) =
		&_SpuriousIntNoErrCodeHandler;


/* FIXME: IRQ direct inline functions have to be placed here and not in
 * arch/cpu.h as inline functions due to nasty circular dependency between
 * arch/cpu.h and kernel_structs.h; the inline functions typically need to
 * perform operations on _kernel.  For now, leave as regular functions, a
 * future iteration will resolve this.
 * We have a similar issue with the k_event_logger functions.
 *
 * See https://jira.zephyrproject.org/browse/ZEP-1595
 */

#ifdef CONFIG_SYS_POWER_MANAGEMENT
void _arch_irq_direct_pm(void)
{
	if (_kernel.idle) {
		s32_t idle_val = _kernel.idle;

		_kernel.idle = 0;
		_sys_power_save_idle_exit(idle_val);
	}
}
#endif

void _arch_isr_direct_header(void)
{
	_int_latency_start();
	_sys_k_event_logger_interrupt();
	_sys_k_event_logger_exit_sleep();

	/* We're not going to unlock IRQs, but we still need to increment this
	 * so that _is_in_isr() works
	 */
	++_kernel.nested;
}

void _arch_isr_direct_footer(int swap)
{
	_irq_controller_eoi();
	_int_latency_stop();
	--_kernel.nested;

	/* Call swap if all the following is true:
	 *
	 * 1) swap argument was enabled to this function
	 * 2) We are not in a nested interrupt
	 * 3) Current thread is preemptible
	 * 4) Next thread to run in the ready queue is not this thread
	 */
	if (swap && !_kernel.nested &&
	    _current->base.preempt < _NON_PREEMPT_THRESHOLD &&
	    _kernel.ready_q.cache != _current) {
		unsigned int flags;

		/* Fetch EFLAGS argument to _Swap() */
		__asm__ volatile (
			"pushfl\n\t"
			"popl %0\n\t"
			: "=g" (flags)
			:
			: "memory"
			);
		_Swap(flags);
	}
}

