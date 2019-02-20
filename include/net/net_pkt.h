/** @file
 * @brief Network packet buffer descriptor API
 *
 * Network data is passed between different parts of the stack via
 * net_buf struct.
 */

/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Data buffer API - used for all data to/from net */

#ifndef ZEPHYR_INCLUDE_NET_NET_PKT_H_
#define ZEPHYR_INCLUDE_NET_NET_PKT_H_

#include <zephyr/types.h>
#include <stdbool.h>

#include <net/buf.h>

#include <net/net_core.h>
#include <net/net_linkaddr.h>
#include <net/net_ip.h>
#include <net/net_if.h>
#include <net/net_context.h>
#include <net/ethernet_vlan.h>
#include <net/ptp_time.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Network packet management library
 * @defgroup net_pkt Network Packet Library
 * @ingroup networking
 * @{
 */

struct net_context;


/* buffer cursor used in net_pkt */
struct net_pkt_cursor {
	/** Current net_buf pointer by the cursor */
	struct net_buf *buf;
	/** Current position in the data buffer of the net_buf */
	u8_t *pos;
};

/**
 * @brief Network packet.
 *
 * Note that if you add new fields into net_pkt, remember to update
 * net_pkt_clone() function.
 */
struct net_pkt {
	/** FIFO uses first 4 bytes itself, reserve space */
	int _reserved;

	/** Internal variable that is used when packet is sent */
	struct k_work work;

	/** Slab pointer from where it belongs to */
	struct k_mem_slab *slab;

	/** buffer holding the packet */
	union {
		struct net_buf *frags;
		struct net_buf *buffer;
	};

	/** Internal buffer iterator used for reading/writing */
	struct net_pkt_cursor cursor;

	/** Network connection context */
	struct net_context *context;

	/** Network context token that user can set. This is passed
	 * to user callback when data has been sent.
	 */
	void *token;

	/** Network interface */
	struct net_if *iface;

	/** @cond ignore */

#if defined(CONFIG_NET_ROUTING)
	struct net_if *orig_iface; /* Original network interface */
#endif

#if defined(CONFIG_NET_PKT_TIMESTAMP)
	/** Timestamp if available. */
	struct net_ptp_time timestamp;
#endif
	/** Reference counter */
	atomic_t atomic_ref;

	/* Filled by layer 2 when network packet is received. */
	struct net_linkaddr lladdr_src;
	struct net_linkaddr lladdr_dst;

#if defined(CONFIG_NET_STATISTICS)
	/* If statistics is enabled, then speed up length calculation by
	 * doing it only once. This value is updated in net_if_queue_tx()
	 * when packet is about to be sent.
	 */
	u16_t total_pkt_len;
#endif
	u16_t data_len;         /* amount of payload data that can be added */

	u8_t ip_hdr_len;	/* pre-filled in order to avoid func call */

	u8_t overwrite  : 1;	/* Is packet content being overwritten? */

	u8_t sent_or_eof: 1;	/* For outgoing packet: is this sent or not
				 * For incoming packet of a socket: last
				 * packet before EOF
				 * Used only if defined(CONFIG_NET_TCP)
				 */
	union {
		u8_t pkt_queued: 1; /* For outgoing packet: is this packet
				     * queued to be sent but has not reached
				     * the driver yet.
				     * Used only if defined(CONFIG_NET_TCP)
				     */
		u8_t gptp_pkt: 1; /* For outgoing packet: is this packet
				   * a GPTP packet.
				   * Used only if defined (CONFIG_NET_GPTP)
				   */
	};

	u8_t forwarding : 1;	/* Are we forwarding this pkt
				 * Used only if defined(CONFIG_NET_ROUTE)
				 */
	u8_t family     : 3;	/* IPv4 vs IPv6 */

	union {
		u8_t ipv4_auto_arp_msg : 1; /* Is this pkt IPv4 autoconf ARP
					     * message. Used only if
					     * defined(CONFIG_NET_IPV4_AUTO).
					     * Note: family needs to be
					     * AF_INET.
					     */
		u8_t lldp_pkt          : 1; /* Is this pkt an LLDP message.
					     * Used only if
					     * defined(CONFIG_NET_LLDP).
					     * Note: family needs to be
					     * AF_UNSPEC.
					     */
	};

#if defined(CONFIG_NET_TCP)
	sys_snode_t sent_list;
#endif

	union {
		/* IPv6 hop limit or IPv4 ttl for this network packet.
		 * The value is shared between IPv6 and IPv4.
		 */
		u8_t ipv6_hop_limit;
		u8_t ipv4_ttl;
	};

#if NET_TC_COUNT > 1
	/** Network packet priority, can be left out in which case packet
	 * is not prioritised.
	 */
	u8_t priority;
#endif

#if defined(CONFIG_NET_VLAN)
	/* VLAN TCI (Tag Control Information). This contains the Priority
	 * Code Point (PCP), Drop Eligible Indicator (DEI) and VLAN
	 * Identifier (VID, called more commonly VLAN tag). This value is
	 * kept in host byte order.
	 */
	u16_t vlan_tci;
#endif /* CONFIG_NET_VLAN */

#if defined(CONFIG_NET_IPV6)
	u16_t ipv6_ext_len;	/* length of extension headers */

	/* Where is the start of the last header before payload data
	 * in IPv6 packet. This is offset value from start of the IPv6
	 * packet. Note that this value should be updated by who ever
	 * adds IPv6 extension headers to the network packet.
	 */
	u16_t ipv6_prev_hdr_start;

#if defined(CONFIG_NET_IPV6_FRAGMENT)
	u16_t ipv6_fragment_offset;	/* Fragment offset of this packet */
	u32_t ipv6_fragment_id;	/* Fragment id */
	u16_t ipv6_frag_hdr_start;	/* Where starts the fragment header */
#endif /* CONFIG_NET_IPV6_FRAGMENT */

	u8_t ipv6_ext_opt_len; /* IPv6 ND option length */
	u8_t ipv6_next_hdr;	/* What is the very first next header */
#endif /* CONFIG_NET_IPV6 */

#if defined(CONFIG_IEEE802154)
	u8_t ieee802154_rssi; /* Received Signal Strength Indication */
	u8_t ieee802154_lqi;  /* Link Quality Indicator */
#endif
	/* @endcond */
};

/** @cond ignore */

static inline struct k_work *net_pkt_work(struct net_pkt *pkt)
{
	return &pkt->work;
}

/* The interface real ll address */
static inline struct net_linkaddr *net_pkt_lladdr_if(struct net_pkt *pkt)
{
	return net_if_get_link_addr(pkt->iface);
}

static inline struct net_context *net_pkt_context(struct net_pkt *pkt)
{
	return pkt->context;
}

static inline void net_pkt_set_context(struct net_pkt *pkt,
				       struct net_context *ctx)
{
	pkt->context = ctx;
}

static inline void *net_pkt_token(struct net_pkt *pkt)
{
	return pkt->token;
}

static inline void net_pkt_set_token(struct net_pkt *pkt, void *token)
{
	pkt->token = token;
}

static inline struct net_if *net_pkt_iface(struct net_pkt *pkt)
{
	return pkt->iface;
}

static inline void net_pkt_set_iface(struct net_pkt *pkt, struct net_if *iface)
{
	pkt->iface = iface;

	/* If the network interface is set in pkt, then also set the type of
	 * the network address that is stored in pkt. This is done here so
	 * that the address type is properly set and is not forgotten.
	 */
	if (iface) {
		pkt->lladdr_src.type = net_if_get_link_addr(iface)->type;
		pkt->lladdr_dst.type = net_if_get_link_addr(iface)->type;
	}
}

static inline struct net_if *net_pkt_orig_iface(struct net_pkt *pkt)
{
#if defined(CONFIG_NET_ROUTING)
	return pkt->orig_iface;
#else
	return pkt->iface;
#endif
}

static inline void net_pkt_set_orig_iface(struct net_pkt *pkt,
					  struct net_if *iface)
{
#if defined(CONFIG_NET_ROUTING)
	pkt->orig_iface = iface;
#endif
}

static inline u8_t net_pkt_family(struct net_pkt *pkt)
{
	return pkt->family;
}

static inline void net_pkt_set_family(struct net_pkt *pkt, u8_t family)
{
	pkt->family = family;
}

static inline bool net_pkt_is_gptp(struct net_pkt *pkt)
{
	return !!(pkt->gptp_pkt);
}

static inline void net_pkt_set_gptp(struct net_pkt *pkt, bool is_gptp)
{
	pkt->gptp_pkt = is_gptp;
}

static inline u8_t net_pkt_ip_hdr_len(struct net_pkt *pkt)
{
	return pkt->ip_hdr_len;
}

static inline void net_pkt_set_ip_hdr_len(struct net_pkt *pkt, u8_t len)
{
	pkt->ip_hdr_len = len;
}

static inline u8_t net_pkt_sent(struct net_pkt *pkt)
{
	return pkt->sent_or_eof;
}

static inline void net_pkt_set_sent(struct net_pkt *pkt, bool sent)
{
	pkt->sent_or_eof = sent;
}

static inline u8_t net_pkt_queued(struct net_pkt *pkt)
{
	return pkt->pkt_queued;
}

static inline void net_pkt_set_queued(struct net_pkt *pkt, bool send)
{
	pkt->pkt_queued = send;
}

#if defined(CONFIG_NET_SOCKETS)
static inline u8_t net_pkt_eof(struct net_pkt *pkt)
{
	return pkt->sent_or_eof;
}

static inline void net_pkt_set_eof(struct net_pkt *pkt, bool eof)
{
	pkt->sent_or_eof = eof;
}
#endif

#if defined(CONFIG_NET_ROUTE)
static inline bool net_pkt_forwarding(struct net_pkt *pkt)
{
	return pkt->forwarding;
}

static inline void net_pkt_set_forwarding(struct net_pkt *pkt, bool forward)
{
	pkt->forwarding = forward;
}
#else
static inline bool net_pkt_forwarding(struct net_pkt *pkt)
{
	return false;
}
#endif

#if defined(CONFIG_NET_IPV4)
static inline u8_t net_pkt_ipv4_ttl(struct net_pkt *pkt)
{
	return pkt->ipv4_ttl;
}

static inline void net_pkt_set_ipv4_ttl(struct net_pkt *pkt,
					u8_t ttl)
{
	pkt->ipv4_ttl = ttl;
}
#else
static inline u8_t net_pkt_ipv4_ttl(struct net_pkt *pkt)
{
	ARG_UNUSED(pkt);

	return 0;
}

static inline void net_pkt_set_ipv4_ttl(struct net_pkt *pkt,
					u8_t ttl)
{
	ARG_UNUSED(pkt);
	ARG_UNUSED(ttl);
}
#endif

#if defined(CONFIG_NET_IPV6)
static inline u8_t net_pkt_ipv6_ext_opt_len(struct net_pkt *pkt)
{
	return pkt->ipv6_ext_opt_len;
}

static inline void net_pkt_set_ipv6_ext_opt_len(struct net_pkt *pkt,
						u8_t len)
{
	pkt->ipv6_ext_opt_len = len;
}

static inline u8_t net_pkt_ipv6_next_hdr(struct net_pkt *pkt)
{
	return pkt->ipv6_next_hdr;
}

static inline void net_pkt_set_ipv6_next_hdr(struct net_pkt *pkt, u8_t next_hdr)
{
	pkt->ipv6_next_hdr = next_hdr;
}

static inline u16_t net_pkt_ipv6_ext_len(struct net_pkt *pkt)
{
	return pkt->ipv6_ext_len;
}

static inline void net_pkt_set_ipv6_ext_len(struct net_pkt *pkt, u16_t len)
{
	pkt->ipv6_ext_len = len;
}

static inline u16_t net_pkt_ipv6_hdr_prev(struct net_pkt *pkt)
{
	return pkt->ipv6_prev_hdr_start;
}

static inline void net_pkt_set_ipv6_hdr_prev(struct net_pkt *pkt,
					     u16_t offset)
{
	pkt->ipv6_prev_hdr_start = offset;
}

static inline u8_t net_pkt_ipv6_hop_limit(struct net_pkt *pkt)
{
	return pkt->ipv6_hop_limit;
}

static inline void net_pkt_set_ipv6_hop_limit(struct net_pkt *pkt,
					      u8_t hop_limit)
{
	pkt->ipv6_hop_limit = hop_limit;
}
#else /* CONFIG_NET_IPV6 */
static inline u8_t net_pkt_ipv6_ext_opt_len(struct net_pkt *pkt)
{
	ARG_UNUSED(pkt);

	return 0;
}

static inline void net_pkt_set_ipv6_ext_opt_len(struct net_pkt *pkt,
						u8_t len)
{
	ARG_UNUSED(pkt);
	ARG_UNUSED(len);
}

static inline u8_t net_pkt_ipv6_next_hdr(struct net_pkt *pkt)
{
	ARG_UNUSED(pkt);

	return 0;
}

static inline void net_pkt_set_ipv6_next_hdr(struct net_pkt *pkt, u8_t next_hdr)
{
	ARG_UNUSED(pkt);
	ARG_UNUSED(next_hdr);
}

static inline u16_t net_pkt_ipv6_ext_len(struct net_pkt *pkt)
{
	ARG_UNUSED(pkt);

	return 0;
}

static inline void net_pkt_set_ipv6_ext_len(struct net_pkt *pkt, u16_t len)
{
	ARG_UNUSED(pkt);
	ARG_UNUSED(len);
}

static inline u16_t net_pkt_ipv6_hdr_prev(struct net_pkt *pkt)
{
	ARG_UNUSED(pkt);

	return 0;
}

static inline void net_pkt_set_ipv6_hdr_prev(struct net_pkt *pkt,
					     u16_t offset)
{
	ARG_UNUSED(pkt);
	ARG_UNUSED(offset);
}

static inline u8_t net_pkt_ipv6_hop_limit(struct net_pkt *pkt)
{
	ARG_UNUSED(pkt);

	return 0;
}

static inline void net_pkt_set_ipv6_hop_limit(struct net_pkt *pkt,
					      u8_t hop_limit)
{
	ARG_UNUSED(pkt);
	ARG_UNUSED(hop_limit);
}
#endif /* CONFIG_NET_IPV6 */

#if defined(CONFIG_NET_IPV6_FRAGMENT)
static inline u16_t net_pkt_ipv6_fragment_start(struct net_pkt *pkt)
{
	return pkt->ipv6_frag_hdr_start;
}

static inline void net_pkt_set_ipv6_fragment_start(struct net_pkt *pkt,
						   u16_t start)
{
	pkt->ipv6_frag_hdr_start = start;
}

static inline u16_t net_pkt_ipv6_fragment_offset(struct net_pkt *pkt)
{
	return pkt->ipv6_fragment_offset;
}

static inline void net_pkt_set_ipv6_fragment_offset(struct net_pkt *pkt,
						    u16_t offset)
{
	pkt->ipv6_fragment_offset = offset;
}

static inline u32_t net_pkt_ipv6_fragment_id(struct net_pkt *pkt)
{
	return pkt->ipv6_fragment_id;
}

static inline void net_pkt_set_ipv6_fragment_id(struct net_pkt *pkt,
						u32_t id)
{
	pkt->ipv6_fragment_id = id;
}
#else /* CONFIG_NET_IPV6_FRAGMENT */
static inline u16_t net_pkt_ipv6_fragment_start(struct net_pkt *pkt)
{
	ARG_UNUSED(pkt);

	return 0;
}

static inline void net_pkt_set_ipv6_fragment_start(struct net_pkt *pkt,
						   u16_t start)
{
	ARG_UNUSED(pkt);
	ARG_UNUSED(start);
}

static inline u16_t net_pkt_ipv6_fragment_offset(struct net_pkt *pkt)
{
	ARG_UNUSED(pkt);

	return 0;
}

static inline void net_pkt_set_ipv6_fragment_offset(struct net_pkt *pkt,
						    u16_t offset)
{
	ARG_UNUSED(pkt);
	ARG_UNUSED(offset);
}

static inline u32_t net_pkt_ipv6_fragment_id(struct net_pkt *pkt)
{
	ARG_UNUSED(pkt);

	return 0;
}

static inline void net_pkt_set_ipv6_fragment_id(struct net_pkt *pkt,
						u32_t id)
{
	ARG_UNUSED(pkt);
	ARG_UNUSED(id);
}
#endif /* CONFIG_NET_IPV6_FRAGMENT */

#if NET_TC_COUNT > 1
static inline u8_t net_pkt_priority(struct net_pkt *pkt)
{
	return pkt->priority;
}

static inline void net_pkt_set_priority(struct net_pkt *pkt,
					u8_t priority)
{
	pkt->priority = priority;
}
#else /* NET_TC_COUNT == 1 */
static inline u8_t net_pkt_priority(struct net_pkt *pkt)
{
	return 0;
}

#define net_pkt_set_priority(...)

#endif /* NET_TC_COUNT > 1 */

#if defined(CONFIG_NET_VLAN)
static inline u16_t net_pkt_vlan_tag(struct net_pkt *pkt)
{
	return net_eth_vlan_get_vid(pkt->vlan_tci);
}

static inline void net_pkt_set_vlan_tag(struct net_pkt *pkt, u16_t tag)
{
	pkt->vlan_tci = net_eth_vlan_set_vid(pkt->vlan_tci, tag);
}

static inline u8_t net_pkt_vlan_priority(struct net_pkt *pkt)
{
	return net_eth_vlan_get_pcp(pkt->vlan_tci);
}

static inline void net_pkt_set_vlan_priority(struct net_pkt *pkt,
					     u8_t priority)
{
	pkt->vlan_tci = net_eth_vlan_set_pcp(pkt->vlan_tci, priority);
}

static inline bool net_pkt_vlan_dei(struct net_pkt *pkt)
{
	return net_eth_vlan_get_dei(pkt->vlan_tci);
}

static inline void net_pkt_set_vlan_dei(struct net_pkt *pkt, bool dei)
{
	pkt->vlan_tci = net_eth_vlan_set_dei(pkt->vlan_tci, dei);
}

static inline void net_pkt_set_vlan_tci(struct net_pkt *pkt, u16_t tci)
{
	pkt->vlan_tci = tci;
}

static inline u16_t net_pkt_vlan_tci(struct net_pkt *pkt)
{
	return pkt->vlan_tci;
}
#else
static inline u16_t net_pkt_vlan_tag(struct net_pkt *pkt)
{
	return NET_VLAN_TAG_UNSPEC;
}

static inline void net_pkt_set_vlan_tag(struct net_pkt *pkt, u16_t tag)
{
	ARG_UNUSED(pkt);
	ARG_UNUSED(tag);
}

static inline u8_t net_pkt_vlan_priority(struct net_pkt *pkt)
{
	ARG_UNUSED(pkt);
	return 0;
}

static inline bool net_pkt_vlan_dei(struct net_pkt *pkt)
{
	return false;
}

static inline void net_pkt_set_vlan_dei(struct net_pkt *pkt, bool dei)
{
	ARG_UNUSED(pkt);
	ARG_UNUSED(dei);
}

static inline u16_t net_pkt_vlan_tci(struct net_pkt *pkt)
{
	return NET_VLAN_TAG_UNSPEC; /* assumes priority is 0 */
}

static inline void net_pkt_set_vlan_tci(struct net_pkt *pkt, u16_t tci)
{
	ARG_UNUSED(pkt);
	ARG_UNUSED(tci);
}
#endif

#if defined(CONFIG_NET_PKT_TIMESTAMP)
static inline struct net_ptp_time *net_pkt_timestamp(struct net_pkt *pkt)
{
	return &pkt->timestamp;
}

static inline void net_pkt_set_timestamp(struct net_pkt *pkt,
					 struct net_ptp_time *timestamp)
{
	pkt->timestamp.second = timestamp->second;
	pkt->timestamp.nanosecond = timestamp->nanosecond;
}
#else
static inline struct net_ptp_time *net_pkt_timestamp(struct net_pkt *pkt)
{
	ARG_UNUSED(pkt);

	return NULL;
}

static inline void net_pkt_set_timestamp(struct net_pkt *pkt,
					 struct net_ptp_time *timestamp)
{
	ARG_UNUSED(pkt);
	ARG_UNUSED(timestamp);
}
#endif /* CONFIG_NET_PKT_TIMESTAMP */

static inline size_t net_pkt_get_len(struct net_pkt *pkt)
{
	return net_buf_frags_len(pkt->frags);
}

static inline u8_t *net_pkt_data(struct net_pkt *pkt)
{
	return pkt->frags->data;
}

static inline u8_t *net_pkt_ip_data(struct net_pkt *pkt)
{
	return pkt->frags->data;
}

static inline struct net_linkaddr *net_pkt_lladdr_src(struct net_pkt *pkt)
{
	return &pkt->lladdr_src;
}

static inline struct net_linkaddr *net_pkt_lladdr_dst(struct net_pkt *pkt)
{
	return &pkt->lladdr_dst;
}

static inline void net_pkt_lladdr_swap(struct net_pkt *pkt)
{
	u8_t *addr = net_pkt_lladdr_src(pkt)->addr;

	net_pkt_lladdr_src(pkt)->addr = net_pkt_lladdr_dst(pkt)->addr;
	net_pkt_lladdr_dst(pkt)->addr = addr;
}

static inline void net_pkt_lladdr_clear(struct net_pkt *pkt)
{
	net_pkt_lladdr_src(pkt)->addr = NULL;
	net_pkt_lladdr_src(pkt)->len = 0;
}

#if defined(CONFIG_IEEE802154) || defined(CONFIG_IEEE802154_RAW_MODE)
static inline u8_t net_pkt_ieee802154_rssi(struct net_pkt *pkt)
{
	return pkt->ieee802154_rssi;
}

static inline void net_pkt_set_ieee802154_rssi(struct net_pkt *pkt,
					       u8_t rssi)
{
	pkt->ieee802154_rssi = rssi;
}

static inline u8_t net_pkt_ieee802154_lqi(struct net_pkt *pkt)
{
	return pkt->ieee802154_lqi;
}

static inline void net_pkt_set_ieee802154_lqi(struct net_pkt *pkt,
					      u8_t lqi)
{
	pkt->ieee802154_lqi = lqi;
}
#endif

#if defined(CONFIG_NET_IPV4_AUTO)
static inline bool net_pkt_ipv4_auto(struct net_pkt *pkt)
{
	return pkt->ipv4_auto_arp_msg;
}

static inline void net_pkt_set_ipv4_auto(struct net_pkt *pkt,
					 bool is_auto_arp_msg)
{
	pkt->ipv4_auto_arp_msg = is_auto_arp_msg;
}
#else /* CONFIG_NET_IPV4_AUTO */
static inline bool net_pkt_ipv4_auto(struct net_pkt *pkt)
{
	ARG_UNUSED(pkt);

	return false;
}

static inline void net_pkt_set_ipv4_auto(struct net_pkt *pkt,
					 bool is_auto_arp_msg)
{
	ARG_UNUSED(pkt);
	ARG_UNUSED(is_auto_arp_msg);
}
#endif /* CONFIG_NET_IPV4_AUTO */

#if defined(CONFIG_NET_LLDP)
static inline bool net_pkt_is_lldp(struct net_pkt *pkt)
{
	return pkt->lldp_pkt;
}

static inline void net_pkt_set_lldp(struct net_pkt *pkt, bool is_lldp)
{
	pkt->lldp_pkt = is_lldp;
}
#else
static inline bool net_pkt_is_lldp(struct net_pkt *pkt)
{
	ARG_UNUSED(pkt);

	return false;
}

static inline void net_pkt_set_lldp(struct net_pkt *pkt, bool is_lldp)
{
	ARG_UNUSED(pkt);
	ARG_UNUSED(is_lldp);
}
#endif /* CONFIG_NET_LLDP */

#define NET_IPV6_HDR(pkt) ((struct net_ipv6_hdr *)net_pkt_ip_data(pkt))
#define NET_IPV4_HDR(pkt) ((struct net_ipv4_hdr *)net_pkt_ip_data(pkt))

static inline void net_pkt_set_src_ipv6_addr(struct net_pkt *pkt)
{
	net_if_ipv6_select_src_addr(net_context_get_iface(
					    net_pkt_context(pkt)),
				    &NET_IPV6_HDR(pkt)->src);
}

static inline void net_pkt_set_overwrite(struct net_pkt *pkt, bool overwrite)
{
	pkt->overwrite = overwrite;
}

static inline bool net_pkt_is_being_overwritten(struct net_pkt *pkt)
{
	return pkt->overwrite;
}

/* @endcond */

/**
 * @brief Create a net_pkt slab
 *
 * A net_pkt slab is used to store meta-information about
 * network packets. It must be coupled with a data fragment pool
 * (:c:macro:`NET_PKT_DATA_POOL_DEFINE`) used to store the actual
 * packet data. The macro can be used by an application to define
 * additional custom per-context TX packet slabs (see
 * :c:func:`net_context_setup_pools`).
 *
 * @param name Name of the slab.
 * @param count Number of net_pkt in this slab.
 */
#define NET_PKT_SLAB_DEFINE(name, count)				\
	K_MEM_SLAB_DEFINE(name, sizeof(struct net_pkt), count, 4)

/* Backward compatibility macro */
#define NET_PKT_TX_SLAB_DEFINE(name, count) NET_PKT_SLAB_DEFINE(name, count)

/**
 * @brief Create a data fragment net_buf pool
 *
 * A net_buf pool is used to store actual data for
 * network packets. It must be coupled with a net_pkt slab
 * (:c:macro:`NET_PKT_SLAB_DEFINE`) used to store the packet
 * meta-information. The macro can be used by an application to
 * define additional custom per-context TX packet pools (see
 * :c:func:`net_context_setup_pools`).
 *
 * @param name Name of the pool.
 * @param count Number of net_buf in this pool.
 */
#define NET_PKT_DATA_POOL_DEFINE(name, count)				\
	NET_BUF_POOL_DEFINE(name, count, CONFIG_NET_BUF_DATA_SIZE,	\
			    CONFIG_NET_BUF_USER_DATA_SIZE, NULL)

/** @cond INTERNAL_HIDDEN */

#if defined(CONFIG_NET_DEBUG_NET_PKT_ALLOC) || \
	(CONFIG_NET_PKT_LOG_LEVEL >= LOG_LEVEL_DBG)
#define NET_PKT_DEBUG_ENABLED
#endif

#if defined(NET_PKT_DEBUG_ENABLED)

/* Debug versions of the net_pkt functions that are used when tracking
 * buffer usage.
 */

struct net_pkt *net_pkt_get_reserve_debug(struct k_mem_slab *slab,
					  s32_t timeout,
					  const char *caller,
					  int line);
#define net_pkt_get_reserve(slab, timeout)				\
	net_pkt_get_reserve_debug(slab, timeout, __func__, __LINE__)

struct net_buf *net_pkt_get_reserve_data_debug(struct net_buf_pool *pool,
					       s32_t timeout,
					       const char *caller,
					       int line);

#define net_pkt_get_reserve_data(pool, timeout)				\
	net_pkt_get_reserve_data_debug(pool, timeout, __func__, __LINE__)

struct net_pkt *net_pkt_get_rx_debug(struct net_context *context,
				     s32_t timeout,
				     const char *caller, int line);
#define net_pkt_get_rx(context, timeout)				\
	net_pkt_get_rx_debug(context, timeout, __func__, __LINE__)

struct net_pkt *net_pkt_get_tx_debug(struct net_context *context,
				     s32_t timeout,
				     const char *caller, int line);
#define net_pkt_get_tx(context, timeout)				\
	net_pkt_get_tx_debug(context, timeout, __func__, __LINE__)

struct net_pkt *net_pkt_get_reserve_rx_debug(s32_t timeout,
					     const char *caller, int line);
#define net_pkt_get_reserve_rx(timeout)					\
	net_pkt_get_reserve_rx_debug(timeout, __func__, __LINE__)

struct net_pkt *net_pkt_get_reserve_tx_debug(s32_t timeout,
					     const char *caller, int line);
#define net_pkt_get_reserve_tx(timeout)					\
	net_pkt_get_reserve_tx_debug(timeout, __func__, __LINE__)

struct net_buf *net_pkt_get_reserve_rx_data_debug(s32_t timeout,
						  const char *caller,
						  int line);
#define net_pkt_get_reserve_rx_data(timeout)				\
	net_pkt_get_reserve_rx_data_debug(timeout, __func__, __LINE__)

struct net_buf *net_pkt_get_reserve_tx_data_debug(s32_t timeout,
						  const char *caller,
						  int line);
#define net_pkt_get_reserve_tx_data(timeout)				\
	net_pkt_get_reserve_tx_data_debug(timeout, __func__, __LINE__)

struct net_buf *net_pkt_get_frag_debug(struct net_pkt *pkt,
				       s32_t timeout,
				       const char *caller, int line);
#define net_pkt_get_frag(pkt, timeout)					\
	net_pkt_get_frag_debug(pkt, timeout, __func__, __LINE__)

void net_pkt_unref_debug(struct net_pkt *pkt, const char *caller, int line);
#define net_pkt_unref(pkt) net_pkt_unref_debug(pkt, __func__, __LINE__)

struct net_pkt *net_pkt_ref_debug(struct net_pkt *pkt, const char *caller,
				  int line);
#define net_pkt_ref(pkt) net_pkt_ref_debug(pkt, __func__, __LINE__)

struct net_buf *net_pkt_frag_ref_debug(struct net_buf *frag,
				       const char *caller, int line);
#define net_pkt_frag_ref(frag) net_pkt_frag_ref_debug(frag, __func__, __LINE__)

void net_pkt_frag_unref_debug(struct net_buf *frag,
			      const char *caller, int line);
#define net_pkt_frag_unref(frag)				\
	net_pkt_frag_unref_debug(frag, __func__, __LINE__)

struct net_buf *net_pkt_frag_del_debug(struct net_pkt *pkt,
				       struct net_buf *parent,
				       struct net_buf *frag,
				       const char *caller, int line);
#define net_pkt_frag_del(pkt, parent, frag)				\
	net_pkt_frag_del_debug(pkt, parent, frag, __func__, __LINE__)

void net_pkt_frag_add_debug(struct net_pkt *pkt, struct net_buf *frag,
			    const char *caller, int line);
#define net_pkt_frag_add(pkt, frag)				\
	net_pkt_frag_add_debug(pkt, frag, __func__, __LINE__)

void net_pkt_frag_insert_debug(struct net_pkt *pkt, struct net_buf *frag,
			       const char *caller, int line);
#define net_pkt_frag_insert(pkt, frag)					\
	net_pkt_frag_insert_debug(pkt, frag, __func__, __LINE__)
#endif /* CONFIG_NET_DEBUG_NET_PKT_ALLOC ||
	* CONFIG_NET_PKT_LOG_LEVEL >= LOG_LEVEL_DBG
	*/
/** @endcond */

/**
 * @brief Print fragment list and the fragment sizes
 *
 * @details Only available if debugging is activated.
 *
 * @param pkt Network pkt.
 */
#if defined(NET_PKT_DEBUG_ENABLED)
void net_pkt_print_frags(struct net_pkt *pkt);
#else
#define net_pkt_print_frags(pkt)
#endif

/**
 * @brief Get packet from the given packet slab.
 *
 * @details Get network packet from the specific packet slab.
 *
 * @param slab Network packet slab.
 * @param timeout Affects the action taken should the net pkt slab be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return Network packet if successful, NULL otherwise.
 */
#if !defined(NET_PKT_DEBUG_ENABLED)
struct net_pkt *net_pkt_get_reserve(struct k_mem_slab *slab,
				    s32_t timeout);
#endif

/**
 * @brief Get packet from the RX packet slab.
 *
 * @details Get network packet from RX packet slab. You must have
 * network context before able to use this function.
 *
 * @param context Network context that will be related to this packet.
 * @param timeout Affects the action taken should the net pkt slab be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return Network packet if successful, NULL otherwise.
 */
#if !defined(NET_PKT_DEBUG_ENABLED)
struct net_pkt *net_pkt_get_rx(struct net_context *context,
			       s32_t timeout);
#endif

/**
 * @brief Get packet from the TX packets slab.
 *
 * @details Get network packet from TX packet slab. You must have
 * network context before able to use this function.
 *
 * @param context Network context that will be related to
 * this packet.
 * @param timeout Affects the action taken should the net pkt slab be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return Network packet if successful, NULL otherwise.
 */
#if !defined(NET_PKT_DEBUG_ENABLED)
struct net_pkt *net_pkt_get_tx(struct net_context *context,
			       s32_t timeout);
#endif

/**
 * @brief Get RX packet from slab
 *
 * @details Normally this version is not useful for applications
 * but is mainly used by network fragmentation code.
 *
 * @param timeout Affects the action taken should the net pkt slab be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return Network packet if successful, NULL otherwise.
 */
#if !defined(NET_PKT_DEBUG_ENABLED)
struct net_pkt *net_pkt_get_reserve_rx(s32_t timeout);
#endif

/**
 * @brief Get TX packet from slab
 *
 * @details Normally this version is not useful for applications
 * but is mainly used by network fragmentation code.
 *
 * @param timeout Affects the action taken should the net pkt slab be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return Network packet if successful, NULL otherwise.
 */
#if !defined(NET_PKT_DEBUG_ENABLED)
struct net_pkt *net_pkt_get_reserve_tx(s32_t timeout);
#endif

/**
 * @brief Get RX DATA buffer from pool.
 * Normally you should use net_pkt_get_frag() instead.
 *
 * @details Normally this version is not useful for applications
 * but is mainly used by network fragmentation code.
 *
 * @param timeout Affects the action taken should the net buf pool be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return Network buffer if successful, NULL otherwise.
 */
#if !defined(NET_PKT_DEBUG_ENABLED)
struct net_buf *net_pkt_get_reserve_rx_data(s32_t timeout);
#endif

/**
 * @brief Get TX DATA buffer from pool.
 * Normally you should use net_pkt_get_frag() instead.
 *
 * @details Normally this version is not useful for applications
 * but is mainly used by network fragmentation code.
 *
 * @param timeout Affects the action taken should the net buf pool be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return Network buffer if successful, NULL otherwise.
 */
#if !defined(NET_PKT_DEBUG_ENABLED)
struct net_buf *net_pkt_get_reserve_tx_data(s32_t timeout);
#endif

/**
 * @brief Get a data fragment that might be from user specific
 * buffer pool or from global DATA pool.
 *
 * @param pkt Network packet.
 * @param timeout Affects the action taken should the net buf pool be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return Network buffer if successful, NULL otherwise.
 */
#if !defined(NET_PKT_DEBUG_ENABLED)
struct net_buf *net_pkt_get_frag(struct net_pkt *pkt, s32_t timeout);
#endif

/**
 * @brief Place packet back into the available packets slab
 *
 * @details Releases the packet to other use. This needs to be
 * called by application after it has finished with the packet.
 *
 * @param pkt Network packet to release.
 *
 */
#if !defined(NET_PKT_DEBUG_ENABLED)
void net_pkt_unref(struct net_pkt *pkt);
#endif

/**
 * @brief Increase the packet ref count
 *
 * @details Mark the packet to be used still.
 *
 * @param pkt Network packet to ref.
 *
 * @return Network packet if successful, NULL otherwise.
 */
#if !defined(NET_PKT_DEBUG_ENABLED)
struct net_pkt *net_pkt_ref(struct net_pkt *pkt);
#endif

/**
 * @brief Increase the packet fragment ref count
 *
 * @details Mark the fragment to be used still.
 *
 * @param frag Network fragment to ref.
 *
 * @return a pointer on the referenced Network fragment.
 */
#if !defined(NET_PKT_DEBUG_ENABLED)
struct net_buf *net_pkt_frag_ref(struct net_buf *frag);
#endif

/**
 * @brief Decrease the packet fragment ref count
 *
 * @param frag Network fragment to unref.
 */
#if !defined(NET_PKT_DEBUG_ENABLED)
void net_pkt_frag_unref(struct net_buf *frag);
#endif

/**
 * @brief Delete existing fragment from a packet
 *
 * @param pkt Network packet from which frag belongs to.
 * @param parent parent fragment of frag, or NULL if none.
 * @param frag Fragment to delete.
 *
 * @return Pointer to the following fragment, or NULL if it had no
 *         further fragments.
 */
#if !defined(NET_PKT_DEBUG_ENABLED)
struct net_buf *net_pkt_frag_del(struct net_pkt *pkt,
				 struct net_buf *parent,
				 struct net_buf *frag);
#endif

/**
 * @brief Add a fragment to a packet at the end of its fragment list
 *
 * @param pkt pkt Network packet where to add the fragment
 * @param frag Fragment to add
 */
#if !defined(NET_PKT_DEBUG_ENABLED)
void net_pkt_frag_add(struct net_pkt *pkt, struct net_buf *frag);
#endif

/**
 * @brief Insert a fragment to a packet at the beginning of its fragment list
 *
 * @param pkt pkt Network packet where to insert the fragment
 * @param frag Fragment to insert
 */
#if !defined(NET_PKT_DEBUG_ENABLED)
void net_pkt_frag_insert(struct net_pkt *pkt, struct net_buf *frag);
#endif

/**
 * @brief Copy len bytes from src starting from	offset to dst
 *
 * This routine assumes that dst is formed of one fragment with enough space
 * to store @a len bytes starting from offset at src.
 *
 * @param dst Destination buffer
 * @param src Source buffer that may be fragmented
 * @param offset Starting point to copy from
 * @param len Number of bytes to copy
 * @return 0 on success
 * @return -ENOMEM on error
 */
int net_frag_linear_copy(struct net_buf *dst, struct net_buf *src,
			 u16_t offset, u16_t len);

/**
 * @brief Compact the fragment list of a packet.
 *
 * @details After this there is no more any free space in individual fragments.
 * @param pkt Network packet.
 *
 * @return True if compact success, False otherwise.
 */
bool net_pkt_compact(struct net_pkt *pkt);

/**
 * @brief Append data to fragment list of a packet
 *
 * @details Append data to last fragment. If there is not enough space in
 * last fragment then more data fragments will be added, unless there are
 * no free fragments and timeout occurs.
 *
 * @param pkt Network packet.
 * @param len Total length of input data
 * @param data Data to be added
 * @param timeout Affects the action taken should the net buf pool be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return Length of data actually added. This may be less than input
 *         length if other timeout than K_FOREVER was used, and there
 *         were no free fragments in a pool to accommodate all data.
 */
u16_t net_pkt_append(struct net_pkt *pkt, u16_t len, const u8_t *data,
		     s32_t timeout);

/**
 * @brief Append all data to fragment list of a packet (or fail)
 *
 * @details Append data to last fragment. If there is not enough space in
 * last fragment then more data fragments will be added. Return unsuccessful
 * status if there are no free fragments to accommodate all data and timeout
 * occurs.
 *
 * @param pkt Network packet.
 * @param len Total length of input data
 * @param data Data to be added
 * @param timeout Affects the action taken should the net buf pool be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return True if all the data is placed at end of fragment list,
 *         false otherwise (in which case packet may contain incomplete
 *         input data).
 */
static inline bool net_pkt_append_all(struct net_pkt *pkt, u16_t len,
				      const u8_t *data, s32_t timeout)
{
	return net_pkt_append(pkt, len, data, timeout) == len;
}

/**
 * @brief Append u8_t data to last fragment in fragment list of a packet
 *
 * @details Append data to last fragment. If there is not enough space in last
 * fragment then new data fragment will be created and will be added to
 * fragment list. Caller has to take care of endianness if needed.
 *
 * @param pkt Network packet.
 * @param data Data to be added
 *
 * @return True if all the data is placed at end of fragment list,
 *         False otherwise (In-case of false pkt might contain input
 *         data in the process of placing into fragments).
 */
static inline bool net_pkt_append_u8(struct net_pkt *pkt, u8_t data)
{
	return net_pkt_append_all(pkt, 1, &data, K_FOREVER);
}

/**
 * @brief Append u16_t data to last fragment in fragment list of a packet
 *
 * @details Append data to last fragment. If there is not enough space in last
 * fragment then new data fragment will be created and will be added to
 * fragment list. Caller has to take care of endianness if needed.
 *
 * @param pkt Network packet.
 * @param data Data to be added
 *
 * @return True if all the data is placed at end of fragment list,
 *         False otherwise (In-case of false pkt might contain input data
 *         in the process of placing into fragments).
 */
static inline bool net_pkt_append_be16(struct net_pkt *pkt, u16_t data)
{
	u16_t value = sys_cpu_to_be16(data);

	return net_pkt_append_all(pkt, sizeof(u16_t), (u8_t *)&value,
			      K_FOREVER);
}

/**
 * @brief Append u32_t data to last fragment in fragment list of a packet
 *
 * @details Append data to last fragment. If there is not enough space in last
 * fragment then new data fragment will be created and will be added to
 * fragment list. Caller has to take care of endianness if needed.
 *
 * @param pkt Network packet.
 * @param data Data to be added
 *
 * @return True if all the data is placed at end of fragment list,
 *         False otherwise (In-case of false pkt might contain input data
 *         in the process of placing into fragments).
 */
static inline bool net_pkt_append_be32(struct net_pkt *pkt, u32_t data)
{
	u32_t value = sys_cpu_to_be32(data);

	return net_pkt_append_all(pkt, sizeof(u32_t), (u8_t *)&value,
			      K_FOREVER);
}

/**
 * @brief Append u32_t data to last fragment in fragment list
 *
 * @details Append data to last fragment. If there is not enough space in last
 * fragment then new data fragment will be created and will be added to
 * fragment list. Convert data to LE.
 *
 * @param pkt Network packet fragment list.
 * @param data Data to be added
 *
 * @return True if all the data is placed at end of fragment list,
 *         False otherwise (In-case of false pkt might contain input data
 *         in the process of placing into fragments).
 */
static inline bool net_pkt_append_le32(struct net_pkt *pkt, u32_t data)
{
	u32_t value = sys_cpu_to_le32(data);

	return net_pkt_append_all(pkt, sizeof(u32_t), (u8_t *)&value,
			      K_FOREVER);
}

/**
 * @brief Append u8_t data to last fragment in fragment list of a packet
 *
 * @details Append data to last fragment. If there is not enough space in last
 * fragment then new data fragment will be created and will be added to
 * fragment list. Caller has to take care of endianness if needed.
 *
 * @param pkt Network packet.
 * @param data Data to be added
 * @param timeout Timeout for buffer allocations
 *
 * @return True if all the data is placed at end of fragment list,
 *         False otherwise (In-case of false pkt might contain input
 *         data in the process of placing into fragments).
 */
static inline bool net_pkt_append_u8_timeout(struct net_pkt *pkt, u8_t data,
					     s32_t timeout)
{
	return net_pkt_append_all(pkt, 1, &data, timeout);
}

/**
 * @brief Append u16_t data to last fragment in fragment list of a packet
 *
 * @details Append data to last fragment. If there is not enough space in last
 * fragment then new data fragment will be created and will be added to
 * fragment list. Caller has to take care of endianness if needed.
 *
 * @param pkt Network packet.
 * @param data Data to be added
 * @param timeout Timeout for buffer allocations
 *
 * @return True if all the data is placed at end of fragment list,
 *         False otherwise (In-case of false pkt might contain input data
 *         in the process of placing into fragments).
 */
static inline bool net_pkt_append_be16_timeout(struct net_pkt *pkt,
					       u16_t data,
					       s32_t timeout)
{
	u16_t value = sys_cpu_to_be16(data);

	return net_pkt_append_all(pkt, sizeof(u16_t), (u8_t *)&value,
				  timeout);
}

/**
 * @brief Append u32_t data to last fragment in fragment list of a packet
 *
 * @details Append data to last fragment. If there is not enough space in last
 * fragment then new data fragment will be created and will be added to
 * fragment list. Caller has to take care of endianness if needed.
 *
 * @param pkt Network packet.
 * @param data Data to be added
 * @param timeout Timeout for buffer allocations
 *
 * @return True if all the data is placed at end of fragment list,
 *         False otherwise (In-case of false pkt might contain input data
 *         in the process of placing into fragments).
 */
static inline bool net_pkt_append_be32_timeout(struct net_pkt *pkt,
					       u32_t data,
					       s32_t timeout)
{
	u32_t value = sys_cpu_to_be32(data);

	return net_pkt_append_all(pkt, sizeof(u32_t), (u8_t *)&value,
				  timeout);
}

/**
 * @brief Append u32_t data to last fragment in fragment list
 *
 * @details Append data to last fragment. If there is not enough space in last
 * fragment then new data fragment will be created and will be added to
 * fragment list. Convert data to LE.
 *
 * @param pkt Network packet fragment list.
 * @param data Data to be added
 * @param timeout Timeout for buffer allocations
 *
 * @return True if all the data is placed at end of fragment list,
 *         False otherwise (In-case of false pkt might contain input data
 *         in the process of placing into fragments).
 */
static inline bool net_pkt_append_le32_timeout(struct net_pkt *pkt,
					       u32_t data,
					       s32_t timeout)
{
	u32_t value = sys_cpu_to_le32(data);

	return net_pkt_append_all(pkt, sizeof(u32_t), (u8_t *)&value,
				  timeout);
}

/**
 * @brief Get data from buffer
 *
 * @details Get N number of bytes starting from fragment's offset. If the total
 * length of data is placed in multiple fragments, this function will read from
 * all fragments until it reaches N number of bytes. Caller has to take care of
 * endianness if needed.
 *
 * @param frag Network buffer fragment.
 * @param offset Offset of input buffer.
 * @param pos Pointer to position of offset after reading n number of bytes,
 *            this is with respect to return buffer(fragment).
 * @param len Total length of data to be read.
 * @param data Data will be copied here.
 *
 * @return Pointer to the fragment or
 *         NULL and pos is 0 after successful read,
 *         NULL and pos is 0xffff otherwise.
 */
struct net_buf *net_frag_read(struct net_buf *frag, u16_t offset,
			      u16_t *pos, u16_t len, u8_t *data);

/**
 * @brief Skip N number of bytes while reading buffer
 *
 * @details Skip N number of bytes starting from fragment's offset. If the total
 * length of data is placed in multiple fragments, this function will skip from
 * all fragments until it reaches N number of bytes. This function is useful
 * when unwanted data (e.g. not supported data in message) is part
 * of fragment and we want to skip it.
 *
 * @param frag Network buffer fragment.
 * @param offset Offset of input buffer.
 * @param pos Pointer to position of offset after reading n number of bytes,
 *            this is with respect to return buffer(fragment).
 * @param len Total length of data to be read.
 *
 * @return Pointer to the fragment or
 *         NULL and pos is 0 after successful skip,
 *         NULL and pos is 0xffff otherwise.
 */
static inline struct net_buf *net_frag_skip(struct net_buf *frag,
					    u16_t offset,
					    u16_t *pos, u16_t len)
{
	return net_frag_read(frag, offset, pos, len, NULL);
}

/**
 * @brief Get a byte value from fragmented buffer
 *
 * @param frag Network buffer fragment.
 * @param offset Offset of input buffer.
 * @param pos Pointer to position of offset after reading 2 bytes,
 *            this is with respect to return buffer(fragment).
 * @param value Value is returned
 *
 * @return Pointer to fragment after successful read,
 *         NULL otherwise (if pos is 0, NULL is not a failure case).
 */
static inline struct net_buf *net_frag_read_u8(struct net_buf *frag,
					      u16_t offset,
					      u16_t *pos,
					      u8_t *value)
{
	return net_frag_read(frag, offset, pos, 1, value);
}

/**
 * @brief Get 16 bit big endian value from fragmented buffer
 *
 * @param frag Network buffer fragment.
 * @param offset Offset of input buffer.
 * @param pos Pointer to position of offset after reading 2 bytes,
 *            this is with respect to return buffer(fragment).
 * @param value Value is returned
 *
 * @return Pointer to fragment after successful read,
 *         NULL otherwise (if pos is 0, NULL is not a failure case).
 */
struct net_buf *net_frag_read_be16(struct net_buf *frag, u16_t offset,
				   u16_t *pos, u16_t *value);

/**
 * @brief Get 32 bit big endian value from fragmented buffer
 *
 * @param frag Network buffer fragment.
 * @param offset Offset of input buffer.
 * @param pos Pointer to position of offset after reading 4 bytes,
 *            this is with respect to return buffer(fragment).
 * @param value Value is returned
 *
 * @return Pointer to fragment after successful read,
 *         NULL otherwise (if pos is 0, NULL is not a failure case).
 */
struct net_buf *net_frag_read_be32(struct net_buf *frag, u16_t offset,
				   u16_t *pos, u32_t *value);

/**
 * @brief Write data to an arbitrary offset in fragments list of a packet.
 *
 * @details Write data to an arbitrary offset in a series of fragments.
 * Offset is based on fragment 'size' and calculates from input fragment
 * starting position.
 *
 * Size in this context refers the fragment full size without link layer header
 * part. The fragment might have user written data in it, the amount of such
 * data is stored in frag->len variable (the frag->len is always <= frag->size).
 * If using this API, the tailroom in the fragments will be taken into use.
 *
 * If offset is more than already allocated length in fragment, then empty space
 * or extra empty fragments is created to reach proper offset.
 * If there is any data present on input fragment offset, then it will be
 * 'overwritten'. Use net_pkt_insert() api if you don't want to overwrite.
 *
 * Offset is calculated from starting point of data area in input fragment.
 * e.g. Pkt(Tx/Rx) - Frag1 - Frag2 - Frag3 - Frag4
 *      (Assume FRAG DATA SIZE is 100 bytes after link layer header)
 *
 *      1) net_pkt_write(pkt, frag2, 20, &pos, 20, data, K_FOREVER)
 *         In this case write starts from "frag2->data + 20",
 *         returns frag2, pos = 40
 *
 *      2) net_pkt_write(pkt, frag1, 150, &pos, 60, data, K_FOREVER)
 *         In this case write starts from "frag2->data + 50"
 *         returns frag3, pos = 10
 *
 *      3) net_pkt_write(pkt, frag1, 350, &pos, 30, data, K_FOREVER)
 *         In this case write starts from "frag4->data + 50"
 *         returns frag4, pos = 80
 *
 *      4) net_pkt_write(pkt, frag2, 110, &pos, 90, data, K_FOREVER)
 *         In this case write starts from "frag3->data + 10"
 *         returns frag4, pos = 0
 *
 *      5) net_pkt_write(pkt, frag4, 110, &pos, 20, data, K_FOREVER)
 *         In this case write creates new data fragment and starts from
 *         "frag5->data + 10"
 *         returns frag5, pos = 30
 *
 * If input argument frag is NULL, it will create new data fragment
 * and append at the end of fragment list.
 *
 * @param pkt    Network packet.
 * @param frag   Network buffer fragment.
 * @param offset Offset
 * @param pos    Position of offset after write completed (this will be
 *               relative to return fragment)
 * @param len    Length of the data to be written.
 * @param data   Data to be written
 * @param timeout Affects the action taken should the net buf pool be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return Pointer to the fragment and position (*pos) where write ended,
 *         NULL and pos is 0xffff otherwise.
 */
struct net_buf *net_pkt_write(struct net_pkt *pkt, struct net_buf *frag,
			      u16_t offset, u16_t *pos, u16_t len,
			      u8_t *data, s32_t timeout);

/* Write u8_t data to an arbitrary offset in fragment. */
static inline struct net_buf *net_pkt_write_u8(struct net_pkt *pkt,
					       struct net_buf *frag,
					       u16_t offset,
					       u16_t *pos,
					       u8_t data)
{
	return net_pkt_write(pkt, frag, offset, pos, sizeof(u8_t),
			     &data, K_FOREVER);
}

/* Write u16_t big endian value to an arbitrary offset in fragment. */
static inline struct net_buf *net_pkt_write_be16(struct net_pkt *pkt,
						 struct net_buf *frag,
						 u16_t offset,
						 u16_t *pos,
						 u16_t data)
{
	u16_t value = htons(data);

	return net_pkt_write(pkt, frag, offset, pos, sizeof(u16_t),
			     (u8_t *)&value, K_FOREVER);
}

/* Write u32_t big endian value to an arbitrary offset in fragment. */
static inline struct net_buf *net_pkt_write_be32(struct net_pkt *pkt,
						 struct net_buf *frag,
						 u16_t offset,
						 u16_t *pos,
						 u32_t data)
{
	u32_t value = htonl(data);

	return net_pkt_write(pkt, frag, offset, pos, sizeof(u32_t),
			     (u8_t *)&value, K_FOREVER);
}

/* Write u8_t data to an arbitrary offset in fragment. */
static inline struct net_buf *net_pkt_write_u8_timeout(struct net_pkt *pkt,
						       struct net_buf *frag,
						       u16_t offset,
						       u16_t *pos,
						       u8_t data,
						       s32_t timeout)
{
	return net_pkt_write(pkt, frag, offset, pos, sizeof(u8_t),
			     &data, timeout);
}

/* Write u16_t big endian value to an arbitrary offset in fragment. */
static inline struct net_buf *net_pkt_write_be16_timeout(struct net_pkt *pkt,
							 struct net_buf *frag,
							 u16_t offset,
							 u16_t *pos,
							 u16_t data,
							 s32_t timeout)
{
	u16_t value = htons(data);

	return net_pkt_write(pkt, frag, offset, pos, sizeof(u16_t),
			     (u8_t *)&value, timeout);
}

/* Write u32_t big endian value to an arbitrary offset in fragment. */
static inline struct net_buf *net_pkt_write_be32_timeout(struct net_pkt *pkt,
							 struct net_buf *frag,
							 u16_t offset,
							 u16_t *pos,
							 u32_t data,
							 s32_t timeout)
{
	u32_t value = htonl(data);

	return net_pkt_write(pkt, frag, offset, pos, sizeof(u32_t),
			     (u8_t *)&value, timeout);
}

/**
 * @brief Insert data at an arbitrary offset in a series of fragments.
 *
 * @details Insert data at an arbitrary offset in a series of fragments. Offset
 * is based on fragment length (only user written data length, any tailroom
 * in fragments does not come to consideration unlike net_pkt_write()) and
 * calculates from input fragment starting position.
 * If the data pointer is NULL, insert a sequence of zeros with the given
 * length.
 *
 * Offset examples can be considered from net_pkt_write() api.
 * If the offset is more than already allocated fragments length then it is an
 * error case.
 *
 * @param pkt    Network packet.
 * @param frag   Network buffer fragment.
 * @param offset Offset of fragment where insertion will start.
 * @param len    Length of the data to be inserted.
 * @param data   Data to be inserted, can be NULL.
 * @param timeout Affects the action taken should the net buf pool be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return True on success, False otherwise.
 */
bool net_pkt_insert(struct net_pkt *pkt, struct net_buf *frag,
		    u16_t offset, u16_t len, u8_t *data,
		    s32_t timeout);

/**
 * @brief Insert u8_t data at an arbitrary offset in a series of fragments.
 *
 * @param pkt    Network packet.
 * @param frag   Network buffer fragment.
 * @param offset Offset of fragment where insertion will start.
 * @param data   Data to be inserted, can be NULL.
 *
 * @return True on success, False otherwise.
 */
static inline bool net_pkt_insert_u8(struct net_pkt *pkt,
				     struct net_buf *frag,
				     u16_t offset,
				     u8_t data)
{
	return net_pkt_insert(pkt, frag, offset, sizeof(u8_t), &data,
			      K_FOREVER);
}

/**
 * @brief Insert u16_t data at an arbitrary offset in a series of fragments.
 *
 * @param pkt    Network packet.
 * @param frag   Network buffer fragment.
 * @param offset Offset of fragment where insertion will start.
 * @param data   Data to be inserted, can be NULL.
 *
 * @return True on success, False otherwise.
 */
static inline bool net_pkt_insert_be16(struct net_pkt *pkt,
				       struct net_buf *frag,
				       u16_t offset,
				       u16_t data)
{
	u16_t value = htons(data);

	return net_pkt_insert(pkt, frag, offset, sizeof(u16_t),
			      (u8_t *)&value, K_FOREVER);
}

/**
 * @brief Insert u32_t data at an arbitrary offset in a series of fragments.
 *
 * @param pkt    Network packet.
 * @param frag   Network buffer fragment.
 * @param offset Offset of fragment where insertion will start.
 * @param data   Data to be inserted, can be NULL.
 *
 * @return True on success, False otherwise.
 */
static inline bool net_pkt_insert_be32(struct net_pkt *pkt,
				       struct net_buf *frag,
				       u16_t offset,
				       u32_t data)
{
	u32_t value = htonl(data);

	return net_pkt_insert(pkt, frag, offset, sizeof(u32_t),
			      (u8_t *)&value, K_FOREVER);
}

/**
 * @brief Insert u8_t data at an arbitrary offset in a series of fragments.
 *
 * @param pkt    Network packet.
 * @param frag   Network buffer fragment.
 * @param offset Offset of fragment where insertion will start.
 * @param data   Data to be inserted, can be NULL.
 * @param timeout Affects the action taken should the net buf pool be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return True on success, False otherwise.
 */
static inline bool net_pkt_insert_u8_timeout(struct net_pkt *pkt,
					     struct net_buf *frag,
					     u16_t offset,
					     u8_t data,
					     s32_t timeout)
{
	return net_pkt_insert(pkt, frag, offset, sizeof(u8_t), &data,
			      timeout);
}

/**
 * @brief Insert u16_t data at an arbitrary offset in a series of fragments.
 *
 * @param pkt    Network packet.
 * @param frag   Network buffer fragment.
 * @param offset Offset of fragment where insertion will start.
 * @param data   Data to be inserted, can be NULL.
 * @param timeout Affects the action taken should the net buf pool be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return True on success, False otherwise.
 */
static inline bool net_pkt_insert_be16_timeout(struct net_pkt *pkt,
					       struct net_buf *frag,
					       u16_t offset,
					       u16_t data,
					       s32_t timeout)
{
	u16_t value = htons(data);

	return net_pkt_insert(pkt, frag, offset, sizeof(u16_t),
			      (u8_t *)&value, timeout);
}

/**
 * @brief Insert u32_t data at an arbitrary offset in a series of fragments.
 *
 * @param pkt    Network packet.
 * @param frag   Network buffer fragment.
 * @param offset Offset of fragment where insertion will start.
 * @param data   Data to be inserted, can be NULL.
 * @param timeout Affects the action taken should the net buf pool be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return True on success, False otherwise.
 */
static inline bool net_pkt_insert_be32_timeout(struct net_pkt *pkt,
					       struct net_buf *frag,
					       u16_t offset,
					       u32_t data,
					       s32_t timeout)
{
	u32_t value = htonl(data);

	return net_pkt_insert(pkt, frag, offset, sizeof(u32_t),
			      (u8_t *)&value, timeout);
}

/**
 * @brief Return the fragment and offset within it according to network
 * packet offset.
 *
 * @details This is typically used to get the protocol header pointer when
 * we know the offset. According to this information, the corresponding fragment
 * and position within that fragment is returned.
 *
 * @param pkt Network packet
 * @param offset Offset of desired location in network packet. For example, if
 * we want to know where UDP header is located after the IPv6 header,
 * the offset could have a value of sizeof(struct net_ipv6_hdr). Note that this
 * is a simplified example that does not take into account the possible IPv6
 * extension headers.
 * @param pos Pointer to position within result fragment corresponding to
 * offset param. For example, if the IPv6 header is split between two fragments,
 * then if we want to know the start of UDP header, the returned pos variable
 * would indicate how many bytes from second fragment the UDP header starts.
 *
 * @return Pointer to the fragment where the the offset is located or
 *         NULL if there is not enough bytes in the packet
 */
struct net_buf *net_frag_get_pos(struct net_pkt *pkt,
				 u16_t offset,
				 u16_t *pos);

/**
 * @brief Get information about predefined RX, TX and DATA pools.
 *
 * @param rx Pointer to RX pool is returned.
 * @param tx Pointer to TX pool is returned.
 * @param rx_data Pointer to RX DATA pool is returned.
 * @param tx_data Pointer to TX DATA pool is returned.
 */
void net_pkt_get_info(struct k_mem_slab **rx,
		      struct k_mem_slab **tx,
		      struct net_buf_pool **rx_data,
		      struct net_buf_pool **tx_data);

/** @cond INTERNAL_HIDDEN */

#if defined(CONFIG_NET_DEBUG_NET_PKT_ALLOC)
/**
 * @brief Debug helper to print out the buffer allocations
 */
void net_pkt_print(void);

typedef void (*net_pkt_allocs_cb_t)(struct net_pkt *pkt,
				    struct net_buf *buf,
				    const char *func_alloc,
				    int line_alloc,
				    const char *func_free,
				    int line_free,
				    bool in_use,
				    void *user_data);

void net_pkt_allocs_foreach(net_pkt_allocs_cb_t cb, void *user_data);

const char *net_pkt_slab2str(struct k_mem_slab *slab);
const char *net_pkt_pool2str(struct net_buf_pool *pool);

#else
#define net_pkt_print(...)
#endif /* CONFIG_NET_DEBUG_NET_PKT_ALLOC */

/* New allocator, and API are defined below.
 * This will be simpler when time will come to get rid of former API above.
 */
#if defined(NET_PKT_DEBUG_ENABLED)

struct net_pkt *net_pkt_alloc_debug(s32_t timeout,
				    const char *caller, int line);
#define net_pkt_alloc(_timeout)					\
	net_pkt_alloc_debug(_timeout, __func__, __LINE__)

struct net_pkt *net_pkt_alloc_from_slab_debug(struct k_mem_slab *slab,
					      s32_t timeout,
					      const char *caller, int line);
#define net_pkt_alloc_from_slab(_slab, _timeout)			\
	net_pkt_alloc_from_slab_debug(_slab, _timeout, __func__, __LINE__)

struct net_pkt *net_pkt_rx_alloc_debug(s32_t timeout,
				       const char *caller, int line);
#define net_pkt_rx_alloc(_timeout)				\
	net_pkt_rx_alloc_debug(_timeout, __func__, __LINE__)

struct net_pkt *net_pkt_alloc_on_iface_debug(struct net_if *iface,
					     s32_t timeout,
					     const char *caller,
					     int line);
#define net_pkt_alloc_on_iface(_iface, _timeout)			\
	net_pkt_alloc_on_iface_debug(_iface, _timeout, __func__, __LINE__)

struct net_pkt *net_pkt_rx_alloc_on_iface_debug(struct net_if *iface,
						s32_t timeout,
						const char *caller,
						int line);
#define net_pkt_rx_alloc_on_iface(_iface, _timeout)			\
	net_pkt_rx_alloc_on_iface_debug(_iface, _timeout,		\
					__func__, __LINE__)

int net_pkt_alloc_buffer_debug(struct net_pkt *pkt,
			       size_t size,
			       enum net_ip_protocol proto,
			       s32_t timeout,
			       const char *caller, int line);
#define net_pkt_alloc_buffer(_pkt, _size, _proto, _timeout)		\
	net_pkt_alloc_buffer_debug(_pkt, _size, _proto, _timeout,	\
				   __func__, __LINE__)

struct net_pkt *net_pkt_alloc_with_buffer_debug(struct net_if *iface,
						size_t size,
						sa_family_t family,
						enum net_ip_protocol proto,
						s32_t timeout,
						const char *caller,
						int line);
#define net_pkt_alloc_with_buffer(_iface, _size, _family,		\
				  _proto, _timeout)			\
	net_pkt_alloc_with_buffer_debug(_iface, _size, _family,		\
					_proto, _timeout,		\
					__func__, __LINE__)

