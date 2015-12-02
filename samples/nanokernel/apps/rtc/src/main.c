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

#include <zephyr.h>

#include <device.h>
#include <rtc.h>
#include <misc/printk.h>


#define ALARM (RTC_ALARM_MINUTE / 6)
#define RTC_DRIVER "rtc"

void test_rtc_interrupt_fn(struct device *rtc_dev)
{
	uint32_t now = rtc_read(rtc_dev);

	printk("Alarm\n");
	rtc_set_alarm(rtc_dev, now + ALARM);
}

void main(void)
{
	struct rtc_config config;
	struct device *rtc_dev;

	printk("Test RTC driver\n");
	rtc_dev = device_get_binding(RTC_DRIVER);

	config.init_val = 0;
	config.alarm_enable = 1;
	config.alarm_val = ALARM;
	config.cb_fn = test_rtc_interrupt_fn;

	rtc_enable(rtc_dev);

	rtc_set_config(rtc_dev, &config);

	while (1) {
		/* do nothing */
	}
}
