/*
 * Copyright (c) 2018-2021 mcumgr authors
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <limits.h>
#include <string.h>
#include <sys/util.h>
#include <zcbor_common.h>
#include <zcbor_encode.h>
#include "cborattr/cborattr.h"
#include <mgmt/mcumgr/buf.h>
#include "mgmt/mgmt.h"
#include "fs_mgmt/fs_mgmt.h"
#include "fs_mgmt/fs_mgmt_impl.h"
#include "fs_mgmt/fs_mgmt_config.h"

static struct {
	/** Whether an upload is currently in progress. */
	bool uploading;

	/** Expected offset of next upload request. */
	size_t off;

	/** Total length of file currently being uploaded. */
	size_t len;
} fs_mgmt_ctxt;

static const struct mgmt_handler fs_mgmt_handlers[];

/**
 * Encodes a file upload response.
 */
static bool
fs_mgmt_file_rsp(zcbor_state_t *zse, int rc, uint64_t off)
{
	bool ok;

	ok = zcbor_tstr_put_lit(zse, "rc")	&&
	     zcbor_int32_put(zse, rc)		&&
	     zcbor_tstr_put_lit(zse, "off")	&&
	     zcbor_uint64_put(zse, off);

	return ok;
}

/**
 * Command handler: fs file (read)
 */
static int
fs_mgmt_file_download(struct mgmt_ctxt *ctxt)
{
	uint8_t file_data[FS_MGMT_DL_CHUNK_SIZE];
	char path[CONFIG_FS_MGMT_PATH_SIZE + 1];
	unsigned long long off;
	size_t bytes_read;
	size_t file_len;
	int rc;
	zcbor_state_t *zse = ctxt->cnbe->zs;
	bool ok;

	const struct cbor_attr_t dload_attr[] = {
		{
			.attribute = "off",
			.type = CborAttrUnsignedIntegerType,
			.addr.uinteger = &off,
		},
		{
			.attribute = "name",
			.type = CborAttrTextStringType,
			.addr.string = path,
			.len = sizeof(path),
		},
		{ 0 },
	};

	off = ULLONG_MAX;
	rc = cbor_read_object(&ctxt->it, dload_attr);
	if (rc != 0 || off == ULLONG_MAX) {
		return MGMT_ERR_EINVAL;
	}

	/* Only the response to the first download request contains the total file
	 * length.
	 */
	if (off == 0) {
		rc = fs_mgmt_impl_filelen(path, &file_len);
		if (rc != 0) {
			return rc;
		}
	}

	/* Read the requested chunk from the file. */
	rc = fs_mgmt_impl_read(path, off, FS_MGMT_DL_CHUNK_SIZE,
						   file_data, &bytes_read);
	if (rc != 0) {
		return rc;
	}

	/* Encode the response. */
	ok = fs_mgmt_file_rsp(zse, MGMT_ERR_EOK, off)				&&
	     zcbor_tstr_put_lit(zse, "data")					&&
	     zcbor_bstr_encode_ptr(zse, file_data, bytes_read)			&&
	     ((off != 0)							||
		(zcbor_tstr_put_lit(zse, "len") && zcbor_uint64_put(zse, file_len)));

	return ok ? MGMT_ERR_EOK : MGMT_ERR_ENOMEM;
}

/**
 * Command handler: fs file (write)
 */
static int
fs_mgmt_file_upload(struct mgmt_ctxt *ctxt)
{
	uint8_t file_data[CONFIG_FS_MGMT_UL_CHUNK_SIZE];
	char file_name[CONFIG_FS_MGMT_PATH_SIZE + 1];
	unsigned long long len;
	unsigned long long off;
	size_t data_len;
	size_t new_off;
	int rc;
	zcbor_state_t *zse = ctxt->cnbe->zs;

	const struct cbor_attr_t uload_attr[5] = {
		[0] = {
			.attribute = "off",
			.type = CborAttrUnsignedIntegerType,
			.addr.uinteger = &off,
			.nodefault = true
		},
		[1] = {
			.attribute = "data",
			.type = CborAttrByteStringType,
			.addr.bytestring.data = file_data,
			.addr.bytestring.len = &data_len,
			.len = sizeof(file_data)
		},
		[2] = {
			.attribute = "len",
			.type = CborAttrUnsignedIntegerType,
			.addr.uinteger = &len,
			.nodefault = true
		},
		[3] = {
			.attribute = "name",
			.type = CborAttrTextStringType,
			.addr.string = file_name,
			.len = sizeof(file_name)
		},
		[4] = { 0 },
	};

	len = ULLONG_MAX;
	off = ULLONG_MAX;
	rc = cbor_read_object(&ctxt->it, uload_attr);
	if (rc != 0 || off == ULLONG_MAX || file_name[0] == '\0') {
		return MGMT_ERR_EINVAL;
	}

	if (off == 0) {
		/* Total file length is a required field in the first chunk request. */
		if (len == ULLONG_MAX) {
			return MGMT_ERR_EINVAL;
		}

		fs_mgmt_ctxt.uploading = true;
		fs_mgmt_ctxt.off = 0;
		fs_mgmt_ctxt.len = len;
	} else {
		if (!fs_mgmt_ctxt.uploading) {
			return MGMT_ERR_EINVAL;
		}

		if (off != fs_mgmt_ctxt.off) {
			/* Invalid offset.  Drop the data and send the expected offset. */
			return fs_mgmt_file_rsp(zse, MGMT_ERR_EINVAL, fs_mgmt_ctxt.off);
		}
	}

	new_off = fs_mgmt_ctxt.off + data_len;
	if (new_off > fs_mgmt_ctxt.len) {
		/* Data exceeds image length. */
		return MGMT_ERR_EINVAL;
	}

	if (data_len > 0) {
		/* Write the data chunk to the file. */
		rc = fs_mgmt_impl_write(file_name, off, file_data, data_len);
		if (rc != 0) {
			return rc;
		}
		fs_mgmt_ctxt.off = new_off;
	}

	if (fs_mgmt_ctxt.off == fs_mgmt_ctxt.len) {
		/* Upload complete. */
		fs_mgmt_ctxt.uploading = false;
	}

	/* Send the response. */
	return fs_mgmt_file_rsp(zse, MGMT_ERR_EOK, fs_mgmt_ctxt.off) ?
			MGMT_ERR_EOK : MGMT_ERR_ENOMEM;
}

static const struct mgmt_handler fs_mgmt_handlers[] = {
	[FS_MGMT_ID_FILE] = {
		.mh_read = fs_mgmt_file_download,
		.mh_write = fs_mgmt_file_upload,
	},
};

#define FS_MGMT_HANDLER_CNT ARRAY_SIZE(fs_mgmt_handlers)

static struct mgmt_group fs_mgmt_group = {
	.mg_handlers = fs_mgmt_handlers,
	.mg_handlers_count = FS_MGMT_HANDLER_CNT,
	.mg_group_id = MGMT_GROUP_ID_FS,
};

void
fs_mgmt_register_group(void)
{
	mgmt_register_group(&fs_mgmt_group);
}
