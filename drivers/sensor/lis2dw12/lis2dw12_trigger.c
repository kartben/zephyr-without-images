/* ST Microelectronics LIS2DW12 3-axis accelerometer driver
 *
 * Copyright (c) 2019 STMicroelectronics
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Datasheet:
 * https://www.st.com/resource/en/datasheet/lis2dw12.pdf
 */

#define DT_DRV_COMPAT st_lis2dw12

#include <kernel.h>
#include <drivers/sensor.h>
#include <drivers/gpio.h>
#include <logging/log.h>

#include "lis2dw12.h"

LOG_MODULE_DECLARE(LIS2DW12, CONFIG_SENSOR_LOG_LEVEL);

/**
 * lis2dw12_enable_int - enable selected int pin to generate interrupt
 */
static int lis2dw12_enable_int(const struct device *dev,
			       enum sensor_trigger_type type, int enable)
{
	const struct lis2dw12_device_config *cfg = dev->config;
	struct lis2dw12_data *lis2dw12 = dev->data;
	lis2dw12_reg_t int_route;

	if (cfg->int_pin == 1U) {
		/* set interrupt for pin INT1 */
		lis2dw12_pin_int1_route_get(lis2dw12->ctx,
				&int_route.ctrl4_int1_pad_ctrl);

		switch (type) {
		case SENSOR_TRIG_DATA_READY:
			int_route.ctrl4_int1_pad_ctrl.int1_drdy = enable;
			break;
#ifdef CONFIG_LIS2DW12_TAP
		case SENSOR_TRIG_TAP:
			int_route.ctrl4_int1_pad_ctrl.int1_single_tap = enable;
			break;
		case SENSOR_TRIG_DOUBLE_TAP:
			int_route.ctrl4_int1_pad_ctrl.int1_tap = enable;
			break;
#endif /* CONFIG_LIS2DW12_TAP */
		default:
			LOG_ERR("Unsupported trigger interrupt route");
			return -ENOTSUP;
		}

		return lis2dw12_pin_int1_route_set(lis2dw12->ctx,
				&int_route.ctrl4_int1_pad_ctrl);
	} else {
		/* set interrupt for pin INT2 */
		lis2dw12_pin_int2_route_get(lis2dw12->ctx,
					    &int_route.ctrl5_int2_pad_ctrl);

		switch (type) {
		case SENSOR_TRIG_DATA_READY:
			int_route.ctrl5_int2_pad_ctrl.int2_drdy = enable;
			break;
		default:
			LOG_ERR("Unsupported trigger interrupt route");
			return -ENOTSUP;
		}

		return lis2dw12_pin_int2_route_set(lis2dw12->ctx,
				&int_route.ctrl5_int2_pad_ctrl);
	}
}

/**
 * lis2dw12_trigger_set - link external trigger to event data ready
 */
int lis2dw12_trigger_set(const struct device *dev,
			  const struct sensor_trigger *trig,
			  sensor_trigger_handler_t handler)
{
	const struct lis2dw12_device_config *cfg = dev->config;
	struct lis2dw12_data *lis2dw12 = dev->data;
	int16_t raw[3];
	int state = (handler != NULL) ? PROPERTY_ENABLE : PROPERTY_DISABLE;

	if (cfg->gpio_int.port == NULL) {
		LOG_ERR("trigger_set is not supported");
		return -ENOTSUP;
	}

	switch (trig->type) {
	case SENSOR_TRIG_DATA_READY:
		lis2dw12->drdy_handler = handler;
		if (state) {
			/* dummy read: re-trigger interrupt */
			lis2dw12_acceleration_raw_get(lis2dw12->ctx, raw);
		}
		return lis2dw12_enable_int(dev, SENSOR_TRIG_DATA_READY, state);
		break;
#ifdef CONFIG_LIS2DW12_TAP
	case SENSOR_TRIG_TAP:
		lis2dw12->tap_handler = handler;
		return lis2dw12_enable_int(dev, SENSOR_TRIG_TAP, state);
		break;
	case SENSOR_TRIG_DOUBLE_TAP:
		lis2dw12->double_tap_handler = handler;
		return lis2dw12_enable_int(dev, SENSOR_TRIG_DOUBLE_TAP, state);
		break;
#endif /* CONFIG_LIS2DW12_TAP */
	default:
		LOG_ERR("Unsupported sensor trigger");
		return -ENOTSUP;
	}
}

static int lis2dw12_handle_drdy_int(const struct device *dev)
{
	struct lis2dw12_data *data = dev->data;

	struct sensor_trigger drdy_trig = {
		.type = SENSOR_TRIG_DATA_READY,
		.chan = SENSOR_CHAN_ALL,
	};

	if (data->drdy_handler) {
		data->drdy_handler(dev, &drdy_trig);
	}

	return 0;
}

