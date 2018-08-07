/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 * Copyright (c) 2018 Ioannis Glaropoulos
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#if defined(CONFIG_SOC_SERIES_NRF51X) || defined(CONFIG_SOC_SERIES_NRF52X)

#include "nrf_ppi.h"

/* Enable Radio on Event Timer tick:
 * wire the EVENT_TIMER EVENTS_COMPARE[0] event to RADIO TASKS_TXEN/RXEN task.
 */
#define HAL_RADIO_ENABLE_ON_TICK_PPI 0
#define HAL_RADIO_ENABLE_ON_TICK_PPI_ENABLE \
	((PPI_CHENSET_CH0_Set << PPI_CHENSET_CH0_Pos) & PPI_CHENSET_CH0_Msk)
#define HAL_RADIO_ENABLE_ON_TICK_PPI_DISABLE \
	((PPI_CHENCLR_CH0_Clear << PPI_CHENCLR_CH0_Pos) & PPI_CHENCLR_CH0_Msk)
#define HAL_RADIO_ENABLE_ON_TICK_PPI_EVT \
	((u32_t)&(EVENT_TIMER->EVENTS_COMPARE[0]))
#define HAL_RADIO_ENABLE_ON_TICK_PPI_TASK_TX \
	((u32_t)&(NRF_RADIO->TASKS_TXEN))
#define HAL_RADIO_ENABLE_ON_TICK_PPI_TASK_RX \
	((u32_t)&(NRF_RADIO->TASKS_RXEN))

static inline void hal_radio_enable_on_tick_ppi_config_and_enable(u8_t trx)
{
	nrf_ppi_channel_endpoint_setup(HAL_RADIO_ENABLE_ON_TICK_PPI,
					HAL_RADIO_ENABLE_ON_TICK_PPI_EVT,
				(trx) ? HAL_RADIO_ENABLE_ON_TICK_PPI_TASK_TX :
					HAL_RADIO_ENABLE_ON_TICK_PPI_TASK_RX);
	nrf_ppi_channels_enable(HAL_RADIO_ENABLE_ON_TICK_PPI_ENABLE);
}

/* Start event timer on RTC tick:
 * wire the RTC0 EVENTS_COMPARE[2] event to EVENT_TIMER  TASKS_START task.
 */
#define HAL_EVENT_TIMER_START_PPI 1
#define HAL_EVENT_TIMER_START_PPI_ENABLE \
	((PPI_CHENSET_CH1_Set << PPI_CHENSET_CH1_Pos) & PPI_CHENSET_CH1_Msk)
#define HAL_EVENT_TIMER_START_PPI_DISABLE \
	((PPI_CHENCLR_CH1_Clear << PPI_CHENCLR_CH1_Pos) & PPI_CHENCLR_CH1_Msk)
#define HAL_EVENT_TIMER_START_EVT \
	((u32_t)&(NRF_RTC0->EVENTS_COMPARE[2]))
#define HAL_EVENT_TIMER_START_TASK \
	((u32_t)&(EVENT_TIMER->TASKS_START))

/* Capture event timer on Radio ready:
 * wire the RADIO EVENTS_READY event to the
 * EVENT_TIMER TASKS_CAPTURE[<radio ready timer>] task.
 */
#define HAL_RADIO_READY_TIME_CAPTURE_PPI 2
#define HAL_RADIO_READY_TIME_CAPTURE_PPI_ENABLE \
	((PPI_CHENSET_CH2_Set << PPI_CHENSET_CH2_Pos) & PPI_CHENSET_CH2_Msk)
#define HAL_RADIO_READY_TIME_CAPTURE_PPI_DISABLE \
	((PPI_CHENCLR_CH2_Clear << PPI_CHENCLR_CH2_Pos) & PPI_CHENCLR_CH2_Msk)
#define HAL_RADIO_READY_TIME_CAPTURE_PPI_EVT \
	((u32_t)&(NRF_RADIO->EVENTS_READY))
#define HAL_RADIO_READY_TIME_CAPTURE_PPI_TASK \
	((u32_t)&(EVENT_TIMER->TASKS_CAPTURE[0]))

/* Capture event timer on Address reception:
 * wire the RADIO EVENTS_ADDRESS event to the
 * EVENT_TIMER TASKS_CAPTURE[<address  timer>] task.
 */
#define HAL_RADIO_RECV_TIMEOUT_CANCEL_PPI 3
#define HAL_RADIO_RECV_TIMEOUT_CANCEL_PPI_ENABLE \
	((PPI_CHENSET_CH3_Set << PPI_CHENSET_CH3_Pos) & PPI_CHENSET_CH3_Msk)
