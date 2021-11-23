/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <sys/util.h>
#include "radio_nrf5_fem.h"

#if defined(CONFIG_BT_CTLR_TIFS_HW) || !defined(CONFIG_BT_CTLR_SW_SWITCH_SINGLE_TIMER)

/* PPI channel 20 is pre-programmed with the following fixed settings:
 *   EEP: TIMER0->EVENTS_COMPARE[0]
 *   TEP: RADIO->TASKS_TXEN
 */
#define HAL_RADIO_ENABLE_TX_ON_TICK_PPI 20
/* PPI channel 21 is pre-programmed with the following fixed settings:
 *   EEP: TIMER0->EVENTS_COMPARE[0]
 *   TEP: RADIO->TASKS_RXEN
 */
#define HAL_RADIO_ENABLE_RX_ON_TICK_PPI 21

/* PPI channel 26 is pre-programmed with the following fixed settings:
 *   EEP: RADIO->EVENTS_ADDRESS
 *   TEP: TIMER0->TASKS_CAPTURE[1]
 */
#define HAL_RADIO_RECV_TIMEOUT_CANCEL_PPI 26

/* PPI channel 22 is pre-programmed with the following fixed settings:
 *   EEP: TIMER0->EVENTS_COMPARE[1]
 *   TEP: RADIO->TASKS_DISABLE
 */
#define HAL_RADIO_DISABLE_ON_HCTO_PPI 22

/* PPI channel 27 is pre-programmed with the following fixed settings:
 *   EEP: RADIO->EVENTS_END
 *   TEP: TIMER0->TASKS_CAPTURE[2]
 */
#define HAL_RADIO_END_TIME_CAPTURE_PPI 27

#else /* CONFIG_BT_CTLR_TIFS_HW || !CONFIG_BT_CTLR_SW_SWITCH_SINGLE_TIMER */

#define HAL_RADIO_ENABLE_ON_TICK_PPI 2
#define HAL_RADIO_ENABLE_TX_ON_TICK_PPI HAL_RADIO_ENABLE_ON_TICK_PPI
#define HAL_RADIO_ENABLE_RX_ON_TICK_PPI HAL_RADIO_ENABLE_ON_TICK_PPI
#define HAL_RADIO_RECV_TIMEOUT_CANCEL_PPI 3
#define HAL_RADIO_DISABLE_ON_HCTO_PPI 4
#define HAL_RADIO_END_TIME_CAPTURE_PPI 5

#endif /* CONFIG_BT_CTLR_TIFS_HW || !CONFIG_BT_CTLR_SW_SWITCH_SINGLE_TIMER */

/* Start event timer on RTC tick wire the RTC0 EVENTS_COMPARE[2] event to
 * EVENT_TIMER  TASKS_START task.
 */
#define HAL_EVENT_TIMER_START_PPI 6

/* Capture event timer on Radio ready, wire the RADIO EVENTS_READY event to the
 * EVENT_TIMER TASKS_CAPTURE[<radio ready timer>] task.
 */
#define HAL_RADIO_READY_TIME_CAPTURE_PPI 7

/* Trigger encryption task upon address reception:
 * wire the RADIO EVENTS_ADDRESS event to the CCM TASKS_CRYPT task.
 *
 * PPI channel 25 is pre-programmed with the following fixed settings:
 *   EEP: RADIO->EVENTS_ADDRESS
 *   TEP: CCM->TASKS_CRYPT
 */
#define HAL_TRIGGER_CRYPT_PPI 25

/* Trigger automatic address resolution on Bit counter match:
 * wire the RADIO EVENTS_BCMATCH event to the AAR TASKS_START task.
 *
 * PPI channel 23 is pre-programmed with the following fixed settings:
 *   EEP: RADIO->EVENTS_BCMATCH
 *   TEP: AAR->TASKS_START
 */
#define HAL_TRIGGER_AAR_PPI 23

/* Trigger Radio Rate override upon Rateboost event. */
#if defined(CONFIG_HAS_HW_NRF_RADIO_BLE_CODED)
#define HAL_TRIGGER_RATEOVERRIDE_PPI 14
#endif /* CONFIG_HAS_HW_NRF_RADIO_BLE_CODED */

#define HAL_ENABLE_PALNA_PPI  15
#define HAL_DISABLE_PALNA_PPI 16