#ifdef CONFIG_LIS2DW12_TAP
static int lis2dw12_handle_single_tap_int(const struct device *dev)
{
	struct lis2dw12_data *data = dev->data;
	sensor_trigger_handler_t handler = data->tap_handler;

	struct sensor_trigger pulse_trig = {
		.type = SENSOR_TRIG_TAP,
		.chan = SENSOR_CHAN_ALL,
	};

	if (handler) {
		handler(dev, &pulse_trig);
	}

	return 0;
}

static int lis2dw12_handle_double_tap_int(const struct device *dev)
{
	struct lis2dw12_data *data = dev->data;
	sensor_trigger_handler_t handler = data->double_tap_handler;

	struct sensor_trigger pulse_trig = {
		.type = SENSOR_TRIG_DOUBLE_TAP,
		.chan = SENSOR_CHAN_ALL,
	};

	if (handler) {
		handler(dev, &pulse_trig);
	}

	return 0;
}
#endif /* CONFIG_LIS2DW12_TAP */

/**
 * lis2dw12_handle_interrupt - handle the drdy event
 * read data and call handler if registered any
 */
static void lis2dw12_handle_interrupt(const struct device *dev)
{
	struct lis2dw12_data *lis2dw12 = dev->data;
	const struct lis2dw12_device_config *cfg = dev->config;
	lis2dw12_all_sources_t sources;

	lis2dw12_all_sources_get(lis2dw12->ctx, &sources);

	if (sources.status_dup.drdy) {
		lis2dw12_handle_drdy_int(dev);
	}
#ifdef CONFIG_LIS2DW12_TAP
	if (sources.status_dup.single_tap) {
		lis2dw12_handle_single_tap_int(dev);
	}
	if (sources.status_dup.double_tap) {
		lis2dw12_handle_double_tap_int(dev);
	}
#endif /* CONFIG_LIS2DW12_TAP */

	gpio_pin_interrupt_configure_dt(&cfg->gpio_int,
					GPIO_INT_EDGE_TO_ACTIVE);
}

static void lis2dw12_gpio_callback(const struct device *dev,
				    struct gpio_callback *cb, uint32_t pins)
{
	struct lis2dw12_data *lis2dw12 =
		CONTAINER_OF(cb, struct lis2dw12_data, gpio_cb);
	const struct lis2dw12_device_config *cfg = lis2dw12->dev->config;

	if ((pins & BIT(cfg->gpio_int.pin)) == 0U) {
		return;
	}

	gpio_pin_interrupt_configure_dt(&cfg->gpio_int, GPIO_INT_DISABLE);

#if defined(CONFIG_LIS2DW12_TRIGGER_OWN_THREAD)
	k_sem_give(&lis2dw12->gpio_sem);
#elif defined(CONFIG_LIS2DW12_TRIGGER_GLOBAL_THREAD)
	k_work_submit(&lis2dw12->work);
#endif /* CONFIG_LIS2DW12_TRIGGER_OWN_THREAD */
}

#ifdef CONFIG_LIS2DW12_TRIGGER_OWN_THREAD
static void lis2dw12_thread(struct lis2dw12_data *lis2dw12)
{
	while (1) {
		k_sem_take(&lis2dw12->gpio_sem, K_FOREVER);
		lis2dw12_handle_interrupt(lis2dw12->dev);
	}
}
#endif /* CONFIG_LIS2DW12_TRIGGER_OWN_THREAD */

#ifdef CONFIG_LIS2DW12_TRIGGER_GLOBAL_THREAD
static void lis2dw12_work_cb(struct k_work *work)
{
	struct lis2dw12_data *lis2dw12 =
		CONTAINER_OF(work, struct lis2dw12_data, work);

	lis2dw12_handle_interrupt(lis2dw12->dev);
}
#endif /* CONFIG_LIS2DW12_TRIGGER_GLOBAL_THREAD */

