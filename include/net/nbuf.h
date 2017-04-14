/** @file
 * @brief Network buffer API
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

#ifndef __NBUF_H
#define __NBUF_H

#include <stdint.h>
#include <stdbool.h>

#include <net/buf.h>

#include <net/net_core.h>
#include <net/net_linkaddr.h>
#include <net/net_ip.h>
#include <net/net_if.h>
#include <net/net_context.h>

#ifdef __cplusplus
extern "C" {
#endif

struct net_context;

enum net_dir {
	/* TX must be first and must have value 0 so that it is selected
	 * by default.
	 */
	NET_TX = 0,
	NET_RX = 1,
};

struct net_nbuf {
	/** Network connection context */
	struct net_context *context;

	/** Network context token that user can set. This is passed
	 * to user callback when data has been sent.
	 */
	void *token;

	/** Network interface */
	struct net_if *iface;

	/** @cond ignore */
	uint8_t *appdata;	/* application data starts here */
	uint8_t *next_hdr;	/* where is the next header */

	/* Filled by layer 2 when network packet is received. */
	struct net_linkaddr lladdr_src;
	struct net_linkaddr lladdr_dst;

#if defined(CONFIG_NET_IPV6_FRAGMENT)
	/* Fragment id */
	uint32_t ipv6_fragment_id;

	/* Where is the start of the fragment header */
	uint8_t *ipv6_frag_hdr_start;

	/* What is the fragment offset of this IPv6 packet */
	uint16_t ipv6_fragment_offset;
#endif

	uint16_t appdatalen;

#if defined(CONFIG_NET_IPV6)
	/* Where is the start of the last header before payload data
	 * in IPv6 packet. This is offset value from start of the IPv6
	 * packet. Note that this value should be updated by who ever
	 * adds IPv6 extension headers to the network packet.
	 */
	uint16_t ipv6_prev_hdr_start;

	/* IPv6 hop limit for this network packet. */
	uint8_t ipv6_hop_limit;
#endif

	uint8_t ll_reserve;	/* link layer header length */
	uint8_t family;		/* IPv4 vs IPv6 */
	uint8_t ip_hdr_len;	/* pre-filled in order to avoid func call */
	uint8_t ext_len;	/* length of extension headers */
	uint8_t ext_bitmap;
	uint8_t net_dir;	/* is this RX or TX buf */

#if defined(CONFIG_NET_IPV6)
	uint8_t ext_opt_len; /* IPv6 ND option length */
#endif

#if defined(CONFIG_NET_TCP)
	bool buf_sent; /* Is this net_buf sent or not */
#endif

#if defined(CONFIG_NET_ROUTE)
	bool forwarding; /* Are we forwarding this buf */
#endif

#if defined(CONFIG_NET_L2_IEEE802154)
	uint8_t ieee802154_rssi;
#endif
	/* @endcond */
};

/** @cond ignore */


/* The interface real ll address */
static inline struct net_linkaddr *net_nbuf_ll_if(struct net_buf *buf)
{
	return net_if_get_link_addr(
		((struct net_nbuf *)net_buf_user_data(buf))->iface);
}

static inline struct net_context *net_nbuf_context(struct net_buf *buf)
{
	return ((struct net_nbuf *)net_buf_user_data(buf))->context;
}

static inline void net_nbuf_set_context(struct net_buf *buf,
					struct net_context *ctx)
{
	((struct net_nbuf *)net_buf_user_data(buf))->context = ctx;
}

static inline void *net_nbuf_token(struct net_buf *buf)
{
	return ((struct net_nbuf *)net_buf_user_data(buf))->token;
}

static inline void net_nbuf_set_token(struct net_buf *buf, void *token)
{
	((struct net_nbuf *)net_buf_user_data(buf))->token = token;
}

static inline struct net_if *net_nbuf_iface(struct net_buf *buf)
{
	return ((struct net_nbuf *)net_buf_user_data(buf))->iface;
}

static inline void net_nbuf_set_iface(struct net_buf *buf, struct net_if *iface)
{
	((struct net_nbuf *)net_buf_user_data(buf))->iface = iface;

	/* If the network interface is set in nbuf, then also set the type of
	 * the network address that is stored in nbuf. This is done here so
	 * that the address type is properly set and is not forgotten.
	 */
	((struct net_nbuf *)net_buf_user_data(buf))->lladdr_src.type =
		iface->link_addr.type;
	((struct net_nbuf *)net_buf_user_data(buf))->lladdr_dst.type =
		iface->link_addr.type;
}

static inline uint8_t net_nbuf_family(struct net_buf *buf)
{
	return ((struct net_nbuf *)net_buf_user_data(buf))->family;
}

static inline void net_nbuf_set_family(struct net_buf *buf, uint8_t family)
{
	((struct net_nbuf *)net_buf_user_data(buf))->family = family;
}

static inline uint8_t net_nbuf_ip_hdr_len(struct net_buf *buf)
{
	return ((struct net_nbuf *) net_buf_user_data(buf))->ip_hdr_len;
}

static inline void net_nbuf_set_ip_hdr_len(struct net_buf *buf, uint8_t len)
{
	((struct net_nbuf *) net_buf_user_data(buf))->ip_hdr_len = len;
}

static inline uint8_t net_nbuf_ext_len(struct net_buf *buf)
{
	return ((struct net_nbuf *)net_buf_user_data(buf))->ext_len;
}

