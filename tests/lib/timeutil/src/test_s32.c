/*
 * Copyright (c) 2019 Peter Bigot Consulting
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Tests where time_t is a 32-bit value */

#include <ztest.h>
#include "timeutil_test.h"

static const struct timeutil_test_data tests[] = {
	/* Simple tests */
	{ .unix = -1,
	  .civil = "1969-12-31 23:59:59 Wed 365",
	  .tm = {
		  .tm_sec = 59,
		  .tm_min = 59,
		  .tm_hour = 23,
		  .tm_mday = 31,
		  .tm_mon = 11,
		  .tm_year = 69,
		  .tm_wday = 3,
		  .tm_yday = 364,
	  } },
	{ .unix = 0,
	  .civil = "1970-01-01 00:00:00 Thu 001",
	  .tm = {
		  .tm_sec = 0,
		  .tm_min = 0,
		  .tm_hour = 0,
		  .tm_mday = 1,
		  .tm_mon = 0,
		  .tm_year = 70,
		  .tm_wday = 4,
		  .tm_yday = 0,
	  } },
	{ .unix = 1498577363,
	  .civil = "2017-06-27 15:29:23 Tue 178",
	  .tm = {
		  .tm_sec = 23,
		  .tm_min = 29,
		  .tm_hour = 15,
		  .tm_mday = 27,
		  .tm_mon = 5,
		  .tm_year = 117,
		  .tm_wday = 2,
		  .tm_yday = 177,
	  } },

	/*
	 * 32-bit extreme values.  Lower range is limited due
	 * algorithm subtraction rounding to days.
	 */
	{ .unix = -2147483648 + 86399,
	  .civil = "1901-12-14 20:45:51 Sat 348",
	  .tm = {
		  .tm_sec = 51,
		  .tm_min = 45,
		  .tm_hour = 20,
		  .tm_mday = 14,
		  .tm_mon = 11,
		  .tm_year = 1,
		  .tm_wday = 6,
		  .tm_yday = 347,
	  } },
	{ .unix = 2147483647,
	  .civil = "2038-01-19 03:14:07 Tue 019",
	  .tm = {
		  .tm_sec = 7,
		  .tm_min = 14,
		  .tm_hour = 3,
		  .tm_mday = 19,
		  .tm_mon = 0,
		  .tm_year = 138,
		  .tm_wday = 2,
		  .tm_yday = 18,
	  } },

	/* Normal leap year: 1972 */
	{ .unix = 63071999,
	  .civil = "1971-12-31 23:59:59 Fri 365",
	  .tm = {
		  .tm_sec = 59,
		  .tm_min = 59,
		  .tm_hour = 23,
		  .tm_mday = 31,
		  .tm_mon = 11,
		  .tm_year = 71,
		  .tm_wday = 5,
		  .tm_yday = 364,
	  } },
	{ .unix = 63072000,
	  .civil = "1972-01-01 00:00:00 Sat 001",
	  .tm = {
		  .tm_sec = 0,
		  .tm_min = 0,
		  .tm_hour = 0,
		  .tm_mday = 1,
		  .tm_mon = 0,
		  .tm_year = 72,
		  .tm_wday = 6,
		  .tm_yday = 0,
	  } },
	{ .unix = 68083200,
	  .civil = "1972-02-28 00:00:00 Mon 059",
	  .tm = {
		  .tm_sec = 0,
		  .tm_min = 0,
		  .tm_hour = 0,
		  .tm_mday = 28,
		  .tm_mon = 1,
		  .tm_year = 72,
		  .tm_wday = 1,
		  .tm_yday = 58,
	  } },
	{ .unix = 68169600,
	  .civil = "1972-02-29 00:00:00 Tue 060",
	  .tm = {
		  .tm_sec = 0,
		  .tm_min = 0,
		  .tm_hour = 0,
		  .tm_mday = 29,
		  .tm_mon = 1,
		  .tm_year = 72,
		  .tm_wday = 2,
		  .tm_yday = 59,
	  } },
	{ .unix = 68256000,
	  .civil = "1972-03-01 00:00:00 Wed 061",
	  .tm = {
		  .tm_sec = 0,
		  .tm_min = 0,
		  .tm_hour = 0,
		  .tm_mday = 1,
		  .tm_mon = 2,
		  .tm_year = 72,
		  .tm_wday = 3,
		  .tm_yday = 60,
	  } },
	{ .unix = 94521600,
	  .civil = "1972-12-30 00:00:00 Sat 365",
	  .tm = {
		  .tm_sec = 0,
		  .tm_min = 0,
		  .tm_hour = 0,
		  .tm_mday = 30,
		  .tm_mon = 11,
		  .tm_year = 72,
		  .tm_wday = 6,
		  .tm_yday = 364,
	  } },
	{ .unix = 94608000,
	  .civil = "1972-12-31 00:00:00 Sun 366",
	  .tm = {
		  .tm_sec = 0,
		  .tm_min = 0,
		  .tm_hour = 0,
		  .tm_mday = 31,
		  .tm_mon = 11,
		  .tm_year = 72,
		  .tm_wday = 0,
		  .tm_yday = 365,
	  } },
	{ .unix = 94694400,
	  .civil = "1973-01-01 00:00:00 Mon 001",
	  .tm = {
		  .tm_sec = 0,
		  .tm_min = 0,
		  .tm_hour = 0,
		  .tm_mday = 1,
		  .tm_mon = 0,
		  .tm_year = 73,
		  .tm_wday = 1,
		  .tm_yday = 0,
	  } },

	/* Start of era 5, special leap year */
	{ .unix = 946684799,
	  .civil = "1999-12-31 23:59:59 Fri 365",
	  .tm = {
		  .tm_sec = 59,
		  .tm_min = 59,
		  .tm_hour = 23,
		  .tm_mday = 31,
		  .tm_mon = 11,
		  .tm_year = 99,
		  .tm_wday = 5,
		  .tm_yday = 364,
	  } },
	{ .unix = 946684800,
	  .civil = "2000-01-01 00:00:00 Sat 001",
	  .tm = {
		  .tm_sec = 0,
		  .tm_min = 0,
		  .tm_hour = 0,
		  .tm_mday = 1,
		  .tm_mon = 0,
		  .tm_year = 100,
		  .tm_wday = 6,
		  .tm_yday = 0,
	  } },
	{ .unix = 951696000,
	  .civil = "2000-02-28 00:00:00 Mon 059",
	  .tm = {
		  .tm_sec = 0,
		  .tm_min = 0,
		  .tm_hour = 0,
		  .tm_mday = 28,
		  .tm_mon = 1,
		  .tm_year = 100,
		  .tm_wday = 1,
		  .tm_yday = 58,
	  } },
	{ .unix = 951782400,
	  .civil = "2000-02-29 00:00:00 Tue 060",
	  .tm = {
		  .tm_sec = 0,
		  .tm_min = 0,
		  .tm_hour = 0,
		  .tm_mday = 29,
		  .tm_mon = 1,
		  .tm_year = 100,
		  .tm_wday = 2,
		  .tm_yday = 59,
	  } },
	{ .unix = 951868800,
	  .civil = "2000-03-01 00:00:00 Wed 061",
	  .tm = {
		  .tm_sec = 0,
		  .tm_min = 0,
		  .tm_hour = 0,
		  .tm_mday = 1,
		  .tm_mon = 2,
		  .tm_year = 100,
		  .tm_wday = 3,
		  .tm_yday = 60,
	  } },
};

void test_s32(void)
{
	timeutil_check(tests, sizeof(tests) / sizeof(*tests));
}
