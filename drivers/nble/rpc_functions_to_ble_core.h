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

/* declare the list of functions sorted by signature */
#define LIST_FN_SIG_NONE

#define LIST_FN_SIG_S							\
	FN_SIG_S(ble_gap_start_advertise_req, struct ble_gap_adv_params *)

#define LIST_FN_SIG_P							\
	FN_SIG_P(ble_get_version_req, void *)				\
	FN_SIG_P(ble_gap_dtm_init_req, void *)				\
	FN_SIG_P(ble_gap_read_bda_req, void *)				\
	FN_SIG_P(ble_gap_stop_advertise_req, void *)			\
	FN_SIG_P(ble_gap_clr_white_list_req, void *)			\
	FN_SIG_P(ble_gap_stop_scan_req, void *)				\
	FN_SIG_P(ble_gap_sm_clear_bonds_req, void *)			\
	FN_SIG_P(ble_gap_cancel_connect_req, void *)			\
	FN_SIG_P(ble_get_bonded_device_list_req, void *)

#define LIST_FN_SIG_S_B							\
	FN_SIG_S_B(ble_gatt_register_req,				\
		   const struct ble_gatt_register_req *,		\
		   uint8_t *, uint16_t)					\
	FN_SIG_S_B(ble_gatt_send_notif_req,				\
		   const struct ble_gatt_send_notif_ind_params *,	\
		   uint8_t *, uint16_t)					\
	FN_SIG_S_B(ble_gatt_send_ind_req,				\
		   const struct ble_gatt_send_notif_ind_params *,	\
		   uint8_t *, uint8_t)					\
	FN_SIG_S_B(nble_gatts_authorize_reply_req,			\
		   const struct ble_gatts_rw_reply_params *,		\
		   uint8_t *, uint16_t)

#define LIST_FN_SIG_B_B_P						\
	FN_SIG_B_B_P(ble_gap_wr_white_list_req, bt_addr_le_t *,		\
		     uint8_t, struct ble_gap_irk_info *,		\
		     uint8_t, void *)

#define LIST_FN_SIG_S_P							\
	FN_SIG_S_P(ble_gap_disconnect_req,				\
		   const struct ble_gap_disconnect_req_params *, void *)\
	FN_SIG_S_P(ble_gap_sm_pairing_req,				\
		   const struct ble_core_gap_sm_pairing_req_params *,	\
		   void *)						\
	FN_SIG_S_P(ble_gap_sm_config_req,				\
		   const struct ble_core_gap_sm_config_params *, void *)\
	FN_SIG_S_P(ble_gap_sm_passkey_reply_req,			\
		   const struct ble_gap_sm_key_reply_req_params *,	\
		   void *)						\
	FN_SIG_S_P(ble_gap_connect_req,					\
		   const struct ble_gap_connect_req_params *, void *)	\
	FN_SIG_S_P(ble_gap_start_scan_req,				\
		   const struct ble_gap_scan_params *, void *)		\
	FN_SIG_S_P(ble_gap_generic_cmd_req,				\
		   const struct ble_gap_gen_cmd_params *, void *)	\
	FN_SIG_S_P(ble_gap_set_option_req,				\
		   const struct ble_gap_set_option_params *, void *)	\
	FN_SIG_S_P(ble_gap_conn_update_req,				\
		   const struct ble_gap_connect_update_params *, void *)\
	FN_SIG_S_P(ble_gap_service_read_req,				\
		   const struct ble_gap_service_read_params *, void *)	\
	FN_SIG_S_P(ble_set_enable_config_req,				\
		   const struct ble_wr_config_params *, void *)		\
	FN_SIG_S_P(ble_gap_set_rssi_report_req,				\
		   const struct ble_core_rssi_report_params *, void *)	\
	FN_SIG_S_P(ble_gap_service_write_req,				\
		   const struct ble_gap_service_write_params *, void *)	\
	FN_SIG_S_P(ble_gap_dbg_req, const struct debug_params *, void *)\
	FN_SIG_S_P(ble_gattc_discover_req,				\
		   const struct ble_core_discover_params *, void *)	\
	FN_SIG_S_P(ble_gattc_read_req,					\
		   const struct ble_gattc_read_params *, void *)	\
	FN_SIG_S_P(ble_gatts_send_svc_changed_req,			\
		   const struct ble_gatts_svc_changed_params *, void *)	\
	FN_SIG_S_P(ble_gatts_get_attribute_value_req,			\
		   const struct ble_gatts_get_attribute_params *,	\
		   void *)

#define LIST_FN_SIG_S_B_P						\
	FN_SIG_S_B_P(ble_gattc_write_req,				\
		     const struct  ble_gattc_write_params *,		\
		     const uint8_t *, uint8_t, void *)

#define LIST_FN_SIG_S_B_B_P
