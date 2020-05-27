/*
 * Copyright (c) 2017, Christian Taedcke
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>
#include <drivers/uart.h>
#include <em_usart.h>
#include <em_gpio.h>
#include <em_cmu.h>
#include <soc.h>

#define USART_PREFIX cmuClock_USART
#define UART_PREFIX cmuClock_UART
#define CLOCK_ID_PRFX2(prefix, suffix) prefix##suffix
#define CLOCK_ID_PRFX(prefix, suffix) CLOCK_ID_PRFX2(prefix, suffix)
#define CLOCK_USART(id) CLOCK_ID_PRFX(USART_PREFIX, id)
#define CLOCK_UART(id) CLOCK_ID_PRFX(UART_PREFIX, id)

struct uart_gecko_config {
	USART_TypeDef *base;
	CMU_Clock_TypeDef clock;
	uint32_t baud_rate;
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	void (*irq_config_func)(struct device *dev);
#endif
	struct soc_gpio_pin pin_rx;
	struct soc_gpio_pin pin_tx;
#ifdef CONFIG_SOC_GECKO_HAS_INDIVIDUAL_PIN_LOCATION
	uint8_t loc_rx;
	uint8_t loc_tx;
#else
	uint8_t loc;
#endif
};

struct uart_gecko_data {
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	uart_irq_callback_user_data_t callback;
	void *cb_data;
#endif
};

static int uart_gecko_poll_in(struct device *dev, unsigned char *c)
{
	const struct uart_gecko_config *config = dev->config_info;
	uint32_t flags = USART_StatusGet(config->base);

	if (flags & USART_STATUS_RXDATAV) {
		*c = USART_Rx(config->base);
		return 0;
	}

	return -1;
}

static void uart_gecko_poll_out(struct device *dev, unsigned char c)
{
	const struct uart_gecko_config *config = dev->config_info;

	USART_Tx(config->base, c);
}

static int uart_gecko_err_check(struct device *dev)
{
	const struct uart_gecko_config *config = dev->config_info;
	uint32_t flags = USART_IntGet(config->base);
	int err = 0;

	if (flags & USART_IF_RXOF) {
		err |= UART_ERROR_OVERRUN;
	}

	if (flags & USART_IF_PERR) {
		err |= UART_ERROR_PARITY;
	}

	if (flags & USART_IF_FERR) {
		err |= UART_ERROR_FRAMING;
	}

	USART_IntClear(config->base, USART_IF_RXOF |
		       USART_IF_PERR |
		       USART_IF_FERR);

	return err;
}

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
static int uart_gecko_fifo_fill(struct device *dev, const uint8_t *tx_data,
			       int len)
{
	const struct uart_gecko_config *config = dev->config_info;
	uint8_t num_tx = 0U;

	while ((len - num_tx > 0) &&
	       (config->base->STATUS & USART_STATUS_TXBL)) {

		config->base->TXDATA = (uint32_t)tx_data[num_tx++];
	}

	return num_tx;
}

static int uart_gecko_fifo_read(struct device *dev, uint8_t *rx_data,
			       const int len)
{
	const struct uart_gecko_config *config = dev->config_info;
	uint8_t num_rx = 0U;

	while ((len - num_rx > 0) &&
	       (config->base->STATUS & USART_STATUS_RXDATAV)) {

		rx_data[num_rx++] = (uint8_t)config->base->RXDATA;
	}

	return num_rx;
}

static void uart_gecko_irq_tx_enable(struct device *dev)
{
	const struct uart_gecko_config *config = dev->config_info;
	uint32_t mask = USART_IEN_TXBL | USART_IEN_TXC;

	USART_IntEnable(config->base, mask);
}

static void uart_gecko_irq_tx_disable(struct device *dev)
{
	const struct uart_gecko_config *config = dev->config_info;
	uint32_t mask = USART_IEN_TXBL | USART_IEN_TXC;

	USART_IntDisable(config->base, mask);
}

static int uart_gecko_irq_tx_complete(struct device *dev)
{
	const struct uart_gecko_config *config = dev->config_info;
	uint32_t flags = USART_IntGet(config->base);

	USART_IntClear(config->base, USART_IF_TXC);

	return (flags & USART_IF_TXC) != 0U;
}

static int uart_gecko_irq_tx_ready(struct device *dev)
{
	const struct uart_gecko_config *config = dev->config_info;
	uint32_t flags = USART_IntGet(config->base);

	return (flags & USART_IF_TXBL) != 0U;
}

static void uart_gecko_irq_rx_enable(struct device *dev)
{
	const struct uart_gecko_config *config = dev->config_info;
	uint32_t mask = USART_IEN_RXDATAV;

	USART_IntEnable(config->base, mask);
}

static void uart_gecko_irq_rx_disable(struct device *dev)
{
	const struct uart_gecko_config *config = dev->config_info;
	uint32_t mask = USART_IEN_RXDATAV;

	USART_IntDisable(config->base, mask);
}

static int uart_gecko_irq_rx_full(struct device *dev)
{
	const struct uart_gecko_config *config = dev->config_info;
	uint32_t flags = USART_IntGet(config->base);

	return (flags & USART_IF_RXDATAV) != 0U;
}

static int uart_gecko_irq_rx_ready(struct device *dev)
{
	const struct uart_gecko_config *config = dev->config_info;
	uint32_t mask = USART_IEN_RXDATAV;

	return (config->base->IEN & mask)
		&& uart_gecko_irq_rx_full(dev);
}

static void uart_gecko_irq_err_enable(struct device *dev)
{
	const struct uart_gecko_config *config = dev->config_info;

	USART_IntEnable(config->base, USART_IF_RXOF |
			 USART_IF_PERR |
			 USART_IF_FERR);
}

static void uart_gecko_irq_err_disable(struct device *dev)
{
	const struct uart_gecko_config *config = dev->config_info;

	USART_IntDisable(config->base, USART_IF_RXOF |
			 USART_IF_PERR |
			 USART_IF_FERR);
}

static int uart_gecko_irq_is_pending(struct device *dev)
{
	return uart_gecko_irq_tx_ready(dev) || uart_gecko_irq_rx_ready(dev);
}

static int uart_gecko_irq_update(struct device *dev)
{
	return 1;
}

static void uart_gecko_irq_callback_set(struct device *dev,
				       uart_irq_callback_user_data_t cb,
				       void *cb_data)
{
	struct uart_gecko_data *data = dev->driver_data;

	data->callback = cb;
	data->cb_data = cb_data;
}

static void uart_gecko_isr(void *arg)
{
	struct device *dev = arg;
	struct uart_gecko_data *data = dev->driver_data;

	if (data->callback) {
		data->callback(data->cb_data);
	}
}
#endif /* CONFIG_UART_INTERRUPT_DRIVEN */

