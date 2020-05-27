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
#include <drivers/flash.h>
#include <storage/flash_map.h>
#include <zephyr.h>
#include <init.h>

#include <sys/__assert.h>
#include <sys/byteorder.h>
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
#define BOOT_FLAG_SET   1
#define BOOT_FLAG_BAD   2
#define BOOT_FLAG_UNSET 3
#define BOOT_FLAG_ANY   4  /* NOTE: control only, not dependent on sector */

/*
 * Raw (on-flash) representation of the v1 image header.
 */
struct mcuboot_v1_raw_header {
	uint32_t header_magic;
	uint32_t image_load_address;
	uint16_t header_size;
	uint16_t pad;
	uint32_t image_size;
	uint32_t image_flags;
	struct {
		uint8_t major;
		uint8_t minor;
		uint16_t revision;
		uint32_t build_num;
	} version;
	uint32_t pad2;
} __packed;

/*
 * End of strict defines
 */

#define BOOT_MAGIC_GOOD    1
#define BOOT_MAGIC_BAD     2
#define BOOT_MAGIC_UNSET   3
#define BOOT_MAGIC_ANY     4  /* NOTE: control only, not dependent on sector */
#define BOOT_MAGIC_NOTGOOD 5  /* NOTE: control only, not dependent on sector */

#define BOOT_FLAG_IMAGE_OK  0
#define BOOT_FLAG_COPY_DONE 1

#define FLASH_MIN_WRITE_SIZE \
	DT_PROP(DT_CHOSEN(zephyr_flash), write_block_size)

/* FLASH_AREA_ID() values used below are auto-generated by DT */
#ifdef CONFIG_TRUSTED_EXECUTION_NONSECURE
#define FLASH_AREA_IMAGE_PRIMARY FLASH_AREA_ID(image_0_nonsecure)
#define FLASH_AREA_IMAGE_SECONDARY FLASH_AREA_ID(image_1_nonsecure)
#else
#define FLASH_AREA_IMAGE_PRIMARY FLASH_AREA_ID(image_0)
#define FLASH_AREA_IMAGE_SECONDARY FLASH_AREA_ID(image_1)
#endif /* CONFIG_TRUSTED_EXECUTION_NONSECURE */

#if FLASH_AREA_LABEL_EXISTS(image_scratch)
#define FLASH_AREA_IMAGE_SCRATCH FLASH_AREA_ID(image_scratch)
#endif

#ifdef CONFIG_MCUBOOT_TRAILER_SWAP_TYPE
#define SWAP_TYPE_OFFS(bank_area) ((bank_area)->fa_size -\
				   BOOT_MAGIC_SZ - BOOT_MAX_ALIGN * 3)
#endif

#define COPY_DONE_OFFS(bank_area) ((bank_area)->fa_size -\
				   BOOT_MAGIC_SZ - BOOT_MAX_ALIGN * 2)

#define IMAGE_OK_OFFS(bank_area) ((bank_area)->fa_size - BOOT_MAGIC_SZ -\
				  BOOT_MAX_ALIGN)
#define MAGIC_OFFS(bank_area) ((bank_area)->fa_size - BOOT_MAGIC_SZ)

static const uint32_t boot_img_magic[4] = {
	0xf395c277,
	0x7fefd260,
	0x0f505235,
	0x8079b62c,
};

#define BOOT_MAGIC_ARR_SZ ARRAY_SIZE(boot_img_magic)

struct boot_swap_table {
	/** For each field, a value of 0 means "any". */
	uint8_t magic_primary_slot;
	uint8_t magic_secondary_slot;
	uint8_t image_ok_primary_slot;
	uint8_t image_ok_secondary_slot;
	uint8_t copy_done_primary_slot;

	uint8_t swap_type;
};

/** Represents the management state of a single image slot. */
struct boot_swap_state {
	uint8_t magic;     /* One of the BOOT_MAGIC_[...] values. */
	uint8_t swap_type; /* One of the BOOT_SWAP_TYPE_[...] values. */
	uint8_t copy_done; /* One of the BOOT_FLAG_[...] values. */
	uint8_t image_ok;  /* One of the BOOT_FLAG_[...] values. */
};