static inline void net_nbuf_set_ext_len(struct net_buf *buf, uint8_t len)
{
	((struct net_nbuf *)net_buf_user_data(buf))->ext_len = len;
}

static inline uint8_t net_nbuf_ext_bitmap(struct net_buf *buf)
{
	return ((struct net_nbuf *)net_buf_user_data(buf))->ext_bitmap;
}

static inline void net_nbuf_set_ext_bitmap(struct net_buf *buf, uint8_t bm)
{
	((struct net_nbuf *)net_buf_user_data(buf))->ext_bitmap = bm;
}

static inline void net_nbuf_add_ext_bitmap(struct net_buf *buf, uint8_t bm)
{
	((struct net_nbuf *)net_buf_user_data(buf))->ext_bitmap |= bm;
}

static inline uint8_t net_nbuf_dir(struct net_buf *buf)
{
	return ((struct net_nbuf *)net_buf_user_data(buf))->net_dir;
}

static inline void net_nbuf_set_dir(struct net_buf *buf, enum net_dir dir)
{
	((struct net_nbuf *)net_buf_user_data(buf))->net_dir = dir;
}

static inline uint8_t *net_nbuf_next_hdr(struct net_buf *buf)
{
	return ((struct net_nbuf *)net_buf_user_data(buf))->next_hdr;
}

static inline void net_nbuf_set_next_hdr(struct net_buf *buf, uint8_t *hdr)
{
	((struct net_nbuf *)net_buf_user_data(buf))->next_hdr = hdr;
}

#if defined(CONFIG_NET_IPV6)
static inline uint8_t net_nbuf_ext_opt_len(struct net_buf *buf)
{
	return ((struct net_nbuf *)net_buf_user_data(buf))->ext_opt_len;
}

static inline void net_nbuf_set_ext_opt_len(struct net_buf *buf, uint8_t len)
{
	((struct net_nbuf *)net_buf_user_data(buf))->ext_opt_len = len;
}
#endif

#if defined(CONFIG_NET_TCP)
static inline uint8_t net_nbuf_buf_sent(struct net_buf *buf)
{
	return ((struct net_nbuf *)net_buf_user_data(buf))->buf_sent;
}

static inline void net_nbuf_set_buf_sent(struct net_buf *buf, bool sent)
{
	((struct net_nbuf *)net_buf_user_data(buf))->buf_sent = sent;
}
#endif

#if defined(CONFIG_NET_ROUTE)
static inline bool net_nbuf_forwarding(struct net_buf *buf)
{
	return ((struct net_nbuf *)net_buf_user_data(buf))->forwarding;
}

static inline void net_nbuf_set_forwarding(struct net_buf *buf, bool forward)
{
	((struct net_nbuf *)net_buf_user_data(buf))->forwarding = forward;
}
#else
static inline bool net_nbuf_forwarding(struct net_buf *buf)
{
	return false;
}
#endif

static inline uint16_t net_nbuf_get_len(struct net_buf *buf)
{
	return buf->len;
}

static inline void net_nbuf_set_len(struct net_buf *buf, uint16_t len)
{
	buf->len = len;
}

static inline uint8_t *net_nbuf_ip_data(struct net_buf *buf)
{
	return buf->frags->data;
}

static inline uint8_t *net_nbuf_udp_data(struct net_buf *buf)
{
	return &buf->frags->data[net_nbuf_ip_hdr_len(buf) +
				 net_nbuf_ext_len(buf)];
}

static inline uint8_t *net_nbuf_tcp_data(struct net_buf *buf)
{
	return &buf->frags->data[net_nbuf_ip_hdr_len(buf) +
				 net_nbuf_ext_len(buf)];
}

static inline uint8_t *net_nbuf_icmp_data(struct net_buf *buf)
{
	return &buf->frags->data[net_nbuf_ip_hdr_len(buf) +
				 net_nbuf_ext_len(buf)];
}

static inline uint8_t *net_nbuf_appdata(struct net_buf *buf)
{
	return ((struct net_nbuf *)net_buf_user_data(buf))->appdata;
}

static inline void net_nbuf_set_appdata(struct net_buf *buf, uint8_t *data)
{
	((struct net_nbuf *)net_buf_user_data(buf))->appdata = data;
}

static inline uint16_t net_nbuf_appdatalen(struct net_buf *buf)
{
	return ((struct net_nbuf *)net_buf_user_data(buf))->appdatalen;
}

static inline void net_nbuf_set_appdatalen(struct net_buf *buf, uint16_t len)
{
	((struct net_nbuf *)net_buf_user_data(buf))->appdatalen = len;
}

static inline uint8_t net_nbuf_ll_reserve(struct net_buf *buf)
{
	return ((struct net_nbuf *) net_buf_user_data(buf))->ll_reserve;
}

static inline void net_nbuf_set_ll_reserve(struct net_buf *buf, uint8_t len)
{
	((struct net_nbuf *) net_buf_user_data(buf))->ll_reserve = len;
}

static inline uint8_t *net_nbuf_ll(struct net_buf *buf)
{
	return net_nbuf_ip_data(buf) - net_nbuf_ll_reserve(buf);
}

static inline struct net_linkaddr *net_nbuf_ll_src(struct net_buf *buf)
{
	return &((struct net_nbuf *)net_buf_user_data(buf))->lladdr_src;
}

static inline struct net_linkaddr *net_nbuf_ll_dst(struct net_buf *buf)
{
	return &((struct net_nbuf *)net_buf_user_data(buf))->lladdr_dst;
}

