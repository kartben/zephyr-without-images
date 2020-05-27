/*
 * Copyright (c) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT microchip_xec_gpio

#include <errno.h>
#include <device.h>
#include <drivers/gpio.h>
#include <soc.h>

#include "gpio_utils.h"

#define GPIO_IN_BASE(config) \
	((__IO uint32_t *)(GPIO_PARIN_BASE + (config->port_num << 2)))

#define GPIO_OUT_BASE(config) \
	((__IO uint32_t *)(GPIO_PAROUT_BASE + (config->port_num << 2)))

static const uint32_t valid_ctrl_masks[NUM_MCHP_GPIO_PORTS] = {
	(MCHP_GPIO_PORT_A_BITMAP),
	(MCHP_GPIO_PORT_B_BITMAP),
	(MCHP_GPIO_PORT_C_BITMAP),
	(MCHP_GPIO_PORT_D_BITMAP),
	(MCHP_GPIO_PORT_E_BITMAP),
	(MCHP_GPIO_PORT_F_BITMAP)
};

struct gpio_xec_data {
	/* gpio_driver_data needs to be first */
	struct gpio_driver_data common;
	/* port ISR callback routine address */
	sys_slist_t callbacks;
	/* pin callback routine enable flags, by pin number */
	uint32_t pin_callback_enables;
};

struct gpio_xec_config {
	/* gpio_driver_config needs to be first */
	struct gpio_driver_config common;
	__IO uint32_t *pcr1_base;
	uint8_t girq_id;
	uint32_t port_num;
	uint32_t flags;
};

static int gpio_xec_configure(struct device *dev,
			      gpio_pin_t pin, gpio_flags_t flags)
{
	const struct gpio_xec_config *config = dev->config_info;
	__IO uint32_t *current_pcr1;
	uint32_t pcr1 = 0U;
	uint32_t mask = 0U;
	__IO uint32_t *gpio_out_reg = GPIO_OUT_BASE(config);

	/* Validate pin number range in terms of current port */
	if ((valid_ctrl_masks[config->port_num] & BIT(pin)) == 0U) {
		return -EINVAL;
	}

	/* Don't support "open source" mode */
	if (((flags & GPIO_SINGLE_ENDED) != 0U) &&
	    ((flags & GPIO_LINE_OPEN_DRAIN) == 0U)) {
		return -ENOTSUP;
	}

	/* The flags contain options that require touching registers in the
	 * PCRs for a given GPIO. There are no GPIO modules in Microchip SOCs!
	 *
	 * Start with the GPIO module and set up the pin direction register.
	 * 0 - pin is input, 1 - pin is output
	 */
	mask |= MCHP_GPIO_CTRL_DIR_MASK;
	mask |= MCHP_GPIO_CTRL_INPAD_DIS_MASK;
	if ((flags & GPIO_OUTPUT) != 0U) {
		pcr1 |= MCHP_GPIO_CTRL_DIR_OUTPUT;
	} else {
		/* GPIO_INPUT */
		pcr1 |= MCHP_GPIO_CTRL_DIR_INPUT;
	}

	/* Figure out the pullup/pulldown configuration and keep it in the
	 * pcr1 variable
	 */
	mask |= MCHP_GPIO_CTRL_PUD_MASK;

	if ((flags & GPIO_PULL_UP) != 0U) {
		/* Enable the pull and select the pullup resistor. */
		pcr1 |= MCHP_GPIO_CTRL_PUD_PU;
	} else if ((flags & GPIO_PULL_DOWN) != 0U) {
		/* Enable the pull and select the pulldown resistor */
		pcr1 |= MCHP_GPIO_CTRL_PUD_PD;
	}

	/* Push-pull or open drain */
	mask |= MCHP_GPIO_CTRL_BUFT_MASK;

	if ((flags & GPIO_OPEN_DRAIN) != 0U) {
		/* Open drain */
		pcr1 |= MCHP_GPIO_CTRL_BUFT_OPENDRAIN;
	} else {
		/* Push-pull */
		pcr1 |= MCHP_GPIO_CTRL_BUFT_PUSHPULL;
	}

	/* Use GPIO output register to control pin output, instead of
	 * using the control register (=> alternate output disable).
	 */
	mask |= MCHP_GPIO_CTRL_AOD_MASK;
	pcr1 |= MCHP_GPIO_CTRL_AOD_DIS;

	/* Now write contents of pcr1 variable to the PCR1 register that
	 * corresponds to the GPIO being configured
	 */
	current_pcr1 = config->pcr1_base + pin;
	*current_pcr1 = (*current_pcr1 & ~mask) | pcr1;

	if ((flags & GPIO_OUTPUT) != 0U) {
		if ((flags & GPIO_OUTPUT_INIT_HIGH) != 0U) {
			*gpio_out_reg |= BIT(pin);
		} else if ((flags & GPIO_OUTPUT_INIT_LOW) != 0U) {
			*gpio_out_reg &= ~BIT(pin);
		}
	}

	return 0;
}

