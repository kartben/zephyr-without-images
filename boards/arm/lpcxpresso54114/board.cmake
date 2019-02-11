#
# Copyright (c) 2017, NXP
#
# SPDX-License-Identifier: Apache-2.0
#

set_ifndef(LPCLINK_FW jlink)

if(LPCLINK_FW STREQUAL jlink)
  set_ifndef(BOARD_DEBUG_RUNNER jlink)
  set_ifndef(BOARD_FLASH_RUNNER jlink)
endif()

if(CONFIG_BOARD_LPCXPRESSO54114_M4)
board_runner_args(jlink "--device=LPC54114J256_M4" "--reset-after-load")
elseif(CONFIG_BOARD_LPCXPRESSO54114_M0)
board_runner_args(jlink "--device=LPC54114J256_M0" "--reset-after-load")
endif()

include(${ZEPHYR_BASE}/boards/common/jlink.board.cmake)
