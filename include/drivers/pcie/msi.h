/*
 * Copyright (c) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_DRIVERS_PCIE_MSI_H_
#define ZEPHYR_INCLUDE_DRIVERS_PCIE_MSI_H_

#include <kernel.h>
#include <zephyr/types.h>
#include <stdbool.h>

#include <drivers/pcie/pcie.h>

#ifdef __cplusplus
extern "C" {
#endif

struct msi_vector {
	pcie_bdf_t bdf;
	arch_msi_vector_t arch;
};

typedef struct msi_vector msi_vector_t;

#ifdef CONFIG_PCIE_MSI_MULTI_VECTOR

/**
 * @brief Allocate vector(s) for the endpoint MSI message(s)
 *
 * @param bdf the target PCI endpoint
 * @param priority the MSI vectors base interrupt priority
 * @param vectors an array for storing allocated MSI vectors
 * @param n_vector the size of the MSI vectors array
 *
 * @return the number of allocated MSI vectors.
 */
extern uint8_t pcie_msi_vectors_allocate(pcie_bdf_t bdf,
					 unsigned int priority,
					 msi_vector_t *vectors,
					 uint8_t n_vector);

/**
 * @brief Connect the MSI vector to the handler
 *
 * @param bdf the target PCI endpoint
 * @param vector the MSI vector to connect
 * @param routine Interrupt service routine
 * @param parameter ISR parameter
 * @param flags Arch-specific IRQ configuration flag
 *
 * @return True on success, false otherwise
 */
extern bool pcie_msi_vector_connect(pcie_bdf_t bdf,
				    msi_vector_t *vector,
				    void (*routine)(const void *parameter),
				    const void *parameter,
				    uint32_t flags);

#endif /* CONFIG_PCIE_MSI_MULTI_VECTOR */

/**
 * @brief Compute the target address for an MSI posted write.
 *
 * This function is exported by the arch, board or SoC code.
 *
 * @param irq The IRQ we wish to trigger via MSI.
 * @param vector The vector for which you want the address (or NULL)
 * @return A (32-bit) value for the MSI MAP register.
 */
extern uint32_t pcie_msi_map(unsigned int irq,
			     msi_vector_t *vector);

/**
 * @brief Compute the data for an MSI posted write.
 *
 * This function is exported by the arch, board or SoC code.
 *
 * @param irq The IRQ we wish to trigger via MSI.
 * @param vector The vector for which you want the data (or NULL)
 * @return A (16-bit) value for MSI MDR register.
 */
extern uint16_t pcie_msi_mdr(unsigned int irq,
			     msi_vector_t *vector);

/**
 * @brief Configure the given PCI endpoint to generate MSIs.
 *
 * @param bdf the target PCI endpoint
 * @param vectors an array of allocated vector(s)
 * @param n_vector the size of the vector array
 * @return true if the endpoint supports MSI, false otherwise.
 */
extern bool pcie_msi_enable(pcie_bdf_t bdf,
			    msi_vector_t *vectors,
			    uint8_t n_vector);

/*
 * MSI capability IDs in the PCI configuration capability list.
 */

#define PCIE_MSI_CAP_ID		0x05U
#define PCIE_MSIX_CAP_ID	0x11U

/*
 * The first word of the MSI capability is shared with the
 * capability ID and list link.  The high 16 bits are the MCR.
 */

#define PCIE_MSI_MCR		0U

#define PCIE_MSI_MCR_EN		0x00010000U  /* enable MSI */
#define PCIE_MSI_MCR_MMC	0x000E0000U  /* Multi Messages Capable mask */
#define PCIE_MSI_MCR_MMC_SHIFT	17
#define PCIE_MSI_MCR_MME	0x00700000U  /* mask of # of enabled IRQs */
#define PCIE_MSI_MCR_MME_SHIFT	20
#define PCIE_MSI_MCR_64		0x00800000U  /* 64-bit MSI */

/*
 * The MAP follows the MCR. If PCIE_MSI_MCR_64, then the MAP
 * is two words long. The MDR follows immediately after the MAP.
 */

#define PCIE_MSI_MAP0		1U
#define PCIE_MSI_MAP1_64	2U
#define PCIE_MSI_MDR_32		2U
#define PCIE_MSI_MDR_64		3U

#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_DRIVERS_PCIE_MSI_H_ */
