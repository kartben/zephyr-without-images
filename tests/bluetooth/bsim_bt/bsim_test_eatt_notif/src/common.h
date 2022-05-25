/**
 * Common functions and helpers for BSIM EATT notification tests
 *
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>

#include "bs_types.h"
#include "bs_tracing.h"
#include "time_machine.h"
#include "bstests.h"

#include <zephyr/types.h>
#include <stddef.h>
#include <errno.h>
#include <zephyr/zephyr.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include "bs_pc_backchannel.h"

extern enum bst_result_t bst_result;

#define WAIT_TIME (30 * 1e6) /*seconds*/

#define CREATE_FLAG(flag) static atomic_t flag = (atomic_t)false
#define SET_FLAG(flag) (void)atomic_set(&flag, (atomic_t)true)
#define UNSET_FLAG(flag) (void)atomic_set(&flag, (atomic_t)false)
#define TEST_FLAG(flag) (atomic_get(&flag) == (atomic_t)true)
#define WAIT_FOR_FLAG(flag) \
	while (!(bool)atomic_get(&flag)) { \
		(void)k_sleep(K_MSEC(1)); \
	}

#define FAIL(...) \
	do { \
		bst_result = Failed; \
		bs_trace_error_time_line(__VA_ARGS__); \
	} while (0)

#define PASS(...) \
	do { \
		bst_result = Passed; \
		bs_trace_info_time(1, __VA_ARGS__); \
	} while (0)

#define CHRC_SIZE 10
#define LONG_CHRC_SIZE 40

#define TEST_SERVICE_UUID \
	BT_UUID_DECLARE_128(0x01, 0x23, 0x45, 0x67, 0x89, 0x01, 0x02, 0x03, \
			    0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x00, 0x00)

#define TEST_CHRC_UUID \
	BT_UUID_DECLARE_128(0x01, 0x23, 0x45, 0x67, 0x89, 0x01, 0x02, 0x03, \
			    0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xFF, 0x00)

#define TEST_LONG_CHRC_UUID \
	BT_UUID_DECLARE_128(0x01, 0x23, 0x45, 0x67, 0x89, 0x01, 0x02, 0x03, \
			    0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xFF, 0x11)

#define CENTRAL_ID 0
#define PERIPHERAL_ID 1
#define BACK_CHANNELS 1

void test_tick(bs_time_t HW_device_time);
void test_init(void);
void device_sync_init(uint device_nbr);
void device_sync_send(void);
void device_sync_wait(void);
