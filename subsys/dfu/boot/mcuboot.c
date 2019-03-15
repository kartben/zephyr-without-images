/*
 * Copyright (c) 2017 Nordic Semiconductor ASA
 * Copyright (c) 2016-2017 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <assert.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>
#include <flash.h>
#include <flash_map.h>
#include <zephyr.h>
#include <init.h>

#include <misc/__assert.h>
#include <misc/byteorder.h>
#include <dfu/mcuboot.h>

/*
 * Helpers for image headers and trailers, as defined by mcuboot.
 */

/*
 * Strict defines: the definitions in the following block contain
 * values which are MCUboot implementation requirements.
 */

/* Header: */
#define BOOT_HEADER_MAGIC_V1 0x96f3b83d
#define BOOT_HEADER_SIZE_V1 32

/* Trailer: */
#define BOOT_FLAG_SET 0x01
#define BOOT_FLAG_UNSET 0xff

/*
 * Raw (on-flash) representation of the v1 image header.
 */
struct mcuboot_v1_raw_header {
	u32_t header_magic;
	u32_t image_load_address;
	u16_t header_size;
	u16_t pad;
	u32_t image_size;
	u32_t image_flags;
	struct {
		u8_t major;
		u8_t minor;
		u16_t revision;
		u32_t build_num;
	} version;
	u32_t pad2;
} __packed;

/*
 * End of strict defines
 */

#define BOOT_MAGIC_GOOD  1
#define BOOT_MAGIC_BAD   2
#define BOOT_MAGIC_UNSET 3

#define BOOT_FLAG_IMAGE_OK 0
#define BOOT_FLAG_COPY_DONE 1

#define FLASH_MIN_WRITE_SIZE DT_FLASH_WRITE_BLOCK_SIZE

/* DT_FLASH_AREA_IMAGE_XX_YY values used below are auto-generated by DT */
#ifdef CONFIG_TRUSTED_EXECUTION_NONSECURE
#define FLASH_AREA_IMAGE_PRIMARY DT_FLASH_AREA_IMAGE_0_NONSECURE_ID
#define FLASH_AREA_IMAGE_SECONDARY DT_FLASH_AREA_IMAGE_1_NONSECURE_ID
#define FLASH_AREA_IMAGE_SCRATCH DT_FLASH_AREA_IMAGE_SCRATCH_ID
#else
#define FLASH_AREA_IMAGE_PRIMARY DT_FLASH_AREA_IMAGE_0_ID
#define FLASH_AREA_IMAGE_SECONDARY DT_FLASH_AREA_IMAGE_1_ID
#define FLASH_AREA_IMAGE_SCRATCH DT_FLASH_AREA_IMAGE_SCRATCH_ID
#endif /* CONFIG_TRUSTED_EXECUTION_NONSECURE */

#define COPY_DONE_OFFS(bank_area) ((bank_area)->fa_size -\
				   BOOT_MAGIC_SZ - BOOT_MAX_ALIGN * 2)

#define IMAGE_OK_OFFS(bank_area) ((bank_area)->fa_size - BOOT_MAGIC_SZ -\
				  BOOT_MAX_ALIGN)
#define MAGIC_OFFS(bank_area) ((bank_area)->fa_size - BOOT_MAGIC_SZ)

static const u32_t boot_img_magic[4] = {
	0xf395c277,
	0x7fefd260,
	0x0f505235,
	0x8079b62c,
};

struct boot_swap_table {
	/** For each field, a value of 0 means "any". */
	u8_t magic_primary_slot;
	u8_t magic_secondary_slot;
	u8_t image_ok_primary_slot;
	u8_t image_ok_secondary_slot;
	u8_t copy_done_primary_slot;

	u8_t swap_type;
};

/** Represents the management state of a single image slot. */
struct boot_swap_state {
	u8_t magic;  /* One of the BOOT_MAGIC_[...] values. */
	u8_t copy_done;
	u8_t image_ok;
};

/**
 * This set of tables maps image trailer contents to swap operation type.
 * When searching for a match, these tables must be iterated sequentially.
 */
