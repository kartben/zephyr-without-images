/*
 * Copyright (c) 2018-2021 mcumgr authors
 * Copyright (c) 2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <sys/util.h>
#include <assert.h>
#include <string.h>
#include <zephyr.h>
#include <debug/object_tracing.h>
#include <kernel_structs.h>
#include <util/mcumgr_util.h>

#include "tinycbor/cbor.h"
#include "cborattr/cborattr.h"
#include "mgmt/mgmt.h"
#include "os_mgmt/os_mgmt.h"
#include "os_mgmt/os_mgmt_impl.h"

/**
 * Command handler: os echo
 */
#if CONFIG_OS_MGMT_ECHO
static int
os_mgmt_echo(struct mgmt_ctxt *ctxt)
{
	char echo_buf[128];
	CborError err;

	const struct cbor_attr_t attrs[2] = {
		[0] = {
			.attribute = "d",
			.type = CborAttrTextStringType,
			.addr.string = echo_buf,
			.nodefault = 1,
			.len = sizeof(echo_buf),
		},
		[1] = {
			.attribute = NULL
		}
	};

	echo_buf[0] = '\0';

	err = cbor_read_object(&ctxt->it, attrs);
	if (err != 0) {
		return MGMT_ERR_EINVAL;
	}

	err |= cbor_encode_text_stringz(&ctxt->encoder, "r");
	err |= cbor_encode_text_string(&ctxt->encoder, echo_buf, strlen(echo_buf));

	if (err != 0) {
		return MGMT_ERR_ENOMEM;
	}

	return 0;
}
#endif

#if CONFIG_OS_MGMT_TASKSTAT
static inline CborError
os_mgmt_taskstat_encode_thread_name(struct CborEncoder *encoder,
				    const struct k_thread *thread)
{
	CborError err = 0;

#ifdef CONFIG_THREAD_NAME
	err |= cbor_encode_text_stringz(encoder, thread->name);
#else
	char thread_name[OS_MGMT_TASK_NAME_LEN];

	thread_name[OS_MGMT_TASK_NAME_LEN - 1] = 0;
	ll_to_s((int)thread->base.prio, sizeof(thread_name) - 1, thread_name);
	err |= cbor_encode_text_stringz(encoder, thread_name);
#endif /* CONFIG_THREAD_NAME */

	return err;
}

static inline CborError
os_mgmt_taskstat_encode_stack_info(struct CborEncoder *thread_map,
				   const struct k_thread *thread)
{
	ssize_t stack_size = 0;
	ssize_t stack_used = 0;
	CborError err = 0;

#ifdef CONFIG_THREAD_STACK_INFO
	stack_size = thread->stack_info.size / 4;

#ifdef CONFIG_INIT_STACKS
	unsigned int stack_unused;

	if (k_thread_stack_space_get(thread, &stack_unused) == 0) {
		stack_used = (thread->stack_info.size - stack_unused) / 4;
	}
#endif /* CONFIG_INIT_STACKS */
#endif /* CONFIG_THREAD_STACK_INFO */

	err |= cbor_encode_text_stringz(thread_map, "stksiz");
	err |= cbor_encode_uint(thread_map, stack_size);

	err |= cbor_encode_text_stringz(thread_map, "stkuse");
	err |= cbor_encode_uint(thread_map, stack_used);

	return err;
}

static inline CborError
os_mgmt_taskstat_encode_unsupported(struct CborEncoder *thread_map)
{
	CborError err = 0;

	if (!IS_ENABLED(CONFIG_OS_MGMT_TASKSTAT_ONLY_SUPPORTED_STATS)) {
		err |= cbor_encode_text_stringz(thread_map, "runtime");
		err |= cbor_encode_uint(thread_map, 0);
		err |= cbor_encode_text_stringz(thread_map, "cswcnt");
		err |= cbor_encode_uint(thread_map, 0);
		err |= cbor_encode_text_stringz(thread_map, "last_checkin");
		err |= cbor_encode_uint(thread_map, 0);
		err |= cbor_encode_text_stringz(thread_map, "next_checkin");
		err |= cbor_encode_uint(thread_map, 0);
	} else {
		ARG_UNUSED(thread_map);
	}

	return err;
}

