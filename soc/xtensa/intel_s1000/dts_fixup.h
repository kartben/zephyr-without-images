/* SPDX-License-Identifier: Apache-2.0 */

/* SoC level DTS fixup file */

#define DT_CPU_CLOCK_FREQUENCY DT_CADENCE_TENSILICA_XTENSA_LX6_0_CLOCK_FREQUENCY

#define DT_L2_SRAM_BASE				CONFIG_SRAM_BASE_ADDRESS
#define DT_L2_SRAM_SIZE				CONFIG_SRAM_SIZE * 1024

#define DT_LP_SRAM_BASE				DT_REG_ADDR(DT_INST(1, mmio_sram))
#define DT_LP_SRAM_SIZE				DT_REG_SIZE(DT_INST(1, mmio_sram))

#define DT_CAVS_ICTL_BASE_ADDR			DT_INTEL_CAVS_INTC_78800_BASE_ADDRESS
#define DT_CAVS_ICTL_0_IRQ				DT_INTEL_CAVS_INTC_78800_IRQ_0
#define DT_CAVS_ICTL_0_IRQ_PRI		DT_INTEL_CAVS_INTC_78800_IRQ_0_PRIORITY
#define DT_CAVS_ICTL_0_IRQ_FLAGS			DT_INTEL_CAVS_INTC_78800_IRQ_0_SENSE

#define DT_CAVS_ICTL_1_IRQ				DT_INTEL_CAVS_INTC_78810_IRQ_0
#define DT_CAVS_ICTL_1_IRQ_PRI		DT_INTEL_CAVS_INTC_78810_IRQ_0_PRIORITY
#define DT_CAVS_ICTL_1_IRQ_FLAGS			DT_INTEL_CAVS_INTC_78810_IRQ_0_SENSE

#define DT_CAVS_ICTL_2_IRQ				DT_INTEL_CAVS_INTC_78820_IRQ_0
#define DT_CAVS_ICTL_2_IRQ_PRI		DT_INTEL_CAVS_INTC_78820_IRQ_0_PRIORITY
#define DT_CAVS_ICTL_2_IRQ_FLAGS			DT_INTEL_CAVS_INTC_78820_IRQ_0_SENSE

#define DT_CAVS_ICTL_3_IRQ				DT_INTEL_CAVS_INTC_78830_IRQ_0
#define DT_CAVS_ICTL_3_IRQ_PRI		DT_INTEL_CAVS_INTC_78830_IRQ_0_PRIORITY
#define DT_CAVS_ICTL_3_IRQ_FLAGS			DT_INTEL_CAVS_INTC_78830_IRQ_0_SENSE

/* End of SoC Level DTS fixup file */
