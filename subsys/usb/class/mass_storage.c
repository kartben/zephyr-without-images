/*
 * The Mass Storage protocol state machine in this file is based on mbed's
 * implementation. We augment it by adding Zephyr's USB transport and Storage
 * APIs.
 *
 * Copyright (c) 2010-2011 mbed.org, MIT License
 * Copyright (c) 2016 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


/**
 * @file
 * @brief Mass Storage device class driver
 *
 * Driver for USB Mass Storage device class driver
 */

#include <init.h>
#include <errno.h>
#include <string.h>
#include <misc/__assert.h>
#include <disk_access.h>
#include "mass_storage.h"
#include "usb_device.h"
#include "usb_common.h"

#define SYS_LOG_LEVEL CONFIG_SYS_LOG_USB_MASS_STORAGE_LEVEL
#include <misc/sys_log.h>

/* Misc. macros */
#define LOW_BYTE(x)  ((x) & 0xFF)
#define HIGH_BYTE(x) ((x) >> 8)

/* max USB packet size */
#define MAX_PACKET  MASS_STORAGE_BULK_EP_MPS

#define BLOCK_SIZE	512
#define DISK_FIBER_STACK_SZ	512
#define DISK_FIBER_PRIO	-5

static volatile int fiber_op;
static char __stack mass_fiber_stack[DISK_FIBER_STACK_SZ];
static struct k_sem disk_wait_sem;
static volatile uint32_t defered_wr_sz;

static uint8_t page[BLOCK_SIZE];

/* Initialized during mass_storage_init() */
static uint32_t memory_size;
static uint32_t block_count;

/* CSW Status */
enum Status {
	CSW_PASSED,
	CSW_FAILED,
	CSW_ERROR,
};

/* MSC Bulk-only Stage */
enum Stage {
	READ_CBW,     /* wait a CBW */
	ERROR,        /* error */
	PROCESS_CBW,  /* process a CBW request */
	SEND_CSW,     /* send a CSW */
	WAIT_CSW      /* wait that a CSW has been effectively sent */
};

/* state of the bulk-only state machine */
static enum Stage stage;

/*current CBW*/
static struct CBW cbw;

/*CSW which will be sent*/
static struct CSW csw;

/*addr where will be read or written data*/
static uint32_t addr;

/*length of a reading or writing*/
static uint32_t length;

static uint8_t max_lun_count;

/*memory OK (after a memoryVerify)*/
static bool memOK;

