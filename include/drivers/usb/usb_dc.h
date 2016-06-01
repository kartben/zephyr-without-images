/* usb_dc.h - USB device controller driver interface */

/*
 * Copyright (c) 2016 Intel Corporation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file
 * @brief USB device controller APIs
 *
 * This file contains the USB device controller APIs. All device controller
 * drivers should implement the APIs described in this file.
 */

#ifndef __USB_DC_H__
#define __USB_DC_H__

#include <device.h>

/**
 * USB endpoint direction and number.
 */

#define	USB_EP_DIR_MASK	0x80
#define	USB_EP_DIR_IN	0x80
#define	USB_EP_DIR_OUT	0x00

/**
 * USB Driver Status Codes
 */
enum usb_dc_status_code {
	USB_DC_ERROR,        /* USB error reported by the controller */
	USB_DC_RESET,        /* USB reset */
	/* USB connection established, hardware enumeration is completed */
	USB_DC_CONNECTED,
	USB_DC_CONFIGURED,   /* USB configuration done */
	USB_DC_DISCONNECTED, /* USB connection lost */
	USB_DC_SUSPEND,      /* USB connection suspended by the HOST */
	USB_DC_RESUME,       /* USB connection resumed by the HOST */
	USB_DC_UNKNOWN       /* Initial USB connection status */
};

/**
 * USB Endpoint Callback Status Codes
 */
enum usb_dc_ep_cb_status_code {
	USB_DC_EP_SETUP,    /* SETUP received */
	/* Out transaction on this EP, data is available for read */
	USB_DC_EP_DATA_OUT,
	USB_DC_EP_DATA_IN,  /* In transaction done on this EP */
};

/**
 * USB Endpoint type
 */
enum usb_dc_ep_type {
	USB_DC_EP_CONTROL = 0,  /* Control type endpoint */
	USB_DC_EP_ISOCHRONOUS,  /* Isochronous type endpoint */
	USB_DC_EP_BULK,         /* Bulk type endpoint */
	USB_DC_EP_INTERRUPT     /* Interrupt type endpoint  */
};

/**
 * USB Endpoint Configuration.
 */
struct usb_dc_ep_cfg_data {
	/** The number associated with the EP in the device
	 *  configuration structure
	 *       IN  EP = 0x80 | \<endpoint number\>
	 *       OUT EP = 0x00 | \<endpoint number\>
	 */
	uint8_t ep_addr;
	uint16_t ep_mps;             /** Endpoint max packet size */
	enum usb_dc_ep_type ep_type; /** Endpoint type */
};

/**
 * Callback function signature for the USB Endpoint status
 */
typedef void (*usb_dc_ep_callback)(uint8_t ep,
	enum usb_dc_ep_cb_status_code cb_status);

/**
 * Callback function signature for the device
 */
typedef void (*usb_dc_status_callback)(enum usb_dc_status_code cb_status);

/**
 * @brief attach USB for device connection
 *
 * Function to attach USB for device connection. Upon success, the USB PLL
 * is enabled, and the USB device is now capable of transmitting and receiving
 * on the USB bus and of generating interrupts.
 *
 * @return 0 on success, negative errno code on fail.
 */
int usb_dc_attach(void);

/**
 * @brief detach the USB device
 *
 * Function to detach the USB device. Upon success, the USB hardware PLL
 * is powered down and USB communication is disabled.
 *
 * @return 0 on success, negative errno code on fail.
 */
int usb_dc_detach(void);

/**
 * @brief reset the USB device
 *
 * This function returns the USB device and firmware back to it's initial state.
 * N.B. the USB PLL is handled by the usb_detach function
 *
 * @return 0 on success, negative errno code on fail.
 */
int usb_dc_reset(void);

/**
 * @brief set USB device address
 *
 * @param[in] addr device address
 *
 * @return 0 on success, negative errno code on fail.
 */
int usb_dc_set_address(const uint8_t addr);

/**
 * @brief set USB device controller status callback
 *
 * Function to set USB device controller status callback. The registered
 * callback is used to report changes in the status of the device controller.
 *
 * @param[in] cb callback function
 *
 * @return 0 on success, negative errno code on fail.
 */
int usb_dc_set_status_callback(const usb_dc_status_callback cb);

/**
 * @brief configure endpoint
 *
 * Function to configure an endpoint. usb_dc_ep_cfg_data structure provides
 * the endpoint configuration parameters: endpoint address, endpoint maximum
 * packet size and endpoint type.
 *
 * @param[in] cfg Endpoint config
 *
 * @return 0 on success, negative errno code on fail.
 */
