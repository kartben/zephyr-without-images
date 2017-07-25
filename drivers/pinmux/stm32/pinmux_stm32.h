/*
 * Copyright (c) 2016 Open-RnD Sp. z o.o.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file header for STM32 pin multiplexing
 */

#ifndef _STM32_PINMUX_H_
#define _STM32_PINMUX_H_

#include <zephyr/types.h>
#include <stddef.h>
#include <clock_control.h>
#include "pinmux/pinmux.h"

#ifdef CONFIG_SOC_SERIES_STM32F1X

/**
 * @brief PIN configuration bitfield
 *
 * Pin configuration is coded with the following
 * fields
 *    GPIO I/O Mode       [ 0 ]
 *    GPIO Input config   [ 1 : 2 ]
 *    GPIO Output speed   [ 3 : 4 ]
 *    GPIO Output PP/OD   [ 5 ]
 *    GPIO Output AF/GP   [ 6 ]
 *    GPIO PUPD Config    [ 7 : 8 ]
 *
 * Applicable to STM32F1 series
 */
#define STM32_AFR_MASK		0

/* Port Mode */
#define STM32_MODE_INPUT		(0x0<<STM32_MODE_INOUT_SHIFT)
#define STM32_MODE_OUTPUT		(0x1<<STM32_MODE_INOUT_SHIFT)
#define STM32_MODE_INOUT_MASK		0x1
#define STM32_MODE_INOUT_SHIFT		0

/* Input Port configuration */
#define STM32_CNF_IN_ANALOG		(0x0<<STM32_CNF_IN_SHIFT)
#define STM32_CNF_IN_FLOAT		(0x1<<STM32_CNF_IN_SHIFT)
#define STM32_CNF_IN_PUPD		(0x2<<STM32_CNF_IN_SHIFT)
#define STM32_CNF_IN_MASK		0x3
#define STM32_CNF_IN_SHIFT		1

/* Output Port configuration */
#define STM32_MODE_OUTPUT_MAX_10	(0x0<<STM32_MODE_OSPEED_SHIFT)
#define STM32_MODE_OUTPUT_MAX_2		(0x1<<STM32_MODE_OSPEED_SHIFT)
#define STM32_MODE_OUTPUT_MAX_50	(0x2<<STM32_MODE_OSPEED_SHIFT)
#define STM32_MODE_OSPEED_MASK		0x3
#define STM32_MODE_OSPEED_SHIFT		3

#define STM32_CNF_PUSH_PULL		(0x0<<STM32_CNF_OUT_0_SHIFT)
#define STM32_CNF_OPEN_DRAIN		(0x1<<STM32_CNF_OUT_0_SHIFT)
#define STM32_CNF_OUT_0_MASK		0x1
#define STM32_CNF_OUT_0_SHIFT		5

#define STM32_CNF_GP_OUTPUT		(0x0<<STM32_CNF_OUT_1_SHIFT)
#define STM32_CNF_ALT_FUNC		(0x1<<STM32_CNF_OUT_1_SHIFT)
#define STM32_CNF_OUT_1_MASK		0x1
#define STM32_CNF_OUT_1_SHIFT		6

/* GPIO High impedance/Pull-up/Pull-down */
#define STM32_PUPD_NO_PULL		(0x0<<STM32_PUPD_SHIFT)
#define STM32_PUPD_PULL_UP		(0x1<<STM32_PUPD_SHIFT)
#define STM32_PUPD_PULL_DOWN		(0x2<<STM32_PUPD_SHIFT)
#define STM32_PUPD_MASK			0x3
#define STM32_PUPD_SHIFT		7

/* Alternate defines */
/* IO pin functions are mostly common across STM32 devices. Notable
 * exception is STM32F1 as these MCUs do not have registers for
 * configuration of pin's alternate function. The configuration is
 * done implicitly by setting specific mode and config in MODE and CNF
 * registers for particular pin.
 */

#define STM32_PIN_USART_TX	STM32_MODE_OUTPUT | STM32_CNF_ALT_FUNC | \
				STM32_CNF_PUSH_PULL
#define STM32_PIN_USART_RX	STM32_MODE_INPUT | STM32_CNF_IN_FLOAT
#define STM32_PIN_I2C		STM32_MODE_OUTPUT | STM32_CNF_ALT_FUNC | \
				STM32_CNF_OPEN_DRAIN
#define STM32_PIN_PWM		STM32_MODE_OUTPUT | STM32_CNF_ALT_FUNC | \
				STM32_CNF_PUSH_PULL