/* Structure representing the global USB description */
static const uint8_t mass_usb_description[] = {
	/* Device descriptor */
	USB_DEVICE_DESC_SIZE,           /* Descriptor size */
	USB_DEVICE_DESC,                /* Descriptor type */
	LOW_BYTE(USB_1_1),
	HIGH_BYTE(USB_1_1),             /* USB version in BCD format */
	0x00,                           /* Class - Interface*/
	0x00,                           /* SubClass - Interface specific */
	0x00,                           /* Protocol - Interface specific */
	MAX_PACKET_SIZE0,               /* Max Packet Size */
	LOW_BYTE(MASS_STORAGE_VENDOR_ID),
	HIGH_BYTE(MASS_STORAGE_VENDOR_ID),       /* Vendor Id */
	LOW_BYTE(MASS_STORAGE_PRODUCT_ID),
	HIGH_BYTE(MASS_STORAGE_PRODUCT_ID),      /* Product Id */
	LOW_BYTE(BCDDEVICE_RELNUM),
	HIGH_BYTE(BCDDEVICE_RELNUM),    /* Device Release Number */
	/* Index of Manufacturer String Descriptor */
	0x01,
	/* Index of Product String Descriptor */
	0x02,
	/* Index of Serial Number String Descriptor */
	0x03,
	MASS_NUM_CONF,                   /* Number of Possible Configuration */

	/* Configuration descriptor */
	USB_CONFIGURATION_DESC_SIZE,    /* Descriptor size */
	USB_CONFIGURATION_DESC,         /* Descriptor type */
	/* Total length in bytes of data returned */
	LOW_BYTE(MASS_CONF_SIZE),
	HIGH_BYTE(MASS_CONF_SIZE),
	MASS_NUM_ITF,                    /* Number of interfaces */
	0x01,                           /* Configuration value */
	0x00,                           /* Index of the Configuration string */
	USB_CONFIGURATION_ATTRIBUTES,   /* Attributes */
	MAX_LOW_POWER,                  /* Max power consumption */

	/* Interface descriptor */
	USB_INTERFACE_DESC_SIZE,        /* Descriptor size */
	USB_INTERFACE_DESC,             /* Descriptor type */
	0x00,                           /* Interface index */
	0x00,                           /* Alternate setting */
	2,                    /* Number of Endpoints */
	MASS_STORAGE_CLASS,     /* Class */
	SCSI_TRANSPARENT_SUBCLASS,                   /* SubClass */
	BULK_ONLY_PROTOCOL,                /* Protocol */
	/* Index of the Interface String Descriptor */
	0x00,

	/* First Endpoint IN */
	USB_ENDPOINT_DESC_SIZE,         /* Descriptor size */
	USB_ENDPOINT_DESC,              /* Descriptor type */
	EPBULK_IN,                    /* Endpoint address */
	USB_DC_EP_BULK,                 /* Attributes */
	LOW_BYTE(MASS_STORAGE_BULK_EP_MPS),
	HIGH_BYTE(MASS_STORAGE_BULK_EP_MPS),     /* Max packet size */
	0x00,                           /* Interval */

	/* Second Endpoint OUT */
	USB_ENDPOINT_DESC_SIZE,         /* Descriptor size */
	USB_ENDPOINT_DESC,              /* Descriptor type */
	EPBULK_OUT,                   /* Endpoint address */
	USB_DC_EP_BULK,                 /* Attributes */
	LOW_BYTE(MASS_STORAGE_BULK_EP_MPS),
	HIGH_BYTE(MASS_STORAGE_BULK_EP_MPS),     /* Max packet size */
	0x00,                           /* Interval */

	/* String descriptor language, only one, so min size 4 bytes.
	 * 0x0409 English(US) language code used
	 */
	USB_STRING_DESC_SIZE,           /* Descriptor size */
	USB_STRING_DESC,                /* Descriptor type */
	0x09,
	0x04,

	/* Manufacturer String Descriptor "ZEPHYR" */
	0x0E,
	USB_STRING_DESC,
	'Z', 0, 'E', 0, 'P', 0, 'H', 0, 'Y', 0, 'R', 0,

	/* Product String Descriptor "USB-DISK" */
	0x12,
	USB_STRING_DESC,
	'U', 0, 'S', 0, 'B', 0, '-', 0, 'D', 0, 'I', 0, 'S', 0, 'K', 0,

	/* Serial Number String Descriptor "0.01" */
	0x0A,
	USB_STRING_DESC,
	'0', 0, '.', 0, '0', 0, '1', 0,
};

static void msd_state_machine_reset(void)
{
	stage = READ_CBW;
}

static void msd_init(void)
{
	memset((void *)&cbw, 0, sizeof(struct CBW));
	memset((void *)&csw, 0, sizeof(struct CSW));
	memset(page, 0, sizeof(page));
	addr = 0;
	length = 0;
}

static void sendCSW(void)
{
	csw.Signature = CSW_Signature;
	if (usb_write(EPBULK_IN, (uint8_t *)&csw,
		      sizeof(struct CSW), NULL) != 0) {
		SYS_LOG_ERR("usb write failure");
	}
	stage = WAIT_CSW;
}

static bool write(uint8_t *buf, uint16_t size)
{
	if (size >= cbw.DataLength) {
		size = cbw.DataLength;
	}

	/* updating the State Machine , so that we send CSW when this
	 * transfer is complete, ie when we get a bulk in callback
	 */
	stage = SEND_CSW;

	if (!usb_write(EPBULK_IN, buf, size, NULL)) {
		return false;
	}

	csw.DataResidue -= size;
	csw.Status = CSW_PASSED;
	return true;
}

/**
 * @brief Handler called for Class requests not handled by the USB stack.
 *
 * @param pSetup    Information about the request to execute.
 * @param len       Size of the buffer.
 * @param data      Buffer containing the request result.
 *
 * @return  0 on success, negative errno code on fail.
 */