static inline void net_nbuf_ll_clear(struct net_buf *buf)
{
	memset(net_nbuf_ll(buf), 0, net_nbuf_ll_reserve(buf));
	net_nbuf_ll_src(buf)->addr = NULL;
	net_nbuf_ll_src(buf)->len = 0;
}

static inline void net_nbuf_ll_swap(struct net_buf *buf)
{
	uint8_t *addr = net_nbuf_ll_src(buf)->addr;

	net_nbuf_ll_src(buf)->addr = net_nbuf_ll_dst(buf)->addr;
	net_nbuf_ll_dst(buf)->addr = addr;
}

static inline void net_nbuf_copy_user_data(struct net_buf *new,
					   struct net_buf *orig)
{
	memcpy((struct net_nbuf *)net_buf_user_data(new),
	       (struct net_nbuf *)net_buf_user_data(orig),
	       sizeof(struct net_nbuf));
}

#if defined(CONFIG_NET_IPV6)
static inline uint16_t net_nbuf_ipv6_hdr_prev(struct net_buf *buf)
{
	return ((struct net_nbuf *)
		net_buf_user_data(buf))->ipv6_prev_hdr_start;
}

static inline void net_nbuf_set_ipv6_hdr_prev(struct net_buf *buf,
					      uint16_t offset)
{
	((struct net_nbuf *)
	 net_buf_user_data(buf))->ipv6_prev_hdr_start = offset;
}

static inline uint8_t net_nbuf_ipv6_hop_limit(struct net_buf *buf)
{
	return ((struct net_nbuf *)
		net_buf_user_data(buf))->ipv6_hop_limit;
}

static inline void net_nbuf_set_ipv6_hop_limit(struct net_buf *buf,
					       uint8_t hop_limit)
{
	((struct net_nbuf *)
	 net_buf_user_data(buf))->ipv6_hop_limit = hop_limit;
}
#endif

#if defined(CONFIG_NET_IPV6_FRAGMENT)
static inline uint8_t *net_nbuf_ipv6_fragment_start(struct net_buf *buf)
{
	return ((struct net_nbuf *)
		net_buf_user_data(buf))->ipv6_frag_hdr_start;
}

static inline void net_nbuf_set_ipv6_fragment_start(struct net_buf *buf,
						    uint8_t *start)
{
	((struct net_nbuf *)
	 net_buf_user_data(buf))->ipv6_frag_hdr_start = start;
}

static inline uint16_t net_nbuf_ipv6_fragment_offset(struct net_buf *buf)
{
	return ((struct net_nbuf *)
		net_buf_user_data(buf))->ipv6_fragment_offset;
}

static inline void net_nbuf_set_ipv6_fragment_offset(struct net_buf *buf,
						     uint16_t offset)
{
	((struct net_nbuf *)
	 net_buf_user_data(buf))->ipv6_fragment_offset = offset;
}

static inline uint32_t net_nbuf_ipv6_fragment_id(struct net_buf *buf)
{
	return ((struct net_nbuf *)net_buf_user_data(buf))->ipv6_fragment_id;
}

static inline void net_nbuf_set_ipv6_fragment_id(struct net_buf *buf,
						 uint32_t id)
{
	((struct net_nbuf *)net_buf_user_data(buf))->ipv6_fragment_id = id;
}
#endif

#if defined(CONFIG_NET_L2_IEEE802154)
static inline uint8_t net_nbuf_ieee802154_rssi(struct net_buf *buf)
{
	return ((struct net_nbuf *)net_buf_user_data(buf))->ieee802154_rssi;
}

static inline void net_nbuf_set_ieee802154_rssi(struct net_buf *buf,
						uint8_t rssi)
{
	((struct net_nbuf *)net_buf_user_data(buf))->ieee802154_rssi = rssi;
}
#endif

#define NET_IPV6_BUF(buf) ((struct net_ipv6_hdr *)net_nbuf_ip_data(buf))
#define NET_IPV4_BUF(buf) ((struct net_ipv4_hdr *)net_nbuf_ip_data(buf))
#define NET_ICMP_BUF(buf) ((struct net_icmp_hdr *)net_nbuf_icmp_data(buf))
#define NET_UDP_BUF(buf)  ((struct net_udp_hdr *)(net_nbuf_udp_data(buf)))
#define NET_TCP_BUF(buf)  ((struct net_tcp_hdr *)(net_nbuf_tcp_data(buf)))

static inline void net_nbuf_set_src_ipv6_addr(struct net_buf *buf)
{
	net_if_ipv6_select_src_addr(net_context_get_iface(
					    net_nbuf_context(buf)),
				    &NET_IPV6_BUF(buf)->src);
}

/* @endcond */

/**
 * @brief Create a TX net_buf pool that is used when sending user
 * specified data to network.
 *
 * @param name Name of the pool.
 * @param count Number of net_buf in this pool.
 */
#define NET_NBUF_TX_POOL_DEFINE(name, count)				\
	NET_BUF_POOL_DEFINE(name, count, 0, sizeof(struct net_nbuf), NULL)

/**
 * @brief Create a DATA net_buf pool that is used when sending user
 * specified data to network.
 *
 * @param name Name of the pool.
 * @param count Number of net_buf in this pool.
 */
#define NET_NBUF_DATA_POOL_DEFINE(name, count)				\
	NET_BUF_POOL_DEFINE(name, count, CONFIG_NET_NBUF_DATA_SIZE,	\
			    CONFIG_NET_NBUF_USER_DATA_SIZE, NULL)

