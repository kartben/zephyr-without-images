/*
 * Copyright (c) 2019, NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <init.h>
#include <fsl_iomuxc.h>
#include <fsl_gpio.h>

static int mimxrt1015_evk_init(const struct device *dev)
{
	ARG_UNUSED(dev);

	CLOCK_EnableClock(kCLOCK_Iomuxc);
	CLOCK_EnableClock(kCLOCK_IomuxcSnvs);

#if DT_NODE_HAS_STATUS(DT_NODELABEL(gpio2), okay)
	IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_09_GPIO2_IO09, 0);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_09_GPIO2_IO09,
				IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
				IOMUXC_SW_PAD_CTL_PAD_PUE(1) |
				IOMUXC_SW_PAD_CTL_PAD_PUS(2) |
				IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
				IOMUXC_SW_PAD_CTL_PAD_DSE(4));
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(lpuart1), okay)
	/* LPUART1 TX/RX */
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_06_LPUART1_TX, 0);
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_07_LPUART1_RX, 0);

	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_06_LPUART1_TX,
				IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
				IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
				IOMUXC_SW_PAD_CTL_PAD_DSE(6));

	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_07_LPUART1_RX,
				IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
				IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
				IOMUXC_SW_PAD_CTL_PAD_DSE(6));
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(lpuart4), okay)
	/* LPUART4 TX/RX */
	IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_32_LPUART4_TX, 0);
	IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_33_LPUART4_RX, 0);

	IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_32_LPUART4_TX,
				IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
				IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
				IOMUXC_SW_PAD_CTL_PAD_DSE(6));

	IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_33_LPUART4_RX,
				IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
				IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
				IOMUXC_SW_PAD_CTL_PAD_DSE(6));
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(lpi2c1), okay)
	/* LPI2C1 SCL, SDA */
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_14_LPI2C1_SCL, 1);
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_15_LPI2C1_SDA, 1);

	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_14_LPI2C1_SCL,
				IOMUXC_SW_PAD_CTL_PAD_PUS(3) |
				IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
				IOMUXC_SW_PAD_CTL_PAD_ODE_MASK |
				IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
				IOMUXC_SW_PAD_CTL_PAD_DSE(6));

	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_15_LPI2C1_SDA,
				IOMUXC_SW_PAD_CTL_PAD_PUS(3) |
				IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
				IOMUXC_SW_PAD_CTL_PAD_ODE_MASK |
				IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
				IOMUXC_SW_PAD_CTL_PAD_DSE(6));
#endif

	return 0;
}

SYS_INIT(mimxrt1015_evk_init, PRE_KERNEL_1, 0);
