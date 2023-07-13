/*
 * Copyright (c) 2023 Google LLC
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/drivers/emul_sensor.h>
#include <zephyr/drivers/emul.h>
#include <zephyr/ztest.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/rtio/rtio.h>
#include <zephyr/sys/bitarray.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(generic_test);

/*
 * Set up an RTIO context that can be shared for all sensors
 */

static enum sensor_channel iodev_all_channels[SENSOR_CHAN_ALL];
static struct sensor_read_config iodev_read_config = {
	.channels = iodev_all_channels,
	.max = SENSOR_CHAN_ALL,
};
RTIO_IODEV_DEFINE(iodev_read, &__sensor_iodev_api, &iodev_read_config);

/* Create the RTIO context to service the reading */
RTIO_DEFINE_WITH_MEMPOOL(sensor_read_rtio_ctx, 1, 1, 1, 64, 4);

/**
 * @brief Prepare the RTIO context for next test
 */
static void before(void *args)
{
	ARG_UNUSED(args);

	/* Clear the array of requested channels */
	memset(iodev_all_channels, 0, sizeof(iodev_all_channels));

	/* Reset the channel count */
	iodev_read_config.count = 0;

	/* Remove previous sensor pointer */
	iodev_read_config.sensor = NULL;

	/* Wipe the mempool by marking every block free */
	zassert_ok(sys_bitarray_clear_region(sensor_read_rtio_ctx_block_pool.mempool->bitmap,
					     sensor_read_rtio_ctx_block_pool.mempool->num_blocks,
					     0));

	/* Flush the SQ and CQ */
	rtio_sqe_drop_all(&sensor_read_rtio_ctx);
	while (rtio_cqe_consume(&sensor_read_rtio_ctx))
		;
}

/**
 * @brief Helper function the carries out the generic sensor test for a given sensor device.
 *        Verifies that the device has a suitable emulator that implements the backend API and
 *        skips the test gracefully if not.
 */
