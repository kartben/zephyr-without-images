/**
 * \file
 *
 * \brief Component description for SERCOM
 *
 * Copyright (c) 2016 Atmel Corporation,
 *                    a wholly owned subsidiary of Microchip Technology Inc.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the Licence at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \asf_license_stop
 *
 */

#ifndef _SAMD21_SERCOM_COMPONENT_
#define _SAMD21_SERCOM_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR SERCOM */
/* ========================================================================== */
/** \addtogroup SAMD21_SERCOM Serial Communication Interface */
/*@{*/

#define SERCOM_U2201
#define REV_SERCOM                  0x200

/* -------- SERCOM_I2CM_CTRLA : (SERCOM Offset: 0x00) (R/W 32) I2CM I2CM Control A -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t SWRST:1;          /*!< bit:      0  Software Reset                     */
    uint32_t ENABLE:1;         /*!< bit:      1  Enable                             */
    uint32_t MODE:3;           /*!< bit:  2.. 4  Operating Mode                     */
    uint32_t :2;               /*!< bit:  5.. 6  Reserved                           */
    uint32_t RUNSTDBY:1;       /*!< bit:      7  Run in Standby                     */
    uint32_t :8;               /*!< bit:  8..15  Reserved                           */
    uint32_t PINOUT:1;         /*!< bit:     16  Pin Usage                          */
    uint32_t :3;               /*!< bit: 17..19  Reserved                           */
    uint32_t SDAHOLD:2;        /*!< bit: 20..21  SDA Hold Time                      */
    uint32_t MEXTTOEN:1;       /*!< bit:     22  Master SCL Low Extend Timeout      */
    uint32_t SEXTTOEN:1;       /*!< bit:     23  Slave SCL Low Extend Timeout       */
    uint32_t SPEED:2;          /*!< bit: 24..25  Transfer Speed                     */
    uint32_t :1;               /*!< bit:     26  Reserved                           */
    uint32_t SCLSM:1;          /*!< bit:     27  SCL Clock Stretch Mode             */
    uint32_t INACTOUT:2;       /*!< bit: 28..29  Inactive Time-Out                  */
    uint32_t LOWTOUTEN:1;      /*!< bit:     30  SCL Low Timeout Enable             */
    uint32_t :1;               /*!< bit:     31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SERCOM_I2CM_CTRLA_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CM_CTRLA_OFFSET    0x00         /**< \brief (SERCOM_I2CM_CTRLA offset) I2CM Control A */
#define SERCOM_I2CM_CTRLA_RESETVALUE __U(0x00000000) /**< \brief (SERCOM_I2CM_CTRLA reset_value) I2CM Control A */

#define SERCOM_I2CM_CTRLA_SWRST_Pos 0            /**< \brief (SERCOM_I2CM_CTRLA) Software Reset */
#define SERCOM_I2CM_CTRLA_SWRST     (__U(0x1) << SERCOM_I2CM_CTRLA_SWRST_Pos)
#define SERCOM_I2CM_CTRLA_ENABLE_Pos 1            /**< \brief (SERCOM_I2CM_CTRLA) Enable */
#define SERCOM_I2CM_CTRLA_ENABLE    (__U(0x1) << SERCOM_I2CM_CTRLA_ENABLE_Pos)
#define SERCOM_I2CM_CTRLA_MODE_Pos  2            /**< \brief (SERCOM_I2CM_CTRLA) Operating Mode */
#define SERCOM_I2CM_CTRLA_MODE_Msk  (__U(0x7) << SERCOM_I2CM_CTRLA_MODE_Pos)
#define SERCOM_I2CM_CTRLA_MODE(value) (SERCOM_I2CM_CTRLA_MODE_Msk & ((value) << SERCOM_I2CM_CTRLA_MODE_Pos))
#define   SERCOM_I2CM_CTRLA_MODE_USART_EXT_CLK_Val __U(0x0)   /**< \brief (SERCOM_I2CM_CTRLA) USART mode with external clock */
#define   SERCOM_I2CM_CTRLA_MODE_USART_INT_CLK_Val __U(0x1)   /**< \brief (SERCOM_I2CM_CTRLA) USART mode with internal clock */
#define   SERCOM_I2CM_CTRLA_MODE_SPI_SLAVE_Val __U(0x2)   /**< \brief (SERCOM_I2CM_CTRLA) SPI mode with external clock */
#define   SERCOM_I2CM_CTRLA_MODE_SPI_MASTER_Val __U(0x3)   /**< \brief (SERCOM_I2CM_CTRLA) SPI mode with internal clock */
#define   SERCOM_I2CM_CTRLA_MODE_I2C_SLAVE_Val __U(0x4)   /**< \brief (SERCOM_I2CM_CTRLA) I2C mode with external clock */
#define   SERCOM_I2CM_CTRLA_MODE_I2C_MASTER_Val __U(0x5)   /**< \brief (SERCOM_I2CM_CTRLA) I2C mode with internal clock */
#define SERCOM_I2CM_CTRLA_MODE_USART_EXT_CLK (SERCOM_I2CM_CTRLA_MODE_USART_EXT_CLK_Val << SERCOM_I2CM_CTRLA_MODE_Pos)
#define SERCOM_I2CM_CTRLA_MODE_USART_INT_CLK (SERCOM_I2CM_CTRLA_MODE_USART_INT_CLK_Val << SERCOM_I2CM_CTRLA_MODE_Pos)
#define SERCOM_I2CM_CTRLA_MODE_SPI_SLAVE (SERCOM_I2CM_CTRLA_MODE_SPI_SLAVE_Val << SERCOM_I2CM_CTRLA_MODE_Pos)
#define SERCOM_I2CM_CTRLA_MODE_SPI_MASTER (SERCOM_I2CM_CTRLA_MODE_SPI_MASTER_Val << SERCOM_I2CM_CTRLA_MODE_Pos)
#define SERCOM_I2CM_CTRLA_MODE_I2C_SLAVE (SERCOM_I2CM_CTRLA_MODE_I2C_SLAVE_Val << SERCOM_I2CM_CTRLA_MODE_Pos)
#define SERCOM_I2CM_CTRLA_MODE_I2C_MASTER (SERCOM_I2CM_CTRLA_MODE_I2C_MASTER_Val << SERCOM_I2CM_CTRLA_MODE_Pos)
#define SERCOM_I2CM_CTRLA_RUNSTDBY_Pos 7            /**< \brief (SERCOM_I2CM_CTRLA) Run in Standby */
#define SERCOM_I2CM_CTRLA_RUNSTDBY  (__U(0x1) << SERCOM_I2CM_CTRLA_RUNSTDBY_Pos)
#define SERCOM_I2CM_CTRLA_PINOUT_Pos 16           /**< \brief (SERCOM_I2CM_CTRLA) Pin Usage */
#define SERCOM_I2CM_CTRLA_PINOUT    (__U(0x1) << SERCOM_I2CM_CTRLA_PINOUT_Pos)
#define SERCOM_I2CM_CTRLA_SDAHOLD_Pos 20           /**< \brief (SERCOM_I2CM_CTRLA) SDA Hold Time */
#define SERCOM_I2CM_CTRLA_SDAHOLD_Msk (__U(0x3) << SERCOM_I2CM_CTRLA_SDAHOLD_Pos)
#define SERCOM_I2CM_CTRLA_SDAHOLD(value) (SERCOM_I2CM_CTRLA_SDAHOLD_Msk & ((value) << SERCOM_I2CM_CTRLA_SDAHOLD_Pos))
#define SERCOM_I2CM_CTRLA_MEXTTOEN_Pos 22           /**< \brief (SERCOM_I2CM_CTRLA) Master SCL Low Extend Timeout */
#define SERCOM_I2CM_CTRLA_MEXTTOEN  (__U(0x1) << SERCOM_I2CM_CTRLA_MEXTTOEN_Pos)
#define SERCOM_I2CM_CTRLA_SEXTTOEN_Pos 23           /**< \brief (SERCOM_I2CM_CTRLA) Slave SCL Low Extend Timeout */
#define SERCOM_I2CM_CTRLA_SEXTTOEN  (__U(0x1) << SERCOM_I2CM_CTRLA_SEXTTOEN_Pos)
#define SERCOM_I2CM_CTRLA_SPEED_Pos 24           /**< \brief (SERCOM_I2CM_CTRLA) Transfer Speed */
#define SERCOM_I2CM_CTRLA_SPEED_Msk (__U(0x3) << SERCOM_I2CM_CTRLA_SPEED_Pos)
#define SERCOM_I2CM_CTRLA_SPEED(value) (SERCOM_I2CM_CTRLA_SPEED_Msk & ((value) << SERCOM_I2CM_CTRLA_SPEED_Pos))
#define SERCOM_I2CM_CTRLA_SCLSM_Pos 27           /**< \brief (SERCOM_I2CM_CTRLA) SCL Clock Stretch Mode */
#define SERCOM_I2CM_CTRLA_SCLSM     (__U(0x1) << SERCOM_I2CM_CTRLA_SCLSM_Pos)
#define SERCOM_I2CM_CTRLA_INACTOUT_Pos 28           /**< \brief (SERCOM_I2CM_CTRLA) Inactive Time-Out */
#define SERCOM_I2CM_CTRLA_INACTOUT_Msk (__U(0x3) << SERCOM_I2CM_CTRLA_INACTOUT_Pos)
#define SERCOM_I2CM_CTRLA_INACTOUT(value) (SERCOM_I2CM_CTRLA_INACTOUT_Msk & ((value) << SERCOM_I2CM_CTRLA_INACTOUT_Pos))
#define SERCOM_I2CM_CTRLA_LOWTOUTEN_Pos 30           /**< \brief (SERCOM_I2CM_CTRLA) SCL Low Timeout Enable */
#define SERCOM_I2CM_CTRLA_LOWTOUTEN (__U(0x1) << SERCOM_I2CM_CTRLA_LOWTOUTEN_Pos)
#define SERCOM_I2CM_CTRLA_MASK      __U(0x7BF1009F) /**< \brief (SERCOM_I2CM_CTRLA) MASK Register */

/* -------- SERCOM_I2CS_CTRLA : (SERCOM Offset: 0x00) (R/W 32) I2CS I2CS Control A -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t SWRST:1;          /*!< bit:      0  Software Reset                     */
    uint32_t ENABLE:1;         /*!< bit:      1  Enable                             */
    uint32_t MODE:3;           /*!< bit:  2.. 4  Operating Mode                     */
    uint32_t :2;               /*!< bit:  5.. 6  Reserved                           */
    uint32_t RUNSTDBY:1;       /*!< bit:      7  Run during Standby                 */
    uint32_t :8;               /*!< bit:  8..15  Reserved                           */
    uint32_t PINOUT:1;         /*!< bit:     16  Pin Usage                          */
    uint32_t :3;               /*!< bit: 17..19  Reserved                           */
    uint32_t SDAHOLD:2;        /*!< bit: 20..21  SDA Hold Time                      */
    uint32_t :1;               /*!< bit:     22  Reserved                           */
    uint32_t SEXTTOEN:1;       /*!< bit:     23  Slave SCL Low Extend Timeout       */
    uint32_t SPEED:2;          /*!< bit: 24..25  Transfer Speed                     */
    uint32_t :1;               /*!< bit:     26  Reserved                           */
    uint32_t SCLSM:1;          /*!< bit:     27  SCL Clock Stretch Mode             */
    uint32_t :2;               /*!< bit: 28..29  Reserved                           */
    uint32_t LOWTOUTEN:1;      /*!< bit:     30  SCL Low Timeout Enable             */
    uint32_t :1;               /*!< bit:     31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SERCOM_I2CS_CTRLA_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CS_CTRLA_OFFSET    0x00         /**< \brief (SERCOM_I2CS_CTRLA offset) I2CS Control A */
#define SERCOM_I2CS_CTRLA_RESETVALUE __U(0x00000000) /**< \brief (SERCOM_I2CS_CTRLA reset_value) I2CS Control A */

#define SERCOM_I2CS_CTRLA_SWRST_Pos 0            /**< \brief (SERCOM_I2CS_CTRLA) Software Reset */
#define SERCOM_I2CS_CTRLA_SWRST     (__U(0x1) << SERCOM_I2CS_CTRLA_SWRST_Pos)
#define SERCOM_I2CS_CTRLA_ENABLE_Pos 1            /**< \brief (SERCOM_I2CS_CTRLA) Enable */
#define SERCOM_I2CS_CTRLA_ENABLE    (__U(0x1) << SERCOM_I2CS_CTRLA_ENABLE_Pos)
#define SERCOM_I2CS_CTRLA_MODE_Pos  2            /**< \brief (SERCOM_I2CS_CTRLA) Operating Mode */
#define SERCOM_I2CS_CTRLA_MODE_Msk  (__U(0x7) << SERCOM_I2CS_CTRLA_MODE_Pos)
#define SERCOM_I2CS_CTRLA_MODE(value) (SERCOM_I2CS_CTRLA_MODE_Msk & ((value) << SERCOM_I2CS_CTRLA_MODE_Pos))
#define   SERCOM_I2CS_CTRLA_MODE_USART_EXT_CLK_Val __U(0x0)   /**< \brief (SERCOM_I2CS_CTRLA) USART mode with external clock */
#define   SERCOM_I2CS_CTRLA_MODE_USART_INT_CLK_Val __U(0x1)   /**< \brief (SERCOM_I2CS_CTRLA) USART mode with internal clock */
#define   SERCOM_I2CS_CTRLA_MODE_SPI_SLAVE_Val __U(0x2)   /**< \brief (SERCOM_I2CS_CTRLA) SPI mode with external clock */
#define   SERCOM_I2CS_CTRLA_MODE_SPI_MASTER_Val __U(0x3)   /**< \brief (SERCOM_I2CS_CTRLA) SPI mode with internal clock */
#define   SERCOM_I2CS_CTRLA_MODE_I2C_SLAVE_Val __U(0x4)   /**< \brief (SERCOM_I2CS_CTRLA) I2C mode with external clock */
#define   SERCOM_I2CS_CTRLA_MODE_I2C_MASTER_Val __U(0x5)   /**< \brief (SERCOM_I2CS_CTRLA) I2C mode with internal clock */
#define SERCOM_I2CS_CTRLA_MODE_USART_EXT_CLK (SERCOM_I2CS_CTRLA_MODE_USART_EXT_CLK_Val << SERCOM_I2CS_CTRLA_MODE_Pos)
#define SERCOM_I2CS_CTRLA_MODE_USART_INT_CLK (SERCOM_I2CS_CTRLA_MODE_USART_INT_CLK_Val << SERCOM_I2CS_CTRLA_MODE_Pos)
#define SERCOM_I2CS_CTRLA_MODE_SPI_SLAVE (SERCOM_I2CS_CTRLA_MODE_SPI_SLAVE_Val << SERCOM_I2CS_CTRLA_MODE_Pos)
#define SERCOM_I2CS_CTRLA_MODE_SPI_MASTER (SERCOM_I2CS_CTRLA_MODE_SPI_MASTER_Val << SERCOM_I2CS_CTRLA_MODE_Pos)
#define SERCOM_I2CS_CTRLA_MODE_I2C_SLAVE (SERCOM_I2CS_CTRLA_MODE_I2C_SLAVE_Val << SERCOM_I2CS_CTRLA_MODE_Pos)
#define SERCOM_I2CS_CTRLA_MODE_I2C_MASTER (SERCOM_I2CS_CTRLA_MODE_I2C_MASTER_Val << SERCOM_I2CS_CTRLA_MODE_Pos)
#define SERCOM_I2CS_CTRLA_RUNSTDBY_Pos 7            /**< \brief (SERCOM_I2CS_CTRLA) Run during Standby */
#define SERCOM_I2CS_CTRLA_RUNSTDBY  (__U(0x1) << SERCOM_I2CS_CTRLA_RUNSTDBY_Pos)
#define SERCOM_I2CS_CTRLA_PINOUT_Pos 16           /**< \brief (SERCOM_I2CS_CTRLA) Pin Usage */
#define SERCOM_I2CS_CTRLA_PINOUT    (__U(0x1) << SERCOM_I2CS_CTRLA_PINOUT_Pos)
#define SERCOM_I2CS_CTRLA_SDAHOLD_Pos 20           /**< \brief (SERCOM_I2CS_CTRLA) SDA Hold Time */
#define SERCOM_I2CS_CTRLA_SDAHOLD_Msk (__U(0x3) << SERCOM_I2CS_CTRLA_SDAHOLD_Pos)
#define SERCOM_I2CS_CTRLA_SDAHOLD(value) (SERCOM_I2CS_CTRLA_SDAHOLD_Msk & ((value) << SERCOM_I2CS_CTRLA_SDAHOLD_Pos))
#define SERCOM_I2CS_CTRLA_SEXTTOEN_Pos 23           /**< \brief (SERCOM_I2CS_CTRLA) Slave SCL Low Extend Timeout */
#define SERCOM_I2CS_CTRLA_SEXTTOEN  (__U(0x1) << SERCOM_I2CS_CTRLA_SEXTTOEN_Pos)
#define SERCOM_I2CS_CTRLA_SPEED_Pos 24           /**< \brief (SERCOM_I2CS_CTRLA) Transfer Speed */
#define SERCOM_I2CS_CTRLA_SPEED_Msk (__U(0x3) << SERCOM_I2CS_CTRLA_SPEED_Pos)
#define SERCOM_I2CS_CTRLA_SPEED(value) (SERCOM_I2CS_CTRLA_SPEED_Msk & ((value) << SERCOM_I2CS_CTRLA_SPEED_Pos))
#define SERCOM_I2CS_CTRLA_SCLSM_Pos 27           /**< \brief (SERCOM_I2CS_CTRLA) SCL Clock Stretch Mode */
#define SERCOM_I2CS_CTRLA_SCLSM     (__U(0x1) << SERCOM_I2CS_CTRLA_SCLSM_Pos)
#define SERCOM_I2CS_CTRLA_LOWTOUTEN_Pos 30           /**< \brief (SERCOM_I2CS_CTRLA) SCL Low Timeout Enable */
#define SERCOM_I2CS_CTRLA_LOWTOUTEN (__U(0x1) << SERCOM_I2CS_CTRLA_LOWTOUTEN_Pos)
#define SERCOM_I2CS_CTRLA_MASK      __U(0x4BB1009F) /**< \brief (SERCOM_I2CS_CTRLA) MASK Register */

