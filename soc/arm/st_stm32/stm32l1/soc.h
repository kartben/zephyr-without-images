/*
 * Copyright (c) 2019 Linaro Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file SoC configuration macros for the STM32L1 family processors.
 *
 * Based on reference manual:
 *   STM32L1X advanced ARM ® -based 32-bit MCUs
 *
 * Chapter 2.2: Memory organization
 */


#ifndef _STM32L1_SOC_H_
#define _STM32L1_SOC_H_

#ifndef _ASMLANGUAGE

#include <stm32l1xx.h>

/* ARM CMSIS definitions must be included before kernel_includes.h.
 * Therefore, it is essential to include kernel_includes.h after including
 * core SOC-specific headers.
 */
#include <kernel_includes.h>

#include <stm32l1xx_ll_system.h>

#ifdef CONFIG_CLOCK_CONTROL_STM32_CUBE
#include <stm32l1xx_ll_utils.h>
#include <stm32l1xx_ll_bus.h>
#include <stm32l1xx_ll_rcc.h>
#endif /* CONFIG_CLOCK_CONTROL_STM32_CUBE */

#endif /* !_ASMLANGUAGE */

#endif /* _STM32L1_SOC_H_ */
