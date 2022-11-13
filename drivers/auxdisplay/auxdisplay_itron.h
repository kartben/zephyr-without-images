/*
 * Copyright (c) 2022-2023 Jamie McCrae
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef H_AUXDISPLAY_ITRON_
#define H_AUXDISPLAY_ITRON_

#define AUXDISPLAY_ITRON_BRIGHTNESS_MIN 1
#define AUXDISPLAY_ITRON_BRIGHTNESS_MAX 8

#define AUXDISPLAY_ITRON_CHARACTER_MIN 0x20
#define AUXDISPLAY_ITRON_CHARACTER_BACK_SPACE 0x08
#define AUXDISPLAY_ITRON_CHARACTER_TAB 0x09
#define AUXDISPLAY_ITRON_CHARACTER_LINE_FEED 0x0a
#define AUXDISPLAY_ITRON_CHARACTER_CARRIAGE_RETURN 0x0d

enum {
	AUXDISPLAY_ITRON_MODE_UNKNOWN = 0,
	AUXDISPLAY_ITRON_MODE_UART,
};

#endif /* H_AUXDISPLAY_ITRON_ */
