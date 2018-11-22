/*
 * Copyright (c) 2018 Peter Bigot Consulting, LLC
 * Copyright (c) 2018 Linaro Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <device.h>
#include <drivers/gpio.h>
#include <drivers/i2c.h>
#include <kernel.h>
#include <sys/byteorder.h>
#include <sys/util.h>
#include <drivers/sensor.h>
#include <sys/__assert.h>
#include <logging/log.h>

#include "ccs811.h"

LOG_MODULE_REGISTER(CCS811, CONFIG_SENSOR_LOG_LEVEL);

#ifdef DT_INST_0_AMS_CCS811_WAKE_GPIOS_CONTROLLER
static void set_wake(struct ccs811_data *drv_data, bool enable)
{
	/* Always active-low */
	gpio_pin_write(drv_data->wake_gpio, DT_INST_0_AMS_CCS811_WAKE_GPIOS_PIN, !enable);
	if (enable) {
		k_busy_wait(50);        /* t_WAKE = 50 us */
	} else {
		k_busy_wait(20);        /* t_DWAKE = 20 us */
	}
}
#else
#define set_wake(...)
#endif

/* Get STATUS register in low 8 bits, and if ERROR is set put ERROR_ID
 * in bits 8..15.  These registers are available in both boot and
 * application mode.
 */
static int fetch_status(struct device *i2c)
{
	u8_t status;
	int rv;

	if (i2c_reg_read_byte(i2c, DT_INST_0_AMS_CCS811_BASE_ADDRESS,
			      CCS811_REG_STATUS, &status) < 0) {
		LOG_ERR("Failed to read Status register");
		return -EIO;
	}

	rv = status;
	if (status & CCS811_STATUS_ERROR) {
		u8_t error_id;

		if (i2c_reg_read_byte(i2c, DT_INST_0_AMS_CCS811_BASE_ADDRESS,
				      CCS811_REG_ERROR_ID, &error_id) < 0) {
			LOG_ERR("Failed to read ERROR_ID register");
			return -EIO;
		}

		rv |= (error_id << 8);
	}

	return rv;
}

static inline u8_t error_from_status(int status)
{
	return status >> 8;
}

int ccs811_baseline_fetch(struct device *dev)
{
	const u8_t cmd = CCS811_REG_BASELINE;
	struct ccs811_data *drv_data = dev->driver_data;
	int rc;
	u16_t baseline;

	set_wake(drv_data, true);

	rc = i2c_write_read(drv_data->i2c, DT_INST_0_AMS_CCS811_BASE_ADDRESS,
			    &cmd, sizeof(cmd),
			    (u8_t *)&baseline, sizeof(baseline));
	set_wake(drv_data, false);
	if (rc <= 0) {
		rc = baseline;
	}
	return rc;
}

int ccs811_baseline_update(struct device *dev,
			   u16_t baseline)
{
	struct ccs811_data *drv_data = dev->driver_data;
	u8_t buf[1 + sizeof(baseline)];
	int rc;

	buf[0] = CCS811_REG_BASELINE;
	memcpy(buf + 1, &baseline, sizeof(baseline));
	set_wake(drv_data, true);
	rc = i2c_write(drv_data->i2c, buf, sizeof(buf), DT_INST_0_AMS_CCS811_BASE_ADDRESS);
	set_wake(drv_data, false);
	return rc;
}

