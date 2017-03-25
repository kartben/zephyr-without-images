/* echo-client.c - Networking echo client */

/*
 * Copyright (c) 2016 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * The echo-client application is acting as a client that is run in Zephyr OS,
 * and echo-server is run in the host acting as a server. The client will send
 * either unicast or multicast packets to the server which will reply the packet
 * back to the originator.
 */

#if 1
#define SYS_LOG_DOMAIN "echo-client"
#define NET_SYS_LOG_LEVEL SYS_LOG_LEVEL_DEBUG
#define NET_LOG_ENABLED 1
#endif

#include <zephyr.h>
#include <sections.h>
#include <errno.h>
#include <stdio.h>

#include <net/nbuf.h>
#include <net/net_if.h>
#include <net/net_core.h>
#include <net/net_context.h>
#include <net/net_mgmt.h>

#if defined(CONFIG_NET_L2_BLUETOOTH)
#include <bluetooth/bluetooth.h>
#include <gatt/ipss.h>
#endif

/* Generated by http://www.lipsum.com/
 * 3 paragraphs, 176 words, 1230 bytes of Lorem Ipsum
 */
static char *lorem_ipsum =
	"Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
	"Vestibulum id cursus felis, sit amet suscipit velit. Integer "
	"facilisis malesuada porta. Nunc at accumsan mauris. Etiam vehicula, "
	"arcu consequat feugiat venenatis, tellus velit gravida ligula, quis "
	"posuere sem leo eget urna. Curabitur condimentum leo nec orci "
	"mattis, nec faucibus dui rutrum. Ut mollis orci in iaculis "
	"consequat. Nulla volutpat nibh eu velit sagittis, a iaculis dui "
	"aliquam."
	"\n"
	"Quisque interdum consequat eros a eleifend. Fusce dapibus nisl "
	"sit amet velit posuere imperdiet. Quisque accumsan tempor massa "
	"sit amet tincidunt. Integer sollicitudin vehicula tristique. Nulla "
	"sagittis massa turpis, ac ultricies neque posuere eu. Nulla et "
	"imperdiet ex. Etiam venenatis sed lacus tincidunt hendrerit. In "
	"libero nisl, congue id tellus vitae, tincidunt tristique mauris. "
	"Nullam sed porta massa. Sed condimentum sem eu convallis euismod. "
	"Suspendisse lobortis purus faucibus, gravida turpis id, mattis "
	"velit. Maecenas eleifend sapien eu tincidunt lobortis. Sed elementum "
	"sapien id enim laoreet consequat."
	"\n"
	"Aenean et neque aliquam, lobortis lectus in, consequat leo. Sed "
	"quis egestas nulla. Quisque ac risus quis elit mollis finibus. "
	"Phasellus efficitur imperdiet metus."
	"\n";

#define STACKSIZE 2048

static int ipsum_len;

/* Note that both tcp and udp can share the same pool but in this
 * example the UDP context and TCP context have separate pools.
 */
#if defined(CONFIG_NET_CONTEXT_NBUF_POOL)
#if defined(CONFIG_NET_TCP)
NET_NBUF_TX_POOL_DEFINE(echo_tx_tcp, 15);
NET_NBUF_DATA_POOL_DEFINE(echo_data_tcp, 30);

static struct net_buf_pool *tx_tcp_pool(void)
{
	return &echo_tx_tcp;
}

static struct net_buf_pool *data_tcp_pool(void)
{
	return &echo_data_tcp;
}
#endif

#if defined(CONFIG_NET_UDP)
NET_NBUF_TX_POOL_DEFINE(echo_tx_udp, 5);
NET_NBUF_DATA_POOL_DEFINE(echo_data_udp, 20);

static struct net_buf_pool *tx_udp_pool(void)
{
	return &echo_tx_udp;
}

static struct net_buf_pool *data_udp_pool(void)
{
	return &echo_data_udp;
}
#endif
#endif /* CONFIG_NET_CONTEXT_NBUF_POOL */

#define MY_PORT 8484
#define PEER_PORT 4242

struct data {
	uint32_t expecting_udp;
	uint32_t expecting_tcp;
	uint32_t received_tcp;
};

