/**
  ******************************************************************************
  * @file    stm32l0xx_hal_iwdg.c
  * @author  MCD Application Team
  * @version V1.7.0
  * @date    31-May-2016
  * @brief   IWDG HAL module driver.
  *          This file provides firmware functions to manage the following 
  *          functionalities of the Independent Watchdog (IWDG) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral State functions
  *         
  @verbatim
  ==============================================================================
                    ##### IWDG Generic features #####
  ==============================================================================
    [..] 
    (+) The IWDG can be started by either software or hardware (configurable
         through option byte).

    (+) The IWDG is clocked by its own dedicated Low-Speed clock (LSI) and
         thus stays active even if the main clock fails.
         Once the IWDG is started, the LSI is forced ON and cannot be disabled
         (LSI cannot be disabled too), and the counter starts counting down from
         the reset value of 0xFFF. When it reaches the end of count value (0x000)
         a system reset is generated.

    (+) The IWDG counter should be refreshed at regular intervals, otherwise the
         watchdog generates an MCU reset when the counter reaches 0.

    (+) The IWDG is implemented in the VDD voltage domain that is still functional
         in STOP and STANDBY mode (IWDG reset can wake-up from STANDBY).
         IWDGRST flag in RCC_CSR register can be used to inform when an IWDG
         reset occurs.

    [..] Min-max timeout value @32KHz (LSI): ~0.512ms / ~32.0s
         The IWDG timeout may vary due to LSI frequency dispersion. STM32L0xx
         devices provide the capability to measure the LSI frequency (LSI clock
         connected internally to TIM5 CH4 input capture). The measured value
         can be used to have an IWDG timeout with an acceptable accuracy.


                     ##### How to use this driver #####
  ==============================================================================
    [..]
    If Window option is disabled
    
      (+) Use IWDG using HAL_IWDG_Init() function to :
         (++) Enable write access to IWDG_PR, IWDG_RLR.
         (++) Configure the IWDG prescaler, counter reload value.
              This reload value will be loaded in the IWDG counter each time the counter
              is reloaded, then the IWDG will start counting down from this value.
      (+) Use IWDG using HAL_IWDG_Start() function to :
         (++) Reload IWDG counter with value defined in the IWDG_RLR register.
         (++) Start the IWDG, when the IWDG is used in software mode (no need 
              to enable the LSI, it will be enabled by hardware).
      (+) Then the application program must refresh the IWDG counter at regular
          intervals during normal operation to prevent an MCU reset, using
          HAL_IWDG_Refresh() function.
    [..] 
    if Window option is enabled:
      
      (+) Use IWDG using HAL_IWDG_Start() function to enable IWDG downcounter
      (+) Use IWDG using HAL_IWDG_Init() function to :
         (++) Enable write access to IWDG_PR, IWDG_RLR and IWDG_WINR registers.
         (++) Configure the IWDG prescaler, reload value and window value.
      (+) Then the application program must refresh the IWDG counter at regular
          intervals during normal operation to prevent an MCU reset, using
          HAL_IWDG_Refresh() function.

     *** IWDG HAL driver macros list ***
     ====================================
     [..]
       Below the list of most used macros in IWDG HAL driver.
       
      (+) __HAL_IWDG_START: Enable the IWDG peripheral
      (+) __HAL_IWDG_RELOAD_COUNTER: Reloads IWDG counter with value defined in the reload register    
      (+) IWDG_ENABLE_WRITE_ACCESS : Enable write access to IWDG_PR and IWDG_RLR registers
      (+) __HAL_IWDG_DISABLE_WRITE_ACCESS : Disable write access to IWDG_PR and IWDG_RLR registers
      (+) __HAL_IWDG_GET_FLAG: Get the selected IWDG's flag status    
            
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
#include "stm32l0xx_hal.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

#ifdef HAL_IWDG_MODULE_ENABLED

/** @addtogroup IWDG
  * @brief IWDG HAL module driver.
  * @{
  */

/** @addtogroup IWDG_Private
  * @{
  */
