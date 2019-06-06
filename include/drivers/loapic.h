/* loapic.h - public LOAPIC APIs */

/*
 * Copyright (c) 2015 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DRIVERS_LOAPIC_H_
#define ZEPHYR_INCLUDE_DRIVERS_LOAPIC_H_

#include <arch/x86/sys_io.h>
#include <arch/x86/msr.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Local APIC Register Offset */

#define LOAPIC_ID 0x020		  /* Local APIC ID Reg */
#define LOAPIC_VER 0x030	  /* Local APIC Version Reg */
#define LOAPIC_TPR 0x080	  /* Task Priority Reg */
#define LOAPIC_APR 0x090	  /* Arbitration Priority Reg */
#define LOAPIC_PPR 0x0a0	  /* Processor Priority Reg */
#define LOAPIC_EOI 0x0b0	  /* EOI Reg */
#define LOAPIC_LDR 0x0d0	  /* Logical Destination Reg */
#define LOAPIC_DFR 0x0e0	  /* Destination Format Reg */
#define LOAPIC_SVR 0x0f0	  /* Spurious Interrupt Reg */
#define LOAPIC_ISR 0x100	  /* In-service Reg */
#define LOAPIC_TMR 0x180	  /* Trigger Mode Reg */
#define LOAPIC_IRR 0x200	  /* Interrupt Request Reg */
#define LOAPIC_ESR 0x280	  /* Error Status Reg */
#define LOAPIC_ICRLO 0x300	/* Interrupt Command Reg */
#define LOAPIC_ICRHI 0x310	/* Interrupt Command Reg */
#define LOAPIC_TIMER 0x320	/* LVT (Timer) */
#define LOAPIC_THERMAL 0x330      /* LVT (Thermal) */
#define LOAPIC_PMC 0x340	  /* LVT (PMC) */
#define LOAPIC_LINT0 0x350	/* LVT (LINT0) */
#define LOAPIC_LINT1 0x360	/* LVT (LINT1) */
#define LOAPIC_ERROR 0x370	/* LVT (ERROR) */
#define LOAPIC_TIMER 0x320	/* LVT (Timer) */
#define LOAPIC_TIMER_ICR 0x380    /* Timer Initial Count Reg */
#define LOAPIC_TIMER_CCR 0x390    /* Timer Current Count Reg */
#define LOAPIC_TIMER_CONFIG 0x3e0 /* Timer Divide Config Reg */

/* Local APIC Vector Table Bits */
#define LOAPIC_LVT_MASKED 0x00010000   /* mask */

#ifndef _ASMLANGUAGE

extern void z_loapic_int_vec_set(unsigned int irq, unsigned int vector);
extern void z_loapic_irq_enable(unsigned int irq);
extern void z_loapic_irq_disable(unsigned int irq);

/**
 * @brief Read 64-bit value from the local APIC in x2APIC mode.
 *
 * @param reg the LOAPIC register number to read (LOAPIC_*)
 */
static inline u64_t x86_read_x2apic(unsigned int reg)
{
	reg >>= 4;
	return z_x86_msr_read(X86_X2APIC_BASE_MSR + reg);
}

/**
 * @brief Read 32-bit value from the local APIC in xAPIC (MMIO) mode.
 *
 * @param reg the LOAPIC register number to read (LOAPIC_*)
 */
static inline u32_t x86_read_xapic(unsigned int reg)
{
	return sys_read32(CONFIG_LOAPIC_BASE_ADDRESS + reg);
}

/**
 * @brief Read value from the local APIC using the default mode.
 *
 * Returns a 32-bit value read from the local APIC, using the access
 * method determined by CONFIG_X2APIC (either xAPIC or x2APIC). Note
 * that 64-bit reads are only allowed in x2APIC mode and can only be
 * done by calling x86_read_x2apic() directly. (This is intentional.)
 *
 * @param reg the LOAPIC register number to read (LOAPIC_*)
 */
static inline u32_t x86_read_loapic(unsigned int reg)
{
#ifdef CONFIG_X2APIC
	return x86_read_x2apic(reg);
#else
	return x86_read_xapic(reg);
#endif
}

/**
 * @brief Write 64-bit value to the local APIC in x2APIC mode.
 *
 * @param reg the LOAPIC register number to write (one of LOAPIC_*)
 * @param val 64-bit value to write
 */
static inline void x86_write_x2apic(unsigned int reg, u64_t val)
{
	reg >>= 4;
	z_x86_msr_write(X86_X2APIC_BASE_MSR + reg, val);
}

/**
 * @brief Write 32-bit value to the local APIC in xAPIC (MMIO) mode.
 *
 * @param reg the LOAPIC register number to write (one of LOAPIC_*)
 * @param val 32-bit value to write
 */
static inline void x86_write_xapic(unsigned int reg, u32_t val)
{
	sys_write32(val, CONFIG_LOAPIC_BASE_ADDRESS + reg);
}

/**
 * @brief Write 32-bit value to the local APIC using the default mode.
 *
 * Write a 32-bit value to the local APIC, using the access method
 * determined by CONFIG_X2APIC (either xAPIC or x2APIC). Note that
 * 64-bit writes are only available in x2APIC mode and can only be
 * done by calling x86_write_x2apic() directly. (This is intentional.)
 *
 * @param reg the LOAPIC register number to write (one of LOAPIC_*)
 * @param val 32-bit value to write
 */
static inline void x86_write_loapic(unsigned int reg, u32_t val)
{
#ifdef CONFIG_X2APIC
	x86_write_x2apic(reg, val);
#else
	x86_write_xapic(reg, val);
#endif
}

#if CONFIG_EOI_FORWARDING_BUG
extern void z_lakemont_eoi(void);
#endif

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_DRIVERS_LOAPIC_H_ */
