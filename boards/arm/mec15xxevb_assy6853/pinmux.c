/*
 * Copyright (c) 2018 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/pinmux.h>

#include "soc.h"

struct pinmux_ports_t {
#if DT_NODE_HAS_STATUS(DT_NODELABEL(pinmux_000_036), okay)
	const struct device *porta;
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(pinmux_040_076), okay)
	const struct device *portb;
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(pinmux_100_136), okay)
	const struct device *portc;
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(pinmux_140_176), okay)
	const struct device *portd;
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(pinmux_200_236), okay)
	const struct device *porte;
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(pinmux_240_276), okay)
	const struct device *portf;
#endif
};

#ifdef CONFIG_I2C_XEC
static void i2c_pinmux(struct pinmux_ports_t *p, uint8_t port_sel)
{
	switch (port_sel) {
#if DT_NODE_HAS_STATUS(DT_NODELABEL(pinmux_000_036), okay)
	case 0:
		pinmux_pin_set(p->porta, MCHP_GPIO_003, MCHP_GPIO_CTRL_MUX_F1);
		pinmux_pin_set(p->porta, MCHP_GPIO_004, MCHP_GPIO_CTRL_MUX_F1);
		break;
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(pinmux_100_136), okay)
	case 1:
		pinmux_pin_set(p->portc, MCHP_GPIO_130, MCHP_GPIO_CTRL_MUX_F1);
		pinmux_pin_set(p->portc, MCHP_GPIO_131, MCHP_GPIO_CTRL_MUX_F1);
		break;
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(pinmux_140_176), okay)
	case 2:
		pinmux_pin_set(p->portd, MCHP_GPIO_154, MCHP_GPIO_CTRL_MUX_F1);
		pinmux_pin_set(p->portd, MCHP_GPIO_155, MCHP_GPIO_CTRL_MUX_F1);
		break;
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(pinmux_000_036), okay)
	case 3:
		pinmux_pin_set(p->porta, MCHP_GPIO_007, MCHP_GPIO_CTRL_MUX_F1);
		pinmux_pin_set(p->porta, MCHP_GPIO_010, MCHP_GPIO_CTRL_MUX_F1);
		break;
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(pinmux_140_176), okay)
	case 4:
		pinmux_pin_set(p->portd, MCHP_GPIO_143, MCHP_GPIO_CTRL_MUX_F1);
		pinmux_pin_set(p->portd, MCHP_GPIO_144, MCHP_GPIO_CTRL_MUX_F1);
		break;
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(pinmux_140_176), okay)
	case 5:
		pinmux_pin_set(p->portd, MCHP_GPIO_141, MCHP_GPIO_CTRL_MUX_F1);
		pinmux_pin_set(p->portd, MCHP_GPIO_142, MCHP_GPIO_CTRL_MUX_F1);
		break;
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(pinmux_100_136), okay)
#if DT_NODE_HAS_STATUS(DT_NODELABEL(pinmux_140_176), okay)
	case 6:
		pinmux_pin_set(p->portc, MCHP_GPIO_132, MCHP_GPIO_CTRL_MUX_F1);
		pinmux_pin_set(p->portd, MCHP_GPIO_140, MCHP_GPIO_CTRL_MUX_F1);
		break;
#endif
#endif

#if DT_NODE_HAS_STATUS(DT_NODELABEL(pinmux_000_036), okay)
	case 7:
		pinmux_pin_set(p->porta, MCHP_GPIO_012, MCHP_GPIO_CTRL_MUX_F1);
		pinmux_pin_set(p->porta, MCHP_GPIO_013, MCHP_GPIO_CTRL_MUX_F1);
		break;
#endif

	default:
		break;
	}
}
#endif

static void configure_debug_interface(void)
{
	/* No debug support */
	ECS_REGS->DEBUG_CTRL = 0;
	ECS_REGS->ETM_CTRL = 0;

#ifdef CONFIG_SOC_MEC1501_DEBUG_WITHOUT_TRACING
	/* Release JTAG TDI and JTAG TDO pins so they can be
	 * controlled by their respective PCR register (UART2).
	 * For more details see table 44-1
	 */
	ECS_REGS->DEBUG_CTRL = (MCHP_ECS_DCTRL_DBG_EN |
				MCHP_ECS_DCTRL_MODE_SWD);
