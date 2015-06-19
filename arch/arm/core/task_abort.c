/* task_abort.c - ARM Cortex-M _TaskAbort() routine */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1) Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3) Neither the name of Wind River Systems nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
DESCRIPTION
The ARM Cortex-M architecture provides its own _TaskAbort() to deal with
different CPU modes (handler vs thread) when a task aborts. When its entry
point returns or when it aborts itself, the CPU is in thread mode and must
call the equivalent of task_abort(<self>), but when in handler mode, the
CPU must queue a packet to K_swapper(), then exit handler mode to queue the
PendSV exception and cause the immediate context switch to K_swapper.
*/

#ifdef CONFIG_MICROKERNEL

#include <toolchain.h>
#include <sections.h>
#include <micro_private.h>
#include <nanok.h>
#include <microkernel.h>
#include <nanokernel.h>
#include <misc/__assert.h>

static struct k_args cmd_packet;

/*******************************************************************************
*
* _TaskAbort - abort the current task
*
* Possible reasons for a task aborting:
*
* - the task explicitly aborts itself by calling this routine
* - the task implicitly aborts by returning from its entry point
* - the task encounters a fatal exception
*
* RETURNS: N/A
*
* \NOMANUAL
*/

void _TaskAbort(void)
{
	const int taskAbortCode = 1;

	if (_ScbIsInThreadMode()) {
		_task_ioctl(_k_current_task->Ident, taskAbortCode);
	} else {
		cmd_packet.Comm = TSKOP;
		cmd_packet.Args.g1.task = _k_current_task->Ident;
		cmd_packet.Args.g1.opt = taskAbortCode;
		cmd_packet.alloc = false;
		_k_current_task->Args = &cmd_packet;
		nano_isr_stack_push(&_k_command_stack, (uint32_t) &cmd_packet);
		_ScbPendsvSet();
	}
}

#endif /* CONFIG_MICROKERNEL */
