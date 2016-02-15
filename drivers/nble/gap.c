/*
 * Copyright (c) 2016 Intel Corporation
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

#include <nanokernel.h>
#include <device.h>
#include <gpio.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/conn.h>
#include <bluetooth/log.h>

#include "gap_internal.h"
#include "uart.h"
#include "rpc.h"

#define NBLE_SWDIO_PIN	6
#define NBLE_RESET_PIN	NBLE_SWDIO_PIN
#define NBLE_BTWAKE_PIN 5

static bt_ready_cb_t bt_ready_cb;

/* Local Bluetooth LE Device Address */
bt_addr_le_t nble_bdaddr;

#if defined(CONFIG_BLUETOOTH_DEBUG)
static const char *bt_addr_le_str(const bt_addr_le_t *addr)
{
	static char str[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(addr, str, sizeof(str));

	return str;
}
#endif /* CONFIG_BLUETOOTH_DEBUG */

static void send_dm_config(void)
{
	struct nble_gap_sm_config_params config = {
		.options = 1,		/* bonding */
		.io_caps = 3,		/* no input no output */
		.key_size = 16,		/* or 7 */
		.oob_present = 0,	/* no oob */
	};

	nble_gap_sm_config_req(&config);
}

void on_nble_up(void)
{
	BT_DBG("");

	send_dm_config();
}

void on_nble_get_version_rsp(const struct nble_version_response *rsp)
{
	BT_DBG("VERSION: %d.%d.%d %.20s", rsp->version.major,
	       rsp->version.minor, rsp->version.patch,
	       rsp->version.version_string);

	if (bt_ready_cb) {
		bt_ready_cb(0);
		bt_ready_cb = NULL;
	}
}

int bt_enable(bt_ready_cb_t cb)
{
	struct device *gpio;
	int ret;

	BT_DBG("");

	gpio = device_get_binding(CONFIG_GPIO_DW_0_NAME);
	if (!gpio) {
		BT_ERR("Cannot find %s", CONFIG_GPIO_DW_0_NAME);
		return -ENODEV;
	}

	ret = gpio_pin_configure(gpio, NBLE_RESET_PIN, GPIO_DIR_OUT);
	if (ret) {
		BT_ERR("Error configuring pin %d", NBLE_RESET_PIN);
		return -ENODEV;
	}

	/* Reset hold time is 0.2us (normal) or 100us (SWD debug) */
	ret = gpio_pin_write(gpio, NBLE_RESET_PIN, 0);
	if (ret) {
		BT_ERR("Error pin write %d", NBLE_RESET_PIN);
		return -EINVAL;
	}

	ret = gpio_pin_configure(gpio, NBLE_BTWAKE_PIN, GPIO_DIR_OUT);
	if (ret) {
		BT_ERR("Error configuring pin %d", NBLE_BTWAKE_PIN);
		return -ENODEV;
	}

	ret = gpio_pin_write(gpio, NBLE_BTWAKE_PIN, 1);
	if (ret) {
		BT_ERR("Error pin write %d", NBLE_BTWAKE_PIN);
		return -EINVAL;
	}

	/**
	 * NBLE reset is achieved by asserting low the SWDIO pin.
	 * However, the BLE Core chip can be in SWD debug mode,
	 * and NRF_POWER->RESET = 0 due to, other constraints: therefore,
	 * this reset might not work everytime, especially after
	 * flashing or debugging.
	 */

	/* sleep 1ms depending on context */
	switch (sys_execution_context_type_get()) {
	case NANO_CTX_FIBER:
		fiber_sleep(MSEC(1));
		break;
	case NANO_CTX_TASK:
		task_sleep(MSEC(1));
		break;
	default:
		BT_ERR("ISR context is not supported");
		return -EINVAL;
	}

	ret = nble_open();
	if (ret) {
		return ret;
	}

	ret = gpio_pin_write(gpio, NBLE_RESET_PIN, 1);
	if (ret) {
		BT_ERR("Error pin write %d", NBLE_RESET_PIN);
		return -EINVAL;
	}

	/* Set back GPIO to input to avoid interfering with external debugger */
	ret = gpio_pin_configure(gpio, NBLE_RESET_PIN, GPIO_DIR_IN);
	if (ret) {
		BT_ERR("Error configuring pin %d", NBLE_RESET_PIN);
		return -ENODEV;
	}

	bt_ready_cb = cb;

	return 0;
}

static bool valid_adv_param(const struct bt_le_adv_param *param)
{
	switch (param->type) {
	case BT_LE_ADV_IND:
	case BT_LE_ADV_SCAN_IND:
	case BT_LE_ADV_NONCONN_IND:
		break;
	default:
		return false;
	}

	switch (param->addr_type) {
	case BT_LE_ADV_ADDR_IDENTITY:
		break;
	case BT_LE_ADV_ADDR_NRPA: /* nble doesn't support NRPAs (for now) */
	default:
		return false;
	}

	if (param->interval_min > param->interval_max ||
	    param->interval_min < 0x0020 || param->interval_max > 0x4000) {
		return false;
	}

	return true;
}

int bt_le_adv_start(const struct bt_le_adv_param *param,
		    const struct bt_data *ad, size_t ad_len,
		    const struct bt_data *sd, size_t sd_len)
{
	struct nble_gap_adv_params params = { 0 };
	int i;

	if (!valid_adv_param(param)) {
		return -EINVAL;
	}

	for (i = 0; i < ad_len; i++) {
		uint8_t *p;

		/* Check if ad fit in the remaining buffer */
		if (params.ad.len + ad[i].data_len + 2 > 31) {
			break;
		}

		p = &params.ad.data[params.ad.len];
		*p++ = ad[i].data_len + 1;
		*p++ = ad[i].type;
		memcpy(p, ad[i].data, ad[i].data_len);
		params.ad.len += ad[i].data_len + 2;
	}

	/*
	 * Don't bother with scan response if the advertising type isn't
	 * a scannable one.
	 */
	if (param->type != BT_LE_ADV_IND && param->type != BT_LE_ADV_SCAN_IND) {
		goto send_set_param;
	}

	for (i = 0; i < sd_len; i++) {
		uint8_t *p;

		/* Check if sd fit in the remaining buffer */
		if (params.sd.len + sd[i].data_len + 2 > 31) {
			break;
		}

		p = &params.sd.data[params.sd.len];
		*p++ = sd[i].data_len + 1;
		*p++ = sd[i].type;
		memcpy(p, sd[i].data, sd[i].data_len);
		params.sd.len += sd[i].data_len + 2;
	}

send_set_param:
	/* Timeout is handled by application timer */
	params.timeout = 0;
	/* forced to none currently (no whitelist support) */
	params.filter_policy = 0;
	params.interval_max = param->interval_max;
	params.interval_min = param->interval_min;
	params.type = param->type;

	nble_gap_start_advertise_req(&params);

	return 0;
}

int bt_le_adv_stop(void)
{
	return -ENOSYS;
}

int bt_le_scan_start(const struct bt_le_scan_param *param, bt_le_scan_cb_t cb)
{
	return -ENOSYS;
}

int bt_le_scan_stop(void)
{
	return -ENOSYS;
}

void on_nble_gap_dtm_init_rsp(void *user_data)
{
	BT_DBG("");
}

void nble_log(const struct nble_log_s *param, char *format, uint8_t len)
{
#if defined(CONFIG_BLUETOOTH_DEBUG)
	/* Build meaningful output */
	printf("nble: ");
	printf(format, param->param0, param->param1, param->param2,
	       param->param3);
	printf("\n");
#endif
}

void on_nble_gap_sm_status_evt(const struct nble_gap_sm_status_evt *ev)
{
	BT_DBG("");
}

void on_nble_gap_sm_passkey_display_evt(const struct nble_gap_sm_passkey_disp_evt *ev)
{
	BT_DBG("");
}

void on_nble_gap_sm_passkey_req_evt(const struct nble_gap_sm_passkey_req_evt *ev)
{
	BT_DBG("");
}

void on_nble_gap_to_evt(const struct nble_gap_timout_evt *ev)
{
	BT_DBG("");
}

void on_nble_gap_rssi_evt(const struct nble_gap_rssi_evt *ev)
{
	BT_DBG("");
}

void on_nble_gap_service_read_rsp(const struct nble_response *rsp)
{
	BT_DBG("");
}

void on_nble_gap_read_bda_rsp(const struct nble_service_read_bda_response *rsp)
{
	if (rsp->status) {
		BT_ERR("Read bdaddr failed, status %d", rsp->status);
		return;
	}

	bt_addr_le_copy(&nble_bdaddr, &rsp->bd);

	BT_DBG("Local bdaddr: %s", bt_addr_le_str(&nble_bdaddr));

	nble_get_version_req(NULL);
}

void on_nble_gap_disconnect_rsp(const struct nble_response *rsp)
{
	BT_DBG("");
}

void on_nble_gap_sm_pairing_rsp(const struct nble_response *rsp)
{
	BT_DBG("");
}

void on_nble_gap_sm_config_rsp(struct nble_gap_sm_config_rsp *rsp)
{
	if (rsp->status) {
		BT_ERR("SM config failed, status %d", rsp->status);
		return;
	}

	BT_DBG("state %u", rsp->state);

	/* Get bdaddr queued after SM setup */
	nble_gap_read_bda_req(NULL);
}

void on_nble_gap_clr_white_list_rsp(const struct nble_response *rsp)
{
	BT_DBG("");
}

void on_nble_gap_sm_passkey_reply_rsp(const struct nble_response *rsp)
{
	BT_DBG("");
}

void on_nble_gap_connect_rsp(const struct nble_response *rsp)
{
	BT_DBG("");
}

void on_nble_gap_start_scan_rsp(const struct nble_response *rsp)
{
	BT_DBG("");
}

void on_nble_gap_stop_scan_rsp(const struct nble_response *rsp)
{
	BT_DBG("");
}

void on_nble_gap_cancel_connect_rsp(const struct nble_response *rsp)
{
	BT_DBG("");
}

void on_nble_gap_set_option_rsp(const struct nble_response *rsp)
{
	BT_DBG("");
}

void on_nble_gap_generic_cmd_rsp(const struct nble_response *rsp)
{
	BT_DBG("");
}

void on_nble_gap_conn_update_rsp(const struct nble_response *rsp)
{
	BT_DBG("");
}

void on_nble_gap_sm_clear_bonds_rsp(const struct nble_response *rsp)
{
	BT_DBG("");
}

void on_nble_gap_service_write_rsp(const struct nble_service_write_response *rsp)
{
	BT_DBG("");
}

void on_ble_set_enable_config_rsp(const struct nble_response *rsp)
{
	BT_DBG("");
}

void on_nble_gap_set_rssi_report_rsp(const struct nble_response *rsp)
{
	BT_DBG("");
}

void on_nble_gap_wr_white_list_rsp(const struct nble_response *rsp)
{
	BT_DBG("");
}

void on_nble_gap_dbg_rsp(const struct debug_response *rsp)
{
	BT_DBG("");
}

void on_nble_gap_start_advertise_rsp(const struct nble_response *rsp)
{
	BT_DBG("");
}


void on_nble_gap_stop_advertise_rsp(const struct nble_response *rsp)
{
	BT_DBG("");
}