#if defined(CONFIG_NET_DEBUG_NET_BUF)

/* Debug versions of the nbuf functions that are used when tracking
 * buffer usage.
 */

struct net_buf *net_nbuf_get_reserve_debug(struct net_buf_pool *pool,
					   uint16_t reserve_head,
					   int32_t timeout,
					   const char *caller,
					   int line);
#define net_nbuf_get_reserve(pool, reserve_head, timeout)		\
	net_nbuf_get_reserve_debug(pool, reserve_head, timeout,		\
				   __func__, __LINE__)

struct net_buf *net_nbuf_get_rx_debug(struct net_context *context,
				      int32_t timeout,
				      const char *caller, int line);
#define net_nbuf_get_rx(context, timeout)				\
	net_nbuf_get_rx_debug(context, timeout, __func__, __LINE__)

struct net_buf *net_nbuf_get_tx_debug(struct net_context *context,
				      int32_t timeout,
				      const char *caller, int line);
#define net_nbuf_get_tx(context, timeout)				\
	net_nbuf_get_tx_debug(context, timeout, __func__, __LINE__)

struct net_buf *net_nbuf_get_data_debug(struct net_context *context,
					int32_t timeout,
					const char *caller, int line);
#define net_nbuf_get_data(context, timeout)				\
	net_nbuf_get_data_debug(context, timeout, __func__, __LINE__)

struct net_buf *net_nbuf_get_reserve_rx_debug(uint16_t reserve_head,
					      int32_t timeout,
					      const char *caller, int line);
#define net_nbuf_get_reserve_rx(res, timeout)				\
	net_nbuf_get_reserve_rx_debug(res, timeout, __func__, __LINE__)

struct net_buf *net_nbuf_get_reserve_tx_debug(uint16_t reserve_head,
					      int32_t timeout,
					      const char *caller, int line);
#define net_nbuf_get_reserve_tx(res, timeout)				\
	net_nbuf_get_reserve_tx_debug(res, timeout, __func__, __LINE__)

struct net_buf *net_nbuf_get_reserve_rx_data_debug(uint16_t reserve_head,
						   int32_t timeout,
						   const char *caller,
						   int line);
#define net_nbuf_get_reserve_rx_data(res, timeout)			\
	net_nbuf_get_reserve_rx_data_debug(res, timeout, __func__, __LINE__)

struct net_buf *net_nbuf_get_reserve_tx_data_debug(uint16_t reserve_head,
						   int32_t timeout,
						   const char *caller,
						   int line);
#define net_nbuf_get_reserve_tx_data(res, timeout)			\
	net_nbuf_get_reserve_tx_data_debug(res, timeout, __func__, __LINE__)

struct net_buf *net_nbuf_get_frag_debug(struct net_buf *buf,
					int32_t timeout,
					const char *caller, int line);
#define net_nbuf_get_frag(buf, timeout)					\
	net_nbuf_get_frag_debug(buf, timeout, __func__, __LINE__)

void net_nbuf_unref_debug(struct net_buf *buf, const char *caller, int line);
#define net_nbuf_unref(buf) net_nbuf_unref_debug(buf, __func__, __LINE__)

struct net_buf *net_nbuf_ref_debug(struct net_buf *buf, const char *caller,
				   int line);
#define net_nbuf_ref(buf) net_nbuf_ref_debug(buf, __func__, __LINE__)

struct net_buf *net_nbuf_frag_del_debug(struct net_buf *parent,
					struct net_buf *frag,
					const char *caller, int line);
#define net_nbuf_frag_del(parent, frag)					\
	net_nbuf_frag_del_debug(parent, frag, __func__, __LINE__)

/**
 * @brief Print fragment list and the fragment sizes
 *
 * @details Only available if debugging is activated.
 *
 * @param buf Network buffer fragment. This should be the first fragment (data)
 * in the fragment list.
 */
void net_nbuf_print_frags(struct net_buf *buf);

#else /* CONFIG_NET_DEBUG_NET_BUF */

#define net_nbuf_print_frags(...)

/**
 * @brief Get buffer from the given buffer pool.
 *
 * @details Get network buffer from the specific buffer pool.
 *
 * @param pool Network buffer pool.
 * @param reserve_head How many bytes to reserve for headroom.
 * @param timeout Affects the action taken should the net buf pool be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return Network buffer if successful, NULL otherwise.
 */
struct net_buf *net_nbuf_get_reserve(struct net_buf_pool *pool,
				     uint16_t reserve_head,
				     int32_t timeout);

/**
 * @brief Get buffer from the RX buffers pool.
 *
 * @details Get network buffer from RX buffer pool. You must have
 * network context before able to use this function.
 *
 * @param context Network context that will be related to
 * this buffer.
 * @param timeout Affects the action taken should the net buf pool be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return Network buffer if successful, NULL otherwise.
 */
struct net_buf *net_nbuf_get_rx(struct net_context *context,
				int32_t timeout);

/**
 * @brief Get buffer from the TX buffers pool.
 *
 * @details Get network buffer from TX buffer pool. You must have
 * network context before able to use this function.
 *
 * @param context Network context that will be related to
 * this buffer.
 * @param timeout Affects the action taken should the net buf pool be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return Network buffer if successful, NULL otherwise.
 */
struct net_buf *net_nbuf_get_tx(struct net_context *context,
				int32_t timeout);

