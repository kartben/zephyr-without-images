/*
 * Copyright (c) 2018-2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include <toolchain.h>
#include <soc.h>

#include <sys/util.h>

#include "hal/cpu.h"
#include "hal/ccm.h"
#include "hal/radio.h"

#include "util/mem.h"
#include "util/memq.h"
#include "util/mfifo.h"

#include "pdu.h"

#include "lll.h"
#include "lll_clock.h"
#include "lll_conn.h"

#include "lll_internal.h"
#include "lll_tim_internal.h"
#include "lll_prof_internal.h"

#define BT_DBG_ENABLED IS_ENABLED(CONFIG_BT_DEBUG_HCI_DRIVER)
#define LOG_MODULE_NAME bt_ctlr_lll_conn
#include "common/log.h"
#include "hal/debug.h"

static int init_reset(void);
static void isr_done(void *param);
static inline int isr_rx_pdu(struct lll_conn *lll, struct pdu_data *pdu_data_rx,
			     uint8_t *is_rx_enqueue,
			     struct node_tx **tx_release, uint8_t *is_done);
static void empty_tx_init(void);

static uint8_t crc_expire;
static uint8_t crc_valid;
static uint16_t trx_cnt;

#if defined(CONFIG_BT_CTLR_LE_ENC)
static uint8_t mic_state;
#endif /* CONFIG_BT_CTLR_LE_ENC */

#if defined(CONFIG_BT_CTLR_FORCE_MD_COUNT) && \
	(CONFIG_BT_CTLR_FORCE_MD_COUNT > 0)
#if defined(CONFIG_BT_CTLR_FORCE_MD_AUTO)
static uint8_t force_md_cnt_reload;
#define BT_CTLR_FORCE_MD_COUNT force_md_cnt_reload
#else
#define BT_CTLR_FORCE_MD_COUNT CONFIG_BT_CTLR_FORCE_MD_COUNT
#endif
static uint8_t force_md_cnt;

#define FORCE_MD_CNT_INIT() \
		{ \
			force_md_cnt = 0U; \
		}

#define FORCE_MD_CNT_DEC() \
		do { \
			if (force_md_cnt) { \
				force_md_cnt--; \
			} \
		} while (0)

#define FORCE_MD_CNT_GET() force_md_cnt

#define FORCE_MD_CNT_SET() \
		do { \
			if (force_md_cnt || \
			    (trx_cnt >= ((CONFIG_BT_CTLR_TX_BUFFERS) - 1))) { \
				force_md_cnt = BT_CTLR_FORCE_MD_COUNT; \
			} \
		} while (0)

#else /* !CONFIG_BT_CTLR_FORCE_MD_COUNT */
#define FORCE_MD_CNT_INIT()
#define FORCE_MD_CNT_DEC()
#define FORCE_MD_CNT_GET() 0
#define FORCE_MD_CNT_SET()
#endif /* !CONFIG_BT_CTLR_FORCE_MD_COUNT */

int lll_conn_init(void)
{
	int err;

	err = init_reset();
	if (err) {
		return err;
	}

	empty_tx_init();

	return 0;
}

int lll_conn_reset(void)
{
	int err;

	err = init_reset();
	if (err) {
		return err;
	}

	FORCE_MD_CNT_INIT();

	return 0;
}

void lll_conn_flush(uint16_t handle, struct lll_conn *lll)
{
	/* Nothing to be flushed */
}

void lll_conn_prepare_reset(void)
{
	trx_cnt = 0U;
	crc_valid = 0U;
	crc_expire = 0U;

#if defined(CONFIG_BT_CTLR_LE_ENC)
	mic_state = LLL_CONN_MIC_NONE;
#endif /* CONFIG_BT_CTLR_LE_ENC */
}

void lll_conn_abort_cb(struct lll_prepare_param *prepare_param, void *param)
{
	int err;

	/* NOTE: This is not a prepare being cancelled */
	if (!prepare_param) {
		/* Perform event abort here.
		 * After event has been cleanly aborted, clean up resources
		 * and dispatch event done.
		 */
		radio_isr_set(isr_done, param);
		radio_disable();
		return;
	}

	/* NOTE: Else clean the top half preparations of the aborted event
	 * currently in preparation pipeline.
	 */
	err = lll_hfclock_off();
	LL_ASSERT(err >= 0);

	lll_done(param);
}