struct net_pkt *net_pkt_rx_alloc_with_buffer_debug(struct net_if *iface,
						   size_t size,
						   sa_family_t family,
						   enum net_ip_protocol proto,
						   s32_t timeout,
						   const char *caller,
						   int line);
#define net_pkt_rx_alloc_with_buffer(_iface, _size, _family,		\
				     _proto, _timeout)			\
	net_pkt_rx_alloc_with_buffer_debug(_iface, _size, _family,	\
					   _proto, _timeout,		\
					   __func__, __LINE__)
#endif /* NET_PKT_DEBUG_ENABLED */
/** @endcond */

/**
 * @brief Allocate an initialized net_pkt
 *
 * Note: for the time being, 2 pools are used. One for TX and one for RX.
 *       This allocator has to be used for TX.
 *
 * @param timeout Maximum time in milliseconds to wait for an allocation.
 *
 * @return a pointer to a newly allocated net_pkt on success, NULL otherwise.
 */
#if !defined(NET_PKT_DEBUG_ENABLED)
struct net_pkt *net_pkt_alloc(s32_t timeout);
#endif

/**
 * @brief Allocate an initialized net_pkt from a specific slab
 *
 * @details unlike net_pkt_alloc() which uses core slabs, this one will use
 *          an external slab (see NET_PKT_SLAB_DEFINE()).
 *          Do _not_ use it unless you know what you are doing. Basically, only
 *          net_context should be using this, in order to allocate packet and
 *          then buffer on its local slab/pool (if any).
 *
 * @param slab    The slab to use for allocating the packet
 * @param timeout Maximum time in milliseconds to wait for an allocation.
 *
 * @return a pointer to a newly allocated net_pkt on success, NULL otherwise.
 */
