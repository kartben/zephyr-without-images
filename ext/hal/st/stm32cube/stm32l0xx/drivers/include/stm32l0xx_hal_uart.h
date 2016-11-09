/**
  ******************************************************************************
  * @file    stm32l0xx_hal_uart.h
  * @author  MCD Application Team
  * @version V1.7.0
  * @date    31-May-2016
  * @brief   Header file of UART HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************  
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L0xx_HAL_UART_H
#define __STM32L0xx_HAL_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup UART UART
  * @{
  */ 

/******************************************************************************/
/* Exported types ------------------------------------------------------------*/
/******************************************************************************/

   /** @defgroup UART_Exported_Types UART Exported Types
  * @{
  */

/** @defgroup UART_Init_Configuration UART initialization configuration structure
  * @{
  */
/** 
  * @brief UART Init Structure definition  
  */ 
typedef struct
{
  uint32_t BaudRate;                  /*!< This member configures the UART communication baud rate.
                                           The baud rate register is computed using the following formula:
                                           - If oversampling is 16 or in LIN mode,
                                              Baud Rate Register = ((PCLKx) / ((huart->Init.BaudRate)))
                                           - If oversampling is 8,
                                              Baud Rate Register[15:4] = ((2 * PCLKx) / ((huart->Init.BaudRate)))[15:4]  
                                              Baud Rate Register[3] =  0
                                              Baud Rate Register[2:0] =  (((2 * PCLKx) / ((huart->Init.BaudRate)))[3:0]) >> 1      */

  uint32_t WordLength;                /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref UARTEx_Word_Length */

  uint32_t StopBits;                  /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref UART_Stop_Bits */

  uint32_t Parity;                    /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref UART_Parity
                                           @note When parity is enabled, the computed parity is inserted
                                                 at the MSB position of the transmitted data (9th bit when
                                                 the word length is set to 9 data bits; 8th bit when the
                                                 word length is set to 8 data bits). */
 
  uint32_t Mode;                      /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref UART_Mode */

  uint32_t HwFlowCtl;                 /*!< Specifies wether the hardware flow control mode is enabled
                                           or disabled.
                                           This parameter can be a value of @ref UART_Hardware_Flow_Control */
  
  uint32_t OverSampling;              /*!< Specifies wether the Over sampling 8 is enabled or disabled, to achieve higher speed (up to fPCLK/8).
                                           This parameter can be a value of @ref UART_Over_Sampling */  
                                           
  uint32_t OneBitSampling;            /*!< Specifies wether a single sample or three samples' majority vote is selected.
                                           Selecting the single sample method increases the receiver tolerance to clock
                                           deviations. This parameter can be a value of @ref UART_One_Bit */
}UART_InitTypeDef;
/**
  * @}
  */
/** @defgroup UART_Advanced_Feature UART advanced feature structure
  * @{
  */
/** 
  * @brief  UART Advanced Features initalization structure definition  
  */
typedef struct                                      
{
  uint32_t AdvFeatureInit;        /*!< Specifies which advanced UART features is initialized. Several
                                       Advanced Features may be initialized at the same time .
                                       This parameter can be a value of @ref UART_Advanced_Features_Initialization_Type */
  
  uint32_t TxPinLevelInvert;      /*!< Specifies whether the TX pin active level is inverted.
                                       This parameter can be a value of @ref UART_Tx_Inv  */
                                           
  uint32_t RxPinLevelInvert;      /*!< Specifies whether the RX pin active level is inverted.
                                       This parameter can be a value of @ref UART_Rx_Inv  */

  uint32_t DataInvert;            /*!< Specifies whether data are inverted (positive/direct logic
                                       vs negative/inverted logic).
                                       This parameter can be a value of @ref UART_Data_Inv */
                                       
  uint32_t Swap;                  /*!< Specifies whether TX and RX pins are swapped.   
                                       This parameter can be a value of @ref UART_Rx_Tx_Swap */
                                       
  uint32_t OverrunDisable;        /*!< Specifies whether the reception overrun detection is disabled.   
                                       This parameter can be a value of @ref UART_Overrun_Disable */
                                       
  uint32_t DMADisableonRxError;   /*!< Specifies whether the DMA is disabled in case of reception error.     
                                       This parameter can be a value of @ref UART_DMA_Disable_on_Rx_Error */
                                       
  uint32_t AutoBaudRateEnable;    /*!< Specifies whether auto Baud rate detection is enabled.     
                                       This parameter can be a value of @ref UART_AutoBaudRate_Enable */  
                                       
  uint32_t AutoBaudRateMode;      /*!< If auto Baud rate detection is enabled, specifies how the rate 
                                       detection is carried out.     
                                       This parameter can be a value of @ref UARTEx_AutoBaud_Rate_Mode */ 
                                    
  uint32_t MSBFirst;              /*!< Specifies whether MSB is sent first on UART line.      
                                       This parameter can be a value of @ref UART_MSB_First */
} UART_AdvFeatureInitTypeDef;
/**
  * @}
  */

/** @defgroup UART_State_Definition  UART state definition
  * @{
  */

/** 
  * @brief HAL UART State structures definition  
  * @note  HAL UART State value is a combination of 2 different substates: gState and RxState.
  *        - gState contains UART state information related to global Handle management
  *          and also information related to Tx operations.
  *          gState value coding follow below described bitmap :
  *          b7-b6  Error information
  *             00 : No Error
  *             01 : (Not Used)
  *             10 : Timeout
  *             11 : Error
  *          b5     IP initilisation status
  *             0  : Reset (IP not initialized)
  *             1  : Init done (IP not initialized. HAL UART Init function already called)
  *          b4-b3  (not used)
  *             xx : Should be set to 00
  *          b2     Intrinsic process state
  *             0  : Ready
  *             1  : Busy (IP busy with some configuration or internal operations)
  *          b1     (not used)
  *             x  : Should be set to 0
  *          b0     Tx state
  *             0  : Ready (no Tx operation ongoing)
  *             1  : Busy (Tx operation ongoing)
  *        - RxState contains information related to Rx operations.
  *          RxState value coding follow below described bitmap :
  *          b7-b6  (not used)
  *             xx : Should be set to 00
  *          b5     IP initilisation status
  *             0  : Reset (IP not initialized)
  *             1  : Init done (IP not initialized)
  *          b4-b2  (not used)
  *            xxx : Should be set to 000
  *          b1     Rx state
  *             0  : Ready (no Rx operation ongoing)
  *             1  : Busy (Rx operation ongoing)
  *          b0     (not used)
  *             x  : Should be set to 0.
  */ 
typedef enum
{
  HAL_UART_STATE_RESET             = 0x00U,    /*!< Peripheral is not yet Initialized
                                                   Value is allowed for gState and RxState */
  HAL_UART_STATE_READY             = 0x20U,    /*!< Peripheral Initialized and ready for use
                                                   Value is allowed for gState and RxState */
  HAL_UART_STATE_BUSY              = 0x24U,    /*!< an internal process is ongoing
                                                   Value is allowed for gState only */
  HAL_UART_STATE_BUSY_TX           = 0x21U,    /*!< Data Transmission process is ongoing
                                                   Value is allowed for gState only */
  HAL_UART_STATE_BUSY_RX           = 0x22U,    /*!< Data Reception process is ongoing
                                                   Value is allowed for RxState only */
  HAL_UART_STATE_BUSY_TX_RX        = 0x23U,    /*!< Data Transmission and Reception process is ongoing
                                                   Not to be used for neither gState nor RxState.
                                                   Value is result of combination (Or) between gState and RxState values */
  HAL_UART_STATE_TIMEOUT           = 0xA0U,    /*!< Timeout state
                                                   Value is allowed for gState only */
  HAL_UART_STATE_ERROR             = 0xE0U     /*!< Error
                                                   Value is allowed for gState only */
}HAL_UART_StateTypeDef;

/**
  * @}
  */
