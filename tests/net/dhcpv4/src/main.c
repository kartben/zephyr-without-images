/* main.c - Application main entry point */

/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <logging/log.h>
LOG_MODULE_REGISTER(net_test, CONFIG_NET_DHCPV4_LOG_LEVEL);

#include <zephyr.h>
#include <linker/sections.h>

#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <device.h>
#include <init.h>
#include <net/net_core.h>
#include <net/net_pkt.h>
#include <net/net_ip.h>
#include <net/dhcpv4.h>
#include <net/ethernet.h>
#include <net/net_mgmt.h>
#include <net/dummy.h>

#include "ipv4.h"
#include "udp_internal.h"

#include <tc_util.h>
#include <ztest.h>

#define NET_LOG_ENABLED 1
#include "net_private.h"

/* Sample DHCP offer (382 bytes) */
static const unsigned char offer[382] = {
0x02, 0x01, 0x06, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x0a, 0xed, 0x48, 0x9e, 0x0a, 0xb8,
0x09, 0x01, 0x0a, 0xed, 0x48, 0x02, 0x00, 0x00,
0x5E, 0x00, 0x53, 0x01, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x82,
0x53, 0x63, 0x35, 0x01, 0x02, 0x01, 0x04, 0xff,
0xff, 0xff, 0x00, 0x3a, 0x04, 0x00, 0x00, 0x54,
0x60, 0x3b, 0x04, 0x00, 0x00, 0x93, 0xa8, 0x33,
0x04, 0x00, 0x00, 0xa8, 0xc0, 0x36, 0x04, 0x0a,
0xb8, 0x09, 0x01, 0x03, 0x04, 0x0a, 0xed, 0x48,
0x01, 0x0f, 0x0d, 0x66, 0x69, 0x2e, 0x69, 0x6e,
0x74, 0x65, 0x6c, 0x2e, 0x63, 0x6f, 0x6d, 0x00,
0x06, 0x0c, 0x0a, 0xf8, 0x02, 0x01, 0xa3, 0x21,
0xfd, 0x44, 0x0a, 0xb8, 0x09, 0x01, 0x77, 0x3d,
0x02, 0x66, 0x69, 0x05, 0x69, 0x6e, 0x74, 0x65,
0x6c, 0x03, 0x63, 0x6f, 0x6d, 0x00, 0x03, 0x67,
0x65, 0x72, 0x04, 0x63, 0x6f, 0x72, 0x70, 0x05,
0x69, 0x6e, 0x74, 0x65, 0x6c, 0x03, 0x63, 0x6f,
0x6d, 0x00, 0x04, 0x63, 0x6f, 0x72, 0x70, 0x05,
0x69, 0x6e, 0x74, 0x65, 0x6c, 0x03, 0x63, 0x6f,
0x6d, 0x00, 0x05, 0x69, 0x6e, 0x74, 0x65, 0x6c,
0x03, 0x63, 0x6f, 0x6d, 0x00, 0x2c, 0x08, 0xa3,
0x21, 0x07, 0x56, 0x8f, 0xb6, 0xfa, 0x69, 0xff
};

/* Sample DHCPv4 ACK */
static const unsigned char ack[382] = {
0x02, 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x0a, 0xed, 0x48, 0x9e, 0x00, 0x00, 0x00, 0x00,
0x0a, 0xed, 0x48, 0x03, 0x00, 0x00, 0x5E, 0x00,
0x53, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x63, 0x82, 0x53, 0x63,
0x35, 0x01, 0x05, 0x3a, 0x04, 0x00, 0x00, 0x54,
0x60, 0x3b, 0x04, 0x00, 0x00, 0x93, 0xa8, 0x33,
0x04, 0x00, 0x00, 0xa8, 0xc0, 0x36, 0x04, 0x0a,
0xb8, 0x09, 0x01, 0x01, 0x04, 0xff, 0xff, 0xff,
0x00, 0x03, 0x04, 0x0a, 0xed, 0x48, 0x01, 0x0f,
0x0d, 0x66, 0x69, 0x2e, 0x69, 0x6e, 0x74, 0x65,
0x6c, 0x2e, 0x63, 0x6f, 0x6d, 0x00, 0x06, 0x0c,
0x0a, 0xf8, 0x02, 0x01, 0xa3, 0x21, 0xfd, 0x44,
0x0a, 0xb8, 0x09, 0x01, 0x77, 0x3d, 0x02, 0x66,
0x69, 0x05, 0x69, 0x6e, 0x74, 0x65, 0x6c, 0x03,
0x63, 0x6f, 0x6d, 0x00, 0x03, 0x67, 0x65, 0x72,
0x04, 0x63, 0x6f, 0x72, 0x70, 0x05, 0x69, 0x6e,
0x74, 0x65, 0x6c, 0x03, 0x63, 0x6f, 0x6d, 0x00,
0x04, 0x63, 0x6f, 0x72, 0x70, 0x05, 0x69, 0x6e,
0x74, 0x65, 0x6c, 0x03, 0x63, 0x6f, 0x6d, 0x00,
0x05, 0x69, 0x6e, 0x74, 0x65, 0x6c, 0x03, 0x63,
0x6f, 0x6d, 0x00, 0x2c, 0x08, 0xa3, 0x21, 0x07,
0x56, 0x8f, 0xb6, 0xfa, 0x69, 0xff
};

