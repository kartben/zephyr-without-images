/*
 * Copyright (c) 2016 Open-RnD Sp. z o.o.
 *           (c) 2016 Linaro Limited.
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
#ifndef _STM32F4_CLOCK_CONTROL_H_
#define _STM32F4_CLOCK_CONTROL_H_

/**
 * @file
 *
 * @brief Clock subsystem IDs for STM32F4 family
 */

/* Bus */
enum {
	STM32F4X_CLOCK_BUS_AHB1,
	STM32F4X_CLOCK_BUS_AHB2,
	STM32F4X_CLOCK_BUS_APB1,
	STM32F4X_CLOCK_BUS_APB2,
};

/* AHB1 pins */
enum {
	/* AHB1 */
	STM32F4X_CLOCK_ENABLE_GPIOA      = 1 << 0,
	STM32F4X_CLOCK_ENABLE_GPIOB      = 1 << 1,
	STM32F4X_CLOCK_ENABLE_GPIOC      = 1 << 2,
	STM32F4X_CLOCK_ENABLE_GPIOD      = 1 << 3,
	STM32F4X_CLOCK_ENABLE_GPIOE      = 1 << 4,
	STM32F4X_CLOCK_ENABLE_GPIOF      = 1 << 5,
	STM32F4X_CLOCK_ENABLE_GPIOG      = 1 << 6,
	STM32F4X_CLOCK_ENABLE_GPIOH      = 1 << 7,
	STM32F4X_CLOCK_ENABLE_GPIOI      = 1 << 8,
	STM32F4X_CLOCK_ENABLE_GPIOJ      = 1 << 9,
	STM32F4X_CLOCK_ENABLE_GPIOK      = 1 << 10,
	STM32F4X_CLOCK_ENABLE_CRC        = 1 << 12,
	STM32F4X_CLOCK_ENABLE_BKPSRAM    = 1 << 14,
	STM32F4X_CLOCK_ENABLE_CCMDATARAM = 1 << 16,
	STM32F4X_CLOCK_ENABLE_DMA1       = 1 << 21,
	STM32F4X_CLOCK_ENABLE_DMA2       = 1 << 22,
	STM32F4X_CLOCK_ENABLE_ETHMAC     = 1 << 25,
	STM32F4X_CLOCK_ENABLE_ETHMACTX   = 1 << 26,
	STM32F4X_CLOCK_ENABLE_ETHMACRX   = 1 << 27,
	STM32F4X_CLOCK_ENABLE_ETHMACPTP  = 1 << 28,
	STM32F4X_CLOCK_ENABLE_OTGHS      = 1 << 29,
	STM32F4X_CLOCK_ENABLE_OTGHSULPI  = 1 << 30,
};

/* AHB2 pins */
enum {
	STM32F4X_CLOCK_ENABLE_DCMI       = 1 << 0,
	STM32F4X_CLOCK_ENABLE_CRYP       = 1 << 4,
	STM32F4X_CLOCK_ENABLE_HASH       = 1 << 5,
	STM32F4X_CLOCK_ENABLE_RNG        = 1 << 6,
	STM32F4X_CLOCK_ENABLE_OTGFS      = 1 << 7,
};

/* APB1 pins */
enum {
	STM32F4X_CLOCK_ENABLE_TIM2   = 1 << 0,
	STM32F4X_CLOCK_ENABLE_TIM3   = 1 << 1,
	STM32F4X_CLOCK_ENABLE_TIM4   = 1 << 2,
	STM32F4X_CLOCK_ENABLE_TIM5   = 1 << 3,
	STM32F4X_CLOCK_ENABLE_TIM6   = 1 << 4,
	STM32F4X_CLOCK_ENABLE_TIM7   = 1 << 5,
	STM32F4X_CLOCK_ENABLE_TIM12  = 1 << 6,
	STM32F4X_CLOCK_ENABLE_TIM13  = 1 << 7,
	STM32F4X_CLOCK_ENABLE_TIM14  = 1 << 8,
	STM32F4X_CLOCK_ENABLE_WWDG   = 1 << 11,
	STM32F4X_CLOCK_ENABLE_SPI2   = 1 << 14,
	STM32F4X_CLOCK_ENABLE_SPI3   = 1 << 15,
	STM32F4X_CLOCK_ENABLE_USART2 = 1 << 17,
	STM32F4X_CLOCK_ENABLE_USART3 = 1 << 18,
	STM32F4X_CLOCK_ENABLE_UART4  = 1 << 19,
	STM32F4X_CLOCK_ENABLE_UART5  = 1 << 20,
	STM32F4X_CLOCK_ENABLE_I2C1   = 1 << 21,
	STM32F4X_CLOCK_ENABLE_I2C2   = 1 << 22,
	STM32F4X_CLOCK_ENABLE_I2C3   = 1 << 23,
	STM32F4X_CLOCK_ENABLE_CAN1   = 1 << 25,
	STM32F4X_CLOCK_ENABLE_CAN2   = 1 << 26,
	STM32F4X_CLOCK_ENABLE_PWR    = 1 << 28,
	STM32F4X_CLOCK_ENABLE_DAC    = 1 << 29,
	STM32F4X_CLOCK_ENABLE_UART7  = 1 << 30,
	STM32F4X_CLOCK_ENABLE_UART8  = 1 << 31,
};

/* APB2 pins */
enum {
	STM32F4X_CLOCK_ENABLE_TIM1   = 1 << 0,
	STM32F4X_CLOCK_ENABLE_TIM8   = 1 << 1,
	STM32F4X_CLOCK_ENABLE_USART1 = 1 << 4,
	STM32F4X_CLOCK_ENABLE_USART6 = 1 << 5,
	STM32F4X_CLOCK_ENABLE_ADC    = 1 << 8,
	STM32F4X_CLOCK_ENABLE_SDIO   = 1 << 11,
	STM32F4X_CLOCK_ENABLE_SPI1   = 1 << 12,
	STM32F4X_CLOCK_ENABLE_SPI4   = 1 << 13,
	STM32F4X_CLOCK_ENABLE_SYSCFG = 1 << 14,
	STM32F4X_CLOCK_ENABLE_TIM9   = 1 << 16,
	STM32F4X_CLOCK_ENABLE_TIM10  = 1 << 17,
	STM32F4X_CLOCK_ENABLE_TIM11  = 1 << 18,
	STM32F4X_CLOCK_ENABLE_SPI5   = 1 << 20,
	STM32F4X_CLOCK_ENABLE_SPI6   = 1 << 21,
	STM32F4X_CLOCK_ENABLE_SAI1   = 1 << 22,
	STM32F4X_CLOCK_ENABLE_LTDC   = 1 << 26,
	STM32F4X_CLOCK_ENABLE_DSI    = 1 << 27,
};

struct stm32f4x_pclken {
	uint32_t bus;
	uint32_t enr;
};

#endif /* _STM32F4_CLOCK_CONTROL_H_ */
