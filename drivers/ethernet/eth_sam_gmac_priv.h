/*
 * Copyright (c) 2016 Piotr Mienkowski
 * SPDX-License-Identifier: Apache-2.0
 */

/** @file
 * @brief Atmel SAM MCU family Ethernet MAC (GMAC) driver.
 */

#ifndef ZEPHYR_DRIVERS_ETHERNET_ETH_SAM_GMAC_PRIV_H_
#define ZEPHYR_DRIVERS_ETHERNET_ETH_SAM_GMAC_PRIV_H_

#include <zephyr/types.h>

#define ATMEL_OUI_B0 0x00
#define ATMEL_OUI_B1 0x04
#define ATMEL_OUI_B2 0x25

/* This option enables support to push multiple packets to the DMA engine.
 * This currently doesn't work given the current version of net_pkt or
 * net_buf does not allowed access from multiple threads. This option is
 * therefore currently disabled.
 */
#define GMAC_MULTIPLE_TX_PACKETS 0

#define GMAC_MTU NET_ETH_MTU
#define GMAC_FRAME_SIZE_MAX (GMAC_MTU + 18)

/** Cache alignment */
#define GMAC_DCACHE_ALIGNMENT             32
/** Memory alignment of the RX/TX Buffer Descriptor List */
#define GMAC_DESC_ALIGNMENT               4
/** Total number of queues supported by GMAC hardware module */
#define GMAC_QUEUE_NO                     3
/** Number of priority queues used */
#define GMAC_PRIORITY_QUEUE_NO            (CONFIG_ETH_SAM_GMAC_QUEUES - 1)

/** RX descriptors count for main queue */
#define MAIN_QUEUE_RX_DESC_COUNT CONFIG_ETH_SAM_GMAC_BUF_RX_COUNT
/** TX descriptors count for main queue */
#define MAIN_QUEUE_TX_DESC_COUNT (CONFIG_NET_BUF_TX_COUNT + 1)

/** RX/TX descriptors count for priority queues */
#if GMAC_PRIORITY_QUEUE_NO == 2
#define PRIORITY_QUEUE2_RX_DESC_COUNT         MAIN_QUEUE_RX_DESC_COUNT
#define PRIORITY_QUEUE2_TX_DESC_COUNT         MAIN_QUEUE_TX_DESC_COUNT
#else
#define PRIORITY_QUEUE2_RX_DESC_COUNT         1
#define PRIORITY_QUEUE2_TX_DESC_COUNT         1
#endif

#if GMAC_PRIORITY_QUEUE_NO >= 1
#define PRIORITY_QUEUE1_RX_DESC_COUNT         MAIN_QUEUE_RX_DESC_COUNT
#define PRIORITY_QUEUE1_TX_DESC_COUNT         MAIN_QUEUE_TX_DESC_COUNT
#else
#define PRIORITY_QUEUE1_RX_DESC_COUNT         1
#define PRIORITY_QUEUE1_TX_DESC_COUNT         1
#endif

/*
 * Receive buffer descriptor bit field definitions
 */

/** Buffer ownership, needs to be 0 for the GMAC to write data to the buffer */
#define GMAC_RXW0_OWNERSHIP           (0x1u <<  0)
/** Last descriptor in the receive buffer descriptor list */
#define GMAC_RXW0_WRAP                (0x1u <<  1)
/** Address of beginning of buffer */
#define GMAC_RXW0_ADDR         (0x3FFFFFFFu <<  2)

/** Receive frame length including FCS */
#define GMAC_RXW1_LEN              (0x1FFFu <<  0)
/** FCS status */
#define GMAC_RXW1_FCS_STATUS          (0x1u << 13)
/** Start of frame */
#define GMAC_RXW1_SOF                 (0x1u << 14)
/** End of frame */
#define GMAC_RXW1_EOF                 (0x1u << 15)
/** Canonical Format Indicator */
#define GMAC_RXW1_CFI                 (0x1u << 16)
/** VLAN priority (if VLAN detected) */
#define GMAC_RXW1_VLANPRIORITY        (0x7u << 17)
/** Priority tag detected */
#define GMAC_RXW1_PRIORITYDETECTED    (0x1u << 20)
/** VLAN tag detected */
#define GMAC_RXW1_VLANDETECTED        (0x1u << 21)
/** Type ID match */
#define GMAC_RXW1_TYPEIDMATCH         (0x3u << 22)
/** Type ID register match found */
#define GMAC_RXW1_TYPEIDFOUND         (0x1u << 24)
/** Specific Address Register match */
#define GMAC_RXW1_ADDRMATCH           (0x3u << 25)
/** Specific Address Register match found */
#define GMAC_RXW1_ADDRFOUND           (0x1u << 27)
/** Unicast hash match */
#define GMAC_RXW1_UNIHASHMATCH        (0x1u << 29)
/** Multicast hash match */
#define GMAC_RXW1_MULTIHASHMATCH      (0x1u << 30)
/** Global all ones broadcast address detected */
#define GMAC_RXW1_BROADCASTDETECTED   (0x1u << 31)

