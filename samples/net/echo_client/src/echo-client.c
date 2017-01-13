/* echo-client.c - Networking echo client */

/*
 * Copyright (c) 2016 Intel Corporation.
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

#if defined(CONFIG_NET_IPV6)
/* admin-local, dynamically allocated multicast address */
#define MCAST_IP6ADDR { { { 0xff, 0x84, 0, 0, 0, 0, 0, 0, \
			    0, 0, 0, 0, 0, 0, 0, 0x2 } } }

/* Define the peer IP address where to send messages */
#define PEER_IP6ADDR { { { 0x20, 0x01, 0x0d, 0xb8, 0, 0, 0, 0, \
			   0, 0, 0, 0, 0, 0, 0, 0x2 } } }

#define MY_IP6ADDR { { { 0x20, 0x01, 0x0d, 0xb8, 0, 0, 0, 0,	\
			 0, 0, 0, 0, 0, 0, 0, 0x1 } } }

#define MY_PREFIX_LEN 64

static struct in6_addr in6addr_my = MY_IP6ADDR;
static struct in6_addr in6addr_peer = PEER_IP6ADDR;
static struct in6_addr in6addr_mcast = MCAST_IP6ADDR;
static struct k_sem recv_ipv6;
static int expecting_ipv6;
static char __noinit __stack ipv6_stack[STACKSIZE];

#endif /* CONFIG_NET_IPV6 */

#if defined(CONFIG_NET_IPV4)
/* Organization-local 239.192.0.0/14 */
#define MCAST_IP4ADDR { { { 239, 192, 0, 2 } } }

#define MY_IP4ADDR { { { 192, 0, 2, 1 } } }
#define PEER_IP4ADDR { { { 192, 0, 2, 2 } } }

static struct in_addr in4addr_my = MY_IP4ADDR;
static struct in_addr in4addr_peer = PEER_IP4ADDR;
static struct k_sem recv_ipv4;
static int expecting_ipv4;
static char __noinit __stack ipv4_stack[STACKSIZE];

#endif /* CONFIG_NET_IPV4 */

#define MY_PORT 8484
#define PEER_PORT 4242

#define WAIT_TIME  (2 * MSEC_PER_SEC)

#if defined(CONFIG_NET_MGMT_EVENT)
static struct net_mgmt_event_callback cb;
#endif

static inline void init_app(void)
{
	NET_INFO("Run echo client");

#if defined(CONFIG_NET_IPV6)
#if defined(CONFIG_NET_SAMPLES_MY_IPV6_ADDR)
	if (net_addr_pton(AF_INET6,
			  CONFIG_NET_SAMPLES_MY_IPV6_ADDR,
			  (struct sockaddr *)&in6addr_my) < 0) {
		NET_ERR("Invalid IPv6 address %s",
			CONFIG_NET_SAMPLES_MY_IPV6_ADDR);
	}
#endif

#if defined(CONFIG_NET_SAMPLES_PEER_IPV6_ADDR)
	if (net_addr_pton(AF_INET6,
			  CONFIG_NET_SAMPLES_PEER_IPV6_ADDR,
			  (struct sockaddr *)&in6addr_peer) < 0) {
		NET_ERR("Invalid peer IPv6 address %s",
			CONFIG_NET_SAMPLES_PEER_IPV6_ADDR);
	}
#endif

	do {
		struct net_if_addr *ifaddr;

		ifaddr = net_if_ipv6_addr_add(net_if_get_default(),
					      &in6addr_my, NET_ADDR_MANUAL, 0);
	} while (0);

	net_if_ipv6_maddr_add(net_if_get_default(), &in6addr_mcast);

	k_sem_init(&recv_ipv6, 0, UINT_MAX);
#endif

#if defined(CONFIG_NET_IPV4)
#if defined(CONFIG_NET_DHCPV4)
	net_dhcpv4_start(net_if_get_default());
#else
#if defined(CONFIG_NET_SAMPLES_MY_IPV4_ADDR)
	if (net_addr_pton(AF_INET,
			  CONFIG_NET_SAMPLES_MY_IPV4_ADDR,
			  (struct sockaddr *)&in4addr_my) < 0) {
		NET_ERR("Invalid IPv4 address %s",
			CONFIG_NET_SAMPLES_MY_IPV4_ADDR);
	}
#endif

#if defined(CONFIG_NET_SAMPLES_PEER_IPV4_ADDR)
	if (net_addr_pton(AF_INET,
			  CONFIG_NET_SAMPLES_PEER_IPV4_ADDR,
			  (struct sockaddr *)&in4addr_peer) < 0) {
		NET_ERR("Invalid peer IPv4 address %s",
			CONFIG_NET_SAMPLES_PEER_IPV4_ADDR);
	}
#endif

	net_if_ipv4_addr_add(net_if_get_default(), &in4addr_my,
			     NET_ADDR_MANUAL, 0);
#endif /* CONFIG_NET_DHCPV4 */

	k_sem_init(&recv_ipv4, 0, UINT_MAX);
#endif
}