/**
 * Encodes a single taskstat entry.
 */
static int
os_mgmt_taskstat_encode_one(struct CborEncoder *encoder, int idx, const struct k_thread *thread)
{
	CborEncoder thread_map;
	CborError err;

	err = 0;

	/*
	 * Threads are sent as map where thread name is key and value is map
	 * of thread parameters
	 */
	err |= os_mgmt_taskstat_encode_thread_name(encoder, thread);
	err |= cbor_encoder_create_map(encoder, &thread_map, CborIndefiniteLength);

	err |= cbor_encode_text_stringz(&thread_map, "prio");
	err |= cbor_encode_uint(&thread_map, (unsigned int)thread->base.prio & 0xff);

	err |= cbor_encode_text_stringz(&thread_map, "tid");
	err |= cbor_encode_uint(&thread_map, idx);

	err |= cbor_encode_text_stringz(&thread_map, "state");
	err |= cbor_encode_uint(&thread_map, thread->base.thread_state);

	err |= os_mgmt_taskstat_encode_stack_info(&thread_map, thread);

	err |= os_mgmt_taskstat_encode_unsupported(&thread_map);

	err |= cbor_encoder_close_container(encoder, &thread_map);

	if (err != 0) {
		return MGMT_ERR_ENOMEM;
	}

	return 0;
}

/**
 * Command handler: os taskstat
 */
static int os_mgmt_taskstat_read(struct mgmt_ctxt *ctxt)
{
	struct CborEncoder tasks_map;
	const struct k_thread *thread;
	CborError err;
	int thread_idx;

	err = 0;
	err |= cbor_encode_text_stringz(&ctxt->encoder, "tasks");
	err |= cbor_encoder_create_map(&ctxt->encoder, &tasks_map, CborIndefiniteLength);
	if (err != 0) {
		return MGMT_ERR_ENOMEM;
	}

	/* Iterate the list of tasks, encoding each. */
	thread = SYS_THREAD_MONITOR_HEAD;
	thread_idx = 0;
	while (thread != NULL) {
		err = os_mgmt_taskstat_encode_one(&tasks_map, thread_idx, thread);
		if (err != 0) {
			break;
		}

		thread = SYS_THREAD_MONITOR_NEXT(thread);
		++thread_idx;
	}

	err |= cbor_encoder_close_container(&ctxt->encoder, &tasks_map);

	return (err != 0) ? MGMT_ERR_ENOMEM : 0;
}
#endif /* CONFIG_OS_MGMT_TASKSTAT */

/**
 * Command handler: os reset
 */
static int
os_mgmt_reset(struct mgmt_ctxt *ctxt)
{
	return os_mgmt_impl_reset(CONFIG_OS_MGMT_RESET_MS);
}

static const struct mgmt_handler os_mgmt_group_handlers[] = {
#if CONFIG_OS_MGMT_ECHO
	[OS_MGMT_ID_ECHO] = {
		os_mgmt_echo, os_mgmt_echo
	},
#endif
#if CONFIG_OS_MGMT_TASKSTAT
	[OS_MGMT_ID_TASKSTAT] = {
		os_mgmt_taskstat_read, NULL
	},
#endif
	[OS_MGMT_ID_RESET] = {
		NULL, os_mgmt_reset
	},
};

#define OS_MGMT_GROUP_SZ ARRAY_SIZE(os_mgmt_group_handlers)

static struct mgmt_group os_mgmt_group = {
	.mg_handlers = os_mgmt_group_handlers,
	.mg_handlers_count = OS_MGMT_GROUP_SZ,
	.mg_group_id = MGMT_GROUP_ID_OS,
};


void
os_mgmt_register_group(void)
{
	mgmt_register_group(&os_mgmt_group);
}

void
os_mgmt_module_init(void)
{
	os_mgmt_register_group();
}