static void uart_gecko_init_pins(struct device *dev)
{
	const struct uart_gecko_config *config = dev->config_info;

	soc_gpio_configure(&config->pin_rx);
	soc_gpio_configure(&config->pin_tx);
#ifdef CONFIG_SOC_GECKO_HAS_INDIVIDUAL_PIN_LOCATION
	config->base->ROUTEPEN = USART_ROUTEPEN_RXPEN | USART_ROUTEPEN_TXPEN;
	config->base->ROUTELOC0 =
		(config->loc_tx << _USART_ROUTELOC0_TXLOC_SHIFT) |
		(config->loc_rx << _USART_ROUTELOC0_RXLOC_SHIFT);
	config->base->ROUTELOC1 = _USART_ROUTELOC1_RESETVALUE;
#else
	config->base->ROUTE = USART_ROUTE_RXPEN | USART_ROUTE_TXPEN
		| (config->loc << 8);
#endif
}

static int uart_gecko_init(struct device *dev)
{
	const struct uart_gecko_config *config = dev->config_info;
	USART_InitAsync_TypeDef usartInit = USART_INITASYNC_DEFAULT;

	/* The peripheral and gpio clock are already enabled from soc and gpio
	 * driver
	 */

	usartInit.baudrate = config->baud_rate;

	/* Enable USART clock */
	CMU_ClockEnable(config->clock, true);

	/* Init USART */
	USART_InitAsync(config->base, &usartInit);

	/* Initialize USART pins */
	uart_gecko_init_pins(dev);

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	config->irq_config_func(dev);
#endif

	return 0;
}