/* -------- SERCOM_SPI_CTRLA : (SERCOM Offset: 0x00) (R/W 32) SPI SPI Control A -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t SWRST:1;          /*!< bit:      0  Software Reset                     */
    uint32_t ENABLE:1;         /*!< bit:      1  Enable                             */
    uint32_t MODE:3;           /*!< bit:  2.. 4  Operating Mode                     */
    uint32_t :2;               /*!< bit:  5.. 6  Reserved                           */
    uint32_t RUNSTDBY:1;       /*!< bit:      7  Run during Standby                 */
    uint32_t IBON:1;           /*!< bit:      8  Immediate Buffer Overflow Notification */
    uint32_t :7;               /*!< bit:  9..15  Reserved                           */
    uint32_t DOPO:2;           /*!< bit: 16..17  Data Out Pinout                    */
    uint32_t :2;               /*!< bit: 18..19  Reserved                           */
    uint32_t DIPO:2;           /*!< bit: 20..21  Data In Pinout                     */
    uint32_t :2;               /*!< bit: 22..23  Reserved                           */
    uint32_t FORM:4;           /*!< bit: 24..27  Frame Format                       */
    uint32_t CPHA:1;           /*!< bit:     28  Clock Phase                        */
    uint32_t CPOL:1;           /*!< bit:     29  Clock Polarity                     */
    uint32_t DORD:1;           /*!< bit:     30  Data Order                         */
    uint32_t :1;               /*!< bit:     31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SERCOM_SPI_CTRLA_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_SPI_CTRLA_OFFSET     0x00         /**< \brief (SERCOM_SPI_CTRLA offset) SPI Control A */
#define SERCOM_SPI_CTRLA_RESETVALUE __U(0x00000000) /**< \brief (SERCOM_SPI_CTRLA reset_value) SPI Control A */

#define SERCOM_SPI_CTRLA_SWRST_Pos  0            /**< \brief (SERCOM_SPI_CTRLA) Software Reset */
#define SERCOM_SPI_CTRLA_SWRST      (__U(0x1) << SERCOM_SPI_CTRLA_SWRST_Pos)
#define SERCOM_SPI_CTRLA_ENABLE_Pos 1            /**< \brief (SERCOM_SPI_CTRLA) Enable */
#define SERCOM_SPI_CTRLA_ENABLE     (__U(0x1) << SERCOM_SPI_CTRLA_ENABLE_Pos)
#define SERCOM_SPI_CTRLA_MODE_Pos   2            /**< \brief (SERCOM_SPI_CTRLA) Operating Mode */
#define SERCOM_SPI_CTRLA_MODE_Msk   (__U(0x7) << SERCOM_SPI_CTRLA_MODE_Pos)
#define SERCOM_SPI_CTRLA_MODE(value) (SERCOM_SPI_CTRLA_MODE_Msk & ((value) << SERCOM_SPI_CTRLA_MODE_Pos))
#define   SERCOM_SPI_CTRLA_MODE_USART_EXT_CLK_Val __U(0x0)   /**< \brief (SERCOM_SPI_CTRLA) USART mode with external clock */
#define   SERCOM_SPI_CTRLA_MODE_USART_INT_CLK_Val __U(0x1)   /**< \brief (SERCOM_SPI_CTRLA) USART mode with internal clock */
#define   SERCOM_SPI_CTRLA_MODE_SPI_SLAVE_Val __U(0x2)   /**< \brief (SERCOM_SPI_CTRLA) SPI mode with external clock */
#define   SERCOM_SPI_CTRLA_MODE_SPI_MASTER_Val __U(0x3)   /**< \brief (SERCOM_SPI_CTRLA) SPI mode with internal clock */
#define   SERCOM_SPI_CTRLA_MODE_I2C_SLAVE_Val __U(0x4)   /**< \brief (SERCOM_SPI_CTRLA) I2C mode with external clock */
#define   SERCOM_SPI_CTRLA_MODE_I2C_MASTER_Val __U(0x5)   /**< \brief (SERCOM_SPI_CTRLA) I2C mode with internal clock */
#define SERCOM_SPI_CTRLA_MODE_USART_EXT_CLK (SERCOM_SPI_CTRLA_MODE_USART_EXT_CLK_Val << SERCOM_SPI_CTRLA_MODE_Pos)
#define SERCOM_SPI_CTRLA_MODE_USART_INT_CLK (SERCOM_SPI_CTRLA_MODE_USART_INT_CLK_Val << SERCOM_SPI_CTRLA_MODE_Pos)
#define SERCOM_SPI_CTRLA_MODE_SPI_SLAVE (SERCOM_SPI_CTRLA_MODE_SPI_SLAVE_Val << SERCOM_SPI_CTRLA_MODE_Pos)
#define SERCOM_SPI_CTRLA_MODE_SPI_MASTER (SERCOM_SPI_CTRLA_MODE_SPI_MASTER_Val << SERCOM_SPI_CTRLA_MODE_Pos)
#define SERCOM_SPI_CTRLA_MODE_I2C_SLAVE (SERCOM_SPI_CTRLA_MODE_I2C_SLAVE_Val << SERCOM_SPI_CTRLA_MODE_Pos)
#define SERCOM_SPI_CTRLA_MODE_I2C_MASTER (SERCOM_SPI_CTRLA_MODE_I2C_MASTER_Val << SERCOM_SPI_CTRLA_MODE_Pos)
#define SERCOM_SPI_CTRLA_RUNSTDBY_Pos 7            /**< \brief (SERCOM_SPI_CTRLA) Run during Standby */
#define SERCOM_SPI_CTRLA_RUNSTDBY   (__U(0x1) << SERCOM_SPI_CTRLA_RUNSTDBY_Pos)
#define SERCOM_SPI_CTRLA_IBON_Pos   8            /**< \brief (SERCOM_SPI_CTRLA) Immediate Buffer Overflow Notification */
#define SERCOM_SPI_CTRLA_IBON       (__U(0x1) << SERCOM_SPI_CTRLA_IBON_Pos)
#define SERCOM_SPI_CTRLA_DOPO_Pos   16           /**< \brief (SERCOM_SPI_CTRLA) Data Out Pinout */
#define SERCOM_SPI_CTRLA_DOPO_Msk   (__U(0x3) << SERCOM_SPI_CTRLA_DOPO_Pos)
#define SERCOM_SPI_CTRLA_DOPO(value) (SERCOM_SPI_CTRLA_DOPO_Msk & ((value) << SERCOM_SPI_CTRLA_DOPO_Pos))
#define SERCOM_SPI_CTRLA_DIPO_Pos   20           /**< \brief (SERCOM_SPI_CTRLA) Data In Pinout */
#define SERCOM_SPI_CTRLA_DIPO_Msk   (__U(0x3) << SERCOM_SPI_CTRLA_DIPO_Pos)
#define SERCOM_SPI_CTRLA_DIPO(value) (SERCOM_SPI_CTRLA_DIPO_Msk & ((value) << SERCOM_SPI_CTRLA_DIPO_Pos))
#define SERCOM_SPI_CTRLA_FORM_Pos   24           /**< \brief (SERCOM_SPI_CTRLA) Frame Format */
#define SERCOM_SPI_CTRLA_FORM_Msk   (__U(0xF) << SERCOM_SPI_CTRLA_FORM_Pos)
#define SERCOM_SPI_CTRLA_FORM(value) (SERCOM_SPI_CTRLA_FORM_Msk & ((value) << SERCOM_SPI_CTRLA_FORM_Pos))
#define SERCOM_SPI_CTRLA_CPHA_Pos   28           /**< \brief (SERCOM_SPI_CTRLA) Clock Phase */
#define SERCOM_SPI_CTRLA_CPHA       (__U(0x1) << SERCOM_SPI_CTRLA_CPHA_Pos)
#define SERCOM_SPI_CTRLA_CPOL_Pos   29           /**< \brief (SERCOM_SPI_CTRLA) Clock Polarity */
#define SERCOM_SPI_CTRLA_CPOL       (__U(0x1) << SERCOM_SPI_CTRLA_CPOL_Pos)
#define SERCOM_SPI_CTRLA_DORD_Pos   30           /**< \brief (SERCOM_SPI_CTRLA) Data Order */
#define SERCOM_SPI_CTRLA_DORD       (__U(0x1) << SERCOM_SPI_CTRLA_DORD_Pos)
#define SERCOM_SPI_CTRLA_MASK       __U(0x7F33019F) /**< \brief (SERCOM_SPI_CTRLA) MASK Register */

/* -------- SERCOM_USART_CTRLA : (SERCOM Offset: 0x00) (R/W 32) USART USART Control A -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t SWRST:1;          /*!< bit:      0  Software Reset                     */
    uint32_t ENABLE:1;         /*!< bit:      1  Enable                             */
    uint32_t MODE:3;           /*!< bit:  2.. 4  Operating Mode                     */
    uint32_t :2;               /*!< bit:  5.. 6  Reserved                           */
    uint32_t RUNSTDBY:1;       /*!< bit:      7  Run during Standby                 */
    uint32_t IBON:1;           /*!< bit:      8  Immediate Buffer Overflow Notification */
    uint32_t :4;               /*!< bit:  9..12  Reserved                           */
    uint32_t SAMPR:3;          /*!< bit: 13..15  Sample                             */
    uint32_t TXPO:2;           /*!< bit: 16..17  Transmit Data Pinout               */
    uint32_t :2;               /*!< bit: 18..19  Reserved                           */
    uint32_t RXPO:2;           /*!< bit: 20..21  Receive Data Pinout                */
    uint32_t SAMPA:2;          /*!< bit: 22..23  Sample Adjustment                  */
    uint32_t FORM:4;           /*!< bit: 24..27  Frame Format                       */
    uint32_t CMODE:1;          /*!< bit:     28  Communication Mode                 */
    uint32_t CPOL:1;           /*!< bit:     29  Clock Polarity                     */
    uint32_t DORD:1;           /*!< bit:     30  Data Order                         */
    uint32_t :1;               /*!< bit:     31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SERCOM_USART_CTRLA_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_USART_CTRLA_OFFSET   0x00         /**< \brief (SERCOM_USART_CTRLA offset) USART Control A */
#define SERCOM_USART_CTRLA_RESETVALUE __U(0x00000000) /**< \brief (SERCOM_USART_CTRLA reset_value) USART Control A */

#define SERCOM_USART_CTRLA_SWRST_Pos 0            /**< \brief (SERCOM_USART_CTRLA) Software Reset */
#define SERCOM_USART_CTRLA_SWRST    (__U(0x1) << SERCOM_USART_CTRLA_SWRST_Pos)
#define SERCOM_USART_CTRLA_ENABLE_Pos 1            /**< \brief (SERCOM_USART_CTRLA) Enable */
#define SERCOM_USART_CTRLA_ENABLE   (__U(0x1) << SERCOM_USART_CTRLA_ENABLE_Pos)
#define SERCOM_USART_CTRLA_MODE_Pos 2            /**< \brief (SERCOM_USART_CTRLA) Operating Mode */
#define SERCOM_USART_CTRLA_MODE_Msk (__U(0x7) << SERCOM_USART_CTRLA_MODE_Pos)
#define SERCOM_USART_CTRLA_MODE(value) (SERCOM_USART_CTRLA_MODE_Msk & ((value) << SERCOM_USART_CTRLA_MODE_Pos))
#define   SERCOM_USART_CTRLA_MODE_USART_EXT_CLK_Val __U(0x0)   /**< \brief (SERCOM_USART_CTRLA) USART mode with external clock */
#define   SERCOM_USART_CTRLA_MODE_USART_INT_CLK_Val __U(0x1)   /**< \brief (SERCOM_USART_CTRLA) USART mode with internal clock */
#define   SERCOM_USART_CTRLA_MODE_SPI_SLAVE_Val __U(0x2)   /**< \brief (SERCOM_USART_CTRLA) SPI mode with external clock */
#define   SERCOM_USART_CTRLA_MODE_SPI_MASTER_Val __U(0x3)   /**< \brief (SERCOM_USART_CTRLA) SPI mode with internal clock */
#define   SERCOM_USART_CTRLA_MODE_I2C_SLAVE_Val __U(0x4)   /**< \brief (SERCOM_USART_CTRLA) I2C mode with external clock */
#define   SERCOM_USART_CTRLA_MODE_I2C_MASTER_Val __U(0x5)   /**< \brief (SERCOM_USART_CTRLA) I2C mode with internal clock */
#define SERCOM_USART_CTRLA_MODE_USART_EXT_CLK (SERCOM_USART_CTRLA_MODE_USART_EXT_CLK_Val << SERCOM_USART_CTRLA_MODE_Pos)
#define SERCOM_USART_CTRLA_MODE_USART_INT_CLK (SERCOM_USART_CTRLA_MODE_USART_INT_CLK_Val << SERCOM_USART_CTRLA_MODE_Pos)
#define SERCOM_USART_CTRLA_MODE_SPI_SLAVE (SERCOM_USART_CTRLA_MODE_SPI_SLAVE_Val << SERCOM_USART_CTRLA_MODE_Pos)
#define SERCOM_USART_CTRLA_MODE_SPI_MASTER (SERCOM_USART_CTRLA_MODE_SPI_MASTER_Val << SERCOM_USART_CTRLA_MODE_Pos)
#define SERCOM_USART_CTRLA_MODE_I2C_SLAVE (SERCOM_USART_CTRLA_MODE_I2C_SLAVE_Val << SERCOM_USART_CTRLA_MODE_Pos)
#define SERCOM_USART_CTRLA_MODE_I2C_MASTER (SERCOM_USART_CTRLA_MODE_I2C_MASTER_Val << SERCOM_USART_CTRLA_MODE_Pos)
#define SERCOM_USART_CTRLA_RUNSTDBY_Pos 7            /**< \brief (SERCOM_USART_CTRLA) Run during Standby */
#define SERCOM_USART_CTRLA_RUNSTDBY (__U(0x1) << SERCOM_USART_CTRLA_RUNSTDBY_Pos)
#define SERCOM_USART_CTRLA_IBON_Pos 8            /**< \brief (SERCOM_USART_CTRLA) Immediate Buffer Overflow Notification */
#define SERCOM_USART_CTRLA_IBON     (__U(0x1) << SERCOM_USART_CTRLA_IBON_Pos)
#define SERCOM_USART_CTRLA_SAMPR_Pos 13           /**< \brief (SERCOM_USART_CTRLA) Sample */
#define SERCOM_USART_CTRLA_SAMPR_Msk (__U(0x7) << SERCOM_USART_CTRLA_SAMPR_Pos)
#define SERCOM_USART_CTRLA_SAMPR(value) (SERCOM_USART_CTRLA_SAMPR_Msk & ((value) << SERCOM_USART_CTRLA_SAMPR_Pos))
#define SERCOM_USART_CTRLA_TXPO_Pos 16           /**< \brief (SERCOM_USART_CTRLA) Transmit Data Pinout */
#define SERCOM_USART_CTRLA_TXPO_Msk (__U(0x3) << SERCOM_USART_CTRLA_TXPO_Pos)
#define SERCOM_USART_CTRLA_TXPO(value) (SERCOM_USART_CTRLA_TXPO_Msk & ((value) << SERCOM_USART_CTRLA_TXPO_Pos))
#define SERCOM_USART_CTRLA_RXPO_Pos 20           /**< \brief (SERCOM_USART_CTRLA) Receive Data Pinout */
#define SERCOM_USART_CTRLA_RXPO_Msk (__U(0x3) << SERCOM_USART_CTRLA_RXPO_Pos)
#define SERCOM_USART_CTRLA_RXPO(value) (SERCOM_USART_CTRLA_RXPO_Msk & ((value) << SERCOM_USART_CTRLA_RXPO_Pos))
#define SERCOM_USART_CTRLA_SAMPA_Pos 22           /**< \brief (SERCOM_USART_CTRLA) Sample Adjustment */
#define SERCOM_USART_CTRLA_SAMPA_Msk (__U(0x3) << SERCOM_USART_CTRLA_SAMPA_Pos)
#define SERCOM_USART_CTRLA_SAMPA(value) (SERCOM_USART_CTRLA_SAMPA_Msk & ((value) << SERCOM_USART_CTRLA_SAMPA_Pos))
#define SERCOM_USART_CTRLA_FORM_Pos 24           /**< \brief (SERCOM_USART_CTRLA) Frame Format */
#define SERCOM_USART_CTRLA_FORM_Msk (__U(0xF) << SERCOM_USART_CTRLA_FORM_Pos)
#define SERCOM_USART_CTRLA_FORM(value) (SERCOM_USART_CTRLA_FORM_Msk & ((value) << SERCOM_USART_CTRLA_FORM_Pos))
#define SERCOM_USART_CTRLA_CMODE_Pos 28           /**< \brief (SERCOM_USART_CTRLA) Communication Mode */
#define SERCOM_USART_CTRLA_CMODE    (__U(0x1) << SERCOM_USART_CTRLA_CMODE_Pos)
#define SERCOM_USART_CTRLA_CPOL_Pos 29           /**< \brief (SERCOM_USART_CTRLA) Clock Polarity */
#define SERCOM_USART_CTRLA_CPOL     (__U(0x1) << SERCOM_USART_CTRLA_CPOL_Pos)
#define SERCOM_USART_CTRLA_DORD_Pos 30           /**< \brief (SERCOM_USART_CTRLA) Data Order */
#define SERCOM_USART_CTRLA_DORD     (__U(0x1) << SERCOM_USART_CTRLA_DORD_Pos)
#define SERCOM_USART_CTRLA_MASK     __U(0x7FF3E19F) /**< \brief (SERCOM_USART_CTRLA) MASK Register */