#ifdef CONFIG_LIS2DW12_TAP
static int lis2dw12_tap_init(const struct device *dev)
{
	const struct lis2dw12_device_config *cfg = dev->config;
	struct lis2dw12_data *lis2dw12 = dev->data;

	LOG_DBG("TAP: tap mode is %d", cfg->tap_mode);
	if (lis2dw12_tap_mode_set(lis2dw12->ctx, cfg->tap_mode) < 0) {
		LOG_ERR("Failed to select tap trigger mode");
		return -EIO;
	}

	LOG_DBG("TAP: ths_x is %02x", cfg->tap_threshold[0]);
	if (lis2dw12_tap_threshold_x_set(lis2dw12->ctx, cfg->tap_threshold[0]) < 0) {
		LOG_ERR("Failed to set tap X axis threshold");
		return -EIO;
	}

	LOG_DBG("TAP: ths_y is %02x", cfg->tap_threshold[1]);
	if (lis2dw12_tap_threshold_y_set(lis2dw12->ctx, cfg->tap_threshold[1]) < 0) {
		LOG_ERR("Failed to set tap Y axis threshold");
		return -EIO;
	}

	LOG_DBG("TAP: ths_z is %02x", cfg->tap_threshold[2]);
	if (lis2dw12_tap_threshold_z_set(lis2dw12->ctx, cfg->tap_threshold[2]) < 0) {
		LOG_ERR("Failed to set tap Z axis threshold");
		return -EIO;
	}

	if (cfg->tap_threshold[0] > 0) {
		LOG_DBG("TAP: tap_x enabled");
		if (lis2dw12_tap_detection_on_x_set(lis2dw12->ctx, 1) < 0) {
			LOG_ERR("Failed to set tap detection on X axis");
			return -EIO;
		}
	}

	if (cfg->tap_threshold[1] > 0) {
		LOG_DBG("TAP: tap_y enabled");
		if (lis2dw12_tap_detection_on_y_set(lis2dw12->ctx, 1) < 0) {
			LOG_ERR("Failed to set tap detection on Y axis");
			return -EIO;
		}
	}

	if (cfg->tap_threshold[2] > 0) {
		LOG_DBG("TAP: tap_z enabled");
		if (lis2dw12_tap_detection_on_z_set(lis2dw12->ctx, 1) < 0) {
			LOG_ERR("Failed to set tap detection on Z axis");
			return -EIO;
		}
	}

	LOG_DBG("TAP: shock is %02x", cfg->tap_shock);
	if (lis2dw12_tap_shock_set(lis2dw12->ctx, cfg->tap_shock) < 0) {
		LOG_ERR("Failed to set tap shock duration");
		return -EIO;
	}

	LOG_DBG("TAP: latency is %02x", cfg->tap_latency);
	if (lis2dw12_tap_dur_set(lis2dw12->ctx, cfg->tap_latency) < 0) {
		LOG_ERR("Failed to set tap latency");
		return -EIO;
	}

	LOG_DBG("TAP: quiet time is %02x", cfg->tap_quiet);
	if (lis2dw12_tap_quiet_set(lis2dw12->ctx, cfg->tap_quiet) < 0) {
		LOG_ERR("Failed to set tap quiet time");
		return -EIO;
	}

	return 0;
}
#endif /* CONFIG_LIS2DW12_TAP */

int lis2dw12_init_interrupt(const struct device *dev)
{
	struct lis2dw12_data *lis2dw12 = dev->data;
	const struct lis2dw12_device_config *cfg = dev->config;
	int ret;

	/* setup data ready gpio interrupt (INT1 or INT2) */
	if (!device_is_ready(cfg->gpio_int.port)) {
		if (cfg->gpio_int.port) {
			LOG_ERR("%s: device %s is not ready", dev->name,
						cfg->gpio_int.port->name);
			return -ENODEV;
		}

		LOG_DBG("%s: gpio_int not defined in DT", dev->name);
		return 0;
	}

	lis2dw12->dev = dev;

	LOG_INF("%s: int-pin is on INT%d", dev->name, cfg->int_pin);
#if defined(CONFIG_LIS2DW12_TRIGGER_OWN_THREAD)
	k_sem_init(&lis2dw12->gpio_sem, 0, K_SEM_MAX_LIMIT);

	k_thread_create(&lis2dw12->thread, lis2dw12->thread_stack,
		       CONFIG_LIS2DW12_THREAD_STACK_SIZE,
		       (k_thread_entry_t)lis2dw12_thread, lis2dw12,
		       NULL, NULL, K_PRIO_COOP(CONFIG_LIS2DW12_THREAD_PRIORITY),
		       0, K_NO_WAIT);
#elif defined(CONFIG_LIS2DW12_TRIGGER_GLOBAL_THREAD)
	lis2dw12->work.handler = lis2dw12_work_cb;
#endif /* CONFIG_LIS2DW12_TRIGGER_OWN_THREAD */

	ret = gpio_pin_configure_dt(&cfg->gpio_int, GPIO_INPUT);
	if (ret < 0) {
		LOG_ERR("Could not configure gpio");
		return ret;
	}

	LOG_INF("%s: int on %s.%02u", dev->name, cfg->gpio_int.port->name,
				      cfg->gpio_int.pin);

	gpio_init_callback(&lis2dw12->gpio_cb,
			   lis2dw12_gpio_callback,
			   BIT(cfg->gpio_int.pin));

	if (gpio_add_callback(cfg->gpio_int.port, &lis2dw12->gpio_cb) < 0) {
		LOG_DBG("Could not set gpio callback");
		return -EIO;
	}

	/* enable interrupt on int1/int2 in pulse mode */
	if (lis2dw12_int_notification_set(lis2dw12->ctx, LIS2DW12_INT_PULSED)) {
		return -EIO;
	}

#ifdef CONFIG_LIS2DW12_TAP
	ret = lis2dw12_tap_init(dev);
	if (ret < 0) {
		return ret;
	}
#endif /* CONFIG_LIS2DW12_TAP */

	return gpio_pin_interrupt_configure_dt(&cfg->gpio_int,
					       GPIO_INT_EDGE_TO_ACTIVE);
}
