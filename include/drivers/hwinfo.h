/**
 * @file
 *
 * @brief Public APIs to get device Information.
 */

/*
 * Copyright (c) 2018 Alexander Wachter
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DRIVERS_HWINFO_H_
#define ZEPHYR_INCLUDE_DRIVERS_HWINFO_H_

/**
 * @brief Hardware Information Interface
 * @defgroup hwinfo_interface Hardware Info Interface
 * @ingroup io_interfaces
 * @{
 */

#include <zephyr/types.h>
#include <sys/types.h>
#include <stddef.h>
#include <errno.h>
#include <kernel.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RESET_PIN				BIT(0)
#define RESET_SOFTWARE				BIT(1)
#define RESET_BROWNOUT				BIT(2)
#define RESET_POR				BIT(3)
#define RESET_WATCHDOG				BIT(4)
#define RESET_DEBUG				BIT(5)
#define RESET_SECURITY				BIT(6)
#define RESET_LOW_POWER_WAKE			BIT(7)
#define RESET_CPU_LOCKUP			BIT(8)
#define RESET_PARITY				BIT(9)

/**
 * @brief Copy the device id to a buffer
 *
 * This routine copies "length" number of bytes of the device ID to the buffer.
 * If the device ID is smaller then length, the rest of the buffer is left unchanged.
 * The ID depends on the hardware and is not guaranteed unique.
 *
 * Drivers are responsible for ensuring that the ID data structure is a
 * sequence of bytes.  The returned ID value is not supposed to be interpreted
 * based on vendor-specific assumptions of byte order. It should express the
 * identifier as a raw byte sequence, doing any endian conversion necessary so
 * that a hex representation of the bytes produces the intended serial number.
 *
 * @param buffer  Buffer to write the ID to.
 * @param length  Max length of the buffer.
 *
 * @retval size of the device ID copied.
 * @retval -ENOTSUP if there is no implementation for the particular device.
 * @retval any negative value on driver specific errors.
 */
__syscall ssize_t hwinfo_get_device_id(uint8_t *buffer, size_t length);

ssize_t z_impl_hwinfo_get_device_id(uint8_t *buffer, size_t length);

/**
 * @brief      Retrieve cause of device reset.
 *
 * @param      cause  OR'd `reset_cause` flags
 *
 * This routine retrieves the flags that indicate why the device was reset.
 *
 * On some platforms the reset cause flags accumulate between successive resets
 * and this routine may return multiple flags indicating all reset causes
 * since the device was powered on. If you need to retrieve the cause only for
 * the most recent reset call `hwinfo_clear_reset_cause` after calling this
 * routine to clear the hardware flags before the next reset event.
 *
 * Successive calls to this routine will return the same value, unless
 * `hwinfo_clear_reset_cause` has been called.
 *
 * @retval zero if successful.
 * @retval -ENOTSUP if there is no implementation for the particular device.
 * @retval any negative value on driver specific errors.
 */
__syscall int hwinfo_get_reset_cause(uint32_t *cause);

int z_impl_hwinfo_get_reset_cause(uint32_t *cause);

/**
 * @brief      Clear cause of device reset.
 *
 * Clears reset cause flags.
 *
 * @retval zero if successful.
 * @retval -ENOTSUP if there is no implementation for the particular device.
 * @retval any negative value on driver specific errors.
 */
__syscall int hwinfo_clear_reset_cause(void);

int z_impl_hwinfo_clear_reset_cause(void);

/**
 * @brief      Get supported reset cause flags
 *
 * @param      supported  OR'd `reset_cause` flags that are supported
 *
 * Retrieves all `reset_cause` flags that are supported by this device.
 *
 * @retval zero if successful.
 * @retval -ENOTSUP if there is no implementation for the particular device.
 * @retval any negative value on driver specific errors.
 */
__syscall int hwinfo_get_supported_reset_cause(uint32_t *supported);

int z_impl_hwinfo_get_supported_reset_cause(uint32_t *supported);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#include <syscalls/hwinfo.h>

#endif /* ZEPHYR_INCLUDE_DRIVERS_HWINFO_H_ */
