/* spi_dw.c - Designware SPI driver implementation */

/*
 * Copyright (c) 2015 Intel Corporation.
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

#include <nanokernel.h>
#include <arch/cpu.h>

#include <misc/__assert.h>
#include <board.h>
#include <device.h>
#include <init.h>

#include <sys_io.h>
#include <clock_control.h>
#include <misc/util.h>

#include <spi.h>
#include <spi_dw.h>

#ifdef CONFIG_IOAPIC
#include <drivers/ioapic.h>
#endif

#ifndef CONFIG_SPI_DEBUG
#define DBG(...) {; }
#else
#if defined(CONFIG_STDOUT_CONSOLE)
#include <stdio.h>
#define DBG printf
#else
#include <misc/printk.h>
#define DBG printk
#endif /* CONFIG_STDOUT_CONSOLE */
#endif /* CONFIG_SPI_DEBUG */

#if defined(CONFIG_SPI_DW_ARC_AUX_REGS)
#define _REG_READ(__sz) sys_in##__sz
#define _REG_WRITE(__sz) sys_out##__sz
#define _REG_SET_BIT _sys_io_set_bit
#define _REG_CLEAR_BIT _sys_io_clear_bit
#define _REG_TEST_BIT _sys_io_test_bit
#else
#define _REG_READ(__sz) sys_read##__sz
#define _REG_WRITE(__sz) sys_write##__sz
#define _REG_SET_BIT sys_set_bit
#define _REG_CLEAR_BIT sys_clear_bit
#define _REG_TEST_BIT sys_test_bit
#endif /* SPI_DW_ARC_AUX_REGS */

#define DEFINE_MM_REG_READ(__reg, __off, __sz)				\
	static inline uint32_t read_##__reg(uint32_t addr)		\
	{								\
		return _REG_READ(__sz)(addr + __off);			\
	}
#define DEFINE_MM_REG_WRITE(__reg, __off, __sz)				\
	static inline void write_##__reg(uint32_t data, uint32_t addr)	\
	{								\
		_REG_WRITE(__sz)(data, addr + __off);			\
	}

#ifdef CONFIG_ARC
DEFINE_MM_REG_WRITE(ctrlr0, DW_SPI_REG_CTRLR0, 16)
DEFINE_MM_REG_READ(dr, DW_SPI_REG_DR, 16)
DEFINE_MM_REG_WRITE(dr, DW_SPI_REG_DR, 16)
#else
DEFINE_MM_REG_WRITE(ctrlr0, DW_SPI_REG_CTRLR0, 32)
DEFINE_MM_REG_READ(dr, DW_SPI_REG_DR, 32)
DEFINE_MM_REG_WRITE(dr, DW_SPI_REG_DR, 32)
#endif
DEFINE_MM_REG_WRITE(ser, DW_SPI_REG_SER, 8)
DEFINE_MM_REG_WRITE(baudr, DW_SPI_REG_BAUDR, 16)
DEFINE_MM_REG_WRITE(txftlr, DW_SPI_REG_TXFTLR, 32)
DEFINE_MM_REG_WRITE(rxftlr, DW_SPI_REG_RXFTLR, 32)
DEFINE_MM_REG_READ(rxftlr, DW_SPI_REG_RXFTLR, 32)
DEFINE_MM_REG_READ(txflr, DW_SPI_REG_TXFLR, 32)
DEFINE_MM_REG_READ(rxflr, DW_SPI_REG_RXFLR, 32)
DEFINE_MM_REG_WRITE(imr, DW_SPI_REG_IMR, 8)
DEFINE_MM_REG_READ(isr, DW_SPI_REG_ISR, 8)
DEFINE_MM_REG_READ(ssi_comp_version, DW_SPI_REG_SSI_COMP_VERSION, 32)

#define DEFINE_SET_BIT_OP(__reg_bit, __reg_off, __bit)			\
	static inline void set_bit_##__reg_bit(uint32_t addr)		\
	{								\
		_REG_SET_BIT(addr + __reg_off, __bit);			\
	}

#define DEFINE_CLEAR_BIT_OP(__reg_bit, __reg_off, __bit)		\
	static inline void clear_bit_##__reg_bit(uint32_t addr)		\
	{								\
		_REG_CLEAR_BIT(addr + __reg_off, __bit);		\
	}

#define DEFINE_TEST_BIT_OP(__reg_bit, __reg_off, __bit)			\
	static inline int test_bit_##__reg_bit(uint32_t addr)		\
	{								\
		return _REG_TEST_BIT(addr + __reg_off, __bit);		\
	}