static const struct in_addr server_addr = { { { 192, 0, 2, 1 } } };
static const struct in_addr client_addr = { { { 255, 255, 255, 255 } } };

#define SERVER_PORT	67
#define CLIENT_PORT	68
#define MSG_TYPE	53
#define DISCOVER	1
#define REQUEST		3

struct dhcp_msg {
	u32_t xid;
	u8_t type;
};

static struct k_sem test_lock;

#define WAIT_TIME K_SECONDS(CONFIG_NET_DHCPV4_INITIAL_DELAY_MAX + 1)

struct net_dhcpv4_context {
	u8_t mac_addr[sizeof(struct net_eth_addr)];
	struct net_linkaddr ll_addr;
};

static int net_dhcpv4_dev_init(struct device *dev)
{
	struct net_dhcpv4_context *net_dhcpv4_context = dev->driver_data;

	net_dhcpv4_context = net_dhcpv4_context;

	return 0;
}

static u8_t *net_dhcpv4_get_mac(struct device *dev)
{
	struct net_dhcpv4_context *context = dev->driver_data;

	if (context->mac_addr[2] == 0x00) {
		/* 00-00-5E-00-53-xx Documentation RFC 7042 */
		context->mac_addr[0] = 0x00;
		context->mac_addr[1] = 0x00;
		context->mac_addr[2] = 0x5E;
		context->mac_addr[3] = 0x00;
		context->mac_addr[4] = 0x53;
		context->mac_addr[5] = 0x01;
	}

	return context->mac_addr;
}

static void net_dhcpv4_iface_init(struct net_if *iface)
{
	u8_t *mac = net_dhcpv4_get_mac(net_if_get_device(iface));

	net_if_set_link_addr(iface, mac, 6, NET_LINK_ETHERNET);
}

struct net_pkt *prepare_dhcp_offer(struct net_if *iface, u32_t xid)
{
	struct net_pkt *pkt;

	pkt = net_pkt_alloc_with_buffer(iface, sizeof(offer), AF_INET,
					IPPROTO_UDP, K_FOREVER);
	if (!pkt) {
		return NULL;
	}

	net_pkt_set_ipv4_ttl(pkt, 0xFF);

	if (net_ipv4_create_new(pkt, &server_addr, &client_addr) ||
	    net_udp_create(pkt, htons(SERVER_PORT), htons(CLIENT_PORT))) {
		goto fail;
	}

	if (net_pkt_write_new(pkt, offer, 4)) {
		goto fail;
	}

	/* Update xid from the client request */
	if (net_pkt_write_be32_new(pkt, xid)) {
		goto fail;
	}

	if (net_pkt_write_new(pkt, offer + 8, sizeof(offer) - 8)) {
		goto fail;
	}

	net_pkt_cursor_init(pkt);

	net_ipv4_finalize(pkt, IPPROTO_UDP);

	return pkt;

fail:
	net_pkt_unref(pkt);
	return NULL;
}

struct net_pkt *prepare_dhcp_ack(struct net_if *iface, u32_t xid)
{
	struct net_pkt *pkt;

	pkt = net_pkt_alloc_with_buffer(iface, sizeof(offer), AF_INET,
					IPPROTO_UDP, K_FOREVER);
	if (!pkt) {
		return NULL;
	}

	net_pkt_set_ipv4_ttl(pkt, 0xFF);

	if (net_ipv4_create_new(pkt, &server_addr, &client_addr) ||
	    net_udp_create(pkt, htons(SERVER_PORT), htons(CLIENT_PORT))) {
		goto fail;
	}

	if (net_pkt_write_new(pkt, ack, 4)) {
		goto fail;
	}