/* TimeOut value */
#define HAL_IWDG_DEFAULT_TIMEOUT (uint32_t)1000U

/* Local define used to check the SR status register */
#define IWDG_SR_FLAGS  (IWDG_FLAG_PVU | IWDG_FLAG_RVU | IWDG_FLAG_WVU)
/**
  * @}
  */

/** @addtogroup IWDG_Exported_Functions
  * @{
  */

/** @addtogroup IWDG_Exported_Functions_Group1
 *  @brief    Initialization and Configuration functions.
 *
@verbatim
 ===============================================================================
          ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize the IWDG according to the specified parameters
          in the IWDG_InitTypeDef and create the associated handle
      (+) Manage Window option
      (+) Initialize the IWDG MSP

@endverbatim
  * @{
  */

/**
  * @brief  Initializes the IWDG according to the specified
  *         parameters in the IWDG_InitTypeDef and creates the associated handle.
  *
  *         When using the 'window option', the function HAL_IWDG_Start() must
  *         be called before calling this function
  *
  * @param  hiwdg : pointer to a IWDG_HandleTypeDef structure that contains
  *                 the configuration information for the specified IWDG module.
  * @retval HAL status
  */

HAL_StatusTypeDef HAL_IWDG_Init(IWDG_HandleTypeDef *hiwdg)
{
  uint32_t tickstart = 0U;

  /* Check the IWDG handle allocation */
  if(hiwdg == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_IWDG_PRESCALER(hiwdg->Init.Prescaler));
  assert_param(IS_IWDG_RELOAD(hiwdg->Init.Reload));
  assert_param(IS_IWDG_WINDOW(hiwdg->Init.Window));

  /* Check pending flag, if previous update not done, return error */
  if(((hiwdg->Instance->SR) & IWDG_SR_FLAGS) != 0U)
  {
    return HAL_ERROR;
  }

  if(hiwdg->State == HAL_IWDG_STATE_RESET)
  { 
     /* Allocate lock resource and initialize it */
     hiwdg->Lock = HAL_UNLOCKED;

     /* Init the low level hardware */
     HAL_IWDG_MspInit(hiwdg);
  }

  /* Change IWDG peripheral state */
  hiwdg->State = HAL_IWDG_STATE_BUSY;

  /* Enable write access to IWDG_PR, IWDG_RLR and IWDG_WINR registers */
  /* by writing 0x5555 in KR */
  IWDG_ENABLE_WRITE_ACCESS(hiwdg);

  /* Write to IWDG registers the IWDG_Prescaler & IWDG_Reload values to work with */
  MODIFY_REG(hiwdg->Instance->PR, (uint32_t)IWDG_PR_PR, hiwdg->Init.Prescaler);
  MODIFY_REG(hiwdg->Instance->RLR, (uint32_t)IWDG_RLR_RL, hiwdg->Init.Reload);

  /* check if window option is enabled */
  if (((hiwdg->Init.Window) != IWDG_WINDOW_DISABLE) || ((hiwdg->Instance->WINR) != IWDG_WINDOW_DISABLE))
  {
    tickstart = HAL_GetTick();

     /* Wait for register to be updated */
     while (((hiwdg->Instance->SR) & IWDG_SR_FLAGS) != 0U)
     {
       if((HAL_GetTick()-tickstart) > HAL_IWDG_DEFAULT_TIMEOUT)
       {
         /* Set IWDG state */
         hiwdg->State = HAL_IWDG_STATE_TIMEOUT;
         return HAL_TIMEOUT;
       }
    }

    /* Write to IWDG WINR the IWDG_Window value to compare with */
    MODIFY_REG(hiwdg->Instance->WINR, (uint32_t)IWDG_WINR_WIN, hiwdg->Init.Window);

  }
  /* Change IWDG peripheral state */
  hiwdg->State = HAL_IWDG_STATE_READY;

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Initializes the IWDG MSP.
  * @param  hiwdg: pointer to a IWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified IWDG module.
  * @retval None
  */
__weak void HAL_IWDG_MspInit(IWDG_HandleTypeDef *hiwdg)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hiwdg);

  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_IWDG_MspInit could be implemented in the user file
   */
}