DEFINE_SET_BIT_OP(ssienr, DW_SPI_REG_SSIENR, DW_SPI_SSIENR_SSIEN_BIT)
DEFINE_CLEAR_BIT_OP(ssienr, DW_SPI_REG_SSIENR, DW_SPI_SSIENR_SSIEN_BIT)
DEFINE_TEST_BIT_OP(ssienr, DW_SPI_REG_SSIENR, DW_SPI_SSIENR_SSIEN_BIT)
DEFINE_TEST_BIT_OP(sr_busy, DW_SPI_REG_SR, DW_SPI_SR_BUSY_BIT)
DEFINE_TEST_BIT_OP(icr, DW_SPI_REG_ICR, DW_SPI_SR_ICR_BIT)

#ifdef CONFIG_SOC_QUARK_SE
#define int_unmask(__mask)						\
	sys_write32(sys_read32(__mask) & INT_UNMASK_IA, __mask)
#else
#define int_unmask(...) {; }
#endif

#ifdef CONFIG_SPI_DW_CLOCK_GATE
static inline void _clock_config(struct device *dev)
{
	struct device *clk;
	char *drv = CONFIG_SPI_DW_CLOCK_GATE_DRV_NAME;

	clk = device_get_binding(drv);
	if (clk) {
		struct spi_dw_data *spi = dev->driver_data;

		spi->clock = clk;
	}
}

static inline void _clock_on(struct device *dev)
{
	struct spi_dw_config *info = dev->config->config_info;
	struct spi_dw_data *spi = dev->driver_data;

	clock_control_on(spi->clock, info->clock_data);
}

static inline void _clock_off(struct device *dev)
{
	struct spi_dw_config *info = dev->config->config_info;
	struct spi_dw_data *spi = dev->driver_data;

	clock_control_off(spi->clock, info->clock_data);
}
#else
#define _clock_config(...)
#define _clock_on(...)
#define _clock_off(...)
#endif

#ifdef CONFIG_SPI_DW_CS_GPIO

#include <gpio.h>

static inline void _spi_config_cs(struct device *dev)
{
	struct spi_dw_config *info = dev->config->config_info;
	struct spi_dw_data *spi = dev->driver_data;
	struct device *gpio;

	gpio = device_get_binding(info->cs_gpio_name);
	if (!gpio) {
		spi->cs_gpio_port = NULL;
		return;
	}

	gpio_pin_configure(gpio, info->cs_gpio_pin, GPIO_DIR_OUT);
	/* Default CS line to high (idling) */
	gpio_pin_write(gpio, info->cs_gpio_pin, 1);

	spi->cs_gpio_port = gpio;
}

static inline void _spi_control_cs(struct device *dev, int on)
{
	struct spi_dw_config *info = dev->config->config_info;
	struct spi_dw_data *spi = dev->driver_data;

	if (spi->cs_gpio_port) {
		gpio_pin_write(spi->cs_gpio_port, info->cs_gpio_pin, !on);
	}
}
#else
#define _spi_control_cs(...)
#define _spi_config_cs(...)
#endif /* CONFIG_SPI_DW_CS_GPIO */

static void completed(struct device *dev, int error)
{
	struct spi_dw_config *info = dev->config->config_info;
	struct spi_dw_data *spi = dev->driver_data;

	if (spi->fifo_diff) {
		return;
	}

	if (!((spi->tx_buf && !spi->tx_buf_len && !spi->rx_buf) ||
	      (spi->rx_buf && !spi->rx_buf_len && !spi->tx_buf) ||
	      (spi->tx_buf && !spi->tx_buf_len &&
				spi->rx_buf && !spi->rx_buf_len) ||
	      error)) {
		return;
	}

	spi->error = error;

	/* Disabling interrupts */
	write_imr(DW_SPI_IMR_MASK, info->regs);
	/* Disabling the controller */
	clear_bit_ssienr(info->regs);

	_spi_control_cs(dev, 0);
	device_sync_call_complete(&spi->sync);
}

