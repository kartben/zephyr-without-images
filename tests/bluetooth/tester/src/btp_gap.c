/* gap.c - Bluetooth GAP Tester */

/*
 * Copyright (c) 2015-2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/sys/atomic.h>
#include <zephyr/types.h>
#include <string.h>

#include <zephyr/toolchain.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/hci.h>

#include <zephyr/sys/byteorder.h>
#include <zephyr/net/buf.h>

#include <hci_core.h>

#include <zephyr/logging/log.h>
#define LOG_MODULE_NAME bttester_gap
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

#include "btp/btp.h"

#define CONTROLLER_INDEX 0
#define CONTROLLER_NAME "btp_tester"

#define BT_LE_AD_DISCOV_MASK (BT_LE_AD_LIMITED | BT_LE_AD_GENERAL)
#define ADV_BUF_LEN (sizeof(struct btp_gap_device_found_ev) + 2 * 31)

static atomic_t current_settings;
struct bt_conn_auth_cb cb;
static uint8_t oob_legacy_tk[16] = { 0 };

#if !defined(CONFIG_BT_SMP_OOB_LEGACY_PAIR_ONLY)
static struct bt_le_oob oob_sc_local = { 0 };
static struct bt_le_oob oob_sc_remote = { 0 };
#endif /* !defined(CONFIG_BT_SMP_OOB_LEGACY_PAIR_ONLY) */

/* connection parameters for rejection test */
#define REJECT_INTERVAL_MIN 0x0C80
#define REJECT_INTERVAL_MAX 0x0C80
#define REJECT_LATENCY 0x0000
#define REJECT_SUPERVISION_TIMEOUT 0x0C80

#if defined(CONFIG_BT_PRIVACY)
static struct {
	bt_addr_le_t addr;
	bool supported;
} cars[CONFIG_BT_MAX_PAIRED];

static uint8_t read_car_cb(struct bt_conn *conn, uint8_t err,
			  struct bt_gatt_read_params *params, const void *data,
			  uint16_t length);

static struct bt_gatt_read_params read_car_params = {
		.func = read_car_cb,
		.by_uuid.uuid = BT_UUID_CENTRAL_ADDR_RES,
		.by_uuid.start_handle = BT_ATT_FIRST_ATTRIBUTE_HANDLE,
		.by_uuid.end_handle = BT_ATT_LAST_ATTRIBUTE_HANDLE,
};

static uint8_t read_car_cb(struct bt_conn *conn, uint8_t err,
			  struct bt_gatt_read_params *params, const void *data,
			  uint16_t length)
{
	struct bt_conn_info info;
	bool supported = false;

	if (!err && data && length == 1) {
		const uint8_t *tmp = data;

		/* only 0 or 1 are valid values */
		if (tmp[0] == 1) {
			supported = true;
		}
	}

	bt_conn_get_info(conn, &info);

	for (int i = 0; i < CONFIG_BT_MAX_PAIRED; i++) {
		if (bt_addr_le_eq(info.le.dst, &cars[i].addr)) {
			cars[i].supported = supported;
			break;
		}
	}

	return BT_GATT_ITER_STOP;
}
#endif

static void le_connected(struct bt_conn *conn, uint8_t err)
{
	struct btp_gap_device_connected_ev ev;
	struct bt_conn_info info;

	if (err) {
		return;
	}

	bt_conn_get_info(conn, &info);

	memcpy(ev.address, info.le.dst->a.val, sizeof(ev.address));
	ev.address_type = info.le.dst->type;
	ev.interval = sys_cpu_to_le16(info.le.interval);
	ev.latency = sys_cpu_to_le16(info.le.latency);
	ev.timeout = sys_cpu_to_le16(info.le.timeout);

	tester_send(BTP_SERVICE_ID_GAP, BTP_GAP_EV_DEVICE_CONNECTED,
		    CONTROLLER_INDEX, (uint8_t *) &ev, sizeof(ev));
}

static void le_disconnected(struct bt_conn *conn, uint8_t reason)
{
	struct btp_gap_device_disconnected_ev ev;
	const bt_addr_le_t *addr = bt_conn_get_dst(conn);

	memcpy(ev.address, addr->a.val, sizeof(ev.address));
	ev.address_type = addr->type;

	tester_send(BTP_SERVICE_ID_GAP, BTP_GAP_EV_DEVICE_DISCONNECTED,
		    CONTROLLER_INDEX, (uint8_t *) &ev, sizeof(ev));
}

static void le_identity_resolved(struct bt_conn *conn, const bt_addr_le_t *rpa,
				 const bt_addr_le_t *identity)
{
	struct btp_gap_identity_resolved_ev ev;

	ev.address_type = rpa->type;
	memcpy(ev.address, rpa->a.val, sizeof(ev.address));

	ev.identity_address_type = identity->type;
	memcpy(ev.identity_address, identity->a.val,
	       sizeof(ev.identity_address));

	tester_send(BTP_SERVICE_ID_GAP, BTP_GAP_EV_IDENTITY_RESOLVED,
		    CONTROLLER_INDEX, (uint8_t *) &ev, sizeof(ev));
}

static void le_param_updated(struct bt_conn *conn, uint16_t interval,
			     uint16_t latency, uint16_t timeout)
{
	struct btp_gap_conn_param_update_ev ev;
	const bt_addr_le_t *addr = bt_conn_get_dst(conn);

	memcpy(ev.address, addr->a.val, sizeof(ev.address));
	ev.address_type = addr->type;
	ev.interval = sys_cpu_to_le16(interval);
	ev.latency = sys_cpu_to_le16(latency);
	ev.timeout = sys_cpu_to_le16(timeout);

	tester_send(BTP_SERVICE_ID_GAP, BTP_GAP_EV_CONN_PARAM_UPDATE,
		    CONTROLLER_INDEX, (uint8_t *) &ev, sizeof(ev));
}

static bool le_param_req(struct bt_conn *conn, struct bt_le_conn_param *param)
{
	/* reject update if all parameters match reject pattern */
	if ((param->interval_min == REJECT_INTERVAL_MIN) &&
			(param->interval_max == REJECT_INTERVAL_MAX) &&
			(param->latency == REJECT_LATENCY) &&
			(param->timeout == REJECT_SUPERVISION_TIMEOUT)) {
		return false;
	}

	return true;
}

static void le_security_changed(struct bt_conn *conn, bt_security_t level,
				enum bt_security_err err)
{
	const bt_addr_le_t *addr = bt_conn_get_dst(conn);
	struct btp_gap_sec_level_changed_ev sec_ev;
	struct btp_gap_bond_lost_ev bond_ev;
	struct bt_conn_info info;

