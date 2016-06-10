/** @file
 *  @brief Bluetooth UUID handling
 */

/*
 * Copyright (c) 2015-2016 Intel Corporation
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
#ifndef __BT_UUID_H
#define __BT_UUID_H

/**
 * @brief UUIDs
 * @defgroup bt_uuid UUIDs
 * @ingroup bluetooth
 * @{
 */

#include <misc/util.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Bluetooth UUID types */
enum {
	BT_UUID_TYPE_16,
	BT_UUID_TYPE_128,
};

/** @brief This is a 'tentative' type and should be used as a pointer only */
struct bt_uuid {
	uint8_t type;
};

struct bt_uuid_16 {
	struct bt_uuid uuid;
	uint16_t val;
};

struct bt_uuid_128 {
	struct bt_uuid uuid;
	uint8_t val[16];
};

#define BT_UUID_INIT_16(value)		\
{					\
	.uuid.type = BT_UUID_TYPE_16,	\
	.val = (value),			\
}

#define BT_UUID_INIT_128(value...)	\
{					\
	.uuid.type = BT_UUID_TYPE_128,	\
	.val = { value },		\
}

#define BT_UUID_DECLARE_16(value) \
	((struct bt_uuid *) (&(struct bt_uuid_16) BT_UUID_INIT_16(value)))
#define BT_UUID_DECLARE_128(value...) \
	((struct bt_uuid *) (&(struct bt_uuid_128) BT_UUID_INIT_128(value)))

#define BT_UUID_16(__u) CONTAINER_OF(__u, struct bt_uuid_16, uuid)
#define BT_UUID_128(__u) CONTAINER_OF(__u, struct bt_uuid_128, uuid)

/** @def BT_UUID_GAP
 *  @brief Generic Access
 */
#define BT_UUID_GAP				BT_UUID_DECLARE_16(0x1800)
#define BT_UUID_GAP_VAL				0x1800
/** @def BT_UUID_GATT
 *  @brief Generic Attribute
 */
#define BT_UUID_GATT				BT_UUID_DECLARE_16(0x1801)
#define BT_UUID_GATT_VAL			0x1801
/** @def BT_UUID_CTS
 *  @brief Current Time Service
 */
#define BT_UUID_CTS				BT_UUID_DECLARE_16(0x1805)
#define BT_UUID_CTS_VAL				0x1805
/** @def BT_UUID_DIS
 *  @brief Device Information Service
 */
#define BT_UUID_DIS				BT_UUID_DECLARE_16(0x180a)
#define BT_UUID_DIS_VAL				0x180a
/** @def BT_UUID_HRS
 *  @brief Heart Rate Service
 */
#define BT_UUID_HRS				BT_UUID_DECLARE_16(0x180d)
#define BT_UUID_HRS_VAL				0x180d
/** @def BT_UUID_BAS
 *  @brief Battery Service
 */
#define BT_UUID_BAS				BT_UUID_DECLARE_16(0x180f)
#define BT_UUID_BAS_VAL				0x180f
/** @def BT_UUID_CSC
 *  @brief Cycling Speed and Cadence Service
 */
#define BT_UUID_CSC				BT_UUID_DECLARE_16(0x1816)
#define BT_UUID_CSC_VAL				0x1816
/** @def BT_UUID_ESS
 *  @brief Environmental Sensing Service
 */
#define BT_UUID_ESS				BT_UUID_DECLARE_16(0x181a)
#define BT_UUID_ESS_VAL				0x181a
/** @def BT_UUID_IPSS
 *  @brief IP Support Service
 */
#define BT_UUID_IPSS				BT_UUID_DECLARE_16(0x1820)
#define BT_UUID_IPSS_VAL			0x1820
/** @def BT_UUID_GATT_PRIMARY
 *  @brief GATT Primary Service
 */
#define BT_UUID_GATT_PRIMARY			BT_UUID_DECLARE_16(0x2800)
#define BT_UUID_GATT_PRIMARY_VAL		0x2800
/** @def BT_UUID_GATT_SECONDARY
 *  @brief GATT Secondary Service
 */
#define BT_UUID_GATT_SECONDARY			BT_UUID_DECLARE_16(0x2801)
#define BT_UUID_GATT_SECONDARY_VAL		0x2801
/** @def BT_UUID_GATT_INCLUDE
 *  @brief GATT Include Service
 */
