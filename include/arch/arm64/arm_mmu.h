/*
 * Copyright 2019 Broadcom
 * The term "Broadcom" refers to Broadcom Inc. and/or its subsidiaries.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef ZEPHYR_INCLUDE_ARCH_ARM64_ARM_MMU_H_
#define ZEPHYR_INCLUDE_ARCH_ARM64_ARM_MMU_H_

/* Following Memory types supported through MAIR encodings can be passed
 * by user through "attrs"(attributes) field of specified memory region.
 * As MAIR supports such 8 encodings, we will reserve attrs[2:0];
 * so that we can provide encodings upto 7 if needed in future.
 */
#define MT_TYPE_MASK		0x7U
#define MT_TYPE(attr)		(attr & MT_TYPE_MASK)
#define MT_DEVICE_nGnRnE	0U
#define MT_DEVICE_nGnRE		1U
#define MT_DEVICE_GRE		2U
#define MT_NORMAL_NC		3U
#define MT_NORMAL		4U
#define MT_NORMAL_WT		5U

#define MEMORY_ATTRIBUTES	((0x00 << (MT_DEVICE_nGnRnE * 8)) |	\
				(0x04 << (MT_DEVICE_nGnRE * 8))   |	\
				(0x0c << (MT_DEVICE_GRE * 8))     |	\
				(0x44 << (MT_NORMAL_NC * 8))      |	\
				(0xffUL << (MT_NORMAL * 8))	  |	\
				(0xbbUL << (MT_NORMAL_WT * 8)))

/* More flags from user's perpective are supported using remaining bits
 * of "attrs" field, i.e. attrs[31:3], underlying code will take care
 * of setting PTE fields correctly.
 *
 * current usage of attrs[31:3] is:
 * attrs[3] : Access Permissions
 * attrs[4] : Memory access from secure/ns state
 * attrs[5] : Execute Permissions privileged mode (PXN)
 * attrs[6] : Execute Permissions unprivileged mode (UXN)
 * attrs[7] : Mirror RO/RW permissions to EL0
 * attrs[8] : Overwrite existing mapping if any
 *
 */
#define MT_PERM_SHIFT		3U
#define MT_SEC_SHIFT		4U
#define MT_P_EXECUTE_SHIFT	5U
#define MT_U_EXECUTE_SHIFT	6U
#define MT_RW_AP_SHIFT		7U
#define MT_NO_OVERWRITE_SHIFT	8U

#define MT_RO			(0U << MT_PERM_SHIFT)
#define MT_RW			(1U << MT_PERM_SHIFT)

#define MT_RW_AP_ELx		(1U << MT_RW_AP_SHIFT)
#define MT_RW_AP_EL_HIGHER	(0U << MT_RW_AP_SHIFT)

#define MT_SECURE		(0U << MT_SEC_SHIFT)
#define MT_NS			(1U << MT_SEC_SHIFT)

#define MT_P_EXECUTE		(0U << MT_P_EXECUTE_SHIFT)
#define MT_P_EXECUTE_NEVER	(1U << MT_P_EXECUTE_SHIFT)

#define MT_U_EXECUTE		(0U << MT_U_EXECUTE_SHIFT)
#define MT_U_EXECUTE_NEVER	(1U << MT_U_EXECUTE_SHIFT)

#define MT_NO_OVERWRITE		(1U << MT_NO_OVERWRITE_SHIFT)

#define MT_P_RW_U_RW		(MT_RW | MT_RW_AP_ELx | MT_P_EXECUTE_NEVER | MT_U_EXECUTE_NEVER)
#define MT_P_RW_U_NA		(MT_RW | MT_RW_AP_EL_HIGHER  | MT_P_EXECUTE_NEVER | MT_U_EXECUTE_NEVER)
#define MT_P_RO_U_RO		(MT_RO | MT_RW_AP_ELx | MT_P_EXECUTE_NEVER | MT_U_EXECUTE_NEVER)
#define MT_P_RO_U_NA		(MT_RO | MT_RW_AP_EL_HIGHER  | MT_P_EXECUTE_NEVER | MT_U_EXECUTE_NEVER)
#define MT_P_RO_U_RX		(MT_RO | MT_RW_AP_ELx | MT_P_EXECUTE_NEVER | MT_U_EXECUTE)
#define MT_P_RX_U_RX		(MT_RO | MT_RW_AP_ELx | MT_P_EXECUTE | MT_U_EXECUTE)
#define MT_P_RX_U_NA		(MT_RO | MT_RW_AP_EL_HIGHER  | MT_P_EXECUTE | MT_U_EXECUTE_NEVER)

#ifdef CONFIG_ARMV8_A_NS
#define MT_DEFAULT_SECURE_STATE	MT_NS
#else
#define MT_DEFAULT_SECURE_STATE	MT_SECURE
#endif

/*
 * PTE descriptor can be Block descriptor or Table descriptor
 * or Page descriptor.
 */
