/*
 * Copyright (c) 2020 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <drivers/pcie/pcie.h>

#include <drivers/edac.h>
#include "ibecc.h"

/**
 * In the driver 64 bit registers are used and not all of then at the
 * moment may be correctly logged.
 */
#include <logging/log.h>
LOG_MODULE_REGISTER(edac_ibecc, CONFIG_EDAC_LOG_LEVEL);

struct ibecc_data {
	mem_addr_t mchbar;
	edac_notify_callback_f cb;

	/* Error count */
	unsigned int errors_cor;
	unsigned int errors_uc;
};

static bool ibecc_enabled(const pcie_bdf_t bdf)
{
	return !!(pcie_conf_read(bdf, CAPID0_C_REG) & CAPID0_C_IBECC_ENABLED);
}

static void ibecc_errcmd_setup(const pcie_bdf_t bdf, bool enable)
{
	uint32_t errcmd;

	errcmd = pcie_conf_read(bdf, ERRCMD_REG);

	if (enable) {
		errcmd |= (ERRCMD_IBECC_COR | ERRCMD_IBECC_UC) << 16;
	} else {
		errcmd &= ~(ERRCMD_IBECC_COR | ERRCMD_IBECC_UC) << 16;
	}

	pcie_conf_write(bdf, ERRCMD_REG, errcmd);
}

static void ibecc_errsts_clear(const pcie_bdf_t bdf)
{
	uint32_t errsts;

	errsts = pcie_conf_read(bdf, ERRSTS_REG);

	if (!(errsts & (ERRSTS_IBECC_COR | ERRSTS_IBECC_UC))) {
		return;
	}

	pcie_conf_write(bdf, ERRSTS_REG, errsts);
}

static const char *get_ddr_type(uint8_t type)
{
	switch (type) {
	case 0:
		return "DDR4";
	case 3:
		return "LPDDR4";
	default:
		return "Unknown";
	}
}

static const char *get_dimm_width(uint8_t type)
{
	switch (type) {
	case 0:
		return "X8";
	case 1:
		return "X16";
	case 2:
		return "X32";
	default:
		return "Unknown";
	}
}

static void mchbar_regs_dump(const struct device *dev)
{
	struct ibecc_data *data = dev->data;
	uint32_t mad_inter_chan, chan_hash;

	/* Memory configuration */

	chan_hash =  sys_read32(HOST_REG(data->mchbar, CHANNEL_HASH));
	LOG_DBG("Channel hash %x", chan_hash);

	mad_inter_chan = sys_read32(HOST_REG(data->mchbar, MAD_INTER_CHAN));
	LOG_DBG("DDR memory type %s",
	       get_ddr_type(INTER_CHAN_DDR_TYPE(mad_inter_chan)));

	for (int ch = 0; ch < DRAM_MAX_CHANNELS; ch++) {
		uint32_t intra_ch =
			sys_read32(HOST_REG(data->mchbar, MAD_INTRA_CH(ch)));
		uint32_t dimm_ch =
			sys_read32(HOST_REG(data->mchbar, MAD_DIMM_CH(ch)));
		uint64_t l_size = DIMM_L_SIZE(dimm_ch);
		uint64_t s_size = DIMM_S_SIZE(dimm_ch);
		uint8_t l_map = DIMM_L_MAP(intra_ch);

		LOG_DBG("channel %d: l_size 0x%llx s_size 0x%llx l_map %d\n",
			ch, l_size, s_size, l_map);

		for (int d = 0; d < DRAM_MAX_DIMMS; d++) {
			uint64_t size;
			const char *type;

			if (d ^ l_map) {
				type = get_dimm_width(DIMM_S_WIDTH(dimm_ch));
				size = s_size;
			} else {
				type = get_dimm_width(DIMM_L_WIDTH(dimm_ch));
				size = l_size;
			}

			if (!size) {
				continue;
			}

			LOG_DBG("Channel %d DIMM %d size %llu GiB width %s",
				ch, d, size >> 30, type);
		}
	}
}

static void parse_ecclog(const struct device *dev, const uint64_t ecclog)
{
	struct ibecc_data *data = dev->data;

	if (!ecclog) {
		return;
	}

	/* Note: works for small addresses */
	LOG_DBG("Error address: 0x%llx", ECC_ERROR_ERRADD(ecclog));
	LOG_DBG("Error Syndrome: 0x%lx", (long)ECC_ERROR_ERRSYND(ecclog));

	if (ecclog & ECC_ERROR_MERRSTS) {
		LOG_DBG("Uncorrectable Error (UE)");
		data->errors_uc++;
	}

	if (ecclog & ECC_ERROR_CERRSTS) {
		LOG_DBG("Correctable Error (CE)");
		data->errors_cor++;
	}
}

