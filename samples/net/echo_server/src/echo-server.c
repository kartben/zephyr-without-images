/* echo.c - Networking echo server */

/*
 * Copyright (c) 2015 Intel Corporation.
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

#if defined(CONFIG_STDOUT_CONSOLE)
#include <stdio.h>
#define PRINT           printf
#else
#include <misc/printk.h>
#define PRINT           printk
#endif

#include <zephyr.h>
#include <sections.h>

#include <net/ip_buf.h>
#include <net/net_core.h>
#include <net/net_socket.h>

#include <contiki/ipv6/uip-ds6-route.h>
#include <contiki/ip/uip.h>
#include <contiki/ipv6/uip-ds6.h>

#ifndef CONFIG_ETHERNET
/* The peer is the client in our case. Just invent a mac
 * address for it because lower parts of the stack cannot set it
 * in this test as we do not have any radios.
 */
static uint8_t peer_mac[] = { 0x15, 0x0a, 0xbe, 0xef, 0xf0, 0x0d };

/* This is my mac address
 */
static uint8_t my_mac[] = { 0x0a, 0xbe, 0xef, 0x15, 0xf0, 0x0d };
#endif

#ifdef CONFIG_NETWORKING_WITH_IPV6
/* The 2001:db8::/32 is the private address space for documentation RFC 3849 */
#define MY_IPADDR { { { 0x20,0x01,0x0d,0xb8,0,0,0,0,0,0,0,0,0,0,0,0x1 } } }
#define PEER_IPADDR { { { 0x20,0x01,0x0d,0xb8,0,0,0,0,0,0,0,0,0,0,0,0x2 } } }

/* admin-local, dynamically allocated multicast address */
#define MCAST_IPADDR { { { 0xff,0x84,0,0,0,0,0,0,0,0,0,0,0,0,0,0x2 } } }

static const struct in6_addr in6addr_peer = PEER_IPADDR;
static struct in6_addr in6addr_my = MY_IPADDR;
#else
/* The 192.0.2.0/24 is the private address space for documentation RFC 5737 */
#define MY_IPADDR { { { 192,0,2,2 } } }

/* Organization-local 239.192.0.0/14 */
#define MCAST_IPADDR { { { 239,192,0,2 } } }
#endif
#define MY_PORT 4242

static inline void init_server()
{
	PRINT("%s: run echo server\n", __func__);

#ifndef CONFIG_ETHERNET
	net_set_mac(my_mac, sizeof(my_mac));
#endif

#ifdef CONFIG_NETWORKING_WITH_IPV4
	{
		uip_ipaddr_t addr;
		uip_ipaddr(&addr, 192,0,2,2);
		uip_sethostaddr(&addr);
	}
#else /* IPv6 */
	{
		uip_ipaddr_t *addr;

#ifdef CONFIG_NETWORKING_IPV6_NO_ND
		/* Set the routes and neighbor cache only if we do not have
		 * neighbor discovery enabled. This setting should only be
		 * used if running in qemu and using slip (tun device).
		 */
		const uip_lladdr_t *lladdr = (const uip_lladdr_t *)&peer_mac;

		addr = (uip_ipaddr_t *)&in6addr_peer;
		uip_ds6_defrt_add(addr, 0);

		/* We cannot send to peer unless it is in neighbor
		 * cache. Neighbor cache should be populated automatically
		 * but do it here so that test works from first packet.
		 */
		uip_ds6_nbr_add(addr, lladdr, 0, NBR_REACHABLE);
#else
		/* Hard code the route to peer just in case, not to
		 * be done in real life applications.
		 */
		addr = (uip_ipaddr_t *)&in6addr_peer;
		uip_ds6_defrt_add(addr, 0);
#endif

		addr = (uip_ipaddr_t *)&in6addr_my;
		uip_ds6_addr_add(addr, 0, ADDR_MANUAL);
	}
#endif
}

static inline void reverse(unsigned char *buf, int len)
{
	int i, last = len - 1;

	for (i = 0; i < len / 2; i++) {
		unsigned char tmp = buf[i];
		buf[i] = buf[last - i];
		buf[last - i] = tmp;
	}
}

