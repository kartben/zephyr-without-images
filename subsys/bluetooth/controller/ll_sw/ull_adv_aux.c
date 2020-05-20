/*
 * Copyright (c) 2017-2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/types.h>
#include <sys/byteorder.h>
#include <bluetooth/hci.h>

#include "hal/ticker.h"

#include "util/util.h"
#include "util/mem.h"
#include "util/memq.h"
#include "util/mayfly.h"

#include "ticker/ticker.h"

#include "pdu.h"
#include "ll.h"
#include "lll.h"
#include "lll_vendor.h"
#include "lll_adv.h"
#include "lll_adv_aux.h"
#include "lll_adv_internal.h"

#include "ull_adv_types.h"

#include "ull_internal.h"
#include "ull_adv_internal.h"

#define BT_DBG_ENABLED IS_ENABLED(CONFIG_BT_DEBUG_HCI_DRIVER)
#define LOG_MODULE_NAME bt_ctlr_ull_adv_aux
#include "common/log.h"
#include <soc.h>
#include "hal/debug.h"

static int init_reset(void);

#if (CONFIG_BT_CTLR_ADV_AUX_SET > 0)
static inline struct ll_adv_aux_set *aux_acquire(void);
static inline void aux_release(struct ll_adv_aux_set *aux);
static inline uint8_t aux_handle_get(struct ll_adv_aux_set *aux);
static void mfy_aux_offset_get(void *param);
static void ticker_cb(uint32_t ticks_at_expire, uint32_t remainder,
		      uint16_t lazy, void *param);
static void ticker_op_cb(uint32_t status, void *param);

static struct ll_adv_aux_set ll_adv_aux_pool[CONFIG_BT_CTLR_ADV_AUX_SET];
static void *adv_aux_free;
#endif /* (CONFIG_BT_CTLR_ADV_AUX_SET > 0) */

uint8_t ll_adv_aux_random_addr_set(uint8_t handle, uint8_t const *const addr)
{
	struct ll_adv_set *adv;

	adv = ull_adv_is_created_get(handle);
	if (!adv) {
		return BT_HCI_ERR_CMD_DISALLOWED;
	}

	/* TODO: Fail if connectable advertising is enabled */
	if (0) {
		return BT_HCI_ERR_CMD_DISALLOWED;
	}

	memcpy(adv->rnd_addr, addr, BDADDR_SIZE);

	return 0;
}

uint8_t const *ll_adv_aux_random_addr_get(struct ll_adv_set const *const adv,
				       uint8_t *const addr)
{
	if (addr) {
		memcpy(addr, adv->rnd_addr, BDADDR_SIZE);
	}

	return adv->rnd_addr;
}

