#
# Copyright (c) 2018, NXP
#
# SPDX-License-Identifier: Apache-2.0
#

board_runner_args(pyocd "--target=cortex_m")
board_runner_args(jlink "--device=MIMXRT1064")

include(${ZEPHYR_BASE}/boards/common/jlink.board.cmake)
include(${ZEPHYR_BASE}/boards/common/pyocd.board.cmake)
