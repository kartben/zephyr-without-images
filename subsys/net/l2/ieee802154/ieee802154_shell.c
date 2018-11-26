/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/** @file
 * @brief IEEE 802.15.4 shell module
 */

#define LOG_MODULE_NAME net_ieee802154_shell
#define NET_LOG_LEVEL CONFIG_NET_L2_IEEE802154_LOG_LEVEL

#include <zephyr.h>
#include <stdio.h>
#include <stdlib.h>
#include <shell/shell.h>
#include <shell/shell_uart.h>
#include <misc/printk.h>

#include <net/net_if.h>
#include <net/ieee802154_mgmt.h>

#include "ieee802154_frame.h"

#define MAX_EXT_ADDR_STR_LEN sizeof("xx:xx:xx:xx:xx:xx:xx:xx")

struct ieee802154_req_params params;
static struct net_mgmt_event_callback scan_cb;
static const struct shell *cb_shell;

static int cmd_ieee802154_ack(const struct shell *shell,
			      size_t argc, char *argv[])
{
	struct net_if *iface = net_if_get_ieee802154();

	ARG_UNUSED(argc);

	if (shell_help_requested(shell)) {
		shell_help_print(shell);
		return -ENOEXEC;
	}

	if (!iface) {
		shell_fprintf(shell, SHELL_INFO,
			      "No IEEE 802.15.4 interface found.\n");
		return -ENOEXEC;
	}

	if (!strcmp(argv[1], "set") || !strcmp(argv[1], "1")) {
		net_mgmt(NET_REQUEST_IEEE802154_SET_ACK, iface, NULL, 0);
		shell_fprintf(shell, SHELL_NORMAL,
			      "ACK flag set on outgoing packets\n");

		return 0;
	}

	if (!strcmp(argv[1], "unset") || !strcmp(argv[1], "0")) {
		net_mgmt(NET_REQUEST_IEEE802154_UNSET_ACK, iface, NULL, 0);
		shell_fprintf(shell, SHELL_NORMAL,
			      "ACK flag unset on outgoing packets\n");

		return 0;
	}

	return 0;
}

static inline void parse_extended_address(char *addr, u8_t *ext_addr)
{
	net_bytes_from_str(ext_addr, IEEE802154_EXT_ADDR_LENGTH, addr);
}

static int cmd_ieee802154_associate(const struct shell *shell,
				    size_t argc, char *argv[])
{
	struct net_if *iface = net_if_get_ieee802154();
	char ext_addr[MAX_EXT_ADDR_STR_LEN];

	if (argc < 3 || shell_help_requested(shell)) {
		shell_help_print(shell);
		return -ENOEXEC;
	}

	if (!iface) {
		shell_fprintf(shell, SHELL_INFO,
			      "No IEEE 802.15.4 interface found.\n");
		return -ENOEXEC;
	}

	params.pan_id = atoi(argv[1]);
	strncpy(ext_addr, argv[2], MAX_EXT_ADDR_STR_LEN - 1);

	if (strlen(ext_addr) == MAX_EXT_ADDR_STR_LEN) {
		parse_extended_address(ext_addr, params.addr);
		params.len = IEEE802154_EXT_ADDR_LENGTH;
	} else {
		params.short_addr = (u16_t) atoi(ext_addr);
		params.len = IEEE802154_SHORT_ADDR_LENGTH;
	}

	if (net_mgmt(NET_REQUEST_IEEE802154_ASSOCIATE, iface,
		     &params, sizeof(struct ieee802154_req_params))) {
		shell_fprintf(shell, SHELL_WARNING,
			      "Could not associate to %s on PAN ID %u\n",
			      argv[2], params.pan_id);

		return -ENOEXEC;
	} else {
		shell_fprintf(shell, SHELL_NORMAL,
			      "Associated to PAN ID %u\n", params.pan_id);
	}

	return 0;
}

