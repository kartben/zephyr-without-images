/*
 * Copyright (c) 2017 Jan Van Winkel <jan.van_winkel@dxplore.eu>
 * Copyright (c) 2019 Nordic Semiconductor ASA
 * Copyright (c) 2020 Teslabs Engineering S.L.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT ilitek_ili9340

#include "display_ili9340.h"

#include <string.h>

#include <drivers/display.h>
#include <drivers/gpio.h>
#include <drivers/spi.h>
#include <sys/byteorder.h>

#include <logging/log.h>
LOG_MODULE_REGISTER(display_ili9340, CONFIG_DISPLAY_LOG_LEVEL);

struct ili9340_config {
	const char *spi_name;
	uint16_t spi_addr;
	uint32_t spi_max_freq;
	const char *spi_cs_label;
	gpio_pin_t spi_cs_pin;
	gpio_dt_flags_t spi_cs_flags;
	const char *cmd_data_label;
	gpio_pin_t cmd_data_pin;
	gpio_dt_flags_t cmd_data_flags;
	const char *reset_label;
	gpio_pin_t reset_pin;
	gpio_dt_flags_t reset_flags;
};

struct ili9340_data {
	const struct device *reset_gpio;
	const struct device *command_data_gpio;
	const struct device *spi_dev;
	struct spi_config spi_config;
	struct spi_cs_control cs_ctrl;
};

/* The number of bytes taken by a RGB pixel */
#ifdef CONFIG_ILI9340_RGB565
#define ILI9340_RGB_SIZE 2U
#else
#define ILI9340_RGB_SIZE 3U
#endif

static int ili9340_exit_sleep(const struct device *dev)
{
	int r;

	r = ili9340_transmit(dev, ILI9340_CMD_EXIT_SLEEP, NULL, 0);
	if (r < 0) {
		return r;
	}

	k_sleep(K_MSEC(ILI9340_SLEEP_OUT_TIME));

	return 0;
}

static void ili9340_hw_reset(const struct device *dev)
{
	const struct ili9340_config *config = (struct ili9340_config *)dev->config;
	struct ili9340_data *data = (struct ili9340_data *)dev->data;

	if (data->reset_gpio == NULL) {
		return;
	}

	gpio_pin_set(data->reset_gpio, config->reset_pin, 1);
	k_sleep(K_MSEC(ILI9340_RESET_PULSE_TIME));
	gpio_pin_set(data->reset_gpio, config->reset_pin, 0);

	k_sleep(K_MSEC(ILI9340_RESET_WAIT_TIME));
}

static int ili9340_init(const struct device *dev)
{
	const struct ili9340_config *config = (struct ili9340_config *)dev->config;
	struct ili9340_data *data = (struct ili9340_data *)dev->data;

	int r;

	data->spi_dev = device_get_binding(config->spi_name);
	if (data->spi_dev == NULL) {
		LOG_ERR("Could not get SPI device %s", config->spi_name);
		return -ENODEV;
	}

	data->spi_config.frequency = config->spi_max_freq;
	data->spi_config.operation = SPI_OP_MODE_MASTER | SPI_WORD_SET(8U);
	data->spi_config.slave = config->spi_addr;

	data->cs_ctrl.gpio_dev = device_get_binding(config->spi_cs_label);
	if (data->cs_ctrl.gpio_dev != NULL) {
		data->cs_ctrl.gpio_pin = config->spi_cs_pin;
		data->cs_ctrl.gpio_dt_flags = config->spi_cs_flags;
		data->cs_ctrl.delay = 0U;
		data->spi_config.cs = &data->cs_ctrl;
	}

	data->command_data_gpio = device_get_binding(config->cmd_data_label);
	if (data->command_data_gpio == NULL) {
		LOG_ERR("Could not get command/data GPIO port %s", config->cmd_data_label);
		return -ENODEV;
	}

	r = gpio_pin_configure(data->command_data_gpio, config->cmd_data_pin,
			       GPIO_OUTPUT | config->cmd_data_flags);
	if (r < 0) {
		LOG_ERR("Could not configure command/data GPIO (%d)", r);
		return r;
	}

	data->reset_gpio = device_get_binding(config->reset_label);
	if (data->reset_gpio != NULL) {
		r = gpio_pin_configure(data->reset_gpio, config->reset_pin,
				       GPIO_OUTPUT_INACTIVE | config->reset_flags);
		if (r < 0) {
			LOG_ERR("Could not configure reset GPIO (%d)", r);
			return r;
		}
	}

	ili9340_hw_reset(dev);

	r = ili9340_lcd_init(dev);
	if (r < 0) {
		LOG_ERR("Could not initialize LCD (%d)", r);
		return r;
	}

	r = ili9340_exit_sleep(dev);
	if (r < 0) {
		LOG_ERR("Could not exit sleep mode (%d)", r);
		return r;
	}

	return 0;
}

