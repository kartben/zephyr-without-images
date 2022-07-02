/* usb_cdc.h - USB CDC-ACM and CDC-ECM public header */

/*
 * Copyright (c) 2017 PHYTEC Messtechnik GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */


/**
 * @file
 * @brief USB Communications Device Class (CDC) public header
 *
 * Header follows the Class Definitions for
 * Communications Devices Specification (CDC120-20101103-track.pdf),
 * PSTN Devices Specification (PSTN120.pdf) and
 * Ethernet Control Model Devices Specification (ECM120.pdf).
 * Header is limited to ACM and ECM Subclasses.
 */

#ifndef ZEPHYR_INCLUDE_USB_CLASS_USB_CDC_H_
#define ZEPHYR_INCLUDE_USB_CLASS_USB_CDC_H_

/** CDC Specification release number in BCD format */
#define CDC_SRN_1_20			0x0120

/** Communications Class Subclass Codes */
#define ACM_SUBCLASS			0x02
#define ECM_SUBCLASS			0x06
#define EEM_SUBCLASS			0x0c

/** Communications Class Protocol Codes */
#define AT_CMD_V250_PROTOCOL		0x01
#define EEM_PROTOCOL			0x07
#define ACM_VENDOR_PROTOCOL		0xFF

/**
 * @brief Data Class Interface Codes
 * @note CDC120-20101103-track.pdf, 4.5, Table 6
 */
#define DATA_INTERFACE_CLASS		0x0A

/**
 * @brief bDescriptor SubType for Communications
 * Class Functional Descriptors
 * @note CDC120-20101103-track.pdf, 5.2.3, Table 13
 */
#define HEADER_FUNC_DESC		0x00
#define CALL_MANAGEMENT_FUNC_DESC	0x01
#define ACM_FUNC_DESC			0x02
#define UNION_FUNC_DESC			0x06
#define ETHERNET_FUNC_DESC		0x0F

/**
 * @brief PSTN Subclass Specific Requests
 * for ACM devices
 * @note PSTN120.pdf, 6.3, Table 13
 */
#define CDC_SEND_ENC_CMD		0x00
#define CDC_GET_ENC_RSP			0x01
#define SET_LINE_CODING			0x20
#define GET_LINE_CODING			0x21
#define SET_CONTROL_LINE_STATE		0x22

/** Control Signal Bitmap Values for SetControlLineState */
#define SET_CONTROL_LINE_STATE_RTS	0x02
#define SET_CONTROL_LINE_STATE_DTR	0x01

/** Enhance enum uart_line_ctrl with CDC specific values */
#define USB_CDC_LINE_CTRL_BAUD_RATE	UART_LINE_CTRL_BAUD_RATE
#define USB_CDC_LINE_CTRL_DCD		UART_LINE_CTRL_DCD
#define USB_CDC_LINE_CTRL_DSR		UART_LINE_CTRL_DSR
#define USB_CDC_LINE_CTRL_BREAK		BIT(5)
#define USB_CDC_LINE_CTRL_RING_SIGNAL	BIT(6)
#define USB_CDC_LINE_CTRL_FRAMING	BIT(7)
#define USB_CDC_LINE_CTRL_PARITY	BIT(8)
#define USB_CDC_LINE_CTRL_OVER_RUN	BIT(9)

/** UART State Bitmap Values */
#define SERIAL_STATE_OVER_RUN		0x40
#define SERIAL_STATE_PARITY		0x20
#define SERIAL_STATE_FRAMING		0x10
#define SERIAL_STATE_RING_SIGNAL	0x08
#define SERIAL_STATE_BREAK		0x04
#define SERIAL_STATE_TX_CARRIER		0x02
#define SERIAL_STATE_RX_CARRIER		0x01

/**
 * @brief PSTN Subclass Line Coding Values
 *
 * @note PSTN120.pdf, 6.3.11, Table 17
 */
#define USB_CDC_LINE_CODING_STOP_BITS_1		0
#define USB_CDC_LINE_CODING_STOP_BITS_1_5	1
#define USB_CDC_LINE_CODING_STOP_BITS_2		2

#define USB_CDC_LINE_CODING_PARITY_NO		0
#define USB_CDC_LINE_CODING_PARITY_ODD		1
#define USB_CDC_LINE_CODING_PARITY_EVEN		2
#define USB_CDC_LINE_CODING_PARITY_MARK		3
#define USB_CDC_LINE_CODING_PARITY_SPACE	4

#define USB_CDC_LINE_CODING_DATA_BITS_5		5
#define USB_CDC_LINE_CODING_DATA_BITS_6		6
#define USB_CDC_LINE_CODING_DATA_BITS_7		7
#define USB_CDC_LINE_CODING_DATA_BITS_8		8

/**
 * @brief Class-Specific Request Codes for Ethernet subclass
 * @note ECM120.pdf, 6.2, Table 6
 */
#define SET_ETHERNET_MULTICAST_FILTERS	0x40
#define SET_ETHERNET_PM_FILTER		0x41
#define GET_ETHERNET_PM_FILTER		0x42
#define SET_ETHERNET_PACKET_FILTER	0x43
#define GET_ETHERNET_STATISTIC		0x44

/** Ethernet Packet Filter Bitmap */
#define PACKET_TYPE_MULTICAST		0x10
#define PACKET_TYPE_BROADCAST		0x08
#define PACKET_TYPE_DIRECTED		0x04
#define PACKET_TYPE_ALL_MULTICAST	0x02
#define PACKET_TYPE_PROMISCUOUS		0x01

/** Header Functional Descriptor */
struct cdc_header_descriptor {
	uint8_t bFunctionLength;
	uint8_t bDescriptorType;
	uint8_t bDescriptorSubtype;
	uint16_t bcdCDC;
} __packed;

/** Union Interface Functional Descriptor */
struct cdc_union_descriptor {
	uint8_t bFunctionLength;
	uint8_t bDescriptorType;
	uint8_t bDescriptorSubtype;
	uint8_t bControlInterface;
	uint8_t bSubordinateInterface0;
} __packed;

/** Call Management Functional Descriptor */
struct cdc_cm_descriptor {
	uint8_t bFunctionLength;
	uint8_t bDescriptorType;
	uint8_t bDescriptorSubtype;
	uint8_t bmCapabilities;
	uint8_t bDataInterface;
} __packed;

/** Abstract Control Management Functional Descriptor */
struct cdc_acm_descriptor {
	uint8_t bFunctionLength;
	uint8_t bDescriptorType;
	uint8_t bDescriptorSubtype;
	uint8_t bmCapabilities;
} __packed;

/** Data structure for GET_LINE_CODING / SET_LINE_CODING class requests */
struct cdc_acm_line_coding {
	uint32_t dwDTERate;
	uint8_t bCharFormat;
	uint8_t bParityType;
	uint8_t bDataBits;
} __packed;

/** Data structure for the notification about SerialState */
struct cdc_acm_notification {
	uint8_t bmRequestType;
	uint8_t bNotificationType;
	uint16_t wValue;
	uint16_t wIndex;
	uint16_t wLength;
	uint16_t data;
} __packed;

/** Ethernet Networking Functional Descriptor */
struct cdc_ecm_descriptor {
	uint8_t bFunctionLength;
	uint8_t bDescriptorType;
	uint8_t bDescriptorSubtype;
	uint8_t iMACAddress;
	uint32_t bmEthernetStatistics;
	uint16_t wMaxSegmentSize;
	uint16_t wNumberMCFilters;
	uint8_t bNumberPowerFilters;
} __packed;

#endif /* ZEPHYR_INCLUDE_USB_CLASS_USB_CDC_H_ */
