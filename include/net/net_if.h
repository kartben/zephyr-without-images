/*
 * Copyright (c) 2016 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief Public API for network interface
 */

#ifndef __NET_IF_H__
#define __NET_IF_H__

/**
 * @brief Network Interface abstraction layer
 * @defgroup net_if Network Interface abstraction layer
 * @{
 */

#include <device.h>
#include <misc/slist.h>

#include <net/net_core.h>
#include <net/net_linkaddr.h>
#include <net/net_ip.h>
#include <net/net_l2.h>

#if defined(CONFIG_NET_DHCPV4)
#include <net/dhcpv4.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Network Interface unicast IP addresses
 *
 * Stores the unicast IP addresses assigned to this network interface.
 */
struct net_if_addr {
	/** IP address */
	struct net_addr address;

	/** Timer that triggers renewal */
	struct k_delayed_work lifetime;

#if defined(CONFIG_NET_IPV6_DAD)
	/** Duplicate address detection (DAD) timer */
	struct k_delayed_work dad_timer;
#endif
	/** How the IP address was set */
	enum net_addr_type addr_type;

	/** What is the current state of the address */
	enum net_addr_state addr_state;

#if defined(CONFIG_NET_IPV6_DAD)
	/** How many times we have done DAD */
	u8_t dad_count;
#endif

	/** Is the IP address valid forever */
	bool is_infinite;

	/** Is this IP address used or not */
	bool is_used;
};

/**
 * @brief Network Interface multicast IP addresses
 *
 * Stores the multicast IP addresses assigned to this network interface.
 */
struct net_if_mcast_addr {
	/** Is this multicast IP address used or not */
	u8_t is_used : 1;

	/** Did we join to this group */
	u8_t is_joined : 1;

	u8_t _unused : 6;

	/** IP address */
	struct net_addr address;
};

#if defined(CONFIG_NET_IPV6)
/**
 * @brief Network Interface IPv6 prefixes
 *
 * Stores the multicast IP addresses assigned to this network interface.
 */
struct net_if_ipv6_prefix {
	/** Prefix lifetime */
	struct k_delayed_work lifetime;

	/** IPv6 prefix */
	struct in6_addr prefix;

	/** Prefix length */
	u8_t len;

	/** Is the IP prefix valid forever */
	bool is_infinite;

	/** Is this prefix used or not */
	bool is_used;
};
#endif /* CONFIG_NET_IPV6 */

/**
 * @brief Information about routers in the system.
 *
 * Stores the router information.
 */
struct net_if_router {
	/** Router lifetime */
	struct k_delayed_work lifetime;

	/** IP address */
	struct net_addr address;

	/** Network interface the router is connected to */
	struct net_if *iface;

	/** Is this router used or not */
	bool is_used;

	/** Is default router */
	bool is_default;

	/** Is the router valid forever */
	bool is_infinite;
};

/*
 * Special alignment is needed for net_if which is stored in
 * a net_if linker section if there are more than one network
 * interface in the system. If there is only one network interface,
 * then this alignment is not needed, unfortunately this cannot be
 * known beforehand.
 *
 * The net_if struct needs to be aligned to 32 byte boundary,
 * otherwise the __net_if_end will point to wrong location and net_if
 * initialization done in net_if_init() will not find proper values
 * for the second interface.
 *
 * So this alignment is a workaround and should eventually be removed.
 */
#define __net_if_align __aligned(32)

enum {
	/* interface is up/ready to receive and transmit */
	NET_IF_UP,

	/* interface is pointopoint */
	NET_IF_POINTOPOINT,

	/* Total number of flags - must be at the end of the enum */
	NET_IF_NUM_FLAGS
};

#if defined(CONFIG_NET_OFFLOAD)
struct net_offload;
#endif /* CONFIG_NET_OFFLOAD */


/**
 * @brief Network Interface structure
 *
 * Used to handle a network interface on top of a device driver instance.
 * There can be many net_if instance against the same device.
 *
 * Such interface is mainly to be used by the link layer, but is also tight
 * to a network context: it then makes the relation with a network context
 * and the network device.
 *
 * Because of the strong relationship between a device driver and such
 * network interface, each net_if should be instantiated by
 */
struct net_if {
	/** The actually device driver instance the net_if is related to */
	struct device *dev;

	/** Interface's L2 layer */
	const struct net_l2 * const l2;

	/** Interface's private L2 data pointer */
	void *l2_data;

	/* For internal use */
	ATOMIC_DEFINE(flags, NET_IF_NUM_FLAGS);

	/** The hardware link address */
	struct net_linkaddr link_addr;

	/** Queue for outgoing packets from apps */
	struct k_fifo tx_queue;

