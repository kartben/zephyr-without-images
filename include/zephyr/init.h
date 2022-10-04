/*
 * Copyright (c) 2015 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_INIT_H_
#define ZEPHYR_INCLUDE_INIT_H_

#include <stdint.h>
#include <stddef.h>

#include <zephyr/toolchain.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup sys_init System Initialization
 *
 * Zephyr offers an infrastructure to call initialization code before `main`.
 * Such initialization calls can be registered using SYS_INIT() or
 * SYS_INIT_NAMED() macros. By using a combination of initialization levels and
 * priorities init sequence can be adjusted as needed. The available
 * initialization levels are described, in order, below:
 *
 * - `EARLY`: Used very early in the boot process, right after entering the C
 *   domain (``z_cstart()``). This can be used in architectures and SoCs that
 *   extend or implement architecture code and use drivers or system services
 *   that have to be initialized before the Kernel calls any architecture
 *   specific initialization code.
 * - `PRE_KERNEL_1`: Executed in Kernel's initialization context, which uses
 *   the interrupt stack. At this point Kernel services are not yet available.
 * - `PRE_KERNEL_2`: Same as `PRE_KERNEL_1`.
 * - `POST_KERNEL`: Executed after Kernel is alive. From this point on, Kernel
 *   primitives can be used.
 * - `APPLICATION`: Executed just before application code (`main`).
 * - `SMP`: Only available if @kconfig{CONFIG_SMP} is enabled, specific for
 *   SMP.
 *
 * Initialization priority can take a value in the range of 0 to 99.
 *
 * @note The same infrastructure is used by devices.
 * @{
 */

struct device;

/** @brief Structure to store initialization entry information. */
struct init_entry {
	/**
	 * Initialization function for the init entry.
	 *
	 * @param dev Device pointer, NULL if not a device init function.
	 *
	 * @retval 0 On success
	 * @retval -errno If init fails.
	 */
	int (*init)(const struct device *dev);
	/**
	 * If the init entry belongs to a device, this fields stores a
	 * reference to it, otherwise it is set to NULL.
	 */
	const struct device *dev;
};

/** @cond INTERNAL_HIDDEN */

/**
 * @brief Construct a namespaced identifier for SYS_INIT instance
 *
 * @param _name Base unique name
 */
#define Z_SYS_NAME(_name) _CONCAT(sys_init_, _name)

/**
 * @brief Construct a namespaced identifier for a struct init_entry instance
 *
 * @param _entry_name Base unique name
 */
#define Z_INIT_ENTRY_NAME(_entry_name) _CONCAT(__init_, _entry_name)

/**
 * @brief Init entry section.
 *
 * Each init entry is placed in a section with a name crafted so that it allows
 * linker scripts to sort them according to the specified level/priority.
 */
#define Z_INIT_ENTRY_SECTION(level, prio) \
	__attribute__((__section__(".z_init_" #level STRINGIFY(prio)"_")))

/**
 * @brief Create an init entry object.
 *
 * This macro defines an init entry object that will be automatically
 * configured by the kernel during system initialization. Note that init
 * entries will not be accessible from user mode.
 *
 * @param _entry_name Init entry name.
 * @param _init_fn Init function.
 * @param _device Device instance (optional).
 * @param _level Initialization level.
 * @param prio Initialization priority within @p _level.
 *
 * @see SYS_INIT()
 */
#define Z_INIT_ENTRY_DEFINE(_entry_name, _init_fn, _device, _level, _prio)	\
	static const Z_DECL_ALIGN(struct init_entry)			\
		Z_INIT_ENTRY_NAME(_entry_name) __used __noasan			\
		Z_INIT_ENTRY_SECTION(_level, _prio) = { 			\
		.init = (_init_fn),					\
		.dev = (_device),					\
	}

/** @endcond */

/**
 * @brief Register an initialization function.
 *
 * The function will be called during system initialization according to the
 * given level and priority.
 *
 * @param _init_fn Initialization function.
 * @param _level Initialization level. Allowed tokens: `EARLY`, `PRE_KERNEL_1`,
 * `PRE_KERNEL_2`, `POST_KERNEL`, `APPLICATION` and `SMP` if
 * @kconfig{CONFIG_SMP} is enabled.
 * @param _prio Initialization priority within @p _level. Note that it must be a
 * decimal integer literal without leading zeroes or sign (e.g. `32`), or an
 * equivalent symbolic name (e.g. `#define MY_INIT_PRIO 32`); symbolic
 * expressions are **not** permitted (e.g.
 * `CONFIG_KERNEL_INIT_PRIORITY_DEFAULT + 5`).
 */
#define SYS_INIT(_init_fn, _level, _prio)					\
	SYS_INIT_NAMED(_init_fn, _init_fn, _level, _prio)

/**
 * @brief Register an initialization function (named).
 *
 * @note This macro can be used for cases where the multiple init calls use the
 * same init function.
 *
 * @param _name Unique name for SYS_INIT entry.
 * @param _init_fn See SYS_INIT().
 * @param _level See SYS_INIT().
 * @param _prio See SYS_INIT().
 *
 * @see SYS_INIT()
 */
#define SYS_INIT_NAMED(_name, _init_fn, _level, _prio)				\
	Z_INIT_ENTRY_DEFINE(Z_SYS_NAME(_name), _init_fn, NULL, _level, _prio)

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_INIT_H_ */