static int cmd_ieee802154_disassociate(const struct shell *shell,
				       size_t argc, char *argv[])
{
	struct net_if *iface = net_if_get_ieee802154();
	int ret;

	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	if (shell_help_requested(shell)) {
		shell_help_print(shell);
		return -ENOEXEC;
	}

	if (!iface) {
		shell_fprintf(shell, SHELL_INFO,
			      "No IEEE 802.15.4 interface found.\n");
		return -ENOEXEC;
	}

	ret = net_mgmt(NET_REQUEST_IEEE802154_DISASSOCIATE, iface, NULL, 0);
	if (ret == -EALREADY) {
		shell_fprintf(shell, SHELL_INFO,
			      "Interface is not associated\n");

		return -ENOEXEC;
	} else if (ret) {
		shell_fprintf(shell, SHELL_WARNING,
			      "Could not disassociate? (status: %i)\n", ret);

		return -ENOEXEC;
	} else {
		shell_fprintf(shell, SHELL_NORMAL,
			      "Interface is now disassociated\n");
	}

	return 0;
}

static inline u32_t parse_channel_set(char *str_set)
{
	u32_t channel_set = 0U;
	char *p, *n;

	p = str_set;

	do {
		u32_t chan;

		n = strchr(p, ':');
		if (n) {
			*n = '\0';
		}

		chan = atoi(p);
		if (chan > 0 && chan < 32) {
			channel_set |= BIT(chan - 1);
		}

		p = n ? n + 1 : n;
	} while (n);

	return channel_set;
}

static inline char *print_coordinator_address(char *buf, int buf_len)
{
	if (params.len == IEEE802154_EXT_ADDR_LENGTH) {
		int i, pos = 0;

		pos += snprintk(buf + pos, buf_len - pos, "(extended) ");

		for (i = IEEE802154_EXT_ADDR_LENGTH - 1; i > -1; i--) {
			pos += snprintk(buf + pos, buf_len - pos,
					"%02X:", params.addr[i]);
		}

		buf[pos - 1] = '\0';
	} else {
		snprintk(buf, buf_len, "(short) %u", params.short_addr);
	}

	return buf;
}

static void scan_result_cb(struct net_mgmt_event_callback *cb,
			   u32_t mgmt_event, struct net_if *iface)
{
	char buf[64];

	shell_fprintf(cb_shell, SHELL_NORMAL,
		      "\nChannel: %u\tPAN ID: %u\tCoordinator Address: %s\t "
		      "LQI: %u\n", params.channel, params.pan_id,
		      print_coordinator_address(buf, sizeof(buf)), params.lqi);
}

static int cmd_ieee802154_scan(const struct shell *shell,
			       size_t argc, char *argv[])
{
	struct net_if *iface = net_if_get_ieee802154();
	u32_t scan_type;
	int ret;

	if (argc < 3 || shell_help_requested(shell)) {
		shell_help_print(shell);
		return -ENOEXEC;
	}

	if (!iface) {
		shell_fprintf(shell, SHELL_INFO,
			      "No IEEE 802.15.4 interface found.\n");
		return -ENOEXEC;
	}

	(void)memset(&params, 0, sizeof(struct ieee802154_req_params));

	net_mgmt_init_event_callback(&scan_cb, scan_result_cb,
				     NET_EVENT_IEEE802154_SCAN_RESULT);

	if (!strcmp(argv[1], "active")) {
		scan_type = NET_REQUEST_IEEE802154_ACTIVE_SCAN;
	} else if (!strcmp(argv[1], "passive")) {
		scan_type = NET_REQUEST_IEEE802154_PASSIVE_SCAN;
	} else {
		return -ENOEXEC;
	}

	if (!strcmp(argv[2], "all")) {
		params.channel_set = IEEE802154_ALL_CHANNELS;
	} else {
		params.channel_set = parse_channel_set(argv[2]);
	}

	if (!params.channel_set) {
		return -ENOEXEC;
	}

	params.duration = atoi(argv[3]);

	shell_fprintf(shell, SHELL_NORMAL,
		      "%s Scanning (channel set: 0x%08x, duration %u ms)...\n",
		      scan_type == NET_REQUEST_IEEE802154_ACTIVE_SCAN ?
		      "Active" : "Passive", params.channel_set,
		      params.duration);

	cb_shell = shell;

	if (scan_type == NET_REQUEST_IEEE802154_ACTIVE_SCAN) {
		ret = net_mgmt(NET_REQUEST_IEEE802154_ACTIVE_SCAN, iface,
			       &params, sizeof(struct ieee802154_req_params));
	} else {
		ret = net_mgmt(NET_REQUEST_IEEE802154_PASSIVE_SCAN, iface,
			       &params, sizeof(struct ieee802154_req_params));
	}

	if (ret) {
		shell_fprintf(shell, SHELL_WARNING,
			      "Could not raise a scan (status: %i)\n", ret);

		return -ENOEXEC;
	} else {
		shell_fprintf(shell, SHELL_NORMAL,
			      "Done\n");
	}

	return 0;
}

