set(BOARD_FLASH_RUNNER em-starterkit)
set(BOARD_DEBUG_RUNNER em-starterkit)

set(OPENOCD_LOAD_CMD "load_image     ${PROJECT_BINARY_DIR}/${KERNEL_ELF_NAME} ${CONFIG_FLASH_BASE_ADDRESS}")
set(OPENOCD_VERIFY_CMD "verify_image ${PROJECT_BINARY_DIR}/${KERNEL_ELF_NAME} ${CONFIG_FLASH_BASE_ADDRESS}")

set_property(GLOBAL APPEND PROPERTY FLASH_SCRIPT_ENV_VARS
  OPENOCD_LOAD_CMD
  OPENOCD_VERIFY_CMD
  )