#if defined(CONFIG_EDAC_ERROR_INJECT)
static int inject_set_param1(const struct device *dev, uint64_t addr)
{
	struct ibecc_data *data = dev->data;

	if (addr & ~INJ_ADDR_BASE_MASK) {
		return -EINVAL;
	}

	sys_write64(addr, (mm_reg_t)((uint8_t *)data->mchbar +
				     IBECC_INJ_ADDR_BASE));

	return 0;
}

static uint64_t inject_get_param1(const struct device *dev)
{
	struct ibecc_data *data = dev->data;

	return sys_read64((mem_addr_t)((uint8_t *)data->mchbar +
				       IBECC_INJ_ADDR_BASE));
}

static int inject_set_param2(const struct device *dev, uint64_t mask)
{
	struct ibecc_data *data = dev->data;

	if (mask & ~INJ_ADDR_BASE_MASK_MASK) {
		return -EINVAL;
	}

	sys_write64(mask, (mm_reg_t)((uint8_t *)data->mchbar +
				     IBECC_INJ_ADDR_MASK));

	return 0;
}

static uint64_t inject_get_param2(const struct device *dev)
{
	struct ibecc_data *data = dev->data;

	return sys_read64((mem_addr_t)((uint8_t *)data->mchbar +
				       IBECC_INJ_ADDR_MASK));
}

static int inject_ctrl_set(const struct device *dev, uint32_t ctrl)
{
	struct ibecc_data *data = dev->data;

	sys_write32(ctrl, (mem_addr_t)((uint8_t *)data->mchbar +
				       IBECC_INJ_ADDR_CTRL));

	return 0;
}
#endif /* CONFIG_EDAC_ERROR_INJECT */

static uint64_t ecc_error_log_get(const struct device *dev)
{
	struct ibecc_data *data = dev->data;

	LOG_DBG("Get ECC Error Log");

	return sys_read64((mem_addr_t)((uint8_t *)data->mchbar +
				       IBECC_ECC_ERROR_LOG));
}

static void ecc_error_log_clear(const struct device *dev)
{
	struct ibecc_data *data = dev->data;

	LOG_DBG("Clearing ECC Error Log");

	/* Clear all error bits */
	sys_write64(ECC_ERROR_MERRSTS | ECC_ERROR_CERRSTS,
		    (mm_reg_t)((uint8_t *)data->mchbar + IBECC_ECC_ERROR_LOG));
}

static uint64_t parity_error_log_get(const struct device *dev)
{
	struct ibecc_data *data = dev->data;

	LOG_DBG("Get Parity Error Log");

	return sys_read64((mem_addr_t)((uint8_t *)data->mchbar +
				       IBECC_PARITY_ERROR_LOG));
}

static void parity_error_log_clear(const struct device *dev)
{
	struct ibecc_data *data = dev->data;

	LOG_DBG("Clearing Parity Error Log");

	sys_write64(PARITY_ERROR_ERRSTS,
		    (mm_reg_t)((uint8_t *)data->mchbar +
			       IBECC_PARITY_ERROR_LOG));
}

static unsigned int errors_cor_get(const struct device *dev)
{
	struct ibecc_data *data = dev->data;

	return data->errors_cor;
}

static unsigned int errors_uc_get(const struct device *dev)
{
	struct ibecc_data *data = dev->data;

	return data->errors_uc;
}

static int notify_callback_set(const struct device *dev,
			       edac_notify_callback_f cb)
{
	struct ibecc_data *data = dev->data;
	int key = irq_lock();

	data->cb = cb;
	irq_unlock(key);

	return 0;
}

static const struct edac_driver_api api = {
#if defined(CONFIG_EDAC_ERROR_INJECT)
	/* Error Injection functions */
	.inject_set_param1 = inject_set_param1,
	.inject_get_param1 = inject_get_param1,
	.inject_set_param2 = inject_set_param2,
	.inject_get_param2 = inject_get_param2,
	.inject_ctrl_set = inject_ctrl_set,
#endif /* CONFIG_EDAC_ERROR_INJECT */

	/* Error reporting & clearing functions */
	.ecc_error_log_get = ecc_error_log_get,
	.ecc_error_log_clear = ecc_error_log_clear,
	.parity_error_log_get = parity_error_log_get,
	.parity_error_log_clear = parity_error_log_clear,

	/* Get error stats */
	.errors_cor_get = errors_cor_get,
	.errors_uc_get = errors_uc_get,

	/* Notification callback set */
	.notify_cb_set = notify_callback_set,
};

