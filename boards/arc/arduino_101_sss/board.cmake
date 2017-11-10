if(DEFINED ENV{ZEPHYR_FLASH_OVER_DFU})
  set(FLASH_SCRIPT dfuutil.sh)

  set(DFUUTIL_PID 8087:0aba)
  set(DFUUTIL_ALT sensor_core)
  set(DFUUTIL_IMG ${PROJECT_BINARY_DIR}/${KERNEL_BIN_NAME})

  set_property(GLOBAL APPEND PROPERTY FLASH_SCRIPT_ENV_VARS
    DFUUTIL_PID
    DFUUTIL_ALT
    DFUUTIL_IMG
    )
else()
  set(FLASH_SCRIPT openocd.sh)
endif()

set(DEBUG_SCRIPT openocd.sh)

set(OPENOCD_PRE_CMD "targets 1")
set(OPENOCD_LOAD_CMD "load_image     ${PROJECT_BINARY_DIR}/${KERNEL_BIN_NAME} ${CONFIG_FLASH_BASE_ADDRESS}")
set(OPENOCD_VERIFY_CMD "verify_image ${PROJECT_BINARY_DIR}/${KERNEL_BIN_NAME} ${CONFIG_FLASH_BASE_ADDRESS}")
set(GDB_PORT 3334)

set_property(GLOBAL APPEND PROPERTY FLASH_SCRIPT_ENV_VARS
  OPENOCD_PRE_CMD
  OPENOCD_LOAD_CMD
  OPENOCD_VERIFY_CMD
  GDB_PORT
  )
