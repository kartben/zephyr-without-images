/*
 * Copyright (c) 2016, Wind River Systems, Inc.
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
 * @file Header file for the Freescale K64 GPIO module.
 */

#ifndef _GPIO_K64_H_
#define _GPIO_K64_H_

#include <nanokernel.h>

#include <gpio.h>

/* GPIO Port Register offsets */

#define GPIO_K64_DATA_OUT_OFFSET	0x00  /* Port Data Output Reg. offset */
#define GPIO_K64_SET_OUT_OFFSET		0x04  /* Port Set Output Reg. offset */
#define GPIO_K64_CLR_OUT_OFFSET		0x08  /* Port Clear Output Reg. offset */
#define GPIO_K64_TOGGLE_OUT_OFFSET	0x0C  /* Port Toggle Output  Reg. offset */
#define GPIO_K64_DATA_IN_OFFSET		0x10  /* Port Data Input Reg. offset */
#define GPIO_K64_DIR_OFFSET			0x14  /* Port Data Direction Reg. offset */


/** Configuration data */
struct gpio_k64_config {
	/* base address */
	uint32_t base_addr;
};

#endif /* _GPIO_K64_H_ */
