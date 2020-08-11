/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdint.h>

#include <toolchain.h>
#include <sys/util.h>

#include "hal/ccm.h"
#include "hal/radio.h"
#include "hal/ticker.h"

#include "util/util.h"
#include "util/memq.h"

#include "pdu.h"

#include "lll.h"
#include "lll_vendor.h"
#include "lll_clock.h"
#include "lll_chan.h"
#include "lll_sync.h"

#include "lll_internal.h"
#include "lll_tim_internal.h"
#include "lll_prof_internal.h"

#define BT_DBG_ENABLED IS_ENABLED(CONFIG_BT_DEBUG_HCI_DRIVER)
#define LOG_MODULE_NAME bt_ctlr_lll_sync
#include "common/log.h"
#include <soc.h>
#include "hal/debug.h"

static int init_reset(void);
static int prepare_cb(struct lll_prepare_param *p);
static void isr_rx(void *param);

int lll_sync_init(void)
{
	int err;

	err = init_reset();
	if (err) {
		return err;
	}

	return 0;
}

int lll_sync_reset(void)
{
	int err;

	err = init_reset();
	if (err) {
		return err;
	}

	return 0;
}

void lll_sync_prepare(void *param)
{
	struct lll_prepare_param *p;
	struct lll_sync *lll;
	uint16_t elapsed;
	int err;

	p = param;
	lll = p->param;

	/* Request to start HF Clock */
	err = lll_hfclock_on();
	LL_ASSERT(err >= 0);

	/* Instants elapsed */
	elapsed = p->lazy + 1;

	/* Save the (latency + 1) for use in event */
	lll->latency_prepare += elapsed;

	/* Accumulate window widening */
	lll->window_widening_prepare_us += lll->window_widening_periodic_us *
					   elapsed;
	if (lll->window_widening_prepare_us > lll->window_widening_max_us) {
		lll->window_widening_prepare_us = lll->window_widening_max_us;
	}

	/* Invoke common pipeline handling of prepare */
	err = lll_prepare(lll_is_abort_cb, lll_abort_cb, prepare_cb, 0, p);
	LL_ASSERT(!err || err == -EINPROGRESS);
}

static int init_reset(void)
{
	return 0;
}