/* -------- SERCOM_I2CM_CTRLB : (SERCOM Offset: 0x04) (R/W 32) I2CM I2CM Control B -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t :8;               /*!< bit:  0.. 7  Reserved                           */
    uint32_t SMEN:1;           /*!< bit:      8  Smart Mode Enable                  */
    uint32_t QCEN:1;           /*!< bit:      9  Quick Command Enable               */
    uint32_t :6;               /*!< bit: 10..15  Reserved                           */
    uint32_t CMD:2;            /*!< bit: 16..17  Command                            */
    uint32_t ACKACT:1;         /*!< bit:     18  Acknowledge Action                 */
    uint32_t :13;              /*!< bit: 19..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SERCOM_I2CM_CTRLB_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CM_CTRLB_OFFSET    0x04         /**< \brief (SERCOM_I2CM_CTRLB offset) I2CM Control B */
#define SERCOM_I2CM_CTRLB_RESETVALUE __U(0x00000000) /**< \brief (SERCOM_I2CM_CTRLB reset_value) I2CM Control B */

#define SERCOM_I2CM_CTRLB_SMEN_Pos  8            /**< \brief (SERCOM_I2CM_CTRLB) Smart Mode Enable */
#define SERCOM_I2CM_CTRLB_SMEN      (__U(0x1) << SERCOM_I2CM_CTRLB_SMEN_Pos)
#define SERCOM_I2CM_CTRLB_QCEN_Pos  9            /**< \brief (SERCOM_I2CM_CTRLB) Quick Command Enable */
#define SERCOM_I2CM_CTRLB_QCEN      (__U(0x1) << SERCOM_I2CM_CTRLB_QCEN_Pos)
#define SERCOM_I2CM_CTRLB_CMD_Pos   16           /**< \brief (SERCOM_I2CM_CTRLB) Command */
#define SERCOM_I2CM_CTRLB_CMD_Msk   (__U(0x3) << SERCOM_I2CM_CTRLB_CMD_Pos)
#define SERCOM_I2CM_CTRLB_CMD(value) (SERCOM_I2CM_CTRLB_CMD_Msk & ((value) << SERCOM_I2CM_CTRLB_CMD_Pos))
#define SERCOM_I2CM_CTRLB_ACKACT_Pos 18           /**< \brief (SERCOM_I2CM_CTRLB) Acknowledge Action */
#define SERCOM_I2CM_CTRLB_ACKACT    (__U(0x1) << SERCOM_I2CM_CTRLB_ACKACT_Pos)
#define SERCOM_I2CM_CTRLB_MASK      __U(0x00070300) /**< \brief (SERCOM_I2CM_CTRLB) MASK Register */

/* -------- SERCOM_I2CS_CTRLB : (SERCOM Offset: 0x04) (R/W 32) I2CS I2CS Control B -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t :8;               /*!< bit:  0.. 7  Reserved                           */
    uint32_t SMEN:1;           /*!< bit:      8  Smart Mode Enable                  */
    uint32_t GCMD:1;           /*!< bit:      9  PMBus Group Command                */
    uint32_t AACKEN:1;         /*!< bit:     10  Automatic Address Acknowledge      */
    uint32_t :3;               /*!< bit: 11..13  Reserved                           */
    uint32_t AMODE:2;          /*!< bit: 14..15  Address Mode                       */
    uint32_t CMD:2;            /*!< bit: 16..17  Command                            */
    uint32_t ACKACT:1;         /*!< bit:     18  Acknowledge Action                 */
    uint32_t :13;              /*!< bit: 19..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SERCOM_I2CS_CTRLB_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CS_CTRLB_OFFSET    0x04         /**< \brief (SERCOM_I2CS_CTRLB offset) I2CS Control B */
#define SERCOM_I2CS_CTRLB_RESETVALUE __U(0x00000000) /**< \brief (SERCOM_I2CS_CTRLB reset_value) I2CS Control B */

#define SERCOM_I2CS_CTRLB_SMEN_Pos  8            /**< \brief (SERCOM_I2CS_CTRLB) Smart Mode Enable */
#define SERCOM_I2CS_CTRLB_SMEN      (__U(0x1) << SERCOM_I2CS_CTRLB_SMEN_Pos)
#define SERCOM_I2CS_CTRLB_GCMD_Pos  9            /**< \brief (SERCOM_I2CS_CTRLB) PMBus Group Command */
#define SERCOM_I2CS_CTRLB_GCMD      (__U(0x1) << SERCOM_I2CS_CTRLB_GCMD_Pos)
#define SERCOM_I2CS_CTRLB_AACKEN_Pos 10           /**< \brief (SERCOM_I2CS_CTRLB) Automatic Address Acknowledge */
#define SERCOM_I2CS_CTRLB_AACKEN    (__U(0x1) << SERCOM_I2CS_CTRLB_AACKEN_Pos)
#define SERCOM_I2CS_CTRLB_AMODE_Pos 14           /**< \brief (SERCOM_I2CS_CTRLB) Address Mode */
#define SERCOM_I2CS_CTRLB_AMODE_Msk (__U(0x3) << SERCOM_I2CS_CTRLB_AMODE_Pos)
#define SERCOM_I2CS_CTRLB_AMODE(value) (SERCOM_I2CS_CTRLB_AMODE_Msk & ((value) << SERCOM_I2CS_CTRLB_AMODE_Pos))
#define SERCOM_I2CS_CTRLB_CMD_Pos   16           /**< \brief (SERCOM_I2CS_CTRLB) Command */
#define SERCOM_I2CS_CTRLB_CMD_Msk   (__U(0x3) << SERCOM_I2CS_CTRLB_CMD_Pos)
#define SERCOM_I2CS_CTRLB_CMD(value) (SERCOM_I2CS_CTRLB_CMD_Msk & ((value) << SERCOM_I2CS_CTRLB_CMD_Pos))
#define SERCOM_I2CS_CTRLB_ACKACT_Pos 18           /**< \brief (SERCOM_I2CS_CTRLB) Acknowledge Action */
#define SERCOM_I2CS_CTRLB_ACKACT    (__U(0x1) << SERCOM_I2CS_CTRLB_ACKACT_Pos)
#define SERCOM_I2CS_CTRLB_MASK      __U(0x0007C700) /**< \brief (SERCOM_I2CS_CTRLB) MASK Register */

/* -------- SERCOM_SPI_CTRLB : (SERCOM Offset: 0x04) (R/W 32) SPI SPI Control B -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t CHSIZE:3;         /*!< bit:  0.. 2  Character Size                     */
    uint32_t :3;               /*!< bit:  3.. 5  Reserved                           */
    uint32_t PLOADEN:1;        /*!< bit:      6  Data Preload Enable                */
    uint32_t :2;               /*!< bit:  7.. 8  Reserved                           */
    uint32_t SSDE:1;           /*!< bit:      9  Slave Select Low Detect Enable     */
    uint32_t :3;               /*!< bit: 10..12  Reserved                           */
    uint32_t MSSEN:1;          /*!< bit:     13  Master Slave Select Enable         */
    uint32_t AMODE:2;          /*!< bit: 14..15  Address Mode                       */
    uint32_t :1;               /*!< bit:     16  Reserved                           */
    uint32_t RXEN:1;           /*!< bit:     17  Receiver Enable                    */
    uint32_t :14;              /*!< bit: 18..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SERCOM_SPI_CTRLB_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_SPI_CTRLB_OFFSET     0x04         /**< \brief (SERCOM_SPI_CTRLB offset) SPI Control B */
#define SERCOM_SPI_CTRLB_RESETVALUE __U(0x00000000) /**< \brief (SERCOM_SPI_CTRLB reset_value) SPI Control B */

#define SERCOM_SPI_CTRLB_CHSIZE_Pos 0            /**< \brief (SERCOM_SPI_CTRLB) Character Size */
#define SERCOM_SPI_CTRLB_CHSIZE_Msk (__U(0x7) << SERCOM_SPI_CTRLB_CHSIZE_Pos)
#define SERCOM_SPI_CTRLB_CHSIZE(value) (SERCOM_SPI_CTRLB_CHSIZE_Msk & ((value) << SERCOM_SPI_CTRLB_CHSIZE_Pos))
#define SERCOM_SPI_CTRLB_PLOADEN_Pos 6            /**< \brief (SERCOM_SPI_CTRLB) Data Preload Enable */
#define SERCOM_SPI_CTRLB_PLOADEN    (__U(0x1) << SERCOM_SPI_CTRLB_PLOADEN_Pos)
#define SERCOM_SPI_CTRLB_SSDE_Pos   9            /**< \brief (SERCOM_SPI_CTRLB) Slave Select Low Detect Enable */
#define SERCOM_SPI_CTRLB_SSDE       (__U(0x1) << SERCOM_SPI_CTRLB_SSDE_Pos)
#define SERCOM_SPI_CTRLB_MSSEN_Pos  13           /**< \brief (SERCOM_SPI_CTRLB) Master Slave Select Enable */
#define SERCOM_SPI_CTRLB_MSSEN      (__U(0x1) << SERCOM_SPI_CTRLB_MSSEN_Pos)
#define SERCOM_SPI_CTRLB_AMODE_Pos  14           /**< \brief (SERCOM_SPI_CTRLB) Address Mode */
#define SERCOM_SPI_CTRLB_AMODE_Msk  (__U(0x3) << SERCOM_SPI_CTRLB_AMODE_Pos)
#define SERCOM_SPI_CTRLB_AMODE(value) (SERCOM_SPI_CTRLB_AMODE_Msk & ((value) << SERCOM_SPI_CTRLB_AMODE_Pos))
#define SERCOM_SPI_CTRLB_RXEN_Pos   17           /**< \brief (SERCOM_SPI_CTRLB) Receiver Enable */
#define SERCOM_SPI_CTRLB_RXEN       (__U(0x1) << SERCOM_SPI_CTRLB_RXEN_Pos)
#define SERCOM_SPI_CTRLB_MASK       __U(0x0002E247) /**< \brief (SERCOM_SPI_CTRLB) MASK Register */

/* -------- SERCOM_USART_CTRLB : (SERCOM Offset: 0x04) (R/W 32) USART USART Control B -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t CHSIZE:3;         /*!< bit:  0.. 2  Character Size                     */
    uint32_t :3;               /*!< bit:  3.. 5  Reserved                           */
    uint32_t SBMODE:1;         /*!< bit:      6  Stop Bit Mode                      */
    uint32_t :1;               /*!< bit:      7  Reserved                           */
    uint32_t COLDEN:1;         /*!< bit:      8  Collision Detection Enable         */
    uint32_t SFDE:1;           /*!< bit:      9  Start of Frame Detection Enable    */
    uint32_t ENC:1;            /*!< bit:     10  Encoding Format                    */
    uint32_t :2;               /*!< bit: 11..12  Reserved                           */
    uint32_t PMODE:1;          /*!< bit:     13  Parity Mode                        */
    uint32_t :2;               /*!< bit: 14..15  Reserved                           */
    uint32_t TXEN:1;           /*!< bit:     16  Transmitter Enable                 */
    uint32_t RXEN:1;           /*!< bit:     17  Receiver Enable                    */
    uint32_t :14;              /*!< bit: 18..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SERCOM_USART_CTRLB_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_USART_CTRLB_OFFSET   0x04         /**< \brief (SERCOM_USART_CTRLB offset) USART Control B */
#define SERCOM_USART_CTRLB_RESETVALUE __U(0x00000000) /**< \brief (SERCOM_USART_CTRLB reset_value) USART Control B */

#define SERCOM_USART_CTRLB_CHSIZE_Pos 0            /**< \brief (SERCOM_USART_CTRLB) Character Size */
#define SERCOM_USART_CTRLB_CHSIZE_Msk (__U(0x7) << SERCOM_USART_CTRLB_CHSIZE_Pos)
#define SERCOM_USART_CTRLB_CHSIZE(value) (SERCOM_USART_CTRLB_CHSIZE_Msk & ((value) << SERCOM_USART_CTRLB_CHSIZE_Pos))
#define SERCOM_USART_CTRLB_SBMODE_Pos 6            /**< \brief (SERCOM_USART_CTRLB) Stop Bit Mode */
#define SERCOM_USART_CTRLB_SBMODE   (__U(0x1) << SERCOM_USART_CTRLB_SBMODE_Pos)
#define SERCOM_USART_CTRLB_COLDEN_Pos 8            /**< \brief (SERCOM_USART_CTRLB) Collision Detection Enable */
#define SERCOM_USART_CTRLB_COLDEN   (__U(0x1) << SERCOM_USART_CTRLB_COLDEN_Pos)
#define SERCOM_USART_CTRLB_SFDE_Pos 9            /**< \brief (SERCOM_USART_CTRLB) Start of Frame Detection Enable */
#define SERCOM_USART_CTRLB_SFDE     (__U(0x1) << SERCOM_USART_CTRLB_SFDE_Pos)
#define SERCOM_USART_CTRLB_ENC_Pos  10           /**< \brief (SERCOM_USART_CTRLB) Encoding Format */
#define SERCOM_USART_CTRLB_ENC      (__U(0x1) << SERCOM_USART_CTRLB_ENC_Pos)
#define SERCOM_USART_CTRLB_PMODE_Pos 13           /**< \brief (SERCOM_USART_CTRLB) Parity Mode */
#define SERCOM_USART_CTRLB_PMODE    (__U(0x1) << SERCOM_USART_CTRLB_PMODE_Pos)
#define SERCOM_USART_CTRLB_TXEN_Pos 16           /**< \brief (SERCOM_USART_CTRLB) Transmitter Enable */
#define SERCOM_USART_CTRLB_TXEN     (__U(0x1) << SERCOM_USART_CTRLB_TXEN_Pos)
#define SERCOM_USART_CTRLB_RXEN_Pos 17           /**< \brief (SERCOM_USART_CTRLB) Receiver Enable */
#define SERCOM_USART_CTRLB_RXEN     (__U(0x1) << SERCOM_USART_CTRLB_RXEN_Pos)
#define SERCOM_USART_CTRLB_MASK     __U(0x00032747) /**< \brief (SERCOM_USART_CTRLB) MASK Register */

/* -------- SERCOM_I2CM_BAUD : (SERCOM Offset: 0x0C) (R/W 32) I2CM I2CM Baud Rate -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t BAUD:8;           /*!< bit:  0.. 7  Baud Rate Value                    */
    uint32_t BAUDLOW:8;        /*!< bit:  8..15  Baud Rate Value Low                */
    uint32_t HSBAUD:8;         /*!< bit: 16..23  High Speed Baud Rate Value         */
    uint32_t HSBAUDLOW:8;      /*!< bit: 24..31  High Speed Baud Rate Value Low     */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SERCOM_I2CM_BAUD_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CM_BAUD_OFFSET     0x0C         /**< \brief (SERCOM_I2CM_BAUD offset) I2CM Baud Rate */
#define SERCOM_I2CM_BAUD_RESETVALUE __U(0x00000000) /**< \brief (SERCOM_I2CM_BAUD reset_value) I2CM Baud Rate */

