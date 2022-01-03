/*
 * Copyright 2020 Broadcom
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef SOC_H
#define SOC_H

#include <sys/util.h>
#include <toolchain.h>

#ifndef _ASMLANGUAGE


/* Interrupt Number Definition */
typedef enum IRQn {
	/* CORTEX-M7 Processor Exceptions Numbers */
	NonMaskableInt_IRQn       = -14, /*< 2  Non Maskable Interrupt            */
	HardFault_IRQn            = -13, /*< 3  HardFault Interrupt               */
	MemoryManagement_IRQn     = -12, /*< 4  Cortex-M7 Memory Management Interrupt */
	BusFault_IRQn             = -11, /*< 5  Cortex-M7 Bus Fault Interrupt     */
	UsageFault_IRQn           = -10, /*< 6  Cortex-M7 Usage Fault Interrupt   */
	SVCall_IRQn               = -5,  /*< 11 Cortex-M7 SV Call Interrupt       */
	DebugMonitor_IRQn         = -4,  /*< 12 Cortex-M7 Debug Monitor Interrupt */
	PendSV_IRQn               = -2,  /*< 14 Cortex-M7 Pend SV Interrupt       */
	SysTick_IRQn              = -1,  /*< 15 Cortex-M7 System Tick Interrupt   */

	/*  VIPER_MPU Specific Interrupt Numbers  */
	M7_RESERVED_0                                     = 0,
	M7_MCU_AON_UART_INTR                              = 1,
	M7_MCU_AON_GPIO_INTR                              = 2,
	M7_CHIPCOMMONG_WDOG_RESET                         = 3,
	M7_RESERVED_4                                     = 4,
	M7_RESERVED_5                                     = 5,
	M7_MCU_SMBUS_INTR                                 = 6,
	M7_MCU_TIMER_INTR                                 = 7,
	M7_MCU_WDOG_INTR                                  = 8,
	M7_MCU_ERROR_LOG_INTR                             = 9,
	M7_MCU_POWER_LOG_INTR                             = 10,
	M7_MCU_RESET_LOG_INTR                             = 11,
	M7_RESERVED_12                                    = 12,
	M7_RESERVED_13                                    = 13,
	M7_MCU_SECURITY_INTR                              = 14,
	M7_AVS_MONITOR_INTR                               = 15,
	M7_AVS_TEMP_RESET_INTR                            = 16,
	M7_GIC_AXI_ERR_INITR                              = 17,
	M7_GIC_ECC_ERR_INITR                              = 18,
	M7_RESERVED_19                                    = 19,
	M7_RESERVED_20                                    = 20,
	M7_RESERVED_21                                    = 21,
	M7_RESERVED_22                                    = 22,
	M7_RESERVED_23                                    = 23,
	M7_RESERVED_24                                    = 24,
	M7_MCU_MAILBOX1_EVENT                             = 25,
	M7_RESERVED_26                                    = 26,
	M7_RESERVED_27                                    = 27,
	M7_RESERVED_28                                    = 28,
	M7_MCU_IPROC_STANDBYWFE_EVENT                     = 29,
	M7_MCU_IPROC_STANDBYWFI_EVENT                     = 30,
	M7_MCU_MAILBOX_EVENT                              = 31,
	M7_MCU_TIMER1_INTR                                = 32,
	M7_MCU_TIMER2_INTR                                = 33,
	M7_MCU_COMB_IDM_INTR                              = 34,
	M7_RESERVED_35                                    = 35,
	M7_RESERVED_36                                    = 36,
	M7_RESERVED_37                                    = 37,
	M7_RESERVED_38                                    = 38,
	M7_RESERVED_39                                    = 39,
	M7_MCU_NS_MAILBOX0_EVENT                          = 40,
	M7_MCU_NS_MAILBOX1_EVENT                          = 41,
	M7_MCU_NS_MAILBOX2_EVENT                          = 42,
	M7_MCU_NS_MAILBOX3_EVENT                          = 43,
	M7_PCIE0_PERSTB_EVENT                             = 44,
	M7_PCIE1_PERSTB_EVENT                             = 45,
	M7_PCIE0_INB_PERSTB_EVENT                         = 46,
	M7_PCIE1_INB_PERSTB_EVENT                         = 47,
	M7_SSIM2_IRQ                                      = 48,
	M7_SSIM2_AFBC_IRQ                                 = 49,
	M7_SSIM2_AFBC_IRQ_AXI_ERR                         = 50,
	M7_SSIM2_AFBC_IRQ_CONFIG_SWAP                     = 51,
	M7_SSIM2_AFBC_IRQ_DECODE_ERR                      = 52,
	M7_SSIM2_AFBC_IRQ_DETLING_ERR                     = 53,
	M7_SSIM2_AFBC_IRQ_SECURE_ID_ERR                   = 54,
	M7_SSIM2_AFBC_IRQ_SURFACES_DONE                   = 55,
	M7_SSIM1_IRQ                                      = 56,
	M7_SSIM1_AFBC_IRQ                                 = 57,
	M7_SSIM1_AFBC_IRQ_AXI_ERR                         = 58,
	M7_SSIM1_AFBC_IRQ_CONFIG_SWAP                     = 59,
	M7_SSIM1_AFBC_IRQ_DECODE_ERR                      = 60,
	M7_SSIM1_AFBC_IRQ_DETLING_ERR                     = 61,
	M7_SSIM1_AFBC_IRQ_SECURE_ID_ERR                   = 62,
	M7_SSIM1_AFBC_IRQ_SURFACES_DONE                   = 63,
	M7_SSIM0_IRQ                                      = 64,
	M7_SSIM0_AFBC_IRQ                                 = 65,
	M7_SSIM0_AFBC_IRQ_AXI_ERR                         = 66,
	M7_SSIM0_AFBC_IRQ_CONFIG_SWAP                     = 67,
	M7_SSIM0_AFBC_IRQ_DECODE_ERR                      = 68,
	M7_SSIM0_AFBC_IRQ_DETLING_ERR                     = 69,
	M7_SSIM0_AFBC_IRQ_SECURE_ID_ERR                   = 70,
	M7_SSIM0_AFBC_IRQ_SURFACES_DONE                   = 71,
	M7_SCL1_IRQ                                       = 72,
	M7_SCL0_IRQ                                       = 73,
	M7_ENC2_IRQ                                       = 74,
	M7_ENC1_IRQ                                       = 75,
	M7_ENC0_IRQ                                       = 76,
	M7_DEC1_IRQ                                       = 77,
	M7_DEC0_IRQ                                       = 78,
	M7_IHOST_CRM_INTERRUPT                            = 79,
	M7_IHOST_NEXTERRIRQ                               = 80,
	M7_IHOST_NINTERRIRQ                               = 81,
	M7_PAXB0_AXI_IBUF_INTR                            = 82,
	M7_PAXB0_GIC_INTR0                                = 83,
	M7_PAXB0_GIC_INTR1                                = 84,
	M7_PAXB0_GIC_INTR2                                = 85,
	M7_PAXB0_GIC_INTR3                                = 86,
	M7_PAXB0_GIC_INTR4                                = 87,
	M7_PAXB0_GIC_INTR5                                = 88,
	M7_PAXB0_GIC_MEM_ERR_INTR                         = 89,
	M7_PAXB0_MSIX_INTR0                               = 90,
	M7_PAXB0_MSIX_INTR1                               = 91,
	M7_PAXB0_MSIX_INTR2                               = 92,
	M7_PAXB0_MSIX_INTR3                               = 93,
	M7_PAXB0_MSIX_INTR4                               = 94,
	M7_PAXB0_MSIX_INTR5                               = 95,
	M7_PAXB0_MSIX_INTR6                               = 96,
	M7_PAXB0_MSIX_INTR7                               = 97,
	M7_PAXB0_MSIX_INTR8                               = 98,
	M7_PAXB0_MSIX_INTR9                               = 99,
	M7_PAXB0_MSIX_INTR10                              = 100,
	M7_PAXB0_MSIX_INTR11                              = 101,
	M7_PAXB0_MSIX_INTR12                              = 102,
	M7_PAXB0_MSIX_INTR13                              = 103,
	M7_PAXB0_MSIX_INTR14                              = 104,
	M7_PAXB0_MSIX_INTR15                              = 105,
	M7_PAXB1_AXI_IBUF_INTR                            = 106,
	M7_PAXB1_GIC_INTR0                                = 107,
	M7_PAXB1_GIC_INTR1                                = 108,
	M7_PAXB1_GIC_INTR2                                = 109,
	M7_PAXB1_GIC_INTR3                                = 110,
	M7_PAXB1_GIC_INTR4                                = 111,
	M7_PAXB1_GIC_INTR5                                = 112,
	M7_PAXB1_GIC_MEM_ERR_INTR                         = 113,
	M7_PAXB1_MSIX_INTR0                               = 114,
	M7_PAXB1_MSIX_INTR1                               = 115,
	M7_PAXB1_MSIX_INTR2                               = 116,
	M7_PAXB1_MSIX_INTR3                               = 117,
	M7_PAXB1_MSIX_INTR4                               = 118,
	M7_PAXB1_MSIX_INTR5                               = 119,
	M7_PAXB1_MSIX_INTR6                               = 120,
	M7_PAXB1_MSIX_INTR7                               = 121,
	M7_PAXB1_MSIX_INTR8                               = 122,
	M7_PAXB1_MSIX_INTR9                               = 123,
	M7_PAXB1_MSIX_INTR10                              = 124,
	M7_PAXB1_MSIX_INTR11                              = 125,
	M7_PAXB1_MSIX_INTR12                              = 126,
	M7_PAXB1_MSIX_INTR13                              = 127,
	M7_PAXB1_MSIX_INTR14                              = 128,
	M7_PAXB1_MSIX_INTR15                              = 129,
	M7_IRQ_PCIE_S0_PINS_BUS                           = 130,
	M7_IRQ_PCIE_S1_PINS_BUS                           = 131,
	M7_IRQ_PCIE_NIC_S_PINS_BUS                        = 132,
	M7_PCIE_GLOBAL_ERR_INTR                           = 133,
	M7_PCIE_ARB_ERR_INTR                              = 134,
	M7_PCIE_RM_ERR_INTR                               = 135,
	M7_VID_MSTR_RESP_ERR_INTR                         = 136,
	M7_SPI_RESERVED3_0                                = 137,
	M7_SPI_RESERVED3_1                                = 138,
	M7_SPI_RESERVED3_2                                = 139,
	M7_SPI_RESERVED3_3                                = 140,
	M7_IRQ_APB_SCR1_PINS_BUS                          = 141,
	M7_IRQ_APB_SCR2_PINS_BUS                          = 142,
	M7_IRQ_CRMU_M0_PINS_BUS                           = 143,
	M7_IRQ_CRMU_S0_PINS_BUS                           = 144,
	M7_IRQ_GIC_S0_PINS_BUS                            = 145,
	M7_SCR_SRAM_INTERRUPT                             = 146,
	M7_SRAM_TZC_INTERRUPT                             = 147,
	M7_PMON_INTERRUPT                                 = 148,
	M7_SPI_RESERVED4_0                                = 149,
	M7_DDR0_TZC_INTERRUPT                             = 150,
	M7_DDR1_TZC_INTERRUPT                             = 151,
	M7_DDR0_INTERRUPT0                                = 152,
	M7_DDR0_INTERRUPT1                                = 153,
	M7_DDR0_INTERRUPT2                                = 154,
	M7_DDR0_INTERRUPT3                                = 155,
	M7_DDR1_INTERRUPT0                                = 156,
	M7_DDR1_INTERRUPT1                                = 157,
	M7_DDR1_INTERRUPT2                                = 158,
	M7_DDR1_INTERRUPT3                                = 159,
	M7_SPI_RESERVED5_0                                = 160,
	M7_SPI_RESERVED5_1                                = 161,
	M7_SPI_RESERVED5_2                                = 162,
	M7_SPI_RESERVED5_3                                = 163,
	M7_SPI_RESERVED5_4                                = 164,
	M7_SPI_RESERVED5_5                                = 165,
	M7_SPI_RESERVED5_6                                = 166,
	M7_SPI_RESERVED5_7                                = 167,
	M7_DMAC_IRQ0                                      = 168,
	M7_DMAC_IRQ1                                      = 169,
	M7_DMAC_IRQ2                                      = 170,
	M7_DMAC_IRQ3                                      = 171,
	M7_DMAC_IRQ4                                      = 172,
	M7_DMAC_IRQ5                                      = 173,
	M7_DMAC_IRQ6                                      = 174,
	M7_DMAC_IRQ7                                      = 175,
	M7_DMAC_IRQ_ABORT                                 = 176,
	M7_ETIMER_0_TM_INTR0                              = 177,
	M7_ETIMER_0_TM_INTR1                              = 178,
	M7_ETIMER_0_TM_INTR2                              = 179,
	M7_ETIMER_0_TM_INTR3                              = 180,
	M7_ETIMER_1_TM_INTR0                              = 181,
	M7_ETIMER_1_TM_INTR1                              = 182,
	M7_ETIMER_1_TM_INTR2                              = 183,
	M7_ETIMER_1_TM_INTR3                              = 184,
	M7_CHIPCOMMONG_MIIM_LINK_SCAN_STATUS_CHANGE_INTR  = 185,
	M7_CHIPCOMMONG_MIIM_OP_DONE_INTR                  = 186,
	M7_CHIPCOMMONG_MIIM_PAUSE_SCAN_STATUS_CHANGE_INTR = 187,
	M7_CHIPCOMMONG_SMBUS0_INTR                        = 188,
	M7_CHIPCOMMONG_SMBUS1_INTR                        = 189,
	M7_CHIPCOMMONG_SPI0_INTR                          = 190,
	M7_CHIPCOMMONG_SPI1_INTR                          = 191,
	M7_CHIPCOMMONG_SPI2_INTR                          = 192,
	M7_CHIPCOMMONG_TIM0_INTR                          = 193,
	M7_CHIPCOMMONG_TIM1_INTR                          = 194,
	M7_CHIPCOMMONG_TIM2_INTR                          = 195,
	M7_CHIPCOMMONG_TIM3_INTR                          = 196,
	M7_CHIPCOMMONG_UART0_INTR                         = 197,
	M7_CHIPCOMMONG_UART1_INTR                         = 198,
	M7_CHIPCOMMONG_UART2_INTR                         = 199,
	M7_CHIPCOMMONG_UART3_INTR                         = 200,
	M7_CHIPCOMMONG_WDOG_INTR                          = 201,
	M7_CHIPCOMMONS_RNG_INTR                           = 202,
	M7_LS_GPIO_INTR                                   = 203,
	M7_NAND_INTERRUPT_O                               = 204,
	M7_QSPI_INTERRUPT_O                               = 205,
	M7_IRQ_APB_LS1_PINS_BUS                           = 206,
	M7_IRQ_APB_LS2_PINS_BUS                           = 207,
	M7_IRQ_APB_LS3_PINS_BUS                           = 208,
	M7_IRQ_CORESIGHT_M0_PINS_BUS                      = 209,
	M7_DMA_ARB_ERR_INTR                               = 210,
	M7_IRQ_NAND_S0_PINS_BUS                           = 211,
	M7_IRQ_QSPI_S0_PINS_BUS                           = 212,
	M7_IRQ_ROM_S0_PINS_BUS                            = 213,
	M7_IRQ_SMAU_S0_PINS_BUS                           = 214,
	M7_SMU_INTR                                       = 215,
	M7_SMU_DMU_PAR_ERR                                = 216,
	M7_SMU_DMU_AUTH_ERR                               = 217,
	M7_SPI_RESERVED6_0                                = 218,
	M7_SPI_RESERVED6_1                                = 219,
	M7_SPI_RESERVED6_2                                = 220,
	M7_SPI_RESERVED6_3                                = 221,
	M7_SPI_RESERVED6_4                                = 222,
	M7_SPI_RESERVED6_5                                = 223,
	M7_SPI_RESERVED6_6                                = 224,
	M7_SPI_RESERVED6_7                                = 225,
	M7_SPI_RESERVED6_8                                = 226,
	M7_SPI_RESERVED6_9                                = 227,
	M7_SPI_RESERVED6_10                               = 228,
	M7_SPI_RESERVED6_11                               = 229,
	M7_SPI_RESERVED6_12                               = 230,
	M7_SPI_RESERVED6_13                               = 231,
	M7_SPI_RESERVED7_0                                = 232,
	M7_SPI_RESERVED7_1                                = 233,
	M7_SPI_RESERVED7_2                                = 234,
	M7_SPI_RESERVED7_3                                = 235,
	M7_SPI_RESERVED7_4                                = 236,
	M7_SPI_RESERVED7_5                                = 237,
	M7_SPI_RESERVED7_6                                = 238,
	M7_SPI_RESERVED7_7                                = 239,
} IRQn_Type;