static const struct uart_driver_api uart_gecko_driver_api = {
	.poll_in = uart_gecko_poll_in,
	.poll_out = uart_gecko_poll_out,
	.err_check = uart_gecko_err_check,
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	.fifo_fill = uart_gecko_fifo_fill,
	.fifo_read = uart_gecko_fifo_read,
	.irq_tx_enable = uart_gecko_irq_tx_enable,
	.irq_tx_disable = uart_gecko_irq_tx_disable,
	.irq_tx_complete = uart_gecko_irq_tx_complete,
	.irq_tx_ready = uart_gecko_irq_tx_ready,
	.irq_rx_enable = uart_gecko_irq_rx_enable,
	.irq_rx_disable = uart_gecko_irq_rx_disable,
	.irq_rx_ready = uart_gecko_irq_rx_ready,
	.irq_err_enable = uart_gecko_irq_err_enable,
	.irq_err_disable = uart_gecko_irq_err_disable,
	.irq_is_pending = uart_gecko_irq_is_pending,
	.irq_update = uart_gecko_irq_update,
	.irq_callback_set = uart_gecko_irq_callback_set,
#endif
};

#define DT_DRV_COMPAT silabs_gecko_uart

#if DT_NODE_HAS_STATUS(DT_DRV_INST(0), okay)

#define PIN_UART0_RXD {DT_INST_PROP_BY_IDX(0, location_rx, 1), \
		DT_INST_PROP_BY_IDX(0, location_rx, 2), gpioModeInput, 1}
#define PIN_UART0_TXD {DT_INST_PROP_BY_IDX(0, location_tx, 1), \
		DT_INST_PROP_BY_IDX(0, location_tx, 2), gpioModePushPull, 1}

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
static void uart_gecko_config_func_0(struct device *dev);
#endif

static const struct uart_gecko_config uart_gecko_0_config = {
	.base = (USART_TypeDef *)DT_INST_REG_ADDR(0),
	.clock = CLOCK_UART(DT_INST_PROP(0, peripheral_id)),
	.baud_rate = DT_INST_PROP(0, current_speed),
	.pin_rx = PIN_UART0_RXD,
	.pin_tx = PIN_UART0_TXD,
#ifdef CONFIG_SOC_GECKO_HAS_INDIVIDUAL_PIN_LOCATION
	.loc_rx = DT_INST_PROP_BY_IDX(0, location_rx, 0),
	.loc_tx = DT_INST_PROP_BY_IDX(0, location_tx, 0),
#else
#if DT_INST_PROP_BY_IDX(0, location_rx, 0) \
	!= DT_INST_PROP_BY_IDX(0, location_tx, 0)
#error UART_0 DTS location-* properties must have identical value
#endif
	.loc = DT_INST_PROP_BY_IDX(0, location_rx, 0),
#endif
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	.irq_config_func = uart_gecko_config_func_0,
#endif
};

static struct uart_gecko_data uart_gecko_0_data;

DEVICE_AND_API_INIT(uart_0, DT_INST_LABEL(0), &uart_gecko_init,
		    &uart_gecko_0_data, &uart_gecko_0_config, PRE_KERNEL_1,
		    CONFIG_KERNEL_INIT_PRIORITY_DEVICE, &uart_gecko_driver_api);

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
static void uart_gecko_config_func_0(struct device *dev)
{
	IRQ_CONNECT(DT_INST_IRQ_BY_NAME(0, rx, irq),
		    DT_INST_IRQ_BY_NAME(0, rx, priority), uart_gecko_isr,
		    DEVICE_GET(uart_0), 0);
	IRQ_CONNECT(DT_INST_IRQ_BY_NAME(0, tx, irq),
		    DT_INST_IRQ_BY_NAME(0, tx, priority), uart_gecko_isr,
		    DEVICE_GET(uart_0), 0);

	irq_enable(DT_INST_IRQ_BY_NAME(0, rx, irq));
	irq_enable(DT_INST_IRQ_BY_NAME(0, tx, irq));
}
#endif

