/*
 * Copyright (c) 2016 Open-RnD Sp. z o.o.
 * Copyright (c) 2016 BayLibre, SAS
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <drivers/pinmux.h>
#include <sys/sys_io.h>

#include <pinmux/stm32/pinmux_stm32.h>

/* pin assignments for NUCLEO-L476RG board */
static const struct pin_config pinconf[] = {
#if DT_NODE_HAS_STATUS(DT_NODELABEL(spi1), okay) && CONFIG_SPI
	/* SPI1 on the Arduino connectors pins A2, D3, D12, D11 */
#ifdef CONFIG_SPI_STM32_USE_HW_SS
	{STM32_PIN_PA4, STM32L4X_PINMUX_FUNC_PA4_SPI1_NSS},
#endif /* CONFIG_SPI_STM32_USE_HW_SS */
	/* SPI1_SCK should output on PA5, but is used for LD2 */
	{STM32_PIN_PB3, STM32L4X_PINMUX_FUNC_PB3_SPI1_SCK},
	{STM32_PIN_PA6, STM32L4X_PINMUX_FUNC_PA6_SPI1_MISO},
	{STM32_PIN_PA7, STM32L4X_PINMUX_FUNC_PA7_SPI1_MOSI},
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(spi2), okay) && CONFIG_SPI
	/* SPI2 on the ST Morpho Connector CN10 pins 16, 30, 28, 26*/
#ifdef CONFIG_SPI_STM32_USE_HW_SS
	{STM32_PIN_PB12, STM32L4X_PINMUX_FUNC_PB12_SPI2_NSS},
#endif /* CONFIG_SPI_STM32_USE_HW_SS */
	{STM32_PIN_PB13, STM32L4X_PINMUX_FUNC_PB13_SPI2_SCK},
	{STM32_PIN_PB14, STM32L4X_PINMUX_FUNC_PB14_SPI2_MISO},
	{STM32_PIN_PB15, STM32L4X_PINMUX_FUNC_PB15_SPI2_MOSI},
#endif
#if DT_NODE_HAS_STATUS(DT_NODELABEL(spi3), okay) && CONFIG_SPI
	/* SPI3 on the ST Morpho Connector CN7 pins 17, 1, 2, 3*/
#ifdef CONFIG_SPI_STM32_USE_HW_SS
	{STM32_PIN_PA15, STM32L4X_PINMUX_FUNC_PA15_SPI3_NSS},
#endif /* CONFIG_SPI_STM32_USE_HW_SS */
	{STM32_PIN_PC10, STM32L4X_PINMUX_FUNC_PC10_SPI3_SCK},
	{STM32_PIN_PC11, STM32L4X_PINMUX_FUNC_PC11_SPI3_MISO},
	{STM32_PIN_PC12, STM32L4X_PINMUX_FUNC_PC12_SPI3_MOSI},
#endif
};

static int pinmux_stm32_init(const struct device *port)
{
	ARG_UNUSED(port);

	stm32_setup_pins(pinconf, ARRAY_SIZE(pinconf));

	return 0;
}

SYS_INIT(pinmux_stm32_init, PRE_KERNEL_1,
	 CONFIG_PINMUX_STM32_DEVICE_INITIALIZATION_PRIORITY);