/**
  * @}
  */

/** @addtogroup IWDG_Exported_Functions_Group2
 *  @brief   IO operation functions  
 *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Start the IWDG.
      (+) Refresh the IWDG.

@endverbatim
  * @{
  */

/**
  * @brief  Starts the IWDG.
  * @param  hiwdg : pointer to a IWDG_HandleTypeDef structure that contains
  *                 the configuration information for the specified IWDG module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IWDG_Start(IWDG_HandleTypeDef *hiwdg)
{
  uint32_t tickstart = 0U;

  /* Process locked */
  __HAL_LOCK(hiwdg); 

    /* Change IWDG peripheral state */
  hiwdg->State = HAL_IWDG_STATE_BUSY;

  /* Enable the IWDG peripheral */
  __HAL_IWDG_START(hiwdg);

  /* Reload IWDG counter with value defined in the RLR register */
  if ((hiwdg->Init.Window) == IWDG_WINDOW_DISABLE)
  {
  __HAL_IWDG_RELOAD_COUNTER(hiwdg);
  }

  tickstart = HAL_GetTick();
  
 /* Wait until PVU, RVU, WVU flag are RESET */
  while (((hiwdg->Instance->SR) & IWDG_SR_FLAGS) != 0U)
  {
    if((HAL_GetTick()-tickstart) > HAL_IWDG_DEFAULT_TIMEOUT)
    { 
      /* Set IWDG state */
      hiwdg->State = HAL_IWDG_STATE_TIMEOUT;
      
      /* Process unlocked */
      __HAL_UNLOCK(hiwdg);
      return HAL_TIMEOUT;
    }
  }
  
  /* Change IWDG peripheral state */
  hiwdg->State = HAL_IWDG_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hiwdg);

  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  Refreshes the IWDG.
  * @param  hiwdg : pointer to a IWDG_HandleTypeDef structure that contains
  *                 the configuration information for the specified IWDG module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IWDG_Refresh(IWDG_HandleTypeDef *hiwdg)
{
  uint32_t tickstart = 0U;

  /* Process Locked */
  __HAL_LOCK(hiwdg);

    /* Change IWDG peripheral state */
  hiwdg->State = HAL_IWDG_STATE_BUSY;

  tickstart = HAL_GetTick();

  /* Wait until RVU flag is RESET */
  while(__HAL_IWDG_GET_FLAG(hiwdg, IWDG_FLAG_RVU) != RESET)
  {
    if((HAL_GetTick()-tickstart) > HAL_IWDG_DEFAULT_TIMEOUT)
    { 
      /* Set IWDG state */
      hiwdg->State = HAL_IWDG_STATE_TIMEOUT;

       /* Process unlocked */
      __HAL_UNLOCK(hiwdg);

      return HAL_TIMEOUT;
    }
  }

  /* Reload IWDG counter with value defined in the reload register */
  __HAL_IWDG_RELOAD_COUNTER(hiwdg);

  /* Change IWDG peripheral state */
  hiwdg->State = HAL_IWDG_STATE_READY;

  /* Process Unlocked */
  __HAL_UNLOCK(hiwdg);

  /* Return function status */
  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup IWDG_Exported_Functions_Group3
 *  @brief    Peripheral State functions.
 *
@verbatim
 ===============================================================================
                      ##### Peripheral State functions #####
 ===============================================================================
    [..]
    This subsection permits to get in run-time the status of the peripheral
    and the data flow.

@endverbatim
  * @{
  */

/**
  * @brief  Returns the IWDG state.
  * @param  hiwdg : pointer to a IWDG_HandleTypeDef structure that contains
  *                 the configuration information for the specified IWDG module.
  * @retval HAL state
  */
HAL_IWDG_StateTypeDef HAL_IWDG_GetState(IWDG_HandleTypeDef *hiwdg)
{
  return hiwdg->State;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_IWDG_MODULE_ENABLED */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

