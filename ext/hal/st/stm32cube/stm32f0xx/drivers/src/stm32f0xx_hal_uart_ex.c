/**
  ******************************************************************************
  * @file    stm32f0xx_hal_uart_ex.c
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    27-May-2016
  * @brief   Extended UART HAL module driver.
  *          This file provides firmware functions to manage the following extended
  *          functionalities of the Universal Asynchronous Receiver Transmitter Peripheral (UART).
  *           + Initialization and de-initialization functions
  *           + Peripheral Control functions
  *
  *
  @verbatim
  ==============================================================================
               ##### UART peripheral extended features  #####
  ==============================================================================

    (#) Declare a UART_HandleTypeDef handle structure.

    (#) For the UART RS485 Driver Enable mode, initialize the UART registers
        by calling the HAL_RS485Ex_Init() API.


  @endverbatim
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

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/** @addtogroup STM32F0xx_HAL_Driver
  * @{
  */

/** @defgroup UARTEx UARTEx
  * @brief UART Extended HAL module driver
  * @{
  */

#ifdef HAL_UART_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup UARTEx_Private_Functions UARTEx Private Functions
  * @{
  */
#if !defined(STM32F030x6) && !defined(STM32F030x8)&& !defined(STM32F070xB)&& !defined(STM32F070x6)&& !defined(STM32F030xC)
static void UARTEx_Wakeup_AddressConfig(UART_HandleTypeDef *huart, UART_WakeUpTypeDef WakeUpSelection);
#endif /* !defined(STM32F030x6) && !defined(STM32F030x8)&& !defined(STM32F070xB)&& !defined(STM32F070x6)&& !defined(STM32F030xC) */

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/

/** @defgroup UARTEx_Exported_Functions UARTEx Exported Functions
  * @{
  */

/** @defgroup UARTEx_Exported_Functions_Group1 Extended Initialization and de-initialization functions
  * @brief    Extended Initialization and Configuration Functions
  *
@verbatim
===============================================================================
            ##### Initialization and Configuration functions #####
 ==============================================================================
    [..]
    This subsection provides a set of functions allowing to initialize the USARTx or the UARTy
    in asynchronous mode.
      (+) For the asynchronous mode the parameters below can be configured:
        (++) Baud Rate
        (++) Word Length (Fixed to 8-bits only for LIN mode)
        (++) Stop Bit
        (++) Parity
        (++) Hardware flow control
        (++) Receiver/transmitter modes
        (++) Over Sampling Method
        (++) One-Bit Sampling Method
      (+) For the asynchronous mode, the following advanced features can be configured as well:
        (++) TX and/or RX pin level inversion
        (++) data logical level inversion
        (++) RX and TX pins swap
        (++) RX overrun detection disabling
        (++) DMA disabling on RX error
        (++) MSB first on communication line
        (++) auto Baud rate detection
    [..]
    The HAL_LIN_Init() and HAL_RS485Ex_Init() APIs follows respectively the LIN and 
    the UART RS485 mode configuration procedures (details for the procedures are 
    available in reference manual).

@endverbatim
  * @{
  */

/*
  Additional Table:  If the parity is enabled, then the MSB bit of the data written
                     in the data register is transmitted but is changed by the parity bit.
                     According to device capability (support or not of 7-bit word length),
                     frame length is either defined by the M bit (8-bits or 9-bits)
                     or by the M1 and M0 bits (7-bit, 8-bit or 9-bit).
                     Possible UART frame formats are as listed in the following table:
            
      Table 1. UART frame format.             
      +-----------------------------------------------------------------------+
      |       M bit       |  PCE bit  |             UART frame                |
      |-------------------|-----------|---------------------------------------|
      |         0         |     0     |    | SB |    8-bit data   | STB |     |
      |-------------------|-----------|---------------------------------------|
      |         0         |     1     |    | SB | 7-bit data | PB | STB |     |
      |-------------------|-----------|---------------------------------------|
      |         1         |     0     |    | SB |    9-bit data   | STB |     |
      |-------------------|-----------|---------------------------------------|
      |         1         |     1     |    | SB | 8-bit data | PB | STB |     |
      +-----------------------------------------------------------------------+
      |  M1 bit |  M0 bit |  PCE bit  |             UART frame                |
      |---------|---------|-----------|---------------------------------------|
      |    0    |    0    |     0     |    | SB |    8 bit data   | STB |     |
      |---------|---------|-----------|---------------------------------------|
      |    0    |    0    |     1     |    | SB | 7 bit data | PB | STB |     |
      |---------|---------|-----------|---------------------------------------|
      |    0    |    1    |     0     |    | SB |    9 bit data   | STB |     |
      |---------|---------|-----------|---------------------------------------|
      |    0    |    1    |     1     |    | SB | 8 bit data | PB | STB |     |
      |---------|---------|-----------|---------------------------------------|
      |    1    |    0    |     0     |    | SB |    7 bit data   | STB |     |
      |---------|---------|-----------|---------------------------------------|
      |    1    |    0    |     1     |    | SB | 6 bit data | PB | STB |     |
      +-----------------------------------------------------------------------+

*/

/**
  * @brief Initialize the RS485 Driver enable feature according to the specified
  *         parameters in the UART_InitTypeDef and creates the associated handle.
  * @param huart: UART handle.
  * @param Polarity: select the driver enable polarity.
  *        This parameter can be one of the following values:
  *          @arg UART_DE_POLARITY_HIGH: DE signal is active high
  *          @arg UART_DE_POLARITY_LOW: DE signal is active low
  * @param AssertionTime: Driver Enable assertion time:
  *                         5-bit value defining the time between the activation of the DE (Driver Enable)
  *                         signal and the beginning of the start bit. It is expressed in sample time
  *                         units (1/8 or 1/16 bit time, depending on the oversampling rate)
  * @param DeassertionTime: Driver Enable deassertion time:
  *                         5-bit value defining the time between the end of the last stop bit, in a
  *                         transmitted message, and the de-activation of the DE (Driver Enable) signal.
  *                         It is expressed in sample time units (1/8 or 1/16 bit time, depending on the
  *                         oversampling rate).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_RS485Ex_Init(UART_HandleTypeDef *huart, uint32_t Polarity, uint32_t AssertionTime, uint32_t DeassertionTime)
{
  uint32_t temp = 0x0;

  /* Check the UART handle allocation */
  if(huart == NULL)
  {
    return HAL_ERROR;
  }
  /* Check the Driver Enable UART instance */
  assert_param(IS_UART_DRIVER_ENABLE_INSTANCE(huart->Instance));

  /* Check the Driver Enable polarity */
  assert_param(IS_UART_DE_POLARITY(Polarity));

  /* Check the Driver Enable assertion time */
  assert_param(IS_UART_ASSERTIONTIME(AssertionTime));

  /* Check the Driver Enable deassertion time */
  assert_param(IS_UART_DEASSERTIONTIME(DeassertionTime));

  if(huart->gState == HAL_UART_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    huart->Lock = HAL_UNLOCKED;

    /* Init the low level hardware : GPIO, CLOCK, CORTEX */
    HAL_UART_MspInit(huart);
  }

  huart->gState = HAL_UART_STATE_BUSY;

  /* Disable the Peripheral */
  __HAL_UART_DISABLE(huart);

  /* Set the UART Communication parameters */
  if (UART_SetConfig(huart) == HAL_ERROR)
  {
    return HAL_ERROR;
  }

  if(huart->AdvancedInit.AdvFeatureInit != UART_ADVFEATURE_NO_INIT)
  {
    UART_AdvFeatureConfig(huart);
  }

  /* Enable the Driver Enable mode by setting the DEM bit in the CR3 register */
  SET_BIT(huart->Instance->CR3, USART_CR3_DEM);

  /* Set the Driver Enable polarity */
  MODIFY_REG(huart->Instance->CR3, USART_CR3_DEP, Polarity);

  /* Set the Driver Enable assertion and deassertion times */
  temp = (AssertionTime << UART_CR1_DEAT_ADDRESS_LSB_POS);
  temp |= (DeassertionTime << UART_CR1_DEDT_ADDRESS_LSB_POS);
  MODIFY_REG(huart->Instance->CR1, (USART_CR1_DEDT|USART_CR1_DEAT), temp);

  /* Enable the Peripheral */
  __HAL_UART_ENABLE(huart);

  /* TEACK and/or REACK to check before moving huart->gState and huart->RxState to Ready */
  return (UART_CheckIdleState(huart));
}

