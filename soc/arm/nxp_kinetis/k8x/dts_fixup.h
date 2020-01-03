/*
 * Copyright (c) 2019 SEAL AG
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* SoC level DTS fixup file */
#define DT_NUM_IRQ_PRIO_BITS		DT_ARM_V7M_NVIC_E000E100_ARM_NUM_IRQ_PRIORITY_BITS

#define DT_MCG_NAME			DT_NXP_KINETIS_MCG_40064000_LABEL

#define DT_SIM_NAME			DT_NXP_KINETIS_SIM_40047000_LABEL
#ifdef DT_NXP_KINETIS_SIM_40047000_CLKOUT_DIVIDER
#define DT_SIM_CLKOUT_DIVIDER		DT_NXP_KINETIS_SIM_40047000_CLKOUT_DIVIDER
#endif
#ifdef DT_NXP_KINETIS_SIM_40047000_CLKOUT_SOURCE
#define DT_SIM_CLKOUT_SOURCE		DT_NXP_KINETIS_SIM_40047000_CLKOUT_SOURCE
#endif

#define DT_FLASH_DEV_BASE_ADDRESS	DT_NXP_KINETIS_FTFA_40020000_BASE_ADDRESS
#define DT_FLASH_DEV_NAME		DT_NXP_KINETIS_FTFA_40020000_LABEL

#define DT_ADC_0_BASE_ADDRESS		DT_NXP_KINETIS_ADC16_4003B000_BASE_ADDRESS
#define DT_ADC_0_IRQ			DT_NXP_KINETIS_ADC16_4003B000_IRQ_0
#define DT_ADC_0_IRQ_PRI		DT_NXP_KINETIS_ADC16_4003B000_IRQ_0_PRIORITY
#define DT_ADC_0_NAME			DT_NXP_KINETIS_ADC16_4003B000_LABEL

#define DT_ENTROPY_MCUX_TRNG_BASE_ADDRESS	DT_NXP_KINETIS_TRNG_400A0000_BASE_ADDRESS
#define DT_ENTROPY_MCUX_TRNG_IRQ		DT_NXP_KINETIS_TRNG_400A0000_IRQ_0
#define DT_ENTROPY_MCUX_TRNG_IRQ_PRI		DT_NXP_KINETIS_TRNG_400A0000_IRQ_0_PRIORITY
#define DT_ENTROPY_MCUX_TRNG_NAME		DT_NXP_KINETIS_TRNG_400A0000_LABEL
#define CONFIG_ENTROPY_NAME			DT_NXP_KINETIS_TRNG_400A0000_LABEL

#define DT_I2C_0_NAME		DT_NXP_KINETIS_I2C_40066000_LABEL
#define DT_I2C_MCUX_0_BASE_ADDRESS	DT_NXP_KINETIS_I2C_40066000_BASE_ADDRESS
#define DT_I2C_MCUX_0_IRQ		DT_NXP_KINETIS_I2C_40066000_IRQ_0
#define DT_I2C_MCUX_0_IRQ_PRI		DT_NXP_KINETIS_I2C_40066000_IRQ_0_PRIORITY
#define DT_I2C_MCUX_0_BITRATE		DT_NXP_KINETIS_I2C_40066000_CLOCK_FREQUENCY

#define DT_I2C_1_NAME		DT_NXP_KINETIS_I2C_40067000_LABEL
#define DT_I2C_MCUX_1_BASE_ADDRESS	DT_NXP_KINETIS_I2C_40067000_BASE_ADDRESS
#define DT_I2C_MCUX_1_IRQ		DT_NXP_KINETIS_I2C_40067000_IRQ_0
#define DT_I2C_MCUX_1_IRQ_PRI		DT_NXP_KINETIS_I2C_40067000_IRQ_0_PRIORITY
#define DT_I2C_MCUX_1_BITRATE		DT_NXP_KINETIS_I2C_40067000_CLOCK_FREQUENCY

#define DT_I2C_2_NAME		DT_NXP_KINETIS_I2C_400E6000_LABEL
#define DT_I2C_MCUX_2_BASE_ADDRESS	DT_NXP_KINETIS_I2C_400E6000_BASE_ADDRESS
#define DT_I2C_MCUX_2_IRQ		DT_NXP_KINETIS_I2C_400E6000_IRQ_0
#define DT_I2C_MCUX_2_IRQ_PRI		DT_NXP_KINETIS_I2C_400E6000_IRQ_0_PRIORITY
#define DT_I2C_MCUX_2_BITRATE		DT_NXP_KINETIS_I2C_400E6000_CLOCK_FREQUENCY

