/*
 * Copyright (c) 2016 Nordic Semiconductor ASA
 * Copyright (c) 2015-2016 Intel Corporation
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

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <nanokernel.h>
#include <arch/cpu.h>
#include <misc/byteorder.h>
#include <misc/sys_log.h>
#include <misc/util.h>

#include <device.h>
#include <init.h>
#include <uart.h>

#include <net/buf.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/driver.h>
#include <bluetooth/buf.h>
#include <bluetooth/hci_raw.h>

static struct device *hci_uart_dev;

/* HCI command buffers */
#define CMD_BUF_SIZE (CONFIG_BLUETOOTH_HCI_SEND_RESERVE + \
		      sizeof(struct bt_hci_cmd_hdr) + \
		      CONFIG_BLUETOOTH_MAX_CMD_LEN)

static struct nano_fifo avail_cmd_tx;
static NET_BUF_POOL(tx_pool, CONFIG_BLUETOOTH_HCI_CMD_COUNT, CMD_BUF_SIZE,
		    &avail_cmd_tx, NULL, BT_BUF_USER_DATA_MIN);

#define BT_L2CAP_MTU 64
/** Data size needed for ACL buffers */
#define BT_BUF_ACL_SIZE (CONFIG_BLUETOOTH_HCI_RECV_RESERVE + \
			 sizeof(struct bt_hci_acl_hdr) + \
			 4 /* L2CAP header size */ + \
			 BT_L2CAP_MTU)

static struct nano_fifo avail_acl_tx;
static NET_BUF_POOL(acl_tx_pool, 2, BT_BUF_ACL_SIZE, &avail_acl_tx, NULL,
		    BT_BUF_USER_DATA_MIN);

#define H4_CMD          0x01
#define H4_ACL          0x02
#define H4_SCO          0x03
#define H4_EVT          0x04

/* Length of a discard/flush buffer.
 * This is sized to align with a BLE HCI packet:
 * 1 byte H:4 header + 32 bytes ACL/event data
 * Bigger values might overflow the stack since this is declared as a local
 * variable, smaller ones will force the caller to call into discard more
 * often.
 */
#define H4_DISCARD_LEN  33

static int h4_read(struct device *uart, uint8_t *buf,
		   size_t len, size_t min)
{
	int total = 0;

	while (len) {
		int rx;

		rx = uart_fifo_read(uart, buf, len);
		if (rx == 0) {
			SYS_LOG_DBG("Got zero bytes from UART");
			if (total < min) {
				continue;
			}
			break;
		}

		SYS_LOG_DBG("read %d remaining %d", rx, len - rx);
		len -= rx;
		total += rx;
		buf += rx;
	}

	return total;
}

static size_t h4_discard(struct device *uart, size_t len)
{
	uint8_t buf[H4_DISCARD_LEN];

	return uart_fifo_read(uart, buf, min(len, sizeof(buf)));
}

static struct net_buf *h4_cmd_recv(int *remaining)
{
	struct bt_hci_cmd_hdr hdr;
	struct net_buf *buf;

	/* We can ignore the return value since we pass len == min */
	h4_read(hci_uart_dev, (void *)&hdr, sizeof(hdr), sizeof(hdr));

	*remaining = hdr.param_len;

	buf = net_buf_get(&avail_cmd_tx, 0);
	if (buf) {
		bt_buf_set_type(buf, BT_BUF_CMD);
		memcpy(net_buf_add(buf, sizeof(hdr)), &hdr, sizeof(hdr));
	} else {
		SYS_LOG_ERR("No available command buffers!");
	}

	SYS_LOG_DBG("len %u", hdr.param_len);

	return buf;
}

static struct net_buf *h4_acl_recv(int *remaining)
{
	struct bt_hci_acl_hdr hdr;
	struct net_buf *buf;

	/* We can ignore the return value since we pass len == min */
	h4_read(hci_uart_dev, (void *)&hdr, sizeof(hdr), sizeof(hdr));

	buf = net_buf_get(&avail_acl_tx, 0);
	if (buf) {
		bt_buf_set_type(buf, BT_BUF_ACL_OUT);
		memcpy(net_buf_add(buf, sizeof(hdr)), &hdr, sizeof(hdr));
	} else {
		SYS_LOG_ERR("No available ACL buffers!");
	}