static int ili9340_set_mem_area(const struct device *dev, const uint16_t x,
				const uint16_t y, const uint16_t w, const uint16_t h)
{
	int r;
	uint16_t spi_data[2];

	spi_data[0] = sys_cpu_to_be16(x);
	spi_data[1] = sys_cpu_to_be16(x + w - 1U);
	r = ili9340_transmit(dev, ILI9340_CMD_COLUMN_ADDR, &spi_data[0], 4U);
	if (r < 0) {
		return r;
	}

	spi_data[0] = sys_cpu_to_be16(y);
	spi_data[1] = sys_cpu_to_be16(y + h - 1U);
	r = ili9340_transmit(dev, ILI9340_CMD_PAGE_ADDR, &spi_data[0], 4U);
	if (r < 0) {
		return r;
	}

	return 0;
}

static int ili9340_write(const struct device *dev, const uint16_t x,
			 const uint16_t y,
			 const struct display_buffer_descriptor *desc,
			 const void *buf)
{
	struct ili9340_data *data = (struct ili9340_data *)dev->data;

	int r;
	const uint8_t *write_data_start = (const uint8_t *)buf;
	struct spi_buf tx_buf;
	struct spi_buf_set tx_bufs;
	uint16_t write_cnt;
	uint16_t nbr_of_writes;
	uint16_t write_h;

	__ASSERT(desc->width <= desc->pitch, "Pitch is smaller than width");
	__ASSERT((desc->pitch * ILI9340_RGB_SIZE * desc->height) <= desc->buf_size,
		 "Input buffer to small");

	LOG_DBG("Writing %dx%d (w,h) @ %dx%d (x,y)", desc->width, desc->height,
			x, y);
	r = ili9340_set_mem_area(dev, x, y, desc->width, desc->height);
	if (r < 0) {
		return r;
	}

	if (desc->pitch > desc->width) {
		write_h = 1U;
		nbr_of_writes = desc->height;
	} else {
		write_h = desc->height;
		nbr_of_writes = 1U;
	}

	r = ili9340_transmit(dev, ILI9340_CMD_MEM_WRITE,
			     write_data_start,
			     desc->width * ILI9340_RGB_SIZE * write_h);
	if (r < 0) {
		return r;
	}

	tx_bufs.buffers = &tx_buf;
	tx_bufs.count = 1;

	write_data_start += (desc->pitch * ILI9340_RGB_SIZE);
	for (write_cnt = 1U; write_cnt < nbr_of_writes; ++write_cnt) {
		tx_buf.buf = (void *)write_data_start;
		tx_buf.len = desc->width * ILI9340_RGB_SIZE * write_h;

		r = spi_write(data->spi_dev, &data->spi_config, &tx_bufs);
		if (r < 0) {
			return r;
		}

		write_data_start += desc->pitch * ILI9340_RGB_SIZE;
	}

	return 0;
}

static int ili9340_read(const struct device *dev, const uint16_t x,
			const uint16_t y,
			const struct display_buffer_descriptor *desc,
			void *buf)
{
	LOG_ERR("Reading not supported");
	return -ENOTSUP;
}

static void *ili9340_get_framebuffer(const struct device *dev)
{
	LOG_ERR("Direct framebuffer access not supported");
	return NULL;
}

static int ili9340_display_blanking_off(const struct device *dev)
{
	LOG_DBG("Turning display blanking off");
	return ili9340_transmit(dev, ILI9340_CMD_DISPLAY_ON, NULL, 0);
}

static int ili9340_display_blanking_on(const struct device *dev)
{
	LOG_DBG("Turning display blanking on");
	return ili9340_transmit(dev, ILI9340_CMD_DISPLAY_OFF, NULL, 0);
}

static int ili9340_set_brightness(const struct device *dev,
				  const uint8_t brightness)
{
	LOG_ERR("Set brightness not implemented");
	return -ENOTSUP;
}

static int ili9340_set_contrast(const struct device *dev, const uint8_t contrast)
{
	LOG_ERR("Set contrast not supported");
	return -ENOTSUP;
}