static int gpio_xec_pin_interrupt_configure(struct device *dev,
		gpio_pin_t pin, enum gpio_int_mode mode,
		enum gpio_int_trig trig)
{
	const struct gpio_xec_config *config = dev->config_info;
	struct gpio_xec_data *drv_data = dev->driver_data;
	__IO uint32_t *current_pcr1;
	uint32_t pcr1 = 0U;
	uint32_t mask = 0U;
	uint32_t gpio_interrupt = 0U;

	/* Validate pin number range in terms of current port */
	if ((valid_ctrl_masks[config->port_num] & BIT(pin)) == 0U) {
		return -EINVAL;
	}

	/* Check if GPIO port supports interrupts */
	if ((mode != GPIO_INT_MODE_DISABLED) &&
	    ((config->flags & GPIO_INT_ENABLE) == 0U)) {
		return -ENOTSUP;
	}

	/* Disable interrupt in the EC aggregator */
	MCHP_GIRQ_ENCLR(config->girq_id) = BIT(pin);

	/* Assemble mask for level/edge triggered interrrupts */
	mask |= MCHP_GPIO_CTRL_IDET_MASK;

	if (mode == GPIO_INT_MODE_DISABLED) {
		/* Explicitly disable interrupts, otherwise the configuration
		 * results in level triggered/low interrupts
		 */
		pcr1 |= MCHP_GPIO_CTRL_IDET_DISABLE;
	} else {
		if (mode == GPIO_INT_MODE_LEVEL) {
			/* Enable level interrupts */
			if (trig == GPIO_INT_TRIG_HIGH) {
				gpio_interrupt = MCHP_GPIO_CTRL_IDET_LVL_HI;
			} else {
				gpio_interrupt = MCHP_GPIO_CTRL_IDET_LVL_LO;
			}
		} else {
			/* Enable edge interrupts */
			switch (trig) {
			case GPIO_INT_TRIG_LOW:
				gpio_interrupt = MCHP_GPIO_CTRL_IDET_FEDGE;
				break;
			case GPIO_INT_TRIG_HIGH:
				gpio_interrupt = MCHP_GPIO_CTRL_IDET_REDGE;
				break;
			case GPIO_INT_TRIG_BOTH:
				gpio_interrupt = MCHP_GPIO_CTRL_IDET_BEDGE;
				break;
			default:
				return -EINVAL;
			}
		}

		pcr1 |= gpio_interrupt;
	}

	/* Now write contents of pcr1 variable to the PCR1 register that
	 * corresponds to the GPIO being configured
	 */
	current_pcr1 = config->pcr1_base + pin;
	*current_pcr1 = (*current_pcr1 & ~mask) | pcr1;

	if (mode == GPIO_INT_MODE_DISABLED) {
		drv_data->pin_callback_enables &= ~BIT(pin);
	} else {
		drv_data->pin_callback_enables |= BIT(pin);
	}

	if (mode != GPIO_INT_MODE_DISABLED) {
		/* We enable the interrupts in the EC aggregator so that the
		 * result can be forwarded to the ARM NVIC
		 */
		MCHP_GIRQ_SRC_CLR(config->girq_id, pin);
		MCHP_GIRQ_ENSET(config->girq_id) = BIT(pin);
	}

