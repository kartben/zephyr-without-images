/*
 * Copyright (c) 2016 Intel Corporation
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_USB_COMMON_USB_DWC2_HW
#define ZEPHYR_DRIVERS_USB_COMMON_USB_DWC2_HW

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* This file describes register set for the DesignWare USB 2.0 controller IP */

/* IN endpoint register block */
struct usb_dwc2_in_ep {
	volatile uint32_t diepctl;
	uint32_t reserved;
	volatile uint32_t diepint;
	uint32_t reserved1;
	volatile uint32_t dieptsiz;
	volatile uint32_t diepdma;
	volatile uint32_t dtxfsts;
	volatile uint32_t diepdmab;
};

/* OUT endpoint register block */
struct usb_dwc2_out_ep {
	volatile uint32_t doepctl;
	uint32_t reserved;
	volatile uint32_t doepint;
	uint32_t reserved1;
	volatile uint32_t doeptsiz;
	volatile uint32_t doepdma;
	uint32_t reserved2;
	volatile uint32_t doepdmab;
};

/* DWC2 register map
 * TODO: This should probably be split into global, host, and device register
 * blocks
 */
struct usb_dwc2_reg {
	volatile uint32_t gotgctl;
	volatile uint32_t gotgint;
	volatile uint32_t gahbcfg;
	volatile uint32_t gusbcfg;
	volatile uint32_t grstctl;
	volatile uint32_t gintsts;
	volatile uint32_t gintmsk;
	volatile uint32_t grxstsr;
	volatile uint32_t grxstsp;
	volatile uint32_t grxfsiz;
	volatile uint32_t gnptxfsiz;
	volatile uint32_t gnptxsts;
	volatile uint32_t gi2cctl;
	volatile uint32_t gpvndctl;
	volatile uint32_t ggpio;
	volatile uint32_t guid;
	volatile uint32_t gsnpsid;
	volatile uint32_t ghwcfg1;
	volatile uint32_t ghwcfg2;
	volatile uint32_t ghwcfg3;
	volatile uint32_t ghwcfg4;
	volatile uint32_t glpmcfg;
	volatile uint32_t gpwrdn;
	volatile uint32_t gdfifocfg;
	volatile uint32_t gadpctl;
	volatile uint32_t grefclk;
	volatile uint32_t gintmsk2;
	volatile uint32_t gintsts2;
	volatile uint32_t reserved1[36];
	volatile uint32_t hptxfsiz;
	union {
		volatile uint32_t dptxfsiz[15];
		volatile uint32_t dieptxf[15];
	};
	volatile uint32_t reserved2[176];
	/* Host mode register 0x0400 .. 0x0670 */
	uint32_t reserved3[256];
	/* Device mode register 0x0800 .. 0x0D00 */
	volatile uint32_t dcfg;
	volatile uint32_t dctl;
	volatile uint32_t dsts;
	uint32_t reserved4;
	volatile uint32_t diepmsk;
	volatile uint32_t doepmsk;
	volatile uint32_t daint;
	volatile uint32_t daintmsk;
	volatile uint32_t dtknqr1;
	volatile uint32_t dtknqr2;
	volatile uint32_t dvbusdis;
	volatile uint32_t dvbuspulse;
	union {
		volatile uint32_t dtknqr3;
		volatile uint32_t dthrctl;
	};
	union {
		volatile uint32_t dtknqr4;
		volatile uint32_t diepempmsk;
	};
	volatile uint32_t deachint;
	volatile uint32_t deachintmsk;
	volatile uint32_t diepeachmsk[16];
	volatile uint32_t doepeachmsk[16];
	volatile uint32_t reserved5[16];
	struct usb_dwc2_in_ep in_ep[16];
	struct usb_dwc2_out_ep out_ep[16];
};

/*
 * With the maximum number of supported endpoints, register map
 * of the controller must be equal to 0x0D00.
 */
BUILD_ASSERT(sizeof(struct usb_dwc2_reg) == 0x0D00);

/*
 * GET_FIELD/SET_FIELD macros below are intended to be used to define functions
 * to get/set a bitfield of a register from/into a value. They should not be
 * used to get/set a bitfield consisting of only one bit.
 */
