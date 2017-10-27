if(DEFINED ENV{ZEPHYR_FLASH_OVER_DFU})
  set(FLASH_SCRIPT dfuutil.sh)

  set_property(GLOBAL APPEND PROPERTY FLASH_SCRIPT_ENV_VARS
    DFUUTIL_PID=8087:0aba
    DFUUTIL_ALT=x86_app
    DFUUTIL_IMG=${PROJECT_BINARY_DIR}/${KERNEL_BIN_NAME}
    )
else()
  set(FLASH_SCRIPT openocd.sh)
endif()

set(DEBUG_SCRIPT openocd.sh)

set_property(GLOBAL APPEND PROPERTY FLASH_SCRIPT_ENV_VARS
  OPENOCD_PRE_CMD="targets 1"
  OPENOCD_LOAD_CMD="load_image     ${PROJECT_BINARY_DIR}/${KERNEL_BIN_NAME} ${CONFIG_FLASH_BASE_ADDRESS}"
  OPENOCD_VERIFY_CMD="verify_image ${PROJECT_BINARY_DIR}/${KERNEL_BIN_NAME} ${CONFIG_FLASH_BASE_ADDRESS}"
  )
