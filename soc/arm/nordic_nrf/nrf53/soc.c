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

#include <kernel.h>
#include <init.h>
#include <arch/arm/aarch32/cortex_m/cmsis.h>
#include <soc/nrfx_coredep.h>
#include <logging/log.h>
#include <nrf_erratas.h>
#if defined(CONFIG_SOC_NRF5340_CPUAPP)
#include <hal/nrf_cache.h>
#include <hal/nrf_oscillators.h>
#include <hal/nrf_regulators.h>
#elif defined(CONFIG_SOC_NRF5340_CPUNET)
#include <hal/nrf_nvmc.h>
#endif

#ifdef CONFIG_RUNTIME_NMI
extern void z_arm_nmi_init(void);
#define NMI_INIT() z_arm_nmi_init()
#else
#define NMI_INIT()
#endif

#if defined(CONFIG_SOC_NRF5340_CPUAPP)
#include <system_nrf5340_application.h>
#elif defined(CONFIG_SOC_NRF5340_CPUNET)
#include <system_nrf5340_network.h>
#else
#error "Unknown nRF53 SoC."
#endif

#define LOG_LEVEL CONFIG_SOC_LOG_LEVEL
LOG_MODULE_REGISTER(soc);

static int nordicsemi_nrf53_init(const struct device *arg)
{
	uint32_t key;

	ARG_UNUSED(arg);

	key = irq_lock();

#if defined(CONFIG_SOC_NRF5340_CPUAPP) && defined(CONFIG_NRF_ENABLE_CACHE)
	/* Enable the instruction & data cache */
	nrf_cache_enable(NRF_CACHE);
#elif defined(CONFIG_SOC_NRF5340_CPUNET) && defined(CONFIG_NRF_ENABLE_CACHE)
	nrf_nvmc_icache_config_set(NRF_NVMC, NRF_NVMC_ICACHE_ENABLE);
#endif

#if defined(CONFIG_SOC_NRF5340_CPUAPP) && \
	!defined(CONFIG_TRUSTED_EXECUTION_NONSECURE)
	nrf_oscillators_lfxo_cap_set(NRF_OSCILLATORS,
				     NRF_OSCILLATORS_LFXO_CAP_6PF);
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

	/* Install default handler that simply resets the CPU
	 * if configured in the kernel, NOP otherwise
	 */
	NMI_INIT();

	irq_unlock(key);

	return 0;
}

void arch_busy_wait(uint32_t time_us)
{
	nrfx_coredep_delay_us(time_us);
}

void z_platform_init(void)
{
	SystemInit();
}

#if defined(CONFIG_SOC_NRF5340_CPUAPP) && \
	!defined(CONFIG_TRUSTED_EXECUTION_NONSECURE) && \
	!defined(CONFIG_NRF5340_CPUAPP_ERRATUM19)

static int check_erratum19(const struct device *arg)
{
	ARG_UNUSED(arg);
	if (nrf53_errata_19()) {
		LOG_ERR("This device is affected by nRF53 Erratum 19,");
		LOG_ERR("but workarounds have not been enabled.");
		LOG_ERR("See CONFIG_NRF5340_CPUAPP_ERRATUM19.");
		k_panic();
	}

	return 0;
}

SYS_INIT(check_erratum19, POST_KERNEL, CONFIG_APPLICATION_INIT_PRIORITY);
#endif

SYS_INIT(nordicsemi_nrf53_init, PRE_KERNEL_1, 0);
