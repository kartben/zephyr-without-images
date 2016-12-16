/* cc2520_frdm_k64f.c - FRDK K64F setup for cc2520 */

/*
 * Copyright (c) 2016 Intel Corporation
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

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <pinmux.h>
#include <pinmux/pinmux.h>
#include <pinmux/k64/pinmux.h>

#include <ieee802154/cc2520.h>
#include <gpio.h>

#define CC2520_GPIO_DEV_NAME CONFIG_GPIO_K64_C_DEV_NAME

#define CC2520_GPIO_VREG_EN	12  /* PTC12 */
#define CC2520_GPIO_RESET	3   /* PTC3 */
#define CC2520_GPIO_FIFO	2   /* PTC2 */
#define CC2520_GPIO_CCA		17  /* PTC17 */
#define CC2520_GPIO_SFD		16  /* PTC16 */
#define CC2520_GPIO_FIFOP	4   /* PTC4 */

static struct cc2520_gpio_configuration cc2520_gpios[CC2520_GPIO_IDX_MAX] = {
	{ .dev = NULL, .pin = CC2520_GPIO_VREG_EN, },
	{ .dev = NULL, .pin = CC2520_GPIO_RESET, },
	{ .dev = NULL, .pin = CC2520_GPIO_FIFO, },
	{ .dev = NULL, .pin = CC2520_GPIO_CCA, },
	{ .dev = NULL, .pin = CC2520_GPIO_SFD, },
	{ .dev = NULL, .pin = CC2520_GPIO_FIFOP, },
};

/* CONFIG_PINMUX_INIT_PRIORITY + 1 ! */
#define CC2520_PINMUX_PRIORITY 46

/* PTC<2/3/4> are by default set on GPIO function */
static const struct pin_config cc2520_mux_config[] = {
	{ K64_PIN_PTC12, K64_PINMUX_FUNC_GPIO },
	{ K64_PIN_PTC16, K64_PINMUX_FUNC_GPIO },
	{ K64_PIN_PTC17, K64_PINMUX_FUNC_GPIO },
};

struct cc2520_gpio_configuration *cc2520_configure_gpios(void)
{
	struct device *gpio;
	int i;

	gpio = device_get_binding(CC2520_GPIO_DEV_NAME);
	if (!gpio) {
		return NULL;
	}

	for (i = 0; i < CC2520_GPIO_IDX_MAX; i++) {
		int flags;

		if (i >= 0 && i < CC2520_GPIO_IDX_FIFO) {
			flags = GPIO_DIR_OUT;
		} else if (i < CC2520_GPIO_IDX_SFD) {
			flags = GPIO_DIR_IN;
		} else {
			flags = (GPIO_DIR_IN | GPIO_INT | GPIO_INT_EDGE |
				 GPIO_INT_ACTIVE_HIGH | GPIO_INT_DEBOUNCE);
		}

		gpio_pin_configure(gpio, cc2520_gpios[i].pin, flags);
		cc2520_gpios[i].dev = gpio;
	}

	return cc2520_gpios;
}

static int fdrm_k64f_cc2520_pinmux_setup(struct device *dev)
{
	int i;

	ARG_UNUSED(dev);

	for (i = 0; i < ARRAY_SIZE(cc2520_mux_config); i++) {
		_fsl_k64_set_pin(cc2520_mux_config[i].pin_num,
				 cc2520_mux_config[i].mode);
	}

	return 0;
}

SYS_INIT(fdrm_k64f_cc2520_pinmux_setup, POST_KERNEL, CC2520_PINMUX_PRIORITY);