#endif /* DT_NODE_HAS_STATUS(DT_DRV_INST(0), okay) */

#if DT_NODE_HAS_STATUS(DT_DRV_INST(1), okay)

#define PIN_UART1_RXD {DT_INST_PROP_BY_IDX(1, location_rx, 1), \
		DT_INST_PROP_BY_IDX(1, location_rx, 2), gpioModeInput, 1}
#define PIN_UART1_TXD {DT_INST_PROP_BY_IDX(1, location_tx, 1), \
		DT_INST_PROP_BY_IDX(1, location_tx, 2), gpioModePushPull, 1}

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
static void uart_gecko_config_func_1(struct device *dev);
#endif

static const struct uart_gecko_config uart_gecko_1_config = {
	.base = (USART_TypeDef *)DT_INST_REG_ADDR(1),
	.clock = CLOCK_UART(DT_INST_PROP(1, peripheral_id)),
	.baud_rate = DT_INST_PROP(1, current_speed),
	.pin_rx = PIN_UART1_RXD,
	.pin_tx = PIN_UART1_TXD,
#ifdef CONFIG_SOC_GECKO_HAS_INDIVIDUAL_PIN_LOCATION
	.loc_rx = DT_INST_PROP_BY_IDX(1, location_rx, 0),
	.loc_tx = DT_INST_PROP_BY_IDX(1, location_tx, 0),
#else
#if DT_INST_PROP_BY_IDX(1, location_rx, 0) \
	!= DT_INST_PROP_BY_IDX(1, location_tx, 0)
#error UART_1 DTS location-* properties must have identical value
#endif
	.loc = DT_INST_PROP_BY_IDX(1, location_rx, 0),
#endif
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	.irq_config_func = uart_gecko_config_func_1,
#endif
};

static struct uart_gecko_data uart_gecko_1_data;

DEVICE_AND_API_INIT(uart_1, DT_INST_LABEL(1), &uart_gecko_init,
		    &uart_gecko_1_data, &uart_gecko_1_config, PRE_KERNEL_1,
		    CONFIG_KERNEL_INIT_PRIORITY_DEVICE, &uart_gecko_driver_api);

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
static void uart_gecko_config_func_1(struct device *dev)
{
	IRQ_CONNECT(DT_INST_IRQ_BY_NAME(1, rx, irq),
		    DT_INST_IRQ_BY_NAME(1, rx, priority), uart_gecko_isr,
		    DEVICE_GET(uart_1), 0);
	IRQ_CONNECT(DT_INST_IRQ_BY_NAME(1, tx, irq),
		    DT_INST_IRQ_BY_NAME(1, tx, priority), uart_gecko_isr,
		    DEVICE_GET(uart_1), 0);

	irq_enable(DT_INST_IRQ_BY_NAME(1, rx, irq));
	irq_enable(DT_INST_IRQ_BY_NAME(1, tx, irq));
}
#endif

#endif /* DT_NODE_HAS_STATUS(DT_DRV_INST(1), okay) */

#undef DT_DRV_COMPAT
#define DT_DRV_COMPAT silabs_gecko_usart

#if DT_NODE_HAS_STATUS(DT_DRV_INST(0), okay)

#define PIN_USART0_RXD {DT_INST_PROP_BY_IDX(0, location_rx, 1), \
		DT_INST_PROP_BY_IDX(0, location_rx, 2), gpioModeInput, 1}
#define PIN_USART0_TXD {DT_INST_PROP_BY_IDX(0, location_tx, 1), \
		DT_INST_PROP_BY_IDX(0, location_tx, 2), gpioModePushPull, 1}

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
static void usart_gecko_config_func_0(struct device *dev);
#endif