static struct {
#if defined(CONFIG_NET_UDP)
	/* semaphore for controlling udp data sending */
	struct k_sem recv_ipv6;
	struct k_sem recv_ipv4;
#endif /* CONFIG_NET_UDP */

	struct data ipv4;
	struct data ipv6;
} conf;

#if defined(CONFIG_NET_TCP)
static bool send_tcp_data(struct net_context *ctx,
			  char *proto,
			  struct data *data);
#endif /* CONFIG_NET_TCP */

#if defined(CONFIG_NET_IPV6)
/* Define the peer IP address where to send messages */
#define PEER_IP6ADDR { { { 0x20, 0x01, 0x0d, 0xb8, 0, 0, 0, 0, \
			   0, 0, 0, 0, 0, 0, 0, 0x2 } } }

#define MY_IP6ADDR { { { 0x20, 0x01, 0x0d, 0xb8, 0, 0, 0, 0,	\
			 0, 0, 0, 0, 0, 0, 0, 0x1 } } }

#define MY_PREFIX_LEN 64

#if defined(CONFIG_NET_SAMPLES_IP_ADDRESSES)
static struct in6_addr in6addr_my = MY_IP6ADDR;
static struct in6_addr in6addr_peer = PEER_IP6ADDR;
#endif

static struct sockaddr_in6 my_addr6 = {
	.sin6_family = AF_INET6,
	.sin6_port = htons(MY_PORT),
};

static struct sockaddr_in6 peer_addr6 = {
	.sin6_family = AF_INET6,
	.sin6_port = htons(PEER_PORT),
};

#if defined(CONFIG_NET_UDP)
static char __noinit __stack ipv6_udp_stack[STACKSIZE];
#endif

#if defined(CONFIG_NET_TCP)
static char __noinit __stack ipv6_tcp_stack[STACKSIZE];
#endif

#endif /* CONFIG_NET_IPV6 */

#if defined(CONFIG_NET_IPV4)
#define MY_IP4ADDR { { { 192, 0, 2, 1 } } }
#define PEER_IP4ADDR { { { 192, 0, 2, 2 } } }

#if defined(CONFIG_NET_SAMPLES_IP_ADDRESSES)
static struct in_addr in4addr_my = MY_IP4ADDR;
static struct in_addr in4addr_peer = PEER_IP4ADDR;
#endif

static struct sockaddr_in my_addr4 = {
	.sin_family = AF_INET,
	.sin_port = htons(MY_PORT),
};

static struct sockaddr_in peer_addr4 = {
	.sin_family = AF_INET,
	.sin_port = htons(PEER_PORT),
};

#if defined(CONFIG_NET_UDP)
static char __noinit __stack ipv4_udp_stack[STACKSIZE];
#endif

#if defined(CONFIG_NET_TCP)
static char __noinit __stack ipv4_tcp_stack[STACKSIZE];
#endif

#endif /* CONFIG_NET_IPV4 */

#define WAIT_TIME  (2 * MSEC_PER_SEC)

#if defined(CONFIG_NET_MGMT_EVENT)
static struct net_mgmt_event_callback cb;
#endif