#define USB_DWC2_GET_FIELD_DEFINE(name, reg_name_and_field)			\
	static inline uint32_t usb_dwc2_get_##name(const uint32_t value)	\
	{									\
		return (value & USB_DWC2_##reg_name_and_field##_MASK) >>	\
			USB_DWC2_##reg_name_and_field##_POS;			\
	}

#define USB_DWC2_SET_FIELD_DEFINE(name, reg_name_and_field)			\
	static inline uint32_t usb_dwc2_set_##name(const uint32_t value)	\
	{									\
		return (value << USB_DWC2_##reg_name_and_field##_POS) &		\
			USB_DWC2_##reg_name_and_field##_MASK;			\
	}

#define USB_DWC2_GET_FIELD_AND_IDX_DEFINE(name, reg_name_and_field)		\
	static inline uint32_t usb_dwc2_get_##name(const uint32_t value,	\
						   const uint32_t idx)		\
	{									\
		return (value & USB_DWC2_##reg_name_and_field##_MASK(idx)) >>	\
			USB_DWC2_##reg_name_and_field##_POS(idx);		\
	}

/* AHB configuration register */
#define USB_DWC2_GAHBCFG			0x0008UL
#define USB_DWC2_GAHBCFG_DMAEN_POS		5UL
#define USB_DWC2_GAHBCFG_DMAEN			BIT(USB_DWC2_GAHBCFG_DMAEN_POS)
#define USB_DWC2_GAHBCFG_GLBINTRMASK_POS	0UL
#define USB_DWC2_GAHBCFG_GLBINTRMASK		BIT(USB_DWC2_GAHBCFG_GLBINTRMASK_POS)

/* USB configuration register */
#define USB_DWC2_GUSBCFG			0x000CUL
#define USB_DWC2_GUSBCFG_FORCEDEVMODE_POS	30UL
#define USB_DWC2_GUSBCFG_FORCEDEVMODE		BIT(USB_DWC2_GUSBCFG_FORCEDEVMODE_POS)
#define USB_DWC2_GUSBCFG_FORCEHSTMODE_POS	29UL
#define USB_DWC2_GUSBCFG_FORCEHSTMODE		BIT(USB_DWC2_GUSBCFG_FORCEHSTMODE_POS)
#define USB_DWC2_GUSBCFG_PHYSEL_POS		6UL
#define USB_DWC2_GUSBCFG_PHYSEL_USB11		BIT(USB_DWC2_GUSBCFG_PHYSEL_POS)
#define USB_DWC2_GUSBCFG_PHYSEL_USB20		0UL
#define USB_DWC2_GUSBCFG_ULPI_UTMI_SEL_POS	4UL
#define USB_DWC2_GUSBCFG_ULPI_UTMI_SEL_ULPI	BIT(USB_DWC2_GUSBCFG_ULPI_UTMI_SEL_POS)
#define USB_DWC2_GUSBCFG_ULPI_UTMI_SEL_UTMI	0UL
#define USB_DWC2_GUSBCFG_PHYIF_POS		3UL
#define USB_DWC2_GUSBCFG_PHYIF_16_BIT		BIT(USB_DWC2_GUSBCFG_PHYIF_POS)
#define USB_DWC2_GUSBCFG_PHYIF_8_BIT		0UL

/* Reset register */
#define USB_DWC2_GRSTCTL			0x0010UL
#define USB_DWC2_GRSTCTL_AHBIDLE_POS		31UL
#define USB_DWC2_GRSTCTL_AHBIDLE		BIT(USB_DWC2_GRSTCTL_AHBIDLE_POS)
#define USB_DWC2_GRSTCTL_CSFTRSTDONE_POS	29UL
#define USB_DWC2_GRSTCTL_CSFTRSTDONE		BIT(USB_DWC2_GRSTCTL_CSFTRSTDONE_POS)
#define USB_DWC2_GRSTCTL_TXFNUM_POS		6UL
#define USB_DWC2_GRSTCTL_TXFNUM_MASK		(0x1FUL << USB_DWC2_GRSTCTL_TXFNUM_POS)
#define USB_DWC2_GRSTCTL_TXFFLSH_POS		5UL
#define USB_DWC2_GRSTCTL_TXFFLSH		BIT(USB_DWC2_GRSTCTL_TXFFLSH_POS)
#define USB_DWC2_GRSTCTL_RXFFLSH_POS		4UL
#define USB_DWC2_GRSTCTL_RXFFLSH		BIT(USB_DWC2_GRSTCTL_RXFFLSH_POS)
#define USB_DWC2_GRSTCTL_CSFTRST_POS		0UL
#define USB_DWC2_GRSTCTL_CSFTRST		BIT(USB_DWC2_GRSTCTL_CSFTRST_POS)

USB_DWC2_SET_FIELD_DEFINE(grstctl_txfnum, GRSTCTL_TXFNUM)

/* Core interrupt registers */
#define USB_DWC2_GINTSTS			0x0014UL
#define USB_DWC2_GINTMSK			0x0018UL
#define USB_DWC2_GINTSTS_WKUPINT_POS		31UL
#define USB_DWC2_GINTSTS_WKUPINT		BIT(USB_DWC2_GINTSTS_WKUPINT_POS)
#define USB_DWC2_GINTSTS_OEPINT_POS		19UL
#define USB_DWC2_GINTSTS_OEPINT			BIT(USB_DWC2_GINTSTS_OEPINT_POS)
#define USB_DWC2_GINTSTS_IEPINT_POS		18UL
#define USB_DWC2_GINTSTS_IEPINT			BIT(USB_DWC2_GINTSTS_IEPINT_POS)
#define USB_DWC2_GINTSTS_ENUMDONE_POS		13UL
#define USB_DWC2_GINTSTS_ENUMDONE		BIT(USB_DWC2_GINTSTS_ENUMDONE_POS)
#define USB_DWC2_GINTSTS_USBRST_POS		12UL
#define USB_DWC2_GINTSTS_USBRST			BIT(USB_DWC2_GINTSTS_USBRST_POS)
#define USB_DWC2_GINTSTS_USBSUSP_POS		11UL
#define USB_DWC2_GINTSTS_USBSUSP		BIT(USB_DWC2_GINTSTS_USBSUSP_POS)
#define USB_DWC2_GINTSTS_RXFLVL_POS		4UL
#define USB_DWC2_GINTSTS_RXFLVL			BIT(USB_DWC2_GINTSTS_RXFLVL_POS)
#define USB_DWC2_GINTSTS_SOF_POS		3UL
#define USB_DWC2_GINTSTS_SOF			BIT(USB_DWC2_GINTSTS_SOF_POS)
#define USB_DWC2_GINTSTS_OTGINT_POS		2UL
#define USB_DWC2_GINTSTS_OTGINT			BIT(USB_DWC2_GINTSTS_OTGINT_POS)

/* Status read and pop registers */
#define USB_DWC2_GRXSTSR			0x001CUL
#define USB_DWC2_GRXSTSP			0x0020UL
#define USB_DWC2_GRXSTSR_PKTSTS_POS		17UL
#define USB_DWC2_GRXSTSR_PKTSTS_MASK		(0xFUL << USB_DWC2_GRXSTSR_PKTSTS_POS)
#define USB_DWC2_GRXSTSR_PKTSTS_OUT_DATA	2
#define USB_DWC2_GRXSTSR_PKTSTS_OUT_DATA_DONE	3
#define USB_DWC2_GRXSTSR_PKTSTS_SETUP_DONE	4
#define USB_DWC2_GRXSTSR_PKTSTS_SETUP		6
#define USB_DWC2_GRXSTSR_BCNT_POS		4UL
#define USB_DWC2_GRXSTSR_BCNT_MASK		(0x000007FFUL << USB_DWC2_GRXSTSR_BCNT_POS)
#define USB_DWC2_GRXSTSR_EPNUM_POS		0UL
#define USB_DWC2_GRXSTSR_EPNUM_MASK		0x0000000FUL
#define USB_DWC2_GRXSTSR_CHNUM_POS		0UL
#define USB_DWC2_GRXSTSR_CHNUM_MASK		0x0000000FUL

USB_DWC2_GET_FIELD_DEFINE(grxstsp_pktsts, GRXSTSR_PKTSTS)
USB_DWC2_GET_FIELD_DEFINE(grxstsp_bcnt, GRXSTSR_BCNT)
USB_DWC2_GET_FIELD_DEFINE(grxstsp_epnum, GRXSTSR_EPNUM)

/* Receive FIFO size register (device mode) */
#define USB_DWC2_GRXFSIZ			0x0024UL
#define USB_DWC2_GRXFSIZ_RXFDEP_POS		0UL
#define USB_DWC2_GRXFSIZ_RXFDEP_MASK		(0xFFFFUL << USB_DWC2_GRXFSIZ_RXFDEP_POS)

USB_DWC2_GET_FIELD_DEFINE(grxfsiz, GRXFSIZ_RXFDEP)
USB_DWC2_SET_FIELD_DEFINE(grxfsiz, GRXFSIZ_RXFDEP)

/* Non-periodic transmit FIFO size register (device mode) */
#define USB_DWC2_GNPTXFSIZ			0x0028UL
#define USB_DWC2_GNPTXFSIZ_NPTXFDEP_POS		16UL
#define USB_DWC2_GNPTXFSIZ_NPTXFDEP_MASK	(0xFFFFUL << USB_DWC2_GNPTXFSIZ_NPTXFDEP_POS)
#define USB_DWC2_GNPTXFSIZ_NPTXFSTADDR_POS	0UL
#define USB_DWC2_GNPTXFSIZ_NPTXFSTADDR_MASK	(0xFFFFUL << USB_DWC2_GNPTXFSIZ_NPTXFSTADDR_POS)

USB_DWC2_GET_FIELD_DEFINE(gnptxfsiz_nptxfdep, GNPTXFSIZ_NPTXFDEP)
USB_DWC2_GET_FIELD_DEFINE(gnptxfsiz_nptxfstaddr, GNPTXFSIZ_NPTXFSTADDR)
USB_DWC2_SET_FIELD_DEFINE(gnptxfsiz_nptxfdep, GNPTXFSIZ_NPTXFDEP)
USB_DWC2_SET_FIELD_DEFINE(gnptxfsiz_nptxfstaddr, GNPTXFSIZ_NPTXFSTADDR)

/* Application (vendor) general purpose registers */
#define USB_DWC2_GGPIO				0x0038UL
#define USB_DWC2_GGPIO_STM32_VBDEN_POS		21UL
#define USB_DWC2_GGPIO_STM32_VBDEN		BIT(USB_DWC2_GGPIO_STM32_VBDEN_POS)
#define USB_DWC2_GGPIO_STM32_PWRDWN_POS		16UL
#define USB_DWC2_GGPIO_STM32_PWRDWN		BIT(USB_DWC2_GGPIO_STM32_PWRDWN_POS)

/* GHWCFG1 register */
#define USB_DWC2_GHWCFG1			0x0044UL
#define USB_DWC2_GHWCFG1_EPDIR_POS(i)		(i * 2)
#define USB_DWC2_GHWCFG1_EPDIR_MASK(i)		(0x3UL << USB_DWC2_GHWCFG1_EPDIR_POS(i))
#define USB_DWC2_GHWCFG1_EPDIR_OUT		2
#define USB_DWC2_GHWCFG1_EPDIR_IN		1
#define USB_DWC2_GHWCFG1_EPDIR_BDIR		0

USB_DWC2_GET_FIELD_AND_IDX_DEFINE(ghwcfg1_epdir, GHWCFG1_EPDIR)

/* GHWCFG2 register */
#define USB_DWC2_GHWCFG2			0x0048UL
#define USB_DWC2_GHWCFG2_DYNFIFOSIZING_POS	19UL
#define USB_DWC2_GHWCFG2_DYNFIFOSIZING		BIT(USB_DWC2_GHWCFG2_DYNFIFOSIZING_POS)
#define USB_DWC2_GHWCFG2_NUMDEVEPS_POS		10UL
#define USB_DWC2_GHWCFG2_NUMDEVEPS_MASK		(0xFUL << USB_DWC2_GHWCFG2_NUMDEVEPS_POS)
#define USB_DWC2_GHWCFG2_FSPHYTYPE_POS		8UL
#define USB_DWC2_GHWCFG2_FSPHYTYPE_MASK		(0x3UL << USB_DWC2_GHWCFG2_FSPHYTYPE_POS)
#define USB_DWC2_GHWCFG2_FSPHYTYPE_FSPLUSULPI	3
#define USB_DWC2_GHWCFG2_FSPHYTYPE_FSPLUSUTMI	2
#define USB_DWC2_GHWCFG2_FSPHYTYPE_FS		1
#define USB_DWC2_GHWCFG2_FSPHYTYPE_NO_FS	0
#define USB_DWC2_GHWCFG2_HSPHYTYPE_POS		6UL
#define USB_DWC2_GHWCFG2_HSPHYTYPE_MASK		(0x3UL << USB_DWC2_GHWCFG2_HSPHYTYPE_POS)
#define USB_DWC2_GHWCFG2_HSPHYTYPE_UTMIPLUSULPI	3
#define USB_DWC2_GHWCFG2_HSPHYTYPE_ULPI		2
#define USB_DWC2_GHWCFG2_HSPHYTYPE_UTMIPLUS	1
#define USB_DWC2_GHWCFG2_HSPHYTYPE_NO_HS	0
#define USB_DWC2_GHWCFG2_OTGARCH_POS		3UL
#define USB_DWC2_GHWCFG2_OTGARCH_MASK		(0x3UL << USB_DWC2_GHWCFG2_OTGARCH_POS)
#define USB_DWC2_GHWCFG2_OTGARCH_INTERNALDMA	2
#define USB_DWC2_GHWCFG2_OTGARCH_EXTERNALDMA	1
#define USB_DWC2_GHWCFG2_OTGARCH_SLAVEMODE	0
#define USB_DWC2_GHWCFG2_OTGMODE_POS		0UL
#define USB_DWC2_GHWCFG2_OTGMODE_MASK		(0x7UL << USB_DWC2_GHWCFG2_OTGMODE_POS)
#define USB_DWC2_GHWCFG2_OTGMODE_NONOTGH	6
#define USB_DWC2_GHWCFG2_OTGMODE_SRPCAPH	5
#define USB_DWC2_GHWCFG2_OTGMODE_NONOTGD	4
#define USB_DWC2_GHWCFG2_OTGMODE_SRPCAPD	3
#define USB_DWC2_GHWCFG2_OTGMODE_NHNPNSRP	2
#define USB_DWC2_GHWCFG2_OTGMODE_SRPOTG		1
#define USB_DWC2_GHWCFG2_OTGMODE_HNPSRP		0

USB_DWC2_GET_FIELD_DEFINE(ghwcfg2_numdeveps, GHWCFG2_NUMDEVEPS)
USB_DWC2_GET_FIELD_DEFINE(ghwcfg2_fsphytype, GHWCFG2_FSPHYTYPE)
USB_DWC2_GET_FIELD_DEFINE(ghwcfg2_hsphytype, GHWCFG2_HSPHYTYPE)
USB_DWC2_GET_FIELD_DEFINE(ghwcfg2_otgarch, GHWCFG2_OTGARCH)
USB_DWC2_GET_FIELD_DEFINE(ghwcfg2_otgmode, GHWCFG2_OTGMODE)

/* GHWCFG3 register */
#define USB_DWC2_GHWCFG3			0x004CUL
#define USB_DWC2_GHWCFG3_DFIFODEPTH_POS		16UL
#define USB_DWC2_GHWCFG3_DFIFODEPTH_MASK	(0xFFFFUL << USB_DWC2_GHWCFG3_DFIFODEPTH_POS)
#define USB_DWC2_GHWCFG3_LPMMODE_POS		15UL
#define USB_DWC2_GHWCFG3_LPMMODE		BIT(USB_DWC2_GHWCFG3_LPMMODE_POS)
#define USB_DWC2_GHWCFG3_OPTFEATURE_POS		10UL
#define USB_DWC2_GHWCFG3_OPTFEATURE		BIT(USB_DWC2_GHWCFG3_OPTFEATURE_POS)
#define USB_DWC2_GHWCFG3_VNDCTLSUPT_POS		9UL
#define USB_DWC2_GHWCFG3_VNDCTLSUPT		BIT(USB_DWC2_GHWCFG3_VNDCTLSUPT_POS)
#define USB_DWC2_GHWCFG3_OTGEN_POS		7UL
#define USB_DWC2_GHWCFG3_OTGEN			BIT(USB_DWC2_GHWCFG3_OTGEN_POS)
#define USB_DWC2_GHWCFG3_PKTSIZEWIDTH_POS	4UL
#define USB_DWC2_GHWCFG3_PKTSIZEWIDTH_MASK	(0x7UL << USB_DWC2_GHWCFG3_PKTSIZEWIDTH_POS)
#define USB_DWC2_GHWCFG3_PKTSIZEWIDTH_BITS10	6U
#define USB_DWC2_GHWCFG3_PKTSIZEWIDTH_BITS9	5U
#define USB_DWC2_GHWCFG3_PKTSIZEWIDTH_BITS8	4U
#define USB_DWC2_GHWCFG3_PKTSIZEWIDTH_BITS7	3U
#define USB_DWC2_GHWCFG3_PKTSIZEWIDTH_BITS6	2U
#define USB_DWC2_GHWCFG3_PKTSIZEWIDTH_BITS5	1U
#define USB_DWC2_GHWCFG3_PKTSIZEWIDTH_BITS4	0U
#define USB_DWC2_GHWCFG3_XFERSIZEWIDTH_POS	0UL
#define USB_DWC2_GHWCFG3_XFERSIZEWIDTH_MASK	(0xFUL << USB_DWC2_GHWCFG3_XFERSIZEWIDTH_POS)
#define USB_DWC2_GHWCFG3_XFERSIZEWIDTH_WIDTH19	8U
#define USB_DWC2_GHWCFG3_XFERSIZEWIDTH_WIDTH18	7U
#define USB_DWC2_GHWCFG3_XFERSIZEWIDTH_WIDTH17	6U
#define USB_DWC2_GHWCFG3_XFERSIZEWIDTH_WIDTH16	5U
#define USB_DWC2_GHWCFG3_XFERSIZEWIDTH_WIDTH15	4U
#define USB_DWC2_GHWCFG3_XFERSIZEWIDTH_WIDTH14	3U
#define USB_DWC2_GHWCFG3_XFERSIZEWIDTH_WIDTH13	2U
#define USB_DWC2_GHWCFG3_XFERSIZEWIDTH_WIDTH12	1U
#define USB_DWC2_GHWCFG3_XFERSIZEWIDTH_WIDTH11	0U

#define GHWCFG3_PKTCOUNT(pktsizewidth) BIT_MASK(pktsizewidth + 4)
#define GHWCFG3_XFERSIZE(xfersizewidth) BIT_MASK(xfersizewidth + 11)

USB_DWC2_GET_FIELD_DEFINE(ghwcfg3_dfifodepth, GHWCFG3_DFIFODEPTH)
USB_DWC2_GET_FIELD_DEFINE(ghwcfg3_pktsizewidth, GHWCFG3_PKTSIZEWIDTH)
USB_DWC2_GET_FIELD_DEFINE(ghwcfg3_xfersizewidth, GHWCFG3_XFERSIZEWIDTH)

/* GHWCFG4 register */
#define USB_DWC2_GHWCFG4			0x0050UL
#define USB_DWC2_GHWCFG4_INEPS_POS		26UL
#define USB_DWC2_GHWCFG4_INEPS_MASK		(0xFUL << USB_DWC2_GHWCFG4_INEPS_POS)
#define USB_DWC2_GHWCFG4_DEDFIFOMODE_POS	25UL
#define USB_DWC2_GHWCFG4_DEDFIFOMODE		BIT(USB_DWC2_GHWCFG4_DEDFIFOMODE_POS)
#define USB_DWC2_GHWCFG4_NUMCTLEPS_POS		16UL
#define USB_DWC2_GHWCFG4_NUMCTLEPS_MASK		(0xFUL << USB_DWC2_GHWCFG4_NUMCTLEPS_POS)
#define USB_DWC2_GHWCFG4_PHYDATAWIDTH_POS	14UL
#define USB_DWC2_GHWCFG4_PHYDATAWIDTH_MASK	(0x3UL << USB_DWC2_GHWCFG4_PHYDATAWIDTH_POS)
#define USB_DWC2_GHWCFG4_NUMDEVPERIOEPS_POS	0UL
#define USB_DWC2_GHWCFG4_NUMDEVPERIOEPS_MASK	(0xFUL << USB_DWC2_GHWCFG4_NUMDEVPERIOEPS_POS)

USB_DWC2_GET_FIELD_DEFINE(ghwcfg4_ineps, GHWCFG4_INEPS)
USB_DWC2_GET_FIELD_DEFINE(ghwcfg4_numctleps, GHWCFG4_NUMCTLEPS)
USB_DWC2_GET_FIELD_DEFINE(ghwcfg4_phydatawidth, GHWCFG4_PHYDATAWIDTH)
USB_DWC2_GET_FIELD_DEFINE(ghwcfg4_numdevperioeps, GHWCFG4_NUMDEVPERIOEPS)

/* Device IN endpoint transmit FIFO size register */
#define USB_DWC2_DIEPTXF1			0x0104UL
#define USB_DWC2_DIEPTXF_INEPNTXFDEP_POS	16UL
#define USB_DWC2_DIEPTXF_INEPNTXFDEP_MASK	(0xFFFFUL << USB_DWC2_DIEPTXF_INEPNTXFDEP_POS)
#define USB_DWC2_DIEPTXF_INEPNTXFSTADDR_POS	0UL
#define USB_DWC2_DIEPTXF_INEPNTXFSTADDR_MASK	(0xFFFFUL << USB_DWC2_DIEPTXF_INEPNTXFSTADDR_POS)

USB_DWC2_GET_FIELD_DEFINE(dieptxf_inepntxfdep, DIEPTXF_INEPNTXFDEP)
USB_DWC2_GET_FIELD_DEFINE(dieptxf_inepntxfstaddr, DIEPTXF_INEPNTXFSTADDR)
USB_DWC2_SET_FIELD_DEFINE(dieptxf_inepntxfdep, DIEPTXF_INEPNTXFDEP)
USB_DWC2_SET_FIELD_DEFINE(dieptxf_inepntxfstaddr, DIEPTXF_INEPNTXFSTADDR)

/* Device configuration registers */
#define USB_DWC2_DCFG				0x0800UL
#define USB_DWC2_DCFG_DEVADDR_POS		4UL
#define USB_DWC2_DCFG_DEVADDR_MASK		(0x7FUL << USB_DWC2_DCFG_DEVADDR_POS)
#define USB_DWC2_DCFG_DEVSPD_POS		0UL
#define USB_DWC2_DCFG_DEVSPD_MASK		(0x03UL << USB_DWC2_DCFG_DEVSPD_POS)
#define USB_DWC2_DCFG_DEVSPD_USBHS20		0
#define USB_DWC2_DCFG_DEVSPD_USBFS20		1
#define USB_DWC2_DCFG_DEVSPD_USBLS116		2
#define USB_DWC2_DCFG_DEVSPD_USBFS1148		3

USB_DWC2_SET_FIELD_DEFINE(dcfg_devaddr, DCFG_DEVADDR)
USB_DWC2_GET_FIELD_DEFINE(dcfg_devspd, DCFG_DEVSPD)

/* Device control register */
#define USB_DWC2_DCTL				0x0804UL
#define USB_DWC2_DCTL_SERVINT_POS		19UL
#define USB_DWC2_DCTL_SERVINT			BIT(USB_DWC2_DCTL_SERVINT_POS)
#define USB_DWC2_DCTL_DEEPSLEEPBESLREJECT_POS	18UL
#define USB_DWC2_DCTL_DEEPSLEEPBESLREJECT	BIT(USB_DWC2_DCTL_DEEPSLEEPBESLREJECT_POS)
#define USB_DWC2_DCTL_NAKONBBLE_POS		16UL
#define USB_DWC2_DCTL_NAKONBBLE			BIT(USB_DWC2_DCTL_NAKONBBLE_POS)
#define USB_DWC2_DCTL_IGNRFRMNUM_POS		15UL
#define USB_DWC2_DCTL_IGNRFRMNUM		BIT(USB_DWC2_DCTL_IGNRFRMNUM_POS)
#define USB_DWC2_DCTL_PWRONPRGDONE_POS		11UL
#define USB_DWC2_DCTL_PWRONPRGDONE		BIT(USB_DWC2_DCTL_PWRONPRGDONE_POS)
#define USB_DWC2_DCTL_CGOUTNAK_POS		10UL
#define USB_DWC2_DCTL_CGOUTNAK			BIT(USB_DWC2_DCTL_CGOUTNAK_POS)
#define USB_DWC2_DCTL_SGOUTNAK_POS		9UL
#define USB_DWC2_DCTL_SGOUTNAK			BIT(USB_DWC2_DCTL_SGOUTNAK_POS)
#define USB_DWC2_DCTL_CGNPINNAK_POS		8UL
#define USB_DWC2_DCTL_CGNPINNAK			BIT(USB_DWC2_DCTL_CGNPINNAK_POS)
#define USB_DWC2_DCTL_SGNPINNAK_POS		7UL
#define USB_DWC2_DCTL_SGNPINNAK			BIT(USB_DWC2_DCTL_SGNPINNAK_POS)
#define USB_DWC2_DCTL_TSTCTL_POS		4UL
#define USB_DWC2_DCTL_TSTCTL_MASK		(0x7UL << USB_DWC2_DCTL_TSTCTL_POS)
#define USB_DWC2_DCTL_TSTCTL_TESTFE		5UL
#define USB_DWC2_DCTL_TSTCTL_TESTPM		4UL
#define USB_DWC2_DCTL_TSTCTL_TESTSN		3UL
#define USB_DWC2_DCTL_TSTCTL_TESTK		2UL
#define USB_DWC2_DCTL_TSTCTL_TESTJ		1UL
#define USB_DWC2_DCTL_TSTCTL_DISABLED		0UL
#define USB_DWC2_DCTL_GOUTNAKSTS_POS		3UL
#define USB_DWC2_DCTL_GOUTNAKSTS		BIT(USB_DWC2_DCTL_GOUTNAKSTS_POS)
#define USB_DWC2_DCTL_GNPINNAKSTS_POS		2UL
#define USB_DWC2_DCTL_GNPINNAKSTS		BIT(USB_DWC2_DCTL_GNPINNAKSTS_POS)
#define USB_DWC2_DCTL_SFTDISCON_POS		1UL
#define USB_DWC2_DCTL_SFTDISCON			BIT(USB_DWC2_DCTL_SFTDISCON_POS)
#define USB_DWC2_DCTL_RMTWKUPSIG_POS		0UL
#define USB_DWC2_DCTL_RMTWKUPSIG		BIT(USB_DWC2_DCTL_RMTWKUPSIG_POS)

USB_DWC2_GET_FIELD_DEFINE(dctl_tstctl, DCTL_TSTCTL)
USB_DWC2_SET_FIELD_DEFINE(dctl_tstctl, DCTL_TSTCTL)

/* Device status register */
#define USB_DWC2_DSTS				0x0808UL
#define USB_DWC2_DSTS_ENUMSPD_POS		1UL
#define USB_DWC2_DSTS_ENUMSPD_MASK		(0x3UL << USB_DWC2_DSTS_ENUMSPD_POS)
#define USB_DWC2_DSTS_ENUMSPD_HS3060		0
#define USB_DWC2_DSTS_ENUMSPD_FS3060		1
#define USB_DWC2_DSTS_ENUMSPD_LS6		2
#define USB_DWC2_DSTS_ENUMSPD_FS48		3

USB_DWC2_GET_FIELD_DEFINE(dsts_enumspd, DSTS_ENUMSPD)

/* Device all endpoints interrupt registers */
#define USB_DWC2_DAINT				0x0818UL
#define USB_DWC2_DAINTMSK			0x081CUL
#define USB_DWC2_DAINT_OUTEPINT(ep_num)		BIT(16UL + ep_num)
#define USB_DWC2_DAINT_INEPINT(ep_num)		BIT(ep_num)

/*
 * Device IN/OUT endpoint control register
 * IN endpoint offsets 0x0900 + (0x20 * n), n = 0 .. x,
 * OUT endpoint offsets 0x0B00 + (0x20 * n), n = 0 .. x,
 *
 */
#define USB_DWC2_DIEPCTL0			0x0900UL
#define USB_DWC2_DOEPCTL0			0x0B00UL
#define USB_DWC2_DEPCTL_EPENA_POS		31UL
#define USB_DWC2_DEPCTL_EPENA			BIT(USB_DWC2_DEPCTL_EPENA_POS)
#define USB_DWC2_DEPCTL_EPDIS_POS		30UL
#define USB_DWC2_DEPCTL_EPDIS			BIT(USB_DWC2_DEPCTL_EPDIS_POS)
#define USB_DWC2_DEPCTL_SETD0PID_POS		28UL
#define USB_DWC2_DEPCTL_SETD0PID		BIT(USB_DWC2_DEPCTL_SETD0PID_POS)
#define USB_DWC2_DEPCTL_SNAK_POS		27UL
#define USB_DWC2_DEPCTL_SNAK			BIT(USB_DWC2_DEPCTL_SNAK_POS)
#define USB_DWC2_DEPCTL_CNAK_POS		26UL
#define USB_DWC2_DEPCTL_CNAK			BIT(USB_DWC2_DEPCTL_CNAK_POS)
#define USB_DWC2_DEPCTL_TXFNUM_POS		22UL
#define USB_DWC2_DEPCTL_TXFNUM_MASK		(0xFUL << USB_DWC2_DEPCTL_TXFNUM_POS)
#define USB_DWC2_DEPCTL_STALL_POS		21UL
#define USB_DWC2_DEPCTL_STALL			BIT(USB_DWC2_DEPCTL_STALL_POS)
#define USB_DWC2_DEPCTL_EPTYPE_POS		18UL
#define USB_DWC2_DEPCTL_EPTYPE_MASK		(0x3UL << USB_DWC2_DEPCTL_EPTYPE_POS)
#define USB_DWC2_DEPCTL_EPTYPE_INTERRUPT	3
#define USB_DWC2_DEPCTL_EPTYPE_BULK		2
#define USB_DWC2_DEPCTL_EPTYPE_ISO		1
#define USB_DWC2_DEPCTL_EPTYPE_CONTROL		0
#define USB_DWC2_DEPCTL_USBACTEP_POS		15UL
#define USB_DWC2_DEPCTL_USBACTEP		BIT(USB_DWC2_DEPCTL_USBACTEP_POS)
#define USB_DWC2_DEPCTL0_MPS_POS		0UL
#define USB_DWC2_DEPCTL0_MPS_MASK		(0x3UL << USB_DWC2_DEPCTL0_MPS_POS)
#define USB_DWC2_DEPCTL0_MPS_8			3
#define USB_DWC2_DEPCTL0_MPS_16			2
#define USB_DWC2_DEPCTL0_MPS_32			1
#define USB_DWC2_DEPCTL0_MPS_64			0
#define USB_DWC2_DEPCTL_MPS_POS			0UL
#define USB_DWC2_DEPCTL_MPS_MASK		(0x7FF << USB_DWC2_DEPCTL_MPS_POS)

USB_DWC2_GET_FIELD_DEFINE(depctl_txfnum, DEPCTL_TXFNUM)
USB_DWC2_SET_FIELD_DEFINE(depctl_txfnum, DEPCTL_TXFNUM)
USB_DWC2_GET_FIELD_DEFINE(depctl_eptype, DEPCTL_EPTYPE)
USB_DWC2_SET_FIELD_DEFINE(depctl_eptype, DEPCTL_EPTYPE)
USB_DWC2_GET_FIELD_DEFINE(depctl0_mps, DEPCTL0_MPS)
USB_DWC2_SET_FIELD_DEFINE(depctl0_mps, DEPCTL0_MPS)
USB_DWC2_GET_FIELD_DEFINE(depctl_mps, DEPCTL_MPS)
USB_DWC2_SET_FIELD_DEFINE(depctl_mps, DEPCTL_MPS)

/*
 * Device IN endpoint interrupt register
 * offsets 0x0908 + (0x20 * n), n = 0 .. x
 */
#define USB_DWC2_DIEPINT0			0x0908UL
#define USB_DWC2_DIEPINT_NYETINTRPT_POS		14UL
#define USB_DWC2_DIEPINT_NYETINTRPT		BIT(USB_DWC2_DIEPINT_NYETINTRPT_POS)
#define USB_DWC2_DIEPINT_NAKINTRPT_POS		13UL
#define USB_DWC2_DIEPINT_NAKINTRPT		BIT(USB_DWC2_DIEPINT_NAKINTRPT_POS)
#define USB_DWC2_DIEPINT_BBLEERR_POS		12UL
#define USB_DWC2_DIEPINT_BBLEERR		BIT(USB_DWC2_DIEPINT_BBLEERR_POS)
#define USB_DWC2_DIEPINT_PKTDRPSTS_POS		11UL
#define USB_DWC2_DIEPINT_PKTDRPSTS		BIT(USB_DWC2_DIEPINT_PKTDRPSTS_POS)
#define USB_DWC2_DIEPINT_BNAINTR_POS		9UL
#define USB_DWC2_DIEPINT_BNAINTR		BIT(USB_DWC2_DIEPINT_BNAINTR_POS)
#define USB_DWC2_DIEPINT_TXFIFOUNDRN_POS	8UL
#define USB_DWC2_DIEPINT_TXFIFOUNDRN		BIT(USB_DWC2_DIEPINT_TXFIFOUNDRN_POS)
#define USB_DWC2_DIEPINT_TXFEMP_POS		7UL
#define USB_DWC2_DIEPINT_TXFEMP			BIT(USB_DWC2_DIEPINT_TXFEMP_POS)
#define USB_DWC2_DIEPINT_INEPNAKEFF_POS		6UL
#define USB_DWC2_DIEPINT_INEPNAKEFF		BIT(USB_DWC2_DIEPINT_INEPNAKEFF_POS)
#define USB_DWC2_DIEPINT_INTKNEPMIS_POS		5UL
#define USB_DWC2_DIEPINT_INTKNEPMIS		BIT(USB_DWC2_DIEPINT_INTKNEPMIS_POS)
#define USB_DWC2_DIEPINT_INTKNTXFEMP_POS	4UL
#define USB_DWC2_DIEPINT_INTKNTXFEMP		BIT(USB_DWC2_DIEPINT_INTKNTXFEMP_POS)
#define USB_DWC2_DIEPINT_TIMEOUT_POS		3UL
#define USB_DWC2_DIEPINT_TIMEOUT		BIT(USB_DWC2_DIEPINT_TIMEOUT_POS)
#define USB_DWC2_DIEPINT_AHBERR_POS		2UL
#define USB_DWC2_DIEPINT_AHBERR			BIT(USB_DWC2_DIEPINT_AHBERR_POS)
#define USB_DWC2_DIEPINT_EPDISBLD_POS		1UL
#define USB_DWC2_DIEPINT_EPDISBLD		BIT(USB_DWC2_DIEPINT_EPDISBLD_POS)
#define USB_DWC2_DIEPINT_XFERCOMPL_POS		0UL
#define USB_DWC2_DIEPINT_XFERCOMPL		BIT(USB_DWC2_DIEPINT_XFERCOMPL_POS)

/*
 * Device OUT endpoint interrupt register
 * offsets 0x0B08 + (0x20 * n), n = 0 .. x
 */
#define USB_DWC2_DOEPINT0			0x0B08UL
#define USB_DWC2_DOEPINT_STUPPKTRCVD_POS	15UL
#define USB_DWC2_DOEPINT_STUPPKTRCVD		BIT(USB_DWC2_DOEPINT_STUPPKTRCVD_POS)
#define USB_DWC2_DOEPINT_NYETINTRPT_POS		14UL
#define USB_DWC2_DOEPINT_NYETINTRPT		BIT(USB_DWC2_DOEPINT_NYETINTRPT_POS)
#define USB_DWC2_DOEPINT_NAKINTRPT_POS		13UL
#define USB_DWC2_DOEPINT_NAKINTRPT		BIT(USB_DWC2_DOEPINT_NAKINTRPT_POS)
#define USB_DWC2_DOEPINT_BBLEERR_POS		12UL
#define USB_DWC2_DOEPINT_BBLEERR		BIT(USB_DWC2_DOEPINT_BBLEERR_POS)
#define USB_DWC2_DOEPINT_PKTDRPSTS_POS		11UL
#define USB_DWC2_DOEPINT_PKTDRPSTS		BIT(USB_DWC2_DOEPINT_PKTDRPSTS_POS)
#define USB_DWC2_DOEPINT_BNAINTR_POS		9UL
#define USB_DWC2_DOEPINT_BNAINTR		BIT(USB_DWC2_DOEPINT_BNAINTR_POS)
#define USB_DWC2_DOEPINT_OUTPKTERR_POS		8UL
#define USB_DWC2_DOEPINT_OUTPKTERR		BIT(USB_DWC2_DOEPINT_OUTPKTERR_POS)
#define USB_DWC2_DOEPINT_BACK2BACKSETUP_POS	6UL
#define USB_DWC2_DOEPINT_BACK2BACKSETUP		BIT(USB_DWC2_DOEPINT_BACK2BACKSETUP_POS)
#define USB_DWC2_DOEPINT_STSPHSERCVD_POS	5UL
#define USB_DWC2_DOEPINT_STSPHSERCVD		BIT(USB_DWC2_DOEPINT_STSPHSERCVD_POS)
#define USB_DWC2_DOEPINT_OUTTKNEPDIS_POS	4UL
#define USB_DWC2_DOEPINT_OUTTKNEPDIS		BIT(USB_DWC2_DOEPINT_OUTTKNEPDIS_POS)
#define USB_DWC2_DOEPINT_SETUP_POS		3UL
#define USB_DWC2_DOEPINT_SETUP			BIT(USB_DWC2_DOEPINT_SETUP_POS)
#define USB_DWC2_DOEPINT_AHBERR_POS		2UL
#define USB_DWC2_DOEPINT_AHBERR			BIT(USB_DWC2_DOEPINT_AHBERR_POS)
#define USB_DWC2_DOEPINT_EPDISBLD_POS		1UL
#define USB_DWC2_DOEPINT_EPDISBLD		BIT(USB_DWC2_DOEPINT_EPDISBLD_POS)
#define USB_DWC2_DOEPINT_XFERCOMPL_POS		0UL
#define USB_DWC2_DOEPINT_XFERCOMPL		BIT(USB_DWC2_DOEPINT_XFERCOMPL_POS)

/*
 * Device IN/OUT control endpoint transfer size register
 */
#define USB_DWC2_DIEPTSIZ0			0x0910UL
#define USB_DWC2_DOEPTSIZ0			0x0B10UL
#define USB_DWC2_DOEPTSIZ0_SUPCNT_POS		29UL
#define USB_DWC2_DOEPTSIZ0_SUPCNT_MASK		(0x3UL << USB_DWC2_DOEPTSIZ0_SUPCNT_POS)
#define USB_DWC2_DOEPTSIZ0_PKTCNT_POS		19UL
#define USB_DWC2_DOEPTSIZ0_PKTCNT_MASK		(0x1UL << USB_DWC2_DOEPTSIZ0_PKTCNT_POS)
#define USB_DWC2_DIEPTSIZ0_PKTCNT_POS		19UL
#define USB_DWC2_DIEPTSIZ0_PKTCNT_MASK		(0x3UL << USB_DWC2_DIEPTSIZ0_PKTCNT_POS)
#define USB_DWC2_DEPTSIZ0_XFERSIZE_POS		0UL
#define USB_DWC2_DEPTSIZ0_XFERSIZE_MASK		0x7FUL

USB_DWC2_GET_FIELD_DEFINE(doeptsiz0_supcnt, DOEPTSIZ0_SUPCNT)
USB_DWC2_GET_FIELD_DEFINE(doeptsiz0_pktcnt, DOEPTSIZ0_PKTCNT)
USB_DWC2_GET_FIELD_DEFINE(doeptsiz0_xfersize, DEPTSIZ0_XFERSIZE)
USB_DWC2_GET_FIELD_DEFINE(dieptsiz0_pktcnt, DIEPTSIZ0_PKTCNT)
USB_DWC2_GET_FIELD_DEFINE(dieptsiz0_xfersize, DEPTSIZ0_XFERSIZE)

/*
 * Device IN/OUT endpoint transfer size register
 * IN at offsets 0x0910 + (0x20 * n), n = 1 .. x,
 * OUT at offsets 0x0B10 + (0x20 * n), n = 1 .. x
 */
#define USB_DWC2_DEPTSIZN_PKTCNT_POS		19UL
#define USB_DWC2_DEPTSIZN_PKTCNT_MASK		(0x3FFUL << USB_DWC2_DEPTSIZN_PKTCNT_POS)
#define USB_DWC2_DEPTSIZN_XFERSIZE_POS		0UL
#define USB_DWC2_DEPTSIZN_XFERSIZE_MASK		0x7FFFFUL

USB_DWC2_GET_FIELD_DEFINE(deptsizn_pktcnt, DEPTSIZN_PKTCNT)
USB_DWC2_GET_FIELD_DEFINE(deptsizn_xfersize, DEPTSIZN_XFERSIZE)

/*
 * Device IN/OUT endpoint transfer size register
 * IN at offsets 0x0910 + (0x20 * n), n = 0 .. x,
 * OUT at offsets 0x0B10 + (0x20 * n), n = 0 .. x
 *
 * Note: Legacy definitions for the usb_dc_dw.c driver only.
 */
#define USB_DWC2_DEPTSIZ_PKT_CNT_POS		19UL
#define USB_DWC2_DIEPTSIZ0_PKT_CNT_MASK		(0x3 << 19)
#define USB_DWC2_DIEPTSIZn_PKT_CNT_MASK		(0x3FF << 19)
#define USB_DWC2_DOEPTSIZn_PKT_CNT_MASK		(0x3FF << 19)
#define USB_DWC2_DOEPTSIZ0_PKT_CNT_MASK		(0x1 << 19)
#define USB_DWC2_DOEPTSIZ_SUP_CNT_POS		29UL
#define USB_DWC2_DOEPTSIZ_SUP_CNT_MASK		(0x3 << 29)
#define USB_DWC2_DEPTSIZ_XFER_SIZE_POS		0UL
#define USB_DWC2_DEPTSIZ0_XFER_SIZE_MASK	0x7F
#define USB_DWC2_DEPTSIZn_XFER_SIZE_MASK	0x7FFFF

/*
 * Device IN endpoint transmit FIFO status register,
 * offsets 0x0918 + (0x20 * n), n = 0 .. x
 */
#define USB_DWC2_DTXFSTS0			0x0918UL
#define USB_DWC2_DTXFSTS_INEPTXFSPCAVAIL_POS	0UL
#define USB_DWC2_DTXFSTS_INEPTXFSPCAVAIL_MASK	0xFFFFUL

USB_DWC2_GET_FIELD_DEFINE(dtxfsts_ineptxfspcavail, DTXFSTS_INEPTXFSPCAVAIL)

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_DRIVERS_USB_COMMON_USB_DWC2_HW */