#if !defined(NET_PKT_DEBUG_ENABLED)
struct net_pkt *net_pkt_alloc_from_slab(struct k_mem_slab *slab,
					s32_t timeout);
#endif

/**
 * @brief Allocate an initialized net_pkt for RX
 *
 * Note: for the time being, 2 pools are used. One for TX and one for RX.
 *       This allocator has to be used for RX.
 *
 * @param timeout Maximum time in milliseconds to wait for an allocation.
 *
 * @return a pointer to a newly allocated net_pkt on success, NULL otherwise.
 */
#if !defined(NET_PKT_DEBUG_ENABLED)
struct net_pkt *net_pkt_rx_alloc(s32_t timeout);
#endif

/**
 * @brief Allocate a network packet for a specific network interface.
 *
 * @param iface The network interface the packet is supposed to go through.
 * @param timeout Maximum time in milliseconds to wait for an allocation.
 *
 * @return a pointer to a newly allocated net_pkt on success, NULL otherwise.
 */
#if !defined(NET_PKT_DEBUG_ENABLED)
struct net_pkt *net_pkt_alloc_on_iface(struct net_if *iface, s32_t timeout);

/* Same as above but specifically for RX packet */
struct net_pkt *net_pkt_rx_alloc_on_iface(struct net_if *iface, s32_t timeout);
#endif