static inline void init_app(void)
{
	NET_INFO("Run echo client");

#if defined(CONFIG_NET_IPV6)
#if defined(CONFIG_NET_SAMPLES_IP_ADDRESSES)
	if (net_addr_pton(AF_INET6,
			  CONFIG_NET_SAMPLES_MY_IPV6_ADDR,
			  &my_addr6.sin6_addr) < 0) {
		NET_ERR("Invalid IPv6 address %s",
			CONFIG_NET_SAMPLES_MY_IPV6_ADDR);

		net_ipaddr_copy(&my_addr6.sin6_addr, &in6addr_my);
	}
#endif

#if defined(CONFIG_NET_SAMPLES_IP_ADDRESSES)
	if (net_addr_pton(AF_INET6,
			  CONFIG_NET_SAMPLES_PEER_IPV6_ADDR,
			  &peer_addr6.sin6_addr) < 0) {
		NET_ERR("Invalid peer IPv6 address %s",
			CONFIG_NET_SAMPLES_PEER_IPV6_ADDR);

		net_ipaddr_copy(&peer_addr6.sin6_addr, &in6addr_peer);
	}
#endif

	do {
		struct net_if_addr *ifaddr;

		ifaddr = net_if_ipv6_addr_add(net_if_get_default(),
					      &my_addr6.sin6_addr,
					      NET_ADDR_MANUAL, 0);
	} while (0);

#if defined(CONFIG_NET_UDP)
	k_sem_init(&conf.recv_ipv6, 0, UINT_MAX);
#endif
#endif

#if defined(CONFIG_NET_IPV4)
#if defined(CONFIG_NET_DHCPV4)
	net_dhcpv4_start(net_if_get_default());
#else
#if defined(CONFIG_NET_SAMPLES_IP_ADDRESSES)
	if (net_addr_pton(AF_INET,
			  CONFIG_NET_SAMPLES_MY_IPV4_ADDR,
			  &my_addr4.sin_addr) < 0) {
		NET_ERR("Invalid IPv4 address %s",
			CONFIG_NET_SAMPLES_MY_IPV4_ADDR);

		net_ipaddr_copy(&my_addr4.sin_addr, &in4addr_my);
	}
#endif

#if defined(CONFIG_NET_SAMPLES_IP_ADDRESSES)
	if (net_addr_pton(AF_INET,
			  CONFIG_NET_SAMPLES_PEER_IPV4_ADDR,
			  &peer_addr4.sin_addr) < 0) {
		NET_ERR("Invalid peer IPv4 address %s",
			CONFIG_NET_SAMPLES_PEER_IPV4_ADDR);

		net_ipaddr_copy(&peer_addr4.sin_addr, &in4addr_peer);
	}
#endif

	net_if_ipv4_addr_add(net_if_get_default(), &my_addr4.sin_addr,
			     NET_ADDR_MANUAL, 0);
#endif /* CONFIG_NET_DHCPV4 */

#if defined(CONFIG_NET_UDP)
	k_sem_init(&conf.recv_ipv4, 0, UINT_MAX);
#endif
#endif
}

static inline bool get_context(struct net_context **udp_recv4,
			       struct net_context **udp_recv6,
			       struct net_context **tcp_recv4,
			       struct net_context **tcp_recv6)
{
	int ret;

#if defined(CONFIG_NET_IPV6) && defined(CONFIG_NET_UDP)
	ret = net_context_get(AF_INET6, SOCK_DGRAM, IPPROTO_UDP, udp_recv6);
	if (ret < 0) {
		NET_ERR("Cannot get network context for IPv6 UDP (%d)",
			ret);
		return false;
	}

	net_context_setup_pools(*udp_recv6, tx_udp_pool, data_udp_pool);

	ret = net_context_bind(*udp_recv6, (struct sockaddr *)&my_addr6,
			       sizeof(struct sockaddr_in6));
	if (ret < 0) {
		NET_ERR("Cannot bind IPv6 UDP port %d (%d)",
			ntohs(my_addr6.sin6_port), ret);
		return false;
	}
#endif

#if defined(CONFIG_NET_IPV4) && defined(CONFIG_NET_UDP)
	ret = net_context_get(AF_INET, SOCK_DGRAM, IPPROTO_UDP, udp_recv4);
	if (ret < 0) {
		NET_ERR("Cannot get network context for IPv4 UDP (%d)",
			ret);
		return false;
	}

	net_context_setup_pools(*udp_recv4, tx_udp_pool, data_udp_pool);

