/*
 * Copyright (c) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief EDAC API header file
 */

#ifndef ZEPHYR_INCLUDE_DRIVERS_EDAC_H_
#define ZEPHYR_INCLUDE_DRIVERS_EDAC_H_

#include <sys/types.h>

typedef int (*edac_api_inject_addr_set_f)(const struct device *dev,
					uint64_t addr);
typedef uint64_t (*edac_api_inject_addr_get_f)(const struct device *dev);

typedef int (*edac_api_inject_addr_mask_set_f)(const struct device *dev,
					     uint64_t mask);
typedef uint64_t (*edac_api_inject_addr_mask_get_f)(const struct device *dev);

typedef int (*edac_api_inject_ctrl_set_f)(const struct device *dev,
					  uint32_t ctrl);

typedef uint64_t (*edac_api_ecc_error_log_get_f)(const struct device *dev);
typedef void (*edac_api_ecc_error_log_clear_f)(const struct device *dev);

typedef uint64_t (*edac_api_parity_error_log_get_f)(const struct device *dev);
typedef void (*edac_api_parity_error_log_clear_f)(const struct device *dev);

typedef unsigned int (*edac_api_errors_cor_get_f)(const struct device *dev);
typedef unsigned int (*edac_api_errors_uc_get_f)(const struct device *dev);

typedef void (*edac_notify_callback_f)(const struct device *dev,
				       void *data);
typedef int (*edac_api_notify_cb_set_f)(const struct device *dev,
				      edac_notify_callback_f cb);

__subsystem struct edac_driver_api {
#if defined(CONFIG_EDAC_ERROR_INJECT)
	/* Error Injection API is disabled by default */
	edac_api_inject_addr_set_f inject_addr_set;
	edac_api_inject_addr_get_f inject_addr_get;
	edac_api_inject_addr_mask_set_f inject_addr_mask_set;
	edac_api_inject_addr_mask_get_f inject_addr_mask_get;
	edac_api_inject_ctrl_set_f inject_ctrl_set;
#endif /* CONFIG_EDAC_ERROR_INJECT */

	/* Error Logging  API */
	edac_api_ecc_error_log_get_f ecc_error_log_get;
	edac_api_ecc_error_log_clear_f ecc_error_log_clear;
	edac_api_parity_error_log_get_f parity_error_log_get;
	edac_api_parity_error_log_clear_f parity_error_log_clear;

	/* Error stats API */
	edac_api_errors_cor_get_f errors_cor_get;
	edac_api_errors_uc_get_f errors_uc_get;

	/* Notification callback API */
	edac_api_notify_cb_set_f notify_cb_set;
};

#if defined(CONFIG_EDAC_ERROR_INJECT)

/**
 * @brief Set injection address base
 *
 * @param dev Pointer to the device structure
 * @param addr Injection address base
 * @return 0 on success, error code otherwise
 */
static inline int edac_inject_addr_set(const struct device *dev,
				       uint64_t addr)
{
	const struct edac_driver_api *api =
		(const struct edac_driver_api *)dev->api;

	return api->inject_addr_set(dev, addr);
}

/**
 * @brief Get injection adrress base
 *
 * @param dev Pointer to the device structure
 * @return Injection address base
 */
static inline uint64_t edac_inject_addr_get(const struct device *dev)
{
	const struct edac_driver_api *api =
		(const struct edac_driver_api *)dev->api;

	return api->inject_addr_get(dev);

}

/**
 * @brief Set injection address mask
 *
 * @param dev Pointer to the device structure
 * @param addr Injection address mask
 * @return 0 on success, error code otherwise
 */
static inline int edac_inject_addr_mask_set(const struct device *dev,
					    uint64_t mask)
{
	const struct edac_driver_api *api =
		(const struct edac_driver_api *)dev->api;

	return api->inject_addr_mask_set(dev, mask);
}

/**
 * @brief Get injection adrress mask
 *
 * @param dev Pointer to the device structure
 * @return Injection address mask
 */
static inline uint64_t edac_inject_addr_mask_get(const struct device *dev)
{
	const struct edac_driver_api *api =
		(const struct edac_driver_api *)dev->api;

	return api->inject_addr_mask_get(dev);

}

/**
 * @brief Set injection control
 *
 * Set injection control register to the value provided.
 *
 * @param dev Pointer to the device structure
 * @param addr Injection control value
 * @return 0 on success, error code otherwise
 */
static inline int edac_inject_ctrl_set(const struct device *dev, uint32_t ctrl)
{
	const struct edac_driver_api *api =
		(const struct edac_driver_api *)dev->api;

	return api->inject_ctrl_set(dev, ctrl);
}

#endif /* CONFIG_EDAC_ERROR_INJECT */

/**
 * @brief Get ECC Error Log
 *
 * Read value of ECC Error Log
 *
 * @param dev Pointer to the device structure
 * @return ECC Error Log value
 */
static inline uint64_t edac_ecc_error_log_get(const struct device *dev)
{
	const struct edac_driver_api *api =
		(const struct edac_driver_api *)dev->api;

	return api->ecc_error_log_get(dev);
}

/**
 * @brief Clear ECC Error Log
 *
 * Clear value of ECC Error Log
 *
 * @param dev Pointer to the device structure
 */
static inline void edac_ecc_error_log_clear(const struct device *dev)
{
	const struct edac_driver_api *api =
		(const struct edac_driver_api *)dev->api;

	api->ecc_error_log_clear(dev);
}

/**
 * @brief Get Parity Error Log
 *
 * Read value of Parity Error Log
 *
 * @param dev Pointer to the device structure
 * @return Parity Error Log value
 */
static inline uint64_t edac_parity_error_log_get(const struct device *dev)
{
	const struct edac_driver_api *api =
		(const struct edac_driver_api *)dev->api;

	return api->parity_error_log_get(dev);
}

/**
 * @brief Clear Parity Error Log
 *
 * Clear value of Parity Error Log
 *
 * @param dev Pointer to the device structure
 */
static inline void edac_parity_error_log_clear(const struct device *dev)
{
	const struct edac_driver_api *api =
		(const struct edac_driver_api *)dev->api;

	api->parity_error_log_clear(dev);
}

/**
 * @brief Get number of correctable errors
 *
 * @param dev Pointer to the device structure
 * @return Number of correctable errors
 */
static inline unsigned int edac_errors_cor_get(const struct device *dev)
{
	const struct edac_driver_api *api =
		(const struct edac_driver_api *)dev->api;

	return api->errors_cor_get(dev);
}

/**
 * @brief Get number of uncorrectable errors
 *
 * @param dev Pointer to the device structure
 * @return Number of uncorrectable errors
 */
static inline unsigned int edac_errors_uc_get(const struct device *dev)
{
	const struct edac_driver_api *api =
		(const struct edac_driver_api *)dev->api;

	return api->errors_uc_get(dev);
}

/**
 * Register callback function for memory error exception
 *
 * This callback runs in interrupt context
 *
 * @param dev EDAC driver device to install callback
 * @param cb Callback function pointer
 * @return 0 Success, nonzero if an error occurred
 */
static inline int edac_notify_callback_set(const struct device *dev,
					   edac_notify_callback_f cb)
{
	const struct edac_driver_api *api = dev->api;

	return api->notify_cb_set(dev, cb);
}

#endif  /* ZEPHYR_INCLUDE_DRIVERS_EDAC_H_ */
