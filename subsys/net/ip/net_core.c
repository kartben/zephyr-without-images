/** @file
 * @brief Network initialization
 *
 * Initialize the network IP stack. Create one thread for reading data
 * from IP stack and passing that data to applications (Rx thread).
 */

/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#if defined(CONFIG_NET_DEBUG_CORE)
#define SYS_LOG_DOMAIN "net/core"
#define NET_LOG_ENABLED 1
#endif

#include <init.h>
#include <kernel.h>
#include <toolchain.h>
#include <sections.h>
#include <string.h>
#include <errno.h>

#include <net/net_if.h>
#include <net/net_mgmt.h>
#include <net/arp.h>
#include <net/nbuf.h>
#include <net/net_core.h>
#include <net/dns_resolve.h>

#include "net_private.h"
#include "net_shell.h"

#include "icmpv6.h"
#include "ipv6.h"

#include "icmpv4.h"

#if defined(CONFIG_NET_DHCPV4)
#include "dhcpv4.h"
#endif

#include "route.h"
#include "rpl.h"

#include "connection.h"
#include "udp.h"
#include "tcp.h"

#include "net_stats.h"

/* Stack for the rx thread.
 */
#if !defined(CONFIG_NET_RX_STACK_SIZE)
#define CONFIG_NET_RX_STACK_SIZE 1024
#endif

NET_STACK_DEFINE(RX, rx_stack, CONFIG_NET_RX_STACK_SIZE,
		 CONFIG_NET_RX_STACK_SIZE + CONFIG_NET_RX_STACK_RPL);

static struct k_fifo rx_queue;
static k_tid_t rx_tid;
static K_SEM_DEFINE(startup_sync, 0, UINT_MAX);

#if defined(CONFIG_NET_IPV4)
static inline enum net_verdict process_icmpv4_pkt(struct net_buf *buf,
						  struct net_ipv4_hdr *ipv4)
{
	struct net_icmp_hdr *hdr = NET_ICMP_BUF(buf);

	NET_DBG("ICMPv4 packet received type %d code %d",
		hdr->type, hdr->code);

	return net_icmpv4_input(buf, hdr->type, hdr->code);
}
#endif /* CONFIG_NET_IPV4 */

#if defined(CONFIG_NET_IPV4)
static inline enum net_verdict process_ipv4_pkt(struct net_buf *buf)
{
	struct net_ipv4_hdr *hdr = NET_IPV4_BUF(buf);
	int real_len = net_buf_frags_len(buf);
	int pkt_len = (hdr->len[0] << 8) + hdr->len[1];
	enum net_verdict verdict = NET_DROP;

	if (real_len != pkt_len) {
		NET_DBG("IPv4 packet size %d buf len %d", pkt_len, real_len);
		goto drop;
	}

#if defined(CONFIG_NET_DEBUG_CORE)
	do {
		char out[sizeof("xxx.xxx.xxx.xxx")];
		snprintk(out, sizeof(out), "%s",
			 net_sprint_ipv4_addr(&hdr->dst));
		NET_DBG("IPv4 packet received from %s to %s",
			net_sprint_ipv4_addr(&hdr->src), out);
	} while (0);
#endif /* CONFIG_NET_DEBUG_CORE */

	net_nbuf_set_ip_hdr_len(buf, sizeof(struct net_ipv4_hdr));

	if (!net_is_my_ipv4_addr(&hdr->dst)) {
#if defined(CONFIG_NET_DHCPV4)
		if (hdr->proto == IPPROTO_UDP &&
		    net_ipv4_addr_cmp(&hdr->dst,
				      net_ipv4_broadcast_address())) {

			verdict = net_conn_input(IPPROTO_UDP, buf);
			if (verdict != NET_DROP) {
				return verdict;
			}
		}
#endif
		NET_DBG("IPv4 packet in buf %p not for me", buf);
		goto drop;
	}

	switch (hdr->proto) {
	case IPPROTO_ICMP:
		verdict = process_icmpv4_pkt(buf, hdr);
		break;
	case IPPROTO_UDP:
		verdict = net_conn_input(IPPROTO_UDP, buf);
		break;
	case IPPROTO_TCP:
		verdict = net_conn_input(IPPROTO_TCP, buf);
		break;
	}

	if (verdict != NET_DROP) {
		return verdict;
	}

drop:
	net_stats_update_ipv4_drop();
	return NET_DROP;
}
#endif /* CONFIG_NET_IPV4 */

