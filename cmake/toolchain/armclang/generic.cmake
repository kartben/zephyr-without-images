# SPDX-License-Identifier: Apache-2.0

set_ifndef(ARMCLANG_TOOLCHAIN_PATH "$ENV{ARMCLANG_TOOLCHAIN_PATH}")
set(ARMCLANG_TOOLCHAIN_PATH ${ARMCLANG_TOOLCHAIN_PATH} CACHE PATH "armclang tools install directory")
assert(ARMCLANG_TOOLCHAIN_PATH "ARMCLANG_TOOLCHAIN_PATH is not set")

if(NOT EXISTS ${ARMCLANG_TOOLCHAIN_PATH})
  message(FATAL_ERROR "Nothing found at ARMCLANG_TOOLCHAIN_PATH: '${ARMCLANG_TOOLCHAIN_PATH}'")
endif()

set(TOOLCHAIN_HOME ${ARMCLANG_TOOLCHAIN_PATH})

set(COMPILER armclang)
set(LINKER armlink)
set(BINTOOLS armclang)

set(SYSROOT_TARGET arm)

set(CROSS_COMPILE ${TOOLCHAIN_HOME}/bin/)

set(TOOLCHAIN_HAS_NEWLIB OFF CACHE BOOL "True if toolchain supports newlib")