#endif

/*
 * Processor and Core Peripheral Section
 */

/*
 * \brief Configuration of the CORTEX-M7 Processor and Core Peripherals
 */
#if defined(CONFIG_SOC_BCM58402_M7)
#define __MPU_PRESENT           1
#define __NVIC_PRIO_BITS        NUM_IRQ_PRIO_BITS
#endif

/* Registers block */
#define CRMU_MCU_EXTRA_EVENT_STATUS	0x40070054
#define CRMU_MCU_EXTRA_EVENT_CLEAR	0x4007005c
#define CRMU_MCU_EXTRA_EVENT_MASK	0x40070064
#define PCIE0_PERST_INTR		BIT(4)
#define PCIE0_PERST_INB_INTR		BIT(6)

#define PCIE_PERSTB_INTR_CTL_STS	0x400700f0
#define PCIE0_PERST_FE_INTR		BIT(1)
#define PCIE0_PERST_INB_FE_INTR		BIT(3)

#define PMON_LITE_PCIE_BASE			0x48180000

#define LS_ICFG_PMON_LITE_CLK_CTRL		0x482f00bc
#define PCIE_PMON_LITE_CLK_ENABLE		(BIT(0) | BIT(2))
#define LS_ICFG_PMON_LITE_SW_RESETN		0x482f0120
#define PCIE_PMON_LITE_SW_RESETN		BIT(0)

#endif
