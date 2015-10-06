/* start_task.h - Intel nanokernel declarations to start a task */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
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
DESCRIPTION
Intel-specific parts of start_task(). Only FP functionality currently.
 */

#ifndef _START_TASK_ARCH__H_
#define _START_TASK_ARCH__H_

#include <toolchain.h>
#include <sections.h>

#include <micro_private.h>
#include <nano_private.h>
#include <microkernel/task.h>

extern void _StartTaskArch(struct k_task *, unsigned int *);

#define _START_TASK_ARCH(task, opt_ptr) _StartTaskArch(task, opt_ptr)

#endif /* _START_TASK_ARCH__H_ */