/** @defgroup UART_Error_Definition  UART error definition
  * @{
  */
/** 
  * @brief  HAL UART Error Code definition
  */ 

#define   HAL_UART_ERROR_NONE      ((uint32_t)0x00U)    /*!< No error            */
#define   HAL_UART_ERROR_PE        ((uint32_t)0x01U)    /*!< Parity error        */
#define   HAL_UART_ERROR_NE        ((uint32_t)0x02U)    /*!< Noise error         */
#define   HAL_UART_ERROR_FE        ((uint32_t)0x04U)    /*!< frame error         */
#define   HAL_UART_ERROR_ORE       ((uint32_t)0x08U)    /*!< Overrun error       */
#define   HAL_UART_ERROR_DMA       ((uint32_t)0x10U)    /*!< DMA transfer error  */

/**
  * @}
  */
/** @defgroup UART_Clock_SourceDefinition  UART clock source definition
  * @{
  */
/**
  * @brief UART clock sources definition
  */
typedef enum
{
  UART_CLOCKSOURCE_PCLK1      = 0x00U,    /*!< PCLK1 clock source  */
  UART_CLOCKSOURCE_PCLK2      = 0x01U,    /*!< PCLK2 clock source  */
  UART_CLOCKSOURCE_HSI        = 0x02U,    /*!< HSI clock source    */
  UART_CLOCKSOURCE_SYSCLK     = 0x04U,    /*!< SYSCLK clock source */
  UART_CLOCKSOURCE_LSE        = 0x08U     /*!< LSE clock source     */
}UART_ClockSourceTypeDef;
/**
  * @}
  */
/** @defgroup UART_handle_Definition  Handle structure definition
  * @{
  */

/** 
  * @brief  UART handle Structure definition  
  */
typedef struct
{
  USART_TypeDef                 *Instance;        /*!< UART registers base address        */

  UART_InitTypeDef              Init;             /*!< UART communication parameters      */

  UART_AdvFeatureInitTypeDef    AdvancedInit;        /*!< UART Advanced Features initialization parameters */

  uint8_t                       *pTxBuffPtr;      /*!< Pointer to UART Tx transfer Buffer */

  uint16_t                      TxXferSize;       /*!< UART Tx Transfer size              */

  uint16_t                      TxXferCount;      /*!< UART Tx Transfer Counter           */

  uint8_t                       *pRxBuffPtr;      /*!< Pointer to UART Rx transfer Buffer */

  uint16_t                      RxXferSize;       /*!< UART Rx Transfer size              */

  uint16_t                      RxXferCount;      /*!< UART Rx Transfer Counter           */

  uint16_t                      Mask;             /*!< UART Rx RDR register mask          */

  DMA_HandleTypeDef             *hdmatx;          /*!< UART Tx DMA Handle parameters      */

  DMA_HandleTypeDef             *hdmarx;          /*!< UART Rx DMA Handle parameters      */

  HAL_LockTypeDef               Lock;             /*!< Locking object                     */

  __IO HAL_UART_StateTypeDef    gState;           /*!< UART state information related to global Handle management
                                                       and also related to Tx operations.
                                                       This parameter can be a value of @ref HAL_UART_StateTypeDef */

  __IO HAL_UART_StateTypeDef    RxState;          /*!< UART state information related to Rx operations.
                                                       This parameter can be a value of @ref HAL_UART_StateTypeDef */

  __IO uint32_t                 ErrorCode;        /*!< UART Error code                    */

}UART_HandleTypeDef;

/**
  * @}
  */
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup UART_Exported_Constants UART Exported Constants
  * @{
  */

/** @defgroup UART_Stop_Bits UART stop bit definition
  * @{
  */
#define UART_STOPBITS_1                     ((uint32_t)0x0000U)                      /*!< USART frame with 1 stop bit    */
#define UART_STOPBITS_1_5                   (USART_CR2_STOP_0 | USART_CR2_STOP_1)   /*!< USART frame with 1.5 stop bits */
#define UART_STOPBITS_2                     ((uint32_t)USART_CR2_STOP_1)            /*!< USART frame with 2 stop bits   */
#define IS_UART_STOPBITS(STOPBITS) (((STOPBITS) == UART_STOPBITS_1)   ||  \
                                    ((STOPBITS) == UART_STOPBITS_1_5) || \
                                    ((STOPBITS) == UART_STOPBITS_2))

#define IS_LPUART_STOPBITS(__STOPBITS__) (((__STOPBITS__) == UART_STOPBITS_1) || \
                                          ((__STOPBITS__) == UART_STOPBITS_2))

/**
  * @}
  */ 

/** @defgroup UART_Parity UART parity definition
  * @{
  */ 
#define UART_PARITY_NONE                    ((uint32_t)0x0000U)
#define UART_PARITY_EVEN                    ((uint32_t)USART_CR1_PCE)
#define UART_PARITY_ODD                     ((uint32_t)(USART_CR1_PCE | USART_CR1_PS)) 
#define IS_UART_PARITY(PARITY) (((PARITY) == UART_PARITY_NONE) || \
                                ((PARITY) == UART_PARITY_EVEN) || \
                                ((PARITY) == UART_PARITY_ODD))
/**
  * @}
  */ 

/** @defgroup UART_Hardware_Flow_Control UART hardware flow control definition
  * @{
  */ 
#define UART_HWCONTROL_NONE                  ((uint32_t)0x0000U)
#define UART_HWCONTROL_RTS                   ((uint32_t)USART_CR3_RTSE)
#define UART_HWCONTROL_CTS                   ((uint32_t)USART_CR3_CTSE)
#define UART_HWCONTROL_RTS_CTS               ((uint32_t)(USART_CR3_RTSE | USART_CR3_CTSE))
#define IS_UART_HARDWARE_FLOW_CONTROL(CONTROL)\
                              (((CONTROL) == UART_HWCONTROL_NONE) || \
                               ((CONTROL) == UART_HWCONTROL_RTS) || \
                               ((CONTROL) == UART_HWCONTROL_CTS) || \
                               ((CONTROL) == UART_HWCONTROL_RTS_CTS))
/**
  * @}
  */

/** @defgroup UART_Mode UART mode definition
  * @{
  */ 
#define UART_MODE_RX                        ((uint32_t)USART_CR1_RE)
#define UART_MODE_TX                        ((uint32_t)USART_CR1_TE)
#define UART_MODE_TX_RX                     ((uint32_t)(USART_CR1_TE |USART_CR1_RE))
#define IS_UART_MODE(MODE) ((((MODE) & (~((uint32_t)(UART_MODE_TX_RX)))) == (uint32_t)0x00U) && ((MODE) != (uint32_t)0x00U))
/**
  * @}
  */
    
 /** @defgroup UART_State UART state enable and disable definition
  * @{
  */ 
#define UART_STATE_DISABLE                  ((uint32_t)0x0000U)
#define UART_STATE_ENABLE                   ((uint32_t)USART_CR1_UE)
#define IS_UART_STATE(STATE) (((STATE) == UART_STATE_DISABLE) || \
                              ((STATE) == UART_STATE_ENABLE))
/**
  * @}
  */

/** @defgroup UART_Over_Sampling UART over sampling definition
  * @{
  */
#define UART_OVERSAMPLING_16                    ((uint32_t)0x0000U)
#define UART_OVERSAMPLING_8                     ((uint32_t)USART_CR1_OVER8)
#define IS_UART_OVERSAMPLING(SAMPLING) (((SAMPLING) == UART_OVERSAMPLING_16) || \
                                        ((SAMPLING) == UART_OVERSAMPLING_8))
/**
  * @}
  */ 
  

/** @defgroup UART_Receiver_TimeOut UART receiver timeOut definition
  * @{
  */
