/*
 * Copyright (c) 2017 Linaro Limited.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _ARM_MPU_MEM_CFG_H_
#define _ARM_MPU_MEM_CFG_H_

#include <soc.h>
#include <arch/arm/cortex_m/mpu/arm_mpu.h>

/* Flash Region Definitions */
#if !defined(CONFIG_SOC_SERIES_STM32WBX)
#if CONFIG_FLASH_SIZE == 64
#define REGION_FLASH_SIZE REGION_64K
#elif CONFIG_FLASH_SIZE == 128
#define REGION_FLASH_SIZE REGION_128K
#elif CONFIG_FLASH_SIZE == 256
#define REGION_FLASH_SIZE REGION_256K
#elif CONFIG_FLASH_SIZE == 512
#define REGION_FLASH_SIZE REGION_512K
#elif CONFIG_FLASH_SIZE == 1024
#define REGION_FLASH_SIZE REGION_1M
#elif CONFIG_FLASH_SIZE == 1536
#define REGION_FLASH_SIZE REGION_2M	/* last 512kB are not mapped */
#elif CONFIG_FLASH_SIZE == 2048
#define REGION_FLASH_SIZE REGION_2M
#else
#error "Unsupported configuration"
#endif
#else /* CONFIG_SOC_SERIES_STM32WBX */
/* For STM32WBX SoCs, last 212K are resevred for M0 fw */
/* and should not be covered by zephyr MPU. */
/* So map only the first 512K, which is beyond partition 'image-0' */
#if CONFIG_FLASH_SIZE == 812
#define REGION_FLASH_SIZE REGION_1M
#else
#error "Unsupported configuration"
#endif
#endif /* CONFIG_SOC_SERIES_STM32WBX */

/* SRAM Region Definitions */
#if CONFIG_SRAM_SIZE == 12
#define REGION_SRAM_0_SIZE REGION_8K
#define REGION_SRAM_1_START 0x2000
#define REGION_SRAM_1_SIZE REGION_4K
#elif CONFIG_SRAM_SIZE == 20
#define REGION_SRAM_0_SIZE REGION_16K
#define REGION_SRAM_1_START 0x4000
#define REGION_SRAM_1_SIZE REGION_4K
#elif CONFIG_SRAM_SIZE == 32
#define REGION_SRAM_0_SIZE REGION_32K
#elif CONFIG_SRAM_SIZE == 40
#define REGION_SRAM_0_SIZE REGION_32K
#define REGION_SRAM_1_START 0x8000
#define REGION_SRAM_1_SIZE REGION_8K
#elif CONFIG_SRAM_SIZE == 64
#define REGION_SRAM_0_SIZE REGION_64K
#elif CONFIG_SRAM_SIZE == 96
#define REGION_SRAM_0_SIZE REGION_64K
#define REGION_SRAM_1_START 0x10000
#define REGION_SRAM_1_SIZE REGION_32K
#elif CONFIG_SRAM_SIZE == 128
#define REGION_SRAM_0_SIZE REGION_128K
#elif CONFIG_SRAM_SIZE == 160
#define REGION_SRAM_0_SIZE REGION_128K
#define REGION_SRAM_1_START 0x20000
#define REGION_SRAM_1_SIZE REGION_32K
#elif CONFIG_SRAM_SIZE == 192
#define REGION_SRAM_0_SIZE REGION_128K
#define REGION_SRAM_1_START 0x20000
#define REGION_SRAM_1_SIZE REGION_64K
#elif CONFIG_SRAM_SIZE == 256
#define REGION_SRAM_0_SIZE REGION_256K
#elif CONFIG_SRAM_SIZE == 320
#define REGION_SRAM_0_SIZE REGION_256K
#define REGION_SRAM_1_START 0x40000
#define REGION_SRAM_1_SIZE REGION_64K
#elif CONFIG_SRAM_SIZE == 384
#define REGION_SRAM_0_SIZE REGION_256K
#define REGION_SRAM_1_START 0x40000
#define REGION_SRAM_1_SIZE REGION_128K
#elif CONFIG_SRAM_SIZE == 512
#define REGION_SRAM_0_SIZE REGION_512K
#elif CONFIG_SRAM_SIZE == 640
#define REGION_SRAM_0_SIZE REGION_512K
#define REGION_SRAM_1_START 0x80000
#define REGION_SRAM_1_SIZE REGION_128K
#else
#error "Unsupported configuration"
#endif

#endif /* _ARM_MPU_MEM_CFG_H_ */
