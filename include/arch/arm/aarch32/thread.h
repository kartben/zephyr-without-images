/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Per-arch thread definition
 *
 * This file contains definitions for
 *
 *  struct _thread_arch
 *  struct _callee_saved
  *
 * necessary to instantiate instances of struct k_thread.
 */

#ifndef ZEPHYR_INCLUDE_ARCH_ARM_AARCH32_THREAD_H_
#define ZEPHYR_INCLUDE_ARCH_ARM_AARCH32_THREAD_H_

#ifndef _ASMLANGUAGE
#include <zephyr/types.h>

struct _callee_saved {
	uint32_t v1;  /* r4 */
	uint32_t v2;  /* r5 */
	uint32_t v3;  /* r6 */
	uint32_t v4;  /* r7 */
	uint32_t v5;  /* r8 */
	uint32_t v6;  /* r9 */
	uint32_t v7;  /* r10 */
	uint32_t v8;  /* r11 */
	uint32_t psp; /* r13 */
};

typedef struct _callee_saved _callee_saved_t;

#if defined(CONFIG_FPU) && defined(CONFIG_FPU_SHARING)
struct _preempt_float {
	float  s16;
	float  s17;
	float  s18;
	float  s19;
	float  s20;
	float  s21;
	float  s22;
	float  s23;
	float  s24;
	float  s25;
	float  s26;
	float  s27;
	float  s28;
	float  s29;
	float  s30;
	float  s31;
};
#endif

struct _thread_arch {

	/* interrupt locking key */
	uint32_t basepri;

	/* r0 in stack frame cannot be written to reliably */
	uint32_t swap_return_value;

#if defined(CONFIG_FPU) && defined(CONFIG_FPU_SHARING)
	/*
	 * No cooperative floating point register set structure exists for
	 * the Cortex-M as it automatically saves the necessary registers
	 * in its exception stack frame.
	 */
	struct _preempt_float  preempt_float;
#endif

#if defined(CONFIG_USERSPACE) || defined(CONFIG_FPU_SHARING)
	uint32_t mode;
#if defined(CONFIG_USERSPACE)
	uint32_t priv_stack_start;
#endif
#endif
};

typedef struct _thread_arch _thread_arch_t;

#endif /* _ASMLANGUAGE */

#endif /* ZEPHYR_INCLUDE_ARCH_ARM_AARCH32_THREAD_H_ */