#define SERCOM_I2CM_BAUD_BAUD_Pos   0            /**< \brief (SERCOM_I2CM_BAUD) Baud Rate Value */
#define SERCOM_I2CM_BAUD_BAUD_Msk   (__U(0xFF) << SERCOM_I2CM_BAUD_BAUD_Pos)
#define SERCOM_I2CM_BAUD_BAUD(value) (SERCOM_I2CM_BAUD_BAUD_Msk & ((value) << SERCOM_I2CM_BAUD_BAUD_Pos))
#define SERCOM_I2CM_BAUD_BAUDLOW_Pos 8            /**< \brief (SERCOM_I2CM_BAUD) Baud Rate Value Low */
#define SERCOM_I2CM_BAUD_BAUDLOW_Msk (__U(0xFF) << SERCOM_I2CM_BAUD_BAUDLOW_Pos)
#define SERCOM_I2CM_BAUD_BAUDLOW(value) (SERCOM_I2CM_BAUD_BAUDLOW_Msk & ((value) << SERCOM_I2CM_BAUD_BAUDLOW_Pos))
#define SERCOM_I2CM_BAUD_HSBAUD_Pos 16           /**< \brief (SERCOM_I2CM_BAUD) High Speed Baud Rate Value */
#define SERCOM_I2CM_BAUD_HSBAUD_Msk (__U(0xFF) << SERCOM_I2CM_BAUD_HSBAUD_Pos)
#define SERCOM_I2CM_BAUD_HSBAUD(value) (SERCOM_I2CM_BAUD_HSBAUD_Msk & ((value) << SERCOM_I2CM_BAUD_HSBAUD_Pos))
#define SERCOM_I2CM_BAUD_HSBAUDLOW_Pos 24           /**< \brief (SERCOM_I2CM_BAUD) High Speed Baud Rate Value Low */
#define SERCOM_I2CM_BAUD_HSBAUDLOW_Msk (__U(0xFF) << SERCOM_I2CM_BAUD_HSBAUDLOW_Pos)
#define SERCOM_I2CM_BAUD_HSBAUDLOW(value) (SERCOM_I2CM_BAUD_HSBAUDLOW_Msk & ((value) << SERCOM_I2CM_BAUD_HSBAUDLOW_Pos))
#define SERCOM_I2CM_BAUD_MASK       __U(0xFFFFFFFF) /**< \brief (SERCOM_I2CM_BAUD) MASK Register */

/* -------- SERCOM_SPI_BAUD : (SERCOM Offset: 0x0C) (R/W  8) SPI SPI Baud Rate -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  BAUD:8;           /*!< bit:  0.. 7  Baud Rate Value                    */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SERCOM_SPI_BAUD_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_SPI_BAUD_OFFSET      0x0C         /**< \brief (SERCOM_SPI_BAUD offset) SPI Baud Rate */
#define SERCOM_SPI_BAUD_RESETVALUE  __U(0x00)     /**< \brief (SERCOM_SPI_BAUD reset_value) SPI Baud Rate */

#define SERCOM_SPI_BAUD_BAUD_Pos    0            /**< \brief (SERCOM_SPI_BAUD) Baud Rate Value */
#define SERCOM_SPI_BAUD_BAUD_Msk    (__U(0xFF) << SERCOM_SPI_BAUD_BAUD_Pos)
#define SERCOM_SPI_BAUD_BAUD(value) (SERCOM_SPI_BAUD_BAUD_Msk & ((value) << SERCOM_SPI_BAUD_BAUD_Pos))
#define SERCOM_SPI_BAUD_MASK        __U(0xFF)     /**< \brief (SERCOM_SPI_BAUD) MASK Register */

/* -------- SERCOM_USART_BAUD : (SERCOM Offset: 0x0C) (R/W 16) USART USART Baud Rate -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t BAUD:16;          /*!< bit:  0..15  Baud Rate Value                    */
  } bit;                       /*!< Structure used for bit  access                  */
  struct { // FRAC mode
    uint16_t BAUD:13;          /*!< bit:  0..12  Baud Rate Value                    */
    uint16_t FP:3;             /*!< bit: 13..15  Fractional Part                    */
  } FRAC;                      /*!< Structure used for FRAC                         */
  struct { // FRACFP mode
    uint16_t BAUD:13;          /*!< bit:  0..12  Baud Rate Value                    */
    uint16_t FP:3;             /*!< bit: 13..15  Fractional Part                    */
  } FRACFP;                    /*!< Structure used for FRACFP                       */
  struct { // USARTFP mode
    uint16_t BAUD:16;          /*!< bit:  0..15  Baud Rate Value                    */
  } USARTFP;                   /*!< Structure used for USARTFP                      */
  uint16_t reg;                /*!< Type      used for register access              */
} SERCOM_USART_BAUD_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_USART_BAUD_OFFSET    0x0C         /**< \brief (SERCOM_USART_BAUD offset) USART Baud Rate */
#define SERCOM_USART_BAUD_RESETVALUE __U(0x0000)   /**< \brief (SERCOM_USART_BAUD reset_value) USART Baud Rate */

#define SERCOM_USART_BAUD_BAUD_Pos  0            /**< \brief (SERCOM_USART_BAUD) Baud Rate Value */
#define SERCOM_USART_BAUD_BAUD_Msk  (__U(0xFFFF) << SERCOM_USART_BAUD_BAUD_Pos)
#define SERCOM_USART_BAUD_BAUD(value) (SERCOM_USART_BAUD_BAUD_Msk & ((value) << SERCOM_USART_BAUD_BAUD_Pos))
#define SERCOM_USART_BAUD_MASK      __U(0xFFFF)   /**< \brief (SERCOM_USART_BAUD) MASK Register */

// FRAC mode
#define SERCOM_USART_BAUD_FRAC_BAUD_Pos 0            /**< \brief (SERCOM_USART_BAUD_FRAC) Baud Rate Value */
#define SERCOM_USART_BAUD_FRAC_BAUD_Msk (__U(0x1FFF) << SERCOM_USART_BAUD_FRAC_BAUD_Pos)
#define SERCOM_USART_BAUD_FRAC_BAUD(value) (SERCOM_USART_BAUD_FRAC_BAUD_Msk & ((value) << SERCOM_USART_BAUD_FRAC_BAUD_Pos))
#define SERCOM_USART_BAUD_FRAC_FP_Pos 13           /**< \brief (SERCOM_USART_BAUD_FRAC) Fractional Part */
#define SERCOM_USART_BAUD_FRAC_FP_Msk (__U(0x7) << SERCOM_USART_BAUD_FRAC_FP_Pos)
#define SERCOM_USART_BAUD_FRAC_FP(value) (SERCOM_USART_BAUD_FRAC_FP_Msk & ((value) << SERCOM_USART_BAUD_FRAC_FP_Pos))
#define SERCOM_USART_BAUD_FRAC_MASK __U(0xFFFF)   /**< \brief (SERCOM_USART_BAUD_FRAC) MASK Register */

// FRACFP mode
#define SERCOM_USART_BAUD_FRACFP_BAUD_Pos 0            /**< \brief (SERCOM_USART_BAUD_FRACFP) Baud Rate Value */
#define SERCOM_USART_BAUD_FRACFP_BAUD_Msk (__U(0x1FFF) << SERCOM_USART_BAUD_FRACFP_BAUD_Pos)
#define SERCOM_USART_BAUD_FRACFP_BAUD(value) (SERCOM_USART_BAUD_FRACFP_BAUD_Msk & ((value) << SERCOM_USART_BAUD_FRACFP_BAUD_Pos))
#define SERCOM_USART_BAUD_FRACFP_FP_Pos 13           /**< \brief (SERCOM_USART_BAUD_FRACFP) Fractional Part */
#define SERCOM_USART_BAUD_FRACFP_FP_Msk (__U(0x7) << SERCOM_USART_BAUD_FRACFP_FP_Pos)
#define SERCOM_USART_BAUD_FRACFP_FP(value) (SERCOM_USART_BAUD_FRACFP_FP_Msk & ((value) << SERCOM_USART_BAUD_FRACFP_FP_Pos))
#define SERCOM_USART_BAUD_FRACFP_MASK __U(0xFFFF)   /**< \brief (SERCOM_USART_BAUD_FRACFP) MASK Register */

// USARTFP mode
#define SERCOM_USART_BAUD_USARTFP_BAUD_Pos 0            /**< \brief (SERCOM_USART_BAUD_USARTFP) Baud Rate Value */
#define SERCOM_USART_BAUD_USARTFP_BAUD_Msk (__U(0xFFFF) << SERCOM_USART_BAUD_USARTFP_BAUD_Pos)
#define SERCOM_USART_BAUD_USARTFP_BAUD(value) (SERCOM_USART_BAUD_USARTFP_BAUD_Msk & ((value) << SERCOM_USART_BAUD_USARTFP_BAUD_Pos))
#define SERCOM_USART_BAUD_USARTFP_MASK __U(0xFFFF)   /**< \brief (SERCOM_USART_BAUD_USARTFP) MASK Register */

/* -------- SERCOM_USART_RXPL : (SERCOM Offset: 0x0E) (R/W  8) USART USART Receive Pulse Length -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  RXPL:8;           /*!< bit:  0.. 7  Receive Pulse Length               */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SERCOM_USART_RXPL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_USART_RXPL_OFFSET    0x0E         /**< \brief (SERCOM_USART_RXPL offset) USART Receive Pulse Length */
#define SERCOM_USART_RXPL_RESETVALUE __U(0x00)     /**< \brief (SERCOM_USART_RXPL reset_value) USART Receive Pulse Length */

#define SERCOM_USART_RXPL_RXPL_Pos  0            /**< \brief (SERCOM_USART_RXPL) Receive Pulse Length */
#define SERCOM_USART_RXPL_RXPL_Msk  (__U(0xFF) << SERCOM_USART_RXPL_RXPL_Pos)
#define SERCOM_USART_RXPL_RXPL(value) (SERCOM_USART_RXPL_RXPL_Msk & ((value) << SERCOM_USART_RXPL_RXPL_Pos))
#define SERCOM_USART_RXPL_MASK      __U(0xFF)     /**< \brief (SERCOM_USART_RXPL) MASK Register */

/* -------- SERCOM_I2CM_INTENCLR : (SERCOM Offset: 0x14) (R/W  8) I2CM I2CM Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  MB:1;             /*!< bit:      0  Master On Bus Interrupt Disable    */
    uint8_t  SB:1;             /*!< bit:      1  Slave On Bus Interrupt Disable     */
    uint8_t  :5;               /*!< bit:  2.. 6  Reserved                           */
    uint8_t  ERROR:1;          /*!< bit:      7  Combined Error Interrupt Disable   */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SERCOM_I2CM_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CM_INTENCLR_OFFSET 0x14         /**< \brief (SERCOM_I2CM_INTENCLR offset) I2CM Interrupt Enable Clear */
#define SERCOM_I2CM_INTENCLR_RESETVALUE __U(0x00)     /**< \brief (SERCOM_I2CM_INTENCLR reset_value) I2CM Interrupt Enable Clear */

#define SERCOM_I2CM_INTENCLR_MB_Pos 0            /**< \brief (SERCOM_I2CM_INTENCLR) Master On Bus Interrupt Disable */
#define SERCOM_I2CM_INTENCLR_MB     (__U(0x1) << SERCOM_I2CM_INTENCLR_MB_Pos)
#define SERCOM_I2CM_INTENCLR_SB_Pos 1            /**< \brief (SERCOM_I2CM_INTENCLR) Slave On Bus Interrupt Disable */
#define SERCOM_I2CM_INTENCLR_SB     (__U(0x1) << SERCOM_I2CM_INTENCLR_SB_Pos)
#define SERCOM_I2CM_INTENCLR_ERROR_Pos 7            /**< \brief (SERCOM_I2CM_INTENCLR) Combined Error Interrupt Disable */
#define SERCOM_I2CM_INTENCLR_ERROR  (__U(0x1) << SERCOM_I2CM_INTENCLR_ERROR_Pos)
#define SERCOM_I2CM_INTENCLR_MASK   __U(0x83)     /**< \brief (SERCOM_I2CM_INTENCLR) MASK Register */

/* -------- SERCOM_I2CS_INTENCLR : (SERCOM Offset: 0x14) (R/W  8) I2CS I2CS Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  PREC:1;           /*!< bit:      0  Stop Received Interrupt Disable    */
    uint8_t  AMATCH:1;         /*!< bit:      1  Address Match Interrupt Disable    */
    uint8_t  DRDY:1;           /*!< bit:      2  Data Interrupt Disable             */
    uint8_t  :4;               /*!< bit:  3.. 6  Reserved                           */
    uint8_t  ERROR:1;          /*!< bit:      7  Combined Error Interrupt Disable   */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SERCOM_I2CS_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CS_INTENCLR_OFFSET 0x14         /**< \brief (SERCOM_I2CS_INTENCLR offset) I2CS Interrupt Enable Clear */
#define SERCOM_I2CS_INTENCLR_RESETVALUE __U(0x00)     /**< \brief (SERCOM_I2CS_INTENCLR reset_value) I2CS Interrupt Enable Clear */

#define SERCOM_I2CS_INTENCLR_PREC_Pos 0            /**< \brief (SERCOM_I2CS_INTENCLR) Stop Received Interrupt Disable */
#define SERCOM_I2CS_INTENCLR_PREC   (__U(0x1) << SERCOM_I2CS_INTENCLR_PREC_Pos)
#define SERCOM_I2CS_INTENCLR_AMATCH_Pos 1            /**< \brief (SERCOM_I2CS_INTENCLR) Address Match Interrupt Disable */
#define SERCOM_I2CS_INTENCLR_AMATCH (__U(0x1) << SERCOM_I2CS_INTENCLR_AMATCH_Pos)
#define SERCOM_I2CS_INTENCLR_DRDY_Pos 2            /**< \brief (SERCOM_I2CS_INTENCLR) Data Interrupt Disable */
#define SERCOM_I2CS_INTENCLR_DRDY   (__U(0x1) << SERCOM_I2CS_INTENCLR_DRDY_Pos)
#define SERCOM_I2CS_INTENCLR_ERROR_Pos 7            /**< \brief (SERCOM_I2CS_INTENCLR) Combined Error Interrupt Disable */
#define SERCOM_I2CS_INTENCLR_ERROR  (__U(0x1) << SERCOM_I2CS_INTENCLR_ERROR_Pos)
#define SERCOM_I2CS_INTENCLR_MASK   __U(0x87)     /**< \brief (SERCOM_I2CS_INTENCLR) MASK Register */

/* -------- SERCOM_SPI_INTENCLR : (SERCOM Offset: 0x14) (R/W  8) SPI SPI Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  DRE:1;            /*!< bit:      0  Data Register Empty Interrupt Disable */
    uint8_t  TXC:1;            /*!< bit:      1  Transmit Complete Interrupt Disable */
    uint8_t  RXC:1;            /*!< bit:      2  Receive Complete Interrupt Disable */
    uint8_t  SSL:1;            /*!< bit:      3  Slave Select Low Interrupt Disable */
    uint8_t  :3;               /*!< bit:  4.. 6  Reserved                           */
    uint8_t  ERROR:1;          /*!< bit:      7  Combined Error Interrupt Disable   */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SERCOM_SPI_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_SPI_INTENCLR_OFFSET  0x14         /**< \brief (SERCOM_SPI_INTENCLR offset) SPI Interrupt Enable Clear */
#define SERCOM_SPI_INTENCLR_RESETVALUE __U(0x00)     /**< \brief (SERCOM_SPI_INTENCLR reset_value) SPI Interrupt Enable Clear */

#define SERCOM_SPI_INTENCLR_DRE_Pos 0            /**< \brief (SERCOM_SPI_INTENCLR) Data Register Empty Interrupt Disable */
#define SERCOM_SPI_INTENCLR_DRE     (__U(0x1) << SERCOM_SPI_INTENCLR_DRE_Pos)
#define SERCOM_SPI_INTENCLR_TXC_Pos 1            /**< \brief (SERCOM_SPI_INTENCLR) Transmit Complete Interrupt Disable */
#define SERCOM_SPI_INTENCLR_TXC     (__U(0x1) << SERCOM_SPI_INTENCLR_TXC_Pos)
#define SERCOM_SPI_INTENCLR_RXC_Pos 2            /**< \brief (SERCOM_SPI_INTENCLR) Receive Complete Interrupt Disable */
#define SERCOM_SPI_INTENCLR_RXC     (__U(0x1) << SERCOM_SPI_INTENCLR_RXC_Pos)
#define SERCOM_SPI_INTENCLR_SSL_Pos 3            /**< \brief (SERCOM_SPI_INTENCLR) Slave Select Low Interrupt Disable */
#define SERCOM_SPI_INTENCLR_SSL     (__U(0x1) << SERCOM_SPI_INTENCLR_SSL_Pos)
#define SERCOM_SPI_INTENCLR_ERROR_Pos 7            /**< \brief (SERCOM_SPI_INTENCLR) Combined Error Interrupt Disable */
#define SERCOM_SPI_INTENCLR_ERROR   (__U(0x1) << SERCOM_SPI_INTENCLR_ERROR_Pos)
#define SERCOM_SPI_INTENCLR_MASK    __U(0x8F)     /**< \brief (SERCOM_SPI_INTENCLR) MASK Register */

/* -------- SERCOM_USART_INTENCLR : (SERCOM Offset: 0x14) (R/W  8) USART USART Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  DRE:1;            /*!< bit:      0  Data Register Empty Interrupt Disable */
    uint8_t  TXC:1;            /*!< bit:      1  Transmit Complete Interrupt Disable */
    uint8_t  RXC:1;            /*!< bit:      2  Receive Complete Interrupt Disable */
    uint8_t  RXS:1;            /*!< bit:      3  Receive Start Interrupt Disable    */
    uint8_t  CTSIC:1;          /*!< bit:      4  Clear To Send Input Change Interrupt Disable */
    uint8_t  RXBRK:1;          /*!< bit:      5  Break Received Interrupt Disable   */
    uint8_t  :1;               /*!< bit:      6  Reserved                           */
    uint8_t  ERROR:1;          /*!< bit:      7  Combined Error Interrupt Disable   */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SERCOM_USART_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_USART_INTENCLR_OFFSET 0x14         /**< \brief (SERCOM_USART_INTENCLR offset) USART Interrupt Enable Clear */