static inline enum net_verdict process_data(struct net_buf *buf,
					    bool is_loopback)
{
	int ret;

	/* If there is no data, then drop the packet. Also if
	 * the buffer is wrong type, then also drop the packet.
	 * The first buffer needs to have user data part that
	 * contains user data. The rest of the fragments should
	 * be data fragments without user data.
	 */
	if (!buf->frags || !buf->pool->user_data_size) {
		NET_DBG("Corrupted buffer (frags %p, data size %u)",
			buf->frags, buf->pool->user_data_size);
		net_stats_update_processing_error();

		return NET_DROP;
	}

	if (!is_loopback) {
		ret = net_if_recv_data(net_nbuf_iface(buf), buf);
		if (ret != NET_CONTINUE) {
			if (ret == NET_DROP) {
				NET_DBG("Buffer %p discarded by L2", buf);
				net_stats_update_processing_error();
			}

			return ret;
		}
	}

	/* IP version and header length. */
	switch (NET_IPV6_BUF(buf)->vtc & 0xf0) {
#if defined(CONFIG_NET_IPV6)
	case 0x60:
		net_stats_update_ipv6_recv();
		net_nbuf_set_family(buf, PF_INET6);
		return net_ipv6_process_pkt(buf);
#endif
#if defined(CONFIG_NET_IPV4)
	case 0x40:
		net_stats_update_ipv4_recv();
		net_nbuf_set_family(buf, PF_INET);
		return process_ipv4_pkt(buf);
#endif
	}

	NET_DBG("Unknown IP family packet (0x%x)",
		NET_IPV6_BUF(buf)->vtc & 0xf0);
	net_stats_update_ip_errors_protoerr();
	net_stats_update_ip_errors_vhlerr();

	return NET_DROP;
}

static void processing_data(struct net_buf *buf, bool is_loopback)
{
	switch (process_data(buf, is_loopback)) {
	case NET_OK:
		NET_DBG("Consumed buf %p", buf);
		break;
	case NET_DROP:
	default:
		NET_DBG("Dropping buf %p", buf);
		net_nbuf_unref(buf);
		break;
	}
}

static void net_rx_thread(void)
{
	struct net_buf *buf;

	NET_DBG("Starting RX thread (stack %zu bytes)", sizeof(rx_stack));

	/* Starting TX side. The ordering is important here and the TX
	 * can only be started when RX side is ready to receive packets.
	 * We synchronize the startup of the device so that both RX and TX
	 * are only started fully when both are ready to receive or send
	 * data.
	 */
	net_if_init(&startup_sync);

	k_sem_take(&startup_sync, K_FOREVER);

	/* This will take the interface up and start everything. */
	net_if_post_init();

	while (1) {
#if defined(CONFIG_NET_STATISTICS) || defined(CONFIG_NET_DEBUG_CORE)
		size_t pkt_len;
#endif

		buf = net_buf_get(&rx_queue, K_FOREVER);

		net_analyze_stack("RX thread", rx_stack, sizeof(rx_stack));

#if defined(CONFIG_NET_STATISTICS) || defined(CONFIG_NET_DEBUG_CORE)
		pkt_len = net_buf_frags_len(buf);
#endif
		NET_DBG("Received buf %p len %zu", buf, pkt_len);

		net_stats_update_bytes_recv(pkt_len);

		processing_data(buf, false);

		net_print_statistics();
		net_nbuf_print();

		k_yield();
	}
}

static void init_rx_queue(void)
{
	k_fifo_init(&rx_queue);

	rx_tid = k_thread_spawn(rx_stack, sizeof(rx_stack),
				(k_thread_entry_t)net_rx_thread,
				NULL, NULL, NULL, K_PRIO_COOP(8),
				K_ESSENTIAL, K_NO_WAIT);
}

#if defined(CONFIG_NET_IP_ADDR_CHECK)
/* Check if the IPv{4|6} addresses are proper. As this can be expensive,
 * make this optional.
 */
