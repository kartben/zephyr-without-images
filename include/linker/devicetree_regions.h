/*
 * Copyright (c) 2021, Commonwealth Scientific and Industrial Research
 * Organisation (CSIRO) ABN 41 687 119 230.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Generate memory regions from devicetree nodes.
 */

/**
 * @brief Get the linker memory-region name
 *
 * This attempts to use the zephyr,memory-region property, falling back
 * to the node path if it doesn't exist.
 *
 * Example devicetree fragment:
 *
 *     / {
 *             soc {
 *                     sram1: memory@2000000 {
 *                         zephyr,memory-region = "MY_NAME";
 *                     };
 *                     sram2: memory@2001000 { ... };
 *             };
 *     };
 *
 * Example usage:
 *
 *    LINKER_DT_NODE_REGION_NAME(DT_NODELABEL(sram1)) // "MY_NAME"
 *    LINKER_DT_NODE_REGION_NAME(DT_NODELABEL(sram2)) // "/soc/memory@2001000"
 *
 * @param node_id node identifier
 * @return the name of the memory memory region the node will generate
 */
#define LINKER_DT_NODE_REGION_NAME(node_id) \
	DT_PROP_OR(node_id, zephyr_memory_region, DT_NODE_PATH(node_id))

/* Declare a memory region */
#define _REGION_DECLARE(name, attr, node) name(attr) : \
	ORIGIN = DT_REG_ADDR(node),		       \
	LENGTH = DT_REG_SIZE(node)

/**
 * @brief Generate a linker memory region from a devicetree node
 *
 * If @p node_id refers to a node with status "okay", then this declares
 * a linker memory region named @p name with attributes from @p attr.
 *
 * Otherwise, it doesn't expand to anything.
 *
 * @param name name of the generated memory region
 * @param attr region attributes to use (rx, rw, ...)
 * @param node_id devicetree node identifier with a \<reg\> property
 *                defining region location and size.
 */
#define LINKER_DT_REGION_FROM_NODE(name, attr, node_id)		\
	COND_CODE_1(DT_NODE_HAS_STATUS(node_id, okay),		\
		    (_REGION_DECLARE(name, attr, node_id)),	\
		    ())
