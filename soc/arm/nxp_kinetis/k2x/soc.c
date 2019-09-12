/*
 * Copyright (c) 2014-2015 Wind River Systems, Inc.
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright (c) 2018 Prevas A/S
 * Copyright (c) 2019 Thomas Burdick <thomas.burdick@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief System/hardware module for fsl_frdm_k22f platform
 *
 * This module provides routines to initialize and support board-level
 * hardware for the fsl_frdm_k22f platform.
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <soc.h>
#include <uart.h>
#include <fsl_common.h>
#include <fsl_clock.h>
#include <arch/cpu.h>
#include <cortex_m/exc.h>

#define PLLFLLSEL_MCGFLLCLK	(0)
#define PLLFLLSEL_MCGPLLCLK	(1)
#define PLLFLLSEL_IRC48MHZ	(3)

#define ER32KSEL_OSC32KCLK	(0)
#define ER32KSEL_RTC		(2)
#define ER32KSEL_LPO1KHZ	(3)

#define TIMESRC_OSCERCLK        (2)

static const osc_config_t oscConfig = {
	.freq = CONFIG_OSC_XTAL0_FREQ,
	.capLoad = 0,

#if defined(CONFIG_OSC_EXTERNAL)
	.workMode = kOSC_ModeExt,
#elif defined(CONFIG_OSC_LOW_POWER)
	.workMode = kOSC_ModeOscLowPower,
#elif defined(CONFIG_OSC_HIGH_GAIN)
	.workMode = kOSC_ModeOscHighGain,
#else
#error "An oscillator mode must be defined"
#endif

	.oscerConfig = {
		.enableMode = 0U, /* Disable external reference clock */
		.erclkDiv = 0U,
	},
};

static const mcg_pll_config_t pll0Config = {
	.enableMode = 0U,
	.prdiv = CONFIG_MCG_PRDIV0,
	.vdiv = CONFIG_MCG_VDIV0,
};

static const sim_clock_config_t simConfig = {
	.pllFllSel = PLLFLLSEL_MCGPLLCLK, /* PLLFLLSEL select PLL. */
	.er32kSrc = ER32KSEL_RTC,         /* ERCLK32K selection, use RTC. */
	.clkdiv1 = SIM_CLKDIV1_OUTDIV1(CONFIG_K22_CORE_CLOCK_DIVIDER - 1) |
		   SIM_CLKDIV1_OUTDIV2(CONFIG_K22_BUS_CLOCK_DIVIDER - 1) |
		   SIM_CLKDIV1_OUTDIV3(CONFIG_K22_FLEXBUS_CLOCK_DIVIDER - 1) |
		   SIM_CLKDIV1_OUTDIV4(CONFIG_K22_FLASH_CLOCK_DIVIDER - 1),
};

/**
 *
 * @brief Initialize the system clock
 *
 * This routine will configure the multipurpose clock generator (MCG) to
 * set up the system clock.
 * The MCG has nine possible modes, including Stop mode.  This routine assumes
 * that the current MCG mode is FLL Engaged Internal (FEI), as from reset.
 * It transitions through the FLL Bypassed External (FBE) and
 * PLL Bypassed External (PBE) modes to get to the desired
 * PLL Engaged External (PEE) mode and generate the maximum 120 MHz system
 * clock.
 *
 * @return N/A
 *
 */
static ALWAYS_INLINE void clkInit(void)
{
	CLOCK_SetSimSafeDivs();

	CLOCK_InitOsc0(&oscConfig);
	CLOCK_SetXtal0Freq(CONFIG_OSC_XTAL0_FREQ);


	CLOCK_SetInternalRefClkConfig(kMCG_IrclkEnable, kMCG_IrcSlow,
				      CONFIG_MCG_FCRDIV);

	/* Configure FLL external reference divider (FRDIV). */
	CLOCK_SetFllExtRefDiv(0);

	CLOCK_BootToPeeMode(kMCG_OscselOsc, kMCG_PllClkSelPll0, &pll0Config);

	CLOCK_SetSimConfig(&simConfig);

#if CONFIG_USB_KINETIS
	CLOCK_EnableUsbfs0Clock(kCLOCK_UsbSrcPll0,
				CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC);
#endif
}

/**
 *
 * @brief Perform basic hardware initialization
 *
 * Initialize the interrupt controller device drivers.
 * Also initialize the timer device driver, if required.
 *
 * @return 0
 */

static int fsl_frdm_k22f_init(struct device *arg)
{
	ARG_UNUSED(arg);

	unsigned int oldLevel; /* old interrupt lock level */
#if !defined(CONFIG_ARM_MPU)
#if defined(SYSMPU)
	u32_t temp_reg;
#endif
#endif /* !CONFIG_ARM_MPU */

	/* disable interrupts */
	oldLevel = irq_lock();

	/* release I/O power hold to allow normal run state */
	PMC->REGSC |= PMC_REGSC_ACKISO_MASK;

#if !defined(CONFIG_ARM_MPU)
	/*
	 * Disable memory protection and clear slave port errors.
	 * Note that the K22F does not implement the optional ARMv7-M memory
	 * protection unit (MPU), specified by the architecture (PMSAv7), in the
	 * Cortex-M4 core.  Instead, the processor includes its own MPU module.
	 */
#if defined(SYSMPU)
	temp_reg = SYSMPU->CESR;
	temp_reg &= ~SYSMPU_CESR_VLD_MASK;
	temp_reg |= SYSMPU_CESR_SPERR_MASK;
	SYSMPU->CESR = temp_reg;
#endif
#endif /* !CONFIG_ARM_MPU */

	/* Initialize PLL/system clock to 120 MHz */
	clkInit();

	/*
	 * install default handler that simply resets the CPU
	 * if configured in the kernel, NOP otherwise
	 */
	NMI_INIT();

	/* restore interrupt state */
	irq_unlock(oldLevel);
	return 0;
}

SYS_INIT(fsl_frdm_k22f_init, PRE_KERNEL_1, 0);
