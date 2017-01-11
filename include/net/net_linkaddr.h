/*
 * Copyright (c) 2016 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Public API for network link address
 */

#ifndef __NET_LINKADDR_H__
#define __NET_LINKADDR_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_NET_L2_IEEE802154
#define NET_LINK_ADDR_MAX_LENGTH 8
#else
#define NET_LINK_ADDR_MAX_LENGTH 6
#endif

/**
 *  @brief Hardware link address structure
 *
 *  Used to hold the link address information
 */
struct net_linkaddr {
	/** The array of byte representing the address */
	uint8_t *addr;

	/** Length of that address array */
	uint8_t len;
};

/**
 *  @brief Hardware link address structure
 *
 *  Used to hold the link address information. This variant is needed
 *  when we have to store the link layer address.
 *
 *  Note that you cannot cast this to net_linkaddr as uint8_t * is
 *  handled differently than uint8_t addr[] and the fields are purposely
 *  in a different order.
 */
struct net_linkaddr_storage {
	/** The real length of the ll address. */
	uint8_t len;

	/** The array of bytes representing the address */
	uint8_t addr[NET_LINK_ADDR_MAX_LENGTH];
};

/**
 * @brief Compare two link layer addresses.
 *
 * @param lladdr1 Pointer to a link layer address
 * @param lladdr2 Pointer to a link layer address
 *
 * @return True if the addresses are the same, false otherwise.
 */
static inline bool net_linkaddr_cmp(struct net_linkaddr *lladdr1,
				    struct net_linkaddr *lladdr2)
{
	if (!lladdr1 || !lladdr2) {
		return false;
	}

	if (lladdr1->len != lladdr2->len) {
		return false;
	}

	return !memcmp(lladdr1->addr, lladdr2->addr, lladdr1->len);
}

#ifdef __cplusplus
}
#endif

#endif /* __NET_LINKADDR_H__ */
