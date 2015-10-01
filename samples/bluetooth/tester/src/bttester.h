/* bttester.h - Bluetooth tester headers */

/*
 * Copyright (c) 2015 Intel Corporation
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

#define BTP_MTU 512

#define BTP_INDEX_NONE		0xff

#define BTP_SERVICE_ID_CORE	0
#define BTP_SERVICE_ID_GAP	1
#define BTP_SERVICE_ID_GATT	2

#define BTP_STATUS_SUCCESS	0x00
#define BTP_STATUS_FAILED	0x01
#define BTP_STATUS_UNKNOWN_CMD	0x02
#define BTP_STATUS_NOT_READY	0x03

#define BTP_BDADDR_BREDR	0x00
#define BTP_BDADDR_LE_PUBLIC	0x01
#define BTP_BDADDR_LE_RANDOM	0x02


struct btp_hdr {
	uint8_t  service;
	uint8_t  opcode;
	uint8_t  index;
	uint16_t len;
	uint8_t  data[0];
} __packed;

#define BTP_STATUS			0x00
struct btp_status {
	uint8_t code;
} __packed;

/* Core Service */
#define CORE_READ_SUPPORTED_COMMANDS	0x01
struct core_read_supported_commands_rp {
	uint8_t data[0];
};

#define CORE_READ_SUPPORTED_SERVICES	0x02
struct core_read_supported_services_rp {
	uint8_t data[0];
};

#define CORE_REGISTER_SERVICE		0x03
struct core_register_service_cmd {
	uint8_t id;
} __packed;

/* GAP Service */
/* commands */
#define GAP_READ_SUPPORTED_COMMANDS	0x01
struct gap_read_supported_commands_rp {
	uint8_t data[0];
};

#define GAP_READ_CONTROLLER_INDEX_LIST	0x02
struct gap_read_controller_index_list_rp {
	uint8_t num;
	uint8_t index[0];
};

#define GAP_SETTINGS_POWERED		0
#define GAP_SETTINGS_CONNECTABLE	1
#define GAP_SETTINGS_FAST_CONNECTABLE	2
#define GAP_SETTINGS_DISCOVERABLE	3
#define GAP_SETTINGS_BONDABLE		4
#define GAP_SETTINGS_LINK_SEC_3		5
#define GAP_SETTINGS_SSP		6
#define GAP_SETTINGS_BREDR		7
#define GAP_SETTINGS_HS			8
#define GAP_SETTINGS_LE			9
#define GAP_SETTINGS_ADVERTISING	10
#define GAP_SETTINGS_SC			11
#define GAP_SETTINGS_DEBUG_KEYS		12
#define GAP_SETTINGS_PRIVACY		13

#define GAP_READ_CONTROLLER_INFO	0x03
struct gap_read_controller_info_rp {
	uint8_t  address[6];
	uint32_t supported_settings;
	uint32_t current_settings;
	uint8_t  cod[3];
	uint8_t  name[249];
	uint8_t  short_name[11];
};

#define GAP_RESET			0x04
struct gap_reset_rp {
	uint32_t current_settings;
};

#define GAP_SET_POWERED			0x05
struct gap_set_powered_cmd {
	uint8_t powered;
};
struct gap_set_powered_rp {
	uint32_t current_settings;
};

#define GAP_SET_CONNECTABLE		0x06
struct gap_set_connectable_cmd {
	uint8_t connectable;
};
struct gap_set_connectable_rp {
	uint32_t current_settings;
};

#define GAP_SET_FAST_CONNECTABLE	0x07
struct gap_set_fast_connectable_cmd {
	uint8_t fast_connectable;
};
struct gap_set_fast_connectable_rp {
	uint32_t current_settings;
};

#define GAP_NON_DISCOVERABLE		0x00
#define GAP_GENERAL_DISCOVERABLE	0x01
#define GAP_LIMITED_DISCOVERABLE	0x02

#define GAP_SET_DISCOVERABLE		0x08
struct gap_set_discoverable_cmd {
	uint8_t discoverable;
};
struct gap_set_discoverable_rp {
	uint32_t current_settings;
};

#define GAP_SET_BONDABLE		0x09
struct gap_set_bondable_cmd {
	uint8_t gap_set_bondable_cmd;
};
struct gap_set_bondable_rp {
	uint32_t current_settings;
};

