/*
 * Copyright (c) 2022 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdint.h>
#include <errno.h>
#include <zephyr/spinlock.h>

#define LOG_DOMAIN dai_intel_dmic_nhlt
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(LOG_DOMAIN);

#include <zephyr/drivers/dai.h>
#include <adsp_clk.h>
#include "dmic.h"
#include <dmic_regs.h>
#include "dmic_nhlt.h"

extern struct dai_dmic_global_shared dai_dmic_global;

/* Base addresses (in PDM scope) of 2ch PDM controllers and coefficient RAM. */
static const uint32_t base[4] = {PDM0, PDM1, PDM2, PDM3};
static const uint32_t coef_base_a[4] = {PDM0_COEFFICIENT_A, PDM1_COEFFICIENT_A,
					PDM2_COEFFICIENT_A, PDM3_COEFFICIENT_A};
static const uint32_t coef_base_b[4] = {PDM0_COEFFICIENT_B, PDM1_COEFFICIENT_B,
					PDM2_COEFFICIENT_B, PDM3_COEFFICIENT_B};

static inline void dai_dmic_write(const struct dai_intel_dmic *dmic,
				  uint32_t reg, uint32_t val)
{
	sys_write32(val, dmic->reg_base + reg);
}

static inline uint32_t dai_dmic_read(const struct dai_intel_dmic *dmic, uint32_t reg)
{
	return sys_read32(dmic->reg_base + reg);
}

#ifdef CONFIG_SOC_SERIES_INTEL_ACE
static int dai_nhlt_get_clock_div(const struct dai_intel_dmic *dmic, const int pdm)
{
	uint32_t val;
	int p_mcic, p_clkdiv, p_mfir, rate_div;

	val = dai_dmic_read(dmic, base[pdm] + CIC_CONFIG);
	p_mcic = FIELD_GET(CIC_CONFIG_COMB_COUNT, val) + 1;

	val = dai_dmic_read(dmic, base[pdm] + MIC_CONTROL);
	p_clkdiv = FIELD_GET(MIC_CONTROL_PDM_CLKDIV, val) + 2;

	val = dai_dmic_read(dmic, base[pdm] +
			    FIR_CHANNEL_REGS_SIZE * dmic->dai_config_params.dai_index + FIR_CONFIG);
	LOG_ERR("pdm = %d, FIR_CONFIG = 0x%08X", pdm, val);

	p_mfir = FIELD_GET(FIR_CONFIG_FIR_DECIMATION, val) + 1;

	rate_div = p_clkdiv * p_mcic * p_mfir;
	LOG_ERR("dai_index = %d, rate_div = %d, p_clkdiv = %d, p_mcic = %d, p_mfir = %d",
		dmic->dai_config_params.dai_index, rate_div, p_clkdiv, p_mcic, p_mfir);

	if (!rate_div) {
		LOG_ERR("zero clock divide or decimation factor");
		return -EINVAL;
	}

	return rate_div;
}

static int dai_nhlt_update_rate(struct dai_intel_dmic *dmic, const int clock_source, const int pdm)
{
	int rate_div;

	rate_div = dai_nhlt_get_clock_div(dmic, pdm);
	if (rate_div < 0) {
		return rate_div;
	}

	dmic->dai_config_params.rate = adsp_clock_source_frequency(clock_source) /
		rate_div;

	LOG_INF("rate = %d, channels = %d, format = %d",
		dmic->dai_config_params.rate, dmic->dai_config_params.channels,
		dmic->dai_config_params.format);

	LOG_INF("io_clk %u, rate_div %d", adsp_clock_source_frequency(clock_source), rate_div);
	return 0;
}

static int dai_ipm_source_to_enable(struct dai_intel_dmic *dmic,
				    int *count, int pdm_count, int stereo,
				    int source_pdm)
{
	int mic_swap;

	if (source_pdm >= CONFIG_DAI_DMIC_HW_CONTROLLERS)
		return -EINVAL;

	if (*count < pdm_count) {
		(*count)++;
		mic_swap = FIELD_GET(MIC_CONTROL_CLK_EDGE, dai_dmic_read(dmic, base[source_pdm] +
									 MIC_CONTROL));
		if (stereo)
			dmic->enable[source_pdm] = 0x3; /* PDMi MIC A and B */
		else
			dmic->enable[source_pdm] = mic_swap ? 0x2 : 0x1; /* PDMi MIC B or MIC A */
	}

	return 0;
}

