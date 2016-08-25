/*
 * Copyright (c) 2016 Linaro Limited
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
 * @file SoC configuration macros for the Nordic nRF51 family processors.
 */

#ifndef _NORDICSEMI_NRF51_SOC_H_
#define _NORDICSEMI_NRF51_SOC_H_

#ifndef _ASMLANGUAGE

#include <nrf5_common.h>
#include <nrf.h>
#include <device.h>
#include <misc/util.h>
#include <drivers/rand32.h>

#endif /* !_ASMLANGUAGE */

#define NRF51_POWER_RAMON_ADDRESS              0x40000524
#define NRF51_POWER_RAMONB_ADDRESS             0x40000554
#define NRF51_POWER_RAMONx_RAMxON_ONMODE_Msk   0x3

#endif /* _NORDICSEMI_NRF51_SOC_H_ */
