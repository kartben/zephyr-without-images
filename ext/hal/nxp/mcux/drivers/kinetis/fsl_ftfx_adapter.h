/*
* Copyright 2017-2018 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
*
*/

#ifndef _FSL_FTFX_ADAPTER_H_
#define _FSL_FTFX_ADAPTER_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define INVALID_REG_MASK (0)
#define INVALID_REG_SHIFT (0)
#define INVALID_REG_ADDRESS (0x00U)
#define INVALID_REG_VALUE (0x00U)

/* @brief Flash register access type defines */
#define FTFx_REG8_ACCESS_TYPE volatile uint8_t *
#define FTFx_REG32_ACCESS_TYPE volatile uint32_t *

/*!
 * @name Common flash register info defines
 * @{
 */
#if defined(FTFA)
#define FTFx FTFA
#define FTFx_BASE FTFA_BASE
#define FTFx_FSTAT_CCIF_MASK FTFA_FSTAT_CCIF_MASK
#define FTFx_FSTAT_RDCOLERR_MASK FTFA_FSTAT_RDCOLERR_MASK
#define FTFx_FSTAT_ACCERR_MASK FTFA_FSTAT_ACCERR_MASK
#define FTFx_FSTAT_FPVIOL_MASK FTFA_FSTAT_FPVIOL_MASK
#define FTFx_FSTAT_MGSTAT0_MASK FTFA_FSTAT_MGSTAT0_MASK
#define FTFx_FSEC_SEC_MASK FTFA_FSEC_SEC_MASK
#define FTFx_FSEC_KEYEN_MASK FTFA_FSEC_KEYEN_MASK
#if defined(FSL_FEATURE_FLASH_HAS_FLEX_RAM) && FSL_FEATURE_FLASH_HAS_FLEX_RAM
#define FTFx_FCNFG_RAMRDY_MASK FTFA_FCNFG_RAMRDY_MASK
#endif /* FSL_FEATURE_FLASH_HAS_FLEX_RAM */
#if defined(FSL_FEATURE_FLASH_HAS_FLEX_NVM) && FSL_FEATURE_FLASH_HAS_FLEX_NVM
#define FTFx_FCNFG_EEERDY_MASK FTFA_FCNFG_EEERDY_MASK
#endif /* FSL_FEATURE_FLASH_HAS_FLEX_NVM */
#elif defined(FTFE)
#define FTFx FTFE
#define FTFx_BASE FTFE_BASE
#define FTFx_FSTAT_CCIF_MASK FTFE_FSTAT_CCIF_MASK
#define FTFx_FSTAT_RDCOLERR_MASK FTFE_FSTAT_RDCOLERR_MASK
#define FTFx_FSTAT_ACCERR_MASK FTFE_FSTAT_ACCERR_MASK
#define FTFx_FSTAT_FPVIOL_MASK FTFE_FSTAT_FPVIOL_MASK
#define FTFx_FSTAT_MGSTAT0_MASK FTFE_FSTAT_MGSTAT0_MASK
#define FTFx_FSEC_SEC_MASK FTFE_FSEC_SEC_MASK
#define FTFx_FSEC_KEYEN_MASK FTFE_FSEC_KEYEN_MASK
#if defined(FSL_FEATURE_FLASH_HAS_FLEX_RAM) && FSL_FEATURE_FLASH_HAS_FLEX_RAM
#define FTFx_FCNFG_RAMRDY_MASK FTFE_FCNFG_RAMRDY_MASK
#endif /* FSL_FEATURE_FLASH_HAS_FLEX_RAM */
#if defined(FSL_FEATURE_FLASH_HAS_FLEX_NVM) && FSL_FEATURE_FLASH_HAS_FLEX_NVM
#define FTFx_FCNFG_EEERDY_MASK FTFE_FCNFG_EEERDY_MASK
#endif /* FSL_FEATURE_FLASH_HAS_FLEX_NVM */
#elif defined(FTFL)
#define FTFx FTFL
#define FTFx_BASE FTFL_BASE
#define FTFx_FSTAT_CCIF_MASK FTFL_FSTAT_CCIF_MASK
#define FTFx_FSTAT_RDCOLERR_MASK FTFL_FSTAT_RDCOLERR_MASK
#define FTFx_FSTAT_ACCERR_MASK FTFL_FSTAT_ACCERR_MASK
#define FTFx_FSTAT_FPVIOL_MASK FTFL_FSTAT_FPVIOL_MASK
#define FTFx_FSTAT_MGSTAT0_MASK FTFL_FSTAT_MGSTAT0_MASK
#define FTFx_FSEC_SEC_MASK FTFL_FSEC_SEC_MASK
#define FTFx_FSEC_KEYEN_MASK FTFL_FSEC_KEYEN_MASK
#if defined(FSL_FEATURE_FLASH_HAS_FLEX_RAM) && FSL_FEATURE_FLASH_HAS_FLEX_RAM
#define FTFx_FCNFG_RAMRDY_MASK FTFL_FCNFG_RAMRDY_MASK
#endif /* FSL_FEATURE_FLASH_HAS_FLEX_RAM */
#if defined(FSL_FEATURE_FLASH_HAS_FLEX_NVM) && FSL_FEATURE_FLASH_HAS_FLEX_NVM
#define FTFx_FCNFG_EEERDY_MASK FTFL_FCNFG_EEERDY_MASK
#endif /* FSL_FEATURE_FLASH_HAS_FLEX_NVM */
#else
#error "Unknown flash controller"
#endif
/*@}*/