#if !defined(STM32F030x6) && !defined(STM32F030x8)&& !defined(STM32F070xB)&& !defined(STM32F070x6)&& !defined(STM32F030xC)
/**
  * @brief Initialize the LIN mode according to the specified
  *         parameters in the UART_InitTypeDef and creates the associated handle .
  * @param huart: UART handle.
  * @param BreakDetectLength: specifies the LIN break detection length.
  *        This parameter can be one of the following values:
  *          @arg UART_LINBREAKDETECTLENGTH_10B: 10-bit break detection
  *          @arg UART_LINBREAKDETECTLENGTH_11B: 11-bit break detection
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LIN_Init(UART_HandleTypeDef *huart, uint32_t BreakDetectLength)
{
  /* Check the UART handle allocation */
  if(huart == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the LIN UART instance */
  assert_param(IS_UART_LIN_INSTANCE(huart->Instance));
  /* Check the Break detection length parameter */
  assert_param(IS_UART_LIN_BREAK_DETECT_LENGTH(BreakDetectLength));

  /* LIN mode limited to 16-bit oversampling only */
  if(huart->Init.OverSampling == UART_OVERSAMPLING_8)
  {
    return HAL_ERROR;
  }
  /* LIN mode limited to 8-bit data length */
  if(huart->Init.WordLength != UART_WORDLENGTH_8B)
  {
    return HAL_ERROR;
  }

  if(huart->gState == HAL_UART_STATE_RESET)
  {
    /* Allocate lock resource and initialize it */
    huart->Lock = HAL_UNLOCKED;

    /* Init the low level hardware : GPIO, CLOCK */
    HAL_UART_MspInit(huart);
  }

  huart->gState = HAL_UART_STATE_BUSY;

  /* Disable the Peripheral */
  __HAL_UART_DISABLE(huart);

  /* Set the UART Communication parameters */
  if (UART_SetConfig(huart) == HAL_ERROR)
  {
    return HAL_ERROR;
  }

  if (huart->AdvancedInit.AdvFeatureInit != UART_ADVFEATURE_NO_INIT)
  {
    UART_AdvFeatureConfig(huart);
  }

  /* In LIN mode, the following bits must be kept cleared:
  - LINEN and CLKEN bits in the USART_CR2 register,
  - SCEN and IREN bits in the USART_CR3 register.*/
  huart->Instance->CR2 &= ~(USART_CR2_CLKEN);
  huart->Instance->CR3 &= ~(USART_CR3_HDSEL | USART_CR3_IREN | USART_CR3_SCEN);

  /* Enable the LIN mode by setting the LINEN bit in the CR2 register */
  huart->Instance->CR2 |= USART_CR2_LINEN;

  /* Set the USART LIN Break detection length. */
  MODIFY_REG(huart->Instance->CR2, USART_CR2_LBDL, BreakDetectLength);

    /* Enable the Peripheral */
  __HAL_UART_ENABLE(huart);

  /* TEACK and/or REACK to check before moving huart->gState and huart->RxState to Ready */
  return (UART_CheckIdleState(huart));
}
#endif /* !defined(STM32F030x6) && !defined(STM32F030x8)&& !defined(STM32F070xB)&& !defined(STM32F070x6)&& !defined(STM32F030xC) */ 

