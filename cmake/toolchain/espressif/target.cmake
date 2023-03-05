# SPDX-License-Identifier: Apache-2.0

zephyr_get(ESPRESSIF_TOOLCHAIN_PATH)
assert(    ESPRESSIF_TOOLCHAIN_PATH "ESPRESSIF_TOOLCHAIN_PATH is not set")

set(COMPILER gcc)
set(LINKER ld)
set(BINTOOLS gnu)

set(CROSS_COMPILE_TARGET_xtensa_esp32     xtensa-esp32-elf)
set(CROSS_COMPILE_TARGET_xtensa_esp32s2   xtensa-esp32s2-elf)
set(CROSS_COMPILE_TARGET_xtensa_esp32s3   xtensa-esp32s3-elf)
set(CROSS_COMPILE_TARGET_riscv_esp32c3    riscv32-esp-elf)

set(CROSS_COMPILE_TARGET ${CROSS_COMPILE_TARGET_${ARCH}_${CONFIG_SOC}})
set(SYSROOT_TARGET       ${CROSS_COMPILE_TARGET})

if(ESPRESSIF_DEPRECATED_PATH)
  set(TOOLCHAIN_HOME ${ESPRESSIF_TOOLCHAIN_PATH})
else()
  set(TOOLCHAIN_HOME ${ESPRESSIF_TOOLCHAIN_PATH}/${CROSS_COMPILE_TARGET})
endif()

set(CROSS_COMPILE ${TOOLCHAIN_HOME}/bin/${CROSS_COMPILE_TARGET}-)
set(SYSROOT_DIR   ${TOOLCHAIN_HOME}/${SYSROOT_TARGET})

set(TOOLCHAIN_HAS_NEWLIB ON CACHE BOOL "True if toolchain supports newlib")

message(STATUS "Found toolchain: espressif (${ESPRESSIF_TOOLCHAIN_PATH})")
