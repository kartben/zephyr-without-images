/*
 * Copyright (c) 2019 Benjamin Valentin
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <init.h>
#include <drivers/pinmux.h>
#include <soc.h>

static int board_pinmux_init(const struct device *dev)
{
	const struct device *muxa = DEVICE_DT_GET(DT_NODELABEL(pinmux_a));
	const struct device *muxb = DEVICE_DT_GET(DT_NODELABEL(pinmux_b));
	const struct device *muxc = DEVICE_DT_GET(DT_NODELABEL(pinmux_c));
	const struct device *muxd = DEVICE_DT_GET(DT_NODELABEL(pinmux_d));

	ARG_UNUSED(dev);

	if (!device_is_ready(muxa)) {
		return -ENXIO;
	}
	if (!device_is_ready(muxb)) {
		return -ENXIO;
	}
	if (!device_is_ready(muxc)) {
		return -ENXIO;
	}
	if (!device_is_ready(muxd)) {
		return -ENXIO;
	}

#ifdef CONFIG_USB_DC_SAM0
	/* USB DP on PA25, USB DM on PA24 */
	pinmux_pin_set(muxa, 25, PINMUX_FUNC_H);
	pinmux_pin_set(muxa, 24, PINMUX_FUNC_H);
#endif

#if (DT_NODE_HAS_STATUS(DT_NODELABEL(gmac), okay) && CONFIG_ETH_SAM_GMAC)
	pinmux_pin_set(muxa, 14, PINMUX_FUNC_L);	/* PA14 = GTXCK */
	pinmux_pin_set(muxa, 17, PINMUX_FUNC_L);	/* PA17 = GTXEN */
	pinmux_pin_set(muxa, 18, PINMUX_FUNC_L);	/* PA18 = GTX0 */
	pinmux_pin_set(muxa, 19, PINMUX_FUNC_L);	/* PA19 = GTX1 */
	pinmux_pin_set(muxc, 20, PINMUX_FUNC_L);	/* PC20 = GRXDV */
	pinmux_pin_set(muxa, 13, PINMUX_FUNC_L);	/* PA13 = GRX0 */
	pinmux_pin_set(muxa, 12, PINMUX_FUNC_L);	/* PA12 = GRX1 */
	pinmux_pin_set(muxa, 15, PINMUX_FUNC_L);	/* PA15 = GRXER */
	pinmux_pin_set(muxc, 11, PINMUX_FUNC_L);	/* PC11 = GMDC */
	pinmux_pin_set(muxc, 12, PINMUX_FUNC_L);	/* PC12 = GMDIO */
#endif

	return 0;
}

SYS_INIT(board_pinmux_init, PRE_KERNEL_2, CONFIG_PINMUX_INIT_PRIORITY);
