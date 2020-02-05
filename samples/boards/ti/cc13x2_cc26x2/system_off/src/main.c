/*
 * Copyright (c) 2019 Nordic Semiconductor ASA
 * Copyright (c) 2020 Linaro Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr.h>
#include <init.h>
#include <device.h>
#include <drivers/gpio.h>
#include <power/power.h>

#include <driverlib/ioc.h>


#define PORT    DT_ALIAS_SW0_GPIOS_CONTROLLER
#define PIN     DT_ALIAS_SW0_GPIOS_PIN
#define PULL_UP DT_ALIAS_SW0_GPIOS_FLAGS

#define BUSY_WAIT_S 5U
#define SLEEP_US 2000U
#define SLEEP_S     3U

extern void CC1352R1_LAUNCHXL_shutDownExtFlash(void);

void main(void)
{
	u32_t config, status;
	struct device *gpiob;

	printk("\n%s system off demo\n", CONFIG_BOARD);

	/* Shut off external flash to save power */
	CC1352R1_LAUNCHXL_shutDownExtFlash();

	/* Configure to generate PORT event (wakeup) on button 1 press. */
	gpiob = device_get_binding(PORT);
	if (!gpiob) {
		printk("error\n");
		return;
	}

	gpio_pin_configure(gpiob, PIN, GPIO_INPUT | PULL_UP);

	/* Set wakeup bits for button gpio */
	config = IOCPortConfigureGet(PIN);
	config |= IOC_WAKE_ON_LOW;
	IOCPortConfigureSet(PIN, IOC_PORT_GPIO, config);

	printk("Busy-wait %u s\n", BUSY_WAIT_S);
	k_busy_wait(BUSY_WAIT_S * USEC_PER_SEC);

	printk("Sleep %u us (IDLE)\n", SLEEP_US);
	k_usleep(SLEEP_US);

	printk("Sleep %u s (STANDBY)\n", SLEEP_S);
	k_sleep(K_SECONDS(SLEEP_S));

	printk("Entering system off (SHUTDOWN); press BUTTON1 to restart\n");

	/* Clear GPIO interrupt */
	status = GPIO_getEventMultiDio(GPIO_DIO_ALL_MASK);
	GPIO_clearEventMultiDio(status);

	/* Above we disabled entry to deep sleep based on duration of
	 * controlled delay.  Here we need to override that, then
	 * force a sleep so that the deep sleep takes effect.
	 */
	sys_pm_force_power_state(SYS_POWER_STATE_DEEP_SLEEP_1);
	k_sleep(K_MSEC(1));

	printk("ERROR: System off failed\n");
	while (true) {
		/* spin to avoid fall-off behavior */
	}
}