	ret = net_context_bind(*udp_recv4, (struct sockaddr *)&my_addr4,
			       sizeof(struct sockaddr_in));
	if (ret < 0) {
		NET_ERR("Cannot bind IPv4 UDP port %d (%d)",
			ntohs(my_addr4.sin_port), ret);
		return false;
	}
#endif

#if defined(CONFIG_NET_IPV6) && defined(CONFIG_NET_TCP)
	if (tcp_recv6) {
		ret = net_context_get(AF_INET6, SOCK_STREAM, IPPROTO_TCP,
				      tcp_recv6);
		if (ret < 0) {
			NET_ERR("Cannot get network context "
				"for IPv6 TCP (%d)", ret);
			return false;
		}

		net_context_setup_pools(*tcp_recv6, tx_tcp_pool, data_tcp_pool);

		ret = net_context_bind(*tcp_recv6,
				       (struct sockaddr *)&my_addr6,
				       sizeof(struct sockaddr_in6));
		if (ret < 0) {
			NET_ERR("Cannot bind IPv6 TCP port %d (%d)",
				ntohs(my_addr6.sin6_port), ret);
			return false;
		}
	}
#endif

#if defined(CONFIG_NET_IPV4) && defined(CONFIG_NET_TCP)
	if (tcp_recv4) {
		ret = net_context_get(AF_INET, SOCK_STREAM, IPPROTO_TCP,
				      tcp_recv4);
		if (ret < 0) {
			NET_ERR("Cannot get network context for IPv4 TCP");
			return false;
		}

		net_context_setup_pools(*tcp_recv4, tx_tcp_pool, data_tcp_pool);

		ret = net_context_bind(*tcp_recv4,
				       (struct sockaddr *)&my_addr4,
				       sizeof(struct sockaddr_in));
		if (ret < 0) {
			NET_ERR("Cannot bind IPv4 TCP port %d",
				ntohs(my_addr4.sin_port));
			return false;
		}
	}
#endif

	return true;
}

static inline bool wait_reply(const char *name,
			      struct k_sem *sem)
{
	int ret = k_sem_take(sem, WAIT_TIME);

	ARG_UNUSED(name);

	if (!ret) {
		return true;
	}

	NET_ERR("wait_reply returned %s",
		ret == -EAGAIN ? "on time out" : "directly");

	return false;
}

static struct net_buf *prepare_send_buf(const char *name,
					struct net_context *context,
					int expecting_len)
{
	struct net_buf *send_buf;
	bool status;

	send_buf = net_nbuf_get_tx(context, K_FOREVER);

	NET_ASSERT(send_buf);

	status = net_nbuf_append(send_buf, expecting_len, lorem_ipsum,
				 K_FOREVER);
	if (!status) {
		NET_ERR("%s: cannot create send buf", name);
		return NULL;
	}

	return send_buf;
}

static inline void udp_sent(struct net_context *context,
			    int status,
			    void *bytes_sent,
			    void *user_data)
{
	ARG_UNUSED(context);

	if (!status) {
		NET_INFO("%s: sent %u bytes", (char *)user_data,
			 POINTER_TO_UINT(bytes_sent));
	}
}

static inline void set_dst_addr(sa_family_t family,
				struct net_buf *buf,
				struct sockaddr *dst_addr)
{
	ARG_UNUSED(buf);

#if defined(CONFIG_NET_IPV6)
	if (family == AF_INET6) {
		net_ipaddr_copy(&net_sin6(dst_addr)->sin6_addr,
				&peer_addr6.sin6_addr);
		net_sin6(dst_addr)->sin6_family = AF_INET6;
		net_sin6(dst_addr)->sin6_port = htons(PEER_PORT);

		return;
	}
#endif /* CONFIG_NET_IPV6 */

#if defined(CONFIG_NET_IPV4)
	if (family == AF_INET) {
		net_ipaddr_copy(&net_sin(dst_addr)->sin_addr,
				&peer_addr4.sin_addr);
		net_sin(dst_addr)->sin_family = AF_INET;
		net_sin(dst_addr)->sin_port = htons(PEER_PORT);

		return;
	}
#endif /* CONFIG_NET_IPV4 */
}

#if defined(CONFIG_NET_UDP)
static bool compare_udp_data(struct net_buf *buf, int expecting_len)
{
	uint8_t *ptr = net_nbuf_appdata(buf);
	int pos = 0;
	int len;

	/* Buf will now point to first fragment with IP header
	 * in it.
	 */
	buf = buf->frags;

	/* Do not include the protocol headers in the first fragment.
	 * The remaining fragments contain only data so the user data
	 * length is directly the fragment len.
	 */
	len = buf->len - (ptr - buf->data);

	while (buf) {
		if (memcmp(ptr, lorem_ipsum + pos, len)) {
			NET_DBG("Invalid data received");
			return false;
		} else {
			pos += len;

			buf = buf->frags;
			if (!buf) {
				break;
			}

			ptr = buf->data;
			len = buf->len;
		}
	}

	NET_DBG("Compared %d bytes, all ok", expecting_len);

	return true;
}

