/*
 * Copyright (c) 2018 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>
#include <kernel_structs.h>
#include <ksched.h>
#include <cmsis_os2.h>

extern u32_t z_tick_get_32(void);

/**
 * @brief Get RTOS Kernel Information.
 */
osStatus_t osKernelGetInfo(osVersion_t *version, char *id_buf, uint32_t id_size)
{
	char os_str[] = "Zephyr VMM.mm.pp";

	if (version != NULL) {
		version->api    = sys_kernel_version_get();
		version->kernel = sys_kernel_version_get();
	}

	sprintf(os_str, "Zephyr V%2d.%2d.%2d",
		SYS_KERNEL_VER_MAJOR(version->kernel),
		SYS_KERNEL_VER_MINOR(version->kernel),
		SYS_KERNEL_VER_PATCHLEVEL(version->kernel));

	if ((id_buf != NULL) && (id_size > strlen(os_str))) {
		memcpy(id_buf, os_str, strlen(os_str)+1);
	}

	return (osOK);
}

/**
 * @brief Lock the RTOS Kernel scheduler.
 */
int32_t osKernelLock(void)
{
	int temp = _current->base.sched_locked;

	if (k_is_in_isr()) {
		return osErrorISR;
	}

	k_sched_lock();

	return temp;
}

/**
 * @brief Unlock the RTOS Kernel scheduler.
 */
int32_t osKernelUnlock(void)
{
	int temp = _current->base.sched_locked;

	if (k_is_in_isr()) {
		return osErrorISR;
	}

	k_sched_unlock();

	return temp;
}

/**
 * @brief Restore the RTOS Kernel scheduler lock state.
 */
int32_t osKernelRestoreLock(int32_t lock)
{
	_current->base.sched_locked = lock;

	if (k_is_in_isr()) {
		return osErrorISR;
	}

	if (lock < 0) {
		return 1; /* locked */
	} else {
		return 0; /* not locked */
	}
}

/**
 * @brief Get the RTOS kernel tick count.
 */
uint32_t osKernelGetTickCount(void)
{
	return z_tick_get_32();
}

/**
 * @brief Get the RTOS kernel tick frequency.
 */
uint32_t osKernelGetTickFreq(void)
{
	return CONFIG_SYS_CLOCK_TICKS_PER_SEC;
}

/**
 * @brief Get the RTOS kernel system timer count.
 */
uint32_t osKernelGetSysTimerCount(void)
{
	return k_cycle_get_32();
}

/**
 * @brief Get the RTOS kernel system timer frequency.
 */
uint32_t osKernelGetSysTimerFreq(void)
{
	return sys_clock_hw_cycles_per_sec();
}
