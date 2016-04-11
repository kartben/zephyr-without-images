/* ieee802154_cc2520_regs.h - Registers definition for TI CC2520 */

/*
 * Copyright (c) 2016 Intel Corporation.
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

#ifndef __IEEE802154_CC2520_REGS_H__
#define __IEEE802154_CC2520_REGS_H__

/* Instructions (see chapter 13) */
#define CC2520_INS_SNOP				(0x00)
#define CC2520_INS_IBUFLD			(0x02)
#define CC2520_INS_SIBUFEX			(0x03)
#define CC2520_INS_SSAMPLECCA			(0x04)
#define CC2520_INS_SRES				(0x0F)
#define CC2520_INS_MEMRD			(0x10)
#define CC2520_INS_MEMWR			(0x20)
#define CC2520_INS_RXBUF			(0x30)
#define CC2520_INS_RXBUFCP			(0x38)
#define CC2520_INS_RXBUFMOV			(0x32)
#define CC2520_INS_TXBUF			(0x3A)
#define CC2520_INS_TXBUFCP			(0x3E)
#define CC2520_INS_RANDOM			(0x3C)
#define CC2520_INS_SXOSCON			(0x40)
#define CC2520_INS_STXCAL			(0x41)
#define CC2520_INS_SRXON			(0x42)
#define CC2520_INS_STXON			(0x43)
#define CC2520_INS_STXONCCA			(0x44)
#define CC2520_INS_SRFOFF			(0x45)
#define CC2520_INS_SXOSCOFF			(0x46)
#define CC2520_INS_SFLUSHRX			(0x47)
#define CC2520_INS_SFLUSHTX			(0x48)
#define CC2520_INS_SACK				(0x49)
#define CC2520_INS_SACKPEND			(0x4A)
#define CC2520_INS_SNACK			(0x4B)
#define CC2520_INS_SRXMASKBITSET		(0x4C)
#define CC2520_INS_SRXMASKBITCLR		(0x4D)
#define CC2520_INS_RXMASKAND			(0x4E)
#define CC2520_INS_RXMASKOR			(0x4F)
#define CC2520_INS_MEMCP			(0x50)
#define CC2520_INS_MEMCPR			(0x52)
#define CC2520_INS_MEMXCP			(0x54)
#define CC2520_INS_MEMXWR			(0x56)
#define CC2520_INS_BCLR				(0x58)
#define CC2520_INS_BSET				(0x59)
#define CC2520_INS_CTR_UCTR			(0x60)
#define CC2520_INS_CBCMAC			(0x64)
#define CC2520_INS_UCBCMAC			(0x66)
#define CC2520_INS_CCM				(0x68)
#define CC2520_INS_UCCM				(0x6A)
#define CC2520_INS_ECB				(0x70)
#define CC2520_INS_ECBO				(0x72)
#define CC2520_INS_ECBX				(0x74)
#define CC2520_INS_INC				(0x78)
#define CC2520_INS_ABORT			(0x7F)
#define CC2520_INS_REGRD			(0x80)
#define CC2520_INS_REGWR			(0xC0)

/* FREG registers (see chapter 28 part 3) */
#define CC2520_FREG_FRMFILT0			(0x00)
#define FRMFILT0_FRAME_FILTER_EN		BIT(0)
#define FRMFILT0_PAN_COORDINATOR		BIT(1)
#define FRMFILT0_MAX_FRAME_VERSION(_mfv_)	(_mfv_ << 2)

#define CC2520_FREG_FRMFILT1			(0x01)
#define FRMFILT1_ACCEPT_FT_0_BEACON		BIT(3)
#define FRMFILT1_ACCEPT_FT_1_DATA		BIT(4)
#define FRMFILT1_ACCEPT_FT_2_ACK		BIT(5)
#define FRMFILT1_ACCEPT_FT_3_MAC_CMD		BIT(6)
#define FRMFILT1_ACCEPT_ALL			(FRMFILT1_ACCEPT_FT_0_BEACON | \
						 FRMFILT1_ACCEPT_FT_1_DATA | \
						 FRMFILT1_ACCEPT_FT_2_ACK | \
						 FRMFILT1_ACCEPT_FT_3_MAC_CMD)

