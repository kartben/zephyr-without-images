# SPDX-License-Identifier: Apache-2.0

# Determines what argument to give to -mcpu= based on the
# KConfig'uration and sets this to GCC_M_CPU

if("${ARCH}" STREQUAL "arm")
  if    (CONFIG_CPU_CORTEX_M0)
    set(GCC_M_CPU cortex-m0)
  elseif(CONFIG_CPU_CORTEX_M0PLUS)
    set(GCC_M_CPU cortex-m0plus)
  elseif(CONFIG_CPU_CORTEX_M1)
    set(GCC_M_CPU cortex-m1)
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
  elseif(CONFIG_CPU_CORTEX_M55)
    if    (CONFIG_ARMV8_1_M_MVEF)
      set(GCC_M_CPU cortex-m55)
    elseif(CONFIG_ARMV8_1_M_MVEI)
      set(GCC_M_CPU cortex-m55+nomve.fp)
    elseif(CONFIG_ARMV8_M_DSP)
      set(GCC_M_CPU cortex-m55+nomve)
    else()
      set(GCC_M_CPU cortex-m55+nodsp)
    endif()
  elseif(CONFIG_CPU_CORTEX_R4)
    set(GCC_M_CPU cortex-r4)
  elseif(CONFIG_CPU_CORTEX_R5)
    set(GCC_M_CPU cortex-r5)
  elseif(CONFIG_CPU_CORTEX_R7)
    set(GCC_M_CPU cortex-r7)
  elseif(CONFIG_CPU_CORTEX_R52)
    set(GCC_M_CPU cortex-r52)
  elseif(CONFIG_CPU_CORTEX_A9)
    set(GCC_M_CPU cortex-a9)
  else()
    message(FATAL_ERROR "Expected CONFIG_CPU_CORTEX_x to be defined")
  endif()
elseif("${ARCH}" STREQUAL "arm64")
  if(CONFIG_CPU_CORTEX_A53)
    set(GCC_M_CPU cortex-a53)
  elseif(CONFIG_CPU_CORTEX_A72)
    set(GCC_M_CPU cortex-a72)
  elseif(CONFIG_CPU_CORTEX_R82)
    set(GCC_M_ARCH armv8.4-a+nolse)
  endif()
elseif("${ARCH}" STREQUAL "arc")
  if(CONFIG_CPU_EM4_FPUS)
    set(GCC_M_CPU em4_fpus)
  elseif(CONFIG_CPU_EM4_DMIPS)
    set(GCC_M_CPU em4_dmips)
  elseif(CONFIG_CPU_EM4_FPUDA)
    set(GCC_M_CPU em4_fpuda)
  elseif(CONFIG_CPU_HS3X)
    set(GCC_M_CPU archs)
  elseif(CONFIG_CPU_HS6X)
    set(GCC_M_CPU hs6x)
  elseif(CONFIG_CPU_EM4)
    set(GCC_M_CPU arcem)
  elseif(CONFIG_CPU_EM6)
    set(GCC_M_CPU arcem)
  endif()
endif()
