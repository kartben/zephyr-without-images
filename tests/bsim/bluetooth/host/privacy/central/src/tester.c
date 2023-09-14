/*
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "bs_bt_utils.h"

#include <stdint.h>
#include <string.h>

#include <zephyr/bluetooth/addr.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/toolchain.h>

DEFINE_FLAG(flag_new_address);

void scanned_cb(struct bt_le_ext_adv *adv, struct bt_le_ext_adv_scanned_info *info)
{
	static bool init;
	static int64_t old_time;
	static bt_addr_le_t old_addr;
	bt_addr_le_t new_addr;

	if (bst_result == Passed) {
		return;
	}

	if (!init) {
		old_addr = *info->addr;
		old_time = k_uptime_get();
		init = true;
	}

	new_addr = *info->addr;

	/* Check if the scan request comes from a new address */
	if (bt_addr_le_cmp(&old_addr, &new_addr)) {
		int64_t new_time, diff, time_diff_ms, rpa_timeout_ms;

		printk("Scanned request from new ");
		print_address(info->addr);

		/* Ensure the RPA rotation occurs within +-10% of CONFIG_BT_RPA_TIMEOUT */
		new_time = k_uptime_get();
		time_diff_ms = new_time - old_time;
		rpa_timeout_ms = CONFIG_BT_RPA_TIMEOUT * MSEC_PER_SEC;

		if (time_diff_ms > rpa_timeout_ms) {
			diff = time_diff_ms - rpa_timeout_ms;
		} else {
			diff = rpa_timeout_ms - time_diff_ms;
		}

		if (diff > rpa_timeout_ms * 0.10) {
			FAIL("RPA rotation did not occur within +-10%% of CONFIG_BT_RPA_TIMEOUT");
		}
		old_time = new_time;

		SET_FLAG(flag_new_address);
	}

	old_addr = new_addr;
}

static struct bt_le_ext_adv_cb adv_callbacks = {
	.scanned = scanned_cb,
};

void start_advertising(void)
{
	int err;
	uint8_t mfg_data[] = {0xAB, 0xCD, 0xEF};
	const struct bt_data sd[] = {BT_DATA(BT_DATA_MANUFACTURER_DATA, mfg_data, 3)};
	struct bt_le_adv_param params;
	struct bt_le_ext_adv_start_param start_params;
	struct bt_le_ext_adv *adv;

	/* Enable bluetooth */
	err = bt_enable(NULL);
	if (err) {
		FAIL("Failed to enable bluetooth (err %d\n)", err);
	}

	/* Create advertising set */
	params.id = BT_ID_DEFAULT;
	params.sid = 0;
	params.secondary_max_skip = 0;
	params.options = BT_LE_ADV_OPT_EXT_ADV | BT_LE_ADV_OPT_SCANNABLE |
			 BT_LE_ADV_OPT_NOTIFY_SCAN_REQ | BT_LE_ADV_OPT_USE_NAME;
	params.interval_min = BT_GAP_ADV_FAST_INT_MIN_1;
	params.interval_max = BT_GAP_ADV_FAST_INT_MAX_1;
	params.peer = NULL;

	err = bt_le_ext_adv_create(&params, &adv_callbacks, &adv);
	if (err) {
		FAIL("Failed to create advertising set (err %d)\n", err);
	}

	/* Set scan data */
	err = bt_le_ext_adv_set_data(adv, NULL, 0, sd, ARRAY_SIZE(sd));
	if (err) {
		FAIL("Failed to set advertising data (err %d)", err);
	}

	/* Start advertising */
	start_params.timeout = 0;
	start_params.num_events = 0;

	err = bt_le_ext_adv_start(adv, &start_params);
	if (err) {
		FAIL("Failed to start advertising (err %d)\n", err);
	}
}

void tester_procedure(void)
{
	start_advertising();

	for (int i = 0; i < 5; i++) {
		WAIT_FOR_FLAG(flag_new_address);
		UNSET_FLAG(flag_new_address);
	}

	PASS("PASS\n");
}
