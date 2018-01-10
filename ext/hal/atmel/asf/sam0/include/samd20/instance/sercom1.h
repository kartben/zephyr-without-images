/**
 * \file
 *
 * \brief Instance description for SERCOM1
 *
 * Copyright (c) 2017 Microchip Technology Inc.
 *
 * \asf_license_start
 *
 * \page License
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the Licence at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \asf_license_stop
 *
 */

#ifndef _SAMD20_SERCOM1_INSTANCE_
#define _SAMD20_SERCOM1_INSTANCE_

/* ========== Register definition for SERCOM1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_SERCOM1_I2CM_CTRLA     (0x42000C00) /**< \brief (SERCOM1) I2CM Control A */
#define REG_SERCOM1_I2CM_CTRLB     (0x42000C04) /**< \brief (SERCOM1) I2CM Control B */
#define REG_SERCOM1_I2CM_DBGCTRL   (0x42000C08) /**< \brief (SERCOM1) I2CM Debug Control */
#define REG_SERCOM1_I2CM_BAUD      (0x42000C0A) /**< \brief (SERCOM1) I2CM Baud Rate */
#define REG_SERCOM1_I2CM_INTENCLR  (0x42000C0C) /**< \brief (SERCOM1) I2CM Interrupt Enable Clear */
#define REG_SERCOM1_I2CM_INTENSET  (0x42000C0D) /**< \brief (SERCOM1) I2CM Interrupt Enable Set */
#define REG_SERCOM1_I2CM_INTFLAG   (0x42000C0E) /**< \brief (SERCOM1) I2CM Interrupt Flag Status and Clear */
#define REG_SERCOM1_I2CM_STATUS    (0x42000C10) /**< \brief (SERCOM1) I2CM Status */
#define REG_SERCOM1_I2CM_ADDR      (0x42000C14) /**< \brief (SERCOM1) I2CM Address */
#define REG_SERCOM1_I2CM_DATA      (0x42000C18) /**< \brief (SERCOM1) I2CM Data */
#define REG_SERCOM1_I2CS_CTRLA     (0x42000C00) /**< \brief (SERCOM1) I2CS Control A */
#define REG_SERCOM1_I2CS_CTRLB     (0x42000C04) /**< \brief (SERCOM1) I2CS Control B */
#define REG_SERCOM1_I2CS_INTENCLR  (0x42000C0C) /**< \brief (SERCOM1) I2CS Interrupt Enable Clear */
#define REG_SERCOM1_I2CS_INTENSET  (0x42000C0D) /**< \brief (SERCOM1) I2CS Interrupt Enable Set */
#define REG_SERCOM1_I2CS_INTFLAG   (0x42000C0E) /**< \brief (SERCOM1) I2CS Interrupt Flag Status and Clear */
#define REG_SERCOM1_I2CS_STATUS    (0x42000C10) /**< \brief (SERCOM1) I2CS Status */
#define REG_SERCOM1_I2CS_ADDR      (0x42000C14) /**< \brief (SERCOM1) I2CS Address */
#define REG_SERCOM1_I2CS_DATA      (0x42000C18) /**< \brief (SERCOM1) I2CS Data */
#define REG_SERCOM1_SPI_CTRLA      (0x42000C00) /**< \brief (SERCOM1) SPI Control A */
#define REG_SERCOM1_SPI_CTRLB      (0x42000C04) /**< \brief (SERCOM1) SPI Control B */
#define REG_SERCOM1_SPI_DBGCTRL    (0x42000C08) /**< \brief (SERCOM1) SPI Debug Control */
#define REG_SERCOM1_SPI_BAUD       (0x42000C0A) /**< \brief (SERCOM1) SPI Baud Rate */
#define REG_SERCOM1_SPI_INTENCLR   (0x42000C0C) /**< \brief (SERCOM1) SPI Interrupt Enable Clear */
#define REG_SERCOM1_SPI_INTENSET   (0x42000C0D) /**< \brief (SERCOM1) SPI Interrupt Enable Set */
#define REG_SERCOM1_SPI_INTFLAG    (0x42000C0E) /**< \brief (SERCOM1) SPI Interrupt Flag Status and Clear */
#define REG_SERCOM1_SPI_STATUS     (0x42000C10) /**< \brief (SERCOM1) SPI Status */
#define REG_SERCOM1_SPI_ADDR       (0x42000C14) /**< \brief (SERCOM1) SPI Address */
#define REG_SERCOM1_SPI_DATA       (0x42000C18) /**< \brief (SERCOM1) SPI Data */
#define REG_SERCOM1_USART_CTRLA    (0x42000C00) /**< \brief (SERCOM1) USART Control A */
#define REG_SERCOM1_USART_CTRLB    (0x42000C04) /**< \brief (SERCOM1) USART Control B */
#define REG_SERCOM1_USART_DBGCTRL  (0x42000C08) /**< \brief (SERCOM1) USART Debug Control */
#define REG_SERCOM1_USART_BAUD     (0x42000C0A) /**< \brief (SERCOM1) USART Baud */
#define REG_SERCOM1_USART_INTENCLR (0x42000C0C) /**< \brief (SERCOM1) USART Interrupt Enable Clear */
#define REG_SERCOM1_USART_INTENSET (0x42000C0D) /**< \brief (SERCOM1) USART Interrupt Enable Set */
#define REG_SERCOM1_USART_INTFLAG  (0x42000C0E) /**< \brief (SERCOM1) USART Interrupt Flag Status and Clear */
#define REG_SERCOM1_USART_STATUS   (0x42000C10) /**< \brief (SERCOM1) USART Status */
#define REG_SERCOM1_USART_DATA     (0x42000C18) /**< \brief (SERCOM1) USART Data */
#else
#define REG_SERCOM1_I2CM_CTRLA     (*(RwReg  *)0x42000C00UL) /**< \brief (SERCOM1) I2CM Control A */
#define REG_SERCOM1_I2CM_CTRLB     (*(RwReg  *)0x42000C04UL) /**< \brief (SERCOM1) I2CM Control B */
#define REG_SERCOM1_I2CM_DBGCTRL   (*(RwReg8 *)0x42000C08UL) /**< \brief (SERCOM1) I2CM Debug Control */
#define REG_SERCOM1_I2CM_BAUD      (*(RwReg16*)0x42000C0AUL) /**< \brief (SERCOM1) I2CM Baud Rate */
#define REG_SERCOM1_I2CM_INTENCLR  (*(RwReg8 *)0x42000C0CUL) /**< \brief (SERCOM1) I2CM Interrupt Enable Clear */
#define REG_SERCOM1_I2CM_INTENSET  (*(RwReg8 *)0x42000C0DUL) /**< \brief (SERCOM1) I2CM Interrupt Enable Set */
#define REG_SERCOM1_I2CM_INTFLAG   (*(RwReg8 *)0x42000C0EUL) /**< \brief (SERCOM1) I2CM Interrupt Flag Status and Clear */
#define REG_SERCOM1_I2CM_STATUS    (*(RwReg16*)0x42000C10UL) /**< \brief (SERCOM1) I2CM Status */
#define REG_SERCOM1_I2CM_ADDR      (*(RwReg8 *)0x42000C14UL) /**< \brief (SERCOM1) I2CM Address */
#define REG_SERCOM1_I2CM_DATA      (*(RwReg8 *)0x42000C18UL) /**< \brief (SERCOM1) I2CM Data */
#define REG_SERCOM1_I2CS_CTRLA     (*(RwReg  *)0x42000C00UL) /**< \brief (SERCOM1) I2CS Control A */
#define REG_SERCOM1_I2CS_CTRLB     (*(RwReg  *)0x42000C04UL) /**< \brief (SERCOM1) I2CS Control B */
#define REG_SERCOM1_I2CS_INTENCLR  (*(RwReg8 *)0x42000C0CUL) /**< \brief (SERCOM1) I2CS Interrupt Enable Clear */
#define REG_SERCOM1_I2CS_INTENSET  (*(RwReg8 *)0x42000C0DUL) /**< \brief (SERCOM1) I2CS Interrupt Enable Set */
#define REG_SERCOM1_I2CS_INTFLAG   (*(RwReg8 *)0x42000C0EUL) /**< \brief (SERCOM1) I2CS Interrupt Flag Status and Clear */
#define REG_SERCOM1_I2CS_STATUS    (*(RwReg16*)0x42000C10UL) /**< \brief (SERCOM1) I2CS Status */
#define REG_SERCOM1_I2CS_ADDR      (*(RwReg  *)0x42000C14UL) /**< \brief (SERCOM1) I2CS Address */
#define REG_SERCOM1_I2CS_DATA      (*(RwReg8 *)0x42000C18UL) /**< \brief (SERCOM1) I2CS Data */
#define REG_SERCOM1_SPI_CTRLA      (*(RwReg  *)0x42000C00UL) /**< \brief (SERCOM1) SPI Control A */
#define REG_SERCOM1_SPI_CTRLB      (*(RwReg  *)0x42000C04UL) /**< \brief (SERCOM1) SPI Control B */
#define REG_SERCOM1_SPI_DBGCTRL    (*(RwReg8 *)0x42000C08UL) /**< \brief (SERCOM1) SPI Debug Control */
#define REG_SERCOM1_SPI_BAUD       (*(RwReg8 *)0x42000C0AUL) /**< \brief (SERCOM1) SPI Baud Rate */
#define REG_SERCOM1_SPI_INTENCLR   (*(RwReg8 *)0x42000C0CUL) /**< \brief (SERCOM1) SPI Interrupt Enable Clear */
#define REG_SERCOM1_SPI_INTENSET   (*(RwReg8 *)0x42000C0DUL) /**< \brief (SERCOM1) SPI Interrupt Enable Set */
#define REG_SERCOM1_SPI_INTFLAG    (*(RwReg8 *)0x42000C0EUL) /**< \brief (SERCOM1) SPI Interrupt Flag Status and Clear */
#define REG_SERCOM1_SPI_STATUS     (*(RwReg16*)0x42000C10UL) /**< \brief (SERCOM1) SPI Status */
#define REG_SERCOM1_SPI_ADDR       (*(RwReg  *)0x42000C14UL) /**< \brief (SERCOM1) SPI Address */
#define REG_SERCOM1_SPI_DATA       (*(RwReg16*)0x42000C18UL) /**< \brief (SERCOM1) SPI Data */
#define REG_SERCOM1_USART_CTRLA    (*(RwReg  *)0x42000C00UL) /**< \brief (SERCOM1) USART Control A */
#define REG_SERCOM1_USART_CTRLB    (*(RwReg  *)0x42000C04UL) /**< \brief (SERCOM1) USART Control B */
#define REG_SERCOM1_USART_DBGCTRL  (*(RwReg8 *)0x42000C08UL) /**< \brief (SERCOM1) USART Debug Control */
#define REG_SERCOM1_USART_BAUD     (*(RwReg16*)0x42000C0AUL) /**< \brief (SERCOM1) USART Baud */
#define REG_SERCOM1_USART_INTENCLR (*(RwReg8 *)0x42000C0CUL) /**< \brief (SERCOM1) USART Interrupt Enable Clear */
#define REG_SERCOM1_USART_INTENSET (*(RwReg8 *)0x42000C0DUL) /**< \brief (SERCOM1) USART Interrupt Enable Set */
#define REG_SERCOM1_USART_INTFLAG  (*(RwReg8 *)0x42000C0EUL) /**< \brief (SERCOM1) USART Interrupt Flag Status and Clear */
#define REG_SERCOM1_USART_STATUS   (*(RwReg16*)0x42000C10UL) /**< \brief (SERCOM1) USART Status */
#define REG_SERCOM1_USART_DATA     (*(RwReg16*)0x42000C18UL) /**< \brief (SERCOM1) USART Data */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for SERCOM1 peripheral ========== */
#define SERCOM1_GCLK_ID_CORE        14      
#define SERCOM1_GCLK_ID_SLOW        12      
#define SERCOM1_INT_MSB             3       
#define SERCOM1_PMSB                3       

#endif /* _SAMD20_SERCOM1_INSTANCE_ */
