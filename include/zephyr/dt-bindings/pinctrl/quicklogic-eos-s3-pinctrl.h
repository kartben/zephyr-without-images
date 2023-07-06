/*
 * Copyright (c) 2023 Antmicro <www.antmicro.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DT_BINDINGS_PINCTRL_QUICKLOGIC_EOS_S3_PINCTRL_H_
#define ZEPHYR_INCLUDE_DT_BINDINGS_PINCTRL_QUICKLOGIC_EOS_S3_PINCTRL_H_

#include <zephyr/sys/util_macro.h>

#define IO_MUX_REG_MAX_OFFSET	107
#define IO_MUX_MAX_PAD_NR	45

#define FUNC_SEL_UART_RX	(77 << 13)

#define QUICKLOGIC_EOS_S3_PINMUX(pin, fun)	(pin) (fun)

#define UART_TX_PAD44		QUICKLOGIC_EOS_S3_PINMUX(44, 0x3)
#define UART_RX_PAD45		QUICKLOGIC_EOS_S3_PINMUX(45, FUNC_SEL_UART_RX | BIT(2))
#define USB_PU_CTRL_PAD23	QUICKLOGIC_EOS_S3_PINMUX(23, 0x0)
#define USB_DN_PAD28		QUICKLOGIC_EOS_S3_PINMUX(28, 0x0)
#define USB_DP_PAD31		QUICKLOGIC_EOS_S3_PINMUX(31, 0x0)

#endif /* ZEPHYR_INCLUDE_DT_BINDINGS_PINCTRL_QUICKLOGIC_EOS_S3_PINCTRL_H_ */
