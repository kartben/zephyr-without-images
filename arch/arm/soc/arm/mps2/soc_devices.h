/*
 * Copyright (c) 2017 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _SOC_DEVICES_H_
#define _SOC_DEVICES_H_

#include <soc_memory_map.h>
#include <soc_irq.h>

#if defined(CONFIG_GPIO)
/* CMSDK AHB General Purpose Input/Output (GPIO) */
#define CMSDK_AHB_GPIO0	GPIO_0_BASE_ADDR
#define IRQ_PORT0_ALL	IRQ_GPIO_0_COMBINED
#define CMSDK_AHB_GPIO1	GPIO_1_BASE_ADDR
#define IRQ_PORT1_ALL	IRQ_GPIO_1_COMBINED
#define CMSDK_AHB_GPIO2	GPIO_2_BASE_ADDR
#define IRQ_PORT2_ALL	IRQ_GPIO_2_COMBINED
#define CMSDK_AHB_GPIO3	GPIO_3_BASE_ADDR
#define IRQ_PORT3_ALL	IRQ_GPIO_3_COMBINED
#endif /* CONFIG_GPIO */

#if defined(CONFIG_UART_CMSDK_APB)
/* CMSDK APB Universal Asynchronous Receiver-Transmitter (UART) */
#define CMSDK_APB_UART0		UART_0_BASE_ADDR
#define CMSDK_APB_UART_0_IRQ_TX	IRQ_UART_0_TX
#define CMSDK_APB_UART_0_IRQ_RX	IRQ_UART_0_RX
#define CMSDK_APB_UART1		UART_1_BASE_ADDR
#define CMSDK_APB_UART_1_IRQ_TX	IRQ_UART_1_TX
#define CMSDK_APB_UART_1_IRQ_RX	IRQ_UART_1_RX
#define CMSDK_APB_UART2		UART_2_BASE_ADDR
#define CMSDK_APB_UART_2_IRQ_TX	IRQ_UART_2_TX
#define CMSDK_APB_UART_2_IRQ_RX	IRQ_UART_2_RX
#define CMSDK_APB_UART3		UART_3_BASE_ADDR
#define CMSDK_APB_UART_3_IRQ_TX	IRQ_UART_3_TX
#define CMSDK_APB_UART_3_IRQ_RX	IRQ_UART_3_RX
#define CMSDK_APB_UART4		UART_4_BASE_ADDR
#define CMSDK_APB_UART_4_IRQ_TX	IRQ_UART_4_TX
#define CMSDK_APB_UART_4_IRQ_RX	IRQ_UART_4_RX
#endif /* CONFIG_UART_CMSDK_APB */

#if defined(CONFIG_WATCHDOG)
/* CMSDK APB Watchdog */
#define CMSDK_APB_WDOG	WDOG_BASE_ADDR
#endif /* CONFIG_WATCHDOG */

#if defined(CONFIG_COUNTER)
/* CMSDK APB Timers */
#define CMSDK_APB_TIMER0	TIMER_0_BASE_ADDR
#define CMSDK_APB_TIMER_0_IRQ	IRQ_TIMER_0
#define CMSDK_APB_TIMER1	TIMER_1_BASE_ADDR
#define CMSDK_APB_TIMER_1_IRQ	IRQ_TIMER_1

/* CMSDK APB Dual Timer */
#define CMSDK_APB_DTIMER	DTIMER_BASE_ADDR
#define CMSDK_APB_DUALTIMER_IRQ	IRQ_DUAL_TIMER
#endif /* CONFIG_COUNTER */

#ifndef _ASMLANGUAGE

#include "soc_registers.h"

/* System Control Register (SYSCON) */
#define __MPS2_SYSCON ((volatile struct mps2_syscon *)SYSCON_BASE_ADDR)

/* FPGA system control block (FPGAIO) */
#define __MPS2_FPGAIO ((volatile struct mps2_fpgaio *)FPGAIO_BASE_ADDR)

/* Names of GPIO drivers used to provide access to some FPGAIO registers */
#define FPGAIO_LED0_GPIO_NAME		"FPGAIO_LED0"
#define FPGAIO_BUTTON_GPIO_NAME		"FPGAIO_BUTTON"
#define FPGAIO_MISC_GPIO_NAME		"FPGAIO_MISC"

#endif /* !_ASMLANGUAGE */

#endif /* _SOC_DEVICES_H_ */