static int mass_storage_class_handle_req(struct usb_setup_packet *pSetup,
		int32_t *len, uint8_t **data)
{

	switch (pSetup->bRequest) {
	case MSC_REQUEST_RESET:
		SYS_LOG_DBG("\nMSC_REQUEST_RESET");
		msd_state_machine_reset();
		break;

	case MSC_REQUEST_GET_MAX_LUN:
		SYS_LOG_DBG("\nMSC_REQUEST_GET_MAX_LUN ");
		max_lun_count = 0;
		*data = (uint8_t *)(&max_lun_count);
		*len = 1;
		break;

	default:
		SYS_LOG_DBG("Mass Storage unknown request 0x%x, value 0x%x",
			pSetup->bRequest, pSetup->wValue);
		return -EINVAL;
	}

	return 0;
}

static void testUnitReady(void)
{
	if (cbw.DataLength != 0) {
		if ((cbw.Flags & 0x80) != 0) {
			SYS_LOG_DBG("TUR - BI - STALL");
			usb_ep_set_stall(EPBULK_IN);
		} else {
			SYS_LOG_DBG("TUR - BO - STALL");
			usb_ep_set_stall(EPBULK_OUT);
		}
	}

	csw.Status = CSW_PASSED;
	sendCSW();
}

static bool requestSense(void)
{
	uint8_t request_sense[] = {
		0x70,
		0x00,
		0x05,   /* Sense Key: illegal request */
		0x00,
		0x00,
		0x00,
		0x00,
		0x0A,
		0x00,
		0x00,
		0x00,
		0x00,
		0x30,
		0x01,
		0x00,
		0x00,
		0x00,
		0x00,
	};

	if (!write(request_sense, sizeof(request_sense))) {
		return false;
	}

	return true;
}

static bool inquiryRequest(void)
{
	uint8_t inquiry[] = { 0x00, 0x80, 0x00, 0x01,
	36 - 4, 0x80, 0x00, 0x00,
	'Z', 'E', 'P', 'H', 'Y', 'R', ' ', ' ',
	'Z', 'E', 'P', 'H', 'Y', 'R', ' ', 'U', 'S', 'B', ' ', 'D', 'I', 'S', 'K', ' ',
	'0', '.', '0', '1',
	};

	if (!write(inquiry, sizeof(inquiry))) {
		return false;
	}
	return true;
}

static bool modeSense6(void)
{
	uint8_t sense6[] = { 0x03, 0x00, 0x00, 0x00 };

	if (!write(sense6, sizeof(sense6))) {
		return false;
	}
	return true;
}

static bool readFormatCapacity(void)
{
	uint8_t capacity[] = { 0x00, 0x00, 0x00, 0x08,
			(uint8_t)((block_count >> 24) & 0xff),
			(uint8_t)((block_count >> 16) & 0xff),
			(uint8_t)((block_count >> 8) & 0xff),
			(uint8_t)((block_count >> 0) & 0xff),

			0x02,
			(uint8_t)((BLOCK_SIZE >> 16) & 0xff),
			(uint8_t)((BLOCK_SIZE >> 8) & 0xff),
			(uint8_t)((BLOCK_SIZE >> 0) & 0xff),
			 };
	if (!write(capacity, sizeof(capacity))) {
		return false;
	}
	return true;
}

static bool readCapacity(void)
{
	uint8_t capacity[] = {
		(uint8_t)(((block_count - 1) >> 24) & 0xff),
		(uint8_t)(((block_count - 1) >> 16) & 0xff),
		(uint8_t)(((block_count - 1) >> 8) & 0xff),
		(uint8_t)(((block_count - 1) >> 0) & 0xff),

		(uint8_t)((BLOCK_SIZE >> 24) & 0xff),
		(uint8_t)((BLOCK_SIZE >> 16) & 0xff),
		(uint8_t)((BLOCK_SIZE >> 8) & 0xff),
		(uint8_t)((BLOCK_SIZE >> 0) & 0xff),
	};
	if (!write(capacity, sizeof(capacity))) {
		return false;
	}
	return true;
}

static void fiber_memory_read_done(void)
{
	uint32_t n;

	n = (length > MAX_PACKET) ? MAX_PACKET : length;
	if ((addr + n) > memory_size) {
		n = memory_size - addr;
		stage = ERROR;
	}

	if (usb_write(EPBULK_IN, &page[addr % BLOCK_SIZE], n, NULL) != 0) {
		SYS_LOG_ERR("usb write failure");
	}
	addr += n;
	length -= n;

	csw.DataResidue -= n;

	if (!length || (stage != PROCESS_CBW)) {
		csw.Status = (stage == PROCESS_CBW) ? CSW_PASSED : CSW_FAILED;
		stage = (stage == PROCESS_CBW) ? SEND_CSW : stage;
	}
}