int usb_dc_ep_configure(const struct usb_dc_ep_cfg_data * const cfg);

/**
 * @brief set stall condition for the selected endpoint
 *
 * @param[in] ep Endpoint address corresponding to the one
 *               listed in the device configuration table
 *
 * @return 0 on success, negative errno code on fail.
 */
int usb_dc_ep_set_stall(const uint8_t ep);

/**
 * @brief clear stall condition for the selected endpoint
 *
 * @param[in] ep Endpoint address corresponding to the one
 *               listed in the device configuration table
 *
 * @return 0 on success, negative errno code on fail.
 */
int usb_dc_ep_clear_stall(const uint8_t ep);

/**
 * @brief check if selected endpoint is stalled
 *
 * @param[in]  ep       Endpoint address corresponding to the one
 *                      listed in the device configuration table
 * @param[out] stalled  Endpoint stall status
 *
 * @return 0 on success, negative errno code on fail.
 */
int usb_dc_ep_is_stalled(const uint8_t ep, uint8_t *const stalled);

/**
 * @brief halt the selected endpoint
 *
 * @param[in] ep Endpoint address corresponding to the one
 *               listed in the device configuration table
 *
 * @return 0 on success, negative errno code on fail.
 */
int usb_dc_ep_halt(const uint8_t ep);

/**
 * @brief enable the selected endpoint
 *
 * Function to enable the selected endpoint. Upon success interrupts are
 * enabled for the corresponding endpoint and the endpoint is ready for
 * transmitting/receiving data.
 *
 * @param[in] ep Endpoint address corresponding to the one
 *               listed in the device configuration table
 *
 * @return 0 on success, negative errno code on fail.
 */
int usb_dc_ep_enable(const uint8_t ep);

/**
 * @brief disable the selected endpoint
 *
 * Function to disable the selected endpoint. Upon success interrupts are
 * disabled for the corresponding endpoint and the endpoint is no longer able
 * for transmitting/receiving data.
 *
 * @param[in] ep Endpoint address corresponding to the one
 *               listed in the device configuration table
 *
 * @return 0 on success, negative errno code on fail.
 */
int usb_dc_ep_disable(const uint8_t ep);

/**
 * @brief flush the selected endpoint
 *
 * @param[in] ep Endpoint address corresponding to the one
 *               listed in the device configuration table
 *
 * @return 0 on success, negative errno code on fail.
 */
int usb_dc_ep_flush(const uint8_t ep);

/**
 * @brief write data to the specified endpoint
 *
 * This function is called to write data to the specified endpoint. The supplied
 * usb_ep_callback function will be called when data is transmitted out.
 *
 * @param[in]  ep        Endpoint address corresponding to the one
 *                       listed in the device configuration table
 * @param[in]  data      pointer to data to write
 * @param[in]  data_len  length of data requested to write. This may
 *                       be zero for a zero length status packet.
 * @param[out] ret_bytes bytes scheduled for transmission. This value
 *                       may be NULL if the application expects all
 *                       bytes to be written
 *
 * @return 0 on success, negative errno code on fail.
 */
int usb_dc_ep_write(const uint8_t ep, const uint8_t *const data,
		const uint32_t data_len, uint32_t * const ret_bytes);

/**
 * @brief read data from the specified endpoint
 *
 * This function is called by the Endpoint handler function, after an OUT
 * interrupt has been received for that EP. The application must only call this
 * function through the supplied usb_ep_callback function.
 *
 * @param[in]  ep           Endpoint address corresponding to the one
 *                          listed in the device configuration table
 * @param[in]  data         pointer to data buffer to write to
 * @param[in]  max_data_len max length of data to read
 * @param[out] read_bytes   Number of bytes read. If data is NULL and
 *                          max_data_len is 0 the number of bytes
 *                          available for read should be returned.
 *
 * @return 0 on success, negative errno code on fail.
 */
int usb_dc_ep_read(const uint8_t ep, uint8_t *const data,
		const uint32_t max_data_len, uint32_t *const read_bytes);

/**
 * @brief set callback function for the specified endpoint
 *
 * Function to set callback function for notification of data received and
 * available to application or trasmit done on the selected endpoint,
 * NULL if callback not required by application code.
 *
 * @param[in] ep Endpoint address corresponding to the one
 *               listed in the device configuration table
 * @param[in] cb callback function
 *
 * @return 0 on success, negative errno code on fail.
 */
int usb_dc_ep_set_callback(const uint8_t ep, const usb_dc_ep_callback cb);

#endif /* __USB_DC_H__ */
