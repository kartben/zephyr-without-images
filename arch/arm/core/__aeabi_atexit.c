/*
 * Copyright (c) 2016 Wind River Systems, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * @file
 * @brief Basic C++ destructor module for globals for ARM
 */

#include <toolchain.h>

EXTERN_C int __cxa_atexit(void (*destructor)(void *), void *objptr, void *dso);

/**
 * @brief Register destructor for a global object
 *
 * @param objptr global object pointer
 * @param destructor the global object destructor function
 * @param dso Dynamic Shared Object handle for shared libraries
 *
 * Wrapper for __cxa_atexit()
 */
int __aeabi_atexit(void *objptr, void (*destructor)(void *), void *dso)
{
	return __cxa_atexit(destructor, objptr, dso);
}