/**
 * @brief Allocate buffer for a net_pkt
 *
 * Note: such allocator will take into account space necessary for headers,
 *       MTU, and existing buffer (if any). Beware that, due to all these
 *       criteria, the allocated size might be smaller/bigger than requested
 *       one.
 *
 * @param pkt     The network packet requiring buffer to be allocated.
 * @param size    The size of buffer being requested.
 * @param proto   The IP protocol type (can be 0 for none).
 * @param timeout Maximum time in milliseconds to wait for an allocation.
 *
 * @return 0 on success, negative errno code otherwise.
 */
#if !defined(NET_PKT_DEBUG_ENABLED)
int net_pkt_alloc_buffer(struct net_pkt *pkt,
			 size_t size,
			 enum net_ip_protocol proto,
			 s32_t timeout);
#endif

/**
 * @brief Allocate a network packet and buffer at once
 *
 * @param iface   The network interface the packet is supposed to go through.
 * @param size    The size of buffer.
 * @param family  The family to which the packet belongs.
 * @param proto   The IP protocol type (can be 0 for none).
 * @param timeout Maximum time in milliseconds to wait for an allocation.
 *
 * @return a pointer to a newly allocated net_pkt on success, NULL otherwise.
 */
#if !defined(NET_PKT_DEBUG_ENABLED)
struct net_pkt *net_pkt_alloc_with_buffer(struct net_if *iface,
					  size_t size,
					  sa_family_t family,
					  enum net_ip_protocol proto,
					  s32_t timeout);

