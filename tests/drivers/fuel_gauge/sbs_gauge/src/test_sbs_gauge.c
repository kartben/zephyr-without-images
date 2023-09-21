/*
 * Copyright 2022 Google LLC
 * Copyright 2023 Microsoft Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/drivers/emul.h>
#include <zephyr/drivers/emul_fuel_gauge.h>
#include <zephyr/drivers/fuel_gauge.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/sys/util.h>
#include <zephyr/ztest.h>
#include <zephyr/ztest_assert.h>

#include "test_sbs_gauge.h"

static void *sbs_gauge_new_api_setup(void)
{
	static ZTEST_DMEM struct sbs_gauge_new_api_fixture fixture;

	fixture.dev = DEVICE_DT_GET_ANY(sbs_sbs_gauge_new_api);
	fixture.sbs_fuel_gauge = EMUL_DT_GET(DT_NODELABEL(smartbattery0));

	k_object_access_all_grant(fixture.dev);

	zassert_true(device_is_ready(fixture.dev), "Fuel Gauge not found");

	return &fixture;
}

ZTEST_USER_F(sbs_gauge_new_api, test_get_some_props_failed_returns_bad_status)
{
	struct fuel_gauge_property props[] = {
		{
			/* First invalid property */
			.property_type = FUEL_GAUGE_PROP_MAX,
		},
		{
			/* Second invalid property */
			.property_type = FUEL_GAUGE_PROP_MAX,
		},
		{
			/* Valid property */
			.property_type = FUEL_GAUGE_VOLTAGE,
		},

	};

	int ret = fuel_gauge_get_props(fixture->dev, props, ARRAY_SIZE(props));

	zassert_equal(ret, -ENOTSUP, "Getting bad property has a good status.");
}

ZTEST_USER_F(sbs_gauge_new_api, test_set_all_props_failed_returns_err)
{
	struct fuel_gauge_property props[] = {
		{
			/* Invalid property */
			.property_type = FUEL_GAUGE_PROP_MAX,
		},
	};

	int ret = fuel_gauge_set_props(fixture->dev, props, ARRAY_SIZE(props));

	zassert_equal(ret, -ENOTSUP);
}

ZTEST_USER_F(sbs_gauge_new_api, test_set_some_props_failed_returns_err)
{
	struct fuel_gauge_property props[] = {
		{
			/* First invalid property */
			.property_type = FUEL_GAUGE_PROP_MAX,
		},
		{
			/* Second invalid property */
			.property_type = FUEL_GAUGE_PROP_MAX,
		},
		{
			/* Valid property */
			.property_type = FUEL_GAUGE_SBS_MFR_ACCESS,
			/* Set Manufacturer's Access to arbitrary word */
			.value.sbs_mfr_access_word = 1,
		},

	};

	int ret = fuel_gauge_set_props(fixture->dev, props, ARRAY_SIZE(props));

	zassert_equal(ret, -ENOTSUP);
}

ZTEST_USER_F(sbs_gauge_new_api, test_set_prop_can_be_get)
{
	uint16_t word = BIT(15) | BIT(0);
	struct fuel_gauge_property set_props[] = {
		{
			/* Valid property */
			.property_type = FUEL_GAUGE_SBS_MFR_ACCESS,
			/* Set Manufacturer's Access to 16 bit word */
			.value.sbs_mfr_access_word = word,
		},
		{
			.property_type = FUEL_GAUGE_SBS_REMAINING_CAPACITY_ALARM,
			.value.sbs_remaining_capacity_alarm = word,
		},
		{
			.property_type = FUEL_GAUGE_SBS_REMAINING_TIME_ALARM,
			.value.sbs_remaining_time_alarm = word,
		},
		{
			.property_type = FUEL_GAUGE_SBS_MODE,
			.value.sbs_mode = word,
		},
		{
			.property_type = FUEL_GAUGE_SBS_ATRATE,
			.value.sbs_at_rate = (int16_t)word,
		},
	};

	struct fuel_gauge_property get_props[] = {
		{
			.property_type = FUEL_GAUGE_SBS_MFR_ACCESS,
		},
		{
			.property_type = FUEL_GAUGE_SBS_REMAINING_CAPACITY_ALARM,
		},
		{
			.property_type = FUEL_GAUGE_SBS_REMAINING_TIME_ALARM,
		},
		{
			.property_type = FUEL_GAUGE_SBS_MODE,
		},
		{
			.property_type = FUEL_GAUGE_SBS_ATRATE,
		},
	};

	zassert_ok(fuel_gauge_set_props(fixture->dev, set_props, ARRAY_SIZE(set_props)));

	zassert_ok(fuel_gauge_get_props(fixture->dev, get_props, ARRAY_SIZE(get_props)));

	zassert_equal(get_props[0].value.sbs_mfr_access_word, word);
	zassert_equal(get_props[1].value.sbs_remaining_capacity_alarm, word);
	zassert_equal(get_props[2].value.sbs_remaining_time_alarm, word);
	zassert_equal(get_props[3].value.sbs_mode, word);
	zassert_equal(get_props[4].value.sbs_at_rate, (int16_t)word);
}

