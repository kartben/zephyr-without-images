/* Copyright (c) 2021 Intel Corporation
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _ZEPHYR_SOC_INTEL_ADSP_MEM
#define _ZEPHYR_SOC_INTEL_ADSP_MEM

#include <devicetree.h>
#include <cavs-vectors.h>

#define L2_SRAM_BASE (DT_REG_ADDR(DT_NODELABEL(sram0)))
#define L2_SRAM_SIZE (DT_REG_SIZE(DT_NODELABEL(sram0)))

#define LP_SRAM_BASE (DT_REG_ADDR(DT_NODELABEL(sram1)))
#define LP_SRAM_SIZE (DT_REG_SIZE(DT_NODELABEL(sram1)))

/* Linker-usable RAM region */
#define RAM_BASE (L2_SRAM_BASE + CONFIG_HP_SRAM_RESERVE + VECTOR_TBL_SIZE)
#define RAM_SIZE (L2_SRAM_SIZE - CONFIG_HP_SRAM_RESERVE - VECTOR_TBL_SIZE)

/* These are fake section addresses used only in the linker scripts */
#define IDT_BASE		(L2_SRAM_BASE + L2_SRAM_SIZE)
#define IDT_SIZE		0x2000
#define UUID_ENTRY_ELF_BASE	0x1FFFA000
#define UUID_ENTRY_ELF_SIZE	0x6000
#define LOG_ENTRY_ELF_BASE	0x20000000
#define LOG_ENTRY_ELF_SIZE	0x2000000
#define EXT_MANIFEST_ELF_BASE	(LOG_ENTRY_ELF_BASE + LOG_ENTRY_ELF_SIZE)
#define EXT_MANIFEST_ELF_SIZE	0x2000000

#endif /* _ZEPHYR_SOC_INTEL_ADSP_MEM */