void lll_conn_isr_rx(void *param)
{
	uint8_t is_empty_pdu_tx_retry;
	struct pdu_data *pdu_data_rx;
	struct pdu_data *pdu_data_tx;
	struct node_rx_pdu *node_rx;
	struct node_tx *tx_release;
	uint8_t is_rx_enqueue;
	struct lll_conn *lll;
	uint8_t rssi_ready;
	uint8_t is_ull_rx;
	uint8_t trx_done;
	uint8_t is_done;
	uint8_t crc_ok;

	if (IS_ENABLED(CONFIG_BT_CTLR_PROFILE_ISR)) {
		lll_prof_latency_capture();
	}

	/* Read radio status and events */
	trx_done = radio_is_done();
	if (trx_done) {
		crc_ok = radio_crc_is_valid();
		rssi_ready = radio_rssi_is_ready();
	} else {
		crc_ok = rssi_ready = 0U;
	}

	/* Clear radio rx status and events */
	lll_isr_rx_status_reset();

	/* No Rx */
	if (!trx_done) {
		radio_isr_set(isr_done, param);
		radio_disable();

		return;
	}

	trx_cnt++;

	is_done = 0U;
	tx_release = NULL;
	is_rx_enqueue = 0U;

	lll = param;

	node_rx = ull_pdu_rx_alloc_peek(1);
	LL_ASSERT(node_rx);

	pdu_data_rx = (void *)node_rx->pdu;

	if (crc_ok) {
		uint32_t err;

		err = isr_rx_pdu(lll, pdu_data_rx, &is_rx_enqueue, &tx_release,
				 &is_done);
		if (err) {
			goto lll_conn_isr_rx_exit;
		}

		/* Reset CRC expiry counter */
		crc_expire = 0U;

		/* CRC valid flag used to detect supervision timeout */
		crc_valid = 1U;
	} else {
		/* Start CRC error countdown, if not already started */
		if (crc_expire == 0U) {
			crc_expire = 2U;
		}

		/* CRC error countdown */
		crc_expire--;
		is_done = (crc_expire == 0U);
	}

	/* prepare tx packet */
	is_empty_pdu_tx_retry = lll->empty;
	lll_conn_pdu_tx_prep(lll, &pdu_data_tx);

	/* Decide on event continuation and hence Radio Shorts to use */
	is_done = is_done || ((crc_ok) && (pdu_data_rx->md == 0) &&
			      (pdu_data_tx->md == 0) &&
			      (pdu_data_tx->len == 0));

	if (is_done) {
		radio_isr_set(isr_done, param);

		if (0) {
#if defined(CONFIG_BT_CENTRAL)
		/* Event done for master */
		} else if (!lll->role) {
			radio_disable();

			/* assert if radio packet ptr is not set and radio
			 * started tx.
			 */
			LL_ASSERT(!radio_is_ready());

			/* Restore state if last transmitted was empty PDU */
			lll->empty = is_empty_pdu_tx_retry;

			goto lll_conn_isr_rx_exit;
#endif /* CONFIG_BT_CENTRAL */
#if defined(CONFIG_BT_PERIPHERAL)
		/* Event done for slave */
		} else {
			radio_switch_complete_and_disable();
#endif /* CONFIG_BT_PERIPHERAL */
		}
	} else {
		radio_tmr_tifs_set(EVENT_IFS_US);

#if defined(CONFIG_BT_CTLR_PHY)
		radio_switch_complete_and_rx(lll->phy_rx);
#else /* !CONFIG_BT_CTLR_PHY */
		radio_switch_complete_and_rx(0);
#endif /* !CONFIG_BT_CTLR_PHY */

		radio_isr_set(lll_conn_isr_tx, param);

		/* capture end of Tx-ed PDU, used to calculate HCTO. */
		radio_tmr_end_capture();
	}

	/* Fill sn and nesn */
	pdu_data_tx->sn = lll->sn;
	pdu_data_tx->nesn = lll->nesn;

	/* setup the radio tx packet buffer */
	lll_conn_tx_pkt_set(lll, pdu_data_tx);

#if defined(CONFIG_BT_CTLR_GPIO_PA_PIN)

#if defined(CONFIG_BT_CTLR_PROFILE_ISR)
	/* PA enable is overwriting packet end used in ISR profiling, hence
	 * back it up for later use.
	 */
	lll_prof_radio_end_backup();
#endif /* CONFIG_BT_CTLR_PROFILE_ISR */

	radio_gpio_pa_setup();

#if defined(CONFIG_BT_CTLR_PHY)
	radio_gpio_pa_lna_enable(radio_tmr_tifs_base_get() + EVENT_IFS_US -
				 radio_rx_chain_delay_get(lll->phy_rx, 1) -
				 CONFIG_BT_CTLR_GPIO_PA_OFFSET);
#else /* !CONFIG_BT_CTLR_PHY */
	radio_gpio_pa_lna_enable(radio_tmr_tifs_base_get() + EVENT_IFS_US -
				 radio_rx_chain_delay_get(0, 0) -
				 CONFIG_BT_CTLR_GPIO_PA_OFFSET);
#endif /* !CONFIG_BT_CTLR_PHY */
#endif /* CONFIG_BT_CTLR_GPIO_PA_PIN */

	/* assert if radio packet ptr is not set and radio started tx */
	LL_ASSERT(!radio_is_ready());

lll_conn_isr_rx_exit:
	/* Save the AA captured for the first Rx in connection event */
	if (!radio_tmr_aa_restore()) {
		radio_tmr_aa_save(radio_tmr_aa_get());
	}

#if defined(CONFIG_BT_CTLR_PROFILE_ISR)
	lll_prof_cputime_capture();
#endif /* CONFIG_BT_CTLR_PROFILE_ISR */

	is_ull_rx = 0U;

	if (tx_release) {
		LL_ASSERT(lll->handle != 0xFFFF);

		ull_conn_lll_ack_enqueue(lll->handle, tx_release);

		is_ull_rx = 1U;
	}

	if (is_rx_enqueue) {
#if defined(CONFIG_SOC_COMPATIBLE_NRF52832) && \
	defined(CONFIG_BT_CTLR_LE_ENC) && \
	defined(HAL_RADIO_PDU_LEN_MAX) && \
	(!defined(CONFIG_BT_CTLR_DATA_LENGTH_MAX) || \
	 (CONFIG_BT_CTLR_DATA_LENGTH_MAX < (HAL_RADIO_PDU_LEN_MAX - 4)))
		if (lll->enc_rx) {
			uint8_t *pkt_decrypt_data;

			pkt_decrypt_data = (uint8_t *)radio_pkt_decrypt_get() +
					   offsetof(struct pdu_data, lldata);
			memcpy((void *)pdu_data_rx->lldata,
			       (void *)pkt_decrypt_data, pdu_data_rx->len);
		}
#elif !defined(HAL_RADIO_PDU_LEN_MAX)
#error "Undefined HAL_RADIO_PDU_LEN_MAX."
#endif

		ull_pdu_rx_alloc();

		node_rx->hdr.type = NODE_RX_TYPE_DC_PDU;
		node_rx->hdr.handle = lll->handle;

		ull_rx_put(node_rx->hdr.link, node_rx);
		is_ull_rx = 1U;
	}

	if (is_ull_rx) {
		ull_rx_sched();
	}

#if defined(CONFIG_BT_CTLR_CONN_RSSI)
	/* Collect RSSI for connection */
	if (rssi_ready) {
		uint8_t rssi = radio_rssi_get();

		lll->rssi_latest = rssi;

#if defined(CONFIG_BT_CTLR_CONN_RSSI_EVENT)
		if (((lll->rssi_reported - rssi) & 0xFF) >
		    LLL_CONN_RSSI_THRESHOLD) {
			if (lll->rssi_sample_count) {
				lll->rssi_sample_count--;
			}
		} else {
			lll->rssi_sample_count = LLL_CONN_RSSI_SAMPLE_COUNT;
		}
#endif /* CONFIG_BT_CTLR_CONN_RSSI_EVENT */
	}
#else /* !CONFIG_BT_CTLR_CONN_RSSI */
	ARG_UNUSED(rssi_ready);
#endif /* !CONFIG_BT_CTLR_CONN_RSSI */

#if defined(CONFIG_BT_CTLR_PROFILE_ISR)
	lll_prof_send();
#endif /* CONFIG_BT_CTLR_PROFILE_ISR */
}