uint8_t ll_adv_aux_ad_data_set(uint8_t handle, uint8_t op, uint8_t frag_pref, uint8_t len,
			    uint8_t const *const data)
{
	struct pdu_adv *pri_pdu, *pri_pdu_prev, *sec_pdu, *sec_pdu_prev;
	struct pdu_adv_com_ext_adv *pri_com_hdr, *pri_com_hdr_prev;
	struct pdu_adv_com_ext_adv *sec_com_hdr, *sec_com_hdr_prev;
	uint8_t pri_len, pri_len_prev, sec_len, sec_len_prev;
	struct pdu_adv_hdr *pri_hdr, pri_hdr_prev;
	struct pdu_adv_hdr *sec_hdr, sec_hdr_prev;
	uint8_t *pri_dptr, *pri_dptr_prev;
	uint8_t *sec_dptr, *sec_dptr_prev;
	struct lll_adv_aux *lll_aux;
	struct ll_adv_aux_set *aux;
	struct ll_adv_set *adv;
	uint8_t pri_idx, sec_idx;
	struct lll_adv *lll;
	uint8_t is_aux_new;

	/* op param definitions:
	 * 0x00 - Intermediate fragment of fragmented extended advertising data
	 * 0x01 - First fragment of fragmented extended advertising data
	 * 0x02 - Last fragemnt of fragemented extended advertising data
	 * 0x03 - Complete extended advertising data
	 * 0x04 - Unchanged data (just update the advertising data)
	 * All other values, Reserved for future use
	 */

	/* TODO: handle other op values */
	if ((op != BT_HCI_LE_EXT_ADV_OP_COMPLETE_DATA) &&
	    (op != BT_HCI_LE_EXT_ADV_OP_UNCHANGED_DATA)) {
		/* FIXME: error code */
		return BT_HCI_ERR_CMD_DISALLOWED;
	}

	/* Get the advertising set instance */
	adv = ull_adv_is_created_get(handle);
	if (!adv) {
		return BT_HCI_ERR_CMD_DISALLOWED;
	}

	lll = &adv->lll;

	/* Do not use Common Extended Advertising Header Format if not extended
	 * advertising.
	 */
	pri_pdu_prev = lll_adv_data_peek(lll);
	if (pri_pdu_prev->type != PDU_ADV_TYPE_EXT_IND) {
		return ull_adv_data_set(adv, len, data);
	}

	/* Allocate or existing Auxiliary channel instance */
	lll_aux = lll->aux;
	if (!lll_aux) {
		aux = ull_adv_aux_acquire(lll);
		if (!aux) {
			return BT_HCI_ERR_MEM_CAPACITY_EXCEEDED;
		}

		lll_aux = &aux->lll;

		is_aux_new = 1U;
	} else {
		aux = (void *)HDR_LLL2EVT(lll_aux);

		is_aux_new = 0U;
	}

	/* Get reference to previous primary PDU data */
	pri_com_hdr_prev = (void *)&pri_pdu_prev->adv_ext_ind;
	pri_hdr = (void *)pri_com_hdr_prev->ext_hdr_adi_adv_data;
	pri_hdr_prev = *pri_hdr;
	pri_dptr_prev = (uint8_t *)pri_hdr + sizeof(*pri_hdr);

	/* Get reference to new primary PDU data buffer */
	pri_pdu = lll_adv_data_alloc(lll, &pri_idx);
	pri_pdu->type = pri_pdu_prev->type;
	pri_pdu->rfu = 0U;
	pri_pdu->chan_sel = 0U;
	pri_com_hdr = (void *)&pri_pdu->adv_ext_ind;
	pri_com_hdr->adv_mode = pri_com_hdr_prev->adv_mode;
	pri_hdr = (void *)pri_com_hdr->ext_hdr_adi_adv_data;
	pri_dptr = (uint8_t *)pri_hdr + sizeof(*pri_hdr);
	*(uint8_t *)pri_hdr = 0U;

	/* Get reference to previous secondary PDU data */
	sec_pdu_prev = lll_adv_aux_data_peek(lll_aux);
	sec_com_hdr_prev = (void *)&sec_pdu_prev->adv_ext_ind;
	sec_hdr = (void *)sec_com_hdr_prev->ext_hdr_adi_adv_data;
	if (!is_aux_new) {
		sec_hdr_prev = *sec_hdr;
	} else {
		*(uint8_t *)&sec_hdr_prev = 0U;
	}
	sec_dptr_prev = (uint8_t *)sec_hdr + sizeof(*sec_hdr);

	/* Get reference to new secondary PDU data buffer */
	sec_pdu = lll_adv_aux_data_alloc(lll_aux, &sec_idx);
	sec_pdu->type = pri_pdu->type;
	sec_pdu->rfu = 0U;

	if (IS_ENABLED(CONFIG_BT_CTLR_CHAN_SEL_2)) {
		sec_pdu->chan_sel = sec_pdu_prev->chan_sel;
	} else {
		sec_pdu->chan_sel = 0U;
	}

	sec_pdu->tx_addr = sec_pdu_prev->tx_addr;
	sec_pdu->rx_addr = sec_pdu_prev->rx_addr;

	sec_com_hdr = (void *)&sec_pdu->adv_ext_ind;
	sec_com_hdr->adv_mode = pri_com_hdr->adv_mode;
	sec_hdr = (void *)sec_com_hdr->ext_hdr_adi_adv_data;
	sec_dptr = (uint8_t *)sec_hdr + sizeof(*sec_hdr);
	*(uint8_t *)sec_hdr = 0U;

	/* AdvA flag */
	/* NOTE: as we will use auxiliary packet, we remove AdvA in primary
	 * channel. i.e. Do nothing to add AdvA in the primary PDU.
	 */
	if (pri_hdr_prev.adv_addr) {
		pri_dptr_prev += BDADDR_SIZE;

		/* Prepare to add AdvA in secondary PDU */
		sec_hdr->adv_addr = 1;

		/* NOTE: AdvA is filled at enable */
		sec_pdu->tx_addr = pri_pdu_prev->tx_addr;
	}
	pri_pdu->tx_addr = 0U;
	pri_pdu->rx_addr = 0U;

	if (sec_hdr_prev.adv_addr) {
		sec_dptr_prev += BDADDR_SIZE;

		/* Prepare to copy AdvA from previous double buffered PDU */
		sec_hdr->adv_addr = 1;
	}
	if (sec_hdr->adv_addr) {
		sec_dptr += BDADDR_SIZE;
	}

	/* No TargetA in primary and secondary channel for undirected */
	/* No CTEInfo flag in primary and secondary channel PDU */

	/* ADI flag */
	if (pri_hdr_prev.adi) {
		pri_dptr_prev += sizeof(struct pdu_adv_adi);
	}
	pri_hdr->adi = 1;
	pri_dptr += sizeof(struct pdu_adv_adi);
	if (sec_hdr_prev.adi) {
		sec_dptr_prev += sizeof(struct pdu_adv_adi);
	}
	sec_hdr->adi = 1;
	sec_dptr += sizeof(struct pdu_adv_adi);

	/* AuxPtr flag */
	if (pri_hdr_prev.aux_ptr) {
		pri_dptr_prev += sizeof(struct pdu_adv_aux_ptr);
	}
	pri_hdr->aux_ptr = 1;
	pri_dptr += sizeof(struct pdu_adv_aux_ptr);
	if (sec_hdr_prev.aux_ptr) {
		sec_dptr_prev += sizeof(struct pdu_adv_aux_ptr);

		sec_hdr->aux_ptr = 1;
		sec_dptr += sizeof(struct pdu_adv_aux_ptr);
	}

	/* No SyncInfo flag in primary channel PDU */
	/* SyncInfo flag in secondary channel PDU */
	if (sec_hdr_prev.sync_info) {
		sec_dptr_prev += sizeof(struct pdu_adv_sync_info);

		sec_hdr->sync_info = 1;
		sec_dptr += sizeof(struct pdu_adv_sync_info);
	}

	/* Tx Power flag */
	if (pri_hdr_prev.tx_pwr) {
		pri_dptr_prev++;

		/* C1, Tx Power is optional on the LE 1M PHY, and reserved for
		 * for future use on the LE Coded PHY.
		 */
		if (lll->phy_p != PHY_CODED) {
			pri_hdr->tx_pwr = 1;
			pri_dptr++;
		} else {
			sec_hdr->tx_pwr = 1;
		}
	}
	if (sec_hdr_prev.tx_pwr) {
		sec_dptr_prev++;

		sec_hdr->tx_pwr = 1;
	}
	if (sec_hdr->tx_pwr) {
		sec_dptr++;
	}

	/* No ACAD in Primary channel PDU */
	/* TODO: ACAD in Secondary channel PDU */

	/* Calc primary PDU len */
	pri_len_prev = pri_dptr_prev - (uint8_t *)pri_com_hdr_prev;
	pri_len = pri_dptr - (uint8_t *)pri_com_hdr;
	pri_com_hdr->ext_hdr_len = pri_len -
				   offsetof(struct pdu_adv_com_ext_adv,
					    ext_hdr_adi_adv_data);

	/* set the primary PDU len */
	pri_pdu->len = pri_len;

	/* Calc secondary PDU len */
	sec_len_prev = sec_dptr_prev - (uint8_t *)sec_com_hdr_prev;
	sec_len = sec_dptr - (uint8_t *)sec_com_hdr;
	sec_com_hdr->ext_hdr_len = sec_len -
				   offsetof(struct pdu_adv_com_ext_adv,
					    ext_hdr_adi_adv_data);

	/* TODO: Check AdvData overflow */

	/* Fill AdvData in secondary PDU */
	memcpy(sec_dptr, data, len);

	/* set the secondary PDU len */
	sec_pdu->len = sec_len + len;

	/* Start filling primary PDU extended header  based on flags */

	/* No AdvData in primary channel PDU */

	/* No ACAD in primary channel PDU */

	/* Tx Power */
	if (pri_hdr->tx_pwr) {
		*--pri_dptr = *--pri_dptr_prev;
	} else if (sec_hdr->tx_pwr) {
		*--sec_dptr = *--sec_dptr_prev;
	}

	/* No SyncInfo in primary channel PDU */
	/* SyncInfo in secondary channel PDU */
	if (sec_hdr->sync_info) {
		sec_dptr_prev -= sizeof(struct pdu_adv_sync_info);
		sec_dptr -= sizeof(struct pdu_adv_sync_info);

		memcpy(sec_dptr, sec_dptr_prev,
		       sizeof(struct pdu_adv_sync_info));
	}

	/* AuxPtr */
	if (pri_hdr_prev.aux_ptr) {
		pri_dptr_prev -= sizeof(struct pdu_adv_aux_ptr);
	}
	{
		struct pdu_adv_aux_ptr *aux_ptr;

		pri_dptr -= sizeof(struct pdu_adv_aux_ptr);

		/* NOTE: Aux Offset will be set in advertiser LLL event */
		aux_ptr = (void *)pri_dptr;

		/* FIXME: implementation defined */
		aux_ptr->chan_idx = 0;
		aux_ptr->ca = 0;
		aux_ptr->offs_units = 0;

		aux_ptr->phy = find_lsb_set(lll->phy_s) - 1;
	}
	if (sec_hdr_prev.aux_ptr) {
		struct pdu_adv_aux_ptr *aux_ptr;

		sec_dptr_prev -= sizeof(struct pdu_adv_aux_ptr);
		sec_dptr -= sizeof(struct pdu_adv_aux_ptr);

		/* NOTE: Aux Offset will be set in advertiser LLL event */
		aux_ptr = (void *)sec_dptr;

		/* FIXME: implementation defined */
		aux_ptr->chan_idx = 0;
		aux_ptr->ca = 0;
		aux_ptr->offs_units = 0;

		aux_ptr->phy = find_lsb_set(lll->phy_s) - 1;
	}

	/* ADI */
	{
		struct pdu_adv_adi *pri_adi, *sec_adi;
		uint16_t did = UINT16_MAX;

		pri_dptr -= sizeof(struct pdu_adv_adi);
		sec_dptr -= sizeof(struct pdu_adv_adi);

		pri_adi = (void *)pri_dptr;
		sec_adi = (void *)sec_dptr;

		if (pri_hdr_prev.adi) {
			struct pdu_adv_adi *pri_adi_prev;

			pri_dptr_prev -= sizeof(struct pdu_adv_adi);
			sec_dptr_prev -= sizeof(struct pdu_adv_adi);

			/* NOTE: memcpy shall handle overlapping buffers */
			memcpy(pri_dptr, pri_dptr_prev,
			       sizeof(struct pdu_adv_adi));
			memcpy(sec_dptr, sec_dptr_prev,
			       sizeof(struct pdu_adv_adi));

			pri_adi_prev = (void *)pri_dptr_prev;
			did = sys_le16_to_cpu(pri_adi_prev->did);
		} else {
			pri_adi->sid = adv->sid;
			sec_adi->sid = adv->sid;
		}

		if ((op == 0x04) || len || (pri_len_prev != pri_len) ||
		    (sec_pdu_prev->len != sec_pdu->len)) {
			did++;
		}

		pri_adi->did = sys_cpu_to_le16(did);
		sec_adi->did = sys_cpu_to_le16(did);
	}

	/* No CTEInfo field in primary channel PDU */

	/* NOTE: TargetA, filled at enable and RPA timeout */

	/* No AdvA in primary channel due to AuxPtr being added */

	/* NOTE: AdvA in aux channel is also filled at enable and RPA timeout */
	if (sec_hdr->adv_addr) {
		void *bdaddr;

		if (sec_hdr_prev.adv_addr) {
			sec_dptr_prev -= BDADDR_SIZE;
			bdaddr = sec_dptr_prev;
		} else {
			pri_dptr_prev -= BDADDR_SIZE;
			bdaddr = pri_dptr_prev;
		}

		sec_dptr -= BDADDR_SIZE;

		memcpy(sec_dptr, bdaddr, BDADDR_SIZE);
	}

	lll_adv_aux_data_enqueue(lll_aux, sec_idx);
	lll_adv_data_enqueue(lll, pri_idx);

	if (adv->is_enabled && !aux->is_started) {
		volatile uint32_t ret_cb;
		uint32_t ticks_anchor;
		uint32_t ret;

		ull_hdr_init(&aux->ull);

		aux->interval =	adv->interval +
				(HAL_TICKER_TICKS_TO_US(ULL_ADV_RANDOM_DELAY) /
				 625U);

		ticks_anchor = ticker_ticks_now_get();

		ret = ull_adv_aux_start(aux, ticks_anchor, &ret_cb);

		ret = ull_ticker_status_take(ret, &ret_cb);
		if (ret != TICKER_STATUS_SUCCESS) {
			/* FIXME: Use a better error code */
			return BT_HCI_ERR_CMD_DISALLOWED;
		}

		aux->is_started = 1;
	}

	return 0;
}

