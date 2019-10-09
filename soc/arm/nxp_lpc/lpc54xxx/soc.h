/*
 * Copyright (c) 2017, NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Board configuration macros for the nxp_lpc54114 platform
 *
 * This header file is used to specify and describe board-level aspects for the
 * 'nxp_lpc54114' platform.
 */

#ifndef _SOC__H_
#define _SOC__H_

#ifndef _ASMLANGUAGE
#include <sys/util.h>
#include <fsl_common.h>

/* Add include for DTS generated information */
#include <generated_dts_board.h>

#endif /* !_ASMLANGUAGE */

#define IOCON_PIO_DIGITAL_EN	0x80u
#define IOCON_PIO_FUNC0		0x00u
#define IOCON_PIO_FUNC1		0x01u
#define IOCON_PIO_FUNC2		0x02u
#define IOCON_PIO_INPFILT_OFF	0x0100u
#define IOCON_PIO_INV_DI	0x00u
#define IOCON_PIO_MODE_INACT	0x00u
#define IOCON_PIO_OPENDRAIN_DI	0x00u
#define IOCON_PIO_SLEW_STANDARD	0x00u
#define IOCON_PIO_MODE_PULLUP	0x10u
#define IOCON_PIO_MODE_PULLDOWN	0x08u

#endif /* _SOC__H_ */