static void memoryRead(void)
{
	uint32_t n;

	n = (length > MAX_PACKET) ? MAX_PACKET : length;
	if ((addr + n) > memory_size) {
		n = memory_size - addr;
		stage = ERROR;
	}

	/* we read an entire block */
	if (!(addr % BLOCK_SIZE)) {
		fiber_op = FIBER_OP_READ_QUEUED;
		SYS_LOG_DBG("Signal fiber for %d", (addr/BLOCK_SIZE));
		k_sem_give(&disk_wait_sem);
		return;
	}
	usb_write(EPBULK_IN, &page[addr % BLOCK_SIZE], n, NULL);
	addr += n;
	length -= n;

	csw.DataResidue -= n;

	if (!length || (stage != PROCESS_CBW)) {
		csw.Status = (stage == PROCESS_CBW) ? CSW_PASSED : CSW_FAILED;
		stage = (stage == PROCESS_CBW) ? SEND_CSW : stage;
	}
}

static bool infoTransfer(void)
{
	uint32_t n;

	/* Logical Block Address of First Block */
	n = (cbw.CB[2] << 24) | (cbw.CB[3] << 16) | (cbw.CB[4] <<  8) |
				 (cbw.CB[5] <<  0);

	SYS_LOG_DBG("LBA (block) : 0x%x ", n);
	addr = n * BLOCK_SIZE;

	/* Number of Blocks to transfer */
	switch (cbw.CB[0]) {
	case READ10:
	case WRITE10:
	case VERIFY10:
		n = (cbw.CB[7] <<  8) | (cbw.CB[8] <<  0);
		break;

	case READ12:
	case WRITE12:
		n = (cbw.CB[6] << 24) | (cbw.CB[7] << 16) |
			(cbw.CB[8] <<  8) | (cbw.CB[9] <<  0);
		break;
	}

	SYS_LOG_DBG("Size (block) : 0x%x ", n);
	length = n * BLOCK_SIZE;

	if (!cbw.DataLength) {              /* host requests no data*/
		SYS_LOG_WRN("Zero length in CBW");
		csw.Status = CSW_FAILED;
		sendCSW();
		return false;
	}

	if (cbw.DataLength != length) {
		if ((cbw.Flags & 0x80) != 0) {
			SYS_LOG_WRN("BI - STall, length != ");
			usb_ep_set_stall(EPBULK_IN);
		} else {
			SYS_LOG_WRN("BO - STall");
			usb_ep_set_stall(EPBULK_OUT);
		}

		csw.Status = CSW_FAILED;
		sendCSW();
		return false;
	}

	return true;
}

static void fail(void)
{
	SYS_LOG_DBG("fail ()");
	csw.Status = CSW_FAILED;
	sendCSW();
}

