/*
 * Copyright (c) 2021 EPAM Systems
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <arch/arm64/hypercall.h>
#include <xen/console.h>
#include <xen/events.h>
#include <xen/generic.h>
#include <xen/hvm.h>
#include <xen/public/io/console.h>
#include <xen/public/xen.h>

#include <device.h>
#include <init.h>
#include <kernel.h>
#include <logging/log.h>
#include <sys/device_mmio.h>

LOG_MODULE_REGISTER(uart_hvc_xen);

static struct hvc_xen_data hvc_data = {0};

static int read_from_ring(const struct device *dev, char *str, int len)
{
	int recv = 0;
	struct hvc_xen_data *hvc_data = dev->data;
	XENCONS_RING_IDX cons = hvc_data->intf->in_cons;
	XENCONS_RING_IDX prod = hvc_data->intf->in_prod;
	XENCONS_RING_IDX in_idx = 0;

	compiler_barrier();
	__ASSERT((prod - cons) <= sizeof(hvc_data->intf->in),
			"Invalid input ring buffer");

	while (cons != prod && recv < len) {
		in_idx = MASK_XENCONS_IDX(cons, hvc_data->intf->in);
		str[recv] = hvc_data->intf->in[in_idx];
		recv++;
		cons++;
	}

	compiler_barrier();
	hvc_data->intf->in_cons = cons;

	notify_evtchn(hvc_data->evtchn);
	return recv;
}

static int write_to_ring(const struct device *dev, const char *str, int len)
{
	int sent = 0;
	struct hvc_xen_data *hvc_data = dev->data;
	XENCONS_RING_IDX cons = hvc_data->intf->out_cons;
	XENCONS_RING_IDX prod = hvc_data->intf->out_prod;
	XENCONS_RING_IDX out_idx = 0;

	compiler_barrier();
	__ASSERT((prod - cons) <= sizeof(hvc_data->intf->out),
			"Invalid output ring buffer");

	while ((sent < len) && ((prod - cons) < sizeof(hvc_data->intf->out))) {
		out_idx = MASK_XENCONS_IDX(prod, hvc_data->intf->out);
		hvc_data->intf->out[out_idx] = str[sent];
		prod++;
		sent++;
	}

	compiler_barrier();
	hvc_data->intf->out_prod = prod;

	if (sent) {
		notify_evtchn(hvc_data->evtchn);
	}

	return sent;
}

static int xen_hvc_poll_in(const struct device *dev,
			unsigned char *c)
{
	int ret = 0;
	char temp;

	ret = read_from_ring(dev, &temp, sizeof(temp));
	if (!ret) {
		/* Char was not received */
		return -1;
	}

	*c = temp;
	return 0;
}

static void xen_hvc_poll_out(const struct device *dev,
			unsigned char c)
{
	/* Not a good solution (notifying HV every time), but needed for poll_out */
	(void) write_to_ring(dev, &c, sizeof(c));
}

static const struct uart_driver_api xen_hvc_api = {
	.poll_in = xen_hvc_poll_in,
	.poll_out = xen_hvc_poll_out,
};

int xen_console_init(const struct device *dev)
{
	int ret = 0;
	uint64_t console_pfn = 0;
	uintptr_t console_addr = 0;
	struct hvc_xen_data *data = dev->data;

	data->dev = dev;

	ret = hvm_get_parameter(HVM_PARAM_CONSOLE_EVTCHN, &data->evtchn);
	if (ret) {
		LOG_ERR("%s: failed to get Xen console evtchn, ret = %d\n",
				__func__, ret);
		return ret;
	}

	ret = hvm_get_parameter(HVM_PARAM_CONSOLE_PFN, &console_pfn);
	if (ret) {
		LOG_ERR("%s: failed to get Xen console PFN, ret = %d\n",
				__func__, ret);
		return ret;
	}

	console_addr = (uintptr_t) (console_pfn << XEN_PAGE_SHIFT);
	device_map(DEVICE_MMIO_RAM_PTR(dev), console_addr, XEN_PAGE_SIZE,
		K_MEM_CACHE_WB);

	data->intf = (struct xencons_interface *) DEVICE_MMIO_GET(dev);

	LOG_INF("Xen HVC inited successfully\n");

	return 0;
}

DEVICE_DT_DEFINE(DT_NODELABEL(xen_hvc), xen_console_init, NULL, &hvc_data,
		NULL, PRE_KERNEL_1, CONFIG_XEN_HVC_INIT_PRIORITY,
		&xen_hvc_api);

#ifdef CONFIG_XEN_EARLY_CONSOLEIO
extern void __printk_hook_install(int (*fn)(int));
extern void __stdout_hook_install(int (*fn)(int));

int xen_consoleio_putc(int c)
{
	char symbol = (char) c;

	HYPERVISOR_console_io(CONSOLEIO_write, sizeof(symbol), &symbol);
	return c;
}



int consoleio_hooks_set(const struct device *dev)
{
	ARG_UNUSED(dev);

	/* Will be replaced with poll_in/poll_out by uart_console.c later on boot */
	__stdout_hook_install(xen_consoleio_putc);
	__printk_hook_install(xen_consoleio_putc);

	return 0;
}

SYS_INIT(consoleio_hooks_set, PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
#endif /* CONFIG_XEN_EARLY_CONSOLEIO */
