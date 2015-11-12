/*
 * Copyright (c) 2015 Intel Corporation
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

#include <device.h>
#include <init.h>
#include "board.h"

#if CONFIG_IPM_QUARK_SE
#include <ipm.h>
#include <ipm/ipm_quark_se.h>

IRQ_CONNECT_STATIC(quark_se_ipm, QUARK_SE_IPM_INTERRUPT,
		   QUARK_SE_IPM_INTERRUPT_PRI, quark_se_ipm_isr, NULL, 0);

static int arc_quark_se_ipm_init(void)
{
	IRQ_CONFIG(quark_se_ipm, QUARK_SE_IPM_INTERRUPT);
	irq_enable(QUARK_SE_IPM_INTERRUPT);
	return DEV_OK;
}

static struct quark_se_ipm_controller_config_info ipm_controller_config = {
	.controller_init = arc_quark_se_ipm_init
};
DECLARE_DEVICE_INIT_CONFIG(quark_se_ipm, "", quark_se_ipm_controller_initialize,
			   &ipm_controller_config);
SYS_DEFINE_DEVICE(quark_se_ipm, NULL, SECONDARY,
					CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);

#if CONFIG_IPM_CONSOLE_SENDER
#include <console/ipm_console.h>
QUARK_SE_IPM_DEFINE(quark_se_ipm4, 4, QUARK_SE_IPM_OUTBOUND);

struct ipm_console_sender_config_info quark_se_ipm_sender_config = {
	.bind_to = "quark_se_ipm4",
	.flags = IPM_CONSOLE_PRINTK | IPM_CONSOLE_STDOUT,
};
DECLARE_DEVICE_INIT_CONFIG(ipm_console, "ipm_console",
			   ipm_console_sender_init,
			   &quark_se_ipm_sender_config);
SYS_DEFINE_DEVICE(ipm_console, NULL, SECONDARY, CONFIG_IPM_CONSOLE_PRIORITY);

#endif /* CONFIG_IPM_CONSOLE_SENDER */
#endif /* CONFIG_IPM_QUARK_SE */
