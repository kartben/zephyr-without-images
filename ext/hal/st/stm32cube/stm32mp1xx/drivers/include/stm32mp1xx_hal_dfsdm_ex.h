/**
  ******************************************************************************
  * @file    stm32mp1xx_hal_dfsdm_ex.h
  * @author  MCD Application Team
  * @brief   Header file of DFSDM HAL extended module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32MP1xx_HAL_DFSDM_EX_H
#define STM32MP1xx_HAL_DFSDM_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32mp1xx_hal_def.h"
   
/** @addtogroup STM32MP1xx_HAL_Driver
  * @{
  */

/** @addtogroup DFSDMEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @addtogroup DFSDMEx_Exported_Functions DFSDM Extended Exported Functions
  * @{
  */

/** @addtogroup DFSDMEx_Exported_Functions_Group1_Channel Extended channel operation functions
  * @{
  */

HAL_StatusTypeDef HAL_DFDSMEx_ChannelSetPulsesSkipping(DFSDM_Channel_HandleTypeDef *hdfsdm_channel, uint32_t PulsesValue);
HAL_StatusTypeDef HAL_DFDSMEx_ChannelGetPulsesSkipping(DFSDM_Channel_HandleTypeDef *hdfsdm_channel, uint32_t* PulsesValue);

/**
  * @}
  */ 

/**
  * @}
  */ 

/* Private macros ------------------------------------------------------------*/

/** @addtogroup DFSDMEx_Private_Macros DFSDM Extended Private Macros
  * @{
  */

#define IS_DFSDM_CHANNEL_SKIPPING_VALUE(VALUE)   ((VALUE) < 64U)

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

#endif /* STM32MP1xx_HAL_DFSDM_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
