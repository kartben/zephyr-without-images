/*
 * Copyright (c) 2019 Roland Ma
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <drivers/pinmux.h>
#include <sys/sys_io.h>

#include <pinmux/stm32/pinmux_stm32.h>

/* NUCLEO-F767ZI pin configurations */
static const struct pin_config pinconf[] = {
#ifdef CONFIG_USB_DC_STM32
	{ STM32_PIN_PA11, STM32F7_PINMUX_FUNC_PA11_OTG_FS_DM },
	{ STM32_PIN_PA12, STM32F7_PINMUX_FUNC_PA12_OTG_FS_DP },
#endif	/* CONFIG_USB_DC_STM32 */
};

static int pinmux_stm32_init(const struct device *port)
{
	ARG_UNUSED(port);

	stm32_setup_pins(pinconf, ARRAY_SIZE(pinconf));

	return 0;
}

SYS_INIT(pinmux_stm32_init, PRE_KERNEL_1,
	 CONFIG_PINMUX_STM32_DEVICE_INITIALIZATION_PRIORITY);