static int dai_nhlt_dmic_dai_params_get(struct dai_intel_dmic *dmic, const int clock_source)
{
	bool stereo_pdm;
	int source_pdm;
	int first_pdm;
	int num_pdm;
	int ret;
	int n;
	uint32_t outcontrol_val = dai_dmic_read(dmic, dmic->dai_config_params.dai_index *
						PDM_CHANNEL_REGS_SIZE + OUTCONTROL);

	switch (FIELD_GET(OUTCONTROL_OF, outcontrol_val)) {
	case 0:
	case 1:
		dmic->dai_config_params.format = DAI_DMIC_FRAME_S16_LE;
		dmic->dai_config_params.word_size = 16;
		break;
	case 2:
		dmic->dai_config_params.format = DAI_DMIC_FRAME_S32_LE;
		dmic->dai_config_params.word_size = 32;
		break;
	default:
		LOG_ERR("nhlt_dmic_dai_params_get(): Illegal OF bit field");
		return -EINVAL;
	}

	num_pdm = FIELD_GET(OUTCONTROL_IPM, outcontrol_val);
	if (num_pdm > CONFIG_DAI_DMIC_HW_CONTROLLERS) {
		LOG_ERR("nhlt_dmic_dai_params_get(): Illegal IPM PDM controllers count %d",
			num_pdm);
		return -EINVAL;
	}

	stereo_pdm = FIELD_GET(OUTCONTROL_IPM_SOURCE_MODE, outcontrol_val);

	dmic->dai_config_params.channels = (stereo_pdm + 1) * num_pdm;
	for (n = 0; n < CONFIG_DAI_DMIC_HW_CONTROLLERS; n++)
		dmic->enable[n] = 0;

	n = 0;
	source_pdm = FIELD_GET(OUTCONTROL_IPM_SOURCE_1, outcontrol_val);
	first_pdm = source_pdm;
	ret = dai_ipm_source_to_enable(dmic, &n, num_pdm, stereo_pdm, source_pdm);
	if (ret) {
		LOG_ERR("nhlt_dmic_dai_params_get(): Illegal IPM_SOURCE_1");
		return -EINVAL;
	}

	source_pdm = FIELD_GET(OUTCONTROL_IPM_SOURCE_2, outcontrol_val);
	ret = dai_ipm_source_to_enable(dmic, &n, num_pdm, stereo_pdm, source_pdm);
	if (ret) {
		LOG_ERR("nhlt_dmic_dai_params_get(): Illegal IPM_SOURCE_2");
		return -EINVAL;
	}

	source_pdm = FIELD_GET(OUTCONTROL_IPM_SOURCE_3, outcontrol_val);
	ret = dai_ipm_source_to_enable(dmic, &n, num_pdm, stereo_pdm, source_pdm);
	if (ret) {
		LOG_ERR("nhlt_dmic_dai_params_get(): Illegal IPM_SOURCE_3");
		return -EINVAL;
	}

	source_pdm = FIELD_GET(OUTCONTROL_IPM_SOURCE_4, outcontrol_val);
	ret = dai_ipm_source_to_enable(dmic, &n, num_pdm, stereo_pdm, source_pdm);
	if (ret) {
		LOG_ERR("nhlt_dmic_dai_params_get(): Illegal IPM_SOURCE_4");
		return -EINVAL;
	}

	return dai_nhlt_update_rate(dmic, clock_source, first_pdm);
}


/*
 * @brief Set clock source used by device
 *
 * @param source Clock source index
 */
static inline void dai_dmic_clock_select_set(const struct dai_intel_dmic *dmic, uint32_t source)
{
	uint32_t val;
#ifdef CONFIG_SOC_INTEL_ACE20_LNL /* Ace 2.0 */
	val = sys_read32(dmic->vshim_base + DMICLVSCTL_OFFSET);
	val &= ~DMICLVSCTL_MLCS;
	val |= FIELD_PREP(DMICLVSCTL_MLCS, source);
	sys_write32(val, dmic->vshim_base + DMICLVSCTL_OFFSET);
#else
	val = sys_read32(dmic->shim_base + DMICLCTL_OFFSET);
	val &= ~DMICLCTL_MLCS;
	val |= FIELD_PREP(DMICLCTL_MLCS, source);
	sys_write32(val, dmic->shim_base + DMICLCTL_OFFSET);
#endif
}

/*
 * @brief Get clock source used by device
 *
 * @return Clock source index
 */
static inline uint32_t dai_dmic_clock_select_get(const struct dai_intel_dmic *dmic)
{
	uint32_t val;
#ifdef CONFIG_SOC_INTEL_ACE20_LNL /* Ace 2.0 */
	val = sys_read32(dmic->vshim_base + DMICLVSCTL_OFFSET);
	return FIELD_GET(DMICLVSCTL_MLCS, val);
#else
	val = sys_read32(dmic->shim_base + DMICLCTL_OFFSET);
	return FIELD_GET(DMICLCTL_MLCS, val);
#endif
}

/*
 * @brief Set clock source used by device
 *
 * @param source Clock source index
 */
