/*
 * Copyright (c) 2021 Nuvoton Technology Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <soc.h>

/* CDCG register structure check */
NPCX_REG_SIZE_CHECK(cdcg_reg, 0x116);
NPCX_REG_OFFSET_CHECK(cdcg_reg, HFCBCD, 0x010);
NPCX_REG_OFFSET_CHECK(cdcg_reg, HFCBCD2, 0x014);
NPCX_REG_OFFSET_CHECK(cdcg_reg, LFCGCTL, 0x100);
NPCX_REG_OFFSET_CHECK(cdcg_reg, LFCGCTL2, 0x114);

/* PMC register structure check */
NPCX_REG_SIZE_CHECK(pmc_reg, 0x025);
NPCX_REG_OFFSET_CHECK(pmc_reg, ENIDL_CTL, 0x003);
NPCX_REG_OFFSET_CHECK(pmc_reg, PWDWN_CTL1, 0x008);
NPCX_REG_OFFSET_CHECK(pmc_reg, PWDWN_CTL7, 0x024);

/* SCFG register structure check */
NPCX_REG_SIZE_CHECK(scfg_reg, 0x02f);
NPCX_REG_OFFSET_CHECK(scfg_reg, DEV_CTL4, 0x006);
NPCX_REG_OFFSET_CHECK(scfg_reg, DEVALT0, 0x010);
NPCX_REG_OFFSET_CHECK(scfg_reg, LV_GPIO_CTL0, 0x02a);

/* GLUE register structure check */
NPCX_REG_SIZE_CHECK(glue_reg, 0x028);
NPCX_REG_OFFSET_CHECK(glue_reg, SMB_EEN, 0x003);
NPCX_REG_OFFSET_CHECK(glue_reg, SDPD0, 0x010);
NPCX_REG_OFFSET_CHECK(glue_reg, SMB_SEL, 0x021);
NPCX_REG_OFFSET_CHECK(glue_reg, PSL_CTS, 0x027);

/* UART register structure check */
NPCX_REG_SIZE_CHECK(uart_reg, 0x027);
NPCX_REG_OFFSET_CHECK(uart_reg, UPSR, 0x00e);
NPCX_REG_OFFSET_CHECK(uart_reg, UFTSTS, 0x020);
NPCX_REG_OFFSET_CHECK(uart_reg, UFRCTL, 0x026);

/* GPIO register structure check */
NPCX_REG_SIZE_CHECK(gpio_reg, 0x008);
NPCX_REG_OFFSET_CHECK(gpio_reg, PLOCK_CTL, 0x007);

/* PWM register structure check */
NPCX_REG_SIZE_CHECK(pwm_reg, 0x00e);
NPCX_REG_OFFSET_CHECK(pwm_reg, PWMCTL, 0x004);
NPCX_REG_OFFSET_CHECK(pwm_reg, DCR, 0x006);
NPCX_REG_OFFSET_CHECK(pwm_reg, PWMCTLEX, 0x00c);

/* ADC register structure check */
NPCX_REG_SIZE_CHECK(adc_reg, 0x028);
NPCX_REG_OFFSET_CHECK(adc_reg, THRCTS, 0x01a);
NPCX_REG_OFFSET_CHECK(adc_reg, ADCCNF2, 0x020);
NPCX_REG_OFFSET_CHECK(adc_reg, MEAST, 0x026);

/* TWD register structure check */
NPCX_REG_SIZE_CHECK(twd_reg, 0x012);
NPCX_REG_OFFSET_CHECK(twd_reg, T0CSR, 0x006);
NPCX_REG_OFFSET_CHECK(twd_reg, TWMWD, 0x00e);
NPCX_REG_OFFSET_CHECK(twd_reg, WDCP, 0x010);

/* ESPI register structure check */
NPCX_REG_SIZE_CHECK(espi_reg, 0x500);
NPCX_REG_OFFSET_CHECK(espi_reg, FLASHCFG, 0x034);
NPCX_REG_OFFSET_CHECK(espi_reg, NPCX_ONLY_ESPI_REG1, 0x0f0);
NPCX_REG_OFFSET_CHECK(espi_reg, VWEVMS, 0x140);
NPCX_REG_OFFSET_CHECK(espi_reg, VWGPSM, 0x180);
NPCX_REG_OFFSET_CHECK(espi_reg, VWCTL, 0x2fc);
NPCX_REG_OFFSET_CHECK(espi_reg, OOBTXBUF, 0x380);
NPCX_REG_OFFSET_CHECK(espi_reg, OOBCTL_DIRECT, 0x3fc);
NPCX_REG_OFFSET_CHECK(espi_reg, FLASHTXBUF, 0x480);
NPCX_REG_OFFSET_CHECK(espi_reg, FLASHCTL_DIRECT, 0x4fc);