#define GAP_START_ADVERTISING	0x0a
struct gap_start_advertising_cmd {
	uint8_t adv_data_len;
	uint8_t scan_rsp_len;
	uint8_t adv_data[0];
	uint8_t scan_rsp[0];
} __packed;
struct gap_start_advertising_rp {
	uint32_t current_settings;
};

#define GAP_STOP_ADVERTISING		0x0b
struct gap_stop_advertising_rp {
	uint32_t current_settings;
};

#define GAP_DISCOVERY_FLAG_LE		0x01
#define GAP_DISCOVERY_FLAG_BREDR	0x02
#define GAP_DISCOVERY_FLAG_LIMITED	0x04

#define GAP_START_DISCOVERY		0x0c
struct gap_start_discovery_cmd {
	uint8_t flags;
} __packed;

#define GAP_STOP_DISCOVERY		0x0d

#define GAP_DISCONNECT			0x0f
struct gap_disconnect_cmd {
	uint8_t  address_type;
	uint8_t  address[6];
} __packed;

/* events */
#define GAP_EV_NEW_SETTINGS		0x80
struct gap_new_settings_ev {
	uint32_t current_settings;
};

#define GAP_DEVICE_FOUND_FLAG_RSSI	0x01
#define GAP_DEVICE_FOUND_FLAG_AD	0x02
#define GAP_DEVICE_FOUND_FLAG_SD	0x04

#define GAP_EV_DEVICE_FOUND		0x81
struct gap_device_found_ev {
	uint8_t  address[6];
	uint8_t  address_type;
	int8_t   rssi;
	uint8_t  flags;
	uint16_t eir_data_len;
	uint8_t  eir_data[0];
};

#define GAP_EV_DEVICE_CONNECTED		0x82
struct gap_device_connected_ev {
	uint8_t address[6];
	uint8_t address_type;
};

#define GAP_EV_DEVICE_DISCONNECTED	0x83
struct gap_device_disconnected_ev {
	uint8_t address[6];
	uint8_t address_type;
};

/* GATT Service */
/* commands */
#define GATT_READ_SUPPORTED_COMMANDS	0x01
struct gatt_read_supported_commands_rp {
	uint8_t data[0];
};

#define GATT_SERVICE_PRIMARY		0x00
#define GATT_SERVICE_SECONDARY		0x01

#define GATT_ADD_SERVICE		0x02
struct gatt_add_service_cmd {
	uint8_t type;
	uint8_t uuid_length;
	uint8_t uuid[0];
} __packed;
struct gatt_add_service_rp {
	uint16_t svc_id;
};

#define GATT_ADD_CHARACTERISTIC		0x03
struct gatt_add_characteristic_cmd {
	uint16_t svc_id;
	uint8_t properties;
	uint8_t permissions;
	uint8_t uuid_length;
	uint8_t uuid[0];
} __packed;
struct gatt_add_characteristic_rp {
	uint16_t char_id;
};

#define GATT_ADD_DESCRIPTOR		0x04
struct gatt_add_descriptor_cmd {
	uint16_t char_id;
	uint8_t permissions;
	uint8_t uuid_length;
	uint8_t uuid[0];
} __packed;
struct gatt_add_descriptor_rp {
	uint16_t desc_id;
} __packed;

#define GATT_ADD_INCLUDED_SERVICE	0x05
struct gatt_add_included_service_cmd {
	uint16_t svc_id;
} __packed;
struct gatt_add_included_service_rp {
	uint16_t included_service_id;
} __packed;

#define GATT_SET_VALUE			0x06
	struct gatt_set_value_cmd {
	uint16_t attr_id;
	uint16_t len;
	uint8_t value[0];
} __packed;

#define GATT_START_SERVER		0x07

void tester_init(void);
void tester_rsp(uint8_t service, uint8_t opcode, uint8_t index, uint8_t status);
void tester_rsp_full(uint8_t service, uint8_t opcode, uint8_t index,
		     uint8_t *data, size_t len);

uint8_t tester_init_gap(void);
void tester_handle_gap(uint8_t opcode, uint8_t index, uint8_t *data,
		       uint16_t len);
uint8_t tester_init_gatt(void);
void tester_handle_gatt(uint8_t opcode, uint8_t index, uint8_t *data,
			uint16_t len);
