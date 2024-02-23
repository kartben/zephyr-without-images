/*
 * Copyright 2024 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/mbox.h>

static K_SEM_DEFINE(g_mbox_data_rx_sem, 0, 1);

static uint32_t g_mbox_received_data;
static uint32_t g_mbox_received_channel;

static void callback(const struct device *dev, uint32_t channel, void *user_data,
		     struct mbox_msg *data)
{
	memcpy(&g_mbox_received_data, data->data, data->size);
	g_mbox_received_channel = channel;

	k_sem_give(&g_mbox_data_rx_sem);
}

int main(void)
{
	const struct mbox_channel tx_channel = MBOX_DT_CHANNEL_GET(DT_PATH(mbox_consumer), tx);
	const struct mbox_channel rx_channel = MBOX_DT_CHANNEL_GET(DT_PATH(mbox_consumer), rx);
	struct mbox_msg msg = {0};
	uint32_t message = 0;

	printk("mbox_data Server demo started\n");

	const int max_transfer_size_bytes = mbox_mtu_get(tx_channel.dev);
	/* Sample currently supports only transfer size up to 4 bytes */
	if ((max_transfer_size_bytes <= 0) || (max_transfer_size_bytes > 4)) {
		printk("mbox_mtu_get() error\n");
		return 0;
	}

	if (mbox_register_callback(&rx_channel, callback, NULL)) {
		printk("mbox_register_callback() error\n");
		return 0;
	}

	if (mbox_set_enabled(&rx_channel, 1)) {
		printk("mbox_set_enable() error\n");
		return 0;
	}

	while (message < 99) {
		k_sem_take(&g_mbox_data_rx_sem, K_FOREVER);
		message = g_mbox_received_data;

		printk("Server receive (on channel %d) value: %d\n", g_mbox_received_channel,
		       g_mbox_received_data);

		message++;

		msg.data = &message;
		msg.size = max_transfer_size_bytes;

		printk("Server send (on channel %d) value: %d\n", tx_channel.id, message);
		if (mbox_send(&tx_channel, &msg) < 0) {
			printk("mbox_send() error\n");
			return 0;
		}
	}

	printk("mbox_data Server demo ended.\n");
	return 0;
}
