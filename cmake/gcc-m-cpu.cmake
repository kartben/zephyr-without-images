# SPDX-License-Identifier: Apache-2.0

# Determines what argument to give to -mcpu= based on the
# KConfig'uration and sets this to GCC_M_CPU

if("${ARCH}" STREQUAL "arm")
  if    (CONFIG_CPU_CORTEX_M0)
    set(GCC_M_CPU cortex-m0)
  elseif(CONFIG_CPU_CORTEX_M0PLUS)
    set(GCC_M_CPU cortex-m0plus)
  elseif(CONFIG_CPU_CORTEX_M3)
    set(GCC_M_CPU cortex-m3)
  elseif(CONFIG_CPU_CORTEX_M4)
    set(GCC_M_CPU cortex-m4)
  elseif(CONFIG_CPU_CORTEX_M7)
    set(GCC_M_CPU cortex-m7)
  elseif(CONFIG_CPU_CORTEX_M23)
    set(GCC_M_CPU cortex-m23)
  elseif(CONFIG_CPU_CORTEX_M33)
    if    (CONFIG_ARMV8_M_DSP)
      set(GCC_M_CPU cortex-m33)
    else()
      set(GCC_M_CPU cortex-m33+nodsp)
    endif()
  else()
    message(FATAL_ERROR "Expected CONFIG_CPU_CORTEX_x to be defined")
  endif()
elseif("${ARCH}" STREQUAL "arc")
  if(CONFIG_SOC_QUARK_SE_C1000_SS)
    set(GCC_M_CPU quarkse_em)
  elseif(CONFIG_CPU_EM4_FPUS)
    set(GCC_M_CPU em4_fpus)
  elseif(CONFIG_CPU_EM4_DMIPS)
    set(GCC_M_CPU em4_dmips)
  elseif(CONFIG_CPU_EM4_FPUDA)
    set(GCC_M_CPU em4_fpuda)
  endif()
endif()