#define HAL_RADIO_RECV_TIMEOUT_CANCEL_PPI_DISABLE \
	((PPI_CHENCLR_CH3_Clear << PPI_CHENCLR_CH3_Pos) & PPI_CHENCLR_CH3_Msk)
#define HAL_RADIO_RECV_TIMEOUT_CANCEL_PPI_EVT \
	((u32_t)&(NRF_RADIO->EVENTS_ADDRESS))
#define HAL_RADIO_RECV_TIMEOUT_CANCEL_PPI_TASK \
	((u32_t)&(EVENT_TIMER->TASKS_CAPTURE[1]))

/* Disable Radio on HCTO:
 * wire the EVENT_TIMER EVENTS_COMPARE[<HCTO timer>] event
 * to the RADIO TASKS_DISABLE task.
 */
#define HAL_RADIO_DISABLE_ON_HCTO_PPI 4
#define HAL_RADIO_DISABLE_ON_HCTO_PPI_ENABLE \
	((PPI_CHENSET_CH4_Set << PPI_CHENSET_CH4_Pos) & PPI_CHENSET_CH4_Msk)
#define HAL_RADIO_DISABLE_ON_HCTO_PPI_DISABLE \
	((PPI_CHENCLR_CH4_Clear << PPI_CHENCLR_CH4_Pos) & PPI_CHENCLR_CH4_Msk)
#define HAL_RADIO_DISABLE_ON_HCTO_PPI_EVT \
	((u32_t)&(EVENT_TIMER->EVENTS_COMPARE[1]))
#define HAL_RADIO_DISABLE_ON_HCTO_PPI_TASK \
	((u32_t)&(NRF_RADIO->TASKS_DISABLE))

/* Capture event timer on Radio end:
 * wire the RADIO EVENTS_END event to the
 * EVENT_TIMER TASKS_CAPTURE[<radio end timer>] task.
 */
#define HAL_RADIO_END_TIME_CAPTURE_PPI 5
#define HAL_RADIO_END_TIME_CAPTURE_PPI_ENABLE \
	((PPI_CHENSET_CH5_Set << PPI_CHENSET_CH5_Pos) & PPI_CHENSET_CH5_Msk)
#define HAL_RADIO_END_TIME_CAPTURE_PPI_DISABLE \
	((PPI_CHENCLR_CH5_Clear << PPI_CHENCLR_CH5_Pos) & PPI_CHENCLR_CH5_Msk)
#define HAL_RADIO_END_TIME_CAPTURE_PPI_EVT \
	((u32_t)&(NRF_RADIO->EVENTS_END))
#define HAL_RADIO_END_TIME_CAPTURE_PPI_TASK \
	((u32_t)&(EVENT_TIMER->TASKS_CAPTURE[2]))

/* Trigger encryption task upon Address reception:
 * wire the RADIO EVENTS_ADDRESS event to the CCM TASKS_CRYPT task.
 */
#define HAL_TRIGGER_CRYPT_PPI 6
#define HAL_TRIGGER_CRYPT_PPI_ENABLE \
	((PPI_CHENSET_CH6_Set << PPI_CHENSET_CH6_Pos) & PPI_CHENSET_CH6_Msk)
#define HAL_TRIGGER_CRYPT_PPI_DISABLE \
	((PPI_CHENCLR_CH6_Clear << PPI_CHENCLR_CH6_Pos) & PPI_CHENCLR_CH6_Msk)
#define HAL_TRIGGER_CRYPT_PPI_EVT \
	((u32_t)&(NRF_RADIO->EVENTS_ADDRESS))
#define HAL_TRIGGER_CRYPT_PPI_TASK \
	((u32_t)&(NRF_CCM->TASKS_CRYPT))

/* Trigger automatic address resolution on Bit counter match:
 * wire the RADIO EVENTS_BCMATCH event to the AAR TASKS_START task.
 * Note that this PPI channel is shared with the encrypt triggering on Address
 * reception.
 */
#define HAL_TRIGGER_AAR_PPI 6
#define HAL_TRIGGER_AAR_PPI_ENABLE \
	((PPI_CHENSET_CH6_Set << PPI_CHENSET_CH6_Pos) & PPI_CHENSET_CH6_Msk)
#define HAL_TRIGGER_AAR_PPI_DISABLE \
	((PPI_CHENCLR_CH6_Clear << PPI_CHENCLR_CH6_Pos) & PPI_CHENCLR_CH6_Msk)
