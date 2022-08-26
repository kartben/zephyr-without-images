/*
 * Copyright (c) 2022 Vestas Wind Systems A/S
 * Copyright (c) 2019 Alexander Wachter
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdlib.h>
#include <stdio.h>

#include <zephyr/device.h>
#include <zephyr/drivers/can.h>
#include <zephyr/logging/log.h>
#include <zephyr/shell/shell.h>

LOG_MODULE_REGISTER(can_shell, CONFIG_CAN_LOG_LEVEL);

struct can_shell_tx_event {
	unsigned int frame_no;
	int error;
};

struct can_shell_mode_mapping {
	const char *name;
	can_mode_t mode;
};

#define CAN_SHELL_MODE_MAPPING(_name, _mode) { .name = _name, .mode = _mode }

static const struct can_shell_mode_mapping can_shell_mode_map[] = {
	/* Array sorted alphabetically based on name */
	CAN_SHELL_MODE_MAPPING("fd",              CAN_MODE_FD),
	CAN_SHELL_MODE_MAPPING("listen-only",     CAN_MODE_LISTENONLY),
	CAN_SHELL_MODE_MAPPING("loopback",        CAN_MODE_LOOPBACK),
	CAN_SHELL_MODE_MAPPING("normal",          CAN_MODE_NORMAL),
	CAN_SHELL_MODE_MAPPING("one-shot",        CAN_MODE_ONE_SHOT),
	CAN_SHELL_MODE_MAPPING("triple-sampling", CAN_MODE_3_SAMPLES),
};

K_MSGQ_DEFINE(can_shell_tx_msgq, sizeof(struct can_shell_tx_event),
	      CONFIG_CAN_SHELL_TX_QUEUE_SIZE, 4);
const struct shell *can_shell_tx_msgq_sh;
static struct k_work_poll can_shell_tx_msgq_work;
static struct k_poll_event can_shell_tx_msgq_events[] = {
	K_POLL_EVENT_STATIC_INITIALIZER(K_POLL_TYPE_MSGQ_DATA_AVAILABLE,
					K_POLL_MODE_NOTIFY_ONLY,
					&can_shell_tx_msgq, 0)
};

CAN_MSGQ_DEFINE(can_shell_rx_msgq, CONFIG_CAN_SHELL_RX_QUEUE_SIZE);
const struct shell *can_shell_rx_msgq_sh;
static struct k_work_poll can_shell_rx_msgq_work;
static struct k_poll_event can_shell_rx_msgq_events[] = {
	K_POLL_EVENT_STATIC_INITIALIZER(K_POLL_TYPE_MSGQ_DATA_AVAILABLE,
					K_POLL_MODE_NOTIFY_ONLY,
					&can_shell_rx_msgq, 0)
};

/* Forward declarations */
static void can_shell_tx_msgq_triggered_work_handler(struct k_work *work);
static void can_shell_rx_msgq_triggered_work_handler(struct k_work *work);

static void can_shell_print_frame(const struct shell *sh, const struct can_frame *frame)
{
	uint8_t nbytes = can_dlc_to_bytes(frame->dlc);
	int i;

#ifdef CONFIG_CAN_RX_TIMESTAMP
	/* Timestamp */
	shell_fprintf(sh, SHELL_NORMAL, "(%05d)  ", frame->timestamp);
#endif /* CONFIG_CAN_RX_TIMESTAMP */

#ifdef CONFIG_CAN_FD_MODE
	/* Flags */
	shell_fprintf(sh, SHELL_NORMAL, "%c  ", frame->brs == 0 ? '-' : 'B');
#endif /* CONFIG_CAN_FD_MODE */

	/* CAN ID */
	shell_fprintf(sh, SHELL_NORMAL, "%*s%0*x  ",
		 frame->id_type == CAN_STANDARD_IDENTIFIER ? 5 : 0, "",
		 frame->id_type == CAN_STANDARD_IDENTIFIER ? 3 : 8,
		 frame->id_type == CAN_STANDARD_IDENTIFIER ?
		 frame->id & CAN_STD_ID_MASK : frame->id & CAN_EXT_ID_MASK);

	/* DLC as number of bytes */
	shell_fprintf(sh, SHELL_NORMAL, "%s[%0*d]  ",
		 frame->fd == 0 ? " " : "",
		 frame->fd == 0 ? 1 : 2,
		 nbytes);

	/* Data payload */
	if (frame->rtr == CAN_DATAFRAME) {
		for (i = 0; i < nbytes; i++) {
			shell_fprintf(sh, SHELL_NORMAL, "%02x ", frame->data[i]);
		}
	} else {
		shell_fprintf(sh, SHELL_NORMAL, "remote transmission request");
	}

	shell_fprintf(sh, SHELL_NORMAL, "\n");
}

