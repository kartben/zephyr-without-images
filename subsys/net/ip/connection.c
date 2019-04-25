/** @file
 * @brief Generic connection related functions
 */

/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <logging/log.h>
LOG_MODULE_REGISTER(net_conn, CONFIG_NET_CONN_LOG_LEVEL);

#include <errno.h>
#include <misc/util.h>

#include <net/net_core.h>
#include <net/net_pkt.h>
#include <net/udp.h>
#include <net/ethernet.h>
#include <net/socket_can.h>

#include "net_private.h"
#include "icmpv6.h"
#include "icmpv4.h"
#include "udp_internal.h"
#include "tcp_internal.h"
#include "connection.h"
#include "net_stats.h"

/** Is this connection used or not */
#define NET_CONN_IN_USE BIT(0)

/** Remote address set */
#define NET_CONN_REMOTE_ADDR_SET BIT(1)

/** Local address set */
#define NET_CONN_LOCAL_ADDR_SET BIT(2)

/** Rank bits */
#define NET_RANK_LOCAL_PORT         BIT(0)
#define NET_RANK_REMOTE_PORT        BIT(1)
#define NET_RANK_LOCAL_UNSPEC_ADDR  BIT(2)
#define NET_RANK_REMOTE_UNSPEC_ADDR BIT(3)
#define NET_RANK_LOCAL_SPEC_ADDR    BIT(4)
#define NET_RANK_REMOTE_SPEC_ADDR   BIT(5)

static struct net_conn conns[CONFIG_NET_MAX_CONN];

int net_conn_unregister(struct net_conn_handle *handle)
{
	struct net_conn *conn = (struct net_conn *)handle;

	if (conn < &conns[0] || conn > &conns[CONFIG_NET_MAX_CONN]) {
		return -EINVAL;
	}

	if (!(conn->flags & NET_CONN_IN_USE)) {
		return -ENOENT;
	}

	NET_DBG("[%zu] connection handler %p removed",
		conn - conns, conn);

	(void)memset(conn, 0, sizeof(*conn));

	return 0;
}

int net_conn_change_callback(struct net_conn_handle *handle,
			     net_conn_cb_t cb, void *user_data)
{
	struct net_conn *conn = (struct net_conn *)handle;

	if (conn < &conns[0] || conn > &conns[CONFIG_NET_MAX_CONN]) {
		return -EINVAL;
	}

	if (!(conn->flags & NET_CONN_IN_USE)) {
		return -ENOENT;
	}

	NET_DBG("[%zu] connection handler %p changed callback",
		conn - conns, conn);

	conn->cb = cb;
	conn->user_data = user_data;

	return 0;
}

static inline
void prepare_register_debug_print(char *dst, int dst_len,
				  char *src, int src_len,
				  const struct sockaddr *remote_addr,
				  const struct sockaddr *local_addr)
{
	if (remote_addr && remote_addr->sa_family == AF_INET6) {
		if (IS_ENABLED(CONFIG_NET_IPV6)) {
			snprintk(dst, dst_len, "%s",
				 log_strdup(net_sprint_ipv6_addr(
					  &net_sin6(remote_addr)->sin6_addr)));
		} else {
			snprintk(dst, dst_len, "%s", "?");
		}

	} else if (remote_addr && remote_addr->sa_family == AF_INET) {
		if (IS_ENABLED(CONFIG_NET_IPV4)) {
			snprintk(dst, dst_len, "%s",
				 log_strdup(net_sprint_ipv4_addr(
					  &net_sin(remote_addr)->sin_addr)));
		} else {
			snprintk(dst, dst_len, "%s", "?");
		}

	} else {
		snprintk(dst, dst_len, "%s", "-");
	}

	if (local_addr && local_addr->sa_family == AF_INET6) {
		if (IS_ENABLED(CONFIG_NET_IPV6)) {
			snprintk(src, src_len, "%s",
				 log_strdup(net_sprint_ipv6_addr(
					  &net_sin6(local_addr)->sin6_addr)));
		} else {
			snprintk(src, src_len, "%s", "?");
		}

	} else if (local_addr && local_addr->sa_family == AF_INET) {
		if (IS_ENABLED(CONFIG_NET_IPV4)) {
			snprintk(src, src_len, "%s",
				 log_strdup(net_sprint_ipv4_addr(
					  &net_sin(local_addr)->sin_addr)));
		} else {
			snprintk(src, src_len, "%s", "?");
		}

	} else {
		snprintk(src, src_len, "%s", "-");
	}
}

