/*
 * Copyright (c) 2016 Open-RnD Sp. z o.o.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file SoC configuration macros for the STM32F1 family processors.
 *
 * Based on reference manual:
 *   STM32F101xx, STM32F102xx, STM32F103xx, STM32F105xx and STM32F107xx
 *   advanced ARM(r)-based 32-bit MCUs
 *
 * Chapter 3.3: Memory Map
 */


#ifndef _STM32F1_SOC_H_
#define _STM32F1_SOC_H_

#ifndef _ASMLANGUAGE

#include <stm32f1xx.h>

/* Add include for DTS generated information */
#include <devicetree.h>

#ifdef CONFIG_EXTI_STM32
#include <stm32f1xx_ll_exti.h>
#endif

#ifdef CONFIG_SERIAL_HAS_DRIVER
#include <stm32f1xx_ll_usart.h>
#endif

#ifdef CONFIG_CLOCK_CONTROL_STM32_CUBE
#include <stm32f1xx_ll_utils.h>
#include <stm32f1xx_ll_bus.h>
#include <stm32f1xx_ll_rcc.h>
#include <stm32f1xx_ll_system.h>
#endif /* CONFIG_CLOCK_CONTROL_STM32_CUBE */

#ifdef CONFIG_I2C_STM32
#include <stm32f1xx_ll_i2c.h>
#endif

#ifdef CONFIG_SPI_STM32
#include <stm32f1xx_ll_spi.h>
#endif

#ifdef CONFIG_IWDG_STM32
#include <stm32f1xx_ll_iwdg.h>
#endif

#ifdef CONFIG_WWDG_STM32
#include <stm32f1xx_ll_wwdg.h>
#endif

#ifdef CONFIG_GPIO_STM32
#include <stm32f1xx_ll_gpio.h>
#endif

#ifdef CONFIG_ADC_STM32
#include <stm32f1xx_ll_adc.h>
#endif

#ifdef CONFIG_DMA_STM32
#include <stm32f1xx_ll_dma.h>
#endif

#ifdef CONFIG_HWINFO_STM32
#include <stm32f1xx_ll_utils.h>
#endif

#ifdef CONFIG_PWM_STM32
#include <stm32f1xx_ll_tim.h>
#endif /* CONFIG_PWM_STM32 */

#endif /* !_ASMLANGUAGE */

#endif /* _STM32F1_SOC_H_ */
