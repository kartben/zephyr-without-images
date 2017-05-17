/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <uart.h>
#include <rom/uart.h>
#include <rom/ets_sys.h>
#include <errno.h>

static unsigned char esp32_uart_tx(struct device *dev,
				   unsigned char c)
{
	ARG_UNUSED(dev);

	uart_tx_one_char(c);

	return 0;
}

static int esp32_uart_rx(struct device *dev, unsigned char *p_char)
{
	ARG_UNUSED(dev);

	switch (uart_rx_one_char(p_char)) {
	case OK:
		return 0;
	case PENDING:
		return -EINPROGRESS;
	case BUSY:
		return -EBUSY;
	case CANCEL:
		return -ECANCELED;
	default:
		return -EIO;
	}
}

static int esp32_uart_init(struct device *dev)
{
	ARG_UNUSED(dev);

	uartAttach();

	return 0;
}

static const struct uart_driver_api esp32_uart_api = {
	.poll_in = &esp32_uart_rx,
	.poll_out = &esp32_uart_tx,
	.err_check = NULL,
#ifdef CONFIG_UART_INTERRUPT_DRIVEN

#error "Interrupt-driven ESP32 UART not implemented yet"

#endif
};

DEVICE_AND_API_INIT(esp32_uart, "ROMUART",
		    esp32_uart_init, NULL, NULL,
		    PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEVICE,
		    &esp32_uart_api);
