/*
 * Copyright (c) 2020 Linumiz
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <logging/log.h>

#include <zephyr.h>

#include <net/net_if.h>
#include <net/net_core.h>
#include <net/net_context.h>
#include <net/net_mgmt.h>

static struct net_mgmt_event_callback mgmt_cb;

/* Semaphore to indicate a lease has been acquired */
static K_SEM_DEFINE(got_address, 0, 1);

static void handler(struct net_mgmt_event_callback *cb,
		    uint32_t mgmt_event,
		    struct net_if *iface)
{
	int i;
	bool notified = false;

	if (mgmt_event != NET_EVENT_IPV4_ADDR_ADD) {
		return;
	}

	for (i = 0; i < NET_IF_MAX_IPV4_ADDR; i++) {
		if (iface->config.ip.ipv4->unicast[i].addr_type !=
		    NET_ADDR_DHCP) {
			continue;
		}

		if (!notified) {
			k_sem_give(&got_address);
			notified = true;
		}
		break;
	}
}

/**
 * Start a DHCP client, and wait for a lease to be acquired.
 */
void app_dhcpv4_startup(void)
{
	struct net_if *iface;

	net_mgmt_init_event_callback(&mgmt_cb, handler,
				     NET_EVENT_IPV4_ADDR_ADD);
	net_mgmt_add_event_callback(&mgmt_cb);

	iface = net_if_get_default();

	net_dhcpv4_start(iface);

	/* Wait for a lease */
	k_sem_take(&got_address, K_FOREVER);
}
