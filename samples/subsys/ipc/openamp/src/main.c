/*
 * Copyright (c) 2018, NXP
 * Copyright (c) 2018, Nordic Semiconductor ASA
 * Copyright (c) 2018-2019, Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/ipm.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zephyr/init.h>

#include <openamp/open_amp.h>

#include "common.h"

#define APP_TASK_STACK_SIZE (1024)
K_THREAD_STACK_DEFINE(thread_stack, APP_TASK_STACK_SIZE);
static struct k_thread thread_data;

static const struct device *const ipm_handle =
	DEVICE_DT_GET(DT_CHOSEN(zephyr_ipc));

static metal_phys_addr_t shm_physmap[] = { SHM_START_ADDR };

static volatile unsigned int received_data;

static struct virtio_vring_info rvrings[2] = {
	[0] = {
		.info.align = VRING_ALIGNMENT,
	},
	[1] = {
		.info.align = VRING_ALIGNMENT,
	},
};
static struct virtio_device vdev;
static struct rpmsg_virtio_device rvdev;
static struct metal_io_region shm_io_data;
static struct metal_io_region *io = &shm_io_data;
static struct virtqueue *vqueue[2];

static unsigned char ipc_virtio_get_status(struct virtio_device *dev)
{
	return VIRTIO_CONFIG_STATUS_DRIVER_OK;
}

static void ipc_virtio_set_status(struct virtio_device *dev, unsigned char status)
{
	sys_write8(status, VDEV_STATUS_ADDR);
}

static uint32_t ipc_virtio_get_features(struct virtio_device *dev)
{
	return 1 << VIRTIO_RPMSG_F_NS;
}

static void ipc_virtio_set_features(struct virtio_device *dev, uint32_t features)
{
}

static void ipc_virtio_notify(struct virtqueue *vq)
{
#if defined(CONFIG_SOC_MPS2_AN521) || \
	defined(CONFIG_SOC_V2M_MUSCA_B1)
	uint32_t current_core = sse_200_platform_get_cpu_id();

	ipm_send(ipm_handle, 0, current_core ? 0 : 1, 0, 1);
#else
	uint32_t dummy_data = 0x55005500; /* Some data must be provided */

	ipm_send(ipm_handle, 0, 0, &dummy_data, sizeof(dummy_data));
#endif /* #if defined(CONFIG_SOC_MPS2_AN521) */
}

struct virtio_dispatch dispatch = {
	.get_status = ipc_virtio_get_status,
	.set_status = ipc_virtio_set_status,
	.get_features = ipc_virtio_get_features,
	.set_features = ipc_virtio_set_features,
	.notify = ipc_virtio_notify,
};

static K_SEM_DEFINE(data_sem, 0, 1);
static K_SEM_DEFINE(data_rx_sem, 0, 1);

static void platform_ipm_callback(const struct device *dev, void *context,
				  uint32_t id, volatile void *data)
{
	k_sem_give(&data_sem);
}

int endpoint_cb(struct rpmsg_endpoint *ept, void *data,
		size_t len, uint32_t src, void *priv)
{
	received_data = *((unsigned int *) data);

	k_sem_give(&data_rx_sem);

	return RPMSG_SUCCESS;
}

static K_SEM_DEFINE(ept_sem, 0, 1);

struct rpmsg_endpoint my_ept;
struct rpmsg_endpoint *ep = &my_ept;

static void rpmsg_service_unbind(struct rpmsg_endpoint *ept)
{
	(void)ept;
	rpmsg_destroy_ept(ep);
}

void ns_bind_cb(struct rpmsg_device *rdev, const char *name, uint32_t dest)
{
	(void)rpmsg_create_ept(ep, rdev, name,
			RPMSG_ADDR_ANY, dest,
			endpoint_cb,
			rpmsg_service_unbind);

	k_sem_give(&ept_sem);
}

static unsigned int receive_message(void)
{
	while (k_sem_take(&data_rx_sem, K_NO_WAIT) != 0) {
		int status = k_sem_take(&data_sem, K_FOREVER);

		if (status == 0) {
			virtqueue_notification(vqueue[0]);
		}
	}
	return received_data;
}

static int send_message(unsigned int message)
{
	return rpmsg_send(ep, &message, sizeof(message));
}

