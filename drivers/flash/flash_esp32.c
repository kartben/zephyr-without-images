/*
 * Copyright (c) 2021 Espressif Systems (Shanghai) Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT espressif_esp32_flash_controller
#define SOC_NV_FLASH_NODE DT_INST(0, soc_nv_flash)

#define FLASH_WRITE_BLK_SZ DT_PROP(SOC_NV_FLASH_NODE, write_block_size)
#define FLASH_ERASE_BLK_SZ DT_PROP(SOC_NV_FLASH_NODE, erase_block_size)

/*
 * HAL includes go first to
 * avoid BIT macro redefinition
 */
#include <esp_spi_flash.h>
#include <hal/spi_ll.h>
#include <hal/spi_flash_ll.h>
#include <hal/spi_flash_hal.h>
#include <soc/spi_struct.h>
#include <spi_flash_defs.h>

#include <kernel.h>
#include <device.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <drivers/flash.h>
#include <soc.h>

#if defined(CONFIG_SOC_ESP32)
#include "soc/dport_reg.h"
#include "esp32/rom/cache.h"
#include "esp32/rom/spi_flash.h"
#include "esp32/spiram.h"
#elif defined(CONFIG_SOC_ESP32S2)
#include "soc/spi_mem_reg.h"
#include "esp32s2/rom/cache.h"
#include "esp32s2/rom/spi_flash.h"
#elif defined(CONFIG_SOC_ESP32C3)
#include "soc/spi_periph.h"
#include "soc/spi_mem_reg.h"
#include "soc/dport_access.h"
#include "esp32c3/dport_access.h"
#include "esp32c3/rom/cache.h"
#include "esp32c3/rom/spi_flash.h"
#endif

#include "soc/mmu.h"

#include <logging/log.h>
LOG_MODULE_REGISTER(flash_esp32, CONFIG_FLASH_LOG_LEVEL);

struct flash_esp32_dev_config {
	spi_dev_t *controller;
};

struct flash_esp32_dev_data {
	struct k_sem sem;
};

static const struct flash_parameters flash_esp32_parameters = {
	.write_block_size = FLASH_WRITE_BLK_SZ,
	.erase_value = 0xff,
};

static inline void flash_esp32_sem_take(const struct device *dev)
{
	struct flash_esp32_dev_data *data = dev->data;

	k_sem_take(&data->sem, K_FOREVER);
}

static inline void flash_esp32_sem_give(const struct device *dev)
{
	struct flash_esp32_dev_data *data = dev->data;

	k_sem_give(&data->sem);
}

static int flash_esp32_read(const struct device *dev, off_t address, void *buffer, size_t length)
{
	flash_esp32_sem_take(dev);
	int ret = spi_flash_read(address, buffer, length);
	flash_esp32_sem_give(dev);
	return ret;
}

static int flash_esp32_write(const struct device *dev,
			     off_t address,
			     const void *buffer,
			     size_t length)
{
	flash_esp32_sem_take(dev);
	int ret = spi_flash_write(address, buffer, length);
	flash_esp32_sem_give(dev);
	return ret;
}

static int flash_esp32_erase(const struct device *dev, off_t start, size_t len)
{
	flash_esp32_sem_take(dev);
	int ret = spi_flash_erase_range(start, len);
	flash_esp32_sem_give(dev);
	return ret;
}

#if CONFIG_FLASH_PAGE_LAYOUT
static const struct flash_pages_layout flash_esp32_pages_layout = {
	.pages_count = DT_REG_SIZE(SOC_NV_FLASH_NODE) / FLASH_ERASE_BLK_SZ,
	.pages_size = DT_PROP(SOC_NV_FLASH_NODE, erase_block_size),
};

void flash_esp32_page_layout(const struct device *dev,
			     const struct flash_pages_layout **layout,
			     size_t *layout_size)
{
	*layout = &flash_esp32_pages_layout;
	*layout_size = 1;
}
#endif /* CONFIG_FLASH_PAGE_LAYOUT */

static const struct flash_parameters *
flash_esp32_get_parameters(const struct device *dev)
{
	ARG_UNUSED(dev);

	return &flash_esp32_parameters;
}

static int flash_esp32_init(const struct device *dev)
{
	struct flash_esp32_dev_data *const dev_data = dev->data;

	k_sem_init(&dev_data->sem, 1, 1);

	return 0;
}

static const struct flash_driver_api flash_esp32_driver_api = {
	.read = flash_esp32_read,
	.write = flash_esp32_write,
	.erase = flash_esp32_erase,
	.get_parameters = flash_esp32_get_parameters,
#ifdef CONFIG_FLASH_PAGE_LAYOUT
	.page_layout = flash_esp32_page_layout,
#endif
};

static struct flash_esp32_dev_data flash_esp32_data;

static const struct flash_esp32_dev_config flash_esp32_config = {
	.controller = (spi_dev_t *) DT_INST_REG_ADDR(0),
};

DEVICE_DT_INST_DEFINE(0, flash_esp32_init,
		      NULL,
		      &flash_esp32_data, &flash_esp32_config,
		      POST_KERNEL, CONFIG_FLASH_INIT_PRIORITY,
		      &flash_esp32_driver_api);
