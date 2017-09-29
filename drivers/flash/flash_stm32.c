/*
 * Copyright (c) 2017 Linaro Limited
 * Copyright (c) 2017 BayLibre, SAS.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <device.h>
#include <string.h>
#include <flash.h>
#include <init.h>
#include <soc.h>

#include <flash_stm32.h>

#define STM32_FLASH_TIMEOUT	((u32_t) 0x000B0000)

/*
 * This is named flash_stm32_sem_take instead of flash_stm32_lock (and
 * similarly for flash_stm32_sem_give) to avoid confusion with locking
 * actual flash pages.
 */
static inline void flash_stm32_sem_take(struct device *dev)
{
	k_sem_take(&FLASH_STM32_PRIV(dev)->sem, K_FOREVER);
}

static inline void flash_stm32_sem_give(struct device *dev)
{
	k_sem_give(&FLASH_STM32_PRIV(dev)->sem);
}

static int flash_stm32_check_status(struct device *dev)
{
	u32_t const error =
		FLASH_FLAG_WRPERR |
		FLASH_FLAG_PGAERR |
#if defined(FLASH_FLAG_RDERR)
		FLASH_FLAG_RDERR  |
#endif
#if defined(FLASH_FLAG_PGPERR)
		FLASH_FLAG_PGPERR |
#endif
		FLASH_FLAG_PGSERR |
		FLASH_FLAG_OPERR;

	if (FLASH_STM32_REGS(dev)->sr & error) {
		return -EIO;
	}

	return 0;
}

int flash_stm32_wait_flash_idle(struct device *dev)
{
	u32_t timeout = STM32_FLASH_TIMEOUT;
	int rc;

	rc = flash_stm32_check_status(dev);
	if (rc < 0) {
		return -EIO;
	}

	while ((FLASH_STM32_REGS(dev)->sr & FLASH_SR_BSY) && timeout) {
		timeout--;
	}

	if (!timeout) {
		return -EIO;
	}

	return 0;
}

static void flash_stm32_flush_caches(struct device *dev)
{
#if defined(CONFIG_SOC_SERIES_STM32F4X)
	struct stm32f4x_flash *regs = FLASH_STM32_REGS(dev);
#elif defined(CONFIG_SOC_SERIES_STM32L4X)
	struct stm32l4x_flash *regs = FLASH_STM32_REGS(dev);
#endif

	if (regs->acr.val & FLASH_ACR_ICEN) {
		regs->acr.val &= ~FLASH_ACR_ICEN;
		regs->acr.val |= FLASH_ACR_ICRST;
		regs->acr.val &= ~FLASH_ACR_ICRST;
		regs->acr.val |= FLASH_ACR_ICEN;
	}

	if (regs->acr.val & FLASH_ACR_DCEN) {
		regs->acr.val &= ~FLASH_ACR_DCEN;
		regs->acr.val |= FLASH_ACR_DCRST;
		regs->acr.val &= ~FLASH_ACR_DCRST;
		regs->acr.val |= FLASH_ACR_DCEN;
	}
}

static int flash_stm32_read(struct device *dev, off_t offset, void *data,
			    size_t len)
{
	if (!flash_stm32_valid_range(dev, offset, len, false)) {
		return -EINVAL;
	}

	if (!len) {
		return 0;
	}

	memcpy(data, (void *) CONFIG_FLASH_BASE_ADDRESS + offset, len);

	return 0;
}

static int flash_stm32_erase(struct device *dev, off_t offset, size_t len)
{
	int rc;

	if (!flash_stm32_valid_range(dev, offset, len, true)) {
		return -EINVAL;
	}

	if (!len) {
		return 0;
	}

	flash_stm32_sem_take(dev);

	rc = flash_stm32_block_erase_loop(dev, offset, len);

	flash_stm32_flush_caches(dev);

	flash_stm32_sem_give(dev);

	return rc;
}

static int flash_stm32_write(struct device *dev, off_t offset,
			     const void *data, size_t len)
{
	int rc;

	if (!flash_stm32_valid_range(dev, offset, len, true)) {
		return -EINVAL;
	}

	if (!len) {
		return 0;
	}

	flash_stm32_sem_take(dev);

	rc = flash_stm32_write_range(dev, offset, data, len);

	flash_stm32_sem_give(dev);

	return rc;
}

static int flash_stm32_write_protection(struct device *dev, bool enable)
{
#if defined(CONFIG_SOC_SERIES_STM32F4X)
	struct stm32f4x_flash *regs = FLASH_STM32_REGS(dev);
#elif defined(CONFIG_SOC_SERIES_STM32L4X)
	struct stm32l4x_flash *regs = FLASH_STM32_REGS(dev);
#endif
	int rc = 0;

	flash_stm32_sem_take(dev);

	if (enable) {
		rc = flash_stm32_wait_flash_idle(dev);
		if (rc) {
			flash_stm32_sem_give(dev);
			return rc;
		}
		regs->cr |= FLASH_CR_LOCK;
	} else {
		if (regs->cr & FLASH_CR_LOCK) {
			regs->keyr = FLASH_KEY1;
			regs->keyr = FLASH_KEY2;
		}
	}

	flash_stm32_sem_give(dev);

	return rc;
}

static struct flash_stm32_priv flash_data = {
#if defined(CONFIG_SOC_SERIES_STM32F4X)
	.regs = (struct stm32f4x_flash *) FLASH_R_BASE,
#elif defined(CONFIG_SOC_SERIES_STM32L4X)
	.regs = (struct stm32l4x_flash *) FLASH_R_BASE,
	.pclken = { .bus = STM32_CLOCK_BUS_AHB1,
		    .enr = LL_AHB1_GRP1_PERIPH_FLASH },
#endif
};

static const struct flash_driver_api flash_stm32_api = {
	.write_protection = flash_stm32_write_protection,
	.erase = flash_stm32_erase,
	.write = flash_stm32_write,
	.read = flash_stm32_read,
#ifdef CONFIG_FLASH_PAGE_LAYOUT
	.page_layout = flash_stm32_page_layout,
#endif
#if defined(CONFIG_SOC_SERIES_STM32F4X)
	.write_block_size = 1,
#elif defined(CONFIG_SOC_SERIES_STM32L4X)
	.write_block_size = 8,
#endif
};

static int stm32_flash_init(struct device *dev)
{
	struct flash_stm32_priv *p = FLASH_STM32_PRIV(dev);
#if defined(CONFIG_SOC_SERIES_STM32L4X)
	struct device *clk = device_get_binding(STM32_CLOCK_CONTROL_NAME);

	/* enable clock */
	clock_control_on(clk, (clock_control_subsys_t *)&p->pclken);
#endif

	k_sem_init(&p->sem, 1, 1);

	return flash_stm32_write_protection(dev, false);
}

DEVICE_AND_API_INIT(stm32_flash, CONFIG_SOC_FLASH_STM32_DEV_NAME,
		    stm32_flash_init, &flash_data, NULL, POST_KERNEL,
		    CONFIG_KERNEL_INIT_PRIORITY_DEVICE, &flash_stm32_api);

