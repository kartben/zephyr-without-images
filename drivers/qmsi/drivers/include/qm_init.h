/*
 * Copyright (c) 2015, Intel Corporation
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the Intel Corporation nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE INTEL CORPORATION OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __QM_INIT_H__
#define __QM_INIT_H__

#include "qm_common.h"
#include "qm_soc_regs.h"

/**
 * Initialisation and reset for Quark Microcontrollers.
 *
 * @defgroup groupInit Initialisation
 * @{
 */

/**
 * Reset Mode type.
 */
typedef enum {
	QM_WARM_RESET = BIT(1),
	QM_COLD_RESET = BIT(3),
} qm_soc_reset_t;

/**
 * Reset the SoC. This can either be a cold reset or a warm reset.
 *
 * @param [in] reset_type Selects the type of reset to perform.
 */
void qm_soc_reset(qm_soc_reset_t reset_type);

/**
 * @}
 */

#endif /* __QM_INIT_H__ */
