/*
 * Copyright (c) 2021 Xiaomi Corporation
 * Copyright (c) 2018 Nordic Semiconductor ASA
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <debug/stack.h>

#include <net/buf.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/mesh.h>

#define BT_DBG_ENABLED IS_ENABLED(CONFIG_BT_MESH_DEBUG_ADV)
#define LOG_MODULE_NAME bt_mesh_adv_ext
#include "common/log.h"

#include "host/hci_core.h"

#include "adv.h"
#include "net.h"
#include "proxy.h"
#include "pb_gatt_srv.h"

/* Convert from ms to 0.625ms units */
#define ADV_INT_FAST_MS    20

enum {
	/** Controller is currently advertising */
	ADV_FLAG_ACTIVE,
	/** Currently performing proxy advertising */
	ADV_FLAG_PROXY,
	/** The send-call has been scheduled. */
	ADV_FLAG_SCHEDULED,
	/** Custom adv params have been set, we need to update the parameters on
	 *  the next send.
	 */
	ADV_FLAG_UPDATE_PARAMS,

	/* Number of adv flags. */
	ADV_FLAGS_NUM
};

typedef struct net_buf* (*adv_buf_handler_t)(k_timeout_t timeout);

struct ext_adv {
	ATOMIC_DEFINE(flags, ADV_FLAGS_NUM);
	struct bt_le_ext_adv *instance;
	struct net_buf *buf;
	uint64_t timestamp;
	struct k_work_delayable work;
	adv_buf_handler_t handler;
	struct bt_le_adv_param adv_param;
};

static void send_pending_adv(struct k_work *work);
static struct ext_adv adv_main = {
	.work = Z_WORK_DELAYABLE_INITIALIZER(send_pending_adv),
	.handler = bt_mesh_adv_buf_get,
	.adv_param = {
		.id = BT_ID_DEFAULT,
		.interval_min = BT_MESH_ADV_SCAN_UNIT(ADV_INT_FAST_MS),
		.interval_max = BT_MESH_ADV_SCAN_UNIT(ADV_INT_FAST_MS),
#if defined(CONFIG_BT_MESH_DEBUG_USE_ID_ADDR)
		.options = BT_LE_ADV_OPT_USE_IDENTITY,
#endif
	}
};

#if defined(CONFIG_BT_MESH_RELAY)
#define RELAY_ADV_COUNT			CONFIG_BT_MESH_RELAY_ADV_SETS
#if RELAY_ADV_COUNT
static struct ext_adv adv_relay[RELAY_ADV_COUNT] = {
	[0 ... RELAY_ADV_COUNT - 1] = {
		.work = Z_WORK_DELAYABLE_INITIALIZER(send_pending_adv),
		.handler = bt_mesh_adv_buf_relay_get,
		.adv_param = {
			.id = BT_ID_DEFAULT,
			.interval_min = BT_MESH_ADV_SCAN_UNIT(ADV_INT_FAST_MS),
			.interval_max = BT_MESH_ADV_SCAN_UNIT(ADV_INT_FAST_MS),
#if defined(CONFIG_BT_MESH_DEBUG_USE_ID_ADDR)
			.options = BT_LE_ADV_OPT_USE_IDENTITY,
#endif
		}
	}
};
#define BT_MESH_RELAY_ADV_INS			(adv_relay)
#else /* !RELAY_ADV_COUNT */
#define BT_MESH_RELAY_ADV_INS			(&adv_main)
#endif /* RELAY_ADV_COUNT */
#else /* !CONFIG_BT_MESH_RELAY */
#define RELAY_ADV_COUNT				0
#define BT_MESH_RELAY_ADV_INS			(struct ext_adv)NULL
#endif /* CONFIG_BT_MESH_RELAY */

