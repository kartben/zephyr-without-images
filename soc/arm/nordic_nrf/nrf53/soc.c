/*
 * Copyright (c) 2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief System/hardware module for Nordic Semiconductor nRF53 family processor
 *
 * This module provides routines to initialize and support board-level hardware
 * for the Nordic Semiconductor nRF53 family processor.
 */

#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <soc/nrfx_coredep.h>
#include <zephyr/logging/log.h>
#include <nrf_erratas.h>
#include <hal/nrf_power.h>
#include <hal/nrf_ipc.h>
#include <helpers/nrfx_gppi.h>
#if defined(CONFIG_SOC_NRF5340_CPUAPP)
#include <zephyr/drivers/gpio.h>
#include <zephyr/devicetree.h>
#include <hal/nrf_cache.h>
#include <hal/nrf_gpio.h>
#include <hal/nrf_oscillators.h>
#include <hal/nrf_regulators.h>
#elif defined(CONFIG_SOC_NRF5340_CPUNET)
#include <hal/nrf_nvmc.h>
#endif
#if defined(CONFIG_PM_S2RAM)
#include <hal/nrf_vmc.h>
#endif
#include <hal/nrf_wdt.h>
#include <hal/nrf_rtc.h>
#include <soc_secure.h>

#include <cmsis_core.h>

#define PIN_XL1 0
#define PIN_XL2 1

#define RTC1_PRETICK_CC_CHAN 1
#define RTC1_PRETICK_OVERFLOW_CHAN 2

#if defined(CONFIG_SOC_NRF_GPIO_FORWARDER_FOR_NRF5340)
#define GPIOS_PSEL_BY_IDX(node_id, prop, idx) \
	NRF_DT_GPIOS_TO_PSEL_BY_IDX(node_id, prop, idx),
#define ALL_GPIOS_IN_NODE(node_id) \
	DT_FOREACH_PROP_ELEM(node_id, gpios, GPIOS_PSEL_BY_IDX)
#define ALL_GPIOS_IN_FORWARDER(node_id) \
	DT_FOREACH_CHILD(node_id, ALL_GPIOS_IN_NODE)
#endif

#define LOG_LEVEL CONFIG_SOC_LOG_LEVEL
LOG_MODULE_REGISTER(soc);

#if defined(CONFIG_PM_S2RAM)

#if defined(CONFIG_SOC_NRF5340_CPUAPP)
#define RAM_N_BLOCK	(8)
#elif defined(CONFIG_SOC_NRF5340_CPUNET)
#define RAM_N_BLOCK	(4)
#endif /* CONFIG_SOC_NRF5340_CPUAPP || CONFIG_SOC_NRF5340_CPUNET */

#define MASK_ALL_SECT	(VMC_RAM_POWER_S0RETENTION_Msk  | VMC_RAM_POWER_S1RETENTION_Msk  | \
			 VMC_RAM_POWER_S2RETENTION_Msk  | VMC_RAM_POWER_S3RETENTION_Msk  | \
			 VMC_RAM_POWER_S4RETENTION_Msk  | VMC_RAM_POWER_S5RETENTION_Msk  | \
			 VMC_RAM_POWER_S6RETENTION_Msk  | VMC_RAM_POWER_S7RETENTION_Msk  | \
			 VMC_RAM_POWER_S8RETENTION_Msk  | VMC_RAM_POWER_S9RETENTION_Msk  | \
			 VMC_RAM_POWER_S10RETENTION_Msk | VMC_RAM_POWER_S11RETENTION_Msk | \
			 VMC_RAM_POWER_S12RETENTION_Msk | VMC_RAM_POWER_S13RETENTION_Msk | \
			 VMC_RAM_POWER_S14RETENTION_Msk | VMC_RAM_POWER_S15RETENTION_Msk)

static void enable_ram_retention(void)
{
	/*
	 * Enable RAM retention for *ALL* the SRAM
	 */
	for (size_t n = 0; n < RAM_N_BLOCK; n++) {
		nrf_vmc_ram_block_retention_set(NRF_VMC, n, MASK_ALL_SECT);
	}

}
#endif /* CONFIG_PM_S2RAM */

#if defined(CONFIG_SOC_NRF53_ANOMALY_160_WORKAROUND)
/* This code prevents the CPU from entering sleep again if it already
 * entered sleep 5 times within last 200 us.
 */