/*!
 * @name Common flash register access info defines
 * @{
 */
#define FTFx_FCCOB3_REG (FTFx->FCCOB3)
#define FTFx_FCCOB5_REG (FTFx->FCCOB5)
#define FTFx_FCCOB6_REG (FTFx->FCCOB6)
#define FTFx_FCCOB7_REG (FTFx->FCCOB7)

#if defined(FTFA_FPROTSL_PROTS_MASK) || defined(FTFE_FPROTSL_PROTS_MASK) || defined(FTFL_FPROTSL_PROTS_MASK)
#define FTFx_FLASH1_HAS_INT_PROT_REG (1)
#define FTFx_FPROTSH_REG (FTFx->FPROTSH)
#define FTFx_FPROTSL_REG (FTFx->FPROTSL)
#else
#define FTFx_FLASH1_HAS_INT_PROT_REG (0)
#define FTFx_FPROTSH_REG (*(uint8_t *)INVALID_REG_ADDRESS)
#define FTFx_FPROTSL_REG (*(uint8_t *)INVALID_REG_ADDRESS)
#endif

#if defined(FTFA_FPROTH0_PROT_MASK) || defined(FTFE_FPROTH0_PROT_MASK) || defined(FTFL_FPROTH0_PROT_MASK)
#define FTFx_FPROT_HIGH_REG (FTFx->FPROTH3)
#define FTFx_FPROTH3_REG (FTFx->FPROTH3)
#define FTFx_FPROTH2_REG (FTFx->FPROTH2)
#define FTFx_FPROTH1_REG (FTFx->FPROTH1)
#define FTFx_FPROTH0_REG (FTFx->FPROTH0)
#else
#define FTFx_FPROT_HIGH_REG (*(uint8_t *)INVALID_REG_ADDRESS)
#define FTFx_FPROTH3_REG (*(uint8_t *)INVALID_REG_ADDRESS)
#define FTFx_FPROTH2_REG (*(uint8_t *)INVALID_REG_ADDRESS)
#define FTFx_FPROTH1_REG (*(uint8_t *)INVALID_REG_ADDRESS)
#define FTFx_FPROTH0_REG (*(uint8_t *)INVALID_REG_ADDRESS)
#endif

