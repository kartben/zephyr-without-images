# SPDX-License-Identifier: Apache-2.0

include_guard(GLOBAL)

include(extensions)
include(python)

# autoconf.h is generated by Kconfig and placed in
# <build>/zephyr/include/generated/autoconf.h.
# A project may request a custom location by setting AUTOCONF_H explicitly before
# calling 'find_package(Zephyr)' or loading this module.
set_ifndef(AUTOCONF_H ${PROJECT_BINARY_DIR}/include/generated/zephyr/autoconf.h)
# Re-configure (Re-execute all CMakeLists.txt code) when autoconf.h changes
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${AUTOCONF_H})

# Folders needed for conf/mconf files (kconfig has no method of redirecting all output files).
# conf/mconf needs to be run from a different directory because of: GH-3408
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/kconfig/include/generated)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/kconfig/include/config)

set_ifndef(KCONFIG_NAMESPACE "CONFIG")

set_ifndef(KCONFIG_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/Kconfig)
file(MAKE_DIRECTORY ${KCONFIG_BINARY_DIR})

if(HWMv1)
  # Support multiple SOC_ROOT
  file(MAKE_DIRECTORY ${KCONFIG_BINARY_DIR}/soc)
  set(kconfig_soc_root ${BOARD_ROOT})
  list(REMOVE_ITEM kconfig_soc_root ${ZEPHYR_BASE})
  set(soc_defconfig_file ${KCONFIG_BINARY_DIR}/soc/Kconfig.defconfig)

  set(OPERATION WRITE)
  foreach(root ${kconfig_soc_root})
    file(APPEND ${soc_defconfig_file}
         "osource \"${root}/soc/$(ARCH)/*/Kconfig.defconfig\"\n")
    file(${OPERATION} ${KCONFIG_BINARY_DIR}/soc/Kconfig.soc.choice
         "osource \"${root}/soc/$(ARCH)/*/Kconfig.soc\"\n"
    )
    file(${OPERATION} ${KCONFIG_BINARY_DIR}/soc/Kconfig.soc.arch
         "osource \"${root}/soc/$(ARCH)/Kconfig\"\n"
         "osource \"${root}/soc/$(ARCH)/*/Kconfig\"\n"
    )
    set(OPERATION APPEND)
  endforeach()
endif()

# Support multiple shields in BOARD_ROOT, remove ZEPHYR_BASE as that is always sourced.
set(kconfig_board_root ${BOARD_ROOT})
list(REMOVE_ITEM kconfig_board_root ${ZEPHYR_BASE})
set(OPERATION WRITE)
foreach(root ${kconfig_board_root})
  file(${OPERATION} ${KCONFIG_BINARY_DIR}/Kconfig.shield.defconfig
       "osource \"${root}/boards/shields/*/Kconfig.defconfig\"\n"
  )
  file(${OPERATION} ${KCONFIG_BINARY_DIR}/Kconfig.shield
       "osource \"${root}/boards/shields/*/Kconfig.shield\"\n"
  )
  set(OPERATION APPEND)
endforeach()

if(KCONFIG_ROOT)
  # Perform any variable substitutions if they are present
  string(CONFIGURE "${KCONFIG_ROOT}" KCONFIG_ROOT)

  zephyr_file(APPLICATION_ROOT KCONFIG_ROOT)
  # KCONFIG_ROOT has either been specified as a CMake variable or is
  # already in the CMakeCache.txt. This has precedence.
elseif(EXISTS   ${APPLICATION_SOURCE_DIR}/Kconfig)
  set(KCONFIG_ROOT ${APPLICATION_SOURCE_DIR}/Kconfig)
else()
  set(KCONFIG_ROOT ${ZEPHYR_BASE}/Kconfig)
endif()

if(NOT DEFINED BOARD_DEFCONFIG)
  zephyr_file(CONF_FILES ${BOARD_DIR} DEFCONFIG BOARD_DEFCONFIG)
endif()

if(DEFINED BOARD_REVISION)
  zephyr_build_string(config_board_string
                      BOARD ${BOARD}
                      BOARD_QUALIFIERS ${BOARD_QUALIFIERS}
                      BOARD_REVISION ${BOARD_REVISION}
  )
  set(board_rev_file ${config_board_string})
  if(EXISTS ${BOARD_DIR}/${board_rev_file}.conf)
    message(DEPRECATION "Use of '${board_rev_file}.conf' is deprecated, please switch to '${board_rev_file}_defconfig'")
    set_ifndef(BOARD_REVISION_CONFIG ${BOARD_DIR}/${board_rev_file}.conf)
  endif()
