/**************************************************************************//**
 * @file efm32hg_dma_descriptor.h
 * @brief EFM32HG_DMA_DESCRIPTOR register and bit field definitions
 * @version 5.1.2
 ******************************************************************************
 * @section License
 * <b>Copyright 2017 Silicon Laboratories, Inc. http://www.silabs.com</b>
 ******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.@n
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.@n
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Silicon Laboratories, Inc.
 * has no obligation to support this Software. Silicon Laboratories, Inc. is
 * providing the Software "AS IS", with no express or implied warranties of any
 * kind, including, but not limited to, any implied warranties of
 * merchantability or fitness for any particular purpose or warranties against
 * infringement of any proprietary rights of a third party.
 *
 * Silicon Laboratories, Inc. will not be liable for any consequential,
 * incidental, or special damages, or any other relief, or for any claim by
 * any third party, arising from your use of this Software.
 *
 *****************************************************************************/
/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFM32HG_DMA_DESCRIPTOR
 * @{
 *****************************************************************************/
typedef struct
{
  /* Note! Use of double __IOM (volatile) qualifier to ensure that both */
  /* pointer and referenced memory are declared volatile. */
  __IOM void * __IOM SRCEND;   /**< DMA source address end */
  __IOM void * __IOM DSTEND;   /**< DMA destination address end */
  __IOM uint32_t     CTRL;     /**< DMA control register */
  __IOM uint32_t     USER;     /**< DMA padding register, available for user */
} DMA_DESCRIPTOR_TypeDef;      /** @} */

/** @} End of group Parts */


