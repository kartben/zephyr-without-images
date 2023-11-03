/* Copyright (c) 2023 Codecoup
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/bluetooth/uuid.h>

#define TEST_SERVICE_UUID                                                                          \
	BT_UUID_DECLARE_128(0x1f, 0x5c, 0x31, 0x85, 0x05, 0xe8, 0x4d, 0x58, 0xb9, 0xf5, 0xae,      \
			    0xf1, 0x7a, 0x88, 0xbe, 0x82)
#define TEST_CHRC_UUID                                                                             \
	BT_UUID_DECLARE_128(0x68, 0xb4, 0x35, 0x19, 0x01, 0x65, 0x4d, 0xdc, 0xb9, 0xf3, 0x91,      \
			    0x0f, 0xf3, 0x18, 0x46, 0x7b)