	/** The hardware MTU */
	u16_t mtu;

#if defined(CONFIG_NET_OFFLOAD)
	/** TCP/IP Offload functions.
	 * If non-NULL, then the TCP/IP stack is located
	 * in the communication chip that is accessed via this
	 * network interface.
	 */
	struct net_offload *offload;
#endif /* CONFIG_NET_OFFLOAD */

#if defined(CONFIG_NET_IPV6)
#define NET_IF_MAX_IPV6_ADDR CONFIG_NET_IF_UNICAST_IPV6_ADDR_COUNT
#define NET_IF_MAX_IPV6_MADDR CONFIG_NET_IF_MCAST_IPV6_ADDR_COUNT
#define NET_IF_MAX_IPV6_PREFIX CONFIG_NET_IF_IPV6_PREFIX_COUNT
	struct {
		/** Unicast IP addresses */
		struct net_if_addr unicast[NET_IF_MAX_IPV6_ADDR];

		/** Multicast IP addresses */
		struct net_if_mcast_addr mcast[NET_IF_MAX_IPV6_MADDR];

		/** Prefixes */
		struct net_if_ipv6_prefix prefix[NET_IF_MAX_IPV6_PREFIX];

		/** Router solicitation timer */
		struct k_delayed_work rs_timer;

		/** Default reachable time (RFC 4861, page 52) */
		u32_t base_reachable_time;

		/** Reachable time (RFC 4861, page 20) */
		u32_t reachable_time;

		/** Retransmit timer (RFC 4861, page 52) */
		u32_t retrans_timer;

		/** IPv6 hop limit */
		u8_t hop_limit;

#if defined(CONFIG_NET_IPV6_DAD)
		/** IPv6 current duplicate address detection count */
		u8_t dad_count;
#endif /* CONFIG_NET_IPV6_DAD */

		/** RS count */
		u8_t rs_count;
	} ipv6;
#endif /* CONFIG_NET_IPV6 */

#if defined(CONFIG_NET_IPV4)
#define NET_IF_MAX_IPV4_ADDR CONFIG_NET_IF_UNICAST_IPV4_ADDR_COUNT
#define NET_IF_MAX_IPV4_MADDR CONFIG_NET_IF_MCAST_IPV4_ADDR_COUNT
	struct {
		/** Unicast IP addresses */
		struct net_if_addr unicast[NET_IF_MAX_IPV4_ADDR];

		/** Multicast IP addresses */
		struct net_if_mcast_addr mcast[NET_IF_MAX_IPV4_MADDR];

		/** Gateway */
		struct in_addr gw;

		/** Netmask */
		struct in_addr netmask;

		/** IPv4 time-to-live */
		u8_t ttl;
	} ipv4;
#endif /* CONFIG_NET_IPV4 */

#if defined(CONFIG_NET_DHCPV4)
	struct {
		u32_t xid;

		/** IP address Lease time */
		u32_t lease_time;

		/** IP address Renewal time */
		u32_t renewal_time;

		/** IP address Rebinding time */
		u32_t rebinding_time;

		/** Server ID */
		struct in_addr server_id;

		/** Requested IP addr */
		struct in_addr requested_ip;

		/** Timer for DHCPv4 Client requests (DISCOVER,
		 * REQUEST or RENEWAL)
		 */
		struct k_delayed_work timer;

		/** T1 (Renewal) timer */
		struct k_delayed_work t1_timer;

		/** T2 (Rebinding) timer */
		struct k_delayed_work t2_timer;

		/**
		 *  DHCPv4 client state in the process of network
		 *  address allocation.
		 */
		enum net_dhcpv4_state state;

		/** Number of attempts made for REQUEST and RENEWAL messages */
		u8_t attempts;
	} dhcpv4;
#endif
} __net_if_align;

/**
 * @brief Send a packet through a net iface
 *
 * @param iface Pointer to a network interface structure
 * @param pkt Pointer to a net packet to send
 *
 * return verdict about the packet
 */
enum net_verdict net_if_send_data(struct net_if *iface, struct net_pkt *pkt);

/**
 * @brief Input a packet through a net iface
 *
 * @param iface Pointer to a network interface structure
 * @param pkt Pointer to a net packet to input
 *
 * @return verdict about the packet
 */
static inline enum net_verdict net_if_recv_data(struct net_if *iface,
						struct net_pkt *pkt)
{
	return iface->l2->recv(iface, pkt);
}

/**
 * @brief Get link layer header size for this network interface
 *
 * @param iface Pointer to a network interface structure
 * @param dst_ip6 Pointer to the destination IPv6 address or NULL if not
 * relevant
 *
 * @return Return the link layer header size
 */
static inline u16_t net_if_get_ll_reserve(struct net_if *iface,
					  const struct in6_addr *dst_ip6)
{
	return iface->l2->reserve(iface, (void *)dst_ip6);
}

/**
 * @brief Get a pointer to the interface L2 private data
 *
 * @param iface a valid pointer to a network interface structure
 *
 * @return a pointer to the iface L2 data
 */
