/**
  ******************************************************************************
  * @file    stm32l0xx_hal_rtc.h
  * @author  MCD Application Team
  * @brief   Header file of RTC HAL module.
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
#ifndef __STM32L0xx_HAL_RTC_H
#define __STM32L0xx_HAL_RTC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup RTC RTC
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup RTC_Exported_Types RTC Exported Types
  * @{
  */

/**
  * @brief  HAL State structures definition
  */
typedef enum
{
  HAL_RTC_STATE_RESET             = 0x00U,  /*!< RTC not yet initialized or disabled */
  HAL_RTC_STATE_READY             = 0x01U,  /*!< RTC initialized and ready for use   */
  HAL_RTC_STATE_BUSY              = 0x02U,  /*!< RTC process is ongoing              */
  HAL_RTC_STATE_TIMEOUT           = 0x03U,  /*!< RTC timeout state                   */
  HAL_RTC_STATE_ERROR             = 0x04U   /*!< RTC error state                     */

}HAL_RTCStateTypeDef;

/**
  * @brief  RTC Configuration Structure definition
  */
typedef struct
{
  uint32_t HourFormat;      /*!< Specifies the RTC Hour Format.
                                 This parameter can be a value of @ref RTC_Hour_Formats */

  uint32_t AsynchPrediv;    /*!< Specifies the RTC Asynchronous Predivider value.
                                 This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x7F */

  uint32_t SynchPrediv;     /*!< Specifies the RTC Synchronous Predivider value.
                                 This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x7FFF */

  uint32_t OutPut;          /*!< Specifies which signal will be routed to the RTC output.
                                 This parameter can be a value of @ref RTCEx_Output_selection_Definitions */

  uint32_t OutPutRemap;    /*!< Specifies the remap for RTC output.
                                 This parameter can be a value of @ref  RTC_Output_ALARM_OUT_Remap */

  uint32_t OutPutPolarity;  /*!< Specifies the polarity of the output signal.
                                 This parameter can be a value of @ref RTC_Output_Polarity_Definitions */

  uint32_t OutPutType;      /*!< Specifies the RTC Output Pin mode.
                                 This parameter can be a value of @ref RTC_Output_Type_ALARM_OUT */
}RTC_InitTypeDef;

/**
  * @brief  RTC Time structure definition
  */
typedef struct
{
  uint8_t Hours;            /*!< Specifies the RTC Time Hour.
                                 This parameter must be a number between Min_Data = 0 and Max_Data = 12 if the RTC_HourFormat_12 is selected.
                                 This parameter must be a number between Min_Data = 0 and Max_Data = 23 if the RTC_HourFormat_24 is selected */

  uint8_t Minutes;          /*!< Specifies the RTC Time Minutes.
                                 This parameter must be a number between Min_Data = 0 and Max_Data = 59 */

  uint8_t Seconds;          /*!< Specifies the RTC Time Seconds.
                                 This parameter must be a number between Min_Data = 0 and Max_Data = 59 */

  uint8_t TimeFormat;       /*!< Specifies the RTC AM/PM Time.
                                 This parameter can be a value of @ref RTC_AM_PM_Definitions */

  uint32_t SubSeconds;     /*!< Specifies the RTC_SSR RTC Sub Second register content.
                                 This parameter corresponds to a time unit range between [0-1] Second
                                 with [1 Sec / SecondFraction +1] granularity */

  uint32_t SecondFraction;  /*!< Specifies the range or granularity of Sub Second register content
                                 corresponding to Synchronous pre-scaler factor value (PREDIV_S)
                                 This parameter corresponds to a time unit range between [0-1] Second
                                 with [1 Sec / SecondFraction +1] granularity.
                                 This field will be used only by HAL_RTC_GetTime function */

  uint32_t DayLightSaving;  /*!< Specifies RTC_DayLightSaveOperation: the value of hour adjustment.
                                 This parameter can be a value of @ref RTC_DayLightSaving_Definitions */

  uint32_t StoreOperation;  /*!< Specifies RTC_StoreOperation value to be written in the BCK bit
                                 in CR register to store the operation.
                                 This parameter can be a value of @ref RTC_StoreOperation_Definitions */
}RTC_TimeTypeDef;

/**
  * @brief  RTC Date structure definition
  */
typedef struct
{
  uint8_t WeekDay;  /*!< Specifies the RTC Date WeekDay.
                         This parameter can be a value of @ref RTC_WeekDay_Definitions */

  uint8_t Month;    /*!< Specifies the RTC Date Month (in BCD format).
                         This parameter can be a value of @ref RTC_Month_Date_Definitions */

  uint8_t Date;     /*!< Specifies the RTC Date.
                         This parameter must be a number between Min_Data = 1 and Max_Data = 31 */

  uint8_t Year;     /*!< Specifies the RTC Date Year.
                         This parameter must be a number between Min_Data = 0 and Max_Data = 99 */

}RTC_DateTypeDef;

/**
  * @brief  RTC Alarm structure definition
  */