#define BT_UUID_GATT_INCLUDE			BT_UUID_DECLARE_16(0x2802)
#define BT_UUID_GATT_INCLUDE_VAL		0x2802
/** @def BT_UUID_GATT_CHRC
 *  @brief GATT Characteristic
 */
#define BT_UUID_GATT_CHRC			BT_UUID_DECLARE_16(0x2803)
#define BT_UUID_GATT_CHRC_VAL			0x2803
/** @def BT_UUID_GATT_CEP
 *  @brief GATT Characteristic Extended Properties
 */
#define BT_UUID_GATT_CEP			BT_UUID_DECLARE_16(0x2900)
#define BT_UUID_GATT_CEP_VAL			0x2900
/** @def BT_UUID_GATT_CUD
 *  @brief GATT Characteristic User Description
 */
#define BT_UUID_GATT_CUD			BT_UUID_DECLARE_16(0x2901)
#define BT_UUID_GATT_CUD_VAL			0x2901
/** @def BT_UUID_GATT_CCC
 *  @brief GATT Client Characteristic Configuration
 */
#define BT_UUID_GATT_CCC			BT_UUID_DECLARE_16(0x2902)
#define BT_UUID_GATT_CCC_VAL			0x2902
/** @def BT_UUID_GATT_SCC
 *  @brief GATT Server Characteristic Configuration
 */
#define BT_UUID_GATT_SCC			BT_UUID_DECLARE_16(0x2903)
#define BT_UUID_GATT_SCC_VAL			0x2903
/** @def BT_UUID_GATT_CPF
 *  @brief GATT Characteristic Presentation Format
 */
#define BT_UUID_GATT_CPF			BT_UUID_DECLARE_16(0x2904)
#define BT_UUID_GATT_CPF_VAL			0x2904
/** @def BT_UUID_VALID_RANGE
 *  @brief Valid Range Descriptor
 */
#define BT_UUID_VALID_RANGE			BT_UUID_DECLARE_16(0x2906)
#define BT_UUID_VALID_RANGE_VAL			0x2906
/** @def BT_UUID_ES_CONFIGURATION
 *  @brief Environmental Sensing Configuration Descriptor
 */
#define BT_UUID_ES_CONFIGURATION		BT_UUID_DECLARE_16(0x290b)
#define BT_UUID_ES_CONFIGURATION_VAL		0x290b
/** @def BT_UUID_ES_MEASUREMENT
 *  @brief Environmental Sensing Measurement Descriptor
 */
#define BT_UUID_ES_MEASUREMENT			BT_UUID_DECLARE_16(0x290c)
#define BT_UUID_ES_MEASUREMENT_VAL		0x290c
/** @def BT_UUID_ES_TRIGGER_SETTING
 *  @brief Environmental Sensing Trigger Setting Descriptor
 */
#define BT_UUID_ES_TRIGGER_SETTING		BT_UUID_DECLARE_16(0x290d)
#define BT_UUID_ES_TRIGGER_SETTING_VAL		0x290d
/** @def BT_UUID_GAP_DEVICE_NAME
 *  @brief GAP Characteristic Device Name
 */
#define BT_UUID_GAP_DEVICE_NAME			BT_UUID_DECLARE_16(0x2a00)
#define BT_UUID_GAP_DEVICE_NAME_VAL		0x2a00
/** @def BT_UUID_GAP_APPEARANCE
 *  @brief GAP Characteristic Appearance
 */
#define BT_UUID_GAP_APPEARANCE			BT_UUID_DECLARE_16(0x2a01)
#define BT_UUID_GAP_APPEARANCE_VAL		0x2a01
/** @def BT_UUID_GAP_PPCP
 *  @brief GAP Characteristic Peripheral Preferred Connection Parameters
 */
#define BT_UUID_GAP_PPCP			BT_UUID_DECLARE_16(0x2a04)
#define BT_UUID_GAP_PPCP_VAL			0x2a04
/** @def BT_UUID_BAS_BATTERY_LEVEL
 *  @brief BAS Characteristic Battery Level
 */
#define BT_UUID_BAS_BATTERY_LEVEL		BT_UUID_DECLARE_16(0x2a19)
#define BT_UUID_BAS_BATTERY_LEVEL_VAL		0x2a19
/** @def BT_UUID_DIS_SYSTEM_ID
 *  @brief DIS Characteristic System ID
 */