static int can_shell_tx_msgq_poll_submit(const struct shell *sh)
{
	int err;

	if (can_shell_tx_msgq_sh == NULL) {
		can_shell_tx_msgq_sh = sh;
		k_work_poll_init(&can_shell_tx_msgq_work, can_shell_tx_msgq_triggered_work_handler);
	}

	err = k_work_poll_submit(&can_shell_tx_msgq_work, can_shell_tx_msgq_events,
				 ARRAY_SIZE(can_shell_tx_msgq_events), K_FOREVER);
	if (err != 0) {
		shell_error(can_shell_tx_msgq_sh, "failed to submit tx msgq polling (err %d)",
			    err);
	}

	return err;
}

static void can_shell_tx_msgq_triggered_work_handler(struct k_work *work)
{
	struct can_shell_tx_event event;

	while (k_msgq_get(&can_shell_tx_msgq, &event, K_NO_WAIT) == 0) {
		if (event.error == 0) {
			shell_print(can_shell_tx_msgq_sh, "CAN frame #%u successfully sent",
				    event.frame_no);
		} else {
			shell_error(can_shell_tx_msgq_sh, "failed to send CAN frame #%u (err %d)",
				    event.frame_no, event.error);
		}
	}

	(void)can_shell_tx_msgq_poll_submit(can_shell_tx_msgq_sh);
}

static void can_shell_tx_callback(const struct device *dev, int error, void *user_data)
{
	struct can_shell_tx_event event;
	int err;

	ARG_UNUSED(dev);

	event.frame_no = POINTER_TO_UINT(user_data);
	event.error = error;

	err = k_msgq_put(&can_shell_tx_msgq, &event, K_NO_WAIT);
	if (err != 0) {
		LOG_ERR("CAN shell tx event queue full");
	}
}

static int can_shell_rx_msgq_poll_submit(const struct shell *sh)
{
	int err;

	if (can_shell_rx_msgq_sh == NULL) {
		can_shell_rx_msgq_sh = sh;
		k_work_poll_init(&can_shell_rx_msgq_work, can_shell_rx_msgq_triggered_work_handler);
	}

	err = k_work_poll_submit(&can_shell_rx_msgq_work, can_shell_rx_msgq_events,
				 ARRAY_SIZE(can_shell_rx_msgq_events), K_FOREVER);
	if (err != 0) {
		shell_error(can_shell_rx_msgq_sh, "failed to submit rx msgq polling (err %d)",
			    err);
	}

	return err;
}

static void can_shell_rx_msgq_triggered_work_handler(struct k_work *work)
{
	struct can_frame frame;

	while (k_msgq_get(&can_shell_rx_msgq, &frame, K_NO_WAIT) == 0) {
		can_shell_print_frame(can_shell_rx_msgq_sh, &frame);
	}

	(void)can_shell_rx_msgq_poll_submit(can_shell_rx_msgq_sh);
}

static const char *can_shell_state_to_string(enum can_state state)
{
	switch (state) {
	case CAN_STATE_ERROR_ACTIVE:
		return "error-active";
	case CAN_STATE_ERROR_WARNING:
		return "error-warning";
	case CAN_STATE_ERROR_PASSIVE:
		return "error-passive";
	case CAN_STATE_BUS_OFF:
		return "bus-off";
	default:
		return "unknown";
	}
}