static inline int check_ip_addr(struct net_buf *buf)
{
#if defined(CONFIG_NET_IPV6)
	if (net_nbuf_family(buf) == AF_INET6) {
		if (net_ipv6_addr_cmp(&NET_IPV6_BUF(buf)->dst,
				      net_ipv6_unspecified_address())) {
			NET_DBG("IPv6 dst address missing");
			return -EADDRNOTAVAIL;
		}

		/* If the destination address is our own, then route it
		 * back to us.
		 */
		if (net_is_ipv6_addr_loopback(&NET_IPV6_BUF(buf)->dst) ||
		    net_is_my_ipv6_addr(&NET_IPV6_BUF(buf)->dst)) {
			struct in6_addr addr;

			/* Swap the addresses so that in receiving side
			 * the packet is accepted.
			 */
			net_ipaddr_copy(&addr, &NET_IPV6_BUF(buf)->src);
			net_ipaddr_copy(&NET_IPV6_BUF(buf)->src,
					&NET_IPV6_BUF(buf)->dst);
			net_ipaddr_copy(&NET_IPV6_BUF(buf)->dst, &addr);

			return 1;
		}

		/* The source check must be done after the destination check
		 * as having src ::1 is perfectly ok if dst is ::1 too.
		 */
		if (net_is_ipv6_addr_loopback(&NET_IPV6_BUF(buf)->src)) {
			NET_DBG("IPv6 loopback src address");
			return -EADDRNOTAVAIL;
		}
	} else
#endif /* CONFIG_NET_IPV6 */

#if defined(CONFIG_NET_IPV4)
	if (net_nbuf_family(buf) == AF_INET) {
		if (net_ipv4_addr_cmp(&NET_IPV4_BUF(buf)->dst,
				      net_ipv4_unspecified_address())) {
			return -EADDRNOTAVAIL;
		}

		/* If the destination address is our own, then route it
		 * back to us.
		 */
		if (net_is_ipv4_addr_loopback(&NET_IPV4_BUF(buf)->dst) ||
		    net_is_my_ipv4_addr(&NET_IPV4_BUF(buf)->dst)) {
			struct in_addr addr;

			/* Swap the addresses so that in receiving side
			 * the packet is accepted.
			 */
			net_ipaddr_copy(&addr, &NET_IPV4_BUF(buf)->src);
			net_ipaddr_copy(&NET_IPV4_BUF(buf)->src,
					&NET_IPV4_BUF(buf)->dst);
			net_ipaddr_copy(&NET_IPV4_BUF(buf)->dst, &addr);

			return 1;
		}

		/* The source check must be done after the destination check
		 * as having src 127.0.0.0/8 is perfectly ok if dst is in
		 * localhost subnet too.
		 */
		if (net_is_ipv4_addr_loopback(&NET_IPV4_BUF(buf)->src)) {
			NET_DBG("IPv4 loopback src address");
			return -EADDRNOTAVAIL;
		}
	} else
#endif /* CONFIG_NET_IPV4 */

	{
		;
	}

	return 0;
}
#else
#define check_ip_addr(buf) 0
#endif

/* Called when data needs to be sent to network */
int net_send_data(struct net_buf *buf)
{
	int status;

	if (!buf || !buf->frags) {
		return -ENODATA;
	}

	if (!net_nbuf_iface(buf)) {
		return -EINVAL;
	}

#if defined(CONFIG_NET_STATISTICS)
	switch (net_nbuf_family(buf)) {
	case AF_INET:
		net_stats_update_ipv4_sent();
		break;
	case AF_INET6:
		net_stats_update_ipv6_sent();
		break;
	}
#endif

	status = check_ip_addr(buf);
	if (status < 0) {
		return status;
	} else if (status > 0) {
		/* Packet is destined back to us so send it directly
		 * to RX processing.
		 */
		processing_data(buf, true);
		return 0;
	}

	if (net_if_send_data(net_nbuf_iface(buf), buf) == NET_DROP) {
		return -EIO;
	}

	return 0;
}

/* Called by driver when an IP packet has been received */
int net_recv_data(struct net_if *iface, struct net_buf *buf)
{
	NET_ASSERT(buf && buf->frags);
	NET_ASSERT(iface);

	if (!buf->frags) {
		return -ENODATA;
	}

	if (!atomic_test_bit(iface->flags, NET_IF_UP)) {
		return -ENETDOWN;
	}

	NET_DBG("fifo %p iface %p buf %p len %zu", &rx_queue, iface, buf,
		net_buf_frags_len(buf));

	net_nbuf_set_iface(buf, iface);

	net_buf_put(&rx_queue, buf);

	return 0;
}

static inline void l3_init(void)
{
	net_icmpv4_init();
	net_icmpv6_init();
	net_ipv6_init();

#if defined(CONFIG_NET_UDP) || defined(CONFIG_NET_TCP)
	net_conn_init();
#endif
	net_udp_init();
	net_tcp_init();

	net_route_init();

	dns_init_resolver();

	NET_DBG("Network L3 init done");
}

static inline void l2_init(void)
{
	net_arp_init();

	NET_DBG("Network L2 init done");
}

static int net_init(struct device *unused)
{
	int status = 0;

	NET_DBG("Priority %d", CONFIG_NET_INIT_PRIO);

	net_shell_init();

	net_nbuf_init();

	net_context_init();

	l2_init();
	l3_init();

	net_mgmt_event_init();

	init_rx_queue();

#if CONFIG_NET_DHCPV4
	status = dhcpv4_init();
	if (status) {
		return status;
	}
#endif

	return status;
}

SYS_INIT(net_init, POST_KERNEL, CONFIG_NET_INIT_PRIO);
