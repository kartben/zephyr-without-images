/* SPDX-License-Identifier: Apache-2.0 */

/* SoC level DTS fixup file */

#define DT_NUM_IRQ_PRIO_BITS			DT_ARM_V7M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS

#define DT_FPGAIO_LED0_GPIO_NAME		DT_ARM_MPS2_FPGAIO_GPIO_40028000_LABEL
#define DT_FPGAIO_LED0_NUM			DT_ARM_MPS2_FPGAIO_GPIO_40028000_NGPIOS
#define DT_FPGAIO_LED0				DT_ARM_MPS2_FPGAIO_GPIO_40028000_BASE_ADDRESS

#define DT_FPGAIO_BUTTON_GPIO_NAME		DT_ARM_MPS2_FPGAIO_GPIO_40028008_LABEL
#define DT_FPGAIO_BUTTON_NUM			DT_ARM_MPS2_FPGAIO_GPIO_40028008_NGPIOS
#define DT_FPGAIO_BUTTON			DT_ARM_MPS2_FPGAIO_GPIO_40028008_BASE_ADDRESS

#define DT_FPGAIO_MISC_GPIO_NAME		DT_ARM_MPS2_FPGAIO_GPIO_4002804C_LABEL
#define DT_FPGAIO_MISC_NUM			DT_ARM_MPS2_FPGAIO_GPIO_4002804C_NGPIOS
#define DT_FPGAIO_MISC				DT_ARM_MPS2_FPGAIO_GPIO_4002804C_BASE_ADDRESS

/* End of SoC Level DTS fixup file */