static void can_shell_print_capabilities(const struct shell *sh, can_mode_t cap)
{
	int bit;
	int i;

	for (bit = 0; bit < sizeof(cap) * 8; bit++) {
		/* Skip unset bits */
		if ((cap & BIT(bit)) == 0) {
			continue;
		}

		/* Lookup symbolic mode name */
		for (i = 0; i < ARRAY_SIZE(can_shell_mode_map); i++) {
			if (BIT(bit) == can_shell_mode_map[i].mode) {
				shell_fprintf(sh, SHELL_NORMAL, "%s ", can_shell_mode_map[i].name);
				break;
			}
		}

		if (i == ARRAY_SIZE(can_shell_mode_map)) {
			/* Symbolic name not found, use raw mode */
			shell_fprintf(sh, SHELL_NORMAL, "0x%08x ", (can_mode_t)BIT(bit));
		}
	}
}

static int cmd_can_bitrate_set(const struct shell *sh, size_t argc, char **argv)
{
	const struct device *dev = device_get_binding(argv[1]);
	struct can_timing timing;
	uint16_t sample_pnt;
	uint32_t bitrate;
	char *endptr;
	int err;

	if (!device_is_ready(dev)) {
		shell_error(sh, "device %s not ready", argv[1]);
		return -ENODEV;
	}

	bitrate = (uint32_t)strtoul(argv[2], &endptr, 10);
	if (*endptr != '\0') {
		shell_error(sh, "failed to parse bitrate");
		return -EINVAL;
	}

	if (argc >= 4) {
		sample_pnt = (uint32_t)strtoul(argv[3], &endptr, 10);
		if (*endptr != '\0') {
			shell_error(sh, "failed to parse sample point");
			return -EINVAL;
		}

		timing.sjw = CAN_SJW_NO_CHANGE;

		err = can_calc_timing(dev, &timing, bitrate, sample_pnt);
		if (err < 0) {
			shell_error(sh, "failed to calculate timing for "
				    "bitrate %d bps, sample point %d.%d%% (err %d)",
				    bitrate, sample_pnt / 10, sample_pnt % 10, err);
			return err;
		}

		shell_print(sh, "setting bitrate to %d bps, sample point %d.%d%% "
			    "(+/- %d.%d%%)",
			    bitrate, sample_pnt / 10, sample_pnt % 10, err / 10, err % 10);

		err = can_set_timing(dev, &timing);
		if (err != 0) {
			shell_error(sh, "failed to set timing (err %d)", err);
			return err;
		}
	} else {
		shell_print(sh, "setting bitrate to %d bps", bitrate);

		err = can_set_bitrate(dev, bitrate);
		if (err != 0) {
			shell_error(sh, "failed to set bitrate (err %d)", err);
			return err;
		}
	}

	return 0;
}

static int cmd_can_dbitrate_set(const struct shell *sh, size_t argc, char **argv)
{
	const struct device *dev = device_get_binding(argv[1]);
	struct can_timing timing;
	uint16_t sample_pnt;
	uint32_t bitrate;
	char *endptr;
	int err;

	if (!device_is_ready(dev)) {
		shell_error(sh, "device %s not ready", argv[1]);
		return -ENODEV;
	}

	bitrate = (uint32_t)strtoul(argv[2], &endptr, 10);
	if (*endptr != '\0') {
		shell_error(sh, "failed to parse data bitrate");
		return -EINVAL;
	}

	if (argc >= 4) {
		sample_pnt = (uint32_t)strtoul(argv[3], &endptr, 10);
		if (*endptr != '\0') {
			shell_error(sh, "failed to parse sample point");
			return -EINVAL;
		}

		timing.sjw = CAN_SJW_NO_CHANGE;

		err = can_calc_timing_data(dev, &timing, bitrate, sample_pnt);
		if (err < 0) {
			shell_error(sh, "failed to calculate timing for "
				    "data bitrate %d bps, sample point %d.%d%% (err %d)",
				    bitrate, sample_pnt / 10, sample_pnt % 10, err);
			return err;
		}

		shell_print(sh, "setting data bitrate to %d bps, sample point %d.%d%% "
			    "(+/- %d.%d%%)",
			    bitrate, sample_pnt / 10, sample_pnt % 10, err / 10, err % 10);

		err = can_set_timing_data(dev, &timing);
		if (err != 0) {
			shell_error(sh, "failed to set data timing (err %d)", err);
			return err;
		}
	} else {
		shell_print(sh, "setting data bitrate to %d bps", bitrate);

		err = can_set_bitrate_data(dev, bitrate);
		if (err != 0) {
			shell_error(sh, "failed to set data bitrate (err %d)", err);
			return err;
		}
	}

	return 0;
}

