# SPDX-License-Identifier: Apache-2.0

set(CROSS_COMPILE_TARGET_arm         arm-zephyr-eabi)
set(CROSS_COMPILE_TARGET_nios2     nios2-zephyr-elf)
set(CROSS_COMPILE_TARGET_riscv   riscv64-zephyr-elf)
set(CROSS_COMPILE_TARGET_mips     mipsel-zephyr-elf)
set(CROSS_COMPILE_TARGET_xtensa   xtensa-zephyr-elf)
set(CROSS_COMPILE_TARGET_arc         arc-zephyr-elf)
set(CROSS_COMPILE_TARGET_x86      x86_64-zephyr-elf)

set(CROSS_COMPILE_TARGET ${CROSS_COMPILE_TARGET_${ARCH}})
set(SYSROOT_TARGET       ${CROSS_COMPILE_TARGET})

if("${ARCH}" STREQUAL "xtensa")
  set(SYSROOT_DIR ${TOOLCHAIN_HOME}/xtensa/${SOC_NAME}/${SYSROOT_TARGET})
  set(TOOLCHAIN_INCLUDES
    ${SYSROOT_DIR}/include/arch/include
    ${SYSROOT_DIR}/include
    )

  LIST(APPEND TOOLCHAIN_LIBS hal)
  LIST(APPEND LIB_INCLUDE_DIR -L${SYSROOT_DIR}/lib)
  set(CROSS_COMPILE ${TOOLCHAIN_HOME}/xtensa/${SOC_NAME}/${CROSS_COMPILE_TARGET}/bin/${CROSS_COMPILE_TARGET}-)
else()
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