typedef struct
{
  RTC_TimeTypeDef AlarmTime;     /*!< Specifies the RTC Alarm Time members */

  uint32_t AlarmMask;            /*!< Specifies the RTC Alarm Masks.
                                      This parameter can be a value of @ref RTC_AlarmMask_Definitions */

  uint32_t AlarmSubSecondMask;   /*!< Specifies the RTC Alarm SubSeconds Masks.
                                      This parameter can be a value of @ref RTC_Alarm_Sub_Seconds_Masks_Definitions */

  uint32_t AlarmDateWeekDaySel;  /*!< Specifies the RTC Alarm is on Date or WeekDay.
                                     This parameter can be a value of @ref RTC_AlarmDateWeekDay_Definitions */

  uint8_t AlarmDateWeekDay;      /*!< Specifies the RTC Alarm Date/WeekDay.
                                      If the Alarm Date is selected, this parameter must be set to a value in the 1-31 range.
                                      If the Alarm WeekDay is selected, this parameter can be a value of @ref RTC_WeekDay_Definitions */

  uint32_t Alarm;                /*!< Specifies the alarm .
                                      This parameter can be a value of @ref RTC_Alarms_Definitions */
}RTC_AlarmTypeDef;

/**
  * @brief  RTC Handle Structure definition
  */
typedef struct
{
  RTC_TypeDef               *Instance;  /*!< Register base address    */

  RTC_InitTypeDef           Init;       /*!< RTC required parameters  */

  HAL_LockTypeDef           Lock;       /*!< RTC locking object       */

  __IO HAL_RTCStateTypeDef  State;      /*!< Time communication state */

}RTC_HandleTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RTC_Exported_Constants RTC Exported Constants
  * @{
  */

/** @defgroup RTC_Hour_Formats RTC Hour Formats
  * @{
  */
#define RTC_HOURFORMAT_24              ((uint32_t)0x00000000U)
#define RTC_HOURFORMAT_12              ((uint32_t)RTC_CR_FMT)

/**
  * @}
  */


/** @defgroup RTC_Output_Polarity_Definitions RTC Output Polarity Definitions
  * @{
  */
#define RTC_OUTPUT_POLARITY_HIGH       ((uint32_t)0x00000000U)
#define RTC_OUTPUT_POLARITY_LOW        ((uint32_t)RTC_CR_POL)

/**
  * @}
  */

/** @defgroup RTC_Output_Type_ALARM_OUT RTC Output Type ALARM OUT
  * @{
  */
#define RTC_OUTPUT_TYPE_OPENDRAIN      ((uint32_t)0x00000000U)
#define RTC_OUTPUT_TYPE_PUSHPULL       ((uint32_t)RTC_OR_ALARMOUTTYPE)

/**
  * @}
  */

/** @defgroup RTC_Output_ALARM_OUT_Remap RTC Output ALARM OUT Remap
  * @{
  */
#define RTC_OUTPUT_REMAP_NONE              ((uint32_t)0x00000000U)
#define RTC_OUTPUT_REMAP_POS1               ((uint32_t)RTC_OR_OUT_RMP)
/**
  * @}
  */

/** @defgroup RTC_AM_PM_Definitions RTC AM PM Definitions
  * @{
  */
#define RTC_HOURFORMAT12_AM            ((uint8_t)0x00U)
#define RTC_HOURFORMAT12_PM            ((uint8_t)0x40U)

/**
  * @}
  */

/** @defgroup RTC_DayLightSaving_Definitions RTC DayLightSaving Definitions
  * @{
  */
#define RTC_DAYLIGHTSAVING_SUB1H       ((uint32_t)RTC_CR_SUB1H)
#define RTC_DAYLIGHTSAVING_ADD1H       ((uint32_t)RTC_CR_ADD1H)
#define RTC_DAYLIGHTSAVING_NONE        ((uint32_t)0x00000000U)

/**
  * @}
  */

/** @defgroup RTC_StoreOperation_Definitions RTC StoreOperation Definitions
  * @{
  */
#define RTC_STOREOPERATION_RESET        ((uint32_t)0x00000000U)
#define RTC_STOREOPERATION_SET          ((uint32_t)RTC_CR_BCK)

/**
  * @}
  */

/** @defgroup RTC_Input_parameter_format_definitions RTC Input Parameter Format Definitions
  * @{
  */
#define RTC_FORMAT_BIN   ((uint32_t)0x000000000U)
#define RTC_FORMAT_BCD   ((uint32_t)0x000000001U)

/**
  * @}
  */

/** @defgroup RTC_Month_Date_Definitions RTC Month Date Definitions
  * @{
  */

/* Coded in BCD format */
#define RTC_MONTH_JANUARY              ((uint8_t)0x01U)
#define RTC_MONTH_FEBRUARY             ((uint8_t)0x02U)
#define RTC_MONTH_MARCH                ((uint8_t)0x03U)
#define RTC_MONTH_APRIL                ((uint8_t)0x04U)
#define RTC_MONTH_MAY                  ((uint8_t)0x05U)
#define RTC_MONTH_JUNE                 ((uint8_t)0x06U)
#define RTC_MONTH_JULY                 ((uint8_t)0x07U)
#define RTC_MONTH_AUGUST               ((uint8_t)0x08U)
#define RTC_MONTH_SEPTEMBER            ((uint8_t)0x09U)
#define RTC_MONTH_OCTOBER              ((uint8_t)0x10U)
#define RTC_MONTH_NOVEMBER             ((uint8_t)0x11U)
#define RTC_MONTH_DECEMBER             ((uint8_t)0x12U)

/**
  * @}
  */

/** @defgroup RTC_WeekDay_Definitions RTC WeekDay Definitions
  * @{
  */
#define RTC_WEEKDAY_MONDAY             ((uint8_t)0x01U)
#define RTC_WEEKDAY_TUESDAY            ((uint8_t)0x02U)
#define RTC_WEEKDAY_WEDNESDAY          ((uint8_t)0x03U)
#define RTC_WEEKDAY_THURSDAY           ((uint8_t)0x04U)
#define RTC_WEEKDAY_FRIDAY             ((uint8_t)0x05U)
#define RTC_WEEKDAY_SATURDAY           ((uint8_t)0x06U)
#define RTC_WEEKDAY_SUNDAY             ((uint8_t)0x07U)

/**
  * @}
  */

/** @defgroup RTC_AlarmDateWeekDay_Definitions RTC AlarmDateWeekDay Definitions
  * @{
  */
#define RTC_ALARMDATEWEEKDAYSEL_DATE      ((uint32_t)0x00000000U)
#define RTC_ALARMDATEWEEKDAYSEL_WEEKDAY   RTC_ALRMAR_WDSEL

/**
  * @}
  */

/** @defgroup RTC_AlarmMask_Definitions RTC AlarmMask Definitions
  * @{
  */
#define RTC_ALARMMASK_NONE             ((uint32_t)0x00000000U)
#define RTC_ALARMMASK_DATEWEEKDAY       RTC_ALRMAR_MSK4
#define RTC_ALARMMASK_HOURS             RTC_ALRMAR_MSK3
#define RTC_ALARMMASK_MINUTES           RTC_ALRMAR_MSK2
#define RTC_ALARMMASK_SECONDS           RTC_ALRMAR_MSK1
#define RTC_ALARMMASK_ALL               ((uint32_t) (RTC_ALARMMASK_NONE        | \
                                                     RTC_ALARMMASK_DATEWEEKDAY | \
                                                     RTC_ALARMMASK_HOURS       | \
                                                     RTC_ALARMMASK_MINUTES     | \
                                                     RTC_ALARMMASK_SECONDS))