static const struct uart_gecko_config usart_gecko_0_config = {
	.base = (USART_TypeDef *)DT_INST_REG_ADDR(0),
	.clock = CLOCK_USART(DT_INST_PROP(0, peripheral_id)),
	.baud_rate = DT_INST_PROP(0, current_speed),
	.pin_rx = PIN_USART0_RXD,
	.pin_tx = PIN_USART0_TXD,
#ifdef CONFIG_SOC_GECKO_HAS_INDIVIDUAL_PIN_LOCATION
	.loc_rx = DT_INST_PROP_BY_IDX(0, location_rx, 0),
	.loc_tx = DT_INST_PROP_BY_IDX(0, location_tx, 0),
#else
#if DT_INST_PROP_BY_IDX(0, location_rx, 0) \
	!= DT_INST_PROP_BY_IDX(0, location_tx, 0)
#error USART_0 DTS location-* properties must have identical value
#endif
	.loc = DT_INST_PROP_BY_IDX(0, location_rx, 0),
#endif
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	.irq_config_func = usart_gecko_config_func_0,
#endif
};

static struct uart_gecko_data usart_gecko_0_data;

DEVICE_AND_API_INIT(usart_0, DT_INST_LABEL(0),
		    &uart_gecko_init, &usart_gecko_0_data,
		    &usart_gecko_0_config, PRE_KERNEL_1,
		    CONFIG_KERNEL_INIT_PRIORITY_DEVICE, &uart_gecko_driver_api);

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
static void usart_gecko_config_func_0(struct device *dev)
{
	IRQ_CONNECT(DT_INST_IRQ_BY_NAME(0, rx, irq),
		    DT_INST_IRQ_BY_NAME(0, rx, priority),
		    uart_gecko_isr, DEVICE_GET(usart_0), 0);
	IRQ_CONNECT(DT_INST_IRQ_BY_NAME(0, tx, irq),
		    DT_INST_IRQ_BY_NAME(0, tx, priority),
		    uart_gecko_isr, DEVICE_GET(usart_0), 0);

	irq_enable(DT_INST_IRQ_BY_NAME(0, rx, irq));
	irq_enable(DT_INST_IRQ_BY_NAME(0, tx, irq));
}
#endif

#endif /* DT_NODE_HAS_STATUS(DT_DRV_INST(0), okay) */

#if DT_NODE_HAS_STATUS(DT_DRV_INST(1), okay)

#define PIN_USART1_RXD {DT_INST_PROP_BY_IDX(1, location_rx, 1), \
		DT_INST_PROP_BY_IDX(1, location_rx, 2), gpioModeInput, 1}
#define PIN_USART1_TXD {DT_INST_PROP_BY_IDX(1, location_tx, 1), \
		DT_INST_PROP_BY_IDX(1, location_tx, 2), gpioModePushPull, 1}

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
static void usart_gecko_config_func_1(struct device *dev);
#endif

static const struct uart_gecko_config usart_gecko_1_config = {
	.base = (USART_TypeDef *)DT_INST_REG_ADDR(1),
	.clock = CLOCK_USART(DT_INST_PROP(1, peripheral_id)),
	.baud_rate = DT_INST_PROP(1, current_speed),
	.pin_rx = PIN_USART1_RXD,
	.pin_tx = PIN_USART1_TXD,
#ifdef CONFIG_SOC_GECKO_HAS_INDIVIDUAL_PIN_LOCATION
	.loc_rx = DT_INST_PROP_BY_IDX(1, location_rx, 0),
	.loc_tx = DT_INST_PROP_BY_IDX(1, location_tx, 0),
#else
#if DT_INST_PROP_BY_IDX(1, location_rx, 0) \
	!= DT_INST_PROP_BY_IDX(1, location_tx, 0)
#error USART_1 DTS location-* properties must have identical value
#endif
	.loc = DT_INST_PROP_BY_IDX(1, location_rx, 0),
#endif
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	.irq_config_func = usart_gecko_config_func_1,
#endif
};

static struct uart_gecko_data usart_gecko_1_data;

