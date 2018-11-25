/*
 * Copyright (c) 2018 Foundries.io Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DT_BINDINGS_INTERRUPT_CONTROLLER_OPENISA_INTMUX_H_
#define ZEPHYR_INCLUDE_DT_BINDINGS_INTERRUPT_CONTROLLER_OPENISA_INTMUX_H_

/*
 * Symbols for intmux channels, for DT readability when using
 * INTMUX_LEVEL2_IRQ().
 */
#define INTMUX_CH0 0
#define INTMUX_CH1 1
#define INTMUX_CH2 2
#define INTMUX_CH3 3
#define INTMUX_CH4 4
#define INTMUX_CH5 5
#define INTMUX_CH6 6
#define INTMUX_CH7 7

/*
 * Level 1 IRQ offsets for each INTMUX channel.
 */
#define INTMUX_CH0_IRQ 24
#define INTMUX_CH1_IRQ 25
#define INTMUX_CH2_IRQ 26
#define INTMUX_CH3_IRQ 27
#define INTMUX_CH4_IRQ 28
#define INTMUX_CH5_IRQ 29
#define INTMUX_CH6_IRQ 30
#define INTMUX_CH7_IRQ 31

/*
 * Multi-level IRQ number for a INTMUX channel/line interrupt.
 *
 * See gen_isr_tables.py for details.
 */
#define INTMUX_LEVEL2_IRQ(channel, line) \
	((((line) + 1) << 8) | ((channel) + INTMUX_CH0_IRQ))

#endif
