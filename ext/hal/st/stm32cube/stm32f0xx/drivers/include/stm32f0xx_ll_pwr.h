/**
  ******************************************************************************
  * @file    stm32f0xx_ll_pwr.h
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    27-May-2016
  * @brief   Header file of PWR LL module.
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
#ifndef __STM32F0xx_LL_PWR_H
#define __STM32F0xx_LL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"

/** @addtogroup STM32F0xx_LL_Driver
  * @{
  */

#if defined(PWR)

/** @defgroup PWR_LL PWR
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWR_LL_EC_CLEAR_FLAG Clear Flags Defines
  * @brief    Flags defines which can be used with LL_PWR_WriteReg function
  * @{
  */
#define LL_PWR_CR_CSBF                     PWR_CR_CSBF            /*!< Clear standby flag */
#define LL_PWR_CR_CWUF                     PWR_CR_CWUF            /*!< Clear wakeup flag */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_PWR_ReadReg function
  * @{
  */
#define LL_PWR_CSR_WUF                     PWR_CSR_WUF            /*!< Wakeup flag */
#define LL_PWR_CSR_SBF                     PWR_CSR_SBF            /*!< Standby flag */
#if defined (PWR_PVD_SUPPORT)
#define LL_PWR_CSR_PVDO                    PWR_CSR_PVDO           /*!< Power voltage detector output flag */
#endif
#if defined (PWR_CSR_VREFINTRDYF)
#define LL_PWR_CSR_VREFINTRDYF             PWR_CSR_VREFINTRDYF    /*!< VREFINT ready flag */
#endif
#define LL_PWR_CSR_EWUP1                   PWR_CSR_EWUP1          /*!< Enable WKUP pin 1 */
#define LL_PWR_CSR_EWUP2                   PWR_CSR_EWUP2          /*!< Enable WKUP pin 2 */
#if defined (PWR_CSR_EWUP3)
#define LL_PWR_CSR_EWUP3                   PWR_CSR_EWUP3          /*!< Enable WKUP pin 3 */
#endif /* PWR_CSR_EWUP3 */
#if defined (PWR_CSR_EWUP4)
#define LL_PWR_CSR_EWUP4                   PWR_CSR_EWUP4          /*!< Enable WKUP pin 4 */
#endif /* PWR_CSR_EWUP4 */
#if defined (PWR_CSR_EWUP5)
#define LL_PWR_CSR_EWUP5                   PWR_CSR_EWUP5          /*!< Enable WKUP pin 5 */
#endif /* PWR_CSR_EWUP5 */
#if defined (PWR_CSR_EWUP6)
#define LL_PWR_CSR_EWUP6                   PWR_CSR_EWUP6          /*!< Enable WKUP pin 6 */
#endif /* PWR_CSR_EWUP6 */
#if defined (PWR_CSR_EWUP7)
#define LL_PWR_CSR_EWUP7                   PWR_CSR_EWUP7          /*!< Enable WKUP pin 7 */
#endif /* PWR_CSR_EWUP7 */
#if defined (PWR_CSR_EWUP8)
#define LL_PWR_CSR_EWUP8                   PWR_CSR_EWUP8          /*!< Enable WKUP pin 8 */
#endif /* PWR_CSR_EWUP8 */
/**
  * @}
  */


/** @defgroup PWR_LL_EC_MODE_PWR Mode Power
  * @{
  */
#define LL_PWR_MODE_STOP_MAINREGU          ((uint32_t)0x00000000U)        /*!< Enter Stop mode when the CPU enters deepsleep */
#define LL_PWR_MODE_STOP_LPREGU            (PWR_CR_LPDS)                  /*!< Enter Stop mode (ith low power regulator ON) when the CPU enters deepsleep */
#define LL_PWR_MODE_STANDBY                (PWR_CR_PDDS)                  /*!< Enter Standby mode when the CPU enters deepsleep */
/**
  * @}
  */

#if defined(PWR_CR_LPDS)
/** @defgroup PWR_LL_EC_REGU_MODE_DS_MODE  Regulator Mode In Deep Sleep Mode
 * @{
 */
#define LL_PWR_REGU_DSMODE_MAIN       ((uint32_t)0x00000000U)        /*!< Voltage regulator in main mode during deepsleep mode */
#define LL_PWR_REGU_DSMODE_LOW_POWER  (PWR_CR_LPDS)                  /*!< Voltage regulator in low-power mode during deepsleep mode */
/**
 * @}
 */
#endif /* PWR_CR_LPDS */

#if defined (PWR_PVD_SUPPORT)
/** @defgroup PWR_LL_EC_PVDLEVEL Power Voltage Detector Level
  * @{
  */
#define LL_PWR_PVDLEVEL_0                  (PWR_CR_PLS_LEV0)      /*!< Voltage threshold 0 */
#define LL_PWR_PVDLEVEL_1                  (PWR_CR_PLS_LEV1)      /*!< Voltage threshold 1 */
#define LL_PWR_PVDLEVEL_2                  (PWR_CR_PLS_LEV2)      /*!< Voltage threshold 2 */
#define LL_PWR_PVDLEVEL_3                  (PWR_CR_PLS_LEV3)      /*!< Voltage threshold 3 */
#define LL_PWR_PVDLEVEL_4                  (PWR_CR_PLS_LEV4)      /*!< Voltage threshold 4 */
#define LL_PWR_PVDLEVEL_5                  (PWR_CR_PLS_LEV5)      /*!< Voltage threshold 5 */
#define LL_PWR_PVDLEVEL_6                  (PWR_CR_PLS_LEV6)      /*!< Voltage threshold 6 */
#define LL_PWR_PVDLEVEL_7                  (PWR_CR_PLS_LEV7)      /*!< Voltage threshold 7 */
/**
  * @}
  */
#endif

/** @defgroup PWR_LL_EC_WAKEUP_PIN  Wakeup Pins
* @{
*/
#define LL_PWR_WAKEUP_PIN1                 (PWR_CSR_EWUP1)        /*!< WKUP pin 1 : PA0 */
#define LL_PWR_WAKEUP_PIN2                 (PWR_CSR_EWUP2)        /*!< WKUP pin 2 : PC13 */
#if defined (PWR_CSR_EWUP3)
#define LL_PWR_WAKEUP_PIN3                 (PWR_CSR_EWUP3)        /*!< WKUP pin 3 : PE6 or PA2 according to device */
#endif /* PWR_CSR_EWUP3 */
#if defined (PWR_CSR_EWUP4)
#define LL_PWR_WAKEUP_PIN4                 (PWR_CSR_EWUP4)        /*!< WKUP pin 4 : LLG TBD */
#endif /* PWR_CSR_EWUP4 */
#if defined (PWR_CSR_EWUP5)
#define LL_PWR_WAKEUP_PIN5                 (PWR_CSR_EWUP5)        /*!< WKUP pin 5 : LLG TBD */
#endif /* PWR_CSR_EWUP5 */
#if defined (PWR_CSR_EWUP6)
#define LL_PWR_WAKEUP_PIN6                 (PWR_CSR_EWUP6)        /*!< WKUP pin 6 : LLG TBD */
#endif /* PWR_CSR_EWUP6 */
#if defined (PWR_CSR_EWUP7)
#define LL_PWR_WAKEUP_PIN7                 (PWR_CSR_EWUP7)        /*!< WKUP pin 7 : LLG TBD */
#endif /* PWR_CSR_EWUP7 */
#if defined (PWR_CSR_EWUP8)
#define LL_PWR_WAKEUP_PIN8                 (PWR_CSR_EWUP8)        /*!< WKUP pin 8 : LLG TBD */
#endif /* PWR_CSR_EWUP8 */
/**
  * @}
  */

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Macros PWR Exported Macros
  * @{
  */

/** @defgroup PWR_LL_EM_WRITE_READ Common write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in PWR register
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_PWR_WriteReg(__REG__, __VALUE__) WRITE_REG(PWR->__REG__, (__VALUE__))

/**
  * @brief  Read a value in PWR register
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_PWR_ReadReg(__REG__) READ_REG(PWR->__REG__)
/**
  * @}
  */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Functions PWR Exported Functions
  * @{
  */

/** @defgroup PWR_LL_EF_Configuration Configuration
  * @{
  */


/**
  * @brief  Enable access to the backup domain
  * @rmtoll CR    DBP       LL_PWR_EnableBkUpAccess
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableBkUpAccess(void)
{
  SET_BIT(PWR->CR, PWR_CR_DBP);
}

/**
  * @brief  Disable access to the backup domain
  * @rmtoll CR    DBP       LL_PWR_DisableBkUpAccess
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableBkUpAccess(void)
{
  CLEAR_BIT(PWR->CR, PWR_CR_DBP);
}

/**
  * @brief  Check if the backup domain is enabled
  * @rmtoll CR    DBP       LL_PWR_IsEnabledBkUpAccess
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBkUpAccess(void)
{
  return (READ_BIT(PWR->CR, PWR_CR_DBP) == (PWR_CR_DBP));
}

#if defined(PWR_CR_LPDS)
/**
  * @brief  Set voltage regulator mode during deep sleep mode
  * @rmtoll CR    LPDS         LL_PWR_SetRegulModeDS
  * @param  RegulMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_REGU_DSMODE_MAIN
  *         @arg @ref LL_PWR_REGU_DSMODE_LOW_POWER
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetRegulModeDS(uint32_t RegulMode)
{
  MODIFY_REG(PWR->CR, PWR_CR_LPDS, RegulMode);
}

/**
  * @brief  Get voltage regulator mode during deep sleep mode
  * @rmtoll CR    LPDS         LL_PWR_GetRegulModeDS
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_REGU_DSMODE_MAIN
  *         @arg @ref LL_PWR_REGU_DSMODE_LOW_POWER
  */
__STATIC_INLINE uint32_t LL_PWR_GetRegulModeDS(void)
{
  return (uint32_t)(READ_BIT(PWR->CR, PWR_CR_LPDS));
}
#endif /* PWR_CR_LPDS */

/**
  * @brief  Set power down mode when CPU enters deepsleep
  * @rmtoll CR    PDDS         LL_PWR_SetPowerMode\n
  *         CR    LPDS         LL_PWR_SetPowerMode
  * @param  PDMode This parameter can be one of the following values:
  *         @arg @ref LL_PWR_MODE_STOP_MAINREGU
  *         @arg @ref LL_PWR_MODE_STOP_LPREGU
  *         @arg @ref LL_PWR_MODE_STANDBY
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPowerMode(uint32_t PDMode)
{
  MODIFY_REG(PWR->CR, (PWR_CR_PDDS| PWR_CR_LPDS), PDMode);
}

/**
  * @brief  Get power down mode when CPU enters deepsleep
  * @rmtoll CR    PDDS         LL_PWR_GetPowerMode
  *         CR    LPDS         LL_PWR_SetPowerMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_MODE_STOP_MAINREGU
  *         @arg @ref LL_PWR_MODE_STOP_LPREGU
  *         @arg @ref LL_PWR_MODE_STANDBY
  */
__STATIC_INLINE uint32_t LL_PWR_GetPowerMode(void)
{
  return (uint32_t)(READ_BIT(PWR->CR, (PWR_CR_PDDS| PWR_CR_LPDS)));
}

#if defined (PWR_PVD_SUPPORT)
/**
  * @brief  Configure the voltage threshold detected by the Power Voltage Detector
  * @rmtoll CR    PLS       LL_PWR_SetPVDLevel
  * @param  PVDLevel This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PVDLEVEL_0
  *         @arg @ref LL_PWR_PVDLEVEL_1
  *         @arg @ref LL_PWR_PVDLEVEL_2
  *         @arg @ref LL_PWR_PVDLEVEL_3
  *         @arg @ref LL_PWR_PVDLEVEL_4
  *         @arg @ref LL_PWR_PVDLEVEL_5
  *         @arg @ref LL_PWR_PVDLEVEL_6
  *         @arg @ref LL_PWR_PVDLEVEL_7
  * @retval None
  */
__STATIC_INLINE void LL_PWR_SetPVDLevel(uint32_t PVDLevel)
{
  MODIFY_REG(PWR->CR, PWR_CR_PLS, PVDLevel);
}

/**
  * @brief  Get the voltage threshold detection
  * @rmtoll CR    PLS       LL_PWR_GetPVDLevel
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_PVDLEVEL_0
  *         @arg @ref LL_PWR_PVDLEVEL_1
  *         @arg @ref LL_PWR_PVDLEVEL_2
  *         @arg @ref LL_PWR_PVDLEVEL_3
  *         @arg @ref LL_PWR_PVDLEVEL_4
  *         @arg @ref LL_PWR_PVDLEVEL_5
  *         @arg @ref LL_PWR_PVDLEVEL_6
  *         @arg @ref LL_PWR_PVDLEVEL_7
  */
__STATIC_INLINE uint32_t LL_PWR_GetPVDLevel(void)
{
  return (uint32_t)(READ_BIT(PWR->CR, PWR_CR_PLS));
}

/**
  * @brief  Enable Power Voltage Detector
  * @rmtoll CR    PVDE       LL_PWR_EnablePVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnablePVD(void)
{
  SET_BIT(PWR->CR, PWR_CR_PVDE);
}

/**
  * @brief  Disable Power Voltage Detector
  * @rmtoll CR    PVDE       LL_PWR_DisablePVD
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisablePVD(void)
{
  CLEAR_BIT(PWR->CR, PWR_CR_PVDE);
}

/**
  * @brief  Check if Power Voltage Detector is enabled
  * @rmtoll CR    PVDE       LL_PWR_IsEnabledPVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPVD(void)
{
  return (READ_BIT(PWR->CR, PWR_CR_PVDE) == (PWR_CR_PVDE));
}
#endif

/**
  * @brief  Enable the WakeUp PINx functionality
  * @rmtoll CSR   EWUP1       LL_PWR_EnableWakeUpPin\n
  *         CSR   EWUP2       LL_PWR_EnableWakeUpPin\n
  *         CSR   EWUP3       LL_PWR_EnableWakeUpPin
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3 (*)
  *         @arg @ref LL_PWR_WAKEUP_PIN4 (*)
  *         @arg @ref LL_PWR_WAKEUP_PIN5 (*)
  *         @arg @ref LL_PWR_WAKEUP_PIN6 (*)
  *         @arg @ref LL_PWR_WAKEUP_PIN7 (*)
  *         @arg @ref LL_PWR_WAKEUP_PIN8 (*)
  *
  *         (*) not available on all devices
  * @retval None
  */
__STATIC_INLINE void LL_PWR_EnableWakeUpPin(uint32_t WakeUpPin)
{
  SET_BIT(PWR->CSR, WakeUpPin);
}

/**
  * @brief  Disable the WakeUp PINx functionality
  * @rmtoll CSR   EWUP1       LL_PWR_DisableWakeUpPin\n
  *         CSR   EWUP2       LL_PWR_DisableWakeUpPin\n
  *         CSR   EWUP3       LL_PWR_DisableWakeUpPin
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3 (*)
  *         @arg @ref LL_PWR_WAKEUP_PIN4 (*)
  *         @arg @ref LL_PWR_WAKEUP_PIN5 (*)
  *         @arg @ref LL_PWR_WAKEUP_PIN6 (*)
  *         @arg @ref LL_PWR_WAKEUP_PIN7 (*)
  *         @arg @ref LL_PWR_WAKEUP_PIN8 (*)
  *
  *         (*) not available on all devices
  * @retval None
  */
__STATIC_INLINE void LL_PWR_DisableWakeUpPin(uint32_t WakeUpPin)
{
  CLEAR_BIT(PWR->CSR, WakeUpPin);
}

/**
  * @brief  Check if the WakeUp PINx functionality is enabled
  * @rmtoll CSR   EWUP1       LL_PWR_IsEnabledWakeUpPin\n
  *         CSR   EWUP2       LL_PWR_IsEnabledWakeUpPin\n
  *         CSR   EWUP3       LL_PWR_IsEnabledWakeUpPin
  * @param  WakeUpPin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN1
  *         @arg @ref LL_PWR_WAKEUP_PIN2
  *         @arg @ref LL_PWR_WAKEUP_PIN3 (*)
  *         @arg @ref LL_PWR_WAKEUP_PIN4 (*)
  *         @arg @ref LL_PWR_WAKEUP_PIN5 (*)
  *         @arg @ref LL_PWR_WAKEUP_PIN6 (*)
  *         @arg @ref LL_PWR_WAKEUP_PIN7 (*)
  *         @arg @ref LL_PWR_WAKEUP_PIN8 (*)
  *
  *         (*) not available on all devices
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledWakeUpPin(uint32_t WakeUpPin)
{
  return (READ_BIT(PWR->CSR, WakeUpPin) == (WakeUpPin));
}

/**
  * @}
  */

/** @defgroup PWR_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Get Wake-up Flag
  * @rmtoll CSR   WUF       LL_PWR_IsActiveFlag_WU
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU(void)
{
  return (READ_BIT(PWR->CSR, PWR_CSR_WUF) == (PWR_CSR_WUF));
}

/**
  * @brief  Get Standby Flag
  * @rmtoll CSR   SBF       LL_PWR_IsActiveFlag_SB
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_SB(void)
{
  return (READ_BIT(PWR->CSR, PWR_CSR_SBF) == (PWR_CSR_SBF));
}

#if defined (PWR_PVD_SUPPORT)
/**
  * @brief  Indicate whether VDD voltage is below the selected PVD threshold
  * @rmtoll CSR   PVDO       LL_PWR_IsActiveFlag_PVDO
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_PVDO(void)
{
  return (READ_BIT(PWR->CSR, PWR_CSR_PVDO) == (PWR_CSR_PVDO));
}
#endif

#if defined (PWR_CSR_VREFINTRDYF)
/**
  * @brief  Get Internal Reference VrefInt Flag
  * @rmtoll CSR   VREFINTRDYF       LL_PWR_IsActiveFlag_VREFINTRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VREFINTRDY(void)
{
  return (READ_BIT(PWR->CSR, PWR_CSR_VREFINTRDYF) == (PWR_CSR_VREFINTRDYF));
}
#endif



/**
  * @brief  Clear Standby Flag
  * @rmtoll CR   CSBF       LL_PWR_ClearFlag_SB
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_SB(void)
{
  SET_BIT(PWR->CR, PWR_CR_CSBF);
}

/**
  * @brief  Clear Wake-up Flags
  * @rmtoll CR   CWUF       LL_PWR_ClearFlag_WU
  * @retval None
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU(void)
{
  SET_BIT(PWR->CR, PWR_CR_CWUF);
}


#if defined(USE_FULL_LL_DRIVER)
/** @defgroup PWR_LL_EF_Init De-initialization function
  * @{
  */
ErrorStatus LL_PWR_DeInit(void);
/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(PWR) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F0xx_LL_PWR_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
