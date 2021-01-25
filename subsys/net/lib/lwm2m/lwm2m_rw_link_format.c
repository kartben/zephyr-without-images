/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdint.h>
#include <logging/log.h>

#include "lwm2m_engine.h"
#include "lwm2m_rw_link_format.h"

LOG_MODULE_REGISTER(net_lwm2m_link_format, CONFIG_LWM2M_LOG_LEVEL);

#define CORELINK_BUF_SIZE 24

struct link_format_out_formatter_data {
	uint8_t request_level;
	bool is_bootstrap : 1;
	bool is_first : 1;
};

static size_t put_begin(struct lwm2m_output_context *out,
			struct lwm2m_obj_path *path)
{
	char enabler_ver[] = "lwm2m=\"" LWM2M_PROTOCOL_VERSION "\"";
	struct link_format_out_formatter_data *fd;
	int ret;

	fd = engine_get_out_user_data(out);
	if (fd == NULL) {
		return 0;
	}

	if (!fd->is_bootstrap) {
		/* Nothing to add in device management mode. */
		return 0;
	}

	fd->is_first = false;

	ret = buf_append(CPKT_BUF_WRITE(out->out_cpkt), enabler_ver,
			 strlen(enabler_ver));
	if (ret < 0) {
		return 0;
	}

	return strlen(enabler_ver);
}

static int put_corelink_separator(struct lwm2m_output_context *out)
{
	char comma = ',';
	int ret;

	ret = buf_append(CPKT_BUF_WRITE(out->out_cpkt), &comma, sizeof(comma));
	if (ret < 0) {
		return ret;
	}

	return (int)sizeof(comma);
}

static int put_corelink_dimension(struct lwm2m_output_context *out,
				  const struct lwm2m_engine_res *res,
				  uint8_t *buf, uint16_t buflen)
{
	int ret, inst_count = 0, len = 0;

	if (res->multi_res_inst) {
		for (int i = 0; i < res->res_inst_count; i++) {
			if (res->res_instances[i].res_inst_id !=
			    RES_INSTANCE_NOT_CREATED) {
				inst_count++;
			}
		}

		len = snprintk(buf, buflen, ";dim=%d", inst_count);
		if (len < 0 || len >= buflen) {
			return -ENOMEM;
		}

		ret = buf_append(CPKT_BUF_WRITE(out->out_cpkt), buf, len);
		if (ret < 0) {
			return ret;
		}
	}

	return len;
}

static int put_corelink_attributes(struct lwm2m_output_context *out,
				   const void *ref, uint8_t *buf,
				   uint16_t buflen)
{
	struct lwm2m_attr *attr = NULL;
	int used, base, ret;
	uint8_t digit;
	int32_t fraction;
	int len = 0;

	while ((attr = lwm2m_engine_get_next_attr(ref, attr)) != NULL) {
		const char *name = lwm2m_engine_get_attr_name(attr);

		if (name == NULL) {
			/* Invalid attribute, ignore. */
			continue;
		}

		/* Assuming integer will have float_val.val2 set as 0. */
		used = snprintk(buf, buflen, ";%s=%s%d%s",
				name,
				attr->float_val.val1 == 0 &&
				attr->float_val.val2 < 0 ? "-" : "",
				attr->float_val.val1,
				attr->float_val.val2 != 0 ? "." : "");
		if (used < 0 || used >= buflen) {
			return -ENOMEM;
		}

		base = 100000;
		fraction = attr->float_val.val2 < 0 ?
			   -attr->float_val.val2 : attr->float_val.val2;
		while (fraction && used < buflen && base > 0) {
			digit = fraction / base;
			buf[used++] = '0' + digit;
			fraction -= digit * base;
			base /= 10;
		}

		len += used;

		ret = buf_append(CPKT_BUF_WRITE(out->out_cpkt), buf, used);
		if (ret < 0) {
			return ret;
		}
	}

	return len;
}