void lll_conn_isr_tx(void *param)
{
	struct lll_conn *lll;
	uint32_t hcto;

	/* Clear radio tx status and events */
	lll_isr_tx_status_reset();

	/* setup tIFS switching */
	radio_tmr_tifs_set(EVENT_IFS_US);

	lll = param;

#if defined(CONFIG_BT_CTLR_PHY)
	radio_switch_complete_and_tx(lll->phy_rx, 0,
				     lll->phy_tx,
				     lll->phy_flags);
#else /* !CONFIG_BT_CTLR_PHY */
	radio_switch_complete_and_tx(0, 0, 0, 0);
#endif /* !CONFIG_BT_CTLR_PHY */

	lll_conn_rx_pkt_set(lll);

	/* assert if radio packet ptr is not set and radio started rx */
	LL_ASSERT(!radio_is_ready());

	/* +/- 2us active clock jitter, +1 us hcto compensation */
	hcto = radio_tmr_tifs_base_get() + EVENT_IFS_US + 4 +
		RANGE_DELAY_US + 1;
#if defined(CONFIG_BT_CTLR_PHY)
	hcto += radio_rx_chain_delay_get(lll->phy_rx, 1);
	hcto += addr_us_get(lll->phy_rx);
	hcto -= radio_tx_chain_delay_get(lll->phy_tx, lll->phy_flags);
#else /* !CONFIG_BT_CTLR_PHY */
	hcto += radio_rx_chain_delay_get(0, 0);
	hcto += addr_us_get(0);
	hcto -= radio_tx_chain_delay_get(0, 0);
#endif /* !CONFIG_BT_CTLR_PHY */

	radio_tmr_hcto_configure(hcto);

#if defined(CONFIG_BT_CENTRAL) && defined(CONFIG_BT_CTLR_CONN_RSSI)
	if (!trx_cnt && !lll->role) {
		radio_rssi_measure();
	}
#endif /* CONFIG_BT_CENTRAL && CONFIG_BT_CTLR_CONN_RSSI */

#if defined(CONFIG_BT_CTLR_PROFILE_ISR) || \
	defined(CONFIG_BT_CTLR_GPIO_PA_PIN)
	radio_tmr_end_capture();
#endif /* CONFIG_BT_CTLR_PROFILE_ISR */

#if defined(CONFIG_BT_CTLR_GPIO_LNA_PIN)
	radio_gpio_lna_setup();
#if defined(CONFIG_BT_CTLR_PHY)
	radio_gpio_pa_lna_enable(radio_tmr_tifs_base_get() + EVENT_IFS_US - 4 -
				 radio_tx_chain_delay_get(lll->phy_tx,
							  lll->phy_flags) -
				 CONFIG_BT_CTLR_GPIO_LNA_OFFSET);
#else /* !CONFIG_BT_CTLR_PHY */
	radio_gpio_pa_lna_enable(radio_tmr_tifs_base_get() + EVENT_IFS_US - 4 -
				 radio_tx_chain_delay_get(0, 0) -
				 CONFIG_BT_CTLR_GPIO_LNA_OFFSET);
#endif /* !CONFIG_BT_CTLR_PHY */
#endif /* CONFIG_BT_CTLR_GPIO_LNA_PIN */

	radio_isr_set(lll_conn_isr_rx, param);
}