#define CC2520_FREG_SRCMATCH			(0x02)
#define SRCMATCH_SRC_MATCH_EN			BIT(0)
#define SRCMATCH_AUTOPEND			BIT(1)
#define SRCMATCH_PEND_DATAREQ_ONLY		BIT(2)
#define SRCMATCH_DEFAULTS			(SRCMATCH_SRC_MATCH_EN | \
						 SRCMATCH_AUTOPEND | \
						 SRCMATCH_PEND_DATAREQ_ONLY)

#define CC2520_FREG_SRCSHORTEN0			(0x04)
#define CC2520_FREG_SRCSHORTEN1			(0x05)
#define CC2520_FREG_SRCSHORTEN2			(0x06)
#define CC2520_FREG_SRCEXTEN0			(0x08)
#define CC2520_FREG_SRCEXTEN1			(0x09)
#define CC2520_FREG_SRCEXTEN2			(0x0A)

#define CC2520_FREG_FRMCTRL0			(0x0C)
#define FRMCTRL0_ENERGY_SCAN			BIT(4)
#define FRMCTRL0_AUTOACK			BIT(5)
#define FRMCTRL0_AUTOCRC			BIT(6)
#define FRMCTRL0_APPEND_DATA_MODE		BIT(7)

#define CC2520_FREG_FRMCTRL1			(0x0D)
#define FRMCTRL1_SET_RXENMASK_ON_TX		BIT(0)
#define FRMCTRL1_IGNORE_TX_UNDERF		BIT(1)
#define FRMCTRL1_PENDING_OR			BIT(2)

#define CC2520_FREG_RXENABLE0			(0x0E)
#define CC2520_FREG_RXENABLE1			(0x0F)
#define CC2520_FREG_EXCFLAG0			(0x10)
#define EXCFLAG0_RF_IDLE			BIT(0)
#define EXCFLAG0_TX_FRM_DONE			BIT(1)
#define EXCFLAG0_TX_ACK_DONE			BIT(2)
#define EXCFLAG0_TX_UNDERFLOW			BIT(3)
#define EXCFLAG0_TX_OVERFLOW			BIT(4)
#define EXCFLAG0_RX_UNDERFLOW			BIT(5)
#define EXCFLAG0_RX_OVERFLOW			BIT(6)
#define EXCFLAG0_RXENABLE_ZERO			BIT(7)
#define EXCFLAG0_RESET_TX_FLAGS			((uint8_t) \
						 ~(EXCFLAG0_TX_FRM_DONE | \
						   EXCFLAG0_TX_ACK_DONE | \
						   EXCFLAG0_TX_UNDERFLOW | \
						   EXCFLAG0_TX_OVERFLOW))
#define EXCFLAG0_RESET_RX_FLAGS			((uint8_t) \
						 ~(EXCFLAG0_RX_UNDERFLOW | \
						   EXCFLAG0_RX_OVERFLOW | \
						   EXCFLAG0_RXENABLE_ZERO))

#define CC2520_FREG_EXCFLAG1			(0x11)
#define EXCFLAG1_RX_FRM_DONE			BIT(0)
#define EXCFLAG1_RX_FRM_ACCEPTED		BIT(1)
#define EXCFLAG1_SRC_MATCH_DONE			BIT(2)
#define EXCFLAG1_SRC_MATCH_FOUND		BIT(3)
#define EXCFLAG1_FIFOP				BIT(4)
#define EXCFLAG1_SFD				BIT(5)
#define EXCFLAG1_DPU_DONE_L			BIT(6)
#define EXCFLAG1_DPU_DONE_H			BIT(7)
#define EXCFLAG1_RESET_RX_FLAGS			((uint8_t) \
						 ~(EXCFLAG1_RX_FRM_DONE | \
						   EXCFLAG1_RX_FRM_ACCEPTED | \
						   EXCFLAG1_FIFOP))

