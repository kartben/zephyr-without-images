# SPDX-License-Identifier: Apache-2.0

if(DEFINED $ENV{CLANG_ROOT_DIR})
  set(TOOLCHAIN_HOME ${CLANG_ROOT}/bin/)
endif()

set(COMPILER clang)
set(LINKER ld) # TODO: Use lld eventually rather than GNU ld

if("${ARCH}" STREQUAL "arm")
  set(triple arm-none-eabi)
  set(CMAKE_EXE_LINKER_FLAGS_INIT "--specs=nosys.specs")
elseif("${ARCH}" STREQUAL "x86")
  set(triple i686-pc-none-elf)
endif()

set(CMAKE_C_COMPILER_TARGET   ${triple})
set(CMAKE_ASM_COMPILER_TARGET ${triple})
set(CMAKE_CXX_COMPILER_TARGET ${triple})

if("${ARCH}" STREQUAL "posix")
  set(TOOLCHAIN_HAS_NEWLIB OFF CACHE BOOL "True if toolchain supports newlib")
endif()
