/*
 * Copyright (c) 2016 Open-RnD Sp. z o.o.
 * Copyright (c) 2016 BayLibre, SAS
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _STM32L4X_CLOCK_CONTROL_H_
#define _STM32L4X_CLOCK_CONTROL_H_

/**
 * @file
 *
 * @brief Clock subsystem IDs for STM32L4 family
 */

enum {
	STM32L4X_CLOCK_AHB1_BASE     = 0,
	STM32L4X_CLOCK_AHB2_BASE,
	STM32L4X_CLOCK_AHB3_BASE,
	STM32L4X_CLOCK_APB1_1_BASE,
	STM32L4X_CLOCK_APB1_2_BASE,
	STM32L4X_CLOCK_APB2_BASE,
	STM32L4X_CLOCK_BASE_COUNT,
};

#define STM32L4X_CLOCK_ID(_base, id) \
	((STM32L4X_CLOCK_##_base##_BASE << 16) + id)

#define STM32L4X_CLOCK_BASE(num)	((num) >> 16)
#define STM32L4X_CLOCK_BIT(num)		((num) & 0xFFFF)

enum {
	/* AHB1 */
	STM32L4X_CLOCK_SUBSYS_DMA1	= STM32L4X_CLOCK_ID(AHB1, 0),
	STM32L4X_CLOCK_SUBSYS_DMA2	= STM32L4X_CLOCK_ID(AHB1, 1),
	STM32L4X_CLOCK_SUBSYS_FLASH	= STM32L4X_CLOCK_ID(AHB1, 8),
	STM32L4X_CLOCK_SUBSYS_CRC	= STM32L4X_CLOCK_ID(AHB1, 12),
	STM32L4X_CLOCK_SUBSYS_TSC	= STM32L4X_CLOCK_ID(AHB1, 16),

	/* AHB2 */
	STM32L4X_CLOCK_SUBSYS_GPIOA	= STM32L4X_CLOCK_ID(AHB2, 0),
	STM32L4X_CLOCK_SUBSYS_GPIOB	= STM32L4X_CLOCK_ID(AHB2, 1),
	STM32L4X_CLOCK_SUBSYS_GPIOC	= STM32L4X_CLOCK_ID(AHB2, 2),
	STM32L4X_CLOCK_SUBSYS_GPIOD	= STM32L4X_CLOCK_ID(AHB2, 3),
	STM32L4X_CLOCK_SUBSYS_GPIOE	= STM32L4X_CLOCK_ID(AHB2, 4),
	STM32L4X_CLOCK_SUBSYS_GPIOF	= STM32L4X_CLOCK_ID(AHB2, 5),
	STM32L4X_CLOCK_SUBSYS_GPIOG	= STM32L4X_CLOCK_ID(AHB2, 6),
	STM32L4X_CLOCK_SUBSYS_GPIOH	= STM32L4X_CLOCK_ID(AHB2, 7),
	STM32L4X_CLOCK_SUBSYS_OTGFS	= STM32L4X_CLOCK_ID(AHB2, 12),
	STM32L4X_CLOCK_SUBSYS_ADC	= STM32L4X_CLOCK_ID(AHB2, 13),
	STM32L4X_CLOCK_SUBSYS_AES	= STM32L4X_CLOCK_ID(AHB2, 16),
	STM32L4X_CLOCK_SUBSYS_RNG	= STM32L4X_CLOCK_ID(AHB2, 18),

	/* AHB3 */
	STM32L4X_CLOCK_SUBSYS_FMC	= STM32L4X_CLOCK_ID(AHB3, 0),
	STM32L4X_CLOCK_SUBSYS_QSPI	= STM32L4X_CLOCK_ID(AHB3, 0),

	/* APB1 */
	STM32L4X_CLOCK_SUBSYS_TIM2	= STM32L4X_CLOCK_ID(APB1_1, 0),
	STM32L4X_CLOCK_SUBSYS_TIM3	= STM32L4X_CLOCK_ID(APB1_1, 1),
	STM32L4X_CLOCK_SUBSYS_TIM4	= STM32L4X_CLOCK_ID(APB1_1, 2),
	STM32L4X_CLOCK_SUBSYS_TIM5	= STM32L4X_CLOCK_ID(APB1_1, 3),
	STM32L4X_CLOCK_SUBSYS_TIM6	= STM32L4X_CLOCK_ID(APB1_1, 4),
	STM32L4X_CLOCK_SUBSYS_TIM7	= STM32L4X_CLOCK_ID(APB1_1, 5),
	STM32L4X_CLOCK_SUBSYS_LCD	= STM32L4X_CLOCK_ID(APB1_1, 9),
	STM32L4X_CLOCK_SUBSYS_WWDG	= STM32L4X_CLOCK_ID(APB1_1, 11),
	STM32L4X_CLOCK_SUBSYS_SPI2	= STM32L4X_CLOCK_ID(APB1_1, 14),
	STM32L4X_CLOCK_SUBSYS_SPI3	= STM32L4X_CLOCK_ID(APB1_1, 15),
	STM32L4X_CLOCK_SUBSYS_USART2	= STM32L4X_CLOCK_ID(APB1_1, 17),
	STM32L4X_CLOCK_SUBSYS_USART3	= STM32L4X_CLOCK_ID(APB1_1, 18),
	STM32L4X_CLOCK_SUBSYS_UART4	= STM32L4X_CLOCK_ID(APB1_1, 19),
	STM32L4X_CLOCK_SUBSYS_UART5	= STM32L4X_CLOCK_ID(APB1_1, 20),
	STM32L4X_CLOCK_SUBSYS_I2C1	= STM32L4X_CLOCK_ID(APB1_1, 21),
	STM32L4X_CLOCK_SUBSYS_I2C2	= STM32L4X_CLOCK_ID(APB1_1, 22),
	STM32L4X_CLOCK_SUBSYS_I2C3	= STM32L4X_CLOCK_ID(APB1_1, 23),
	STM32L4X_CLOCK_SUBSYS_PWR	= STM32L4X_CLOCK_ID(APB1_1, 28),
	STM32L4X_CLOCK_SUBSYS_DAC	= STM32L4X_CLOCK_ID(APB1_1, 29),
	STM32L4X_CLOCK_SUBSYS_OPAMP	= STM32L4X_CLOCK_ID(APB1_1, 30),
	STM32L4X_CLOCK_SUBSYS_LPTIM1	= STM32L4X_CLOCK_ID(APB1_1, 31),
	STM32L4X_CLOCK_SUBSYS_LPUART1	= STM32L4X_CLOCK_ID(APB1_2, 0),
	STM32L4X_CLOCK_SUBSYS_SWPMI1	= STM32L4X_CLOCK_ID(APB1_2, 2),
	STM32L4X_CLOCK_SUBSYS_LPTIM2	= STM32L4X_CLOCK_ID(APB1_2, 5),

	/* APB2 */
	STM32L4X_CLOCK_SUBSYS_SYSCFG	= STM32L4X_CLOCK_ID(APB2, 0),
	STM32L4X_CLOCK_SUBSYS_FW	= STM32L4X_CLOCK_ID(APB2, 7),
	STM32L4X_CLOCK_SUBSYS_SDMMC1	= STM32L4X_CLOCK_ID(APB2, 10),
	STM32L4X_CLOCK_SUBSYS_TIM1	= STM32L4X_CLOCK_ID(APB2, 11),
	STM32L4X_CLOCK_SUBSYS_SPI1	= STM32L4X_CLOCK_ID(APB2, 12),
	STM32L4X_CLOCK_SUBSYS_TIM8	= STM32L4X_CLOCK_ID(APB2, 13),
	STM32L4X_CLOCK_SUBSYS_USART1	= STM32L4X_CLOCK_ID(APB2, 14),
	STM32L4X_CLOCK_SUBSYS_TIM15	= STM32L4X_CLOCK_ID(APB2, 16),
	STM32L4X_CLOCK_SUBSYS_TIM16	= STM32L4X_CLOCK_ID(APB2, 17),
	STM32L4X_CLOCK_SUBSYS_TIM17	= STM32L4X_CLOCK_ID(APB2, 18),
	STM32L4X_CLOCK_SUBSYS_SAI1	= STM32L4X_CLOCK_ID(APB2, 21),
	STM32L4X_CLOCK_SUBSYS_SAI2	= STM32L4X_CLOCK_ID(APB2, 22),
	STM32L4X_CLOCK_SUBSYS_DFSDM1	= STM32L4X_CLOCK_ID(APB2, 24),

};

#endif /* _STM32L4_CLOCK_CONTROL_H_ */