#define PTE_DESC_TYPE_MASK	3U
#define PTE_BLOCK_DESC		1U
#define PTE_TABLE_DESC		3U
#define PTE_PAGE_DESC		3U
#define PTE_INVALID_DESC	0U

/*
 * Block and Page descriptor attributes fields
 */
#define PTE_BLOCK_DESC_MEMTYPE(x)	(x << 2)
#define PTE_BLOCK_DESC_NS		(1ULL << 5)
#define PTE_BLOCK_DESC_AP_ELx		(1ULL << 6)
#define PTE_BLOCK_DESC_AP_EL_HIGHER	(0ULL << 6)
#define PTE_BLOCK_DESC_AP_RO		(1ULL << 7)
#define PTE_BLOCK_DESC_AP_RW		(0ULL << 7)
#define PTE_BLOCK_DESC_NON_SHARE	(0ULL << 8)
#define PTE_BLOCK_DESC_OUTER_SHARE	(2ULL << 8)
#define PTE_BLOCK_DESC_INNER_SHARE	(3ULL << 8)
#define PTE_BLOCK_DESC_AF		(1ULL << 10)
#define PTE_BLOCK_DESC_NG		(1ULL << 11)
#define PTE_BLOCK_DESC_PXN		(1ULL << 53)
#define PTE_BLOCK_DESC_UXN		(1ULL << 54)

/*
 * TCR definitions.
 */
#define TCR_EL1_IPS_SHIFT	32U
#define TCR_EL2_PS_SHIFT	16U
#define TCR_EL3_PS_SHIFT	16U

#define TCR_T0SZ_SHIFT		0U
#define TCR_T0SZ(x)		((64 - (x)) << TCR_T0SZ_SHIFT)

#define TCR_IRGN_NC		(0ULL << 8)
#define TCR_IRGN_WBWA		(1ULL << 8)
#define TCR_IRGN_WT		(2ULL << 8)
#define TCR_IRGN_WBNWA		(3ULL << 8)
#define TCR_IRGN_MASK		(3ULL << 8)
#define TCR_ORGN_NC		(0ULL << 10)
#define TCR_ORGN_WBWA		(1ULL << 10)
#define TCR_ORGN_WT		(2ULL << 10)
#define TCR_ORGN_WBNWA		(3ULL << 10)
#define TCR_ORGN_MASK		(3ULL << 10)
#define TCR_SHARED_NON		(0ULL << 12)
#define TCR_SHARED_OUTER	(2ULL << 12)
#define TCR_SHARED_INNER	(3ULL << 12)
#define TCR_TG0_4K		(0ULL << 14)
#define TCR_TG0_64K		(1ULL << 14)
#define TCR_TG0_16K		(2ULL << 14)
#define TCR_EPD1_DISABLE	(1ULL << 23)

#define TCR_PS_BITS_4GB		0x0ULL
#define TCR_PS_BITS_64GB	0x1ULL
#define TCR_PS_BITS_1TB		0x2ULL
#define TCR_PS_BITS_4TB		0x3ULL
#define TCR_PS_BITS_16TB	0x4ULL
#define TCR_PS_BITS_256TB	0x5ULL

#ifndef _ASMLANGUAGE

/* Region definition data structure */
struct arm_mmu_region {
	/* Region Base Physical Address */
	uintptr_t base_pa;
	/* Region Base Virtual Address */
	uintptr_t base_va;
	/* Region size */
	size_t size;
	/* Region Name */
	const char *name;
	/* Region Attributes */
	uint32_t attrs;
};

/* MMU configuration data structure */
struct arm_mmu_config {
	/* Number of regions */
	unsigned int num_regions;
	/* Regions */
	const struct arm_mmu_region *mmu_regions;
};

struct arm_mmu_ptables {
	uint64_t *base_xlat_table;
};

/* Convenience macros to represent the ARMv8-A-specific
 * configuration for memory access permission and
 * cache-ability attribution.
 */

#define MMU_REGION_ENTRY(_name, _base_pa, _base_va, _size, _attrs) \
	{\
		.name = _name, \
		.base_pa = _base_pa, \
		.base_va = _base_va, \
		.size = _size, \
		.attrs = _attrs, \
	}

#define MMU_REGION_FLAT_ENTRY(name, adr, sz, attrs) \
	MMU_REGION_ENTRY(name, adr, adr, sz, attrs)

/* Reference to the MMU configuration.
 *
 * This struct is defined and populated for each SoC (in the SoC definition),
 * and holds the build-time configuration information for the fixed MMU
 * regions enabled during kernel initialization.
 */
extern const struct arm_mmu_config mmu_config;

struct k_thread;
void z_arm64_thread_pt_init(struct k_thread *thread);
void z_arm64_swap_ptables(struct k_thread *thread);

#endif /* _ASMLANGUAGE */

#endif /* ZEPHYR_INCLUDE_ARCH_ARM64_ARM_MMU_H_ */