/**
 * This set of tables maps image trailer contents to swap operation type.
 * When searching for a match, these tables must be iterated sequentially.
 *
 * NOTE: the table order is very important. The settings in the secondary
 * slot always are priority to the primary slot and should be located
 * earlier in the table.
 *
 * The table lists only states where there is action needs to be taken by
 * the bootloader, as in starting/finishing a swap operation.
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
		.magic_primary_slot =      BOOT_MAGIC_ANY,
		.magic_secondary_slot =    BOOT_MAGIC_GOOD,
		.image_ok_primary_slot =   BOOT_FLAG_ANY,
		.image_ok_secondary_slot = BOOT_FLAG_UNSET,
		.copy_done_primary_slot =  BOOT_FLAG_ANY,
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
		.magic_primary_slot =      BOOT_MAGIC_ANY,
		.magic_secondary_slot =    BOOT_MAGIC_GOOD,
		.image_ok_primary_slot =   BOOT_FLAG_ANY,
		.image_ok_secondary_slot = BOOT_FLAG_SET,
		.copy_done_primary_slot =  BOOT_FLAG_ANY,
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
		.image_ok_primary_slot =   BOOT_FLAG_UNSET,
		.image_ok_secondary_slot = BOOT_FLAG_ANY,
		.copy_done_primary_slot =  BOOT_FLAG_SET,
		.swap_type =               BOOT_SWAP_TYPE_REVERT,
	},
};
#define BOOT_SWAP_TABLES_COUNT (ARRAY_SIZE(boot_swap_tables))

static int boot_magic_decode(const uint32_t *magic)
{
	if (memcmp(magic, boot_img_magic, BOOT_MAGIC_SZ) == 0) {
		return BOOT_MAGIC_GOOD;
	}

	return BOOT_MAGIC_BAD;
}

static int boot_flag_decode(uint8_t flag)
{
	if (flag != BOOT_FLAG_SET) {
		return BOOT_FLAG_BAD;
	}

	return BOOT_FLAG_SET;
}

/* TODO: this function should be moved to flash_area api in future */
uint8_t flash_area_erased_val(const struct flash_area *fa)
{
	#define ERASED_VAL 0xff

	(void)fa;
	return ERASED_VAL;
}

/* TODO: this function should be moved to flash_area api in future */
int flash_area_read_is_empty(const struct flash_area *fa, uint32_t off,
	void *dst, uint32_t len)
{
	const uint8_t erase_val = flash_area_erased_val(fa);
	uint8_t *u8dst;
	uint8_t i;
	int rc;

	rc = flash_area_read(fa, off, dst, len);
	if (rc) {
		return rc;
	}

	for (i = 0, u8dst = (uint8_t *)dst; i < len; i++) {
		if (u8dst[i] != erase_val) {
			return 0;
		}
	}

	return 1;
}

static int erased_flag_val(uint8_t bank_id)
{
	const struct flash_area *fa;
	int rc;

	rc = flash_area_open(bank_id, &fa);
	if (rc) {
		return -EINVAL;
	}
	return flash_area_erased_val(fa);
}

/**
 * Determines if a status source table is satisfied by the specified magic
 * code.
 *
 * @param tbl_val               A magic field from a status source table.
 * @param val                   The magic value in a trailer, encoded as a
 *                                  BOOT_MAGIC_[...].
 *
 * @return                      1 if the two values are compatible;
 *                              0 otherwise.
 */
int boot_magic_compatible_check(uint8_t tbl_val, uint8_t val)
{
	switch (tbl_val) {
	case BOOT_MAGIC_ANY:
		return 1;

	case BOOT_MAGIC_NOTGOOD:
		return val != BOOT_MAGIC_GOOD;

	default:
		return tbl_val == val;
	}
}

static int boot_flag_offs(int flag, const struct flash_area *fa, uint32_t *offs)
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

static int boot_write_trailer_byte(const struct flash_area *fa, uint32_t off,
				   uint8_t val)
{
	uint8_t buf[BOOT_MAX_ALIGN];
	uint8_t align;
	uint8_t erased_val;
	int rc;

	align = flash_area_align(fa);
	assert(align <= BOOT_MAX_ALIGN);
	erased_val = flash_area_erased_val(fa);
	memset(buf, erased_val, BOOT_MAX_ALIGN);
	buf[0] = val;

	rc = flash_area_write(fa, off, buf, align);
	if (rc != 0) {
		return -EIO;
	}

	return 0;
}

