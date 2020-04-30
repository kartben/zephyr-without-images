/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright 2020 Broadcom
 *
 */

#include <drivers/pcie/endpoint/pcie_ep.h>
#include <string.h>
#include <sys/util.h>

static int pcie_ep_mapped_copy(uint64_t mapped_addr, uintptr_t local_addr,
			       const uint32_t size,
			       const enum xfer_direction dir)
{
	/*
	 * Make sure that address can be generated by core, this condition
	 * would not hit if proper pcie_ob_mem_type is passed by core
	 */
	if ((!IS_ENABLED(CONFIG_64BIT)) && (mapped_addr >> 32)) {
		return -EINVAL;
	}

	if (dir == DEVICE_TO_HOST) {
		memcpy(UINT_TO_POINTER(mapped_addr),
		       UINT_TO_POINTER(local_addr), size);
	} else {
		memcpy(UINT_TO_POINTER(local_addr),
		       UINT_TO_POINTER(mapped_addr), size);
	}

	return 0;
}

/*
 * Helper API to achieve data transfer with memcpy operation
 * through PCIe outbound memory
 */
int pcie_ep_xfer_data_memcpy(const struct device *dev, uint64_t pcie_addr,
			     uintptr_t *local_addr, uint32_t size,
			     enum pcie_ob_mem_type ob_mem_type,
			     enum xfer_direction dir)
{
	uint64_t mapped_addr;
	int mapped_size, ret;
	uint32_t xfer_size, unmapped_size;

	mapped_size = pcie_ep_map_addr(dev, pcie_addr, &mapped_addr,
				       size, ob_mem_type);

	/* Check if outbound memory mapping succeeded */
	if (mapped_size < 0) {
		return mapped_size;
	}

	ret = pcie_ep_mapped_copy(mapped_addr, (uintptr_t)local_addr,
				  mapped_size, dir);

	pcie_ep_unmap_addr(dev, mapped_addr);

	/* Check if mapped_copy succeeded */
	if (ret < 0) {
		return ret;
	}

	/* Check if we achieved data transfer for given size */
	if (mapped_size == size) {
		return 0;
	}

	/*
	 * In normal case, we are done with data transfer by now,
	 * but some PCIe address translation hardware requires us to
	 * align Host address to be mapped to the translation window size.
	 * So, even though translation window size is good enough for
	 * size of Host buffer, we may not be able to map entire Host buffer
	 * to given outbound window in one time, and we may need to map
	 * ramaining size and complete remaining data transfer
	 */

	xfer_size = mapped_size; /* save already tranferred data size */

	unmapped_size = size - mapped_size;
	mapped_size = pcie_ep_map_addr(dev, pcie_addr + xfer_size,
				       &mapped_addr, unmapped_size,
				       ob_mem_type);

	/* Check if outbound memory mapping succeeded */
	if (mapped_size < 0) {
		return mapped_size;
	}

	ret = pcie_ep_mapped_copy(mapped_addr,
				  ((uintptr_t)local_addr) + xfer_size,
				  mapped_size, dir);

	pcie_ep_unmap_addr(dev, mapped_addr);

	/* Check if mapped_copy succeeded */
	if (ret < 0) {
		return ret;
	}

	/* In second attempt, we must have completed data transfer */
	if (mapped_size != unmapped_size) {
		return -EIO;
	}

	return 0;
}