/**
  * @}
  */

/** @defgroup RTC_Alarms_Definitions RTC Alarms Definitions
  * @{
  */
#define RTC_ALARM_A                       RTC_CR_ALRAE
#define RTC_ALARM_B                       RTC_CR_ALRBE

/**
  * @}
  */


  /** @defgroup RTC_Alarm_Sub_Seconds_Masks_Definitions RTC Alarm Sub Seconds Masks Definitions
  * @{
  */
#define RTC_ALARMSUBSECONDMASK_ALL        ((uint32_t)0x00000000U)                                                                 /*!< All Alarm SS fields are masked.
                                                                                                                                    There is no comparison on sub seconds
                                                                                                                                    for Alarm */
#define RTC_ALARMSUBSECONDMASK_SS14_1      RTC_ALRMASSR_MASKSS_0                                                                 /*!< SS[14:1] are don't care in Alarm
                                                                                                                                    comparison. Only SS[0] is compared.    */
#define RTC_ALARMSUBSECONDMASK_SS14_2      RTC_ALRMASSR_MASKSS_1                                                                 /*!< SS[14:2] are don't care in Alarm
                                                                                                                                     comparison. Only SS[1:0] are compared  */
#define RTC_ALARMSUBSECONDMASK_SS14_3      ((uint32_t) (RTC_ALRMASSR_MASKSS_0 | RTC_ALRMASSR_MASKSS_1))                          /*!< SS[14:3] are don't care in Alarm
                                                                                                                                     comparison. Only SS[2:0] are compared  */
#define RTC_ALARMSUBSECONDMASK_SS14_4      RTC_ALRMASSR_MASKSS_2                                                                 /*!< SS[14:4] are don't care in Alarm
                                                                                                                                     comparison. Only SS[3:0] are compared  */
#define RTC_ALARMSUBSECONDMASK_SS14_5      ((uint32_t) (RTC_ALRMASSR_MASKSS_0 | RTC_ALRMASSR_MASKSS_2))                          /*!< SS[14:5] are don't care in Alarm
                                                                                                                                      comparison. Only SS[4:0] are compared  */
#define RTC_ALARMSUBSECONDMASK_SS14_6      ((uint32_t) (RTC_ALRMASSR_MASKSS_1 | RTC_ALRMASSR_MASKSS_2))                          /*!< SS[14:6] are don't care in Alarm
                                                                                                                                      comparison. Only SS[5:0] are compared  */
