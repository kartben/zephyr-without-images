/*
 * Copyright (c) 2020 Vossloh Cogifer
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT st_stm32h7_flash_controller

#include <sys/util.h>
#include <kernel.h>
#include <device.h>
#include <string.h>
#include <drivers/flash.h>
#include <init.h>
#include <soc.h>
#include <stm32h7xx_ll_bus.h>
#include <stm32h7xx_ll_utils.h>

#include "flash_stm32.h"
#include "stm32_hsem.h"

#define LOG_DOMAIN flash_stm32h7
#define LOG_LEVEL CONFIG_FLASH_LOG_LEVEL
#include <logging/log.h>
LOG_MODULE_REGISTER(LOG_DOMAIN);

#define STM32H7_FLASH_MAX_ERASE_TIME    4000

/* Let's wait for double the max erase time to be sure that the operation is
 * completed.
 */
#define STM32H7_FLASH_TIMEOUT   (2 * STM32H7_FLASH_MAX_ERASE_TIME)

#ifdef CONFIG_CPU_CORTEX_M4
#error Flash driver on M4 core is not supported yet
#endif

#define REAL_FLASH_SIZE_KB	KB(LL_GetFlashSize())
#define SECTOR_PER_BANK		((REAL_FLASH_SIZE_KB / FLASH_SECTOR_SIZE) / 2)
#if defined(DUAL_BANK)
#define STM32H7_SERIES_MAX_FLASH_KB	KB(2048)
#define BANK2_OFFSET	(STM32H7_SERIES_MAX_FLASH_KB / 2)
/* When flash is dual bank and flash size is smaller than Max flash size of
 * the serie, there is a discontinuty between bank1 and bank2.
 */
#define DISCONTINUOUS_BANKS (REAL_FLASH_SIZE_KB < STM32H7_SERIES_MAX_FLASH_KB)
#endif

struct flash_stm32_sector_t {
	int sector_index;
	int bank;
	volatile uint32_t *cr;
	volatile uint32_t *sr;
};

#if defined(CONFIG_MULTITHREADING) || defined(CONFIG_STM32H7_DUAL_CORE)
/*
 * This is named flash_stm32_sem_take instead of flash_stm32_lock (and
 * similarly for flash_stm32_sem_give) to avoid confusion with locking
 * actual flash sectors.
 */
static inline void _flash_stm32_sem_take(const struct device *dev)
{
	k_sem_take(&FLASH_STM32_PRIV(dev)->sem, K_FOREVER);
	z_stm32_hsem_lock(CFG_HW_FLASH_SEMID, HSEM_LOCK_WAIT_FOREVER);
}

static inline void _flash_stm32_sem_give(const struct device *dev)
{
	z_stm32_hsem_unlock(CFG_HW_FLASH_SEMID);
	k_sem_give(&FLASH_STM32_PRIV(dev)->sem);
}

#define flash_stm32_sem_init(dev) k_sem_init(&FLASH_STM32_PRIV(dev)->sem, 1, 1)
#define flash_stm32_sem_take(dev) _flash_stm32_sem_take(dev)
#define flash_stm32_sem_give(dev) _flash_stm32_sem_give(dev)
#else
#define flash_stm32_sem_init(dev)
#define flash_stm32_sem_take(dev)
#define flash_stm32_sem_give(dev)
#endif

bool flash_stm32_valid_range(const struct device *dev, off_t offset,
			     uint32_t len,
			     bool write)
{
#if defined(DUAL_BANK)
	if (DISCONTINUOUS_BANKS) {
		/*
		 * In case of bank1/2 discontinuity, the range should not
		 * start before bank2 and end beyond bank1 at the same time.
		 * Locations beyond bank2 are caught by flash_stm32_range_exists
		 */
		if ((offset < BANK2_OFFSET)
		    && (offset + len > REAL_FLASH_SIZE_KB / 2)) {
			LOG_ERR("Range ovelaps flash bank discontinuity");
			return false;
		}
	}
#endif

	if (write) {
		if ((offset % FLASH_NB_32BITWORD_IN_FLASHWORD * 4) != 0) {
			LOG_ERR("Write offset not aligned on flashword length. "
				"Offset: 0x%x, flashword length: %d",
				offset, FLASH_NB_32BITWORD_IN_FLASHWORD * 4);
			return false;
		}
	}
	return flash_stm32_range_exists(dev, offset, len);
}