endif()

set(DOTCONFIG                  ${PROJECT_BINARY_DIR}/.config)
set(PARSED_KCONFIG_SOURCES_TXT ${PROJECT_BINARY_DIR}/kconfig/sources.txt)

if(CONF_FILE)
  string(CONFIGURE "${CONF_FILE}" CONF_FILE_EXPANDED)
  string(REPLACE " " ";" CONF_FILE_AS_LIST "${CONF_FILE_EXPANDED}")
endif()

if(EXTRA_CONF_FILE)
  string(CONFIGURE "${EXTRA_CONF_FILE}" EXTRA_CONF_FILE_EXPANDED)
  string(REPLACE " " ";" EXTRA_CONF_FILE_AS_LIST "${EXTRA_CONF_FILE_EXPANDED}")
endif()

zephyr_file(CONF_FILES ${BOARD_EXTENSION_DIRS} KCONF board_extension_conf_files SUFFIX ${FILE_SUFFIX})

# DTS_ROOT_BINDINGS is a semicolon separated list, this causes
# problems when invoking kconfig_target since semicolon is a special
# character in the C shell, so we make it into a question-mark
# separated list instead.
string(REPLACE ";" "?" DTS_ROOT_BINDINGS "${DTS_ROOT_BINDINGS}")

# Export each `ZEPHYR_<module>_MODULE_DIR` to Kconfig.
# This allows Kconfig files to refer relative from a modules root as:
# source "$(ZEPHYR_FOO_MODULE_DIR)/Kconfig"
foreach(module_name ${ZEPHYR_MODULE_NAMES})
  zephyr_string(SANITIZE TOUPPER MODULE_NAME_UPPER ${module_name})
  list(APPEND
       ZEPHYR_KCONFIG_MODULES_DIR
       "ZEPHYR_${MODULE_NAME_UPPER}_MODULE_DIR=${ZEPHYR_${MODULE_NAME_UPPER}_MODULE_DIR}"
  )

  if(ZEPHYR_${MODULE_NAME_UPPER}_KCONFIG)
    list(APPEND
         ZEPHYR_KCONFIG_MODULES_DIR
         "ZEPHYR_${MODULE_NAME_UPPER}_KCONFIG=${ZEPHYR_${MODULE_NAME_UPPER}_KCONFIG}"
  )
  endif()
endforeach()

# A list of common environment settings used when invoking Kconfig during CMake
# configure time or menuconfig and related build target.
string(REPLACE ";" "\\\;" SHIELD_AS_LIST_ESCAPED "${SHIELD_AS_LIST}")
# cmake commands are escaped differently
string(REPLACE ";" "\\;" SHIELD_AS_LIST_ESCAPED_COMMAND "${SHIELD_AS_LIST}")

if(TOOLCHAIN_HAS_NEWLIB)
  set(_local_TOOLCHAIN_HAS_NEWLIB y)
else()
  set(_local_TOOLCHAIN_HAS_NEWLIB n)
endif()

if(TOOLCHAIN_HAS_PICOLIBC)
  set(_local_TOOLCHAIN_HAS_PICOLIBC y)
else()
  set(_local_TOOLCHAIN_HAS_PICOLIBC n)
endif()

set(COMMON_KCONFIG_ENV_SETTINGS
  PYTHON_EXECUTABLE=${PYTHON_EXECUTABLE}
  srctree=${ZEPHYR_BASE}
  KERNELVERSION=${KERNELVERSION}
  APPVERSION=${APP_VERSION_STRING}
  APP_VERSION_EXTENDED_STRING=${APP_VERSION_EXTENDED_STRING}
  APP_VERSION_TWEAK_STRING=${APP_VERSION_TWEAK_STRING}
  CONFIG_=${KCONFIG_NAMESPACE}_
  KCONFIG_CONFIG=${DOTCONFIG}
  BOARD_DIR=${BOARD_DIR}
  BOARD=${BOARD}
  BOARD_REVISION=${BOARD_REVISION}
  BOARD_QUALIFIERS=${BOARD_QUALIFIERS}
  HWM_SCHEME=${HWM}
  KCONFIG_BINARY_DIR=${KCONFIG_BINARY_DIR}
  APPLICATION_SOURCE_DIR=${APPLICATION_SOURCE_DIR}
  ZEPHYR_TOOLCHAIN_VARIANT=${ZEPHYR_TOOLCHAIN_VARIANT}
  TOOLCHAIN_KCONFIG_DIR=${TOOLCHAIN_KCONFIG_DIR}
  TOOLCHAIN_HAS_NEWLIB=${_local_TOOLCHAIN_HAS_NEWLIB}
  TOOLCHAIN_HAS_PICOLIBC=${_local_TOOLCHAIN_HAS_PICOLIBC}
  EDT_PICKLE=${EDT_PICKLE}
  # Export all Zephyr modules to Kconfig
  ${ZEPHYR_KCONFIG_MODULES_DIR}
)

