/*
 * Copyright (c) 2017 Linaro Limited.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _ARM_CORTEX_M_MPU_MEM_CFG_H_
#define _ARM_CORTEX_M_MPU_MEM_CFG_H_

#include <arch/arm/cortex_m/mpu/arm_mpu.h>

#if !defined(CONFIG_ARMV8_M_BASELINE) && !defined(CONFIG_ARMV8_M_MAINLINE)

/* Flash Region Definitions */
#if CONFIG_FLASH_SIZE <= 64
#define REGION_FLASH_SIZE REGION_64K
#elif CONFIG_FLASH_SIZE <= 128
#define REGION_FLASH_SIZE REGION_128K
#elif CONFIG_FLASH_SIZE <= 256
#define REGION_FLASH_SIZE REGION_256K
#elif CONFIG_FLASH_SIZE <= 512
#define REGION_FLASH_SIZE REGION_512K
#elif CONFIG_FLASH_SIZE <= 1024
#define REGION_FLASH_SIZE REGION_1M
#elif CONFIG_FLASH_SIZE <= 2048
#define REGION_FLASH_SIZE REGION_2M
#elif CONFIG_FLASH_SIZE <= 4096
#define REGION_FLASH_SIZE REGION_4M
#elif CONFIG_FLASH_SIZE <= 8192
#define REGION_FLASH_SIZE REGION_8M
#elif CONFIG_FLASH_SIZE <= 16384
#define REGION_FLASH_SIZE REGION_16M
#elif CONFIG_FLASH_SIZE <= 65536
#define REGION_FLASH_SIZE REGION_64M
#else
#error "Unsupported configuration"
#endif

/* SRAM Region Definitions */
#if CONFIG_SRAM_SIZE <= 16
#define REGION_SRAM_SIZE REGION_16K
#elif CONFIG_SRAM_SIZE <= 32
#define REGION_SRAM_SIZE REGION_32K
#elif CONFIG_SRAM_SIZE <= 64
#define REGION_SRAM_SIZE REGION_64K
#elif CONFIG_SRAM_SIZE <= 128
#define REGION_SRAM_SIZE REGION_128K
#elif CONFIG_SRAM_SIZE <= 256
#define REGION_SRAM_SIZE REGION_256K
#elif CONFIG_SRAM_SIZE <= 512
#define REGION_SRAM_SIZE REGION_512K
#elif CONFIG_SRAM_SIZE <= 1024
#define REGION_SRAM_SIZE REGION_1M
#elif CONFIG_SRAM_SIZE <= 2048
#define REGION_SRAM_SIZE REGION_2M
#elif CONFIG_SRAM_SIZE <= 4096
#define REGION_SRAM_SIZE REGION_4M
#elif CONFIG_SRAM_SIZE == 32768
#define REGION_SRAM_SIZE REGION_32M
#else
#error "Unsupported configuration"
#endif

#endif /* !ARMV8_M_BASELINE && !ARMV8_M_MAINLINE */

#endif /* _ARM_CORTEX_M_MPU_MEM_CFG_H_ */
