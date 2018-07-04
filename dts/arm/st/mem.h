/*
 * Copyright (c) 2017 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __DT_BINDING_ST_MEM_H
#define __DT_BINDING_ST_MEM_H

#define __SIZE_K(x) ((x) * 1024)

#if defined(CONFIG_SOC_STM32F030X8)
#define DT_FLASH_SIZE		__SIZE_K(64)
#define DT_SRAM_SIZE		__SIZE_K(8)
#elif defined(CONFIG_SOC_STM32F051X8)
#define DT_FLASH_SIZE		__SIZE_K(64)
#define DT_SRAM_SIZE		__SIZE_K(8)
#elif defined(CONFIG_SOC_STM32F070XB)
#define DT_FLASH_SIZE		__SIZE_K(128)
#define DT_SRAM_SIZE		__SIZE_K(16)
#elif defined(CONFIG_SOC_STM32F072XB)
#define DT_FLASH_SIZE		__SIZE_K(128)
#define DT_SRAM_SIZE		__SIZE_K(16)
#elif defined(CONFIG_SOC_STM32F091XC)
#define DT_FLASH_SIZE		__SIZE_K(256)
#define DT_SRAM_SIZE		__SIZE_K(32)
#elif defined(CONFIG_SOC_STM32F103X8)
#define DT_FLASH_SIZE		__SIZE_K(64)
#define DT_SRAM_SIZE		__SIZE_K(20)
#elif defined(CONFIG_SOC_STM32F103XB)
#define DT_FLASH_SIZE		__SIZE_K(128)
#define DT_SRAM_SIZE		__SIZE_K(20)
#elif defined(CONFIG_SOC_STM32F103XE)
#define DT_FLASH_SIZE		__SIZE_K(512)
#define DT_SRAM_SIZE		__SIZE_K(64)
#elif defined(CONFIG_SOC_STM32F107XC)
#define DT_FLASH_SIZE		__SIZE_K(256)
#define DT_SRAM_SIZE		__SIZE_K(64)
#elif defined(CONFIG_SOC_STM32F207XE)
#define DT_FLASH_SIZE		__SIZE_K(512)
#define DT_SRAM_SIZE		__SIZE_K(128)
#elif defined(CONFIG_SOC_STM32F207XG)
#define DT_FLASH_SIZE		__SIZE_K(1024)
#define DT_SRAM_SIZE		__SIZE_K(128)
#elif defined(CONFIG_SOC_STM32F303XC)
#define DT_FLASH_SIZE		__SIZE_K(256)
#define DT_SRAM_SIZE		__SIZE_K(40)
#define DT_CCM_SIZE		__SIZE_K(8)
#elif defined(CONFIG_SOC_STM32F334X8)
#define DT_FLASH_SIZE		__SIZE_K(64)
#define DT_SRAM_SIZE		__SIZE_K(12)
#define DT_CCM_SIZE		__SIZE_K(4)
#elif defined(CONFIG_SOC_STM32F373XC)
#define DT_FLASH_SIZE		__SIZE_K(256)
#define DT_SRAM_SIZE		__SIZE_K(32)
#elif defined(CONFIG_SOC_STM32F401XE)
#define DT_FLASH_SIZE		__SIZE_K(512)
#define DT_SRAM_SIZE		__SIZE_K(96)
#elif defined(CONFIG_SOC_STM32F405XG)
#define DT_FLASH_SIZE		__SIZE_K(1024)
#define DT_SRAM_SIZE		__SIZE_K(192)
#define DT_CCM_SIZE		__SIZE_K(64)
#elif defined(CONFIG_SOC_STM32F407XG)
#define DT_FLASH_SIZE		__SIZE_K(1024)
#define DT_SRAM_SIZE		__SIZE_K(192)
#define DT_CCM_SIZE		__SIZE_K(64)
#elif defined(CONFIG_SOC_STM32F411XE)
#define DT_FLASH_SIZE		__SIZE_K(512)
#define DT_SRAM_SIZE		__SIZE_K(128)
#elif defined(CONFIG_SOC_STM32F412ZG) || defined(CONFIG_SOC_STM32F412CG)
#define DT_FLASH_SIZE		__SIZE_K(1024)
#define DT_SRAM_SIZE		__SIZE_K(256)
#elif defined(CONFIG_SOC_STM32F413XH)
#define DT_FLASH_SIZE		__SIZE_K(1536)
#define DT_SRAM_SIZE		__SIZE_K(320)
#elif defined(CONFIG_SOC_STM32F417XE)
#define DT_FLASH_SIZE		__SIZE_K(512)
#define DT_SRAM_SIZE		__SIZE_K(192)
#define DT_CCM_SIZE		__SIZE_K(64)
#elif defined(CONFIG_SOC_STM32F417XG)
#define DT_FLASH_SIZE		__SIZE_K(1024)
#define DT_SRAM_SIZE		__SIZE_K(192)
#define DT_CCM_SIZE		__SIZE_K(64)
#elif defined(CONFIG_SOC_STM32F429XI)
#define DT_FLASH_SIZE		__SIZE_K(2048)
#define DT_SRAM_SIZE		__SIZE_K(256)
#define DT_CCM_SIZE		__SIZE_K(64)
#elif defined(CONFIG_SOC_STM32F446XE)
#define DT_FLASH_SIZE		__SIZE_K(512)
#define DT_SRAM_SIZE		__SIZE_K(128)
#elif defined(CONFIG_SOC_STM32F469XI)
#define DT_FLASH_SIZE		__SIZE_K(2048)
#define DT_SRAM_SIZE		__SIZE_K(384)
#define DT_CCM_SIZE		__SIZE_K(64)
#elif defined(CONFIG_SOC_STM32F723XE)
#define DT_FLASH_SIZE		__SIZE_K(512)
#define DT_SRAM_SIZE		__SIZE_K(256)
#elif defined(CONFIG_SOC_STM32F746XG)
#define DT_FLASH_SIZE		__SIZE_K(1024)
#define DT_SRAM_SIZE		__SIZE_K(320)
#elif defined(CONFIG_SOC_STM32F769XI)
#define DT_FLASH_SIZE		__SIZE_K(2048)
#define DT_SRAM_SIZE		__SIZE_K(512)
#elif defined(CONFIG_SOC_STM32L053X8)
#define DT_FLASH_SIZE		__SIZE_K(64)
#define DT_SRAM_SIZE		__SIZE_K(8)
#elif defined(CONFIG_SOC_STM32L072XZ)
#define DT_FLASH_SIZE		__SIZE_K(192)
#define DT_SRAM_SIZE		__SIZE_K(20)
#elif defined(CONFIG_SOC_STM32L073XZ)
#define DT_FLASH_SIZE		__SIZE_K(192)
#define DT_SRAM_SIZE		__SIZE_K(20)
#elif defined(CONFIG_SOC_STM32L475XG)
#define DT_FLASH_SIZE		__SIZE_K(1024)
#define DT_SRAM_SIZE		__SIZE_K(96)
#elif defined(CONFIG_SOC_STM32L476XG)
#define DT_FLASH_SIZE		__SIZE_K(1024)
#define DT_SRAM_SIZE		__SIZE_K(96)
#elif defined(CONFIG_SOC_STM32L496XG)
#define DT_FLASH_SIZE		__SIZE_K(1024)
#define DT_SRAM_SIZE		__SIZE_K(320)
#elif defined(CONFIG_SOC_STM32L432XC)
#define DT_FLASH_SIZE		__SIZE_K(256)
#define DT_SRAM_SIZE		__SIZE_K(64)
#else
#error "Flash, RAM, and CCM sizes not defined for this chip"
#endif

#endif /* __DT_BINDING_ST_MEM_H */