#if defined(CONFIG_BT_MESH_ADV_EXT_GATT_SEPARATE)
#define BT_MESH_ADV_COUNT			(1 + RELAY_ADV_COUNT + 1)
static void send_pending_adv_gatt_handler(struct k_work *work);
static struct ext_adv adv_gatt = {
	.work = Z_WORK_DELAYABLE_INITIALIZER(send_pending_adv_gatt_handler),
	.adv_param = {
		.id = BT_ID_DEFAULT,
		.interval_min = BT_MESH_ADV_SCAN_UNIT(ADV_INT_FAST_MS),
		.interval_max = BT_MESH_ADV_SCAN_UNIT(ADV_INT_FAST_MS),
#if defined(CONFIG_BT_MESH_DEBUG_USE_ID_ADDR)
		.options = BT_LE_ADV_OPT_USE_IDENTITY,
#endif
	}
};
#define BT_MESH_ADV_EXT_GATT_SEPARATE_INS	(&adv_gatt)
#elif defined(CONFIG_BT_MESH_GATT_SERVER)
#define BT_MESH_ADV_COUNT			(1 + RELAY_ADV_COUNT)
#define BT_MESH_ADV_EXT_GATT_SEPARATE_INS	(&adv_main)
#else /* !CONFIG_BT_MESH_ADV_EXT_GATT_SEPARATE */
#define BT_MESH_ADV_COUNT			(1 + RELAY_ADV_COUNT)
#define BT_MESH_ADV_EXT_GATT_SEPARATE_INS	(struct ext_adv)NULL
#endif /* CONFIG_BT_MESH_ADV_EXT_GATT_SEPARATE */

BUILD_ASSERT(CONFIG_BT_EXT_ADV_MAX_ADV_SET >= BT_MESH_ADV_COUNT,
	     "Insufficient adv instances");

static int adv_start(struct ext_adv *adv,
		     const struct bt_le_adv_param *param,
		     struct bt_le_ext_adv_start_param *start,
		     const struct bt_data *ad, size_t ad_len,
		     const struct bt_data *sd, size_t sd_len)
{
	int err;

	if (!adv->instance) {
		BT_ERR("Mesh advertiser not enabled");
		return -ENODEV;
	}

	if (atomic_test_and_set_bit(adv->flags, ADV_FLAG_ACTIVE)) {
		BT_ERR("Advertiser is busy");
		return -EBUSY;
	}

	if (atomic_test_bit(adv->flags, ADV_FLAG_UPDATE_PARAMS)) {
		err = bt_le_ext_adv_update_param(adv->instance, param);
		if (err) {
			BT_ERR("Failed updating adv params: %d", err);
			atomic_clear_bit(adv->flags, ADV_FLAG_ACTIVE);
			return err;
		}

		atomic_set_bit_to(adv->flags, ADV_FLAG_UPDATE_PARAMS,
				  param != &adv->adv_param);
	}

	err = bt_le_ext_adv_set_data(adv->instance, ad, ad_len, sd, sd_len);
	if (err) {
		BT_ERR("Failed setting adv data: %d", err);
		atomic_clear_bit(adv->flags, ADV_FLAG_ACTIVE);
		return err;
	}

	adv->timestamp = k_uptime_get();

	err = bt_le_ext_adv_start(adv->instance, start);
	if (err) {
		BT_ERR("Advertising failed: err %d", err);
		atomic_clear_bit(adv->flags, ADV_FLAG_ACTIVE);
	}

	return err;
}

static int buf_send(struct ext_adv *adv, struct net_buf *buf)
{
	struct bt_le_ext_adv_start_param start = {
		.num_events =
			BT_MESH_TRANSMIT_COUNT(BT_MESH_ADV(buf)->xmit) + 1,
	};
	uint16_t duration, adv_int;
	struct bt_data ad;
	int err;

	adv_int = MAX(ADV_INT_FAST_MS,
		      BT_MESH_TRANSMIT_INT(BT_MESH_ADV(buf)->xmit));
	/* Upper boundary estimate: */
	duration = start.num_events * (adv_int + 10);

	BT_DBG("type %u len %u: %s", BT_MESH_ADV(buf)->type,
	       buf->len, bt_hex(buf->data, buf->len));
	BT_DBG("count %u interval %ums duration %ums",
	       BT_MESH_TRANSMIT_COUNT(BT_MESH_ADV(buf)->xmit) + 1, adv_int,
	       duration);

	ad.type = bt_mesh_adv_type[BT_MESH_ADV(buf)->type];
	ad.data_len = buf->len;
	ad.data = buf->data;

	/* Only update advertising parameters if they're different */
	if (adv->adv_param.interval_min != BT_MESH_ADV_SCAN_UNIT(adv_int)) {
		adv->adv_param.interval_min = BT_MESH_ADV_SCAN_UNIT(adv_int);
		adv->adv_param.interval_max = adv->adv_param.interval_min;
		atomic_set_bit(adv->flags, ADV_FLAG_UPDATE_PARAMS);
	}

	err = adv_start(adv, &adv->adv_param, &start, &ad, 1, NULL, 0);
	if (!err) {
		adv->buf = net_buf_ref(buf);
	}

	bt_mesh_adv_send_start(duration, err, BT_MESH_ADV(buf));

	return err;
}

