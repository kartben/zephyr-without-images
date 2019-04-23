/*
 * Copyright (c) 2019 Intel Corporation.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <device.h>
#include <sys/libc-hooks.h>
#include <logging/log.h>

#include "main.h"
#include "app_b.h"

LOG_MODULE_REGISTER(app_b);

/* Resource pool for allocations made by the kernel on behalf of system
 * calls. Needed for k_queue_alloc_append()
 */
K_MEM_POOL_DEFINE(app_b_resource_pool, 32, 256, 4, 4);

/* Define app_b_partition, where all globals for this app will be routed.
 * The partition starting address and size are populated by build system
 * and linker magic.
 */
K_APPMEM_PARTITION_DEFINE(app_b_partition);

/* Memory domain for application B, set up and installed in app_a_entry() */
static struct k_mem_domain app_b_domain;

/* Global data used by application B. By tagging with APP_B_BSS or APP_B_DATA,
 * we ensure all this gets linked into the continuous region denoted by
 * app_b_partition.
 *
 * This is just for demonstration purposes, processor_thread could just as
 * easily put this on its stack.
 */
APP_B_BSS unsigned int process_count;

static void processor_thread(void *p1, void *p2, void *p3)
{
	void *payload;

	ARG_UNUSED(p1);
	ARG_UNUSED(p2);
	ARG_UNUSED(p3);

	LOG_DBG("processor thread entered");

	/* Pretend that processor_thread takes some initialization time,
	 * meanwhile data coming in from the driver will be buffered in the
	 * incoming queue/
	 */
	k_sleep(4000);

	/* Consume data blobs from shared_queue_incoming.
	 * Do some processing, and the put the processed data
	 * into shared_queue_outgoing.
	 */
	while (process_count < NUM_LOOPS) {
		payload = k_queue_get(&shared_queue_incoming, K_FOREVER);

		/* pretend we're doing something complicated and useful
		 * to the data, which is untrusted and hence processed in
		 * a sandboxed App B
		 */
		LOG_DBG("processing payload #%d", process_count);
		k_busy_wait(1000000);
		process_count++;
		LOG_INF("processing payload #%d complete", process_count);

		/* Stick the now-processed data into the outgoing queue,
		 * to be handled by App A's writeback thread.
		 */
		k_queue_alloc_append(&shared_queue_outgoing, payload);
	}

	LOG_DBG("processor thread exiting");
}

void app_b_entry(void *p1, void *p2, void *p3)
{
	struct k_mem_partition *parts[] = {
#if Z_LIBC_PARTITION_EXISTS
		&z_libc_partition,
#endif
		&app_b_partition, &shared_partition
	};

	/* Initialize a memory domain with the specified partitions
	 * and add ourself to this domain. We need access to our own
	 * partition, the shared partition, and any common libc partition
	 * if it exists.
	 */
	k_mem_domain_init(&app_b_domain, ARRAY_SIZE(parts), parts);
	k_mem_domain_add_thread(&app_b_domain, k_current_get());

	/* Assign a resource pool to serve for kernel-side allocations on
	 * behalf of application A. Needed for k_queue_alloc_append().
	 */
	k_thread_resource_pool_assign(k_current_get(), &app_b_resource_pool);

	/* We are about to drop to user mode and become the monitor thread.
	 * Grant ourselves access to the kernel objects we need for
	 * the monitor thread to function.
	 *
	 * In this case, we need access to both shared queue objects. We
	 * don't need access to the sample driver, App A handles all that
	 * for us.
	 */
	k_thread_access_grant(k_current_get(), &shared_queue_incoming,
			      &shared_queue_outgoing);

	k_thread_user_mode_enter(processor_thread, NULL, NULL, NULL);
}
