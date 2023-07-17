/*
 * Copyright (c) 2022 Espressif Systems (Shanghai) Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/pm/pm.h>
#include <esp_sleep.h>
#include <soc/rtc_io_channel.h>
#include <hal/rtc_io_hal.h>

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(soc, CONFIG_SOC_LOG_LEVEL);

static uint32_t intenable;

/* Invoke Low Power/System Off specific Tasks */
void pm_state_set(enum pm_state state, uint8_t substate_id)
{
	ARG_UNUSED(substate_id);

	switch (state) {
	case PM_STATE_SOFT_OFF:
		/*
		 * Isolate GPIO12 pin from external circuits. This is needed for modules
		 * which have an external pull-up resistor on GPIO12 (such as ESP32-WROVER)
		 * to minimize current consumption.
		 */
		rtcio_hal_isolate(RTCIO_GPIO12_CHANNEL);
		/* Forces RTC domain to be always on */
		esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);
		esp_deep_sleep_start();
		break;
	case PM_STATE_STANDBY:
		intenable = XTENSA_RSR("INTENABLE");
		__asm__ volatile ("waiti 0");
		break;
	default:
		LOG_DBG("Unsupported power state %u", state);
		break;
	}
}

/* Handle SOC specific activity after Low Power Mode Exit */
void pm_state_exit_post_ops(enum pm_state state, uint8_t substate_id)
{
	ARG_UNUSED(substate_id);

	switch (state) {
	case PM_STATE_SOFT_OFF:
		/* Nothing to do. */
		break;
	case PM_STATE_STANDBY:
		z_xt_ints_on(intenable);
		esp_light_sleep_start();
		break;
	default:
		LOG_DBG("Unsupported power state %u", state);
		break;
	}
}
