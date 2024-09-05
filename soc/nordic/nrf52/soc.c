/*
 * Copyright (c) 2016 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief System/hardware module for Nordic Semiconductor nRF52 family processor
 *
 * This module provides routines to initialize and support board-level hardware
 * for the Nordic Semiconductor nRF52 family processor.
 */

#include <zephyr/devicetree.h>
#include <zephyr/dt-bindings/regulator/nrf5x.h>
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <hal/nrf_power.h>
#include <soc/nrfx_coredep.h>
#include <zephyr/logging/log.h>

#include <cmsis_core.h>

#define LOG_LEVEL CONFIG_SOC_LOG_LEVEL
LOG_MODULE_REGISTER(soc);

static int nordicsemi_nrf52_init(void)
{
#ifdef CONFIG_NRF_ENABLE_ICACHE
	/* Enable the instruction cache */
	NRF_NVMC->ICACHECNF = NVMC_ICACHECNF_CACHEEN_Msk;
#endif

#if defined(CONFIG_SOC_DCDC_NRF52X) || (DT_PROP(DT_INST(0, nordic_nrf5x_regulator),                \
						regulator_initial_mode) == NRF5X_REG_MODE_DCDC)
	nrf_power_dcdcen_set(NRF_POWER, true);
#endif
#if NRF_POWER_HAS_DCDCEN_VDDH && (defined(CONFIG_SOC_DCDC_NRF52X_HV) || \
	DT_NODE_HAS_STATUS(DT_INST(0, nordic_nrf52x_regulator_hv), okay))
	nrf_power_dcdcen_vddh_set(NRF_POWER, true);
#endif

	return 0;
}

void arch_busy_wait(uint32_t time_us)
{
	nrfx_coredep_delay_us(time_us);
}

SYS_INIT(nordicsemi_nrf52_init, PRE_KERNEL_1, 0);
