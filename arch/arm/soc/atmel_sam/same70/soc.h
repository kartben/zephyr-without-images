/*
 * Copyright (c) 2016 Piotr Mienkowski
 * SPDX-License-Identifier: Apache-2.0
 */

/** @file
 * @brief Register access macros for the Atmel SAM E70 MCU.
 *
 * This file provides register access macros for the Atmel SAM E70 MCU, HAL
 * drivers for core peripherals as well as symbols specific to Atmel SAM family.
 */

#ifndef _ATMEL_SAME70_SOC_H_
#define _ATMEL_SAME70_SOC_H_

#ifndef _ASMLANGUAGE

#define DONT_USE_CMSIS_INIT
#define DONT_USE_PREDEFINED_CORE_HANDLERS
#define DONT_USE_PREDEFINED_PERIPHERALS_HANDLERS

#if defined CONFIG_SOC_PART_NUMBER_SAME70J19
#include <same70j19.h>
#elif defined CONFIG_SOC_PART_NUMBER_SAME70J20
#include <same70j20.h>
#elif defined CONFIG_SOC_PART_NUMBER_SAME70J21
#include <same70j21.h>
#elif defined CONFIG_SOC_PART_NUMBER_SAME70N19
#include <same70n19.h>
#elif defined CONFIG_SOC_PART_NUMBER_SAME70N20
#include <same70n20.h>
#elif defined CONFIG_SOC_PART_NUMBER_SAME70N21
#include <same70n21.h>
#elif defined CONFIG_SOC_PART_NUMBER_SAME70Q19
#include <same70q19.h>
#elif defined CONFIG_SOC_PART_NUMBER_SAME70Q20
#include <same70q20.h>
#elif defined CONFIG_SOC_PART_NUMBER_SAME70Q21
#include <same70q21.h>
#else
  #error Library does not support the specified device.
#endif

#include "soc_pinmap.h"

#include "../common/soc_pmc.h"
#include "../common/soc_gpio.h"

#endif /* _ASMLANGUAGE */

/** Processor Clock (HCLK) Frequency */
#define SOC_ATMEL_SAM_HCLK_FREQ_HZ CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC
/** Master Clock (MCK) Frequency */
#define SOC_ATMEL_SAM_MCK_FREQ_HZ \
		(SOC_ATMEL_SAM_HCLK_FREQ_HZ / CONFIG_SOC_ATMEL_SAME70_MDIV)

#endif /* _ATMEL_SAME70_SOC_H_ */