static int cmd_can_mode_set(const struct shell *sh, size_t argc, char **argv)
{
	const struct device *dev = device_get_binding(argv[1]);
	can_mode_t mode = CAN_MODE_NORMAL;
	can_mode_t raw;
	char *endptr;
	int err;
	int i;
	int j;

	if (!device_is_ready(dev)) {
		shell_error(sh, "device %s not ready", argv[1]);
		return -ENODEV;
	}

	for (i = 2; i < argc; i++) {
		/* Lookup symbolic mode name */
		for (j = 0; j < ARRAY_SIZE(can_shell_mode_map); j++) {
			if (strcmp(argv[i], can_shell_mode_map[j].name) == 0) {
				mode |= can_shell_mode_map[j].mode;
				break;
			}
		}

		if (j == ARRAY_SIZE(can_shell_mode_map)) {
			/* Symbolic name not found, use raw mode if hex number */
			raw = (can_mode_t)strtoul(argv[i], &endptr, 16);
			if (*endptr == '\0') {
				mode |= raw;
				continue;
			}

			shell_error(sh, "failed to parse mode");
			return -EINVAL;
		}
	}

	shell_print(sh, "setting mode 0x%08x", mode);

	err = can_set_mode(dev, mode);
	if (err != 0) {
		shell_error(sh, "failed to set mode 0x%08x (err %d)", mode, err);
		return err;
	}

	return 0;
}

