"""
Copyright (c) 2021 Zephyr Project members and individual contributors
SPDX-License-Identifier: Apache-2.0

This module contains a variable with a list of tuples (old_url, new_url) for
pages to redirect. This list allows redirecting old URLs (caused by reorganizing
doc directories)

Notes:
    - Please keep this list sorted alphabetically.
    - URLs must be relative to document root (with NO leading slash), and
      without the html extension).
"""

REDIRECTS = [
    ('application/index', 'develop/application/index'),
    ('development_process/code_flow', 'project/code_flow'),
    ('development_process/index', 'project/index'),
    ('development_process/issues', 'project/issues'),
    ('development_process/proposals', 'project/proposals'),
    ('getting_started/index', 'develop/getting_started/index'),
    ('guides/arch/arm_cortex_m', 'hardware/arch/arm_cortex_m'),
    ('guides/arch/index', 'hardware/arch/index'),
    ('guides/arch/x86', 'hardware/arch/x86'),
    ('guides/beyond-GSG', 'develop/beyond-GSG'),
    ('guides/bluetooth/index', 'connectivity/bluetooth/index'),
    ('guides/bluetooth/sm-pics', 'connectivity/bluetooth/sm-pics'),
    ('guides/build/index', 'build/cmake/index'),
    ('guides/build/kconfig/extensions', '/build/kconfig/extensions'),
    ('guides/build/kconfig/menuconfig', '/build/kconfig/menuconfig'),
    ('guides/build/kconfig/setting', '/build/kconfig/setting'),
    ('guides/build/kconfig/tips', '/build/kconfig/tips'),
    ('guides/coccinelle', 'develop/tools/coccinelle'),
    ('guides/code-relocation', 'kernel/code-relocation'),
    ('guides/crypto/index', 'services/crypto/index'),
    ('guides/crypto/tinycrypt', 'services/crypto/tinycrypt'),
    ('guides/device_mgmt/dfu', 'services/device_mgmt/dfu'),
    ('guides/device_mgmt/index', 'services/device_mgmt/index'),
    ('guides/device_mgmt/mcumgr', 'services/device_mgmt/mcumgr'),
    ('guides/device_mgmt/ota', 'services/device_mgmt/ota'),
    ('guides/dts/api-usage', 'build/dts/api-usage'),
    ('guides/dts/bindings', 'build/dts/bindings'),
    ('guides/dts/design', 'build/dts/design'),
    ('guides/dts/dt-vs-kconfig', 'build/dts/dt-vs-kconfig'),
    ('guides/dts/howtos', 'build/dts/howtos'),
    ('guides/dts/index', 'build/dts/index'),
    ('guides/dts/intro', 'build/dts/intro'),
    ('guides/dts/macros.bnf', 'build/dts/macros.bnf'),
    ('guides/dts/main-example.dts', 'build/dts/main-example.dts'),
    ('guides/dts/troubleshooting', 'build/dts/troubleshooting'),
    ('guides/emulator/index', 'hardware/emulator/index'),
    ('guides/env_vars', 'develop/env_vars'),
    ('guides/flash_debug/host-tools', 'develop/flash_debug/host-tools'),
    ('guides/flash_debug/index', 'develop/flash_debug/index'),
    ('guides/flash_debug/probes', 'develop/flash_debug/probes'),
    ('guides/modules', 'develop/modules'),
    ('guides/networking/index', 'connectivity/networking/index'),
    ('guides/optimizations/index', 'develop/optimizations/index'),
    ('guides/optimizations/tools', 'develop/optimizations/tools'),
    ('guides/pinctrl/index', 'hardware/pinctrl/index'),
    ('guides/platformio/index', 'develop/tools/platformio/index'),
    ('guides/pm/device', 'services/pm/device'),
    ('guides/pm/device_runtime', 'services/pm/device_runtime'),
    ('guides/pm/index', 'services/pm/index'),
    ('guides/pm/overview', 'services/pm/overview'),
    ('guides/pm/power_domain', 'services/pm/power_domain'),
    ('guides/pm/system', 'services/pm/system'),
    ('guides/portability/index', 'services/portability/index'),
    ('guides/portability/posix', 'services/portability/posix'),
    ('guides/porting/arch', 'hardware/porting/arch'),
    ('guides/porting/board_porting', 'hardware/porting/board_porting'),
    ('guides/porting/index', 'hardware/porting/index'),
    ('guides/porting/shields', 'hardware/porting/shields'),
    ('guides/smf/index', 'services/smf/index'),
    ('guides/test/coverage', 'develop/test/coverage'),
    ('guides/test/index', 'develop/test/index'),
    ('guides/test/mocking.c', 'develop/test/mocking.c'),
    ('guides/test/twister', 'develop/test/twister'),
    ('guides/test/ztest', 'develop/test/ztest'),
    ('guides/tfm/build', 'services/tfm/build'),
    ('guides/tfm/index', 'services/tfm/index'),
    ('guides/tfm/integration', 'services/tfm/integration'),
    ('guides/tfm/overview', 'services/tfm/overview'),
    ('guides/tfm/requirements', 'services/tfm/requirements'),
    ('guides/tfm/testsuites', 'services/tfm/testsuites'),
    ('guides/west/basics', 'develop/west/basics'),
    ('guides/west/build-flash-debug', 'develop/west/build-flash-debug'),
    ('guides/west/built-in', 'develop/west/built-in'),
    ('guides/west/config', 'develop/west/config'),
    ('guides/west/extensions', 'develop/west/extensions'),
    ('guides/west/index', 'develop/west/index'),
    ('guides/west/install', 'develop/west/install'),
    ('guides/west/manifest', 'develop/west/manifest'),
    ('guides/west/moving-to-west', 'develop/west/moving-to-west'),
    ('guides/west/release-notes', 'develop/west/release-notes'),
    ('guides/west/sign', 'develop/west/sign'),
    ('guides/west/troubleshooting', 'develop/west/troubleshooting'),
    ('guides/west/west-apis', 'develop/west/west-apis'),
    ('guides/west/west-not-found', 'develop/west/west-not-found'),
    ('guides/west/why', 'develop/west/why'),
    ('guides/west/without-west', 'develop/west/without-west'),
    ('guides/west/workspaces', 'develop/west/workspaces'),
    ('guides/west/zephyr-cmds', 'develop/west/zephyr-cmds'),
    ('guides/zephyr_cmake_package', 'build/zephyr_cmake_package'),
    ('reference/api/api_lifecycle', 'develop/api/api_lifecycle'),
    ('reference/api/index', 'develop/api/index'),
    ('reference/api/overview', 'develop/api/overview'),
    ('reference/api/terminology', 'develop/api/terminology'),
    ('reference/drivers/index', 'kernel/drivers/index'),
    ('reference/file_system/index', 'services/file_system/index'),
    ('reference/libc/index', 'kernel/libc/index'),
    ('reference/logging/index', 'services/logging/index'),
    ('reference/misc/notify', 'services/notify'),
    ('reference/misc/timeutil', 'kernel/timeutil'),
    ('reference/modbus/index', 'services/modbus/index'),
    ('reference/networking/sockets', 'connectivity/networking/api/sockets'),
    ('reference/peripherals/adc', 'hardware/peripherals/adc'),
    ('reference/peripherals/dac', 'hardware/peripherals/dac'),
    ('reference/peripherals/dma', 'hardware/peripherals/dma'),
    ('reference/peripherals/eeprom', 'hardware/peripherals/eeprom'),
    ('reference/peripherals/espi', 'hardware/peripherals/espi'),
    ('reference/peripherals/flash', 'hardware/peripherals/flash'),
    ('reference/peripherals/gna', 'hardware/peripherals/gna'),
    ('reference/peripherals/gpio', 'hardware/peripherals/gpio'),
    ('reference/peripherals/hwinfo', 'hardware/peripherals/hwinfo'),
    ('reference/peripherals/i2c', 'hardware/peripherals/i2c'),
    ('reference/peripherals/index', 'hardware/peripherals/index'),
    ('reference/peripherals/ipm', 'hardware/peripherals/ipm'),
    ('reference/peripherals/kscan', 'hardware/peripherals/kscan'),
    ('reference/peripherals/led', 'hardware/peripherals/led'),
    ('reference/peripherals/mbox', 'hardware/peripherals/mbox'),
    ('reference/peripherals/mdio', 'hardware/peripherals/mdio'),
    ('reference/peripherals/peci', 'hardware/peripherals/peci'),
    ('reference/peripherals/pinmux', 'hardware/peripherals/pinmux'),
    ('reference/peripherals/ps2', 'hardware/peripherals/ps2'),
    ('reference/peripherals/pwm', 'hardware/peripherals/pwm'),
    ('reference/peripherals/reset', 'hardware/peripherals/reset'),
    ('reference/peripherals/rtc', 'hardware/peripherals/rtc'),
    ('reference/peripherals/sensor', 'hardware/peripherals/sensor'),
    ('reference/peripherals/spi', 'hardware/peripherals/spi'),
    ('reference/peripherals/tcpc', 'hardware/peripherals/tcpc'),
    ('reference/peripherals/uart', 'hardware/peripherals/uart'),
    ('reference/peripherals/video', 'hardware/peripherals/video'),
    ('reference/pm/index', 'services/pm/api/index'),
    ('reference/settings/index', 'services/settings/index'),
    ('reference/shell/index', 'services/shell/index'),
    ('reference/storage/fcb/fcb', 'services/storage/fcb/fcb'),
    ('reference/storage/index', 'services/storage/index'),
    ('reference/storage/nvs/nvs', 'services/storage/nvs/nvs'),
    ('reference/task_wdt/index', 'services/task_wdt/index'),
    ('reference/usb/hid', 'services/usb/hid'),
    ('reference/usb/index', 'services/usb/index'),
    ('reference/usb/udc', 'services/usb/udc'),
    ('reference/usb/uds', 'services/usb/uds'),
    ('reference/usb/uds_cdc_acm', 'services/usb/uds_cdc_acm'),
    ('reference/usb/uds_testing', 'services/usb/uds_testing'),
    ('reference/usermode/index', 'kernel/usermode/index'),
    ('reference/usermode/overview', 'kernel/usermode/overview'),
    ('reference/usermode/syscalls', 'kernel/usermode/syscalls'),
    ('reference/util/index', 'kernel/util/index'),
]