/**
  * @}
  */

/** @defgroup UARTEx_Exported_Functions_Group2 Extended IO operation function 
  * @brief    Extended UART Interrupt handling function 
  *
@verbatim
 ===============================================================================
                      ##### IO operation function #####
 ===============================================================================
    [..]
    This subsection provides function to handle Wake up interrupt call-back.

    (#) Callback provided in No_Blocking mode:
        (++) HAL_UARTEx_WakeupCallback()

@endverbatim
  * @{
  */

#if !defined(STM32F030x6) && !defined(STM32F030x8)&& !defined(STM32F070xB)&& !defined(STM32F070x6)&& !defined(STM32F030xC)
/**
  * @brief  UART wakeup from Stop mode callback
  * @param  huart: UART handle
  * @retval None
  */
 __weak void HAL_UARTEx_WakeupCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_UARTEx_WakeupCallback can be implemented in the user file
   */ 
}
#endif /*!defined(STM32F030x6) && !defined(STM32F030x8)&& !defined(STM32F070xB)&& !defined(STM32F070x6)&& !defined(STM32F030xC)*/ 

/**
  * @}
  */


/** @defgroup UARTEx_Exported_Functions_Group3 Extended Peripheral Control functions
  * @brief    Extended Peripheral Control functions
  *
@verbatim   
 ===============================================================================
                      ##### Peripheral Control function #####
 ===============================================================================  
    [..]
    This subsection provides extended functions allowing to control the UART.         
     (+) HAL_UARTEx_StopModeWakeUpSourceConfig() API sets Wakeup from Stop mode interrupt flag selection
     (+) HAL_UARTEx_EnableStopMode() API allows the UART to wake up the MCU from Stop mode as 
         long as UART clock is HSI or LSE 
     (+) HAL_UARTEx_DisableStopMode() API disables the above feature 
     (+) HAL_MultiProcessorEx_AddressLength_Set() API optionally sets the UART node address
         detection length to more than 4 bits for multiprocessor address mark wake up.
     (+) HAL_LIN_SendBreak() API transmits the break characters 
             
@endverbatim
  * @{
  */

