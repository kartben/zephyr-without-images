/**
 * @file
 *
 * @brief Public APIs for the DMA drivers.
 */

/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DRIVERS_DMA_H_
#define ZEPHYR_INCLUDE_DRIVERS_DMA_H_

#include <kernel.h>
#include <device.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief DMA Interface
 * @defgroup dma_interface DMA Interface
 * @ingroup io_interfaces
 * @{
 */

enum dma_channel_direction {
	MEMORY_TO_MEMORY = 0x0,
	MEMORY_TO_PERIPHERAL,
	PERIPHERAL_TO_MEMORY,
	PERIPHERAL_TO_PERIPHERAL /*only supported in NXP EDMA*/
};

/** Valid values for @a source_addr_adj and @a dest_addr_adj */
enum dma_addr_adj {
	DMA_ADDR_ADJ_INCREMENT,
	DMA_ADDR_ADJ_DECREMENT,
	DMA_ADDR_ADJ_NO_CHANGE,
};

/**
 * @brief DMA block configuration structure.
 *
 * source_address is block starting address at source
 * source_gather_interval is the address adjustment at gather boundary
 * dest_address is block starting address at destination
 * dest_scatter_interval is the address adjustment at scatter boundary
 * dest_scatter_count is the continuous transfer count between scatter
 *                    boundaries
 * source_gather_count is the continuous transfer count between gather
 *                     boundaries
 * block_size is the number of bytes to be transferred for this block.
 *
 * config is a bit field with the following parts:
 *     source_gather_en   [ 0 ]       - 0-disable, 1-enable
 *     dest_scatter_en    [ 1 ]       - 0-disable, 1-enable
 *     source_addr_adj    [ 2 : 3 ]   - 00-increment, 01-decrement,
 *                                      10-no change
 *     dest_addr_adj      [ 4 : 5 ]   - 00-increment, 01-decrement,
 *                                      10-no change
 *     source_reload_en   [ 6 ]       - reload source address at the end of
 *                                      block transfer
 *                                      0-disable, 1-enable
 *     dest_reload_en     [ 7 ]       - reload destination address at the end
 *                                      of block transfer
 *                                      0-disable, 1-enable
 *     fifo_mode_control  [ 8 : 11 ]  - How full  of the fifo before transfer
 *                                      start. HW specific.
 *     flow_control_mode  [ 12 ]      - 0-source request served upon data
 *                                        availability
 *                                      1-source request postponed until
 *                                        destination request happens
 *     reserved           [ 13 : 15 ]
 */
struct dma_block_config {
#ifdef CONFIG_DMA_64BIT
	uint64_t source_address;
	uint64_t dest_address;
#else
	uint32_t source_address;
	uint32_t dest_address;
#endif
	uint32_t source_gather_interval;
	uint32_t dest_scatter_interval;
	uint16_t dest_scatter_count;
	uint16_t source_gather_count;
	uint32_t block_size;
	struct dma_block_config *next_block;
	uint16_t  source_gather_en :  1;
	uint16_t  dest_scatter_en :   1;
	uint16_t  source_addr_adj :   2;
	uint16_t  dest_addr_adj :     2;
	uint16_t  source_reload_en :  1;
	uint16_t  dest_reload_en :    1;
	uint16_t  fifo_mode_control : 4;
	uint16_t  flow_control_mode : 1;
	uint16_t  reserved :          3;
};

/**
 * @brief DMA configuration structure.
 *
 *     dma_slot             [ 0 : 6 ]   - which peripheral and direction
 *                                        (HW specific)
 *     channel_direction    [ 7 : 9 ]   - 000-memory to memory,
 *                                        001-memory to peripheral,
 *                                        010-peripheral to memory,
 *                                        011-peripheral to peripheral,
 *                                        ...
 *     complete_callback_en [ 10 ]       - 0-callback invoked at completion only
 *                                        1-callback invoked at completion of
 *                                          each block
 *     error_callback_en    [ 11 ]      - 0-error callback enabled
 *                                        1-error callback disabled
 *     source_handshake     [ 12 ]      - 0-HW, 1-SW
 *     dest_handshake       [ 13 ]      - 0-HW, 1-SW
 *     channel_priority     [ 14 : 17 ] - DMA channel priority
 *     source_chaining_en   [ 18 ]      - enable/disable source block chaining
 *                                        0-disable, 1-enable
 *     dest_chaining_en     [ 19 ]      - enable/disable destination block
 *                                        chaining.
 *                                        0-disable, 1-enable
 *     linked_channel       [ 20 : 26 ] - after channel count exhaust will
 *                                        initiate a channel service request
 *                                        at this channel
 *     reserved             [ 27 : 31 ]
 *
 *     source_data_size    [ 0 : 15 ]   - width of source data (in bytes)
 *     dest_data_size      [ 16 : 31 ]  - width of dest data (in bytes)
 *     source_burst_length [ 0 : 15 ]   - number of source data units
 *     dest_burst_length   [ 16 : 31 ]  - number of destination data units
 *
 *     block_count  is the number of blocks used for block chaining, this
 *     depends on availability of the DMA controller.
 *
 *     callback_arg  private argument from DMA client.
 *
 * dma_callback is the callback function pointer. If enabled, callback function
 *              will be invoked at transfer completion or when error happens
 *              (error_code: zero-transfer success, non zero-error happens).
 */
struct dma_config {
	uint32_t  dma_slot :             7;
	uint32_t  channel_direction :    3;
	uint32_t  complete_callback_en : 1;
	uint32_t  error_callback_en :    1;
	uint32_t  source_handshake :     1;
	uint32_t  dest_handshake :       1;
	uint32_t  channel_priority :     4;
	uint32_t  source_chaining_en :   1;
	uint32_t  dest_chaining_en :     1;
	uint32_t  linked_channel   :     7;
	uint32_t  reserved :             5;
	uint32_t  source_data_size :    16;
	uint32_t  dest_data_size :      16;
	uint32_t  source_burst_length : 16;
	uint32_t  dest_burst_length :   16;
	uint32_t block_count;
	struct dma_block_config *head_block;
	void *callback_arg;
	void (*dma_callback)(void *callback_arg, uint32_t channel,
			     int error_code);
};

/**
 * DMA runtime status structure
 *
 * busy 			- is current DMA transfer busy or idle
 * dir				- DMA transfer direction
 * pending_length 		- data length pending to be transferred in bytes
 * 					or platform dependent.
 *
 */
struct dma_status {
	bool busy;
	enum dma_channel_direction dir;
	uint32_t pending_length;
};

/**
 * @cond INTERNAL_HIDDEN
 *
 * These are for internal use only, so skip these in
 * public documentation.
 */

typedef int (*dma_api_config)(struct device *dev, uint32_t channel,
			      struct dma_config *config);

#ifdef CONFIG_DMA_64BIT
typedef int (*dma_api_reload)(struct device *dev, uint32_t channel,
		uint64_t src, uint64_t dst, size_t size);
#else
typedef int (*dma_api_reload)(struct device *dev, uint32_t channel,
		uint32_t src, uint32_t dst, size_t size);
#endif

typedef int (*dma_api_start)(struct device *dev, uint32_t channel);

typedef int (*dma_api_stop)(struct device *dev, uint32_t channel);

typedef int (*dma_api_get_status)(struct device *dev, uint32_t channel,
				  struct dma_status *status);

__subsystem struct dma_driver_api {
	dma_api_config config;
	dma_api_reload reload;
	dma_api_start start;
	dma_api_stop stop;
	dma_api_get_status get_status;
};
/**
 * @endcond
 */

/**
 * @brief Configure individual channel for DMA transfer.
 *
 * @param dev     Pointer to the device structure for the driver instance.
 * @param channel Numeric identification of the channel to configure
 * @param config  Data structure containing the intended configuration for the
 *                selected channel
 *
 * @retval 0 if successful.
 * @retval Negative errno code if failure.
 */
static inline int dma_config(struct device *dev, uint32_t channel,
			     struct dma_config *config)
{
	const struct dma_driver_api *api =
		(const struct dma_driver_api *)dev->driver_api;

	return api->config(dev, channel, config);
}

/**
 * @brief Reload buffer(s) for a DMA channel
 *
 * @param dev     Pointer to the device structure for the driver instance.
 * @param channel Numeric identification of the channel to configure
 *                selected channel
 * @param src     source address for the DMA transfer
 * @param dst     destination address for the DMA transfer
 * @param size    size of DMA transfer
 *
 * @retval 0 if successful.
 * @retval Negative errno code if failure.
 */
#ifdef CONFIG_DMA_64BIT
static inline int dma_reload(struct device *dev, uint32_t channel,
		uint64_t src, uint64_t dst, size_t size)
#else
static inline int dma_reload(struct device *dev, uint32_t channel,
		uint32_t src, uint32_t dst, size_t size)
#endif
{
	const struct dma_driver_api *api =
		(const struct dma_driver_api *)dev->driver_api;

	if (api->reload) {
		return api->reload(dev, channel, src, dst, size);
	}

	return -ENOSYS;
}

/**
 * @brief Enables DMA channel and starts the transfer, the channel must be
 *        configured beforehand.
 *
 * Implementations must check the validity of the channel ID passed in and
 * return -EINVAL if it is invalid.
 *
 * @param dev     Pointer to the device structure for the driver instance.
 * @param channel Numeric identification of the channel where the transfer will
 *                be processed
 *
 * @retval 0 if successful.
 * @retval Negative errno code if failure.
 */
__syscall int dma_start(struct device *dev, uint32_t channel);

static inline int z_impl_dma_start(struct device *dev, uint32_t channel)
{
	const struct dma_driver_api *api =
		(const struct dma_driver_api *)dev->driver_api;

	return api->start(dev, channel);
}

/**
 * @brief Stops the DMA transfer and disables the channel.
 *
 * Implementations must check the validity of the channel ID passed in and
 * return -EINVAL if it is invalid.
 *
 * @param dev     Pointer to the device structure for the driver instance.
 * @param channel Numeric identification of the channel where the transfer was
 *                being processed
 *
 * @retval 0 if successful.
 * @retval Negative errno code if failure.
 */
__syscall int dma_stop(struct device *dev, uint32_t channel);

static inline int z_impl_dma_stop(struct device *dev, uint32_t channel)
{
	const struct dma_driver_api *api =
		(const struct dma_driver_api *)dev->driver_api;

	return api->stop(dev, channel);
}

/**
 * @brief get current runtime status of DMA transfer
 *
 * Implementations must check the validity of the channel ID passed in and
 * return -EINVAL if it is invalid or -ENOSYS if not supported.
 *
 * @param dev     Pointer to the device structure for the driver instance.
 * @param channel Numeric identification of the channel where the transfer was
 *                being processed
 * @param stat   a non-NULL dma_status object for storing DMA status
 *
 * @retval non-negative if successful.
 * @retval Negative errno code if failure.
 */
static inline int dma_get_status(struct device *dev, uint32_t channel,
				 struct dma_status *stat)
{
	const struct dma_driver_api *api =
		(const struct dma_driver_api *)dev->driver_api;

	if (api->get_status) {
		return api->get_status(dev, channel, stat);
	}

	return -ENOSYS;
}

/**
 * @brief Look-up generic width index to be used in registers
 *
 * WARNING: This look-up works for most controllers, but *may* not work for
 *          yours.  Ensure your controller expects the most common register
 *          bit values before using this convenience function.  If your
 *          controller does not support these values, you will have to write
 *          your own look-up inside the controller driver.
 *
 * @param size: width of bus (in bytes)
 *
 * @retval common DMA index to be placed into registers.
 */
static inline uint32_t dma_width_index(uint32_t size)
{
	/* Check boundaries (max supported width is 32 Bytes) */
	if (size < 1 || size > 32) {
		return 0; /* Zero is the default (8 Bytes) */
	}

	/* Ensure size is a power of 2 */
	if (!is_power_of_two(size)) {
		return 0; /* Zero is the default (8 Bytes) */
	}

	/* Convert to bit pattern for writing to a register */
	return find_msb_set(size);
}

/**
 * @brief Look-up generic burst index to be used in registers
 *
 * WARNING: This look-up works for most controllers, but *may* not work for
 *          yours.  Ensure your controller expects the most common register
 *          bit values before using this convenience function.  If your
 *          controller does not support these values, you will have to write
 *          your own look-up inside the controller driver.
 *
 * @param burst: number of bytes to be sent in a single burst
 *
 * @retval common DMA index to be placed into registers.
 */
static inline uint32_t dma_burst_index(uint32_t burst)
{
	/* Check boundaries (max supported burst length is 256) */
	if (burst < 1 || burst > 256) {
		return 0; /* Zero is the default (1 burst length) */
	}

	/* Ensure burst is a power of 2 */
	if (!(burst & (burst - 1))) {
		return 0; /* Zero is the default (1 burst length) */
	}

	/* Convert to bit pattern for writing to a register */
	return find_msb_set(burst);
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#include <syscalls/dma.h>

#endif /* ZEPHYR_INCLUDE_DRIVERS_DMA_H_ */
