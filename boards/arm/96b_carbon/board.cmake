set(FLASH_SCRIPT dfuutil.sh)

set_property(GLOBAL APPEND PROPERTY FLASH_SCRIPT_ENV_VARS
  DFUUTIL_PID=0483:df11
  DFUUTIL_ALT=0
  DFUUTIL_IMG=${PROJECT_BINARY_DIR}/${KERNEL_BIN_NAME}
  DFUUTIL_DFUSE_ADDR=${CONFIG_FLASH_BASE_ADDRESS}
  )