#else

/**
 * @brief PIN configuration bitfield
 *
 * Pin configuration is coded with the following
 * fields
 *    Alternate Function  [ 0 : 7 ]
 *    GPIO Mode           [ 8 : 9 ]
 *    GPIO Output type    [ 10 ]
 *    GPIO Speed          [ 11 : 12 ]
 *    GPIO PUPD config    [ 13 : 14 ]
 *
 * Applicable to STM32F3, STM32F4, STM32L4 series
 */

#define STM32_AFR_MASK			0xF

/* GPIO Mode */
#define STM32_MODER_INPUT_MODE		(0x0<<STM32_MODER_SHIFT)
#define STM32_MODER_OUTPUT_MODE		(0x1<<STM32_MODER_SHIFT)
#define STM32_MODER_ALT_MODE		(0x2<<STM32_MODER_SHIFT)
#define STM32_MODER_ANALOG_MODE	 	(0x3<<STM32_MODER_SHIFT)
#define STM32_MODER_MASK	 	0x3
#define STM32_MODER_SHIFT		4

/* GPIO Output type */
#define STM32_OTYPER_PUSH_PULL		(0x0<<STM32_OTYPER_SHIFT)
#define STM32_OTYPER_OPEN_DRAIN		(0x1<<STM32_OTYPER_SHIFT)
#define STM32_OTYPER_MASK		0x1
#define STM32_OTYPER_SHIFT		6

/* GPIO speed */
#define STM32_OSPEEDR_LOW_SPEED		(0x0<<STM32_OSPEEDR_SHIFT)
#define STM32_OSPEEDR_MEDIUM_SPEED	(0x1<<STM32_OSPEEDR_SHIFT)
#define STM32_OSPEEDR_HIGH_SPEED	(0x2<<STM32_OSPEEDR_SHIFT)
#define STM32_OSPEEDR_VERY_HIGH_SPEED	(0x3<<STM32_OSPEEDR_SHIFT)
#define STM32_OSPEEDR_MASK		0x3
#define STM32_OSPEEDR_SHIFT		7

/* GPIO High impedance/Pull-up/pull-down */
#define STM32_PUPDR_NO_PULL		(0x0<<STM32_PUPDR_SHIFT)
#define STM32_PUPDR_PULL_UP		(0x1<<STM32_PUPDR_SHIFT)
#define STM32_PUPDR_PULL_DOWN		(0x2<<STM32_PUPDR_SHIFT)
#define STM32_PUPDR_MASK		0x3
#define STM32_PUPDR_SHIFT		9

/* Add usefull defines */
#define STM32_PUSHPULL_NOPULL        (STM32_OTYPER_PUSH_PULL | \
				      STM32_PUPDR_NO_PULL)
#define STM32_OPENDRAIN_PULLUP       (STM32_OTYPER_OPEN_DRAIN | \
				      STM32_PUPDR_PULL_UP)


enum stm32_pin_alt_func {
	STM32_FUNC_ALT_0 = 0, /* GPIO */
	STM32_FUNC_ALT_1,
	STM32_FUNC_ALT_2,
	STM32_FUNC_ALT_3,
	STM32_FUNC_ALT_4,
	STM32_FUNC_ALT_5,
	STM32_FUNC_ALT_6,
	STM32_FUNC_ALT_7,
	STM32_FUNC_ALT_8,
	STM32_FUNC_ALT_9,
	STM32_FUNC_ALT_10,
	STM32_FUNC_ALT_11,
	STM32_FUNC_ALT_12,
	STM32_FUNC_ALT_13,
	STM32_FUNC_ALT_14,
	STM32_FUNC_ALT_15,
	STM32_FUNC_ALT_16,
	STM32_FUNC_ALT_MAX
};

