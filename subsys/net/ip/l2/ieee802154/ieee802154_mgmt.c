/*
 * Copyright (c) 2016 Intel Corporation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <errno.h>

#include <net/net_if.h>
#include <net/ieee802154_radio.h>
#include <net/ieee802154.h>

#include "ieee802154_frame.h"
#include "ieee802154_mgmt.h"

enum net_verdict ieee802154_handle_beacon(struct net_if *iface,
					  struct ieee802154_mpdu *mpdu)
{
	struct ieee802154_context *ctx = net_if_l2_data(iface);
	struct ieee802154_radio_api *radio =
		(struct ieee802154_radio_api *)iface->dev->driver_api;

	if (!ctx->scan_ctx) {
		return NET_DROP;
	}

	if (!mpdu->beacon->sf.association) {
		return NET_DROP;
	}

	k_sem_take(&ctx->res_lock, K_FOREVER);

	ctx->scan_ctx->pan_id = mpdu->mhr.src_addr->plain.pan_id;
	ctx->scan_ctx->lqi = radio->get_lqi(iface->dev);

	if (mpdu->mhr.fs->fc.src_addr_mode == IEEE802154_ADDR_MODE_SHORT) {
		ctx->scan_ctx->len = IEEE802154_SHORT_ADDR_LENGTH;
		ctx->scan_ctx->short_addr =
			mpdu->mhr.src_addr->plain.addr.short_addr;
	} else {
		ctx->scan_ctx->len = IEEE802154_EXT_ADDR_LENGTH;
		sys_memcpy_swap(ctx->scan_ctx->addr,
				mpdu->mhr.src_addr->plain.addr.ext_addr,
				IEEE802154_EXT_ADDR_LENGTH);
	}

	net_mgmt_event_notify(NET_EVENT_IEEE802154_SCAN_RESULT, iface);

	k_sem_give(&ctx->res_lock);

	return NET_OK;
}

static int ieee802154_cancel_scan(uint32_t mgmt_request, struct net_if *iface,
				  void *data, size_t len)
{
	struct ieee802154_context *ctx = net_if_l2_data(iface);

	ARG_UNUSED(data);
	ARG_UNUSED(len);

	ctx->scan_ctx = NULL;

	return 0;
}

NET_MGMT_REGISTER_REQUEST_HANDLER(NET_REQUEST_IEEE802154_CANCEL_SCAN,
				  ieee802154_cancel_scan);

static int ieee802154_scan(uint32_t mgmt_request, struct net_if *iface,
			   void *data, size_t len)
{
	struct ieee802154_radio_api *radio =
		(struct ieee802154_radio_api *)iface->dev->driver_api;
	struct ieee802154_context *ctx = net_if_l2_data(iface);
	struct ieee802154_req_params *scan =
		(struct ieee802154_req_params *)data;
	uint8_t channel;
	int ret;

	if (ctx->scan_ctx) {
		return -EALREADY;
	}

	if (radio->start(iface->dev)) {
		return -EIO;
	}

	ctx->scan_ctx = scan;
	ret = 0;

	radio->set_pan_id(iface->dev, IEEE802154_BROADCAST_PAN_ID);

	/* ToDo: For now, we assume we are on 2.4Ghz
	 * (device will have to export capabilities) */
	for (channel = 11; channel <= 26; channel++) {
		if (IEEE802154_IS_CHAN_UNSCANNED(scan->channel_set, channel)) {
			continue;
		}

		scan->channel = channel;
		radio->set_channel(iface->dev, channel);

		/* Context aware sleep */
		k_sleep(scan->duration);

		if (!ctx->scan_ctx) {
			ret = -ECANCELED;
			break;
		}
	}

	/* Let's come back to context's settings */
	radio->set_pan_id(iface->dev, ctx->pan_id);
	radio->set_channel(iface->dev, ctx->channel);

	ctx->scan_ctx = NULL;

	return ret;
}

NET_MGMT_REGISTER_REQUEST_HANDLER(NET_REQUEST_IEEE802154_PASSIVE_SCAN,
				  ieee802154_scan);

static int ieee802154_set_ack(uint32_t mgmt_request, struct net_if *iface,
			      void *data, size_t len)
{
	struct ieee802154_context *ctx = net_if_l2_data(iface);

	ARG_UNUSED(data);
	ARG_UNUSED(len);

	if (mgmt_request == NET_REQUEST_IEEE802154_SET_ACK) {
		ctx->ack_requested = true;
	} else if (mgmt_request == NET_REQUEST_IEEE802154_UNSET_ACK) {
		ctx->ack_requested = false;
	}

	return 0;
}

NET_MGMT_REGISTER_REQUEST_HANDLER(NET_REQUEST_IEEE802154_SET_ACK,
				  ieee802154_set_ack);

NET_MGMT_REGISTER_REQUEST_HANDLER(NET_REQUEST_IEEE802154_UNSET_ACK,
				  ieee802154_set_ack);
