/*
 * Copyright (c) 2020, Laird Connectivity
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT honeywell_sm351lt

#include "sm351lt.h"

#include <init.h>
#include <sys/byteorder.h>
#include <logging/log.h>
#include <stdio.h>
#include <sys/util.h>
#include <drivers/gpio.h>
#include <drivers/sensor.h>
#include <string.h>

LOG_MODULE_REGISTER(SM351LT, CONFIG_SENSOR_LOG_LEVEL);

#if CONFIG_SM351LT_TRIGGER
static int sm351lt_trigger_set(const struct device *dev,
			       const struct sensor_trigger *trig,
			       sensor_trigger_handler_t handler)
{
	const struct sm351lt_config *const config = dev->config;
	struct sm351lt_data *data = dev->data;
	int ret = -ENOTSUP;

	if (trig->chan == SENSOR_CHAN_PROX) {
		data->changed_handler = handler;
		ret = gpio_pin_interrupt_configure(data->bus, config->gpio_pin,
						   (handler ? data->trigger_type
							    : GPIO_INT_DISABLE));

		if (ret < 0) {
			return ret;
		}

		if (handler) {
			ret = gpio_add_callback(data->bus, &data->gpio_cb);
		} else {
			ret = gpio_remove_callback(data->bus, &data->gpio_cb);
		}
	}

	return ret;
}

static void sm351lt_gpio_callback(const struct device *dev,
				  struct gpio_callback *cb, uint32_t pins)
{
	struct sm351lt_data *data =
		CONTAINER_OF(cb, struct sm351lt_data, gpio_cb);

#if defined(CONFIG_SM351LT_TRIGGER_OWN_THREAD)
	k_sem_give(&data->gpio_sem);
#elif defined(CONFIG_SM351LT_TRIGGER_GLOBAL_THREAD)
	k_work_submit(&data->work);
#endif
}

static void sm351lt_thread_cb(void *arg)
{
	const struct device *dev = arg;
	struct sm351lt_data *data = dev->data;

	struct sensor_trigger mag_trigger = {
		.type = SENSOR_TRIG_NEAR_FAR,
		.chan = SENSOR_CHAN_PROX,
	};

	if (likely(data->changed_handler != NULL)) {
		data->changed_handler(dev, &mag_trigger);
	}

	return;
}

#if defined(CONFIG_SM351LT_TRIGGER_OWN_THREAD)
static void sm351lt_thread(void *arg1, void *unused2, void *unused3)
{
	const struct device *dev = arg1;
	struct sm351lt_data *data = dev->data;

	ARG_UNUSED(unused2);
	ARG_UNUSED(unused3);

	while (1) {
		k_sem_take(&data->gpio_sem, K_FOREVER);
		sm351lt_thread_cb(dev);
	}
}
#endif

#if defined(CONFIG_SM351LT_TRIGGER_GLOBAL_THREAD)
static void sm351lt_work_cb(struct k_work *work)
{
	struct sm351lt_data *data =
		CONTAINER_OF(work, struct sm351lt_data, work);

	sm351lt_thread_cb(data->dev);
}
#endif
#endif

static int sm351lt_sample_fetch(const struct device *dev,
				enum sensor_channel chan)
{
	const struct sm351lt_config *config = dev->config;
	struct sm351lt_data *data = dev->data;

	if (chan != SENSOR_CHAN_ALL && chan != SENSOR_CHAN_PROX) {
		return -ENOTSUP;
	}

	data->sample_status = gpio_pin_get(data->bus, config->gpio_pin);

	return 0;
}

static int sm351lt_channel_get(const struct device *dev,
			       enum sensor_channel chan,
			       struct sensor_value *val)
{
	struct sm351lt_data *data = dev->data;

	if (chan == SENSOR_CHAN_PROX) {
		val->val1 = data->sample_status;
		val->val2 = 0;
	} else {
		return -ENOTSUP;
	}

	return 0;
}

#if CONFIG_SM351LT_TRIGGER
static int sm351lt_attr_set(const struct device *dev,
			    enum sensor_channel chan,
			    enum sensor_attribute attr,
			    const struct sensor_value *val)
{
	struct sm351lt_data *data = dev->data;

	if (chan == SENSOR_CHAN_PROX) {
		if (attr == SENSOR_ATTR_SM351LT_TRIGGER_TYPE) {
			/* Interrupt triggering type */
			data->trigger_type = val->val1;
		} else {
			return -ENOTSUP;
		}
	} else {
		return -ENOTSUP;
	}

	return 0;
}

