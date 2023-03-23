/*
 * Copyright (c) 2023 Yonatan Schachter
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/bindesc.h>

#if IS_ENABLED(CONFIG_BINDESC_HOST_NAME)
BINDESC_STR_DEFINE(host_name, BINDESC_ID_HOST_NAME, HOST_NAME);
#endif /* IS_ENABLED(CONFIG_BINDESC_HOST_NAME) */

#if IS_ENABLED(CONFIG_BINDESC_C_COMPILER_NAME)
BINDESC_STR_DEFINE(c_compiler_name, BINDESC_ID_C_COMPILER_NAME, C_COMPILER_NAME);
#endif /* IS_ENABLED(CONFIG_BINDESC_C_COMPILER_NAME) */

#if IS_ENABLED(CONFIG_BINDESC_C_COMPILER_VERSION)
BINDESC_STR_DEFINE(c_compiler_version, BINDESC_ID_C_COMPILER_VERSION, C_COMPILER_VERSION);
#endif /* IS_ENABLED(CONFIG_BINDESC_C_COMPILER_VERSION) */

#if IS_ENABLED(CONFIG_BINDESC_CXX_COMPILER_NAME)
BINDESC_STR_DEFINE(cxx_compiler_name, BINDESC_ID_CXX_COMPILER_NAME, CXX_COMPILER_NAME);
#endif /* IS_ENABLED(CONFIG_BINDESC_CXX_COMPILER_NAME) */

#if IS_ENABLED(CONFIG_BINDESC_CXX_COMPILER_VERSION)
BINDESC_STR_DEFINE(cxx_compiler_version, BINDESC_ID_CXX_COMPILER_VERSION,
			CXX_COMPILER_VERSION);
#endif /* IS_ENABLED(CONFIG_BINDESC_CXX_COMPILER_VERSION) */
