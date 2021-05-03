/** @file
 * @brief Bluetooth shell module
 *
 * Provide some Bluetooth shell commands that can be useful to applications.
 */

/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>
#include <zephyr/types.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/byteorder.h>
#include <zephyr.h>

#include <settings/settings.h>

#include <bluetooth/hci.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/conn.h>
#include <bluetooth/l2cap.h>
#include <bluetooth/rfcomm.h>
#include <bluetooth/sdp.h>

#include <shell/shell.h>

#include "bt.h"

#define CREDITS			10
#define DATA_MTU		(23 * CREDITS)

#define L2CAP_POLICY_NONE		0x00
#define L2CAP_POLICY_WHITELIST		0x01
#define L2CAP_POLICY_16BYTE_KEY		0x02

NET_BUF_POOL_FIXED_DEFINE(data_tx_pool, 1, DATA_MTU, NULL);
NET_BUF_POOL_FIXED_DEFINE(data_rx_pool, 1, DATA_MTU, NULL);

static uint8_t l2cap_policy;
static struct bt_conn *l2cap_whitelist[CONFIG_BT_MAX_CONN];

static uint32_t l2cap_rate;
static uint32_t l2cap_recv_delay_ms;
static K_FIFO_DEFINE(l2cap_recv_fifo);
struct l2ch {
	struct k_work_delayable recv_work;
	struct bt_l2cap_le_chan ch;
};
#define L2CH_CHAN(_chan) CONTAINER_OF(_chan, struct l2ch, ch.chan)
#define L2CH_WORK(_work) CONTAINER_OF(_work, struct l2ch, recv_work)
#define L2CAP_CHAN(_chan) _chan->ch.chan

static bool metrics;

static int l2cap_recv_metrics(struct bt_l2cap_chan *chan, struct net_buf *buf)
{
	static uint32_t len;
	static uint32_t cycle_stamp;
	uint32_t delta;

	delta = k_cycle_get_32() - cycle_stamp;
	delta = (uint32_t)k_cyc_to_ns_floor64(delta);

	/* if last data rx-ed was greater than 1 second in the past,
	 * reset the metrics.
	 */
	if (delta > 1000000000) {
		len = 0U;
		l2cap_rate = 0U;
		cycle_stamp = k_cycle_get_32();
	} else {
		len += buf->len;
		l2cap_rate = ((uint64_t)len << 3) * 1000000000U / delta;
	}

	return 0;
}

static void l2cap_recv_cb(struct k_work *work)
{
	struct l2ch *c = L2CH_WORK(work);
	struct net_buf *buf;

	while ((buf = net_buf_get(&l2cap_recv_fifo, K_NO_WAIT))) {
		shell_print(ctx_shell, "Confirming reception");
		bt_l2cap_chan_recv_complete(&c->ch.chan, buf);
	}
}

static int l2cap_recv(struct bt_l2cap_chan *chan, struct net_buf *buf)
{
	struct l2ch *l2ch = L2CH_CHAN(chan);

	if (metrics) {
		return l2cap_recv_metrics(chan, buf);
	}

	shell_print(ctx_shell, "Incoming data channel %p len %u", chan,
		    buf->len);

	if (buf->len) {
		shell_hexdump(ctx_shell, buf->data, buf->len);
	}

	if (l2cap_recv_delay_ms > 0) {
		/* Submit work only if queue is empty */
		if (k_fifo_is_empty(&l2cap_recv_fifo)) {
			shell_print(ctx_shell, "Delaying response in %u ms...",
				    l2cap_recv_delay_ms);
		}

		net_buf_put(&l2cap_recv_fifo, buf);
		k_work_schedule(&l2ch->recv_work, K_MSEC(l2cap_recv_delay_ms));

		return -EINPROGRESS;
	}

	return 0;
}

static void l2cap_sent(struct bt_l2cap_chan *chan)
{
	shell_print(ctx_shell, "Outgoing data channel %p transmitted", chan);
}

static void l2cap_status(struct bt_l2cap_chan *chan, atomic_t *status)
{
	shell_print(ctx_shell, "Channel %p status %u", chan, status);
}

static void l2cap_connected(struct bt_l2cap_chan *chan)
{
	struct l2ch *c = L2CH_CHAN(chan);

	k_work_init_delayable(&c->recv_work, l2cap_recv_cb);

	shell_print(ctx_shell, "Channel %p connected", chan);
}

static void l2cap_disconnected(struct bt_l2cap_chan *chan)
{
	shell_print(ctx_shell, "Channel %p disconnected", chan);
}

static struct net_buf *l2cap_alloc_buf(struct bt_l2cap_chan *chan)
{
	/* print if metrics is disabled */
	if (!metrics) {
		shell_print(ctx_shell, "Channel %p requires buffer", chan);
	}

