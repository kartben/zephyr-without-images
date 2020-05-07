/*
 * Copyright (c) 2017,  NXP
 * SPDX-License-Identifier: Apache-2.0
 */

#include <init.h>
#include <drivers/pinmux.h>
#include <fsl_common.h>
#include <fsl_iocon.h>
#include <soc.h>

static int lpcxpresso_54114_pinmux_init(struct device *dev)
{
	ARG_UNUSED(dev);

#ifdef CONFIG_PINMUX_MCUX_LPC_PORT0
	struct device *port0 =
		device_get_binding(CONFIG_PINMUX_MCUX_LPC_PORT0_NAME);
#endif

#ifdef	CONFIG_PINMUX_MCUX_LPC_PORT1
	struct device *port1 =
		device_get_binding(CONFIG_PINMUX_MCUX_LPC_PORT1_NAME);
#endif

#if DT_NODE_HAS_COMPAT_STATUS(DT_NODELABEL(flexcomm0), nxp_lpc_usart, okay)
	/* USART0 RX,  TX */
	const u32_t port0_pin0_config = (
			IOCON_PIO_FUNC1 |
			IOCON_PIO_MODE_INACT |
			IOCON_PIO_INV_DI |
			IOCON_PIO_DIGITAL_EN |
			IOCON_PIO_INPFILT_OFF |
			IOCON_PIO_SLEW_STANDARD |
			IOCON_PIO_OPENDRAIN_DI
			);

	const u32_t port0_pin1_config = (
			IOCON_PIO_FUNC1 |
			IOCON_PIO_MODE_INACT |
			IOCON_PIO_INV_DI |
			IOCON_PIO_DIGITAL_EN |
			IOCON_PIO_INPFILT_OFF |
			IOCON_PIO_SLEW_STANDARD |
			IOCON_PIO_OPENDRAIN_DI
			);

	pinmux_pin_set(port0, 0, port0_pin0_config);
	pinmux_pin_set(port0, 1, port0_pin1_config);

#endif

#if DT_HAS_NODE_STATUS_OKAY(DT_NODELABEL(gpio0))
	const u32_t port0_pin29_config = (
			IOCON_PIO_FUNC0 |
			IOCON_PIO_MODE_PULLUP |
			IOCON_PIO_INV_DI |
			IOCON_PIO_DIGITAL_EN |
			IOCON_PIO_INPFILT_OFF |
			IOCON_PIO_OPENDRAIN_DI
			);

	pinmux_pin_set(port0, 29, port0_pin29_config);

	const u32_t port0_pin24_config = (
			IOCON_PIO_FUNC0 |
			IOCON_PIO_INV_DI |
			IOCON_PIO_DIGITAL_EN |
			IOCON_PIO_INPFILT_OFF |
			IOCON_PIO_OPENDRAIN_DI
			);
	pinmux_pin_set(port0,  24, port0_pin24_config);

	const u32_t port0_pin31_config = (
			IOCON_PIO_FUNC0 |
			IOCON_PIO_MODE_PULLUP |
			IOCON_PIO_INV_DI |
			IOCON_PIO_DIGITAL_EN |
			IOCON_PIO_INPFILT_OFF |
			IOCON_PIO_OPENDRAIN_DI
			);
	pinmux_pin_set(port0,  31, port0_pin31_config);

	const u32_t port0_pin4_config = (
			IOCON_PIO_FUNC0 |
			IOCON_PIO_MODE_PULLUP |
			IOCON_PIO_INV_DI |
			IOCON_PIO_DIGITAL_EN |
			IOCON_PIO_INPFILT_OFF |
			IOCON_PIO_OPENDRAIN_DI
			);
	pinmux_pin_set(port0,  4, port0_pin4_config);

#endif

#if DT_HAS_NODE_STATUS_OKAY(DT_NODELABEL(gpio1))
	const u32_t port1_pin10_config = (
			IOCON_PIO_FUNC0 |
			IOCON_PIO_MODE_PULLUP |
			IOCON_PIO_INV_DI |
			IOCON_PIO_DIGITAL_EN |
			IOCON_PIO_INPFILT_OFF |
			IOCON_PIO_SLEW_STANDARD |
			IOCON_PIO_OPENDRAIN_DI
			);

	pinmux_pin_set(port1, 10, port1_pin10_config);
#endif

#if DT_NODE_HAS_COMPAT_STATUS(DT_NODELABEL(flexcomm4), nxp_lpc_i2c, okay)
	/* PORT0 PIN25 is configured as FC4_RTS_SCL_SSEL1 */
	pinmux_pin_set(port0, 25, IOCON_PIO_FUNC1 |
				  IOCON_PIO_I2CSLEW_I2C |
				  IOCON_PIO_INV_DI |
				  IOCON_PIO_DIGITAL_EN |
				  IOCON_PIO_INPFILT_OFF |
				  IOCON_PIO_I2CDRIVE_LOW |
				  IOCON_PIO_I2CFILTER_EN);

	/* PORT0 PIN26 is configured as FC4_CTS_SDA_SSEL0 */
	pinmux_pin_set(port0, 26, IOCON_PIO_FUNC1 |
				  IOCON_PIO_I2CSLEW_I2C |
				  IOCON_PIO_INV_DI |
				  IOCON_PIO_DIGITAL_EN |
				  IOCON_PIO_INPFILT_OFF |
				  IOCON_PIO_I2CDRIVE_LOW |
				  IOCON_PIO_I2CFILTER_EN);
#endif

#if DT_NODE_HAS_COMPAT_STATUS(DT_NODELABEL(flexcomm5), nxp_lpc_spi, okay)
	/* PORT0 PIN18 is configured as FC5_TXD_SCL_MISO */
	pinmux_pin_set(port0, 18, IOCON_PIO_FUNC1 |
				  IOCON_PIO_MODE_PULLUP |
				  IOCON_PIO_INV_DI |
				  IOCON_PIO_DIGITAL_EN |
				  IOCON_PIO_SLEW_STANDARD |
				  IOCON_PIO_OPENDRAIN_DI);

	/* PORT0 PIN19 is configured as FC5_SCK-SPIFI_CSn */
	pinmux_pin_set(port0, 19, IOCON_PIO_FUNC1 |
				  IOCON_PIO_MODE_PULLUP |
				  IOCON_PIO_INV_DI |
				  IOCON_PIO_DIGITAL_EN |
				  IOCON_PIO_SLEW_STANDARD |
				  IOCON_PIO_OPENDRAIN_DI);

	/* PORT0 PIN20 is configured as FC5_RXD_SDA_MOSI */
	pinmux_pin_set(port0, 20, IOCON_PIO_FUNC1 |
				  IOCON_PIO_MODE_PULLUP |
				  IOCON_PIO_INV_DI |
				  IOCON_PIO_DIGITAL_EN |
				  IOCON_PIO_SLEW_STANDARD |
				  IOCON_PIO_OPENDRAIN_DI);

	/* PORT1 PIN1 is configured as FC5_SSEL2 */
	pinmux_pin_set(port1,  1, IOCON_PIO_FUNC4 |
				  IOCON_PIO_MODE_PULLUP |
				  IOCON_PIO_INV_DI |
				  IOCON_PIO_DIGITAL_EN |
				  IOCON_PIO_SLEW_STANDARD |
				  IOCON_PIO_OPENDRAIN_DI);
#endif

	return 0;
}

SYS_INIT(lpcxpresso_54114_pinmux_init,  PRE_KERNEL_1,
	 CONFIG_PINMUX_INIT_PRIORITY);