static inline void *net_if_l2_data(struct net_if *iface)
{
	return iface->l2_data;
}

/**
 * @brief Get an network interface's device
 *
 * @param iface Pointer to a network interface structure
 *
 * @return a pointer to the device driver instance
 */
static inline struct device *net_if_get_device(struct net_if *iface)
{
	return iface->dev;
}

/**
 * @brief Queue a packet to the net interface TX queue
 *
 * @param iface Pointer to a network interface structure
 * @param pkt Pointer to a net packet to queue
 */
static inline void net_if_queue_tx(struct net_if *iface, struct net_pkt *pkt)
{
	k_fifo_put(&iface->tx_queue, pkt);
}

#if defined(CONFIG_NET_OFFLOAD)
/**
 * @brief Return the IP offload status
 *
 * @param iface Network interface
 *
 * @return True if IP offlining is active, false otherwise.
 */
static inline bool net_if_is_ip_offloaded(struct net_if *iface)
{
	return (iface->offload != NULL);
}
#endif

/**
 * @brief Get an network interface's link address
 *
 * @param iface Pointer to a network interface structure
 *
 * @return a pointer to the network link address
 */
static inline struct net_linkaddr *net_if_get_link_addr(struct net_if *iface)
{
	return &iface->link_addr;
}

/**
 * @brief Start duplicate address detection procedure.
 *
 * @param iface Pointer to a network interface structure
 */
#if defined(CONFIG_NET_IPV6_DAD)
void net_if_start_dad(struct net_if *iface);
#else
#define net_if_start_dad(iface)
#endif

/**
 * @brief Start neighbor discovery and send router solicitation message.
 *
 * @param iface Pointer to a network interface structure
 */
void net_if_start_rs(struct net_if *iface);

/**
 * @brief Set a network interface's link address
 *
 * @param iface Pointer to a network interface structure
 * @param addr a pointer to a u8_t buffer representing the address
 * @param len length of the address buffer
 * @param type network bearer type of this link address
 *
 * @return 0 on success
 */
static inline int net_if_set_link_addr(struct net_if *iface,
				       u8_t *addr, u8_t len,
				       enum net_link_type type)
{
	if (atomic_test_bit(iface->flags, NET_IF_UP)) {
		return -EPERM;
	}

	iface->link_addr.addr = addr;
	iface->link_addr.len = len;
	iface->link_addr.type = type;

	return 0;
}

/**
 * @brief Get an network interface's MTU
 *
 * @param iface Pointer to a network interface structure
 *
 * @return the MTU
 */
static inline u16_t net_if_get_mtu(struct net_if *iface)
{
	return iface->mtu;
}

/**
 * @brief Set an network interface's MTU
 *
 * @param iface Pointer to a network interface structure
 * @param mtu New MTU, note that we store only 16 bit mtu value.
 */
static inline void net_if_set_mtu(struct net_if *iface,
				  u16_t mtu)
{
	iface->mtu = mtu;
}

/**
 * @brief Set the infinite status of the network interface address
 *
 * @param ifaddr IP address for network interface
 * @param is_infinite Infinite status
 */
static inline void net_if_addr_set_lf(struct net_if_addr *ifaddr,
				      bool is_infinite)
{
	ifaddr->is_infinite = is_infinite;
}

/**
 * @brief Get an interface according to link layer address.
 *
 * @param ll_addr Link layer address.
 *
 * @return Network interface or NULL if not found.
 */
struct net_if *net_if_get_by_link_addr(struct net_linkaddr *ll_addr);

/**
 * @brief Find an interface from it's related device
 *
 * @param dev A valid struct device pointer to relate with an interface
 *
 * @return a valid struct net_if pointer on success, NULL otherwise
 */
struct net_if *net_if_lookup_by_dev(struct device *dev);

/**
 * @brief Remove a router from the system
 *
 * @param router Pointer to existing router
 */
static inline void net_if_router_rm(struct net_if_router *router)
{
	router->is_used = false;

	/* FIXME - remove timer */
}

/**
 * @brief Get the default network interface.
 *
 * @return Default interface or NULL if no interfaces are configured.
 */
struct net_if *net_if_get_default(void);

/**
 * @brief Get the first network interface according to its type.
 *
 * @param l2 Layer 2 type of the network interface.
 *
 * @return First network interface of a given type or NULL if no such
 * interfaces was found.
 */
struct net_if *net_if_get_first_by_type(const struct net_l2 *l2);

#if defined(CONFIG_NET_L2_IEEE802154)
/**
 * @brief Get the first IEEE 802.15.4 network interface.
 *
 * @return First IEEE 802.15.4 network interface or NULL if no such
 * interfaces was found.
 */
static inline struct net_if *net_if_get_ieee802154(void)
{
	return net_if_get_first_by_type(&NET_L2_GET_NAME(IEEE802154));
}
#endif /* CONFIG_NET_L2_IEEE802154 */