	switch (err) {
	case BT_SECURITY_ERR_SUCCESS:
		memcpy(sec_ev.address, addr->a.val, sizeof(sec_ev.address));
		sec_ev.address_type = addr->type;
		/* enum matches BTP values */
		sec_ev.sec_level = level;

		tester_send(BTP_SERVICE_ID_GAP, BTP_GAP_EV_SEC_LEVEL_CHANGED,
			    CONTROLLER_INDEX, (uint8_t *) &sec_ev, sizeof(sec_ev));
		break;
	case BT_SECURITY_ERR_PIN_OR_KEY_MISSING:
		/* for central role this means that peer have no LTK when we
		 * started encryption procedure
		 *
		 * This means bond is lost and we restart pairing to re-bond
		 */
		if (bt_conn_get_info(conn, &info) == 0 &&
		    info.role == BT_CONN_ROLE_CENTRAL) {
			LOG_DBG("Bond lost");

			(void)memcpy(bond_ev.address, addr->a.val, sizeof(bond_ev.address));
			bond_ev.address_type = addr->type;

			tester_send(BTP_SERVICE_ID_GAP, BTP_GAP_EV_BOND_LOST,
				    CONTROLLER_INDEX, (uint8_t *)&bond_ev, sizeof(bond_ev));

			(void)bt_conn_set_security(conn, BT_SECURITY_L2 | BT_SECURITY_FORCE_PAIR);
		}
		break;
	default:
		break;
	}
}

static struct bt_conn_cb conn_callbacks = {
	.connected = le_connected,
	.disconnected = le_disconnected,
	.identity_resolved = le_identity_resolved,
	.le_param_updated = le_param_updated,
	.le_param_req = le_param_req,
	.security_changed = le_security_changed,
};

static void supported_commands(uint8_t *data, uint16_t len)
{
	uint8_t cmds[4];
	struct btp_gap_read_supported_commands_rp *rp = (void *) &cmds;

	(void)memset(cmds, 0, sizeof(cmds));

	tester_set_bit(cmds, BTP_GAP_READ_SUPPORTED_COMMANDS);
	tester_set_bit(cmds, BTP_GAP_READ_CONTROLLER_INDEX_LIST);
	tester_set_bit(cmds, BTP_GAP_READ_CONTROLLER_INFO);
	tester_set_bit(cmds, BTP_GAP_SET_CONNECTABLE);
	tester_set_bit(cmds, BTP_GAP_SET_DISCOVERABLE);
	tester_set_bit(cmds, BTP_GAP_SET_BONDABLE);
	tester_set_bit(cmds, BTP_GAP_START_ADVERTISING);
	tester_set_bit(cmds, BTP_GAP_START_DIRECTED_ADV);
	tester_set_bit(cmds, BTP_GAP_STOP_ADVERTISING);
	tester_set_bit(cmds, BTP_GAP_START_DISCOVERY);
	tester_set_bit(cmds, BTP_GAP_STOP_DISCOVERY);
	tester_set_bit(cmds, BTP_GAP_CONNECT);
	tester_set_bit(cmds, BTP_GAP_DISCONNECT);
	tester_set_bit(cmds, BTP_GAP_SET_IO_CAP);
	tester_set_bit(cmds, BTP_GAP_PAIR);
	tester_set_bit(cmds, BTP_GAP_PASSKEY_ENTRY);
	tester_set_bit(cmds, BTP_GAP_PASSKEY_CONFIRM);
	tester_set_bit(cmds, BTP_GAP_CONN_PARAM_UPDATE);
	tester_set_bit(cmds, BTP_GAP_SET_MITM);
	tester_set_bit(cmds, BTP_GAP_OOB_LEGACY_SET_DATA);
#if !defined(CONFIG_BT_SMP_OOB_LEGACY_PAIR_ONLY)
	tester_set_bit(cmds, BTP_GAP_OOB_SC_GET_LOCAL_DATA);
	tester_set_bit(cmds, BTP_GAP_OOB_SC_SET_REMOTE_DATA);
#endif /* !defined(CONFIG_BT_SMP_OOB_LEGACY_PAIR_ONLY) */
	tester_set_bit(cmds, BTP_GAP_SET_FILTER_LIST);

	tester_send(BTP_SERVICE_ID_GAP, BTP_GAP_READ_SUPPORTED_COMMANDS,
		    CONTROLLER_INDEX, (uint8_t *) rp, sizeof(cmds));
}

static void controller_index_list(uint8_t *data,  uint16_t len)
{
	struct btp_gap_read_controller_index_list_rp *rp;
	uint8_t buf[sizeof(*rp) + 1];

	rp = (void *) buf;

	rp->num = 1U;
	rp->index[0] = CONTROLLER_INDEX;

	tester_send(BTP_SERVICE_ID_GAP, BTP_GAP_READ_CONTROLLER_INDEX_LIST,
		    BTP_INDEX_NONE, (uint8_t *) rp, sizeof(buf));
}

static void controller_info(uint8_t *data, uint16_t len)
{
	struct btp_gap_read_controller_info_rp rp;
	uint32_t supported_settings;

	(void)memset(&rp, 0, sizeof(rp));

	struct bt_le_oob oob_local = { 0 };

	bt_le_oob_get_local(BT_ID_DEFAULT, &oob_local);
	memcpy(rp.address, &oob_local.addr.a, sizeof(bt_addr_t));

	/*
	 * Re-use the oob data read here in get_oob_sc_local_data()
	 */
#if !defined(CONFIG_BT_SMP_OOB_LEGACY_PAIR_ONLY)
	oob_sc_local = oob_local;
#endif /* !defined(CONFIG_BT_SMP_OOB_LEGACY_PAIR_ONLY) */

	/*
	 * If privacy is used, the device uses random type address, otherwise
	 * static random or public type address is used.
	 */
#if !defined(CONFIG_BT_PRIVACY)
	if (oob_local.addr.type == BT_ADDR_LE_RANDOM) {
		atomic_set_bit(&current_settings, BTP_GAP_SETTINGS_STATIC_ADDRESS);
	}
#endif /* CONFIG_BT_PRIVACY */

	supported_settings = BIT(BTP_GAP_SETTINGS_POWERED);
	supported_settings |= BIT(BTP_GAP_SETTINGS_CONNECTABLE);
	supported_settings |= BIT(BTP_GAP_SETTINGS_BONDABLE);
	supported_settings |= BIT(BTP_GAP_SETTINGS_LE);
	supported_settings |= BIT(BTP_GAP_SETTINGS_ADVERTISING);

	rp->supported_settings = sys_cpu_to_le32(supported_settings);
	rp->current_settings = sys_cpu_to_le32(current_settings);

	memcpy(rp->name, CONTROLLER_NAME, sizeof(CONTROLLER_NAME));

	*rsp_len = sizeof(*rp);

	return BTP_STATUS_SUCCESS;
}

#if !defined(CONFIG_BT_SMP_OOB_LEGACY_PAIR_ONLY)
static const char *oob_config_str(int oob_config)
{
	switch (oob_config) {
	case BT_CONN_OOB_LOCAL_ONLY:
		return "Local";
	case BT_CONN_OOB_REMOTE_ONLY:
		return "Remote";
	case BT_CONN_OOB_BOTH_PEERS:
		return "Local and Remote";
	case BT_CONN_OOB_NO_DATA:
	default:
		return "no";
	}
}
#endif /* !defined(CONFIG_BT_SMP_OOB_LEGACY_PAIR_ONLY) */

