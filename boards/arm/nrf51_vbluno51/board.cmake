set(BOARD_FLASH_RUNNER pyocd)
set(BOARD_DEBUG_RUNNER pyocd)

set(PYOCD_TARGET nrf51)

set_property(GLOBAL APPEND PROPERTY FLASH_SCRIPT_ENV_VARS
  PYOCD_TARGET
  )