#define STM32_PINMUX_ALT_FUNC_0 (STM32_FUNC_ALT_0 | STM32_MODER_ALT_MODE)
#define STM32_PINMUX_ALT_FUNC_1 (STM32_FUNC_ALT_1 | STM32_MODER_ALT_MODE)
#define STM32_PINMUX_ALT_FUNC_2 (STM32_FUNC_ALT_2 | STM32_MODER_ALT_MODE)
#define STM32_PINMUX_ALT_FUNC_3 (STM32_FUNC_ALT_3 | STM32_MODER_ALT_MODE)
#define STM32_PINMUX_ALT_FUNC_4 (STM32_FUNC_ALT_4 | STM32_MODER_ALT_MODE)
#define STM32_PINMUX_ALT_FUNC_5 (STM32_FUNC_ALT_5 | STM32_MODER_ALT_MODE)
#define STM32_PINMUX_ALT_FUNC_6 (STM32_FUNC_ALT_6 | STM32_MODER_ALT_MODE)
#define STM32_PINMUX_ALT_FUNC_7 (STM32_FUNC_ALT_7 | STM32_MODER_ALT_MODE)
#define STM32_PINMUX_ALT_FUNC_8 (STM32_FUNC_ALT_8 | STM32_MODER_ALT_MODE)
#define STM32_PINMUX_ALT_FUNC_9 (STM32_FUNC_ALT_9 | STM32_MODER_ALT_MODE)
#define STM32_PINMUX_ALT_FUNC_10 (STM32_FUNC_ALT_10 | STM32_MODER_ALT_MODE)
#define STM32_PINMUX_ALT_FUNC_11 (STM32_FUNC_ALT_11 | STM32_MODER_ALT_MODE)
#define STM32_PINMUX_ALT_FUNC_12 (STM32_FUNC_ALT_12 | STM32_MODER_ALT_MODE)
#define STM32_PINMUX_ALT_FUNC_13 (STM32_FUNC_ALT_13 | STM32_MODER_ALT_MODE)
#define STM32_PINMUX_ALT_FUNC_14 (STM32_FUNC_ALT_14 | STM32_MODER_ALT_MODE)
#define STM32_PINMUX_ALT_FUNC_15 (STM32_FUNC_ALT_15 | STM32_MODER_ALT_MODE)

#define STM32_PINMUX_FUNC_GPIO 0
#define STM32_PINMUX_FUNC_ANALOG (STM32_PINMUX_FUNC_ALT_MAX)

#define STM32_AF_SHIFT 16

#endif /* SOC_SERIES_STM32F1X */

/**
 * @brief numerical IDs for IO ports
 */
enum stm32_pin_port {
	STM32_PORTA = 0,	/* IO port A */
	STM32_PORTB,		/* .. */
	STM32_PORTC,
	STM32_PORTD,
	STM32_PORTE,
	STM32_PORTF,
	STM32_PORTG,
	STM32_PORTH,		/* IO port H */
};

/* override this at soc level */
#ifndef STM32_PORTS_MAX
#define STM32_PORTS_MAX (STM32_PORTH + 1)
#endif

/**
 * @brief helper macro to encode an IO port pin in a numerical format
 */
#define STM32PIN(_port, _pin) \
	(_port << 4 | _pin)


#define STM32_PIN_PA0	STM32PIN(STM32_PORTA, 0)
#define STM32_PIN_PA1	STM32PIN(STM32_PORTA, 1)
#define STM32_PIN_PA2	STM32PIN(STM32_PORTA, 2)
#define STM32_PIN_PA3	STM32PIN(STM32_PORTA, 3)
#define STM32_PIN_PA4	STM32PIN(STM32_PORTA, 4)
#define STM32_PIN_PA5	STM32PIN(STM32_PORTA, 5)
#define STM32_PIN_PA6	STM32PIN(STM32_PORTA, 6)
#define STM32_PIN_PA7	STM32PIN(STM32_PORTA, 7)
#define STM32_PIN_PA8	STM32PIN(STM32_PORTA, 8)
#define STM32_PIN_PA9	STM32PIN(STM32_PORTA, 9)
#define STM32_PIN_PA10  STM32PIN(STM32_PORTA, 10)
#define STM32_PIN_PA11  STM32PIN(STM32_PORTA, 11)
#define STM32_PIN_PA12  STM32PIN(STM32_PORTA, 12)
#define STM32_PIN_PA13  STM32PIN(STM32_PORTA, 13)
#define STM32_PIN_PA14  STM32PIN(STM32_PORTA, 14)
#define STM32_PIN_PA15  STM32PIN(STM32_PORTA, 15)

