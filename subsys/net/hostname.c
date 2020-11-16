/** @file
 * @brief Hostname configuration
 */

/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <logging/log.h>
LOG_MODULE_REGISTER(net_hostname, CONFIG_NET_HOSTNAME_LOG_LEVEL);

#include <zephyr.h>

#include <net/hostname.h>
#include <net/net_core.h>

static char hostname[NET_HOSTNAME_MAX_LEN + 1];

const char *net_hostname_get(void)
{
	return hostname;
}

#if defined(CONFIG_NET_HOSTNAME_UNIQUE)
int net_hostname_set_postfix(const uint8_t *hostname_postfix,
			     int postfix_len)
{
	static bool postfix_set;
	int pos = 0;
	int i;

	if (postfix_set) {
		return -EALREADY;
	}

	NET_ASSERT(postfix_len > 0);

	/* Note that we convert the postfix to hex (2 chars / byte) */
	if ((postfix_len * 2) >
	    (NET_HOSTNAME_MAX_LEN - (sizeof(CONFIG_NET_HOSTNAME) - 1))) {
		return -EMSGSIZE;
	}

	for (i = 0; i < postfix_len; i++, pos += 2) {
		snprintk(&hostname[sizeof(CONFIG_NET_HOSTNAME) - 1 + pos],
			 2 + 1, "%02x", hostname_postfix[i]);
	}

	NET_DBG("New hostname %s", log_strdup(hostname));

	postfix_set = true;

	return 0;
}
#endif /* CONFIG_NET_HOSTNAME_UNIQUE */

void net_hostname_init(void)
{
	memcpy(hostname, CONFIG_NET_HOSTNAME, sizeof(CONFIG_NET_HOSTNAME) - 1);

	NET_DBG("Hostname set to %s", CONFIG_NET_HOSTNAME);
}
