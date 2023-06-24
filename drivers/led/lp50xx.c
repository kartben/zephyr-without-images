/*
 * Copyright (c) 2020 Seagate Technology LLC
 * Copyright (c) 2022 Grinn
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief LP50xx LED controller
 */
#include <errno.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/led.h>
#include <zephyr/drivers/led/lp50xx.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/util.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(lp50xx, CONFIG_LED_LOG_LEVEL);

#define LP50XX_MIN_BRIGHTNESS		0U
#define LP50XX_MAX_BRIGHTNESS		100U

/*
 * Number of supported RGB led modules per chipset.
 *
 * For each module, there are 4 associated registers:
 *   - 1 brightness register
 *   - 3 color registers (RGB)
 *
 * A chipset can have more modules than leds. In this case, the
 * associated registers will simply be inactive.
 */
#define LP5012_NUM_MODULES		4
#define LP5024_NUM_MODULES		8
#define LP5036_NUM_MODULES		12

/* Maximum number of channels */
#define LP50XX_MAX_CHANNELS(nmodules)	\
	((LP50XX_COLORS_PER_LED + 1) * ((nmodules) + 1))

/* Base registers */
#define LP50XX_DEVICE_CONFIG0		0x00
#define LP50XX_DEVICE_CONFIG1		0x01
#define LP50XX_LED_CONFIG0		0x02

#define LP50XX_BANK_BASE(nmodules)		\
	(0x03 + (((nmodules) - 1) / 8))

#define LP50XX_LED0_BRIGHTNESS(nmodules)	\
	((LP50XX_BANK_BASE(nmodules)) + 4)

#define LP50XX_OUT0_COLOR(nmodules)		\
	(LP50XX_LED0_BRIGHTNESS(nmodules) + (nmodules))

/* Register values */
#define CONFIG0_CHIP_EN			BIT(6)

#define CONFIG1_LED_GLOBAL_OFF		BIT(0)
#define CONFIG1_MAX_CURRENT_OPT		BIT(1)
#define CONFIG1_PWM_DITHERING_EN	BIT(2)
#define CONFIG1_AUTO_INCR_EN		BIT(3)
#define CONFIG1_POWER_SAVE_EN		BIT(4)
#define CONFIG1_LOG_SCALE_EN		BIT(5)

struct lp50xx_config {
	struct i2c_dt_spec bus;
	uint8_t num_modules;
	uint8_t max_leds;
	uint8_t num_leds;
	bool log_scale_en;
	bool max_curr_opt;
	const struct led_info *leds_info;
};

struct lp50xx_data {
	uint8_t *chan_buf;
};

static const struct led_info *lp50xx_led_to_info(
			const struct lp50xx_config *config, uint32_t led)
{
	const struct led_info *led_info = NULL;

	for (uint8_t i = 0; i < config->num_leds; i++) {
		if (config->leds_info[i].index == led) {
			led_info = &config->leds_info[i];
		}
	}
	return led_info;
}

static int lp50xx_get_info(const struct device *dev, uint32_t led,
			   const struct led_info **info)
{
	const struct lp50xx_config *config = dev->config;
	const struct led_info *led_info = lp50xx_led_to_info(config, led);

	if (!led_info) {
		return -EINVAL;
	}

	*info = led_info;

	return 0;
}

static int lp50xx_set_brightness(const struct device *dev,
				 uint32_t led, uint8_t value)
{
	const struct lp50xx_config *config = dev->config;
	const struct led_info *led_info = lp50xx_led_to_info(config, led);
	uint8_t buf[2];

	if (!led_info) {
		return -ENODEV;
	}

	if (!IN_RANGE(value, LP50XX_MIN_BRIGHTNESS, LP50XX_MAX_BRIGHTNESS)) {
		LOG_ERR("%s: brightness value out of bounds: "
			"val=%d, min=%d, max=%d",
			dev->name,
			value,
			LP50XX_MIN_BRIGHTNESS,
			LP50XX_MAX_BRIGHTNESS);
		return -EINVAL;
	}

	buf[0] = LP50XX_LED0_BRIGHTNESS(config->num_modules) + led_info->index;
	buf[1] = (value * 0xff) / 100;

	return i2c_write_dt(&config->bus, buf, sizeof(buf));
}