static int cmd_can_send(const struct shell *sh, size_t argc, char **argv)
{
	const struct device *dev = device_get_binding(argv[1]);
	static unsigned int frame_counter;
	unsigned int frame_no;
	struct can_frame frame;
	uint32_t max_id;
	int argidx = 2;
	uint32_t val;
	char *endptr;
	int nbytes;
	int err;
	int i;

	if (!device_is_ready(dev)) {
		shell_error(sh, "device %s not ready", argv[1]);
		return -ENODEV;
	}

	/* Defaults */
	max_id = CAN_MAX_STD_ID;
	frame.id_type = CAN_STANDARD_IDENTIFIER;
	frame.rtr = CAN_DATAFRAME;
	frame.dlc = 0;
	frame.fd = 0;
	frame.brs = 0;

	/* Parse options */
	while (argidx < argc && strncmp(argv[argidx], "-", 1) == 0) {
		if (strcmp(argv[argidx], "--") == 0) {
			argidx++;
			break;
		} else if (strcmp(argv[argidx], "-e") == 0) {
			frame.id_type = CAN_EXTENDED_IDENTIFIER;
			max_id = CAN_MAX_EXT_ID;
			argidx++;
		} else if (strcmp(argv[argidx], "-r") == 0) {
			frame.rtr = CAN_REMOTEREQUEST;
			argidx++;
		} else if (strcmp(argv[argidx], "-f") == 0) {
			frame.fd = 1;
			argidx++;
		} else if (strcmp(argv[argidx], "-b") == 0) {
			frame.brs = 1;
			argidx++;
		} else {
			shell_error(sh, "unsupported option %s", argv[argidx]);
			shell_help(sh);
			return SHELL_CMD_HELP_PRINTED;
		}
	}

	/* Parse CAN ID */
	if (argidx >= argc) {
		shell_error(sh, "missing CAN ID parameter");
		shell_help(sh);
		return SHELL_CMD_HELP_PRINTED;
	}

	val = (uint32_t)strtoul(argv[argidx++], &endptr, 16);
	if (*endptr != '\0') {
		shell_error(sh, "failed to parse CAN ID");
		return -EINVAL;
	}

	if (val > max_id) {
		shell_error(sh, "CAN ID 0x%0*x out of range",
			    frame.id_type == CAN_STANDARD_IDENTIFIER ? 3 : 8,
			    val);
		return -EINVAL;
	}

	frame.id = val;

	nbytes = argc - argidx;
	if (nbytes > ARRAY_SIZE(frame.data)) {
		shell_error(sh, "excessive amount of data (%d bytes)", nbytes);
		return -EINVAL;
	}

	frame.dlc = can_bytes_to_dlc(nbytes);

	/* Parse data */
	for (i = 0; i < nbytes; i++) {
		val = (uint32_t)strtoul(argv[argidx++], &endptr, 16);
		if (*endptr != '\0') {
			shell_error(sh, "failed to parse data %s", argv[argidx++]);
			return -EINVAL;
		}

		if (val > 0xff) {
			shell_error(sh, "data 0x%x out of range", val);
			return -EINVAL;
		}

		frame.data[i] = val;
	}

	err = can_shell_tx_msgq_poll_submit(sh);
	if (err != 0) {
		return err;
	}

	frame_no = frame_counter++;

	shell_print(sh, "enqueuing CAN frame #%u with %s (%d-bit) CAN ID 0x%0*x, "
		    "RTR %d, CAN-FD %d, BRS %d, DLC %d", frame_no,
		    frame.id_type == CAN_STANDARD_IDENTIFIER ? "standard" : "extended",
		    frame.id_type == CAN_STANDARD_IDENTIFIER ? 11 : 29,
		    frame.id_type == CAN_STANDARD_IDENTIFIER ? 3 : 8, frame.id,
		    frame.rtr, frame.fd, frame.brs, can_dlc_to_bytes(frame.dlc));

	err = can_send(dev, &frame, K_NO_WAIT, can_shell_tx_callback, UINT_TO_POINTER(frame_no));
	if (err != 0) {
		shell_error(sh, "failed to enqueue CAN frame #%u (err %d)", frame_no, err);
		return err;
	}

	return 0;
}