static void oob_data_request(struct bt_conn *conn,
			     struct bt_conn_oob_info *oob_info)
{
	struct bt_conn_info info;
	int err = bt_conn_get_info(conn, &info);

	if (err) {
		return;
	}

	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(info.le.dst, addr, sizeof(addr));

	switch (oob_info->type) {
#if !defined(CONFIG_BT_SMP_OOB_LEGACY_PAIR_ONLY)
	case BT_CONN_OOB_LE_SC:
	{
		LOG_DBG("Set %s OOB SC data for %s, ",
			oob_config_str(oob_info->lesc.oob_config),
			addr);

		struct bt_le_oob_sc_data *oobd_local =
			oob_info->lesc.oob_config != BT_CONN_OOB_REMOTE_ONLY ?
				      &oob_sc_local.le_sc_data :
				      NULL;

		struct bt_le_oob_sc_data *oobd_remote =
			oob_info->lesc.oob_config != BT_CONN_OOB_LOCAL_ONLY ?
				      &oob_sc_remote.le_sc_data :
				      NULL;

		if (oobd_remote) {
			/* Assume that oob_sc_remote
			 * corresponds to the currently connected peer
			 */
			bt_addr_le_copy(&oob_sc_remote.addr, info.le.remote);
		}

		if (oobd_local &&
		    !bt_addr_le_eq(info.le.local, &oob_sc_local.addr)) {
			bt_addr_le_to_str(info.le.local, addr, sizeof(addr));
			LOG_DBG("No OOB data available for local %s",
				addr);
			bt_conn_auth_cancel(conn);
			return;
		}

		err = bt_le_oob_set_sc_data(conn, oobd_local, oobd_remote);
		if (err) {
			LOG_DBG("bt_le_oob_set_sc_data failed with: %d", err);
		}

		break;
	}
#endif /* !defined(CONFIG_BT_SMP_OOB_LEGACY_PAIR_ONLY) */

#if !defined(CONFIG_BT_SMP_SC_PAIR_ONLY)
	case BT_CONN_OOB_LE_LEGACY:
		LOG_DBG("Legacy OOB TK requested from remote %s", addr);

		err = bt_le_oob_set_legacy_tk(conn, oob_legacy_tk);
		if (err < 0) {
			LOG_ERR("Failed to set OOB TK: %d", err);
		}

		break;
#endif /* !defined(CONFIG_BT_SMP_SC_PAIR_ONLY) */
	default:
		LOG_ERR("Unhandled OOB type %d", oob_info->type);
		break;
	}
}

#if !defined(CONFIG_BT_SMP_OOB_LEGACY_PAIR_ONLY)
static uint8_t get_oob_sc_local_data(uint8_t index, const void *cmd, uint16_t cmd_len,
				     void *rsp, uint16_t *rsp_len)
{
	struct btp_gap_oob_sc_get_local_data_rp *rp = rsp;

	if (index != CONTROLLER_INDEX) {
		return BTP_STATUS_FAILED;
	}

	cb.oob_data_request = oob_data_request;

	memcpy(rp->conf, &oob_sc_local.le_sc_data.c[0], sizeof(rp->conf));
	memcpy(rp->rand, &oob_sc_local.le_sc_data.r[0], sizeof(rp->rand));

	*rsp_len = sizeof(*rp);
	return BTP_STATUS_SUCCESS;
}

static uint8_t set_oob_sc_remote_data(uint8_t index, const void *cmd, uint16_t cmd_len,
				      void *rsp, uint16_t *rsp_len)
{
	const struct btp_gap_oob_sc_set_remote_data_cmd *cp = cmd;

	if (index != CONTROLLER_INDEX) {
		return BTP_STATUS_FAILED;
	}

	cb.oob_data_request = oob_data_request;
	bt_set_oob_data_flag(true);

	/* Note that the .addr field
	 * will be set by the oob_data_request callback
	 */
	memcpy(&oob_sc_remote.le_sc_data.r[0], cp->rand,
	       sizeof(oob_sc_remote.le_sc_data.r));
	memcpy(&oob_sc_remote.le_sc_data.c[0], cp->conf,
	       sizeof(oob_sc_remote.le_sc_data.c));

	return BTP_STATUS_SUCCESS;
}
#endif /* !defined(CONFIG_BT_SMP_OOB_LEGACY_PAIR_ONLY) */

static uint8_t set_connectable(uint8_t index, const void *cmd, uint16_t cmd_len,
			       void *rsp, uint16_t *rsp_len)
{
	const struct btp_gap_set_connectable_cmd *cp = cmd;
	struct btp_gap_set_connectable_rp *rp = rsp;

	if (index != CONTROLLER_INDEX) {
		return BTP_STATUS_FAILED;
	}

	if (cp->connectable) {
		atomic_set_bit(&current_settings, BTP_GAP_SETTINGS_CONNECTABLE);
	} else {
		atomic_clear_bit(&current_settings, BTP_GAP_SETTINGS_CONNECTABLE);
	}

	rp->current_settings = sys_cpu_to_le32(current_settings);

	*rsp_len = sizeof(*rp);

	return BTP_STATUS_SUCCESS;
}

static uint8_t ad_flags = BT_LE_AD_NO_BREDR;
static struct bt_data ad[10] = {
	BT_DATA(BT_DATA_FLAGS, &ad_flags, sizeof(ad_flags)),
};
static struct bt_data sd[10];

static uint8_t set_discoverable(uint8_t index, const void *cmd, uint16_t cmd_len,
			       void *rsp, uint16_t *rsp_len)
{
	const struct btp_gap_set_discoverable_cmd *cp = cmd;
	struct btp_gap_set_discoverable_rp *rp = rsp;

	if (index != CONTROLLER_INDEX) {
		return BTP_STATUS_FAILED;
	}

	switch (cp->discoverable) {
	case BTP_GAP_NON_DISCOVERABLE:
		ad_flags &= ~(BT_LE_AD_GENERAL | BT_LE_AD_LIMITED);
		atomic_clear_bit(&current_settings, BTP_GAP_SETTINGS_DISCOVERABLE);
		break;
	case BTP_GAP_GENERAL_DISCOVERABLE:
		ad_flags &= ~BT_LE_AD_LIMITED;
		ad_flags |= BT_LE_AD_GENERAL;
		atomic_set_bit(&current_settings, BTP_GAP_SETTINGS_DISCOVERABLE);
		break;
	case BTP_GAP_LIMITED_DISCOVERABLE:
		ad_flags &= ~BT_LE_AD_GENERAL;
		ad_flags |= BT_LE_AD_LIMITED;
		atomic_set_bit(&current_settings, BTP_GAP_SETTINGS_DISCOVERABLE);
		break;
	default:
		return BTP_STATUS_FAILED;
	}

	rp->current_settings = sys_cpu_to_le32(current_settings);

	*rsp_len = sizeof(*rp);
	return BTP_STATUS_SUCCESS;
}

