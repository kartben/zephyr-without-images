/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 * @brief TrustZone API
 *
 * TrustZone API for Cortex-M23/M33 CPUs implementing the Security Extension.
 */

#ifndef _ARM_CORTEXM_TZ__H_
#define _ARM_CORTEXM_TZ__H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _ASMLANGUAGE

/* nothing */

#else

#include <stdint.h>

/**
 *
 * @brief Initial Non-Secure state configuration
 *
 * A convenient struct to include all required Non-Secure
 * state configuration.
 */
typedef struct tz_nonsecure_setup_conf {
	u32_t msp_ns;
	u32_t psp_ns;
	u32_t vtor_ns;
	struct {
		u32_t npriv:1;
		u32_t spsel:1;
		u32_t reserved:30;
	} control_ns;
} tz_nonsecure_setup_conf_t;


/**
 *
 * @brief Setup Non-Secure state core registers
 *
 * Configure the Non-Secure instances of the VTOR, MSP, PSP,
 * and CONTROL register.
 *
 * @param p_ns_conf Pointer to a structure holding the desired configuration.
 *
 * Notes:
 *
 * This function shall only be called from Secure state, otherwise the
 * Non-Secure instances of the core registers are RAZ/WI.
 *
 * This function shall be called before the Secure Firmware may transition
 * to Non-Secure state.
 *
 * @return N/A
 */
void tz_nonsecure_state_setup(const tz_nonsecure_setup_conf_t *p_ns_conf);

#if defined(CONFIG_ARMV8_M_MAINLINE)

/**
 *
 * @brief Setup Non-Secure Main Stack Pointer limit register
 *
 * Configure the Non-Secure instance of the MSPLIM register.
 *
 * @param val value to configure the MSPLIM_NS register with.
 *
 * Notes:
 *
 * This function shall only be called from Secure state.
 * Only ARMv8-M Mainline implementations have Non-Secure MSPLIM instance.
 *
 * @return N/A
 */
void tz_nonsecure_msplim_set(u32_t val);

/**
 *
 * @brief Setup Non-Secure Process Stack Pointer limit register
 *
 * Configure the Non-Secure instance of the PSPLIM register.
 *
 * @param val value to configure the PSPLIM_NS register with.
 *
 * Notes:
 *
 * This function shall only be called from Secure state.
 * Only ARMv8-M Mainline implementations have Non-Secure PSPLIM instance.
 *
 * @return N/A
 */
void tz_nonsecure_psplim_set(u32_t val);

#endif /* CONFIG_ARMV8_M_MAINLINE */

/**
 * @brief Prioritize Secure exceptions
 *
 * Function allows the user to prioritize Secure exceptions over Non-Secure,
 * enabling Secure exception priority boosting.
 *
 * @param secure_boost Flag indicating whether Secure priority boosting
 *                 is desired; select 1 for priority boosting, otherwise 0.
 *
 * Note:
 *
 * This function shall only be called from Secure state.
 *
 * @return N/A
 */
void tz_nonsecure_exception_prio_config(int secure_boost);

/**
 * @brief Set target state for exceptions not banked between security states
 *
 *  Function sets the security state (Secure or Non-Secure) target
 *  for ARMv8-M HardFault, NMI, and BusFault exception.
 *
 * @param secure_state 1 if target state is Secure, 0 if target state
 *                      is Non-Secure.
 *
 * Secure state: BusFault, HardFault, and NMI are Secure.
 * Non-Secure state: BusFault and NMI are Non-Secure and exceptions can
 * target Non-Secure HardFault.
 *
 * Notes:
 *
 * - This function shall only be called from Secure state.
 * - NMI and BusFault are not banked between security states; they
 * shall either target Secure or Non-Secure state based on user selection.
 * - HardFault exception generated through escalation will target the
 * security state of the original fault before its escalation to HardFault.
 * - If secure_state is set to 1 (Secure), all Non-Secure HardFaults are
 * escalated to Secure HardFaults.
 * - BusFault is present only if the Main Extension is implemented.
 *
 * @return N/A
 */
void tz_nbanked_exception_target_state_set(int secure_state);

/**
 *
 * @brief Configure SAU
 *
 * Configure (enable or disable) the ARMv8-M Security Attribution Unit.
 *
 * @param enable SAU enable flag: 1 if SAU is to be enabled, 0 if SAU is
 *               to be disabled.
 * @param allns SAU_CTRL.ALLNS flag: select 1 to set SAU_CTRL.ALLNS, 0
 *               to clear SAU_CTRL.ALLNS.
 *
 * Notes:
 *
 * SAU_CTRL.ALLNS bit: All Non-secure. When SAU_CTRL.ENABLE is 0
 *  this bit controls if the memory is marked as Non-secure or Secure.
 *  Values:
 *  Secure (not Non-Secure Callable): 0
 *  Non-Secure: 1
 *
 * This function shall only be called from Secure state, otherwise the
 * Non-Secure instance of SAU_CTRL register is RAZ/WI.
 *
 * This function shall be called before the Secure Firmware may transition
 * to Non-Secure state.
 *
 * @return N/A
 */
void tz_sau_configure(int enable, int allns);

/**
 *
 * @brief Get number of SAU regions
 *
 * Get the number of regions implemented by the Security Attribution Unit,
 * indicated by SAU_TYPE.SREGION (read-only) register field.
 *
 * Notes:
 *
 * The SREGION field reads as an IMPLEMENTATION DEFINED value.
 *
 * This function shall only be called from Secure state, otherwise the
 * Non-Secure instance of SAU_TYPE register is RAZ.
 *
 * @return The number of configured SAU regions.
 */
u32_t tz_sau_number_of_regions_get(void);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* _ARM_CORTEXM_TZ__H_ */