	return 0;
}

static int gpio_xec_port_set_masked_raw(struct device *dev, uint32_t mask,
					uint32_t value)
{
	const struct gpio_xec_config *config = dev->config_info;

	/* GPIO output registers are used for writing */
	__IO uint32_t *gpio_base = GPIO_OUT_BASE(config);

	*gpio_base = (*gpio_base & ~mask) | (mask & value);

	return 0;
}

static int gpio_xec_port_set_bits_raw(struct device *dev, uint32_t mask)
{
	const struct gpio_xec_config *config = dev->config_info;

	/* GPIO output registers are used for writing */
	__IO uint32_t *gpio_base = GPIO_OUT_BASE(config);

	*gpio_base |= mask;

	return 0;
}

static int gpio_xec_port_clear_bits_raw(struct device *dev, uint32_t mask)
{
	const struct gpio_xec_config *config = dev->config_info;

	/* GPIO output registers are used for writing */
	__IO uint32_t *gpio_base = GPIO_OUT_BASE(config);

	*gpio_base &= ~mask;

	return 0;
}

static int gpio_xec_port_toggle_bits(struct device *dev, uint32_t mask)
{
	const struct gpio_xec_config *config = dev->config_info;

	/* GPIO output registers are used for writing */
	__IO uint32_t *gpio_base = GPIO_OUT_BASE(config);

	*gpio_base ^= mask;

	return 0;
}

static int gpio_xec_port_get_raw(struct device *dev, uint32_t *value)
{
	const struct gpio_xec_config *config = dev->config_info;

	/* GPIO input registers are used for reading */
	__IO uint32_t *gpio_base = GPIO_IN_BASE(config);

	*value = *gpio_base;

	return 0;
}

static int gpio_xec_manage_callback(struct device *dev,
				    struct gpio_callback *callback, bool set)
{
	struct gpio_xec_data *data = dev->driver_data;

	gpio_manage_callback(&data->callbacks, callback, set);

	return 0;
}

static int gpio_xec_enable_callback(struct device *dev,
				    gpio_pin_t pin)
{
	struct gpio_xec_data *data = dev->driver_data;

	data->pin_callback_enables |= BIT(pin);

	return 0;
}

static int gpio_xec_disable_callback(struct device *dev,
				     gpio_pin_t pin)
{
	struct gpio_xec_data *data = dev->driver_data;

	data->pin_callback_enables &= ~BIT(pin);

	return 0;
}

static void gpio_gpio_xec_port_isr(void *arg)
{
	struct device *dev = (struct device *)arg;
	const struct gpio_xec_config *config = dev->config_info;
	struct gpio_xec_data *data = dev->driver_data;
	uint32_t girq_result;
	uint32_t enabled_int;

	/* Figure out which interrupts have been triggered from the EC
	 * aggregator result register
	 */
	girq_result = MCHP_GIRQ_RESULT(config->girq_id);
	enabled_int = girq_result & data->pin_callback_enables;

	/* Clear source register in aggregator before firing callbacks */
	REG32(MCHP_GIRQ_SRC_ADDR(config->girq_id)) = girq_result;

	gpio_fire_callbacks(&data->callbacks, dev, enabled_int);
}

static const struct gpio_driver_api gpio_xec_driver_api = {
	.pin_configure = gpio_xec_configure,
	.port_get_raw = gpio_xec_port_get_raw,
	.port_set_masked_raw = gpio_xec_port_set_masked_raw,
	.port_set_bits_raw = gpio_xec_port_set_bits_raw,
	.port_clear_bits_raw = gpio_xec_port_clear_bits_raw,
	.port_toggle_bits = gpio_xec_port_toggle_bits,
	.pin_interrupt_configure = gpio_xec_pin_interrupt_configure,
	.manage_callback = gpio_xec_manage_callback,
	.enable_callback = gpio_xec_enable_callback,
	.disable_callback = gpio_xec_disable_callback,
};

#if DT_NODE_HAS_STATUS(DT_NODELABEL(gpio_000_036), okay)
static int gpio_xec_port000_036_init(struct device *dev);