/**
 * @brief Get buffer from the DATA buffers pool.
 *
 * @details Get network buffer from DATA buffer pool. You must have
 * network context before able to use this function.
 *
 * @param context Network context that will be related to
 * this buffer.
 * @param timeout Affects the action taken should the net buf pool be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return Network buffer if successful, NULL otherwise.
 */
struct net_buf *net_nbuf_get_data(struct net_context *context,
				  int32_t timeout);

/**
 * @brief Get RX buffer from pool but also reserve headroom for
 * potential headers.
 *
 * @details Normally this version is not useful for applications
 * but is mainly used by network fragmentation code.
 *
 * @param reserve_head How many bytes to reserve for headroom.
 * @param timeout Affects the action taken should the net buf pool be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return Network buffer if successful, NULL otherwise.
 */
struct net_buf *net_nbuf_get_reserve_rx(uint16_t reserve_head,
					int32_t timeout);

/**
 * @brief Get TX buffer from pool but also reserve headroom for
 * potential headers.
 *
 * @details Normally this version is not useful for applications
 * but is mainly used by network fragmentation code.
 *
 * @param reserve_head How many bytes to reserve for headroom.
 * @param timeout Affects the action taken should the net buf pool be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return Network buffer if successful, NULL otherwise.
 */
struct net_buf *net_nbuf_get_reserve_tx(uint16_t reserve_head,
					int32_t timeout);

/**
 * @brief Get RX DATA buffer from pool but also reserve headroom for
 * potential headers. Normally you should use net_nbuf_get_frag() instead.
 *
 * @details Normally this version is not useful for applications
 * but is mainly used by network fragmentation code.
 *
 * @param reserve_head How many bytes to reserve for headroom.
 * @param timeout Affects the action taken should the net buf pool be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return Network buffer if successful, NULL otherwise.
 */
struct net_buf *net_nbuf_get_reserve_rx_data(uint16_t reserve_head,
					     int32_t timeout);

/**
 * @brief Get TX DATA buffer from pool but also reserve headroom for
 * potential headers. Normally you should use net_nbuf_get_frag() instead.
 *
 * @details Normally this version is not useful for applications
 * but is mainly used by network fragmentation code.
 *
 * @param reserve_head How many bytes to reserve for headroom.
 * @param timeout Affects the action taken should the net buf pool be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return Network buffer if successful, NULL otherwise.
 */
struct net_buf *net_nbuf_get_reserve_tx_data(uint16_t reserve_head,
					     int32_t timeout);

/**
 * @brief Get a data fragment that might be from user specific
 * buffer pool or from global DATA pool.
 *
 * @param buf Network buffer. This must be the first buffer of the
 *        buffer chain with user data part in it.
 * @param timeout Affects the action taken should the net buf pool be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return Network buffer if successful, NULL otherwise.
 */
struct net_buf *net_nbuf_get_frag(struct net_buf *buf,
				  int32_t timeout);

/**
 * @brief Place buffer back into the available buffers pool.
 *
 * @details Releases the buffer to other use. This needs to be
 * called by application after it has finished with
 * the buffer.
 *
 * @param buf Network buffer to release.
 *
 */
void net_nbuf_unref(struct net_buf *buf);

/**
 * @brief Increase the ref count
 *
 * @details Mark the buffer to be used still.
 *
 * @param buf Network buffer to ref.
 *
 * @return Network buffer if successful, NULL otherwise.
 */
struct net_buf *net_nbuf_ref(struct net_buf *buf);

/** @brief Delete existing fragment from a chain of bufs.
 *
 *  @param parent Parent buffer/fragment, or NULL if there is no parent.
 *  @param frag Fragment to delete.
 *
 *  @return Pointer to the buffer following the fragment, or NULL if it
 *          had no further fragments.
 */
struct net_buf *net_nbuf_frag_del(struct net_buf *parent,
				  struct net_buf *frag);

#endif /* CONFIG_NET_DEBUG_NET_BUF */

/**
 * @brief Copy a buffer with fragments while reserving some extra space
 * in destination buffer before a copy.
 *
 * @param buf Network buffer. This should be the head of the buffer chain.
 * @param amount Max amount of data to be copied.
 * @param reserve Amount of extra data (this is not link layer header) in the
 * first data fragment that is returned. The function will copy the original
 * buffer right after the reserved bytes in the first destination fragment.
 * @param timeout Affects the action taken should the net buf pool be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return New fragment list if successful, NULL otherwise.
 */
struct net_buf *net_nbuf_copy(struct net_buf *buf, size_t amount,
			      size_t reserve, int32_t timeout);

/**
 * @brief Copy a buffer with fragments while reserving some extra space
 * in destination buffer before a copy.
 *
 * @param buf Network buffer fragment. This should be the head of the buffer
 * chain.
 * @param reserve Amount of extra data (this is not link layer header) in the
 * first data fragment that is returned. The function will copy the original
 * buffer right after the reserved bytes in the first destination fragment.
 * @param timeout Affects the action taken should the net buf pool be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return New fragment list if successful, NULL otherwise.
 */
static inline struct net_buf *net_nbuf_copy_all(struct net_buf *buf,
						size_t reserve,
						int32_t timeout)
{
	return net_nbuf_copy(buf, net_buf_frags_len(buf), reserve, timeout);
}

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
int net_nbuf_linear_copy(struct net_buf *dst, struct net_buf *src,
			 uint16_t offset, uint16_t len);

