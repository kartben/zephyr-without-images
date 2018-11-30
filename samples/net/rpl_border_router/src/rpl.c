/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_LEVEL LOG_LEVEL_DBG

#include <logging/log.h>
LOG_MODULE_DECLARE(net_rpl_br_sample, LOG_LEVEL);

#include <zephyr.h>
#include <stdio.h>
#include <stdlib.h>

#include <net/net_ip.h>
#include "../../../subsys/net/ip/rpl.h"

#include "config.h"

static struct {
	struct in6_addr dag_id;
	u8_t dag_init_version;
	bool dag_has_version;

	struct in6_addr prefix;
	u8_t prefix_len;
} rpl;

static bool br_join_dag(struct net_rpl_dio *dio)
{
	static u8_t last_version;

	if (net_ipv6_addr_cmp(&dio->dag_id, &rpl.dag_id)) {
		if (rpl.dag_init_version != dio->version &&
		    last_version != dio->version) {
			LOG_DBG("Me root, DIO version %d instance %d",
				dio->version, dio->instance_id);
			last_version = dio->version;
		}

		if (dio->version > NET_RPL_LOLLIPOP_CIRCULAR_REGION) {
			rpl.dag_init_version = dio->version;
			rpl.dag_has_version = true;
		}
	} else {
		if (LOG_LEVEL >= LOG_LEVEL_DBG) {
			char me[NET_IPV6_ADDR_LEN];
			char other[NET_IPV6_ADDR_LEN];

			net_addr_ntop(AF_INET6, &dio->dag_id, other,
				      NET_IPV6_ADDR_LEN);
			net_addr_ntop(AF_INET6, &rpl.dag_id, me,
				      NET_IPV6_ADDR_LEN);

			LOG_DBG("Other root %s, me %s, "
				"DIO version %d instance %d",
				log_strdup(other), log_strdup(me),
				dio->version, dio->instance_id);
		}
	}

	return 0;
}

bool setup_rpl(struct net_if *iface, const char *addr_prefix)
{
	char prefix[NET_IPV6_ADDR_LEN + 1];
	struct net_rpl_dag *dag;
	char *slash;
	bool ret;

	/* As the addr_prefix is Kconfig option we need to copy it to temporary
	 * buffer in order to be able to manipulate it.
	 */
	(void)memset(prefix, 0, sizeof(prefix));
	memcpy(prefix, addr_prefix, min(strlen(addr_prefix),
					NET_IPV6_ADDR_LEN));

	slash = strstr(prefix, "/");
	if (!slash) {
		rpl.prefix_len = 64U;
	} else {
		*slash = '\0';
		rpl.prefix_len = atoi(slash + 1);
	}

	if (rpl.prefix_len == 0) {
		LOG_ERR("Invalid prefix length %s", log_strdup(slash + 1));
		return false;
	}

	if (net_addr_pton(AF_INET6, prefix, &rpl.prefix) < 0) {
		LOG_ERR("Invalid IPv6 prefix %s", log_strdup(prefix));
		return false;
	}

	net_rpl_set_join_callback(br_join_dag);

	if (rpl.dag_has_version) {
		net_rpl_lollipop_increment(&rpl.dag_init_version);

		dag = net_rpl_set_root_with_version(iface,
			CONFIG_NET_RPL_DEFAULT_INSTANCE, &rpl.dag_id,
			rpl.dag_init_version);
	} else {
		dag = net_rpl_set_root(iface, CONFIG_NET_RPL_DEFAULT_INSTANCE,
				       &rpl.prefix);
	}
	if (!dag) {
		LOG_ERR("Cannot set root node");
		return false;
	}

	net_rpl_dag_set_grounded_status(dag, 1);

	ret = net_rpl_set_prefix(iface, dag, &rpl.prefix, rpl.prefix_len);
	if (!ret) {
		LOG_ERR("Cannot set prefix %s/%d", log_strdup(prefix),
			rpl.prefix_len);
		return false;
	}

	if (LOG_LEVEL >= LOG_LEVEL_DBG) {
		char out[NET_IPV6_ADDR_LEN];

		if (net_addr_ntop(AF_INET6, &rpl.prefix, out,
				  NET_IPV6_ADDR_LEN)) {
			if (rpl.dag_has_version) {
				LOG_DBG("New RPL dag %s/%d version %u created",
					log_strdup(out), rpl.prefix_len,
					rpl.dag_init_version);
			} else {
				LOG_DBG("New RPL dag %s/%d created",
					log_strdup(out),
					rpl.prefix_len);
			}
		}
	}

	return true;
}