static int dai_dmic_set_clock(const struct dai_intel_dmic *dmic, const uint8_t clock_source)
{
	LOG_DBG("%s(): clock_source = %u", __func__, clock_source);

	if (!adsp_clock_source_is_supported(clock_source)) {
		return -ENOTSUP;
	}

#ifndef CONFIG_SOC_INTEL_ACE20_LNL /* Ace 2.0 */
	if (clock_source && !(sys_read32(dmic->shim_base + DMICLCAP_OFFSET) & DMICLCAP_MLCS)) {
		return -ENOTSUP;
	}
#endif

	dai_dmic_clock_select_set(dmic, clock_source);
	return 0;
}
#else
static int dai_nhlt_dmic_dai_params_get(struct dai_intel_dmic *dmic,
					int32_t *outcontrol,
					struct nhlt_pdm_ctrl_cfg **pdm_cfg,
					struct nhlt_pdm_ctrl_fir_cfg **fir_cfg)
{
	int fir_stereo[2];
	int mic_swap;

	switch (FIELD_GET(OUTCONTROL_OF, outcontrol[dmic->dai_config_params.dai_index])) {
	case 0:
	case 1:
		dmic->dai_config_params.format = DAI_DMIC_FRAME_S16_LE;
		break;
	case 2:
		dmic->dai_config_params.format = DAI_DMIC_FRAME_S32_LE;
		break;
	default:
		LOG_ERR("nhlt_dmic_dai_params_get(): Illegal OF bit field");
		return -EINVAL;
	}

	switch (FIELD_GET(OUTCONTROL_IPM, outcontrol[dmic->dai_config_params.dai_index])) {
	case 0:
		if (!fir_cfg[0])
			return -EINVAL;

		fir_stereo[0] = FIELD_GET(FIR_CONTROL_STEREO, fir_cfg[0]->fir_control);
		if (fir_stereo[0]) {
			dmic->dai_config_params.channels = 2;
			dmic->enable[0] = 0x3; /* PDM0 MIC A and B */
			dmic->enable[1] = 0x0;	/* PDM1 none */

		} else {
			dmic->dai_config_params.channels = 1;
			mic_swap = FIELD_GET(MIC_CONTROL_CLK_EDGE, pdm_cfg[0]->mic_control);
			dmic->enable[0] = mic_swap ? 0x2 : 0x1; /* PDM0 MIC B or MIC A */
			dmic->enable[1] = 0x0;	/* PDM1 */
		}
		break;
	case 1:
		if (!fir_cfg[1])
			return -EINVAL;

		fir_stereo[1] = FIELD_GET(FIR_CONTROL_STEREO, fir_cfg[1]->fir_control);
		if (fir_stereo[1]) {
			dmic->dai_config_params.channels = 2;
			dmic->enable[0] = 0x0; /* PDM0 none */
			dmic->enable[1] = 0x3;	/* PDM1 MIC A and B */
		} else {
			dmic->dai_config_params.channels = 1;
			dmic->enable[0] = 0x0; /* PDM0 none */
			mic_swap = FIELD_GET(MIC_CONTROL_CLK_EDGE, pdm_cfg[1]->mic_control);
			dmic->enable[1] = mic_swap ? 0x2 : 0x1; /* PDM1 MIC B or MIC A */
		}
		break;
	case 2:
		if (!fir_cfg[0] || !fir_cfg[0])
			return -EINVAL;

		fir_stereo[0] = FIELD_GET(FIR_CONTROL_STEREO, fir_cfg[0]->fir_control);
		fir_stereo[1] = FIELD_GET(FIR_CONTROL_STEREO, fir_cfg[1]->fir_control);
		if (fir_stereo[0] == fir_stereo[1]) {
			dmic->dai_config_params.channels = 4;
			dmic->enable[0] = 0x3; /* PDM0 MIC A and B */
			dmic->enable[1] = 0x3;	/* PDM1 MIC A and B */
			LOG_INF("nhlt_dmic_dai_params_get(): set 4ch pdm0 and pdm1");
		} else {
			LOG_ERR("nhlt_dmic_dai_params_get(): Illegal 4ch configuration");
			return -EINVAL;
		}
		break;
	default:
		LOG_ERR("nhlt_dmic_dai_params_get(): Illegal OF bit field");
		return -EINVAL;
	}

	return 0;
}

static inline int dai_dmic_set_clock(const struct dai_intel_dmic *dmic, const uint8_t clock_source)
{
	return 0;
}
#endif