static void setup_udp_recv(struct net_context *udp, void *user_data,
			   net_context_recv_cb_t cb)
{
	int ret;

	ret = net_context_recv(udp, cb, 0, user_data);
	if (ret < 0) {
		NET_ERR("Cannot receive UDP packets");
	}
}

static bool send_udp_data(struct net_context *udp,
			  sa_family_t family,
			  char *proto,
			  struct data *data)
{
	bool status = false;
	struct net_buf *send_buf;
	struct sockaddr dst_addr;
	socklen_t addrlen;
	size_t len;
	int ret;

	data->expecting_udp = sys_rand32_get() % ipsum_len;

	send_buf = prepare_send_buf(proto, udp, data->expecting_udp);
	if (!send_buf) {
		goto out;
	}

	len = net_buf_frags_len(send_buf);

	NET_ASSERT_INFO(data->expecting_udp == len,
			"Data to send %d bytes, real len %zu",
			data->expecting_udp, len);

	set_dst_addr(family, send_buf, &dst_addr);

	if (family == AF_INET6) {
		addrlen = sizeof(struct sockaddr_in6);
	} else {
		addrlen = sizeof(struct sockaddr_in);
	}

	ret = net_context_sendto(send_buf, &dst_addr,
				 addrlen, udp_sent, 0,
				 UINT_TO_POINTER(len),
				 proto);
	if (ret < 0) {
		NET_ERR("Cannot send %s data to peer (%d)", proto, ret);
		net_nbuf_unref(send_buf);
	} else {
		status = true;
	}
out:

	return status;
}

static void udp_received(struct net_context *context,
			      struct net_buf *buf,
			      int status,
			      void *user_data)
{
	sa_family_t family = net_nbuf_family(buf);
	struct data *data = user_data;
	struct k_sem *recv;

	ARG_UNUSED(context);
	ARG_UNUSED(status);

	if (family == AF_INET) {
		recv = &conf.recv_ipv4;
	} else {
		recv = &conf.recv_ipv6;
	}

	if (data->expecting_udp != net_nbuf_appdatalen(buf)) {
		NET_ERR("Sent %d bytes, received %u bytes",
			data->expecting_udp, net_nbuf_appdatalen(buf));
	}

	if (!compare_udp_data(buf, data->expecting_udp)) {
		NET_DBG("Data mismatch");
	}

	net_nbuf_unref(buf);

	k_sem_give(recv);
}

static void send_udp(struct net_context *udp,
		     sa_family_t family,
		     char *proto,
		     struct k_sem *sem,
		     struct data *data)
{
	setup_udp_recv(udp, data, udp_received);

	NET_INFO("Starting to send %s data", proto);

	do {
		/* We first send a packet, then wait for a packet to arrive.
		 * If the reply does not come in time, we send another packet.
		 */
		send_udp_data(udp, family, proto, data);

		NET_DBG("Waiting %s packet", proto);

		if (!wait_reply(proto, sem)) {
			NET_DBG("Waited %d bytes but did not receive them.",
				data->expecting_udp);
		}

		k_yield();
	} while (1);
}

#endif /* CONFIG_NET_UDP */

#if defined(CONFIG_NET_TCP)
static bool compare_tcp_data(struct net_buf *buf, int expecting_len,
			     int received_len)
{
	uint8_t *ptr = net_nbuf_appdata(buf), *start;
	int pos = 0;
	struct net_buf *frag;
	int len;

	/* frag will point to first fragment with IP header in it.
	 */
	frag = buf->frags;

	/* Do not include the protocol headers for the first fragment.
	 * The remaining fragments contain only data so the user data
	 * length is directly the fragment len.
	 */
	len = frag->len - (ptr - frag->data);

	start = lorem_ipsum + received_len;

	while (frag) {
		if (memcmp(ptr, start + pos, len)) {
			NET_DBG("Invalid data received");
			return false;
		}

		pos += len;

		frag = frag->frags;
		if (!frag) {
			break;
		}

		ptr = frag->data;
		len = frag->len;
	}

	NET_DBG("Compared %d bytes, all ok", net_nbuf_appdatalen(buf));

	return true;
}