/* Check if we already have identical connection handler installed. */
static int find_conn_handler(u16_t proto, u8_t family,
			     const struct sockaddr *remote_addr,
			     const struct sockaddr *local_addr,
			     u16_t remote_port,
			     u16_t local_port)
{
	int i;

	for (i = 0; i < CONFIG_NET_MAX_CONN; i++) {
		if (!(conns[i].flags & NET_CONN_IN_USE)) {
			continue;
		}

		if (conns[i].proto != proto) {
			continue;
		}

		if (conns[i].family != family) {
			continue;
		}

		if (remote_addr) {
			if (!(conns[i].flags & NET_CONN_REMOTE_ADDR_SET)) {
				continue;
			}

#if defined(CONFIG_NET_IPV6)
			if (remote_addr->sa_family == AF_INET6 &&
			    remote_addr->sa_family ==
			    conns[i].remote_addr.sa_family) {
				if (!net_ipv6_addr_cmp(
					    &net_sin6(remote_addr)->sin6_addr,
					    &net_sin6(&conns[i].remote_addr)->
								sin6_addr)) {
					continue;
				}
			} else
#endif
#if defined(CONFIG_NET_IPV4)
			if (remote_addr->sa_family == AF_INET &&
			    remote_addr->sa_family ==
			    conns[i].remote_addr.sa_family) {
				if (!net_ipv4_addr_cmp(
					    &net_sin(remote_addr)->sin_addr,
					    &net_sin(&conns[i].remote_addr)->
								sin_addr)) {
					continue;
				}
			} else
#endif
			{
				continue;
			}
		} else {
			if (conns[i].flags & NET_CONN_REMOTE_ADDR_SET) {
				continue;
			}
		}

		if (local_addr) {
			if (!(conns[i].flags & NET_CONN_LOCAL_ADDR_SET)) {
				continue;
			}

#if defined(CONFIG_NET_IPV6)
			if (local_addr->sa_family == AF_INET6 &&
			    local_addr->sa_family ==
			    conns[i].local_addr.sa_family) {
				if (!net_ipv6_addr_cmp(
					    &net_sin6(local_addr)->sin6_addr,
					    &net_sin6(&conns[i].local_addr)->
								sin6_addr)) {
					continue;
				}
			} else
#endif
#if defined(CONFIG_NET_IPV4)
			if (local_addr->sa_family == AF_INET &&
			    local_addr->sa_family ==
			    conns[i].local_addr.sa_family) {
				if (!net_ipv4_addr_cmp(
					    &net_sin(local_addr)->sin_addr,
					    &net_sin(&conns[i].local_addr)->
								sin_addr)) {
					continue;
				}
			} else
#endif
			{
				continue;
			}
		} else {
			if (conns[i].flags & NET_CONN_LOCAL_ADDR_SET) {
				continue;
			}
		}

		if (net_sin(&conns[i].remote_addr)->sin_port !=
		    htons(remote_port)) {
			continue;
		}

		if (net_sin(&conns[i].local_addr)->sin_port !=
		    htons(local_port)) {
			continue;
		}

		return i;
	}

	return -ENOENT;
}

int net_conn_register(u16_t proto, u8_t family,
		      const struct sockaddr *remote_addr,
		      const struct sockaddr *local_addr,
		      u16_t remote_port,
		      u16_t local_port,
		      net_conn_cb_t cb,
		      void *user_data,
		      struct net_conn_handle **handle)
{
	int i;
	u8_t rank = 0U;

	i = find_conn_handler(proto, family, remote_addr, local_addr,
			      remote_port, local_port);
	if (i != -ENOENT) {
		NET_ERR("Identical connection handler %p already found.",
			&conns[i]);
		return -EALREADY;
	}

