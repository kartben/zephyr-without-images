/* main.c - Application main entry point */

/*
 * Copyright (c) 2015 Intel Corporation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1) Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3) Neither the name of Intel Corporation nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <misc/printk.h>
#include <misc/byteorder.h>

#include "bluetooth/bluetooth.h"
#include "bluetooth/hci.h"
#include "bluetooth/uuid.h"
#include "bluetooth/gatt.h"

#define DEVICE_NAME		"Test peripheral"
#define HEART_RATE_APPEARANCE	0x0341

static struct bt_uuid gap_uuid = {
	.type = BT_UUID_16,
	.u16 = BT_UUID_GAP,
};

static struct bt_uuid device_name_uuid = {
	.type = BT_UUID_16,
	.u16 = BT_UUID_GAP_DEVICE_NAME,
};

static struct bt_gatt_chrc name_chrc = {
	.properties = BT_GATT_CHRC_READ,
	.value_handle = 0x0003,
	.uuid = &device_name_uuid,
};

static int read_name(const bt_addr_le_t *peer, const struct bt_gatt_attr *attr,
		     void *buf, uint8_t len, uint16_t offset)
{
	const char *name = attr->user_data;

	return bt_gatt_attr_read(peer, attr, buf, len, offset, name,
				 strlen(name));
}

static struct bt_uuid appeareance_uuid = {
	.type = BT_UUID_16,
	.u16 = BT_UUID_GAP_APPEARANCE,
};

static struct bt_gatt_chrc appearance_chrc = {
	.properties = BT_GATT_CHRC_READ,
	.value_handle = 0x0005,
	.uuid = &appeareance_uuid,
};

static int read_appearance(const bt_addr_le_t *peer,
			   const struct bt_gatt_attr *attr, void *buf,
			   uint8_t len, uint16_t offset)
{
	uint16_t appearance = sys_cpu_to_le16(HEART_RATE_APPEARANCE);

	return bt_gatt_attr_read(peer, attr, buf, len, offset, &appearance,
				 sizeof(appearance));
}

static struct bt_uuid hrs_uuid = {
	.type = BT_UUID_16,
	.u16 = BT_UUID_HRS,
};

static struct bt_uuid hrmc_uuid = {
	.type = BT_UUID_16,
	.u16 = BT_UUID_HR_MEASUREMENT,
};

static struct bt_gatt_chrc hrmc_chrc = {
	.properties = BT_GATT_CHRC_NOTIFY,
	.value_handle = 0x0008,
	.uuid = &hrmc_uuid,
};

static struct bt_uuid bslc_uuid = {
	.type = BT_UUID_16,
	.u16 = BT_UUID_HR_BODY_SENSOR,
};

static struct bt_gatt_chrc bslc_chrc = {
	.properties = BT_GATT_CHRC_READ,
	.value_handle = 0x000b,
	.uuid = &bslc_uuid,
};

static struct bt_uuid hrcpc_uuid = {
	.type = BT_UUID_16,
	.u16 = BT_UUID_HR_CONTROL_POINT,
};

static struct bt_gatt_chrc hrcpc_chrc = {
	.properties = BT_GATT_CHRC_WRITE,
	.value_handle = 0x000d,
	.uuid = &hrcpc_uuid,
};

static struct bt_uuid ccc_uuid = {
	.type = BT_UUID_16,
	.u16 = BT_UUID_GATT_CCC,
};

static uint16_t hrmc_ccc = 0x0000;

static int read_ccc(const bt_addr_le_t *peer, const struct bt_gatt_attr *attr,
		    void *buf, uint8_t len, uint16_t offset)
{
	uint16_t *value = attr->user_data;
	uint16_t data = sys_cpu_to_le16(*value);

	return bt_gatt_attr_read(peer, attr, buf, len, offset, &data,
				 sizeof(data));
}

static int write_ccc(const bt_addr_le_t *peer, const struct bt_gatt_attr *attr,
		     const void *buf, uint8_t len, uint16_t offset)
{
	uint16_t *value = attr->user_data;
	const uint16_t *data = buf;

	if (len != sizeof(*data) || offset) {
		return -EINVAL;
	}

	/* TODO: Write per client */

	*value = sys_le16_to_cpu(*data);

	return len;
}

static int read_blsc(const bt_addr_le_t *peer, const struct bt_gatt_attr *attr,
		     void *buf, uint8_t len, uint16_t offset)
{
	uint8_t value = 0x01;

	return bt_gatt_attr_read(peer, attr, buf, len, offset, &value,
				 sizeof(value));
}

/* Battery Service Variables */
static struct bt_uuid bas_uuid = {
	.type = BT_UUID_16,
	.u16 = BT_UUID_BAS,
};

static struct bt_uuid blvl_uuid = {
	.type = BT_UUID_16,
	.u16 = BT_UUID_BATTERY_LEVEL,
};

static struct bt_gatt_chrc blvl_chrc = {
	.properties = BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
	.value_handle = 0x0010,
	.uuid = &blvl_uuid,
};

static uint16_t blvl_ccc = 0x0000;

static int read_blvl(const bt_addr_le_t *peer, const struct bt_gatt_attr *attr,
		     void *buf, uint8_t len, uint16_t offset)
{
	uint8_t value = 100;

	return bt_gatt_attr_read(peer, attr, buf, len, offset, &value,
				 sizeof(value));
}