uint8_t ll_adv_aux_sr_data_set(uint8_t handle, uint8_t op, uint8_t frag_pref, uint8_t len,
			    uint8_t const *const data)
{
	struct ll_adv_set *adv;
	struct pdu_adv *pri_pdu_prev;
	struct lll_adv *lll;

	/* op param definitions:
	 * 0x00 - Intermediate fragment of fragmented extended advertising data
	 * 0x01 - First fragment of fragmented extended advertising data
	 * 0x02 - Last fragemnt of fragemented extended advertising data
	 * 0x03 - Complete extended advertising data
	 * 0x04 - Unchanged data (just update the advertising data)
	 * All other values, Reserved for future use
	 */

	/* TODO: handle other op values */
	if ((op != 0x03) && (op != 0x04)) {
		/* FIXME: error code */
		return BT_HCI_ERR_CMD_DISALLOWED;
	}

	/* Get the advertising set instance */
	adv = ull_adv_is_created_get(handle);
	if (!adv) {
		return BT_HCI_ERR_CMD_DISALLOWED;
	}

	lll = &adv->lll;

	/* Do not use Common Extended Advertising Header Format if not extended
	 * advertising.
	 */
	pri_pdu_prev = lll_adv_data_peek(lll);
	if (pri_pdu_prev->type != PDU_ADV_TYPE_EXT_IND) {
		return ull_scan_rsp_set(adv, len, data);
	}

	/* FIXME: Workaround to not fail when no data is supplied */
	if (!len) {
		return 0;
	}

	/* TODO: Populate extended scan response data */

	return BT_HCI_ERR_CMD_DISALLOWED;
}

