/* buf.c - Bluetooth buffer management */

/*
 * Copyright (c) 2015 Intel Corporation
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

#include <nanokernel.h>
#include <toolchain.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <atomic.h>
#include <misc/byteorder.h>

#include <bluetooth/log.h>
#include <bluetooth/hci.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/buf.h>

#include "hci_core.h"

#if !defined(CONFIG_BLUETOOTH_DEBUG_BUF)
#undef BT_DBG
#define BT_DBG(fmt, ...)
#endif

/* Total number of all types of buffers */
#if defined(CONFIG_BLUETOOTH_CONN)
#define NUM_BUFS		22
#else
#define NUM_BUFS		8
#endif /* CONFIG_BLUETOOTH_CONN */

static struct bt_buf		buffers[NUM_BUFS];

/* Available (free) buffers queues */
static struct nano_fifo		avail_hci;

#if defined(CONFIG_BLUETOOTH_CONN)
static struct nano_fifo		avail_acl_in;
static struct nano_fifo		avail_acl_out;
#endif /* CONFIG_BLUETOOTH_CONN */

static struct nano_fifo *get_avail(enum bt_buf_type type)
{
	switch (type) {
	case BT_CMD:
	case BT_EVT:
		return &avail_hci;
#if defined(CONFIG_BLUETOOTH_CONN)
	case BT_ACL_IN:
		return &avail_acl_in;
	case BT_ACL_OUT:
		return &avail_acl_out;
#endif /* CONFIG_BLUETOOTH_CONN */
	default:
		return NULL;
	}
}

struct bt_buf *bt_buf_get(enum bt_buf_type type, size_t reserve_head)
{
	struct nano_fifo *avail;
	struct bt_buf *buf;

	BT_DBG("type %d reserve %u\n", type, reserve_head);

	avail = get_avail(type);
	if (!avail) {
		return NULL;
	}

	buf = nano_fifo_get(avail);
	if (!buf) {
		if (sys_execution_context_type_get() == NANO_CTX_ISR) {
			BT_ERR("Failed to get free buffer\n");
			return NULL;
		}

		BT_WARN("Low on buffers. Waiting (type %d)\n", type);
		buf = nano_fifo_get_wait(avail);
	}

	memset(buf, 0, sizeof(*buf));

	buf->ref  = 1;
	buf->type = type;
	buf->data = buf->buf + reserve_head;

	BT_DBG("buf %p type %d reserve %u\n", buf, buf->type, reserve_head);

	return buf;
}

#if defined(CONFIG_BLUETOOTH_CONN)
static void report_completed_packet(struct bt_buf *buf)
{

	struct bt_hci_cp_host_num_completed_packets *cp;
	struct bt_hci_handle_count *hc;
	uint16_t handle;

	handle = buf->acl.handle;
	nano_fifo_put(&avail_acl_in, buf);

	BT_DBG("Reporting completed packet for handle %u\n", handle);

	buf = bt_hci_cmd_create(BT_HCI_OP_HOST_NUM_COMPLETED_PACKETS,
				sizeof(*cp) + sizeof(*hc));
	if (!buf) {
		BT_ERR("Unable to allocate new HCI command\n");
		return;
	}

	cp = bt_buf_add(buf, sizeof(*cp));
	cp->num_handles = sys_cpu_to_le16(1);

	hc = bt_buf_add(buf, sizeof(*hc));
	hc->handle = sys_cpu_to_le16(handle);
	hc->count  = sys_cpu_to_le16(1);

	bt_hci_cmd_send(BT_HCI_OP_HOST_NUM_COMPLETED_PACKETS, buf);
}
#endif /* CONFIG_BLUETOOTH_CONN */