#define STM32_PIN_PB0	STM32PIN(STM32_PORTB, 0)
#define STM32_PIN_PB1	STM32PIN(STM32_PORTB, 1)
#define STM32_PIN_PB2	STM32PIN(STM32_PORTB, 2)
#define STM32_PIN_PB3	STM32PIN(STM32_PORTB, 3)
#define STM32_PIN_PB4	STM32PIN(STM32_PORTB, 4)
#define STM32_PIN_PB5	STM32PIN(STM32_PORTB, 5)
#define STM32_PIN_PB6	STM32PIN(STM32_PORTB, 6)
#define STM32_PIN_PB7	STM32PIN(STM32_PORTB, 7)
#define STM32_PIN_PB8	STM32PIN(STM32_PORTB, 8)
#define STM32_PIN_PB9	STM32PIN(STM32_PORTB, 9)
#define STM32_PIN_PB10  STM32PIN(STM32_PORTB, 10)
#define STM32_PIN_PB11  STM32PIN(STM32_PORTB, 11)
#define STM32_PIN_PB12  STM32PIN(STM32_PORTB, 12)
#define STM32_PIN_PB13  STM32PIN(STM32_PORTB, 13)
#define STM32_PIN_PB14  STM32PIN(STM32_PORTB, 14)
#define STM32_PIN_PB15  STM32PIN(STM32_PORTB, 15)

#define STM32_PIN_PC0	STM32PIN(STM32_PORTC, 0)
#define STM32_PIN_PC1	STM32PIN(STM32_PORTC, 1)
#define STM32_PIN_PC2	STM32PIN(STM32_PORTC, 2)
#define STM32_PIN_PC3	STM32PIN(STM32_PORTC, 3)
#define STM32_PIN_PC4	STM32PIN(STM32_PORTC, 4)
#define STM32_PIN_PC5	STM32PIN(STM32_PORTC, 5)
#define STM32_PIN_PC6	STM32PIN(STM32_PORTC, 6)
#define STM32_PIN_PC7	STM32PIN(STM32_PORTC, 7)
#define STM32_PIN_PC8	STM32PIN(STM32_PORTC, 8)
#define STM32_PIN_PC9	STM32PIN(STM32_PORTC, 9)
#define STM32_PIN_PC10  STM32PIN(STM32_PORTC, 10)
#define STM32_PIN_PC11  STM32PIN(STM32_PORTC, 11)
#define STM32_PIN_PC12  STM32PIN(STM32_PORTC, 12)
#define STM32_PIN_PC13  STM32PIN(STM32_PORTC, 13)
#define STM32_PIN_PC14  STM32PIN(STM32_PORTC, 14)
#define STM32_PIN_PC15  STM32PIN(STM32_PORTC, 15)

#define STM32_PIN_PD0	STM32PIN(STM32_PORTD, 0)
#define STM32_PIN_PD1	STM32PIN(STM32_PORTD, 1)
#define STM32_PIN_PD2	STM32PIN(STM32_PORTD, 2)
#define STM32_PIN_PD3	STM32PIN(STM32_PORTD, 3)
#define STM32_PIN_PD4	STM32PIN(STM32_PORTD, 4)
#define STM32_PIN_PD5	STM32PIN(STM32_PORTD, 5)
#define STM32_PIN_PD6	STM32PIN(STM32_PORTD, 6)
#define STM32_PIN_PD7	STM32PIN(STM32_PORTD, 7)
#define STM32_PIN_PD8	STM32PIN(STM32_PORTD, 8)
#define STM32_PIN_PD9	STM32PIN(STM32_PORTD, 9)
#define STM32_PIN_PD10  STM32PIN(STM32_PORTD, 10)
#define STM32_PIN_PD11  STM32PIN(STM32_PORTD, 11)
#define STM32_PIN_PD12  STM32PIN(STM32_PORTD, 12)
#define STM32_PIN_PD13  STM32PIN(STM32_PORTD, 13)
#define STM32_PIN_PD14  STM32PIN(STM32_PORTD, 14)
#define STM32_PIN_PD15  STM32PIN(STM32_PORTD, 15)

#define STM32_PIN_PE0	STM32PIN(STM32_PORTE, 0)
#define STM32_PIN_PE1	STM32PIN(STM32_PORTE, 1)
#define STM32_PIN_PE2	STM32PIN(STM32_PORTE, 2)
#define STM32_PIN_PE3	STM32PIN(STM32_PORTE, 3)
#define STM32_PIN_PE4	STM32PIN(STM32_PORTE, 4)
#define STM32_PIN_PE5	STM32PIN(STM32_PORTE, 5)
#define STM32_PIN_PE6	STM32PIN(STM32_PORTE, 6)
#define STM32_PIN_PE7	STM32PIN(STM32_PORTE, 7)
#define STM32_PIN_PE8	STM32PIN(STM32_PORTE, 8)
#define STM32_PIN_PE9	STM32PIN(STM32_PORTE, 9)
#define STM32_PIN_PE10  STM32PIN(STM32_PORTE, 10)
#define STM32_PIN_PE11  STM32PIN(STM32_PORTE, 11)
#define STM32_PIN_PE12  STM32PIN(STM32_PORTE, 12)
#define STM32_PIN_PE13  STM32PIN(STM32_PORTE, 13)
#define STM32_PIN_PE14  STM32PIN(STM32_PORTE, 14)
#define STM32_PIN_PE15  STM32PIN(STM32_PORTE, 15)