static void CBWDecode(uint8_t *buf, uint16_t size)
{
	if (size != sizeof(cbw)) {
		SYS_LOG_ERR("size != sizeof(cbw)");
		return;
	}

	memcpy((uint8_t *)&cbw, buf, size);
	if (cbw.Signature != CBW_Signature) {
		SYS_LOG_ERR("CBW Signature Mismatch");
		return;
	}

	csw.Tag = cbw.Tag;
	csw.DataResidue = cbw.DataLength;

	if ((cbw.CBLength <  1) || (cbw.CBLength > 16) || (cbw.LUN != 0)) {
		SYS_LOG_WRN("cbw.CBLength %d", cbw.CBLength);
		fail();
	} else {
		switch (cbw.CB[0]) {
		case TEST_UNIT_READY:
			SYS_LOG_DBG(">> TUR");
			testUnitReady();
			break;
		case REQUEST_SENSE:
			SYS_LOG_DBG(">> REQ_SENSE");
			requestSense();
			break;
		case INQUIRY:
			SYS_LOG_DBG(">> INQ");
			inquiryRequest();
			break;
		case MODE_SENSE6:
			SYS_LOG_DBG(">> MODE_SENSE6");
			modeSense6();
			break;
		case READ_FORMAT_CAPACITIES:
			SYS_LOG_DBG(">> READ_FORMAT_CAPACITY");
			readFormatCapacity();
			break;
		case READ_CAPACITY:
			SYS_LOG_DBG(">> READ_CAPACITY");
			readCapacity();
			break;
		case READ10:
		case READ12:
			SYS_LOG_DBG(">> READ");
			if (infoTransfer()) {
				if ((cbw.Flags & 0x80)) {
					stage = PROCESS_CBW;
					memoryRead();
				} else {
					usb_ep_set_stall(EPBULK_OUT);
					SYS_LOG_DBG("BO-STALL");
					csw.Status = CSW_ERROR;
					sendCSW();
				}
			}
			break;
		case WRITE10:
		case WRITE12:
			SYS_LOG_DBG(">> WRITE");
			if (infoTransfer()) {
				if (!(cbw.Flags & 0x80)) {
					stage = PROCESS_CBW;
				} else {
					usb_ep_set_stall(EPBULK_IN);
					SYS_LOG_DBG("BI-STALL");
					csw.Status = CSW_ERROR;
					sendCSW();
				}
			}
			break;
		case VERIFY10:
			SYS_LOG_DBG(">> VERIFY10");
			if (!(cbw.CB[1] & 0x02)) {
				csw.Status = CSW_PASSED;
				sendCSW();
				break;
			}
			if (infoTransfer()) {
				if (!(cbw.Flags & 0x80)) {
					stage = PROCESS_CBW;
					memOK = true;
				} else {
					usb_ep_set_stall(EPBULK_IN);
					SYS_LOG_DBG("VERIFY10 - BI - STALL");
					csw.Status = CSW_ERROR;
					sendCSW();
				}
			}
			break;
		case MEDIA_REMOVAL:
			SYS_LOG_DBG(">> MEDIA_REMOVAL");
			csw.Status = CSW_PASSED;
			sendCSW();
			break;
		default:
			SYS_LOG_WRN(">> default CB[0] %x", cbw.CB[0]);
			fail();
			break;
		}		/*switch(cbw.CB[0])*/
	}		/* else */

}

static void memoryVerify(uint8_t *buf, uint16_t size)
{
	uint32_t n;

	if ((addr + size) > memory_size) {
		size = memory_size - addr;
		stage = ERROR;
		usb_ep_set_stall(EPBULK_OUT);
		SYS_LOG_WRN("BO - STall > MemSz");
	}

	/* beginning of a new block -> load a whole block in RAM */
	if (!(addr % BLOCK_SIZE)) {
		SYS_LOG_DBG("Disk READ sector %d", addr/BLOCK_SIZE);
		if (disk_access_read(page, addr/BLOCK_SIZE, 1)) {
			SYS_LOG_ERR("---- Disk Read Error %d", addr/BLOCK_SIZE);
		}
	}

	/* info are in RAM -> no need to re-read memory */
	for (n = 0; n < size; n++) {
		if (page[addr%BLOCK_SIZE + n] != buf[n]) {
			SYS_LOG_DBG("Mismatch sector %d offset %d",
					addr/BLOCK_SIZE, n);
			memOK = false;
			break;
		}
	}

	addr += size;
	length -= size;
	csw.DataResidue -= size;

	if (!length || (stage != PROCESS_CBW)) {
		csw.Status = (memOK && (stage == PROCESS_CBW)) ?
						CSW_PASSED : CSW_FAILED;
		sendCSW();
	}
}

static void memoryWrite(uint8_t *buf, uint16_t size)
{
	if ((addr + size) > memory_size) {
		size = memory_size - addr;
		stage = ERROR;
		usb_ep_set_stall(EPBULK_OUT);
		SYS_LOG_WRN("BO - STall > MemSz");
	}

	/* we fill an array in RAM of 1 block before writing it in memory */
	for (int i = 0; i < size; i++) {
		page[addr % BLOCK_SIZE + i] = buf[i];
	}

	/* if the array is filled, write it in memory */
	if (!((addr + size) % BLOCK_SIZE)) {
		if (!(disk_access_status() & DISK_STATUS_WR_PROTECT)) {
			SYS_LOG_DBG("Disk WRITE Qd %d", (addr/BLOCK_SIZE));
			fiber_op = FIBER_OP_WRITE_QUEUED;  /* write_queued */
			defered_wr_sz = size;
			k_sem_give(&disk_wait_sem);
			return;
		}
	}

	addr += size;
	length -= size;
	csw.DataResidue -= size;

	if ((!length) || (stage != PROCESS_CBW)) {
		csw.Status = (stage == ERROR) ? CSW_FAILED : CSW_PASSED;
		sendCSW();
	}
}