ZTEST_USER_F(sbs_gauge_new_api, test_get_props__returns_ok)
{
	/* Validate what props are supported by the driver */

	struct fuel_gauge_property props[] = {
		{
			.property_type = FUEL_GAUGE_VOLTAGE,
		},
		{
			.property_type = FUEL_GAUGE_CURRENT,
		},
		{
			.property_type = FUEL_GAUGE_AVG_CURRENT,
		},
		{
			.property_type = FUEL_GAUGE_TEMPERATURE,
		},
		{
			.property_type = FUEL_GAUGE_ABSOLUTE_STATE_OF_CHARGE,
		},
		{
			.property_type = FUEL_GAUGE_RELATIVE_STATE_OF_CHARGE,
		},
		{
			.property_type = FUEL_GAUGE_RUNTIME_TO_FULL,
		},
		{
			.property_type = FUEL_GAUGE_RUNTIME_TO_EMPTY,
		},
		{
			.property_type = FUEL_GAUGE_REMAINING_CAPACITY,
		},
		{
			.property_type = FUEL_GAUGE_FULL_CHARGE_CAPACITY,
		},
		{
			.property_type = FUEL_GAUGE_CYCLE_COUNT,
		},
		{
			.property_type = FUEL_GAUGE_SBS_MFR_ACCESS,
		},
		{
			.property_type = FUEL_GAUGE_SBS_MODE,
		},
		{
			.property_type = FUEL_GAUGE_CHARGE_CURRENT,
		},
		{
			.property_type = FUEL_GAUGE_CHARGE_VOLTAGE,
		},
		{
			.property_type = FUEL_GAUGE_STATUS,
		},
		{
			.property_type = FUEL_GAUGE_DESIGN_CAPACITY,
		},
		{
			.property_type = FUEL_GAUGE_DESIGN_VOLTAGE,
		},
		{
			.property_type = FUEL_GAUGE_SBS_ATRATE,
		},
		{
			.property_type = FUEL_GAUGE_SBS_ATRATE_TIME_TO_FULL,
		},
		{
			.property_type = FUEL_GAUGE_SBS_ATRATE_TIME_TO_EMPTY,
		},
		{
			.property_type = FUEL_GAUGE_SBS_ATRATE_OK,
		},
		{
			.property_type = FUEL_GAUGE_SBS_REMAINING_CAPACITY_ALARM,
		},
		{
			.property_type = FUEL_GAUGE_SBS_REMAINING_TIME_ALARM,
		},
	};

	zassert_ok(fuel_gauge_get_props(fixture->dev, props, ARRAY_SIZE(props)));
}

ZTEST_USER_F(sbs_gauge_new_api, test_set_props__returns_ok)
{
	/* Validate what props are supported by the driver */

	struct fuel_gauge_property props[] = {
		{
			.property_type = FUEL_GAUGE_SBS_MFR_ACCESS,
		},
		{
			.property_type = FUEL_GAUGE_SBS_REMAINING_CAPACITY_ALARM,
		},
		{
			.property_type = FUEL_GAUGE_SBS_REMAINING_TIME_ALARM,
		},
		{
			.property_type = FUEL_GAUGE_SBS_MODE,
		},
		{
			.property_type = FUEL_GAUGE_SBS_ATRATE,
		},
	};

	zassert_ok(fuel_gauge_set_props(fixture->dev, props, ARRAY_SIZE(props)));
}


ZTEST_USER_F(sbs_gauge_new_api, test_get_buffer_props__returns_ok)
{
	/* Validate what properties are supported by the driver */
	struct fuel_gauge_buffer_property prop;
	struct sbs_gauge_manufacturer_name mfg_name;
	struct sbs_gauge_device_name dev_name;
	struct sbs_gauge_device_chemistry chem;

	prop.property_type = FUEL_GAUGE_MANUFACTURER_NAME;
	zassert_ok(fuel_gauge_get_buffer_prop(fixture->dev, &prop, &mfg_name, sizeof(mfg_name)));

	prop.property_type = FUEL_GAUGE_DEVICE_NAME;
	zassert_ok(fuel_gauge_get_buffer_prop(fixture->dev, &prop, &dev_name, sizeof(dev_name)));

	prop.property_type = FUEL_GAUGE_DEVICE_CHEMISTRY;
	zassert_ok(fuel_gauge_get_buffer_prop(fixture->dev, &prop, &chem, sizeof(chem)));
}

ZTEST_USER_F(sbs_gauge_new_api, test_charging_5v_3a)
{
	/* Validate what props are supported by the driver */
	uint32_t expected_uV = 5000 * 1000;
	uint32_t expected_uA = 3000 * 1000;

	struct fuel_gauge_property voltage = {
		.property_type = FUEL_GAUGE_VOLTAGE,
	};
	struct fuel_gauge_property current = {
		.property_type = FUEL_GAUGE_CURRENT,
	};

	zassume_ok(emul_fuel_gauge_set_battery_charging(fixture->sbs_fuel_gauge, expected_uV,
							expected_uA));
	zassert_ok(fuel_gauge_get_prop(fixture->dev, &voltage));
	zassert_ok(fuel_gauge_get_prop(fixture->dev, &current));

	zassert_equal(voltage.value.voltage, expected_uV, "Got %d instead of %d",
		      voltage.value.voltage, expected_uV);

	zassert_equal(current.value.current, expected_uA, "Got %d instead of %d",
		      current.value.current, expected_uA);
}

ZTEST_USER_F(sbs_gauge_new_api, test_set_get_single_prop)
{
	/* Validate what props are supported by the driver */

	uint16_t test_value = 0x1001;

	struct fuel_gauge_property mfr_acc_set = {
		.property_type = FUEL_GAUGE_SBS_MFR_ACCESS,
		.value.sbs_mfr_access_word = test_value,
	};
	struct fuel_gauge_property mfr_acc_get = {
		.property_type = FUEL_GAUGE_SBS_MFR_ACCESS,
	};

	zassert_ok(fuel_gauge_set_prop(fixture->dev, &mfr_acc_set));
	zassert_ok(fuel_gauge_get_prop(fixture->dev, &mfr_acc_get));
	zassert_equal(mfr_acc_get.value.sbs_mfr_access_word, test_value);
}

ZTEST_SUITE(sbs_gauge_new_api, NULL, sbs_gauge_new_api_setup, NULL, NULL, NULL);