int edac_ibecc_init(const struct device *dev)
{
	const pcie_bdf_t bdf = PCIE_BDF(0, 0, 0);
	struct ibecc_data *data = dev->data;
	uint32_t tolud;
	uint64_t touud, tom, mchbar;

	LOG_INF("EDAC IBECC initialization");

	if (!pcie_probe(bdf, PCIE_ID(PCI_VENDOR_ID_INTEL,
				     PCI_DEVICE_ID_SKU7)) &&
	    !pcie_probe(bdf, PCIE_ID(PCI_VENDOR_ID_INTEL,
				     PCI_DEVICE_ID_SKU12))) {
		LOG_ERR("Probe failed");
		return -ENODEV;
	}

	if (!ibecc_enabled(bdf)) {
		LOG_ERR("IBECC is not enabled");
		return -ENODEV;
	}

	mchbar = pcie_conf_read(bdf, MCHBAR_REG);
	mchbar |= (uint64_t)pcie_conf_read(bdf, MCHBAR_REG + 1) << 32;

	/* Check that MCHBAR is enabled */
	if (!(mchbar & MCHBAR_ENABLE)) {
		LOG_ERR("MCHBAR is not enabled");
		return -ENODEV;
	}

	mchbar &= GENMASK(38, 16);

	/* workaround for 32 bit read */
	touud = pcie_conf_read(bdf, TOUUD_REG);
	touud |= (uint64_t)pcie_conf_read(bdf, TOUUD_REG + 1) << 32;
	touud &= GENMASK(38, 20);

	/* workaround for 32 bit read */
	tom = pcie_conf_read(bdf, TOM_REG);
	tom |= (uint64_t)pcie_conf_read(bdf, TOM_REG + 1) << 32;
	tom &= GENMASK(38, 20);

	tolud = pcie_conf_read(bdf, TOLUD_REG) & GENMASK(31, 20);

	device_map(&data->mchbar, mchbar, 0x10000, K_MEM_CACHE_NONE);

	LOG_DBG("MCHBAR\t%llx", mchbar);
	LOG_DBG("TOUUD\t%llx", touud);
	LOG_DBG("TOM\t%llx", tom);
	LOG_DBG("TOLUD\t%x", tolud);

	mchbar_regs_dump(dev);

	/* Enable Host Bridge generated SERR event */
	ibecc_errcmd_setup(bdf, true);

	return 0;
}

static struct ibecc_data ibecc_data;

DEVICE_AND_API_INIT(edac_ibecc, EDAC_IBECC_NAME,
		    &edac_ibecc_init,
		    &ibecc_data, NULL,
		    POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEVICE,
		    &api);

/**
 * An IBECC error causes SERR_NMI_STS set and is indicated by
 * ERRSTS PCI registers by IBECC_UC and IBECC_COR fields.
 * Following needs to be done:
 *  - Read ECC_ERR_LOG register
 *  - Clear IBECC_UC and IBECC_COR fields of ERRSTS PCI
 *  - Clear MERRSTS & CERRSTS fields of ECC_ERR_LOG register
 */

static struct k_spinlock nmi_lock;

/* NMI handling */

static bool handle_nmi(void)
{
	uint8_t status;

	status = sys_in8(NMI_STS_CNT_REG);

	if (!(status & NMI_STS_SRC_SERR)) {
		LOG_DBG("Skip NMI, NMI_STS_CNT: 0x%x", status);
		/**
		 * We should be able to find that this NMI we
		 * should not handle and return false. However this
		 * does not work for some older SKUs
		 */
		return true;
	}

	LOG_DBG("core: %d status 0x%x", arch_curr_cpu()->id, status);

	/* Re-enable */

	status = (status & NMI_STS_MASK_EN) | NMI_STS_SERR_EN;
	sys_out8(status, NMI_STS_CNT_REG);

	status &= ~NMI_STS_SERR_EN;
	sys_out8(status, NMI_STS_CNT_REG);

	return true;
}

bool z_x86_do_kernel_nmi(const z_arch_esf_t *esf)
{
	const struct device *dev = DEVICE_GET(edac_ibecc);
	struct ibecc_data *data = dev->data;
	k_spinlock_key_t key;
	bool ret = true;
	uint64_t ecclog;

	key = k_spin_lock(&nmi_lock);

	if (!handle_nmi()) {
		/* Indicate that we do not handle this NMI */
		ret = false;
		goto out;
	}

	/* Skip the same NMI handling for other cores and return handled */
	if (arch_curr_cpu()->id) {
		ret = true;
		goto out;
	}

	ecclog = edac_ecc_error_log_get(dev);
	parse_ecclog(dev, ecclog);

	if (data->cb) {
		data->cb(dev, NULL);
	}

	edac_ecc_error_log_clear(dev);

	ibecc_errsts_clear(PCIE_BDF(0, 0, 0));

out:
	k_spin_unlock(&nmi_lock, key);

	return ret;
}