#if !defined(STM32F030x6) && !defined(STM32F030x8)&& !defined(STM32F070xB)&& !defined(STM32F070x6)&& !defined(STM32F030xC)
/**
  * @brief Set Wakeup from Stop mode interrupt flag selection.
  * @param huart: UART handle.
  * @param WakeUpSelection: address match, Start Bit detection or RXNE bit status.
  * This parameter can be one of the following values:
  *      @arg UART_WAKEUP_ON_ADDRESS
  *      @arg UART_WAKEUP_ON_STARTBIT
  *      @arg UART_WAKEUP_ON_READDATA_NONEMPTY
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UARTEx_StopModeWakeUpSourceConfig(UART_HandleTypeDef *huart, UART_WakeUpTypeDef WakeUpSelection)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* check the wake-up from stop mode UART instance */
  assert_param(IS_UART_WAKEUP_FROMSTOP_INSTANCE(huart->Instance));
  /* check the wake-up selection parameter */
  assert_param(IS_UART_WAKEUP_SELECTION(WakeUpSelection.WakeUpEvent));

  /* Process Locked */
  __HAL_LOCK(huart);

  huart->gState = HAL_UART_STATE_BUSY;

  /* Disable the Peripheral */
  __HAL_UART_DISABLE(huart);

  /* Set the wake-up selection scheme */
  MODIFY_REG(huart->Instance->CR3, USART_CR3_WUS, WakeUpSelection.WakeUpEvent);

  if (WakeUpSelection.WakeUpEvent == UART_WAKEUP_ON_ADDRESS)
  {
    UARTEx_Wakeup_AddressConfig(huart, WakeUpSelection);
  }

  /* Enable the Peripheral */
  __HAL_UART_ENABLE(huart);

  /* Wait until REACK flag is set */
  if(UART_WaitOnFlagUntilTimeout(huart, USART_ISR_REACK, RESET, HAL_UART_TIMEOUT_VALUE) != HAL_OK)
  {
    status = HAL_TIMEOUT;
  }
  else
  {
    /* Initialize the UART State */
    huart->gState = HAL_UART_STATE_READY;
  }

  /* Process Unlocked */
  __HAL_UNLOCK(huart);

  return status;
}


/**
  * @brief Enable UART Stop Mode.
  * @note The UART is able to wake up the MCU from Stop 1 mode as long as UART clock is HSI or LSE.
  * @param huart: UART handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UARTEx_EnableStopMode(UART_HandleTypeDef *huart)
{
  /* Check parameter */
  assert_param(IS_UART_WAKEUP_FROMSTOP_INSTANCE(huart->Instance));

  /* Process Locked */
  __HAL_LOCK(huart);

  huart->gState = HAL_UART_STATE_BUSY;

  /* Set UESM bit */
  SET_BIT(huart->Instance->CR1, USART_CR1_UESM);

  huart->gState = HAL_UART_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(huart);

  return HAL_OK;
}