static const struct gpio_xec_config gpio_xec_port000_036_config = {
	.common = {
		.port_pin_mask = GPIO_PORT_PIN_MASK_FROM_DT_NODE(
					DT_NODELABEL(gpio_000_036)),
	},
	.pcr1_base = (uint32_t *) DT_REG_ADDR(DT_NODELABEL(gpio_000_036)),
	.port_num = MCHP_GPIO_000_036,
#if DT_IRQ_HAS_CELL(DT_NODELABEL(gpio_000_036), irq)
	.girq_id = MCHP_GIRQ11_ID,
	.flags = GPIO_INT_ENABLE,
#else
	.flags = 0,
#endif
};

static struct gpio_xec_data gpio_xec_port000_036_data;

DEVICE_AND_API_INIT(gpio_xec_port000_036,
		DT_LABEL(DT_NODELABEL(gpio_000_036)),
		gpio_xec_port000_036_init,
		&gpio_xec_port000_036_data, &gpio_xec_port000_036_config,
		POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
		&gpio_xec_driver_api);

static int gpio_xec_port000_036_init(struct device *dev)
{
#if DT_IRQ_HAS_CELL(DT_NODELABEL(gpio_000_036), irq)
	const struct gpio_xec_config *config = dev->config_info;

	/* Turn on the block enable in the EC aggregator */
	MCHP_GIRQ_BLK_SETEN(config->girq_id);

	IRQ_CONNECT(DT_IRQ(DT_NODELABEL(gpio_000_036), irq),
		DT_IRQ(DT_NODELABEL(gpio_000_036), priority),
		gpio_gpio_xec_port_isr, DEVICE_GET(gpio_xec_port000_036), 0U);

	irq_enable(DT_IRQ(DT_NODELABEL(gpio_000_036), irq));
#endif
	return 0;
}
#endif /* DT_NODE_HAS_STATUS(DT_NODELABEL(gpio_000_036), okay) */

#if DT_NODE_HAS_STATUS(DT_NODELABEL(gpio_040_076), okay)
static int gpio_xec_port040_076_init(struct device *dev);

static const struct gpio_xec_config gpio_xec_port040_076_config = {
	.common = {
		.port_pin_mask = GPIO_PORT_PIN_MASK_FROM_DT_NODE(
					DT_NODELABEL(gpio_040_076)),
	},
	.pcr1_base = (uint32_t *) DT_REG_ADDR(DT_NODELABEL(gpio_040_076)),
	.port_num = MCHP_GPIO_040_076,
#if DT_IRQ_HAS_CELL(DT_NODELABEL(gpio_040_076), irq)
	.girq_id = MCHP_GIRQ10_ID,
	.flags = GPIO_INT_ENABLE,
#else
	.flags = 0,
#endif
};

static struct gpio_xec_data gpio_xec_port040_076_data;

DEVICE_AND_API_INIT(gpio_xec_port040_076,
		DT_LABEL(DT_NODELABEL(gpio_040_076)),
		gpio_xec_port040_076_init,
		&gpio_xec_port040_076_data, &gpio_xec_port040_076_config,
		POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
		&gpio_xec_driver_api);

static int gpio_xec_port040_076_init(struct device *dev)
{
#if DT_IRQ_HAS_CELL(DT_NODELABEL(gpio_040_076), irq)
	const struct gpio_xec_config *config = dev->config_info;

	/* Turn on the block enable in the EC aggregator */
	MCHP_GIRQ_BLK_SETEN(config->girq_id);

	IRQ_CONNECT(DT_IRQ(DT_NODELABEL(gpio_040_076), irq),
		DT_IRQ(DT_NODELABEL(gpio_040_076), priority),
		gpio_gpio_xec_port_isr, DEVICE_GET(gpio_xec_port040_076), 0U);

	irq_enable(DT_IRQ(DT_NODELABEL(gpio_040_076), irq));
#endif
	return 0;
}
#endif /* DT_NODE_HAS_STATUS(DT_NODELABEL(gpio_040_076), okay) */

#if DT_NODE_HAS_STATUS(DT_NODELABEL(gpio_100_136), okay)
static int gpio_xec_port100_136_init(struct device *dev);