#define SERCOM_USART_INTENCLR_RESETVALUE __U(0x00)     /**< \brief (SERCOM_USART_INTENCLR reset_value) USART Interrupt Enable Clear */

#define SERCOM_USART_INTENCLR_DRE_Pos 0            /**< \brief (SERCOM_USART_INTENCLR) Data Register Empty Interrupt Disable */
#define SERCOM_USART_INTENCLR_DRE   (__U(0x1) << SERCOM_USART_INTENCLR_DRE_Pos)
#define SERCOM_USART_INTENCLR_TXC_Pos 1            /**< \brief (SERCOM_USART_INTENCLR) Transmit Complete Interrupt Disable */
#define SERCOM_USART_INTENCLR_TXC   (__U(0x1) << SERCOM_USART_INTENCLR_TXC_Pos)
#define SERCOM_USART_INTENCLR_RXC_Pos 2            /**< \brief (SERCOM_USART_INTENCLR) Receive Complete Interrupt Disable */
#define SERCOM_USART_INTENCLR_RXC   (__U(0x1) << SERCOM_USART_INTENCLR_RXC_Pos)
#define SERCOM_USART_INTENCLR_RXS_Pos 3            /**< \brief (SERCOM_USART_INTENCLR) Receive Start Interrupt Disable */
#define SERCOM_USART_INTENCLR_RXS   (__U(0x1) << SERCOM_USART_INTENCLR_RXS_Pos)
#define SERCOM_USART_INTENCLR_CTSIC_Pos 4            /**< \brief (SERCOM_USART_INTENCLR) Clear To Send Input Change Interrupt Disable */
#define SERCOM_USART_INTENCLR_CTSIC (__U(0x1) << SERCOM_USART_INTENCLR_CTSIC_Pos)
#define SERCOM_USART_INTENCLR_RXBRK_Pos 5            /**< \brief (SERCOM_USART_INTENCLR) Break Received Interrupt Disable */
#define SERCOM_USART_INTENCLR_RXBRK (__U(0x1) << SERCOM_USART_INTENCLR_RXBRK_Pos)
#define SERCOM_USART_INTENCLR_ERROR_Pos 7            /**< \brief (SERCOM_USART_INTENCLR) Combined Error Interrupt Disable */
#define SERCOM_USART_INTENCLR_ERROR (__U(0x1) << SERCOM_USART_INTENCLR_ERROR_Pos)
#define SERCOM_USART_INTENCLR_MASK  __U(0xBF)     /**< \brief (SERCOM_USART_INTENCLR) MASK Register */

/* -------- SERCOM_I2CM_INTENSET : (SERCOM Offset: 0x16) (R/W  8) I2CM I2CM Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  MB:1;             /*!< bit:      0  Master On Bus Interrupt Enable     */
    uint8_t  SB:1;             /*!< bit:      1  Slave On Bus Interrupt Enable      */
    uint8_t  :5;               /*!< bit:  2.. 6  Reserved                           */
    uint8_t  ERROR:1;          /*!< bit:      7  Combined Error Interrupt Enable    */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SERCOM_I2CM_INTENSET_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CM_INTENSET_OFFSET 0x16         /**< \brief (SERCOM_I2CM_INTENSET offset) I2CM Interrupt Enable Set */
#define SERCOM_I2CM_INTENSET_RESETVALUE __U(0x00)     /**< \brief (SERCOM_I2CM_INTENSET reset_value) I2CM Interrupt Enable Set */

#define SERCOM_I2CM_INTENSET_MB_Pos 0            /**< \brief (SERCOM_I2CM_INTENSET) Master On Bus Interrupt Enable */
#define SERCOM_I2CM_INTENSET_MB     (__U(0x1) << SERCOM_I2CM_INTENSET_MB_Pos)
#define SERCOM_I2CM_INTENSET_SB_Pos 1            /**< \brief (SERCOM_I2CM_INTENSET) Slave On Bus Interrupt Enable */
#define SERCOM_I2CM_INTENSET_SB     (__U(0x1) << SERCOM_I2CM_INTENSET_SB_Pos)
#define SERCOM_I2CM_INTENSET_ERROR_Pos 7            /**< \brief (SERCOM_I2CM_INTENSET) Combined Error Interrupt Enable */
#define SERCOM_I2CM_INTENSET_ERROR  (__U(0x1) << SERCOM_I2CM_INTENSET_ERROR_Pos)
#define SERCOM_I2CM_INTENSET_MASK   __U(0x83)     /**< \brief (SERCOM_I2CM_INTENSET) MASK Register */

/* -------- SERCOM_I2CS_INTENSET : (SERCOM Offset: 0x16) (R/W  8) I2CS I2CS Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  PREC:1;           /*!< bit:      0  Stop Received Interrupt Enable     */
    uint8_t  AMATCH:1;         /*!< bit:      1  Address Match Interrupt Enable     */
    uint8_t  DRDY:1;           /*!< bit:      2  Data Interrupt Enable              */
    uint8_t  :4;               /*!< bit:  3.. 6  Reserved                           */
    uint8_t  ERROR:1;          /*!< bit:      7  Combined Error Interrupt Enable    */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SERCOM_I2CS_INTENSET_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CS_INTENSET_OFFSET 0x16         /**< \brief (SERCOM_I2CS_INTENSET offset) I2CS Interrupt Enable Set */
#define SERCOM_I2CS_INTENSET_RESETVALUE __U(0x00)     /**< \brief (SERCOM_I2CS_INTENSET reset_value) I2CS Interrupt Enable Set */

#define SERCOM_I2CS_INTENSET_PREC_Pos 0            /**< \brief (SERCOM_I2CS_INTENSET) Stop Received Interrupt Enable */
#define SERCOM_I2CS_INTENSET_PREC   (__U(0x1) << SERCOM_I2CS_INTENSET_PREC_Pos)
#define SERCOM_I2CS_INTENSET_AMATCH_Pos 1            /**< \brief (SERCOM_I2CS_INTENSET) Address Match Interrupt Enable */
#define SERCOM_I2CS_INTENSET_AMATCH (__U(0x1) << SERCOM_I2CS_INTENSET_AMATCH_Pos)
#define SERCOM_I2CS_INTENSET_DRDY_Pos 2            /**< \brief (SERCOM_I2CS_INTENSET) Data Interrupt Enable */
#define SERCOM_I2CS_INTENSET_DRDY   (__U(0x1) << SERCOM_I2CS_INTENSET_DRDY_Pos)
#define SERCOM_I2CS_INTENSET_ERROR_Pos 7            /**< \brief (SERCOM_I2CS_INTENSET) Combined Error Interrupt Enable */
#define SERCOM_I2CS_INTENSET_ERROR  (__U(0x1) << SERCOM_I2CS_INTENSET_ERROR_Pos)
#define SERCOM_I2CS_INTENSET_MASK   __U(0x87)     /**< \brief (SERCOM_I2CS_INTENSET) MASK Register */

/* -------- SERCOM_SPI_INTENSET : (SERCOM Offset: 0x16) (R/W  8) SPI SPI Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  DRE:1;            /*!< bit:      0  Data Register Empty Interrupt Enable */
    uint8_t  TXC:1;            /*!< bit:      1  Transmit Complete Interrupt Enable */
    uint8_t  RXC:1;            /*!< bit:      2  Receive Complete Interrupt Enable  */
    uint8_t  SSL:1;            /*!< bit:      3  Slave Select Low Interrupt Enable  */
    uint8_t  :3;               /*!< bit:  4.. 6  Reserved                           */
    uint8_t  ERROR:1;          /*!< bit:      7  Combined Error Interrupt Enable    */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SERCOM_SPI_INTENSET_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_SPI_INTENSET_OFFSET  0x16         /**< \brief (SERCOM_SPI_INTENSET offset) SPI Interrupt Enable Set */
#define SERCOM_SPI_INTENSET_RESETVALUE __U(0x00)     /**< \brief (SERCOM_SPI_INTENSET reset_value) SPI Interrupt Enable Set */

#define SERCOM_SPI_INTENSET_DRE_Pos 0            /**< \brief (SERCOM_SPI_INTENSET) Data Register Empty Interrupt Enable */
#define SERCOM_SPI_INTENSET_DRE     (__U(0x1) << SERCOM_SPI_INTENSET_DRE_Pos)
#define SERCOM_SPI_INTENSET_TXC_Pos 1            /**< \brief (SERCOM_SPI_INTENSET) Transmit Complete Interrupt Enable */
#define SERCOM_SPI_INTENSET_TXC     (__U(0x1) << SERCOM_SPI_INTENSET_TXC_Pos)
#define SERCOM_SPI_INTENSET_RXC_Pos 2            /**< \brief (SERCOM_SPI_INTENSET) Receive Complete Interrupt Enable */
#define SERCOM_SPI_INTENSET_RXC     (__U(0x1) << SERCOM_SPI_INTENSET_RXC_Pos)
#define SERCOM_SPI_INTENSET_SSL_Pos 3            /**< \brief (SERCOM_SPI_INTENSET) Slave Select Low Interrupt Enable */
#define SERCOM_SPI_INTENSET_SSL     (__U(0x1) << SERCOM_SPI_INTENSET_SSL_Pos)
#define SERCOM_SPI_INTENSET_ERROR_Pos 7            /**< \brief (SERCOM_SPI_INTENSET) Combined Error Interrupt Enable */
#define SERCOM_SPI_INTENSET_ERROR   (__U(0x1) << SERCOM_SPI_INTENSET_ERROR_Pos)
#define SERCOM_SPI_INTENSET_MASK    __U(0x8F)     /**< \brief (SERCOM_SPI_INTENSET) MASK Register */

/* -------- SERCOM_USART_INTENSET : (SERCOM Offset: 0x16) (R/W  8) USART USART Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  DRE:1;            /*!< bit:      0  Data Register Empty Interrupt Enable */
    uint8_t  TXC:1;            /*!< bit:      1  Transmit Complete Interrupt Enable */
    uint8_t  RXC:1;            /*!< bit:      2  Receive Complete Interrupt Enable  */
    uint8_t  RXS:1;            /*!< bit:      3  Receive Start Interrupt Enable     */
    uint8_t  CTSIC:1;          /*!< bit:      4  Clear To Send Input Change Interrupt Enable */
    uint8_t  RXBRK:1;          /*!< bit:      5  Break Received Interrupt Enable    */
    uint8_t  :1;               /*!< bit:      6  Reserved                           */
    uint8_t  ERROR:1;          /*!< bit:      7  Combined Error Interrupt Enable    */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SERCOM_USART_INTENSET_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_USART_INTENSET_OFFSET 0x16         /**< \brief (SERCOM_USART_INTENSET offset) USART Interrupt Enable Set */
#define SERCOM_USART_INTENSET_RESETVALUE __U(0x00)     /**< \brief (SERCOM_USART_INTENSET reset_value) USART Interrupt Enable Set */

#define SERCOM_USART_INTENSET_DRE_Pos 0            /**< \brief (SERCOM_USART_INTENSET) Data Register Empty Interrupt Enable */
#define SERCOM_USART_INTENSET_DRE   (__U(0x1) << SERCOM_USART_INTENSET_DRE_Pos)
#define SERCOM_USART_INTENSET_TXC_Pos 1            /**< \brief (SERCOM_USART_INTENSET) Transmit Complete Interrupt Enable */
#define SERCOM_USART_INTENSET_TXC   (__U(0x1) << SERCOM_USART_INTENSET_TXC_Pos)
#define SERCOM_USART_INTENSET_RXC_Pos 2            /**< \brief (SERCOM_USART_INTENSET) Receive Complete Interrupt Enable */
#define SERCOM_USART_INTENSET_RXC   (__U(0x1) << SERCOM_USART_INTENSET_RXC_Pos)
#define SERCOM_USART_INTENSET_RXS_Pos 3            /**< \brief (SERCOM_USART_INTENSET) Receive Start Interrupt Enable */
#define SERCOM_USART_INTENSET_RXS   (__U(0x1) << SERCOM_USART_INTENSET_RXS_Pos)
#define SERCOM_USART_INTENSET_CTSIC_Pos 4            /**< \brief (SERCOM_USART_INTENSET) Clear To Send Input Change Interrupt Enable */
#define SERCOM_USART_INTENSET_CTSIC (__U(0x1) << SERCOM_USART_INTENSET_CTSIC_Pos)
#define SERCOM_USART_INTENSET_RXBRK_Pos 5            /**< \brief (SERCOM_USART_INTENSET) Break Received Interrupt Enable */
#define SERCOM_USART_INTENSET_RXBRK (__U(0x1) << SERCOM_USART_INTENSET_RXBRK_Pos)
#define SERCOM_USART_INTENSET_ERROR_Pos 7            /**< \brief (SERCOM_USART_INTENSET) Combined Error Interrupt Enable */
#define SERCOM_USART_INTENSET_ERROR (__U(0x1) << SERCOM_USART_INTENSET_ERROR_Pos)
#define SERCOM_USART_INTENSET_MASK  __U(0xBF)     /**< \brief (SERCOM_USART_INTENSET) MASK Register */

/* -------- SERCOM_I2CM_INTFLAG : (SERCOM Offset: 0x18) (R/W  8) I2CM I2CM Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t  MB:1;             /*!< bit:      0  Master On Bus Interrupt            */
    __I uint8_t  SB:1;             /*!< bit:      1  Slave On Bus Interrupt             */
    __I uint8_t  :5;               /*!< bit:  2.. 6  Reserved                           */
    __I uint8_t  ERROR:1;          /*!< bit:      7  Combined Error Interrupt           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SERCOM_I2CM_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CM_INTFLAG_OFFSET  0x18         /**< \brief (SERCOM_I2CM_INTFLAG offset) I2CM Interrupt Flag Status and Clear */
#define SERCOM_I2CM_INTFLAG_RESETVALUE __U(0x00)     /**< \brief (SERCOM_I2CM_INTFLAG reset_value) I2CM Interrupt Flag Status and Clear */

#define SERCOM_I2CM_INTFLAG_MB_Pos  0            /**< \brief (SERCOM_I2CM_INTFLAG) Master On Bus Interrupt */
#define SERCOM_I2CM_INTFLAG_MB      (__U(0x1) << SERCOM_I2CM_INTFLAG_MB_Pos)
#define SERCOM_I2CM_INTFLAG_SB_Pos  1            /**< \brief (SERCOM_I2CM_INTFLAG) Slave On Bus Interrupt */
#define SERCOM_I2CM_INTFLAG_SB      (__U(0x1) << SERCOM_I2CM_INTFLAG_SB_Pos)
#define SERCOM_I2CM_INTFLAG_ERROR_Pos 7            /**< \brief (SERCOM_I2CM_INTFLAG) Combined Error Interrupt */
#define SERCOM_I2CM_INTFLAG_ERROR   (__U(0x1) << SERCOM_I2CM_INTFLAG_ERROR_Pos)
#define SERCOM_I2CM_INTFLAG_MASK    __U(0x83)     /**< \brief (SERCOM_I2CM_INTFLAG) MASK Register */

/* -------- SERCOM_I2CS_INTFLAG : (SERCOM Offset: 0x18) (R/W  8) I2CS I2CS Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t  PREC:1;           /*!< bit:      0  Stop Received Interrupt            */
    __I uint8_t  AMATCH:1;         /*!< bit:      1  Address Match Interrupt            */
    __I uint8_t  DRDY:1;           /*!< bit:      2  Data Interrupt                     */
    __I uint8_t  :4;               /*!< bit:  3.. 6  Reserved                           */
    __I uint8_t  ERROR:1;          /*!< bit:      7  Combined Error Interrupt           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SERCOM_I2CS_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CS_INTFLAG_OFFSET  0x18         /**< \brief (SERCOM_I2CS_INTFLAG offset) I2CS Interrupt Flag Status and Clear */
#define SERCOM_I2CS_INTFLAG_RESETVALUE __U(0x00)     /**< \brief (SERCOM_I2CS_INTFLAG reset_value) I2CS Interrupt Flag Status and Clear */

#define SERCOM_I2CS_INTFLAG_PREC_Pos 0            /**< \brief (SERCOM_I2CS_INTFLAG) Stop Received Interrupt */
#define SERCOM_I2CS_INTFLAG_PREC    (__U(0x1) << SERCOM_I2CS_INTFLAG_PREC_Pos)
#define SERCOM_I2CS_INTFLAG_AMATCH_Pos 1            /**< \brief (SERCOM_I2CS_INTFLAG) Address Match Interrupt */
#define SERCOM_I2CS_INTFLAG_AMATCH  (__U(0x1) << SERCOM_I2CS_INTFLAG_AMATCH_Pos)
#define SERCOM_I2CS_INTFLAG_DRDY_Pos 2            /**< \brief (SERCOM_I2CS_INTFLAG) Data Interrupt */
#define SERCOM_I2CS_INTFLAG_DRDY    (__U(0x1) << SERCOM_I2CS_INTFLAG_DRDY_Pos)
#define SERCOM_I2CS_INTFLAG_ERROR_Pos 7            /**< \brief (SERCOM_I2CS_INTFLAG) Combined Error Interrupt */
#define SERCOM_I2CS_INTFLAG_ERROR   (__U(0x1) << SERCOM_I2CS_INTFLAG_ERROR_Pos)
#define SERCOM_I2CS_INTFLAG_MASK    __U(0x87)     /**< \brief (SERCOM_I2CS_INTFLAG) MASK Register */

