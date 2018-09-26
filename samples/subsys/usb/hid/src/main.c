/*
 * Copyright (c) 2016-2018 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define SYS_LOG_LEVEL 4
#define SYS_LOG_DOMAIN "main"
#include <logging/sys_log.h>

#include <zephyr.h>
#include <init.h>

#include <usb/usb_device.h>
#include <usb/class/usb_hid.h>

#define REPORT_ID_1	0x01
#define REPORT_ID_2	0x02

/* Some HID sample Report Descriptor */
static const u8_t hid_report_desc[] = {
	/* 0x05, 0x01,		USAGE_PAGE (Generic Desktop)		*/
	HID_GI_USAGE_PAGE, USAGE_GEN_DESKTOP,
	/* 0x09, 0x00,		USAGE (Undefined)			*/
	HID_LI_USAGE, USAGE_GEN_DESKTOP_UNDEFINED,
	/* 0xa1, 0x01,		COLLECTION (Application)		*/
	HID_MI_COLLECTION, COLLECTION_APPLICATION,
	/* 0x15, 0x00,			LOGICAL_MINIMUM one-byte (0)	*/
	HID_GI_LOGICAL_MIN(1), 0x00,
	/* 0x26, 0xff, 0x00,		LOGICAL_MAXIMUM two-bytes (255)	*/
	HID_GI_LOGICAL_MAX(2), 0xFF, 0x00,
	/* 0x85, 0x01,			REPORT_ID (1)			*/
	HID_GI_REPORT_ID, REPORT_ID_1,
	/* 0x75, 0x08,			REPORT_SIZE (8) in bits		*/
	HID_GI_REPORT_SIZE, 0x08,
	/* 0x95, 0x01,			REPORT_COUNT (1)		*/
	HID_GI_REPORT_COUNT, 0x01,
	/* 0x09, 0x00,			USAGE (Undefined)		*/
	HID_LI_USAGE, USAGE_GEN_DESKTOP_UNDEFINED,
	/* v0x81, 0x82,			INPUT (Data,Var,Abs,Vol)	*/
	HID_MI_INPUT, 0x82,
	/* 0x85, 0x02,			REPORT_ID (2)			*/
	HID_GI_REPORT_ID, REPORT_ID_2,
	/* 0x75, 0x08,			REPORT_SIZE (8) in bits		*/
	HID_GI_REPORT_SIZE, 0x08,
	/* 0x95, 0x01,			REPORT_COUNT (1)		*/
	HID_GI_REPORT_COUNT, 0x01,
	/* 0x09, 0x00,			USAGE (Undefined)		*/
	HID_LI_USAGE, USAGE_GEN_DESKTOP_UNDEFINED,
	/* 0x91, 0x82,			OUTPUT (Data,Var,Abs,Vol)	*/
	HID_MI_OUTPUT, 0x82,
	/* 0xc0			END_COLLECTION			*/
	HID_MI_COLLECTION_END,
};

static u8_t report_1[2] = { REPORT_ID_1, 0x00 };

static int debug_cb(struct usb_setup_packet *setup, s32_t *len,
		    u8_t **data)
{
	SYS_LOG_DBG("Debug callback");

	return -ENOTSUP;
}

static int set_idle_cb(struct usb_setup_packet *setup, s32_t *len,
		       u8_t **data)
{
	SYS_LOG_DBG("Set Idle callback");

	/* TODO: Do something */

	return 0;
}

static int get_report_cb(struct usb_setup_packet *setup, s32_t *len,
			 u8_t **data)
{
	SYS_LOG_DBG("Get report callback");

	/* TODO: Do something */

	return 0;
}

static void in_ready_cb(void)
{
	int ret, wrote;

	ret = hid_int_ep_write(report_1, sizeof(report_1), &wrote);

	SYS_LOG_DBG("Wrote %d bytes with ret %d", wrote, ret);
}

static void status_cb(enum usb_dc_status_code status, u8_t *param)
{
	switch (status) {
	case USB_DC_CONFIGURED:
		in_ready_cb();
		break;
	default:
		SYS_LOG_DBG("status %u unhandled", status);
		break;
	}
}

static const struct hid_ops ops = {
	.get_report = get_report_cb,
	.get_idle = debug_cb,
	.get_protocol = debug_cb,
	.set_report = debug_cb,
	.set_idle = set_idle_cb,
	.set_protocol = debug_cb,
	.int_in_ready = in_ready_cb,
	.status_cb = status_cb,
};

void main(void)
{
	SYS_LOG_DBG("Starting application");

#ifndef CONFIG_USB_COMPOSITE_DEVICE
	usb_hid_register_device(hid_report_desc, sizeof(hid_report_desc), &ops);
	usb_hid_init();
#endif

	while (true) {
		k_sleep(K_SECONDS(2));

		report_1[1]++;
	}
}

#ifdef CONFIG_USB_COMPOSITE_DEVICE
static int composite_pre_init(struct device *dev)
{
	usb_hid_register_device(hid_report_desc, sizeof(hid_report_desc), &ops);

	return usb_hid_init();
}

SYS_INIT(composite_pre_init, APPLICATION, CONFIG_KERNEL_INIT_PRIORITY_DEVICE);
#endif
