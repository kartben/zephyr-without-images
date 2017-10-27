set(FLASH_SCRIPT openocd.sh)
set(DEBUG_SCRIPT openocd.sh)

set(FLASH_BASE_ADDRESS 0x08000000)

set_property(GLOBAL APPEND PROPERTY FLASH_SCRIPT_ENV_VARS
  OPENOCD_LOAD_CMD="flash write_image erase ${PROJECT_BINARY_DIR}/${KERNEL_BIN_NAME} ${FLASH_BASE_ADDRESS}"
  OPENOCD_VERIFY_CMD="verify_image          ${PROJECT_BINARY_DIR}/${KERNEL_BIN_NAME} ${FLASH_BASE_ADDRESS}"
  )