	for (i = 0; i < CONFIG_NET_MAX_CONN; i++) {
		if (conns[i].flags & NET_CONN_IN_USE) {
			continue;
		}

		if (remote_addr) {
#if defined(CONFIG_NET_IPV6)
			if (remote_addr->sa_family == AF_INET6) {
				memcpy(&conns[i].remote_addr, remote_addr,
				       sizeof(struct sockaddr_in6));

				if (net_ipv6_is_addr_unspecified(
					    &net_sin6(remote_addr)->
							sin6_addr)) {
					rank |= NET_RANK_REMOTE_UNSPEC_ADDR;
				} else {
					rank |= NET_RANK_REMOTE_SPEC_ADDR;
				}
			} else
#endif

#if defined(CONFIG_NET_IPV4)
			if (remote_addr->sa_family == AF_INET) {
				memcpy(&conns[i].remote_addr, remote_addr,
				       sizeof(struct sockaddr_in));

				if (!net_sin(remote_addr)->
							sin_addr.s_addr) {
					rank |= NET_RANK_REMOTE_UNSPEC_ADDR;
				} else {
					rank |= NET_RANK_REMOTE_SPEC_ADDR;
				}
			} else
#endif
			{
				NET_ERR("Remote address family not set");
				return -EINVAL;
			}

			conns[i].flags |= NET_CONN_REMOTE_ADDR_SET;
		}

		if (local_addr) {
#if defined(CONFIG_NET_IPV6)
			if (local_addr->sa_family == AF_INET6) {
				memcpy(&conns[i].local_addr, local_addr,
				       sizeof(struct sockaddr_in6));

				if (net_ipv6_is_addr_unspecified(
					    &net_sin6(local_addr)->
							sin6_addr)) {
					rank |= NET_RANK_LOCAL_UNSPEC_ADDR;
				} else {
					rank |= NET_RANK_LOCAL_SPEC_ADDR;
				}
			} else
#endif

#if defined(CONFIG_NET_IPV4)
			if (local_addr->sa_family == AF_INET) {
				memcpy(&conns[i].local_addr, local_addr,
				       sizeof(struct sockaddr_in));

				if (!net_sin(local_addr)->sin_addr.s_addr) {
					rank |= NET_RANK_LOCAL_UNSPEC_ADDR;
				} else {
					rank |= NET_RANK_LOCAL_SPEC_ADDR;
				}
			} else
#endif
			{
				NET_ERR("Local address family not set");
				return -EINVAL;
			}

			conns[i].flags |= NET_CONN_LOCAL_ADDR_SET;
		}

		if (remote_addr && local_addr) {
			if (remote_addr->sa_family != local_addr->sa_family) {
				NET_ERR("Address families different");
				return -EINVAL;
			}
		}

		if (remote_port) {
			rank |= NET_RANK_REMOTE_PORT;
			net_sin(&conns[i].remote_addr)->sin_port =
				htons(remote_port);
		}

		if (local_port) {
			rank |= NET_RANK_LOCAL_PORT;
			net_sin(&conns[i].local_addr)->sin_port =
				htons(local_port);
		}

		conns[i].flags |= NET_CONN_IN_USE;
		conns[i].cb = cb;
		conns[i].user_data = user_data;
		conns[i].rank = rank;
		conns[i].proto = proto;
		conns[i].family = family;

		if (CONFIG_NET_CONN_LOG_LEVEL >= LOG_LEVEL_DBG) {
			char dst[NET_IPV6_ADDR_LEN];
			char src[NET_IPV6_ADDR_LEN];

			prepare_register_debug_print(dst, sizeof(dst),
						     src, sizeof(src),
						     remote_addr,
						     local_addr);

			NET_DBG("[%d/%d/%u/%u/0x%02x] remote %p/%s/%u ", i,
				local_addr ? local_addr->sa_family : AF_UNSPEC,
				proto, family, rank, remote_addr,
				log_strdup(dst), remote_port);
			NET_DBG("  local %p/%s/%u cb %p ud %p",
				local_addr, log_strdup(src), local_port,
				cb, user_data);
		}

		if (handle) {
			*handle = (struct net_conn_handle *)&conns[i];
		}

		return 0;
	}

	return -ENOENT;
}

static bool check_addr(struct net_pkt *pkt,
		       union net_ip_header *ip_hdr,
		       struct sockaddr *addr,
		       bool is_remote)
{
	if (addr->sa_family != net_pkt_family(pkt)) {
		return false;
	}

#if defined(CONFIG_NET_IPV6)
	if (net_pkt_family(pkt) == AF_INET6 && addr->sa_family == AF_INET6) {
		struct in6_addr *addr6;

		if (is_remote) {
			addr6 = &ip_hdr->ipv6->src;
		} else {
			addr6 = &ip_hdr->ipv6->dst;
		}

		if (!net_ipv6_is_addr_unspecified(
			    &net_sin6(addr)->sin6_addr)) {
			if (!net_ipv6_addr_cmp(&net_sin6(addr)->sin6_addr,
					       addr6)) {
				return false;
			}
		}

		return true;
	}
#endif /* CONFIG_NET_IPV6 */

#if defined(CONFIG_NET_IPV4)
	if (net_pkt_family(pkt) == AF_INET && addr->sa_family == AF_INET) {
		struct in_addr *addr4;

		if (is_remote) {
			addr4 = &ip_hdr->ipv4->src;
		} else {
			addr4 = &ip_hdr->ipv4->dst;
		}

		if (net_sin(addr)->sin_addr.s_addr) {
			if (!net_ipv4_addr_cmp(&net_sin(addr)->sin_addr,
					       addr4)) {
				return false;
			}
		}
	}
#endif /* CONFIG_NET_IPV4 */

	return true;
}