uint16_t ll_adv_aux_max_data_length_get(void)
{
	return CONFIG_BT_CTLR_ADV_DATA_LEN_MAX;
}

uint8_t ll_adv_aux_set_count_get(void)
{
	return CONFIG_BT_CTLR_ADV_SET;
}

uint8_t ll_adv_aux_set_remove(uint8_t handle)
{
	/* TODO: reset/release primary channel and Aux channel PDUs */
	return 0;
}

uint8_t ll_adv_aux_set_clear(void)
{
	/* TODO: reset/release all adv set primary channel and  Aux channel
	 * PDUs
	 */
	return 0;
}

int ull_adv_aux_init(void)
{
	int err;

	err = init_reset();
	if (err) {
		return err;
	}

	return 0;
}

int ull_adv_aux_reset(void)
{
	int err;

	err = init_reset();
	if (err) {
		return err;
	}

	return 0;
}

#if (CONFIG_BT_CTLR_ADV_AUX_SET > 0)
uint8_t ull_adv_aux_lll_handle_get(struct lll_adv_aux *lll)
{
	return aux_handle_get((void *)lll->hdr.parent);
}

uint32_t ull_adv_aux_start(struct ll_adv_aux_set *aux, uint32_t ticks_anchor,
			uint32_t volatile *ret_cb)
{
	uint32_t slot_us = EVENT_OVERHEAD_START_US + EVENT_OVERHEAD_END_US;
	uint32_t ticks_slot_overhead;
	uint8_t aux_handle;
	uint32_t ret;

	/* TODO: Calc AUX_ADV_IND slot_us */
	slot_us += 1000;

	/* TODO: active_to_start feature port */
	aux->evt.ticks_active_to_start = 0;
	aux->evt.ticks_xtal_to_start =
		HAL_TICKER_US_TO_TICKS(EVENT_OVERHEAD_XTAL_US);
	aux->evt.ticks_preempt_to_start =
		HAL_TICKER_US_TO_TICKS(EVENT_OVERHEAD_PREEMPT_MIN_US);
	aux->evt.ticks_slot = HAL_TICKER_US_TO_TICKS(slot_us);

	if (IS_ENABLED(CONFIG_BT_CTLR_LOW_LAT)) {
		ticks_slot_overhead = MAX(aux->evt.ticks_active_to_start,
					  aux->evt.ticks_xtal_to_start);
	} else {
		ticks_slot_overhead = 0;
	}

	aux_handle = aux_handle_get(aux);

	*ret_cb = TICKER_STATUS_BUSY;
	ret = ticker_start(TICKER_INSTANCE_ID_CTLR, TICKER_USER_ID_THREAD,
			   (TICKER_ID_ADV_AUX_BASE + aux_handle),
			   ticks_anchor, 0,
			   HAL_TICKER_US_TO_TICKS((uint64_t)aux->interval *
						  625),
			   TICKER_NULL_REMAINDER, TICKER_NULL_LAZY,
			   (aux->evt.ticks_slot + ticks_slot_overhead),
			   ticker_cb, aux,
			   ull_ticker_status_give, (void *)ret_cb);

	return ret;
}