	/* Update xid from the client request */
	if (net_pkt_write_be32_new(pkt, xid)) {
		goto fail;
	}

	if (net_pkt_write_new(pkt, ack + 8, sizeof(ack) - 8)) {
		goto fail;
	}

	net_pkt_cursor_init(pkt);

	net_ipv4_finalize(pkt, IPPROTO_UDP);

	return pkt;

fail:
	net_pkt_unref(pkt);
	return NULL;
}

static int parse_dhcp_message(struct net_pkt *pkt, struct dhcp_msg *msg)
{
	/* Skip IPv4 and UDP headers */
	if (net_pkt_skip(pkt, NET_IPV4UDPH_LEN)) {
		return 0;
	}

	/* Skip DHCPv4 headers (size of op, htype, hlen, hops) */
	if (net_pkt_skip(pkt, 4)) {
		return 0;
	}

	if (net_pkt_read_be32_new(pkt, &msg->xid)) {
		return 0;
	}

	/* Skip DHCPv4 Options (size of op, htype, ... cookie) */
	if (net_pkt_skip(pkt, 36 + 64 + 128 + 4)) {
		return 0;
	}

	while (1) {
		u8_t length = 0U;
		u8_t type;

		if (net_pkt_read_u8_new(pkt, &type)) {
			return 0;
		}

		if (type == MSG_TYPE) {
			if (net_pkt_skip(pkt, 1)) {
				return 0;
			}

			if (net_pkt_read_u8_new(pkt, &msg->type)) {
				return 0;
			}

			return 1;
		}

		if (net_pkt_read_u8_new(pkt, &length)) {
			return 0;
		}

		if (length && net_pkt_skip(pkt, length)) {
			return 0;
		}
	}

	return 0;
}

static int tester_send(struct device *dev, struct net_pkt *pkt)
{
	struct net_pkt *rpkt;
	struct dhcp_msg msg;

	(void)memset(&msg, 0, sizeof(msg));

	if (!pkt->frags) {
		TC_PRINT("No data to send!\n");

		return -ENODATA;
	}

	parse_dhcp_message(pkt, &msg);

	if (msg.type == DISCOVER) {
		/* Reply with DHCPv4 offer message */
		rpkt = prepare_dhcp_offer(net_pkt_iface(pkt), msg.xid);
		if (!rpkt) {
			return -EINVAL;
		}
	} else if (msg.type == REQUEST) {
		/* Reply with DHCPv4 ACK message */
		rpkt = prepare_dhcp_ack(net_pkt_iface(pkt), msg.xid);
		if (!rpkt) {
			return -EINVAL;
		}
	} else {
		/* Invalid message type received */
		return -EINVAL;
	}

	if (net_recv_data(net_pkt_iface(rpkt), rpkt)) {
		net_pkt_unref(rpkt);

		return -EINVAL;
	}

	return 0;
}

struct net_dhcpv4_context net_dhcpv4_context_data;

static struct dummy_api net_dhcpv4_if_api = {
	.iface_api.init = net_dhcpv4_iface_init,
	.send = tester_send,
};

NET_DEVICE_INIT(net_dhcpv4_test, "net_dhcpv4_test",
		net_dhcpv4_dev_init, &net_dhcpv4_context_data, NULL,
		CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
		&net_dhcpv4_if_api, DUMMY_L2,
		NET_L2_GET_CTX_TYPE(DUMMY_L2), 127);

static struct net_mgmt_event_callback rx_cb;

static void receiver_cb(struct net_mgmt_event_callback *cb,
			u32_t nm_event, struct net_if *iface)
{
	if (nm_event != NET_EVENT_IPV4_ADDR_ADD) {
		/* Spurious callback. */
		return;
	}

	k_sem_give(&test_lock);
}

void test_dhcp(void)
{
	struct net_if *iface;

	k_sem_init(&test_lock, 0, UINT_MAX);

	net_mgmt_init_event_callback(&rx_cb, receiver_cb,
				     NET_EVENT_IPV4_ADDR_ADD);

	net_mgmt_add_event_callback(&rx_cb);

	iface = net_if_get_default();
	if (!iface) {
		zassert_true(false, "Interface not available");
	}

	net_dhcpv4_start(iface);

	if (k_sem_take(&test_lock, WAIT_TIME)) {
		zassert_true(false, "Timeout while waiting");
	}
}

/**test case main entry */
void test_main(void)
{
	ztest_test_suite(test_dhcpv4,
			ztest_unit_test(test_dhcp));
	ztest_run_test_suite(test_dhcpv4);
}
