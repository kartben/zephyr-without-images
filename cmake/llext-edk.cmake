# Copyright (c) 2024 Intel Corporation
# SPDX-License-Identifier: Apache-2.0

# This script generates a tarball containing all headers and flags necessary to
# build an llext extension. It does so by copying all headers accessible from
# INTERFACE_INCLUDE_DIRECTORIES and generating a Makefile.cflags file (and a
# cmake.cflags one) with all flags necessary to build the extension.
#
# The tarball can be extracted and used in the extension build system to include
# all necessary headers and flags. File paths are made relative to a few key
# directories (build/zephyr, zephyr base, west top dir and application source
# dir), to avoid leaking any information about the host system.
#
# The following arguments are expected:
# - llext_edk_name: Name of the extension, used to name the tarball and the
#   install directory variable for Makefile.
# - INTERFACE_INCLUDE_DIRECTORIES: List of include directories to copy headers
#   from. It should simply be the INTERFACE_INCLUDE_DIRECTORIES property of the
#   zephyr_interface target.
# - AUTOCONF_H: Name of the autoconf.h file, used to generate the imacros flag.
# - llext_edk_file: Output file name for the tarball.
# - LLEXT_CFLAGS: Additional flags to be added to the generated flags.
# - ZEPHYR_BASE: Path to the zephyr base directory.
# - WEST_TOPDIR: Path to the west top directory.
# - APPLICATION_SOURCE_DIR: Path to the application source directory.
# - PROJECT_BINARY_DIR: Path to the project binary build directory.

cmake_minimum_required(VERSION 3.20.0)

set(llext_edk ${PROJECT_BINARY_DIR}/${llext_edk_name})
set(llext_edk_inc ${llext_edk}/include)

string(REGEX REPLACE "[^a-zA-Z0-9]" "_" llext_edk_name_sane ${llext_edk_name})
string(TOUPPER ${llext_edk_name_sane} llext_edk_name_sane)
set(install_dir_var "${llext_edk_name_sane}_INSTALL_DIR")

cmake_path(CONVERT "${INTERFACE_INCLUDE_DIRECTORIES}" TO_CMAKE_PATH_LIST include_dirs)

set(autoconf_h_edk ${llext_edk_inc}/${AUTOCONF_H})
cmake_path(RELATIVE_PATH AUTOCONF_H BASE_DIRECTORY ${PROJECT_BINARY_DIR} OUTPUT_VARIABLE autoconf_h_rel)

list(APPEND all_flags_make
    "${LLEXT_CFLAGS} -imacros\$(${install_dir_var})/include/zephyr/${autoconf_h_rel}")
list(APPEND all_flags_cmake
    "${LLEXT_CFLAGS} -imacros\${CMAKE_CURRENT_LIST_DIR}/include/zephyr/${autoconf_h_rel}")

file(MAKE_DIRECTORY ${llext_edk_inc})
foreach(dir ${include_dirs})
    if (NOT EXISTS ${dir})
        continue()
    endif()
    cmake_path(IS_PREFIX PROJECT_BINARY_DIR ${dir} NORMALIZE to_prj_bindir)
    cmake_path(IS_PREFIX ZEPHYR_BASE ${dir} NORMALIZE to_zephyr_base)
    if("${WEST_TOPDIR}" STREQUAL "")
        set(to_west_topdir FALSE)
    else()
        cmake_path(IS_PREFIX WEST_TOPDIR ${dir} NORMALIZE to_west_topdir)
    endif()
    cmake_path(IS_PREFIX APPLICATION_SOURCE_DIR ${dir} NORMALIZE to_app_srcdir)

    # Overall idea is to place included files in the destination dir based on the source:
    # files coming from build/zephyr/generated will end up at
    # <install-dir>/include/zephyr/include/generated, files coming from zephyr base at
    # <install-dir>/include/zephyr/include, files from west top dir (for instance, hal modules),
    # at <install-dir>/include and application ones at <install-dir>/include/<application-dir>.
    # Finally, everything else (such as external libs not at any of those places) will end up
    # at <install-dir>/include/<full-path-to-external-include>, so we avoid any external lib
    # stepping at any other lib toes.
    if(to_prj_bindir)
        cmake_path(RELATIVE_PATH dir BASE_DIRECTORY ${PROJECT_BINARY_DIR} OUTPUT_VARIABLE dir_tmp)
        set(dest ${llext_edk_inc}/zephyr/${dir_tmp})
    elseif(to_zephyr_base)
        cmake_path(RELATIVE_PATH dir BASE_DIRECTORY ${ZEPHYR_BASE} OUTPUT_VARIABLE dir_tmp)
        set(dest ${llext_edk_inc}/zephyr/${dir_tmp})
    elseif(to_west_topdir)
        cmake_path(RELATIVE_PATH dir BASE_DIRECTORY ${WEST_TOPDIR} OUTPUT_VARIABLE dir_tmp)
        set(dest ${llext_edk_inc}/${dir_tmp})
    elseif(to_app_srcdir)
        cmake_path(GET APPLICATION_SOURCE_DIR FILENAME app_dir)
        cmake_path(RELATIVE_PATH dir BASE_DIRECTORY ${APPLICATION_SOURCE_DIR} OUTPUT_VARIABLE dir_tmp)
        set(dest ${llext_edk_inc}/${app_dir}/${dir_tmp})
    else()
        set(dest ${llext_edk_inc}/${dir})
    endif()

    # Use destination parent, as the last part of the source directory is copied as well
    cmake_path(GET dest PARENT_PATH dest_p)

    file(MAKE_DIRECTORY ${dest_p})
    file(COPY ${dir} DESTINATION ${dest_p} FILES_MATCHING PATTERN "*.h")

    cmake_path(RELATIVE_PATH dest BASE_DIRECTORY ${llext_edk} OUTPUT_VARIABLE dest_rel)
    list(APPEND all_flags_make "-I\$(${install_dir_var})/${dest_rel}")
    list(APPEND all_flags_cmake "-I\${CMAKE_CURRENT_LIST_DIR}/${dest_rel}")
endforeach()

list(JOIN all_flags_make " " all_flags_str)
file(WRITE ${llext_edk}/Makefile.cflags "LLEXT_CFLAGS = ${all_flags_str}")

file(WRITE ${llext_edk}/cmake.cflags "set(LLEXT_CFLAGS ${all_flags_cmake})")

file(ARCHIVE_CREATE
    OUTPUT ${llext_edk_file}
    PATHS ${llext_edk}
    FORMAT gnutar
    COMPRESSION XZ
)

file(REMOVE_RECURSE ${llext_edk})