static bool nrf53_anomaly_160_check(void)
{
	/* System clock cycles needed to cover 200 us window. */
	const uint32_t window_cycles =
		DIV_ROUND_UP(200 * CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC,
				 1000000);
	static uint32_t timestamps[5];
	static bool timestamps_filled;
	static uint8_t current;
	uint8_t oldest = (current + 1) % ARRAY_SIZE(timestamps);
	uint32_t now = k_cycle_get_32();

	if (timestamps_filled &&
	    /* + 1 because only fully elapsed cycles need to be counted. */
	    (now - timestamps[oldest]) < (window_cycles + 1)) {
		return false;
	}

	/* Check if the CPU actually entered sleep since the last visit here
	 * (WFE/WFI could return immediately if the wake-up event was already
	 * registered).
	 */
	if (nrf_power_event_check(NRF_POWER, NRF_POWER_EVENT_SLEEPENTER)) {
		nrf_power_event_clear(NRF_POWER, NRF_POWER_EVENT_SLEEPENTER);
		/* If so, update the index at which the current timestamp is
		 * to be stored so that it replaces the oldest one, otherwise
		 * (when the CPU did not sleep), the recently stored timestamp
		 * is updated.
		 */
		current = oldest;
		if (current == 0) {
			timestamps_filled = true;
		}
	}

	timestamps[current] = k_cycle_get_32();

	return true;
}

bool z_arm_on_enter_cpu_idle(void)
{
	bool ok_to_sleep = nrf53_anomaly_160_check();

#if (LOG_LEVEL >= LOG_LEVEL_DBG)
	static bool suppress_message;

	if (ok_to_sleep) {
		suppress_message = false;
	} else if (!suppress_message) {
		LOG_DBG("Anomaly 160 trigger conditions detected.");
		suppress_message = true;
	}
#endif
#if defined(CONFIG_SOC_NRF53_RTC_PRETICK) && defined(CONFIG_SOC_NRF5340_CPUNET)
	if (ok_to_sleep) {
		NRF_IPC->PUBLISH_RECEIVE[CONFIG_SOC_NRF53_RTC_PRETICK_IPC_CH_TO_NET] |=
			IPC_PUBLISH_RECEIVE_EN_Msk;
		if (!nrf_rtc_event_check(NRF_RTC0, NRF_RTC_CHANNEL_EVENT_ADDR(3)) &&
		    !nrf_rtc_event_check(NRF_RTC1, NRF_RTC_CHANNEL_EVENT_ADDR(RTC1_PRETICK_CC_CHAN)) &&
		    !nrf_rtc_event_check(NRF_RTC1, NRF_RTC_CHANNEL_EVENT_ADDR(RTC1_PRETICK_OVERFLOW_CHAN))) {
			NRF_WDT->TASKS_STOP = 1;
			/* Check if any event did not occur after we checked for
			 * stopping condition. If yes, we might have stopped WDT
			 * when it should be running. Restart it.
			 */
			if (nrf_rtc_event_check(NRF_RTC0, NRF_RTC_CHANNEL_EVENT_ADDR(3)) ||
			    nrf_rtc_event_check(NRF_RTC1, NRF_RTC_CHANNEL_EVENT_ADDR(RTC1_PRETICK_CC_CHAN)) ||
			    nrf_rtc_event_check(NRF_RTC1, NRF_RTC_CHANNEL_EVENT_ADDR(RTC1_PRETICK_OVERFLOW_CHAN))) {
				NRF_WDT->TASKS_START = 1;
			}
		}
	}
#endif

	return ok_to_sleep;
}
#endif /* CONFIG_SOC_NRF53_ANOMALY_160_WORKAROUND */