#define STM32_PIN_PF0	STM32PIN(STM32_PORTF, 0)
#define STM32_PIN_PF1	STM32PIN(STM32_PORTF, 1)
#define STM32_PIN_PF2	STM32PIN(STM32_PORTF, 2)
#define STM32_PIN_PF3	STM32PIN(STM32_PORTF, 3)
#define STM32_PIN_PF4	STM32PIN(STM32_PORTF, 4)
#define STM32_PIN_PF5	STM32PIN(STM32_PORTF, 5)
#define STM32_PIN_PF6	STM32PIN(STM32_PORTF, 6)
#define STM32_PIN_PF7	STM32PIN(STM32_PORTF, 7)
#define STM32_PIN_PF8	STM32PIN(STM32_PORTF, 8)
#define STM32_PIN_PF9	STM32PIN(STM32_PORTF, 9)
#define STM32_PIN_PF10  STM32PIN(STM32_PORTF, 10)
#define STM32_PIN_PF11  STM32PIN(STM32_PORTF, 11)
#define STM32_PIN_PF12  STM32PIN(STM32_PORTF, 12)
#define STM32_PIN_PF13  STM32PIN(STM32_PORTF, 13)
#define STM32_PIN_PF14  STM32PIN(STM32_PORTF, 14)
#define STM32_PIN_PF15  STM32PIN(STM32_PORTF, 15)

#define STM32_PIN_PG0	STM32PIN(STM32_PORTG, 0)
#define STM32_PIN_PG1	STM32PIN(STM32_PORTG, 1)
#define STM32_PIN_PG2	STM32PIN(STM32_PORTG, 2)
#define STM32_PIN_PG3	STM32PIN(STM32_PORTG, 3)
#define STM32_PIN_PG4	STM32PIN(STM32_PORTG, 4)
#define STM32_PIN_PG5	STM32PIN(STM32_PORTG, 5)
#define STM32_PIN_PG6	STM32PIN(STM32_PORTG, 6)
#define STM32_PIN_PG7	STM32PIN(STM32_PORTG, 7)
#define STM32_PIN_PG8	STM32PIN(STM32_PORTG, 8)
#define STM32_PIN_PG9	STM32PIN(STM32_PORTG, 9)
#define STM32_PIN_PG10  STM32PIN(STM32_PORTG, 10)
#define STM32_PIN_PG11  STM32PIN(STM32_PORTG, 11)
#define STM32_PIN_PG12  STM32PIN(STM32_PORTG, 12)
#define STM32_PIN_PG13  STM32PIN(STM32_PORTG, 13)
#define STM32_PIN_PG14  STM32PIN(STM32_PORTG, 14)
#define STM32_PIN_PG15  STM32PIN(STM32_PORTG, 15)

#define STM32_PIN_PH0	STM32PIN(STM32_PORTH, 0)
#define STM32_PIN_PH1	STM32PIN(STM32_PORTH, 1)
#define STM32_PIN_PH2	STM32PIN(STM32_PORTH, 2)
#define STM32_PIN_PH3	STM32PIN(STM32_PORTH, 3)
#define STM32_PIN_PH4	STM32PIN(STM32_PORTH, 4)
#define STM32_PIN_PH5	STM32PIN(STM32_PORTH, 5)
#define STM32_PIN_PH6	STM32PIN(STM32_PORTH, 6)
#define STM32_PIN_PH7	STM32PIN(STM32_PORTH, 7)
#define STM32_PIN_PH8	STM32PIN(STM32_PORTH, 8)
#define STM32_PIN_PH9	STM32PIN(STM32_PORTH, 9)
#define STM32_PIN_PH10  STM32PIN(STM32_PORTH, 10)
#define STM32_PIN_PH11  STM32PIN(STM32_PORTH, 11)
#define STM32_PIN_PH12  STM32PIN(STM32_PORTH, 12)
#define STM32_PIN_PH13  STM32PIN(STM32_PORTH, 13)
#define STM32_PIN_PH14  STM32PIN(STM32_PORTH, 14)
#define STM32_PIN_PH15  STM32PIN(STM32_PORTH, 15)