static int ccs811_sample_fetch(struct device *dev, enum sensor_channel chan)
{
	struct ccs811_data *drv_data = dev->driver_data;
	int rc;
	int tries;
	u16_t buf[4];
	int status;

	/* Check data ready flag for the measurement interval */
#ifdef CONFIG_CCS811_DRIVE_MODE_1
	tries = 11;
#elif defined(CONFIG_CCS811_DRIVE_MODE_2)
	tries = 101;
#elif defined(CONFIG_CCS811_DRIVE_MODE_3)
	tries = 601;
#endif

	do {
		const u8_t cmd = CCS811_REG_ALG_RESULT_DATA;

		set_wake(drv_data, true);
		rc = i2c_write_read(drv_data->i2c, DT_INST_0_AMS_CCS811_BASE_ADDRESS,
				    &cmd, sizeof(cmd),
				    (u8_t *)buf, sizeof(buf));

		set_wake(drv_data, false);
		if (rc < 0) {
			return -EIO;
		}

		status = buf[2];
		if (status & CCS811_STATUS_ERROR) {
			LOG_ERR("CCS811 ERROR ID %02x",
				error_from_status(status));
			return -EIO;
		}

		if (status & CCS811_STATUS_DATA_READY) {
			break;
		}

		k_sleep(K_MSEC(100));
	} while (--tries > 0);
	if (!(status & CCS811_STATUS_DATA_READY)) {
		return -EIO;
	}
	drv_data->co2 = sys_be16_to_cpu(buf[0]);
	drv_data->voc = sys_be16_to_cpu(buf[1]);
	drv_data->status = status;
	drv_data->error = error_from_status(status);
	drv_data->raw = sys_be16_to_cpu(buf[3]);
	return 0;
}

static int ccs811_channel_get(struct device *dev,
			      enum sensor_channel chan,
			      struct sensor_value *val)
{
	struct ccs811_data *drv_data = dev->driver_data;
	u32_t uval;

	switch (chan) {
	case SENSOR_CHAN_CO2:
		val->val1 = drv_data->co2;
		val->val2 = 0;

		break;
	case SENSOR_CHAN_VOC:
		val->val1 = drv_data->voc;
		val->val2 = 0;

		break;
	case SENSOR_CHAN_VOLTAGE:
		/*
		 * Raw ADC readings are contained in least significant 10 bits
		 */
		uval = ((drv_data->raw & CCS811_RAW_VOLTAGE_MSK)
			>> CCS811_RAW_VOLTAGE_POS) * CCS811_RAW_VOLTAGE_SCALE;
		val->val1 = uval / 1000000U;
		val->val2 = uval % 1000000;

		break;
	case SENSOR_CHAN_CURRENT:
		/*
		 * Current readings are contained in most
		 * significant 6 bits in microAmps
		 */
		uval = ((drv_data->raw & CCS811_RAW_CURRENT_MSK)
			>> CCS811_RAW_CURRENT_POS) * CCS811_RAW_CURRENT_SCALE;
		val->val1 = uval / 1000000U;
		val->val2 = uval % 1000000;

		break;
	default:
		return -ENOTSUP;
	}

	return 0;
}

static const struct sensor_driver_api ccs811_driver_api = {
#ifdef CONFIG_CCS811_TRIGGER
	.attr_set = ccs811_attr_set,
	.trigger_set = ccs811_trigger_set,
#endif
	.sample_fetch = ccs811_sample_fetch,
	.channel_get = ccs811_channel_get,
};

static int switch_to_app_mode(struct device *i2c)
{
	u8_t buf;
	int status;

	LOG_DBG("Switching to Application mode...");

	status = fetch_status(i2c);
	if (status < 0) {
		return -EIO;
	}

	/* Check for the application firmware */
	if (!(status & CCS811_STATUS_APP_VALID)) {
		LOG_ERR("No Application firmware loaded");
		return -EINVAL;
	}

	/* Check if already in application mode */
	if (status & CCS811_STATUS_FW_MODE) {
		LOG_DBG("CCS811 Already in application mode");
		return 0;
	}

	buf = CCS811_REG_APP_START;
	/* Set the device to application mode */
	if (i2c_write(i2c, &buf, 1, DT_INST_0_AMS_CCS811_BASE_ADDRESS) < 0) {
		LOG_ERR("Failed to set Application mode");
		return -EIO;
	}

	k_sleep(1);             /* t_APP_START */
	status = fetch_status(i2c);
	if (status < 0) {
		return -EIO;
	}

	/* Check for application mode */
	if (!(status & CCS811_STATUS_FW_MODE)) {
		LOG_ERR("Failed to start Application firmware");
		return -EINVAL;
	}

	LOG_DBG("CCS811 Application firmware started!");

	return 0;
}