static inline void send_icmp_error(struct net_pkt *pkt)
{
	if (net_pkt_family(pkt) == AF_INET6) {
#if defined(CONFIG_NET_IPV6)
		net_icmpv6_send_error(pkt, NET_ICMPV6_DST_UNREACH,
				      NET_ICMPV6_DST_UNREACH_NO_PORT, 0);
#endif /* CONFIG_NET_IPV6 */

	} else {

#if defined(CONFIG_NET_IPV4)
		net_icmpv4_send_error(pkt, NET_ICMPV4_DST_UNREACH,
				      NET_ICMPV4_DST_UNREACH_NO_PORT);
#endif /* CONFIG_NET_IPV4 */
	}
}

static bool is_valid_packet(struct net_pkt *pkt,
			    union net_ip_header *ip_hdr,
			    u16_t src_port,
			    u16_t dst_port)
{
	bool my_src_addr = false;

	/* For AF_PACKET family, we are not not parsing headers. */
	if (IS_ENABLED(CONFIG_NET_SOCKETS_PACKET) &&
	    net_pkt_family(pkt) == AF_PACKET) {
		return true;
	}

	if (IS_ENABLED(CONFIG_NET_SOCKETS_CAN) &&
	    net_pkt_family(pkt) == AF_CAN) {
		return true;
	}

	if (IS_ENABLED(CONFIG_NET_IPV4) && net_pkt_family(pkt) == AF_INET) {
		if (net_ipv4_addr_cmp(&ip_hdr->ipv4->src,
				      &ip_hdr->ipv4->dst) ||
		    net_ipv4_is_my_addr(&ip_hdr->ipv4->src)) {
			my_src_addr = true;
		}
	} else if (IS_ENABLED(CONFIG_NET_IPV6) &&
		   net_pkt_family(pkt) == AF_INET6) {
		if (net_ipv6_addr_cmp(&ip_hdr->ipv6->src,
				      &ip_hdr->ipv6->dst) ||
		    net_ipv6_is_my_addr(&ip_hdr->ipv6->src)) {
			my_src_addr = true;
		}
	}

	return !(my_src_addr && (src_port == dst_port));
}

enum net_verdict net_conn_input(struct net_pkt *pkt,
				union net_ip_header *ip_hdr,
				u8_t proto,
				union net_proto_header *proto_hdr)
{
	struct net_if *pkt_iface = net_pkt_iface(pkt);
	int i, best_match = -1;
	s16_t best_rank = -1;
	u16_t src_port;
	u16_t dst_port;

	if (IS_ENABLED(CONFIG_NET_UDP) && proto == IPPROTO_UDP) {
		src_port = proto_hdr->udp->src_port;
		dst_port = proto_hdr->udp->dst_port;
	} else if (IS_ENABLED(CONFIG_NET_TCP) && proto == IPPROTO_TCP) {
		src_port = proto_hdr->tcp->src_port;
		dst_port = proto_hdr->tcp->dst_port;
	} else if (IS_ENABLED(CONFIG_NET_SOCKETS_PACKET)) {
		if (net_pkt_family(pkt) != AF_PACKET || proto != ETH_P_ALL) {
			return NET_DROP;
		}

		src_port = dst_port = 0U;
	} else if (IS_ENABLED(CONFIG_NET_SOCKETS_CAN) &&
		   net_pkt_family(pkt) == AF_CAN) {
		if (proto != CAN_RAW) {
			return NET_DROP;
		}

		src_port = dst_port = 0U;
	} else {
		NET_DBG("No suitable protocol handler configured");
		return NET_DROP;
	}

	if (!is_valid_packet(pkt, ip_hdr, src_port, dst_port)) {
		NET_DBG("Dropping invalid packet");
		return NET_DROP;
	}