static const struct gpio_xec_config gpio_xec_port100_136_config = {
	.common = {
		.port_pin_mask = GPIO_PORT_PIN_MASK_FROM_DT_NODE(
					DT_NODELABEL(gpio_100_136)),
	},
	.pcr1_base = (uint32_t *) DT_REG_ADDR(DT_NODELABEL(gpio_100_136)),
	.port_num = MCHP_GPIO_100_136,
#if DT_IRQ_HAS_CELL(DT_NODELABEL(gpio_100_136), irq)
	.girq_id = MCHP_GIRQ09_ID,
	.flags = GPIO_INT_ENABLE,
#else
	.flags = 0,
#endif
};

static struct gpio_xec_data gpio_xec_port100_136_data;

DEVICE_AND_API_INIT(gpio_xec_port100_136,
		DT_LABEL(DT_NODELABEL(gpio_100_136)),
		gpio_xec_port100_136_init,
		&gpio_xec_port100_136_data, &gpio_xec_port100_136_config,
		POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
		&gpio_xec_driver_api);

static int gpio_xec_port100_136_init(struct device *dev)
{
#if DT_IRQ_HAS_CELL(DT_NODELABEL(gpio_100_136), irq)
	const struct gpio_xec_config *config = dev->config_info;

	/* Turn on the block enable in the EC aggregator */
	MCHP_GIRQ_BLK_SETEN(config->girq_id);

	IRQ_CONNECT(DT_IRQ(DT_NODELABEL(gpio_100_136), irq),
		DT_IRQ(DT_NODELABEL(gpio_100_136), priority),
		gpio_gpio_xec_port_isr, DEVICE_GET(gpio_xec_port100_136), 0U);

	irq_enable(DT_IRQ(DT_NODELABEL(gpio_100_136), irq));
#endif
	return 0;
}
#endif /* DT_NODE_HAS_STATUS(DT_NODELABEL(gpio_100_136), okay) */

#if DT_NODE_HAS_STATUS(DT_NODELABEL(gpio_140_176), okay)
static int gpio_xec_port140_176_init(struct device *dev);

static const struct gpio_xec_config gpio_xec_port140_176_config = {
	.common = {
		.port_pin_mask = GPIO_PORT_PIN_MASK_FROM_DT_NODE(
					DT_NODELABEL(gpio_140_176)),
	},
	.pcr1_base = (uint32_t *) DT_REG_ADDR(DT_NODELABEL(gpio_140_176)),
	.port_num = MCHP_GPIO_140_176,
#if DT_IRQ_HAS_CELL(DT_NODELABEL(gpio_140_176), irq)
	.girq_id = MCHP_GIRQ08_ID,
	.flags = GPIO_INT_ENABLE,
#else
	.flags = 0,
#endif
};

static struct gpio_xec_data gpio_xec_port140_176_data;

DEVICE_AND_API_INIT(gpio_xec_port140_176,
		DT_LABEL(DT_NODELABEL(gpio_140_176)),
		gpio_xec_port140_176_init,
		&gpio_xec_port140_176_data, &gpio_xec_port140_176_config,
		POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
		&gpio_xec_driver_api);

static int gpio_xec_port140_176_init(struct device *dev)
{
#if DT_IRQ_HAS_CELL(DT_NODELABEL(gpio_140_176), irq)
	const struct gpio_xec_config *config = dev->config_info;

	/* Turn on the block enable in the EC aggregator */
	MCHP_GIRQ_BLK_SETEN(config->girq_id);

	IRQ_CONNECT(DT_IRQ(DT_NODELABEL(gpio_140_176), irq),
		DT_IRQ(DT_NODELABEL(gpio_140_176), priority),
		gpio_gpio_xec_port_isr, DEVICE_GET(gpio_xec_port140_176), 0U);

	irq_enable(DT_IRQ(DT_NODELABEL(gpio_140_176), irq));
#endif
	return 0;
}
#endif /* DT_NODE_HAS_STATUS(DT_NODELABEL(gpio_140_176), okay) */