static int lp50xx_on(const struct device *dev, uint32_t led)
{
	return lp50xx_set_brightness(dev, led, 100);
}

static int lp50xx_off(const struct device *dev, uint32_t led)
{
	return lp50xx_set_brightness(dev, led, 0);
}

static int lp50xx_set_color(const struct device *dev, uint32_t led,
			    uint8_t num_colors, const uint8_t *color)
{
	const struct lp50xx_config *config = dev->config;
	const struct led_info *led_info = lp50xx_led_to_info(config, led);
	uint8_t buf[4];

	if (!led_info) {
		return -ENODEV;
	}

	if (num_colors != led_info->num_colors) {
		LOG_ERR("%s: invalid number of colors: got=%d, expected=%d",
			dev->name,
			num_colors,
			led_info->num_colors);
		return -EINVAL;
	}

	buf[0] = LP50XX_OUT0_COLOR(config->num_modules);
	buf[0] += LP50XX_COLORS_PER_LED * led_info->index;

	buf[1] = color[0];
	buf[2] = color[1];
	buf[3] = color[2];

	return i2c_write_dt(&config->bus, buf, sizeof(buf));
}

static int lp50xx_write_channels(const struct device *dev,
				 uint32_t start_channel,
				 uint32_t num_channels, const uint8_t *buf)
{
	const struct lp50xx_config *config = dev->config;
	struct lp50xx_data *data = dev->data;
	uint8_t base_channel, end_channel, max_channels;

	base_channel = LP50XX_BANK_BASE(config->num_modules);
	end_channel = base_channel + start_channel + num_channels;
	max_channels = base_channel + LP50XX_MAX_CHANNELS(config->num_modules);

	if (end_channel > max_channels) {
		return -EINVAL;
	}

	/*
	 * Unfortunately this controller doesn't support commands split into
	 * two I2C messages.
	 */
	data->chan_buf[0] = base_channel + start_channel;
	memcpy(data->chan_buf + 1, buf, num_channels);

	return i2c_write_dt(&config->bus, data->chan_buf, num_channels + 1);
}

static int lp50xx_init(const struct device *dev)
{
	const struct lp50xx_config *config = dev->config;
	uint8_t buf[3];
	int err;

	if (!i2c_is_ready_dt(&config->bus)) {
		LOG_ERR("%s: I2C device not ready", dev->name);
		return -ENODEV;
	}

	if (config->num_leds > config->max_leds) {
		LOG_ERR("%s: invalid number of LEDs %d (max %d)",
			dev->name,
			config->num_leds,
			config->max_leds);
		return -EINVAL;
	}

	/*
	 * Since the status of the LP503x controller is unknown when entering
	 * this function, and since there is no way to reset it, then the whole
	 * configuration must be applied.
	 */

	/* Disable bank control for all LEDs. */
	buf[0] = LP50XX_LED_CONFIG0;
	buf[1] = 0;
	buf[2] = 0;
	if (config->chip == LP5009 || config->chip == LP5012) {
		err = i2c_write_dt(&config->bus, buf, 2);
	} else {
		err = i2c_write_dt(&config->bus, buf, 3);
	}
	if (err < 0) {
		return err;
	}

	/* Enable LED controller. */
	buf[0] = LP50XX_DEVICE_CONFIG0;
	buf[1] = CONFIG0_CHIP_EN;
	err = i2c_write_dt(&config->bus, buf, 2);
	if (err < 0) {
		return err;
	}

	/* Apply configuration. */
	buf[0] = LP50XX_DEVICE_CONFIG1;
	buf[1] = CONFIG1_PWM_DITHERING_EN | CONFIG1_AUTO_INCR_EN
		| CONFIG1_POWER_SAVE_EN;
	if (config->max_curr_opt) {
		buf[1] |= CONFIG1_MAX_CURRENT_OPT;
	}
	if (config->log_scale_en) {
		buf[1] |= CONFIG1_LOG_SCALE_EN;
	}

	return i2c_write_dt(&config->bus, buf, 2);
}