	/* TODO: Make core part of networing subsystem less dependent on
	 * UDP, TCP, IPv4 or IPv6. So that we can add new features with
	 * less cross-module changes.
	 */
	NET_DBG("Check %s listener for pkt %p src port %u dst port %u"
		" family %d", net_proto2str(net_pkt_family(pkt), proto), pkt,
		ntohs(src_port), ntohs(dst_port), net_pkt_family(pkt));

	for (i = 0; i < CONFIG_NET_MAX_CONN; i++) {
		if (!(conns[i].flags & NET_CONN_IN_USE)) {
			continue;
		}

		if (conns[i].proto != proto) {
			continue;
		}

		if (conns[i].family != AF_UNSPEC &&
		    conns[i].family != net_pkt_family(pkt)) {
			continue;
		}

		if (IS_ENABLED(CONFIG_NET_UDP) ||
		    IS_ENABLED(CONFIG_NET_TCP)) {
			if (net_sin(&conns[i].remote_addr)->sin_port) {
				if (net_sin(&conns[i].remote_addr)->sin_port !=
				    src_port) {
					continue;
				}
			}

			if (net_sin(&conns[i].local_addr)->sin_port) {
				if (net_sin(&conns[i].local_addr)->sin_port !=
				    dst_port) {
					continue;
				}
			}

			if (conns[i].flags & NET_CONN_REMOTE_ADDR_SET) {
				if (!check_addr(pkt, ip_hdr,
						&conns[i].remote_addr,
						true)) {
					continue;
				}
			}

			if (conns[i].flags & NET_CONN_LOCAL_ADDR_SET) {
				if (!check_addr(pkt, ip_hdr,
						&conns[i].local_addr,
						false)) {
					continue;
				}
			}

			/* If we have an existing best_match, and that one
			 * specifies a remote port, then we've matched to a
			 * LISTENING connection that should not override.
			 */
			if (best_match >= 0 &&
			    net_sin(&conns[best_match].remote_addr)->sin_port) {
				continue;
			}

			if (best_rank < conns[i].rank) {
				best_rank = conns[i].rank;
				best_match = i;
			}
		} else if (IS_ENABLED(CONFIG_NET_SOCKETS_PACKET)) {
			best_rank = 0;
			best_match = i;
		} else if (IS_ENABLED(CONFIG_NET_SOCKETS_CAN)) {
			best_rank = 0;
			best_match = i;
		}
	}

	if (best_match >= 0) {
		NET_DBG("[%d] match found cb %p ud %p rank 0x%02x",
			best_match,
			conns[best_match].cb,
			conns[best_match].user_data,
			conns[best_match].rank);

		if (conns[best_match].cb(&conns[best_match], pkt, ip_hdr,
			proto_hdr, conns[best_match].user_data) == NET_DROP) {
			goto drop;
		}

		net_stats_update_per_proto_recv(pkt_iface, proto);

		return NET_OK;
	}

	NET_DBG("No match found.");

	/* If the destination address is multicast address,
	 * we will not send an ICMP error as that makes no sense.
	 */
	if (IS_ENABLED(CONFIG_NET_IPV6) &&
	    net_pkt_family(pkt) == AF_INET6 &&
	    net_ipv6_is_addr_mcast(&ip_hdr->ipv6->dst)) {
		;
	} else if (IS_ENABLED(CONFIG_NET_IPV4) &&
		   net_pkt_family(pkt) == AF_INET &&
		   net_ipv4_is_addr_mcast(&ip_hdr->ipv4->dst)) {
		;
	} else if (IS_ENABLED(CONFIG_NET_SOCKETS_PACKET) &&
		    net_pkt_family(pkt) == AF_PACKET) {
		;
	} else {
		send_icmp_error(pkt);

		if (IS_ENABLED(CONFIG_NET_TCP) && proto == IPPROTO_TCP) {
			net_stats_update_tcp_seg_connrst(net_pkt_iface(pkt));
		}
	}

drop:
	net_stats_update_per_proto_drop(pkt_iface, proto);

	return NET_DROP;
}

void net_conn_foreach(net_conn_foreach_cb_t cb, void *user_data)
{
	int i;

	for (i = 0; i < CONFIG_NET_MAX_CONN; i++) {
		if (!(conns[i].flags & NET_CONN_IN_USE)) {
			continue;
		}

		cb(&conns[i], user_data);
	}
}

void net_conn_init(void)
{
}
