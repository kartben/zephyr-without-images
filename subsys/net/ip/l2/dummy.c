/*
 * Copyright (c) 2016 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <net/net_core.h>
#include <net/net_l2.h>
#include <net/net_if.h>
#include <net/net_pkt.h>

static inline enum net_verdict dummy_recv(struct net_if *iface,
					  struct net_pkt *pkt)
{
	net_pkt_ll_src(pkt)->addr = NULL;
	net_pkt_ll_src(pkt)->len = 0;
	net_pkt_ll_src(pkt)->type = NET_LINK_DUMMY;
	net_pkt_ll_dst(pkt)->addr = NULL;
	net_pkt_ll_dst(pkt)->len = 0;
	net_pkt_ll_dst(pkt)->type = NET_LINK_DUMMY;

	return NET_CONTINUE;
}

static inline enum net_verdict dummy_send(struct net_if *iface,
					  struct net_pkt *pkt)
{
	net_if_queue_tx(iface, pkt);

	return NET_OK;
}

static inline uint16_t dummy_reserve(struct net_if *iface, void *unused)
{
	ARG_UNUSED(iface);
	ARG_UNUSED(unused);

	return 0;
}

NET_L2_INIT(DUMMY_L2, dummy_recv, dummy_send, dummy_reserve, NULL);