static void push_data(struct device *dev)
{
	struct spi_dw_config *info = dev->config->config_info;
	struct spi_dw_data *spi = dev->driver_data;
	uint32_t cnt = 0;
	uint32_t data = 0;
	uint32_t f_tx;

	DBG("spi: push_data\n");

	f_tx = DW_SPI_FIFO_DEPTH - read_txflr(info->regs) -
					read_rxflr(info->regs) - 1;
	while (f_tx) {
		if (spi->tx_buf && spi->tx_buf_len > 0) {
			switch (spi->dfs) {
			case 1:
				data = *(uint8_t *)(spi->tx_buf);
				break;
			case 2:
				data = *(uint16_t *)(spi->tx_buf);
				break;
#ifndef CONFIG_ARC
			case 4:
				data = *(uint32_t *)(spi->tx_buf);
				break;
#endif
			}

			spi->tx_buf += spi->dfs;
			spi->tx_buf_len--;
		} else if (spi->rx_buf && spi->rx_buf_len > 0) {
			/* No need to push more than necessary */
			if (spi->rx_buf_len - spi->fifo_diff <= 0) {
				break;
			}

			data = 0;
		} else {
			/* Nothing to push anymore */
			break;
		}

		write_dr(data, info->regs);
		f_tx--;
		spi->fifo_diff++;
		cnt++;
	}

	if (!spi->tx_buf_len && !spi->rx_buf_len) {
		write_txftlr(0, info->regs);
	}

	DBG("Pushed: %d\n", cnt);
}

static void pull_data(struct device *dev)
{
	struct spi_dw_config *info = dev->config->config_info;
	struct spi_dw_data *spi = dev->driver_data;
	uint32_t cnt = 0;
	uint32_t data = 0;

	DBG("spi: pull_data\n");

	while (read_rxflr(info->regs)) {
		data = read_dr(info->regs);
		cnt++;

		if (spi->rx_buf && spi->rx_buf_len > 0) {
			switch (spi->dfs) {
			case 1:
				*(uint8_t *)(spi->rx_buf) = (uint8_t)data;
				break;
			case 2:
				*(uint16_t *)(spi->rx_buf) = (uint16_t)data;
				break;
#ifndef CONFIG_ARC
			case 4:
				*(uint32_t *)(spi->rx_buf) = (uint32_t)data;
				break;
#endif
			}

			spi->rx_buf += spi->dfs;
			spi->rx_buf_len--;
		}

		spi->fifo_diff--;
	}

	if (!spi->rx_buf_len && spi->tx_buf_len < DW_SPI_FIFO_DEPTH) {
		write_rxftlr(spi->tx_buf_len - 1, info->regs);
	} else if (read_rxftlr(info->regs) >= spi->rx_buf_len) {
		write_rxftlr(spi->rx_buf_len - 1, info->regs);
	}

	DBG("Pulled: %d\n", cnt);
}

static inline bool _spi_dw_is_controller_ready(struct device *dev)
{
	struct spi_dw_config *info = dev->config->config_info;

	if (test_bit_ssienr(info->regs) || test_bit_sr_busy(info->regs)) {
		return false;
	}

	return true;
}

static int spi_dw_configure(struct device *dev,
				struct spi_config *config)
{
	struct spi_dw_config *info = dev->config->config_info;
	struct spi_dw_data *spi = dev->driver_data;
	uint32_t flags = config->config;
	uint32_t ctrlr0 = 0;
	uint32_t mode;

	DBG("spi_dw_configure: %p (0x%x), %p\n", dev, info->regs, config);

	/* Check status */
	if (!_spi_dw_is_controller_ready(dev)) {
		DBG("spi_dw_configure: Controller is busy\n");
		return DEV_USED;
	}

	/* Word size */
	ctrlr0 |= DW_SPI_CTRLR0_DFS(SPI_WORD_SIZE_GET(flags));

	/* Determine how many bytes are required per-frame */
	spi->dfs = SPI_DFS_TO_BYTES(SPI_WORD_SIZE_GET(flags));

	/* SPI mode */
	mode = SPI_MODE(flags);
	if (mode & SPI_MODE_CPOL) {
		ctrlr0 |= DW_SPI_CTRLR0_SCPOL;
	}

	if (mode & SPI_MODE_CPHA) {
		ctrlr0 |= DW_SPI_CTRLR0_SCPH;
	}

	if (mode & SPI_MODE_LOOP) {
		ctrlr0 |= DW_SPI_CTRLR0_SRL;
	}

	/* Installing the configuration */
	write_ctrlr0(ctrlr0, info->regs);

	/* Tx Threshold, always at default */
	write_txftlr(DW_SPI_TXFTLR_DFLT, info->regs);

	/* Configuring the rate */
	write_baudr(config->max_sys_freq, info->regs);

	/* Mask SPI interrupts */
	write_imr(DW_SPI_IMR_MASK, info->regs);

	return DEV_OK;
}

static int spi_dw_slave_select(struct device *dev, uint32_t slave)
{
	struct spi_dw_data *spi = dev->driver_data;

	if (slave == 0 || slave > 4) {
		return DEV_INVALID_CONF;
	}

	spi->slave = 1 << (slave - 1);

	return DEV_OK;
}