#define UART_RECEIVER_TIMEOUT_DISABLE   ((uint32_t)0x00000000U)
#define UART_RECEIVER_TIMEOUT_ENABLE    ((uint32_t)USART_CR2_RTOEN)
#define IS_UART_RECEIVER_TIMEOUT(TIMEOUT) (((TIMEOUT) == UART_RECEIVER_TIMEOUT_DISABLE) || \
                                           ((TIMEOUT) == UART_RECEIVER_TIMEOUT_ENABLE))
/**
  * @}
  */ 

/** @defgroup UART_LIN UART LIN enable and disable definition
  * @{
  */
#define UART_LIN_DISABLE            ((uint32_t)0x00000000U)
#define UART_LIN_ENABLE             ((uint32_t)USART_CR2_LINEN)
#define IS_UART_LIN(LIN)            (((LIN) == UART_LIN_DISABLE) || \
                                     ((LIN) == UART_LIN_ENABLE))
/**
  * @}
  */ 
  
/** @defgroup UART_LIN_Break_Detection UART LIN break detection definition
  * @{
  */
#define UART_LINBREAKDETECTLENGTH_10B            ((uint32_t)0x00000000U)
#define UART_LINBREAKDETECTLENGTH_11B            ((uint32_t)USART_CR2_LBDL)
#define IS_UART_LIN_BREAK_DETECT_LENGTH(LENGTH) (((LENGTH) == UART_LINBREAKDETECTLENGTH_10B) || \
                                                 ((LENGTH) == UART_LINBREAKDETECTLENGTH_11B))
/**
  * @}
  */ 
  
 

/** @defgroup UART_One_Bit UART one bit definition
  * @{
  */
#define UART_ONE_BIT_SAMPLE_DISABLE          ((uint32_t)0x00000000U)
#define UART_ONE_BIT_SAMPLE_ENABLE           ((uint32_t)USART_CR3_ONEBIT)
#define IS_UART_ONE_BIT_SAMPLE(ONEBIT)       (((ONEBIT) == UART_ONE_BIT_SAMPLE_DISABLE) || \
                                              ((ONEBIT) == UART_ONE_BIT_SAMPLE_ENABLE))
/**
  * @}
  */  
  
/** @defgroup UART_DMA_Tx UART DMA Tx definition
  * @{
  */
#define UART_DMA_TX_DISABLE          ((uint32_t)0x00000000U)
#define UART_DMA_TX_ENABLE           ((uint32_t)USART_CR3_DMAT)
#define IS_UART_DMA_TX(DMATX)         (((DMATX) == UART_DMA_TX_DISABLE) || \
                                       ((DMATX) == UART_DMA_TX_ENABLE))
/**
  * @}
  */

/** @defgroup UART_DMA_Rx UART DMA Rx definition
  * @{
  */
#define UART_DMA_RX_DISABLE           ((uint32_t)0x0000U)
#define UART_DMA_RX_ENABLE            ((uint32_t)USART_CR3_DMAR)
#define IS_UART_DMA_RX(DMARX)         (((DMARX) == UART_DMA_RX_DISABLE) || \
                                       ((DMARX) == UART_DMA_RX_ENABLE))
/**
  * @}
  */

/** @defgroup UART_Half_Duplex_Selection UART half duplex selection definition
  * @{
  */
#define UART_HALF_DUPLEX_DISABLE          ((uint32_t)0x0000U)
#define UART_HALF_DUPLEX_ENABLE           ((uint32_t)USART_CR3_HDSEL)
#define IS_UART_HALF_DUPLEX(HDSEL)         (((HDSEL) == UART_HALF_DUPLEX_DISABLE) || \
                                            ((HDSEL) == UART_HALF_DUPLEX_ENABLE))
/**
  * @}
  */

/** @defgroup UART_Flags UART flags definition
  *        Elements values convention: 0xXXXX
  *           - 0xXXXX  : Flag mask in the ISR register
  * @{
  */
#define UART_FLAG_REACK                     USART_ISR_REACK   /*!< Receive Enable Acknowledge Flag */
#define UART_FLAG_TEACK                     USART_ISR_TEACK   /*!< Transmit Enable Acknowledge Flag */
#define UART_FLAG_WUF                       USART_ISR_WUF     /*!< Wake Up from stop mode Flag */
#define UART_FLAG_RWU                       USART_ISR_RWU     /*!< Receive Wake Up from mute mode Flag */
#define UART_FLAG_SBKF                      USART_ISR_SBKF    /*!< Send Break Flag */
#define UART_FLAG_CMF                       USART_ISR_CMF     /*!< Character Match Flag */
#define UART_FLAG_BUSY                      USART_ISR_BUSY    /*!< Busy Flag */
#define UART_FLAG_ABRF                      USART_ISR_ABRF    /*!< Auto-Baud Rate Flag */
#define UART_FLAG_ABRE                      USART_ISR_ABRE    /*!< Auto-Baud Rate Error */
#define UART_FLAG_EOBF                      USART_ISR_EOBF    /*!< End Of Block Flag */
#define UART_FLAG_RTOF                      USART_ISR_RTOF    /*!< Receiver Time Out */
#define UART_FLAG_CTS                       USART_ISR_CTS     /*!< CTS flag */
#define UART_FLAG_CTSIF                     USART_ISR_CTSIF   /*!< CTS interrupt flag */
#define UART_FLAG_LBDF                      USART_ISR_LBDF    /*!< LIN Break Detection Flag */
#define UART_FLAG_TXE                       USART_ISR_TXE     /*!< Transmit Data Register Empty */
#define UART_FLAG_TC                        USART_ISR_TC      /*!< Transmission Complete */
#define UART_FLAG_RXNE                      USART_ISR_RXNE    /*!< Read Data Register Not Empty */
#define UART_FLAG_IDLE                      USART_ISR_IDLE    /*!< IDLE line detected */
#define UART_FLAG_ORE                       USART_ISR_ORE     /*!< OverRun Error */
#define UART_FLAG_NE                        USART_ISR_NE      /*!< Noise detected Flag */
#define UART_FLAG_FE                        USART_ISR_FE      /*!< Framing Error */
#define UART_FLAG_PE                        USART_ISR_PE      /*!< Parity Error */
/**
  * @}
  */ 

/** @defgroup UART_Interrupt_definition UART interrupt definition
  *        Elements values convention: 000ZZZZZ0XXYYYYYb
  *           - YYYYY  : Interrupt source position in the XX register (5bits)
  *           - XX  : Interrupt source register (2bits)
  *                 - 01: CR1 register
  *                 - 10: CR2 register
  *                 - 11: CR3 register
  *           - ZZZZZ  : Flag position in the ISR register(5bits)
  * @{
  */
#define UART_IT_PE                          ((uint32_t)0x0028U)
#define UART_IT_TXE                         ((uint32_t)0x0727U)
#define UART_IT_TC                          ((uint32_t)0x0626U)
#define UART_IT_RXNE                        ((uint32_t)0x0525U)
#define UART_IT_IDLE                        ((uint32_t)0x0424U)
#define UART_IT_LBD                         ((uint32_t)0x0846U)
#define UART_IT_CTS                         ((uint32_t)0x096AU)
#define UART_IT_CM                          ((uint32_t)0x112EU)
#define UART_IT_WUF                         ((uint32_t)0x1476U)

/**       Elements values convention: 000000000XXYYYYYb
  *           - YYYYY  : Interrupt source position in the XX register (5bits)
  *           - XX  : Interrupt source register (2bits)
  *                 - 01: CR1 register
  *                 - 10: CR2 register
  *                 - 11: CR3 register
  */
#define UART_IT_ERR                         ((uint32_t)0x0060U)

/**       Elements values convention: 0000ZZZZ00000000b
  *           - ZZZZ  : Flag position in the ISR register(4bits)
  */
#define UART_IT_ORE                         ((uint32_t)0x0300U)
#define UART_IT_NE                          ((uint32_t)0x0200U)
#define UART_IT_FE                          ((uint32_t)0x0100U)
/**
  * @}
  */

