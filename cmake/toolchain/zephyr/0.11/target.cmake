# SPDX-License-Identifier: Apache-2.0

set(CROSS_COMPILE_TARGET_arm        arm-zephyr-eabi)
set(CROSS_COMPILE_TARGET_arm64   aarch64-zephyr-elf)
set(CROSS_COMPILE_TARGET_nios2     nios2-zephyr-elf)
set(CROSS_COMPILE_TARGET_riscv   riscv64-zephyr-elf)
set(CROSS_COMPILE_TARGET_mips     mipsel-zephyr-elf)
set(CROSS_COMPILE_TARGET_xtensa   xtensa-zephyr-elf)
set(CROSS_COMPILE_TARGET_arc         arc-zephyr-elf)
set(CROSS_COMPILE_TARGET_x86      x86_64-zephyr-elf)
set(CROSS_COMPILE_TARGET_sparc     sparc-zephyr-elf)

set(CROSS_COMPILE_TARGET ${CROSS_COMPILE_TARGET_${ARCH}})
set(SYSROOT_TARGET       ${CROSS_COMPILE_TARGET})

if("${ARCH}" STREQUAL "xtensa")
  # Xtensa GCC needs a different toolchain per SOC
  if("${SOC_SERIES}" STREQUAL "cavs_v15")
    set(SR_XT_TC_SOC intel_apl_adsp)
  elseif("${SOC_SERIES}" STREQUAL "cavs_v18")
    set(SR_XT_TC_SOC intel_s1000)
  elseif("${SOC_SERIES}" STREQUAL "cavs_v20")
    set(SR_XT_TC_SOC intel_s1000)
  elseif("${SOC_SERIES}" STREQUAL "cavs_v25")
    set(SR_XT_TC_SOC intel_s1000)
  elseif("${SOC_SERIES}" STREQUAL "baytrail_adsp")
    set(SR_XT_TC_SOC intel_byt_adsp)
  elseif("${SOC_SERIES}" STREQUAL "broadwell_adsp")
    set(SR_XT_TC_SOC intel_bdw_adsp)
  elseif("${SOC_SERIES}" STREQUAL "imx8")
    set(SR_XT_TC_SOC nxp_imx_adsp)
  elseif("${SOC_SERIES}" STREQUAL "imx8m")
    set(SR_XT_TC_SOC nxp_imx8m_adsp)
  else()
    message(FATAL_ERROR "Not compiler set for SOC_SERIES ${SOC_SERIES}")
 endif()
 set(SYSROOT_DIR ${TOOLCHAIN_HOME}/xtensa/${SR_XT_TC_SOC}/${SYSROOT_TARGET})
 set(CROSS_COMPILE ${TOOLCHAIN_HOME}/xtensa/${SR_XT_TC_SOC}/${CROSS_COMPILE_TARGET}/bin/${CROSS_COMPILE_TARGET}-)
else()
  # Non-Xtensa SDK toolchains follow a simpler convention
  set(SYSROOT_DIR   ${TOOLCHAIN_HOME}/${SYSROOT_TARGET}/${SYSROOT_TARGET})
  set(CROSS_COMPILE ${TOOLCHAIN_HOME}/${CROSS_COMPILE_TARGET}/bin/${CROSS_COMPILE_TARGET}-)
endif()

if("${ARCH}" STREQUAL "x86")
  if(CONFIG_X86_64)
    list(APPEND TOOLCHAIN_C_FLAGS -m64)
    list(APPEND TOOLCHAIN_LD_FLAGS -m64)
  else()
    list(APPEND TOOLCHAIN_C_FLAGS -m32)
    list(APPEND TOOLCHAIN_LD_FLAGS -m32)
  endif()
endif()