static int spi_dw_transceive(struct device *dev,
			     uint8_t *tx_buf, uint32_t tx_buf_len,
			     uint8_t *rx_buf, uint32_t rx_buf_len)
{
	struct spi_dw_config *info = dev->config->config_info;
	struct spi_dw_data *spi = dev->driver_data;
	uint32_t rx_thsld = DW_SPI_RXFTLR_DFLT;

	DBG("spi_dw_transceive: %p, %p, %u, %p, %u\n",
			dev, tx_buf, tx_buf_len, rx_buf, rx_buf_len);

	/* Check status */
	if (!_spi_dw_is_controller_ready(dev)) {
		DBG("spi_dw_transceive: Controller is busy\n");
		return DEV_USED;
	}

	/* Set buffers info */
	spi->tx_buf = tx_buf;
	spi->tx_buf_len = tx_buf_len/spi->dfs;
	spi->rx_buf = rx_buf;
	spi->rx_buf_len = rx_buf_len/spi->dfs;
	spi->fifo_diff = 0;

	/* Does Rx thresholds needs to be lower? */
	if (rx_buf_len && spi->rx_buf_len < DW_SPI_FIFO_DEPTH) {
		rx_thsld = spi->rx_buf_len - 1;
	} else if (!rx_buf_len && spi->tx_buf_len < DW_SPI_FIFO_DEPTH) {
		rx_thsld = spi->tx_buf_len - 1;
	}
	write_rxftlr(rx_thsld, info->regs);

	/* Slave select */
	write_ser(spi->slave, info->regs);

	_spi_control_cs(dev, 1);

	/* Enable interrupts */
	write_imr(DW_SPI_IMR_UNMASK, info->regs);

	/* Enable the controller */
	set_bit_ssienr(info->regs);

	device_sync_call_wait(&spi->sync);

	if (spi->error) {
		spi->error = 0;
		return DEV_FAIL;
	}

	return DEV_OK;
}

static int spi_dw_suspend(struct device *dev)
{
	struct spi_dw_config *info = dev->config->config_info;

	DBG("spi_dw_suspend: %p\n", dev);

	write_imr(DW_SPI_IMR_MASK, info->regs);
	irq_disable(info->irq);

	_clock_off(dev);

	return DEV_OK;
}

static int spi_dw_resume(struct device *dev)
{
	struct spi_dw_config *info = dev->config->config_info;

	DBG("spi_dw_resume: %p\n", dev);

	_clock_on(dev);

	irq_enable(info->irq);
	write_imr(DW_SPI_IMR_UNMASK, info->regs);

	return DEV_OK;
}

void spi_dw_isr(void *arg)
{
	struct device *dev = arg;
	struct spi_dw_config *info = dev->config->config_info;
	uint32_t error = 0;
	uint32_t int_status;

	DBG("spi_dw_isr: %p\n", dev);

	int_status = read_isr(info->regs);
	test_bit_icr(info->regs);

	DBG("int_status 0x%x - (tx: %d, rx: %d)\n",
		int_status, read_txflr(info->regs), read_rxflr(info->regs));

	if (int_status & DW_SPI_ISR_ERRORS_MASK) {
		error = 1;
		goto out;
	}

	if (int_status & DW_SPI_ISR_RXFIS) {
		pull_data(dev);
	}

	if (int_status & DW_SPI_ISR_TXEIS) {
		push_data(dev);
	}

out:
	completed(dev, error);
}

static struct spi_driver_api dw_spi_api = {
	.configure = spi_dw_configure,
	.slave_select = spi_dw_slave_select,
	.transceive = spi_dw_transceive,
	.suspend = spi_dw_suspend,
	.resume = spi_dw_resume,
};

int spi_dw_init(struct device *dev)
{
	struct spi_dw_config *info = dev->config->config_info;
	struct spi_dw_data *spi = dev->driver_data;

	_clock_config(dev);

	if (read_ssi_comp_version(info->regs) != DW_SSI_COMP_VERSION) {
		_clock_off(dev);
		return DEV_NOT_CONFIG;
	}

	dev->driver_api = &dw_spi_api;

	info->config_func();

	device_sync_call_init(&spi->sync);

	_spi_config_cs(dev);

	write_imr(DW_SPI_IMR_MASK, info->regs);
	clear_bit_ssienr(info->regs);

	int_unmask(info->int_mask);

	DBG("Designware SPI driver initialized on device: %p\n", dev);

	return DEV_OK;
}

