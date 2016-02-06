/*
 * Copyright (c) 2016 Intel Corporation
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
#include <misc/byteorder.h>

#include <bluetooth/gatt.h>
#include <bluetooth/log.h>

#include "gatt_internal.h"

#define NBLE_BUF_SIZE	384

struct ble_gatt_service {
	const struct bt_gatt_attr *attrs;
	uint16_t attr_count;
};

static struct ble_gatt_service svc_db[BLE_GATTS_MAX_SERVICES];
static uint8_t svc_count;

/**
 * Copy a UUID in a buffer using the smallest memory length
 * @param buf Pointer to the memory where the UUID shall be copied
 * @param uuid Pointer to the UUID to copy
 * @return The length required to store the UUID in the memory
 */
static uint8_t bt_gatt_uuid_memcpy(uint8_t *buf, const struct bt_uuid *uuid)
{
	uint8_t *ptr = buf;

	/* Store the type of the UUID */
	*ptr = uuid->type;
	ptr++;

	/* Store the UUID data */
	if (uuid->type == BT_UUID_TYPE_16) {
		uint16_t le16;

		le16 = sys_cpu_to_le16(BT_UUID_16(uuid)->val);
		memcpy(ptr, &le16, sizeof(le16));
		ptr += sizeof(le16);
	} else {
		memcpy(ptr, BT_UUID_128(uuid)->val, 16);
		ptr += 16;
	}

	return ptr - buf;
}

/* These attributes need the value to be read */
static struct bt_uuid *whitelist[] = {
	BT_UUID_GATT_PRIMARY,
	BT_UUID_GATT_SECONDARY,
	BT_UUID_GATT_INCLUDE,
	BT_UUID_GATT_CHRC,
	BT_UUID_GATT_CEP,
	BT_UUID_GATT_CUD,
	BT_UUID_GATT_CPF,
	BT_UUID_GAP_DEVICE_NAME,
	BT_UUID_GAP_APPEARANCE,
	BT_UUID_GAP_PPCP
};

static int attr_read(struct bt_gatt_attr *attr, uint8_t *data, size_t len)
{
	uint8_t i;
	int data_size;

	if (!data) {
		return -ENOMEM;
	}

	data_size = bt_gatt_uuid_memcpy(data, attr->uuid);

	for (i = 0; i < ARRAY_SIZE(whitelist); i++) {
		if (!bt_uuid_cmp(attr->uuid, whitelist[i])) {
			int read;

			read = attr->read(NULL, attr, data + data_size, len, 0);
			if (read < 0) {
				return read;
			}

			data_size += read;
			break;
		}
	}

	return data_size;
}

int bt_gatt_register(struct bt_gatt_attr *attrs, size_t count)
{
	struct ble_gatt_register_req param;
	size_t i;
	/* TODO: Replace the following with net_buf */
	uint8_t attr_table[NBLE_BUF_SIZE];
	uint8_t attr_table_size;

	if (!attrs || !count) {
		return -EINVAL;
	}
	BT_ASSERT(svc_count < BLE_GATTS_MAX_SERVICES);

	svc_db[svc_count].attrs = attrs;
	svc_db[svc_count].attr_count = count;
	svc_count++;
	param.attr_base = attrs;
	param.attr_count = count;

	attr_table_size = 0;

	for (i = 0; i < count; i++) {
		struct bt_gatt_attr *attr = &attrs[i];
		struct ble_gatt_attr *att;
		int err;

		if (attr_table_size + sizeof(*att) > sizeof(attr_table)) {
			return -ENOMEM;
		}

		att = (void *)&attr_table[attr_table_size];
		att->perm = attr->perm;

		attr_table_size += sizeof(*att);

		/* Read attribute data */
		err = attr_read(attr, att->data,
				sizeof(attr_table) - attr_table_size);
		if (err < 0) {
			BT_ERR("Failed to read attr: %d", err);
			return err;
		}

		att->data_size = err;

		/* Compute the new element size and align it on upper 4 bytes
		 * boundary.
		 */
		attr_table_size += (att->data_size + 3) & ~3;

		BT_DBG("table size = %u attr data_size = %u", attr_table_size,
		       att->data_size);
	}

	ble_gatt_register_req(&param, attr_table, attr_table_size);
	return 0;
}

void on_ble_gatt_register_rsp(const struct ble_gatt_register_rsp *rsp,
			      const struct ble_gatt_attr_handles *handles,
			      uint8_t len)
{
	BT_DBG("status %u", rsp->status);

	if (rsp->status != 0) {
		return;
	}
#if defined(CONFIG_BLUETOOTH_DEBUG_GATT)
	{
		int idx;

		for (idx = 0; idx < rsp->attr_count; idx++) {
			/* The following order of declaration is assumed for
			 * this to work (otherwise idx-2 will fail!):
			 * BT_GATT_CHARACTERISTIC -> ble core returns invalid
			 * handle.
			 * BT_GATT_DESCRIPTOR -> value handle of characteristic
			 * BT_GATT_CCC -> cccd handle is ignored as no storage
			 * but reference value is updated in CCC with value
			 * handle from descriptor.
			 */
			if (handles[idx].handle != 0) {
				char uuid[37];

				bt_uuid_to_str(rsp->attr_base[idx].uuid,
					       uuid, sizeof(uuid));
				BT_DBG("handle %u uuid %s", handles[idx].handle,
				       uuid);
			}
		}
	}
#endif
}

