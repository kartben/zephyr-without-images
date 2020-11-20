/*
 * Copyright (c) 2019 Philippe Retornaz <philippe@shapescale.com>
 * Copyright (c) 2019 STMicroelectronics
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file SoC configuration macros for the STM32G0 family processors.
 *
 * Based on reference manual:
 *   STM32G0X advanced ARM ® -based 32-bit MCUs
 *
 * Chapter 2.2: Memory organization
 */


#ifndef _STM32G0_SOC_H_
#define _STM32G0_SOC_H_

#include <sys/util.h>

#ifndef _ASMLANGUAGE

#include <stm32g0xx.h>

/* Add include for DTS generated information */
#include <st_stm32_dt.h>

#include <stm32g0xx_ll_system.h>

#ifdef CONFIG_CLOCK_CONTROL_STM32_CUBE
#include <stm32g0xx_ll_utils.h>
#include <stm32g0xx_ll_bus.h>
#include <stm32g0xx_ll_rcc.h>
#endif /* CONFIG_CLOCK_CONTROL_STM32_CUBE */

#ifdef CONFIG_EXTI_STM32
#include <stm32g0xx_ll_exti.h>
#endif

/* Add include for DTS generated information */
#include <devicetree.h>

#endif /* !_ASMLANGUAGE */

#endif /* _STM32G0_SOC_H_ */
