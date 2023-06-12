/*
 * Copyright (c) 2019, Texas Instruments Incorporated
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * pinmux.c
 *
 * configure the device pins for different peripheral signals
 */

/*
 * This file was automatically generated on 7/21/2014 at 3:06:20 PM
 * by TI PinMux version 3.0.334
 * (Then modified to meet Zephyr coding style)
 */

/*
 * TI Recommends use of the PinMux utility to ensure consistent configuration
 * of pins: http://processors.wiki.ti.com/index.php/TI_PinMux_Tool
 *
 * Zephyr GPIO API however allows runtime configuration by applications.
 *
 * For the TI CC32XX port we leverage this output file
 * from the PinMux tool, and guard sections based on Kconfig variables.
 *
 * The individual (uart/gpio) driver init/configuration functions
 * therefore assume pinmux initialization is done here rather in the drivers
 * at runtime.
 */

#include <zephyr/init.h>

#include <inc/hw_types.h>
#include <inc/hw_memmap.h>
#include <inc/hw_gpio.h>
#include <driverlib/pin.h>
#include <driverlib/rom.h>
#include <driverlib/rom_map.h>
#include <driverlib/gpio.h>
#include <driverlib/prcm.h>
#include <driverlib/i2c.h>

/* Defines taken from SimpleLink SDK's I2CCC32XX.h: */
/*
 *  Macros defining possible I2C signal pin mux options
 *
 *  The bits in the pin mode macros are as follows:
 *  The lower 8 bits of the macro refer to the pin, offset by 1, to match
 *  driverlib pin defines.  For example, I2C_CC32XX_PIN_01_I2C_SCL & 0xff = 0,
 *  which equals PIN_01 in driverlib pin.h.  By matching the PIN_xx defines in
 *  driverlib pin.h, we can pass the pin directly to the driverlib functions.
 *  The upper 8 bits of the macro correspond to the pin mux config mode
 *  value for the pin to operate in the I2C mode.  For example, pin 1 is
 *  configured with mode 1 to operate as I2C_SCL.
 */
#define I2C_CC32XX_PIN_01_I2C_SCL  0x100  /*!< PIN 1 is used for I2C_SCL */
#define I2C_CC32XX_PIN_02_I2C_SDA  0x101  /*!< PIN 2 is used for I2C_SDA */
#define I2C_CC32XX_PIN_03_I2C_SCL  0x502  /*!< PIN 3 is used for I2C_SCL */
#define I2C_CC32XX_PIN_04_I2C_SDA  0x503  /*!< PIN 4 is used for I2C_SDA */
#define I2C_CC32XX_PIN_05_I2C_SCL  0x504  /*!< PIN 5 is used for I2C_SCL */
#define I2C_CC32XX_PIN_06_I2C_SDA  0x505  /*!< PIN 6 is used for I2C_SDA */
#define I2C_CC32XX_PIN_16_I2C_SCL  0x90F  /*!< PIN 16 is used for I2C_SCL */
#define I2C_CC32XX_PIN_17_I2C_SDA  0x910  /*!< PIN 17 is used for I2C_SDA */

int pinmux_initialize(void)
{

#ifdef CONFIG_UART_CC32XX
	/* Configure PIN_55 for UART0 UART0_TX */
	MAP_PinTypeUART(PIN_55, PIN_MODE_3);

	/* Configure PIN_57 for UART0 UART0_RX */
	MAP_PinTypeUART(PIN_57, PIN_MODE_3);
#endif

#ifdef CONFIG_I2C_CC32XX
	{
		unsigned long pin;
		unsigned long mode;

		pin = I2C_CC32XX_PIN_01_I2C_SCL & 0xff;
		mode = (I2C_CC32XX_PIN_01_I2C_SCL >> 8) & 0xff;
		MAP_PinTypeI2C(pin, mode);

		pin = I2C_CC32XX_PIN_02_I2C_SDA & 0xff;
		mode = (I2C_CC32XX_PIN_02_I2C_SDA >> 8) & 0xff;
		MAP_PinTypeI2C(pin, mode);
	}
#endif

	return 0;
}

SYS_INIT(pinmux_initialize, PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