/*
 * Transmit buffer descriptor bit field definitions
 */

/** Transmit buffer length */
#define GMAC_TXW1_LEN              (0x3FFFu <<  0)
/** Last buffer in the current frame */
#define GMAC_TXW1_LASTBUFFER          (0x1u << 15)
/** No CRC */
#define GMAC_TXW1_NOCRC               (0x1u << 16)
/** Transmit IP/TCP/UDP checksum generation offload errors */
#define GMAC_TXW1_CHKSUMERR           (0x7u << 20)
/** Late collision, transmit error detected */
#define GMAC_TXW1_LATECOLERR          (0x1u << 26)
/** Transmit frame corruption due to AHB error */
#define GMAC_TXW1_TRANSERR            (0x1u << 27)
/** Retry limit exceeded, transmit error detected */
#define GMAC_TXW1_RETRYEXC            (0x1u << 29)
/** Last descriptor in Transmit Descriptor list */
#define GMAC_TXW1_WRAP                (0x1u << 30)
/** Buffer used, must be 0 for the GMAC to read data to the transmit buffer */
#define GMAC_TXW1_USED                (0x1u << 31)

/*
 * Interrupt Status/Enable/Disable/Mask register bit field definitions
 */

#define GMAC_INT_RX_ERR_BITS \
		(GMAC_IER_RXUBR | GMAC_IER_ROVR)
#define GMAC_INT_TX_ERR_BITS \
		(GMAC_IER_TUR | GMAC_IER_RLEX | GMAC_IER_TFC)
#define GMAC_INT_EN_FLAGS \
		(GMAC_IER_RCOMP | GMAC_INT_RX_ERR_BITS | \
		 GMAC_IER_TCOMP | GMAC_INT_TX_ERR_BITS | GMAC_IER_HRESP)

#define GMAC_INTPQ_RX_ERR_BITS \
		(GMAC_IERPQ_RXUBR | GMAC_IERPQ_ROVR)
#define GMAC_INTPQ_TX_ERR_BITS \
		(GMAC_IERPQ_RLEX | GMAC_IERPQ_TFC)
#define GMAC_INTPQ_EN_FLAGS \
		(GMAC_IERPQ_RCOMP | GMAC_INTPQ_RX_ERR_BITS | \
		 GMAC_IERPQ_TCOMP | GMAC_INTPQ_TX_ERR_BITS | GMAC_IERPQ_HRESP)

/** List of GMAC queues */
enum queue_idx {
	GMAC_QUE_0,  /** Main queue */
	GMAC_QUE_1,  /** Priority queue 1 */
	GMAC_QUE_2,  /** Priority queue 2 */
};

/** Minimal ring buffer implementation */
struct ring_buf {
	u32_t *buf;
	u16_t len;
	u16_t head;
	u16_t tail;
};

/** Receive/transmit buffer descriptor */
struct gmac_desc {
	u32_t w0;
	u32_t w1;
};

/** Ring list of receive/transmit buffer descriptors */
struct gmac_desc_list {
	struct gmac_desc *buf;
	u16_t len;
	u16_t head;
	u16_t tail;
};

/** GMAC Queue data */
struct gmac_queue {
	struct gmac_desc_list rx_desc_list;
	struct gmac_desc_list tx_desc_list;
#if GMAC_MULTIPLE_TX_PACKETS == 1
	struct k_sem tx_desc_sem;
#else
	struct k_sem tx_sem;
#endif

	struct net_buf **rx_frag_list;

#if GMAC_MULTIPLE_TX_PACKETS == 1
	struct ring_buf tx_frag_list;
#if defined(CONFIG_PTP_CLOCK_SAM_GMAC)
	struct ring_buf tx_frames;
#endif
#endif

	/** Number of RX frames dropped by the driver */
	volatile u32_t err_rx_frames_dropped;
	/** Number of times receive queue was flushed */
	volatile u32_t err_rx_flushed_count;
	/** Number of times transmit queue was flushed */
	volatile u32_t err_tx_flushed_count;

	enum queue_idx que_idx;
};

/* Device constant configuration parameters */
struct eth_sam_dev_cfg {
	Gmac *regs;
	u32_t periph_id;
	const struct soc_gpio_pin *pin_list;
	u32_t pin_list_size;
	void (*config_func)(void);
	struct phy_sam_gmac_dev phy;
};

/* Device run time data */
struct eth_sam_dev_data {
	struct net_if *iface;
#if defined(CONFIG_PTP_CLOCK_SAM_GMAC)
	struct device *ptp_clock;
#endif
	u8_t mac_addr[6];
	struct gmac_queue queue_list[GMAC_QUEUE_NO];
};

#define DEV_CFG(dev) \
	((const struct eth_sam_dev_cfg *const)(dev)->config->config_info)
#define DEV_DATA(dev) \
	((struct eth_sam_dev_data *const)(dev)->driver_data)

#endif /* ZEPHYR_DRIVERS_ETHERNET_ETH_SAM_GMAC_PRIV_H_ */
