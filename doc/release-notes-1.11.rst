:orphan:

.. _zephyr_1.11:

Zephyr Kernel 1.11.0
#####################

We are pleased to announce the release of Zephyr kernel version 1.11.0.

Major enhancements with this release include:

* Thread-level memory protection on x86, ARC and ARM, userspace and memory
  domains
* Symmetric Multi Processing (SMP) support on the Xtensa architecture.
* Initial Armv8-M architecture support.
* Native development environment on Microsoft Windows.
* Native build target on POSIX platforms.
* POSIX PSE52 partial support.
* Thread support via integration with OpenThread.
* Over the Air Firmware Updates over BLE using MCUmgr.
* Lightweight flash storage layer for constrained devices.

* Additional SoC, platform and driver support for many of the already supported
  platforms.

The following sections provide detailed lists of changes by component.

Kernel
******

* Initial Symmetric Multi Processing (SMP) support added:
  * SMP-aware scheduler
  * SMP timer and idling support
  * Available on the Xtensa architecture
* POSIX PSE52 support:
  * Timer, clock, scheduler and pthread APIs

Architectures
*************

* User space and system call related changes:
  * Added ARC user space implementation
  * Added ARM user space implementation
  * Fixed a few MPU related issues with stack guards
* Armv8-M iniital architecture support, including the following cores:
  * Arm Cortex-M23
  * Arm Cortex-M33
* New "posix" architecture for native GNU/Linux and macOS build targets:
  * Targets native executables that can be run on the operating system

Boards
******

* New native_posix board for the posix architecture:
  * Includes a template for hardware models
  * Adds support for console and logging
  * Interrupts and timers are simulated in several different configurations
* Added support for the following ARM boards:

  * adafruit_trinket_m0
  * arduino_zero
  * lpcxpresso54114
  * nrf52_sparkfun
  * nucleo_f429zi
  * stm32f072_eval
  * stm32f072b_disco
* Removed Panther board support which included boards/x86/panther and
  boards/arc/panther_ss
* Refactored dts.fixup so common SoC related fixes are in arch/<*>/soc
  and board dts.fixup only used for board specific items.

Drivers and Sensors
*******************

* New LED PWM driver for ESP32 SoC
* Fixed ESP32 I2C driver

Networking
**********

* Generic OpenThread support added
* OpenThread support to nrf5 IEEE 802.15.4 driver added
* NXP MCUX ethernet driver IPv6 multicast join/leave enhancements
* Ethernet stm32 fixes
* IEEE 802.15.4 Sub-GHz TI CC1200 chip support added
* IEEE 802.15.4 test driver (upipe) hw filtering support added
* IEEE 802.15.4 radio API enhancements
* Net loopback driver fixes
* Net management API event enhancements
* IPv6 neighbor addition and removal can be monitored
* Static IPv4 and DHCPv4 configuration enhancements
* Bluetooth IPSP disconnect fix
* Network buffer enhancements
* ICMPv4 and ICMPv6 error checking fixes
* Network interface address handling enhancements
* Add routing support between network interfaces
* LWM2M fixes and enhancements
* Old legacy HTTP API removed
* Old legacy ZoAP API removed
* CoAP fixes
* TCP fixes
* HTTP fixes
* RPL fixes
* Net-app API fixes
* Net-shell fixes
* BSD socket API fixes

Bluetooth
*********

* Multiple fixes to the controller
* Fixed potential connection transmission deadlock issue with the help
  of a dedicated fragment pool
* Multiple fixes to Mesh support
* Added test automation for Mesh (for tests/bluetooth/tester)

Build and Infrastructure
************************

* Native development enviroment on Microsoft Windows:
  * Uses CMake and Kconfiglib to avoid requiring an emulation layer
  * Package management support with Chocolatey for simple setup
  * Build time now comparable to Linux and macOS using Ninja

Libraries / Subsystems
***********************

* New management subystem based on the cross-RTOS MCUmgr:
  * Secure Firmware Updates over BLE and serial
  * Support for file system access and statistics
  * mcumgr cross-platform command-line tool

* FCB (File Circular Buffer) lightweight storage layer:
  * Wear-levelling support for NOR flashes
  * Suitable for memory constrained devices

HALs
****

* Updated ARM CMSIS from version 4 to 5.2.0
* Updated stm32cube stm32l4xx from version 1.9.0 to 1.10.0
* Updated stm32cube stm32f4xx from version 1.16.0 to 1.18.0
* Added Atmel SAMD21 HAL
* Added mcux 2.2.1 for lpc54114
* Added HAL for vl53l0x sensor from STM
* Imported and moved to nrfx 0.8.0 on Nordic SoCs
* Added QSPI Controller HAL driver

Documentation
*************

* Added MPU specific stack and userspace documentation
* Improved docs for Native (POSIX) support
* Docs for new samples and supported board
* General documentation clarifications and improvements
* Addressed Sphinx-generated intra-page link issues
* Updated doc generation tools (Doxygen, Sphinx, Breathe, Docutils)

Tests and Samples
*****************

* Added additional tests and test improvements for user space testing

Issue Related Items
*******************

These GitHub issues were addressed since the previous 1.10.0 tagged
release:

.. comment  List derived from Jira/GitHub Issue query: ...