static int print_outcontrol(uint32_t val)
{
	int bf1, bf2, bf3, bf4, bf5, bf6, bf7, bf8;
#ifdef CONFIG_SOC_SERIES_INTEL_ACE
	int bf9, bf10, bf11, bf12, bf13;
#endif
	uint32_t ref;

	bf1 = FIELD_GET(OUTCONTROL_TIE, val);
	bf2 = FIELD_GET(OUTCONTROL_SIP, val);
	bf3 = FIELD_GET(OUTCONTROL_FINIT, val);
	bf4 = FIELD_GET(OUTCONTROL_FCI, val);
	bf5 = FIELD_GET(OUTCONTROL_BFTH, val);
	bf6 = FIELD_GET(OUTCONTROL_OF, val);
	bf7 = FIELD_GET(OUTCONTROL_IPM, val);
	bf8 = FIELD_GET(OUTCONTROL_TH, val);
	LOG_INF("OUTCONTROL = %08x", val);
	LOG_INF("  tie=%d, sip=%d, finit=%d, fci=%d", bf1, bf2, bf3, bf4);
	LOG_INF("  bfth=%d, of=%d, ipm=%d, th=%d", bf5, bf6, bf7, bf8);
	if (bf5 > OUTCONTROL_BFTH_MAX) {
		LOG_WRN("illegal BFTH value %d", bf5);
		return -EINVAL;
	}

#ifdef CONFIG_SOC_SERIES_INTEL_ACE
	bf9 = FIELD_GET(OUTCONTROL_IPM_SOURCE_1, val);
	bf10 = FIELD_GET(OUTCONTROL_IPM_SOURCE_2, val);
	bf11 = FIELD_GET(OUTCONTROL_IPM_SOURCE_3, val);
	bf12 = FIELD_GET(OUTCONTROL_IPM_SOURCE_4, val);
	bf13 = FIELD_GET(OUTCONTROL_IPM_SOURCE_MODE, val);
	LOG_INF("  ipms1=%d, ipms2=%d, ipms3=%d, ipms4=%d", bf9, bf10, bf11, bf12);
	LOG_INF("  ipms_mode=%d", bf13);
	ref = FIELD_PREP(OUTCONTROL_TIE, bf1) | FIELD_PREP(OUTCONTROL_SIP, bf2) |
		FIELD_PREP(OUTCONTROL_FINIT, bf3) | FIELD_PREP(OUTCONTROL_FCI, bf4) |
		FIELD_PREP(OUTCONTROL_BFTH, bf5) | FIELD_PREP(OUTCONTROL_OF, bf6) |
		FIELD_PREP(OUTCONTROL_IPM, bf7) | FIELD_PREP(OUTCONTROL_IPM_SOURCE_1, bf9) |
		FIELD_PREP(OUTCONTROL_IPM_SOURCE_2, bf10) |
		FIELD_PREP(OUTCONTROL_IPM_SOURCE_3, bf11) |
		FIELD_PREP(OUTCONTROL_IPM_SOURCE_4, bf12) | FIELD_PREP(OUTCONTROL_TH, bf8) |
		FIELD_PREP(OUTCONTROL_IPM_SOURCE_MODE, bf13);
#else
	ref = FIELD_PREP(OUTCONTROL_TIE, bf1) | FIELD_PREP(OUTCONTROL_SIP, bf2) |
		FIELD_PREP(OUTCONTROL_FINIT, bf3) | FIELD_PREP(OUTCONTROL_FCI, bf4) |
		FIELD_PREP(OUTCONTROL_BFTH, bf5) | FIELD_PREP(OUTCONTROL_OF, bf6) |
		FIELD_PREP(OUTCONTROL_IPM, bf7) | FIELD_PREP(OUTCONTROL_TH, bf8);
#endif
	if (ref != val) {
		LOG_WRN("Some reserved bits are set in OUTCONTROL = 0x%08x", val);
	}

	return 0;
}

static void print_cic_control(uint32_t val)
{
	int bf1, bf2, bf3, bf4, bf5, bf6, bf7;
	uint32_t ref;

	bf1 = FIELD_GET(CIC_CONTROL_SOFT_RESET, val);
	bf2 = FIELD_GET(CIC_CONTROL_CIC_START_B, val);
	bf3 = FIELD_GET(CIC_CONTROL_CIC_START_A, val);
	bf4 = FIELD_GET(CIC_CONTROL_MIC_B_POLARITY, val);
	bf5 = FIELD_GET(CIC_CONTROL_MIC_A_POLARITY, val);
	bf6 = FIELD_GET(CIC_CONTROL_MIC_MUTE, val);
#ifndef CONFIG_SOC_SERIES_INTEL_ACE
	bf7 = FIELD_GET(CIC_CONTROL_STEREO_MODE, val);
#else
	bf7 = -1;
#endif
	LOG_DBG("CIC_CONTROL = %08x", val);
	LOG_DBG("  soft_reset=%d, cic_start_b=%d, cic_start_a=%d",
		bf1, bf2, bf3);
	LOG_DBG("  mic_b_polarity=%d, mic_a_polarity=%d, mic_mute=%d",
		bf4, bf5, bf6);
	ref = FIELD_PREP(CIC_CONTROL_SOFT_RESET, bf1) |
		FIELD_PREP(CIC_CONTROL_CIC_START_B, bf2) |
		FIELD_PREP(CIC_CONTROL_CIC_START_A, bf3) |
		FIELD_PREP(CIC_CONTROL_MIC_B_POLARITY, bf4) |
		FIELD_PREP(CIC_CONTROL_MIC_A_POLARITY, bf5) |
		FIELD_PREP(CIC_CONTROL_MIC_MUTE, bf6)
#ifndef CONFIG_SOC_SERIES_INTEL_ACE
		| FIELD_PREP(CIC_CONTROL_STEREO_MODE, bf7)
#endif
		;
	LOG_DBG("  stereo_mode=%d", bf7);
	if (ref != val) {
		LOG_WRN("Some reserved bits are set in CIC_CONTROL = 0x%08x", val);
	}
}