#ifdef CONFIG_CCS811_TRIGGER

int ccs811_mutate_meas_mode(struct device *dev,
			    u8_t set,
			    u8_t clear)
{
	struct ccs811_data *drv_data = dev->driver_data;
	int rc = 0;
	u8_t mode = set | (drv_data->mode & ~clear);

	/*
	 * Changing drive mode of a running system has preconditions.
	 * Only allow changing the interrupt generation.
	 */
	if ((set | clear) & ~(CCS811_MODE_DATARDY | CCS811_MODE_THRESH)) {
		return -EINVAL;
	}

	if (mode != drv_data->mode) {
		set_wake(drv_data, true);
		rc = i2c_reg_write_byte(drv_data->i2c, DT_INST_0_AMS_CCS811_BASE_ADDRESS,
					CCS811_REG_MEAS_MODE,
					mode);
		LOG_DBG("CCS811 meas mode change %02x to %02x got %d",
			drv_data->mode, mode, rc);
		if (rc < 0) {
			LOG_ERR("Failed to set mode");
			rc = -EIO;
		} else {
			drv_data->mode = mode;
			rc = 0;
		}

		set_wake(drv_data, false);
	}

	return rc;
}

int ccs811_set_thresholds(struct device *dev)
{
	struct ccs811_data *drv_data = dev->driver_data;
	const u8_t buf[5] = {
		CCS811_REG_THRESHOLDS,
		drv_data->co2_l2m >> 8,
		drv_data->co2_l2m,
		drv_data->co2_m2h >> 8,
		drv_data->co2_m2h,
	};
	int rc;

	set_wake(drv_data, true);
	rc = i2c_write(drv_data->i2c, buf, sizeof(buf), DT_INST_0_AMS_CCS811_BASE_ADDRESS);
	set_wake(drv_data, false);
	return rc;
}

#endif /* CONFIG_CCS811_TRIGGER */

