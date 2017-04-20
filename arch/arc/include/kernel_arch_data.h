/*
 * Copyright (c) 2014-2016 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Private kernel definitions
 *
 * This file contains private kernel structures definitions and various
 * other definitions for the ARCv2 processor architecture.
 *
 * This file is also included by assembly language files which must #define
 * _ASMLANGUAGE before including this header file.  Note that kernel
 * assembly source files obtains structure offset values via "absolute
 * symbols" in the offsets.o module.
 */

#ifndef _kernel_arch_data__h_
#define _kernel_arch_data__h_

#ifdef __cplusplus
extern "C" {
#endif

#include <toolchain.h>
#include <sections.h>
#include <arch/cpu.h>
#include <vector_table.h>

#ifndef _ASMLANGUAGE
#include <kernel.h>
#include <nano_internal.h>
#include <zephyr/types.h>
#include <misc/util.h>
#include <misc/dlist.h>
#endif

#ifndef _ASMLANGUAGE

struct _caller_saved {
	/*
	 * Saved on the stack as part of handling a regular IRQ or by the
	 * kernel when calling the FIRQ return code.
	 */
};

typedef struct _caller_saved _caller_saved_t;

struct _irq_stack_frame {
	u32_t r0;
	u32_t r1;
	u32_t r2;
	u32_t r3;
	u32_t r4;
	u32_t r5;
	u32_t r6;
	u32_t r7;
	u32_t r8;
	u32_t r9;
	u32_t r10;
	u32_t r11;
	u32_t r12;
	u32_t r13;
	u32_t blink;
	u32_t lp_end;
	u32_t lp_start;
	u32_t lp_count;
#ifdef CONFIG_CODE_DENSITY
	/*
	 * Currently unsupported. This is where those registers are
	 * automatically pushed on the stack by the CPU when taking a regular
	 * IRQ.
	 */
	u32_t ei_base;
	u32_t ldi_base;
	u32_t jli_base;
#endif
	u32_t pc;
	u32_t status32;
};

typedef struct _irq_stack_frame _isf_t;

struct _callee_saved {
	u32_t sp; /* r28 */
};
typedef struct _callee_saved _callee_saved_t;

/* callee-saved registers pushed on the stack, not in k_thread */
struct _callee_saved_stack {
	u32_t r13;
	u32_t r14;
	u32_t r15;
	u32_t r16;
	u32_t r17;
	u32_t r18;
	u32_t r19;
	u32_t r20;
	u32_t r21;
	u32_t r22;
	u32_t r23;
	u32_t r24;
	u32_t r25;
	u32_t r26;
	u32_t fp; /* r27 */
	/* r28 is the stack pointer and saved separately */
	/* r29 is ILINK and does not need to be saved */
	u32_t r30;
	/*
	 * No need to save r31 (blink), it's either alread pushed as the pc or
	 * blink on an irq stack frame.
	 */
};

typedef struct _callee_saved_stack _callee_saved_stack_t;

#endif /* _ASMLANGUAGE */

/* stacks */

#define STACK_ALIGN_SIZE 4

#define STACK_ROUND_UP(x) ROUND_UP(x, STACK_ALIGN_SIZE)
#define STACK_ROUND_DOWN(x) ROUND_DOWN(x, STACK_ALIGN_SIZE)

/*
 * Reason a thread has relinquished control: fibers can only be in the NONE
 * or COOP state, tasks can be one in the four.
 */
#define _CAUSE_NONE 0
#define _CAUSE_COOP 1
#define _CAUSE_RIRQ 2
#define _CAUSE_FIRQ 3

#ifndef _ASMLANGUAGE

struct _thread_arch {

	/* interrupt key when relinquishing control */
	u32_t intlock_key;

	/* one of the _CAUSE_xxxx definitions above */
	int relinquish_cause;

	/* return value from _Swap */
	unsigned int return_value;

#ifdef CONFIG_ARC_STACK_CHECKING
	/* top of stack for hardware stack checking */
	u32_t stack_top;
#endif
};

typedef struct _thread_arch _thread_arch_t;

struct _kernel_arch {

	char *rirq_sp; /* regular IRQ stack pointer base */

	/*
	 * FIRQ stack pointer is installed once in the second bank's SP, so
	 * there is no need to track it in _kernel.
	 */

};

typedef struct _kernel_arch _kernel_arch_t;

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* _kernel_arch_data__h_ */