static int cmd_ieee802154_set_chan(const struct shell *shell,
				   size_t argc, char *argv[])
{
	struct net_if *iface = net_if_get_ieee802154();
	u16_t channel;

	if (argc < 2 || shell_help_requested(shell)) {
		shell_help_print(shell);
		return -ENOEXEC;
	}

	if (!iface) {
		shell_fprintf(shell, SHELL_INFO,
			      "No IEEE 802.15.4 interface found.\n");
		return -ENOEXEC;
	}

	channel = (u16_t)atoi(argv[1]);

	if (net_mgmt(NET_REQUEST_IEEE802154_SET_CHANNEL, iface,
		     &channel, sizeof(u16_t))) {
		shell_fprintf(shell, SHELL_WARNING,
			      "Could not set channel %u\n", channel);

		return -ENOEXEC;
	} else {
		shell_fprintf(shell, SHELL_NORMAL,
			      "Channel %u set\n", channel);
	}

	return 0;
}

static int cmd_ieee802154_get_chan(const struct shell *shell,
				   size_t argc, char *argv[])
{
	struct net_if *iface = net_if_get_ieee802154();
	u16_t channel;

	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	if (shell_help_requested(shell)) {
		shell_help_print(shell);
		return -ENOEXEC;
	}

	if (!iface) {
		shell_fprintf(shell, SHELL_INFO,
			      "No IEEE 802.15.4 interface found.\n");
		return -ENOEXEC;
	}

	if (net_mgmt(NET_REQUEST_IEEE802154_GET_CHANNEL, iface,
		     &channel, sizeof(u16_t))) {
		shell_fprintf(shell, SHELL_WARNING,
			      "Could not get channel\n");

		return -ENOEXEC;
	} else {
		shell_fprintf(shell, SHELL_NORMAL,
			      "Channel %u\n", channel);
	}

	return 0;
}

static int cmd_ieee802154_set_pan_id(const struct shell *shell,
				     size_t argc, char *argv[])
{
	struct net_if *iface = net_if_get_ieee802154();
	u16_t pan_id;

	ARG_UNUSED(argc);

	if (argc < 2 || shell_help_requested(shell)) {
		shell_help_print(shell);
		return -ENOEXEC;
	}

	if (!iface) {
		shell_fprintf(shell, SHELL_INFO,
			      "No IEEE 802.15.4 interface found.\n");
		return -ENOEXEC;
	}

	pan_id = (u16_t)atoi(argv[1]);

	if (net_mgmt(NET_REQUEST_IEEE802154_SET_PAN_ID, iface,
		     &pan_id, sizeof(u16_t))) {
		shell_fprintf(shell, SHELL_WARNING,
			      "Could not set PAN ID %u\n", pan_id);

		return -ENOEXEC;
	} else {
		shell_fprintf(shell, SHELL_NORMAL,
			      "PAN ID %u set\n", pan_id);
	}

	return 0;
}

static int cmd_ieee802154_get_pan_id(const struct shell *shell,
				     size_t argc, char *argv[])
{
	struct net_if *iface = net_if_get_ieee802154();
	u16_t pan_id;

	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

	if (shell_help_requested(shell)) {
		shell_help_print(shell);
		return -ENOEXEC;
	}

	if (!iface) {
		shell_fprintf(shell, SHELL_INFO,
			      "No IEEE 802.15.4 interface found.\n");
		return -ENOEXEC;
	}

	if (net_mgmt(NET_REQUEST_IEEE802154_GET_PAN_ID, iface,
		     &pan_id, sizeof(u16_t))) {
		shell_fprintf(shell, SHELL_WARNING,
			      "Could not get PAN ID\n");

		return -ENOEXEC;
	} else {
		shell_fprintf(shell, SHELL_NORMAL,
			      "PAN ID %u (0x%x)\n", pan_id, pan_id);
	}

	return 0;
}