#elif defined(CONFIG_SOC_MEC1501_DEBUG_AND_TRACING)
	#if defined(CONFIG_SOC_MEC1501_DEBUG_AND_ETM_TRACING)
		ECS_REGS->ETM_CTRL = MCHP_ECS_ETM_CTRL_EN;
		ECS_REGS->DEBUG_CTRL = (MCHP_ECS_DCTRL_DBG_EN |
				MCHP_ECS_DCTRL_MODE_SWD);
	#elif defined(CONFIG_SOC_MEC1501_DEBUG_AND_SWV_TRACING)
		ECS_REGS->DEBUG_CTRL = (MCHP_ECS_DCTRL_DBG_EN |
				MCHP_ECS_DCTRL_MODE_SWD_SWV);
	#endif /* CONFIG_SOC_MEC1501_DEBUG_AND_TRACING */

#endif /* CONFIG_SOC_MEC1501_DEBUG_WITHOUT_TRACING */
}

static int board_pinmux_init(const struct device *dev)
{
	ARG_UNUSED(dev);
	struct pinmux_ports_t pinmux_ports;

#if DT_NODE_HAS_STATUS(DT_NODELABEL(pinmux_000_036), okay)
	const struct device *const porta = DEVICE_DT_GET(DT_NODELABEL(pinmux_000_036));

	__ASSERT_NO_MSG(device_is_ready(porta));

	pinmux_ports.porta = porta;
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(pinmux_040_076), okay)
	const struct device *const portb = DEVICE_DT_GET(DT_NODELABEL(pinmux_040_076));

	__ASSERT_NO_MSG(device_is_ready(portb));

	pinmux_ports.portb = portb;
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(pinmux_100_136), okay)
	const struct device *const portc = DEVICE_DT_GET(DT_NODELABEL(pinmux_100_136));

	__ASSERT_NO_MSG(device_is_ready(portc));

	pinmux_ports.portc = portc;
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(pinmux_140_176), okay)
	const struct device *const portd = DEVICE_DT_GET(DT_NODELABEL(pinmux_140_176));

	__ASSERT_NO_MSG(device_is_ready(portd));

	pinmux_ports.portd = portd;
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(pinmux_200_236), okay)
	const struct device *const porte = DEVICE_DT_GET(DT_NODELABEL(pinmux_200_236));

	__ASSERT_NO_MSG(device_is_ready(porte));

	pinmux_ports.porte = porte;
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(pinmux_240_276), okay)
	const struct device *const portf = DEVICE_DT_GET(DT_NODELABEL(pinmux_240_276));

	__ASSERT_NO_MSG(device_is_ready(portf));

	pinmux_ports.portf = portf;
#endif

	/* Configure GPIO bank before usage
	 * VTR1 is not configurable
	 * VTR2 doesn't need configuration if setting VTR2_STRAP
	 */
#ifdef CONFIG_SOC_MEC1501_VTR3_1_8V
	ECS_REGS->GPIO_BANK_PWR |= MCHP_ECS_VTR3_LVL_18;
#endif

	configure_debug_interface();

	/* Configure pins that are not GPIOS by default */
#ifdef CONFIG_SOC_MEC1501_VCI_PINS_AS_GPIOS
	pinmux_pin_set(porta, MCHP_GPIO_000, MCHP_GPIO_CTRL_MUX_F0);
	pinmux_pin_set(portd, MCHP_GPIO_161, MCHP_GPIO_CTRL_MUX_F0);
	pinmux_pin_set(portd, MCHP_GPIO_162, MCHP_GPIO_CTRL_MUX_F0);
	pinmux_pin_set(portd, MCHP_GPIO_163, MCHP_GPIO_CTRL_MUX_F0);
	pinmux_pin_set(portd, MCHP_GPIO_172, MCHP_GPIO_CTRL_MUX_F0);
	pinmux_pin_set(portf, MCHP_GPIO_250, MCHP_GPIO_CTRL_MUX_F0);
#endif
	pinmux_pin_set(portd, MCHP_GPIO_170, MCHP_GPIO_CTRL_MUX_F0);

	/* See table 2-4 from the data sheet for pin multiplexing*/
