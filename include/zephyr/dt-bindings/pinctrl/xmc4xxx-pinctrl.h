/*
 * Copyright (c) 2022 Schlumberger
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DT_BINDINGS_PINCTRL_XMC4XXX_PINCTRL_H_
#define ZEPHYR_INCLUDE_DT_BINDINGS_PINCTRL_XMC4XXX_PINCTRL_H_

/* Bit Masks */

#define XMC4XXX_PORT_POS        0
#define XMC4XXX_PORT_MASK       0xf

#define XMC4XXX_PIN_POS	        4
#define XMC4XXX_PIN_MASK        0xf

#define XMC4XXX_ALT_POS	        8
#define XMC4XXX_ALT_MASK        0xf

#define XMC4XXX_PULL_DOWN_POS   12
#define XMC4XXX_PULL_DOWN_MASK  0x1

#define XMC4XXX_PULL_UP_POS     13
#define XMC4XXX_PULL_UP_MASK    0x1

#define XMC4XXX_PUSH_PULL_POS   14
#define XMC4XXX_PUSH_PULL_MASK  0x1

#define XMC4XXX_OPEN_DRAIN_POS	15
#define XMC4XXX_OPEN_DRAIN_MASK 0x1

#define XMC4XXX_OUT_HIGH_POS    16
#define XMC4XXX_OUT_HIGH_MASK   0x1

#define XMC4XXX_OUT_LOW_POS     17
#define XMC4XXX_OUT_LOW_MASK    0x1

#define XMC4XXX_INV_INPUT_POS   18
#define XMC4XXX_INV_INPUT_MASK  0x1

#define XMC4XXX_DRIVE_POS       19
#define XMC4XXX_DRIVE_MASK      0x7

#define XMC4XXX_HWCTRL_POS      22
#define XMC4XXX_HWCTRL_MASK     0x3

/* Setters and getters */

#define XMC4XXX_PINMUX_SET(port, pin, alt_fun)                                                     \
	((port) << XMC4XXX_PORT_POS | (pin) << XMC4XXX_PIN_POS | (alt_fun) << XMC4XXX_ALT_POS)

#define XMC4XXX_PINMUX_GET_PORT(mx)	      ((mx >> XMC4XXX_PORT_POS)       & XMC4XXX_PORT_MASK)
#define XMC4XXX_PINMUX_GET_PIN(mx)	      ((mx >> XMC4XXX_PIN_POS)        & XMC4XXX_PIN_MASK)
#define XMC4XXX_PINMUX_GET_ALT(mx)	      ((mx >> XMC4XXX_ALT_POS)        & XMC4XXX_ALT_MASK)
#define XMC4XXX_PINMUX_GET_PULL_DOWN(mx)  ((mx >> XMC4XXX_PULL_DOWN_POS)  & XMC4XXX_PULL_DOWN_MASK)
#define XMC4XXX_PINMUX_GET_PULL_UP(mx)	  ((mx >> XMC4XXX_PULL_UP_POS)    & XMC4XXX_PULL_UP_MASK)
#define XMC4XXX_PINMUX_GET_PUSH_PULL(mx)  ((mx >> XMC4XXX_PUSH_PULL_POS)  & XMC4XXX_PUSH_PULL_MASK)
#define XMC4XXX_PINMUX_GET_OPEN_DRAIN(mx) ((mx >> XMC4XXX_OPEN_DRAIN_POS) & XMC4XXX_OPEN_DRAIN_MASK)
#define XMC4XXX_PINMUX_GET_OUT_HIGH(mx)	  ((mx >> XMC4XXX_OUT_HIGH_POS)   & XMC4XXX_OUT_HIGH_MASK)
#define XMC4XXX_PINMUX_GET_OUT_LOW(mx)	  ((mx >> XMC4XXX_OUT_LOW_POS)    & XMC4XXX_OUT_LOW_MASK)
#define XMC4XXX_PINMUX_GET_INV_INPUT(mx)  ((mx >> XMC4XXX_INV_INPUT_POS)  & XMC4XXX_INV_INPUT_MASK)
#define XMC4XXX_PINMUX_GET_DRIVE(mx)	  ((mx >> XMC4XXX_DRIVE_POS)      & XMC4XXX_DRIVE_MASK)
#define XMC4XXX_PINMUX_GET_HWCTRL(mx)	  ((mx >> XMC4XXX_HWCTRL_POS)     & XMC4XXX_HWCTRL_MASK)

#endif /* ZEPHYR_INCLUDE_DT_BINDINGS_PINCTRL_XMC4XXX_PINCTRL_H_ */