DEVICE_AND_API_INIT(usart_1, DT_INST_LABEL(1),
		    &uart_gecko_init, &usart_gecko_1_data,
		    &usart_gecko_1_config, PRE_KERNEL_1,
		    CONFIG_KERNEL_INIT_PRIORITY_DEVICE, &uart_gecko_driver_api);

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
static void usart_gecko_config_func_1(struct device *dev)
{
	IRQ_CONNECT(DT_INST_IRQ_BY_NAME(1, rx, irq),
		    DT_INST_IRQ_BY_NAME(1, rx, priority),
		    uart_gecko_isr, DEVICE_GET(usart_1), 0);
	IRQ_CONNECT(DT_INST_IRQ_BY_NAME(1, tx, irq),
		    DT_INST_IRQ_BY_NAME(1, tx, priority),
		    uart_gecko_isr, DEVICE_GET(usart_1), 0);

	irq_enable(DT_INST_IRQ_BY_NAME(1, rx, irq));
	irq_enable(DT_INST_IRQ_BY_NAME(1, tx, irq));
}
#endif

#endif /* DT_NODE_HAS_STATUS(DT_DRV_INST(1), okay) */

#if DT_NODE_HAS_STATUS(DT_DRV_INST(2), okay)

#define PIN_USART2_RXD {DT_INST_PROP_BY_IDX(2, location_rx, 1), \
		DT_INST_PROP_BY_IDX(2, location_rx, 2), gpioModeInput, 1}
#define PIN_USART2_TXD {DT_INST_PROP_BY_IDX(2, location_tx, 1), \
		DT_INST_PROP_BY_IDX(2, location_tx, 2), gpioModePushPull, 1}

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
static void usart_gecko_config_func_2(struct device *dev);
#endif

static const struct uart_gecko_config usart_gecko_2_config = {
	.base = (USART_TypeDef *)DT_INST_REG_ADDR(2),
	.clock = CLOCK_USART(DT_INST_PROP(2, peripheral_id)),
	.baud_rate = DT_INST_PROP(2, current_speed),
	.pin_rx = PIN_USART2_RXD,
	.pin_tx = PIN_USART2_TXD,
#ifdef CONFIG_SOC_GECKO_HAS_INDIVIDUAL_PIN_LOCATION
	.loc_rx = DT_INST_PROP_BY_IDX(2, location_rx, 0),
	.loc_tx = DT_INST_PROP_BY_IDX(2, location_tx, 0),
#else
#if DT_INST_PROP_BY_IDX(2, location_rx, 0) \
	!= DT_INST_PROP_BY_IDX(2, location_tx, 0)
#error USART_2 DTS location-* properties must have identical value
#endif
	.loc = DT_INST_PROP_BY_IDX(2, location_rx, 0),
#endif
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	.irq_config_func = usart_gecko_config_func_2,
#endif
};

static struct uart_gecko_data usart_gecko_2_data;

DEVICE_AND_API_INIT(usart_2, DT_INST_LABEL(2),
		    &uart_gecko_init, &usart_gecko_2_data,
		    &usart_gecko_2_config, PRE_KERNEL_1,
		    CONFIG_KERNEL_INIT_PRIORITY_DEVICE, &uart_gecko_driver_api);

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
static void usart_gecko_config_func_2(struct device *dev)
{
	IRQ_CONNECT(DT_INST_IRQ_BY_NAME(2, rx, irq),
		    DT_INST_IRQ_BY_NAME(2, rx, priority),
		    uart_gecko_isr, DEVICE_GET(usart_2), 0);
	IRQ_CONNECT(DT_INST_IRQ_BY_NAME(2, tx, irq),
		    DT_INST_IRQ_BY_NAME(2, tx, priority),
		    uart_gecko_isr, DEVICE_GET(usart_2), 0);

	irq_enable(DT_INST_IRQ_BY_NAME(2, rx, irq));
	irq_enable(DT_INST_IRQ_BY_NAME(2, tx, irq));
}
#endif

#endif /* DT_NODE_HAS_STATUS(DT_DRV_INST(2), okay) */

#if DT_NODE_HAS_STATUS(DT_DRV_INST(3), okay)

#define PIN_USART3_RXD {DT_INST_PROP_BY_IDX(3, location_rx, 1), \
		DT_INST_PROP_BY_IDX(3, location_rx, 2), gpioModeInput, 1}
#define PIN_USART3_TXD {DT_INST_PROP_BY_IDX(3, location_tx, 1), \
		DT_INST_PROP_BY_IDX(3, location_tx, 2), gpioModePushPull, 1}

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
static void usart_gecko_config_func_3(struct device *dev);
#endif