static int cmd_ieee802154_set_ext_addr(const struct shell *shell,
				       size_t argc, char *argv[])
{
	struct net_if *iface = net_if_get_ieee802154();
	u8_t addr[IEEE802154_EXT_ADDR_LENGTH];

	if (argc < 2 || shell_help_requested(shell)) {
		shell_help_print(shell);
		return -ENOEXEC;
	}

	if (!iface) {
		shell_fprintf(shell, SHELL_INFO,
			      "No IEEE 802.15.4 interface found.\n");
		return -ENOEXEC;
	}

	if (strlen(argv[1]) != MAX_EXT_ADDR_STR_LEN) {
		shell_fprintf(shell, SHELL_INFO,
			      "%zd characters needed\n", MAX_EXT_ADDR_STR_LEN);
		return -ENOEXEC;
	}

	parse_extended_address(argv[1], addr);

	if (net_mgmt(NET_REQUEST_IEEE802154_SET_EXT_ADDR, iface,
		     addr, IEEE802154_EXT_ADDR_LENGTH)) {
		shell_fprintf(shell, SHELL_WARNING,
			      "Could not set extended address\n");

		return -ENOEXEC;
	} else {
		shell_fprintf(shell, SHELL_NORMAL,
			      "Extended address set\n");
	}

	return 0;
}

static int cmd_ieee802154_get_ext_addr(const struct shell *shell,
				       size_t argc, char *argv[])
{
	struct net_if *iface = net_if_get_ieee802154();
	u8_t addr[IEEE802154_EXT_ADDR_LENGTH];

	if (shell_help_requested(shell)) {
		shell_help_print(shell);
		return -ENOEXEC;
	}

	if (!iface) {
		shell_fprintf(shell, SHELL_INFO,
			      "No IEEE 802.15.4 interface found.\n");
		return -ENOEXEC;
	}

	if (net_mgmt(NET_REQUEST_IEEE802154_GET_EXT_ADDR, iface,
		     addr, IEEE802154_EXT_ADDR_LENGTH)) {
		shell_fprintf(shell, SHELL_WARNING,
			      "Could not get extended address\n");
		return -ENOEXEC;
	} else {
		static char ext_addr[MAX_EXT_ADDR_STR_LEN];
		int i, j;

		for (j = 0, i = IEEE802154_EXT_ADDR_LENGTH - 1; i > -1; i--) {
			snprintf(&ext_addr[j], 4, "%02X:", addr[i]);

			j += 3;
		}

		ext_addr[MAX_EXT_ADDR_STR_LEN - 1] = '\0';

		shell_fprintf(shell, SHELL_NORMAL,
			      "Extended address: %s\n", ext_addr);
	}

	return 0;
}

static int cmd_ieee802154_set_short_addr(const struct shell *shell,
					 size_t argc, char *argv[])
{
	struct net_if *iface = net_if_get_ieee802154();
	u16_t short_addr;

	if (argc < 2 || shell_help_requested(shell)) {
		shell_help_print(shell);
		return -ENOEXEC;
	}

	if (!iface) {
		shell_fprintf(shell, SHELL_INFO,
			      "No IEEE 802.15.4 interface found.\n");
		return -ENOEXEC;
	}

	short_addr = (u16_t)atoi(argv[1]);

	if (net_mgmt(NET_REQUEST_IEEE802154_SET_SHORT_ADDR, iface,
		     &short_addr, sizeof(u16_t))) {
		shell_fprintf(shell, SHELL_WARNING,
			      "Could not set short address %u\n", short_addr);

		return -ENOEXEC;
	} else {
		shell_fprintf(shell, SHELL_NORMAL,
			      "Short address %u set\n", short_addr);
	}

	return 0;
}

static int cmd_ieee802154_get_short_addr(const struct shell *shell,
					 size_t argc, char *argv[])
{
	struct net_if *iface = net_if_get_ieee802154();
	u16_t short_addr;

	if (shell_help_requested(shell)) {
		shell_help_print(shell);
		return -ENOEXEC;
	}

	if (!iface) {
		shell_fprintf(shell, SHELL_INFO,
			      "No IEEE 802.15.4 interface found.\n");
		return -ENOEXEC;
	}

	if (net_mgmt(NET_REQUEST_IEEE802154_GET_SHORT_ADDR, iface,
		     &short_addr, sizeof(u16_t))) {
		shell_fprintf(shell, SHELL_WARNING,
			      "Could not get short address\n");

		return -ENOEXEC;
	} else {
		shell_fprintf(shell, SHELL_NORMAL,
			      "Short address %u\n", short_addr);
	}

	return 0;
}

