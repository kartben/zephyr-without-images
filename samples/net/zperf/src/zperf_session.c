/*
 * Copyright (c) 2015 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_MODULE_NAME net_zperf_session
#define NET_LOG_LEVEL LOG_LEVEL_DBG

#include <zephyr.h>

#include <net/net_pkt.h>
#include <net/udp.h>

#include "zperf_session.h"

#define SESSION_MAX 4

static struct session sessions[SESSION_PROTO_END][SESSION_MAX];

/* Get session from a given packet */
struct session *get_session(struct net_pkt *pkt, enum session_proto proto)
{
	struct session *active = NULL;
	struct session *free = NULL;
	struct in6_addr ipv6 = { };
	struct in_addr ipv4 = { };
	struct net_udp_hdr hdr, *udp_hdr;
	int i = 0;
	u16_t port;

	if (!pkt) {
		printk("Error! null pkt detected.\n");
		return NULL;
	}

	if (proto != SESSION_TCP && proto != SESSION_UDP) {
		printk("Error! unsupported proto.\n");
		return NULL;
	}

	udp_hdr = net_udp_get_hdr(pkt, &hdr);
	if (!udp_hdr) {
		printk("Invalid UDP data\n");
		return NULL;
	}

	/* Get tuple of the remote connection */
	port = udp_hdr->src_port;

	if (net_pkt_family(pkt) == AF_INET6) {
		net_ipaddr_copy(&ipv6, &NET_IPV6_HDR(pkt)->src);
	} else if (net_pkt_family(pkt) == AF_INET) {
		net_ipaddr_copy(&ipv4, &NET_IPV4_HDR(pkt)->src);
	} else {
		printk("Error! unsupported protocol %d\n",
		       net_pkt_family(pkt));
		return NULL;
	}

	/* Check whether we already have an active session */
	while (!active && i < SESSION_MAX) {
		struct session *ptr = &sessions[proto][i];

#if defined(CONFIG_NET_IPV4)
		if (ptr->port == port &&
		    net_pkt_family(pkt) == AF_INET &&
		    net_ipv4_addr_cmp(&ptr->ip.in_addr, &ipv4)) {
			/* We found an active session */
			active = ptr;
		} else
#endif
#if defined(CONFIG_NET_IPV6)
		if (ptr->port == port &&
		    net_pkt_family(pkt) == AF_INET6 &&
		    net_ipv6_addr_cmp(&ptr->ip.in6_addr, &ipv6)) {
			/* We found an active session */
			active = ptr;
		} else
#endif
		if (!free && (ptr->state == STATE_NULL ||
			      ptr->state == STATE_COMPLETED)) {
			/* We found a free slot - just in case */
			free = ptr;
		}

		i++;
	}

	/* If no active session then create a new one */
	if (!active && free) {
		active = free;
		active->port = port;

#if defined(CONFIG_NET_IPV6)
		if (net_pkt_family(pkt) == AF_INET6) {
			net_ipaddr_copy(&active->ip.in6_addr, &ipv6);
		}
#endif
#if defined(CONFIG_NET_IPV4)
		if (net_pkt_family(pkt) == AF_INET) {
			net_ipaddr_copy(&active->ip.in_addr, &ipv4);
		}
#endif
	}

	return active;
}

void zperf_reset_session_stats(struct session *session)
{
	if (!session) {
		return;
	}

	session->counter = 0U;
	session->start_time = 0U;
	session->next_id = 0U;
	session->length = 0U;
	session->outorder = 0U;
	session->error = 0U;
	session->jitter = 0;
	session->last_transit_time = 0;
}

void zperf_session_init(void)
{
	int i, j;

	for (i = 0; i < SESSION_PROTO_END; i++) {
		for (j = 0; j < SESSION_MAX; j++) {
			sessions[i][j].state = STATE_NULL;
			zperf_reset_session_stats(&(sessions[i][j]));
		}
	}
}