static void print_fir_control(uint32_t val)
{
	int bf1, bf2, bf3, bf4, bf5, bf6;
	uint32_t ref;

	bf1 = FIELD_GET(FIR_CONTROL_START, val);
	bf2 = FIELD_GET(FIR_CONTROL_ARRAY_START_EN, val);
#ifdef CONFIG_SOC_SERIES_INTEL_ACE
	bf3 = FIELD_GET(FIR_CONTROL_PERIODIC_START_EN, val);
#else
	bf3 = -1;
#endif
	bf4 = FIELD_GET(FIR_CONTROL_DCCOMP, val);
	bf5 = FIELD_GET(FIR_CONTROL_MUTE, val);
	bf6 = FIELD_GET(FIR_CONTROL_STEREO, val);
	LOG_DBG("FIR_CONTROL = %08x", val);
	LOG_DBG("  start=%d, array_start_en=%d, periodic_start_en=%d",
		bf1, bf2, bf3);
	LOG_DBG("  dccomp=%d, mute=%d, stereo=%d", bf4, bf5, bf6);
	ref = FIELD_PREP(FIR_CONTROL_START, bf1) |
		FIELD_PREP(FIR_CONTROL_ARRAY_START_EN, bf2) |
#ifdef CONFIG_SOC_SERIES_INTEL_ACE
		FIELD_PREP(FIR_CONTROL_PERIODIC_START_EN, bf3) |
#endif
		FIELD_PREP(FIR_CONTROL_DCCOMP, bf4) |
		FIELD_PREP(FIR_CONTROL_MUTE, bf5) |
		FIELD_PREP(FIR_CONTROL_STEREO, bf6);

	if (ref != val) {
		LOG_WRN("Some reserved bits are set in FIR_CONTROL = 0x%08x", val);
	}
}

static void print_pdm_ctrl(const struct nhlt_pdm_ctrl_cfg *pdm_cfg)
{
	int bf1, bf2, bf3, bf4, bf5;
	uint32_t val;

	LOG_DBG("CIC_CONTROL = %08x", pdm_cfg->cic_control);

	val = pdm_cfg->cic_config;
	bf1 = FIELD_GET(CIC_CONFIG_CIC_SHIFT, val);
	bf2 = FIELD_GET(CIC_CONFIG_COMB_COUNT, val);
	LOG_DBG("CIC_CONFIG = %08x", val);
	LOG_DBG("  cic_shift=%d, comb_count=%d", bf1, bf2);

	val = pdm_cfg->mic_control;

#ifndef CONFIG_SOC_SERIES_INTEL_ACE
	bf1 = FIELD_GET(MIC_CONTROL_PDM_SKEW, val);
#else
	bf1 = -1;
#endif
	bf2 = FIELD_GET(MIC_CONTROL_CLK_EDGE, val);
	bf3 = FIELD_GET(MIC_CONTROL_PDM_EN_B, val);
	bf4 = FIELD_GET(MIC_CONTROL_PDM_EN_A, val);
	bf5 = FIELD_GET(MIC_CONTROL_PDM_CLKDIV, val);
	LOG_DBG("MIC_CONTROL = %08x", val);
	LOG_DBG("  clkdiv=%d, skew=%d, clk_edge=%d", bf5, bf1, bf2);
	LOG_DBG("  en_b=%d, en_a=%d", bf3, bf4);
}