#if defined(CONFIG_NET_IPV6)
/**
 * @brief Check if this IPv6 address belongs to one of the interfaces.
 *
 * @param addr IPv6 address
 * @param iface Pointer to interface is returned
 *
 * @return Pointer to interface address, NULL if not found.
 */
struct net_if_addr *net_if_ipv6_addr_lookup(const struct in6_addr *addr,
					    struct net_if **iface);

/**
 * @brief Check if this IPv6 address belongs to this specific interfaces.
 *
 * @param iface Network interface
 * @param addr IPv6 address
 *
 * @return Pointer to interface address, NULL if not found.
 */
static inline
struct net_if_addr *net_if_ipv6_addr_lookup_by_iface(struct net_if *iface,
						     struct in6_addr *addr)
{
	int i;

	for (i = 0; i < NET_IF_MAX_IPV6_ADDR; i++) {
		if (!iface->ipv6.unicast[i].is_used ||
		    iface->ipv6.unicast[i].address.family != AF_INET6) {
			continue;
		}

		if (net_is_ipv6_prefix(addr->s6_addr,
			iface->ipv6.unicast[i].address.in6_addr.s6_addr,
				       128)) {
			return &iface->ipv6.unicast[i];
		}
	}

	return NULL;
}

/**
 * @brief Add a IPv6 address to an interface
 *
 * @param iface Network interface
 * @param addr IPv6 address
 * @param addr_type IPv6 address type
 * @param vlifetime Validity time for this address
 *
 * @return Pointer to interface address, NULL if cannot be added
 */
struct net_if_addr *net_if_ipv6_addr_add(struct net_if *iface,
					 struct in6_addr *addr,
					 enum net_addr_type addr_type,
					 u32_t vlifetime);

/**
 * @brief Update validity lifetime time of an IPv6 address.
 *
 * @param ifaddr Network IPv6 address
 * @param vlifetime Validity time for this address
 */
void net_if_ipv6_addr_update_lifetime(struct net_if_addr *ifaddr,
				      u32_t vlifetime);

/**
 * @brief Remove an IPv6 address from an interface
 *
 * @param iface Network interface
 * @param addr IPv6 address
 *
 * @return True if successfully removed, false otherwise
 */
bool net_if_ipv6_addr_rm(struct net_if *iface, const struct in6_addr *addr);


/**
 * @brief Add a IPv6 multicast address to an interface
 *
 * @param iface Network interface
 * @param addr IPv6 multicast address
 *
 * @return Pointer to interface multicast address, NULL if cannot be added
 */
struct net_if_mcast_addr *net_if_ipv6_maddr_add(struct net_if *iface,
						const struct in6_addr *addr);

/**
 * @brief Remove an IPv6 multicast address from an interface
 *
 * @param iface Network interface
 * @param addr IPv6 multicast address
 *
 * @return True if successfully removed, false otherwise
 */
bool net_if_ipv6_maddr_rm(struct net_if *iface, const struct in6_addr *addr);

/**
 * @brief Check if this IPv6 multicast address belongs to a specific interface
 * or one of the interfaces.
 *
 * @param addr IPv6 address
 * @param iface If *iface is null, then pointer to interface is returned,
 * otherwise the *iface value needs to be matched.
 *
 * @return Pointer to interface multicast address, NULL if not found.
 */
struct net_if_mcast_addr *net_if_ipv6_maddr_lookup(const struct in6_addr *addr,
						   struct net_if **iface);

/**
 * @typedef net_if_mcast_callback_t

 * @brief Define callback that is called whenever IPv6 multicast address group
 * is joined or left.

 * @param "struct net_if *iface" A pointer to a struct net_if to which the
 *        multicast address is attached.
 * @param "const struct in6_addr *addr" IPv6 multicast address.
 * @param "bool is_joined" True if the address is joined, false if left.
 */
typedef void (*net_if_mcast_callback_t)(struct net_if *iface,
					const struct in6_addr *addr,
					bool is_joined);

/**
 * @brief Multicast monitor handler struct.
 *
 * Stores the multicast callback information. Caller must make sure that
 * the variable pointed by this is valid during the lifetime of
 * registration. Typically this means that the variable cannot be
 * allocated from stack.
 */
struct net_if_mcast_monitor {
	/** Node information for the slist. */
	sys_snode_t node;

	/** Network interface */
	struct net_if *iface;

	/** Multicast callback */
	net_if_mcast_callback_t cb;
};

/**
 * @brief Register a multicast monitor
 *
 * @param mon Monitor handle. This is a pointer to a monitor storage structure
 * which should be allocated by caller, but does not need to be initialized.
 * @param iface Network interface
 * @param cb Monitor callback
 */
void net_if_mcast_mon_register(struct net_if_mcast_monitor *mon,
			       struct net_if *iface,
			       net_if_mcast_callback_t cb);