static uint8_t set_bondable(uint8_t index, const void *cmd, uint16_t cmd_len,
			    void *rsp, uint16_t *rsp_len)
{
	const struct btp_gap_set_bondable_cmd *cp = cmd;
	struct btp_gap_set_bondable_rp *rp = rsp;

	if (index != CONTROLLER_INDEX) {
		return BTP_STATUS_FAILED;
	}

	LOG_DBG("bondable: %d", cp->bondable);

	if (cp->bondable) {
		atomic_set_bit(&current_settings, BTP_GAP_SETTINGS_BONDABLE);
	} else {
		atomic_clear_bit(&current_settings, BTP_GAP_SETTINGS_BONDABLE);
	}

	bt_set_bondable(cp->bondable);

	rp->current_settings = sys_cpu_to_le32(current_settings);
	*rsp_len = sizeof(*rp);
	return BTP_STATUS_SUCCESS;
}

static uint8_t start_advertising(uint8_t index, const void *cmd, uint16_t cmd_len,
				 void *rsp, uint16_t *rsp_len)
{
	const struct btp_gap_start_advertising_cmd *cp = cmd;
	struct btp_gap_start_advertising_rp *rp = rsp;
	struct bt_le_adv_param param = BT_LE_ADV_PARAM_INIT(0,
							    BT_GAP_ADV_FAST_INT_MIN_2,
							    BT_GAP_ADV_FAST_INT_MAX_2,
							    NULL);
	uint8_t own_addr_type;
	uint32_t duration;
	uint8_t adv_len;
	uint8_t sd_len;
	int i;

	if (index != CONTROLLER_INDEX) {
		return BTP_STATUS_FAILED;
	}

	/* This command is very unfortunate since after variable data there is
	 * additional 5 bytes (4 bytes for duration, 1 byte for own address
	 * type.
	 */
	if ((cmd_len < sizeof(*cp)) ||
	    (cmd_len != sizeof(*cp) + cp->adv_data_len + cp->scan_rsp_len +
			    sizeof(duration) + sizeof(own_addr_type))) {
		return BTP_STATUS_FAILED;
	}

	/* currently ignored */
	duration = sys_get_le32(cp->adv_sr_data + cp->adv_data_len + cp->scan_rsp_len);
	(void)duration;
	own_addr_type = cp->adv_sr_data[cp->adv_data_len + cp->scan_rsp_len + sizeof(duration)];

	for (i = 0, adv_len = 1U; i < cp->adv_data_len; adv_len++) {
		if (adv_len >= ARRAY_SIZE(ad)) {
			LOG_ERR("ad[] Out of memory");
			return BTP_STATUS_FAILED;
		}

		ad[adv_len].type = cp->adv_sr_data[i++];
		ad[adv_len].data_len = cp->adv_sr_data[i++];
		ad[adv_len].data = &cp->adv_sr_data[i];
		i += ad[adv_len].data_len;
	}

	for (sd_len = 0U; i < cp->adv_data_len + cp->scan_rsp_len; sd_len++) {
		if (sd_len >= ARRAY_SIZE(sd)) {
			LOG_ERR("sd[] Out of memory");
			return BTP_STATUS_FAILED;
		}

		sd[sd_len].type = cp->adv_sr_data[i++];
		sd[sd_len].data_len = cp->adv_sr_data[i++];
		sd[sd_len].data = &cp->adv_sr_data[i];
		i += sd[sd_len].data_len;
	}

	if (atomic_test_bit(&current_settings, BTP_GAP_SETTINGS_CONNECTABLE)) {
		param.options |= BT_LE_ADV_OPT_CONNECTABLE;
	}

	switch (own_addr_type) {
	case 0x00:
		param.options |= BT_LE_ADV_OPT_USE_IDENTITY;
		break;
#if defined(CONFIG_BT_PRIVACY)
	case 0x01:
		/* RPA usage is is controlled via privacy settings */
		if (!atomic_test_bit(&current_settings, BTP_GAP_SETTINGS_PRIVACY)) {
			return BTP_STATUS_FAILED;
		}
		break;
	case 0x02:
		/* NRPA is used only for non-connectable advertising */
		if (atomic_test_bit(&current_settings, BTP_GAP_SETTINGS_CONNECTABLE)) {
			return BTP_STATUS_FAILED;
		}
		break;
#endif
	default:
		return BTP_STATUS_FAILED;
	}

	/* BTP API don't allow to set empty scan response data. */
	if (bt_le_adv_start(&param, ad, adv_len, sd_len ? sd : NULL, sd_len) < 0) {
		LOG_ERR("Failed to start advertising");
		return BTP_STATUS_FAILED;
	}

	atomic_set_bit(&current_settings, BTP_GAP_SETTINGS_ADVERTISING);
	rp->current_settings = sys_cpu_to_le32(current_settings);

	*rsp_len = sizeof(*rp);
	return BTP_STATUS_SUCCESS;
}

static uint8_t start_directed_advertising(uint8_t index, const void *cmd, uint16_t cmd_len,
					  void *rsp, uint16_t *rsp_len)
{
	const struct btp_gap_start_directed_adv_cmd *cp = cmd;
	struct btp_gap_start_directed_adv_rp *rp = rsp;
	struct bt_le_adv_param adv_param;
	uint16_t options = sys_le16_to_cpu(cp->options);

	if (index != CONTROLLER_INDEX) {
		return BTP_STATUS_FAILED;
	}

	adv_param = *BT_LE_ADV_CONN_DIR(&cp->address);

	if (!(options & BTP_GAP_START_DIRECTED_ADV_HD)) {
		adv_param.options |= BT_LE_ADV_OPT_DIR_MODE_LOW_DUTY;
		adv_param.interval_max = BT_GAP_ADV_FAST_INT_MAX_2;
		adv_param.interval_min = BT_GAP_ADV_FAST_INT_MIN_2;
	}

	if (options & BTP_GAP_START_DIRECTED_ADV_PEER_RPA) {
#if defined(CONFIG_BT_PRIVACY)
		/* check if peer supports Central Address Resolution */
		for (int i = 0; i < CONFIG_BT_MAX_PAIRED; i++) {
			if (bt_addr_le_eq(peer, &cars[i].addr)) {
				if (cars[i].supported) {
					adv_param.options |= BT_LE_ADV_OPT_DIR_ADDR_RPA;
				}
			}
		}
#endif
	}

	if (bt_le_adv_start(&adv_param, NULL, 0, NULL, 0) < 0) {
		LOG_ERR("Failed to start advertising");
		return BTP_STATUS_FAILED;
	}

	atomic_set_bit(&current_settings, BTP_GAP_SETTINGS_ADVERTISING);
	rp->current_settings = sys_cpu_to_le32(current_settings);

	*rsp_len = sizeof(*rp);
	return BTP_STATUS_SUCCESS;
}