static int cmd_can_filter_add(const struct shell *sh, size_t argc, char **argv)
{
	const struct device *dev = device_get_binding(argv[1]);
	struct can_filter filter;
	uint32_t max_id;
	int argidx = 2;
	uint32_t val;
	char *endptr;
	int err;

	if (!device_is_ready(dev)) {
		shell_error(sh, "device %s not ready", argv[1]);
		return -ENODEV;
	}

	/* Defaults */
	max_id = CAN_MAX_STD_ID;
	filter.id_type = CAN_STANDARD_IDENTIFIER;
	filter.rtr = CAN_DATAFRAME;
	filter.rtr_mask = 0;

	/* Parse options */
	while (argidx < argc && strncmp(argv[argidx], "-", 1) == 0) {
		if (strcmp(argv[argidx], "--") == 0) {
			argidx++;
			break;
		} else if (strcmp(argv[argidx], "-e") == 0) {
			filter.id_type = CAN_EXTENDED_IDENTIFIER;
			max_id = CAN_MAX_EXT_ID;
			argidx++;
		} else if (strcmp(argv[argidx], "-r") == 0) {
			filter.rtr = CAN_REMOTEREQUEST;
			argidx++;
		} else if (strcmp(argv[argidx], "-R") == 0) {
			filter.rtr_mask = 1;
			argidx++;
		} else {
			shell_error(sh, "unsupported argument %s", argv[argidx]);
			shell_help(sh);
			return SHELL_CMD_HELP_PRINTED;
		}
	}

	/* Parse CAN ID */
	if (argidx >= argc) {
		shell_error(sh, "missing CAN ID parameter");
		shell_help(sh);
		return SHELL_CMD_HELP_PRINTED;
	}

	val = (uint32_t)strtoul(argv[argidx++], &endptr, 16);
	if (*endptr != '\0') {
		shell_error(sh, "failed to parse CAN ID");
		return -EINVAL;
	}

	if (val > max_id) {
		shell_error(sh, "CAN ID 0x%0*x out of range",
			    filter.id_type == CAN_STANDARD_IDENTIFIER ? 3 : 8,
			    val);
		return -EINVAL;
	}

	filter.id = val;

	if (argidx < argc) {
		/* Parse CAN ID mask */
		val = (uint32_t)strtoul(argv[argidx++], &endptr, 16);
		if (*endptr != '\0') {
			shell_error(sh, "failed to parse CAN ID mask");
			return -EINVAL;
		}

		if (val > max_id) {
			shell_error(sh, "CAN ID mask 0x%0*x out of range",
				    filter.id_type == CAN_STANDARD_IDENTIFIER ? 3 : 8,
				    val);
			return -EINVAL;
		}

	} else {
		val = max_id;
	}

	filter.id_mask = val;

	err = can_shell_rx_msgq_poll_submit(sh);
	if (err != 0) {
		return err;
	}

	shell_print(sh, "adding filter with %s (%d-bit) CAN ID 0x%0*x, "
		    "CAN ID mask 0x%0*x, RTR %d, RTR mask %d",
		    filter.id_type == CAN_STANDARD_IDENTIFIER ? "standard" : "extended",
		    filter.id_type == CAN_STANDARD_IDENTIFIER ? 11 : 29,
		    filter.id_type == CAN_STANDARD_IDENTIFIER ? 3 : 8, filter.id,
		    filter.id_type == CAN_STANDARD_IDENTIFIER ? 3 : 8, filter.id_mask,
		    filter.rtr, filter.rtr_mask);

	err = can_add_rx_filter_msgq(dev, &can_shell_rx_msgq, &filter);
	if (err < 0) {
		shell_error(sh, "failed to add filter (err %d)", err);
		return err;
	}

	shell_print(sh, "filter ID: %d", err);

	return 0;
}

static int cmd_can_filter_remove(const struct shell *sh, size_t argc, char **argv)
{
	const struct device *dev = device_get_binding(argv[1]);
	int filter_id;
	char *endptr;

	if (!device_is_ready(dev)) {
		shell_error(sh, "device %s not ready", argv[1]);
		return -ENODEV;
	}

	/* Parse filter ID */
	filter_id = (int)strtol(argv[2], &endptr, 10);
	if (*endptr != '\0') {
		shell_error(sh, "failed to parse filter ID");
		return -EINVAL;
	}

	shell_print(sh, "removing filter with ID %d", filter_id);
	can_remove_rx_filter(dev, filter_id);

	return 0;
}

static int cmd_can_recover(const struct shell *sh, size_t argc, char **argv)
{
	const struct device *dev = device_get_binding(argv[1]);
	k_timeout_t timeout = K_FOREVER;
	int millisec;
	char *endptr;
	int err;

	if (!device_is_ready(dev)) {
		shell_error(sh, "device %s not ready", argv[1]);
		return -ENODEV;
	}

	if (argc >= 3) {
		/* Parse timeout */
		millisec = (int)strtol(argv[2], &endptr, 10);
		if (*endptr != '\0') {
			shell_error(sh, "failed to parse timeout");
			return -EINVAL;
		}

		timeout = K_MSEC(millisec);
		shell_print(sh, "recovering, timeout %d ms", millisec);
	} else {
		shell_print(sh, "recovering, no timeout");
	}

	err = can_recover(dev, timeout);
	if (err != 0) {
		shell_error(sh, "failed to recover CAN controller from bus-off (err %d)", err);
		return err;
	}

	return 0;
}

static void cmd_can_device_name(size_t idx, struct shell_static_entry *entry)
{
	const struct device *dev = shell_device_lookup(idx, NULL);

	entry->syntax = (dev != NULL) ? dev->name : NULL;
	entry->handler = NULL;
	entry->help = NULL;
	entry->subcmd = NULL;
}