if(HWMv1)
  list(APPEND COMMON_KCONFIG_ENV_SETTINGS
    ARCH=${ARCH}
    ARCH_DIR=${ARCH_DIR}
  )
else()
  # For HWMv2 we should in future generate a Kconfig.arch.v2 which instead
  # glob-sources all arch roots, but for Zephyr itself, the current approach is
  # sufficient.
  list(APPEND COMMON_KCONFIG_ENV_SETTINGS
    ARCH=*
    ARCH_DIR=${ZEPHYR_BASE}/arch
  )
endif()

# Allow out-of-tree users to add their own Kconfig python frontend
# targets by appending targets to the CMake list
# 'EXTRA_KCONFIG_TARGETS' and setting variables named
# 'EXTRA_KCONFIG_TARGET_COMMAND_FOR_<target>'
#
# e.g.
# cmake -DEXTRA_KCONFIG_TARGETS=cli
# -DEXTRA_KCONFIG_TARGET_COMMAND_FOR_cli=cli_kconfig_frontend.py

set(EXTRA_KCONFIG_TARGET_COMMAND_FOR_menuconfig
  ${ZEPHYR_BASE}/scripts/kconfig/menuconfig.py
  )

set(EXTRA_KCONFIG_TARGET_COMMAND_FOR_guiconfig
  ${ZEPHYR_BASE}/scripts/kconfig/guiconfig.py
  )

set(EXTRA_KCONFIG_TARGET_COMMAND_FOR_hardenconfig
  ${ZEPHYR_BASE}/scripts/kconfig/hardenconfig.py
  )

set_ifndef(KCONFIG_TARGETS menuconfig guiconfig hardenconfig)

foreach(kconfig_target
    ${KCONFIG_TARGETS}
    ${EXTRA_KCONFIG_TARGETS}
    )
  add_custom_target(
    ${kconfig_target}
    ${CMAKE_COMMAND} -E env
    ZEPHYR_BASE=${ZEPHYR_BASE}
    ${COMMON_KCONFIG_ENV_SETTINGS}
    "SHIELD_AS_LIST=${SHIELD_AS_LIST_ESCAPED}"
    DTS_POST_CPP=${DTS_POST_CPP}
    DTS_ROOT_BINDINGS=${DTS_ROOT_BINDINGS}
    ${PYTHON_EXECUTABLE}
    ${EXTRA_KCONFIG_TARGET_COMMAND_FOR_${kconfig_target}}
    ${KCONFIG_ROOT}
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/kconfig
    USES_TERMINAL
    COMMAND_EXPAND_LISTS
    )
endforeach()

# Support assigning Kconfig symbols on the command-line with CMake
# cache variables prefixed according to the Kconfig namespace.
# This feature is experimental and undocumented until it has undergone more
# user-testing.
unset(EXTRA_KCONFIG_OPTIONS)
if(SYSBUILD)
  get_property(sysbuild_variable_names TARGET sysbuild_cache PROPERTY "SYSBUILD_CACHE:VARIABLES")
  zephyr_get(SYSBUILD_MAIN_APP)
  zephyr_get(SYSBUILD_NAME)

  foreach (name ${sysbuild_variable_names})
    if("${name}" MATCHES "^${SYSBUILD_NAME}_${KCONFIG_NAMESPACE}_")
      string(REGEX REPLACE "^${SYSBUILD_NAME}_" "" org_name ${name})
      get_property(${org_name} TARGET sysbuild_cache PROPERTY ${name})
      list(APPEND cache_variable_names ${org_name})
    elseif(SYSBUILD_MAIN_APP AND "${name}" MATCHES "^${KCONFIG_NAMESPACE}_")
      get_property(${name} TARGET sysbuild_cache PROPERTY ${name})
      list(APPEND cache_variable_names ${name})
    endif()
  endforeach()
