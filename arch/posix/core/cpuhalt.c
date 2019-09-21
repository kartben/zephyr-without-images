/*
 * Copyright (c) 2011-2015 Wind River Systems, Inc.
 * Copyright (c) 2017 Oticon A/S
 *
 * SPDX-License-Identifier: Apache-2.0
 */
/**
 * @file  CPU power management code for POSIX
 *
 * This module provides:
 *
 * An implementation of the architecture-specific
 * z_arch_cpu_idle() primitive required by the kernel idle loop component.
 * It can be called within an implementation of _sys_power_save_idle(),
 * which is provided for the kernel by the platform.
 *
 * An implementation of z_arch_cpu_atomic_idle(), which
 * atomically re-enables interrupts and enters low power mode.
 *
 * A weak stub for sys_arch_reboot(), which does nothing
 */

#include "posix_core.h"
#include "posix_soc_if.h"
#include <debug/tracing.h>

/**
 *
 * @brief Power save idle routine for IA-32
 *
 * This function will be called by the kernel idle loop or possibly within
 * an implementation of _sys_power_save_idle in the kernel when the
 * '_sys_power_save_flag' variable is non-zero.
 *
 * This function is just a pass thru to the SOC one
 *
 * @return N/A
 */
void z_arch_cpu_idle(void)
{
	sys_trace_idle();
	posix_irq_full_unlock();
	posix_halt_cpu();
}

/**
 *
 * @brief Atomically re-enable interrupts and enter low power mode
 *
 * INTERNAL
 * The requirements for z_arch_cpu_atomic_idle() are as follows:
 * 1) The enablement of interrupts and entering a low-power mode needs to be
 *    atomic, i.e. there should be no period of time where interrupts are
 *    enabled before the processor enters a low-power mode.  See the comments
 *    in k_lifo_get(), for example, of the race condition that
 *    occurs if this requirement is not met.
 *
 * 2) After waking up from the low-power mode, the interrupt lockout state
 *    must be restored as indicated in the 'key' input parameter.
 *
 * This function is just a pass thru to the SOC one
 *
 * @return N/A
 */
void z_arch_cpu_atomic_idle(unsigned int key)
{
	sys_trace_idle();
	posix_atomic_halt_cpu(key);
}

#if defined(CONFIG_REBOOT)
/**
 *
 * @brief Stub for sys_arch_reboot
 *
 * Does nothing
 *
 * @return N/A
 */
void __weak sys_arch_reboot(int type)
{
	ARG_UNUSED(type);
}
#endif /* CONFIG_REBOOT */
