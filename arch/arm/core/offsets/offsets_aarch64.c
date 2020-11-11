/*
 * Copyright (c) 2019 Carlo Caione <ccaione@baylibre.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief ARM64 kernel structure member offset definition file
 *
 * This module is responsible for the generation of the absolute symbols whose
 * value represents the member offsets for various ARM kernel structures.
 *
 * All of the absolute symbols defined by this module will be present in the
 * final kernel ELF image (due to the linker's reference to the _OffsetAbsSyms
 * symbol).
 *
 * INTERNAL
 * It is NOT necessary to define the offset for every member of a structure.
 * Typically, only those members that are accessed by assembly language routines
 * are defined; however, it doesn't hurt to define all fields for the sake of
 * completeness.
 */

#ifndef _ARM_OFFSETS_INC_
#define _ARM_OFFSETS_INC_

#include <kernel.h>
#include <kernel_arch_data.h>
#include <kernel_offsets.h>

GEN_NAMED_OFFSET_SYM(_callee_saved_t, x19, x19_x20);
GEN_NAMED_OFFSET_SYM(_callee_saved_t, x21, x21_x22);
GEN_NAMED_OFFSET_SYM(_callee_saved_t, x23, x23_x24);
GEN_NAMED_OFFSET_SYM(_callee_saved_t, x25, x25_x26);
GEN_NAMED_OFFSET_SYM(_callee_saved_t, x27, x27_x28);
GEN_NAMED_OFFSET_SYM(_callee_saved_t, x29, x29_sp);

GEN_ABSOLUTE_SYM(___callee_saved_t_SIZEOF, sizeof(struct _callee_saved));

GEN_NAMED_OFFSET_SYM(_esf_t, spsr, spsr_elr);
GEN_NAMED_OFFSET_SYM(_esf_t, x18, x18_x30);
GEN_NAMED_OFFSET_SYM(_esf_t, x16, x16_x17);
GEN_NAMED_OFFSET_SYM(_esf_t, x14, x14_x15);
GEN_NAMED_OFFSET_SYM(_esf_t, x12, x12_x13);
GEN_NAMED_OFFSET_SYM(_esf_t, x10, x10_x11);
GEN_NAMED_OFFSET_SYM(_esf_t, x8, x8_x9);
GEN_NAMED_OFFSET_SYM(_esf_t, x6, x6_x7);
GEN_NAMED_OFFSET_SYM(_esf_t, x4, x4_x5);
GEN_NAMED_OFFSET_SYM(_esf_t, x2, x2_x3);
GEN_NAMED_OFFSET_SYM(_esf_t, x0, x0_x1);

GEN_ABSOLUTE_SYM(___esf_t_SIZEOF, sizeof(_esf_t));

#endif /* _ARM_OFFSETS_INC_ */
