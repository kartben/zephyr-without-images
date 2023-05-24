/*
 * Copyright (c) 2023 Carlo Caione <ccaione@baylibre.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_SYS_BARRIER_H_
#define ZEPHYR_INCLUDE_SYS_BARRIER_H_

#include <zephyr/toolchain.h>

#if defined(CONFIG_BARRIER_OPERATIONS_ARCH)
/* Empty */
#elif defined(CONFIG_BARRIER_OPERATIONS_BUILTIN)
#include <zephyr/sys/barrier_builtin.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup barrier_apis Barrier Services APIs
 * @ingroup kernel_apis
 * @{
 */

/**
 * @brief Full/sequentially-consistent data memory barrier.
 *
 * This routine acts as a synchronization fence between threads and prevents
 * re-ordering of data accesses instructions across the barrier instruction.
 */
static ALWAYS_INLINE void barrier_dmem_fence_full(void)
{
#if defined(CONFIG_BARRIER_OPERATIONS_ARCH) || defined(CONFIG_BARRIER_OPERATIONS_BUILTIN)
	z_barrier_dmem_fence_full();
#endif
}

/** @} */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ZEPHYR_INCLUDE_SYS_ATOMIC_H_ */