static const struct boot_swap_table boot_swap_tables[] = {
	{
		/*          | slot-0     | slot-1     |
		 *----------+------------+------------|
		 *    magic | Any        | Good       |
		 * image-ok | Any        | Unset      |
		 * ---------+------------+------------+
		 * swap: test                         |
		 * -----------------------------------'
		 */
		.magic_primary_slot =      0,
		.magic_secondary_slot =    BOOT_MAGIC_GOOD,
		.image_ok_primary_slot =   0,
		.image_ok_secondary_slot = 0xff,
		.copy_done_primary_slot =  0,
		.swap_type =               BOOT_SWAP_TYPE_TEST,
	},
	{
		/*          | slot-0     | slot-1     |
		 *----------+------------+------------|
		 *    magic | Any        | Good       |
		 * image-ok | Any        | 0x01       |
		 * ---------+------------+------------+
		 * swap: permanent                    |
		 * -----------------------------------'
		 */
		.magic_primary_slot =      0,
		.magic_secondary_slot =    BOOT_MAGIC_GOOD,
		.image_ok_primary_slot =   0,
		.image_ok_secondary_slot = 0x01,
		.copy_done_primary_slot =  0,
		.swap_type =               BOOT_SWAP_TYPE_PERM,
	},
	{
		/*          | slot-0     | slot-1     |
		 *----------+------------+------------|
		 *    magic | Good       | Unset      |
		 * image-ok | Unset      | Any        |
		 * ---------+------------+------------+
		 * swap: revert (test image running)  |
		 * -----------------------------------'
		 */
		.magic_primary_slot =      BOOT_MAGIC_GOOD,
		.magic_secondary_slot =    BOOT_MAGIC_UNSET,
		.image_ok_primary_slot =   0xff,
		.image_ok_secondary_slot = 0,
		.copy_done_primary_slot =  0x01,
		.swap_type =               BOOT_SWAP_TYPE_REVERT,
	},
};
#define BOOT_SWAP_TABLES_COUNT (ARRAY_SIZE(boot_swap_tables))

static int boot_flag_offs(int flag, const struct flash_area *fa, u32_t *offs)
{
	switch (flag) {
	case BOOT_FLAG_COPY_DONE:
		*offs = COPY_DONE_OFFS(fa);
		return 0;
	case BOOT_FLAG_IMAGE_OK:
		*offs = IMAGE_OK_OFFS(fa);
		return 0;
	default:
		return -ENOTSUP;
	}
}

static int boot_flag_write(int flag, u8_t bank_id)
{
	const struct flash_area *fa;
	u8_t buf[FLASH_MIN_WRITE_SIZE];
	u32_t offs;
	int rc;

	rc = flash_area_open(bank_id, &fa);
	if (rc) {
		return rc;
	}

	rc = boot_flag_offs(flag, fa, &offs);
	if (rc != 0) {
		flash_area_close(fa);
		return rc;
	}

	(void)memset(buf, BOOT_FLAG_UNSET, sizeof(buf));
	buf[0] = BOOT_FLAG_SET;

	rc = flash_area_write(fa, offs, buf, sizeof(buf));
	flash_area_close(fa);

	return rc;
}

static int boot_flag_read(int flag, u8_t bank_id)
{
	const struct flash_area *fa;
	u32_t offs;
	int rc;
	u8_t flag_val;

	rc = flash_area_open(bank_id, &fa);
	if (rc) {
		return rc;
	}

	rc = boot_flag_offs(flag, fa, &offs);
	if (rc != 0) {
		flash_area_close(fa);
		return rc;
	}

	rc = flash_area_read(fa, offs, &flag_val, sizeof(flag_val));
	if (rc != 0) {
		return rc;
	}

	return flag_val;
}

static int boot_image_ok_read(u8_t bank_id)
{
	return boot_flag_read(BOOT_FLAG_IMAGE_OK, bank_id);
}

static int boot_image_ok_write(u8_t bank_id)
{
	return boot_flag_write(BOOT_FLAG_IMAGE_OK, bank_id);
}