/**
 * @brief Unregister a multicast monitor
 *
 * @param mon Monitor handle
 */
void net_if_mcast_mon_unregister(struct net_if_mcast_monitor *mon);

/**
 * @brief Call registered multicast monitors
 *
 * @param iface Network interface
 * @param addr Multicast address
 * @param is_joined Is this multicast address joined (true) or not (false)
 */
void net_if_mcast_monitor(struct net_if *iface, const struct in6_addr *addr,
			  bool is_joined);

/**
 * @brief Mark a given multicast address to be joined.
 *
 * @param addr IPv6 multicast address
 */
static inline void net_if_ipv6_maddr_join(struct net_if_mcast_addr *addr)
{
	NET_ASSERT(addr);

	addr->is_joined = true;
}

/**
 * @brief Check if given multicast address is joined or not.
 *
 * @param addr IPv6 multicast address
 *
 * @return True if address is joined, False otherwise.
 */
static inline bool net_if_ipv6_maddr_is_joined(struct net_if_mcast_addr *addr)
{
	NET_ASSERT(addr);

	return addr->is_joined;
}

/**
 * @brief Mark a given multicast address to be left.
 *
 * @param addr IPv6 multicast address
 */
static inline void net_if_ipv6_maddr_leave(struct net_if_mcast_addr *addr)
{
	NET_ASSERT(addr);

	addr->is_joined = false;
}

/**
 * @brief Check if this IPv6 prefix belongs to this interface
 *
 * @param iface Network interface
 * @param addr IPv6 address
 * @param len Prefix length
 *
 * @return Pointer to prefix, NULL if not found.
 */
struct net_if_ipv6_prefix *net_if_ipv6_prefix_lookup(struct net_if *iface,
						     struct in6_addr *addr,
						     u8_t len);

/**
 * @brief Add a IPv6 prefix to an network interface.
 *
 * @param iface Network interface
 * @param prefix IPv6 address
 * @param len Prefix length
 * @param lifetime Prefix lifetime in seconds
 *
 * @return Pointer to prefix, NULL if the prefix was not added.
 */
struct net_if_ipv6_prefix *net_if_ipv6_prefix_add(struct net_if *iface,
						  struct in6_addr *prefix,
						  u8_t len,
						  u32_t lifetime);

/**
 * @brief Remove an IPv6 prefix from an interface
 *
 * @param iface Network interface
 * @param addr IPv6 prefix address
 * @param len Prefix length
 *
 * @return True if successfully removed, false otherwise
 */
bool net_if_ipv6_prefix_rm(struct net_if *iface, struct in6_addr *addr,
			   u8_t len);

/**
 * @brief Set the infinite status of the prefix
 *
 * @param prefix IPv6 address
 * @param is_infinite Infinite status
 */
static inline void net_if_ipv6_prefix_set_lf(struct net_if_ipv6_prefix *prefix,
					     bool is_infinite)
{
	prefix->is_infinite = is_infinite;
}

/**
 * @brief Set the prefix lifetime timer.
 *
 * @param prefix IPv6 address
 * @param lifetime Prefix lifetime in seconds
 */
void net_if_ipv6_prefix_set_timer(struct net_if_ipv6_prefix *prefix,
				  u32_t lifetime);

/**
 * @brief Unset the prefix lifetime timer.
 *
 * @param prefix IPv6 address
 */
void net_if_ipv6_prefix_unset_timer(struct net_if_ipv6_prefix *prefix);

/**
 * @brief Check if this IPv6 address is part of the subnet of our
 * network interface.
 *
 * @param iface Network interface. This is returned to the caller.
 * The iface can be NULL in which case we check all the interfaces.
 * @param addr IPv6 address
 *
 * @return True if address is part of our subnet, false otherwise
 */
bool net_if_ipv6_addr_onlink(struct net_if **iface, struct in6_addr *addr);

/**
 * @brief Check if IPv6 address is one of the routers configured
 * in the system.
 *
 * @param iface Network interface
 * @param addr IPv6 address
 *
 * @return Pointer to router information, NULL if cannot be found
 */
struct net_if_router *net_if_ipv6_router_lookup(struct net_if *iface,
						struct in6_addr *addr);

/**
 * @brief Find default router for this IPv6 address.
 *
 * @param iface Network interface. This can be NULL in which case we
 * go through all the network interfaces to find a suitable router.
 * @param addr IPv6 address
 *
 * @return Pointer to router information, NULL if cannot be found
 */
struct net_if_router *net_if_ipv6_router_find_default(struct net_if *iface,
						      struct in6_addr *addr);

/**
 * @brief Update validity lifetime time of a router.
 *
 * @param router Network IPv6 address
 * @param lifetime Lifetime of this router.
 */
void net_if_ipv6_router_update_lifetime(struct net_if_router *router,
					u32_t lifetime);