static int sm351lt_attr_get(const struct device *dev,
			    enum sensor_channel chan,
			    enum sensor_attribute attr,
			    struct sensor_value *val)
{
	struct sm351lt_data *data = dev->data;

	if (chan == SENSOR_CHAN_PROX) {
		if (attr == SENSOR_ATTR_SM351LT_TRIGGER_TYPE) {
			/* Interrupt triggering type */
			val->val1 = data->trigger_type;
			val->val2 = 0;
		} else {
			return -ENOTSUP;
		}
	} else {
		return -ENOTSUP;
	}

	return 0;
}
#endif

static const struct sensor_driver_api sm351lt_api_funcs = {
	.sample_fetch = sm351lt_sample_fetch,
	.channel_get = sm351lt_channel_get,
#if CONFIG_SM351LT_TRIGGER
	.attr_set = sm351lt_attr_set,
	.attr_get = sm351lt_attr_get,
	.trigger_set = sm351lt_trigger_set,
#endif
};

static int sm351lt_init(const struct device *dev)
{
	const struct sm351lt_config *const config = dev->config;
	struct sm351lt_data *data = dev->data;
	uint32_t ret;

	data->bus = device_get_binding(config->bus_name);
	if (!data->bus) {
		LOG_ERR("gpio bus not found: %s", config->bus_name);
		return -ENODEV;
	}

	ret = gpio_pin_configure(data->bus, config->gpio_pin,
				 (config->gpio_flags | GPIO_INPUT));
	if (ret) {
		LOG_ERR("failed to configure gpio: %d", ret);
		return ret;
	}

#if defined(CONFIG_SM351LT_TRIGGER)
#if defined(CONFIG_SM351LT_TRIGGER_OWN_THREAD)
	k_sem_init(&data->gpio_sem, 0, UINT_MAX);

	k_thread_create(&data->thread, data->thread_stack,
			CONFIG_SM351LT_THREAD_STACK_SIZE,
			(k_thread_entry_t)sm351lt_thread, dev, NULL,
			NULL, K_PRIO_COOP(CONFIG_SM351LT_THREAD_PRIORITY),
			0, K_NO_WAIT);

#if defined(CONFIG_THREAD_NAME) && defined(CONFIG_THREAD_MAX_NAME_LEN)
	/* Sets up thread name as the device name */
	k_thread_name_set(&data->thread, dev->name);
#endif

#elif defined(CONFIG_SM351LT_TRIGGER_GLOBAL_THREAD)
	data->work.handler = sm351lt_work_cb;
	data->dev = dev;
#endif

	data->trigger_type = GPIO_INT_DISABLE;

	ret = gpio_pin_interrupt_configure(data->bus, config->gpio_pin,
					   GPIO_INT_DISABLE);
	if (ret) {
		LOG_ERR("failed to configure gpio interrupt: %d", ret);
		return ret;
	}

	/* Setup callback struct but do not add it yet */
	gpio_init_callback(&data->gpio_cb, sm351lt_gpio_callback,
			   BIT(config->gpio_pin));
#endif

	return 0;
}

/* Instantiation macros for each individual device. */
#define SM351LT_DEFINE(inst)					     \
	static struct sm351lt_data sm351lt_data_##inst;		     \
	static const struct sm351lt_config sm351lt_config_##inst = { \
		.bus_name =   DT_INST_GPIO_LABEL(inst, gpios),	     \
		.gpio_pin =   DT_INST_GPIO_PIN(inst, gpios),	     \
		.gpio_flags = DT_INST_GPIO_FLAGS(inst, gpios),	     \
	};							     \
								     \
	DEVICE_AND_API_INIT(sm351lt_##inst,			     \
			    DT_INST_LABEL(inst),		     \
			    sm351lt_init,			     \
			    &sm351lt_data_##inst,		     \
			    &sm351lt_config_##inst,		     \
			    POST_KERNEL,			     \
			    CONFIG_SENSOR_INIT_PRIORITY,	     \
			    &sm351lt_api_funcs);


/* Main instantiation macro for every configured device in DTS. */
DT_INST_FOREACH_STATUS_OKAY(SM351LT_DEFINE)
