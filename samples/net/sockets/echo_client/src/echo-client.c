/* echo-client.c - Networking echo client */

/*
 * Copyright (c) 2017 Intel Corporation.
 * Copyright (c) 2018 Nordic Semiconductor ASA.
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

#include <net/socket.h>
#include <net/tls_credentials.h>

#include "common.h"
#include "ca_certificate.h"

#define APP_BANNER "Run echo client"

/* Generated by http://www.lipsum.com/
 * 2 paragraphs, 171 words, 1210 bytes of Lorem Ipsum
 */
const char lorem_ipsum[] =
	"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse "
	"eleifend odio sit amet scelerisque tincidunt. In orci ligula, egestas "
	"ut neque sit amet, fringilla malesuada dolor. Fusce rhoncus nunc in "
	"lacus tincidunt lobortis. Donec aliquam lectus gravida fermentum "
	"egestas. Curabitur eu ex pretium, dapibus massa in, pretium tellus. "
	"Suspendisse ac efficitur magna, ut convallis nisl. Duis sed sapien "
	"odio. Aliquam efficitur sed tellus sit amet eleifend. Sed facilisis "
	"ligula aliquam erat ornare hendrerit. Aenean tincidunt nunc a nulla "
	"vestibulum mollis. Vivamus fringilla euismod nisi sit amet malesuada. "
	"Vivamus consequat ultricies metus sed feugiat. Aenean malesuada "
	"cursus sem."
	"\n"
	"Vestibulum tempor diam et aliquam tristique. Nullam condimentum felis "
	"et convallis finibus. Aliquam erat volutpat. Nam et blandit tortor. "
	"Nullam pharetra arcu aliquam, suscipit mi eu, faucibus lacus. "
	"Pellentesque eleifend nulla sit amet purus maximus, et elementum "
	"lectus fringilla. Praesent consectetur diam eget tellus molestie "
	"tempor. Class aptent taciti sociosqu ad litora torquent per conubia "
	"nostra, per inceptos himenaeos. Nam tincidunt urna augue, nec cursus "
	"arcu eleifend nec. Donec semper tellus in leo nullam."
	"\n";

const int ipsum_len = sizeof(lorem_ipsum) - 1;

struct configs conf = {
	.ipv4 = {
		.proto = "IPv4",
	},
	.ipv6 = {
		.proto = "IPv6",
	},
};

struct pollfd fds[4];
int nfds;

static void prepare_fds(void)
{
	if (conf.ipv4.udp.sock > 0) {
		fds[nfds].fd = conf.ipv4.udp.sock;
		fds[nfds].events = POLLIN;
		nfds++;
	}

	if (conf.ipv4.tcp.sock > 0) {
		fds[nfds].fd = conf.ipv4.tcp.sock;
		fds[nfds].events = POLLIN;
		nfds++;
	}

	if (conf.ipv6.udp.sock > 0) {
		fds[nfds].fd = conf.ipv6.udp.sock;
		fds[nfds].events = POLLIN;
		nfds++;
	}

	if (conf.ipv6.tcp.sock > 0) {
		fds[nfds].fd = conf.ipv6.tcp.sock;
		fds[nfds].events = POLLIN;
		nfds++;
	}
}

static void wait(void)
{
	/* Wait for event on any socket used. Once event occurs,
	 * we'll check them all.
	 */
	if (poll(fds, nfds, K_FOREVER) < 0) {
		NET_ERR("Error in poll:%d", errno);
	}
}

static void init_app(void)
{
	NET_INFO(APP_BANNER);

#if defined(CONFIG_NET_SOCKETS_SOCKOPT_TLS)
	int err = tls_credential_add(CA_CERTIFICATE_TAG,
				    TLS_CREDENTIAL_CA_CERTIFICATE,
				    ca_certificate,
				    sizeof(ca_certificate));
	if (err < 0) {
		NET_ERR("Failed to register public certificate: %d", err);
	}
#endif
}

void main(void)
{
	int ret;

	init_app();

	if (IS_ENABLED(CONFIG_NET_TCP)) {
		ret = start_tcp();
		if (ret < 0) {
			goto quit;
		}
	}

	if (IS_ENABLED(CONFIG_NET_UDP)) {
		ret = start_udp();
		if (ret < 0) {
			goto quit;
		}
	}

	prepare_fds();

	while (true) {
		if (IS_ENABLED(CONFIG_NET_TCP)) {
			ret = process_tcp();
			if (ret < 0) {
				goto quit;
			}
		}

		if (IS_ENABLED(CONFIG_NET_UDP)) {
			ret = process_udp();
			if (ret < 0) {
				goto quit;
			}
		}

		wait();
	}

quit:
	NET_INFO("Stopping...");

	if (IS_ENABLED(CONFIG_NET_UDP)) {
		stop_udp();
	}

	if (IS_ENABLED(CONFIG_NET_TCP)) {
		stop_tcp();
	}
}