#if defined(HAL_RADIO_FEM_IS_NRF21540)
#define HAL_ENABLE_FEM_PPI  4
#define HAL_DISABLE_FEM_PPI 5
#endif /* HAL_RADIO_FEM_IS_NRF21540 */

#if !defined(CONFIG_BT_CTLR_TIFS_HW)
/* PPI setup used for SW-based auto-switching during TIFS. */

#if !defined(CONFIG_BT_CTLR_SW_SWITCH_SINGLE_TIMER)

/* Clear SW-switch timer on packet end:
 * wire the RADIO EVENTS_END event to SW_SWITCH_TIMER TASKS_CLEAR task.
 *
 * Note: this PPI is not needed if we use a single TIMER instance in radio.c
 */
#define HAL_SW_SWITCH_TIMER_CLEAR_PPI 8

#else /* !CONFIG_BT_CTLR_SW_SWITCH_SINGLE_TIMER */

/* Clear event timer (sw-switch timer) on Radio end:
 * wire the RADIO EVENTS_END event to the
 * EVENT_TIMER TASKS_CLEAR task.
 *
 * Note: in nRF52X this PPI channel is forked for both capturing and clearing
 * timer on RADIO EVENTS_END.
 */
#define HAL_SW_SWITCH_TIMER_CLEAR_PPI HAL_RADIO_END_TIME_CAPTURE_PPI

#endif /* !CONFIG_BT_CTLR_SW_SWITCH_SINGLE_TIMER */

/* Wire a SW SWITCH TIMER EVENTS_COMPARE[<cc_offset>] event
 * to a PPI GROUP TASK DISABLE task (PPI group with index <index>).
 * 2 adjacent PPIs (9 & 10) and 2 adjacent PPI groups are used for this wiring;
 * <index> must be 0 or 1. <offset> must be a valid TIMER CC register offset.
 */
#if defined(CONFIG_SOC_NRF52805)
#define HAL_SW_SWITCH_GROUP_TASK_DISABLE_PPI_BASE 2
#else /* CONFIG_SOC_NRF52805 */
#define HAL_SW_SWITCH_GROUP_TASK_DISABLE_PPI_BASE 9
#endif

/* Wire the RADIO EVENTS_END event to one of the PPI GROUP TASK ENABLE task.
 * 2 adjacent PPI groups are used for this wiring. 'index' must be 0 or 1.
 */
#if defined(CONFIG_SOC_NRF52805)
#define HAL_SW_SWITCH_GROUP_TASK_ENABLE_PPI 9
#else /* CONFIG_SOC_NRF52805 */
#define HAL_SW_SWITCH_GROUP_TASK_ENABLE_PPI 11
#endif

/*Enable Radio at specific time-stamp:
 * wire the SW SWITCH TIMER EVENTS_COMPARE[<cc_offset>] event
 * to RADIO TASKS_TXEN/RXEN task.
 * 2 adjacent PPIs (12 & 13) are used for this wiring; <index> must be 0 or 1.
 * <offset> must be a valid TIMER CC register offset.
 */
#if defined(CONFIG_SOC_NRF52805)
#define HAL_SW_SWITCH_RADIO_ENABLE_PPI_BASE 4
#else /* CONFIG_SOC_NRF52805 */
#define HAL_SW_SWITCH_RADIO_ENABLE_PPI_BASE 12
#endif

#if defined(CONFIG_BT_CTLR_PHY_CODED) && \
	defined(CONFIG_HAS_HW_NRF_RADIO_BLE_CODED)

/* Wire the SW SWITCH TIMER EVENTS_COMPARE[<cc_offset>] event
 * to RADIO TASKS_TXEN/RXEN task.
 */
#define HAL_SW_SWITCH_RADIO_ENABLE_S2_PPI_BASE 17

/* Cancel the SW switch timer running considering S8 timing:
 * wire the RADIO EVENTS_RATEBOOST event to SW_SWITCH_TIMER TASKS_CAPTURE task.
 */
#define HAL_SW_SWITCH_TIMER_S8_DISABLE_PPI 19

#endif /* CONFIG_HAS_HW_NRF_RADIO_BLE_CODED */

#endif /* !CONFIG_BT_CTLR_TIFS_HW */