static int prepare_cb(struct lll_prepare_param *p)
{
	struct node_rx_pdu *node_rx;
	uint32_t ticks_at_event;
	uint32_t ticks_at_start;
	uint16_t event_counter;
	uint32_t remainder_us;
	uint8_t data_chan_use;
	struct lll_sync *lll;
	struct evt_hdr *evt;
	uint32_t remainder;
	uint32_t hcto;

	DEBUG_RADIO_START_O(1);

	lll = p->param;

	/* Deduce the latency */
	lll->latency_event = lll->latency_prepare - 1;

	/* Calculate the current event counter value */
	event_counter = lll->event_counter + lll->latency_event;

	/* Update event counter to next value */
	lll->event_counter = lll->event_counter + lll->latency_prepare;

	/* Reset accumulated latencies */
	lll->latency_prepare = 0;

	/* Current window widening */
	lll->window_widening_event_us += lll->window_widening_prepare_us;
	lll->window_widening_prepare_us = 0;
	if (lll->window_widening_event_us > lll->window_widening_max_us) {
		lll->window_widening_event_us =	lll->window_widening_max_us;
	}

	/* Current window size */
	lll->window_size_event_us += lll->window_size_prepare_us;
	lll->window_size_prepare_us = 0;

	/* Calculate the radio channel to use */
	data_chan_use = lll_chan_sel_2(event_counter, lll->data_chan_id,
				       &lll->data_chan_map[0],
				       lll->data_chan_count);

	/* Start setting up Radio h/w */
	radio_reset();

#if defined(CONFIG_BT_CTLR_TX_PWR_DYNAMIC_CONTROL)
	radio_tx_power_set(lll->tx_pwr_lvl);
#else
	radio_tx_power_set(RADIO_TXP_DEFAULT);
#endif /* CONFIG_BT_CTLR_TX_PWR_DYNAMIC_CONTROL */

	radio_phy_set(lll->phy, 1);
	radio_pkt_configure(8, PDU_AC_PAYLOAD_SIZE_MAX, (lll->phy << 1));

	node_rx = ull_pdu_rx_alloc_peek(1);
	LL_ASSERT(node_rx);

	radio_pkt_rx_set(node_rx->pdu);

	radio_aa_set(lll->access_addr);
	radio_crc_configure(((0x5bUL) | ((0x06UL) << 8) | ((0x00UL) << 16)),
			    (((uint32_t)lll->crc_init[2] << 16) |
			     ((uint32_t)lll->crc_init[1] << 8) |
			     ((uint32_t)lll->crc_init[0])));

	lll_chan_set(data_chan_use);

	radio_isr_set(isr_rx, lll);

	radio_tmr_tifs_set(EVENT_IFS_US);

	radio_switch_complete_and_disable();

	ticks_at_event = p->ticks_at_expire;
	evt = HDR_LLL2EVT(lll);
	ticks_at_event += lll_evt_offset_get(evt);

	ticks_at_start = ticks_at_event;
	ticks_at_start += HAL_TICKER_US_TO_TICKS(EVENT_OVERHEAD_START_US);

	remainder = p->remainder;
	remainder_us = radio_tmr_start(0, ticks_at_start, remainder);

	radio_tmr_aa_capture();
	radio_tmr_aa_save(0);

	hcto = remainder_us +
	       ((EVENT_JITTER_US + EVENT_TICKER_RES_MARGIN_US +
		 lll->window_widening_event_us) << 1) +
	       lll->window_size_event_us;

#if defined(CONFIG_BT_CTLR_PHY)
	hcto += radio_rx_ready_delay_get(lll->phy, 1);
	hcto += addr_us_get(lll->phy);
	hcto += radio_rx_chain_delay_get(lll->phy, 1);
#else /* !CONFIG_BT_CTLR_PHY */
	hcto += radio_rx_ready_delay_get(0, 0);
	hcto += addr_us_get(0);
	hcto += radio_rx_chain_delay_get(0, 0);
#endif /* !CONFIG_BT_CTLR_PHY */

	radio_tmr_hcto_configure(hcto);
	radio_tmr_end_capture();
	radio_rssi_measure();

#if defined(CONFIG_BT_CTLR_GPIO_LNA_PIN)
	radio_gpio_lna_setup();

#if defined(CONFIG_BT_CTLR_PHY)
	radio_gpio_pa_lna_enable(remainder_us +
				 radio_rx_ready_delay_get(lll->phy_rx, 1) -
				 CONFIG_BT_CTLR_GPIO_LNA_OFFSET);
#else /* !CONFIG_BT_CTLR_PHY */
	radio_gpio_pa_lna_enable(remainder_us +
				 radio_rx_ready_delay_get(0, 0) -
				 CONFIG_BT_CTLR_GPIO_LNA_OFFSET);
#endif /* !CONFIG_BT_CTLR_PHY */
#endif /* CONFIG_BT_CTLR_GPIO_LNA_PIN */

#if defined(CONFIG_BT_CTLR_XTAL_ADVANCED) && \
	(EVENT_OVERHEAD_PREEMPT_US <= EVENT_OVERHEAD_PREEMPT_MIN_US)
	/* check if preempt to start has changed */
	if (lll_preempt_calc(evt, (TICKER_ID_SCAN_SYNC_BASE +
				   ull_sync_lll_handle_get(lll)),
			     ticks_at_event)) {
		radio_isr_set(lll_isr_abort, lll);
		radio_disable();
	} else
#endif /* CONFIG_BT_CTLR_XTAL_ADVANCED */
	{
		uint32_t ret;

		ret = lll_prepare_done(lll);
		LL_ASSERT(!ret);
	}

	DEBUG_RADIO_START_O(1);

	printk("SYNC PREPARE\n");
	return 0;
}

static void isr_rx(void *param)
{
	uint8_t rssi_ready;
	uint8_t trx_done;
	uint8_t crc_ok;

	/* TODO: may be we dont need to profile, as there is no use of tIFS */
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
		/* TODO: Combine the early exit with above if-then-else block
		 */
		printk("RX FAILED\n");

		return;
	}

	if (crc_ok) {
		/* TODO: */
		printk("CRC OK\n");
	} else {
		printk("CRC BAD\n");
	}

	if (IS_ENABLED(CONFIG_BT_CTLR_PROFILE_ISR)) {
		lll_prof_cputime_capture();
	}

	/* TODO: drift compensation */

	lll_isr_cleanup(param);

	if (IS_ENABLED(CONFIG_BT_CTLR_PROFILE_ISR)) {
		lll_prof_send();
	}
}