void bt_gatt_foreach_attr(uint16_t start_handle, uint16_t end_handle,
			  bt_gatt_attr_func_t func, void *user_data)
{
}

struct bt_gatt_attr *bt_gatt_attr_next(const struct bt_gatt_attr *attr)
{
	return NULL;
}

int bt_gatt_attr_read(struct bt_conn *conn, const struct bt_gatt_attr *attr,
		      void *buf, uint16_t buf_len, uint16_t offset,
		      const void *value, uint16_t value_len)
{
	uint16_t len;

	BT_DBG("handle 0x%04x offset %u", attr->handle, offset);

	/* simply return the value length. used as max_value. */
	if (buf == NULL) {
		return value_len;
	}

	if (offset > value_len) {
		return -EINVAL;
	}

	len = min(buf_len, value_len - offset);

	memcpy(buf, value + offset, len);

	return len;
}

int bt_gatt_attr_read_service(struct bt_conn *conn,
			      const struct bt_gatt_attr *attr,
			      void *buf, uint16_t len, uint16_t offset)
{
	struct bt_uuid *uuid = attr->user_data;

	if (uuid->type == BT_UUID_TYPE_16) {
		uint16_t uuid16 = sys_cpu_to_le16(BT_UUID_16(uuid)->val);

		return bt_gatt_attr_read(conn, attr, buf, len, offset,
					 &uuid16, 2);
	}

	return bt_gatt_attr_read(conn, attr, buf, len, offset,
				 BT_UUID_128(uuid)->val, 16);
}

int bt_gatt_attr_read_included(struct bt_conn *conn,
			       const struct bt_gatt_attr *attr,
			       void *buf, uint16_t len, uint16_t offset)
{
	return -ENOSYS;
}

struct gatt_chrc {
	uint8_t properties;
	uint16_t value_handle;
	union {
		uint16_t uuid16;
		uint8_t  uuid[16];
	};
} __packed;

int bt_gatt_attr_read_chrc(struct bt_conn *conn,
			   const struct bt_gatt_attr *attr, void *buf,
			   uint16_t len, uint16_t offset)
{
	struct bt_gatt_chrc *chrc = attr->user_data;
	struct gatt_chrc pdu;
	uint8_t value_len;

	pdu.properties = chrc->properties;

	/* Handle cannot be read at this point */
	pdu.value_handle = 0x0000;

	value_len = sizeof(pdu.properties) + sizeof(pdu.value_handle);

	if (chrc->uuid->type == BT_UUID_TYPE_16) {
		pdu.uuid16 = sys_cpu_to_le16(BT_UUID_16(chrc->uuid)->val);
		value_len += 2;
	} else {
		memcpy(pdu.uuid, BT_UUID_128(chrc->uuid)->val, 16);
		value_len += 16;
	}

	return bt_gatt_attr_read(conn, attr, buf, len, offset, &pdu, value_len);
}

int bt_gatt_attr_read_ccc(struct bt_conn *conn,
			  const struct bt_gatt_attr *attr, void *buf,
			  uint16_t len, uint16_t offset)
{
	return -ENOSYS;
}

int bt_gatt_attr_write_ccc(struct bt_conn *conn,
			   const struct bt_gatt_attr *attr, const void *buf,
			   uint16_t len, uint16_t offset)
{
	struct _bt_gatt_ccc *ccc = attr->user_data;
	const uint16_t *data = buf;

	if (offset > sizeof(*data)) {
		return -EINVAL;
	}

	if (offset + len > sizeof(*data)) {
		return -EFBIG;
	}

	/* We expect to receive this only when the has really changed */
	ccc->value = sys_le16_to_cpu(*data);

	if (ccc->cfg_changed) {
		ccc->cfg_changed(ccc->value);
	}

	BT_DBG("handle 0x%04x value %u", attr->handle, ccc->value);

	return len;
}

int bt_gatt_attr_read_cep(struct bt_conn *conn,
			  const struct bt_gatt_attr *attr, void *buf,
			  uint16_t len, uint16_t offset)
{
	struct bt_gatt_cep *value = attr->user_data;
	uint16_t props = sys_cpu_to_le16(value->properties);

	return bt_gatt_attr_read(conn, attr, buf, len, offset, &props,
				 sizeof(props));
}

int bt_gatt_attr_read_cud(struct bt_conn *conn,
			  const struct bt_gatt_attr *attr, void *buf,
			  uint16_t len, uint16_t offset)
{
	return -ENOSYS;
}