	return net_buf_alloc(&data_rx_pool, K_FOREVER);
}

static const struct bt_l2cap_chan_ops l2cap_ops = {
	.alloc_buf	= l2cap_alloc_buf,
	.recv		= l2cap_recv,
	.sent		= l2cap_sent,
	.status		= l2cap_status,
	.connected	= l2cap_connected,
	.disconnected	= l2cap_disconnected,
};

static struct l2ch l2ch_chan = {
	.ch.chan.ops	= &l2cap_ops,
	.ch.rx.mtu	= DATA_MTU,
};

static void l2cap_whitelist_remove(struct bt_conn *conn, uint8_t reason)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(l2cap_whitelist); i++) {
		if (l2cap_whitelist[i] == conn) {
			bt_conn_unref(l2cap_whitelist[i]);
			l2cap_whitelist[i] = NULL;
		}
	}
}

static struct bt_conn_cb l2cap_conn_callbacks = {
	.disconnected = l2cap_whitelist_remove,
};

static int l2cap_accept_policy(struct bt_conn *conn)
{
	int i;

	if (l2cap_policy == L2CAP_POLICY_16BYTE_KEY) {
		uint8_t enc_key_size = bt_conn_enc_key_size(conn);

		if (enc_key_size && enc_key_size < BT_ENC_KEY_SIZE_MAX) {
			return -EPERM;
		}
	} else if (l2cap_policy == L2CAP_POLICY_WHITELIST) {
		for (i = 0; i < ARRAY_SIZE(l2cap_whitelist); i++) {
			if (l2cap_whitelist[i] == conn) {
				return 0;
			}
		}

		return -EACCES;
	}

	return 0;
}

static int l2cap_accept(struct bt_conn *conn, struct bt_l2cap_chan **chan)
{
	int err;

	shell_print(ctx_shell, "Incoming conn %p", conn);

	err = l2cap_accept_policy(conn);
	if (err < 0) {
		return err;
	}

	if (l2ch_chan.ch.chan.conn) {
		shell_print(ctx_shell, "No channels available");
		return -ENOMEM;
	}

	*chan = &l2ch_chan.ch.chan;

	return 0;
}

static struct bt_l2cap_server server = {
	.accept		= l2cap_accept,
};

static int cmd_register(const struct shell *shell, size_t argc, char *argv[])
{
	const char *policy;

	if (server.psm) {
		shell_error(shell, "Already registered");
		return -ENOEXEC;
	}

	server.psm = strtoul(argv[1], NULL, 16);

	if (argc > 2) {
		server.sec_level = strtoul(argv[2], NULL, 10);
	}

	if (argc > 3) {
		policy = argv[3];

		if (!strcmp(policy, "whitelist")) {
			l2cap_policy = L2CAP_POLICY_WHITELIST;
		} else if (!strcmp(policy, "16byte_key")) {
			l2cap_policy = L2CAP_POLICY_16BYTE_KEY;
		} else {
			return -EINVAL;
		}
	}

	if (bt_l2cap_server_register(&server) < 0) {
		shell_error(shell, "Unable to register psm");
		server.psm = 0U;
		return -ENOEXEC;
	} else {
		bt_conn_cb_register(&l2cap_conn_callbacks);

		shell_print(shell, "L2CAP psm %u sec_level %u registered",
			    server.psm, server.sec_level);
	}

	return 0;
}

static int cmd_connect(const struct shell *shell, size_t argc, char *argv[])
{
	uint16_t psm;
	int err;

	if (!default_conn) {
		shell_error(shell, "Not connected");
		return -ENOEXEC;
	}

	if (l2ch_chan.ch.chan.conn) {
		shell_error(shell, "Channel already in use");
		return -ENOEXEC;
	}

	psm = strtoul(argv[1], NULL, 16);

	if (argc > 2) {
		int sec;

		sec = *argv[2] - '0';

		l2ch_chan.ch.chan.required_sec_level = sec;
	}

	err = bt_l2cap_chan_connect(default_conn, &l2ch_chan.ch.chan, psm);
	if (err < 0) {
		shell_error(shell, "Unable to connect to psm %u (err %d)", psm,
			    err);
	} else {
		shell_print(shell, "L2CAP connection pending");
	}

	return err;
}

static int cmd_disconnect(const struct shell *shell, size_t argc, char *argv[])
{
	int err;

	err = bt_l2cap_chan_disconnect(&l2ch_chan.ch.chan);
	if (err) {
		shell_print(shell, "Unable to disconnect: %u", -err);
	}

	return err;
}

