/*
 * Copyright (c) 2017 Nordic Semiconductor ASA
 * Copyright (c) 2016-2017 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DFU_BOOT_MCUBOOT_H_
#define ZEPHYR_DFU_BOOT_MCUBOOT_H_

#include <storage/flash_map.h>

/* FLASH_AREA_ID() values used below are auto-generated by DT */
#ifdef CONFIG_TRUSTED_EXECUTION_NONSECURE
#define FLASH_AREA_IMAGE_PRIMARY FLASH_AREA_ID(image_0_nonsecure)
#define FLASH_AREA_IMAGE_SECONDARY FLASH_AREA_ID(image_1_nonsecure)
#else
#define FLASH_AREA_IMAGE_PRIMARY FLASH_AREA_ID(image_0)
#if FLASH_AREA_LABEL_EXISTS(image_1)
#define FLASH_AREA_IMAGE_SECONDARY FLASH_AREA_ID(image_1)
#endif
#endif /* CONFIG_TRUSTED_EXECUTION_NONSECURE */

#if FLASH_AREA_LABEL_EXISTS(image_scratch)
#define FLASH_AREA_IMAGE_SCRATCH FLASH_AREA_ID(image_scratch)
#endif

#define BOOT_MAGIC_GOOD    1
#define BOOT_MAGIC_BAD     2
#define BOOT_MAGIC_UNSET   3
#define BOOT_MAGIC_ANY     4  /* NOTE: control only, not dependent on sector */
#define BOOT_MAGIC_NOTGOOD 5  /* NOTE: control only, not dependent on sector */

#define BOOT_FLAG_SET   1
#define BOOT_FLAG_BAD   2
#define BOOT_FLAG_UNSET 3
#define BOOT_FLAG_ANY   4  /* NOTE: control only, not dependent on sector */

/** Represents the management state of a single image slot. */
struct boot_swap_state {
	uint8_t magic;     /* One of the BOOT_MAGIC_[...] values. */
	uint8_t swap_type; /* One of the BOOT_SWAP_TYPE_[...] values. */
	uint8_t copy_done; /* One of the BOOT_FLAG_[...] values. */
	uint8_t image_ok;  /* One of the BOOT_FLAG_[...] values. */
};

int
boot_read_swap_state_by_id(int flash_area_id, struct boot_swap_state *state);

#endif /* ZEPHYR_DFU_BOOT_MCUBOOT_H_ */
