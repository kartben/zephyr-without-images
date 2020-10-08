/* ST Microelectronics IIS2ICLX 2-axis accelerometer sensor driver
 *
 * Copyright (c) 2020 STMicroelectronics
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Datasheet:
 * https://www.st.com/resource/en/datasheet/iis2iclx.pdf
 */

#ifndef ZEPHYR_DRIVERS_SENSOR_IIS2ICLX_IIS2ICLX_H_
#define ZEPHYR_DRIVERS_SENSOR_IIS2ICLX_IIS2ICLX_H_

#include <drivers/sensor.h>
#include <zephyr/types.h>
#include <drivers/gpio.h>
#include <drivers/spi.h>
#include <sys/util.h>
#include "iis2iclx_reg.h"

#define IIS2ICLX_EN_BIT					0x01
#define IIS2ICLX_DIS_BIT					0x00

/* Accel sensor sensitivity grain is 15 ug/LSB */
#define GAIN_UNIT_XL				(15LL)

#define SENSOR_PI_DOUBLE			(SENSOR_PI / 1000000.0)
#define SENSOR_DEG2RAD_DOUBLE			(SENSOR_PI_DOUBLE / 180)
#define SENSOR_G_DOUBLE				(SENSOR_G / 1000000.0)

#if CONFIG_IIS2ICLX_ACCEL_FS == 0
	#define IIS2ICLX_ACCEL_FS_RUNTIME 1
	#define IIS2ICLX_DEFAULT_ACCEL_FULLSCALE		0
	#define IIS2ICLX_DEFAULT_ACCEL_SENSITIVITY	GAIN_UNIT_XL
#elif CONFIG_IIS2ICLX_ACCEL_FS == 500
	#define IIS2ICLX_DEFAULT_ACCEL_FULLSCALE		0
	#define IIS2ICLX_DEFAULT_ACCEL_SENSITIVITY	GAIN_UNIT_XL
#elif CONFIG_IIS2ICLX_ACCEL_FS == 1000
	#define IIS2ICLX_DEFAULT_ACCEL_FULLSCALE		2
	#define IIS2ICLX_DEFAULT_ACCEL_SENSITIVITY	(2.0 * GAIN_UNIT_XL)
#elif CONFIG_IIS2ICLX_ACCEL_FS == 2000
	#define IIS2ICLX_DEFAULT_ACCEL_FULLSCALE		3
	#define IIS2ICLX_DEFAULT_ACCEL_SENSITIVITY	(4.0 * GAIN_UNIT_XL)
#elif CONFIG_IIS2ICLX_ACCEL_FS == 3000
	#define IIS2ICLX_DEFAULT_ACCEL_FULLSCALE		1
	#define IIS2ICLX_DEFAULT_ACCEL_SENSITIVITY	(8.0 * GAIN_UNIT_XL)
#endif

#if (CONFIG_IIS2ICLX_ACCEL_ODR == 0)
#define IIS2ICLX_ACCEL_ODR_RUNTIME 1
#endif

struct iis2iclx_config {
	char *bus_name;
	int (*bus_init)(const struct device *dev);
#ifdef CONFIG_IIS2ICLX_TRIGGER
	const char *int_gpio_port;
	uint8_t int_gpio_pin;
	uint8_t int_gpio_flags;
	uint8_t int_pin;
#endif /* CONFIG_IIS2ICLX_TRIGGER */
#if DT_ANY_INST_ON_BUS_STATUS_OKAY(i2c)
	uint16_t i2c_slv_addr;
#elif DT_ANY_INST_ON_BUS_STATUS_OKAY(spi)
	struct spi_config spi_conf;
#if DT_INST_SPI_DEV_HAS_CS_GPIOS(0)
	const char *gpio_cs_port;
	uint8_t cs_gpio;
	uint8_t cs_gpio_flags;
#endif /* DT_INST_SPI_DEV_HAS_CS_GPIOS(0) */
#endif /* DT_ANY_INST_ON_BUS_STATUS_OKAY(i2c) */
};