static int cmd_send(const struct shell *shell, size_t argc, char *argv[])
{
	static uint8_t buf_data[DATA_MTU] = { [0 ... (DATA_MTU - 1)] = 0xff };
	int ret, len = DATA_MTU, count = 1;
	struct net_buf *buf;

	if (argc > 1) {
		count = strtoul(argv[1], NULL, 10);
	}

	if (argc > 2) {
		len = strtoul(argv[2], NULL, 10);
		if (len > DATA_MTU) {
			shell_print(shell,
				    "Length exceeds TX MTU for the channel");
			return -ENOEXEC;
		}
	}

	len = MIN(l2ch_chan.ch.tx.mtu, len);

	while (count--) {
		buf = net_buf_alloc(&data_tx_pool, K_FOREVER);
		net_buf_reserve(buf, BT_L2CAP_CHAN_SEND_RESERVE);

		net_buf_add_mem(buf, buf_data, len);
		ret = bt_l2cap_chan_send(&l2ch_chan.ch.chan, buf);
		if (ret < 0) {
			shell_print(shell, "Unable to send: %d", -ret);
			net_buf_unref(buf);
			return -ENOEXEC;
		}
	}

	return 0;
}

static int cmd_recv(const struct shell *shell, size_t argc, char *argv[])
{
	if (argc > 1) {
		l2cap_recv_delay_ms = strtoul(argv[1], NULL, 10);
	} else {
		shell_print(shell, "l2cap receive delay: %u ms",
			    l2cap_recv_delay_ms);
	}

	return 0;
}

static int cmd_metrics(const struct shell *shell, size_t argc, char *argv[])
{
	const char *action;

	if (argc < 2) {
		shell_print(shell, "l2cap rate: %u bps.", l2cap_rate);

		return 0;
	}

	action = argv[1];

	if (!strcmp(action, "on")) {
		metrics = true;
	} else if (!strcmp(action, "off")) {
		metrics = false;
	} else {
		shell_help(shell);
		return 0;
	}

	shell_print(shell, "l2cap metrics %s.", action);
	return 0;
}

static int cmd_whitelist_add(const struct shell *shell, size_t argc, char *argv[])
{
	int i;

	if (!default_conn) {
		shell_error(shell, "Not connected");
		return 0;
	}

	for (i = 0; i < ARRAY_SIZE(l2cap_whitelist); i++) {
		if (l2cap_whitelist[i] == NULL) {
			l2cap_whitelist[i] = bt_conn_ref(default_conn);
			return 0;
		}
	}

	return -ENOMEM;
}

static int cmd_whitelist_remove(const struct shell *shell, size_t argc, char *argv[])
{
	if (!default_conn) {
		shell_error(shell, "Not connected");
		return 0;
	}

	l2cap_whitelist_remove(default_conn, 0);

	return 0;
}

#define HELP_NONE "[none]"

SHELL_STATIC_SUBCMD_SET_CREATE(whitelist_cmds,
	SHELL_CMD_ARG(add, NULL, HELP_NONE, cmd_whitelist_add, 1, 0),
	SHELL_CMD_ARG(remove, NULL, HELP_NONE, cmd_whitelist_remove, 1, 0),
	SHELL_SUBCMD_SET_END
);

SHELL_STATIC_SUBCMD_SET_CREATE(l2cap_cmds,
	SHELL_CMD_ARG(connect, NULL, "<psm> [sec_level]", cmd_connect, 2, 1),
	SHELL_CMD_ARG(disconnect, NULL, HELP_NONE, cmd_disconnect, 1, 0),
	SHELL_CMD_ARG(metrics, NULL, "<value on, off>", cmd_metrics, 2, 0),
	SHELL_CMD_ARG(recv, NULL, "[delay (in miliseconds)", cmd_recv, 1, 1),
	SHELL_CMD_ARG(register, NULL, "<psm> [sec_level] "
		      "[policy: whitelist, 16byte_key]", cmd_register, 2, 2),
	SHELL_CMD_ARG(send, NULL, "[number of packets] [length of packet(s)]",
		      cmd_send, 1, 2),
	SHELL_CMD_ARG(whitelist, &whitelist_cmds, HELP_NONE, NULL, 1, 0),
	SHELL_SUBCMD_SET_END
);

static int cmd_l2cap(const struct shell *shell, size_t argc, char **argv)
{
	if (argc == 1) {
		shell_help(shell);
		/* shell returns 1 when help is printed */
		return 1;
	}

	shell_error(shell, "%s unknown parameter: %s", argv[0], argv[1]);

	return -ENOEXEC;
}

SHELL_CMD_ARG_REGISTER(l2cap, &l2cap_cmds, "Bluetooth L2CAP shell commands",
		       cmd_l2cap, 1, 1);
