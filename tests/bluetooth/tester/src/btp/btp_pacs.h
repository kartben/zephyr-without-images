/* btp_bap.h - Bluetooth tester headers */

/*
 * Copyright (c) 2023 Codecoup
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* PACS commands */
#define BTP_PACS_READ_SUPPORTED_COMMANDS			0x01
struct btp_pacs_read_supported_commands_rp {
	uint8_t data[0];
} __packed;

#define BTP_PACS_CHARACTERISTIC_SINK_PAC			0x01
#define BTP_PACS_CHARACTERISTIC_SOURCE_PAC			0x02
#define BTP_PACS_CHARACTERISTIC_SINK_AUDIO_LOCATIONS		0x03
#define BTP_PACS_CHARACTERISTIC_SOURCE_AUDIO_LOCATIONS		0x04
#define BTP_PACS_CHARACTERISTIC_AVAILABLE_AUDIO_CONTEXTS	0x05
#define BTP_PACS_CHARACTERISTIC_SUPPORTED_AUDIO_CONTEXTS	0x06

#define BTP_PACS_UPDATE_CHARACTERISTIC	0x02
struct btp_pacs_update_characteristic_cmd {
	uint8_t characteristic;
} __packed;