#if defined(FTFA_FPROTL0_PROT_MASK) || defined(FTFE_FPROTL0_PROT_MASK) || defined(FTFL_FPROTL0_PROT_MASK)
#define FTFx_FPROT_LOW_REG (FTFx->FPROTL3)
#define FTFx_FPROTL3_REG (FTFx->FPROTL3)
#define FTFx_FPROTL2_REG (FTFx->FPROTL2)
#define FTFx_FPROTL1_REG (FTFx->FPROTL1)
#define FTFx_FPROTL0_REG (FTFx->FPROTL0)
#elif defined(FTFA_FPROT0_PROT_MASK) || defined(FTFE_FPROT0_PROT_MASK) || defined(FTFL_FPROT0_PROT_MASK)
#define FTFx_FPROT_LOW_REG (FTFx->FPROT3)
#define FTFx_FPROTL3_REG (FTFx->FPROT3)
#define FTFx_FPROTL2_REG (FTFx->FPROT2)
#define FTFx_FPROTL1_REG (FTFx->FPROT1)
#define FTFx_FPROTL0_REG (FTFx->FPROT0)
#else
#define FTFx_FPROT_LOW_REG (*(uint8_t *)INVALID_REG_ADDRESS)
#define FTFx_FPROTL3_REG (*(uint8_t *)INVALID_REG_ADDRESS)
#define FTFx_FPROTL2_REG (*(uint8_t *)INVALID_REG_ADDRESS)
#define FTFx_FPROTL1_REG (*(uint8_t *)INVALID_REG_ADDRESS)
#define FTFx_FPROTL0_REG (*(uint8_t *)INVALID_REG_ADDRESS)
#endif

#if defined(FTFA_FACSSS_SGSIZE_S_MASK) || defined(FTFE_FACSSS_SGSIZE_S_MASK) || defined(FTFL_FACSSS_SGSIZE_S_MASK)
#define FTFx_FLASH1_HAS_INT_XACC_REG (1)
#define FTFx_XACCSH_REG (FTFx->XACCSH)
#define FTFx_XACCSL_REG (FTFx->XACCSL)
#define FTFx_FACSSS_REG (FTFx->FACSSS)
#define FTFx_FACSNS_REG (FTFx->FACSNS)
#else
#define FTFx_FLASH1_HAS_INT_XACC_REG (0)
#define FTFx_XACCSH_REG (*(uint8_t *)INVALID_REG_ADDRESS)
#define FTFx_XACCSL_REG (*(uint8_t *)INVALID_REG_ADDRESS)
#define FTFx_FACSSS_REG (*(uint8_t *)INVALID_REG_ADDRESS)
#define FTFx_FACSNS_REG (*(uint8_t *)INVALID_REG_ADDRESS)
#endif

#if (defined(FTFA_FACSS_SGSIZE_MASK) || defined(FTFE_FACSS_SGSIZE_MASK) || defined(FTFL_FACSS_SGSIZE_MASK) || \
     defined(FTFA_FACSS_SGSIZE_S_MASK) || defined(FTFE_FACSS_SGSIZE_S_MASK) || defined(FTFL_FACSS_SGSIZE_S_MASK))
//#define FTFx_FLASH0_HAS_INT_XACC_REG (FTFx_FLASH1_HAS_INT_XACC_REG)
#define FTFx_XACCH3_REG (FTFx->XACCH3)
#define FTFx_XACCL3_REG (FTFx->XACCL3)
#define FTFx_FACSS_REG (FTFx->FACSS)
#define FTFx_FACSN_REG (FTFx->FACSN)
#else
#define FTFx_FLASH0_HAS_INT_XACC_REG (0)
#define FTFx_XACCH3_REG (*(uint8_t *)INVALID_REG_ADDRESS)
#define FTFx_XACCL3_REG (*(uint8_t *)INVALID_REG_ADDRESS)
#define FTFx_FACSS_REG (*(uint8_t *)INVALID_REG_ADDRESS)
#define FTFx_FACSN_REG (*(uint8_t *)INVALID_REG_ADDRESS)
#endif
/*@}*/

/*!
 * @brief MCM cache register access info defines.
 */