/* Same as above but specifically for RX packet */
struct net_pkt *net_pkt_rx_alloc_with_buffer(struct net_if *iface,
					     size_t size,
					     sa_family_t family,
					     enum net_ip_protocol proto,
					     s32_t timeout);
#endif

/**
 * @brief Append a buffer in packet
 *
 * @param pkt    Network packet where to append the buffer
 * @param buffer Buffer to append
 */
void net_pkt_append_buffer(struct net_pkt *pkt, struct net_buf *buffer);

/**
 * @brief Get available buffer space from a pkt
 *
 * @param pkt The net_pkt which buffer availability should be evaluated
 *
 * @return the amount of buffer available
 */
size_t net_pkt_available_buffer(struct net_pkt *pkt);

/**
 * @brief Get available buffer space for payload from a pkt
 *
 * Note: Unlike net_pkt_available_buffer(), this will take into account the
 *       headers space.
 *
 * @param pkt   The net_pkt which payload buffer availability should
 *              be evaluated
 * @param proto The IP protocol type (can be 0 for none).
 *
 * @return the amount of buffer available for payload
 */
size_t net_pkt_available_payload_buffer(struct net_pkt *pkt,
					enum net_ip_protocol proto);

/**
 * @brief Trim net_pkt buffer
 *
 * Note: This will basically check for unused net_buf buffer and
 *       deallocates them relevantly
 *
 * @param pkt The net_pkt which buffer will be trimmed
 */