static int flash_stm32_check_status(const struct device *dev)
{
	uint32_t const error_bank1 = FLASH_FLAG_ALL_ERRORS_BANK1;
#ifdef DUAL_BANK
	uint32_t const error_bank2 = FLASH_FLAG_ALL_ERRORS_BANK2;
#endif

	if (FLASH_STM32_REGS(dev)->SR1 & error_bank1) {
		LOG_ERR("Status Bank1: 0x%08x",
			FLASH_STM32_REGS(dev)->SR1 & error_bank1);
		return -EIO;
	}

#ifdef DUAL_BANK
	if (FLASH_STM32_REGS(dev)->SR2 & error_bank2) {
		LOG_ERR("Status Bank2: 0x%08x",
			FLASH_STM32_REGS(dev)->SR2 & error_bank2);
		return -EIO;
	}
#endif

	return 0;
}


int flash_stm32_wait_flash_idle(const struct device *dev)
{
	int64_t timeout_time = k_uptime_get() + STM32H7_FLASH_TIMEOUT;
	int rc;

	rc = flash_stm32_check_status(dev);
	if (rc < 0) {
		return -EIO;
	}
#ifdef DUAL_BANK
	while ((FLASH_STM32_REGS(dev)->SR1 & FLASH_SR_QW)
	       || (FLASH_STM32_REGS(dev)->SR2 & FLASH_SR_QW))
#else
	while (FLASH_STM32_REGS(dev)->SR1 & FLASH_SR_QW)
#endif
	{
		if (k_uptime_get() > timeout_time) {
			LOG_ERR("Timeout! val: %d", STM32H7_FLASH_TIMEOUT);
			return -EIO;
		}
	}

	return 0;
}

static struct flash_stm32_sector_t get_sector(const struct device *dev,
					      off_t offset)
{
	struct flash_stm32_sector_t sector;
	FLASH_TypeDef *regs = FLASH_STM32_REGS(dev);

#ifdef DUAL_BANK
	bool bank_swap;
	/* Check whether bank1/2 are swapped */
	bank_swap = (READ_BIT(FLASH->OPTCR, FLASH_OPTCR_SWAP_BANK)
			== FLASH_OPTCR_SWAP_BANK);
	sector.sector_index = offset / FLASH_SECTOR_SIZE;
	if ((offset < (REAL_FLASH_SIZE_KB / 2)) && !bank_swap) {
		sector.bank = 1;
		sector.cr = &regs->CR1;
		sector.sr = &regs->SR1;
	} else if ((offset >= BANK2_OFFSET) && bank_swap) {
		sector.sector_index -= BANK2_OFFSET / FLASH_SECTOR_SIZE;
		sector.bank = 1;
		sector.cr = &regs->CR2;
		sector.sr = &regs->SR2;
	} else if ((offset < (REAL_FLASH_SIZE_KB / 2)) && bank_swap) {
		sector.bank = 2;
		sector.cr = &regs->CR1;
		sector.sr = &regs->SR1;
	} else if ((offset >= BANK2_OFFSET) && !bank_swap) {
		sector.sector_index -= BANK2_OFFSET / FLASH_SECTOR_SIZE;
		sector.bank = 2;
		sector.cr = &regs->CR2;
		sector.sr = &regs->SR2;
	} else {
		sector.sector_index = 0;
		sector.bank = 0;
		sector.cr = NULL;
		sector.sr = NULL;
	}
#else
	if (offset < REAL_FLASH_SIZE_KB) {
		sector.sector_index = offset / FLASH_SECTOR_SIZE;
		sector.bank = 1;
		sector.cr = &regs->CR1;
		sector.sr = &regs->SR1;
	} else {
		sector.sector_index = 0;
		sector.bank = 0;
		sector.cr = NULL;
		sector.sr = NULL;
	}
#endif

	return sector;
}

static int erase_sector(const struct device *dev, int offset)
{
	int rc;
	uint32_t tmp;
	struct flash_stm32_sector_t sector = get_sector(dev, offset);

	if (sector.bank == 0) {

		LOG_ERR("Offset %d does not exist", offset);
		return -EINVAL;
	}

	/* if the control register is locked, do not fail silently */
	if (*(sector.cr) & FLASH_CR_LOCK) {
		return -EIO;
	}

	rc = flash_stm32_wait_flash_idle(dev);
	if (rc < 0) {
		return rc;
	}

	*(sector.cr) &= FLASH_CR_SNB;
	*(sector.cr) |= (FLASH_CR_SER
		| ((sector.sector_index << FLASH_CR_SNB_Pos) & FLASH_CR_SNB));
	*(sector.cr) |= FLASH_CR_START;
	/* flush the register write */
	tmp = *(sector.cr);

	rc = flash_stm32_wait_flash_idle(dev);
	*(sector.cr) &= ~(FLASH_CR_SER | FLASH_CR_SNB);

	return rc;
}