#if defined(CONFIG_BT_MESH_GATT_SERVER)
static void gatt_server_adv_send(struct ext_adv *adv)
{
	int err;

	if (bt_mesh_is_provisioned()) {
		if (IS_ENABLED(CONFIG_BT_MESH_GATT_PROXY)) {
			err = bt_mesh_proxy_adv_start();
			BT_DBG("Proxy Advertising");
		}
	} else if (IS_ENABLED(CONFIG_BT_MESH_PB_GATT)) {
		err = bt_mesh_pb_gatt_adv_start();
		BT_DBG("PB-GATT Advertising");
	}

	if (!err) {
		atomic_set_bit(adv->flags, ADV_FLAG_PROXY);
	}
}
#endif /* CONFIG_BT_MESH_GATT_SERVER */

static void send_pending_adv(struct k_work *work)
{
	struct ext_adv *adv = CONTAINER_OF(work, struct ext_adv, work.work);
	struct net_buf *buf;
	int err;

	atomic_clear_bit(adv->flags, ADV_FLAG_SCHEDULED);

	while ((buf = adv->handler(K_NO_WAIT))) {
		/* busy == 0 means this was canceled */
		if (!BT_MESH_ADV(buf)->busy) {
			net_buf_unref(buf);
			continue;
		}

		BT_MESH_ADV(buf)->busy = 0U;
		err = buf_send(adv, buf);

		net_buf_unref(buf);

		if (!err) {
			return; /* Wait for advertising to finish */
		}
	}

	if (IS_ENABLED(CONFIG_BT_MESH_GATT_SERVER) &&
	    adv == BT_MESH_ADV_EXT_GATT_SEPARATE_INS) {
		gatt_server_adv_send(adv);
	}
}

#if defined(CONFIG_BT_MESH_ADV_EXT_GATT_SEPARATE)
static void send_pending_adv_gatt_handler(struct k_work *work)
{
	struct ext_adv *adv = CONTAINER_OF(work, struct ext_adv, work.work);

	gatt_server_adv_send(adv);
}
#endif /* CONFIG_BT_MESH_ADV_EXT_GATT_SEPARATE */

static bool schedule_send(struct ext_adv *adv)
{
	uint64_t timestamp;
	int64_t delta;

	if (!adv) {
		return false;
	}

	timestamp = adv->timestamp;

	if (atomic_test_and_clear_bit(adv->flags, ADV_FLAG_PROXY)) {
		(void)bt_le_ext_adv_stop(adv->instance);
		atomic_clear_bit(adv->flags, ADV_FLAG_ACTIVE);
	}

	if (atomic_test_bit(adv->flags, ADV_FLAG_ACTIVE) ||
	    atomic_test_and_set_bit(adv->flags, ADV_FLAG_SCHEDULED)) {
		return false;
	}

	/* The controller will send the next advertisement immediately.
	 * Introduce a delay here to avoid sending the next mesh packet closer
	 * to the previous packet than what's permitted by the specification.
	 */
	delta = k_uptime_delta(&timestamp);
	k_work_reschedule(&adv->work, K_MSEC(ADV_INT_FAST_MS - delta));

	return true;
}

void bt_mesh_adv_gatt_update(void)
{
	(void)schedule_send(BT_MESH_ADV_EXT_GATT_SEPARATE_INS);
}

void bt_mesh_adv_buf_local_ready(void)
{
	(void)schedule_send(&adv_main);
}

void bt_mesh_adv_buf_relay_ready(void)
{
	struct bt_mesh_ext_adv *adv = relay_adv_get();

	for (int i = 0; i < RELAY_ADV_COUNT; i++) {
		if (schedule_send(&adv[i])) {
			return;
		}
	}
}