#if defined(MCM_PLACR_CFCC_MASK)
#define MCM_CACHE_CLEAR_MASK MCM_PLACR_CFCC_MASK
#define MCM_CACHE_CLEAR_SHIFT MCM_PLACR_CFCC_SHIFT
#if defined(MCM0)
#define MCM0_CACHE_REG MCM0->PLACR
#elif defined(MCM) && (!defined(MCM1))
#define MCM0_CACHE_REG MCM->PLACR
#endif
#if defined(MCM1)
#define MCM1_CACHE_REG MCM1->PLACR
#elif defined(MCM) && (!defined(MCM0))
#define MCM1_CACHE_REG MCM->PLACR
#endif
#else
#define MCM_CACHE_CLEAR_MASK INVALID_REG_MASK
#define MCM_CACHE_CLEAR_SHIFT INVALID_REG_SHIFT
#define MCM0_CACHE_REG (*(uint32_t *)INVALID_REG_ADDRESS)
#define MCM1_CACHE_REG (*(uint32_t *)INVALID_REG_ADDRESS)
#endif

/*!
 * @brief FMC cache register access info defines.
 */
#if defined(FMC_PFB01CR_S_INV_MASK)
#define FMC_SPECULATION_INVALIDATE_MASK FMC_PFB01CR_S_INV_MASK
#define FMC_SPECULATION_INVALIDATE_SHIFT FMC_PFB01CR_S_INV_SHIFT
#define FMC_SPECULATION_INVALIDATE_REG FMC->PFB01CR
#elif defined(FMC_PFB01CR_S_B_INV_MASK)
#define FMC_SPECULATION_INVALIDATE_MASK FMC_PFB01CR_S_B_INV_MASK
#define FMC_SPECULATION_INVALIDATE_SHIFT FMC_PFB01CR_S_B_INV_SHIFT
#define FMC_SPECULATION_INVALIDATE_REG FMC->PFB01CR
#elif defined(FMC_PFB0CR_S_INV_MASK)
#define FMC_SPECULATION_INVALIDATE_MASK FMC_PFB0CR_S_INV_MASK
#define FMC_SPECULATION_INVALIDATE_SHIFT FMC_PFB0CR_S_INV_SHIFT
#define FMC_SPECULATION_INVALIDATE_REG FMC->PFB0CR
#elif defined(FMC_PFB0CR_S_B_INV_MASK)
#define FMC_SPECULATION_INVALIDATE_MASK FMC_PFB0CR_S_B_INV_MASK
#define FMC_SPECULATION_INVALIDATE_SHIFT FMC_PFB0CR_S_B_INV_SHIFT
#define FMC_SPECULATION_INVALIDATE_REG FMC->PFB0CR
#else
#define FMC_SPECULATION_INVALIDATE_MASK INVALID_REG_MASK
#define FMC_SPECULATION_INVALIDATE_SHIFT INVALID_REG_SHIFT
#define FMC_SPECULATION_INVALIDATE(x) (((uint32_t)(((uint32_t)(x)) << INVALID_REG_SHIFT)) & INVALID_REG_MASK)
#define FMC_SPECULATION_INVALIDATE_REG (*(uint32_t *)INVALID_REG_ADDRESS)
#endif

#if defined(FMC_PFB01CR_CINV_WAY_MASK)
#define FMC_CACHE_CLEAR_MASK FMC_PFB01CR_CINV_WAY_MASK
#define FMC_CACHE_CLEAR_SHIFT FMC_PFB01CR_CINV_WAY_SHIFT
#define FMC_CACHE_CLEAR(x) FMC_PFB01CR_CINV_WAY(x)
#elif defined(FMC_PFB0CR_CINV_WAY_MASK)
#define FMC_CACHE_CLEAR_MASK FMC_PFB0CR_CINV_WAY_MASK
#define FMC_CACHE_CLEAR_SHIFT FMC_PFB0CR_CINV_WAY_SHIFT
#define FMC_CACHE_CLEAR(x) FMC_PFB0CR_CINV_WAY(x)
#else
#define FMC_CACHE_CLEAR_MASK INVALID_REG_MASK
#define FMC_CACHE_CLEAR_SHIFT INVALID_REG_SHIFT
#define FMC_CACHE_CLEAR(x) (((uint32_t)(((uint32_t)(x)) << INVALID_REG_SHIFT)) & INVALID_REG_MASK)
#endif

