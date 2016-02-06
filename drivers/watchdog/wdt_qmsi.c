/*
 * Copyright (c) 2015 Intel Corporation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <init.h>
#include <device.h>
#include <watchdog.h>
#include <ioapic.h>

#include "qm_wdt.h"
#include "qm_scss.h"

static void (*user_cb)(struct device *dev);

static void interrupt_callback(void);

static void get_config(struct device *dev, struct wdt_config *cfg)
{
	qm_wdt_config_t qm_cfg;

	qm_wdt_get_config(QM_WDT_0, &qm_cfg);

	cfg->timeout = qm_cfg.timeout;
	cfg->mode = (qm_cfg.mode == QM_WDT_MODE_RESET) ?
			WDT_MODE_RESET : WDT_MODE_INTERRUPT_RESET;
	cfg->interrupt_fn = user_cb;
}

static int set_config(struct device *dev, struct wdt_config *cfg)
{
	qm_wdt_config_t qm_cfg;

	user_cb = cfg->interrupt_fn;

	qm_cfg.timeout = cfg->timeout;
	qm_cfg.mode = (cfg->mode == WDT_MODE_RESET) ?
			QM_WDT_MODE_RESET : QM_WDT_MODE_INTERRUPT_RESET;
	qm_cfg.callback = interrupt_callback;

	qm_wdt_set_config(QM_WDT_0, &qm_cfg);
	qm_wdt_start(QM_WDT_0);

	return DEV_OK;
}

static void reload(struct device *dev)
{
	qm_wdt_reload(QM_WDT_0);
}

static void enable(struct device *dev)
{
	clk_periph_enable(CLK_PERIPH_WDT_REGISTER);
}

static void disable(struct device *dev)
{
	clk_periph_disable(CLK_PERIPH_WDT_REGISTER);
}

static struct wdt_driver_api api = {
	.enable = enable,
	.disable = disable,
	.get_config = get_config,
	.set_config = set_config,
	.reload = reload,
};

void wdt_qmsi_isr(void *arg)
{
	qm_wdt_isr_0();
}

static int init(struct device *dev)
{
	IRQ_CONNECT(CONFIG_WDT_QMSI_IRQ, CONFIG_WDT_QMSI_IRQ_PRI,
		    wdt_qmsi_isr, 0, IOAPIC_EDGE | IOAPIC_HIGH);

	/* Unmask watchdog interrupt */
	irq_enable(CONFIG_WDT_QMSI_IRQ);

	/* Route watchdog interrupt to Lakemont */
	QM_SCSS_INT->int_watchdog_mask &= ~BIT(0);

	dev->driver_api = &api;
	return 0;
}

DEVICE_INIT(wdt, CONFIG_WDT_QMSI_DRV_NAME, init,
			0, 0,
			PRIMARY, CONFIG_KERNEL_INIT_PRIORITY_DEVICE);

/* Define 'struct device' variable which is passed to the ISR. Even if it
 * is not used by the ISR code, we require it in order to be able to pass
 * the device argument from the user callback (wdt_config->interrupt_fn).
 */
struct device *wdt_qmsi_isr_dev = DEVICE_GET(wdt);

static void interrupt_callback(void)
{
	if (user_cb)
		user_cb(wdt_qmsi_isr_dev);
}