#define DT_I2C_3_NAME		DT_NXP_KINETIS_I2C_400E7000_LABEL
#define DT_I2C_MCUX_3_BASE_ADDRESS	DT_NXP_KINETIS_I2C_400E7000_BASE_ADDRESS
#define DT_I2C_MCUX_3_IRQ		DT_NXP_KINETIS_I2C_400E7000_IRQ_0
#define DT_I2C_MCUX_3_IRQ_PRI		DT_NXP_KINETIS_I2C_400E7000_IRQ_0_PRIORITY
#define DT_I2C_MCUX_3_BITRATE		DT_NXP_KINETIS_I2C_400E7000_CLOCK_FREQUENCY

#define DT_RTC_0_NAME			DT_NXP_KINETIS_RTC_4003D000_LABEL
#define DT_RTC_MCUX_0_NAME		DT_NXP_KINETIS_RTC_4003D000_LABEL
#define DT_RTC_MCUX_0_BASE_ADDRESS	DT_NXP_KINETIS_RTC_4003D000_BASE_ADDRESS
#define DT_RTC_MCUX_0_IRQ		DT_NXP_KINETIS_RTC_4003D000_IRQ_ALARM
#define DT_RTC_MCUX_0_IRQ_PRI		DT_NXP_KINETIS_RTC_4003D000_IRQ_ALARM_PRIORITY

#define DT_SPI_0_NAME			DT_NXP_KINETIS_DSPI_4002C000_LABEL
#define DT_SPI_0_BASE_ADDRESS		DT_NXP_KINETIS_DSPI_4002C000_BASE_ADDRESS
#define DT_SPI_0_IRQ			DT_NXP_KINETIS_DSPI_4002C000_IRQ_0
#define DT_SPI_0_IRQ_PRI		DT_NXP_KINETIS_DSPI_4002C000_IRQ_0_PRIORITY
#define DT_SPI_0_CLOCK_NAME		DT_NXP_KINETIS_DSPI_4002C000_CLOCK_CONTROLLER
#define DT_SPI_0_CLOCK_SUBSYS		DT_NXP_KINETIS_DSPI_4002C000_CLOCK_NAME

#define DT_SPI_1_NAME			DT_NXP_KINETIS_DSPI_4002D000_LABEL
#define DT_SPI_1_BASE_ADDRESS		DT_NXP_KINETIS_DSPI_4002D000_BASE_ADDRESS
#define DT_SPI_1_IRQ			DT_NXP_KINETIS_DSPI_4002D000_IRQ_0
#define DT_SPI_1_IRQ_PRI		DT_NXP_KINETIS_DSPI_4002D000_IRQ_0_PRIORITY
#define DT_SPI_1_CLOCK_NAME		DT_NXP_KINETIS_DSPI_4002D000_CLOCK_CONTROLLER
#define DT_SPI_1_CLOCK_SUBSYS		DT_NXP_KINETIS_DSPI_4002D000_CLOCK_NAME

#define DT_SPI_2_NAME			DT_NXP_KINETIS_DSPI_400AC000_LABEL
#define DT_SPI_2_BASE_ADDRESS		DT_NXP_KINETIS_DSPI_400AC000_BASE_ADDRESS
#define DT_SPI_2_IRQ			DT_NXP_KINETIS_DSPI_400AC000_IRQ_0
#define DT_SPI_2_IRQ_PRI		DT_NXP_KINETIS_DSPI_400AC000_IRQ_0_PRIORITY
#define DT_SPI_2_CLOCK_NAME		DT_NXP_KINETIS_DSPI_400AC000_CLOCK_CONTROLLER
#define DT_SPI_2_CLOCK_SUBSYS		DT_NXP_KINETIS_DSPI_400AC000_CLOCK_NAME

#define DT_USBD_KINETIS_NAME		DT_NXP_KINETIS_USBD_40072000_LABEL
#define DT_USBD_KINETIS_IRQ		DT_NXP_KINETIS_USBD_40072000_IRQ_USB_OTG
#define DT_USBD_KINETIS_IRQ_PRI		DT_NXP_KINETIS_USBD_40072000_IRQ_USB_OTG_PRIORITY
#define DT_USBD_KINETIS_BASE_ADDRESS	DT_NXP_KINETIS_USBD_40072000_BASE_ADDRESS
#define DT_USBD_KINETIS_NUM_BIDIR_EP	DT_NXP_KINETIS_USBD_40072000_NUM_BIDIR_ENDPOINTS

#define DT_WDT_0_BASE_ADDRESS		DT_NXP_KINETIS_WDOG_40052000_BASE_ADDRESS
#define DT_WDT_0_IRQ			DT_NXP_KINETIS_WDOG_40052000_IRQ_0
#define DT_WDT_0_IRQ_PRI		DT_NXP_KINETIS_WDOG_40052000_IRQ_0_PRIORITY
#define DT_WDT_0_CLOCK_NAME		DT_NXP_KINETIS_WDOG_40052000_CLOCK_CONTROLLER
#define DT_WDT_0_CLOCK_SUBSYS		DT_NXP_KINETIS_WDOG_40052000_CLOCK_NAME
