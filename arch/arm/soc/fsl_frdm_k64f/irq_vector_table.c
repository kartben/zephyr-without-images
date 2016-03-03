/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file
 * @brief IRQ part of vector table
 *
 * This file contains the IRQ part of the vector table. It is meant to be used
 * for one of two cases:
 *
 * a) When software-managed ISRs (SW_ISR_TABLE) is enabled, and in that case it
 *    binds _isr_wrapper() to all the IRQ entries in the vector table.
 *
 * b) When the platform is written so that device ISRs are installed directly in
 *    the vector table, they are enumerated here.
 */

#include <toolchain.h>
#include <sections.h>

#include <soc.h>
#include <serial/uart_k20.h>

extern void _isr_wrapper(void);
typedef void (*vth)(void); /* Vector Table Handler */

#if defined(CONFIG_SW_ISR_TABLE)

vth __irq_vector_table _irq_vector_table[CONFIG_NUM_IRQS] = {
	[0 ...(CONFIG_NUM_IRQS - 1)] = _isr_wrapper,
};

#elif !defined(CONFIG_IRQ_VECTOR_TABLE_CUSTOM)

extern void _irq_spurious(void);

#if defined(CONFIG_UART_INTERRUPT_DRIVEN)
static void _uart_k20_0_isr(void)
{
	uart_k20_isr(DEVICE_GET(uart_k20_0));
	_IntExit();
}

static void _uart_k20_1_isr(void)
{
	uart_k20_isr(DEVICE_GET(uart_k20_1));
	_IntExit();
}

static void _uart_k20_2_isr(void)
{
	uart_k20_isr(DEVICE_GET(uart_k20_2));
	_IntExit();
}

static void _uart_k20_3_isr(void)
{
	uart_k20_isr(DEVICE_GET(uart_k20_3));
	_IntExit();
}

static void _uart_k20_4_isr(void)
{
	uart_k20_isr(DEVICE_GET(uart_k20_4));
	_IntExit();
}
#endif /* CONFIG_CONSOLE_HANDLER */

#if defined(CONFIG_BLUETOOTH_UART)
static void _bt_uart_isr(void)
{
	bt_uart_isr(NULL);
	_IntExit();
}
#endif /* CONFIG_BLUETOOTH_UART */

/* placeholders: fill with real ISRs */
vth __irq_vector_table _irq_vector_table[CONFIG_NUM_IRQS] = {
	[0 ...(CONFIG_NUM_IRQS - 1)] = _irq_spurious,

#if defined(CONFIG_UART_INTERRUPT_DRIVEN)
	[CONFIG_UART_K20_PORT_0_IRQ] = _uart_k20_0_isr,
	[CONFIG_UART_K20_PORT_1_IRQ] = _uart_k20_1_isr,
	[CONFIG_UART_K20_PORT_2_IRQ] = _uart_k20_2_isr,
	[CONFIG_UART_K20_PORT_3_IRQ] = _uart_k20_3_isr,
	[CONFIG_UART_K20_PORT_4_IRQ] = _uart_k20_4_isr,
#endif
};

#endif /* CONFIG_SW_ISR_TABLE */