#ifdef CONFIG_IOAPIC
	#if defined(CONFIG_SPI_DW_FALLING_EDGE)
		#define SPI_DW_IRQ_FLAGS (IOAPIC_EDGE | IOAPIC_LOW)
	#elif defined(CONFIG_SPI_DW_RISING_EDGE)
		#define SPI_DW_IRQ_FLAGS (IOAPIC_EDGE | IOAPIC_HIGH)
	#elif defined(CONFIG_SPI_DW_LEVEL_HIGH)
		#define SPI_DW_IRQ_FLAGS (IOAPIC_LEVEL | IOAPIC_HIGH)
	#elif defined(CONFIG_SPI_DW_LEVEL_LOW)
		#define SPI_DW_IRQ_FLAGS (IOAPIC_LEVEL | IOAPIC_LOW)
	#endif
#else
	#define SPI_DW_IRQ_FLAGS 0
#endif /* CONFIG_IOAPIC */

#ifdef CONFIG_SPI_DW_PORT_0
void spi_config_0_irq(void);

struct spi_dw_data spi_dw_data_port_0;

struct spi_dw_config spi_dw_config_0 = {
	.regs = CONFIG_SPI_DW_PORT_0_REGS,
	.irq = CONFIG_SPI_DW_PORT_0_IRQ,
	.int_mask = SPI_DW_PORT_0_INT_MASK,
#ifdef CONFIG_SPI_DW_CLOCK_GATE
	.clock_data = UINT_TO_POINTER(CONFIG_SPI_DW_PORT_0_CLOCK_GATE_SUBSYS),
#endif /* CONFIG_SPI_DW_CLOCK_GATE */
#ifdef CONFIG_SPI_DW_CS_GPIO
	.cs_gpio_name = CONFIG_SPI_DW_PORT_0_CS_GPIO_PORT,
	.cs_gpio_pin = CONFIG_SPI_DW_PORT_0_CS_GPIO_PIN,
#endif
	.config_func = spi_config_0_irq
};

DEVICE_INIT(spi_dw_port_0, CONFIG_SPI_DW_PORT_0_DRV_NAME, spi_dw_init,
			&spi_dw_data_port_0, &spi_dw_config_0,
			SECONDARY, CONFIG_SPI_DW_INIT_PRIORITY);

void spi_config_0_irq(void)
{
	IRQ_CONNECT(CONFIG_SPI_DW_PORT_0_IRQ, CONFIG_SPI_DW_PORT_0_PRI,
		    spi_dw_isr, DEVICE_GET(spi_dw_port_0),
		    SPI_DW_IRQ_FLAGS);
	irq_enable(CONFIG_SPI_DW_PORT_0_IRQ);
}
#endif /* CONFIG_SPI_DW_PORT_0 */
#ifdef CONFIG_SPI_DW_PORT_1
void spi_config_1_irq(void);

struct spi_dw_data spi_dw_data_port_1;

struct spi_dw_config spi_dw_config_1 = {
	.regs = CONFIG_SPI_DW_PORT_1_REGS,
	.irq = CONFIG_SPI_DW_PORT_1_IRQ,
	.int_mask = SPI_DW_PORT_1_INT_MASK,
#ifdef CONFIG_SPI_DW_CLOCK_GATE
	.clock_data = UINT_TO_POINTER(CONFIG_SPI_DW_PORT_1_CLOCK_GATE_SUBSYS),
#endif /* CONFIG_SPI_DW_CLOCK_GATE */
#ifdef CONFIG_SPI_DW_CS_GPIO
	.cs_gpio_name = CONFIG_SPI_DW_PORT_1_CS_GPIO_PORT,
	.cs_gpio_pin = CONFIG_SPI_DW_PORT_1_CS_GPIO_PIN,
#endif
	.config_func = spi_config_1_irq
};

DEVICE_INIT(spi_dw_port_1, CONFIG_SPI_DW_PORT_1_DRV_NAME, spi_dw_init,
			&spi_dw_data_port_1, &spi_dw_config_1,
			SECONDARY, CONFIG_SPI_DW_INIT_PRIORITY);

void spi_config_1_irq(void)
{
	IRQ_CONNECT(CONFIG_SPI_DW_PORT_1_IRQ, CONFIG_SPI_DW_PORT_1_PRI,
		    spi_dw_isr, DEVICE_GET(spi_dw_port_1),
		    SPI_DW_IRQ_FLAGS);
	irq_enable(CONFIG_SPI_DW_PORT_1_IRQ);
}
#endif /* CONFIG_SPI_DW_PORT_1 */