#if DT_NODE_HAS_STATUS(DT_NODELABEL(uart2), okay)
	/* Set muxing, for UART 2 TX/RX and power up */
	mchp_pcr_periph_slp_ctrl(PCR_UART2, MCHP_PCR_SLEEP_DIS);

	UART2_REGS->CFG_SEL = (MCHP_UART_LD_CFG_INTCLK +
		MCHP_UART_LD_CFG_RESET_SYS + MCHP_UART_LD_CFG_NO_INVERT);
	UART2_REGS->ACTV = MCHP_UART_LD_ACTIVATE;

	pinmux_pin_set(portd, MCHP_GPIO_145, MCHP_GPIO_CTRL_MUX_F2);
	pinmux_pin_set(portd, MCHP_GPIO_146, MCHP_GPIO_CTRL_MUX_F2);
#endif

#ifdef CONFIG_ADC_XEC
	/* Disable sleep for ADC block */
	mchp_pcr_periph_slp_ctrl(PCR_ADC, MCHP_PCR_SLEEP_DIS);

	/* ADC pin muxes, ADC00 - ADC07 */
	/* Note, by default ETM is enabled ADC00-ADC03 are not available */
#ifndef CONFIG_SOC_MEC1501_DEBUG_AND_ETM_TRACING
	pinmux_pin_set(porte, MCHP_GPIO_200, MCHP_GPIO_CTRL_MUX_F1);
	pinmux_pin_set(porte, MCHP_GPIO_201, MCHP_GPIO_CTRL_MUX_F1);
	pinmux_pin_set(porte, MCHP_GPIO_202, MCHP_GPIO_CTRL_MUX_F1);
	pinmux_pin_set(porte, MCHP_GPIO_203, MCHP_GPIO_CTRL_MUX_F1);
#endif
	pinmux_pin_set(porte, MCHP_GPIO_204, MCHP_GPIO_CTRL_MUX_F1);
	pinmux_pin_set(porte, MCHP_GPIO_205, MCHP_GPIO_CTRL_MUX_F1);
	pinmux_pin_set(porte, MCHP_GPIO_206, MCHP_GPIO_CTRL_MUX_F1);
	pinmux_pin_set(porte, MCHP_GPIO_207, MCHP_GPIO_CTRL_MUX_F1);

	/* VREF2_ADC */
	pinmux_pin_set(portb, MCHP_GPIO_067, MCHP_GPIO_CTRL_MUX_F1);
#endif /* CONFIG_ADC_XEC */

#ifdef CONFIG_I2C_XEC

#if DT_NODE_HAS_STATUS(DT_INST(0, microchip_xec_i2c), okay)
	i2c_pinmux(&pinmux_ports, DT_PROP(DT_INST(0, microchip_xec_i2c), port_sel));
#endif

#if DT_NODE_HAS_STATUS(DT_INST(1, microchip_xec_i2c), okay)
	i2c_pinmux(&pinmux_ports, DT_PROP(DT_INST(1, microchip_xec_i2c), port_sel));
#endif

#if DT_NODE_HAS_STATUS(DT_INST(2, microchip_xec_i2c), okay)
	i2c_pinmux(&pinmux_ports, DT_PROP(DT_INST(2, microchip_xec_i2c), port_sel));
#endif

#if DT_NODE_HAS_STATUS(DT_INST(3, microchip_xec_i2c), okay)
	i2c_pinmux(&pinmux_ports, DT_PROP(DT_INST(3, microchip_xec_i2c), port_sel));
#endif

#if DT_NODE_HAS_STATUS(DT_INST(4, microchip_xec_i2c), okay)
	i2c_pinmux(&pinmux_ports, DT_PROP(DT_INST(4, microchip_xec_i2c), port_sel));
#endif

#endif /* CONFIG_I2C_XEC */

#ifdef CONFIG_ESPI_XEC
	mchp_pcr_periph_slp_ctrl(PCR_ESPI, MCHP_PCR_SLEEP_DIS);
	/* ESPI RESET */
	pinmux_pin_set(portb, MCHP_GPIO_061, MCHP_GPIO_CTRL_MUX_F1);
	/* ESPI ALERT */
	pinmux_pin_set(portb, MCHP_GPIO_063, MCHP_GPIO_CTRL_MUX_F1);
	/* ESPI CS */
	pinmux_pin_set(portb, MCHP_GPIO_066, MCHP_GPIO_CTRL_MUX_F1);
	/* ESPI CLK */
	pinmux_pin_set(portb, MCHP_GPIO_065, MCHP_GPIO_CTRL_MUX_F1);
	/* ESPI IO1-4*/
	pinmux_pin_set(portb, MCHP_GPIO_070, MCHP_GPIO_CTRL_MUX_F1);
	pinmux_pin_set(portb, MCHP_GPIO_071, MCHP_GPIO_CTRL_MUX_F1);
	pinmux_pin_set(portb, MCHP_GPIO_072, MCHP_GPIO_CTRL_MUX_F1);
	pinmux_pin_set(portb, MCHP_GPIO_073, MCHP_GPIO_CTRL_MUX_F1);