else()
  get_cmake_property(cache_variable_names CACHE_VARIABLES)
  list(FILTER cache_variable_names INCLUDE REGEX "^(CLI_)?${KCONFIG_NAMESPACE}_")
  list(TRANSFORM cache_variable_names REPLACE "^CLI_" "")
  list(REMOVE_DUPLICATES cache_variable_names)
endif()

# Sorting the variable names will make checksum calculation more stable.
list(SORT cache_variable_names)
foreach (name ${cache_variable_names})
  if(DEFINED ${name})
    # When a cache variable starts with the 'KCONFIG_NAMESPACE' value, it is
    # assumed to be a Kconfig symbol assignment from the CMake command line.
    set(EXTRA_KCONFIG_OPTIONS
      "${EXTRA_KCONFIG_OPTIONS}\n${name}=${${name}}"
      )
    set(CLI_${name} "${${name}}")
    list(APPEND cli_config_list ${name})
  elseif(DEFINED CLI_${name})
    # An additional 'CLI_' prefix means that the value was set by the user in
    # an earlier invocation. Append it to extra config only if no new value was
    # assigned above.
    set(EXTRA_KCONFIG_OPTIONS
      "${EXTRA_KCONFIG_OPTIONS}\n${name}=${CLI_${name}}"
      )
  endif()
endforeach()

if(EXTRA_KCONFIG_OPTIONS)
  set(EXTRA_KCONFIG_OPTIONS_FILE ${PROJECT_BINARY_DIR}/misc/generated/extra_kconfig_options.conf)
  file(WRITE
    ${EXTRA_KCONFIG_OPTIONS_FILE}
    ${EXTRA_KCONFIG_OPTIONS}
    )
endif()

