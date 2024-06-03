/*
 * Copyright (c) 2023 Codecoup
 * Copyright (c) 2024 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <zephyr/bluetooth/audio/audio.h>
#include <zephyr/bluetooth/audio/bap.h>
#include <zephyr/sys/slist.h>

#include "bap_endpoint.h"
#include "ztest_assert.h"

bool bt_bap_ep_is_unicast_client(const struct bt_bap_ep *ep)
{
	return false;
}

int bt_bap_unicast_client_config(struct bt_bap_stream *stream,
				 const struct bt_audio_codec_cfg *codec_cfg)
{
	if (stream == NULL || stream->ep == NULL || codec_cfg == NULL) {
		return -EINVAL;
	}

	stream->ep->status.state = BT_BAP_EP_STATE_CODEC_CONFIGURED;

	if (stream->ops != NULL && stream->ops->configured != NULL) {
		const struct bt_audio_codec_qos_pref pref = {0};

		stream->ops->configured(stream, &pref);
	}

	return 0;
}

int bt_bap_unicast_client_qos(struct bt_conn *conn, struct bt_bap_unicast_group *group)
{
	struct bt_bap_stream *stream;

	if (conn == NULL || group == NULL) {
		return -EINVAL;
	}

	SYS_SLIST_FOR_EACH_CONTAINER(&group->streams, stream, _node) {
		if (stream->conn == conn) {
			stream->ep->status.state = BT_BAP_EP_STATE_QOS_CONFIGURED;

			if (stream->ops != NULL && stream->ops->qos_set != NULL) {
				stream->ops->qos_set(stream);
			}
		}
	}

	return 0;
}

int bt_bap_unicast_client_enable(struct bt_bap_stream *stream, const uint8_t meta[],
				 size_t meta_len)
{
	if (stream == NULL) {
		return -EINVAL;
	}

	stream->ep->status.state = BT_BAP_EP_STATE_ENABLING;

	if (stream->ops != NULL && stream->ops->enabled != NULL) {
		stream->ops->enabled(stream);
	}

	return 0;
}

int bt_bap_unicast_client_metadata(struct bt_bap_stream *stream, const uint8_t meta[],
				   size_t meta_len)
{
	if (stream == NULL) {
		return -EINVAL;
	}

	if (stream->ops != NULL && stream->ops->metadata_updated != NULL) {
		stream->ops->metadata_updated(stream);
	}

	return 0;
}

int bt_bap_unicast_client_connect(struct bt_bap_stream *stream)
{
	if (stream == NULL) {
		return -EINVAL;
	}

	if (stream->ops != NULL && stream->ops->connected != NULL) {
		stream->ops->connected(stream);
	}

	if (stream->ep != NULL && stream->ep->dir == BT_AUDIO_DIR_SINK) {
		/* Mocking that the unicast server automatically starts the stream */
		stream->ep->status.state = BT_BAP_EP_STATE_STREAMING;

		if (stream->ops != NULL && stream->ops->started != NULL) {
			stream->ops->started(stream);
		}
	}

	return 0;
}

int bt_bap_unicast_client_start(struct bt_bap_stream *stream)
{
	/* As per the ASCS spec, only source streams can be started by the client */
	if (stream == NULL || stream->ep == NULL || stream->ep->dir == BT_AUDIO_DIR_SINK) {
		return -EINVAL;
	}

	stream->ep->status.state = BT_BAP_EP_STATE_STREAMING;

	if (stream->ops != NULL && stream->ops->started != NULL) {
		stream->ops->started(stream);
	}

	return 0;
}

int bt_bap_unicast_client_disable(struct bt_bap_stream *stream)
{
	zassert_unreachable("Unexpected call to '%s()' occurred", __func__);
	return 0;
}

int bt_bap_unicast_client_stop(struct bt_bap_stream *stream)
{
	zassert_unreachable("Unexpected call to '%s()' occurred", __func__);
	return 0;
}

int bt_bap_unicast_client_release(struct bt_bap_stream *stream)
{
	zassert_unreachable("Unexpected call to '%s()' occurred", __func__);
	return 0;
}