/** @defgroup UART_IT_CLEAR_Flags  UART interrupt clear flags definition
  * @{
  */
#define UART_CLEAR_PEF                       USART_ICR_PECF            /*!< Parity Error Clear Flag */          
#define UART_CLEAR_FEF                       USART_ICR_FECF            /*!< Framing Error Clear Flag */         
#define UART_CLEAR_NEF                       USART_ICR_NCF             /*!< Noise detected Clear Flag */        
#define UART_CLEAR_OREF                      USART_ICR_ORECF           /*!< OverRun Error Clear Flag */         
#define UART_CLEAR_IDLEF                     USART_ICR_IDLECF          /*!< IDLE line detected Clear Flag */    
#define UART_CLEAR_TCF                       USART_ICR_TCCF            /*!< Transmission Complete Clear Flag */ 
#define UART_CLEAR_LBDF                      USART_ICR_LBDCF           /*!< LIN Break Detection Clear Flag */   
#define UART_CLEAR_CTSF                      USART_ICR_CTSCF           /*!< CTS Interrupt Clear Flag */         
#define UART_CLEAR_RTOF                      USART_ICR_RTOCF           /*!< Receiver Time Out Clear Flag */     
#define UART_CLEAR_EOBF                      USART_ICR_EOBCF           /*!< End Of Block Clear Flag */          
#define UART_CLEAR_CMF                       USART_ICR_CMCF            /*!< Character Match Clear Flag */       
#define UART_CLEAR_WUF                       USART_ICR_WUCF            /*!< Wake Up from stop mode Clear Flag */
/**
  * @}
  */

/** @defgroup UART_Request_Parameters UART request parameter definition
  * @{
  */
#define UART_AUTOBAUD_REQUEST            ((uint32_t)USART_RQR_ABRRQ)        /*!< Auto-Baud Rate Request */     
#define UART_SENDBREAK_REQUEST           ((uint32_t)USART_RQR_SBKRQ)        /*!< Send Break Request */         
#define UART_MUTE_MODE_REQUEST           ((uint32_t)USART_RQR_MMRQ)         /*!< Mute Mode Request */          
#define UART_RXDATA_FLUSH_REQUEST        ((uint32_t)USART_RQR_RXFRQ)        /*!< Receive Data flush Request */ 
#define UART_TXDATA_FLUSH_REQUEST        ((uint32_t)USART_RQR_TXFRQ)        /*!< Transmit data flush Request */
#define IS_UART_REQUEST_PARAMETER(PARAM) (((PARAM) == UART_AUTOBAUD_REQUEST) || \
                                          ((PARAM) == UART_SENDBREAK_REQUEST) || \
                                          ((PARAM) == UART_MUTE_MODE_REQUEST) || \
                                          ((PARAM) == UART_RXDATA_FLUSH_REQUEST) || \
                                          ((PARAM) == UART_TXDATA_FLUSH_REQUEST))
/**
  * @}
  */

/** @defgroup UART_Advanced_Features_Initialization_Type UART advanced features initialization type definition
  * @{
  */
#define UART_ADVFEATURE_NO_INIT                 ((uint32_t)0x00000000U)
#define UART_ADVFEATURE_TXINVERT_INIT           ((uint32_t)0x00000001U)
#define UART_ADVFEATURE_RXINVERT_INIT           ((uint32_t)0x00000002U)
#define UART_ADVFEATURE_DATAINVERT_INIT         ((uint32_t)0x00000004U)
#define UART_ADVFEATURE_SWAP_INIT               ((uint32_t)0x00000008U)
#define UART_ADVFEATURE_RXOVERRUNDISABLE_INIT   ((uint32_t)0x00000010U)
#define UART_ADVFEATURE_DMADISABLEONERROR_INIT  ((uint32_t)0x00000020U)
#define UART_ADVFEATURE_AUTOBAUDRATE_INIT       ((uint32_t)0x00000040U)
#define UART_ADVFEATURE_MSBFIRST_INIT           ((uint32_t)0x00000080U)
#define IS_UART_ADVFEATURE_INIT(INIT)           ((INIT) <= (UART_ADVFEATURE_NO_INIT | \
                                                            UART_ADVFEATURE_TXINVERT_INIT | \
                                                            UART_ADVFEATURE_RXINVERT_INIT | \
                                                            UART_ADVFEATURE_DATAINVERT_INIT | \
                                                            UART_ADVFEATURE_SWAP_INIT | \
                                                            UART_ADVFEATURE_RXOVERRUNDISABLE_INIT | \
                                                            UART_ADVFEATURE_DMADISABLEONERROR_INIT   | \
                                                            UART_ADVFEATURE_AUTOBAUDRATE_INIT | \
                                                            UART_ADVFEATURE_MSBFIRST_INIT))
/**
  * @}
  */

/** @defgroup UART_Tx_Inv UART advanced Tx inv activation definition
  * @{
  */
#define UART_ADVFEATURE_TXINV_DISABLE   ((uint32_t)0x00000000U)
#define UART_ADVFEATURE_TXINV_ENABLE    ((uint32_t)USART_CR2_TXINV)
#define IS_UART_ADVFEATURE_TXINV(TXINV) (((TXINV) == UART_ADVFEATURE_TXINV_DISABLE) || \
                                         ((TXINV) == UART_ADVFEATURE_TXINV_ENABLE))
/**
  * @}
  */

/** @defgroup UART_Rx_Inv UART advanced Rx inv activation definition
  * @{
  */
#define UART_ADVFEATURE_RXINV_DISABLE   ((uint32_t)0x00000000U)
#define UART_ADVFEATURE_RXINV_ENABLE    ((uint32_t)USART_CR2_RXINV)
#define IS_UART_ADVFEATURE_RXINV(RXINV) (((RXINV) == UART_ADVFEATURE_RXINV_DISABLE) || \
                                         ((RXINV) == UART_ADVFEATURE_RXINV_ENABLE))
/**
  * @}
  */

/** @defgroup UART_Data_Inv UART advanced data inv activation definition
  * @{
  */
#define UART_ADVFEATURE_DATAINV_DISABLE     ((uint32_t)0x00000000U)
#define UART_ADVFEATURE_DATAINV_ENABLE      ((uint32_t)USART_CR2_DATAINV)
#define IS_UART_ADVFEATURE_DATAINV(DATAINV) (((DATAINV) == UART_ADVFEATURE_DATAINV_DISABLE) || \
                                             ((DATAINV) == UART_ADVFEATURE_DATAINV_ENABLE))
/**
  * @}
  */

/** @defgroup UART_Rx_Tx_Swap UART advanced swap activation definition
  * @{
  */
#define UART_ADVFEATURE_SWAP_DISABLE   ((uint32_t)0x00000000U)
#define UART_ADVFEATURE_SWAP_ENABLE    ((uint32_t)USART_CR2_SWAP)
#define IS_UART_ADVFEATURE_SWAP(SWAP) (((SWAP) == UART_ADVFEATURE_SWAP_DISABLE) || \
                                       ((SWAP) == UART_ADVFEATURE_SWAP_ENABLE))
/**
  * @}
  */

/** @defgroup UART_Overrun_Disable UART advanced overrun activation definition
  * @{
  */
#define UART_ADVFEATURE_OVERRUN_ENABLE   ((uint32_t)0x00000000U)
#define UART_ADVFEATURE_OVERRUN_DISABLE  ((uint32_t)USART_CR3_OVRDIS)
#define IS_UART_OVERRUN(OVERRUN)         (((OVERRUN) == UART_ADVFEATURE_OVERRUN_ENABLE) || \
                                          ((OVERRUN) == UART_ADVFEATURE_OVERRUN_DISABLE))
/**
  * @}
  */

/** @defgroup UART_AutoBaudRate_Enable UART advanced auto baud rate activation definition
  * @{
  */
