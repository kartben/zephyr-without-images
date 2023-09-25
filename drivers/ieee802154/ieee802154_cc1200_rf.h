/*
 * Copyright (c) 2017 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_IEEE802154_IEEE802154_CC1200_RF_H_
#define ZEPHYR_DRIVERS_IEEE802154_IEEE802154_CC1200_RF_H_

#include <zephyr/drivers/ieee802154/cc1200.h>

#define CC1200_RF_NON_EXT_SPACE_REGS	42
#define CC1200_RF_EXT_SPACE_REGS	58

/* About PKTCFGn from Kconfig:
 * CONFIG_IEEE802154_CC1200_PKTCFG0 LENGTH_VAR_1
 * CONFIG_IEEE802154_CC1200_PKTCFG1 (APPEND_STATUS | CRC_FFFF | ADDR_NO_CHK)
 * We do not enable 802.15.4g mode yet:
 * CONFIG_IEEE802154_CC1200_PKTCFG2 (PKT_FORMAT_NORMAL_MODE | CCA_ALWAYS_CLEAR)
 **/

#ifdef CONFIG_IEEE802154_CC1200_RF_PRESET

#if defined(CONFIG_IEEE802154_CC1200_RF_SET_0)

#define IEEE802154_CC1200_CHANNEL_LIMIT 33

const struct cc1200_rf_registers_set cc1200_rf_settings = {
	.chan_center_freq0 = 863125,
	.channel_spacing = 2000, /* 200 KHz */
	.registers = {
		0x6F, /* SYNC3 */
		0x4E,
		0x90,
		0x4E,
		0xE5,
		0x23,
		0x47,
		0x0B,
		0x56,
		0x19, /* 0x14 */
		0xBA,
		0xC8,
		0x84,
		0x42,
		0x05,
		0x94,
		0x7A,
		0xE1,
		0x27,
		CONFIG_IEEE802154_CC1200_CCA_THRESHOLD,
		CONFIG_IEEE802154_CC1200_RSSI_OFFSET,
		0xB1,
		0x20,
		0x11,
		0x90,
		0x00,
		0x00,
		CONFIG_IEEE802154_CC1200_SETTLING_CFG,
		0x12,
		0x08,
		0x21,
		0x00,
		0x00,
		0x00,
		CONFIG_IEEE802154_CC1200_PKTCFG2,
		CONFIG_IEEE802154_CC1200_PKTCFG1,
		CONFIG_IEEE802154_CC1200_PKTCFG0,
		CONFIG_IEEE802154_CC1200_RFEND_CFG1,
		CONFIG_IEEE802154_CC1200_RFEND_CFG0,
		0x7F,
		0x56,
		0x0F, /* ASK_CFG */
		0x18, /* IF_MIX_CFG */
		0x20,
		0x03,
		0x00,
		0x00,
		0x02,
		0x01,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x56,
		0xCC,
		0xCC,
		0x02,
		0xEE,
		0x10,
		0x04,
		0x50,
		0x00,
		0x20,
		0x40,
		0x0E,
		0x28,
		0x03,
		0x00,
		0x33,
		0xF7,
		0x0F,
		0x00,
		0x00,
		0x6E,
		0x1C,
		0xAC,
		0x14,
		0x00,
		0x00,
		0x00,
		0xB5,
		0x00,
		0x02,
		0x00,
		0x00,
		0x10,
		0x00,
		0x00,
		0x05,
		0x01,
		0x01,
		0x0E,
		0xA0,
		0x03,
		0x04,
		0x03,
		0x00,
		0x00,
		0x00, /* PA_CFG3 */
	}
};

#elif defined(CONFIG_IEEE802154_CC1200_RF_SET_1)

#define IEEE802154_CC1200_CHANNEL_LIMIT 38