/**
 * @brief Add IPv6 router to the system.
 *
 * @param iface Network interface
 * @param addr IPv6 address
 * @param router_lifetime Lifetime of the router
 *
 * @return Pointer to router information, NULL if could not be added
 */
struct net_if_router *net_if_ipv6_router_add(struct net_if *iface,
					     struct in6_addr *addr,
					     u16_t router_lifetime);

/**
 * @brief Remove IPv6 router from the system.
 *
 * @param router Router information.
 *
 * @return True if successfully removed, false otherwise
 */
bool net_if_ipv6_router_rm(struct net_if_router *router);

/**
 * @brief Get IPv6 hop limit specified for a given interface. This is the
 * default value but can be overridden by the user.
 *
 * @param iface Network interface
 *
 * @return Hop limit
 */
static inline u8_t net_if_ipv6_get_hop_limit(struct net_if *iface)
{
	return iface->ipv6.hop_limit;
}

/**
 * @brief Set the default IPv6 hop limit of a given interface.
 *
 * @param iface Network interface
 * @param hop_limit New hop limit
 */
static inline void net_ipv6_set_hop_limit(struct net_if *iface,
					  u8_t hop_limit)
{
	iface->ipv6.hop_limit = hop_limit;
}

/**
 * @brief Set IPv6 reachable time for a given interface
 *
 * @param iface Network interface
 * @param reachable_time New reachable time
 */
static inline void net_if_ipv6_set_base_reachable_time(struct net_if *iface,
						    u32_t reachable_time)
{
	iface->ipv6.base_reachable_time = reachable_time;
}

/**
 * @brief Get IPv6 reachable timeout specified for a given interface
 *
 * @param iface Network interface
 *
 * @return Reachable timeout
 */
static inline u32_t net_if_ipv6_get_reachable_time(struct net_if *iface)
{
	return iface->ipv6.reachable_time;
}

/**
 * @brief Calculate next reachable time value for IPv6 reachable time
 *
 * @param iface Network interface
 *
 * @return Reachable time
 */
u32_t net_if_ipv6_calc_reachable_time(struct net_if *iface);

/**
 * @brief Set IPv6 reachable time for a given interface. This requires
 * that base reachable time is set for the interface.
 *
 * @param iface Network interface
 */
static inline void net_if_ipv6_set_reachable_time(struct net_if *iface)
{
	iface->ipv6.reachable_time = net_if_ipv6_calc_reachable_time(iface);
}

/**
 * @brief Set IPv6 retransmit timer for a given interface
 *
 * @param iface Network interface
 * @param retrans_timer New retransmit timer
 */
static inline void net_if_ipv6_set_retrans_timer(struct net_if *iface,
						 u32_t retrans_timer)
{
	iface->ipv6.retrans_timer = retrans_timer;
}

/**
 * @brief Get IPv6 retransmit timer specified for a given interface
 *
 * @param iface Network interface
 *
 * @return Retransmit timer
 */
static inline u32_t net_if_ipv6_get_retrans_timer(struct net_if *iface)
{
	return iface->ipv6.retrans_timer;
}

/**
 * @brief Get a IPv6 source address that should be used when sending
 * network data to destination.
 *
 * @param iface Interface that was used when packet was received.
 * If the interface is not known, then NULL can be given.
 * @param dst IPv6 destination address
 *
 * @return Pointer to IPv6 address to use, NULL if no IPv6 address
 * could be found.
 */
const struct in6_addr *net_if_ipv6_select_src_addr(struct net_if *iface,
						   struct in6_addr *dst);

/**
 * @brief Get a IPv6 link local address in a given state.
 *
 * @param iface Interface to use. Must be a valid pointer to an interface.
 * @param addr_state IPv6 address state (preferred, tentative, deprecated)
 *
 * @return Pointer to link local IPv6 address, NULL if no proper IPv6 address
 * could be found.
 */
struct in6_addr *net_if_ipv6_get_ll(struct net_if *iface,
				    enum net_addr_state addr_state);

/**
 * @brief Return link local IPv6 address from the first interface that has
 * a link local address matching give state.
 *
 * @param state IPv6 address state (ANY, TENTATIVE, PREFERRED, DEPRECATED)
 * @param iface Pointer to interface is returned
 *
 * @return Pointer to IPv6 address, NULL if not found.
 */
struct in6_addr *net_if_ipv6_get_ll_addr(enum net_addr_state state,
					 struct net_if **iface);

/**
 * @brief Stop IPv6 Duplicate Address Detection (DAD) procedure if
 * we find out that our IPv6 address is already in use.
 *
 * @param iface Interface where the DAD was running.
 * @param addr IPv6 address that failed DAD
 */
void net_if_ipv6_dad_failed(struct net_if *iface, const struct in6_addr *addr);