uint8_t ull_adv_aux_stop(struct ll_adv_aux_set *aux)
{
	volatile uint32_t ret_cb = TICKER_STATUS_BUSY;
	uint8_t aux_handle;
	void *mark;
	uint32_t ret;

	mark = ull_disable_mark(aux);
	LL_ASSERT(mark == aux);

	aux_handle = aux_handle_get(aux);

	ret = ticker_stop(TICKER_INSTANCE_ID_CTLR, TICKER_USER_ID_THREAD,
			  TICKER_ID_ADV_AUX_BASE + aux_handle,
			  ull_ticker_status_give, (void *)&ret_cb);

	ret = ull_ticker_status_take(ret, &ret_cb);
	if (ret) {
		mark = ull_disable_mark(aux);
		LL_ASSERT(mark == aux);

		return BT_HCI_ERR_CMD_DISALLOWED;
	}

	ret = ull_disable(&aux->lll);
	LL_ASSERT(!ret);

	mark = ull_disable_unmark(aux);
	LL_ASSERT(mark == aux);

	aux->is_started = 0U;

	return 0;
}

struct ll_adv_aux_set *ull_adv_aux_acquire(struct lll_adv *lll)
{
	struct lll_adv_aux *lll_aux;
	struct ll_adv_aux_set *aux;