/**
 * @brief Compact the fragment list.
 *
 * @details After this there is no more any free space in individual fragments.
 * @param buf Network buffer fragment. This should be the Tx/Rx buffer.
 *
 * @return True if compact success, False otherwise. (Note that it fails only
 *         when input is data fragment)
 *
 */
bool net_nbuf_compact(struct net_buf *buf);

/**
 * @brief Check if the buffer chain is compact or not.
 *
 * @details The compact here means that is there any free space in the
 * fragments. Only the last fragment can have some free space if the fragment
 * list is compact.
 *
 * @param buf Network buffer.
 *
 * @return True if there is no free space in the fragment list,
 * false otherwise.
 */
bool net_nbuf_is_compact(struct net_buf *buf);

/**
 * @brief Remove given amount of data from the beginning of fragment list.
 * This is similar thing to do as in net_buf_pull() but this function changes
 * the fragment list instead of one fragment.
 *
 * @param buf Network buffer fragment list.
 * @param amount Max amount of data to be remove.
 *
 * @return Pointer to start of the fragment list if successful. NULL can be
 * returned if all fragments were removed from the list.
 */
struct net_buf *net_nbuf_pull(struct net_buf *buf, size_t amount);

/**
 * @brief Append data to last fragment in fragment list
 *
 * @details Append data to last fragment. If there is not enough space in
 * last fragment then new data fragment will be created and will be added to
 * fragment list. Caller has to take care of endianness if needed.
 *
 * @param buf Network buffer fragment list.
 * @param len Total length of input data
 * @param data Data to be added
 * @param timeout Affects the action taken should the net buf pool be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return True if all the data is placed at end of fragment list,
 *         False otherwise (In-case of false buf might contain input
 *         data in the process of placing into fragments).
 */
bool net_nbuf_append(struct net_buf *buf, uint16_t len, const uint8_t *data,
		     int32_t timeout);

/**
 * @brief Append uint8_t data to last fragment in fragment list
 *
 * @details Append data to last fragment. If there is not enough space in last
 * fragment then new data fragment will be created and will be added to
 * fragment list. Caller has to take care of endianness if needed.
 *
 * @param buf Network buffer fragment list.
 * @param data Data to be added
 *
 * @return True if all the data is placed at end of fragment list,
 *         False otherwise (In-case of false buf might contain input
 *         data in the process of placing into fragments).
 */
static inline bool net_nbuf_append_u8(struct net_buf *buf, uint8_t data)
{
	return net_nbuf_append(buf, 1, &data, K_FOREVER);
}

/**
 * @brief Append uint16_t data to last fragment in fragment list
 *
 * @details Append data to last fragment. If there is not enough space in last
 * fragment then new data fragment will be created and will be added to
 * fragment list. Caller has to take care of endianness if needed.
 *
 * @param buf Network buffer fragment list.
 * @param data Data to be added
 *
 * @return True if all the data is placed at end of fragment list,
 *         False otherwise (In-case of false buf might contain input data
 *         in the process of placing into fragments).
 */
static inline bool net_nbuf_append_be16(struct net_buf *buf, uint16_t data)
{
	uint16_t value = sys_cpu_to_be16(data);

	return net_nbuf_append(buf, sizeof(uint16_t), (uint8_t *)&value,
			       K_FOREVER);
}

/**
 * @brief Append uint32_t data to last fragment in fragment list
 *
 * @details Append data to last fragment. If there is not enough space in last
 * fragment then new data fragment will be created and will be added to
 * fragment list. Caller has to take care of endianness if needed.
 *
 * @param buf Network buffer fragment list.
 * @param data Data to be added
 *
 * @return True if all the data is placed at end of fragment list,
 *         False otherwise (In-case of false buf might contain input data
 *         in the process of placing into fragments).
 */
static inline bool net_nbuf_append_be32(struct net_buf *buf, uint32_t data)
{
	uint32_t value = sys_cpu_to_be32(data);

	return net_nbuf_append(buf, sizeof(uint32_t), (uint8_t *)&value,
			       K_FOREVER);
}

/**
 * @brief Append uint32_t data to last fragment in fragment list
 *
 * @details Append data to last fragment. If there is not enough space in last
 * fragment then new data fragment will be created and will be added to
 * fragment list. Convert data to LE.
 *
 * @param buf Network buffer fragment list.
 * @param data Data to be added
 *
 * @return True if all the data is placed at end of fragment list,
 *         False otherwise (In-case of false buf might contain input data
 *         in the process of placing into fragments).
 */
static inline bool net_nbuf_append_le32(struct net_buf *buf, uint32_t data)
{
	uint32_t value = sys_cpu_to_le32(data);

	return net_nbuf_append(buf, sizeof(uint32_t), (uint8_t *)&value,
			       K_FOREVER);
}

/**
 * @brief Get data from buffer
 *
 * @details Get N number of bytes starting from fragment's offset. If the total
 * length of data is placed in multiple framgents, this function will read from
 * all fragments until it reaches N number of bytes. Caller has to take care of
 * endianness if needed.
 *
 * @param buf Network buffer fragment.
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
struct net_buf *net_nbuf_read(struct net_buf *buf, uint16_t offset,
			      uint16_t *pos, uint16_t len, uint8_t *data);

/**
 * @brief Skip N number of bytes while reading buffer
 *
 * @details Skip N number of bytes starting from fragment's offset. If the total
 * length of data is placed in multiple framgents, this function will skip from
 * all fragments until it reaches N number of bytes. This function is useful
 * when unwanted data (e.g. reserved or not supported data in message) is part
 * of fragment and want to skip it.
 *
 * @param buf Network buffer fragment.
 * @param offset Offset of input buffer.
 * @param pos Pointer to position of offset after reading n number of bytes,
 *            this is with respect to return buffer(fragment).
 * @param len Total length of data to be read.
 *
 * @return Pointer to the fragment or
 *         NULL and pos is 0 after successful skip,
 *         NULL and pos is 0xffff otherwise.
 */