void net_pkt_trim_buffer(struct net_pkt *pkt);

/**
 * @brief Initialize net_pkt cursor
 *
 * Note: This will initialize the net_pkt cursor from its buffer.
 *
 * @param pkt The net_pkt whose cursor is going to be initialized
 */
void net_pkt_cursor_init(struct net_pkt *pkt);

/**
 * @brief Backup net_pkt cursor
 *
 * @param pkt    The net_pkt whose cursor is going to be backed up
 * @param backup The cursor where to backup net_pkt cursor
 */
static inline void net_pkt_cursor_backup(struct net_pkt *pkt,
					 struct net_pkt_cursor *backup)
{
	backup->buf = pkt->cursor.buf;
	backup->pos = pkt->cursor.pos;
}

/**
 * @brief Restore net_pkt cursor from a backup
 *
 * @param pkt    The net_pkt whose cursor is going to be restored
 * @param backup The cursor from where to restore net_pkt cursor
 */
static inline void net_pkt_cursor_restore(struct net_pkt *pkt,
					  struct net_pkt_cursor *backup)
{
	pkt->cursor.buf = backup->buf;
	pkt->cursor.pos = backup->pos;
}

/**
 * @brief Returns current position of the cursor
 *
 * @param pkt The net_pkt whose cursor position is going to be returned
 *
 * @return cursor's position
 */