	aux = aux_acquire();
	if (!aux) {
		return aux;
	}

	lll_aux = &aux->lll;
	lll->aux = lll_aux;
	lll_aux->adv = lll;

	/* NOTE: ull_hdr_init(&aux->ull); is done on start */
	lll_hdr_init(lll_aux, aux);

	aux->is_started = 0U;

	return aux;
}

void ull_adv_aux_release(struct ll_adv_aux_set *aux)
{
	aux_release(aux);
}

void ull_adv_aux_offset_get(struct ll_adv_set *adv)
{
	static memq_link_t link;
	static struct mayfly mfy = {0, 0, &link, NULL, mfy_aux_offset_get};
	uint32_t ret;

	mfy.param = adv;
	ret = mayfly_enqueue(TICKER_USER_ID_ULL_HIGH, TICKER_USER_ID_ULL_LOW, 1,
			     &mfy);
	LL_ASSERT(!ret);
}

struct pdu_adv_aux_ptr *ull_adv_aux_lll_offset_fill(uint32_t ticks_offset,
						    uint32_t start_us,
						    struct pdu_adv *pdu)
{
	struct pdu_adv_com_ext_adv *pri_com_hdr;
	struct pdu_adv_aux_ptr *aux;
	struct pdu_adv_hdr *h;
	uint8_t *ptr;