static inline struct net_buf *net_nbuf_skip(struct net_buf *buf,
					    uint16_t offset,
					    uint16_t *pos, uint16_t len)
{
	return net_nbuf_read(buf, offset, pos, len, NULL);
}

/**
 * @brief Get a byte value from fragmented buffer
 *
 * @param buf Network buffer fragment.
 * @param offset Offset of input buffer.
 * @param pos Pointer to position of offset after reading 2 bytes,
 *            this is with respect to return buffer(fragment).
 * @param value Value is returned
 *
 * @return Pointer to fragment after successful read,
 *         NULL otherwise (if pos is 0, NULL is not a failure case).
 */
static inline struct net_buf *net_nbuf_read_u8(struct net_buf *buf,
					       uint16_t offset,
					       uint16_t *pos,
					       uint8_t *value)
{
	return net_nbuf_read(buf, offset, pos, 1, value);
}

/**
 * @brief Get 16 bit big endian value from fragmented buffer
 *
 * @param buf Network buffer fragment.
 * @param offset Offset of input buffer.
 * @param pos Pointer to position of offset after reading 2 bytes,
 *            this is with respect to return buffer(fragment).
 * @param value Value is returned
 *
 * @return Pointer to fragment after successful read,
 *         NULL otherwise (if pos is 0, NULL is not a failure case).
 */
struct net_buf *net_nbuf_read_be16(struct net_buf *buf, uint16_t offset,
				   uint16_t *pos, uint16_t *value);

/**
 * @brief Get 32 bit big endian value from fragmented buffer
 *
 * @param buf Network buffer fragment.
 * @param offset Offset of input buffer.
 * @param pos Pointer to position of offset after reading 4 bytes,
 *            this is with respect to return buffer(fragment).
 * @param value Value is returned
 *
 * @return Pointer to fragment after successful read,
 *         NULL otherwise (if pos is 0, NULL is not a failure case).
 */
struct net_buf *net_nbuf_read_be32(struct net_buf *buf, uint16_t offset,
				   uint16_t *pos, uint32_t *value);

/**
 * @brief Write data to an arbitrary offset in a series of fragments.
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
 * 'overwritten'. Use net_nbuf_insert() api if you don't want to overwrite.
 *
 * Offset is calculated from starting point of data area in input fragment.
 * e.g. Buf(Tx/Rx) - Frag1 - Frag2 - Frag3 - Frag4
 *      (Assume FRAG DATA SIZE is 100 bytes after link layer header)
 *
 *      1) net_nbuf_write(buf, frag2, 20, &pos, 20, data, K_FOREVER)
 *         In this case write starts from "frag2->data + 20",
 *         returns frag2, pos = 40
 *
 *      2) net_nbuf_write(buf, frag1, 150, &pos, 60, data, K_FOREVER)
 *         In this case write starts from "frag2->data + 50"
 *         returns frag3, pos = 10
 *
 *      3) net_nbuf_write(buf, frag1, 350, &pos, 30, data, K_FOREVER)
 *         In this case write starts from "frag4->data + 50"
 *         returns frag4, pos = 80
 *
 *      4) net_nbuf_write(buf, frag2, 110, &pos, 90, data, K_FOREVER)
 *         In this case write starts from "frag3->data + 10"
 *         returns frag4, pos = 0
 *
 *      5) net_nbuf_write(buf, frag4, 110, &pos, 20, data, K_FOREVER)
 *         In this case write creates new data fragment and starts from
 *         "frag5->data + 10"
 *         returns frag5, pos = 30
 *
 * If input argument frag is NULL, it will create new data fragment
 * and append at the end of fragment list.
 *
 * @param buf    Network buffer fragment list.
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
struct net_buf *net_nbuf_write(struct net_buf *buf, struct net_buf *frag,
			       uint16_t offset, uint16_t *pos, uint16_t len,
			       uint8_t *data, int32_t timeout);

/* Write uint8_t data to an arbitrary offset in fragment. */
static inline struct net_buf *net_nbuf_write_u8(struct net_buf *buf,
						struct net_buf *frag,
						uint16_t offset,
						uint16_t *pos,
						uint8_t data)
{
	return net_nbuf_write(buf, frag, offset, pos, sizeof(uint8_t),
			      &data, K_FOREVER);
}

/* Write uint16_t big endian value to an arbitrary offset in fragment. */
static inline struct net_buf *net_nbuf_write_be16(struct net_buf *buf,
						  struct net_buf *frag,
						  uint16_t offset,
						  uint16_t *pos,
						  uint16_t data)
{
	uint16_t value = htons(data);

	return net_nbuf_write(buf, frag, offset, pos, sizeof(uint16_t),
			      (uint8_t *)&value, K_FOREVER);
}

