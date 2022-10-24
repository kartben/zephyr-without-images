/* Copyright (c) 2022 Intel Corporation
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef ZEPHYR_SOC_INTEL_ADSP_ACE_IMR_LAYOUT_H_
#define ZEPHYR_SOC_INTEL_ADSP_ACE_IMR_LAYOUT_H_

/* These structs and macros are from from the ROM code header
 * on cAVS platforms, please keep them immutable
 */

/*
 * A magic that tells ROM to jump to imr_restore_vector instead of normal boot
 */
#define ADSP_IMR_MAGIC_VALUE		0x02468ACE
#define IMR_LAYOUT_OFFSET               0x20000
#define IMR_LAYOUT_ADDRESS              (L3_MEM_BASE_ADDR + IMR_LAYOUT_OFFSET)

struct imr_header {
	uint32_t adsp_imr_magic;
	uint32_t structure_version;
	uint32_t structure_size;
	uint32_t imr_state;
	uint32_t imr_size;
	void *imr_restore_vector;
	void *imr_auth_api_vector;
	uint8_t *imr_ram_storage;
};

struct imr_state {
	struct imr_header header;
	uint8_t reserved[0x1000 - sizeof(struct imr_header)];
};

struct imr_layout {
	struct imr_state    imr_state;
};

#endif /* ZEPHYR_SOC_INTEL_ADSP_ACE_IMR_LAYOUT_H_ */