static uint8_t stop_advertising(uint8_t index, const void *cmd, uint16_t cmd_len,
			        void *rsp, uint16_t *rsp_len)
{
	struct btp_gap_stop_advertising_rp *rp = rsp;
	int err;

	if (index != CONTROLLER_INDEX) {
		return BTP_STATUS_FAILED;
	}

	err = bt_le_adv_stop();
	if (err < 0) {
		tester_rsp(BTP_SERVICE_ID_GAP, BTP_GAP_STOP_ADVERTISING,
			   CONTROLLER_INDEX, BTP_STATUS_FAILED);
		LOG_ERR("Failed to stop advertising: %d", err);
		return BTP_STATUS_FAILED;
	}

	atomic_clear_bit(&current_settings, BTP_GAP_SETTINGS_ADVERTISING);
	rp->current_settings = sys_cpu_to_le32(current_settings);

	*rsp_len = sizeof(*rp);
	return BTP_STATUS_SUCCESS;
}

static uint8_t get_ad_flags(struct net_buf_simple *ad)
{
	uint8_t len, i;

	/* Parse advertisement to get flags */
	for (i = 0U; i < ad->len; i += len - 1) {
		len = ad->data[i++];
		if (!len) {
			break;
		}

		/* Check if field length is correct */
		if (len > (ad->len - i) || (ad->len - i) < 1) {
			break;
		}

		switch (ad->data[i++]) {
		case BT_DATA_FLAGS:
			return ad->data[i];
		default:
			break;
		}
	}

	return 0;
}

static uint8_t discovery_flags;
static struct net_buf_simple *adv_buf = NET_BUF_SIMPLE(ADV_BUF_LEN);

static void store_adv(const bt_addr_le_t *addr, int8_t rssi,
		      struct net_buf_simple *ad)
{
	struct btp_gap_device_found_ev *ev;

	/* cleanup */
	net_buf_simple_init(adv_buf, 0);

	ev = net_buf_simple_add(adv_buf, sizeof(*ev));

	memcpy(ev->address, addr->a.val, sizeof(ev->address));
	ev->address_type = addr->type;
	ev->rssi = rssi;
	ev->flags = BTP_GAP_DEVICE_FOUND_FLAG_AD | BTP_GAP_DEVICE_FOUND_FLAG_RSSI;
	ev->eir_data_len = ad->len;
	memcpy(net_buf_simple_add(adv_buf, ad->len), ad->data, ad->len);
}

static void device_found(const bt_addr_le_t *addr, int8_t rssi, uint8_t evtype,
			 struct net_buf_simple *ad)
{
	/* if General/Limited Discovery - parse Advertising data to get flags */
	if (!(discovery_flags & BTP_GAP_DISCOVERY_FLAG_LE_OBSERVE) &&
	    (evtype != BT_GAP_ADV_TYPE_SCAN_RSP)) {
		uint8_t flags = get_ad_flags(ad);

		/* ignore non-discoverable devices */
		if (!(flags & BT_LE_AD_DISCOV_MASK)) {
			LOG_DBG("Non discoverable, skipping");
			return;
		}

		/* if Limited Discovery - ignore general discoverable devices */
		if ((discovery_flags & BTP_GAP_DISCOVERY_FLAG_LIMITED) &&
		    !(flags & BT_LE_AD_LIMITED)) {
			LOG_DBG("General discoverable, skipping");
			return;
		}
	}

	/* attach Scan Response data */
	if (evtype == BT_GAP_ADV_TYPE_SCAN_RSP) {
		struct btp_gap_device_found_ev *ev;
		bt_addr_le_t a;

		/* skip if there is no pending advertisement */
		if (!adv_buf->len) {
			LOG_INF("No pending advertisement, skipping");
			return;
		}

		ev = (void *) adv_buf->data;
		a.type = ev->address_type;
		memcpy(a.a.val, ev->address, sizeof(a.a.val));

		/*
		 * in general, the Scan Response comes right after the
		 * Advertisement, but if not if send stored event and ignore
		 * this one
		 */
		if (!bt_addr_le_eq(addr, &a)) {
			LOG_INF("Address does not match, skipping");
			goto done;
		}

		ev->eir_data_len += ad->len;
		ev->flags |= BTP_GAP_DEVICE_FOUND_FLAG_SD;

		memcpy(net_buf_simple_add(adv_buf, ad->len), ad->data, ad->len);

		goto done;
	}

	/*
	 * if there is another pending advertisement, send it and store the
	 * current one
	 */
	if (adv_buf->len) {
		tester_send(BTP_SERVICE_ID_GAP, BTP_GAP_EV_DEVICE_FOUND,
			    CONTROLLER_INDEX, adv_buf->data, adv_buf->len);
		net_buf_simple_reset(adv_buf);
	}

	store_adv(addr, rssi, ad);

	/* if Active Scan and scannable event - wait for Scan Response */
	if ((discovery_flags & BTP_GAP_DISCOVERY_FLAG_LE_ACTIVE_SCAN) &&
	    (evtype == BT_GAP_ADV_TYPE_ADV_IND ||
	     evtype == BT_GAP_ADV_TYPE_ADV_SCAN_IND)) {
		LOG_DBG("Waiting for scan response");
		return;
	}
done:
	tester_send(BTP_SERVICE_ID_GAP, BTP_GAP_EV_DEVICE_FOUND,
		    CONTROLLER_INDEX, adv_buf->data, adv_buf->len);
	net_buf_simple_reset(adv_buf);
}

static uint8_t start_discovery(uint8_t index, const void *cmd, uint16_t cmd_len,
			       void *rsp, uint16_t *rsp_len)
{
	const struct btp_gap_start_discovery_cmd *cp = cmd;

	if (index != CONTROLLER_INDEX) {
		return BTP_STATUS_FAILED;
	}

	/* only LE scan is supported */
	if (cp->flags & BTP_GAP_DISCOVERY_FLAG_BREDR) {
		LOG_WRN("BR/EDR not supported");
		return BTP_STATUS_FAILED;
	}

	if (bt_le_scan_start(cp->flags & BTP_GAP_DISCOVERY_FLAG_LE_ACTIVE_SCAN ?
			     BT_LE_SCAN_ACTIVE : BT_LE_SCAN_PASSIVE,
			     device_found) < 0) {
		LOG_ERR("Failed to start scanning");
		return BTP_STATUS_FAILED;
	}

	net_buf_simple_init(adv_buf, 0);
	discovery_flags = cp->flags;

	return BTP_STATUS_SUCCESS;
}

static uint8_t stop_discovery(uint8_t index, const void *cmd, uint16_t cmd_len,
			      void *rsp, uint16_t *rsp_len)
{
	int err;

	if (index != CONTROLLER_INDEX) {
		return BTP_STATUS_FAILED;
	}

	err = bt_le_scan_stop();
	if (err < 0) {
		LOG_ERR("Failed to stop scanning: %d", err);
		return BTP_STATUS_FAILED;
	}

	return BTP_STATUS_SUCCESS;
}