static void mass_storage_bulk_out(uint8_t ep,
		enum usb_dc_ep_cb_status_code ep_status)
{
	uint32_t bytes_read = 0;
	uint8_t bo_buf[MASS_STORAGE_BULK_EP_MPS];

	usb_ep_read_wait(ep, bo_buf, MASS_STORAGE_BULK_EP_MPS, &bytes_read);

	switch (stage) {
	/*the device has to decode the CBW received*/
	case READ_CBW:
		SYS_LOG_DBG("> BO - READ_CBW");
		CBWDecode(bo_buf, bytes_read);
		break;

	/*the device has to receive data from the host*/
	case PROCESS_CBW:
		switch (cbw.CB[0]) {
		case WRITE10:
		case WRITE12:
			/* SYS_LOG_DBG("> BO - PROC_CBW WR");*/
			memoryWrite(bo_buf, bytes_read);
			break;
		case VERIFY10:
			SYS_LOG_DBG("> BO - PROC_CBW VER");
			memoryVerify(bo_buf, bytes_read);
			break;
		default:
			SYS_LOG_DBG("> BO - PROC_CBW default"
					"<<ERROR!!!>>");
			break;
		}
		break;

	/*an error has occurred: stall endpoint and send CSW*/
	default:
	SYS_LOG_DBG("> BO - default stalling %d", stage);
		usb_ep_set_stall(ep);
		csw.Status = CSW_ERROR;
		sendCSW();
		break;
	}

	if (fiber_op != FIBER_OP_WRITE_QUEUED) {
		usb_ep_read_continue(ep);
	} else {
		SYS_LOG_DBG("> BO not clearing NAKs yet");
	}

}

static void fiber_memory_write_done(void)
{
	uint32_t size = defered_wr_sz;

	addr += size;
	length -= size;
	csw.DataResidue -= size;


	if ((!length) || (stage != PROCESS_CBW)) {
		csw.Status = (stage == ERROR) ? CSW_FAILED : CSW_PASSED;
		sendCSW();
	}

	fiber_op = FIBER_OP_WRITE_DONE;

	usb_ep_read_continue(EPBULK_OUT);
}

/**
 * @brief EP Bulk IN handler, used to send data to the Host
 *
 * @param ep        Endpoint address.
 * @param ep_status Endpoint status code.
 *
 * @return  N/A.
 */
static void mass_storage_bulk_in(uint8_t ep,
				 enum usb_dc_ep_cb_status_code ep_status)
{
	switch (stage) {
	/*the device has to send data to the host*/
	case PROCESS_CBW:
		switch (cbw.CB[0]) {
		case READ10:
		case READ12:
			/* SYS_LOG_DBG("< BI - PROC_CBW  READ"); */
			memoryRead();
			break;
		default:
			SYS_LOG_ERR("< BI-PROC_CBW default <<ERROR!!>>");
			break;
		}
		break;

	/*the device has to send a CSW*/
	case SEND_CSW:
		SYS_LOG_DBG("< BI - SEND_CSW");
		sendCSW();
		break;

	/*the host has received the CSW -> we wait a CBW*/
	case WAIT_CSW:
		SYS_LOG_DBG("< BI - WAIT_CSW");
		stage = READ_CBW;
		break;

	/*an error has occurred*/
	default:
		SYS_LOG_DBG("< BI - default stalling %d", stage);
		usb_ep_set_stall(EPBULK_IN);
		sendCSW();
		break;
	}
}



/**
 * @brief Callback used to know the USB connection status
 *
 * @param status USB device status code.
 *
 * @return  N/A.
 */
static void mass_storage_status_cb(enum usb_dc_status_code status)
{

	/* Check the USB status and do needed action if required */
	switch (status) {
	case USB_DC_ERROR:
		SYS_LOG_DBG("USB device error");
		break;
	case USB_DC_RESET:
		SYS_LOG_DBG("USB device reset detected 4");
		msd_state_machine_reset();
		msd_init();
		break;
	case USB_DC_CONNECTED:
		SYS_LOG_DBG("USB device connected");
		break;
	case USB_DC_CONFIGURED:
		SYS_LOG_DBG("USB device configured");
		break;
	case USB_DC_DISCONNECTED:
		SYS_LOG_DBG("USB device disconnected");
		break;
	case USB_DC_SUSPEND:
		SYS_LOG_DBG("USB device supended");
		break;
	case USB_DC_RESUME:
		SYS_LOG_DBG("USB device resumed");
		break;
	case USB_DC_UNKNOWN:
	default:
		SYS_LOG_DBG("USB unknown state");
		break;
		}
}

