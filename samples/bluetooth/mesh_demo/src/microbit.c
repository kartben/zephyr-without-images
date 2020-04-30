/* microbit.c - BBC micro:bit specific hooks */

/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <drivers/gpio.h>
#include <board.h>
#include <soc.h>
#include <sys/printk.h>
#include <ctype.h>
#include <drivers/gpio.h>
#include <drivers/pwm.h>

#include <display/mb_display.h>

#include <bluetooth/mesh.h>

#include "board.h"

#define SCROLL_SPEED   300

#define BUZZER_PIN     EXT_P0_GPIO_PIN
#define BEEP_DURATION  K_MSEC(60)

#define SEQ_PER_BIT  976
#define SEQ_PAGE     (NRF_FICR->CODEPAGESIZE * (NRF_FICR->CODESIZE - 1))
#define SEQ_MAX      (NRF_FICR->CODEPAGESIZE * 8 * SEQ_PER_BIT)

static const struct device *gpio;
static const struct device *nvm;
static const struct device *pwm;

static struct k_work button_work;

static void button_send_pressed(struct k_work *work)
{
	printk("button_send_pressed()\n");
	board_button_1_pressed();
}

static void button_pressed(const struct device *dev, struct gpio_callback *cb,
			   uint32_t pins)
{
	struct mb_display *disp = mb_display_get();

	if (pins & BIT(DT_GPIO_PIN(DT_ALIAS(sw0), gpios))) {
		k_work_submit(&button_work);
	} else {
		uint16_t target = board_set_target();

		if (target > 0x0009) {
			mb_display_print(disp, MB_DISPLAY_MODE_SINGLE,
					 2 * MSEC_PER_SEC, "A");
		} else {
			mb_display_print(disp, MB_DISPLAY_MODE_SINGLE,
					 2 * MSEC_PER_SEC, "%X", (target & 0xf));
		}
	}
}

static const struct {
	char  note;
	uint32_t period;
	uint32_t sharp;
} period_map[] = {
	{ 'C',  3822,  3608 },
	{ 'D',  3405,  3214 },
	{ 'E',  3034,  3034 },
	{ 'F',  2863,  2703 },
	{ 'G',  2551,  2407 },
	{ 'A',  2273,  2145 },
	{ 'B',  2025,  2025 },
};

static uint32_t get_period(char note, bool sharp)
{
	int i;

	if (note == ' ') {
		return 0;
	}

	for (i = 0; i < ARRAY_SIZE(period_map); i++) {
		if (period_map[i].note != note) {
			continue;
		}

		if (sharp) {
			return period_map[i].sharp;
		} else {
			return period_map[i].period;
		}
	}

	return 1500;
}

void board_play_tune(const char *str)
{
	while (*str) {
		uint32_t period, duration = 0U;

		while (*str && !isdigit((unsigned char)*str)) {
			str++;
		}

		while (isdigit((unsigned char)*str)) {
			duration *= 10U;
			duration += *str - '0';
			str++;
		}

		if (!*str) {
			break;
		}

		if (str[1] == '#') {
			period = get_period(*str, true);
			str += 2;
		} else {
			period = get_period(*str, false);
			str++;
		}

		if (period) {
			pwm_pin_set_usec(pwm, BUZZER_PIN, period, period / 2U,
					 0);
		}

		k_sleep(K_MSEC(duration));

		/* Disable the PWM */
		pwm_pin_set_usec(pwm, BUZZER_PIN, 0, 0, 0);
	}
}

void board_heartbeat(uint8_t hops, uint16_t feat)
{
	struct mb_display *disp = mb_display_get();
	const struct mb_image hops_img[] = {
		MB_IMAGE({ 1, 1, 1, 1, 1 },
			 { 1, 1, 1, 1, 1 },
			 { 1, 1, 1, 1, 1 },
			 { 1, 1, 1, 1, 1 },
			 { 1, 1, 1, 1, 1 }),
		MB_IMAGE({ 1, 1, 1, 1, 1 },
			 { 1, 1, 1, 1, 1 },
			 { 1, 1, 0, 1, 1 },
			 { 1, 1, 1, 1, 1 },
			 { 1, 1, 1, 1, 1 }),
		MB_IMAGE({ 1, 1, 1, 1, 1 },
			 { 1, 0, 0, 0, 1 },
			 { 1, 0, 0, 0, 1 },
			 { 1, 0, 0, 0, 1 },
			 { 1, 1, 1, 1, 1 }),
		MB_IMAGE({ 1, 1, 1, 1, 1 },
			 { 1, 0, 0, 0, 1 },
			 { 1, 0, 0, 0, 1 },
			 { 1, 0, 0, 0, 1 },
			 { 1, 1, 1, 1, 1 }),
		MB_IMAGE({ 1, 0, 1, 0, 1 },
			 { 0, 0, 0, 0, 0 },
			 { 1, 0, 0, 0, 1 },
			 { 0, 0, 0, 0, 0 },
			 { 1, 0, 1, 0, 1 })
	};

	printk("%u hops\n", hops);

	if (hops) {
		hops = MIN(hops, ARRAY_SIZE(hops_img));
		mb_display_image(disp, MB_DISPLAY_MODE_SINGLE, 2 * MSEC_PER_SEC,
				 &hops_img[hops - 1], 1);
	}
}

