/*
 * Copyright (c) 2021 Fabio Baltieri
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr.h>
#include <pm/pm.h>
#include <soc.h>
#include <init.h>

#include <stm32l0xx_ll_utils.h>
#include <stm32l0xx_ll_bus.h>
#include <stm32l0xx_ll_cortex.h>
#include <stm32l0xx_ll_pwr.h>
#include <stm32l0xx_ll_rcc.h>
#include <stm32l0xx_ll_system.h>
#include <clock_control/clock_stm32_ll_common.h>

#include <logging/log.h>
LOG_MODULE_DECLARE(soc, CONFIG_SOC_LOG_LEVEL);

/* Select MSI as wake-up system clock if configured, HSI otherwise */
#if STM32_SYSCLK_SRC_MSI
#define RCC_STOP_WAKEUPCLOCK_SELECTED LL_RCC_STOP_WAKEUPCLOCK_MSI
#else
#define RCC_STOP_WAKEUPCLOCK_SELECTED LL_RCC_STOP_WAKEUPCLOCK_HSI
#endif

/* Invoke Low Power/System Off specific Tasks */
void pm_power_state_set(struct pm_state_info info)
{
	switch (info.state) {
	case PM_STATE_SUSPEND_TO_IDLE:
		LL_RCC_SetClkAfterWakeFromStop(RCC_STOP_WAKEUPCLOCK_SELECTED);
		LL_PWR_ClearFlag_WU();
		LL_PWR_SetPowerMode(LL_PWR_MODE_STOP);
		LL_PWR_SetRegulModeLP(LL_PWR_REGU_LPMODES_LOW_POWER);
		LL_LPM_EnableDeepSleep();
		k_cpu_idle();
		break;
	case PM_STATE_SOFT_OFF:
		LL_PWR_ClearFlag_WU();
		LL_PWR_SetPowerMode(LL_PWR_MODE_STANDBY);
		LL_LPM_EnableDeepSleep();
		k_cpu_idle();
		break;
	default:
		LOG_DBG("Unsupported power state %u", info.state);
		break;
	}
}

/* Handle SOC specific activity after Low Power Mode Exit */
void pm_power_state_exit_post_ops(struct pm_state_info info)
{
	switch (info.state) {
	case PM_STATE_SUSPEND_TO_IDLE:
		LL_LPM_DisableSleepOnExit();
		LL_LPM_EnableSleep();

		/* Restore the clock setup. */
		stm32_clock_control_init(NULL);
		break;
	case PM_STATE_SOFT_OFF:
		/* Nothing to do. */
		break;
	default:
		LOG_DBG("Unsupported power substate-id %u", info.state);
		break;
	}

	/*
	 * System is now in active mode. Reenable interrupts which were
	 * disabled when OS started idling code.
	 */
	irq_unlock(0);
}

/* Initialize STM32 Power */
static int stm32_power_init(const struct device *dev)
{
	ARG_UNUSED(dev);

	/* Enable Power clock */
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

#ifdef CONFIG_DEBUG
	/* Enable the Debug Module during STOP mode */
	LL_DBGMCU_EnableDBGStopMode();
#endif /* CONFIG_DEBUG */

	return 0;
}

SYS_INIT(stm32_power_init, POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