#endif

#ifdef CONFIG_SPI_XEC_QMSPI
#if DT_NODE_HAS_STATUS(DT_INST(0, microchip_xec_qmspi), okay)
	mchp_pcr_periph_slp_ctrl(PCR_QMSPI, MCHP_PCR_SLEEP_DIS);

#if DT_PROP(DT_INST(0, microchip_xec_qmspi), port_sel) == 0
	/* Port 0: Shared SPI pins. Shared has two chip selects */
#if DT_PROP(DT_INST(0, microchip_xec_qmspi), chip_select) == 0
	pinmux_pin_set(portb, MCHP_GPIO_055, MCHP_GPIO_CTRL_MUX_F2);
#else
	pinmux_pin_set(porta, MCHP_GPIO_002, MCHP_GPIO_CTRL_MUX_F2);
#endif
	pinmux_pin_set(portb, MCHP_GPIO_056, MCHP_GPIO_CTRL_MUX_F2);
	pinmux_pin_set(porte, MCHP_GPIO_223, MCHP_GPIO_CTRL_MUX_F1);
	pinmux_pin_set(porte, MCHP_GPIO_224, MCHP_GPIO_CTRL_MUX_F2);
#if DT_PROP(DT_INST(0, microchip_xec_qmspi), lines) == 4
	pinmux_pin_set(porte, MCHP_GPIO_227, MCHP_GPIO_CTRL_MUX_F1);
	pinmux_pin_set(porta, MCHP_GPIO_016, MCHP_GPIO_CTRL_MUX_F2);
#endif

#else
	/* Port 1: Private SPI pins. Only one chip select */
	pinmux_pin_set(portc, MCHP_GPIO_124, MCHP_GPIO_CTRL_MUX_F1);
	pinmux_pin_set(portc, MCHP_GPIO_125, MCHP_GPIO_CTRL_MUX_F1);
	pinmux_pin_set(portc, MCHP_GPIO_121, MCHP_GPIO_CTRL_MUX_F1);
	pinmux_pin_set(portc, MCHP_GPIO_122, MCHP_GPIO_CTRL_MUX_F1);
#if DT_PROP(DT_INST(0, microchip_xec_qmspi), lines) == 4
	pinmux_pin_set(portc, MCHP_GPIO_123, MCHP_GPIO_CTRL_MUX_F1);
	pinmux_pin_set(portc, MCHP_GPIO_126, MCHP_GPIO_CTRL_MUX_F1);
#endif
#endif /* DT_PROP(DT_INST(0, microchip_xec_qmspi), port_sel) == 0 */

#endif /* DT_NODE_HAS_STATUS(DT_INST(0, microchip_xec_qmspi), okay) */
#endif /* CONFIG_SPI_XEC_QMSPI */

#ifdef CONFIG_SOC_MEC1501_TEST_CLK_OUT
	/*
	 * Deep sleep testing: Enable TEST_CLK_OUT on GPIO_060 function 2.
	 * TEST_CLK_OUT is the PLL 48MHz conditioned output.
	 */
	pinmux_pin_set(portb, MCHP_GPIO_060, MCHP_GPIO_CTRL_MUX_F2);
#endif

#ifdef CONFIG_TACH_XEC

#if DT_NODE_HAS_STATUS(DT_INST(0, microchip_xec_tach), okay)
	pinmux_pin_set(portb, MCHP_GPIO_050, MCHP_GPIO_CTRL_MUX_F1);
#endif /* CONFIG_TACH_XEC */

#endif

	return 0;
}

SYS_INIT(board_pinmux_init, PRE_KERNEL_1, CONFIG_PINMUX_INIT_PRIORITY);