#if defined(FMC_PFB01CR_B0DPE_MASK)
#define FMC_CACHE_B0DPE_MASK FMC_PFB01CR_B0DPE_MASK
#define FMC_CACHE_B0IPE_MASK FMC_PFB01CR_B0IPE_MASK
#define FMC_CACHE_REG FMC->PFB01CR
#elif defined(FMC_PFB0CR_B0DPE_MASK)
#define FMC_CACHE_B0DPE_MASK FMC_PFB0CR_B0DPE_MASK
#define FMC_CACHE_B0IPE_MASK FMC_PFB0CR_B0IPE_MASK
#define FMC_CACHE_REG FMC->PFB0CR
#else
#define FMC_CACHE_B0DPE_MASK INVALID_REG_MASK
#define FMC_CACHE_B0IPE_MASK INVALID_REG_MASK
#define FMC_CACHE_REG (*(uint32_t *)INVALID_REG_ADDRESS)
#endif

/*!
 * @brief MSCM cache register access info defines.
 */
#if defined(MSCM_OCMDR_OCM1_MASK)
#define MSCM_SPECULATION_SET_MASK MSCM_OCMDR_OCM1_MASK
#define MSCM_SPECULATION_SET_SHIFT MSCM_OCMDR_OCM1_SHIFT
#define MSCM_SPECULATION_SET(x) MSCM_OCMDR_OCM1(x)
#elif defined(MSCM_OCMDR0_OCM1_MASK) || defined(MSCM_OCMDR1_OCM1_MASK)
#define MSCM_SPECULATION_SET_MASK MSCM_OCMDR0_OCM1_MASK
#define MSCM_SPECULATION_SET_SHIFT MSCM_OCMDR0_OCM1_SHIFT
#define MSCM_SPECULATION_SET(x) MSCM_OCMDR0_OCM1(x)
#elif defined(MSCM_OCMDR_OCMC1_MASK)
#define MSCM_SPECULATION_SET_MASK MSCM_OCMDR_OCMC1_MASK
#define MSCM_SPECULATION_SET_SHIFT MSCM_OCMDR_OCMC1_SHIFT
#define MSCM_SPECULATION_SET(x) MSCM_OCMDR_OCMC1(x)
#else
#define MSCM_SPECULATION_SET_MASK INVALID_REG_MASK
#define MSCM_SPECULATION_SET_SHIFT INVALID_REG_SHIFT
#define MSCM_SPECULATION_SET(x) (((uint32_t)(((uint32_t)(x)) << INVALID_REG_SHIFT)) & INVALID_REG_MASK)
#endif

#if defined(MSCM_OCMDR_OCM2_MASK)
#define MSCM_CACHE_CLEAR_MASK MSCM_OCMDR_OCM2_MASK
#define MSCM_CACHE_CLEAR_SHIFT MSCM_OCMDR_OCM2_SHIFT
#define MSCM_CACHE_CLEAR(x) MSCM_OCMDR_OCM2(x)
#else
#define MSCM_CACHE_CLEAR_MASK INVALID_REG_MASK
#define MSCM_CACHE_CLEAR_SHIFT INVALID_REG_SHIFT
#define MSCM_CACHE_CLEAR(x) (((uint32_t)(((uint32_t)(x)) << INVALID_REG_SHIFT)) & INVALID_REG_MASK)
#endif

#if defined(MSCM_OCMDR_OCM1_MASK) || defined(MSCM_OCMDR_OCMC1_MASK)
#define MSCM_OCMDR0_REG MSCM->OCMDR[0]
#define MSCM_OCMDR1_REG MSCM->OCMDR[1]
#elif defined(MSCM_OCMDR0_OCM1_MASK) || defined(MSCM_OCMDR1_OCM1_MASK)
#define MSCM_OCMDR0_REG MSCM->OCMDR0
#define MSCM_OCMDR1_REG MSCM->OCMDR1
#else
#define MSCM_OCMDR0_REG (*(uint32_t *)INVALID_REG_ADDRESS)
#define MSCM_OCMDR1_REG (*(uint32_t *)INVALID_REG_ADDRESS)
#endif

/*!
 * @brief MSCM prefetch speculation defines.
 */
#define MSCM_OCMDR_OCMC1_DFDS_MASK (0x10U)
#define MSCM_OCMDR_OCMC1_DFCS_MASK (0x20U)
#define MSCM_OCMDR_OCMC1_DFDS_SHIFT (4U)
#define MSCM_OCMDR_OCMC1_DFCS_SHIFT (5U)

