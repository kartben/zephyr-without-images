/*
 * Copyright (c) 2022 Vestas Wind Systems A/S
 * Copyright (c) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/logging/log.h>
#include <zephyr/net/socket_can.h>
#include <zephyr/ztest.h>

LOG_MODULE_REGISTER(socket_can, LOG_LEVEL_ERR);

/**
 * @brief Test of @a can_copy_frame_to_zframe()
 */
ZTEST(socket_can, test_can_frame_to_zcan_frame)
{
	struct socketcan_frame frame = { 0 };
	struct zcan_frame expected = { 0 };
	struct zcan_frame msg;
	const uint8_t data[CAN_MAX_DLEN] = { 0x01, 0x02, 0x03, 0x04,
					  0x05, 0x06, 0x07, 0x08 };

	frame.can_id = BIT(31) | BIT(30) | 1234;
	frame.can_dlc = sizeof(data);
	memcpy(frame.data, data, sizeof(frame.data));

	expected.rtr = CAN_REMOTEREQUEST;
	expected.id_type = CAN_EXTENDED_IDENTIFIER;
	expected.id = 1234U;
	expected.dlc = sizeof(data);

	can_copy_frame_to_zframe(&frame, &msg);

	LOG_HEXDUMP_DBG((const uint8_t *)&frame, sizeof(frame), "frame");
	LOG_HEXDUMP_DBG((const uint8_t *)&msg, sizeof(msg), "msg");
	LOG_HEXDUMP_DBG((const uint8_t *)&expected, sizeof(expected), "expected");

	zassert_equal(msg.rtr, expected.rtr, "RTR bit not set");
	zassert_equal(msg.id_type, expected.id_type, "Id-type bit not set");
	zassert_equal(msg.id, expected.id, "CAN id invalid");
	zassert_equal(msg.dlc, expected.dlc, "Msg length invalid");
}

/**
 * @brief Test of @a can_copy_zframe_to_frame()
 */
ZTEST(socket_can, test_zcan_frame_to_can_frame)
{
	struct socketcan_frame frame = { 0 };
	struct socketcan_frame expected = { 0 };
	struct zcan_frame msg = { 0 };
	const uint8_t data[CAN_MAX_DLEN] = { 0x01, 0x02, 0x03, 0x04,
					  0x05, 0x06, 0x07, 0x08 };

	expected.can_id = BIT(31) | BIT(30) | 1234;
	expected.can_dlc = sizeof(data);
	memcpy(expected.data, data, sizeof(expected.data));

	msg.rtr = CAN_REMOTEREQUEST;
	msg.id_type = CAN_EXTENDED_IDENTIFIER;
	msg.id = 1234U;
	msg.dlc = sizeof(data);
	memcpy(msg.data, data, sizeof(data));

	can_copy_zframe_to_frame(&msg, &frame);

	LOG_HEXDUMP_DBG((const uint8_t *)&frame, sizeof(frame), "frame");
	LOG_HEXDUMP_DBG((const uint8_t *)&msg, sizeof(msg), "msg");
	LOG_HEXDUMP_DBG((const uint8_t *)&expected, sizeof(expected), "expected");

	zassert_equal(frame.can_id, expected.can_id, "CAN ID not same");
	zassert_mem_equal(&frame.data, &expected.data, sizeof(frame.data),
			  "CAN data not same");
	zassert_equal(frame.can_dlc, expected.can_dlc,
		      "CAN msg length not same");
}

/**
 * @brief Test of @a can_copy_filter_to_zfilter()
 */
ZTEST(socket_can, test_can_filter_to_zcan_filter)
{
	struct socketcan_filter filter = { 0 };
	struct zcan_filter expected = { 0 };
	struct zcan_filter msg_filter = { 0 };

	filter.can_id = BIT(31) | BIT(30) | 1234;
	filter.can_mask = BIT(31) | BIT(30) | 1234;

	expected.rtr = CAN_REMOTEREQUEST;
	expected.id_type = CAN_EXTENDED_IDENTIFIER;
	expected.id = 1234U;
	expected.rtr_mask = 1U;
	expected.id_mask = 1234U;

	can_copy_filter_to_zfilter(&filter, &msg_filter);

	LOG_HEXDUMP_DBG((const uint8_t *)&msg_filter, sizeof(msg_filter),
			"msg_filter");
	LOG_HEXDUMP_DBG((const uint8_t *)&filter, sizeof(filter), "filter");
	LOG_HEXDUMP_DBG((const uint8_t *)&expected, sizeof(expected), "expected");

	zassert_equal(msg_filter.rtr, expected.rtr, "RTR bit not set");
	zassert_equal(msg_filter.id_type, expected.id_type,
		      "Id-type bit not set");
	zassert_equal(msg_filter.id, expected.id,
		      "CAN id invalid");
	zassert_equal(msg_filter.rtr_mask, expected.rtr_mask,
		      "RTR mask bit not set");
	zassert_equal(msg_filter.id_mask, expected.id_mask,
		      "id mask not set");
}

/**
 * @brief Test of @a can_copy_zfilter_to_filter()
 */
ZTEST(socket_can, test_zcan_filter_to_can_filter)
{
	struct socketcan_filter filter = { 0 };
	struct socketcan_filter expected = { 0 };
	struct zcan_filter msg_filter = { 0 };

	expected.can_id = BIT(31) | BIT(30) | 1234;
	expected.can_mask = BIT(31) | BIT(30) | 1234;

	msg_filter.rtr = CAN_REMOTEREQUEST;
	msg_filter.id_type = CAN_EXTENDED_IDENTIFIER;
	msg_filter.id = 1234U;
	msg_filter.rtr_mask = 1U;
	msg_filter.id_mask = 1234U;

	can_copy_zfilter_to_filter(&msg_filter, &filter);

	LOG_HEXDUMP_DBG((const uint8_t *)&msg_filter, sizeof(msg_filter),
			"msg_filter");
	LOG_HEXDUMP_DBG((const uint8_t *)&filter, sizeof(filter), "filter");
	LOG_HEXDUMP_DBG((const uint8_t *)&expected, sizeof(expected), "expected");

	zassert_equal(filter.can_id, expected.can_id, "CAN ID not same");
	zassert_equal(filter.can_mask, expected.can_mask, "CAN mask not same");
}

ZTEST_SUITE(socket_can, NULL, NULL, NULL, NULL, NULL);
