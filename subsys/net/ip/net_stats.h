/*
 * Copyright (c) 2016 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __NET_STATS_H__
#define __NET_STATS_H__

#if defined(CONFIG_NET_STATISTICS)

#include <net/net_stats.h>

extern struct net_stats net_stats;

#define GET_STAT(s) net_stats.s

/* Core stats */

static inline void net_stats_update_processing_error(void)
{
	net_stats.processing_error++;
}

static inline void net_stats_update_ip_errors_protoerr(void)
{
	net_stats.ip_errors.protoerr++;
}

static inline void net_stats_update_ip_errors_vhlerr(void)
{
	net_stats.ip_errors.vhlerr++;
}
#else
#define net_stats_update_processing_error()
#define net_stats_update_ip_errors_protoerr()
#define net_stats_update_ip_errors_vhlerr()
#endif /* CONFIG_NET_STATISTICS */

#if defined(CONFIG_NET_STATISTICS_IPV6)
/* IPv6 stats */

static inline void net_stats_update_ipv6_sent(void)
{
	net_stats.ipv6.sent++;
}

static inline void net_stats_update_ipv6_recv(void)
{
	net_stats.ipv6.recv++;
}

static inline void net_stats_update_ipv6_drop(void)
{
	net_stats.ipv6.drop++;
}
#else
#define net_stats_update_ipv6_drop()
#define net_stats_update_ipv6_sent()
#define net_stats_update_ipv6_recv()
#endif /* CONFIG_NET_STATISTICS_IPV6 */

#if defined(CONFIG_NET_STATISTICS_IPV6_ND)
/* IPv6 Neighbor Discovery stats*/

static inline void net_stats_update_ipv6_nd_sent(void)
{
	net_stats.ipv6_nd.sent++;
}

static inline void net_stats_update_ipv6_nd_recv(void)
{
	net_stats.ipv6_nd.recv++;
}

static inline void net_stats_update_ipv6_nd_drop(void)
{
	net_stats.ipv6_nd.drop++;
}
#else
#define net_stats_update_ipv6_nd_sent()
#define net_stats_update_ipv6_nd_recv()
#define net_stats_update_ipv6_nd_drop()
#endif /* CONFIG_NET_STATISTICS_IPV6_ND */

#if defined(CONFIG_NET_STATISTICS_IPV4)
/* IPv4 stats */

static inline void net_stats_update_ipv4_drop(void)
{
	net_stats.ipv4.drop++;
}

static inline void net_stats_update_ipv4_sent(void)
{
	net_stats.ipv4.sent++;
}

static inline void net_stats_update_ipv4_recv(void)
{
	net_stats.ipv4.recv++;
}
#else
#define net_stats_update_ipv4_drop()
#define net_stats_update_ipv4_sent()
#define net_stats_update_ipv4_recv()
#endif /* CONFIG_NET_STATISTICS_IPV4 */

#if defined(CONFIG_NET_STATISTICS_ICMP)
/* Common ICMPv4/ICMPv6 stats */
static inline void net_stats_update_icmp_sent(void)
{
	net_stats.icmp.sent++;
}

static inline void net_stats_update_icmp_recv(void)
{
	net_stats.icmp.recv++;
}

static inline void net_stats_update_icmp_drop(void)
{
	net_stats.icmp.drop++;
}
#else
#define net_stats_update_icmp_sent()
#define net_stats_update_icmp_recv()
#define net_stats_update_icmp_drop()
#endif /* CONFIG_NET_STATISTICS_ICMP */

#if defined(CONFIG_NET_STATISTICS_UDP)
/* UDP stats */
static inline void net_stats_update_udp_sent(void)
{
	net_stats.udp.sent++;
}

static inline void net_stats_update_udp_recv(void)
{
	net_stats.udp.recv++;
}

static inline void net_stats_update_udp_drop(void)
{
	net_stats.udp.drop++;
}
#else
#define net_stats_update_udp_sent()
#define net_stats_update_udp_recv()
#define net_stats_update_udp_drop()
#endif /* CONFIG_NET_STATISTICS_UDP */

#if defined(CONFIG_NET_STATISTICS_RPL)
/* RPL stats */
static inline void net_stats_update_rpl_resets(void)
{
	net_stats.rpl.resets++;
}

static inline void net_stats_update_rpl_mem_overflows(void)
{
	net_stats.rpl.mem_overflows++;
}

static inline void net_stats_update_rpl_parent_switch(void)
{
	net_stats.rpl.parent_switch++;
}

static inline void net_stats_update_rpl_local_repairs(void)
{
	net_stats.rpl.local_repairs++;
}

static inline void net_stats_update_rpl_global_repairs(void)
{
	net_stats.rpl.global_repairs++;
}

static inline void net_stats_update_rpl_root_repairs(void)
{
	net_stats.rpl.root_repairs++;
}

static inline void net_stats_update_rpl_malformed_msgs(void)
{
	net_stats.rpl.malformed_msgs++;
}

static inline void net_stats_update_rpl_forward_errors(void)
{
	net_stats.rpl.forward_errors++;
}

static inline void net_stats_update_rpl_loop_errors(void)
{
	net_stats.rpl.loop_errors++;
}

static inline void net_stats_update_rpl_loop_warnings(void)
{
	net_stats.rpl.loop_warnings++;
}

static inline void net_stats_update_rpl_dis_sent(void)
{
	net_stats.rpl.dis.sent++;
}

static inline void net_stats_update_rpl_dio_sent(void)
{
	net_stats.rpl.dio.sent++;
}

static inline void net_stats_update_rpl_dao_sent(void)
{
	net_stats.rpl.dao.sent++;
}

static inline void net_stats_update_rpl_dao_forwarded(void)
{
	net_stats.rpl.dao.forwarded++;
}

static inline void net_stats_update_rpl_dao_ack_sent(void)
{
	net_stats.rpl.dao_ack.sent++;
}

static inline void net_stats_update_rpl_dao_ack_recv(void)
{
	net_stats.rpl.dao_ack.recv++;
}
#else
#define net_stats_update_rpl_resets()
#define net_stats_update_rpl_mem_overflows()
#define net_stats_update_rpl_parent_switch()
#define net_stats_update_rpl_local_repairs()
#define net_stats_update_rpl_global_repairs()
#define net_stats_update_rpl_root_repairs()
#define net_stats_update_rpl_malformed_msgs()
#define net_stats_update_rpl_forward_errors()
#define net_stats_update_rpl_loop_errors()
#define net_stats_update_rpl_loop_warnings()
#define net_stats_update_rpl_dis_sent()
#define net_stats_update_rpl_dio_sent()
#define net_stats_update_rpl_dao_sent()
#define net_stats_update_rpl_dao_forwarded()
#define net_stats_update_rpl_dao_ack_sent()
#define net_stats_update_rpl_dao_ack_recv()
#endif /* CONFIG_NET_STATISTICS_RPL */

#if defined(CONFIG_NET_STATISTICS_PERIODIC_OUTPUT)
/* A simple periodic statistic printer, used only in net core */
void net_print_statistics(void);
#else
#define net_print_statistics()
#endif

#endif /* __NET_STATS_H__ */