static void run_generic_test(const struct device *dev)
{
	zassert_not_null(dev, "Cannot get device pointer. Is this driver properly instantiated?");

	const struct emul *emul = emul_get_binding(dev->name);

	/* Skip this sensor if there is no emulator loaded. */
	if (!emul) {
		ztest_test_skip();
	}

	/* Also skip if this emulator does not implement the backend API. */
	if (!emul_sensor_backend_is_supported(emul)) {
		ztest_test_skip();
	}

	/*
	 * Begin the actual test sequence
	 */

	static struct {
		bool supported;
		bool received;
		q31_t expected_values[CONFIG_GENERIC_SENSOR_TEST_NUM_EXPECTED_VALS];
		q31_t epsilon;
		int8_t expected_value_shift;
	} channel_table[SENSOR_CHAN_ALL];

	memset(channel_table, 0, sizeof(channel_table));

	/* Discover supported channels on this device and fill out our sensor read request */
	for (enum sensor_channel ch = 0; ch < ARRAY_SIZE(channel_table); ch++) {
		if (SENSOR_CHANNEL_3_AXIS(ch)) {
			continue;
		}

		q31_t lower, upper;
		int8_t shift;

		if (emul_sensor_backend_get_sample_range(emul, ch, &lower, &upper,
							 &channel_table[ch].epsilon, &shift) == 0) {
			/* This channel is supported */
			channel_table[ch].supported = true;

			LOG_INF("CH %d: lower=%d, upper=%d, eps=%d, shift=%d", ch, lower, upper,
				channel_table[ch].epsilon, shift);

			/* Add to the list of channels to read */
			iodev_all_channels[iodev_read_config.count++] = ch;

			/* Generate a set of CONFIG_GENERIC_SENSOR_TEST_NUM_EXPECTED_VALS test
			 * values.
			 */

			channel_table[ch].expected_value_shift = shift;
			for (size_t i = 0; i < CONFIG_GENERIC_SENSOR_TEST_NUM_EXPECTED_VALS; i++) {
				channel_table[ch].expected_values[i] =
					lower +
					(i * ((int64_t)upper - lower) /
					 (CONFIG_GENERIC_SENSOR_TEST_NUM_EXPECTED_VALS - 1));
				LOG_INF("CH %d: Expected value %d/%d: %d", ch, i + 1,
					CONFIG_GENERIC_SENSOR_TEST_NUM_EXPECTED_VALS,
					channel_table[ch].expected_values[i]);
			}
		}
	}
	iodev_read_config.sensor = dev;

	/* Do a read of all channels for quantity CONFIG_GENERIC_SENSOR_TEST_NUM_EXPECTED_VALS
	 * iterations.
	 */

	for (size_t iteration = 0; iteration < CONFIG_GENERIC_SENSOR_TEST_NUM_EXPECTED_VALS;
	     iteration++) {
		int rv;

		/* Reset received flag */
		for (size_t i = 0; i < ARRAY_SIZE(channel_table); i++) {
			channel_table[i].received = false;
		}

		/* Set this iteration's expected values in emul for every supported channel */
		for (size_t i = 0; i < iodev_read_config.count; i++) {
			enum sensor_channel ch = iodev_all_channels[i];

			rv = emul_sensor_backend_set_channel(
				emul, ch, channel_table[ch].expected_values[iteration],
				channel_table[ch].expected_value_shift);
			zassert_ok(
				rv,
				"Cannot set value 0x%08x on channel %d (error %d, iteration %d/%d)",
				channel_table[i].expected_values[iteration], ch, rv, iteration + 1,
				CONFIG_GENERIC_SENSOR_TEST_NUM_EXPECTED_VALS);
		}

		/* Perform the actual sensor read */
		rv = sensor_read(&iodev_read, &sensor_read_rtio_ctx, NULL);
		zassert_ok(rv, "Could not read sensor (error %d, iteration %d/%d)", rv,
			   iteration + 1, CONFIG_GENERIC_SENSOR_TEST_NUM_EXPECTED_VALS);

		/* Wait for a CQE */
		struct rtio_cqe *cqe = rtio_cqe_consume_block(&sensor_read_rtio_ctx);

		zassert_ok(cqe->result, "CQE has failed status (error %d, iteration %d/%d)",
			   cqe->result, iteration + 1,
			   CONFIG_GENERIC_SENSOR_TEST_NUM_EXPECTED_VALS);

		uint8_t *buf = NULL;
		uint32_t buf_len = 0;

		/* Cache the data from the CQE */
		rtio_cqe_get_mempool_buffer(&sensor_read_rtio_ctx, cqe, &buf, &buf_len);

		/* Release the CQE */
		rtio_cqe_release(&sensor_read_rtio_ctx, cqe);

		enum sensor_channel channel;
		sensor_frame_iterator_t fit = {0};
		sensor_channel_iterator_t cit = {0};
		const struct sensor_decoder_api *decoder;
		int8_t shift;
		q31_t q;

		zassert_ok(sensor_get_decoder(dev, &decoder));

		/* Decode the buffer and verify all channels */
		while (decoder->decode(buf, &fit, &cit, &channel, &q, 1) > 0) {
			zassert_true(channel_table[channel].supported);
			zassert_false(channel_table[channel].received);
			channel_table[channel].received = true;

			zassert_ok(decoder->get_shift(buf, channel, &shift));

			/* Align everything to be a 64-bit Q32.32 number for comparison */
			int64_t expected_shifted =
				(int64_t)channel_table[channel].expected_values[iteration]
				<< channel_table[channel].expected_value_shift;
			int64_t actual_shifted = (int64_t)q << shift;
			int64_t epsilon_shifted = (int64_t)channel_table[channel].epsilon
						  << channel_table[channel].expected_value_shift;

			zassert_within(expected_shifted, actual_shifted, epsilon_shifted,
				       "Expected %lld, got %lld (shift %d, ch %d, iteration %d/%d, "
				       "Error %lld, Epsilon %lld)",
				       expected_shifted, actual_shifted, shift, channel,
				       iteration + 1, CONFIG_GENERIC_SENSOR_TEST_NUM_EXPECTED_VALS,
				       expected_shifted - actual_shifted, epsilon_shifted);
		}

		/* Release the memory */
		rtio_release_buffer(&sensor_read_rtio_ctx, buf, buf_len);

		/* Ensure all supported channels were received */
		int missing_channel_count = 0;

		for (size_t i = 0; i < ARRAY_SIZE(channel_table); i++) {
			if (channel_table[i].supported && !channel_table[i].received) {
				missing_channel_count++;
			}
		}

		zassert_equal(0, missing_channel_count);
	}
}

#define DECLARE_ZTEST_PER_DEVICE(n)                                                                \
	ZTEST(generic, test_##n)                                                                   \
	{                                                                                          \
		run_generic_test(DEVICE_DT_GET(n));                                                \
	}

/* Iterate through each of the emulated buses and create a test for each device. */
DT_FOREACH_CHILD_STATUS_OKAY(DT_NODELABEL(test_i2c), DECLARE_ZTEST_PER_DEVICE)
DT_FOREACH_CHILD_STATUS_OKAY(DT_NODELABEL(test_spi), DECLARE_ZTEST_PER_DEVICE)

ZTEST_SUITE(generic, NULL, NULL, before, NULL, NULL);