static inline bool get_context(struct net_context **udp_recv4,
			       struct net_context **udp_recv6,
			       struct net_context **mcast_recv6)
{
	int ret;

#if defined(CONFIG_NET_IPV6)
	struct sockaddr_in6 mcast_addr6 = { 0 };
	struct sockaddr_in6 my_addr6 = { 0 };
#endif

#if defined(CONFIG_NET_IPV4)
	struct sockaddr_in my_addr4 = { 0 };
#endif

#if defined(CONFIG_NET_IPV6)
	net_ipaddr_copy(&mcast_addr6.sin6_addr, &in6addr_mcast);
	mcast_addr6.sin6_family = AF_INET6;

	net_ipaddr_copy(&my_addr6.sin6_addr, &in6addr_my);
	my_addr6.sin6_family = AF_INET6;
	my_addr6.sin6_port = htons(MY_PORT);
#endif

#if defined(CONFIG_NET_IPV4)
	net_ipaddr_copy(&my_addr4.sin_addr, &in4addr_my);
	my_addr4.sin_family = AF_INET;
	my_addr4.sin_port = htons(MY_PORT);
#endif

#if defined(CONFIG_NET_IPV6) && defined(CONFIG_NET_UDP)
	ret = net_context_get(AF_INET6, SOCK_DGRAM, IPPROTO_UDP, udp_recv6);
	if (ret < 0) {
		NET_ERR("Cannot get network context for IPv6 UDP (%d)",
			ret);
		return false;
	}

	ret = net_context_bind(*udp_recv6, (struct sockaddr *)&my_addr6,
			       sizeof(struct sockaddr_in6));
	if (ret < 0) {
		NET_ERR("Cannot bind IPv6 UDP port %d (%d)",
			ntohs(my_addr6.sin6_port), ret);
		return false;
	}

	ret = net_context_get(AF_INET6, SOCK_DGRAM, IPPROTO_UDP, mcast_recv6);
	if (ret < 0) {
		NET_ERR("Cannot get receiving IPv6 mcast "
			"network context (%d)", ret);
		return false;
	}

	ret = net_context_bind(*mcast_recv6, (struct sockaddr *)&mcast_addr6,
			       sizeof(struct sockaddr_in6));
	if (ret < 0) {
		NET_ERR("Cannot bind IPv6 mcast (%d)", ret);
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

	ret = net_context_bind(*udp_recv4, (struct sockaddr *)&my_addr4,
			       sizeof(struct sockaddr_in));
	if (ret < 0) {
		NET_ERR("Cannot bind IPv4 UDP port %d (%d)",
			ntohs(my_addr4.sin_port), ret);
		return false;
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

	send_buf = net_nbuf_get_tx(context);

	NET_ASSERT(send_buf);

	status = net_nbuf_append(send_buf, expecting_len, lorem_ipsum);
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
				&in6addr_peer);
		net_sin6(dst_addr)->sin6_family = AF_INET6;
		net_sin6(dst_addr)->sin6_port = htons(PEER_PORT);

		return;
	}
#endif /* CONFIG_NET_IPV6 */

#if defined(CONFIG_NET_IPV4)
	if (family == AF_INET) {
		net_ipaddr_copy(&net_sin(dst_addr)->sin_addr,
				&in4addr_peer);
		net_sin(dst_addr)->sin_family = AF_INET;
		net_sin(dst_addr)->sin_port = htons(PEER_PORT);

		return;
	}
#endif /* CONFIG_NET_IPV4 */
}