static const struct led_driver_api lp50xx_led_api = {
	.on		= lp50xx_on,
	.off		= lp50xx_off,
	.get_info	= lp50xx_get_info,
	.set_brightness	= lp50xx_set_brightness,
	.set_color	= lp50xx_set_color,
	.write_channels	= lp50xx_write_channels,
};

#define COLOR_MAPPING(led_node_id)						\
	const uint8_t color_mapping_##led_node_id[] =				\
		DT_PROP(led_node_id, color_mapping);

#define LED_INFO(led_node_id)							\
	{									\
		.label		= DT_PROP(led_node_id, label),			\
		.index		= DT_PROP(led_node_id, index),			\
		.num_colors	=						\
			DT_PROP_LEN(led_node_id, color_mapping),		\
		.color_mapping	= color_mapping_##led_node_id,			\
	},

#define LP50XX_DEVICE(n, id, nmodules)						\
	DT_INST_FOREACH_CHILD(n, COLOR_MAPPING)					\
										\
	static const struct led_info lp##id##_leds_##n[] = {			\
		DT_INST_FOREACH_CHILD(n, LED_INFO)				\
	};									\
										\
	static const struct lp50xx_config lp##id##_config_##n = {		\
		.bus			= I2C_DT_SPEC_INST_GET(n),		\
		.num_modules		= nmodules,				\
		.max_leds		= LP##id##_MAX_LEDS,			\
		.num_leds		= ARRAY_SIZE(lp##id##_leds_##n),	\
		.log_scale_en		= DT_INST_PROP(n, log_scale_en),	\
		.max_curr_opt		= DT_INST_PROP(n, max_curr_opt),	\
		.leds_info		= lp##id##_leds_##n,			\
	};									\
										\
	static uint8_t lp##id##_chan_buf_##n[LP50XX_MAX_CHANNELS(nmodules) + 1];\
										\
	static struct lp50xx_data lp##id##_data_##n = {				\
		.chan_buf	= lp##id##_chan_buf_##n,			\
	};									\
										\
	DEVICE_DT_INST_DEFINE(n,						\
			      lp50xx_init,					\
			      NULL,						\
			      &lp##id##_data_##n,				\
			      &lp##id##_config_##n,				\
			      POST_KERNEL, CONFIG_LED_INIT_PRIORITY,		\
			      &lp50xx_led_api);

#undef DT_DRV_COMPAT
#define DT_DRV_COMPAT ti_lp5009
DT_INST_FOREACH_STATUS_OKAY_VARGS(LP50XX_DEVICE, 5009, LP5012_NUM_MODULES)

#undef DT_DRV_COMPAT
#define DT_DRV_COMPAT ti_lp5012
DT_INST_FOREACH_STATUS_OKAY_VARGS(LP50XX_DEVICE, 5012, LP5012_NUM_MODULES)

#undef DT_DRV_COMPAT
#define DT_DRV_COMPAT ti_lp5018
DT_INST_FOREACH_STATUS_OKAY_VARGS(LP50XX_DEVICE, 5018, LP5024_NUM_MODULES)

#undef DT_DRV_COMPAT
#define DT_DRV_COMPAT ti_lp5024
DT_INST_FOREACH_STATUS_OKAY_VARGS(LP50XX_DEVICE, 5024, LP5024_NUM_MODULES)

#undef DT_DRV_COMPAT
#define DT_DRV_COMPAT ti_lp5030
DT_INST_FOREACH_STATUS_OKAY_VARGS(LP50XX_DEVICE, 5030, LP5036_NUM_MODULES)

#undef DT_DRV_COMPAT
#define DT_DRV_COMPAT ti_lp5036
DT_INST_FOREACH_STATUS_OKAY_VARGS(LP50XX_DEVICE, 5036, LP5036_NUM_MODULES)
