include($ENV{ZEPHYR_BASE}/boards/common/openocd.board.cmake)

set(OPENOCD_LOAD_CMD "load_image     ${PROJECT_BINARY_DIR}/${KERNEL_BIN_NAME} ${CONFIG_FLASH_BASE_ADDRESS}")

set_property(GLOBAL APPEND PROPERTY FLASH_SCRIPT_ENV_VARS
  OPENOCD_LOAD_CMD
  )