#define UART_ADVFEATURE_AUTOBAUDRATE_DISABLE           ((uint32_t)0x00000000U)
#define UART_ADVFEATURE_AUTOBAUDRATE_ENABLE            ((uint32_t)USART_CR2_ABREN)
#define IS_UART_ADVFEATURE_AUTOBAUDRATE(AUTOBAUDRATE)  (((AUTOBAUDRATE) == UART_ADVFEATURE_AUTOBAUDRATE_DISABLE) || \
                                                        ((AUTOBAUDRATE) == UART_ADVFEATURE_AUTOBAUDRATE_ENABLE))
/**
  * @}
  */

/** @defgroup UART_DMA_Disable_on_Rx_Error UART advanced DMA on Rx error activation definition
  * @{
  */
#define UART_ADVFEATURE_DMA_ENABLEONRXERROR       ((uint32_t)0x00000000U)
#define UART_ADVFEATURE_DMA_DISABLEONRXERROR      ((uint32_t)USART_CR3_DDRE)
#define IS_UART_ADVFEATURE_DMAONRXERROR(DMA)      (((DMA) == UART_ADVFEATURE_DMA_ENABLEONRXERROR) || \
                                                   ((DMA) == UART_ADVFEATURE_DMA_DISABLEONRXERROR))
/**
  * @}
  */

/** @defgroup UART_MSB_First  UART advanced MSB first activation definition
  * @{
  */
#define UART_ADVFEATURE_MSBFIRST_DISABLE      ((uint32_t)0x00000000U)
#define UART_ADVFEATURE_MSBFIRST_ENABLE       ((uint32_t)USART_CR2_MSBFIRST)
#define IS_UART_ADVFEATURE_MSBFIRST(MSBFIRST) (((MSBFIRST) == UART_ADVFEATURE_MSBFIRST_DISABLE) || \
                                               ((MSBFIRST) == UART_ADVFEATURE_MSBFIRST_ENABLE))
/**
  * @}
  */

/** @defgroup UART_Stop_Mode_Enable UART advanced stop mode activation definition
  * @{
  */
#define UART_ADVFEATURE_STOPMODE_DISABLE      ((uint32_t)0x00000000U)
#define UART_ADVFEATURE_STOPMODE_ENABLE       ((uint32_t)USART_CR1_UESM)
#define IS_UART_ADVFEATURE_STOPMODE(STOPMODE) (((STOPMODE) == UART_ADVFEATURE_STOPMODE_DISABLE) || \
                                               ((STOPMODE) == UART_ADVFEATURE_STOPMODE_ENABLE))
/**
  * @}
  */

/** @defgroup UART_Mute_Mode UART advanced mute mode activation definition
  * @{
  */
#define UART_ADVFEATURE_MUTEMODE_DISABLE    ((uint32_t)0x00000000U)
#define UART_ADVFEATURE_MUTEMODE_ENABLE    ((uint32_t)USART_CR1_MME)
#define IS_UART_MUTE_MODE(MUTE)           (((MUTE) == UART_ADVFEATURE_MUTEMODE_DISABLE) || \
                                           ((MUTE) == UART_ADVFEATURE_MUTEMODE_ENABLE))
/**
  * @}
  */

/** @defgroup UART_CR2_ADDRESS_LSBPOS UART CR2 address lsb position definition
  * @{
  */
#define UART_CR2_ADDRESS_LSB_POS            ((uint32_t) 24U)
/**
  * @}
  */

/** @defgroup UART_WakeUp_from_Stop_Selection UART wake up mode selection definition
  * @{
  */
#define UART_WAKEUP_ON_ADDRESS           ((uint32_t)0x0000U)
#define UART_WAKEUP_ON_STARTBIT          ((uint32_t)USART_CR3_WUS_1)
#define UART_WAKEUP_ON_READDATA_NONEMPTY ((uint32_t)USART_CR3_WUS)
#define IS_UART_WAKEUP_SELECTION(WAKE)   (((WAKE) == UART_WAKEUP_ON_ADDRESS) || \
                                          ((WAKE) == UART_WAKEUP_ON_STARTBIT) || \
                                          ((WAKE) == UART_WAKEUP_ON_READDATA_NONEMPTY))
/**
  * @}
  */

/** @defgroup UART_DriverEnable_Polarity UART driver polarity level definition
  * @{
  */
#define UART_DE_POLARITY_HIGH            ((uint32_t)0x00000000U)
#define UART_DE_POLARITY_LOW             ((uint32_t)USART_CR3_DEP)
#define IS_UART_DE_POLARITY(POLARITY)    (((POLARITY) == UART_DE_POLARITY_HIGH) || \
                                          ((POLARITY) == UART_DE_POLARITY_LOW))
/**
  * @}
  */

/** @defgroup UART_CR1_DEAT_ADDRESS_LSBPOS  UART CR1 DEAT address lsb position definition
  * @{
  */
#define UART_CR1_DEAT_ADDRESS_LSB_POS            ((uint32_t) 21U)
/**
  * @}
  */

/** @defgroup UART_CR1_DEDT_ADDRESS_LSBPOS UART CR1 DEDT address lsb position definition
  * @{
  */
#define UART_CR1_DEDT_ADDRESS_LSB_POS            ((uint32_t) 16U)
/**
  * @}
  */

/** @defgroup UART_Interruption_Mask UART interruption mask definition
  * @{
  */