static inline struct net_buf *prepare_reply(const char *name,
					    const char *type,
					    struct net_buf *buf)
{
	PRINT("%s: %sreceived %d bytes\n", name, type,
	      ip_buf_appdatalen(buf));

	/* In this test we reverse the received bytes.
	 * We could just pass the data back as is but
	 * this way it is possible to see how the app
	 * can manipulate the received data.
	 */
	reverse(ip_buf_appdata(buf), ip_buf_appdatalen(buf));

#ifndef CONFIG_ETHERNET
	/* Set the mac address of the peer in net_buf because
	 * there is no radio layer involved in this test app.
	 * Normally there is no need to do this.
	 */
	memcpy(&ip_buf_ll_src(buf), &peer_mac, sizeof(ip_buf_ll_src(buf)));
#endif

	return buf;
}

/* How many tics to wait for a network packet */
#if 0
#define WAIT_TIME 1
#define WAIT_TICKS (WAIT_TIME * sys_clock_ticks_per_sec)
#else
#define WAIT_TICKS TICKS_UNLIMITED
#endif

static inline void receive_and_reply(const char *name, struct net_context *recv,
				     struct net_context *mcast_recv)
{
	struct net_buf *buf;

	buf = net_receive(recv, WAIT_TICKS);
	if (buf) {
		prepare_reply(name, "unicast ", buf);

		if (net_reply(recv, buf)) {
			ip_buf_unref(buf);
		}
		return;
	}

	buf = net_receive(mcast_recv, WAIT_TICKS);
	if (buf) {
		prepare_reply(name, "multicast ", buf);

		if (net_reply(mcast_recv, buf)) {
			ip_buf_unref(buf);
		}
		return;
	}
}

static inline bool get_context(struct net_context **recv,
			       struct net_context **mcast_recv)
{
	static struct net_addr mcast_addr;
	static struct net_addr any_addr;
	static struct net_addr my_addr;

#ifdef CONFIG_NETWORKING_WITH_IPV6
	static const struct in6_addr in6addr_any = IN6ADDR_ANY_INIT;
	static const struct in6_addr in6addr_mcast = MCAST_IPADDR;

	mcast_addr.in6_addr = in6addr_mcast;
	mcast_addr.family = AF_INET6;

	any_addr.in6_addr = in6addr_any;
	any_addr.family = AF_INET6;

	my_addr.in6_addr = in6addr_my;
	my_addr.family = AF_INET6;
#else
	static const struct in_addr in4addr_any = { { { 0 } } };
	static struct in_addr in4addr_my = MY_IPADDR;
	static struct in_addr in4addr_mcast = MCAST_IPADDR;

	mcast_addr.in_addr = in4addr_mcast;
	mcast_addr.family = AF_INET;

	any_addr.in_addr = in4addr_any;
	any_addr.family = AF_INET;

	my_addr.in_addr = in4addr_my;
	my_addr.family = AF_INET;
#endif

	*recv = net_context_get(IPPROTO_UDP,
				&any_addr, 0,
				&my_addr, MY_PORT);
	if (!*recv) {
		PRINT("%s: Cannot get network context\n", __func__);
		return NULL;
	}

	*mcast_recv = net_context_get(IPPROTO_UDP,
				      &any_addr, 0,
				      &mcast_addr, MY_PORT);
	if (!*mcast_recv) {
		PRINT("%s: Cannot get receiving mcast network context\n",
		      __func__);
		return false;
	}

	return true;
}

#ifdef CONFIG_NANOKERNEL
#define STACKSIZE 2000
char __noinit __stack fiberStack[STACKSIZE];
#endif

void receive(void)
{
	static struct net_context *recv;
	static struct net_context *mcast_recv;

	if (!get_context(&recv, &mcast_recv)) {
		PRINT("%s: Cannot get network contexts\n", __func__);
		return;
	}

	while (1) {
		receive_and_reply(__func__, recv, mcast_recv);
	}
}

void main(void)
{
	net_init();

	init_server();

#ifdef CONFIG_MICROKERNEL
	receive();
#else
	task_fiber_start (&fiberStack[0], STACKSIZE,
			(nano_fiber_entry_t)receive, 0, 0, 7, 0);
#endif
}