static void print_fir_config(const struct nhlt_pdm_ctrl_fir_cfg *fir_cfg)
{
	uint32_t val;
	int fir_decimation, fir_shift, fir_length;

	val = fir_cfg->fir_config;
	fir_length = FIELD_GET(FIR_CONFIG_FIR_LENGTH, val);
	fir_decimation = FIELD_GET(FIR_CONFIG_FIR_DECIMATION, val);
	fir_shift = FIELD_GET(FIR_CONFIG_FIR_SHIFT, val);
	LOG_DBG("FIR_CONFIG = %08x", val);
	LOG_DBG("  fir_decimation=%d, fir_shift=%d, fir_length=%d",
		fir_decimation, fir_shift, fir_length);

	print_fir_control(fir_cfg->fir_control);

	/* Use DC_OFFSET and GAIN as such */
	LOG_DBG("DC_OFFSET_LEFT = %08x", fir_cfg->dc_offset_left);
	LOG_DBG("DC_OFFSET_RIGHT = %08x", fir_cfg->dc_offset_right);
	LOG_DBG("OUT_GAIN_LEFT = %08x", fir_cfg->out_gain_left);
	LOG_DBG("OUT_GAIN_RIGHT = %08x", fir_cfg->out_gain_right);
}

static void configure_fir(struct dai_intel_dmic *dmic, const uint32_t base,
			  const struct nhlt_pdm_ctrl_fir_cfg *fir_cfg)
{
	uint32_t val;

	print_fir_config(fir_cfg);

	/* Use FIR_CONFIG as such */
	val = fir_cfg->fir_config;
	dai_dmic_write(dmic, base + FIR_CONFIG, val);

	val = fir_cfg->fir_control;
	print_fir_control(val);

	/* Clear START, set MUTE */
	val = (val & ~FIR_CONTROL_START) | FIR_CONTROL_MUTE;
	dai_dmic_write(dmic, base + FIR_CONTROL, val);
	LOG_DBG("FIR_CONTROL = %08x", val);

	/* Use DC_OFFSET and GAIN as such */
	dai_dmic_write(dmic, base + DC_OFFSET_LEFT, fir_cfg->dc_offset_left);
	dai_dmic_write(dmic, base + DC_OFFSET_RIGHT, fir_cfg->dc_offset_right);
	dai_dmic_write(dmic, base + OUT_GAIN_LEFT, fir_cfg->out_gain_left);
	dai_dmic_write(dmic, base + OUT_GAIN_RIGHT, fir_cfg->out_gain_right);
}

