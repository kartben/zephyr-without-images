/*
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <counter.h>
#include <nrfx_timer.h>

#define LOG_LEVEL CONFIG_COUNTER_LOG_LEVEL
#define LOG_MODULE_NAME counter_timer
#include <logging/log.h>
LOG_MODULE_REGISTER();

#define TIMER_CLOCK 16000000

#define CC_TO_ID(cc_num) (cc_num - 2)

#define ID_TO_CC(idx) (nrf_timer_cc_channel_t)(idx + 2)

#define COUNTER_EVENT_TO_ID(evt) \
	(evt - NRF_TIMER_EVENT_COMPARE2)/sizeof(u32_t)

#define WRAP_CH NRF_TIMER_CC_CHANNEL0
#define COUNTER_WRAP_INT NRF_TIMER_EVENT_COMPARE0
#define COUNTER_OVERFLOW_SHORT NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK
#define COUNTER_READ_CC NRF_TIMER_CC_CHANNEL1

struct counter_nrfx_data {
	counter_wrap_callback_t wrap_cb;
	void *wrap_user_data;
};

struct counter_nrfx_config {
	struct counter_config_info info;
	const struct counter_alarm_cfg **alarm_cfgs;
	nrfx_timer_t timer;

	LOG_INSTANCE_PTR_DECLARE(log);
};

static inline struct counter_nrfx_data *get_dev_data(struct device *dev)
{
	return dev->driver_data;
}

static inline const struct counter_nrfx_config *get_nrfx_config(
							struct device *dev)
{
	return CONTAINER_OF(dev->config->config_info,
				struct counter_nrfx_config, info);
}

static int counter_nrfx_start(struct device *dev)
{
	nrfx_timer_enable(&get_nrfx_config(dev)->timer);

	return 0;
}

static int counter_nrfx_stop(struct device *dev)
{
	nrfx_timer_disable(&get_nrfx_config(dev)->timer);

	return 0;
}

static u32_t counter_nrfx_read(struct device *dev)
{
	return nrfx_timer_capture(&get_nrfx_config(dev)->timer,
				  COUNTER_READ_CC);
}

static int counter_nrfx_set_alarm(struct device *dev,
				  const struct counter_alarm_cfg *alarm_cfg)
{
	const struct counter_nrfx_config *nrfx_config = get_nrfx_config(dev);
	const nrfx_timer_t *timer = &nrfx_config->timer;
	u32_t cc_val;

	if (alarm_cfg->ticks > nrfx_timer_capture_get(timer, WRAP_CH)) {
		return -EINVAL;
	}

	if (nrfx_config->alarm_cfgs[alarm_cfg->channel_id]) {
		return -EBUSY;
	}

	cc_val = alarm_cfg->ticks + (alarm_cfg->absolute ?
				0 : nrfx_timer_capture(timer, COUNTER_READ_CC));
	nrfx_config->alarm_cfgs[alarm_cfg->channel_id] = alarm_cfg;

	nrfx_timer_compare(timer, ID_TO_CC(alarm_cfg->channel_id),
			   cc_val, true);

	return 0;
}

static void _disable(struct device *dev, u8_t id)
{
	const struct counter_nrfx_config *config = get_nrfx_config(dev);

	nrfx_timer_compare_int_disable(&config->timer, ID_TO_CC(id));
	config->alarm_cfgs[id] = NULL;
}

static int counter_nrfx_disable_alarm(struct device *dev,
				      const struct counter_alarm_cfg *alarm_cfg)
{
	_disable(dev, alarm_cfg->channel_id);

	return 0;
}

static int counter_nrfx_set_wrap(struct device *dev, u32_t ticks,
				 counter_wrap_callback_t callback,
				 void *user_data)
{
	const struct counter_nrfx_config *nrfx_config = get_nrfx_config(dev);
	const nrfx_timer_t *timer = &nrfx_config->timer;
	struct counter_nrfx_data *data = get_dev_data(dev);

	for (int i = 0; i < counter_get_num_of_channels(dev); i++) {
		/* Overflow can be changed only when all alarms are
		 * disables.
		 */
		if (nrfx_config->alarm_cfgs[i]) {
			return -EBUSY;
		}
	}

	nrfx_timer_compare_int_disable(timer, WRAP_CH);
	nrfx_timer_clear(timer);

	data->wrap_cb = callback;
	data->wrap_user_data = user_data;
	nrfx_timer_extended_compare(timer, WRAP_CH,
				    ticks, COUNTER_OVERFLOW_SHORT,
				    callback ? true : false);

	return 0;
}

static u32_t counter_nrfx_get_pending_int(struct device *dev)
{
	return 0;
}

static void alarm_event_handler(struct device *dev, u32_t id)
{
	const nrfx_timer_t *timer = &get_nrfx_config(dev)->timer;
	const struct counter_alarm_cfg *alarm_cfg =
				get_nrfx_config(dev)->alarm_cfgs[id];
	u32_t cc_val;

	if (!alarm_cfg->handler) {
		return;
	}

	cc_val = nrfx_timer_capture_get(timer, ID_TO_CC(id));
	_disable(dev, id);
	alarm_cfg->handler(dev, alarm_cfg, cc_val);
}

