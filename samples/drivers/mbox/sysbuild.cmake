# Copyright (c) 2023 Nordic Semiconductor ASA
# Copyright 2023-2024 NXP
# SPDX-License-Identifier: Apache-2.0

if("${SB_CONFIG_REMOTE_BOARD}" STREQUAL "")
	message(FATAL_ERROR
	"Target ${BOARD}${BOARD_QUALIFIERS} not supported for this sample. "
	"There is no remote board selected in Kconfig.sysbuild")
endif()

set(REMOTE_APP remote)

ExternalZephyrProject_Add(
	APPLICATION ${REMOTE_APP}
	SOURCE_DIR  ${APP_DIR}/${REMOTE_APP}
	BOARD       ${SB_CONFIG_REMOTE_BOARD}
)

native_simulator_set_child_images(${DEFAULT_IMAGE} ${REMOTE_APP})

native_simulator_set_final_executable(${DEFAULT_IMAGE})

if(SB_CONFIG_BOARD_MIMXRT1160_EVK_MIMXRT1166_CM7 OR
   SB_CONFIG_BOARD_MIMXRT1170_EVK_MIMXRT1176_CM7 OR
   SB_CONFIG_BOARD_LPCXPRESSO55S69_LPC55S69_CPU0)
  # For these NXP boards the main core application is dependent on
  # 'zephyr_image_info.h' generated by remote application.

  # Let's build the remote application first
  add_dependencies(${DEFAULT_IMAGE} ${REMOTE_APP})
endif()