/* sensor data forward declaration (member definition is below) */
struct iis2iclx_data;

struct iis2iclx_tf {
	int (*read_data)(struct iis2iclx_data *data, uint8_t reg_addr,
			 uint8_t *value, uint8_t len);
	int (*write_data)(struct iis2iclx_data *data, uint8_t reg_addr,
			  uint8_t *value, uint8_t len);
	int (*read_reg)(struct iis2iclx_data *data, uint8_t reg_addr,
			uint8_t *value);
	int (*write_reg)(struct iis2iclx_data *data, uint8_t reg_addr,
			uint8_t value);
	int (*update_reg)(struct iis2iclx_data *data, uint8_t reg_addr,
			  uint8_t mask, uint8_t value);
};

#define IIS2ICLX_SHUB_MAX_NUM_SLVS			2

struct iis2iclx_data {
	const struct device *dev;
	const struct device *bus;
	int16_t acc[2];
	uint32_t acc_gain;
#if defined(CONFIG_IIS2ICLX_ENABLE_TEMP)
	int temp_sample;
#endif
#if defined(CONFIG_IIS2ICLX_SENSORHUB)
	uint8_t ext_data[2][6];
	uint16_t magn_gain;

	struct hts221_data {
		int16_t x0;
		int16_t x1;
		int16_t y0;
		int16_t y1;
	} hts221;
#endif /* CONFIG_IIS2ICLX_SENSORHUB */

	stmdev_ctx_t *ctx;

	#if DT_ANY_INST_ON_BUS_STATUS_OKAY(i2c)
	stmdev_ctx_t ctx_i2c;
	#elif DT_ANY_INST_ON_BUS_STATUS_OKAY(spi)
	stmdev_ctx_t ctx_spi;
	#endif

	uint16_t accel_freq;
	uint8_t accel_fs;

#ifdef CONFIG_IIS2ICLX_TRIGGER
	const struct device *gpio;
	struct gpio_callback gpio_cb;
	sensor_trigger_handler_t handler_drdy_acc;
	sensor_trigger_handler_t handler_drdy_temp;

#if defined(CONFIG_IIS2ICLX_TRIGGER_OWN_THREAD)
	K_KERNEL_STACK_MEMBER(thread_stack, CONFIG_IIS2ICLX_THREAD_STACK_SIZE);
	struct k_thread thread;
	struct k_sem gpio_sem;
#elif defined(CONFIG_IIS2ICLX_TRIGGER_GLOBAL_THREAD)
	struct k_work work;
#endif
#endif /* CONFIG_IIS2ICLX_TRIGGER */

#if DT_INST_SPI_DEV_HAS_CS_GPIOS(0)
	struct spi_cs_control cs_ctrl;
#endif
};

int iis2iclx_spi_init(const struct device *dev);
int iis2iclx_i2c_init(const struct device *dev);
#if defined(CONFIG_IIS2ICLX_SENSORHUB)
int iis2iclx_shub_init(const struct device *dev);
int iis2iclx_shub_fetch_external_devs(const struct device *dev);
int iis2iclx_shub_get_idx(enum sensor_channel type);
int iis2iclx_shub_config(const struct device *dev, enum sensor_channel chan,
			   enum sensor_attribute attr,
			   const struct sensor_value *val);
#endif /* CONFIG_IIS2ICLX_SENSORHUB */

#ifdef CONFIG_IIS2ICLX_TRIGGER
int iis2iclx_trigger_set(const struct device *dev,
			   const struct sensor_trigger *trig,
			   sensor_trigger_handler_t handler);

int iis2iclx_init_interrupt(const struct device *dev);
#endif

#endif /* ZEPHYR_DRIVERS_SENSOR_IIS2ICLX_IIS2ICLX_H_ */