/* -------- SERCOM_SPI_INTFLAG : (SERCOM Offset: 0x18) (R/W  8) SPI SPI Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t  DRE:1;            /*!< bit:      0  Data Register Empty Interrupt      */
    __I uint8_t  TXC:1;            /*!< bit:      1  Transmit Complete Interrupt        */
    __I uint8_t  RXC:1;            /*!< bit:      2  Receive Complete Interrupt         */
    __I uint8_t  SSL:1;            /*!< bit:      3  Slave Select Low Interrupt Flag    */
    __I uint8_t  :3;               /*!< bit:  4.. 6  Reserved                           */
    __I uint8_t  ERROR:1;          /*!< bit:      7  Combined Error Interrupt           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SERCOM_SPI_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_SPI_INTFLAG_OFFSET   0x18         /**< \brief (SERCOM_SPI_INTFLAG offset) SPI Interrupt Flag Status and Clear */
#define SERCOM_SPI_INTFLAG_RESETVALUE __U(0x00)     /**< \brief (SERCOM_SPI_INTFLAG reset_value) SPI Interrupt Flag Status and Clear */

#define SERCOM_SPI_INTFLAG_DRE_Pos  0            /**< \brief (SERCOM_SPI_INTFLAG) Data Register Empty Interrupt */
#define SERCOM_SPI_INTFLAG_DRE      (__U(0x1) << SERCOM_SPI_INTFLAG_DRE_Pos)
#define SERCOM_SPI_INTFLAG_TXC_Pos  1            /**< \brief (SERCOM_SPI_INTFLAG) Transmit Complete Interrupt */
#define SERCOM_SPI_INTFLAG_TXC      (__U(0x1) << SERCOM_SPI_INTFLAG_TXC_Pos)
#define SERCOM_SPI_INTFLAG_RXC_Pos  2            /**< \brief (SERCOM_SPI_INTFLAG) Receive Complete Interrupt */
#define SERCOM_SPI_INTFLAG_RXC      (__U(0x1) << SERCOM_SPI_INTFLAG_RXC_Pos)
#define SERCOM_SPI_INTFLAG_SSL_Pos  3            /**< \brief (SERCOM_SPI_INTFLAG) Slave Select Low Interrupt Flag */
#define SERCOM_SPI_INTFLAG_SSL      (__U(0x1) << SERCOM_SPI_INTFLAG_SSL_Pos)
#define SERCOM_SPI_INTFLAG_ERROR_Pos 7            /**< \brief (SERCOM_SPI_INTFLAG) Combined Error Interrupt */
#define SERCOM_SPI_INTFLAG_ERROR    (__U(0x1) << SERCOM_SPI_INTFLAG_ERROR_Pos)
#define SERCOM_SPI_INTFLAG_MASK     __U(0x8F)     /**< \brief (SERCOM_SPI_INTFLAG) MASK Register */

/* -------- SERCOM_USART_INTFLAG : (SERCOM Offset: 0x18) (R/W  8) USART USART Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t  DRE:1;            /*!< bit:      0  Data Register Empty Interrupt      */
    __I uint8_t  TXC:1;            /*!< bit:      1  Transmit Complete Interrupt        */
    __I uint8_t  RXC:1;            /*!< bit:      2  Receive Complete Interrupt         */
    __I uint8_t  RXS:1;            /*!< bit:      3  Receive Start Interrupt            */
    __I uint8_t  CTSIC:1;          /*!< bit:      4  Clear To Send Input Change Interrupt */
    __I uint8_t  RXBRK:1;          /*!< bit:      5  Break Received Interrupt           */
    __I uint8_t  :1;               /*!< bit:      6  Reserved                           */
    __I uint8_t  ERROR:1;          /*!< bit:      7  Combined Error Interrupt           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SERCOM_USART_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_USART_INTFLAG_OFFSET 0x18         /**< \brief (SERCOM_USART_INTFLAG offset) USART Interrupt Flag Status and Clear */
#define SERCOM_USART_INTFLAG_RESETVALUE __U(0x00)     /**< \brief (SERCOM_USART_INTFLAG reset_value) USART Interrupt Flag Status and Clear */

#define SERCOM_USART_INTFLAG_DRE_Pos 0            /**< \brief (SERCOM_USART_INTFLAG) Data Register Empty Interrupt */
#define SERCOM_USART_INTFLAG_DRE    (__U(0x1) << SERCOM_USART_INTFLAG_DRE_Pos)
#define SERCOM_USART_INTFLAG_TXC_Pos 1            /**< \brief (SERCOM_USART_INTFLAG) Transmit Complete Interrupt */
#define SERCOM_USART_INTFLAG_TXC    (__U(0x1) << SERCOM_USART_INTFLAG_TXC_Pos)
#define SERCOM_USART_INTFLAG_RXC_Pos 2            /**< \brief (SERCOM_USART_INTFLAG) Receive Complete Interrupt */
#define SERCOM_USART_INTFLAG_RXC    (__U(0x1) << SERCOM_USART_INTFLAG_RXC_Pos)
#define SERCOM_USART_INTFLAG_RXS_Pos 3            /**< \brief (SERCOM_USART_INTFLAG) Receive Start Interrupt */
#define SERCOM_USART_INTFLAG_RXS    (__U(0x1) << SERCOM_USART_INTFLAG_RXS_Pos)
#define SERCOM_USART_INTFLAG_CTSIC_Pos 4            /**< \brief (SERCOM_USART_INTFLAG) Clear To Send Input Change Interrupt */
#define SERCOM_USART_INTFLAG_CTSIC  (__U(0x1) << SERCOM_USART_INTFLAG_CTSIC_Pos)
#define SERCOM_USART_INTFLAG_RXBRK_Pos 5            /**< \brief (SERCOM_USART_INTFLAG) Break Received Interrupt */
#define SERCOM_USART_INTFLAG_RXBRK  (__U(0x1) << SERCOM_USART_INTFLAG_RXBRK_Pos)
#define SERCOM_USART_INTFLAG_ERROR_Pos 7            /**< \brief (SERCOM_USART_INTFLAG) Combined Error Interrupt */
#define SERCOM_USART_INTFLAG_ERROR  (__U(0x1) << SERCOM_USART_INTFLAG_ERROR_Pos)
#define SERCOM_USART_INTFLAG_MASK   __U(0xBF)     /**< \brief (SERCOM_USART_INTFLAG) MASK Register */

/* -------- SERCOM_I2CM_STATUS : (SERCOM Offset: 0x1A) (R/W 16) I2CM I2CM Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t BUSERR:1;         /*!< bit:      0  Bus Error                          */
    uint16_t ARBLOST:1;        /*!< bit:      1  Arbitration Lost                   */
    uint16_t RXNACK:1;         /*!< bit:      2  Received Not Acknowledge           */
    uint16_t :1;               /*!< bit:      3  Reserved                           */
    uint16_t BUSSTATE:2;       /*!< bit:  4.. 5  Bus State                          */
    uint16_t LOWTOUT:1;        /*!< bit:      6  SCL Low Timeout                    */
    uint16_t CLKHOLD:1;        /*!< bit:      7  Clock Hold                         */
    uint16_t MEXTTOUT:1;       /*!< bit:      8  Master SCL Low Extend Timeout      */
    uint16_t SEXTTOUT:1;       /*!< bit:      9  Slave SCL Low Extend Timeout       */
    uint16_t LENERR:1;         /*!< bit:     10  Length Error                       */
    uint16_t :5;               /*!< bit: 11..15  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} SERCOM_I2CM_STATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CM_STATUS_OFFSET   0x1A         /**< \brief (SERCOM_I2CM_STATUS offset) I2CM Status */
#define SERCOM_I2CM_STATUS_RESETVALUE __U(0x0000)   /**< \brief (SERCOM_I2CM_STATUS reset_value) I2CM Status */

#define SERCOM_I2CM_STATUS_BUSERR_Pos 0            /**< \brief (SERCOM_I2CM_STATUS) Bus Error */
#define SERCOM_I2CM_STATUS_BUSERR   (__U(0x1) << SERCOM_I2CM_STATUS_BUSERR_Pos)
#define SERCOM_I2CM_STATUS_ARBLOST_Pos 1            /**< \brief (SERCOM_I2CM_STATUS) Arbitration Lost */
#define SERCOM_I2CM_STATUS_ARBLOST  (__U(0x1) << SERCOM_I2CM_STATUS_ARBLOST_Pos)
#define SERCOM_I2CM_STATUS_RXNACK_Pos 2            /**< \brief (SERCOM_I2CM_STATUS) Received Not Acknowledge */
#define SERCOM_I2CM_STATUS_RXNACK   (__U(0x1) << SERCOM_I2CM_STATUS_RXNACK_Pos)
#define SERCOM_I2CM_STATUS_BUSSTATE_Pos 4            /**< \brief (SERCOM_I2CM_STATUS) Bus State */
#define SERCOM_I2CM_STATUS_BUSSTATE_Msk (__U(0x3) << SERCOM_I2CM_STATUS_BUSSTATE_Pos)
#define SERCOM_I2CM_STATUS_BUSSTATE(value) (SERCOM_I2CM_STATUS_BUSSTATE_Msk & ((value) << SERCOM_I2CM_STATUS_BUSSTATE_Pos))
#define SERCOM_I2CM_STATUS_LOWTOUT_Pos 6            /**< \brief (SERCOM_I2CM_STATUS) SCL Low Timeout */
#define SERCOM_I2CM_STATUS_LOWTOUT  (__U(0x1) << SERCOM_I2CM_STATUS_LOWTOUT_Pos)
#define SERCOM_I2CM_STATUS_CLKHOLD_Pos 7            /**< \brief (SERCOM_I2CM_STATUS) Clock Hold */
#define SERCOM_I2CM_STATUS_CLKHOLD  (__U(0x1) << SERCOM_I2CM_STATUS_CLKHOLD_Pos)
#define SERCOM_I2CM_STATUS_MEXTTOUT_Pos 8            /**< \brief (SERCOM_I2CM_STATUS) Master SCL Low Extend Timeout */
#define SERCOM_I2CM_STATUS_MEXTTOUT (__U(0x1) << SERCOM_I2CM_STATUS_MEXTTOUT_Pos)
#define SERCOM_I2CM_STATUS_SEXTTOUT_Pos 9            /**< \brief (SERCOM_I2CM_STATUS) Slave SCL Low Extend Timeout */
#define SERCOM_I2CM_STATUS_SEXTTOUT (__U(0x1) << SERCOM_I2CM_STATUS_SEXTTOUT_Pos)
#define SERCOM_I2CM_STATUS_LENERR_Pos 10           /**< \brief (SERCOM_I2CM_STATUS) Length Error */
#define SERCOM_I2CM_STATUS_LENERR   (__U(0x1) << SERCOM_I2CM_STATUS_LENERR_Pos)
#define SERCOM_I2CM_STATUS_MASK     __U(0x07F7)   /**< \brief (SERCOM_I2CM_STATUS) MASK Register */

/* -------- SERCOM_I2CS_STATUS : (SERCOM Offset: 0x1A) (R/W 16) I2CS I2CS Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t BUSERR:1;         /*!< bit:      0  Bus Error                          */
    uint16_t COLL:1;           /*!< bit:      1  Transmit Collision                 */
    uint16_t RXNACK:1;         /*!< bit:      2  Received Not Acknowledge           */
    uint16_t DIR:1;            /*!< bit:      3  Read/Write Direction               */
    uint16_t SR:1;             /*!< bit:      4  Repeated Start                     */
    uint16_t :1;               /*!< bit:      5  Reserved                           */
    uint16_t LOWTOUT:1;        /*!< bit:      6  SCL Low Timeout                    */
    uint16_t CLKHOLD:1;        /*!< bit:      7  Clock Hold                         */
    uint16_t :1;               /*!< bit:      8  Reserved                           */
    uint16_t SEXTTOUT:1;       /*!< bit:      9  Slave SCL Low Extend Timeout       */
    uint16_t HS:1;             /*!< bit:     10  High Speed                         */
    uint16_t :5;               /*!< bit: 11..15  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} SERCOM_I2CS_STATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CS_STATUS_OFFSET   0x1A         /**< \brief (SERCOM_I2CS_STATUS offset) I2CS Status */
#define SERCOM_I2CS_STATUS_RESETVALUE __U(0x0000)   /**< \brief (SERCOM_I2CS_STATUS reset_value) I2CS Status */

#define SERCOM_I2CS_STATUS_BUSERR_Pos 0            /**< \brief (SERCOM_I2CS_STATUS) Bus Error */
#define SERCOM_I2CS_STATUS_BUSERR   (__U(0x1) << SERCOM_I2CS_STATUS_BUSERR_Pos)
#define SERCOM_I2CS_STATUS_COLL_Pos 1            /**< \brief (SERCOM_I2CS_STATUS) Transmit Collision */
#define SERCOM_I2CS_STATUS_COLL     (__U(0x1) << SERCOM_I2CS_STATUS_COLL_Pos)
#define SERCOM_I2CS_STATUS_RXNACK_Pos 2            /**< \brief (SERCOM_I2CS_STATUS) Received Not Acknowledge */
#define SERCOM_I2CS_STATUS_RXNACK   (__U(0x1) << SERCOM_I2CS_STATUS_RXNACK_Pos)
#define SERCOM_I2CS_STATUS_DIR_Pos  3            /**< \brief (SERCOM_I2CS_STATUS) Read/Write Direction */
#define SERCOM_I2CS_STATUS_DIR      (__U(0x1) << SERCOM_I2CS_STATUS_DIR_Pos)
#define SERCOM_I2CS_STATUS_SR_Pos   4            /**< \brief (SERCOM_I2CS_STATUS) Repeated Start */
#define SERCOM_I2CS_STATUS_SR       (__U(0x1) << SERCOM_I2CS_STATUS_SR_Pos)
#define SERCOM_I2CS_STATUS_LOWTOUT_Pos 6            /**< \brief (SERCOM_I2CS_STATUS) SCL Low Timeout */
#define SERCOM_I2CS_STATUS_LOWTOUT  (__U(0x1) << SERCOM_I2CS_STATUS_LOWTOUT_Pos)
#define SERCOM_I2CS_STATUS_CLKHOLD_Pos 7            /**< \brief (SERCOM_I2CS_STATUS) Clock Hold */
#define SERCOM_I2CS_STATUS_CLKHOLD  (__U(0x1) << SERCOM_I2CS_STATUS_CLKHOLD_Pos)
#define SERCOM_I2CS_STATUS_SEXTTOUT_Pos 9            /**< \brief (SERCOM_I2CS_STATUS) Slave SCL Low Extend Timeout */
#define SERCOM_I2CS_STATUS_SEXTTOUT (__U(0x1) << SERCOM_I2CS_STATUS_SEXTTOUT_Pos)
#define SERCOM_I2CS_STATUS_HS_Pos   10           /**< \brief (SERCOM_I2CS_STATUS) High Speed */
#define SERCOM_I2CS_STATUS_HS       (__U(0x1) << SERCOM_I2CS_STATUS_HS_Pos)
#define SERCOM_I2CS_STATUS_MASK     __U(0x06DF)   /**< \brief (SERCOM_I2CS_STATUS) MASK Register */

/* -------- SERCOM_SPI_STATUS : (SERCOM Offset: 0x1A) (R/W 16) SPI SPI Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t :2;               /*!< bit:  0.. 1  Reserved                           */
    uint16_t BUFOVF:1;         /*!< bit:      2  Buffer Overflow                    */
    uint16_t :13;              /*!< bit:  3..15  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} SERCOM_SPI_STATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_SPI_STATUS_OFFSET    0x1A         /**< \brief (SERCOM_SPI_STATUS offset) SPI Status */
#define SERCOM_SPI_STATUS_RESETVALUE __U(0x0000)   /**< \brief (SERCOM_SPI_STATUS reset_value) SPI Status */

#define SERCOM_SPI_STATUS_BUFOVF_Pos 2            /**< \brief (SERCOM_SPI_STATUS) Buffer Overflow */
#define SERCOM_SPI_STATUS_BUFOVF    (__U(0x1) << SERCOM_SPI_STATUS_BUFOVF_Pos)
#define SERCOM_SPI_STATUS_MASK      __U(0x0004)   /**< \brief (SERCOM_SPI_STATUS) MASK Register */

/* -------- SERCOM_USART_STATUS : (SERCOM Offset: 0x1A) (R/W 16) USART USART Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t PERR:1;           /*!< bit:      0  Parity Error                       */
    uint16_t FERR:1;           /*!< bit:      1  Frame Error                        */
    uint16_t BUFOVF:1;         /*!< bit:      2  Buffer Overflow                    */
    uint16_t CTS:1;            /*!< bit:      3  Clear To Send                      */
    uint16_t ISF:1;            /*!< bit:      4  Inconsistent Sync Field            */
    uint16_t COLL:1;           /*!< bit:      5  Collision Detected                 */
    uint16_t :10;              /*!< bit:  6..15  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} SERCOM_USART_STATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_USART_STATUS_OFFSET  0x1A         /**< \brief (SERCOM_USART_STATUS offset) USART Status */
