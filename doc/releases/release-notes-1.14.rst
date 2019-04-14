:orphan:

.. _zephyr_1.14:

Zephyr Kernel 1.14.0 (Working Draft)
####################################

We are pleased to announce the release of Zephyr kernel version 1.14.0.

Major enhancements with this release include:

* The Zephyr project now supports over 160 different board configurations
  spanning 8 architectures. All architectures are rigorously tested and
  validated using one of the many simulation platforms supported by the project.
  (QEMU, Renode, ARC Simulator and the native POSIX configuration).

* Overhaul of Network packet (:ref:`net-pkt <net_pkt_interface>`) API and move
  majority of components and protocols to the :ref:`BSD socket API
  <bsd_sockets_interface>` including MQTT, CoAP, LWM2M and SNTP.

* Enhanced the native POSIX port adding UART, USB and display
  drivers. Based on this port we added a simulated NRF52832 SoC which enables
  running full system, multi-node simulations, without the need of real hardware.

* Added an experimental BLE split software Controller with ith Upper Link Layer
  and Lower Link Layer for supporting multiple BLE radio hardware architectures.

* Power management, device idle power management

* In this release we introduced major updates and an overhaul to both the
  logging and the shell subsystems supporting multiple back-ends, integration of
  logging into the shell and delayed log processing.

* Introduced the ``west`` tool for management of multiple repositories and
  enhanced support for flashing and debugging.

* Enabled tickless kernel by default and reworked all timer driver to support
  the new mode.

* Added support for application user mode, application memory partitions and
  hardware stack protection in ARMv8m

* Applied MISRA-C code guideline on kernel and core components of Zephyr.
  MISRA-C is a well established code guideline focused on embedded systems and
  aims to improve code safety, security and portability.



The following sections provide detailed lists of changes by component.

Security Vulnerability Related
******************************

The following security vulnerabilities (CVEs) were addressed in this release:

* Tinycrypt HMAC-PRNG implementation doesn't take the HMAC state
  clearing into account as it performs the HMAC operations, thereby using a
  incorrect HMAC key for some of the HMAC operations.
  CVE-2017-14200

* The shell DNS command can cause unpredictable results due to misuse of stack
  variables.
  CVE-2017-14201

* The shell implementation does not protect against buffer overruns resulting
  in unpredictable behavior.
  CVE-2017-14202

* We introduced Kernel Page Table Isolation, a technique for
  mitigating the Meltdown security vulnerability on x86 systems. This
  technique helps isolate user and kernel space memory by ensuring
  non-essential kernel pages are unmapped in the page tables when the CPU
  is running in the least privileged user mode, Ring 3. This is the
  fix for Rogue Data Cache Load (CVE-2017-5754).

* We also addressed these CVEs for the x86 port:

  - Bounds Check Bypass (CVE-2017-5753)
  - Branch Target Injection (CVE-2017-5715)
  - Speculative Store Bypass (CVE-2018-3639)
  - L1 Terminal Fault (CVE-2018-3620)
  - Lazy FP State Restore (CVE-2018-3665)

Kernel
******

* K_THREAD_STACK_BUFFER() has been demoted to a private API and will be removed
  in a future Zephyr release.
* A new API sys_mutex has been introduced. It has the same semantics
  as a k_mutex, but the memory for it can reside in user memory and there is
  no explicit permission management required.
* sys_mem_pool() now uses a sys_mutex() for concurrency control.
* Memory protection:

  - CONFIG_APPLICATION_MEMORY has been removed from Zephyr. All test cases
    have been appropriately converted to use memory domains.
  - The build time memory domain partition generation mechanism, formerly
    an optional feature under CONFIG_APP_SHARED_MEM, has been overhauled
    and is now a core part of memory protection.
  - Userspace is no longer enabled by default for tests. Tests that are
    written to execute wholly or in part in user mode will need to enable
    CONFIG_TEST_USERSPACE in the test's project configuration. There are
    assertions in place to enforce that this is done.
  - The default stack size for handling system calls has been increased to
    1024 bytes.