	pri_com_hdr = (void *)&pdu->adv_ext_ind;
	h = (void *)pri_com_hdr->ext_hdr_adi_adv_data;
	ptr = (uint8_t *)h + sizeof(*h);

	if (h->adv_addr) {
		ptr += BDADDR_SIZE;
	}

	if (h->adi) {
		ptr += sizeof(struct pdu_adv_adi);
	}

	aux = (void *)ptr;
	aux->offs = (HAL_TICKER_TICKS_TO_US(ticks_offset) - start_us) / 30;
	if (aux->offs_units) {
		aux->offs /= 10;
	}

	return aux;
}

static int init_reset(void)
{
	/* Initialize adv aux pool. */
	mem_init(ll_adv_aux_pool, sizeof(struct ll_adv_aux_set),
		 sizeof(ll_adv_aux_pool) / sizeof(struct ll_adv_aux_set),
		 &adv_aux_free);

	return 0;
}

static inline struct ll_adv_aux_set *aux_acquire(void)
{
	return mem_acquire(&adv_aux_free);
}

static inline void aux_release(struct ll_adv_aux_set *aux)
{
	mem_release(aux, &adv_aux_free);
}

static inline uint8_t aux_handle_get(struct ll_adv_aux_set *aux)
{
	return mem_index_get(aux, ll_adv_aux_pool,
			     sizeof(struct ll_adv_aux_set));
}