static int ccs811_init(struct device *dev)
{
	struct ccs811_data *drv_data = dev->driver_data;
	int ret = 0;
	u8_t hw_id;
	int status;

	*drv_data = (struct ccs811_data){ 0 };
	drv_data->i2c = device_get_binding(DT_INST_0_AMS_CCS811_BUS_NAME);
	if (drv_data->i2c == NULL) {
		LOG_ERR("Failed to get pointer to %s device!",
			DT_INST_0_AMS_CCS811_BUS_NAME);
		return -EINVAL;
	}

#ifdef DT_INST_0_AMS_CCS811_WAKE_GPIOS_CONTROLLER
	drv_data->wake_gpio = device_get_binding(DT_INST_0_AMS_CCS811_WAKE_GPIOS_CONTROLLER);
	if (drv_data->wake_gpio == NULL) {
		LOG_ERR("Failed to get pointer to WAKE device: %s",
			DT_INST_0_AMS_CCS811_WAKE_GPIOS_CONTROLLER);
		return -EINVAL;
	}

	/*
	 * Wakeup pin should be pulled low before initiating
	 * any I2C transfer.  If it has been tied to GND by
	 * default, skip this part.
	 */
	gpio_pin_configure(drv_data->wake_gpio, DT_INST_0_AMS_CCS811_WAKE_GPIOS_PIN,
			   GPIO_DIR_OUT);

	set_wake(drv_data, true);
	k_sleep(1);
#endif
#ifdef DT_INST_0_AMS_CCS811_RESET_GPIOS_CONTROLLER
	drv_data->reset_gpio = device_get_binding(DT_INST_0_AMS_CCS811_RESET_GPIOS_CONTROLLER);
	if (drv_data->reset_gpio == NULL) {
		LOG_ERR("Failed to get pointer to RESET device: %s",
			DT_INST_0_AMS_CCS811_RESET_GPIOS_CONTROLLER);
		return -EINVAL;
	}
	gpio_pin_configure(drv_data->reset_gpio, DT_INST_0_AMS_CCS811_RESET_GPIOS_PIN,
			   GPIO_DIR_OUT);
	gpio_pin_write(drv_data->reset_gpio, DT_INST_0_AMS_CCS811_RESET_GPIOS_PIN, 1);

	k_sleep(1);
#endif

#ifdef DT_INST_0_AMS_CCS811_IRQ_GPIOS_CONTROLLER
	drv_data->int_gpio = device_get_binding(DT_INST_0_AMS_CCS811_IRQ_GPIOS_CONTROLLER);
	if (drv_data->int_gpio == NULL) {
		LOG_ERR("Failed to get pointer to INT device: %s",
			DT_INST_0_AMS_CCS811_IRQ_GPIOS_CONTROLLER);
		return -EINVAL;
	}
#endif

	/* Reset the device.  This saves having to deal with detecting
	 * and validating any errors or configuration inconsistencies
	 * after a reset that left the device running.
	 */
#ifdef DT_INST_0_AMS_CCS811_RESET_GPIOS_PIN
	gpio_pin_write(drv_data->reset_gpio, DT_INST_0_AMS_CCS811_RESET_GPIOS_PIN, 0);
	k_busy_wait(15);        /* t_RESET */
	gpio_pin_write(drv_data->reset_gpio, DT_INST_0_AMS_CCS811_RESET_GPIOS_PIN, 1);
#else
	{
		static u8_t const reset_seq[] = {
			0xFF, 0x11, 0xE5, 0x72, 0x8A,
		};

		if (i2c_write(drv_data->i2c, reset_seq, sizeof(reset_seq),
			      DT_INST_0_AMS_CCS811_BASE_ADDRESS) < 0) {
			LOG_ERR("Failed to issue SW reset");
			ret = -EIO;
			goto out;
		}
	}
#endif
	k_sleep(20);            /* t_START assuming recent power-on */

	/* Switch device to application mode */
	ret = switch_to_app_mode(drv_data->i2c);
	if (ret) {
		goto out;
	}

	/* Check Hardware ID */
	if (i2c_reg_read_byte(drv_data->i2c, DT_INST_0_AMS_CCS811_BASE_ADDRESS,
			      CCS811_REG_HW_ID, &hw_id) < 0) {
		LOG_ERR("Failed to read Hardware ID register");
		ret = -EIO;
		goto out;
	}

	if (hw_id != CCS881_HW_ID) {
		LOG_ERR("Hardware ID mismatch!");
		ret = -EINVAL;
		goto out;
	}

	/* Configure measurement mode */
	u8_t meas_mode = 0;
#ifdef CONFIG_CCS811_DRIVE_MODE_1
	meas_mode = 0x10;
#elif defined(CONFIG_CCS811_DRIVE_MODE_2)
	meas_mode = 0x20;
#elif defined(CONFIG_CCS811_DRIVE_MODE_3)
	meas_mode = 0x30;
#endif
	if (i2c_reg_write_byte(drv_data->i2c, DT_INST_0_AMS_CCS811_BASE_ADDRESS,
			       CCS811_REG_MEAS_MODE,
			       meas_mode) < 0) {
		LOG_ERR("Failed to set Measurement mode");
		ret = -EIO;
		goto out;
	}
	drv_data->mode = meas_mode;

	/* Check for error */
	status = fetch_status(drv_data->i2c);
	if (status < 0) {
		ret = -EIO;
		goto out;
	}

	if (status & CCS811_STATUS_ERROR) {
		LOG_ERR("CCS811 Error %02x during sensor configuration",
			error_from_status(status));
		ret = -EINVAL;
		goto out;
	}

#ifdef CONFIG_CCS811_TRIGGER
	ret = ccs811_init_interrupt(dev);
	LOG_DBG("CCS811 interrupt init got %d", ret);
#endif

out:
	set_wake(drv_data, false);
	return ret;
}

static struct ccs811_data ccs811_driver;

DEVICE_AND_API_INIT(ccs811, DT_INST_0_AMS_CCS811_LABEL, ccs811_init, &ccs811_driver,
		    NULL, POST_KERNEL, CONFIG_SENSOR_INIT_PRIORITY,
		    &ccs811_driver_api);
