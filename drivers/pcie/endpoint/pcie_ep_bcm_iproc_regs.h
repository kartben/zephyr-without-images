/*
 * Copyright 2020 Broadcom
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DRIVERS_PCIE_EP_BCM_IPROC_REGS_H_
#define ZEPHYR_INCLUDE_DRIVERS_PCIE_EP_BCM_IPROC_REGS_H_

struct paxb_64 {
	uint32_t lower;
	uint32_t upper;
};

#ifdef CONFIG_PCIE_EP_BCM_IPROC_V2
struct paxb_imap {
	uint32_t lower;
	uint32_t upper;
	uint32_t axim_write_config;
	uint32_t axim_read_config;
};

struct iproc_pcie_reg {
	uint32_t paxb_clk_control;
	uint32_t paxb_ep_perst_hold_off;
	uint32_t paxb_global_control;
	uint32_t paxb_flush_control;
	uint32_t paxb_flush_status;
	uint32_t paxb_strap_status;
	uint32_t paxb_reset_status;
	uint32_t paxb_mps_mrrs_stat;
	uint32_t paxb_cfg_addr;
	uint32_t paxb_cfg_data;
	uint32_t paxb_cfg_be;
	uint32_t paxb_config_ind_addr;
	uint32_t paxb_config_ind_data;
	uint32_t paxb_config_ind_cmpl_stat;
	uint32_t paxb_config_ind_be;
	uint32_t paxb_config_ecm_addr;
	uint32_t paxb_config_ecm_data;
	uint32_t paxb_hide_func_cfg;
	uint32_t paxb_0_apb_timeout;
	uint32_t paxb_0_apb_err_en_for_cfg_rd_cmpl;
	uint32_t paxb_0_apb_err_en_for_cfg_wr_cmpl;
	uint32_t paxb_0_ur_resp_on_apb_timeout;
	uint32_t paxb_ordering_cfg;
	uint32_t paxb_master_cfg;
	uint32_t paxb_master_axid_seq_num_cfg;
	uint32_t paxb_pnpn_so_traffic_shaper_count_slow;
	uint32_t paxb_pnpn_so_traffic_shaper_count_fast;
	uint32_t paxb_pnpn_so_traffic_shaper_thrshold;
	uint32_t paxb_bdf_to_func_num_mapping;
	uint32_t paxb_atomics_cfg;
	uint32_t paxb_master_gic_its_address;
	uint32_t paxb_master_id_seq_num_avbl_status;
	uint32_t paxb_axim_rd_fsm_state;
	uint32_t paxb_atomics_status;
	uint32_t paxb_atomics_fail_addr_h_status;
	uint32_t paxb_atomics_fail_addr_l_status;
	uint32_t paxb_atomics_fail_status;
	uint32_t paxb_atomics_fail_pf_vf_num;
	uint32_t paxb_nullified_tx_pd_status;
	uint32_t paxb_nullified_tx_pd_addr_h_status;
	uint32_t paxb_nullified_tx_pd_addr_l_status;
	uint32_t paxb_ds_non_posted_crdt_default;
	uint32_t paxb_ds_posted_crdt_default;
	uint32_t paxb_ds_cmpl_crdt_default;
	uint32_t paxb_ds_cfg;
	uint32_t paxb_us_cfg;
	uint32_t paxb_axim_write_config_func0;
	uint32_t paxb_axim_read_config_func0;
	uint32_t paxb_axim_write_config_func1;
	uint32_t paxb_axim_read_config_func1;
	uint32_t paxb_axim_write_config_func2;
	uint32_t paxb_axim_read_config_func2;
	uint32_t paxb_axim_write_config_func3;
	uint32_t paxb_axim_read_config_func3;
	uint32_t paxb_axim_write_config_func4;
	uint32_t paxb_axim_read_config_func4;
	uint32_t paxb_axim_write_config_func5;
	uint32_t paxb_axim_read_config_func5;
	uint32_t paxb_axim_write_config_func6;
	uint32_t paxb_axim_read_config_func6;
	uint32_t paxb_axim_write_config_func7;
	uint32_t paxb_axim_read_config_func7;
	uint32_t paxb_axim_write_config_func8;
	uint32_t paxb_axim_read_config_func8;
	uint32_t paxb_axim_write_config_func9;
	uint32_t paxb_axim_read_config_func9;
	uint32_t paxb_axim_write_config_func10;
	uint32_t paxb_axim_read_config_func10;
	uint32_t paxb_axim_write_config_func11;
	uint32_t paxb_axim_read_config_func11;
	uint32_t paxb_axim_write_config_func12;
	uint32_t paxb_axim_read_config_func12;
	uint32_t paxb_axim_write_config_func13;
	uint32_t paxb_axim_read_config_func13;
	uint32_t paxb_axim_write_config_func14;
	uint32_t paxb_axim_read_config_func14;
	uint32_t paxb_axim_write_config_func15;
	uint32_t paxb_axim_read_config_func15;
	uint32_t paxb_default_imap_lower;
	uint32_t paxb_default_imap_upper;
	uint32_t paxb_default_imap_axim_write_config;
	uint32_t paxb_default_imap_axim_read_config;
	struct paxb_imap paxb_func0_imap0[8];
	struct paxb_imap paxb_func0_imap1[8];
	uint32_t paxb_func0_imap2;
	uint32_t paxb_func0_imap2_upper;
	uint32_t paxb_imap2_axim_write_config;
	uint32_t paxb_imap2_axim_read_config;
	uint32_t paxb_func0_imap3_0;
	uint32_t paxb_func0_imap3_0_upper;
	uint32_t paxb_imap3_0_axim_write_config;
	uint32_t paxb_imap3_0_axim_read_config;
	uint32_t paxb_func0_imap3_1;
	uint32_t paxb_func0_imap3_1_upper;
	uint32_t paxb_imap3_1_axim_write_config;
	uint32_t paxb_imap3_1_axim_read_config;
	uint32_t paxb_func0_imap3_2;
	uint32_t paxb_func0_imap3_2_upper;
	uint32_t paxb_imap3_2_axim_write_config;
	uint32_t paxb_imap3_2_axim_read_config;
	uint32_t paxb_func0_imap3_3;
	uint32_t paxb_func0_imap3_3_upper;
	uint32_t paxb_imap3_3_axim_write_config;
	uint32_t paxb_imap3_3_axim_read_config;
	uint32_t paxb_func0_imap3_4;
	uint32_t paxb_func0_imap3_4_upper;
	uint32_t paxb_imap3_4_axim_write_config;
	uint32_t paxb_imap3_4_axim_read_config;
	uint32_t paxb_func0_imap3_5;
	uint32_t paxb_func0_imap3_5_upper;
	uint32_t paxb_imap3_5_axim_write_config;
	uint32_t paxb_imap3_5_axim_read_config;
	uint32_t paxb_func0_imap3_6;
	uint32_t paxb_func0_imap3_6_upper;
	uint32_t paxb_imap3_6_axim_write_config;
	uint32_t paxb_imap3_6_axim_read_config;
	uint32_t paxb_func0_imap3_7;
	uint32_t paxb_func0_imap3_7_upper;
	uint32_t paxb_imap3_7_axim_write_config;
	uint32_t paxb_imap3_7_axim_read_config;
	uint32_t paxb_func0_imap4_0;
	uint32_t paxb_func0_imap4_0_upper;
	uint32_t paxb_imap4_0_axim_write_config;
	uint32_t paxb_imap4_0_axim_read_config;
	uint32_t paxb_func0_imap4_1;
	uint32_t paxb_func0_imap4_1_upper;
	uint32_t paxb_imap4_1_axim_write_config;
	uint32_t paxb_imap4_1_axim_read_config;
	uint32_t paxb_func0_imap4_2;
	uint32_t paxb_func0_imap4_2_upper;
	uint32_t paxb_imap4_2_axim_write_config;
	uint32_t paxb_imap4_2_axim_read_config;
	uint32_t paxb_func0_imap4_3;
	uint32_t paxb_func0_imap4_3_upper;
	uint32_t paxb_imap4_3_axim_write_config;
	uint32_t paxb_imap4_3_axim_read_config;
	uint32_t paxb_func0_imap4_4;
	uint32_t paxb_func0_imap4_4_upper;
	uint32_t paxb_imap4_4_axim_write_config;
	uint32_t paxb_imap4_4_axim_read_config;
	uint32_t paxb_func0_imap4_5;
	uint32_t paxb_func0_imap4_5_upper;
	uint32_t paxb_imap4_5_axim_write_config;
	uint32_t paxb_imap4_5_axim_read_config;
	uint32_t paxb_func0_imap4_6;
	uint32_t paxb_func0_imap4_6_upper;
	uint32_t paxb_imap4_6_axim_write_config;
	uint32_t paxb_imap4_6_axim_read_config;
	uint32_t paxb_func0_imap4_7;
	uint32_t paxb_func0_imap4_7_upper;
	uint32_t paxb_imap4_7_axim_write_config;
	uint32_t paxb_imap4_7_axim_read_config;
	struct paxb_64 paxb_iarr[5];
	uint32_t paxb_override_window0_cfg0;
	uint32_t paxb_override_window0_cfg1;
	uint32_t paxb_override_window0_write_cfg;
	uint32_t paxb_override_window0_read_cfg;
	uint32_t paxb_override_window1_cfg0;
	uint32_t paxb_override_window1_cfg1;
	uint32_t paxb_override_window1_write_cfg;
	uint32_t paxb_override_window1_read_cfg;
	uint32_t paxb_msi_base_addr_cfg;
	uint32_t paxb_msi_high_addr_cfg;
	uint32_t paxb_msi_window_write_cfg;
	uint32_t paxb_oarr_func0_msi_page;
	uint32_t paxb_oarr_func0_msi_page_upper;
	struct paxb_64 paxb_oarr[2];
	struct paxb_64 paxb_omap[2];
	uint32_t paxb_oarr_2;
	uint32_t paxb_oarr_2_upper;
	uint32_t paxb_omap_2_lower;
	uint32_t paxb_omap_2_upper;
	uint32_t paxb_oarr_3;
	uint32_t paxb_oarr_3_upper;
	uint32_t paxb_omap_3_lower;
	uint32_t paxb_omap_3_upper;
	uint32_t paxb_oarr_4;
	uint32_t paxb_oarr_4_upper;
	uint32_t paxb_omap_4_upper;
	uint32_t paxb_rc_pm_control;
	uint32_t paxb_rc_pm_status;
	uint32_t paxb_ep_pm_control;
	uint32_t paxb_ep_pm_status;
	uint32_t paxb_ep_ltr_control;
	uint32_t paxb_ep_ltr_status;
	uint32_t paxb_ep_obff_status;
	uint32_t paxb_pcie_error_status;
	uint32_t paxb_pcie_link_status;
	uint32_t paxb_ecam_cfg_0;
	uint32_t paxb_ecam_cfg_1;
	uint32_t paxb_ecam_cfg_rc;
	uint32_t paxb_ecam_crs_cfg;
	uint32_t paxb_ecam_cfg_rd_data;
	uint32_t paxb_ecam_cmpl_stat;
	uint32_t paxb_ecam_apb_err_cfg;
	uint32_t paxb_ecam_apb_ur_resp_cfg;
	uint32_t paxb_mem_pwr_cfg;
	uint32_t paxb_mem_iso_cfg;
	uint32_t paxb_mem_pwr_status;
	uint32_t paxb_free_cid_cfg;
	uint32_t paxb_free_cid_status;
	uint32_t paxb_slave_cfg;
	uint32_t paxb_slave_pf_vf_offset;
	uint32_t paxb_cmp_err_tx_cplh_status;
	uint32_t paxb_cmp_err_tx_cplh_addr_h_status;
	uint32_t paxb_cmp_err_tx_cplh_addr_l_status;
	uint32_t paxb_axi_slave_debug_status;
	uint32_t paxb_paxb_intr_status;
	uint32_t paxb_paxb_intr_en;
	uint32_t paxb_paxb_intr_clear;
	uint32_t paxb_pcie_cfg_intr_status;
	uint32_t paxb_pcie_cfg_intr_mask;
	uint32_t paxb_pcie_cfg_intr_clear;
	uint32_t paxb_master_intr_status;
	uint32_t paxb_master_intr_mask;
	uint32_t paxb_master_intr_clear;
	uint32_t paxb_slave_intr_status;
	uint32_t paxb_slave_intr_mask;
	uint32_t paxb_slave_intr_clear;
	uint32_t paxb_user_if_intr_status;
	uint32_t paxb_user_if_intr_mask;
	uint32_t paxb_user_if_intr_clear;
	uint32_t paxb_master_underflow_status;
	uint32_t paxb_master_overflow_status;
	uint32_t paxb_master_fifo_ecc_corr_status;
	uint32_t paxb_master_fifo_ecc_uncorr_status;
	uint32_t paxb_slave_underflow_status;
	uint32_t paxb_slave_overflow_status;
	uint32_t paxb_slave_ecc_err_corrected_status;
	uint32_t paxb_slave_ecc_err_uncor_status;
	uint32_t paxb_userif_underflow_status;
	uint32_t paxb_userif_overflow_status;
	uint32_t paxb_userif_ecc_err_corrected_status;
	uint32_t paxb_userif_ecc_err_uncor_status;
};
#else
struct iproc_pcie_reg {
	uint32_t paxb_clk_control;
	uint32_t paxb_rc_pm_control;
	uint32_t paxb_rc_pm_status;
	uint32_t paxb_ep_pm_control;
	uint32_t paxb_ep_pm_status;
	uint32_t paxb_ep_ltr_control;
	uint32_t paxb_ep_ltr_status;
	uint32_t paxb_reserved_0[1];
	uint32_t paxb_ep_obff_status;
	uint32_t paxb_pcie_error_status;
	uint32_t paxb_reserved_1[2];
	uint32_t paxb_paxb_endianness;
	uint32_t paxb_apb_timeout_count;
	uint32_t paxb_paxb_tx_arbiter_priority;
	uint32_t paxb_reserved_2[1];
	uint32_t paxb_paxb_rd_cmpl_buf_init_start;
	uint32_t paxb_paxb_rd_cmpl_buf_init_done;
	uint32_t paxb_pcie_ordering_rules_enable;
	uint32_t paxb_axi_slverr_en_for_mem_rd_cmpl;
	uint32_t paxb_reserved_3[44];
	uint32_t paxb_pcie_rc_axi_config;
	uint32_t paxb_pcie_ep_axi_config;
	uint32_t paxb_pcie_paxb_rx_debug_status_0;
	uint32_t paxb_pcie_paxb_rx_debug_control_0;
	uint32_t paxb_reserved_4[4];
	uint32_t paxb_config_ind_addr;
	uint32_t paxb_config_ind_data;
	uint32_t paxb_reserved_5[51];
	uint32_t paxb_cfg_be;
	uint32_t paxb_cfg_addr;
	uint32_t paxb_cfg_data;
	uint32_t paxb_pcie_sys_eq_page;
	uint32_t paxb_pcie_sys_msi_page;
	uint32_t paxb_reserved_6[2];
	uint32_t paxb_pcie_sys_msi_ctrl[6];
	uint32_t paxb_reserved_7[10];
	uint32_t paxb_pcie_sys_eq_head_0;
	uint32_t paxb_pcie_sys_eq_tail_0;
	uint32_t paxb_pcie_sys_eq_head_1;
	uint32_t paxb_pcie_sys_eq_tail_1;
	uint32_t paxb_pcie_sys_eq_head_2;
	uint32_t paxb_pcie_sys_eq_tail_2;
	uint32_t paxb_pcie_sys_eq_head_3;
	uint32_t paxb_pcie_sys_eq_tail_3;
	uint32_t paxb_pcie_sys_eq_head_4;
	uint32_t paxb_pcie_sys_eq_tail_4;
	uint32_t paxb_pcie_sys_eq_head_5;
	uint32_t paxb_pcie_sys_eq_tail_5;
	uint32_t paxb_pcie_sys_eq_tail_early[6];
	uint32_t paxb_reserved_8[2];
	uint32_t paxb_pcie_sys_eq_overwritten[6];
	uint32_t paxb_reserved_9[2];
	uint32_t paxb_pcie_sys_eq_page_upper;
	uint32_t paxb_pcie_sys_msi_page_upper;
	uint32_t paxb_reserved_10[26];
	uint32_t paxb_pcie_sys_rc_intx_en;
	uint32_t paxb_pcie_sys_rc_intx_csr;
	uint32_t paxb_reserved_11[2];
	uint32_t paxb_pcie_sys_msi_req;
	uint32_t paxb_pcie_sys_host_intr_en;
	uint32_t paxb_pcie_sys_host_intr_csr;
	uint32_t paxb_reserved_12[1];
	uint32_t paxb_pcie_sys_host_intr[4];
	uint32_t paxb_pcie_sys_ep_int_en0;
	uint32_t paxb_pcie_sys_ep_int_en1;
	uint32_t paxb_reserved_13[2];
	uint32_t paxb_pcie_sys_ep_int_csr0;
	uint32_t paxb_pcie_sys_ep_int_csr1;
	uint32_t paxb_reserved_14[2];
	uint32_t paxb_cmicd_to_pcie_intr_en;
	uint32_t paxb_reserved_15[543];
	uint32_t paxb_func0_imap0[8];
	uint32_t paxb_func1_imap0[8];
	uint32_t paxb_func0_imap0_upper[8];
	uint32_t paxb_func1_imap0_upper[8];
	uint32_t paxb_reserved_16[16];
	uint32_t paxb_func0_imap2;
	uint32_t paxb_func0_imap2_upper;
	uint32_t paxb_func1_imap2;
	uint32_t paxb_func1_imap2_upper;
	uint32_t paxb_func0_imap0_0123_regs_type;
	uint32_t paxb_reserved_17[11];
	struct paxb_64 paxb_iarr[3];
	uint32_t paxb_reserved_18[2];
	struct paxb_64 paxb_oarr[2];
	uint32_t paxb_reserved_19[1];
	uint32_t paxb_oarr_func0_msi_page;
	uint32_t paxb_oarr_func1_msi_page;
	uint32_t paxb_reserved_20[1];
	struct paxb_64 paxb_omap[2];
	uint32_t paxb_oarr_func0_msi_page_upper;
	uint32_t paxb_oarr_func1_msi_page_upper;
	uint32_t paxb_reserved_21[1];
	uint32_t paxb_func1_iarr_2_size;
	uint32_t paxb_oarr_2;
	uint32_t paxb_oarr_2_upper;
	uint32_t paxb_omap_2_lower;
	uint32_t paxb_omap_2_upper;
	struct paxb_64 paxb_func0_imap1[8];
	struct paxb_64 paxb_func1_imap1[8];
	uint32_t paxb_oarr_3;
	uint32_t paxb_oarr_3_upper;
	uint32_t paxb_omap_3_lower;
	uint32_t paxb_omap_3_upper;
	uint32_t paxb_iarr_3_lower;
	uint32_t paxb_iarr_3_upper;
	struct paxb_64 paxb_func0_imap3[8];
	uint32_t paxb_func0_imap3_axuser[8];
	uint32_t paxb_iarr_4_lower;
	uint32_t paxb_iarr_4_upper;
	struct paxb_64 paxb_func0_imap4[8];
	uint32_t paxb_func0_imap4_axuser[8];
	uint32_t paxb_default_imap_lower;
	uint32_t paxb_default_imap_upper;
	uint32_t paxb_default_imap_axuser;
	uint32_t paxb_default_imap_axcache;
	uint32_t paxb_cfg_tlp_rd_status;
	uint32_t paxb_reserved_22[7];
	uint32_t paxb_mem_control;
	uint32_t paxb_mem_ecc_err_log_0;
	uint32_t paxb_mem_ecc_err_log_1;
	uint32_t paxb_pcie_link_status;
	uint32_t paxb_strap_status;
	uint32_t paxb_reset_status;
	uint32_t paxb_reset_enable_in_pcie_link_down;
	uint32_t paxb_reserved_23[1];
	uint32_t paxb_paxb_tx_debug_cfg;
	uint32_t paxb_paxb_misc_config;
	uint32_t paxb_reserved_24[2];
	uint32_t paxb_paxb_intr_en;
	uint32_t paxb_paxb_intr_clear;
	uint32_t paxb_paxb_intr_status;
	uint32_t paxb_reserved_25[1];
	uint32_t paxb_apb_err_en_for_cfg_rd_cmpl;
	uint32_t paxb_pcie_replay_addr_buf_ecc_log;
	uint32_t paxb_pcie_replay_data_buf_ecc_log;
	uint32_t paxb_pcie_dl_to_tl_buf_ecc_log;
	uint32_t paxb_pcie_tl_to_dl_buf_ecc_log;
	uint32_t paxb_reserved_26[3];
	uint32_t paxb_func0_imap0_axuser[8];
	uint32_t paxb_func1_imap0_axuser[8];
	uint32_t paxb_func0_imap1_axuser[8];
	uint32_t paxb_func1_imap1_axuser[8];
	uint32_t paxb_func0_imap2_axuser;
	uint32_t paxb_func1_imap2_axuser;
};
#endif

static inline void pcie_write32(uint32_t data, uint32_t *addr)
{
	sys_write32(data, (mem_addr_t)addr);
}

static inline uint32_t pcie_read32(uint32_t *addr)
{
	return sys_read32((mem_addr_t)addr);
}
#endif /* ZEPHYR_INCLUDE_DRIVERS_PCIE_EP_BCM_IPROC_REGS_H_ */
