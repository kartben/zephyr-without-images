/* Copyright (c) 2016, Nordic Semiconductor ASA
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice, this
 *     list of conditions and the following disclaimer.
 *
 *   * Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 *   * Neither the name of Nordic Semiconductor ASA nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
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
 */
 
#ifndef __NRF52840_BITS_H
#define __NRF52840_BITS_H

/*lint ++flb "Enter library region" */

/* Peripheral: AAR */
/* Description: Accelerated Address Resolver */

/* Register: AAR_INTENSET */
/* Description: Enable interrupt */

/* Bit 2 : Write '1' to Enable interrupt for NOTRESOLVED event */
#define AAR_INTENSET_NOTRESOLVED_Pos (2UL) /*!< Position of NOTRESOLVED field. */
#define AAR_INTENSET_NOTRESOLVED_Msk (0x1UL << AAR_INTENSET_NOTRESOLVED_Pos) /*!< Bit mask of NOTRESOLVED field. */
#define AAR_INTENSET_NOTRESOLVED_Disabled (0UL) /*!< Read: Disabled */
#define AAR_INTENSET_NOTRESOLVED_Enabled (1UL) /*!< Read: Enabled */
#define AAR_INTENSET_NOTRESOLVED_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable interrupt for RESOLVED event */
#define AAR_INTENSET_RESOLVED_Pos (1UL) /*!< Position of RESOLVED field. */
#define AAR_INTENSET_RESOLVED_Msk (0x1UL << AAR_INTENSET_RESOLVED_Pos) /*!< Bit mask of RESOLVED field. */
#define AAR_INTENSET_RESOLVED_Disabled (0UL) /*!< Read: Disabled */
#define AAR_INTENSET_RESOLVED_Enabled (1UL) /*!< Read: Enabled */
#define AAR_INTENSET_RESOLVED_Set (1UL) /*!< Enable */

/* Bit 0 : Write '1' to Enable interrupt for END event */
#define AAR_INTENSET_END_Pos (0UL) /*!< Position of END field. */
#define AAR_INTENSET_END_Msk (0x1UL << AAR_INTENSET_END_Pos) /*!< Bit mask of END field. */
#define AAR_INTENSET_END_Disabled (0UL) /*!< Read: Disabled */
#define AAR_INTENSET_END_Enabled (1UL) /*!< Read: Enabled */
#define AAR_INTENSET_END_Set (1UL) /*!< Enable */

/* Register: AAR_INTENCLR */
/* Description: Disable interrupt */

/* Bit 2 : Write '1' to Disable interrupt for NOTRESOLVED event */
#define AAR_INTENCLR_NOTRESOLVED_Pos (2UL) /*!< Position of NOTRESOLVED field. */
#define AAR_INTENCLR_NOTRESOLVED_Msk (0x1UL << AAR_INTENCLR_NOTRESOLVED_Pos) /*!< Bit mask of NOTRESOLVED field. */
#define AAR_INTENCLR_NOTRESOLVED_Disabled (0UL) /*!< Read: Disabled */
#define AAR_INTENCLR_NOTRESOLVED_Enabled (1UL) /*!< Read: Enabled */
#define AAR_INTENCLR_NOTRESOLVED_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable interrupt for RESOLVED event */
#define AAR_INTENCLR_RESOLVED_Pos (1UL) /*!< Position of RESOLVED field. */
#define AAR_INTENCLR_RESOLVED_Msk (0x1UL << AAR_INTENCLR_RESOLVED_Pos) /*!< Bit mask of RESOLVED field. */
#define AAR_INTENCLR_RESOLVED_Disabled (0UL) /*!< Read: Disabled */
#define AAR_INTENCLR_RESOLVED_Enabled (1UL) /*!< Read: Enabled */
#define AAR_INTENCLR_RESOLVED_Clear (1UL) /*!< Disable */

/* Bit 0 : Write '1' to Disable interrupt for END event */
#define AAR_INTENCLR_END_Pos (0UL) /*!< Position of END field. */
#define AAR_INTENCLR_END_Msk (0x1UL << AAR_INTENCLR_END_Pos) /*!< Bit mask of END field. */
#define AAR_INTENCLR_END_Disabled (0UL) /*!< Read: Disabled */
#define AAR_INTENCLR_END_Enabled (1UL) /*!< Read: Enabled */
#define AAR_INTENCLR_END_Clear (1UL) /*!< Disable */

/* Register: AAR_STATUS */
/* Description: Resolution status */

/* Bits 3..0 : The IRK that was used last time an address was resolved */
#define AAR_STATUS_STATUS_Pos (0UL) /*!< Position of STATUS field. */
#define AAR_STATUS_STATUS_Msk (0xFUL << AAR_STATUS_STATUS_Pos) /*!< Bit mask of STATUS field. */

/* Register: AAR_ENABLE */
/* Description: Enable AAR */

/* Bits 1..0 : Enable or disable AAR */
#define AAR_ENABLE_ENABLE_Pos (0UL) /*!< Position of ENABLE field. */
#define AAR_ENABLE_ENABLE_Msk (0x3UL << AAR_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define AAR_ENABLE_ENABLE_Disabled (0UL) /*!< Disable */
#define AAR_ENABLE_ENABLE_Enabled (3UL) /*!< Enable */

/* Register: AAR_NIRK */
/* Description: Number of IRKs */

/* Bits 4..0 : Number of Identity root keys available in the IRK data structure */
#define AAR_NIRK_NIRK_Pos (0UL) /*!< Position of NIRK field. */
#define AAR_NIRK_NIRK_Msk (0x1FUL << AAR_NIRK_NIRK_Pos) /*!< Bit mask of NIRK field. */

/* Register: AAR_IRKPTR */
/* Description: Pointer to IRK data structure */

/* Bits 31..0 : Pointer to the IRK data structure */
#define AAR_IRKPTR_IRKPTR_Pos (0UL) /*!< Position of IRKPTR field. */
#define AAR_IRKPTR_IRKPTR_Msk (0xFFFFFFFFUL << AAR_IRKPTR_IRKPTR_Pos) /*!< Bit mask of IRKPTR field. */

/* Register: AAR_ADDRPTR */
/* Description: Pointer to the resolvable address */

/* Bits 31..0 : Pointer to the resolvable address (6-bytes) */
#define AAR_ADDRPTR_ADDRPTR_Pos (0UL) /*!< Position of ADDRPTR field. */
#define AAR_ADDRPTR_ADDRPTR_Msk (0xFFFFFFFFUL << AAR_ADDRPTR_ADDRPTR_Pos) /*!< Bit mask of ADDRPTR field. */

/* Register: AAR_SCRATCHPTR */
/* Description: Pointer to data area used for temporary storage */

/* Bits 31..0 : Pointer to a scratch data area used for temporary storage during resolution.A space of minimum 3 bytes must be reserved. */
#define AAR_SCRATCHPTR_SCRATCHPTR_Pos (0UL) /*!< Position of SCRATCHPTR field. */
#define AAR_SCRATCHPTR_SCRATCHPTR_Msk (0xFFFFFFFFUL << AAR_SCRATCHPTR_SCRATCHPTR_Pos) /*!< Bit mask of SCRATCHPTR field. */


/* Peripheral: ACL */
/* Description: Access control lists */

/* Register: ACL_DISABLEINDEBUG */
/* Description: Disable all ACL protection mechanisms for regions while in debug mode */

/* Bit 0 : Disable the protection mechanism for regions while in debug mode. */
#define ACL_DISABLEINDEBUG_DISABLEINDEBUG_Pos (0UL) /*!< Position of DISABLEINDEBUG field. */
#define ACL_DISABLEINDEBUG_DISABLEINDEBUG_Msk (0x1UL << ACL_DISABLEINDEBUG_DISABLEINDEBUG_Pos) /*!< Bit mask of DISABLEINDEBUG field. */
#define ACL_DISABLEINDEBUG_DISABLEINDEBUG_Enabled (0UL) /*!< ACL is enabled in debug mode */
#define ACL_DISABLEINDEBUG_DISABLEINDEBUG_Disabled (1UL) /*!< ACL is disabled in debug mode */

/* Register: ACL_ACL_ADDR */
/* Description: Description cluster[0]:  Configure the word-aligned start address of region 0 to protect */

/* Bits 31..0 : Valid word-aligned start address of region 0 to protect. Address must point to a flash page boundary. */
#define ACL_ACL_ADDR_ADDR_Pos (0UL) /*!< Position of ADDR field. */
#define ACL_ACL_ADDR_ADDR_Msk (0xFFFFFFFFUL << ACL_ACL_ADDR_ADDR_Pos) /*!< Bit mask of ADDR field. */

/* Register: ACL_ACL_SIZE */
/* Description: Description cluster[0]:  Size of region to protect counting from address ACL[0].ADDR. Write '0' as no effect. */

/* Bits 31..0 : Size of flash region 0 in bytes. Must be a multiple of the flash page size. */
#define ACL_ACL_SIZE_SIZE_Pos (0UL) /*!< Position of SIZE field. */
#define ACL_ACL_SIZE_SIZE_Msk (0xFFFFFFFFUL << ACL_ACL_SIZE_SIZE_Pos) /*!< Bit mask of SIZE field. */

/* Register: ACL_ACL_PERM */
/* Description: Description cluster[0]:  Access permissions for region 0 as defined by start address ACL[0].ADDR and size ACL[0].SIZE */

/* Bit 2 : Configure read permissions for region 0. Write '0' has no effect. */
#define ACL_ACL_PERM_READ_Pos (2UL) /*!< Position of READ field. */
#define ACL_ACL_PERM_READ_Msk (0x1UL << ACL_ACL_PERM_READ_Pos) /*!< Bit mask of READ field. */
#define ACL_ACL_PERM_READ_Enable (0UL) /*!< Allow read instructions to region 0 */
#define ACL_ACL_PERM_READ_Disable (1UL) /*!< Block read instructions to region 0 */

/* Bit 1 : Configure write and erase permissions for region 0. Write '0' has no effect. */
#define ACL_ACL_PERM_WRITE_Pos (1UL) /*!< Position of WRITE field. */
#define ACL_ACL_PERM_WRITE_Msk (0x1UL << ACL_ACL_PERM_WRITE_Pos) /*!< Bit mask of WRITE field. */
#define ACL_ACL_PERM_WRITE_Enable (0UL) /*!< Allow write and erase instructions to region 0 */
#define ACL_ACL_PERM_WRITE_Disable (1UL) /*!< Block write and erase instructions to region 0 */


/* Peripheral: CCM */
/* Description: AES CCM Mode Encryption */

/* Register: CCM_SHORTS */
/* Description: Shortcut register */

/* Bit 0 : Shortcut between ENDKSGEN event and CRYPT task */
#define CCM_SHORTS_ENDKSGEN_CRYPT_Pos (0UL) /*!< Position of ENDKSGEN_CRYPT field. */
#define CCM_SHORTS_ENDKSGEN_CRYPT_Msk (0x1UL << CCM_SHORTS_ENDKSGEN_CRYPT_Pos) /*!< Bit mask of ENDKSGEN_CRYPT field. */
#define CCM_SHORTS_ENDKSGEN_CRYPT_Disabled (0UL) /*!< Disable shortcut */
#define CCM_SHORTS_ENDKSGEN_CRYPT_Enabled (1UL) /*!< Enable shortcut */

/* Register: CCM_INTENSET */
/* Description: Enable interrupt */

/* Bit 2 : Write '1' to Enable interrupt for ERROR event */
#define CCM_INTENSET_ERROR_Pos (2UL) /*!< Position of ERROR field. */
#define CCM_INTENSET_ERROR_Msk (0x1UL << CCM_INTENSET_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define CCM_INTENSET_ERROR_Disabled (0UL) /*!< Read: Disabled */
#define CCM_INTENSET_ERROR_Enabled (1UL) /*!< Read: Enabled */
#define CCM_INTENSET_ERROR_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable interrupt for ENDCRYPT event */
#define CCM_INTENSET_ENDCRYPT_Pos (1UL) /*!< Position of ENDCRYPT field. */
#define CCM_INTENSET_ENDCRYPT_Msk (0x1UL << CCM_INTENSET_ENDCRYPT_Pos) /*!< Bit mask of ENDCRYPT field. */
#define CCM_INTENSET_ENDCRYPT_Disabled (0UL) /*!< Read: Disabled */
#define CCM_INTENSET_ENDCRYPT_Enabled (1UL) /*!< Read: Enabled */
#define CCM_INTENSET_ENDCRYPT_Set (1UL) /*!< Enable */

/* Bit 0 : Write '1' to Enable interrupt for ENDKSGEN event */
#define CCM_INTENSET_ENDKSGEN_Pos (0UL) /*!< Position of ENDKSGEN field. */
#define CCM_INTENSET_ENDKSGEN_Msk (0x1UL << CCM_INTENSET_ENDKSGEN_Pos) /*!< Bit mask of ENDKSGEN field. */
#define CCM_INTENSET_ENDKSGEN_Disabled (0UL) /*!< Read: Disabled */
#define CCM_INTENSET_ENDKSGEN_Enabled (1UL) /*!< Read: Enabled */
#define CCM_INTENSET_ENDKSGEN_Set (1UL) /*!< Enable */

/* Register: CCM_INTENCLR */
/* Description: Disable interrupt */

/* Bit 2 : Write '1' to Disable interrupt for ERROR event */
#define CCM_INTENCLR_ERROR_Pos (2UL) /*!< Position of ERROR field. */
#define CCM_INTENCLR_ERROR_Msk (0x1UL << CCM_INTENCLR_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define CCM_INTENCLR_ERROR_Disabled (0UL) /*!< Read: Disabled */
#define CCM_INTENCLR_ERROR_Enabled (1UL) /*!< Read: Enabled */
#define CCM_INTENCLR_ERROR_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable interrupt for ENDCRYPT event */
#define CCM_INTENCLR_ENDCRYPT_Pos (1UL) /*!< Position of ENDCRYPT field. */
#define CCM_INTENCLR_ENDCRYPT_Msk (0x1UL << CCM_INTENCLR_ENDCRYPT_Pos) /*!< Bit mask of ENDCRYPT field. */
#define CCM_INTENCLR_ENDCRYPT_Disabled (0UL) /*!< Read: Disabled */
#define CCM_INTENCLR_ENDCRYPT_Enabled (1UL) /*!< Read: Enabled */
#define CCM_INTENCLR_ENDCRYPT_Clear (1UL) /*!< Disable */

/* Bit 0 : Write '1' to Disable interrupt for ENDKSGEN event */
#define CCM_INTENCLR_ENDKSGEN_Pos (0UL) /*!< Position of ENDKSGEN field. */
#define CCM_INTENCLR_ENDKSGEN_Msk (0x1UL << CCM_INTENCLR_ENDKSGEN_Pos) /*!< Bit mask of ENDKSGEN field. */
#define CCM_INTENCLR_ENDKSGEN_Disabled (0UL) /*!< Read: Disabled */
#define CCM_INTENCLR_ENDKSGEN_Enabled (1UL) /*!< Read: Enabled */
#define CCM_INTENCLR_ENDKSGEN_Clear (1UL) /*!< Disable */

/* Register: CCM_MICSTATUS */
/* Description: MIC check result */

/* Bit 0 : The result of the MIC check performed during the previous decryption operation */
#define CCM_MICSTATUS_MICSTATUS_Pos (0UL) /*!< Position of MICSTATUS field. */
#define CCM_MICSTATUS_MICSTATUS_Msk (0x1UL << CCM_MICSTATUS_MICSTATUS_Pos) /*!< Bit mask of MICSTATUS field. */
#define CCM_MICSTATUS_MICSTATUS_CheckFailed (0UL) /*!< MIC check failed */
#define CCM_MICSTATUS_MICSTATUS_CheckPassed (1UL) /*!< MIC check passed */

/* Register: CCM_ENABLE */
/* Description: Enable */

/* Bits 1..0 : Enable or disable CCM */
#define CCM_ENABLE_ENABLE_Pos (0UL) /*!< Position of ENABLE field. */
#define CCM_ENABLE_ENABLE_Msk (0x3UL << CCM_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define CCM_ENABLE_ENABLE_Disabled (0UL) /*!< Disable */
#define CCM_ENABLE_ENABLE_Enabled (2UL) /*!< Enable */

/* Register: CCM_MODE */
/* Description: Operation mode */

/* Bit 24 : Packet length configuration */
#define CCM_MODE_LENGTH_Pos (24UL) /*!< Position of LENGTH field. */
#define CCM_MODE_LENGTH_Msk (0x1UL << CCM_MODE_LENGTH_Pos) /*!< Bit mask of LENGTH field. */
#define CCM_MODE_LENGTH_Default (0UL) /*!< Default length. Effective length of LENGTH field in encrypted/decrypted packet is 5 bits. A key-stream for packets up to 27 bytes will be generated. */
#define CCM_MODE_LENGTH_Extended (1UL) /*!< Extended length. Effective length of LENGTH field in encrypted/decrypted packet is 8 bits. A key-stream for packets up to MAXPACKETSIZE bytes will be generated. */

/* Bits 17..16 : Radio data rate that the CCM shall run synchronous with */
#define CCM_MODE_DATARATE_Pos (16UL) /*!< Position of DATARATE field. */
#define CCM_MODE_DATARATE_Msk (0x3UL << CCM_MODE_DATARATE_Pos) /*!< Bit mask of DATARATE field. */
#define CCM_MODE_DATARATE_1Mbit (0UL) /*!< 1 Mbps */
#define CCM_MODE_DATARATE_2Mbit (1UL) /*!< 2 Mbps */
#define CCM_MODE_DATARATE_125Kbps (2UL) /*!< 125 Kbps */
#define CCM_MODE_DATARATE_500Kbps (3UL) /*!< 500 Kbps */

/* Bit 0 : The mode of operation to be used. The settings in this register apply whenever either the KSGEN or CRYPT tasks are triggered. */
#define CCM_MODE_MODE_Pos (0UL) /*!< Position of MODE field. */
#define CCM_MODE_MODE_Msk (0x1UL << CCM_MODE_MODE_Pos) /*!< Bit mask of MODE field. */
#define CCM_MODE_MODE_Encryption (0UL) /*!< AES CCM packet encryption mode */
#define CCM_MODE_MODE_Decryption (1UL) /*!< AES CCM packet decryption mode */

/* Register: CCM_CNFPTR */
/* Description: Pointer to data structure holding AES key and NONCE vector */

/* Bits 31..0 : Pointer to the data structure holding the AES key and the CCM NONCE vector (see Table 1 CCM data structure overview) */
#define CCM_CNFPTR_CNFPTR_Pos (0UL) /*!< Position of CNFPTR field. */
#define CCM_CNFPTR_CNFPTR_Msk (0xFFFFFFFFUL << CCM_CNFPTR_CNFPTR_Pos) /*!< Bit mask of CNFPTR field. */

/* Register: CCM_INPTR */
/* Description: Input pointer */

/* Bits 31..0 : Input pointer */
#define CCM_INPTR_INPTR_Pos (0UL) /*!< Position of INPTR field. */
#define CCM_INPTR_INPTR_Msk (0xFFFFFFFFUL << CCM_INPTR_INPTR_Pos) /*!< Bit mask of INPTR field. */

/* Register: CCM_OUTPTR */
/* Description: Output pointer */

/* Bits 31..0 : Output pointer */
#define CCM_OUTPTR_OUTPTR_Pos (0UL) /*!< Position of OUTPTR field. */
#define CCM_OUTPTR_OUTPTR_Msk (0xFFFFFFFFUL << CCM_OUTPTR_OUTPTR_Pos) /*!< Bit mask of OUTPTR field. */

/* Register: CCM_SCRATCHPTR */
/* Description: Pointer to data area used for temporary storage */

/* Bits 31..0 : Pointer to a scratch data area used for temporary storage during key-stream generation, MIC generation and encryption/decryption. */
#define CCM_SCRATCHPTR_SCRATCHPTR_Pos (0UL) /*!< Position of SCRATCHPTR field. */
#define CCM_SCRATCHPTR_SCRATCHPTR_Msk (0xFFFFFFFFUL << CCM_SCRATCHPTR_SCRATCHPTR_Pos) /*!< Bit mask of SCRATCHPTR field. */

/* Register: CCM_MAXPACKETSIZE */
/* Description: Length of key-stream generated when MODE.LENGTH = Extended. */

/* Bits 7..0 : Length of key-stream generated when MODE.LENGTH = Extended. This value must be greater or equal to the subsequent packet to be encrypted/decrypted. */
#define CCM_MAXPACKETSIZE_MAXPACKETSIZE_Pos (0UL) /*!< Position of MAXPACKETSIZE field. */
#define CCM_MAXPACKETSIZE_MAXPACKETSIZE_Msk (0xFFUL << CCM_MAXPACKETSIZE_MAXPACKETSIZE_Pos) /*!< Bit mask of MAXPACKETSIZE field. */

/* Register: CCM_RATEOVERRIDE */
/* Description: Data rate override setting. */

/* Bits 1..0 : Data rate override setting. */
#define CCM_RATEOVERRIDE_RATEOVERRIDE_Pos (0UL) /*!< Position of RATEOVERRIDE field. */
#define CCM_RATEOVERRIDE_RATEOVERRIDE_Msk (0x3UL << CCM_RATEOVERRIDE_RATEOVERRIDE_Pos) /*!< Bit mask of RATEOVERRIDE field. */
#define CCM_RATEOVERRIDE_RATEOVERRIDE_1Mbit (0UL) /*!< 1 Mbps */
#define CCM_RATEOVERRIDE_RATEOVERRIDE_2Mbit (1UL) /*!< 2 Mbps */
#define CCM_RATEOVERRIDE_RATEOVERRIDE_125Kbps (2UL) /*!< 125 Kbps */
#define CCM_RATEOVERRIDE_RATEOVERRIDE_500Kbps (3UL) /*!< 500 Kbps */


/* Peripheral: CLOCK */
/* Description: Clock control */

/* Register: CLOCK_INTENSET */
/* Description: Enable interrupt */

/* Bit 4 : Write '1' to Enable interrupt for CTTO event */
#define CLOCK_INTENSET_CTTO_Pos (4UL) /*!< Position of CTTO field. */
#define CLOCK_INTENSET_CTTO_Msk (0x1UL << CLOCK_INTENSET_CTTO_Pos) /*!< Bit mask of CTTO field. */
#define CLOCK_INTENSET_CTTO_Disabled (0UL) /*!< Read: Disabled */
#define CLOCK_INTENSET_CTTO_Enabled (1UL) /*!< Read: Enabled */
#define CLOCK_INTENSET_CTTO_Set (1UL) /*!< Enable */

/* Bit 3 : Write '1' to Enable interrupt for DONE event */
#define CLOCK_INTENSET_DONE_Pos (3UL) /*!< Position of DONE field. */
#define CLOCK_INTENSET_DONE_Msk (0x1UL << CLOCK_INTENSET_DONE_Pos) /*!< Bit mask of DONE field. */
#define CLOCK_INTENSET_DONE_Disabled (0UL) /*!< Read: Disabled */
#define CLOCK_INTENSET_DONE_Enabled (1UL) /*!< Read: Enabled */
#define CLOCK_INTENSET_DONE_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable interrupt for LFCLKSTARTED event */
#define CLOCK_INTENSET_LFCLKSTARTED_Pos (1UL) /*!< Position of LFCLKSTARTED field. */
#define CLOCK_INTENSET_LFCLKSTARTED_Msk (0x1UL << CLOCK_INTENSET_LFCLKSTARTED_Pos) /*!< Bit mask of LFCLKSTARTED field. */
#define CLOCK_INTENSET_LFCLKSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define CLOCK_INTENSET_LFCLKSTARTED_Enabled (1UL) /*!< Read: Enabled */
#define CLOCK_INTENSET_LFCLKSTARTED_Set (1UL) /*!< Enable */

/* Bit 0 : Write '1' to Enable interrupt for HFCLKSTARTED event */
#define CLOCK_INTENSET_HFCLKSTARTED_Pos (0UL) /*!< Position of HFCLKSTARTED field. */
#define CLOCK_INTENSET_HFCLKSTARTED_Msk (0x1UL << CLOCK_INTENSET_HFCLKSTARTED_Pos) /*!< Bit mask of HFCLKSTARTED field. */
#define CLOCK_INTENSET_HFCLKSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define CLOCK_INTENSET_HFCLKSTARTED_Enabled (1UL) /*!< Read: Enabled */
#define CLOCK_INTENSET_HFCLKSTARTED_Set (1UL) /*!< Enable */

/* Register: CLOCK_INTENCLR */
/* Description: Disable interrupt */

/* Bit 4 : Write '1' to Disable interrupt for CTTO event */
#define CLOCK_INTENCLR_CTTO_Pos (4UL) /*!< Position of CTTO field. */
#define CLOCK_INTENCLR_CTTO_Msk (0x1UL << CLOCK_INTENCLR_CTTO_Pos) /*!< Bit mask of CTTO field. */
#define CLOCK_INTENCLR_CTTO_Disabled (0UL) /*!< Read: Disabled */
#define CLOCK_INTENCLR_CTTO_Enabled (1UL) /*!< Read: Enabled */
#define CLOCK_INTENCLR_CTTO_Clear (1UL) /*!< Disable */

/* Bit 3 : Write '1' to Disable interrupt for DONE event */
#define CLOCK_INTENCLR_DONE_Pos (3UL) /*!< Position of DONE field. */
#define CLOCK_INTENCLR_DONE_Msk (0x1UL << CLOCK_INTENCLR_DONE_Pos) /*!< Bit mask of DONE field. */
#define CLOCK_INTENCLR_DONE_Disabled (0UL) /*!< Read: Disabled */
#define CLOCK_INTENCLR_DONE_Enabled (1UL) /*!< Read: Enabled */
#define CLOCK_INTENCLR_DONE_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable interrupt for LFCLKSTARTED event */
#define CLOCK_INTENCLR_LFCLKSTARTED_Pos (1UL) /*!< Position of LFCLKSTARTED field. */
#define CLOCK_INTENCLR_LFCLKSTARTED_Msk (0x1UL << CLOCK_INTENCLR_LFCLKSTARTED_Pos) /*!< Bit mask of LFCLKSTARTED field. */
#define CLOCK_INTENCLR_LFCLKSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define CLOCK_INTENCLR_LFCLKSTARTED_Enabled (1UL) /*!< Read: Enabled */
#define CLOCK_INTENCLR_LFCLKSTARTED_Clear (1UL) /*!< Disable */

/* Bit 0 : Write '1' to Disable interrupt for HFCLKSTARTED event */
#define CLOCK_INTENCLR_HFCLKSTARTED_Pos (0UL) /*!< Position of HFCLKSTARTED field. */
#define CLOCK_INTENCLR_HFCLKSTARTED_Msk (0x1UL << CLOCK_INTENCLR_HFCLKSTARTED_Pos) /*!< Bit mask of HFCLKSTARTED field. */
#define CLOCK_INTENCLR_HFCLKSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define CLOCK_INTENCLR_HFCLKSTARTED_Enabled (1UL) /*!< Read: Enabled */
#define CLOCK_INTENCLR_HFCLKSTARTED_Clear (1UL) /*!< Disable */

/* Register: CLOCK_HFCLKRUN */
/* Description: Status indicating that HFCLKSTART task has been triggered */

/* Bit 0 : HFCLKSTART task triggered or not */
#define CLOCK_HFCLKRUN_STATUS_Pos (0UL) /*!< Position of STATUS field. */
#define CLOCK_HFCLKRUN_STATUS_Msk (0x1UL << CLOCK_HFCLKRUN_STATUS_Pos) /*!< Bit mask of STATUS field. */
#define CLOCK_HFCLKRUN_STATUS_NotTriggered (0UL) /*!< Task not triggered */
#define CLOCK_HFCLKRUN_STATUS_Triggered (1UL) /*!< Task triggered */

/* Register: CLOCK_HFCLKSTAT */
/* Description: HFCLK status */

/* Bit 16 : HFCLK state */
#define CLOCK_HFCLKSTAT_STATE_Pos (16UL) /*!< Position of STATE field. */
#define CLOCK_HFCLKSTAT_STATE_Msk (0x1UL << CLOCK_HFCLKSTAT_STATE_Pos) /*!< Bit mask of STATE field. */
#define CLOCK_HFCLKSTAT_STATE_NotRunning (0UL) /*!< HFCLK not running */
#define CLOCK_HFCLKSTAT_STATE_Running (1UL) /*!< HFCLK running */

/* Bit 0 : Source of HFCLK */
#define CLOCK_HFCLKSTAT_SRC_Pos (0UL) /*!< Position of SRC field. */
#define CLOCK_HFCLKSTAT_SRC_Msk (0x1UL << CLOCK_HFCLKSTAT_SRC_Pos) /*!< Bit mask of SRC field. */
#define CLOCK_HFCLKSTAT_SRC_RC (0UL) /*!< 64 MHz internal oscillator (HFINT) */
#define CLOCK_HFCLKSTAT_SRC_Xtal (1UL) /*!< 64 MHz crystal oscillator (HFXO) */

/* Register: CLOCK_LFCLKRUN */
/* Description: Status indicating that LFCLKSTART task has been triggered */

/* Bit 0 : LFCLKSTART task triggered or not */
#define CLOCK_LFCLKRUN_STATUS_Pos (0UL) /*!< Position of STATUS field. */
#define CLOCK_LFCLKRUN_STATUS_Msk (0x1UL << CLOCK_LFCLKRUN_STATUS_Pos) /*!< Bit mask of STATUS field. */
#define CLOCK_LFCLKRUN_STATUS_NotTriggered (0UL) /*!< Task not triggered */
#define CLOCK_LFCLKRUN_STATUS_Triggered (1UL) /*!< Task triggered */

/* Register: CLOCK_LFCLKSTAT */
/* Description: LFCLK status */

/* Bit 16 : LFCLK state */
#define CLOCK_LFCLKSTAT_STATE_Pos (16UL) /*!< Position of STATE field. */
#define CLOCK_LFCLKSTAT_STATE_Msk (0x1UL << CLOCK_LFCLKSTAT_STATE_Pos) /*!< Bit mask of STATE field. */
#define CLOCK_LFCLKSTAT_STATE_NotRunning (0UL) /*!< LFCLK not running */
#define CLOCK_LFCLKSTAT_STATE_Running (1UL) /*!< LFCLK running */

/* Bits 1..0 : Source of LFCLK */
#define CLOCK_LFCLKSTAT_SRC_Pos (0UL) /*!< Position of SRC field. */
#define CLOCK_LFCLKSTAT_SRC_Msk (0x3UL << CLOCK_LFCLKSTAT_SRC_Pos) /*!< Bit mask of SRC field. */
#define CLOCK_LFCLKSTAT_SRC_RC (0UL) /*!< 32.768 kHz RC oscillator */
#define CLOCK_LFCLKSTAT_SRC_Xtal (1UL) /*!< 32.768 kHz crystal oscillator */
#define CLOCK_LFCLKSTAT_SRC_Synth (2UL) /*!< 32.768 kHz synthesized from HFCLK */
#define CLOCK_LFCLKSTAT_SRC_LFULP (3UL) /*!< 32.768 kHz ultra low power RC oscillator */

/* Register: CLOCK_LFCLKSRCCOPY */
/* Description: Copy of LFCLKSRC register, set when LFCLKSTART task was triggered */

/* Bits 1..0 : Clock source */
#define CLOCK_LFCLKSRCCOPY_SRC_Pos (0UL) /*!< Position of SRC field. */
#define CLOCK_LFCLKSRCCOPY_SRC_Msk (0x3UL << CLOCK_LFCLKSRCCOPY_SRC_Pos) /*!< Bit mask of SRC field. */
#define CLOCK_LFCLKSRCCOPY_SRC_RC (0UL) /*!< 32.768 kHz RC oscillator */
#define CLOCK_LFCLKSRCCOPY_SRC_Xtal (1UL) /*!< 32.768 kHz crystal oscillator */
#define CLOCK_LFCLKSRCCOPY_SRC_Synth (2UL) /*!< 32.768 kHz synthesized from HFCLK */
#define CLOCK_LFCLKSRCCOPY_SRC_LFULP (3UL) /*!< 32.768 kHz ultra low power RC oscillator */

/* Register: CLOCK_LFCLKSRC */
/* Description: Clock source for the LFCLK */

/* Bit 17 : Enable or disable external source for LFCLK */
#define CLOCK_LFCLKSRC_EXTERNAL_Pos (17UL) /*!< Position of EXTERNAL field. */
#define CLOCK_LFCLKSRC_EXTERNAL_Msk (0x1UL << CLOCK_LFCLKSRC_EXTERNAL_Pos) /*!< Bit mask of EXTERNAL field. */
#define CLOCK_LFCLKSRC_EXTERNAL_Disabled (0UL) /*!< Disable external source (use with Xtal) */
#define CLOCK_LFCLKSRC_EXTERNAL_Enabled (1UL) /*!< Enable use of external source instead of Xtal (SRC needs to be set to Xtal) */

/* Bit 16 : Enable or disable bypass of LFCLK crystal oscillator with external clock source */
#define CLOCK_LFCLKSRC_BYPASS_Pos (16UL) /*!< Position of BYPASS field. */
#define CLOCK_LFCLKSRC_BYPASS_Msk (0x1UL << CLOCK_LFCLKSRC_BYPASS_Pos) /*!< Bit mask of BYPASS field. */
#define CLOCK_LFCLKSRC_BYPASS_Disabled (0UL) /*!< Disable (use with Xtal or low-swing external source) */
#define CLOCK_LFCLKSRC_BYPASS_Enabled (1UL) /*!< Enable (use with rail-to-rail external source) */

/* Bits 1..0 : Clock source */
#define CLOCK_LFCLKSRC_SRC_Pos (0UL) /*!< Position of SRC field. */
#define CLOCK_LFCLKSRC_SRC_Msk (0x3UL << CLOCK_LFCLKSRC_SRC_Pos) /*!< Bit mask of SRC field. */
#define CLOCK_LFCLKSRC_SRC_RC (0UL) /*!< 32.768 kHz RC oscillator */
#define CLOCK_LFCLKSRC_SRC_Xtal (1UL) /*!< 32.768 kHz crystal oscillator */
#define CLOCK_LFCLKSRC_SRC_Synth (2UL) /*!< 32.768 kHz synthesized from HFCLK */
#define CLOCK_LFCLKSRC_SRC_LFULP (3UL) /*!< 32.768 kHz ultra low power RC oscillator */

/* Register: CLOCK_CTIV */
/* Description: Calibration timer interval */

/* Bits 6..0 : Calibration timer interval in multiple of 0.25 seconds. Range: 0.25 seconds to 31.75 seconds. */
#define CLOCK_CTIV_CTIV_Pos (0UL) /*!< Position of CTIV field. */
#define CLOCK_CTIV_CTIV_Msk (0x7FUL << CLOCK_CTIV_CTIV_Pos) /*!< Bit mask of CTIV field. */

/* Register: CLOCK_TRACECONFIG */
/* Description: Clocking options for the Trace Port debug interface */

/* Bits 17..16 : Pin multiplexing of trace signals. */
#define CLOCK_TRACECONFIG_TRACEMUX_Pos (16UL) /*!< Position of TRACEMUX field. */
#define CLOCK_TRACECONFIG_TRACEMUX_Msk (0x3UL << CLOCK_TRACECONFIG_TRACEMUX_Pos) /*!< Bit mask of TRACEMUX field. */
#define CLOCK_TRACECONFIG_TRACEMUX_GPIO (0UL) /*!< GPIOs multiplexed onto all trace-pins */
#define CLOCK_TRACECONFIG_TRACEMUX_Serial (1UL) /*!< SWO multiplexed onto P0.18, GPIO multiplexed onto other trace pins */
#define CLOCK_TRACECONFIG_TRACEMUX_Parallel (2UL) /*!< TRACECLK and TRACEDATA multiplexed onto P0.20, P0.18, P0.16, P0.15 and P0.14. */

/* Bits 1..0 : Speed of Trace Port clock. Note that the TRACECLK pin will output this clock divided by two. */
#define CLOCK_TRACECONFIG_TRACEPORTSPEED_Pos (0UL) /*!< Position of TRACEPORTSPEED field. */
#define CLOCK_TRACECONFIG_TRACEPORTSPEED_Msk (0x3UL << CLOCK_TRACECONFIG_TRACEPORTSPEED_Pos) /*!< Bit mask of TRACEPORTSPEED field. */
#define CLOCK_TRACECONFIG_TRACEPORTSPEED_32MHz (0UL) /*!< 32 MHz Trace Port clock (TRACECLK = 16 MHz) */
#define CLOCK_TRACECONFIG_TRACEPORTSPEED_16MHz (1UL) /*!< 16 MHz Trace Port clock (TRACECLK = 8 MHz) */
#define CLOCK_TRACECONFIG_TRACEPORTSPEED_8MHz (2UL) /*!< 8 MHz Trace Port clock (TRACECLK = 4 MHz) */
#define CLOCK_TRACECONFIG_TRACEPORTSPEED_4MHz (3UL) /*!< 4 MHz Trace Port clock (TRACECLK = 2 MHz) */


/* Peripheral: COMP */
/* Description: Comparator */

/* Register: COMP_SHORTS */
/* Description: Shortcut register */

/* Bit 4 : Shortcut between CROSS event and STOP task */
#define COMP_SHORTS_CROSS_STOP_Pos (4UL) /*!< Position of CROSS_STOP field. */
#define COMP_SHORTS_CROSS_STOP_Msk (0x1UL << COMP_SHORTS_CROSS_STOP_Pos) /*!< Bit mask of CROSS_STOP field. */
#define COMP_SHORTS_CROSS_STOP_Disabled (0UL) /*!< Disable shortcut */
#define COMP_SHORTS_CROSS_STOP_Enabled (1UL) /*!< Enable shortcut */

/* Bit 3 : Shortcut between UP event and STOP task */
#define COMP_SHORTS_UP_STOP_Pos (3UL) /*!< Position of UP_STOP field. */
#define COMP_SHORTS_UP_STOP_Msk (0x1UL << COMP_SHORTS_UP_STOP_Pos) /*!< Bit mask of UP_STOP field. */
#define COMP_SHORTS_UP_STOP_Disabled (0UL) /*!< Disable shortcut */
#define COMP_SHORTS_UP_STOP_Enabled (1UL) /*!< Enable shortcut */

/* Bit 2 : Shortcut between DOWN event and STOP task */
#define COMP_SHORTS_DOWN_STOP_Pos (2UL) /*!< Position of DOWN_STOP field. */
#define COMP_SHORTS_DOWN_STOP_Msk (0x1UL << COMP_SHORTS_DOWN_STOP_Pos) /*!< Bit mask of DOWN_STOP field. */
#define COMP_SHORTS_DOWN_STOP_Disabled (0UL) /*!< Disable shortcut */
#define COMP_SHORTS_DOWN_STOP_Enabled (1UL) /*!< Enable shortcut */

/* Bit 1 : Shortcut between READY event and STOP task */
#define COMP_SHORTS_READY_STOP_Pos (1UL) /*!< Position of READY_STOP field. */
#define COMP_SHORTS_READY_STOP_Msk (0x1UL << COMP_SHORTS_READY_STOP_Pos) /*!< Bit mask of READY_STOP field. */
#define COMP_SHORTS_READY_STOP_Disabled (0UL) /*!< Disable shortcut */
#define COMP_SHORTS_READY_STOP_Enabled (1UL) /*!< Enable shortcut */

/* Bit 0 : Shortcut between READY event and SAMPLE task */
#define COMP_SHORTS_READY_SAMPLE_Pos (0UL) /*!< Position of READY_SAMPLE field. */
#define COMP_SHORTS_READY_SAMPLE_Msk (0x1UL << COMP_SHORTS_READY_SAMPLE_Pos) /*!< Bit mask of READY_SAMPLE field. */
#define COMP_SHORTS_READY_SAMPLE_Disabled (0UL) /*!< Disable shortcut */
#define COMP_SHORTS_READY_SAMPLE_Enabled (1UL) /*!< Enable shortcut */

/* Register: COMP_INTEN */
/* Description: Enable or disable interrupt */

/* Bit 3 : Enable or disable interrupt for CROSS event */
#define COMP_INTEN_CROSS_Pos (3UL) /*!< Position of CROSS field. */
#define COMP_INTEN_CROSS_Msk (0x1UL << COMP_INTEN_CROSS_Pos) /*!< Bit mask of CROSS field. */
#define COMP_INTEN_CROSS_Disabled (0UL) /*!< Disable */
#define COMP_INTEN_CROSS_Enabled (1UL) /*!< Enable */

/* Bit 2 : Enable or disable interrupt for UP event */
#define COMP_INTEN_UP_Pos (2UL) /*!< Position of UP field. */
#define COMP_INTEN_UP_Msk (0x1UL << COMP_INTEN_UP_Pos) /*!< Bit mask of UP field. */
#define COMP_INTEN_UP_Disabled (0UL) /*!< Disable */
#define COMP_INTEN_UP_Enabled (1UL) /*!< Enable */

/* Bit 1 : Enable or disable interrupt for DOWN event */
#define COMP_INTEN_DOWN_Pos (1UL) /*!< Position of DOWN field. */
#define COMP_INTEN_DOWN_Msk (0x1UL << COMP_INTEN_DOWN_Pos) /*!< Bit mask of DOWN field. */
#define COMP_INTEN_DOWN_Disabled (0UL) /*!< Disable */
#define COMP_INTEN_DOWN_Enabled (1UL) /*!< Enable */

/* Bit 0 : Enable or disable interrupt for READY event */
#define COMP_INTEN_READY_Pos (0UL) /*!< Position of READY field. */
#define COMP_INTEN_READY_Msk (0x1UL << COMP_INTEN_READY_Pos) /*!< Bit mask of READY field. */
#define COMP_INTEN_READY_Disabled (0UL) /*!< Disable */
#define COMP_INTEN_READY_Enabled (1UL) /*!< Enable */

/* Register: COMP_INTENSET */
/* Description: Enable interrupt */

/* Bit 3 : Write '1' to Enable interrupt for CROSS event */
#define COMP_INTENSET_CROSS_Pos (3UL) /*!< Position of CROSS field. */
#define COMP_INTENSET_CROSS_Msk (0x1UL << COMP_INTENSET_CROSS_Pos) /*!< Bit mask of CROSS field. */
#define COMP_INTENSET_CROSS_Disabled (0UL) /*!< Read: Disabled */
#define COMP_INTENSET_CROSS_Enabled (1UL) /*!< Read: Enabled */
#define COMP_INTENSET_CROSS_Set (1UL) /*!< Enable */

/* Bit 2 : Write '1' to Enable interrupt for UP event */
#define COMP_INTENSET_UP_Pos (2UL) /*!< Position of UP field. */
#define COMP_INTENSET_UP_Msk (0x1UL << COMP_INTENSET_UP_Pos) /*!< Bit mask of UP field. */
#define COMP_INTENSET_UP_Disabled (0UL) /*!< Read: Disabled */
#define COMP_INTENSET_UP_Enabled (1UL) /*!< Read: Enabled */
#define COMP_INTENSET_UP_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable interrupt for DOWN event */
#define COMP_INTENSET_DOWN_Pos (1UL) /*!< Position of DOWN field. */
#define COMP_INTENSET_DOWN_Msk (0x1UL << COMP_INTENSET_DOWN_Pos) /*!< Bit mask of DOWN field. */
#define COMP_INTENSET_DOWN_Disabled (0UL) /*!< Read: Disabled */
#define COMP_INTENSET_DOWN_Enabled (1UL) /*!< Read: Enabled */
#define COMP_INTENSET_DOWN_Set (1UL) /*!< Enable */

/* Bit 0 : Write '1' to Enable interrupt for READY event */
#define COMP_INTENSET_READY_Pos (0UL) /*!< Position of READY field. */
#define COMP_INTENSET_READY_Msk (0x1UL << COMP_INTENSET_READY_Pos) /*!< Bit mask of READY field. */
#define COMP_INTENSET_READY_Disabled (0UL) /*!< Read: Disabled */
#define COMP_INTENSET_READY_Enabled (1UL) /*!< Read: Enabled */
#define COMP_INTENSET_READY_Set (1UL) /*!< Enable */

/* Register: COMP_INTENCLR */
/* Description: Disable interrupt */

/* Bit 3 : Write '1' to Disable interrupt for CROSS event */
#define COMP_INTENCLR_CROSS_Pos (3UL) /*!< Position of CROSS field. */
#define COMP_INTENCLR_CROSS_Msk (0x1UL << COMP_INTENCLR_CROSS_Pos) /*!< Bit mask of CROSS field. */
#define COMP_INTENCLR_CROSS_Disabled (0UL) /*!< Read: Disabled */
#define COMP_INTENCLR_CROSS_Enabled (1UL) /*!< Read: Enabled */
#define COMP_INTENCLR_CROSS_Clear (1UL) /*!< Disable */

/* Bit 2 : Write '1' to Disable interrupt for UP event */
#define COMP_INTENCLR_UP_Pos (2UL) /*!< Position of UP field. */
#define COMP_INTENCLR_UP_Msk (0x1UL << COMP_INTENCLR_UP_Pos) /*!< Bit mask of UP field. */
#define COMP_INTENCLR_UP_Disabled (0UL) /*!< Read: Disabled */
#define COMP_INTENCLR_UP_Enabled (1UL) /*!< Read: Enabled */
#define COMP_INTENCLR_UP_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable interrupt for DOWN event */
#define COMP_INTENCLR_DOWN_Pos (1UL) /*!< Position of DOWN field. */
#define COMP_INTENCLR_DOWN_Msk (0x1UL << COMP_INTENCLR_DOWN_Pos) /*!< Bit mask of DOWN field. */
#define COMP_INTENCLR_DOWN_Disabled (0UL) /*!< Read: Disabled */
#define COMP_INTENCLR_DOWN_Enabled (1UL) /*!< Read: Enabled */
#define COMP_INTENCLR_DOWN_Clear (1UL) /*!< Disable */

/* Bit 0 : Write '1' to Disable interrupt for READY event */
#define COMP_INTENCLR_READY_Pos (0UL) /*!< Position of READY field. */
#define COMP_INTENCLR_READY_Msk (0x1UL << COMP_INTENCLR_READY_Pos) /*!< Bit mask of READY field. */
#define COMP_INTENCLR_READY_Disabled (0UL) /*!< Read: Disabled */
#define COMP_INTENCLR_READY_Enabled (1UL) /*!< Read: Enabled */
#define COMP_INTENCLR_READY_Clear (1UL) /*!< Disable */

/* Register: COMP_RESULT */
/* Description: Compare result */

/* Bit 0 : Result of last compare. Decision point SAMPLE task. */
#define COMP_RESULT_RESULT_Pos (0UL) /*!< Position of RESULT field. */
#define COMP_RESULT_RESULT_Msk (0x1UL << COMP_RESULT_RESULT_Pos) /*!< Bit mask of RESULT field. */
#define COMP_RESULT_RESULT_Below (0UL) /*!< Input voltage is below the threshold (VIN+ &lt; VIN-) */
#define COMP_RESULT_RESULT_Above (1UL) /*!< Input voltage is above the threshold (VIN+ &gt; VIN-) */

/* Register: COMP_ENABLE */
/* Description: COMP enable */

/* Bits 1..0 : Enable or disable COMP */
#define COMP_ENABLE_ENABLE_Pos (0UL) /*!< Position of ENABLE field. */
#define COMP_ENABLE_ENABLE_Msk (0x3UL << COMP_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define COMP_ENABLE_ENABLE_Disabled (0UL) /*!< Disable */
#define COMP_ENABLE_ENABLE_Enabled (2UL) /*!< Enable */

/* Register: COMP_PSEL */
/* Description: Pin select */

/* Bits 2..0 : Analog pin select */
#define COMP_PSEL_PSEL_Pos (0UL) /*!< Position of PSEL field. */
#define COMP_PSEL_PSEL_Msk (0x7UL << COMP_PSEL_PSEL_Pos) /*!< Bit mask of PSEL field. */
#define COMP_PSEL_PSEL_AnalogInput0 (0UL) /*!< AIN0 selected as analog input */
#define COMP_PSEL_PSEL_AnalogInput1 (1UL) /*!< AIN1 selected as analog input */
#define COMP_PSEL_PSEL_AnalogInput2 (2UL) /*!< AIN2 selected as analog input */
#define COMP_PSEL_PSEL_AnalogInput3 (3UL) /*!< AIN3 selected as analog input */
#define COMP_PSEL_PSEL_AnalogInput4 (4UL) /*!< AIN4 selected as analog input */
#define COMP_PSEL_PSEL_AnalogInput5 (5UL) /*!< AIN5 selected as analog input */
#define COMP_PSEL_PSEL_AnalogInput6 (6UL) /*!< AIN6 selected as analog input */
#define COMP_PSEL_PSEL_AnalogInput7 (7UL) /*!< AIN7 selected as analog input */

/* Register: COMP_REFSEL */
/* Description: Reference source select */

/* Bits 2..0 : Reference select */
#define COMP_REFSEL_REFSEL_Pos (0UL) /*!< Position of REFSEL field. */
#define COMP_REFSEL_REFSEL_Msk (0x7UL << COMP_REFSEL_REFSEL_Pos) /*!< Bit mask of REFSEL field. */
#define COMP_REFSEL_REFSEL_Int1V2 (0UL) /*!< VREF = internal 1.2 V reference (VDD &gt;= 1.7 V) */
#define COMP_REFSEL_REFSEL_Int1V8 (1UL) /*!< VREF = internal 1.8 V reference (VDD &gt;= VREF + 0.2 V) */
#define COMP_REFSEL_REFSEL_Int2V4 (2UL) /*!< VREF = internal 2.4 V reference (VDD &gt;= VREF + 0.2 V) */
#define COMP_REFSEL_REFSEL_VDD (4UL) /*!< VREF = VDD */
#define COMP_REFSEL_REFSEL_ARef (7UL) /*!< VREF = AREF (VDD &gt;= VREF &gt;= AREFMIN) */

/* Register: COMP_EXTREFSEL */
/* Description: External reference select */

/* Bit 0 : External analog reference select */
#define COMP_EXTREFSEL_EXTREFSEL_Pos (0UL) /*!< Position of EXTREFSEL field. */
#define COMP_EXTREFSEL_EXTREFSEL_Msk (0x1UL << COMP_EXTREFSEL_EXTREFSEL_Pos) /*!< Bit mask of EXTREFSEL field. */
#define COMP_EXTREFSEL_EXTREFSEL_AnalogReference0 (0UL) /*!< Use AIN0 as external analog reference */
#define COMP_EXTREFSEL_EXTREFSEL_AnalogReference1 (1UL) /*!< Use AIN1 as external analog reference */

/* Register: COMP_TH */
/* Description: Threshold configuration for hysteresis unit */

/* Bits 13..8 : VUP = (THUP+1)/64*VREF */
#define COMP_TH_THUP_Pos (8UL) /*!< Position of THUP field. */
#define COMP_TH_THUP_Msk (0x3FUL << COMP_TH_THUP_Pos) /*!< Bit mask of THUP field. */

/* Bits 5..0 : VDOWN = (THDOWN+1)/64*VREF */
#define COMP_TH_THDOWN_Pos (0UL) /*!< Position of THDOWN field. */
#define COMP_TH_THDOWN_Msk (0x3FUL << COMP_TH_THDOWN_Pos) /*!< Bit mask of THDOWN field. */

/* Register: COMP_MODE */
/* Description: Mode configuration */

/* Bit 8 : Main operation mode */
#define COMP_MODE_MAIN_Pos (8UL) /*!< Position of MAIN field. */
#define COMP_MODE_MAIN_Msk (0x1UL << COMP_MODE_MAIN_Pos) /*!< Bit mask of MAIN field. */
#define COMP_MODE_MAIN_SE (0UL) /*!< Single ended mode */
#define COMP_MODE_MAIN_Diff (1UL) /*!< Differential mode */

/* Bits 1..0 : Speed and power mode */
#define COMP_MODE_SP_Pos (0UL) /*!< Position of SP field. */
#define COMP_MODE_SP_Msk (0x3UL << COMP_MODE_SP_Pos) /*!< Bit mask of SP field. */
#define COMP_MODE_SP_Low (0UL) /*!< Low power mode */
#define COMP_MODE_SP_Normal (1UL) /*!< Normal mode */
#define COMP_MODE_SP_High (2UL) /*!< High speed mode */

/* Register: COMP_HYST */
/* Description: Comparator hysteresis enable */

/* Bit 0 : Comparator hysteresis */
#define COMP_HYST_HYST_Pos (0UL) /*!< Position of HYST field. */
#define COMP_HYST_HYST_Msk (0x1UL << COMP_HYST_HYST_Pos) /*!< Bit mask of HYST field. */
#define COMP_HYST_HYST_NoHyst (0UL) /*!< Comparator hysteresis disabled */
#define COMP_HYST_HYST_Hyst50mV (1UL) /*!< Comparator hysteresis enabled */

/* Register: COMP_ISOURCE */
/* Description: Current source select on analog input */

/* Bits 1..0 : Comparator hysteresis */
#define COMP_ISOURCE_ISOURCE_Pos (0UL) /*!< Position of ISOURCE field. */
#define COMP_ISOURCE_ISOURCE_Msk (0x3UL << COMP_ISOURCE_ISOURCE_Pos) /*!< Bit mask of ISOURCE field. */
#define COMP_ISOURCE_ISOURCE_Off (0UL) /*!< Current source disabled */
#define COMP_ISOURCE_ISOURCE_Ien2mA5 (1UL) /*!< Current source enabled (+/- 2.5 uA) */
#define COMP_ISOURCE_ISOURCE_Ien5mA (2UL) /*!< Current source enabled (+/- 5 uA) */
#define COMP_ISOURCE_ISOURCE_Ien10mA (3UL) /*!< Current source enabled (+/- 10 uA) */


/* Peripheral: CRYPTOCELL */
/* Description: ARM CryptoCell register interface */

/* Register: CRYPTOCELL_ENABLE */
/* Description: Control power and clock for ARM CryptoCell subsystem */

/* Bit 0 : Enable or disable the CryptoCell subsystem */
#define CRYPTOCELL_ENABLE_ENABLE_Pos (0UL) /*!< Position of ENABLE field. */
#define CRYPTOCELL_ENABLE_ENABLE_Msk (0x1UL << CRYPTOCELL_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define CRYPTOCELL_ENABLE_ENABLE_Disabled (0UL) /*!< CryptoCell subsystem disabled */
#define CRYPTOCELL_ENABLE_ENABLE_Enabled (1UL) /*!< CryptoCell subsystem enabled */


/* Peripheral: ECB */
/* Description: AES ECB Mode Encryption */

/* Register: ECB_INTENSET */
/* Description: Enable interrupt */

/* Bit 1 : Write '1' to Enable interrupt for ERRORECB event */
#define ECB_INTENSET_ERRORECB_Pos (1UL) /*!< Position of ERRORECB field. */
#define ECB_INTENSET_ERRORECB_Msk (0x1UL << ECB_INTENSET_ERRORECB_Pos) /*!< Bit mask of ERRORECB field. */
#define ECB_INTENSET_ERRORECB_Disabled (0UL) /*!< Read: Disabled */
#define ECB_INTENSET_ERRORECB_Enabled (1UL) /*!< Read: Enabled */
#define ECB_INTENSET_ERRORECB_Set (1UL) /*!< Enable */

/* Bit 0 : Write '1' to Enable interrupt for ENDECB event */
#define ECB_INTENSET_ENDECB_Pos (0UL) /*!< Position of ENDECB field. */
#define ECB_INTENSET_ENDECB_Msk (0x1UL << ECB_INTENSET_ENDECB_Pos) /*!< Bit mask of ENDECB field. */
#define ECB_INTENSET_ENDECB_Disabled (0UL) /*!< Read: Disabled */
#define ECB_INTENSET_ENDECB_Enabled (1UL) /*!< Read: Enabled */
#define ECB_INTENSET_ENDECB_Set (1UL) /*!< Enable */

/* Register: ECB_INTENCLR */
/* Description: Disable interrupt */

/* Bit 1 : Write '1' to Disable interrupt for ERRORECB event */
#define ECB_INTENCLR_ERRORECB_Pos (1UL) /*!< Position of ERRORECB field. */
#define ECB_INTENCLR_ERRORECB_Msk (0x1UL << ECB_INTENCLR_ERRORECB_Pos) /*!< Bit mask of ERRORECB field. */
#define ECB_INTENCLR_ERRORECB_Disabled (0UL) /*!< Read: Disabled */
#define ECB_INTENCLR_ERRORECB_Enabled (1UL) /*!< Read: Enabled */
#define ECB_INTENCLR_ERRORECB_Clear (1UL) /*!< Disable */

/* Bit 0 : Write '1' to Disable interrupt for ENDECB event */
#define ECB_INTENCLR_ENDECB_Pos (0UL) /*!< Position of ENDECB field. */
#define ECB_INTENCLR_ENDECB_Msk (0x1UL << ECB_INTENCLR_ENDECB_Pos) /*!< Bit mask of ENDECB field. */
#define ECB_INTENCLR_ENDECB_Disabled (0UL) /*!< Read: Disabled */
#define ECB_INTENCLR_ENDECB_Enabled (1UL) /*!< Read: Enabled */
#define ECB_INTENCLR_ENDECB_Clear (1UL) /*!< Disable */

/* Register: ECB_ECBDATAPTR */
/* Description: ECB block encrypt memory pointers */

/* Bits 31..0 : Pointer to the ECB data structure (see Table 1 ECB data structure overview) */
#define ECB_ECBDATAPTR_ECBDATAPTR_Pos (0UL) /*!< Position of ECBDATAPTR field. */
#define ECB_ECBDATAPTR_ECBDATAPTR_Msk (0xFFFFFFFFUL << ECB_ECBDATAPTR_ECBDATAPTR_Pos) /*!< Bit mask of ECBDATAPTR field. */


/* Peripheral: EGU */
/* Description: Event Generator Unit 0 */

/* Register: EGU_INTEN */
/* Description: Enable or disable interrupt */

/* Bit 15 : Enable or disable interrupt for TRIGGERED[15] event */
#define EGU_INTEN_TRIGGERED15_Pos (15UL) /*!< Position of TRIGGERED15 field. */
#define EGU_INTEN_TRIGGERED15_Msk (0x1UL << EGU_INTEN_TRIGGERED15_Pos) /*!< Bit mask of TRIGGERED15 field. */
#define EGU_INTEN_TRIGGERED15_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED15_Enabled (1UL) /*!< Enable */

/* Bit 14 : Enable or disable interrupt for TRIGGERED[14] event */
#define EGU_INTEN_TRIGGERED14_Pos (14UL) /*!< Position of TRIGGERED14 field. */
#define EGU_INTEN_TRIGGERED14_Msk (0x1UL << EGU_INTEN_TRIGGERED14_Pos) /*!< Bit mask of TRIGGERED14 field. */
#define EGU_INTEN_TRIGGERED14_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED14_Enabled (1UL) /*!< Enable */

/* Bit 13 : Enable or disable interrupt for TRIGGERED[13] event */
#define EGU_INTEN_TRIGGERED13_Pos (13UL) /*!< Position of TRIGGERED13 field. */
#define EGU_INTEN_TRIGGERED13_Msk (0x1UL << EGU_INTEN_TRIGGERED13_Pos) /*!< Bit mask of TRIGGERED13 field. */
#define EGU_INTEN_TRIGGERED13_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED13_Enabled (1UL) /*!< Enable */

/* Bit 12 : Enable or disable interrupt for TRIGGERED[12] event */
#define EGU_INTEN_TRIGGERED12_Pos (12UL) /*!< Position of TRIGGERED12 field. */
#define EGU_INTEN_TRIGGERED12_Msk (0x1UL << EGU_INTEN_TRIGGERED12_Pos) /*!< Bit mask of TRIGGERED12 field. */
#define EGU_INTEN_TRIGGERED12_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED12_Enabled (1UL) /*!< Enable */

/* Bit 11 : Enable or disable interrupt for TRIGGERED[11] event */
#define EGU_INTEN_TRIGGERED11_Pos (11UL) /*!< Position of TRIGGERED11 field. */
#define EGU_INTEN_TRIGGERED11_Msk (0x1UL << EGU_INTEN_TRIGGERED11_Pos) /*!< Bit mask of TRIGGERED11 field. */
#define EGU_INTEN_TRIGGERED11_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED11_Enabled (1UL) /*!< Enable */

/* Bit 10 : Enable or disable interrupt for TRIGGERED[10] event */
#define EGU_INTEN_TRIGGERED10_Pos (10UL) /*!< Position of TRIGGERED10 field. */
#define EGU_INTEN_TRIGGERED10_Msk (0x1UL << EGU_INTEN_TRIGGERED10_Pos) /*!< Bit mask of TRIGGERED10 field. */
#define EGU_INTEN_TRIGGERED10_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED10_Enabled (1UL) /*!< Enable */

/* Bit 9 : Enable or disable interrupt for TRIGGERED[9] event */
#define EGU_INTEN_TRIGGERED9_Pos (9UL) /*!< Position of TRIGGERED9 field. */
#define EGU_INTEN_TRIGGERED9_Msk (0x1UL << EGU_INTEN_TRIGGERED9_Pos) /*!< Bit mask of TRIGGERED9 field. */
#define EGU_INTEN_TRIGGERED9_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED9_Enabled (1UL) /*!< Enable */

/* Bit 8 : Enable or disable interrupt for TRIGGERED[8] event */
#define EGU_INTEN_TRIGGERED8_Pos (8UL) /*!< Position of TRIGGERED8 field. */
#define EGU_INTEN_TRIGGERED8_Msk (0x1UL << EGU_INTEN_TRIGGERED8_Pos) /*!< Bit mask of TRIGGERED8 field. */
#define EGU_INTEN_TRIGGERED8_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED8_Enabled (1UL) /*!< Enable */

/* Bit 7 : Enable or disable interrupt for TRIGGERED[7] event */
#define EGU_INTEN_TRIGGERED7_Pos (7UL) /*!< Position of TRIGGERED7 field. */
#define EGU_INTEN_TRIGGERED7_Msk (0x1UL << EGU_INTEN_TRIGGERED7_Pos) /*!< Bit mask of TRIGGERED7 field. */
#define EGU_INTEN_TRIGGERED7_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED7_Enabled (1UL) /*!< Enable */

/* Bit 6 : Enable or disable interrupt for TRIGGERED[6] event */
#define EGU_INTEN_TRIGGERED6_Pos (6UL) /*!< Position of TRIGGERED6 field. */
#define EGU_INTEN_TRIGGERED6_Msk (0x1UL << EGU_INTEN_TRIGGERED6_Pos) /*!< Bit mask of TRIGGERED6 field. */
#define EGU_INTEN_TRIGGERED6_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED6_Enabled (1UL) /*!< Enable */

/* Bit 5 : Enable or disable interrupt for TRIGGERED[5] event */
#define EGU_INTEN_TRIGGERED5_Pos (5UL) /*!< Position of TRIGGERED5 field. */
#define EGU_INTEN_TRIGGERED5_Msk (0x1UL << EGU_INTEN_TRIGGERED5_Pos) /*!< Bit mask of TRIGGERED5 field. */
#define EGU_INTEN_TRIGGERED5_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED5_Enabled (1UL) /*!< Enable */

/* Bit 4 : Enable or disable interrupt for TRIGGERED[4] event */
#define EGU_INTEN_TRIGGERED4_Pos (4UL) /*!< Position of TRIGGERED4 field. */
#define EGU_INTEN_TRIGGERED4_Msk (0x1UL << EGU_INTEN_TRIGGERED4_Pos) /*!< Bit mask of TRIGGERED4 field. */
#define EGU_INTEN_TRIGGERED4_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED4_Enabled (1UL) /*!< Enable */

/* Bit 3 : Enable or disable interrupt for TRIGGERED[3] event */
#define EGU_INTEN_TRIGGERED3_Pos (3UL) /*!< Position of TRIGGERED3 field. */
#define EGU_INTEN_TRIGGERED3_Msk (0x1UL << EGU_INTEN_TRIGGERED3_Pos) /*!< Bit mask of TRIGGERED3 field. */
#define EGU_INTEN_TRIGGERED3_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED3_Enabled (1UL) /*!< Enable */

/* Bit 2 : Enable or disable interrupt for TRIGGERED[2] event */
#define EGU_INTEN_TRIGGERED2_Pos (2UL) /*!< Position of TRIGGERED2 field. */
#define EGU_INTEN_TRIGGERED2_Msk (0x1UL << EGU_INTEN_TRIGGERED2_Pos) /*!< Bit mask of TRIGGERED2 field. */
#define EGU_INTEN_TRIGGERED2_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED2_Enabled (1UL) /*!< Enable */

/* Bit 1 : Enable or disable interrupt for TRIGGERED[1] event */
#define EGU_INTEN_TRIGGERED1_Pos (1UL) /*!< Position of TRIGGERED1 field. */
#define EGU_INTEN_TRIGGERED1_Msk (0x1UL << EGU_INTEN_TRIGGERED1_Pos) /*!< Bit mask of TRIGGERED1 field. */
#define EGU_INTEN_TRIGGERED1_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED1_Enabled (1UL) /*!< Enable */

/* Bit 0 : Enable or disable interrupt for TRIGGERED[0] event */
#define EGU_INTEN_TRIGGERED0_Pos (0UL) /*!< Position of TRIGGERED0 field. */
#define EGU_INTEN_TRIGGERED0_Msk (0x1UL << EGU_INTEN_TRIGGERED0_Pos) /*!< Bit mask of TRIGGERED0 field. */
#define EGU_INTEN_TRIGGERED0_Disabled (0UL) /*!< Disable */
#define EGU_INTEN_TRIGGERED0_Enabled (1UL) /*!< Enable */

/* Register: EGU_INTENSET */
/* Description: Enable interrupt */

/* Bit 15 : Write '1' to Enable interrupt for TRIGGERED[15] event */
#define EGU_INTENSET_TRIGGERED15_Pos (15UL) /*!< Position of TRIGGERED15 field. */
#define EGU_INTENSET_TRIGGERED15_Msk (0x1UL << EGU_INTENSET_TRIGGERED15_Pos) /*!< Bit mask of TRIGGERED15 field. */
#define EGU_INTENSET_TRIGGERED15_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED15_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED15_Set (1UL) /*!< Enable */

/* Bit 14 : Write '1' to Enable interrupt for TRIGGERED[14] event */
#define EGU_INTENSET_TRIGGERED14_Pos (14UL) /*!< Position of TRIGGERED14 field. */
#define EGU_INTENSET_TRIGGERED14_Msk (0x1UL << EGU_INTENSET_TRIGGERED14_Pos) /*!< Bit mask of TRIGGERED14 field. */
#define EGU_INTENSET_TRIGGERED14_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED14_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED14_Set (1UL) /*!< Enable */

/* Bit 13 : Write '1' to Enable interrupt for TRIGGERED[13] event */
#define EGU_INTENSET_TRIGGERED13_Pos (13UL) /*!< Position of TRIGGERED13 field. */
#define EGU_INTENSET_TRIGGERED13_Msk (0x1UL << EGU_INTENSET_TRIGGERED13_Pos) /*!< Bit mask of TRIGGERED13 field. */
#define EGU_INTENSET_TRIGGERED13_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED13_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED13_Set (1UL) /*!< Enable */

/* Bit 12 : Write '1' to Enable interrupt for TRIGGERED[12] event */
#define EGU_INTENSET_TRIGGERED12_Pos (12UL) /*!< Position of TRIGGERED12 field. */
#define EGU_INTENSET_TRIGGERED12_Msk (0x1UL << EGU_INTENSET_TRIGGERED12_Pos) /*!< Bit mask of TRIGGERED12 field. */
#define EGU_INTENSET_TRIGGERED12_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED12_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED12_Set (1UL) /*!< Enable */

/* Bit 11 : Write '1' to Enable interrupt for TRIGGERED[11] event */
#define EGU_INTENSET_TRIGGERED11_Pos (11UL) /*!< Position of TRIGGERED11 field. */
#define EGU_INTENSET_TRIGGERED11_Msk (0x1UL << EGU_INTENSET_TRIGGERED11_Pos) /*!< Bit mask of TRIGGERED11 field. */
#define EGU_INTENSET_TRIGGERED11_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED11_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED11_Set (1UL) /*!< Enable */

/* Bit 10 : Write '1' to Enable interrupt for TRIGGERED[10] event */
#define EGU_INTENSET_TRIGGERED10_Pos (10UL) /*!< Position of TRIGGERED10 field. */
#define EGU_INTENSET_TRIGGERED10_Msk (0x1UL << EGU_INTENSET_TRIGGERED10_Pos) /*!< Bit mask of TRIGGERED10 field. */
#define EGU_INTENSET_TRIGGERED10_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED10_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED10_Set (1UL) /*!< Enable */

/* Bit 9 : Write '1' to Enable interrupt for TRIGGERED[9] event */
#define EGU_INTENSET_TRIGGERED9_Pos (9UL) /*!< Position of TRIGGERED9 field. */
#define EGU_INTENSET_TRIGGERED9_Msk (0x1UL << EGU_INTENSET_TRIGGERED9_Pos) /*!< Bit mask of TRIGGERED9 field. */
#define EGU_INTENSET_TRIGGERED9_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED9_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED9_Set (1UL) /*!< Enable */

/* Bit 8 : Write '1' to Enable interrupt for TRIGGERED[8] event */
#define EGU_INTENSET_TRIGGERED8_Pos (8UL) /*!< Position of TRIGGERED8 field. */
#define EGU_INTENSET_TRIGGERED8_Msk (0x1UL << EGU_INTENSET_TRIGGERED8_Pos) /*!< Bit mask of TRIGGERED8 field. */
#define EGU_INTENSET_TRIGGERED8_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED8_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED8_Set (1UL) /*!< Enable */

/* Bit 7 : Write '1' to Enable interrupt for TRIGGERED[7] event */
#define EGU_INTENSET_TRIGGERED7_Pos (7UL) /*!< Position of TRIGGERED7 field. */
#define EGU_INTENSET_TRIGGERED7_Msk (0x1UL << EGU_INTENSET_TRIGGERED7_Pos) /*!< Bit mask of TRIGGERED7 field. */
#define EGU_INTENSET_TRIGGERED7_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED7_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED7_Set (1UL) /*!< Enable */

/* Bit 6 : Write '1' to Enable interrupt for TRIGGERED[6] event */
#define EGU_INTENSET_TRIGGERED6_Pos (6UL) /*!< Position of TRIGGERED6 field. */
#define EGU_INTENSET_TRIGGERED6_Msk (0x1UL << EGU_INTENSET_TRIGGERED6_Pos) /*!< Bit mask of TRIGGERED6 field. */
#define EGU_INTENSET_TRIGGERED6_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED6_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED6_Set (1UL) /*!< Enable */

/* Bit 5 : Write '1' to Enable interrupt for TRIGGERED[5] event */
#define EGU_INTENSET_TRIGGERED5_Pos (5UL) /*!< Position of TRIGGERED5 field. */
#define EGU_INTENSET_TRIGGERED5_Msk (0x1UL << EGU_INTENSET_TRIGGERED5_Pos) /*!< Bit mask of TRIGGERED5 field. */
#define EGU_INTENSET_TRIGGERED5_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED5_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED5_Set (1UL) /*!< Enable */

/* Bit 4 : Write '1' to Enable interrupt for TRIGGERED[4] event */
#define EGU_INTENSET_TRIGGERED4_Pos (4UL) /*!< Position of TRIGGERED4 field. */
#define EGU_INTENSET_TRIGGERED4_Msk (0x1UL << EGU_INTENSET_TRIGGERED4_Pos) /*!< Bit mask of TRIGGERED4 field. */
#define EGU_INTENSET_TRIGGERED4_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED4_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED4_Set (1UL) /*!< Enable */

/* Bit 3 : Write '1' to Enable interrupt for TRIGGERED[3] event */
#define EGU_INTENSET_TRIGGERED3_Pos (3UL) /*!< Position of TRIGGERED3 field. */
#define EGU_INTENSET_TRIGGERED3_Msk (0x1UL << EGU_INTENSET_TRIGGERED3_Pos) /*!< Bit mask of TRIGGERED3 field. */
#define EGU_INTENSET_TRIGGERED3_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED3_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED3_Set (1UL) /*!< Enable */

/* Bit 2 : Write '1' to Enable interrupt for TRIGGERED[2] event */
#define EGU_INTENSET_TRIGGERED2_Pos (2UL) /*!< Position of TRIGGERED2 field. */
#define EGU_INTENSET_TRIGGERED2_Msk (0x1UL << EGU_INTENSET_TRIGGERED2_Pos) /*!< Bit mask of TRIGGERED2 field. */
#define EGU_INTENSET_TRIGGERED2_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED2_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED2_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable interrupt for TRIGGERED[1] event */
#define EGU_INTENSET_TRIGGERED1_Pos (1UL) /*!< Position of TRIGGERED1 field. */
#define EGU_INTENSET_TRIGGERED1_Msk (0x1UL << EGU_INTENSET_TRIGGERED1_Pos) /*!< Bit mask of TRIGGERED1 field. */
#define EGU_INTENSET_TRIGGERED1_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED1_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED1_Set (1UL) /*!< Enable */

/* Bit 0 : Write '1' to Enable interrupt for TRIGGERED[0] event */
#define EGU_INTENSET_TRIGGERED0_Pos (0UL) /*!< Position of TRIGGERED0 field. */
#define EGU_INTENSET_TRIGGERED0_Msk (0x1UL << EGU_INTENSET_TRIGGERED0_Pos) /*!< Bit mask of TRIGGERED0 field. */
#define EGU_INTENSET_TRIGGERED0_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENSET_TRIGGERED0_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENSET_TRIGGERED0_Set (1UL) /*!< Enable */

/* Register: EGU_INTENCLR */
/* Description: Disable interrupt */

/* Bit 15 : Write '1' to Disable interrupt for TRIGGERED[15] event */
#define EGU_INTENCLR_TRIGGERED15_Pos (15UL) /*!< Position of TRIGGERED15 field. */
#define EGU_INTENCLR_TRIGGERED15_Msk (0x1UL << EGU_INTENCLR_TRIGGERED15_Pos) /*!< Bit mask of TRIGGERED15 field. */
#define EGU_INTENCLR_TRIGGERED15_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED15_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED15_Clear (1UL) /*!< Disable */

/* Bit 14 : Write '1' to Disable interrupt for TRIGGERED[14] event */
#define EGU_INTENCLR_TRIGGERED14_Pos (14UL) /*!< Position of TRIGGERED14 field. */
#define EGU_INTENCLR_TRIGGERED14_Msk (0x1UL << EGU_INTENCLR_TRIGGERED14_Pos) /*!< Bit mask of TRIGGERED14 field. */
#define EGU_INTENCLR_TRIGGERED14_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED14_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED14_Clear (1UL) /*!< Disable */

/* Bit 13 : Write '1' to Disable interrupt for TRIGGERED[13] event */
#define EGU_INTENCLR_TRIGGERED13_Pos (13UL) /*!< Position of TRIGGERED13 field. */
#define EGU_INTENCLR_TRIGGERED13_Msk (0x1UL << EGU_INTENCLR_TRIGGERED13_Pos) /*!< Bit mask of TRIGGERED13 field. */
#define EGU_INTENCLR_TRIGGERED13_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED13_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED13_Clear (1UL) /*!< Disable */

/* Bit 12 : Write '1' to Disable interrupt for TRIGGERED[12] event */
#define EGU_INTENCLR_TRIGGERED12_Pos (12UL) /*!< Position of TRIGGERED12 field. */
#define EGU_INTENCLR_TRIGGERED12_Msk (0x1UL << EGU_INTENCLR_TRIGGERED12_Pos) /*!< Bit mask of TRIGGERED12 field. */
#define EGU_INTENCLR_TRIGGERED12_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED12_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED12_Clear (1UL) /*!< Disable */

/* Bit 11 : Write '1' to Disable interrupt for TRIGGERED[11] event */
#define EGU_INTENCLR_TRIGGERED11_Pos (11UL) /*!< Position of TRIGGERED11 field. */
#define EGU_INTENCLR_TRIGGERED11_Msk (0x1UL << EGU_INTENCLR_TRIGGERED11_Pos) /*!< Bit mask of TRIGGERED11 field. */
#define EGU_INTENCLR_TRIGGERED11_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED11_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED11_Clear (1UL) /*!< Disable */

/* Bit 10 : Write '1' to Disable interrupt for TRIGGERED[10] event */
#define EGU_INTENCLR_TRIGGERED10_Pos (10UL) /*!< Position of TRIGGERED10 field. */
#define EGU_INTENCLR_TRIGGERED10_Msk (0x1UL << EGU_INTENCLR_TRIGGERED10_Pos) /*!< Bit mask of TRIGGERED10 field. */
#define EGU_INTENCLR_TRIGGERED10_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED10_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED10_Clear (1UL) /*!< Disable */

/* Bit 9 : Write '1' to Disable interrupt for TRIGGERED[9] event */
#define EGU_INTENCLR_TRIGGERED9_Pos (9UL) /*!< Position of TRIGGERED9 field. */
#define EGU_INTENCLR_TRIGGERED9_Msk (0x1UL << EGU_INTENCLR_TRIGGERED9_Pos) /*!< Bit mask of TRIGGERED9 field. */
#define EGU_INTENCLR_TRIGGERED9_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED9_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED9_Clear (1UL) /*!< Disable */

/* Bit 8 : Write '1' to Disable interrupt for TRIGGERED[8] event */
#define EGU_INTENCLR_TRIGGERED8_Pos (8UL) /*!< Position of TRIGGERED8 field. */
#define EGU_INTENCLR_TRIGGERED8_Msk (0x1UL << EGU_INTENCLR_TRIGGERED8_Pos) /*!< Bit mask of TRIGGERED8 field. */
#define EGU_INTENCLR_TRIGGERED8_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED8_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED8_Clear (1UL) /*!< Disable */

/* Bit 7 : Write '1' to Disable interrupt for TRIGGERED[7] event */
#define EGU_INTENCLR_TRIGGERED7_Pos (7UL) /*!< Position of TRIGGERED7 field. */
#define EGU_INTENCLR_TRIGGERED7_Msk (0x1UL << EGU_INTENCLR_TRIGGERED7_Pos) /*!< Bit mask of TRIGGERED7 field. */
#define EGU_INTENCLR_TRIGGERED7_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED7_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED7_Clear (1UL) /*!< Disable */

/* Bit 6 : Write '1' to Disable interrupt for TRIGGERED[6] event */
#define EGU_INTENCLR_TRIGGERED6_Pos (6UL) /*!< Position of TRIGGERED6 field. */
#define EGU_INTENCLR_TRIGGERED6_Msk (0x1UL << EGU_INTENCLR_TRIGGERED6_Pos) /*!< Bit mask of TRIGGERED6 field. */
#define EGU_INTENCLR_TRIGGERED6_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED6_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED6_Clear (1UL) /*!< Disable */

/* Bit 5 : Write '1' to Disable interrupt for TRIGGERED[5] event */
#define EGU_INTENCLR_TRIGGERED5_Pos (5UL) /*!< Position of TRIGGERED5 field. */
#define EGU_INTENCLR_TRIGGERED5_Msk (0x1UL << EGU_INTENCLR_TRIGGERED5_Pos) /*!< Bit mask of TRIGGERED5 field. */
#define EGU_INTENCLR_TRIGGERED5_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED5_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED5_Clear (1UL) /*!< Disable */

/* Bit 4 : Write '1' to Disable interrupt for TRIGGERED[4] event */
#define EGU_INTENCLR_TRIGGERED4_Pos (4UL) /*!< Position of TRIGGERED4 field. */
#define EGU_INTENCLR_TRIGGERED4_Msk (0x1UL << EGU_INTENCLR_TRIGGERED4_Pos) /*!< Bit mask of TRIGGERED4 field. */
#define EGU_INTENCLR_TRIGGERED4_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED4_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED4_Clear (1UL) /*!< Disable */

/* Bit 3 : Write '1' to Disable interrupt for TRIGGERED[3] event */
#define EGU_INTENCLR_TRIGGERED3_Pos (3UL) /*!< Position of TRIGGERED3 field. */
#define EGU_INTENCLR_TRIGGERED3_Msk (0x1UL << EGU_INTENCLR_TRIGGERED3_Pos) /*!< Bit mask of TRIGGERED3 field. */
#define EGU_INTENCLR_TRIGGERED3_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED3_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED3_Clear (1UL) /*!< Disable */

/* Bit 2 : Write '1' to Disable interrupt for TRIGGERED[2] event */
#define EGU_INTENCLR_TRIGGERED2_Pos (2UL) /*!< Position of TRIGGERED2 field. */
#define EGU_INTENCLR_TRIGGERED2_Msk (0x1UL << EGU_INTENCLR_TRIGGERED2_Pos) /*!< Bit mask of TRIGGERED2 field. */
#define EGU_INTENCLR_TRIGGERED2_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED2_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED2_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable interrupt for TRIGGERED[1] event */
#define EGU_INTENCLR_TRIGGERED1_Pos (1UL) /*!< Position of TRIGGERED1 field. */
#define EGU_INTENCLR_TRIGGERED1_Msk (0x1UL << EGU_INTENCLR_TRIGGERED1_Pos) /*!< Bit mask of TRIGGERED1 field. */
#define EGU_INTENCLR_TRIGGERED1_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED1_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED1_Clear (1UL) /*!< Disable */

/* Bit 0 : Write '1' to Disable interrupt for TRIGGERED[0] event */
#define EGU_INTENCLR_TRIGGERED0_Pos (0UL) /*!< Position of TRIGGERED0 field. */
#define EGU_INTENCLR_TRIGGERED0_Msk (0x1UL << EGU_INTENCLR_TRIGGERED0_Pos) /*!< Bit mask of TRIGGERED0 field. */
#define EGU_INTENCLR_TRIGGERED0_Disabled (0UL) /*!< Read: Disabled */
#define EGU_INTENCLR_TRIGGERED0_Enabled (1UL) /*!< Read: Enabled */
#define EGU_INTENCLR_TRIGGERED0_Clear (1UL) /*!< Disable */


/* Peripheral: FICR */
/* Description: Factory Information Configuration Registers */

/* Register: FICR_CODEPAGESIZE */
/* Description: Code memory page size */

/* Bits 31..0 : Code memory page size */
#define FICR_CODEPAGESIZE_CODEPAGESIZE_Pos (0UL) /*!< Position of CODEPAGESIZE field. */
#define FICR_CODEPAGESIZE_CODEPAGESIZE_Msk (0xFFFFFFFFUL << FICR_CODEPAGESIZE_CODEPAGESIZE_Pos) /*!< Bit mask of CODEPAGESIZE field. */

/* Register: FICR_CODESIZE */
/* Description: Code memory size */

/* Bits 31..0 : Code memory size in number of pages */
#define FICR_CODESIZE_CODESIZE_Pos (0UL) /*!< Position of CODESIZE field. */
#define FICR_CODESIZE_CODESIZE_Msk (0xFFFFFFFFUL << FICR_CODESIZE_CODESIZE_Pos) /*!< Bit mask of CODESIZE field. */

/* Register: FICR_DEVICEID */
/* Description: Description collection[0]:  Device identifier */

/* Bits 31..0 : 64 bit unique device identifier */
#define FICR_DEVICEID_DEVICEID_Pos (0UL) /*!< Position of DEVICEID field. */
#define FICR_DEVICEID_DEVICEID_Msk (0xFFFFFFFFUL << FICR_DEVICEID_DEVICEID_Pos) /*!< Bit mask of DEVICEID field. */

/* Register: FICR_ER */
/* Description: Description collection[0]:  Encryption root, word 0 */

/* Bits 31..0 : Encryption root, word 0 */
#define FICR_ER_ER_Pos (0UL) /*!< Position of ER field. */
#define FICR_ER_ER_Msk (0xFFFFFFFFUL << FICR_ER_ER_Pos) /*!< Bit mask of ER field. */

/* Register: FICR_IR */
/* Description: Description collection[0]:  Identity Root, word 0 */

/* Bits 31..0 : Identity Root, word 0 */
#define FICR_IR_IR_Pos (0UL) /*!< Position of IR field. */
#define FICR_IR_IR_Msk (0xFFFFFFFFUL << FICR_IR_IR_Pos) /*!< Bit mask of IR field. */

/* Register: FICR_DEVICEADDRTYPE */
/* Description: Device address type */

/* Bit 0 : Device address type */
#define FICR_DEVICEADDRTYPE_DEVICEADDRTYPE_Pos (0UL) /*!< Position of DEVICEADDRTYPE field. */
#define FICR_DEVICEADDRTYPE_DEVICEADDRTYPE_Msk (0x1UL << FICR_DEVICEADDRTYPE_DEVICEADDRTYPE_Pos) /*!< Bit mask of DEVICEADDRTYPE field. */
#define FICR_DEVICEADDRTYPE_DEVICEADDRTYPE_Public (0UL) /*!< Public address */
#define FICR_DEVICEADDRTYPE_DEVICEADDRTYPE_Random (1UL) /*!< Random address */

/* Register: FICR_DEVICEADDR */
/* Description: Description collection[0]:  Device address 0 */

/* Bits 31..0 : 48 bit device address */
#define FICR_DEVICEADDR_DEVICEADDR_Pos (0UL) /*!< Position of DEVICEADDR field. */
#define FICR_DEVICEADDR_DEVICEADDR_Msk (0xFFFFFFFFUL << FICR_DEVICEADDR_DEVICEADDR_Pos) /*!< Bit mask of DEVICEADDR field. */

/* Register: FICR_INFO_PART */
/* Description: Part code */

/* Bits 31..0 : Part code */
#define FICR_INFO_PART_PART_Pos (0UL) /*!< Position of PART field. */
#define FICR_INFO_PART_PART_Msk (0xFFFFFFFFUL << FICR_INFO_PART_PART_Pos) /*!< Bit mask of PART field. */
#define FICR_INFO_PART_PART_N52840 (0x52840UL) /*!< nRF52840 */
#define FICR_INFO_PART_PART_Unspecified (0xFFFFFFFFUL) /*!< Unspecified */

/* Register: FICR_INFO_VARIANT */
/* Description: Part variant (hardware version and production configuration). */

/* Bits 31..0 : Part variant (hardware version and production configuration). Encoded as ASCII. */
#define FICR_INFO_VARIANT_VARIANT_Pos (0UL) /*!< Position of VARIANT field. */
#define FICR_INFO_VARIANT_VARIANT_Msk (0xFFFFFFFFUL << FICR_INFO_VARIANT_VARIANT_Pos) /*!< Bit mask of VARIANT field. */
#define FICR_INFO_VARIANT_VARIANT_AAAA (0x41414141UL) /*!< AAAA */
#define FICR_INFO_VARIANT_VARIANT_AAAB (0x41414142UL) /*!< AAAB */
#define FICR_INFO_VARIANT_VARIANT_AAB0 (0x41414230UL) /*!< AAB0 */
#define FICR_INFO_VARIANT_VARIANT_AABA (0x41414241UL) /*!< AABA */
#define FICR_INFO_VARIANT_VARIANT_AABB (0x41414242UL) /*!< AABB */
#define FICR_INFO_VARIANT_VARIANT_ABBA (0x41424241UL) /*!< ABBA */
#define FICR_INFO_VARIANT_VARIANT_Unspecified (0xFFFFFFFFUL) /*!< Unspecified */

/* Register: FICR_INFO_PACKAGE */
/* Description: Package option */

/* Bits 31..0 : Package option */
#define FICR_INFO_PACKAGE_PACKAGE_Pos (0UL) /*!< Position of PACKAGE field. */
#define FICR_INFO_PACKAGE_PACKAGE_Msk (0xFFFFFFFFUL << FICR_INFO_PACKAGE_PACKAGE_Pos) /*!< Bit mask of PACKAGE field. */
#define FICR_INFO_PACKAGE_PACKAGE_QI (0x2004UL) /*!< QIxx - 73-pin aQFN */
#define FICR_INFO_PACKAGE_PACKAGE_Unspecified (0xFFFFFFFFUL) /*!< Unspecified */

/* Register: FICR_INFO_RAM */
/* Description: RAM variant */

/* Bits 31..0 : RAM variant */
#define FICR_INFO_RAM_RAM_Pos (0UL) /*!< Position of RAM field. */
#define FICR_INFO_RAM_RAM_Msk (0xFFFFFFFFUL << FICR_INFO_RAM_RAM_Pos) /*!< Bit mask of RAM field. */
#define FICR_INFO_RAM_RAM_K16 (0x10UL) /*!< 16 kByte RAM */
#define FICR_INFO_RAM_RAM_K32 (0x20UL) /*!< 32 kByte RAM */
#define FICR_INFO_RAM_RAM_K64 (0x40UL) /*!< 64 kByte RAM */
#define FICR_INFO_RAM_RAM_K128 (0x80UL) /*!< 128 kByte RAM */
#define FICR_INFO_RAM_RAM_K256 (0x100UL) /*!< 256 kByte RAM */
#define FICR_INFO_RAM_RAM_Unspecified (0xFFFFFFFFUL) /*!< Unspecified */

/* Register: FICR_INFO_FLASH */
/* Description: Flash variant */

/* Bits 31..0 : Flash variant */
#define FICR_INFO_FLASH_FLASH_Pos (0UL) /*!< Position of FLASH field. */
#define FICR_INFO_FLASH_FLASH_Msk (0xFFFFFFFFUL << FICR_INFO_FLASH_FLASH_Pos) /*!< Bit mask of FLASH field. */
#define FICR_INFO_FLASH_FLASH_K128 (0x80UL) /*!< 128 kByte FLASH */
#define FICR_INFO_FLASH_FLASH_K256 (0x100UL) /*!< 256 kByte FLASH */
#define FICR_INFO_FLASH_FLASH_K512 (0x200UL) /*!< 512 kByte FLASH */
#define FICR_INFO_FLASH_FLASH_K1024 (0x400UL) /*!< 1 MByte FLASH */
#define FICR_INFO_FLASH_FLASH_K2048 (0x800UL) /*!< 2 MByte FLASH */
#define FICR_INFO_FLASH_FLASH_Unspecified (0xFFFFFFFFUL) /*!< Unspecified */

/* Register: FICR_TEMP_A0 */
/* Description: Slope definition A0. */

/* Bits 11..0 : A (slope definition) register. */
#define FICR_TEMP_A0_A_Pos (0UL) /*!< Position of A field. */
#define FICR_TEMP_A0_A_Msk (0xFFFUL << FICR_TEMP_A0_A_Pos) /*!< Bit mask of A field. */

/* Register: FICR_TEMP_A1 */
/* Description: Slope definition A1. */

/* Bits 11..0 : A (slope definition) register. */
#define FICR_TEMP_A1_A_Pos (0UL) /*!< Position of A field. */
#define FICR_TEMP_A1_A_Msk (0xFFFUL << FICR_TEMP_A1_A_Pos) /*!< Bit mask of A field. */

/* Register: FICR_TEMP_A2 */
/* Description: Slope definition A2. */

/* Bits 11..0 : A (slope definition) register. */
#define FICR_TEMP_A2_A_Pos (0UL) /*!< Position of A field. */
#define FICR_TEMP_A2_A_Msk (0xFFFUL << FICR_TEMP_A2_A_Pos) /*!< Bit mask of A field. */

/* Register: FICR_TEMP_A3 */
/* Description: Slope definition A3. */

/* Bits 11..0 : A (slope definition) register. */
#define FICR_TEMP_A3_A_Pos (0UL) /*!< Position of A field. */
#define FICR_TEMP_A3_A_Msk (0xFFFUL << FICR_TEMP_A3_A_Pos) /*!< Bit mask of A field. */

/* Register: FICR_TEMP_A4 */
/* Description: Slope definition A4. */

/* Bits 11..0 : A (slope definition) register. */
#define FICR_TEMP_A4_A_Pos (0UL) /*!< Position of A field. */
#define FICR_TEMP_A4_A_Msk (0xFFFUL << FICR_TEMP_A4_A_Pos) /*!< Bit mask of A field. */

/* Register: FICR_TEMP_A5 */
/* Description: Slope definition A5. */

/* Bits 11..0 : A (slope definition) register. */
#define FICR_TEMP_A5_A_Pos (0UL) /*!< Position of A field. */
#define FICR_TEMP_A5_A_Msk (0xFFFUL << FICR_TEMP_A5_A_Pos) /*!< Bit mask of A field. */

/* Register: FICR_TEMP_B0 */
/* Description: y-intercept B0. */

/* Bits 13..0 : B (y-intercept) */
#define FICR_TEMP_B0_B_Pos (0UL) /*!< Position of B field. */
#define FICR_TEMP_B0_B_Msk (0x3FFFUL << FICR_TEMP_B0_B_Pos) /*!< Bit mask of B field. */

/* Register: FICR_TEMP_B1 */
/* Description: y-intercept B1. */

/* Bits 13..0 : B (y-intercept) */
#define FICR_TEMP_B1_B_Pos (0UL) /*!< Position of B field. */
#define FICR_TEMP_B1_B_Msk (0x3FFFUL << FICR_TEMP_B1_B_Pos) /*!< Bit mask of B field. */

/* Register: FICR_TEMP_B2 */
/* Description: y-intercept B2. */

/* Bits 13..0 : B (y-intercept) */
#define FICR_TEMP_B2_B_Pos (0UL) /*!< Position of B field. */
#define FICR_TEMP_B2_B_Msk (0x3FFFUL << FICR_TEMP_B2_B_Pos) /*!< Bit mask of B field. */

/* Register: FICR_TEMP_B3 */
/* Description: y-intercept B3. */

/* Bits 13..0 : B (y-intercept) */
#define FICR_TEMP_B3_B_Pos (0UL) /*!< Position of B field. */
#define FICR_TEMP_B3_B_Msk (0x3FFFUL << FICR_TEMP_B3_B_Pos) /*!< Bit mask of B field. */

/* Register: FICR_TEMP_B4 */
/* Description: y-intercept B4. */

/* Bits 13..0 : B (y-intercept) */
#define FICR_TEMP_B4_B_Pos (0UL) /*!< Position of B field. */
#define FICR_TEMP_B4_B_Msk (0x3FFFUL << FICR_TEMP_B4_B_Pos) /*!< Bit mask of B field. */

/* Register: FICR_TEMP_B5 */
/* Description: y-intercept B5. */

/* Bits 13..0 : B (y-intercept) */
#define FICR_TEMP_B5_B_Pos (0UL) /*!< Position of B field. */
#define FICR_TEMP_B5_B_Msk (0x3FFFUL << FICR_TEMP_B5_B_Pos) /*!< Bit mask of B field. */

/* Register: FICR_TEMP_T0 */
/* Description: Segment end T0. */

/* Bits 7..0 : T (segment end)register. */
#define FICR_TEMP_T0_T_Pos (0UL) /*!< Position of T field. */
#define FICR_TEMP_T0_T_Msk (0xFFUL << FICR_TEMP_T0_T_Pos) /*!< Bit mask of T field. */

/* Register: FICR_TEMP_T1 */
/* Description: Segment end T1. */

/* Bits 7..0 : T (segment end)register. */
#define FICR_TEMP_T1_T_Pos (0UL) /*!< Position of T field. */
#define FICR_TEMP_T1_T_Msk (0xFFUL << FICR_TEMP_T1_T_Pos) /*!< Bit mask of T field. */

/* Register: FICR_TEMP_T2 */
/* Description: Segment end T2. */

/* Bits 7..0 : T (segment end)register. */
#define FICR_TEMP_T2_T_Pos (0UL) /*!< Position of T field. */
#define FICR_TEMP_T2_T_Msk (0xFFUL << FICR_TEMP_T2_T_Pos) /*!< Bit mask of T field. */

/* Register: FICR_TEMP_T3 */
/* Description: Segment end T3. */

/* Bits 7..0 : T (segment end)register. */
#define FICR_TEMP_T3_T_Pos (0UL) /*!< Position of T field. */
#define FICR_TEMP_T3_T_Msk (0xFFUL << FICR_TEMP_T3_T_Pos) /*!< Bit mask of T field. */

/* Register: FICR_TEMP_T4 */
/* Description: Segment end T4. */

/* Bits 7..0 : T (segment end)register. */
#define FICR_TEMP_T4_T_Pos (0UL) /*!< Position of T field. */
#define FICR_TEMP_T4_T_Msk (0xFFUL << FICR_TEMP_T4_T_Pos) /*!< Bit mask of T field. */

/* Register: FICR_NFC_TAGHEADER0 */
/* Description: Default header for NFC Tag. Software can read these values to populate NFCID1_3RD_LAST, NFCID1_2ND_LAST and NFCID1_LAST. */

/* Bits 31..24 : Unique identifier byte 3 */
#define FICR_NFC_TAGHEADER0_UD3_Pos (24UL) /*!< Position of UD3 field. */
#define FICR_NFC_TAGHEADER0_UD3_Msk (0xFFUL << FICR_NFC_TAGHEADER0_UD3_Pos) /*!< Bit mask of UD3 field. */

/* Bits 23..16 : Unique identifier byte 2 */
#define FICR_NFC_TAGHEADER0_UD2_Pos (16UL) /*!< Position of UD2 field. */
#define FICR_NFC_TAGHEADER0_UD2_Msk (0xFFUL << FICR_NFC_TAGHEADER0_UD2_Pos) /*!< Bit mask of UD2 field. */

/* Bits 15..8 : Unique identifier byte 1 */
#define FICR_NFC_TAGHEADER0_UD1_Pos (8UL) /*!< Position of UD1 field. */
#define FICR_NFC_TAGHEADER0_UD1_Msk (0xFFUL << FICR_NFC_TAGHEADER0_UD1_Pos) /*!< Bit mask of UD1 field. */

/* Bits 7..0 : Default Manufacturer ID: Nordic Semiconductor ASA has ICM 0x5F */
#define FICR_NFC_TAGHEADER0_MFGID_Pos (0UL) /*!< Position of MFGID field. */
#define FICR_NFC_TAGHEADER0_MFGID_Msk (0xFFUL << FICR_NFC_TAGHEADER0_MFGID_Pos) /*!< Bit mask of MFGID field. */

/* Register: FICR_NFC_TAGHEADER1 */
/* Description: Default header for NFC Tag. Software can read these values to populate NFCID1_3RD_LAST, NFCID1_2ND_LAST and NFCID1_LAST. */

/* Bits 31..24 : Unique identifier byte 7 */
#define FICR_NFC_TAGHEADER1_UD7_Pos (24UL) /*!< Position of UD7 field. */
#define FICR_NFC_TAGHEADER1_UD7_Msk (0xFFUL << FICR_NFC_TAGHEADER1_UD7_Pos) /*!< Bit mask of UD7 field. */

/* Bits 23..16 : Unique identifier byte 6 */
#define FICR_NFC_TAGHEADER1_UD6_Pos (16UL) /*!< Position of UD6 field. */
#define FICR_NFC_TAGHEADER1_UD6_Msk (0xFFUL << FICR_NFC_TAGHEADER1_UD6_Pos) /*!< Bit mask of UD6 field. */

/* Bits 15..8 : Unique identifier byte 5 */
#define FICR_NFC_TAGHEADER1_UD5_Pos (8UL) /*!< Position of UD5 field. */
#define FICR_NFC_TAGHEADER1_UD5_Msk (0xFFUL << FICR_NFC_TAGHEADER1_UD5_Pos) /*!< Bit mask of UD5 field. */

/* Bits 7..0 : Unique identifier byte 4 */
#define FICR_NFC_TAGHEADER1_UD4_Pos (0UL) /*!< Position of UD4 field. */
#define FICR_NFC_TAGHEADER1_UD4_Msk (0xFFUL << FICR_NFC_TAGHEADER1_UD4_Pos) /*!< Bit mask of UD4 field. */

/* Register: FICR_NFC_TAGHEADER2 */
/* Description: Default header for NFC Tag. Software can read these values to populate NFCID1_3RD_LAST, NFCID1_2ND_LAST and NFCID1_LAST. */

/* Bits 31..24 : Unique identifier byte 11 */
#define FICR_NFC_TAGHEADER2_UD11_Pos (24UL) /*!< Position of UD11 field. */
#define FICR_NFC_TAGHEADER2_UD11_Msk (0xFFUL << FICR_NFC_TAGHEADER2_UD11_Pos) /*!< Bit mask of UD11 field. */

/* Bits 23..16 : Unique identifier byte 10 */
#define FICR_NFC_TAGHEADER2_UD10_Pos (16UL) /*!< Position of UD10 field. */
#define FICR_NFC_TAGHEADER2_UD10_Msk (0xFFUL << FICR_NFC_TAGHEADER2_UD10_Pos) /*!< Bit mask of UD10 field. */

/* Bits 15..8 : Unique identifier byte 9 */
#define FICR_NFC_TAGHEADER2_UD9_Pos (8UL) /*!< Position of UD9 field. */
#define FICR_NFC_TAGHEADER2_UD9_Msk (0xFFUL << FICR_NFC_TAGHEADER2_UD9_Pos) /*!< Bit mask of UD9 field. */

/* Bits 7..0 : Unique identifier byte 8 */
#define FICR_NFC_TAGHEADER2_UD8_Pos (0UL) /*!< Position of UD8 field. */
#define FICR_NFC_TAGHEADER2_UD8_Msk (0xFFUL << FICR_NFC_TAGHEADER2_UD8_Pos) /*!< Bit mask of UD8 field. */

/* Register: FICR_NFC_TAGHEADER3 */
/* Description: Default header for NFC Tag. Software can read these values to populate NFCID1_3RD_LAST, NFCID1_2ND_LAST and NFCID1_LAST. */

/* Bits 31..24 : Unique identifier byte 15 */
#define FICR_NFC_TAGHEADER3_UD15_Pos (24UL) /*!< Position of UD15 field. */
#define FICR_NFC_TAGHEADER3_UD15_Msk (0xFFUL << FICR_NFC_TAGHEADER3_UD15_Pos) /*!< Bit mask of UD15 field. */

/* Bits 23..16 : Unique identifier byte 14 */
#define FICR_NFC_TAGHEADER3_UD14_Pos (16UL) /*!< Position of UD14 field. */
#define FICR_NFC_TAGHEADER3_UD14_Msk (0xFFUL << FICR_NFC_TAGHEADER3_UD14_Pos) /*!< Bit mask of UD14 field. */

/* Bits 15..8 : Unique identifier byte 13 */
#define FICR_NFC_TAGHEADER3_UD13_Pos (8UL) /*!< Position of UD13 field. */
#define FICR_NFC_TAGHEADER3_UD13_Msk (0xFFUL << FICR_NFC_TAGHEADER3_UD13_Pos) /*!< Bit mask of UD13 field. */

/* Bits 7..0 : Unique identifier byte 12 */
#define FICR_NFC_TAGHEADER3_UD12_Pos (0UL) /*!< Position of UD12 field. */
#define FICR_NFC_TAGHEADER3_UD12_Msk (0xFFUL << FICR_NFC_TAGHEADER3_UD12_Pos) /*!< Bit mask of UD12 field. */


/* Peripheral: GPIOTE */
/* Description: GPIO Tasks and Events */

/* Register: GPIOTE_INTENSET */
/* Description: Enable interrupt */

/* Bit 31 : Write '1' to Enable interrupt for PORT event */
#define GPIOTE_INTENSET_PORT_Pos (31UL) /*!< Position of PORT field. */
#define GPIOTE_INTENSET_PORT_Msk (0x1UL << GPIOTE_INTENSET_PORT_Pos) /*!< Bit mask of PORT field. */
#define GPIOTE_INTENSET_PORT_Disabled (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENSET_PORT_Enabled (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENSET_PORT_Set (1UL) /*!< Enable */

/* Bit 7 : Write '1' to Enable interrupt for IN[7] event */
#define GPIOTE_INTENSET_IN7_Pos (7UL) /*!< Position of IN7 field. */
#define GPIOTE_INTENSET_IN7_Msk (0x1UL << GPIOTE_INTENSET_IN7_Pos) /*!< Bit mask of IN7 field. */
#define GPIOTE_INTENSET_IN7_Disabled (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENSET_IN7_Enabled (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENSET_IN7_Set (1UL) /*!< Enable */

/* Bit 6 : Write '1' to Enable interrupt for IN[6] event */
#define GPIOTE_INTENSET_IN6_Pos (6UL) /*!< Position of IN6 field. */
#define GPIOTE_INTENSET_IN6_Msk (0x1UL << GPIOTE_INTENSET_IN6_Pos) /*!< Bit mask of IN6 field. */
#define GPIOTE_INTENSET_IN6_Disabled (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENSET_IN6_Enabled (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENSET_IN6_Set (1UL) /*!< Enable */

/* Bit 5 : Write '1' to Enable interrupt for IN[5] event */
#define GPIOTE_INTENSET_IN5_Pos (5UL) /*!< Position of IN5 field. */
#define GPIOTE_INTENSET_IN5_Msk (0x1UL << GPIOTE_INTENSET_IN5_Pos) /*!< Bit mask of IN5 field. */
#define GPIOTE_INTENSET_IN5_Disabled (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENSET_IN5_Enabled (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENSET_IN5_Set (1UL) /*!< Enable */

/* Bit 4 : Write '1' to Enable interrupt for IN[4] event */
#define GPIOTE_INTENSET_IN4_Pos (4UL) /*!< Position of IN4 field. */
#define GPIOTE_INTENSET_IN4_Msk (0x1UL << GPIOTE_INTENSET_IN4_Pos) /*!< Bit mask of IN4 field. */
#define GPIOTE_INTENSET_IN4_Disabled (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENSET_IN4_Enabled (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENSET_IN4_Set (1UL) /*!< Enable */

/* Bit 3 : Write '1' to Enable interrupt for IN[3] event */
#define GPIOTE_INTENSET_IN3_Pos (3UL) /*!< Position of IN3 field. */
#define GPIOTE_INTENSET_IN3_Msk (0x1UL << GPIOTE_INTENSET_IN3_Pos) /*!< Bit mask of IN3 field. */
#define GPIOTE_INTENSET_IN3_Disabled (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENSET_IN3_Enabled (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENSET_IN3_Set (1UL) /*!< Enable */

/* Bit 2 : Write '1' to Enable interrupt for IN[2] event */
#define GPIOTE_INTENSET_IN2_Pos (2UL) /*!< Position of IN2 field. */
#define GPIOTE_INTENSET_IN2_Msk (0x1UL << GPIOTE_INTENSET_IN2_Pos) /*!< Bit mask of IN2 field. */
#define GPIOTE_INTENSET_IN2_Disabled (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENSET_IN2_Enabled (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENSET_IN2_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable interrupt for IN[1] event */
#define GPIOTE_INTENSET_IN1_Pos (1UL) /*!< Position of IN1 field. */
#define GPIOTE_INTENSET_IN1_Msk (0x1UL << GPIOTE_INTENSET_IN1_Pos) /*!< Bit mask of IN1 field. */
#define GPIOTE_INTENSET_IN1_Disabled (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENSET_IN1_Enabled (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENSET_IN1_Set (1UL) /*!< Enable */

/* Bit 0 : Write '1' to Enable interrupt for IN[0] event */
#define GPIOTE_INTENSET_IN0_Pos (0UL) /*!< Position of IN0 field. */
#define GPIOTE_INTENSET_IN0_Msk (0x1UL << GPIOTE_INTENSET_IN0_Pos) /*!< Bit mask of IN0 field. */
#define GPIOTE_INTENSET_IN0_Disabled (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENSET_IN0_Enabled (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENSET_IN0_Set (1UL) /*!< Enable */

/* Register: GPIOTE_INTENCLR */
/* Description: Disable interrupt */

/* Bit 31 : Write '1' to Disable interrupt for PORT event */
#define GPIOTE_INTENCLR_PORT_Pos (31UL) /*!< Position of PORT field. */
#define GPIOTE_INTENCLR_PORT_Msk (0x1UL << GPIOTE_INTENCLR_PORT_Pos) /*!< Bit mask of PORT field. */
#define GPIOTE_INTENCLR_PORT_Disabled (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENCLR_PORT_Enabled (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENCLR_PORT_Clear (1UL) /*!< Disable */

/* Bit 7 : Write '1' to Disable interrupt for IN[7] event */
#define GPIOTE_INTENCLR_IN7_Pos (7UL) /*!< Position of IN7 field. */
#define GPIOTE_INTENCLR_IN7_Msk (0x1UL << GPIOTE_INTENCLR_IN7_Pos) /*!< Bit mask of IN7 field. */
#define GPIOTE_INTENCLR_IN7_Disabled (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENCLR_IN7_Enabled (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENCLR_IN7_Clear (1UL) /*!< Disable */

/* Bit 6 : Write '1' to Disable interrupt for IN[6] event */
#define GPIOTE_INTENCLR_IN6_Pos (6UL) /*!< Position of IN6 field. */
#define GPIOTE_INTENCLR_IN6_Msk (0x1UL << GPIOTE_INTENCLR_IN6_Pos) /*!< Bit mask of IN6 field. */
#define GPIOTE_INTENCLR_IN6_Disabled (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENCLR_IN6_Enabled (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENCLR_IN6_Clear (1UL) /*!< Disable */

/* Bit 5 : Write '1' to Disable interrupt for IN[5] event */
#define GPIOTE_INTENCLR_IN5_Pos (5UL) /*!< Position of IN5 field. */
#define GPIOTE_INTENCLR_IN5_Msk (0x1UL << GPIOTE_INTENCLR_IN5_Pos) /*!< Bit mask of IN5 field. */
#define GPIOTE_INTENCLR_IN5_Disabled (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENCLR_IN5_Enabled (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENCLR_IN5_Clear (1UL) /*!< Disable */

/* Bit 4 : Write '1' to Disable interrupt for IN[4] event */
#define GPIOTE_INTENCLR_IN4_Pos (4UL) /*!< Position of IN4 field. */
#define GPIOTE_INTENCLR_IN4_Msk (0x1UL << GPIOTE_INTENCLR_IN4_Pos) /*!< Bit mask of IN4 field. */
#define GPIOTE_INTENCLR_IN4_Disabled (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENCLR_IN4_Enabled (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENCLR_IN4_Clear (1UL) /*!< Disable */

/* Bit 3 : Write '1' to Disable interrupt for IN[3] event */
#define GPIOTE_INTENCLR_IN3_Pos (3UL) /*!< Position of IN3 field. */
#define GPIOTE_INTENCLR_IN3_Msk (0x1UL << GPIOTE_INTENCLR_IN3_Pos) /*!< Bit mask of IN3 field. */
#define GPIOTE_INTENCLR_IN3_Disabled (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENCLR_IN3_Enabled (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENCLR_IN3_Clear (1UL) /*!< Disable */

/* Bit 2 : Write '1' to Disable interrupt for IN[2] event */
#define GPIOTE_INTENCLR_IN2_Pos (2UL) /*!< Position of IN2 field. */
#define GPIOTE_INTENCLR_IN2_Msk (0x1UL << GPIOTE_INTENCLR_IN2_Pos) /*!< Bit mask of IN2 field. */
#define GPIOTE_INTENCLR_IN2_Disabled (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENCLR_IN2_Enabled (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENCLR_IN2_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable interrupt for IN[1] event */
#define GPIOTE_INTENCLR_IN1_Pos (1UL) /*!< Position of IN1 field. */
#define GPIOTE_INTENCLR_IN1_Msk (0x1UL << GPIOTE_INTENCLR_IN1_Pos) /*!< Bit mask of IN1 field. */
#define GPIOTE_INTENCLR_IN1_Disabled (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENCLR_IN1_Enabled (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENCLR_IN1_Clear (1UL) /*!< Disable */

/* Bit 0 : Write '1' to Disable interrupt for IN[0] event */
#define GPIOTE_INTENCLR_IN0_Pos (0UL) /*!< Position of IN0 field. */
#define GPIOTE_INTENCLR_IN0_Msk (0x1UL << GPIOTE_INTENCLR_IN0_Pos) /*!< Bit mask of IN0 field. */
#define GPIOTE_INTENCLR_IN0_Disabled (0UL) /*!< Read: Disabled */
#define GPIOTE_INTENCLR_IN0_Enabled (1UL) /*!< Read: Enabled */
#define GPIOTE_INTENCLR_IN0_Clear (1UL) /*!< Disable */

/* Register: GPIOTE_CONFIG */
/* Description: Description collection[0]:  Configuration for OUT[n], SET[n] and CLR[n] tasks and IN[n] event */

/* Bit 20 : When in task mode: Initial value of the output when the GPIOTE channel is configured. When in event mode: No effect. */
#define GPIOTE_CONFIG_OUTINIT_Pos (20UL) /*!< Position of OUTINIT field. */
#define GPIOTE_CONFIG_OUTINIT_Msk (0x1UL << GPIOTE_CONFIG_OUTINIT_Pos) /*!< Bit mask of OUTINIT field. */
#define GPIOTE_CONFIG_OUTINIT_Low (0UL) /*!< Task mode: Initial value of pin before task triggering is low */
#define GPIOTE_CONFIG_OUTINIT_High (1UL) /*!< Task mode: Initial value of pin before task triggering is high */

/* Bits 17..16 : When In task mode: Operation to be performed on output when OUT[n] task is triggered. When In event mode: Operation on input that shall trigger IN[n] event. */
#define GPIOTE_CONFIG_POLARITY_Pos (16UL) /*!< Position of POLARITY field. */
#define GPIOTE_CONFIG_POLARITY_Msk (0x3UL << GPIOTE_CONFIG_POLARITY_Pos) /*!< Bit mask of POLARITY field. */
#define GPIOTE_CONFIG_POLARITY_None (0UL) /*!< Task mode: No effect on pin from OUT[n] task. Event mode: no IN[n] event generated on pin activity. */
#define GPIOTE_CONFIG_POLARITY_LoToHi (1UL) /*!< Task mode: Set pin from OUT[n] task. Event mode: Generate IN[n] event when rising edge on pin. */
#define GPIOTE_CONFIG_POLARITY_HiToLo (2UL) /*!< Task mode: Clear pin from OUT[n] task. Event mode: Generate IN[n] event when falling edge on pin. */
#define GPIOTE_CONFIG_POLARITY_Toggle (3UL) /*!< Task mode: Toggle pin from OUT[n]. Event mode: Generate IN[n] when any change on pin. */

/* Bits 14..13 : Port number */
#define GPIOTE_CONFIG_PORT_Pos (13UL) /*!< Position of PORT field. */
#define GPIOTE_CONFIG_PORT_Msk (0x3UL << GPIOTE_CONFIG_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 12..8 : GPIO number associated with SET[n], CLR[n] and OUT[n] tasks and IN[n] event */
#define GPIOTE_CONFIG_PSEL_Pos (8UL) /*!< Position of PSEL field. */
#define GPIOTE_CONFIG_PSEL_Msk (0x1FUL << GPIOTE_CONFIG_PSEL_Pos) /*!< Bit mask of PSEL field. */

/* Bits 1..0 : Mode */
#define GPIOTE_CONFIG_MODE_Pos (0UL) /*!< Position of MODE field. */
#define GPIOTE_CONFIG_MODE_Msk (0x3UL << GPIOTE_CONFIG_MODE_Pos) /*!< Bit mask of MODE field. */
#define GPIOTE_CONFIG_MODE_Disabled (0UL) /*!< Disabled. Pin specified by PSEL will not be acquired by the GPIOTE module. */
#define GPIOTE_CONFIG_MODE_Event (1UL) /*!< Event mode */
#define GPIOTE_CONFIG_MODE_Task (3UL) /*!< Task mode */


/* Peripheral: I2S */
/* Description: Inter-IC Sound */

/* Register: I2S_INTEN */
/* Description: Enable or disable interrupt */

/* Bit 5 : Enable or disable interrupt for TXPTRUPD event */
#define I2S_INTEN_TXPTRUPD_Pos (5UL) /*!< Position of TXPTRUPD field. */
#define I2S_INTEN_TXPTRUPD_Msk (0x1UL << I2S_INTEN_TXPTRUPD_Pos) /*!< Bit mask of TXPTRUPD field. */
#define I2S_INTEN_TXPTRUPD_Disabled (0UL) /*!< Disable */
#define I2S_INTEN_TXPTRUPD_Enabled (1UL) /*!< Enable */

/* Bit 2 : Enable or disable interrupt for STOPPED event */
#define I2S_INTEN_STOPPED_Pos (2UL) /*!< Position of STOPPED field. */
#define I2S_INTEN_STOPPED_Msk (0x1UL << I2S_INTEN_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define I2S_INTEN_STOPPED_Disabled (0UL) /*!< Disable */
#define I2S_INTEN_STOPPED_Enabled (1UL) /*!< Enable */

/* Bit 1 : Enable or disable interrupt for RXPTRUPD event */
#define I2S_INTEN_RXPTRUPD_Pos (1UL) /*!< Position of RXPTRUPD field. */
#define I2S_INTEN_RXPTRUPD_Msk (0x1UL << I2S_INTEN_RXPTRUPD_Pos) /*!< Bit mask of RXPTRUPD field. */
#define I2S_INTEN_RXPTRUPD_Disabled (0UL) /*!< Disable */
#define I2S_INTEN_RXPTRUPD_Enabled (1UL) /*!< Enable */

/* Register: I2S_INTENSET */
/* Description: Enable interrupt */

/* Bit 5 : Write '1' to Enable interrupt for TXPTRUPD event */
#define I2S_INTENSET_TXPTRUPD_Pos (5UL) /*!< Position of TXPTRUPD field. */
#define I2S_INTENSET_TXPTRUPD_Msk (0x1UL << I2S_INTENSET_TXPTRUPD_Pos) /*!< Bit mask of TXPTRUPD field. */
#define I2S_INTENSET_TXPTRUPD_Disabled (0UL) /*!< Read: Disabled */
#define I2S_INTENSET_TXPTRUPD_Enabled (1UL) /*!< Read: Enabled */
#define I2S_INTENSET_TXPTRUPD_Set (1UL) /*!< Enable */

/* Bit 2 : Write '1' to Enable interrupt for STOPPED event */
#define I2S_INTENSET_STOPPED_Pos (2UL) /*!< Position of STOPPED field. */
#define I2S_INTENSET_STOPPED_Msk (0x1UL << I2S_INTENSET_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define I2S_INTENSET_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define I2S_INTENSET_STOPPED_Enabled (1UL) /*!< Read: Enabled */
#define I2S_INTENSET_STOPPED_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable interrupt for RXPTRUPD event */
#define I2S_INTENSET_RXPTRUPD_Pos (1UL) /*!< Position of RXPTRUPD field. */
#define I2S_INTENSET_RXPTRUPD_Msk (0x1UL << I2S_INTENSET_RXPTRUPD_Pos) /*!< Bit mask of RXPTRUPD field. */
#define I2S_INTENSET_RXPTRUPD_Disabled (0UL) /*!< Read: Disabled */
#define I2S_INTENSET_RXPTRUPD_Enabled (1UL) /*!< Read: Enabled */
#define I2S_INTENSET_RXPTRUPD_Set (1UL) /*!< Enable */

/* Register: I2S_INTENCLR */
/* Description: Disable interrupt */

/* Bit 5 : Write '1' to Disable interrupt for TXPTRUPD event */
#define I2S_INTENCLR_TXPTRUPD_Pos (5UL) /*!< Position of TXPTRUPD field. */
#define I2S_INTENCLR_TXPTRUPD_Msk (0x1UL << I2S_INTENCLR_TXPTRUPD_Pos) /*!< Bit mask of TXPTRUPD field. */
#define I2S_INTENCLR_TXPTRUPD_Disabled (0UL) /*!< Read: Disabled */
#define I2S_INTENCLR_TXPTRUPD_Enabled (1UL) /*!< Read: Enabled */
#define I2S_INTENCLR_TXPTRUPD_Clear (1UL) /*!< Disable */

/* Bit 2 : Write '1' to Disable interrupt for STOPPED event */
#define I2S_INTENCLR_STOPPED_Pos (2UL) /*!< Position of STOPPED field. */
#define I2S_INTENCLR_STOPPED_Msk (0x1UL << I2S_INTENCLR_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define I2S_INTENCLR_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define I2S_INTENCLR_STOPPED_Enabled (1UL) /*!< Read: Enabled */
#define I2S_INTENCLR_STOPPED_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable interrupt for RXPTRUPD event */
#define I2S_INTENCLR_RXPTRUPD_Pos (1UL) /*!< Position of RXPTRUPD field. */
#define I2S_INTENCLR_RXPTRUPD_Msk (0x1UL << I2S_INTENCLR_RXPTRUPD_Pos) /*!< Bit mask of RXPTRUPD field. */
#define I2S_INTENCLR_RXPTRUPD_Disabled (0UL) /*!< Read: Disabled */
#define I2S_INTENCLR_RXPTRUPD_Enabled (1UL) /*!< Read: Enabled */
#define I2S_INTENCLR_RXPTRUPD_Clear (1UL) /*!< Disable */

/* Register: I2S_ENABLE */
/* Description: Enable I2S module. */

/* Bit 0 : Enable I2S module. */
#define I2S_ENABLE_ENABLE_Pos (0UL) /*!< Position of ENABLE field. */
#define I2S_ENABLE_ENABLE_Msk (0x1UL << I2S_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define I2S_ENABLE_ENABLE_Disabled (0UL) /*!< Disable */
#define I2S_ENABLE_ENABLE_Enabled (1UL) /*!< Enable */

/* Register: I2S_CONFIG_MODE */
/* Description: I2S mode. */

/* Bit 0 : I2S mode. */
#define I2S_CONFIG_MODE_MODE_Pos (0UL) /*!< Position of MODE field. */
#define I2S_CONFIG_MODE_MODE_Msk (0x1UL << I2S_CONFIG_MODE_MODE_Pos) /*!< Bit mask of MODE field. */
#define I2S_CONFIG_MODE_MODE_Master (0UL) /*!< Master mode. SCK and LRCK generated from internal master clcok (MCK) and output on pins defined by PSEL.xxx. */
#define I2S_CONFIG_MODE_MODE_Slave (1UL) /*!< Slave mode. SCK and LRCK generated by external master and received on pins defined by PSEL.xxx */

/* Register: I2S_CONFIG_RXEN */
/* Description: Reception (RX) enable. */

/* Bit 0 : Reception (RX) enable. */
#define I2S_CONFIG_RXEN_RXEN_Pos (0UL) /*!< Position of RXEN field. */
#define I2S_CONFIG_RXEN_RXEN_Msk (0x1UL << I2S_CONFIG_RXEN_RXEN_Pos) /*!< Bit mask of RXEN field. */
#define I2S_CONFIG_RXEN_RXEN_Disabled (0UL) /*!< Reception disabled and now data will be written to the RXD.PTR address. */
#define I2S_CONFIG_RXEN_RXEN_Enabled (1UL) /*!< Reception enabled. */

/* Register: I2S_CONFIG_TXEN */
/* Description: Transmission (TX) enable. */

/* Bit 0 : Transmission (TX) enable. */
#define I2S_CONFIG_TXEN_TXEN_Pos (0UL) /*!< Position of TXEN field. */
#define I2S_CONFIG_TXEN_TXEN_Msk (0x1UL << I2S_CONFIG_TXEN_TXEN_Pos) /*!< Bit mask of TXEN field. */
#define I2S_CONFIG_TXEN_TXEN_Disabled (0UL) /*!< Transmission disabled and now data will be read from the RXD.TXD address. */
#define I2S_CONFIG_TXEN_TXEN_Enabled (1UL) /*!< Transmission enabled. */

/* Register: I2S_CONFIG_MCKEN */
/* Description: Master clock generator enable. */

/* Bit 0 : Master clock generator enable. */
#define I2S_CONFIG_MCKEN_MCKEN_Pos (0UL) /*!< Position of MCKEN field. */
#define I2S_CONFIG_MCKEN_MCKEN_Msk (0x1UL << I2S_CONFIG_MCKEN_MCKEN_Pos) /*!< Bit mask of MCKEN field. */
#define I2S_CONFIG_MCKEN_MCKEN_Disabled (0UL) /*!< Master clock generator disabled and PSEL.MCK not connected(available as GPIO). */
#define I2S_CONFIG_MCKEN_MCKEN_Enabled (1UL) /*!< Master clock generator running and MCK output on PSEL.MCK. */

/* Register: I2S_CONFIG_MCKFREQ */
/* Description: Master clock generator frequency. */

/* Bits 31..0 : Master clock generator frequency. */
#define I2S_CONFIG_MCKFREQ_MCKFREQ_Pos (0UL) /*!< Position of MCKFREQ field. */
#define I2S_CONFIG_MCKFREQ_MCKFREQ_Msk (0xFFFFFFFFUL << I2S_CONFIG_MCKFREQ_MCKFREQ_Pos) /*!< Bit mask of MCKFREQ field. */
#define I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV125 (0x020C0000UL) /*!< 32 MHz / 125 = 0.256 MHz */
#define I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV63 (0x04100000UL) /*!< 32 MHz / 63 = 0.5079365 MHz */
#define I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV42 (0x06000000UL) /*!< 32 MHz / 42 = 0.7619048 MHz */
#define I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV32 (0x08000000UL) /*!< 32 MHz / 32 = 1.0 MHz */
#define I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV31 (0x08400000UL) /*!< 32 MHz / 31 = 1.0322581 MHz */
#define I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV30 (0x08800000UL) /*!< 32 MHz / 30 = 1.0666667 MHz */
#define I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV23 (0x0B000000UL) /*!< 32 MHz / 23 = 1.3913043 MHz */
#define I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV21 (0x0C000000UL) /*!< 32 MHz / 21 = 1.5238095 */
#define I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV16 (0x10000000UL) /*!< 32 MHz / 16 = 2.0 MHz */
#define I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV15 (0x11000000UL) /*!< 32 MHz / 15 = 2.1333333 MHz */
#define I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV11 (0x16000000UL) /*!< 32 MHz / 11 = 2.9090909 MHz */
#define I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV10 (0x18000000UL) /*!< 32 MHz / 10 = 3.2 MHz */
#define I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV8 (0x20000000UL) /*!< 32 MHz / 8 = 4.0 MHz */
#define I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV6 (0x28000000UL) /*!< 32 MHz / 6 = 5.3333333 MHz */
#define I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV5 (0x30000000UL) /*!< 32 MHz / 5 = 6.4 MHz */
#define I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV4 (0x40000000UL) /*!< 32 MHz / 4 = 8.0 MHz */
#define I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV3 (0x50000000UL) /*!< 32 MHz / 3 = 10.6666667 MHz */
#define I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV2 (0x80000000UL) /*!< 32 MHz / 2 = 16.0 MHz */

/* Register: I2S_CONFIG_RATIO */
/* Description: MCK / LRCK ratio. */

/* Bits 3..0 : MCK / LRCK ratio. */
#define I2S_CONFIG_RATIO_RATIO_Pos (0UL) /*!< Position of RATIO field. */
#define I2S_CONFIG_RATIO_RATIO_Msk (0xFUL << I2S_CONFIG_RATIO_RATIO_Pos) /*!< Bit mask of RATIO field. */
#define I2S_CONFIG_RATIO_RATIO_32X (0UL) /*!< LRCK = MCK / 32 */
#define I2S_CONFIG_RATIO_RATIO_48X (1UL) /*!< LRCK = MCK / 48 */
#define I2S_CONFIG_RATIO_RATIO_64X (2UL) /*!< LRCK = MCK / 64 */
#define I2S_CONFIG_RATIO_RATIO_96X (3UL) /*!< LRCK = MCK / 96 */
#define I2S_CONFIG_RATIO_RATIO_128X (4UL) /*!< LRCK = MCK / 128 */
#define I2S_CONFIG_RATIO_RATIO_192X (5UL) /*!< LRCK = MCK / 192 */
#define I2S_CONFIG_RATIO_RATIO_256X (6UL) /*!< LRCK = MCK / 256 */
#define I2S_CONFIG_RATIO_RATIO_384X (7UL) /*!< LRCK = MCK / 384 */
#define I2S_CONFIG_RATIO_RATIO_512X (8UL) /*!< LRCK = MCK / 512 */

/* Register: I2S_CONFIG_SWIDTH */
/* Description: Sample width. */

/* Bits 1..0 : Sample width. */
#define I2S_CONFIG_SWIDTH_SWIDTH_Pos (0UL) /*!< Position of SWIDTH field. */
#define I2S_CONFIG_SWIDTH_SWIDTH_Msk (0x3UL << I2S_CONFIG_SWIDTH_SWIDTH_Pos) /*!< Bit mask of SWIDTH field. */
#define I2S_CONFIG_SWIDTH_SWIDTH_8Bit (0UL) /*!< 8 bit. */
#define I2S_CONFIG_SWIDTH_SWIDTH_16Bit (1UL) /*!< 16 bit. */
#define I2S_CONFIG_SWIDTH_SWIDTH_24Bit (2UL) /*!< 24 bit. */

/* Register: I2S_CONFIG_ALIGN */
/* Description: Alignment of sample within a frame. */

/* Bit 0 : Alignment of sample within a frame. */
#define I2S_CONFIG_ALIGN_ALIGN_Pos (0UL) /*!< Position of ALIGN field. */
#define I2S_CONFIG_ALIGN_ALIGN_Msk (0x1UL << I2S_CONFIG_ALIGN_ALIGN_Pos) /*!< Bit mask of ALIGN field. */
#define I2S_CONFIG_ALIGN_ALIGN_Left (0UL) /*!< Left-aligned. */
#define I2S_CONFIG_ALIGN_ALIGN_Right (1UL) /*!< Right-aligned. */

/* Register: I2S_CONFIG_FORMAT */
/* Description: Frame format. */

/* Bit 0 : Frame format. */
#define I2S_CONFIG_FORMAT_FORMAT_Pos (0UL) /*!< Position of FORMAT field. */
#define I2S_CONFIG_FORMAT_FORMAT_Msk (0x1UL << I2S_CONFIG_FORMAT_FORMAT_Pos) /*!< Bit mask of FORMAT field. */
#define I2S_CONFIG_FORMAT_FORMAT_I2S (0UL) /*!< Original I2S format. */
#define I2S_CONFIG_FORMAT_FORMAT_Aligned (1UL) /*!< Alternate (left- or right-aligned) format. */

/* Register: I2S_CONFIG_CHANNELS */
/* Description: Enable channels. */

/* Bits 1..0 : Enable channels. */
#define I2S_CONFIG_CHANNELS_CHANNELS_Pos (0UL) /*!< Position of CHANNELS field. */
#define I2S_CONFIG_CHANNELS_CHANNELS_Msk (0x3UL << I2S_CONFIG_CHANNELS_CHANNELS_Pos) /*!< Bit mask of CHANNELS field. */
#define I2S_CONFIG_CHANNELS_CHANNELS_Stereo (0UL) /*!< Stereo. */
#define I2S_CONFIG_CHANNELS_CHANNELS_Left (1UL) /*!< Left only. */
#define I2S_CONFIG_CHANNELS_CHANNELS_Right (2UL) /*!< Right only. */

/* Register: I2S_RXD_PTR */
/* Description: Receive buffer RAM start address. */

/* Bits 31..0 : Receive buffer Data RAM start address. When receiving, words containing samples will be written to this address. This address is a word aligned Data RAM address. */
#define I2S_RXD_PTR_PTR_Pos (0UL) /*!< Position of PTR field. */
#define I2S_RXD_PTR_PTR_Msk (0xFFFFFFFFUL << I2S_RXD_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: I2S_TXD_PTR */
/* Description: Transmit buffer RAM start address. */

/* Bits 31..0 : Transmit buffer Data RAM start address. When transmitting, words containing samples will be fetched from this address. This address is a word aligned Data RAM address. */
#define I2S_TXD_PTR_PTR_Pos (0UL) /*!< Position of PTR field. */
#define I2S_TXD_PTR_PTR_Msk (0xFFFFFFFFUL << I2S_TXD_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: I2S_RXTXD_MAXCNT */
/* Description: Size of RXD and TXD buffers. */

/* Bits 13..0 : Size of RXD and TXD buffers in number of 32 bit words. */
#define I2S_RXTXD_MAXCNT_MAXCNT_Pos (0UL) /*!< Position of MAXCNT field. */
#define I2S_RXTXD_MAXCNT_MAXCNT_Msk (0x3FFFUL << I2S_RXTXD_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: I2S_PSEL_MCK */
/* Description: Pin select for MCK signal. */

/* Bit 31 : Connection */
#define I2S_PSEL_MCK_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define I2S_PSEL_MCK_CONNECT_Msk (0x1UL << I2S_PSEL_MCK_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define I2S_PSEL_MCK_CONNECT_Connected (0UL) /*!< Connect */
#define I2S_PSEL_MCK_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 9..8 : Port number */
#define I2S_PSEL_MCK_PORT_Pos (8UL) /*!< Position of PORT field. */
#define I2S_PSEL_MCK_PORT_Msk (0x3UL << I2S_PSEL_MCK_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define I2S_PSEL_MCK_PIN_Pos (0UL) /*!< Position of PIN field. */
#define I2S_PSEL_MCK_PIN_Msk (0x1FUL << I2S_PSEL_MCK_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: I2S_PSEL_SCK */
/* Description: Pin select for SCK signal. */

/* Bit 31 : Connection */
#define I2S_PSEL_SCK_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define I2S_PSEL_SCK_CONNECT_Msk (0x1UL << I2S_PSEL_SCK_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define I2S_PSEL_SCK_CONNECT_Connected (0UL) /*!< Connect */
#define I2S_PSEL_SCK_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 9..8 : Port number */
#define I2S_PSEL_SCK_PORT_Pos (8UL) /*!< Position of PORT field. */
#define I2S_PSEL_SCK_PORT_Msk (0x3UL << I2S_PSEL_SCK_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define I2S_PSEL_SCK_PIN_Pos (0UL) /*!< Position of PIN field. */
#define I2S_PSEL_SCK_PIN_Msk (0x1FUL << I2S_PSEL_SCK_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: I2S_PSEL_LRCK */
/* Description: Pin select for LRCK signal. */

/* Bit 31 : Connection */
#define I2S_PSEL_LRCK_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define I2S_PSEL_LRCK_CONNECT_Msk (0x1UL << I2S_PSEL_LRCK_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define I2S_PSEL_LRCK_CONNECT_Connected (0UL) /*!< Connect */
#define I2S_PSEL_LRCK_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 9..8 : Port number */
#define I2S_PSEL_LRCK_PORT_Pos (8UL) /*!< Position of PORT field. */
#define I2S_PSEL_LRCK_PORT_Msk (0x3UL << I2S_PSEL_LRCK_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define I2S_PSEL_LRCK_PIN_Pos (0UL) /*!< Position of PIN field. */
#define I2S_PSEL_LRCK_PIN_Msk (0x1FUL << I2S_PSEL_LRCK_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: I2S_PSEL_SDIN */
/* Description: Pin select for SDIN signal. */

/* Bit 31 : Connection */
#define I2S_PSEL_SDIN_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define I2S_PSEL_SDIN_CONNECT_Msk (0x1UL << I2S_PSEL_SDIN_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define I2S_PSEL_SDIN_CONNECT_Connected (0UL) /*!< Connect */
#define I2S_PSEL_SDIN_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 9..8 : Port number */
#define I2S_PSEL_SDIN_PORT_Pos (8UL) /*!< Position of PORT field. */
#define I2S_PSEL_SDIN_PORT_Msk (0x3UL << I2S_PSEL_SDIN_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define I2S_PSEL_SDIN_PIN_Pos (0UL) /*!< Position of PIN field. */
#define I2S_PSEL_SDIN_PIN_Msk (0x1FUL << I2S_PSEL_SDIN_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: I2S_PSEL_SDOUT */
/* Description: Pin select for SDOUT signal. */

/* Bit 31 : Connection */
#define I2S_PSEL_SDOUT_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define I2S_PSEL_SDOUT_CONNECT_Msk (0x1UL << I2S_PSEL_SDOUT_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define I2S_PSEL_SDOUT_CONNECT_Connected (0UL) /*!< Connect */
#define I2S_PSEL_SDOUT_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 9..8 : Port number */
#define I2S_PSEL_SDOUT_PORT_Pos (8UL) /*!< Position of PORT field. */
#define I2S_PSEL_SDOUT_PORT_Msk (0x3UL << I2S_PSEL_SDOUT_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define I2S_PSEL_SDOUT_PIN_Pos (0UL) /*!< Position of PIN field. */
#define I2S_PSEL_SDOUT_PIN_Msk (0x1FUL << I2S_PSEL_SDOUT_PIN_Pos) /*!< Bit mask of PIN field. */


/* Peripheral: LPCOMP */
/* Description: Low Power Comparator */

/* Register: LPCOMP_SHORTS */
/* Description: Shortcut register */

/* Bit 4 : Shortcut between CROSS event and STOP task */
#define LPCOMP_SHORTS_CROSS_STOP_Pos (4UL) /*!< Position of CROSS_STOP field. */
#define LPCOMP_SHORTS_CROSS_STOP_Msk (0x1UL << LPCOMP_SHORTS_CROSS_STOP_Pos) /*!< Bit mask of CROSS_STOP field. */
#define LPCOMP_SHORTS_CROSS_STOP_Disabled (0UL) /*!< Disable shortcut */
#define LPCOMP_SHORTS_CROSS_STOP_Enabled (1UL) /*!< Enable shortcut */

/* Bit 3 : Shortcut between UP event and STOP task */
#define LPCOMP_SHORTS_UP_STOP_Pos (3UL) /*!< Position of UP_STOP field. */
#define LPCOMP_SHORTS_UP_STOP_Msk (0x1UL << LPCOMP_SHORTS_UP_STOP_Pos) /*!< Bit mask of UP_STOP field. */
#define LPCOMP_SHORTS_UP_STOP_Disabled (0UL) /*!< Disable shortcut */
#define LPCOMP_SHORTS_UP_STOP_Enabled (1UL) /*!< Enable shortcut */

/* Bit 2 : Shortcut between DOWN event and STOP task */
#define LPCOMP_SHORTS_DOWN_STOP_Pos (2UL) /*!< Position of DOWN_STOP field. */
#define LPCOMP_SHORTS_DOWN_STOP_Msk (0x1UL << LPCOMP_SHORTS_DOWN_STOP_Pos) /*!< Bit mask of DOWN_STOP field. */
#define LPCOMP_SHORTS_DOWN_STOP_Disabled (0UL) /*!< Disable shortcut */
#define LPCOMP_SHORTS_DOWN_STOP_Enabled (1UL) /*!< Enable shortcut */

/* Bit 1 : Shortcut between READY event and STOP task */
#define LPCOMP_SHORTS_READY_STOP_Pos (1UL) /*!< Position of READY_STOP field. */
#define LPCOMP_SHORTS_READY_STOP_Msk (0x1UL << LPCOMP_SHORTS_READY_STOP_Pos) /*!< Bit mask of READY_STOP field. */
#define LPCOMP_SHORTS_READY_STOP_Disabled (0UL) /*!< Disable shortcut */
#define LPCOMP_SHORTS_READY_STOP_Enabled (1UL) /*!< Enable shortcut */

/* Bit 0 : Shortcut between READY event and SAMPLE task */
#define LPCOMP_SHORTS_READY_SAMPLE_Pos (0UL) /*!< Position of READY_SAMPLE field. */
#define LPCOMP_SHORTS_READY_SAMPLE_Msk (0x1UL << LPCOMP_SHORTS_READY_SAMPLE_Pos) /*!< Bit mask of READY_SAMPLE field. */
#define LPCOMP_SHORTS_READY_SAMPLE_Disabled (0UL) /*!< Disable shortcut */
#define LPCOMP_SHORTS_READY_SAMPLE_Enabled (1UL) /*!< Enable shortcut */

/* Register: LPCOMP_INTENSET */
/* Description: Enable interrupt */

/* Bit 3 : Write '1' to Enable interrupt for CROSS event */
#define LPCOMP_INTENSET_CROSS_Pos (3UL) /*!< Position of CROSS field. */
#define LPCOMP_INTENSET_CROSS_Msk (0x1UL << LPCOMP_INTENSET_CROSS_Pos) /*!< Bit mask of CROSS field. */
#define LPCOMP_INTENSET_CROSS_Disabled (0UL) /*!< Read: Disabled */
#define LPCOMP_INTENSET_CROSS_Enabled (1UL) /*!< Read: Enabled */
#define LPCOMP_INTENSET_CROSS_Set (1UL) /*!< Enable */

/* Bit 2 : Write '1' to Enable interrupt for UP event */
#define LPCOMP_INTENSET_UP_Pos (2UL) /*!< Position of UP field. */
#define LPCOMP_INTENSET_UP_Msk (0x1UL << LPCOMP_INTENSET_UP_Pos) /*!< Bit mask of UP field. */
#define LPCOMP_INTENSET_UP_Disabled (0UL) /*!< Read: Disabled */
#define LPCOMP_INTENSET_UP_Enabled (1UL) /*!< Read: Enabled */
#define LPCOMP_INTENSET_UP_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable interrupt for DOWN event */
#define LPCOMP_INTENSET_DOWN_Pos (1UL) /*!< Position of DOWN field. */
#define LPCOMP_INTENSET_DOWN_Msk (0x1UL << LPCOMP_INTENSET_DOWN_Pos) /*!< Bit mask of DOWN field. */
#define LPCOMP_INTENSET_DOWN_Disabled (0UL) /*!< Read: Disabled */
#define LPCOMP_INTENSET_DOWN_Enabled (1UL) /*!< Read: Enabled */
#define LPCOMP_INTENSET_DOWN_Set (1UL) /*!< Enable */

/* Bit 0 : Write '1' to Enable interrupt for READY event */
#define LPCOMP_INTENSET_READY_Pos (0UL) /*!< Position of READY field. */
#define LPCOMP_INTENSET_READY_Msk (0x1UL << LPCOMP_INTENSET_READY_Pos) /*!< Bit mask of READY field. */
#define LPCOMP_INTENSET_READY_Disabled (0UL) /*!< Read: Disabled */
#define LPCOMP_INTENSET_READY_Enabled (1UL) /*!< Read: Enabled */
#define LPCOMP_INTENSET_READY_Set (1UL) /*!< Enable */

/* Register: LPCOMP_INTENCLR */
/* Description: Disable interrupt */

/* Bit 3 : Write '1' to Disable interrupt for CROSS event */
#define LPCOMP_INTENCLR_CROSS_Pos (3UL) /*!< Position of CROSS field. */
#define LPCOMP_INTENCLR_CROSS_Msk (0x1UL << LPCOMP_INTENCLR_CROSS_Pos) /*!< Bit mask of CROSS field. */
#define LPCOMP_INTENCLR_CROSS_Disabled (0UL) /*!< Read: Disabled */
#define LPCOMP_INTENCLR_CROSS_Enabled (1UL) /*!< Read: Enabled */
#define LPCOMP_INTENCLR_CROSS_Clear (1UL) /*!< Disable */

/* Bit 2 : Write '1' to Disable interrupt for UP event */
#define LPCOMP_INTENCLR_UP_Pos (2UL) /*!< Position of UP field. */
#define LPCOMP_INTENCLR_UP_Msk (0x1UL << LPCOMP_INTENCLR_UP_Pos) /*!< Bit mask of UP field. */
#define LPCOMP_INTENCLR_UP_Disabled (0UL) /*!< Read: Disabled */
#define LPCOMP_INTENCLR_UP_Enabled (1UL) /*!< Read: Enabled */
#define LPCOMP_INTENCLR_UP_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable interrupt for DOWN event */
#define LPCOMP_INTENCLR_DOWN_Pos (1UL) /*!< Position of DOWN field. */
#define LPCOMP_INTENCLR_DOWN_Msk (0x1UL << LPCOMP_INTENCLR_DOWN_Pos) /*!< Bit mask of DOWN field. */
#define LPCOMP_INTENCLR_DOWN_Disabled (0UL) /*!< Read: Disabled */
#define LPCOMP_INTENCLR_DOWN_Enabled (1UL) /*!< Read: Enabled */
#define LPCOMP_INTENCLR_DOWN_Clear (1UL) /*!< Disable */

/* Bit 0 : Write '1' to Disable interrupt for READY event */
#define LPCOMP_INTENCLR_READY_Pos (0UL) /*!< Position of READY field. */
#define LPCOMP_INTENCLR_READY_Msk (0x1UL << LPCOMP_INTENCLR_READY_Pos) /*!< Bit mask of READY field. */
#define LPCOMP_INTENCLR_READY_Disabled (0UL) /*!< Read: Disabled */
#define LPCOMP_INTENCLR_READY_Enabled (1UL) /*!< Read: Enabled */
#define LPCOMP_INTENCLR_READY_Clear (1UL) /*!< Disable */

/* Register: LPCOMP_RESULT */
/* Description: Compare result */

/* Bit 0 : Result of last compare. Decision point SAMPLE task. */
#define LPCOMP_RESULT_RESULT_Pos (0UL) /*!< Position of RESULT field. */
#define LPCOMP_RESULT_RESULT_Msk (0x1UL << LPCOMP_RESULT_RESULT_Pos) /*!< Bit mask of RESULT field. */
#define LPCOMP_RESULT_RESULT_Below (0UL) /*!< Input voltage is below the reference threshold (VIN+ &lt; VIN-). */
#define LPCOMP_RESULT_RESULT_Above (1UL) /*!< Input voltage is above the reference threshold (VIN+ &gt; VIN-). */

/* Register: LPCOMP_ENABLE */
/* Description: Enable LPCOMP */

/* Bits 1..0 : Enable or disable LPCOMP */
#define LPCOMP_ENABLE_ENABLE_Pos (0UL) /*!< Position of ENABLE field. */
#define LPCOMP_ENABLE_ENABLE_Msk (0x3UL << LPCOMP_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define LPCOMP_ENABLE_ENABLE_Disabled (0UL) /*!< Disable */
#define LPCOMP_ENABLE_ENABLE_Enabled (1UL) /*!< Enable */

/* Register: LPCOMP_PSEL */
/* Description: Input pin select */

/* Bits 2..0 : Analog pin select */
#define LPCOMP_PSEL_PSEL_Pos (0UL) /*!< Position of PSEL field. */
#define LPCOMP_PSEL_PSEL_Msk (0x7UL << LPCOMP_PSEL_PSEL_Pos) /*!< Bit mask of PSEL field. */
#define LPCOMP_PSEL_PSEL_AnalogInput0 (0UL) /*!< AIN0 selected as analog input */
#define LPCOMP_PSEL_PSEL_AnalogInput1 (1UL) /*!< AIN1 selected as analog input */
#define LPCOMP_PSEL_PSEL_AnalogInput2 (2UL) /*!< AIN2 selected as analog input */
#define LPCOMP_PSEL_PSEL_AnalogInput3 (3UL) /*!< AIN3 selected as analog input */
#define LPCOMP_PSEL_PSEL_AnalogInput4 (4UL) /*!< AIN4 selected as analog input */
#define LPCOMP_PSEL_PSEL_AnalogInput5 (5UL) /*!< AIN5 selected as analog input */
#define LPCOMP_PSEL_PSEL_AnalogInput6 (6UL) /*!< AIN6 selected as analog input */
#define LPCOMP_PSEL_PSEL_AnalogInput7 (7UL) /*!< AIN7 selected as analog input */

/* Register: LPCOMP_REFSEL */
/* Description: Reference select */

/* Bits 3..0 : Reference select */
#define LPCOMP_REFSEL_REFSEL_Pos (0UL) /*!< Position of REFSEL field. */
#define LPCOMP_REFSEL_REFSEL_Msk (0xFUL << LPCOMP_REFSEL_REFSEL_Pos) /*!< Bit mask of REFSEL field. */
#define LPCOMP_REFSEL_REFSEL_Ref1_8Vdd (0UL) /*!< VDD * 1/8 selected as reference */
#define LPCOMP_REFSEL_REFSEL_Ref2_8Vdd (1UL) /*!< VDD * 2/8 selected as reference */
#define LPCOMP_REFSEL_REFSEL_Ref3_8Vdd (2UL) /*!< VDD * 3/8 selected as reference */
#define LPCOMP_REFSEL_REFSEL_Ref4_8Vdd (3UL) /*!< VDD * 4/8 selected as reference */
#define LPCOMP_REFSEL_REFSEL_Ref5_8Vdd (4UL) /*!< VDD * 5/8 selected as reference */
#define LPCOMP_REFSEL_REFSEL_Ref6_8Vdd (5UL) /*!< VDD * 6/8 selected as reference */
#define LPCOMP_REFSEL_REFSEL_Ref7_8Vdd (6UL) /*!< VDD * 7/8 selected as reference */
#define LPCOMP_REFSEL_REFSEL_ARef (7UL) /*!< External analog reference selected */
#define LPCOMP_REFSEL_REFSEL_Ref1_16Vdd (8UL) /*!< VDD * 1/16 selected as reference */
#define LPCOMP_REFSEL_REFSEL_Ref3_16Vdd (9UL) /*!< VDD * 3/16 selected as reference */
#define LPCOMP_REFSEL_REFSEL_Ref5_16Vdd (10UL) /*!< VDD * 5/16 selected as reference */
#define LPCOMP_REFSEL_REFSEL_Ref7_16Vdd (11UL) /*!< VDD * 7/16 selected as reference */
#define LPCOMP_REFSEL_REFSEL_Ref9_16Vdd (12UL) /*!< VDD * 9/16 selected as reference */
#define LPCOMP_REFSEL_REFSEL_Ref11_16Vdd (13UL) /*!< VDD * 11/16 selected as reference */
#define LPCOMP_REFSEL_REFSEL_Ref13_16Vdd (14UL) /*!< VDD * 13/16 selected as reference */
#define LPCOMP_REFSEL_REFSEL_Ref15_16Vdd (15UL) /*!< VDD * 15/16 selected as reference */

/* Register: LPCOMP_EXTREFSEL */
/* Description: External reference select */

/* Bit 0 : External analog reference select */
#define LPCOMP_EXTREFSEL_EXTREFSEL_Pos (0UL) /*!< Position of EXTREFSEL field. */
#define LPCOMP_EXTREFSEL_EXTREFSEL_Msk (0x1UL << LPCOMP_EXTREFSEL_EXTREFSEL_Pos) /*!< Bit mask of EXTREFSEL field. */
#define LPCOMP_EXTREFSEL_EXTREFSEL_AnalogReference0 (0UL) /*!< Use AIN0 as external analog reference */
#define LPCOMP_EXTREFSEL_EXTREFSEL_AnalogReference1 (1UL) /*!< Use AIN1 as external analog reference */

/* Register: LPCOMP_ANADETECT */
/* Description: Analog detect configuration */

/* Bits 1..0 : Analog detect configuration */
#define LPCOMP_ANADETECT_ANADETECT_Pos (0UL) /*!< Position of ANADETECT field. */
#define LPCOMP_ANADETECT_ANADETECT_Msk (0x3UL << LPCOMP_ANADETECT_ANADETECT_Pos) /*!< Bit mask of ANADETECT field. */
#define LPCOMP_ANADETECT_ANADETECT_Cross (0UL) /*!< Generate ANADETECT on crossing, both upward crossing and downward crossing */
#define LPCOMP_ANADETECT_ANADETECT_Up (1UL) /*!< Generate ANADETECT on upward crossing only */
#define LPCOMP_ANADETECT_ANADETECT_Down (2UL) /*!< Generate ANADETECT on downward crossing only */

/* Register: LPCOMP_HYST */
/* Description: Comparator hysteresis enable */

/* Bit 0 : Comparator hysteresis enable */
#define LPCOMP_HYST_HYST_Pos (0UL) /*!< Position of HYST field. */
#define LPCOMP_HYST_HYST_Msk (0x1UL << LPCOMP_HYST_HYST_Pos) /*!< Bit mask of HYST field. */
#define LPCOMP_HYST_HYST_NoHyst (0UL) /*!< Comparator hysteresis disabled */
#define LPCOMP_HYST_HYST_Hyst50mV (1UL) /*!< Comparator hysteresis disabled (typ. 50 mV) */


/* Peripheral: MWU */
/* Description: Memory Watch Unit */

/* Register: MWU_INTEN */
/* Description: Enable or disable interrupt */

/* Bit 27 : Enable or disable interrupt for PREGION[1].RA event */
#define MWU_INTEN_PREGION1RA_Pos (27UL) /*!< Position of PREGION1RA field. */
#define MWU_INTEN_PREGION1RA_Msk (0x1UL << MWU_INTEN_PREGION1RA_Pos) /*!< Bit mask of PREGION1RA field. */
#define MWU_INTEN_PREGION1RA_Disabled (0UL) /*!< Disable */
#define MWU_INTEN_PREGION1RA_Enabled (1UL) /*!< Enable */

/* Bit 26 : Enable or disable interrupt for PREGION[1].WA event */
#define MWU_INTEN_PREGION1WA_Pos (26UL) /*!< Position of PREGION1WA field. */
#define MWU_INTEN_PREGION1WA_Msk (0x1UL << MWU_INTEN_PREGION1WA_Pos) /*!< Bit mask of PREGION1WA field. */
#define MWU_INTEN_PREGION1WA_Disabled (0UL) /*!< Disable */
#define MWU_INTEN_PREGION1WA_Enabled (1UL) /*!< Enable */

/* Bit 25 : Enable or disable interrupt for PREGION[0].RA event */
#define MWU_INTEN_PREGION0RA_Pos (25UL) /*!< Position of PREGION0RA field. */
#define MWU_INTEN_PREGION0RA_Msk (0x1UL << MWU_INTEN_PREGION0RA_Pos) /*!< Bit mask of PREGION0RA field. */
#define MWU_INTEN_PREGION0RA_Disabled (0UL) /*!< Disable */
#define MWU_INTEN_PREGION0RA_Enabled (1UL) /*!< Enable */

/* Bit 24 : Enable or disable interrupt for PREGION[0].WA event */
#define MWU_INTEN_PREGION0WA_Pos (24UL) /*!< Position of PREGION0WA field. */
#define MWU_INTEN_PREGION0WA_Msk (0x1UL << MWU_INTEN_PREGION0WA_Pos) /*!< Bit mask of PREGION0WA field. */
#define MWU_INTEN_PREGION0WA_Disabled (0UL) /*!< Disable */
#define MWU_INTEN_PREGION0WA_Enabled (1UL) /*!< Enable */

/* Bit 7 : Enable or disable interrupt for REGION[3].RA event */
#define MWU_INTEN_REGION3RA_Pos (7UL) /*!< Position of REGION3RA field. */
#define MWU_INTEN_REGION3RA_Msk (0x1UL << MWU_INTEN_REGION3RA_Pos) /*!< Bit mask of REGION3RA field. */
#define MWU_INTEN_REGION3RA_Disabled (0UL) /*!< Disable */
#define MWU_INTEN_REGION3RA_Enabled (1UL) /*!< Enable */

/* Bit 6 : Enable or disable interrupt for REGION[3].WA event */
#define MWU_INTEN_REGION3WA_Pos (6UL) /*!< Position of REGION3WA field. */
#define MWU_INTEN_REGION3WA_Msk (0x1UL << MWU_INTEN_REGION3WA_Pos) /*!< Bit mask of REGION3WA field. */
#define MWU_INTEN_REGION3WA_Disabled (0UL) /*!< Disable */
#define MWU_INTEN_REGION3WA_Enabled (1UL) /*!< Enable */

/* Bit 5 : Enable or disable interrupt for REGION[2].RA event */
#define MWU_INTEN_REGION2RA_Pos (5UL) /*!< Position of REGION2RA field. */
#define MWU_INTEN_REGION2RA_Msk (0x1UL << MWU_INTEN_REGION2RA_Pos) /*!< Bit mask of REGION2RA field. */
#define MWU_INTEN_REGION2RA_Disabled (0UL) /*!< Disable */
#define MWU_INTEN_REGION2RA_Enabled (1UL) /*!< Enable */

/* Bit 4 : Enable or disable interrupt for REGION[2].WA event */
#define MWU_INTEN_REGION2WA_Pos (4UL) /*!< Position of REGION2WA field. */
#define MWU_INTEN_REGION2WA_Msk (0x1UL << MWU_INTEN_REGION2WA_Pos) /*!< Bit mask of REGION2WA field. */
#define MWU_INTEN_REGION2WA_Disabled (0UL) /*!< Disable */
#define MWU_INTEN_REGION2WA_Enabled (1UL) /*!< Enable */

/* Bit 3 : Enable or disable interrupt for REGION[1].RA event */
#define MWU_INTEN_REGION1RA_Pos (3UL) /*!< Position of REGION1RA field. */
#define MWU_INTEN_REGION1RA_Msk (0x1UL << MWU_INTEN_REGION1RA_Pos) /*!< Bit mask of REGION1RA field. */
#define MWU_INTEN_REGION1RA_Disabled (0UL) /*!< Disable */
#define MWU_INTEN_REGION1RA_Enabled (1UL) /*!< Enable */

/* Bit 2 : Enable or disable interrupt for REGION[1].WA event */
#define MWU_INTEN_REGION1WA_Pos (2UL) /*!< Position of REGION1WA field. */
#define MWU_INTEN_REGION1WA_Msk (0x1UL << MWU_INTEN_REGION1WA_Pos) /*!< Bit mask of REGION1WA field. */
#define MWU_INTEN_REGION1WA_Disabled (0UL) /*!< Disable */
#define MWU_INTEN_REGION1WA_Enabled (1UL) /*!< Enable */

/* Bit 1 : Enable or disable interrupt for REGION[0].RA event */
#define MWU_INTEN_REGION0RA_Pos (1UL) /*!< Position of REGION0RA field. */
#define MWU_INTEN_REGION0RA_Msk (0x1UL << MWU_INTEN_REGION0RA_Pos) /*!< Bit mask of REGION0RA field. */
#define MWU_INTEN_REGION0RA_Disabled (0UL) /*!< Disable */
#define MWU_INTEN_REGION0RA_Enabled (1UL) /*!< Enable */

/* Bit 0 : Enable or disable interrupt for REGION[0].WA event */
#define MWU_INTEN_REGION0WA_Pos (0UL) /*!< Position of REGION0WA field. */
#define MWU_INTEN_REGION0WA_Msk (0x1UL << MWU_INTEN_REGION0WA_Pos) /*!< Bit mask of REGION0WA field. */
#define MWU_INTEN_REGION0WA_Disabled (0UL) /*!< Disable */
#define MWU_INTEN_REGION0WA_Enabled (1UL) /*!< Enable */

/* Register: MWU_INTENSET */
/* Description: Enable interrupt */

/* Bit 27 : Write '1' to Enable interrupt for PREGION[1].RA event */
#define MWU_INTENSET_PREGION1RA_Pos (27UL) /*!< Position of PREGION1RA field. */
#define MWU_INTENSET_PREGION1RA_Msk (0x1UL << MWU_INTENSET_PREGION1RA_Pos) /*!< Bit mask of PREGION1RA field. */
#define MWU_INTENSET_PREGION1RA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_INTENSET_PREGION1RA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_INTENSET_PREGION1RA_Set (1UL) /*!< Enable */

/* Bit 26 : Write '1' to Enable interrupt for PREGION[1].WA event */
#define MWU_INTENSET_PREGION1WA_Pos (26UL) /*!< Position of PREGION1WA field. */
#define MWU_INTENSET_PREGION1WA_Msk (0x1UL << MWU_INTENSET_PREGION1WA_Pos) /*!< Bit mask of PREGION1WA field. */
#define MWU_INTENSET_PREGION1WA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_INTENSET_PREGION1WA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_INTENSET_PREGION1WA_Set (1UL) /*!< Enable */

/* Bit 25 : Write '1' to Enable interrupt for PREGION[0].RA event */
#define MWU_INTENSET_PREGION0RA_Pos (25UL) /*!< Position of PREGION0RA field. */
#define MWU_INTENSET_PREGION0RA_Msk (0x1UL << MWU_INTENSET_PREGION0RA_Pos) /*!< Bit mask of PREGION0RA field. */
#define MWU_INTENSET_PREGION0RA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_INTENSET_PREGION0RA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_INTENSET_PREGION0RA_Set (1UL) /*!< Enable */

/* Bit 24 : Write '1' to Enable interrupt for PREGION[0].WA event */
#define MWU_INTENSET_PREGION0WA_Pos (24UL) /*!< Position of PREGION0WA field. */
#define MWU_INTENSET_PREGION0WA_Msk (0x1UL << MWU_INTENSET_PREGION0WA_Pos) /*!< Bit mask of PREGION0WA field. */
#define MWU_INTENSET_PREGION0WA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_INTENSET_PREGION0WA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_INTENSET_PREGION0WA_Set (1UL) /*!< Enable */

/* Bit 7 : Write '1' to Enable interrupt for REGION[3].RA event */
#define MWU_INTENSET_REGION3RA_Pos (7UL) /*!< Position of REGION3RA field. */
#define MWU_INTENSET_REGION3RA_Msk (0x1UL << MWU_INTENSET_REGION3RA_Pos) /*!< Bit mask of REGION3RA field. */
#define MWU_INTENSET_REGION3RA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_INTENSET_REGION3RA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_INTENSET_REGION3RA_Set (1UL) /*!< Enable */

/* Bit 6 : Write '1' to Enable interrupt for REGION[3].WA event */
#define MWU_INTENSET_REGION3WA_Pos (6UL) /*!< Position of REGION3WA field. */
#define MWU_INTENSET_REGION3WA_Msk (0x1UL << MWU_INTENSET_REGION3WA_Pos) /*!< Bit mask of REGION3WA field. */
#define MWU_INTENSET_REGION3WA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_INTENSET_REGION3WA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_INTENSET_REGION3WA_Set (1UL) /*!< Enable */

/* Bit 5 : Write '1' to Enable interrupt for REGION[2].RA event */
#define MWU_INTENSET_REGION2RA_Pos (5UL) /*!< Position of REGION2RA field. */
#define MWU_INTENSET_REGION2RA_Msk (0x1UL << MWU_INTENSET_REGION2RA_Pos) /*!< Bit mask of REGION2RA field. */
#define MWU_INTENSET_REGION2RA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_INTENSET_REGION2RA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_INTENSET_REGION2RA_Set (1UL) /*!< Enable */

/* Bit 4 : Write '1' to Enable interrupt for REGION[2].WA event */
#define MWU_INTENSET_REGION2WA_Pos (4UL) /*!< Position of REGION2WA field. */
#define MWU_INTENSET_REGION2WA_Msk (0x1UL << MWU_INTENSET_REGION2WA_Pos) /*!< Bit mask of REGION2WA field. */
#define MWU_INTENSET_REGION2WA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_INTENSET_REGION2WA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_INTENSET_REGION2WA_Set (1UL) /*!< Enable */

/* Bit 3 : Write '1' to Enable interrupt for REGION[1].RA event */
#define MWU_INTENSET_REGION1RA_Pos (3UL) /*!< Position of REGION1RA field. */
#define MWU_INTENSET_REGION1RA_Msk (0x1UL << MWU_INTENSET_REGION1RA_Pos) /*!< Bit mask of REGION1RA field. */
#define MWU_INTENSET_REGION1RA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_INTENSET_REGION1RA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_INTENSET_REGION1RA_Set (1UL) /*!< Enable */

/* Bit 2 : Write '1' to Enable interrupt for REGION[1].WA event */
#define MWU_INTENSET_REGION1WA_Pos (2UL) /*!< Position of REGION1WA field. */
#define MWU_INTENSET_REGION1WA_Msk (0x1UL << MWU_INTENSET_REGION1WA_Pos) /*!< Bit mask of REGION1WA field. */
#define MWU_INTENSET_REGION1WA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_INTENSET_REGION1WA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_INTENSET_REGION1WA_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable interrupt for REGION[0].RA event */
#define MWU_INTENSET_REGION0RA_Pos (1UL) /*!< Position of REGION0RA field. */
#define MWU_INTENSET_REGION0RA_Msk (0x1UL << MWU_INTENSET_REGION0RA_Pos) /*!< Bit mask of REGION0RA field. */
#define MWU_INTENSET_REGION0RA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_INTENSET_REGION0RA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_INTENSET_REGION0RA_Set (1UL) /*!< Enable */

/* Bit 0 : Write '1' to Enable interrupt for REGION[0].WA event */
#define MWU_INTENSET_REGION0WA_Pos (0UL) /*!< Position of REGION0WA field. */
#define MWU_INTENSET_REGION0WA_Msk (0x1UL << MWU_INTENSET_REGION0WA_Pos) /*!< Bit mask of REGION0WA field. */
#define MWU_INTENSET_REGION0WA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_INTENSET_REGION0WA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_INTENSET_REGION0WA_Set (1UL) /*!< Enable */

/* Register: MWU_INTENCLR */
/* Description: Disable interrupt */

/* Bit 27 : Write '1' to Disable interrupt for PREGION[1].RA event */
#define MWU_INTENCLR_PREGION1RA_Pos (27UL) /*!< Position of PREGION1RA field. */
#define MWU_INTENCLR_PREGION1RA_Msk (0x1UL << MWU_INTENCLR_PREGION1RA_Pos) /*!< Bit mask of PREGION1RA field. */
#define MWU_INTENCLR_PREGION1RA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_INTENCLR_PREGION1RA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_INTENCLR_PREGION1RA_Clear (1UL) /*!< Disable */

/* Bit 26 : Write '1' to Disable interrupt for PREGION[1].WA event */
#define MWU_INTENCLR_PREGION1WA_Pos (26UL) /*!< Position of PREGION1WA field. */
#define MWU_INTENCLR_PREGION1WA_Msk (0x1UL << MWU_INTENCLR_PREGION1WA_Pos) /*!< Bit mask of PREGION1WA field. */
#define MWU_INTENCLR_PREGION1WA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_INTENCLR_PREGION1WA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_INTENCLR_PREGION1WA_Clear (1UL) /*!< Disable */

/* Bit 25 : Write '1' to Disable interrupt for PREGION[0].RA event */
#define MWU_INTENCLR_PREGION0RA_Pos (25UL) /*!< Position of PREGION0RA field. */
#define MWU_INTENCLR_PREGION0RA_Msk (0x1UL << MWU_INTENCLR_PREGION0RA_Pos) /*!< Bit mask of PREGION0RA field. */
#define MWU_INTENCLR_PREGION0RA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_INTENCLR_PREGION0RA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_INTENCLR_PREGION0RA_Clear (1UL) /*!< Disable */

/* Bit 24 : Write '1' to Disable interrupt for PREGION[0].WA event */
#define MWU_INTENCLR_PREGION0WA_Pos (24UL) /*!< Position of PREGION0WA field. */
#define MWU_INTENCLR_PREGION0WA_Msk (0x1UL << MWU_INTENCLR_PREGION0WA_Pos) /*!< Bit mask of PREGION0WA field. */
#define MWU_INTENCLR_PREGION0WA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_INTENCLR_PREGION0WA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_INTENCLR_PREGION0WA_Clear (1UL) /*!< Disable */

/* Bit 7 : Write '1' to Disable interrupt for REGION[3].RA event */
#define MWU_INTENCLR_REGION3RA_Pos (7UL) /*!< Position of REGION3RA field. */
#define MWU_INTENCLR_REGION3RA_Msk (0x1UL << MWU_INTENCLR_REGION3RA_Pos) /*!< Bit mask of REGION3RA field. */
#define MWU_INTENCLR_REGION3RA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_INTENCLR_REGION3RA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_INTENCLR_REGION3RA_Clear (1UL) /*!< Disable */

/* Bit 6 : Write '1' to Disable interrupt for REGION[3].WA event */
#define MWU_INTENCLR_REGION3WA_Pos (6UL) /*!< Position of REGION3WA field. */
#define MWU_INTENCLR_REGION3WA_Msk (0x1UL << MWU_INTENCLR_REGION3WA_Pos) /*!< Bit mask of REGION3WA field. */
#define MWU_INTENCLR_REGION3WA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_INTENCLR_REGION3WA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_INTENCLR_REGION3WA_Clear (1UL) /*!< Disable */

/* Bit 5 : Write '1' to Disable interrupt for REGION[2].RA event */
#define MWU_INTENCLR_REGION2RA_Pos (5UL) /*!< Position of REGION2RA field. */
#define MWU_INTENCLR_REGION2RA_Msk (0x1UL << MWU_INTENCLR_REGION2RA_Pos) /*!< Bit mask of REGION2RA field. */
#define MWU_INTENCLR_REGION2RA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_INTENCLR_REGION2RA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_INTENCLR_REGION2RA_Clear (1UL) /*!< Disable */

/* Bit 4 : Write '1' to Disable interrupt for REGION[2].WA event */
#define MWU_INTENCLR_REGION2WA_Pos (4UL) /*!< Position of REGION2WA field. */
#define MWU_INTENCLR_REGION2WA_Msk (0x1UL << MWU_INTENCLR_REGION2WA_Pos) /*!< Bit mask of REGION2WA field. */
#define MWU_INTENCLR_REGION2WA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_INTENCLR_REGION2WA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_INTENCLR_REGION2WA_Clear (1UL) /*!< Disable */

/* Bit 3 : Write '1' to Disable interrupt for REGION[1].RA event */
#define MWU_INTENCLR_REGION1RA_Pos (3UL) /*!< Position of REGION1RA field. */
#define MWU_INTENCLR_REGION1RA_Msk (0x1UL << MWU_INTENCLR_REGION1RA_Pos) /*!< Bit mask of REGION1RA field. */
#define MWU_INTENCLR_REGION1RA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_INTENCLR_REGION1RA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_INTENCLR_REGION1RA_Clear (1UL) /*!< Disable */

/* Bit 2 : Write '1' to Disable interrupt for REGION[1].WA event */
#define MWU_INTENCLR_REGION1WA_Pos (2UL) /*!< Position of REGION1WA field. */
#define MWU_INTENCLR_REGION1WA_Msk (0x1UL << MWU_INTENCLR_REGION1WA_Pos) /*!< Bit mask of REGION1WA field. */
#define MWU_INTENCLR_REGION1WA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_INTENCLR_REGION1WA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_INTENCLR_REGION1WA_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable interrupt for REGION[0].RA event */
#define MWU_INTENCLR_REGION0RA_Pos (1UL) /*!< Position of REGION0RA field. */
#define MWU_INTENCLR_REGION0RA_Msk (0x1UL << MWU_INTENCLR_REGION0RA_Pos) /*!< Bit mask of REGION0RA field. */
#define MWU_INTENCLR_REGION0RA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_INTENCLR_REGION0RA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_INTENCLR_REGION0RA_Clear (1UL) /*!< Disable */

/* Bit 0 : Write '1' to Disable interrupt for REGION[0].WA event */
#define MWU_INTENCLR_REGION0WA_Pos (0UL) /*!< Position of REGION0WA field. */
#define MWU_INTENCLR_REGION0WA_Msk (0x1UL << MWU_INTENCLR_REGION0WA_Pos) /*!< Bit mask of REGION0WA field. */
#define MWU_INTENCLR_REGION0WA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_INTENCLR_REGION0WA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_INTENCLR_REGION0WA_Clear (1UL) /*!< Disable */

/* Register: MWU_NMIEN */
/* Description: Enable or disable non-maskable interrupt */

/* Bit 27 : Enable or disable non-maskable interrupt for PREGION[1].RA event */
#define MWU_NMIEN_PREGION1RA_Pos (27UL) /*!< Position of PREGION1RA field. */
#define MWU_NMIEN_PREGION1RA_Msk (0x1UL << MWU_NMIEN_PREGION1RA_Pos) /*!< Bit mask of PREGION1RA field. */
#define MWU_NMIEN_PREGION1RA_Disabled (0UL) /*!< Disable */
#define MWU_NMIEN_PREGION1RA_Enabled (1UL) /*!< Enable */

/* Bit 26 : Enable or disable non-maskable interrupt for PREGION[1].WA event */
#define MWU_NMIEN_PREGION1WA_Pos (26UL) /*!< Position of PREGION1WA field. */
#define MWU_NMIEN_PREGION1WA_Msk (0x1UL << MWU_NMIEN_PREGION1WA_Pos) /*!< Bit mask of PREGION1WA field. */
#define MWU_NMIEN_PREGION1WA_Disabled (0UL) /*!< Disable */
#define MWU_NMIEN_PREGION1WA_Enabled (1UL) /*!< Enable */

/* Bit 25 : Enable or disable non-maskable interrupt for PREGION[0].RA event */
#define MWU_NMIEN_PREGION0RA_Pos (25UL) /*!< Position of PREGION0RA field. */
#define MWU_NMIEN_PREGION0RA_Msk (0x1UL << MWU_NMIEN_PREGION0RA_Pos) /*!< Bit mask of PREGION0RA field. */
#define MWU_NMIEN_PREGION0RA_Disabled (0UL) /*!< Disable */
#define MWU_NMIEN_PREGION0RA_Enabled (1UL) /*!< Enable */

/* Bit 24 : Enable or disable non-maskable interrupt for PREGION[0].WA event */
#define MWU_NMIEN_PREGION0WA_Pos (24UL) /*!< Position of PREGION0WA field. */
#define MWU_NMIEN_PREGION0WA_Msk (0x1UL << MWU_NMIEN_PREGION0WA_Pos) /*!< Bit mask of PREGION0WA field. */
#define MWU_NMIEN_PREGION0WA_Disabled (0UL) /*!< Disable */
#define MWU_NMIEN_PREGION0WA_Enabled (1UL) /*!< Enable */

/* Bit 7 : Enable or disable non-maskable interrupt for REGION[3].RA event */
#define MWU_NMIEN_REGION3RA_Pos (7UL) /*!< Position of REGION3RA field. */
#define MWU_NMIEN_REGION3RA_Msk (0x1UL << MWU_NMIEN_REGION3RA_Pos) /*!< Bit mask of REGION3RA field. */
#define MWU_NMIEN_REGION3RA_Disabled (0UL) /*!< Disable */
#define MWU_NMIEN_REGION3RA_Enabled (1UL) /*!< Enable */

/* Bit 6 : Enable or disable non-maskable interrupt for REGION[3].WA event */
#define MWU_NMIEN_REGION3WA_Pos (6UL) /*!< Position of REGION3WA field. */
#define MWU_NMIEN_REGION3WA_Msk (0x1UL << MWU_NMIEN_REGION3WA_Pos) /*!< Bit mask of REGION3WA field. */
#define MWU_NMIEN_REGION3WA_Disabled (0UL) /*!< Disable */
#define MWU_NMIEN_REGION3WA_Enabled (1UL) /*!< Enable */

/* Bit 5 : Enable or disable non-maskable interrupt for REGION[2].RA event */
#define MWU_NMIEN_REGION2RA_Pos (5UL) /*!< Position of REGION2RA field. */
#define MWU_NMIEN_REGION2RA_Msk (0x1UL << MWU_NMIEN_REGION2RA_Pos) /*!< Bit mask of REGION2RA field. */
#define MWU_NMIEN_REGION2RA_Disabled (0UL) /*!< Disable */
#define MWU_NMIEN_REGION2RA_Enabled (1UL) /*!< Enable */

/* Bit 4 : Enable or disable non-maskable interrupt for REGION[2].WA event */
#define MWU_NMIEN_REGION2WA_Pos (4UL) /*!< Position of REGION2WA field. */
#define MWU_NMIEN_REGION2WA_Msk (0x1UL << MWU_NMIEN_REGION2WA_Pos) /*!< Bit mask of REGION2WA field. */
#define MWU_NMIEN_REGION2WA_Disabled (0UL) /*!< Disable */
#define MWU_NMIEN_REGION2WA_Enabled (1UL) /*!< Enable */

/* Bit 3 : Enable or disable non-maskable interrupt for REGION[1].RA event */
#define MWU_NMIEN_REGION1RA_Pos (3UL) /*!< Position of REGION1RA field. */
#define MWU_NMIEN_REGION1RA_Msk (0x1UL << MWU_NMIEN_REGION1RA_Pos) /*!< Bit mask of REGION1RA field. */
#define MWU_NMIEN_REGION1RA_Disabled (0UL) /*!< Disable */
#define MWU_NMIEN_REGION1RA_Enabled (1UL) /*!< Enable */

/* Bit 2 : Enable or disable non-maskable interrupt for REGION[1].WA event */
#define MWU_NMIEN_REGION1WA_Pos (2UL) /*!< Position of REGION1WA field. */
#define MWU_NMIEN_REGION1WA_Msk (0x1UL << MWU_NMIEN_REGION1WA_Pos) /*!< Bit mask of REGION1WA field. */
#define MWU_NMIEN_REGION1WA_Disabled (0UL) /*!< Disable */
#define MWU_NMIEN_REGION1WA_Enabled (1UL) /*!< Enable */

/* Bit 1 : Enable or disable non-maskable interrupt for REGION[0].RA event */
#define MWU_NMIEN_REGION0RA_Pos (1UL) /*!< Position of REGION0RA field. */
#define MWU_NMIEN_REGION0RA_Msk (0x1UL << MWU_NMIEN_REGION0RA_Pos) /*!< Bit mask of REGION0RA field. */
#define MWU_NMIEN_REGION0RA_Disabled (0UL) /*!< Disable */
#define MWU_NMIEN_REGION0RA_Enabled (1UL) /*!< Enable */

/* Bit 0 : Enable or disable non-maskable interrupt for REGION[0].WA event */
#define MWU_NMIEN_REGION0WA_Pos (0UL) /*!< Position of REGION0WA field. */
#define MWU_NMIEN_REGION0WA_Msk (0x1UL << MWU_NMIEN_REGION0WA_Pos) /*!< Bit mask of REGION0WA field. */
#define MWU_NMIEN_REGION0WA_Disabled (0UL) /*!< Disable */
#define MWU_NMIEN_REGION0WA_Enabled (1UL) /*!< Enable */

/* Register: MWU_NMIENSET */
/* Description: Enable non-maskable interrupt */

/* Bit 27 : Write '1' to Enable non-maskable interrupt for PREGION[1].RA event */
#define MWU_NMIENSET_PREGION1RA_Pos (27UL) /*!< Position of PREGION1RA field. */
#define MWU_NMIENSET_PREGION1RA_Msk (0x1UL << MWU_NMIENSET_PREGION1RA_Pos) /*!< Bit mask of PREGION1RA field. */
#define MWU_NMIENSET_PREGION1RA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_NMIENSET_PREGION1RA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_NMIENSET_PREGION1RA_Set (1UL) /*!< Enable */

/* Bit 26 : Write '1' to Enable non-maskable interrupt for PREGION[1].WA event */
#define MWU_NMIENSET_PREGION1WA_Pos (26UL) /*!< Position of PREGION1WA field. */
#define MWU_NMIENSET_PREGION1WA_Msk (0x1UL << MWU_NMIENSET_PREGION1WA_Pos) /*!< Bit mask of PREGION1WA field. */
#define MWU_NMIENSET_PREGION1WA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_NMIENSET_PREGION1WA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_NMIENSET_PREGION1WA_Set (1UL) /*!< Enable */

/* Bit 25 : Write '1' to Enable non-maskable interrupt for PREGION[0].RA event */
#define MWU_NMIENSET_PREGION0RA_Pos (25UL) /*!< Position of PREGION0RA field. */
#define MWU_NMIENSET_PREGION0RA_Msk (0x1UL << MWU_NMIENSET_PREGION0RA_Pos) /*!< Bit mask of PREGION0RA field. */
#define MWU_NMIENSET_PREGION0RA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_NMIENSET_PREGION0RA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_NMIENSET_PREGION0RA_Set (1UL) /*!< Enable */

/* Bit 24 : Write '1' to Enable non-maskable interrupt for PREGION[0].WA event */
#define MWU_NMIENSET_PREGION0WA_Pos (24UL) /*!< Position of PREGION0WA field. */
#define MWU_NMIENSET_PREGION0WA_Msk (0x1UL << MWU_NMIENSET_PREGION0WA_Pos) /*!< Bit mask of PREGION0WA field. */
#define MWU_NMIENSET_PREGION0WA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_NMIENSET_PREGION0WA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_NMIENSET_PREGION0WA_Set (1UL) /*!< Enable */

/* Bit 7 : Write '1' to Enable non-maskable interrupt for REGION[3].RA event */
#define MWU_NMIENSET_REGION3RA_Pos (7UL) /*!< Position of REGION3RA field. */
#define MWU_NMIENSET_REGION3RA_Msk (0x1UL << MWU_NMIENSET_REGION3RA_Pos) /*!< Bit mask of REGION3RA field. */
#define MWU_NMIENSET_REGION3RA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_NMIENSET_REGION3RA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_NMIENSET_REGION3RA_Set (1UL) /*!< Enable */

/* Bit 6 : Write '1' to Enable non-maskable interrupt for REGION[3].WA event */
#define MWU_NMIENSET_REGION3WA_Pos (6UL) /*!< Position of REGION3WA field. */
#define MWU_NMIENSET_REGION3WA_Msk (0x1UL << MWU_NMIENSET_REGION3WA_Pos) /*!< Bit mask of REGION3WA field. */
#define MWU_NMIENSET_REGION3WA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_NMIENSET_REGION3WA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_NMIENSET_REGION3WA_Set (1UL) /*!< Enable */

/* Bit 5 : Write '1' to Enable non-maskable interrupt for REGION[2].RA event */
#define MWU_NMIENSET_REGION2RA_Pos (5UL) /*!< Position of REGION2RA field. */
#define MWU_NMIENSET_REGION2RA_Msk (0x1UL << MWU_NMIENSET_REGION2RA_Pos) /*!< Bit mask of REGION2RA field. */
#define MWU_NMIENSET_REGION2RA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_NMIENSET_REGION2RA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_NMIENSET_REGION2RA_Set (1UL) /*!< Enable */

/* Bit 4 : Write '1' to Enable non-maskable interrupt for REGION[2].WA event */
#define MWU_NMIENSET_REGION2WA_Pos (4UL) /*!< Position of REGION2WA field. */
#define MWU_NMIENSET_REGION2WA_Msk (0x1UL << MWU_NMIENSET_REGION2WA_Pos) /*!< Bit mask of REGION2WA field. */
#define MWU_NMIENSET_REGION2WA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_NMIENSET_REGION2WA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_NMIENSET_REGION2WA_Set (1UL) /*!< Enable */

/* Bit 3 : Write '1' to Enable non-maskable interrupt for REGION[1].RA event */
#define MWU_NMIENSET_REGION1RA_Pos (3UL) /*!< Position of REGION1RA field. */
#define MWU_NMIENSET_REGION1RA_Msk (0x1UL << MWU_NMIENSET_REGION1RA_Pos) /*!< Bit mask of REGION1RA field. */
#define MWU_NMIENSET_REGION1RA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_NMIENSET_REGION1RA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_NMIENSET_REGION1RA_Set (1UL) /*!< Enable */

/* Bit 2 : Write '1' to Enable non-maskable interrupt for REGION[1].WA event */
#define MWU_NMIENSET_REGION1WA_Pos (2UL) /*!< Position of REGION1WA field. */
#define MWU_NMIENSET_REGION1WA_Msk (0x1UL << MWU_NMIENSET_REGION1WA_Pos) /*!< Bit mask of REGION1WA field. */
#define MWU_NMIENSET_REGION1WA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_NMIENSET_REGION1WA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_NMIENSET_REGION1WA_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable non-maskable interrupt for REGION[0].RA event */
#define MWU_NMIENSET_REGION0RA_Pos (1UL) /*!< Position of REGION0RA field. */
#define MWU_NMIENSET_REGION0RA_Msk (0x1UL << MWU_NMIENSET_REGION0RA_Pos) /*!< Bit mask of REGION0RA field. */
#define MWU_NMIENSET_REGION0RA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_NMIENSET_REGION0RA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_NMIENSET_REGION0RA_Set (1UL) /*!< Enable */

/* Bit 0 : Write '1' to Enable non-maskable interrupt for REGION[0].WA event */
#define MWU_NMIENSET_REGION0WA_Pos (0UL) /*!< Position of REGION0WA field. */
#define MWU_NMIENSET_REGION0WA_Msk (0x1UL << MWU_NMIENSET_REGION0WA_Pos) /*!< Bit mask of REGION0WA field. */
#define MWU_NMIENSET_REGION0WA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_NMIENSET_REGION0WA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_NMIENSET_REGION0WA_Set (1UL) /*!< Enable */

/* Register: MWU_NMIENCLR */
/* Description: Disable non-maskable interrupt */

/* Bit 27 : Write '1' to Disable non-maskable interrupt for PREGION[1].RA event */
#define MWU_NMIENCLR_PREGION1RA_Pos (27UL) /*!< Position of PREGION1RA field. */
#define MWU_NMIENCLR_PREGION1RA_Msk (0x1UL << MWU_NMIENCLR_PREGION1RA_Pos) /*!< Bit mask of PREGION1RA field. */
#define MWU_NMIENCLR_PREGION1RA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_NMIENCLR_PREGION1RA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_NMIENCLR_PREGION1RA_Clear (1UL) /*!< Disable */

/* Bit 26 : Write '1' to Disable non-maskable interrupt for PREGION[1].WA event */
#define MWU_NMIENCLR_PREGION1WA_Pos (26UL) /*!< Position of PREGION1WA field. */
#define MWU_NMIENCLR_PREGION1WA_Msk (0x1UL << MWU_NMIENCLR_PREGION1WA_Pos) /*!< Bit mask of PREGION1WA field. */
#define MWU_NMIENCLR_PREGION1WA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_NMIENCLR_PREGION1WA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_NMIENCLR_PREGION1WA_Clear (1UL) /*!< Disable */

/* Bit 25 : Write '1' to Disable non-maskable interrupt for PREGION[0].RA event */
#define MWU_NMIENCLR_PREGION0RA_Pos (25UL) /*!< Position of PREGION0RA field. */
#define MWU_NMIENCLR_PREGION0RA_Msk (0x1UL << MWU_NMIENCLR_PREGION0RA_Pos) /*!< Bit mask of PREGION0RA field. */
#define MWU_NMIENCLR_PREGION0RA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_NMIENCLR_PREGION0RA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_NMIENCLR_PREGION0RA_Clear (1UL) /*!< Disable */

/* Bit 24 : Write '1' to Disable non-maskable interrupt for PREGION[0].WA event */
#define MWU_NMIENCLR_PREGION0WA_Pos (24UL) /*!< Position of PREGION0WA field. */
#define MWU_NMIENCLR_PREGION0WA_Msk (0x1UL << MWU_NMIENCLR_PREGION0WA_Pos) /*!< Bit mask of PREGION0WA field. */
#define MWU_NMIENCLR_PREGION0WA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_NMIENCLR_PREGION0WA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_NMIENCLR_PREGION0WA_Clear (1UL) /*!< Disable */

/* Bit 7 : Write '1' to Disable non-maskable interrupt for REGION[3].RA event */
#define MWU_NMIENCLR_REGION3RA_Pos (7UL) /*!< Position of REGION3RA field. */
#define MWU_NMIENCLR_REGION3RA_Msk (0x1UL << MWU_NMIENCLR_REGION3RA_Pos) /*!< Bit mask of REGION3RA field. */
#define MWU_NMIENCLR_REGION3RA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_NMIENCLR_REGION3RA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_NMIENCLR_REGION3RA_Clear (1UL) /*!< Disable */

/* Bit 6 : Write '1' to Disable non-maskable interrupt for REGION[3].WA event */
#define MWU_NMIENCLR_REGION3WA_Pos (6UL) /*!< Position of REGION3WA field. */
#define MWU_NMIENCLR_REGION3WA_Msk (0x1UL << MWU_NMIENCLR_REGION3WA_Pos) /*!< Bit mask of REGION3WA field. */
#define MWU_NMIENCLR_REGION3WA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_NMIENCLR_REGION3WA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_NMIENCLR_REGION3WA_Clear (1UL) /*!< Disable */

/* Bit 5 : Write '1' to Disable non-maskable interrupt for REGION[2].RA event */
#define MWU_NMIENCLR_REGION2RA_Pos (5UL) /*!< Position of REGION2RA field. */
#define MWU_NMIENCLR_REGION2RA_Msk (0x1UL << MWU_NMIENCLR_REGION2RA_Pos) /*!< Bit mask of REGION2RA field. */
#define MWU_NMIENCLR_REGION2RA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_NMIENCLR_REGION2RA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_NMIENCLR_REGION2RA_Clear (1UL) /*!< Disable */

/* Bit 4 : Write '1' to Disable non-maskable interrupt for REGION[2].WA event */
#define MWU_NMIENCLR_REGION2WA_Pos (4UL) /*!< Position of REGION2WA field. */
#define MWU_NMIENCLR_REGION2WA_Msk (0x1UL << MWU_NMIENCLR_REGION2WA_Pos) /*!< Bit mask of REGION2WA field. */
#define MWU_NMIENCLR_REGION2WA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_NMIENCLR_REGION2WA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_NMIENCLR_REGION2WA_Clear (1UL) /*!< Disable */

/* Bit 3 : Write '1' to Disable non-maskable interrupt for REGION[1].RA event */
#define MWU_NMIENCLR_REGION1RA_Pos (3UL) /*!< Position of REGION1RA field. */
#define MWU_NMIENCLR_REGION1RA_Msk (0x1UL << MWU_NMIENCLR_REGION1RA_Pos) /*!< Bit mask of REGION1RA field. */
#define MWU_NMIENCLR_REGION1RA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_NMIENCLR_REGION1RA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_NMIENCLR_REGION1RA_Clear (1UL) /*!< Disable */

/* Bit 2 : Write '1' to Disable non-maskable interrupt for REGION[1].WA event */
#define MWU_NMIENCLR_REGION1WA_Pos (2UL) /*!< Position of REGION1WA field. */
#define MWU_NMIENCLR_REGION1WA_Msk (0x1UL << MWU_NMIENCLR_REGION1WA_Pos) /*!< Bit mask of REGION1WA field. */
#define MWU_NMIENCLR_REGION1WA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_NMIENCLR_REGION1WA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_NMIENCLR_REGION1WA_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable non-maskable interrupt for REGION[0].RA event */
#define MWU_NMIENCLR_REGION0RA_Pos (1UL) /*!< Position of REGION0RA field. */
#define MWU_NMIENCLR_REGION0RA_Msk (0x1UL << MWU_NMIENCLR_REGION0RA_Pos) /*!< Bit mask of REGION0RA field. */
#define MWU_NMIENCLR_REGION0RA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_NMIENCLR_REGION0RA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_NMIENCLR_REGION0RA_Clear (1UL) /*!< Disable */

/* Bit 0 : Write '1' to Disable non-maskable interrupt for REGION[0].WA event */
#define MWU_NMIENCLR_REGION0WA_Pos (0UL) /*!< Position of REGION0WA field. */
#define MWU_NMIENCLR_REGION0WA_Msk (0x1UL << MWU_NMIENCLR_REGION0WA_Pos) /*!< Bit mask of REGION0WA field. */
#define MWU_NMIENCLR_REGION0WA_Disabled (0UL) /*!< Read: Disabled */
#define MWU_NMIENCLR_REGION0WA_Enabled (1UL) /*!< Read: Enabled */
#define MWU_NMIENCLR_REGION0WA_Clear (1UL) /*!< Disable */

/* Register: MWU_PERREGION_SUBSTATWA */
/* Description: Description cluster[0]:  Source of event/interrupt in region 0, write access detected while corresponding subregion was enabled for watching */

/* Bit 31 : Subregion 31 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR31_Pos (31UL) /*!< Position of SR31 field. */
#define MWU_PERREGION_SUBSTATWA_SR31_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR31_Pos) /*!< Bit mask of SR31 field. */
#define MWU_PERREGION_SUBSTATWA_SR31_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR31_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 30 : Subregion 30 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR30_Pos (30UL) /*!< Position of SR30 field. */
#define MWU_PERREGION_SUBSTATWA_SR30_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR30_Pos) /*!< Bit mask of SR30 field. */
#define MWU_PERREGION_SUBSTATWA_SR30_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR30_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 29 : Subregion 29 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR29_Pos (29UL) /*!< Position of SR29 field. */
#define MWU_PERREGION_SUBSTATWA_SR29_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR29_Pos) /*!< Bit mask of SR29 field. */
#define MWU_PERREGION_SUBSTATWA_SR29_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR29_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 28 : Subregion 28 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR28_Pos (28UL) /*!< Position of SR28 field. */
#define MWU_PERREGION_SUBSTATWA_SR28_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR28_Pos) /*!< Bit mask of SR28 field. */
#define MWU_PERREGION_SUBSTATWA_SR28_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR28_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 27 : Subregion 27 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR27_Pos (27UL) /*!< Position of SR27 field. */
#define MWU_PERREGION_SUBSTATWA_SR27_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR27_Pos) /*!< Bit mask of SR27 field. */
#define MWU_PERREGION_SUBSTATWA_SR27_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR27_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 26 : Subregion 26 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR26_Pos (26UL) /*!< Position of SR26 field. */
#define MWU_PERREGION_SUBSTATWA_SR26_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR26_Pos) /*!< Bit mask of SR26 field. */
#define MWU_PERREGION_SUBSTATWA_SR26_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR26_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 25 : Subregion 25 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR25_Pos (25UL) /*!< Position of SR25 field. */
#define MWU_PERREGION_SUBSTATWA_SR25_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR25_Pos) /*!< Bit mask of SR25 field. */
#define MWU_PERREGION_SUBSTATWA_SR25_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR25_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 24 : Subregion 24 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR24_Pos (24UL) /*!< Position of SR24 field. */
#define MWU_PERREGION_SUBSTATWA_SR24_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR24_Pos) /*!< Bit mask of SR24 field. */
#define MWU_PERREGION_SUBSTATWA_SR24_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR24_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 23 : Subregion 23 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR23_Pos (23UL) /*!< Position of SR23 field. */
#define MWU_PERREGION_SUBSTATWA_SR23_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR23_Pos) /*!< Bit mask of SR23 field. */
#define MWU_PERREGION_SUBSTATWA_SR23_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR23_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 22 : Subregion 22 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR22_Pos (22UL) /*!< Position of SR22 field. */
#define MWU_PERREGION_SUBSTATWA_SR22_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR22_Pos) /*!< Bit mask of SR22 field. */
#define MWU_PERREGION_SUBSTATWA_SR22_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR22_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 21 : Subregion 21 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR21_Pos (21UL) /*!< Position of SR21 field. */
#define MWU_PERREGION_SUBSTATWA_SR21_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR21_Pos) /*!< Bit mask of SR21 field. */
#define MWU_PERREGION_SUBSTATWA_SR21_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR21_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 20 : Subregion 20 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR20_Pos (20UL) /*!< Position of SR20 field. */
#define MWU_PERREGION_SUBSTATWA_SR20_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR20_Pos) /*!< Bit mask of SR20 field. */
#define MWU_PERREGION_SUBSTATWA_SR20_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR20_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 19 : Subregion 19 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR19_Pos (19UL) /*!< Position of SR19 field. */
#define MWU_PERREGION_SUBSTATWA_SR19_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR19_Pos) /*!< Bit mask of SR19 field. */
#define MWU_PERREGION_SUBSTATWA_SR19_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR19_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 18 : Subregion 18 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR18_Pos (18UL) /*!< Position of SR18 field. */
#define MWU_PERREGION_SUBSTATWA_SR18_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR18_Pos) /*!< Bit mask of SR18 field. */
#define MWU_PERREGION_SUBSTATWA_SR18_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR18_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 17 : Subregion 17 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR17_Pos (17UL) /*!< Position of SR17 field. */
#define MWU_PERREGION_SUBSTATWA_SR17_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR17_Pos) /*!< Bit mask of SR17 field. */
#define MWU_PERREGION_SUBSTATWA_SR17_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR17_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 16 : Subregion 16 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR16_Pos (16UL) /*!< Position of SR16 field. */
#define MWU_PERREGION_SUBSTATWA_SR16_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR16_Pos) /*!< Bit mask of SR16 field. */
#define MWU_PERREGION_SUBSTATWA_SR16_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR16_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 15 : Subregion 15 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR15_Pos (15UL) /*!< Position of SR15 field. */
#define MWU_PERREGION_SUBSTATWA_SR15_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR15_Pos) /*!< Bit mask of SR15 field. */
#define MWU_PERREGION_SUBSTATWA_SR15_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR15_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 14 : Subregion 14 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR14_Pos (14UL) /*!< Position of SR14 field. */
#define MWU_PERREGION_SUBSTATWA_SR14_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR14_Pos) /*!< Bit mask of SR14 field. */
#define MWU_PERREGION_SUBSTATWA_SR14_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR14_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 13 : Subregion 13 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR13_Pos (13UL) /*!< Position of SR13 field. */
#define MWU_PERREGION_SUBSTATWA_SR13_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR13_Pos) /*!< Bit mask of SR13 field. */
#define MWU_PERREGION_SUBSTATWA_SR13_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR13_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 12 : Subregion 12 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR12_Pos (12UL) /*!< Position of SR12 field. */
#define MWU_PERREGION_SUBSTATWA_SR12_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR12_Pos) /*!< Bit mask of SR12 field. */
#define MWU_PERREGION_SUBSTATWA_SR12_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR12_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 11 : Subregion 11 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR11_Pos (11UL) /*!< Position of SR11 field. */
#define MWU_PERREGION_SUBSTATWA_SR11_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR11_Pos) /*!< Bit mask of SR11 field. */
#define MWU_PERREGION_SUBSTATWA_SR11_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR11_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 10 : Subregion 10 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR10_Pos (10UL) /*!< Position of SR10 field. */
#define MWU_PERREGION_SUBSTATWA_SR10_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR10_Pos) /*!< Bit mask of SR10 field. */
#define MWU_PERREGION_SUBSTATWA_SR10_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR10_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 9 : Subregion 9 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR9_Pos (9UL) /*!< Position of SR9 field. */
#define MWU_PERREGION_SUBSTATWA_SR9_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR9_Pos) /*!< Bit mask of SR9 field. */
#define MWU_PERREGION_SUBSTATWA_SR9_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR9_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 8 : Subregion 8 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR8_Pos (8UL) /*!< Position of SR8 field. */
#define MWU_PERREGION_SUBSTATWA_SR8_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR8_Pos) /*!< Bit mask of SR8 field. */
#define MWU_PERREGION_SUBSTATWA_SR8_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR8_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 7 : Subregion 7 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR7_Pos (7UL) /*!< Position of SR7 field. */
#define MWU_PERREGION_SUBSTATWA_SR7_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR7_Pos) /*!< Bit mask of SR7 field. */
#define MWU_PERREGION_SUBSTATWA_SR7_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR7_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 6 : Subregion 6 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR6_Pos (6UL) /*!< Position of SR6 field. */
#define MWU_PERREGION_SUBSTATWA_SR6_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR6_Pos) /*!< Bit mask of SR6 field. */
#define MWU_PERREGION_SUBSTATWA_SR6_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR6_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 5 : Subregion 5 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR5_Pos (5UL) /*!< Position of SR5 field. */
#define MWU_PERREGION_SUBSTATWA_SR5_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR5_Pos) /*!< Bit mask of SR5 field. */
#define MWU_PERREGION_SUBSTATWA_SR5_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR5_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 4 : Subregion 4 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR4_Pos (4UL) /*!< Position of SR4 field. */
#define MWU_PERREGION_SUBSTATWA_SR4_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR4_Pos) /*!< Bit mask of SR4 field. */
#define MWU_PERREGION_SUBSTATWA_SR4_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR4_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 3 : Subregion 3 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR3_Pos (3UL) /*!< Position of SR3 field. */
#define MWU_PERREGION_SUBSTATWA_SR3_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR3_Pos) /*!< Bit mask of SR3 field. */
#define MWU_PERREGION_SUBSTATWA_SR3_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR3_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 2 : Subregion 2 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR2_Pos (2UL) /*!< Position of SR2 field. */
#define MWU_PERREGION_SUBSTATWA_SR2_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR2_Pos) /*!< Bit mask of SR2 field. */
#define MWU_PERREGION_SUBSTATWA_SR2_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR2_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 1 : Subregion 1 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR1_Pos (1UL) /*!< Position of SR1 field. */
#define MWU_PERREGION_SUBSTATWA_SR1_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR1_Pos) /*!< Bit mask of SR1 field. */
#define MWU_PERREGION_SUBSTATWA_SR1_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR1_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Bit 0 : Subregion 0 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATWA_SR0_Pos (0UL) /*!< Position of SR0 field. */
#define MWU_PERREGION_SUBSTATWA_SR0_Msk (0x1UL << MWU_PERREGION_SUBSTATWA_SR0_Pos) /*!< Bit mask of SR0 field. */
#define MWU_PERREGION_SUBSTATWA_SR0_NoAccess (0UL) /*!< No write access occurred in this subregion */
#define MWU_PERREGION_SUBSTATWA_SR0_Access (1UL) /*!< Write access(es) occurred in this subregion */

/* Register: MWU_PERREGION_SUBSTATRA */
/* Description: Description cluster[0]:  Source of event/interrupt in region 0, read access detected while corresponding subregion was enabled for watching */

/* Bit 31 : Subregion 31 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR31_Pos (31UL) /*!< Position of SR31 field. */
#define MWU_PERREGION_SUBSTATRA_SR31_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR31_Pos) /*!< Bit mask of SR31 field. */
#define MWU_PERREGION_SUBSTATRA_SR31_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR31_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 30 : Subregion 30 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR30_Pos (30UL) /*!< Position of SR30 field. */
#define MWU_PERREGION_SUBSTATRA_SR30_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR30_Pos) /*!< Bit mask of SR30 field. */
#define MWU_PERREGION_SUBSTATRA_SR30_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR30_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 29 : Subregion 29 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR29_Pos (29UL) /*!< Position of SR29 field. */
#define MWU_PERREGION_SUBSTATRA_SR29_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR29_Pos) /*!< Bit mask of SR29 field. */
#define MWU_PERREGION_SUBSTATRA_SR29_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR29_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 28 : Subregion 28 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR28_Pos (28UL) /*!< Position of SR28 field. */
#define MWU_PERREGION_SUBSTATRA_SR28_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR28_Pos) /*!< Bit mask of SR28 field. */
#define MWU_PERREGION_SUBSTATRA_SR28_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR28_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 27 : Subregion 27 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR27_Pos (27UL) /*!< Position of SR27 field. */
#define MWU_PERREGION_SUBSTATRA_SR27_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR27_Pos) /*!< Bit mask of SR27 field. */
#define MWU_PERREGION_SUBSTATRA_SR27_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR27_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 26 : Subregion 26 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR26_Pos (26UL) /*!< Position of SR26 field. */
#define MWU_PERREGION_SUBSTATRA_SR26_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR26_Pos) /*!< Bit mask of SR26 field. */
#define MWU_PERREGION_SUBSTATRA_SR26_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR26_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 25 : Subregion 25 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR25_Pos (25UL) /*!< Position of SR25 field. */
#define MWU_PERREGION_SUBSTATRA_SR25_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR25_Pos) /*!< Bit mask of SR25 field. */
#define MWU_PERREGION_SUBSTATRA_SR25_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR25_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 24 : Subregion 24 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR24_Pos (24UL) /*!< Position of SR24 field. */
#define MWU_PERREGION_SUBSTATRA_SR24_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR24_Pos) /*!< Bit mask of SR24 field. */
#define MWU_PERREGION_SUBSTATRA_SR24_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR24_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 23 : Subregion 23 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR23_Pos (23UL) /*!< Position of SR23 field. */
#define MWU_PERREGION_SUBSTATRA_SR23_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR23_Pos) /*!< Bit mask of SR23 field. */
#define MWU_PERREGION_SUBSTATRA_SR23_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR23_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 22 : Subregion 22 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR22_Pos (22UL) /*!< Position of SR22 field. */
#define MWU_PERREGION_SUBSTATRA_SR22_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR22_Pos) /*!< Bit mask of SR22 field. */
#define MWU_PERREGION_SUBSTATRA_SR22_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR22_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 21 : Subregion 21 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR21_Pos (21UL) /*!< Position of SR21 field. */
#define MWU_PERREGION_SUBSTATRA_SR21_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR21_Pos) /*!< Bit mask of SR21 field. */
#define MWU_PERREGION_SUBSTATRA_SR21_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR21_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 20 : Subregion 20 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR20_Pos (20UL) /*!< Position of SR20 field. */
#define MWU_PERREGION_SUBSTATRA_SR20_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR20_Pos) /*!< Bit mask of SR20 field. */
#define MWU_PERREGION_SUBSTATRA_SR20_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR20_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 19 : Subregion 19 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR19_Pos (19UL) /*!< Position of SR19 field. */
#define MWU_PERREGION_SUBSTATRA_SR19_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR19_Pos) /*!< Bit mask of SR19 field. */
#define MWU_PERREGION_SUBSTATRA_SR19_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR19_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 18 : Subregion 18 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR18_Pos (18UL) /*!< Position of SR18 field. */
#define MWU_PERREGION_SUBSTATRA_SR18_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR18_Pos) /*!< Bit mask of SR18 field. */
#define MWU_PERREGION_SUBSTATRA_SR18_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR18_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 17 : Subregion 17 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR17_Pos (17UL) /*!< Position of SR17 field. */
#define MWU_PERREGION_SUBSTATRA_SR17_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR17_Pos) /*!< Bit mask of SR17 field. */
#define MWU_PERREGION_SUBSTATRA_SR17_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR17_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 16 : Subregion 16 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR16_Pos (16UL) /*!< Position of SR16 field. */
#define MWU_PERREGION_SUBSTATRA_SR16_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR16_Pos) /*!< Bit mask of SR16 field. */
#define MWU_PERREGION_SUBSTATRA_SR16_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR16_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 15 : Subregion 15 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR15_Pos (15UL) /*!< Position of SR15 field. */
#define MWU_PERREGION_SUBSTATRA_SR15_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR15_Pos) /*!< Bit mask of SR15 field. */
#define MWU_PERREGION_SUBSTATRA_SR15_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR15_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 14 : Subregion 14 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR14_Pos (14UL) /*!< Position of SR14 field. */
#define MWU_PERREGION_SUBSTATRA_SR14_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR14_Pos) /*!< Bit mask of SR14 field. */
#define MWU_PERREGION_SUBSTATRA_SR14_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR14_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 13 : Subregion 13 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR13_Pos (13UL) /*!< Position of SR13 field. */
#define MWU_PERREGION_SUBSTATRA_SR13_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR13_Pos) /*!< Bit mask of SR13 field. */
#define MWU_PERREGION_SUBSTATRA_SR13_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR13_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 12 : Subregion 12 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR12_Pos (12UL) /*!< Position of SR12 field. */
#define MWU_PERREGION_SUBSTATRA_SR12_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR12_Pos) /*!< Bit mask of SR12 field. */
#define MWU_PERREGION_SUBSTATRA_SR12_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR12_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 11 : Subregion 11 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR11_Pos (11UL) /*!< Position of SR11 field. */
#define MWU_PERREGION_SUBSTATRA_SR11_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR11_Pos) /*!< Bit mask of SR11 field. */
#define MWU_PERREGION_SUBSTATRA_SR11_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR11_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 10 : Subregion 10 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR10_Pos (10UL) /*!< Position of SR10 field. */
#define MWU_PERREGION_SUBSTATRA_SR10_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR10_Pos) /*!< Bit mask of SR10 field. */
#define MWU_PERREGION_SUBSTATRA_SR10_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR10_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 9 : Subregion 9 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR9_Pos (9UL) /*!< Position of SR9 field. */
#define MWU_PERREGION_SUBSTATRA_SR9_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR9_Pos) /*!< Bit mask of SR9 field. */
#define MWU_PERREGION_SUBSTATRA_SR9_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR9_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 8 : Subregion 8 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR8_Pos (8UL) /*!< Position of SR8 field. */
#define MWU_PERREGION_SUBSTATRA_SR8_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR8_Pos) /*!< Bit mask of SR8 field. */
#define MWU_PERREGION_SUBSTATRA_SR8_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR8_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 7 : Subregion 7 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR7_Pos (7UL) /*!< Position of SR7 field. */
#define MWU_PERREGION_SUBSTATRA_SR7_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR7_Pos) /*!< Bit mask of SR7 field. */
#define MWU_PERREGION_SUBSTATRA_SR7_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR7_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 6 : Subregion 6 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR6_Pos (6UL) /*!< Position of SR6 field. */
#define MWU_PERREGION_SUBSTATRA_SR6_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR6_Pos) /*!< Bit mask of SR6 field. */
#define MWU_PERREGION_SUBSTATRA_SR6_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR6_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 5 : Subregion 5 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR5_Pos (5UL) /*!< Position of SR5 field. */
#define MWU_PERREGION_SUBSTATRA_SR5_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR5_Pos) /*!< Bit mask of SR5 field. */
#define MWU_PERREGION_SUBSTATRA_SR5_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR5_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 4 : Subregion 4 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR4_Pos (4UL) /*!< Position of SR4 field. */
#define MWU_PERREGION_SUBSTATRA_SR4_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR4_Pos) /*!< Bit mask of SR4 field. */
#define MWU_PERREGION_SUBSTATRA_SR4_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR4_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 3 : Subregion 3 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR3_Pos (3UL) /*!< Position of SR3 field. */
#define MWU_PERREGION_SUBSTATRA_SR3_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR3_Pos) /*!< Bit mask of SR3 field. */
#define MWU_PERREGION_SUBSTATRA_SR3_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR3_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 2 : Subregion 2 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR2_Pos (2UL) /*!< Position of SR2 field. */
#define MWU_PERREGION_SUBSTATRA_SR2_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR2_Pos) /*!< Bit mask of SR2 field. */
#define MWU_PERREGION_SUBSTATRA_SR2_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR2_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 1 : Subregion 1 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR1_Pos (1UL) /*!< Position of SR1 field. */
#define MWU_PERREGION_SUBSTATRA_SR1_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR1_Pos) /*!< Bit mask of SR1 field. */
#define MWU_PERREGION_SUBSTATRA_SR1_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR1_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Bit 0 : Subregion 0 in region 0 (write '1' to clear) */
#define MWU_PERREGION_SUBSTATRA_SR0_Pos (0UL) /*!< Position of SR0 field. */
#define MWU_PERREGION_SUBSTATRA_SR0_Msk (0x1UL << MWU_PERREGION_SUBSTATRA_SR0_Pos) /*!< Bit mask of SR0 field. */
#define MWU_PERREGION_SUBSTATRA_SR0_NoAccess (0UL) /*!< No read access occurred in this subregion */
#define MWU_PERREGION_SUBSTATRA_SR0_Access (1UL) /*!< Read access(es) occurred in this subregion */

/* Register: MWU_REGIONEN */
/* Description: Enable/disable regions watch */

/* Bit 27 : Enable/disable read access watch in PREGION[1] */
#define MWU_REGIONEN_PRGN1RA_Pos (27UL) /*!< Position of PRGN1RA field. */
#define MWU_REGIONEN_PRGN1RA_Msk (0x1UL << MWU_REGIONEN_PRGN1RA_Pos) /*!< Bit mask of PRGN1RA field. */
#define MWU_REGIONEN_PRGN1RA_Disable (0UL) /*!< Disable read access watch in this PREGION */
#define MWU_REGIONEN_PRGN1RA_Enable (1UL) /*!< Enable read access watch in this PREGION */

/* Bit 26 : Enable/disable write access watch in PREGION[1] */
#define MWU_REGIONEN_PRGN1WA_Pos (26UL) /*!< Position of PRGN1WA field. */
#define MWU_REGIONEN_PRGN1WA_Msk (0x1UL << MWU_REGIONEN_PRGN1WA_Pos) /*!< Bit mask of PRGN1WA field. */
#define MWU_REGIONEN_PRGN1WA_Disable (0UL) /*!< Disable write access watch in this PREGION */
#define MWU_REGIONEN_PRGN1WA_Enable (1UL) /*!< Enable write access watch in this PREGION */

/* Bit 25 : Enable/disable read access watch in PREGION[0] */
#define MWU_REGIONEN_PRGN0RA_Pos (25UL) /*!< Position of PRGN0RA field. */
#define MWU_REGIONEN_PRGN0RA_Msk (0x1UL << MWU_REGIONEN_PRGN0RA_Pos) /*!< Bit mask of PRGN0RA field. */
#define MWU_REGIONEN_PRGN0RA_Disable (0UL) /*!< Disable read access watch in this PREGION */
#define MWU_REGIONEN_PRGN0RA_Enable (1UL) /*!< Enable read access watch in this PREGION */

/* Bit 24 : Enable/disable write access watch in PREGION[0] */
#define MWU_REGIONEN_PRGN0WA_Pos (24UL) /*!< Position of PRGN0WA field. */
#define MWU_REGIONEN_PRGN0WA_Msk (0x1UL << MWU_REGIONEN_PRGN0WA_Pos) /*!< Bit mask of PRGN0WA field. */
#define MWU_REGIONEN_PRGN0WA_Disable (0UL) /*!< Disable write access watch in this PREGION */
#define MWU_REGIONEN_PRGN0WA_Enable (1UL) /*!< Enable write access watch in this PREGION */

/* Bit 7 : Enable/disable read access watch in region[3] */
#define MWU_REGIONEN_RGN3RA_Pos (7UL) /*!< Position of RGN3RA field. */
#define MWU_REGIONEN_RGN3RA_Msk (0x1UL << MWU_REGIONEN_RGN3RA_Pos) /*!< Bit mask of RGN3RA field. */
#define MWU_REGIONEN_RGN3RA_Disable (0UL) /*!< Disable read access watch in this region */
#define MWU_REGIONEN_RGN3RA_Enable (1UL) /*!< Enable read access watch in this region */

/* Bit 6 : Enable/disable write access watch in region[3] */
#define MWU_REGIONEN_RGN3WA_Pos (6UL) /*!< Position of RGN3WA field. */
#define MWU_REGIONEN_RGN3WA_Msk (0x1UL << MWU_REGIONEN_RGN3WA_Pos) /*!< Bit mask of RGN3WA field. */
#define MWU_REGIONEN_RGN3WA_Disable (0UL) /*!< Disable write access watch in this region */
#define MWU_REGIONEN_RGN3WA_Enable (1UL) /*!< Enable write access watch in this region */

/* Bit 5 : Enable/disable read access watch in region[2] */
#define MWU_REGIONEN_RGN2RA_Pos (5UL) /*!< Position of RGN2RA field. */
#define MWU_REGIONEN_RGN2RA_Msk (0x1UL << MWU_REGIONEN_RGN2RA_Pos) /*!< Bit mask of RGN2RA field. */
#define MWU_REGIONEN_RGN2RA_Disable (0UL) /*!< Disable read access watch in this region */
#define MWU_REGIONEN_RGN2RA_Enable (1UL) /*!< Enable read access watch in this region */

/* Bit 4 : Enable/disable write access watch in region[2] */
#define MWU_REGIONEN_RGN2WA_Pos (4UL) /*!< Position of RGN2WA field. */
#define MWU_REGIONEN_RGN2WA_Msk (0x1UL << MWU_REGIONEN_RGN2WA_Pos) /*!< Bit mask of RGN2WA field. */
#define MWU_REGIONEN_RGN2WA_Disable (0UL) /*!< Disable write access watch in this region */
#define MWU_REGIONEN_RGN2WA_Enable (1UL) /*!< Enable write access watch in this region */

/* Bit 3 : Enable/disable read access watch in region[1] */
#define MWU_REGIONEN_RGN1RA_Pos (3UL) /*!< Position of RGN1RA field. */
#define MWU_REGIONEN_RGN1RA_Msk (0x1UL << MWU_REGIONEN_RGN1RA_Pos) /*!< Bit mask of RGN1RA field. */
#define MWU_REGIONEN_RGN1RA_Disable (0UL) /*!< Disable read access watch in this region */
#define MWU_REGIONEN_RGN1RA_Enable (1UL) /*!< Enable read access watch in this region */

/* Bit 2 : Enable/disable write access watch in region[1] */
#define MWU_REGIONEN_RGN1WA_Pos (2UL) /*!< Position of RGN1WA field. */
#define MWU_REGIONEN_RGN1WA_Msk (0x1UL << MWU_REGIONEN_RGN1WA_Pos) /*!< Bit mask of RGN1WA field. */
#define MWU_REGIONEN_RGN1WA_Disable (0UL) /*!< Disable write access watch in this region */
#define MWU_REGIONEN_RGN1WA_Enable (1UL) /*!< Enable write access watch in this region */

/* Bit 1 : Enable/disable read access watch in region[0] */
#define MWU_REGIONEN_RGN0RA_Pos (1UL) /*!< Position of RGN0RA field. */
#define MWU_REGIONEN_RGN0RA_Msk (0x1UL << MWU_REGIONEN_RGN0RA_Pos) /*!< Bit mask of RGN0RA field. */
#define MWU_REGIONEN_RGN0RA_Disable (0UL) /*!< Disable read access watch in this region */
#define MWU_REGIONEN_RGN0RA_Enable (1UL) /*!< Enable read access watch in this region */

/* Bit 0 : Enable/disable write access watch in region[0] */
#define MWU_REGIONEN_RGN0WA_Pos (0UL) /*!< Position of RGN0WA field. */
#define MWU_REGIONEN_RGN0WA_Msk (0x1UL << MWU_REGIONEN_RGN0WA_Pos) /*!< Bit mask of RGN0WA field. */
#define MWU_REGIONEN_RGN0WA_Disable (0UL) /*!< Disable write access watch in this region */
#define MWU_REGIONEN_RGN0WA_Enable (1UL) /*!< Enable write access watch in this region */

/* Register: MWU_REGIONENSET */
/* Description: Enable regions watch */

/* Bit 27 : Enable read access watch in PREGION[1] */
#define MWU_REGIONENSET_PRGN1RA_Pos (27UL) /*!< Position of PRGN1RA field. */
#define MWU_REGIONENSET_PRGN1RA_Msk (0x1UL << MWU_REGIONENSET_PRGN1RA_Pos) /*!< Bit mask of PRGN1RA field. */
#define MWU_REGIONENSET_PRGN1RA_Disabled (0UL) /*!< Read access watch in this PREGION is disabled */
#define MWU_REGIONENSET_PRGN1RA_Enabled (1UL) /*!< Read access watch in this PREGION is enabled */
#define MWU_REGIONENSET_PRGN1RA_Set (1UL) /*!< Enable read access watch in this PREGION */

/* Bit 26 : Enable write access watch in PREGION[1] */
#define MWU_REGIONENSET_PRGN1WA_Pos (26UL) /*!< Position of PRGN1WA field. */
#define MWU_REGIONENSET_PRGN1WA_Msk (0x1UL << MWU_REGIONENSET_PRGN1WA_Pos) /*!< Bit mask of PRGN1WA field. */
#define MWU_REGIONENSET_PRGN1WA_Disabled (0UL) /*!< Write access watch in this PREGION is disabled */
#define MWU_REGIONENSET_PRGN1WA_Enabled (1UL) /*!< Write access watch in this PREGION is enabled */
#define MWU_REGIONENSET_PRGN1WA_Set (1UL) /*!< Enable write access watch in this PREGION */

/* Bit 25 : Enable read access watch in PREGION[0] */
#define MWU_REGIONENSET_PRGN0RA_Pos (25UL) /*!< Position of PRGN0RA field. */
#define MWU_REGIONENSET_PRGN0RA_Msk (0x1UL << MWU_REGIONENSET_PRGN0RA_Pos) /*!< Bit mask of PRGN0RA field. */
#define MWU_REGIONENSET_PRGN0RA_Disabled (0UL) /*!< Read access watch in this PREGION is disabled */
#define MWU_REGIONENSET_PRGN0RA_Enabled (1UL) /*!< Read access watch in this PREGION is enabled */
#define MWU_REGIONENSET_PRGN0RA_Set (1UL) /*!< Enable read access watch in this PREGION */

/* Bit 24 : Enable write access watch in PREGION[0] */
#define MWU_REGIONENSET_PRGN0WA_Pos (24UL) /*!< Position of PRGN0WA field. */
#define MWU_REGIONENSET_PRGN0WA_Msk (0x1UL << MWU_REGIONENSET_PRGN0WA_Pos) /*!< Bit mask of PRGN0WA field. */
#define MWU_REGIONENSET_PRGN0WA_Disabled (0UL) /*!< Write access watch in this PREGION is disabled */
#define MWU_REGIONENSET_PRGN0WA_Enabled (1UL) /*!< Write access watch in this PREGION is enabled */
#define MWU_REGIONENSET_PRGN0WA_Set (1UL) /*!< Enable write access watch in this PREGION */

/* Bit 7 : Enable read access watch in region[3] */
#define MWU_REGIONENSET_RGN3RA_Pos (7UL) /*!< Position of RGN3RA field. */
#define MWU_REGIONENSET_RGN3RA_Msk (0x1UL << MWU_REGIONENSET_RGN3RA_Pos) /*!< Bit mask of RGN3RA field. */
#define MWU_REGIONENSET_RGN3RA_Disabled (0UL) /*!< Read access watch in this region is disabled */
#define MWU_REGIONENSET_RGN3RA_Enabled (1UL) /*!< Read access watch in this region is enabled */
#define MWU_REGIONENSET_RGN3RA_Set (1UL) /*!< Enable read access watch in this region */

/* Bit 6 : Enable write access watch in region[3] */
#define MWU_REGIONENSET_RGN3WA_Pos (6UL) /*!< Position of RGN3WA field. */
#define MWU_REGIONENSET_RGN3WA_Msk (0x1UL << MWU_REGIONENSET_RGN3WA_Pos) /*!< Bit mask of RGN3WA field. */
#define MWU_REGIONENSET_RGN3WA_Disabled (0UL) /*!< Write access watch in this region is disabled */
#define MWU_REGIONENSET_RGN3WA_Enabled (1UL) /*!< Write access watch in this region is enabled */
#define MWU_REGIONENSET_RGN3WA_Set (1UL) /*!< Enable write access watch in this region */

/* Bit 5 : Enable read access watch in region[2] */
#define MWU_REGIONENSET_RGN2RA_Pos (5UL) /*!< Position of RGN2RA field. */
#define MWU_REGIONENSET_RGN2RA_Msk (0x1UL << MWU_REGIONENSET_RGN2RA_Pos) /*!< Bit mask of RGN2RA field. */
#define MWU_REGIONENSET_RGN2RA_Disabled (0UL) /*!< Read access watch in this region is disabled */
#define MWU_REGIONENSET_RGN2RA_Enabled (1UL) /*!< Read access watch in this region is enabled */
#define MWU_REGIONENSET_RGN2RA_Set (1UL) /*!< Enable read access watch in this region */

/* Bit 4 : Enable write access watch in region[2] */
#define MWU_REGIONENSET_RGN2WA_Pos (4UL) /*!< Position of RGN2WA field. */
#define MWU_REGIONENSET_RGN2WA_Msk (0x1UL << MWU_REGIONENSET_RGN2WA_Pos) /*!< Bit mask of RGN2WA field. */
#define MWU_REGIONENSET_RGN2WA_Disabled (0UL) /*!< Write access watch in this region is disabled */
#define MWU_REGIONENSET_RGN2WA_Enabled (1UL) /*!< Write access watch in this region is enabled */
#define MWU_REGIONENSET_RGN2WA_Set (1UL) /*!< Enable write access watch in this region */

/* Bit 3 : Enable read access watch in region[1] */
#define MWU_REGIONENSET_RGN1RA_Pos (3UL) /*!< Position of RGN1RA field. */
#define MWU_REGIONENSET_RGN1RA_Msk (0x1UL << MWU_REGIONENSET_RGN1RA_Pos) /*!< Bit mask of RGN1RA field. */
#define MWU_REGIONENSET_RGN1RA_Disabled (0UL) /*!< Read access watch in this region is disabled */
#define MWU_REGIONENSET_RGN1RA_Enabled (1UL) /*!< Read access watch in this region is enabled */
#define MWU_REGIONENSET_RGN1RA_Set (1UL) /*!< Enable read access watch in this region */

/* Bit 2 : Enable write access watch in region[1] */
#define MWU_REGIONENSET_RGN1WA_Pos (2UL) /*!< Position of RGN1WA field. */
#define MWU_REGIONENSET_RGN1WA_Msk (0x1UL << MWU_REGIONENSET_RGN1WA_Pos) /*!< Bit mask of RGN1WA field. */
#define MWU_REGIONENSET_RGN1WA_Disabled (0UL) /*!< Write access watch in this region is disabled */
#define MWU_REGIONENSET_RGN1WA_Enabled (1UL) /*!< Write access watch in this region is enabled */
#define MWU_REGIONENSET_RGN1WA_Set (1UL) /*!< Enable write access watch in this region */

/* Bit 1 : Enable read access watch in region[0] */
#define MWU_REGIONENSET_RGN0RA_Pos (1UL) /*!< Position of RGN0RA field. */
#define MWU_REGIONENSET_RGN0RA_Msk (0x1UL << MWU_REGIONENSET_RGN0RA_Pos) /*!< Bit mask of RGN0RA field. */
#define MWU_REGIONENSET_RGN0RA_Disabled (0UL) /*!< Read access watch in this region is disabled */
#define MWU_REGIONENSET_RGN0RA_Enabled (1UL) /*!< Read access watch in this region is enabled */
#define MWU_REGIONENSET_RGN0RA_Set (1UL) /*!< Enable read access watch in this region */

/* Bit 0 : Enable write access watch in region[0] */
#define MWU_REGIONENSET_RGN0WA_Pos (0UL) /*!< Position of RGN0WA field. */
#define MWU_REGIONENSET_RGN0WA_Msk (0x1UL << MWU_REGIONENSET_RGN0WA_Pos) /*!< Bit mask of RGN0WA field. */
#define MWU_REGIONENSET_RGN0WA_Disabled (0UL) /*!< Write access watch in this region is disabled */
#define MWU_REGIONENSET_RGN0WA_Enabled (1UL) /*!< Write access watch in this region is enabled */
#define MWU_REGIONENSET_RGN0WA_Set (1UL) /*!< Enable write access watch in this region */

/* Register: MWU_REGIONENCLR */
/* Description: Disable regions watch */

/* Bit 27 : Disable read access watch in PREGION[1] */
#define MWU_REGIONENCLR_PRGN1RA_Pos (27UL) /*!< Position of PRGN1RA field. */
#define MWU_REGIONENCLR_PRGN1RA_Msk (0x1UL << MWU_REGIONENCLR_PRGN1RA_Pos) /*!< Bit mask of PRGN1RA field. */
#define MWU_REGIONENCLR_PRGN1RA_Disabled (0UL) /*!< Read access watch in this PREGION is disabled */
#define MWU_REGIONENCLR_PRGN1RA_Enabled (1UL) /*!< Read access watch in this PREGION is enabled */
#define MWU_REGIONENCLR_PRGN1RA_Clear (1UL) /*!< Disable read access watch in this PREGION */

/* Bit 26 : Disable write access watch in PREGION[1] */
#define MWU_REGIONENCLR_PRGN1WA_Pos (26UL) /*!< Position of PRGN1WA field. */
#define MWU_REGIONENCLR_PRGN1WA_Msk (0x1UL << MWU_REGIONENCLR_PRGN1WA_Pos) /*!< Bit mask of PRGN1WA field. */
#define MWU_REGIONENCLR_PRGN1WA_Disabled (0UL) /*!< Write access watch in this PREGION is disabled */
#define MWU_REGIONENCLR_PRGN1WA_Enabled (1UL) /*!< Write access watch in this PREGION is enabled */
#define MWU_REGIONENCLR_PRGN1WA_Clear (1UL) /*!< Disable write access watch in this PREGION */

/* Bit 25 : Disable read access watch in PREGION[0] */
#define MWU_REGIONENCLR_PRGN0RA_Pos (25UL) /*!< Position of PRGN0RA field. */
#define MWU_REGIONENCLR_PRGN0RA_Msk (0x1UL << MWU_REGIONENCLR_PRGN0RA_Pos) /*!< Bit mask of PRGN0RA field. */
#define MWU_REGIONENCLR_PRGN0RA_Disabled (0UL) /*!< Read access watch in this PREGION is disabled */
#define MWU_REGIONENCLR_PRGN0RA_Enabled (1UL) /*!< Read access watch in this PREGION is enabled */
#define MWU_REGIONENCLR_PRGN0RA_Clear (1UL) /*!< Disable read access watch in this PREGION */

/* Bit 24 : Disable write access watch in PREGION[0] */
#define MWU_REGIONENCLR_PRGN0WA_Pos (24UL) /*!< Position of PRGN0WA field. */
#define MWU_REGIONENCLR_PRGN0WA_Msk (0x1UL << MWU_REGIONENCLR_PRGN0WA_Pos) /*!< Bit mask of PRGN0WA field. */
#define MWU_REGIONENCLR_PRGN0WA_Disabled (0UL) /*!< Write access watch in this PREGION is disabled */
#define MWU_REGIONENCLR_PRGN0WA_Enabled (1UL) /*!< Write access watch in this PREGION is enabled */
#define MWU_REGIONENCLR_PRGN0WA_Clear (1UL) /*!< Disable write access watch in this PREGION */

/* Bit 7 : Disable read access watch in region[3] */
#define MWU_REGIONENCLR_RGN3RA_Pos (7UL) /*!< Position of RGN3RA field. */
#define MWU_REGIONENCLR_RGN3RA_Msk (0x1UL << MWU_REGIONENCLR_RGN3RA_Pos) /*!< Bit mask of RGN3RA field. */
#define MWU_REGIONENCLR_RGN3RA_Disabled (0UL) /*!< Read access watch in this region is disabled */
#define MWU_REGIONENCLR_RGN3RA_Enabled (1UL) /*!< Read access watch in this region is enabled */
#define MWU_REGIONENCLR_RGN3RA_Clear (1UL) /*!< Disable read access watch in this region */

/* Bit 6 : Disable write access watch in region[3] */
#define MWU_REGIONENCLR_RGN3WA_Pos (6UL) /*!< Position of RGN3WA field. */
#define MWU_REGIONENCLR_RGN3WA_Msk (0x1UL << MWU_REGIONENCLR_RGN3WA_Pos) /*!< Bit mask of RGN3WA field. */
#define MWU_REGIONENCLR_RGN3WA_Disabled (0UL) /*!< Write access watch in this region is disabled */
#define MWU_REGIONENCLR_RGN3WA_Enabled (1UL) /*!< Write access watch in this region is enabled */
#define MWU_REGIONENCLR_RGN3WA_Clear (1UL) /*!< Disable write access watch in this region */

/* Bit 5 : Disable read access watch in region[2] */
#define MWU_REGIONENCLR_RGN2RA_Pos (5UL) /*!< Position of RGN2RA field. */
#define MWU_REGIONENCLR_RGN2RA_Msk (0x1UL << MWU_REGIONENCLR_RGN2RA_Pos) /*!< Bit mask of RGN2RA field. */
#define MWU_REGIONENCLR_RGN2RA_Disabled (0UL) /*!< Read access watch in this region is disabled */
#define MWU_REGIONENCLR_RGN2RA_Enabled (1UL) /*!< Read access watch in this region is enabled */
#define MWU_REGIONENCLR_RGN2RA_Clear (1UL) /*!< Disable read access watch in this region */

/* Bit 4 : Disable write access watch in region[2] */
#define MWU_REGIONENCLR_RGN2WA_Pos (4UL) /*!< Position of RGN2WA field. */
#define MWU_REGIONENCLR_RGN2WA_Msk (0x1UL << MWU_REGIONENCLR_RGN2WA_Pos) /*!< Bit mask of RGN2WA field. */
#define MWU_REGIONENCLR_RGN2WA_Disabled (0UL) /*!< Write access watch in this region is disabled */
#define MWU_REGIONENCLR_RGN2WA_Enabled (1UL) /*!< Write access watch in this region is enabled */
#define MWU_REGIONENCLR_RGN2WA_Clear (1UL) /*!< Disable write access watch in this region */

/* Bit 3 : Disable read access watch in region[1] */
#define MWU_REGIONENCLR_RGN1RA_Pos (3UL) /*!< Position of RGN1RA field. */
#define MWU_REGIONENCLR_RGN1RA_Msk (0x1UL << MWU_REGIONENCLR_RGN1RA_Pos) /*!< Bit mask of RGN1RA field. */
#define MWU_REGIONENCLR_RGN1RA_Disabled (0UL) /*!< Read access watch in this region is disabled */
#define MWU_REGIONENCLR_RGN1RA_Enabled (1UL) /*!< Read access watch in this region is enabled */
#define MWU_REGIONENCLR_RGN1RA_Clear (1UL) /*!< Disable read access watch in this region */

/* Bit 2 : Disable write access watch in region[1] */
#define MWU_REGIONENCLR_RGN1WA_Pos (2UL) /*!< Position of RGN1WA field. */
#define MWU_REGIONENCLR_RGN1WA_Msk (0x1UL << MWU_REGIONENCLR_RGN1WA_Pos) /*!< Bit mask of RGN1WA field. */
#define MWU_REGIONENCLR_RGN1WA_Disabled (0UL) /*!< Write access watch in this region is disabled */
#define MWU_REGIONENCLR_RGN1WA_Enabled (1UL) /*!< Write access watch in this region is enabled */
#define MWU_REGIONENCLR_RGN1WA_Clear (1UL) /*!< Disable write access watch in this region */

/* Bit 1 : Disable read access watch in region[0] */
#define MWU_REGIONENCLR_RGN0RA_Pos (1UL) /*!< Position of RGN0RA field. */
#define MWU_REGIONENCLR_RGN0RA_Msk (0x1UL << MWU_REGIONENCLR_RGN0RA_Pos) /*!< Bit mask of RGN0RA field. */
#define MWU_REGIONENCLR_RGN0RA_Disabled (0UL) /*!< Read access watch in this region is disabled */
#define MWU_REGIONENCLR_RGN0RA_Enabled (1UL) /*!< Read access watch in this region is enabled */
#define MWU_REGIONENCLR_RGN0RA_Clear (1UL) /*!< Disable read access watch in this region */

/* Bit 0 : Disable write access watch in region[0] */
#define MWU_REGIONENCLR_RGN0WA_Pos (0UL) /*!< Position of RGN0WA field. */
#define MWU_REGIONENCLR_RGN0WA_Msk (0x1UL << MWU_REGIONENCLR_RGN0WA_Pos) /*!< Bit mask of RGN0WA field. */
#define MWU_REGIONENCLR_RGN0WA_Disabled (0UL) /*!< Write access watch in this region is disabled */
#define MWU_REGIONENCLR_RGN0WA_Enabled (1UL) /*!< Write access watch in this region is enabled */
#define MWU_REGIONENCLR_RGN0WA_Clear (1UL) /*!< Disable write access watch in this region */

/* Register: MWU_REGION_START */
/* Description: Description cluster[0]:  Start address for region 0 */

/* Bits 31..0 : Start address for region */
#define MWU_REGION_START_START_Pos (0UL) /*!< Position of START field. */
#define MWU_REGION_START_START_Msk (0xFFFFFFFFUL << MWU_REGION_START_START_Pos) /*!< Bit mask of START field. */

/* Register: MWU_REGION_END */
/* Description: Description cluster[0]:  End address of region 0 */

/* Bits 31..0 : End address of region. */
#define MWU_REGION_END_END_Pos (0UL) /*!< Position of END field. */
#define MWU_REGION_END_END_Msk (0xFFFFFFFFUL << MWU_REGION_END_END_Pos) /*!< Bit mask of END field. */

/* Register: MWU_PREGION_START */
/* Description: Description cluster[0]:  Reserved for future use */

/* Bits 31..0 : Reserved for future use */
#define MWU_PREGION_START_START_Pos (0UL) /*!< Position of START field. */
#define MWU_PREGION_START_START_Msk (0xFFFFFFFFUL << MWU_PREGION_START_START_Pos) /*!< Bit mask of START field. */

/* Register: MWU_PREGION_END */
/* Description: Description cluster[0]:  Reserved for future use */

/* Bits 31..0 : Reserved for future use */
#define MWU_PREGION_END_END_Pos (0UL) /*!< Position of END field. */
#define MWU_PREGION_END_END_Msk (0xFFFFFFFFUL << MWU_PREGION_END_END_Pos) /*!< Bit mask of END field. */

/* Register: MWU_PREGION_SUBS */
/* Description: Description cluster[0]:  Subregions of region 0 */

/* Bit 31 : Include or exclude subregion 31 in region */
#define MWU_PREGION_SUBS_SR31_Pos (31UL) /*!< Position of SR31 field. */
#define MWU_PREGION_SUBS_SR31_Msk (0x1UL << MWU_PREGION_SUBS_SR31_Pos) /*!< Bit mask of SR31 field. */
#define MWU_PREGION_SUBS_SR31_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR31_Include (1UL) /*!< Include */

/* Bit 30 : Include or exclude subregion 30 in region */
#define MWU_PREGION_SUBS_SR30_Pos (30UL) /*!< Position of SR30 field. */
#define MWU_PREGION_SUBS_SR30_Msk (0x1UL << MWU_PREGION_SUBS_SR30_Pos) /*!< Bit mask of SR30 field. */
#define MWU_PREGION_SUBS_SR30_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR30_Include (1UL) /*!< Include */

/* Bit 29 : Include or exclude subregion 29 in region */
#define MWU_PREGION_SUBS_SR29_Pos (29UL) /*!< Position of SR29 field. */
#define MWU_PREGION_SUBS_SR29_Msk (0x1UL << MWU_PREGION_SUBS_SR29_Pos) /*!< Bit mask of SR29 field. */
#define MWU_PREGION_SUBS_SR29_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR29_Include (1UL) /*!< Include */

/* Bit 28 : Include or exclude subregion 28 in region */
#define MWU_PREGION_SUBS_SR28_Pos (28UL) /*!< Position of SR28 field. */
#define MWU_PREGION_SUBS_SR28_Msk (0x1UL << MWU_PREGION_SUBS_SR28_Pos) /*!< Bit mask of SR28 field. */
#define MWU_PREGION_SUBS_SR28_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR28_Include (1UL) /*!< Include */

/* Bit 27 : Include or exclude subregion 27 in region */
#define MWU_PREGION_SUBS_SR27_Pos (27UL) /*!< Position of SR27 field. */
#define MWU_PREGION_SUBS_SR27_Msk (0x1UL << MWU_PREGION_SUBS_SR27_Pos) /*!< Bit mask of SR27 field. */
#define MWU_PREGION_SUBS_SR27_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR27_Include (1UL) /*!< Include */

/* Bit 26 : Include or exclude subregion 26 in region */
#define MWU_PREGION_SUBS_SR26_Pos (26UL) /*!< Position of SR26 field. */
#define MWU_PREGION_SUBS_SR26_Msk (0x1UL << MWU_PREGION_SUBS_SR26_Pos) /*!< Bit mask of SR26 field. */
#define MWU_PREGION_SUBS_SR26_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR26_Include (1UL) /*!< Include */

/* Bit 25 : Include or exclude subregion 25 in region */
#define MWU_PREGION_SUBS_SR25_Pos (25UL) /*!< Position of SR25 field. */
#define MWU_PREGION_SUBS_SR25_Msk (0x1UL << MWU_PREGION_SUBS_SR25_Pos) /*!< Bit mask of SR25 field. */
#define MWU_PREGION_SUBS_SR25_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR25_Include (1UL) /*!< Include */

/* Bit 24 : Include or exclude subregion 24 in region */
#define MWU_PREGION_SUBS_SR24_Pos (24UL) /*!< Position of SR24 field. */
#define MWU_PREGION_SUBS_SR24_Msk (0x1UL << MWU_PREGION_SUBS_SR24_Pos) /*!< Bit mask of SR24 field. */
#define MWU_PREGION_SUBS_SR24_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR24_Include (1UL) /*!< Include */

/* Bit 23 : Include or exclude subregion 23 in region */
#define MWU_PREGION_SUBS_SR23_Pos (23UL) /*!< Position of SR23 field. */
#define MWU_PREGION_SUBS_SR23_Msk (0x1UL << MWU_PREGION_SUBS_SR23_Pos) /*!< Bit mask of SR23 field. */
#define MWU_PREGION_SUBS_SR23_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR23_Include (1UL) /*!< Include */

/* Bit 22 : Include or exclude subregion 22 in region */
#define MWU_PREGION_SUBS_SR22_Pos (22UL) /*!< Position of SR22 field. */
#define MWU_PREGION_SUBS_SR22_Msk (0x1UL << MWU_PREGION_SUBS_SR22_Pos) /*!< Bit mask of SR22 field. */
#define MWU_PREGION_SUBS_SR22_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR22_Include (1UL) /*!< Include */

/* Bit 21 : Include or exclude subregion 21 in region */
#define MWU_PREGION_SUBS_SR21_Pos (21UL) /*!< Position of SR21 field. */
#define MWU_PREGION_SUBS_SR21_Msk (0x1UL << MWU_PREGION_SUBS_SR21_Pos) /*!< Bit mask of SR21 field. */
#define MWU_PREGION_SUBS_SR21_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR21_Include (1UL) /*!< Include */

/* Bit 20 : Include or exclude subregion 20 in region */
#define MWU_PREGION_SUBS_SR20_Pos (20UL) /*!< Position of SR20 field. */
#define MWU_PREGION_SUBS_SR20_Msk (0x1UL << MWU_PREGION_SUBS_SR20_Pos) /*!< Bit mask of SR20 field. */
#define MWU_PREGION_SUBS_SR20_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR20_Include (1UL) /*!< Include */

/* Bit 19 : Include or exclude subregion 19 in region */
#define MWU_PREGION_SUBS_SR19_Pos (19UL) /*!< Position of SR19 field. */
#define MWU_PREGION_SUBS_SR19_Msk (0x1UL << MWU_PREGION_SUBS_SR19_Pos) /*!< Bit mask of SR19 field. */
#define MWU_PREGION_SUBS_SR19_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR19_Include (1UL) /*!< Include */

/* Bit 18 : Include or exclude subregion 18 in region */
#define MWU_PREGION_SUBS_SR18_Pos (18UL) /*!< Position of SR18 field. */
#define MWU_PREGION_SUBS_SR18_Msk (0x1UL << MWU_PREGION_SUBS_SR18_Pos) /*!< Bit mask of SR18 field. */
#define MWU_PREGION_SUBS_SR18_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR18_Include (1UL) /*!< Include */

/* Bit 17 : Include or exclude subregion 17 in region */
#define MWU_PREGION_SUBS_SR17_Pos (17UL) /*!< Position of SR17 field. */
#define MWU_PREGION_SUBS_SR17_Msk (0x1UL << MWU_PREGION_SUBS_SR17_Pos) /*!< Bit mask of SR17 field. */
#define MWU_PREGION_SUBS_SR17_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR17_Include (1UL) /*!< Include */

/* Bit 16 : Include or exclude subregion 16 in region */
#define MWU_PREGION_SUBS_SR16_Pos (16UL) /*!< Position of SR16 field. */
#define MWU_PREGION_SUBS_SR16_Msk (0x1UL << MWU_PREGION_SUBS_SR16_Pos) /*!< Bit mask of SR16 field. */
#define MWU_PREGION_SUBS_SR16_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR16_Include (1UL) /*!< Include */

/* Bit 15 : Include or exclude subregion 15 in region */
#define MWU_PREGION_SUBS_SR15_Pos (15UL) /*!< Position of SR15 field. */
#define MWU_PREGION_SUBS_SR15_Msk (0x1UL << MWU_PREGION_SUBS_SR15_Pos) /*!< Bit mask of SR15 field. */
#define MWU_PREGION_SUBS_SR15_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR15_Include (1UL) /*!< Include */

/* Bit 14 : Include or exclude subregion 14 in region */
#define MWU_PREGION_SUBS_SR14_Pos (14UL) /*!< Position of SR14 field. */
#define MWU_PREGION_SUBS_SR14_Msk (0x1UL << MWU_PREGION_SUBS_SR14_Pos) /*!< Bit mask of SR14 field. */
#define MWU_PREGION_SUBS_SR14_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR14_Include (1UL) /*!< Include */

/* Bit 13 : Include or exclude subregion 13 in region */
#define MWU_PREGION_SUBS_SR13_Pos (13UL) /*!< Position of SR13 field. */
#define MWU_PREGION_SUBS_SR13_Msk (0x1UL << MWU_PREGION_SUBS_SR13_Pos) /*!< Bit mask of SR13 field. */
#define MWU_PREGION_SUBS_SR13_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR13_Include (1UL) /*!< Include */

/* Bit 12 : Include or exclude subregion 12 in region */
#define MWU_PREGION_SUBS_SR12_Pos (12UL) /*!< Position of SR12 field. */
#define MWU_PREGION_SUBS_SR12_Msk (0x1UL << MWU_PREGION_SUBS_SR12_Pos) /*!< Bit mask of SR12 field. */
#define MWU_PREGION_SUBS_SR12_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR12_Include (1UL) /*!< Include */

/* Bit 11 : Include or exclude subregion 11 in region */
#define MWU_PREGION_SUBS_SR11_Pos (11UL) /*!< Position of SR11 field. */
#define MWU_PREGION_SUBS_SR11_Msk (0x1UL << MWU_PREGION_SUBS_SR11_Pos) /*!< Bit mask of SR11 field. */
#define MWU_PREGION_SUBS_SR11_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR11_Include (1UL) /*!< Include */

/* Bit 10 : Include or exclude subregion 10 in region */
#define MWU_PREGION_SUBS_SR10_Pos (10UL) /*!< Position of SR10 field. */
#define MWU_PREGION_SUBS_SR10_Msk (0x1UL << MWU_PREGION_SUBS_SR10_Pos) /*!< Bit mask of SR10 field. */
#define MWU_PREGION_SUBS_SR10_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR10_Include (1UL) /*!< Include */

/* Bit 9 : Include or exclude subregion 9 in region */
#define MWU_PREGION_SUBS_SR9_Pos (9UL) /*!< Position of SR9 field. */
#define MWU_PREGION_SUBS_SR9_Msk (0x1UL << MWU_PREGION_SUBS_SR9_Pos) /*!< Bit mask of SR9 field. */
#define MWU_PREGION_SUBS_SR9_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR9_Include (1UL) /*!< Include */

/* Bit 8 : Include or exclude subregion 8 in region */
#define MWU_PREGION_SUBS_SR8_Pos (8UL) /*!< Position of SR8 field. */
#define MWU_PREGION_SUBS_SR8_Msk (0x1UL << MWU_PREGION_SUBS_SR8_Pos) /*!< Bit mask of SR8 field. */
#define MWU_PREGION_SUBS_SR8_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR8_Include (1UL) /*!< Include */

/* Bit 7 : Include or exclude subregion 7 in region */
#define MWU_PREGION_SUBS_SR7_Pos (7UL) /*!< Position of SR7 field. */
#define MWU_PREGION_SUBS_SR7_Msk (0x1UL << MWU_PREGION_SUBS_SR7_Pos) /*!< Bit mask of SR7 field. */
#define MWU_PREGION_SUBS_SR7_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR7_Include (1UL) /*!< Include */

/* Bit 6 : Include or exclude subregion 6 in region */
#define MWU_PREGION_SUBS_SR6_Pos (6UL) /*!< Position of SR6 field. */
#define MWU_PREGION_SUBS_SR6_Msk (0x1UL << MWU_PREGION_SUBS_SR6_Pos) /*!< Bit mask of SR6 field. */
#define MWU_PREGION_SUBS_SR6_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR6_Include (1UL) /*!< Include */

/* Bit 5 : Include or exclude subregion 5 in region */
#define MWU_PREGION_SUBS_SR5_Pos (5UL) /*!< Position of SR5 field. */
#define MWU_PREGION_SUBS_SR5_Msk (0x1UL << MWU_PREGION_SUBS_SR5_Pos) /*!< Bit mask of SR5 field. */
#define MWU_PREGION_SUBS_SR5_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR5_Include (1UL) /*!< Include */

/* Bit 4 : Include or exclude subregion 4 in region */
#define MWU_PREGION_SUBS_SR4_Pos (4UL) /*!< Position of SR4 field. */
#define MWU_PREGION_SUBS_SR4_Msk (0x1UL << MWU_PREGION_SUBS_SR4_Pos) /*!< Bit mask of SR4 field. */
#define MWU_PREGION_SUBS_SR4_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR4_Include (1UL) /*!< Include */

/* Bit 3 : Include or exclude subregion 3 in region */
#define MWU_PREGION_SUBS_SR3_Pos (3UL) /*!< Position of SR3 field. */
#define MWU_PREGION_SUBS_SR3_Msk (0x1UL << MWU_PREGION_SUBS_SR3_Pos) /*!< Bit mask of SR3 field. */
#define MWU_PREGION_SUBS_SR3_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR3_Include (1UL) /*!< Include */

/* Bit 2 : Include or exclude subregion 2 in region */
#define MWU_PREGION_SUBS_SR2_Pos (2UL) /*!< Position of SR2 field. */
#define MWU_PREGION_SUBS_SR2_Msk (0x1UL << MWU_PREGION_SUBS_SR2_Pos) /*!< Bit mask of SR2 field. */
#define MWU_PREGION_SUBS_SR2_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR2_Include (1UL) /*!< Include */

/* Bit 1 : Include or exclude subregion 1 in region */
#define MWU_PREGION_SUBS_SR1_Pos (1UL) /*!< Position of SR1 field. */
#define MWU_PREGION_SUBS_SR1_Msk (0x1UL << MWU_PREGION_SUBS_SR1_Pos) /*!< Bit mask of SR1 field. */
#define MWU_PREGION_SUBS_SR1_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR1_Include (1UL) /*!< Include */

/* Bit 0 : Include or exclude subregion 0 in region */
#define MWU_PREGION_SUBS_SR0_Pos (0UL) /*!< Position of SR0 field. */
#define MWU_PREGION_SUBS_SR0_Msk (0x1UL << MWU_PREGION_SUBS_SR0_Pos) /*!< Bit mask of SR0 field. */
#define MWU_PREGION_SUBS_SR0_Exclude (0UL) /*!< Exclude */
#define MWU_PREGION_SUBS_SR0_Include (1UL) /*!< Include */


/* Peripheral: NFCT */
/* Description: NFC-A compatible radio */

/* Register: NFCT_SHORTS */
/* Description: Shortcut register */

/* Bit 5 : Shortcut between TXFRAMEEND event and ENABLERXDATA task */
#define NFCT_SHORTS_TXFRAMEEND_ENABLERXDATA_Pos (5UL) /*!< Position of TXFRAMEEND_ENABLERXDATA field. */
#define NFCT_SHORTS_TXFRAMEEND_ENABLERXDATA_Msk (0x1UL << NFCT_SHORTS_TXFRAMEEND_ENABLERXDATA_Pos) /*!< Bit mask of TXFRAMEEND_ENABLERXDATA field. */
#define NFCT_SHORTS_TXFRAMEEND_ENABLERXDATA_Disabled (0UL) /*!< Disable shortcut */
#define NFCT_SHORTS_TXFRAMEEND_ENABLERXDATA_Enabled (1UL) /*!< Enable shortcut */

/* Bit 1 : Shortcut between FIELDLOST event and SENSE task */
#define NFCT_SHORTS_FIELDLOST_SENSE_Pos (1UL) /*!< Position of FIELDLOST_SENSE field. */
#define NFCT_SHORTS_FIELDLOST_SENSE_Msk (0x1UL << NFCT_SHORTS_FIELDLOST_SENSE_Pos) /*!< Bit mask of FIELDLOST_SENSE field. */
#define NFCT_SHORTS_FIELDLOST_SENSE_Disabled (0UL) /*!< Disable shortcut */
#define NFCT_SHORTS_FIELDLOST_SENSE_Enabled (1UL) /*!< Enable shortcut */

/* Bit 0 : Shortcut between FIELDDETECTED event and ACTIVATE task */
#define NFCT_SHORTS_FIELDDETECTED_ACTIVATE_Pos (0UL) /*!< Position of FIELDDETECTED_ACTIVATE field. */
#define NFCT_SHORTS_FIELDDETECTED_ACTIVATE_Msk (0x1UL << NFCT_SHORTS_FIELDDETECTED_ACTIVATE_Pos) /*!< Bit mask of FIELDDETECTED_ACTIVATE field. */
#define NFCT_SHORTS_FIELDDETECTED_ACTIVATE_Disabled (0UL) /*!< Disable shortcut */
#define NFCT_SHORTS_FIELDDETECTED_ACTIVATE_Enabled (1UL) /*!< Enable shortcut */

/* Register: NFCT_INTEN */
/* Description: Enable or disable interrupt */

/* Bit 20 : Enable or disable interrupt for STARTED event */
#define NFCT_INTEN_STARTED_Pos (20UL) /*!< Position of STARTED field. */
#define NFCT_INTEN_STARTED_Msk (0x1UL << NFCT_INTEN_STARTED_Pos) /*!< Bit mask of STARTED field. */
#define NFCT_INTEN_STARTED_Disabled (0UL) /*!< Disable */
#define NFCT_INTEN_STARTED_Enabled (1UL) /*!< Enable */

/* Bit 19 : Enable or disable interrupt for SELECTED event */
#define NFCT_INTEN_SELECTED_Pos (19UL) /*!< Position of SELECTED field. */
#define NFCT_INTEN_SELECTED_Msk (0x1UL << NFCT_INTEN_SELECTED_Pos) /*!< Bit mask of SELECTED field. */
#define NFCT_INTEN_SELECTED_Disabled (0UL) /*!< Disable */
#define NFCT_INTEN_SELECTED_Enabled (1UL) /*!< Enable */

/* Bit 18 : Enable or disable interrupt for COLLISION event */
#define NFCT_INTEN_COLLISION_Pos (18UL) /*!< Position of COLLISION field. */
#define NFCT_INTEN_COLLISION_Msk (0x1UL << NFCT_INTEN_COLLISION_Pos) /*!< Bit mask of COLLISION field. */
#define NFCT_INTEN_COLLISION_Disabled (0UL) /*!< Disable */
#define NFCT_INTEN_COLLISION_Enabled (1UL) /*!< Enable */

/* Bit 14 : Enable or disable interrupt for AUTOCOLRESSTARTED event */
#define NFCT_INTEN_AUTOCOLRESSTARTED_Pos (14UL) /*!< Position of AUTOCOLRESSTARTED field. */
#define NFCT_INTEN_AUTOCOLRESSTARTED_Msk (0x1UL << NFCT_INTEN_AUTOCOLRESSTARTED_Pos) /*!< Bit mask of AUTOCOLRESSTARTED field. */
#define NFCT_INTEN_AUTOCOLRESSTARTED_Disabled (0UL) /*!< Disable */
#define NFCT_INTEN_AUTOCOLRESSTARTED_Enabled (1UL) /*!< Enable */

/* Bit 12 : Enable or disable interrupt for ENDTX event */
#define NFCT_INTEN_ENDTX_Pos (12UL) /*!< Position of ENDTX field. */
#define NFCT_INTEN_ENDTX_Msk (0x1UL << NFCT_INTEN_ENDTX_Pos) /*!< Bit mask of ENDTX field. */
#define NFCT_INTEN_ENDTX_Disabled (0UL) /*!< Disable */
#define NFCT_INTEN_ENDTX_Enabled (1UL) /*!< Enable */

/* Bit 11 : Enable or disable interrupt for ENDRX event */
#define NFCT_INTEN_ENDRX_Pos (11UL) /*!< Position of ENDRX field. */
#define NFCT_INTEN_ENDRX_Msk (0x1UL << NFCT_INTEN_ENDRX_Pos) /*!< Bit mask of ENDRX field. */
#define NFCT_INTEN_ENDRX_Disabled (0UL) /*!< Disable */
#define NFCT_INTEN_ENDRX_Enabled (1UL) /*!< Enable */

/* Bit 10 : Enable or disable interrupt for RXERROR event */
#define NFCT_INTEN_RXERROR_Pos (10UL) /*!< Position of RXERROR field. */
#define NFCT_INTEN_RXERROR_Msk (0x1UL << NFCT_INTEN_RXERROR_Pos) /*!< Bit mask of RXERROR field. */
#define NFCT_INTEN_RXERROR_Disabled (0UL) /*!< Disable */
#define NFCT_INTEN_RXERROR_Enabled (1UL) /*!< Enable */

/* Bit 7 : Enable or disable interrupt for ERROR event */
#define NFCT_INTEN_ERROR_Pos (7UL) /*!< Position of ERROR field. */
#define NFCT_INTEN_ERROR_Msk (0x1UL << NFCT_INTEN_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define NFCT_INTEN_ERROR_Disabled (0UL) /*!< Disable */
#define NFCT_INTEN_ERROR_Enabled (1UL) /*!< Enable */

/* Bit 6 : Enable or disable interrupt for RXFRAMEEND event */
#define NFCT_INTEN_RXFRAMEEND_Pos (6UL) /*!< Position of RXFRAMEEND field. */
#define NFCT_INTEN_RXFRAMEEND_Msk (0x1UL << NFCT_INTEN_RXFRAMEEND_Pos) /*!< Bit mask of RXFRAMEEND field. */
#define NFCT_INTEN_RXFRAMEEND_Disabled (0UL) /*!< Disable */
#define NFCT_INTEN_RXFRAMEEND_Enabled (1UL) /*!< Enable */

/* Bit 5 : Enable or disable interrupt for RXFRAMESTART event */
#define NFCT_INTEN_RXFRAMESTART_Pos (5UL) /*!< Position of RXFRAMESTART field. */
#define NFCT_INTEN_RXFRAMESTART_Msk (0x1UL << NFCT_INTEN_RXFRAMESTART_Pos) /*!< Bit mask of RXFRAMESTART field. */
#define NFCT_INTEN_RXFRAMESTART_Disabled (0UL) /*!< Disable */
#define NFCT_INTEN_RXFRAMESTART_Enabled (1UL) /*!< Enable */

/* Bit 4 : Enable or disable interrupt for TXFRAMEEND event */
#define NFCT_INTEN_TXFRAMEEND_Pos (4UL) /*!< Position of TXFRAMEEND field. */
#define NFCT_INTEN_TXFRAMEEND_Msk (0x1UL << NFCT_INTEN_TXFRAMEEND_Pos) /*!< Bit mask of TXFRAMEEND field. */
#define NFCT_INTEN_TXFRAMEEND_Disabled (0UL) /*!< Disable */
#define NFCT_INTEN_TXFRAMEEND_Enabled (1UL) /*!< Enable */

/* Bit 3 : Enable or disable interrupt for TXFRAMESTART event */
#define NFCT_INTEN_TXFRAMESTART_Pos (3UL) /*!< Position of TXFRAMESTART field. */
#define NFCT_INTEN_TXFRAMESTART_Msk (0x1UL << NFCT_INTEN_TXFRAMESTART_Pos) /*!< Bit mask of TXFRAMESTART field. */
#define NFCT_INTEN_TXFRAMESTART_Disabled (0UL) /*!< Disable */
#define NFCT_INTEN_TXFRAMESTART_Enabled (1UL) /*!< Enable */

/* Bit 2 : Enable or disable interrupt for FIELDLOST event */
#define NFCT_INTEN_FIELDLOST_Pos (2UL) /*!< Position of FIELDLOST field. */
#define NFCT_INTEN_FIELDLOST_Msk (0x1UL << NFCT_INTEN_FIELDLOST_Pos) /*!< Bit mask of FIELDLOST field. */
#define NFCT_INTEN_FIELDLOST_Disabled (0UL) /*!< Disable */
#define NFCT_INTEN_FIELDLOST_Enabled (1UL) /*!< Enable */

/* Bit 1 : Enable or disable interrupt for FIELDDETECTED event */
#define NFCT_INTEN_FIELDDETECTED_Pos (1UL) /*!< Position of FIELDDETECTED field. */
#define NFCT_INTEN_FIELDDETECTED_Msk (0x1UL << NFCT_INTEN_FIELDDETECTED_Pos) /*!< Bit mask of FIELDDETECTED field. */
#define NFCT_INTEN_FIELDDETECTED_Disabled (0UL) /*!< Disable */
#define NFCT_INTEN_FIELDDETECTED_Enabled (1UL) /*!< Enable */

/* Bit 0 : Enable or disable interrupt for READY event */
#define NFCT_INTEN_READY_Pos (0UL) /*!< Position of READY field. */
#define NFCT_INTEN_READY_Msk (0x1UL << NFCT_INTEN_READY_Pos) /*!< Bit mask of READY field. */
#define NFCT_INTEN_READY_Disabled (0UL) /*!< Disable */
#define NFCT_INTEN_READY_Enabled (1UL) /*!< Enable */

/* Register: NFCT_INTENSET */
/* Description: Enable interrupt */

/* Bit 20 : Write '1' to Enable interrupt for STARTED event */
#define NFCT_INTENSET_STARTED_Pos (20UL) /*!< Position of STARTED field. */
#define NFCT_INTENSET_STARTED_Msk (0x1UL << NFCT_INTENSET_STARTED_Pos) /*!< Bit mask of STARTED field. */
#define NFCT_INTENSET_STARTED_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENSET_STARTED_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENSET_STARTED_Set (1UL) /*!< Enable */

/* Bit 19 : Write '1' to Enable interrupt for SELECTED event */
#define NFCT_INTENSET_SELECTED_Pos (19UL) /*!< Position of SELECTED field. */
#define NFCT_INTENSET_SELECTED_Msk (0x1UL << NFCT_INTENSET_SELECTED_Pos) /*!< Bit mask of SELECTED field. */
#define NFCT_INTENSET_SELECTED_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENSET_SELECTED_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENSET_SELECTED_Set (1UL) /*!< Enable */

/* Bit 18 : Write '1' to Enable interrupt for COLLISION event */
#define NFCT_INTENSET_COLLISION_Pos (18UL) /*!< Position of COLLISION field. */
#define NFCT_INTENSET_COLLISION_Msk (0x1UL << NFCT_INTENSET_COLLISION_Pos) /*!< Bit mask of COLLISION field. */
#define NFCT_INTENSET_COLLISION_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENSET_COLLISION_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENSET_COLLISION_Set (1UL) /*!< Enable */

/* Bit 14 : Write '1' to Enable interrupt for AUTOCOLRESSTARTED event */
#define NFCT_INTENSET_AUTOCOLRESSTARTED_Pos (14UL) /*!< Position of AUTOCOLRESSTARTED field. */
#define NFCT_INTENSET_AUTOCOLRESSTARTED_Msk (0x1UL << NFCT_INTENSET_AUTOCOLRESSTARTED_Pos) /*!< Bit mask of AUTOCOLRESSTARTED field. */
#define NFCT_INTENSET_AUTOCOLRESSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENSET_AUTOCOLRESSTARTED_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENSET_AUTOCOLRESSTARTED_Set (1UL) /*!< Enable */

/* Bit 12 : Write '1' to Enable interrupt for ENDTX event */
#define NFCT_INTENSET_ENDTX_Pos (12UL) /*!< Position of ENDTX field. */
#define NFCT_INTENSET_ENDTX_Msk (0x1UL << NFCT_INTENSET_ENDTX_Pos) /*!< Bit mask of ENDTX field. */
#define NFCT_INTENSET_ENDTX_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENSET_ENDTX_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENSET_ENDTX_Set (1UL) /*!< Enable */

/* Bit 11 : Write '1' to Enable interrupt for ENDRX event */
#define NFCT_INTENSET_ENDRX_Pos (11UL) /*!< Position of ENDRX field. */
#define NFCT_INTENSET_ENDRX_Msk (0x1UL << NFCT_INTENSET_ENDRX_Pos) /*!< Bit mask of ENDRX field. */
#define NFCT_INTENSET_ENDRX_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENSET_ENDRX_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENSET_ENDRX_Set (1UL) /*!< Enable */

/* Bit 10 : Write '1' to Enable interrupt for RXERROR event */
#define NFCT_INTENSET_RXERROR_Pos (10UL) /*!< Position of RXERROR field. */
#define NFCT_INTENSET_RXERROR_Msk (0x1UL << NFCT_INTENSET_RXERROR_Pos) /*!< Bit mask of RXERROR field. */
#define NFCT_INTENSET_RXERROR_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENSET_RXERROR_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENSET_RXERROR_Set (1UL) /*!< Enable */

/* Bit 7 : Write '1' to Enable interrupt for ERROR event */
#define NFCT_INTENSET_ERROR_Pos (7UL) /*!< Position of ERROR field. */
#define NFCT_INTENSET_ERROR_Msk (0x1UL << NFCT_INTENSET_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define NFCT_INTENSET_ERROR_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENSET_ERROR_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENSET_ERROR_Set (1UL) /*!< Enable */

/* Bit 6 : Write '1' to Enable interrupt for RXFRAMEEND event */
#define NFCT_INTENSET_RXFRAMEEND_Pos (6UL) /*!< Position of RXFRAMEEND field. */
#define NFCT_INTENSET_RXFRAMEEND_Msk (0x1UL << NFCT_INTENSET_RXFRAMEEND_Pos) /*!< Bit mask of RXFRAMEEND field. */
#define NFCT_INTENSET_RXFRAMEEND_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENSET_RXFRAMEEND_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENSET_RXFRAMEEND_Set (1UL) /*!< Enable */

/* Bit 5 : Write '1' to Enable interrupt for RXFRAMESTART event */
#define NFCT_INTENSET_RXFRAMESTART_Pos (5UL) /*!< Position of RXFRAMESTART field. */
#define NFCT_INTENSET_RXFRAMESTART_Msk (0x1UL << NFCT_INTENSET_RXFRAMESTART_Pos) /*!< Bit mask of RXFRAMESTART field. */
#define NFCT_INTENSET_RXFRAMESTART_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENSET_RXFRAMESTART_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENSET_RXFRAMESTART_Set (1UL) /*!< Enable */

/* Bit 4 : Write '1' to Enable interrupt for TXFRAMEEND event */
#define NFCT_INTENSET_TXFRAMEEND_Pos (4UL) /*!< Position of TXFRAMEEND field. */
#define NFCT_INTENSET_TXFRAMEEND_Msk (0x1UL << NFCT_INTENSET_TXFRAMEEND_Pos) /*!< Bit mask of TXFRAMEEND field. */
#define NFCT_INTENSET_TXFRAMEEND_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENSET_TXFRAMEEND_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENSET_TXFRAMEEND_Set (1UL) /*!< Enable */

/* Bit 3 : Write '1' to Enable interrupt for TXFRAMESTART event */
#define NFCT_INTENSET_TXFRAMESTART_Pos (3UL) /*!< Position of TXFRAMESTART field. */
#define NFCT_INTENSET_TXFRAMESTART_Msk (0x1UL << NFCT_INTENSET_TXFRAMESTART_Pos) /*!< Bit mask of TXFRAMESTART field. */
#define NFCT_INTENSET_TXFRAMESTART_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENSET_TXFRAMESTART_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENSET_TXFRAMESTART_Set (1UL) /*!< Enable */

/* Bit 2 : Write '1' to Enable interrupt for FIELDLOST event */
#define NFCT_INTENSET_FIELDLOST_Pos (2UL) /*!< Position of FIELDLOST field. */
#define NFCT_INTENSET_FIELDLOST_Msk (0x1UL << NFCT_INTENSET_FIELDLOST_Pos) /*!< Bit mask of FIELDLOST field. */
#define NFCT_INTENSET_FIELDLOST_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENSET_FIELDLOST_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENSET_FIELDLOST_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable interrupt for FIELDDETECTED event */
#define NFCT_INTENSET_FIELDDETECTED_Pos (1UL) /*!< Position of FIELDDETECTED field. */
#define NFCT_INTENSET_FIELDDETECTED_Msk (0x1UL << NFCT_INTENSET_FIELDDETECTED_Pos) /*!< Bit mask of FIELDDETECTED field. */
#define NFCT_INTENSET_FIELDDETECTED_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENSET_FIELDDETECTED_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENSET_FIELDDETECTED_Set (1UL) /*!< Enable */

/* Bit 0 : Write '1' to Enable interrupt for READY event */
#define NFCT_INTENSET_READY_Pos (0UL) /*!< Position of READY field. */
#define NFCT_INTENSET_READY_Msk (0x1UL << NFCT_INTENSET_READY_Pos) /*!< Bit mask of READY field. */
#define NFCT_INTENSET_READY_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENSET_READY_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENSET_READY_Set (1UL) /*!< Enable */

/* Register: NFCT_INTENCLR */
/* Description: Disable interrupt */

/* Bit 20 : Write '1' to Disable interrupt for STARTED event */
#define NFCT_INTENCLR_STARTED_Pos (20UL) /*!< Position of STARTED field. */
#define NFCT_INTENCLR_STARTED_Msk (0x1UL << NFCT_INTENCLR_STARTED_Pos) /*!< Bit mask of STARTED field. */
#define NFCT_INTENCLR_STARTED_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENCLR_STARTED_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENCLR_STARTED_Clear (1UL) /*!< Disable */

/* Bit 19 : Write '1' to Disable interrupt for SELECTED event */
#define NFCT_INTENCLR_SELECTED_Pos (19UL) /*!< Position of SELECTED field. */
#define NFCT_INTENCLR_SELECTED_Msk (0x1UL << NFCT_INTENCLR_SELECTED_Pos) /*!< Bit mask of SELECTED field. */
#define NFCT_INTENCLR_SELECTED_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENCLR_SELECTED_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENCLR_SELECTED_Clear (1UL) /*!< Disable */

/* Bit 18 : Write '1' to Disable interrupt for COLLISION event */
#define NFCT_INTENCLR_COLLISION_Pos (18UL) /*!< Position of COLLISION field. */
#define NFCT_INTENCLR_COLLISION_Msk (0x1UL << NFCT_INTENCLR_COLLISION_Pos) /*!< Bit mask of COLLISION field. */
#define NFCT_INTENCLR_COLLISION_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENCLR_COLLISION_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENCLR_COLLISION_Clear (1UL) /*!< Disable */

/* Bit 14 : Write '1' to Disable interrupt for AUTOCOLRESSTARTED event */
#define NFCT_INTENCLR_AUTOCOLRESSTARTED_Pos (14UL) /*!< Position of AUTOCOLRESSTARTED field. */
#define NFCT_INTENCLR_AUTOCOLRESSTARTED_Msk (0x1UL << NFCT_INTENCLR_AUTOCOLRESSTARTED_Pos) /*!< Bit mask of AUTOCOLRESSTARTED field. */
#define NFCT_INTENCLR_AUTOCOLRESSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENCLR_AUTOCOLRESSTARTED_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENCLR_AUTOCOLRESSTARTED_Clear (1UL) /*!< Disable */

/* Bit 12 : Write '1' to Disable interrupt for ENDTX event */
#define NFCT_INTENCLR_ENDTX_Pos (12UL) /*!< Position of ENDTX field. */
#define NFCT_INTENCLR_ENDTX_Msk (0x1UL << NFCT_INTENCLR_ENDTX_Pos) /*!< Bit mask of ENDTX field. */
#define NFCT_INTENCLR_ENDTX_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENCLR_ENDTX_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENCLR_ENDTX_Clear (1UL) /*!< Disable */

/* Bit 11 : Write '1' to Disable interrupt for ENDRX event */
#define NFCT_INTENCLR_ENDRX_Pos (11UL) /*!< Position of ENDRX field. */
#define NFCT_INTENCLR_ENDRX_Msk (0x1UL << NFCT_INTENCLR_ENDRX_Pos) /*!< Bit mask of ENDRX field. */
#define NFCT_INTENCLR_ENDRX_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENCLR_ENDRX_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENCLR_ENDRX_Clear (1UL) /*!< Disable */

/* Bit 10 : Write '1' to Disable interrupt for RXERROR event */
#define NFCT_INTENCLR_RXERROR_Pos (10UL) /*!< Position of RXERROR field. */
#define NFCT_INTENCLR_RXERROR_Msk (0x1UL << NFCT_INTENCLR_RXERROR_Pos) /*!< Bit mask of RXERROR field. */
#define NFCT_INTENCLR_RXERROR_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENCLR_RXERROR_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENCLR_RXERROR_Clear (1UL) /*!< Disable */

/* Bit 7 : Write '1' to Disable interrupt for ERROR event */
#define NFCT_INTENCLR_ERROR_Pos (7UL) /*!< Position of ERROR field. */
#define NFCT_INTENCLR_ERROR_Msk (0x1UL << NFCT_INTENCLR_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define NFCT_INTENCLR_ERROR_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENCLR_ERROR_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENCLR_ERROR_Clear (1UL) /*!< Disable */

/* Bit 6 : Write '1' to Disable interrupt for RXFRAMEEND event */
#define NFCT_INTENCLR_RXFRAMEEND_Pos (6UL) /*!< Position of RXFRAMEEND field. */
#define NFCT_INTENCLR_RXFRAMEEND_Msk (0x1UL << NFCT_INTENCLR_RXFRAMEEND_Pos) /*!< Bit mask of RXFRAMEEND field. */
#define NFCT_INTENCLR_RXFRAMEEND_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENCLR_RXFRAMEEND_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENCLR_RXFRAMEEND_Clear (1UL) /*!< Disable */

/* Bit 5 : Write '1' to Disable interrupt for RXFRAMESTART event */
#define NFCT_INTENCLR_RXFRAMESTART_Pos (5UL) /*!< Position of RXFRAMESTART field. */
#define NFCT_INTENCLR_RXFRAMESTART_Msk (0x1UL << NFCT_INTENCLR_RXFRAMESTART_Pos) /*!< Bit mask of RXFRAMESTART field. */
#define NFCT_INTENCLR_RXFRAMESTART_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENCLR_RXFRAMESTART_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENCLR_RXFRAMESTART_Clear (1UL) /*!< Disable */

/* Bit 4 : Write '1' to Disable interrupt for TXFRAMEEND event */
#define NFCT_INTENCLR_TXFRAMEEND_Pos (4UL) /*!< Position of TXFRAMEEND field. */
#define NFCT_INTENCLR_TXFRAMEEND_Msk (0x1UL << NFCT_INTENCLR_TXFRAMEEND_Pos) /*!< Bit mask of TXFRAMEEND field. */
#define NFCT_INTENCLR_TXFRAMEEND_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENCLR_TXFRAMEEND_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENCLR_TXFRAMEEND_Clear (1UL) /*!< Disable */

/* Bit 3 : Write '1' to Disable interrupt for TXFRAMESTART event */
#define NFCT_INTENCLR_TXFRAMESTART_Pos (3UL) /*!< Position of TXFRAMESTART field. */
#define NFCT_INTENCLR_TXFRAMESTART_Msk (0x1UL << NFCT_INTENCLR_TXFRAMESTART_Pos) /*!< Bit mask of TXFRAMESTART field. */
#define NFCT_INTENCLR_TXFRAMESTART_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENCLR_TXFRAMESTART_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENCLR_TXFRAMESTART_Clear (1UL) /*!< Disable */

/* Bit 2 : Write '1' to Disable interrupt for FIELDLOST event */
#define NFCT_INTENCLR_FIELDLOST_Pos (2UL) /*!< Position of FIELDLOST field. */
#define NFCT_INTENCLR_FIELDLOST_Msk (0x1UL << NFCT_INTENCLR_FIELDLOST_Pos) /*!< Bit mask of FIELDLOST field. */
#define NFCT_INTENCLR_FIELDLOST_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENCLR_FIELDLOST_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENCLR_FIELDLOST_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable interrupt for FIELDDETECTED event */
#define NFCT_INTENCLR_FIELDDETECTED_Pos (1UL) /*!< Position of FIELDDETECTED field. */
#define NFCT_INTENCLR_FIELDDETECTED_Msk (0x1UL << NFCT_INTENCLR_FIELDDETECTED_Pos) /*!< Bit mask of FIELDDETECTED field. */
#define NFCT_INTENCLR_FIELDDETECTED_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENCLR_FIELDDETECTED_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENCLR_FIELDDETECTED_Clear (1UL) /*!< Disable */

/* Bit 0 : Write '1' to Disable interrupt for READY event */
#define NFCT_INTENCLR_READY_Pos (0UL) /*!< Position of READY field. */
#define NFCT_INTENCLR_READY_Msk (0x1UL << NFCT_INTENCLR_READY_Pos) /*!< Bit mask of READY field. */
#define NFCT_INTENCLR_READY_Disabled (0UL) /*!< Read: Disabled */
#define NFCT_INTENCLR_READY_Enabled (1UL) /*!< Read: Enabled */
#define NFCT_INTENCLR_READY_Clear (1UL) /*!< Disable */

/* Register: NFCT_ERRORSTATUS */
/* Description: NFC Error Status register */

/* Bit 0 : No STARTTX task triggered before expiration of the time set in FRAMEDELAYMAX */
#define NFCT_ERRORSTATUS_FRAMEDELAYTIMEOUT_Pos (0UL) /*!< Position of FRAMEDELAYTIMEOUT field. */
#define NFCT_ERRORSTATUS_FRAMEDELAYTIMEOUT_Msk (0x1UL << NFCT_ERRORSTATUS_FRAMEDELAYTIMEOUT_Pos) /*!< Bit mask of FRAMEDELAYTIMEOUT field. */

/* Register: NFCT_FRAMESTATUS_RX */
/* Description: Result of last incoming frame */

/* Bit 3 : Overrun detected */
#define NFCT_FRAMESTATUS_RX_OVERRUN_Pos (3UL) /*!< Position of OVERRUN field. */
#define NFCT_FRAMESTATUS_RX_OVERRUN_Msk (0x1UL << NFCT_FRAMESTATUS_RX_OVERRUN_Pos) /*!< Bit mask of OVERRUN field. */
#define NFCT_FRAMESTATUS_RX_OVERRUN_NoOverrun (0UL) /*!< No overrun detected */
#define NFCT_FRAMESTATUS_RX_OVERRUN_Overrun (1UL) /*!< Overrun error */

/* Bit 2 : Parity status of received frame */
#define NFCT_FRAMESTATUS_RX_PARITYSTATUS_Pos (2UL) /*!< Position of PARITYSTATUS field. */
#define NFCT_FRAMESTATUS_RX_PARITYSTATUS_Msk (0x1UL << NFCT_FRAMESTATUS_RX_PARITYSTATUS_Pos) /*!< Bit mask of PARITYSTATUS field. */
#define NFCT_FRAMESTATUS_RX_PARITYSTATUS_ParityOK (0UL) /*!< Frame received with parity OK */
#define NFCT_FRAMESTATUS_RX_PARITYSTATUS_ParityError (1UL) /*!< Frame received with parity error */

/* Bit 0 : No valid end of frame (EoF) detected */
#define NFCT_FRAMESTATUS_RX_CRCERROR_Pos (0UL) /*!< Position of CRCERROR field. */
#define NFCT_FRAMESTATUS_RX_CRCERROR_Msk (0x1UL << NFCT_FRAMESTATUS_RX_CRCERROR_Pos) /*!< Bit mask of CRCERROR field. */
#define NFCT_FRAMESTATUS_RX_CRCERROR_CRCCorrect (0UL) /*!< Valid CRC detected */
#define NFCT_FRAMESTATUS_RX_CRCERROR_CRCError (1UL) /*!< CRC received does not match local check */

/* Register: NFCT_NFCTAGSTATE */
/* Description: NfcTag state register */

/* Bits 2..0 : NfcTag state */
#define NFCT_NFCTAGSTATE_NFCTAGSTATE_Pos (0UL) /*!< Position of NFCTAGSTATE field. */
#define NFCT_NFCTAGSTATE_NFCTAGSTATE_Msk (0x7UL << NFCT_NFCTAGSTATE_NFCTAGSTATE_Pos) /*!< Bit mask of NFCTAGSTATE field. */
#define NFCT_NFCTAGSTATE_NFCTAGSTATE_Disabled (0UL) /*!< Disabled or sense */
#define NFCT_NFCTAGSTATE_NFCTAGSTATE_RampUp (2UL) /*!< RampUp */
#define NFCT_NFCTAGSTATE_NFCTAGSTATE_Idle (3UL) /*!< Idle */
#define NFCT_NFCTAGSTATE_NFCTAGSTATE_Receive (4UL) /*!< Receive */
#define NFCT_NFCTAGSTATE_NFCTAGSTATE_FrameDelay (5UL) /*!< FrameDelay */
#define NFCT_NFCTAGSTATE_NFCTAGSTATE_Transmit (6UL) /*!< Transmit */

/* Register: NFCT_FIELDPRESENT */
/* Description: Indicates the presence or not of a valid field */

/* Bit 1 : Indicates if the low level has locked to the field */
#define NFCT_FIELDPRESENT_LOCKDETECT_Pos (1UL) /*!< Position of LOCKDETECT field. */
#define NFCT_FIELDPRESENT_LOCKDETECT_Msk (0x1UL << NFCT_FIELDPRESENT_LOCKDETECT_Pos) /*!< Bit mask of LOCKDETECT field. */
#define NFCT_FIELDPRESENT_LOCKDETECT_NotLocked (0UL) /*!< Not locked to field */
#define NFCT_FIELDPRESENT_LOCKDETECT_Locked (1UL) /*!< Locked to field */

/* Bit 0 : Indicates if a valid field is present. Available only in the activated state. */
#define NFCT_FIELDPRESENT_FIELDPRESENT_Pos (0UL) /*!< Position of FIELDPRESENT field. */
#define NFCT_FIELDPRESENT_FIELDPRESENT_Msk (0x1UL << NFCT_FIELDPRESENT_FIELDPRESENT_Pos) /*!< Bit mask of FIELDPRESENT field. */
#define NFCT_FIELDPRESENT_FIELDPRESENT_NoField (0UL) /*!< No valid field detected */
#define NFCT_FIELDPRESENT_FIELDPRESENT_FieldPresent (1UL) /*!< Valid field detected */

/* Register: NFCT_FRAMEDELAYMIN */
/* Description: Minimum frame delay */

/* Bits 15..0 : Minimum frame delay in number of 13.56 MHz clocks */
#define NFCT_FRAMEDELAYMIN_FRAMEDELAYMIN_Pos (0UL) /*!< Position of FRAMEDELAYMIN field. */
#define NFCT_FRAMEDELAYMIN_FRAMEDELAYMIN_Msk (0xFFFFUL << NFCT_FRAMEDELAYMIN_FRAMEDELAYMIN_Pos) /*!< Bit mask of FRAMEDELAYMIN field. */

/* Register: NFCT_FRAMEDELAYMAX */
/* Description: Maximum frame delay */

/* Bits 15..0 : Maximum frame delay in number of 13.56 MHz clocks */
#define NFCT_FRAMEDELAYMAX_FRAMEDELAYMAX_Pos (0UL) /*!< Position of FRAMEDELAYMAX field. */
#define NFCT_FRAMEDELAYMAX_FRAMEDELAYMAX_Msk (0xFFFFUL << NFCT_FRAMEDELAYMAX_FRAMEDELAYMAX_Pos) /*!< Bit mask of FRAMEDELAYMAX field. */

/* Register: NFCT_FRAMEDELAYMODE */
/* Description: Configuration register for the Frame Delay Timer */

/* Bits 1..0 : Configuration register for the Frame Delay Timer */
#define NFCT_FRAMEDELAYMODE_FRAMEDELAYMODE_Pos (0UL) /*!< Position of FRAMEDELAYMODE field. */
#define NFCT_FRAMEDELAYMODE_FRAMEDELAYMODE_Msk (0x3UL << NFCT_FRAMEDELAYMODE_FRAMEDELAYMODE_Pos) /*!< Bit mask of FRAMEDELAYMODE field. */
#define NFCT_FRAMEDELAYMODE_FRAMEDELAYMODE_FreeRun (0UL) /*!< Transmission is independent of frame timer and will start when the STARTTX task is triggered. No timeout. */
#define NFCT_FRAMEDELAYMODE_FRAMEDELAYMODE_Window (1UL) /*!< Frame is transmitted between FRAMEDELAYMIN and FRAMEDELAYMAX */
#define NFCT_FRAMEDELAYMODE_FRAMEDELAYMODE_ExactVal (2UL) /*!< Frame is transmitted exactly at FRAMEDELAYMAX */
#define NFCT_FRAMEDELAYMODE_FRAMEDELAYMODE_WindowGrid (3UL) /*!< Frame is transmitted on a bit grid between FRAMEDELAYMIN and FRAMEDELAYMAX */

/* Register: NFCT_PACKETPTR */
/* Description: Packet pointer for TXD and RXD data storage in Data RAM */

/* Bits 31..0 : Packet pointer for TXD and RXD data storage in Data RAM. This address is a byte-aligned RAM address. */
#define NFCT_PACKETPTR_PTR_Pos (0UL) /*!< Position of PTR field. */
#define NFCT_PACKETPTR_PTR_Msk (0xFFFFFFFFUL << NFCT_PACKETPTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: NFCT_MAXLEN */
/* Description: Size of the RAM buffer allocated to TXD and RXD data storage each */

/* Bits 8..0 : Size of the RAM buffer allocated to TXD and RXD data storage each */
#define NFCT_MAXLEN_MAXLEN_Pos (0UL) /*!< Position of MAXLEN field. */
#define NFCT_MAXLEN_MAXLEN_Msk (0x1FFUL << NFCT_MAXLEN_MAXLEN_Pos) /*!< Bit mask of MAXLEN field. */

/* Register: NFCT_TXD_FRAMECONFIG */
/* Description: Configuration of outgoing frames */

/* Bit 4 : CRC mode for outgoing frames */
#define NFCT_TXD_FRAMECONFIG_CRCMODETX_Pos (4UL) /*!< Position of CRCMODETX field. */
#define NFCT_TXD_FRAMECONFIG_CRCMODETX_Msk (0x1UL << NFCT_TXD_FRAMECONFIG_CRCMODETX_Pos) /*!< Bit mask of CRCMODETX field. */
#define NFCT_TXD_FRAMECONFIG_CRCMODETX_NoCRCTX (0UL) /*!< CRC is not added to the frame */
#define NFCT_TXD_FRAMECONFIG_CRCMODETX_CRC16TX (1UL) /*!< 16 bit CRC added to the frame based on all the data read from RAM that is used in the frame */

/* Bit 2 : Adding SoF or not in TX frames */
#define NFCT_TXD_FRAMECONFIG_SOF_Pos (2UL) /*!< Position of SOF field. */
#define NFCT_TXD_FRAMECONFIG_SOF_Msk (0x1UL << NFCT_TXD_FRAMECONFIG_SOF_Pos) /*!< Bit mask of SOF field. */
#define NFCT_TXD_FRAMECONFIG_SOF_NoSoF (0UL) /*!< SoF symbol not added */
#define NFCT_TXD_FRAMECONFIG_SOF_SoF (1UL) /*!< SoF symbol added */

/* Bit 1 : Discarding unused bits at start or end of a frame */
#define NFCT_TXD_FRAMECONFIG_DISCARDMODE_Pos (1UL) /*!< Position of DISCARDMODE field. */
#define NFCT_TXD_FRAMECONFIG_DISCARDMODE_Msk (0x1UL << NFCT_TXD_FRAMECONFIG_DISCARDMODE_Pos) /*!< Bit mask of DISCARDMODE field. */
#define NFCT_TXD_FRAMECONFIG_DISCARDMODE_DiscardEnd (0UL) /*!< Unused bits are discarded at end of frame (EoF) */
#define NFCT_TXD_FRAMECONFIG_DISCARDMODE_DiscardStart (1UL) /*!< Unused bits are discarded at start of frame (SoF) */

/* Bit 0 : Indicates if parity is added to the frame */
#define NFCT_TXD_FRAMECONFIG_PARITY_Pos (0UL) /*!< Position of PARITY field. */
#define NFCT_TXD_FRAMECONFIG_PARITY_Msk (0x1UL << NFCT_TXD_FRAMECONFIG_PARITY_Pos) /*!< Bit mask of PARITY field. */
#define NFCT_TXD_FRAMECONFIG_PARITY_NoParity (0UL) /*!< Parity is not added to TX frames */
#define NFCT_TXD_FRAMECONFIG_PARITY_Parity (1UL) /*!< Parity is added to TX frames */

/* Register: NFCT_TXD_AMOUNT */
/* Description: Size of outgoing frame */

/* Bits 11..3 : Number of complete bytes that shall be included in the frame, excluding CRC, parity and framing */
#define NFCT_TXD_AMOUNT_TXDATABYTES_Pos (3UL) /*!< Position of TXDATABYTES field. */
#define NFCT_TXD_AMOUNT_TXDATABYTES_Msk (0x1FFUL << NFCT_TXD_AMOUNT_TXDATABYTES_Pos) /*!< Bit mask of TXDATABYTES field. */

/* Bits 2..0 : Number of bits in the last or first byte read from RAM that shall be included in the frame (excluding parity bit). */
#define NFCT_TXD_AMOUNT_TXDATABITS_Pos (0UL) /*!< Position of TXDATABITS field. */
#define NFCT_TXD_AMOUNT_TXDATABITS_Msk (0x7UL << NFCT_TXD_AMOUNT_TXDATABITS_Pos) /*!< Bit mask of TXDATABITS field. */

/* Register: NFCT_RXD_FRAMECONFIG */
/* Description: Configuration of incoming frames */

/* Bit 4 : CRC mode for incoming frames */
#define NFCT_RXD_FRAMECONFIG_CRCMODERX_Pos (4UL) /*!< Position of CRCMODERX field. */
#define NFCT_RXD_FRAMECONFIG_CRCMODERX_Msk (0x1UL << NFCT_RXD_FRAMECONFIG_CRCMODERX_Pos) /*!< Bit mask of CRCMODERX field. */
#define NFCT_RXD_FRAMECONFIG_CRCMODERX_NoCRCRX (0UL) /*!< CRC is not expected in RX frames */
#define NFCT_RXD_FRAMECONFIG_CRCMODERX_CRC16RX (1UL) /*!< Last 16 bits in RX frame is CRC, CRC is checked and CRCSTATUS updated */

/* Bit 2 : SoF expected or not in RX frames */
#define NFCT_RXD_FRAMECONFIG_SOF_Pos (2UL) /*!< Position of SOF field. */
#define NFCT_RXD_FRAMECONFIG_SOF_Msk (0x1UL << NFCT_RXD_FRAMECONFIG_SOF_Pos) /*!< Bit mask of SOF field. */
#define NFCT_RXD_FRAMECONFIG_SOF_NoSoF (0UL) /*!< SoF symbol is not expected in RX frames */
#define NFCT_RXD_FRAMECONFIG_SOF_SoF (1UL) /*!< SoF symbol is expected in RX frames */

/* Bit 0 : Indicates if parity expected in RX frame */
#define NFCT_RXD_FRAMECONFIG_PARITY_Pos (0UL) /*!< Position of PARITY field. */
#define NFCT_RXD_FRAMECONFIG_PARITY_Msk (0x1UL << NFCT_RXD_FRAMECONFIG_PARITY_Pos) /*!< Bit mask of PARITY field. */
#define NFCT_RXD_FRAMECONFIG_PARITY_NoParity (0UL) /*!< Parity is not expected in RX frames */
#define NFCT_RXD_FRAMECONFIG_PARITY_Parity (1UL) /*!< Parity is expected in RX frames */

/* Register: NFCT_RXD_AMOUNT */
/* Description: Size of last incoming frame */

/* Bits 11..3 : Number of complete bytes received in the frame (including CRC, but excluding parity and SoF/EoF framing) */
#define NFCT_RXD_AMOUNT_RXDATABYTES_Pos (3UL) /*!< Position of RXDATABYTES field. */
#define NFCT_RXD_AMOUNT_RXDATABYTES_Msk (0x1FFUL << NFCT_RXD_AMOUNT_RXDATABYTES_Pos) /*!< Bit mask of RXDATABYTES field. */

/* Bits 2..0 : Number of bits in the last byte in the frame, if less than 8 (including CRC, but excluding parity and SoF/EoF framing). */
#define NFCT_RXD_AMOUNT_RXDATABITS_Pos (0UL) /*!< Position of RXDATABITS field. */
#define NFCT_RXD_AMOUNT_RXDATABITS_Msk (0x7UL << NFCT_RXD_AMOUNT_RXDATABITS_Pos) /*!< Bit mask of RXDATABITS field. */

/* Register: NFCT_NFCID1_LAST */
/* Description: Last NFCID1 part (4, 7 or 10 bytes ID) */

/* Bits 31..24 : NFCID1 byte W */
#define NFCT_NFCID1_LAST_NFCID1_W_Pos (24UL) /*!< Position of NFCID1_W field. */
#define NFCT_NFCID1_LAST_NFCID1_W_Msk (0xFFUL << NFCT_NFCID1_LAST_NFCID1_W_Pos) /*!< Bit mask of NFCID1_W field. */

/* Bits 23..16 : NFCID1 byte X */
#define NFCT_NFCID1_LAST_NFCID1_X_Pos (16UL) /*!< Position of NFCID1_X field. */
#define NFCT_NFCID1_LAST_NFCID1_X_Msk (0xFFUL << NFCT_NFCID1_LAST_NFCID1_X_Pos) /*!< Bit mask of NFCID1_X field. */

/* Bits 15..8 : NFCID1 byte Y */
#define NFCT_NFCID1_LAST_NFCID1_Y_Pos (8UL) /*!< Position of NFCID1_Y field. */
#define NFCT_NFCID1_LAST_NFCID1_Y_Msk (0xFFUL << NFCT_NFCID1_LAST_NFCID1_Y_Pos) /*!< Bit mask of NFCID1_Y field. */

/* Bits 7..0 : NFCID1 byte Z (very last byte sent) */
#define NFCT_NFCID1_LAST_NFCID1_Z_Pos (0UL) /*!< Position of NFCID1_Z field. */
#define NFCT_NFCID1_LAST_NFCID1_Z_Msk (0xFFUL << NFCT_NFCID1_LAST_NFCID1_Z_Pos) /*!< Bit mask of NFCID1_Z field. */

/* Register: NFCT_NFCID1_2ND_LAST */
/* Description: Second last NFCID1 part (7 or 10 bytes ID) */

/* Bits 23..16 : NFCID1 byte T */
#define NFCT_NFCID1_2ND_LAST_NFCID1_T_Pos (16UL) /*!< Position of NFCID1_T field. */
#define NFCT_NFCID1_2ND_LAST_NFCID1_T_Msk (0xFFUL << NFCT_NFCID1_2ND_LAST_NFCID1_T_Pos) /*!< Bit mask of NFCID1_T field. */

/* Bits 15..8 : NFCID1 byte U */
#define NFCT_NFCID1_2ND_LAST_NFCID1_U_Pos (8UL) /*!< Position of NFCID1_U field. */
#define NFCT_NFCID1_2ND_LAST_NFCID1_U_Msk (0xFFUL << NFCT_NFCID1_2ND_LAST_NFCID1_U_Pos) /*!< Bit mask of NFCID1_U field. */

/* Bits 7..0 : NFCID1 byte V */
#define NFCT_NFCID1_2ND_LAST_NFCID1_V_Pos (0UL) /*!< Position of NFCID1_V field. */
#define NFCT_NFCID1_2ND_LAST_NFCID1_V_Msk (0xFFUL << NFCT_NFCID1_2ND_LAST_NFCID1_V_Pos) /*!< Bit mask of NFCID1_V field. */

/* Register: NFCT_NFCID1_3RD_LAST */
/* Description: Third last NFCID1 part (10 bytes ID) */

/* Bits 23..16 : NFCID1 byte Q */
#define NFCT_NFCID1_3RD_LAST_NFCID1_Q_Pos (16UL) /*!< Position of NFCID1_Q field. */
#define NFCT_NFCID1_3RD_LAST_NFCID1_Q_Msk (0xFFUL << NFCT_NFCID1_3RD_LAST_NFCID1_Q_Pos) /*!< Bit mask of NFCID1_Q field. */

/* Bits 15..8 : NFCID1 byte R */
#define NFCT_NFCID1_3RD_LAST_NFCID1_R_Pos (8UL) /*!< Position of NFCID1_R field. */
#define NFCT_NFCID1_3RD_LAST_NFCID1_R_Msk (0xFFUL << NFCT_NFCID1_3RD_LAST_NFCID1_R_Pos) /*!< Bit mask of NFCID1_R field. */

/* Bits 7..0 : NFCID1 byte S */
#define NFCT_NFCID1_3RD_LAST_NFCID1_S_Pos (0UL) /*!< Position of NFCID1_S field. */
#define NFCT_NFCID1_3RD_LAST_NFCID1_S_Msk (0xFFUL << NFCT_NFCID1_3RD_LAST_NFCID1_S_Pos) /*!< Bit mask of NFCID1_S field. */

/* Register: NFCT_AUTOCOLRESCONFIG */
/* Description: Controls the auto collision resolution function. This setting must be done before the NFCT peripheral is enabled. */

/* Bit 0 : Enables/disables auto collision resolution */
#define NFCT_AUTOCOLRESCONFIG_MODE_Pos (0UL) /*!< Position of MODE field. */
#define NFCT_AUTOCOLRESCONFIG_MODE_Msk (0x1UL << NFCT_AUTOCOLRESCONFIG_MODE_Pos) /*!< Bit mask of MODE field. */
#define NFCT_AUTOCOLRESCONFIG_MODE_Enabled (0UL) /*!< Auto collision resolution enabled */
#define NFCT_AUTOCOLRESCONFIG_MODE_Disabled (1UL) /*!< Auto collision resolution disabled */

/* Register: NFCT_SENSRES */
/* Description: NFC-A SENS_RES auto-response settings */

/* Bits 15..12 : Reserved for future use. Shall be 0. */
#define NFCT_SENSRES_RFU74_Pos (12UL) /*!< Position of RFU74 field. */
#define NFCT_SENSRES_RFU74_Msk (0xFUL << NFCT_SENSRES_RFU74_Pos) /*!< Bit mask of RFU74 field. */

/* Bits 11..8 : Tag platform configuration as defined by the b4:b1 of byte 2 in SENS_RES response in the NFC Forum, NFC Digital Protocol Technical Specification */
#define NFCT_SENSRES_PLATFCONFIG_Pos (8UL) /*!< Position of PLATFCONFIG field. */
#define NFCT_SENSRES_PLATFCONFIG_Msk (0xFUL << NFCT_SENSRES_PLATFCONFIG_Pos) /*!< Bit mask of PLATFCONFIG field. */

/* Bits 7..6 : NFCID1 size. This value is used by the auto collision resolution engine. */
#define NFCT_SENSRES_NFCIDSIZE_Pos (6UL) /*!< Position of NFCIDSIZE field. */
#define NFCT_SENSRES_NFCIDSIZE_Msk (0x3UL << NFCT_SENSRES_NFCIDSIZE_Pos) /*!< Bit mask of NFCIDSIZE field. */
#define NFCT_SENSRES_NFCIDSIZE_NFCID1Single (0UL) /*!< NFCID1 size: single (4 bytes) */
#define NFCT_SENSRES_NFCIDSIZE_NFCID1Double (1UL) /*!< NFCID1 size: double (7 bytes) */
#define NFCT_SENSRES_NFCIDSIZE_NFCID1Triple (2UL) /*!< NFCID1 size: triple (10 bytes) */

/* Bit 5 : Reserved for future use. Shall be 0. */
#define NFCT_SENSRES_RFU5_Pos (5UL) /*!< Position of RFU5 field. */
#define NFCT_SENSRES_RFU5_Msk (0x1UL << NFCT_SENSRES_RFU5_Pos) /*!< Bit mask of RFU5 field. */

/* Bits 4..0 : Bit frame SDD as defined by the b5:b1 of byte 1 in SENS_RES response in the <i>NFC Forum, NFC Digital Protocol Technical Specification</i> */
#define NFCT_SENSRES_BITFRAMESDD_Pos (0UL) /*!< Position of BITFRAMESDD field. */
#define NFCT_SENSRES_BITFRAMESDD_Msk (0x1FUL << NFCT_SENSRES_BITFRAMESDD_Pos) /*!< Bit mask of BITFRAMESDD field. */
#define NFCT_SENSRES_BITFRAMESDD_SDD00000 (0UL) /*!< SDD pattern 00000 */
#define NFCT_SENSRES_BITFRAMESDD_SDD00001 (1UL) /*!< SDD pattern 00001 */
#define NFCT_SENSRES_BITFRAMESDD_SDD00010 (2UL) /*!< SDD pattern 00010 */
#define NFCT_SENSRES_BITFRAMESDD_SDD00100 (4UL) /*!< SDD pattern 00100 */
#define NFCT_SENSRES_BITFRAMESDD_SDD01000 (8UL) /*!< SDD pattern 01000 */
#define NFCT_SENSRES_BITFRAMESDD_SDD10000 (16UL) /*!< SDD pattern 10000 */

/* Register: NFCT_SELRES */
/* Description: NFC-A SEL_RES auto-response settings */

/* Bit 7 : Reserved for future use. Shall be 0. */
#define NFCT_SELRES_RFU7_Pos (7UL) /*!< Position of RFU7 field. */
#define NFCT_SELRES_RFU7_Msk (0x1UL << NFCT_SELRES_RFU7_Pos) /*!< Bit mask of RFU7 field. */

/* Bits 6..5 : Protocol as defined by the b7:b6 of SEL_RES response in the NFC Forum, NFC Digital Protocol Technical Specification */
#define NFCT_SELRES_PROTOCOL_Pos (5UL) /*!< Position of PROTOCOL field. */
#define NFCT_SELRES_PROTOCOL_Msk (0x3UL << NFCT_SELRES_PROTOCOL_Pos) /*!< Bit mask of PROTOCOL field. */

/* Bits 4..3 : Reserved for future use. Shall be 0. */
#define NFCT_SELRES_RFU43_Pos (3UL) /*!< Position of RFU43 field. */
#define NFCT_SELRES_RFU43_Msk (0x3UL << NFCT_SELRES_RFU43_Pos) /*!< Bit mask of RFU43 field. */

/* Bit 2 : Cascade as defined by the b3 of SEL_RES response in the NFC Forum, NFC Digital Protocol Technical Specification (controlled by hardware, shall be 0) */
#define NFCT_SELRES_CASCADE_Pos (2UL) /*!< Position of CASCADE field. */
#define NFCT_SELRES_CASCADE_Msk (0x1UL << NFCT_SELRES_CASCADE_Pos) /*!< Bit mask of CASCADE field. */

/* Bits 1..0 : Reserved for future use. Shall be 0. */
#define NFCT_SELRES_RFU10_Pos (0UL) /*!< Position of RFU10 field. */
#define NFCT_SELRES_RFU10_Msk (0x3UL << NFCT_SELRES_RFU10_Pos) /*!< Bit mask of RFU10 field. */


/* Peripheral: NVMC */
/* Description: Non Volatile Memory Controller */

/* Register: NVMC_READY */
/* Description: Ready flag */

/* Bit 0 : NVMC is ready or busy */
#define NVMC_READY_READY_Pos (0UL) /*!< Position of READY field. */
#define NVMC_READY_READY_Msk (0x1UL << NVMC_READY_READY_Pos) /*!< Bit mask of READY field. */
#define NVMC_READY_READY_Busy (0UL) /*!< NVMC is busy (on-going write or erase operation) */
#define NVMC_READY_READY_Ready (1UL) /*!< NVMC is ready */

/* Register: NVMC_CONFIG */
/* Description: Configuration register */

/* Bits 1..0 : Program memory access mode. It is strongly recommended to only activate erase and write modes when they are actively used. Enabling write or erase will invalidate the cache and keep it invalidated. */
#define NVMC_CONFIG_WEN_Pos (0UL) /*!< Position of WEN field. */
#define NVMC_CONFIG_WEN_Msk (0x3UL << NVMC_CONFIG_WEN_Pos) /*!< Bit mask of WEN field. */
#define NVMC_CONFIG_WEN_Ren (0UL) /*!< Read only access */
#define NVMC_CONFIG_WEN_Wen (1UL) /*!< Write Enabled */
#define NVMC_CONFIG_WEN_Een (2UL) /*!< Erase enabled */

/* Register: NVMC_ERASEPAGE */
/* Description: Register for erasing a page in Code area */

/* Bits 31..0 : Register for starting erase of a page in Code area */
#define NVMC_ERASEPAGE_ERASEPAGE_Pos (0UL) /*!< Position of ERASEPAGE field. */
#define NVMC_ERASEPAGE_ERASEPAGE_Msk (0xFFFFFFFFUL << NVMC_ERASEPAGE_ERASEPAGE_Pos) /*!< Bit mask of ERASEPAGE field. */

/* Register: NVMC_ERASEPCR1 */
/* Description: Deprecated register -  Register for erasing a page in Code area. Equivalent to ERASEPAGE. */

/* Bits 31..0 : Register for erasing a page in Code area. Equivalent to ERASEPAGE. */
#define NVMC_ERASEPCR1_ERASEPCR1_Pos (0UL) /*!< Position of ERASEPCR1 field. */
#define NVMC_ERASEPCR1_ERASEPCR1_Msk (0xFFFFFFFFUL << NVMC_ERASEPCR1_ERASEPCR1_Pos) /*!< Bit mask of ERASEPCR1 field. */

/* Register: NVMC_ERASEALL */
/* Description: Register for erasing all non-volatile user memory */

/* Bit 0 : Erase all non-volatile memory including UICR registers. Note that the erase must be enabled using CONFIG.WEN before the non-volatile memory can be erased. */
#define NVMC_ERASEALL_ERASEALL_Pos (0UL) /*!< Position of ERASEALL field. */
#define NVMC_ERASEALL_ERASEALL_Msk (0x1UL << NVMC_ERASEALL_ERASEALL_Pos) /*!< Bit mask of ERASEALL field. */
#define NVMC_ERASEALL_ERASEALL_NoOperation (0UL) /*!< No operation */
#define NVMC_ERASEALL_ERASEALL_Erase (1UL) /*!< Start chip erase */

/* Register: NVMC_ERASEPCR0 */
/* Description: Deprecated register -  Register for erasing a page in Code area. Equivalent to ERASEPAGE. */

/* Bits 31..0 : Register for starting erase of a page in Code area. Equivalent to ERASEPAGE. */
#define NVMC_ERASEPCR0_ERASEPCR0_Pos (0UL) /*!< Position of ERASEPCR0 field. */
#define NVMC_ERASEPCR0_ERASEPCR0_Msk (0xFFFFFFFFUL << NVMC_ERASEPCR0_ERASEPCR0_Pos) /*!< Bit mask of ERASEPCR0 field. */

/* Register: NVMC_ERASEUICR */
/* Description: Register for erasing User Information Configuration Registers */

/* Bit 0 : Register starting erase of all User Information Configuration Registers. Note that the erase must be enabled using CONFIG.WEN before the UICR can be erased. */
#define NVMC_ERASEUICR_ERASEUICR_Pos (0UL) /*!< Position of ERASEUICR field. */
#define NVMC_ERASEUICR_ERASEUICR_Msk (0x1UL << NVMC_ERASEUICR_ERASEUICR_Pos) /*!< Bit mask of ERASEUICR field. */
#define NVMC_ERASEUICR_ERASEUICR_NoOperation (0UL) /*!< No operation */
#define NVMC_ERASEUICR_ERASEUICR_Erase (1UL) /*!< Start erase of UICR */

/* Register: NVMC_ICACHECNF */
/* Description: I-Code cache configuration register. */

/* Bit 8 : Cache profiling enable */
#define NVMC_ICACHECNF_CACHEPROFEN_Pos (8UL) /*!< Position of CACHEPROFEN field. */
#define NVMC_ICACHECNF_CACHEPROFEN_Msk (0x1UL << NVMC_ICACHECNF_CACHEPROFEN_Pos) /*!< Bit mask of CACHEPROFEN field. */
#define NVMC_ICACHECNF_CACHEPROFEN_Disabled (0UL) /*!< Disable cache profiling */
#define NVMC_ICACHECNF_CACHEPROFEN_Enabled (1UL) /*!< Enable cache profiling */

/* Bit 0 : Cache enable */
#define NVMC_ICACHECNF_CACHEEN_Pos (0UL) /*!< Position of CACHEEN field. */
#define NVMC_ICACHECNF_CACHEEN_Msk (0x1UL << NVMC_ICACHECNF_CACHEEN_Pos) /*!< Bit mask of CACHEEN field. */
#define NVMC_ICACHECNF_CACHEEN_Disabled (0UL) /*!< Disable cache. Invalidates all cache entries. */
#define NVMC_ICACHECNF_CACHEEN_Enabled (1UL) /*!< Enable cache */

/* Register: NVMC_IHIT */
/* Description: I-Code cache hit counter. */

/* Bits 31..0 : Number of cache hits */
#define NVMC_IHIT_HITS_Pos (0UL) /*!< Position of HITS field. */
#define NVMC_IHIT_HITS_Msk (0xFFFFFFFFUL << NVMC_IHIT_HITS_Pos) /*!< Bit mask of HITS field. */

/* Register: NVMC_IMISS */
/* Description: I-Code cache miss counter. */

/* Bits 31..0 : Number of cache misses */
#define NVMC_IMISS_MISSES_Pos (0UL) /*!< Position of MISSES field. */
#define NVMC_IMISS_MISSES_Msk (0xFFFFFFFFUL << NVMC_IMISS_MISSES_Pos) /*!< Bit mask of MISSES field. */


/* Peripheral: GPIO */
/* Description: GPIO Port 1 */

/* Register: GPIO_OUT */
/* Description: Write GPIO port */

/* Bit 31 : Pin 31 */
#define GPIO_OUT_PIN31_Pos (31UL) /*!< Position of PIN31 field. */
#define GPIO_OUT_PIN31_Msk (0x1UL << GPIO_OUT_PIN31_Pos) /*!< Bit mask of PIN31 field. */
#define GPIO_OUT_PIN31_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN31_High (1UL) /*!< Pin driver is high */

/* Bit 30 : Pin 30 */
#define GPIO_OUT_PIN30_Pos (30UL) /*!< Position of PIN30 field. */
#define GPIO_OUT_PIN30_Msk (0x1UL << GPIO_OUT_PIN30_Pos) /*!< Bit mask of PIN30 field. */
#define GPIO_OUT_PIN30_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN30_High (1UL) /*!< Pin driver is high */

/* Bit 29 : Pin 29 */
#define GPIO_OUT_PIN29_Pos (29UL) /*!< Position of PIN29 field. */
#define GPIO_OUT_PIN29_Msk (0x1UL << GPIO_OUT_PIN29_Pos) /*!< Bit mask of PIN29 field. */
#define GPIO_OUT_PIN29_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN29_High (1UL) /*!< Pin driver is high */

/* Bit 28 : Pin 28 */
#define GPIO_OUT_PIN28_Pos (28UL) /*!< Position of PIN28 field. */
#define GPIO_OUT_PIN28_Msk (0x1UL << GPIO_OUT_PIN28_Pos) /*!< Bit mask of PIN28 field. */
#define GPIO_OUT_PIN28_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN28_High (1UL) /*!< Pin driver is high */

/* Bit 27 : Pin 27 */
#define GPIO_OUT_PIN27_Pos (27UL) /*!< Position of PIN27 field. */
#define GPIO_OUT_PIN27_Msk (0x1UL << GPIO_OUT_PIN27_Pos) /*!< Bit mask of PIN27 field. */
#define GPIO_OUT_PIN27_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN27_High (1UL) /*!< Pin driver is high */

/* Bit 26 : Pin 26 */
#define GPIO_OUT_PIN26_Pos (26UL) /*!< Position of PIN26 field. */
#define GPIO_OUT_PIN26_Msk (0x1UL << GPIO_OUT_PIN26_Pos) /*!< Bit mask of PIN26 field. */
#define GPIO_OUT_PIN26_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN26_High (1UL) /*!< Pin driver is high */

/* Bit 25 : Pin 25 */
#define GPIO_OUT_PIN25_Pos (25UL) /*!< Position of PIN25 field. */
#define GPIO_OUT_PIN25_Msk (0x1UL << GPIO_OUT_PIN25_Pos) /*!< Bit mask of PIN25 field. */
#define GPIO_OUT_PIN25_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN25_High (1UL) /*!< Pin driver is high */

/* Bit 24 : Pin 24 */
#define GPIO_OUT_PIN24_Pos (24UL) /*!< Position of PIN24 field. */
#define GPIO_OUT_PIN24_Msk (0x1UL << GPIO_OUT_PIN24_Pos) /*!< Bit mask of PIN24 field. */
#define GPIO_OUT_PIN24_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN24_High (1UL) /*!< Pin driver is high */

/* Bit 23 : Pin 23 */
#define GPIO_OUT_PIN23_Pos (23UL) /*!< Position of PIN23 field. */
#define GPIO_OUT_PIN23_Msk (0x1UL << GPIO_OUT_PIN23_Pos) /*!< Bit mask of PIN23 field. */
#define GPIO_OUT_PIN23_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN23_High (1UL) /*!< Pin driver is high */

/* Bit 22 : Pin 22 */
#define GPIO_OUT_PIN22_Pos (22UL) /*!< Position of PIN22 field. */
#define GPIO_OUT_PIN22_Msk (0x1UL << GPIO_OUT_PIN22_Pos) /*!< Bit mask of PIN22 field. */
#define GPIO_OUT_PIN22_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN22_High (1UL) /*!< Pin driver is high */

/* Bit 21 : Pin 21 */
#define GPIO_OUT_PIN21_Pos (21UL) /*!< Position of PIN21 field. */
#define GPIO_OUT_PIN21_Msk (0x1UL << GPIO_OUT_PIN21_Pos) /*!< Bit mask of PIN21 field. */
#define GPIO_OUT_PIN21_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN21_High (1UL) /*!< Pin driver is high */

/* Bit 20 : Pin 20 */
#define GPIO_OUT_PIN20_Pos (20UL) /*!< Position of PIN20 field. */
#define GPIO_OUT_PIN20_Msk (0x1UL << GPIO_OUT_PIN20_Pos) /*!< Bit mask of PIN20 field. */
#define GPIO_OUT_PIN20_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN20_High (1UL) /*!< Pin driver is high */

/* Bit 19 : Pin 19 */
#define GPIO_OUT_PIN19_Pos (19UL) /*!< Position of PIN19 field. */
#define GPIO_OUT_PIN19_Msk (0x1UL << GPIO_OUT_PIN19_Pos) /*!< Bit mask of PIN19 field. */
#define GPIO_OUT_PIN19_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN19_High (1UL) /*!< Pin driver is high */

/* Bit 18 : Pin 18 */
#define GPIO_OUT_PIN18_Pos (18UL) /*!< Position of PIN18 field. */
#define GPIO_OUT_PIN18_Msk (0x1UL << GPIO_OUT_PIN18_Pos) /*!< Bit mask of PIN18 field. */
#define GPIO_OUT_PIN18_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN18_High (1UL) /*!< Pin driver is high */

/* Bit 17 : Pin 17 */
#define GPIO_OUT_PIN17_Pos (17UL) /*!< Position of PIN17 field. */
#define GPIO_OUT_PIN17_Msk (0x1UL << GPIO_OUT_PIN17_Pos) /*!< Bit mask of PIN17 field. */
#define GPIO_OUT_PIN17_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN17_High (1UL) /*!< Pin driver is high */

/* Bit 16 : Pin 16 */
#define GPIO_OUT_PIN16_Pos (16UL) /*!< Position of PIN16 field. */
#define GPIO_OUT_PIN16_Msk (0x1UL << GPIO_OUT_PIN16_Pos) /*!< Bit mask of PIN16 field. */
#define GPIO_OUT_PIN16_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN16_High (1UL) /*!< Pin driver is high */

/* Bit 15 : Pin 15 */
#define GPIO_OUT_PIN15_Pos (15UL) /*!< Position of PIN15 field. */
#define GPIO_OUT_PIN15_Msk (0x1UL << GPIO_OUT_PIN15_Pos) /*!< Bit mask of PIN15 field. */
#define GPIO_OUT_PIN15_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN15_High (1UL) /*!< Pin driver is high */

/* Bit 14 : Pin 14 */
#define GPIO_OUT_PIN14_Pos (14UL) /*!< Position of PIN14 field. */
#define GPIO_OUT_PIN14_Msk (0x1UL << GPIO_OUT_PIN14_Pos) /*!< Bit mask of PIN14 field. */
#define GPIO_OUT_PIN14_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN14_High (1UL) /*!< Pin driver is high */

/* Bit 13 : Pin 13 */
#define GPIO_OUT_PIN13_Pos (13UL) /*!< Position of PIN13 field. */
#define GPIO_OUT_PIN13_Msk (0x1UL << GPIO_OUT_PIN13_Pos) /*!< Bit mask of PIN13 field. */
#define GPIO_OUT_PIN13_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN13_High (1UL) /*!< Pin driver is high */

/* Bit 12 : Pin 12 */
#define GPIO_OUT_PIN12_Pos (12UL) /*!< Position of PIN12 field. */
#define GPIO_OUT_PIN12_Msk (0x1UL << GPIO_OUT_PIN12_Pos) /*!< Bit mask of PIN12 field. */
#define GPIO_OUT_PIN12_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN12_High (1UL) /*!< Pin driver is high */

/* Bit 11 : Pin 11 */
#define GPIO_OUT_PIN11_Pos (11UL) /*!< Position of PIN11 field. */
#define GPIO_OUT_PIN11_Msk (0x1UL << GPIO_OUT_PIN11_Pos) /*!< Bit mask of PIN11 field. */
#define GPIO_OUT_PIN11_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN11_High (1UL) /*!< Pin driver is high */

/* Bit 10 : Pin 10 */
#define GPIO_OUT_PIN10_Pos (10UL) /*!< Position of PIN10 field. */
#define GPIO_OUT_PIN10_Msk (0x1UL << GPIO_OUT_PIN10_Pos) /*!< Bit mask of PIN10 field. */
#define GPIO_OUT_PIN10_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN10_High (1UL) /*!< Pin driver is high */

/* Bit 9 : Pin 9 */
#define GPIO_OUT_PIN9_Pos (9UL) /*!< Position of PIN9 field. */
#define GPIO_OUT_PIN9_Msk (0x1UL << GPIO_OUT_PIN9_Pos) /*!< Bit mask of PIN9 field. */
#define GPIO_OUT_PIN9_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN9_High (1UL) /*!< Pin driver is high */

/* Bit 8 : Pin 8 */
#define GPIO_OUT_PIN8_Pos (8UL) /*!< Position of PIN8 field. */
#define GPIO_OUT_PIN8_Msk (0x1UL << GPIO_OUT_PIN8_Pos) /*!< Bit mask of PIN8 field. */
#define GPIO_OUT_PIN8_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN8_High (1UL) /*!< Pin driver is high */

/* Bit 7 : Pin 7 */
#define GPIO_OUT_PIN7_Pos (7UL) /*!< Position of PIN7 field. */
#define GPIO_OUT_PIN7_Msk (0x1UL << GPIO_OUT_PIN7_Pos) /*!< Bit mask of PIN7 field. */
#define GPIO_OUT_PIN7_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN7_High (1UL) /*!< Pin driver is high */

/* Bit 6 : Pin 6 */
#define GPIO_OUT_PIN6_Pos (6UL) /*!< Position of PIN6 field. */
#define GPIO_OUT_PIN6_Msk (0x1UL << GPIO_OUT_PIN6_Pos) /*!< Bit mask of PIN6 field. */
#define GPIO_OUT_PIN6_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN6_High (1UL) /*!< Pin driver is high */

/* Bit 5 : Pin 5 */
#define GPIO_OUT_PIN5_Pos (5UL) /*!< Position of PIN5 field. */
#define GPIO_OUT_PIN5_Msk (0x1UL << GPIO_OUT_PIN5_Pos) /*!< Bit mask of PIN5 field. */
#define GPIO_OUT_PIN5_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN5_High (1UL) /*!< Pin driver is high */

/* Bit 4 : Pin 4 */
#define GPIO_OUT_PIN4_Pos (4UL) /*!< Position of PIN4 field. */
#define GPIO_OUT_PIN4_Msk (0x1UL << GPIO_OUT_PIN4_Pos) /*!< Bit mask of PIN4 field. */
#define GPIO_OUT_PIN4_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN4_High (1UL) /*!< Pin driver is high */

/* Bit 3 : Pin 3 */
#define GPIO_OUT_PIN3_Pos (3UL) /*!< Position of PIN3 field. */
#define GPIO_OUT_PIN3_Msk (0x1UL << GPIO_OUT_PIN3_Pos) /*!< Bit mask of PIN3 field. */
#define GPIO_OUT_PIN3_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN3_High (1UL) /*!< Pin driver is high */

/* Bit 2 : Pin 2 */
#define GPIO_OUT_PIN2_Pos (2UL) /*!< Position of PIN2 field. */
#define GPIO_OUT_PIN2_Msk (0x1UL << GPIO_OUT_PIN2_Pos) /*!< Bit mask of PIN2 field. */
#define GPIO_OUT_PIN2_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN2_High (1UL) /*!< Pin driver is high */

/* Bit 1 : Pin 1 */
#define GPIO_OUT_PIN1_Pos (1UL) /*!< Position of PIN1 field. */
#define GPIO_OUT_PIN1_Msk (0x1UL << GPIO_OUT_PIN1_Pos) /*!< Bit mask of PIN1 field. */
#define GPIO_OUT_PIN1_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN1_High (1UL) /*!< Pin driver is high */

/* Bit 0 : Pin 0 */
#define GPIO_OUT_PIN0_Pos (0UL) /*!< Position of PIN0 field. */
#define GPIO_OUT_PIN0_Msk (0x1UL << GPIO_OUT_PIN0_Pos) /*!< Bit mask of PIN0 field. */
#define GPIO_OUT_PIN0_Low (0UL) /*!< Pin driver is low */
#define GPIO_OUT_PIN0_High (1UL) /*!< Pin driver is high */

/* Register: GPIO_OUTSET */
/* Description: Set individual bits in GPIO port */

/* Bit 31 : Pin 31 */
#define GPIO_OUTSET_PIN31_Pos (31UL) /*!< Position of PIN31 field. */
#define GPIO_OUTSET_PIN31_Msk (0x1UL << GPIO_OUTSET_PIN31_Pos) /*!< Bit mask of PIN31 field. */
#define GPIO_OUTSET_PIN31_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN31_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN31_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 30 : Pin 30 */
#define GPIO_OUTSET_PIN30_Pos (30UL) /*!< Position of PIN30 field. */
#define GPIO_OUTSET_PIN30_Msk (0x1UL << GPIO_OUTSET_PIN30_Pos) /*!< Bit mask of PIN30 field. */
#define GPIO_OUTSET_PIN30_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN30_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN30_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 29 : Pin 29 */
#define GPIO_OUTSET_PIN29_Pos (29UL) /*!< Position of PIN29 field. */
#define GPIO_OUTSET_PIN29_Msk (0x1UL << GPIO_OUTSET_PIN29_Pos) /*!< Bit mask of PIN29 field. */
#define GPIO_OUTSET_PIN29_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN29_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN29_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 28 : Pin 28 */
#define GPIO_OUTSET_PIN28_Pos (28UL) /*!< Position of PIN28 field. */
#define GPIO_OUTSET_PIN28_Msk (0x1UL << GPIO_OUTSET_PIN28_Pos) /*!< Bit mask of PIN28 field. */
#define GPIO_OUTSET_PIN28_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN28_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN28_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 27 : Pin 27 */
#define GPIO_OUTSET_PIN27_Pos (27UL) /*!< Position of PIN27 field. */
#define GPIO_OUTSET_PIN27_Msk (0x1UL << GPIO_OUTSET_PIN27_Pos) /*!< Bit mask of PIN27 field. */
#define GPIO_OUTSET_PIN27_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN27_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN27_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 26 : Pin 26 */
#define GPIO_OUTSET_PIN26_Pos (26UL) /*!< Position of PIN26 field. */
#define GPIO_OUTSET_PIN26_Msk (0x1UL << GPIO_OUTSET_PIN26_Pos) /*!< Bit mask of PIN26 field. */
#define GPIO_OUTSET_PIN26_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN26_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN26_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 25 : Pin 25 */
#define GPIO_OUTSET_PIN25_Pos (25UL) /*!< Position of PIN25 field. */
#define GPIO_OUTSET_PIN25_Msk (0x1UL << GPIO_OUTSET_PIN25_Pos) /*!< Bit mask of PIN25 field. */
#define GPIO_OUTSET_PIN25_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN25_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN25_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 24 : Pin 24 */
#define GPIO_OUTSET_PIN24_Pos (24UL) /*!< Position of PIN24 field. */
#define GPIO_OUTSET_PIN24_Msk (0x1UL << GPIO_OUTSET_PIN24_Pos) /*!< Bit mask of PIN24 field. */
#define GPIO_OUTSET_PIN24_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN24_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN24_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 23 : Pin 23 */
#define GPIO_OUTSET_PIN23_Pos (23UL) /*!< Position of PIN23 field. */
#define GPIO_OUTSET_PIN23_Msk (0x1UL << GPIO_OUTSET_PIN23_Pos) /*!< Bit mask of PIN23 field. */
#define GPIO_OUTSET_PIN23_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN23_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN23_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 22 : Pin 22 */
#define GPIO_OUTSET_PIN22_Pos (22UL) /*!< Position of PIN22 field. */
#define GPIO_OUTSET_PIN22_Msk (0x1UL << GPIO_OUTSET_PIN22_Pos) /*!< Bit mask of PIN22 field. */
#define GPIO_OUTSET_PIN22_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN22_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN22_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 21 : Pin 21 */
#define GPIO_OUTSET_PIN21_Pos (21UL) /*!< Position of PIN21 field. */
#define GPIO_OUTSET_PIN21_Msk (0x1UL << GPIO_OUTSET_PIN21_Pos) /*!< Bit mask of PIN21 field. */
#define GPIO_OUTSET_PIN21_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN21_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN21_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 20 : Pin 20 */
#define GPIO_OUTSET_PIN20_Pos (20UL) /*!< Position of PIN20 field. */
#define GPIO_OUTSET_PIN20_Msk (0x1UL << GPIO_OUTSET_PIN20_Pos) /*!< Bit mask of PIN20 field. */
#define GPIO_OUTSET_PIN20_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN20_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN20_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 19 : Pin 19 */
#define GPIO_OUTSET_PIN19_Pos (19UL) /*!< Position of PIN19 field. */
#define GPIO_OUTSET_PIN19_Msk (0x1UL << GPIO_OUTSET_PIN19_Pos) /*!< Bit mask of PIN19 field. */
#define GPIO_OUTSET_PIN19_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN19_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN19_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 18 : Pin 18 */
#define GPIO_OUTSET_PIN18_Pos (18UL) /*!< Position of PIN18 field. */
#define GPIO_OUTSET_PIN18_Msk (0x1UL << GPIO_OUTSET_PIN18_Pos) /*!< Bit mask of PIN18 field. */
#define GPIO_OUTSET_PIN18_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN18_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN18_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 17 : Pin 17 */
#define GPIO_OUTSET_PIN17_Pos (17UL) /*!< Position of PIN17 field. */
#define GPIO_OUTSET_PIN17_Msk (0x1UL << GPIO_OUTSET_PIN17_Pos) /*!< Bit mask of PIN17 field. */
#define GPIO_OUTSET_PIN17_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN17_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN17_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 16 : Pin 16 */
#define GPIO_OUTSET_PIN16_Pos (16UL) /*!< Position of PIN16 field. */
#define GPIO_OUTSET_PIN16_Msk (0x1UL << GPIO_OUTSET_PIN16_Pos) /*!< Bit mask of PIN16 field. */
#define GPIO_OUTSET_PIN16_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN16_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN16_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 15 : Pin 15 */
#define GPIO_OUTSET_PIN15_Pos (15UL) /*!< Position of PIN15 field. */
#define GPIO_OUTSET_PIN15_Msk (0x1UL << GPIO_OUTSET_PIN15_Pos) /*!< Bit mask of PIN15 field. */
#define GPIO_OUTSET_PIN15_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN15_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN15_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 14 : Pin 14 */
#define GPIO_OUTSET_PIN14_Pos (14UL) /*!< Position of PIN14 field. */
#define GPIO_OUTSET_PIN14_Msk (0x1UL << GPIO_OUTSET_PIN14_Pos) /*!< Bit mask of PIN14 field. */
#define GPIO_OUTSET_PIN14_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN14_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN14_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 13 : Pin 13 */
#define GPIO_OUTSET_PIN13_Pos (13UL) /*!< Position of PIN13 field. */
#define GPIO_OUTSET_PIN13_Msk (0x1UL << GPIO_OUTSET_PIN13_Pos) /*!< Bit mask of PIN13 field. */
#define GPIO_OUTSET_PIN13_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN13_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN13_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 12 : Pin 12 */
#define GPIO_OUTSET_PIN12_Pos (12UL) /*!< Position of PIN12 field. */
#define GPIO_OUTSET_PIN12_Msk (0x1UL << GPIO_OUTSET_PIN12_Pos) /*!< Bit mask of PIN12 field. */
#define GPIO_OUTSET_PIN12_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN12_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN12_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 11 : Pin 11 */
#define GPIO_OUTSET_PIN11_Pos (11UL) /*!< Position of PIN11 field. */
#define GPIO_OUTSET_PIN11_Msk (0x1UL << GPIO_OUTSET_PIN11_Pos) /*!< Bit mask of PIN11 field. */
#define GPIO_OUTSET_PIN11_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN11_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN11_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 10 : Pin 10 */
#define GPIO_OUTSET_PIN10_Pos (10UL) /*!< Position of PIN10 field. */
#define GPIO_OUTSET_PIN10_Msk (0x1UL << GPIO_OUTSET_PIN10_Pos) /*!< Bit mask of PIN10 field. */
#define GPIO_OUTSET_PIN10_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN10_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN10_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 9 : Pin 9 */
#define GPIO_OUTSET_PIN9_Pos (9UL) /*!< Position of PIN9 field. */
#define GPIO_OUTSET_PIN9_Msk (0x1UL << GPIO_OUTSET_PIN9_Pos) /*!< Bit mask of PIN9 field. */
#define GPIO_OUTSET_PIN9_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN9_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN9_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 8 : Pin 8 */
#define GPIO_OUTSET_PIN8_Pos (8UL) /*!< Position of PIN8 field. */
#define GPIO_OUTSET_PIN8_Msk (0x1UL << GPIO_OUTSET_PIN8_Pos) /*!< Bit mask of PIN8 field. */
#define GPIO_OUTSET_PIN8_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN8_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN8_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 7 : Pin 7 */
#define GPIO_OUTSET_PIN7_Pos (7UL) /*!< Position of PIN7 field. */
#define GPIO_OUTSET_PIN7_Msk (0x1UL << GPIO_OUTSET_PIN7_Pos) /*!< Bit mask of PIN7 field. */
#define GPIO_OUTSET_PIN7_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN7_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN7_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 6 : Pin 6 */
#define GPIO_OUTSET_PIN6_Pos (6UL) /*!< Position of PIN6 field. */
#define GPIO_OUTSET_PIN6_Msk (0x1UL << GPIO_OUTSET_PIN6_Pos) /*!< Bit mask of PIN6 field. */
#define GPIO_OUTSET_PIN6_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN6_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN6_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 5 : Pin 5 */
#define GPIO_OUTSET_PIN5_Pos (5UL) /*!< Position of PIN5 field. */
#define GPIO_OUTSET_PIN5_Msk (0x1UL << GPIO_OUTSET_PIN5_Pos) /*!< Bit mask of PIN5 field. */
#define GPIO_OUTSET_PIN5_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN5_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN5_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 4 : Pin 4 */
#define GPIO_OUTSET_PIN4_Pos (4UL) /*!< Position of PIN4 field. */
#define GPIO_OUTSET_PIN4_Msk (0x1UL << GPIO_OUTSET_PIN4_Pos) /*!< Bit mask of PIN4 field. */
#define GPIO_OUTSET_PIN4_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN4_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN4_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 3 : Pin 3 */
#define GPIO_OUTSET_PIN3_Pos (3UL) /*!< Position of PIN3 field. */
#define GPIO_OUTSET_PIN3_Msk (0x1UL << GPIO_OUTSET_PIN3_Pos) /*!< Bit mask of PIN3 field. */
#define GPIO_OUTSET_PIN3_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN3_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN3_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 2 : Pin 2 */
#define GPIO_OUTSET_PIN2_Pos (2UL) /*!< Position of PIN2 field. */
#define GPIO_OUTSET_PIN2_Msk (0x1UL << GPIO_OUTSET_PIN2_Pos) /*!< Bit mask of PIN2 field. */
#define GPIO_OUTSET_PIN2_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN2_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN2_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 1 : Pin 1 */
#define GPIO_OUTSET_PIN1_Pos (1UL) /*!< Position of PIN1 field. */
#define GPIO_OUTSET_PIN1_Msk (0x1UL << GPIO_OUTSET_PIN1_Pos) /*!< Bit mask of PIN1 field. */
#define GPIO_OUTSET_PIN1_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN1_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN1_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Bit 0 : Pin 0 */
#define GPIO_OUTSET_PIN0_Pos (0UL) /*!< Position of PIN0 field. */
#define GPIO_OUTSET_PIN0_Msk (0x1UL << GPIO_OUTSET_PIN0_Pos) /*!< Bit mask of PIN0 field. */
#define GPIO_OUTSET_PIN0_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTSET_PIN0_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTSET_PIN0_Set (1UL) /*!< Write: writing a '1' sets the pin high; writing a '0' has no effect */

/* Register: GPIO_OUTCLR */
/* Description: Clear individual bits in GPIO port */

/* Bit 31 : Pin 31 */
#define GPIO_OUTCLR_PIN31_Pos (31UL) /*!< Position of PIN31 field. */
#define GPIO_OUTCLR_PIN31_Msk (0x1UL << GPIO_OUTCLR_PIN31_Pos) /*!< Bit mask of PIN31 field. */
#define GPIO_OUTCLR_PIN31_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN31_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN31_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 30 : Pin 30 */
#define GPIO_OUTCLR_PIN30_Pos (30UL) /*!< Position of PIN30 field. */
#define GPIO_OUTCLR_PIN30_Msk (0x1UL << GPIO_OUTCLR_PIN30_Pos) /*!< Bit mask of PIN30 field. */
#define GPIO_OUTCLR_PIN30_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN30_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN30_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 29 : Pin 29 */
#define GPIO_OUTCLR_PIN29_Pos (29UL) /*!< Position of PIN29 field. */
#define GPIO_OUTCLR_PIN29_Msk (0x1UL << GPIO_OUTCLR_PIN29_Pos) /*!< Bit mask of PIN29 field. */
#define GPIO_OUTCLR_PIN29_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN29_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN29_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 28 : Pin 28 */
#define GPIO_OUTCLR_PIN28_Pos (28UL) /*!< Position of PIN28 field. */
#define GPIO_OUTCLR_PIN28_Msk (0x1UL << GPIO_OUTCLR_PIN28_Pos) /*!< Bit mask of PIN28 field. */
#define GPIO_OUTCLR_PIN28_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN28_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN28_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 27 : Pin 27 */
#define GPIO_OUTCLR_PIN27_Pos (27UL) /*!< Position of PIN27 field. */
#define GPIO_OUTCLR_PIN27_Msk (0x1UL << GPIO_OUTCLR_PIN27_Pos) /*!< Bit mask of PIN27 field. */
#define GPIO_OUTCLR_PIN27_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN27_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN27_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 26 : Pin 26 */
#define GPIO_OUTCLR_PIN26_Pos (26UL) /*!< Position of PIN26 field. */
#define GPIO_OUTCLR_PIN26_Msk (0x1UL << GPIO_OUTCLR_PIN26_Pos) /*!< Bit mask of PIN26 field. */
#define GPIO_OUTCLR_PIN26_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN26_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN26_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 25 : Pin 25 */
#define GPIO_OUTCLR_PIN25_Pos (25UL) /*!< Position of PIN25 field. */
#define GPIO_OUTCLR_PIN25_Msk (0x1UL << GPIO_OUTCLR_PIN25_Pos) /*!< Bit mask of PIN25 field. */
#define GPIO_OUTCLR_PIN25_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN25_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN25_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 24 : Pin 24 */
#define GPIO_OUTCLR_PIN24_Pos (24UL) /*!< Position of PIN24 field. */
#define GPIO_OUTCLR_PIN24_Msk (0x1UL << GPIO_OUTCLR_PIN24_Pos) /*!< Bit mask of PIN24 field. */
#define GPIO_OUTCLR_PIN24_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN24_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN24_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 23 : Pin 23 */
#define GPIO_OUTCLR_PIN23_Pos (23UL) /*!< Position of PIN23 field. */
#define GPIO_OUTCLR_PIN23_Msk (0x1UL << GPIO_OUTCLR_PIN23_Pos) /*!< Bit mask of PIN23 field. */
#define GPIO_OUTCLR_PIN23_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN23_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN23_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 22 : Pin 22 */
#define GPIO_OUTCLR_PIN22_Pos (22UL) /*!< Position of PIN22 field. */
#define GPIO_OUTCLR_PIN22_Msk (0x1UL << GPIO_OUTCLR_PIN22_Pos) /*!< Bit mask of PIN22 field. */
#define GPIO_OUTCLR_PIN22_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN22_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN22_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 21 : Pin 21 */
#define GPIO_OUTCLR_PIN21_Pos (21UL) /*!< Position of PIN21 field. */
#define GPIO_OUTCLR_PIN21_Msk (0x1UL << GPIO_OUTCLR_PIN21_Pos) /*!< Bit mask of PIN21 field. */
#define GPIO_OUTCLR_PIN21_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN21_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN21_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 20 : Pin 20 */
#define GPIO_OUTCLR_PIN20_Pos (20UL) /*!< Position of PIN20 field. */
#define GPIO_OUTCLR_PIN20_Msk (0x1UL << GPIO_OUTCLR_PIN20_Pos) /*!< Bit mask of PIN20 field. */
#define GPIO_OUTCLR_PIN20_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN20_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN20_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 19 : Pin 19 */
#define GPIO_OUTCLR_PIN19_Pos (19UL) /*!< Position of PIN19 field. */
#define GPIO_OUTCLR_PIN19_Msk (0x1UL << GPIO_OUTCLR_PIN19_Pos) /*!< Bit mask of PIN19 field. */
#define GPIO_OUTCLR_PIN19_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN19_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN19_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 18 : Pin 18 */
#define GPIO_OUTCLR_PIN18_Pos (18UL) /*!< Position of PIN18 field. */
#define GPIO_OUTCLR_PIN18_Msk (0x1UL << GPIO_OUTCLR_PIN18_Pos) /*!< Bit mask of PIN18 field. */
#define GPIO_OUTCLR_PIN18_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN18_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN18_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 17 : Pin 17 */
#define GPIO_OUTCLR_PIN17_Pos (17UL) /*!< Position of PIN17 field. */
#define GPIO_OUTCLR_PIN17_Msk (0x1UL << GPIO_OUTCLR_PIN17_Pos) /*!< Bit mask of PIN17 field. */
#define GPIO_OUTCLR_PIN17_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN17_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN17_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 16 : Pin 16 */
#define GPIO_OUTCLR_PIN16_Pos (16UL) /*!< Position of PIN16 field. */
#define GPIO_OUTCLR_PIN16_Msk (0x1UL << GPIO_OUTCLR_PIN16_Pos) /*!< Bit mask of PIN16 field. */
#define GPIO_OUTCLR_PIN16_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN16_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN16_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 15 : Pin 15 */
#define GPIO_OUTCLR_PIN15_Pos (15UL) /*!< Position of PIN15 field. */
#define GPIO_OUTCLR_PIN15_Msk (0x1UL << GPIO_OUTCLR_PIN15_Pos) /*!< Bit mask of PIN15 field. */
#define GPIO_OUTCLR_PIN15_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN15_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN15_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 14 : Pin 14 */
#define GPIO_OUTCLR_PIN14_Pos (14UL) /*!< Position of PIN14 field. */
#define GPIO_OUTCLR_PIN14_Msk (0x1UL << GPIO_OUTCLR_PIN14_Pos) /*!< Bit mask of PIN14 field. */
#define GPIO_OUTCLR_PIN14_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN14_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN14_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 13 : Pin 13 */
#define GPIO_OUTCLR_PIN13_Pos (13UL) /*!< Position of PIN13 field. */
#define GPIO_OUTCLR_PIN13_Msk (0x1UL << GPIO_OUTCLR_PIN13_Pos) /*!< Bit mask of PIN13 field. */
#define GPIO_OUTCLR_PIN13_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN13_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN13_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 12 : Pin 12 */
#define GPIO_OUTCLR_PIN12_Pos (12UL) /*!< Position of PIN12 field. */
#define GPIO_OUTCLR_PIN12_Msk (0x1UL << GPIO_OUTCLR_PIN12_Pos) /*!< Bit mask of PIN12 field. */
#define GPIO_OUTCLR_PIN12_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN12_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN12_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 11 : Pin 11 */
#define GPIO_OUTCLR_PIN11_Pos (11UL) /*!< Position of PIN11 field. */
#define GPIO_OUTCLR_PIN11_Msk (0x1UL << GPIO_OUTCLR_PIN11_Pos) /*!< Bit mask of PIN11 field. */
#define GPIO_OUTCLR_PIN11_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN11_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN11_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 10 : Pin 10 */
#define GPIO_OUTCLR_PIN10_Pos (10UL) /*!< Position of PIN10 field. */
#define GPIO_OUTCLR_PIN10_Msk (0x1UL << GPIO_OUTCLR_PIN10_Pos) /*!< Bit mask of PIN10 field. */
#define GPIO_OUTCLR_PIN10_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN10_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN10_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 9 : Pin 9 */
#define GPIO_OUTCLR_PIN9_Pos (9UL) /*!< Position of PIN9 field. */
#define GPIO_OUTCLR_PIN9_Msk (0x1UL << GPIO_OUTCLR_PIN9_Pos) /*!< Bit mask of PIN9 field. */
#define GPIO_OUTCLR_PIN9_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN9_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN9_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 8 : Pin 8 */
#define GPIO_OUTCLR_PIN8_Pos (8UL) /*!< Position of PIN8 field. */
#define GPIO_OUTCLR_PIN8_Msk (0x1UL << GPIO_OUTCLR_PIN8_Pos) /*!< Bit mask of PIN8 field. */
#define GPIO_OUTCLR_PIN8_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN8_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN8_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 7 : Pin 7 */
#define GPIO_OUTCLR_PIN7_Pos (7UL) /*!< Position of PIN7 field. */
#define GPIO_OUTCLR_PIN7_Msk (0x1UL << GPIO_OUTCLR_PIN7_Pos) /*!< Bit mask of PIN7 field. */
#define GPIO_OUTCLR_PIN7_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN7_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN7_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 6 : Pin 6 */
#define GPIO_OUTCLR_PIN6_Pos (6UL) /*!< Position of PIN6 field. */
#define GPIO_OUTCLR_PIN6_Msk (0x1UL << GPIO_OUTCLR_PIN6_Pos) /*!< Bit mask of PIN6 field. */
#define GPIO_OUTCLR_PIN6_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN6_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN6_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 5 : Pin 5 */
#define GPIO_OUTCLR_PIN5_Pos (5UL) /*!< Position of PIN5 field. */
#define GPIO_OUTCLR_PIN5_Msk (0x1UL << GPIO_OUTCLR_PIN5_Pos) /*!< Bit mask of PIN5 field. */
#define GPIO_OUTCLR_PIN5_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN5_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN5_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 4 : Pin 4 */
#define GPIO_OUTCLR_PIN4_Pos (4UL) /*!< Position of PIN4 field. */
#define GPIO_OUTCLR_PIN4_Msk (0x1UL << GPIO_OUTCLR_PIN4_Pos) /*!< Bit mask of PIN4 field. */
#define GPIO_OUTCLR_PIN4_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN4_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN4_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 3 : Pin 3 */
#define GPIO_OUTCLR_PIN3_Pos (3UL) /*!< Position of PIN3 field. */
#define GPIO_OUTCLR_PIN3_Msk (0x1UL << GPIO_OUTCLR_PIN3_Pos) /*!< Bit mask of PIN3 field. */
#define GPIO_OUTCLR_PIN3_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN3_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN3_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 2 : Pin 2 */
#define GPIO_OUTCLR_PIN2_Pos (2UL) /*!< Position of PIN2 field. */
#define GPIO_OUTCLR_PIN2_Msk (0x1UL << GPIO_OUTCLR_PIN2_Pos) /*!< Bit mask of PIN2 field. */
#define GPIO_OUTCLR_PIN2_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN2_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN2_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 1 : Pin 1 */
#define GPIO_OUTCLR_PIN1_Pos (1UL) /*!< Position of PIN1 field. */
#define GPIO_OUTCLR_PIN1_Msk (0x1UL << GPIO_OUTCLR_PIN1_Pos) /*!< Bit mask of PIN1 field. */
#define GPIO_OUTCLR_PIN1_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN1_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN1_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Bit 0 : Pin 0 */
#define GPIO_OUTCLR_PIN0_Pos (0UL) /*!< Position of PIN0 field. */
#define GPIO_OUTCLR_PIN0_Msk (0x1UL << GPIO_OUTCLR_PIN0_Pos) /*!< Bit mask of PIN0 field. */
#define GPIO_OUTCLR_PIN0_Low (0UL) /*!< Read: pin driver is low */
#define GPIO_OUTCLR_PIN0_High (1UL) /*!< Read: pin driver is high */
#define GPIO_OUTCLR_PIN0_Clear (1UL) /*!< Write: writing a '1' sets the pin low; writing a '0' has no effect */

/* Register: GPIO_IN */
/* Description: Read GPIO port */

/* Bit 31 : Pin 31 */
#define GPIO_IN_PIN31_Pos (31UL) /*!< Position of PIN31 field. */
#define GPIO_IN_PIN31_Msk (0x1UL << GPIO_IN_PIN31_Pos) /*!< Bit mask of PIN31 field. */
#define GPIO_IN_PIN31_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN31_High (1UL) /*!< Pin input is high */

/* Bit 30 : Pin 30 */
#define GPIO_IN_PIN30_Pos (30UL) /*!< Position of PIN30 field. */
#define GPIO_IN_PIN30_Msk (0x1UL << GPIO_IN_PIN30_Pos) /*!< Bit mask of PIN30 field. */
#define GPIO_IN_PIN30_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN30_High (1UL) /*!< Pin input is high */

/* Bit 29 : Pin 29 */
#define GPIO_IN_PIN29_Pos (29UL) /*!< Position of PIN29 field. */
#define GPIO_IN_PIN29_Msk (0x1UL << GPIO_IN_PIN29_Pos) /*!< Bit mask of PIN29 field. */
#define GPIO_IN_PIN29_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN29_High (1UL) /*!< Pin input is high */

/* Bit 28 : Pin 28 */
#define GPIO_IN_PIN28_Pos (28UL) /*!< Position of PIN28 field. */
#define GPIO_IN_PIN28_Msk (0x1UL << GPIO_IN_PIN28_Pos) /*!< Bit mask of PIN28 field. */
#define GPIO_IN_PIN28_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN28_High (1UL) /*!< Pin input is high */

/* Bit 27 : Pin 27 */
#define GPIO_IN_PIN27_Pos (27UL) /*!< Position of PIN27 field. */
#define GPIO_IN_PIN27_Msk (0x1UL << GPIO_IN_PIN27_Pos) /*!< Bit mask of PIN27 field. */
#define GPIO_IN_PIN27_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN27_High (1UL) /*!< Pin input is high */

/* Bit 26 : Pin 26 */
#define GPIO_IN_PIN26_Pos (26UL) /*!< Position of PIN26 field. */
#define GPIO_IN_PIN26_Msk (0x1UL << GPIO_IN_PIN26_Pos) /*!< Bit mask of PIN26 field. */
#define GPIO_IN_PIN26_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN26_High (1UL) /*!< Pin input is high */

/* Bit 25 : Pin 25 */
#define GPIO_IN_PIN25_Pos (25UL) /*!< Position of PIN25 field. */
#define GPIO_IN_PIN25_Msk (0x1UL << GPIO_IN_PIN25_Pos) /*!< Bit mask of PIN25 field. */
#define GPIO_IN_PIN25_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN25_High (1UL) /*!< Pin input is high */

/* Bit 24 : Pin 24 */
#define GPIO_IN_PIN24_Pos (24UL) /*!< Position of PIN24 field. */
#define GPIO_IN_PIN24_Msk (0x1UL << GPIO_IN_PIN24_Pos) /*!< Bit mask of PIN24 field. */
#define GPIO_IN_PIN24_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN24_High (1UL) /*!< Pin input is high */

/* Bit 23 : Pin 23 */
#define GPIO_IN_PIN23_Pos (23UL) /*!< Position of PIN23 field. */
#define GPIO_IN_PIN23_Msk (0x1UL << GPIO_IN_PIN23_Pos) /*!< Bit mask of PIN23 field. */
#define GPIO_IN_PIN23_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN23_High (1UL) /*!< Pin input is high */

/* Bit 22 : Pin 22 */
#define GPIO_IN_PIN22_Pos (22UL) /*!< Position of PIN22 field. */
#define GPIO_IN_PIN22_Msk (0x1UL << GPIO_IN_PIN22_Pos) /*!< Bit mask of PIN22 field. */
#define GPIO_IN_PIN22_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN22_High (1UL) /*!< Pin input is high */

/* Bit 21 : Pin 21 */
#define GPIO_IN_PIN21_Pos (21UL) /*!< Position of PIN21 field. */
#define GPIO_IN_PIN21_Msk (0x1UL << GPIO_IN_PIN21_Pos) /*!< Bit mask of PIN21 field. */
#define GPIO_IN_PIN21_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN21_High (1UL) /*!< Pin input is high */

/* Bit 20 : Pin 20 */
#define GPIO_IN_PIN20_Pos (20UL) /*!< Position of PIN20 field. */
#define GPIO_IN_PIN20_Msk (0x1UL << GPIO_IN_PIN20_Pos) /*!< Bit mask of PIN20 field. */
#define GPIO_IN_PIN20_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN20_High (1UL) /*!< Pin input is high */

/* Bit 19 : Pin 19 */
#define GPIO_IN_PIN19_Pos (19UL) /*!< Position of PIN19 field. */
#define GPIO_IN_PIN19_Msk (0x1UL << GPIO_IN_PIN19_Pos) /*!< Bit mask of PIN19 field. */
#define GPIO_IN_PIN19_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN19_High (1UL) /*!< Pin input is high */

/* Bit 18 : Pin 18 */
#define GPIO_IN_PIN18_Pos (18UL) /*!< Position of PIN18 field. */
#define GPIO_IN_PIN18_Msk (0x1UL << GPIO_IN_PIN18_Pos) /*!< Bit mask of PIN18 field. */
#define GPIO_IN_PIN18_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN18_High (1UL) /*!< Pin input is high */

/* Bit 17 : Pin 17 */
#define GPIO_IN_PIN17_Pos (17UL) /*!< Position of PIN17 field. */
#define GPIO_IN_PIN17_Msk (0x1UL << GPIO_IN_PIN17_Pos) /*!< Bit mask of PIN17 field. */
#define GPIO_IN_PIN17_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN17_High (1UL) /*!< Pin input is high */

/* Bit 16 : Pin 16 */
#define GPIO_IN_PIN16_Pos (16UL) /*!< Position of PIN16 field. */
#define GPIO_IN_PIN16_Msk (0x1UL << GPIO_IN_PIN16_Pos) /*!< Bit mask of PIN16 field. */
#define GPIO_IN_PIN16_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN16_High (1UL) /*!< Pin input is high */

/* Bit 15 : Pin 15 */
#define GPIO_IN_PIN15_Pos (15UL) /*!< Position of PIN15 field. */
#define GPIO_IN_PIN15_Msk (0x1UL << GPIO_IN_PIN15_Pos) /*!< Bit mask of PIN15 field. */
#define GPIO_IN_PIN15_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN15_High (1UL) /*!< Pin input is high */

/* Bit 14 : Pin 14 */
#define GPIO_IN_PIN14_Pos (14UL) /*!< Position of PIN14 field. */
#define GPIO_IN_PIN14_Msk (0x1UL << GPIO_IN_PIN14_Pos) /*!< Bit mask of PIN14 field. */
#define GPIO_IN_PIN14_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN14_High (1UL) /*!< Pin input is high */

/* Bit 13 : Pin 13 */
#define GPIO_IN_PIN13_Pos (13UL) /*!< Position of PIN13 field. */
#define GPIO_IN_PIN13_Msk (0x1UL << GPIO_IN_PIN13_Pos) /*!< Bit mask of PIN13 field. */
#define GPIO_IN_PIN13_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN13_High (1UL) /*!< Pin input is high */

/* Bit 12 : Pin 12 */
#define GPIO_IN_PIN12_Pos (12UL) /*!< Position of PIN12 field. */
#define GPIO_IN_PIN12_Msk (0x1UL << GPIO_IN_PIN12_Pos) /*!< Bit mask of PIN12 field. */
#define GPIO_IN_PIN12_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN12_High (1UL) /*!< Pin input is high */

/* Bit 11 : Pin 11 */
#define GPIO_IN_PIN11_Pos (11UL) /*!< Position of PIN11 field. */
#define GPIO_IN_PIN11_Msk (0x1UL << GPIO_IN_PIN11_Pos) /*!< Bit mask of PIN11 field. */
#define GPIO_IN_PIN11_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN11_High (1UL) /*!< Pin input is high */

/* Bit 10 : Pin 10 */
#define GPIO_IN_PIN10_Pos (10UL) /*!< Position of PIN10 field. */
#define GPIO_IN_PIN10_Msk (0x1UL << GPIO_IN_PIN10_Pos) /*!< Bit mask of PIN10 field. */
#define GPIO_IN_PIN10_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN10_High (1UL) /*!< Pin input is high */

/* Bit 9 : Pin 9 */
#define GPIO_IN_PIN9_Pos (9UL) /*!< Position of PIN9 field. */
#define GPIO_IN_PIN9_Msk (0x1UL << GPIO_IN_PIN9_Pos) /*!< Bit mask of PIN9 field. */
#define GPIO_IN_PIN9_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN9_High (1UL) /*!< Pin input is high */

/* Bit 8 : Pin 8 */
#define GPIO_IN_PIN8_Pos (8UL) /*!< Position of PIN8 field. */
#define GPIO_IN_PIN8_Msk (0x1UL << GPIO_IN_PIN8_Pos) /*!< Bit mask of PIN8 field. */
#define GPIO_IN_PIN8_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN8_High (1UL) /*!< Pin input is high */

/* Bit 7 : Pin 7 */
#define GPIO_IN_PIN7_Pos (7UL) /*!< Position of PIN7 field. */
#define GPIO_IN_PIN7_Msk (0x1UL << GPIO_IN_PIN7_Pos) /*!< Bit mask of PIN7 field. */
#define GPIO_IN_PIN7_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN7_High (1UL) /*!< Pin input is high */

/* Bit 6 : Pin 6 */
#define GPIO_IN_PIN6_Pos (6UL) /*!< Position of PIN6 field. */
#define GPIO_IN_PIN6_Msk (0x1UL << GPIO_IN_PIN6_Pos) /*!< Bit mask of PIN6 field. */
#define GPIO_IN_PIN6_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN6_High (1UL) /*!< Pin input is high */

/* Bit 5 : Pin 5 */
#define GPIO_IN_PIN5_Pos (5UL) /*!< Position of PIN5 field. */
#define GPIO_IN_PIN5_Msk (0x1UL << GPIO_IN_PIN5_Pos) /*!< Bit mask of PIN5 field. */
#define GPIO_IN_PIN5_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN5_High (1UL) /*!< Pin input is high */

/* Bit 4 : Pin 4 */
#define GPIO_IN_PIN4_Pos (4UL) /*!< Position of PIN4 field. */
#define GPIO_IN_PIN4_Msk (0x1UL << GPIO_IN_PIN4_Pos) /*!< Bit mask of PIN4 field. */
#define GPIO_IN_PIN4_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN4_High (1UL) /*!< Pin input is high */

/* Bit 3 : Pin 3 */
#define GPIO_IN_PIN3_Pos (3UL) /*!< Position of PIN3 field. */
#define GPIO_IN_PIN3_Msk (0x1UL << GPIO_IN_PIN3_Pos) /*!< Bit mask of PIN3 field. */
#define GPIO_IN_PIN3_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN3_High (1UL) /*!< Pin input is high */

/* Bit 2 : Pin 2 */
#define GPIO_IN_PIN2_Pos (2UL) /*!< Position of PIN2 field. */
#define GPIO_IN_PIN2_Msk (0x1UL << GPIO_IN_PIN2_Pos) /*!< Bit mask of PIN2 field. */
#define GPIO_IN_PIN2_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN2_High (1UL) /*!< Pin input is high */

/* Bit 1 : Pin 1 */
#define GPIO_IN_PIN1_Pos (1UL) /*!< Position of PIN1 field. */
#define GPIO_IN_PIN1_Msk (0x1UL << GPIO_IN_PIN1_Pos) /*!< Bit mask of PIN1 field. */
#define GPIO_IN_PIN1_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN1_High (1UL) /*!< Pin input is high */

/* Bit 0 : Pin 0 */
#define GPIO_IN_PIN0_Pos (0UL) /*!< Position of PIN0 field. */
#define GPIO_IN_PIN0_Msk (0x1UL << GPIO_IN_PIN0_Pos) /*!< Bit mask of PIN0 field. */
#define GPIO_IN_PIN0_Low (0UL) /*!< Pin input is low */
#define GPIO_IN_PIN0_High (1UL) /*!< Pin input is high */

/* Register: GPIO_DIR */
/* Description: Direction of GPIO pins */

/* Bit 31 : Pin 31 */
#define GPIO_DIR_PIN31_Pos (31UL) /*!< Position of PIN31 field. */
#define GPIO_DIR_PIN31_Msk (0x1UL << GPIO_DIR_PIN31_Pos) /*!< Bit mask of PIN31 field. */
#define GPIO_DIR_PIN31_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN31_Output (1UL) /*!< Pin set as output */

/* Bit 30 : Pin 30 */
#define GPIO_DIR_PIN30_Pos (30UL) /*!< Position of PIN30 field. */
#define GPIO_DIR_PIN30_Msk (0x1UL << GPIO_DIR_PIN30_Pos) /*!< Bit mask of PIN30 field. */
#define GPIO_DIR_PIN30_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN30_Output (1UL) /*!< Pin set as output */

/* Bit 29 : Pin 29 */
#define GPIO_DIR_PIN29_Pos (29UL) /*!< Position of PIN29 field. */
#define GPIO_DIR_PIN29_Msk (0x1UL << GPIO_DIR_PIN29_Pos) /*!< Bit mask of PIN29 field. */
#define GPIO_DIR_PIN29_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN29_Output (1UL) /*!< Pin set as output */

/* Bit 28 : Pin 28 */
#define GPIO_DIR_PIN28_Pos (28UL) /*!< Position of PIN28 field. */
#define GPIO_DIR_PIN28_Msk (0x1UL << GPIO_DIR_PIN28_Pos) /*!< Bit mask of PIN28 field. */
#define GPIO_DIR_PIN28_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN28_Output (1UL) /*!< Pin set as output */

/* Bit 27 : Pin 27 */
#define GPIO_DIR_PIN27_Pos (27UL) /*!< Position of PIN27 field. */
#define GPIO_DIR_PIN27_Msk (0x1UL << GPIO_DIR_PIN27_Pos) /*!< Bit mask of PIN27 field. */
#define GPIO_DIR_PIN27_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN27_Output (1UL) /*!< Pin set as output */

/* Bit 26 : Pin 26 */
#define GPIO_DIR_PIN26_Pos (26UL) /*!< Position of PIN26 field. */
#define GPIO_DIR_PIN26_Msk (0x1UL << GPIO_DIR_PIN26_Pos) /*!< Bit mask of PIN26 field. */
#define GPIO_DIR_PIN26_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN26_Output (1UL) /*!< Pin set as output */

/* Bit 25 : Pin 25 */
#define GPIO_DIR_PIN25_Pos (25UL) /*!< Position of PIN25 field. */
#define GPIO_DIR_PIN25_Msk (0x1UL << GPIO_DIR_PIN25_Pos) /*!< Bit mask of PIN25 field. */
#define GPIO_DIR_PIN25_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN25_Output (1UL) /*!< Pin set as output */

/* Bit 24 : Pin 24 */
#define GPIO_DIR_PIN24_Pos (24UL) /*!< Position of PIN24 field. */
#define GPIO_DIR_PIN24_Msk (0x1UL << GPIO_DIR_PIN24_Pos) /*!< Bit mask of PIN24 field. */
#define GPIO_DIR_PIN24_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN24_Output (1UL) /*!< Pin set as output */

/* Bit 23 : Pin 23 */
#define GPIO_DIR_PIN23_Pos (23UL) /*!< Position of PIN23 field. */
#define GPIO_DIR_PIN23_Msk (0x1UL << GPIO_DIR_PIN23_Pos) /*!< Bit mask of PIN23 field. */
#define GPIO_DIR_PIN23_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN23_Output (1UL) /*!< Pin set as output */

/* Bit 22 : Pin 22 */
#define GPIO_DIR_PIN22_Pos (22UL) /*!< Position of PIN22 field. */
#define GPIO_DIR_PIN22_Msk (0x1UL << GPIO_DIR_PIN22_Pos) /*!< Bit mask of PIN22 field. */
#define GPIO_DIR_PIN22_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN22_Output (1UL) /*!< Pin set as output */

/* Bit 21 : Pin 21 */
#define GPIO_DIR_PIN21_Pos (21UL) /*!< Position of PIN21 field. */
#define GPIO_DIR_PIN21_Msk (0x1UL << GPIO_DIR_PIN21_Pos) /*!< Bit mask of PIN21 field. */
#define GPIO_DIR_PIN21_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN21_Output (1UL) /*!< Pin set as output */

/* Bit 20 : Pin 20 */
#define GPIO_DIR_PIN20_Pos (20UL) /*!< Position of PIN20 field. */
#define GPIO_DIR_PIN20_Msk (0x1UL << GPIO_DIR_PIN20_Pos) /*!< Bit mask of PIN20 field. */
#define GPIO_DIR_PIN20_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN20_Output (1UL) /*!< Pin set as output */

/* Bit 19 : Pin 19 */
#define GPIO_DIR_PIN19_Pos (19UL) /*!< Position of PIN19 field. */
#define GPIO_DIR_PIN19_Msk (0x1UL << GPIO_DIR_PIN19_Pos) /*!< Bit mask of PIN19 field. */
#define GPIO_DIR_PIN19_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN19_Output (1UL) /*!< Pin set as output */

/* Bit 18 : Pin 18 */
#define GPIO_DIR_PIN18_Pos (18UL) /*!< Position of PIN18 field. */
#define GPIO_DIR_PIN18_Msk (0x1UL << GPIO_DIR_PIN18_Pos) /*!< Bit mask of PIN18 field. */
#define GPIO_DIR_PIN18_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN18_Output (1UL) /*!< Pin set as output */

/* Bit 17 : Pin 17 */
#define GPIO_DIR_PIN17_Pos (17UL) /*!< Position of PIN17 field. */
#define GPIO_DIR_PIN17_Msk (0x1UL << GPIO_DIR_PIN17_Pos) /*!< Bit mask of PIN17 field. */
#define GPIO_DIR_PIN17_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN17_Output (1UL) /*!< Pin set as output */

/* Bit 16 : Pin 16 */
#define GPIO_DIR_PIN16_Pos (16UL) /*!< Position of PIN16 field. */
#define GPIO_DIR_PIN16_Msk (0x1UL << GPIO_DIR_PIN16_Pos) /*!< Bit mask of PIN16 field. */
#define GPIO_DIR_PIN16_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN16_Output (1UL) /*!< Pin set as output */

/* Bit 15 : Pin 15 */
#define GPIO_DIR_PIN15_Pos (15UL) /*!< Position of PIN15 field. */
#define GPIO_DIR_PIN15_Msk (0x1UL << GPIO_DIR_PIN15_Pos) /*!< Bit mask of PIN15 field. */
#define GPIO_DIR_PIN15_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN15_Output (1UL) /*!< Pin set as output */

/* Bit 14 : Pin 14 */
#define GPIO_DIR_PIN14_Pos (14UL) /*!< Position of PIN14 field. */
#define GPIO_DIR_PIN14_Msk (0x1UL << GPIO_DIR_PIN14_Pos) /*!< Bit mask of PIN14 field. */
#define GPIO_DIR_PIN14_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN14_Output (1UL) /*!< Pin set as output */

/* Bit 13 : Pin 13 */
#define GPIO_DIR_PIN13_Pos (13UL) /*!< Position of PIN13 field. */
#define GPIO_DIR_PIN13_Msk (0x1UL << GPIO_DIR_PIN13_Pos) /*!< Bit mask of PIN13 field. */
#define GPIO_DIR_PIN13_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN13_Output (1UL) /*!< Pin set as output */

/* Bit 12 : Pin 12 */
#define GPIO_DIR_PIN12_Pos (12UL) /*!< Position of PIN12 field. */
#define GPIO_DIR_PIN12_Msk (0x1UL << GPIO_DIR_PIN12_Pos) /*!< Bit mask of PIN12 field. */
#define GPIO_DIR_PIN12_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN12_Output (1UL) /*!< Pin set as output */

/* Bit 11 : Pin 11 */
#define GPIO_DIR_PIN11_Pos (11UL) /*!< Position of PIN11 field. */
#define GPIO_DIR_PIN11_Msk (0x1UL << GPIO_DIR_PIN11_Pos) /*!< Bit mask of PIN11 field. */
#define GPIO_DIR_PIN11_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN11_Output (1UL) /*!< Pin set as output */

/* Bit 10 : Pin 10 */
#define GPIO_DIR_PIN10_Pos (10UL) /*!< Position of PIN10 field. */
#define GPIO_DIR_PIN10_Msk (0x1UL << GPIO_DIR_PIN10_Pos) /*!< Bit mask of PIN10 field. */
#define GPIO_DIR_PIN10_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN10_Output (1UL) /*!< Pin set as output */

/* Bit 9 : Pin 9 */
#define GPIO_DIR_PIN9_Pos (9UL) /*!< Position of PIN9 field. */
#define GPIO_DIR_PIN9_Msk (0x1UL << GPIO_DIR_PIN9_Pos) /*!< Bit mask of PIN9 field. */
#define GPIO_DIR_PIN9_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN9_Output (1UL) /*!< Pin set as output */

/* Bit 8 : Pin 8 */
#define GPIO_DIR_PIN8_Pos (8UL) /*!< Position of PIN8 field. */
#define GPIO_DIR_PIN8_Msk (0x1UL << GPIO_DIR_PIN8_Pos) /*!< Bit mask of PIN8 field. */
#define GPIO_DIR_PIN8_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN8_Output (1UL) /*!< Pin set as output */

/* Bit 7 : Pin 7 */
#define GPIO_DIR_PIN7_Pos (7UL) /*!< Position of PIN7 field. */
#define GPIO_DIR_PIN7_Msk (0x1UL << GPIO_DIR_PIN7_Pos) /*!< Bit mask of PIN7 field. */
#define GPIO_DIR_PIN7_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN7_Output (1UL) /*!< Pin set as output */

/* Bit 6 : Pin 6 */
#define GPIO_DIR_PIN6_Pos (6UL) /*!< Position of PIN6 field. */
#define GPIO_DIR_PIN6_Msk (0x1UL << GPIO_DIR_PIN6_Pos) /*!< Bit mask of PIN6 field. */
#define GPIO_DIR_PIN6_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN6_Output (1UL) /*!< Pin set as output */

/* Bit 5 : Pin 5 */
#define GPIO_DIR_PIN5_Pos (5UL) /*!< Position of PIN5 field. */
#define GPIO_DIR_PIN5_Msk (0x1UL << GPIO_DIR_PIN5_Pos) /*!< Bit mask of PIN5 field. */
#define GPIO_DIR_PIN5_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN5_Output (1UL) /*!< Pin set as output */

/* Bit 4 : Pin 4 */
#define GPIO_DIR_PIN4_Pos (4UL) /*!< Position of PIN4 field. */
#define GPIO_DIR_PIN4_Msk (0x1UL << GPIO_DIR_PIN4_Pos) /*!< Bit mask of PIN4 field. */
#define GPIO_DIR_PIN4_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN4_Output (1UL) /*!< Pin set as output */

/* Bit 3 : Pin 3 */
#define GPIO_DIR_PIN3_Pos (3UL) /*!< Position of PIN3 field. */
#define GPIO_DIR_PIN3_Msk (0x1UL << GPIO_DIR_PIN3_Pos) /*!< Bit mask of PIN3 field. */
#define GPIO_DIR_PIN3_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN3_Output (1UL) /*!< Pin set as output */

/* Bit 2 : Pin 2 */
#define GPIO_DIR_PIN2_Pos (2UL) /*!< Position of PIN2 field. */
#define GPIO_DIR_PIN2_Msk (0x1UL << GPIO_DIR_PIN2_Pos) /*!< Bit mask of PIN2 field. */
#define GPIO_DIR_PIN2_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN2_Output (1UL) /*!< Pin set as output */

/* Bit 1 : Pin 1 */
#define GPIO_DIR_PIN1_Pos (1UL) /*!< Position of PIN1 field. */
#define GPIO_DIR_PIN1_Msk (0x1UL << GPIO_DIR_PIN1_Pos) /*!< Bit mask of PIN1 field. */
#define GPIO_DIR_PIN1_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN1_Output (1UL) /*!< Pin set as output */

/* Bit 0 : Pin 0 */
#define GPIO_DIR_PIN0_Pos (0UL) /*!< Position of PIN0 field. */
#define GPIO_DIR_PIN0_Msk (0x1UL << GPIO_DIR_PIN0_Pos) /*!< Bit mask of PIN0 field. */
#define GPIO_DIR_PIN0_Input (0UL) /*!< Pin set as input */
#define GPIO_DIR_PIN0_Output (1UL) /*!< Pin set as output */

/* Register: GPIO_DIRSET */
/* Description: DIR set register */

/* Bit 31 : Set as output pin 31 */
#define GPIO_DIRSET_PIN31_Pos (31UL) /*!< Position of PIN31 field. */
#define GPIO_DIRSET_PIN31_Msk (0x1UL << GPIO_DIRSET_PIN31_Pos) /*!< Bit mask of PIN31 field. */
#define GPIO_DIRSET_PIN31_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN31_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN31_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 30 : Set as output pin 30 */
#define GPIO_DIRSET_PIN30_Pos (30UL) /*!< Position of PIN30 field. */
#define GPIO_DIRSET_PIN30_Msk (0x1UL << GPIO_DIRSET_PIN30_Pos) /*!< Bit mask of PIN30 field. */
#define GPIO_DIRSET_PIN30_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN30_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN30_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 29 : Set as output pin 29 */
#define GPIO_DIRSET_PIN29_Pos (29UL) /*!< Position of PIN29 field. */
#define GPIO_DIRSET_PIN29_Msk (0x1UL << GPIO_DIRSET_PIN29_Pos) /*!< Bit mask of PIN29 field. */
#define GPIO_DIRSET_PIN29_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN29_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN29_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 28 : Set as output pin 28 */
#define GPIO_DIRSET_PIN28_Pos (28UL) /*!< Position of PIN28 field. */
#define GPIO_DIRSET_PIN28_Msk (0x1UL << GPIO_DIRSET_PIN28_Pos) /*!< Bit mask of PIN28 field. */
#define GPIO_DIRSET_PIN28_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN28_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN28_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 27 : Set as output pin 27 */
#define GPIO_DIRSET_PIN27_Pos (27UL) /*!< Position of PIN27 field. */
#define GPIO_DIRSET_PIN27_Msk (0x1UL << GPIO_DIRSET_PIN27_Pos) /*!< Bit mask of PIN27 field. */
#define GPIO_DIRSET_PIN27_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN27_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN27_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 26 : Set as output pin 26 */
#define GPIO_DIRSET_PIN26_Pos (26UL) /*!< Position of PIN26 field. */
#define GPIO_DIRSET_PIN26_Msk (0x1UL << GPIO_DIRSET_PIN26_Pos) /*!< Bit mask of PIN26 field. */
#define GPIO_DIRSET_PIN26_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN26_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN26_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 25 : Set as output pin 25 */
#define GPIO_DIRSET_PIN25_Pos (25UL) /*!< Position of PIN25 field. */
#define GPIO_DIRSET_PIN25_Msk (0x1UL << GPIO_DIRSET_PIN25_Pos) /*!< Bit mask of PIN25 field. */
#define GPIO_DIRSET_PIN25_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN25_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN25_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 24 : Set as output pin 24 */
#define GPIO_DIRSET_PIN24_Pos (24UL) /*!< Position of PIN24 field. */
#define GPIO_DIRSET_PIN24_Msk (0x1UL << GPIO_DIRSET_PIN24_Pos) /*!< Bit mask of PIN24 field. */
#define GPIO_DIRSET_PIN24_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN24_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN24_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 23 : Set as output pin 23 */
#define GPIO_DIRSET_PIN23_Pos (23UL) /*!< Position of PIN23 field. */
#define GPIO_DIRSET_PIN23_Msk (0x1UL << GPIO_DIRSET_PIN23_Pos) /*!< Bit mask of PIN23 field. */
#define GPIO_DIRSET_PIN23_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN23_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN23_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 22 : Set as output pin 22 */
#define GPIO_DIRSET_PIN22_Pos (22UL) /*!< Position of PIN22 field. */
#define GPIO_DIRSET_PIN22_Msk (0x1UL << GPIO_DIRSET_PIN22_Pos) /*!< Bit mask of PIN22 field. */
#define GPIO_DIRSET_PIN22_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN22_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN22_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 21 : Set as output pin 21 */
#define GPIO_DIRSET_PIN21_Pos (21UL) /*!< Position of PIN21 field. */
#define GPIO_DIRSET_PIN21_Msk (0x1UL << GPIO_DIRSET_PIN21_Pos) /*!< Bit mask of PIN21 field. */
#define GPIO_DIRSET_PIN21_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN21_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN21_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 20 : Set as output pin 20 */
#define GPIO_DIRSET_PIN20_Pos (20UL) /*!< Position of PIN20 field. */
#define GPIO_DIRSET_PIN20_Msk (0x1UL << GPIO_DIRSET_PIN20_Pos) /*!< Bit mask of PIN20 field. */
#define GPIO_DIRSET_PIN20_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN20_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN20_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 19 : Set as output pin 19 */
#define GPIO_DIRSET_PIN19_Pos (19UL) /*!< Position of PIN19 field. */
#define GPIO_DIRSET_PIN19_Msk (0x1UL << GPIO_DIRSET_PIN19_Pos) /*!< Bit mask of PIN19 field. */
#define GPIO_DIRSET_PIN19_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN19_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN19_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 18 : Set as output pin 18 */
#define GPIO_DIRSET_PIN18_Pos (18UL) /*!< Position of PIN18 field. */
#define GPIO_DIRSET_PIN18_Msk (0x1UL << GPIO_DIRSET_PIN18_Pos) /*!< Bit mask of PIN18 field. */
#define GPIO_DIRSET_PIN18_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN18_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN18_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 17 : Set as output pin 17 */
#define GPIO_DIRSET_PIN17_Pos (17UL) /*!< Position of PIN17 field. */
#define GPIO_DIRSET_PIN17_Msk (0x1UL << GPIO_DIRSET_PIN17_Pos) /*!< Bit mask of PIN17 field. */
#define GPIO_DIRSET_PIN17_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN17_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN17_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 16 : Set as output pin 16 */
#define GPIO_DIRSET_PIN16_Pos (16UL) /*!< Position of PIN16 field. */
#define GPIO_DIRSET_PIN16_Msk (0x1UL << GPIO_DIRSET_PIN16_Pos) /*!< Bit mask of PIN16 field. */
#define GPIO_DIRSET_PIN16_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN16_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN16_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 15 : Set as output pin 15 */
#define GPIO_DIRSET_PIN15_Pos (15UL) /*!< Position of PIN15 field. */
#define GPIO_DIRSET_PIN15_Msk (0x1UL << GPIO_DIRSET_PIN15_Pos) /*!< Bit mask of PIN15 field. */
#define GPIO_DIRSET_PIN15_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN15_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN15_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 14 : Set as output pin 14 */
#define GPIO_DIRSET_PIN14_Pos (14UL) /*!< Position of PIN14 field. */
#define GPIO_DIRSET_PIN14_Msk (0x1UL << GPIO_DIRSET_PIN14_Pos) /*!< Bit mask of PIN14 field. */
#define GPIO_DIRSET_PIN14_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN14_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN14_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 13 : Set as output pin 13 */
#define GPIO_DIRSET_PIN13_Pos (13UL) /*!< Position of PIN13 field. */
#define GPIO_DIRSET_PIN13_Msk (0x1UL << GPIO_DIRSET_PIN13_Pos) /*!< Bit mask of PIN13 field. */
#define GPIO_DIRSET_PIN13_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN13_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN13_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 12 : Set as output pin 12 */
#define GPIO_DIRSET_PIN12_Pos (12UL) /*!< Position of PIN12 field. */
#define GPIO_DIRSET_PIN12_Msk (0x1UL << GPIO_DIRSET_PIN12_Pos) /*!< Bit mask of PIN12 field. */
#define GPIO_DIRSET_PIN12_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN12_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN12_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 11 : Set as output pin 11 */
#define GPIO_DIRSET_PIN11_Pos (11UL) /*!< Position of PIN11 field. */
#define GPIO_DIRSET_PIN11_Msk (0x1UL << GPIO_DIRSET_PIN11_Pos) /*!< Bit mask of PIN11 field. */
#define GPIO_DIRSET_PIN11_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN11_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN11_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 10 : Set as output pin 10 */
#define GPIO_DIRSET_PIN10_Pos (10UL) /*!< Position of PIN10 field. */
#define GPIO_DIRSET_PIN10_Msk (0x1UL << GPIO_DIRSET_PIN10_Pos) /*!< Bit mask of PIN10 field. */
#define GPIO_DIRSET_PIN10_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN10_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN10_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 9 : Set as output pin 9 */
#define GPIO_DIRSET_PIN9_Pos (9UL) /*!< Position of PIN9 field. */
#define GPIO_DIRSET_PIN9_Msk (0x1UL << GPIO_DIRSET_PIN9_Pos) /*!< Bit mask of PIN9 field. */
#define GPIO_DIRSET_PIN9_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN9_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN9_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 8 : Set as output pin 8 */
#define GPIO_DIRSET_PIN8_Pos (8UL) /*!< Position of PIN8 field. */
#define GPIO_DIRSET_PIN8_Msk (0x1UL << GPIO_DIRSET_PIN8_Pos) /*!< Bit mask of PIN8 field. */
#define GPIO_DIRSET_PIN8_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN8_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN8_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 7 : Set as output pin 7 */
#define GPIO_DIRSET_PIN7_Pos (7UL) /*!< Position of PIN7 field. */
#define GPIO_DIRSET_PIN7_Msk (0x1UL << GPIO_DIRSET_PIN7_Pos) /*!< Bit mask of PIN7 field. */
#define GPIO_DIRSET_PIN7_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN7_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN7_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 6 : Set as output pin 6 */
#define GPIO_DIRSET_PIN6_Pos (6UL) /*!< Position of PIN6 field. */
#define GPIO_DIRSET_PIN6_Msk (0x1UL << GPIO_DIRSET_PIN6_Pos) /*!< Bit mask of PIN6 field. */
#define GPIO_DIRSET_PIN6_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN6_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN6_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 5 : Set as output pin 5 */
#define GPIO_DIRSET_PIN5_Pos (5UL) /*!< Position of PIN5 field. */
#define GPIO_DIRSET_PIN5_Msk (0x1UL << GPIO_DIRSET_PIN5_Pos) /*!< Bit mask of PIN5 field. */
#define GPIO_DIRSET_PIN5_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN5_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN5_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 4 : Set as output pin 4 */
#define GPIO_DIRSET_PIN4_Pos (4UL) /*!< Position of PIN4 field. */
#define GPIO_DIRSET_PIN4_Msk (0x1UL << GPIO_DIRSET_PIN4_Pos) /*!< Bit mask of PIN4 field. */
#define GPIO_DIRSET_PIN4_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN4_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN4_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 3 : Set as output pin 3 */
#define GPIO_DIRSET_PIN3_Pos (3UL) /*!< Position of PIN3 field. */
#define GPIO_DIRSET_PIN3_Msk (0x1UL << GPIO_DIRSET_PIN3_Pos) /*!< Bit mask of PIN3 field. */
#define GPIO_DIRSET_PIN3_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN3_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN3_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 2 : Set as output pin 2 */
#define GPIO_DIRSET_PIN2_Pos (2UL) /*!< Position of PIN2 field. */
#define GPIO_DIRSET_PIN2_Msk (0x1UL << GPIO_DIRSET_PIN2_Pos) /*!< Bit mask of PIN2 field. */
#define GPIO_DIRSET_PIN2_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN2_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN2_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 1 : Set as output pin 1 */
#define GPIO_DIRSET_PIN1_Pos (1UL) /*!< Position of PIN1 field. */
#define GPIO_DIRSET_PIN1_Msk (0x1UL << GPIO_DIRSET_PIN1_Pos) /*!< Bit mask of PIN1 field. */
#define GPIO_DIRSET_PIN1_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN1_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN1_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Bit 0 : Set as output pin 0 */
#define GPIO_DIRSET_PIN0_Pos (0UL) /*!< Position of PIN0 field. */
#define GPIO_DIRSET_PIN0_Msk (0x1UL << GPIO_DIRSET_PIN0_Pos) /*!< Bit mask of PIN0 field. */
#define GPIO_DIRSET_PIN0_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRSET_PIN0_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRSET_PIN0_Set (1UL) /*!< Write: writing a '1' sets pin to output; writing a '0' has no effect */

/* Register: GPIO_DIRCLR */
/* Description: DIR clear register */

/* Bit 31 : Set as input pin 31 */
#define GPIO_DIRCLR_PIN31_Pos (31UL) /*!< Position of PIN31 field. */
#define GPIO_DIRCLR_PIN31_Msk (0x1UL << GPIO_DIRCLR_PIN31_Pos) /*!< Bit mask of PIN31 field. */
#define GPIO_DIRCLR_PIN31_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN31_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN31_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 30 : Set as input pin 30 */
#define GPIO_DIRCLR_PIN30_Pos (30UL) /*!< Position of PIN30 field. */
#define GPIO_DIRCLR_PIN30_Msk (0x1UL << GPIO_DIRCLR_PIN30_Pos) /*!< Bit mask of PIN30 field. */
#define GPIO_DIRCLR_PIN30_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN30_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN30_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 29 : Set as input pin 29 */
#define GPIO_DIRCLR_PIN29_Pos (29UL) /*!< Position of PIN29 field. */
#define GPIO_DIRCLR_PIN29_Msk (0x1UL << GPIO_DIRCLR_PIN29_Pos) /*!< Bit mask of PIN29 field. */
#define GPIO_DIRCLR_PIN29_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN29_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN29_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 28 : Set as input pin 28 */
#define GPIO_DIRCLR_PIN28_Pos (28UL) /*!< Position of PIN28 field. */
#define GPIO_DIRCLR_PIN28_Msk (0x1UL << GPIO_DIRCLR_PIN28_Pos) /*!< Bit mask of PIN28 field. */
#define GPIO_DIRCLR_PIN28_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN28_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN28_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 27 : Set as input pin 27 */
#define GPIO_DIRCLR_PIN27_Pos (27UL) /*!< Position of PIN27 field. */
#define GPIO_DIRCLR_PIN27_Msk (0x1UL << GPIO_DIRCLR_PIN27_Pos) /*!< Bit mask of PIN27 field. */
#define GPIO_DIRCLR_PIN27_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN27_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN27_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 26 : Set as input pin 26 */
#define GPIO_DIRCLR_PIN26_Pos (26UL) /*!< Position of PIN26 field. */
#define GPIO_DIRCLR_PIN26_Msk (0x1UL << GPIO_DIRCLR_PIN26_Pos) /*!< Bit mask of PIN26 field. */
#define GPIO_DIRCLR_PIN26_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN26_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN26_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 25 : Set as input pin 25 */
#define GPIO_DIRCLR_PIN25_Pos (25UL) /*!< Position of PIN25 field. */
#define GPIO_DIRCLR_PIN25_Msk (0x1UL << GPIO_DIRCLR_PIN25_Pos) /*!< Bit mask of PIN25 field. */
#define GPIO_DIRCLR_PIN25_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN25_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN25_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 24 : Set as input pin 24 */
#define GPIO_DIRCLR_PIN24_Pos (24UL) /*!< Position of PIN24 field. */
#define GPIO_DIRCLR_PIN24_Msk (0x1UL << GPIO_DIRCLR_PIN24_Pos) /*!< Bit mask of PIN24 field. */
#define GPIO_DIRCLR_PIN24_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN24_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN24_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 23 : Set as input pin 23 */
#define GPIO_DIRCLR_PIN23_Pos (23UL) /*!< Position of PIN23 field. */
#define GPIO_DIRCLR_PIN23_Msk (0x1UL << GPIO_DIRCLR_PIN23_Pos) /*!< Bit mask of PIN23 field. */
#define GPIO_DIRCLR_PIN23_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN23_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN23_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 22 : Set as input pin 22 */
#define GPIO_DIRCLR_PIN22_Pos (22UL) /*!< Position of PIN22 field. */
#define GPIO_DIRCLR_PIN22_Msk (0x1UL << GPIO_DIRCLR_PIN22_Pos) /*!< Bit mask of PIN22 field. */
#define GPIO_DIRCLR_PIN22_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN22_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN22_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 21 : Set as input pin 21 */
#define GPIO_DIRCLR_PIN21_Pos (21UL) /*!< Position of PIN21 field. */
#define GPIO_DIRCLR_PIN21_Msk (0x1UL << GPIO_DIRCLR_PIN21_Pos) /*!< Bit mask of PIN21 field. */
#define GPIO_DIRCLR_PIN21_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN21_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN21_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 20 : Set as input pin 20 */
#define GPIO_DIRCLR_PIN20_Pos (20UL) /*!< Position of PIN20 field. */
#define GPIO_DIRCLR_PIN20_Msk (0x1UL << GPIO_DIRCLR_PIN20_Pos) /*!< Bit mask of PIN20 field. */
#define GPIO_DIRCLR_PIN20_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN20_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN20_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 19 : Set as input pin 19 */
#define GPIO_DIRCLR_PIN19_Pos (19UL) /*!< Position of PIN19 field. */
#define GPIO_DIRCLR_PIN19_Msk (0x1UL << GPIO_DIRCLR_PIN19_Pos) /*!< Bit mask of PIN19 field. */
#define GPIO_DIRCLR_PIN19_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN19_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN19_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 18 : Set as input pin 18 */
#define GPIO_DIRCLR_PIN18_Pos (18UL) /*!< Position of PIN18 field. */
#define GPIO_DIRCLR_PIN18_Msk (0x1UL << GPIO_DIRCLR_PIN18_Pos) /*!< Bit mask of PIN18 field. */
#define GPIO_DIRCLR_PIN18_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN18_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN18_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 17 : Set as input pin 17 */
#define GPIO_DIRCLR_PIN17_Pos (17UL) /*!< Position of PIN17 field. */
#define GPIO_DIRCLR_PIN17_Msk (0x1UL << GPIO_DIRCLR_PIN17_Pos) /*!< Bit mask of PIN17 field. */
#define GPIO_DIRCLR_PIN17_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN17_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN17_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 16 : Set as input pin 16 */
#define GPIO_DIRCLR_PIN16_Pos (16UL) /*!< Position of PIN16 field. */
#define GPIO_DIRCLR_PIN16_Msk (0x1UL << GPIO_DIRCLR_PIN16_Pos) /*!< Bit mask of PIN16 field. */
#define GPIO_DIRCLR_PIN16_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN16_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN16_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 15 : Set as input pin 15 */
#define GPIO_DIRCLR_PIN15_Pos (15UL) /*!< Position of PIN15 field. */
#define GPIO_DIRCLR_PIN15_Msk (0x1UL << GPIO_DIRCLR_PIN15_Pos) /*!< Bit mask of PIN15 field. */
#define GPIO_DIRCLR_PIN15_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN15_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN15_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 14 : Set as input pin 14 */
#define GPIO_DIRCLR_PIN14_Pos (14UL) /*!< Position of PIN14 field. */
#define GPIO_DIRCLR_PIN14_Msk (0x1UL << GPIO_DIRCLR_PIN14_Pos) /*!< Bit mask of PIN14 field. */
#define GPIO_DIRCLR_PIN14_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN14_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN14_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 13 : Set as input pin 13 */
#define GPIO_DIRCLR_PIN13_Pos (13UL) /*!< Position of PIN13 field. */
#define GPIO_DIRCLR_PIN13_Msk (0x1UL << GPIO_DIRCLR_PIN13_Pos) /*!< Bit mask of PIN13 field. */
#define GPIO_DIRCLR_PIN13_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN13_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN13_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 12 : Set as input pin 12 */
#define GPIO_DIRCLR_PIN12_Pos (12UL) /*!< Position of PIN12 field. */
#define GPIO_DIRCLR_PIN12_Msk (0x1UL << GPIO_DIRCLR_PIN12_Pos) /*!< Bit mask of PIN12 field. */
#define GPIO_DIRCLR_PIN12_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN12_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN12_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 11 : Set as input pin 11 */
#define GPIO_DIRCLR_PIN11_Pos (11UL) /*!< Position of PIN11 field. */
#define GPIO_DIRCLR_PIN11_Msk (0x1UL << GPIO_DIRCLR_PIN11_Pos) /*!< Bit mask of PIN11 field. */
#define GPIO_DIRCLR_PIN11_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN11_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN11_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 10 : Set as input pin 10 */
#define GPIO_DIRCLR_PIN10_Pos (10UL) /*!< Position of PIN10 field. */
#define GPIO_DIRCLR_PIN10_Msk (0x1UL << GPIO_DIRCLR_PIN10_Pos) /*!< Bit mask of PIN10 field. */
#define GPIO_DIRCLR_PIN10_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN10_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN10_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 9 : Set as input pin 9 */
#define GPIO_DIRCLR_PIN9_Pos (9UL) /*!< Position of PIN9 field. */
#define GPIO_DIRCLR_PIN9_Msk (0x1UL << GPIO_DIRCLR_PIN9_Pos) /*!< Bit mask of PIN9 field. */
#define GPIO_DIRCLR_PIN9_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN9_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN9_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 8 : Set as input pin 8 */
#define GPIO_DIRCLR_PIN8_Pos (8UL) /*!< Position of PIN8 field. */
#define GPIO_DIRCLR_PIN8_Msk (0x1UL << GPIO_DIRCLR_PIN8_Pos) /*!< Bit mask of PIN8 field. */
#define GPIO_DIRCLR_PIN8_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN8_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN8_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 7 : Set as input pin 7 */
#define GPIO_DIRCLR_PIN7_Pos (7UL) /*!< Position of PIN7 field. */
#define GPIO_DIRCLR_PIN7_Msk (0x1UL << GPIO_DIRCLR_PIN7_Pos) /*!< Bit mask of PIN7 field. */
#define GPIO_DIRCLR_PIN7_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN7_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN7_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 6 : Set as input pin 6 */
#define GPIO_DIRCLR_PIN6_Pos (6UL) /*!< Position of PIN6 field. */
#define GPIO_DIRCLR_PIN6_Msk (0x1UL << GPIO_DIRCLR_PIN6_Pos) /*!< Bit mask of PIN6 field. */
#define GPIO_DIRCLR_PIN6_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN6_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN6_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 5 : Set as input pin 5 */
#define GPIO_DIRCLR_PIN5_Pos (5UL) /*!< Position of PIN5 field. */
#define GPIO_DIRCLR_PIN5_Msk (0x1UL << GPIO_DIRCLR_PIN5_Pos) /*!< Bit mask of PIN5 field. */
#define GPIO_DIRCLR_PIN5_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN5_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN5_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 4 : Set as input pin 4 */
#define GPIO_DIRCLR_PIN4_Pos (4UL) /*!< Position of PIN4 field. */
#define GPIO_DIRCLR_PIN4_Msk (0x1UL << GPIO_DIRCLR_PIN4_Pos) /*!< Bit mask of PIN4 field. */
#define GPIO_DIRCLR_PIN4_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN4_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN4_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 3 : Set as input pin 3 */
#define GPIO_DIRCLR_PIN3_Pos (3UL) /*!< Position of PIN3 field. */
#define GPIO_DIRCLR_PIN3_Msk (0x1UL << GPIO_DIRCLR_PIN3_Pos) /*!< Bit mask of PIN3 field. */
#define GPIO_DIRCLR_PIN3_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN3_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN3_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 2 : Set as input pin 2 */
#define GPIO_DIRCLR_PIN2_Pos (2UL) /*!< Position of PIN2 field. */
#define GPIO_DIRCLR_PIN2_Msk (0x1UL << GPIO_DIRCLR_PIN2_Pos) /*!< Bit mask of PIN2 field. */
#define GPIO_DIRCLR_PIN2_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN2_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN2_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 1 : Set as input pin 1 */
#define GPIO_DIRCLR_PIN1_Pos (1UL) /*!< Position of PIN1 field. */
#define GPIO_DIRCLR_PIN1_Msk (0x1UL << GPIO_DIRCLR_PIN1_Pos) /*!< Bit mask of PIN1 field. */
#define GPIO_DIRCLR_PIN1_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN1_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN1_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Bit 0 : Set as input pin 0 */
#define GPIO_DIRCLR_PIN0_Pos (0UL) /*!< Position of PIN0 field. */
#define GPIO_DIRCLR_PIN0_Msk (0x1UL << GPIO_DIRCLR_PIN0_Pos) /*!< Bit mask of PIN0 field. */
#define GPIO_DIRCLR_PIN0_Input (0UL) /*!< Read: pin set as input */
#define GPIO_DIRCLR_PIN0_Output (1UL) /*!< Read: pin set as output */
#define GPIO_DIRCLR_PIN0_Clear (1UL) /*!< Write: writing a '1' sets pin to input; writing a '0' has no effect */

/* Register: GPIO_LATCH */
/* Description: Latch register indicating what GPIO pins that have met the criteria set in the PIN_CNF[n].SENSE registers */

/* Bit 31 : Status on whether PIN31 has met criteria set in PIN_CNF31.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN31_Pos (31UL) /*!< Position of PIN31 field. */
#define GPIO_LATCH_PIN31_Msk (0x1UL << GPIO_LATCH_PIN31_Pos) /*!< Bit mask of PIN31 field. */
#define GPIO_LATCH_PIN31_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN31_Latched (1UL) /*!< Criteria has been met */

/* Bit 30 : Status on whether PIN30 has met criteria set in PIN_CNF30.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN30_Pos (30UL) /*!< Position of PIN30 field. */
#define GPIO_LATCH_PIN30_Msk (0x1UL << GPIO_LATCH_PIN30_Pos) /*!< Bit mask of PIN30 field. */
#define GPIO_LATCH_PIN30_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN30_Latched (1UL) /*!< Criteria has been met */

/* Bit 29 : Status on whether PIN29 has met criteria set in PIN_CNF29.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN29_Pos (29UL) /*!< Position of PIN29 field. */
#define GPIO_LATCH_PIN29_Msk (0x1UL << GPIO_LATCH_PIN29_Pos) /*!< Bit mask of PIN29 field. */
#define GPIO_LATCH_PIN29_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN29_Latched (1UL) /*!< Criteria has been met */

/* Bit 28 : Status on whether PIN28 has met criteria set in PIN_CNF28.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN28_Pos (28UL) /*!< Position of PIN28 field. */
#define GPIO_LATCH_PIN28_Msk (0x1UL << GPIO_LATCH_PIN28_Pos) /*!< Bit mask of PIN28 field. */
#define GPIO_LATCH_PIN28_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN28_Latched (1UL) /*!< Criteria has been met */

/* Bit 27 : Status on whether PIN27 has met criteria set in PIN_CNF27.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN27_Pos (27UL) /*!< Position of PIN27 field. */
#define GPIO_LATCH_PIN27_Msk (0x1UL << GPIO_LATCH_PIN27_Pos) /*!< Bit mask of PIN27 field. */
#define GPIO_LATCH_PIN27_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN27_Latched (1UL) /*!< Criteria has been met */

/* Bit 26 : Status on whether PIN26 has met criteria set in PIN_CNF26.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN26_Pos (26UL) /*!< Position of PIN26 field. */
#define GPIO_LATCH_PIN26_Msk (0x1UL << GPIO_LATCH_PIN26_Pos) /*!< Bit mask of PIN26 field. */
#define GPIO_LATCH_PIN26_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN26_Latched (1UL) /*!< Criteria has been met */

/* Bit 25 : Status on whether PIN25 has met criteria set in PIN_CNF25.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN25_Pos (25UL) /*!< Position of PIN25 field. */
#define GPIO_LATCH_PIN25_Msk (0x1UL << GPIO_LATCH_PIN25_Pos) /*!< Bit mask of PIN25 field. */
#define GPIO_LATCH_PIN25_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN25_Latched (1UL) /*!< Criteria has been met */

/* Bit 24 : Status on whether PIN24 has met criteria set in PIN_CNF24.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN24_Pos (24UL) /*!< Position of PIN24 field. */
#define GPIO_LATCH_PIN24_Msk (0x1UL << GPIO_LATCH_PIN24_Pos) /*!< Bit mask of PIN24 field. */
#define GPIO_LATCH_PIN24_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN24_Latched (1UL) /*!< Criteria has been met */

/* Bit 23 : Status on whether PIN23 has met criteria set in PIN_CNF23.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN23_Pos (23UL) /*!< Position of PIN23 field. */
#define GPIO_LATCH_PIN23_Msk (0x1UL << GPIO_LATCH_PIN23_Pos) /*!< Bit mask of PIN23 field. */
#define GPIO_LATCH_PIN23_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN23_Latched (1UL) /*!< Criteria has been met */

/* Bit 22 : Status on whether PIN22 has met criteria set in PIN_CNF22.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN22_Pos (22UL) /*!< Position of PIN22 field. */
#define GPIO_LATCH_PIN22_Msk (0x1UL << GPIO_LATCH_PIN22_Pos) /*!< Bit mask of PIN22 field. */
#define GPIO_LATCH_PIN22_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN22_Latched (1UL) /*!< Criteria has been met */

/* Bit 21 : Status on whether PIN21 has met criteria set in PIN_CNF21.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN21_Pos (21UL) /*!< Position of PIN21 field. */
#define GPIO_LATCH_PIN21_Msk (0x1UL << GPIO_LATCH_PIN21_Pos) /*!< Bit mask of PIN21 field. */
#define GPIO_LATCH_PIN21_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN21_Latched (1UL) /*!< Criteria has been met */

/* Bit 20 : Status on whether PIN20 has met criteria set in PIN_CNF20.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN20_Pos (20UL) /*!< Position of PIN20 field. */
#define GPIO_LATCH_PIN20_Msk (0x1UL << GPIO_LATCH_PIN20_Pos) /*!< Bit mask of PIN20 field. */
#define GPIO_LATCH_PIN20_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN20_Latched (1UL) /*!< Criteria has been met */

/* Bit 19 : Status on whether PIN19 has met criteria set in PIN_CNF19.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN19_Pos (19UL) /*!< Position of PIN19 field. */
#define GPIO_LATCH_PIN19_Msk (0x1UL << GPIO_LATCH_PIN19_Pos) /*!< Bit mask of PIN19 field. */
#define GPIO_LATCH_PIN19_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN19_Latched (1UL) /*!< Criteria has been met */

/* Bit 18 : Status on whether PIN18 has met criteria set in PIN_CNF18.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN18_Pos (18UL) /*!< Position of PIN18 field. */
#define GPIO_LATCH_PIN18_Msk (0x1UL << GPIO_LATCH_PIN18_Pos) /*!< Bit mask of PIN18 field. */
#define GPIO_LATCH_PIN18_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN18_Latched (1UL) /*!< Criteria has been met */

/* Bit 17 : Status on whether PIN17 has met criteria set in PIN_CNF17.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN17_Pos (17UL) /*!< Position of PIN17 field. */
#define GPIO_LATCH_PIN17_Msk (0x1UL << GPIO_LATCH_PIN17_Pos) /*!< Bit mask of PIN17 field. */
#define GPIO_LATCH_PIN17_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN17_Latched (1UL) /*!< Criteria has been met */

/* Bit 16 : Status on whether PIN16 has met criteria set in PIN_CNF16.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN16_Pos (16UL) /*!< Position of PIN16 field. */
#define GPIO_LATCH_PIN16_Msk (0x1UL << GPIO_LATCH_PIN16_Pos) /*!< Bit mask of PIN16 field. */
#define GPIO_LATCH_PIN16_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN16_Latched (1UL) /*!< Criteria has been met */

/* Bit 15 : Status on whether PIN15 has met criteria set in PIN_CNF15.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN15_Pos (15UL) /*!< Position of PIN15 field. */
#define GPIO_LATCH_PIN15_Msk (0x1UL << GPIO_LATCH_PIN15_Pos) /*!< Bit mask of PIN15 field. */
#define GPIO_LATCH_PIN15_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN15_Latched (1UL) /*!< Criteria has been met */

/* Bit 14 : Status on whether PIN14 has met criteria set in PIN_CNF14.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN14_Pos (14UL) /*!< Position of PIN14 field. */
#define GPIO_LATCH_PIN14_Msk (0x1UL << GPIO_LATCH_PIN14_Pos) /*!< Bit mask of PIN14 field. */
#define GPIO_LATCH_PIN14_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN14_Latched (1UL) /*!< Criteria has been met */

/* Bit 13 : Status on whether PIN13 has met criteria set in PIN_CNF13.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN13_Pos (13UL) /*!< Position of PIN13 field. */
#define GPIO_LATCH_PIN13_Msk (0x1UL << GPIO_LATCH_PIN13_Pos) /*!< Bit mask of PIN13 field. */
#define GPIO_LATCH_PIN13_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN13_Latched (1UL) /*!< Criteria has been met */

/* Bit 12 : Status on whether PIN12 has met criteria set in PIN_CNF12.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN12_Pos (12UL) /*!< Position of PIN12 field. */
#define GPIO_LATCH_PIN12_Msk (0x1UL << GPIO_LATCH_PIN12_Pos) /*!< Bit mask of PIN12 field. */
#define GPIO_LATCH_PIN12_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN12_Latched (1UL) /*!< Criteria has been met */

/* Bit 11 : Status on whether PIN11 has met criteria set in PIN_CNF11.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN11_Pos (11UL) /*!< Position of PIN11 field. */
#define GPIO_LATCH_PIN11_Msk (0x1UL << GPIO_LATCH_PIN11_Pos) /*!< Bit mask of PIN11 field. */
#define GPIO_LATCH_PIN11_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN11_Latched (1UL) /*!< Criteria has been met */

/* Bit 10 : Status on whether PIN10 has met criteria set in PIN_CNF10.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN10_Pos (10UL) /*!< Position of PIN10 field. */
#define GPIO_LATCH_PIN10_Msk (0x1UL << GPIO_LATCH_PIN10_Pos) /*!< Bit mask of PIN10 field. */
#define GPIO_LATCH_PIN10_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN10_Latched (1UL) /*!< Criteria has been met */

/* Bit 9 : Status on whether PIN9 has met criteria set in PIN_CNF9.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN9_Pos (9UL) /*!< Position of PIN9 field. */
#define GPIO_LATCH_PIN9_Msk (0x1UL << GPIO_LATCH_PIN9_Pos) /*!< Bit mask of PIN9 field. */
#define GPIO_LATCH_PIN9_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN9_Latched (1UL) /*!< Criteria has been met */

/* Bit 8 : Status on whether PIN8 has met criteria set in PIN_CNF8.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN8_Pos (8UL) /*!< Position of PIN8 field. */
#define GPIO_LATCH_PIN8_Msk (0x1UL << GPIO_LATCH_PIN8_Pos) /*!< Bit mask of PIN8 field. */
#define GPIO_LATCH_PIN8_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN8_Latched (1UL) /*!< Criteria has been met */

/* Bit 7 : Status on whether PIN7 has met criteria set in PIN_CNF7.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN7_Pos (7UL) /*!< Position of PIN7 field. */
#define GPIO_LATCH_PIN7_Msk (0x1UL << GPIO_LATCH_PIN7_Pos) /*!< Bit mask of PIN7 field. */
#define GPIO_LATCH_PIN7_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN7_Latched (1UL) /*!< Criteria has been met */

/* Bit 6 : Status on whether PIN6 has met criteria set in PIN_CNF6.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN6_Pos (6UL) /*!< Position of PIN6 field. */
#define GPIO_LATCH_PIN6_Msk (0x1UL << GPIO_LATCH_PIN6_Pos) /*!< Bit mask of PIN6 field. */
#define GPIO_LATCH_PIN6_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN6_Latched (1UL) /*!< Criteria has been met */

/* Bit 5 : Status on whether PIN5 has met criteria set in PIN_CNF5.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN5_Pos (5UL) /*!< Position of PIN5 field. */
#define GPIO_LATCH_PIN5_Msk (0x1UL << GPIO_LATCH_PIN5_Pos) /*!< Bit mask of PIN5 field. */
#define GPIO_LATCH_PIN5_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN5_Latched (1UL) /*!< Criteria has been met */

/* Bit 4 : Status on whether PIN4 has met criteria set in PIN_CNF4.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN4_Pos (4UL) /*!< Position of PIN4 field. */
#define GPIO_LATCH_PIN4_Msk (0x1UL << GPIO_LATCH_PIN4_Pos) /*!< Bit mask of PIN4 field. */
#define GPIO_LATCH_PIN4_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN4_Latched (1UL) /*!< Criteria has been met */

/* Bit 3 : Status on whether PIN3 has met criteria set in PIN_CNF3.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN3_Pos (3UL) /*!< Position of PIN3 field. */
#define GPIO_LATCH_PIN3_Msk (0x1UL << GPIO_LATCH_PIN3_Pos) /*!< Bit mask of PIN3 field. */
#define GPIO_LATCH_PIN3_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN3_Latched (1UL) /*!< Criteria has been met */

/* Bit 2 : Status on whether PIN2 has met criteria set in PIN_CNF2.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN2_Pos (2UL) /*!< Position of PIN2 field. */
#define GPIO_LATCH_PIN2_Msk (0x1UL << GPIO_LATCH_PIN2_Pos) /*!< Bit mask of PIN2 field. */
#define GPIO_LATCH_PIN2_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN2_Latched (1UL) /*!< Criteria has been met */

/* Bit 1 : Status on whether PIN1 has met criteria set in PIN_CNF1.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN1_Pos (1UL) /*!< Position of PIN1 field. */
#define GPIO_LATCH_PIN1_Msk (0x1UL << GPIO_LATCH_PIN1_Pos) /*!< Bit mask of PIN1 field. */
#define GPIO_LATCH_PIN1_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN1_Latched (1UL) /*!< Criteria has been met */

/* Bit 0 : Status on whether PIN0 has met criteria set in PIN_CNF0.SENSE register. Write '1' to clear. */
#define GPIO_LATCH_PIN0_Pos (0UL) /*!< Position of PIN0 field. */
#define GPIO_LATCH_PIN0_Msk (0x1UL << GPIO_LATCH_PIN0_Pos) /*!< Bit mask of PIN0 field. */
#define GPIO_LATCH_PIN0_NotLatched (0UL) /*!< Criteria has not been met */
#define GPIO_LATCH_PIN0_Latched (1UL) /*!< Criteria has been met */

/* Register: GPIO_DETECTMODE */
/* Description: Select between default DETECT signal behaviour and LDETECT mode */

/* Bit 0 : Select between default DETECT signal behaviour and LDETECT mode */
#define GPIO_DETECTMODE_DETECTMODE_Pos (0UL) /*!< Position of DETECTMODE field. */
#define GPIO_DETECTMODE_DETECTMODE_Msk (0x1UL << GPIO_DETECTMODE_DETECTMODE_Pos) /*!< Bit mask of DETECTMODE field. */
#define GPIO_DETECTMODE_DETECTMODE_Default (0UL) /*!< DETECT directly connected to PIN DETECT signals */
#define GPIO_DETECTMODE_DETECTMODE_LDETECT (1UL) /*!< Use the latched LDETECT behaviour */

/* Register: GPIO_PIN_CNF */
/* Description: Description collection[0]:  Configuration of GPIO pins */

/* Bits 17..16 : Pin sensing mechanism */
#define GPIO_PIN_CNF_SENSE_Pos (16UL) /*!< Position of SENSE field. */
#define GPIO_PIN_CNF_SENSE_Msk (0x3UL << GPIO_PIN_CNF_SENSE_Pos) /*!< Bit mask of SENSE field. */
#define GPIO_PIN_CNF_SENSE_Disabled (0UL) /*!< Disabled */
#define GPIO_PIN_CNF_SENSE_High (2UL) /*!< Sense for high level */
#define GPIO_PIN_CNF_SENSE_Low (3UL) /*!< Sense for low level */

/* Bits 10..8 : Drive configuration */
#define GPIO_PIN_CNF_DRIVE_Pos (8UL) /*!< Position of DRIVE field. */
#define GPIO_PIN_CNF_DRIVE_Msk (0x7UL << GPIO_PIN_CNF_DRIVE_Pos) /*!< Bit mask of DRIVE field. */
#define GPIO_PIN_CNF_DRIVE_S0S1 (0UL) /*!< Standard '0', standard '1' */
#define GPIO_PIN_CNF_DRIVE_H0S1 (1UL) /*!< High drive '0', standard '1' */
#define GPIO_PIN_CNF_DRIVE_S0H1 (2UL) /*!< Standard '0', high drive '1' */
#define GPIO_PIN_CNF_DRIVE_H0H1 (3UL) /*!< High drive '0', high 'drive '1'' */
#define GPIO_PIN_CNF_DRIVE_D0S1 (4UL) /*!< Disconnect '0' standard '1' (normally used for wired-or connections) */
#define GPIO_PIN_CNF_DRIVE_D0H1 (5UL) /*!< Disconnect '0', high drive '1' (normally used for wired-or connections) */
#define GPIO_PIN_CNF_DRIVE_S0D1 (6UL) /*!< Standard '0'. disconnect '1' (normally used for wired-and connections) */
#define GPIO_PIN_CNF_DRIVE_H0D1 (7UL) /*!< High drive '0', disconnect '1' (normally used for wired-and connections) */

/* Bits 3..2 : Pull configuration */
#define GPIO_PIN_CNF_PULL_Pos (2UL) /*!< Position of PULL field. */
#define GPIO_PIN_CNF_PULL_Msk (0x3UL << GPIO_PIN_CNF_PULL_Pos) /*!< Bit mask of PULL field. */
#define GPIO_PIN_CNF_PULL_Disabled (0UL) /*!< No pull */
#define GPIO_PIN_CNF_PULL_Pulldown (1UL) /*!< Pull down on pin */
#define GPIO_PIN_CNF_PULL_Pullup (3UL) /*!< Pull up on pin */

/* Bit 1 : Connect or disconnect input buffer */
#define GPIO_PIN_CNF_INPUT_Pos (1UL) /*!< Position of INPUT field. */
#define GPIO_PIN_CNF_INPUT_Msk (0x1UL << GPIO_PIN_CNF_INPUT_Pos) /*!< Bit mask of INPUT field. */
#define GPIO_PIN_CNF_INPUT_Connect (0UL) /*!< Connect input buffer */
#define GPIO_PIN_CNF_INPUT_Disconnect (1UL) /*!< Disconnect input buffer */

/* Bit 0 : Pin direction. Same physical register as DIR register */
#define GPIO_PIN_CNF_DIR_Pos (0UL) /*!< Position of DIR field. */
#define GPIO_PIN_CNF_DIR_Msk (0x1UL << GPIO_PIN_CNF_DIR_Pos) /*!< Bit mask of DIR field. */
#define GPIO_PIN_CNF_DIR_Input (0UL) /*!< Configure pin as an input pin */
#define GPIO_PIN_CNF_DIR_Output (1UL) /*!< Configure pin as an output pin */


/* Peripheral: PDM */
/* Description: Pulse Density Modulation (Digital Microphone) Interface */

/* Register: PDM_INTEN */
/* Description: Enable or disable interrupt */

/* Bit 2 : Enable or disable interrupt for END event */
#define PDM_INTEN_END_Pos (2UL) /*!< Position of END field. */
#define PDM_INTEN_END_Msk (0x1UL << PDM_INTEN_END_Pos) /*!< Bit mask of END field. */
#define PDM_INTEN_END_Disabled (0UL) /*!< Disable */
#define PDM_INTEN_END_Enabled (1UL) /*!< Enable */

/* Bit 1 : Enable or disable interrupt for STOPPED event */
#define PDM_INTEN_STOPPED_Pos (1UL) /*!< Position of STOPPED field. */
#define PDM_INTEN_STOPPED_Msk (0x1UL << PDM_INTEN_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define PDM_INTEN_STOPPED_Disabled (0UL) /*!< Disable */
#define PDM_INTEN_STOPPED_Enabled (1UL) /*!< Enable */

/* Bit 0 : Enable or disable interrupt for STARTED event */
#define PDM_INTEN_STARTED_Pos (0UL) /*!< Position of STARTED field. */
#define PDM_INTEN_STARTED_Msk (0x1UL << PDM_INTEN_STARTED_Pos) /*!< Bit mask of STARTED field. */
#define PDM_INTEN_STARTED_Disabled (0UL) /*!< Disable */
#define PDM_INTEN_STARTED_Enabled (1UL) /*!< Enable */

/* Register: PDM_INTENSET */
/* Description: Enable interrupt */

/* Bit 2 : Write '1' to Enable interrupt for END event */
#define PDM_INTENSET_END_Pos (2UL) /*!< Position of END field. */
#define PDM_INTENSET_END_Msk (0x1UL << PDM_INTENSET_END_Pos) /*!< Bit mask of END field. */
#define PDM_INTENSET_END_Disabled (0UL) /*!< Read: Disabled */
#define PDM_INTENSET_END_Enabled (1UL) /*!< Read: Enabled */
#define PDM_INTENSET_END_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable interrupt for STOPPED event */
#define PDM_INTENSET_STOPPED_Pos (1UL) /*!< Position of STOPPED field. */
#define PDM_INTENSET_STOPPED_Msk (0x1UL << PDM_INTENSET_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define PDM_INTENSET_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define PDM_INTENSET_STOPPED_Enabled (1UL) /*!< Read: Enabled */
#define PDM_INTENSET_STOPPED_Set (1UL) /*!< Enable */

/* Bit 0 : Write '1' to Enable interrupt for STARTED event */
#define PDM_INTENSET_STARTED_Pos (0UL) /*!< Position of STARTED field. */
#define PDM_INTENSET_STARTED_Msk (0x1UL << PDM_INTENSET_STARTED_Pos) /*!< Bit mask of STARTED field. */
#define PDM_INTENSET_STARTED_Disabled (0UL) /*!< Read: Disabled */
#define PDM_INTENSET_STARTED_Enabled (1UL) /*!< Read: Enabled */
#define PDM_INTENSET_STARTED_Set (1UL) /*!< Enable */

/* Register: PDM_INTENCLR */
/* Description: Disable interrupt */

/* Bit 2 : Write '1' to Disable interrupt for END event */
#define PDM_INTENCLR_END_Pos (2UL) /*!< Position of END field. */
#define PDM_INTENCLR_END_Msk (0x1UL << PDM_INTENCLR_END_Pos) /*!< Bit mask of END field. */
#define PDM_INTENCLR_END_Disabled (0UL) /*!< Read: Disabled */
#define PDM_INTENCLR_END_Enabled (1UL) /*!< Read: Enabled */
#define PDM_INTENCLR_END_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable interrupt for STOPPED event */
#define PDM_INTENCLR_STOPPED_Pos (1UL) /*!< Position of STOPPED field. */
#define PDM_INTENCLR_STOPPED_Msk (0x1UL << PDM_INTENCLR_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define PDM_INTENCLR_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define PDM_INTENCLR_STOPPED_Enabled (1UL) /*!< Read: Enabled */
#define PDM_INTENCLR_STOPPED_Clear (1UL) /*!< Disable */

/* Bit 0 : Write '1' to Disable interrupt for STARTED event */
#define PDM_INTENCLR_STARTED_Pos (0UL) /*!< Position of STARTED field. */
#define PDM_INTENCLR_STARTED_Msk (0x1UL << PDM_INTENCLR_STARTED_Pos) /*!< Bit mask of STARTED field. */
#define PDM_INTENCLR_STARTED_Disabled (0UL) /*!< Read: Disabled */
#define PDM_INTENCLR_STARTED_Enabled (1UL) /*!< Read: Enabled */
#define PDM_INTENCLR_STARTED_Clear (1UL) /*!< Disable */

/* Register: PDM_ENABLE */
/* Description: PDM module enable register */

/* Bit 0 : Enable or disable PDM module */
#define PDM_ENABLE_ENABLE_Pos (0UL) /*!< Position of ENABLE field. */
#define PDM_ENABLE_ENABLE_Msk (0x1UL << PDM_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define PDM_ENABLE_ENABLE_Disabled (0UL) /*!< Disable */
#define PDM_ENABLE_ENABLE_Enabled (1UL) /*!< Enable */

/* Register: PDM_PDMCLKCTRL */
/* Description: PDM clock generator control */

/* Bits 31..0 : PDM_CLK frequency */
#define PDM_PDMCLKCTRL_FREQ_Pos (0UL) /*!< Position of FREQ field. */
#define PDM_PDMCLKCTRL_FREQ_Msk (0xFFFFFFFFUL << PDM_PDMCLKCTRL_FREQ_Pos) /*!< Bit mask of FREQ field. */
#define PDM_PDMCLKCTRL_FREQ_1000K (0x08000000UL) /*!< PDM_CLK = 32 MHz / 32 = 1.000 MHz */
#define PDM_PDMCLKCTRL_FREQ_Default (0x08400000UL) /*!< PDM_CLK = 32 MHz / 31 = 1.032 MHz. Nominal clock for RATIO=Ratio64. */
#define PDM_PDMCLKCTRL_FREQ_1067K (0x08800000UL) /*!< PDM_CLK = 32 MHz / 30 = 1.067 MHz */
#define PDM_PDMCLKCTRL_FREQ_1231K (0x09800000UL) /*!< PDM_CLK = 32 MHz / 26 = 1.231 MHz */
#define PDM_PDMCLKCTRL_FREQ_1280K (0x0A000000UL) /*!< PDM_CLK = 32 MHz / 25 = 1.280 MHz. Nominal clock for RATIO=Ratio80. */
#define PDM_PDMCLKCTRL_FREQ_1333K (0x0A800000UL) /*!< PDM_CLK = 32 MHz / 24 = 1.333 MHz */

/* Register: PDM_MODE */
/* Description: Defines the routing of the connected PDM microphones' signals */

/* Bit 1 : Defines on which PDM_CLK edge Left (or mono) is sampled */
#define PDM_MODE_EDGE_Pos (1UL) /*!< Position of EDGE field. */
#define PDM_MODE_EDGE_Msk (0x1UL << PDM_MODE_EDGE_Pos) /*!< Bit mask of EDGE field. */
#define PDM_MODE_EDGE_LeftFalling (0UL) /*!< Left (or mono) is sampled on falling edge of PDM_CLK */
#define PDM_MODE_EDGE_LeftRising (1UL) /*!< Left (or mono) is sampled on rising edge of PDM_CLK */

/* Bit 0 : Mono or stereo operation */
#define PDM_MODE_OPERATION_Pos (0UL) /*!< Position of OPERATION field. */
#define PDM_MODE_OPERATION_Msk (0x1UL << PDM_MODE_OPERATION_Pos) /*!< Bit mask of OPERATION field. */
#define PDM_MODE_OPERATION_Stereo (0UL) /*!< Sample and store one pair (Left + Right) of 16bit samples per RAM word R=[31:16]; L=[15:0] */
#define PDM_MODE_OPERATION_Mono (1UL) /*!< Sample and store two successive Left samples (16 bit each) per RAM word L1=[31:16]; L0=[15:0] */

/* Register: PDM_GAINL */
/* Description: Left output gain adjustment */

/* Bits 6..0 : Left output gain adjustment, in 0.5 dB steps, around the default module gain (see electrical parameters) 0x00    -20 dB gain adjust 0x01  -19.5 dB gain adjust (...) 0x27   -0.5 dB gain adjust 0x28      0 dB gain adjust 0x29   +0.5 dB gain adjust (...) 0x4F  +19.5 dB gain adjust 0x50    +20 dB gain adjust */
#define PDM_GAINL_GAINL_Pos (0UL) /*!< Position of GAINL field. */
#define PDM_GAINL_GAINL_Msk (0x7FUL << PDM_GAINL_GAINL_Pos) /*!< Bit mask of GAINL field. */
#define PDM_GAINL_GAINL_MinGain (0x00UL) /*!< -20dB gain adjustment (minimum) */
#define PDM_GAINL_GAINL_DefaultGain (0x28UL) /*!< 0dB gain adjustment ('2500 RMS' requirement) */
#define PDM_GAINL_GAINL_MaxGain (0x50UL) /*!< +20dB gain adjustment (maximum) */

/* Register: PDM_GAINR */
/* Description: Right output gain adjustment */

/* Bits 7..0 : Right output gain adjustment, in 0.5 dB steps, around the default module gain (see electrical parameters) */
#define PDM_GAINR_GAINR_Pos (0UL) /*!< Position of GAINR field. */
#define PDM_GAINR_GAINR_Msk (0xFFUL << PDM_GAINR_GAINR_Pos) /*!< Bit mask of GAINR field. */
#define PDM_GAINR_GAINR_MinGain (0x00UL) /*!< -20dB gain adjustment (minimum) */
#define PDM_GAINR_GAINR_DefaultGain (0x28UL) /*!< 0dB gain adjustment ('2500 RMS' requirement) */
#define PDM_GAINR_GAINR_MaxGain (0x50UL) /*!< +20dB gain adjustment (maximum) */

/* Register: PDM_RATIO */
/* Description: Selects the ratio between PDM_CLK and output sample rate. Change PDMCLKCTRL accordingly. */

/* Bit 0 : Selects the ratio between PDM_CLK and output sample rate */
#define PDM_RATIO_RATIO_Pos (0UL) /*!< Position of RATIO field. */
#define PDM_RATIO_RATIO_Msk (0x1UL << PDM_RATIO_RATIO_Pos) /*!< Bit mask of RATIO field. */
#define PDM_RATIO_RATIO_Ratio64 (0UL) /*!< Ratio of 64 */
#define PDM_RATIO_RATIO_Ratio80 (1UL) /*!< Ratio of 80 */

/* Register: PDM_PSEL_CLK */
/* Description: Pin number configuration for PDM CLK signal */

/* Bit 31 : Connection */
#define PDM_PSEL_CLK_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define PDM_PSEL_CLK_CONNECT_Msk (0x1UL << PDM_PSEL_CLK_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define PDM_PSEL_CLK_CONNECT_Connected (0UL) /*!< Connect */
#define PDM_PSEL_CLK_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define PDM_PSEL_CLK_PORT_Pos (5UL) /*!< Position of PORT field. */
#define PDM_PSEL_CLK_PORT_Msk (0x3UL << PDM_PSEL_CLK_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define PDM_PSEL_CLK_PIN_Pos (0UL) /*!< Position of PIN field. */
#define PDM_PSEL_CLK_PIN_Msk (0x1FUL << PDM_PSEL_CLK_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: PDM_PSEL_DIN */
/* Description: Pin number configuration for PDM DIN signal */

/* Bit 31 : Connection */
#define PDM_PSEL_DIN_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define PDM_PSEL_DIN_CONNECT_Msk (0x1UL << PDM_PSEL_DIN_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define PDM_PSEL_DIN_CONNECT_Connected (0UL) /*!< Connect */
#define PDM_PSEL_DIN_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define PDM_PSEL_DIN_PORT_Pos (5UL) /*!< Position of PORT field. */
#define PDM_PSEL_DIN_PORT_Msk (0x3UL << PDM_PSEL_DIN_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define PDM_PSEL_DIN_PIN_Pos (0UL) /*!< Position of PIN field. */
#define PDM_PSEL_DIN_PIN_Msk (0x1FUL << PDM_PSEL_DIN_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: PDM_SAMPLE_PTR */
/* Description: RAM address pointer to write samples to with EasyDMA */

/* Bits 31..0 : Address to write PDM samples to over DMA */
#define PDM_SAMPLE_PTR_SAMPLEPTR_Pos (0UL) /*!< Position of SAMPLEPTR field. */
#define PDM_SAMPLE_PTR_SAMPLEPTR_Msk (0xFFFFFFFFUL << PDM_SAMPLE_PTR_SAMPLEPTR_Pos) /*!< Bit mask of SAMPLEPTR field. */

/* Register: PDM_SAMPLE_MAXCNT */
/* Description: Number of samples to allocate memory for in EasyDMA mode */

/* Bits 14..0 : Length of DMA RAM allocation in number of samples */
#define PDM_SAMPLE_MAXCNT_BUFFSIZE_Pos (0UL) /*!< Position of BUFFSIZE field. */
#define PDM_SAMPLE_MAXCNT_BUFFSIZE_Msk (0x7FFFUL << PDM_SAMPLE_MAXCNT_BUFFSIZE_Pos) /*!< Bit mask of BUFFSIZE field. */


/* Peripheral: POWER */
/* Description: Power control */

/* Register: POWER_INTENSET */
/* Description: Enable interrupt */

/* Bit 9 : Write '1' to Enable interrupt for USBPWRRDY event */
#define POWER_INTENSET_USBPWRRDY_Pos (9UL) /*!< Position of USBPWRRDY field. */
#define POWER_INTENSET_USBPWRRDY_Msk (0x1UL << POWER_INTENSET_USBPWRRDY_Pos) /*!< Bit mask of USBPWRRDY field. */
#define POWER_INTENSET_USBPWRRDY_Disabled (0UL) /*!< Read: Disabled */
#define POWER_INTENSET_USBPWRRDY_Enabled (1UL) /*!< Read: Enabled */
#define POWER_INTENSET_USBPWRRDY_Set (1UL) /*!< Enable */

/* Bit 8 : Write '1' to Enable interrupt for USBREMOVED event */
#define POWER_INTENSET_USBREMOVED_Pos (8UL) /*!< Position of USBREMOVED field. */
#define POWER_INTENSET_USBREMOVED_Msk (0x1UL << POWER_INTENSET_USBREMOVED_Pos) /*!< Bit mask of USBREMOVED field. */
#define POWER_INTENSET_USBREMOVED_Disabled (0UL) /*!< Read: Disabled */
#define POWER_INTENSET_USBREMOVED_Enabled (1UL) /*!< Read: Enabled */
#define POWER_INTENSET_USBREMOVED_Set (1UL) /*!< Enable */

/* Bit 7 : Write '1' to Enable interrupt for USBDETECTED event */
#define POWER_INTENSET_USBDETECTED_Pos (7UL) /*!< Position of USBDETECTED field. */
#define POWER_INTENSET_USBDETECTED_Msk (0x1UL << POWER_INTENSET_USBDETECTED_Pos) /*!< Bit mask of USBDETECTED field. */
#define POWER_INTENSET_USBDETECTED_Disabled (0UL) /*!< Read: Disabled */
#define POWER_INTENSET_USBDETECTED_Enabled (1UL) /*!< Read: Enabled */
#define POWER_INTENSET_USBDETECTED_Set (1UL) /*!< Enable */

/* Bit 6 : Write '1' to Enable interrupt for SLEEPEXIT event */
#define POWER_INTENSET_SLEEPEXIT_Pos (6UL) /*!< Position of SLEEPEXIT field. */
#define POWER_INTENSET_SLEEPEXIT_Msk (0x1UL << POWER_INTENSET_SLEEPEXIT_Pos) /*!< Bit mask of SLEEPEXIT field. */
#define POWER_INTENSET_SLEEPEXIT_Disabled (0UL) /*!< Read: Disabled */
#define POWER_INTENSET_SLEEPEXIT_Enabled (1UL) /*!< Read: Enabled */
#define POWER_INTENSET_SLEEPEXIT_Set (1UL) /*!< Enable */

/* Bit 5 : Write '1' to Enable interrupt for SLEEPENTER event */
#define POWER_INTENSET_SLEEPENTER_Pos (5UL) /*!< Position of SLEEPENTER field. */
#define POWER_INTENSET_SLEEPENTER_Msk (0x1UL << POWER_INTENSET_SLEEPENTER_Pos) /*!< Bit mask of SLEEPENTER field. */
#define POWER_INTENSET_SLEEPENTER_Disabled (0UL) /*!< Read: Disabled */
#define POWER_INTENSET_SLEEPENTER_Enabled (1UL) /*!< Read: Enabled */
#define POWER_INTENSET_SLEEPENTER_Set (1UL) /*!< Enable */

/* Bit 2 : Write '1' to Enable interrupt for POFWARN event */
#define POWER_INTENSET_POFWARN_Pos (2UL) /*!< Position of POFWARN field. */
#define POWER_INTENSET_POFWARN_Msk (0x1UL << POWER_INTENSET_POFWARN_Pos) /*!< Bit mask of POFWARN field. */
#define POWER_INTENSET_POFWARN_Disabled (0UL) /*!< Read: Disabled */
#define POWER_INTENSET_POFWARN_Enabled (1UL) /*!< Read: Enabled */
#define POWER_INTENSET_POFWARN_Set (1UL) /*!< Enable */

/* Register: POWER_INTENCLR */
/* Description: Disable interrupt */

/* Bit 9 : Write '1' to Disable interrupt for USBPWRRDY event */
#define POWER_INTENCLR_USBPWRRDY_Pos (9UL) /*!< Position of USBPWRRDY field. */
#define POWER_INTENCLR_USBPWRRDY_Msk (0x1UL << POWER_INTENCLR_USBPWRRDY_Pos) /*!< Bit mask of USBPWRRDY field. */
#define POWER_INTENCLR_USBPWRRDY_Disabled (0UL) /*!< Read: Disabled */
#define POWER_INTENCLR_USBPWRRDY_Enabled (1UL) /*!< Read: Enabled */
#define POWER_INTENCLR_USBPWRRDY_Clear (1UL) /*!< Disable */

/* Bit 8 : Write '1' to Disable interrupt for USBREMOVED event */
#define POWER_INTENCLR_USBREMOVED_Pos (8UL) /*!< Position of USBREMOVED field. */
#define POWER_INTENCLR_USBREMOVED_Msk (0x1UL << POWER_INTENCLR_USBREMOVED_Pos) /*!< Bit mask of USBREMOVED field. */
#define POWER_INTENCLR_USBREMOVED_Disabled (0UL) /*!< Read: Disabled */
#define POWER_INTENCLR_USBREMOVED_Enabled (1UL) /*!< Read: Enabled */
#define POWER_INTENCLR_USBREMOVED_Clear (1UL) /*!< Disable */

/* Bit 7 : Write '1' to Disable interrupt for USBDETECTED event */
#define POWER_INTENCLR_USBDETECTED_Pos (7UL) /*!< Position of USBDETECTED field. */
#define POWER_INTENCLR_USBDETECTED_Msk (0x1UL << POWER_INTENCLR_USBDETECTED_Pos) /*!< Bit mask of USBDETECTED field. */
#define POWER_INTENCLR_USBDETECTED_Disabled (0UL) /*!< Read: Disabled */
#define POWER_INTENCLR_USBDETECTED_Enabled (1UL) /*!< Read: Enabled */
#define POWER_INTENCLR_USBDETECTED_Clear (1UL) /*!< Disable */

/* Bit 6 : Write '1' to Disable interrupt for SLEEPEXIT event */
#define POWER_INTENCLR_SLEEPEXIT_Pos (6UL) /*!< Position of SLEEPEXIT field. */
#define POWER_INTENCLR_SLEEPEXIT_Msk (0x1UL << POWER_INTENCLR_SLEEPEXIT_Pos) /*!< Bit mask of SLEEPEXIT field. */
#define POWER_INTENCLR_SLEEPEXIT_Disabled (0UL) /*!< Read: Disabled */
#define POWER_INTENCLR_SLEEPEXIT_Enabled (1UL) /*!< Read: Enabled */
#define POWER_INTENCLR_SLEEPEXIT_Clear (1UL) /*!< Disable */

/* Bit 5 : Write '1' to Disable interrupt for SLEEPENTER event */
#define POWER_INTENCLR_SLEEPENTER_Pos (5UL) /*!< Position of SLEEPENTER field. */
#define POWER_INTENCLR_SLEEPENTER_Msk (0x1UL << POWER_INTENCLR_SLEEPENTER_Pos) /*!< Bit mask of SLEEPENTER field. */
#define POWER_INTENCLR_SLEEPENTER_Disabled (0UL) /*!< Read: Disabled */
#define POWER_INTENCLR_SLEEPENTER_Enabled (1UL) /*!< Read: Enabled */
#define POWER_INTENCLR_SLEEPENTER_Clear (1UL) /*!< Disable */

/* Bit 2 : Write '1' to Disable interrupt for POFWARN event */
#define POWER_INTENCLR_POFWARN_Pos (2UL) /*!< Position of POFWARN field. */
#define POWER_INTENCLR_POFWARN_Msk (0x1UL << POWER_INTENCLR_POFWARN_Pos) /*!< Bit mask of POFWARN field. */
#define POWER_INTENCLR_POFWARN_Disabled (0UL) /*!< Read: Disabled */
#define POWER_INTENCLR_POFWARN_Enabled (1UL) /*!< Read: Enabled */
#define POWER_INTENCLR_POFWARN_Clear (1UL) /*!< Disable */

/* Register: POWER_RESETREAS */
/* Description: Reset reason */

/* Bit 20 : Reset due to wake up from System OFF mode by Vbus rising into valid range */
#define POWER_RESETREAS_VBUS_Pos (20UL) /*!< Position of VBUS field. */
#define POWER_RESETREAS_VBUS_Msk (0x1UL << POWER_RESETREAS_VBUS_Pos) /*!< Bit mask of VBUS field. */
#define POWER_RESETREAS_VBUS_NotDetected (0UL) /*!< Not detected */
#define POWER_RESETREAS_VBUS_Detected (1UL) /*!< Detected */

/* Bit 19 : Reset due to wake up from System OFF mode by NFC field detect */
#define POWER_RESETREAS_NFC_Pos (19UL) /*!< Position of NFC field. */
#define POWER_RESETREAS_NFC_Msk (0x1UL << POWER_RESETREAS_NFC_Pos) /*!< Bit mask of NFC field. */
#define POWER_RESETREAS_NFC_NotDetected (0UL) /*!< Not detected */
#define POWER_RESETREAS_NFC_Detected (1UL) /*!< Detected */

/* Bit 18 : Reset due to wake up from System OFF mode when wakeup is triggered from entering into debug interface mode */
#define POWER_RESETREAS_DIF_Pos (18UL) /*!< Position of DIF field. */
#define POWER_RESETREAS_DIF_Msk (0x1UL << POWER_RESETREAS_DIF_Pos) /*!< Bit mask of DIF field. */
#define POWER_RESETREAS_DIF_NotDetected (0UL) /*!< Not detected */
#define POWER_RESETREAS_DIF_Detected (1UL) /*!< Detected */

/* Bit 17 : Reset due to wake up from System OFF mode when wakeup is triggered from ANADETECT signal from LPCOMP */
#define POWER_RESETREAS_LPCOMP_Pos (17UL) /*!< Position of LPCOMP field. */
#define POWER_RESETREAS_LPCOMP_Msk (0x1UL << POWER_RESETREAS_LPCOMP_Pos) /*!< Bit mask of LPCOMP field. */
#define POWER_RESETREAS_LPCOMP_NotDetected (0UL) /*!< Not detected */
#define POWER_RESETREAS_LPCOMP_Detected (1UL) /*!< Detected */

/* Bit 16 : Reset due to wake up from System OFF mode when wakeup is triggered from DETECT signal from GPIO */
#define POWER_RESETREAS_OFF_Pos (16UL) /*!< Position of OFF field. */
#define POWER_RESETREAS_OFF_Msk (0x1UL << POWER_RESETREAS_OFF_Pos) /*!< Bit mask of OFF field. */
#define POWER_RESETREAS_OFF_NotDetected (0UL) /*!< Not detected */
#define POWER_RESETREAS_OFF_Detected (1UL) /*!< Detected */

/* Bit 3 : Reset from CPU lock-up detected */
#define POWER_RESETREAS_LOCKUP_Pos (3UL) /*!< Position of LOCKUP field. */
#define POWER_RESETREAS_LOCKUP_Msk (0x1UL << POWER_RESETREAS_LOCKUP_Pos) /*!< Bit mask of LOCKUP field. */
#define POWER_RESETREAS_LOCKUP_NotDetected (0UL) /*!< Not detected */
#define POWER_RESETREAS_LOCKUP_Detected (1UL) /*!< Detected */

/* Bit 2 : Reset from soft reset detected */
#define POWER_RESETREAS_SREQ_Pos (2UL) /*!< Position of SREQ field. */
#define POWER_RESETREAS_SREQ_Msk (0x1UL << POWER_RESETREAS_SREQ_Pos) /*!< Bit mask of SREQ field. */
#define POWER_RESETREAS_SREQ_NotDetected (0UL) /*!< Not detected */
#define POWER_RESETREAS_SREQ_Detected (1UL) /*!< Detected */

/* Bit 1 : Reset from watchdog detected */
#define POWER_RESETREAS_DOG_Pos (1UL) /*!< Position of DOG field. */
#define POWER_RESETREAS_DOG_Msk (0x1UL << POWER_RESETREAS_DOG_Pos) /*!< Bit mask of DOG field. */
#define POWER_RESETREAS_DOG_NotDetected (0UL) /*!< Not detected */
#define POWER_RESETREAS_DOG_Detected (1UL) /*!< Detected */

/* Bit 0 : Reset from pin-reset detected */
#define POWER_RESETREAS_RESETPIN_Pos (0UL) /*!< Position of RESETPIN field. */
#define POWER_RESETREAS_RESETPIN_Msk (0x1UL << POWER_RESETREAS_RESETPIN_Pos) /*!< Bit mask of RESETPIN field. */
#define POWER_RESETREAS_RESETPIN_NotDetected (0UL) /*!< Not detected */
#define POWER_RESETREAS_RESETPIN_Detected (1UL) /*!< Detected */

/* Register: POWER_RAMSTATUS */
/* Description: Deprecated register -  RAM status register */

/* Bit 3 : RAM block 3 is on or off/powering up */
#define POWER_RAMSTATUS_RAMBLOCK3_Pos (3UL) /*!< Position of RAMBLOCK3 field. */
#define POWER_RAMSTATUS_RAMBLOCK3_Msk (0x1UL << POWER_RAMSTATUS_RAMBLOCK3_Pos) /*!< Bit mask of RAMBLOCK3 field. */
#define POWER_RAMSTATUS_RAMBLOCK3_Off (0UL) /*!< Off */
#define POWER_RAMSTATUS_RAMBLOCK3_On (1UL) /*!< On */

/* Bit 2 : RAM block 2 is on or off/powering up */
#define POWER_RAMSTATUS_RAMBLOCK2_Pos (2UL) /*!< Position of RAMBLOCK2 field. */
#define POWER_RAMSTATUS_RAMBLOCK2_Msk (0x1UL << POWER_RAMSTATUS_RAMBLOCK2_Pos) /*!< Bit mask of RAMBLOCK2 field. */
#define POWER_RAMSTATUS_RAMBLOCK2_Off (0UL) /*!< Off */
#define POWER_RAMSTATUS_RAMBLOCK2_On (1UL) /*!< On */

/* Bit 1 : RAM block 1 is on or off/powering up */
#define POWER_RAMSTATUS_RAMBLOCK1_Pos (1UL) /*!< Position of RAMBLOCK1 field. */
#define POWER_RAMSTATUS_RAMBLOCK1_Msk (0x1UL << POWER_RAMSTATUS_RAMBLOCK1_Pos) /*!< Bit mask of RAMBLOCK1 field. */
#define POWER_RAMSTATUS_RAMBLOCK1_Off (0UL) /*!< Off */
#define POWER_RAMSTATUS_RAMBLOCK1_On (1UL) /*!< On */

/* Bit 0 : RAM block 0 is on or off/powering up */
#define POWER_RAMSTATUS_RAMBLOCK0_Pos (0UL) /*!< Position of RAMBLOCK0 field. */
#define POWER_RAMSTATUS_RAMBLOCK0_Msk (0x1UL << POWER_RAMSTATUS_RAMBLOCK0_Pos) /*!< Bit mask of RAMBLOCK0 field. */
#define POWER_RAMSTATUS_RAMBLOCK0_Off (0UL) /*!< Off */
#define POWER_RAMSTATUS_RAMBLOCK0_On (1UL) /*!< On */

/* Register: POWER_USBREGSTATUS */
/* Description: USB supply status */

/* Bit 1 : USB supply output settling time elapsed */
#define POWER_USBREGSTATUS_OUTPUTRDY_Pos (1UL) /*!< Position of OUTPUTRDY field. */
#define POWER_USBREGSTATUS_OUTPUTRDY_Msk (0x1UL << POWER_USBREGSTATUS_OUTPUTRDY_Pos) /*!< Bit mask of OUTPUTRDY field. */
#define POWER_USBREGSTATUS_OUTPUTRDY_NotReady (0UL) /*!< USBREG output settling time not elapsed */
#define POWER_USBREGSTATUS_OUTPUTRDY_Ready (1UL) /*!< USBREG output settling time elapsed (same information as USBPWRRDY event) */

/* Bit 0 : VBUS input detection status (USBDETECTED and USBREMOVED events are derived from this information) */
#define POWER_USBREGSTATUS_VBUSDETECT_Pos (0UL) /*!< Position of VBUSDETECT field. */
#define POWER_USBREGSTATUS_VBUSDETECT_Msk (0x1UL << POWER_USBREGSTATUS_VBUSDETECT_Pos) /*!< Bit mask of VBUSDETECT field. */
#define POWER_USBREGSTATUS_VBUSDETECT_NoVbus (0UL) /*!< VBUS voltage below valid threshold */
#define POWER_USBREGSTATUS_VBUSDETECT_VbusPresent (1UL) /*!< VBUS voltage above valid threshold */

/* Register: POWER_SYSTEMOFF */
/* Description: System OFF register */

/* Bit 0 : Enable System OFF mode */
#define POWER_SYSTEMOFF_SYSTEMOFF_Pos (0UL) /*!< Position of SYSTEMOFF field. */
#define POWER_SYSTEMOFF_SYSTEMOFF_Msk (0x1UL << POWER_SYSTEMOFF_SYSTEMOFF_Pos) /*!< Bit mask of SYSTEMOFF field. */
#define POWER_SYSTEMOFF_SYSTEMOFF_Enter (1UL) /*!< Enable System OFF mode */

/* Register: POWER_POFCON */
/* Description: Power failure comparator configuration */

/* Bits 11..8 : Power failure comparator threshold setting for voltage supply on VDDH */
#define POWER_POFCON_THRESHOLDVDDH_Pos (8UL) /*!< Position of THRESHOLDVDDH field. */
#define POWER_POFCON_THRESHOLDVDDH_Msk (0xFUL << POWER_POFCON_THRESHOLDVDDH_Pos) /*!< Bit mask of THRESHOLDVDDH field. */
#define POWER_POFCON_THRESHOLDVDDH_V27 (0UL) /*!< Set threshold to 2.7 V */
#define POWER_POFCON_THRESHOLDVDDH_V28 (1UL) /*!< Set threshold to 2.8 V */
#define POWER_POFCON_THRESHOLDVDDH_V29 (2UL) /*!< Set threshold to 2.9 V */
#define POWER_POFCON_THRESHOLDVDDH_V30 (3UL) /*!< Set threshold to 3.0 V */
#define POWER_POFCON_THRESHOLDVDDH_V31 (4UL) /*!< Set threshold to 3.1 V */
#define POWER_POFCON_THRESHOLDVDDH_V32 (5UL) /*!< Set threshold to 3.2 V */
#define POWER_POFCON_THRESHOLDVDDH_V33 (6UL) /*!< Set threshold to 3.3 V */
#define POWER_POFCON_THRESHOLDVDDH_V34 (7UL) /*!< Set threshold to 3.4 V */
#define POWER_POFCON_THRESHOLDVDDH_V35 (8UL) /*!< Set threshold to 3.5 V */
#define POWER_POFCON_THRESHOLDVDDH_V36 (9UL) /*!< Set threshold to 3.6 V */
#define POWER_POFCON_THRESHOLDVDDH_V37 (10UL) /*!< Set threshold to 3.7 V */
#define POWER_POFCON_THRESHOLDVDDH_V38 (11UL) /*!< Set threshold to 3.8 V */
#define POWER_POFCON_THRESHOLDVDDH_V39 (12UL) /*!< Set threshold to 3.9 V */
#define POWER_POFCON_THRESHOLDVDDH_V40 (13UL) /*!< Set threshold to 4.0 V */
#define POWER_POFCON_THRESHOLDVDDH_V41 (14UL) /*!< Set threshold to 4.1 V */
#define POWER_POFCON_THRESHOLDVDDH_V42 (15UL) /*!< Set threshold to 4.2 V */

/* Bits 4..1 : Power failure comparator threshold setting */
#define POWER_POFCON_THRESHOLD_Pos (1UL) /*!< Position of THRESHOLD field. */
#define POWER_POFCON_THRESHOLD_Msk (0xFUL << POWER_POFCON_THRESHOLD_Pos) /*!< Bit mask of THRESHOLD field. */
#define POWER_POFCON_THRESHOLD_V17 (4UL) /*!< Set threshold to 1.7 V */
#define POWER_POFCON_THRESHOLD_V18 (5UL) /*!< Set threshold to 1.8 V */
#define POWER_POFCON_THRESHOLD_V19 (6UL) /*!< Set threshold to 1.9 V */
#define POWER_POFCON_THRESHOLD_V20 (7UL) /*!< Set threshold to 2.0 V */
#define POWER_POFCON_THRESHOLD_V21 (8UL) /*!< Set threshold to 2.1 V */
#define POWER_POFCON_THRESHOLD_V22 (9UL) /*!< Set threshold to 2.2 V */
#define POWER_POFCON_THRESHOLD_V23 (10UL) /*!< Set threshold to 2.3 V */
#define POWER_POFCON_THRESHOLD_V24 (11UL) /*!< Set threshold to 2.4 V */
#define POWER_POFCON_THRESHOLD_V25 (12UL) /*!< Set threshold to 2.5 V */
#define POWER_POFCON_THRESHOLD_V26 (13UL) /*!< Set threshold to 2.6 V */
#define POWER_POFCON_THRESHOLD_V27 (14UL) /*!< Set threshold to 2.7 V */
#define POWER_POFCON_THRESHOLD_V28 (15UL) /*!< Set threshold to 2.8 V */

/* Bit 0 : Enable or disable power failure comparator */
#define POWER_POFCON_POF_Pos (0UL) /*!< Position of POF field. */
#define POWER_POFCON_POF_Msk (0x1UL << POWER_POFCON_POF_Pos) /*!< Bit mask of POF field. */
#define POWER_POFCON_POF_Disabled (0UL) /*!< Disable */
#define POWER_POFCON_POF_Enabled (1UL) /*!< Enable */

/* Register: POWER_GPREGRET */
/* Description: General purpose retention register */

/* Bits 7..0 : General purpose retention register */
#define POWER_GPREGRET_GPREGRET_Pos (0UL) /*!< Position of GPREGRET field. */
#define POWER_GPREGRET_GPREGRET_Msk (0xFFUL << POWER_GPREGRET_GPREGRET_Pos) /*!< Bit mask of GPREGRET field. */

/* Register: POWER_GPREGRET2 */
/* Description: General purpose retention register */

/* Bits 7..0 : General purpose retention register */
#define POWER_GPREGRET2_GPREGRET_Pos (0UL) /*!< Position of GPREGRET field. */
#define POWER_GPREGRET2_GPREGRET_Msk (0xFFUL << POWER_GPREGRET2_GPREGRET_Pos) /*!< Bit mask of GPREGRET field. */

/* Register: POWER_DCDCEN */
/* Description: Enable DC/DC converter for REG1 stage. */

/* Bit 0 : Enable DC/DC converter for REG1 stage. */
#define POWER_DCDCEN_DCDCEN_Pos (0UL) /*!< Position of DCDCEN field. */
#define POWER_DCDCEN_DCDCEN_Msk (0x1UL << POWER_DCDCEN_DCDCEN_Pos) /*!< Bit mask of DCDCEN field. */
#define POWER_DCDCEN_DCDCEN_Disabled (0UL) /*!< Disable */
#define POWER_DCDCEN_DCDCEN_Enabled (1UL) /*!< Enable */

/* Register: POWER_DCDCEN0 */
/* Description: Enable DC/DC converter for REG0 stage. */

/* Bit 0 : Enable DC/DC converter for REG0 stage. */
#define POWER_DCDCEN0_DCDCEN_Pos (0UL) /*!< Position of DCDCEN field. */
#define POWER_DCDCEN0_DCDCEN_Msk (0x1UL << POWER_DCDCEN0_DCDCEN_Pos) /*!< Bit mask of DCDCEN field. */
#define POWER_DCDCEN0_DCDCEN_Disabled (0UL) /*!< Disable */
#define POWER_DCDCEN0_DCDCEN_Enabled (1UL) /*!< Enable */

/* Register: POWER_MAINREGSTATUS */
/* Description: Main supply status */

/* Bit 0 : Main supply status */
#define POWER_MAINREGSTATUS_MAINREGSTATUS_Pos (0UL) /*!< Position of MAINREGSTATUS field. */
#define POWER_MAINREGSTATUS_MAINREGSTATUS_Msk (0x1UL << POWER_MAINREGSTATUS_MAINREGSTATUS_Pos) /*!< Bit mask of MAINREGSTATUS field. */
#define POWER_MAINREGSTATUS_MAINREGSTATUS_Normal (0UL) /*!< Normal voltage mode. Voltage supplied on VDD. */
#define POWER_MAINREGSTATUS_MAINREGSTATUS_High (1UL) /*!< High voltage mode. Voltage supplied on VDDH. */

/* Register: POWER_RAM_POWER */
/* Description: Description cluster[0]:  RAM0 power control register */

/* Bit 31 : Keep retention on RAM section S15 when RAM section is in OFF */
#define POWER_RAM_POWER_S15RETENTION_Pos (31UL) /*!< Position of S15RETENTION field. */
#define POWER_RAM_POWER_S15RETENTION_Msk (0x1UL << POWER_RAM_POWER_S15RETENTION_Pos) /*!< Bit mask of S15RETENTION field. */
#define POWER_RAM_POWER_S15RETENTION_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S15RETENTION_On (1UL) /*!< On */

/* Bit 30 : Keep retention on RAM section S14 when RAM section is in OFF */
#define POWER_RAM_POWER_S14RETENTION_Pos (30UL) /*!< Position of S14RETENTION field. */
#define POWER_RAM_POWER_S14RETENTION_Msk (0x1UL << POWER_RAM_POWER_S14RETENTION_Pos) /*!< Bit mask of S14RETENTION field. */
#define POWER_RAM_POWER_S14RETENTION_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S14RETENTION_On (1UL) /*!< On */

/* Bit 29 : Keep retention on RAM section S13 when RAM section is in OFF */
#define POWER_RAM_POWER_S13RETENTION_Pos (29UL) /*!< Position of S13RETENTION field. */
#define POWER_RAM_POWER_S13RETENTION_Msk (0x1UL << POWER_RAM_POWER_S13RETENTION_Pos) /*!< Bit mask of S13RETENTION field. */
#define POWER_RAM_POWER_S13RETENTION_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S13RETENTION_On (1UL) /*!< On */

/* Bit 28 : Keep retention on RAM section S12 when RAM section is in OFF */
#define POWER_RAM_POWER_S12RETENTION_Pos (28UL) /*!< Position of S12RETENTION field. */
#define POWER_RAM_POWER_S12RETENTION_Msk (0x1UL << POWER_RAM_POWER_S12RETENTION_Pos) /*!< Bit mask of S12RETENTION field. */
#define POWER_RAM_POWER_S12RETENTION_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S12RETENTION_On (1UL) /*!< On */

/* Bit 27 : Keep retention on RAM section S11 when RAM section is in OFF */
#define POWER_RAM_POWER_S11RETENTION_Pos (27UL) /*!< Position of S11RETENTION field. */
#define POWER_RAM_POWER_S11RETENTION_Msk (0x1UL << POWER_RAM_POWER_S11RETENTION_Pos) /*!< Bit mask of S11RETENTION field. */
#define POWER_RAM_POWER_S11RETENTION_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S11RETENTION_On (1UL) /*!< On */

/* Bit 26 : Keep retention on RAM section S10 when RAM section is in OFF */
#define POWER_RAM_POWER_S10RETENTION_Pos (26UL) /*!< Position of S10RETENTION field. */
#define POWER_RAM_POWER_S10RETENTION_Msk (0x1UL << POWER_RAM_POWER_S10RETENTION_Pos) /*!< Bit mask of S10RETENTION field. */
#define POWER_RAM_POWER_S10RETENTION_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S10RETENTION_On (1UL) /*!< On */

/* Bit 25 : Keep retention on RAM section S9 when RAM section is in OFF */
#define POWER_RAM_POWER_S9RETENTION_Pos (25UL) /*!< Position of S9RETENTION field. */
#define POWER_RAM_POWER_S9RETENTION_Msk (0x1UL << POWER_RAM_POWER_S9RETENTION_Pos) /*!< Bit mask of S9RETENTION field. */
#define POWER_RAM_POWER_S9RETENTION_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S9RETENTION_On (1UL) /*!< On */

/* Bit 24 : Keep retention on RAM section S8 when RAM section is in OFF */
#define POWER_RAM_POWER_S8RETENTION_Pos (24UL) /*!< Position of S8RETENTION field. */
#define POWER_RAM_POWER_S8RETENTION_Msk (0x1UL << POWER_RAM_POWER_S8RETENTION_Pos) /*!< Bit mask of S8RETENTION field. */
#define POWER_RAM_POWER_S8RETENTION_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S8RETENTION_On (1UL) /*!< On */

/* Bit 23 : Keep retention on RAM section S7 when RAM section is in OFF */
#define POWER_RAM_POWER_S7RETENTION_Pos (23UL) /*!< Position of S7RETENTION field. */
#define POWER_RAM_POWER_S7RETENTION_Msk (0x1UL << POWER_RAM_POWER_S7RETENTION_Pos) /*!< Bit mask of S7RETENTION field. */
#define POWER_RAM_POWER_S7RETENTION_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S7RETENTION_On (1UL) /*!< On */

/* Bit 22 : Keep retention on RAM section S6 when RAM section is in OFF */
#define POWER_RAM_POWER_S6RETENTION_Pos (22UL) /*!< Position of S6RETENTION field. */
#define POWER_RAM_POWER_S6RETENTION_Msk (0x1UL << POWER_RAM_POWER_S6RETENTION_Pos) /*!< Bit mask of S6RETENTION field. */
#define POWER_RAM_POWER_S6RETENTION_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S6RETENTION_On (1UL) /*!< On */

/* Bit 21 : Keep retention on RAM section S5 when RAM section is in OFF */
#define POWER_RAM_POWER_S5RETENTION_Pos (21UL) /*!< Position of S5RETENTION field. */
#define POWER_RAM_POWER_S5RETENTION_Msk (0x1UL << POWER_RAM_POWER_S5RETENTION_Pos) /*!< Bit mask of S5RETENTION field. */
#define POWER_RAM_POWER_S5RETENTION_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S5RETENTION_On (1UL) /*!< On */

/* Bit 20 : Keep retention on RAM section S4 when RAM section is in OFF */
#define POWER_RAM_POWER_S4RETENTION_Pos (20UL) /*!< Position of S4RETENTION field. */
#define POWER_RAM_POWER_S4RETENTION_Msk (0x1UL << POWER_RAM_POWER_S4RETENTION_Pos) /*!< Bit mask of S4RETENTION field. */
#define POWER_RAM_POWER_S4RETENTION_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S4RETENTION_On (1UL) /*!< On */

/* Bit 19 : Keep retention on RAM section S3 when RAM section is in OFF */
#define POWER_RAM_POWER_S3RETENTION_Pos (19UL) /*!< Position of S3RETENTION field. */
#define POWER_RAM_POWER_S3RETENTION_Msk (0x1UL << POWER_RAM_POWER_S3RETENTION_Pos) /*!< Bit mask of S3RETENTION field. */
#define POWER_RAM_POWER_S3RETENTION_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S3RETENTION_On (1UL) /*!< On */

/* Bit 18 : Keep retention on RAM section S2 when RAM section is in OFF */
#define POWER_RAM_POWER_S2RETENTION_Pos (18UL) /*!< Position of S2RETENTION field. */
#define POWER_RAM_POWER_S2RETENTION_Msk (0x1UL << POWER_RAM_POWER_S2RETENTION_Pos) /*!< Bit mask of S2RETENTION field. */
#define POWER_RAM_POWER_S2RETENTION_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S2RETENTION_On (1UL) /*!< On */

/* Bit 17 : Keep retention on RAM section S1 when RAM section is in OFF */
#define POWER_RAM_POWER_S1RETENTION_Pos (17UL) /*!< Position of S1RETENTION field. */
#define POWER_RAM_POWER_S1RETENTION_Msk (0x1UL << POWER_RAM_POWER_S1RETENTION_Pos) /*!< Bit mask of S1RETENTION field. */
#define POWER_RAM_POWER_S1RETENTION_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S1RETENTION_On (1UL) /*!< On */

/* Bit 16 : Keep retention on RAM section S0 when RAM section is in OFF */
#define POWER_RAM_POWER_S0RETENTION_Pos (16UL) /*!< Position of S0RETENTION field. */
#define POWER_RAM_POWER_S0RETENTION_Msk (0x1UL << POWER_RAM_POWER_S0RETENTION_Pos) /*!< Bit mask of S0RETENTION field. */
#define POWER_RAM_POWER_S0RETENTION_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S0RETENTION_On (1UL) /*!< On */

/* Bit 15 : Keep RAM section S15 ON or OFF in System ON mode. */
#define POWER_RAM_POWER_S15POWER_Pos (15UL) /*!< Position of S15POWER field. */
#define POWER_RAM_POWER_S15POWER_Msk (0x1UL << POWER_RAM_POWER_S15POWER_Pos) /*!< Bit mask of S15POWER field. */
#define POWER_RAM_POWER_S15POWER_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S15POWER_On (1UL) /*!< On */

/* Bit 14 : Keep RAM section S14 ON or OFF in System ON mode. */
#define POWER_RAM_POWER_S14POWER_Pos (14UL) /*!< Position of S14POWER field. */
#define POWER_RAM_POWER_S14POWER_Msk (0x1UL << POWER_RAM_POWER_S14POWER_Pos) /*!< Bit mask of S14POWER field. */
#define POWER_RAM_POWER_S14POWER_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S14POWER_On (1UL) /*!< On */

/* Bit 13 : Keep RAM section S13 ON or OFF in System ON mode. */
#define POWER_RAM_POWER_S13POWER_Pos (13UL) /*!< Position of S13POWER field. */
#define POWER_RAM_POWER_S13POWER_Msk (0x1UL << POWER_RAM_POWER_S13POWER_Pos) /*!< Bit mask of S13POWER field. */
#define POWER_RAM_POWER_S13POWER_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S13POWER_On (1UL) /*!< On */

/* Bit 12 : Keep RAM section S12 ON or OFF in System ON mode. */
#define POWER_RAM_POWER_S12POWER_Pos (12UL) /*!< Position of S12POWER field. */
#define POWER_RAM_POWER_S12POWER_Msk (0x1UL << POWER_RAM_POWER_S12POWER_Pos) /*!< Bit mask of S12POWER field. */
#define POWER_RAM_POWER_S12POWER_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S12POWER_On (1UL) /*!< On */

/* Bit 11 : Keep RAM section S11 ON or OFF in System ON mode. */
#define POWER_RAM_POWER_S11POWER_Pos (11UL) /*!< Position of S11POWER field. */
#define POWER_RAM_POWER_S11POWER_Msk (0x1UL << POWER_RAM_POWER_S11POWER_Pos) /*!< Bit mask of S11POWER field. */
#define POWER_RAM_POWER_S11POWER_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S11POWER_On (1UL) /*!< On */

/* Bit 10 : Keep RAM section S10 ON or OFF in System ON mode. */
#define POWER_RAM_POWER_S10POWER_Pos (10UL) /*!< Position of S10POWER field. */
#define POWER_RAM_POWER_S10POWER_Msk (0x1UL << POWER_RAM_POWER_S10POWER_Pos) /*!< Bit mask of S10POWER field. */
#define POWER_RAM_POWER_S10POWER_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S10POWER_On (1UL) /*!< On */

/* Bit 9 : Keep RAM section S9 ON or OFF in System ON mode. */
#define POWER_RAM_POWER_S9POWER_Pos (9UL) /*!< Position of S9POWER field. */
#define POWER_RAM_POWER_S9POWER_Msk (0x1UL << POWER_RAM_POWER_S9POWER_Pos) /*!< Bit mask of S9POWER field. */
#define POWER_RAM_POWER_S9POWER_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S9POWER_On (1UL) /*!< On */

/* Bit 8 : Keep RAM section S8 ON or OFF in System ON mode. */
#define POWER_RAM_POWER_S8POWER_Pos (8UL) /*!< Position of S8POWER field. */
#define POWER_RAM_POWER_S8POWER_Msk (0x1UL << POWER_RAM_POWER_S8POWER_Pos) /*!< Bit mask of S8POWER field. */
#define POWER_RAM_POWER_S8POWER_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S8POWER_On (1UL) /*!< On */

/* Bit 7 : Keep RAM section S7 ON or OFF in System ON mode. */
#define POWER_RAM_POWER_S7POWER_Pos (7UL) /*!< Position of S7POWER field. */
#define POWER_RAM_POWER_S7POWER_Msk (0x1UL << POWER_RAM_POWER_S7POWER_Pos) /*!< Bit mask of S7POWER field. */
#define POWER_RAM_POWER_S7POWER_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S7POWER_On (1UL) /*!< On */

/* Bit 6 : Keep RAM section S6 ON or OFF in System ON mode. */
#define POWER_RAM_POWER_S6POWER_Pos (6UL) /*!< Position of S6POWER field. */
#define POWER_RAM_POWER_S6POWER_Msk (0x1UL << POWER_RAM_POWER_S6POWER_Pos) /*!< Bit mask of S6POWER field. */
#define POWER_RAM_POWER_S6POWER_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S6POWER_On (1UL) /*!< On */

/* Bit 5 : Keep RAM section S5 ON or OFF in System ON mode. */
#define POWER_RAM_POWER_S5POWER_Pos (5UL) /*!< Position of S5POWER field. */
#define POWER_RAM_POWER_S5POWER_Msk (0x1UL << POWER_RAM_POWER_S5POWER_Pos) /*!< Bit mask of S5POWER field. */
#define POWER_RAM_POWER_S5POWER_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S5POWER_On (1UL) /*!< On */

/* Bit 4 : Keep RAM section S4 ON or OFF in System ON mode. */
#define POWER_RAM_POWER_S4POWER_Pos (4UL) /*!< Position of S4POWER field. */
#define POWER_RAM_POWER_S4POWER_Msk (0x1UL << POWER_RAM_POWER_S4POWER_Pos) /*!< Bit mask of S4POWER field. */
#define POWER_RAM_POWER_S4POWER_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S4POWER_On (1UL) /*!< On */

/* Bit 3 : Keep RAM section S3 ON or OFF in System ON mode. */
#define POWER_RAM_POWER_S3POWER_Pos (3UL) /*!< Position of S3POWER field. */
#define POWER_RAM_POWER_S3POWER_Msk (0x1UL << POWER_RAM_POWER_S3POWER_Pos) /*!< Bit mask of S3POWER field. */
#define POWER_RAM_POWER_S3POWER_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S3POWER_On (1UL) /*!< On */

/* Bit 2 : Keep RAM section S2 ON or OFF in System ON mode. */
#define POWER_RAM_POWER_S2POWER_Pos (2UL) /*!< Position of S2POWER field. */
#define POWER_RAM_POWER_S2POWER_Msk (0x1UL << POWER_RAM_POWER_S2POWER_Pos) /*!< Bit mask of S2POWER field. */
#define POWER_RAM_POWER_S2POWER_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S2POWER_On (1UL) /*!< On */

/* Bit 1 : Keep RAM section S1 ON or OFF in System ON mode. */
#define POWER_RAM_POWER_S1POWER_Pos (1UL) /*!< Position of S1POWER field. */
#define POWER_RAM_POWER_S1POWER_Msk (0x1UL << POWER_RAM_POWER_S1POWER_Pos) /*!< Bit mask of S1POWER field. */
#define POWER_RAM_POWER_S1POWER_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S1POWER_On (1UL) /*!< On */

/* Bit 0 : Keep RAM section S0 ON or OFF in System ON mode. */
#define POWER_RAM_POWER_S0POWER_Pos (0UL) /*!< Position of S0POWER field. */
#define POWER_RAM_POWER_S0POWER_Msk (0x1UL << POWER_RAM_POWER_S0POWER_Pos) /*!< Bit mask of S0POWER field. */
#define POWER_RAM_POWER_S0POWER_Off (0UL) /*!< Off */
#define POWER_RAM_POWER_S0POWER_On (1UL) /*!< On */

/* Register: POWER_RAM_POWERSET */
/* Description: Description cluster[0]:  RAM0 power control set register */

/* Bit 31 : Keep retention on RAM section S15 when RAM section is switched off */
#define POWER_RAM_POWERSET_S15RETENTION_Pos (31UL) /*!< Position of S15RETENTION field. */
#define POWER_RAM_POWERSET_S15RETENTION_Msk (0x1UL << POWER_RAM_POWERSET_S15RETENTION_Pos) /*!< Bit mask of S15RETENTION field. */
#define POWER_RAM_POWERSET_S15RETENTION_On (1UL) /*!< On */

/* Bit 30 : Keep retention on RAM section S14 when RAM section is switched off */
#define POWER_RAM_POWERSET_S14RETENTION_Pos (30UL) /*!< Position of S14RETENTION field. */
#define POWER_RAM_POWERSET_S14RETENTION_Msk (0x1UL << POWER_RAM_POWERSET_S14RETENTION_Pos) /*!< Bit mask of S14RETENTION field. */
#define POWER_RAM_POWERSET_S14RETENTION_On (1UL) /*!< On */

/* Bit 29 : Keep retention on RAM section S13 when RAM section is switched off */
#define POWER_RAM_POWERSET_S13RETENTION_Pos (29UL) /*!< Position of S13RETENTION field. */
#define POWER_RAM_POWERSET_S13RETENTION_Msk (0x1UL << POWER_RAM_POWERSET_S13RETENTION_Pos) /*!< Bit mask of S13RETENTION field. */
#define POWER_RAM_POWERSET_S13RETENTION_On (1UL) /*!< On */

/* Bit 28 : Keep retention on RAM section S12 when RAM section is switched off */
#define POWER_RAM_POWERSET_S12RETENTION_Pos (28UL) /*!< Position of S12RETENTION field. */
#define POWER_RAM_POWERSET_S12RETENTION_Msk (0x1UL << POWER_RAM_POWERSET_S12RETENTION_Pos) /*!< Bit mask of S12RETENTION field. */
#define POWER_RAM_POWERSET_S12RETENTION_On (1UL) /*!< On */

/* Bit 27 : Keep retention on RAM section S11 when RAM section is switched off */
#define POWER_RAM_POWERSET_S11RETENTION_Pos (27UL) /*!< Position of S11RETENTION field. */
#define POWER_RAM_POWERSET_S11RETENTION_Msk (0x1UL << POWER_RAM_POWERSET_S11RETENTION_Pos) /*!< Bit mask of S11RETENTION field. */
#define POWER_RAM_POWERSET_S11RETENTION_On (1UL) /*!< On */

/* Bit 26 : Keep retention on RAM section S10 when RAM section is switched off */
#define POWER_RAM_POWERSET_S10RETENTION_Pos (26UL) /*!< Position of S10RETENTION field. */
#define POWER_RAM_POWERSET_S10RETENTION_Msk (0x1UL << POWER_RAM_POWERSET_S10RETENTION_Pos) /*!< Bit mask of S10RETENTION field. */
#define POWER_RAM_POWERSET_S10RETENTION_On (1UL) /*!< On */

/* Bit 25 : Keep retention on RAM section S9 when RAM section is switched off */
#define POWER_RAM_POWERSET_S9RETENTION_Pos (25UL) /*!< Position of S9RETENTION field. */
#define POWER_RAM_POWERSET_S9RETENTION_Msk (0x1UL << POWER_RAM_POWERSET_S9RETENTION_Pos) /*!< Bit mask of S9RETENTION field. */
#define POWER_RAM_POWERSET_S9RETENTION_On (1UL) /*!< On */

/* Bit 24 : Keep retention on RAM section S8 when RAM section is switched off */
#define POWER_RAM_POWERSET_S8RETENTION_Pos (24UL) /*!< Position of S8RETENTION field. */
#define POWER_RAM_POWERSET_S8RETENTION_Msk (0x1UL << POWER_RAM_POWERSET_S8RETENTION_Pos) /*!< Bit mask of S8RETENTION field. */
#define POWER_RAM_POWERSET_S8RETENTION_On (1UL) /*!< On */

/* Bit 23 : Keep retention on RAM section S7 when RAM section is switched off */
#define POWER_RAM_POWERSET_S7RETENTION_Pos (23UL) /*!< Position of S7RETENTION field. */
#define POWER_RAM_POWERSET_S7RETENTION_Msk (0x1UL << POWER_RAM_POWERSET_S7RETENTION_Pos) /*!< Bit mask of S7RETENTION field. */
#define POWER_RAM_POWERSET_S7RETENTION_On (1UL) /*!< On */

/* Bit 22 : Keep retention on RAM section S6 when RAM section is switched off */
#define POWER_RAM_POWERSET_S6RETENTION_Pos (22UL) /*!< Position of S6RETENTION field. */
#define POWER_RAM_POWERSET_S6RETENTION_Msk (0x1UL << POWER_RAM_POWERSET_S6RETENTION_Pos) /*!< Bit mask of S6RETENTION field. */
#define POWER_RAM_POWERSET_S6RETENTION_On (1UL) /*!< On */

/* Bit 21 : Keep retention on RAM section S5 when RAM section is switched off */
#define POWER_RAM_POWERSET_S5RETENTION_Pos (21UL) /*!< Position of S5RETENTION field. */
#define POWER_RAM_POWERSET_S5RETENTION_Msk (0x1UL << POWER_RAM_POWERSET_S5RETENTION_Pos) /*!< Bit mask of S5RETENTION field. */
#define POWER_RAM_POWERSET_S5RETENTION_On (1UL) /*!< On */

/* Bit 20 : Keep retention on RAM section S4 when RAM section is switched off */
#define POWER_RAM_POWERSET_S4RETENTION_Pos (20UL) /*!< Position of S4RETENTION field. */
#define POWER_RAM_POWERSET_S4RETENTION_Msk (0x1UL << POWER_RAM_POWERSET_S4RETENTION_Pos) /*!< Bit mask of S4RETENTION field. */
#define POWER_RAM_POWERSET_S4RETENTION_On (1UL) /*!< On */

/* Bit 19 : Keep retention on RAM section S3 when RAM section is switched off */
#define POWER_RAM_POWERSET_S3RETENTION_Pos (19UL) /*!< Position of S3RETENTION field. */
#define POWER_RAM_POWERSET_S3RETENTION_Msk (0x1UL << POWER_RAM_POWERSET_S3RETENTION_Pos) /*!< Bit mask of S3RETENTION field. */
#define POWER_RAM_POWERSET_S3RETENTION_On (1UL) /*!< On */

/* Bit 18 : Keep retention on RAM section S2 when RAM section is switched off */
#define POWER_RAM_POWERSET_S2RETENTION_Pos (18UL) /*!< Position of S2RETENTION field. */
#define POWER_RAM_POWERSET_S2RETENTION_Msk (0x1UL << POWER_RAM_POWERSET_S2RETENTION_Pos) /*!< Bit mask of S2RETENTION field. */
#define POWER_RAM_POWERSET_S2RETENTION_On (1UL) /*!< On */

/* Bit 17 : Keep retention on RAM section S1 when RAM section is switched off */
#define POWER_RAM_POWERSET_S1RETENTION_Pos (17UL) /*!< Position of S1RETENTION field. */
#define POWER_RAM_POWERSET_S1RETENTION_Msk (0x1UL << POWER_RAM_POWERSET_S1RETENTION_Pos) /*!< Bit mask of S1RETENTION field. */
#define POWER_RAM_POWERSET_S1RETENTION_On (1UL) /*!< On */

/* Bit 16 : Keep retention on RAM section S0 when RAM section is switched off */
#define POWER_RAM_POWERSET_S0RETENTION_Pos (16UL) /*!< Position of S0RETENTION field. */
#define POWER_RAM_POWERSET_S0RETENTION_Msk (0x1UL << POWER_RAM_POWERSET_S0RETENTION_Pos) /*!< Bit mask of S0RETENTION field. */
#define POWER_RAM_POWERSET_S0RETENTION_On (1UL) /*!< On */

/* Bit 15 : Keep RAM section S15 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERSET_S15POWER_Pos (15UL) /*!< Position of S15POWER field. */
#define POWER_RAM_POWERSET_S15POWER_Msk (0x1UL << POWER_RAM_POWERSET_S15POWER_Pos) /*!< Bit mask of S15POWER field. */
#define POWER_RAM_POWERSET_S15POWER_On (1UL) /*!< On */

/* Bit 14 : Keep RAM section S14 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERSET_S14POWER_Pos (14UL) /*!< Position of S14POWER field. */
#define POWER_RAM_POWERSET_S14POWER_Msk (0x1UL << POWER_RAM_POWERSET_S14POWER_Pos) /*!< Bit mask of S14POWER field. */
#define POWER_RAM_POWERSET_S14POWER_On (1UL) /*!< On */

/* Bit 13 : Keep RAM section S13 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERSET_S13POWER_Pos (13UL) /*!< Position of S13POWER field. */
#define POWER_RAM_POWERSET_S13POWER_Msk (0x1UL << POWER_RAM_POWERSET_S13POWER_Pos) /*!< Bit mask of S13POWER field. */
#define POWER_RAM_POWERSET_S13POWER_On (1UL) /*!< On */

/* Bit 12 : Keep RAM section S12 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERSET_S12POWER_Pos (12UL) /*!< Position of S12POWER field. */
#define POWER_RAM_POWERSET_S12POWER_Msk (0x1UL << POWER_RAM_POWERSET_S12POWER_Pos) /*!< Bit mask of S12POWER field. */
#define POWER_RAM_POWERSET_S12POWER_On (1UL) /*!< On */

/* Bit 11 : Keep RAM section S11 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERSET_S11POWER_Pos (11UL) /*!< Position of S11POWER field. */
#define POWER_RAM_POWERSET_S11POWER_Msk (0x1UL << POWER_RAM_POWERSET_S11POWER_Pos) /*!< Bit mask of S11POWER field. */
#define POWER_RAM_POWERSET_S11POWER_On (1UL) /*!< On */

/* Bit 10 : Keep RAM section S10 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERSET_S10POWER_Pos (10UL) /*!< Position of S10POWER field. */
#define POWER_RAM_POWERSET_S10POWER_Msk (0x1UL << POWER_RAM_POWERSET_S10POWER_Pos) /*!< Bit mask of S10POWER field. */
#define POWER_RAM_POWERSET_S10POWER_On (1UL) /*!< On */

/* Bit 9 : Keep RAM section S9 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERSET_S9POWER_Pos (9UL) /*!< Position of S9POWER field. */
#define POWER_RAM_POWERSET_S9POWER_Msk (0x1UL << POWER_RAM_POWERSET_S9POWER_Pos) /*!< Bit mask of S9POWER field. */
#define POWER_RAM_POWERSET_S9POWER_On (1UL) /*!< On */

/* Bit 8 : Keep RAM section S8 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERSET_S8POWER_Pos (8UL) /*!< Position of S8POWER field. */
#define POWER_RAM_POWERSET_S8POWER_Msk (0x1UL << POWER_RAM_POWERSET_S8POWER_Pos) /*!< Bit mask of S8POWER field. */
#define POWER_RAM_POWERSET_S8POWER_On (1UL) /*!< On */

/* Bit 7 : Keep RAM section S7 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERSET_S7POWER_Pos (7UL) /*!< Position of S7POWER field. */
#define POWER_RAM_POWERSET_S7POWER_Msk (0x1UL << POWER_RAM_POWERSET_S7POWER_Pos) /*!< Bit mask of S7POWER field. */
#define POWER_RAM_POWERSET_S7POWER_On (1UL) /*!< On */

/* Bit 6 : Keep RAM section S6 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERSET_S6POWER_Pos (6UL) /*!< Position of S6POWER field. */
#define POWER_RAM_POWERSET_S6POWER_Msk (0x1UL << POWER_RAM_POWERSET_S6POWER_Pos) /*!< Bit mask of S6POWER field. */
#define POWER_RAM_POWERSET_S6POWER_On (1UL) /*!< On */

/* Bit 5 : Keep RAM section S5 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERSET_S5POWER_Pos (5UL) /*!< Position of S5POWER field. */
#define POWER_RAM_POWERSET_S5POWER_Msk (0x1UL << POWER_RAM_POWERSET_S5POWER_Pos) /*!< Bit mask of S5POWER field. */
#define POWER_RAM_POWERSET_S5POWER_On (1UL) /*!< On */

/* Bit 4 : Keep RAM section S4 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERSET_S4POWER_Pos (4UL) /*!< Position of S4POWER field. */
#define POWER_RAM_POWERSET_S4POWER_Msk (0x1UL << POWER_RAM_POWERSET_S4POWER_Pos) /*!< Bit mask of S4POWER field. */
#define POWER_RAM_POWERSET_S4POWER_On (1UL) /*!< On */

/* Bit 3 : Keep RAM section S3 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERSET_S3POWER_Pos (3UL) /*!< Position of S3POWER field. */
#define POWER_RAM_POWERSET_S3POWER_Msk (0x1UL << POWER_RAM_POWERSET_S3POWER_Pos) /*!< Bit mask of S3POWER field. */
#define POWER_RAM_POWERSET_S3POWER_On (1UL) /*!< On */

/* Bit 2 : Keep RAM section S2 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERSET_S2POWER_Pos (2UL) /*!< Position of S2POWER field. */
#define POWER_RAM_POWERSET_S2POWER_Msk (0x1UL << POWER_RAM_POWERSET_S2POWER_Pos) /*!< Bit mask of S2POWER field. */
#define POWER_RAM_POWERSET_S2POWER_On (1UL) /*!< On */

/* Bit 1 : Keep RAM section S1 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERSET_S1POWER_Pos (1UL) /*!< Position of S1POWER field. */
#define POWER_RAM_POWERSET_S1POWER_Msk (0x1UL << POWER_RAM_POWERSET_S1POWER_Pos) /*!< Bit mask of S1POWER field. */
#define POWER_RAM_POWERSET_S1POWER_On (1UL) /*!< On */

/* Bit 0 : Keep RAM section S0 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERSET_S0POWER_Pos (0UL) /*!< Position of S0POWER field. */
#define POWER_RAM_POWERSET_S0POWER_Msk (0x1UL << POWER_RAM_POWERSET_S0POWER_Pos) /*!< Bit mask of S0POWER field. */
#define POWER_RAM_POWERSET_S0POWER_On (1UL) /*!< On */

/* Register: POWER_RAM_POWERCLR */
/* Description: Description cluster[0]:  RAM0 power control clear register */

/* Bit 31 : Keep retention on RAM section S15 when RAM section is switched off */
#define POWER_RAM_POWERCLR_S15RETENTION_Pos (31UL) /*!< Position of S15RETENTION field. */
#define POWER_RAM_POWERCLR_S15RETENTION_Msk (0x1UL << POWER_RAM_POWERCLR_S15RETENTION_Pos) /*!< Bit mask of S15RETENTION field. */
#define POWER_RAM_POWERCLR_S15RETENTION_Off (1UL) /*!< Off */

/* Bit 30 : Keep retention on RAM section S14 when RAM section is switched off */
#define POWER_RAM_POWERCLR_S14RETENTION_Pos (30UL) /*!< Position of S14RETENTION field. */
#define POWER_RAM_POWERCLR_S14RETENTION_Msk (0x1UL << POWER_RAM_POWERCLR_S14RETENTION_Pos) /*!< Bit mask of S14RETENTION field. */
#define POWER_RAM_POWERCLR_S14RETENTION_Off (1UL) /*!< Off */

/* Bit 29 : Keep retention on RAM section S13 when RAM section is switched off */
#define POWER_RAM_POWERCLR_S13RETENTION_Pos (29UL) /*!< Position of S13RETENTION field. */
#define POWER_RAM_POWERCLR_S13RETENTION_Msk (0x1UL << POWER_RAM_POWERCLR_S13RETENTION_Pos) /*!< Bit mask of S13RETENTION field. */
#define POWER_RAM_POWERCLR_S13RETENTION_Off (1UL) /*!< Off */

/* Bit 28 : Keep retention on RAM section S12 when RAM section is switched off */
#define POWER_RAM_POWERCLR_S12RETENTION_Pos (28UL) /*!< Position of S12RETENTION field. */
#define POWER_RAM_POWERCLR_S12RETENTION_Msk (0x1UL << POWER_RAM_POWERCLR_S12RETENTION_Pos) /*!< Bit mask of S12RETENTION field. */
#define POWER_RAM_POWERCLR_S12RETENTION_Off (1UL) /*!< Off */

/* Bit 27 : Keep retention on RAM section S11 when RAM section is switched off */
#define POWER_RAM_POWERCLR_S11RETENTION_Pos (27UL) /*!< Position of S11RETENTION field. */
#define POWER_RAM_POWERCLR_S11RETENTION_Msk (0x1UL << POWER_RAM_POWERCLR_S11RETENTION_Pos) /*!< Bit mask of S11RETENTION field. */
#define POWER_RAM_POWERCLR_S11RETENTION_Off (1UL) /*!< Off */

/* Bit 26 : Keep retention on RAM section S10 when RAM section is switched off */
#define POWER_RAM_POWERCLR_S10RETENTION_Pos (26UL) /*!< Position of S10RETENTION field. */
#define POWER_RAM_POWERCLR_S10RETENTION_Msk (0x1UL << POWER_RAM_POWERCLR_S10RETENTION_Pos) /*!< Bit mask of S10RETENTION field. */
#define POWER_RAM_POWERCLR_S10RETENTION_Off (1UL) /*!< Off */

/* Bit 25 : Keep retention on RAM section S9 when RAM section is switched off */
#define POWER_RAM_POWERCLR_S9RETENTION_Pos (25UL) /*!< Position of S9RETENTION field. */
#define POWER_RAM_POWERCLR_S9RETENTION_Msk (0x1UL << POWER_RAM_POWERCLR_S9RETENTION_Pos) /*!< Bit mask of S9RETENTION field. */
#define POWER_RAM_POWERCLR_S9RETENTION_Off (1UL) /*!< Off */

/* Bit 24 : Keep retention on RAM section S8 when RAM section is switched off */
#define POWER_RAM_POWERCLR_S8RETENTION_Pos (24UL) /*!< Position of S8RETENTION field. */
#define POWER_RAM_POWERCLR_S8RETENTION_Msk (0x1UL << POWER_RAM_POWERCLR_S8RETENTION_Pos) /*!< Bit mask of S8RETENTION field. */
#define POWER_RAM_POWERCLR_S8RETENTION_Off (1UL) /*!< Off */

/* Bit 23 : Keep retention on RAM section S7 when RAM section is switched off */
#define POWER_RAM_POWERCLR_S7RETENTION_Pos (23UL) /*!< Position of S7RETENTION field. */
#define POWER_RAM_POWERCLR_S7RETENTION_Msk (0x1UL << POWER_RAM_POWERCLR_S7RETENTION_Pos) /*!< Bit mask of S7RETENTION field. */
#define POWER_RAM_POWERCLR_S7RETENTION_Off (1UL) /*!< Off */

/* Bit 22 : Keep retention on RAM section S6 when RAM section is switched off */
#define POWER_RAM_POWERCLR_S6RETENTION_Pos (22UL) /*!< Position of S6RETENTION field. */
#define POWER_RAM_POWERCLR_S6RETENTION_Msk (0x1UL << POWER_RAM_POWERCLR_S6RETENTION_Pos) /*!< Bit mask of S6RETENTION field. */
#define POWER_RAM_POWERCLR_S6RETENTION_Off (1UL) /*!< Off */

/* Bit 21 : Keep retention on RAM section S5 when RAM section is switched off */
#define POWER_RAM_POWERCLR_S5RETENTION_Pos (21UL) /*!< Position of S5RETENTION field. */
#define POWER_RAM_POWERCLR_S5RETENTION_Msk (0x1UL << POWER_RAM_POWERCLR_S5RETENTION_Pos) /*!< Bit mask of S5RETENTION field. */
#define POWER_RAM_POWERCLR_S5RETENTION_Off (1UL) /*!< Off */

/* Bit 20 : Keep retention on RAM section S4 when RAM section is switched off */
#define POWER_RAM_POWERCLR_S4RETENTION_Pos (20UL) /*!< Position of S4RETENTION field. */
#define POWER_RAM_POWERCLR_S4RETENTION_Msk (0x1UL << POWER_RAM_POWERCLR_S4RETENTION_Pos) /*!< Bit mask of S4RETENTION field. */
#define POWER_RAM_POWERCLR_S4RETENTION_Off (1UL) /*!< Off */

/* Bit 19 : Keep retention on RAM section S3 when RAM section is switched off */
#define POWER_RAM_POWERCLR_S3RETENTION_Pos (19UL) /*!< Position of S3RETENTION field. */
#define POWER_RAM_POWERCLR_S3RETENTION_Msk (0x1UL << POWER_RAM_POWERCLR_S3RETENTION_Pos) /*!< Bit mask of S3RETENTION field. */
#define POWER_RAM_POWERCLR_S3RETENTION_Off (1UL) /*!< Off */

/* Bit 18 : Keep retention on RAM section S2 when RAM section is switched off */
#define POWER_RAM_POWERCLR_S2RETENTION_Pos (18UL) /*!< Position of S2RETENTION field. */
#define POWER_RAM_POWERCLR_S2RETENTION_Msk (0x1UL << POWER_RAM_POWERCLR_S2RETENTION_Pos) /*!< Bit mask of S2RETENTION field. */
#define POWER_RAM_POWERCLR_S2RETENTION_Off (1UL) /*!< Off */

/* Bit 17 : Keep retention on RAM section S1 when RAM section is switched off */
#define POWER_RAM_POWERCLR_S1RETENTION_Pos (17UL) /*!< Position of S1RETENTION field. */
#define POWER_RAM_POWERCLR_S1RETENTION_Msk (0x1UL << POWER_RAM_POWERCLR_S1RETENTION_Pos) /*!< Bit mask of S1RETENTION field. */
#define POWER_RAM_POWERCLR_S1RETENTION_Off (1UL) /*!< Off */

/* Bit 16 : Keep retention on RAM section S0 when RAM section is switched off */
#define POWER_RAM_POWERCLR_S0RETENTION_Pos (16UL) /*!< Position of S0RETENTION field. */
#define POWER_RAM_POWERCLR_S0RETENTION_Msk (0x1UL << POWER_RAM_POWERCLR_S0RETENTION_Pos) /*!< Bit mask of S0RETENTION field. */
#define POWER_RAM_POWERCLR_S0RETENTION_Off (1UL) /*!< Off */

/* Bit 15 : Keep RAM section S15 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERCLR_S15POWER_Pos (15UL) /*!< Position of S15POWER field. */
#define POWER_RAM_POWERCLR_S15POWER_Msk (0x1UL << POWER_RAM_POWERCLR_S15POWER_Pos) /*!< Bit mask of S15POWER field. */
#define POWER_RAM_POWERCLR_S15POWER_Off (1UL) /*!< Off */

/* Bit 14 : Keep RAM section S14 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERCLR_S14POWER_Pos (14UL) /*!< Position of S14POWER field. */
#define POWER_RAM_POWERCLR_S14POWER_Msk (0x1UL << POWER_RAM_POWERCLR_S14POWER_Pos) /*!< Bit mask of S14POWER field. */
#define POWER_RAM_POWERCLR_S14POWER_Off (1UL) /*!< Off */

/* Bit 13 : Keep RAM section S13 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERCLR_S13POWER_Pos (13UL) /*!< Position of S13POWER field. */
#define POWER_RAM_POWERCLR_S13POWER_Msk (0x1UL << POWER_RAM_POWERCLR_S13POWER_Pos) /*!< Bit mask of S13POWER field. */
#define POWER_RAM_POWERCLR_S13POWER_Off (1UL) /*!< Off */

/* Bit 12 : Keep RAM section S12 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERCLR_S12POWER_Pos (12UL) /*!< Position of S12POWER field. */
#define POWER_RAM_POWERCLR_S12POWER_Msk (0x1UL << POWER_RAM_POWERCLR_S12POWER_Pos) /*!< Bit mask of S12POWER field. */
#define POWER_RAM_POWERCLR_S12POWER_Off (1UL) /*!< Off */

/* Bit 11 : Keep RAM section S11 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERCLR_S11POWER_Pos (11UL) /*!< Position of S11POWER field. */
#define POWER_RAM_POWERCLR_S11POWER_Msk (0x1UL << POWER_RAM_POWERCLR_S11POWER_Pos) /*!< Bit mask of S11POWER field. */
#define POWER_RAM_POWERCLR_S11POWER_Off (1UL) /*!< Off */

/* Bit 10 : Keep RAM section S10 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERCLR_S10POWER_Pos (10UL) /*!< Position of S10POWER field. */
#define POWER_RAM_POWERCLR_S10POWER_Msk (0x1UL << POWER_RAM_POWERCLR_S10POWER_Pos) /*!< Bit mask of S10POWER field. */
#define POWER_RAM_POWERCLR_S10POWER_Off (1UL) /*!< Off */

/* Bit 9 : Keep RAM section S9 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERCLR_S9POWER_Pos (9UL) /*!< Position of S9POWER field. */
#define POWER_RAM_POWERCLR_S9POWER_Msk (0x1UL << POWER_RAM_POWERCLR_S9POWER_Pos) /*!< Bit mask of S9POWER field. */
#define POWER_RAM_POWERCLR_S9POWER_Off (1UL) /*!< Off */

/* Bit 8 : Keep RAM section S8 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERCLR_S8POWER_Pos (8UL) /*!< Position of S8POWER field. */
#define POWER_RAM_POWERCLR_S8POWER_Msk (0x1UL << POWER_RAM_POWERCLR_S8POWER_Pos) /*!< Bit mask of S8POWER field. */
#define POWER_RAM_POWERCLR_S8POWER_Off (1UL) /*!< Off */

/* Bit 7 : Keep RAM section S7 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERCLR_S7POWER_Pos (7UL) /*!< Position of S7POWER field. */
#define POWER_RAM_POWERCLR_S7POWER_Msk (0x1UL << POWER_RAM_POWERCLR_S7POWER_Pos) /*!< Bit mask of S7POWER field. */
#define POWER_RAM_POWERCLR_S7POWER_Off (1UL) /*!< Off */

/* Bit 6 : Keep RAM section S6 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERCLR_S6POWER_Pos (6UL) /*!< Position of S6POWER field. */
#define POWER_RAM_POWERCLR_S6POWER_Msk (0x1UL << POWER_RAM_POWERCLR_S6POWER_Pos) /*!< Bit mask of S6POWER field. */
#define POWER_RAM_POWERCLR_S6POWER_Off (1UL) /*!< Off */

/* Bit 5 : Keep RAM section S5 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERCLR_S5POWER_Pos (5UL) /*!< Position of S5POWER field. */
#define POWER_RAM_POWERCLR_S5POWER_Msk (0x1UL << POWER_RAM_POWERCLR_S5POWER_Pos) /*!< Bit mask of S5POWER field. */
#define POWER_RAM_POWERCLR_S5POWER_Off (1UL) /*!< Off */

/* Bit 4 : Keep RAM section S4 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERCLR_S4POWER_Pos (4UL) /*!< Position of S4POWER field. */
#define POWER_RAM_POWERCLR_S4POWER_Msk (0x1UL << POWER_RAM_POWERCLR_S4POWER_Pos) /*!< Bit mask of S4POWER field. */
#define POWER_RAM_POWERCLR_S4POWER_Off (1UL) /*!< Off */

/* Bit 3 : Keep RAM section S3 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERCLR_S3POWER_Pos (3UL) /*!< Position of S3POWER field. */
#define POWER_RAM_POWERCLR_S3POWER_Msk (0x1UL << POWER_RAM_POWERCLR_S3POWER_Pos) /*!< Bit mask of S3POWER field. */
#define POWER_RAM_POWERCLR_S3POWER_Off (1UL) /*!< Off */

/* Bit 2 : Keep RAM section S2 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERCLR_S2POWER_Pos (2UL) /*!< Position of S2POWER field. */
#define POWER_RAM_POWERCLR_S2POWER_Msk (0x1UL << POWER_RAM_POWERCLR_S2POWER_Pos) /*!< Bit mask of S2POWER field. */
#define POWER_RAM_POWERCLR_S2POWER_Off (1UL) /*!< Off */

/* Bit 1 : Keep RAM section S1 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERCLR_S1POWER_Pos (1UL) /*!< Position of S1POWER field. */
#define POWER_RAM_POWERCLR_S1POWER_Msk (0x1UL << POWER_RAM_POWERCLR_S1POWER_Pos) /*!< Bit mask of S1POWER field. */
#define POWER_RAM_POWERCLR_S1POWER_Off (1UL) /*!< Off */

/* Bit 0 : Keep RAM section S0 of RAM0 on or off in System ON mode */
#define POWER_RAM_POWERCLR_S0POWER_Pos (0UL) /*!< Position of S0POWER field. */
#define POWER_RAM_POWERCLR_S0POWER_Msk (0x1UL << POWER_RAM_POWERCLR_S0POWER_Pos) /*!< Bit mask of S0POWER field. */
#define POWER_RAM_POWERCLR_S0POWER_Off (1UL) /*!< Off */


/* Peripheral: PPI */
/* Description: Programmable Peripheral Interconnect */

/* Register: PPI_CHEN */
/* Description: Channel enable register */

/* Bit 31 : Enable or disable channel 31 */
#define PPI_CHEN_CH31_Pos (31UL) /*!< Position of CH31 field. */
#define PPI_CHEN_CH31_Msk (0x1UL << PPI_CHEN_CH31_Pos) /*!< Bit mask of CH31 field. */
#define PPI_CHEN_CH31_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH31_Enabled (1UL) /*!< Enable channel */

/* Bit 30 : Enable or disable channel 30 */
#define PPI_CHEN_CH30_Pos (30UL) /*!< Position of CH30 field. */
#define PPI_CHEN_CH30_Msk (0x1UL << PPI_CHEN_CH30_Pos) /*!< Bit mask of CH30 field. */
#define PPI_CHEN_CH30_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH30_Enabled (1UL) /*!< Enable channel */

/* Bit 29 : Enable or disable channel 29 */
#define PPI_CHEN_CH29_Pos (29UL) /*!< Position of CH29 field. */
#define PPI_CHEN_CH29_Msk (0x1UL << PPI_CHEN_CH29_Pos) /*!< Bit mask of CH29 field. */
#define PPI_CHEN_CH29_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH29_Enabled (1UL) /*!< Enable channel */

/* Bit 28 : Enable or disable channel 28 */
#define PPI_CHEN_CH28_Pos (28UL) /*!< Position of CH28 field. */
#define PPI_CHEN_CH28_Msk (0x1UL << PPI_CHEN_CH28_Pos) /*!< Bit mask of CH28 field. */
#define PPI_CHEN_CH28_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH28_Enabled (1UL) /*!< Enable channel */

/* Bit 27 : Enable or disable channel 27 */
#define PPI_CHEN_CH27_Pos (27UL) /*!< Position of CH27 field. */
#define PPI_CHEN_CH27_Msk (0x1UL << PPI_CHEN_CH27_Pos) /*!< Bit mask of CH27 field. */
#define PPI_CHEN_CH27_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH27_Enabled (1UL) /*!< Enable channel */

/* Bit 26 : Enable or disable channel 26 */
#define PPI_CHEN_CH26_Pos (26UL) /*!< Position of CH26 field. */
#define PPI_CHEN_CH26_Msk (0x1UL << PPI_CHEN_CH26_Pos) /*!< Bit mask of CH26 field. */
#define PPI_CHEN_CH26_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH26_Enabled (1UL) /*!< Enable channel */

/* Bit 25 : Enable or disable channel 25 */
#define PPI_CHEN_CH25_Pos (25UL) /*!< Position of CH25 field. */
#define PPI_CHEN_CH25_Msk (0x1UL << PPI_CHEN_CH25_Pos) /*!< Bit mask of CH25 field. */
#define PPI_CHEN_CH25_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH25_Enabled (1UL) /*!< Enable channel */

/* Bit 24 : Enable or disable channel 24 */
#define PPI_CHEN_CH24_Pos (24UL) /*!< Position of CH24 field. */
#define PPI_CHEN_CH24_Msk (0x1UL << PPI_CHEN_CH24_Pos) /*!< Bit mask of CH24 field. */
#define PPI_CHEN_CH24_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH24_Enabled (1UL) /*!< Enable channel */

/* Bit 23 : Enable or disable channel 23 */
#define PPI_CHEN_CH23_Pos (23UL) /*!< Position of CH23 field. */
#define PPI_CHEN_CH23_Msk (0x1UL << PPI_CHEN_CH23_Pos) /*!< Bit mask of CH23 field. */
#define PPI_CHEN_CH23_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH23_Enabled (1UL) /*!< Enable channel */

/* Bit 22 : Enable or disable channel 22 */
#define PPI_CHEN_CH22_Pos (22UL) /*!< Position of CH22 field. */
#define PPI_CHEN_CH22_Msk (0x1UL << PPI_CHEN_CH22_Pos) /*!< Bit mask of CH22 field. */
#define PPI_CHEN_CH22_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH22_Enabled (1UL) /*!< Enable channel */

/* Bit 21 : Enable or disable channel 21 */
#define PPI_CHEN_CH21_Pos (21UL) /*!< Position of CH21 field. */
#define PPI_CHEN_CH21_Msk (0x1UL << PPI_CHEN_CH21_Pos) /*!< Bit mask of CH21 field. */
#define PPI_CHEN_CH21_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH21_Enabled (1UL) /*!< Enable channel */

/* Bit 20 : Enable or disable channel 20 */
#define PPI_CHEN_CH20_Pos (20UL) /*!< Position of CH20 field. */
#define PPI_CHEN_CH20_Msk (0x1UL << PPI_CHEN_CH20_Pos) /*!< Bit mask of CH20 field. */
#define PPI_CHEN_CH20_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH20_Enabled (1UL) /*!< Enable channel */

/* Bit 19 : Enable or disable channel 19 */
#define PPI_CHEN_CH19_Pos (19UL) /*!< Position of CH19 field. */
#define PPI_CHEN_CH19_Msk (0x1UL << PPI_CHEN_CH19_Pos) /*!< Bit mask of CH19 field. */
#define PPI_CHEN_CH19_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH19_Enabled (1UL) /*!< Enable channel */

/* Bit 18 : Enable or disable channel 18 */
#define PPI_CHEN_CH18_Pos (18UL) /*!< Position of CH18 field. */
#define PPI_CHEN_CH18_Msk (0x1UL << PPI_CHEN_CH18_Pos) /*!< Bit mask of CH18 field. */
#define PPI_CHEN_CH18_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH18_Enabled (1UL) /*!< Enable channel */

/* Bit 17 : Enable or disable channel 17 */
#define PPI_CHEN_CH17_Pos (17UL) /*!< Position of CH17 field. */
#define PPI_CHEN_CH17_Msk (0x1UL << PPI_CHEN_CH17_Pos) /*!< Bit mask of CH17 field. */
#define PPI_CHEN_CH17_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH17_Enabled (1UL) /*!< Enable channel */

/* Bit 16 : Enable or disable channel 16 */
#define PPI_CHEN_CH16_Pos (16UL) /*!< Position of CH16 field. */
#define PPI_CHEN_CH16_Msk (0x1UL << PPI_CHEN_CH16_Pos) /*!< Bit mask of CH16 field. */
#define PPI_CHEN_CH16_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH16_Enabled (1UL) /*!< Enable channel */

/* Bit 15 : Enable or disable channel 15 */
#define PPI_CHEN_CH15_Pos (15UL) /*!< Position of CH15 field. */
#define PPI_CHEN_CH15_Msk (0x1UL << PPI_CHEN_CH15_Pos) /*!< Bit mask of CH15 field. */
#define PPI_CHEN_CH15_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH15_Enabled (1UL) /*!< Enable channel */

/* Bit 14 : Enable or disable channel 14 */
#define PPI_CHEN_CH14_Pos (14UL) /*!< Position of CH14 field. */
#define PPI_CHEN_CH14_Msk (0x1UL << PPI_CHEN_CH14_Pos) /*!< Bit mask of CH14 field. */
#define PPI_CHEN_CH14_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH14_Enabled (1UL) /*!< Enable channel */

/* Bit 13 : Enable or disable channel 13 */
#define PPI_CHEN_CH13_Pos (13UL) /*!< Position of CH13 field. */
#define PPI_CHEN_CH13_Msk (0x1UL << PPI_CHEN_CH13_Pos) /*!< Bit mask of CH13 field. */
#define PPI_CHEN_CH13_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH13_Enabled (1UL) /*!< Enable channel */

/* Bit 12 : Enable or disable channel 12 */
#define PPI_CHEN_CH12_Pos (12UL) /*!< Position of CH12 field. */
#define PPI_CHEN_CH12_Msk (0x1UL << PPI_CHEN_CH12_Pos) /*!< Bit mask of CH12 field. */
#define PPI_CHEN_CH12_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH12_Enabled (1UL) /*!< Enable channel */

/* Bit 11 : Enable or disable channel 11 */
#define PPI_CHEN_CH11_Pos (11UL) /*!< Position of CH11 field. */
#define PPI_CHEN_CH11_Msk (0x1UL << PPI_CHEN_CH11_Pos) /*!< Bit mask of CH11 field. */
#define PPI_CHEN_CH11_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH11_Enabled (1UL) /*!< Enable channel */

/* Bit 10 : Enable or disable channel 10 */
#define PPI_CHEN_CH10_Pos (10UL) /*!< Position of CH10 field. */
#define PPI_CHEN_CH10_Msk (0x1UL << PPI_CHEN_CH10_Pos) /*!< Bit mask of CH10 field. */
#define PPI_CHEN_CH10_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH10_Enabled (1UL) /*!< Enable channel */

/* Bit 9 : Enable or disable channel 9 */
#define PPI_CHEN_CH9_Pos (9UL) /*!< Position of CH9 field. */
#define PPI_CHEN_CH9_Msk (0x1UL << PPI_CHEN_CH9_Pos) /*!< Bit mask of CH9 field. */
#define PPI_CHEN_CH9_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH9_Enabled (1UL) /*!< Enable channel */

/* Bit 8 : Enable or disable channel 8 */
#define PPI_CHEN_CH8_Pos (8UL) /*!< Position of CH8 field. */
#define PPI_CHEN_CH8_Msk (0x1UL << PPI_CHEN_CH8_Pos) /*!< Bit mask of CH8 field. */
#define PPI_CHEN_CH8_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH8_Enabled (1UL) /*!< Enable channel */

/* Bit 7 : Enable or disable channel 7 */
#define PPI_CHEN_CH7_Pos (7UL) /*!< Position of CH7 field. */
#define PPI_CHEN_CH7_Msk (0x1UL << PPI_CHEN_CH7_Pos) /*!< Bit mask of CH7 field. */
#define PPI_CHEN_CH7_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH7_Enabled (1UL) /*!< Enable channel */

/* Bit 6 : Enable or disable channel 6 */
#define PPI_CHEN_CH6_Pos (6UL) /*!< Position of CH6 field. */
#define PPI_CHEN_CH6_Msk (0x1UL << PPI_CHEN_CH6_Pos) /*!< Bit mask of CH6 field. */
#define PPI_CHEN_CH6_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH6_Enabled (1UL) /*!< Enable channel */

/* Bit 5 : Enable or disable channel 5 */
#define PPI_CHEN_CH5_Pos (5UL) /*!< Position of CH5 field. */
#define PPI_CHEN_CH5_Msk (0x1UL << PPI_CHEN_CH5_Pos) /*!< Bit mask of CH5 field. */
#define PPI_CHEN_CH5_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH5_Enabled (1UL) /*!< Enable channel */

/* Bit 4 : Enable or disable channel 4 */
#define PPI_CHEN_CH4_Pos (4UL) /*!< Position of CH4 field. */
#define PPI_CHEN_CH4_Msk (0x1UL << PPI_CHEN_CH4_Pos) /*!< Bit mask of CH4 field. */
#define PPI_CHEN_CH4_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH4_Enabled (1UL) /*!< Enable channel */

/* Bit 3 : Enable or disable channel 3 */
#define PPI_CHEN_CH3_Pos (3UL) /*!< Position of CH3 field. */
#define PPI_CHEN_CH3_Msk (0x1UL << PPI_CHEN_CH3_Pos) /*!< Bit mask of CH3 field. */
#define PPI_CHEN_CH3_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH3_Enabled (1UL) /*!< Enable channel */

/* Bit 2 : Enable or disable channel 2 */
#define PPI_CHEN_CH2_Pos (2UL) /*!< Position of CH2 field. */
#define PPI_CHEN_CH2_Msk (0x1UL << PPI_CHEN_CH2_Pos) /*!< Bit mask of CH2 field. */
#define PPI_CHEN_CH2_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH2_Enabled (1UL) /*!< Enable channel */

/* Bit 1 : Enable or disable channel 1 */
#define PPI_CHEN_CH1_Pos (1UL) /*!< Position of CH1 field. */
#define PPI_CHEN_CH1_Msk (0x1UL << PPI_CHEN_CH1_Pos) /*!< Bit mask of CH1 field. */
#define PPI_CHEN_CH1_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH1_Enabled (1UL) /*!< Enable channel */

/* Bit 0 : Enable or disable channel 0 */
#define PPI_CHEN_CH0_Pos (0UL) /*!< Position of CH0 field. */
#define PPI_CHEN_CH0_Msk (0x1UL << PPI_CHEN_CH0_Pos) /*!< Bit mask of CH0 field. */
#define PPI_CHEN_CH0_Disabled (0UL) /*!< Disable channel */
#define PPI_CHEN_CH0_Enabled (1UL) /*!< Enable channel */

/* Register: PPI_CHENSET */
/* Description: Channel enable set register */

/* Bit 31 : Channel 31 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH31_Pos (31UL) /*!< Position of CH31 field. */
#define PPI_CHENSET_CH31_Msk (0x1UL << PPI_CHENSET_CH31_Pos) /*!< Bit mask of CH31 field. */
#define PPI_CHENSET_CH31_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH31_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH31_Set (1UL) /*!< Write: Enable channel */

/* Bit 30 : Channel 30 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH30_Pos (30UL) /*!< Position of CH30 field. */
#define PPI_CHENSET_CH30_Msk (0x1UL << PPI_CHENSET_CH30_Pos) /*!< Bit mask of CH30 field. */
#define PPI_CHENSET_CH30_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH30_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH30_Set (1UL) /*!< Write: Enable channel */

/* Bit 29 : Channel 29 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH29_Pos (29UL) /*!< Position of CH29 field. */
#define PPI_CHENSET_CH29_Msk (0x1UL << PPI_CHENSET_CH29_Pos) /*!< Bit mask of CH29 field. */
#define PPI_CHENSET_CH29_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH29_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH29_Set (1UL) /*!< Write: Enable channel */

/* Bit 28 : Channel 28 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH28_Pos (28UL) /*!< Position of CH28 field. */
#define PPI_CHENSET_CH28_Msk (0x1UL << PPI_CHENSET_CH28_Pos) /*!< Bit mask of CH28 field. */
#define PPI_CHENSET_CH28_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH28_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH28_Set (1UL) /*!< Write: Enable channel */

/* Bit 27 : Channel 27 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH27_Pos (27UL) /*!< Position of CH27 field. */
#define PPI_CHENSET_CH27_Msk (0x1UL << PPI_CHENSET_CH27_Pos) /*!< Bit mask of CH27 field. */
#define PPI_CHENSET_CH27_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH27_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH27_Set (1UL) /*!< Write: Enable channel */

/* Bit 26 : Channel 26 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH26_Pos (26UL) /*!< Position of CH26 field. */
#define PPI_CHENSET_CH26_Msk (0x1UL << PPI_CHENSET_CH26_Pos) /*!< Bit mask of CH26 field. */
#define PPI_CHENSET_CH26_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH26_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH26_Set (1UL) /*!< Write: Enable channel */

/* Bit 25 : Channel 25 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH25_Pos (25UL) /*!< Position of CH25 field. */
#define PPI_CHENSET_CH25_Msk (0x1UL << PPI_CHENSET_CH25_Pos) /*!< Bit mask of CH25 field. */
#define PPI_CHENSET_CH25_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH25_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH25_Set (1UL) /*!< Write: Enable channel */

/* Bit 24 : Channel 24 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH24_Pos (24UL) /*!< Position of CH24 field. */
#define PPI_CHENSET_CH24_Msk (0x1UL << PPI_CHENSET_CH24_Pos) /*!< Bit mask of CH24 field. */
#define PPI_CHENSET_CH24_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH24_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH24_Set (1UL) /*!< Write: Enable channel */

/* Bit 23 : Channel 23 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH23_Pos (23UL) /*!< Position of CH23 field. */
#define PPI_CHENSET_CH23_Msk (0x1UL << PPI_CHENSET_CH23_Pos) /*!< Bit mask of CH23 field. */
#define PPI_CHENSET_CH23_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH23_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH23_Set (1UL) /*!< Write: Enable channel */

/* Bit 22 : Channel 22 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH22_Pos (22UL) /*!< Position of CH22 field. */
#define PPI_CHENSET_CH22_Msk (0x1UL << PPI_CHENSET_CH22_Pos) /*!< Bit mask of CH22 field. */
#define PPI_CHENSET_CH22_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH22_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH22_Set (1UL) /*!< Write: Enable channel */

/* Bit 21 : Channel 21 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH21_Pos (21UL) /*!< Position of CH21 field. */
#define PPI_CHENSET_CH21_Msk (0x1UL << PPI_CHENSET_CH21_Pos) /*!< Bit mask of CH21 field. */
#define PPI_CHENSET_CH21_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH21_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH21_Set (1UL) /*!< Write: Enable channel */

/* Bit 20 : Channel 20 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH20_Pos (20UL) /*!< Position of CH20 field. */
#define PPI_CHENSET_CH20_Msk (0x1UL << PPI_CHENSET_CH20_Pos) /*!< Bit mask of CH20 field. */
#define PPI_CHENSET_CH20_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH20_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH20_Set (1UL) /*!< Write: Enable channel */

/* Bit 19 : Channel 19 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH19_Pos (19UL) /*!< Position of CH19 field. */
#define PPI_CHENSET_CH19_Msk (0x1UL << PPI_CHENSET_CH19_Pos) /*!< Bit mask of CH19 field. */
#define PPI_CHENSET_CH19_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH19_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH19_Set (1UL) /*!< Write: Enable channel */

/* Bit 18 : Channel 18 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH18_Pos (18UL) /*!< Position of CH18 field. */
#define PPI_CHENSET_CH18_Msk (0x1UL << PPI_CHENSET_CH18_Pos) /*!< Bit mask of CH18 field. */
#define PPI_CHENSET_CH18_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH18_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH18_Set (1UL) /*!< Write: Enable channel */

/* Bit 17 : Channel 17 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH17_Pos (17UL) /*!< Position of CH17 field. */
#define PPI_CHENSET_CH17_Msk (0x1UL << PPI_CHENSET_CH17_Pos) /*!< Bit mask of CH17 field. */
#define PPI_CHENSET_CH17_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH17_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH17_Set (1UL) /*!< Write: Enable channel */

/* Bit 16 : Channel 16 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH16_Pos (16UL) /*!< Position of CH16 field. */
#define PPI_CHENSET_CH16_Msk (0x1UL << PPI_CHENSET_CH16_Pos) /*!< Bit mask of CH16 field. */
#define PPI_CHENSET_CH16_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH16_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH16_Set (1UL) /*!< Write: Enable channel */

/* Bit 15 : Channel 15 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH15_Pos (15UL) /*!< Position of CH15 field. */
#define PPI_CHENSET_CH15_Msk (0x1UL << PPI_CHENSET_CH15_Pos) /*!< Bit mask of CH15 field. */
#define PPI_CHENSET_CH15_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH15_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH15_Set (1UL) /*!< Write: Enable channel */

/* Bit 14 : Channel 14 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH14_Pos (14UL) /*!< Position of CH14 field. */
#define PPI_CHENSET_CH14_Msk (0x1UL << PPI_CHENSET_CH14_Pos) /*!< Bit mask of CH14 field. */
#define PPI_CHENSET_CH14_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH14_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH14_Set (1UL) /*!< Write: Enable channel */

/* Bit 13 : Channel 13 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH13_Pos (13UL) /*!< Position of CH13 field. */
#define PPI_CHENSET_CH13_Msk (0x1UL << PPI_CHENSET_CH13_Pos) /*!< Bit mask of CH13 field. */
#define PPI_CHENSET_CH13_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH13_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH13_Set (1UL) /*!< Write: Enable channel */

/* Bit 12 : Channel 12 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH12_Pos (12UL) /*!< Position of CH12 field. */
#define PPI_CHENSET_CH12_Msk (0x1UL << PPI_CHENSET_CH12_Pos) /*!< Bit mask of CH12 field. */
#define PPI_CHENSET_CH12_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH12_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH12_Set (1UL) /*!< Write: Enable channel */

/* Bit 11 : Channel 11 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH11_Pos (11UL) /*!< Position of CH11 field. */
#define PPI_CHENSET_CH11_Msk (0x1UL << PPI_CHENSET_CH11_Pos) /*!< Bit mask of CH11 field. */
#define PPI_CHENSET_CH11_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH11_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH11_Set (1UL) /*!< Write: Enable channel */

/* Bit 10 : Channel 10 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH10_Pos (10UL) /*!< Position of CH10 field. */
#define PPI_CHENSET_CH10_Msk (0x1UL << PPI_CHENSET_CH10_Pos) /*!< Bit mask of CH10 field. */
#define PPI_CHENSET_CH10_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH10_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH10_Set (1UL) /*!< Write: Enable channel */

/* Bit 9 : Channel 9 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH9_Pos (9UL) /*!< Position of CH9 field. */
#define PPI_CHENSET_CH9_Msk (0x1UL << PPI_CHENSET_CH9_Pos) /*!< Bit mask of CH9 field. */
#define PPI_CHENSET_CH9_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH9_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH9_Set (1UL) /*!< Write: Enable channel */

/* Bit 8 : Channel 8 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH8_Pos (8UL) /*!< Position of CH8 field. */
#define PPI_CHENSET_CH8_Msk (0x1UL << PPI_CHENSET_CH8_Pos) /*!< Bit mask of CH8 field. */
#define PPI_CHENSET_CH8_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH8_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH8_Set (1UL) /*!< Write: Enable channel */

/* Bit 7 : Channel 7 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH7_Pos (7UL) /*!< Position of CH7 field. */
#define PPI_CHENSET_CH7_Msk (0x1UL << PPI_CHENSET_CH7_Pos) /*!< Bit mask of CH7 field. */
#define PPI_CHENSET_CH7_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH7_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH7_Set (1UL) /*!< Write: Enable channel */

/* Bit 6 : Channel 6 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH6_Pos (6UL) /*!< Position of CH6 field. */
#define PPI_CHENSET_CH6_Msk (0x1UL << PPI_CHENSET_CH6_Pos) /*!< Bit mask of CH6 field. */
#define PPI_CHENSET_CH6_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH6_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH6_Set (1UL) /*!< Write: Enable channel */

/* Bit 5 : Channel 5 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH5_Pos (5UL) /*!< Position of CH5 field. */
#define PPI_CHENSET_CH5_Msk (0x1UL << PPI_CHENSET_CH5_Pos) /*!< Bit mask of CH5 field. */
#define PPI_CHENSET_CH5_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH5_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH5_Set (1UL) /*!< Write: Enable channel */

/* Bit 4 : Channel 4 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH4_Pos (4UL) /*!< Position of CH4 field. */
#define PPI_CHENSET_CH4_Msk (0x1UL << PPI_CHENSET_CH4_Pos) /*!< Bit mask of CH4 field. */
#define PPI_CHENSET_CH4_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH4_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH4_Set (1UL) /*!< Write: Enable channel */

/* Bit 3 : Channel 3 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH3_Pos (3UL) /*!< Position of CH3 field. */
#define PPI_CHENSET_CH3_Msk (0x1UL << PPI_CHENSET_CH3_Pos) /*!< Bit mask of CH3 field. */
#define PPI_CHENSET_CH3_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH3_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH3_Set (1UL) /*!< Write: Enable channel */

/* Bit 2 : Channel 2 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH2_Pos (2UL) /*!< Position of CH2 field. */
#define PPI_CHENSET_CH2_Msk (0x1UL << PPI_CHENSET_CH2_Pos) /*!< Bit mask of CH2 field. */
#define PPI_CHENSET_CH2_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH2_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH2_Set (1UL) /*!< Write: Enable channel */

/* Bit 1 : Channel 1 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH1_Pos (1UL) /*!< Position of CH1 field. */
#define PPI_CHENSET_CH1_Msk (0x1UL << PPI_CHENSET_CH1_Pos) /*!< Bit mask of CH1 field. */
#define PPI_CHENSET_CH1_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH1_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH1_Set (1UL) /*!< Write: Enable channel */

/* Bit 0 : Channel 0 enable set register.  Writing '0' has no effect */
#define PPI_CHENSET_CH0_Pos (0UL) /*!< Position of CH0 field. */
#define PPI_CHENSET_CH0_Msk (0x1UL << PPI_CHENSET_CH0_Pos) /*!< Bit mask of CH0 field. */
#define PPI_CHENSET_CH0_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENSET_CH0_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENSET_CH0_Set (1UL) /*!< Write: Enable channel */

/* Register: PPI_CHENCLR */
/* Description: Channel enable clear register */

/* Bit 31 : Channel 31 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH31_Pos (31UL) /*!< Position of CH31 field. */
#define PPI_CHENCLR_CH31_Msk (0x1UL << PPI_CHENCLR_CH31_Pos) /*!< Bit mask of CH31 field. */
#define PPI_CHENCLR_CH31_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH31_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH31_Clear (1UL) /*!< Write: disable channel */

/* Bit 30 : Channel 30 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH30_Pos (30UL) /*!< Position of CH30 field. */
#define PPI_CHENCLR_CH30_Msk (0x1UL << PPI_CHENCLR_CH30_Pos) /*!< Bit mask of CH30 field. */
#define PPI_CHENCLR_CH30_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH30_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH30_Clear (1UL) /*!< Write: disable channel */

/* Bit 29 : Channel 29 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH29_Pos (29UL) /*!< Position of CH29 field. */
#define PPI_CHENCLR_CH29_Msk (0x1UL << PPI_CHENCLR_CH29_Pos) /*!< Bit mask of CH29 field. */
#define PPI_CHENCLR_CH29_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH29_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH29_Clear (1UL) /*!< Write: disable channel */

/* Bit 28 : Channel 28 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH28_Pos (28UL) /*!< Position of CH28 field. */
#define PPI_CHENCLR_CH28_Msk (0x1UL << PPI_CHENCLR_CH28_Pos) /*!< Bit mask of CH28 field. */
#define PPI_CHENCLR_CH28_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH28_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH28_Clear (1UL) /*!< Write: disable channel */

/* Bit 27 : Channel 27 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH27_Pos (27UL) /*!< Position of CH27 field. */
#define PPI_CHENCLR_CH27_Msk (0x1UL << PPI_CHENCLR_CH27_Pos) /*!< Bit mask of CH27 field. */
#define PPI_CHENCLR_CH27_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH27_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH27_Clear (1UL) /*!< Write: disable channel */

/* Bit 26 : Channel 26 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH26_Pos (26UL) /*!< Position of CH26 field. */
#define PPI_CHENCLR_CH26_Msk (0x1UL << PPI_CHENCLR_CH26_Pos) /*!< Bit mask of CH26 field. */
#define PPI_CHENCLR_CH26_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH26_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH26_Clear (1UL) /*!< Write: disable channel */

/* Bit 25 : Channel 25 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH25_Pos (25UL) /*!< Position of CH25 field. */
#define PPI_CHENCLR_CH25_Msk (0x1UL << PPI_CHENCLR_CH25_Pos) /*!< Bit mask of CH25 field. */
#define PPI_CHENCLR_CH25_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH25_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH25_Clear (1UL) /*!< Write: disable channel */

/* Bit 24 : Channel 24 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH24_Pos (24UL) /*!< Position of CH24 field. */
#define PPI_CHENCLR_CH24_Msk (0x1UL << PPI_CHENCLR_CH24_Pos) /*!< Bit mask of CH24 field. */
#define PPI_CHENCLR_CH24_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH24_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH24_Clear (1UL) /*!< Write: disable channel */

/* Bit 23 : Channel 23 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH23_Pos (23UL) /*!< Position of CH23 field. */
#define PPI_CHENCLR_CH23_Msk (0x1UL << PPI_CHENCLR_CH23_Pos) /*!< Bit mask of CH23 field. */
#define PPI_CHENCLR_CH23_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH23_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH23_Clear (1UL) /*!< Write: disable channel */

/* Bit 22 : Channel 22 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH22_Pos (22UL) /*!< Position of CH22 field. */
#define PPI_CHENCLR_CH22_Msk (0x1UL << PPI_CHENCLR_CH22_Pos) /*!< Bit mask of CH22 field. */
#define PPI_CHENCLR_CH22_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH22_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH22_Clear (1UL) /*!< Write: disable channel */

/* Bit 21 : Channel 21 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH21_Pos (21UL) /*!< Position of CH21 field. */
#define PPI_CHENCLR_CH21_Msk (0x1UL << PPI_CHENCLR_CH21_Pos) /*!< Bit mask of CH21 field. */
#define PPI_CHENCLR_CH21_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH21_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH21_Clear (1UL) /*!< Write: disable channel */

/* Bit 20 : Channel 20 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH20_Pos (20UL) /*!< Position of CH20 field. */
#define PPI_CHENCLR_CH20_Msk (0x1UL << PPI_CHENCLR_CH20_Pos) /*!< Bit mask of CH20 field. */
#define PPI_CHENCLR_CH20_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH20_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH20_Clear (1UL) /*!< Write: disable channel */

/* Bit 19 : Channel 19 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH19_Pos (19UL) /*!< Position of CH19 field. */
#define PPI_CHENCLR_CH19_Msk (0x1UL << PPI_CHENCLR_CH19_Pos) /*!< Bit mask of CH19 field. */
#define PPI_CHENCLR_CH19_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH19_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH19_Clear (1UL) /*!< Write: disable channel */

/* Bit 18 : Channel 18 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH18_Pos (18UL) /*!< Position of CH18 field. */
#define PPI_CHENCLR_CH18_Msk (0x1UL << PPI_CHENCLR_CH18_Pos) /*!< Bit mask of CH18 field. */
#define PPI_CHENCLR_CH18_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH18_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH18_Clear (1UL) /*!< Write: disable channel */

/* Bit 17 : Channel 17 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH17_Pos (17UL) /*!< Position of CH17 field. */
#define PPI_CHENCLR_CH17_Msk (0x1UL << PPI_CHENCLR_CH17_Pos) /*!< Bit mask of CH17 field. */
#define PPI_CHENCLR_CH17_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH17_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH17_Clear (1UL) /*!< Write: disable channel */

/* Bit 16 : Channel 16 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH16_Pos (16UL) /*!< Position of CH16 field. */
#define PPI_CHENCLR_CH16_Msk (0x1UL << PPI_CHENCLR_CH16_Pos) /*!< Bit mask of CH16 field. */
#define PPI_CHENCLR_CH16_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH16_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH16_Clear (1UL) /*!< Write: disable channel */

/* Bit 15 : Channel 15 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH15_Pos (15UL) /*!< Position of CH15 field. */
#define PPI_CHENCLR_CH15_Msk (0x1UL << PPI_CHENCLR_CH15_Pos) /*!< Bit mask of CH15 field. */
#define PPI_CHENCLR_CH15_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH15_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH15_Clear (1UL) /*!< Write: disable channel */

/* Bit 14 : Channel 14 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH14_Pos (14UL) /*!< Position of CH14 field. */
#define PPI_CHENCLR_CH14_Msk (0x1UL << PPI_CHENCLR_CH14_Pos) /*!< Bit mask of CH14 field. */
#define PPI_CHENCLR_CH14_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH14_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH14_Clear (1UL) /*!< Write: disable channel */

/* Bit 13 : Channel 13 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH13_Pos (13UL) /*!< Position of CH13 field. */
#define PPI_CHENCLR_CH13_Msk (0x1UL << PPI_CHENCLR_CH13_Pos) /*!< Bit mask of CH13 field. */
#define PPI_CHENCLR_CH13_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH13_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH13_Clear (1UL) /*!< Write: disable channel */

/* Bit 12 : Channel 12 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH12_Pos (12UL) /*!< Position of CH12 field. */
#define PPI_CHENCLR_CH12_Msk (0x1UL << PPI_CHENCLR_CH12_Pos) /*!< Bit mask of CH12 field. */
#define PPI_CHENCLR_CH12_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH12_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH12_Clear (1UL) /*!< Write: disable channel */

/* Bit 11 : Channel 11 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH11_Pos (11UL) /*!< Position of CH11 field. */
#define PPI_CHENCLR_CH11_Msk (0x1UL << PPI_CHENCLR_CH11_Pos) /*!< Bit mask of CH11 field. */
#define PPI_CHENCLR_CH11_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH11_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH11_Clear (1UL) /*!< Write: disable channel */

/* Bit 10 : Channel 10 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH10_Pos (10UL) /*!< Position of CH10 field. */
#define PPI_CHENCLR_CH10_Msk (0x1UL << PPI_CHENCLR_CH10_Pos) /*!< Bit mask of CH10 field. */
#define PPI_CHENCLR_CH10_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH10_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH10_Clear (1UL) /*!< Write: disable channel */

/* Bit 9 : Channel 9 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH9_Pos (9UL) /*!< Position of CH9 field. */
#define PPI_CHENCLR_CH9_Msk (0x1UL << PPI_CHENCLR_CH9_Pos) /*!< Bit mask of CH9 field. */
#define PPI_CHENCLR_CH9_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH9_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH9_Clear (1UL) /*!< Write: disable channel */

/* Bit 8 : Channel 8 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH8_Pos (8UL) /*!< Position of CH8 field. */
#define PPI_CHENCLR_CH8_Msk (0x1UL << PPI_CHENCLR_CH8_Pos) /*!< Bit mask of CH8 field. */
#define PPI_CHENCLR_CH8_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH8_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH8_Clear (1UL) /*!< Write: disable channel */

/* Bit 7 : Channel 7 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH7_Pos (7UL) /*!< Position of CH7 field. */
#define PPI_CHENCLR_CH7_Msk (0x1UL << PPI_CHENCLR_CH7_Pos) /*!< Bit mask of CH7 field. */
#define PPI_CHENCLR_CH7_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH7_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH7_Clear (1UL) /*!< Write: disable channel */

/* Bit 6 : Channel 6 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH6_Pos (6UL) /*!< Position of CH6 field. */
#define PPI_CHENCLR_CH6_Msk (0x1UL << PPI_CHENCLR_CH6_Pos) /*!< Bit mask of CH6 field. */
#define PPI_CHENCLR_CH6_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH6_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH6_Clear (1UL) /*!< Write: disable channel */

/* Bit 5 : Channel 5 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH5_Pos (5UL) /*!< Position of CH5 field. */
#define PPI_CHENCLR_CH5_Msk (0x1UL << PPI_CHENCLR_CH5_Pos) /*!< Bit mask of CH5 field. */
#define PPI_CHENCLR_CH5_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH5_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH5_Clear (1UL) /*!< Write: disable channel */

/* Bit 4 : Channel 4 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH4_Pos (4UL) /*!< Position of CH4 field. */
#define PPI_CHENCLR_CH4_Msk (0x1UL << PPI_CHENCLR_CH4_Pos) /*!< Bit mask of CH4 field. */
#define PPI_CHENCLR_CH4_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH4_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH4_Clear (1UL) /*!< Write: disable channel */

/* Bit 3 : Channel 3 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH3_Pos (3UL) /*!< Position of CH3 field. */
#define PPI_CHENCLR_CH3_Msk (0x1UL << PPI_CHENCLR_CH3_Pos) /*!< Bit mask of CH3 field. */
#define PPI_CHENCLR_CH3_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH3_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH3_Clear (1UL) /*!< Write: disable channel */

/* Bit 2 : Channel 2 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH2_Pos (2UL) /*!< Position of CH2 field. */
#define PPI_CHENCLR_CH2_Msk (0x1UL << PPI_CHENCLR_CH2_Pos) /*!< Bit mask of CH2 field. */
#define PPI_CHENCLR_CH2_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH2_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH2_Clear (1UL) /*!< Write: disable channel */

/* Bit 1 : Channel 1 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH1_Pos (1UL) /*!< Position of CH1 field. */
#define PPI_CHENCLR_CH1_Msk (0x1UL << PPI_CHENCLR_CH1_Pos) /*!< Bit mask of CH1 field. */
#define PPI_CHENCLR_CH1_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH1_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH1_Clear (1UL) /*!< Write: disable channel */

/* Bit 0 : Channel 0 enable clear register.  Writing '0' has no effect */
#define PPI_CHENCLR_CH0_Pos (0UL) /*!< Position of CH0 field. */
#define PPI_CHENCLR_CH0_Msk (0x1UL << PPI_CHENCLR_CH0_Pos) /*!< Bit mask of CH0 field. */
#define PPI_CHENCLR_CH0_Disabled (0UL) /*!< Read: channel disabled */
#define PPI_CHENCLR_CH0_Enabled (1UL) /*!< Read: channel enabled */
#define PPI_CHENCLR_CH0_Clear (1UL) /*!< Write: disable channel */

/* Register: PPI_CH_EEP */
/* Description: Description cluster[0]:  Channel 0 event end-point */

/* Bits 31..0 : Pointer to event register. Accepts only addresses to registers from the Event group. */
#define PPI_CH_EEP_EEP_Pos (0UL) /*!< Position of EEP field. */
#define PPI_CH_EEP_EEP_Msk (0xFFFFFFFFUL << PPI_CH_EEP_EEP_Pos) /*!< Bit mask of EEP field. */

/* Register: PPI_CH_TEP */
/* Description: Description cluster[0]:  Channel 0 task end-point */

/* Bits 31..0 : Pointer to task register. Accepts only addresses to registers from the Task group. */
#define PPI_CH_TEP_TEP_Pos (0UL) /*!< Position of TEP field. */
#define PPI_CH_TEP_TEP_Msk (0xFFFFFFFFUL << PPI_CH_TEP_TEP_Pos) /*!< Bit mask of TEP field. */

/* Register: PPI_CHG */
/* Description: Description collection[0]:  Channel group 0 */

/* Bit 31 : Include or exclude channel 31 */
#define PPI_CHG_CH31_Pos (31UL) /*!< Position of CH31 field. */
#define PPI_CHG_CH31_Msk (0x1UL << PPI_CHG_CH31_Pos) /*!< Bit mask of CH31 field. */
#define PPI_CHG_CH31_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH31_Included (1UL) /*!< Include */

/* Bit 30 : Include or exclude channel 30 */
#define PPI_CHG_CH30_Pos (30UL) /*!< Position of CH30 field. */
#define PPI_CHG_CH30_Msk (0x1UL << PPI_CHG_CH30_Pos) /*!< Bit mask of CH30 field. */
#define PPI_CHG_CH30_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH30_Included (1UL) /*!< Include */

/* Bit 29 : Include or exclude channel 29 */
#define PPI_CHG_CH29_Pos (29UL) /*!< Position of CH29 field. */
#define PPI_CHG_CH29_Msk (0x1UL << PPI_CHG_CH29_Pos) /*!< Bit mask of CH29 field. */
#define PPI_CHG_CH29_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH29_Included (1UL) /*!< Include */

/* Bit 28 : Include or exclude channel 28 */
#define PPI_CHG_CH28_Pos (28UL) /*!< Position of CH28 field. */
#define PPI_CHG_CH28_Msk (0x1UL << PPI_CHG_CH28_Pos) /*!< Bit mask of CH28 field. */
#define PPI_CHG_CH28_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH28_Included (1UL) /*!< Include */

/* Bit 27 : Include or exclude channel 27 */
#define PPI_CHG_CH27_Pos (27UL) /*!< Position of CH27 field. */
#define PPI_CHG_CH27_Msk (0x1UL << PPI_CHG_CH27_Pos) /*!< Bit mask of CH27 field. */
#define PPI_CHG_CH27_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH27_Included (1UL) /*!< Include */

/* Bit 26 : Include or exclude channel 26 */
#define PPI_CHG_CH26_Pos (26UL) /*!< Position of CH26 field. */
#define PPI_CHG_CH26_Msk (0x1UL << PPI_CHG_CH26_Pos) /*!< Bit mask of CH26 field. */
#define PPI_CHG_CH26_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH26_Included (1UL) /*!< Include */

/* Bit 25 : Include or exclude channel 25 */
#define PPI_CHG_CH25_Pos (25UL) /*!< Position of CH25 field. */
#define PPI_CHG_CH25_Msk (0x1UL << PPI_CHG_CH25_Pos) /*!< Bit mask of CH25 field. */
#define PPI_CHG_CH25_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH25_Included (1UL) /*!< Include */

/* Bit 24 : Include or exclude channel 24 */
#define PPI_CHG_CH24_Pos (24UL) /*!< Position of CH24 field. */
#define PPI_CHG_CH24_Msk (0x1UL << PPI_CHG_CH24_Pos) /*!< Bit mask of CH24 field. */
#define PPI_CHG_CH24_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH24_Included (1UL) /*!< Include */

/* Bit 23 : Include or exclude channel 23 */
#define PPI_CHG_CH23_Pos (23UL) /*!< Position of CH23 field. */
#define PPI_CHG_CH23_Msk (0x1UL << PPI_CHG_CH23_Pos) /*!< Bit mask of CH23 field. */
#define PPI_CHG_CH23_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH23_Included (1UL) /*!< Include */

/* Bit 22 : Include or exclude channel 22 */
#define PPI_CHG_CH22_Pos (22UL) /*!< Position of CH22 field. */
#define PPI_CHG_CH22_Msk (0x1UL << PPI_CHG_CH22_Pos) /*!< Bit mask of CH22 field. */
#define PPI_CHG_CH22_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH22_Included (1UL) /*!< Include */

/* Bit 21 : Include or exclude channel 21 */
#define PPI_CHG_CH21_Pos (21UL) /*!< Position of CH21 field. */
#define PPI_CHG_CH21_Msk (0x1UL << PPI_CHG_CH21_Pos) /*!< Bit mask of CH21 field. */
#define PPI_CHG_CH21_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH21_Included (1UL) /*!< Include */

/* Bit 20 : Include or exclude channel 20 */
#define PPI_CHG_CH20_Pos (20UL) /*!< Position of CH20 field. */
#define PPI_CHG_CH20_Msk (0x1UL << PPI_CHG_CH20_Pos) /*!< Bit mask of CH20 field. */
#define PPI_CHG_CH20_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH20_Included (1UL) /*!< Include */

/* Bit 19 : Include or exclude channel 19 */
#define PPI_CHG_CH19_Pos (19UL) /*!< Position of CH19 field. */
#define PPI_CHG_CH19_Msk (0x1UL << PPI_CHG_CH19_Pos) /*!< Bit mask of CH19 field. */
#define PPI_CHG_CH19_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH19_Included (1UL) /*!< Include */

/* Bit 18 : Include or exclude channel 18 */
#define PPI_CHG_CH18_Pos (18UL) /*!< Position of CH18 field. */
#define PPI_CHG_CH18_Msk (0x1UL << PPI_CHG_CH18_Pos) /*!< Bit mask of CH18 field. */
#define PPI_CHG_CH18_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH18_Included (1UL) /*!< Include */

/* Bit 17 : Include or exclude channel 17 */
#define PPI_CHG_CH17_Pos (17UL) /*!< Position of CH17 field. */
#define PPI_CHG_CH17_Msk (0x1UL << PPI_CHG_CH17_Pos) /*!< Bit mask of CH17 field. */
#define PPI_CHG_CH17_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH17_Included (1UL) /*!< Include */

/* Bit 16 : Include or exclude channel 16 */
#define PPI_CHG_CH16_Pos (16UL) /*!< Position of CH16 field. */
#define PPI_CHG_CH16_Msk (0x1UL << PPI_CHG_CH16_Pos) /*!< Bit mask of CH16 field. */
#define PPI_CHG_CH16_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH16_Included (1UL) /*!< Include */

/* Bit 15 : Include or exclude channel 15 */
#define PPI_CHG_CH15_Pos (15UL) /*!< Position of CH15 field. */
#define PPI_CHG_CH15_Msk (0x1UL << PPI_CHG_CH15_Pos) /*!< Bit mask of CH15 field. */
#define PPI_CHG_CH15_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH15_Included (1UL) /*!< Include */

/* Bit 14 : Include or exclude channel 14 */
#define PPI_CHG_CH14_Pos (14UL) /*!< Position of CH14 field. */
#define PPI_CHG_CH14_Msk (0x1UL << PPI_CHG_CH14_Pos) /*!< Bit mask of CH14 field. */
#define PPI_CHG_CH14_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH14_Included (1UL) /*!< Include */

/* Bit 13 : Include or exclude channel 13 */
#define PPI_CHG_CH13_Pos (13UL) /*!< Position of CH13 field. */
#define PPI_CHG_CH13_Msk (0x1UL << PPI_CHG_CH13_Pos) /*!< Bit mask of CH13 field. */
#define PPI_CHG_CH13_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH13_Included (1UL) /*!< Include */

/* Bit 12 : Include or exclude channel 12 */
#define PPI_CHG_CH12_Pos (12UL) /*!< Position of CH12 field. */
#define PPI_CHG_CH12_Msk (0x1UL << PPI_CHG_CH12_Pos) /*!< Bit mask of CH12 field. */
#define PPI_CHG_CH12_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH12_Included (1UL) /*!< Include */

/* Bit 11 : Include or exclude channel 11 */
#define PPI_CHG_CH11_Pos (11UL) /*!< Position of CH11 field. */
#define PPI_CHG_CH11_Msk (0x1UL << PPI_CHG_CH11_Pos) /*!< Bit mask of CH11 field. */
#define PPI_CHG_CH11_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH11_Included (1UL) /*!< Include */

/* Bit 10 : Include or exclude channel 10 */
#define PPI_CHG_CH10_Pos (10UL) /*!< Position of CH10 field. */
#define PPI_CHG_CH10_Msk (0x1UL << PPI_CHG_CH10_Pos) /*!< Bit mask of CH10 field. */
#define PPI_CHG_CH10_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH10_Included (1UL) /*!< Include */

/* Bit 9 : Include or exclude channel 9 */
#define PPI_CHG_CH9_Pos (9UL) /*!< Position of CH9 field. */
#define PPI_CHG_CH9_Msk (0x1UL << PPI_CHG_CH9_Pos) /*!< Bit mask of CH9 field. */
#define PPI_CHG_CH9_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH9_Included (1UL) /*!< Include */

/* Bit 8 : Include or exclude channel 8 */
#define PPI_CHG_CH8_Pos (8UL) /*!< Position of CH8 field. */
#define PPI_CHG_CH8_Msk (0x1UL << PPI_CHG_CH8_Pos) /*!< Bit mask of CH8 field. */
#define PPI_CHG_CH8_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH8_Included (1UL) /*!< Include */

/* Bit 7 : Include or exclude channel 7 */
#define PPI_CHG_CH7_Pos (7UL) /*!< Position of CH7 field. */
#define PPI_CHG_CH7_Msk (0x1UL << PPI_CHG_CH7_Pos) /*!< Bit mask of CH7 field. */
#define PPI_CHG_CH7_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH7_Included (1UL) /*!< Include */

/* Bit 6 : Include or exclude channel 6 */
#define PPI_CHG_CH6_Pos (6UL) /*!< Position of CH6 field. */
#define PPI_CHG_CH6_Msk (0x1UL << PPI_CHG_CH6_Pos) /*!< Bit mask of CH6 field. */
#define PPI_CHG_CH6_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH6_Included (1UL) /*!< Include */

/* Bit 5 : Include or exclude channel 5 */
#define PPI_CHG_CH5_Pos (5UL) /*!< Position of CH5 field. */
#define PPI_CHG_CH5_Msk (0x1UL << PPI_CHG_CH5_Pos) /*!< Bit mask of CH5 field. */
#define PPI_CHG_CH5_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH5_Included (1UL) /*!< Include */

/* Bit 4 : Include or exclude channel 4 */
#define PPI_CHG_CH4_Pos (4UL) /*!< Position of CH4 field. */
#define PPI_CHG_CH4_Msk (0x1UL << PPI_CHG_CH4_Pos) /*!< Bit mask of CH4 field. */
#define PPI_CHG_CH4_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH4_Included (1UL) /*!< Include */

/* Bit 3 : Include or exclude channel 3 */
#define PPI_CHG_CH3_Pos (3UL) /*!< Position of CH3 field. */
#define PPI_CHG_CH3_Msk (0x1UL << PPI_CHG_CH3_Pos) /*!< Bit mask of CH3 field. */
#define PPI_CHG_CH3_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH3_Included (1UL) /*!< Include */

/* Bit 2 : Include or exclude channel 2 */
#define PPI_CHG_CH2_Pos (2UL) /*!< Position of CH2 field. */
#define PPI_CHG_CH2_Msk (0x1UL << PPI_CHG_CH2_Pos) /*!< Bit mask of CH2 field. */
#define PPI_CHG_CH2_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH2_Included (1UL) /*!< Include */

/* Bit 1 : Include or exclude channel 1 */
#define PPI_CHG_CH1_Pos (1UL) /*!< Position of CH1 field. */
#define PPI_CHG_CH1_Msk (0x1UL << PPI_CHG_CH1_Pos) /*!< Bit mask of CH1 field. */
#define PPI_CHG_CH1_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH1_Included (1UL) /*!< Include */

/* Bit 0 : Include or exclude channel 0 */
#define PPI_CHG_CH0_Pos (0UL) /*!< Position of CH0 field. */
#define PPI_CHG_CH0_Msk (0x1UL << PPI_CHG_CH0_Pos) /*!< Bit mask of CH0 field. */
#define PPI_CHG_CH0_Excluded (0UL) /*!< Exclude */
#define PPI_CHG_CH0_Included (1UL) /*!< Include */

/* Register: PPI_FORK_TEP */
/* Description: Description cluster[0]:  Channel 0 task end-point */

/* Bits 31..0 : Pointer to task register */
#define PPI_FORK_TEP_TEP_Pos (0UL) /*!< Position of TEP field. */
#define PPI_FORK_TEP_TEP_Msk (0xFFFFFFFFUL << PPI_FORK_TEP_TEP_Pos) /*!< Bit mask of TEP field. */


/* Peripheral: PWM */
/* Description: Pulse Width Modulation Unit 0 */

/* Register: PWM_SHORTS */
/* Description: Shortcut register */

/* Bit 4 : Shortcut between LOOPSDONE event and STOP task */
#define PWM_SHORTS_LOOPSDONE_STOP_Pos (4UL) /*!< Position of LOOPSDONE_STOP field. */
#define PWM_SHORTS_LOOPSDONE_STOP_Msk (0x1UL << PWM_SHORTS_LOOPSDONE_STOP_Pos) /*!< Bit mask of LOOPSDONE_STOP field. */
#define PWM_SHORTS_LOOPSDONE_STOP_Disabled (0UL) /*!< Disable shortcut */
#define PWM_SHORTS_LOOPSDONE_STOP_Enabled (1UL) /*!< Enable shortcut */

/* Bit 3 : Shortcut between LOOPSDONE event and SEQSTART[1] task */
#define PWM_SHORTS_LOOPSDONE_SEQSTART1_Pos (3UL) /*!< Position of LOOPSDONE_SEQSTART1 field. */
#define PWM_SHORTS_LOOPSDONE_SEQSTART1_Msk (0x1UL << PWM_SHORTS_LOOPSDONE_SEQSTART1_Pos) /*!< Bit mask of LOOPSDONE_SEQSTART1 field. */
#define PWM_SHORTS_LOOPSDONE_SEQSTART1_Disabled (0UL) /*!< Disable shortcut */
#define PWM_SHORTS_LOOPSDONE_SEQSTART1_Enabled (1UL) /*!< Enable shortcut */

/* Bit 2 : Shortcut between LOOPSDONE event and SEQSTART[0] task */
#define PWM_SHORTS_LOOPSDONE_SEQSTART0_Pos (2UL) /*!< Position of LOOPSDONE_SEQSTART0 field. */
#define PWM_SHORTS_LOOPSDONE_SEQSTART0_Msk (0x1UL << PWM_SHORTS_LOOPSDONE_SEQSTART0_Pos) /*!< Bit mask of LOOPSDONE_SEQSTART0 field. */
#define PWM_SHORTS_LOOPSDONE_SEQSTART0_Disabled (0UL) /*!< Disable shortcut */
#define PWM_SHORTS_LOOPSDONE_SEQSTART0_Enabled (1UL) /*!< Enable shortcut */

/* Bit 1 : Shortcut between SEQEND[1] event and STOP task */
#define PWM_SHORTS_SEQEND1_STOP_Pos (1UL) /*!< Position of SEQEND1_STOP field. */
#define PWM_SHORTS_SEQEND1_STOP_Msk (0x1UL << PWM_SHORTS_SEQEND1_STOP_Pos) /*!< Bit mask of SEQEND1_STOP field. */
#define PWM_SHORTS_SEQEND1_STOP_Disabled (0UL) /*!< Disable shortcut */
#define PWM_SHORTS_SEQEND1_STOP_Enabled (1UL) /*!< Enable shortcut */

/* Bit 0 : Shortcut between SEQEND[0] event and STOP task */
#define PWM_SHORTS_SEQEND0_STOP_Pos (0UL) /*!< Position of SEQEND0_STOP field. */
#define PWM_SHORTS_SEQEND0_STOP_Msk (0x1UL << PWM_SHORTS_SEQEND0_STOP_Pos) /*!< Bit mask of SEQEND0_STOP field. */
#define PWM_SHORTS_SEQEND0_STOP_Disabled (0UL) /*!< Disable shortcut */
#define PWM_SHORTS_SEQEND0_STOP_Enabled (1UL) /*!< Enable shortcut */

/* Register: PWM_INTEN */
/* Description: Enable or disable interrupt */

/* Bit 7 : Enable or disable interrupt for LOOPSDONE event */
#define PWM_INTEN_LOOPSDONE_Pos (7UL) /*!< Position of LOOPSDONE field. */
#define PWM_INTEN_LOOPSDONE_Msk (0x1UL << PWM_INTEN_LOOPSDONE_Pos) /*!< Bit mask of LOOPSDONE field. */
#define PWM_INTEN_LOOPSDONE_Disabled (0UL) /*!< Disable */
#define PWM_INTEN_LOOPSDONE_Enabled (1UL) /*!< Enable */

/* Bit 6 : Enable or disable interrupt for PWMPERIODEND event */
#define PWM_INTEN_PWMPERIODEND_Pos (6UL) /*!< Position of PWMPERIODEND field. */
#define PWM_INTEN_PWMPERIODEND_Msk (0x1UL << PWM_INTEN_PWMPERIODEND_Pos) /*!< Bit mask of PWMPERIODEND field. */
#define PWM_INTEN_PWMPERIODEND_Disabled (0UL) /*!< Disable */
#define PWM_INTEN_PWMPERIODEND_Enabled (1UL) /*!< Enable */

/* Bit 5 : Enable or disable interrupt for SEQEND[1] event */
#define PWM_INTEN_SEQEND1_Pos (5UL) /*!< Position of SEQEND1 field. */
#define PWM_INTEN_SEQEND1_Msk (0x1UL << PWM_INTEN_SEQEND1_Pos) /*!< Bit mask of SEQEND1 field. */
#define PWM_INTEN_SEQEND1_Disabled (0UL) /*!< Disable */
#define PWM_INTEN_SEQEND1_Enabled (1UL) /*!< Enable */

/* Bit 4 : Enable or disable interrupt for SEQEND[0] event */
#define PWM_INTEN_SEQEND0_Pos (4UL) /*!< Position of SEQEND0 field. */
#define PWM_INTEN_SEQEND0_Msk (0x1UL << PWM_INTEN_SEQEND0_Pos) /*!< Bit mask of SEQEND0 field. */
#define PWM_INTEN_SEQEND0_Disabled (0UL) /*!< Disable */
#define PWM_INTEN_SEQEND0_Enabled (1UL) /*!< Enable */

/* Bit 3 : Enable or disable interrupt for SEQSTARTED[1] event */
#define PWM_INTEN_SEQSTARTED1_Pos (3UL) /*!< Position of SEQSTARTED1 field. */
#define PWM_INTEN_SEQSTARTED1_Msk (0x1UL << PWM_INTEN_SEQSTARTED1_Pos) /*!< Bit mask of SEQSTARTED1 field. */
#define PWM_INTEN_SEQSTARTED1_Disabled (0UL) /*!< Disable */
#define PWM_INTEN_SEQSTARTED1_Enabled (1UL) /*!< Enable */

/* Bit 2 : Enable or disable interrupt for SEQSTARTED[0] event */
#define PWM_INTEN_SEQSTARTED0_Pos (2UL) /*!< Position of SEQSTARTED0 field. */
#define PWM_INTEN_SEQSTARTED0_Msk (0x1UL << PWM_INTEN_SEQSTARTED0_Pos) /*!< Bit mask of SEQSTARTED0 field. */
#define PWM_INTEN_SEQSTARTED0_Disabled (0UL) /*!< Disable */
#define PWM_INTEN_SEQSTARTED0_Enabled (1UL) /*!< Enable */

/* Bit 1 : Enable or disable interrupt for STOPPED event */
#define PWM_INTEN_STOPPED_Pos (1UL) /*!< Position of STOPPED field. */
#define PWM_INTEN_STOPPED_Msk (0x1UL << PWM_INTEN_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define PWM_INTEN_STOPPED_Disabled (0UL) /*!< Disable */
#define PWM_INTEN_STOPPED_Enabled (1UL) /*!< Enable */

/* Register: PWM_INTENSET */
/* Description: Enable interrupt */

/* Bit 7 : Write '1' to Enable interrupt for LOOPSDONE event */
#define PWM_INTENSET_LOOPSDONE_Pos (7UL) /*!< Position of LOOPSDONE field. */
#define PWM_INTENSET_LOOPSDONE_Msk (0x1UL << PWM_INTENSET_LOOPSDONE_Pos) /*!< Bit mask of LOOPSDONE field. */
#define PWM_INTENSET_LOOPSDONE_Disabled (0UL) /*!< Read: Disabled */
#define PWM_INTENSET_LOOPSDONE_Enabled (1UL) /*!< Read: Enabled */
#define PWM_INTENSET_LOOPSDONE_Set (1UL) /*!< Enable */

/* Bit 6 : Write '1' to Enable interrupt for PWMPERIODEND event */
#define PWM_INTENSET_PWMPERIODEND_Pos (6UL) /*!< Position of PWMPERIODEND field. */
#define PWM_INTENSET_PWMPERIODEND_Msk (0x1UL << PWM_INTENSET_PWMPERIODEND_Pos) /*!< Bit mask of PWMPERIODEND field. */
#define PWM_INTENSET_PWMPERIODEND_Disabled (0UL) /*!< Read: Disabled */
#define PWM_INTENSET_PWMPERIODEND_Enabled (1UL) /*!< Read: Enabled */
#define PWM_INTENSET_PWMPERIODEND_Set (1UL) /*!< Enable */

/* Bit 5 : Write '1' to Enable interrupt for SEQEND[1] event */
#define PWM_INTENSET_SEQEND1_Pos (5UL) /*!< Position of SEQEND1 field. */
#define PWM_INTENSET_SEQEND1_Msk (0x1UL << PWM_INTENSET_SEQEND1_Pos) /*!< Bit mask of SEQEND1 field. */
#define PWM_INTENSET_SEQEND1_Disabled (0UL) /*!< Read: Disabled */
#define PWM_INTENSET_SEQEND1_Enabled (1UL) /*!< Read: Enabled */
#define PWM_INTENSET_SEQEND1_Set (1UL) /*!< Enable */

/* Bit 4 : Write '1' to Enable interrupt for SEQEND[0] event */
#define PWM_INTENSET_SEQEND0_Pos (4UL) /*!< Position of SEQEND0 field. */
#define PWM_INTENSET_SEQEND0_Msk (0x1UL << PWM_INTENSET_SEQEND0_Pos) /*!< Bit mask of SEQEND0 field. */
#define PWM_INTENSET_SEQEND0_Disabled (0UL) /*!< Read: Disabled */
#define PWM_INTENSET_SEQEND0_Enabled (1UL) /*!< Read: Enabled */
#define PWM_INTENSET_SEQEND0_Set (1UL) /*!< Enable */

/* Bit 3 : Write '1' to Enable interrupt for SEQSTARTED[1] event */
#define PWM_INTENSET_SEQSTARTED1_Pos (3UL) /*!< Position of SEQSTARTED1 field. */
#define PWM_INTENSET_SEQSTARTED1_Msk (0x1UL << PWM_INTENSET_SEQSTARTED1_Pos) /*!< Bit mask of SEQSTARTED1 field. */
#define PWM_INTENSET_SEQSTARTED1_Disabled (0UL) /*!< Read: Disabled */
#define PWM_INTENSET_SEQSTARTED1_Enabled (1UL) /*!< Read: Enabled */
#define PWM_INTENSET_SEQSTARTED1_Set (1UL) /*!< Enable */

/* Bit 2 : Write '1' to Enable interrupt for SEQSTARTED[0] event */
#define PWM_INTENSET_SEQSTARTED0_Pos (2UL) /*!< Position of SEQSTARTED0 field. */
#define PWM_INTENSET_SEQSTARTED0_Msk (0x1UL << PWM_INTENSET_SEQSTARTED0_Pos) /*!< Bit mask of SEQSTARTED0 field. */
#define PWM_INTENSET_SEQSTARTED0_Disabled (0UL) /*!< Read: Disabled */
#define PWM_INTENSET_SEQSTARTED0_Enabled (1UL) /*!< Read: Enabled */
#define PWM_INTENSET_SEQSTARTED0_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable interrupt for STOPPED event */
#define PWM_INTENSET_STOPPED_Pos (1UL) /*!< Position of STOPPED field. */
#define PWM_INTENSET_STOPPED_Msk (0x1UL << PWM_INTENSET_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define PWM_INTENSET_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define PWM_INTENSET_STOPPED_Enabled (1UL) /*!< Read: Enabled */
#define PWM_INTENSET_STOPPED_Set (1UL) /*!< Enable */

/* Register: PWM_INTENCLR */
/* Description: Disable interrupt */

/* Bit 7 : Write '1' to Disable interrupt for LOOPSDONE event */
#define PWM_INTENCLR_LOOPSDONE_Pos (7UL) /*!< Position of LOOPSDONE field. */
#define PWM_INTENCLR_LOOPSDONE_Msk (0x1UL << PWM_INTENCLR_LOOPSDONE_Pos) /*!< Bit mask of LOOPSDONE field. */
#define PWM_INTENCLR_LOOPSDONE_Disabled (0UL) /*!< Read: Disabled */
#define PWM_INTENCLR_LOOPSDONE_Enabled (1UL) /*!< Read: Enabled */
#define PWM_INTENCLR_LOOPSDONE_Clear (1UL) /*!< Disable */

/* Bit 6 : Write '1' to Disable interrupt for PWMPERIODEND event */
#define PWM_INTENCLR_PWMPERIODEND_Pos (6UL) /*!< Position of PWMPERIODEND field. */
#define PWM_INTENCLR_PWMPERIODEND_Msk (0x1UL << PWM_INTENCLR_PWMPERIODEND_Pos) /*!< Bit mask of PWMPERIODEND field. */
#define PWM_INTENCLR_PWMPERIODEND_Disabled (0UL) /*!< Read: Disabled */
#define PWM_INTENCLR_PWMPERIODEND_Enabled (1UL) /*!< Read: Enabled */
#define PWM_INTENCLR_PWMPERIODEND_Clear (1UL) /*!< Disable */

/* Bit 5 : Write '1' to Disable interrupt for SEQEND[1] event */
#define PWM_INTENCLR_SEQEND1_Pos (5UL) /*!< Position of SEQEND1 field. */
#define PWM_INTENCLR_SEQEND1_Msk (0x1UL << PWM_INTENCLR_SEQEND1_Pos) /*!< Bit mask of SEQEND1 field. */
#define PWM_INTENCLR_SEQEND1_Disabled (0UL) /*!< Read: Disabled */
#define PWM_INTENCLR_SEQEND1_Enabled (1UL) /*!< Read: Enabled */
#define PWM_INTENCLR_SEQEND1_Clear (1UL) /*!< Disable */

/* Bit 4 : Write '1' to Disable interrupt for SEQEND[0] event */
#define PWM_INTENCLR_SEQEND0_Pos (4UL) /*!< Position of SEQEND0 field. */
#define PWM_INTENCLR_SEQEND0_Msk (0x1UL << PWM_INTENCLR_SEQEND0_Pos) /*!< Bit mask of SEQEND0 field. */
#define PWM_INTENCLR_SEQEND0_Disabled (0UL) /*!< Read: Disabled */
#define PWM_INTENCLR_SEQEND0_Enabled (1UL) /*!< Read: Enabled */
#define PWM_INTENCLR_SEQEND0_Clear (1UL) /*!< Disable */

/* Bit 3 : Write '1' to Disable interrupt for SEQSTARTED[1] event */
#define PWM_INTENCLR_SEQSTARTED1_Pos (3UL) /*!< Position of SEQSTARTED1 field. */
#define PWM_INTENCLR_SEQSTARTED1_Msk (0x1UL << PWM_INTENCLR_SEQSTARTED1_Pos) /*!< Bit mask of SEQSTARTED1 field. */
#define PWM_INTENCLR_SEQSTARTED1_Disabled (0UL) /*!< Read: Disabled */
#define PWM_INTENCLR_SEQSTARTED1_Enabled (1UL) /*!< Read: Enabled */
#define PWM_INTENCLR_SEQSTARTED1_Clear (1UL) /*!< Disable */

/* Bit 2 : Write '1' to Disable interrupt for SEQSTARTED[0] event */
#define PWM_INTENCLR_SEQSTARTED0_Pos (2UL) /*!< Position of SEQSTARTED0 field. */
#define PWM_INTENCLR_SEQSTARTED0_Msk (0x1UL << PWM_INTENCLR_SEQSTARTED0_Pos) /*!< Bit mask of SEQSTARTED0 field. */
#define PWM_INTENCLR_SEQSTARTED0_Disabled (0UL) /*!< Read: Disabled */
#define PWM_INTENCLR_SEQSTARTED0_Enabled (1UL) /*!< Read: Enabled */
#define PWM_INTENCLR_SEQSTARTED0_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable interrupt for STOPPED event */
#define PWM_INTENCLR_STOPPED_Pos (1UL) /*!< Position of STOPPED field. */
#define PWM_INTENCLR_STOPPED_Msk (0x1UL << PWM_INTENCLR_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define PWM_INTENCLR_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define PWM_INTENCLR_STOPPED_Enabled (1UL) /*!< Read: Enabled */
#define PWM_INTENCLR_STOPPED_Clear (1UL) /*!< Disable */

/* Register: PWM_ENABLE */
/* Description: PWM module enable register */

/* Bit 0 : Enable or disable PWM module */
#define PWM_ENABLE_ENABLE_Pos (0UL) /*!< Position of ENABLE field. */
#define PWM_ENABLE_ENABLE_Msk (0x1UL << PWM_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define PWM_ENABLE_ENABLE_Disabled (0UL) /*!< Disabled */
#define PWM_ENABLE_ENABLE_Enabled (1UL) /*!< Enable */

/* Register: PWM_MODE */
/* Description: Selects operating mode of the wave counter */

/* Bit 0 : Selects up or up and down as wave counter mode */
#define PWM_MODE_UPDOWN_Pos (0UL) /*!< Position of UPDOWN field. */
#define PWM_MODE_UPDOWN_Msk (0x1UL << PWM_MODE_UPDOWN_Pos) /*!< Bit mask of UPDOWN field. */
#define PWM_MODE_UPDOWN_Up (0UL) /*!< Up counter - edge aligned PWM duty-cycle */
#define PWM_MODE_UPDOWN_UpAndDown (1UL) /*!< Up and down counter - center aligned PWM duty cycle */

/* Register: PWM_COUNTERTOP */
/* Description: Value up to which the pulse generator counter counts */

/* Bits 14..0 : Value up to which the pulse generator counter counts. This register is ignored when DECODER.MODE=WaveForm and only values from RAM will be used. */
#define PWM_COUNTERTOP_COUNTERTOP_Pos (0UL) /*!< Position of COUNTERTOP field. */
#define PWM_COUNTERTOP_COUNTERTOP_Msk (0x7FFFUL << PWM_COUNTERTOP_COUNTERTOP_Pos) /*!< Bit mask of COUNTERTOP field. */

/* Register: PWM_PRESCALER */
/* Description: Configuration for PWM_CLK */

/* Bits 2..0 : Pre-scaler of PWM_CLK */
#define PWM_PRESCALER_PRESCALER_Pos (0UL) /*!< Position of PRESCALER field. */
#define PWM_PRESCALER_PRESCALER_Msk (0x7UL << PWM_PRESCALER_PRESCALER_Pos) /*!< Bit mask of PRESCALER field. */
#define PWM_PRESCALER_PRESCALER_DIV_1 (0UL) /*!< Divide by   1 (16MHz) */
#define PWM_PRESCALER_PRESCALER_DIV_2 (1UL) /*!< Divide by   2 ( 8MHz) */
#define PWM_PRESCALER_PRESCALER_DIV_4 (2UL) /*!< Divide by   4 ( 4MHz) */
#define PWM_PRESCALER_PRESCALER_DIV_8 (3UL) /*!< Divide by   8 ( 2MHz) */
#define PWM_PRESCALER_PRESCALER_DIV_16 (4UL) /*!< Divide by  16 ( 1MHz) */
#define PWM_PRESCALER_PRESCALER_DIV_32 (5UL) /*!< Divide by  32 ( 500kHz) */
#define PWM_PRESCALER_PRESCALER_DIV_64 (6UL) /*!< Divide by  64 ( 250kHz) */
#define PWM_PRESCALER_PRESCALER_DIV_128 (7UL) /*!< Divide by 128 ( 125kHz) */

/* Register: PWM_DECODER */
/* Description: Configuration of the decoder */

/* Bit 8 : Selects source for advancing the active sequence */
#define PWM_DECODER_MODE_Pos (8UL) /*!< Position of MODE field. */
#define PWM_DECODER_MODE_Msk (0x1UL << PWM_DECODER_MODE_Pos) /*!< Bit mask of MODE field. */
#define PWM_DECODER_MODE_RefreshCount (0UL) /*!< SEQ[n].REFRESH is used to determine loading internal compare registers */
#define PWM_DECODER_MODE_NextStep (1UL) /*!< NEXTSTEP task causes a new value to be loaded to internal compare registers */

/* Bits 2..0 : How a sequence is read from RAM and spread to the compare register */
#define PWM_DECODER_LOAD_Pos (0UL) /*!< Position of LOAD field. */
#define PWM_DECODER_LOAD_Msk (0x7UL << PWM_DECODER_LOAD_Pos) /*!< Bit mask of LOAD field. */
#define PWM_DECODER_LOAD_Common (0UL) /*!< 1st half word (16-bit) used in all PWM channels 0..3 */
#define PWM_DECODER_LOAD_Grouped (1UL) /*!< 1st half word (16-bit) used in channel 0..1; 2nd word in channel 2..3 */
#define PWM_DECODER_LOAD_Individual (2UL) /*!< 1st half word (16-bit) in ch.0; 2nd in ch.1; ...; 4th in ch.3 */
#define PWM_DECODER_LOAD_WaveForm (3UL) /*!< 1st half word (16-bit) in ch.0; 2nd in ch.1; ...; 4th in COUNTERTOP */

/* Register: PWM_LOOP */
/* Description: Amount of playback of a loop */

/* Bits 15..0 : Amount of playback of pattern cycles */
#define PWM_LOOP_CNT_Pos (0UL) /*!< Position of CNT field. */
#define PWM_LOOP_CNT_Msk (0xFFFFUL << PWM_LOOP_CNT_Pos) /*!< Bit mask of CNT field. */
#define PWM_LOOP_CNT_Disabled (0UL) /*!< Looping disabled (stop at the end of the sequence) */

/* Register: PWM_SEQ_PTR */
/* Description: Description cluster[0]:  Beginning address in Data RAM of sequence A */

/* Bits 31..0 : Beginning address in Data RAM of sequence A */
#define PWM_SEQ_PTR_PTR_Pos (0UL) /*!< Position of PTR field. */
#define PWM_SEQ_PTR_PTR_Msk (0xFFFFFFFFUL << PWM_SEQ_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: PWM_SEQ_CNT */
/* Description: Description cluster[0]:  Amount of values (duty cycles) in sequence A */

/* Bits 14..0 : Amount of values (duty cycles) in sequence A */
#define PWM_SEQ_CNT_CNT_Pos (0UL) /*!< Position of CNT field. */
#define PWM_SEQ_CNT_CNT_Msk (0x7FFFUL << PWM_SEQ_CNT_CNT_Pos) /*!< Bit mask of CNT field. */
#define PWM_SEQ_CNT_CNT_Disabled (0UL) /*!< Sequence is disabled, and shall not be started as it is empty */

/* Register: PWM_SEQ_REFRESH */
/* Description: Description cluster[0]:  Amount of additional PWM periods between samples loaded to compare register (load every CNT+1 PWM periods) */

/* Bits 23..0 : Amount of additional PWM periods between samples loaded to compare register (load every CNT+1 PWM periods) */
#define PWM_SEQ_REFRESH_CNT_Pos (0UL) /*!< Position of CNT field. */
#define PWM_SEQ_REFRESH_CNT_Msk (0xFFFFFFUL << PWM_SEQ_REFRESH_CNT_Pos) /*!< Bit mask of CNT field. */
#define PWM_SEQ_REFRESH_CNT_Continuous (0UL) /*!< Update every PWM period */

/* Register: PWM_SEQ_ENDDELAY */
/* Description: Description cluster[0]:  Time added after the sequence */

/* Bits 23..0 : Time added after the sequence in PWM periods */
#define PWM_SEQ_ENDDELAY_CNT_Pos (0UL) /*!< Position of CNT field. */
#define PWM_SEQ_ENDDELAY_CNT_Msk (0xFFFFFFUL << PWM_SEQ_ENDDELAY_CNT_Pos) /*!< Bit mask of CNT field. */

/* Register: PWM_PSEL_OUT */
/* Description: Description collection[0]:  Output pin select for PWM channel 0 */

/* Bit 31 : Connection */
#define PWM_PSEL_OUT_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define PWM_PSEL_OUT_CONNECT_Msk (0x1UL << PWM_PSEL_OUT_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define PWM_PSEL_OUT_CONNECT_Connected (0UL) /*!< Connect */
#define PWM_PSEL_OUT_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 9..8 : Port number */
#define PWM_PSEL_OUT_PORT_Pos (8UL) /*!< Position of PORT field. */
#define PWM_PSEL_OUT_PORT_Msk (0x3UL << PWM_PSEL_OUT_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define PWM_PSEL_OUT_PIN_Pos (0UL) /*!< Position of PIN field. */
#define PWM_PSEL_OUT_PIN_Msk (0x1FUL << PWM_PSEL_OUT_PIN_Pos) /*!< Bit mask of PIN field. */


/* Peripheral: QDEC */
/* Description: Quadrature Decoder */

/* Register: QDEC_SHORTS */
/* Description: Shortcut register */

/* Bit 6 : Shortcut between SAMPLERDY event and READCLRACC task */
#define QDEC_SHORTS_SAMPLERDY_READCLRACC_Pos (6UL) /*!< Position of SAMPLERDY_READCLRACC field. */
#define QDEC_SHORTS_SAMPLERDY_READCLRACC_Msk (0x1UL << QDEC_SHORTS_SAMPLERDY_READCLRACC_Pos) /*!< Bit mask of SAMPLERDY_READCLRACC field. */
#define QDEC_SHORTS_SAMPLERDY_READCLRACC_Disabled (0UL) /*!< Disable shortcut */
#define QDEC_SHORTS_SAMPLERDY_READCLRACC_Enabled (1UL) /*!< Enable shortcut */

/* Bit 5 : Shortcut between DBLRDY event and STOP task */
#define QDEC_SHORTS_DBLRDY_STOP_Pos (5UL) /*!< Position of DBLRDY_STOP field. */
#define QDEC_SHORTS_DBLRDY_STOP_Msk (0x1UL << QDEC_SHORTS_DBLRDY_STOP_Pos) /*!< Bit mask of DBLRDY_STOP field. */
#define QDEC_SHORTS_DBLRDY_STOP_Disabled (0UL) /*!< Disable shortcut */
#define QDEC_SHORTS_DBLRDY_STOP_Enabled (1UL) /*!< Enable shortcut */

/* Bit 4 : Shortcut between DBLRDY event and RDCLRDBL task */
#define QDEC_SHORTS_DBLRDY_RDCLRDBL_Pos (4UL) /*!< Position of DBLRDY_RDCLRDBL field. */
#define QDEC_SHORTS_DBLRDY_RDCLRDBL_Msk (0x1UL << QDEC_SHORTS_DBLRDY_RDCLRDBL_Pos) /*!< Bit mask of DBLRDY_RDCLRDBL field. */
#define QDEC_SHORTS_DBLRDY_RDCLRDBL_Disabled (0UL) /*!< Disable shortcut */
#define QDEC_SHORTS_DBLRDY_RDCLRDBL_Enabled (1UL) /*!< Enable shortcut */

/* Bit 3 : Shortcut between REPORTRDY event and STOP task */
#define QDEC_SHORTS_REPORTRDY_STOP_Pos (3UL) /*!< Position of REPORTRDY_STOP field. */
#define QDEC_SHORTS_REPORTRDY_STOP_Msk (0x1UL << QDEC_SHORTS_REPORTRDY_STOP_Pos) /*!< Bit mask of REPORTRDY_STOP field. */
#define QDEC_SHORTS_REPORTRDY_STOP_Disabled (0UL) /*!< Disable shortcut */
#define QDEC_SHORTS_REPORTRDY_STOP_Enabled (1UL) /*!< Enable shortcut */

/* Bit 2 : Shortcut between REPORTRDY event and RDCLRACC task */
#define QDEC_SHORTS_REPORTRDY_RDCLRACC_Pos (2UL) /*!< Position of REPORTRDY_RDCLRACC field. */
#define QDEC_SHORTS_REPORTRDY_RDCLRACC_Msk (0x1UL << QDEC_SHORTS_REPORTRDY_RDCLRACC_Pos) /*!< Bit mask of REPORTRDY_RDCLRACC field. */
#define QDEC_SHORTS_REPORTRDY_RDCLRACC_Disabled (0UL) /*!< Disable shortcut */
#define QDEC_SHORTS_REPORTRDY_RDCLRACC_Enabled (1UL) /*!< Enable shortcut */

/* Bit 1 : Shortcut between SAMPLERDY event and STOP task */
#define QDEC_SHORTS_SAMPLERDY_STOP_Pos (1UL) /*!< Position of SAMPLERDY_STOP field. */
#define QDEC_SHORTS_SAMPLERDY_STOP_Msk (0x1UL << QDEC_SHORTS_SAMPLERDY_STOP_Pos) /*!< Bit mask of SAMPLERDY_STOP field. */
#define QDEC_SHORTS_SAMPLERDY_STOP_Disabled (0UL) /*!< Disable shortcut */
#define QDEC_SHORTS_SAMPLERDY_STOP_Enabled (1UL) /*!< Enable shortcut */

/* Bit 0 : Shortcut between REPORTRDY event and READCLRACC task */
#define QDEC_SHORTS_REPORTRDY_READCLRACC_Pos (0UL) /*!< Position of REPORTRDY_READCLRACC field. */
#define QDEC_SHORTS_REPORTRDY_READCLRACC_Msk (0x1UL << QDEC_SHORTS_REPORTRDY_READCLRACC_Pos) /*!< Bit mask of REPORTRDY_READCLRACC field. */
#define QDEC_SHORTS_REPORTRDY_READCLRACC_Disabled (0UL) /*!< Disable shortcut */
#define QDEC_SHORTS_REPORTRDY_READCLRACC_Enabled (1UL) /*!< Enable shortcut */

/* Register: QDEC_INTENSET */
/* Description: Enable interrupt */

/* Bit 4 : Write '1' to Enable interrupt for STOPPED event */
#define QDEC_INTENSET_STOPPED_Pos (4UL) /*!< Position of STOPPED field. */
#define QDEC_INTENSET_STOPPED_Msk (0x1UL << QDEC_INTENSET_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define QDEC_INTENSET_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define QDEC_INTENSET_STOPPED_Enabled (1UL) /*!< Read: Enabled */
#define QDEC_INTENSET_STOPPED_Set (1UL) /*!< Enable */

/* Bit 3 : Write '1' to Enable interrupt for DBLRDY event */
#define QDEC_INTENSET_DBLRDY_Pos (3UL) /*!< Position of DBLRDY field. */
#define QDEC_INTENSET_DBLRDY_Msk (0x1UL << QDEC_INTENSET_DBLRDY_Pos) /*!< Bit mask of DBLRDY field. */
#define QDEC_INTENSET_DBLRDY_Disabled (0UL) /*!< Read: Disabled */
#define QDEC_INTENSET_DBLRDY_Enabled (1UL) /*!< Read: Enabled */
#define QDEC_INTENSET_DBLRDY_Set (1UL) /*!< Enable */

/* Bit 2 : Write '1' to Enable interrupt for ACCOF event */
#define QDEC_INTENSET_ACCOF_Pos (2UL) /*!< Position of ACCOF field. */
#define QDEC_INTENSET_ACCOF_Msk (0x1UL << QDEC_INTENSET_ACCOF_Pos) /*!< Bit mask of ACCOF field. */
#define QDEC_INTENSET_ACCOF_Disabled (0UL) /*!< Read: Disabled */
#define QDEC_INTENSET_ACCOF_Enabled (1UL) /*!< Read: Enabled */
#define QDEC_INTENSET_ACCOF_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable interrupt for REPORTRDY event */
#define QDEC_INTENSET_REPORTRDY_Pos (1UL) /*!< Position of REPORTRDY field. */
#define QDEC_INTENSET_REPORTRDY_Msk (0x1UL << QDEC_INTENSET_REPORTRDY_Pos) /*!< Bit mask of REPORTRDY field. */
#define QDEC_INTENSET_REPORTRDY_Disabled (0UL) /*!< Read: Disabled */
#define QDEC_INTENSET_REPORTRDY_Enabled (1UL) /*!< Read: Enabled */
#define QDEC_INTENSET_REPORTRDY_Set (1UL) /*!< Enable */

/* Bit 0 : Write '1' to Enable interrupt for SAMPLERDY event */
#define QDEC_INTENSET_SAMPLERDY_Pos (0UL) /*!< Position of SAMPLERDY field. */
#define QDEC_INTENSET_SAMPLERDY_Msk (0x1UL << QDEC_INTENSET_SAMPLERDY_Pos) /*!< Bit mask of SAMPLERDY field. */
#define QDEC_INTENSET_SAMPLERDY_Disabled (0UL) /*!< Read: Disabled */
#define QDEC_INTENSET_SAMPLERDY_Enabled (1UL) /*!< Read: Enabled */
#define QDEC_INTENSET_SAMPLERDY_Set (1UL) /*!< Enable */

/* Register: QDEC_INTENCLR */
/* Description: Disable interrupt */

/* Bit 4 : Write '1' to Disable interrupt for STOPPED event */
#define QDEC_INTENCLR_STOPPED_Pos (4UL) /*!< Position of STOPPED field. */
#define QDEC_INTENCLR_STOPPED_Msk (0x1UL << QDEC_INTENCLR_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define QDEC_INTENCLR_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define QDEC_INTENCLR_STOPPED_Enabled (1UL) /*!< Read: Enabled */
#define QDEC_INTENCLR_STOPPED_Clear (1UL) /*!< Disable */

/* Bit 3 : Write '1' to Disable interrupt for DBLRDY event */
#define QDEC_INTENCLR_DBLRDY_Pos (3UL) /*!< Position of DBLRDY field. */
#define QDEC_INTENCLR_DBLRDY_Msk (0x1UL << QDEC_INTENCLR_DBLRDY_Pos) /*!< Bit mask of DBLRDY field. */
#define QDEC_INTENCLR_DBLRDY_Disabled (0UL) /*!< Read: Disabled */
#define QDEC_INTENCLR_DBLRDY_Enabled (1UL) /*!< Read: Enabled */
#define QDEC_INTENCLR_DBLRDY_Clear (1UL) /*!< Disable */

/* Bit 2 : Write '1' to Disable interrupt for ACCOF event */
#define QDEC_INTENCLR_ACCOF_Pos (2UL) /*!< Position of ACCOF field. */
#define QDEC_INTENCLR_ACCOF_Msk (0x1UL << QDEC_INTENCLR_ACCOF_Pos) /*!< Bit mask of ACCOF field. */
#define QDEC_INTENCLR_ACCOF_Disabled (0UL) /*!< Read: Disabled */
#define QDEC_INTENCLR_ACCOF_Enabled (1UL) /*!< Read: Enabled */
#define QDEC_INTENCLR_ACCOF_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable interrupt for REPORTRDY event */
#define QDEC_INTENCLR_REPORTRDY_Pos (1UL) /*!< Position of REPORTRDY field. */
#define QDEC_INTENCLR_REPORTRDY_Msk (0x1UL << QDEC_INTENCLR_REPORTRDY_Pos) /*!< Bit mask of REPORTRDY field. */
#define QDEC_INTENCLR_REPORTRDY_Disabled (0UL) /*!< Read: Disabled */
#define QDEC_INTENCLR_REPORTRDY_Enabled (1UL) /*!< Read: Enabled */
#define QDEC_INTENCLR_REPORTRDY_Clear (1UL) /*!< Disable */

/* Bit 0 : Write '1' to Disable interrupt for SAMPLERDY event */
#define QDEC_INTENCLR_SAMPLERDY_Pos (0UL) /*!< Position of SAMPLERDY field. */
#define QDEC_INTENCLR_SAMPLERDY_Msk (0x1UL << QDEC_INTENCLR_SAMPLERDY_Pos) /*!< Bit mask of SAMPLERDY field. */
#define QDEC_INTENCLR_SAMPLERDY_Disabled (0UL) /*!< Read: Disabled */
#define QDEC_INTENCLR_SAMPLERDY_Enabled (1UL) /*!< Read: Enabled */
#define QDEC_INTENCLR_SAMPLERDY_Clear (1UL) /*!< Disable */

/* Register: QDEC_ENABLE */
/* Description: Enable the quadrature decoder */

/* Bit 0 : Enable or disable the quadrature decoder */
#define QDEC_ENABLE_ENABLE_Pos (0UL) /*!< Position of ENABLE field. */
#define QDEC_ENABLE_ENABLE_Msk (0x1UL << QDEC_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define QDEC_ENABLE_ENABLE_Disabled (0UL) /*!< Disable */
#define QDEC_ENABLE_ENABLE_Enabled (1UL) /*!< Enable */

/* Register: QDEC_LEDPOL */
/* Description: LED output pin polarity */

/* Bit 0 : LED output pin polarity */
#define QDEC_LEDPOL_LEDPOL_Pos (0UL) /*!< Position of LEDPOL field. */
#define QDEC_LEDPOL_LEDPOL_Msk (0x1UL << QDEC_LEDPOL_LEDPOL_Pos) /*!< Bit mask of LEDPOL field. */
#define QDEC_LEDPOL_LEDPOL_ActiveLow (0UL) /*!< Led active on output pin low */
#define QDEC_LEDPOL_LEDPOL_ActiveHigh (1UL) /*!< Led active on output pin high */

/* Register: QDEC_SAMPLEPER */
/* Description: Sample period */

/* Bits 3..0 : Sample period. The SAMPLE register will be updated for every new sample */
#define QDEC_SAMPLEPER_SAMPLEPER_Pos (0UL) /*!< Position of SAMPLEPER field. */
#define QDEC_SAMPLEPER_SAMPLEPER_Msk (0xFUL << QDEC_SAMPLEPER_SAMPLEPER_Pos) /*!< Bit mask of SAMPLEPER field. */
#define QDEC_SAMPLEPER_SAMPLEPER_128us (0UL) /*!< 128 us */
#define QDEC_SAMPLEPER_SAMPLEPER_256us (1UL) /*!< 256 us */
#define QDEC_SAMPLEPER_SAMPLEPER_512us (2UL) /*!< 512 us */
#define QDEC_SAMPLEPER_SAMPLEPER_1024us (3UL) /*!< 1024 us */
#define QDEC_SAMPLEPER_SAMPLEPER_2048us (4UL) /*!< 2048 us */
#define QDEC_SAMPLEPER_SAMPLEPER_4096us (5UL) /*!< 4096 us */
#define QDEC_SAMPLEPER_SAMPLEPER_8192us (6UL) /*!< 8192 us */
#define QDEC_SAMPLEPER_SAMPLEPER_16384us (7UL) /*!< 16384 us */
#define QDEC_SAMPLEPER_SAMPLEPER_32ms (8UL) /*!< 32768 us */
#define QDEC_SAMPLEPER_SAMPLEPER_65ms (9UL) /*!< 65536 us */
#define QDEC_SAMPLEPER_SAMPLEPER_131ms (10UL) /*!< 131072 us */

/* Register: QDEC_SAMPLE */
/* Description: Motion sample value */

/* Bits 31..0 : Last motion sample */
#define QDEC_SAMPLE_SAMPLE_Pos (0UL) /*!< Position of SAMPLE field. */
#define QDEC_SAMPLE_SAMPLE_Msk (0xFFFFFFFFUL << QDEC_SAMPLE_SAMPLE_Pos) /*!< Bit mask of SAMPLE field. */

/* Register: QDEC_REPORTPER */
/* Description: Number of samples to be taken before REPORTRDY and DBLRDY events can be generated */

/* Bits 3..0 : Specifies the number of samples to be accumulated in the ACC register before the REPORTRDY and DBLRDY events can be generated */
#define QDEC_REPORTPER_REPORTPER_Pos (0UL) /*!< Position of REPORTPER field. */
#define QDEC_REPORTPER_REPORTPER_Msk (0xFUL << QDEC_REPORTPER_REPORTPER_Pos) /*!< Bit mask of REPORTPER field. */
#define QDEC_REPORTPER_REPORTPER_10Smpl (0UL) /*!< 10 samples / report */
#define QDEC_REPORTPER_REPORTPER_40Smpl (1UL) /*!< 40 samples / report */
#define QDEC_REPORTPER_REPORTPER_80Smpl (2UL) /*!< 80 samples / report */
#define QDEC_REPORTPER_REPORTPER_120Smpl (3UL) /*!< 120 samples / report */
#define QDEC_REPORTPER_REPORTPER_160Smpl (4UL) /*!< 160 samples / report */
#define QDEC_REPORTPER_REPORTPER_200Smpl (5UL) /*!< 200 samples / report */
#define QDEC_REPORTPER_REPORTPER_240Smpl (6UL) /*!< 240 samples / report */
#define QDEC_REPORTPER_REPORTPER_280Smpl (7UL) /*!< 280 samples / report */
#define QDEC_REPORTPER_REPORTPER_1Smpl (8UL) /*!< 1 sample / report */

/* Register: QDEC_ACC */
/* Description: Register accumulating the valid transitions */

/* Bits 31..0 : Register accumulating all valid samples (not double transition) read from the SAMPLE register */
#define QDEC_ACC_ACC_Pos (0UL) /*!< Position of ACC field. */
#define QDEC_ACC_ACC_Msk (0xFFFFFFFFUL << QDEC_ACC_ACC_Pos) /*!< Bit mask of ACC field. */

/* Register: QDEC_ACCREAD */
/* Description: Snapshot of the ACC register, updated by the READCLRACC or RDCLRACC task */

/* Bits 31..0 : Snapshot of the ACC register. */
#define QDEC_ACCREAD_ACCREAD_Pos (0UL) /*!< Position of ACCREAD field. */
#define QDEC_ACCREAD_ACCREAD_Msk (0xFFFFFFFFUL << QDEC_ACCREAD_ACCREAD_Pos) /*!< Bit mask of ACCREAD field. */

/* Register: QDEC_PSEL_LED */
/* Description: Pin select for LED signal */

/* Bit 31 : Connection */
#define QDEC_PSEL_LED_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define QDEC_PSEL_LED_CONNECT_Msk (0x1UL << QDEC_PSEL_LED_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define QDEC_PSEL_LED_CONNECT_Connected (0UL) /*!< Connect */
#define QDEC_PSEL_LED_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define QDEC_PSEL_LED_PORT_Pos (5UL) /*!< Position of PORT field. */
#define QDEC_PSEL_LED_PORT_Msk (0x3UL << QDEC_PSEL_LED_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define QDEC_PSEL_LED_PIN_Pos (0UL) /*!< Position of PIN field. */
#define QDEC_PSEL_LED_PIN_Msk (0x1FUL << QDEC_PSEL_LED_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: QDEC_PSEL_A */
/* Description: Pin select for A signal */

/* Bit 31 : Connection */
#define QDEC_PSEL_A_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define QDEC_PSEL_A_CONNECT_Msk (0x1UL << QDEC_PSEL_A_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define QDEC_PSEL_A_CONNECT_Connected (0UL) /*!< Connect */
#define QDEC_PSEL_A_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define QDEC_PSEL_A_PORT_Pos (5UL) /*!< Position of PORT field. */
#define QDEC_PSEL_A_PORT_Msk (0x3UL << QDEC_PSEL_A_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define QDEC_PSEL_A_PIN_Pos (0UL) /*!< Position of PIN field. */
#define QDEC_PSEL_A_PIN_Msk (0x1FUL << QDEC_PSEL_A_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: QDEC_PSEL_B */
/* Description: Pin select for B signal */

/* Bit 31 : Connection */
#define QDEC_PSEL_B_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define QDEC_PSEL_B_CONNECT_Msk (0x1UL << QDEC_PSEL_B_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define QDEC_PSEL_B_CONNECT_Connected (0UL) /*!< Connect */
#define QDEC_PSEL_B_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define QDEC_PSEL_B_PORT_Pos (5UL) /*!< Position of PORT field. */
#define QDEC_PSEL_B_PORT_Msk (0x3UL << QDEC_PSEL_B_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define QDEC_PSEL_B_PIN_Pos (0UL) /*!< Position of PIN field. */
#define QDEC_PSEL_B_PIN_Msk (0x1FUL << QDEC_PSEL_B_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: QDEC_DBFEN */
/* Description: Enable input debounce filters */

/* Bit 0 : Enable input debounce filters */
#define QDEC_DBFEN_DBFEN_Pos (0UL) /*!< Position of DBFEN field. */
#define QDEC_DBFEN_DBFEN_Msk (0x1UL << QDEC_DBFEN_DBFEN_Pos) /*!< Bit mask of DBFEN field. */
#define QDEC_DBFEN_DBFEN_Disabled (0UL) /*!< Debounce input filters disabled */
#define QDEC_DBFEN_DBFEN_Enabled (1UL) /*!< Debounce input filters enabled */

/* Register: QDEC_LEDPRE */
/* Description: Time period the LED is switched ON prior to sampling */

/* Bits 8..0 : Period in us the LED is switched on prior to sampling */
#define QDEC_LEDPRE_LEDPRE_Pos (0UL) /*!< Position of LEDPRE field. */
#define QDEC_LEDPRE_LEDPRE_Msk (0x1FFUL << QDEC_LEDPRE_LEDPRE_Pos) /*!< Bit mask of LEDPRE field. */

/* Register: QDEC_ACCDBL */
/* Description: Register accumulating the number of detected double transitions */

/* Bits 3..0 : Register accumulating the number of detected double or illegal transitions. ( SAMPLE = 2 ). */
#define QDEC_ACCDBL_ACCDBL_Pos (0UL) /*!< Position of ACCDBL field. */
#define QDEC_ACCDBL_ACCDBL_Msk (0xFUL << QDEC_ACCDBL_ACCDBL_Pos) /*!< Bit mask of ACCDBL field. */

/* Register: QDEC_ACCDBLREAD */
/* Description: Snapshot of the ACCDBL, updated by the READCLRACC or RDCLRDBL task */

/* Bits 3..0 : Snapshot of the ACCDBL register. This field is updated when the READCLRACC or RDCLRDBL task is triggered. */
#define QDEC_ACCDBLREAD_ACCDBLREAD_Pos (0UL) /*!< Position of ACCDBLREAD field. */
#define QDEC_ACCDBLREAD_ACCDBLREAD_Msk (0xFUL << QDEC_ACCDBLREAD_ACCDBLREAD_Pos) /*!< Bit mask of ACCDBLREAD field. */


/* Peripheral: QSPI */
/* Description: External flash interface */

/* Register: QSPI_INTEN */
/* Description: Enable or disable interrupt */

/* Bit 0 : Enable or disable interrupt for READY event */
#define QSPI_INTEN_READY_Pos (0UL) /*!< Position of READY field. */
#define QSPI_INTEN_READY_Msk (0x1UL << QSPI_INTEN_READY_Pos) /*!< Bit mask of READY field. */
#define QSPI_INTEN_READY_Disabled (0UL) /*!< Disable */
#define QSPI_INTEN_READY_Enabled (1UL) /*!< Enable */

/* Register: QSPI_INTENSET */
/* Description: Enable interrupt */

/* Bit 0 : Write '1' to Enable interrupt for READY event */
#define QSPI_INTENSET_READY_Pos (0UL) /*!< Position of READY field. */
#define QSPI_INTENSET_READY_Msk (0x1UL << QSPI_INTENSET_READY_Pos) /*!< Bit mask of READY field. */
#define QSPI_INTENSET_READY_Disabled (0UL) /*!< Read: Disabled */
#define QSPI_INTENSET_READY_Enabled (1UL) /*!< Read: Enabled */
#define QSPI_INTENSET_READY_Set (1UL) /*!< Enable */

/* Register: QSPI_INTENCLR */
/* Description: Disable interrupt */

/* Bit 0 : Write '1' to Disable interrupt for READY event */
#define QSPI_INTENCLR_READY_Pos (0UL) /*!< Position of READY field. */
#define QSPI_INTENCLR_READY_Msk (0x1UL << QSPI_INTENCLR_READY_Pos) /*!< Bit mask of READY field. */
#define QSPI_INTENCLR_READY_Disabled (0UL) /*!< Read: Disabled */
#define QSPI_INTENCLR_READY_Enabled (1UL) /*!< Read: Enabled */
#define QSPI_INTENCLR_READY_Clear (1UL) /*!< Disable */

/* Register: QSPI_ENABLE */
/* Description: Enable QSPI peripheral and acquire the pins selected in PSELn registers */

/* Bit 0 : Enable or disable QSPI */
#define QSPI_ENABLE_ENABLE_Pos (0UL) /*!< Position of ENABLE field. */
#define QSPI_ENABLE_ENABLE_Msk (0x1UL << QSPI_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define QSPI_ENABLE_ENABLE_Disabled (0UL) /*!< Disable QSPI */
#define QSPI_ENABLE_ENABLE_Enabled (1UL) /*!< Enable QSPI */

/* Register: QSPI_READ_SRC */
/* Description: Flash memory source address */

/* Bits 31..0 : Word-aligned flash memory source address. */
#define QSPI_READ_SRC_SRC_Pos (0UL) /*!< Position of SRC field. */
#define QSPI_READ_SRC_SRC_Msk (0xFFFFFFFFUL << QSPI_READ_SRC_SRC_Pos) /*!< Bit mask of SRC field. */

/* Register: QSPI_READ_DST */
/* Description: RAM destination address */

/* Bits 31..0 : Word-aligned RAM destination address. */
#define QSPI_READ_DST_DST_Pos (0UL) /*!< Position of DST field. */
#define QSPI_READ_DST_DST_Msk (0xFFFFFFFFUL << QSPI_READ_DST_DST_Pos) /*!< Bit mask of DST field. */

/* Register: QSPI_READ_CNT */
/* Description: Read transfer length */

/* Bits 20..0 : Read transfer length in number of bytes. The length must be a multiple of 4 bytes. */
#define QSPI_READ_CNT_CNT_Pos (0UL) /*!< Position of CNT field. */
#define QSPI_READ_CNT_CNT_Msk (0x1FFFFFUL << QSPI_READ_CNT_CNT_Pos) /*!< Bit mask of CNT field. */

/* Register: QSPI_WRITE_DST */
/* Description: Flash destination address */

/* Bits 31..0 : Word-aligned flash destination address. */
#define QSPI_WRITE_DST_DST_Pos (0UL) /*!< Position of DST field. */
#define QSPI_WRITE_DST_DST_Msk (0xFFFFFFFFUL << QSPI_WRITE_DST_DST_Pos) /*!< Bit mask of DST field. */

/* Register: QSPI_WRITE_SRC */
/* Description: RAM source address */

/* Bits 31..0 : Word-aligned RAM source address. */
#define QSPI_WRITE_SRC_SRC_Pos (0UL) /*!< Position of SRC field. */
#define QSPI_WRITE_SRC_SRC_Msk (0xFFFFFFFFUL << QSPI_WRITE_SRC_SRC_Pos) /*!< Bit mask of SRC field. */

/* Register: QSPI_WRITE_CNT */
/* Description: Write transfer length */

/* Bits 20..0 : Write transfer length in number of bytes. The length must be a multiple of 4 bytes. */
#define QSPI_WRITE_CNT_CNT_Pos (0UL) /*!< Position of CNT field. */
#define QSPI_WRITE_CNT_CNT_Msk (0x1FFFFFUL << QSPI_WRITE_CNT_CNT_Pos) /*!< Bit mask of CNT field. */

/* Register: QSPI_ERASE_PTR */
/* Description: Start address of flash block to be erased */

/* Bits 31..0 : Word-aligned start address of block to be erased. */
#define QSPI_ERASE_PTR_PTR_Pos (0UL) /*!< Position of PTR field. */
#define QSPI_ERASE_PTR_PTR_Msk (0xFFFFFFFFUL << QSPI_ERASE_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: QSPI_ERASE_LEN */
/* Description: Size of block to be erased. */

/* Bits 1..0 : LEN */
#define QSPI_ERASE_LEN_LEN_Pos (0UL) /*!< Position of LEN field. */
#define QSPI_ERASE_LEN_LEN_Msk (0x3UL << QSPI_ERASE_LEN_LEN_Pos) /*!< Bit mask of LEN field. */
#define QSPI_ERASE_LEN_LEN_4KB (0UL) /*!< Erase 4 kB block (flash command 0x20) */
#define QSPI_ERASE_LEN_LEN_64KB (1UL) /*!< Erase 64 kB block (flash command 0xD8) */
#define QSPI_ERASE_LEN_LEN_All (2UL) /*!< Erase all (flash command 0xC7) */

/* Register: QSPI_PSEL_SCK */
/* Description: Pin select for serial clock SCK */

/* Bit 31 : Connection */
#define QSPI_PSEL_SCK_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define QSPI_PSEL_SCK_CONNECT_Msk (0x1UL << QSPI_PSEL_SCK_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define QSPI_PSEL_SCK_CONNECT_Connected (0UL) /*!< Connect */
#define QSPI_PSEL_SCK_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define QSPI_PSEL_SCK_PORT_Pos (5UL) /*!< Position of PORT field. */
#define QSPI_PSEL_SCK_PORT_Msk (0x3UL << QSPI_PSEL_SCK_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define QSPI_PSEL_SCK_PIN_Pos (0UL) /*!< Position of PIN field. */
#define QSPI_PSEL_SCK_PIN_Msk (0x1FUL << QSPI_PSEL_SCK_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: QSPI_PSEL_CSN */
/* Description: Pin select for chip select signal CSN. */

/* Bit 31 : Connection */
#define QSPI_PSEL_CSN_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define QSPI_PSEL_CSN_CONNECT_Msk (0x1UL << QSPI_PSEL_CSN_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define QSPI_PSEL_CSN_CONNECT_Connected (0UL) /*!< Connect */
#define QSPI_PSEL_CSN_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define QSPI_PSEL_CSN_PORT_Pos (5UL) /*!< Position of PORT field. */
#define QSPI_PSEL_CSN_PORT_Msk (0x3UL << QSPI_PSEL_CSN_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define QSPI_PSEL_CSN_PIN_Pos (0UL) /*!< Position of PIN field. */
#define QSPI_PSEL_CSN_PIN_Msk (0x1FUL << QSPI_PSEL_CSN_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: QSPI_PSEL_IO0 */
/* Description: Pin select for serial data MOSI/IO0. */

/* Bit 31 : Connection */
#define QSPI_PSEL_IO0_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define QSPI_PSEL_IO0_CONNECT_Msk (0x1UL << QSPI_PSEL_IO0_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define QSPI_PSEL_IO0_CONNECT_Connected (0UL) /*!< Connect */
#define QSPI_PSEL_IO0_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define QSPI_PSEL_IO0_PORT_Pos (5UL) /*!< Position of PORT field. */
#define QSPI_PSEL_IO0_PORT_Msk (0x3UL << QSPI_PSEL_IO0_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define QSPI_PSEL_IO0_PIN_Pos (0UL) /*!< Position of PIN field. */
#define QSPI_PSEL_IO0_PIN_Msk (0x1FUL << QSPI_PSEL_IO0_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: QSPI_PSEL_IO1 */
/* Description: Pin select for serial data MISO/IO1. */

/* Bit 31 : Connection */
#define QSPI_PSEL_IO1_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define QSPI_PSEL_IO1_CONNECT_Msk (0x1UL << QSPI_PSEL_IO1_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define QSPI_PSEL_IO1_CONNECT_Connected (0UL) /*!< Connect */
#define QSPI_PSEL_IO1_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define QSPI_PSEL_IO1_PORT_Pos (5UL) /*!< Position of PORT field. */
#define QSPI_PSEL_IO1_PORT_Msk (0x3UL << QSPI_PSEL_IO1_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define QSPI_PSEL_IO1_PIN_Pos (0UL) /*!< Position of PIN field. */
#define QSPI_PSEL_IO1_PIN_Msk (0x1FUL << QSPI_PSEL_IO1_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: QSPI_PSEL_IO2 */
/* Description: Pin select for serial data IO2. */

/* Bit 31 : Connection */
#define QSPI_PSEL_IO2_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define QSPI_PSEL_IO2_CONNECT_Msk (0x1UL << QSPI_PSEL_IO2_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define QSPI_PSEL_IO2_CONNECT_Connected (0UL) /*!< Connect */
#define QSPI_PSEL_IO2_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define QSPI_PSEL_IO2_PORT_Pos (5UL) /*!< Position of PORT field. */
#define QSPI_PSEL_IO2_PORT_Msk (0x3UL << QSPI_PSEL_IO2_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define QSPI_PSEL_IO2_PIN_Pos (0UL) /*!< Position of PIN field. */
#define QSPI_PSEL_IO2_PIN_Msk (0x1FUL << QSPI_PSEL_IO2_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: QSPI_PSEL_IO3 */
/* Description: Pin select for serial data IO3. */

/* Bit 31 : Connection */
#define QSPI_PSEL_IO3_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define QSPI_PSEL_IO3_CONNECT_Msk (0x1UL << QSPI_PSEL_IO3_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define QSPI_PSEL_IO3_CONNECT_Connected (0UL) /*!< Connect */
#define QSPI_PSEL_IO3_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define QSPI_PSEL_IO3_PORT_Pos (5UL) /*!< Position of PORT field. */
#define QSPI_PSEL_IO3_PORT_Msk (0x3UL << QSPI_PSEL_IO3_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define QSPI_PSEL_IO3_PIN_Pos (0UL) /*!< Position of PIN field. */
#define QSPI_PSEL_IO3_PIN_Msk (0x1FUL << QSPI_PSEL_IO3_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: QSPI_XIPOFFSET */
/* Description: Address offset into the external memory for Execute in Place operation. */

/* Bits 31..0 : Address offset into the external memory for Execute in Place operation. Value must be a multiple of 4. */
#define QSPI_XIPOFFSET_XIPOFFSET_Pos (0UL) /*!< Position of XIPOFFSET field. */
#define QSPI_XIPOFFSET_XIPOFFSET_Msk (0xFFFFFFFFUL << QSPI_XIPOFFSET_XIPOFFSET_Pos) /*!< Bit mask of XIPOFFSET field. */

/* Register: QSPI_IFCONFIG0 */
/* Description: Interface configuration. */

/* Bit 7 : Enable deep power-down mode (DPM) feature. */
#define QSPI_IFCONFIG0_DPMENABLE_Pos (7UL) /*!< Position of DPMENABLE field. */
#define QSPI_IFCONFIG0_DPMENABLE_Msk (0x1UL << QSPI_IFCONFIG0_DPMENABLE_Pos) /*!< Bit mask of DPMENABLE field. */
#define QSPI_IFCONFIG0_DPMENABLE_Disable (0UL) /*!< Disable DPM feature. */
#define QSPI_IFCONFIG0_DPMENABLE_Enable (1UL) /*!< Enable DPM feature. */

/* Bit 6 : Addressing mode. */
#define QSPI_IFCONFIG0_ADDRMODE_Pos (6UL) /*!< Position of ADDRMODE field. */
#define QSPI_IFCONFIG0_ADDRMODE_Msk (0x1UL << QSPI_IFCONFIG0_ADDRMODE_Pos) /*!< Bit mask of ADDRMODE field. */
#define QSPI_IFCONFIG0_ADDRMODE_24BIT (0UL) /*!< 24-bit addressing. */
#define QSPI_IFCONFIG0_ADDRMODE_32BIT (1UL) /*!< 32-bit addressing. */

/* Bits 5..3 : Configure number of data lines and opcode used for writing. */
#define QSPI_IFCONFIG0_WRITEOC_Pos (3UL) /*!< Position of WRITEOC field. */
#define QSPI_IFCONFIG0_WRITEOC_Msk (0x7UL << QSPI_IFCONFIG0_WRITEOC_Pos) /*!< Bit mask of WRITEOC field. */
#define QSPI_IFCONFIG0_WRITEOC_PP (0UL) /*!< Single data line SPI. PP (opcode 0x02). */
#define QSPI_IFCONFIG0_WRITEOC_PP2O (1UL) /*!< Dual data line SPI. PP2O (opcode 0xA2). */
#define QSPI_IFCONFIG0_WRITEOC_PP4O (2UL) /*!< Quad data line SPI. PP4O (opcode 0x32). */
#define QSPI_IFCONFIG0_WRITEOC_PP4IO (3UL) /*!< Quad data line SPI. PP4IO (opcode 0x38). */

/* Bits 2..0 : Configure number of data lines and opcode used for reading. */
#define QSPI_IFCONFIG0_READOC_Pos (0UL) /*!< Position of READOC field. */
#define QSPI_IFCONFIG0_READOC_Msk (0x7UL << QSPI_IFCONFIG0_READOC_Pos) /*!< Bit mask of READOC field. */
#define QSPI_IFCONFIG0_READOC_FASTREAD (0UL) /*!< Single data line SPI. FAST_READ (opcode 0x0B). */
#define QSPI_IFCONFIG0_READOC_READ2O (1UL) /*!< Dual data line SPI. READ2O (opcode 0x3B). */
#define QSPI_IFCONFIG0_READOC_READ2IO (2UL) /*!< Dual data line SPI. READ2IO (opcode 0xBB). */
#define QSPI_IFCONFIG0_READOC_READ4O (3UL) /*!< Quad data line SPI. READ4O (opcode 0x6B). */
#define QSPI_IFCONFIG0_READOC_READ4IO (4UL) /*!< Quad data line SPI. READ4IO (opcode 0xEB). */

/* Register: QSPI_IFCONFIG1 */
/* Description: Interface configuration. */

/* Bits 31..28 : SCK frequency is given as 32 MHz / (SCKFREQ + 1). */
#define QSPI_IFCONFIG1_SCKFREQ_Pos (28UL) /*!< Position of SCKFREQ field. */
#define QSPI_IFCONFIG1_SCKFREQ_Msk (0xFUL << QSPI_IFCONFIG1_SCKFREQ_Pos) /*!< Bit mask of SCKFREQ field. */

/* Bit 25 : Select SPI mode. */
#define QSPI_IFCONFIG1_SPIMODE_Pos (25UL) /*!< Position of SPIMODE field. */
#define QSPI_IFCONFIG1_SPIMODE_Msk (0x1UL << QSPI_IFCONFIG1_SPIMODE_Pos) /*!< Bit mask of SPIMODE field. */
#define QSPI_IFCONFIG1_SPIMODE_MODE0 (0UL) /*!< Mode 0: Data are captured on the clock's rising edge and data is output on a falling edge. Base level of clock is 0 (CPOL=0, CPHA=0). */
#define QSPI_IFCONFIG1_SPIMODE_MODE3 (1UL) /*!< Mode 3: Data are captured on the clock's falling edge and data is output on a rising edge. Base level of clock is 1 (CPOL=1, CPHA=1). */

/* Bit 24 : Enter/exit deep power-down mode (DPM) for external flash memory. */
#define QSPI_IFCONFIG1_DPMEN_Pos (24UL) /*!< Position of DPMEN field. */
#define QSPI_IFCONFIG1_DPMEN_Msk (0x1UL << QSPI_IFCONFIG1_DPMEN_Pos) /*!< Bit mask of DPMEN field. */
#define QSPI_IFCONFIG1_DPMEN_Exit (0UL) /*!< Exit DPM. */
#define QSPI_IFCONFIG1_DPMEN_Enter (1UL) /*!< Enter DPM. */

/* Bits 7..0 : Minimum amount of time that the CSN pin must stay high before it can go low again. Value is specified in number of 16 MHz periods (62.5 ns). */
#define QSPI_IFCONFIG1_SCKDELAY_Pos (0UL) /*!< Position of SCKDELAY field. */
#define QSPI_IFCONFIG1_SCKDELAY_Msk (0xFFUL << QSPI_IFCONFIG1_SCKDELAY_Pos) /*!< Bit mask of SCKDELAY field. */

/* Register: QSPI_STATUS */
/* Description: Status register. */

/* Bits 31..24 : Value of external flash devices Status Register. When the external flash has two bytes status register this field includes the value of the low byte. */
#define QSPI_STATUS_SREG_Pos (24UL) /*!< Position of SREG field. */
#define QSPI_STATUS_SREG_Msk (0xFFUL << QSPI_STATUS_SREG_Pos) /*!< Bit mask of SREG field. */

/* Bit 3 : Ready status. */
#define QSPI_STATUS_READY_Pos (3UL) /*!< Position of READY field. */
#define QSPI_STATUS_READY_Msk (0x1UL << QSPI_STATUS_READY_Pos) /*!< Bit mask of READY field. */
#define QSPI_STATUS_READY_BUSY (0UL) /*!< QSPI peripheral is busy. It is not allowed to trigger any new tasks, writing custom instructions or enter/exit DPM. */
#define QSPI_STATUS_READY_READY (1UL) /*!< QSPI peripheral is ready. It is allowed to trigger new tasks, writing custom instructions or enter/exit DPM. */

/* Bit 2 : Deep power-down mode (DPM) status of external flash. */
#define QSPI_STATUS_DPM_Pos (2UL) /*!< Position of DPM field. */
#define QSPI_STATUS_DPM_Msk (0x1UL << QSPI_STATUS_DPM_Pos) /*!< Bit mask of DPM field. */
#define QSPI_STATUS_DPM_Disabled (0UL) /*!< External flash is not in DPM. */
#define QSPI_STATUS_DPM_Enabled (1UL) /*!< External flash is in DPM. */

/* Register: QSPI_DPMDUR */
/* Description: Set the duration required to enter/exit deep power-down mode (DPM). */

/* Bits 31..16 : Duration needed by external flash to exit DPM. Duration is given as EXIT * 256 * 62.5 ns. */
#define QSPI_DPMDUR_EXIT_Pos (16UL) /*!< Position of EXIT field. */
#define QSPI_DPMDUR_EXIT_Msk (0xFFFFUL << QSPI_DPMDUR_EXIT_Pos) /*!< Bit mask of EXIT field. */

/* Bits 15..0 : Duration needed by external flash to enter DPM. Duration is given as ENTER * 256 * 62.5 ns. */
#define QSPI_DPMDUR_ENTER_Pos (0UL) /*!< Position of ENTER field. */
#define QSPI_DPMDUR_ENTER_Msk (0xFFFFUL << QSPI_DPMDUR_ENTER_Pos) /*!< Bit mask of ENTER field. */

/* Register: QSPI_ADDRCONF */
/* Description: Extended address configuration. */

/* Bit 27 : Send WREN (write enable opcode 0x06) before instruction. */
#define QSPI_ADDRCONF_WREN_Pos (27UL) /*!< Position of WREN field. */
#define QSPI_ADDRCONF_WREN_Msk (0x1UL << QSPI_ADDRCONF_WREN_Pos) /*!< Bit mask of WREN field. */
#define QSPI_ADDRCONF_WREN_Disable (0UL) /*!< Do not send WREN. */
#define QSPI_ADDRCONF_WREN_Enable (1UL) /*!< Send WREN. */

/* Bit 26 : Wait for write complete before sending command. */
#define QSPI_ADDRCONF_WIPWAIT_Pos (26UL) /*!< Position of WIPWAIT field. */
#define QSPI_ADDRCONF_WIPWAIT_Msk (0x1UL << QSPI_ADDRCONF_WIPWAIT_Pos) /*!< Bit mask of WIPWAIT field. */
#define QSPI_ADDRCONF_WIPWAIT_Disable (0UL) /*!< No wait. */
#define QSPI_ADDRCONF_WIPWAIT_Enable (1UL) /*!< Wait. */

/* Bits 25..24 : Extended addressing mode. */
#define QSPI_ADDRCONF_MODE_Pos (24UL) /*!< Position of MODE field. */
#define QSPI_ADDRCONF_MODE_Msk (0x3UL << QSPI_ADDRCONF_MODE_Pos) /*!< Bit mask of MODE field. */
#define QSPI_ADDRCONF_MODE_NoInstr (0UL) /*!< Do not send any instruction. */
#define QSPI_ADDRCONF_MODE_Opcode (1UL) /*!< Send opcode. */
#define QSPI_ADDRCONF_MODE_OpByte0 (2UL) /*!< Send opcode, byte0. */
#define QSPI_ADDRCONF_MODE_All (3UL) /*!< Send opcode, byte0, byte1. */

/* Bits 23..16 : Byte 1 following byte 0. */
#define QSPI_ADDRCONF_BYTE1_Pos (16UL) /*!< Position of BYTE1 field. */
#define QSPI_ADDRCONF_BYTE1_Msk (0xFFUL << QSPI_ADDRCONF_BYTE1_Pos) /*!< Bit mask of BYTE1 field. */

/* Bits 15..8 : Byte 0 following opcode. */
#define QSPI_ADDRCONF_BYTE0_Pos (8UL) /*!< Position of BYTE0 field. */
#define QSPI_ADDRCONF_BYTE0_Msk (0xFFUL << QSPI_ADDRCONF_BYTE0_Pos) /*!< Bit mask of BYTE0 field. */

/* Bits 7..0 : Opcode that enters the 32-bit addressing mode. */
#define QSPI_ADDRCONF_OPCODE_Pos (0UL) /*!< Position of OPCODE field. */
#define QSPI_ADDRCONF_OPCODE_Msk (0xFFUL << QSPI_ADDRCONF_OPCODE_Pos) /*!< Bit mask of OPCODE field. */

/* Register: QSPI_CINSTRCONF */
/* Description: Custom instruction configuration register. */

/* Bit 15 : Send WREN (write enable opcode 0x06) before instruction. */
#define QSPI_CINSTRCONF_WREN_Pos (15UL) /*!< Position of WREN field. */
#define QSPI_CINSTRCONF_WREN_Msk (0x1UL << QSPI_CINSTRCONF_WREN_Pos) /*!< Bit mask of WREN field. */
#define QSPI_CINSTRCONF_WREN_Disable (0UL) /*!< Do not send WREN. */
#define QSPI_CINSTRCONF_WREN_Enable (1UL) /*!< Send WREN. */

/* Bit 14 : Wait for write complete before sending command. */
#define QSPI_CINSTRCONF_WIPWAIT_Pos (14UL) /*!< Position of WIPWAIT field. */
#define QSPI_CINSTRCONF_WIPWAIT_Msk (0x1UL << QSPI_CINSTRCONF_WIPWAIT_Pos) /*!< Bit mask of WIPWAIT field. */
#define QSPI_CINSTRCONF_WIPWAIT_Disable (0UL) /*!< No wait. */
#define QSPI_CINSTRCONF_WIPWAIT_Enable (1UL) /*!< Wait. */

/* Bit 13 : Level of the IO3 pin (if connected) during transmission of custom instruction. */
#define QSPI_CINSTRCONF_LIO3_Pos (13UL) /*!< Position of LIO3 field. */
#define QSPI_CINSTRCONF_LIO3_Msk (0x1UL << QSPI_CINSTRCONF_LIO3_Pos) /*!< Bit mask of LIO3 field. */

/* Bit 12 : Level of the IO2 pin (if connected) during transmission of custom instruction. */
#define QSPI_CINSTRCONF_LIO2_Pos (12UL) /*!< Position of LIO2 field. */
#define QSPI_CINSTRCONF_LIO2_Msk (0x1UL << QSPI_CINSTRCONF_LIO2_Pos) /*!< Bit mask of LIO2 field. */

/* Bits 11..8 : Length of custom instruction in number of bytes. */
#define QSPI_CINSTRCONF_LENGTH_Pos (8UL) /*!< Position of LENGTH field. */
#define QSPI_CINSTRCONF_LENGTH_Msk (0xFUL << QSPI_CINSTRCONF_LENGTH_Pos) /*!< Bit mask of LENGTH field. */
#define QSPI_CINSTRCONF_LENGTH_1B (1UL) /*!< Send opcode only. */
#define QSPI_CINSTRCONF_LENGTH_2B (2UL) /*!< Send opcode, CINSTRDAT0.BYTE0. */
#define QSPI_CINSTRCONF_LENGTH_3B (3UL) /*!< Send opcode, CINSTRDAT0.BYTE0 -&gt; CINSTRDAT0.BYTE1. */
#define QSPI_CINSTRCONF_LENGTH_4B (4UL) /*!< Send opcode, CINSTRDAT0.BYTE0 -&gt; CINSTRDAT0.BYTE2. */
#define QSPI_CINSTRCONF_LENGTH_5B (5UL) /*!< Send opcode, CINSTRDAT0.BYTE0 -&gt; CINSTRDAT0.BYTE3. */
#define QSPI_CINSTRCONF_LENGTH_6B (6UL) /*!< Send opcode, CINSTRDAT0.BYTE0 -&gt; CINSTRDAT1.BYTE4. */
#define QSPI_CINSTRCONF_LENGTH_7B (7UL) /*!< Send opcode, CINSTRDAT0.BYTE0 -&gt; CINSTRDAT1.BYTE5. */
#define QSPI_CINSTRCONF_LENGTH_8B (8UL) /*!< Send opcode, CINSTRDAT0.BYTE0 -&gt; CINSTRDAT1.BYTE6. */
#define QSPI_CINSTRCONF_LENGTH_9B (9UL) /*!< Send opcode, CINSTRDAT0.BYTE0 -&gt; CINSTRDAT1.BYTE7. */

/* Bits 7..0 : Opcode of Custom instruction. */
#define QSPI_CINSTRCONF_OPCODE_Pos (0UL) /*!< Position of OPCODE field. */
#define QSPI_CINSTRCONF_OPCODE_Msk (0xFFUL << QSPI_CINSTRCONF_OPCODE_Pos) /*!< Bit mask of OPCODE field. */

/* Register: QSPI_CINSTRDAT0 */
/* Description: Custom instruction data register 0. */

/* Bits 31..24 : Data byte 3 */
#define QSPI_CINSTRDAT0_BYTE3_Pos (24UL) /*!< Position of BYTE3 field. */
#define QSPI_CINSTRDAT0_BYTE3_Msk (0xFFUL << QSPI_CINSTRDAT0_BYTE3_Pos) /*!< Bit mask of BYTE3 field. */

/* Bits 23..16 : Data byte 2 */
#define QSPI_CINSTRDAT0_BYTE2_Pos (16UL) /*!< Position of BYTE2 field. */
#define QSPI_CINSTRDAT0_BYTE2_Msk (0xFFUL << QSPI_CINSTRDAT0_BYTE2_Pos) /*!< Bit mask of BYTE2 field. */

/* Bits 15..8 : Data byte 1 */
#define QSPI_CINSTRDAT0_BYTE1_Pos (8UL) /*!< Position of BYTE1 field. */
#define QSPI_CINSTRDAT0_BYTE1_Msk (0xFFUL << QSPI_CINSTRDAT0_BYTE1_Pos) /*!< Bit mask of BYTE1 field. */

/* Bits 7..0 : Data byte 0 */
#define QSPI_CINSTRDAT0_BYTE0_Pos (0UL) /*!< Position of BYTE0 field. */
#define QSPI_CINSTRDAT0_BYTE0_Msk (0xFFUL << QSPI_CINSTRDAT0_BYTE0_Pos) /*!< Bit mask of BYTE0 field. */

/* Register: QSPI_CINSTRDAT1 */
/* Description: Custom instruction data register 1. */

/* Bits 31..24 : Data byte 7 */
#define QSPI_CINSTRDAT1_BYTE7_Pos (24UL) /*!< Position of BYTE7 field. */
#define QSPI_CINSTRDAT1_BYTE7_Msk (0xFFUL << QSPI_CINSTRDAT1_BYTE7_Pos) /*!< Bit mask of BYTE7 field. */

/* Bits 23..16 : Data byte 6 */
#define QSPI_CINSTRDAT1_BYTE6_Pos (16UL) /*!< Position of BYTE6 field. */
#define QSPI_CINSTRDAT1_BYTE6_Msk (0xFFUL << QSPI_CINSTRDAT1_BYTE6_Pos) /*!< Bit mask of BYTE6 field. */

/* Bits 15..8 : Data byte 5 */
#define QSPI_CINSTRDAT1_BYTE5_Pos (8UL) /*!< Position of BYTE5 field. */
#define QSPI_CINSTRDAT1_BYTE5_Msk (0xFFUL << QSPI_CINSTRDAT1_BYTE5_Pos) /*!< Bit mask of BYTE5 field. */

/* Bits 7..0 : Data byte 4 */
#define QSPI_CINSTRDAT1_BYTE4_Pos (0UL) /*!< Position of BYTE4 field. */
#define QSPI_CINSTRDAT1_BYTE4_Msk (0xFFUL << QSPI_CINSTRDAT1_BYTE4_Pos) /*!< Bit mask of BYTE4 field. */

/* Register: QSPI_IFTIMING */
/* Description: SPI interface timing. */

/* Bits 10..8 : Timing related to sampling of the input serial data. The value of RXDELAY specifies the number of 64 MHz cycles (15.625 ns) delay from the the rising edge of the SPI Clock (SCK) until the input serial data is sampled. As en example, if set to 0 the input serial data is sampled on the rising edge of SCK. */
#define QSPI_IFTIMING_RXDELAY_Pos (8UL) /*!< Position of RXDELAY field. */
#define QSPI_IFTIMING_RXDELAY_Msk (0x7UL << QSPI_IFTIMING_RXDELAY_Pos) /*!< Bit mask of RXDELAY field. */


/* Peripheral: RADIO */
/* Description: 2.4 GHz Radio */

/* Register: RADIO_SHORTS */
/* Description: Shortcut register */

/* Bit 19 : Shortcut between RXREADY event and START task */
#define RADIO_SHORTS_RXREADY_START_Pos (19UL) /*!< Position of RXREADY_START field. */
#define RADIO_SHORTS_RXREADY_START_Msk (0x1UL << RADIO_SHORTS_RXREADY_START_Pos) /*!< Bit mask of RXREADY_START field. */
#define RADIO_SHORTS_RXREADY_START_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_RXREADY_START_Enabled (1UL) /*!< Enable shortcut */

/* Bit 18 : Shortcut between TXREADY event and START task */
#define RADIO_SHORTS_TXREADY_START_Pos (18UL) /*!< Position of TXREADY_START field. */
#define RADIO_SHORTS_TXREADY_START_Msk (0x1UL << RADIO_SHORTS_TXREADY_START_Pos) /*!< Bit mask of TXREADY_START field. */
#define RADIO_SHORTS_TXREADY_START_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_TXREADY_START_Enabled (1UL) /*!< Enable shortcut */

/* Bit 17 : Shortcut between CCAIDLE event and STOP task */
#define RADIO_SHORTS_CCAIDLE_STOP_Pos (17UL) /*!< Position of CCAIDLE_STOP field. */
#define RADIO_SHORTS_CCAIDLE_STOP_Msk (0x1UL << RADIO_SHORTS_CCAIDLE_STOP_Pos) /*!< Bit mask of CCAIDLE_STOP field. */
#define RADIO_SHORTS_CCAIDLE_STOP_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_CCAIDLE_STOP_Enabled (1UL) /*!< Enable shortcut */

/* Bit 16 : Shortcut between EDEND event and DISABLE task */
#define RADIO_SHORTS_EDEND_DISABLE_Pos (16UL) /*!< Position of EDEND_DISABLE field. */
#define RADIO_SHORTS_EDEND_DISABLE_Msk (0x1UL << RADIO_SHORTS_EDEND_DISABLE_Pos) /*!< Bit mask of EDEND_DISABLE field. */
#define RADIO_SHORTS_EDEND_DISABLE_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_EDEND_DISABLE_Enabled (1UL) /*!< Enable shortcut */

/* Bit 15 : Shortcut between READY event and EDSTART task */
#define RADIO_SHORTS_READY_EDSTART_Pos (15UL) /*!< Position of READY_EDSTART field. */
#define RADIO_SHORTS_READY_EDSTART_Msk (0x1UL << RADIO_SHORTS_READY_EDSTART_Pos) /*!< Bit mask of READY_EDSTART field. */
#define RADIO_SHORTS_READY_EDSTART_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_READY_EDSTART_Enabled (1UL) /*!< Enable shortcut */

/* Bit 14 : Shortcut between FRAMESTART event and BCSTART task */
#define RADIO_SHORTS_FRAMESTART_BCSTART_Pos (14UL) /*!< Position of FRAMESTART_BCSTART field. */
#define RADIO_SHORTS_FRAMESTART_BCSTART_Msk (0x1UL << RADIO_SHORTS_FRAMESTART_BCSTART_Pos) /*!< Bit mask of FRAMESTART_BCSTART field. */
#define RADIO_SHORTS_FRAMESTART_BCSTART_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_FRAMESTART_BCSTART_Enabled (1UL) /*!< Enable shortcut */

/* Bit 13 : Shortcut between CCABUSY event and DISABLE task */
#define RADIO_SHORTS_CCABUSY_DISABLE_Pos (13UL) /*!< Position of CCABUSY_DISABLE field. */
#define RADIO_SHORTS_CCABUSY_DISABLE_Msk (0x1UL << RADIO_SHORTS_CCABUSY_DISABLE_Pos) /*!< Bit mask of CCABUSY_DISABLE field. */
#define RADIO_SHORTS_CCABUSY_DISABLE_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_CCABUSY_DISABLE_Enabled (1UL) /*!< Enable shortcut */

/* Bit 12 : Shortcut between CCAIDLE event and TXEN task */
#define RADIO_SHORTS_CCAIDLE_TXEN_Pos (12UL) /*!< Position of CCAIDLE_TXEN field. */
#define RADIO_SHORTS_CCAIDLE_TXEN_Msk (0x1UL << RADIO_SHORTS_CCAIDLE_TXEN_Pos) /*!< Bit mask of CCAIDLE_TXEN field. */
#define RADIO_SHORTS_CCAIDLE_TXEN_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_CCAIDLE_TXEN_Enabled (1UL) /*!< Enable shortcut */

/* Bit 11 : Shortcut between RXREADY event and CCASTART task */
#define RADIO_SHORTS_RXREADY_CCASTART_Pos (11UL) /*!< Position of RXREADY_CCASTART field. */
#define RADIO_SHORTS_RXREADY_CCASTART_Msk (0x1UL << RADIO_SHORTS_RXREADY_CCASTART_Pos) /*!< Bit mask of RXREADY_CCASTART field. */
#define RADIO_SHORTS_RXREADY_CCASTART_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_RXREADY_CCASTART_Enabled (1UL) /*!< Enable shortcut */

/* Bit 8 : Shortcut between DISABLED event and RSSISTOP task */
#define RADIO_SHORTS_DISABLED_RSSISTOP_Pos (8UL) /*!< Position of DISABLED_RSSISTOP field. */
#define RADIO_SHORTS_DISABLED_RSSISTOP_Msk (0x1UL << RADIO_SHORTS_DISABLED_RSSISTOP_Pos) /*!< Bit mask of DISABLED_RSSISTOP field. */
#define RADIO_SHORTS_DISABLED_RSSISTOP_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_DISABLED_RSSISTOP_Enabled (1UL) /*!< Enable shortcut */

/* Bit 6 : Shortcut between ADDRESS event and BCSTART task */
#define RADIO_SHORTS_ADDRESS_BCSTART_Pos (6UL) /*!< Position of ADDRESS_BCSTART field. */
#define RADIO_SHORTS_ADDRESS_BCSTART_Msk (0x1UL << RADIO_SHORTS_ADDRESS_BCSTART_Pos) /*!< Bit mask of ADDRESS_BCSTART field. */
#define RADIO_SHORTS_ADDRESS_BCSTART_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_ADDRESS_BCSTART_Enabled (1UL) /*!< Enable shortcut */

/* Bit 5 : Shortcut between END event and START task */
#define RADIO_SHORTS_END_START_Pos (5UL) /*!< Position of END_START field. */
#define RADIO_SHORTS_END_START_Msk (0x1UL << RADIO_SHORTS_END_START_Pos) /*!< Bit mask of END_START field. */
#define RADIO_SHORTS_END_START_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_END_START_Enabled (1UL) /*!< Enable shortcut */

/* Bit 4 : Shortcut between ADDRESS event and RSSISTART task */
#define RADIO_SHORTS_ADDRESS_RSSISTART_Pos (4UL) /*!< Position of ADDRESS_RSSISTART field. */
#define RADIO_SHORTS_ADDRESS_RSSISTART_Msk (0x1UL << RADIO_SHORTS_ADDRESS_RSSISTART_Pos) /*!< Bit mask of ADDRESS_RSSISTART field. */
#define RADIO_SHORTS_ADDRESS_RSSISTART_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_ADDRESS_RSSISTART_Enabled (1UL) /*!< Enable shortcut */

/* Bit 3 : Shortcut between DISABLED event and RXEN task */
#define RADIO_SHORTS_DISABLED_RXEN_Pos (3UL) /*!< Position of DISABLED_RXEN field. */
#define RADIO_SHORTS_DISABLED_RXEN_Msk (0x1UL << RADIO_SHORTS_DISABLED_RXEN_Pos) /*!< Bit mask of DISABLED_RXEN field. */
#define RADIO_SHORTS_DISABLED_RXEN_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_DISABLED_RXEN_Enabled (1UL) /*!< Enable shortcut */

/* Bit 2 : Shortcut between DISABLED event and TXEN task */
#define RADIO_SHORTS_DISABLED_TXEN_Pos (2UL) /*!< Position of DISABLED_TXEN field. */
#define RADIO_SHORTS_DISABLED_TXEN_Msk (0x1UL << RADIO_SHORTS_DISABLED_TXEN_Pos) /*!< Bit mask of DISABLED_TXEN field. */
#define RADIO_SHORTS_DISABLED_TXEN_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_DISABLED_TXEN_Enabled (1UL) /*!< Enable shortcut */

/* Bit 1 : Shortcut between END event and DISABLE task */
#define RADIO_SHORTS_END_DISABLE_Pos (1UL) /*!< Position of END_DISABLE field. */
#define RADIO_SHORTS_END_DISABLE_Msk (0x1UL << RADIO_SHORTS_END_DISABLE_Pos) /*!< Bit mask of END_DISABLE field. */
#define RADIO_SHORTS_END_DISABLE_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_END_DISABLE_Enabled (1UL) /*!< Enable shortcut */

/* Bit 0 : Shortcut between READY event and START task */
#define RADIO_SHORTS_READY_START_Pos (0UL) /*!< Position of READY_START field. */
#define RADIO_SHORTS_READY_START_Msk (0x1UL << RADIO_SHORTS_READY_START_Pos) /*!< Bit mask of READY_START field. */
#define RADIO_SHORTS_READY_START_Disabled (0UL) /*!< Disable shortcut */
#define RADIO_SHORTS_READY_START_Enabled (1UL) /*!< Enable shortcut */

/* Register: RADIO_INTENSET */
/* Description: Enable interrupt */

/* Bit 23 : Write '1' to Enable interrupt for MHRMATCH event */
#define RADIO_INTENSET_MHRMATCH_Pos (23UL) /*!< Position of MHRMATCH field. */
#define RADIO_INTENSET_MHRMATCH_Msk (0x1UL << RADIO_INTENSET_MHRMATCH_Pos) /*!< Bit mask of MHRMATCH field. */
#define RADIO_INTENSET_MHRMATCH_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_MHRMATCH_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_MHRMATCH_Set (1UL) /*!< Enable */

/* Bit 22 : Write '1' to Enable interrupt for RXREADY event */
#define RADIO_INTENSET_RXREADY_Pos (22UL) /*!< Position of RXREADY field. */
#define RADIO_INTENSET_RXREADY_Msk (0x1UL << RADIO_INTENSET_RXREADY_Pos) /*!< Bit mask of RXREADY field. */
#define RADIO_INTENSET_RXREADY_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_RXREADY_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_RXREADY_Set (1UL) /*!< Enable */

/* Bit 21 : Write '1' to Enable interrupt for TXREADY event */
#define RADIO_INTENSET_TXREADY_Pos (21UL) /*!< Position of TXREADY field. */
#define RADIO_INTENSET_TXREADY_Msk (0x1UL << RADIO_INTENSET_TXREADY_Pos) /*!< Bit mask of TXREADY field. */
#define RADIO_INTENSET_TXREADY_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_TXREADY_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_TXREADY_Set (1UL) /*!< Enable */

/* Bit 20 : Write '1' to Enable interrupt for RATEBOOST event */
#define RADIO_INTENSET_RATEBOOST_Pos (20UL) /*!< Position of RATEBOOST field. */
#define RADIO_INTENSET_RATEBOOST_Msk (0x1UL << RADIO_INTENSET_RATEBOOST_Pos) /*!< Bit mask of RATEBOOST field. */
#define RADIO_INTENSET_RATEBOOST_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_RATEBOOST_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_RATEBOOST_Set (1UL) /*!< Enable */

/* Bit 19 : Write '1' to Enable interrupt for CCASTOPPED event */
#define RADIO_INTENSET_CCASTOPPED_Pos (19UL) /*!< Position of CCASTOPPED field. */
#define RADIO_INTENSET_CCASTOPPED_Msk (0x1UL << RADIO_INTENSET_CCASTOPPED_Pos) /*!< Bit mask of CCASTOPPED field. */
#define RADIO_INTENSET_CCASTOPPED_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_CCASTOPPED_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_CCASTOPPED_Set (1UL) /*!< Enable */

/* Bit 18 : Write '1' to Enable interrupt for CCABUSY event */
#define RADIO_INTENSET_CCABUSY_Pos (18UL) /*!< Position of CCABUSY field. */
#define RADIO_INTENSET_CCABUSY_Msk (0x1UL << RADIO_INTENSET_CCABUSY_Pos) /*!< Bit mask of CCABUSY field. */
#define RADIO_INTENSET_CCABUSY_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_CCABUSY_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_CCABUSY_Set (1UL) /*!< Enable */

/* Bit 17 : Write '1' to Enable interrupt for CCAIDLE event */
#define RADIO_INTENSET_CCAIDLE_Pos (17UL) /*!< Position of CCAIDLE field. */
#define RADIO_INTENSET_CCAIDLE_Msk (0x1UL << RADIO_INTENSET_CCAIDLE_Pos) /*!< Bit mask of CCAIDLE field. */
#define RADIO_INTENSET_CCAIDLE_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_CCAIDLE_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_CCAIDLE_Set (1UL) /*!< Enable */

/* Bit 16 : Write '1' to Enable interrupt for EDSTOPPED event */
#define RADIO_INTENSET_EDSTOPPED_Pos (16UL) /*!< Position of EDSTOPPED field. */
#define RADIO_INTENSET_EDSTOPPED_Msk (0x1UL << RADIO_INTENSET_EDSTOPPED_Pos) /*!< Bit mask of EDSTOPPED field. */
#define RADIO_INTENSET_EDSTOPPED_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_EDSTOPPED_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_EDSTOPPED_Set (1UL) /*!< Enable */

/* Bit 15 : Write '1' to Enable interrupt for EDEND event */
#define RADIO_INTENSET_EDEND_Pos (15UL) /*!< Position of EDEND field. */
#define RADIO_INTENSET_EDEND_Msk (0x1UL << RADIO_INTENSET_EDEND_Pos) /*!< Bit mask of EDEND field. */
#define RADIO_INTENSET_EDEND_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_EDEND_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_EDEND_Set (1UL) /*!< Enable */

/* Bit 14 : Write '1' to Enable interrupt for FRAMESTART event */
#define RADIO_INTENSET_FRAMESTART_Pos (14UL) /*!< Position of FRAMESTART field. */
#define RADIO_INTENSET_FRAMESTART_Msk (0x1UL << RADIO_INTENSET_FRAMESTART_Pos) /*!< Bit mask of FRAMESTART field. */
#define RADIO_INTENSET_FRAMESTART_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_FRAMESTART_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_FRAMESTART_Set (1UL) /*!< Enable */

/* Bit 13 : Write '1' to Enable interrupt for CRCERROR event */
#define RADIO_INTENSET_CRCERROR_Pos (13UL) /*!< Position of CRCERROR field. */
#define RADIO_INTENSET_CRCERROR_Msk (0x1UL << RADIO_INTENSET_CRCERROR_Pos) /*!< Bit mask of CRCERROR field. */
#define RADIO_INTENSET_CRCERROR_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_CRCERROR_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_CRCERROR_Set (1UL) /*!< Enable */

/* Bit 12 : Write '1' to Enable interrupt for CRCOK event */
#define RADIO_INTENSET_CRCOK_Pos (12UL) /*!< Position of CRCOK field. */
#define RADIO_INTENSET_CRCOK_Msk (0x1UL << RADIO_INTENSET_CRCOK_Pos) /*!< Bit mask of CRCOK field. */
#define RADIO_INTENSET_CRCOK_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_CRCOK_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_CRCOK_Set (1UL) /*!< Enable */

/* Bit 10 : Write '1' to Enable interrupt for BCMATCH event */
#define RADIO_INTENSET_BCMATCH_Pos (10UL) /*!< Position of BCMATCH field. */
#define RADIO_INTENSET_BCMATCH_Msk (0x1UL << RADIO_INTENSET_BCMATCH_Pos) /*!< Bit mask of BCMATCH field. */
#define RADIO_INTENSET_BCMATCH_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_BCMATCH_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_BCMATCH_Set (1UL) /*!< Enable */

/* Bit 7 : Write '1' to Enable interrupt for RSSIEND event */
#define RADIO_INTENSET_RSSIEND_Pos (7UL) /*!< Position of RSSIEND field. */
#define RADIO_INTENSET_RSSIEND_Msk (0x1UL << RADIO_INTENSET_RSSIEND_Pos) /*!< Bit mask of RSSIEND field. */
#define RADIO_INTENSET_RSSIEND_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_RSSIEND_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_RSSIEND_Set (1UL) /*!< Enable */

/* Bit 6 : Write '1' to Enable interrupt for DEVMISS event */
#define RADIO_INTENSET_DEVMISS_Pos (6UL) /*!< Position of DEVMISS field. */
#define RADIO_INTENSET_DEVMISS_Msk (0x1UL << RADIO_INTENSET_DEVMISS_Pos) /*!< Bit mask of DEVMISS field. */
#define RADIO_INTENSET_DEVMISS_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_DEVMISS_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_DEVMISS_Set (1UL) /*!< Enable */

/* Bit 5 : Write '1' to Enable interrupt for DEVMATCH event */
#define RADIO_INTENSET_DEVMATCH_Pos (5UL) /*!< Position of DEVMATCH field. */
#define RADIO_INTENSET_DEVMATCH_Msk (0x1UL << RADIO_INTENSET_DEVMATCH_Pos) /*!< Bit mask of DEVMATCH field. */
#define RADIO_INTENSET_DEVMATCH_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_DEVMATCH_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_DEVMATCH_Set (1UL) /*!< Enable */

/* Bit 4 : Write '1' to Enable interrupt for DISABLED event */
#define RADIO_INTENSET_DISABLED_Pos (4UL) /*!< Position of DISABLED field. */
#define RADIO_INTENSET_DISABLED_Msk (0x1UL << RADIO_INTENSET_DISABLED_Pos) /*!< Bit mask of DISABLED field. */
#define RADIO_INTENSET_DISABLED_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_DISABLED_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_DISABLED_Set (1UL) /*!< Enable */

/* Bit 3 : Write '1' to Enable interrupt for END event */
#define RADIO_INTENSET_END_Pos (3UL) /*!< Position of END field. */
#define RADIO_INTENSET_END_Msk (0x1UL << RADIO_INTENSET_END_Pos) /*!< Bit mask of END field. */
#define RADIO_INTENSET_END_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_END_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_END_Set (1UL) /*!< Enable */

/* Bit 2 : Write '1' to Enable interrupt for PAYLOAD event */
#define RADIO_INTENSET_PAYLOAD_Pos (2UL) /*!< Position of PAYLOAD field. */
#define RADIO_INTENSET_PAYLOAD_Msk (0x1UL << RADIO_INTENSET_PAYLOAD_Pos) /*!< Bit mask of PAYLOAD field. */
#define RADIO_INTENSET_PAYLOAD_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_PAYLOAD_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_PAYLOAD_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable interrupt for ADDRESS event */
#define RADIO_INTENSET_ADDRESS_Pos (1UL) /*!< Position of ADDRESS field. */
#define RADIO_INTENSET_ADDRESS_Msk (0x1UL << RADIO_INTENSET_ADDRESS_Pos) /*!< Bit mask of ADDRESS field. */
#define RADIO_INTENSET_ADDRESS_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_ADDRESS_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_ADDRESS_Set (1UL) /*!< Enable */

/* Bit 0 : Write '1' to Enable interrupt for READY event */
#define RADIO_INTENSET_READY_Pos (0UL) /*!< Position of READY field. */
#define RADIO_INTENSET_READY_Msk (0x1UL << RADIO_INTENSET_READY_Pos) /*!< Bit mask of READY field. */
#define RADIO_INTENSET_READY_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENSET_READY_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENSET_READY_Set (1UL) /*!< Enable */

/* Register: RADIO_INTENCLR */
/* Description: Disable interrupt */

/* Bit 23 : Write '1' to Disable interrupt for MHRMATCH event */
#define RADIO_INTENCLR_MHRMATCH_Pos (23UL) /*!< Position of MHRMATCH field. */
#define RADIO_INTENCLR_MHRMATCH_Msk (0x1UL << RADIO_INTENCLR_MHRMATCH_Pos) /*!< Bit mask of MHRMATCH field. */
#define RADIO_INTENCLR_MHRMATCH_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_MHRMATCH_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_MHRMATCH_Clear (1UL) /*!< Disable */

/* Bit 22 : Write '1' to Disable interrupt for RXREADY event */
#define RADIO_INTENCLR_RXREADY_Pos (22UL) /*!< Position of RXREADY field. */
#define RADIO_INTENCLR_RXREADY_Msk (0x1UL << RADIO_INTENCLR_RXREADY_Pos) /*!< Bit mask of RXREADY field. */
#define RADIO_INTENCLR_RXREADY_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_RXREADY_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_RXREADY_Clear (1UL) /*!< Disable */

/* Bit 21 : Write '1' to Disable interrupt for TXREADY event */
#define RADIO_INTENCLR_TXREADY_Pos (21UL) /*!< Position of TXREADY field. */
#define RADIO_INTENCLR_TXREADY_Msk (0x1UL << RADIO_INTENCLR_TXREADY_Pos) /*!< Bit mask of TXREADY field. */
#define RADIO_INTENCLR_TXREADY_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_TXREADY_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_TXREADY_Clear (1UL) /*!< Disable */

/* Bit 20 : Write '1' to Disable interrupt for RATEBOOST event */
#define RADIO_INTENCLR_RATEBOOST_Pos (20UL) /*!< Position of RATEBOOST field. */
#define RADIO_INTENCLR_RATEBOOST_Msk (0x1UL << RADIO_INTENCLR_RATEBOOST_Pos) /*!< Bit mask of RATEBOOST field. */
#define RADIO_INTENCLR_RATEBOOST_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_RATEBOOST_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_RATEBOOST_Clear (1UL) /*!< Disable */

/* Bit 19 : Write '1' to Disable interrupt for CCASTOPPED event */
#define RADIO_INTENCLR_CCASTOPPED_Pos (19UL) /*!< Position of CCASTOPPED field. */
#define RADIO_INTENCLR_CCASTOPPED_Msk (0x1UL << RADIO_INTENCLR_CCASTOPPED_Pos) /*!< Bit mask of CCASTOPPED field. */
#define RADIO_INTENCLR_CCASTOPPED_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_CCASTOPPED_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_CCASTOPPED_Clear (1UL) /*!< Disable */

/* Bit 18 : Write '1' to Disable interrupt for CCABUSY event */
#define RADIO_INTENCLR_CCABUSY_Pos (18UL) /*!< Position of CCABUSY field. */
#define RADIO_INTENCLR_CCABUSY_Msk (0x1UL << RADIO_INTENCLR_CCABUSY_Pos) /*!< Bit mask of CCABUSY field. */
#define RADIO_INTENCLR_CCABUSY_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_CCABUSY_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_CCABUSY_Clear (1UL) /*!< Disable */

/* Bit 17 : Write '1' to Disable interrupt for CCAIDLE event */
#define RADIO_INTENCLR_CCAIDLE_Pos (17UL) /*!< Position of CCAIDLE field. */
#define RADIO_INTENCLR_CCAIDLE_Msk (0x1UL << RADIO_INTENCLR_CCAIDLE_Pos) /*!< Bit mask of CCAIDLE field. */
#define RADIO_INTENCLR_CCAIDLE_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_CCAIDLE_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_CCAIDLE_Clear (1UL) /*!< Disable */

/* Bit 16 : Write '1' to Disable interrupt for EDSTOPPED event */
#define RADIO_INTENCLR_EDSTOPPED_Pos (16UL) /*!< Position of EDSTOPPED field. */
#define RADIO_INTENCLR_EDSTOPPED_Msk (0x1UL << RADIO_INTENCLR_EDSTOPPED_Pos) /*!< Bit mask of EDSTOPPED field. */
#define RADIO_INTENCLR_EDSTOPPED_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_EDSTOPPED_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_EDSTOPPED_Clear (1UL) /*!< Disable */

/* Bit 15 : Write '1' to Disable interrupt for EDEND event */
#define RADIO_INTENCLR_EDEND_Pos (15UL) /*!< Position of EDEND field. */
#define RADIO_INTENCLR_EDEND_Msk (0x1UL << RADIO_INTENCLR_EDEND_Pos) /*!< Bit mask of EDEND field. */
#define RADIO_INTENCLR_EDEND_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_EDEND_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_EDEND_Clear (1UL) /*!< Disable */

/* Bit 14 : Write '1' to Disable interrupt for FRAMESTART event */
#define RADIO_INTENCLR_FRAMESTART_Pos (14UL) /*!< Position of FRAMESTART field. */
#define RADIO_INTENCLR_FRAMESTART_Msk (0x1UL << RADIO_INTENCLR_FRAMESTART_Pos) /*!< Bit mask of FRAMESTART field. */
#define RADIO_INTENCLR_FRAMESTART_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_FRAMESTART_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_FRAMESTART_Clear (1UL) /*!< Disable */

/* Bit 13 : Write '1' to Disable interrupt for CRCERROR event */
#define RADIO_INTENCLR_CRCERROR_Pos (13UL) /*!< Position of CRCERROR field. */
#define RADIO_INTENCLR_CRCERROR_Msk (0x1UL << RADIO_INTENCLR_CRCERROR_Pos) /*!< Bit mask of CRCERROR field. */
#define RADIO_INTENCLR_CRCERROR_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_CRCERROR_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_CRCERROR_Clear (1UL) /*!< Disable */

/* Bit 12 : Write '1' to Disable interrupt for CRCOK event */
#define RADIO_INTENCLR_CRCOK_Pos (12UL) /*!< Position of CRCOK field. */
#define RADIO_INTENCLR_CRCOK_Msk (0x1UL << RADIO_INTENCLR_CRCOK_Pos) /*!< Bit mask of CRCOK field. */
#define RADIO_INTENCLR_CRCOK_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_CRCOK_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_CRCOK_Clear (1UL) /*!< Disable */

/* Bit 10 : Write '1' to Disable interrupt for BCMATCH event */
#define RADIO_INTENCLR_BCMATCH_Pos (10UL) /*!< Position of BCMATCH field. */
#define RADIO_INTENCLR_BCMATCH_Msk (0x1UL << RADIO_INTENCLR_BCMATCH_Pos) /*!< Bit mask of BCMATCH field. */
#define RADIO_INTENCLR_BCMATCH_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_BCMATCH_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_BCMATCH_Clear (1UL) /*!< Disable */

/* Bit 7 : Write '1' to Disable interrupt for RSSIEND event */
#define RADIO_INTENCLR_RSSIEND_Pos (7UL) /*!< Position of RSSIEND field. */
#define RADIO_INTENCLR_RSSIEND_Msk (0x1UL << RADIO_INTENCLR_RSSIEND_Pos) /*!< Bit mask of RSSIEND field. */
#define RADIO_INTENCLR_RSSIEND_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_RSSIEND_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_RSSIEND_Clear (1UL) /*!< Disable */

/* Bit 6 : Write '1' to Disable interrupt for DEVMISS event */
#define RADIO_INTENCLR_DEVMISS_Pos (6UL) /*!< Position of DEVMISS field. */
#define RADIO_INTENCLR_DEVMISS_Msk (0x1UL << RADIO_INTENCLR_DEVMISS_Pos) /*!< Bit mask of DEVMISS field. */
#define RADIO_INTENCLR_DEVMISS_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_DEVMISS_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_DEVMISS_Clear (1UL) /*!< Disable */

/* Bit 5 : Write '1' to Disable interrupt for DEVMATCH event */
#define RADIO_INTENCLR_DEVMATCH_Pos (5UL) /*!< Position of DEVMATCH field. */
#define RADIO_INTENCLR_DEVMATCH_Msk (0x1UL << RADIO_INTENCLR_DEVMATCH_Pos) /*!< Bit mask of DEVMATCH field. */
#define RADIO_INTENCLR_DEVMATCH_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_DEVMATCH_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_DEVMATCH_Clear (1UL) /*!< Disable */

/* Bit 4 : Write '1' to Disable interrupt for DISABLED event */
#define RADIO_INTENCLR_DISABLED_Pos (4UL) /*!< Position of DISABLED field. */
#define RADIO_INTENCLR_DISABLED_Msk (0x1UL << RADIO_INTENCLR_DISABLED_Pos) /*!< Bit mask of DISABLED field. */
#define RADIO_INTENCLR_DISABLED_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_DISABLED_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_DISABLED_Clear (1UL) /*!< Disable */

/* Bit 3 : Write '1' to Disable interrupt for END event */
#define RADIO_INTENCLR_END_Pos (3UL) /*!< Position of END field. */
#define RADIO_INTENCLR_END_Msk (0x1UL << RADIO_INTENCLR_END_Pos) /*!< Bit mask of END field. */
#define RADIO_INTENCLR_END_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_END_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_END_Clear (1UL) /*!< Disable */

/* Bit 2 : Write '1' to Disable interrupt for PAYLOAD event */
#define RADIO_INTENCLR_PAYLOAD_Pos (2UL) /*!< Position of PAYLOAD field. */
#define RADIO_INTENCLR_PAYLOAD_Msk (0x1UL << RADIO_INTENCLR_PAYLOAD_Pos) /*!< Bit mask of PAYLOAD field. */
#define RADIO_INTENCLR_PAYLOAD_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_PAYLOAD_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_PAYLOAD_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable interrupt for ADDRESS event */
#define RADIO_INTENCLR_ADDRESS_Pos (1UL) /*!< Position of ADDRESS field. */
#define RADIO_INTENCLR_ADDRESS_Msk (0x1UL << RADIO_INTENCLR_ADDRESS_Pos) /*!< Bit mask of ADDRESS field. */
#define RADIO_INTENCLR_ADDRESS_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_ADDRESS_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_ADDRESS_Clear (1UL) /*!< Disable */

/* Bit 0 : Write '1' to Disable interrupt for READY event */
#define RADIO_INTENCLR_READY_Pos (0UL) /*!< Position of READY field. */
#define RADIO_INTENCLR_READY_Msk (0x1UL << RADIO_INTENCLR_READY_Pos) /*!< Bit mask of READY field. */
#define RADIO_INTENCLR_READY_Disabled (0UL) /*!< Read: Disabled */
#define RADIO_INTENCLR_READY_Enabled (1UL) /*!< Read: Enabled */
#define RADIO_INTENCLR_READY_Clear (1UL) /*!< Disable */

/* Register: RADIO_CRCSTATUS */
/* Description: CRC status */

/* Bit 0 : CRC status of packet received */
#define RADIO_CRCSTATUS_CRCSTATUS_Pos (0UL) /*!< Position of CRCSTATUS field. */
#define RADIO_CRCSTATUS_CRCSTATUS_Msk (0x1UL << RADIO_CRCSTATUS_CRCSTATUS_Pos) /*!< Bit mask of CRCSTATUS field. */
#define RADIO_CRCSTATUS_CRCSTATUS_CRCError (0UL) /*!< Packet received with CRC error */
#define RADIO_CRCSTATUS_CRCSTATUS_CRCOk (1UL) /*!< Packet received with CRC ok */

/* Register: RADIO_RXMATCH */
/* Description: Received address */

/* Bits 2..0 : Received address */
#define RADIO_RXMATCH_RXMATCH_Pos (0UL) /*!< Position of RXMATCH field. */
#define RADIO_RXMATCH_RXMATCH_Msk (0x7UL << RADIO_RXMATCH_RXMATCH_Pos) /*!< Bit mask of RXMATCH field. */

/* Register: RADIO_RXCRC */
/* Description: CRC field of previously received packet */

/* Bits 23..0 : CRC field of previously received packet */
#define RADIO_RXCRC_RXCRC_Pos (0UL) /*!< Position of RXCRC field. */
#define RADIO_RXCRC_RXCRC_Msk (0xFFFFFFUL << RADIO_RXCRC_RXCRC_Pos) /*!< Bit mask of RXCRC field. */

/* Register: RADIO_DAI */
/* Description: Device address match index */

/* Bits 2..0 : Device address match index */
#define RADIO_DAI_DAI_Pos (0UL) /*!< Position of DAI field. */
#define RADIO_DAI_DAI_Msk (0x7UL << RADIO_DAI_DAI_Pos) /*!< Bit mask of DAI field. */

/* Register: RADIO_PACKETPTR */
/* Description: Packet pointer */

/* Bits 31..0 : Packet pointer */
#define RADIO_PACKETPTR_PACKETPTR_Pos (0UL) /*!< Position of PACKETPTR field. */
#define RADIO_PACKETPTR_PACKETPTR_Msk (0xFFFFFFFFUL << RADIO_PACKETPTR_PACKETPTR_Pos) /*!< Bit mask of PACKETPTR field. */

/* Register: RADIO_FREQUENCY */
/* Description: Frequency */

/* Bit 8 : Channel map selection. */
#define RADIO_FREQUENCY_MAP_Pos (8UL) /*!< Position of MAP field. */
#define RADIO_FREQUENCY_MAP_Msk (0x1UL << RADIO_FREQUENCY_MAP_Pos) /*!< Bit mask of MAP field. */
#define RADIO_FREQUENCY_MAP_Default (0UL) /*!< Channel map between 2400 MHZ .. 2500 MHz */
#define RADIO_FREQUENCY_MAP_Low (1UL) /*!< Channel map between 2360 MHZ .. 2460 MHz */

/* Bits 6..0 : Radio channel frequency */
#define RADIO_FREQUENCY_FREQUENCY_Pos (0UL) /*!< Position of FREQUENCY field. */
#define RADIO_FREQUENCY_FREQUENCY_Msk (0x7FUL << RADIO_FREQUENCY_FREQUENCY_Pos) /*!< Bit mask of FREQUENCY field. */

/* Register: RADIO_TXPOWER */
/* Description: Output power */

/* Bits 7..0 : RADIO output power. */
#define RADIO_TXPOWER_TXPOWER_Pos (0UL) /*!< Position of TXPOWER field. */
#define RADIO_TXPOWER_TXPOWER_Msk (0xFFUL << RADIO_TXPOWER_TXPOWER_Pos) /*!< Bit mask of TXPOWER field. */
#define RADIO_TXPOWER_TXPOWER_0dBm (0x0UL) /*!< 0 dBm */
#define RADIO_TXPOWER_TXPOWER_Pos2dBm (0x2UL) /*!< +2 dBm */
#define RADIO_TXPOWER_TXPOWER_Pos3dBm (0x3UL) /*!< +3 dBm */
#define RADIO_TXPOWER_TXPOWER_Pos4dBm (0x4UL) /*!< +4 dBm */
#define RADIO_TXPOWER_TXPOWER_Pos5dBm (0x5UL) /*!< +5 dBm */
#define RADIO_TXPOWER_TXPOWER_Pos6dBm (0x6UL) /*!< +6 dBm */
#define RADIO_TXPOWER_TXPOWER_Pos7dBm (0x7UL) /*!< +7 dBm */
#define RADIO_TXPOWER_TXPOWER_Pos8dBm (0x8UL) /*!< +8 dBm */
#define RADIO_TXPOWER_TXPOWER_Pos9dBm (0x9UL) /*!< +9 dBm */
#define RADIO_TXPOWER_TXPOWER_Neg30dBm (0xD8UL) /*!< Deprecated enumerator -  -40 dBm */
#define RADIO_TXPOWER_TXPOWER_Neg40dBm (0xD8UL) /*!< -40 dBm */
#define RADIO_TXPOWER_TXPOWER_Neg20dBm (0xECUL) /*!< -20 dBm */
#define RADIO_TXPOWER_TXPOWER_Neg16dBm (0xF0UL) /*!< -16 dBm */
#define RADIO_TXPOWER_TXPOWER_Neg12dBm (0xF4UL) /*!< -12 dBm */
#define RADIO_TXPOWER_TXPOWER_Neg8dBm (0xF8UL) /*!< -8 dBm */
#define RADIO_TXPOWER_TXPOWER_Neg4dBm (0xFCUL) /*!< -4 dBm */

/* Register: RADIO_MODE */
/* Description: Data rate and modulation */

/* Bits 3..0 : Radio data rate and modulation setting. The radio supports Frequency-shift Keying (FSK) modulation. */
#define RADIO_MODE_MODE_Pos (0UL) /*!< Position of MODE field. */
#define RADIO_MODE_MODE_Msk (0xFUL << RADIO_MODE_MODE_Pos) /*!< Bit mask of MODE field. */
#define RADIO_MODE_MODE_Nrf_1Mbit (0UL) /*!< 1 Mbit/s Nordic proprietary radio mode */
#define RADIO_MODE_MODE_Nrf_2Mbit (1UL) /*!< 2 Mbit/s Nordic proprietary radio mode */
#define RADIO_MODE_MODE_Nrf_250Kbit (2UL) /*!< Deprecated enumerator -  250 kbit/s Nordic proprietary radio mode */
#define RADIO_MODE_MODE_Ble_1Mbit (3UL) /*!< 1 Mbit/s Bluetooth Low Energy */
#define RADIO_MODE_MODE_Ble_2Mbit (4UL) /*!< 2 Mbit/s Bluetooth Low Energy */
#define RADIO_MODE_MODE_Ble_LR125Kbit (5UL) /*!< Long range 125 kbit/s (TX Only - RX supports both) */
#define RADIO_MODE_MODE_Ble_LR500Kbit (6UL) /*!< Long range 500 kbit/s (TX Only - RX supports both) */
#define RADIO_MODE_MODE_Ieee802154_250Kbit (15UL) /*!< IEEE 802.15.4-2006 250 kbit/s */

/* Register: RADIO_PCNF0 */
/* Description: Packet configuration register 0 */

/* Bits 30..29 : Length of TERM field in Long Range operation */
#define RADIO_PCNF0_TERMLEN_Pos (29UL) /*!< Position of TERMLEN field. */
#define RADIO_PCNF0_TERMLEN_Msk (0x3UL << RADIO_PCNF0_TERMLEN_Pos) /*!< Bit mask of TERMLEN field. */

/* Bit 26 : Indicates if LENGTH field contains CRC or not */
#define RADIO_PCNF0_CRCINC_Pos (26UL) /*!< Position of CRCINC field. */
#define RADIO_PCNF0_CRCINC_Msk (0x1UL << RADIO_PCNF0_CRCINC_Pos) /*!< Bit mask of CRCINC field. */
#define RADIO_PCNF0_CRCINC_Exclude (0UL) /*!< LENGTH does not contain CRC */
#define RADIO_PCNF0_CRCINC_Include (1UL) /*!< LENGTH includes CRC */

/* Bits 25..24 : Length of preamble on air. Decision point: TASKS_START task */
#define RADIO_PCNF0_PLEN_Pos (24UL) /*!< Position of PLEN field. */
#define RADIO_PCNF0_PLEN_Msk (0x3UL << RADIO_PCNF0_PLEN_Pos) /*!< Bit mask of PLEN field. */
#define RADIO_PCNF0_PLEN_8bit (0UL) /*!< 8-bit preamble */
#define RADIO_PCNF0_PLEN_16bit (1UL) /*!< 16-bit preamble */
#define RADIO_PCNF0_PLEN_32bitZero (2UL) /*!< 32-bit zero preamble - used for IEEE 802.15.4 */
#define RADIO_PCNF0_PLEN_LongRange (3UL) /*!< Preamble - used for BTLE Long Range */

/* Bits 23..22 : Length of Code Indicator - Long Range */
#define RADIO_PCNF0_CILEN_Pos (22UL) /*!< Position of CILEN field. */
#define RADIO_PCNF0_CILEN_Msk (0x3UL << RADIO_PCNF0_CILEN_Pos) /*!< Bit mask of CILEN field. */

/* Bit 20 : Include or exclude S1 field in RAM */
#define RADIO_PCNF0_S1INCL_Pos (20UL) /*!< Position of S1INCL field. */
#define RADIO_PCNF0_S1INCL_Msk (0x1UL << RADIO_PCNF0_S1INCL_Pos) /*!< Bit mask of S1INCL field. */
#define RADIO_PCNF0_S1INCL_Automatic (0UL) /*!< Include S1 field in RAM only if S1LEN &gt; 0 */
#define RADIO_PCNF0_S1INCL_Include (1UL) /*!< Always include S1 field in RAM independent of S1LEN */

/* Bits 19..16 : Length on air of S1 field in number of bits. */
#define RADIO_PCNF0_S1LEN_Pos (16UL) /*!< Position of S1LEN field. */
#define RADIO_PCNF0_S1LEN_Msk (0xFUL << RADIO_PCNF0_S1LEN_Pos) /*!< Bit mask of S1LEN field. */

/* Bit 8 : Length on air of S0 field in number of bytes. */
#define RADIO_PCNF0_S0LEN_Pos (8UL) /*!< Position of S0LEN field. */
#define RADIO_PCNF0_S0LEN_Msk (0x1UL << RADIO_PCNF0_S0LEN_Pos) /*!< Bit mask of S0LEN field. */

/* Bits 3..0 : Length on air of LENGTH field in number of bits. */
#define RADIO_PCNF0_LFLEN_Pos (0UL) /*!< Position of LFLEN field. */
#define RADIO_PCNF0_LFLEN_Msk (0xFUL << RADIO_PCNF0_LFLEN_Pos) /*!< Bit mask of LFLEN field. */

/* Register: RADIO_PCNF1 */
/* Description: Packet configuration register 1 */

/* Bit 25 : Enable or disable packet whitening */
#define RADIO_PCNF1_WHITEEN_Pos (25UL) /*!< Position of WHITEEN field. */
#define RADIO_PCNF1_WHITEEN_Msk (0x1UL << RADIO_PCNF1_WHITEEN_Pos) /*!< Bit mask of WHITEEN field. */
#define RADIO_PCNF1_WHITEEN_Disabled (0UL) /*!< Disable */
#define RADIO_PCNF1_WHITEEN_Enabled (1UL) /*!< Enable */

/* Bit 24 : On air endianness of packet, this applies to the S0, LENGTH, S1 and the PAYLOAD fields. */
#define RADIO_PCNF1_ENDIAN_Pos (24UL) /*!< Position of ENDIAN field. */
#define RADIO_PCNF1_ENDIAN_Msk (0x1UL << RADIO_PCNF1_ENDIAN_Pos) /*!< Bit mask of ENDIAN field. */
#define RADIO_PCNF1_ENDIAN_Little (0UL) /*!< Least Significant bit on air first */
#define RADIO_PCNF1_ENDIAN_Big (1UL) /*!< Most significant bit on air first */

/* Bits 18..16 : Base address length in number of bytes */
#define RADIO_PCNF1_BALEN_Pos (16UL) /*!< Position of BALEN field. */
#define RADIO_PCNF1_BALEN_Msk (0x7UL << RADIO_PCNF1_BALEN_Pos) /*!< Bit mask of BALEN field. */

/* Bits 15..8 : Static length in number of bytes */
#define RADIO_PCNF1_STATLEN_Pos (8UL) /*!< Position of STATLEN field. */
#define RADIO_PCNF1_STATLEN_Msk (0xFFUL << RADIO_PCNF1_STATLEN_Pos) /*!< Bit mask of STATLEN field. */

/* Bits 7..0 : Maximum length of packet payload. If the packet payload is larger than MAXLEN, the radio will truncate the payload to MAXLEN. */
#define RADIO_PCNF1_MAXLEN_Pos (0UL) /*!< Position of MAXLEN field. */
#define RADIO_PCNF1_MAXLEN_Msk (0xFFUL << RADIO_PCNF1_MAXLEN_Pos) /*!< Bit mask of MAXLEN field. */

/* Register: RADIO_BASE0 */
/* Description: Base address 0 */

/* Bits 31..0 : Base address 0 */
#define RADIO_BASE0_BASE0_Pos (0UL) /*!< Position of BASE0 field. */
#define RADIO_BASE0_BASE0_Msk (0xFFFFFFFFUL << RADIO_BASE0_BASE0_Pos) /*!< Bit mask of BASE0 field. */

/* Register: RADIO_BASE1 */
/* Description: Base address 1 */

/* Bits 31..0 : Base address 1 */
#define RADIO_BASE1_BASE1_Pos (0UL) /*!< Position of BASE1 field. */
#define RADIO_BASE1_BASE1_Msk (0xFFFFFFFFUL << RADIO_BASE1_BASE1_Pos) /*!< Bit mask of BASE1 field. */

/* Register: RADIO_PREFIX0 */
/* Description: Prefixes bytes for logical addresses 0-3 */

/* Bits 31..24 : Address prefix 3. */
#define RADIO_PREFIX0_AP3_Pos (24UL) /*!< Position of AP3 field. */
#define RADIO_PREFIX0_AP3_Msk (0xFFUL << RADIO_PREFIX0_AP3_Pos) /*!< Bit mask of AP3 field. */

/* Bits 23..16 : Address prefix 2. */
#define RADIO_PREFIX0_AP2_Pos (16UL) /*!< Position of AP2 field. */
#define RADIO_PREFIX0_AP2_Msk (0xFFUL << RADIO_PREFIX0_AP2_Pos) /*!< Bit mask of AP2 field. */

/* Bits 15..8 : Address prefix 1. */
#define RADIO_PREFIX0_AP1_Pos (8UL) /*!< Position of AP1 field. */
#define RADIO_PREFIX0_AP1_Msk (0xFFUL << RADIO_PREFIX0_AP1_Pos) /*!< Bit mask of AP1 field. */

/* Bits 7..0 : Address prefix 0. */
#define RADIO_PREFIX0_AP0_Pos (0UL) /*!< Position of AP0 field. */
#define RADIO_PREFIX0_AP0_Msk (0xFFUL << RADIO_PREFIX0_AP0_Pos) /*!< Bit mask of AP0 field. */

/* Register: RADIO_PREFIX1 */
/* Description: Prefixes bytes for logical addresses 4-7 */

/* Bits 31..24 : Address prefix 7. */
#define RADIO_PREFIX1_AP7_Pos (24UL) /*!< Position of AP7 field. */
#define RADIO_PREFIX1_AP7_Msk (0xFFUL << RADIO_PREFIX1_AP7_Pos) /*!< Bit mask of AP7 field. */

/* Bits 23..16 : Address prefix 6. */
#define RADIO_PREFIX1_AP6_Pos (16UL) /*!< Position of AP6 field. */
#define RADIO_PREFIX1_AP6_Msk (0xFFUL << RADIO_PREFIX1_AP6_Pos) /*!< Bit mask of AP6 field. */

/* Bits 15..8 : Address prefix 5. */
#define RADIO_PREFIX1_AP5_Pos (8UL) /*!< Position of AP5 field. */
#define RADIO_PREFIX1_AP5_Msk (0xFFUL << RADIO_PREFIX1_AP5_Pos) /*!< Bit mask of AP5 field. */

/* Bits 7..0 : Address prefix 4. */
#define RADIO_PREFIX1_AP4_Pos (0UL) /*!< Position of AP4 field. */
#define RADIO_PREFIX1_AP4_Msk (0xFFUL << RADIO_PREFIX1_AP4_Pos) /*!< Bit mask of AP4 field. */

/* Register: RADIO_TXADDRESS */
/* Description: Transmit address select */

/* Bits 2..0 : Transmit address select */
#define RADIO_TXADDRESS_TXADDRESS_Pos (0UL) /*!< Position of TXADDRESS field. */
#define RADIO_TXADDRESS_TXADDRESS_Msk (0x7UL << RADIO_TXADDRESS_TXADDRESS_Pos) /*!< Bit mask of TXADDRESS field. */

/* Register: RADIO_RXADDRESSES */
/* Description: Receive address select */

/* Bit 7 : Enable or disable reception on logical address 7. */
#define RADIO_RXADDRESSES_ADDR7_Pos (7UL) /*!< Position of ADDR7 field. */
#define RADIO_RXADDRESSES_ADDR7_Msk (0x1UL << RADIO_RXADDRESSES_ADDR7_Pos) /*!< Bit mask of ADDR7 field. */
#define RADIO_RXADDRESSES_ADDR7_Disabled (0UL) /*!< Disable */
#define RADIO_RXADDRESSES_ADDR7_Enabled (1UL) /*!< Enable */

/* Bit 6 : Enable or disable reception on logical address 6. */
#define RADIO_RXADDRESSES_ADDR6_Pos (6UL) /*!< Position of ADDR6 field. */
#define RADIO_RXADDRESSES_ADDR6_Msk (0x1UL << RADIO_RXADDRESSES_ADDR6_Pos) /*!< Bit mask of ADDR6 field. */
#define RADIO_RXADDRESSES_ADDR6_Disabled (0UL) /*!< Disable */
#define RADIO_RXADDRESSES_ADDR6_Enabled (1UL) /*!< Enable */

/* Bit 5 : Enable or disable reception on logical address 5. */
#define RADIO_RXADDRESSES_ADDR5_Pos (5UL) /*!< Position of ADDR5 field. */
#define RADIO_RXADDRESSES_ADDR5_Msk (0x1UL << RADIO_RXADDRESSES_ADDR5_Pos) /*!< Bit mask of ADDR5 field. */
#define RADIO_RXADDRESSES_ADDR5_Disabled (0UL) /*!< Disable */
#define RADIO_RXADDRESSES_ADDR5_Enabled (1UL) /*!< Enable */

/* Bit 4 : Enable or disable reception on logical address 4. */
#define RADIO_RXADDRESSES_ADDR4_Pos (4UL) /*!< Position of ADDR4 field. */
#define RADIO_RXADDRESSES_ADDR4_Msk (0x1UL << RADIO_RXADDRESSES_ADDR4_Pos) /*!< Bit mask of ADDR4 field. */
#define RADIO_RXADDRESSES_ADDR4_Disabled (0UL) /*!< Disable */
#define RADIO_RXADDRESSES_ADDR4_Enabled (1UL) /*!< Enable */

/* Bit 3 : Enable or disable reception on logical address 3. */
#define RADIO_RXADDRESSES_ADDR3_Pos (3UL) /*!< Position of ADDR3 field. */
#define RADIO_RXADDRESSES_ADDR3_Msk (0x1UL << RADIO_RXADDRESSES_ADDR3_Pos) /*!< Bit mask of ADDR3 field. */
#define RADIO_RXADDRESSES_ADDR3_Disabled (0UL) /*!< Disable */
#define RADIO_RXADDRESSES_ADDR3_Enabled (1UL) /*!< Enable */

/* Bit 2 : Enable or disable reception on logical address 2. */
#define RADIO_RXADDRESSES_ADDR2_Pos (2UL) /*!< Position of ADDR2 field. */
#define RADIO_RXADDRESSES_ADDR2_Msk (0x1UL << RADIO_RXADDRESSES_ADDR2_Pos) /*!< Bit mask of ADDR2 field. */
#define RADIO_RXADDRESSES_ADDR2_Disabled (0UL) /*!< Disable */
#define RADIO_RXADDRESSES_ADDR2_Enabled (1UL) /*!< Enable */

/* Bit 1 : Enable or disable reception on logical address 1. */
#define RADIO_RXADDRESSES_ADDR1_Pos (1UL) /*!< Position of ADDR1 field. */
#define RADIO_RXADDRESSES_ADDR1_Msk (0x1UL << RADIO_RXADDRESSES_ADDR1_Pos) /*!< Bit mask of ADDR1 field. */
#define RADIO_RXADDRESSES_ADDR1_Disabled (0UL) /*!< Disable */
#define RADIO_RXADDRESSES_ADDR1_Enabled (1UL) /*!< Enable */

/* Bit 0 : Enable or disable reception on logical address 0. */
#define RADIO_RXADDRESSES_ADDR0_Pos (0UL) /*!< Position of ADDR0 field. */
#define RADIO_RXADDRESSES_ADDR0_Msk (0x1UL << RADIO_RXADDRESSES_ADDR0_Pos) /*!< Bit mask of ADDR0 field. */
#define RADIO_RXADDRESSES_ADDR0_Disabled (0UL) /*!< Disable */
#define RADIO_RXADDRESSES_ADDR0_Enabled (1UL) /*!< Enable */

/* Register: RADIO_CRCCNF */
/* Description: CRC configuration */

/* Bits 9..8 : Include or exclude packet address field out of CRC calculation. */
#define RADIO_CRCCNF_SKIPADDR_Pos (8UL) /*!< Position of SKIPADDR field. */
#define RADIO_CRCCNF_SKIPADDR_Msk (0x3UL << RADIO_CRCCNF_SKIPADDR_Pos) /*!< Bit mask of SKIPADDR field. */
#define RADIO_CRCCNF_SKIPADDR_Include (0UL) /*!< CRC calculation includes address field */
#define RADIO_CRCCNF_SKIPADDR_Skip (1UL) /*!< CRC calculation does not include address field. The CRC calculation will start at the first byte after the address. */
#define RADIO_CRCCNF_SKIPADDR_Ieee802154 (2UL) /*!< CRC calculation as per 802.15.4 standard. Starting at first byte after length field. */

/* Bits 1..0 : CRC length in number of bytes. */
#define RADIO_CRCCNF_LEN_Pos (0UL) /*!< Position of LEN field. */
#define RADIO_CRCCNF_LEN_Msk (0x3UL << RADIO_CRCCNF_LEN_Pos) /*!< Bit mask of LEN field. */
#define RADIO_CRCCNF_LEN_Disabled (0UL) /*!< CRC length is zero and CRC calculation is disabled */
#define RADIO_CRCCNF_LEN_One (1UL) /*!< CRC length is one byte and CRC calculation is enabled */
#define RADIO_CRCCNF_LEN_Two (2UL) /*!< CRC length is two bytes and CRC calculation is enabled */
#define RADIO_CRCCNF_LEN_Three (3UL) /*!< CRC length is three bytes and CRC calculation is enabled */

/* Register: RADIO_CRCPOLY */
/* Description: CRC polynomial */

/* Bits 23..0 : CRC polynomial */
#define RADIO_CRCPOLY_CRCPOLY_Pos (0UL) /*!< Position of CRCPOLY field. */
#define RADIO_CRCPOLY_CRCPOLY_Msk (0xFFFFFFUL << RADIO_CRCPOLY_CRCPOLY_Pos) /*!< Bit mask of CRCPOLY field. */

/* Register: RADIO_CRCINIT */
/* Description: CRC initial value */

/* Bits 23..0 : CRC initial value */
#define RADIO_CRCINIT_CRCINIT_Pos (0UL) /*!< Position of CRCINIT field. */
#define RADIO_CRCINIT_CRCINIT_Msk (0xFFFFFFUL << RADIO_CRCINIT_CRCINIT_Pos) /*!< Bit mask of CRCINIT field. */

/* Register: RADIO_TIFS */
/* Description: Inter Frame Spacing in us */

/* Bits 9..0 : Inter Frame Spacing in us */
#define RADIO_TIFS_TIFS_Pos (0UL) /*!< Position of TIFS field. */
#define RADIO_TIFS_TIFS_Msk (0x3FFUL << RADIO_TIFS_TIFS_Pos) /*!< Bit mask of TIFS field. */

/* Register: RADIO_RSSISAMPLE */
/* Description: RSSI sample */

/* Bits 6..0 : RSSI sample */
#define RADIO_RSSISAMPLE_RSSISAMPLE_Pos (0UL) /*!< Position of RSSISAMPLE field. */
#define RADIO_RSSISAMPLE_RSSISAMPLE_Msk (0x7FUL << RADIO_RSSISAMPLE_RSSISAMPLE_Pos) /*!< Bit mask of RSSISAMPLE field. */

/* Register: RADIO_STATE */
/* Description: Current radio state */

/* Bits 3..0 : Current radio state */
#define RADIO_STATE_STATE_Pos (0UL) /*!< Position of STATE field. */
#define RADIO_STATE_STATE_Msk (0xFUL << RADIO_STATE_STATE_Pos) /*!< Bit mask of STATE field. */
#define RADIO_STATE_STATE_Disabled (0UL) /*!< RADIO is in the Disabled state */
#define RADIO_STATE_STATE_RxRu (1UL) /*!< RADIO is in the RXRU state */
#define RADIO_STATE_STATE_RxIdle (2UL) /*!< RADIO is in the RXIDLE state */
#define RADIO_STATE_STATE_Rx (3UL) /*!< RADIO is in the RX state */
#define RADIO_STATE_STATE_RxDisable (4UL) /*!< RADIO is in the RXDISABLED state */
#define RADIO_STATE_STATE_TxRu (9UL) /*!< RADIO is in the TXRU state */
#define RADIO_STATE_STATE_TxIdle (10UL) /*!< RADIO is in the TXIDLE state */
#define RADIO_STATE_STATE_Tx (11UL) /*!< RADIO is in the TX state */
#define RADIO_STATE_STATE_TxDisable (12UL) /*!< RADIO is in the TXDISABLED state */

/* Register: RADIO_DATAWHITEIV */
/* Description: Data whitening initial value */

/* Bits 6..0 : Data whitening initial value. Bit 6 is hard-wired to '1', writing '0' to it has no effect, and it will always be read back and used by the device as '1'. */
#define RADIO_DATAWHITEIV_DATAWHITEIV_Pos (0UL) /*!< Position of DATAWHITEIV field. */
#define RADIO_DATAWHITEIV_DATAWHITEIV_Msk (0x7FUL << RADIO_DATAWHITEIV_DATAWHITEIV_Pos) /*!< Bit mask of DATAWHITEIV field. */

/* Register: RADIO_BCC */
/* Description: Bit counter compare */

/* Bits 31..0 : Bit counter compare */
#define RADIO_BCC_BCC_Pos (0UL) /*!< Position of BCC field. */
#define RADIO_BCC_BCC_Msk (0xFFFFFFFFUL << RADIO_BCC_BCC_Pos) /*!< Bit mask of BCC field. */

/* Register: RADIO_DAB */
/* Description: Description collection[0]:  Device address base segment 0 */

/* Bits 31..0 : Device address base segment 0 */
#define RADIO_DAB_DAB_Pos (0UL) /*!< Position of DAB field. */
#define RADIO_DAB_DAB_Msk (0xFFFFFFFFUL << RADIO_DAB_DAB_Pos) /*!< Bit mask of DAB field. */

/* Register: RADIO_DAP */
/* Description: Description collection[0]:  Device address prefix 0 */

/* Bits 15..0 : Device address prefix 0 */
#define RADIO_DAP_DAP_Pos (0UL) /*!< Position of DAP field. */
#define RADIO_DAP_DAP_Msk (0xFFFFUL << RADIO_DAP_DAP_Pos) /*!< Bit mask of DAP field. */

/* Register: RADIO_DACNF */
/* Description: Device address match configuration */

/* Bit 15 : TxAdd for device address 7 */
#define RADIO_DACNF_TXADD7_Pos (15UL) /*!< Position of TXADD7 field. */
#define RADIO_DACNF_TXADD7_Msk (0x1UL << RADIO_DACNF_TXADD7_Pos) /*!< Bit mask of TXADD7 field. */

/* Bit 14 : TxAdd for device address 6 */
#define RADIO_DACNF_TXADD6_Pos (14UL) /*!< Position of TXADD6 field. */
#define RADIO_DACNF_TXADD6_Msk (0x1UL << RADIO_DACNF_TXADD6_Pos) /*!< Bit mask of TXADD6 field. */

/* Bit 13 : TxAdd for device address 5 */
#define RADIO_DACNF_TXADD5_Pos (13UL) /*!< Position of TXADD5 field. */
#define RADIO_DACNF_TXADD5_Msk (0x1UL << RADIO_DACNF_TXADD5_Pos) /*!< Bit mask of TXADD5 field. */

/* Bit 12 : TxAdd for device address 4 */
#define RADIO_DACNF_TXADD4_Pos (12UL) /*!< Position of TXADD4 field. */
#define RADIO_DACNF_TXADD4_Msk (0x1UL << RADIO_DACNF_TXADD4_Pos) /*!< Bit mask of TXADD4 field. */

/* Bit 11 : TxAdd for device address 3 */
#define RADIO_DACNF_TXADD3_Pos (11UL) /*!< Position of TXADD3 field. */
#define RADIO_DACNF_TXADD3_Msk (0x1UL << RADIO_DACNF_TXADD3_Pos) /*!< Bit mask of TXADD3 field. */

/* Bit 10 : TxAdd for device address 2 */
#define RADIO_DACNF_TXADD2_Pos (10UL) /*!< Position of TXADD2 field. */
#define RADIO_DACNF_TXADD2_Msk (0x1UL << RADIO_DACNF_TXADD2_Pos) /*!< Bit mask of TXADD2 field. */

/* Bit 9 : TxAdd for device address 1 */
#define RADIO_DACNF_TXADD1_Pos (9UL) /*!< Position of TXADD1 field. */
#define RADIO_DACNF_TXADD1_Msk (0x1UL << RADIO_DACNF_TXADD1_Pos) /*!< Bit mask of TXADD1 field. */

/* Bit 8 : TxAdd for device address 0 */
#define RADIO_DACNF_TXADD0_Pos (8UL) /*!< Position of TXADD0 field. */
#define RADIO_DACNF_TXADD0_Msk (0x1UL << RADIO_DACNF_TXADD0_Pos) /*!< Bit mask of TXADD0 field. */

/* Bit 7 : Enable or disable device address matching using device address 7 */
#define RADIO_DACNF_ENA7_Pos (7UL) /*!< Position of ENA7 field. */
#define RADIO_DACNF_ENA7_Msk (0x1UL << RADIO_DACNF_ENA7_Pos) /*!< Bit mask of ENA7 field. */
#define RADIO_DACNF_ENA7_Disabled (0UL) /*!< Disabled */
#define RADIO_DACNF_ENA7_Enabled (1UL) /*!< Enabled */

/* Bit 6 : Enable or disable device address matching using device address 6 */
#define RADIO_DACNF_ENA6_Pos (6UL) /*!< Position of ENA6 field. */
#define RADIO_DACNF_ENA6_Msk (0x1UL << RADIO_DACNF_ENA6_Pos) /*!< Bit mask of ENA6 field. */
#define RADIO_DACNF_ENA6_Disabled (0UL) /*!< Disabled */
#define RADIO_DACNF_ENA6_Enabled (1UL) /*!< Enabled */

/* Bit 5 : Enable or disable device address matching using device address 5 */
#define RADIO_DACNF_ENA5_Pos (5UL) /*!< Position of ENA5 field. */
#define RADIO_DACNF_ENA5_Msk (0x1UL << RADIO_DACNF_ENA5_Pos) /*!< Bit mask of ENA5 field. */
#define RADIO_DACNF_ENA5_Disabled (0UL) /*!< Disabled */
#define RADIO_DACNF_ENA5_Enabled (1UL) /*!< Enabled */

/* Bit 4 : Enable or disable device address matching using device address 4 */
#define RADIO_DACNF_ENA4_Pos (4UL) /*!< Position of ENA4 field. */
#define RADIO_DACNF_ENA4_Msk (0x1UL << RADIO_DACNF_ENA4_Pos) /*!< Bit mask of ENA4 field. */
#define RADIO_DACNF_ENA4_Disabled (0UL) /*!< Disabled */
#define RADIO_DACNF_ENA4_Enabled (1UL) /*!< Enabled */

/* Bit 3 : Enable or disable device address matching using device address 3 */
#define RADIO_DACNF_ENA3_Pos (3UL) /*!< Position of ENA3 field. */
#define RADIO_DACNF_ENA3_Msk (0x1UL << RADIO_DACNF_ENA3_Pos) /*!< Bit mask of ENA3 field. */
#define RADIO_DACNF_ENA3_Disabled (0UL) /*!< Disabled */
#define RADIO_DACNF_ENA3_Enabled (1UL) /*!< Enabled */

/* Bit 2 : Enable or disable device address matching using device address 2 */
#define RADIO_DACNF_ENA2_Pos (2UL) /*!< Position of ENA2 field. */
#define RADIO_DACNF_ENA2_Msk (0x1UL << RADIO_DACNF_ENA2_Pos) /*!< Bit mask of ENA2 field. */
#define RADIO_DACNF_ENA2_Disabled (0UL) /*!< Disabled */
#define RADIO_DACNF_ENA2_Enabled (1UL) /*!< Enabled */

/* Bit 1 : Enable or disable device address matching using device address 1 */
#define RADIO_DACNF_ENA1_Pos (1UL) /*!< Position of ENA1 field. */
#define RADIO_DACNF_ENA1_Msk (0x1UL << RADIO_DACNF_ENA1_Pos) /*!< Bit mask of ENA1 field. */
#define RADIO_DACNF_ENA1_Disabled (0UL) /*!< Disabled */
#define RADIO_DACNF_ENA1_Enabled (1UL) /*!< Enabled */

/* Bit 0 : Enable or disable device address matching using device address 0 */
#define RADIO_DACNF_ENA0_Pos (0UL) /*!< Position of ENA0 field. */
#define RADIO_DACNF_ENA0_Msk (0x1UL << RADIO_DACNF_ENA0_Pos) /*!< Bit mask of ENA0 field. */
#define RADIO_DACNF_ENA0_Disabled (0UL) /*!< Disabled */
#define RADIO_DACNF_ENA0_Enabled (1UL) /*!< Enabled */

/* Register: RADIO_MODECNF0 */
/* Description: Radio mode configuration register 0 */

/* Bits 9..8 : Default TX value */
#define RADIO_MODECNF0_DTX_Pos (8UL) /*!< Position of DTX field. */
#define RADIO_MODECNF0_DTX_Msk (0x3UL << RADIO_MODECNF0_DTX_Pos) /*!< Bit mask of DTX field. */
#define RADIO_MODECNF0_DTX_B1 (0UL) /*!< Transmit '1' */
#define RADIO_MODECNF0_DTX_B0 (1UL) /*!< Transmit '0' */
#define RADIO_MODECNF0_DTX_Center (2UL) /*!< Transmit center frequency */

/* Bit 0 : Radio ramp-up time */
#define RADIO_MODECNF0_RU_Pos (0UL) /*!< Position of RU field. */
#define RADIO_MODECNF0_RU_Msk (0x1UL << RADIO_MODECNF0_RU_Pos) /*!< Bit mask of RU field. */
#define RADIO_MODECNF0_RU_Default (0UL) /*!< Default ramp-up time (tRXEN), compatible with firmware written for nRF51 */
#define RADIO_MODECNF0_RU_Fast (1UL) /*!< Fast ramp-up (tRXEN,FAST), see electrical specification for more information */

/* Register: RADIO_SFD */
/* Description: IEEE 802.15.4 Start of Frame Delimiter */

/* Bits 7..0 : IEEE 802.15.4 Start of Frame Delimiter */
#define RADIO_SFD_SFD_Pos (0UL) /*!< Position of SFD field. */
#define RADIO_SFD_SFD_Msk (0xFFUL << RADIO_SFD_SFD_Pos) /*!< Bit mask of SFD field. */

/* Register: RADIO_EDCNT */
/* Description: IEEE 802.15.4 Energy Detect Loop Count */

/* Bits 20..0 : IEEE 802.15.4 Energy Detect Loop Count */
#define RADIO_EDCNT_EDCNT_Pos (0UL) /*!< Position of EDCNT field. */
#define RADIO_EDCNT_EDCNT_Msk (0x1FFFFFUL << RADIO_EDCNT_EDCNT_Pos) /*!< Bit mask of EDCNT field. */

/* Register: RADIO_EDSAMPLE */
/* Description: IEEE 802.15.4 Energy Detect Level */

/* Bits 7..0 : IEEE 802.15.4 Energy Detect Level */
#define RADIO_EDSAMPLE_EDLVL_Pos (0UL) /*!< Position of EDLVL field. */
#define RADIO_EDSAMPLE_EDLVL_Msk (0xFFUL << RADIO_EDSAMPLE_EDLVL_Pos) /*!< Bit mask of EDLVL field. */

/* Register: RADIO_CCACTRL */
/* Description: IEEE 802.15.4 Clear Channel Assessment Control */

/* Bits 31..24 : Limit for occurances above CCACORRTHRES. When not equal to zero the corrolator based signal detect is enabled. */
#define RADIO_CCACTRL_CCACORRCNT_Pos (24UL) /*!< Position of CCACORRCNT field. */
#define RADIO_CCACTRL_CCACORRCNT_Msk (0xFFUL << RADIO_CCACTRL_CCACORRCNT_Pos) /*!< Bit mask of CCACORRCNT field. */

/* Bits 23..16 : CCA Correlator Busy Threshold. Only relevant to CarrierMode, CarrierAndEdMode and CarrierOrEdMode. */
#define RADIO_CCACTRL_CCACORRTHRES_Pos (16UL) /*!< Position of CCACORRTHRES field. */
#define RADIO_CCACTRL_CCACORRTHRES_Msk (0xFFUL << RADIO_CCACTRL_CCACORRTHRES_Pos) /*!< Bit mask of CCACORRTHRES field. */

/* Bits 15..8 : CCA Energy Busy Threshold. Used in all the CCA modes except CarrierMode. */
#define RADIO_CCACTRL_CCAEDTHRES_Pos (8UL) /*!< Position of CCAEDTHRES field. */
#define RADIO_CCACTRL_CCAEDTHRES_Msk (0xFFUL << RADIO_CCACTRL_CCAEDTHRES_Pos) /*!< Bit mask of CCAEDTHRES field. */

/* Bits 2..0 : CCA Mode Of Operation */
#define RADIO_CCACTRL_CCAMODE_Pos (0UL) /*!< Position of CCAMODE field. */
#define RADIO_CCACTRL_CCAMODE_Msk (0x7UL << RADIO_CCACTRL_CCAMODE_Pos) /*!< Bit mask of CCAMODE field. */
#define RADIO_CCACTRL_CCAMODE_EdMode (0UL) /*!< Energy Above Threshold */
#define RADIO_CCACTRL_CCAMODE_CarrierMode (1UL) /*!< Carrier Seen */
#define RADIO_CCACTRL_CCAMODE_CarrierAndEdMode (2UL) /*!< Energy Above Threshold AND Carrier Seen */
#define RADIO_CCACTRL_CCAMODE_CarrierOrEdMode (3UL) /*!< Energy Above Threshold OR Carrier Seen */
#define RADIO_CCACTRL_CCAMODE_EdModeTest1 (4UL) /*!< Energy Above Threshold test mode that will abort when first ED measurement over threshold is seen. No averaging. */

/* Register: RADIO_POWER */
/* Description: Peripheral power control */

/* Bit 0 : Peripheral power control. The peripheral and its registers will be reset to its initial state by switching the peripheral off and then back on again. */
#define RADIO_POWER_POWER_Pos (0UL) /*!< Position of POWER field. */
#define RADIO_POWER_POWER_Msk (0x1UL << RADIO_POWER_POWER_Pos) /*!< Bit mask of POWER field. */
#define RADIO_POWER_POWER_Disabled (0UL) /*!< Peripheral is powered off */
#define RADIO_POWER_POWER_Enabled (1UL) /*!< Peripheral is powered on */


/* Peripheral: RNG */
/* Description: Random Number Generator */

/* Register: RNG_SHORTS */
/* Description: Shortcut register */

/* Bit 0 : Shortcut between VALRDY event and STOP task */
#define RNG_SHORTS_VALRDY_STOP_Pos (0UL) /*!< Position of VALRDY_STOP field. */
#define RNG_SHORTS_VALRDY_STOP_Msk (0x1UL << RNG_SHORTS_VALRDY_STOP_Pos) /*!< Bit mask of VALRDY_STOP field. */
#define RNG_SHORTS_VALRDY_STOP_Disabled (0UL) /*!< Disable shortcut */
#define RNG_SHORTS_VALRDY_STOP_Enabled (1UL) /*!< Enable shortcut */

/* Register: RNG_INTENSET */
/* Description: Enable interrupt */

/* Bit 0 : Write '1' to Enable interrupt for VALRDY event */
#define RNG_INTENSET_VALRDY_Pos (0UL) /*!< Position of VALRDY field. */
#define RNG_INTENSET_VALRDY_Msk (0x1UL << RNG_INTENSET_VALRDY_Pos) /*!< Bit mask of VALRDY field. */
#define RNG_INTENSET_VALRDY_Disabled (0UL) /*!< Read: Disabled */
#define RNG_INTENSET_VALRDY_Enabled (1UL) /*!< Read: Enabled */
#define RNG_INTENSET_VALRDY_Set (1UL) /*!< Enable */

/* Register: RNG_INTENCLR */
/* Description: Disable interrupt */

/* Bit 0 : Write '1' to Disable interrupt for VALRDY event */
#define RNG_INTENCLR_VALRDY_Pos (0UL) /*!< Position of VALRDY field. */
#define RNG_INTENCLR_VALRDY_Msk (0x1UL << RNG_INTENCLR_VALRDY_Pos) /*!< Bit mask of VALRDY field. */
#define RNG_INTENCLR_VALRDY_Disabled (0UL) /*!< Read: Disabled */
#define RNG_INTENCLR_VALRDY_Enabled (1UL) /*!< Read: Enabled */
#define RNG_INTENCLR_VALRDY_Clear (1UL) /*!< Disable */

/* Register: RNG_CONFIG */
/* Description: Configuration register */

/* Bit 0 : Bias correction */
#define RNG_CONFIG_DERCEN_Pos (0UL) /*!< Position of DERCEN field. */
#define RNG_CONFIG_DERCEN_Msk (0x1UL << RNG_CONFIG_DERCEN_Pos) /*!< Bit mask of DERCEN field. */
#define RNG_CONFIG_DERCEN_Disabled (0UL) /*!< Disabled */
#define RNG_CONFIG_DERCEN_Enabled (1UL) /*!< Enabled */

/* Register: RNG_VALUE */
/* Description: Output random number */

/* Bits 7..0 : Generated random number */
#define RNG_VALUE_VALUE_Pos (0UL) /*!< Position of VALUE field. */
#define RNG_VALUE_VALUE_Msk (0xFFUL << RNG_VALUE_VALUE_Pos) /*!< Bit mask of VALUE field. */


/* Peripheral: RTC */
/* Description: Real time counter 0 */

/* Register: RTC_INTENSET */
/* Description: Enable interrupt */

/* Bit 19 : Write '1' to Enable interrupt for COMPARE[3] event */
#define RTC_INTENSET_COMPARE3_Pos (19UL) /*!< Position of COMPARE3 field. */
#define RTC_INTENSET_COMPARE3_Msk (0x1UL << RTC_INTENSET_COMPARE3_Pos) /*!< Bit mask of COMPARE3 field. */
#define RTC_INTENSET_COMPARE3_Disabled (0UL) /*!< Read: Disabled */
#define RTC_INTENSET_COMPARE3_Enabled (1UL) /*!< Read: Enabled */
#define RTC_INTENSET_COMPARE3_Set (1UL) /*!< Enable */

/* Bit 18 : Write '1' to Enable interrupt for COMPARE[2] event */
#define RTC_INTENSET_COMPARE2_Pos (18UL) /*!< Position of COMPARE2 field. */
#define RTC_INTENSET_COMPARE2_Msk (0x1UL << RTC_INTENSET_COMPARE2_Pos) /*!< Bit mask of COMPARE2 field. */
#define RTC_INTENSET_COMPARE2_Disabled (0UL) /*!< Read: Disabled */
#define RTC_INTENSET_COMPARE2_Enabled (1UL) /*!< Read: Enabled */
#define RTC_INTENSET_COMPARE2_Set (1UL) /*!< Enable */

/* Bit 17 : Write '1' to Enable interrupt for COMPARE[1] event */
#define RTC_INTENSET_COMPARE1_Pos (17UL) /*!< Position of COMPARE1 field. */
#define RTC_INTENSET_COMPARE1_Msk (0x1UL << RTC_INTENSET_COMPARE1_Pos) /*!< Bit mask of COMPARE1 field. */
#define RTC_INTENSET_COMPARE1_Disabled (0UL) /*!< Read: Disabled */
#define RTC_INTENSET_COMPARE1_Enabled (1UL) /*!< Read: Enabled */
#define RTC_INTENSET_COMPARE1_Set (1UL) /*!< Enable */

/* Bit 16 : Write '1' to Enable interrupt for COMPARE[0] event */
#define RTC_INTENSET_COMPARE0_Pos (16UL) /*!< Position of COMPARE0 field. */
#define RTC_INTENSET_COMPARE0_Msk (0x1UL << RTC_INTENSET_COMPARE0_Pos) /*!< Bit mask of COMPARE0 field. */
#define RTC_INTENSET_COMPARE0_Disabled (0UL) /*!< Read: Disabled */
#define RTC_INTENSET_COMPARE0_Enabled (1UL) /*!< Read: Enabled */
#define RTC_INTENSET_COMPARE0_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable interrupt for OVRFLW event */
#define RTC_INTENSET_OVRFLW_Pos (1UL) /*!< Position of OVRFLW field. */
#define RTC_INTENSET_OVRFLW_Msk (0x1UL << RTC_INTENSET_OVRFLW_Pos) /*!< Bit mask of OVRFLW field. */
#define RTC_INTENSET_OVRFLW_Disabled (0UL) /*!< Read: Disabled */
#define RTC_INTENSET_OVRFLW_Enabled (1UL) /*!< Read: Enabled */
#define RTC_INTENSET_OVRFLW_Set (1UL) /*!< Enable */

/* Bit 0 : Write '1' to Enable interrupt for TICK event */
#define RTC_INTENSET_TICK_Pos (0UL) /*!< Position of TICK field. */
#define RTC_INTENSET_TICK_Msk (0x1UL << RTC_INTENSET_TICK_Pos) /*!< Bit mask of TICK field. */
#define RTC_INTENSET_TICK_Disabled (0UL) /*!< Read: Disabled */
#define RTC_INTENSET_TICK_Enabled (1UL) /*!< Read: Enabled */
#define RTC_INTENSET_TICK_Set (1UL) /*!< Enable */

/* Register: RTC_INTENCLR */
/* Description: Disable interrupt */

/* Bit 19 : Write '1' to Disable interrupt for COMPARE[3] event */
#define RTC_INTENCLR_COMPARE3_Pos (19UL) /*!< Position of COMPARE3 field. */
#define RTC_INTENCLR_COMPARE3_Msk (0x1UL << RTC_INTENCLR_COMPARE3_Pos) /*!< Bit mask of COMPARE3 field. */
#define RTC_INTENCLR_COMPARE3_Disabled (0UL) /*!< Read: Disabled */
#define RTC_INTENCLR_COMPARE3_Enabled (1UL) /*!< Read: Enabled */
#define RTC_INTENCLR_COMPARE3_Clear (1UL) /*!< Disable */

/* Bit 18 : Write '1' to Disable interrupt for COMPARE[2] event */
#define RTC_INTENCLR_COMPARE2_Pos (18UL) /*!< Position of COMPARE2 field. */
#define RTC_INTENCLR_COMPARE2_Msk (0x1UL << RTC_INTENCLR_COMPARE2_Pos) /*!< Bit mask of COMPARE2 field. */
#define RTC_INTENCLR_COMPARE2_Disabled (0UL) /*!< Read: Disabled */
#define RTC_INTENCLR_COMPARE2_Enabled (1UL) /*!< Read: Enabled */
#define RTC_INTENCLR_COMPARE2_Clear (1UL) /*!< Disable */

/* Bit 17 : Write '1' to Disable interrupt for COMPARE[1] event */
#define RTC_INTENCLR_COMPARE1_Pos (17UL) /*!< Position of COMPARE1 field. */
#define RTC_INTENCLR_COMPARE1_Msk (0x1UL << RTC_INTENCLR_COMPARE1_Pos) /*!< Bit mask of COMPARE1 field. */
#define RTC_INTENCLR_COMPARE1_Disabled (0UL) /*!< Read: Disabled */
#define RTC_INTENCLR_COMPARE1_Enabled (1UL) /*!< Read: Enabled */
#define RTC_INTENCLR_COMPARE1_Clear (1UL) /*!< Disable */

/* Bit 16 : Write '1' to Disable interrupt for COMPARE[0] event */
#define RTC_INTENCLR_COMPARE0_Pos (16UL) /*!< Position of COMPARE0 field. */
#define RTC_INTENCLR_COMPARE0_Msk (0x1UL << RTC_INTENCLR_COMPARE0_Pos) /*!< Bit mask of COMPARE0 field. */
#define RTC_INTENCLR_COMPARE0_Disabled (0UL) /*!< Read: Disabled */
#define RTC_INTENCLR_COMPARE0_Enabled (1UL) /*!< Read: Enabled */
#define RTC_INTENCLR_COMPARE0_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable interrupt for OVRFLW event */
#define RTC_INTENCLR_OVRFLW_Pos (1UL) /*!< Position of OVRFLW field. */
#define RTC_INTENCLR_OVRFLW_Msk (0x1UL << RTC_INTENCLR_OVRFLW_Pos) /*!< Bit mask of OVRFLW field. */
#define RTC_INTENCLR_OVRFLW_Disabled (0UL) /*!< Read: Disabled */
#define RTC_INTENCLR_OVRFLW_Enabled (1UL) /*!< Read: Enabled */
#define RTC_INTENCLR_OVRFLW_Clear (1UL) /*!< Disable */

/* Bit 0 : Write '1' to Disable interrupt for TICK event */
#define RTC_INTENCLR_TICK_Pos (0UL) /*!< Position of TICK field. */
#define RTC_INTENCLR_TICK_Msk (0x1UL << RTC_INTENCLR_TICK_Pos) /*!< Bit mask of TICK field. */
#define RTC_INTENCLR_TICK_Disabled (0UL) /*!< Read: Disabled */
#define RTC_INTENCLR_TICK_Enabled (1UL) /*!< Read: Enabled */
#define RTC_INTENCLR_TICK_Clear (1UL) /*!< Disable */

/* Register: RTC_EVTEN */
/* Description: Enable or disable event routing */

/* Bit 19 : Enable or disable event routing for COMPARE[3] event */
#define RTC_EVTEN_COMPARE3_Pos (19UL) /*!< Position of COMPARE3 field. */
#define RTC_EVTEN_COMPARE3_Msk (0x1UL << RTC_EVTEN_COMPARE3_Pos) /*!< Bit mask of COMPARE3 field. */
#define RTC_EVTEN_COMPARE3_Disabled (0UL) /*!< Disable */
#define RTC_EVTEN_COMPARE3_Enabled (1UL) /*!< Enable */

/* Bit 18 : Enable or disable event routing for COMPARE[2] event */
#define RTC_EVTEN_COMPARE2_Pos (18UL) /*!< Position of COMPARE2 field. */
#define RTC_EVTEN_COMPARE2_Msk (0x1UL << RTC_EVTEN_COMPARE2_Pos) /*!< Bit mask of COMPARE2 field. */
#define RTC_EVTEN_COMPARE2_Disabled (0UL) /*!< Disable */
#define RTC_EVTEN_COMPARE2_Enabled (1UL) /*!< Enable */

/* Bit 17 : Enable or disable event routing for COMPARE[1] event */
#define RTC_EVTEN_COMPARE1_Pos (17UL) /*!< Position of COMPARE1 field. */
#define RTC_EVTEN_COMPARE1_Msk (0x1UL << RTC_EVTEN_COMPARE1_Pos) /*!< Bit mask of COMPARE1 field. */
#define RTC_EVTEN_COMPARE1_Disabled (0UL) /*!< Disable */
#define RTC_EVTEN_COMPARE1_Enabled (1UL) /*!< Enable */

/* Bit 16 : Enable or disable event routing for COMPARE[0] event */
#define RTC_EVTEN_COMPARE0_Pos (16UL) /*!< Position of COMPARE0 field. */
#define RTC_EVTEN_COMPARE0_Msk (0x1UL << RTC_EVTEN_COMPARE0_Pos) /*!< Bit mask of COMPARE0 field. */
#define RTC_EVTEN_COMPARE0_Disabled (0UL) /*!< Disable */
#define RTC_EVTEN_COMPARE0_Enabled (1UL) /*!< Enable */

/* Bit 1 : Enable or disable event routing for OVRFLW event */
#define RTC_EVTEN_OVRFLW_Pos (1UL) /*!< Position of OVRFLW field. */
#define RTC_EVTEN_OVRFLW_Msk (0x1UL << RTC_EVTEN_OVRFLW_Pos) /*!< Bit mask of OVRFLW field. */
#define RTC_EVTEN_OVRFLW_Disabled (0UL) /*!< Disable */
#define RTC_EVTEN_OVRFLW_Enabled (1UL) /*!< Enable */

/* Bit 0 : Enable or disable event routing for TICK event */
#define RTC_EVTEN_TICK_Pos (0UL) /*!< Position of TICK field. */
#define RTC_EVTEN_TICK_Msk (0x1UL << RTC_EVTEN_TICK_Pos) /*!< Bit mask of TICK field. */
#define RTC_EVTEN_TICK_Disabled (0UL) /*!< Disable */
#define RTC_EVTEN_TICK_Enabled (1UL) /*!< Enable */

/* Register: RTC_EVTENSET */
/* Description: Enable event routing */

/* Bit 19 : Write '1' to Enable event routing for COMPARE[3] event */
#define RTC_EVTENSET_COMPARE3_Pos (19UL) /*!< Position of COMPARE3 field. */
#define RTC_EVTENSET_COMPARE3_Msk (0x1UL << RTC_EVTENSET_COMPARE3_Pos) /*!< Bit mask of COMPARE3 field. */
#define RTC_EVTENSET_COMPARE3_Disabled (0UL) /*!< Read: Disabled */
#define RTC_EVTENSET_COMPARE3_Enabled (1UL) /*!< Read: Enabled */
#define RTC_EVTENSET_COMPARE3_Set (1UL) /*!< Enable */

/* Bit 18 : Write '1' to Enable event routing for COMPARE[2] event */
#define RTC_EVTENSET_COMPARE2_Pos (18UL) /*!< Position of COMPARE2 field. */
#define RTC_EVTENSET_COMPARE2_Msk (0x1UL << RTC_EVTENSET_COMPARE2_Pos) /*!< Bit mask of COMPARE2 field. */
#define RTC_EVTENSET_COMPARE2_Disabled (0UL) /*!< Read: Disabled */
#define RTC_EVTENSET_COMPARE2_Enabled (1UL) /*!< Read: Enabled */
#define RTC_EVTENSET_COMPARE2_Set (1UL) /*!< Enable */

/* Bit 17 : Write '1' to Enable event routing for COMPARE[1] event */
#define RTC_EVTENSET_COMPARE1_Pos (17UL) /*!< Position of COMPARE1 field. */
#define RTC_EVTENSET_COMPARE1_Msk (0x1UL << RTC_EVTENSET_COMPARE1_Pos) /*!< Bit mask of COMPARE1 field. */
#define RTC_EVTENSET_COMPARE1_Disabled (0UL) /*!< Read: Disabled */
#define RTC_EVTENSET_COMPARE1_Enabled (1UL) /*!< Read: Enabled */
#define RTC_EVTENSET_COMPARE1_Set (1UL) /*!< Enable */

/* Bit 16 : Write '1' to Enable event routing for COMPARE[0] event */
#define RTC_EVTENSET_COMPARE0_Pos (16UL) /*!< Position of COMPARE0 field. */
#define RTC_EVTENSET_COMPARE0_Msk (0x1UL << RTC_EVTENSET_COMPARE0_Pos) /*!< Bit mask of COMPARE0 field. */
#define RTC_EVTENSET_COMPARE0_Disabled (0UL) /*!< Read: Disabled */
#define RTC_EVTENSET_COMPARE0_Enabled (1UL) /*!< Read: Enabled */
#define RTC_EVTENSET_COMPARE0_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable event routing for OVRFLW event */
#define RTC_EVTENSET_OVRFLW_Pos (1UL) /*!< Position of OVRFLW field. */
#define RTC_EVTENSET_OVRFLW_Msk (0x1UL << RTC_EVTENSET_OVRFLW_Pos) /*!< Bit mask of OVRFLW field. */
#define RTC_EVTENSET_OVRFLW_Disabled (0UL) /*!< Read: Disabled */
#define RTC_EVTENSET_OVRFLW_Enabled (1UL) /*!< Read: Enabled */
#define RTC_EVTENSET_OVRFLW_Set (1UL) /*!< Enable */

/* Bit 0 : Write '1' to Enable event routing for TICK event */
#define RTC_EVTENSET_TICK_Pos (0UL) /*!< Position of TICK field. */
#define RTC_EVTENSET_TICK_Msk (0x1UL << RTC_EVTENSET_TICK_Pos) /*!< Bit mask of TICK field. */
#define RTC_EVTENSET_TICK_Disabled (0UL) /*!< Read: Disabled */
#define RTC_EVTENSET_TICK_Enabled (1UL) /*!< Read: Enabled */
#define RTC_EVTENSET_TICK_Set (1UL) /*!< Enable */

/* Register: RTC_EVTENCLR */
/* Description: Disable event routing */

/* Bit 19 : Write '1' to Disable event routing for COMPARE[3] event */
#define RTC_EVTENCLR_COMPARE3_Pos (19UL) /*!< Position of COMPARE3 field. */
#define RTC_EVTENCLR_COMPARE3_Msk (0x1UL << RTC_EVTENCLR_COMPARE3_Pos) /*!< Bit mask of COMPARE3 field. */
#define RTC_EVTENCLR_COMPARE3_Disabled (0UL) /*!< Read: Disabled */
#define RTC_EVTENCLR_COMPARE3_Enabled (1UL) /*!< Read: Enabled */
#define RTC_EVTENCLR_COMPARE3_Clear (1UL) /*!< Disable */

/* Bit 18 : Write '1' to Disable event routing for COMPARE[2] event */
#define RTC_EVTENCLR_COMPARE2_Pos (18UL) /*!< Position of COMPARE2 field. */
#define RTC_EVTENCLR_COMPARE2_Msk (0x1UL << RTC_EVTENCLR_COMPARE2_Pos) /*!< Bit mask of COMPARE2 field. */
#define RTC_EVTENCLR_COMPARE2_Disabled (0UL) /*!< Read: Disabled */
#define RTC_EVTENCLR_COMPARE2_Enabled (1UL) /*!< Read: Enabled */
#define RTC_EVTENCLR_COMPARE2_Clear (1UL) /*!< Disable */

/* Bit 17 : Write '1' to Disable event routing for COMPARE[1] event */
#define RTC_EVTENCLR_COMPARE1_Pos (17UL) /*!< Position of COMPARE1 field. */
#define RTC_EVTENCLR_COMPARE1_Msk (0x1UL << RTC_EVTENCLR_COMPARE1_Pos) /*!< Bit mask of COMPARE1 field. */
#define RTC_EVTENCLR_COMPARE1_Disabled (0UL) /*!< Read: Disabled */
#define RTC_EVTENCLR_COMPARE1_Enabled (1UL) /*!< Read: Enabled */
#define RTC_EVTENCLR_COMPARE1_Clear (1UL) /*!< Disable */

/* Bit 16 : Write '1' to Disable event routing for COMPARE[0] event */
#define RTC_EVTENCLR_COMPARE0_Pos (16UL) /*!< Position of COMPARE0 field. */
#define RTC_EVTENCLR_COMPARE0_Msk (0x1UL << RTC_EVTENCLR_COMPARE0_Pos) /*!< Bit mask of COMPARE0 field. */
#define RTC_EVTENCLR_COMPARE0_Disabled (0UL) /*!< Read: Disabled */
#define RTC_EVTENCLR_COMPARE0_Enabled (1UL) /*!< Read: Enabled */
#define RTC_EVTENCLR_COMPARE0_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable event routing for OVRFLW event */
#define RTC_EVTENCLR_OVRFLW_Pos (1UL) /*!< Position of OVRFLW field. */
#define RTC_EVTENCLR_OVRFLW_Msk (0x1UL << RTC_EVTENCLR_OVRFLW_Pos) /*!< Bit mask of OVRFLW field. */
#define RTC_EVTENCLR_OVRFLW_Disabled (0UL) /*!< Read: Disabled */
#define RTC_EVTENCLR_OVRFLW_Enabled (1UL) /*!< Read: Enabled */
#define RTC_EVTENCLR_OVRFLW_Clear (1UL) /*!< Disable */

/* Bit 0 : Write '1' to Disable event routing for TICK event */
#define RTC_EVTENCLR_TICK_Pos (0UL) /*!< Position of TICK field. */
#define RTC_EVTENCLR_TICK_Msk (0x1UL << RTC_EVTENCLR_TICK_Pos) /*!< Bit mask of TICK field. */
#define RTC_EVTENCLR_TICK_Disabled (0UL) /*!< Read: Disabled */
#define RTC_EVTENCLR_TICK_Enabled (1UL) /*!< Read: Enabled */
#define RTC_EVTENCLR_TICK_Clear (1UL) /*!< Disable */

/* Register: RTC_COUNTER */
/* Description: Current COUNTER value */

/* Bits 23..0 : Counter value */
#define RTC_COUNTER_COUNTER_Pos (0UL) /*!< Position of COUNTER field. */
#define RTC_COUNTER_COUNTER_Msk (0xFFFFFFUL << RTC_COUNTER_COUNTER_Pos) /*!< Bit mask of COUNTER field. */

/* Register: RTC_PRESCALER */
/* Description: 12 bit prescaler for COUNTER frequency (32768/(PRESCALER+1)).Must be written when RTC is stopped */

/* Bits 11..0 : Prescaler value */
#define RTC_PRESCALER_PRESCALER_Pos (0UL) /*!< Position of PRESCALER field. */
#define RTC_PRESCALER_PRESCALER_Msk (0xFFFUL << RTC_PRESCALER_PRESCALER_Pos) /*!< Bit mask of PRESCALER field. */

/* Register: RTC_CC */
/* Description: Description collection[0]:  Compare register 0 */

/* Bits 23..0 : Compare value */
#define RTC_CC_COMPARE_Pos (0UL) /*!< Position of COMPARE field. */
#define RTC_CC_COMPARE_Msk (0xFFFFFFUL << RTC_CC_COMPARE_Pos) /*!< Bit mask of COMPARE field. */


/* Peripheral: SAADC */
/* Description: Analog to Digital Converter */

/* Register: SAADC_INTEN */
/* Description: Enable or disable interrupt */

/* Bit 21 : Enable or disable interrupt for CH[7].LIMITL event */
#define SAADC_INTEN_CH7LIMITL_Pos (21UL) /*!< Position of CH7LIMITL field. */
#define SAADC_INTEN_CH7LIMITL_Msk (0x1UL << SAADC_INTEN_CH7LIMITL_Pos) /*!< Bit mask of CH7LIMITL field. */
#define SAADC_INTEN_CH7LIMITL_Disabled (0UL) /*!< Disable */
#define SAADC_INTEN_CH7LIMITL_Enabled (1UL) /*!< Enable */

/* Bit 20 : Enable or disable interrupt for CH[7].LIMITH event */
#define SAADC_INTEN_CH7LIMITH_Pos (20UL) /*!< Position of CH7LIMITH field. */
#define SAADC_INTEN_CH7LIMITH_Msk (0x1UL << SAADC_INTEN_CH7LIMITH_Pos) /*!< Bit mask of CH7LIMITH field. */
#define SAADC_INTEN_CH7LIMITH_Disabled (0UL) /*!< Disable */
#define SAADC_INTEN_CH7LIMITH_Enabled (1UL) /*!< Enable */

/* Bit 19 : Enable or disable interrupt for CH[6].LIMITL event */
#define SAADC_INTEN_CH6LIMITL_Pos (19UL) /*!< Position of CH6LIMITL field. */
#define SAADC_INTEN_CH6LIMITL_Msk (0x1UL << SAADC_INTEN_CH6LIMITL_Pos) /*!< Bit mask of CH6LIMITL field. */
#define SAADC_INTEN_CH6LIMITL_Disabled (0UL) /*!< Disable */
#define SAADC_INTEN_CH6LIMITL_Enabled (1UL) /*!< Enable */

/* Bit 18 : Enable or disable interrupt for CH[6].LIMITH event */
#define SAADC_INTEN_CH6LIMITH_Pos (18UL) /*!< Position of CH6LIMITH field. */
#define SAADC_INTEN_CH6LIMITH_Msk (0x1UL << SAADC_INTEN_CH6LIMITH_Pos) /*!< Bit mask of CH6LIMITH field. */
#define SAADC_INTEN_CH6LIMITH_Disabled (0UL) /*!< Disable */
#define SAADC_INTEN_CH6LIMITH_Enabled (1UL) /*!< Enable */

/* Bit 17 : Enable or disable interrupt for CH[5].LIMITL event */
#define SAADC_INTEN_CH5LIMITL_Pos (17UL) /*!< Position of CH5LIMITL field. */
#define SAADC_INTEN_CH5LIMITL_Msk (0x1UL << SAADC_INTEN_CH5LIMITL_Pos) /*!< Bit mask of CH5LIMITL field. */
#define SAADC_INTEN_CH5LIMITL_Disabled (0UL) /*!< Disable */
#define SAADC_INTEN_CH5LIMITL_Enabled (1UL) /*!< Enable */

/* Bit 16 : Enable or disable interrupt for CH[5].LIMITH event */
#define SAADC_INTEN_CH5LIMITH_Pos (16UL) /*!< Position of CH5LIMITH field. */
#define SAADC_INTEN_CH5LIMITH_Msk (0x1UL << SAADC_INTEN_CH5LIMITH_Pos) /*!< Bit mask of CH5LIMITH field. */
#define SAADC_INTEN_CH5LIMITH_Disabled (0UL) /*!< Disable */
#define SAADC_INTEN_CH5LIMITH_Enabled (1UL) /*!< Enable */

/* Bit 15 : Enable or disable interrupt for CH[4].LIMITL event */
#define SAADC_INTEN_CH4LIMITL_Pos (15UL) /*!< Position of CH4LIMITL field. */
#define SAADC_INTEN_CH4LIMITL_Msk (0x1UL << SAADC_INTEN_CH4LIMITL_Pos) /*!< Bit mask of CH4LIMITL field. */
#define SAADC_INTEN_CH4LIMITL_Disabled (0UL) /*!< Disable */
#define SAADC_INTEN_CH4LIMITL_Enabled (1UL) /*!< Enable */

/* Bit 14 : Enable or disable interrupt for CH[4].LIMITH event */
#define SAADC_INTEN_CH4LIMITH_Pos (14UL) /*!< Position of CH4LIMITH field. */
#define SAADC_INTEN_CH4LIMITH_Msk (0x1UL << SAADC_INTEN_CH4LIMITH_Pos) /*!< Bit mask of CH4LIMITH field. */
#define SAADC_INTEN_CH4LIMITH_Disabled (0UL) /*!< Disable */
#define SAADC_INTEN_CH4LIMITH_Enabled (1UL) /*!< Enable */

/* Bit 13 : Enable or disable interrupt for CH[3].LIMITL event */
#define SAADC_INTEN_CH3LIMITL_Pos (13UL) /*!< Position of CH3LIMITL field. */
#define SAADC_INTEN_CH3LIMITL_Msk (0x1UL << SAADC_INTEN_CH3LIMITL_Pos) /*!< Bit mask of CH3LIMITL field. */
#define SAADC_INTEN_CH3LIMITL_Disabled (0UL) /*!< Disable */
#define SAADC_INTEN_CH3LIMITL_Enabled (1UL) /*!< Enable */

/* Bit 12 : Enable or disable interrupt for CH[3].LIMITH event */
#define SAADC_INTEN_CH3LIMITH_Pos (12UL) /*!< Position of CH3LIMITH field. */
#define SAADC_INTEN_CH3LIMITH_Msk (0x1UL << SAADC_INTEN_CH3LIMITH_Pos) /*!< Bit mask of CH3LIMITH field. */
#define SAADC_INTEN_CH3LIMITH_Disabled (0UL) /*!< Disable */
#define SAADC_INTEN_CH3LIMITH_Enabled (1UL) /*!< Enable */

/* Bit 11 : Enable or disable interrupt for CH[2].LIMITL event */
#define SAADC_INTEN_CH2LIMITL_Pos (11UL) /*!< Position of CH2LIMITL field. */
#define SAADC_INTEN_CH2LIMITL_Msk (0x1UL << SAADC_INTEN_CH2LIMITL_Pos) /*!< Bit mask of CH2LIMITL field. */
#define SAADC_INTEN_CH2LIMITL_Disabled (0UL) /*!< Disable */
#define SAADC_INTEN_CH2LIMITL_Enabled (1UL) /*!< Enable */

/* Bit 10 : Enable or disable interrupt for CH[2].LIMITH event */
#define SAADC_INTEN_CH2LIMITH_Pos (10UL) /*!< Position of CH2LIMITH field. */
#define SAADC_INTEN_CH2LIMITH_Msk (0x1UL << SAADC_INTEN_CH2LIMITH_Pos) /*!< Bit mask of CH2LIMITH field. */
#define SAADC_INTEN_CH2LIMITH_Disabled (0UL) /*!< Disable */
#define SAADC_INTEN_CH2LIMITH_Enabled (1UL) /*!< Enable */

/* Bit 9 : Enable or disable interrupt for CH[1].LIMITL event */
#define SAADC_INTEN_CH1LIMITL_Pos (9UL) /*!< Position of CH1LIMITL field. */
#define SAADC_INTEN_CH1LIMITL_Msk (0x1UL << SAADC_INTEN_CH1LIMITL_Pos) /*!< Bit mask of CH1LIMITL field. */
#define SAADC_INTEN_CH1LIMITL_Disabled (0UL) /*!< Disable */
#define SAADC_INTEN_CH1LIMITL_Enabled (1UL) /*!< Enable */

/* Bit 8 : Enable or disable interrupt for CH[1].LIMITH event */
#define SAADC_INTEN_CH1LIMITH_Pos (8UL) /*!< Position of CH1LIMITH field. */
#define SAADC_INTEN_CH1LIMITH_Msk (0x1UL << SAADC_INTEN_CH1LIMITH_Pos) /*!< Bit mask of CH1LIMITH field. */
#define SAADC_INTEN_CH1LIMITH_Disabled (0UL) /*!< Disable */
#define SAADC_INTEN_CH1LIMITH_Enabled (1UL) /*!< Enable */

/* Bit 7 : Enable or disable interrupt for CH[0].LIMITL event */
#define SAADC_INTEN_CH0LIMITL_Pos (7UL) /*!< Position of CH0LIMITL field. */
#define SAADC_INTEN_CH0LIMITL_Msk (0x1UL << SAADC_INTEN_CH0LIMITL_Pos) /*!< Bit mask of CH0LIMITL field. */
#define SAADC_INTEN_CH0LIMITL_Disabled (0UL) /*!< Disable */
#define SAADC_INTEN_CH0LIMITL_Enabled (1UL) /*!< Enable */

/* Bit 6 : Enable or disable interrupt for CH[0].LIMITH event */
#define SAADC_INTEN_CH0LIMITH_Pos (6UL) /*!< Position of CH0LIMITH field. */
#define SAADC_INTEN_CH0LIMITH_Msk (0x1UL << SAADC_INTEN_CH0LIMITH_Pos) /*!< Bit mask of CH0LIMITH field. */
#define SAADC_INTEN_CH0LIMITH_Disabled (0UL) /*!< Disable */
#define SAADC_INTEN_CH0LIMITH_Enabled (1UL) /*!< Enable */

/* Bit 5 : Enable or disable interrupt for STOPPED event */
#define SAADC_INTEN_STOPPED_Pos (5UL) /*!< Position of STOPPED field. */
#define SAADC_INTEN_STOPPED_Msk (0x1UL << SAADC_INTEN_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define SAADC_INTEN_STOPPED_Disabled (0UL) /*!< Disable */
#define SAADC_INTEN_STOPPED_Enabled (1UL) /*!< Enable */

/* Bit 4 : Enable or disable interrupt for CALIBRATEDONE event */
#define SAADC_INTEN_CALIBRATEDONE_Pos (4UL) /*!< Position of CALIBRATEDONE field. */
#define SAADC_INTEN_CALIBRATEDONE_Msk (0x1UL << SAADC_INTEN_CALIBRATEDONE_Pos) /*!< Bit mask of CALIBRATEDONE field. */
#define SAADC_INTEN_CALIBRATEDONE_Disabled (0UL) /*!< Disable */
#define SAADC_INTEN_CALIBRATEDONE_Enabled (1UL) /*!< Enable */

/* Bit 3 : Enable or disable interrupt for RESULTDONE event */
#define SAADC_INTEN_RESULTDONE_Pos (3UL) /*!< Position of RESULTDONE field. */
#define SAADC_INTEN_RESULTDONE_Msk (0x1UL << SAADC_INTEN_RESULTDONE_Pos) /*!< Bit mask of RESULTDONE field. */
#define SAADC_INTEN_RESULTDONE_Disabled (0UL) /*!< Disable */
#define SAADC_INTEN_RESULTDONE_Enabled (1UL) /*!< Enable */

/* Bit 2 : Enable or disable interrupt for DONE event */
#define SAADC_INTEN_DONE_Pos (2UL) /*!< Position of DONE field. */
#define SAADC_INTEN_DONE_Msk (0x1UL << SAADC_INTEN_DONE_Pos) /*!< Bit mask of DONE field. */
#define SAADC_INTEN_DONE_Disabled (0UL) /*!< Disable */
#define SAADC_INTEN_DONE_Enabled (1UL) /*!< Enable */

/* Bit 1 : Enable or disable interrupt for END event */
#define SAADC_INTEN_END_Pos (1UL) /*!< Position of END field. */
#define SAADC_INTEN_END_Msk (0x1UL << SAADC_INTEN_END_Pos) /*!< Bit mask of END field. */
#define SAADC_INTEN_END_Disabled (0UL) /*!< Disable */
#define SAADC_INTEN_END_Enabled (1UL) /*!< Enable */

/* Bit 0 : Enable or disable interrupt for STARTED event */
#define SAADC_INTEN_STARTED_Pos (0UL) /*!< Position of STARTED field. */
#define SAADC_INTEN_STARTED_Msk (0x1UL << SAADC_INTEN_STARTED_Pos) /*!< Bit mask of STARTED field. */
#define SAADC_INTEN_STARTED_Disabled (0UL) /*!< Disable */
#define SAADC_INTEN_STARTED_Enabled (1UL) /*!< Enable */

/* Register: SAADC_INTENSET */
/* Description: Enable interrupt */

/* Bit 21 : Write '1' to Enable interrupt for CH[7].LIMITL event */
#define SAADC_INTENSET_CH7LIMITL_Pos (21UL) /*!< Position of CH7LIMITL field. */
#define SAADC_INTENSET_CH7LIMITL_Msk (0x1UL << SAADC_INTENSET_CH7LIMITL_Pos) /*!< Bit mask of CH7LIMITL field. */
#define SAADC_INTENSET_CH7LIMITL_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENSET_CH7LIMITL_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENSET_CH7LIMITL_Set (1UL) /*!< Enable */

/* Bit 20 : Write '1' to Enable interrupt for CH[7].LIMITH event */
#define SAADC_INTENSET_CH7LIMITH_Pos (20UL) /*!< Position of CH7LIMITH field. */
#define SAADC_INTENSET_CH7LIMITH_Msk (0x1UL << SAADC_INTENSET_CH7LIMITH_Pos) /*!< Bit mask of CH7LIMITH field. */
#define SAADC_INTENSET_CH7LIMITH_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENSET_CH7LIMITH_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENSET_CH7LIMITH_Set (1UL) /*!< Enable */

/* Bit 19 : Write '1' to Enable interrupt for CH[6].LIMITL event */
#define SAADC_INTENSET_CH6LIMITL_Pos (19UL) /*!< Position of CH6LIMITL field. */
#define SAADC_INTENSET_CH6LIMITL_Msk (0x1UL << SAADC_INTENSET_CH6LIMITL_Pos) /*!< Bit mask of CH6LIMITL field. */
#define SAADC_INTENSET_CH6LIMITL_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENSET_CH6LIMITL_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENSET_CH6LIMITL_Set (1UL) /*!< Enable */

/* Bit 18 : Write '1' to Enable interrupt for CH[6].LIMITH event */
#define SAADC_INTENSET_CH6LIMITH_Pos (18UL) /*!< Position of CH6LIMITH field. */
#define SAADC_INTENSET_CH6LIMITH_Msk (0x1UL << SAADC_INTENSET_CH6LIMITH_Pos) /*!< Bit mask of CH6LIMITH field. */
#define SAADC_INTENSET_CH6LIMITH_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENSET_CH6LIMITH_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENSET_CH6LIMITH_Set (1UL) /*!< Enable */

/* Bit 17 : Write '1' to Enable interrupt for CH[5].LIMITL event */
#define SAADC_INTENSET_CH5LIMITL_Pos (17UL) /*!< Position of CH5LIMITL field. */
#define SAADC_INTENSET_CH5LIMITL_Msk (0x1UL << SAADC_INTENSET_CH5LIMITL_Pos) /*!< Bit mask of CH5LIMITL field. */
#define SAADC_INTENSET_CH5LIMITL_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENSET_CH5LIMITL_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENSET_CH5LIMITL_Set (1UL) /*!< Enable */

/* Bit 16 : Write '1' to Enable interrupt for CH[5].LIMITH event */
#define SAADC_INTENSET_CH5LIMITH_Pos (16UL) /*!< Position of CH5LIMITH field. */
#define SAADC_INTENSET_CH5LIMITH_Msk (0x1UL << SAADC_INTENSET_CH5LIMITH_Pos) /*!< Bit mask of CH5LIMITH field. */
#define SAADC_INTENSET_CH5LIMITH_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENSET_CH5LIMITH_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENSET_CH5LIMITH_Set (1UL) /*!< Enable */

/* Bit 15 : Write '1' to Enable interrupt for CH[4].LIMITL event */
#define SAADC_INTENSET_CH4LIMITL_Pos (15UL) /*!< Position of CH4LIMITL field. */
#define SAADC_INTENSET_CH4LIMITL_Msk (0x1UL << SAADC_INTENSET_CH4LIMITL_Pos) /*!< Bit mask of CH4LIMITL field. */
#define SAADC_INTENSET_CH4LIMITL_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENSET_CH4LIMITL_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENSET_CH4LIMITL_Set (1UL) /*!< Enable */

/* Bit 14 : Write '1' to Enable interrupt for CH[4].LIMITH event */
#define SAADC_INTENSET_CH4LIMITH_Pos (14UL) /*!< Position of CH4LIMITH field. */
#define SAADC_INTENSET_CH4LIMITH_Msk (0x1UL << SAADC_INTENSET_CH4LIMITH_Pos) /*!< Bit mask of CH4LIMITH field. */
#define SAADC_INTENSET_CH4LIMITH_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENSET_CH4LIMITH_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENSET_CH4LIMITH_Set (1UL) /*!< Enable */

/* Bit 13 : Write '1' to Enable interrupt for CH[3].LIMITL event */
#define SAADC_INTENSET_CH3LIMITL_Pos (13UL) /*!< Position of CH3LIMITL field. */
#define SAADC_INTENSET_CH3LIMITL_Msk (0x1UL << SAADC_INTENSET_CH3LIMITL_Pos) /*!< Bit mask of CH3LIMITL field. */
#define SAADC_INTENSET_CH3LIMITL_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENSET_CH3LIMITL_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENSET_CH3LIMITL_Set (1UL) /*!< Enable */

/* Bit 12 : Write '1' to Enable interrupt for CH[3].LIMITH event */
#define SAADC_INTENSET_CH3LIMITH_Pos (12UL) /*!< Position of CH3LIMITH field. */
#define SAADC_INTENSET_CH3LIMITH_Msk (0x1UL << SAADC_INTENSET_CH3LIMITH_Pos) /*!< Bit mask of CH3LIMITH field. */
#define SAADC_INTENSET_CH3LIMITH_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENSET_CH3LIMITH_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENSET_CH3LIMITH_Set (1UL) /*!< Enable */

/* Bit 11 : Write '1' to Enable interrupt for CH[2].LIMITL event */
#define SAADC_INTENSET_CH2LIMITL_Pos (11UL) /*!< Position of CH2LIMITL field. */
#define SAADC_INTENSET_CH2LIMITL_Msk (0x1UL << SAADC_INTENSET_CH2LIMITL_Pos) /*!< Bit mask of CH2LIMITL field. */
#define SAADC_INTENSET_CH2LIMITL_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENSET_CH2LIMITL_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENSET_CH2LIMITL_Set (1UL) /*!< Enable */

/* Bit 10 : Write '1' to Enable interrupt for CH[2].LIMITH event */
#define SAADC_INTENSET_CH2LIMITH_Pos (10UL) /*!< Position of CH2LIMITH field. */
#define SAADC_INTENSET_CH2LIMITH_Msk (0x1UL << SAADC_INTENSET_CH2LIMITH_Pos) /*!< Bit mask of CH2LIMITH field. */
#define SAADC_INTENSET_CH2LIMITH_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENSET_CH2LIMITH_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENSET_CH2LIMITH_Set (1UL) /*!< Enable */

/* Bit 9 : Write '1' to Enable interrupt for CH[1].LIMITL event */
#define SAADC_INTENSET_CH1LIMITL_Pos (9UL) /*!< Position of CH1LIMITL field. */
#define SAADC_INTENSET_CH1LIMITL_Msk (0x1UL << SAADC_INTENSET_CH1LIMITL_Pos) /*!< Bit mask of CH1LIMITL field. */
#define SAADC_INTENSET_CH1LIMITL_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENSET_CH1LIMITL_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENSET_CH1LIMITL_Set (1UL) /*!< Enable */

/* Bit 8 : Write '1' to Enable interrupt for CH[1].LIMITH event */
#define SAADC_INTENSET_CH1LIMITH_Pos (8UL) /*!< Position of CH1LIMITH field. */
#define SAADC_INTENSET_CH1LIMITH_Msk (0x1UL << SAADC_INTENSET_CH1LIMITH_Pos) /*!< Bit mask of CH1LIMITH field. */
#define SAADC_INTENSET_CH1LIMITH_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENSET_CH1LIMITH_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENSET_CH1LIMITH_Set (1UL) /*!< Enable */

/* Bit 7 : Write '1' to Enable interrupt for CH[0].LIMITL event */
#define SAADC_INTENSET_CH0LIMITL_Pos (7UL) /*!< Position of CH0LIMITL field. */
#define SAADC_INTENSET_CH0LIMITL_Msk (0x1UL << SAADC_INTENSET_CH0LIMITL_Pos) /*!< Bit mask of CH0LIMITL field. */
#define SAADC_INTENSET_CH0LIMITL_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENSET_CH0LIMITL_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENSET_CH0LIMITL_Set (1UL) /*!< Enable */

/* Bit 6 : Write '1' to Enable interrupt for CH[0].LIMITH event */
#define SAADC_INTENSET_CH0LIMITH_Pos (6UL) /*!< Position of CH0LIMITH field. */
#define SAADC_INTENSET_CH0LIMITH_Msk (0x1UL << SAADC_INTENSET_CH0LIMITH_Pos) /*!< Bit mask of CH0LIMITH field. */
#define SAADC_INTENSET_CH0LIMITH_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENSET_CH0LIMITH_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENSET_CH0LIMITH_Set (1UL) /*!< Enable */

/* Bit 5 : Write '1' to Enable interrupt for STOPPED event */
#define SAADC_INTENSET_STOPPED_Pos (5UL) /*!< Position of STOPPED field. */
#define SAADC_INTENSET_STOPPED_Msk (0x1UL << SAADC_INTENSET_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define SAADC_INTENSET_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENSET_STOPPED_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENSET_STOPPED_Set (1UL) /*!< Enable */

/* Bit 4 : Write '1' to Enable interrupt for CALIBRATEDONE event */
#define SAADC_INTENSET_CALIBRATEDONE_Pos (4UL) /*!< Position of CALIBRATEDONE field. */
#define SAADC_INTENSET_CALIBRATEDONE_Msk (0x1UL << SAADC_INTENSET_CALIBRATEDONE_Pos) /*!< Bit mask of CALIBRATEDONE field. */
#define SAADC_INTENSET_CALIBRATEDONE_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENSET_CALIBRATEDONE_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENSET_CALIBRATEDONE_Set (1UL) /*!< Enable */

/* Bit 3 : Write '1' to Enable interrupt for RESULTDONE event */
#define SAADC_INTENSET_RESULTDONE_Pos (3UL) /*!< Position of RESULTDONE field. */
#define SAADC_INTENSET_RESULTDONE_Msk (0x1UL << SAADC_INTENSET_RESULTDONE_Pos) /*!< Bit mask of RESULTDONE field. */
#define SAADC_INTENSET_RESULTDONE_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENSET_RESULTDONE_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENSET_RESULTDONE_Set (1UL) /*!< Enable */

/* Bit 2 : Write '1' to Enable interrupt for DONE event */
#define SAADC_INTENSET_DONE_Pos (2UL) /*!< Position of DONE field. */
#define SAADC_INTENSET_DONE_Msk (0x1UL << SAADC_INTENSET_DONE_Pos) /*!< Bit mask of DONE field. */
#define SAADC_INTENSET_DONE_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENSET_DONE_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENSET_DONE_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable interrupt for END event */
#define SAADC_INTENSET_END_Pos (1UL) /*!< Position of END field. */
#define SAADC_INTENSET_END_Msk (0x1UL << SAADC_INTENSET_END_Pos) /*!< Bit mask of END field. */
#define SAADC_INTENSET_END_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENSET_END_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENSET_END_Set (1UL) /*!< Enable */

/* Bit 0 : Write '1' to Enable interrupt for STARTED event */
#define SAADC_INTENSET_STARTED_Pos (0UL) /*!< Position of STARTED field. */
#define SAADC_INTENSET_STARTED_Msk (0x1UL << SAADC_INTENSET_STARTED_Pos) /*!< Bit mask of STARTED field. */
#define SAADC_INTENSET_STARTED_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENSET_STARTED_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENSET_STARTED_Set (1UL) /*!< Enable */

/* Register: SAADC_INTENCLR */
/* Description: Disable interrupt */

/* Bit 21 : Write '1' to Disable interrupt for CH[7].LIMITL event */
#define SAADC_INTENCLR_CH7LIMITL_Pos (21UL) /*!< Position of CH7LIMITL field. */
#define SAADC_INTENCLR_CH7LIMITL_Msk (0x1UL << SAADC_INTENCLR_CH7LIMITL_Pos) /*!< Bit mask of CH7LIMITL field. */
#define SAADC_INTENCLR_CH7LIMITL_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENCLR_CH7LIMITL_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENCLR_CH7LIMITL_Clear (1UL) /*!< Disable */

/* Bit 20 : Write '1' to Disable interrupt for CH[7].LIMITH event */
#define SAADC_INTENCLR_CH7LIMITH_Pos (20UL) /*!< Position of CH7LIMITH field. */
#define SAADC_INTENCLR_CH7LIMITH_Msk (0x1UL << SAADC_INTENCLR_CH7LIMITH_Pos) /*!< Bit mask of CH7LIMITH field. */
#define SAADC_INTENCLR_CH7LIMITH_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENCLR_CH7LIMITH_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENCLR_CH7LIMITH_Clear (1UL) /*!< Disable */

/* Bit 19 : Write '1' to Disable interrupt for CH[6].LIMITL event */
#define SAADC_INTENCLR_CH6LIMITL_Pos (19UL) /*!< Position of CH6LIMITL field. */
#define SAADC_INTENCLR_CH6LIMITL_Msk (0x1UL << SAADC_INTENCLR_CH6LIMITL_Pos) /*!< Bit mask of CH6LIMITL field. */
#define SAADC_INTENCLR_CH6LIMITL_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENCLR_CH6LIMITL_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENCLR_CH6LIMITL_Clear (1UL) /*!< Disable */

/* Bit 18 : Write '1' to Disable interrupt for CH[6].LIMITH event */
#define SAADC_INTENCLR_CH6LIMITH_Pos (18UL) /*!< Position of CH6LIMITH field. */
#define SAADC_INTENCLR_CH6LIMITH_Msk (0x1UL << SAADC_INTENCLR_CH6LIMITH_Pos) /*!< Bit mask of CH6LIMITH field. */
#define SAADC_INTENCLR_CH6LIMITH_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENCLR_CH6LIMITH_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENCLR_CH6LIMITH_Clear (1UL) /*!< Disable */

/* Bit 17 : Write '1' to Disable interrupt for CH[5].LIMITL event */
#define SAADC_INTENCLR_CH5LIMITL_Pos (17UL) /*!< Position of CH5LIMITL field. */
#define SAADC_INTENCLR_CH5LIMITL_Msk (0x1UL << SAADC_INTENCLR_CH5LIMITL_Pos) /*!< Bit mask of CH5LIMITL field. */
#define SAADC_INTENCLR_CH5LIMITL_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENCLR_CH5LIMITL_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENCLR_CH5LIMITL_Clear (1UL) /*!< Disable */

/* Bit 16 : Write '1' to Disable interrupt for CH[5].LIMITH event */
#define SAADC_INTENCLR_CH5LIMITH_Pos (16UL) /*!< Position of CH5LIMITH field. */
#define SAADC_INTENCLR_CH5LIMITH_Msk (0x1UL << SAADC_INTENCLR_CH5LIMITH_Pos) /*!< Bit mask of CH5LIMITH field. */
#define SAADC_INTENCLR_CH5LIMITH_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENCLR_CH5LIMITH_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENCLR_CH5LIMITH_Clear (1UL) /*!< Disable */

/* Bit 15 : Write '1' to Disable interrupt for CH[4].LIMITL event */
#define SAADC_INTENCLR_CH4LIMITL_Pos (15UL) /*!< Position of CH4LIMITL field. */
#define SAADC_INTENCLR_CH4LIMITL_Msk (0x1UL << SAADC_INTENCLR_CH4LIMITL_Pos) /*!< Bit mask of CH4LIMITL field. */
#define SAADC_INTENCLR_CH4LIMITL_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENCLR_CH4LIMITL_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENCLR_CH4LIMITL_Clear (1UL) /*!< Disable */

/* Bit 14 : Write '1' to Disable interrupt for CH[4].LIMITH event */
#define SAADC_INTENCLR_CH4LIMITH_Pos (14UL) /*!< Position of CH4LIMITH field. */
#define SAADC_INTENCLR_CH4LIMITH_Msk (0x1UL << SAADC_INTENCLR_CH4LIMITH_Pos) /*!< Bit mask of CH4LIMITH field. */
#define SAADC_INTENCLR_CH4LIMITH_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENCLR_CH4LIMITH_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENCLR_CH4LIMITH_Clear (1UL) /*!< Disable */

/* Bit 13 : Write '1' to Disable interrupt for CH[3].LIMITL event */
#define SAADC_INTENCLR_CH3LIMITL_Pos (13UL) /*!< Position of CH3LIMITL field. */
#define SAADC_INTENCLR_CH3LIMITL_Msk (0x1UL << SAADC_INTENCLR_CH3LIMITL_Pos) /*!< Bit mask of CH3LIMITL field. */
#define SAADC_INTENCLR_CH3LIMITL_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENCLR_CH3LIMITL_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENCLR_CH3LIMITL_Clear (1UL) /*!< Disable */

/* Bit 12 : Write '1' to Disable interrupt for CH[3].LIMITH event */
#define SAADC_INTENCLR_CH3LIMITH_Pos (12UL) /*!< Position of CH3LIMITH field. */
#define SAADC_INTENCLR_CH3LIMITH_Msk (0x1UL << SAADC_INTENCLR_CH3LIMITH_Pos) /*!< Bit mask of CH3LIMITH field. */
#define SAADC_INTENCLR_CH3LIMITH_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENCLR_CH3LIMITH_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENCLR_CH3LIMITH_Clear (1UL) /*!< Disable */

/* Bit 11 : Write '1' to Disable interrupt for CH[2].LIMITL event */
#define SAADC_INTENCLR_CH2LIMITL_Pos (11UL) /*!< Position of CH2LIMITL field. */
#define SAADC_INTENCLR_CH2LIMITL_Msk (0x1UL << SAADC_INTENCLR_CH2LIMITL_Pos) /*!< Bit mask of CH2LIMITL field. */
#define SAADC_INTENCLR_CH2LIMITL_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENCLR_CH2LIMITL_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENCLR_CH2LIMITL_Clear (1UL) /*!< Disable */

/* Bit 10 : Write '1' to Disable interrupt for CH[2].LIMITH event */
#define SAADC_INTENCLR_CH2LIMITH_Pos (10UL) /*!< Position of CH2LIMITH field. */
#define SAADC_INTENCLR_CH2LIMITH_Msk (0x1UL << SAADC_INTENCLR_CH2LIMITH_Pos) /*!< Bit mask of CH2LIMITH field. */
#define SAADC_INTENCLR_CH2LIMITH_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENCLR_CH2LIMITH_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENCLR_CH2LIMITH_Clear (1UL) /*!< Disable */

/* Bit 9 : Write '1' to Disable interrupt for CH[1].LIMITL event */
#define SAADC_INTENCLR_CH1LIMITL_Pos (9UL) /*!< Position of CH1LIMITL field. */
#define SAADC_INTENCLR_CH1LIMITL_Msk (0x1UL << SAADC_INTENCLR_CH1LIMITL_Pos) /*!< Bit mask of CH1LIMITL field. */
#define SAADC_INTENCLR_CH1LIMITL_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENCLR_CH1LIMITL_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENCLR_CH1LIMITL_Clear (1UL) /*!< Disable */

/* Bit 8 : Write '1' to Disable interrupt for CH[1].LIMITH event */
#define SAADC_INTENCLR_CH1LIMITH_Pos (8UL) /*!< Position of CH1LIMITH field. */
#define SAADC_INTENCLR_CH1LIMITH_Msk (0x1UL << SAADC_INTENCLR_CH1LIMITH_Pos) /*!< Bit mask of CH1LIMITH field. */
#define SAADC_INTENCLR_CH1LIMITH_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENCLR_CH1LIMITH_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENCLR_CH1LIMITH_Clear (1UL) /*!< Disable */

/* Bit 7 : Write '1' to Disable interrupt for CH[0].LIMITL event */
#define SAADC_INTENCLR_CH0LIMITL_Pos (7UL) /*!< Position of CH0LIMITL field. */
#define SAADC_INTENCLR_CH0LIMITL_Msk (0x1UL << SAADC_INTENCLR_CH0LIMITL_Pos) /*!< Bit mask of CH0LIMITL field. */
#define SAADC_INTENCLR_CH0LIMITL_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENCLR_CH0LIMITL_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENCLR_CH0LIMITL_Clear (1UL) /*!< Disable */

/* Bit 6 : Write '1' to Disable interrupt for CH[0].LIMITH event */
#define SAADC_INTENCLR_CH0LIMITH_Pos (6UL) /*!< Position of CH0LIMITH field. */
#define SAADC_INTENCLR_CH0LIMITH_Msk (0x1UL << SAADC_INTENCLR_CH0LIMITH_Pos) /*!< Bit mask of CH0LIMITH field. */
#define SAADC_INTENCLR_CH0LIMITH_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENCLR_CH0LIMITH_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENCLR_CH0LIMITH_Clear (1UL) /*!< Disable */

/* Bit 5 : Write '1' to Disable interrupt for STOPPED event */
#define SAADC_INTENCLR_STOPPED_Pos (5UL) /*!< Position of STOPPED field. */
#define SAADC_INTENCLR_STOPPED_Msk (0x1UL << SAADC_INTENCLR_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define SAADC_INTENCLR_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENCLR_STOPPED_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENCLR_STOPPED_Clear (1UL) /*!< Disable */

/* Bit 4 : Write '1' to Disable interrupt for CALIBRATEDONE event */
#define SAADC_INTENCLR_CALIBRATEDONE_Pos (4UL) /*!< Position of CALIBRATEDONE field. */
#define SAADC_INTENCLR_CALIBRATEDONE_Msk (0x1UL << SAADC_INTENCLR_CALIBRATEDONE_Pos) /*!< Bit mask of CALIBRATEDONE field. */
#define SAADC_INTENCLR_CALIBRATEDONE_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENCLR_CALIBRATEDONE_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENCLR_CALIBRATEDONE_Clear (1UL) /*!< Disable */

/* Bit 3 : Write '1' to Disable interrupt for RESULTDONE event */
#define SAADC_INTENCLR_RESULTDONE_Pos (3UL) /*!< Position of RESULTDONE field. */
#define SAADC_INTENCLR_RESULTDONE_Msk (0x1UL << SAADC_INTENCLR_RESULTDONE_Pos) /*!< Bit mask of RESULTDONE field. */
#define SAADC_INTENCLR_RESULTDONE_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENCLR_RESULTDONE_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENCLR_RESULTDONE_Clear (1UL) /*!< Disable */

/* Bit 2 : Write '1' to Disable interrupt for DONE event */
#define SAADC_INTENCLR_DONE_Pos (2UL) /*!< Position of DONE field. */
#define SAADC_INTENCLR_DONE_Msk (0x1UL << SAADC_INTENCLR_DONE_Pos) /*!< Bit mask of DONE field. */
#define SAADC_INTENCLR_DONE_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENCLR_DONE_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENCLR_DONE_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable interrupt for END event */
#define SAADC_INTENCLR_END_Pos (1UL) /*!< Position of END field. */
#define SAADC_INTENCLR_END_Msk (0x1UL << SAADC_INTENCLR_END_Pos) /*!< Bit mask of END field. */
#define SAADC_INTENCLR_END_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENCLR_END_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENCLR_END_Clear (1UL) /*!< Disable */

/* Bit 0 : Write '1' to Disable interrupt for STARTED event */
#define SAADC_INTENCLR_STARTED_Pos (0UL) /*!< Position of STARTED field. */
#define SAADC_INTENCLR_STARTED_Msk (0x1UL << SAADC_INTENCLR_STARTED_Pos) /*!< Bit mask of STARTED field. */
#define SAADC_INTENCLR_STARTED_Disabled (0UL) /*!< Read: Disabled */
#define SAADC_INTENCLR_STARTED_Enabled (1UL) /*!< Read: Enabled */
#define SAADC_INTENCLR_STARTED_Clear (1UL) /*!< Disable */

/* Register: SAADC_STATUS */
/* Description: Status */

/* Bit 0 : Status */
#define SAADC_STATUS_STATUS_Pos (0UL) /*!< Position of STATUS field. */
#define SAADC_STATUS_STATUS_Msk (0x1UL << SAADC_STATUS_STATUS_Pos) /*!< Bit mask of STATUS field. */
#define SAADC_STATUS_STATUS_Ready (0UL) /*!< ADC is ready. No on-going conversion. */
#define SAADC_STATUS_STATUS_Busy (1UL) /*!< ADC is busy. Conversion in progress. */

/* Register: SAADC_ENABLE */
/* Description: Enable or disable ADC */

/* Bit 0 : Enable or disable ADC */
#define SAADC_ENABLE_ENABLE_Pos (0UL) /*!< Position of ENABLE field. */
#define SAADC_ENABLE_ENABLE_Msk (0x1UL << SAADC_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define SAADC_ENABLE_ENABLE_Disabled (0UL) /*!< Disable ADC */
#define SAADC_ENABLE_ENABLE_Enabled (1UL) /*!< Enable ADC */

/* Register: SAADC_CH_PSELP */
/* Description: Description cluster[0]:  Input positive pin selection for CH[0] */

/* Bits 4..0 : Analog positive input channel */
#define SAADC_CH_PSELP_PSELP_Pos (0UL) /*!< Position of PSELP field. */
#define SAADC_CH_PSELP_PSELP_Msk (0x1FUL << SAADC_CH_PSELP_PSELP_Pos) /*!< Bit mask of PSELP field. */
#define SAADC_CH_PSELP_PSELP_NC (0UL) /*!< Not connected */
#define SAADC_CH_PSELP_PSELP_AnalogInput0 (1UL) /*!< AIN0 */
#define SAADC_CH_PSELP_PSELP_AnalogInput1 (2UL) /*!< AIN1 */
#define SAADC_CH_PSELP_PSELP_AnalogInput2 (3UL) /*!< AIN2 */
#define SAADC_CH_PSELP_PSELP_AnalogInput3 (4UL) /*!< AIN3 */
#define SAADC_CH_PSELP_PSELP_AnalogInput4 (5UL) /*!< AIN4 */
#define SAADC_CH_PSELP_PSELP_AnalogInput5 (6UL) /*!< AIN5 */
#define SAADC_CH_PSELP_PSELP_AnalogInput6 (7UL) /*!< AIN6 */
#define SAADC_CH_PSELP_PSELP_AnalogInput7 (8UL) /*!< AIN7 */
#define SAADC_CH_PSELP_PSELP_VDD (9UL) /*!< VDD */
#define SAADC_CH_PSELP_PSELP_VDDHDIV5 (0x11UL) /*!< VDDH/5 */

/* Register: SAADC_CH_PSELN */
/* Description: Description cluster[0]:  Input negative pin selection for CH[0] */

/* Bits 4..0 : Analog negative input, enables differential channel */
#define SAADC_CH_PSELN_PSELN_Pos (0UL) /*!< Position of PSELN field. */
#define SAADC_CH_PSELN_PSELN_Msk (0x1FUL << SAADC_CH_PSELN_PSELN_Pos) /*!< Bit mask of PSELN field. */
#define SAADC_CH_PSELN_PSELN_NC (0UL) /*!< Not connected */
#define SAADC_CH_PSELN_PSELN_AnalogInput0 (1UL) /*!< AIN0 */
#define SAADC_CH_PSELN_PSELN_AnalogInput1 (2UL) /*!< AIN1 */
#define SAADC_CH_PSELN_PSELN_AnalogInput2 (3UL) /*!< AIN2 */
#define SAADC_CH_PSELN_PSELN_AnalogInput3 (4UL) /*!< AIN3 */
#define SAADC_CH_PSELN_PSELN_AnalogInput4 (5UL) /*!< AIN4 */
#define SAADC_CH_PSELN_PSELN_AnalogInput5 (6UL) /*!< AIN5 */
#define SAADC_CH_PSELN_PSELN_AnalogInput6 (7UL) /*!< AIN6 */
#define SAADC_CH_PSELN_PSELN_AnalogInput7 (8UL) /*!< AIN7 */
#define SAADC_CH_PSELN_PSELN_VDD (9UL) /*!< VDD */
#define SAADC_CH_PSELN_PSELN_VDDHDIV5 (0x11UL) /*!< VDDH/5 */

/* Register: SAADC_CH_CONFIG */
/* Description: Description cluster[0]:  Input configuration for CH[0] */

/* Bit 24 : Enable burst mode */
#define SAADC_CH_CONFIG_BURST_Pos (24UL) /*!< Position of BURST field. */
#define SAADC_CH_CONFIG_BURST_Msk (0x1UL << SAADC_CH_CONFIG_BURST_Pos) /*!< Bit mask of BURST field. */
#define SAADC_CH_CONFIG_BURST_Disabled (0UL) /*!< Burst mode is disabled (normal operation) */
#define SAADC_CH_CONFIG_BURST_Enabled (1UL) /*!< Burst mode is enabled. SAADC takes 2^OVERSAMPLE number of samples as fast as it can, and sends the average to Data RAM. */

/* Bit 20 : Enable differential mode */
#define SAADC_CH_CONFIG_MODE_Pos (20UL) /*!< Position of MODE field. */
#define SAADC_CH_CONFIG_MODE_Msk (0x1UL << SAADC_CH_CONFIG_MODE_Pos) /*!< Bit mask of MODE field. */
#define SAADC_CH_CONFIG_MODE_SE (0UL) /*!< Single ended, PSELN will be ignored, negative input to ADC shorted to GND */
#define SAADC_CH_CONFIG_MODE_Diff (1UL) /*!< Differential */

/* Bits 18..16 : Acquisition time, the time the ADC uses to sample the input voltage */
#define SAADC_CH_CONFIG_TACQ_Pos (16UL) /*!< Position of TACQ field. */
#define SAADC_CH_CONFIG_TACQ_Msk (0x7UL << SAADC_CH_CONFIG_TACQ_Pos) /*!< Bit mask of TACQ field. */
#define SAADC_CH_CONFIG_TACQ_3us (0UL) /*!< 3 us */
#define SAADC_CH_CONFIG_TACQ_5us (1UL) /*!< 5 us */
#define SAADC_CH_CONFIG_TACQ_10us (2UL) /*!< 10 us */
#define SAADC_CH_CONFIG_TACQ_15us (3UL) /*!< 15 us */
#define SAADC_CH_CONFIG_TACQ_20us (4UL) /*!< 20 us */
#define SAADC_CH_CONFIG_TACQ_40us (5UL) /*!< 40 us */

/* Bit 12 : Reference control */
#define SAADC_CH_CONFIG_REFSEL_Pos (12UL) /*!< Position of REFSEL field. */
#define SAADC_CH_CONFIG_REFSEL_Msk (0x1UL << SAADC_CH_CONFIG_REFSEL_Pos) /*!< Bit mask of REFSEL field. */
#define SAADC_CH_CONFIG_REFSEL_Internal (0UL) /*!< Internal reference (0.6 V) */
#define SAADC_CH_CONFIG_REFSEL_VDD1_4 (1UL) /*!< VDD/4 as reference */

/* Bits 10..8 : Gain control */
#define SAADC_CH_CONFIG_GAIN_Pos (8UL) /*!< Position of GAIN field. */
#define SAADC_CH_CONFIG_GAIN_Msk (0x7UL << SAADC_CH_CONFIG_GAIN_Pos) /*!< Bit mask of GAIN field. */
#define SAADC_CH_CONFIG_GAIN_Gain1_6 (0UL) /*!< 1/6 */
#define SAADC_CH_CONFIG_GAIN_Gain1_5 (1UL) /*!< 1/5 */
#define SAADC_CH_CONFIG_GAIN_Gain1_4 (2UL) /*!< 1/4 */
#define SAADC_CH_CONFIG_GAIN_Gain1_3 (3UL) /*!< 1/3 */
#define SAADC_CH_CONFIG_GAIN_Gain1_2 (4UL) /*!< 1/2 */
#define SAADC_CH_CONFIG_GAIN_Gain1 (5UL) /*!< 1 */
#define SAADC_CH_CONFIG_GAIN_Gain2 (6UL) /*!< 2 */
#define SAADC_CH_CONFIG_GAIN_Gain4 (7UL) /*!< 4 */

/* Bits 5..4 : Negative channel resistor control */
#define SAADC_CH_CONFIG_RESN_Pos (4UL) /*!< Position of RESN field. */
#define SAADC_CH_CONFIG_RESN_Msk (0x3UL << SAADC_CH_CONFIG_RESN_Pos) /*!< Bit mask of RESN field. */
#define SAADC_CH_CONFIG_RESN_Bypass (0UL) /*!< Bypass resistor ladder */
#define SAADC_CH_CONFIG_RESN_Pulldown (1UL) /*!< Pull-down to GND */
#define SAADC_CH_CONFIG_RESN_Pullup (2UL) /*!< Pull-up to VDD */
#define SAADC_CH_CONFIG_RESN_VDD1_2 (3UL) /*!< Set input at VDD/2 */

/* Bits 1..0 : Positive channel resistor control */
#define SAADC_CH_CONFIG_RESP_Pos (0UL) /*!< Position of RESP field. */
#define SAADC_CH_CONFIG_RESP_Msk (0x3UL << SAADC_CH_CONFIG_RESP_Pos) /*!< Bit mask of RESP field. */
#define SAADC_CH_CONFIG_RESP_Bypass (0UL) /*!< Bypass resistor ladder */
#define SAADC_CH_CONFIG_RESP_Pulldown (1UL) /*!< Pull-down to GND */
#define SAADC_CH_CONFIG_RESP_Pullup (2UL) /*!< Pull-up to VDD */
#define SAADC_CH_CONFIG_RESP_VDD1_2 (3UL) /*!< Set input at VDD/2 */

/* Register: SAADC_CH_LIMIT */
/* Description: Description cluster[0]:  High/low limits for event monitoring a channel */

/* Bits 31..16 : High level limit */
#define SAADC_CH_LIMIT_HIGH_Pos (16UL) /*!< Position of HIGH field. */
#define SAADC_CH_LIMIT_HIGH_Msk (0xFFFFUL << SAADC_CH_LIMIT_HIGH_Pos) /*!< Bit mask of HIGH field. */

/* Bits 15..0 : Low level limit */
#define SAADC_CH_LIMIT_LOW_Pos (0UL) /*!< Position of LOW field. */
#define SAADC_CH_LIMIT_LOW_Msk (0xFFFFUL << SAADC_CH_LIMIT_LOW_Pos) /*!< Bit mask of LOW field. */

/* Register: SAADC_RESOLUTION */
/* Description: Resolution configuration */

/* Bits 2..0 : Set the resolution */
#define SAADC_RESOLUTION_VAL_Pos (0UL) /*!< Position of VAL field. */
#define SAADC_RESOLUTION_VAL_Msk (0x7UL << SAADC_RESOLUTION_VAL_Pos) /*!< Bit mask of VAL field. */
#define SAADC_RESOLUTION_VAL_8bit (0UL) /*!< 8 bit */
#define SAADC_RESOLUTION_VAL_10bit (1UL) /*!< 10 bit */
#define SAADC_RESOLUTION_VAL_12bit (2UL) /*!< 12 bit */
#define SAADC_RESOLUTION_VAL_14bit (3UL) /*!< 14 bit */

/* Register: SAADC_OVERSAMPLE */
/* Description: Oversampling configuration. OVERSAMPLE should not be combined with SCAN. The RESOLUTION is applied before averaging, thus for high OVERSAMPLE a higher RESOLUTION should be used. */

/* Bits 3..0 : Oversample control */
#define SAADC_OVERSAMPLE_OVERSAMPLE_Pos (0UL) /*!< Position of OVERSAMPLE field. */
#define SAADC_OVERSAMPLE_OVERSAMPLE_Msk (0xFUL << SAADC_OVERSAMPLE_OVERSAMPLE_Pos) /*!< Bit mask of OVERSAMPLE field. */
#define SAADC_OVERSAMPLE_OVERSAMPLE_Bypass (0UL) /*!< Bypass oversampling */
#define SAADC_OVERSAMPLE_OVERSAMPLE_Over2x (1UL) /*!< Oversample 2x */
#define SAADC_OVERSAMPLE_OVERSAMPLE_Over4x (2UL) /*!< Oversample 4x */
#define SAADC_OVERSAMPLE_OVERSAMPLE_Over8x (3UL) /*!< Oversample 8x */
#define SAADC_OVERSAMPLE_OVERSAMPLE_Over16x (4UL) /*!< Oversample 16x */
#define SAADC_OVERSAMPLE_OVERSAMPLE_Over32x (5UL) /*!< Oversample 32x */
#define SAADC_OVERSAMPLE_OVERSAMPLE_Over64x (6UL) /*!< Oversample 64x */
#define SAADC_OVERSAMPLE_OVERSAMPLE_Over128x (7UL) /*!< Oversample 128x */
#define SAADC_OVERSAMPLE_OVERSAMPLE_Over256x (8UL) /*!< Oversample 256x */

/* Register: SAADC_SAMPLERATE */
/* Description: Controls normal or continuous sample rate */

/* Bit 12 : Select mode for sample rate control */
#define SAADC_SAMPLERATE_MODE_Pos (12UL) /*!< Position of MODE field. */
#define SAADC_SAMPLERATE_MODE_Msk (0x1UL << SAADC_SAMPLERATE_MODE_Pos) /*!< Bit mask of MODE field. */
#define SAADC_SAMPLERATE_MODE_Task (0UL) /*!< Rate is controlled from SAMPLE task */
#define SAADC_SAMPLERATE_MODE_Timers (1UL) /*!< Rate is controlled from local timer (use CC to control the rate) */

/* Bits 10..0 : Capture and compare value. Sample rate is 16 MHz/CC */
#define SAADC_SAMPLERATE_CC_Pos (0UL) /*!< Position of CC field. */
#define SAADC_SAMPLERATE_CC_Msk (0x7FFUL << SAADC_SAMPLERATE_CC_Pos) /*!< Bit mask of CC field. */

/* Register: SAADC_RESULT_PTR */
/* Description: Data pointer */

/* Bits 31..0 : Data pointer */
#define SAADC_RESULT_PTR_PTR_Pos (0UL) /*!< Position of PTR field. */
#define SAADC_RESULT_PTR_PTR_Msk (0xFFFFFFFFUL << SAADC_RESULT_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: SAADC_RESULT_MAXCNT */
/* Description: Maximum number of buffer words to transfer */

/* Bits 14..0 : Maximum number of buffer words to transfer */
#define SAADC_RESULT_MAXCNT_MAXCNT_Pos (0UL) /*!< Position of MAXCNT field. */
#define SAADC_RESULT_MAXCNT_MAXCNT_Msk (0x7FFFUL << SAADC_RESULT_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: SAADC_RESULT_AMOUNT */
/* Description: Number of buffer words transferred since last START */

/* Bits 14..0 : Number of buffer words transferred since last START. This register can be read after an END or STOPPED event. */
#define SAADC_RESULT_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define SAADC_RESULT_AMOUNT_AMOUNT_Msk (0x7FFFUL << SAADC_RESULT_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */


/* Peripheral: SPI */
/* Description: Serial Peripheral Interface 0 */

/* Register: SPI_INTENSET */
/* Description: Enable interrupt */

/* Bit 2 : Write '1' to Enable interrupt for READY event */
#define SPI_INTENSET_READY_Pos (2UL) /*!< Position of READY field. */
#define SPI_INTENSET_READY_Msk (0x1UL << SPI_INTENSET_READY_Pos) /*!< Bit mask of READY field. */
#define SPI_INTENSET_READY_Disabled (0UL) /*!< Read: Disabled */
#define SPI_INTENSET_READY_Enabled (1UL) /*!< Read: Enabled */
#define SPI_INTENSET_READY_Set (1UL) /*!< Enable */

/* Register: SPI_INTENCLR */
/* Description: Disable interrupt */

/* Bit 2 : Write '1' to Disable interrupt for READY event */
#define SPI_INTENCLR_READY_Pos (2UL) /*!< Position of READY field. */
#define SPI_INTENCLR_READY_Msk (0x1UL << SPI_INTENCLR_READY_Pos) /*!< Bit mask of READY field. */
#define SPI_INTENCLR_READY_Disabled (0UL) /*!< Read: Disabled */
#define SPI_INTENCLR_READY_Enabled (1UL) /*!< Read: Enabled */
#define SPI_INTENCLR_READY_Clear (1UL) /*!< Disable */

/* Register: SPI_ENABLE */
/* Description: Enable SPI */

/* Bits 3..0 : Enable or disable SPI */
#define SPI_ENABLE_ENABLE_Pos (0UL) /*!< Position of ENABLE field. */
#define SPI_ENABLE_ENABLE_Msk (0xFUL << SPI_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define SPI_ENABLE_ENABLE_Disabled (0UL) /*!< Disable SPI */
#define SPI_ENABLE_ENABLE_Enabled (1UL) /*!< Enable SPI */

/* Register: SPI_PSEL_SCK */
/* Description: Pin select for SCK */

/* Bit 31 : Connection */
#define SPI_PSEL_SCK_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define SPI_PSEL_SCK_CONNECT_Msk (0x1UL << SPI_PSEL_SCK_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define SPI_PSEL_SCK_CONNECT_Connected (0UL) /*!< Connect */
#define SPI_PSEL_SCK_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define SPI_PSEL_SCK_PORT_Pos (5UL) /*!< Position of PORT field. */
#define SPI_PSEL_SCK_PORT_Msk (0x3UL << SPI_PSEL_SCK_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define SPI_PSEL_SCK_PIN_Pos (0UL) /*!< Position of PIN field. */
#define SPI_PSEL_SCK_PIN_Msk (0x1FUL << SPI_PSEL_SCK_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: SPI_PSEL_MOSI */
/* Description: Pin select for MOSI signal */

/* Bit 31 : Connection */
#define SPI_PSEL_MOSI_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define SPI_PSEL_MOSI_CONNECT_Msk (0x1UL << SPI_PSEL_MOSI_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define SPI_PSEL_MOSI_CONNECT_Connected (0UL) /*!< Connect */
#define SPI_PSEL_MOSI_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define SPI_PSEL_MOSI_PORT_Pos (5UL) /*!< Position of PORT field. */
#define SPI_PSEL_MOSI_PORT_Msk (0x3UL << SPI_PSEL_MOSI_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define SPI_PSEL_MOSI_PIN_Pos (0UL) /*!< Position of PIN field. */
#define SPI_PSEL_MOSI_PIN_Msk (0x1FUL << SPI_PSEL_MOSI_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: SPI_PSEL_MISO */
/* Description: Pin select for MISO signal */

/* Bit 31 : Connection */
#define SPI_PSEL_MISO_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define SPI_PSEL_MISO_CONNECT_Msk (0x1UL << SPI_PSEL_MISO_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define SPI_PSEL_MISO_CONNECT_Connected (0UL) /*!< Connect */
#define SPI_PSEL_MISO_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define SPI_PSEL_MISO_PORT_Pos (5UL) /*!< Position of PORT field. */
#define SPI_PSEL_MISO_PORT_Msk (0x3UL << SPI_PSEL_MISO_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define SPI_PSEL_MISO_PIN_Pos (0UL) /*!< Position of PIN field. */
#define SPI_PSEL_MISO_PIN_Msk (0x1FUL << SPI_PSEL_MISO_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: SPI_RXD */
/* Description: RXD register */

/* Bits 7..0 : RX data received. Double buffered */
#define SPI_RXD_RXD_Pos (0UL) /*!< Position of RXD field. */
#define SPI_RXD_RXD_Msk (0xFFUL << SPI_RXD_RXD_Pos) /*!< Bit mask of RXD field. */

/* Register: SPI_TXD */
/* Description: TXD register */

/* Bits 7..0 : TX data to send. Double buffered */
#define SPI_TXD_TXD_Pos (0UL) /*!< Position of TXD field. */
#define SPI_TXD_TXD_Msk (0xFFUL << SPI_TXD_TXD_Pos) /*!< Bit mask of TXD field. */

/* Register: SPI_FREQUENCY */
/* Description: SPI frequency. Accuracy depends on the HFCLK source selected. */

/* Bits 31..0 : SPI master data rate */
#define SPI_FREQUENCY_FREQUENCY_Pos (0UL) /*!< Position of FREQUENCY field. */
#define SPI_FREQUENCY_FREQUENCY_Msk (0xFFFFFFFFUL << SPI_FREQUENCY_FREQUENCY_Pos) /*!< Bit mask of FREQUENCY field. */
#define SPI_FREQUENCY_FREQUENCY_K125 (0x02000000UL) /*!< 125 kbps */
#define SPI_FREQUENCY_FREQUENCY_K250 (0x04000000UL) /*!< 250 kbps */
#define SPI_FREQUENCY_FREQUENCY_K500 (0x08000000UL) /*!< 500 kbps */
#define SPI_FREQUENCY_FREQUENCY_M1 (0x10000000UL) /*!< 1 Mbps */
#define SPI_FREQUENCY_FREQUENCY_M2 (0x20000000UL) /*!< 2 Mbps */
#define SPI_FREQUENCY_FREQUENCY_M4 (0x40000000UL) /*!< 4 Mbps */
#define SPI_FREQUENCY_FREQUENCY_M8 (0x80000000UL) /*!< 8 Mbps */

/* Register: SPI_CONFIG */
/* Description: Configuration register */

/* Bit 2 : Serial clock (SCK) polarity */
#define SPI_CONFIG_CPOL_Pos (2UL) /*!< Position of CPOL field. */
#define SPI_CONFIG_CPOL_Msk (0x1UL << SPI_CONFIG_CPOL_Pos) /*!< Bit mask of CPOL field. */
#define SPI_CONFIG_CPOL_ActiveHigh (0UL) /*!< Active high */
#define SPI_CONFIG_CPOL_ActiveLow (1UL) /*!< Active low */

/* Bit 1 : Serial clock (SCK) phase */
#define SPI_CONFIG_CPHA_Pos (1UL) /*!< Position of CPHA field. */
#define SPI_CONFIG_CPHA_Msk (0x1UL << SPI_CONFIG_CPHA_Pos) /*!< Bit mask of CPHA field. */
#define SPI_CONFIG_CPHA_Leading (0UL) /*!< Sample on leading edge of clock, shift serial data on trailing edge */
#define SPI_CONFIG_CPHA_Trailing (1UL) /*!< Sample on trailing edge of clock, shift serial data on leading edge */

/* Bit 0 : Bit order */
#define SPI_CONFIG_ORDER_Pos (0UL) /*!< Position of ORDER field. */
#define SPI_CONFIG_ORDER_Msk (0x1UL << SPI_CONFIG_ORDER_Pos) /*!< Bit mask of ORDER field. */
#define SPI_CONFIG_ORDER_MsbFirst (0UL) /*!< Most significant bit shifted out first */
#define SPI_CONFIG_ORDER_LsbFirst (1UL) /*!< Least significant bit shifted out first */


/* Peripheral: SPIM */
/* Description: Serial Peripheral Interface Master with EasyDMA 0 */

/* Register: SPIM_SHORTS */
/* Description: Shortcut register */

/* Bit 17 : Shortcut between END event and START task */
#define SPIM_SHORTS_END_START_Pos (17UL) /*!< Position of END_START field. */
#define SPIM_SHORTS_END_START_Msk (0x1UL << SPIM_SHORTS_END_START_Pos) /*!< Bit mask of END_START field. */
#define SPIM_SHORTS_END_START_Disabled (0UL) /*!< Disable shortcut */
#define SPIM_SHORTS_END_START_Enabled (1UL) /*!< Enable shortcut */

/* Register: SPIM_INTENSET */
/* Description: Enable interrupt */

/* Bit 19 : Write '1' to Enable interrupt for STARTED event */
#define SPIM_INTENSET_STARTED_Pos (19UL) /*!< Position of STARTED field. */
#define SPIM_INTENSET_STARTED_Msk (0x1UL << SPIM_INTENSET_STARTED_Pos) /*!< Bit mask of STARTED field. */
#define SPIM_INTENSET_STARTED_Disabled (0UL) /*!< Read: Disabled */
#define SPIM_INTENSET_STARTED_Enabled (1UL) /*!< Read: Enabled */
#define SPIM_INTENSET_STARTED_Set (1UL) /*!< Enable */

/* Bit 8 : Write '1' to Enable interrupt for ENDTX event */
#define SPIM_INTENSET_ENDTX_Pos (8UL) /*!< Position of ENDTX field. */
#define SPIM_INTENSET_ENDTX_Msk (0x1UL << SPIM_INTENSET_ENDTX_Pos) /*!< Bit mask of ENDTX field. */
#define SPIM_INTENSET_ENDTX_Disabled (0UL) /*!< Read: Disabled */
#define SPIM_INTENSET_ENDTX_Enabled (1UL) /*!< Read: Enabled */
#define SPIM_INTENSET_ENDTX_Set (1UL) /*!< Enable */

/* Bit 6 : Write '1' to Enable interrupt for END event */
#define SPIM_INTENSET_END_Pos (6UL) /*!< Position of END field. */
#define SPIM_INTENSET_END_Msk (0x1UL << SPIM_INTENSET_END_Pos) /*!< Bit mask of END field. */
#define SPIM_INTENSET_END_Disabled (0UL) /*!< Read: Disabled */
#define SPIM_INTENSET_END_Enabled (1UL) /*!< Read: Enabled */
#define SPIM_INTENSET_END_Set (1UL) /*!< Enable */

/* Bit 4 : Write '1' to Enable interrupt for ENDRX event */
#define SPIM_INTENSET_ENDRX_Pos (4UL) /*!< Position of ENDRX field. */
#define SPIM_INTENSET_ENDRX_Msk (0x1UL << SPIM_INTENSET_ENDRX_Pos) /*!< Bit mask of ENDRX field. */
#define SPIM_INTENSET_ENDRX_Disabled (0UL) /*!< Read: Disabled */
#define SPIM_INTENSET_ENDRX_Enabled (1UL) /*!< Read: Enabled */
#define SPIM_INTENSET_ENDRX_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable interrupt for STOPPED event */
#define SPIM_INTENSET_STOPPED_Pos (1UL) /*!< Position of STOPPED field. */
#define SPIM_INTENSET_STOPPED_Msk (0x1UL << SPIM_INTENSET_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define SPIM_INTENSET_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define SPIM_INTENSET_STOPPED_Enabled (1UL) /*!< Read: Enabled */
#define SPIM_INTENSET_STOPPED_Set (1UL) /*!< Enable */

/* Register: SPIM_INTENCLR */
/* Description: Disable interrupt */

/* Bit 19 : Write '1' to Disable interrupt for STARTED event */
#define SPIM_INTENCLR_STARTED_Pos (19UL) /*!< Position of STARTED field. */
#define SPIM_INTENCLR_STARTED_Msk (0x1UL << SPIM_INTENCLR_STARTED_Pos) /*!< Bit mask of STARTED field. */
#define SPIM_INTENCLR_STARTED_Disabled (0UL) /*!< Read: Disabled */
#define SPIM_INTENCLR_STARTED_Enabled (1UL) /*!< Read: Enabled */
#define SPIM_INTENCLR_STARTED_Clear (1UL) /*!< Disable */

/* Bit 8 : Write '1' to Disable interrupt for ENDTX event */
#define SPIM_INTENCLR_ENDTX_Pos (8UL) /*!< Position of ENDTX field. */
#define SPIM_INTENCLR_ENDTX_Msk (0x1UL << SPIM_INTENCLR_ENDTX_Pos) /*!< Bit mask of ENDTX field. */
#define SPIM_INTENCLR_ENDTX_Disabled (0UL) /*!< Read: Disabled */
#define SPIM_INTENCLR_ENDTX_Enabled (1UL) /*!< Read: Enabled */
#define SPIM_INTENCLR_ENDTX_Clear (1UL) /*!< Disable */

/* Bit 6 : Write '1' to Disable interrupt for END event */
#define SPIM_INTENCLR_END_Pos (6UL) /*!< Position of END field. */
#define SPIM_INTENCLR_END_Msk (0x1UL << SPIM_INTENCLR_END_Pos) /*!< Bit mask of END field. */
#define SPIM_INTENCLR_END_Disabled (0UL) /*!< Read: Disabled */
#define SPIM_INTENCLR_END_Enabled (1UL) /*!< Read: Enabled */
#define SPIM_INTENCLR_END_Clear (1UL) /*!< Disable */

/* Bit 4 : Write '1' to Disable interrupt for ENDRX event */
#define SPIM_INTENCLR_ENDRX_Pos (4UL) /*!< Position of ENDRX field. */
#define SPIM_INTENCLR_ENDRX_Msk (0x1UL << SPIM_INTENCLR_ENDRX_Pos) /*!< Bit mask of ENDRX field. */
#define SPIM_INTENCLR_ENDRX_Disabled (0UL) /*!< Read: Disabled */
#define SPIM_INTENCLR_ENDRX_Enabled (1UL) /*!< Read: Enabled */
#define SPIM_INTENCLR_ENDRX_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable interrupt for STOPPED event */
#define SPIM_INTENCLR_STOPPED_Pos (1UL) /*!< Position of STOPPED field. */
#define SPIM_INTENCLR_STOPPED_Msk (0x1UL << SPIM_INTENCLR_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define SPIM_INTENCLR_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define SPIM_INTENCLR_STOPPED_Enabled (1UL) /*!< Read: Enabled */
#define SPIM_INTENCLR_STOPPED_Clear (1UL) /*!< Disable */

/* Register: SPIM_STALLSTAT */
/* Description: Stall status for EasyDMA RAM accesses. The fields in this register is set to STALL by hardware whenever a stall occurres and can be cleared (set to NOSTALL) by the CPU. */

/* Bit 1 : Stall status for EasyDMA RAM writes */
#define SPIM_STALLSTAT_RX_Pos (1UL) /*!< Position of RX field. */
#define SPIM_STALLSTAT_RX_Msk (0x1UL << SPIM_STALLSTAT_RX_Pos) /*!< Bit mask of RX field. */
#define SPIM_STALLSTAT_RX_NOSTALL (0UL) /*!< No stall */
#define SPIM_STALLSTAT_RX_STALL (1UL) /*!< A stall has occurred */

/* Bit 0 : Stall status for EasyDMA RAM reads */
#define SPIM_STALLSTAT_TX_Pos (0UL) /*!< Position of TX field. */
#define SPIM_STALLSTAT_TX_Msk (0x1UL << SPIM_STALLSTAT_TX_Pos) /*!< Bit mask of TX field. */
#define SPIM_STALLSTAT_TX_NOSTALL (0UL) /*!< No stall */
#define SPIM_STALLSTAT_TX_STALL (1UL) /*!< A stall has occurred */

/* Register: SPIM_ENABLE */
/* Description: Enable SPIM */

/* Bits 3..0 : Enable or disable SPIM */
#define SPIM_ENABLE_ENABLE_Pos (0UL) /*!< Position of ENABLE field. */
#define SPIM_ENABLE_ENABLE_Msk (0xFUL << SPIM_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define SPIM_ENABLE_ENABLE_Disabled (0UL) /*!< Disable SPIM */
#define SPIM_ENABLE_ENABLE_Enabled (7UL) /*!< Enable SPIM */

/* Register: SPIM_PSEL_SCK */
/* Description: Pin select for SCK */

/* Bit 31 : Connection */
#define SPIM_PSEL_SCK_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define SPIM_PSEL_SCK_CONNECT_Msk (0x1UL << SPIM_PSEL_SCK_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define SPIM_PSEL_SCK_CONNECT_Connected (0UL) /*!< Connect */
#define SPIM_PSEL_SCK_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define SPIM_PSEL_SCK_PORT_Pos (5UL) /*!< Position of PORT field. */
#define SPIM_PSEL_SCK_PORT_Msk (0x3UL << SPIM_PSEL_SCK_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define SPIM_PSEL_SCK_PIN_Pos (0UL) /*!< Position of PIN field. */
#define SPIM_PSEL_SCK_PIN_Msk (0x1FUL << SPIM_PSEL_SCK_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: SPIM_PSEL_MOSI */
/* Description: Pin select for MOSI signal */

/* Bit 31 : Connection */
#define SPIM_PSEL_MOSI_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define SPIM_PSEL_MOSI_CONNECT_Msk (0x1UL << SPIM_PSEL_MOSI_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define SPIM_PSEL_MOSI_CONNECT_Connected (0UL) /*!< Connect */
#define SPIM_PSEL_MOSI_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define SPIM_PSEL_MOSI_PORT_Pos (5UL) /*!< Position of PORT field. */
#define SPIM_PSEL_MOSI_PORT_Msk (0x3UL << SPIM_PSEL_MOSI_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define SPIM_PSEL_MOSI_PIN_Pos (0UL) /*!< Position of PIN field. */
#define SPIM_PSEL_MOSI_PIN_Msk (0x1FUL << SPIM_PSEL_MOSI_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: SPIM_PSEL_MISO */
/* Description: Pin select for MISO signal */

/* Bit 31 : Connection */
#define SPIM_PSEL_MISO_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define SPIM_PSEL_MISO_CONNECT_Msk (0x1UL << SPIM_PSEL_MISO_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define SPIM_PSEL_MISO_CONNECT_Connected (0UL) /*!< Connect */
#define SPIM_PSEL_MISO_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define SPIM_PSEL_MISO_PORT_Pos (5UL) /*!< Position of PORT field. */
#define SPIM_PSEL_MISO_PORT_Msk (0x3UL << SPIM_PSEL_MISO_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define SPIM_PSEL_MISO_PIN_Pos (0UL) /*!< Position of PIN field. */
#define SPIM_PSEL_MISO_PIN_Msk (0x1FUL << SPIM_PSEL_MISO_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: SPIM_PSEL_CSN */
/* Description: Pin select for CSN */

/* Bit 31 : Connection */
#define SPIM_PSEL_CSN_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define SPIM_PSEL_CSN_CONNECT_Msk (0x1UL << SPIM_PSEL_CSN_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define SPIM_PSEL_CSN_CONNECT_Connected (0UL) /*!< Connect */
#define SPIM_PSEL_CSN_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define SPIM_PSEL_CSN_PORT_Pos (5UL) /*!< Position of PORT field. */
#define SPIM_PSEL_CSN_PORT_Msk (0x3UL << SPIM_PSEL_CSN_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define SPIM_PSEL_CSN_PIN_Pos (0UL) /*!< Position of PIN field. */
#define SPIM_PSEL_CSN_PIN_Msk (0x1FUL << SPIM_PSEL_CSN_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: SPIM_FREQUENCY */
/* Description: SPI frequency. Accuracy depends on the HFCLK source selected. */

/* Bits 31..0 : SPI master data rate */
#define SPIM_FREQUENCY_FREQUENCY_Pos (0UL) /*!< Position of FREQUENCY field. */
#define SPIM_FREQUENCY_FREQUENCY_Msk (0xFFFFFFFFUL << SPIM_FREQUENCY_FREQUENCY_Pos) /*!< Bit mask of FREQUENCY field. */
#define SPIM_FREQUENCY_FREQUENCY_K125 (0x02000000UL) /*!< 125 kbps */
#define SPIM_FREQUENCY_FREQUENCY_K250 (0x04000000UL) /*!< 250 kbps */
#define SPIM_FREQUENCY_FREQUENCY_K500 (0x08000000UL) /*!< 500 kbps */
#define SPIM_FREQUENCY_FREQUENCY_M16 (0x0A000000UL) /*!< 16 Mbps */
#define SPIM_FREQUENCY_FREQUENCY_M1 (0x10000000UL) /*!< 1 Mbps */
#define SPIM_FREQUENCY_FREQUENCY_M32 (0x14000000UL) /*!< 32 Mbps */
#define SPIM_FREQUENCY_FREQUENCY_M2 (0x20000000UL) /*!< 2 Mbps */
#define SPIM_FREQUENCY_FREQUENCY_M4 (0x40000000UL) /*!< 4 Mbps */
#define SPIM_FREQUENCY_FREQUENCY_M8 (0x80000000UL) /*!< 8 Mbps */

/* Register: SPIM_RXD_PTR */
/* Description: Data pointer */

/* Bits 31..0 : Data pointer */
#define SPIM_RXD_PTR_PTR_Pos (0UL) /*!< Position of PTR field. */
#define SPIM_RXD_PTR_PTR_Msk (0xFFFFFFFFUL << SPIM_RXD_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: SPIM_RXD_MAXCNT */
/* Description: Maximum number of bytes in receive buffer */

/* Bits 15..0 : Maximum number of bytes in receive buffer */
#define SPIM_RXD_MAXCNT_MAXCNT_Pos (0UL) /*!< Position of MAXCNT field. */
#define SPIM_RXD_MAXCNT_MAXCNT_Msk (0xFFFFUL << SPIM_RXD_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: SPIM_RXD_AMOUNT */
/* Description: Number of bytes transferred in the last transaction */

/* Bits 15..0 : Number of bytes transferred in the last transaction */
#define SPIM_RXD_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define SPIM_RXD_AMOUNT_AMOUNT_Msk (0xFFFFUL << SPIM_RXD_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: SPIM_RXD_LIST */
/* Description: EasyDMA list type */

/* Bits 1..0 : List type */
#define SPIM_RXD_LIST_LIST_Pos (0UL) /*!< Position of LIST field. */
#define SPIM_RXD_LIST_LIST_Msk (0x3UL << SPIM_RXD_LIST_LIST_Pos) /*!< Bit mask of LIST field. */
#define SPIM_RXD_LIST_LIST_Disabled (0UL) /*!< Disable EasyDMA list */
#define SPIM_RXD_LIST_LIST_ArrayList (1UL) /*!< Use array list */

/* Register: SPIM_TXD_PTR */
/* Description: Data pointer */

/* Bits 31..0 : Data pointer */
#define SPIM_TXD_PTR_PTR_Pos (0UL) /*!< Position of PTR field. */
#define SPIM_TXD_PTR_PTR_Msk (0xFFFFFFFFUL << SPIM_TXD_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: SPIM_TXD_MAXCNT */
/* Description: Number of bytes in transmit buffer */

/* Bits 15..0 : Maximum number of bytes in transmit buffer */
#define SPIM_TXD_MAXCNT_MAXCNT_Pos (0UL) /*!< Position of MAXCNT field. */
#define SPIM_TXD_MAXCNT_MAXCNT_Msk (0xFFFFUL << SPIM_TXD_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: SPIM_TXD_AMOUNT */
/* Description: Number of bytes transferred in the last transaction */

/* Bits 15..0 : Number of bytes transferred in the last transaction */
#define SPIM_TXD_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define SPIM_TXD_AMOUNT_AMOUNT_Msk (0xFFFFUL << SPIM_TXD_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: SPIM_TXD_LIST */
/* Description: EasyDMA list type */

/* Bits 1..0 : List type */
#define SPIM_TXD_LIST_LIST_Pos (0UL) /*!< Position of LIST field. */
#define SPIM_TXD_LIST_LIST_Msk (0x3UL << SPIM_TXD_LIST_LIST_Pos) /*!< Bit mask of LIST field. */
#define SPIM_TXD_LIST_LIST_Disabled (0UL) /*!< Disable EasyDMA list */
#define SPIM_TXD_LIST_LIST_ArrayList (1UL) /*!< Use array list */

/* Register: SPIM_CONFIG */
/* Description: Configuration register */

/* Bit 2 : Serial clock (SCK) polarity */
#define SPIM_CONFIG_CPOL_Pos (2UL) /*!< Position of CPOL field. */
#define SPIM_CONFIG_CPOL_Msk (0x1UL << SPIM_CONFIG_CPOL_Pos) /*!< Bit mask of CPOL field. */
#define SPIM_CONFIG_CPOL_ActiveHigh (0UL) /*!< Active high */
#define SPIM_CONFIG_CPOL_ActiveLow (1UL) /*!< Active low */

/* Bit 1 : Serial clock (SCK) phase */
#define SPIM_CONFIG_CPHA_Pos (1UL) /*!< Position of CPHA field. */
#define SPIM_CONFIG_CPHA_Msk (0x1UL << SPIM_CONFIG_CPHA_Pos) /*!< Bit mask of CPHA field. */
#define SPIM_CONFIG_CPHA_Leading (0UL) /*!< Sample on leading edge of clock, shift serial data on trailing edge */
#define SPIM_CONFIG_CPHA_Trailing (1UL) /*!< Sample on trailing edge of clock, shift serial data on leading edge */

/* Bit 0 : Bit order */
#define SPIM_CONFIG_ORDER_Pos (0UL) /*!< Position of ORDER field. */
#define SPIM_CONFIG_ORDER_Msk (0x1UL << SPIM_CONFIG_ORDER_Pos) /*!< Bit mask of ORDER field. */
#define SPIM_CONFIG_ORDER_MsbFirst (0UL) /*!< Most significant bit shifted out first */
#define SPIM_CONFIG_ORDER_LsbFirst (1UL) /*!< Least significant bit shifted out first */

/* Register: SPIM_IFTIMING_RXDELAY */
/* Description: Sample delay for input serial data on MISO */

/* Bits 2..0 : Sample delay for input serial data on MISO. The value specifies the number of 64 MHz clock cycles (15.625 ns) delay from the the sampling edge of SCK (leading edge for CONFIG.CPHA = 0, trailing edge for CONFIG.CPHA = 1) until the input serial data is sampled. As en example, if RXDELAY = 0 and CONFIG.CPHA = 0, the input serial data is sampled on the rising edge of SCK. */
#define SPIM_IFTIMING_RXDELAY_RXDELAY_Pos (0UL) /*!< Position of RXDELAY field. */
#define SPIM_IFTIMING_RXDELAY_RXDELAY_Msk (0x7UL << SPIM_IFTIMING_RXDELAY_RXDELAY_Pos) /*!< Bit mask of RXDELAY field. */

/* Register: SPIM_IFTIMING_CSNDUR */
/* Description: Minimum duration between edge of CSN and edge of SCK and minimum duration CSN must stay high between transactions */

/* Bits 7..0 : Minimum duration between edge of CSN and edge of SCK and minimum duration CSN must stay high between transactions. The value is specified in number of 64 MHz clock cycles (15.625 ns). */
#define SPIM_IFTIMING_CSNDUR_CSNDUR_Pos (0UL) /*!< Position of CSNDUR field. */
#define SPIM_IFTIMING_CSNDUR_CSNDUR_Msk (0xFFUL << SPIM_IFTIMING_CSNDUR_CSNDUR_Pos) /*!< Bit mask of CSNDUR field. */

/* Register: SPIM_ORC */
/* Description: Byte transmitted after TXD.MAXCNT bytes have been transmitted in the case when RXD.MAXCNT is greater than TXD.MAXCNT */

/* Bits 7..0 : Byte transmitted after TXD.MAXCNT bytes have been transmitted in the case when RXD.MAXCNT is greater than TXD.MAXCNT. */
#define SPIM_ORC_ORC_Pos (0UL) /*!< Position of ORC field. */
#define SPIM_ORC_ORC_Msk (0xFFUL << SPIM_ORC_ORC_Pos) /*!< Bit mask of ORC field. */


/* Peripheral: SPIS */
/* Description: SPI Slave 0 */

/* Register: SPIS_SHORTS */
/* Description: Shortcut register */

/* Bit 2 : Shortcut between END event and ACQUIRE task */
#define SPIS_SHORTS_END_ACQUIRE_Pos (2UL) /*!< Position of END_ACQUIRE field. */
#define SPIS_SHORTS_END_ACQUIRE_Msk (0x1UL << SPIS_SHORTS_END_ACQUIRE_Pos) /*!< Bit mask of END_ACQUIRE field. */
#define SPIS_SHORTS_END_ACQUIRE_Disabled (0UL) /*!< Disable shortcut */
#define SPIS_SHORTS_END_ACQUIRE_Enabled (1UL) /*!< Enable shortcut */

/* Register: SPIS_INTENSET */
/* Description: Enable interrupt */

/* Bit 10 : Write '1' to Enable interrupt for ACQUIRED event */
#define SPIS_INTENSET_ACQUIRED_Pos (10UL) /*!< Position of ACQUIRED field. */
#define SPIS_INTENSET_ACQUIRED_Msk (0x1UL << SPIS_INTENSET_ACQUIRED_Pos) /*!< Bit mask of ACQUIRED field. */
#define SPIS_INTENSET_ACQUIRED_Disabled (0UL) /*!< Read: Disabled */
#define SPIS_INTENSET_ACQUIRED_Enabled (1UL) /*!< Read: Enabled */
#define SPIS_INTENSET_ACQUIRED_Set (1UL) /*!< Enable */

/* Bit 4 : Write '1' to Enable interrupt for ENDRX event */
#define SPIS_INTENSET_ENDRX_Pos (4UL) /*!< Position of ENDRX field. */
#define SPIS_INTENSET_ENDRX_Msk (0x1UL << SPIS_INTENSET_ENDRX_Pos) /*!< Bit mask of ENDRX field. */
#define SPIS_INTENSET_ENDRX_Disabled (0UL) /*!< Read: Disabled */
#define SPIS_INTENSET_ENDRX_Enabled (1UL) /*!< Read: Enabled */
#define SPIS_INTENSET_ENDRX_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable interrupt for END event */
#define SPIS_INTENSET_END_Pos (1UL) /*!< Position of END field. */
#define SPIS_INTENSET_END_Msk (0x1UL << SPIS_INTENSET_END_Pos) /*!< Bit mask of END field. */
#define SPIS_INTENSET_END_Disabled (0UL) /*!< Read: Disabled */
#define SPIS_INTENSET_END_Enabled (1UL) /*!< Read: Enabled */
#define SPIS_INTENSET_END_Set (1UL) /*!< Enable */

/* Register: SPIS_INTENCLR */
/* Description: Disable interrupt */

/* Bit 10 : Write '1' to Disable interrupt for ACQUIRED event */
#define SPIS_INTENCLR_ACQUIRED_Pos (10UL) /*!< Position of ACQUIRED field. */
#define SPIS_INTENCLR_ACQUIRED_Msk (0x1UL << SPIS_INTENCLR_ACQUIRED_Pos) /*!< Bit mask of ACQUIRED field. */
#define SPIS_INTENCLR_ACQUIRED_Disabled (0UL) /*!< Read: Disabled */
#define SPIS_INTENCLR_ACQUIRED_Enabled (1UL) /*!< Read: Enabled */
#define SPIS_INTENCLR_ACQUIRED_Clear (1UL) /*!< Disable */

/* Bit 4 : Write '1' to Disable interrupt for ENDRX event */
#define SPIS_INTENCLR_ENDRX_Pos (4UL) /*!< Position of ENDRX field. */
#define SPIS_INTENCLR_ENDRX_Msk (0x1UL << SPIS_INTENCLR_ENDRX_Pos) /*!< Bit mask of ENDRX field. */
#define SPIS_INTENCLR_ENDRX_Disabled (0UL) /*!< Read: Disabled */
#define SPIS_INTENCLR_ENDRX_Enabled (1UL) /*!< Read: Enabled */
#define SPIS_INTENCLR_ENDRX_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable interrupt for END event */
#define SPIS_INTENCLR_END_Pos (1UL) /*!< Position of END field. */
#define SPIS_INTENCLR_END_Msk (0x1UL << SPIS_INTENCLR_END_Pos) /*!< Bit mask of END field. */
#define SPIS_INTENCLR_END_Disabled (0UL) /*!< Read: Disabled */
#define SPIS_INTENCLR_END_Enabled (1UL) /*!< Read: Enabled */
#define SPIS_INTENCLR_END_Clear (1UL) /*!< Disable */

/* Register: SPIS_SEMSTAT */
/* Description: Semaphore status register */

/* Bits 1..0 : Semaphore status */
#define SPIS_SEMSTAT_SEMSTAT_Pos (0UL) /*!< Position of SEMSTAT field. */
#define SPIS_SEMSTAT_SEMSTAT_Msk (0x3UL << SPIS_SEMSTAT_SEMSTAT_Pos) /*!< Bit mask of SEMSTAT field. */
#define SPIS_SEMSTAT_SEMSTAT_Free (0UL) /*!< Semaphore is free */
#define SPIS_SEMSTAT_SEMSTAT_CPU (1UL) /*!< Semaphore is assigned to CPU */
#define SPIS_SEMSTAT_SEMSTAT_SPIS (2UL) /*!< Semaphore is assigned to SPI slave */
#define SPIS_SEMSTAT_SEMSTAT_CPUPending (3UL) /*!< Semaphore is assigned to SPI but a handover to the CPU is pending */

/* Register: SPIS_STATUS */
/* Description: Status from last transaction */

/* Bit 1 : RX buffer overflow detected, and prevented */
#define SPIS_STATUS_OVERFLOW_Pos (1UL) /*!< Position of OVERFLOW field. */
#define SPIS_STATUS_OVERFLOW_Msk (0x1UL << SPIS_STATUS_OVERFLOW_Pos) /*!< Bit mask of OVERFLOW field. */
#define SPIS_STATUS_OVERFLOW_NotPresent (0UL) /*!< Read: error not present */
#define SPIS_STATUS_OVERFLOW_Present (1UL) /*!< Read: error present */
#define SPIS_STATUS_OVERFLOW_Clear (1UL) /*!< Write: clear error on writing '1' */

/* Bit 0 : TX buffer over-read detected, and prevented */
#define SPIS_STATUS_OVERREAD_Pos (0UL) /*!< Position of OVERREAD field. */
#define SPIS_STATUS_OVERREAD_Msk (0x1UL << SPIS_STATUS_OVERREAD_Pos) /*!< Bit mask of OVERREAD field. */
#define SPIS_STATUS_OVERREAD_NotPresent (0UL) /*!< Read: error not present */
#define SPIS_STATUS_OVERREAD_Present (1UL) /*!< Read: error present */
#define SPIS_STATUS_OVERREAD_Clear (1UL) /*!< Write: clear error on writing '1' */

/* Register: SPIS_ENABLE */
/* Description: Enable SPI slave */

/* Bits 3..0 : Enable or disable SPI slave */
#define SPIS_ENABLE_ENABLE_Pos (0UL) /*!< Position of ENABLE field. */
#define SPIS_ENABLE_ENABLE_Msk (0xFUL << SPIS_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define SPIS_ENABLE_ENABLE_Disabled (0UL) /*!< Disable SPI slave */
#define SPIS_ENABLE_ENABLE_Enabled (2UL) /*!< Enable SPI slave */

/* Register: SPIS_PSEL_SCK */
/* Description: Pin select for SCK */

/* Bit 31 : Connection */
#define SPIS_PSEL_SCK_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define SPIS_PSEL_SCK_CONNECT_Msk (0x1UL << SPIS_PSEL_SCK_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define SPIS_PSEL_SCK_CONNECT_Connected (0UL) /*!< Connect */
#define SPIS_PSEL_SCK_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define SPIS_PSEL_SCK_PORT_Pos (5UL) /*!< Position of PORT field. */
#define SPIS_PSEL_SCK_PORT_Msk (0x3UL << SPIS_PSEL_SCK_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define SPIS_PSEL_SCK_PIN_Pos (0UL) /*!< Position of PIN field. */
#define SPIS_PSEL_SCK_PIN_Msk (0x1FUL << SPIS_PSEL_SCK_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: SPIS_PSEL_MISO */
/* Description: Pin select for MISO signal */

/* Bit 31 : Connection */
#define SPIS_PSEL_MISO_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define SPIS_PSEL_MISO_CONNECT_Msk (0x1UL << SPIS_PSEL_MISO_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define SPIS_PSEL_MISO_CONNECT_Connected (0UL) /*!< Connect */
#define SPIS_PSEL_MISO_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define SPIS_PSEL_MISO_PORT_Pos (5UL) /*!< Position of PORT field. */
#define SPIS_PSEL_MISO_PORT_Msk (0x3UL << SPIS_PSEL_MISO_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define SPIS_PSEL_MISO_PIN_Pos (0UL) /*!< Position of PIN field. */
#define SPIS_PSEL_MISO_PIN_Msk (0x1FUL << SPIS_PSEL_MISO_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: SPIS_PSEL_MOSI */
/* Description: Pin select for MOSI signal */

/* Bit 31 : Connection */
#define SPIS_PSEL_MOSI_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define SPIS_PSEL_MOSI_CONNECT_Msk (0x1UL << SPIS_PSEL_MOSI_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define SPIS_PSEL_MOSI_CONNECT_Connected (0UL) /*!< Connect */
#define SPIS_PSEL_MOSI_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define SPIS_PSEL_MOSI_PORT_Pos (5UL) /*!< Position of PORT field. */
#define SPIS_PSEL_MOSI_PORT_Msk (0x3UL << SPIS_PSEL_MOSI_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define SPIS_PSEL_MOSI_PIN_Pos (0UL) /*!< Position of PIN field. */
#define SPIS_PSEL_MOSI_PIN_Msk (0x1FUL << SPIS_PSEL_MOSI_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: SPIS_PSEL_CSN */
/* Description: Pin select for CSN signal */

/* Bit 31 : Connection */
#define SPIS_PSEL_CSN_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define SPIS_PSEL_CSN_CONNECT_Msk (0x1UL << SPIS_PSEL_CSN_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define SPIS_PSEL_CSN_CONNECT_Connected (0UL) /*!< Connect */
#define SPIS_PSEL_CSN_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define SPIS_PSEL_CSN_PORT_Pos (5UL) /*!< Position of PORT field. */
#define SPIS_PSEL_CSN_PORT_Msk (0x3UL << SPIS_PSEL_CSN_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define SPIS_PSEL_CSN_PIN_Pos (0UL) /*!< Position of PIN field. */
#define SPIS_PSEL_CSN_PIN_Msk (0x1FUL << SPIS_PSEL_CSN_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: SPIS_RXD_PTR */
/* Description: RXD data pointer */

/* Bits 31..0 : RXD data pointer */
#define SPIS_RXD_PTR_PTR_Pos (0UL) /*!< Position of PTR field. */
#define SPIS_RXD_PTR_PTR_Msk (0xFFFFFFFFUL << SPIS_RXD_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: SPIS_RXD_MAXCNT */
/* Description: Maximum number of bytes in receive buffer */

/* Bits 7..0 : Maximum number of bytes in receive buffer */
#define SPIS_RXD_MAXCNT_MAXCNT_Pos (0UL) /*!< Position of MAXCNT field. */
#define SPIS_RXD_MAXCNT_MAXCNT_Msk (0xFFUL << SPIS_RXD_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: SPIS_RXD_AMOUNT */
/* Description: Number of bytes received in last granted transaction */

/* Bits 7..0 : Number of bytes received in the last granted transaction */
#define SPIS_RXD_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define SPIS_RXD_AMOUNT_AMOUNT_Msk (0xFFUL << SPIS_RXD_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: SPIS_TXD_PTR */
/* Description: TXD data pointer */

/* Bits 31..0 : TXD data pointer */
#define SPIS_TXD_PTR_PTR_Pos (0UL) /*!< Position of PTR field. */
#define SPIS_TXD_PTR_PTR_Msk (0xFFFFFFFFUL << SPIS_TXD_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: SPIS_TXD_MAXCNT */
/* Description: Maximum number of bytes in transmit buffer */

/* Bits 7..0 : Maximum number of bytes in transmit buffer */
#define SPIS_TXD_MAXCNT_MAXCNT_Pos (0UL) /*!< Position of MAXCNT field. */
#define SPIS_TXD_MAXCNT_MAXCNT_Msk (0xFFUL << SPIS_TXD_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: SPIS_TXD_AMOUNT */
/* Description: Number of bytes transmitted in last granted transaction */

/* Bits 7..0 : Number of bytes transmitted in last granted transaction */
#define SPIS_TXD_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define SPIS_TXD_AMOUNT_AMOUNT_Msk (0xFFUL << SPIS_TXD_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: SPIS_CONFIG */
/* Description: Configuration register */

/* Bit 2 : Serial clock (SCK) polarity */
#define SPIS_CONFIG_CPOL_Pos (2UL) /*!< Position of CPOL field. */
#define SPIS_CONFIG_CPOL_Msk (0x1UL << SPIS_CONFIG_CPOL_Pos) /*!< Bit mask of CPOL field. */
#define SPIS_CONFIG_CPOL_ActiveHigh (0UL) /*!< Active high */
#define SPIS_CONFIG_CPOL_ActiveLow (1UL) /*!< Active low */

/* Bit 1 : Serial clock (SCK) phase */
#define SPIS_CONFIG_CPHA_Pos (1UL) /*!< Position of CPHA field. */
#define SPIS_CONFIG_CPHA_Msk (0x1UL << SPIS_CONFIG_CPHA_Pos) /*!< Bit mask of CPHA field. */
#define SPIS_CONFIG_CPHA_Leading (0UL) /*!< Sample on leading edge of clock, shift serial data on trailing edge */
#define SPIS_CONFIG_CPHA_Trailing (1UL) /*!< Sample on trailing edge of clock, shift serial data on leading edge */

/* Bit 0 : Bit order */
#define SPIS_CONFIG_ORDER_Pos (0UL) /*!< Position of ORDER field. */
#define SPIS_CONFIG_ORDER_Msk (0x1UL << SPIS_CONFIG_ORDER_Pos) /*!< Bit mask of ORDER field. */
#define SPIS_CONFIG_ORDER_MsbFirst (0UL) /*!< Most significant bit shifted out first */
#define SPIS_CONFIG_ORDER_LsbFirst (1UL) /*!< Least significant bit shifted out first */

/* Register: SPIS_DEF */
/* Description: Default character. Character clocked out in case of an ignored transaction. */

/* Bits 7..0 : Default character. Character clocked out in case of an ignored transaction. */
#define SPIS_DEF_DEF_Pos (0UL) /*!< Position of DEF field. */
#define SPIS_DEF_DEF_Msk (0xFFUL << SPIS_DEF_DEF_Pos) /*!< Bit mask of DEF field. */

/* Register: SPIS_ORC */
/* Description: Over-read character */

/* Bits 7..0 : Over-read character. Character clocked out after an over-read of the transmit buffer. */
#define SPIS_ORC_ORC_Pos (0UL) /*!< Position of ORC field. */
#define SPIS_ORC_ORC_Msk (0xFFUL << SPIS_ORC_ORC_Pos) /*!< Bit mask of ORC field. */


/* Peripheral: TEMP */
/* Description: Temperature Sensor */

/* Register: TEMP_INTENSET */
/* Description: Enable interrupt */

/* Bit 0 : Write '1' to Enable interrupt for DATARDY event */
#define TEMP_INTENSET_DATARDY_Pos (0UL) /*!< Position of DATARDY field. */
#define TEMP_INTENSET_DATARDY_Msk (0x1UL << TEMP_INTENSET_DATARDY_Pos) /*!< Bit mask of DATARDY field. */
#define TEMP_INTENSET_DATARDY_Disabled (0UL) /*!< Read: Disabled */
#define TEMP_INTENSET_DATARDY_Enabled (1UL) /*!< Read: Enabled */
#define TEMP_INTENSET_DATARDY_Set (1UL) /*!< Enable */

/* Register: TEMP_INTENCLR */
/* Description: Disable interrupt */

/* Bit 0 : Write '1' to Disable interrupt for DATARDY event */
#define TEMP_INTENCLR_DATARDY_Pos (0UL) /*!< Position of DATARDY field. */
#define TEMP_INTENCLR_DATARDY_Msk (0x1UL << TEMP_INTENCLR_DATARDY_Pos) /*!< Bit mask of DATARDY field. */
#define TEMP_INTENCLR_DATARDY_Disabled (0UL) /*!< Read: Disabled */
#define TEMP_INTENCLR_DATARDY_Enabled (1UL) /*!< Read: Enabled */
#define TEMP_INTENCLR_DATARDY_Clear (1UL) /*!< Disable */

/* Register: TEMP_TEMP */
/* Description: Temperature in degC (0.25deg steps) */

/* Bits 31..0 : Temperature in degC (0.25deg steps) */
#define TEMP_TEMP_TEMP_Pos (0UL) /*!< Position of TEMP field. */
#define TEMP_TEMP_TEMP_Msk (0xFFFFFFFFUL << TEMP_TEMP_TEMP_Pos) /*!< Bit mask of TEMP field. */

/* Register: TEMP_A0 */
/* Description: Slope of 1st piece wise linear function */

/* Bits 11..0 : Slope of 1st piece wise linear function */
#define TEMP_A0_A0_Pos (0UL) /*!< Position of A0 field. */
#define TEMP_A0_A0_Msk (0xFFFUL << TEMP_A0_A0_Pos) /*!< Bit mask of A0 field. */

/* Register: TEMP_A1 */
/* Description: Slope of 2nd piece wise linear function */

/* Bits 11..0 : Slope of 2nd piece wise linear function */
#define TEMP_A1_A1_Pos (0UL) /*!< Position of A1 field. */
#define TEMP_A1_A1_Msk (0xFFFUL << TEMP_A1_A1_Pos) /*!< Bit mask of A1 field. */

/* Register: TEMP_A2 */
/* Description: Slope of 3rd piece wise linear function */

/* Bits 11..0 : Slope of 3rd piece wise linear function */
#define TEMP_A2_A2_Pos (0UL) /*!< Position of A2 field. */
#define TEMP_A2_A2_Msk (0xFFFUL << TEMP_A2_A2_Pos) /*!< Bit mask of A2 field. */

/* Register: TEMP_A3 */
/* Description: Slope of 4th piece wise linear function */

/* Bits 11..0 : Slope of 4th piece wise linear function */
#define TEMP_A3_A3_Pos (0UL) /*!< Position of A3 field. */
#define TEMP_A3_A3_Msk (0xFFFUL << TEMP_A3_A3_Pos) /*!< Bit mask of A3 field. */

/* Register: TEMP_A4 */
/* Description: Slope of 5th piece wise linear function */

/* Bits 11..0 : Slope of 5th piece wise linear function */
#define TEMP_A4_A4_Pos (0UL) /*!< Position of A4 field. */
#define TEMP_A4_A4_Msk (0xFFFUL << TEMP_A4_A4_Pos) /*!< Bit mask of A4 field. */

/* Register: TEMP_A5 */
/* Description: Slope of 6th piece wise linear function */

/* Bits 11..0 : Slope of 6th piece wise linear function */
#define TEMP_A5_A5_Pos (0UL) /*!< Position of A5 field. */
#define TEMP_A5_A5_Msk (0xFFFUL << TEMP_A5_A5_Pos) /*!< Bit mask of A5 field. */

/* Register: TEMP_B0 */
/* Description: y-intercept of 1st piece wise linear function */

/* Bits 13..0 : y-intercept of 1st piece wise linear function */
#define TEMP_B0_B0_Pos (0UL) /*!< Position of B0 field. */
#define TEMP_B0_B0_Msk (0x3FFFUL << TEMP_B0_B0_Pos) /*!< Bit mask of B0 field. */

/* Register: TEMP_B1 */
/* Description: y-intercept of 2nd piece wise linear function */

/* Bits 13..0 : y-intercept of 2nd piece wise linear function */
#define TEMP_B1_B1_Pos (0UL) /*!< Position of B1 field. */
#define TEMP_B1_B1_Msk (0x3FFFUL << TEMP_B1_B1_Pos) /*!< Bit mask of B1 field. */

/* Register: TEMP_B2 */
/* Description: y-intercept of 3rd piece wise linear function */

/* Bits 13..0 : y-intercept of 3rd piece wise linear function */
#define TEMP_B2_B2_Pos (0UL) /*!< Position of B2 field. */
#define TEMP_B2_B2_Msk (0x3FFFUL << TEMP_B2_B2_Pos) /*!< Bit mask of B2 field. */

/* Register: TEMP_B3 */
/* Description: y-intercept of 4th piece wise linear function */

/* Bits 13..0 : y-intercept of 4th piece wise linear function */
#define TEMP_B3_B3_Pos (0UL) /*!< Position of B3 field. */
#define TEMP_B3_B3_Msk (0x3FFFUL << TEMP_B3_B3_Pos) /*!< Bit mask of B3 field. */

/* Register: TEMP_B4 */
/* Description: y-intercept of 5th piece wise linear function */

/* Bits 13..0 : y-intercept of 5th piece wise linear function */
#define TEMP_B4_B4_Pos (0UL) /*!< Position of B4 field. */
#define TEMP_B4_B4_Msk (0x3FFFUL << TEMP_B4_B4_Pos) /*!< Bit mask of B4 field. */

/* Register: TEMP_B5 */
/* Description: y-intercept of 6th piece wise linear function */

/* Bits 13..0 : y-intercept of 6th piece wise linear function */
#define TEMP_B5_B5_Pos (0UL) /*!< Position of B5 field. */
#define TEMP_B5_B5_Msk (0x3FFFUL << TEMP_B5_B5_Pos) /*!< Bit mask of B5 field. */

/* Register: TEMP_T0 */
/* Description: End point of 1st piece wise linear function */

/* Bits 7..0 : End point of 1st piece wise linear function */
#define TEMP_T0_T0_Pos (0UL) /*!< Position of T0 field. */
#define TEMP_T0_T0_Msk (0xFFUL << TEMP_T0_T0_Pos) /*!< Bit mask of T0 field. */

/* Register: TEMP_T1 */
/* Description: End point of 2nd piece wise linear function */

/* Bits 7..0 : End point of 2nd piece wise linear function */
#define TEMP_T1_T1_Pos (0UL) /*!< Position of T1 field. */
#define TEMP_T1_T1_Msk (0xFFUL << TEMP_T1_T1_Pos) /*!< Bit mask of T1 field. */

/* Register: TEMP_T2 */
/* Description: End point of 3rd piece wise linear function */

/* Bits 7..0 : End point of 3rd piece wise linear function */
#define TEMP_T2_T2_Pos (0UL) /*!< Position of T2 field. */
#define TEMP_T2_T2_Msk (0xFFUL << TEMP_T2_T2_Pos) /*!< Bit mask of T2 field. */

/* Register: TEMP_T3 */
/* Description: End point of 4th piece wise linear function */

/* Bits 7..0 : End point of 4th piece wise linear function */
#define TEMP_T3_T3_Pos (0UL) /*!< Position of T3 field. */
#define TEMP_T3_T3_Msk (0xFFUL << TEMP_T3_T3_Pos) /*!< Bit mask of T3 field. */

/* Register: TEMP_T4 */
/* Description: End point of 5th piece wise linear function */

/* Bits 7..0 : End point of 5th piece wise linear function */
#define TEMP_T4_T4_Pos (0UL) /*!< Position of T4 field. */
#define TEMP_T4_T4_Msk (0xFFUL << TEMP_T4_T4_Pos) /*!< Bit mask of T4 field. */


/* Peripheral: TIMER */
/* Description: Timer/Counter 0 */

/* Register: TIMER_SHORTS */
/* Description: Shortcut register */

/* Bit 13 : Shortcut between COMPARE[5] event and STOP task */
#define TIMER_SHORTS_COMPARE5_STOP_Pos (13UL) /*!< Position of COMPARE5_STOP field. */
#define TIMER_SHORTS_COMPARE5_STOP_Msk (0x1UL << TIMER_SHORTS_COMPARE5_STOP_Pos) /*!< Bit mask of COMPARE5_STOP field. */
#define TIMER_SHORTS_COMPARE5_STOP_Disabled (0UL) /*!< Disable shortcut */
#define TIMER_SHORTS_COMPARE5_STOP_Enabled (1UL) /*!< Enable shortcut */

/* Bit 12 : Shortcut between COMPARE[4] event and STOP task */
#define TIMER_SHORTS_COMPARE4_STOP_Pos (12UL) /*!< Position of COMPARE4_STOP field. */
#define TIMER_SHORTS_COMPARE4_STOP_Msk (0x1UL << TIMER_SHORTS_COMPARE4_STOP_Pos) /*!< Bit mask of COMPARE4_STOP field. */
#define TIMER_SHORTS_COMPARE4_STOP_Disabled (0UL) /*!< Disable shortcut */
#define TIMER_SHORTS_COMPARE4_STOP_Enabled (1UL) /*!< Enable shortcut */

/* Bit 11 : Shortcut between COMPARE[3] event and STOP task */
#define TIMER_SHORTS_COMPARE3_STOP_Pos (11UL) /*!< Position of COMPARE3_STOP field. */
#define TIMER_SHORTS_COMPARE3_STOP_Msk (0x1UL << TIMER_SHORTS_COMPARE3_STOP_Pos) /*!< Bit mask of COMPARE3_STOP field. */
#define TIMER_SHORTS_COMPARE3_STOP_Disabled (0UL) /*!< Disable shortcut */
#define TIMER_SHORTS_COMPARE3_STOP_Enabled (1UL) /*!< Enable shortcut */

/* Bit 10 : Shortcut between COMPARE[2] event and STOP task */
#define TIMER_SHORTS_COMPARE2_STOP_Pos (10UL) /*!< Position of COMPARE2_STOP field. */
#define TIMER_SHORTS_COMPARE2_STOP_Msk (0x1UL << TIMER_SHORTS_COMPARE2_STOP_Pos) /*!< Bit mask of COMPARE2_STOP field. */
#define TIMER_SHORTS_COMPARE2_STOP_Disabled (0UL) /*!< Disable shortcut */
#define TIMER_SHORTS_COMPARE2_STOP_Enabled (1UL) /*!< Enable shortcut */

/* Bit 9 : Shortcut between COMPARE[1] event and STOP task */
#define TIMER_SHORTS_COMPARE1_STOP_Pos (9UL) /*!< Position of COMPARE1_STOP field. */
#define TIMER_SHORTS_COMPARE1_STOP_Msk (0x1UL << TIMER_SHORTS_COMPARE1_STOP_Pos) /*!< Bit mask of COMPARE1_STOP field. */
#define TIMER_SHORTS_COMPARE1_STOP_Disabled (0UL) /*!< Disable shortcut */
#define TIMER_SHORTS_COMPARE1_STOP_Enabled (1UL) /*!< Enable shortcut */

/* Bit 8 : Shortcut between COMPARE[0] event and STOP task */
#define TIMER_SHORTS_COMPARE0_STOP_Pos (8UL) /*!< Position of COMPARE0_STOP field. */
#define TIMER_SHORTS_COMPARE0_STOP_Msk (0x1UL << TIMER_SHORTS_COMPARE0_STOP_Pos) /*!< Bit mask of COMPARE0_STOP field. */
#define TIMER_SHORTS_COMPARE0_STOP_Disabled (0UL) /*!< Disable shortcut */
#define TIMER_SHORTS_COMPARE0_STOP_Enabled (1UL) /*!< Enable shortcut */

/* Bit 5 : Shortcut between COMPARE[5] event and CLEAR task */
#define TIMER_SHORTS_COMPARE5_CLEAR_Pos (5UL) /*!< Position of COMPARE5_CLEAR field. */
#define TIMER_SHORTS_COMPARE5_CLEAR_Msk (0x1UL << TIMER_SHORTS_COMPARE5_CLEAR_Pos) /*!< Bit mask of COMPARE5_CLEAR field. */
#define TIMER_SHORTS_COMPARE5_CLEAR_Disabled (0UL) /*!< Disable shortcut */
#define TIMER_SHORTS_COMPARE5_CLEAR_Enabled (1UL) /*!< Enable shortcut */

/* Bit 4 : Shortcut between COMPARE[4] event and CLEAR task */
#define TIMER_SHORTS_COMPARE4_CLEAR_Pos (4UL) /*!< Position of COMPARE4_CLEAR field. */
#define TIMER_SHORTS_COMPARE4_CLEAR_Msk (0x1UL << TIMER_SHORTS_COMPARE4_CLEAR_Pos) /*!< Bit mask of COMPARE4_CLEAR field. */
#define TIMER_SHORTS_COMPARE4_CLEAR_Disabled (0UL) /*!< Disable shortcut */
#define TIMER_SHORTS_COMPARE4_CLEAR_Enabled (1UL) /*!< Enable shortcut */

/* Bit 3 : Shortcut between COMPARE[3] event and CLEAR task */
#define TIMER_SHORTS_COMPARE3_CLEAR_Pos (3UL) /*!< Position of COMPARE3_CLEAR field. */
#define TIMER_SHORTS_COMPARE3_CLEAR_Msk (0x1UL << TIMER_SHORTS_COMPARE3_CLEAR_Pos) /*!< Bit mask of COMPARE3_CLEAR field. */
#define TIMER_SHORTS_COMPARE3_CLEAR_Disabled (0UL) /*!< Disable shortcut */
#define TIMER_SHORTS_COMPARE3_CLEAR_Enabled (1UL) /*!< Enable shortcut */

/* Bit 2 : Shortcut between COMPARE[2] event and CLEAR task */
#define TIMER_SHORTS_COMPARE2_CLEAR_Pos (2UL) /*!< Position of COMPARE2_CLEAR field. */
#define TIMER_SHORTS_COMPARE2_CLEAR_Msk (0x1UL << TIMER_SHORTS_COMPARE2_CLEAR_Pos) /*!< Bit mask of COMPARE2_CLEAR field. */
#define TIMER_SHORTS_COMPARE2_CLEAR_Disabled (0UL) /*!< Disable shortcut */
#define TIMER_SHORTS_COMPARE2_CLEAR_Enabled (1UL) /*!< Enable shortcut */

/* Bit 1 : Shortcut between COMPARE[1] event and CLEAR task */
#define TIMER_SHORTS_COMPARE1_CLEAR_Pos (1UL) /*!< Position of COMPARE1_CLEAR field. */
#define TIMER_SHORTS_COMPARE1_CLEAR_Msk (0x1UL << TIMER_SHORTS_COMPARE1_CLEAR_Pos) /*!< Bit mask of COMPARE1_CLEAR field. */
#define TIMER_SHORTS_COMPARE1_CLEAR_Disabled (0UL) /*!< Disable shortcut */
#define TIMER_SHORTS_COMPARE1_CLEAR_Enabled (1UL) /*!< Enable shortcut */

/* Bit 0 : Shortcut between COMPARE[0] event and CLEAR task */
#define TIMER_SHORTS_COMPARE0_CLEAR_Pos (0UL) /*!< Position of COMPARE0_CLEAR field. */
#define TIMER_SHORTS_COMPARE0_CLEAR_Msk (0x1UL << TIMER_SHORTS_COMPARE0_CLEAR_Pos) /*!< Bit mask of COMPARE0_CLEAR field. */
#define TIMER_SHORTS_COMPARE0_CLEAR_Disabled (0UL) /*!< Disable shortcut */
#define TIMER_SHORTS_COMPARE0_CLEAR_Enabled (1UL) /*!< Enable shortcut */

/* Register: TIMER_INTENSET */
/* Description: Enable interrupt */

/* Bit 21 : Write '1' to Enable interrupt for COMPARE[5] event */
#define TIMER_INTENSET_COMPARE5_Pos (21UL) /*!< Position of COMPARE5 field. */
#define TIMER_INTENSET_COMPARE5_Msk (0x1UL << TIMER_INTENSET_COMPARE5_Pos) /*!< Bit mask of COMPARE5 field. */
#define TIMER_INTENSET_COMPARE5_Disabled (0UL) /*!< Read: Disabled */
#define TIMER_INTENSET_COMPARE5_Enabled (1UL) /*!< Read: Enabled */
#define TIMER_INTENSET_COMPARE5_Set (1UL) /*!< Enable */

/* Bit 20 : Write '1' to Enable interrupt for COMPARE[4] event */
#define TIMER_INTENSET_COMPARE4_Pos (20UL) /*!< Position of COMPARE4 field. */
#define TIMER_INTENSET_COMPARE4_Msk (0x1UL << TIMER_INTENSET_COMPARE4_Pos) /*!< Bit mask of COMPARE4 field. */
#define TIMER_INTENSET_COMPARE4_Disabled (0UL) /*!< Read: Disabled */
#define TIMER_INTENSET_COMPARE4_Enabled (1UL) /*!< Read: Enabled */
#define TIMER_INTENSET_COMPARE4_Set (1UL) /*!< Enable */

/* Bit 19 : Write '1' to Enable interrupt for COMPARE[3] event */
#define TIMER_INTENSET_COMPARE3_Pos (19UL) /*!< Position of COMPARE3 field. */
#define TIMER_INTENSET_COMPARE3_Msk (0x1UL << TIMER_INTENSET_COMPARE3_Pos) /*!< Bit mask of COMPARE3 field. */
#define TIMER_INTENSET_COMPARE3_Disabled (0UL) /*!< Read: Disabled */
#define TIMER_INTENSET_COMPARE3_Enabled (1UL) /*!< Read: Enabled */
#define TIMER_INTENSET_COMPARE3_Set (1UL) /*!< Enable */

/* Bit 18 : Write '1' to Enable interrupt for COMPARE[2] event */
#define TIMER_INTENSET_COMPARE2_Pos (18UL) /*!< Position of COMPARE2 field. */
#define TIMER_INTENSET_COMPARE2_Msk (0x1UL << TIMER_INTENSET_COMPARE2_Pos) /*!< Bit mask of COMPARE2 field. */
#define TIMER_INTENSET_COMPARE2_Disabled (0UL) /*!< Read: Disabled */
#define TIMER_INTENSET_COMPARE2_Enabled (1UL) /*!< Read: Enabled */
#define TIMER_INTENSET_COMPARE2_Set (1UL) /*!< Enable */

/* Bit 17 : Write '1' to Enable interrupt for COMPARE[1] event */
#define TIMER_INTENSET_COMPARE1_Pos (17UL) /*!< Position of COMPARE1 field. */
#define TIMER_INTENSET_COMPARE1_Msk (0x1UL << TIMER_INTENSET_COMPARE1_Pos) /*!< Bit mask of COMPARE1 field. */
#define TIMER_INTENSET_COMPARE1_Disabled (0UL) /*!< Read: Disabled */
#define TIMER_INTENSET_COMPARE1_Enabled (1UL) /*!< Read: Enabled */
#define TIMER_INTENSET_COMPARE1_Set (1UL) /*!< Enable */

/* Bit 16 : Write '1' to Enable interrupt for COMPARE[0] event */
#define TIMER_INTENSET_COMPARE0_Pos (16UL) /*!< Position of COMPARE0 field. */
#define TIMER_INTENSET_COMPARE0_Msk (0x1UL << TIMER_INTENSET_COMPARE0_Pos) /*!< Bit mask of COMPARE0 field. */
#define TIMER_INTENSET_COMPARE0_Disabled (0UL) /*!< Read: Disabled */
#define TIMER_INTENSET_COMPARE0_Enabled (1UL) /*!< Read: Enabled */
#define TIMER_INTENSET_COMPARE0_Set (1UL) /*!< Enable */

/* Register: TIMER_INTENCLR */
/* Description: Disable interrupt */

/* Bit 21 : Write '1' to Disable interrupt for COMPARE[5] event */
#define TIMER_INTENCLR_COMPARE5_Pos (21UL) /*!< Position of COMPARE5 field. */
#define TIMER_INTENCLR_COMPARE5_Msk (0x1UL << TIMER_INTENCLR_COMPARE5_Pos) /*!< Bit mask of COMPARE5 field. */
#define TIMER_INTENCLR_COMPARE5_Disabled (0UL) /*!< Read: Disabled */
#define TIMER_INTENCLR_COMPARE5_Enabled (1UL) /*!< Read: Enabled */
#define TIMER_INTENCLR_COMPARE5_Clear (1UL) /*!< Disable */

/* Bit 20 : Write '1' to Disable interrupt for COMPARE[4] event */
#define TIMER_INTENCLR_COMPARE4_Pos (20UL) /*!< Position of COMPARE4 field. */
#define TIMER_INTENCLR_COMPARE4_Msk (0x1UL << TIMER_INTENCLR_COMPARE4_Pos) /*!< Bit mask of COMPARE4 field. */
#define TIMER_INTENCLR_COMPARE4_Disabled (0UL) /*!< Read: Disabled */
#define TIMER_INTENCLR_COMPARE4_Enabled (1UL) /*!< Read: Enabled */
#define TIMER_INTENCLR_COMPARE4_Clear (1UL) /*!< Disable */

/* Bit 19 : Write '1' to Disable interrupt for COMPARE[3] event */
#define TIMER_INTENCLR_COMPARE3_Pos (19UL) /*!< Position of COMPARE3 field. */
#define TIMER_INTENCLR_COMPARE3_Msk (0x1UL << TIMER_INTENCLR_COMPARE3_Pos) /*!< Bit mask of COMPARE3 field. */
#define TIMER_INTENCLR_COMPARE3_Disabled (0UL) /*!< Read: Disabled */
#define TIMER_INTENCLR_COMPARE3_Enabled (1UL) /*!< Read: Enabled */
#define TIMER_INTENCLR_COMPARE3_Clear (1UL) /*!< Disable */

/* Bit 18 : Write '1' to Disable interrupt for COMPARE[2] event */
#define TIMER_INTENCLR_COMPARE2_Pos (18UL) /*!< Position of COMPARE2 field. */
#define TIMER_INTENCLR_COMPARE2_Msk (0x1UL << TIMER_INTENCLR_COMPARE2_Pos) /*!< Bit mask of COMPARE2 field. */
#define TIMER_INTENCLR_COMPARE2_Disabled (0UL) /*!< Read: Disabled */
#define TIMER_INTENCLR_COMPARE2_Enabled (1UL) /*!< Read: Enabled */
#define TIMER_INTENCLR_COMPARE2_Clear (1UL) /*!< Disable */

/* Bit 17 : Write '1' to Disable interrupt for COMPARE[1] event */
#define TIMER_INTENCLR_COMPARE1_Pos (17UL) /*!< Position of COMPARE1 field. */
#define TIMER_INTENCLR_COMPARE1_Msk (0x1UL << TIMER_INTENCLR_COMPARE1_Pos) /*!< Bit mask of COMPARE1 field. */
#define TIMER_INTENCLR_COMPARE1_Disabled (0UL) /*!< Read: Disabled */
#define TIMER_INTENCLR_COMPARE1_Enabled (1UL) /*!< Read: Enabled */
#define TIMER_INTENCLR_COMPARE1_Clear (1UL) /*!< Disable */

/* Bit 16 : Write '1' to Disable interrupt for COMPARE[0] event */
#define TIMER_INTENCLR_COMPARE0_Pos (16UL) /*!< Position of COMPARE0 field. */
#define TIMER_INTENCLR_COMPARE0_Msk (0x1UL << TIMER_INTENCLR_COMPARE0_Pos) /*!< Bit mask of COMPARE0 field. */
#define TIMER_INTENCLR_COMPARE0_Disabled (0UL) /*!< Read: Disabled */
#define TIMER_INTENCLR_COMPARE0_Enabled (1UL) /*!< Read: Enabled */
#define TIMER_INTENCLR_COMPARE0_Clear (1UL) /*!< Disable */

/* Register: TIMER_STATUS */
/* Description: Timer status */

/* Bit 0 : Timer status */
#define TIMER_STATUS_STATUS_Pos (0UL) /*!< Position of STATUS field. */
#define TIMER_STATUS_STATUS_Msk (0x1UL << TIMER_STATUS_STATUS_Pos) /*!< Bit mask of STATUS field. */
#define TIMER_STATUS_STATUS_Stopped (0UL) /*!< Timer is stopped */
#define TIMER_STATUS_STATUS_Started (1UL) /*!< Timer is started */

/* Register: TIMER_MODE */
/* Description: Timer mode selection */

/* Bits 1..0 : Timer mode */
#define TIMER_MODE_MODE_Pos (0UL) /*!< Position of MODE field. */
#define TIMER_MODE_MODE_Msk (0x3UL << TIMER_MODE_MODE_Pos) /*!< Bit mask of MODE field. */
#define TIMER_MODE_MODE_Timer (0UL) /*!< Select Timer mode */
#define TIMER_MODE_MODE_Counter (1UL) /*!< Deprecated enumerator -  Select Counter mode */
#define TIMER_MODE_MODE_LowPowerCounter (2UL) /*!< Select Low Power Counter mode */

/* Register: TIMER_BITMODE */
/* Description: Configure the number of bits used by the TIMER */

/* Bits 1..0 : Timer bit width */
#define TIMER_BITMODE_BITMODE_Pos (0UL) /*!< Position of BITMODE field. */
#define TIMER_BITMODE_BITMODE_Msk (0x3UL << TIMER_BITMODE_BITMODE_Pos) /*!< Bit mask of BITMODE field. */
#define TIMER_BITMODE_BITMODE_16Bit (0UL) /*!< 16 bit timer bit width */
#define TIMER_BITMODE_BITMODE_08Bit (1UL) /*!< 8 bit timer bit width */
#define TIMER_BITMODE_BITMODE_24Bit (2UL) /*!< 24 bit timer bit width */
#define TIMER_BITMODE_BITMODE_32Bit (3UL) /*!< 32 bit timer bit width */

/* Register: TIMER_PRESCALER */
/* Description: Timer prescaler register */

/* Bits 3..0 : Prescaler value */
#define TIMER_PRESCALER_PRESCALER_Pos (0UL) /*!< Position of PRESCALER field. */
#define TIMER_PRESCALER_PRESCALER_Msk (0xFUL << TIMER_PRESCALER_PRESCALER_Pos) /*!< Bit mask of PRESCALER field. */

/* Register: TIMER_CC */
/* Description: Description collection[0]:  Capture/Compare register 0 */

/* Bits 31..0 : Capture/Compare value */
#define TIMER_CC_CC_Pos (0UL) /*!< Position of CC field. */
#define TIMER_CC_CC_Msk (0xFFFFFFFFUL << TIMER_CC_CC_Pos) /*!< Bit mask of CC field. */


/* Peripheral: TWI */
/* Description: I2C compatible Two-Wire Interface 0 */

/* Register: TWI_SHORTS */
/* Description: Shortcut register */

/* Bit 1 : Shortcut between BB event and STOP task */
#define TWI_SHORTS_BB_STOP_Pos (1UL) /*!< Position of BB_STOP field. */
#define TWI_SHORTS_BB_STOP_Msk (0x1UL << TWI_SHORTS_BB_STOP_Pos) /*!< Bit mask of BB_STOP field. */
#define TWI_SHORTS_BB_STOP_Disabled (0UL) /*!< Disable shortcut */
#define TWI_SHORTS_BB_STOP_Enabled (1UL) /*!< Enable shortcut */

/* Bit 0 : Shortcut between BB event and SUSPEND task */
#define TWI_SHORTS_BB_SUSPEND_Pos (0UL) /*!< Position of BB_SUSPEND field. */
#define TWI_SHORTS_BB_SUSPEND_Msk (0x1UL << TWI_SHORTS_BB_SUSPEND_Pos) /*!< Bit mask of BB_SUSPEND field. */
#define TWI_SHORTS_BB_SUSPEND_Disabled (0UL) /*!< Disable shortcut */
#define TWI_SHORTS_BB_SUSPEND_Enabled (1UL) /*!< Enable shortcut */

/* Register: TWI_INTENSET */
/* Description: Enable interrupt */

/* Bit 18 : Write '1' to Enable interrupt for SUSPENDED event */
#define TWI_INTENSET_SUSPENDED_Pos (18UL) /*!< Position of SUSPENDED field. */
#define TWI_INTENSET_SUSPENDED_Msk (0x1UL << TWI_INTENSET_SUSPENDED_Pos) /*!< Bit mask of SUSPENDED field. */
#define TWI_INTENSET_SUSPENDED_Disabled (0UL) /*!< Read: Disabled */
#define TWI_INTENSET_SUSPENDED_Enabled (1UL) /*!< Read: Enabled */
#define TWI_INTENSET_SUSPENDED_Set (1UL) /*!< Enable */

/* Bit 14 : Write '1' to Enable interrupt for BB event */
#define TWI_INTENSET_BB_Pos (14UL) /*!< Position of BB field. */
#define TWI_INTENSET_BB_Msk (0x1UL << TWI_INTENSET_BB_Pos) /*!< Bit mask of BB field. */
#define TWI_INTENSET_BB_Disabled (0UL) /*!< Read: Disabled */
#define TWI_INTENSET_BB_Enabled (1UL) /*!< Read: Enabled */
#define TWI_INTENSET_BB_Set (1UL) /*!< Enable */

/* Bit 9 : Write '1' to Enable interrupt for ERROR event */
#define TWI_INTENSET_ERROR_Pos (9UL) /*!< Position of ERROR field. */
#define TWI_INTENSET_ERROR_Msk (0x1UL << TWI_INTENSET_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define TWI_INTENSET_ERROR_Disabled (0UL) /*!< Read: Disabled */
#define TWI_INTENSET_ERROR_Enabled (1UL) /*!< Read: Enabled */
#define TWI_INTENSET_ERROR_Set (1UL) /*!< Enable */

/* Bit 7 : Write '1' to Enable interrupt for TXDSENT event */
#define TWI_INTENSET_TXDSENT_Pos (7UL) /*!< Position of TXDSENT field. */
#define TWI_INTENSET_TXDSENT_Msk (0x1UL << TWI_INTENSET_TXDSENT_Pos) /*!< Bit mask of TXDSENT field. */
#define TWI_INTENSET_TXDSENT_Disabled (0UL) /*!< Read: Disabled */
#define TWI_INTENSET_TXDSENT_Enabled (1UL) /*!< Read: Enabled */
#define TWI_INTENSET_TXDSENT_Set (1UL) /*!< Enable */

/* Bit 2 : Write '1' to Enable interrupt for RXDREADY event */
#define TWI_INTENSET_RXDREADY_Pos (2UL) /*!< Position of RXDREADY field. */
#define TWI_INTENSET_RXDREADY_Msk (0x1UL << TWI_INTENSET_RXDREADY_Pos) /*!< Bit mask of RXDREADY field. */
#define TWI_INTENSET_RXDREADY_Disabled (0UL) /*!< Read: Disabled */
#define TWI_INTENSET_RXDREADY_Enabled (1UL) /*!< Read: Enabled */
#define TWI_INTENSET_RXDREADY_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable interrupt for STOPPED event */
#define TWI_INTENSET_STOPPED_Pos (1UL) /*!< Position of STOPPED field. */
#define TWI_INTENSET_STOPPED_Msk (0x1UL << TWI_INTENSET_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define TWI_INTENSET_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define TWI_INTENSET_STOPPED_Enabled (1UL) /*!< Read: Enabled */
#define TWI_INTENSET_STOPPED_Set (1UL) /*!< Enable */

/* Register: TWI_INTENCLR */
/* Description: Disable interrupt */

/* Bit 18 : Write '1' to Disable interrupt for SUSPENDED event */
#define TWI_INTENCLR_SUSPENDED_Pos (18UL) /*!< Position of SUSPENDED field. */
#define TWI_INTENCLR_SUSPENDED_Msk (0x1UL << TWI_INTENCLR_SUSPENDED_Pos) /*!< Bit mask of SUSPENDED field. */
#define TWI_INTENCLR_SUSPENDED_Disabled (0UL) /*!< Read: Disabled */
#define TWI_INTENCLR_SUSPENDED_Enabled (1UL) /*!< Read: Enabled */
#define TWI_INTENCLR_SUSPENDED_Clear (1UL) /*!< Disable */

/* Bit 14 : Write '1' to Disable interrupt for BB event */
#define TWI_INTENCLR_BB_Pos (14UL) /*!< Position of BB field. */
#define TWI_INTENCLR_BB_Msk (0x1UL << TWI_INTENCLR_BB_Pos) /*!< Bit mask of BB field. */
#define TWI_INTENCLR_BB_Disabled (0UL) /*!< Read: Disabled */
#define TWI_INTENCLR_BB_Enabled (1UL) /*!< Read: Enabled */
#define TWI_INTENCLR_BB_Clear (1UL) /*!< Disable */

/* Bit 9 : Write '1' to Disable interrupt for ERROR event */
#define TWI_INTENCLR_ERROR_Pos (9UL) /*!< Position of ERROR field. */
#define TWI_INTENCLR_ERROR_Msk (0x1UL << TWI_INTENCLR_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define TWI_INTENCLR_ERROR_Disabled (0UL) /*!< Read: Disabled */
#define TWI_INTENCLR_ERROR_Enabled (1UL) /*!< Read: Enabled */
#define TWI_INTENCLR_ERROR_Clear (1UL) /*!< Disable */

/* Bit 7 : Write '1' to Disable interrupt for TXDSENT event */
#define TWI_INTENCLR_TXDSENT_Pos (7UL) /*!< Position of TXDSENT field. */
#define TWI_INTENCLR_TXDSENT_Msk (0x1UL << TWI_INTENCLR_TXDSENT_Pos) /*!< Bit mask of TXDSENT field. */
#define TWI_INTENCLR_TXDSENT_Disabled (0UL) /*!< Read: Disabled */
#define TWI_INTENCLR_TXDSENT_Enabled (1UL) /*!< Read: Enabled */
#define TWI_INTENCLR_TXDSENT_Clear (1UL) /*!< Disable */

/* Bit 2 : Write '1' to Disable interrupt for RXDREADY event */
#define TWI_INTENCLR_RXDREADY_Pos (2UL) /*!< Position of RXDREADY field. */
#define TWI_INTENCLR_RXDREADY_Msk (0x1UL << TWI_INTENCLR_RXDREADY_Pos) /*!< Bit mask of RXDREADY field. */
#define TWI_INTENCLR_RXDREADY_Disabled (0UL) /*!< Read: Disabled */
#define TWI_INTENCLR_RXDREADY_Enabled (1UL) /*!< Read: Enabled */
#define TWI_INTENCLR_RXDREADY_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable interrupt for STOPPED event */
#define TWI_INTENCLR_STOPPED_Pos (1UL) /*!< Position of STOPPED field. */
#define TWI_INTENCLR_STOPPED_Msk (0x1UL << TWI_INTENCLR_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define TWI_INTENCLR_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define TWI_INTENCLR_STOPPED_Enabled (1UL) /*!< Read: Enabled */
#define TWI_INTENCLR_STOPPED_Clear (1UL) /*!< Disable */

/* Register: TWI_ERRORSRC */
/* Description: Error source */

/* Bit 2 : NACK received after sending a data byte (write '1' to clear) */
#define TWI_ERRORSRC_DNACK_Pos (2UL) /*!< Position of DNACK field. */
#define TWI_ERRORSRC_DNACK_Msk (0x1UL << TWI_ERRORSRC_DNACK_Pos) /*!< Bit mask of DNACK field. */
#define TWI_ERRORSRC_DNACK_NotPresent (0UL) /*!< Read: error not present */
#define TWI_ERRORSRC_DNACK_Present (1UL) /*!< Read: error present */

/* Bit 1 : NACK received after sending the address (write '1' to clear) */
#define TWI_ERRORSRC_ANACK_Pos (1UL) /*!< Position of ANACK field. */
#define TWI_ERRORSRC_ANACK_Msk (0x1UL << TWI_ERRORSRC_ANACK_Pos) /*!< Bit mask of ANACK field. */
#define TWI_ERRORSRC_ANACK_NotPresent (0UL) /*!< Read: error not present */
#define TWI_ERRORSRC_ANACK_Present (1UL) /*!< Read: error present */

/* Bit 0 : Overrun error */
#define TWI_ERRORSRC_OVERRUN_Pos (0UL) /*!< Position of OVERRUN field. */
#define TWI_ERRORSRC_OVERRUN_Msk (0x1UL << TWI_ERRORSRC_OVERRUN_Pos) /*!< Bit mask of OVERRUN field. */
#define TWI_ERRORSRC_OVERRUN_NotPresent (0UL) /*!< Read: no overrun occured */
#define TWI_ERRORSRC_OVERRUN_Present (1UL) /*!< Read: overrun occured */

/* Register: TWI_ENABLE */
/* Description: Enable TWI */

/* Bits 3..0 : Enable or disable TWI */
#define TWI_ENABLE_ENABLE_Pos (0UL) /*!< Position of ENABLE field. */
#define TWI_ENABLE_ENABLE_Msk (0xFUL << TWI_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define TWI_ENABLE_ENABLE_Disabled (0UL) /*!< Disable TWI */
#define TWI_ENABLE_ENABLE_Enabled (5UL) /*!< Enable TWI */

/* Register: TWI_PSEL_SCL */
/* Description: Pin select for SCL */

/* Bit 31 : Connection */
#define TWI_PSEL_SCL_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define TWI_PSEL_SCL_CONNECT_Msk (0x1UL << TWI_PSEL_SCL_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define TWI_PSEL_SCL_CONNECT_Connected (0UL) /*!< Connect */
#define TWI_PSEL_SCL_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define TWI_PSEL_SCL_PORT_Pos (5UL) /*!< Position of PORT field. */
#define TWI_PSEL_SCL_PORT_Msk (0x3UL << TWI_PSEL_SCL_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define TWI_PSEL_SCL_PIN_Pos (0UL) /*!< Position of PIN field. */
#define TWI_PSEL_SCL_PIN_Msk (0x1FUL << TWI_PSEL_SCL_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: TWI_PSEL_SDA */
/* Description: Pin select for SDA */

/* Bit 31 : Connection */
#define TWI_PSEL_SDA_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define TWI_PSEL_SDA_CONNECT_Msk (0x1UL << TWI_PSEL_SDA_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define TWI_PSEL_SDA_CONNECT_Connected (0UL) /*!< Connect */
#define TWI_PSEL_SDA_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define TWI_PSEL_SDA_PORT_Pos (5UL) /*!< Position of PORT field. */
#define TWI_PSEL_SDA_PORT_Msk (0x3UL << TWI_PSEL_SDA_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define TWI_PSEL_SDA_PIN_Pos (0UL) /*!< Position of PIN field. */
#define TWI_PSEL_SDA_PIN_Msk (0x1FUL << TWI_PSEL_SDA_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: TWI_RXD */
/* Description: RXD register */

/* Bits 7..0 : RXD register */
#define TWI_RXD_RXD_Pos (0UL) /*!< Position of RXD field. */
#define TWI_RXD_RXD_Msk (0xFFUL << TWI_RXD_RXD_Pos) /*!< Bit mask of RXD field. */

/* Register: TWI_TXD */
/* Description: TXD register */

/* Bits 7..0 : TXD register */
#define TWI_TXD_TXD_Pos (0UL) /*!< Position of TXD field. */
#define TWI_TXD_TXD_Msk (0xFFUL << TWI_TXD_TXD_Pos) /*!< Bit mask of TXD field. */

/* Register: TWI_FREQUENCY */
/* Description: TWI frequency. Accuracy depends on the HFCLK source selected. */

/* Bits 31..0 : TWI master clock frequency */
#define TWI_FREQUENCY_FREQUENCY_Pos (0UL) /*!< Position of FREQUENCY field. */
#define TWI_FREQUENCY_FREQUENCY_Msk (0xFFFFFFFFUL << TWI_FREQUENCY_FREQUENCY_Pos) /*!< Bit mask of FREQUENCY field. */
#define TWI_FREQUENCY_FREQUENCY_K100 (0x01980000UL) /*!< 100 kbps */
#define TWI_FREQUENCY_FREQUENCY_K250 (0x04000000UL) /*!< 250 kbps */
#define TWI_FREQUENCY_FREQUENCY_K400 (0x06680000UL) /*!< 400 kbps (actual rate 410.256 kbps) */

/* Register: TWI_ADDRESS */
/* Description: Address used in the TWI transfer */

/* Bits 6..0 : Address used in the TWI transfer */
#define TWI_ADDRESS_ADDRESS_Pos (0UL) /*!< Position of ADDRESS field. */
#define TWI_ADDRESS_ADDRESS_Msk (0x7FUL << TWI_ADDRESS_ADDRESS_Pos) /*!< Bit mask of ADDRESS field. */


/* Peripheral: TWIM */
/* Description: I2C compatible Two-Wire Master Interface with EasyDMA 0 */

/* Register: TWIM_SHORTS */
/* Description: Shortcut register */

/* Bit 12 : Shortcut between LASTRX event and STOP task */
#define TWIM_SHORTS_LASTRX_STOP_Pos (12UL) /*!< Position of LASTRX_STOP field. */
#define TWIM_SHORTS_LASTRX_STOP_Msk (0x1UL << TWIM_SHORTS_LASTRX_STOP_Pos) /*!< Bit mask of LASTRX_STOP field. */
#define TWIM_SHORTS_LASTRX_STOP_Disabled (0UL) /*!< Disable shortcut */
#define TWIM_SHORTS_LASTRX_STOP_Enabled (1UL) /*!< Enable shortcut */

/* Bit 10 : Shortcut between LASTRX event and STARTTX task */
#define TWIM_SHORTS_LASTRX_STARTTX_Pos (10UL) /*!< Position of LASTRX_STARTTX field. */
#define TWIM_SHORTS_LASTRX_STARTTX_Msk (0x1UL << TWIM_SHORTS_LASTRX_STARTTX_Pos) /*!< Bit mask of LASTRX_STARTTX field. */
#define TWIM_SHORTS_LASTRX_STARTTX_Disabled (0UL) /*!< Disable shortcut */
#define TWIM_SHORTS_LASTRX_STARTTX_Enabled (1UL) /*!< Enable shortcut */

/* Bit 9 : Shortcut between LASTTX event and STOP task */
#define TWIM_SHORTS_LASTTX_STOP_Pos (9UL) /*!< Position of LASTTX_STOP field. */
#define TWIM_SHORTS_LASTTX_STOP_Msk (0x1UL << TWIM_SHORTS_LASTTX_STOP_Pos) /*!< Bit mask of LASTTX_STOP field. */
#define TWIM_SHORTS_LASTTX_STOP_Disabled (0UL) /*!< Disable shortcut */
#define TWIM_SHORTS_LASTTX_STOP_Enabled (1UL) /*!< Enable shortcut */

/* Bit 8 : Shortcut between LASTTX event and SUSPEND task */
#define TWIM_SHORTS_LASTTX_SUSPEND_Pos (8UL) /*!< Position of LASTTX_SUSPEND field. */
#define TWIM_SHORTS_LASTTX_SUSPEND_Msk (0x1UL << TWIM_SHORTS_LASTTX_SUSPEND_Pos) /*!< Bit mask of LASTTX_SUSPEND field. */
#define TWIM_SHORTS_LASTTX_SUSPEND_Disabled (0UL) /*!< Disable shortcut */
#define TWIM_SHORTS_LASTTX_SUSPEND_Enabled (1UL) /*!< Enable shortcut */

/* Bit 7 : Shortcut between LASTTX event and STARTRX task */
#define TWIM_SHORTS_LASTTX_STARTRX_Pos (7UL) /*!< Position of LASTTX_STARTRX field. */
#define TWIM_SHORTS_LASTTX_STARTRX_Msk (0x1UL << TWIM_SHORTS_LASTTX_STARTRX_Pos) /*!< Bit mask of LASTTX_STARTRX field. */
#define TWIM_SHORTS_LASTTX_STARTRX_Disabled (0UL) /*!< Disable shortcut */
#define TWIM_SHORTS_LASTTX_STARTRX_Enabled (1UL) /*!< Enable shortcut */

/* Register: TWIM_INTEN */
/* Description: Enable or disable interrupt */

/* Bit 24 : Enable or disable interrupt for LASTTX event */
#define TWIM_INTEN_LASTTX_Pos (24UL) /*!< Position of LASTTX field. */
#define TWIM_INTEN_LASTTX_Msk (0x1UL << TWIM_INTEN_LASTTX_Pos) /*!< Bit mask of LASTTX field. */
#define TWIM_INTEN_LASTTX_Disabled (0UL) /*!< Disable */
#define TWIM_INTEN_LASTTX_Enabled (1UL) /*!< Enable */

/* Bit 23 : Enable or disable interrupt for LASTRX event */
#define TWIM_INTEN_LASTRX_Pos (23UL) /*!< Position of LASTRX field. */
#define TWIM_INTEN_LASTRX_Msk (0x1UL << TWIM_INTEN_LASTRX_Pos) /*!< Bit mask of LASTRX field. */
#define TWIM_INTEN_LASTRX_Disabled (0UL) /*!< Disable */
#define TWIM_INTEN_LASTRX_Enabled (1UL) /*!< Enable */

/* Bit 20 : Enable or disable interrupt for TXSTARTED event */
#define TWIM_INTEN_TXSTARTED_Pos (20UL) /*!< Position of TXSTARTED field. */
#define TWIM_INTEN_TXSTARTED_Msk (0x1UL << TWIM_INTEN_TXSTARTED_Pos) /*!< Bit mask of TXSTARTED field. */
#define TWIM_INTEN_TXSTARTED_Disabled (0UL) /*!< Disable */
#define TWIM_INTEN_TXSTARTED_Enabled (1UL) /*!< Enable */

/* Bit 19 : Enable or disable interrupt for RXSTARTED event */
#define TWIM_INTEN_RXSTARTED_Pos (19UL) /*!< Position of RXSTARTED field. */
#define TWIM_INTEN_RXSTARTED_Msk (0x1UL << TWIM_INTEN_RXSTARTED_Pos) /*!< Bit mask of RXSTARTED field. */
#define TWIM_INTEN_RXSTARTED_Disabled (0UL) /*!< Disable */
#define TWIM_INTEN_RXSTARTED_Enabled (1UL) /*!< Enable */

/* Bit 18 : Enable or disable interrupt for SUSPENDED event */
#define TWIM_INTEN_SUSPENDED_Pos (18UL) /*!< Position of SUSPENDED field. */
#define TWIM_INTEN_SUSPENDED_Msk (0x1UL << TWIM_INTEN_SUSPENDED_Pos) /*!< Bit mask of SUSPENDED field. */
#define TWIM_INTEN_SUSPENDED_Disabled (0UL) /*!< Disable */
#define TWIM_INTEN_SUSPENDED_Enabled (1UL) /*!< Enable */

/* Bit 9 : Enable or disable interrupt for ERROR event */
#define TWIM_INTEN_ERROR_Pos (9UL) /*!< Position of ERROR field. */
#define TWIM_INTEN_ERROR_Msk (0x1UL << TWIM_INTEN_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define TWIM_INTEN_ERROR_Disabled (0UL) /*!< Disable */
#define TWIM_INTEN_ERROR_Enabled (1UL) /*!< Enable */

/* Bit 1 : Enable or disable interrupt for STOPPED event */
#define TWIM_INTEN_STOPPED_Pos (1UL) /*!< Position of STOPPED field. */
#define TWIM_INTEN_STOPPED_Msk (0x1UL << TWIM_INTEN_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define TWIM_INTEN_STOPPED_Disabled (0UL) /*!< Disable */
#define TWIM_INTEN_STOPPED_Enabled (1UL) /*!< Enable */

/* Register: TWIM_INTENSET */
/* Description: Enable interrupt */

/* Bit 24 : Write '1' to Enable interrupt for LASTTX event */
#define TWIM_INTENSET_LASTTX_Pos (24UL) /*!< Position of LASTTX field. */
#define TWIM_INTENSET_LASTTX_Msk (0x1UL << TWIM_INTENSET_LASTTX_Pos) /*!< Bit mask of LASTTX field. */
#define TWIM_INTENSET_LASTTX_Disabled (0UL) /*!< Read: Disabled */
#define TWIM_INTENSET_LASTTX_Enabled (1UL) /*!< Read: Enabled */
#define TWIM_INTENSET_LASTTX_Set (1UL) /*!< Enable */

/* Bit 23 : Write '1' to Enable interrupt for LASTRX event */
#define TWIM_INTENSET_LASTRX_Pos (23UL) /*!< Position of LASTRX field. */
#define TWIM_INTENSET_LASTRX_Msk (0x1UL << TWIM_INTENSET_LASTRX_Pos) /*!< Bit mask of LASTRX field. */
#define TWIM_INTENSET_LASTRX_Disabled (0UL) /*!< Read: Disabled */
#define TWIM_INTENSET_LASTRX_Enabled (1UL) /*!< Read: Enabled */
#define TWIM_INTENSET_LASTRX_Set (1UL) /*!< Enable */

/* Bit 20 : Write '1' to Enable interrupt for TXSTARTED event */
#define TWIM_INTENSET_TXSTARTED_Pos (20UL) /*!< Position of TXSTARTED field. */
#define TWIM_INTENSET_TXSTARTED_Msk (0x1UL << TWIM_INTENSET_TXSTARTED_Pos) /*!< Bit mask of TXSTARTED field. */
#define TWIM_INTENSET_TXSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define TWIM_INTENSET_TXSTARTED_Enabled (1UL) /*!< Read: Enabled */
#define TWIM_INTENSET_TXSTARTED_Set (1UL) /*!< Enable */

/* Bit 19 : Write '1' to Enable interrupt for RXSTARTED event */
#define TWIM_INTENSET_RXSTARTED_Pos (19UL) /*!< Position of RXSTARTED field. */
#define TWIM_INTENSET_RXSTARTED_Msk (0x1UL << TWIM_INTENSET_RXSTARTED_Pos) /*!< Bit mask of RXSTARTED field. */
#define TWIM_INTENSET_RXSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define TWIM_INTENSET_RXSTARTED_Enabled (1UL) /*!< Read: Enabled */
#define TWIM_INTENSET_RXSTARTED_Set (1UL) /*!< Enable */

/* Bit 18 : Write '1' to Enable interrupt for SUSPENDED event */
#define TWIM_INTENSET_SUSPENDED_Pos (18UL) /*!< Position of SUSPENDED field. */
#define TWIM_INTENSET_SUSPENDED_Msk (0x1UL << TWIM_INTENSET_SUSPENDED_Pos) /*!< Bit mask of SUSPENDED field. */
#define TWIM_INTENSET_SUSPENDED_Disabled (0UL) /*!< Read: Disabled */
#define TWIM_INTENSET_SUSPENDED_Enabled (1UL) /*!< Read: Enabled */
#define TWIM_INTENSET_SUSPENDED_Set (1UL) /*!< Enable */

/* Bit 9 : Write '1' to Enable interrupt for ERROR event */
#define TWIM_INTENSET_ERROR_Pos (9UL) /*!< Position of ERROR field. */
#define TWIM_INTENSET_ERROR_Msk (0x1UL << TWIM_INTENSET_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define TWIM_INTENSET_ERROR_Disabled (0UL) /*!< Read: Disabled */
#define TWIM_INTENSET_ERROR_Enabled (1UL) /*!< Read: Enabled */
#define TWIM_INTENSET_ERROR_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable interrupt for STOPPED event */
#define TWIM_INTENSET_STOPPED_Pos (1UL) /*!< Position of STOPPED field. */
#define TWIM_INTENSET_STOPPED_Msk (0x1UL << TWIM_INTENSET_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define TWIM_INTENSET_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define TWIM_INTENSET_STOPPED_Enabled (1UL) /*!< Read: Enabled */
#define TWIM_INTENSET_STOPPED_Set (1UL) /*!< Enable */

/* Register: TWIM_INTENCLR */
/* Description: Disable interrupt */

/* Bit 24 : Write '1' to Disable interrupt for LASTTX event */
#define TWIM_INTENCLR_LASTTX_Pos (24UL) /*!< Position of LASTTX field. */
#define TWIM_INTENCLR_LASTTX_Msk (0x1UL << TWIM_INTENCLR_LASTTX_Pos) /*!< Bit mask of LASTTX field. */
#define TWIM_INTENCLR_LASTTX_Disabled (0UL) /*!< Read: Disabled */
#define TWIM_INTENCLR_LASTTX_Enabled (1UL) /*!< Read: Enabled */
#define TWIM_INTENCLR_LASTTX_Clear (1UL) /*!< Disable */

/* Bit 23 : Write '1' to Disable interrupt for LASTRX event */
#define TWIM_INTENCLR_LASTRX_Pos (23UL) /*!< Position of LASTRX field. */
#define TWIM_INTENCLR_LASTRX_Msk (0x1UL << TWIM_INTENCLR_LASTRX_Pos) /*!< Bit mask of LASTRX field. */
#define TWIM_INTENCLR_LASTRX_Disabled (0UL) /*!< Read: Disabled */
#define TWIM_INTENCLR_LASTRX_Enabled (1UL) /*!< Read: Enabled */
#define TWIM_INTENCLR_LASTRX_Clear (1UL) /*!< Disable */

/* Bit 20 : Write '1' to Disable interrupt for TXSTARTED event */
#define TWIM_INTENCLR_TXSTARTED_Pos (20UL) /*!< Position of TXSTARTED field. */
#define TWIM_INTENCLR_TXSTARTED_Msk (0x1UL << TWIM_INTENCLR_TXSTARTED_Pos) /*!< Bit mask of TXSTARTED field. */
#define TWIM_INTENCLR_TXSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define TWIM_INTENCLR_TXSTARTED_Enabled (1UL) /*!< Read: Enabled */
#define TWIM_INTENCLR_TXSTARTED_Clear (1UL) /*!< Disable */

/* Bit 19 : Write '1' to Disable interrupt for RXSTARTED event */
#define TWIM_INTENCLR_RXSTARTED_Pos (19UL) /*!< Position of RXSTARTED field. */
#define TWIM_INTENCLR_RXSTARTED_Msk (0x1UL << TWIM_INTENCLR_RXSTARTED_Pos) /*!< Bit mask of RXSTARTED field. */
#define TWIM_INTENCLR_RXSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define TWIM_INTENCLR_RXSTARTED_Enabled (1UL) /*!< Read: Enabled */
#define TWIM_INTENCLR_RXSTARTED_Clear (1UL) /*!< Disable */

/* Bit 18 : Write '1' to Disable interrupt for SUSPENDED event */
#define TWIM_INTENCLR_SUSPENDED_Pos (18UL) /*!< Position of SUSPENDED field. */
#define TWIM_INTENCLR_SUSPENDED_Msk (0x1UL << TWIM_INTENCLR_SUSPENDED_Pos) /*!< Bit mask of SUSPENDED field. */
#define TWIM_INTENCLR_SUSPENDED_Disabled (0UL) /*!< Read: Disabled */
#define TWIM_INTENCLR_SUSPENDED_Enabled (1UL) /*!< Read: Enabled */
#define TWIM_INTENCLR_SUSPENDED_Clear (1UL) /*!< Disable */

/* Bit 9 : Write '1' to Disable interrupt for ERROR event */
#define TWIM_INTENCLR_ERROR_Pos (9UL) /*!< Position of ERROR field. */
#define TWIM_INTENCLR_ERROR_Msk (0x1UL << TWIM_INTENCLR_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define TWIM_INTENCLR_ERROR_Disabled (0UL) /*!< Read: Disabled */
#define TWIM_INTENCLR_ERROR_Enabled (1UL) /*!< Read: Enabled */
#define TWIM_INTENCLR_ERROR_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable interrupt for STOPPED event */
#define TWIM_INTENCLR_STOPPED_Pos (1UL) /*!< Position of STOPPED field. */
#define TWIM_INTENCLR_STOPPED_Msk (0x1UL << TWIM_INTENCLR_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define TWIM_INTENCLR_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define TWIM_INTENCLR_STOPPED_Enabled (1UL) /*!< Read: Enabled */
#define TWIM_INTENCLR_STOPPED_Clear (1UL) /*!< Disable */

/* Register: TWIM_ERRORSRC */
/* Description: Error source */

/* Bit 2 : NACK received after sending a data byte (write '1' to clear) */
#define TWIM_ERRORSRC_DNACK_Pos (2UL) /*!< Position of DNACK field. */
#define TWIM_ERRORSRC_DNACK_Msk (0x1UL << TWIM_ERRORSRC_DNACK_Pos) /*!< Bit mask of DNACK field. */
#define TWIM_ERRORSRC_DNACK_NotReceived (0UL) /*!< Error did not occur */
#define TWIM_ERRORSRC_DNACK_Received (1UL) /*!< Error occurred */

/* Bit 1 : NACK received after sending the address (write '1' to clear) */
#define TWIM_ERRORSRC_ANACK_Pos (1UL) /*!< Position of ANACK field. */
#define TWIM_ERRORSRC_ANACK_Msk (0x1UL << TWIM_ERRORSRC_ANACK_Pos) /*!< Bit mask of ANACK field. */
#define TWIM_ERRORSRC_ANACK_NotReceived (0UL) /*!< Error did not occur */
#define TWIM_ERRORSRC_ANACK_Received (1UL) /*!< Error occurred */

/* Bit 0 : Overrun error */
#define TWIM_ERRORSRC_OVERRUN_Pos (0UL) /*!< Position of OVERRUN field. */
#define TWIM_ERRORSRC_OVERRUN_Msk (0x1UL << TWIM_ERRORSRC_OVERRUN_Pos) /*!< Bit mask of OVERRUN field. */
#define TWIM_ERRORSRC_OVERRUN_NotReceived (0UL) /*!< Error did not occur */
#define TWIM_ERRORSRC_OVERRUN_Received (1UL) /*!< Error occurred */

/* Register: TWIM_ENABLE */
/* Description: Enable TWIM */

/* Bits 3..0 : Enable or disable TWIM */
#define TWIM_ENABLE_ENABLE_Pos (0UL) /*!< Position of ENABLE field. */
#define TWIM_ENABLE_ENABLE_Msk (0xFUL << TWIM_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define TWIM_ENABLE_ENABLE_Disabled (0UL) /*!< Disable TWIM */
#define TWIM_ENABLE_ENABLE_Enabled (6UL) /*!< Enable TWIM */

/* Register: TWIM_PSEL_SCL */
/* Description: Pin select for SCL signal */

/* Bit 31 : Connection */
#define TWIM_PSEL_SCL_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define TWIM_PSEL_SCL_CONNECT_Msk (0x1UL << TWIM_PSEL_SCL_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define TWIM_PSEL_SCL_CONNECT_Connected (0UL) /*!< Connect */
#define TWIM_PSEL_SCL_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define TWIM_PSEL_SCL_PORT_Pos (5UL) /*!< Position of PORT field. */
#define TWIM_PSEL_SCL_PORT_Msk (0x3UL << TWIM_PSEL_SCL_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define TWIM_PSEL_SCL_PIN_Pos (0UL) /*!< Position of PIN field. */
#define TWIM_PSEL_SCL_PIN_Msk (0x1FUL << TWIM_PSEL_SCL_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: TWIM_PSEL_SDA */
/* Description: Pin select for SDA signal */

/* Bit 31 : Connection */
#define TWIM_PSEL_SDA_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define TWIM_PSEL_SDA_CONNECT_Msk (0x1UL << TWIM_PSEL_SDA_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define TWIM_PSEL_SDA_CONNECT_Connected (0UL) /*!< Connect */
#define TWIM_PSEL_SDA_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define TWIM_PSEL_SDA_PORT_Pos (5UL) /*!< Position of PORT field. */
#define TWIM_PSEL_SDA_PORT_Msk (0x3UL << TWIM_PSEL_SDA_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define TWIM_PSEL_SDA_PIN_Pos (0UL) /*!< Position of PIN field. */
#define TWIM_PSEL_SDA_PIN_Msk (0x1FUL << TWIM_PSEL_SDA_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: TWIM_FREQUENCY */
/* Description: TWI frequency. Accuracy depends on the HFCLK source selected. */

/* Bits 31..0 : TWI master clock frequency */
#define TWIM_FREQUENCY_FREQUENCY_Pos (0UL) /*!< Position of FREQUENCY field. */
#define TWIM_FREQUENCY_FREQUENCY_Msk (0xFFFFFFFFUL << TWIM_FREQUENCY_FREQUENCY_Pos) /*!< Bit mask of FREQUENCY field. */
#define TWIM_FREQUENCY_FREQUENCY_K100 (0x01980000UL) /*!< 100 kbps */
#define TWIM_FREQUENCY_FREQUENCY_K250 (0x04000000UL) /*!< 250 kbps */
#define TWIM_FREQUENCY_FREQUENCY_K400 (0x06400000UL) /*!< 400 kbps */

/* Register: TWIM_RXD_PTR */
/* Description: Data pointer */

/* Bits 31..0 : Data pointer */
#define TWIM_RXD_PTR_PTR_Pos (0UL) /*!< Position of PTR field. */
#define TWIM_RXD_PTR_PTR_Msk (0xFFFFFFFFUL << TWIM_RXD_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: TWIM_RXD_MAXCNT */
/* Description: Maximum number of bytes in receive buffer */

/* Bits 7..0 : Maximum number of bytes in receive buffer */
#define TWIM_RXD_MAXCNT_MAXCNT_Pos (0UL) /*!< Position of MAXCNT field. */
#define TWIM_RXD_MAXCNT_MAXCNT_Msk (0xFFUL << TWIM_RXD_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: TWIM_RXD_AMOUNT */
/* Description: Number of bytes transferred in the last transaction */

/* Bits 7..0 : Number of bytes transferred in the last transaction. In case of NACK error, includes the NACK'ed byte. */
#define TWIM_RXD_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define TWIM_RXD_AMOUNT_AMOUNT_Msk (0xFFUL << TWIM_RXD_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: TWIM_RXD_LIST */
/* Description: EasyDMA list type */

/* Bits 2..0 : List type */
#define TWIM_RXD_LIST_LIST_Pos (0UL) /*!< Position of LIST field. */
#define TWIM_RXD_LIST_LIST_Msk (0x7UL << TWIM_RXD_LIST_LIST_Pos) /*!< Bit mask of LIST field. */
#define TWIM_RXD_LIST_LIST_Disabled (0UL) /*!< Disable EasyDMA list */
#define TWIM_RXD_LIST_LIST_ArrayList (1UL) /*!< Use array list */

/* Register: TWIM_TXD_PTR */
/* Description: Data pointer */

/* Bits 31..0 : Data pointer */
#define TWIM_TXD_PTR_PTR_Pos (0UL) /*!< Position of PTR field. */
#define TWIM_TXD_PTR_PTR_Msk (0xFFFFFFFFUL << TWIM_TXD_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: TWIM_TXD_MAXCNT */
/* Description: Maximum number of bytes in transmit buffer */

/* Bits 7..0 : Maximum number of bytes in transmit buffer */
#define TWIM_TXD_MAXCNT_MAXCNT_Pos (0UL) /*!< Position of MAXCNT field. */
#define TWIM_TXD_MAXCNT_MAXCNT_Msk (0xFFUL << TWIM_TXD_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: TWIM_TXD_AMOUNT */
/* Description: Number of bytes transferred in the last transaction */

/* Bits 7..0 : Number of bytes transferred in the last transaction. In case of NACK error, includes the NACK'ed byte. */
#define TWIM_TXD_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define TWIM_TXD_AMOUNT_AMOUNT_Msk (0xFFUL << TWIM_TXD_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: TWIM_TXD_LIST */
/* Description: EasyDMA list type */

/* Bits 2..0 : List type */
#define TWIM_TXD_LIST_LIST_Pos (0UL) /*!< Position of LIST field. */
#define TWIM_TXD_LIST_LIST_Msk (0x7UL << TWIM_TXD_LIST_LIST_Pos) /*!< Bit mask of LIST field. */
#define TWIM_TXD_LIST_LIST_Disabled (0UL) /*!< Disable EasyDMA list */
#define TWIM_TXD_LIST_LIST_ArrayList (1UL) /*!< Use array list */

/* Register: TWIM_ADDRESS */
/* Description: Address used in the TWI transfer */

/* Bits 6..0 : Address used in the TWI transfer */
#define TWIM_ADDRESS_ADDRESS_Pos (0UL) /*!< Position of ADDRESS field. */
#define TWIM_ADDRESS_ADDRESS_Msk (0x7FUL << TWIM_ADDRESS_ADDRESS_Pos) /*!< Bit mask of ADDRESS field. */


/* Peripheral: TWIS */
/* Description: I2C compatible Two-Wire Slave Interface with EasyDMA 0 */

/* Register: TWIS_SHORTS */
/* Description: Shortcut register */

/* Bit 14 : Shortcut between READ event and SUSPEND task */
#define TWIS_SHORTS_READ_SUSPEND_Pos (14UL) /*!< Position of READ_SUSPEND field. */
#define TWIS_SHORTS_READ_SUSPEND_Msk (0x1UL << TWIS_SHORTS_READ_SUSPEND_Pos) /*!< Bit mask of READ_SUSPEND field. */
#define TWIS_SHORTS_READ_SUSPEND_Disabled (0UL) /*!< Disable shortcut */
#define TWIS_SHORTS_READ_SUSPEND_Enabled (1UL) /*!< Enable shortcut */

/* Bit 13 : Shortcut between WRITE event and SUSPEND task */
#define TWIS_SHORTS_WRITE_SUSPEND_Pos (13UL) /*!< Position of WRITE_SUSPEND field. */
#define TWIS_SHORTS_WRITE_SUSPEND_Msk (0x1UL << TWIS_SHORTS_WRITE_SUSPEND_Pos) /*!< Bit mask of WRITE_SUSPEND field. */
#define TWIS_SHORTS_WRITE_SUSPEND_Disabled (0UL) /*!< Disable shortcut */
#define TWIS_SHORTS_WRITE_SUSPEND_Enabled (1UL) /*!< Enable shortcut */

/* Register: TWIS_INTEN */
/* Description: Enable or disable interrupt */

/* Bit 26 : Enable or disable interrupt for READ event */
#define TWIS_INTEN_READ_Pos (26UL) /*!< Position of READ field. */
#define TWIS_INTEN_READ_Msk (0x1UL << TWIS_INTEN_READ_Pos) /*!< Bit mask of READ field. */
#define TWIS_INTEN_READ_Disabled (0UL) /*!< Disable */
#define TWIS_INTEN_READ_Enabled (1UL) /*!< Enable */

/* Bit 25 : Enable or disable interrupt for WRITE event */
#define TWIS_INTEN_WRITE_Pos (25UL) /*!< Position of WRITE field. */
#define TWIS_INTEN_WRITE_Msk (0x1UL << TWIS_INTEN_WRITE_Pos) /*!< Bit mask of WRITE field. */
#define TWIS_INTEN_WRITE_Disabled (0UL) /*!< Disable */
#define TWIS_INTEN_WRITE_Enabled (1UL) /*!< Enable */

/* Bit 20 : Enable or disable interrupt for TXSTARTED event */
#define TWIS_INTEN_TXSTARTED_Pos (20UL) /*!< Position of TXSTARTED field. */
#define TWIS_INTEN_TXSTARTED_Msk (0x1UL << TWIS_INTEN_TXSTARTED_Pos) /*!< Bit mask of TXSTARTED field. */
#define TWIS_INTEN_TXSTARTED_Disabled (0UL) /*!< Disable */
#define TWIS_INTEN_TXSTARTED_Enabled (1UL) /*!< Enable */

/* Bit 19 : Enable or disable interrupt for RXSTARTED event */
#define TWIS_INTEN_RXSTARTED_Pos (19UL) /*!< Position of RXSTARTED field. */
#define TWIS_INTEN_RXSTARTED_Msk (0x1UL << TWIS_INTEN_RXSTARTED_Pos) /*!< Bit mask of RXSTARTED field. */
#define TWIS_INTEN_RXSTARTED_Disabled (0UL) /*!< Disable */
#define TWIS_INTEN_RXSTARTED_Enabled (1UL) /*!< Enable */

/* Bit 9 : Enable or disable interrupt for ERROR event */
#define TWIS_INTEN_ERROR_Pos (9UL) /*!< Position of ERROR field. */
#define TWIS_INTEN_ERROR_Msk (0x1UL << TWIS_INTEN_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define TWIS_INTEN_ERROR_Disabled (0UL) /*!< Disable */
#define TWIS_INTEN_ERROR_Enabled (1UL) /*!< Enable */

/* Bit 1 : Enable or disable interrupt for STOPPED event */
#define TWIS_INTEN_STOPPED_Pos (1UL) /*!< Position of STOPPED field. */
#define TWIS_INTEN_STOPPED_Msk (0x1UL << TWIS_INTEN_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define TWIS_INTEN_STOPPED_Disabled (0UL) /*!< Disable */
#define TWIS_INTEN_STOPPED_Enabled (1UL) /*!< Enable */

/* Register: TWIS_INTENSET */
/* Description: Enable interrupt */

/* Bit 26 : Write '1' to Enable interrupt for READ event */
#define TWIS_INTENSET_READ_Pos (26UL) /*!< Position of READ field. */
#define TWIS_INTENSET_READ_Msk (0x1UL << TWIS_INTENSET_READ_Pos) /*!< Bit mask of READ field. */
#define TWIS_INTENSET_READ_Disabled (0UL) /*!< Read: Disabled */
#define TWIS_INTENSET_READ_Enabled (1UL) /*!< Read: Enabled */
#define TWIS_INTENSET_READ_Set (1UL) /*!< Enable */

/* Bit 25 : Write '1' to Enable interrupt for WRITE event */
#define TWIS_INTENSET_WRITE_Pos (25UL) /*!< Position of WRITE field. */
#define TWIS_INTENSET_WRITE_Msk (0x1UL << TWIS_INTENSET_WRITE_Pos) /*!< Bit mask of WRITE field. */
#define TWIS_INTENSET_WRITE_Disabled (0UL) /*!< Read: Disabled */
#define TWIS_INTENSET_WRITE_Enabled (1UL) /*!< Read: Enabled */
#define TWIS_INTENSET_WRITE_Set (1UL) /*!< Enable */

/* Bit 20 : Write '1' to Enable interrupt for TXSTARTED event */
#define TWIS_INTENSET_TXSTARTED_Pos (20UL) /*!< Position of TXSTARTED field. */
#define TWIS_INTENSET_TXSTARTED_Msk (0x1UL << TWIS_INTENSET_TXSTARTED_Pos) /*!< Bit mask of TXSTARTED field. */
#define TWIS_INTENSET_TXSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define TWIS_INTENSET_TXSTARTED_Enabled (1UL) /*!< Read: Enabled */
#define TWIS_INTENSET_TXSTARTED_Set (1UL) /*!< Enable */

/* Bit 19 : Write '1' to Enable interrupt for RXSTARTED event */
#define TWIS_INTENSET_RXSTARTED_Pos (19UL) /*!< Position of RXSTARTED field. */
#define TWIS_INTENSET_RXSTARTED_Msk (0x1UL << TWIS_INTENSET_RXSTARTED_Pos) /*!< Bit mask of RXSTARTED field. */
#define TWIS_INTENSET_RXSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define TWIS_INTENSET_RXSTARTED_Enabled (1UL) /*!< Read: Enabled */
#define TWIS_INTENSET_RXSTARTED_Set (1UL) /*!< Enable */

/* Bit 9 : Write '1' to Enable interrupt for ERROR event */
#define TWIS_INTENSET_ERROR_Pos (9UL) /*!< Position of ERROR field. */
#define TWIS_INTENSET_ERROR_Msk (0x1UL << TWIS_INTENSET_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define TWIS_INTENSET_ERROR_Disabled (0UL) /*!< Read: Disabled */
#define TWIS_INTENSET_ERROR_Enabled (1UL) /*!< Read: Enabled */
#define TWIS_INTENSET_ERROR_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable interrupt for STOPPED event */
#define TWIS_INTENSET_STOPPED_Pos (1UL) /*!< Position of STOPPED field. */
#define TWIS_INTENSET_STOPPED_Msk (0x1UL << TWIS_INTENSET_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define TWIS_INTENSET_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define TWIS_INTENSET_STOPPED_Enabled (1UL) /*!< Read: Enabled */
#define TWIS_INTENSET_STOPPED_Set (1UL) /*!< Enable */

/* Register: TWIS_INTENCLR */
/* Description: Disable interrupt */

/* Bit 26 : Write '1' to Disable interrupt for READ event */
#define TWIS_INTENCLR_READ_Pos (26UL) /*!< Position of READ field. */
#define TWIS_INTENCLR_READ_Msk (0x1UL << TWIS_INTENCLR_READ_Pos) /*!< Bit mask of READ field. */
#define TWIS_INTENCLR_READ_Disabled (0UL) /*!< Read: Disabled */
#define TWIS_INTENCLR_READ_Enabled (1UL) /*!< Read: Enabled */
#define TWIS_INTENCLR_READ_Clear (1UL) /*!< Disable */

/* Bit 25 : Write '1' to Disable interrupt for WRITE event */
#define TWIS_INTENCLR_WRITE_Pos (25UL) /*!< Position of WRITE field. */
#define TWIS_INTENCLR_WRITE_Msk (0x1UL << TWIS_INTENCLR_WRITE_Pos) /*!< Bit mask of WRITE field. */
#define TWIS_INTENCLR_WRITE_Disabled (0UL) /*!< Read: Disabled */
#define TWIS_INTENCLR_WRITE_Enabled (1UL) /*!< Read: Enabled */
#define TWIS_INTENCLR_WRITE_Clear (1UL) /*!< Disable */

/* Bit 20 : Write '1' to Disable interrupt for TXSTARTED event */
#define TWIS_INTENCLR_TXSTARTED_Pos (20UL) /*!< Position of TXSTARTED field. */
#define TWIS_INTENCLR_TXSTARTED_Msk (0x1UL << TWIS_INTENCLR_TXSTARTED_Pos) /*!< Bit mask of TXSTARTED field. */
#define TWIS_INTENCLR_TXSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define TWIS_INTENCLR_TXSTARTED_Enabled (1UL) /*!< Read: Enabled */
#define TWIS_INTENCLR_TXSTARTED_Clear (1UL) /*!< Disable */

/* Bit 19 : Write '1' to Disable interrupt for RXSTARTED event */
#define TWIS_INTENCLR_RXSTARTED_Pos (19UL) /*!< Position of RXSTARTED field. */
#define TWIS_INTENCLR_RXSTARTED_Msk (0x1UL << TWIS_INTENCLR_RXSTARTED_Pos) /*!< Bit mask of RXSTARTED field. */
#define TWIS_INTENCLR_RXSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define TWIS_INTENCLR_RXSTARTED_Enabled (1UL) /*!< Read: Enabled */
#define TWIS_INTENCLR_RXSTARTED_Clear (1UL) /*!< Disable */

/* Bit 9 : Write '1' to Disable interrupt for ERROR event */
#define TWIS_INTENCLR_ERROR_Pos (9UL) /*!< Position of ERROR field. */
#define TWIS_INTENCLR_ERROR_Msk (0x1UL << TWIS_INTENCLR_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define TWIS_INTENCLR_ERROR_Disabled (0UL) /*!< Read: Disabled */
#define TWIS_INTENCLR_ERROR_Enabled (1UL) /*!< Read: Enabled */
#define TWIS_INTENCLR_ERROR_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable interrupt for STOPPED event */
#define TWIS_INTENCLR_STOPPED_Pos (1UL) /*!< Position of STOPPED field. */
#define TWIS_INTENCLR_STOPPED_Msk (0x1UL << TWIS_INTENCLR_STOPPED_Pos) /*!< Bit mask of STOPPED field. */
#define TWIS_INTENCLR_STOPPED_Disabled (0UL) /*!< Read: Disabled */
#define TWIS_INTENCLR_STOPPED_Enabled (1UL) /*!< Read: Enabled */
#define TWIS_INTENCLR_STOPPED_Clear (1UL) /*!< Disable */

/* Register: TWIS_ERRORSRC */
/* Description: Error source */

/* Bit 3 : TX buffer over-read detected, and prevented */
#define TWIS_ERRORSRC_OVERREAD_Pos (3UL) /*!< Position of OVERREAD field. */
#define TWIS_ERRORSRC_OVERREAD_Msk (0x1UL << TWIS_ERRORSRC_OVERREAD_Pos) /*!< Bit mask of OVERREAD field. */
#define TWIS_ERRORSRC_OVERREAD_NotDetected (0UL) /*!< Error did not occur */
#define TWIS_ERRORSRC_OVERREAD_Detected (1UL) /*!< Error occurred */

/* Bit 2 : NACK sent after receiving a data byte */
#define TWIS_ERRORSRC_DNACK_Pos (2UL) /*!< Position of DNACK field. */
#define TWIS_ERRORSRC_DNACK_Msk (0x1UL << TWIS_ERRORSRC_DNACK_Pos) /*!< Bit mask of DNACK field. */
#define TWIS_ERRORSRC_DNACK_NotReceived (0UL) /*!< Error did not occur */
#define TWIS_ERRORSRC_DNACK_Received (1UL) /*!< Error occurred */

/* Bit 0 : RX buffer overflow detected, and prevented */
#define TWIS_ERRORSRC_OVERFLOW_Pos (0UL) /*!< Position of OVERFLOW field. */
#define TWIS_ERRORSRC_OVERFLOW_Msk (0x1UL << TWIS_ERRORSRC_OVERFLOW_Pos) /*!< Bit mask of OVERFLOW field. */
#define TWIS_ERRORSRC_OVERFLOW_NotDetected (0UL) /*!< Error did not occur */
#define TWIS_ERRORSRC_OVERFLOW_Detected (1UL) /*!< Error occurred */

/* Register: TWIS_MATCH */
/* Description: Status register indicating which address had a match */

/* Bit 0 : Which of the addresses in {ADDRESS} matched the incoming address */
#define TWIS_MATCH_MATCH_Pos (0UL) /*!< Position of MATCH field. */
#define TWIS_MATCH_MATCH_Msk (0x1UL << TWIS_MATCH_MATCH_Pos) /*!< Bit mask of MATCH field. */

/* Register: TWIS_ENABLE */
/* Description: Enable TWIS */

/* Bits 3..0 : Enable or disable TWIS */
#define TWIS_ENABLE_ENABLE_Pos (0UL) /*!< Position of ENABLE field. */
#define TWIS_ENABLE_ENABLE_Msk (0xFUL << TWIS_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define TWIS_ENABLE_ENABLE_Disabled (0UL) /*!< Disable TWIS */
#define TWIS_ENABLE_ENABLE_Enabled (9UL) /*!< Enable TWIS */

/* Register: TWIS_PSEL_SCL */
/* Description: Pin select for SCL signal */

/* Bit 31 : Connection */
#define TWIS_PSEL_SCL_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define TWIS_PSEL_SCL_CONNECT_Msk (0x1UL << TWIS_PSEL_SCL_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define TWIS_PSEL_SCL_CONNECT_Connected (0UL) /*!< Connect */
#define TWIS_PSEL_SCL_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define TWIS_PSEL_SCL_PORT_Pos (5UL) /*!< Position of PORT field. */
#define TWIS_PSEL_SCL_PORT_Msk (0x3UL << TWIS_PSEL_SCL_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define TWIS_PSEL_SCL_PIN_Pos (0UL) /*!< Position of PIN field. */
#define TWIS_PSEL_SCL_PIN_Msk (0x1FUL << TWIS_PSEL_SCL_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: TWIS_PSEL_SDA */
/* Description: Pin select for SDA signal */

/* Bit 31 : Connection */
#define TWIS_PSEL_SDA_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define TWIS_PSEL_SDA_CONNECT_Msk (0x1UL << TWIS_PSEL_SDA_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define TWIS_PSEL_SDA_CONNECT_Connected (0UL) /*!< Connect */
#define TWIS_PSEL_SDA_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define TWIS_PSEL_SDA_PORT_Pos (5UL) /*!< Position of PORT field. */
#define TWIS_PSEL_SDA_PORT_Msk (0x3UL << TWIS_PSEL_SDA_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define TWIS_PSEL_SDA_PIN_Pos (0UL) /*!< Position of PIN field. */
#define TWIS_PSEL_SDA_PIN_Msk (0x1FUL << TWIS_PSEL_SDA_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: TWIS_RXD_PTR */
/* Description: RXD Data pointer */

/* Bits 31..0 : RXD Data pointer */
#define TWIS_RXD_PTR_PTR_Pos (0UL) /*!< Position of PTR field. */
#define TWIS_RXD_PTR_PTR_Msk (0xFFFFFFFFUL << TWIS_RXD_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: TWIS_RXD_MAXCNT */
/* Description: Maximum number of bytes in RXD buffer */

/* Bits 7..0 : Maximum number of bytes in RXD buffer */
#define TWIS_RXD_MAXCNT_MAXCNT_Pos (0UL) /*!< Position of MAXCNT field. */
#define TWIS_RXD_MAXCNT_MAXCNT_Msk (0xFFUL << TWIS_RXD_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: TWIS_RXD_AMOUNT */
/* Description: Number of bytes transferred in the last RXD transaction */

/* Bits 7..0 : Number of bytes transferred in the last RXD transaction */
#define TWIS_RXD_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define TWIS_RXD_AMOUNT_AMOUNT_Msk (0xFFUL << TWIS_RXD_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: TWIS_TXD_PTR */
/* Description: TXD Data pointer */

/* Bits 31..0 : TXD Data pointer */
#define TWIS_TXD_PTR_PTR_Pos (0UL) /*!< Position of PTR field. */
#define TWIS_TXD_PTR_PTR_Msk (0xFFFFFFFFUL << TWIS_TXD_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: TWIS_TXD_MAXCNT */
/* Description: Maximum number of bytes in TXD buffer */

/* Bits 7..0 : Maximum number of bytes in TXD buffer */
#define TWIS_TXD_MAXCNT_MAXCNT_Pos (0UL) /*!< Position of MAXCNT field. */
#define TWIS_TXD_MAXCNT_MAXCNT_Msk (0xFFUL << TWIS_TXD_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: TWIS_TXD_AMOUNT */
/* Description: Number of bytes transferred in the last TXD transaction */

/* Bits 7..0 : Number of bytes transferred in the last TXD transaction */
#define TWIS_TXD_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define TWIS_TXD_AMOUNT_AMOUNT_Msk (0xFFUL << TWIS_TXD_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: TWIS_ADDRESS */
/* Description: Description collection[0]:  TWI slave address 0 */

/* Bits 6..0 : TWI slave address */
#define TWIS_ADDRESS_ADDRESS_Pos (0UL) /*!< Position of ADDRESS field. */
#define TWIS_ADDRESS_ADDRESS_Msk (0x7FUL << TWIS_ADDRESS_ADDRESS_Pos) /*!< Bit mask of ADDRESS field. */

/* Register: TWIS_CONFIG */
/* Description: Configuration register for the address match mechanism */

/* Bit 1 : Enable or disable address matching on ADDRESS[1] */
#define TWIS_CONFIG_ADDRESS1_Pos (1UL) /*!< Position of ADDRESS1 field. */
#define TWIS_CONFIG_ADDRESS1_Msk (0x1UL << TWIS_CONFIG_ADDRESS1_Pos) /*!< Bit mask of ADDRESS1 field. */
#define TWIS_CONFIG_ADDRESS1_Disabled (0UL) /*!< Disabled */
#define TWIS_CONFIG_ADDRESS1_Enabled (1UL) /*!< Enabled */

/* Bit 0 : Enable or disable address matching on ADDRESS[0] */
#define TWIS_CONFIG_ADDRESS0_Pos (0UL) /*!< Position of ADDRESS0 field. */
#define TWIS_CONFIG_ADDRESS0_Msk (0x1UL << TWIS_CONFIG_ADDRESS0_Pos) /*!< Bit mask of ADDRESS0 field. */
#define TWIS_CONFIG_ADDRESS0_Disabled (0UL) /*!< Disabled */
#define TWIS_CONFIG_ADDRESS0_Enabled (1UL) /*!< Enabled */

/* Register: TWIS_ORC */
/* Description: Over-read character. Character sent out in case of an over-read of the transmit buffer. */

/* Bits 7..0 : Over-read character. Character sent out in case of an over-read of the transmit buffer. */
#define TWIS_ORC_ORC_Pos (0UL) /*!< Position of ORC field. */
#define TWIS_ORC_ORC_Msk (0xFFUL << TWIS_ORC_ORC_Pos) /*!< Bit mask of ORC field. */


/* Peripheral: UART */
/* Description: Universal Asynchronous Receiver/Transmitter */

/* Register: UART_SHORTS */
/* Description: Shortcut register */

/* Bit 4 : Shortcut between NCTS event and STOPRX task */
#define UART_SHORTS_NCTS_STOPRX_Pos (4UL) /*!< Position of NCTS_STOPRX field. */
#define UART_SHORTS_NCTS_STOPRX_Msk (0x1UL << UART_SHORTS_NCTS_STOPRX_Pos) /*!< Bit mask of NCTS_STOPRX field. */
#define UART_SHORTS_NCTS_STOPRX_Disabled (0UL) /*!< Disable shortcut */
#define UART_SHORTS_NCTS_STOPRX_Enabled (1UL) /*!< Enable shortcut */

/* Bit 3 : Shortcut between CTS event and STARTRX task */
#define UART_SHORTS_CTS_STARTRX_Pos (3UL) /*!< Position of CTS_STARTRX field. */
#define UART_SHORTS_CTS_STARTRX_Msk (0x1UL << UART_SHORTS_CTS_STARTRX_Pos) /*!< Bit mask of CTS_STARTRX field. */
#define UART_SHORTS_CTS_STARTRX_Disabled (0UL) /*!< Disable shortcut */
#define UART_SHORTS_CTS_STARTRX_Enabled (1UL) /*!< Enable shortcut */

/* Register: UART_INTENSET */
/* Description: Enable interrupt */

/* Bit 17 : Write '1' to Enable interrupt for RXTO event */
#define UART_INTENSET_RXTO_Pos (17UL) /*!< Position of RXTO field. */
#define UART_INTENSET_RXTO_Msk (0x1UL << UART_INTENSET_RXTO_Pos) /*!< Bit mask of RXTO field. */
#define UART_INTENSET_RXTO_Disabled (0UL) /*!< Read: Disabled */
#define UART_INTENSET_RXTO_Enabled (1UL) /*!< Read: Enabled */
#define UART_INTENSET_RXTO_Set (1UL) /*!< Enable */

/* Bit 9 : Write '1' to Enable interrupt for ERROR event */
#define UART_INTENSET_ERROR_Pos (9UL) /*!< Position of ERROR field. */
#define UART_INTENSET_ERROR_Msk (0x1UL << UART_INTENSET_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define UART_INTENSET_ERROR_Disabled (0UL) /*!< Read: Disabled */
#define UART_INTENSET_ERROR_Enabled (1UL) /*!< Read: Enabled */
#define UART_INTENSET_ERROR_Set (1UL) /*!< Enable */

/* Bit 7 : Write '1' to Enable interrupt for TXDRDY event */
#define UART_INTENSET_TXDRDY_Pos (7UL) /*!< Position of TXDRDY field. */
#define UART_INTENSET_TXDRDY_Msk (0x1UL << UART_INTENSET_TXDRDY_Pos) /*!< Bit mask of TXDRDY field. */
#define UART_INTENSET_TXDRDY_Disabled (0UL) /*!< Read: Disabled */
#define UART_INTENSET_TXDRDY_Enabled (1UL) /*!< Read: Enabled */
#define UART_INTENSET_TXDRDY_Set (1UL) /*!< Enable */

/* Bit 2 : Write '1' to Enable interrupt for RXDRDY event */
#define UART_INTENSET_RXDRDY_Pos (2UL) /*!< Position of RXDRDY field. */
#define UART_INTENSET_RXDRDY_Msk (0x1UL << UART_INTENSET_RXDRDY_Pos) /*!< Bit mask of RXDRDY field. */
#define UART_INTENSET_RXDRDY_Disabled (0UL) /*!< Read: Disabled */
#define UART_INTENSET_RXDRDY_Enabled (1UL) /*!< Read: Enabled */
#define UART_INTENSET_RXDRDY_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable interrupt for NCTS event */
#define UART_INTENSET_NCTS_Pos (1UL) /*!< Position of NCTS field. */
#define UART_INTENSET_NCTS_Msk (0x1UL << UART_INTENSET_NCTS_Pos) /*!< Bit mask of NCTS field. */
#define UART_INTENSET_NCTS_Disabled (0UL) /*!< Read: Disabled */
#define UART_INTENSET_NCTS_Enabled (1UL) /*!< Read: Enabled */
#define UART_INTENSET_NCTS_Set (1UL) /*!< Enable */

/* Bit 0 : Write '1' to Enable interrupt for CTS event */
#define UART_INTENSET_CTS_Pos (0UL) /*!< Position of CTS field. */
#define UART_INTENSET_CTS_Msk (0x1UL << UART_INTENSET_CTS_Pos) /*!< Bit mask of CTS field. */
#define UART_INTENSET_CTS_Disabled (0UL) /*!< Read: Disabled */
#define UART_INTENSET_CTS_Enabled (1UL) /*!< Read: Enabled */
#define UART_INTENSET_CTS_Set (1UL) /*!< Enable */

/* Register: UART_INTENCLR */
/* Description: Disable interrupt */

/* Bit 17 : Write '1' to Disable interrupt for RXTO event */
#define UART_INTENCLR_RXTO_Pos (17UL) /*!< Position of RXTO field. */
#define UART_INTENCLR_RXTO_Msk (0x1UL << UART_INTENCLR_RXTO_Pos) /*!< Bit mask of RXTO field. */
#define UART_INTENCLR_RXTO_Disabled (0UL) /*!< Read: Disabled */
#define UART_INTENCLR_RXTO_Enabled (1UL) /*!< Read: Enabled */
#define UART_INTENCLR_RXTO_Clear (1UL) /*!< Disable */

/* Bit 9 : Write '1' to Disable interrupt for ERROR event */
#define UART_INTENCLR_ERROR_Pos (9UL) /*!< Position of ERROR field. */
#define UART_INTENCLR_ERROR_Msk (0x1UL << UART_INTENCLR_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define UART_INTENCLR_ERROR_Disabled (0UL) /*!< Read: Disabled */
#define UART_INTENCLR_ERROR_Enabled (1UL) /*!< Read: Enabled */
#define UART_INTENCLR_ERROR_Clear (1UL) /*!< Disable */

/* Bit 7 : Write '1' to Disable interrupt for TXDRDY event */
#define UART_INTENCLR_TXDRDY_Pos (7UL) /*!< Position of TXDRDY field. */
#define UART_INTENCLR_TXDRDY_Msk (0x1UL << UART_INTENCLR_TXDRDY_Pos) /*!< Bit mask of TXDRDY field. */
#define UART_INTENCLR_TXDRDY_Disabled (0UL) /*!< Read: Disabled */
#define UART_INTENCLR_TXDRDY_Enabled (1UL) /*!< Read: Enabled */
#define UART_INTENCLR_TXDRDY_Clear (1UL) /*!< Disable */

/* Bit 2 : Write '1' to Disable interrupt for RXDRDY event */
#define UART_INTENCLR_RXDRDY_Pos (2UL) /*!< Position of RXDRDY field. */
#define UART_INTENCLR_RXDRDY_Msk (0x1UL << UART_INTENCLR_RXDRDY_Pos) /*!< Bit mask of RXDRDY field. */
#define UART_INTENCLR_RXDRDY_Disabled (0UL) /*!< Read: Disabled */
#define UART_INTENCLR_RXDRDY_Enabled (1UL) /*!< Read: Enabled */
#define UART_INTENCLR_RXDRDY_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable interrupt for NCTS event */
#define UART_INTENCLR_NCTS_Pos (1UL) /*!< Position of NCTS field. */
#define UART_INTENCLR_NCTS_Msk (0x1UL << UART_INTENCLR_NCTS_Pos) /*!< Bit mask of NCTS field. */
#define UART_INTENCLR_NCTS_Disabled (0UL) /*!< Read: Disabled */
#define UART_INTENCLR_NCTS_Enabled (1UL) /*!< Read: Enabled */
#define UART_INTENCLR_NCTS_Clear (1UL) /*!< Disable */

/* Bit 0 : Write '1' to Disable interrupt for CTS event */
#define UART_INTENCLR_CTS_Pos (0UL) /*!< Position of CTS field. */
#define UART_INTENCLR_CTS_Msk (0x1UL << UART_INTENCLR_CTS_Pos) /*!< Bit mask of CTS field. */
#define UART_INTENCLR_CTS_Disabled (0UL) /*!< Read: Disabled */
#define UART_INTENCLR_CTS_Enabled (1UL) /*!< Read: Enabled */
#define UART_INTENCLR_CTS_Clear (1UL) /*!< Disable */

/* Register: UART_ERRORSRC */
/* Description: Error source */

/* Bit 3 : Break condition */
#define UART_ERRORSRC_BREAK_Pos (3UL) /*!< Position of BREAK field. */
#define UART_ERRORSRC_BREAK_Msk (0x1UL << UART_ERRORSRC_BREAK_Pos) /*!< Bit mask of BREAK field. */
#define UART_ERRORSRC_BREAK_NotPresent (0UL) /*!< Read: error not present */
#define UART_ERRORSRC_BREAK_Present (1UL) /*!< Read: error present */

/* Bit 2 : Framing error occurred */
#define UART_ERRORSRC_FRAMING_Pos (2UL) /*!< Position of FRAMING field. */
#define UART_ERRORSRC_FRAMING_Msk (0x1UL << UART_ERRORSRC_FRAMING_Pos) /*!< Bit mask of FRAMING field. */
#define UART_ERRORSRC_FRAMING_NotPresent (0UL) /*!< Read: error not present */
#define UART_ERRORSRC_FRAMING_Present (1UL) /*!< Read: error present */

/* Bit 1 : Parity error */
#define UART_ERRORSRC_PARITY_Pos (1UL) /*!< Position of PARITY field. */
#define UART_ERRORSRC_PARITY_Msk (0x1UL << UART_ERRORSRC_PARITY_Pos) /*!< Bit mask of PARITY field. */
#define UART_ERRORSRC_PARITY_NotPresent (0UL) /*!< Read: error not present */
#define UART_ERRORSRC_PARITY_Present (1UL) /*!< Read: error present */

/* Bit 0 : Overrun error */
#define UART_ERRORSRC_OVERRUN_Pos (0UL) /*!< Position of OVERRUN field. */
#define UART_ERRORSRC_OVERRUN_Msk (0x1UL << UART_ERRORSRC_OVERRUN_Pos) /*!< Bit mask of OVERRUN field. */
#define UART_ERRORSRC_OVERRUN_NotPresent (0UL) /*!< Read: error not present */
#define UART_ERRORSRC_OVERRUN_Present (1UL) /*!< Read: error present */

/* Register: UART_ENABLE */
/* Description: Enable UART */

/* Bits 3..0 : Enable or disable UART */
#define UART_ENABLE_ENABLE_Pos (0UL) /*!< Position of ENABLE field. */
#define UART_ENABLE_ENABLE_Msk (0xFUL << UART_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define UART_ENABLE_ENABLE_Disabled (0UL) /*!< Disable UART */
#define UART_ENABLE_ENABLE_Enabled (4UL) /*!< Enable UART */

/* Register: UART_PSEL_RTS */
/* Description: Pin select for RTS */

/* Bit 31 : Connection */
#define UART_PSEL_RTS_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define UART_PSEL_RTS_CONNECT_Msk (0x1UL << UART_PSEL_RTS_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define UART_PSEL_RTS_CONNECT_Connected (0UL) /*!< Connect */
#define UART_PSEL_RTS_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define UART_PSEL_RTS_PORT_Pos (5UL) /*!< Position of PORT field. */
#define UART_PSEL_RTS_PORT_Msk (0x3UL << UART_PSEL_RTS_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define UART_PSEL_RTS_PIN_Pos (0UL) /*!< Position of PIN field. */
#define UART_PSEL_RTS_PIN_Msk (0x1FUL << UART_PSEL_RTS_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: UART_PSEL_TXD */
/* Description: Pin select for TXD */

/* Bit 31 : Connection */
#define UART_PSEL_TXD_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define UART_PSEL_TXD_CONNECT_Msk (0x1UL << UART_PSEL_TXD_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define UART_PSEL_TXD_CONNECT_Connected (0UL) /*!< Connect */
#define UART_PSEL_TXD_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define UART_PSEL_TXD_PORT_Pos (5UL) /*!< Position of PORT field. */
#define UART_PSEL_TXD_PORT_Msk (0x3UL << UART_PSEL_TXD_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define UART_PSEL_TXD_PIN_Pos (0UL) /*!< Position of PIN field. */
#define UART_PSEL_TXD_PIN_Msk (0x1FUL << UART_PSEL_TXD_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: UART_PSEL_CTS */
/* Description: Pin select for CTS */

/* Bit 31 : Connection */
#define UART_PSEL_CTS_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define UART_PSEL_CTS_CONNECT_Msk (0x1UL << UART_PSEL_CTS_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define UART_PSEL_CTS_CONNECT_Connected (0UL) /*!< Connect */
#define UART_PSEL_CTS_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define UART_PSEL_CTS_PORT_Pos (5UL) /*!< Position of PORT field. */
#define UART_PSEL_CTS_PORT_Msk (0x3UL << UART_PSEL_CTS_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define UART_PSEL_CTS_PIN_Pos (0UL) /*!< Position of PIN field. */
#define UART_PSEL_CTS_PIN_Msk (0x1FUL << UART_PSEL_CTS_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: UART_PSEL_RXD */
/* Description: Pin select for RXD */

/* Bit 31 : Connection */
#define UART_PSEL_RXD_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define UART_PSEL_RXD_CONNECT_Msk (0x1UL << UART_PSEL_RXD_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define UART_PSEL_RXD_CONNECT_Connected (0UL) /*!< Connect */
#define UART_PSEL_RXD_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define UART_PSEL_RXD_PORT_Pos (5UL) /*!< Position of PORT field. */
#define UART_PSEL_RXD_PORT_Msk (0x3UL << UART_PSEL_RXD_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define UART_PSEL_RXD_PIN_Pos (0UL) /*!< Position of PIN field. */
#define UART_PSEL_RXD_PIN_Msk (0x1FUL << UART_PSEL_RXD_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: UART_RXD */
/* Description: RXD register */

/* Bits 7..0 : RX data received in previous transfers, double buffered */
#define UART_RXD_RXD_Pos (0UL) /*!< Position of RXD field. */
#define UART_RXD_RXD_Msk (0xFFUL << UART_RXD_RXD_Pos) /*!< Bit mask of RXD field. */

/* Register: UART_TXD */
/* Description: TXD register */

/* Bits 7..0 : TX data to be transferred */
#define UART_TXD_TXD_Pos (0UL) /*!< Position of TXD field. */
#define UART_TXD_TXD_Msk (0xFFUL << UART_TXD_TXD_Pos) /*!< Bit mask of TXD field. */

/* Register: UART_BAUDRATE */
/* Description: Baud rate. Accuracy depends on the HFCLK source selected. */

/* Bits 31..0 : Baud rate */
#define UART_BAUDRATE_BAUDRATE_Pos (0UL) /*!< Position of BAUDRATE field. */
#define UART_BAUDRATE_BAUDRATE_Msk (0xFFFFFFFFUL << UART_BAUDRATE_BAUDRATE_Pos) /*!< Bit mask of BAUDRATE field. */
#define UART_BAUDRATE_BAUDRATE_Baud1200 (0x0004F000UL) /*!< 1200 baud (actual rate: 1205) */
#define UART_BAUDRATE_BAUDRATE_Baud2400 (0x0009D000UL) /*!< 2400 baud (actual rate: 2396) */
#define UART_BAUDRATE_BAUDRATE_Baud4800 (0x0013B000UL) /*!< 4800 baud (actual rate: 4808) */
#define UART_BAUDRATE_BAUDRATE_Baud9600 (0x00275000UL) /*!< 9600 baud (actual rate: 9598) */
#define UART_BAUDRATE_BAUDRATE_Baud14400 (0x003B0000UL) /*!< 14400 baud (actual rate: 14414) */
#define UART_BAUDRATE_BAUDRATE_Baud19200 (0x004EA000UL) /*!< 19200 baud (actual rate: 19208) */
#define UART_BAUDRATE_BAUDRATE_Baud28800 (0x0075F000UL) /*!< 28800 baud (actual rate: 28829) */
#define UART_BAUDRATE_BAUDRATE_Baud31250 (0x00800000UL) /*!< 31250 baud */
#define UART_BAUDRATE_BAUDRATE_Baud38400 (0x009D5000UL) /*!< 38400 baud (actual rate: 38462) */
#define UART_BAUDRATE_BAUDRATE_Baud56000 (0x00E50000UL) /*!< 56000 baud (actual rate: 55944) */
#define UART_BAUDRATE_BAUDRATE_Baud57600 (0x00EBF000UL) /*!< 57600 baud (actual rate: 57762) */
#define UART_BAUDRATE_BAUDRATE_Baud76800 (0x013A9000UL) /*!< 76800 baud (actual rate: 76923) */
#define UART_BAUDRATE_BAUDRATE_Baud115200 (0x01D7E000UL) /*!< 115200 baud (actual rate: 115942) */
#define UART_BAUDRATE_BAUDRATE_Baud230400 (0x03AFB000UL) /*!< 230400 baud (actual rate: 231884) */
#define UART_BAUDRATE_BAUDRATE_Baud250000 (0x04000000UL) /*!< 250000 baud */
#define UART_BAUDRATE_BAUDRATE_Baud460800 (0x075F7000UL) /*!< 460800 baud (actual rate: 470588) */
#define UART_BAUDRATE_BAUDRATE_Baud921600 (0x0EBED000UL) /*!< 921600 baud (actual rate: 941176) */
#define UART_BAUDRATE_BAUDRATE_Baud1M (0x10000000UL) /*!< 1Mega baud */

/* Register: UART_CONFIG */
/* Description: Configuration of parity and hardware flow control */

/* Bits 3..1 : Parity */
#define UART_CONFIG_PARITY_Pos (1UL) /*!< Position of PARITY field. */
#define UART_CONFIG_PARITY_Msk (0x7UL << UART_CONFIG_PARITY_Pos) /*!< Bit mask of PARITY field. */
#define UART_CONFIG_PARITY_Excluded (0x0UL) /*!< Exclude parity bit */
#define UART_CONFIG_PARITY_Included (0x7UL) /*!< Include parity bit */

/* Bit 0 : Hardware flow control */
#define UART_CONFIG_HWFC_Pos (0UL) /*!< Position of HWFC field. */
#define UART_CONFIG_HWFC_Msk (0x1UL << UART_CONFIG_HWFC_Pos) /*!< Bit mask of HWFC field. */
#define UART_CONFIG_HWFC_Disabled (0UL) /*!< Disabled */
#define UART_CONFIG_HWFC_Enabled (1UL) /*!< Enabled */


/* Peripheral: UARTE */
/* Description: UART with EasyDMA 0 */

/* Register: UARTE_SHORTS */
/* Description: Shortcut register */

/* Bit 6 : Shortcut between ENDRX event and STOPRX task */
#define UARTE_SHORTS_ENDRX_STOPRX_Pos (6UL) /*!< Position of ENDRX_STOPRX field. */
#define UARTE_SHORTS_ENDRX_STOPRX_Msk (0x1UL << UARTE_SHORTS_ENDRX_STOPRX_Pos) /*!< Bit mask of ENDRX_STOPRX field. */
#define UARTE_SHORTS_ENDRX_STOPRX_Disabled (0UL) /*!< Disable shortcut */
#define UARTE_SHORTS_ENDRX_STOPRX_Enabled (1UL) /*!< Enable shortcut */

/* Bit 5 : Shortcut between ENDRX event and STARTRX task */
#define UARTE_SHORTS_ENDRX_STARTRX_Pos (5UL) /*!< Position of ENDRX_STARTRX field. */
#define UARTE_SHORTS_ENDRX_STARTRX_Msk (0x1UL << UARTE_SHORTS_ENDRX_STARTRX_Pos) /*!< Bit mask of ENDRX_STARTRX field. */
#define UARTE_SHORTS_ENDRX_STARTRX_Disabled (0UL) /*!< Disable shortcut */
#define UARTE_SHORTS_ENDRX_STARTRX_Enabled (1UL) /*!< Enable shortcut */

/* Register: UARTE_INTEN */
/* Description: Enable or disable interrupt */

/* Bit 22 : Enable or disable interrupt for TXSTOPPED event */
#define UARTE_INTEN_TXSTOPPED_Pos (22UL) /*!< Position of TXSTOPPED field. */
#define UARTE_INTEN_TXSTOPPED_Msk (0x1UL << UARTE_INTEN_TXSTOPPED_Pos) /*!< Bit mask of TXSTOPPED field. */
#define UARTE_INTEN_TXSTOPPED_Disabled (0UL) /*!< Disable */
#define UARTE_INTEN_TXSTOPPED_Enabled (1UL) /*!< Enable */

/* Bit 20 : Enable or disable interrupt for TXSTARTED event */
#define UARTE_INTEN_TXSTARTED_Pos (20UL) /*!< Position of TXSTARTED field. */
#define UARTE_INTEN_TXSTARTED_Msk (0x1UL << UARTE_INTEN_TXSTARTED_Pos) /*!< Bit mask of TXSTARTED field. */
#define UARTE_INTEN_TXSTARTED_Disabled (0UL) /*!< Disable */
#define UARTE_INTEN_TXSTARTED_Enabled (1UL) /*!< Enable */

/* Bit 19 : Enable or disable interrupt for RXSTARTED event */
#define UARTE_INTEN_RXSTARTED_Pos (19UL) /*!< Position of RXSTARTED field. */
#define UARTE_INTEN_RXSTARTED_Msk (0x1UL << UARTE_INTEN_RXSTARTED_Pos) /*!< Bit mask of RXSTARTED field. */
#define UARTE_INTEN_RXSTARTED_Disabled (0UL) /*!< Disable */
#define UARTE_INTEN_RXSTARTED_Enabled (1UL) /*!< Enable */

/* Bit 17 : Enable or disable interrupt for RXTO event */
#define UARTE_INTEN_RXTO_Pos (17UL) /*!< Position of RXTO field. */
#define UARTE_INTEN_RXTO_Msk (0x1UL << UARTE_INTEN_RXTO_Pos) /*!< Bit mask of RXTO field. */
#define UARTE_INTEN_RXTO_Disabled (0UL) /*!< Disable */
#define UARTE_INTEN_RXTO_Enabled (1UL) /*!< Enable */

/* Bit 9 : Enable or disable interrupt for ERROR event */
#define UARTE_INTEN_ERROR_Pos (9UL) /*!< Position of ERROR field. */
#define UARTE_INTEN_ERROR_Msk (0x1UL << UARTE_INTEN_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define UARTE_INTEN_ERROR_Disabled (0UL) /*!< Disable */
#define UARTE_INTEN_ERROR_Enabled (1UL) /*!< Enable */

/* Bit 8 : Enable or disable interrupt for ENDTX event */
#define UARTE_INTEN_ENDTX_Pos (8UL) /*!< Position of ENDTX field. */
#define UARTE_INTEN_ENDTX_Msk (0x1UL << UARTE_INTEN_ENDTX_Pos) /*!< Bit mask of ENDTX field. */
#define UARTE_INTEN_ENDTX_Disabled (0UL) /*!< Disable */
#define UARTE_INTEN_ENDTX_Enabled (1UL) /*!< Enable */

/* Bit 7 : Enable or disable interrupt for TXDRDY event */
#define UARTE_INTEN_TXDRDY_Pos (7UL) /*!< Position of TXDRDY field. */
#define UARTE_INTEN_TXDRDY_Msk (0x1UL << UARTE_INTEN_TXDRDY_Pos) /*!< Bit mask of TXDRDY field. */
#define UARTE_INTEN_TXDRDY_Disabled (0UL) /*!< Disable */
#define UARTE_INTEN_TXDRDY_Enabled (1UL) /*!< Enable */

/* Bit 4 : Enable or disable interrupt for ENDRX event */
#define UARTE_INTEN_ENDRX_Pos (4UL) /*!< Position of ENDRX field. */
#define UARTE_INTEN_ENDRX_Msk (0x1UL << UARTE_INTEN_ENDRX_Pos) /*!< Bit mask of ENDRX field. */
#define UARTE_INTEN_ENDRX_Disabled (0UL) /*!< Disable */
#define UARTE_INTEN_ENDRX_Enabled (1UL) /*!< Enable */

/* Bit 2 : Enable or disable interrupt for RXDRDY event */
#define UARTE_INTEN_RXDRDY_Pos (2UL) /*!< Position of RXDRDY field. */
#define UARTE_INTEN_RXDRDY_Msk (0x1UL << UARTE_INTEN_RXDRDY_Pos) /*!< Bit mask of RXDRDY field. */
#define UARTE_INTEN_RXDRDY_Disabled (0UL) /*!< Disable */
#define UARTE_INTEN_RXDRDY_Enabled (1UL) /*!< Enable */

/* Bit 1 : Enable or disable interrupt for NCTS event */
#define UARTE_INTEN_NCTS_Pos (1UL) /*!< Position of NCTS field. */
#define UARTE_INTEN_NCTS_Msk (0x1UL << UARTE_INTEN_NCTS_Pos) /*!< Bit mask of NCTS field. */
#define UARTE_INTEN_NCTS_Disabled (0UL) /*!< Disable */
#define UARTE_INTEN_NCTS_Enabled (1UL) /*!< Enable */

/* Bit 0 : Enable or disable interrupt for CTS event */
#define UARTE_INTEN_CTS_Pos (0UL) /*!< Position of CTS field. */
#define UARTE_INTEN_CTS_Msk (0x1UL << UARTE_INTEN_CTS_Pos) /*!< Bit mask of CTS field. */
#define UARTE_INTEN_CTS_Disabled (0UL) /*!< Disable */
#define UARTE_INTEN_CTS_Enabled (1UL) /*!< Enable */

/* Register: UARTE_INTENSET */
/* Description: Enable interrupt */

/* Bit 22 : Write '1' to Enable interrupt for TXSTOPPED event */
#define UARTE_INTENSET_TXSTOPPED_Pos (22UL) /*!< Position of TXSTOPPED field. */
#define UARTE_INTENSET_TXSTOPPED_Msk (0x1UL << UARTE_INTENSET_TXSTOPPED_Pos) /*!< Bit mask of TXSTOPPED field. */
#define UARTE_INTENSET_TXSTOPPED_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENSET_TXSTOPPED_Enabled (1UL) /*!< Read: Enabled */
#define UARTE_INTENSET_TXSTOPPED_Set (1UL) /*!< Enable */

/* Bit 20 : Write '1' to Enable interrupt for TXSTARTED event */
#define UARTE_INTENSET_TXSTARTED_Pos (20UL) /*!< Position of TXSTARTED field. */
#define UARTE_INTENSET_TXSTARTED_Msk (0x1UL << UARTE_INTENSET_TXSTARTED_Pos) /*!< Bit mask of TXSTARTED field. */
#define UARTE_INTENSET_TXSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENSET_TXSTARTED_Enabled (1UL) /*!< Read: Enabled */
#define UARTE_INTENSET_TXSTARTED_Set (1UL) /*!< Enable */

/* Bit 19 : Write '1' to Enable interrupt for RXSTARTED event */
#define UARTE_INTENSET_RXSTARTED_Pos (19UL) /*!< Position of RXSTARTED field. */
#define UARTE_INTENSET_RXSTARTED_Msk (0x1UL << UARTE_INTENSET_RXSTARTED_Pos) /*!< Bit mask of RXSTARTED field. */
#define UARTE_INTENSET_RXSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENSET_RXSTARTED_Enabled (1UL) /*!< Read: Enabled */
#define UARTE_INTENSET_RXSTARTED_Set (1UL) /*!< Enable */

/* Bit 17 : Write '1' to Enable interrupt for RXTO event */
#define UARTE_INTENSET_RXTO_Pos (17UL) /*!< Position of RXTO field. */
#define UARTE_INTENSET_RXTO_Msk (0x1UL << UARTE_INTENSET_RXTO_Pos) /*!< Bit mask of RXTO field. */
#define UARTE_INTENSET_RXTO_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENSET_RXTO_Enabled (1UL) /*!< Read: Enabled */
#define UARTE_INTENSET_RXTO_Set (1UL) /*!< Enable */

/* Bit 9 : Write '1' to Enable interrupt for ERROR event */
#define UARTE_INTENSET_ERROR_Pos (9UL) /*!< Position of ERROR field. */
#define UARTE_INTENSET_ERROR_Msk (0x1UL << UARTE_INTENSET_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define UARTE_INTENSET_ERROR_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENSET_ERROR_Enabled (1UL) /*!< Read: Enabled */
#define UARTE_INTENSET_ERROR_Set (1UL) /*!< Enable */

/* Bit 8 : Write '1' to Enable interrupt for ENDTX event */
#define UARTE_INTENSET_ENDTX_Pos (8UL) /*!< Position of ENDTX field. */
#define UARTE_INTENSET_ENDTX_Msk (0x1UL << UARTE_INTENSET_ENDTX_Pos) /*!< Bit mask of ENDTX field. */
#define UARTE_INTENSET_ENDTX_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENSET_ENDTX_Enabled (1UL) /*!< Read: Enabled */
#define UARTE_INTENSET_ENDTX_Set (1UL) /*!< Enable */

/* Bit 7 : Write '1' to Enable interrupt for TXDRDY event */
#define UARTE_INTENSET_TXDRDY_Pos (7UL) /*!< Position of TXDRDY field. */
#define UARTE_INTENSET_TXDRDY_Msk (0x1UL << UARTE_INTENSET_TXDRDY_Pos) /*!< Bit mask of TXDRDY field. */
#define UARTE_INTENSET_TXDRDY_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENSET_TXDRDY_Enabled (1UL) /*!< Read: Enabled */
#define UARTE_INTENSET_TXDRDY_Set (1UL) /*!< Enable */

/* Bit 4 : Write '1' to Enable interrupt for ENDRX event */
#define UARTE_INTENSET_ENDRX_Pos (4UL) /*!< Position of ENDRX field. */
#define UARTE_INTENSET_ENDRX_Msk (0x1UL << UARTE_INTENSET_ENDRX_Pos) /*!< Bit mask of ENDRX field. */
#define UARTE_INTENSET_ENDRX_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENSET_ENDRX_Enabled (1UL) /*!< Read: Enabled */
#define UARTE_INTENSET_ENDRX_Set (1UL) /*!< Enable */

/* Bit 2 : Write '1' to Enable interrupt for RXDRDY event */
#define UARTE_INTENSET_RXDRDY_Pos (2UL) /*!< Position of RXDRDY field. */
#define UARTE_INTENSET_RXDRDY_Msk (0x1UL << UARTE_INTENSET_RXDRDY_Pos) /*!< Bit mask of RXDRDY field. */
#define UARTE_INTENSET_RXDRDY_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENSET_RXDRDY_Enabled (1UL) /*!< Read: Enabled */
#define UARTE_INTENSET_RXDRDY_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable interrupt for NCTS event */
#define UARTE_INTENSET_NCTS_Pos (1UL) /*!< Position of NCTS field. */
#define UARTE_INTENSET_NCTS_Msk (0x1UL << UARTE_INTENSET_NCTS_Pos) /*!< Bit mask of NCTS field. */
#define UARTE_INTENSET_NCTS_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENSET_NCTS_Enabled (1UL) /*!< Read: Enabled */
#define UARTE_INTENSET_NCTS_Set (1UL) /*!< Enable */

/* Bit 0 : Write '1' to Enable interrupt for CTS event */
#define UARTE_INTENSET_CTS_Pos (0UL) /*!< Position of CTS field. */
#define UARTE_INTENSET_CTS_Msk (0x1UL << UARTE_INTENSET_CTS_Pos) /*!< Bit mask of CTS field. */
#define UARTE_INTENSET_CTS_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENSET_CTS_Enabled (1UL) /*!< Read: Enabled */
#define UARTE_INTENSET_CTS_Set (1UL) /*!< Enable */

/* Register: UARTE_INTENCLR */
/* Description: Disable interrupt */

/* Bit 22 : Write '1' to Disable interrupt for TXSTOPPED event */
#define UARTE_INTENCLR_TXSTOPPED_Pos (22UL) /*!< Position of TXSTOPPED field. */
#define UARTE_INTENCLR_TXSTOPPED_Msk (0x1UL << UARTE_INTENCLR_TXSTOPPED_Pos) /*!< Bit mask of TXSTOPPED field. */
#define UARTE_INTENCLR_TXSTOPPED_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENCLR_TXSTOPPED_Enabled (1UL) /*!< Read: Enabled */
#define UARTE_INTENCLR_TXSTOPPED_Clear (1UL) /*!< Disable */

/* Bit 20 : Write '1' to Disable interrupt for TXSTARTED event */
#define UARTE_INTENCLR_TXSTARTED_Pos (20UL) /*!< Position of TXSTARTED field. */
#define UARTE_INTENCLR_TXSTARTED_Msk (0x1UL << UARTE_INTENCLR_TXSTARTED_Pos) /*!< Bit mask of TXSTARTED field. */
#define UARTE_INTENCLR_TXSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENCLR_TXSTARTED_Enabled (1UL) /*!< Read: Enabled */
#define UARTE_INTENCLR_TXSTARTED_Clear (1UL) /*!< Disable */

/* Bit 19 : Write '1' to Disable interrupt for RXSTARTED event */
#define UARTE_INTENCLR_RXSTARTED_Pos (19UL) /*!< Position of RXSTARTED field. */
#define UARTE_INTENCLR_RXSTARTED_Msk (0x1UL << UARTE_INTENCLR_RXSTARTED_Pos) /*!< Bit mask of RXSTARTED field. */
#define UARTE_INTENCLR_RXSTARTED_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENCLR_RXSTARTED_Enabled (1UL) /*!< Read: Enabled */
#define UARTE_INTENCLR_RXSTARTED_Clear (1UL) /*!< Disable */

/* Bit 17 : Write '1' to Disable interrupt for RXTO event */
#define UARTE_INTENCLR_RXTO_Pos (17UL) /*!< Position of RXTO field. */
#define UARTE_INTENCLR_RXTO_Msk (0x1UL << UARTE_INTENCLR_RXTO_Pos) /*!< Bit mask of RXTO field. */
#define UARTE_INTENCLR_RXTO_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENCLR_RXTO_Enabled (1UL) /*!< Read: Enabled */
#define UARTE_INTENCLR_RXTO_Clear (1UL) /*!< Disable */

/* Bit 9 : Write '1' to Disable interrupt for ERROR event */
#define UARTE_INTENCLR_ERROR_Pos (9UL) /*!< Position of ERROR field. */
#define UARTE_INTENCLR_ERROR_Msk (0x1UL << UARTE_INTENCLR_ERROR_Pos) /*!< Bit mask of ERROR field. */
#define UARTE_INTENCLR_ERROR_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENCLR_ERROR_Enabled (1UL) /*!< Read: Enabled */
#define UARTE_INTENCLR_ERROR_Clear (1UL) /*!< Disable */

/* Bit 8 : Write '1' to Disable interrupt for ENDTX event */
#define UARTE_INTENCLR_ENDTX_Pos (8UL) /*!< Position of ENDTX field. */
#define UARTE_INTENCLR_ENDTX_Msk (0x1UL << UARTE_INTENCLR_ENDTX_Pos) /*!< Bit mask of ENDTX field. */
#define UARTE_INTENCLR_ENDTX_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENCLR_ENDTX_Enabled (1UL) /*!< Read: Enabled */
#define UARTE_INTENCLR_ENDTX_Clear (1UL) /*!< Disable */

/* Bit 7 : Write '1' to Disable interrupt for TXDRDY event */
#define UARTE_INTENCLR_TXDRDY_Pos (7UL) /*!< Position of TXDRDY field. */
#define UARTE_INTENCLR_TXDRDY_Msk (0x1UL << UARTE_INTENCLR_TXDRDY_Pos) /*!< Bit mask of TXDRDY field. */
#define UARTE_INTENCLR_TXDRDY_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENCLR_TXDRDY_Enabled (1UL) /*!< Read: Enabled */
#define UARTE_INTENCLR_TXDRDY_Clear (1UL) /*!< Disable */

/* Bit 4 : Write '1' to Disable interrupt for ENDRX event */
#define UARTE_INTENCLR_ENDRX_Pos (4UL) /*!< Position of ENDRX field. */
#define UARTE_INTENCLR_ENDRX_Msk (0x1UL << UARTE_INTENCLR_ENDRX_Pos) /*!< Bit mask of ENDRX field. */
#define UARTE_INTENCLR_ENDRX_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENCLR_ENDRX_Enabled (1UL) /*!< Read: Enabled */
#define UARTE_INTENCLR_ENDRX_Clear (1UL) /*!< Disable */

/* Bit 2 : Write '1' to Disable interrupt for RXDRDY event */
#define UARTE_INTENCLR_RXDRDY_Pos (2UL) /*!< Position of RXDRDY field. */
#define UARTE_INTENCLR_RXDRDY_Msk (0x1UL << UARTE_INTENCLR_RXDRDY_Pos) /*!< Bit mask of RXDRDY field. */
#define UARTE_INTENCLR_RXDRDY_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENCLR_RXDRDY_Enabled (1UL) /*!< Read: Enabled */
#define UARTE_INTENCLR_RXDRDY_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable interrupt for NCTS event */
#define UARTE_INTENCLR_NCTS_Pos (1UL) /*!< Position of NCTS field. */
#define UARTE_INTENCLR_NCTS_Msk (0x1UL << UARTE_INTENCLR_NCTS_Pos) /*!< Bit mask of NCTS field. */
#define UARTE_INTENCLR_NCTS_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENCLR_NCTS_Enabled (1UL) /*!< Read: Enabled */
#define UARTE_INTENCLR_NCTS_Clear (1UL) /*!< Disable */

/* Bit 0 : Write '1' to Disable interrupt for CTS event */
#define UARTE_INTENCLR_CTS_Pos (0UL) /*!< Position of CTS field. */
#define UARTE_INTENCLR_CTS_Msk (0x1UL << UARTE_INTENCLR_CTS_Pos) /*!< Bit mask of CTS field. */
#define UARTE_INTENCLR_CTS_Disabled (0UL) /*!< Read: Disabled */
#define UARTE_INTENCLR_CTS_Enabled (1UL) /*!< Read: Enabled */
#define UARTE_INTENCLR_CTS_Clear (1UL) /*!< Disable */

/* Register: UARTE_ERRORSRC */
/* Description: Error source Note : this register is read / write one to clear. */

/* Bit 3 : Break condition */
#define UARTE_ERRORSRC_BREAK_Pos (3UL) /*!< Position of BREAK field. */
#define UARTE_ERRORSRC_BREAK_Msk (0x1UL << UARTE_ERRORSRC_BREAK_Pos) /*!< Bit mask of BREAK field. */
#define UARTE_ERRORSRC_BREAK_NotPresent (0UL) /*!< Read: error not present */
#define UARTE_ERRORSRC_BREAK_Present (1UL) /*!< Read: error present */

/* Bit 2 : Framing error occurred */
#define UARTE_ERRORSRC_FRAMING_Pos (2UL) /*!< Position of FRAMING field. */
#define UARTE_ERRORSRC_FRAMING_Msk (0x1UL << UARTE_ERRORSRC_FRAMING_Pos) /*!< Bit mask of FRAMING field. */
#define UARTE_ERRORSRC_FRAMING_NotPresent (0UL) /*!< Read: error not present */
#define UARTE_ERRORSRC_FRAMING_Present (1UL) /*!< Read: error present */

/* Bit 1 : Parity error */
#define UARTE_ERRORSRC_PARITY_Pos (1UL) /*!< Position of PARITY field. */
#define UARTE_ERRORSRC_PARITY_Msk (0x1UL << UARTE_ERRORSRC_PARITY_Pos) /*!< Bit mask of PARITY field. */
#define UARTE_ERRORSRC_PARITY_NotPresent (0UL) /*!< Read: error not present */
#define UARTE_ERRORSRC_PARITY_Present (1UL) /*!< Read: error present */

/* Bit 0 : Overrun error */
#define UARTE_ERRORSRC_OVERRUN_Pos (0UL) /*!< Position of OVERRUN field. */
#define UARTE_ERRORSRC_OVERRUN_Msk (0x1UL << UARTE_ERRORSRC_OVERRUN_Pos) /*!< Bit mask of OVERRUN field. */
#define UARTE_ERRORSRC_OVERRUN_NotPresent (0UL) /*!< Read: error not present */
#define UARTE_ERRORSRC_OVERRUN_Present (1UL) /*!< Read: error present */

/* Register: UARTE_ENABLE */
/* Description: Enable UART */

/* Bits 3..0 : Enable or disable UARTE */
#define UARTE_ENABLE_ENABLE_Pos (0UL) /*!< Position of ENABLE field. */
#define UARTE_ENABLE_ENABLE_Msk (0xFUL << UARTE_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define UARTE_ENABLE_ENABLE_Disabled (0UL) /*!< Disable UARTE */
#define UARTE_ENABLE_ENABLE_Enabled (8UL) /*!< Enable UARTE */

/* Register: UARTE_PSEL_RTS */
/* Description: Pin select for RTS signal */

/* Bit 31 : Connection */
#define UARTE_PSEL_RTS_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define UARTE_PSEL_RTS_CONNECT_Msk (0x1UL << UARTE_PSEL_RTS_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define UARTE_PSEL_RTS_CONNECT_Connected (0UL) /*!< Connect */
#define UARTE_PSEL_RTS_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define UARTE_PSEL_RTS_PORT_Pos (5UL) /*!< Position of PORT field. */
#define UARTE_PSEL_RTS_PORT_Msk (0x3UL << UARTE_PSEL_RTS_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define UARTE_PSEL_RTS_PIN_Pos (0UL) /*!< Position of PIN field. */
#define UARTE_PSEL_RTS_PIN_Msk (0x1FUL << UARTE_PSEL_RTS_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: UARTE_PSEL_TXD */
/* Description: Pin select for TXD signal */

/* Bit 31 : Connection */
#define UARTE_PSEL_TXD_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define UARTE_PSEL_TXD_CONNECT_Msk (0x1UL << UARTE_PSEL_TXD_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define UARTE_PSEL_TXD_CONNECT_Connected (0UL) /*!< Connect */
#define UARTE_PSEL_TXD_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define UARTE_PSEL_TXD_PORT_Pos (5UL) /*!< Position of PORT field. */
#define UARTE_PSEL_TXD_PORT_Msk (0x3UL << UARTE_PSEL_TXD_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define UARTE_PSEL_TXD_PIN_Pos (0UL) /*!< Position of PIN field. */
#define UARTE_PSEL_TXD_PIN_Msk (0x1FUL << UARTE_PSEL_TXD_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: UARTE_PSEL_CTS */
/* Description: Pin select for CTS signal */

/* Bit 31 : Connection */
#define UARTE_PSEL_CTS_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define UARTE_PSEL_CTS_CONNECT_Msk (0x1UL << UARTE_PSEL_CTS_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define UARTE_PSEL_CTS_CONNECT_Connected (0UL) /*!< Connect */
#define UARTE_PSEL_CTS_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define UARTE_PSEL_CTS_PORT_Pos (5UL) /*!< Position of PORT field. */
#define UARTE_PSEL_CTS_PORT_Msk (0x3UL << UARTE_PSEL_CTS_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define UARTE_PSEL_CTS_PIN_Pos (0UL) /*!< Position of PIN field. */
#define UARTE_PSEL_CTS_PIN_Msk (0x1FUL << UARTE_PSEL_CTS_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: UARTE_PSEL_RXD */
/* Description: Pin select for RXD signal */

/* Bit 31 : Connection */
#define UARTE_PSEL_RXD_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define UARTE_PSEL_RXD_CONNECT_Msk (0x1UL << UARTE_PSEL_RXD_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define UARTE_PSEL_RXD_CONNECT_Connected (0UL) /*!< Connect */
#define UARTE_PSEL_RXD_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number */
#define UARTE_PSEL_RXD_PORT_Pos (5UL) /*!< Position of PORT field. */
#define UARTE_PSEL_RXD_PORT_Msk (0x3UL << UARTE_PSEL_RXD_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number */
#define UARTE_PSEL_RXD_PIN_Pos (0UL) /*!< Position of PIN field. */
#define UARTE_PSEL_RXD_PIN_Msk (0x1FUL << UARTE_PSEL_RXD_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: UARTE_BAUDRATE */
/* Description: Baud rate. Accuracy depends on the HFCLK source selected. */

/* Bits 31..0 : Baud rate */
#define UARTE_BAUDRATE_BAUDRATE_Pos (0UL) /*!< Position of BAUDRATE field. */
#define UARTE_BAUDRATE_BAUDRATE_Msk (0xFFFFFFFFUL << UARTE_BAUDRATE_BAUDRATE_Pos) /*!< Bit mask of BAUDRATE field. */
#define UARTE_BAUDRATE_BAUDRATE_Baud1200 (0x0004F000UL) /*!< 1200 baud (actual rate: 1205) */
#define UARTE_BAUDRATE_BAUDRATE_Baud2400 (0x0009D000UL) /*!< 2400 baud (actual rate: 2396) */
#define UARTE_BAUDRATE_BAUDRATE_Baud4800 (0x0013B000UL) /*!< 4800 baud (actual rate: 4808) */
#define UARTE_BAUDRATE_BAUDRATE_Baud9600 (0x00275000UL) /*!< 9600 baud (actual rate: 9598) */
#define UARTE_BAUDRATE_BAUDRATE_Baud14400 (0x003AF000UL) /*!< 14400 baud (actual rate: 14401) */
#define UARTE_BAUDRATE_BAUDRATE_Baud19200 (0x004EA000UL) /*!< 19200 baud (actual rate: 19208) */
#define UARTE_BAUDRATE_BAUDRATE_Baud28800 (0x0075C000UL) /*!< 28800 baud (actual rate: 28777) */
#define UARTE_BAUDRATE_BAUDRATE_Baud31250 (0x00800000UL) /*!< 31250 baud */
#define UARTE_BAUDRATE_BAUDRATE_Baud38400 (0x009D0000UL) /*!< 38400 baud (actual rate: 38369) */
#define UARTE_BAUDRATE_BAUDRATE_Baud56000 (0x00E50000UL) /*!< 56000 baud (actual rate: 55944) */
#define UARTE_BAUDRATE_BAUDRATE_Baud57600 (0x00EB0000UL) /*!< 57600 baud (actual rate: 57554) */
#define UARTE_BAUDRATE_BAUDRATE_Baud76800 (0x013A9000UL) /*!< 76800 baud (actual rate: 76923) */
#define UARTE_BAUDRATE_BAUDRATE_Baud115200 (0x01D60000UL) /*!< 115200 baud (actual rate: 115108) */
#define UARTE_BAUDRATE_BAUDRATE_Baud230400 (0x03B00000UL) /*!< 230400 baud (actual rate: 231884) */
#define UARTE_BAUDRATE_BAUDRATE_Baud250000 (0x04000000UL) /*!< 250000 baud */
#define UARTE_BAUDRATE_BAUDRATE_Baud460800 (0x07400000UL) /*!< 460800 baud (actual rate: 457143) */
#define UARTE_BAUDRATE_BAUDRATE_Baud921600 (0x0F000000UL) /*!< 921600 baud (actual rate: 941176) */
#define UARTE_BAUDRATE_BAUDRATE_Baud1M (0x10000000UL) /*!< 1Mega baud */

/* Register: UARTE_RXD_PTR */
/* Description: Data pointer */

/* Bits 31..0 : Data pointer */
#define UARTE_RXD_PTR_PTR_Pos (0UL) /*!< Position of PTR field. */
#define UARTE_RXD_PTR_PTR_Msk (0xFFFFFFFFUL << UARTE_RXD_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: UARTE_RXD_MAXCNT */
/* Description: Maximum number of bytes in receive buffer */

/* Bits 9..0 : Maximum number of bytes in receive buffer */
#define UARTE_RXD_MAXCNT_MAXCNT_Pos (0UL) /*!< Position of MAXCNT field. */
#define UARTE_RXD_MAXCNT_MAXCNT_Msk (0x3FFUL << UARTE_RXD_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: UARTE_RXD_AMOUNT */
/* Description: Number of bytes transferred in the last transaction */

/* Bits 9..0 : Number of bytes transferred in the last transaction */
#define UARTE_RXD_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define UARTE_RXD_AMOUNT_AMOUNT_Msk (0x3FFUL << UARTE_RXD_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: UARTE_TXD_PTR */
/* Description: Data pointer */

/* Bits 31..0 : Data pointer */
#define UARTE_TXD_PTR_PTR_Pos (0UL) /*!< Position of PTR field. */
#define UARTE_TXD_PTR_PTR_Msk (0xFFFFFFFFUL << UARTE_TXD_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: UARTE_TXD_MAXCNT */
/* Description: Maximum number of bytes in transmit buffer */

/* Bits 9..0 : Maximum number of bytes in transmit buffer */
#define UARTE_TXD_MAXCNT_MAXCNT_Pos (0UL) /*!< Position of MAXCNT field. */
#define UARTE_TXD_MAXCNT_MAXCNT_Msk (0x3FFUL << UARTE_TXD_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: UARTE_TXD_AMOUNT */
/* Description: Number of bytes transferred in the last transaction */

/* Bits 9..0 : Number of bytes transferred in the last transaction */
#define UARTE_TXD_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define UARTE_TXD_AMOUNT_AMOUNT_Msk (0x3FFUL << UARTE_TXD_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: UARTE_CONFIG */
/* Description: Configuration of parity and hardware flow control */

/* Bit 4 : Stop bits */
#define UARTE_CONFIG_STOP_Pos (4UL) /*!< Position of STOP field. */
#define UARTE_CONFIG_STOP_Msk (0x1UL << UARTE_CONFIG_STOP_Pos) /*!< Bit mask of STOP field. */
#define UARTE_CONFIG_STOP_One (0UL) /*!< One stop bit */
#define UARTE_CONFIG_STOP_Two (1UL) /*!< Two stop bits */

/* Bits 3..1 : Parity */
#define UARTE_CONFIG_PARITY_Pos (1UL) /*!< Position of PARITY field. */
#define UARTE_CONFIG_PARITY_Msk (0x7UL << UARTE_CONFIG_PARITY_Pos) /*!< Bit mask of PARITY field. */
#define UARTE_CONFIG_PARITY_Excluded (0x0UL) /*!< Exclude parity bit */
#define UARTE_CONFIG_PARITY_Included (0x7UL) /*!< Include even parity bit */

/* Bit 0 : Hardware flow control */
#define UARTE_CONFIG_HWFC_Pos (0UL) /*!< Position of HWFC field. */
#define UARTE_CONFIG_HWFC_Msk (0x1UL << UARTE_CONFIG_HWFC_Pos) /*!< Bit mask of HWFC field. */
#define UARTE_CONFIG_HWFC_Disabled (0UL) /*!< Disabled */
#define UARTE_CONFIG_HWFC_Enabled (1UL) /*!< Enabled */


/* Peripheral: UICR */
/* Description: User Information Configuration Registers */

/* Register: UICR_NRFFW */
/* Description: Description collection[0]:  Reserved for Nordic firmware design */

/* Bits 31..0 : Reserved for Nordic firmware design */
#define UICR_NRFFW_NRFFW_Pos (0UL) /*!< Position of NRFFW field. */
#define UICR_NRFFW_NRFFW_Msk (0xFFFFFFFFUL << UICR_NRFFW_NRFFW_Pos) /*!< Bit mask of NRFFW field. */

/* Register: UICR_NRFHW */
/* Description: Description collection[0]:  Reserved for Nordic hardware design */

/* Bits 31..0 : Reserved for Nordic hardware design */
#define UICR_NRFHW_NRFHW_Pos (0UL) /*!< Position of NRFHW field. */
#define UICR_NRFHW_NRFHW_Msk (0xFFFFFFFFUL << UICR_NRFHW_NRFHW_Pos) /*!< Bit mask of NRFHW field. */

/* Register: UICR_CUSTOMER */
/* Description: Description collection[0]:  Reserved for customer */

/* Bits 31..0 : Reserved for customer */
#define UICR_CUSTOMER_CUSTOMER_Pos (0UL) /*!< Position of CUSTOMER field. */
#define UICR_CUSTOMER_CUSTOMER_Msk (0xFFFFFFFFUL << UICR_CUSTOMER_CUSTOMER_Pos) /*!< Bit mask of CUSTOMER field. */

/* Register: UICR_PSELRESET */
/* Description: Description collection[0]:  Mapping of the nRESET function */

/* Bit 31 : Connection */
#define UICR_PSELRESET_CONNECT_Pos (31UL) /*!< Position of CONNECT field. */
#define UICR_PSELRESET_CONNECT_Msk (0x1UL << UICR_PSELRESET_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define UICR_PSELRESET_CONNECT_Connected (0UL) /*!< Connect */
#define UICR_PSELRESET_CONNECT_Disconnected (1UL) /*!< Disconnect */

/* Bits 6..5 : Port number onto which nRESET is exposed */
#define UICR_PSELRESET_PORT_Pos (5UL) /*!< Position of PORT field. */
#define UICR_PSELRESET_PORT_Msk (0x3UL << UICR_PSELRESET_PORT_Pos) /*!< Bit mask of PORT field. */

/* Bits 4..0 : Pin number of PORT onto which nRESET is exposed */
#define UICR_PSELRESET_PIN_Pos (0UL) /*!< Position of PIN field. */
#define UICR_PSELRESET_PIN_Msk (0x1FUL << UICR_PSELRESET_PIN_Pos) /*!< Bit mask of PIN field. */

/* Register: UICR_APPROTECT */
/* Description: Access port protection */

/* Bits 7..0 : Enable or disable Access Port protection. */
#define UICR_APPROTECT_PALL_Pos (0UL) /*!< Position of PALL field. */
#define UICR_APPROTECT_PALL_Msk (0xFFUL << UICR_APPROTECT_PALL_Pos) /*!< Bit mask of PALL field. */
#define UICR_APPROTECT_PALL_Enabled (0x00UL) /*!< Enable */
#define UICR_APPROTECT_PALL_Disabled (0xFFUL) /*!< Disable */

/* Register: UICR_NFCPINS */
/* Description: Setting of pins dedicated to NFC functionality: NFC antenna or GPIO */

/* Bit 0 : Setting of pins dedicated to NFC functionality */
#define UICR_NFCPINS_PROTECT_Pos (0UL) /*!< Position of PROTECT field. */
#define UICR_NFCPINS_PROTECT_Msk (0x1UL << UICR_NFCPINS_PROTECT_Pos) /*!< Bit mask of PROTECT field. */
#define UICR_NFCPINS_PROTECT_Disabled (0UL) /*!< Operation as GPIO pins. Same protection as normal GPIO pins */
#define UICR_NFCPINS_PROTECT_NFC (1UL) /*!< Operation as NFC antenna pins. Configures the protection for NFC operation */

/* Register: UICR_EXTSUPPLY */
/* Description: Enable external circuitry to be supplied from VDD pin. Applicable in 'High voltage mode' only. */

/* Bit 0 : Enable external circuitry to be supplied from VDD pin (output of REG0 stage). */
#define UICR_EXTSUPPLY_EXTSUPPLY_Pos (0UL) /*!< Position of EXTSUPPLY field. */
#define UICR_EXTSUPPLY_EXTSUPPLY_Msk (0x1UL << UICR_EXTSUPPLY_EXTSUPPLY_Pos) /*!< Bit mask of EXTSUPPLY field. */
#define UICR_EXTSUPPLY_EXTSUPPLY_Disabled (0UL) /*!< No current can be drawn from the VDD pin. */
#define UICR_EXTSUPPLY_EXTSUPPLY_Enabled (1UL) /*!< It is allowed to supply external circuitry from the VDD pin. */

/* Register: UICR_REGOUT0 */
/* Description: GPIO reference voltage / external output supply voltage in 'High voltage mode'. */

/* Bits 2..0 : Output voltage from of REG0 regulator stage. The maximum output voltage from this stage is given as VDDH - VEXDIF. */
#define UICR_REGOUT0_VOUT_Pos (0UL) /*!< Position of VOUT field. */
#define UICR_REGOUT0_VOUT_Msk (0x7UL << UICR_REGOUT0_VOUT_Pos) /*!< Bit mask of VOUT field. */
#define UICR_REGOUT0_VOUT_1V8 (0UL) /*!< 1.8 V */
#define UICR_REGOUT0_VOUT_2V1 (1UL) /*!< 2.1 V */
#define UICR_REGOUT0_VOUT_2V4 (2UL) /*!< 2.4 V */
#define UICR_REGOUT0_VOUT_2V7 (3UL) /*!< 2.7 V */
#define UICR_REGOUT0_VOUT_3V0 (4UL) /*!< 3.0 V */
#define UICR_REGOUT0_VOUT_3V3 (5UL) /*!< 3.3 V */
#define UICR_REGOUT0_VOUT_DEFAULT (7UL) /*!< Default voltage: 1.8 V */


/* Peripheral: USBD */
/* Description: Universal Serial Bus device */

/* Register: USBD_SHORTS */
/* Description: Shortcut register */

/* Bit 4 : Shortcut between ENDEPOUT[0] event and EP0RCVOUT task */
#define USBD_SHORTS_ENDEPOUT0_EP0RCVOUT_Pos (4UL) /*!< Position of ENDEPOUT0_EP0RCVOUT field. */
#define USBD_SHORTS_ENDEPOUT0_EP0RCVOUT_Msk (0x1UL << USBD_SHORTS_ENDEPOUT0_EP0RCVOUT_Pos) /*!< Bit mask of ENDEPOUT0_EP0RCVOUT field. */
#define USBD_SHORTS_ENDEPOUT0_EP0RCVOUT_Disabled (0UL) /*!< Disable shortcut */
#define USBD_SHORTS_ENDEPOUT0_EP0RCVOUT_Enabled (1UL) /*!< Enable shortcut */

/* Bit 3 : Shortcut between ENDEPOUT[0] event and EP0STATUS task */
#define USBD_SHORTS_ENDEPOUT0_EP0STATUS_Pos (3UL) /*!< Position of ENDEPOUT0_EP0STATUS field. */
#define USBD_SHORTS_ENDEPOUT0_EP0STATUS_Msk (0x1UL << USBD_SHORTS_ENDEPOUT0_EP0STATUS_Pos) /*!< Bit mask of ENDEPOUT0_EP0STATUS field. */
#define USBD_SHORTS_ENDEPOUT0_EP0STATUS_Disabled (0UL) /*!< Disable shortcut */
#define USBD_SHORTS_ENDEPOUT0_EP0STATUS_Enabled (1UL) /*!< Enable shortcut */

/* Bit 2 : Shortcut between EP0DATADONE event and EP0STATUS task */
#define USBD_SHORTS_EP0DATADONE_EP0STATUS_Pos (2UL) /*!< Position of EP0DATADONE_EP0STATUS field. */
#define USBD_SHORTS_EP0DATADONE_EP0STATUS_Msk (0x1UL << USBD_SHORTS_EP0DATADONE_EP0STATUS_Pos) /*!< Bit mask of EP0DATADONE_EP0STATUS field. */
#define USBD_SHORTS_EP0DATADONE_EP0STATUS_Disabled (0UL) /*!< Disable shortcut */
#define USBD_SHORTS_EP0DATADONE_EP0STATUS_Enabled (1UL) /*!< Enable shortcut */

/* Bit 1 : Shortcut between EP0DATADONE event and STARTEPOUT[0] task */
#define USBD_SHORTS_EP0DATADONE_STARTEPOUT0_Pos (1UL) /*!< Position of EP0DATADONE_STARTEPOUT0 field. */
#define USBD_SHORTS_EP0DATADONE_STARTEPOUT0_Msk (0x1UL << USBD_SHORTS_EP0DATADONE_STARTEPOUT0_Pos) /*!< Bit mask of EP0DATADONE_STARTEPOUT0 field. */
#define USBD_SHORTS_EP0DATADONE_STARTEPOUT0_Disabled (0UL) /*!< Disable shortcut */
#define USBD_SHORTS_EP0DATADONE_STARTEPOUT0_Enabled (1UL) /*!< Enable shortcut */

/* Bit 0 : Shortcut between EP0DATADONE event and STARTEPIN[0] task */
#define USBD_SHORTS_EP0DATADONE_STARTEPIN0_Pos (0UL) /*!< Position of EP0DATADONE_STARTEPIN0 field. */
#define USBD_SHORTS_EP0DATADONE_STARTEPIN0_Msk (0x1UL << USBD_SHORTS_EP0DATADONE_STARTEPIN0_Pos) /*!< Bit mask of EP0DATADONE_STARTEPIN0 field. */
#define USBD_SHORTS_EP0DATADONE_STARTEPIN0_Disabled (0UL) /*!< Disable shortcut */
#define USBD_SHORTS_EP0DATADONE_STARTEPIN0_Enabled (1UL) /*!< Enable shortcut */

/* Register: USBD_INTEN */
/* Description: Enable or disable interrupt */

/* Bit 25 : Enable or disable interrupt for ACCESSFAULT event */
#define USBD_INTEN_ACCESSFAULT_Pos (25UL) /*!< Position of ACCESSFAULT field. */
#define USBD_INTEN_ACCESSFAULT_Msk (0x1UL << USBD_INTEN_ACCESSFAULT_Pos) /*!< Bit mask of ACCESSFAULT field. */
#define USBD_INTEN_ACCESSFAULT_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ACCESSFAULT_Enabled (1UL) /*!< Enable */

/* Bit 24 : Enable or disable interrupt for EPDATA event */
#define USBD_INTEN_EPDATA_Pos (24UL) /*!< Position of EPDATA field. */
#define USBD_INTEN_EPDATA_Msk (0x1UL << USBD_INTEN_EPDATA_Pos) /*!< Bit mask of EPDATA field. */
#define USBD_INTEN_EPDATA_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_EPDATA_Enabled (1UL) /*!< Enable */

/* Bit 23 : Enable or disable interrupt for EP0SETUP event */
#define USBD_INTEN_EP0SETUP_Pos (23UL) /*!< Position of EP0SETUP field. */
#define USBD_INTEN_EP0SETUP_Msk (0x1UL << USBD_INTEN_EP0SETUP_Pos) /*!< Bit mask of EP0SETUP field. */
#define USBD_INTEN_EP0SETUP_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_EP0SETUP_Enabled (1UL) /*!< Enable */

/* Bit 22 : Enable or disable interrupt for USBEVENT event */
#define USBD_INTEN_USBEVENT_Pos (22UL) /*!< Position of USBEVENT field. */
#define USBD_INTEN_USBEVENT_Msk (0x1UL << USBD_INTEN_USBEVENT_Pos) /*!< Bit mask of USBEVENT field. */
#define USBD_INTEN_USBEVENT_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_USBEVENT_Enabled (1UL) /*!< Enable */

/* Bit 21 : Enable or disable interrupt for SOF event */
#define USBD_INTEN_SOF_Pos (21UL) /*!< Position of SOF field. */
#define USBD_INTEN_SOF_Msk (0x1UL << USBD_INTEN_SOF_Pos) /*!< Bit mask of SOF field. */
#define USBD_INTEN_SOF_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_SOF_Enabled (1UL) /*!< Enable */

/* Bit 20 : Enable or disable interrupt for ENDISOOUT event */
#define USBD_INTEN_ENDISOOUT_Pos (20UL) /*!< Position of ENDISOOUT field. */
#define USBD_INTEN_ENDISOOUT_Msk (0x1UL << USBD_INTEN_ENDISOOUT_Pos) /*!< Bit mask of ENDISOOUT field. */
#define USBD_INTEN_ENDISOOUT_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDISOOUT_Enabled (1UL) /*!< Enable */

/* Bit 19 : Enable or disable interrupt for ENDEPOUT[7] event */
#define USBD_INTEN_ENDEPOUT7_Pos (19UL) /*!< Position of ENDEPOUT7 field. */
#define USBD_INTEN_ENDEPOUT7_Msk (0x1UL << USBD_INTEN_ENDEPOUT7_Pos) /*!< Bit mask of ENDEPOUT7 field. */
#define USBD_INTEN_ENDEPOUT7_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPOUT7_Enabled (1UL) /*!< Enable */

/* Bit 18 : Enable or disable interrupt for ENDEPOUT[6] event */
#define USBD_INTEN_ENDEPOUT6_Pos (18UL) /*!< Position of ENDEPOUT6 field. */
#define USBD_INTEN_ENDEPOUT6_Msk (0x1UL << USBD_INTEN_ENDEPOUT6_Pos) /*!< Bit mask of ENDEPOUT6 field. */
#define USBD_INTEN_ENDEPOUT6_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPOUT6_Enabled (1UL) /*!< Enable */

/* Bit 17 : Enable or disable interrupt for ENDEPOUT[5] event */
#define USBD_INTEN_ENDEPOUT5_Pos (17UL) /*!< Position of ENDEPOUT5 field. */
#define USBD_INTEN_ENDEPOUT5_Msk (0x1UL << USBD_INTEN_ENDEPOUT5_Pos) /*!< Bit mask of ENDEPOUT5 field. */
#define USBD_INTEN_ENDEPOUT5_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPOUT5_Enabled (1UL) /*!< Enable */

/* Bit 16 : Enable or disable interrupt for ENDEPOUT[4] event */
#define USBD_INTEN_ENDEPOUT4_Pos (16UL) /*!< Position of ENDEPOUT4 field. */
#define USBD_INTEN_ENDEPOUT4_Msk (0x1UL << USBD_INTEN_ENDEPOUT4_Pos) /*!< Bit mask of ENDEPOUT4 field. */
#define USBD_INTEN_ENDEPOUT4_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPOUT4_Enabled (1UL) /*!< Enable */

/* Bit 15 : Enable or disable interrupt for ENDEPOUT[3] event */
#define USBD_INTEN_ENDEPOUT3_Pos (15UL) /*!< Position of ENDEPOUT3 field. */
#define USBD_INTEN_ENDEPOUT3_Msk (0x1UL << USBD_INTEN_ENDEPOUT3_Pos) /*!< Bit mask of ENDEPOUT3 field. */
#define USBD_INTEN_ENDEPOUT3_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPOUT3_Enabled (1UL) /*!< Enable */

/* Bit 14 : Enable or disable interrupt for ENDEPOUT[2] event */
#define USBD_INTEN_ENDEPOUT2_Pos (14UL) /*!< Position of ENDEPOUT2 field. */
#define USBD_INTEN_ENDEPOUT2_Msk (0x1UL << USBD_INTEN_ENDEPOUT2_Pos) /*!< Bit mask of ENDEPOUT2 field. */
#define USBD_INTEN_ENDEPOUT2_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPOUT2_Enabled (1UL) /*!< Enable */

/* Bit 13 : Enable or disable interrupt for ENDEPOUT[1] event */
#define USBD_INTEN_ENDEPOUT1_Pos (13UL) /*!< Position of ENDEPOUT1 field. */
#define USBD_INTEN_ENDEPOUT1_Msk (0x1UL << USBD_INTEN_ENDEPOUT1_Pos) /*!< Bit mask of ENDEPOUT1 field. */
#define USBD_INTEN_ENDEPOUT1_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPOUT1_Enabled (1UL) /*!< Enable */

/* Bit 12 : Enable or disable interrupt for ENDEPOUT[0] event */
#define USBD_INTEN_ENDEPOUT0_Pos (12UL) /*!< Position of ENDEPOUT0 field. */
#define USBD_INTEN_ENDEPOUT0_Msk (0x1UL << USBD_INTEN_ENDEPOUT0_Pos) /*!< Bit mask of ENDEPOUT0 field. */
#define USBD_INTEN_ENDEPOUT0_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPOUT0_Enabled (1UL) /*!< Enable */

/* Bit 11 : Enable or disable interrupt for ENDISOIN event */
#define USBD_INTEN_ENDISOIN_Pos (11UL) /*!< Position of ENDISOIN field. */
#define USBD_INTEN_ENDISOIN_Msk (0x1UL << USBD_INTEN_ENDISOIN_Pos) /*!< Bit mask of ENDISOIN field. */
#define USBD_INTEN_ENDISOIN_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDISOIN_Enabled (1UL) /*!< Enable */

/* Bit 10 : Enable or disable interrupt for EP0DATADONE event */
#define USBD_INTEN_EP0DATADONE_Pos (10UL) /*!< Position of EP0DATADONE field. */
#define USBD_INTEN_EP0DATADONE_Msk (0x1UL << USBD_INTEN_EP0DATADONE_Pos) /*!< Bit mask of EP0DATADONE field. */
#define USBD_INTEN_EP0DATADONE_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_EP0DATADONE_Enabled (1UL) /*!< Enable */

/* Bit 9 : Enable or disable interrupt for ENDEPIN[7] event */
#define USBD_INTEN_ENDEPIN7_Pos (9UL) /*!< Position of ENDEPIN7 field. */
#define USBD_INTEN_ENDEPIN7_Msk (0x1UL << USBD_INTEN_ENDEPIN7_Pos) /*!< Bit mask of ENDEPIN7 field. */
#define USBD_INTEN_ENDEPIN7_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPIN7_Enabled (1UL) /*!< Enable */

/* Bit 8 : Enable or disable interrupt for ENDEPIN[6] event */
#define USBD_INTEN_ENDEPIN6_Pos (8UL) /*!< Position of ENDEPIN6 field. */
#define USBD_INTEN_ENDEPIN6_Msk (0x1UL << USBD_INTEN_ENDEPIN6_Pos) /*!< Bit mask of ENDEPIN6 field. */
#define USBD_INTEN_ENDEPIN6_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPIN6_Enabled (1UL) /*!< Enable */

/* Bit 7 : Enable or disable interrupt for ENDEPIN[5] event */
#define USBD_INTEN_ENDEPIN5_Pos (7UL) /*!< Position of ENDEPIN5 field. */
#define USBD_INTEN_ENDEPIN5_Msk (0x1UL << USBD_INTEN_ENDEPIN5_Pos) /*!< Bit mask of ENDEPIN5 field. */
#define USBD_INTEN_ENDEPIN5_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPIN5_Enabled (1UL) /*!< Enable */

/* Bit 6 : Enable or disable interrupt for ENDEPIN[4] event */
#define USBD_INTEN_ENDEPIN4_Pos (6UL) /*!< Position of ENDEPIN4 field. */
#define USBD_INTEN_ENDEPIN4_Msk (0x1UL << USBD_INTEN_ENDEPIN4_Pos) /*!< Bit mask of ENDEPIN4 field. */
#define USBD_INTEN_ENDEPIN4_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPIN4_Enabled (1UL) /*!< Enable */

/* Bit 5 : Enable or disable interrupt for ENDEPIN[3] event */
#define USBD_INTEN_ENDEPIN3_Pos (5UL) /*!< Position of ENDEPIN3 field. */
#define USBD_INTEN_ENDEPIN3_Msk (0x1UL << USBD_INTEN_ENDEPIN3_Pos) /*!< Bit mask of ENDEPIN3 field. */
#define USBD_INTEN_ENDEPIN3_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPIN3_Enabled (1UL) /*!< Enable */

/* Bit 4 : Enable or disable interrupt for ENDEPIN[2] event */
#define USBD_INTEN_ENDEPIN2_Pos (4UL) /*!< Position of ENDEPIN2 field. */
#define USBD_INTEN_ENDEPIN2_Msk (0x1UL << USBD_INTEN_ENDEPIN2_Pos) /*!< Bit mask of ENDEPIN2 field. */
#define USBD_INTEN_ENDEPIN2_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPIN2_Enabled (1UL) /*!< Enable */

/* Bit 3 : Enable or disable interrupt for ENDEPIN[1] event */
#define USBD_INTEN_ENDEPIN1_Pos (3UL) /*!< Position of ENDEPIN1 field. */
#define USBD_INTEN_ENDEPIN1_Msk (0x1UL << USBD_INTEN_ENDEPIN1_Pos) /*!< Bit mask of ENDEPIN1 field. */
#define USBD_INTEN_ENDEPIN1_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPIN1_Enabled (1UL) /*!< Enable */

/* Bit 2 : Enable or disable interrupt for ENDEPIN[0] event */
#define USBD_INTEN_ENDEPIN0_Pos (2UL) /*!< Position of ENDEPIN0 field. */
#define USBD_INTEN_ENDEPIN0_Msk (0x1UL << USBD_INTEN_ENDEPIN0_Pos) /*!< Bit mask of ENDEPIN0 field. */
#define USBD_INTEN_ENDEPIN0_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_ENDEPIN0_Enabled (1UL) /*!< Enable */

/* Bit 1 : Enable or disable interrupt for STARTED event */
#define USBD_INTEN_STARTED_Pos (1UL) /*!< Position of STARTED field. */
#define USBD_INTEN_STARTED_Msk (0x1UL << USBD_INTEN_STARTED_Pos) /*!< Bit mask of STARTED field. */
#define USBD_INTEN_STARTED_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_STARTED_Enabled (1UL) /*!< Enable */

/* Bit 0 : Enable or disable interrupt for USBRESET event */
#define USBD_INTEN_USBRESET_Pos (0UL) /*!< Position of USBRESET field. */
#define USBD_INTEN_USBRESET_Msk (0x1UL << USBD_INTEN_USBRESET_Pos) /*!< Bit mask of USBRESET field. */
#define USBD_INTEN_USBRESET_Disabled (0UL) /*!< Disable */
#define USBD_INTEN_USBRESET_Enabled (1UL) /*!< Enable */

/* Register: USBD_INTENSET */
/* Description: Enable interrupt */

/* Bit 25 : Write '1' to Enable interrupt for ACCESSFAULT event */
#define USBD_INTENSET_ACCESSFAULT_Pos (25UL) /*!< Position of ACCESSFAULT field. */
#define USBD_INTENSET_ACCESSFAULT_Msk (0x1UL << USBD_INTENSET_ACCESSFAULT_Pos) /*!< Bit mask of ACCESSFAULT field. */
#define USBD_INTENSET_ACCESSFAULT_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ACCESSFAULT_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ACCESSFAULT_Set (1UL) /*!< Enable */

/* Bit 24 : Write '1' to Enable interrupt for EPDATA event */
#define USBD_INTENSET_EPDATA_Pos (24UL) /*!< Position of EPDATA field. */
#define USBD_INTENSET_EPDATA_Msk (0x1UL << USBD_INTENSET_EPDATA_Pos) /*!< Bit mask of EPDATA field. */
#define USBD_INTENSET_EPDATA_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_EPDATA_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_EPDATA_Set (1UL) /*!< Enable */

/* Bit 23 : Write '1' to Enable interrupt for EP0SETUP event */
#define USBD_INTENSET_EP0SETUP_Pos (23UL) /*!< Position of EP0SETUP field. */
#define USBD_INTENSET_EP0SETUP_Msk (0x1UL << USBD_INTENSET_EP0SETUP_Pos) /*!< Bit mask of EP0SETUP field. */
#define USBD_INTENSET_EP0SETUP_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_EP0SETUP_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_EP0SETUP_Set (1UL) /*!< Enable */

/* Bit 22 : Write '1' to Enable interrupt for USBEVENT event */
#define USBD_INTENSET_USBEVENT_Pos (22UL) /*!< Position of USBEVENT field. */
#define USBD_INTENSET_USBEVENT_Msk (0x1UL << USBD_INTENSET_USBEVENT_Pos) /*!< Bit mask of USBEVENT field. */
#define USBD_INTENSET_USBEVENT_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_USBEVENT_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_USBEVENT_Set (1UL) /*!< Enable */

/* Bit 21 : Write '1' to Enable interrupt for SOF event */
#define USBD_INTENSET_SOF_Pos (21UL) /*!< Position of SOF field. */
#define USBD_INTENSET_SOF_Msk (0x1UL << USBD_INTENSET_SOF_Pos) /*!< Bit mask of SOF field. */
#define USBD_INTENSET_SOF_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_SOF_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_SOF_Set (1UL) /*!< Enable */

/* Bit 20 : Write '1' to Enable interrupt for ENDISOOUT event */
#define USBD_INTENSET_ENDISOOUT_Pos (20UL) /*!< Position of ENDISOOUT field. */
#define USBD_INTENSET_ENDISOOUT_Msk (0x1UL << USBD_INTENSET_ENDISOOUT_Pos) /*!< Bit mask of ENDISOOUT field. */
#define USBD_INTENSET_ENDISOOUT_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDISOOUT_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDISOOUT_Set (1UL) /*!< Enable */

/* Bit 19 : Write '1' to Enable interrupt for ENDEPOUT[7] event */
#define USBD_INTENSET_ENDEPOUT7_Pos (19UL) /*!< Position of ENDEPOUT7 field. */
#define USBD_INTENSET_ENDEPOUT7_Msk (0x1UL << USBD_INTENSET_ENDEPOUT7_Pos) /*!< Bit mask of ENDEPOUT7 field. */
#define USBD_INTENSET_ENDEPOUT7_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPOUT7_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPOUT7_Set (1UL) /*!< Enable */

/* Bit 18 : Write '1' to Enable interrupt for ENDEPOUT[6] event */
#define USBD_INTENSET_ENDEPOUT6_Pos (18UL) /*!< Position of ENDEPOUT6 field. */
#define USBD_INTENSET_ENDEPOUT6_Msk (0x1UL << USBD_INTENSET_ENDEPOUT6_Pos) /*!< Bit mask of ENDEPOUT6 field. */
#define USBD_INTENSET_ENDEPOUT6_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPOUT6_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPOUT6_Set (1UL) /*!< Enable */

/* Bit 17 : Write '1' to Enable interrupt for ENDEPOUT[5] event */
#define USBD_INTENSET_ENDEPOUT5_Pos (17UL) /*!< Position of ENDEPOUT5 field. */
#define USBD_INTENSET_ENDEPOUT5_Msk (0x1UL << USBD_INTENSET_ENDEPOUT5_Pos) /*!< Bit mask of ENDEPOUT5 field. */
#define USBD_INTENSET_ENDEPOUT5_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPOUT5_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPOUT5_Set (1UL) /*!< Enable */

/* Bit 16 : Write '1' to Enable interrupt for ENDEPOUT[4] event */
#define USBD_INTENSET_ENDEPOUT4_Pos (16UL) /*!< Position of ENDEPOUT4 field. */
#define USBD_INTENSET_ENDEPOUT4_Msk (0x1UL << USBD_INTENSET_ENDEPOUT4_Pos) /*!< Bit mask of ENDEPOUT4 field. */
#define USBD_INTENSET_ENDEPOUT4_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPOUT4_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPOUT4_Set (1UL) /*!< Enable */

/* Bit 15 : Write '1' to Enable interrupt for ENDEPOUT[3] event */
#define USBD_INTENSET_ENDEPOUT3_Pos (15UL) /*!< Position of ENDEPOUT3 field. */
#define USBD_INTENSET_ENDEPOUT3_Msk (0x1UL << USBD_INTENSET_ENDEPOUT3_Pos) /*!< Bit mask of ENDEPOUT3 field. */
#define USBD_INTENSET_ENDEPOUT3_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPOUT3_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPOUT3_Set (1UL) /*!< Enable */

/* Bit 14 : Write '1' to Enable interrupt for ENDEPOUT[2] event */
#define USBD_INTENSET_ENDEPOUT2_Pos (14UL) /*!< Position of ENDEPOUT2 field. */
#define USBD_INTENSET_ENDEPOUT2_Msk (0x1UL << USBD_INTENSET_ENDEPOUT2_Pos) /*!< Bit mask of ENDEPOUT2 field. */
#define USBD_INTENSET_ENDEPOUT2_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPOUT2_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPOUT2_Set (1UL) /*!< Enable */

/* Bit 13 : Write '1' to Enable interrupt for ENDEPOUT[1] event */
#define USBD_INTENSET_ENDEPOUT1_Pos (13UL) /*!< Position of ENDEPOUT1 field. */
#define USBD_INTENSET_ENDEPOUT1_Msk (0x1UL << USBD_INTENSET_ENDEPOUT1_Pos) /*!< Bit mask of ENDEPOUT1 field. */
#define USBD_INTENSET_ENDEPOUT1_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPOUT1_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPOUT1_Set (1UL) /*!< Enable */

/* Bit 12 : Write '1' to Enable interrupt for ENDEPOUT[0] event */
#define USBD_INTENSET_ENDEPOUT0_Pos (12UL) /*!< Position of ENDEPOUT0 field. */
#define USBD_INTENSET_ENDEPOUT0_Msk (0x1UL << USBD_INTENSET_ENDEPOUT0_Pos) /*!< Bit mask of ENDEPOUT0 field. */
#define USBD_INTENSET_ENDEPOUT0_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPOUT0_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPOUT0_Set (1UL) /*!< Enable */

/* Bit 11 : Write '1' to Enable interrupt for ENDISOIN event */
#define USBD_INTENSET_ENDISOIN_Pos (11UL) /*!< Position of ENDISOIN field. */
#define USBD_INTENSET_ENDISOIN_Msk (0x1UL << USBD_INTENSET_ENDISOIN_Pos) /*!< Bit mask of ENDISOIN field. */
#define USBD_INTENSET_ENDISOIN_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDISOIN_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDISOIN_Set (1UL) /*!< Enable */

/* Bit 10 : Write '1' to Enable interrupt for EP0DATADONE event */
#define USBD_INTENSET_EP0DATADONE_Pos (10UL) /*!< Position of EP0DATADONE field. */
#define USBD_INTENSET_EP0DATADONE_Msk (0x1UL << USBD_INTENSET_EP0DATADONE_Pos) /*!< Bit mask of EP0DATADONE field. */
#define USBD_INTENSET_EP0DATADONE_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_EP0DATADONE_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_EP0DATADONE_Set (1UL) /*!< Enable */

/* Bit 9 : Write '1' to Enable interrupt for ENDEPIN[7] event */
#define USBD_INTENSET_ENDEPIN7_Pos (9UL) /*!< Position of ENDEPIN7 field. */
#define USBD_INTENSET_ENDEPIN7_Msk (0x1UL << USBD_INTENSET_ENDEPIN7_Pos) /*!< Bit mask of ENDEPIN7 field. */
#define USBD_INTENSET_ENDEPIN7_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPIN7_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPIN7_Set (1UL) /*!< Enable */

/* Bit 8 : Write '1' to Enable interrupt for ENDEPIN[6] event */
#define USBD_INTENSET_ENDEPIN6_Pos (8UL) /*!< Position of ENDEPIN6 field. */
#define USBD_INTENSET_ENDEPIN6_Msk (0x1UL << USBD_INTENSET_ENDEPIN6_Pos) /*!< Bit mask of ENDEPIN6 field. */
#define USBD_INTENSET_ENDEPIN6_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPIN6_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPIN6_Set (1UL) /*!< Enable */

/* Bit 7 : Write '1' to Enable interrupt for ENDEPIN[5] event */
#define USBD_INTENSET_ENDEPIN5_Pos (7UL) /*!< Position of ENDEPIN5 field. */
#define USBD_INTENSET_ENDEPIN5_Msk (0x1UL << USBD_INTENSET_ENDEPIN5_Pos) /*!< Bit mask of ENDEPIN5 field. */
#define USBD_INTENSET_ENDEPIN5_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPIN5_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPIN5_Set (1UL) /*!< Enable */

/* Bit 6 : Write '1' to Enable interrupt for ENDEPIN[4] event */
#define USBD_INTENSET_ENDEPIN4_Pos (6UL) /*!< Position of ENDEPIN4 field. */
#define USBD_INTENSET_ENDEPIN4_Msk (0x1UL << USBD_INTENSET_ENDEPIN4_Pos) /*!< Bit mask of ENDEPIN4 field. */
#define USBD_INTENSET_ENDEPIN4_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPIN4_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPIN4_Set (1UL) /*!< Enable */

/* Bit 5 : Write '1' to Enable interrupt for ENDEPIN[3] event */
#define USBD_INTENSET_ENDEPIN3_Pos (5UL) /*!< Position of ENDEPIN3 field. */
#define USBD_INTENSET_ENDEPIN3_Msk (0x1UL << USBD_INTENSET_ENDEPIN3_Pos) /*!< Bit mask of ENDEPIN3 field. */
#define USBD_INTENSET_ENDEPIN3_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPIN3_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPIN3_Set (1UL) /*!< Enable */

/* Bit 4 : Write '1' to Enable interrupt for ENDEPIN[2] event */
#define USBD_INTENSET_ENDEPIN2_Pos (4UL) /*!< Position of ENDEPIN2 field. */
#define USBD_INTENSET_ENDEPIN2_Msk (0x1UL << USBD_INTENSET_ENDEPIN2_Pos) /*!< Bit mask of ENDEPIN2 field. */
#define USBD_INTENSET_ENDEPIN2_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPIN2_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPIN2_Set (1UL) /*!< Enable */

/* Bit 3 : Write '1' to Enable interrupt for ENDEPIN[1] event */
#define USBD_INTENSET_ENDEPIN1_Pos (3UL) /*!< Position of ENDEPIN1 field. */
#define USBD_INTENSET_ENDEPIN1_Msk (0x1UL << USBD_INTENSET_ENDEPIN1_Pos) /*!< Bit mask of ENDEPIN1 field. */
#define USBD_INTENSET_ENDEPIN1_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPIN1_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPIN1_Set (1UL) /*!< Enable */

/* Bit 2 : Write '1' to Enable interrupt for ENDEPIN[0] event */
#define USBD_INTENSET_ENDEPIN0_Pos (2UL) /*!< Position of ENDEPIN0 field. */
#define USBD_INTENSET_ENDEPIN0_Msk (0x1UL << USBD_INTENSET_ENDEPIN0_Pos) /*!< Bit mask of ENDEPIN0 field. */
#define USBD_INTENSET_ENDEPIN0_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_ENDEPIN0_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_ENDEPIN0_Set (1UL) /*!< Enable */

/* Bit 1 : Write '1' to Enable interrupt for STARTED event */
#define USBD_INTENSET_STARTED_Pos (1UL) /*!< Position of STARTED field. */
#define USBD_INTENSET_STARTED_Msk (0x1UL << USBD_INTENSET_STARTED_Pos) /*!< Bit mask of STARTED field. */
#define USBD_INTENSET_STARTED_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_STARTED_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_STARTED_Set (1UL) /*!< Enable */

/* Bit 0 : Write '1' to Enable interrupt for USBRESET event */
#define USBD_INTENSET_USBRESET_Pos (0UL) /*!< Position of USBRESET field. */
#define USBD_INTENSET_USBRESET_Msk (0x1UL << USBD_INTENSET_USBRESET_Pos) /*!< Bit mask of USBRESET field. */
#define USBD_INTENSET_USBRESET_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENSET_USBRESET_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENSET_USBRESET_Set (1UL) /*!< Enable */

/* Register: USBD_INTENCLR */
/* Description: Disable interrupt */

/* Bit 25 : Write '1' to Disable interrupt for ACCESSFAULT event */
#define USBD_INTENCLR_ACCESSFAULT_Pos (25UL) /*!< Position of ACCESSFAULT field. */
#define USBD_INTENCLR_ACCESSFAULT_Msk (0x1UL << USBD_INTENCLR_ACCESSFAULT_Pos) /*!< Bit mask of ACCESSFAULT field. */
#define USBD_INTENCLR_ACCESSFAULT_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ACCESSFAULT_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ACCESSFAULT_Clear (1UL) /*!< Disable */

/* Bit 24 : Write '1' to Disable interrupt for EPDATA event */
#define USBD_INTENCLR_EPDATA_Pos (24UL) /*!< Position of EPDATA field. */
#define USBD_INTENCLR_EPDATA_Msk (0x1UL << USBD_INTENCLR_EPDATA_Pos) /*!< Bit mask of EPDATA field. */
#define USBD_INTENCLR_EPDATA_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_EPDATA_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_EPDATA_Clear (1UL) /*!< Disable */

/* Bit 23 : Write '1' to Disable interrupt for EP0SETUP event */
#define USBD_INTENCLR_EP0SETUP_Pos (23UL) /*!< Position of EP0SETUP field. */
#define USBD_INTENCLR_EP0SETUP_Msk (0x1UL << USBD_INTENCLR_EP0SETUP_Pos) /*!< Bit mask of EP0SETUP field. */
#define USBD_INTENCLR_EP0SETUP_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_EP0SETUP_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_EP0SETUP_Clear (1UL) /*!< Disable */

/* Bit 22 : Write '1' to Disable interrupt for USBEVENT event */
#define USBD_INTENCLR_USBEVENT_Pos (22UL) /*!< Position of USBEVENT field. */
#define USBD_INTENCLR_USBEVENT_Msk (0x1UL << USBD_INTENCLR_USBEVENT_Pos) /*!< Bit mask of USBEVENT field. */
#define USBD_INTENCLR_USBEVENT_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_USBEVENT_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_USBEVENT_Clear (1UL) /*!< Disable */

/* Bit 21 : Write '1' to Disable interrupt for SOF event */
#define USBD_INTENCLR_SOF_Pos (21UL) /*!< Position of SOF field. */
#define USBD_INTENCLR_SOF_Msk (0x1UL << USBD_INTENCLR_SOF_Pos) /*!< Bit mask of SOF field. */
#define USBD_INTENCLR_SOF_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_SOF_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_SOF_Clear (1UL) /*!< Disable */

/* Bit 20 : Write '1' to Disable interrupt for ENDISOOUT event */
#define USBD_INTENCLR_ENDISOOUT_Pos (20UL) /*!< Position of ENDISOOUT field. */
#define USBD_INTENCLR_ENDISOOUT_Msk (0x1UL << USBD_INTENCLR_ENDISOOUT_Pos) /*!< Bit mask of ENDISOOUT field. */
#define USBD_INTENCLR_ENDISOOUT_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDISOOUT_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDISOOUT_Clear (1UL) /*!< Disable */

/* Bit 19 : Write '1' to Disable interrupt for ENDEPOUT[7] event */
#define USBD_INTENCLR_ENDEPOUT7_Pos (19UL) /*!< Position of ENDEPOUT7 field. */
#define USBD_INTENCLR_ENDEPOUT7_Msk (0x1UL << USBD_INTENCLR_ENDEPOUT7_Pos) /*!< Bit mask of ENDEPOUT7 field. */
#define USBD_INTENCLR_ENDEPOUT7_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPOUT7_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPOUT7_Clear (1UL) /*!< Disable */

/* Bit 18 : Write '1' to Disable interrupt for ENDEPOUT[6] event */
#define USBD_INTENCLR_ENDEPOUT6_Pos (18UL) /*!< Position of ENDEPOUT6 field. */
#define USBD_INTENCLR_ENDEPOUT6_Msk (0x1UL << USBD_INTENCLR_ENDEPOUT6_Pos) /*!< Bit mask of ENDEPOUT6 field. */
#define USBD_INTENCLR_ENDEPOUT6_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPOUT6_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPOUT6_Clear (1UL) /*!< Disable */

/* Bit 17 : Write '1' to Disable interrupt for ENDEPOUT[5] event */
#define USBD_INTENCLR_ENDEPOUT5_Pos (17UL) /*!< Position of ENDEPOUT5 field. */
#define USBD_INTENCLR_ENDEPOUT5_Msk (0x1UL << USBD_INTENCLR_ENDEPOUT5_Pos) /*!< Bit mask of ENDEPOUT5 field. */
#define USBD_INTENCLR_ENDEPOUT5_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPOUT5_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPOUT5_Clear (1UL) /*!< Disable */

/* Bit 16 : Write '1' to Disable interrupt for ENDEPOUT[4] event */
#define USBD_INTENCLR_ENDEPOUT4_Pos (16UL) /*!< Position of ENDEPOUT4 field. */
#define USBD_INTENCLR_ENDEPOUT4_Msk (0x1UL << USBD_INTENCLR_ENDEPOUT4_Pos) /*!< Bit mask of ENDEPOUT4 field. */
#define USBD_INTENCLR_ENDEPOUT4_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPOUT4_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPOUT4_Clear (1UL) /*!< Disable */

/* Bit 15 : Write '1' to Disable interrupt for ENDEPOUT[3] event */
#define USBD_INTENCLR_ENDEPOUT3_Pos (15UL) /*!< Position of ENDEPOUT3 field. */
#define USBD_INTENCLR_ENDEPOUT3_Msk (0x1UL << USBD_INTENCLR_ENDEPOUT3_Pos) /*!< Bit mask of ENDEPOUT3 field. */
#define USBD_INTENCLR_ENDEPOUT3_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPOUT3_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPOUT3_Clear (1UL) /*!< Disable */

/* Bit 14 : Write '1' to Disable interrupt for ENDEPOUT[2] event */
#define USBD_INTENCLR_ENDEPOUT2_Pos (14UL) /*!< Position of ENDEPOUT2 field. */
#define USBD_INTENCLR_ENDEPOUT2_Msk (0x1UL << USBD_INTENCLR_ENDEPOUT2_Pos) /*!< Bit mask of ENDEPOUT2 field. */
#define USBD_INTENCLR_ENDEPOUT2_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPOUT2_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPOUT2_Clear (1UL) /*!< Disable */

/* Bit 13 : Write '1' to Disable interrupt for ENDEPOUT[1] event */
#define USBD_INTENCLR_ENDEPOUT1_Pos (13UL) /*!< Position of ENDEPOUT1 field. */
#define USBD_INTENCLR_ENDEPOUT1_Msk (0x1UL << USBD_INTENCLR_ENDEPOUT1_Pos) /*!< Bit mask of ENDEPOUT1 field. */
#define USBD_INTENCLR_ENDEPOUT1_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPOUT1_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPOUT1_Clear (1UL) /*!< Disable */

/* Bit 12 : Write '1' to Disable interrupt for ENDEPOUT[0] event */
#define USBD_INTENCLR_ENDEPOUT0_Pos (12UL) /*!< Position of ENDEPOUT0 field. */
#define USBD_INTENCLR_ENDEPOUT0_Msk (0x1UL << USBD_INTENCLR_ENDEPOUT0_Pos) /*!< Bit mask of ENDEPOUT0 field. */
#define USBD_INTENCLR_ENDEPOUT0_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPOUT0_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPOUT0_Clear (1UL) /*!< Disable */

/* Bit 11 : Write '1' to Disable interrupt for ENDISOIN event */
#define USBD_INTENCLR_ENDISOIN_Pos (11UL) /*!< Position of ENDISOIN field. */
#define USBD_INTENCLR_ENDISOIN_Msk (0x1UL << USBD_INTENCLR_ENDISOIN_Pos) /*!< Bit mask of ENDISOIN field. */
#define USBD_INTENCLR_ENDISOIN_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDISOIN_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDISOIN_Clear (1UL) /*!< Disable */

/* Bit 10 : Write '1' to Disable interrupt for EP0DATADONE event */
#define USBD_INTENCLR_EP0DATADONE_Pos (10UL) /*!< Position of EP0DATADONE field. */
#define USBD_INTENCLR_EP0DATADONE_Msk (0x1UL << USBD_INTENCLR_EP0DATADONE_Pos) /*!< Bit mask of EP0DATADONE field. */
#define USBD_INTENCLR_EP0DATADONE_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_EP0DATADONE_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_EP0DATADONE_Clear (1UL) /*!< Disable */

/* Bit 9 : Write '1' to Disable interrupt for ENDEPIN[7] event */
#define USBD_INTENCLR_ENDEPIN7_Pos (9UL) /*!< Position of ENDEPIN7 field. */
#define USBD_INTENCLR_ENDEPIN7_Msk (0x1UL << USBD_INTENCLR_ENDEPIN7_Pos) /*!< Bit mask of ENDEPIN7 field. */
#define USBD_INTENCLR_ENDEPIN7_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPIN7_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPIN7_Clear (1UL) /*!< Disable */

/* Bit 8 : Write '1' to Disable interrupt for ENDEPIN[6] event */
#define USBD_INTENCLR_ENDEPIN6_Pos (8UL) /*!< Position of ENDEPIN6 field. */
#define USBD_INTENCLR_ENDEPIN6_Msk (0x1UL << USBD_INTENCLR_ENDEPIN6_Pos) /*!< Bit mask of ENDEPIN6 field. */
#define USBD_INTENCLR_ENDEPIN6_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPIN6_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPIN6_Clear (1UL) /*!< Disable */

/* Bit 7 : Write '1' to Disable interrupt for ENDEPIN[5] event */
#define USBD_INTENCLR_ENDEPIN5_Pos (7UL) /*!< Position of ENDEPIN5 field. */
#define USBD_INTENCLR_ENDEPIN5_Msk (0x1UL << USBD_INTENCLR_ENDEPIN5_Pos) /*!< Bit mask of ENDEPIN5 field. */
#define USBD_INTENCLR_ENDEPIN5_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPIN5_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPIN5_Clear (1UL) /*!< Disable */

/* Bit 6 : Write '1' to Disable interrupt for ENDEPIN[4] event */
#define USBD_INTENCLR_ENDEPIN4_Pos (6UL) /*!< Position of ENDEPIN4 field. */
#define USBD_INTENCLR_ENDEPIN4_Msk (0x1UL << USBD_INTENCLR_ENDEPIN4_Pos) /*!< Bit mask of ENDEPIN4 field. */
#define USBD_INTENCLR_ENDEPIN4_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPIN4_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPIN4_Clear (1UL) /*!< Disable */

/* Bit 5 : Write '1' to Disable interrupt for ENDEPIN[3] event */
#define USBD_INTENCLR_ENDEPIN3_Pos (5UL) /*!< Position of ENDEPIN3 field. */
#define USBD_INTENCLR_ENDEPIN3_Msk (0x1UL << USBD_INTENCLR_ENDEPIN3_Pos) /*!< Bit mask of ENDEPIN3 field. */
#define USBD_INTENCLR_ENDEPIN3_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPIN3_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPIN3_Clear (1UL) /*!< Disable */

/* Bit 4 : Write '1' to Disable interrupt for ENDEPIN[2] event */
#define USBD_INTENCLR_ENDEPIN2_Pos (4UL) /*!< Position of ENDEPIN2 field. */
#define USBD_INTENCLR_ENDEPIN2_Msk (0x1UL << USBD_INTENCLR_ENDEPIN2_Pos) /*!< Bit mask of ENDEPIN2 field. */
#define USBD_INTENCLR_ENDEPIN2_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPIN2_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPIN2_Clear (1UL) /*!< Disable */

/* Bit 3 : Write '1' to Disable interrupt for ENDEPIN[1] event */
#define USBD_INTENCLR_ENDEPIN1_Pos (3UL) /*!< Position of ENDEPIN1 field. */
#define USBD_INTENCLR_ENDEPIN1_Msk (0x1UL << USBD_INTENCLR_ENDEPIN1_Pos) /*!< Bit mask of ENDEPIN1 field. */
#define USBD_INTENCLR_ENDEPIN1_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPIN1_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPIN1_Clear (1UL) /*!< Disable */

/* Bit 2 : Write '1' to Disable interrupt for ENDEPIN[0] event */
#define USBD_INTENCLR_ENDEPIN0_Pos (2UL) /*!< Position of ENDEPIN0 field. */
#define USBD_INTENCLR_ENDEPIN0_Msk (0x1UL << USBD_INTENCLR_ENDEPIN0_Pos) /*!< Bit mask of ENDEPIN0 field. */
#define USBD_INTENCLR_ENDEPIN0_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_ENDEPIN0_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_ENDEPIN0_Clear (1UL) /*!< Disable */

/* Bit 1 : Write '1' to Disable interrupt for STARTED event */
#define USBD_INTENCLR_STARTED_Pos (1UL) /*!< Position of STARTED field. */
#define USBD_INTENCLR_STARTED_Msk (0x1UL << USBD_INTENCLR_STARTED_Pos) /*!< Bit mask of STARTED field. */
#define USBD_INTENCLR_STARTED_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_STARTED_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_STARTED_Clear (1UL) /*!< Disable */

/* Bit 0 : Write '1' to Disable interrupt for USBRESET event */
#define USBD_INTENCLR_USBRESET_Pos (0UL) /*!< Position of USBRESET field. */
#define USBD_INTENCLR_USBRESET_Msk (0x1UL << USBD_INTENCLR_USBRESET_Pos) /*!< Bit mask of USBRESET field. */
#define USBD_INTENCLR_USBRESET_Disabled (0UL) /*!< Read: Disabled */
#define USBD_INTENCLR_USBRESET_Enabled (1UL) /*!< Read: Enabled */
#define USBD_INTENCLR_USBRESET_Clear (1UL) /*!< Disable */

/* Register: USBD_EVENTCAUSE */
/* Description: Details on event that caused the USBEVENT event */

/* Bit 11 : Wrapper has re-initialized SFRs to the proper values. MAC is ready for normal operation. Write '1' to clear. */
#define USBD_EVENTCAUSE_READY_Pos (11UL) /*!< Position of READY field. */
#define USBD_EVENTCAUSE_READY_Msk (0x1UL << USBD_EVENTCAUSE_READY_Pos) /*!< Bit mask of READY field. */
#define USBD_EVENTCAUSE_READY_NotDetected (0UL) /*!< USBEVENT was not issued due to USBD peripheral ready */
#define USBD_EVENTCAUSE_READY_Ready (1UL) /*!< USBD peripheral is ready */

/* Bit 9 : Signals that a RESUME condition (K state or activity restart) has been detected on the USB lines. Write '1' to clear. */
#define USBD_EVENTCAUSE_RESUME_Pos (9UL) /*!< Position of RESUME field. */
#define USBD_EVENTCAUSE_RESUME_Msk (0x1UL << USBD_EVENTCAUSE_RESUME_Pos) /*!< Bit mask of RESUME field. */
#define USBD_EVENTCAUSE_RESUME_NotDetected (0UL) /*!< Resume not detected */
#define USBD_EVENTCAUSE_RESUME_Detected (1UL) /*!< Resume detected */

/* Bit 8 : Signals that the USB lines have been seen idle long enough for the device to enter suspend. Write '1' to clear. */
#define USBD_EVENTCAUSE_SUSPEND_Pos (8UL) /*!< Position of SUSPEND field. */
#define USBD_EVENTCAUSE_SUSPEND_Msk (0x1UL << USBD_EVENTCAUSE_SUSPEND_Pos) /*!< Bit mask of SUSPEND field. */
#define USBD_EVENTCAUSE_SUSPEND_NotDetected (0UL) /*!< Suspend not detected */
#define USBD_EVENTCAUSE_SUSPEND_Detected (1UL) /*!< Suspend detected */

/* Bit 0 : CRC error was detected on isochronous OUT endpoint 8. Write '1' to clear. */
#define USBD_EVENTCAUSE_ISOOUTCRC_Pos (0UL) /*!< Position of ISOOUTCRC field. */
#define USBD_EVENTCAUSE_ISOOUTCRC_Msk (0x1UL << USBD_EVENTCAUSE_ISOOUTCRC_Pos) /*!< Bit mask of ISOOUTCRC field. */
#define USBD_EVENTCAUSE_ISOOUTCRC_NotDetected (0UL) /*!< No error detected */
#define USBD_EVENTCAUSE_ISOOUTCRC_Detected (1UL) /*!< Error detected */

/* Register: USBD_BUSSTATE */
/* Description: Provides the logic state of the D+ and D- lines */

/* Bit 1 : State of the D+ line */
#define USBD_BUSSTATE_DP_Pos (1UL) /*!< Position of DP field. */
#define USBD_BUSSTATE_DP_Msk (0x1UL << USBD_BUSSTATE_DP_Pos) /*!< Bit mask of DP field. */
#define USBD_BUSSTATE_DP_Low (0UL) /*!< Low */
#define USBD_BUSSTATE_DP_High (1UL) /*!< High */

/* Bit 0 : State of the D- line */
#define USBD_BUSSTATE_DM_Pos (0UL) /*!< Position of DM field. */
#define USBD_BUSSTATE_DM_Msk (0x1UL << USBD_BUSSTATE_DM_Pos) /*!< Bit mask of DM field. */
#define USBD_BUSSTATE_DM_Low (0UL) /*!< Low */
#define USBD_BUSSTATE_DM_High (1UL) /*!< High */

/* Register: USBD_HALTED_EPIN */
/* Description: Description collection[0]:  IN endpoint halted status. Can be used as is as response to a GetStatus() request to endpoint. */

/* Bits 15..0 : IN endpoint halted status. Can be used as is as response to a GetStatus() request to endpoint. */
#define USBD_HALTED_EPIN_GETSTATUS_Pos (0UL) /*!< Position of GETSTATUS field. */
#define USBD_HALTED_EPIN_GETSTATUS_Msk (0xFFFFUL << USBD_HALTED_EPIN_GETSTATUS_Pos) /*!< Bit mask of GETSTATUS field. */
#define USBD_HALTED_EPIN_GETSTATUS_NotHalted (0UL) /*!< Endpoint is not halted */
#define USBD_HALTED_EPIN_GETSTATUS_Halted (1UL) /*!< Endpoint is halted */

/* Register: USBD_HALTED_EPOUT */
/* Description: Description collection[0]:  OUT endpoint halted status. Can be used as is as response to a GetStatus() request to endpoint. */

/* Bits 15..0 : OUT endpoint halted status. Can be used as is as response to a GetStatus() request to endpoint. */
#define USBD_HALTED_EPOUT_GETSTATUS_Pos (0UL) /*!< Position of GETSTATUS field. */
#define USBD_HALTED_EPOUT_GETSTATUS_Msk (0xFFFFUL << USBD_HALTED_EPOUT_GETSTATUS_Pos) /*!< Bit mask of GETSTATUS field. */
#define USBD_HALTED_EPOUT_GETSTATUS_NotHalted (0UL) /*!< Endpoint is not halted */
#define USBD_HALTED_EPOUT_GETSTATUS_Halted (1UL) /*!< Endpoint is halted */

/* Register: USBD_EPSTATUS */
/* Description: Provides information on which endpoint's EasyDMA registers have been captured */

/* Bit 24 : Endpoint's EasyDMA registers captured state. Write '1' to clear. */
#define USBD_EPSTATUS_EPOUT8_Pos (24UL) /*!< Position of EPOUT8 field. */
#define USBD_EPSTATUS_EPOUT8_Msk (0x1UL << USBD_EPSTATUS_EPOUT8_Pos) /*!< Bit mask of EPOUT8 field. */
#define USBD_EPSTATUS_EPOUT8_NoData (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPOUT8_DataDone (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 23 : Endpoint's EasyDMA registers captured state. Write '1' to clear. */
#define USBD_EPSTATUS_EPOUT7_Pos (23UL) /*!< Position of EPOUT7 field. */
#define USBD_EPSTATUS_EPOUT7_Msk (0x1UL << USBD_EPSTATUS_EPOUT7_Pos) /*!< Bit mask of EPOUT7 field. */
#define USBD_EPSTATUS_EPOUT7_NoData (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPOUT7_DataDone (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 22 : Endpoint's EasyDMA registers captured state. Write '1' to clear. */
#define USBD_EPSTATUS_EPOUT6_Pos (22UL) /*!< Position of EPOUT6 field. */
#define USBD_EPSTATUS_EPOUT6_Msk (0x1UL << USBD_EPSTATUS_EPOUT6_Pos) /*!< Bit mask of EPOUT6 field. */
#define USBD_EPSTATUS_EPOUT6_NoData (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPOUT6_DataDone (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 21 : Endpoint's EasyDMA registers captured state. Write '1' to clear. */
#define USBD_EPSTATUS_EPOUT5_Pos (21UL) /*!< Position of EPOUT5 field. */
#define USBD_EPSTATUS_EPOUT5_Msk (0x1UL << USBD_EPSTATUS_EPOUT5_Pos) /*!< Bit mask of EPOUT5 field. */
#define USBD_EPSTATUS_EPOUT5_NoData (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPOUT5_DataDone (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 20 : Endpoint's EasyDMA registers captured state. Write '1' to clear. */
#define USBD_EPSTATUS_EPOUT4_Pos (20UL) /*!< Position of EPOUT4 field. */
#define USBD_EPSTATUS_EPOUT4_Msk (0x1UL << USBD_EPSTATUS_EPOUT4_Pos) /*!< Bit mask of EPOUT4 field. */
#define USBD_EPSTATUS_EPOUT4_NoData (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPOUT4_DataDone (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 19 : Endpoint's EasyDMA registers captured state. Write '1' to clear. */
#define USBD_EPSTATUS_EPOUT3_Pos (19UL) /*!< Position of EPOUT3 field. */
#define USBD_EPSTATUS_EPOUT3_Msk (0x1UL << USBD_EPSTATUS_EPOUT3_Pos) /*!< Bit mask of EPOUT3 field. */
#define USBD_EPSTATUS_EPOUT3_NoData (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPOUT3_DataDone (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 18 : Endpoint's EasyDMA registers captured state. Write '1' to clear. */
#define USBD_EPSTATUS_EPOUT2_Pos (18UL) /*!< Position of EPOUT2 field. */
#define USBD_EPSTATUS_EPOUT2_Msk (0x1UL << USBD_EPSTATUS_EPOUT2_Pos) /*!< Bit mask of EPOUT2 field. */
#define USBD_EPSTATUS_EPOUT2_NoData (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPOUT2_DataDone (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 17 : Endpoint's EasyDMA registers captured state. Write '1' to clear. */
#define USBD_EPSTATUS_EPOUT1_Pos (17UL) /*!< Position of EPOUT1 field. */
#define USBD_EPSTATUS_EPOUT1_Msk (0x1UL << USBD_EPSTATUS_EPOUT1_Pos) /*!< Bit mask of EPOUT1 field. */
#define USBD_EPSTATUS_EPOUT1_NoData (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPOUT1_DataDone (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 16 : Endpoint's EasyDMA registers captured state. Write '1' to clear. */
#define USBD_EPSTATUS_EPOUT0_Pos (16UL) /*!< Position of EPOUT0 field. */
#define USBD_EPSTATUS_EPOUT0_Msk (0x1UL << USBD_EPSTATUS_EPOUT0_Pos) /*!< Bit mask of EPOUT0 field. */
#define USBD_EPSTATUS_EPOUT0_NoData (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPOUT0_DataDone (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 8 : Endpoint's EasyDMA registers captured state. Write '1' to clear. */
#define USBD_EPSTATUS_EPIN8_Pos (8UL) /*!< Position of EPIN8 field. */
#define USBD_EPSTATUS_EPIN8_Msk (0x1UL << USBD_EPSTATUS_EPIN8_Pos) /*!< Bit mask of EPIN8 field. */
#define USBD_EPSTATUS_EPIN8_NoData (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPIN8_DataDone (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 7 : Endpoint's EasyDMA registers captured state. Write '1' to clear. */
#define USBD_EPSTATUS_EPIN7_Pos (7UL) /*!< Position of EPIN7 field. */
#define USBD_EPSTATUS_EPIN7_Msk (0x1UL << USBD_EPSTATUS_EPIN7_Pos) /*!< Bit mask of EPIN7 field. */
#define USBD_EPSTATUS_EPIN7_NoData (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPIN7_DataDone (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 6 : Endpoint's EasyDMA registers captured state. Write '1' to clear. */
#define USBD_EPSTATUS_EPIN6_Pos (6UL) /*!< Position of EPIN6 field. */
#define USBD_EPSTATUS_EPIN6_Msk (0x1UL << USBD_EPSTATUS_EPIN6_Pos) /*!< Bit mask of EPIN6 field. */
#define USBD_EPSTATUS_EPIN6_NoData (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPIN6_DataDone (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 5 : Endpoint's EasyDMA registers captured state. Write '1' to clear. */
#define USBD_EPSTATUS_EPIN5_Pos (5UL) /*!< Position of EPIN5 field. */
#define USBD_EPSTATUS_EPIN5_Msk (0x1UL << USBD_EPSTATUS_EPIN5_Pos) /*!< Bit mask of EPIN5 field. */
#define USBD_EPSTATUS_EPIN5_NoData (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPIN5_DataDone (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 4 : Endpoint's EasyDMA registers captured state. Write '1' to clear. */
#define USBD_EPSTATUS_EPIN4_Pos (4UL) /*!< Position of EPIN4 field. */
#define USBD_EPSTATUS_EPIN4_Msk (0x1UL << USBD_EPSTATUS_EPIN4_Pos) /*!< Bit mask of EPIN4 field. */
#define USBD_EPSTATUS_EPIN4_NoData (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPIN4_DataDone (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 3 : Endpoint's EasyDMA registers captured state. Write '1' to clear. */
#define USBD_EPSTATUS_EPIN3_Pos (3UL) /*!< Position of EPIN3 field. */
#define USBD_EPSTATUS_EPIN3_Msk (0x1UL << USBD_EPSTATUS_EPIN3_Pos) /*!< Bit mask of EPIN3 field. */
#define USBD_EPSTATUS_EPIN3_NoData (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPIN3_DataDone (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 2 : Endpoint's EasyDMA registers captured state. Write '1' to clear. */
#define USBD_EPSTATUS_EPIN2_Pos (2UL) /*!< Position of EPIN2 field. */
#define USBD_EPSTATUS_EPIN2_Msk (0x1UL << USBD_EPSTATUS_EPIN2_Pos) /*!< Bit mask of EPIN2 field. */
#define USBD_EPSTATUS_EPIN2_NoData (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPIN2_DataDone (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 1 : Endpoint's EasyDMA registers captured state. Write '1' to clear. */
#define USBD_EPSTATUS_EPIN1_Pos (1UL) /*!< Position of EPIN1 field. */
#define USBD_EPSTATUS_EPIN1_Msk (0x1UL << USBD_EPSTATUS_EPIN1_Pos) /*!< Bit mask of EPIN1 field. */
#define USBD_EPSTATUS_EPIN1_NoData (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPIN1_DataDone (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Bit 0 : Endpoint's EasyDMA registers captured state. Write '1' to clear. */
#define USBD_EPSTATUS_EPIN0_Pos (0UL) /*!< Position of EPIN0 field. */
#define USBD_EPSTATUS_EPIN0_Msk (0x1UL << USBD_EPSTATUS_EPIN0_Pos) /*!< Bit mask of EPIN0 field. */
#define USBD_EPSTATUS_EPIN0_NoData (0UL) /*!< EasyDMA registers have not been captured for this endpoint */
#define USBD_EPSTATUS_EPIN0_DataDone (1UL) /*!< EasyDMA registers have been captured for this endpoint */

/* Register: USBD_EPDATASTATUS */
/* Description: Provides information on which endpoint(s) an acknowledged data transfer has occurred (EPDATA event) */

/* Bit 23 : Acknowledged data transfer on this OUT endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPOUT7_Pos (23UL) /*!< Position of EPOUT7 field. */
#define USBD_EPDATASTATUS_EPOUT7_Msk (0x1UL << USBD_EPDATASTATUS_EPOUT7_Pos) /*!< Bit mask of EPOUT7 field. */
#define USBD_EPDATASTATUS_EPOUT7_NotStarted (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPOUT7_Started (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 22 : Acknowledged data transfer on this OUT endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPOUT6_Pos (22UL) /*!< Position of EPOUT6 field. */
#define USBD_EPDATASTATUS_EPOUT6_Msk (0x1UL << USBD_EPDATASTATUS_EPOUT6_Pos) /*!< Bit mask of EPOUT6 field. */
#define USBD_EPDATASTATUS_EPOUT6_NotStarted (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPOUT6_Started (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 21 : Acknowledged data transfer on this OUT endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPOUT5_Pos (21UL) /*!< Position of EPOUT5 field. */
#define USBD_EPDATASTATUS_EPOUT5_Msk (0x1UL << USBD_EPDATASTATUS_EPOUT5_Pos) /*!< Bit mask of EPOUT5 field. */
#define USBD_EPDATASTATUS_EPOUT5_NotStarted (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPOUT5_Started (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 20 : Acknowledged data transfer on this OUT endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPOUT4_Pos (20UL) /*!< Position of EPOUT4 field. */
#define USBD_EPDATASTATUS_EPOUT4_Msk (0x1UL << USBD_EPDATASTATUS_EPOUT4_Pos) /*!< Bit mask of EPOUT4 field. */
#define USBD_EPDATASTATUS_EPOUT4_NotStarted (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPOUT4_Started (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 19 : Acknowledged data transfer on this OUT endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPOUT3_Pos (19UL) /*!< Position of EPOUT3 field. */
#define USBD_EPDATASTATUS_EPOUT3_Msk (0x1UL << USBD_EPDATASTATUS_EPOUT3_Pos) /*!< Bit mask of EPOUT3 field. */
#define USBD_EPDATASTATUS_EPOUT3_NotStarted (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPOUT3_Started (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 18 : Acknowledged data transfer on this OUT endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPOUT2_Pos (18UL) /*!< Position of EPOUT2 field. */
#define USBD_EPDATASTATUS_EPOUT2_Msk (0x1UL << USBD_EPDATASTATUS_EPOUT2_Pos) /*!< Bit mask of EPOUT2 field. */
#define USBD_EPDATASTATUS_EPOUT2_NotStarted (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPOUT2_Started (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 17 : Acknowledged data transfer on this OUT endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPOUT1_Pos (17UL) /*!< Position of EPOUT1 field. */
#define USBD_EPDATASTATUS_EPOUT1_Msk (0x1UL << USBD_EPDATASTATUS_EPOUT1_Pos) /*!< Bit mask of EPOUT1 field. */
#define USBD_EPDATASTATUS_EPOUT1_NotStarted (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPOUT1_Started (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 7 : Acknowledged data transfer on this IN endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPIN7_Pos (7UL) /*!< Position of EPIN7 field. */
#define USBD_EPDATASTATUS_EPIN7_Msk (0x1UL << USBD_EPDATASTATUS_EPIN7_Pos) /*!< Bit mask of EPIN7 field. */
#define USBD_EPDATASTATUS_EPIN7_NotDone (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPIN7_DataDone (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 6 : Acknowledged data transfer on this IN endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPIN6_Pos (6UL) /*!< Position of EPIN6 field. */
#define USBD_EPDATASTATUS_EPIN6_Msk (0x1UL << USBD_EPDATASTATUS_EPIN6_Pos) /*!< Bit mask of EPIN6 field. */
#define USBD_EPDATASTATUS_EPIN6_NotDone (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPIN6_DataDone (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 5 : Acknowledged data transfer on this IN endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPIN5_Pos (5UL) /*!< Position of EPIN5 field. */
#define USBD_EPDATASTATUS_EPIN5_Msk (0x1UL << USBD_EPDATASTATUS_EPIN5_Pos) /*!< Bit mask of EPIN5 field. */
#define USBD_EPDATASTATUS_EPIN5_NotDone (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPIN5_DataDone (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 4 : Acknowledged data transfer on this IN endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPIN4_Pos (4UL) /*!< Position of EPIN4 field. */
#define USBD_EPDATASTATUS_EPIN4_Msk (0x1UL << USBD_EPDATASTATUS_EPIN4_Pos) /*!< Bit mask of EPIN4 field. */
#define USBD_EPDATASTATUS_EPIN4_NotDone (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPIN4_DataDone (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 3 : Acknowledged data transfer on this IN endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPIN3_Pos (3UL) /*!< Position of EPIN3 field. */
#define USBD_EPDATASTATUS_EPIN3_Msk (0x1UL << USBD_EPDATASTATUS_EPIN3_Pos) /*!< Bit mask of EPIN3 field. */
#define USBD_EPDATASTATUS_EPIN3_NotDone (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPIN3_DataDone (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 2 : Acknowledged data transfer on this IN endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPIN2_Pos (2UL) /*!< Position of EPIN2 field. */
#define USBD_EPDATASTATUS_EPIN2_Msk (0x1UL << USBD_EPDATASTATUS_EPIN2_Pos) /*!< Bit mask of EPIN2 field. */
#define USBD_EPDATASTATUS_EPIN2_NotDone (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPIN2_DataDone (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Bit 1 : Acknowledged data transfer on this IN endpoint. Write '1' to clear. */
#define USBD_EPDATASTATUS_EPIN1_Pos (1UL) /*!< Position of EPIN1 field. */
#define USBD_EPDATASTATUS_EPIN1_Msk (0x1UL << USBD_EPDATASTATUS_EPIN1_Pos) /*!< Bit mask of EPIN1 field. */
#define USBD_EPDATASTATUS_EPIN1_NotDone (0UL) /*!< No acknowledged data transfer on this endpoint */
#define USBD_EPDATASTATUS_EPIN1_DataDone (1UL) /*!< Acknowledged data transfer on this endpoint has occurred */

/* Register: USBD_USBADDR */
/* Description: Device USB address */

/* Bits 6..0 : Device USB address */
#define USBD_USBADDR_ADDR_Pos (0UL) /*!< Position of ADDR field. */
#define USBD_USBADDR_ADDR_Msk (0x7FUL << USBD_USBADDR_ADDR_Pos) /*!< Bit mask of ADDR field. */

/* Register: USBD_BMREQUESTTYPE */
/* Description: SETUP data, byte 0, bmRequestType */

/* Bit 7 : Data transfer direction */
#define USBD_BMREQUESTTYPE_DIRECTION_Pos (7UL) /*!< Position of DIRECTION field. */
#define USBD_BMREQUESTTYPE_DIRECTION_Msk (0x1UL << USBD_BMREQUESTTYPE_DIRECTION_Pos) /*!< Bit mask of DIRECTION field. */
#define USBD_BMREQUESTTYPE_DIRECTION_HostToDevice (0UL) /*!< Host-to-device */
#define USBD_BMREQUESTTYPE_DIRECTION_DeviceToHost (1UL) /*!< Device-to-host */

/* Bits 6..5 : Data transfer type */
#define USBD_BMREQUESTTYPE_TYPE_Pos (5UL) /*!< Position of TYPE field. */
#define USBD_BMREQUESTTYPE_TYPE_Msk (0x3UL << USBD_BMREQUESTTYPE_TYPE_Pos) /*!< Bit mask of TYPE field. */
#define USBD_BMREQUESTTYPE_TYPE_Standard (0UL) /*!< Standard */
#define USBD_BMREQUESTTYPE_TYPE_Class (1UL) /*!< Class */
#define USBD_BMREQUESTTYPE_TYPE_Vendor (2UL) /*!< Vendor */

/* Bits 4..0 : Data transfer type */
#define USBD_BMREQUESTTYPE_RECIPIENT_Pos (0UL) /*!< Position of RECIPIENT field. */
#define USBD_BMREQUESTTYPE_RECIPIENT_Msk (0x1FUL << USBD_BMREQUESTTYPE_RECIPIENT_Pos) /*!< Bit mask of RECIPIENT field. */
#define USBD_BMREQUESTTYPE_RECIPIENT_Device (0UL) /*!< Device */
#define USBD_BMREQUESTTYPE_RECIPIENT_Interface (1UL) /*!< Interface */
#define USBD_BMREQUESTTYPE_RECIPIENT_Endpoint (2UL) /*!< Endpoint */
#define USBD_BMREQUESTTYPE_RECIPIENT_Other (3UL) /*!< Other */

/* Register: USBD_BREQUEST */
/* Description: SETUP data, byte 1, bRequest */

/* Bits 7..0 : SETUP data, byte 1, bRequest. Values provides for standard requests only, user must implement Class and Vendor values. */
#define USBD_BREQUEST_BREQUEST_Pos (0UL) /*!< Position of BREQUEST field. */
#define USBD_BREQUEST_BREQUEST_Msk (0xFFUL << USBD_BREQUEST_BREQUEST_Pos) /*!< Bit mask of BREQUEST field. */
#define USBD_BREQUEST_BREQUEST_STD_GET_STATUS (0UL) /*!< Standard request GET_STATUS */
#define USBD_BREQUEST_BREQUEST_STD_CLEAR_FEATURE (1UL) /*!< Standard request CLEAR_FEATURE */
#define USBD_BREQUEST_BREQUEST_STD_SET_FEATURE (3UL) /*!< Standard request SET_FEATURE */
#define USBD_BREQUEST_BREQUEST_STD_SET_ADDRESS (5UL) /*!< Standard request SET_ADDRESS */
#define USBD_BREQUEST_BREQUEST_STD_GET_DESCRIPTOR (6UL) /*!< Standard request GET_DESCRIPTOR */
#define USBD_BREQUEST_BREQUEST_STD_SET_DESCRIPTOR (7UL) /*!< Standard request SET_DESCRIPTOR */
#define USBD_BREQUEST_BREQUEST_STD_GET_CONFIGURATION (8UL) /*!< Standard request GET_CONFIGURATION */
#define USBD_BREQUEST_BREQUEST_STD_SET_CONFIGURATION (9UL) /*!< Standard request SET_CONFIGURATION */
#define USBD_BREQUEST_BREQUEST_STD_GET_INTERFACE (10UL) /*!< Standard request GET_INTERFACE */
#define USBD_BREQUEST_BREQUEST_STD_SET_INTERFACE (11UL) /*!< Standard request SET_INTERFACE */
#define USBD_BREQUEST_BREQUEST_STD_SYNCH_FRAME (12UL) /*!< Standard request SYNCH_FRAME */

/* Register: USBD_WVALUEL */
/* Description: SETUP data, byte 2, LSB of wValue */

/* Bits 7..0 : SETUP data, byte 2, LSB of wValue */
#define USBD_WVALUEL_WVALUEL_Pos (0UL) /*!< Position of WVALUEL field. */
#define USBD_WVALUEL_WVALUEL_Msk (0xFFUL << USBD_WVALUEL_WVALUEL_Pos) /*!< Bit mask of WVALUEL field. */

/* Register: USBD_WVALUEH */
/* Description: SETUP data, byte 3, MSB of wValue */

/* Bits 7..0 : SETUP data, byte 3, MSB of wValue */
#define USBD_WVALUEH_WVALUEH_Pos (0UL) /*!< Position of WVALUEH field. */
#define USBD_WVALUEH_WVALUEH_Msk (0xFFUL << USBD_WVALUEH_WVALUEH_Pos) /*!< Bit mask of WVALUEH field. */

/* Register: USBD_WINDEXL */
/* Description: SETUP data, byte 4, LSB of wIndex */

/* Bits 7..0 : SETUP data, byte 4, LSB of wIndex */
#define USBD_WINDEXL_WINDEXL_Pos (0UL) /*!< Position of WINDEXL field. */
#define USBD_WINDEXL_WINDEXL_Msk (0xFFUL << USBD_WINDEXL_WINDEXL_Pos) /*!< Bit mask of WINDEXL field. */

/* Register: USBD_WINDEXH */
/* Description: SETUP data, byte 5, MSB of wIndex */

/* Bits 7..0 : SETUP data, byte 5, MSB of wIndex */
#define USBD_WINDEXH_WINDEXH_Pos (0UL) /*!< Position of WINDEXH field. */
#define USBD_WINDEXH_WINDEXH_Msk (0xFFUL << USBD_WINDEXH_WINDEXH_Pos) /*!< Bit mask of WINDEXH field. */

/* Register: USBD_WLENGTHL */
/* Description: SETUP data, byte 6, LSB of wLength */

/* Bits 7..0 : SETUP data, byte 6, LSB of wLength */
#define USBD_WLENGTHL_WLENGTHL_Pos (0UL) /*!< Position of WLENGTHL field. */
#define USBD_WLENGTHL_WLENGTHL_Msk (0xFFUL << USBD_WLENGTHL_WLENGTHL_Pos) /*!< Bit mask of WLENGTHL field. */

/* Register: USBD_WLENGTHH */
/* Description: SETUP data, byte 7, MSB of wLength */

/* Bits 7..0 : SETUP data, byte 7, MSB of wLength */
#define USBD_WLENGTHH_WLENGTHH_Pos (0UL) /*!< Position of WLENGTHH field. */
#define USBD_WLENGTHH_WLENGTHH_Msk (0xFFUL << USBD_WLENGTHH_WLENGTHH_Pos) /*!< Bit mask of WLENGTHH field. */

/* Register: USBD_SIZE_EPOUT */
/* Description: Description collection[0]:  Amount of bytes received last in the data stage of this OUT endpoint */

/* Bits 6..0 : Amount of bytes received last in the data stage of this OUT endpoint */
#define USBD_SIZE_EPOUT_SIZE_Pos (0UL) /*!< Position of SIZE field. */
#define USBD_SIZE_EPOUT_SIZE_Msk (0x7FUL << USBD_SIZE_EPOUT_SIZE_Pos) /*!< Bit mask of SIZE field. */

/* Register: USBD_SIZE_ISOOUT */
/* Description: Amount of bytes received last on this iso OUT data endpoint */

/* Bit 16 : Zero-length data packet received */
#define USBD_SIZE_ISOOUT_ZERO_Pos (16UL) /*!< Position of ZERO field. */
#define USBD_SIZE_ISOOUT_ZERO_Msk (0x1UL << USBD_SIZE_ISOOUT_ZERO_Pos) /*!< Bit mask of ZERO field. */
#define USBD_SIZE_ISOOUT_ZERO_Normal (0UL) /*!< No zero-length data received, use value in SIZE */
#define USBD_SIZE_ISOOUT_ZERO_ZeroData (1UL) /*!< Zero-length data received, ignore value in SIZE */

/* Bits 9..0 : Amount of bytes received last on this iso OUT data endpoint */
#define USBD_SIZE_ISOOUT_SIZE_Pos (0UL) /*!< Position of SIZE field. */
#define USBD_SIZE_ISOOUT_SIZE_Msk (0x3FFUL << USBD_SIZE_ISOOUT_SIZE_Pos) /*!< Bit mask of SIZE field. */

/* Register: USBD_ENABLE */
/* Description: Enable USB */

/* Bit 0 : Enable USB */
#define USBD_ENABLE_ENABLE_Pos (0UL) /*!< Position of ENABLE field. */
#define USBD_ENABLE_ENABLE_Msk (0x1UL << USBD_ENABLE_ENABLE_Pos) /*!< Bit mask of ENABLE field. */
#define USBD_ENABLE_ENABLE_Disabled (0UL) /*!< USB peripheral is disabled */
#define USBD_ENABLE_ENABLE_Enabled (1UL) /*!< USB peripheral is enabled */

/* Register: USBD_USBPULLUP */
/* Description: Control of the USB pull-up */

/* Bit 0 : Control of the USB pull-up on the D+ line */
#define USBD_USBPULLUP_CONNECT_Pos (0UL) /*!< Position of CONNECT field. */
#define USBD_USBPULLUP_CONNECT_Msk (0x1UL << USBD_USBPULLUP_CONNECT_Pos) /*!< Bit mask of CONNECT field. */
#define USBD_USBPULLUP_CONNECT_Disabled (0UL) /*!< Pull-up is disconnected */
#define USBD_USBPULLUP_CONNECT_Enabled (1UL) /*!< Pull-up is connected to D+ */

/* Register: USBD_DPDMVALUE */
/* Description: State at which the DPDMDRIVE task will force D+ and D-. The DPDMNODRIVE task reverts the control of the lines to MAC IP (no forcing). */

/* Bits 4..0 : State at which the DPDMDRIVE task will force D+ and D- */
#define USBD_DPDMVALUE_STATE_Pos (0UL) /*!< Position of STATE field. */
#define USBD_DPDMVALUE_STATE_Msk (0x1FUL << USBD_DPDMVALUE_STATE_Pos) /*!< Bit mask of STATE field. */
#define USBD_DPDMVALUE_STATE_Resume (1UL) /*!< D+ forced low, D- forced high (K state) for a timing pre-set in hardware (50 us or 5 ms, depending on bus state) */
#define USBD_DPDMVALUE_STATE_J (2UL) /*!< D+ forced high, D- forced low (J state) */
#define USBD_DPDMVALUE_STATE_K (4UL) /*!< D+ forced low, D- forced high (K state) */

/* Register: USBD_DTOGGLE */
/* Description: Data toggle control and status. */

/* Bits 9..8 : Data toggle value */
#define USBD_DTOGGLE_VALUE_Pos (8UL) /*!< Position of VALUE field. */
#define USBD_DTOGGLE_VALUE_Msk (0x3UL << USBD_DTOGGLE_VALUE_Pos) /*!< Bit mask of VALUE field. */
#define USBD_DTOGGLE_VALUE_Nop (0UL) /*!< No action on data toggle when writing the register with this value */
#define USBD_DTOGGLE_VALUE_Data0 (1UL) /*!< Data toggle is DATA0 on endpoint set by EP and IO */
#define USBD_DTOGGLE_VALUE_Data1 (2UL) /*!< Data toggle is DATA1 on endpoint set by EP and IO */

/* Bit 7 : Selects IN or OUT endpoint */
#define USBD_DTOGGLE_IO_Pos (7UL) /*!< Position of IO field. */
#define USBD_DTOGGLE_IO_Msk (0x1UL << USBD_DTOGGLE_IO_Pos) /*!< Bit mask of IO field. */
#define USBD_DTOGGLE_IO_Out (0UL) /*!< Selects OUT endpoint */
#define USBD_DTOGGLE_IO_In (1UL) /*!< Selects IN endpoint */

/* Bits 2..0 : Select bulk endpoint number */
#define USBD_DTOGGLE_EP_Pos (0UL) /*!< Position of EP field. */
#define USBD_DTOGGLE_EP_Msk (0x7UL << USBD_DTOGGLE_EP_Pos) /*!< Bit mask of EP field. */

/* Register: USBD_EPINEN */
/* Description: Endpoint IN enable */

/* Bit 8 : Enable iso IN endpoint */
#define USBD_EPINEN_ISOIN_Pos (8UL) /*!< Position of ISOIN field. */
#define USBD_EPINEN_ISOIN_Msk (0x1UL << USBD_EPINEN_ISOIN_Pos) /*!< Bit mask of ISOIN field. */
#define USBD_EPINEN_ISOIN_Disable (0UL) /*!< Disable iso IN endpoint 8 */
#define USBD_EPINEN_ISOIN_Enable (1UL) /*!< Enable iso IN endpoint 8 */

/* Bit 7 : Enable IN endpoint 7 */
#define USBD_EPINEN_IN7_Pos (7UL) /*!< Position of IN7 field. */
#define USBD_EPINEN_IN7_Msk (0x1UL << USBD_EPINEN_IN7_Pos) /*!< Bit mask of IN7 field. */
#define USBD_EPINEN_IN7_Disable (0UL) /*!< Disable endpoint IN 7 (no response to IN tokens) */
#define USBD_EPINEN_IN7_Enable (1UL) /*!< Enable endpoint IN 7 (response to IN tokens) */

/* Bit 6 : Enable IN endpoint 6 */
#define USBD_EPINEN_IN6_Pos (6UL) /*!< Position of IN6 field. */
#define USBD_EPINEN_IN6_Msk (0x1UL << USBD_EPINEN_IN6_Pos) /*!< Bit mask of IN6 field. */
#define USBD_EPINEN_IN6_Disable (0UL) /*!< Disable endpoint IN 6 (no response to IN tokens) */
#define USBD_EPINEN_IN6_Enable (1UL) /*!< Enable endpoint IN 6 (response to IN tokens) */

/* Bit 5 : Enable IN endpoint 5 */
#define USBD_EPINEN_IN5_Pos (5UL) /*!< Position of IN5 field. */
#define USBD_EPINEN_IN5_Msk (0x1UL << USBD_EPINEN_IN5_Pos) /*!< Bit mask of IN5 field. */
#define USBD_EPINEN_IN5_Disable (0UL) /*!< Disable endpoint IN 5 (no response to IN tokens) */
#define USBD_EPINEN_IN5_Enable (1UL) /*!< Enable endpoint IN 5 (response to IN tokens) */

/* Bit 4 : Enable IN endpoint 4 */
#define USBD_EPINEN_IN4_Pos (4UL) /*!< Position of IN4 field. */
#define USBD_EPINEN_IN4_Msk (0x1UL << USBD_EPINEN_IN4_Pos) /*!< Bit mask of IN4 field. */
#define USBD_EPINEN_IN4_Disable (0UL) /*!< Disable endpoint IN 4 (no response to IN tokens) */
#define USBD_EPINEN_IN4_Enable (1UL) /*!< Enable endpoint IN 4 (response to IN tokens) */

/* Bit 3 : Enable IN endpoint 3 */
#define USBD_EPINEN_IN3_Pos (3UL) /*!< Position of IN3 field. */
#define USBD_EPINEN_IN3_Msk (0x1UL << USBD_EPINEN_IN3_Pos) /*!< Bit mask of IN3 field. */
#define USBD_EPINEN_IN3_Disable (0UL) /*!< Disable endpoint IN 3 (no response to IN tokens) */
#define USBD_EPINEN_IN3_Enable (1UL) /*!< Enable endpoint IN 3 (response to IN tokens) */

/* Bit 2 : Enable IN endpoint 2 */
#define USBD_EPINEN_IN2_Pos (2UL) /*!< Position of IN2 field. */
#define USBD_EPINEN_IN2_Msk (0x1UL << USBD_EPINEN_IN2_Pos) /*!< Bit mask of IN2 field. */
#define USBD_EPINEN_IN2_Disable (0UL) /*!< Disable endpoint IN 2 (no response to IN tokens) */
#define USBD_EPINEN_IN2_Enable (1UL) /*!< Enable endpoint IN 2 (response to IN tokens) */

/* Bit 1 : Enable IN endpoint 1 */
#define USBD_EPINEN_IN1_Pos (1UL) /*!< Position of IN1 field. */
#define USBD_EPINEN_IN1_Msk (0x1UL << USBD_EPINEN_IN1_Pos) /*!< Bit mask of IN1 field. */
#define USBD_EPINEN_IN1_Disable (0UL) /*!< Disable endpoint IN 1 (no response to IN tokens) */
#define USBD_EPINEN_IN1_Enable (1UL) /*!< Enable endpoint IN 1 (response to IN tokens) */

/* Bit 0 : Enable IN endpoint 0 */
#define USBD_EPINEN_IN0_Pos (0UL) /*!< Position of IN0 field. */
#define USBD_EPINEN_IN0_Msk (0x1UL << USBD_EPINEN_IN0_Pos) /*!< Bit mask of IN0 field. */
#define USBD_EPINEN_IN0_Disable (0UL) /*!< Disable endpoint IN 0 (no response to IN tokens) */
#define USBD_EPINEN_IN0_Enable (1UL) /*!< Enable endpoint IN 0 (response to IN tokens) */

/* Register: USBD_EPOUTEN */
/* Description: Endpoint OUT enable */

/* Bit 8 : Enable iso OUT endpoint 8 */
#define USBD_EPOUTEN_ISOOUT_Pos (8UL) /*!< Position of ISOOUT field. */
#define USBD_EPOUTEN_ISOOUT_Msk (0x1UL << USBD_EPOUTEN_ISOOUT_Pos) /*!< Bit mask of ISOOUT field. */
#define USBD_EPOUTEN_ISOOUT_Disable (0UL) /*!< Disable iso OUT endpoint 8 */
#define USBD_EPOUTEN_ISOOUT_Enable (1UL) /*!< Enable iso OUT endpoint 8 */

/* Bit 7 : Enable OUT endpoint 7 */
#define USBD_EPOUTEN_OUT7_Pos (7UL) /*!< Position of OUT7 field. */
#define USBD_EPOUTEN_OUT7_Msk (0x1UL << USBD_EPOUTEN_OUT7_Pos) /*!< Bit mask of OUT7 field. */
#define USBD_EPOUTEN_OUT7_Disable (0UL) /*!< Disable endpoint OUT 7 (no response to OUT tokens) */
#define USBD_EPOUTEN_OUT7_Enable (1UL) /*!< Enable endpoint OUT 7 (response to OUT tokens) */

/* Bit 6 : Enable OUT endpoint 6 */
#define USBD_EPOUTEN_OUT6_Pos (6UL) /*!< Position of OUT6 field. */
#define USBD_EPOUTEN_OUT6_Msk (0x1UL << USBD_EPOUTEN_OUT6_Pos) /*!< Bit mask of OUT6 field. */
#define USBD_EPOUTEN_OUT6_Disable (0UL) /*!< Disable endpoint OUT 6 (no response to OUT tokens) */
#define USBD_EPOUTEN_OUT6_Enable (1UL) /*!< Enable endpoint OUT 6 (response to OUT tokens) */

/* Bit 5 : Enable OUT endpoint 5 */
#define USBD_EPOUTEN_OUT5_Pos (5UL) /*!< Position of OUT5 field. */
#define USBD_EPOUTEN_OUT5_Msk (0x1UL << USBD_EPOUTEN_OUT5_Pos) /*!< Bit mask of OUT5 field. */
#define USBD_EPOUTEN_OUT5_Disable (0UL) /*!< Disable endpoint OUT 5 (no response to OUT tokens) */
#define USBD_EPOUTEN_OUT5_Enable (1UL) /*!< Enable endpoint OUT 5 (response to OUT tokens) */

/* Bit 4 : Enable OUT endpoint 4 */
#define USBD_EPOUTEN_OUT4_Pos (4UL) /*!< Position of OUT4 field. */
#define USBD_EPOUTEN_OUT4_Msk (0x1UL << USBD_EPOUTEN_OUT4_Pos) /*!< Bit mask of OUT4 field. */
#define USBD_EPOUTEN_OUT4_Disable (0UL) /*!< Disable endpoint OUT 4 (no response to OUT tokens) */
#define USBD_EPOUTEN_OUT4_Enable (1UL) /*!< Enable endpoint OUT 4 (response to OUT tokens) */

/* Bit 3 : Enable OUT endpoint 3 */
#define USBD_EPOUTEN_OUT3_Pos (3UL) /*!< Position of OUT3 field. */
#define USBD_EPOUTEN_OUT3_Msk (0x1UL << USBD_EPOUTEN_OUT3_Pos) /*!< Bit mask of OUT3 field. */
#define USBD_EPOUTEN_OUT3_Disable (0UL) /*!< Disable endpoint OUT 3 (no response to OUT tokens) */
#define USBD_EPOUTEN_OUT3_Enable (1UL) /*!< Enable endpoint OUT 3 (response to OUT tokens) */

/* Bit 2 : Enable OUT endpoint 2 */
#define USBD_EPOUTEN_OUT2_Pos (2UL) /*!< Position of OUT2 field. */
#define USBD_EPOUTEN_OUT2_Msk (0x1UL << USBD_EPOUTEN_OUT2_Pos) /*!< Bit mask of OUT2 field. */
#define USBD_EPOUTEN_OUT2_Disable (0UL) /*!< Disable endpoint OUT 2 (no response to OUT tokens) */
#define USBD_EPOUTEN_OUT2_Enable (1UL) /*!< Enable endpoint OUT 2 (response to OUT tokens) */

/* Bit 1 : Enable OUT endpoint 1 */
#define USBD_EPOUTEN_OUT1_Pos (1UL) /*!< Position of OUT1 field. */
#define USBD_EPOUTEN_OUT1_Msk (0x1UL << USBD_EPOUTEN_OUT1_Pos) /*!< Bit mask of OUT1 field. */
#define USBD_EPOUTEN_OUT1_Disable (0UL) /*!< Disable endpoint OUT 1 (no response to OUT tokens) */
#define USBD_EPOUTEN_OUT1_Enable (1UL) /*!< Enable endpoint OUT 1 (response to OUT tokens) */

/* Bit 0 : Enable OUT endpoint 0 */
#define USBD_EPOUTEN_OUT0_Pos (0UL) /*!< Position of OUT0 field. */
#define USBD_EPOUTEN_OUT0_Msk (0x1UL << USBD_EPOUTEN_OUT0_Pos) /*!< Bit mask of OUT0 field. */
#define USBD_EPOUTEN_OUT0_Disable (0UL) /*!< Disable endpoint OUT 0 (no response to OUT tokens) */
#define USBD_EPOUTEN_OUT0_Enable (1UL) /*!< Enable endpoint OUT 0 (response to OUT tokens) */

/* Register: USBD_EPSTALL */
/* Description: STALL endpoints */

/* Bit 8 : Stall selected endpoint */
#define USBD_EPSTALL_STALL_Pos (8UL) /*!< Position of STALL field. */
#define USBD_EPSTALL_STALL_Msk (0x1UL << USBD_EPSTALL_STALL_Pos) /*!< Bit mask of STALL field. */
#define USBD_EPSTALL_STALL_UnStall (0UL) /*!< Don't stall selected endpoint */
#define USBD_EPSTALL_STALL_Stall (1UL) /*!< Stall selected endpoint */

/* Bit 7 : Selects IN or OUT endpoint */
#define USBD_EPSTALL_IO_Pos (7UL) /*!< Position of IO field. */
#define USBD_EPSTALL_IO_Msk (0x1UL << USBD_EPSTALL_IO_Pos) /*!< Bit mask of IO field. */
#define USBD_EPSTALL_IO_Out (0UL) /*!< Selects OUT endpoint */
#define USBD_EPSTALL_IO_In (1UL) /*!< Selects IN endpoint */

/* Bits 2..0 : Select endpoint number */
#define USBD_EPSTALL_EP_Pos (0UL) /*!< Position of EP field. */
#define USBD_EPSTALL_EP_Msk (0x7UL << USBD_EPSTALL_EP_Pos) /*!< Bit mask of EP field. */

/* Register: USBD_ISOSPLIT */
/* Description: Controls the split of ISO buffers */

/* Bits 15..0 : Controls the split of ISO buffers */
#define USBD_ISOSPLIT_SPLIT_Pos (0UL) /*!< Position of SPLIT field. */
#define USBD_ISOSPLIT_SPLIT_Msk (0xFFFFUL << USBD_ISOSPLIT_SPLIT_Pos) /*!< Bit mask of SPLIT field. */
#define USBD_ISOSPLIT_SPLIT_OneDir (0x0000UL) /*!< Full buffer dedicated to either iso IN or OUT */
#define USBD_ISOSPLIT_SPLIT_HalfIN (0x0080UL) /*!< Lower half for IN, upper half for OUT */

/* Register: USBD_FRAMECNTR */
/* Description: Returns the current value of the start of frame counter */

/* Bits 10..0 : Returns the current value of the start of frame counter */
#define USBD_FRAMECNTR_FRAMECNTR_Pos (0UL) /*!< Position of FRAMECNTR field. */
#define USBD_FRAMECNTR_FRAMECNTR_Msk (0x7FFUL << USBD_FRAMECNTR_FRAMECNTR_Pos) /*!< Bit mask of FRAMECNTR field. */

/* Register: USBD_ISOINCONFIG */
/* Description: Controls the response of the ISO IN endpoint to an IN token when no data is ready to be sent */

/* Bit 0 : Controls the response of the ISO IN endpoint to an IN token when no data is ready to be sent */
#define USBD_ISOINCONFIG_RESPONSE_Pos (0UL) /*!< Position of RESPONSE field. */
#define USBD_ISOINCONFIG_RESPONSE_Msk (0x1UL << USBD_ISOINCONFIG_RESPONSE_Pos) /*!< Bit mask of RESPONSE field. */
#define USBD_ISOINCONFIG_RESPONSE_NoResp (0UL) /*!< Endpoint does not respond in that case */
#define USBD_ISOINCONFIG_RESPONSE_ZeroData (1UL) /*!< Endpoint responds with a zero-length data packet in that case */

/* Register: USBD_EPIN_PTR */
/* Description: Description cluster[0]:  Data pointer */

/* Bits 31..0 : Data pointer. Accepts any address in Data RAM. */
#define USBD_EPIN_PTR_PTR_Pos (0UL) /*!< Position of PTR field. */
#define USBD_EPIN_PTR_PTR_Msk (0xFFFFFFFFUL << USBD_EPIN_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: USBD_EPIN_MAXCNT */
/* Description: Description cluster[0]:  Maximum number of bytes to transfer */

/* Bits 6..0 : Maximum number of bytes to transfer */
#define USBD_EPIN_MAXCNT_MAXCNT_Pos (0UL) /*!< Position of MAXCNT field. */
#define USBD_EPIN_MAXCNT_MAXCNT_Msk (0x7FUL << USBD_EPIN_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: USBD_EPIN_AMOUNT */
/* Description: Description cluster[0]:  Number of bytes transferred in the last transaction */

/* Bits 6..0 : Number of bytes transferred in the last transaction */
#define USBD_EPIN_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define USBD_EPIN_AMOUNT_AMOUNT_Msk (0x7FUL << USBD_EPIN_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: USBD_ISOIN_PTR */
/* Description: Data pointer */

/* Bits 31..0 : Data pointer. Accepts any address in Data RAM. */
#define USBD_ISOIN_PTR_PTR_Pos (0UL) /*!< Position of PTR field. */
#define USBD_ISOIN_PTR_PTR_Msk (0xFFFFFFFFUL << USBD_ISOIN_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: USBD_ISOIN_MAXCNT */
/* Description: Maximum number of bytes to transfer */

/* Bits 9..0 : Maximum number of bytes to transfer */
#define USBD_ISOIN_MAXCNT_MAXCNT_Pos (0UL) /*!< Position of MAXCNT field. */
#define USBD_ISOIN_MAXCNT_MAXCNT_Msk (0x3FFUL << USBD_ISOIN_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: USBD_ISOIN_AMOUNT */
/* Description: Number of bytes transferred in the last transaction */

/* Bits 9..0 : Number of bytes transferred in the last transaction */
#define USBD_ISOIN_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define USBD_ISOIN_AMOUNT_AMOUNT_Msk (0x3FFUL << USBD_ISOIN_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: USBD_EPOUT_PTR */
/* Description: Description cluster[0]:  Data pointer */

/* Bits 31..0 : Data pointer. Accepts any address in Data RAM. */
#define USBD_EPOUT_PTR_PTR_Pos (0UL) /*!< Position of PTR field. */
#define USBD_EPOUT_PTR_PTR_Msk (0xFFFFFFFFUL << USBD_EPOUT_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: USBD_EPOUT_MAXCNT */
/* Description: Description cluster[0]:  Maximum number of bytes to transfer */

/* Bits 6..0 : Maximum number of bytes to transfer */
#define USBD_EPOUT_MAXCNT_MAXCNT_Pos (0UL) /*!< Position of MAXCNT field. */
#define USBD_EPOUT_MAXCNT_MAXCNT_Msk (0x7FUL << USBD_EPOUT_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: USBD_EPOUT_AMOUNT */
/* Description: Description cluster[0]:  Number of bytes transferred in the last transaction */

/* Bits 6..0 : Number of bytes transferred in the last transaction */
#define USBD_EPOUT_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define USBD_EPOUT_AMOUNT_AMOUNT_Msk (0x7FUL << USBD_EPOUT_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */

/* Register: USBD_ISOOUT_PTR */
/* Description: Data pointer */

/* Bits 31..0 : Data pointer. Accepts any address in Data RAM. */
#define USBD_ISOOUT_PTR_PTR_Pos (0UL) /*!< Position of PTR field. */
#define USBD_ISOOUT_PTR_PTR_Msk (0xFFFFFFFFUL << USBD_ISOOUT_PTR_PTR_Pos) /*!< Bit mask of PTR field. */

/* Register: USBD_ISOOUT_MAXCNT */
/* Description: Maximum number of bytes to transfer */

/* Bits 9..0 : Maximum number of bytes to transfer */
#define USBD_ISOOUT_MAXCNT_MAXCNT_Pos (0UL) /*!< Position of MAXCNT field. */
#define USBD_ISOOUT_MAXCNT_MAXCNT_Msk (0x3FFUL << USBD_ISOOUT_MAXCNT_MAXCNT_Pos) /*!< Bit mask of MAXCNT field. */

/* Register: USBD_ISOOUT_AMOUNT */
/* Description: Number of bytes transferred in the last transaction */

/* Bits 9..0 : Number of bytes transferred in the last transaction */
#define USBD_ISOOUT_AMOUNT_AMOUNT_Pos (0UL) /*!< Position of AMOUNT field. */
#define USBD_ISOOUT_AMOUNT_AMOUNT_Msk (0x3FFUL << USBD_ISOOUT_AMOUNT_AMOUNT_Pos) /*!< Bit mask of AMOUNT field. */


/* Peripheral: WDT */
/* Description: Watchdog Timer */

/* Register: WDT_INTENSET */
/* Description: Enable interrupt */

/* Bit 0 : Write '1' to Enable interrupt for TIMEOUT event */
#define WDT_INTENSET_TIMEOUT_Pos (0UL) /*!< Position of TIMEOUT field. */
#define WDT_INTENSET_TIMEOUT_Msk (0x1UL << WDT_INTENSET_TIMEOUT_Pos) /*!< Bit mask of TIMEOUT field. */
#define WDT_INTENSET_TIMEOUT_Disabled (0UL) /*!< Read: Disabled */
#define WDT_INTENSET_TIMEOUT_Enabled (1UL) /*!< Read: Enabled */
#define WDT_INTENSET_TIMEOUT_Set (1UL) /*!< Enable */

/* Register: WDT_INTENCLR */
/* Description: Disable interrupt */

/* Bit 0 : Write '1' to Disable interrupt for TIMEOUT event */
#define WDT_INTENCLR_TIMEOUT_Pos (0UL) /*!< Position of TIMEOUT field. */
#define WDT_INTENCLR_TIMEOUT_Msk (0x1UL << WDT_INTENCLR_TIMEOUT_Pos) /*!< Bit mask of TIMEOUT field. */
#define WDT_INTENCLR_TIMEOUT_Disabled (0UL) /*!< Read: Disabled */
#define WDT_INTENCLR_TIMEOUT_Enabled (1UL) /*!< Read: Enabled */
#define WDT_INTENCLR_TIMEOUT_Clear (1UL) /*!< Disable */

/* Register: WDT_RUNSTATUS */
/* Description: Run status */

/* Bit 0 : Indicates whether or not the watchdog is running */
#define WDT_RUNSTATUS_RUNSTATUS_Pos (0UL) /*!< Position of RUNSTATUS field. */
#define WDT_RUNSTATUS_RUNSTATUS_Msk (0x1UL << WDT_RUNSTATUS_RUNSTATUS_Pos) /*!< Bit mask of RUNSTATUS field. */
#define WDT_RUNSTATUS_RUNSTATUS_NotRunning (0UL) /*!< Watchdog not running */
#define WDT_RUNSTATUS_RUNSTATUS_Running (1UL) /*!< Watchdog is running */

/* Register: WDT_REQSTATUS */
/* Description: Request status */

/* Bit 7 : Request status for RR[7] register */
#define WDT_REQSTATUS_RR7_Pos (7UL) /*!< Position of RR7 field. */
#define WDT_REQSTATUS_RR7_Msk (0x1UL << WDT_REQSTATUS_RR7_Pos) /*!< Bit mask of RR7 field. */
#define WDT_REQSTATUS_RR7_DisabledOrRequested (0UL) /*!< RR[7] register is not enabled, or are already requesting reload */
#define WDT_REQSTATUS_RR7_EnabledAndUnrequested (1UL) /*!< RR[7] register is enabled, and are not yet requesting reload */

/* Bit 6 : Request status for RR[6] register */
#define WDT_REQSTATUS_RR6_Pos (6UL) /*!< Position of RR6 field. */
#define WDT_REQSTATUS_RR6_Msk (0x1UL << WDT_REQSTATUS_RR6_Pos) /*!< Bit mask of RR6 field. */
#define WDT_REQSTATUS_RR6_DisabledOrRequested (0UL) /*!< RR[6] register is not enabled, or are already requesting reload */
#define WDT_REQSTATUS_RR6_EnabledAndUnrequested (1UL) /*!< RR[6] register is enabled, and are not yet requesting reload */

/* Bit 5 : Request status for RR[5] register */
#define WDT_REQSTATUS_RR5_Pos (5UL) /*!< Position of RR5 field. */
#define WDT_REQSTATUS_RR5_Msk (0x1UL << WDT_REQSTATUS_RR5_Pos) /*!< Bit mask of RR5 field. */
#define WDT_REQSTATUS_RR5_DisabledOrRequested (0UL) /*!< RR[5] register is not enabled, or are already requesting reload */
#define WDT_REQSTATUS_RR5_EnabledAndUnrequested (1UL) /*!< RR[5] register is enabled, and are not yet requesting reload */

/* Bit 4 : Request status for RR[4] register */
#define WDT_REQSTATUS_RR4_Pos (4UL) /*!< Position of RR4 field. */
#define WDT_REQSTATUS_RR4_Msk (0x1UL << WDT_REQSTATUS_RR4_Pos) /*!< Bit mask of RR4 field. */
#define WDT_REQSTATUS_RR4_DisabledOrRequested (0UL) /*!< RR[4] register is not enabled, or are already requesting reload */
#define WDT_REQSTATUS_RR4_EnabledAndUnrequested (1UL) /*!< RR[4] register is enabled, and are not yet requesting reload */

/* Bit 3 : Request status for RR[3] register */
#define WDT_REQSTATUS_RR3_Pos (3UL) /*!< Position of RR3 field. */
#define WDT_REQSTATUS_RR3_Msk (0x1UL << WDT_REQSTATUS_RR3_Pos) /*!< Bit mask of RR3 field. */
#define WDT_REQSTATUS_RR3_DisabledOrRequested (0UL) /*!< RR[3] register is not enabled, or are already requesting reload */
#define WDT_REQSTATUS_RR3_EnabledAndUnrequested (1UL) /*!< RR[3] register is enabled, and are not yet requesting reload */

/* Bit 2 : Request status for RR[2] register */
#define WDT_REQSTATUS_RR2_Pos (2UL) /*!< Position of RR2 field. */
#define WDT_REQSTATUS_RR2_Msk (0x1UL << WDT_REQSTATUS_RR2_Pos) /*!< Bit mask of RR2 field. */
#define WDT_REQSTATUS_RR2_DisabledOrRequested (0UL) /*!< RR[2] register is not enabled, or are already requesting reload */
#define WDT_REQSTATUS_RR2_EnabledAndUnrequested (1UL) /*!< RR[2] register is enabled, and are not yet requesting reload */

/* Bit 1 : Request status for RR[1] register */
#define WDT_REQSTATUS_RR1_Pos (1UL) /*!< Position of RR1 field. */
#define WDT_REQSTATUS_RR1_Msk (0x1UL << WDT_REQSTATUS_RR1_Pos) /*!< Bit mask of RR1 field. */
#define WDT_REQSTATUS_RR1_DisabledOrRequested (0UL) /*!< RR[1] register is not enabled, or are already requesting reload */
#define WDT_REQSTATUS_RR1_EnabledAndUnrequested (1UL) /*!< RR[1] register is enabled, and are not yet requesting reload */

/* Bit 0 : Request status for RR[0] register */
#define WDT_REQSTATUS_RR0_Pos (0UL) /*!< Position of RR0 field. */
#define WDT_REQSTATUS_RR0_Msk (0x1UL << WDT_REQSTATUS_RR0_Pos) /*!< Bit mask of RR0 field. */
#define WDT_REQSTATUS_RR0_DisabledOrRequested (0UL) /*!< RR[0] register is not enabled, or are already requesting reload */
#define WDT_REQSTATUS_RR0_EnabledAndUnrequested (1UL) /*!< RR[0] register is enabled, and are not yet requesting reload */

/* Register: WDT_CRV */
/* Description: Counter reload value */

/* Bits 31..0 : Counter reload value in number of cycles of the 32.768 kHz clock */
#define WDT_CRV_CRV_Pos (0UL) /*!< Position of CRV field. */
#define WDT_CRV_CRV_Msk (0xFFFFFFFFUL << WDT_CRV_CRV_Pos) /*!< Bit mask of CRV field. */

/* Register: WDT_RREN */
/* Description: Enable register for reload request registers */

/* Bit 7 : Enable or disable RR[7] register */
#define WDT_RREN_RR7_Pos (7UL) /*!< Position of RR7 field. */
#define WDT_RREN_RR7_Msk (0x1UL << WDT_RREN_RR7_Pos) /*!< Bit mask of RR7 field. */
#define WDT_RREN_RR7_Disabled (0UL) /*!< Disable RR[7] register */
#define WDT_RREN_RR7_Enabled (1UL) /*!< Enable RR[7] register */

/* Bit 6 : Enable or disable RR[6] register */
#define WDT_RREN_RR6_Pos (6UL) /*!< Position of RR6 field. */
#define WDT_RREN_RR6_Msk (0x1UL << WDT_RREN_RR6_Pos) /*!< Bit mask of RR6 field. */
#define WDT_RREN_RR6_Disabled (0UL) /*!< Disable RR[6] register */
#define WDT_RREN_RR6_Enabled (1UL) /*!< Enable RR[6] register */

/* Bit 5 : Enable or disable RR[5] register */
#define WDT_RREN_RR5_Pos (5UL) /*!< Position of RR5 field. */
#define WDT_RREN_RR5_Msk (0x1UL << WDT_RREN_RR5_Pos) /*!< Bit mask of RR5 field. */
#define WDT_RREN_RR5_Disabled (0UL) /*!< Disable RR[5] register */
#define WDT_RREN_RR5_Enabled (1UL) /*!< Enable RR[5] register */

/* Bit 4 : Enable or disable RR[4] register */
#define WDT_RREN_RR4_Pos (4UL) /*!< Position of RR4 field. */
#define WDT_RREN_RR4_Msk (0x1UL << WDT_RREN_RR4_Pos) /*!< Bit mask of RR4 field. */
#define WDT_RREN_RR4_Disabled (0UL) /*!< Disable RR[4] register */
#define WDT_RREN_RR4_Enabled (1UL) /*!< Enable RR[4] register */

/* Bit 3 : Enable or disable RR[3] register */
#define WDT_RREN_RR3_Pos (3UL) /*!< Position of RR3 field. */
#define WDT_RREN_RR3_Msk (0x1UL << WDT_RREN_RR3_Pos) /*!< Bit mask of RR3 field. */
#define WDT_RREN_RR3_Disabled (0UL) /*!< Disable RR[3] register */
#define WDT_RREN_RR3_Enabled (1UL) /*!< Enable RR[3] register */

/* Bit 2 : Enable or disable RR[2] register */
#define WDT_RREN_RR2_Pos (2UL) /*!< Position of RR2 field. */
#define WDT_RREN_RR2_Msk (0x1UL << WDT_RREN_RR2_Pos) /*!< Bit mask of RR2 field. */
#define WDT_RREN_RR2_Disabled (0UL) /*!< Disable RR[2] register */
#define WDT_RREN_RR2_Enabled (1UL) /*!< Enable RR[2] register */

/* Bit 1 : Enable or disable RR[1] register */
#define WDT_RREN_RR1_Pos (1UL) /*!< Position of RR1 field. */
#define WDT_RREN_RR1_Msk (0x1UL << WDT_RREN_RR1_Pos) /*!< Bit mask of RR1 field. */
#define WDT_RREN_RR1_Disabled (0UL) /*!< Disable RR[1] register */
#define WDT_RREN_RR1_Enabled (1UL) /*!< Enable RR[1] register */

/* Bit 0 : Enable or disable RR[0] register */
#define WDT_RREN_RR0_Pos (0UL) /*!< Position of RR0 field. */
#define WDT_RREN_RR0_Msk (0x1UL << WDT_RREN_RR0_Pos) /*!< Bit mask of RR0 field. */
#define WDT_RREN_RR0_Disabled (0UL) /*!< Disable RR[0] register */
#define WDT_RREN_RR0_Enabled (1UL) /*!< Enable RR[0] register */

/* Register: WDT_CONFIG */
/* Description: Configuration register */

/* Bit 3 : Configure the watchdog to either be paused, or kept running, while the CPU is halted by the debugger */
#define WDT_CONFIG_HALT_Pos (3UL) /*!< Position of HALT field. */
#define WDT_CONFIG_HALT_Msk (0x1UL << WDT_CONFIG_HALT_Pos) /*!< Bit mask of HALT field. */
#define WDT_CONFIG_HALT_Pause (0UL) /*!< Pause watchdog while the CPU is halted by the debugger */
#define WDT_CONFIG_HALT_Run (1UL) /*!< Keep the watchdog running while the CPU is halted by the debugger */

/* Bit 0 : Configure the watchdog to either be paused, or kept running, while the CPU is sleeping */
#define WDT_CONFIG_SLEEP_Pos (0UL) /*!< Position of SLEEP field. */
#define WDT_CONFIG_SLEEP_Msk (0x1UL << WDT_CONFIG_SLEEP_Pos) /*!< Bit mask of SLEEP field. */
#define WDT_CONFIG_SLEEP_Pause (0UL) /*!< Pause watchdog while the CPU is sleeping */
#define WDT_CONFIG_SLEEP_Run (1UL) /*!< Keep the watchdog running while the CPU is sleeping */

/* Register: WDT_RR */
/* Description: Description collection[0]:  Reload request 0 */

/* Bits 31..0 : Reload request register */
#define WDT_RR_RR_Pos (0UL) /*!< Position of RR field. */
#define WDT_RR_RR_Msk (0xFFFFFFFFUL << WDT_RR_RR_Pos) /*!< Bit mask of RR field. */
#define WDT_RR_RR_Reload (0x6E524635UL) /*!< Value to request a reload of the watchdog timer */


/*lint --flb "Leave library region" */
#endif
