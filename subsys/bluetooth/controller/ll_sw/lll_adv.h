/*
 * Copyright (c) 2017-2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

struct lll_adv_iso {
	struct lll_hdr hdr;
	struct lll_adv *adv;

	uint8_t seed_access_addr[4];
	uint8_t base_crc_init[2];
	uint16_t latency_prepare;
	uint16_t latency_event;
	uint16_t data_chan_prn_s;
	uint16_t data_chan_remap_idx;

	uint64_t payload_count:39;
	uint64_t enc:1;
	uint64_t framing:1;
	uint64_t handle:8;
	uint64_t cssn:3;

	uint8_t data_chan_map[5];
	uint8_t data_chan_count:6;
	uint8_t num_bis:5;
	uint8_t bn:3;
	uint8_t nse:5;
	uint8_t phy:3;

	uint32_t sub_interval:20;
	uint32_t max_pdu:8;
	uint32_t pto:4;

	uint32_t bis_spacing:20;
	uint32_t max_sdu:8;
	uint32_t irc:4;

	uint32_t sdu_interval:20;
	uint32_t irc_curr:4;
	uint32_t ptc_curr:4;
	uint32_t ptc:4;

	uint8_t bn_curr:3;
	uint8_t bis_curr:5;

	uint8_t phy_flags:1;

	uint8_t term_req:1;
	uint8_t term_ack:1;
	uint8_t term_reason;
	uint8_t chm_req;
	uint8_t chm_ack;

	uint8_t  ctrl_chan_use;
	uint8_t  ctrl_expire;
	uint16_t ctrl_instant;
};

struct lll_adv_sync {
	struct lll_hdr hdr;
	struct lll_adv *adv;

	uint8_t access_addr[4];
	uint8_t crc_init[3];

	uint16_t latency_prepare;
	uint16_t latency_event;
	uint16_t event_counter;

	uint16_t data_chan_id;
	struct {
		uint8_t data_chan_map[PDU_CHANNEL_MAP_SIZE];
		uint8_t data_chan_count:6;
	} chm[DOUBLE_BUFFER_SIZE];
	uint8_t  chm_first;
	uint8_t  chm_last;
	uint16_t chm_instant;

	uint32_t ticks_offset;

	struct lll_adv_pdu data;
#if defined(CONFIG_BT_CTLR_ADV_PDU_LINK)
	struct pdu_adv *last_pdu;
#endif /* CONFIG_BT_CTLR_ADV_PDU_LINK */

#if defined(CONFIG_BT_CTLR_ADV_ISO)
	struct lll_adv_iso *iso;
#endif /* CONFIG_BT_CTLR_ADV_ISO */

#if defined(CONFIG_BT_CTLR_DF_ADV_CTE_TX)
	/* This flag is used only by LLL. It holds information if CTE
	 * transmission was started by LLL.
	 */
	uint8_t cte_started:1;
#endif /* CONFIG_BT_CTLR_DF_ADV_CTE_TX */

#if defined(CONFIG_BT_CTLR_TX_PWR_DYNAMIC_CONTROL)
	int8_t tx_pwr_lvl;
#endif /* CONFIG_BT_CTLR_TX_PWR_DYNAMIC_CONTROL */
};

struct lll_adv_aux {
	struct lll_hdr hdr;
	struct lll_adv *adv;

	/* Implementation defined radio event counter to calculate auxiliary
	 * PDU channel index.
	 */
	uint16_t data_chan_counter;

	/* Temporary stored use by primary channel PDU event to fill the
	 * auxiliary offset to this auxiliary PDU event.
	 */
	uint32_t ticks_offset;

	struct lll_adv_pdu data;
#if defined(CONFIG_BT_CTLR_ADV_PDU_LINK)
	struct pdu_adv     *last_pdu;
#endif /* CONFIG_BT_CTLR_ADV_PDU_LINK */

#if defined(CONFIG_BT_CTLR_TX_PWR_DYNAMIC_CONTROL)
	int8_t tx_pwr_lvl;
#endif /* CONFIG_BT_CTLR_TX_PWR_DYNAMIC_CONTROL */
};

struct lll_adv {
	struct lll_hdr hdr;

#if defined(CONFIG_BT_PERIPHERAL)
	/* NOTE: conn context SHALL be after lll_hdr,
	 *       check ull_conn_setup how it access the connection LLL
	 *       context.
	 */
	struct lll_conn *conn;
	uint8_t is_hdcd:1;
#endif /* CONFIG_BT_PERIPHERAL */

	uint8_t chan_map:3;
	uint8_t chan_map_curr:3;
	uint8_t filter_policy:2;

#if defined(CONFIG_BT_CTLR_ADV_EXT)
	uint8_t phy_p:3;
	uint8_t phy_s:3;
	uint8_t phy_flags:1;
#endif /* CONFIG_BT_CTLR_ADV_EXT */

#if defined(CONFIG_BT_CTLR_SCAN_REQ_NOTIFY)
	uint8_t scan_req_notify:1;
#endif

#if defined(CONFIG_BT_HCI_MESH_EXT)
	uint8_t is_mesh:1;
#endif /* CONFIG_BT_HCI_MESH_EXT */

#if defined(CONFIG_BT_CTLR_PRIVACY)
	uint8_t  rl_idx;
#endif /* CONFIG_BT_CTLR_PRIVACY */

	struct lll_adv_pdu adv_data;
	struct lll_adv_pdu scan_rsp;

#if defined(CONFIG_BT_CTLR_ADV_EXT)
	struct node_rx_hdr *node_rx_adv_term;
	struct lll_adv_aux *aux;

#if defined(CONFIG_BT_CTLR_ADV_PERIODIC)
	struct lll_adv_sync *sync;
#endif /* CONFIG_BT_CTLR_ADV_PERIODIC */
#endif /* CONFIG_BT_CTLR_ADV_EXT */

#if defined(CONFIG_BT_CTLR_TX_PWR_DYNAMIC_CONTROL)
	int8_t tx_pwr_lvl;
#endif /* CONFIG_BT_CTLR_TX_PWR_DYNAMIC_CONTROL */
};

int lll_adv_init(void);
int lll_adv_reset(void);
void lll_adv_prepare(void *param);

extern uint16_t ull_adv_lll_handle_get(struct lll_adv *lll);