void bt_buf_put(struct bt_buf *buf)
{
	struct nano_fifo *avail = get_avail(buf->type);

	BT_DBG("buf %p ref %u type %d\n", buf, buf->ref, buf->type);

	if (--buf->ref) {
		return;
	}

#if defined(CONFIG_BLUETOOTH_CONN)
	if (avail == &avail_acl_in) {
		report_completed_packet(buf);
		return;
	}
#endif /* CONFIG_BLUETOOTH_CONN */

	/* Even if connection support is disabled avail shall always be not
	 * null. It is required to first get bt_buf with specific type to be
	 * able to put it. If connection support is disabled get returns NULL.
	 */
	BT_ASSERT(avail);

	nano_fifo_put(avail, buf);
}

struct bt_buf *bt_buf_hold(struct bt_buf *buf)
{
	BT_DBG("buf %p (old) ref %u type %d\n", buf, buf->ref, buf->type);
	buf->ref++;
	return buf;
}

struct bt_buf *bt_buf_clone(struct bt_buf *buf)
{
	struct bt_buf *clone;

	clone = bt_buf_get(buf->type, bt_buf_headroom(buf));
	if (!clone) {
		return NULL;
	}

	/* TODO: Add reference to the original buffer instead of copying it. */
	memcpy(bt_buf_add(clone, buf->len), buf->data, buf->len);

	return clone;
}

void *bt_buf_add(struct bt_buf *buf, size_t len)
{
	uint8_t *tail = bt_buf_tail(buf);

	BT_DBG("buf %p len %u\n", buf, len);

	BT_ASSERT(bt_buf_tailroom(buf) >= len);

	buf->len += len;
	return tail;
}

void bt_buf_add_le16(struct bt_buf *buf, uint16_t value)
{
	BT_DBG("buf %p value %u\n", buf, value);

	value = sys_cpu_to_le16(value);
	memcpy(bt_buf_add(buf, sizeof(value)), &value, sizeof(value));
}

void *bt_buf_push(struct bt_buf *buf, size_t len)
{
	BT_DBG("buf %p len %u\n", buf, len);

	BT_ASSERT(bt_buf_headroom(buf) >= len);

	buf->data -= len;
	buf->len += len;
	return buf->data;
}

void *bt_buf_pull(struct bt_buf *buf, size_t len)
{
	BT_DBG("buf %p len %u\n", buf, len);

	BT_ASSERT(buf->len >= len);

	buf->len -= len;
	return buf->data += len;
}

uint16_t bt_buf_pull_le16(struct bt_buf *buf)
{
	uint16_t value;

	value = UNALIGNED_GET((uint16_t *)buf->data);
	bt_buf_pull(buf, sizeof(value));

	return sys_le16_to_cpu(value);
}

size_t bt_buf_headroom(struct bt_buf *buf)
{
	return buf->data - buf->buf;
}

size_t bt_buf_tailroom(struct bt_buf *buf)
{
	return BT_BUF_MAX_DATA - bt_buf_headroom(buf) - buf->len;
}

int bt_buf_init(int acl_in, int acl_out)
{
	int i = 0;

	/* Check that we have enough buffers configured */
	if (acl_out + acl_in >= NUM_BUFS - 2) {
		BT_ERR("Too many ACL buffers requested\n");
		return -EINVAL;
	}

	BT_DBG("Available bufs: ACL in: %d, ACL out: %d, cmds/evts: %d\n",
	       acl_in, acl_out, NUM_BUFS - (acl_in + acl_out));

#if defined(CONFIG_BLUETOOTH_CONN)
	nano_fifo_init(&avail_acl_in);
	for (; acl_in > 0; i++, acl_in--) {
		nano_fifo_put(&avail_acl_in, &buffers[i]);
	}

	nano_fifo_init(&avail_acl_out);
	for (; acl_out > 0; i++, acl_out--) {
		nano_fifo_put(&avail_acl_out, &buffers[i]);
	}
#endif /* CONFIG_BLUETOOTH_CONN */

	nano_fifo_init(&avail_hci);
	for (; i < NUM_BUFS; i++) {
		nano_fifo_put(&avail_hci, &buffers[i]);
	}

	BT_DBG("%u buffers * %u bytes = %u bytes\n", NUM_BUFS,
	       sizeof(buffers[0]), sizeof(buffers));

	return 0;
}
