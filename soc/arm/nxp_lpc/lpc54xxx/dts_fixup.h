/*
 * Copyright (c) 2017, NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* SoC level DTS fixup file */

#if defined(CONFIG_SOC_LPC54114_M0)
#define DT_NUM_IRQ_PRIO_BITS		DT_ARM_V6M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS
#else
#define DT_NUM_IRQ_PRIO_BITS		DT_ARM_V7M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS
#endif

#define DT_USART_MCUX_LPC_0_BASE_ADDRESS	DT_NXP_LPC_USART_40086000_BASE_ADDRESS
#define DT_USART_MCUX_LPC_0_BAUD_RATE	DT_NXP_LPC_USART_40086000_CURRENT_SPEED
#define DT_USART_MCUX_LPC_0_IRQ	        DT_NXP_LPC_USART_40086000_IRQ_0
#define DT_USART_MCUX_LPC_0_IRQ_PRI	        DT_NXP_LPC_USART_40086000_IRQ_0_PRIORITY
#define DT_USART_MCUX_LPC_0_NAME	        DT_NXP_LPC_USART_40086000_LABEL

#define DT_MAILBOX_MCUX_MAILBOX_0_IRQ	DT_NXP_LPC_MAILBOX_4008B000_IRQ_0
#define DT_MAILBOX_MCUX_MAILBOX_0_IRQ_PRI	DT_NXP_LPC_MAILBOX_4008B000_IRQ_0_PRIORITY
#define DT_MAILBOX_MCUX_MAILBOX_0_NAME	DT_NXP_LPC_MAILBOX_4008B000_LABEL
#define DT_MAILBOX_MCUX_MAILBOX_0_BASE_ADDRESS	DT_NXP_LPC_MAILBOX_4008B000_BASE_ADDRESS

/* End of SoC Level DTS fixup file */
