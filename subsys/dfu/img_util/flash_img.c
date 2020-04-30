/*
 * Copyright (c) 2017, 2020 Nordic Semiconductor ASA
 * Copyright (c) 2017 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr/types.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <dfu/flash_img.h>
#include <storage/flash_map.h>
#include <storage/stream_flash.h>

#ifdef CONFIG_IMG_ERASE_PROGRESSIVELY
#include <dfu/mcuboot.h>
#endif

#include <devicetree.h>
/* FLASH_AREA_ID() values used below are auto-generated by DT */
#ifdef CONFIG_TRUSTED_EXECUTION_NONSECURE
#define FLASH_AREA_IMAGE_SECONDARY FLASH_AREA_ID(image_1_nonsecure)
#else
#define FLASH_AREA_IMAGE_SECONDARY FLASH_AREA_ID(image_1)
#endif /* CONFIG_TRUSTED_EXECUTION_NONSECURE */

#define FLASH_WRITE_BLOCK_SIZE \
	DT_PROP(DT_CHOSEN(zephyr_flash), write_block_size)

BUILD_ASSERT((CONFIG_IMG_BLOCK_BUF_SIZE % FLASH_WRITE_BLOCK_SIZE == 0),
	     "CONFIG_IMG_BLOCK_BUF_SIZE is not a multiple of "
	     "FLASH_WRITE_BLOCK_SIZE");

int flash_img_buffered_write(struct flash_img_context *ctx, const uint8_t *data,
			     size_t len, bool flush)
{
	int rc;

	rc = stream_flash_buffered_write(&ctx->stream, data, len, flush);
	if (!flush) {
		return rc;
	}

#ifdef CONFIG_IMG_ERASE_PROGRESSIVELY
	rc = stream_flash_erase_page(&ctx->stream,
				ctx->flash_area->fa_off +
				BOOT_TRAILER_IMG_STATUS_OFFS(ctx->flash_area));
	if (rc) {
		return rc;
	}
#endif

	flash_area_close(ctx->flash_area);
	ctx->flash_area = NULL;

	return rc;
}

size_t flash_img_bytes_written(struct flash_img_context *ctx)
{
	return stream_flash_bytes_written(&ctx->stream);
}

int flash_img_init_id(struct flash_img_context *ctx, uint8_t area_id)
{
	int rc;
	const struct device *flash_dev;

	rc = flash_area_open(area_id,
			       (const struct flash_area **)&(ctx->flash_area));
	if (rc) {
		return rc;
	}

	flash_dev = flash_area_get_device(ctx->flash_area);

	return stream_flash_init(&ctx->stream, flash_dev, ctx->buf,
			CONFIG_IMG_BLOCK_BUF_SIZE, ctx->flash_area->fa_off,
			ctx->flash_area->fa_size, NULL);
}

int flash_img_init(struct flash_img_context *ctx)
{
	return flash_img_init_id(ctx, FLASH_AREA_IMAGE_SECONDARY);
}