#define HAL_TRIGGER_AAR_PPI_EVT \
	((u32_t)&(NRF_RADIO->EVENTS_BCMATCH))
#define HAL_TRIGGER_AAR_PPI_TASK \
	((u32_t)&(NRF_AAR->TASKS_START))

/* Trigger Radio Rate override upon Rateboost event. */
#if defined(CONFIG_SOC_NRF52840)
#define HAL_TRIGGER_RATEOVERRIDE_PPI 13
#define HAL_TRIGGER_RATEOVERRIDE_PPI_ENABLE \
	((PPI_CHENSET_CH13_Set << PPI_CHENSET_CH13_Pos) & PPI_CHENSET_CH13_Msk)
#define HAL_TRIGGER_RATEOVERRIDE_PPI_DISABLE \
	((PPI_CHENCLR_CH13_Clear << PPI_CHENCLR_CH13_Pos) \
	& PPI_CHENCLR_CH13_Msk)
#define HAL_TRIGGER_RATEOVERRIDE_PPI_REGISTER_EVT \
	NRF_PPI->CH[HAL_TRIGGER_RATEOVERRIDE_PPI].EEP
#define HAL_TRIGGER_RATEOVERRIDE_PPI_EVT \
	((u32_t)&(NRF_RADIO->EVENTS_RATEBOOST))
#define HAL_TRIGGER_RATEOVERRIDE_PPI_REGISTER_TASK \
	NRF_PPI->CH[HAL_TRIGGER_RATEOVERRIDE_PPI].TEP
#define HAL_TRIGGER_RATEOVERRIDE_PPI_TASK \
	((u32_t)&(NRF_CCM->TASKS_RATEOVERRIDE))
#endif /* CONFIG_SOC_NRF52840 */

#if defined(CONFIG_BT_CTLR_GPIO_PA_PIN) || defined(CONFIG_BT_CTLR_GPIO_LNA_PIN)
#define HAL_ENABLE_PALNA_PPI 14
#define HAL_ENABLE_PALNA_PPI_ENABLE \
	((PPI_CHENSET_CH14_Set << PPI_CHENSET_CH14_Pos) & PPI_CHENSET_CH14_Msk)
#define HAL_ENABLE_PALNA_PPI_DISABLE \
	((PPI_CHENCLR_CH14_Clear << PPI_CHENCLR_CH14_Pos) \
	& PPI_CHENCLR_CH14_Msk)
#define HAL_ENABLE_PALNA_PPI_REGISTER_EVT \
	NRF_PPI->CH[HAL_ENABLE_PALNA_PPI].EEP
#define HAL_ENABLE_PALNA_PPI_EVT \
	((u32_t)&(EVENT_TIMER->EVENTS_COMPARE[2]))
#define HAL_ENABLE_PALNA_PPI_REGISTER_TASK \
	NRF_PPI->CH[HAL_ENABLE_PALNA_PPI].TEP
#define HAL_ENABLE_PALNA_PPI_TASK \
	((u32_t)&(NRF_GPIOTE->TASKS_OUT[CONFIG_BT_CTLR_PA_LNA_GPIOTE_CHAN]))

#define HAL_DISABLE_PALNA_PPI 15
#define HAL_DISABLE_PALNA_PPI_ENABLE \
	((PPI_CHENSET_CH15_Set << PPI_CHENSET_CH15_Pos) & PPI_CHENSET_CH15_Msk)
#define HAL_DISABLE_PALNA_PPI_DISABLE \
	((PPI_CHENCLR_CH15_Clear << PPI_CHENCLR_CH15_Pos) \
	& PPI_CHENCLR_CH15_Msk)
#define HAL_DISABLE_PALNA_PPI_REGISTER_EVT \
	NRF_PPI->CH[HAL_DISABLE_PALNA_PPI].EEP
#define HAL_DISABLE_PALNA_PPI_EVT \
	((u32_t)&(NRF_RADIO->EVENTS_DISABLED))
#define HAL_DISABLE_PALNA_PPI_REGISTER_TASK \
	NRF_PPI->CH[HAL_DISABLE_PALNA_PPI].TEP
#define HAL_DISABLE_PALNA_PPI_TASK \
	((u32_t)&(NRF_GPIOTE->TASKS_OUT[CONFIG_BT_CTLR_PA_LNA_GPIOTE_CHAN]))
#endif /* CONFIG_BT_CTLR_GPIO_PA_PIN || CONFIG_BT_CTLR_GPIO_LNA_PIN */