/* MSWC register structure check */
NPCX_REG_SIZE_CHECK(mswc_reg, 0x030);
NPCX_REG_OFFSET_CHECK(mswc_reg, HCBAL, 0x008);
NPCX_REG_OFFSET_CHECK(mswc_reg, HCBAH, 0x00a);
NPCX_REG_OFFSET_CHECK(mswc_reg, SRID_CR, 0x01c);
NPCX_REG_OFFSET_CHECK(mswc_reg, SID_CR, 0x020);
NPCX_REG_OFFSET_CHECK(mswc_reg, VW_SLPST1, 0x02e);

/* SHM register structure check */
NPCX_REG_SIZE_CHECK(shm_reg, 0x050);
NPCX_REG_OFFSET_CHECK(shm_reg, IMA_WIN_SIZE, 0x005);
NPCX_REG_OFFSET_CHECK(shm_reg, WIN_SIZE, 0x007);
NPCX_REG_OFFSET_CHECK(shm_reg, IMA_SEM, 0x00b);
NPCX_REG_OFFSET_CHECK(shm_reg, SHCFG, 0x00e);
NPCX_REG_OFFSET_CHECK(shm_reg, WIN1_WR_PROT, 0x010);
NPCX_REG_OFFSET_CHECK(shm_reg, IMA_WR_PROT, 0x016);
NPCX_REG_OFFSET_CHECK(shm_reg, WIN_BASE1, 0x020);
NPCX_REG_OFFSET_CHECK(shm_reg, WIN_BASE2, 0x024);
NPCX_REG_OFFSET_CHECK(shm_reg, RST_CFG, 0x03a);
NPCX_REG_OFFSET_CHECK(shm_reg, DP80BUF, 0x040);
NPCX_REG_OFFSET_CHECK(shm_reg, DP80CTL, 0x044);
NPCX_REG_OFFSET_CHECK(shm_reg, HOFS_STS, 0x048);
NPCX_REG_OFFSET_CHECK(shm_reg, COFS1, 0x04c);

/* KBC register structure check */
NPCX_REG_SIZE_CHECK(kbc_reg, 0x00c);
NPCX_REG_OFFSET_CHECK(kbc_reg, HIKMDI, 0x00a);
NPCX_REG_OFFSET_CHECK(kbc_reg, SHIKMDI, 0x00b);

/* PMCH register structure check */
NPCX_REG_SIZE_CHECK(pmch_reg, 0x012);
NPCX_REG_OFFSET_CHECK(pmch_reg, HIPMDO, 0x002);
NPCX_REG_OFFSET_CHECK(pmch_reg, HIPMDOC, 0x006);
NPCX_REG_OFFSET_CHECK(pmch_reg, HIPMDOM, 0x008);
NPCX_REG_OFFSET_CHECK(pmch_reg, HIPMDIC, 0x00a);
NPCX_REG_OFFSET_CHECK(pmch_reg, HIPMIE, 0x010);

/* C2H register structure check */
NPCX_REG_SIZE_CHECK(c2h_reg, 0x00c);
NPCX_REG_OFFSET_CHECK(c2h_reg, LKSIOHA, 0x004);
NPCX_REG_OFFSET_CHECK(c2h_reg, CRSMAE, 0x008);
NPCX_REG_OFFSET_CHECK(c2h_reg, SIBCTRL, 0x00a);

/* SMB register structure check */
NPCX_REG_SIZE_CHECK(smb_reg, 0x020);
NPCX_REG_OFFSET_CHECK(smb_reg, SMBCTL1, 0x006);
NPCX_REG_OFFSET_CHECK(smb_reg, SMBT_OUT, 0x00f);
NPCX_REG_OFFSET_CHECK(smb_reg, SMBADDR6, 0x016);
NPCX_REG_OFFSET_CHECK(smb_reg, SMBSCLHT, 0x01e);