void lll_conn_rx_pkt_set(struct lll_conn *lll)
{
	struct node_rx_pdu *node_rx;
	uint16_t max_rx_octets;
	uint8_t phy;

	node_rx = ull_pdu_rx_alloc_peek(1);
	LL_ASSERT(node_rx);

#if defined(CONFIG_BT_CTLR_DATA_LENGTH)
	max_rx_octets = lll->max_rx_octets;
#else /* !CONFIG_BT_CTLR_DATA_LENGTH */
	max_rx_octets = PDU_DC_PAYLOAD_SIZE_MIN;
#endif /* !CONFIG_BT_CTLR_DATA_LENGTH */

#if defined(CONFIG_BT_CTLR_PHY)
	phy = lll->phy_rx;
#else /* !CONFIG_BT_CTLR_PHY */
	phy = 0U;
#endif /* !CONFIG_BT_CTLR_PHY */

	radio_phy_set(phy, 0);

	if (0) {
#if defined(CONFIG_BT_CTLR_LE_ENC)
	} else if (lll->enc_rx) {
		radio_pkt_configure(8, (max_rx_octets + 4), (phy << 1) | 0x01);

#if defined(CONFIG_SOC_COMPATIBLE_NRF52832) && \
	defined(HAL_RADIO_PDU_LEN_MAX) && \
	(!defined(CONFIG_BT_CTLR_DATA_LENGTH_MAX) || \
	 (CONFIG_BT_CTLR_DATA_LENGTH_MAX < (HAL_RADIO_PDU_LEN_MAX - 4)))
		radio_pkt_rx_set(radio_ccm_rx_pkt_set(&lll->ccm_rx, phy,
						      radio_pkt_decrypt_get()));
#elif !defined(HAL_RADIO_PDU_LEN_MAX)
#error "Undefined HAL_RADIO_PDU_LEN_MAX."
#else
		radio_pkt_rx_set(radio_ccm_rx_pkt_set(&lll->ccm_rx, phy,
						      node_rx->pdu));
#endif
#endif /* CONFIG_BT_CTLR_LE_ENC */
	} else {
		radio_pkt_configure(8, max_rx_octets, (phy << 1) | 0x01);

		radio_pkt_rx_set(node_rx->pdu);
	}
}