#define BT_UUID_DIS_SYSTEM_ID			BT_UUID_DECLARE_16(0x2a23)
#define BT_UUID_DIS_SYSTEM_ID_VAL		0x2a23
/** @def BT_UUID_DIS_MODEL_NUMBER
 *  @brief DIS Characteristic Model Number String
 */
#define BT_UUID_DIS_MODEL_NUMBER		BT_UUID_DECLARE_16(0x2a24)
#define BT_UUID_DIS_MODEL_NUMBER_VAL		0x2a24
/** @def BT_UUID_DIS_SERIAL_NUMBER
 *  @brief DIS Characteristic Serial Number String
 */
#define BT_UUID_DIS_SERIAL_NUMBER		BT_UUID_DECLARE_16(0x2a25)
#define BT_UUID_DIS_SERIAL_NUMBER_VAL		0x2a25
/** @def BT_UUID_DIS_FIRMWARE_REVISION
 *  @brief DIS Characteristic Firmware Revision String
 */
#define BT_UUID_DIS_FIRMWARE_REVISION		BT_UUID_DECLARE_16(0x2a26)
#define BT_UUID_DIS_FIRMWARE_REVISION_VAL	0x2a26
/** @def BT_UUID_DIS_HARDWARE_REVISION
 *  @brief DIS Characteristic Hardware Revision String
 */
#define BT_UUID_DIS_HARDWARE_REVISION		BT_UUID_DECLARE_16(0x2a27)
#define BT_UUID_DIS_HARDWARE_REVISION_VAL	0x2a27
/** @def BT_UUID_DIS_SOFTWARE_REVISION
 *  @brief DIS Characteristic Software Revision String
 */
#define BT_UUID_DIS_SOFTWARE_REVISION		BT_UUID_DECLARE_16(0x2a28)
#define BT_UUID_DIS_SOFTWARE_REVISION_VAL	0x2a28
/** @def BT_UUID_DIS_MANUFACTURER_NAME
 *  @brief DIS Characteristic Manufacturer Name String
 */
#define BT_UUID_DIS_MANUFACTURER_NAME		BT_UUID_DECLARE_16(0x2a29)
#define BT_UUID_DIS_MANUFACTURER_NAME_VAL	0x2a29
/** @def BT_UUID_DIS_PNP_ID
 *  @brief DIS Characteristic PnP ID
 */
#define BT_UUID_DIS_PNP_ID			BT_UUID_DECLARE_16(0x2a50)
#define BT_UUID_DIS_PNP_ID_VAL			0x2a50
/** @def BT_UUID_CTS_CURRENT_TIME
 *  @brief CTS Characteristic Current Time
 */
#define BT_UUID_CTS_CURRENT_TIME		BT_UUID_DECLARE_16(0x2a2b)
#define BT_UUID_CTS_CURRENT_TIME_VAL		0x2a2b
/** @def BT_UUID_MAGN_DECLINATION
 *  @brief Magnetic Declination Characteristic
 */
#define BT_UUID_MAGN_DECLINATION		BT_UUID_DECLARE_16(0x2a2c)
#define BT_UUID_MAGN_DECLINATION_VAL		0x2a2c
/** @def BT_UUID_HRS_MEASUREMENT
 *  @brief HRS Characteristic Measurement Interval
 */
#define BT_UUID_HRS_MEASUREMENT			BT_UUID_DECLARE_16(0x2a37)
#define BT_UUID_HRS_MEASUREMENT_VAL		0x2a37
/** @def BT_UUID_HRS_BODY_SENSOR
 *  @brief HRS Characteristic Body Sensor Location
 */
#define BT_UUID_HRS_BODY_SENSOR			BT_UUID_DECLARE_16(0x2a38)
#define BT_UUID_HRS_BODY_SENSOR_VAL		0x2a38
/** @def BT_UUID_HRS_CONTROL_POINT
 *  @brief HRS Characteristic Control Point
 */
#define BT_UUID_HRS_CONTROL_POINT		BT_UUID_DECLARE_16(0x2a39)
#define BT_UUID_HRS_CONTROL_POINT_VAL		0x2a39
/** @def BT_UUID_CSC_MEASUREMENT
 *  @brief CSC Measurement Characteristic
 */