#define UART_IT_MASK                             ((uint32_t)0x001FU)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup UART_Exported_Macros UART Exported Macros
  * @{
  */

/** @brief Reset UART handle state
  * @param  __HANDLE__: specifies the UART Handle.
  *         The Handle Instance which can be USART1, USART2 or LPUART.
  * @retval None
  */
#define __HAL_UART_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_UART_STATE_RESET)

/** @brief  Flush the UART Data registers
  * @param  __HANDLE__: specifies the UART Handle.
  */
#define __HAL_UART_FLUSH_DRREGISTER(__HANDLE__)  \
  do{                \
      SET_BIT((__HANDLE__)->Instance->RQR, UART_RXDATA_FLUSH_REQUEST); \
      SET_BIT((__HANDLE__)->Instance->RQR, UART_TXDATA_FLUSH_REQUEST); \
    } while(0)


/** @brief  Clears the specified UART pending flag.
  * @param  __HANDLE__: specifies the UART Handle.
  * @param  __FLAG__: specifies the flag to check.
  *          This parameter can be any combination of the following values:
  *            @arg UART_CLEAR_PEF
  *            @arg UART_CLEAR_FEF
  *            @arg UART_CLEAR_NEF
  *            @arg UART_CLEAR_OREF
  *            @arg UART_CLEAR_IDLEF
  *            @arg UART_CLEAR_TCF
  *            @arg UART_CLEAR_LBDF
  *            @arg UART_CLEAR_CTSF
  *            @arg UART_CLEAR_RTOF
  *            @arg UART_CLEAR_EOBF
  *            @arg UART_CLEAR_CMF
  *            @arg UART_CLEAR_WUF
  * @retval None
  */
#define __HAL_UART_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->ICR = (__FLAG__))


/** @brief  Clear the UART PE pending flag.
  * @param  __HANDLE__: specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_CLEAR_PEFLAG(__HANDLE__)   __HAL_UART_CLEAR_FLAG(__HANDLE__,UART_CLEAR_PEF)

/** @brief  Clear the UART FE pending flag.
  * @param  __HANDLE__: specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_CLEAR_FEFLAG(__HANDLE__)   __HAL_UART_CLEAR_FLAG(__HANDLE__,UART_CLEAR_FEF)

/** @brief  Clear the UART NE pending flag.
  * @param  __HANDLE__: specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_CLEAR_NEFLAG(__HANDLE__)  __HAL_UART_CLEAR_FLAG(__HANDLE__,UART_CLEAR_NEF)

/** @brief  Clear the UART ORE pending flag.
  * @param  __HANDLE__: specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_CLEAR_OREFLAG(__HANDLE__)   __HAL_UART_CLEAR_FLAG(__HANDLE__,UART_CLEAR_OREF)

/** @brief  Clear the UART IDLE pending flag.
  * @param  __HANDLE__: specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_CLEAR_IDLEFLAG(__HANDLE__)   __HAL_UART_CLEAR_FLAG(__HANDLE__,UART_CLEAR_IDLEF)

/** @brief  Checks whether the specified UART flag is set or not.
  * @param  __HANDLE__: specifies the UART Handle.
  *         This parameter can be USART1, USART2 or LPUART.
  * @param  __FLAG__: specifies the flag to check.
  *        This parameter can be one of the following values:
  *            @arg UART_FLAG_REACK: Receive enable ackowledge flag
  *            @arg UART_FLAG_TEACK: Transmit enable ackowledge flag
  *            @arg UART_FLAG_WUF:   Wake up from stop mode flag
  *            @arg UART_FLAG_RWU:   Receiver wake up flag (is the UART in mute mode)
  *            @arg UART_FLAG_SBKF:  Send Break flag
  *            @arg UART_FLAG_CMF:   Character match flag
  *            @arg UART_FLAG_BUSY:  Busy flag
  *            @arg UART_FLAG_ABRF:  Auto Baud rate detection flag
  *            @arg UART_FLAG_ABRE:  Auto Baud rate detection error flag
  *            @arg UART_FLAG_EOBF:  End of block flag   
  *            @arg UART_FLAG_RTOF:  Receiver timeout flag                     
  *            @arg UART_FLAG_CTS:   CTS Change flag (not available for UART4 and UART5)
  *            @arg UART_FLAG_LBD:   LIN Break detection flag
  *            @arg UART_FLAG_TXE:   Transmit data register empty flag
  *            @arg UART_FLAG_TC:    Transmission Complete flag
  *            @arg UART_FLAG_RXNE:  Receive data register not empty flag
  *            @arg UART_FLAG_IDLE:  Idle Line detection flag
  *            @arg UART_FLAG_ORE:   OverRun Error flag
  *            @arg UART_FLAG_NE:    Noise Error flag
  *            @arg UART_FLAG_FE:    Framing Error flag
  *            @arg UART_FLAG_PE:    Parity Error flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_UART_GET_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->ISR & (__FLAG__)) == (__FLAG__))

/** @brief  Enables the specified UART interrupt.
  * @param  __HANDLE__: specifies the UART Handle.
  *         This parameter can be USART1, USART2 or LPUART.
  * @param  __INTERRUPT__: specifies the UART interrupt source to enable.
  *          This parameter can be one of the following values:
  *            @arg UART_IT_WUF:  Wakeup from stop mode interrupt
  *            @arg UART_IT_CM:   Character match interrupt
  *            @arg UART_IT_CTS:  CTS change interrupt
  *            @arg UART_IT_LBD:  LIN Break detection interrupt
  *            @arg UART_IT_TXE:  Transmit Data Register empty interrupt
  *            @arg UART_IT_TC:   Transmission complete interrupt
  *            @arg UART_IT_RXNE: Receive Data register not empty interrupt
  *            @arg UART_IT_IDLE: Idle line detection interrupt
  *            @arg UART_IT_PE:   Parity Error interrupt
  *            @arg UART_IT_ERR:  Error interrupt(Frame error, noise error, overrun error)
  * @retval None
  */
#define __HAL_UART_ENABLE_IT(__HANDLE__, __INTERRUPT__)   (((((uint8_t)(__INTERRUPT__)) >> 5U) == 1U)? ((__HANDLE__)->Instance->CR1 |= (1U << ((__INTERRUPT__) & UART_IT_MASK))): \
                                                       ((((uint8_t)(__INTERRUPT__)) >> 5U) == 2U)? ((__HANDLE__)->Instance->CR2 |= (1U << ((__INTERRUPT__) & UART_IT_MASK))): \
                                                       ((__HANDLE__)->Instance->CR3 |= (1U << ((__INTERRUPT__) & UART_IT_MASK))))

/** @brief  Disables the specified UART interrupt.
  * @param  __HANDLE__: specifies the UART Handle.
  *         This parameter can be USART1, USART2 or LPUART.
  * @param  __INTERRUPT__: specifies the UART interrupt source to disable.
  *          This parameter can be one of the following values:
  *            @arg UART_IT_WUF:  Wakeup from stop mode interrupt
  *            @arg UART_IT_CM:   Character match interrupt            
  *            @arg UART_IT_CTS:  CTS change interrupt
  *            @arg UART_IT_LBD:  LIN Break detection interrupt
  *            @arg UART_IT_TXE:  Transmit Data Register empty interrupt
  *            @arg UART_IT_TC:   Transmission complete interrupt
  *            @arg UART_IT_RXNE: Receive Data register not empty interrupt
  *            @arg UART_IT_IDLE: Idle line detection interrupt
  *            @arg UART_IT_PE:   Parity Error interrupt
  *            @arg UART_IT_ERR:  Error interrupt(Frame error, noise error, overrun error)
  * @retval None
  */
#define __HAL_UART_DISABLE_IT(__HANDLE__, __INTERRUPT__)  (((((uint8_t)(__INTERRUPT__)) >> 5U) == 1U)? ((__HANDLE__)->Instance->CR1 &= ~ ((uint32_t)1U << ((__INTERRUPT__) & UART_IT_MASK))): \
                                                       ((((uint8_t)(__INTERRUPT__)) >> 5U) == 2U)? ((__HANDLE__)->Instance->CR2 &= ~ ((uint32_t)1U << ((__INTERRUPT__) & UART_IT_MASK))): \
                                                       ((__HANDLE__)->Instance->CR3 &= ~ ((uint32_t)1U << ((__INTERRUPT__) & UART_IT_MASK))))

/** @brief  Checks whether the specified UART interrupt has occurred or not.
  * @param  __HANDLE__: specifies the UART Handle.
  *         This parameter can be USART1, USART2 or LPUART.
  * @param  __IT__: specifies the UART interrupt to check.
  *          This parameter can be one of the following values:
  *            @arg UART_IT_WUF:  Wakeup from stop mode interrupt
  *            @arg UART_IT_CM:   Character match interrupt              
  *            @arg UART_IT_CTS:  CTS change interrupt (not available for UART4 and UART5)
  *            @arg UART_IT_LBD:  LIN Break detection interrupt
  *            @arg UART_IT_TXE:  Transmit Data Register empty interrupt
  *            @arg UART_IT_TC:   Transmission complete interrupt
  *            @arg UART_IT_RXNE: Receive Data register not empty interrupt
  *            @arg UART_IT_IDLE: Idle line detection interrupt
  *            @arg UART_IT_ORE:  OverRun Error interrupt
  *            @arg UART_IT_NE:   Noise Error interrupt
  *            @arg UART_IT_FE:   Framing Error interrupt
  *            @arg UART_IT_PE:   Parity Error interrupt  
  * @retval The new state of __IT__ (TRUE or FALSE).
  */
#define __HAL_UART_GET_IT(__HANDLE__, __IT__) ((__HANDLE__)->Instance->ISR & ((uint32_t)1U << ((__IT__)>> 0x08U)))

/** @brief  Checks whether the specified UART interrupt source is enabled.
  * @param  __HANDLE__: specifies the UART Handle.
  *         This parameter can be USART1, USART2 or LPUART.
  * @param  __IT__: specifies the UART interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg UART_IT_CTS: CTS change interrupt (not available for UART4 and UART5)
  *            @arg UART_IT_LBD: LIN Break detection interrupt
  *            @arg UART_IT_TXE: Transmit Data Register empty interrupt
  *            @arg UART_IT_TC:  Transmission complete interrupt
  *            @arg UART_IT_RXNE: Receive Data register not empty interrupt
  *            @arg UART_IT_IDLE: Idle line detection interrupt
  *            @arg UART_IT_ORE: OverRun Error interrupt
  *            @arg UART_IT_NE: Noise Error interrupt
  *            @arg UART_IT_FE: Framing Error interrupt
  *            @arg UART_IT_PE: Parity Error interrupt  
  * @retval The new state of __IT__ (TRUE or FALSE).
  */
