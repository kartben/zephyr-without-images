/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 * Copyright (c) 2018 Ioannis Glaropoulos
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define HAL_RADIO_NS2US_CEIL(ns)  ((ns + 999)/1000)
#define HAL_RADIO_NS2US_ROUND(ns) ((ns + 500)/1000)

/* Use the timer instance ID, not NRF_TIMERx directly, so that it can be checked
 * in radio_nrf5_ppi.h by the preprocessor.
 */
#define EVENT_TIMER_ID 0
#define EVENT_TIMER    _CONCAT(NRF_TIMER, EVENT_TIMER_ID)

/* Wrapper for EVENTS_END event generated by Radio peripheral at the very end of the transmission
 * or reception of a PDU on air. In case of regular PDU it is generated when last bit of CRC is
 * received or transmitted.
 */
#define NRF_RADIO_TXRX_END_EVENT EVENTS_END
/* Wrapper for RADIO_SHORTS mask connecting EVENTS_END to EVENTS_DISABLE.
 * This is a default shortcut used to automatically disable Radio after end of PDU.
 */
#define NRF_RADIO_SHORTS_PDU_END_DISABLE RADIO_SHORTS_END_DISABLE_Msk

#if defined(CONFIG_BT_CTLR_DF_PHYEND_OFFSET_COMPENSATION_ENABLE)
/* Delay of EVENTS_PHYEND event on receive PDU without CTE inclded when CTEINLINE is enabled */
#define RADIO_EVENTS_PHYEND_DELAY_US 16
#endif /* CONFIG_BT_CTLR_DF_PHYEND_OFFSET_COMPENSATION_ENABLE */

/* EVENTS_TIMER capture register used for sampling TIMER time-stamps. */
#define HAL_EVENT_TIMER_SAMPLE_CC_OFFSET 3
#define HAL_EVENT_TIMER_SAMPLE_TASK NRF_TIMER_TASK_CAPTURE3

#define NRF_PPI_NONE 0

#if defined(CONFIG_SOC_SERIES_BSIM_NRFXX)
#include "radio_sim_nrfxx.h"
#elif defined(CONFIG_SOC_SERIES_NRF51X)
#include "radio_nrf51.h"
#elif defined(CONFIG_SOC_NRF52805)
#include "radio_nrf52805.h"
#elif defined(CONFIG_SOC_NRF52810)
#include "radio_nrf52810.h"
#elif defined(CONFIG_SOC_NRF52811)
#include "radio_nrf52811.h"
#elif defined(CONFIG_SOC_NRF52820)
#include "radio_nrf52820.h"
#elif defined(CONFIG_SOC_NRF52832)
#include "radio_nrf52832.h"
#elif defined(CONFIG_SOC_NRF52833)
#include "radio_nrf52833.h"
#elif defined(CONFIG_SOC_NRF52840)
#include <nrf52_erratas.h>
#include "radio_nrf52840.h"
#elif defined(CONFIG_SOC_NRF5340_CPUNET)
#include "radio_nrf5340.h"
#elif
#error "Unsupported SoC."
#endif

#if defined(CONFIG_SOC_SERIES_NRF51X)
#define HAL_RADIO_PDU_LEN_MAX (BIT(5) - 1)
#else
#define HAL_RADIO_PDU_LEN_MAX (BIT(8) - 1)
#endif

#include <nrf_peripherals.h>

/* This has to come before the ppi/dppi includes below. */
#include "radio_nrf5_fem.h"

#if defined(PPI_PRESENT)
#include "radio_nrf5_ppi.h"
#elif defined(DPPI_PRESENT)
#include "radio_nrf5_dppi.h"
#else
#error "PPI or DPPI abstractions missing."
#endif
#include "radio_nrf5_txp.h"
