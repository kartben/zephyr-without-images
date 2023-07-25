/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/sys/byteorder.h>
#include <zephyr/types.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/audio/audio.h>
#include <zephyr/bluetooth/audio/pbp.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/check.h>

LOG_MODULE_REGISTER(bt_pbp, CONFIG_BT_PBP_LOG_LEVEL);

int bt_pbp_get_announcement(const uint8_t meta[], size_t meta_len,
			    enum bt_pbp_announcement_feature features,
			    struct net_buf_simple *pba_data_buf)
{
	CHECKIF(pba_data_buf == NULL) {
		LOG_DBG("No buffer provided for advertising data!\n");

		return -EINVAL;
	}

	CHECKIF((meta == NULL && meta_len != 0) || (meta != NULL && meta_len == 0)) {
		LOG_DBG("Invalid metadata combination: %p %zu", meta, meta_len);

		return -EINVAL;
	}

	CHECKIF(pba_data_buf->size < (meta_len + BT_PBP_MIN_PBA_SIZE)) {
		LOG_DBG("Buffer size needs to be at least %d!\n", meta_len + BT_PBP_MIN_PBA_SIZE);

		return -EINVAL;
	}

	/* Fill Announcement data */
	net_buf_simple_add_le16(pba_data_buf, BT_UUID_PBA_VAL);
	net_buf_simple_add_u8(pba_data_buf, features);
	net_buf_simple_add_u8(pba_data_buf, meta_len);
	net_buf_simple_add_mem(pba_data_buf, meta, meta_len);

	return 0;
}

uint8_t bt_pbp_parse_announcement(struct bt_data *data,
				  enum bt_pbp_announcement_feature *features,
				  uint8_t *meta)
{
	uint8_t meta_len = 0;
	struct bt_uuid_16 adv_uuid;

	CHECKIF(!data || !features || !meta) {
		return -EINVAL;
	}

	if (data->data_len < BT_PBP_MIN_PBA_SIZE) {
		return -EBADMSG;
	}

	if (data->type != BT_DATA_SVC_DATA16) {
		return -EINVAL;
	}

	if (!bt_uuid_create(&adv_uuid.uuid, data->data, BT_UUID_SIZE_16)) {
		return -EINVAL;
	}

	if (bt_uuid_cmp(&adv_uuid.uuid, BT_UUID_PBA)) {
		return -EBADMSG;
	}

	/* Copy source features, metadata length and metadata from the Announcement */
	*features = data->data[BT_UUID_SIZE_16];
	meta_len = data->data[BT_UUID_SIZE_16 + sizeof(uint8_t)];
	memcpy(meta, data->data + BT_PBP_MIN_PBA_SIZE, meta_len);

	return meta_len;
}
