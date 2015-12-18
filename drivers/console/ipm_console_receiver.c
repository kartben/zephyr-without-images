/* ipm_console.c - Console messages to/from another processor */

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

#include <nanokernel.h>
#include <misc/ring_buffer.h>
#include <misc/printk.h>
#include <stdio.h>
#include <ipm.h>
#include <console/ipm_console.h>

static void ipm_console_fiber(int arg1, int arg2)
{
	uint8_t size32;
	uint16_t type;
	int ret;
	struct device *d;
	struct ipm_console_receiver_config_info *config_info;
	struct ipm_console_receiver_runtime_data *driver_data;
	int pos;

	d = (struct device *)arg1;
	driver_data = d->driver_data;
	config_info = d->config->config_info;
	ARG_UNUSED(arg2);
	size32 = 0;
	pos = 0;

	while (1) {
		nano_fiber_sem_take_wait(&driver_data->sem);

		ret = sys_ring_buf_get(&driver_data->rb, &type,
				       (uint8_t *)&config_info->line_buf[pos],
				       NULL, &size32);
		if (ret) {
			/* Shouldn't ever happen... */
			printk("ipm console ring buffer error: %d\n", ret);
			size32 = 0;
			continue;
		}

		if (config_info->line_buf[pos] == '\n' ||
		    pos == config_info->lb_size - 2) {
			if (pos != config_info->lb_size - 2) {
				config_info->line_buf[pos] = '\0';
			} else {
				config_info->line_buf[pos + 1] = '\0';
			}
			if (config_info->flags & IPM_CONSOLE_PRINTK) {
				printk("\n%s: '%s'", d->config->name,
				       config_info->line_buf);
			}
			if (config_info->flags & IPM_CONSOLE_STDOUT) {
				printf("\n%s: '%s'", d->config->name,
				       config_info->line_buf);
			}
			pos = 0;
		} else {
			++pos;
		}
	}
}

static void ipm_console_receive_callback(void *context, uint32_t id,
					 volatile void *data)
{
	struct device *d;
	struct ipm_console_receiver_runtime_data *driver_data;

	ARG_UNUSED(data);
	d = context;
	driver_data = d->driver_data;
	if (!sys_ring_buf_put(&driver_data->rb, 0, id, NULL, 0)) {
		nano_isr_sem_give(&driver_data->sem);
	}
}


int ipm_console_receiver_init(struct device *d)
{
	struct ipm_console_receiver_config_info *config_info =
		d->config->config_info;
	struct ipm_console_receiver_runtime_data *driver_data = d->driver_data;
	struct device *ipm;

	ipm = device_get_binding(config_info->bind_to);

	if (!ipm) {
		printk("unable to bind IPM console receiver to '%s'\n",
		       __func__, config_info->bind_to);
		return DEV_INVALID_CONF;
	}

	if (ipm_max_id_val_get(ipm) < 0xFF) {
		printk("IPM driver %s doesn't support 8-bit id values",
		       config_info->bind_to);
		return DEV_INVALID_CONF;
	}

	nano_sem_init(&driver_data->sem);
	sys_ring_buf_init(&driver_data->rb, config_info->rb_size32,
			  config_info->ring_buf_data);

	ipm_register_callback(ipm, ipm_console_receive_callback, d);

	task_fiber_start(config_info->fiber_stack, IPM_CONSOLE_STACK_SIZE,
			 ipm_console_fiber, (int)d, 0,
			 IPM_CONSOLE_PRI, 0);
	ipm_set_enabled(ipm, 1);

	return DEV_OK;
}