void lll_conn_tx_pkt_set(struct lll_conn *lll, struct pdu_data *pdu_data_tx)
{
	uint16_t max_tx_octets;
	uint8_t phy, flags;

#if defined(CONFIG_BT_CTLR_DATA_LENGTH)
	max_tx_octets = lll->max_tx_octets;
#else /* !CONFIG_BT_CTLR_DATA_LENGTH */
	max_tx_octets = PDU_DC_PAYLOAD_SIZE_MIN;
#endif /* !CONFIG_BT_CTLR_DATA_LENGTH */

#if defined(CONFIG_BT_CTLR_PHY)
	phy = lll->phy_tx;
	flags = lll->phy_flags;
#else /* !CONFIG_BT_CTLR_PHY */
	phy = 0U;
	flags = 0U;
#endif /* !CONFIG_BT_CTLR_PHY */

	radio_phy_set(phy, flags);

	if (0) {
#if defined(CONFIG_BT_CTLR_LE_ENC)
	} else if (lll->enc_tx) {
		radio_pkt_configure(8, (max_tx_octets + 4U),
				    (phy << 1) | 0x01);

		radio_pkt_tx_set(radio_ccm_tx_pkt_set(&lll->ccm_tx,
						      pdu_data_tx));
#endif /* CONFIG_BT_CTLR_LE_ENC */
	} else {
		radio_pkt_configure(8, max_tx_octets, (phy << 1) | 0x01);

		radio_pkt_tx_set(pdu_data_tx);
	}
}

void lll_conn_pdu_tx_prep(struct lll_conn *lll, struct pdu_data **pdu_data_tx)
{
	struct node_tx *tx;
	struct pdu_data *p;
	memq_link_t *link;

	link = memq_peek(lll->memq_tx.head, lll->memq_tx.tail, (void **)&tx);
	if (lll->empty || !link) {
		lll->empty = 1U;

		p = (void *)radio_pkt_empty_get();
		if (link || FORCE_MD_CNT_GET()) {
			p->md = 1U;
		} else {
			p->md = 0U;
		}
	} else {
		uint16_t max_tx_octets;

		p = (void *)(tx->pdu + lll->packet_tx_head_offset);

		if (!lll->packet_tx_head_len) {
			lll->packet_tx_head_len = p->len;
		}

		if (lll->packet_tx_head_offset) {
			p->ll_id = PDU_DATA_LLID_DATA_CONTINUE;
		}

		p->len = lll->packet_tx_head_len - lll->packet_tx_head_offset;

		max_tx_octets = ull_conn_lll_max_tx_octets_get(lll);

		if (p->len > max_tx_octets) {
			p->len = max_tx_octets;
			p->md = 1U;
		} else if ((link->next != lll->memq_tx.tail) ||
			   FORCE_MD_CNT_GET()) {
			p->md = 1U;
		} else {
			p->md = 0U;
		}

		p->rfu = 0U;

#if !defined(CONFIG_BT_CTLR_DATA_LENGTH_CLEAR)
		p->resv = 0U;
#endif /* !CONFIG_BT_CTLR_DATA_LENGTH_CLEAR */
	}

	*pdu_data_tx = p;
}

