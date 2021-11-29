/*
 * Copyright (c) 2016 Linaro Limited
 * Copyright (c) 2021 Yonatan Schachter
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file SoC configuration macros for the Raspberry Pi RP2040 family processors
 */

#ifndef _RPI_PICO_RP2040_SOC_H_
#define _RPI_PICO_RP2040_SOC_H_

#include <autoconf.h>

#define __VTOR_PRESENT CONFIG_CPU_CORTEX_M_HAS_VTOR
#define __MPU_PRESENT CONFIG_CPU_HAS_ARM_MPU

#endif /* _RPI_PICO_RP2040_SOC_H_ */
