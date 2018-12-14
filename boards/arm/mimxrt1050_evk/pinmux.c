/*
 * Copyright (c) 2017, NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <init.h>
#include <fsl_iomuxc.h>
#include <fsl_gpio.h>

#ifdef CONFIG_ETH_MCUX_0
static gpio_pin_config_t enet_gpio_config = {
	.direction = kGPIO_DigitalOutput,
	.outputLogic = 0,
	.interruptMode = kGPIO_NoIntmode
};
#endif

static int mimxrt1050_evk_init(struct device *dev)
{
	ARG_UNUSED(dev);

	CLOCK_EnableClock(kCLOCK_Iomuxc);
	CLOCK_EnableClock(kCLOCK_IomuxcSnvs);

#ifndef CONFIG_ETH_MCUX_0
	/* LED */
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_09_GPIO1_IO09, 0);

	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_09_GPIO1_IO09,
			    IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
			    IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
			    IOMUXC_SW_PAD_CTL_PAD_DSE(6));

	/* SW0 */
	IOMUXC_SetPinMux(IOMUXC_SNVS_WAKEUP_GPIO5_IO00, 0);
#endif

#ifdef CONFIG_UART_MCUX_LPUART_1
	/* LPUART1 TX/RX */
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_12_LPUART1_TX, 0);
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_13_LPUART1_RX, 0);

	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_12_LPUART1_TX,
			    IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
			    IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
			    IOMUXC_SW_PAD_CTL_PAD_DSE(6));

	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_13_LPUART1_RX,
			    IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
			    IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
			    IOMUXC_SW_PAD_CTL_PAD_DSE(6));
#endif

#ifdef CONFIG_UART_MCUX_LPUART_3
	/* LPUART3 TX/RX */
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_06_LPUART3_TX, 0);
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_07_LPUART3_RX, 0);

	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_06_LPUART3_TX,
			    IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
			    IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
			    IOMUXC_SW_PAD_CTL_PAD_DSE(6));

	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_07_LPUART3_RX,
			    IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
			    IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
			    IOMUXC_SW_PAD_CTL_PAD_DSE(6));
#endif

#ifdef CONFIG_SPI_3
	/* LPSPI3 SCK, SDO, SDI, PCS0 */
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_00_LPSPI3_SCK, 0);
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_01_LPSPI3_SDO, 0);
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_02_LPSPI3_SDI, 0);
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_03_LPSPI3_PCS0, 0);

	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_00_LPSPI3_SCK,
			    IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
			    IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
			    IOMUXC_SW_PAD_CTL_PAD_DSE(6));

	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_01_LPSPI3_SDO,
			    IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
			    IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
			    IOMUXC_SW_PAD_CTL_PAD_DSE(6));

	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_02_LPSPI3_SDI,
			    IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
			    IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
			    IOMUXC_SW_PAD_CTL_PAD_DSE(6));

	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_03_LPSPI3_PCS0,
			    IOMUXC_SW_PAD_CTL_PAD_PKE_MASK |
			    IOMUXC_SW_PAD_CTL_PAD_SPEED(2) |
			    IOMUXC_SW_PAD_CTL_PAD_DSE(6));
#endif

#ifdef CONFIG_ETH_MCUX_0
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_09_GPIO1_IO09, 0U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_10_GPIO1_IO10, 0U);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B1_04_ENET_RX_DATA00, 0);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B1_05_ENET_RX_DATA01, 0);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B1_06_ENET_RX_EN, 0);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B1_07_ENET_TX_DATA00, 0);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B1_08_ENET_TX_DATA01, 0);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B1_09_ENET_TX_EN, 0);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B1_10_ENET_REF_CLK, 1);
	IOMUXC_SetPinMux(IOMUXC_GPIO_B1_11_ENET_RX_ER, 0);
	IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_40_ENET_MDC, 0);
	IOMUXC_SetPinMux(IOMUXC_GPIO_EMC_41_ENET_MDIO, 0);

	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_09_GPIO1_IO09, 0xB0A9u);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_10_GPIO1_IO10, 0xB0A9u);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_04_ENET_RX_DATA00, 0xB0E9);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_05_ENET_RX_DATA01, 0xB0E9);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_06_ENET_RX_EN, 0xB0E9);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_07_ENET_TX_DATA00, 0xB0E9);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_08_ENET_TX_DATA01, 0xB0E9);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_09_ENET_TX_EN, 0xB0E9);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_10_ENET_REF_CLK, 0x31);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_11_ENET_RX_ER, 0xB0E9);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_40_ENET_MDC, 0xB0E9);
	IOMUXC_SetPinConfig(IOMUXC_GPIO_EMC_41_ENET_MDIO, 0xB829);

	IOMUXC_EnableMode(IOMUXC_GPR, kIOMUXC_GPR_ENET1TxClkOutputDir, true);

	/* Intialize ENET_INT GPIO */
	GPIO_PinInit(GPIO1, 9, &enet_gpio_config);
	GPIO_PinInit(GPIO1, 10, &enet_gpio_config);

	/* pull up the ENET_INT before RESET. */
	GPIO_WritePinOutput(GPIO1, 10, 1);
	/* RESET PHY chip. */
	GPIO_WritePinOutput(GPIO1, 9, 1);
#endif

	return 0;
}

SYS_INIT(mimxrt1050_evk_init, PRE_KERNEL_1, 0);