	*remaining = sys_le16_to_cpu(hdr.len);

	SYS_LOG_DBG("len %u", *remaining);

	return buf;
}

static void bt_uart_isr(struct device *unused)
{
	static struct net_buf *buf;
	static int remaining;

	ARG_UNUSED(unused);

	while (uart_irq_update(hci_uart_dev) &&
	       uart_irq_is_pending(hci_uart_dev)) {
		int read;

		if (!uart_irq_rx_ready(hci_uart_dev)) {
			if (uart_irq_tx_ready(hci_uart_dev)) {
				SYS_LOG_DBG("transmit ready");
			} else {
				SYS_LOG_DBG("spurious interrupt");
			}
			continue;
		}

		/* Beginning of a new packet */
		if (!remaining) {
			uint8_t type;

			/* Get packet type */
			read = h4_read(hci_uart_dev, &type, sizeof(type), 0);
			if (read != sizeof(type)) {
				SYS_LOG_WRN("Unable to read H4 packet type");
				continue;
			}

			switch (type) {
			case H4_CMD:
				buf = h4_cmd_recv(&remaining);
				break;
			case H4_ACL:
				buf = h4_acl_recv(&remaining);
				break;
			default:
				SYS_LOG_ERR("Unknown H4 type %u", type);
				return;
			}

			SYS_LOG_DBG("need to get %u bytes", remaining);

			if (buf && remaining > net_buf_tailroom(buf)) {
				SYS_LOG_ERR("Not enough space in buffer");
				net_buf_unref(buf);
				buf = NULL;
			}
		}

		if (!buf) {
			read = h4_discard(hci_uart_dev, remaining);
			SYS_LOG_WRN("Discarded %d bytes", read);
			remaining -= read;
			continue;
		}

		read = h4_read(hci_uart_dev, net_buf_tail(buf), remaining, 0);

		buf->len += read;
		remaining -= read;

		SYS_LOG_DBG("received %d bytes", read);

		if (!remaining) {
			SYS_LOG_DBG("full packet received");

			/* Pass buffer to the stack */
			bt_send(buf);
			buf = NULL;
		}
	}
}

static int h4_send(struct net_buf *buf)
{
	SYS_LOG_DBG("buf %p type %u len %u", buf, bt_buf_get_type(buf),
		    buf->len);

	switch (bt_buf_get_type(buf)) {
	case BT_BUF_ACL_IN:
		uart_poll_out(hci_uart_dev, H4_ACL);
		break;
	case BT_BUF_EVT:
		uart_poll_out(hci_uart_dev, H4_EVT);
		break;
	default:
		SYS_LOG_ERR("Unknown type %u", bt_buf_get_type(buf));
		net_buf_unref(buf);
		return -EINVAL;
	}

	while (buf->len) {
		uart_poll_out(hci_uart_dev, net_buf_pull_u8(buf));
	}

	net_buf_unref(buf);

	return 0;
}


static int hci_uart_init(struct device *unused)
{
	SYS_LOG_DBG("");

	hci_uart_dev =
		device_get_binding(CONFIG_BLUETOOTH_UART_TO_HOST_DEV_NAME);
	if (!hci_uart_dev) {
		return -EINVAL;
	}

	uart_irq_rx_disable(hci_uart_dev);
	uart_irq_tx_disable(hci_uart_dev);

	uart_irq_callback_set(hci_uart_dev, bt_uart_isr);

	uart_irq_rx_enable(hci_uart_dev);

	return 0;
}

DEVICE_INIT(hci_uart, "hci_uart", &hci_uart_init, NULL, NULL,
	    APPLICATION, CONFIG_KERNEL_INIT_PRIORITY_DEVICE);

void main(void)
{
	/* incoming events and data from the controller */
	static struct nano_fifo rx_queue;
	int err;

	SYS_LOG_DBG("Start");

	/* Initialize the buffer pools */
	net_buf_pool_init(tx_pool);
	net_buf_pool_init(acl_tx_pool);
	nano_fifo_init(&rx_queue);

	bt_enable_raw(&rx_queue);

	while (1) {
		struct net_buf *buf;

		buf = net_buf_get_timeout(&rx_queue, 0, TICKS_UNLIMITED);
		err = h4_send(buf);
		if (err) {
			SYS_LOG_ERR("Failed to send");
		}
	}
}