static inline void *net_pkt_cursor_get_pos(struct net_pkt *pkt)
{
	return pkt->cursor.pos;
}

/**
 * @brief Skip some data from a net_pkt
 *
 * Note: net_pkt's cursor should be properly initialized
 *       Cursor position will be updated after the operation.
 *       Depending on the value of pkt->overwrite bit, this function
 *       will affect the buffer length or not: if it's 0, skip will
 *       actually apply the move in the buffer as it had written in it.
 *
 * @param pkt    The net_pkt whose cursor will be updated to skip given
 *               amount of data from the buffer.
 * @param length Amount of data to skip in the buffer
 *
 * @return 0 in success, negative errno code otherwise.
 */
int net_pkt_skip(struct net_pkt *pkt, size_t length);

/**
 * @brief Memset some data in a net_pkt
 *
 * Note: net_pkt's cursor should be properly initialized and, if needed,
 *       positioned using net_pkt_skip.
 *       Cursor position will be updated after the operation.
 *
 * @param pkt    The net_pkt whose buffer to fill starting at the current
 *               cursor position.
 * @param byte   The byte to write in memory
 * @param length Amount of data to memset with given byte
 *
 * @return 0 in success, negative errno code otherwise.
 */
int net_pkt_memset(struct net_pkt *pkt, int byte, size_t length);