NPCX_REG_SIZE_CHECK(smb_fifo_reg, 0x020);
NPCX_REG_OFFSET_CHECK(smb_fifo_reg, SMBT_OUT, 0x00f);
NPCX_REG_OFFSET_CHECK(smb_fifo_reg, SMBCST2, 0x018);
NPCX_REG_OFFSET_CHECK(smb_fifo_reg, SMBTXF_STS, 0x01a);
NPCX_REG_OFFSET_CHECK(smb_fifo_reg, SMBRXF_CTL, 0x01e);

/* ITIM register structure check */
NPCX_REG_SIZE_CHECK(itim32_reg, 0x00c);
NPCX_REG_OFFSET_CHECK(itim32_reg, ITPRE32, 0x001);
NPCX_REG_OFFSET_CHECK(itim32_reg, ITCTS32, 0x004);
NPCX_REG_OFFSET_CHECK(itim32_reg, ITCNT32, 0x008);

NPCX_REG_SIZE_CHECK(itim64_reg, 0x010);
NPCX_REG_OFFSET_CHECK(itim64_reg, ITPRE64, 0x001);
NPCX_REG_OFFSET_CHECK(itim64_reg, ITCTS64, 0x004);
NPCX_REG_OFFSET_CHECK(itim64_reg, ITCNT64L, 0x008);
NPCX_REG_OFFSET_CHECK(itim64_reg, ITCNT64H, 0x00c);

/* TACH register structure check */
NPCX_REG_SIZE_CHECK(tach_reg, 0x01e);
NPCX_REG_OFFSET_CHECK(tach_reg, TPRSC, 0x008);
NPCX_REG_OFFSET_CHECK(tach_reg, TECLR, 0x010);
NPCX_REG_OFFSET_CHECK(tach_reg, TCPA, 0x014);
NPCX_REG_OFFSET_CHECK(tach_reg, TCPCFG, 0x018);
NPCX_REG_OFFSET_CHECK(tach_reg, TCFG, 0x01c);

/* Debug Interface register structure check */
NPCX_REG_SIZE_CHECK(dbg_reg, 0x06);
NPCX_REG_OFFSET_CHECK(dbg_reg, DBGCTRL, 0x000);
NPCX_REG_OFFSET_CHECK(dbg_reg, DBGFRZEN2, 0x003);
NPCX_REG_OFFSET_CHECK(dbg_reg, DBGFRZEN4, 0x005);

/* PS/2 Interface register structure check */
NPCX_REG_SIZE_CHECK(ps2_reg, 0x00c);
NPCX_REG_OFFSET_CHECK(ps2_reg, PSDAT, 0x000);
NPCX_REG_OFFSET_CHECK(ps2_reg, PSTAT, 0x002);
NPCX_REG_OFFSET_CHECK(ps2_reg, PSCON, 0x004);
NPCX_REG_OFFSET_CHECK(ps2_reg, PSOSIG, 0x006);
NPCX_REG_OFFSET_CHECK(ps2_reg, PSISIG, 0x008);
NPCX_REG_OFFSET_CHECK(ps2_reg, PSIEN, 0x00a);

/* FIU register structure check */
NPCX_REG_SIZE_CHECK(fiu_reg, 0x034);
NPCX_REG_OFFSET_CHECK(fiu_reg, BURST_CFG, 0x001);
NPCX_REG_OFFSET_CHECK(fiu_reg, SPI_FL_CFG, 0x014);
NPCX_REG_OFFSET_CHECK(fiu_reg, UMA_CTS, 0x01e);
NPCX_REG_OFFSET_CHECK(fiu_reg, CRCCON, 0x026);
NPCX_REG_OFFSET_CHECK(fiu_reg, FIU_RD_CMD, 0x030);
NPCX_REG_OFFSET_CHECK(fiu_reg, FIU_EXT_CFG, 0x033);

/* PECI register structure check */
NPCX_REG_SIZE_CHECK(peci_reg, 0x050);
NPCX_REG_OFFSET_CHECK(peci_reg, PECI_ADDR, 0x002);
NPCX_REG_OFFSET_CHECK(peci_reg, PECI_WR_LENGTH, 0x007);
NPCX_REG_OFFSET_CHECK(peci_reg, PECI_WR_FCS, 0x00b);
