# Copyright (c) 2019 Nordic Semiconductor ASA

# SPDX-License-Identifier: Apache-2.0

board_runner_args(jlink "--device=nRF52840_xxAA" "--speed=4000")
include(${ZEPHYR_BASE}/boards/common/nrfjprog.board.cmake)
include(${ZEPHYR_BASE}/boards/common/nrfutil.board.cmake)
include(${ZEPHYR_BASE}/boards/common/jlink.board.cmake)
include(${ZEPHYR_BASE}/boards/common/openocd-nrf5.board.cmake)
