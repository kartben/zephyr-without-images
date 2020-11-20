/*
 * Copyright (c) 2019 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file SoC configuration macros for the STM32WB family processors.
 *
 * Based on reference manual:
 *   TODO: Provide reference when known
 *
 * Chapter 2.2.2: Memory map and register boundary addresses
 */


#ifndef _STM32WBX_SOC_H_
#define _STM32WBX_SOC_H_

#include <sys/util.h>

#ifndef _ASMLANGUAGE

#include <stm32wbxx.h>

/* Add include for DTS generated information */
#include <st_stm32_dt.h>

#endif /* !_ASMLANGUAGE */

#endif /* _STM32WBX_SOC_H_ */
