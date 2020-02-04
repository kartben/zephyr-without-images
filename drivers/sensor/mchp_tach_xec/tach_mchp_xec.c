/*
 * Copyright (c) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <errno.h>
#include <device.h>
#include <drivers/sensor.h>
#include <soc.h>
#include <logging/log.h>

LOG_MODULE_REGISTER(tach_xec, CONFIG_SENSOR_LOG_LEVEL);

struct tach_xec_config {
	u32_t base_address;
};

struct tach_xec_data {
	u16_t count;
};

#define FAN_STOPPED		0xFFFFU
#define COUNT_100KHZ_SEC	100000U
#define SEC_TO_MINUTE		60U
#define PIN_STS_TIMEOUT		20U

#define TACH_XEC_REG_BASE(_dev)				\
	((TACH_Type *)					\
	 ((const struct tach_xec_config * const)	\
	  _dev->config->config_info)->base_address)

#define TACH_XEC_CONFIG(_dev)				\
	(((const struct counter_xec_config * const)	\
	  _dev->config->config_info))

#define TACH_XEC_DATA(_dev)				\
	((struct tach_xec_data *)dev->driver_data)


int tach_xec_sample_fetch(struct device *dev, enum sensor_channel chan)
{
	ARG_UNUSED(chan);

	TACH_Type *tach = TACH_XEC_REG_BASE(dev);
	struct tach_xec_data *data = TACH_XEC_DATA(dev);
	u8_t poll_count = 0;

	while (poll_count < PIN_STS_TIMEOUT) {
		/* See whether internal counter is already latched */
		if (tach->STATUS & MCHP_TACH_STS_CNT_RDY) {
			data->count =
				tach->CONTROL >> MCHP_TACH_CTRL_COUNTER_POS;
			break;
		}

		poll_count++;

		/* Allow other threads to run while we sleep */
		k_usleep(USEC_PER_MSEC);
	}

	if (poll_count == PIN_STS_TIMEOUT) {
		return -EINVAL;
	}

	/* We interprept a fan stopped or jammed as 0 */
	if (data->count == FAN_STOPPED) {
		data->count = 0U;
	}

	return 0;
}

static int tach_xec_channel_get(struct device *dev,
				enum sensor_channel chan,
				struct sensor_value *val)
{
	struct tach_xec_data *data = TACH_XEC_DATA(dev);

	if (chan != SENSOR_CHAN_RPM) {
		return -ENOTSUP;
	}

	/* Convert the count per 100khz cycles to rpm */
	if (data->count != FAN_STOPPED && data->count != 0U) {
		val->val1 = (SEC_TO_MINUTE * COUNT_100KHZ_SEC)/data->count;
		val->val2 = 0U;
	} else {
		val->val1 =  0U;
	}

	val->val2 = 0U;

	return 0;
}

static int tach_xec_init(struct device *dev)
{
	TACH_Type *tach = TACH_XEC_REG_BASE(dev);

	tach->CONTROL = MCHP_TACH_CTRL_READ_MODE_100K_CLOCK	|
			MCHP_TACH_CTRL_EDGES_5			|
			MCHP_TACH_CTRL_FILTER_EN		|
			MCHP_TACH_CTRL_EN;

	return 0;
}

static const struct sensor_driver_api tach_xec_driver_api = {
	.sample_fetch = tach_xec_sample_fetch,
	.channel_get = tach_xec_channel_get,
};

#define TACH_XEC_DEVICE(id)						\
	static const struct tach_xec_config tach_xec_dev_config##id = {	\
		.base_address =						\
		DT_INST_##id##_MICROCHIP_XEC_TACH_BASE_ADDRESS,		\
	};								\
									\
	static struct tach_xec_data tach_xec_dev_data##id;		\
									\
	DEVICE_AND_API_INIT(tach##id,					\
			    DT_INST_##id##_MICROCHIP_XEC_TACH_LABEL,	\
			    tach_xec_init,				\
			    &tach_xec_dev_data##id,			\
			    &tach_xec_dev_config##id,			\
			    POST_KERNEL,				\
			    CONFIG_SENSOR_INIT_PRIORITY,		\
			    &tach_xec_driver_api)			\

#ifdef DT_INST_0_MICROCHIP_XEC_TACH
TACH_XEC_DEVICE(0);
#endif

#ifdef DT_INST_1_MICROCHIP_XEC_TACH
TACH_XEC_DEVICE(1);
#endif

#ifdef DT_INST_2_MICROCHIP_XEC_TACH
TACH_XEC_DEVICE(2);
#endif

#ifdef DT_INST_3_MICROCHIP_XEC_TACH
TACH_XEC_DEVICE(3);
#endif
