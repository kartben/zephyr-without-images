/*
 * Copyright (c) 2022, Teslabs Engineering S.L.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef SOC_ARM_GIGADEVICE_GD32F4XX_GD32_REGS_H_
#define SOC_ARM_GIGADEVICE_GD32F4XX_GD32_REGS_H_

#include <zephyr/sys/util_macro.h>

/* RCU */
#define RCU_CFG0_OFFSET      0x08U
#define RCU_AHB1EN_OFFSET    0x30U
#define RCU_AHB2EN_OFFSET    0x34U
#define RCU_AHB3EN_OFFSET    0x38U
#define RCU_APB1EN_OFFSET    0x40U
#define RCU_APB2EN_OFFSET    0x44U
#define RCU_CFG1_OFFSET      0x8CU
#define RCU_ADDAPB1EN_OFFSET 0xE4U

#define RCU_CFG0_AHBPSC_POS  4U
#define RCU_CFG0_AHBPSC_MSK  (BIT_MASK(4) << RCU_CFG0_AHBPSC_POS)
#define RCU_CFG0_APB1PSC_POS 10U
#define RCU_CFG0_APB1PSC_MSK (BIT_MASK(3) << RCU_CFG0_APB1PSC_POS)
#define RCU_CFG0_APB2PSC_POS 13U
#define RCU_CFG0_APB2PSC_MSK (BIT_MASK(3) << RCU_CFG0_APB2PSC_POS)

#define RCU_CFG1_TIMERSEL_POS 24U
#define RCU_CFG1_TIMERSEK_MSK (BIT_MASK(1) << RCU_CFG1_TIMERSEL_POS)

#endif /* SOC_ARM_GIGADEVICE_GD32F4XX_GD32_REGS_H_ */