int bt_gatt_attr_read_cpf(struct bt_conn *conn,
			  const struct bt_gatt_attr *attr, void *buf,
			  uint16_t len, uint16_t offset)
{
	return -ENOSYS;
}

int bt_gatt_notify(struct bt_conn *conn, const struct bt_gatt_attr *attr,
		   const void *data, uint16_t len)
{
	struct ble_gatt_send_notif_ind_params notif;

	notif.conn_handle = 0xFFFF;
	notif.params.attr = (struct bt_gatt_attr *)attr;
	notif.params.offset = 0;

	ble_gatt_send_notif_req(&notif, (uint8_t *)data, len);
	return 0;
}

int bt_gatt_exchange_mtu(struct bt_conn *conn, bt_gatt_rsp_func_t func)
{
	return -ENOSYS;
}

int bt_gatt_discover(struct bt_conn *conn,
		     struct bt_gatt_discover_params *params)
{
	return -ENOSYS;
}

int bt_gatt_read(struct bt_conn *conn, struct bt_gatt_read_params *params)
{
	return -ENOSYS;
}

int bt_gatt_write(struct bt_conn *conn, uint16_t handle, uint16_t offset,
		  const void *data, uint16_t length, bt_gatt_rsp_func_t func)
{
	return -ENOSYS;
}

int bt_gatt_write_without_response(struct bt_conn *conn, uint16_t handle,
				   const void *data, uint16_t length,
				   bool sign)
{
	return -ENOSYS;
}

int bt_gatt_subscribe(struct bt_conn *conn,
		      struct bt_gatt_subscribe_params *params)
{
	return -ENOSYS;
}

int bt_gatt_unsubscribe(struct bt_conn *conn,
			struct bt_gatt_subscribe_params *params)
{
	return -ENOSYS;
}

void bt_gatt_cancel(struct bt_conn *conn)
{
}

int bt_gatt_read_multiple(struct bt_conn *conn, const uint16_t *handles,
			  size_t count, bt_gatt_read_func_t func)
{
	return -ENOSYS;
}

void on_ble_gattc_write_rsp(const struct ble_gattc_write_rsp *ev,
			    void *priv)
{
	BT_DBG("");
}

void on_ble_gattc_read_rsp(const struct ble_gattc_read_rsp *ev,
			   uint8_t *data, uint8_t data_len, void *priv)
{
	BT_DBG("");
}

void on_ble_gattc_value_evt(const struct ble_gattc_value_evt *ev,
		uint8_t *buf, uint8_t buflen)
{
	BT_DBG("");
}

void on_ble_gatts_write_evt(const struct ble_gatt_wr_evt *evt,
			    const uint8_t *buf, uint8_t buflen)
{
	const struct bt_gatt_attr *attr = evt->attr;
	struct ble_gatts_rw_reply_params reply_data;

	if (attr->write) {
		reply_data.status = attr->write(NULL, attr, buf, buflen,
						evt->offset);
	}

	BT_DBG("handle 0x%04x buf %p len %u", attr->handle, buf, buflen);

	if (evt->reply) {
		reply_data.conn_handle = evt->conn_handle;
		reply_data.offset = evt->offset;
		reply_data.write_reply = 1;

		nble_gatts_authorize_reply_req(&reply_data, NULL,
					       reply_data.status);
	}
}

void on_ble_gatts_get_attribute_value_rsp(const struct ble_gatts_attribute_response *par,
					  uint8_t *data, uint8_t length)
{
	BT_DBG("");
}

void on_ble_gattc_discover_rsp(const struct ble_gattc_disc_rsp *rsp,
			       const uint8_t *data, uint8_t len)
{
	BT_DBG("");
}

void on_ble_gatts_send_svc_changed_rsp(const struct ble_core_response *par)
{
	BT_DBG("");
}

void on_ble_gatts_set_attribute_value_rsp(const struct ble_gatts_attribute_response *par)
{
	BT_DBG("");
}

void on_ble_gatts_send_notif_ind_rsp(const struct ble_gatt_notif_ind_rsp *par)
{
	BT_DBG("");
}

void on_ble_gatts_read_evt(const struct nble_gatt_rd_evt *evt)
{
	struct ble_gatts_rw_reply_params reply_data;
	const struct bt_gatt_attr *attr;
	/* TODO: Replace the following with net_buf */
	uint8_t data[NBLE_BUF_SIZE];

	reply_data.status = -EACCES;

	attr = evt->attr;

	BT_DBG("read %p", attr);

	if (attr->read) {
		reply_data.status = attr->read(NULL, attr, data, sizeof(data),
					       evt->offset);
	}

	reply_data.conn_handle = evt->conn_handle;
	reply_data.offset = evt->offset;
	reply_data.write_reply = 0;

	nble_gatts_authorize_reply_req(&reply_data, data, reply_data.status);
}