/**
 * @brief Return global IPv6 address from the first interface that has
 * a global IPv6 address either in TENTATIVE or PREFERRED state.
 *
 * @param iface Caller can give an interface to check. If iface is set to NULL,
 * then all the interfaces are checked. Pointer to interface where the IPv6
 * address is defined is returned to the caller.
 *
 * @return Pointer to IPv6 address, NULL if not found.
 */
struct in6_addr *net_if_ipv6_get_global_addr(struct net_if **iface);
#else
#define net_if_ipv6_select_src_addr(...)
#endif /* CONFIG_NET_IPV6 */

#if defined(CONFIG_NET_IPV4)
/**
 * @brief Get IPv4 time-to-live value specified for a given interface
 *
 * @param iface Network interface
 *
 * @return Time-to-live
 */
static inline u8_t net_if_ipv4_get_ttl(struct net_if *iface)
{
	return iface->ipv4.ttl;
}

/**
 * @brief Check if this IPv4 address belongs to one of the interfaces.
 *
 * @param addr IPv4 address
 * @param iface Interface is returned
 *
 * @return Pointer to interface address, NULL if not found.
 */
struct net_if_addr *net_if_ipv4_addr_lookup(const struct in_addr *addr,
					    struct net_if **iface);

/**
 * @brief Add a IPv4 address to an interface
 *
 * @param iface Network interface
 * @param addr IPv4 address
 * @param addr_type IPv4 address type
 * @param vlifetime Validity time for this address
 *
 * @return Pointer to interface address, NULL if cannot be added
 */
struct net_if_addr *net_if_ipv4_addr_add(struct net_if *iface,
					 struct in_addr *addr,
					 enum net_addr_type addr_type,
					 u32_t vlifetime);

/**
 * @brief Remove a IPv4 address from an interface
 *
 * @param iface Network interface
 * @param addr IPv4 address
 *
 * @return True if successfully removed, false otherwise
 */
bool net_if_ipv4_addr_rm(struct net_if *iface,  struct in_addr *addr);


/**
 * @brief Check if IPv4 address is one of the routers configured
 * in the system.
 *
 * @param iface Network interface
 * @param addr IPv4 address
 *
 * @return Pointer to router information, NULL if cannot be found
 */
struct net_if_router *net_if_ipv4_router_lookup(struct net_if *iface,
						struct in_addr *addr);

/**
 * @brief Add IPv4 router to the system.
 *
 * @param iface Network interface
 * @param addr IPv4 address
 * @param is_default Is this router the default one
 * @param router_lifetime Lifetime of the router
 *
 * @return Pointer to router information, NULL if could not be added
 */
struct net_if_router *net_if_ipv4_router_add(struct net_if *iface,
					     struct in_addr *addr,
					     bool is_default,
					     u16_t router_lifetime);

/**
 * @brief Check if the given IPv4 address belongs to local subnet.
 *
 * @param iface Interface to use. Must be a valid pointer to an interface.
 * @param addr IPv4 address
 *
 * @return True if address is part of local subnet, false otherwise.
 */
bool net_if_ipv4_addr_mask_cmp(struct net_if *iface,
			       struct in_addr *addr);

/**
 * @brief Set IPv4 netmask for an interface.
 *
 * @param iface Interface to use.
 * @param netmask IPv4 netmask
 */
static inline void net_if_ipv4_set_netmask(struct net_if *iface,
					   struct in_addr *netmask)
{
	net_ipaddr_copy(&iface->ipv4.netmask, netmask);
}

/**
 * @brief Set IPv4 gateway for an interface.
 *
 * @param iface Interface to use.
 * @param gw IPv4 address of an gateway
 */
static inline void net_if_ipv4_set_gw(struct net_if *iface,
				      struct in_addr *gw)
{
	net_ipaddr_copy(&iface->ipv4.gw, gw);
}

#endif /* CONFIG_NET_IPV4 */

/**
 * @typedef net_if_link_callback_t
 * @brief Define callback that is called after a network packet
 *        has been sent.
 * @param "struct net_if *iface" A pointer to a struct net_if to which the
 *        the net_pkt was sent to.
 * @param "struct net_linkaddr *dst" Link layer address of the destination
 *        where the network packet was sent.
 * @param "int status" Send status, 0 is ok, < 0 error.
 */
typedef void (*net_if_link_callback_t)(struct net_if *iface,
				       struct net_linkaddr *dst,
				       int status);

/**
 * @brief Link callback handler struct.
 *
 * Stores the link callback information. Caller must make sure that
 * the variable pointed by this is valid during the lifetime of
 * registration. Typically this means that the variable cannot be
 * allocated from stack.
 */
struct net_if_link_cb {
	/** Node information for the slist. */
	sys_snode_t node;

	/** Link callback */
	net_if_link_callback_t cb;
};

/**
 * @brief Register a link callback.
 *
 * @param link Caller specified handler for the callback.
 * @param cb Callback to register.
 */