/**
  * @brief Disable UART Stop Mode.
  * @param huart: UART handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_UARTEx_DisableStopMode(UART_HandleTypeDef *huart)
{
  /* Check parameter */
  assert_param(IS_UART_WAKEUP_FROMSTOP_INSTANCE(huart->Instance));

  /* Process Locked */
  __HAL_LOCK(huart);

  huart->gState = HAL_UART_STATE_BUSY;

  /* Clear UESM bit */
  CLEAR_BIT(huart->Instance->CR1, USART_CR1_UESM);

  huart->gState = HAL_UART_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(huart);

  return HAL_OK;
}
#endif /* !defined(STM32F030x6) && !defined(STM32F030x8)&& !defined(STM32F070xB)&& !defined(STM32F070x6)&& !defined(STM32F030xC) */

/**
  * @brief By default in multiprocessor mode, when the wake up method is set
  *        to address mark, the UART handles only 4-bit long addresses detection;
  *        this API allows to enable longer addresses detection (6-, 7- or 8-bit
  *        long).
  * @note  Addresses detection lengths are: 6-bit address detection in 7-bit data mode, 
  *        7-bit address detection in 8-bit data mode, 8-bit address detection in 9-bit data mode.
  * @param huart: UART handle.
  * @param AddressLength: this parameter can be one of the following values:
  *          @arg UART_ADDRESS_DETECT_4B: 4-bit long address
  *          @arg UART_ADDRESS_DETECT_7B: 6-, 7- or 8-bit long address
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_MultiProcessorEx_AddressLength_Set(UART_HandleTypeDef *huart, uint32_t AddressLength)
{
  /* Check the UART handle allocation */
  if(huart == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the address length parameter */
  assert_param(IS_UART_ADDRESSLENGTH_DETECT(AddressLength));

  huart->gState = HAL_UART_STATE_BUSY;

  /* Disable the Peripheral */
  __HAL_UART_DISABLE(huart);

  /* Set the address length */
  MODIFY_REG(huart->Instance->CR2, USART_CR2_ADDM7, AddressLength);

  /* Enable the Peripheral */
  __HAL_UART_ENABLE(huart);

  /* TEACK and/or REACK to check before moving huart->gState to Ready */
  return (UART_CheckIdleState(huart));
}


#if !defined(STM32F030x6) && !defined(STM32F030x8)&& !defined(STM32F070xB)&& !defined(STM32F070x6)&& !defined(STM32F030xC)
/**
  * @brief  Transmit break characters.
  * @param  huart: UART handle.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_LIN_SendBreak(UART_HandleTypeDef *huart)
{
  /* Check the parameters */
  assert_param(IS_UART_LIN_INSTANCE(huart->Instance));

  /* Process Locked */
  __HAL_LOCK(huart);

  huart->gState = HAL_UART_STATE_BUSY;

  /* Send break characters */
  huart->Instance->RQR |= UART_SENDBREAK_REQUEST;

  huart->gState = HAL_UART_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(huart);

  return HAL_OK;
}
#endif /* !defined(STM32F030x6) && !defined(STM32F030x8)&& !defined(STM32F070xB)&& !defined(STM32F070x6)&& !defined(STM32F030xC) */

/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup UARTEx_Private_Functions
  * @{
  */

#if !defined(STM32F030x6) && !defined(STM32F030x8)&& !defined(STM32F070xB)&& !defined(STM32F070x6)&& !defined(STM32F030xC)
/**
  * @brief Initialize the UART wake-up from stop mode parameters when triggered by address detection.
  * @param huart: UART handle.
  * @param WakeUpSelection: UART wake up from stop mode parameters.
  * @retval None
  */
static void UARTEx_Wakeup_AddressConfig(UART_HandleTypeDef *huart, UART_WakeUpTypeDef WakeUpSelection)
{
  /* Check parmeters */
  assert_param(IS_UART_WAKEUP_FROMSTOP_INSTANCE(huart->Instance));
  assert_param(IS_UART_ADDRESSLENGTH_DETECT(WakeUpSelection.AddressLength));

  /* Set the USART address length */
  MODIFY_REG(huart->Instance->CR2, USART_CR2_ADDM7, WakeUpSelection.AddressLength);

  /* Set the USART address node */
  MODIFY_REG(huart->Instance->CR2, USART_CR2_ADD, ((uint32_t)WakeUpSelection.Address << UART_CR2_ADDRESS_LSB_POS));
}
#endif /* !defined(STM32F030x6) && !defined(STM32F030x8)&& !defined(STM32F070xB)&& !defined(STM32F070x6)&& !defined(STM32F030xC) */

/**
  * @}
  */

#endif /* HAL_UART_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