#define RTC_ALARMSUBSECONDMASK_SS14_7      ((uint32_t) (RTC_ALRMASSR_MASKSS_0 | RTC_ALRMASSR_MASKSS_1 | RTC_ALRMASSR_MASKSS_2))  /*!< SS[14:7] are don't care in Alarm
                                                                                                                                `     comparison. Only SS[6:0] are compared  */
#define RTC_ALARMSUBSECONDMASK_SS14_8      RTC_ALRMASSR_MASKSS_3                                                                 /*!< SS[14:8] are don't care in Alarm
                                                                                                                                      comparison. Only SS[7:0] are compared  */
#define RTC_ALARMSUBSECONDMASK_SS14_9      ((uint32_t) (RTC_ALRMASSR_MASKSS_0 | RTC_ALRMASSR_MASKSS_3))                          /*!< SS[14:9] are don't care in Alarm
                                                                                                                                      comparison. Only SS[8:0] are compared  */
#define RTC_ALARMSUBSECONDMASK_SS14_10     ((uint32_t) (RTC_ALRMASSR_MASKSS_1 | RTC_ALRMASSR_MASKSS_3))                          /*!< SS[14:10] are don't care in Alarm
                                                                                                                                      comparison. Only SS[9:0] are compared  */
#define RTC_ALARMSUBSECONDMASK_SS14_11     ((uint32_t) (RTC_ALRMASSR_MASKSS_0 | RTC_ALRMASSR_MASKSS_1 | RTC_ALRMASSR_MASKSS_3))  /*!< SS[14:11] are don't care in Alarm
                                                                                                                                      comparison. Only SS[10:0] are compared */
#define RTC_ALARMSUBSECONDMASK_SS14_12     ((uint32_t) (RTC_ALRMASSR_MASKSS_2 | RTC_ALRMASSR_MASKSS_3))                          /*!< SS[14:12] are don't care in Alarm
                                                                                                                                      comparison.Only SS[11:0] are compared  */
#define RTC_ALARMSUBSECONDMASK_SS14_13     ((uint32_t) (RTC_ALRMASSR_MASKSS_0 | RTC_ALRMASSR_MASKSS_2 | RTC_ALRMASSR_MASKSS_3))  /*!< SS[14:13] are don't care in Alarm
                                                                                                                                      comparison. Only SS[12:0] are compared */
#define RTC_ALARMSUBSECONDMASK_SS14        ((uint32_t) (RTC_ALRMASSR_MASKSS_1 | RTC_ALRMASSR_MASKSS_2 | RTC_ALRMASSR_MASKSS_3))  /*!< SS[14] is don't care in Alarm
                                                                                                                                      comparison.Only SS[13:0] are compared  */
#define RTC_ALARMSUBSECONDMASK_NONE        RTC_ALRMASSR_MASKSS                                                                   /*!< SS[14:0] are compared and must match
                                                                                                                                      to activate alarm. */
/**
  * @}
  */

/** @defgroup RTC_Interrupts_Definitions RTC Interrupts Definitions
  * @{
  */
#define RTC_IT_TS                         ((uint32_t)RTC_CR_TSIE)        /*!< Enable Timestamp Interrupt    */
#define RTC_IT_WUT                        ((uint32_t)RTC_CR_WUTIE)       /*!< Enable Wakeup timer Interrupt */
#define RTC_IT_ALRA                       ((uint32_t)RTC_CR_ALRAIE)      /*!< Enable Alarm A Interrupt      */
#define RTC_IT_ALRB                       ((uint32_t)RTC_CR_ALRBIE)      /*!< Enable Alarm B Interrupt      */
#define RTC_IT_TAMP                       ((uint32_t)RTC_TAMPCR_TAMPIE)  /*!< Enable all Tamper Interrupt   */

#if defined (STM32L063xx) || defined (STM32L062xx) || defined (STM32L061xx) || \
    defined (STM32L053xx) || defined (STM32L052xx) || defined (STM32L051xx) ||\
    defined (STM32L083xx) || defined (STM32L082xx) || defined (STM32L081xx) || \
    defined (STM32L073xx) || defined (STM32L072xx) || defined (STM32L071xx) || \
    defined (STM32L031xx) || defined (STM32L041xx)

#define RTC_IT_TAMP1                      ((uint32_t)RTC_TAMPCR_TAMP1IE) /*!< Enable Tamper 1 Interrupt     */
#endif /* (STM32L063xx) || (STM32L062xx) || (STM32L061xx) ||
        * (STM32L053xx) || (STM32L052xx) || (STM32L051xx) ||
        * (STM32L083xx) || (STM32L082xx) || (STM32L081xx) ||
        * (STM32L073xx) || (STM32L072xx) || (STM32L071xx) ||
        * (STM32L031xx) || (STM32L041xx)
        */
#define RTC_IT_TAMP2                      ((uint32_t)RTC_TAMPCR_TAMP2IE) /*!< Enable Tamper 2 Interrupt     */
/**
  * @}
  */

/** @defgroup RTC_Flags_Definitions RTC Flags Definitions
  * @{
  */
#define RTC_FLAG_RECALPF                  ((uint32_t)RTC_ISR_RECALPF)
#define RTC_FLAG_TAMP2F                   ((uint32_t)RTC_ISR_TAMP2F)

#if defined (STM32L063xx) || defined (STM32L062xx) || defined (STM32L061xx) || \
    defined (STM32L053xx) || defined (STM32L052xx) || defined (STM32L051xx) ||\
    defined (STM32L083xx) || defined (STM32L082xx) || defined (STM32L081xx) || \
    defined (STM32L073xx) || defined (STM32L072xx) || defined (STM32L071xx) || \
    defined (STM32L031xx) || defined (STM32L041xx)
#define RTC_FLAG_TAMP1F                   ((uint32_t)RTC_ISR_TAMP1F)
#endif /* (STM32L063xx) || (STM32L062xx) || (STM32L061xx) ||
        * (STM32L053xx) || (STM32L052xx) || (STM32L051xx) ||
        * (STM32L083xx) || (STM32L082xx) || (STM32L081xx) ||
        * (STM32L073xx) || (STM32L072xx) || (STM32L071xx) ||
        * (STM32L031xx) || (STM32L041xx)
        */

#define RTC_FLAG_TSOVF                    ((uint32_t)RTC_ISR_TSOVF)
#define RTC_FLAG_TSF                      ((uint32_t)RTC_ISR_TSF)
#define RTC_FLAG_WUTF                     ((uint32_t)RTC_ISR_WUTF)
#define RTC_FLAG_ALRBF                    ((uint32_t)RTC_ISR_ALRBF)
#define RTC_FLAG_ALRAF                    ((uint32_t)RTC_ISR_ALRAF)
#define RTC_FLAG_INITF                    ((uint32_t)RTC_ISR_INITF)
#define RTC_FLAG_RSF                      ((uint32_t)RTC_ISR_RSF)
#define RTC_FLAG_INITS                    ((uint32_t)RTC_ISR_INITS)
#define RTC_FLAG_SHPF                     ((uint32_t)RTC_ISR_SHPF)
#define RTC_FLAG_WUTWF                    ((uint32_t)RTC_ISR_WUTWF)
#define RTC_FLAG_ALRBWF                   ((uint32_t)RTC_ISR_ALRBWF)
#define RTC_FLAG_ALRAWF                   ((uint32_t)RTC_ISR_ALRAWF)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup RTC_Exported_Macros RTC Exported Macros
  * @{
  */

/** @brief Reset RTC handle state
  * @param  __HANDLE__: RTC handle.
  * @retval None
  */
#define __HAL_RTC_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_RTC_STATE_RESET)

/**
  * @brief  Disable the write protection for RTC registers.
  * @param  __HANDLE__: specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_WRITEPROTECTION_DISABLE(__HANDLE__)             \
                        do{                                       \
                            (__HANDLE__)->Instance->WPR = 0xCAU;   \
                            (__HANDLE__)->Instance->WPR = 0x53U;   \
                          } while(0U)

/**
  * @brief  Enable the write protection for RTC registers.
  * @param  __HANDLE__: specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_WRITEPROTECTION_ENABLE(__HANDLE__)              \
                        do{                                       \
                            (__HANDLE__)->Instance->WPR = 0xFFU;   \
                          } while(0U)

/**
  * @brief  Enable the RTC ALARMA peripheral.
  * @param  __HANDLE__: specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_ALARMA_ENABLE(__HANDLE__)  ((__HANDLE__)->Instance->CR |= (RTC_CR_ALRAE))

/**
  * @brief  Disable the RTC ALARMA peripheral.
  * @param  __HANDLE__: specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_ALARMA_DISABLE(__HANDLE__)  ((__HANDLE__)->Instance->CR &= ~(RTC_CR_ALRAE))

/**
  * @brief  Enable the RTC ALARMB peripheral.
  * @param  __HANDLE__: specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_ALARMB_ENABLE(__HANDLE__)   ((__HANDLE__)->Instance->CR |= (RTC_CR_ALRBE))

/**
  * @brief  Disable the RTC ALARMB peripheral.
  * @param  __HANDLE__: specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_ALARMB_DISABLE(__HANDLE__)  ((__HANDLE__)->Instance->CR &= ~(RTC_CR_ALRBE))

/**
  * @brief  Enable the RTC Alarm interrupt.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __INTERRUPT__: specifies the RTC Alarm interrupt sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *             @arg RTC_IT_ALRA: Alarm A interrupt
  *             @arg RTC_IT_ALRB: Alarm B interrupt
  * @retval None
  */
#define __HAL_RTC_ALARM_ENABLE_IT(__HANDLE__, __INTERRUPT__)   ((__HANDLE__)->Instance->CR |= (__INTERRUPT__))

/**
  * @brief  Disable the RTC Alarm interrupt.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __INTERRUPT__: specifies the RTC Alarm interrupt sources to be enabled or disabled.
  *         This parameter can be any combination of the following values:
  *            @arg RTC_IT_ALRA: Alarm A interrupt
  *            @arg RTC_IT_ALRB: Alarm B interrupt
  * @retval None
  */
#define __HAL_RTC_ALARM_DISABLE_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->CR &= ~(__INTERRUPT__))

/**
  * @brief  Check whether the specified RTC Alarm interrupt has occurred or not.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __INTERRUPT__: specifies the RTC Alarm interrupt sources to check.
  *         This parameter can be:
  *            @arg RTC_IT_ALRA: Alarm A interrupt
  *            @arg RTC_IT_ALRB: Alarm B interrupt
  * @retval None
  */
#define __HAL_RTC_ALARM_GET_IT(__HANDLE__, __INTERRUPT__)  (((((__HANDLE__)->Instance->ISR)& ((__INTERRUPT__)>> 4U)) != RESET)? SET : RESET)

/**
  * @brief  Check whether the specified RTC Alarm interrupt has been enabled or not.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __INTERRUPT__: specifies the RTC Alarm interrupt sources to check.
  *         This parameter can be:
  *            @arg RTC_IT_ALRA: Alarm A interrupt
  *            @arg RTC_IT_ALRB: Alarm B interrupt
  * @retval None
  */
#define __HAL_RTC_ALARM_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)     (((((__HANDLE__)->Instance->CR) & (__INTERRUPT__)) != RESET) ? SET : RESET)

/**
  * @brief  Get the selected RTC Alarm's flag status.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __FLAG__: specifies the RTC Alarm Flag sources to check.
  *         This parameter can be:
  *            @arg RTC_FLAG_ALRAF
  *            @arg RTC_FLAG_ALRBF
  *            @arg RTC_FLAG_ALRAWF
  *            @arg RTC_FLAG_ALRBWF
  * @retval None
  */
#define __HAL_RTC_ALARM_GET_FLAG(__HANDLE__, __FLAG__)   (((((__HANDLE__)->Instance->ISR) & (__FLAG__)) != RESET)? SET : RESET)

/**
  * @brief  Clear the RTC Alarm's pending flags.
  * @param  __HANDLE__: specifies the RTC handle.
  * @param  __FLAG__: specifies the RTC Alarm Flag sources to clear.
  *          This parameter can be:
  *             @arg RTC_FLAG_ALRAF
  *             @arg RTC_FLAG_ALRBF
  * @retval None
  */
#define __HAL_RTC_ALARM_CLEAR_FLAG(__HANDLE__, __FLAG__)   ((__HANDLE__)->Instance->ISR) = (~((__FLAG__) | RTC_ISR_INIT) | ((__HANDLE__)->Instance->ISR & RTC_ISR_INIT))

/**
  * @brief  Enable interrupt on the RTC Alarm associated Exti line.
  * @retval None
  */
#define __HAL_RTC_ALARM_EXTI_ENABLE_IT()            (EXTI->IMR |= RTC_EXTI_LINE_ALARM_EVENT)

/**
  * @brief  Disable interrupt on the RTC Alarm associated Exti line.
  * @retval None
  */
#define __HAL_RTC_ALARM_EXTI_DISABLE_IT()           (EXTI->IMR &= ~(RTC_EXTI_LINE_ALARM_EVENT))

/**
  * @brief  Enable event on the RTC Alarm associated Exti line.
  * @retval None.
  */
#define __HAL_RTC_ALARM_EXTI_ENABLE_EVENT()         (EXTI->EMR |= RTC_EXTI_LINE_ALARM_EVENT)

/**
  * @brief  Disable event on the RTC Alarm associated Exti line.
  * @retval None.
  */
#define __HAL_RTC_ALARM_EXTI_DISABLE_EVENT()         (EXTI->EMR &= ~(RTC_EXTI_LINE_ALARM_EVENT))

/**
  * @brief  Enable falling edge trigger on the RTC Alarm associated Exti line.
  * @retval None.
  */
#define __HAL_RTC_ALARM_EXTI_ENABLE_FALLING_EDGE()   (EXTI->FTSR |= RTC_EXTI_LINE_ALARM_EVENT)

/**
  * @brief  Disable falling edge trigger on the RTC Alarm associated Exti line.
  * @retval None.
  */
#define __HAL_RTC_ALARM_EXTI_DISABLE_FALLING_EDGE()  (EXTI->FTSR &= ~(RTC_EXTI_LINE_ALARM_EVENT))

/**
  * @brief  Enable rising edge trigger on the RTC Alarm associated Exti line.
  * @retval None.
  */
#define __HAL_RTC_ALARM_EXTI_ENABLE_RISING_EDGE()    (EXTI->RTSR |= RTC_EXTI_LINE_ALARM_EVENT)

/**
  * @brief  Disable rising edge trigger on the RTC Alarm associated Exti line.
  * @retval None.
  */
#define __HAL_RTC_ALARM_EXTI_DISABLE_RISING_EDGE()   (EXTI->RTSR &= ~(RTC_EXTI_LINE_ALARM_EVENT))

/**
  * @brief  Enable rising & falling edge trigger on the RTC Alarm associated Exti line.
  * @retval None.
  */
#define __HAL_RTC_ALARM_EXTI_ENABLE_RISING_FALLING_EDGE()  do { \
                                                             __HAL_RTC_ALARM_EXTI_ENABLE_RISING_EDGE();  \
                                                             __HAL_RTC_ALARM_EXTI_ENABLE_FALLING_EDGE(); \
                                                           } while(0U)

/**
  * @brief  Disable rising & falling edge trigger on the RTC Alarm associated Exti line.
  * @retval None.
  */
#define __HAL_RTC_ALARM_EXTI_DISABLE_RISING_FALLING_EDGE() do { \
                                                             __HAL_RTC_ALARM_EXTI_DISABLE_RISING_EDGE();  \
                                                             __HAL_RTC_ALARM_EXTI_DISABLE_FALLING_EDGE(); \
                                                           } while(0U)

/**
  * @brief Check whether the RTC Alarm associated Exti line interrupt flag is set or not.
  * @retval Line Status.
  */
#define __HAL_RTC_ALARM_EXTI_GET_FLAG()              (EXTI->PR & RTC_EXTI_LINE_ALARM_EVENT)

/**
  * @brief Clear the RTC Alarm associated Exti line flag.
  * @retval None.
  */
#define __HAL_RTC_ALARM_EXTI_CLEAR_FLAG()            (EXTI->PR = RTC_EXTI_LINE_ALARM_EVENT)

/**
  * @brief Generate a Software interrupt on RTC Alarm associated Exti line.
  * @retval None.
  */
#define __HAL_RTC_ALARM_EXTI_GENERATE_SWIT()         (EXTI->SWIER |= RTC_EXTI_LINE_ALARM_EVENT)

/**
  * @}
  */

/* Include RTC HAL Extended module */
#include "stm32l0xx_hal_rtc_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @defgroup RTC_Exported_Functions RTC Exported Functions
  * @{
  */

/** @defgroup RTC_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
/* Initialization and de-initialization functions  ****************************/
HAL_StatusTypeDef HAL_RTC_Init(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTC_DeInit(RTC_HandleTypeDef *hrtc);
void HAL_RTC_MspInit(RTC_HandleTypeDef *hrtc);
void HAL_RTC_MspDeInit(RTC_HandleTypeDef *hrtc);
/**
  * @}
  */

/** @defgroup RTC_Exported_Functions_Group2 RTC Time and Date functions
  * @{
  */
/* RTC Time and Date functions ************************************************/
HAL_StatusTypeDef HAL_RTC_SetTime(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime, uint32_t Format);
HAL_StatusTypeDef HAL_RTC_GetTime(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime, uint32_t Format);
HAL_StatusTypeDef HAL_RTC_SetDate(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate, uint32_t Format);
HAL_StatusTypeDef HAL_RTC_GetDate(RTC_HandleTypeDef *hrtc, RTC_DateTypeDef *sDate, uint32_t Format);
/**
  * @}
  */

/** @defgroup RTC_Exported_Functions_Group3 RTC Alarm functions
  * @{
  */
/* RTC Alarm functions ********************************************************/
HAL_StatusTypeDef HAL_RTC_SetAlarm(RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm, uint32_t Format);
HAL_StatusTypeDef HAL_RTC_SetAlarm_IT(RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm, uint32_t Format);
HAL_StatusTypeDef HAL_RTC_DeactivateAlarm(RTC_HandleTypeDef *hrtc, uint32_t Alarm);
HAL_StatusTypeDef HAL_RTC_GetAlarm(RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm, uint32_t Alarm, uint32_t Format);
void              HAL_RTC_AlarmIRQHandler(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTC_PollForAlarmAEvent(RTC_HandleTypeDef *hrtc, uint32_t Timeout);
void              HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc);
/**
  * @}
  */

/** @defgroup  RTC_Exported_Functions_Group4 Peripheral Control functions
  * @{
  */
/* Peripheral Control functions ***********************************************/
HAL_StatusTypeDef   HAL_RTC_WaitForSynchro(RTC_HandleTypeDef* hrtc);
/**
  * @}
  */

/** @defgroup RTC_Exported_Functions_Group5 Peripheral State functions
  * @{
  */
/* Peripheral State functions *************************************************/
HAL_RTCStateTypeDef HAL_RTC_GetState(RTC_HandleTypeDef *hrtc);
/**
  * @}
  */

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup RTC_Private_Constants RTC Private Constants
  * @{
  */
/* Masks Definition */
#define RTC_TR_RESERVED_MASK  ((uint32_t) (RTC_TR_PM | RTC_TR_HT | RTC_TR_HU | \
                                           RTC_TR_MNT | RTC_TR_MNU| RTC_TR_ST | \
                                           RTC_TR_SU))
#define RTC_DR_RESERVED_MASK  ((uint32_t) (RTC_DR_YT | RTC_DR_YU | RTC_DR_WDU | \
                                           RTC_DR_MT | RTC_DR_MU | RTC_DR_DT  | \
                                           RTC_DR_DU))
#define RTC_INIT_MASK           ((uint32_t)0xFFFFFFFFU)
#define RTC_RSF_MASK            ((uint32_t)~(RTC_ISR_INIT | RTC_ISR_RSF))

#define RTC_TIMEOUT_VALUE  1000U

#define RTC_EXTI_LINE_ALARM_EVENT             ((uint32_t)EXTI_IMR_IM17)  /*!< External interrupt line 17 Connected to the RTC Alarm event */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup RTC_Private_Macros RTC Private Macros
  * @{
  */

/** @defgroup RTC_IS_RTC_Definitions RTC Private macros to check input parameters
  * @{
  */

#define IS_RTC_HOUR_FORMAT(FORMAT)     (((FORMAT) == RTC_HOURFORMAT_12) || \
                                        ((FORMAT) == RTC_HOURFORMAT_24))

#define IS_RTC_OUTPUT_POL(POL) (((POL) == RTC_OUTPUT_POLARITY_HIGH) || \
                                ((POL) == RTC_OUTPUT_POLARITY_LOW))

#define IS_RTC_OUTPUT_TYPE(TYPE) (((TYPE) == RTC_OUTPUT_TYPE_OPENDRAIN) || \
                                  ((TYPE) == RTC_OUTPUT_TYPE_PUSHPULL))

#define IS_RTC_OUTPUT_REMAP(REMAP)   (((REMAP) == RTC_OUTPUT_REMAP_NONE) || \
                                      ((REMAP) == RTC_OUTPUT_REMAP_POS1))

#define IS_RTC_HOURFORMAT12(PM)  (((PM) == RTC_HOURFORMAT12_AM) || \
                                  ((PM) == RTC_HOURFORMAT12_PM))

#define IS_RTC_DAYLIGHT_SAVING(SAVE) (((SAVE) == RTC_DAYLIGHTSAVING_SUB1H) || \
                                      ((SAVE) == RTC_DAYLIGHTSAVING_ADD1H) || \
                                      ((SAVE) == RTC_DAYLIGHTSAVING_NONE))

#define IS_RTC_STORE_OPERATION(OPERATION) (((OPERATION) == RTC_STOREOPERATION_RESET) || \
                                           ((OPERATION) == RTC_STOREOPERATION_SET))

#define IS_RTC_FORMAT(FORMAT) (((FORMAT) == RTC_FORMAT_BIN) || ((FORMAT) == RTC_FORMAT_BCD))

#define IS_RTC_YEAR(YEAR)              ((YEAR) <= (uint32_t)99U)

#define IS_RTC_MONTH(MONTH)            (((MONTH) >= (uint32_t)1U) && ((MONTH) <= (uint32_t)12U))

#define IS_RTC_DATE(DATE)              (((DATE) >= (uint32_t)1U) && ((DATE) <= (uint32_t)31U))

#define IS_RTC_WEEKDAY(WEEKDAY) (((WEEKDAY) == RTC_WEEKDAY_MONDAY)    || \
                                 ((WEEKDAY) == RTC_WEEKDAY_TUESDAY)   || \
                                 ((WEEKDAY) == RTC_WEEKDAY_WEDNESDAY) || \
                                 ((WEEKDAY) == RTC_WEEKDAY_THURSDAY)  || \
                                 ((WEEKDAY) == RTC_WEEKDAY_FRIDAY)    || \
                                 ((WEEKDAY) == RTC_WEEKDAY_SATURDAY)  || \
                                 ((WEEKDAY) == RTC_WEEKDAY_SUNDAY))

#define IS_RTC_ALARM_DATE_WEEKDAY_DATE(DATE) (((DATE) >(uint32_t)0U) && ((DATE) <= (uint32_t)31U))

#define IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(WEEKDAY) (((WEEKDAY) == RTC_WEEKDAY_MONDAY)    || \
                                                    ((WEEKDAY) == RTC_WEEKDAY_TUESDAY)   || \
                                                    ((WEEKDAY) == RTC_WEEKDAY_WEDNESDAY) || \
                                                    ((WEEKDAY) == RTC_WEEKDAY_THURSDAY)  || \
                                                    ((WEEKDAY) == RTC_WEEKDAY_FRIDAY)    || \
                                                    ((WEEKDAY) == RTC_WEEKDAY_SATURDAY)  || \
                                                    ((WEEKDAY) == RTC_WEEKDAY_SUNDAY))

#define IS_RTC_ALARM_DATE_WEEKDAY_SEL(SEL) (((SEL) == RTC_ALARMDATEWEEKDAYSEL_DATE) || \
                                            ((SEL) == RTC_ALARMDATEWEEKDAYSEL_WEEKDAY))

#define IS_RTC_ALARM_MASK(MASK)  (((MASK) & ~(RTC_ALARMMASK_ALL)) == (uint32_t)RESET)

#define IS_RTC_ALARM(ALARM)      (((ALARM) == RTC_ALARM_A) || ((ALARM) == RTC_ALARM_B))

#define IS_RTC_ALARM_SUB_SECOND_VALUE(VALUE) ((VALUE) <= RTC_ALRMASSR_SS)

#define IS_RTC_ALARM_SUB_SECOND_MASK(MASK)   (((MASK) == RTC_ALARMSUBSECONDMASK_ALL) || \
                                              ((MASK) == RTC_ALARMSUBSECONDMASK_SS14_1) || \
                                              ((MASK) == RTC_ALARMSUBSECONDMASK_SS14_2) || \
                                              ((MASK) == RTC_ALARMSUBSECONDMASK_SS14_3) || \
                                              ((MASK) == RTC_ALARMSUBSECONDMASK_SS14_4) || \
                                              ((MASK) == RTC_ALARMSUBSECONDMASK_SS14_5) || \
                                              ((MASK) == RTC_ALARMSUBSECONDMASK_SS14_6) || \
                                              ((MASK) == RTC_ALARMSUBSECONDMASK_SS14_7) || \
                                              ((MASK) == RTC_ALARMSUBSECONDMASK_SS14_8) || \
                                              ((MASK) == RTC_ALARMSUBSECONDMASK_SS14_9) || \
                                              ((MASK) == RTC_ALARMSUBSECONDMASK_SS14_10) || \
                                              ((MASK) == RTC_ALARMSUBSECONDMASK_SS14_11) || \
                                              ((MASK) == RTC_ALARMSUBSECONDMASK_SS14_12) || \
                                              ((MASK) == RTC_ALARMSUBSECONDMASK_SS14_13) || \
                                              ((MASK) == RTC_ALARMSUBSECONDMASK_SS14) || \
                                              ((MASK) == RTC_ALARMSUBSECONDMASK_NONE))

#define IS_RTC_ASYNCH_PREDIV(PREDIV)   ((PREDIV) <= (uint32_t)0x7FU)

#define IS_RTC_SYNCH_PREDIV(PREDIV)    ((PREDIV) <= (uint32_t)0x7FFFU)

#define IS_RTC_HOUR12(HOUR)            (((HOUR) > (uint32_t)0U) && ((HOUR) <= (uint32_t)12U))

#define IS_RTC_HOUR24(HOUR)            ((HOUR) <= (uint32_t)23U)

#define IS_RTC_MINUTES(MINUTES)        ((MINUTES) <= (uint32_t)59U)

#define IS_RTC_SECONDS(SECONDS)        ((SECONDS) <= (uint32_t)59U)

/**
  * @}
  */

/**
  * @}
  */

/* Private functions -------------------------------------------------------------*/
/** @defgroup RTC_Private_Functions RTC Private Functions
  * @{
  */
HAL_StatusTypeDef  RTC_EnterInitMode(RTC_HandleTypeDef* hrtc);
uint8_t            RTC_ByteToBcd2(uint8_t Value);
uint8_t            RTC_Bcd2ToByte(uint8_t Value);
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

#endif /* __STM32L0xx_HAL_RTC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