#define __HAL_UART_GET_IT_SOURCE(__HANDLE__, __IT__) ((((((uint8_t)(__IT__)) >> 5U) == 1U)? (__HANDLE__)->Instance->CR1:(((((uint8_t)(__IT__)) >> 5U) == 2U)? \
                                                       (__HANDLE__)->Instance->CR2 : (__HANDLE__)->Instance->CR3)) & ((uint32_t)1U << (((uint16_t)(__IT__)) & UART_IT_MASK)))

/** @brief  Clears the specified UART ISR flag, in setting the proper ICR register flag.
  * @param  __HANDLE__: specifies the UART Handle.
  *         This parameter can be USART1, USART2 or LPUART.
  * @param  __IT_CLEAR__: specifies the interrupt clear register flag that needs to be set
  *                       to clear the corresponding interrupt
  *          This parameter can be one of the following values:
  *            @arg UART_CLEAR_PEF: Parity Error Clear Flag
  *            @arg UART_CLEAR_FEF: Framing Error Clear Flag
  *            @arg UART_CLEAR_NEF: Noise detected Clear Flag
  *            @arg UART_CLEAR_OREF: OverRun Error Clear Flag
  *            @arg UART_CLEAR_IDLEF: IDLE line detected Clear Flag
  *            @arg UART_CLEAR_TCF: Transmission Complete Clear Flag
  *            @arg UART_CLEAR_LBDF: LIN Break Detection Clear Flag
  *            @arg UART_CLEAR_CTSF: CTS Interrupt Clear Flag
  *            @arg UART_CLEAR_RTOF: Receiver Time Out Clear Flag
  *            @arg UART_CLEAR_EOBF: End Of Block Clear Flag
  *            @arg UART_CLEAR_CMF: Character Match Clear Flag
  *            @arg UART_CLEAR_WUF:  Wake Up from stop mode Clear Flag
  * @retval None
  */
#define __HAL_UART_CLEAR_IT(__HANDLE__, __IT_CLEAR__) ((__HANDLE__)->Instance->ICR = (uint32_t)(__IT_CLEAR__))

/** @brief  Set a specific UART request flag.
  * @param  __HANDLE__: specifies the UART Handle.
  *         This parameter can be USART1, USART2 or LPUART.
  * @param  __REQ__: specifies the request flag to set
  *          This parameter can be one of the following values:
  *            @arg UART_AUTOBAUD_REQUEST: Auto-Baud Rate Request
  *            @arg UART_SENDBREAK_REQUEST: Send Break Request
  *            @arg UART_MUTE_MODE_REQUEST: Mute Mode Request
  *            @arg UART_RXDATA_FLUSH_REQUEST: Receive Data flush Request
  *            @arg UART_TXDATA_FLUSH_REQUEST: Transmit data flush Request
  * @retval None
  */
#define __HAL_UART_SEND_REQ(__HANDLE__, __REQ__) ((__HANDLE__)->Instance->RQR |= (uint32_t)(__REQ__))

/** @brief  Enables the UART one bit sample method
  * @param  __HANDLE__: specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_ONE_BIT_SAMPLE_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->CR3|= USART_CR3_ONEBIT)

/** @brief  Disables the UART one bit sample method
  * @param  __HANDLE__: specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_ONE_BIT_SAMPLE_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->CR3 &= (uint32_t)~((uint32_t)USART_CR3_ONEBIT))

/** @brief  Enable UART
  * @param  __HANDLE__: specifies the UART Handle.
  *         The Handle Instance can be USART1, USART2 or LPUART.
  * @retval None
  */ 
#define __HAL_UART_ENABLE(__HANDLE__)                   ((__HANDLE__)->Instance->CR1 |=  USART_CR1_UE)

/** @brief  Disable UART
  * @param  __HANDLE__: specifies the UART Handle.
  *         The Handle Instance can be USART1, USART2 or LPUART.
  * @retval None
  */
#define __HAL_UART_DISABLE(__HANDLE__)                  ((__HANDLE__)->Instance->CR1 &=  ~USART_CR1_UE)

/** @brief  Enable CTS flow control 
  *         This macro allows to enable CTS hardware flow control for a given UART instance, 
  *         without need to call HAL_UART_Init() function.
  *         As involving direct access to UART registers, usage of this macro should be fully endorsed by user.
  * @note   As macro is expected to be used for modifying CTS Hw flow control feature activation, without need
  *         for USART instance Deinit/Init, following conditions for macro call should be fulfilled :
  *           - UART instance should have already been initialised (through call of HAL_UART_Init() )
  *           - macro could only be called when corresponding UART instance is disabled (i.e __HAL_UART_DISABLE(__HANDLE__))
  *             and should be followed by an Enable macro (i.e __HAL_UART_ENABLE(__HANDLE__)).                                                                                                                  
  * @param  __HANDLE__: specifies the UART Handle.
  *         The Handle Instance can be USART1, USART2 or LPUART.
  * @retval None
  */
#define __HAL_UART_HWCONTROL_CTS_ENABLE(__HANDLE__)        \
  do{                                                      \
    SET_BIT((__HANDLE__)->Instance->CR3, USART_CR3_CTSE);  \
    (__HANDLE__)->Init.HwFlowCtl |= USART_CR3_CTSE;        \
  } while(0)

/** @brief  Disable CTS flow control 
  *         This macro allows to disable CTS hardware flow control for a given UART instance, 
  *         without need to call HAL_UART_Init() function.
  *         As involving direct access to UART registers, usage of this macro should be fully endorsed by user.
  * @note   As macro is expected to be used for modifying CTS Hw flow control feature activation, without need
  *         for USART instance Deinit/Init, following conditions for macro call should be fulfilled :
  *           - UART instance should have already been initialised (through call of HAL_UART_Init() )
  *           - macro could only be called when corresponding UART instance is disabled (i.e __HAL_UART_DISABLE(__HANDLE__))
  *             and should be followed by an Enable macro (i.e __HAL_UART_ENABLE(__HANDLE__)). 
  * @param  __HANDLE__: specifies the UART Handle.
  *         The Handle Instance can be USART1, USART2 or LPUART.
  * @retval None
  */
#define __HAL_UART_HWCONTROL_CTS_DISABLE(__HANDLE__)        \
  do{                                                       \
    CLEAR_BIT((__HANDLE__)->Instance->CR3, USART_CR3_CTSE); \
    (__HANDLE__)->Init.HwFlowCtl &= ~(USART_CR3_CTSE);      \
  } while(0)

/** @brief  Enable RTS flow control 
  *         This macro allows to enable RTS hardware flow control for a given UART instance, 
  *         without need to call HAL_UART_Init() function.
  *         As involving direct access to UART registers, usage of this macro should be fully endorsed by user.
  * @note   As macro is expected to be used for modifying RTS Hw flow control feature activation, without need
  *         for USART instance Deinit/Init, following conditions for macro call should be fulfilled :
  *           - UART instance should have already been initialised (through call of HAL_UART_Init() )
  *           - macro could only be called when corresponding UART instance is disabled (i.e __HAL_UART_DISABLE(__HANDLE__))
  *             and should be followed by an Enable macro (i.e __HAL_UART_ENABLE(__HANDLE__)). 
  * @param  __HANDLE__: specifies the UART Handle.
  *         The Handle Instance can be USART1, USART2 or LPUART.
  * @retval None
  */
#define __HAL_UART_HWCONTROL_RTS_ENABLE(__HANDLE__)       \
  do{                                                     \
    SET_BIT((__HANDLE__)->Instance->CR3, USART_CR3_RTSE); \
    (__HANDLE__)->Init.HwFlowCtl |= USART_CR3_RTSE;       \
  } while(0)