#if CONFIG_SOC_NRF53_RTC_PRETICK
#ifdef CONFIG_SOC_NRF5340_CPUAPP
/* RTC pretick - application core part. */
static int rtc_pretick_cpuapp_init(void)
{
	uint8_t ch;
	nrfx_err_t err;
	nrf_ipc_event_t ipc_event =
		nrf_ipc_receive_event_get(CONFIG_SOC_NRF53_RTC_PRETICK_IPC_CH_FROM_NET);
	nrf_ipc_task_t ipc_task =
		nrf_ipc_send_task_get(CONFIG_SOC_NRF53_RTC_PRETICK_IPC_CH_TO_NET);
	uint32_t task_ipc = nrf_ipc_task_address_get(NRF_IPC, ipc_task);
	uint32_t evt_ipc = nrf_ipc_event_address_get(NRF_IPC, ipc_event);

	err = nrfx_gppi_channel_alloc(&ch);
	if (err != NRFX_SUCCESS) {
		return -ENOMEM;
	}

	nrf_ipc_receive_config_set(NRF_IPC, CONFIG_SOC_NRF53_RTC_PRETICK_IPC_CH_FROM_NET,
				   BIT(CONFIG_SOC_NRF53_RTC_PRETICK_IPC_CH_FROM_NET));
	nrf_ipc_send_config_set(NRF_IPC, CONFIG_SOC_NRF53_RTC_PRETICK_IPC_CH_TO_NET,
				   BIT(CONFIG_SOC_NRF53_RTC_PRETICK_IPC_CH_TO_NET));

	nrfx_gppi_task_endpoint_setup(ch, task_ipc);
	nrfx_gppi_event_endpoint_setup(ch, evt_ipc);
	nrfx_gppi_channels_enable(BIT(ch));

	return 0;
}
#else /* CONFIG_SOC_NRF5340_CPUNET */

static void rtc_pretick_rtc_isr_hook(void)
{
	NRF_IPC->PUBLISH_RECEIVE[CONFIG_SOC_NRF53_RTC_PRETICK_IPC_CH_TO_NET] &=
			~IPC_PUBLISH_RECEIVE_EN_Msk;
}

void rtc_pretick_rtc0_isr_hook(void)
{
	rtc_pretick_rtc_isr_hook();
}

void rtc_pretick_rtc1_cc0_set_hook(uint32_t val)
{
	nrf_rtc_cc_set(NRF_RTC1, RTC1_PRETICK_CC_CHAN, val - 1);
}

void rtc_pretick_rtc1_isr_hook(void)
{
	rtc_pretick_rtc_isr_hook();

	if (nrf_rtc_event_check(NRF_RTC1, NRF_RTC_EVENT_OVERFLOW)) {
		if (IS_ENABLED(CONFIG_SOC_NRF53_RTC_PRETICK)) {
			nrf_rtc_event_clear(NRF_RTC1,
					    NRF_RTC_CHANNEL_EVENT_ADDR(RTC1_PRETICK_OVERFLOW_CHAN));
		}
	}
	if (nrf_rtc_event_check(NRF_RTC1, NRF_RTC_EVENT_COMPARE_0)) {
		if (IS_ENABLED(CONFIG_SOC_NRF53_RTC_PRETICK)) {
			nrf_rtc_event_clear(NRF_RTC1, NRF_RTC_CHANNEL_EVENT_ADDR(RTC1_PRETICK_CC_CHAN));
		}
	}
}