static uint8_t connect(uint8_t index, const void *cmd, uint16_t cmd_len,
		       void *rsp, uint16_t *rsp_len)
{
	const struct btp_gap_connect_cmd *cp = cmd;
	int err;

	if (index != CONTROLLER_INDEX) {
		return BTP_STATUS_FAILED;
	}

	if (!bt_addr_le_eq(&cp->address, BT_ADDR_LE_ANY)) {
		struct bt_conn *conn;

		err = bt_conn_le_create(&cp->address, BT_CONN_LE_CREATE_CONN,
					BT_LE_CONN_PARAM_DEFAULT, &conn);
		if (err) {
			LOG_ERR("Failed to create connection (%d)", err);
			return BTP_STATUS_FAILED;
		}

		bt_conn_unref(conn);
	} else {
		err = bt_conn_le_create_auto(BT_CONN_LE_CREATE_CONN,
					     BT_LE_CONN_PARAM_DEFAULT);
		if (err) {
			LOG_ERR("Failed to create auto connection (%d)", err);
			return BTP_STATUS_FAILED;
		}
	}

	return BTP_STATUS_SUCCESS;
}

static uint8_t disconnect(uint8_t index, const void *cmd, uint16_t cmd_len,
			  void *rsp, uint16_t *rsp_len)
{
	const struct btp_gap_disconnect_cmd *cp = cmd;
	struct bt_conn *conn;
	uint8_t status;

	if (index != CONTROLLER_INDEX) {
		return BTP_STATUS_FAILED;
	}

	conn = bt_conn_lookup_addr_le(BT_ID_DEFAULT, &cp->address);
	if (!conn) {
		LOG_ERR("Unknown connection");
		return BTP_STATUS_FAILED;
	}

	if (bt_conn_disconnect(conn, BT_HCI_ERR_REMOTE_USER_TERM_CONN)) {
		LOG_ERR("Failed to disconnect");
		status = BTP_STATUS_FAILED;
	} else {
		status = BTP_STATUS_SUCCESS;
	}

	bt_conn_unref(conn);

	return status;
}

static void auth_passkey_display(struct bt_conn *conn, unsigned int passkey)
{
	struct btp_gap_passkey_display_ev ev;
	const bt_addr_le_t *addr = bt_conn_get_dst(conn);

	memcpy(ev.address, addr->a.val, sizeof(ev.address));
	ev.address_type = addr->type;
	ev.passkey = sys_cpu_to_le32(passkey);

	tester_send(BTP_SERVICE_ID_GAP, BTP_GAP_EV_PASSKEY_DISPLAY,
		    CONTROLLER_INDEX, (uint8_t *) &ev, sizeof(ev));
}

static void auth_passkey_entry(struct bt_conn *conn)
{
	struct btp_gap_passkey_entry_req_ev ev;
	const bt_addr_le_t *addr = bt_conn_get_dst(conn);

	memcpy(ev.address, addr->a.val, sizeof(ev.address));
	ev.address_type = addr->type;

	tester_send(BTP_SERVICE_ID_GAP, BTP_GAP_EV_PASSKEY_ENTRY_REQ,
		    CONTROLLER_INDEX, (uint8_t *) &ev, sizeof(ev));
}

static void auth_passkey_confirm(struct bt_conn *conn, unsigned int passkey)
{
	struct btp_gap_passkey_confirm_req_ev ev;
	const bt_addr_le_t *addr = bt_conn_get_dst(conn);

	memcpy(ev.address, addr->a.val, sizeof(ev.address));
	ev.address_type = addr->type;
	ev.passkey = sys_cpu_to_le32(passkey);

	tester_send(BTP_SERVICE_ID_GAP, BTP_GAP_EV_PASSKEY_CONFIRM_REQ,
		    CONTROLLER_INDEX, (uint8_t *) &ev, sizeof(ev));
}

static void auth_cancel(struct bt_conn *conn)
{
	/* TODO */
}

enum bt_security_err auth_pairing_accept(struct bt_conn *conn,
					 const struct bt_conn_pairing_feat *const feat)
{
	struct btp_gap_bond_lost_ev ev;
	const bt_addr_le_t *addr = bt_conn_get_dst(conn);

	if (!bt_addr_le_is_bonded(BT_ID_DEFAULT, addr)) {
		return BT_SECURITY_ERR_SUCCESS;
	}

	/* If a peer is already bonded and tries to pair again then it means that
	 * the it has lost its bond information.
	 */
	LOG_DBG("Bond lost");

	memcpy(ev.address, addr->a.val, sizeof(ev.address));
	ev.address_type = addr->type;

	tester_send(BTP_SERVICE_ID_GAP, BTP_GAP_EV_BOND_LOST, CONTROLLER_INDEX, (uint8_t *)&ev,
		    sizeof(ev));

	return BT_SECURITY_ERR_SUCCESS;
}

void auth_pairing_failed(struct bt_conn *conn, enum bt_security_err reason)
{
	struct btp_gap_bond_pairing_failed_ev ev;
	const bt_addr_le_t *addr = bt_conn_get_dst(conn);

	memcpy(ev.address, addr->a.val, sizeof(ev.address));
	ev.address_type = addr->type;
	ev.reason = reason;

	tester_send(BTP_SERVICE_ID_GAP, BTP_GAP_EV_PAIRING_FAILED, CONTROLLER_INDEX,
		    (uint8_t *)&ev, sizeof(ev));
}

static void auth_pairing_complete(struct bt_conn *conn, bool bonded)
{
#if defined(CONFIG_BT_PRIVACY)
	/* Read peer's Central Address Resolution if bonded */
	if (bonded) {
		bt_gatt_read(conn, &read_car_params);
	}
#endif
}

static struct bt_conn_auth_info_cb auth_info_cb = {
	.pairing_failed = auth_pairing_failed,
	.pairing_complete = auth_pairing_complete,
};

static uint8_t set_io_cap(uint8_t index, const void *cmd, uint16_t cmd_len,
			  void *rsp, uint16_t *rsp_len)
{
	const struct btp_gap_set_io_cap_cmd *cp = cmd;

	if (index != CONTROLLER_INDEX) {
		return BTP_STATUS_FAILED;
	}

	/* Reset io cap requirements */
	(void)memset(&cb, 0, sizeof(cb));
	bt_conn_auth_cb_register(NULL);

	LOG_DBG("io_cap: %d", cp->io_cap);

	switch (cp->io_cap) {
	case BTP_GAP_IO_CAP_DISPLAY_ONLY:
		cb.cancel = auth_cancel;
		cb.passkey_display = auth_passkey_display;
		break;
	case BTP_GAP_IO_CAP_KEYBOARD_DISPLAY:
		cb.cancel = auth_cancel;
		cb.passkey_display = auth_passkey_display;
		cb.passkey_entry = auth_passkey_entry;
		cb.passkey_confirm = auth_passkey_confirm;
		break;
	case BTP_GAP_IO_CAP_NO_INPUT_OUTPUT:
		cb.cancel = auth_cancel;
		break;
	case BTP_GAP_IO_CAP_KEYBOARD_ONLY:
		cb.cancel = auth_cancel;
		cb.passkey_entry = auth_passkey_entry;
		break;
	case BTP_GAP_IO_CAP_DISPLAY_YESNO:
		cb.cancel = auth_cancel;
		cb.passkey_display = auth_passkey_display;
		cb.passkey_confirm = auth_passkey_confirm;
		break;
	default:
		LOG_WRN("Unhandled io_cap: 0x%x", cp->io_cap);
		return BTP_STATUS_FAILED;
	}

	cb.pairing_accept = auth_pairing_accept;

	if (bt_conn_auth_cb_register(&cb)) {
		return BTP_STATUS_FAILED;
	}

	return BTP_STATUS_SUCCESS;
}

