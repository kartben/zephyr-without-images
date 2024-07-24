# Copyright (c) 2023-2024 Nordic Semiconductor
#
# SPDX-License-Identifier: Apache-2.0

# This sysbuild CMake file sets the sysbuild controlled settings as properties
# on the main Zephyr image.

set_config_bool(${ZCMAKE_APPLICATION} CONFIG_BOOTLOADER_MCUBOOT "${SB_CONFIG_BOOTLOADER_MCUBOOT}")
set_config_string(${ZCMAKE_APPLICATION} CONFIG_MCUBOOT_SIGNATURE_KEY_FILE
                  "${SB_CONFIG_BOOT_SIGNATURE_KEY_FILE}"
)
set_config_string(${ZCMAKE_APPLICATION} CONFIG_MCUBOOT_ENCRYPTION_KEY_FILE
                  "${SB_CONFIG_BOOT_ENCRYPTION_KEY_FILE}"
)

if(SB_CONFIG_BOOTLOADER_MCUBOOT)
  if("${SB_CONFIG_SIGNATURE_TYPE}" STREQUAL "NONE")
    set_config_bool(${ZCMAKE_APPLICATION} CONFIG_MCUBOOT_GENERATE_UNSIGNED_IMAGE y)
  else()
    set_config_bool(${ZCMAKE_APPLICATION} CONFIG_MCUBOOT_GENERATE_UNSIGNED_IMAGE n)
  endif()

  if(SB_CONFIG_MCUBOOT_MODE_SINGLE_APP)
    set_config_bool(${ZCMAKE_APPLICATION} CONFIG_MCUBOOT_BOOTLOADER_MODE_SINGLE_APP y)
  elseif(SB_CONFIG_MCUBOOT_MODE_SWAP_WITHOUT_SCRATCH)
    set_config_bool(${ZCMAKE_APPLICATION} CONFIG_MCUBOOT_BOOTLOADER_MODE_SWAP_WITHOUT_SCRATCH y)
  elseif(SB_CONFIG_MCUBOOT_MODE_SWAP_SCRATCH)
    set_config_bool(${ZCMAKE_APPLICATION} CONFIG_MCUBOOT_BOOTLOADER_MODE_SWAP_SCRATCH y)
  elseif(SB_CONFIG_MCUBOOT_MODE_OVERWRITE_ONLY)
    set_config_bool(${ZCMAKE_APPLICATION} CONFIG_MCUBOOT_BOOTLOADER_MODE_OVERWRITE_ONLY y)
  elseif(SB_CONFIG_MCUBOOT_MODE_DIRECT_XIP)
    set_config_bool(${ZCMAKE_APPLICATION} CONFIG_MCUBOOT_BOOTLOADER_MODE_DIRECT_XIP y)
  elseif(SB_CONFIG_MCUBOOT_MODE_DIRECT_XIP_WITH_REVERT)
    set_config_bool(${ZCMAKE_APPLICATION} CONFIG_MCUBOOT_BOOTLOADER_MODE_DIRECT_XIP_WITH_REVERT y)
  elseif(SB_CONFIG_MCUBOOT_MODE_RAM_LOAD)
    # Not yet supported in zephyr code
  elseif(SB_CONFIG_MCUBOOT_MODE_FIRMWARE_UPDATER)
    set_config_bool(${ZCMAKE_APPLICATION} CONFIG_MCUBOOT_BOOTLOADER_MODE_FIRMWARE_UPDATER y)
  endif()
endif()