#if defined(CONFIG_BT_CTLR_FORCE_MD_AUTO)
uint8_t lll_conn_force_md_cnt_set(uint8_t force_md_cnt)
{
	uint8_t previous;

	previous = force_md_cnt_reload;
	force_md_cnt_reload = force_md_cnt;

	return previous;
}
#endif /* CONFIG_BT_CTLR_FORCE_MD_AUTO */

static int init_reset(void)
{
	return 0;
}

static void isr_done(void *param)
{
	struct event_done_extra *e;

	lll_isr_status_reset();

	e = ull_event_done_extra_get();
	LL_ASSERT(e);

	e->type = EVENT_DONE_EXTRA_TYPE_CONN;
	e->trx_cnt = trx_cnt;
	e->crc_valid = crc_valid;

#if defined(CONFIG_BT_CTLR_LE_ENC)
	e->mic_state = mic_state;
#endif /* CONFIG_BT_CTLR_LE_ENC */

#if defined(CONFIG_BT_PERIPHERAL)
	if (trx_cnt) {
		struct lll_conn *lll = param;

		if (lll->role) {
			uint32_t preamble_to_addr_us;

#if defined(CONFIG_BT_CTLR_PHY)
			preamble_to_addr_us =
				addr_us_get(lll->phy_rx);
#else /* !CONFIG_BT_CTLR_PHY */
			preamble_to_addr_us =
				addr_us_get(0);
#endif /* !CONFIG_BT_CTLR_PHY */

			e->drift.start_to_address_actual_us =
				radio_tmr_aa_restore() - radio_tmr_ready_get();
			e->drift.window_widening_event_us =
				lll->slave.window_widening_event_us;
			e->drift.preamble_to_addr_us = preamble_to_addr_us;

			/* Reset window widening, as anchor point sync-ed */
			lll->slave.window_widening_event_us = 0;
			lll->slave.window_size_event_us = 0;
		}
	}
#endif /* CONFIG_BT_PERIPHERAL */

	lll_isr_cleanup(param);
}

static inline bool ctrl_pdu_len_check(uint8_t len)
{
	return len <= (offsetof(struct pdu_data, llctrl) +
		       sizeof(struct pdu_data_llctrl));

}

static inline int isr_rx_pdu(struct lll_conn *lll, struct pdu_data *pdu_data_rx,
			     uint8_t *is_rx_enqueue,
			     struct node_tx **tx_release, uint8_t *is_done)
{
#if defined(CONFIG_SOC_COMPATIBLE_NRF52832) && \
	defined(CONFIG_BT_CTLR_LE_ENC) && \
	defined(HAL_RADIO_PDU_LEN_MAX) && \
	(!defined(CONFIG_BT_CTLR_DATA_LENGTH_MAX) || \
	 (CONFIG_BT_CTLR_DATA_LENGTH_MAX < (HAL_RADIO_PDU_LEN_MAX - 4)))
	if (lll->enc_rx) {
		uint8_t *pkt_decrypt;

		pkt_decrypt = radio_pkt_decrypt_get();
		memcpy((void *)pdu_data_rx, (void *)pkt_decrypt,
		       offsetof(struct pdu_data, lldata));
	}
#elif !defined(HAL_RADIO_PDU_LEN_MAX)
#error "Undefined HAL_RADIO_PDU_LEN_MAX."
#endif