static int put_corelink_ssid(struct lwm2m_output_context *out,
			     const struct lwm2m_obj_path *path,
			     uint8_t *buf, uint16_t buflen)
{
	uint16_t server_id = 0;
	int ret;
	int len;

	switch (path->obj_id) {
	case LWM2M_OBJECT_SECURITY_ID: {
		bool bootstrap_inst;

		ret = snprintk(buf, buflen, "0/%d/1",
			       path->obj_inst_id);
		if (ret < 0 || ret >= buflen) {
			return -ENOMEM;
		}

		ret = lwm2m_engine_get_bool(buf, &bootstrap_inst);
		if (ret < 0) {
			return ret;
		}

		/* Bootstrap Security object instance does not have associated
		 * Server object instance, so do not report ssid for it.
		 */
		if (bootstrap_inst) {
			return 0;
		}

		ret = snprintk(buf, buflen, "0/%d/10",
				path->obj_inst_id);
		if (ret < 0 || ret >= buflen) {
			return -ENOMEM;
		}

		ret = lwm2m_engine_get_u16(buf, &server_id);
		if (ret < 0) {
			return ret;
		}

		break;
	}

	case LWM2M_OBJECT_SERVER_ID:
		ret = snprintk(buf, buflen, "1/%d/0", path->obj_inst_id);
		if (ret < 0 || ret >= buflen) {
			return -ENOMEM;
		}

		ret = lwm2m_engine_get_u16(buf, &server_id);
		if (ret < 0) {
			return ret;
		}

		break;

	default:
		LOG_ERR("Invalid object ID for ssid attribute: %d",
			path->obj_id);
		return -EINVAL;
	}

	len = snprintk(buf, buflen, ";ssid=%d", server_id);
	if (len < 0 || len >= buflen) {
		return -ENOMEM;
	}

	ret = buf_append(CPKT_BUF_WRITE(out->out_cpkt), buf, len);
	if (ret < 0) {
		return ret;
	}

	return len;
}

static int put_obj_corelink(struct lwm2m_output_context *out,
			    const struct lwm2m_obj_path *path,
			    struct link_format_out_formatter_data *fd)
{
	char obj_buf[CORELINK_BUF_SIZE];
	int len = 0;
	int ret;

	ret = snprintk(obj_buf, sizeof(obj_buf), "</%u>", path->obj_id);
	if (ret < 0 || ret >= sizeof(obj_buf)) {
		return -ENOMEM;
	}

	len += ret;

	ret = buf_append(CPKT_BUF_WRITE(out->out_cpkt), obj_buf, len);
	if (ret < 0) {
		return ret;
	}

	if (!fd->is_bootstrap) {
		/* Report object attributes only in device management mode
		 * (5.4.2).
		 */
		struct lwm2m_engine_obj *obj = lwm2m_engine_get_obj(path);

		if (obj == NULL) {
			return -EINVAL;
		}

		ret = put_corelink_attributes(out, obj, obj_buf,
					      sizeof(obj_buf));
		if (ret < 0) {
			return ret;
		}

		len += ret;
	}

	return len;
}

static int put_obj_inst_corelink(struct lwm2m_output_context *out,
				 const struct lwm2m_obj_path *path,
				 struct link_format_out_formatter_data *fd)
{
	char obj_buf[CORELINK_BUF_SIZE];
	int len = 0;
	int ret;

	ret = snprintk(obj_buf, sizeof(obj_buf), "</%u/%u>",
		       path->obj_id, path->obj_inst_id);
	if (ret < 0 || ret >= sizeof(obj_buf)) {
		return -ENOMEM;
	}

	len += ret;

	ret = buf_append(CPKT_BUF_WRITE(out->out_cpkt), obj_buf, len);
	if (ret < 0) {
		return ret;
	}

	/* Bootstrap object instance corelink shall only contain ssid
	 * parameter for Security and Server objects (5.2.7.3).
	 */
	if (fd->is_bootstrap) {
		if (path->obj_id == LWM2M_OBJECT_SECURITY_ID ||
		    path->obj_id == LWM2M_OBJECT_SERVER_ID) {
			ret = put_corelink_ssid(out, path, obj_buf,
						sizeof(obj_buf));
			if (ret < 0) {
				return ret;
			}

			len += ret;
		}

		return len;
	}