/* pretend that array will cover pin functions */
typedef int stm32_pin_func_t;

/**
 * @brief pinmux config wrapper
 *
 * GPIO function is assumed to be always available, as such it's not listed
 * in @funcs array
 */
struct stm32_pinmux_conf {
	u32_t pin;		 /* pin ID */
	const stm32_pin_func_t *funcs; /* functions array, indexed with
					* (stm32_pin_alt_func - 1)
					*/
	const size_t nfuncs;	 /* number of alternate functions, not
				  * counting GPIO
				  */
};

/**
 * @brief helper to define pins
 */
#define STM32_PIN_CONF(__pin, __funcs) \
	{__pin, __funcs, ARRAY_SIZE(__funcs)}

/**
 * @brief helper for encoding alternate function with pin config mode
 * on stm32_pin_func_t
 */
#define STM32_AS_AF(__af)			\
	(__af << STM32_AF_SHIFT)

/**
 * @brief helper for extracting alternate function from stm32_pin_func_t
 */
#define STM32_AF(__pinconf)			\
	(__pinconf >> STM32_AF_SHIFT)

/**
 * @brief helper for encoding pin mode on stm32_pin_func_t
 */
#define STM32_AS_MODE(__mode)			\
	(__mode)

/**
 * @brief helper for extracting pin mode encoded on stm32_pin_func_t
 */
#define STM32_MODE(__pinconf)				\
	(__pinconf & ((1 << STM32_AF_SHIFT) - 1))

/**
 * @brief helper for encoding pin mode and alternate function on
 * stm32_pin_func_t
 */
#define STM32_PINFUNC(__af, __mode)			\
	(STM32_AS_AF(__af) | STM32_AS_MODE(__mode))

/**
 * @brief helper to extract IO port number from STM32PIN() encoded
 * value
 */
#define STM32_PORT(__pin) \
	(__pin >> 4)

/**
 * @brief helper to extract IO pin number from STM32PIN() encoded
 * value
 */
#define STM32_PIN(__pin) \
	(__pin & 0xf)

/**
 * @brief helper for mapping pin function to its configuration
 *
 * @param pin   pin ID encoded with STM32PIN()
 * @param func  alternate function ID
 *
 * Helper function for mapping alternate function for given pin to its
 * configuration. This function must be implemented by SoC integration
 * code.
 *
 * @return SoC specific pin configuration
 */
int stm32_get_pin_config(int pin, int func);

/**
 * @brief helper for mapping IO port to its clock subsystem
 *
 * @param port  IO port
 *
 * Map given IO @port to corresponding clock subsystem. The returned
 * clock subsystem ID must suitable for passing as parameter to
 * clock_control_on(). Implement this function at the SoC level.
 *
 * @return clock subsystem ID
 */
clock_control_subsys_t stm32_get_port_clock(int port);

/**
 * @brief helper for configuration of IO pin
 *
 * @param pin IO pin, STM32PIN() encoded
 * @param func IO function encoded
 * @param clk clock control device, for enabling/disabling clock gate
 * for the port
 */
int _pinmux_stm32_set(u32_t pin, u32_t func,
		      struct device *clk);

/**
 * @brief helper for obtaining pin configuration for the board
 *
 * @param[out] pins  set to the number of pins in the array
 *
 * Obtain pin assignment/configuration for current board. This call
 * needs to be implemented at the board integration level. After
 * restart all pins are already configured as GPIO and can be skipped
 * in the configuration array. Pin numbers in @pin_num field are
 * STM32PIN() encoded.
 *
 * @return array of pin assignments
 */
void stm32_setup_pins(const struct pin_config *pinconf,
		      size_t pins);

/* common pinmux device name for all STM32 chips */
#define STM32_PINMUX_NAME "stm32-pinmux"

#ifdef CONFIG_SOC_SERIES_STM32F1X
#include "pinmux_stm32f1.h"
#elif CONFIG_SOC_SERIES_STM32F3X
#include "pinmux_stm32f3.h"
#elif CONFIG_SOC_SERIES_STM32F4X
#include "pinmux_stm32f4.h"
#elif CONFIG_SOC_SERIES_STM32L4X
#include "pinmux_stm32l4x.h"
#endif

#endif	/* _STM32_PINMUX_H_ */
