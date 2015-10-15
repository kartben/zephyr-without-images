/*
 * Copyright (c) 2015 Intel Corporation.
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
 * @file Header file for ns16550 UART driver
 */

#ifndef _DRIVERS_UART_NS16550_H_
#define _DRIVERS_UART_NS16550_H_

#include <uart.h>

/** Device data structure */
struct uart_ns16550_dev_data_t {
	uint8_t iir_cache;	/**< cache of IIR since it clears when read */
};

void ns16550_uart_port_init(struct device *,
			    const struct uart_init_info * const);

#endif /* _DRIVERS_UART_NS16550_H_ */
