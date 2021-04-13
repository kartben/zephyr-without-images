/*
 * Copyright (c) 2018 - 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <stdarg.h>
#include <stdio.h>

#include <openthread/platform/logging.h>
#include "openthread-core-zephyr-config.h"

#define LOG_MODULE_NAME net_openthread
#define LOG_LEVEL LOG_LEVEL_DBG
#include <logging/log.h>
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

#include "platform-zephyr.h"

/* Convert OT log level to zephyr log level. */
static inline int log_translate(otLogLevel aLogLevel)
{
	switch (aLogLevel) {
	case OT_LOG_LEVEL_CRIT:
		return LOG_LEVEL_ERR;
	case OT_LOG_LEVEL_WARN:
		return LOG_LEVEL_WRN;
	case OT_LOG_LEVEL_NOTE:
	case OT_LOG_LEVEL_INFO:
		return LOG_LEVEL_INF;
	case OT_LOG_LEVEL_DEBG:
		return LOG_LEVEL_DBG;
	default:
		break;
	}

	return -1;
}

void otPlatLog(otLogLevel aLogLevel, otLogRegion aLogRegion,
	       const char *aFormat, ...)
{
	/*
	 * The following speed optimization have been used:
	 * - arguments are counted at compile time
	 * - for none arguments aFormat is not checked for %s
	 * - for up to three arguments program uses fast path
	 * - time consuming string formatting is posponed to idle time
	 * TODO : add support for ll (problem for 32 bit processors)
	 */


#ifdef OPENTHREAD_CONFIG_PLAT_LOG_MACRO_NAME__COUNT_ARGS
	/* The arguments number has been counted by macro at compile time,
	 * and the value has been passed in unused (now) aLogRegion.
	 * If LogRegion value from OT is needed, rewrite macro
	 * OPENTHREAD_CONFIG_PLAT_LOG_MACRO_NAME__COUNT_ARGS and use higher
	 * bits to pass args_num.
	 */
	uint32_t args_num = (uint32_t) aLogRegion;
#else
	ARG_UNUSED(aLogRegion);

	uint32_t args_num = log_count_args(aFormat);
#endif

	va_list param_list;
	int level = log_translate(aLogLevel);

	if (level < 0) {
		return;
	}

	va_start(param_list, aFormat);

	/* We assume, that OT has no access to strdup utility,
	 * and we are not obliged to check, if string has already
	 * been duplicated. So, to save time, in Z_LOG_VA macro calls
	 * we will use LOG_STRDUP_EXEC option.
	 */
	Z_LOG_VA(level, aFormat, param_list, args_num, LOG_STRDUP_EXEC);
	va_end(param_list);
}