void bt_mesh_adv_init(void)
{
}

static struct ext_adv *adv_instance_find(struct bt_le_ext_adv *instance)
{
	if (adv_main.instance == instance) {
		return &adv_main;
	}

#if RELAY_ADV_COUNT
	for (int i = 0; i < ARRAY_SIZE(adv_relay); i++) {
		if (adv_relay[i].instance == instance) {
			return &adv_relay[i];
		}
	}
#endif /* RELAY_ADV_COUNT */

#if defined(CONFIG_BT_MESH_ADV_EXT_GATT_SEPARATE)
	if (adv_gatt.instance == instance) {
		return &adv_gatt;
	}
#endif

	return NULL;
}

static void adv_sent(struct bt_le_ext_adv *instance,
		     struct bt_le_ext_adv_sent_info *info)
{
	struct ext_adv *adv = adv_instance_find(instance);

	if (!adv) {
		BT_WARN("Unexpected adv instance");
		return;
	}

	/* Calling k_uptime_delta on a timestamp moves it to the current time.
	 * This is essential here, as schedule_send() uses the end of the event
	 * as a reference to avoid sending the next advertisement too soon.
	 */
	int64_t duration = k_uptime_delta(&adv->timestamp);

	BT_DBG("Advertising stopped after %u ms", (uint32_t)duration);

	atomic_clear_bit(adv->flags, ADV_FLAG_ACTIVE);

	if (!atomic_test_and_clear_bit(adv->flags, ADV_FLAG_PROXY)) {
		net_buf_unref(adv->buf);
	}

	(void)schedule_send(adv);
}

#if defined(CONFIG_BT_MESH_GATT_SERVER)
static void connected(struct bt_le_ext_adv *instance,
		      struct bt_le_ext_adv_connected_info *info)
{
	struct ext_adv *adv = BT_MESH_ADV_EXT_GATT_SEPARATE_INS;

	if (atomic_test_and_clear_bit(adv->flags, ADV_FLAG_PROXY)) {
		atomic_clear_bit(adv->flags, ADV_FLAG_ACTIVE);
		(void)schedule_send(adv);
	}
}
#endif /* CONFIG_BT_MESH_GATT_SERVER */

int bt_mesh_adv_enable(void)
{
	int err;

	static const struct bt_le_ext_adv_cb adv_cb = {
		.sent = adv_sent,
#if defined(CONFIG_BT_MESH_GATT_SERVER)
		.connected = connected,
#endif /* CONFIG_BT_MESH_GATT_SERVER */
	};

	if (adv_main.instance) {
		/* Already initialized */
		return 0;
	}


	err = bt_le_ext_adv_create(&adv_main.adv_param, &adv_cb,
				   &adv_main.instance);
	if (err) {
		return err;
	}

#if RELAY_ADV_COUNT
	for (int i = 0; i < RELAY_ADV_COUNT; i++) {
		err = bt_le_ext_adv_create(&adv_relay[i].adv_param, &adv_cb,
					   &adv_relay[i].instance);
		if (err) {
			return err;
		}
	}
#endif /* RELAY_ADV_COUNT */

#if defined(CONFIG_BT_MESH_ADV_EXT_GATT_SEPARATE)
	err = bt_le_ext_adv_create(&adv_gatt.adv_param, &adv_cb,
				   &adv_gatt.instance);
	if (err) {
		return err;
	}
#endif /* CONFIG_BT_MESH_ADV_EXT_GATT_SEPARATE */

	return 0;
}

int bt_mesh_adv_gatt_start(const struct bt_le_adv_param *param, int32_t duration,
			   const struct bt_data *ad, size_t ad_len,
			   const struct bt_data *sd, size_t sd_len)
{
	struct ext_adv *adv = BT_MESH_ADV_EXT_GATT_SEPARATE_INS;
	struct bt_le_ext_adv_start_param start = {
		/* Timeout is set in 10 ms steps, with 0 indicating "forever" */
		.timeout = (duration == SYS_FOREVER_MS) ? 0 : (duration / 10),
	};

	BT_DBG("Start advertising %d ms", duration);

	atomic_set_bit(adv->flags, ADV_FLAG_UPDATE_PARAMS);

	return adv_start(adv, param, &start, ad, ad_len, sd, sd_len);
}