/** @brief  Disable RTS flow control 
  *         This macro allows to disable RTS hardware flow control for a given UART instance, 
  *         without need to call HAL_UART_Init() function.
  *         As involving direct access to UART registers, usage of this macro should be fully endorsed by user.
  * @note   As macro is expected to be used for modifying RTS Hw flow control feature activation, without need
  *         for USART instance Deinit/Init, following conditions for macro call should be fulfilled :
  *           - UART instance should have already been initialised (through call of HAL_UART_Init() )
  *           - macro could only be called when corresponding UART instance is disabled (i.e __HAL_UART_DISABLE(__HANDLE__))
  *             and should be followed by an Enable macro (i.e __HAL_UART_ENABLE(__HANDLE__)). 
  * @param  __HANDLE__: specifies the UART Handle.
  *         The Handle Instance can be USART1, USART2 or LPUART.
  * @retval None
  */
#define __HAL_UART_HWCONTROL_RTS_DISABLE(__HANDLE__)       \
  do{                                                      \
    CLEAR_BIT((__HANDLE__)->Instance->CR3, USART_CR3_RTSE);\
    (__HANDLE__)->Init.HwFlowCtl &= ~(USART_CR3_RTSE);     \
  } while(0)

/** @brief  macros to enable the UART's one bit sampling method
  * @param  __HANDLE__: specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_ONE_BIT_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->CR3|= USART_CR3_ONEBIT)

/** @brief  macros to disable the UART's one bit sampling method
  * @param  __HANDLE__: specifies the UART Handle.
  * @retval None
  */
#define __HAL_UART_ONE_BIT_DISABLE(__HANDLE__) ((__HANDLE__)->Instance->CR3 &= (uint16_t)~((uint16_t)USART_CR3_ONEBIT))


/** @brief  BRR division operation to set BRR register with LPUART
  * @param  _PCLK_: LPUART clock
  * @param  _BAUD_: Baud rate set by the user
  * @retval Division result
  */
#define __DIV_LPUART(_PCLK_, _BAUD_)                ((uint32_t)(((((uint64_t)_PCLK_)*256.0) + (((uint64_t)_BAUD_)/2U)) / (((uint64_t)_BAUD_))))
    
/** @brief  BRR division operation to set BRR register in 8-bit oversampling mode
  * @param  _PCLK_: UART clock
  * @param  _BAUD_: Baud rate set by the user
  * @retval Division result
  */
#define UART_DIV_SAMPLING8(_PCLK_, _BAUD_)             ((((_PCLK_)*2U) + ((_BAUD_)/2U)) / ((_BAUD_)))

/** @brief  BRR division operation to set BRR register in 16-bit oversampling mode
  * @param  _PCLK_: UART clock
  * @param  _BAUD_: Baud rate set by the user
  * @retval Division result
  */
#define UART_DIV_SAMPLING16(_PCLK_, _BAUD_)             ((((_PCLK_)) + ((_BAUD_)/2U)) / ((_BAUD_)))

/** @brief  Check whether or not UART instance is Low Power UART.
  * @param  __HANDLE__: specifies the UART Handle.
  * @retval SET (instance is LPUART) or RESET (instance isn't LPUART)
  */
#define UART_INSTANCE_LOWPOWER(__HANDLE__) (((__HANDLE__)->Instance == LPUART1) ? SET : RESET )

/** @brief  Check UART Baud rate
  * @param  BAUDRATE: Baudrate specified by the user
  *         The maximum Baud Rate is derived from the maximum clock on L0 (i.e. 32 MHz) 
  *         divided by the smallest oversampling used on the USART (i.e. 8) 
  * @retval Test result (TRUE or FALSE).
  */
#define IS_UART_BAUDRATE(BAUDRATE) ((BAUDRATE) < 4000001)

/** @brief  Check UART byte address
  * @param  ADDRESS: UART 8-bit address for wake-up process scheme
  * @retval Test result (TRUE or FALSE). 
  */ 
#define IS_UART_7B_ADDRESS(ADDRESS) ((ADDRESS) <= 0x7F)

/** @brief  Check UART 4-bit address
  * @param  ADDRESS: UART 4-bit address for wake-up process scheme
  * @retval Test result (TRUE or FALSE). 
  */ 
#define IS_UART_4B_ADDRESS(ADDRESS) ((ADDRESS) <= 0xF)

/** @brief  Check UART assertion time
  * @param  TIME: 5-bit value assertion time
  * @retval Test result (TRUE or FALSE). 
  */ 
#define IS_UART_ASSERTIONTIME(TIME)    ((TIME) <= 0x1F)

/** @brief  Check UART deassertion time
  * @param  TIME: 5-bit value deassertion time
  * @retval Test result (TRUE or FALSE). 
  */
#define IS_UART_DEASSERTIONTIME(TIME) ((TIME) <= 0x1F)

/**
  * @}
  */
/* Include UART HAL Extension module */
#include "stm32l0xx_hal_uart_ex.h"

/******************************************************************************/
/* Exported functions --------------------------------------------------------*/
/******************************************************************************/

/* Exported functions --------------------------------------------------------*/
/** @defgroup UART_Exported_Functions UART Exported Functions
  * @{
  */
/* Initialization/de-initialization functions  ********************************/
/** @defgroup UART_Exported_Functions_Group1 Initialization/de-initialization methods
 *  @{
 */
HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_HalfDuplex_Init(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_LIN_Init(UART_HandleTypeDef *huart, uint32_t BreakDetectLength);
HAL_StatusTypeDef HAL_MultiProcessor_Init(UART_HandleTypeDef *huart, uint8_t Address, uint32_t WakeUpMethod);
HAL_StatusTypeDef HAL_UART_DeInit (UART_HandleTypeDef *huart);
void HAL_UART_MspInit(UART_HandleTypeDef *huart);
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart);
/**
  * @}
  */

/* IO operation functions *****************************************************/
/** @defgroup UART_Exported_Functions_Group2 IO operation functions
 *  @{
 */
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_DMAPause(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DMAResume(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DMAStop(UART_HandleTypeDef *huart);
void HAL_UART_IRQHandler(UART_HandleTypeDef *huart);
void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart);
/**
  * @}
  */
/* Peripheral Control and State functions  ************************************/
/** @defgroup UART_Exported_Functions_Group3 Peripheral Control funtions
 *  @{
 */
HAL_StatusTypeDef HAL_MultiProcessor_EnableMuteMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_MultiProcessor_DisableMuteMode(UART_HandleTypeDef *huart);
void HAL_MultiProcessor_EnterMuteMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_HalfDuplex_EnableTransmitter(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_HalfDuplex_EnableReceiver(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_LIN_SendBreak(UART_HandleTypeDef *huart);
HAL_UART_StateTypeDef HAL_UART_GetState(UART_HandleTypeDef *huart);
uint32_t HAL_UART_GetError(UART_HandleTypeDef *huart);
/**
  * @}
  */
/**
  * @}
  */

/** @addtogroup UART_Private
  * @{
  */
void UART_SetConfig(UART_HandleTypeDef *huart);
HAL_StatusTypeDef UART_CheckIdleState(UART_HandleTypeDef *huart);
HAL_StatusTypeDef UART_WaitOnFlagUntilTimeout(UART_HandleTypeDef *huart, uint32_t Flag, FlagStatus Status, uint32_t Timeout);
void UART_AdvFeatureConfig(UART_HandleTypeDef *huart);
/**
  * @}
  */


/* Define the private group ***********************************/
/**************************************************************/
/** @defgroup UART_Private UART Private
  * @{
  */
/**
  * @}
  */
/**************************************************************/

/**
  * @}
  */ 
/**
  * @}
  */ 
  
#ifdef __cplusplus
}
#endif

#endif /* __STM32L0xx_HAL_UART_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
