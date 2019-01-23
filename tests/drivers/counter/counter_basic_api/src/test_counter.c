/*
 * Copyright (c) 2018, Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <counter.h>
#include <ztest.h>
#include <kernel.h>

static volatile u32_t top_cnt;
static volatile u32_t alarm_cnt;

static void top_handler(struct device *dev, void *user_data);

void *exp_user_data = (void *)199;

#define COUNTER_PERIOD_US 20000

struct counter_alarm_cfg alarm_cfg;
struct counter_alarm_cfg alarm_cfg2;

const char *devices[] = {

#ifdef CONFIG_COUNTER_TIMER0
	/* Nordic TIMER0 may be reserved for Bluetooth */
	CONFIG_COUNTER_TIMER0_NAME,
#endif
#ifdef CONFIG_COUNTER_TIMER1
	CONFIG_COUNTER_TIMER1_NAME,
#endif
#ifdef CONFIG_COUNTER_TIMER2
	CONFIG_COUNTER_TIMER2_NAME,
#endif
#ifdef CONFIG_COUNTER_TIMER3
	CONFIG_COUNTER_TIMER3_NAME,
#endif
#ifdef CONFIG_COUNTER_TIMER4
	CONFIG_COUNTER_TIMER4_NAME,
#endif
#ifdef CONFIG_COUNTER_RTC0
	/* Nordic RTC0 may be reserved for Bluetooth */
	CONFIG_COUNTER_RTC0_NAME,
#endif
	/* Nordic RTC1 is used for the system clock */
#ifdef CONFIG_COUNTER_RTC2
	CONFIG_COUNTER_RTC2_NAME,
#endif
};
typedef void (*counter_test_func_t)(const char *dev_name);


static void counter_tear_down_instance(const char *dev_name)
{
	int err;
	struct device *dev;

	dev = device_get_binding(dev_name);

	err = counter_set_top_value(dev, counter_get_max_top_value(dev),
				    NULL, NULL);
	zassert_equal(0, err, "Setting top value to default failed\n");

	err = counter_stop(dev);
	zassert_equal(0, err, "Counter failed to stop\n");
}

static void test_all_instances(counter_test_func_t func)
{
	for (int i = 0; i < ARRAY_SIZE(devices); i++) {
		func(devices[i]);
		counter_tear_down_instance(devices[i]);
	}
}

void counter_tear_down(void)
{

}

static void top_handler(struct device *dev, void *user_data)
{
	zassert_true(user_data == exp_user_data, "Unexpected callback\n");
	top_cnt++;
}

void test_set_top_value_with_alarm_instance(const char *dev_name)
{
	struct device *dev;
	int err;
	u32_t cnt;
	u32_t ticks;

	top_cnt = 0;

	dev = device_get_binding(dev_name);
	ticks = counter_us_to_ticks(dev, COUNTER_PERIOD_US);

	err = counter_start(dev);
	zassert_equal(0, err, "Counter failed to start\n");

	k_busy_wait(5000);

	cnt = counter_read(dev);
	zassert_true(cnt > 0, "Counter should progress (dev:%s)\n", dev_name);

	err = counter_set_top_value(dev, ticks, top_handler, exp_user_data);
	zassert_equal(0, err, "Counter failed to set top value (dev:%s)\n",
			dev_name);

	k_busy_wait(5.2*COUNTER_PERIOD_US);

	zassert_true(top_cnt == 5,
			"Unexpected number of turnarounds (%d) (dev: %s).\n",
			top_cnt, dev_name);
}

void test_set_top_value_with_alarm(void)
{
	test_all_instances(test_set_top_value_with_alarm_instance);
}

static void alarm_handler(struct device *dev, u8_t chan_id, u32_t counter,
			  void *user_data)
{
	zassert_true(&alarm_cfg == user_data, "Unexpected callback\n");
	alarm_cnt++;
}

void test_single_shot_alarm_instance(const char *dev_name)
{
	struct device *dev;
	int err;
	u32_t ticks;

	dev = device_get_binding(dev_name);
	ticks = counter_us_to_ticks(dev, COUNTER_PERIOD_US);

	alarm_cfg.absolute = true;
	alarm_cfg.ticks = ticks + 1;
	alarm_cfg.callback = alarm_handler;
	alarm_cfg.user_data = &alarm_cfg;

	alarm_cnt = 0;

	err = counter_start(dev);
	zassert_equal(0, err, "Counter failed to start\n");

	err = counter_set_top_value(dev, ticks, top_handler, exp_user_data);
	zassert_equal(0, err, "Counter failed to set top value\n");

	err = counter_set_channel_alarm(dev, 0, &alarm_cfg);
	zassert_equal(-EINVAL, err, "Counter should return error because ticks"
					" exceeded the limit set alarm\n");
	alarm_cfg.ticks = ticks - 100;

	err = counter_set_channel_alarm(dev, 0, &alarm_cfg);
	zassert_equal(0, err, "Counter set alarm failed\n");

	k_busy_wait(1.2*counter_ticks_to_us(dev, ticks));

	zassert_equal(1, alarm_cnt, "Expecting alarm callback\n");

	k_busy_wait(counter_ticks_to_us(dev, 2*ticks));
	zassert_equal(1, alarm_cnt, "Expecting alarm callback\n");

	err = counter_disable_channel_alarm(dev, 0);
	zassert_equal(0, err, "Counter disabling alarm failed\n");

	err = counter_set_top_value(dev, counter_get_max_top_value(dev),
				    NULL, NULL);
	zassert_equal(0, err, "Setting top value to default failed\n");

	err = counter_stop(dev);
	zassert_equal(0, err, "Counter failed to stop\n");
}

