/*
 * Copyright (c) 2016 Intel Corporation
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

#include <i2c.h>
#include <init.h>
#include <sensor.h>
#include <misc/__assert.h>

#include "sensor_lis3dh.h"

static void lis3dh_convert(struct sensor_value *val, int64_t raw_val)
{
	/* val = raw_val * LIS3DH_ACCEL_SCALE / (10^6 * (2^16 - 1)) */
	val->type = SENSOR_VALUE_TYPE_INT_PLUS_MICRO;
	raw_val = raw_val * LIS3DH_ACCEL_SCALE / 1000000;
	val->val1 = raw_val / 0xFFFF;
	val->val2 = (raw_val % 0xFFFF) * 1000000 / 0xFFFF;

	/* normalize val to make sure val->val2 is positive */
	if (val->val2 < 0) {
		val->val1 -= 1;
		val->val2 += 1000000;
	}
}

static int lis3dh_channel_get(struct device *dev,
			      enum sensor_channel chan,
			      struct sensor_value *val)
{
	struct lis3dh_data *drv_data = dev->driver_data;

	if (chan == SENSOR_CHAN_ACCEL_X) {
		lis3dh_convert(val, drv_data->x_sample);
	} else if (chan == SENSOR_CHAN_ACCEL_Y) {
		lis3dh_convert(val, drv_data->y_sample);
	} else if (chan == SENSOR_CHAN_ACCEL_Z) {
		lis3dh_convert(val, drv_data->z_sample);
	} else if (chan == SENSOR_CHAN_ACCEL_ANY) {
		lis3dh_convert(val, drv_data->x_sample);
		lis3dh_convert(val + 1, drv_data->y_sample);
		lis3dh_convert(val + 2, drv_data->z_sample);
	} else {
		return -ENOTSUP;
	}

	return 0;
}

int lis3dh_sample_fetch(struct device *dev, enum sensor_channel chan)
{
	struct lis3dh_data *drv_data = dev->driver_data;
	uint8_t buf[6];

	__ASSERT(chan == SENSOR_CHAN_ALL || chan == SENSOR_CHAN_ACCEL_ANY);

	/*
	 * since all accel data register addresses are consecutive,
	 * a burst read can be used to read all the samples
	 */
	if (i2c_burst_read(drv_data->i2c, LIS3DH_I2C_ADDRESS,
			   LIS3DH_REG_ACCEL_X_LSB, buf, 6) < 0) {
		SYS_LOG_DBG("Could not read accel axis data");
		return -EIO;
	}

	drv_data->x_sample = (buf[1] << 8) | buf[0];
	drv_data->y_sample = (buf[3] << 8) | buf[2];
	drv_data->z_sample = (buf[5] << 8) | buf[4];

	return 0;
}

static struct sensor_driver_api lis3dh_driver_api = {
#if CONFIG_LIS3DH_TRIGGER
	.trigger_set = lis3dh_trigger_set,
#endif
	.sample_fetch = lis3dh_sample_fetch,
	.channel_get = lis3dh_channel_get,
};

int lis3dh_init(struct device *dev)
{
	struct lis3dh_data *drv_data = dev->driver_data;

	drv_data->i2c = device_get_binding(CONFIG_LIS3DH_I2C_MASTER_DEV_NAME);
	if (drv_data->i2c == NULL) {
		SYS_LOG_DBG("Could not get pointer to %s device",
		    CONFIG_LIS3DH_I2C_MASTER_DEV_NAME);
		return -EINVAL;
	}

	/* enable accel measurements and set power mode and data rate */
	if (i2c_reg_write_byte(drv_data->i2c, LIS3DH_I2C_ADDRESS,
			       LIS3DH_REG_CTRL1, LIS3DH_ACCEL_EN_BITS |
			       LIS3DH_LP_EN_BIT | LIS3DH_ODR_BITS) < 0) {
		SYS_LOG_DBG("Failed to configure chip.");
	}

	/* set full scale range */
	if (i2c_reg_write_byte(drv_data->i2c, LIS3DH_I2C_ADDRESS,
			       LIS3DH_REG_CTRL4, LIS3DH_FS_BITS) < 0) {
		SYS_LOG_DBG("Failed to set full scale range.");
		return -EIO;
	}

#ifdef CONFIG_LIS3DH_TRIGGER
	if (lis3dh_init_interrupt(dev) < 0) {
		SYS_LOG_DBG("Failed to initialize interrupts.");
		return -EIO;
	}
#endif

	dev->driver_api = &lis3dh_driver_api;

	return 0;
}

struct lis3dh_data lis3dh_driver;

DEVICE_INIT(lis3dh, CONFIG_LIS3DH_NAME, lis3dh_init, &lis3dh_driver,
	    NULL, SECONDARY, CONFIG_LIS3DH_INIT_PRIORITY);