/* Describe EndPoints configuration */
static struct usb_ep_cfg_data mass_ep_data[] = {
	{
		.ep_cb	= mass_storage_bulk_out,
		.ep_addr = EPBULK_OUT
	},
	{
		.ep_cb = mass_storage_bulk_in,
		.ep_addr = EPBULK_IN
	}
};

/* Configuration of the CDC-ACM Device send to the USB Driver */
static struct usb_cfg_data mass_storage_config = {
	.usb_device_description = mass_usb_description,
	.cb_usb_status = mass_storage_status_cb,
	.interface = {
		.class_handler = mass_storage_class_handle_req,
		.custom_handler = NULL,
		.payload_data = NULL,
	},
	.num_endpoints = 2,
	.endpoint = mass_ep_data
};

static void mass_fiber_main(int arg1, int unused)
{

	ARG_UNUSED(unused);

	while (1) {
		k_sem_take(&disk_wait_sem, K_FOREVER);
		SYS_LOG_DBG("sem %d", fiber_op);

		switch (fiber_op) {
		case FIBER_OP_READ_QUEUED:
			if (disk_access_read(page, (addr/BLOCK_SIZE), 1)) {
				SYS_LOG_ERR("!! Disk Read Error %d !",
						addr/BLOCK_SIZE);
			}

			fiber_memory_read_done();
			break;
		case FIBER_OP_WRITE_QUEUED:
			if (disk_access_write(page, (addr/BLOCK_SIZE), 1)) {
				SYS_LOG_ERR("!!!!! Disk Write Error %d !!!!!",
					    addr/BLOCK_SIZE);
			}
			fiber_memory_write_done();
			break;
		default:
			SYS_LOG_ERR("XXXXXX fiber_op  %d ! XXXXX", fiber_op);
		}
	}
}

static uint8_t interface_data[64];
/**
 * @brief Initialize USB mass storage setup
 *
 * This routine is called to reset the USB device controller chip to a
 * quiescent state. Also it initializes the backing storage and initializes
 * the mass storage protocol state.
 *
 * @param dev device struct.
 *
 * @return negative errno code on fatal failure, 0 otherwise
 */
static int mass_storage_init(struct device *dev)
{
	int ret;
	uint32_t block_size = 0;

	if (disk_access_init() != 0) {
		SYS_LOG_ERR("Storage init ERROR !!!! - Aborting USB init");
		return 0;
	}

	if (disk_access_ioctl(DISK_IOCTL_GET_SECTOR_COUNT, &block_count)) {
		SYS_LOG_ERR("Unable to get sector count - Aborting USB init");
		return 0;
	}

	if (disk_access_ioctl(DISK_IOCTL_GET_SECTOR_SIZE, &block_size)) {
		SYS_LOG_ERR("Unable to get sector size - Aborting USB init");
		return 0;
	}

	if (block_size != BLOCK_SIZE) {
		SYS_LOG_ERR("Block Size reported by the storage side is "
		 "different from Mass Storgae Class page Buffer - Aborting");
		return 0;
	}


	SYS_LOG_INF("Sect Count %d", block_count);
	memory_size = block_count * BLOCK_SIZE;
	SYS_LOG_INF("Memory Size %d", memory_size);

	mass_storage_config.interface.payload_data = interface_data;
	msd_state_machine_reset();
	msd_init();

	/* Initialize the USB driver with the right configuration */
	ret = usb_set_config(&mass_storage_config);
	if (ret < 0) {
		SYS_LOG_ERR("Failed to config USB");
		return ret;
	}

	/* Enable USB driver */
	ret = usb_enable(&mass_storage_config);
	if (ret < 0) {
		SYS_LOG_ERR("Failed to enable USB");
		return ret;
	}

	k_sem_init(&disk_wait_sem, 0, 1);

	/* Start a fiber to offload disk ops */
	fiber_start(mass_fiber_stack, DISK_FIBER_STACK_SZ,
		    mass_fiber_main, 0, 0,
		    DISK_FIBER_PRIO, 0);

	return 0;
}

SYS_INIT(mass_storage_init, APPLICATION, CONFIG_KERNEL_INIT_PRIORITY_DEVICE);
