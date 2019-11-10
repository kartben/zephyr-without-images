/*
 * Copyright (c) 2019 Carlo Caione <ccaione@baylibre.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_ARCH_ARM_INCLUDE_OFFSETS_SHORT_ARCH_H_
#define ZEPHYR_ARCH_ARM_INCLUDE_OFFSETS_SHORT_ARCH_H_

#if defined(CONFIG_ARM64)
#include <aarch64/offsets_short_arch.h>
#else
#include <aarch32/offsets_short_arch.h>
#endif

#endif /* ZEPHYR_ARCH_ARM_INCLUDE_OFFSETS_SHORT_ARCH_H_ */
