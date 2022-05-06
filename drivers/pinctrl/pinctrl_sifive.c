/*
 * Copyright (c) 2022 Antmicro <www.antmicro.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT sifive_pinctrl

#include <zephyr/devicetree.h>
#include <zephyr/drivers/pinctrl.h>
#include <soc.h>

#define PINCTRL_BASE_ADDR	DT_INST_REG_ADDR(0)
#define PINCTRL_IOF_EN		(PINCTRL_BASE_ADDR + 0x0)
#define PINCTRL_IOF_SEL		(PINCTRL_BASE_ADDR + 0x4)

static int pinctrl_sifive_set(uint32_t pin, uint32_t func)
{
	uint32_t val;

	if (func > SIFIVE_PINMUX_IOF1 || pin >= SIFIVE_PINMUX_PINS) {
		return -EINVAL;
	}

	val = sys_read32(PINCTRL_IOF_SEL);
	if (func == SIFIVE_PINMUX_IOF1) {
		val |= (SIFIVE_PINMUX_IOF1 << pin);
	} else {
		val &= ~(SIFIVE_PINMUX_IOF1 << pin);
	}
	sys_write32(val, PINCTRL_IOF_SEL);

	/* Enable IO function for this pin */
	val = sys_read32(PINCTRL_IOF_EN);
	val |= BIT(pin);
	sys_write32(val, PINCTRL_IOF_EN);

	return 0;
}


int pinctrl_configure_pins(const pinctrl_soc_pin_t *pins, uint8_t pin_cnt, uintptr_t reg)
{
	ARG_UNUSED(reg);
	int i;

	for (i = 0; i < pin_cnt; i++) {
		pinctrl_sifive_set(pins[i].pin, pins[i].iof);
	}

	return 0;
}