	/* Report object instance attributes only when Instance
	 * ID was specified (5.4.2).
	 */
	if (fd->request_level == LWM2M_PATH_LEVEL_OBJECT_INST) {
		struct lwm2m_engine_obj_inst *obj_inst =
					lwm2m_engine_get_obj_inst(path);

		if (obj_inst == NULL) {
			return -EINVAL;
		}

		ret = put_corelink_attributes(out, obj_inst, obj_buf,
					      sizeof(obj_buf));
		if (ret < 0) {
			return ret;
		}

		len += ret;
	}

	return len;
}

static int put_res_corelink(struct lwm2m_output_context *out,
			    const struct lwm2m_obj_path *path,
			    struct link_format_out_formatter_data *fd)
{
	char obj_buf[CORELINK_BUF_SIZE];
	int len = 0;
	int ret;

	if (fd->is_bootstrap) {
		/* No resource reporting in bootstrap mode. */
		return 0;
	}

	ret = snprintk(obj_buf, sizeof(obj_buf), "</%u/%u/%u>", path->obj_id,
		       path->obj_inst_id, path->res_id);
	if (ret < 0 || ret >= sizeof(obj_buf)) {
		return -ENOMEM;
	}

	len += ret;

	ret = buf_append(CPKT_BUF_WRITE(out->out_cpkt), obj_buf, len);
	if (ret < 0) {
		return ret;
	}

	/* Report resource attrs when at least object instance was specified
	 * (5.4.2).
	 */
	if (fd->request_level >= LWM2M_PATH_LEVEL_OBJECT_INST) {
		struct lwm2m_engine_res *res = lwm2m_engine_get_res(path);

		if (res == NULL) {
			return -EINVAL;
		}

		ret = put_corelink_dimension(out, res, obj_buf,
					     sizeof(obj_buf));
		if (ret < 0) {
			return ret;
		}

		len += ret;

		ret = put_corelink_attributes(out, res, obj_buf,
					      sizeof(obj_buf));
		if (ret < 0) {
			return ret;
		}

		len += ret;
	}

	return len;
}

static ssize_t put_corelink(struct lwm2m_output_context *out,
			    const struct lwm2m_obj_path *path)
{
	struct link_format_out_formatter_data *fd;
	ssize_t len = 0;
	int ret;

	fd = engine_get_out_user_data(out);
	if (fd == NULL) {
		return -EINVAL;
	}

	if (fd->is_first) {
		fd->is_first = false;
	} else {
		ret = put_corelink_separator(out);
		if (ret < 0) {
			return ret;
		}

		len += ret;
	}

	switch (path->level) {
	case LWM2M_PATH_LEVEL_OBJECT:
		ret =  put_obj_corelink(out, path, fd);
		if (ret < 0) {
			return ret;
		}

		len += ret;
		break;

	case LWM2M_PATH_LEVEL_OBJECT_INST:
		ret = put_obj_inst_corelink(out, path, fd);
		if (ret < 0) {
			return ret;
		}

		len += ret;
		break;

	case LWM2M_PATH_LEVEL_RESOURCE:
		ret = put_res_corelink(out, path, fd);
		if (ret < 0) {
			return ret;
		}

		len += ret;
		break;

	default:
		LOG_ERR("Invalid corelink path level: %d", path->level);
		return -EINVAL;
	}

	return len;
}

const struct lwm2m_writer link_format_writer = {
	.put_begin = put_begin,
	.put_corelink = put_corelink,
};

int do_discover_op_link_format(struct lwm2m_message *msg, bool is_bootstrap)
{
	struct link_format_out_formatter_data fd;
	int ret;

	fd.is_first = true;
	fd.is_bootstrap = is_bootstrap;
	fd.request_level = msg->path.level;

	engine_set_out_user_data(&msg->out, &fd);
	ret = lwm2m_discover_handler(msg, is_bootstrap);
	engine_clear_out_user_data(&msg->out);

	return ret;
}
