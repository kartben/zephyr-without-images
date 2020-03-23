/*
 * Copyright (c) 2019 Carlo Caione <ccaione@baylibre.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief ARM64 Cortex-A interrupt management
 */

#include <kernel.h>
#include <arch/cpu.h>
#include <tracing/tracing.h>
#include <irq.h>
#include <toolchain.h>
#include <linker/sections.h>
#include <sw_isr_table.h>
#include <drivers/interrupt_controller/gic.h>

void z_arm64_fatal_error(unsigned int reason, const z_arch_esf_t *esf);

#if !defined(CONFIG_ARM_CUSTOM_INTERRUPT_CONTROLLER)
/*
 * The default interrupt controller for AArch64 is the ARM Generic Interrupt
 * Controller (GIC) and therefore the architecture interrupt control functions
 * are mapped to the GIC driver interface.
 *
 * When a custom interrupt controller is used (i.e.
 * CONFIG_ARM_CUSTOM_INTERRUPT_CONTROLLER is enabled), the architecture
 * interrupt control functions are mapped to the SoC layer in
 * `include/arch/arm/aarch64/irq.h`.
 */

void arch_irq_enable(unsigned int irq)
{
	arm_gic_irq_enable(irq);
}

void arch_irq_disable(unsigned int irq)
{
	arm_gic_irq_disable(irq);
}

int arch_irq_is_enabled(unsigned int irq)
{
	return arm_gic_irq_is_enabled(irq);
}

void z_arm64_irq_priority_set(unsigned int irq, unsigned int prio, u32_t flags)
{
	arm_gic_irq_set_priority(irq, prio, flags);
}
#endif /* !CONFIG_ARM_CUSTOM_INTERRUPT_CONTROLLER */

#ifdef CONFIG_DYNAMIC_INTERRUPTS
int arch_irq_connect_dynamic(unsigned int irq, unsigned int priority,
			     void (*routine)(void *parameter), void *parameter,
			     u32_t flags)
{
	z_isr_install(irq, routine, parameter);
	z_arm64_irq_priority_set(irq, priority, flags);
	return irq;
}
#endif

void z_irq_spurious(void *unused)
{
	ARG_UNUSED(unused);

	z_arm64_fatal_error(K_ERR_SPURIOUS_IRQ, NULL);
}