static void tcp_received(struct net_context *context,
			 struct net_buf *buf,
			 int status,
			 void *user_data)
{
	struct data *data = user_data;
	char *proto;

	ARG_UNUSED(status);

	if (!buf || net_nbuf_appdatalen(buf) == 0) {
		if (buf) {
			net_nbuf_unref(buf);
		}

		return;
	}

	if (net_nbuf_family(buf) == AF_INET6) {
		proto = "IPv6";
	} else {
		proto = "IPv4";
	}

	NET_DBG("Sent %d bytes, received %u bytes",
		data->expecting_tcp, net_nbuf_appdatalen(buf));

	if (!compare_tcp_data(buf, data->expecting_tcp, data->received_tcp)) {
		NET_DBG("Data mismatch");
	} else {
		data->received_tcp += net_nbuf_appdatalen(buf);
	}

	if (data->expecting_tcp <= data->received_tcp) {
		/* Send more data */
		send_tcp_data(context, proto, data);
	}

	net_nbuf_unref(buf);
}

static void setup_tcp_recv(struct net_context *tcp,
			   net_context_recv_cb_t cb,
			   void *user_data)
{
	int ret;

	ret = net_context_recv(tcp, cb, 0, user_data);
	if (ret < 0) {
		NET_ERR("Cannot receive TCP packets (%d)", ret);
	}
}

static void tcp_sent(struct net_context *context,
		     int status,
		     void *token,
		     void *user_data)
{
	uint32_t len = POINTER_TO_UINT(token);

	if (len) {
		if (status) {
			NET_DBG("%s: len %u status %d", (char *)user_data,
				len, status);
		} else {
			NET_DBG("%s: len %u", (char *)user_data, len);
		}
	}
}

static bool send_tcp_data(struct net_context *ctx,
			  char *proto,
			  struct data *data)
{
	struct net_buf *send_buf;
	bool status = false;
	size_t len;
	int ret;

	data->expecting_tcp = sys_rand32_get() % ipsum_len;
	data->received_tcp = 0;

	send_buf = prepare_send_buf(proto, ctx, data->expecting_tcp);
	if (!send_buf) {
		goto out;
	}

	len = net_buf_frags_len(send_buf);

	NET_ASSERT_INFO(data->expecting_tcp == len,
			"%s data to send %d bytes, real len %zu",
			proto, data->expecting_tcp, len);

	ret = net_context_send(send_buf, tcp_sent, 0,
			       UINT_TO_POINTER(len), proto);
	if (ret < 0) {
		NET_ERR("Cannot send %s data to peer (%d)", proto, ret);
		net_nbuf_unref(send_buf);
	} else {
		status = true;
	}

out:
	return status;
}

static void tcp_connected(struct net_context *context,
			  int status,
			  void *user_data)
{
	/* Start to send data */
	sa_family_t family = POINTER_TO_UINT(user_data);

	NET_DBG("%s connected.", family == AF_INET ? "IPv4" : "IPv6");

	if (family == AF_INET) {
#if defined(CONFIG_NET_IPV4)
		setup_tcp_recv(context, tcp_received, &conf.ipv4);

		send_tcp_data(context, "IPv4", &conf.ipv4);
#else
		NET_DBG("IPv4 data skipped.");
#endif
	} else if (family == AF_INET6) {
#if defined(CONFIG_NET_IPV6)
		setup_tcp_recv(context, tcp_received, &conf.ipv6);

		send_tcp_data(context, "IPv6", &conf.ipv6);
#else
		NET_DBG("IPv6 data skipped.");
#endif
	}
}

#if defined(CONFIG_NET_IPV4)
static void tcp_connect4(struct net_context *tcp_send)
{
	int ret;

	ret = net_context_connect(tcp_send,
				  (struct sockaddr *)&peer_addr4,
				  sizeof(peer_addr4),
				  tcp_connected,
				  K_FOREVER,
				  UINT_TO_POINTER(AF_INET));
	if (ret < 0) {
		NET_DBG("Cannot connect to IPv4 peer (%d)", ret);
	}
}
#endif