#define SERCOM_USART_STATUS_RESETVALUE __U(0x0000)   /**< \brief (SERCOM_USART_STATUS reset_value) USART Status */

#define SERCOM_USART_STATUS_PERR_Pos 0            /**< \brief (SERCOM_USART_STATUS) Parity Error */
#define SERCOM_USART_STATUS_PERR    (__U(0x1) << SERCOM_USART_STATUS_PERR_Pos)
#define SERCOM_USART_STATUS_FERR_Pos 1            /**< \brief (SERCOM_USART_STATUS) Frame Error */
#define SERCOM_USART_STATUS_FERR    (__U(0x1) << SERCOM_USART_STATUS_FERR_Pos)
#define SERCOM_USART_STATUS_BUFOVF_Pos 2            /**< \brief (SERCOM_USART_STATUS) Buffer Overflow */
#define SERCOM_USART_STATUS_BUFOVF  (__U(0x1) << SERCOM_USART_STATUS_BUFOVF_Pos)
#define SERCOM_USART_STATUS_CTS_Pos 3            /**< \brief (SERCOM_USART_STATUS) Clear To Send */
#define SERCOM_USART_STATUS_CTS     (__U(0x1) << SERCOM_USART_STATUS_CTS_Pos)
#define SERCOM_USART_STATUS_ISF_Pos 4            /**< \brief (SERCOM_USART_STATUS) Inconsistent Sync Field */
#define SERCOM_USART_STATUS_ISF     (__U(0x1) << SERCOM_USART_STATUS_ISF_Pos)
#define SERCOM_USART_STATUS_COLL_Pos 5            /**< \brief (SERCOM_USART_STATUS) Collision Detected */
#define SERCOM_USART_STATUS_COLL    (__U(0x1) << SERCOM_USART_STATUS_COLL_Pos)
#define SERCOM_USART_STATUS_MASK    __U(0x003F)   /**< \brief (SERCOM_USART_STATUS) MASK Register */

/* -------- SERCOM_I2CM_SYNCBUSY : (SERCOM Offset: 0x1C) (R/  32) I2CM I2CM Syncbusy -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t SWRST:1;          /*!< bit:      0  Software Reset Synchronization Busy */
    uint32_t ENABLE:1;         /*!< bit:      1  SERCOM Enable Synchronization Busy */
    uint32_t SYSOP:1;          /*!< bit:      2  System Operation Synchronization Busy */
    uint32_t :29;              /*!< bit:  3..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SERCOM_I2CM_SYNCBUSY_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CM_SYNCBUSY_OFFSET 0x1C         /**< \brief (SERCOM_I2CM_SYNCBUSY offset) I2CM Syncbusy */
#define SERCOM_I2CM_SYNCBUSY_RESETVALUE __U(0x00000000) /**< \brief (SERCOM_I2CM_SYNCBUSY reset_value) I2CM Syncbusy */

#define SERCOM_I2CM_SYNCBUSY_SWRST_Pos 0            /**< \brief (SERCOM_I2CM_SYNCBUSY) Software Reset Synchronization Busy */
#define SERCOM_I2CM_SYNCBUSY_SWRST  (__U(0x1) << SERCOM_I2CM_SYNCBUSY_SWRST_Pos)
#define SERCOM_I2CM_SYNCBUSY_ENABLE_Pos 1            /**< \brief (SERCOM_I2CM_SYNCBUSY) SERCOM Enable Synchronization Busy */
#define SERCOM_I2CM_SYNCBUSY_ENABLE (__U(0x1) << SERCOM_I2CM_SYNCBUSY_ENABLE_Pos)
#define SERCOM_I2CM_SYNCBUSY_SYSOP_Pos 2            /**< \brief (SERCOM_I2CM_SYNCBUSY) System Operation Synchronization Busy */
#define SERCOM_I2CM_SYNCBUSY_SYSOP  (__U(0x1) << SERCOM_I2CM_SYNCBUSY_SYSOP_Pos)
#define SERCOM_I2CM_SYNCBUSY_MASK   __U(0x00000007) /**< \brief (SERCOM_I2CM_SYNCBUSY) MASK Register */

/* -------- SERCOM_I2CS_SYNCBUSY : (SERCOM Offset: 0x1C) (R/  32) I2CS I2CS Syncbusy -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t SWRST:1;          /*!< bit:      0  Software Reset Synchronization Busy */
    uint32_t ENABLE:1;         /*!< bit:      1  SERCOM Enable Synchronization Busy */
    uint32_t :30;              /*!< bit:  2..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SERCOM_I2CS_SYNCBUSY_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CS_SYNCBUSY_OFFSET 0x1C         /**< \brief (SERCOM_I2CS_SYNCBUSY offset) I2CS Syncbusy */
#define SERCOM_I2CS_SYNCBUSY_RESETVALUE __U(0x00000000) /**< \brief (SERCOM_I2CS_SYNCBUSY reset_value) I2CS Syncbusy */

#define SERCOM_I2CS_SYNCBUSY_SWRST_Pos 0            /**< \brief (SERCOM_I2CS_SYNCBUSY) Software Reset Synchronization Busy */
#define SERCOM_I2CS_SYNCBUSY_SWRST  (__U(0x1) << SERCOM_I2CS_SYNCBUSY_SWRST_Pos)
#define SERCOM_I2CS_SYNCBUSY_ENABLE_Pos 1            /**< \brief (SERCOM_I2CS_SYNCBUSY) SERCOM Enable Synchronization Busy */
#define SERCOM_I2CS_SYNCBUSY_ENABLE (__U(0x1) << SERCOM_I2CS_SYNCBUSY_ENABLE_Pos)
#define SERCOM_I2CS_SYNCBUSY_MASK   __U(0x00000003) /**< \brief (SERCOM_I2CS_SYNCBUSY) MASK Register */

/* -------- SERCOM_SPI_SYNCBUSY : (SERCOM Offset: 0x1C) (R/  32) SPI SPI Syncbusy -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t SWRST:1;          /*!< bit:      0  Software Reset Synchronization Busy */
    uint32_t ENABLE:1;         /*!< bit:      1  SERCOM Enable Synchronization Busy */
    uint32_t CTRLB:1;          /*!< bit:      2  CTRLB Synchronization Busy         */
    uint32_t :29;              /*!< bit:  3..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SERCOM_SPI_SYNCBUSY_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_SPI_SYNCBUSY_OFFSET  0x1C         /**< \brief (SERCOM_SPI_SYNCBUSY offset) SPI Syncbusy */
#define SERCOM_SPI_SYNCBUSY_RESETVALUE __U(0x00000000) /**< \brief (SERCOM_SPI_SYNCBUSY reset_value) SPI Syncbusy */

#define SERCOM_SPI_SYNCBUSY_SWRST_Pos 0            /**< \brief (SERCOM_SPI_SYNCBUSY) Software Reset Synchronization Busy */
#define SERCOM_SPI_SYNCBUSY_SWRST   (__U(0x1) << SERCOM_SPI_SYNCBUSY_SWRST_Pos)
#define SERCOM_SPI_SYNCBUSY_ENABLE_Pos 1            /**< \brief (SERCOM_SPI_SYNCBUSY) SERCOM Enable Synchronization Busy */
#define SERCOM_SPI_SYNCBUSY_ENABLE  (__U(0x1) << SERCOM_SPI_SYNCBUSY_ENABLE_Pos)
#define SERCOM_SPI_SYNCBUSY_CTRLB_Pos 2            /**< \brief (SERCOM_SPI_SYNCBUSY) CTRLB Synchronization Busy */
#define SERCOM_SPI_SYNCBUSY_CTRLB   (__U(0x1) << SERCOM_SPI_SYNCBUSY_CTRLB_Pos)
#define SERCOM_SPI_SYNCBUSY_MASK    __U(0x00000007) /**< \brief (SERCOM_SPI_SYNCBUSY) MASK Register */

/* -------- SERCOM_USART_SYNCBUSY : (SERCOM Offset: 0x1C) (R/  32) USART USART Syncbusy -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t SWRST:1;          /*!< bit:      0  Software Reset Synchronization Busy */
    uint32_t ENABLE:1;         /*!< bit:      1  SERCOM Enable Synchronization Busy */
    uint32_t CTRLB:1;          /*!< bit:      2  CTRLB Synchronization Busy         */
    uint32_t :29;              /*!< bit:  3..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SERCOM_USART_SYNCBUSY_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_USART_SYNCBUSY_OFFSET 0x1C         /**< \brief (SERCOM_USART_SYNCBUSY offset) USART Syncbusy */
#define SERCOM_USART_SYNCBUSY_RESETVALUE __U(0x00000000) /**< \brief (SERCOM_USART_SYNCBUSY reset_value) USART Syncbusy */

#define SERCOM_USART_SYNCBUSY_SWRST_Pos 0            /**< \brief (SERCOM_USART_SYNCBUSY) Software Reset Synchronization Busy */
#define SERCOM_USART_SYNCBUSY_SWRST (__U(0x1) << SERCOM_USART_SYNCBUSY_SWRST_Pos)
#define SERCOM_USART_SYNCBUSY_ENABLE_Pos 1            /**< \brief (SERCOM_USART_SYNCBUSY) SERCOM Enable Synchronization Busy */
#define SERCOM_USART_SYNCBUSY_ENABLE (__U(0x1) << SERCOM_USART_SYNCBUSY_ENABLE_Pos)
#define SERCOM_USART_SYNCBUSY_CTRLB_Pos 2            /**< \brief (SERCOM_USART_SYNCBUSY) CTRLB Synchronization Busy */
#define SERCOM_USART_SYNCBUSY_CTRLB (__U(0x1) << SERCOM_USART_SYNCBUSY_CTRLB_Pos)
#define SERCOM_USART_SYNCBUSY_MASK  __U(0x00000007) /**< \brief (SERCOM_USART_SYNCBUSY) MASK Register */

/* -------- SERCOM_I2CM_ADDR : (SERCOM Offset: 0x24) (R/W 32) I2CM I2CM Address -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t ADDR:11;          /*!< bit:  0..10  Address Value                      */
    uint32_t :2;               /*!< bit: 11..12  Reserved                           */
    uint32_t LENEN:1;          /*!< bit:     13  Length Enable                      */
    uint32_t HS:1;             /*!< bit:     14  High Speed Mode                    */
    uint32_t TENBITEN:1;       /*!< bit:     15  Ten Bit Addressing Enable          */
    uint32_t LEN:8;            /*!< bit: 16..23  Length                             */
    uint32_t :8;               /*!< bit: 24..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SERCOM_I2CM_ADDR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CM_ADDR_OFFSET     0x24         /**< \brief (SERCOM_I2CM_ADDR offset) I2CM Address */
#define SERCOM_I2CM_ADDR_RESETVALUE __U(0x00000000) /**< \brief (SERCOM_I2CM_ADDR reset_value) I2CM Address */

#define SERCOM_I2CM_ADDR_ADDR_Pos   0            /**< \brief (SERCOM_I2CM_ADDR) Address Value */
#define SERCOM_I2CM_ADDR_ADDR_Msk   (__U(0x7FF) << SERCOM_I2CM_ADDR_ADDR_Pos)
#define SERCOM_I2CM_ADDR_ADDR(value) (SERCOM_I2CM_ADDR_ADDR_Msk & ((value) << SERCOM_I2CM_ADDR_ADDR_Pos))
#define SERCOM_I2CM_ADDR_LENEN_Pos  13           /**< \brief (SERCOM_I2CM_ADDR) Length Enable */
#define SERCOM_I2CM_ADDR_LENEN      (__U(0x1) << SERCOM_I2CM_ADDR_LENEN_Pos)
#define SERCOM_I2CM_ADDR_HS_Pos     14           /**< \brief (SERCOM_I2CM_ADDR) High Speed Mode */
#define SERCOM_I2CM_ADDR_HS         (__U(0x1) << SERCOM_I2CM_ADDR_HS_Pos)
#define SERCOM_I2CM_ADDR_TENBITEN_Pos 15           /**< \brief (SERCOM_I2CM_ADDR) Ten Bit Addressing Enable */
#define SERCOM_I2CM_ADDR_TENBITEN   (__U(0x1) << SERCOM_I2CM_ADDR_TENBITEN_Pos)
#define SERCOM_I2CM_ADDR_LEN_Pos    16           /**< \brief (SERCOM_I2CM_ADDR) Length */
#define SERCOM_I2CM_ADDR_LEN_Msk    (__U(0xFF) << SERCOM_I2CM_ADDR_LEN_Pos)
#define SERCOM_I2CM_ADDR_LEN(value) (SERCOM_I2CM_ADDR_LEN_Msk & ((value) << SERCOM_I2CM_ADDR_LEN_Pos))
#define SERCOM_I2CM_ADDR_MASK       __U(0x00FFE7FF) /**< \brief (SERCOM_I2CM_ADDR) MASK Register */

/* -------- SERCOM_I2CS_ADDR : (SERCOM Offset: 0x24) (R/W 32) I2CS I2CS Address -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t GENCEN:1;         /*!< bit:      0  General Call Address Enable        */
    uint32_t ADDR:10;          /*!< bit:  1..10  Address Value                      */
    uint32_t :4;               /*!< bit: 11..14  Reserved                           */
    uint32_t TENBITEN:1;       /*!< bit:     15  Ten Bit Addressing Enable          */
    uint32_t :1;               /*!< bit:     16  Reserved                           */
    uint32_t ADDRMASK:10;      /*!< bit: 17..26  Address Mask                       */
    uint32_t :5;               /*!< bit: 27..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SERCOM_I2CS_ADDR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CS_ADDR_OFFSET     0x24         /**< \brief (SERCOM_I2CS_ADDR offset) I2CS Address */
#define SERCOM_I2CS_ADDR_RESETVALUE __U(0x00000000) /**< \brief (SERCOM_I2CS_ADDR reset_value) I2CS Address */

#define SERCOM_I2CS_ADDR_GENCEN_Pos 0            /**< \brief (SERCOM_I2CS_ADDR) General Call Address Enable */
#define SERCOM_I2CS_ADDR_GENCEN     (__U(0x1) << SERCOM_I2CS_ADDR_GENCEN_Pos)
#define SERCOM_I2CS_ADDR_ADDR_Pos   1            /**< \brief (SERCOM_I2CS_ADDR) Address Value */
#define SERCOM_I2CS_ADDR_ADDR_Msk   (__U(0x3FF) << SERCOM_I2CS_ADDR_ADDR_Pos)
#define SERCOM_I2CS_ADDR_ADDR(value) (SERCOM_I2CS_ADDR_ADDR_Msk & ((value) << SERCOM_I2CS_ADDR_ADDR_Pos))
#define SERCOM_I2CS_ADDR_TENBITEN_Pos 15           /**< \brief (SERCOM_I2CS_ADDR) Ten Bit Addressing Enable */
#define SERCOM_I2CS_ADDR_TENBITEN   (__U(0x1) << SERCOM_I2CS_ADDR_TENBITEN_Pos)
#define SERCOM_I2CS_ADDR_ADDRMASK_Pos 17           /**< \brief (SERCOM_I2CS_ADDR) Address Mask */
#define SERCOM_I2CS_ADDR_ADDRMASK_Msk (__U(0x3FF) << SERCOM_I2CS_ADDR_ADDRMASK_Pos)
#define SERCOM_I2CS_ADDR_ADDRMASK(value) (SERCOM_I2CS_ADDR_ADDRMASK_Msk & ((value) << SERCOM_I2CS_ADDR_ADDRMASK_Pos))
#define SERCOM_I2CS_ADDR_MASK       __U(0x07FE87FF) /**< \brief (SERCOM_I2CS_ADDR) MASK Register */

/* -------- SERCOM_SPI_ADDR : (SERCOM Offset: 0x24) (R/W 32) SPI SPI Address -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t ADDR:8;           /*!< bit:  0.. 7  Address Value                      */
    uint32_t :8;               /*!< bit:  8..15  Reserved                           */
    uint32_t ADDRMASK:8;       /*!< bit: 16..23  Address Mask                       */
    uint32_t :8;               /*!< bit: 24..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SERCOM_SPI_ADDR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_SPI_ADDR_OFFSET      0x24         /**< \brief (SERCOM_SPI_ADDR offset) SPI Address */
#define SERCOM_SPI_ADDR_RESETVALUE  __U(0x00000000) /**< \brief (SERCOM_SPI_ADDR reset_value) SPI Address */