static int boot_flag_write(int flag, uint8_t bank_id)
{
	const struct flash_area *fa;
	uint32_t offs;
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

	rc = boot_write_trailer_byte(fa, offs, BOOT_FLAG_SET);
	flash_area_close(fa);

	return rc;
}

static int boot_flag_read(int flag, uint8_t bank_id)
{
	const struct flash_area *fa;
	uint32_t offs;
	int rc;
	uint8_t flag_val;

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

static int boot_image_ok_read(uint8_t bank_id)
{
	return boot_flag_read(BOOT_FLAG_IMAGE_OK, bank_id);
}

static int boot_image_ok_write(uint8_t bank_id)
{
	return boot_flag_write(BOOT_FLAG_IMAGE_OK, bank_id);
}

static int boot_magic_write(uint8_t bank_id)
{
	const struct flash_area *fa;
	uint32_t offs;
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

#ifdef CONFIG_MCUBOOT_TRAILER_SWAP_TYPE
static int boot_swap_type_write(uint8_t bank_id, uint8_t swap_type)
{
	const struct flash_area *fa;
	uint32_t offs;
	int rc;

	rc = flash_area_open(bank_id, &fa);
	if (rc) {
		return rc;
	}

	offs = SWAP_TYPE_OFFS(fa);

	rc = boot_write_trailer_byte(fa, offs, swap_type);
	flash_area_close(fa);

	return rc;
}
#endif

static int boot_read_v1_header(uint8_t area_id,
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

int boot_read_bank_header(uint8_t area_id,
			  struct mcuboot_img_header *header,
			  size_t header_size)
{
	int rc;
	struct mcuboot_v1_raw_header v1_raw;
	struct mcuboot_img_sem_ver *sem_ver;
	size_t v1_min_size = (sizeof(uint32_t) +
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

static int boot_read_swap_state(const struct flash_area *fa,
				struct boot_swap_state *state)
{
	uint32_t magic[BOOT_MAGIC_ARR_SZ];
	uint32_t off;
	int rc;

	off = MAGIC_OFFS(fa);
	rc = flash_area_read_is_empty(fa, off, magic, BOOT_MAGIC_SZ);
	if (rc < 0) {
		return -EIO;
	}
	if (rc == 1) {
		state->magic = BOOT_MAGIC_UNSET;
	} else {
		state->magic = boot_magic_decode(magic);
	}

#ifdef CONFIG_MCUBOOT_TRAILER_SWAP_TYPE
	off = SWAP_TYPE_OFFS(fa);
	rc = flash_area_read_is_empty(fa, off, &state->swap_type,
				      sizeof(state->swap_type));
	if (rc < 0) {
		return -EIO;
	}
	if (rc == 1 || state->swap_type > BOOT_SWAP_TYPE_REVERT) {
		state->swap_type = BOOT_SWAP_TYPE_NONE;
	}

	off = COPY_DONE_OFFS(fa);
	rc = flash_area_read_is_empty(fa, off, &state->copy_done,
				      sizeof(state->copy_done));
	if (rc < 0) {
		return -EIO;
	}
	if (rc == 1) {
		state->copy_done = BOOT_FLAG_UNSET;
	} else {
		state->copy_done = boot_flag_decode(state->copy_done);
	}
#else
#ifdef FLASH_AREA_IMAGE_SCRATCH
	if (fa->fa_id != FLASH_AREA_IMAGE_SCRATCH) {
#endif
		off = COPY_DONE_OFFS(fa);
		rc = flash_area_read_is_empty(fa, off, &state->copy_done,
					      sizeof(state->copy_done));
		if (rc < 0) {
			return -EIO;
		}
		if (rc == 1) {
			state->copy_done = BOOT_FLAG_UNSET;
		} else {
			state->copy_done = boot_flag_decode(state->copy_done);
		}
#ifdef FLASH_AREA_IMAGE_SCRATCH
	}
#endif
#endif

	off = IMAGE_OK_OFFS(fa);
	rc = flash_area_read_is_empty(fa, off, &state->image_ok,
				  sizeof(state->image_ok));
	if (rc < 0) {
		return -EIO;
	}
	if (rc == 1) {
		state->image_ok = BOOT_FLAG_UNSET;
	} else {
		state->image_ok = boot_flag_decode(state->image_ok);
	}

	return 0;
}

/**
 * Reads the image trailer from the scratch area.
 */
int
boot_read_swap_state_by_id(int flash_area_id, struct boot_swap_state *state)
{
	const struct flash_area *fap;
	int rc;

	switch (flash_area_id) {
#ifdef FLASH_AREA_IMAGE_SCRATCH
	case FLASH_AREA_IMAGE_SCRATCH:
#endif
	case FLASH_AREA_IMAGE_PRIMARY:
	case FLASH_AREA_IMAGE_SECONDARY:
		rc = flash_area_open(flash_area_id, &fap);
		if (rc != 0) {
			return -EIO;
		}
		break;
	default:
		return -EINVAL;
	}

	rc = boot_read_swap_state(fap, state);
	flash_area_close(fap);
	return rc;
}

/* equivalent of boot_swap_type() in mcuboot bootutil_misc.c */
int mcuboot_swap_type(void)
{
	const struct boot_swap_table *table;
	struct boot_swap_state primary_slot;
	struct boot_swap_state secondary_slot;
	int rc;
	size_t i;

	rc = boot_read_swap_state_by_id(FLASH_AREA_IMAGE_PRIMARY,
					&primary_slot);
	if (rc) {
		return rc;
	}

	rc = boot_read_swap_state_by_id(FLASH_AREA_IMAGE_SECONDARY,
					&secondary_slot);
	if (rc) {
		return rc;
	}

	for (i = 0; i < BOOT_SWAP_TABLES_COUNT; i++) {
		table = boot_swap_tables + i;

		if (boot_magic_compatible_check(table->magic_primary_slot,
						primary_slot.magic)
		    &&
		    boot_magic_compatible_check(table->magic_secondary_slot,
						secondary_slot.magic)
		    &&
		    (table->image_ok_primary_slot == BOOT_FLAG_ANY   ||
		     table->image_ok_primary_slot == primary_slot.image_ok)
		    &&
		    (table->image_ok_secondary_slot == BOOT_FLAG_ANY ||
		     table->image_ok_secondary_slot == secondary_slot.image_ok)
		    &&
		    (table->copy_done_primary_slot == BOOT_FLAG_ANY  ||
		     table->copy_done_primary_slot == primary_slot.copy_done)) {

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
#ifdef CONFIG_MCUBOOT_TRAILER_SWAP_TYPE
	uint8_t swap_type;
#endif
	int rc;

	rc = boot_magic_write(FLASH_AREA_IMAGE_SECONDARY);
	if (rc) {
		goto op_end;
	}

	if (permanent) {
		rc = boot_image_ok_write(FLASH_AREA_IMAGE_SECONDARY);

#ifdef CONFIG_MCUBOOT_TRAILER_SWAP_TYPE
		if (rc) {
			goto op_end;
		}

		swap_type = BOOT_SWAP_TYPE_PERM;
	} else {
		swap_type = BOOT_SWAP_TYPE_TEST;
	}

	rc = boot_swap_type_write(FLASH_AREA_IMAGE_SECONDARY, swap_type);
#else
	}
#endif
op_end:
	return rc;
}

bool boot_is_img_confirmed(void)
{
	return boot_image_ok_read(FLASH_AREA_IMAGE_PRIMARY) == BOOT_FLAG_SET;
}

int boot_write_img_confirmed(void)
{
	int rc;

	if (boot_image_ok_read(FLASH_AREA_IMAGE_PRIMARY) !=
	    erased_flag_val(FLASH_AREA_IMAGE_PRIMARY)) {
		/* Already confirmed. */
		return 0;
	}

	rc = boot_image_ok_write(FLASH_AREA_IMAGE_PRIMARY);

	return rc;
}

int boot_erase_img_bank(uint8_t area_id)
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