static const struct uart_gecko_config usart_gecko_3_config = {
	.base = (USART_TypeDef *)DT_INST_REG_ADDR(3),
	.clock = CLOCK_USART(DT_INST_PROP(3, peripheral_id)),
	.baud_rate = DT_INST_PROP(3, current_speed),
	.pin_rx = PIN_USART3_RXD,
	.pin_tx = PIN_USART3_TXD,
#ifdef CONFIG_SOC_GECKO_HAS_INDIVIDUAL_PIN_LOCATION
	.loc_rx = DT_INST_PROP_BY_IDX(3, location_rx, 0),
	.loc_tx = DT_INST_PROP_BY_IDX(3, location_tx, 0),
#else
#if DT_INST_PROP_BY_IDX(3, location_rx, 0) \
	!= DT_INST_PROP_BY_IDX(3, location_tx, 0)
#error USART_3 DTS location-* properties must have identical value
#endif
	.loc = DT_INST_PROP_BY_IDX(3, location_rx, 0),
#endif
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	.irq_config_func = usart_gecko_config_func_3,
#endif
};

static struct uart_gecko_data usart_gecko_3_data;

DEVICE_AND_API_INIT(usart_3, DT_INST_LABEL(3),
		    &uart_gecko_init, &usart_gecko_3_data,
		    &usart_gecko_3_config, PRE_KERNEL_1,
		    CONFIG_KERNEL_INIT_PRIORITY_DEVICE, &uart_gecko_driver_api);

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
static void usart_gecko_config_func_3(struct device *dev)
{
	IRQ_CONNECT(DT_INST_IRQ_BY_NAME(3, rx, irq),
		    DT_INST_IRQ_BY_NAME(3, rx, priority),
		    uart_gecko_isr, DEVICE_GET(usart_3), 0);
	IRQ_CONNECT(DT_INST_IRQ_BY_NAME(3, tx, irq),
		    DT_INST_IRQ_BY_NAME(3, tx, priority),
		    uart_gecko_isr, DEVICE_GET(usart_3), 0);

	irq_enable(DT_INST_IRQ_BY_NAME(3, rx, irq));
	irq_enable(DT_INST_IRQ_BY_NAME(3, tx, irq));
}
#endif

#endif /* DT_NODE_HAS_STATUS(DT_DRV_INST(3), okay) */

#if DT_NODE_HAS_STATUS(DT_DRV_INST(4), okay)

#define PIN_USART4_RXD {DT_INST_PROP_BY_IDX(4, location_rx, 1), \
		DT_INST_PROP_BY_IDX(4, location_rx, 2), gpioModeInput, 1}
#define PIN_USART4_TXD {DT_INST_PROP_BY_IDX(4, location_tx, 1), \
		DT_INST_PROP_BY_IDX(4, location_tx, 2), gpioModePushPull, 1}

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
static void usart_gecko_config_func_4(struct device *dev);
#endif

static const struct uart_gecko_config usart_gecko_4_config = {
	.base = (USART_TypeDef *)DT_INST_REG_ADDR(4),
	.clock = CLOCK_USART(DT_INST_PROP(4, peripheral_id)),
	.baud_rate = DT_INST_PROP(4, current_speed),
	.pin_rx = PIN_USART4_RXD,
	.pin_tx = PIN_USART4_TXD,
#ifdef CONFIG_SOC_GECKO_HAS_INDIVIDUAL_PIN_LOCATION
	.loc_rx = DT_INST_PROP_BY_IDX(4, location_rx, 0),
	.loc_tx = DT_INST_PROP_BY_IDX(4, location_tx, 0),
#else
#if DT_INST_PROP_BY_IDX(4, location_rx, 0) \
	!= DT_INST_PROP_BY_IDX(4, location_tx, 0)
#error USART_4 DTS location-* properties must have identical value
#endif
	.loc = DT_INST_PROP_BY_IDX(4, location_rx, 0),
#endif
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	.irq_config_func = usart_gecko_config_func_4,
#endif
};