/**
 * @brief Copy data from a packet into another one.
 *
 * Note: Both net_pkt cursors should be properly initialized and, if needed,
 *       positioned using net_pkt_skip.
 *       The cursors will be updated after the operation.
 *
 * @param pkt_dst Destination network packet.
 * @param pkt_src Source network packet.
 * @param length  Length of data to be copied.
 *
 * @return 0 on success, negative errno code otherwise.
 */
int net_pkt_copy(struct net_pkt *pkt_dst,
		 struct net_pkt *pkt_src,
		 size_t length);

/**
 * @brief Clone pkt and its buffer.
 *
 * @param pkt Original pkt to be cloned
 * @param timeout Timeout to wait for free buffer
 *
 * @return NULL if error, cloned packet otherwise.
 */
struct net_pkt *net_pkt_clone(struct net_pkt *pkt, s32_t timeout);

/**
 * @brief Read some data from a net_pkt
 *
 * Note: net_pkt's cursor should be properly initialized and, if needed,
 *       positioned using net_pkt_skip.
 *       Cursor position will be updated after the operation.
 * @param pkt    The network packet from where to read some data
 * @param data   The destination buffer where to copy the data
 * @param length The amount of data to copy
 *
 * @return 0 on success, negative errno code otherwise.
 */
int net_pkt_read(struct net_pkt *pkt, void *data, size_t length);

/* Read u8_t data data a net_pkt */
static inline int net_pkt_read_u8(struct net_pkt *pkt, u8_t *data)
{
	return net_pkt_read(pkt, data, 1);
}

/**
 * @brief Read u16_t big endian data from a net_pkt
 *
 * Note: net_pkt's cursor should be properly initialized and,
 *       eventually, properly positioned using net_pkt_skip.
 *       Cursor position will be updated after the operation.
 *
 * @param pkt  The network packet from where to read
 * @param data The destination u16_t where to copy the data
 *
 * @return 0 on success, negative errno code otherwise.
 */
int net_pkt_read_be16(struct net_pkt *pkt, u16_t *data);

/**
 * @brief Read u32_t big endian data from a net_pkt
 *
 * Note: net_pkt's cursor should be properly initialized and,
 *       eventually, properly positioned using net_pkt_skip.
 *       Cursor position will be updated after the operation.
 *
 * @param pkt  The network packet from where to read
 * @param data The destination u32_t where to copy the data
 *
 * @return 0 on success, negative errno code otherwise.
 */
int net_pkt_read_be32(struct net_pkt *pkt, u32_t *data);

/**
 * @brief Write data into a net_pkt
 *
 * Note: net_pkt's cursor should be properly initialized and, if needed,
 *       positioned using net_pkt_skip.
 *       Cursor position will be updated after the operation.
 *
 * @param pkt    The network packet where to write
 * @param data   Data to be written
 * @param length Length of the data to be written
 *
 * @return 0 on success, negative errno code otherwise.
 */
int net_pkt_write_new(struct net_pkt *pkt, const void *data, size_t length);

/* Write u8_t data into a net_pkt. */
static inline int net_pkt_write_u8_new(struct net_pkt *pkt, u8_t data)
{
	return net_pkt_write_new(pkt, &data, sizeof(u8_t));
}

/* Write u16_t big endian data into a net_pkt. */
static inline int net_pkt_write_be16_new(struct net_pkt *pkt, u16_t data)
{
	u16_t data_be16 = htons(data);

	return net_pkt_write_new(pkt, &data_be16, sizeof(u16_t));
}

/* Write u32_t big endian data into a net_pkt. */
static inline int net_pkt_write_be32_new(struct net_pkt *pkt, u32_t data)
{
	u32_t data_be32 = htonl(data);

	return net_pkt_write_new(pkt, &data_be32, sizeof(u32_t));
}

/* Write u32_t little endian data into a net_pkt. */
static inline int net_pkt_write_le32_new(struct net_pkt *pkt, u32_t data)
{
	u32_t data_le32 = sys_cpu_to_le32(data);

	return net_pkt_write_new(pkt, &data_le32, sizeof(u32_t));
}

/**
 * @brief Get the amount of data which can be read from current cursor position
 *
 * @param pkt Network packet
 *
 * @return Amount of data which can be read from current pkt cursor
 */
size_t net_pkt_remaining_data(struct net_pkt *pkt);

/**
 * @brief Update the overall length of a packet
 *
 * Note: Unlike net_pkt_pull() below, this does not take packet cursor
 *       into account. It's mainly a helper dedicated for ipv4 and ipv6
 *       input functions. It shrinks the overall length by given parameter.
 *
 * @param pkt    Network packet
 * @param length The new length of the packet
 *
 * @return 0 on success, negative errno code otherwise.
 */
int net_pkt_update_length(struct net_pkt *pkt, size_t length);

/**
 * @brief Remove data from the packet at current location
 *
 * Note: net_pkt's cursor should be properly initialized and,
 *       eventually, properly positioned using net_pkt_skip/read/write.
 *
 * @param pkt    Network packet
 * @param length Number of bytes to be removed
 *
 * @return 0 on success, negative errno code otherwise.
 */
int net_pkt_pull(struct net_pkt *pkt, size_t length);

/**
 * @brief Get the actual offset in the packet from its cursor
 *
 * @param pkt Network packet.
 *
 * @return a valid offset on success, 0 otherwise as there is nothing that
 *         can be done to evaluate the offset.
 */
u16_t net_pkt_get_current_offset(struct net_pkt *pkt);

/**
 * @brief Check if a data size could fit contiguously
 *
 * Note: net_pkt's cursor should be properly initialized and, if needed,
 *       positioned using net_pkt_skip.
 *
 * @param pkt  Network packet.
 * @param size The size to check for contiguity
 *
 * @return true if that is the case, false otherwise.
 */
bool net_pkt_is_contiguous(struct net_pkt *pkt, size_t size);

struct net_pkt_data_access {
#if !defined(CONFIG_NET_HEADERS_ALWAYS_CONTIGUOUS)
	void *data;
#endif
	const size_t size;
};

#if defined(CONFIG_NET_HEADERS_ALWAYS_CONTIGUOUS)
#define NET_PKT_DATA_ACCESS_DEFINE(_name, _type)		\
	struct net_pkt_data_access _name = {			\
		.size = sizeof(_type),				\
	}

#define NET_PKT_DATA_ACCESS_CONTIGUOUS_DEFINE(_name, _type)	\
	NET_PKT_DATA_ACCESS_DEFINE(_name, _type)

#else
#define NET_PKT_DATA_ACCESS_DEFINE(_name, _type)		\
	_type _hdr_##_name;					\
	struct net_pkt_data_access _name = {			\
		.data = &_hdr_##_name,				\
		.size = sizeof(_type),				\
	}

#define NET_PKT_DATA_ACCESS_CONTIGUOUS_DEFINE(_name, _type)	\
	struct net_pkt_data_access _name = {			\
		.data = NULL,					\
		.size = sizeof(_type),				\
	}

#endif /* CONFIG_NET_HEADERS_ALWAYS_CONTIGUOUS */

/**
 * @brief Get data from a network packet in a contiguous way
 *
 * Note: net_pkt's cursor should be properly initialized and, if needed,
 *       positioned using net_pkt_skip.
 *       Cursor position will be updated after the operation.
 *
 * @param pkt    The network packet from where to get the data.
 * @param access A pointer to a valid net_pkt_data_access describing the
 *        data to get in a contiguous way.
 *
 * @return a pointer to the requested contiguous data, NULL otherwise.
 */
void *net_pkt_get_data(struct net_pkt *pkt,
		       struct net_pkt_data_access *access);

/**
 * @brief Set contiguous data into a network packet
 *
 * Note: net_pkt's cursor should be properly initialized and, if needed,
 *       properly positioned using net_pkt_skip.
 *       Cursor position will be updated after the operation.
 *
 * @param pkt    The network packet to where the data should be set.
 * @param access A pointer to a valid net_pkt_data_access describing the
 *        data to set.
 *
 * @return 0 on success, a negative errno otherwise.
 */
int net_pkt_set_data(struct net_pkt *pkt,
		     struct net_pkt_data_access *access);

/**
 * Acknowledge previously contiguous data taken from a network packet
 * Packet needs to be set to overwrite mode.
 */
static inline int net_pkt_acknowledge_data(struct net_pkt *pkt,
					   struct net_pkt_data_access *access)
{
	return net_pkt_skip(pkt, access->size);
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_NET_NET_PKT_H_ */
