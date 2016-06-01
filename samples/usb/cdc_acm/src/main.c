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

/**
 * @file
 * @brief Sample app for CDC ACM class driver
 *
 * Sample app for USB CDC ACM class driver. The received data is echoed back
 * to the serial port.
 */

#include <stdio.h>
#include <string.h>
#include <device.h>
#include <uart.h>
#include <zephyr.h>

#if defined(CONFIG_STDOUT_CONSOLE)
#include <stdio.h>
#define PRINT           printf
#else
#include <misc/printk.h>
#define PRINT           printk
#endif

static const char *banner1 = "Send characters to the UART device\r\n";
static const char *banner2 = "Characters read:\r\n";

static volatile bool data_transmitted;
static volatile bool data_arrived;
static	char data_buf[64];

static void interrupt_handler(struct device *dev)
{
	uart_irq_update(dev);

	if (uart_irq_tx_ready(dev)) {
		data_transmitted = true;
	}

	if (uart_irq_rx_ready(dev)) {
		data_arrived = true;
	}
}

static void read_data(struct device *dev, int *bytes_read)
{
	uart_irq_rx_enable(dev);

	data_arrived = false;
	while (data_arrived == false)
		;

	/* Read all data */
	*bytes_read = uart_fifo_read(dev, data_buf, sizeof(data_buf));

	uart_irq_rx_disable(dev);
}

static void write_data(struct device *dev, const char *buf, int len)
{
	uart_irq_tx_enable(dev);

	data_transmitted = false;
	uart_fifo_fill(dev, buf, len);
	while (data_transmitted == false)
		;

	uart_irq_tx_disable(dev);
}

void main(void)
{
	struct device *dev;
	uint32_t baudrate, bytes_read, dtr = 0;
	int ret;

	dev = device_get_binding(CONFIG_CDC_ACM_PORT_NAME);
	if (!dev) {
		PRINT("CDC ACM device not found\n");
		return;
	}

	PRINT("Wait for DTR\n");
	while (1) {
		uart_line_ctrl_get(dev, LINE_CTRL_DTR, &dtr);
		if (dtr)
			break;
	}
	PRINT("DTR set, start test\n");

	/* They are optional, we use them to test the interrupt endpoint */
	ret = uart_line_ctrl_set(dev, LINE_CTRL_DCD, 1);
	if (ret)
		PRINT("Failed to set DCD, ret code %d\n", ret);

	ret = uart_line_ctrl_set(dev, LINE_CTRL_DSR, 1);
	if (ret)
		PRINT("Failed to set DSR, ret code %d\n", ret);

	/* Wait 1 sec for the host to do all settings */
	sys_thread_busy_wait(1000000);

	ret = uart_line_ctrl_get(dev, LINE_CTRL_BAUD_RATE, &baudrate);
	if (ret)
		PRINT("Failed to get baudrate, ret code %d\n", ret);
	else
		PRINT("Baudrate detected: %d\n", baudrate);

	uart_irq_callback_set(dev, interrupt_handler);
	write_data(dev, banner1, strlen(banner1));
	write_data(dev, banner2, strlen(banner2));

	/* Echo the received data */
	while (1) {
		read_data(dev, &bytes_read);
		write_data(dev, data_buf, bytes_read);
	}
}