int flash_stm32_block_erase_loop(const struct device *dev,
				 unsigned int offset,
				 unsigned int len)
{
	unsigned int address = offset, rc = 0;

	for (; address <= offset + len - 1 ; address += FLASH_SECTOR_SIZE) {
		rc = erase_sector(dev, address);
		if (rc < 0) {
			break;
		}
	}
	return rc;
}

static int wait_write_queue(const struct device *dev, off_t offset)
{
	int64_t timeout_time = k_uptime_get() + 100;
	struct flash_stm32_sector_t sector = get_sector(dev, offset);

	if (sector.bank == 0) {
		LOG_ERR("Offset %d does not exist", offset);
		return -EINVAL;
	}

	while (*(sector.sr) & FLASH_SR_QW) {
		if (k_uptime_get() > timeout_time) {
			LOG_ERR("Timeout! val: %d", 100);
			return -EIO;
		}
	}

	return 0;
}

static int write_ndwords(const struct device *dev,
			 off_t offset, const uint64_t *data,
			 uint8_t n)
{
	volatile uint64_t *flash = (uint64_t *)(offset
						+ CONFIG_FLASH_BASE_ADDRESS);
	uint32_t tmp;
	int rc;
	int i;
	struct flash_stm32_sector_t sector = get_sector(dev, offset);

	if (sector.bank == 0) {
		LOG_ERR("Offset %d does not exist", offset);
		return -EINVAL;
	}

	/* if the control register is locked, do not fail silently */
	if (*(sector.cr) & FLASH_CR_LOCK) {
		return -EIO;
	}

	/* Check that no Flash main memory operation is ongoing */
	rc = flash_stm32_wait_flash_idle(dev);
	if (rc < 0) {
		return rc;
	}

	/* Check if 256 bits location is erased */
	for (i = 0; i < n; ++i) {
		if (flash[i] != 0xFFFFFFFFFFFFFFFFUL) {
			return -EIO;
		}
	}

	/* Set the PG bit */
	*(sector.cr) |= FLASH_CR_PG;

	/* Flush the register write */
	tmp = *(sector.cr);

	/* Perform the data write operation at the desired memory address */
	for (i = 0; i < n; ++i) {
		flash[i] = data[i];
		wait_write_queue(dev, offset);
	}

	/* Wait until the BSY bit is cleared */
	rc = flash_stm32_wait_flash_idle(dev);

	/* Clear the PG bit */
	*(sector.cr) &= (~FLASH_CR_PG);

	return rc;
}

int flash_stm32_write_range(const struct device *dev, unsigned int offset,
			    const void *data, unsigned int len)
{
	int rc = 0;
	int i, j;
	const uint8_t ndwords = FLASH_NB_32BITWORD_IN_FLASHWORD / 2;
	const uint8_t nbytes = FLASH_NB_32BITWORD_IN_FLASHWORD * 4;
	uint8_t unaligned_datas[nbytes];

	for (i = 0; i < len && i + 32 <= len; i += 32, offset += 32U) {
		rc = write_ndwords(dev, offset,
				   (const uint64_t *) data + (i >> 3),
				   ndwords);
		if (rc < 0) {
			return rc;
		}
	}

	/* Handle the remaining bytes if length is not aligned on
	 * FLASH_NB_32BITWORD_IN_FLASHWORD
	 */
	if (i < len) {
		memset(unaligned_datas, 0xff, sizeof(unaligned_datas));
		for (j = 0; j < len - i; ++j) {
			unaligned_datas[j] = ((uint8_t *)data)[i + j];
		}
		rc = write_ndwords(dev, offset,
				   (const uint64_t *)unaligned_datas,
				   ndwords);
		if (rc < 0) {
			return rc;
		}
	}

	return rc;
}

