/**
  ******************************************************************************
  * @file    stm32f4xx_hal_crc.h
  * @author  MCD Application Team
  * @version V1.7.0
  * @date    17-February-2017
  * @brief   Header file of CRC HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
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
#ifndef __STM32F4xx_HAL_CRC_H
#define __STM32F4xx_HAL_CRC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal_def.h"

/** @addtogroup STM32F4xx_HAL_Driver
  * @{
  */

/** @defgroup CRC CRC
  * @brief CRC HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup CRC_Exported_Types CRC Exported Types
  * @{
  */

/** @defgroup CRC_Exported_Types_Group1 CRC State Structure definition 
  * @{
  */
typedef enum
{
  HAL_CRC_STATE_RESET     = 0x00U,  /*!< CRC not yet initialized or disabled */
  HAL_CRC_STATE_READY     = 0x01U,  /*!< CRC initialized and ready for use   */
  HAL_CRC_STATE_BUSY      = 0x02U,  /*!< CRC internal process is ongoing     */
  HAL_CRC_STATE_TIMEOUT   = 0x03U,  /*!< CRC timeout state                   */
  HAL_CRC_STATE_ERROR     = 0x04U   /*!< CRC error state                     */

}HAL_CRC_StateTypeDef;
/** 
  * @}
  */

/** @defgroup CRC_Exported_Types_Group2 CRC Handle Structure definition   
  * @{
  */ 
typedef struct
{
  CRC_TypeDef                 *Instance;  /*!< Register base address   */

  HAL_LockTypeDef             Lock;       /*!< CRC locking object      */

  __IO HAL_CRC_StateTypeDef   State;      /*!< CRC communication state */

}CRC_HandleTypeDef;
/** 
  * @}
  */

/**
  * @}
  */ 

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/** @defgroup CRC_Exported_Macros CRC Exported Macros
  * @{
  */

/** @brief Resets CRC handle state
  * @param  __HANDLE__: CRC handle
  * @retval None
  */
#define __HAL_CRC_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_CRC_STATE_RESET)

/**
  * @brief  Resets CRC Data Register.
  * @param  __HANDLE__: CRC handle
  * @retval None
  */
#define __HAL_CRC_DR_RESET(__HANDLE__) ((__HANDLE__)->Instance->CR |= CRC_CR_RESET)

/**
  * @brief Stores a 8-bit data in the Independent Data(ID) register.
  * @param __HANDLE__: CRC handle
  * @param __VALUE__: 8-bit value to be stored in the ID register
  * @retval None
  */
#define __HAL_CRC_SET_IDR(__HANDLE__, __VALUE__) (WRITE_REG((__HANDLE__)->Instance->IDR, (__VALUE__)))

/**
  * @brief Returns the 8-bit data stored in the Independent Data(ID) register.
  * @param __HANDLE__: CRC handle
  * @retval 8-bit value of the ID register 
  */
#define __HAL_CRC_GET_IDR(__HANDLE__) (((__HANDLE__)->Instance->IDR) & CRC_IDR_IDR)
/**
  * @}
  */ 

/* Exported functions --------------------------------------------------------*/
/** @defgroup CRC_Exported_Functions CRC Exported Functions
  * @{
  */

/** @defgroup CRC_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
HAL_StatusTypeDef HAL_CRC_Init(CRC_HandleTypeDef *hcrc);
HAL_StatusTypeDef HAL_CRC_DeInit (CRC_HandleTypeDef *hcrc);
void HAL_CRC_MspInit(CRC_HandleTypeDef *hcrc);
void HAL_CRC_MspDeInit(CRC_HandleTypeDef *hcrc);
/**
  * @}
  */ 

/** @defgroup CRC_Exported_Functions_Group2 Peripheral Control functions
  * @{
  */
uint32_t HAL_CRC_Accumulate(CRC_HandleTypeDef *hcrc, uint32_t pBuffer[], uint32_t BufferLength);
uint32_t HAL_CRC_Calculate(CRC_HandleTypeDef *hcrc, uint32_t pBuffer[], uint32_t BufferLength);
/**
  * @}
  */ 

/** @defgroup CRC_Exported_Functions_Group3 Peripheral State functions
  * @{
  */
HAL_CRC_StateTypeDef HAL_CRC_GetState(CRC_HandleTypeDef *hcrc);
/**
  * @}
  */ 

/**
  * @}
  */
/* Private types -------------------------------------------------------------*/
/** @defgroup CRC_Private_Types CRC Private Types
  * @{
  */

/**
  * @}
  */ 

/* Private defines -----------------------------------------------------------*/
/** @defgroup CRC_Private_Defines CRC Private Defines
  * @{
  */

/**
  * @}
  */ 
          
/* Private variables ---------------------------------------------------------*/
/** @defgroup CRC_Private_Variables CRC Private Variables
  * @{
  */

/**
  * @}
  */ 

/* Private constants ---------------------------------------------------------*/
/** @defgroup CRC_Private_Constants CRC Private Constants
  * @{
  */

/**
  * @}
  */ 

/* Private macros ------------------------------------------------------------*/
/** @defgroup CRC_Private_Macros CRC Private Macros
  * @{
  */

/**
  * @}
  */

/* Private functions prototypes ----------------------------------------------*/
/** @defgroup CRC_Private_Functions_Prototypes CRC Private Functions Prototypes
  * @{
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup CRC_Private_Functions CRC Private Functions
  * @{
  */

/**
  * @}
  */

/**
  * @}
  */ 

/**
  * @}
  */ 

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_HAL_CRC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
