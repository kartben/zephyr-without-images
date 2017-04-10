/** @file
 @brief ARP handler

 This is not to be included by the application.
 */

/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __ARP_H
#define __ARP_H

#if defined(CONFIG_NET_ARP)

#include <net/ethernet.h>

#define NET_ARP_HDR(pkt) ((struct net_arp_hdr *)net_pkt_ip_data(pkt))

struct net_arp_hdr {
	uint16_t hwtype;		/* HTYPE */
	uint16_t protocol;		/* PTYPE */
	uint8_t hwlen;			/* HLEN */
	uint8_t protolen;		/* PLEN */
	uint16_t opcode;
	struct net_eth_addr src_hwaddr;	/* SHA */
	struct in_addr src_ipaddr;	/* SPA */
	struct net_eth_addr dst_hwaddr;	/* THA */
	struct in_addr dst_ipaddr;	/* TPA */
}  __packed;

#define NET_ARP_HTYPE_ETH 1

#define NET_ARP_REQUEST 1
#define NET_ARP_REPLY   2

struct net_pkt *net_arp_prepare(struct net_pkt *pkt);
enum net_verdict net_arp_input(struct net_pkt *pkt);

void net_arp_init(void);

#else /* CONFIG_NET_ARP */

#define net_arp_init(...)

#endif /* CONFIG_NET_ARP */

#endif /* __ARP_H */