static uint8_t pair(uint8_t index, const void *cmd, uint16_t cmd_len,
		    void *rsp, uint16_t *rsp_len)
{
	const struct btp_gap_pair_cmd *cp = cmd;
	struct bt_conn *conn;
	int err;

	if (index != CONTROLLER_INDEX) {
		return BTP_STATUS_FAILED;
	}

	conn = bt_conn_lookup_addr_le(BT_ID_DEFAULT, &cp->address);
	if (!conn) {
		LOG_ERR("Unknown connection");
		return BTP_STATUS_FAILED;
	}

	err = bt_conn_set_security(conn, BT_SECURITY_L2);
	if (err < 0) {
		LOG_ERR("Failed to set security: %d", err);
		bt_conn_unref(conn);
		return BTP_STATUS_FAILED;
	}

	bt_conn_unref(conn);
	return BTP_STATUS_SUCCESS;
}

static uint8_t unpair(uint8_t index, const void *cmd, uint16_t cmd_len,
		      void *rsp, uint16_t *rsp_len)
{
	const struct btp_gap_unpair_cmd *cp = cmd;
	struct bt_conn *conn;
	int err;

	if (index != CONTROLLER_INDEX) {
		return BTP_STATUS_FAILED;
	}

	conn = bt_conn_lookup_addr_le(BT_ID_DEFAULT, &cp->address);
	if (!conn) {
		LOG_INF("Unknown connection");
		goto keys;
	}

	err = bt_conn_disconnect(conn, BT_HCI_ERR_REMOTE_USER_TERM_CONN);

	bt_conn_unref(conn);

	if (err < 0) {
		LOG_ERR("Failed to disconnect: %d", err);
		return BTP_STATUS_FAILED;
	}
keys:
	err = bt_unpair(BT_ID_DEFAULT, &cp->address);
	if (err < 0) {
		return BTP_STATUS_FAILED;
	}

	return BTP_STATUS_SUCCESS;
}

static uint8_t passkey_entry(uint8_t index, const void *cmd, uint16_t cmd_len,
			     void *rsp, uint16_t *rsp_len)
{
	const struct btp_gap_passkey_entry_cmd *cp = cmd;
	struct bt_conn *conn;
	int err;

	if (index != CONTROLLER_INDEX) {
		return BTP_STATUS_FAILED;
	}

	conn = bt_conn_lookup_addr_le(BT_ID_DEFAULT, &cp->address);
	if (!conn) {
		LOG_ERR("Unknown connection");
		return BTP_STATUS_FAILED;
	}

	err = bt_conn_auth_passkey_entry(conn, sys_le32_to_cpu(cp->passkey));
	bt_conn_unref(conn);

	if (err < 0) {
		LOG_ERR("Failed to enter passkey: %d", err);
		return BTP_STATUS_FAILED;
	}

	return BTP_STATUS_SUCCESS;
}

static uint8_t passkey_confirm(uint8_t index, const void *cmd, uint16_t cmd_len,
			       void *rsp, uint16_t *rsp_len)
{
	const struct btp_gap_passkey_confirm_cmd *cp = cmd;
	struct bt_conn *conn;
	int err;

	if (index != CONTROLLER_INDEX) {
		return BTP_STATUS_FAILED;
	}

	conn = bt_conn_lookup_addr_le(BT_ID_DEFAULT, &cp->address);
	if (!conn) {
		LOG_ERR("Unknown connection");
		return BTP_STATUS_FAILED;
	}

	if (cp->match) {
		err = bt_conn_auth_passkey_confirm(conn);
		if (err < 0) {
			LOG_ERR("Failed to confirm passkey: %d", err);
		}
	} else {
		err = bt_conn_auth_cancel(conn);
		if (err < 0) {
			LOG_ERR("Failed to cancel auth: %d", err);
		}
	}

	bt_conn_unref(conn);

	if (err < 0) {
		return BTP_STATUS_FAILED;
	}

	return BTP_STATUS_SUCCESS;
}

static uint8_t conn_param_update(uint8_t index, const void *cmd, uint16_t cmd_len,
				 void *rsp, uint16_t *rsp_len)
{
	const struct btp_gap_conn_param_update_cmd *cp = cmd;
	struct bt_le_conn_param param = {
		.interval_min = sys_le16_to_cpu(cp->interval_min),
		.interval_max = sys_le16_to_cpu(cp->interval_max),
		.latency = sys_le16_to_cpu(cp->latency),
		.timeout = sys_le16_to_cpu(cp->timeout),
	};
	struct bt_conn *conn;
	int err;

	if (index != CONTROLLER_INDEX) {
		return BTP_STATUS_FAILED;
	}

	conn = bt_conn_lookup_addr_le(BT_ID_DEFAULT, &cp->address);
	if (!conn) {
		LOG_ERR("Unknown connection");
		return BTP_STATUS_FAILED;
	}

	err = bt_conn_le_param_update(conn, &param);
	bt_conn_unref(conn);

	if (err < 0) {
		LOG_ERR("Failed to update params: %d", err);
		return BTP_STATUS_FAILED;
	}
	return BTP_STATUS_SUCCESS;
}

static uint8_t set_mitm(uint8_t index, const void *cmd, uint16_t cmd_len,
			void *rsp, uint16_t *rsp_len)
{
	/* TODO verify if can be done in runtime */
	LOG_WRN("Use CONFIG_BT_SMP_ENFORCE_MITM instead");

	if (index != CONTROLLER_INDEX) {
		return BTP_STATUS_FAILED;
	}

	return BTP_STATUS_SUCCESS;
}

static uint8_t set_oob_legacy_data(uint8_t index, const void *cmd, uint16_t cmd_len,
				   void *rsp, uint16_t *rsp_len)
{
	const struct btp_gap_oob_legacy_set_data_cmd *cp = cmd;

	if (index != CONTROLLER_INDEX) {
		return BTP_STATUS_FAILED;
	}

	memcpy(oob_legacy_tk, cp->oob_data, 16);

	bt_set_oob_data_flag(true);
	cb.oob_data_request = oob_data_request;

	return BTP_STATUS_SUCCESS;
}

