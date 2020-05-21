/*
 * Copyright (c) 2019, Joris Offouga
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#include <init.h>
#include "device_imx.h"

static int pico_pi_m4_pinmux_init(struct device *dev)
{
	ARG_UNUSED(dev);

 #if DT_NODE_HAS_STATUS(DT_NODELABEL(uart2), okay) && CONFIG_SERIAL
	IOMUXC_SW_MUX_CTL_PAD_UART2_RX_DATA =
		IOMUXC_SW_MUX_CTL_PAD_UART2_RX_DATA_MUX_MODE(0);
	IOMUXC_SW_MUX_CTL_PAD_UART2_TX_DATA =
		IOMUXC_SW_MUX_CTL_PAD_UART2_TX_DATA_MUX_MODE(0);
	IOMUXC_SW_PAD_CTL_PAD_UART2_RX_DATA =
		IOMUXC_SW_PAD_CTL_PAD_UART2_RX_DATA_PE_MASK  |
		IOMUXC_SW_PAD_CTL_PAD_UART2_RX_DATA_PS(3)    |
		IOMUXC_SW_PAD_CTL_PAD_UART2_RX_DATA_HYS_MASK |
		IOMUXC_SW_PAD_CTL_PAD_UART2_RX_DATA_DSE(0);

	IOMUXC_SW_PAD_CTL_PAD_UART2_TX_DATA =
		IOMUXC_SW_PAD_CTL_PAD_UART2_TX_DATA_PE_MASK  |
		IOMUXC_SW_PAD_CTL_PAD_UART2_TX_DATA_PS(3)    |
		IOMUXC_SW_PAD_CTL_PAD_UART2_TX_DATA_HYS_MASK |
		IOMUXC_SW_PAD_CTL_PAD_UART2_TX_DATA_DSE(0);

	IOMUXC_UART2_RX_DATA_SELECT_INPUT =
		IOMUXC_UART2_RX_DATA_SELECT_INPUT_DAISY(2);
 #endif


 #if DT_NODE_HAS_STATUS(DT_NODELABEL(uart5), okay) && CONFIG_SERIAL
	IOMUXC_SW_MUX_CTL_PAD_I2C4_SCL =
		IOMUXC_SW_MUX_CTL_PAD_I2C4_SCL_MUX_MODE(1);
	IOMUXC_SW_MUX_CTL_PAD_I2C4_SDA =
		IOMUXC_SW_MUX_CTL_PAD_I2C4_SDA_MUX_MODE(1);

	IOMUXC_SW_PAD_CTL_PAD_I2C4_SCL =
		IOMUXC_SW_PAD_CTL_PAD_I2C4_SCL_PE_MASK  |
		IOMUXC_SW_PAD_CTL_PAD_I2C4_SCL_PS(3)    |
		IOMUXC_SW_PAD_CTL_PAD_I2C4_SCL_HYS_MASK |
		IOMUXC_SW_PAD_CTL_PAD_I2C4_SCL_DSE(0);

	IOMUXC_SW_PAD_CTL_PAD_I2C4_SDA =
		IOMUXC_SW_PAD_CTL_PAD_I2C4_SDA_PE_MASK  |
		IOMUXC_SW_PAD_CTL_PAD_I2C4_SDA_PS(3)    |
		IOMUXC_SW_PAD_CTL_PAD_I2C4_SDA_HYS_MASK |
		IOMUXC_SW_PAD_CTL_PAD_I2C4_SDA_DSE(0);

	IOMUXC_UART5_RX_DATA_SELECT_INPUT =
		IOMUXC_UART5_RX_DATA_SELECT_INPUT_DAISY(0);

 #endif


 #if DT_NODE_HAS_STATUS(DT_NODELABEL(uart6), okay) && CONFIG_SERIAL
	IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA08 =
		IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA08_MUX_MODE(3);
	IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA09 =
		IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA09_MUX_MODE(3);

	IOMUXC_SW_PAD_CTL_PAD_EPDC_DATA08 =
		IOMUXC_SW_PAD_CTL_PAD_EPDC_DATA08_PE_MASK  |
		IOMUXC_SW_PAD_CTL_PAD_EPDC_DATA08_PS(3)    |
		IOMUXC_SW_PAD_CTL_PAD_EPDC_DATA08_HYS_MASK |
		IOMUXC_SW_PAD_CTL_PAD_EPDC_DATA08_DSE(1);

	IOMUXC_SW_PAD_CTL_PAD_EPDC_DATA09 =
		IOMUXC_SW_PAD_CTL_PAD_EPDC_DATA09_PE_MASK  |
		IOMUXC_SW_PAD_CTL_PAD_EPDC_DATA09_PS(3)    |
		IOMUXC_SW_PAD_CTL_PAD_EPDC_DATA09_HYS_MASK |
		IOMUXC_SW_PAD_CTL_PAD_EPDC_DATA09_DSE(1);

	IOMUXC_UART6_RX_DATA_SELECT_INPUT =
		IOMUXC_UART6_RX_DATA_SELECT_INPUT_DAISY(0);
 #endif


 #if DT_NODE_HAS_STATUS(DT_NODELABEL(i2c1), okay)
	IOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA =
		IOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA_MUX_MODE(1) |
		IOMUXC_SW_MUX_CTL_PAD_UART1_RX_DATA_SION_MASK;
	IOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA =
		IOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA_MUX_MODE(1) |
		IOMUXC_SW_MUX_CTL_PAD_UART1_TX_DATA_SION_MASK;

	IOMUXC_I2C1_SCL_SELECT_INPUT = IOMUXC_I2C1_SCL_SELECT_INPUT_DAISY(0);
	IOMUXC_I2C1_SDA_SELECT_INPUT = IOMUXC_I2C1_SDA_SELECT_INPUT_DAISY(0);

	IOMUXC_SW_PAD_CTL_PAD_UART1_RX_DATA =
		IOMUXC_SW_PAD_CTL_PAD_UART1_RX_DATA_PE_MASK  |
		IOMUXC_SW_PAD_CTL_PAD_UART1_RX_DATA_PS(3)    |
		IOMUXC_SW_PAD_CTL_PAD_UART1_RX_DATA_DSE(0)   |
		IOMUXC_SW_PAD_CTL_PAD_UART1_RX_DATA_HYS_MASK;

	IOMUXC_SW_PAD_CTL_PAD_UART1_TX_DATA =
		IOMUXC_SW_PAD_CTL_PAD_UART1_TX_DATA_PE_MASK  |
		IOMUXC_SW_PAD_CTL_PAD_UART1_TX_DATA_PS(3)    |
		IOMUXC_SW_PAD_CTL_PAD_UART1_TX_DATA_DSE(0)   |
		IOMUXC_SW_PAD_CTL_PAD_UART1_TX_DATA_HYS_MASK;
 #endif


 #if DT_NODE_HAS_STATUS(DT_NODELABEL(i2c2), okay)
	IOMUXC_SW_MUX_CTL_PAD_I2C2_SCL =
		IOMUXC_SW_MUX_CTL_PAD_I2C2_SCL_MUX_MODE(0) |
		IOMUXC_SW_MUX_CTL_PAD_I2C2_SCL_SION_MASK;
	IOMUXC_SW_MUX_CTL_PAD_I2C2_SDA =
		IOMUXC_SW_MUX_CTL_PAD_I2C2_SDA_MUX_MODE(0) |
		IOMUXC_SW_MUX_CTL_PAD_I2C2_SDA_SION_MASK;

	IOMUXC_I2C2_SCL_SELECT_INPUT = IOMUXC_I2C2_SCL_SELECT_INPUT_DAISY(1);
	IOMUXC_I2C2_SDA_SELECT_INPUT = IOMUXC_I2C2_SDA_SELECT_INPUT_DAISY(1);

	IOMUXC_SW_PAD_CTL_PAD_I2C2_SCL =
		IOMUXC_SW_PAD_CTL_PAD_I2C2_SCL_PE_MASK  |
		IOMUXC_SW_PAD_CTL_PAD_I2C2_SCL_PS(3)    |
		IOMUXC_SW_PAD_CTL_PAD_I2C2_SCL_DSE(0)   |
		IOMUXC_SW_PAD_CTL_PAD_I2C2_SCL_HYS_MASK;

	IOMUXC_SW_PAD_CTL_PAD_I2C2_SDA =
		IOMUXC_SW_PAD_CTL_PAD_I2C2_SDA_PE_MASK  |
		IOMUXC_SW_PAD_CTL_PAD_I2C2_SDA_PS(3)    |
		IOMUXC_SW_PAD_CTL_PAD_I2C2_SDA_DSE(0)   |
		IOMUXC_SW_PAD_CTL_PAD_I2C2_SDA_HYS_MASK;
 #endif


 #if DT_NODE_HAS_STATUS(DT_NODELABEL(i2c3), okay)
	IOMUXC_SW_MUX_CTL_PAD_I2C3_SCL =
		IOMUXC_SW_MUX_CTL_PAD_I2C3_SCL_MUX_MODE(0) |
		IOMUXC_SW_MUX_CTL_PAD_I2C3_SCL_SION_MASK;
	IOMUXC_SW_MUX_CTL_PAD_I2C3_SDA =
		IOMUXC_SW_MUX_CTL_PAD_I2C3_SDA_MUX_MODE(0) |
		IOMUXC_SW_MUX_CTL_PAD_I2C3_SDA_SION_MASK;

	IOMUXC_I2C3_SCL_SELECT_INPUT = IOMUXC_I2C3_SCL_SELECT_INPUT_DAISY(2);
	IOMUXC_I2C3_SDA_SELECT_INPUT = IOMUXC_I2C3_SDA_SELECT_INPUT_DAISY(2);

	IOMUXC_SW_PAD_CTL_PAD_I2C3_SCL =
		IOMUXC_SW_PAD_CTL_PAD_I2C3_SCL_PE_MASK  |
		IOMUXC_SW_PAD_CTL_PAD_I2C3_SCL_PS(3)    |
		IOMUXC_SW_PAD_CTL_PAD_I2C3_SCL_DSE(0)   |
		IOMUXC_SW_PAD_CTL_PAD_I2C3_SCL_HYS_MASK;

	IOMUXC_SW_PAD_CTL_PAD_I2C3_SDA =
		IOMUXC_SW_PAD_CTL_PAD_I2C3_SDA_PE_MASK  |
		IOMUXC_SW_PAD_CTL_PAD_I2C3_SDA_PS(3)    |
		IOMUXC_SW_PAD_CTL_PAD_I2C3_SDA_DSE(0)   |
		IOMUXC_SW_PAD_CTL_PAD_I2C3_SDA_HYS_MASK;
 #endif


 #if DT_NODE_HAS_STATUS(DT_NODELABEL(i2c4), okay)
	IOMUXC_SW_MUX_CTL_PAD_SAI1_RX_SYNC =
		IOMUXC_SW_MUX_CTL_PAD_SAI1_RX_SYNC_MUX_MODE(3) |
		IOMUXC_SW_MUX_CTL_PAD_SAI1_RX_SYNC_SION_MASK;
	IOMUXC_SW_MUX_CTL_PAD_SAI1_RX_BCLK =
		IOMUXC_SW_MUX_CTL_PAD_SAI1_RX_BCLK_MUX_MODE(3) |
		IOMUXC_SW_MUX_CTL_PAD_SAI1_RX_BCLK_SION_MASK;

	IOMUXC_I2C4_SCL_SELECT_INPUT = IOMUXC_I2C4_SCL_SELECT_INPUT_DAISY(3);
	IOMUXC_I2C4_SDA_SELECT_INPUT = IOMUXC_I2C4_SDA_SELECT_INPUT_DAISY(3);

	IOMUXC_SW_PAD_CTL_PAD_SAI1_RX_SYNC =
		IOMUXC_SW_PAD_CTL_PAD_SAI1_RX_SYNC_PE_MASK  |
		IOMUXC_SW_PAD_CTL_PAD_SAI1_RX_SYNC_PS(3)    |
		IOMUXC_SW_PAD_CTL_PAD_SAI1_RX_SYNC_DSE(0)   |
		IOMUXC_SW_PAD_CTL_PAD_SAI1_RX_SYNC_HYS_MASK;

	IOMUXC_SW_MUX_CTL_PAD_SAI1_RX_BCLK =
		IOMUXC_SW_PAD_CTL_PAD_SAI1_RX_BCLK_PE_MASK  |
		IOMUXC_SW_PAD_CTL_PAD_SAI1_RX_BCLK_PS(3)    |
		IOMUXC_SW_PAD_CTL_PAD_SAI1_RX_BCLK_DSE(0)   |
		IOMUXC_SW_PAD_CTL_PAD_SAI1_RX_BCLK_HYS_MASK;
 #endif

	return 0;

}

SYS_INIT(pico_pi_m4_pinmux_init, PRE_KERNEL_1, 0);