/*!
 * @brief SIM PFSIZE register access info defines.
 */
#if defined(SIM_FCFG1_CORE0_PFSIZE_MASK)
#define SIM_FLASH0_PFSIZE_MASK SIM_FCFG1_CORE0_PFSIZE_MASK
#define SIM_FLASH0_PFSIZE_SHIFT SIM_FCFG1_CORE0_PFSIZE_SHIFT
#define SIM_FCFG1_REG SIM->FCFG1
#elif defined(SIM_FCFG1_PFSIZE_MASK)
#define SIM_FLASH0_PFSIZE_MASK SIM_FCFG1_PFSIZE_MASK
#define SIM_FLASH0_PFSIZE_SHIFT SIM_FCFG1_PFSIZE_SHIFT
#define SIM_FCFG1_REG SIM->FCFG1
#else
#define SIM_FLASH0_PFSIZE_MASK INVALID_REG_MASK
#define SIM_FLASH0_PFSIZE_SHIFT INVALID_REG_SHIFT
#define SIM_FCFG1_REG INVALID_REG_VALUE
#endif

#if defined(SIM_FCFG1_CORE1_PFSIZE_MASK)
#define SIM_FLASH1_PFSIZE_MASK SIM_FCFG1_CORE1_PFSIZE_MASK
#define SIM_FLASH1_PFSIZE_SHIFT SIM_FCFG1_CORE1_PFSIZE_SHIFT
#else
#define SIM_FLASH1_PFSIZE_MASK INVALID_REG_MASK
#define SIM_FLASH1_PFSIZE_SHIFT INVALID_REG_SHIFT
#endif

/*!
 * @name Dual core/flash configuration
 * @{
 */