static struct rpmsg_virtio_shm_pool shpool;

void app_task(void *arg1, void *arg2, void *arg3)
{
	ARG_UNUSED(arg1);
	ARG_UNUSED(arg2);
	ARG_UNUSED(arg3);

	int status = 0;
	unsigned int message = 0U;
	struct metal_init_params metal_params = METAL_INIT_DEFAULTS;

	printk("\r\nOpenAMP[master] demo started\r\n");

	status = metal_init(&metal_params);
	if (status != 0) {
		printk("metal_init: failed - error code %d\n", status);
		return;
	}

	/* declare shared memory region */
	metal_io_init(io, (void *)SHM_START_ADDR, shm_physmap, SHM_SIZE, -1, 0, NULL);

	/* setup IPM */
	if (!device_is_ready(ipm_handle)) {
		printk("IPM device is not ready\n");
		return;
	}

	ipm_register_callback(ipm_handle, platform_ipm_callback, NULL);

	status = ipm_set_enabled(ipm_handle, 1);
	if (status != 0) {
		printk("ipm_set_enabled failed\n");
		return;
	}

	/* setup vdev */
	vqueue[0] = virtqueue_allocate(VRING_SIZE);
	if (vqueue[0] == NULL) {
		printk("virtqueue_allocate failed to alloc vqueue[0]\n");
		return;
	}
	vqueue[1] = virtqueue_allocate(VRING_SIZE);
	if (vqueue[1] == NULL) {
		printk("virtqueue_allocate failed to alloc vqueue[1]\n");
		return;
	}

	vdev.role = RPMSG_HOST;
	vdev.vrings_num = VRING_COUNT;
	vdev.func = &dispatch;
	rvrings[0].io = io;
	rvrings[0].info.vaddr = (void *)VRING_TX_ADDRESS;
	rvrings[0].info.num_descs = VRING_SIZE;
	rvrings[0].info.align = VRING_ALIGNMENT;
	rvrings[0].vq = vqueue[0];

	rvrings[1].io = io;
	rvrings[1].info.vaddr = (void *)VRING_RX_ADDRESS;
	rvrings[1].info.num_descs = VRING_SIZE;
	rvrings[1].info.align = VRING_ALIGNMENT;
	rvrings[1].vq = vqueue[1];

	vdev.vrings_info = &rvrings[0];

	/* setup rvdev */
	rpmsg_virtio_init_shm_pool(&shpool, (void *)SHM_START_ADDR, SHM_SIZE);
	status = rpmsg_init_vdev(&rvdev, &vdev, ns_bind_cb, io, &shpool);
	if (status != 0) {
		printk("rpmsg_init_vdev failed %d\n", status);
		return;
	}

	/* Since we are using name service, we need to wait for a response
	 * from NS setup and than we need to process it
	 */
	k_sem_take(&data_sem, K_FOREVER);
	virtqueue_notification(vqueue[0]);

	/* Wait til nameservice ep is setup */
	k_sem_take(&ept_sem, K_FOREVER);

	while (message < 100) {
		status = send_message(message);
		if (status < 0) {
			printk("send_message(%d) failed with status %d\n",
			       message, status);
			goto _cleanup;
		}

		message = receive_message();
		printk("Master core received a message: %d\n", message);

		message++;
	}

_cleanup:
	rpmsg_deinit_vdev(&rvdev);
	metal_finish();

	printk("OpenAMP demo ended.\n");
}

int main(void)
{
	printk("Starting application thread!\n");
	k_thread_create(&thread_data, thread_stack, APP_TASK_STACK_SIZE,
			app_task,
			NULL, NULL, NULL, K_PRIO_COOP(7), 0, K_NO_WAIT);

#if defined(CONFIG_SOC_MPS2_AN521) || \
	defined(CONFIG_SOC_V2M_MUSCA_B1)
	wakeup_cpu1();
	k_msleep(500);
#endif /* #if defined(CONFIG_SOC_MPS2_AN521) */
	return 0;
}

/* Make sure we clear out the status flag very early (before we bringup the
 * secondary core) so the secondary core see's the proper status
 */
int init_status_flag(void)
{
	ipc_virtio_set_status(NULL, 0);

	return 0;
}

SYS_INIT(init_status_flag, PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