static int flash_stm32h7_write_protection(const struct device *dev, bool enable)
{
	FLASH_TypeDef *regs = FLASH_STM32_REGS(dev);

	int rc = 0;

	flash_stm32_sem_take(dev);

	if (enable) {
		rc = flash_stm32_wait_flash_idle(dev);
		if (rc) {
			flash_stm32_sem_give(dev);
			return rc;
		}
	}

	/* Bank 1 */
	if (enable) {
		regs->CR1 |= FLASH_CR_LOCK;
	} else {
		if (regs->CR1 & FLASH_CR_LOCK) {
			regs->KEYR1 = FLASH_KEY1;
			regs->KEYR1 = FLASH_KEY2;
		}
	}
#ifdef DUAL_BANK
	/* Bank 2 */
	if (enable) {
		regs->CR2 |= FLASH_CR_LOCK;
	} else {
		if (regs->CR2 & FLASH_CR_LOCK) {
			regs->KEYR2 = FLASH_KEY1;
			regs->KEYR2 = FLASH_KEY2;
		}
	}
#endif

	if (enable) {
		LOG_DBG("Enable write protection");
	} else {
		LOG_DBG("Disable write protection");
	}

	flash_stm32_sem_give(dev);

	return rc;
}

#ifdef CONFIG_CPU_CORTEX_M7
static void flash_stm32h7_flush_caches(const struct device *dev,
				       off_t offset, size_t len)
{
	ARG_UNUSED(dev);
	SCB_InvalidateDCache_by_Addr((uint32_t *)(CONFIG_FLASH_BASE_ADDRESS
						  + offset), len);
}
#endif /* CONFIG_CPU_CORTEX_M7 */

static int flash_stm32h7_erase(const struct device *dev, off_t offset,
			       size_t len)
{
	int rc;
#ifdef CONFIG_CPU_CORTEX_M7
	/* Flush whole sectors */
	off_t flush_offset = ROUND_DOWN(offset, FLASH_SECTOR_SIZE);
	size_t flush_len = ROUND_UP(offset + len - 1, FLASH_SECTOR_SIZE)
		 - flush_offset;
#endif /* CONFIG_CPU_CORTEX_M7 */

	if (!flash_stm32_valid_range(dev, offset, len, true)) {
		LOG_ERR("Erase range invalid. Offset: %ld, len: %zu",
			(long) offset, len);
		return -EINVAL;
	}

	if (!len) {
		return 0;
	}

	flash_stm32_sem_take(dev);

	LOG_DBG("Erase offset: %ld, len: %zu", (long) offset, len);

	rc = flash_stm32_block_erase_loop(dev, offset, len);

#ifdef CONFIG_CPU_CORTEX_M7
	/* Flush cache on all sectors affected by the erase */
	flash_stm32h7_flush_caches(dev, flush_offset, flush_len);
#elif CONFIG_CPU_CORTEX_M4
	if (LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_ART)
		&& LL_ART_IsEnabled()) {
		LOG_ERR("Cortex M4: ART enabled not supported by flash driver");
	}
#endif /* CONFIG_CPU_CORTEX_M7 */

	flash_stm32_sem_give(dev);

	return rc;
}


static int flash_stm32h7_write(const struct device *dev, off_t offset,
			       const void *data, size_t len)
{
	int rc;

	if (!flash_stm32_valid_range(dev, offset, len, true)) {
		LOG_ERR("Write range invalid. Offset: %ld, len: %zu",
			(long) offset, len);
		return -EINVAL;
	}

	if (!len) {
		return 0;
	}

	flash_stm32_sem_take(dev);

	LOG_DBG("Write offset: %ld, len: %zu", (long) offset, len);

	rc = flash_stm32_write_range(dev, offset, data, len);

	flash_stm32_sem_give(dev);

	return rc;
}

static int flash_stm32h7_read(const struct device *dev, off_t offset,
			      void *data,
			      size_t len)
{
	if (!flash_stm32_valid_range(dev, offset, len, false)) {
		LOG_ERR("Read range invalid. Offset: %ld, len: %zu",
			(long) offset, len);
		return -EINVAL;
	}

	if (!len) {
		return 0;
	}

	LOG_DBG("Read offset: %ld, len: %zu", (long) offset, len);

	memcpy(data, (uint8_t *) CONFIG_FLASH_BASE_ADDRESS + offset, len);

	return 0;
}


static const struct flash_parameters flash_stm32h7_parameters = {
	.write_block_size = FLASH_STM32_WRITE_BLOCK_SIZE,
	.erase_value = 0xff,
};