static int cmd_ieee802154_set_tx_power(const struct shell *shell,
				       size_t argc, char *argv[])
{
	struct net_if *iface = net_if_get_ieee802154();
	s16_t tx_power;

	if (argc < 2 || shell_help_requested(shell)) {
		shell_help_print(shell);
		return -ENOEXEC;
	}

	if (!iface) {
		shell_fprintf(shell, SHELL_INFO,
			      "No IEEE 802.15.4 interface found.\n");
		return -ENOEXEC;
	}

	tx_power = (s16_t)atoi(argv[1]);

	if (net_mgmt(NET_REQUEST_IEEE802154_SET_TX_POWER, iface,
		     &tx_power, sizeof(s16_t))) {
		shell_fprintf(shell, SHELL_WARNING,
			      "Could not set TX power %d\n", tx_power);

		return -ENOEXEC;
	} else {
		shell_fprintf(shell, SHELL_NORMAL,
			      "TX power %d set\n", tx_power);
	}

	return 0;
}

static int cmd_ieee802154_get_tx_power(const struct shell *shell,
				       size_t argc, char *argv[])
{
	struct net_if *iface = net_if_get_ieee802154();
	s16_t tx_power;

	if (shell_help_requested(shell)) {
		shell_help_print(shell);
		return -ENOEXEC;
	}

	if (!iface) {
		shell_fprintf(shell, SHELL_INFO,
			      "No IEEE 802.15.4 interface found.\n");
		return -ENOEXEC;
	}

	if (net_mgmt(NET_REQUEST_IEEE802154_GET_TX_POWER, iface,
		     &tx_power, sizeof(s16_t))) {
		shell_fprintf(shell, SHELL_WARNING,
			      "Could not get TX power\n");

		return -ENOEXEC;
	} else {
		shell_fprintf(shell, SHELL_NORMAL,
			      "TX power (in dbm) %d\n", tx_power);
	}

	return 0;
}

SHELL_CREATE_STATIC_SUBCMD_SET(ieee802154_commands)
{
	SHELL_CMD(ack, NULL,
		  "<set/1 | unset/0> Set auto-ack flag",
		  cmd_ieee802154_ack),
	SHELL_CMD(associate, NULL,
		  "<pan_id> <PAN coordinator short or long address (EUI-64)>",
		  cmd_ieee802154_associate),
	SHELL_CMD(disassociate,	NULL,
		  "Disassociate from network",
		  cmd_ieee802154_disassociate),
	SHELL_CMD(get_chan, NULL,
		  "Get currently used channel",
		  cmd_ieee802154_get_chan),
	SHELL_CMD(get_ext_addr,	NULL,
		  "Get currently used extended address",
		  cmd_ieee802154_get_ext_addr),
	SHELL_CMD(get_pan_id, NULL,
		  "Get currently used PAN id",
		  cmd_ieee802154_get_pan_id),
	SHELL_CMD(get_short_addr, NULL,
		  "Get currently used short address",
		  cmd_ieee802154_get_short_addr),
	SHELL_CMD(get_tx_power,	NULL,
		  "Get currently used TX power",
		  cmd_ieee802154_get_tx_power),
	SHELL_CMD(scan,	NULL,
		  "<passive|active> <channels set n[:m:...]:x|all>"
		  " <per-channel duration in ms>",
		  cmd_ieee802154_scan),
	SHELL_CMD(set_chan, NULL,
		  "<channel> Set used channel",
		  cmd_ieee802154_set_chan),
	SHELL_CMD(set_ext_addr,	NULL,
		  "<long/extended address (EUI-64)> Set extended address",
		  cmd_ieee802154_set_ext_addr),
	SHELL_CMD(set_pan_id, NULL,
		  "<pan_id> Set used PAN id",
		  cmd_ieee802154_set_pan_id),
	SHELL_CMD(set_short_addr, NULL,
		  "<short address> Set short address",
		  cmd_ieee802154_set_short_addr),
	SHELL_CMD(set_tx_power,	NULL,
		  "<-18/-7/-4/-2/0/1/2/3/5> Set TX power",
		  cmd_ieee802154_set_tx_power),
	SHELL_SUBCMD_SET_END
};

SHELL_CMD_REGISTER(ieee802154, &ieee802154_commands, "IEEE 802.15.4 commands",
		   NULL);