static int rtc_pretick_cpunet_init(void)
{
	uint8_t ppi_ch;
	nrf_ipc_task_t ipc_task =
		nrf_ipc_send_task_get(CONFIG_SOC_NRF53_RTC_PRETICK_IPC_CH_FROM_NET);
	nrf_ipc_event_t ipc_event =
		nrf_ipc_receive_event_get(CONFIG_SOC_NRF53_RTC_PRETICK_IPC_CH_TO_NET);
	uint32_t task_ipc = nrf_ipc_task_address_get(NRF_IPC, ipc_task);
	uint32_t evt_ipc = nrf_ipc_event_address_get(NRF_IPC, ipc_event);
	uint32_t task_wdt = nrf_wdt_task_address_get(NRF_WDT, NRF_WDT_TASK_START);
	uint32_t evt_mpsl_cc = nrf_rtc_event_address_get(NRF_RTC0, NRF_RTC_EVENT_COMPARE_3);
	uint32_t evt_cc = nrf_rtc_event_address_get(NRF_RTC1,
				NRF_RTC_CHANNEL_EVENT_ADDR(RTC1_PRETICK_CC_CHAN));
	uint32_t evt_overflow = nrf_rtc_event_address_get(NRF_RTC1,
				NRF_RTC_CHANNEL_EVENT_ADDR(RTC1_PRETICK_OVERFLOW_CHAN));

	/* Configure Watchdog to allow stopping. */
	nrf_wdt_behaviour_set(NRF_WDT, WDT_CONFIG_STOPEN_Msk | BIT(4));
	*((volatile uint32_t *)0x41203120) = 0x14;

	/* Configure IPC */
	nrf_ipc_receive_config_set(NRF_IPC, CONFIG_SOC_NRF53_RTC_PRETICK_IPC_CH_TO_NET,
				   BIT(CONFIG_SOC_NRF53_RTC_PRETICK_IPC_CH_TO_NET));
	nrf_ipc_send_config_set(NRF_IPC, CONFIG_SOC_NRF53_RTC_PRETICK_IPC_CH_FROM_NET,
				   BIT(CONFIG_SOC_NRF53_RTC_PRETICK_IPC_CH_FROM_NET));

	/* Allocate PPI channel for RTC Compare event publishers that starts WDT. */
	nrfx_err_t err = nrfx_gppi_channel_alloc(&ppi_ch);

	if (err != NRFX_SUCCESS) {
		return -ENOMEM;
	}

	/* Setup a PPI connection between RTC "pretick" events and IPC task. */
	if (IS_ENABLED(CONFIG_BT_LL_SOFTDEVICE)) {
		nrfx_gppi_event_endpoint_setup(ppi_ch, evt_mpsl_cc);
	}
	nrfx_gppi_event_endpoint_setup(ppi_ch, evt_cc);
	nrfx_gppi_event_endpoint_setup(ppi_ch, evt_overflow);
	nrfx_gppi_task_endpoint_setup(ppi_ch, task_ipc);
	nrfx_gppi_event_endpoint_setup(ppi_ch, evt_ipc);
	nrfx_gppi_task_endpoint_setup(ppi_ch, task_wdt);
	nrfx_gppi_channels_enable(BIT(ppi_ch));

	nrf_rtc_event_enable(NRF_RTC1, NRF_RTC_CHANNEL_INT_MASK(RTC1_PRETICK_CC_CHAN));
	nrf_rtc_event_enable(NRF_RTC1, NRF_RTC_CHANNEL_INT_MASK(RTC1_PRETICK_OVERFLOW_CHAN));

	nrf_rtc_event_clear(NRF_RTC1, NRF_RTC_CHANNEL_EVENT_ADDR(RTC1_PRETICK_CC_CHAN));
	nrf_rtc_event_clear(NRF_RTC1, NRF_RTC_CHANNEL_EVENT_ADDR(RTC1_PRETICK_OVERFLOW_CHAN));
	/* Set event 1 tick before overflow. */
	nrf_rtc_cc_set(NRF_RTC1, RTC1_PRETICK_OVERFLOW_CHAN, 0x00FFFFFF);

	return 0;
}
#endif /* CONFIG_SOC_NRF5340_CPUNET */

static int rtc_pretick_init(void)
{
	ARG_UNUSED(unused);
#ifdef CONFIG_SOC_NRF5340_CPUAPP
	return rtc_pretick_cpuapp_init();
#else
	return rtc_pretick_cpunet_init();
#endif
}
#endif /* CONFIG_SOC_NRF53_RTC_PRETICK */