* We start applying MISRA-C (https://www.misra.org.uk/) code guideline on
  Zephyr's kernel. MISRA-C is a well established code guideline focused on
  embedded systems and aims to improve code safety, security and portability.
  This initial effort was narrowed to Zephyr's kernel and architecture code and
  was concentrated only in mandatory and required rules. The following rules
  have been addressed:

  - Namespace changes
  - Normalize switch() operators
  - Avoid implicit conversion to boolean types
  - Fix and normalize headers guard
  - Make if() evaluate boolean operands
  - Remove all VLAs (variable length array)
  - Avoid undefined and implementation defined behavior with shift operator
  - Remove recursions

Architectures
*************

* Introduced X86_64 (64 bit) architecture support with SMP features
* High-level Kconfig symbol structure for Trusted Execution

* ARM

  * Re-architect Memory Protection code for ARM and NXP
  * Fully support application user mode in ARMv8m
  * Fully support application memory partitions in ARMv8m
  * Fully support hardware stack protection in ARMv8m
  * Support built-in stack overflow protection in user mode in ARMv8m
  * Fix stack overflow error reporting
  * Support executing from SRAM in XIP builds
  * Support non-cacheable memory sections
  * Remove power-of-two align and size requirement for ARMv8-m
  * Introduce sync barriers in arm-specific IRQ lock/unlock functions
  * Enforce double-word stack alignment on exception entry
  * API to allow Non-Secure FPU Access (ARMv8-M)
  * Various enhancements in ARM system boot code
  * Indicate Secure domain fault in Non-Secure fault exception
  * Update ARM CMSIS headers to version 5.4.0

* ARC:

  * Userspace and MPU driver improvements
  * Optimization of the thread stack definition macros
  * Bug fixes: handling of lp_xxx registers in _rirq_return_from_coop, nested
    interrupt handling, hardware stack bounds checking, execution benchmarking
  * Atomic operations are now usable from user mode on all ARC CPUs

* x86:

  - Support for non-PAE page tables has been dropped.
  - Various security CVEs related to micro-arch side effects of speculative
    execution fixed as detailed in the security notes.
  - Added robustness when reporting exceptions generated due to stack
    overflows or were induced in user mode
  - Pages containing read-only data no longer have the execute disable (XD)
    bit un-set.
  - Fix potential IRQ stack corruption when handling double faults


Boards & SoC Support
********************

* Added the all new :ref:`NRF52 simulated board <nrf52_bsim>`:
  It models some of the hardware in an NRF52832 SOC, to enable running
  full system, multi-node simulations, without the need of real hardware.
  Enabling fast, reproducible tests, development and debugging of the
  application, BT stack and kernel. It relies on `BabbleSim`_
  to simulate the radio physical layer.

* Added SoC configuration for nRF9160 Arm Cortex-M33 CPU
* Added SoC configuration for Musca Arm Cortex-M33 CPU

* Added support for the following Arm boards:

  * 96b_stm32_sensor_mez
  * b_l072z_lrwan1
  * bl652_dvk
  * bl654_dvk
  * cy8ckit_062_wifi_bt_m0
  * cy8ckit_062_wifi_bt_m4
  * efm32hg_slstk3400a
  * efm32pg_stk3402a
  * efr32mg_sltb004a
  * mimxrt1020_evk
  * mimxrt1060_evk
  * mimxrt1064_evk
  * nrf52832_mdk
  * nrf52840_blip
  * nrf52840_mdk
  * nrf52840_papyr
  * nrf52840_pca10090
  * nrf9160_pca10090
  * nucleo_f302r8
  * nucleo_f746zg
  * nucleo_f756zg
  * nucleo_l496zg
  * nucleo_l4r5zi
  * particle_argon
  * particle_xenon
  * v2m_musca

* Added support for the following RISC-V boards:

  * rv32m1_vega

* Added support for the following ARC boards:
  * Synopsys ARC IoT DevKit
  * Several ARC simulation targets (ARC nSIM EM/SEM; with and without MPU stack guards)

* Added support for the following shield boards:

  * frdm_kw41z
  * x_nucleo_iks01a1
  * x_nucleo_iks01a2

.. _BabbleSim:
   https://BabbleSim.github.io

Drivers and Sensors
*******************

* Added new drivers and backends for :ref:`native_posix <native_posix>`:

  * An UART driver which maps the Zephyr UART to a new host PTY
  * A USB driver which can expose a host connected USB device
  * A display driver which will render to a dedicated window using the SDL
    library
  * A dedicated backend for the new logger subsystem

* Counter

  * Refactored API
  * Ported existing counter and rtc drivers to the new API
  * Deprecated legacy API

* RTC

  - Deprecated RTC API. The Counter API should be used instead

* UART

  * Added asynchronous API.
  * Added implementation of the new asynchronous API for nRF series (UART and
    UARTE).

* ADC

  * ADC driver APIs are now available to threads running in user mode.
  * Overhauled adc_dw and renamed it to adc_intel_quark_se_c1000_ss
  * Fixed handling of invalid sampling requests

* Display

  * Introduced mcux elcdif shim driver
  * Added support for ssd16xx monochrome controllers
  * Added support for ssd1608, gde029a1, and hink e0154a05
  * Added SDL based display emulation driver
  * Added SSD1673 EPD controller driver
  * Added SSD1306 display controller driver


* Flash:

  * nRF5 flash driver support UICR operations
  * Added driver for STM32F7x series
  * Added flash driver support for Atmel SAM E70
  * Added a generic spi nor flash driver
  * Added flash driver for SiLabs Gecko SoCs

* Ethernet:

  * Extended mcux driver for i.mx rt socs
  * Added driver for Intel PRO/1000 Ethernet controller

* I2C

  * Added mcux lpi2c shim driver
  * Removed deprecated i2c_atmel_sam3 driver
  * Introduced Silabs i2c shim driver
  * Added support for I2S stm32

* Pinmux

  * Added RV32M1 driver
  * Added pinmux driver for Intel S1000
  * Added support for STM32F302x8

* PWM

  * Added SiFive PWM driver
  * Added Atmel SAM PWM driver
  * Converted nRF drivers to use device tree

* Sensor

  * Added lis2ds12, lis2dw12, lis2mdl, and lsm303dlhc drivers
  * Added ms5837 driver
  * Added support for Nordic QDEC
  * Converted drivers to use device tree

* Serial

  * Added RV32M1 driver
  * Added new asynchronous UART API
  * Added support for ARM PL011 UART
  * Introduced Silabs leuart shim serial driver
  * Adapted gecko uart driver for Silabs EFM32HG

* USB

  * Added native_posix USB driver
  * Added usb device driver for Atmel SAM E70 family
  * Added nRF52840 USBD driver


* Other Drivers

  * clock_control: Added RV32M1 driver
  * console: Removed telnet driver
  * entropy: Added Atmel SAM entropy generator driver
  * spi: Converted nRF drivers to use device tree
  * watchdog: Converted drivers to new API
  * wifi: simplelink: Implemented setsockopt() for TLS offload
  * wifi: Added inventek es-WiFi driver
  * timer: Refactored and accuracy improvements of the arcv2 timer driver (boot
    time measurements)
  * timer: Added/reworked Xtensa, RISV-V, NRF, HPET, and Arm systick drivers
  * gpio: Added RV32M1 driver
  * hwinfo: Added new hwinfo API and drivers
  * ipm: Added IMX IPM driver for i.MX socs
  * interrupt_controller: Added RV32M1 driver
  * interrupt_controller: Added support for STM32F302x8 EXTI_LINES
  * neural_net: Added Intel GNA driver
  * can: Added socket CAN support


Networking
**********

* The :ref:`BSD socket API <bsd_sockets_interface>` should be used by
  applications for any network connectivity needs.
* Majority of the network sample applications were converted to use
  the BSD socket API.
* New BSD socket based APIs were created for these components and protocols:

  - :ref:`MQTT <mqtt_socket_interface>`
  - :ref:`CoAP <coap_sock_interface>`
  - :ref:`LWM2M <lwm2m_interface>`
  - :ref:`SNTP <sntp_interface>`
* net-app client and server APIs were removed. This also required removal of
  the following net-app based legacy APIs:

  - MQTT
  - CoAP
  - SNTP
  - LWM2M
  - HTTP client and server
  - Websocket
* Network packet (:ref:`net-pkt <net_pkt_interface>`) API overhaul. The new
  net-pkt API uses less memory and is more streamlined than the old one.
* Implement following BSD socket APIs: ``freeaddrinfo()``, ``gethostname()``,
  ``getnameinfo()``, ``getsockopt()``, ``select()``, ``setsockopt()``,
  ``shutdown()``
* Converted BSD socket code to use global file descriptor numbers.
* Network subsystem converted to use new :ref:`logging system <logger>`.
* Added support for disabling IPv4, IPv6, UDP, and TCP simultaneously.
* Added support for :ref:`BSD socket offloading <net_socket_offloading>`.
* Added support for long lifetime IPv6 prefixes.
* Added enhancements to IPv6 multicast address checking.
* Added support for IPv6 Destination Options Header extension.
* Added support for packet socket (AF_PACKET).
* Added support for socket CAN (AF_CAN).
* Added support for SOCKS5 proxy in MQTT client.
* Added support for IPSO Timer object in LWM2M.
* Added support for receiving gratuitous ARP request.
* Added :ref:`sample application <google-iot-mqtt-sample>` for Google IoT Cloud.
* :ref:`Network interface <net_if_interface>` numbering starts now from 1 for
  POSIX compatibility.
* :ref:`OpenThread <thread_protocol_interface>` enhancements.
* :ref:`zperf <zperf-sample>` sample application fixes.
* :ref:`LLDP <lldp_interface>` (Link Layer Discovery Protocol) enhancements.
* ARP cache update fix.
* gPTP link delay calculation fixes.
* Changed how network data is passed from
  :ref:`L2 to network device driver <network_stack_architecture>`.
* Removed RPL (Ripple) IPv6 mesh routing support.
* MQTT is now available to threads running in user mode.
* Network device driver additions and enhancements:

  - Added Intel PRO/1000 Ethernet driver (e1000).
  - Added SMSC9118/LAN9118 Ethernet driver (smsc911x).
  - Added Inventek es-WiFi driver for disco_l475_iot1 board.
  - Added support for automatically enabling QEMU based Ethernet drivers.
  - SAM-E70 gmac Ethernet driver Qav fixes.
  - enc28j60 Ethernet driver fixes and enhancements.

Bluetooth
*********

* Host:

  * GATT: Added support for Robust Caching
  * GATT: L2CAP: User driven flow control
  * Many fixes to Mesh
  * Fixed & improved persistent storage handling
  * Fixed direct advertising support
  * Fixed security level 4 handling
  * Add option to configure peripheral connection parameters
  * Added support for updating advertising data without having to restart advertising
  * Added API to iterate through existing bonds
  * Added support for setting channel map
  * Converted SPI HCI driver to use device tree

* New BLE split software Controller (experimental):

  - Split design with Upper Link Layer and Lower Link Layer
  - Enabled with :option:`CONFIG_BT_LL_SW_SPLIT` (disabled by default)
  - Support for multiple BLE radio hardware architectures
  - Asynchronous handling of procedures in the ULL
  - Enhanced radio utilization (99% on continous 100ms scan)
  - Latency resilience: Approx 100uS vs 10uS, 10x improvement
  - CPU and power usage: About 20% improvement
  - Multiple advertiser and scanner instances
  - Support for both Big and Little-Endian architectures

* Controller:

  * Added support for setting the public address
  * Multiple control procedures fixes and improvements
  * Advertising random delay fixes
  * Fix a serious memory corruption issue during scanning
  * Fixes to RSSI measurement
  * Fixes to Connection Failed to be Established sequence
  * Transitioned to the new logging subsystem from syslog
  * Switched from -Ofast to -O2 in time-critical sections
  * Reworked the RNG/entropy driver to make it available to apps
  * Multiple size optimizations to make it fit in smaller devices
  * nRF: Rework the PPI channel assignment to use pre-assigned ones
  * Add extensive documentation to the shared primitives

* Several fixes for big endian architectures

Build and Infrastructure
************************

* Added support for out-of-tree architectures.
* Added support for out-of-tree implementations of in-tree drivers.
* `BabbleSim`_ has been integrated in Zephyr's CI system.
* Introduced ``DT_`` prefix for all labels generated for information extracted from
  device tree (with a few exceptions, like labels for LEDs and buttons, kept
  for backward compatibility with existing applications).
* Introduce CMake variables for DT symbols just as we have for CONFIG symbols.
* Move DeviceTree processing before Kconfig. Thereby allowing software
  to be configured based on DeviceTree information.
* Automatically change the KCONFIG_ROOT when the application directory
  has a Kconfig file.
* Added :ref:`west <west>` tool for multiple repository management
* Added support for :ref:`Zephyr modules <ext-projs>`
* Build system ``flash`` and ``debug`` targets now require west

Libraries / Subsystems
***********************

* Added a new display API and subsystem
* Added support for CTF Tracing
* Added support for JWT (JSON Web Tockens)
*
* Flash Maps:
  - API extension
  - Automatic generation of the list of flash areas

* Settings:
  - Enabled logging instead of ASSERTs
  - Always use the storage partition for FCB
  - fixed FCB backend and common bugs

* Logging:

  - Removed sys_log which has been replaced by the new logging subsystem
    introduced in v1.13
  - Refactored log modules registration macros
  - Improved synchronous operation (see :option:`CONFIG_LOG_IMMEDIATE`)
  - Added commands to control the logger using shell
  - Added :c:macro:`LOG_PANIC()` call to the fault handlers to ensure that logs
    are output on fault
  - Added mechanism for handling logging of transient strings. See
    :cpp:func:`log_strdup`
  - Added support for up to 15 arguments in the log message
  - Added optional function name prefix in the log message
  - Changed logging thread priority to the lowest application priority
  - Added notification about dropped log messages due to insufficent logger
    buffer size
  - Added log backends:

    - RTT
    - native_posix
    - net
    - SWO
    - Xtensa Sim
  - Changed default timestamp source function to :cpp:func:`k_uptime_get_32`

* Shell:

  - Added new implementation of the shell sub-system. See :ref:`shell_label`
  - Added shell backends:
    - UART
    - RTT
    - telnet

* Ring buffer:

  - Added byte mode
  - Added API to work directly on ring buffer memory to reduce memory copying
  - Removed ``sys_`` prefix from API functions

* MBEDTLS APIs may now be used from user mode.


HALs
****

* Updated Nordic nrfx to version 1.6.2
* Updated Nordic nrf ieee802154 radio driver to version 1.2.3
* Updated SimpleLink to TI CC32XX SDK 2.40.01.01
* Added Microchip MEC1701 Support
* Added Cypress PDL for PSoC6 SoC Support
* Updates to stm32cube, Silabs Gecko SDK, Atmel.
* Update ARM CMSIS headers to version 5.4.0


Documentation
*************

* Reorganized subsystem documentation into more meaningful collections
  and added or improved introductory material for each subsystem.
* Overhauled  Bluetooth documentation to split it into
  manageable units and included additional information, such as
  architecture and tooling.
* Added to and improved documentation on many minor subsystems and APIs
  including socket offloading, Ethernet management, LLDP networking,
  network architecture and overview, net shell, CoAP, network interface,
  network configuration library, DNS resolver, DHCPv4, DTS, flash_area,
  flash_mpa, NVS , settings and more.
* Introduced a new debugging guide that documents all the different
  variations of debug probes and host tools in
  one place, including which combinations are valid.
* Clarified and improved information about the west tool and its use.
* Improved development process documentation including how new features
  are proposed and tracked, and clarifying API lifecycle, issue and PR
  tagging requirements, contributing guidelines, doc guidelines,
  release process, and PR review process.
* Introduced a developer "fast" doc build option to eliminate
  the time needed to create the full kconfig option docs from a local
  doc build, saving five minutes for a full doc build.
* Made dramatic improvements to the doc build processing, bringing
  iterative local doc generation down from over two minutes to only a
  few seconds. This makes it much faster for doc developers to iteratively
  edit and test doc changes locally before submitting a PR.
* Added a new ``zephyr-file`` directive to link directly to files in the
  Git tree.
* Introduced simplified linking to doxygen-generated API reference
  material.
* Made board documentation consistent, enabling a board-image carousel
  on the zephyrproject.org home page.
* Reduced unnecessarily large images to improve page load times.
* Added CSS changes to improve API docs appearance and usability
* Made doc version selector more obvious, making it easier to select
  documentation for a specific release
* Added a friendlier and more graphic home page.

Tests and Samples
*****************

* A new set of, multinode, full system tests of the BT stack,
  based on `BabbleSim`_ have been added.
* Added unique identifiers to all tests and samples.
* Removed old footprint benchmarks
* Added tests for CMSIS RTOS API v2, BSD Sockets, CANBus, Settings, USB, Misc.
  drivers.
* Added benchmark applications for the scheduler and mbedTLS
* Added samples for the display subsystem, LVGL, Goofle IOT, Sockets, CMSIS RTOS
  API v2, Wifi, Shields, IPC subsystem and USB CDC ACM and USB HID.
* Add support for testing with Renode using sanitycheck


Issue Related Items
*******************

These GitHub issues were addressed since the previous 1.13.0 tagged
release:

.. comment  List derived from GitHub Issue query: ...
   * :github:`issuenumber` - issue title

* :github:`99999` - issue title
