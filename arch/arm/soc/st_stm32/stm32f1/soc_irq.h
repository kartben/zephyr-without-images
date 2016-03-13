/*
 * Copyright (c) 2016 Open-RnD Sp. z o.o.
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
 * @file Interrupt numbers for STM32F1 family processors.
 *
 * Based on reference manual:
 *   STM32F101xx, STM32F102xx, STM32F103xx, STM32F105xx and STM32F107xx
 *   advanced ARM ® -based 32-bit MCUs
 *
 * Chapter 10.1.2: Interrupt and exception vectors
 */


#ifndef _STM32F1_SOC_IRQ_H_
#define _STM32F1_SOC_IRQ_H_

#define STM32F1_IRQ_WWDG		0
#define STM32F1_IRQ_PVD		1
#define STM32F1_IRQ_TAMPER		2
#define STM32F1_IRQ_RTC		3
#define STM32F1_IRQ_FLAGS		4
#define STM32F1_IRQ_RCC		5
#define STM32F1_IRQ_EXTI0		6
#define STM32F1_IRQ_EXTI1		7
#define STM32F1_IRQ_EXTI2		8
#define STM32F1_IRQ_EXTI3		9
#define STM32F1_IRQ_EXTI4		10
#define STM32F1_IRQ_DMA1_CH1		11
#define STM32F1_IRQ_DMA1_CH2		12
#define STM32F1_IRQ_DMA1_CH3		13
#define STM32F1_IRQ_DMA1_CH4		14
#define STM32F1_IRQ_DMA1_CH5		15
#define STM32F1_IRQ_DMA1_CH6		16
#define STM32F1_IRQ_DMA1_CH7		17
#define STM32F1_IRQ_ADC1_2		18
#define STM32F1_IRQ_USB_HP_CAN_TX	19
#define STM32F1_IRQ_USB_LP_CAN_RX0	20
#define STM32F1_IRQ_CAN_RX1		21
#define STM32F1_IRQ_CAN_SCE		22
#define STM32F1_IRQ_EXTI9_5		23
#define STM32F1_IRQ_TIM1_BRK		24
#define STM32F1_IRQ_TIM1_UP		25
#define STM32F1_IRQ_TIM1_TRG_COM	26
#define STM32F1_IRQ_TIM1_CC		27
#define STM32F1_IRQ_TIM2		28
#define STM32F1_IRQ_TIM3		29
#define STM32F1_IRQ_TIM4		30
#define STM32F1_IRQ_I2C1_EV		31
#define STM32F1_IRQ_I2C1_ER		32
#define STM32F1_IRQ_I2C2_EV		33
#define STM32F1_IRQ_I2C2_ER		34
#define STM32F1_IRQ_SPI1		35
#define STM32F1_IRQ_SPI2		36
#define STM32F1_IRQ_USART1		37
#define STM32F1_IRQ_USART2		38
#define STM32F1_IRQ_USART3		39
#define STM32F1_IRQ_EXTI15_10		40
#define STM32F1_IRQ_RTC_ALARM		41
#define STM32F1_IRQ_USB_WAKEUP		42
#define STM32F1_IRQ_OTG_FS_WKUP	STM32F1_IRQ_USB_WAKEUP
#define STM32F1_IRQ_TIM8_BRK		43
#define STM32F1_IRQ_TIM8_UP		44
#define STM32F1_IRQ_TIM8_TRG_COM	45
#define STM32F1_IRQ_TIM8_CC		46
#define STM32F1_IRQ_ADC3		47
#define STM32F1_IRQ_FSMC		48
#define STM32F1_IRQ_SDIO		49
#define STM32F1_IRQ_TIM5		50
#define STM32F1_IRQ_SPI3		51
#define STM32F1_IRQ_UART4		52
#define STM32F1_IRQ_UART5		53
#define STM32F1_IRQ_TIM6		54
#define STM32F1_IRQ_TIM7		55
#define STM32F1_IRQ_DMA2_CH1		56
#define STM32F1_IRQ_DMA2_CH2		57
#define STM32F1_IRQ_DMA2_CH3		58
#define STM32F1_IRQ_DMA2_CH4_5		59
/* IRQs below this point are available on connectivity line
 * devices only
 */
#define STM32F1_IRQ_DMA2_CH4		STM32F1_IRQ_DMA2_CH4_5
#define STM32F1_IRQ_DMA2_CH5		60
#define STM32F1_IRQ_ETH		61
#define STM32F1_IRQ_ETH_WKUP		62
#define STM32F1_IRQ_CAN2_TX		63
#define STM32F1_IRQ_CAN2_RX0		64
#define STM32F1_IRQ_CAN2_RX1		65
#define STM32F1_IRQ_CAN2_SCE		66
#define STM32F1_IRQ_OTG_FS		67

#endif	/* _STM32F1_SOC_IRQ_H_ */