void test_single_shot_alarm(void)
{
	test_all_instances(test_single_shot_alarm_instance);
}

static void *clbk_data[2];

static void alarm_handler2(struct device *dev, u8_t chan_id, u32_t counter,
			   void *user_data)
{
	clbk_data[alarm_cnt] = user_data;
	alarm_cnt++;
}

/*
 * Two alarms set. First alarm is absolute, second relative. Because
 * setting of both alarms is delayed it is expected that second alarm
 * will expire first (relative to the time called) while first alarm
 * will expire after next wrap around.
 */
void test_multiple_alarms_instance(const char *dev_name)
{
	struct device *dev;
	int err;
	u32_t ticks;

	dev = device_get_binding(dev_name);
	ticks = counter_us_to_ticks(dev, COUNTER_PERIOD_US);

	alarm_cfg.absolute = true;
	alarm_cfg.ticks = counter_us_to_ticks(dev, 2000);
	alarm_cfg.callback = alarm_handler2;
	alarm_cfg.user_data = &alarm_cfg;

	alarm_cfg2.absolute = false;
	alarm_cfg2.ticks = counter_us_to_ticks(dev, 2000);
	alarm_cfg2.callback = alarm_handler2;
	alarm_cfg2.user_data = &alarm_cfg2;

	alarm_cnt = 0;

	err = counter_start(dev);
	zassert_equal(0, err, "Counter failed to start\n");

	err = counter_set_top_value(dev, ticks, top_handler, exp_user_data);
	zassert_equal(0, err, "Counter failed to set top value\n");

	k_busy_wait(1.4*counter_ticks_to_us(dev, alarm_cfg.ticks));

	err = counter_set_channel_alarm(dev, 0, &alarm_cfg);
	zassert_equal(0, err, "Counter set alarm failed\n");

	err = counter_set_channel_alarm(dev, 1, &alarm_cfg2);
	zassert_equal(0, err, "Counter set alarm failed\n");

	k_busy_wait(1.2*counter_ticks_to_us(dev, 2*ticks));
	zassert_equal(2, alarm_cnt, "Counter set alarm failed\n");
	zassert_equal(&alarm_cfg2, clbk_data[0],
			"Expected different order or callbacks\n");
	zassert_equal(&alarm_cfg, clbk_data[1],
			"Expected different order or callbacks\n");

	/* tear down */
	err = counter_disable_channel_alarm(dev, 0);
	zassert_equal(0, err, "Counter disabling alarm failed\n");

	err = counter_disable_channel_alarm(dev, 1);
	zassert_equal(0, err, "Counter disabling alarm failed\n");
}

void test_multiple_alarms(void)
{
	test_all_instances(test_multiple_alarms_instance);
}

void test_all_channels_instance(const char *str)
{
	struct device *dev;
	int err;
	const int n = 10;
	int nchan = 0;
	bool limit_reached = false;
	struct counter_alarm_cfg alarm_cfgs[n];
	u32_t ticks;

	dev = device_get_binding(str);
	ticks = counter_us_to_ticks(dev, COUNTER_PERIOD_US);

	for (int i = 0; i < n; i++) {
		alarm_cfgs[i].absolute = false;
		alarm_cfgs[i].ticks = ticks-100;
		alarm_cfgs[i].callback = alarm_handler2;
	}

	err = counter_start(dev);
	zassert_equal(0, err, "Counter failed to start");

	for (int i = 0; i < n; i++) {
		err = counter_set_channel_alarm(dev, i, &alarm_cfgs[i]);
		if ((err == 0) && !limit_reached) {
			nchan++;
		} else if (err == -ENOTSUP) {
			limit_reached = true;
		} else {
			zassert_equal(0, 1,
					"Unexpected error on setting alarm");
		}
	}

	for (int i = 0; i < nchan; i++) {
		err = counter_disable_channel_alarm(dev, i);
		zassert_equal(0, err, "Unexpected error on disabling alarm");
	}

	for (int i = nchan; i < n; i++) {
		err = counter_disable_channel_alarm(dev, i);
		zassert_equal(-ENOTSUP, err,
				"Unexpected error on disabling alarm\n");
	}
}

void test_all_channels(void)
{
	test_all_instances(test_all_channels_instance);
}

void test_main(void)
{
	ztest_test_suite(test_counter,
		ztest_unit_test_setup_teardown(test_set_top_value_with_alarm,
					unit_test_noop,
					counter_tear_down),
		ztest_unit_test_setup_teardown(test_single_shot_alarm,
					unit_test_noop,
					counter_tear_down),
		ztest_unit_test_setup_teardown(test_multiple_alarms,
					unit_test_noop,
					counter_tear_down),
		ztest_unit_test_setup_teardown(test_all_channels,
					unit_test_noop,
					counter_tear_down)
			 );
	ztest_run_test_suite(test_counter);
}