#define SERCOM_SPI_ADDR_ADDR_Pos    0            /**< \brief (SERCOM_SPI_ADDR) Address Value */
#define SERCOM_SPI_ADDR_ADDR_Msk    (__U(0xFF) << SERCOM_SPI_ADDR_ADDR_Pos)
#define SERCOM_SPI_ADDR_ADDR(value) (SERCOM_SPI_ADDR_ADDR_Msk & ((value) << SERCOM_SPI_ADDR_ADDR_Pos))
#define SERCOM_SPI_ADDR_ADDRMASK_Pos 16           /**< \brief (SERCOM_SPI_ADDR) Address Mask */
#define SERCOM_SPI_ADDR_ADDRMASK_Msk (__U(0xFF) << SERCOM_SPI_ADDR_ADDRMASK_Pos)
#define SERCOM_SPI_ADDR_ADDRMASK(value) (SERCOM_SPI_ADDR_ADDRMASK_Msk & ((value) << SERCOM_SPI_ADDR_ADDRMASK_Pos))
#define SERCOM_SPI_ADDR_MASK        __U(0x00FF00FF) /**< \brief (SERCOM_SPI_ADDR) MASK Register */

/* -------- SERCOM_I2CM_DATA : (SERCOM Offset: 0x28) (R/W  8) I2CM I2CM Data -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  DATA:8;           /*!< bit:  0.. 7  Data Value                         */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SERCOM_I2CM_DATA_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CM_DATA_OFFSET     0x28         /**< \brief (SERCOM_I2CM_DATA offset) I2CM Data */
#define SERCOM_I2CM_DATA_RESETVALUE __U(0x00)     /**< \brief (SERCOM_I2CM_DATA reset_value) I2CM Data */

#define SERCOM_I2CM_DATA_DATA_Pos   0            /**< \brief (SERCOM_I2CM_DATA) Data Value */
#define SERCOM_I2CM_DATA_DATA_Msk   (__U(0xFF) << SERCOM_I2CM_DATA_DATA_Pos)
#define SERCOM_I2CM_DATA_DATA(value) (SERCOM_I2CM_DATA_DATA_Msk & ((value) << SERCOM_I2CM_DATA_DATA_Pos))
#define SERCOM_I2CM_DATA_MASK       __U(0xFF)     /**< \brief (SERCOM_I2CM_DATA) MASK Register */

/* -------- SERCOM_I2CS_DATA : (SERCOM Offset: 0x28) (R/W  8) I2CS I2CS Data -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  DATA:8;           /*!< bit:  0.. 7  Data Value                         */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SERCOM_I2CS_DATA_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CS_DATA_OFFSET     0x28         /**< \brief (SERCOM_I2CS_DATA offset) I2CS Data */
#define SERCOM_I2CS_DATA_RESETVALUE __U(0x00)     /**< \brief (SERCOM_I2CS_DATA reset_value) I2CS Data */

#define SERCOM_I2CS_DATA_DATA_Pos   0            /**< \brief (SERCOM_I2CS_DATA) Data Value */
#define SERCOM_I2CS_DATA_DATA_Msk   (__U(0xFF) << SERCOM_I2CS_DATA_DATA_Pos)
#define SERCOM_I2CS_DATA_DATA(value) (SERCOM_I2CS_DATA_DATA_Msk & ((value) << SERCOM_I2CS_DATA_DATA_Pos))
#define SERCOM_I2CS_DATA_MASK       __U(0xFF)     /**< \brief (SERCOM_I2CS_DATA) MASK Register */

/* -------- SERCOM_SPI_DATA : (SERCOM Offset: 0x28) (R/W 32) SPI SPI Data -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t DATA:9;           /*!< bit:  0.. 8  Data Value                         */
    uint32_t :23;              /*!< bit:  9..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SERCOM_SPI_DATA_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_SPI_DATA_OFFSET      0x28         /**< \brief (SERCOM_SPI_DATA offset) SPI Data */
#define SERCOM_SPI_DATA_RESETVALUE  __U(0x00000000) /**< \brief (SERCOM_SPI_DATA reset_value) SPI Data */

#define SERCOM_SPI_DATA_DATA_Pos    0            /**< \brief (SERCOM_SPI_DATA) Data Value */
#define SERCOM_SPI_DATA_DATA_Msk    (__U(0x1FF) << SERCOM_SPI_DATA_DATA_Pos)
#define SERCOM_SPI_DATA_DATA(value) (SERCOM_SPI_DATA_DATA_Msk & ((value) << SERCOM_SPI_DATA_DATA_Pos))
#define SERCOM_SPI_DATA_MASK        __U(0x000001FF) /**< \brief (SERCOM_SPI_DATA) MASK Register */

/* -------- SERCOM_USART_DATA : (SERCOM Offset: 0x28) (R/W 16) USART USART Data -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t DATA:9;           /*!< bit:  0.. 8  Data Value                         */
    uint16_t :7;               /*!< bit:  9..15  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} SERCOM_USART_DATA_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_USART_DATA_OFFSET    0x28         /**< \brief (SERCOM_USART_DATA offset) USART Data */
#define SERCOM_USART_DATA_RESETVALUE __U(0x0000)   /**< \brief (SERCOM_USART_DATA reset_value) USART Data */

#define SERCOM_USART_DATA_DATA_Pos  0            /**< \brief (SERCOM_USART_DATA) Data Value */
#define SERCOM_USART_DATA_DATA_Msk  (__U(0x1FF) << SERCOM_USART_DATA_DATA_Pos)
#define SERCOM_USART_DATA_DATA(value) (SERCOM_USART_DATA_DATA_Msk & ((value) << SERCOM_USART_DATA_DATA_Pos))
#define SERCOM_USART_DATA_MASK      __U(0x01FF)   /**< \brief (SERCOM_USART_DATA) MASK Register */

/* -------- SERCOM_I2CM_DBGCTRL : (SERCOM Offset: 0x30) (R/W  8) I2CM I2CM Debug Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  DBGSTOP:1;        /*!< bit:      0  Debug Mode                         */
    uint8_t  :7;               /*!< bit:  1.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SERCOM_I2CM_DBGCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_I2CM_DBGCTRL_OFFSET  0x30         /**< \brief (SERCOM_I2CM_DBGCTRL offset) I2CM Debug Control */
#define SERCOM_I2CM_DBGCTRL_RESETVALUE __U(0x00)     /**< \brief (SERCOM_I2CM_DBGCTRL reset_value) I2CM Debug Control */

#define SERCOM_I2CM_DBGCTRL_DBGSTOP_Pos 0            /**< \brief (SERCOM_I2CM_DBGCTRL) Debug Mode */
#define SERCOM_I2CM_DBGCTRL_DBGSTOP (__U(0x1) << SERCOM_I2CM_DBGCTRL_DBGSTOP_Pos)
#define SERCOM_I2CM_DBGCTRL_MASK    __U(0x01)     /**< \brief (SERCOM_I2CM_DBGCTRL) MASK Register */

/* -------- SERCOM_SPI_DBGCTRL : (SERCOM Offset: 0x30) (R/W  8) SPI SPI Debug Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  DBGSTOP:1;        /*!< bit:      0  Debug Mode                         */
    uint8_t  :7;               /*!< bit:  1.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SERCOM_SPI_DBGCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_SPI_DBGCTRL_OFFSET   0x30         /**< \brief (SERCOM_SPI_DBGCTRL offset) SPI Debug Control */
#define SERCOM_SPI_DBGCTRL_RESETVALUE __U(0x00)     /**< \brief (SERCOM_SPI_DBGCTRL reset_value) SPI Debug Control */

#define SERCOM_SPI_DBGCTRL_DBGSTOP_Pos 0            /**< \brief (SERCOM_SPI_DBGCTRL) Debug Mode */
#define SERCOM_SPI_DBGCTRL_DBGSTOP  (__U(0x1) << SERCOM_SPI_DBGCTRL_DBGSTOP_Pos)
#define SERCOM_SPI_DBGCTRL_MASK     __U(0x01)     /**< \brief (SERCOM_SPI_DBGCTRL) MASK Register */

/* -------- SERCOM_USART_DBGCTRL : (SERCOM Offset: 0x30) (R/W  8) USART USART Debug Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  DBGSTOP:1;        /*!< bit:      0  Debug Mode                         */
    uint8_t  :7;               /*!< bit:  1.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} SERCOM_USART_DBGCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SERCOM_USART_DBGCTRL_OFFSET 0x30         /**< \brief (SERCOM_USART_DBGCTRL offset) USART Debug Control */
#define SERCOM_USART_DBGCTRL_RESETVALUE __U(0x00)     /**< \brief (SERCOM_USART_DBGCTRL reset_value) USART Debug Control */

#define SERCOM_USART_DBGCTRL_DBGSTOP_Pos 0            /**< \brief (SERCOM_USART_DBGCTRL) Debug Mode */
#define SERCOM_USART_DBGCTRL_DBGSTOP (__U(0x1) << SERCOM_USART_DBGCTRL_DBGSTOP_Pos)
#define SERCOM_USART_DBGCTRL_MASK   __U(0x01)     /**< \brief (SERCOM_USART_DBGCTRL) MASK Register */

/** \brief SERCOM_I2CM hardware registers */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct { /* I2C Master Mode */
  __IO SERCOM_I2CM_CTRLA_Type    CTRLA;       /**< \brief Offset: 0x00 (R/W 32) I2CM Control A */
  __IO SERCOM_I2CM_CTRLB_Type    CTRLB;       /**< \brief Offset: 0x04 (R/W 32) I2CM Control B */
       RoReg8                    Reserved1[0x4];
  __IO SERCOM_I2CM_BAUD_Type     BAUD;        /**< \brief Offset: 0x0C (R/W 32) I2CM Baud Rate */
       RoReg8                    Reserved2[0x4];
  __IO SERCOM_I2CM_INTENCLR_Type INTENCLR;    /**< \brief Offset: 0x14 (R/W  8) I2CM Interrupt Enable Clear */
       RoReg8                    Reserved3[0x1];
  __IO SERCOM_I2CM_INTENSET_Type INTENSET;    /**< \brief Offset: 0x16 (R/W  8) I2CM Interrupt Enable Set */
       RoReg8                    Reserved4[0x1];
  __IO SERCOM_I2CM_INTFLAG_Type  INTFLAG;     /**< \brief Offset: 0x18 (R/W  8) I2CM Interrupt Flag Status and Clear */
       RoReg8                    Reserved5[0x1];
  __IO SERCOM_I2CM_STATUS_Type   STATUS;      /**< \brief Offset: 0x1A (R/W 16) I2CM Status */
  __I  SERCOM_I2CM_SYNCBUSY_Type SYNCBUSY;    /**< \brief Offset: 0x1C (R/  32) I2CM Syncbusy */
       RoReg8                    Reserved6[0x4];
  __IO SERCOM_I2CM_ADDR_Type     ADDR;        /**< \brief Offset: 0x24 (R/W 32) I2CM Address */
  __IO SERCOM_I2CM_DATA_Type     DATA;        /**< \brief Offset: 0x28 (R/W  8) I2CM Data */
       RoReg8                    Reserved7[0x7];
  __IO SERCOM_I2CM_DBGCTRL_Type  DBGCTRL;     /**< \brief Offset: 0x30 (R/W  8) I2CM Debug Control */
} SercomI2cm;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/** \brief SERCOM_I2CS hardware registers */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct { /* I2C Slave Mode */
  __IO SERCOM_I2CS_CTRLA_Type    CTRLA;       /**< \brief Offset: 0x00 (R/W 32) I2CS Control A */
  __IO SERCOM_I2CS_CTRLB_Type    CTRLB;       /**< \brief Offset: 0x04 (R/W 32) I2CS Control B */
       RoReg8                    Reserved1[0xC];
  __IO SERCOM_I2CS_INTENCLR_Type INTENCLR;    /**< \brief Offset: 0x14 (R/W  8) I2CS Interrupt Enable Clear */
       RoReg8                    Reserved2[0x1];
  __IO SERCOM_I2CS_INTENSET_Type INTENSET;    /**< \brief Offset: 0x16 (R/W  8) I2CS Interrupt Enable Set */
       RoReg8                    Reserved3[0x1];
  __IO SERCOM_I2CS_INTFLAG_Type  INTFLAG;     /**< \brief Offset: 0x18 (R/W  8) I2CS Interrupt Flag Status and Clear */
       RoReg8                    Reserved4[0x1];
  __IO SERCOM_I2CS_STATUS_Type   STATUS;      /**< \brief Offset: 0x1A (R/W 16) I2CS Status */
  __I  SERCOM_I2CS_SYNCBUSY_Type SYNCBUSY;    /**< \brief Offset: 0x1C (R/  32) I2CS Syncbusy */
       RoReg8                    Reserved5[0x4];
  __IO SERCOM_I2CS_ADDR_Type     ADDR;        /**< \brief Offset: 0x24 (R/W 32) I2CS Address */
  __IO SERCOM_I2CS_DATA_Type     DATA;        /**< \brief Offset: 0x28 (R/W  8) I2CS Data */
} SercomI2cs;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/** \brief SERCOM_SPI hardware registers */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct { /* SPI Mode */
  __IO SERCOM_SPI_CTRLA_Type     CTRLA;       /**< \brief Offset: 0x00 (R/W 32) SPI Control A */
  __IO SERCOM_SPI_CTRLB_Type     CTRLB;       /**< \brief Offset: 0x04 (R/W 32) SPI Control B */
       RoReg8                    Reserved1[0x4];
  __IO SERCOM_SPI_BAUD_Type      BAUD;        /**< \brief Offset: 0x0C (R/W  8) SPI Baud Rate */
       RoReg8                    Reserved2[0x7];
  __IO SERCOM_SPI_INTENCLR_Type  INTENCLR;    /**< \brief Offset: 0x14 (R/W  8) SPI Interrupt Enable Clear */
       RoReg8                    Reserved3[0x1];
  __IO SERCOM_SPI_INTENSET_Type  INTENSET;    /**< \brief Offset: 0x16 (R/W  8) SPI Interrupt Enable Set */
       RoReg8                    Reserved4[0x1];
  __IO SERCOM_SPI_INTFLAG_Type   INTFLAG;     /**< \brief Offset: 0x18 (R/W  8) SPI Interrupt Flag Status and Clear */
       RoReg8                    Reserved5[0x1];
  __IO SERCOM_SPI_STATUS_Type    STATUS;      /**< \brief Offset: 0x1A (R/W 16) SPI Status */
  __I  SERCOM_SPI_SYNCBUSY_Type  SYNCBUSY;    /**< \brief Offset: 0x1C (R/  32) SPI Syncbusy */
       RoReg8                    Reserved6[0x4];
  __IO SERCOM_SPI_ADDR_Type      ADDR;        /**< \brief Offset: 0x24 (R/W 32) SPI Address */
  __IO SERCOM_SPI_DATA_Type      DATA;        /**< \brief Offset: 0x28 (R/W 32) SPI Data */
       RoReg8                    Reserved7[0x4];
  __IO SERCOM_SPI_DBGCTRL_Type   DBGCTRL;     /**< \brief Offset: 0x30 (R/W  8) SPI Debug Control */
} SercomSpi;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/** \brief SERCOM_USART hardware registers */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct { /* USART Mode */
  __IO SERCOM_USART_CTRLA_Type   CTRLA;       /**< \brief Offset: 0x00 (R/W 32) USART Control A */
  __IO SERCOM_USART_CTRLB_Type   CTRLB;       /**< \brief Offset: 0x04 (R/W 32) USART Control B */
       RoReg8                    Reserved1[0x4];
  __IO SERCOM_USART_BAUD_Type    BAUD;        /**< \brief Offset: 0x0C (R/W 16) USART Baud Rate */
  __IO SERCOM_USART_RXPL_Type    RXPL;        /**< \brief Offset: 0x0E (R/W  8) USART Receive Pulse Length */
       RoReg8                    Reserved2[0x5];
  __IO SERCOM_USART_INTENCLR_Type INTENCLR;    /**< \brief Offset: 0x14 (R/W  8) USART Interrupt Enable Clear */
       RoReg8                    Reserved3[0x1];
  __IO SERCOM_USART_INTENSET_Type INTENSET;    /**< \brief Offset: 0x16 (R/W  8) USART Interrupt Enable Set */
       RoReg8                    Reserved4[0x1];
  __IO SERCOM_USART_INTFLAG_Type INTFLAG;     /**< \brief Offset: 0x18 (R/W  8) USART Interrupt Flag Status and Clear */
       RoReg8                    Reserved5[0x1];
  __IO SERCOM_USART_STATUS_Type  STATUS;      /**< \brief Offset: 0x1A (R/W 16) USART Status */
  __I  SERCOM_USART_SYNCBUSY_Type SYNCBUSY;    /**< \brief Offset: 0x1C (R/  32) USART Syncbusy */
       RoReg8                    Reserved6[0x8];
  __IO SERCOM_USART_DATA_Type    DATA;        /**< \brief Offset: 0x28 (R/W 16) USART Data */
       RoReg8                    Reserved7[0x6];
  __IO SERCOM_USART_DBGCTRL_Type DBGCTRL;     /**< \brief Offset: 0x30 (R/W  8) USART Debug Control */
} SercomUsart;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
       SercomI2cm                I2CM;        /**< \brief Offset: 0x00 I2C Master Mode */
       SercomI2cs                I2CS;        /**< \brief Offset: 0x00 I2C Slave Mode */
       SercomSpi                 SPI;         /**< \brief Offset: 0x00 SPI Mode */
       SercomUsart               USART;       /**< \brief Offset: 0x00 USART Mode */
} Sercom;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/*@}*/

#endif /* _SAMD21_SERCOM_COMPONENT_ */