#define BT_UUID_CSC_MEASUREMENT			BT_UUID_DECLARE_16(0x2a5b)
#define BT_UUID_CSC_MEASUREMENT_VAL		0x2a5b
/** @def BT_UUID_CSC_FEATURE
 *  @brief CSC Feature Characteristic
 */
#define BT_UUID_CSC_FEATURE			BT_UUID_DECLARE_16(0x2a5c)
#define BT_UUID_CSC_FEATURE_VAL			0x2a5c
/** @def BT_UUID_SENSOR_LOCATION
 *  @brief Sensor Location Characteristic
 */
#define BT_UUID_SENSOR_LOCATION			BT_UUID_DECLARE_16(0x2a5d)
#define BT_UUID_SENSOR_LOCATION_VAL		0x2a5d
/** @def BT_UUID_SC_CONTROL_POINT
 *  @brief SC Control Point Characteristic
 */
#define BT_UUID_SC_CONTROL_POINT		BT_UUID_DECLARE_16(0x2a55)
#define BT_UUID_SC_CONTROL_POINT_VAl		0x2a55
/** @def BT_UUID_ELEVATION
 *  @brief Elevation Characteristic
 */
#define BT_UUID_ELEVATION			BT_UUID_DECLARE_16(0x2a6c)
#define BT_UUID_ELEVATION_VAL			0x2a6c
/** @def BT_UUID_PRESSURE
 *  @brief Pressure Characteristic
 */
#define BT_UUID_PRESSURE			BT_UUID_DECLARE_16(0x2a6d)
#define BT_UUID_PRESSURE_VAL			0x2a6d
/** @def BT_UUID_TEMPERATURE
 *  @brief Temperature Characteristic
 */
#define BT_UUID_TEMPERATURE			BT_UUID_DECLARE_16(0x2a6e)
#define BT_UUID_TEMPERATURE_VAL			0x2a6e
/** @def BT_UUID_HUMIDITY
 *  @brief Humidity Characteristic
 */
#define BT_UUID_HUMIDITY			BT_UUID_DECLARE_16(0x2a6f)
#define BT_UUID_HUMIDITY_VAL			0x2a6f
/** @def BT_UUID_TRUE_WIND_SPEED
 *  @brief True Wind Speed Characteristic
 */
#define BT_UUID_TRUE_WIND_SPEED			BT_UUID_DECLARE_16(0x2a70)
#define BT_UUID_TRUE_WIND_SPEED_VAL		0x2a70
/** @def BT_UUID_TRUE_WIND_DIR
 *  @brief True Wind Direction Characteristic
 */
#define BT_UUID_TRUE_WIND_DIR			BT_UUID_DECLARE_16(0x2a71)
#define BT_UUID_TRUE_WIND_DIR_VAL		0x2a71
/** @def BT_UUID_APPARENT_WIND_SPEED
 *  @brief Apparent Wind Speed Characteristic
 */
#define BT_UUID_APPARENT_WIND_SPEED		BT_UUID_DECLARE_16(0x2a72)
#define BT_UUID_APPARENT_WIND_SPEED_VAL		0x2a72
/** @def BT_UUID_APPARENT_WIND_DIR
 *  @brief Apparent Wind Direction Characteristic
 */
#define BT_UUID_APPARENT_WIND_DIR		BT_UUID_DECLARE_16(0x2a73)
#define BT_UUID_APPARENT_WIND_DIR_VAL		0x2a73
/** @def BT_UUID_GUST_FACTOR
 *  @brief Gust Factor Characteristic
 */
#define BT_UUID_GUST_FACTOR			BT_UUID_DECLARE_16(0x2a74)
#define BT_UUID_GUST_FACTOR_VAL			0x2a74
/** @def BT_UUID_POLLEN_CONCENTRATION
 *  @brief Pollen Concentration Characteristic
 */
#define BT_UUID_POLLEN_CONCENTRATION		BT_UUID_DECLARE_16(0x2a75)
#define BT_UUID_POLLEN_CONCENTRATION_VAL	0x2a75
/** @def BT_UUID_UV_INDEX
 *  @brief UV Index Characteristic
 */
#define BT_UUID_UV_INDEX			BT_UUID_DECLARE_16(0x2a76)
#define BT_UUID_UV_INDEX_VAL			0x2a76
/** @def BT_UUID_IRRADIANCE
 *  @brief Irradiance Characteristic
 */