#if !defined(CONFIG_BT_CTLR_TIFS_HW)
/* PPI setup used for SW-based auto-switching during TIFS. */

#if !defined(CONFIG_BT_CTLR_SW_SWITCH_SINGLE_TIMER)
/* Clear SW-switch timer on packet end:
 * wire the RADIO EVENTS_END event to SW_SWITCH_TIMER TASKS_CLEAR task.
 *
 * Note: this PPI is not needed if we use a single TIMER instance in radio.c
 */
#define HAL_SW_SWITCH_TIMER_CLEAR_PPI 7
#define HAL_SW_SWITCH_TIMER_CLEAR_PPI_ENABLE \
	((PPI_CHENSET_CH7_Set << PPI_CHENSET_CH7_Pos) & PPI_CHENSET_CH7_Msk)
#define HAL_SW_SWITCH_TIMER_CLEAR_PPI_DISABLE \
	((PPI_CHENCLR_CH7_Clear << PPI_CHENCLR_CH7_Pos) & PPI_CHENCLR_CH7_Msk)
#else /* !CONFIG_BT_CTLR_SW_SWITCH_SINGLE_TIMER */

/* Clear event timer (sw-switch timer) on Radio end:
 * wire the RADIO EVENTS_END event to the
 * EVENT_TIMER TASKS_CLEAR task.
 *
 * Note: in nRF52X PPI 5 is forked for both capturing and clearing timer
 * on RADIO EVENTS_END.
 */
#define HAL_SW_SWITCH_TIMER_CLEAR_PPI 5
#define HAL_SW_SWITCH_TIMER_CLEAR_PPI_ENABLE \
	((PPI_CHENSET_CH5_Set << PPI_CHENSET_CH5_Pos) & PPI_CHENSET_CH5_Msk)
#define HAL_SW_SWITCH_TIMER_CLEAR_PPI_DISABLE \
	((PPI_CHENCLR_CH5_Clear << PPI_CHENCLR_CH5_Pos) & PPI_CHENCLR_CH5_Msk)
#endif /*  !CONFIG_BT_CTLR_SW_SWITCH_SINGLE_TIMER */
#define HAL_SW_SWITCH_TIMER_CLEAR_PPI_REGISTER_EVT \
	NRF_PPI->CH[HAL_SW_SWITCH_TIMER_CLEAR_PPI].EEP
#define HAL_SW_SWITCH_TIMER_CLEAR_PPI_EVT \
	((u32_t)&(NRF_RADIO->EVENTS_END))
#if !defined(CONFIG_BT_CTLR_SW_SWITCH_SINGLE_TIMER)
#define HAL_SW_SWITCH_TIMER_CLEAR_PPI_REGISTER_TASK \
	NRF_PPI->CH[HAL_SW_SWITCH_TIMER_CLEAR_PPI].TEP
#else /* !CONFIG_BT_CTLR_SW_SWITCH_SINGLE_TIMER */
#define HAL_SW_SWITCH_TIMER_CLEAR_PPI_REGISTER_TASK \
	NRF_PPI->FORK[HAL_SW_SWITCH_TIMER_CLEAR_PPI].TEP
#endif /* !CONFIG_BT_CTLR_SW_SWITCH_SINGLE_TIMER */
#define HAL_SW_SWITCH_TIMER_CLEAR_PPI_TASK \
	((u32_t)&(SW_SWITCH_TIMER->TASKS_CLEAR))

/* The 2 adjacent PPI groups used for implementing SW_SWITCH_TIMER-based
 * auto-switch for TIFS. 'index' must be 0 or 1.
 */
#define SW_SWITCH_TIMER_TASK_GROUP(index) \
	(SW_SWITCH_TIMER_TASK_GROUP_BASE + index)

/* The 2 adjacent TIMER EVENTS_COMPARE event offsets used for implementing
 * SW_SWITCH_TIMER-based auto-switch for TIFS. 'index' must be 0 or 1.
 */
#define SW_SWITCH_TIMER_EVTS_COMP(index) \
	(SW_SWITCH_TIMER_EVTS_COMP_BASE + index)

/* Wire a SW SWITCH TIMER EVENTS_COMPARE[<cc_offset>] event
 * to a PPI GROUP TASK DISABLE task (PPI group with index <index>).
 * 2 adjacent PPIs (8 & 9) and 2 adjacent PPI groups are used for this wiring;
 * <index> must be 0 or 1. <offset> must be a valid TIMER CC register offset.
 */
