/*
 * Copyright (c) 2022 Aspeed Technology Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DT_BINDINGS_RESET_AST10X0_H_
#define ZEPHYR_INCLUDE_DT_BINDINGS_RESET_AST10X0_H_

#define ASPEED_RESET_GRP_0_OFFSET	(0)
#define ASPEED_RESET_GRP_1_OFFSET	(32)

#define ASPEED_RESET_HACE		(ASPEED_RESET_GRP_0_OFFSET + 4)
#define ASPEED_RESET_USB		(ASPEED_RESET_GRP_0_OFFSET + 3)
#define ASPEED_RESET_SRAM		(ASPEED_RESET_GRP_0_OFFSET + 0)

#define ASPEED_RESET_UART4		(ASPEED_RESET_GRP_1_OFFSET + 31)
#define ASPEED_RESET_UART3		(ASPEED_RESET_GRP_1_OFFSET + 30)
#define ASPEED_RESET_UART2		(ASPEED_RESET_GRP_1_OFFSET + 29)
#define ASPEED_RESET_UART1		(ASPEED_RESET_GRP_1_OFFSET + 28)

#define ASPEED_RESET_JTAG_M0		(ASPEED_RESET_GRP_1_OFFSET + 26)
#define ASPEED_RESET_ESPI		(ASPEED_RESET_GRP_1_OFFSET + 25)

#define ASPEED_RESET_ADC		(ASPEED_RESET_GRP_1_OFFSET + 23)
#define ASPEED_RESET_JTAG_M1		(ASPEED_RESET_GRP_1_OFFSET + 22)

#define ASPEED_RESET_MAC		(ASPEED_RESET_GRP_1_OFFSET + 20)

#define ASPEED_RESET_I3C3		(ASPEED_RESET_GRP_1_OFFSET + 11)
#define ASPEED_RESET_I3C2		(ASPEED_RESET_GRP_1_OFFSET + 10)
#define ASPEED_RESET_I3C1		(ASPEED_RESET_GRP_1_OFFSET + 9)
#define ASPEED_RESET_I3C0		(ASPEED_RESET_GRP_1_OFFSET + 8)
#define ASPEED_RESET_I3C		(ASPEED_RESET_GRP_1_OFFSET + 7)
#define ASPEED_RESET_PWM_TACH		(ASPEED_RESET_GRP_1_OFFSET + 5)
#define ASPEED_RESET_PECI		(ASPEED_RESET_GRP_1_OFFSET + 4)
#define ASPEED_RESET_MII		(ASPEED_RESET_GRP_1_OFFSET + 3)
#define ASPEED_RESET_I2C		(ASPEED_RESET_GRP_1_OFFSET + 2)

#define ASPEED_RESET_LPC		(ASPEED_RESET_GRP_1_OFFSET + 0)

#endif /* ZEPHYR_INCLUDE_DT_BINDINGS_RESET_AST10X0_H_ */