static const struct flash_parameters *
flash_stm32h7_get_parameters(const struct device *dev)
{
	ARG_UNUSED(dev);

	return &flash_stm32h7_parameters;
}


void flash_stm32_page_layout(const struct device *dev,
			     const struct flash_pages_layout **layout,
			     size_t *layout_size)
{
	ARG_UNUSED(dev);

#if defined(DUAL_BANK)
	static struct flash_pages_layout stm32h7_flash_layout[3];

	if (DISCONTINUOUS_BANKS) {
		if (stm32h7_flash_layout[0].pages_count == 0) {
			/* Bank1 */
			stm32h7_flash_layout[0].pages_count = SECTOR_PER_BANK;
			stm32h7_flash_layout[0].pages_size = FLASH_SECTOR_SIZE;
			/*
			 * Dummy page corresponding to discontinuity
			 * between bank1/2
			 */
			stm32h7_flash_layout[1].pages_count = 1;
			stm32h7_flash_layout[1].pages_size = BANK2_OFFSET
					- (SECTOR_PER_BANK * FLASH_SECTOR_SIZE);
			/* Bank2 */
			stm32h7_flash_layout[2].pages_count = SECTOR_PER_BANK;
			stm32h7_flash_layout[2].pages_size = FLASH_SECTOR_SIZE;
		}
		*layout_size = ARRAY_SIZE(stm32h7_flash_layout);
	} else {
		if (stm32h7_flash_layout[0].pages_count == 0) {
			stm32h7_flash_layout[0].pages_count =
				REAL_FLASH_SIZE_KB / FLASH_SECTOR_SIZE;
			stm32h7_flash_layout[0].pages_size = FLASH_SECTOR_SIZE;
		}
		*layout_size = 1;
	}
#else
	static struct flash_pages_layout stm32h7_flash_layout[1];

	if (stm32h7_flash_layout[0].pages_count == 0) {
		stm32h7_flash_layout[0].pages_count =
				REAL_FLASH_SIZE_KB / FLASH_SECTOR_SIZE;
		stm32h7_flash_layout[0].pages_size = FLASH_SECTOR_SIZE;
	}
	*layout_size = ARRAY_SIZE(stm32h7_flash_layout);
#endif
	*layout = stm32h7_flash_layout;
}

static struct flash_stm32_priv flash_data = {
	.regs = (FLASH_TypeDef *) DT_INST_REG_ADDR(0),
	.pclken = { .bus = STM32_CLOCK_BUS_AHB3,
		    .enr = LL_AHB3_GRP1_PERIPH_FLASH },
};

static const struct flash_driver_api flash_stm32h7_api = {
	.write_protection = flash_stm32h7_write_protection,
	.erase = flash_stm32h7_erase,
	.write = flash_stm32h7_write,
	.read = flash_stm32h7_read,
	.get_parameters = flash_stm32h7_get_parameters,
#ifdef CONFIG_FLASH_PAGE_LAYOUT
	.page_layout = flash_stm32_page_layout,
#endif
};

static int stm32h7_flash_init(const struct device *dev)
{
	struct flash_stm32_priv *p = FLASH_STM32_PRIV(dev);
	const struct device *clk = device_get_binding(STM32_CLOCK_CONTROL_NAME);

	/* enable clock */
	if (clock_control_on(clk, (clock_control_subsys_t *)&p->pclken) != 0) {
		LOG_ERR("Failed to enable clock");
		return -EIO;
	}

	flash_stm32_sem_init(dev);

	LOG_DBG("Flash initialized. BS: %zu",
		flash_stm32h7_parameters.write_block_size);

#if ((CONFIG_FLASH_LOG_LEVEL >= LOG_LEVEL_DBG) && CONFIG_FLASH_PAGE_LAYOUT)
	const struct flash_pages_layout *layout;
	size_t layout_size;

	flash_stm32_page_layout(dev, &layout, &layout_size);
	for (size_t i = 0; i < layout_size; i++) {
		LOG_DBG("Block %zu: bs: %zu count: %zu", i,
			layout[i].pages_size, layout[i].pages_count);
	}
#endif

	return flash_stm32h7_write_protection(dev, false);
}


DEVICE_DT_INST_DEFINE(0, stm32h7_flash_init, device_pm_control_nop,
		    &flash_data, NULL, POST_KERNEL,
		    CONFIG_KERNEL_INIT_PRIORITY_DEVICE, &flash_stm32h7_api);