static struct uart_gecko_data usart_gecko_4_data;

DEVICE_AND_API_INIT(usart_4, DT_INST_LABEL(4),
		    &uart_gecko_init, &usart_gecko_4_data,
		    &usart_gecko_4_config, PRE_KERNEL_1,
		    CONFIG_KERNEL_INIT_PRIORITY_DEVICE, &uart_gecko_driver_api);

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
static void usart_gecko_config_func_4(struct device *dev)
{
	IRQ_CONNECT(DT_INST_IRQ_BY_NAME(4, rx, irq),
		    DT_INST_IRQ_BY_NAME(4, rx, priority),
		    uart_gecko_isr, DEVICE_GET(usart_4), 0);
	IRQ_CONNECT(DT_INST_IRQ_BY_NAME(4, tx, irq),
		    DT_INST_IRQ_BY_NAME(4, tx, priority),
		    uart_gecko_isr, DEVICE_GET(usart_4), 0);

	irq_enable(DT_INST_IRQ_BY_NAME(4, rx, irq));
	irq_enable(DT_INST_IRQ_BY_NAME(4, tx, irq));
}
#endif

#endif /* DT_NODE_HAS_STATUS(DT_DRV_INST(4), okay) */

#if DT_NODE_HAS_STATUS(DT_DRV_INST(5), okay)

#define PIN_USART5_RXD {DT_INST_PROP_BY_IDX(5, location_rx, 1), \
		DT_INST_PROP_BY_IDX(5, location_rx, 2), gpioModeInput, 1}
#define PIN_USART5_TXD {DT_INST_PROP_BY_IDX(5, location_tx, 1), \
		DT_INST_PROP_BY_IDX(5, location_tx, 2), gpioModePushPull, 1}

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
static void usart_gecko_config_func_5(struct device *dev);
#endif

static const struct uart_gecko_config usart_gecko_5_config = {
	.base = (USART_TypeDef *)DT_INST_REG_ADDR(5),
	.clock = CLOCK_USART(DT_INST_PROP(5, peripheral_id)),
	.baud_rate = DT_INST_PROP(5, current_speed),
	.pin_rx = PIN_USART5_RXD,
	.pin_tx = PIN_USART5_TXD,
#ifdef CONFIG_SOC_GECKO_HAS_INDIVIDUAL_PIN_LOCATION
	.loc_rx = DT_INST_PROP_BY_IDX(5, location_rx, 0),
	.loc_tx = DT_INST_PROP_BY_IDX(5, location_tx, 0),
#else
#if DT_INST_PROP_BY_IDX(5, location_rx, 0) \
	!= DT_INST_PROP_BY_IDX(5, location_tx, 0)
#error USART_5 DTS location-* properties must have identical value
#endif
	.loc = DT_INST_PROP_BY_IDX(5, location_rx, 0),
#endif
#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	.irq_config_func = usart_gecko_config_func_5,
#endif
};

static struct uart_gecko_data usart_gecko_5_data;

DEVICE_AND_API_INIT(usart_5, DT_INST_LABEL(5),
		    &uart_gecko_init, &usart_gecko_5_data,
		    &usart_gecko_5_config, PRE_KERNEL_1,
		    CONFIG_KERNEL_INIT_PRIORITY_DEVICE, &uart_gecko_driver_api);

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
static void usart_gecko_config_func_5(struct device *dev)
{
	IRQ_CONNECT(DT_INST_IRQ_BY_NAME(5, rx, irq),
		    DT_INST_IRQ_BY_NAME(5, rx, priority),
		    uart_gecko_isr, DEVICE_GET(usart_5), 0);
	IRQ_CONNECT(DT_INST_IRQ_BY_NAME(5, tx, irq),
		    DT_INST_IRQ_BY_NAME(5, tx, priority),
		    uart_gecko_isr, DEVICE_GET(usart_5), 0);

	irq_enable(DT_INST_IRQ_BY_NAME(5, rx, irq));
	irq_enable(DT_INST_IRQ_BY_NAME(5, tx, irq));
}
#endif

#endif /* DT_NODE_HAS_STATUS(DT_DRV_INST(5), okay) */