static int ili9340_set_pixel_format(const struct device *dev,
				    const enum display_pixel_format
				    pixel_format)
{
#ifdef CONFIG_ILI9340_RGB565
	if (pixel_format == PIXEL_FORMAT_RGB_565) {
#else
	if (pixel_format == PIXEL_FORMAT_RGB_888) {
#endif
		return 0;
	}
	LOG_ERR("Pixel format change not implemented");
	return -ENOTSUP;
}

static int ili9340_set_orientation(const struct device *dev,
				   const enum display_orientation orientation)
{
	if (orientation == DISPLAY_ORIENTATION_NORMAL) {
		return 0;
	}
	LOG_ERR("Changing display orientation not implemented");
	return -ENOTSUP;
}

static void ili9340_get_capabilities(const struct device *dev,
				     struct display_capabilities *capabilities)
{
	memset(capabilities, 0, sizeof(struct display_capabilities));
	capabilities->x_resolution = ILI9340_X_RES;
	capabilities->y_resolution = ILI9340_Y_RES;
#ifdef CONFIG_ILI9340_RGB565
	capabilities->supported_pixel_formats = PIXEL_FORMAT_RGB_565;
	capabilities->current_pixel_format = PIXEL_FORMAT_RGB_565;
#else
	capabilities->supported_pixel_formats = PIXEL_FORMAT_RGB_888;
	capabilities->current_pixel_format = PIXEL_FORMAT_RGB_888;
#endif
	capabilities->current_orientation = DISPLAY_ORIENTATION_NORMAL;
}

int ili9340_transmit(const struct device *dev, uint8_t cmd, const void *tx_data,
		     size_t tx_len)
{
	const struct ili9340_config *config = (struct ili9340_config *)dev->config;
	struct ili9340_data *data = (struct ili9340_data *)dev->data;

	int r;
	struct spi_buf tx_buf;
	struct spi_buf_set tx_bufs = { .buffers = &tx_buf, .count = 1U };

	/* send command */
	tx_buf.buf = &cmd;
	tx_buf.len = 1U;

	gpio_pin_set(data->command_data_gpio, config->cmd_data_pin, ILI9340_CMD);
	r = spi_write(data->spi_dev, &data->spi_config, &tx_bufs);
	if (r < 0) {
		return r;
	}

	/* send data (if any) */
	if (tx_data != NULL) {
		tx_buf.buf = (void *)tx_data;
		tx_buf.len = tx_len;

		gpio_pin_set(data->command_data_gpio, config->cmd_data_pin, ILI9340_DATA);
		r = spi_write(data->spi_dev, &data->spi_config, &tx_bufs);
		if (r < 0) {
			return r;
		}
	}

	return 0;
}

static const struct display_driver_api ili9340_api = {
	.blanking_on = ili9340_display_blanking_on,
	.blanking_off = ili9340_display_blanking_off,
	.write = ili9340_write,
	.read = ili9340_read,
	.get_framebuffer = ili9340_get_framebuffer,
	.set_brightness = ili9340_set_brightness,
	.set_contrast = ili9340_set_contrast,
	.get_capabilities = ili9340_get_capabilities,
	.set_pixel_format = ili9340_set_pixel_format,
	.set_orientation = ili9340_set_orientation,
};

#define ILI9340_INIT(index)                                                    \
	static const struct ili9340_config ili9340_config_##index = {          \
		.spi_name = DT_INST_BUS_LABEL(index),                          \
		.spi_addr = DT_INST_REG_ADDR(index),                           \
		.spi_max_freq = UTIL_AND(                                      \
			DT_INST_HAS_PROP(index, spi_max_frequency),            \
			DT_INST_PROP(index, spi_max_frequency)                 \
		),                                                             \
		.spi_cs_label = UTIL_AND(                                      \
			DT_INST_SPI_DEV_HAS_CS_GPIOS(index),                   \
			DT_INST_SPI_DEV_CS_GPIOS_LABEL(index)),                \
		.spi_cs_pin = UTIL_AND(                                        \
			DT_INST_SPI_DEV_HAS_CS_GPIOS(index),                   \
			DT_INST_SPI_DEV_CS_GPIOS_PIN(index)),                  \
		.spi_cs_flags = UTIL_AND(                                      \
			DT_INST_SPI_DEV_HAS_CS_GPIOS(index),                   \
			DT_INST_SPI_DEV_CS_GPIOS_FLAGS(index)),                \
		.cmd_data_label = DT_INST_GPIO_LABEL(index, cmd_data_gpios),   \
		.cmd_data_pin = DT_INST_GPIO_PIN(index, cmd_data_gpios),       \
		.cmd_data_flags = DT_INST_GPIO_FLAGS(index, cmd_data_gpios),   \
		.reset_label = UTIL_AND(                                       \
			DT_INST_NODE_HAS_PROP(index, reset_gpios),             \
			DT_INST_GPIO_LABEL(index, reset_gpios)),               \
		.reset_pin = UTIL_AND(                                         \
			DT_INST_NODE_HAS_PROP(index, reset_gpios),             \
			DT_INST_GPIO_PIN(index, reset_gpios)),                 \
		.reset_flags = UTIL_AND(                                       \
			DT_INST_NODE_HAS_PROP(index, reset_gpios),             \
			DT_INST_GPIO_FLAGS(index, reset_gpios)),               \
	};                                                                     \
									       \
	static struct ili9340_data ili9340_data_##index;                       \
									       \
	DEVICE_AND_API_INIT(ili9340_##index, DT_INST_LABEL(index),             \
			    ili9340_init, &ili9340_data_##index,               \
			    &ili9340_config_##index, POST_KERNEL,              \
			    CONFIG_APPLICATION_INIT_PRIORITY, &ili9340_api);

DT_INST_FOREACH_STATUS_OKAY(ILI9340_INIT)