#if DT_NODE_HAS_STATUS(DT_NODELABEL(gpio_200_236), okay)
static int gpio_xec_port200_236_init(struct device *dev);

static const struct gpio_xec_config gpio_xec_port200_236_config = {
	.common = {
		.port_pin_mask = GPIO_PORT_PIN_MASK_FROM_DT_NODE(
					DT_NODELABEL(gpio_200_236)),
	},
	.pcr1_base = (uint32_t *) DT_REG_ADDR(DT_NODELABEL(gpio_200_236)),
	.port_num = MCHP_GPIO_200_236,
#if DT_IRQ_HAS_CELL(DT_NODELABEL(gpio_200_236), irq)
	.girq_id = MCHP_GIRQ12_ID,
	.flags = GPIO_INT_ENABLE,
#else
	.flags = 0,
#endif
};

static struct gpio_xec_data gpio_xec_port200_236_data;

DEVICE_AND_API_INIT(gpio_xec_port200_236,
		DT_LABEL(DT_NODELABEL(gpio_200_236)),
		gpio_xec_port200_236_init,
		&gpio_xec_port200_236_data, &gpio_xec_port200_236_config,
		POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
		&gpio_xec_driver_api);

static int gpio_xec_port200_236_init(struct device *dev)
{
#if DT_IRQ_HAS_CELL(DT_NODELABEL(gpio_200_236), irq)
	const struct gpio_xec_config *config = dev->config_info;

	/* Turn on the block enable in the EC aggregator */
	MCHP_GIRQ_BLK_SETEN(config->girq_id);

	IRQ_CONNECT(DT_IRQ(DT_NODELABEL(gpio_200_236), irq),
		DT_IRQ(DT_NODELABEL(gpio_200_236), priority),
		gpio_gpio_xec_port_isr, DEVICE_GET(gpio_xec_port200_236), 0U);

	irq_enable(DT_IRQ(DT_NODELABEL(gpio_200_236), irq));
#endif
	return 0;
}
#endif /* DT_NODE_HAS_STATUS(DT_NODELABEL(gpio_200_236), okay) */

#if DT_NODE_HAS_STATUS(DT_NODELABEL(gpio_240_276), okay)
static int gpio_xec_port240_276_init(struct device *dev);

static const struct gpio_xec_config gpio_xec_port240_276_config = {
	.common = {
		.port_pin_mask = GPIO_PORT_PIN_MASK_FROM_DT_NODE(
					DT_NODELABEL(gpio_240_276)),
	},
	.pcr1_base = (uint32_t *) DT_REG_ADDR(DT_NODELABEL(gpio_240_276)),
	.port_num = MCHP_GPIO_240_276,
#if DT_IRQ_HAS_CELL(DT_NODELABEL(gpio_240_276), irq)
	.girq_id = MCHP_GIRQ26_ID,
	.flags = GPIO_INT_ENABLE,
#else
	.flags = 0,
#endif
};

static struct gpio_xec_data gpio_xec_port240_276_data;

DEVICE_AND_API_INIT(gpio_xec_port240_276,
		DT_LABEL(DT_NODELABEL(gpio_240_276)),
		gpio_xec_port240_276_init,
		&gpio_xec_port240_276_data, &gpio_xec_port240_276_config,
		POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
		&gpio_xec_driver_api);

static int gpio_xec_port240_276_init(struct device *dev)
{
#if DT_IRQ_HAS_CELL(DT_NODELABEL(gpio_240_276), irq)
	const struct gpio_xec_config *config = dev->config_info;

	/* Turn on the block enable in the EC aggregator */
	MCHP_GIRQ_BLK_SETEN(config->girq_id);

	IRQ_CONNECT(DT_IRQ(DT_NODELABEL(gpio_240_276), irq),
		DT_IRQ(DT_NODELABEL(gpio_240_276), priority),
		gpio_gpio_xec_port_isr, DEVICE_GET(gpio_xec_port240_276), 0U);

	irq_enable(DT_IRQ(DT_NODELABEL(gpio_240_276), irq));
#endif
	return 0;
}
#endif /* DT_NODE_HAS_STATUS(DT_NODELABEL(gpio_240_276), okay) */
