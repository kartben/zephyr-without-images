
/*
 * Copyright (c) 2015 Intel Corporation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _DEVICE_H_
#define _DEVICE_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @def DEVICE_INIT
 *
 * @brief create device object and set it up for boot time initialization
 *
 * @details This macro defines a device object that is automatically
 * configured by the kernel during system initialization.
 *
 * @param dev_name Device name.
 *
 * @param drv_name The name this instance of the driver exposes to
 * the system.
 *
 * @param init_fn Address to the init function of the driver.
 *
 * @param data Pointer to the device's configuration data.
 *
 * @param cfg_info The address to the structure containing the
 * configuration information for this instance of the driver.
 *
 * @param level The initialization level at which configuration occurs.
 * Must be one of the following symbols, which are listed in the order
 * they are performed by the kernel:
 *
 * PRIMARY: Used for devices that have no dependencies, such as those
 * that rely solely on hardware present in the processor/SOC. These devices
 * cannot use any kernel services during configuration, since they are not
 * yet available.
 *
 * SECONDARY: Used for devices that rely on the initialization of devices
 * initialized as part of the PRIMARY level. These devices cannot use any
 * kernel services during configuration, since they are not yet available.
 *
 * NANOKERNEL: Used for devices that require nanokernel services during
 * configuration.
 *
 * MICROKERNEL: Used for devices that require microkernel services during
 * configuration.
 *
 * APPLICATION: Used for application components (i.e. non-kernel components)
 * that need automatic configuration. These devices can use all services
 * provided by the kernel during configuration.
 *
 * @param prio The initialization priority of the device, relative to
 * other devices of the same initialization level. Specified as an integer
 * value in the range 0 to 99; lower values indicate earlier initialization.
 * Must be a decimal integer literal without leading zeroes or sign (e.g. 32),
 * or an equivalent symbolic name (e.g. #define MY_INIT_PRIO 32); symbolic
 * expressions are *not* permitted
 * (e.g. CONFIG_KERNEL_INIT_PRIORITY_DEFAULT + 5).
 */

