# SPDX-License-Identifier: Apache-2.0
board_runner_args(pyocd "--target=stm32wb55rgvx")
board_runner_args(stm32cubeprogrammer "--port=swd" "--reset=hw")

include(${ZEPHYR_BASE}/boards/common/openocd.board.cmake)
include(${ZEPHYR_BASE}/boards/common/pyocd.board.cmake)
include(${ZEPHYR_BASE}/boards/common/stm32cubeprogrammer.board.cmake)