/*! @brief Redefines some flash features. */
#if defined(FSL_FEATURE_FLASH_CURRENT_CORE_ID)
#if (FSL_FEATURE_FLASH_CURRENT_CORE_ID == 0u)
#define FLASH0_FEATURE_PFLASH_START_ADDRESS FSL_FEATURE_FLASH_PFLASH_START_ADDRESS
#define FLASH0_FEATURE_PFLASH_BLOCK_COUNT FSL_FEATURE_FLASH_PFLASH_BLOCK_COUNT
#define FLASH0_FEATURE_PFLASH_BLOCK_SIZE FSL_FEATURE_FLASH_PFLASH_BLOCK_SIZE
#define FLASH0_FEATURE_PFLASH_BLOCK_SECTOR_SIZE FSL_FEATURE_FLASH_PFLASH_BLOCK_SECTOR_SIZE
#define FLASH0_FEATURE_PFLASH_BLOCK_WRITE_UNIT_SIZE FSL_FEATURE_FLASH_PFLASH_BLOCK_WRITE_UNIT_SIZE
#define FLASH0_FEATURE_PFLASH_SECTOR_CMD_ADDRESS_ALIGMENT FSL_FEATURE_FLASH_PFLASH_SECTOR_CMD_ADDRESS_ALIGMENT
#define FLASH0_FEATURE_PFLASH_SECTION_CMD_ADDRESS_ALIGMENT FSL_FEATURE_FLASH_PFLASH_SECTION_CMD_ADDRESS_ALIGMENT
#define FLASH0_FEATURE_PFLASH_PROTECTION_REGION_COUNT FSL_FEATURE_FLASH_PFLASH_PROTECTION_REGION_COUNT
#define FLASH1_FEATURE_PFLASH_START_ADDRESS FSL_FEATURE_FLASH_PFLASH_1_START_ADDRESS
#define FLASH1_FEATURE_PFLASH_BLOCK_COUNT FSL_FEATURE_FLASH_PFLASH_1_BLOCK_COUNT
#define FLASH1_FEATURE_PFLASH_BLOCK_SIZE FSL_FEATURE_FLASH_PFLASH_1_BLOCK_SIZE
#define FLASH1_FEATURE_PFLASH_BLOCK_SECTOR_SIZE FSL_FEATURE_FLASH_PFLASH_1_BLOCK_SECTOR_SIZE
#define FLASH1_FEATURE_PFLASH_BLOCK_WRITE_UNIT_SIZE FSL_FEATURE_FLASH_PFLASH_1_BLOCK_WRITE_UNIT_SIZE
#if defined(FSL_FEATURE_FLASH_PFLASH_1_SECTOR_CMD_ADDRESS_ALIGMENT) && defined(FSL_FEATURE_FLASH_PFLASH_1_SECTION_CMD_ADDRESS_ALIGMENT)
#define FLASH1_FEATURE_PFLASH_SECTOR_CMD_ADDRESS_ALIGMENT FSL_FEATURE_FLASH_PFLASH_1_SECTOR_CMD_ADDRESS_ALIGMENT
#define FLASH1_FEATURE_PFLASH_SECTION_CMD_ADDRESS_ALIGMENT FSL_FEATURE_FLASH_PFLASH_1_SECTION_CMD_ADDRESS_ALIGMENT
#else
#define FLASH1_FEATURE_PFLASH_SECTOR_CMD_ADDRESS_ALIGMENT FSL_FEATURE_FLASH_PFLASH_SECTOR_CMD_ADDRESS_ALIGMENT
#define FLASH1_FEATURE_PFLASH_SECTION_CMD_ADDRESS_ALIGMENT FSL_FEATURE_FLASH_PFLASH_SECTION_CMD_ADDRESS_ALIGMENT
#endif
#define FLASH1_FEATURE_PFLASH_PROTECTION_REGION_COUNT FSL_FEATURE_FLASH_PFLASH_1_PROTECTION_REGION_COUNT
#elif (FSL_FEATURE_FLASH_CURRENT_CORE_ID == 1u)
#define FLASH0_FEATURE_PFLASH_START_ADDRESS FSL_FEATURE_FLASH_PFLASH_1_START_ADDRESS
#define FLASH0_FEATURE_PFLASH_BLOCK_COUNT FSL_FEATURE_FLASH_PFLASH_1_BLOCK_COUNT
#define FLASH0_FEATURE_PFLASH_BLOCK_SIZE FSL_FEATURE_FLASH_PFLASH_1_BLOCK_SIZE
#define FLASH0_FEATURE_PFLASH_BLOCK_SECTOR_SIZE FSL_FEATURE_FLASH_PFLASH_1_BLOCK_SECTOR_SIZE
#define FLASH0_FEATURE_PFLASH_BLOCK_WRITE_UNIT_SIZE FSL_FEATURE_FLASH_PFLASH_1_BLOCK_WRITE_UNIT_SIZE
#if defined(FSL_FEATURE_FLASH_PFLASH_1_SECTOR_CMD_ADDRESS_ALIGMENT) && defined(FSL_FEATURE_FLASH_PFLASH_1_SECTION_CMD_ADDRESS_ALIGMENT)
#define FLASH0_FEATURE_PFLASH_SECTOR_CMD_ADDRESS_ALIGMENT FSL_FEATURE_FLASH_PFLASH_1_SECTOR_CMD_ADDRESS_ALIGMENT
#define FLASH0_FEATURE_PFLASH_SECTION_CMD_ADDRESS_ALIGMENT FSL_FEATURE_FLASH_PFLASH_1_SECTION_CMD_ADDRESS_ALIGMENT
#else
#define FLASH0_FEATURE_PFLASH_SECTOR_CMD_ADDRESS_ALIGMENT FSL_FEATURE_FLASH_PFLASH_SECTOR_CMD_ADDRESS_ALIGMENT
#define FLASH0_FEATURE_PFLASH_SECTION_CMD_ADDRESS_ALIGMENT FSL_FEATURE_FLASH_PFLASH_SECTION_CMD_ADDRESS_ALIGMENT
#endif
#define FLASH0_FEATURE_PFLASH_PROTECTION_REGION_COUNT FSL_FEATURE_FLASH_PFLASH_1_PROTECTION_REGION_COUNT
#define FLASH1_FEATURE_PFLASH_START_ADDRESS FSL_FEATURE_FLASH_PFLASH_START_ADDRESS
#define FLASH1_FEATURE_PFLASH_BLOCK_COUNT FSL_FEATURE_FLASH_PFLASH_BLOCK_COUNT
#define FLASH1_FEATURE_PFLASH_BLOCK_SIZE FSL_FEATURE_FLASH_PFLASH_BLOCK_SIZE
#define FLASH1_FEATURE_PFLASH_BLOCK_SECTOR_SIZE FSL_FEATURE_FLASH_PFLASH_BLOCK_SECTOR_SIZE
#define FLASH1_FEATURE_PFLASH_BLOCK_WRITE_UNIT_SIZE FSL_FEATURE_FLASH_PFLASH_BLOCK_WRITE_UNIT_SIZE
#define FLASH1_FEATURE_PFLASH_SECTOR_CMD_ADDRESS_ALIGMENT FSL_FEATURE_FLASH_PFLASH_SECTOR_CMD_ADDRESS_ALIGMENT
#define FLASH1_FEATURE_PFLASH_SECTION_CMD_ADDRESS_ALIGMENT FSL_FEATURE_FLASH_PFLASH_SECTION_CMD_ADDRESS_ALIGMENT
#define FLASH1_FEATURE_PFLASH_PROTECTION_REGION_COUNT FSL_FEATURE_FLASH_PFLASH_PROTECTION_REGION_COUNT
#endif
#else
#define FLASH0_FEATURE_PFLASH_START_ADDRESS FSL_FEATURE_FLASH_PFLASH_START_ADDRESS
#define FLASH0_FEATURE_PFLASH_BLOCK_COUNT FSL_FEATURE_FLASH_PFLASH_BLOCK_COUNT
#define FLASH0_FEATURE_PFLASH_BLOCK_SIZE FSL_FEATURE_FLASH_PFLASH_BLOCK_SIZE
#define FLASH0_FEATURE_PFLASH_BLOCK_SECTOR_SIZE FSL_FEATURE_FLASH_PFLASH_BLOCK_SECTOR_SIZE
#define FLASH0_FEATURE_PFLASH_BLOCK_WRITE_UNIT_SIZE FSL_FEATURE_FLASH_PFLASH_BLOCK_WRITE_UNIT_SIZE
#define FLASH0_FEATURE_PFLASH_SECTOR_CMD_ADDRESS_ALIGMENT FSL_FEATURE_FLASH_PFLASH_SECTOR_CMD_ADDRESS_ALIGMENT
#define FLASH0_FEATURE_PFLASH_SECTION_CMD_ADDRESS_ALIGMENT FSL_FEATURE_FLASH_PFLASH_SECTION_CMD_ADDRESS_ALIGMENT
#define FLASH0_FEATURE_PFLASH_PROTECTION_REGION_COUNT FSL_FEATURE_FLASH_PFLASH_PROTECTION_REGION_COUNT
#define FLASH1_FEATURE_PFLASH_START_ADDRESS 0
#define FLASH1_FEATURE_PFLASH_BLOCK_COUNT 0
#define FLASH1_FEATURE_PFLASH_BLOCK_SIZE 0
#define FLASH1_FEATURE_PFLASH_BLOCK_SECTOR_SIZE 0
#define FLASH1_FEATURE_PFLASH_BLOCK_WRITE_UNIT_SIZE 0
#define FLASH1_FEATURE_PFLASH_SECTOR_CMD_ADDRESS_ALIGMENT 0
#define FLASH1_FEATURE_PFLASH_SECTION_CMD_ADDRESS_ALIGMENT 0
#define FLASH1_FEATURE_PFLASH_PROTECTION_REGION_COUNT 0
#endif

#if FLASH0_FEATURE_PFLASH_PROTECTION_REGION_COUNT > FLASH1_FEATURE_PFLASH_PROTECTION_REGION_COUNT
#define MAX_FLASH_PROT_REGION_COUNT FLASH0_FEATURE_PFLASH_PROTECTION_REGION_COUNT
#else
#define MAX_FLASH_PROT_REGION_COUNT FLASH1_FEATURE_PFLASH_PROTECTION_REGION_COUNT
#endif

/*@}*/


#endif /* _FSL_FTFX_ADAPTER_H_ */

