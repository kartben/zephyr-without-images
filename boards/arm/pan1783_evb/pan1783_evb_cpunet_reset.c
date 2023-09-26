/*
 * Copyright (c) 2023 Panasonic Industrial Devices Europe GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/logging/log.h>

#include <soc.h>
#include <hal/nrf_reset.h>

LOG_MODULE_REGISTER(pan1783_evb_cpuapp, CONFIG_LOG_DEFAULT_LEVEL);

#if defined(CONFIG_BT_CTLR_DEBUG_PINS_CPUAPP)
#include <../subsys/bluetooth/controller/ll_sw/nordic/hal/nrf5/debug.h>
#else
#define DEBUG_SETUP()
#endif

static void remoteproc_mgr_config(void)
{
	/* Route Bluetooth Controller Debug Pins */
	DEBUG_SETUP();

	/* Retain nRF5340 Network MCU */
	NRF_SPU->EXTDOMAIN[0].PERM = 1 << 4;
}

static int remoteproc_mgr_boot(void)
{
	/* Configure permissions for the Network MCU. */
	remoteproc_mgr_config();

	/* Release the Network MCU, 'Release force off signal' */
	nrf_reset_network_force_off(NRF_RESET, false);

	LOG_DBG("Network MCU released.");

	return 0;
}

SYS_INIT(remoteproc_mgr_boot, POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEVICE);