static void mfy_aux_offset_get(void *param)
{
	struct ll_adv_set *adv = param;
	struct ll_adv_aux_set *aux;
	uint32_t ticks_to_expire;
	uint32_t ticks_current;
	struct pdu_adv *pdu;
	uint8_t ticker_id;
	uint8_t retry;
	uint8_t id;

	aux = (void *)HDR_LLL2EVT(adv->lll.aux);
	ticker_id = TICKER_ID_ADV_AUX_BASE + aux_handle_get(aux);

	id = TICKER_NULL;
	ticks_to_expire = 0U;
	ticks_current = 0U;
	retry = 4U;
	do {
		uint32_t volatile ret_cb = TICKER_STATUS_BUSY;
		uint32_t ticks_previous;
		uint32_t ret;

		ticks_previous = ticks_current;

		ret = ticker_next_slot_get(TICKER_INSTANCE_ID_CTLR,
					   TICKER_USER_ID_ULL_LOW,
					   &id,
					   &ticks_current, &ticks_to_expire,
					   ticker_op_cb, (void *)&ret_cb);
		if (ret == TICKER_STATUS_BUSY) {
			while (ret_cb == TICKER_STATUS_BUSY) {
				ticker_job_sched(TICKER_INSTANCE_ID_CTLR,
						 TICKER_USER_ID_ULL_LOW);
			}
		}

		LL_ASSERT(ret_cb == TICKER_STATUS_SUCCESS);

		LL_ASSERT((ticks_current == ticks_previous) || retry--);

		LL_ASSERT(id != TICKER_NULL);
	} while (id != ticker_id);

	/* Store the ticks offset for population in other advertising primary
	 * channel PDUs.
	 */
	aux->lll.ticks_offset = ticks_to_expire;

	/* NOTE: as remainder used in scheduling primary PDU not available,
	 * compensate with a probable jitter of one ticker resolution unit that
	 * would be included in the packet timer capture when scheduling next
	 * advertising primary channel PDU.
	 */
	aux->lll.ticks_offset +=
		HAL_TICKER_US_TO_TICKS(EVENT_TICKER_RES_MARGIN_US);

	/* FIXME: we are in ULL_LOW context, fill offset in LLL context */
	pdu = lll_adv_data_curr_get(&adv->lll);
	ull_adv_aux_lll_offset_fill(ticks_to_expire, 0, pdu);
}

static void ticker_cb(uint32_t ticks_at_expire, uint32_t remainder,
		      uint16_t lazy, void *param)
{
	static memq_link_t link;
	static struct mayfly mfy = {0, 0, &link, NULL, lll_adv_aux_prepare};
	static struct lll_prepare_param p;
	struct ll_adv_aux_set *aux = param;
	struct lll_adv_aux *lll;
	uint32_t ret;
	uint8_t ref;

	DEBUG_RADIO_PREPARE_A(1);

	lll = &aux->lll;

	/* Increment prepare reference count */
	ref = ull_ref_inc(&aux->ull);
	LL_ASSERT(ref);

	/* Append timing parameters */
	p.ticks_at_expire = ticks_at_expire;
	p.remainder = remainder;
	p.lazy = lazy;
	p.param = lll;
	mfy.param = &p;

	/* Kick LLL prepare */
	ret = mayfly_enqueue(TICKER_USER_ID_ULL_HIGH,
			     TICKER_USER_ID_LLL, 0, &mfy);
	LL_ASSERT(!ret);

#if defined(CONFIG_BT_CTLR_ADV_PERIODIC)
	struct ll_adv_set *adv;

	adv = (void *)HDR_LLL2EVT(lll->adv);
	if (adv->lll.sync) {
		struct ll_adv_sync_set *sync;

		sync  = (void *)HDR_LLL2EVT(adv->lll.sync);
		if (sync->is_started) {
			ull_adv_sync_offset_get(adv);
		}
	}
#endif /* CONFIG_BT_CTLR_ADV_PERIODIC */

	DEBUG_RADIO_PREPARE_A(1);
}

static void ticker_op_cb(uint32_t status, void *param)
{
	*((uint32_t volatile *)param) = status;
}
#else /* !(CONFIG_BT_CTLR_ADV_AUX_SET > 0) */

static int init_reset(void)
{
	return 0;
}
#endif /* !(CONFIG_BT_CTLR_ADV_AUX_SET > 0) */