	/* Ack for tx-ed data */
	if (pdu_data_rx->nesn != lll->sn) {
		struct pdu_data *pdu_data_tx;
		struct node_tx *tx;
		memq_link_t *link;

		/* Increment sequence number */
		lll->sn++;

#if defined(CONFIG_BT_PERIPHERAL)
		/* First ack (and redundantly any other ack) enable use of
		 * slave latency.
		 */
		if (lll->role) {
			lll->slave.latency_enabled = 1;
		}
#endif /* CONFIG_BT_PERIPHERAL */

		FORCE_MD_CNT_DEC();

		if (!lll->empty) {
			link = memq_peek(lll->memq_tx.head, lll->memq_tx.tail,
					 (void **)&tx);
		} else {
			lll->empty = 0;

			pdu_data_tx = (void *)radio_pkt_empty_get();
			if (IS_ENABLED(CONFIG_BT_CENTRAL) && !lll->role &&
			    !pdu_data_rx->md) {
				*is_done = !pdu_data_tx->md;
			}

			link = NULL;
		}

		if (link) {
			uint8_t pdu_data_tx_len;
			uint8_t offset;

			pdu_data_tx = (void *)(tx->pdu +
					       lll->packet_tx_head_offset);

			pdu_data_tx_len = pdu_data_tx->len;
#if defined(CONFIG_BT_CTLR_LE_ENC)
			if (pdu_data_tx_len != 0U) {
				/* if encrypted increment tx counter */
				if (lll->enc_tx) {
					lll->ccm_tx.counter++;
				}
			}
#endif /* CONFIG_BT_CTLR_LE_ENC */

			offset = lll->packet_tx_head_offset + pdu_data_tx_len;
			if (offset < lll->packet_tx_head_len) {
				lll->packet_tx_head_offset = offset;
			} else if (offset == lll->packet_tx_head_len) {
				lll->packet_tx_head_len = 0;
				lll->packet_tx_head_offset = 0;

				memq_dequeue(lll->memq_tx.tail,
					     &lll->memq_tx.head, NULL);

				/* TX node UPSTREAM, i.e. Tx node ack path */
				link->next = tx->next; /* Indicates ctrl or data
							* pool.
							*/
				tx->next = link;

				*tx_release = tx;

				FORCE_MD_CNT_SET();
			} else {
				LL_ASSERT(0);
			}

			if (IS_ENABLED(CONFIG_BT_CENTRAL) && !lll->role &&
			    !pdu_data_rx->md) {
				*is_done = !pdu_data_tx->md;
			}
		}
	}

	/* process received data */
	if ((pdu_data_rx->sn == lll->nesn) &&
	    /* check so that we will NEVER use the rx buffer reserved for empty
	     * packet and internal control enqueue
	     */
	    (ull_pdu_rx_alloc_peek(3) != 0)) {
		/* Increment next expected serial number */
		lll->nesn++;

		if (pdu_data_rx->len != 0) {
#if defined(CONFIG_BT_CTLR_LE_ENC)
			/* If required, wait for CCM to finish
			 */
			if (lll->enc_rx) {
				uint32_t done;

				done = radio_ccm_is_done();
				LL_ASSERT(done);

				bool mic_failure = !radio_ccm_mic_is_valid();

				if (mic_failure &&
				    lll->ccm_rx.counter == 0 &&
				    (pdu_data_rx->ll_id ==
				     PDU_DATA_LLID_CTRL)) {
					/* Received an LL control packet in the
					 * middle of the LL encryption procedure
					 * with MIC failure.
					 * This could be an unencrypted packet
					 */
					struct pdu_data *scratch_pkt =
						radio_pkt_scratch_get();

					if (ctrl_pdu_len_check(
						scratch_pkt->len)) {
						memcpy(pdu_data_rx,
						       scratch_pkt,
						       scratch_pkt->len +
						       offsetof(struct pdu_data,
							llctrl));
						mic_failure = false;
						lll->ccm_rx.counter--;
					}
				}

				if (mic_failure) {
					/* Record MIC invalid */
					mic_state = LLL_CONN_MIC_FAIL;

					return -EINVAL;
				}

				/* Increment counter */
				lll->ccm_rx.counter++;

				/* Record MIC valid */
				mic_state = LLL_CONN_MIC_PASS;
			}
#endif /* CONFIG_BT_CTLR_LE_ENC */

			/* Enqueue non-empty PDU */
			*is_rx_enqueue = 1U;
		}
	}

	return 0;
}

static void empty_tx_init(void)
{
	struct pdu_data *p;

	p = (void *)radio_pkt_empty_get();
	p->ll_id = PDU_DATA_LLID_DATA_CONTINUE;
}