static int nordicsemi_nrf53_init(void)
{
#if defined(CONFIG_SOC_NRF5340_CPUAPP) && defined(CONFIG_NRF_ENABLE_CACHE)
#if !defined(CONFIG_BUILD_WITH_TFM)
	/* Enable the instruction & data cache.
	 * This can only be done from secure code.
	 * This is handled by the TF-M platform so we skip it when TF-M is
	 * enabled.
	 */
	nrf_cache_enable(NRF_CACHE);
#endif
#elif defined(CONFIG_SOC_NRF5340_CPUNET) && defined(CONFIG_NRF_ENABLE_CACHE)
	nrf_nvmc_icache_config_set(NRF_NVMC, NRF_NVMC_ICACHE_ENABLE);
#endif

#if defined(CONFIG_SOC_ENABLE_LFXO)
	nrf_oscillators_lfxo_cap_set(NRF_OSCILLATORS,
		IS_ENABLED(CONFIG_SOC_LFXO_CAP_INT_6PF) ?
			NRF_OSCILLATORS_LFXO_CAP_6PF :
		IS_ENABLED(CONFIG_SOC_LFXO_CAP_INT_7PF) ?
			NRF_OSCILLATORS_LFXO_CAP_7PF :
		IS_ENABLED(CONFIG_SOC_LFXO_CAP_INT_9PF) ?
			NRF_OSCILLATORS_LFXO_CAP_9PF :
			NRF_OSCILLATORS_LFXO_CAP_EXTERNAL);
#if !defined(CONFIG_BUILD_WITH_TFM)
	/* This can only be done from secure code.
	 * This is handled by the TF-M platform so we skip it when TF-M is
	 * enabled.
	 */
	nrf_gpio_pin_control_select(PIN_XL1, NRF_GPIO_PIN_SEL_PERIPHERAL);
	nrf_gpio_pin_control_select(PIN_XL2, NRF_GPIO_PIN_SEL_PERIPHERAL);
#endif /* !defined(CONFIG_BUILD_WITH_TFM) */
#endif /* defined(CONFIG_SOC_ENABLE_LFXO) */
#if defined(CONFIG_SOC_HFXO_CAP_INTERNAL)
	/* This register is only accessible from secure code. */
	uint32_t xosc32mtrim = soc_secure_read_xosc32mtrim();
	/* The SLOPE field is in the two's complement form, hence this special
	 * handling. Ideally, it would result in just one SBFX instruction for
	 * extracting the slope value, at least gcc is capable of producing such
	 * output, but since the compiler apparently tries first to optimize
	 * additions and subtractions, it generates slightly less than optimal
	 * code.
	 */
	uint32_t slope_field = (xosc32mtrim & FICR_XOSC32MTRIM_SLOPE_Msk)
			       >> FICR_XOSC32MTRIM_SLOPE_Pos;
	uint32_t slope_mask = FICR_XOSC32MTRIM_SLOPE_Msk
			      >> FICR_XOSC32MTRIM_SLOPE_Pos;
	uint32_t slope_sign = (slope_mask - (slope_mask >> 1));
	int32_t slope = (int32_t)(slope_field ^ slope_sign) - (int32_t)slope_sign;
	uint32_t offset = (xosc32mtrim & FICR_XOSC32MTRIM_OFFSET_Msk)
			  >> FICR_XOSC32MTRIM_OFFSET_Pos;
	/* As specified in the nRF5340 PS:
	 * CAPVALUE = (((FICR->XOSC32MTRIM.SLOPE+56)*(CAPACITANCE*2-14))
	 *            +((FICR->XOSC32MTRIM.OFFSET-8)<<4)+32)>>6;
	 * where CAPACITANCE is the desired capacitor value in pF, holding any
	 * value between 7.0 pF and 20.0 pF in 0.5 pF steps.
	 */
	uint32_t capvalue =
		((slope + 56) * (CONFIG_SOC_HFXO_CAP_INT_VALUE_X2 - 14)
		 + ((offset - 8) << 4) + 32) >> 6;

	nrf_oscillators_hfxo_cap_set(NRF_OSCILLATORS, true, capvalue);
#elif defined(CONFIG_SOC_HFXO_CAP_EXTERNAL)
	nrf_oscillators_hfxo_cap_set(NRF_OSCILLATORS, false, 0);
#endif

#if defined(CONFIG_SOC_DCDC_NRF53X_APP)
	nrf_regulators_dcdcen_set(NRF_REGULATORS, true);
#endif
#if defined(CONFIG_SOC_DCDC_NRF53X_NET)
	nrf_regulators_dcdcen_radio_set(NRF_REGULATORS, true);
#endif
#if defined(CONFIG_SOC_DCDC_NRF53X_HV)
	nrf_regulators_dcdcen_vddh_set(NRF_REGULATORS, true);
#endif

#if defined(CONFIG_SOC_NRF_GPIO_FORWARDER_FOR_NRF5340)
	static const uint8_t forwarded_psels[] = {
		DT_FOREACH_STATUS_OKAY(nordic_nrf_gpio_forwarder, ALL_GPIOS_IN_FORWARDER)
	};

	for (int i = 0; i < ARRAY_SIZE(forwarded_psels); i++) {
		soc_secure_gpio_pin_mcu_select(forwarded_psels[i], NRF_GPIO_PIN_SEL_NETWORK);
	}

#endif

#if defined(CONFIG_PM_S2RAM)
	enable_ram_retention();
#endif /* CONFIG_PM_S2RAM */

	return 0;
}

void arch_busy_wait(uint32_t time_us)
{
	nrfx_coredep_delay_us(time_us);
}

SYS_INIT(nordicsemi_nrf53_init, PRE_KERNEL_1, 0);

#ifdef CONFIG_SOC_NRF53_RTC_PRETICK
SYS_INIT(rtc_pretick_init, POST_KERNEL, 0);
#endif
