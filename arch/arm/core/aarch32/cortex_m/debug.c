/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief ARM Cortex-M debug monitor functions interface based on DWT
 *
 */

#include <device.h>
#include <aarch32/cortex_m/dwt.h>

/**
 * @brief Assess whether a debug monitor event should be treated as an error
 *
 * This routine checks the status of a debug monitor ()exception, and
 * evaluates whether this needs to be considered as a processor error.
 *
 * @return true if the DM exception is a processor error, otherwise false
 */
bool z_arm_debug_monitor_event_error_check(void)
{
#if defined(CONFIG_CORTEX_M_DEBUG_NULL_POINTER_EXCEPTION_DETECTION_DWT)
	/* Assess whether this debug exception was triggered
	 * as a result of a null pointer (R/W) dereferencing.
	 */
	if (SCB->DFSR & SCB_DFSR_DWTTRAP_Msk) {
		/* Debug event generated by the DWT unit */
		if (DWT->FUNCTION0 & DWT_FUNCTION_MATCHED_Msk) {
			/* DWT Comparator match used for */
			printk("Null-pointer exception?\n");
		}
		__ASSERT((DWT->FUNCTION0 & DWT_FUNCTION_MATCHED_Msk) == 0,
			"MATCHED flag should have been cleared on read.");

		return true;
	} else if (SCB->DFSR & SCB_DFSR_BKPT_Msk) {
		/* Treat BKPT events as an error as well (since they
		 * would mean the system would be stuck in an infinite loop).
		 */
		return true;
	}
#endif /* CONFIG_CORTEX_M_DEBUG_NULL_POINTER_EXCEPTION_DETECTION_DWT */
	return false;
}

#if defined(CONFIG_CORTEX_M_DEBUG_NULL_POINTER_EXCEPTION_DETECTION_DWT)

static int z_arm_debug_enable_null_pointer_detection(const struct device *arg)
{
	ARG_UNUSED(arg);

	z_arm_dwt_init();
	z_arm_dwt_enable_debug_monitor();

	/* Enable null pointer detection by monitoring R/W access to the
	 * memory area 0x0 - <size> that is (or was intentionally left)
	 * unused by the system.
	 */

	/* ASSERT that we have the comparator needed for the implementation */
	if (((DWT->CTRL & DWT_CTRL_NUMCOMP_Msk) >> DWT_CTRL_NUMCOMP_Pos) < 1) {
		__ASSERT(0, "on board DWT does not support the feature\n");
		return -EINVAL;
	}

	/* Use comparator 0, R/W access check */
	DWT->COMP0 = 0;

	DWT->FUNCTION0 = (0x7 << DWT_FUNCTION_FUNCTION_Pos) &
		DWT_FUNCTION_FUNCTION_Msk;


	/* Set mask according to the desired size */
	DWT->MASK0 = 32 - __builtin_clzl(
		CONFIG_CORTEX_M_DEBUG_NULL_POINTER_EXCEPTION_PAGE_SIZE - 1);

	return 0;
}

SYS_INIT(z_arm_debug_enable_null_pointer_detection, PRE_KERNEL_1,
	 CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);

#endif /* CONFIG_CORTEX_M_DEBUG_NULL_POINTER_EXCEPTION_DETECTION_DWT */