static int boot_copy_done_read(u8_t bank_id)
{
	return boot_flag_read(BOOT_FLAG_COPY_DONE, bank_id);
}

static int boot_magic_write(u8_t bank_id)
{
	const struct flash_area *fa;
	u32_t offs;
	int rc;

	rc = flash_area_open(bank_id, &fa);
	if (rc) {
		return rc;
	}

	offs = MAGIC_OFFS(fa);

	rc = flash_area_write(fa, offs, boot_img_magic, BOOT_MAGIC_SZ);
	flash_area_close(fa);

	return rc;
}

static int boot_read_v1_header(u8_t area_id,
			       struct mcuboot_v1_raw_header *v1_raw)
{
	const struct flash_area *fa;
	int rc;

	rc = flash_area_open(area_id, &fa);
	if (rc) {
		return rc;
	}

	/*
	 * Read and sanity-check the raw header.
	 */
	rc = flash_area_read(fa, 0, v1_raw, sizeof(*v1_raw));
	flash_area_close(fa);
	if (rc) {
		return rc;
	}

	v1_raw->header_magic = sys_le32_to_cpu(v1_raw->header_magic);
	v1_raw->image_load_address =
		sys_le32_to_cpu(v1_raw->image_load_address);
	v1_raw->header_size = sys_le16_to_cpu(v1_raw->header_size);
	v1_raw->image_size = sys_le32_to_cpu(v1_raw->image_size);
	v1_raw->image_flags = sys_le32_to_cpu(v1_raw->image_flags);
	v1_raw->version.revision =
		sys_le16_to_cpu(v1_raw->version.revision);
	v1_raw->version.build_num =
		sys_le32_to_cpu(v1_raw->version.build_num);

	/*
	 * Sanity checks.
	 *
	 * Larger values in header_size than BOOT_HEADER_SIZE_V1 are
	 * possible, e.g. if Zephyr was linked with
	 * CONFIG_TEXT_SECTION_OFFSET > BOOT_HEADER_SIZE_V1.
	 */
	if ((v1_raw->header_magic != BOOT_HEADER_MAGIC_V1) ||
	    (v1_raw->header_size < BOOT_HEADER_SIZE_V1)) {
		return -EIO;
	}

	return 0;
}

int boot_read_bank_header(u8_t area_id,
			  struct mcuboot_img_header *header,
			  size_t header_size)
{
	int rc;
	struct mcuboot_v1_raw_header v1_raw;
	struct mcuboot_img_sem_ver *sem_ver;
	size_t v1_min_size = (sizeof(u32_t) +
			      sizeof(struct mcuboot_img_header_v1));

	/*
	 * Only version 1 image headers are supported.
	 */
	if (header_size < v1_min_size) {
		return -ENOMEM;
	}
	rc = boot_read_v1_header(area_id, &v1_raw);
	if (rc) {
		return rc;
	}

	/*
	 * Copy just the fields we care about into the return parameter.
	 *
	 * - header_magic:       skip (only used to check format)
	 * - image_load_address: skip (only matters for PIC code)
	 * - header_size:        skip (only used to check format)
	 * - image_size:         include
	 * - image_flags:        skip (all unsupported or not relevant)
	 * - version:            include
	 */
	header->mcuboot_version = 1U;
	header->h.v1.image_size = v1_raw.image_size;
	sem_ver = &header->h.v1.sem_ver;
	sem_ver->major = v1_raw.version.major;
	sem_ver->minor = v1_raw.version.minor;
	sem_ver->revision = v1_raw.version.revision;
	sem_ver->build_num = v1_raw.version.build_num;
	return 0;
}

static int boot_magic_code_check(const u32_t *magic)
{
	int i;

	if (memcmp(magic, boot_img_magic, sizeof(boot_img_magic)) == 0) {
		return BOOT_MAGIC_GOOD;
	}

	for (i = 0; i < ARRAY_SIZE(boot_img_magic); i++) {
		if (magic[i] != 0xffffffff) {
			return BOOT_MAGIC_BAD;
		}
	}

	return BOOT_MAGIC_UNSET;
}

