/*
 * Copyright (c) 2017 Nordic Semiconductor ASA
 * Copyright (c) 2017 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_MODULE_NAME fota_flash_block
#define LOG_LEVEL CONFIG_IMG_MANAGER_LOG_LEVEL
#include <logging/log.h>
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

#include <zephyr/types.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <dfu/flash_img.h>
#include <inttypes.h>

#ifdef CONFIG_IMG_ERASE_PROGRESSIVELY
#include <dfu/mcuboot.h>
#include <flash.h>
#endif

BUILD_ASSERT_MSG((CONFIG_IMG_BLOCK_BUF_SIZE % DT_FLASH_WRITE_BLOCK_SIZE == 0),
		 "CONFIG_IMG_BLOCK_BUF_SIZE is not a multiple of "
		 "DT_FLASH_WRITE_BLOCK_SIZE");

static bool flash_verify(const struct flash_area *fa, off_t offset,
			 u8_t *data, size_t len)
{
	size_t size;
	u32_t temp;
	int rc;

	while (len) {
		size = (len >= sizeof(temp)) ? sizeof(temp) : len;
		rc = flash_area_read(fa, offset, &temp, size);
		if (rc) {
			LOG_ERR("flash_read error %d offset=0x%08"PRIx32,
				rc, (u32_t)offset);
			break;
		}

		if (memcmp(data, &temp, size)) {
			LOG_ERR("offset=0x%08"PRIx32" VERIFY FAIL. "
				"expected: 0x%08x, actual: 0x%08x",
				(u32_t)offset, temp, UNALIGNED_GET(data));
			break;
		}
		len -= size;
		offset += size;
		data += size;
	}

	return (len == 0) ? true : false;
}

#ifdef CONFIG_IMG_ERASE_PROGRESSIVELY

static int flash_sector_from_off(struct flash_area const *fap, off_t off,
				 struct flash_sector *sector)
{
	struct flash_pages_info page;
	struct device *flash_dev;
	int rc = -ENODEV;

	flash_dev = flash_area_get_device(fap);
	if (flash_dev) {
		rc = flash_get_page_info_by_offs(flash_dev, off, &page);
		if (rc == 0) {
			sector->fs_off = page.start_offset;
			sector->fs_size = page.size;
		}
	}

	return rc;
}

/**
 * Erase the image slot progressively
 *
 * This function erases a flash page to which offset belongs if only this page
 * wasn't erased before.
 *
 * @param[in] ctx context of the image collection process.
 * @param[in] off offset from the beginning of the image flash area beginning
 *
 * @return  0 on success, negative errno code on fail.
 */
static int flash_progressive_erase(struct flash_img_context *ctx, off_t off)
{
	struct flash_sector sector;
	int rc;

	rc = flash_sector_from_off(ctx->flash_area, off, &sector);
	if (rc) {
		LOG_ERR("Unable to determine flash sector size");
	} else {
		if (ctx->off_last != sector.fs_off) {
			ctx->off_last = sector.fs_off;
			LOG_INF("Erasing sector at offset 0x%x", sector.fs_off);
			rc = flash_area_erase(ctx->flash_area, sector.fs_off,
					      sector.fs_size);
			if (rc) {
				LOG_ERR("Error %d while erasing sector", rc);
			}
		}
	}

	return rc;
}

#endif /* CONFIG_IMG_ERASE_PROGRESSIVELY */

static int flash_sync(struct flash_img_context *ctx)
{
	int rc = 0;

	if (ctx->buf_bytes < CONFIG_IMG_BLOCK_BUF_SIZE) {
		(void)memset(ctx->buf + ctx->buf_bytes, 0xFF,
			     CONFIG_IMG_BLOCK_BUF_SIZE - ctx->buf_bytes);
	}

#ifdef CONFIG_IMG_ERASE_PROGRESSIVELY
	flash_progressive_erase(ctx, ctx->bytes_written +
				CONFIG_IMG_BLOCK_BUF_SIZE);
#endif

	rc = flash_area_write(ctx->flash_area, ctx->bytes_written, ctx->buf,
			      CONFIG_IMG_BLOCK_BUF_SIZE);
	if (rc) {
		LOG_ERR("flash_write error %d offset=0x%08" PRIx32, rc,
			(u32_t)ctx->bytes_written);
		return rc;
	}

	if (!flash_verify(ctx->flash_area, ctx->bytes_written, ctx->buf,
			  CONFIG_IMG_BLOCK_BUF_SIZE)) {
		return -EIO;
	}

	ctx->bytes_written += ctx->buf_bytes;
	ctx->buf_bytes = 0U;

	return rc;
}

int flash_img_buffered_write(struct flash_img_context *ctx, u8_t *data,
			     size_t len, bool flush)
{
	int processed = 0;
	int rc = 0;
	int buf_empty_bytes;

	while ((len - processed) >
	       (buf_empty_bytes = CONFIG_IMG_BLOCK_BUF_SIZE - ctx->buf_bytes)) {
		memcpy(ctx->buf + ctx->buf_bytes, data + processed,
		       buf_empty_bytes);

		ctx->buf_bytes = CONFIG_IMG_BLOCK_BUF_SIZE;
		rc = flash_sync(ctx);

		if (rc) {
			return rc;
		}

		processed += buf_empty_bytes;
	}

	/* place rest of the data into ctx->buf */
	if (processed < len) {
		memcpy(ctx->buf + ctx->buf_bytes,
		       data + processed, len - processed);
		ctx->buf_bytes += len - processed;
	}

	if (!flush) {
		return rc;
	}

	if (ctx->buf_bytes > 0) {
		/* pad the rest of ctx->buf and write it out */
		rc = flash_sync(ctx);

		if (rc) {
			return rc;
		}
	}
#ifdef CONFIG_IMG_ERASE_PROGRESSIVELY
	/* erase the image trailer area if it was not erased */
	flash_progressive_erase(ctx,
				BOOT_TRAILER_IMG_STATUS_OFFS(ctx->flash_area));
#endif

	flash_area_close(ctx->flash_area);
	ctx->flash_area = NULL;

	return rc;
}

size_t flash_img_bytes_written(struct flash_img_context *ctx)
{
	return ctx->bytes_written;
}

int flash_img_init(struct flash_img_context *ctx)
{
	ctx->bytes_written = 0;
	ctx->buf_bytes = 0U;
#ifdef CONFIG_IMG_ERASE_PROGRESSIVELY
	ctx->off_last = -1;
#endif
	return flash_area_open(DT_FLASH_AREA_IMAGE_1_ID,
			       (const struct flash_area **)&(ctx->flash_area));
}
