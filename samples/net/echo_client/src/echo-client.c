/* echo-client.c - Networking echo client */

/*
 * Copyright (c) 2017 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * The echo-client application is acting as a client that is run in Zephyr OS,
 * and echo-server is run in the host acting as a server. The client will send
 * either unicast or multicast packets to the server which will reply the packet
 * back to the originator.
 *
 * In this sample application we create four threads that start to send data.
 * This might not be what you want to do in your app so caveat emptor.
 */

#if 1
#define SYS_LOG_DOMAIN "echo-client"
#define NET_SYS_LOG_LEVEL SYS_LOG_LEVEL_DEBUG
#define NET_LOG_ENABLED 1
#endif

#include <zephyr.h>
#include <errno.h>
#include <stdio.h>

#include <net/net_pkt.h>
#include <net/net_core.h>
#include <net/net_context.h>

#include <net/net_app.h>

#include "common.h"

#define APP_BANNER "Run echo client"

/* Generated by http://www.lipsum.com/
 * 3 paragraphs, 176 words, 1230 bytes of Lorem Ipsum
 */
const char lorem_ipsum[] =
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

int ipsum_len = sizeof(lorem_ipsum) - 1;

struct configs conf = {
	.ipv4 = {
		.proto = "IPv4",
	},
	.ipv6 = {
		.proto = "IPv6",
	},
};

static struct k_sem quit_lock;
struct k_sem tcp_ready;

void panic(const char *msg)
{
	if (msg) {
		NET_ERR("%s", msg);
	}

	k_sem_give(&quit_lock);

	for (;;) {
		k_sleep(K_FOREVER);
	}
}

static inline int init_app(void)
{
	NET_INFO(APP_BANNER);

	k_sem_init(&quit_lock, 0, UINT_MAX);

	return 0;
}

struct net_pkt *prepare_send_pkt(struct net_app_ctx *ctx,
				 const char *name,
				 int expecting_len)
{
	struct net_pkt *send_pkt;
	bool status;

	send_pkt = net_app_get_net_pkt(ctx, AF_UNSPEC, K_FOREVER);

	NET_ASSERT(send_pkt);

	status = net_pkt_append_all(send_pkt, expecting_len, lorem_ipsum,
				    K_FOREVER);
	if (!status) {
		NET_ERR("%s: cannot create send pkt", name);
		net_pkt_unref(send_pkt);
		return NULL;
	}

	return send_pkt;
}

void main(void)
{
	int ret;

	init_app();

	if (IS_ENABLED(CONFIG_NET_TCP)) {
		if (IS_ENABLED(CONFIG_NET_UDP)) {
			k_sem_init(&tcp_ready, 0, 1);
		}

		ret = start_tcp();
		if (ret < 0) {
			goto quit;
		}

		/* We start the UDP after the TCP is connected properly.
		 * This is done like this so that UDP does not use all the
		 * buffers as it is basically flooding the link with UDP
		 * data.
		 */
		if (IS_ENABLED(CONFIG_NET_UDP)) {
			k_sem_take(&tcp_ready, K_FOREVER);
		}
	}

	if (IS_ENABLED(CONFIG_NET_UDP)) {
		start_udp();
	}

	k_sem_take(&quit_lock, K_FOREVER);

quit:
	NET_INFO("Stopping...");

	if (IS_ENABLED(CONFIG_NET_UDP)) {
		stop_udp();
	}

	if (IS_ENABLED(CONFIG_NET_TCP)) {
		stop_tcp();
	}
}