#define HAL_SW_SWITCH_GROUP_TASK_DISABLE_PPI_BASE 8
#define HAL_SW_SWITCH_GROUP_TASK_DISABLE_PPI(index) \
	(HAL_SW_SWITCH_GROUP_TASK_DISABLE_PPI_BASE + index)
#define HAL_SW_SWITCH_GROUP_TASK_DISABLE_PPI_0_INCLUDE \
	((PPI_CHG_CH8_Included << PPI_CHG_CH8_Pos) & PPI_CHG_CH8_Msk)
#define HAL_SW_SWITCH_GROUP_TASK_DISABLE_PPI_0_EXCLUDE \
	((PPI_CHG_CH8_Excluded << PPI_CHG_CH8_Pos) & PPI_CHG_CH8_Msk)
#define HAL_SW_SWITCH_GROUP_TASK_DISABLE_PPI_1_INCLUDE \
	((PPI_CHG_CH9_Included << PPI_CHG_CH9_Pos) & PPI_CHG_CH9_Msk)
#define HAL_SW_SWITCH_GROUP_TASK_DISABLE_PPI_1_EXCLUDE \
	((PPI_CHG_CH9_Excluded << PPI_CHG_CH9_Pos) & PPI_CHG_CH9_Msk)
#define HAL_SW_SWITCH_GROUP_TASK_DISABLE_PPI_REGISTER_EVT(chan) \
	NRF_PPI->CH[chan].EEP
#define HAL_SW_SWITCH_GROUP_TASK_DISABLE_PPI_EVT(cc_offset) \
	((u32_t)&(SW_SWITCH_TIMER->EVENTS_COMPARE[cc_offset]))
#define HAL_SW_SWITCH_GROUP_TASK_DISABLE_PPI_REGISTER_TASK(chan) \
	NRF_PPI->CH[chan].TEP
#define HAL_SW_SWITCH_GROUP_TASK_DISABLE_PPI_TASK(index) \
	((u32_t)&(NRF_PPI->TASKS_CHG[SW_SWITCH_TIMER_TASK_GROUP(index)].DIS))

/* Wire the RADIO EVENTS_END event to one of the PPI GROUP TASK ENABLE task.
 * 2 adjacent PPI groups are used for this wiring. 'index' must be 0 or 1.
 */
#define HAL_SW_SWITCH_GROUP_TASK_ENABLE_PPI 10
#define HAL_SW_SWITCH_GROUP_TASK_ENABLE_PPI_ENABLE \
	((PPI_CHENSET_CH10_Set << PPI_CHENSET_CH10_Pos) & PPI_CHENSET_CH10_Msk)
#define HAL_SW_SWITCH_GROUP_TASK_ENABLE_PPI_DISABLE \
	((PPI_CHENCLR_CH10_Clear << PPI_CHENCLR_CH10_Pos) \
	& PPI_CHENCLR_CH10_Msk)
#define HAL_SW_SWITCH_GROUP_TASK_ENABLE_PPI_EVT \
	((u32_t)&(NRF_RADIO->EVENTS_END))
#define HAL_SW_SWITCH_GROUP_TASK_ENABLE_PPI_TASK(index) \
	((u32_t)&(NRF_PPI->TASKS_CHG[SW_SWITCH_TIMER_TASK_GROUP(index)].EN))

/*Enable Radio at specific time-stamp:
 * wire the SW SWITCH TIMER EVENTS_COMPARE[<cc_offset>] event
 * to RADIO TASKS_TXEN/RXEN task.
 * 2 adjacent PPIs (11 & 12) are used for this wiring; <index> must be 0 or 1.
 * <offset> must be a valid TIMER CC register offset.
 */
#define HAL_SW_SWITCH_RADIO_ENABLE_PPI_BASE 11
#define HAL_SW_SWITCH_RADIO_ENABLE_PPI(index) \
	(HAL_SW_SWITCH_RADIO_ENABLE_PPI_BASE + index)
#define HAL_SW_SWITCH_RADIO_ENABLE_PPI_0_INCLUDE \
	((PPI_CHG_CH11_Included << PPI_CHG_CH11_Pos) & PPI_CHG_CH11_Msk)
#define HAL_SW_SWITCH_RADIO_ENABLE_PPI_0_EXCLUDE \
	((PPI_CHG_CH11_Excluded << PPI_CHG_CH11_Pos) & PPI_CHG_CH11_Msk)