const struct cc1200_rf_registers_set cc1200_rf_settings = {
	.chan_center_freq0 = 920600,
	.channel_spacing = 2000, /* 200 KHz */
	.registers = {
		0x6F, /* SYNC3 */
		0x4E,
		0x90,
		0x4E,
		0xE5,
		0x23,
		0x47,
		0x0B,
		0x56,
		0x14,
		0xBA,
		0xC8,
		0x84,
		0x42,
		0x05,
		0x94,
		0x7A,
		0xE1,
		0x27,
		CONFIG_IEEE802154_CC1200_CCA_THRESHOLD,
		CONFIG_IEEE802154_CC1200_RSSI_OFFSET,
		0xB1,
		0x20,
		0x11,
		0x90,
		0x00,
		0x00,
		CONFIG_IEEE802154_CC1200_SETTLING_CFG,
		0x12,
		0x08,
		0x21,
		0x00,
		0x00,
		0x00,
		CONFIG_IEEE802154_CC1200_PKTCFG2,
		CONFIG_IEEE802154_CC1200_PKTCFG1,
		CONFIG_IEEE802154_CC1200_PKTCFG0,
		CONFIG_IEEE802154_CC1200_RFEND_CFG1,
		CONFIG_IEEE802154_CC1200_RFEND_CFG0
		0x7F,
		0x56,
		0x0F, /* ASK_CFG */
		0x18, /* IF_MIX_CFG */
		0x20,
		0x03,
		0x00,
		0x00,
		0x02,
		0x01,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x5C,
		0x0F,
		0x5C,
		0x02,
		0xEE,
		0x10,
		0x04,
		0x55,
		0x00,
		0x20,
		0x40,
		0x0E,
		0x28,
		0x03,
		0x00,
		0x33,
		0xFF,
		0x17,
		0x00,
		0x00,
		0x6E,
		0x1C,
		0xAC,
		0x14,
		0x00,
		0x00,
		0x00,
		0xB5,
		0x00,
		0x02,
		0x00,
		0x00,
		0x10,
		0x00,
		0x00,
		0x05,
		0x01,
		0x01,
		0x0E,
		0xA0,
		0x03,
		0x04,
		0x03,
		0x00,
		0x00,
		0x00, /* PA_CFG3 */
	}
};

#elif defined(CONFIG_IEEE802154_CC1200_RF_SET_2)

#define IEEE802154_CC1200_CHANNEL_LIMIT 14

const struct cc1200_rf_registers_set cc1200_rf_settings = {
	.chan_center_freq0 = 433164,
	.channel_spacing = 2000, /* 200 KHz */
	.registers = {
		0x6F, /* SYNC3 */
		0x4E,
		0x90,
		0x4E,
		0xE5,
		0x23,
		0x47,
		0x0B,
		0x56,
		0x14,
		0xBA,
		0xC8,
		0x84,
		0x42,
		0x05,
		0x94,
		0x7A,
		0xE1,
		0x27,
		CONFIG_IEEE802154_CC1200_CCA_THRESHOLD,
		CONFIG_IEEE802154_CC1200_RSSI_OFFSET,
		0xB1,
		0x20,
		0x11,
		0x90,
		0x00,
		0x00,
		CONFIG_IEEE802154_CC1200_SETTLING_CFG,
		0x14,
		0x08,
		0x21,
		0x00,
		0x00,
		0x00,
		CONFIG_IEEE802154_CC1200_PKTCFG2,
		CONFIG_IEEE802154_CC1200_PKTCFG1,
		CONFIG_IEEE802154_CC1200_PKTCFG0,
		CONFIG_IEEE802154_CC1200_RFEND_CFG1,
		CONFIG_IEEE802154_CC1200_RFEND_CFG0,
		0x7F,
		0x56,
		0x0F, /* ASK_CFG */
		0x18, /* IF_MIX_CFG */
		0x20,
		0x03,
		0x00,
		0x00,
		0x02,
		0x01,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x56,
		0xCC,
		0xCC,
		0x02,
		0xEE,
		0x10,
		0x04,
		0x50,
		0x00,
		0x20,
		0x40,
		0x0E,
		0x28,
		0x03,
		0x00,
		0x33,
		0xF7,
		0x0F,
		0x00,
		0x00,
		0x6E,
		0x1C,
		0xAC,
		0x14,
		0x00,
		0x00,
		0x00,
		0xB5,
		0x00,
		0x02,
		0x00,
		0x00,
		0x10,
		0x00,
		0x00,
		0x05,
		0x01,
		0x01,
		0x0E,
		0xA0,
		0x03,
		0x04,
		0x03,
		0x00,
		0x00,
		0x00, /* PA_CFG3 */
	}
};

#endif /* CONFIG_IEEE802154_CC1200_RF_SET_n */

#endif /* CONFIG_IEEE802154_CC1200_RF_PRESET */

#endif /* ZEPHYR_DRIVERS_IEEE802154_IEEE802154_CC1200_RF_H_ */
