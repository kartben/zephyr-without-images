/* Bluetooth: Mesh Generic OnOff, Generic Level, Lighting & Vendor Models
 *
 * Copyright (c) 2018 Vikrant More
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _DEVICE_COMPOSITION_H
#define _DEVICE_COMPOSITION_H

#define CID_ZEPHYR 0x0002

#define STATE_OFF	0x00
#define STATE_ON	0x01
#define STATE_DEFAULT	0x01
#define STATE_RESTORE	0x02

/* Following 4 values are as per Mesh Model specification */
#define LIGHTNESS_MIN	0x0001
#define LIGHTNESS_MAX	0xFFFF
#define TEMP_MIN	0x0320
#define TEMP_MAX	0x4E20

/* Refer 7.2 of Mesh Model Specification */
#define RANGE_SUCCESSFULLY_UPDATED	0x00
#define CANNOT_SET_RANGE_MIN		0x01
#define CANNOT_SET_RANGE_MAX		0x02

enum lightness {
	ONPOWERUP = 0x01,
	ONOFF,
	LEVEL,
	DELTA_LEVEL,
	ACTUAL,
	LINEAR,
	CTL,
	IGNORE
};

enum temperature {
	ONOFF_TEMP = 0x01,
	LEVEL_TEMP,
	CTL_TEMP,
	IGNORE_TEMP
};

enum target_values {
	ONOFF_TARGET = 0x01,
	LEVEL_LIGHT_TARGET,
	LIGHT_ACTUAL_TARGET,
	LIGHT_LINEAR_TARGET,
	LIGHT_CTL_TARGET,
	LEVEL_TEMP_TARGET,
	LIGHT_CTL_TEMP_TARGET
};

struct generic_onoff_state {
	u8_t onoff;
	u8_t target_onoff;

	u8_t last_tid;
	u16_t last_tx_addr;
	s64_t last_msg_timestamp;

	struct transition *transition;
};

struct generic_level_state {
	s16_t level;
	s16_t target_level;

	s16_t last_level;
	s32_t last_delta;

	u8_t last_tid;
	u16_t last_tx_addr;
	s64_t last_msg_timestamp;

	s32_t tt_delta;

	struct transition *transition;
};

struct generic_onpowerup_state {
	u8_t onpowerup;
	u8_t last_tid;
	u16_t last_tx_addr;
};

struct gen_def_trans_time_state {
	u8_t tt;
};

struct vendor_state {
	int current;
	u32_t response;
	u8_t last_tid;
	u16_t last_tx_addr;
	s64_t last_msg_timestamp;
};

struct light_lightness_state {
	u16_t linear;
	u16_t target_linear;

	u16_t actual;
	u16_t target_actual;

	u16_t last;
	u16_t def;

	u8_t status_code;
	u16_t light_range_min;
	u16_t light_range_max;

	u8_t last_tid;
	u16_t last_tx_addr;
	s64_t last_msg_timestamp;

	s32_t tt_delta_actual;
	s32_t tt_delta_linear;

	struct transition *transition;
};

struct light_ctl_state {
	u16_t lightness;
	u16_t target_lightness;

	u16_t temp;
	u16_t target_temp;

	s16_t delta_uv;
	s16_t target_delta_uv;

	u8_t status_code;
	u16_t temp_range_min;
	u16_t temp_range_max;

	u16_t lightness_def;
	u16_t temp_def;
	u32_t lightness_temp_def;
	s16_t delta_uv_def;

	u32_t lightness_temp_last;

	u8_t last_tid;
	u16_t last_tx_addr;
	s64_t last_msg_timestamp;

	s32_t tt_delta_lightness;
	s32_t tt_delta_temp;
	s32_t tt_delta_duv;

	struct transition *transition;
};

extern struct generic_onoff_state gen_onoff_srv_root_user_data;
extern struct generic_level_state gen_level_srv_root_user_data;
extern struct gen_def_trans_time_state gen_def_trans_time_srv_user_data;
extern struct generic_onpowerup_state gen_power_onoff_srv_user_data;
extern struct light_lightness_state light_lightness_srv_user_data;
extern struct light_ctl_state light_ctl_srv_user_data;
extern struct generic_level_state gen_level_srv_s0_user_data;

extern struct bt_mesh_model root_models[];
extern struct bt_mesh_model vnd_models[];
extern struct bt_mesh_model s0_models[];

extern const struct bt_mesh_comp comp;

void gen_onoff_publisher(struct bt_mesh_model *model);
void gen_level_publisher(struct bt_mesh_model *model);
void light_lightness_publisher(struct bt_mesh_model *model);
void light_lightness_linear_publisher(struct bt_mesh_model *model);
void light_ctl_publisher(struct bt_mesh_model *model);
void light_ctl_temp_publisher(struct bt_mesh_model *model);

#endif
