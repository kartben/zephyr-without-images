/* gatt.c - Generic Attribute Profile handling */

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

#include <nanokernel.h>
#include <toolchain.h>
#include <string.h>
#include <errno.h>
#include <misc/byteorder.h>
#include <misc/util.h>

#include <bluetooth/hci.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/buf.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>

static const struct bt_gatt_attr *db = NULL;
static size_t attr_count = 0;

void bt_gatt_register(const struct bt_gatt_attr *attrs, size_t count)
{
	db = attrs;
	attr_count = count;
}

int bt_gatt_attr_read(const struct bt_gatt_attr *attr, void *buf,
		      uint8_t buf_len, uint16_t offset, const void *value,
		      uint8_t value_len)
{
	uint8_t len;

	if (offset > value_len) {
		return -EINVAL;
	}

	len = min(buf_len, value_len - offset);

	BT_DBG("handle %u offset %u length %u\n", attr->handle, offset, len);

	memcpy(buf, value + offset, len);

	return len;
}

int bt_gatt_attr_read_service(const struct bt_gatt_attr *attr,
			      void *buf, uint8_t len, uint16_t offset)
{
	struct bt_uuid *uuid = attr->user_data;

	if (uuid->type == BT_UUID_16) {
		uint16_t uuid16 = sys_cpu_to_le16(uuid->u16);

		return bt_gatt_attr_read(attr, buf, len, offset, &uuid16,
					 sizeof(uuid16));
	}

	return bt_gatt_attr_read(attr, buf, len, offset, uuid->u128,
				 sizeof(uuid->u128));
}

struct gatt_incl {
	uint16_t start_handle;
	uint16_t end_handle;
	union {
		uint16_t uuid16;
		uint8_t  uuid[16];
	};
} PACK_STRUCT;

int bt_gatt_attr_read_include(struct bt_gatt_attr *attr, void *buf, uint8_t len,
			      uint16_t offset)
{
	struct bt_gatt_include *incl = attr->user_data;
	struct gatt_incl pdu;
	uint8_t value_len;

	pdu.start_handle = sys_cpu_to_le16(incl->start_handle);
	pdu.end_handle = sys_cpu_to_le16(incl->end_handle);
	value_len = sizeof(pdu.start_handle) + sizeof(pdu.end_handle);

	if (incl->uuid->type == BT_UUID_16) {
		pdu.uuid16 = sys_cpu_to_le16(incl->uuid->u16);
		value_len += sizeof(pdu.uuid16);
	} else {
		memcpy(pdu.uuid, incl->uuid->u128, sizeof(incl->uuid->u128));
		value_len += sizeof(incl->uuid->u128);
	}

	return bt_gatt_attr_read(attr, buf, len, offset, &pdu, value_len);
}

struct gatt_chrc {
	uint8_t properties;
	uint16_t value_handle;
	union {
		uint16_t uuid16;
		uint8_t  uuid[16];
	};
} PACK_STRUCT;

int bt_gatt_attr_read_chrc(const struct bt_gatt_attr *attr, void *buf,
			   uint8_t len, uint16_t offset)
{
	struct bt_gatt_chrc *chrc = attr->user_data;
	struct gatt_chrc pdu;
	uint8_t value_len;

	pdu.properties = chrc->properties;
	pdu.value_handle = sys_cpu_to_le16(chrc->value_handle);
	value_len = sizeof(pdu.properties) + sizeof(pdu.value_handle);

	if (chrc->uuid->type == BT_UUID_16) {
		pdu.uuid16 = sys_cpu_to_le16(chrc->uuid->u16);
		value_len += sizeof(pdu.uuid16);
	} else {
		memcpy(pdu.uuid, chrc->uuid->u128, sizeof(chrc->uuid->u128));
		value_len = sizeof(chrc->uuid->u128);
	}

	return bt_gatt_attr_read(attr, buf, len, offset, &pdu, value_len);
}
