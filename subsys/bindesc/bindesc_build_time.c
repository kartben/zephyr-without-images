/*
 * Copyright (c) 2023 Yonatan Schachter
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/bindesc.h>

#if IS_ENABLED(CONFIG_BINDESC_BUILD_TIME_YEAR)
BINDESC_UINT_DEFINE(build_time_year, BINDESC_ID_BUILD_TIME_YEAR, BUILD_TIME_YEAR);
#endif /* IS_ENABLED(CONFIG_BINDESC_BUILD_TIME_YEAR) */

#if IS_ENABLED(CONFIG_BINDESC_BUILD_TIME_MONTH)
BINDESC_UINT_DEFINE(build_time_month, BINDESC_ID_BUILD_TIME_MONTH, BUILD_TIME_MONTH);
#endif /* IS_ENABLED(CONFIG_BINDESC_BUILD_TIME_MONTH) */

#if IS_ENABLED(CONFIG_BINDESC_BUILD_TIME_DAY)
BINDESC_UINT_DEFINE(build_time_day, BINDESC_ID_BUILD_TIME_DAY, BUILD_TIME_DAY);
#endif /* IS_ENABLED(CONFIG_BINDESC_BUILD_TIME_DAY) */

#if IS_ENABLED(CONFIG_BINDESC_BUILD_TIME_HOUR)
BINDESC_UINT_DEFINE(build_time_hour, BINDESC_ID_BUILD_TIME_HOUR, BUILD_TIME_HOUR);
#endif /* IS_ENABLED(CONFIG_BINDESC_BUILD_TIME_HOUR) */

#if IS_ENABLED(CONFIG_BINDESC_BUILD_TIME_MINUTE)
BINDESC_UINT_DEFINE(build_time_minute, BINDESC_ID_BUILD_TIME_MINUTE, BUILD_TIME_MINUTE);
#endif /* IS_ENABLED(CONFIG_BINDESC_BUILD_TIME_MINUTE) */

#if IS_ENABLED(CONFIG_BINDESC_BUILD_TIME_SECOND)
BINDESC_UINT_DEFINE(build_time_second, BINDESC_ID_BUILD_TIME_SECOND, BUILD_TIME_SECOND);
#endif /* IS_ENABLED(CONFIG_BINDESC_BUILD_TIME_SECOND) */

#if IS_ENABLED(CONFIG_BINDESC_BUILD_TIME_UNIX)
BINDESC_UINT_DEFINE(build_time_unix, BINDESC_ID_BUILD_TIME_UNIX, BUILD_TIME_UNIX);
#endif /* IS_ENABLED(CONFIG_BINDESC_BUILD_TIME_UNIX) */

#if IS_ENABLED(CONFIG_BINDESC_BUILD_DATE_TIME_STRING)
BINDESC_STR_DEFINE(build_date_time_string, BINDESC_ID_BUILD_DATE_TIME_STRING,
			BUILD_DATE_TIME_STRING);
#endif /* IS_ENABLED(CONFIG_BINDESC_BUILD_DATE_TIME_STRING) */

#if IS_ENABLED(CONFIG_BINDESC_BUILD_DATE_STRING)
BINDESC_STR_DEFINE(build_date_string, BINDESC_ID_BUILD_DATE_STRING, BUILD_DATE_STRING);
#endif /* IS_ENABLED(CONFIG_BINDESC_BUILD_DATE_STRING) */

#if IS_ENABLED(CONFIG_BINDESC_BUILD_TIME_STRING)
BINDESC_STR_DEFINE(build_time_string, BINDESC_ID_BUILD_TIME_STRING, BUILD_TIME_STRING);
#endif /* IS_ENABLED(CONFIG_BINDESC_BUILD_TIME_STRING) */
