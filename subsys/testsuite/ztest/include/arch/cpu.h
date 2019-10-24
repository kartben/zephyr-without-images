/*
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef ZEPHYR_SUBSYS_TESTSUITE_ZTEST_INCLUDE_ARCH_CPU_H
#define ZEPHYR_SUBSYS_TESTSUITE_ZTEST_INCLUDE_ARCH_CPU_H

/* This file exists as a hack around Zephyr's dependencies */

/* Architecture thread structure */
struct _callee_saved {
};

typedef struct _callee_saved _callee_saved_t;

struct _thread_arch {
};

typedef struct _thread_arch _thread_arch_t;

/* Architecture functions */
static inline u32_t z_arch_k_cycle_get_32(void)
{
	return 0;
}

static ALWAYS_INLINE unsigned int z_arch_irq_lock(void)
{
	return 0;
}

static inline void z_arch_irq_unlock(unsigned int key)
{
	ARG_UNUSED(key);
}

static inline bool z_arch_irq_unlocked(unsigned int key)
{
	return 0;
}

#include <sys/arch_interface.h>


#endif /* ZEPHYR_SUBSYS_TESTSUITE_ZTEST_INCLUDE_ARCH_CPU_H */