#if defined(CONFIG_NET_IPV6)
static void tcp_connect6(struct net_context *tcp_send)
{
	int ret;

	ret = net_context_connect(tcp_send,
				  (struct sockaddr *)&peer_addr6,
				  sizeof(peer_addr6),
				  tcp_connected,
				  K_FOREVER,
				  UINT_TO_POINTER(AF_INET6));
	if (ret < 0) {
		NET_DBG("Cannot connect to IPv6 peer (%d)", ret);
	}
}
#endif /* CONFIG_NET_IPV6 */
#endif /* CONFIG_NET_TCP */

#if defined(CONFIG_NET_IPV4) && defined(CONFIG_NET_UDP)
static void send_udp_ipv4(struct net_context *udp)
{
	send_udp(udp, AF_INET, "IPv4", &conf.recv_ipv4, &conf.ipv4);
}
#endif

#if defined(CONFIG_NET_IPV4) && defined(CONFIG_NET_TCP)
static void send_tcp_ipv4(struct net_context *tcp)
{
	tcp_connect4(tcp);
}
#endif

#if defined(CONFIG_NET_IPV6) && defined(CONFIG_NET_UDP)
static void send_udp_ipv6(struct net_context *udp)
{
	send_udp(udp, AF_INET6, "IPv6", &conf.recv_ipv6, &conf.ipv6);
}
#endif

#if defined(CONFIG_NET_IPV6) && defined(CONFIG_NET_TCP)
static void send_tcp_ipv6(struct net_context *tcp)
{
	tcp_connect6(tcp);
}
#endif

static void event_iface_up(struct net_mgmt_event_callback *cb,
			   uint32_t mgmt_event, struct net_if *iface)
{
	struct net_context *udp_send4 = { 0 };
	struct net_context *udp_send6 = { 0 };
	struct net_context *tcp_send4 = { 0 };
	struct net_context *tcp_send6 = { 0 };

	ipsum_len = strlen(lorem_ipsum);

	if (!get_context(&udp_send4, &udp_send6,
			 &tcp_send4, &tcp_send6)) {
		NET_ERR("Cannot get network contexts");
		return;
	}

#if defined(CONFIG_NET_IPV4) && defined(CONFIG_NET_UDP)
	k_thread_spawn(ipv4_udp_stack, STACKSIZE,
		       (k_thread_entry_t)send_udp_ipv4,
		       udp_send4, NULL, NULL, K_PRIO_COOP(7), 0, 0);
#endif

#if defined(CONFIG_NET_IPV4) && defined(CONFIG_NET_TCP)
	k_thread_spawn(ipv4_tcp_stack, STACKSIZE,
		       (k_thread_entry_t)send_tcp_ipv4,
		       tcp_send4, NULL, NULL, K_PRIO_COOP(7), 0, 0);
#endif

#if defined(CONFIG_NET_IPV6) && defined(CONFIG_NET_UDP)
	k_thread_spawn(ipv6_udp_stack, STACKSIZE,
		       (k_thread_entry_t)send_udp_ipv6,
		       udp_send6, NULL, NULL, K_PRIO_COOP(7), 0, 0);
#endif

#if defined(CONFIG_NET_IPV6) && defined(CONFIG_NET_TCP)
	k_thread_spawn(ipv6_tcp_stack, STACKSIZE,
		       (k_thread_entry_t)send_tcp_ipv6,
		       tcp_send6, NULL, NULL, K_PRIO_COOP(7), 0, 0);
#endif
}

void main(void)
{
	struct net_if *iface = net_if_get_default();

	init_app();

#if defined(CONFIG_NET_L2_BLUETOOTH)
	if (bt_enable(NULL)) {
		NET_ERR("Bluetooth init failed\n");
		return;
	}
#endif

#if defined(CONFIG_NET_MGMT_EVENT)
	/* Subscribe to NET_IF_UP if interface is not ready */
	if (!atomic_test_bit(iface->flags, NET_IF_UP)) {
		net_mgmt_init_event_callback(&cb, event_iface_up,
					     NET_EVENT_IF_UP);
		net_mgmt_add_event_callback(&cb);
		return;
	}
#endif

	event_iface_up(NULL, NET_EVENT_IF_UP, iface);
}