#define CC2520_FREG_EXCFLAG2			(0x12)
#define EXCFLAG2_MEMADDR_ERROR			BIT(0)
#define EXCFLAG2_USAGE_ERROR			BIT(1)
#define EXCFLAG2_OPERAND_ERROR			BIT(2)
#define EXCFLAG2_SPI_ERROR			BIT(3)
#define EXCFLAG2_RF_NO_LOCK			BIT(4)
#define EXCFLAG2_RX_FRM_ABORTED			BIT(5)
#define EXCFLAG2_RFBUFMOV_TIMEOUT		BIT(6)
#define EXCFLAG2_UNUSED				BIT(7)

#define CC2520_FREG_EXMASKA0			(0x13)
#define CC2520_FREG_EXMASKA1			(0x14)
#define CC2520_FREG_EXMASKA2			(0x15)
#define CC2520_FREG_EXMASKB0			(0x18)
#define CC2520_FREG_EXMASKB1			(0x19)
#define CC2520_FREG_EXMASKB2			(0x1A)
#define CC2520_FREG_EXCBINDX0			(0x1C)
#define CC2520_FREG_EXCBINDX1			(0x1D)
#define CC2520_FREG_EXCBINDY0			(0x1E)
#define CC2520_FREG_EXCBINDY1			(0x1F)

#define CC2520_FREG_GPIOCTRL0			(0x20)
#define GPIOCTRL0_CTRL0(_ctrl_)			(_ctrl_ & 0x7F)
#define GPIOCTRL0_IN0				BIT(7)

#define CC2520_FREG_GPIOCTRL1			(0x21)
#define GPIOCTRL1_CTRL1(_ctrl_)			(_ctrl_ & 0x7F)
#define GPIOCTRL1_IN1				BIT(7)

#define CC2520_FREG_GPIOCTRL2			(0x22)
#define GPIOCTRL2_CTRL2(_ctrl_)			(_ctrl_ & 0x7F)
#define GPIOCTRL2_IN2				BIT(7)

#define CC2520_FREG_GPIOCTRL3			(0x23)
#define GPIOCTRL3_CTRL3(_ctrl_)			(_ctrl_ & 0x7F)
#define GPIOCTRL3_IN3				BIT(7)

#define CC2520_FREG_GPIOCTRL4			(0x24)
#define GPIOCTRL4_CTRL4(_ctrl_)			(_ctrl_ & 0x7F)
#define GPIOCTRL4_IN4				BIT(7)

#define CC2520_FREG_GPIOCTRL5			(0x25)
#define GPIOCTRL5_CTRL5(_ctrl_)			(_ctrl_ & 0x7F)
#define GPIOCTRL5_IN5				BIT(7)

#define CC2520_FREG_GPIOPOLARITY		(0x26)
#define GPIOPOLARITY_POLARITY0			BIT(0)
#define GPIOPOLARITY_POLARITY1			BIT(1)
#define GPIOPOLARITY_POLARITY2			BIT(2)
#define GPIOPOLARITY_POLARITY3			BIT(3)
#define GPIOPOLARITY_POLARITY4			BIT(4)
#define GPIOPOLARITY_POLARITY5			BIT(5)

#define CC2520_FREG_GPIOCTRL			(0x28)
#define GPIOCTRL_GPIO_PUE0			BIT(0)
#define GPIOCTRL_GPIO_PUE1			BIT(1)
#define GPIOCTRL_GPIO_PUE2			BIT(2)
#define GPIOCTRL_GPIO_PUE3			BIT(3)
#define GPIOCTRL_GPIO_PUE4			BIT(4)
#define GPIOCTRL_GPIO_PUE5			BIT(5)
#define GPIOCTRL_GPIO_ACTRL			BIT(6)
#define GPIOCTRL_SC				BIT(7)

#define CC2520_FREG_DPUCON			(0x2A)
#define DPUCON_RXTIMEOUT			BIT(0)

