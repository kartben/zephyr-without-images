/*
 * Copyright (c) 2017 Linaro Limited.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _ARM_MPU_H_
#define _ARM_MPU_H_

#include <arch/arm/cortex_m/mpu/arm_core_mpu_dev.h>
#include <arch/arm/cortex_m/cmsis.h>

/* ARM MPU RASR Register */

/* Privileged No Access, Unprivileged No Access */
#define NO_ACCESS	((0x0 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk)
/* Privileged No Access, Unprivileged No Access */
#define P_NA_U_NA	((0x0 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk)
/* Privileged Read Write, Unprivileged No Access */
#define P_RW_U_NA	((0x1 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk)
/* Privileged Read Write, Unprivileged Read Only */
#define P_RW_U_RO	((0x2 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk)
/* Privileged Read Write, Unprivileged Read Write */
#define P_RW_U_RW	((0x3 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk)
/* Privileged Read Write, Unprivileged Read Write */
#define FULL_ACCESS	((0x3 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk)
/* Privileged Read Only, Unprivileged No Access */
#define P_RO_U_NA	((0x5 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk)
/* Privileged Read Only, Unprivileged Read Only */
#define P_RO_U_RO	((0x6 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk)
/* Privileged Read Only, Unprivileged Read Only */
#define RO		((0x7 << MPU_RASR_AP_Pos) & MPU_RASR_AP_Msk)

/* The following definitions are for internal use in this file. */
#define STRONGLY_ORDERED_SHAREABLE      MPU_RASR_S_Msk
#define DEVICE_SHAREABLE                (MPU_RASR_B_Msk | MPU_RASR_S_Msk)
#define NORMAL_OUTER_INNER_WRITE_THROUGH_SHAREABLE \
		(MPU_RASR_C_Msk | MPU_RASR_S_Msk)
#define NORMAL_OUTER_INNER_WRITE_THROUGH_NON_SHAREABLE	MPU_RASR_C_Msk
#define NORMAL_OUTER_INNER_WRITE_BACK_SHAREABLE	\
		(MPU_RASR_C_Msk | MPU_RASR_B_Msk | MPU_RASR_S_Msk)
#define NORMAL_OUTER_INNER_WRITE_BACK_NON_SHAREABLE \
		(MPU_RASR_C_Msk | MPU_RASR_B_Msk)
#define NORMAL_OUTER_INNER_NON_CACHEABLE_SHAREABLE \
		((1 << MPU_RASR_TEX_Pos) | MPU_RASR_S_Msk)
#define NORMAL_OUTER_INNER_NON_CACHEABLE_NON_SHAREABLE \
		(1 << MPU_RASR_TEX_Pos)
#define NORMAL_OUTER_INNER_WRITE_BACK_WRITE_READ_ALLOCATE_SHAREABLE \
	((1 << MPU_RASR_TEX_Pos) |\
	 MPU_RASR_C_Msk | MPU_RASR_B_Msk | MPU_RASR_S_Msk)
#define NORMAL_OUTER_INNER_WRITE_BACK_WRITE_READ_ALLOCATE_NONSHAREABLE \
	((1 << MPU_RASR_TEX_Pos) | MPU_RASR_C_Msk | MPU_RASR_S_Msk)
#define DEVICE_NON_SHAREABLE            (2 << MPU_RASR_TEX_Pos)

/* Some helper defines for common regions */
#define REGION_USER_RAM_ATTR(size) \
		(NORMAL_OUTER_INNER_NON_CACHEABLE_NON_SHAREABLE | \
		 MPU_RASR_XN_Msk | size | FULL_ACCESS)
#define REGION_RAM_ATTR(size) \
		(NORMAL_OUTER_INNER_NON_CACHEABLE_NON_SHAREABLE | \
		 MPU_RASR_XN_Msk | size | P_RW_U_NA)
#if defined(CONFIG_MPU_ALLOW_FLASH_WRITE)
#define REGION_FLASH_ATTR(size) \
		(NORMAL_OUTER_INNER_NON_CACHEABLE_NON_SHAREABLE | size | \
		 P_RW_U_RO)
#else
#define REGION_FLASH_ATTR(size) \
		(NORMAL_OUTER_INNER_NON_CACHEABLE_NON_SHAREABLE | size | RO)
#endif
#define REGION_PPB_ATTR(size) (STRONGLY_ORDERED_SHAREABLE | size | P_RW_U_NA)
#define REGION_IO_ATTR(size) (DEVICE_NON_SHAREABLE | size | P_RW_U_NA)

#define SUB_REGION_0_DISABLED	((0x01 << MPU_RASR_SRD_Pos) & MPU_RASR_SRD_Msk)
#define SUB_REGION_1_DISABLED	((0x02 << MPU_RASR_SRD_Pos) & MPU_RASR_SRD_Msk)
#define SUB_REGION_2_DISABLED	((0x04 << MPU_RASR_SRD_Pos) & MPU_RASR_SRD_Msk)
#define SUB_REGION_3_DISABLED	((0x08 << MPU_RASR_SRD_Pos) & MPU_RASR_SRD_Msk)
#define SUB_REGION_4_DISABLED	((0x10 << MPU_RASR_SRD_Pos) & MPU_RASR_SRD_Msk)
#define SUB_REGION_5_DISABLED	((0x20 << MPU_RASR_SRD_Pos) & MPU_RASR_SRD_Msk)
#define SUB_REGION_6_DISABLED	((0x40 << MPU_RASR_SRD_Pos) & MPU_RASR_SRD_Msk)
#define SUB_REGION_7_DISABLED	((0x80 << MPU_RASR_SRD_Pos) & MPU_RASR_SRD_Msk)

#define REGION_32B      ((0x04 << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_64B      ((0x05 << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_128B     ((0x06 << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_256B     ((0x07 << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_512B     ((0x08 << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_1K       ((0x09 << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_2K       ((0x0A << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_4K       ((0x0B << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_8K       ((0x0C << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_16K      ((0x0D << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_32K      ((0x0E << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_64K      ((0x0F << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_128K     ((0x10 << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_256K     ((0x11 << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_512K     ((0x12 << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_1M       ((0x13 << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_2M       ((0x14 << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_4M       ((0x15 << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_8M       ((0x16 << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_16M      ((0x17 << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_32M      ((0x18 << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_64M      ((0x19 << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_128M     ((0x1A << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_256M     ((0x1B << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_512M     ((0x1C << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_1G       ((0x1D << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_2G       ((0x1E << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)
#define REGION_4G       ((0x1F << MPU_RASR_SIZE_Pos) & MPU_RASR_SIZE_Msk)

/* Region definition data structure */
struct arm_mpu_region {
	/* Region Base Address */
	u32_t base;
	/* Region Name */
	const char *name;
	/* Region Attributes */
	u32_t attr;
};

#define MPU_REGION_ENTRY(_name, _base, _attr) \
	{\
		.name = _name, \
		.base = _base, \
		.attr = _attr, \
	}

/* MPU configuration data structure */
struct arm_mpu_config {
	/* Number of regions */
	u32_t num_regions;
	/* Regions */
	struct arm_mpu_region *mpu_regions;
};

/* Reference to the MPU configuration */
extern struct arm_mpu_config mpu_config;

#endif /* _ARM_MPU_H_ */