static void event_handler(nrf_timer_event_t event_type, void *p_context)
{
	struct device *dev = p_context;
	struct counter_nrfx_data *dev_data = get_dev_data(dev);

	if (event_type == COUNTER_WRAP_INT) {
		if (dev_data->wrap_cb) {
			dev_data->wrap_cb(dev, dev_data->wrap_user_data);
		}
	} else if (event_type > NRF_TIMER_EVENT_COMPARE1) {
		alarm_event_handler(dev, COUNTER_EVENT_TO_ID(event_type));

	}
}

static int init_timer(struct device *dev, const nrfx_timer_config_t *config)
{
	const struct counter_nrfx_config *nrfx_config = get_nrfx_config(dev);
	const nrfx_timer_t *timer = &nrfx_config->timer;

	nrfx_err_t result = nrfx_timer_init(timer, config, event_handler);

	if (result != NRFX_SUCCESS) {
		LOG_INST_ERR(nrfx_config->log, "Failed to initialize device.");
		return -EBUSY;
	}

	nrfx_timer_compare(timer, WRAP_CH, UINT32_MAX, false);

	LOG_INST_DBG(nrfx_config->log, "Initialized");

	return 0;
}

static u32_t counter_nrfx_get_wrap(struct device *dev)
{
	return nrfx_timer_capture_get(&get_nrfx_config(dev)->timer, WRAP_CH);
}

static u32_t counter_nrfx_get_max_relative_alarm(struct device *dev)
{
	return nrfx_timer_capture_get(&get_nrfx_config(dev)->timer, WRAP_CH);
}

static const struct counter_driver_api counter_nrfx_driver_api = {
	.start = counter_nrfx_start,
	.stop = counter_nrfx_stop,
	.read = counter_nrfx_read,
	.set_alarm = counter_nrfx_set_alarm,
	.disable_alarm = counter_nrfx_disable_alarm,
	.set_wrap = counter_nrfx_set_wrap,
	.get_pending_int = counter_nrfx_get_pending_int,
	.get_wrap = counter_nrfx_get_wrap,
	.get_max_relative_alarm = counter_nrfx_get_max_relative_alarm,
};

#define COUNTER_NRFX_TIMER_DEVICE(idx)					       \
	static int counter_##idx##_init(struct device *dev)		       \
	{								       \
		IRQ_CONNECT(NRFX_IRQ_NUMBER_GET(NRF_TIMER##idx),	       \
			    CONFIG_COUNTER_TIMER##idx##_IRQ_PRI,	       \
			    nrfx_isr, nrfx_timer_##idx##_irq_handler, 0);      \
		const nrfx_timer_config_t config = {			       \
			.frequency = CONFIG_COUNTER_TIMER##idx##_PRESCALER,    \
			.mode      = NRF_TIMER_MODE_TIMER,		       \
			.bit_width = (TIMER##idx##_MAX_SIZE == 32) ?	       \
					NRF_TIMER_BIT_WIDTH_32 :	       \
					NRF_TIMER_BIT_WIDTH_16,		       \
			.p_context = dev				       \
		};							       \
		return init_timer(dev, &config);			       \
	}								       \
	static struct counter_nrfx_data counter_##idx##_data;		       \
	static const struct counter_alarm_cfg				       \
		*counter##idx##_alarm_cfgs[CC_TO_ID(TIMER##idx##_CC_NUM)];     \
	LOG_INSTANCE_REGISTER(LOG_MODULE_NAME, idx, CONFIG_COUNTER_LOG_LEVEL); \
	static const struct counter_nrfx_config nrfx_counter_##idx##_config = {\
		.info = {						       \
			.max_wrap = (TIMER##idx##_MAX_SIZE == 32) ?	       \
					0xffffffff : 0x0000ffff,	       \
			.freq = TIMER_CLOCK /				       \
				(1 << CONFIG_COUNTER_TIMER##idx##_PRESCALER),  \
			.count_up = true,				       \
			.channels = CC_TO_ID(TIMER##idx##_CC_NUM),	       \
		},							       \
		.alarm_cfgs = counter##idx##_alarm_cfgs,		       \
		.timer = NRFX_TIMER_INSTANCE(idx),			       \
		LOG_INSTANCE_PTR_INIT(log, LOG_MODULE_NAME, idx)	       \
	};								       \
	DEVICE_AND_API_INIT(timer_##idx, CONFIG_COUNTER_##idx##_NAME,	       \
			    counter_##idx##_init,			       \
			    &counter_##idx##_data,			       \
			    &nrfx_counter_##idx##_config.info,		       \
			    PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEVICE,  \
			    &counter_nrfx_driver_api)

#ifdef CONFIG_COUNTER_TIMER0
COUNTER_NRFX_TIMER_DEVICE(0);
#endif

#ifdef CONFIG_COUNTER_TIMER1
COUNTER_NRFX_TIMER_DEVICE(1);
#endif

#ifdef CONFIG_COUNTER_TIMER2
COUNTER_NRFX_TIMER_DEVICE(2);
#endif

#ifdef CONFIG_COUNTER_TIMER3
COUNTER_NRFX_TIMER_DEVICE(3);
#endif

#ifdef CONFIG_COUNTER_TIMER4
COUNTER_NRFX_TIMER_DEVICE(4);
#endif
