/**
 * @file smp_null.c
 * Security Manager Protocol stub
 */

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
#include <errno.h>
#include <atomic.h>
#include <misc/util.h>

#include <bluetooth/log.h>
#include <bluetooth/bluetooth.h>

#include "hci_core.h"
#include "conn_internal.h"
#include "l2cap_internal.h"
#include "smp.h"

static struct bt_l2cap_chan bt_smp_pool[CONFIG_BLUETOOTH_MAX_CONN];

int bt_smp_sign_verify(struct bt_conn *conn, struct net_buf *buf)
{
	return -ENOTSUP;
}

static void bt_smp_recv(struct bt_l2cap_chan *chan, struct net_buf *buf)
{
	struct bt_conn *conn = chan->conn;
	struct bt_smp_pairing_fail *rsp;
	struct bt_smp_hdr *hdr;

	/* If a device does not support pairing then it shall respond with
	 * a Pairing Failed command with the reason set to “Pairing Not
	 * Supported” when any command is received.
	 * Core Specification Vol. 3, Part H, 3.3
	 */

	buf = bt_l2cap_create_pdu(conn);
	if (!buf) {
		return;
	}

	hdr = net_buf_add(buf, sizeof(*hdr));
	hdr->code = BT_SMP_CMD_PAIRING_FAIL;

	rsp = net_buf_add(buf, sizeof(*rsp));
	rsp->reason = BT_SMP_ERR_PAIRING_NOTSUPP;

	bt_l2cap_send(conn, BT_L2CAP_CID_SMP, buf);
}

static int bt_smp_accept(struct bt_conn *conn, struct bt_l2cap_chan **chan)
{
	int i;
	static struct bt_l2cap_chan_ops ops = {
		.recv = bt_smp_recv,
	};

	BT_DBG("conn %p handle %u\n", conn, conn->handle);

	for (i = 0; i < ARRAY_SIZE(bt_smp_pool); i++) {
		struct bt_l2cap_chan *smp = &bt_smp_pool[i];

		if (smp->conn) {
			continue;
		}

		smp->ops = &ops;

		*chan = smp;

		return 0;
	}

	BT_ERR("No available SMP context for conn %p\n", conn);

	return -ENOMEM;
}

int bt_smp_init(void)
{
	static struct bt_l2cap_fixed_chan chan = {
		.cid	= BT_L2CAP_CID_SMP,
		.accept	= bt_smp_accept,
	};

	bt_l2cap_fixed_chan_register(&chan);

	return 0;
}
