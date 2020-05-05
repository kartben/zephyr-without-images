/*
 * Copyright (c) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <drivers/pinmux.h>
#include <sys/sys_io.h>

#include <pinmux/stm32/pinmux_stm32.h>

/* pin assignment for black_f407zg_pro board */
static const struct pin_config pinconf[] = {
#if DT_HAS_NODE_STATUS_OKAY(DT_NODELABEL(usart1))
	{STM32_PIN_PB6, STM32F4_PINMUX_FUNC_PB6_USART1_TX},
	{STM32_PIN_PB7, STM32F4_PINMUX_FUNC_PB7_USART1_RX},
#endif
#if DT_HAS_NODE_STATUS_OKAY(DT_NODELABEL(usart2))
	{STM32_PIN_PA2, STM32F4_PINMUX_FUNC_PA2_USART2_TX},
	{STM32_PIN_PA3, STM32F4_PINMUX_FUNC_PA3_USART2_RX},
#endif
#if DT_HAS_NODE_STATUS_OKAY(DT_NODELABEL(pwm2))
	{STM32_PIN_PA0, STM32F4_PINMUX_FUNC_PA0_PWM2_CH1},
#endif
#ifdef CONFIG_USB_DC_STM32
	{STM32_PIN_PA11, STM32F4_PINMUX_FUNC_PA11_OTG_FS_DM},
	{STM32_PIN_PA12, STM32F4_PINMUX_FUNC_PA12_OTG_FS_DP},
#endif	/* CONFIG_USB_DC_STM32 */
#if DT_HAS_NODE_STATUS_OKAY(DT_NODELABEL(can1))
	{STM32_PIN_PD0, STM32F4_PINMUX_FUNC_PD0_CAN1_RX},
	{STM32_PIN_PD1, STM32F4_PINMUX_FUNC_PD1_CAN1_TX},
#endif
#if DT_HAS_NODE_STATUS_OKAY(DT_NODELABEL(can2))
	{STM32_PIN_PB12, STM32F4_PINMUX_FUNC_PB12_CAN2_RX},
	{STM32_PIN_PB13, STM32F4_PINMUX_FUNC_PB13_CAN2_TX},
#endif
#if DT_HAS_NODE_STATUS_OKAY(DT_NODELABEL(spi1))
	{STM32_PIN_PB3, STM32F4_PINMUX_FUNC_PB3_SPI1_SCK},
	{STM32_PIN_PB4, STM32F4_PINMUX_FUNC_PB4_SPI1_MISO},
	{STM32_PIN_PB5, STM32F4_PINMUX_FUNC_PB5_SPI1_MOSI},
#endif
#if DT_HAS_NODE_STATUS_OKAY(DT_NODELABEL(spi2))
	{STM32_PIN_PB10, STM32F4_PINMUX_FUNC_PB10_SPI2_SCK},
	{STM32_PIN_PC2, STM32F4_PINMUX_FUNC_PC2_SPI2_MISO},
	{STM32_PIN_PC3, STM32F4_PINMUX_FUNC_PC3_SPI2_MOSI},
#endif
};


static int pinmux_black_f407zg_init(struct device *port)
{
	ARG_UNUSED(port);

	stm32_setup_pins(pinconf, ARRAY_SIZE(pinconf));

	return 0;
}

SYS_INIT(pinmux_black_f407zg_init, PRE_KERNEL_1,
	 CONFIG_PINMUX_STM32_DEVICE_INITIALIZATION_PRIORITY);