#define HAL_SW_SWITCH_RADIO_ENABLE_PPI_1_INCLUDE \
	((PPI_CHG_CH12_Included << PPI_CHG_CH12_Pos) & PPI_CHG_CH12_Msk)
#define HAL_SW_SWITCH_RADIO_ENABLE_PPI_1_EXCLUDE \
	((PPI_CHG_CH12_Excluded << PPI_CHG_CH12_Pos) & PPI_CHG_CH12_Msk)
#define HAL_SW_SWITCH_RADIO_ENABLE_PPI_REGISTER_EVT(chan) \
	NRF_PPI->CH[chan].EEP
#define HAL_SW_SWITCH_RADIO_ENABLE_PPI_EVT(cc_offset) \
	((u32_t)&(SW_SWITCH_TIMER->EVENTS_COMPARE[cc_offset]))
#define HAL_SW_SWITCH_RADIO_ENABLE_PPI_REGISTER_TASK(chan) \
	NRF_PPI->CH[chan].TEP
#define HAL_SW_SWITCH_RADIO_ENABLE_PPI_TASK_TX \
	((u32_t)&(NRF_RADIO->TASKS_TXEN))
#define HAL_SW_SWITCH_RADIO_ENABLE_PPI_TASK_RX \
	((u32_t)&(NRF_RADIO->TASKS_RXEN))


static inline void hal_radio_txen_on_sw_switch(u8_t ppi)
{
	nrf_ppi_task_endpoint_setup(ppi,
		HAL_SW_SWITCH_RADIO_ENABLE_PPI_TASK_TX);
}

static inline void hal_radio_rxen_on_sw_switch(u8_t ppi)
{
	nrf_ppi_task_endpoint_setup(ppi,
		HAL_SW_SWITCH_RADIO_ENABLE_PPI_TASK_RX);
}

#if defined(CONFIG_SOC_NRF52840)
/* Wire the SW SWITCH TIMER EVENTS_COMPARE[<cc_offset>] event
 * to RADIO TASKS_TXEN/RXEN task.
 * 2 adjacent PPIs (16 & 17) are used for this wiring; <index> must be 0 or 1.
 */
#define HAL_SW_SWITCH_RADIO_ENABLE_S2_PPI 16
#define HAL_SW_SWITCH_RADIO_ENABLE_S2_PPI_INCLUDE \
	((PPI_CHG_CH16_Included << PPI_CHG_CH16_Pos) & PPI_CHG_CH16_Msk)
#define HAL_SW_SWITCH_RADIO_ENABLE_S2_PPI_EXCLUDE \
	((PPI_CHG_CH16_Excluded << PPI_CHG_CH16_Pos) & PPI_CHG_CH16_Msk)

/* Cancel the SW switch timer running considering S8 timing:
 * wire the RADIO EVENTS_RATEBOOST event to SW_SWITCH_TIMER TASKS_CAPTURE task.
 */
#define HAL_SW_SWITCH_TIMER_S8_DISABLE_PPI 17
#define HAL_SW_SWITCH_TIMER_S8_DISABLE_PPI_ENABLE \
	((PPI_CHENSET_CH18_Set << PPI_CHENSET_CH18_Pos) & PPI_CHENSET_CH18_Msk)
#define HAL_SW_SWITCH_TIMER_S8_DISABLE_PPI_DISABLE \
	((PPI_CHENCLR_CH18_Clear << PPI_CHENCLR_CH18_Pos) \
	& PPI_CHENCLR_CH18_Msk)
#define HAL_SW_SWITCH_TIMER_S8_DISABLE_PPI_REGISTER_EVT \
	NRF_PPI->CH[HAL_SW_SWITCH_TIMER_S8_DISABLE_PPI].EEP
#define HAL_SW_SWITCH_TIMER_S8_DISABLE_PPI_EVT \
	((u32_t)&(NRF_RADIO->EVENTS_RATEBOOST))
#define HAL_SW_SWITCH_TIMER_S8_DISABLE_PPI_REGISTER_TASK \
	NRF_PPI->CH[HAL_SW_SWITCH_TIMER_S8_DISABLE_PPI].TEP
#define HAL_SW_SWITCH_TIMER_S8_DISABLE_PPI_TASK(index) \
	((u32_t)&(SW_SWITCH_TIMER->TASKS_CAPTURE[index]))

#endif /* CONFIG_SOC_NRF52840 */
#endif /* !CONFIG_BT_CTLR_TIFS_HW */
#endif /* CONFIG_SOC_SERIES_NRF51X || CONFIG_SOC_SERIES_NRF52X */
