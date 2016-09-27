/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file
 * @brief ARM CORTEX-M memory map
 *
 * This module contains definitions for the memory map of the CORTEX-M series of
 * processors.
 */

#ifndef _CORTEXM_MEMORY_MAP__H_
#define _CORTEXM_MEMORY_MAP__H_

#include <misc/util.h>

/* 0x00000000 -> 0x1fffffff: Code in ROM [0.5 GB] */
#define _CODE_BASE_ADDR           0x00000000
#define _CODE_END_ADDR            0x1FFFFFFF

/* 0x20000000 -> 0x3fffffff: SRAM [0.5GB] */
#define _SRAM_BASE_ADDR           0x20000000
#define _SRAM_BIT_BAND_REGION     0x20000000
#define _SRAM_BIT_BAND_REGION_END 0x200FFFFF
#define _SRAM_BIT_BAND_ALIAS      0x22000000
#define _SRAM_BIT_BAND_ALIAS_END  0x23FFFFFF
#define _SRAM_END_ADDR            0x3FFFFFFF

/* 0x40000000 -> 0x5fffffff: Peripherals [0.5GB] */
#define _PERI_BASE_ADDR           0x40000000
#define _PERI_BIT_BAND_REGION     0x40000000
#define _PERI_BIT_BAND_REGION_END 0x400FFFFF
#define _PERI_BIT_BAND_ALIAS      0x42000000
#define _PERI_BIT_BAND_ALIAS_END  0x43FFFFFF
#define _PERI_END_ADDR            0x5FFFFFFF

/* 0x60000000 -> 0x9fffffff: external RAM [1GB] */
#define _ERAM_BASE_ADDR           0x60000000
#define _ERAM_END_ADDR            0x9FFFFFFF

/* 0xa0000000 -> 0xdfffffff: external devices [1GB] */
#define _EDEV_BASE_ADDR           0xA0000000
#define _EDEV_END_ADDR            0xDFFFFFFF

/* 0xe0000000 -> 0xffffffff: varies by processor (see below) */

/* 0xe0000000 -> 0xe00fffff: private peripheral bus */
/* 0xe0000000 -> 0xe003ffff: internal [256KB] */
#define _PPB_INT_BASE_ADDR        0xE0000000
#if defined(CONFIG_CPU_CORTEX_M0_M0PLUS)
#define _PPB_INT_RSVD_0           0xE0000000
#define _PPB_INT_DWT              0xE0001000
#define _PPB_INT_BPU              0xE0002000
#define _PPB_INT_RSVD_1           0xE0003000
#define _PPB_INT_SCS              0xE000E000
#define _PPB_INT_RSVD_2           0xE000F000
#elif defined(CONFIG_CPU_CORTEX_M3_M4) || defined(CONFIG_CPU_CORTEX_M7)
#define _PPB_INT_ITM              0xE0000000
#define _PPB_INT_DWT              0xE0001000
#define _PPB_INT_FPB              0xE0002000
#define _PPB_INT_RSVD_1           0xE0003000
#define _PPB_INT_SCS              0xE000E000
#define _PPB_INT_RSVD_2           0xE000F000
#else
#error Unknown CPU
#endif
#define _PPB_INT_END_ADDR         0xE003FFFF

/* 0xe0000000 -> 0xe00fffff: private peripheral bus */
/* 0xe0040000 -> 0xe00fffff: external [768K] */
#define _PPB_EXT_BASE_ADDR        0xE0040000
#if defined(CONFIG_CPU_CORTEX_M0_M0PLUS)
#elif defined(CONFIG_CPU_CORTEX_M3_M4)
#define _PPB_EXT_TPIU             0xE0040000
#define _PPB_EXT_ETM              0xE0041000
#define _PPB_EXT_PPB              0xE0042000
#define _PPB_EXT_ROM_TABLE        0xE00FF000
#define _PPB_EXT_END_ADDR         0xE00FFFFF
#elif defined(CONFIG_CPU_CORTEX_M7)
#define _PPB_EXT_BASE_ADDR        0xE0040000
#define _PPB_EXT_RSVD_TPIU        0xE0040000
#define _PPB_EXT_ETM              0xE0041000
#define _PPB_EXT_CTI              0xE0042000
#define _PPB_EXT_PPB              0xE0043000
#define _PPB_EXT_PROC_ROM_TABLE   0xE00FE000
#define _PPB_EXT_PPB_ROM_TABLE    0xE00FF000
#else
#error Unknown CPU
#endif
#define _PPB_EXT_END_ADDR         0xE00FFFFF

/* 0xe0100000 -> 0xffffffff: vendor-specific [0.5GB-1MB or 511MB]  */
#define _VENDOR_BASE_ADDR         0xE0100000
#define _VENDOR_END_ADDR          0xFFFFFFFF

#endif /* _CORTEXM_MEMORY_MAP__H_ */
