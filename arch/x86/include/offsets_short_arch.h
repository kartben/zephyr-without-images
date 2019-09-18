/*
 * Copyright (c) 2019 Intel Corporation
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_ARCH_X86_INCLUDE_OFFSETS_SHORT_ARCH_H_
#define ZEPHYR_ARCH_X86_INCLUDE_OFFSETS_SHORT_ARCH_H_

#ifdef CONFIG_X86_LONGMODE
#include <intel64/offsets_short_arch.h>
#else
#include <ia32/offsets_short_arch.h>
#endif

#define _thread_offset_to_flags \
	(___thread_t_arch_OFFSET + ___thread_arch_t_flags_OFFSET)

#endif /* ZEPHYR_ARCH_X86_INCLUDE_OFFSETS_SHORT_ARCH_H_ */