static uint8_t set_filter_list(uint8_t index, const void *cmd, uint16_t cmd_len,
			       void *rsp, uint16_t *rsp_len)
{
	const struct btp_gap_set_filter_list *cp = cmd;
	int err;

	if ((cmd_len < sizeof(*cp)) ||
	    (cmd_len != sizeof(*cp) + (cp->cnt * sizeof(cp->addr[0])))) {
		return BTP_STATUS_FAILED;
	}

	if (index != CONTROLLER_INDEX) {
		return BTP_STATUS_FAILED;
	}

	(void)bt_le_filter_accept_list_clear();

	for (int i = 0; i < cp->cnt; i++) {
		err = bt_le_filter_accept_list_add(&cp->addr[i]);
		if (err < 0) {
			return BTP_STATUS_FAILED;
		}
	}

	return BTP_STATUS_SUCCESS;
}

static const struct btp_handler handlers[] = {
	{
		.opcode = BTP_GAP_READ_SUPPORTED_COMMANDS,
		.expect_len = 0,
		.func = supported_commands,
	},
	{
		.opcode = BTP_GAP_READ_CONTROLLER_INDEX_LIST,
		.expect_len = 0,
		.func = controller_index_list,
	},
	{
		.opcode = BTP_GAP_READ_CONTROLLER_INFO,
		.expect_len = 0,
		.func = controller_info,
	},
	{
		.opcode = BTP_GAP_SET_CONNECTABLE,
		.expect_len = sizeof(struct btp_gap_set_connectable_cmd),
		.func = set_connectable,
	},
	{
		.opcode = BTP_GAP_SET_DISCOVERABLE,
		.expect_len = sizeof(struct btp_gap_set_discoverable_cmd),
		.func = set_discoverable,
	},
	{
		.opcode = BTP_GAP_SET_BONDABLE,
		.expect_len = sizeof(struct btp_gap_set_bondable_cmd),
		.func = set_bondable,
	},
	{
		.opcode = BTP_GAP_START_ADVERTISING,
		.expect_len = -1,
		.func = start_advertising,
	},
	{
		.opcode = BTP_GAP_START_DIRECTED_ADV,
		.expect_len = sizeof(struct btp_gap_start_directed_adv_cmd),
		.func = start_directed_advertising,
	},
	{
		.opcode = BTP_GAP_STOP_ADVERTISING,
		.expect_len = 0,
		.func = stop_advertising,
	},
	{
		.opcode = BTP_GAP_START_DISCOVERY,
		.expect_len = sizeof(struct btp_gap_start_discovery_cmd),
		.func = start_discovery,
	},
	{
		.opcode = BTP_GAP_STOP_DISCOVERY,
		.expect_len = 0,
		.func = stop_discovery,
	},
	{
		.opcode = BTP_GAP_CONNECT,
		.expect_len = sizeof(struct btp_gap_connect_cmd),
		.func = connect,
	},
	{
		.opcode = BTP_GAP_DISCONNECT,
		.expect_len = sizeof(struct btp_gap_disconnect_cmd),
		.func = disconnect,
	},
	{
		.opcode = BTP_GAP_SET_IO_CAP,
		.expect_len = sizeof(struct btp_gap_set_io_cap_cmd),
		.func = set_io_cap,
	},
	{
		.opcode = BTP_GAP_PAIR,
		.expect_len = sizeof(struct btp_gap_pair_cmd),
		.func = pair,
	},
	{
		.opcode = BTP_GAP_UNPAIR,
		.expect_len = sizeof(struct btp_gap_unpair_cmd),
		.func = unpair,
	},
	{
		.opcode = BTP_GAP_PASSKEY_ENTRY,
		.expect_len = sizeof(struct btp_gap_passkey_entry_cmd),
		.func = passkey_entry,
	},
	{
		.opcode = BTP_GAP_PASSKEY_CONFIRM,
		.expect_len = sizeof(struct btp_gap_passkey_confirm_cmd),
		.func = passkey_confirm,
	},
	{
		.opcode = BTP_GAP_CONN_PARAM_UPDATE,
		.expect_len = sizeof(struct btp_gap_conn_param_update_cmd),
		.func = conn_param_update,
	},
	{
		.opcode = BTP_GAP_SET_MITM,
		.expect_len = sizeof(struct btp_gap_set_mitm),
		.func = set_mitm,
	},
	{
		.opcode = BTP_GAP_OOB_LEGACY_SET_DATA,
		.expect_len = sizeof(struct btp_gap_oob_legacy_set_data_cmd),
		.func = set_oob_legacy_data,
	},
#if !defined(CONFIG_BT_SMP_OOB_LEGACY_PAIR_ONLY)
	{
		.opcode = BTP_GAP_OOB_SC_GET_LOCAL_DATA,
		.expect_len = 0,
		.func = get_oob_sc_local_data,
	},
	{
		.opcode = BTP_GAP_OOB_SC_SET_REMOTE_DATA,
		.expect_len = sizeof(struct btp_gap_oob_sc_set_remote_data_cmd),
		.func = set_oob_sc_remote_data,
	},
#endif /* !defined(CONFIG_BT_SMP_OOB_LEGACY_PAIR_ONLY) */
	{
		.opcode = BTP_GAP_SET_FILTER_LIST,
		.expect_len = -1,
		.func = set_filter_list,
	},
};

uint8_t tester_init_gap(void)
{
	int err;

	(void)memset(&cb, 0, sizeof(cb));
	bt_conn_auth_cb_register(NULL);
	cb.pairing_accept = auth_pairing_accept;
	if (bt_conn_auth_cb_register(&cb)) {
		return BTP_STATUS_FAILED;
	}

	err = bt_enable(NULL);
	if (err < 0) {
		LOG_ERR("Unable to enable Bluetooth: %d", err);
		return BTP_STATUS_FAILED;
	}

	atomic_clear(&current_settings);
	atomic_set_bit(&current_settings, BTP_GAP_SETTINGS_POWERED);
	atomic_set_bit(&current_settings, BTP_GAP_SETTINGS_CONNECTABLE);
	atomic_set_bit(&current_settings, BTP_GAP_SETTINGS_BONDABLE);
	atomic_set_bit(&current_settings, BTP_GAP_SETTINGS_LE);
#if defined(CONFIG_BT_PRIVACY)
	atomic_set_bit(&current_settings, BTP_GAP_SETTINGS_PRIVACY);
#endif /* CONFIG_BT_PRIVACY */

	bt_conn_cb_register(&conn_callbacks);
	bt_conn_auth_info_cb_register(&auth_info_cb);

	tester_register_command_handlers(BTP_SERVICE_ID_GAP, handlers,
					 ARRAY_SIZE(handlers));

	return BTP_STATUS_SUCCESS;
}

uint8_t tester_unregister_gap(void)
{
	return BTP_STATUS_SUCCESS;
}