#define CC2520_FREG_DPUSTAT			(0x2B)
#define DPUSTAT_DPUL_ACTIVE			BIT(0)
#define DPUSTAT_DPUH_ACTIVE			BIT(1)
#define DPUSTAT_AUTHSTAT_L			BIT(2)
#define DPUSTAT_AUTHSTAT_H			BIT(3)

#define CC2520_FREG_FREQCTRL			(0x2E)
#define FREQCTRL_FREQ(_f_)			(_f_ & 0x7F)

#define CC2520_FREG_FREQTUNE			(0x2F)
#define FREQTUNE_XOSC32M_TUNE(_xt_)		(_xt_ & 0x07)

#define CC2520_FREG_TXPOWER			(0x30)
#define CC2520_FREG_TXCTRL			(0x31)

#define CC2520_FREG_FMSTAT0			(0x32)
#define FMSTAT0_CAL_RUNNING			BIT(6)
#define FMSTAT0_CAL_DONE			BIT(7)

#define CC2520_FREG_FMSTAT1			(0x33)
#define FMSTAT1_RX_ACTIVE			BIT(0)
#define FMSTAT1_TX_ACTIVE			BIT(1)
#define FMSTAT1_LOCK_STATUS			BIT(2)
#define FMSTAT1_CCA_SAMPLED			BIT(3)
#define FMSTAT1_CCA				BIT(4)
#define FMSTAT1_SFD				BIT(5)
#define FMSTAT1_FIFOP				BIT(6)
#define FMSTAT1_FIFO				BIT(7)

#define CC2520_FREG_FIFOPCTRL			(0x34)
#define FIFOPCTRL_FIFOP_THR(_ft_)		(_ft_ & 0x7F)

#define CC2520_FREG_FSMCTRL			(0x35)
#define FSMCTRL_RX2RX_TIME_OFF			BIT(0)
#define FSMCTRL_SLOTTED_ACK			BIT(1)

#define CC2520_FREG_CCACTRL0			(0x36)
#define CC2520_FREG_CCACTRL1			(0x37)
#define CCACTRL1_CCA_HYST(_ch_)			(_ch_ & 0x07)
#define CCACTRL1_CCA_MODE(_cm_)			((_cm_ << 3) & 0x18)

#define CC2520_FREG_RSSI			(0x38)
#define RSSI_RSSI_VALID				BIT(0)

#define CC2520_FREG_RSSISTAT			(0x39)
#define CC2520_FREG_RXFIRST			(0x3C)
#define CC2520_FREG_RXFIFOCNT			(0x3E)
#define CC2520_FREG_TXFIFOCNT			(0x3F)


/* SREG registers (see chapter 28 part 3) */
#define CC2520_SREG_CHIPID			(0x40)
#define CC2520_SREG_VERSION			(0x42)

#define CC2520_SREG_EXTCLOCK			(0x44)
#define EXTCLOCK_EXT_FREQ(_ef_)			(_ef_ & 0x1F)
#define EXTCLOCK_EXTCLOCK_EN			BIT(5)

#define CC2520_SREG_MDMCTRL0			(0x46)
#define MDMCTRL0_TX_FILTER			BIT(0)
#define MDMCTRL0_PREAMBLE_LENGTH(_pl_)		((_pl_ << 1) & 0x1E)
#define MDMCTRL0_DEMOD_AVG_MODE			BIT(5)
#define MDMCTRL0_DEM_NUM_ZEROS(_dnz_)		((_dnz_ << 6) & 0xC0)

#define CC2520_SREG_MDMCTRL1			(0x47)
#define MDMCTRL1_CORR_THR(_ct_)			(_ct_ & 0x1F)
#define MDMCTRL1_CORR_THR_SFD			BIT(5)

#define CC2520_SREG_FREQEST			(0x48)

#define CC2520_SREG_MDMTEST1			(0x49)
#define MDMTEST1_MODULATION_MODE		BIT(1)
#define MDMTEST1_RFC_SNIFF_EN			BIT(2)

