/*
 * Copyright (c) 2018 Synopsys.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <misc/printk.h>
#include <soc.h>

#if defined(CONFIG_SOC_NSIM_SEM)
#define NORMAL_FIRMWARE_ENTRY 0x40000
#elif defined(CONFIG_SOC_EMSK)
#define NORMAL_FIRMWARE_ENTRY 0x20000
#endif


#define STACKSIZE 1024
#define PRIORITY 7
#define SLEEPTIME 1000


void threadA(void *dummy1, void *dummy2, void *dummy3)
{
	ARG_UNUSED(dummy1);
	ARG_UNUSED(dummy2);
	ARG_UNUSED(dummy3);


	printk("Go to normal application\n");

	arc_go_to_normal(*((u32_t *)(NORMAL_FIRMWARE_ENTRY)));

	printk("should not come here\n");

}

K_THREAD_DEFINE(thread_a, STACKSIZE, threadA, NULL, NULL, NULL,
		PRIORITY, 0, K_NO_WAIT);


void main(void)
{
	/* necessary configuration before go to normal */
	s32_t i = 0;

	/* allocate timer 0 and timer1 to normal mode */
	z_arc_v2_irq_uinit_secure_set(IRQ_TIMER0, 0);
	z_arc_v2_irq_uinit_secure_set(IRQ_TIMER1, 0);

	/* disable the secure interrupts for debug purpose*/
	/* _arc_v2_irq_unit_int_disable(IRQ_S_TIMER0); */

	while (1) {
		printk("I am the %s thread in secure world: %d\n",
				 __func__, i++);
		k_sleep(SLEEPTIME);
	}
}
