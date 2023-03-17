/*
 * Copyright (c) 2023 The ChromiumOS Authors
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/drivers/adc.h>
#include <zephyr/drivers/adc/adc_emul.h>
#include <zephyr/drivers/adc/voltage_divider.h>
#include <zephyr/kernel.h>
#include <zephyr/ztest.h>

/* Raw to millivolt conversion doesn't handle rounding */
#define MV_OUTPUT_EPS 10

#define ADC_TEST_NODE_0 DT_NODELABEL(sensor0)

/**
 * @brief Get ADC emulated device
 *
 * @return pointer to ADC device
 */
const struct device *get_adc_device(void)
{
	const struct device *const adc_dev = DEVICE_DT_GET(DT_NODELABEL(adc0));

	zassert_true(device_is_ready(adc_dev), "ADC device is not ready");

	return adc_dev;
}

static int init_adc(const struct adc_dt_spec *spec, int input_mv)
{
	int ret;

	zassert_true(device_is_ready(spec->dev), "ADC device is not ready");

	ret = adc_channel_setup_dt(spec);
	zassert_equal(ret, 0, "Setting up of the first channel failed with code %d", ret);

	/* ADC emulator-specific setup */
	ret = adc_emul_const_value_set(spec->dev, spec->channel_id, input_mv);
	zassert_ok(ret, "adc_emul_const_value_set() failed with code %d", ret);

	return ret;
}

/*
 * test_adc_voltage_divider
 */
static int test_task_voltage_divider(void)
{
	int ret;
	int32_t calculated_voltage = 0;
	int32_t input_mv = 1000;
	const struct voltage_divider_dt_spec adc_node_0 =
		VOLTAGE_DIVIDER_DT_SPEC_GET(ADC_TEST_NODE_0);

	ret = init_adc(&adc_node_0.port, input_mv);
	zassert_equal(ret, 0, "Setting up of the first channel failed with code %d", ret);

	struct adc_sequence sequence = {
		.buffer = &calculated_voltage,
		.buffer_size = sizeof(calculated_voltage),
	};
	adc_sequence_init_dt(&adc_node_0.port, &sequence);

	ret = adc_read(adc_node_0.port.dev, &sequence);
	zassert_equal(ret, 0, "adc_read() failed with code %d", ret);

	ret = adc_raw_to_millivolts_dt(&adc_node_0.port, &calculated_voltage);
	zassert_equal(ret, 0, "adc_raw_to_millivolts_dt() failed with code %d", ret);

	ret = voltage_divider_scale_dt(&adc_node_0, &calculated_voltage);
	zassert_equal(ret, 0, "divider_scale_voltage_dt() failed with code %d", ret);

	zassert_within(calculated_voltage, input_mv * 2, MV_OUTPUT_EPS,
		       "%u != %u should have set value", calculated_voltage, input_mv * 2);

	return TC_PASS;
}

ZTEST_USER(adc_rescale, test_adc_voltage_divider)
{
	zassert_true(test_task_voltage_divider() == TC_PASS);
}

void *adc_rescale_setup(void)
{
	k_object_access_grant(get_adc_device(), k_current_get());

	return NULL;
}

ZTEST_SUITE(adc_rescale, NULL, adc_rescale_setup, NULL, NULL, NULL);