# Bring in extra configuration files dropped in by the user or anyone else;
# make sure they are set at the end so we can override any other setting
file(GLOB config_files ${APPLICATION_BINARY_DIR}/*.conf)
list(SORT config_files)
set(
  merge_config_files
  ${BOARD_DEFCONFIG}
  ${BOARD_REVISION_CONFIG}
  ${board_extension_conf_files}
  ${CONF_FILE_AS_LIST}
  ${shield_conf_files}
  ${EXTRA_CONF_FILE_AS_LIST}
  ${EXTRA_KCONFIG_OPTIONS_FILE}
  ${config_files}
)

# Create a list of absolute paths to the .config sources from
# merge_config_files, which is a mix of absolute and relative paths.
set(merge_config_files_with_absolute_paths "")
foreach(f ${merge_config_files})
  if(IS_ABSOLUTE ${f})
    set(path ${f})
  else()
    set(path ${APPLICATION_CONFIG_DIR}/${f})
  endif()

  list(APPEND merge_config_files_with_absolute_paths ${path})
endforeach()
set(merge_config_files ${merge_config_files_with_absolute_paths})

foreach(f ${merge_config_files})
  if(NOT EXISTS ${f} OR IS_DIRECTORY ${f})
    message(FATAL_ERROR "File not found: ${f}")
  endif()
endforeach()

# Calculate a checksum of merge_config_files to determine if we need
# to re-generate .config
set(merge_config_files_checksum "")
foreach(f ${merge_config_files})
  file(MD5 ${f} checksum)
  set(merge_config_files_checksum "${merge_config_files_checksum}${checksum}")
endforeach()

# Create a new .config if it does not exists, or if the checksum of
# the dependencies has changed
set(merge_config_files_checksum_file ${PROJECT_BINARY_DIR}/.cmake.dotconfig.checksum)
set(CREATE_NEW_DOTCONFIG 1)
# Check if the checksum file exists too before trying to open it, though it
# should under normal circumstances
if(EXISTS ${DOTCONFIG} AND EXISTS ${merge_config_files_checksum_file})
  # Read out what the checksum was previously
  file(READ
    ${merge_config_files_checksum_file}
    merge_config_files_checksum_prev
    )
  if(
      ${merge_config_files_checksum} STREQUAL
      ${merge_config_files_checksum_prev}
      )
    # Checksum is the same as before
    set(CREATE_NEW_DOTCONFIG 0)
  endif()
endif()

if(CREATE_NEW_DOTCONFIG)
  set(input_configs_flags --handwritten-input-configs)
  set(input_configs ${merge_config_files} ${FORCED_CONF_FILE})
else()
  set(input_configs ${DOTCONFIG} ${FORCED_CONF_FILE})
endif()

if(DEFINED FORCED_CONF_FILE)
  list(APPEND input_configs_flags --forced-input-configs)
endif()

cmake_path(GET AUTOCONF_H PARENT_PATH autoconf_h_path)
if(NOT EXISTS ${autoconf_h_path})
  file(MAKE_DIRECTORY ${autoconf_h_path})
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E env
  ${COMMON_KCONFIG_ENV_SETTINGS}
  SHIELD_AS_LIST=${SHIELD_AS_LIST_ESCAPED_COMMAND}
  ${PYTHON_EXECUTABLE}
  ${ZEPHYR_BASE}/scripts/kconfig/kconfig.py
  --zephyr-base=${ZEPHYR_BASE}
  ${input_configs_flags}
  ${KCONFIG_ROOT}
  ${DOTCONFIG}
  ${AUTOCONF_H}
  ${PARSED_KCONFIG_SOURCES_TXT}
  ${input_configs}
  WORKING_DIRECTORY ${APPLICATION_SOURCE_DIR}
  # The working directory is set to the app dir such that the user
  # can use relative paths in CONF_FILE, e.g. CONF_FILE=nrf5.conf
  RESULT_VARIABLE ret
  )
if(NOT "${ret}" STREQUAL "0")
  message(FATAL_ERROR "command failed with return code: ${ret}")
endif()

if(CREATE_NEW_DOTCONFIG)
  # Write the new configuration fragment checksum. Only do this if kconfig.py
  # succeeds, to avoid marking zephyr/.config as up-to-date when it hasn't been
  # regenerated.
  file(WRITE ${merge_config_files_checksum_file}
             ${merge_config_files_checksum})
endif()

# Read out the list of 'Kconfig' sources that were used by the engine.
file(STRINGS ${PARSED_KCONFIG_SOURCES_TXT} PARSED_KCONFIG_SOURCES_LIST ENCODING UTF-8)

# Force CMAKE configure when the Kconfig sources or configuration files changes.
foreach(kconfig_input
    ${merge_config_files}
    ${DOTCONFIG}
    ${PARSED_KCONFIG_SOURCES_LIST}
    )
  set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${kconfig_input})
endforeach()

add_custom_target(config-twister DEPENDS ${DOTCONFIG})

# Remove the CLI Kconfig symbols from the namespace and
# CMakeCache.txt. If the symbols end up in DOTCONFIG they will be
# re-introduced to the namespace through 'import_kconfig'.
foreach (name ${cli_config_list})
  unset(${name})
  unset(${name} CACHE)
endforeach()

# Before importing the symbol values from DOTCONFIG, process the CLI values by
# re-importing them from EXTRA_KCONFIG_OPTIONS_FILE. Later, we want to compare
# the values from both files, and 'import_kconfig' will make this easier.
if(EXTRA_KCONFIG_OPTIONS_FILE)
  import_kconfig(${KCONFIG_NAMESPACE} ${EXTRA_KCONFIG_OPTIONS_FILE})
  foreach (name ${cache_variable_names})
    if(DEFINED ${name})
      set(temp_${name} "${${name}}")
      unset(${name})
    endif()
  endforeach()
endif()

# Import the .config file and make all settings available in CMake processing.
import_kconfig(${KCONFIG_NAMESPACE} ${DOTCONFIG})

# Cache the CLI Kconfig symbols that survived through Kconfig, prefixed with CLI_.
# Remove those who might have changed compared to earlier runs, if they no longer appears.
foreach (name ${cache_variable_names})
  # Note: "${CLI_${name}}" is the verbatim value of ${name} from command-line,
  # while "${temp_${name}}" is the same value processed by 'import_kconfig'.
  if(((NOT DEFINED ${name}) AND (NOT DEFINED temp_${name})) OR
     ((DEFINED ${name}) AND (DEFINED temp_${name}) AND (${name} STREQUAL temp_${name})))
    set(CLI_${name} ${CLI_${name}} CACHE INTERNAL "")
  else()
    unset(CLI_${name} CACHE)
  endif()
  unset(temp_${name})
endforeach()