#define BT_UUID_IRRADIANCE			BT_UUID_DECLARE_16(0x2a77)
#define BT_UUID_IRRADIANCE_VAL			0x2a77
/** @def BT_UUID_RAINFALL
 *  @brief Rainfall Characteristic
 */
#define BT_UUID_RAINFALL			BT_UUID_DECLARE_16(0x2a78)
#define BT_UUID_RAINFALL_VAL			0x2a78
/** @def BT_UUID_WIND_CHILL
 *  @brief Wind Chill Characteristic
 */
#define BT_UUID_WIND_CHILL			BT_UUID_DECLARE_16(0x2a79)
#define BT_UUID_WIND_CHILL_VAL			0x2a79
/** @def BT_UUID_HEAT_INDEX
 *  @brief Heat Index Characteristic
 */
#define BT_UUID_HEAT_INDEX			BT_UUID_DECLARE_16(0x2a7a)
#define BT_UUID_HEAT_INDEX_VAL			0x2a7a
/** @def BT_UUID_DEW_POINT
 *  @brief Dew Point Characteristic
 */
#define BT_UUID_DEW_POINT			BT_UUID_DECLARE_16(0x2a7b)
#define BT_UUID_DEW_POINT_VAL			0x2a7b
/** @def BT_UUID_DESC_VALUE_CHANGED
 *  @brief Descriptor Value Changed Characteristic
 */
#define BT_UUID_DESC_VALUE_CHANGED		BT_UUID_DECLARE_16(0x2a7d)
#define BT_UUID_DESC_VALUE_CHANGED_VAL		0x2a7d
/** @def BT_UUID_MAGN_FLUX_DENSITY_2D
 *  @brief Magnetic Flux Density - 2D Characteristic
 */
#define BT_UUID_MAGN_FLUX_DENSITY_2D		BT_UUID_DECLARE_16(0x2aa0)
#define BT_UUID_MAGN_FLUX_DENSITY_2D_VAL	0x2aa0
/** @def BT_UUID_MAGN_FLUX_DENSITY_3D
 *  @brief Magnetic Flux Density - 3D Characteristic
 */
#define BT_UUID_MAGN_FLUX_DENSITY_3D		BT_UUID_DECLARE_16(0x2aa1)
#define BT_UUID_MAGN_FLUX_DENSITY_3D_VAL	0x2aa1
/** @def BT_UUID_BAR_PRESSURE_TREND
 *  @brief Barometric Pressure Trend Characteristic
 */
#define BT_UUID_BAR_PRESSURE_TREND		BT_UUID_DECLARE_16(0x2aa3)
#define BT_UUID_BAR_PRESSURE_TREND_VAL		0x2aa3

/** @brief Compare Bluetooth UUIDs.
 *
 *  Compares 2 Bluetooth UUIDs, if the types are different both UUIDs are
 *  first converted to 128 bits format before comparing.
 *
 *  @param u1 First Bluetooth UUID to compare
 *  @param u2 Second Bluetooth UUID to compare
 *
 *  @return negative value if @a u1 < @a u2, 0 if @a u1 == @a u2, else positive
 */
int bt_uuid_cmp(const struct bt_uuid *u1, const struct bt_uuid *u2);

#if defined(CONFIG_BLUETOOTH_DEBUG)
/** @brief Convert Bluetooth UUID to string.
 *
 *  Converts Bluetooth UUID to string. UUID has to be in 16 bits or 128 bits
 *  format.
 *
 *  @param uuid Bluetooth UUID
 *  @param str pointer where to put converted string
 *  @param len length of str
 *
 *  @return N/A
 */
void bt_uuid_to_str(const struct bt_uuid *uuid, char *str, size_t len);

/** @brief Convert Bluetooth UUID to string in place.
 *
 *  Converts Bluetooth UUID to string in place. UUID has to be in 16 bits or
 *  128 bits format.
 *
 *  @param uuid Bluetooth UUID
 *
 *  @return String representation of the UUID given
 */
const char *bt_uuid_str(const struct bt_uuid *uuid);
#else
static inline void bt_uuid_to_str(const struct bt_uuid *uuid, char *str,
				  size_t len)
{
	if (len > 0) {
		str[0] = '\0';
	}
}

static inline const char *bt_uuid_str(const struct bt_uuid *uuid)
{
	return "";
}
#endif /* CONFIG_BLUETOOTH_DEBUG */

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* __BT_UUID_H */