static int boot_magic_state_read(u8_t bank_id)
{
	const struct flash_area *fa;
	u32_t magic[(sizeof(u32_t) - 1 + BOOT_MAGIC_SZ) / sizeof(u32_t)];
	u32_t offs;
	int rc;

	rc = flash_area_open(bank_id, &fa);
	if (rc) {
		return rc;
	}

	offs = MAGIC_OFFS(fa);
	rc = flash_area_read(fa, offs, magic, BOOT_MAGIC_SZ);
	flash_area_close(fa);

	if (rc != 0) {
		return rc;
	}

	return boot_magic_code_check(magic);
}

static int boot_read_swap_state(u8_t bank_id, struct boot_swap_state *state)
{
	int rc;

	rc = boot_magic_state_read(bank_id);
	if (rc < 0) {
		return rc;
	}
	state->magic = rc;

	if (bank_id != FLASH_AREA_IMAGE_SCRATCH) {
		rc = boot_copy_done_read(bank_id);
		if (rc < 0) {
			return rc;
		}
		state->copy_done = rc;
	}

	rc = boot_image_ok_read(bank_id);
	if (rc < 0) {
		return rc;
	}
	state->image_ok = rc;

	return 0;
}

int mcuboot_swap_type(void)
{
	const struct boot_swap_table *table;
	struct boot_swap_state state_primary_slot;
	struct boot_swap_state state_secondary_slot;
	int rc;
	int i;

	rc = boot_read_swap_state(FLASH_AREA_IMAGE_PRIMARY,
				  &state_primary_slot);
	if (rc != 0) {
		return rc;
	}

	rc = boot_read_swap_state(FLASH_AREA_IMAGE_SECONDARY,
				  &state_secondary_slot);
	if (rc != 0) {
		return rc;
	}

	for (i = 0; i < BOOT_SWAP_TABLES_COUNT; i++) {
		table = boot_swap_tables + i;

		if ((table->magic_primary_slot == 0U ||
		     table->magic_primary_slot == state_primary_slot.magic)
		    &&
		    (table->magic_secondary_slot == 0U ||
		     table->magic_secondary_slot == state_secondary_slot.magic)
		    &&
		    (table->image_ok_primary_slot == 0U ||
		     table->image_ok_primary_slot ==
		     state_primary_slot.image_ok)
		    &&
		    (table->image_ok_secondary_slot == 0U ||
		     table->image_ok_secondary_slot ==
		     state_secondary_slot.image_ok)
		    &&
		    (table->copy_done_primary_slot == 0U ||
		     table->copy_done_primary_slot ==
		     state_primary_slot.copy_done)) {

			assert(table->swap_type == BOOT_SWAP_TYPE_TEST ||
			       table->swap_type == BOOT_SWAP_TYPE_PERM ||
			       table->swap_type == BOOT_SWAP_TYPE_REVERT);
			return table->swap_type;
		}
	}

	return BOOT_SWAP_TYPE_NONE;
}

int boot_request_upgrade(int permanent)
{
	int rc;

	rc = boot_magic_write(FLASH_AREA_IMAGE_SECONDARY);
	if (rc == 0 && permanent) {
		rc = boot_image_ok_write(FLASH_AREA_IMAGE_SECONDARY);
	}

	return rc;
}

bool boot_is_img_confirmed(void)
{
	return boot_image_ok_read(FLASH_AREA_IMAGE_PRIMARY) == BOOT_FLAG_SET;
}

int boot_write_img_confirmed(void)
{
	int rc;

	if (boot_image_ok_read(FLASH_AREA_IMAGE_PRIMARY) != BOOT_FLAG_UNSET) {
		/* Already confirmed. */
		return 0;
	}

	rc = boot_image_ok_write(FLASH_AREA_IMAGE_PRIMARY);

	return rc;
}

int boot_erase_img_bank(u8_t area_id)
{
	const struct flash_area *fa;
	int rc;

	rc = flash_area_open(area_id, &fa);
	if (rc) {
		return rc;
	}

	rc = flash_area_erase(fa, 0, fa->fa_size);

	flash_area_close(fa);

	return rc;
}
