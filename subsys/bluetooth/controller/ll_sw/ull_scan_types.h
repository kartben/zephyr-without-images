/*
 * Copyright (c) 2018-2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

struct ll_scan_set {
	struct evt_hdr  evt;
	struct ull_hdr  ull;
	struct lll_scan lll;

#if defined(CONFIG_BT_CTLR_ADV_EXT)
	uint16_t duration_lazy;
	struct node_rx_hdr *node_rx_scan_term;
#endif /* CONFIG_BT_CTLR_ADV_EXT */

	uint8_t is_enabled:1;
	uint8_t own_addr_type:2;

#if defined(CONFIG_BT_CTLR_SYNC_PERIODIC)
	struct {
		uint8_t sid;

		uint8_t adv_addr_type:1;
		uint8_t filter_policy:1;
		uint8_t state:2;

		uint8_t adv_addr[BDADDR_SIZE];

		struct node_rx_hdr *node_rx_estab;

		/* Non-Null when creating sync, reset in ISR context on
		 * synchronisation state and checked in Thread context when
		 * cancelling sync create, hence the volatile keyword.
		 */
		struct ll_sync_set *volatile sync;
	} per_scan;
#endif
};

struct ll_scan_aux_set {
	struct evt_hdr      evt;
	struct ull_hdr      ull;
	struct lll_scan_aux lll;

	struct node_rx_hdr *rx_head;
	struct node_rx_hdr *rx_last;
};
