/*
 * Copyright (c) 2017 Linaro Limited.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef ZEPHYR_INCLUDE_ARCH_ARM_CORTEX_M_MPU_ARM_CORE_MPU_H_
#define ZEPHYR_INCLUDE_ARCH_ARM_CORTEX_M_MPU_ARM_CORE_MPU_H_

#include <kernel_structs.h>

#include <arch/arm/cortex_m/mpu/arm_core_mpu_dev.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Use the HW-specific MPU driver to program
 *        the static MPU regions.
 *
 * Program the static MPU regions through the HW-specific
 * MPU driver. The function is meant to be invoked once,
 * during system initialization.
 */
void _arch_configure_static_mpu_regions(void);

/**
 * @brief Use the HW-specific MPU driver to program
 *        the dynamic MPU regions.
 *
 * Program the dynamic MPU regions using the HW-specific MPU
 * driver. This function is meant to be invoked every time the
 * memory map is to be re-programmed, e.g during thread context
 * switch, entering user mode, reconfiguring memory domain, etc.
 *
 * @param thread pointer to the current k_thread context
 */
void _arch_configure_dynamic_mpu_regions(struct k_thread *thread);

#if defined(CONFIG_MPU_STACK_GUARD)
/**
 * @brief Configure MPU stack guard
 *
 * This function configures per thread stack guards reprogramming the MPU.
 * The functionality is meant to be used during context switch.
 *
 * @param thread thread info data structure.
 */
void configure_mpu_stack_guard(struct k_thread *thread);
#endif

#if defined(CONFIG_USERSPACE)
/*
 * @brief Configure MPU memory domain
 *
 * This function configures per thread memory domain reprogramming the MPU.
 * The functionality is meant to be used during context switch.
 *
 * @param thread thread info data structure.
 */
void configure_mpu_mem_domain(struct k_thread *thread);

/*
 * @brief Configure MPU user context
 *
 * This function configures the stack and application data regions
 * for user mode threads
 *
 * @param thread thread info data structure.
 */
void configure_mpu_user_context(struct k_thread *thread);

#endif

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_ARCH_ARM_CORTEX_M_MPU_ARM_CORE_MPU_H_ */