#define CC2520_SREG_RXCTRL			(0x4A)
#define CC2520_SREG_FSCTRL			(0x4C)
#define CC2520_SREG_FSCAL0			(0x4E)
#define CC2520_SREG_FSCAL1			(0x4F)
#define CC2520_SREG_FSCAL2			(0x50)
#define CC2520_SREG_FSCAL3			(0x51)
#define CC2520_SREG_AGCCTRL0			(0x52)
#define CC2520_SREG_AGCCTRL1			(0x53)
#define CC2520_SREG_AGCCTRL2			(0x54)
#define CC2520_SREG_AGCCTRL3			(0x55)
#define CC2520_SREG_ADCTEST0			(0x56)
#define CC2520_SREG_ADCTEST1			(0x57)
#define CC2520_SREG_ADCTEST2			(0x58)
#define CC2520_SREG_MDMTEST0			(0x5A)
#define CC2520_SREG_DACTEST0			(0x5C)
#define CC2520_SREG_DACTEST1			(0x5D)
#define CC2520_SREG_ATEST			(0x5E)
#define CC2520_SREG_DACTEST2			(0x5F)
#define CC2520_SREG_PTEST0			(0x60)
#define CC2520_SREG_PTEST1			(0x61)
#define CC2520_SREG_DPUBIST			(0x7A)
#define CC2520_SREG_ACTBIST			(0x7C)
#define CC2520_SREG_RAMBIST			(0x7E)

/* Useful RAM addresses (see chapter 15 part 6) */
#define CC2520_MEM_SHORT_ADDR			(0x03F4)
#define CC2520_MEM_PAN_ID			(0x03F2)
#define CC2520_MEM_EXT_ADDR			(0x03EA)
#define CC2520_MEM_SRCSHORTPENDEN2		(0x03E9)
#define CC2520_MEM_SRCSHORTPENDEN1		(0x03E8)
#define CC2520_MEM_SRCSHORTPENDEN0		(0x03E7)
#define CC2520_MEM_SRCEXTPENDEN2		(0x03E6)
#define CC2520_MEM_SRCEXTPENDEN1		(0x03E5)
#define CC2520_MEM_SRCEXTPENDEN0		(0x03E4)
#define CC2520_MEM_SRCRESINDEX			(0x03E3)
#define CC2520_MEM_SRCRESMASK2			(0x03E2)
#define CC2520_MEM_SRCRESMASK1			(0x03E1)
#define CC2520_MEM_SRCRESMASK0			(0x03E0)

/* Default settings (see chapter 28 part 1) */
#define CC2520_TXPOWER_DEFAULT			(0x32)
#define CC2520_CCACTRL0_DEFAULT			(0xF8)
#define CC2520_MDMCTRL0_DEFAULT			(0x85)
#define CC2520_MDMCTRL1_DEFAULT			(0x14)
#define CC2520_RXCTRL_DEFAULT			(0x3F)
#define CC2520_FSCTRL_DEFAULT			(0x5A)
#define CC2520_FSCAL1_DEFAULT			(0x2B)
#define CC2520_AGCCTRL1_DEFAULT			(0x11)
#define CC2520_ADCTEST0_DEFAULT			(0x10)
#define CC2520_ADCTEST1_DEFAULT			(0x0E)
#define CC2520_ADCTEST2_DEFAULT			(0x03)

/* Status bits (see chapter 13 part 4) */
#define CC2520_STATUS_RX_ACTIVE			BIT(0)
#define CC2520_STATUS_TX_ACTIVE			BIT(1)
#define CC2520_STATUS_DPU_L_ACTIVE		BIT(2)
#define CC2520_STATUS_DPU_H_ACTIVE		BIT(3)
#define CC2520_STATUS_EXCEPTION_CHANNEL_B	BIT(4)
#define CC2520_STATUS_EXCEPTION_CHANNEL_A	BIT(5)
#define CC2520_STATUS_RSSI_VALID		BIT(6)
#define CC2520_STATUS_XOSC_STABLE_N_RUNNING	BIT(7)

#define CC2520_FCS_CRC_OK			(0x80)
#define CC2520_FCS_CORRELATION			(0x7f)

#endif /* __IEEE802154_CC2520_REGS_H__ */