static bool compare_data(struct net_buf *buf, int expecting_len)
{
	uint8_t *ptr = net_nbuf_appdata(buf);
	int pos = 0;
	int len;

	/* Buf will now point to first fragment with IP header
	 * in it.
	 */
	buf = buf->frags;

	/* Do not include the protocol headers in len for the
	 * first fragment. The remaining fragments contain only
	 * data so the user data length is directly the fragment len.
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

#if defined(CONFIG_NET_IPV4)
static bool send_ipv4_data(struct net_context *udp)
{
	struct net_buf *send_buf;
	struct sockaddr dst_addr;
	bool status = false;
	size_t len;
	int ret;

	expecting_ipv4 = sys_rand32_get() % ipsum_len;

	send_buf = prepare_send_buf("IPv4", udp, expecting_ipv4);
	if (!send_buf) {
		goto out;
	}

	len = net_buf_frags_len(send_buf);

	NET_ASSERT_INFO(expecting_ipv4 == len,
			"Data to send %d bytes, real len %zu",
			expecting_ipv4, len);

	set_dst_addr(AF_INET, send_buf, &dst_addr);

	ret = net_context_sendto(send_buf, &dst_addr,
				 sizeof(struct sockaddr_in),
				 udp_sent, 0,
				 UINT_TO_POINTER(len),
				 "IPv4");
	if (ret < 0) {
		NET_ERR("Cannot send IPv4 data to peer (%d)", ret);
		net_nbuf_unref(send_buf);
	} else {
		status = true;
	}
out:

	return status;
}

static void udp_ipv4_received(struct net_context *context,
			      struct net_buf *buf,
			      int status,
			      void *user_data)
{
	sa_family_t family = net_nbuf_family(buf);
	struct k_sem *recv = user_data;

	ARG_UNUSED(context);
	ARG_UNUSED(status);

	if (family == AF_INET) {
		if (expecting_ipv4 != net_nbuf_appdatalen(buf)) {
			NET_ERR("Sent %d bytes, received %u bytes",
				expecting_ipv4, net_nbuf_appdatalen(buf));
		}

		if (!compare_data(buf, expecting_ipv4)) {
			NET_DBG("Data mismatch");
		}

		net_nbuf_unref(buf);

		k_sem_give(recv);
	}
}

static void send_ipv4(struct net_context *udp)
{
	setup_udp_recv(udp, &recv_ipv4, udp_ipv4_received);

	NET_INFO("Starting to send IPv4 data");

	do {
		/* We first send a packet, then wait for a packet to arrive.
		 * If the reply does not come in time, we send another packet.
		 */
		send_ipv4_data(udp);

		NET_DBG("Waiting IPv4 packet");

		if (!wait_reply("IPv4", &recv_ipv4)) {
			NET_DBG("Waited %d bytes but did not receive them.",
				expecting_ipv4);
		}

		k_yield();
	} while (1);
}
#endif

#if defined(CONFIG_NET_IPV6)
static bool send_ipv6_data(struct net_context *udp)
{
	struct net_buf *send_buf;
	struct sockaddr dst_addr;
	bool status = false;
	size_t len;
	int ret;

	expecting_ipv6 = sys_rand32_get() % ipsum_len;

	send_buf = prepare_send_buf("IPv6", udp, expecting_ipv6);
	if (!send_buf) {
		goto out;
	}

	len = net_buf_frags_len(send_buf);

	NET_ASSERT_INFO(expecting_ipv6 == len,
			"Data to send %d bytes, real len %d",
			expecting_ipv6, len);

	set_dst_addr(AF_INET6, send_buf, &dst_addr);

	ret = net_context_sendto(send_buf, &dst_addr,
				 sizeof(struct sockaddr_in6),
				 udp_sent, 0,
				 UINT_TO_POINTER(len),
				 "IPv6");
	if (ret < 0) {
		NET_ERR("Cannot send IPv6 data to peer (%d)", ret);
		net_nbuf_unref(send_buf);
	} else {
		status = true;
	}
out:

	return status;
}

static void udp_ipv6_received(struct net_context *context,
			      struct net_buf *buf,
			      int status,
			      void *user_data)
{
	sa_family_t family = net_nbuf_family(buf);
	struct k_sem *recv = user_data;

	ARG_UNUSED(context);
	ARG_UNUSED(status);

	if (family == AF_INET6) {
		if (expecting_ipv6 != net_nbuf_appdatalen(buf)) {
			NET_ERR("Sent %d bytes, received %d bytes",
				expecting_ipv6, net_nbuf_appdatalen(buf));
		}

		if (!compare_data(buf, expecting_ipv6)) {
			NET_DBG("Data mismatch");
		}

		net_nbuf_unref(buf);

		k_sem_give(recv);
	}
}

static void send_ipv6(struct net_context *udp)
{
	setup_udp_recv(udp, &recv_ipv6, udp_ipv6_received);

	NET_INFO("Starting to send IPv6 data");

	do {
		/* We first send a packet, then wait for a packet to arrive.
		 * If the reply does not come in time, we send another packet.
		 */
		send_ipv6_data(udp);

		NET_DBG("Waiting IPv6 packet");

		if (!wait_reply("IPv6", &recv_ipv6)) {
			NET_DBG("Waited %d bytes but did not receive them.",
				expecting_ipv6);
		}

		k_yield();
	} while (1);
}
#endif

static void event_iface_up(struct net_mgmt_event_callback *cb,
			   uint32_t mgmt_event, struct net_if *iface)
{
	struct net_context *udp_send4 = { 0 };
	struct net_context *udp_send6 = { 0 };
	struct net_context *mcast_send6 = { 0 };

	ipsum_len = strlen(lorem_ipsum);

	if (!get_context(&udp_send4, &udp_send6, &mcast_send6)) {
		NET_ERR("Cannot get network contexts");
		return;
	}

#if defined(CONFIG_NET_IPV4)
	k_thread_spawn(ipv4_stack, STACKSIZE,
		       (k_thread_entry_t)send_ipv4,
		       udp_send4, NULL, NULL, K_PRIO_COOP(7), 0, 0);
#endif

#if defined(CONFIG_NET_IPV6)
	k_thread_spawn(ipv6_stack, STACKSIZE,
		       (k_thread_entry_t)send_ipv6,
		       udp_send6, NULL, NULL, K_PRIO_COOP(7), 0, 0);
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