/* Current Time Service Variables */
static struct bt_uuid cts_uuid = {
	.type = BT_UUID_16,
	.u16 = BT_UUID_CTS,
};

static struct bt_uuid ct_uuid = {
	.type = BT_UUID_16,
	.u16 = BT_UUID_CURRENT_TIME,
};

static struct bt_gatt_chrc ct_chrc = {
	.properties =  BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
	.value_handle = 0x0014,
	.uuid = &ct_uuid,
};

static uint16_t ct_ccc = 0x0000;

static void generate_current_time(uint8_t *buf)
{
	uint16_t year;

	/* 'Exact Time 256' contains 'Day Date Time' which contains
	 * 'Date Time' - characteristic contains fields for:
	 * year, month, day, hours, minutes and seconds.
	 */

	year = sys_cpu_to_le16(2015);
	memcpy(buf,  &year, 2); /* year */
	buf[2] = 5; /* months starting from 1 */
	buf[3] = 30; /* day */
	buf[4] = 12; /* hours */
	buf[5] = 45; /* minutes */
	buf[6] = 30; /* seconds */

	/* 'Day of Week' part of 'Day Date Time' */
	buf[7] = 1; /* day of week starting from 1 */

	/* 'Fractions 256 part of 'Exact Time 256' */
	buf[8] = 0;

	/* Adjust reason */
	buf[9] = 0; /* No update, change, etc */
}

static int read_ct(const bt_addr_le_t *peer, const struct bt_gatt_attr *attr,
		   void *buf, uint8_t len, uint16_t offset)
{
	uint8_t ct[10];

	generate_current_time(ct);

	return bt_gatt_attr_read(peer, attr, buf, len, offset, &ct, sizeof(ct));
}

static const struct bt_gatt_attr attrs[] = {
	BT_GATT_PRIMARY_SERVICE(0x0001, &gap_uuid),
	BT_GATT_CHARACTERISTIC(0x0002, &name_chrc),
	BT_GATT_DESCRIPTOR(0x0003, &device_name_uuid, read_name, NULL,
			   DEVICE_NAME),
	BT_GATT_CHARACTERISTIC(0x0004, &appearance_chrc),
	BT_GATT_DESCRIPTOR(0x0005, &appeareance_uuid, read_appearance, NULL,
			   NULL),
	/* Heart Rate Service Declaration */
	BT_GATT_PRIMARY_SERVICE(0x0006, &hrs_uuid),
	BT_GATT_CHARACTERISTIC(0x0007, &hrmc_chrc),
	BT_GATT_DESCRIPTOR(0x0008, &hrmc_uuid, NULL, NULL, NULL),
	BT_GATT_DESCRIPTOR(0x0009, &ccc_uuid, read_ccc, write_ccc, &hrmc_ccc),
	BT_GATT_CHARACTERISTIC(0x000a, &bslc_chrc),
	BT_GATT_DESCRIPTOR(0x000b, &bslc_uuid, read_blsc, NULL, NULL),
	BT_GATT_CHARACTERISTIC(0x000c, &hrcpc_chrc),
	/* TODO: Add write permission and callback */
	BT_GATT_DESCRIPTOR(0x000d, &hrcpc_uuid, NULL, NULL, NULL),
	/* Battery Service Declaration */
	BT_GATT_PRIMARY_SERVICE(0x000e, &bas_uuid),
	BT_GATT_CHARACTERISTIC(0x000f, &blvl_chrc),
	BT_GATT_DESCRIPTOR(0x0010, &blvl_uuid, read_blvl, NULL, NULL),
	BT_GATT_DESCRIPTOR(0x0011, &ccc_uuid, read_ccc, write_ccc, &blvl_ccc),
	/* Current Time Service Declaration */
	BT_GATT_PRIMARY_SERVICE(0x0012, &cts_uuid),
	BT_GATT_CHARACTERISTIC(0x0013, &ct_chrc),
	BT_GATT_DESCRIPTOR(0x0014, &ct_uuid, read_ct, NULL, NULL),
	BT_GATT_DESCRIPTOR(0x0015, &ccc_uuid, read_ccc, write_ccc, &ct_ccc),
};

static const struct bt_eir ad[] = {
	{
		.len = 2,
		.type = BT_EIR_FLAGS,
		.data = { BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR },
	},
	{
		.len = 7,
		.type = BT_EIR_UUID16_ALL,
		.data = { 0x0d, 0x18, 0x0f, 0x18, 0x05, 0x18 },
	},
	{ }
};

static const struct bt_eir sd[] = {
	{
		.len = 16,
		.type = BT_EIR_NAME_COMPLETE,
		.data = DEVICE_NAME,
	},
	{ }
};

#ifdef CONFIG_MICROKERNEL
void mainloop(void)
#else
void main(void)
#endif
{
	int err;

	err = bt_init();
	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return;
	}

	printk("Bluetooth initialized\n");

	bt_gatt_register(attrs, ARRAY_SIZE(attrs));

	err = bt_start_advertising(BT_LE_ADV_IND, ad, sd);
	if (err) {
		printk("Advertising failed to start (err %d)\n", err);
		return;
	}

	printk("Advertising successfully started\n");
}