/* Write uint32_t big endian value to an arbitrary offset in fragment. */
static inline struct net_buf *net_nbuf_write_be32(struct net_buf *buf,
						  struct net_buf *frag,
						  uint16_t offset,
						  uint16_t *pos,
						  uint32_t data)
{
	uint32_t value = htonl(data);

	return net_nbuf_write(buf, frag, offset, pos, sizeof(uint32_t),
			      (uint8_t *)&value, K_FOREVER);
}

/**
 * @brief Insert data at an arbitrary offset in a series of fragments.
 *
 * @details Insert data at an arbitrary offset in a series of fragments. Offset
 * is based on fragment length (only user written data length, any tailroom
 * in fragments does not come to consideration unlike net_nbuf_write()) and
 * calculates from input fragment starting position.
 *
 * Offset examples can be considered from net_nbuf_write() api.
 * If the offset is more than already allocated fragments length then it is an
 * error case.
 *
 * @param buf    Network buffer fragment list.
 * @param frag   Network buffer fragment.
 * @param offset Offset of fragment where insertion will start.
 * @param len    Length of the data to be inserted.
 * @param data   Data to be inserted
 * @param timeout Affects the action taken should the net buf pool be empty.
 *        If K_NO_WAIT, then return immediately. If K_FOREVER, then
 *        wait as long as necessary. Otherwise, wait up to the specified
 *        number of milliseconds before timing out.
 *
 * @return True on success,
 *         False otherwise.
 */
bool net_nbuf_insert(struct net_buf *buf, struct net_buf *frag,
		     uint16_t offset, uint16_t len, uint8_t *data,
		     int32_t timeout);

/* Insert uint8_t data at an arbitrary offset in a series of fragments. */
static inline bool net_nbuf_insert_u8(struct net_buf *buf,
				      struct net_buf *frag,
				      uint16_t offset,
				      uint8_t data)
{
	return net_nbuf_insert(buf, frag, offset, sizeof(uint8_t), &data,
			       K_FOREVER);
}

/* Insert uint16_t big endian value at an arbitrary offset in a series of
 * fragments.
 */
static inline bool net_nbuf_insert_be16(struct net_buf *buf,
					struct net_buf *frag,
					uint16_t offset,
					uint16_t data)
{
	uint16_t value = htons(data);

	return net_nbuf_insert(buf, frag, offset, sizeof(uint16_t),
			       (uint8_t *)&value, K_FOREVER);
}

/* Insert uint32_t big endian value at an arbitrary offset in a series of
 * fragments.
 */
static inline bool net_nbuf_insert_be32(struct net_buf *buf,
					struct net_buf *frag,
					uint16_t offset,
					uint32_t data)
{
	uint32_t value = htonl(data);

	return net_nbuf_insert(buf, frag, offset, sizeof(uint32_t),
			       (uint8_t *)&value, K_FOREVER);
}

/**
 * @brief Split a fragment to two parts at arbitrary offset.
 *
 * @details This will generate two new fragments (fragA and fragB) from
 * one (orig_frag). The original fragment is not modified but two new
 * fragments are allocated and returned to the caller. The original fragment
 * must be part of the chain pointed by the buf parameter. If the len parameter
 * is larger than the amount of data in the orig fragment, then the fragA will
 * contain all the data and fragB will be empty.
 *
 * @param buf Head of the network buffer fragment list.
 * @param orig_frag Original network buffer fragment which is to be split.
 * @param len Amount of data in the first returned fragment.
 * @param fragA A fragment is returned. This will contain len bytes that
 * are copied from start of orig_frag.
 * @param fragB Another fragment is returned. This will contain remaining
 * bytes (orig_frag->len - len) from the orig_frag or NULL if all the data
 * was copied into fragA.
 * @param timeout Affects the action taken should the net buf pool be empty.
 * If K_NO_WAIT, then return immediately. If K_FOREVER, then wait as long as
 * necessary. Otherwise, wait up to the specified number of milliseconds before
 * timing out.
 *
 * @return 0 on success, <0 otherwise.
 */
int net_nbuf_split(struct net_buf *buf, struct net_buf *orig_frag,
		   uint16_t len, struct net_buf **fragA,
		   struct net_buf **fragB, int32_t timeout);

/**
 * @brief Get information about pre-defined RX, TX and DATA pools.
 *
 * @param rx Pointer to RX pool is returned.
 * @param tx Pointer to TX pool is returned.
 * @param rx_data Pointer to RX DATA pool is returned.
 * @param tx_data Pointer to TX DATA pool is returned.
 */
void net_nbuf_get_info(struct net_buf_pool **rx,
		       struct net_buf_pool **tx,
		       struct net_buf_pool **rx_data,
		       struct net_buf_pool **tx_data);

#if defined(CONFIG_NET_DEBUG_NET_BUF)
/**
 * @brief Debug helper to print out the buffer allocations
 */
void net_nbuf_print(void);
#else
#define net_nbuf_print(...)
#endif /* CONFIG_NET_DEBUG_NET_BUF */

#if defined(CONFIG_NET_DEBUG_NET_BUF)
typedef void (*net_nbuf_allocs_cb_t)(struct net_buf *buf,
				     const char *func_alloc,
				     int line_alloc,
				     const char *func_free,
				     int line_free,
				     bool in_use,
				     void *user_data);

void net_nbuf_allocs_foreach(net_nbuf_allocs_cb_t cb, void *user_data);
const char *net_nbuf_pool2str(struct net_buf_pool *pool);

#endif /* CONFIG_NET_DEBUG_NET_BUF */

#ifdef __cplusplus
}
#endif

#endif /* __NBUF_H */