#define DEVICE_INIT(dev_name, drv_name, init_fn, data, cfg_info, level, prio) \
	\
	static struct device_config __config_##dev_name __used \
	__attribute__((__section__(".devconfig.init"))) = { \
		.name = drv_name, .init = (init_fn), \
		.config_info = (cfg_info) \
	}; \
	\
	static struct device (__device_##dev_name) __used \
	__attribute__((__section__(".init_" #level STRINGIFY(prio)))) = { \
		 .config = &(__config_##dev_name), \
		 .driver_data = data \
	}

/**
 * @def DEVICE_NAME_GET
 *
 * @brief Expands to the full name of a global device object
 *
 * @details Return the full name of a device object symbol created by
 * DEVICE_INIT(), using the @dev_name provided to DEVICE_INIT().
 *
 * It is meant to be used for declaring extern symbols pointing on device
 * objects before using the DEVICE_GET macro to get the device object.
 *
 * @param name The same as dev_name provided to DEVICE_INIT()
 *
 * @return The exanded name of the device object created by DEVICE_INIT()
 */
#define DEVICE_NAME_GET(name) (_CONCAT(__device_, name))

/**
 * @def DEVICE_GET
 *
 * @brief Obtain a pointer to a device object by name
 *
 * @details Return the address of a device object created by
 * DEVICE_INIT(), using the @dev_name provided to DEVICE_INIT().
 *
 * @param name The same as dev_name provided to DEVICE_INIT()
 *
 * @return A pointer to the device object created by DEVICE_INIT()
 */
#define DEVICE_GET(name) (&DEVICE_NAME_GET(name))

/* Common Error Codes devices can provide */
#define DEV_OK			0  /* No error */
#define DEV_FAIL		1 /* General operation failure */
#define DEV_INVALID_OP		2 /* Invalid operation */
#define DEV_INVALID_CONF	3 /* Invalid configuration */
#define DEV_USED		4 /* Device controller in use */
#define DEV_NO_ACCESS		5 /* Controller not accessible */
#define DEV_NO_SUPPORT		6 /* Device type not supported */
#define DEV_NOT_CONFIG		7 /* Device not configured */

struct device;

/**
 * @brief Static device information (In ROM) Per driver instance
 * @param name name of the device
 * @param init init function for the driver
 * @param config_info address of driver instance config information
 */
struct device_config {
	char	*name;
	int (*init)(struct device *device);
	void *config_info;
};

/**
 * @brief Runtime device structure (In memory) Per driver instance
 * @param device_config Build time config information
 * @param driver_api pointer to structure containing the API functions for
 * the device type. This pointer is filled in by the driver at init time.
 * @param driver_data river instance data. For driver use only
 */
struct device {
	struct device_config *config;
	void *driver_api;
	void *driver_data;
};

void _sys_device_do_config_level(int level);
struct device* device_get_binding(char *name);

/**
 * Synchronous calls API
 */

#include <stdbool.h>
#include <nanokernel.h>
#ifdef CONFIG_MICROKERNEL
#include <microkernel.h>
#endif


/**
 * Specific type for synchronizing calls among the 2 possible contexts
 */
typedef struct {
	/** Nanokernel semaphore used for fiber context */
	struct nano_sem f_sem;
#ifdef CONFIG_MICROKERNEL
	/** Microkernel semaphore used for task context */
	struct _k_sem_struct _t_sem;
	ksem_t t_sem;
	bool waiter_is_task;
#endif
} device_sync_call_t;


/**
 * @brief Initialize the context-dependent synchronization data
 *
 * @param sync A pointer to a valid device_sync_call_t
 */
static inline void device_sync_call_init(device_sync_call_t *sync)
{
	nano_sem_init(&sync->f_sem);
#ifdef CONFIG_MICROKERNEL
	sync->_t_sem.waiters = NULL;
	sync->_t_sem.level = sync->_t_sem.count = 0;
	sync->t_sem = (ksem_t)&sync->_t_sem;
	sync->waiter_is_task = false;
#endif
}

#ifdef CONFIG_MICROKERNEL

/**
 * @brief Wait for the isr to complete the synchronous call
 * Note: In a microkernel built this function will take care of the caller
 * context and thus use the right attribute to handle the synchronization.
 *
 * @param sync A pointer to a valid device_sync_call_t
 */
static inline void device_sync_call_wait(device_sync_call_t *sync)
{
	if ((sys_execution_context_type_get() == NANO_CTX_TASK) &&
	    (task_priority_get() < CONFIG_NUM_TASK_PRIORITIES - 1)) {
		sync->waiter_is_task = true;
		task_sem_take(sync->t_sem, TICKS_UNLIMITED);
	} else {
		sync->waiter_is_task = false;
		nano_sem_take(&sync->f_sem, TICKS_NONE);
	}
}

/**
 * @brief Signal the waiter about synchronization completion
 * Note: In a microkernel built this function will take care of the waiter
 * context and thus use the right attribute to signale the completion.
 *
 * @param sync A pointer to a valid device_sync_call_t
 */
static inline void device_sync_call_complete(device_sync_call_t *sync)
{
	static void (*func[3])(ksem_t sema) = {
		isr_sem_give,
		fiber_sem_give,
		task_sem_give
	};
	if (sync->waiter_is_task) {
		func[sys_execution_context_type_get()](sync->t_sem);
	} else {
		nano_sem_give(&sync->f_sem);
	}
}

#else

/**
 * @brief Wait for the isr to complete the synchronous call
 * Note: It will simply wait on the internal semaphore.
 *
 * @param sync A pointer to a valid device_sync_call_t
 */
static inline void device_sync_call_wait(device_sync_call_t *sync)
{
	nano_sem_take(&sync->f_sem, TICKS_UNLIMITED);
}

/**
 * @brief Signal the waiter about synchronization completion
 * Note: It will simply release the internal semaphore
 *
 * @param sync A pointer to a valid device_sync_call_t
 */
static inline void device_sync_call_complete(device_sync_call_t *sync)
{
	nano_sem_give(&sync->f_sem);
}

#endif /* CONFIG_MICROKERNEL || CONFIG_NANOKERNEL */

#ifdef __cplusplus
}
#endif

#endif /* _DEVICE_H_ */