void net_if_register_link_cb(struct net_if_link_cb *link,
			     net_if_link_callback_t cb);

/**
 * @brief Unregister a link callback.
 *
 * @param link Caller specified handler for the callback.
 */
void net_if_unregister_link_cb(struct net_if_link_cb *link);

/**
 * @brief Call a link callback function.
 *
 * @param iface Network interface.
 * @param lladdr Destination link layer address
 * @param status 0 is ok, < 0 error
 */
void net_if_call_link_cb(struct net_if *iface, struct net_linkaddr *lladdr,
			 int status);

/**
 * @brief Get interface according to index
 *
 * @param index Interface index
 *
 * @return Pointer to interface or NULL if not found.
 */
struct net_if *net_if_get_by_index(u8_t index);

/**
 * @brief Get interface index according to pointer
 *
 * @param iface Pointer to network interface
 *
 * @return Interface index
 */
u8_t net_if_get_by_iface(struct net_if *iface);

/**
 * @typedef net_if_cb_t
 * @brief Callback used while iterating over network interfaces
 *
 * @param iface Pointer to current network interface
 * @param user_data A valid pointer to user data or NULL
 */
typedef void (*net_if_cb_t)(struct net_if *iface, void *user_data);

/**
 * @brief Go through all the network interfaces and call callback
 * for each interface.
 *
 * @param cb User-supplied callback function to call
 * @param user_data User specified data
 */
void net_if_foreach(net_if_cb_t cb, void *user_data);

/**
 * @brief Bring interface up
 *
 * @param iface Pointer to network interface
 *
 * @return 0 on success
 */
int net_if_up(struct net_if *iface);

/**
 * @brief Check if interface is up.
 *
 * @param iface Pointer to network interface
 *
 * @return True if interface is up, False if it is down.
 */
static inline bool net_if_is_up(struct net_if *iface)
{
	NET_ASSERT(iface);

	return atomic_test_bit(iface->flags, NET_IF_UP);
}

/**
 * @brief Bring interface down
 *
 * @param iface Pointer to network interface
 *
 * @return 0 on success
 */
int net_if_down(struct net_if *iface);

struct net_if_api {
	void (*init)(struct net_if *iface);
	int (*send)(struct net_if *iface, struct net_pkt *pkt);
};

#if defined(CONFIG_NET_DHCPV4)
#define NET_IF_DHCPV4_INIT .dhcpv4.state = NET_DHCPV4_DISABLED,
#else
#define NET_IF_DHCPV4_INIT
#endif

#define NET_IF_GET_NAME(dev_name, sfx) (__net_if_##dev_name##_##sfx)
#define NET_IF_EVENT_GET_NAME(dev_name, sfx)	\
	(__net_if_event_##dev_name##_##sfx)

#define NET_IF_GET(dev_name, sfx)					\
	((struct net_if *)&NET_IF_GET_NAME(dev_name, sfx))

#define NET_IF_INIT(dev_name, sfx, _l2, _mtu)				\
	static struct net_if (NET_IF_GET_NAME(dev_name, sfx)) __used	\
	__attribute__((__section__(".net_if.data"))) = {		\
		.dev = &(__device_##dev_name),				\
		.l2 = &(NET_L2_GET_NAME(_l2)),				\
		.l2_data = &(NET_L2_GET_DATA(dev_name, sfx)),		\
		.mtu = _mtu,						\
		NET_IF_DHCPV4_INIT					\
	};								\
	static struct k_poll_event					\
	(NET_IF_EVENT_GET_NAME(dev_name, sfx)) __used			\
		__attribute__((__section__(".net_if_event.data"))) = {}


/* Network device initialization macros */

#define NET_DEVICE_INIT(dev_name, drv_name, init_fn,		\
			data, cfg_info, prio, api, l2,		\
			l2_ctx_type, mtu)			\
	DEVICE_AND_API_INIT(dev_name, drv_name, init_fn, data,	\
			    cfg_info, POST_KERNEL, prio, api);	\
	NET_L2_DATA_INIT(dev_name, 0, l2_ctx_type);		\
	NET_IF_INIT(dev_name, 0, l2, mtu)

/**
 * If your network device needs more than one instance of a network interface,
 * Use this macro below and provide a different instance suffix each time
 * (0, 1, 2, ... or a, b, c ... whatever works for you)
 */
#define NET_DEVICE_INIT_INSTANCE(dev_name, drv_name, instance, init_fn,	\
				 data, cfg_info, prio, api, l2,		\
				 l2_ctx_type, mtu)			\
	DEVICE_AND_API_INIT(dev_name, drv_name, init_fn, data,		\
			    cfg_info, POST_KERNEL, prio, api);		\
	NET_L2_DATA_INIT(dev_name, instance, l2_ctx_type);		\
	NET_IF_INIT(dev_name, instance, l2, mtu)

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* __NET_IF_H__ */
