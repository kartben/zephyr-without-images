/* main.c - Application main entry point */

/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sections.h>

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <device.h>
#include <init.h>
#include <net/net_core.h>
#include <net/nbuf.h>
#include <net/net_ip.h>
#include <net/dhcpv4.h>
#include <net/ethernet.h>
#include <net/net_mgmt.h>

#include <tc_util.h>

#define NET_LOG_ENABLED 1
#include "net_private.h"

/* Sample DHCP offer (382 bytes) */
static const unsigned char offer[382] = {
0x02, 0x01, 0x06, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x0a, 0xed, 0x48, 0x9e, 0x0a, 0xb8,
0x09, 0x01, 0x0a, 0xed, 0x48, 0x02, 0x10, 0x00,
0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
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
0x0a, 0xed, 0x48, 0x03, 0x10, 0x00, 0x00, 0x00,
0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
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

static const struct net_eth_addr src_addr = {
	{ 0x10, 0x00, 0x00, 0x00, 0x00, 0x01 } };
static const struct net_eth_addr dst_addr = {
	{ 0x10, 0x00, 0x00, 0x00, 0x00, 0x02 } };
static const struct in_addr server_addr = { { { 192, 0, 2, 1 } } };
static const struct in_addr client_addr = { { { 255, 255, 255, 255 } } };

#define SERVER_PORT	67
#define CLIENT_PORT	68
#define MSG_TYPE	53
#define DISCOVER	1
#define REQUEST		3

struct dhcp_msg {
	uint32_t xid;
	uint8_t type;
};

static void test_result(bool pass)
{
	if (pass) {
		TC_END(PASS, "passed\n");
		TC_END_REPORT(TC_PASS);
	} else {
		TC_END(FAIL, "failed\n");
		TC_END_REPORT(TC_PASS);
	}
}

struct net_dhcpv4_context {
	uint8_t mac_addr[sizeof(struct net_eth_addr)];
	struct net_linkaddr ll_addr;
};

static int net_dhcpv4_dev_init(struct device *dev)
{
	struct net_dhcpv4_context *net_dhcpv4_context = dev->driver_data;

	net_dhcpv4_context = net_dhcpv4_context;

	return 0;
}

static uint8_t *net_dhcpv4_get_mac(struct device *dev)
{
	struct net_dhcpv4_context *context = dev->driver_data;

	if (context->mac_addr[0] == 0x00) {
		/* 10-00-00-00-00 to 10-00-00-00-FF
		 * Documentation RFC7042
		 */
		context->mac_addr[0] = 0x10;
		context->mac_addr[1] = 0x00;
		context->mac_addr[2] = 0x00;
		context->mac_addr[3] = 0x00;
		context->mac_addr[4] = 0x00;
		context->mac_addr[5] = 0x01;
	}

	return context->mac_addr;
}

static void net_dhcpv4_iface_init(struct net_if *iface)
{
	uint8_t *mac = net_dhcpv4_get_mac(net_if_get_device(iface));

	net_if_set_link_addr(iface, mac, 6, NET_LINK_ETHERNET);
}

static struct net_buf *nbuf_get_data(struct net_if *iface)
{
	struct net_buf *buf;
	struct net_eth_hdr *hdr;

	buf = net_nbuf_get_reserve_rx_data(net_if_get_ll_reserve(iface, NULL),
					   K_FOREVER);
	if (!buf) {
		return NULL;
	}

	hdr = (struct net_eth_hdr *)net_nbuf_ll(buf);
	hdr->type = htons(NET_ETH_PTYPE_IP);

	net_ipaddr_copy(&hdr->dst, &src_addr);
	net_ipaddr_copy(&hdr->src, &dst_addr);

	return buf;
}

static void set_ipv4_header(struct net_buf *buf)
{
	struct net_ipv4_hdr *ipv4;
	uint16_t length;

	ipv4 = NET_IPV4_BUF(buf);

	ipv4->vhl = 0x45; /* IP version and header length */
	ipv4->tos = 0x00;

	length = sizeof(offer) + sizeof(struct net_ipv4_hdr) +
		 sizeof(struct net_udp_hdr);

	ipv4->len[1] = length;
	ipv4->len[0] = length >> 8;

	memset(ipv4->id, 0, 4); /* id and offset */

	ipv4->ttl = 0xFF;
	ipv4->proto = IPPROTO_UDP;

	net_ipaddr_copy(&ipv4->src, &server_addr);
	net_ipaddr_copy(&ipv4->dst, &client_addr);
}

static void set_udp_header(struct net_buf *buf)
{
	struct net_udp_hdr *udp;
	uint16_t length;

	udp = NET_UDP_BUF(buf);
	udp->src_port = htons(SERVER_PORT);
	udp->dst_port = htons(CLIENT_PORT);

	length = sizeof(offer) + sizeof(struct net_udp_hdr);
	udp->len = htons(length);
	udp->chksum = 0;
}

struct net_buf *prepare_dhcp_offer(struct net_if *iface, uint32_t xid)
{
	struct net_buf *buf, *frag;
	int bytes, remaining = sizeof(offer), pos = 0;
	uint16_t offset;

	buf = net_nbuf_get_reserve_rx(0, K_FOREVER);
	if (!buf) {
		return NULL;
	}

	frag = nbuf_get_data(iface);
	if (!frag) {
		net_nbuf_unref(buf);
		return NULL;
	}

	net_nbuf_set_iface(buf, iface);
	net_nbuf_set_ll_reserve(buf, net_buf_headroom(frag));
	net_nbuf_set_family(buf, AF_INET);
	net_nbuf_set_ip_hdr_len(buf, sizeof(struct net_ipv4_hdr));

	net_buf_frag_add(buf, frag);

	/* Place the IPv4 header */
	set_ipv4_header(buf);

	/* Place the UDP header */
	set_udp_header(buf);

	net_buf_add(frag, NET_IPV4UDPH_LEN);
	offset = NET_IPV4UDPH_LEN;

	while (remaining > 0) {
		int copy;

		bytes = net_buf_tailroom(frag);
		copy = remaining > bytes ? bytes : remaining;

		memcpy(frag->data + offset, &offer[pos], copy);

		net_buf_add(frag, copy);

		pos += bytes;
		remaining -= bytes;

		if (remaining > 0) {
			frag = nbuf_get_data(iface);
			if (!frag) {
				goto fail;
			}

			offset = 0;
			net_buf_frag_add(buf, frag);
		}
	}

	/* Now fixup the expect XID */
	frag = net_nbuf_write_be32(buf, buf->frags,
				   (sizeof(struct net_ipv4_hdr) +
				    sizeof(struct net_udp_hdr)) + 4,
				   &offset, xid);
	return buf;

fail:
	net_nbuf_unref(buf);
	return NULL;
}

struct net_buf *prepare_dhcp_ack(struct net_if *iface, uint32_t xid)
{
	struct net_buf *buf, *frag;
	int bytes, remaining = sizeof(ack), pos = 0;
	uint16_t offset;

	buf = net_nbuf_get_reserve_rx(0, K_FOREVER);
	if (!buf) {
		return NULL;
	}

	frag = nbuf_get_data(iface);
	if (!frag) {
		net_nbuf_unref(buf);
		return NULL;
	}

	net_nbuf_set_iface(buf, iface);
	net_nbuf_set_ll_reserve(buf, net_buf_headroom(frag));
	net_nbuf_set_family(buf, AF_INET);
	net_nbuf_set_ip_hdr_len(buf, sizeof(struct net_ipv4_hdr));

	net_buf_frag_add(buf, frag);

	/* Place the IPv4 header */
	set_ipv4_header(buf);

	/* Place the UDP header */
	set_udp_header(buf);

	net_buf_add(frag, NET_IPV4UDPH_LEN);
	offset = NET_IPV4UDPH_LEN;

	while (remaining > 0) {
		int copy;

		bytes = net_buf_tailroom(frag);
		copy = remaining > bytes ? bytes : remaining;

		memcpy(frag->data + offset, &ack[pos], copy);

		net_buf_add(frag, copy);

		pos += bytes;
		remaining -= bytes;

		if (remaining > 0) {
			frag = nbuf_get_data(iface);
			if (!frag) {
				goto fail;
			}

			offset = 0;
			net_buf_frag_add(buf, frag);
		}
	}

	/* Now fixup the expect XID */
	frag = net_nbuf_write_be32(buf, buf->frags,
				   (sizeof(struct net_ipv4_hdr) +
				    sizeof(struct net_udp_hdr)) + 4,
				   &offset, xid);
	return buf;

fail:
	net_nbuf_unref(buf);
	return NULL;
}

static int parse_dhcp_message(struct net_buf *buf, struct dhcp_msg *msg)
{
	struct net_buf *frag = buf->frags;
	uint8_t type;
	uint16_t offset;

	frag = net_nbuf_skip(frag, 0, &offset,
			   /* size of op, htype, hlen, hops */
			   (sizeof(struct net_ipv4_hdr) +
			    sizeof(struct net_udp_hdr)) + 4);
	if (!frag) {
		return 0;
	}

	frag = net_nbuf_read_be32(frag, offset, &offset, &msg->xid);
	if (!frag) {
		return 0;
	}

	frag = net_nbuf_skip(frag, offset, &offset,
			   /* size of op, htype ... cookie */
			   (36 + 64 + 128 + 4));
	if (!frag) {
		return 0;
	}

	while (frag) {
		uint8_t length;

		frag = net_nbuf_read_u8(frag, offset, &offset, &type);
		if (!frag) {
			return 0;
		}

		if (type == MSG_TYPE) {
			frag = net_nbuf_skip(frag, offset, &offset, 1);
			if (!frag) {
				return 0;
			}

			frag = net_nbuf_read_u8(frag, offset, &offset,
						&msg->type);
			if (!frag) {
				return 0;
			}

			return 1;
		}

		frag = net_nbuf_read_u8(frag, offset, &offset, &length);
		if (frag) {
			frag = net_nbuf_skip(frag, offset, &offset, length);
			if (!frag) {
				return 0;
			}
		}
	}

	return 0;
}

static int tester_send(struct net_if *iface, struct net_buf *buf)
{
	struct net_buf *rbuf;
	struct dhcp_msg msg;

	memset(&msg, 0, sizeof(msg));

	if (!buf->frags) {
		TC_PRINT("No data to send!\n");

		return -ENODATA;
	}

	parse_dhcp_message(buf, &msg);
	net_nbuf_unref(buf);

	if (msg.type == DISCOVER) {
		/* Reply with DHCPv4 offer message */
		rbuf = prepare_dhcp_offer(iface, msg.xid);
		if (!rbuf) {
			return -EINVAL;
		}
	} else if (msg.type == REQUEST) {
		/* Reply with DHCPv4 ACK message */
		rbuf = prepare_dhcp_ack(iface, msg.xid);
		if (!rbuf) {
			return -EINVAL;
		}

	} else {
		/* Invalid message type received */
		return -EINVAL;
	}

	if (net_recv_data(iface, rbuf)) {
		net_nbuf_unref(rbuf);

		return -EINVAL;
	}

	return NET_OK;
}

struct net_dhcpv4_context net_dhcpv4_context_data;

static struct net_if_api net_dhcpv4_if_api = {
	.init = net_dhcpv4_iface_init,
	.send = tester_send,
};

NET_DEVICE_INIT(net_dhcpv4_test, "net_dhcpv4_test",
		net_dhcpv4_dev_init, &net_dhcpv4_context_data, NULL,
		CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
		&net_dhcpv4_if_api, DUMMY_L2,
		NET_L2_GET_CTX_TYPE(DUMMY_L2), 127);

static struct net_mgmt_event_callback rx_cb;

static void receiver_cb(struct net_mgmt_event_callback *cb,
			uint32_t nm_event, struct net_if *iface)
{
	test_result(true);
}

void main_thread(void)
{
	struct net_if *iface;

	net_mgmt_init_event_callback(&rx_cb, receiver_cb,
				     NET_EVENT_IPV4_ADDR_ADD);

	net_mgmt_add_event_callback(&rx_cb);

	iface = net_if_get_default();
	if (!iface) {
		TC_PRINT("Interface not available n");
		return;
	}

	net_dhcpv4_start(iface);

	k_yield();
}

#define STACKSIZE 3000
char __noinit __stack thread_stack[STACKSIZE];

void main(void)
{
	k_thread_spawn(&thread_stack[0], STACKSIZE,
		       (k_thread_entry_t)main_thread, NULL, NULL, NULL,
		       K_PRIO_COOP(7), 0, 0);
}
