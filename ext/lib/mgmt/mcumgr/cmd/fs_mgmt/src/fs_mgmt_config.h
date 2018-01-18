/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef H_FS_MGMT_CONFIG_
#define H_FS_MGMT_CONFIG_

#if defined MYNEWT

#include "syscfg/syscfg.h"

#define FS_MGMT_DL_CHUNK_SIZE   MYNEWT_VAL(FS_MGMT_DL_CHUNK_SIZE)
#define FS_MGMT_PATH_SIZE       MYNEWT_VAL(FS_MGMT_PATH_SIZE)
#define FS_MGMT_UL_CHUNK_SIZE   MYNEWT_VAL(FS_MGMT_UL_CHUNK_SIZE)

#elif defined __ZEPHYR__

#define FS_MGMT_DL_CHUNK_SIZE   CONFIG_FS_MGMT_DL_CHUNK_SIZE
#define FS_MGMT_PATH_SIZE       CONFIG_FS_MGMT_PATH_SIZE
#define FS_MGMT_UL_CHUNK_SIZE   CONFIG_FS_MGMT_UL_CHUNK_SIZE

#else

/* No direct support for this OS.  The application needs to define the above
 * settings itself.
 */

#endif

#endif
