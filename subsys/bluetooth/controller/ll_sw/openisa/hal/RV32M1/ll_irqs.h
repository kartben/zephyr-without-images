/*
 * Copyright 2019 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */
/* Needed for the DT_INST_* defines below */
#include <generated_dts_board.h>

#define LL_SWI4_IRQn EMVSIM0_IRQn
#define LL_SWI5_IRQn MUA_IRQn

/*
 * LPTMR1 -> INTMUX_CH2. We expect it to be the only IRQ source for this channel
 * We'll use the INTMUX ISR for channel 2 instead of LPTMR1 ISR
 */
#define LL_RTC0_IRQn_1st_lvl DT_INST_2_OPENISA_RV32M1_INTMUX_CH_IRQ_0
#define LL_RTC0_IRQn_2nd_lvl DT_INST_1_OPENISA_RV32M1_LPTMR_IRQ_0

/*
 * radio -> INTMUX_CH3. We expect it to be the only IRQ source for this channel
 * We'll use the INTMUX ISR for channel 3 instead of radio ISR
 */
#define LL_RADIO_IRQn_1st_lvl DT_INST_3_OPENISA_RV32M1_INTMUX_CH_IRQ_0
#define LL_RADIO_IRQn_2nd_lvl DT_INST_0_OPENISA_RV32M1_GENFSK_IRQ_0

#define LL_RTC0_IRQn LL_RTC0_IRQn_1st_lvl
#define LL_RADIO_IRQn LL_RADIO_IRQn_1st_lvl