void board_other_dev_pressed(uint16_t addr)
{
	struct mb_display *disp = mb_display_get();

	printk("board_other_dev_pressed(0x%04x)\n", addr);

	mb_display_print(disp, MB_DISPLAY_MODE_SINGLE, 2 * MSEC_PER_SEC, "%X",
			 (addr & 0xf));
}

void board_attention(bool attention)
{
	struct mb_display *disp = mb_display_get();
	static const struct mb_image attn_img[] = {
		MB_IMAGE({ 0, 0, 0, 0, 0 },
			 { 0, 0, 0, 0, 0 },
			 { 0, 0, 1, 0, 0 },
			 { 0, 0, 0, 0, 0 },
			 { 0, 0, 0, 0, 0 }),
		MB_IMAGE({ 0, 0, 0, 0, 0 },
			 { 0, 1, 1, 1, 0 },
			 { 0, 1, 1, 1, 0 },
			 { 0, 1, 1, 1, 0 },
			 { 0, 0, 0, 0, 0 }),
		MB_IMAGE({ 1, 1, 1, 1, 1 },
			 { 1, 1, 1, 1, 1 },
			 { 1, 1, 0, 1, 1 },
			 { 1, 1, 1, 1, 1 },
			 { 1, 1, 1, 1, 1 }),
		MB_IMAGE({ 1, 1, 1, 1, 1 },
			 { 1, 0, 0, 0, 1 },
			 { 1, 0, 0, 0, 1 },
			 { 1, 0, 0, 0, 1 },
			 { 1, 1, 1, 1, 1 }),
	};

	if (attention) {
		mb_display_image(disp,
				 MB_DISPLAY_MODE_DEFAULT | MB_DISPLAY_FLAG_LOOP,
				 150, attn_img, ARRAY_SIZE(attn_img));
	} else {
		mb_display_stop(disp);
	}
}

static void configure_button(void)
{
	static struct gpio_callback button_cb;

	k_work_init(&button_work, button_send_pressed);

	gpio = device_get_binding(DT_GPIO_LABEL(DT_ALIAS(sw0), gpios));

	gpio_pin_configure(gpio, DT_GPIO_PIN(DT_ALIAS(sw0), gpios),
			   GPIO_INPUT | DT_GPIO_FLAGS(DT_ALIAS(sw0), gpios));
	gpio_pin_interrupt_configure(gpio, DT_GPIO_PIN(DT_ALIAS(sw0), gpios),
				     GPIO_INT_EDGE_TO_ACTIVE);

	gpio_pin_configure(gpio, DT_GPIO_PIN(DT_ALIAS(sw1), gpios),
			   GPIO_INPUT | DT_GPIO_FLAGS(DT_ALIAS(sw1), gpios));
	gpio_pin_interrupt_configure(gpio, DT_GPIO_PIN(DT_ALIAS(sw1), gpios),
				     GPIO_INT_EDGE_TO_ACTIVE);

	gpio_init_callback(&button_cb, button_pressed,
			   BIT(DT_GPIO_PIN(DT_ALIAS(sw0), gpios)) |
			   BIT(DT_GPIO_PIN(DT_ALIAS(sw1), gpios)));
	gpio_add_callback(gpio, &button_cb);
}

void board_init(uint16_t *addr)
{
	struct mb_display *disp = mb_display_get();

	nvm = device_get_binding(DT_CHOSEN_ZEPHYR_FLASH_CONTROLLER_LABEL);
	pwm = device_get_binding(DT_LABEL(DT_INST(0, nordic_nrf_sw_pwm)));

	*addr = NRF_UICR->CUSTOMER[0];
	if (!*addr || *addr == 0xffff) {
#if defined(NODE_ADDR)
		*addr = NODE_ADDR;
#else
		*addr = 0x0b0c;
#endif
	}

	mb_display_print(disp, MB_DISPLAY_MODE_DEFAULT, SCROLL_SPEED,
			 "0x%04x", *addr);

	configure_button();
}
