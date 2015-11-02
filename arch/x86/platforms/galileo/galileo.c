/* galileo.c - system/hardware module for the galileo platform */

/*
 * Copyright (c) 2013-2015, Wind River Systems, Inc.
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

/*
 * DESCRIPTION
 * This module provides routines to initialize and support board-level hardware
 * for the galileo platform.
 *
 * Implementation Remarks:
 * Handlers for the secondary serial port have not been added.
 */

#include <nanokernel.h>
#include <init.h>
#include <device.h>
#include <misc/printk.h>
#include <misc/__assert.h>
#include "board.h"
#include <uart.h>
#include <drivers/ioapic.h>
#include <drivers/pic.h>
#include <drivers/pci/pci.h>
#include <drivers/pci/pci_mgr.h>
#include <drivers/loapic.h>
#include <drivers/ioapic.h>


#ifdef CONFIG_PCI_LEGACY_BRIDGE
/**
 *
 * @brief Configure PCI interrupt pin to IRQ mapping
 *
 * The routine detects PCI legacy bridge and if present,
 * configures PCI interrupt pin to IRQ mapping for D:20
 * and D:21 IO Fabric, that contains the following devices:
 * - SPI0, SPI1;
 * - I2C;
 * - GPIO;
 * - UART0, UART1;
 * - SDIO/eMMC, USB, Ethernet.
 */
static int pci_legacy_bridge_irq_config(struct device *unused)
{
	ARG_UNUSED(unused);
	struct pci_dev_info info = {
		.function = PCI_FUNCTION_ANY,
		.bar = PCI_BAR_ANY,
	};
	if (pci_legacy_bridge_detect(&info) == 0) {
		pci_legacy_bridge_configure(&info, 1, PCI_INTA, 16);
		pci_legacy_bridge_configure(&info, 1, PCI_INTB, 17);
		pci_legacy_bridge_configure(&info, 1, PCI_INTC, 18);
		pci_legacy_bridge_configure(&info, 1, PCI_INTD, 19);
	}
	return 0;
}

DECLARE_DEVICE_INIT_CONFIG(pci_legacy_bridge_0, "", pci_legacy_bridge_irq_config, NULL);
pre_kernel_late_init(pci_legacy_bridge_0, NULL);
#endif /* CONFIG_PCI_LEGACY_BRIDGE */

#ifdef CONFIG_IOAPIC
DECLARE_DEVICE_INIT_CONFIG(ioapic_0, "", _ioapic_init, NULL);
pre_kernel_core_init(ioapic_0, NULL);

#endif /* CONFIG_IOAPIC */

#ifdef CONFIG_LOAPIC
DECLARE_DEVICE_INIT_CONFIG(loapic_0, "", _loapic_init, NULL);
pre_kernel_core_init(loapic_0, NULL);

#endif /* CONFIG_LOAPIC */

#if defined(CONFIG_PIC_DISABLE)

DECLARE_DEVICE_INIT_CONFIG(pic_0, "", _i8259_init, NULL);
pre_kernel_core_init(pic_0, NULL);

#endif /* CONFIG_PIC_DISABLE */