int dai_dmic_set_config_nhlt(struct dai_intel_dmic *dmic, const void *bespoke_cfg)
{
	struct nhlt_pdm_ctrl_cfg *pdm_cfg[DMIC_HW_CONTROLLERS_MAX];
	struct nhlt_pdm_ctrl_fir_cfg *fir_cfg_a[DMIC_HW_CONTROLLERS_MAX];
	struct nhlt_pdm_ctrl_fir_cfg *fir_cfg_b[DMIC_HW_CONTROLLERS_MAX];
	const uint32_t *fir_a[DMIC_HW_CONTROLLERS_MAX] = {NULL};
	const uint32_t *fir_b[DMIC_HW_CONTROLLERS_MAX];
	struct nhlt_dmic_channel_ctrl_mask *dmic_cfg;

	uint32_t out_control[DMIC_HW_FIFOS_MAX] = {0};
	uint32_t channel_ctrl_mask;
	uint32_t pdm_ctrl_mask;
	uint32_t pdm_base;
	int pdm_idx;
	uint32_t val;
	const uint8_t *p = bespoke_cfg;
	int num_fifos;
	int num_pdm;
	int fir_length_a;
	int fir_length_b;
	int n;
	int i;
	int clk_div;
	int comb_count;
	int fir_decimation, fir_length;
	int bfth;
	int ret;
	int p_mcic = 0;
	int p_mfira = 0;
	int p_mfirb = 0;
	int p_clkdiv = 0;

	if (dmic->dai_config_params.dai_index >= DMIC_HW_FIFOS_MAX) {
		LOG_ERR("dmic_set_config_nhlt(): illegal DAI index %d",
			 dmic->dai_config_params.dai_index);
		return -EINVAL;
	}

	/* Skip not used headers */
	p += sizeof(struct nhlt_dmic_gateway_attributes);
	p += sizeof(struct nhlt_dmic_ts_group);
	p += sizeof(struct nhlt_dmic_global_config);

	/* Channel_ctlr_mask bits indicate the FIFOs enabled*/
	dmic_cfg = (struct nhlt_dmic_channel_ctrl_mask *)p;
	channel_ctrl_mask = dmic_cfg->channel_ctrl_mask;
	num_fifos = POPCOUNT(channel_ctrl_mask); /* Count set bits */
	p += sizeof(struct nhlt_dmic_channel_ctrl_mask);
	LOG_DBG("dmic_set_config_nhlt(): channel_ctrl_mask = %d", channel_ctrl_mask);

	/* Configure clock source */
	ret = dai_dmic_set_clock(dmic, dmic_cfg->clock_source);
	if (ret)
		return ret;

	/* Get OUTCONTROLx configuration */
	if (num_fifos < 1 || num_fifos > DMIC_HW_FIFOS_MAX) {
		LOG_ERR("dmic_set_config_nhlt(): illegal number of FIFOs %d", num_fifos);
		return -EINVAL;
	}

	for (n = 0; n < DMIC_HW_FIFOS_MAX; n++) {
		if (!(channel_ctrl_mask & (1 << n)))
			continue;

		val = *(uint32_t *)p;
		out_control[n] = val;

		ret = print_outcontrol(val);
		if (ret) {
			return ret;
		}

		p += sizeof(uint32_t);
	}

	/* Write the FIFO control registers. The clear/set of bits is the same for
	 * all DMIC_HW_VERSION
	 */
	/* Clear TIE, SIP, FCI, set FINIT, the rest of bits as such */
	val = (out_control[dmic->dai_config_params.dai_index] &
		~(OUTCONTROL_TIE | OUTCONTROL_SIP | OUTCONTROL_FCI)) |
		OUTCONTROL_FINIT;

	dai_dmic_write(dmic, dmic->dai_config_params.dai_index * PDM_CHANNEL_REGS_SIZE +
		       OUTCONTROL, val);

	LOG_INF("dmic_set_config_nhlt(): OUTCONTROL%d = %08x",
		 dmic->dai_config_params.dai_index, val);

	/* Pass 2^BFTH to plat_data fifo depth. It will be used later in DMA
	 * configuration
	 */
	bfth = FIELD_GET(OUTCONTROL_BFTH, val);
	dmic->fifo.depth = 1 << bfth;

	/* Get PDMx registers */
	pdm_ctrl_mask = ((struct nhlt_pdm_ctrl_mask *)p)->pdm_ctrl_mask;
	num_pdm = POPCOUNT(pdm_ctrl_mask); /* Count set bits */
	p += sizeof(struct nhlt_pdm_ctrl_mask);
	LOG_DBG("dmic_set_config_nhlt(): pdm_ctrl_mask = %d", pdm_ctrl_mask);
	if (num_pdm < 1 || num_pdm > CONFIG_DAI_DMIC_HW_CONTROLLERS) {
		LOG_ERR("dmic_set_config_nhlt(): illegal number of PDMs %d", num_pdm);
		return -EINVAL;
	}

	for (pdm_idx = 0; pdm_idx < CONFIG_DAI_DMIC_HW_CONTROLLERS; pdm_idx++) {
		pdm_base = base[pdm_idx];
		fir_cfg_a[pdm_idx] = NULL;
		fir_cfg_b[pdm_idx] = NULL;

		if (!(pdm_ctrl_mask & (1 << pdm_idx))) {
			/* Set MIC_MUTE bit to unused PDM */
			dai_dmic_write(dmic, pdm_base + CIC_CONTROL, CIC_CONTROL_MIC_MUTE);
			continue;
		}

		LOG_DBG("PDM%d", pdm_idx);

		/* Get CIC configuration */
		pdm_cfg[pdm_idx] = (struct nhlt_pdm_ctrl_cfg *)p;
		p += sizeof(struct nhlt_pdm_ctrl_cfg);

		comb_count = FIELD_GET(CIC_CONFIG_COMB_COUNT, pdm_cfg[pdm_idx]->cic_config);
		p_mcic = comb_count + 1;
		clk_div = FIELD_GET(MIC_CONTROL_PDM_CLKDIV, pdm_cfg[pdm_idx]->mic_control);
		p_clkdiv = clk_div + 2;
		if (dai_dmic_global.active_fifos_mask == 0) {
			print_pdm_ctrl(pdm_cfg[pdm_idx]);

			val = pdm_cfg[pdm_idx]->cic_control;
			print_cic_control(val);

			/* Clear CIC_START_A and CIC_START_B */
			val = (val & ~(CIC_CONTROL_CIC_START_A | CIC_CONTROL_CIC_START_B));
			dai_dmic_write(dmic, pdm_base + CIC_CONTROL, val);
			LOG_DBG("dmic_set_config_nhlt(): CIC_CONTROL = %08x", val);

			/* Use CIC_CONFIG as such */
			val = pdm_cfg[pdm_idx]->cic_config;
			dai_dmic_write(dmic, pdm_base + CIC_CONFIG, val);

			/* Clear PDM_EN_A and PDM_EN_B */
			val = pdm_cfg[pdm_idx]->mic_control;
			val &= ~(MIC_CONTROL_PDM_EN_A | MIC_CONTROL_PDM_EN_B);
			dai_dmic_write(dmic, pdm_base + MIC_CONTROL, val);
			LOG_DBG("dmic_set_config_nhlt(): MIC_CONTROL = %08x", val);
		}

		configure_fir(dmic, pdm_base +
			      FIR_CHANNEL_REGS_SIZE * dmic->dai_config_params.dai_index,
			      &pdm_cfg[pdm_idx]->fir_config[dmic->dai_config_params.dai_index]);

		/* FIR A */
		fir_cfg_a[pdm_idx] = &pdm_cfg[pdm_idx]->fir_config[0];
		val = fir_cfg_a[pdm_idx]->fir_config;
		fir_length = FIELD_GET(FIR_CONFIG_FIR_LENGTH, val);
		fir_length_a = fir_length + 1; /* Need for parsing */
		fir_decimation = FIELD_GET(FIR_CONFIG_FIR_DECIMATION, val);
		p_mfira = fir_decimation + 1;

		/* FIR B */
		fir_cfg_b[pdm_idx] = &pdm_cfg[pdm_idx]->fir_config[1];
		val = fir_cfg_b[pdm_idx]->fir_config;
		fir_length = FIELD_GET(FIR_CONFIG_FIR_LENGTH, val);
		fir_length_b = fir_length + 1; /* Need for parsing */
		fir_decimation = FIELD_GET(FIR_CONFIG_FIR_DECIMATION, val);
		p_mfirb = fir_decimation + 1;

		/* Set up FIR coefficients RAM */
		val = pdm_cfg[pdm_idx]->reuse_fir_from_pdm;
		if (val == 0) {
			fir_a[pdm_idx] = (uint32_t *)p;
			p += sizeof(int32_t) * fir_length_a;
			fir_b[pdm_idx] = (uint32_t *)p;
			p += sizeof(int32_t) * fir_length_b;
		} else {
			val--;
			if (val >= pdm_idx) {
				LOG_ERR("Illegal FIR reuse 0x%x", val);
				return -EINVAL;
			}

			if (!fir_a[val]) {
				LOG_ERR("PDM%d FIR reuse from %d fail", pdm_idx, val);
				return -EINVAL;
			}

			fir_a[pdm_idx] = fir_a[val];
			fir_b[pdm_idx] = fir_b[val];
		}

		if (dmic->dai_config_params.dai_index == 0) {
			LOG_INF(
			  "dmic_set_config_nhlt(): clkdiv = %d, mcic = %d, mfir_a = %d, len = %d",
			   p_clkdiv, p_mcic, p_mfira, fir_length_a);
			for (i = 0; i < fir_length_a; i++)
				dai_dmic_write(dmic,
					       coef_base_a[pdm_idx] + (i << 2), fir_a[pdm_idx][i]);
		} else {
			LOG_INF(
			  "dmic_set_config_nhlt(): clkdiv = %d, mcic = %d, mfir_b = %d, len = %d",
			  p_clkdiv, p_mcic, p_mfirb, fir_length_b);
			for (i = 0; i < fir_length_b; i++)
				dai_dmic_write(dmic,
					       coef_base_b[pdm_idx] + (i << 2), fir_b[pdm_idx][i]);
		}
	}

#ifdef CONFIG_SOC_SERIES_INTEL_ACE
	ret = dai_nhlt_dmic_dai_params_get(dmic, dmic_cfg->clock_source);
#else
	if (dmic->dai_config_params.dai_index == 0)
		ret = dai_nhlt_dmic_dai_params_get(dmic, out_control, pdm_cfg, fir_cfg_a);
	else
		ret = dai_nhlt_dmic_dai_params_get(dmic, out_control, pdm_cfg, fir_cfg_b);
#endif
	if (ret)
		return ret;

#ifndef CONFIG_SOC_SERIES_INTEL_ACE
	if (dmic->dai_config_params.dai_index == 0)
		rate_div = p_clkdiv * p_mcic * p_mfira;
	else
		rate_div = p_clkdiv * p_mcic * p_mfirb;

	if (!rate_div) {
		LOG_ERR("dmic_set_config_nhlt(): zero clock divide or decimation factor");
		return -EINVAL;
	}

	dmic->dai_config_params.rate = adsp_clock_source_frequency(dmic_cfg->clock_source) /
		rate_div;
	LOG_INF("dmic_set_config_nhlt(): rate = %d, channels = %d, format = %d",
		 dmic->dai_config_params.rate, dmic->dai_config_params.channels,
		 dmic->dai_config_params.format);

	LOG_INF("dmic_set_config_nhlt(): io_clk %u, rate_div %d",
		adsp_clock_source_frequency(dmic_cfg->clock_source), rate_div);
#endif

	LOG_INF("dmic_set_config_nhlt(): enable0 %u, enable1 %u",
		dmic->enable[0], dmic->enable[1]);
	return 0;
}
