/* SPDX-License-Identifier: Apache-2.0 */

/* SoC level DTS fixup file */

#define DT_ADC_0_BASE_ADDRESS		DT_NXP_KINETIS_ADC16_4003B000_BASE_ADDRESS
#define DT_ADC_0_IRQ			DT_NXP_KINETIS_ADC16_4003B000_IRQ_0
#define DT_ADC_0_IRQ_PRI			DT_NXP_KINETIS_ADC16_4003B000_IRQ_0_PRIORITY
#define DT_ADC_0_NAME			DT_NXP_KINETIS_ADC16_4003B000_LABEL

#define DT_SIM_BASE_ADDRESS			DT_NXP_KINETIS_SIM_40047000_BASE_ADDRESS
#define DT_SIM_NAME				DT_NXP_KINETIS_SIM_40047000_LABEL

#define DT_MCG_NAME				DT_NXP_KINETIS_MCG_40064000_LABEL

#define DT_RTC_0_NAME				DT_NXP_KINETIS_RTC_4003D000_LABEL

#if defined(CONFIG_SOC_MKW22D5) || defined(CONFIG_SOC_MKW24D5)
#define DT_NUM_IRQ_PRIO_BITS		DT_ARM_V7M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS

#define DT_FLASH_DEV_BASE_ADDRESS		DT_NXP_KINETIS_FTFL_40020000_BASE_ADDRESS
#define DT_FLASH_DEV_NAME			DT_NXP_KINETIS_FTFL_40020000_LABEL

#define DT_WDT_0_BASE_ADDRESS		DT_NXP_KINETIS_WDOG_40052000_BASE_ADDRESS
#define DT_WDT_0_IRQ			DT_NXP_KINETIS_WDOG_40052000_IRQ_0
#define DT_WDT_0_IRQ_PRI			DT_NXP_KINETIS_WDOG_40052000_IRQ_0_PRIORITY
#define DT_WDT_0_CLOCK_NAME			DT_NXP_KINETIS_WDOG_40052000_CLOCK_CONTROLLER
#define DT_WDT_0_CLOCK_SUBSYS		DT_NXP_KINETIS_WDOG_40052000_CLOCK_NAME

#define DT_USBD_KINETIS_NAME		DT_NXP_KINETIS_USBD_40072000_LABEL
#define DT_USBD_KINETIS_IRQ			DT_NXP_KINETIS_USBD_40072000_IRQ_USB_OTG
#define DT_USBD_KINETIS_IRQ_PRI		DT_NXP_KINETIS_USBD_40072000_IRQ_USB_OTG_PRIORITY
#define DT_USBD_KINETIS_BASE_ADDRESS	DT_NXP_KINETIS_USBD_40072000_BASE_ADDRESS
#define DT_USBD_KINETIS_NUM_BIDIR_EP	DT_NXP_KINETIS_USBD_40072000_NUM_BIDIR_ENDPOINTS

#define DT_ENTROPY_MCUX_RNGA_BASE_ADDRESS	DT_NXP_KINETIS_RNGA_40029000_BASE_ADDRESS
#define DT_ENTROPY_MCUX_RNGA_IRQ		DT_NXP_KINETIS_RNGA_40029000_IRQ_0
#define DT_ENTROPY_MCUX_RNGA_IRQ_PRI	DT_NXP_KINETIS_RNGA_40029000_IRQ_0_PRIORITY
#define DT_ENTROPY_MCUX_RNGA_NAME		DT_NXP_KINETIS_RNGA_40029000_LABEL
#define CONFIG_ENTROPY_NAME			DT_NXP_KINETIS_RNGA_40029000_LABEL
#endif /* CONFIG_SOC_MKW22D5 || CONFIG_SOC_MKW24D5 */

#if defined(CONFIG_SOC_MKW40Z4) || defined(CONFIG_SOC_MKW41Z4)
#define DT_NUM_IRQ_PRIO_BITS		DT_ARM_V6M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS

#define DT_FLASH_DEV_BASE_ADDRESS		DT_NXP_KINETIS_FTFA_40020000_BASE_ADDRESS
#define DT_FLASH_DEV_NAME			DT_NXP_KINETIS_FTFA_40020000_LABEL

#define DT_ENTROPY_MCUX_TRNG_BASE_ADDRESS	DT_NXP_KINETIS_TRNG_40029000_BASE_ADDRESS
#define DT_ENTROPY_MCUX_TRNG_IRQ		DT_NXP_KINETIS_TRNG_40029000_IRQ_0
#define DT_ENTROPY_MCUX_TRNG_IRQ_PRI	DT_NXP_KINETIS_TRNG_40029000_IRQ_0_PRIORITY
#define DT_ENTROPY_MCUX_TRNG_NAME		DT_NXP_KINETIS_TRNG_40029000_LABEL
#define CONFIG_ENTROPY_NAME			DT_NXP_KINETIS_TRNG_40029000_LABEL

#endif /* CONFIG_SOC_MKW40Z4 || CONFIG_SOC_MKW41Z4 */
/* End of SoC Level DTS fixup file */
