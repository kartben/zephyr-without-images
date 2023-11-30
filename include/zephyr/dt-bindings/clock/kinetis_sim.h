/*
 * Copyright (c) 2017, NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DT_BINDINGS_CLOCK_KINETIS_SIM_H_
#define ZEPHYR_INCLUDE_DT_BINDINGS_CLOCK_KINETIS_SIM_H_

#define KINETIS_SIM_CORESYS_CLK		0
#define KINETIS_SIM_PLATFORM_CLK	1
#define KINETIS_SIM_BUS_CLK		2
#define KINETIS_SIM_FAST_PERIPHERAL_CLK	5
#define KINETIS_SIM_LPO_CLK		19
#define KINETIS_SIM_DMAMUX_CLK  KINETIS_SIM_BUS_CLK
#define KINETIS_SIM_DMA_CLK     KINETIS_SIM_CORESYS_CLK
#define KINETIS_SIM_SIM_SOPT7   7

#define KINETIS_SIM_PLLFLLSEL_MCGFLLCLK	0
#define KINETIS_SIM_PLLFLLSEL_MCGPLLCLK	1
#define KINETIS_SIM_PLLFLLSEL_IRC48MHZ	3

#define KINETIS_SIM_ER32KSEL_OSC32KCLK	0
#define KINETIS_SIM_ER32KSEL_RTC	2
#define KINETIS_SIM_ER32KSEL_LPO1KHZ	3

#define KINETIS_SIM_ENET_CLK		4321


#endif /* ZEPHYR_INCLUDE_DT_BINDINGS_CLOCK_KINETIS_SIM_H_ */
