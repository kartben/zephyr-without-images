# SPDX-License-Identifier: Apache-2.0

set(SUPPORTED_EMU_PLATFORMS renode)
set(RENODE_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/support/m2gl025_miv.resc)
set(RENODE_UART sysbus.uart)

set_ifndef(BOARD_SIM_RUNNER renode)
include(${ZEPHYR_BASE}/boards/common/renode.board.cmake)