SHELL_DYNAMIC_CMD_CREATE(dsub_can_device_name, cmd_can_device_name);

static void cmd_can_mode(size_t idx, struct shell_static_entry *entry);

SHELL_DYNAMIC_CMD_CREATE(dsub_can_mode, cmd_can_mode);

static void cmd_can_mode(size_t idx, struct shell_static_entry *entry)
{
	if (idx < ARRAY_SIZE(can_shell_mode_map)) {
		entry->syntax = can_shell_mode_map[idx].name;

	} else {
		entry->syntax = NULL;
	}

	entry->handler = NULL;
	entry->help = NULL;
	entry->subcmd = &dsub_can_mode;
}

static void cmd_can_device_name_mode(size_t idx, struct shell_static_entry *entry)
{
	const struct device *dev = shell_device_lookup(idx, NULL);

	entry->syntax = (dev != NULL) ? dev->name : NULL;
	entry->handler = NULL;
	entry->help = NULL;
	entry->subcmd = &dsub_can_mode;
}

SHELL_DYNAMIC_CMD_CREATE(dsub_can_device_name_mode, cmd_can_device_name_mode);

SHELL_STATIC_SUBCMD_SET_CREATE(sub_can_filter_cmds,
	SHELL_CMD_ARG(add, &dsub_can_device_name,
		"Add rx filter\n"
		"Usage: can filter add <device> [-e] [-r] [-R] <CAN ID> [CAN ID mask]\n"
		"-e  use extended (29-bit) CAN ID/CAN ID mask\n"
		"-r  set Remote Transmission Request (RTR) bit\n"
		"-R  set Remote Transmission Request (RTR) mask",
		cmd_can_filter_add, 3, 4),
	SHELL_CMD_ARG(remove, &dsub_can_device_name,
		"Remove rx filter\n"
		"Usage: can filter remove <device> <filter_id>",
		cmd_can_filter_remove, 3, 0),
	SHELL_SUBCMD_SET_END
);

SHELL_STATIC_SUBCMD_SET_CREATE(sub_can_cmds,
	SHELL_CMD_ARG(bitrate, &dsub_can_device_name,
		"Set CAN controller bitrate and optional sample point\n"
		"Usage: can bitrate <device> <bitrate> [sample point]",
		cmd_can_bitrate_set, 3, 1),
	SHELL_COND_CMD_ARG(CONFIG_CAN_FD_MODE,
		dbitrate, &dsub_can_device_name,
		"Set CAN controller data phase bitrate and optional sample point\n"
		"Usage: can dbitrate <device> <data phase bitrate> [sample point]",
		cmd_can_dbitrate_set, 3, 1),
	SHELL_CMD_ARG(mode, &dsub_can_device_name_mode,
		"Set CAN controller mode\n"
		"Usage: can mode <device> <mode> [mode] [mode] [...]",
		cmd_can_mode_set, 3, SHELL_OPT_ARG_CHECK_SKIP),
	SHELL_CMD_ARG(send, &dsub_can_device_name,
		"Enqueue a CAN frame for sending\n"
		"Usage: can send <device> [-e] [-r] [-f] [-b] <CAN ID> [data] [...]\n"
		"-e  use extended (29-bit) CAN ID\n"
		"-r  send Remote Transmission Request (RTR) frame\n"
		"-f  use CAN-FD frame format\n"
		"-b  use CAN-FD Bit Rate Switching (BRS)",
		cmd_can_send, 3, SHELL_OPT_ARG_CHECK_SKIP),
	SHELL_CMD(filter, &sub_can_filter_cmds,
		"CAN rx filter commands\n"
		"Usage: can filter <add|remove> <device> ...",
		NULL),
	SHELL_EXPR_CMD_ARG(!IS_ENABLED(CONFIG_CAN_AUTO_BUS_OFF_RECOVERY),
		recover, &dsub_can_device_name,
		"Recover CAN controller from bus-off state\n"
		"Usage: can recover <device> [timeout ms]",
		cmd_can_recover, 2, 1),
	SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(can, &sub_can_cmds, "CAN controller commands", NULL);
