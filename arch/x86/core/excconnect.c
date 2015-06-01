/* excconnect.c - VxMicro exception management support for IA-32 arch */

/*
 * Copyright (c) 2010-2014 Wind River Systems, Inc.
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
This module provides routines to manage exceptions (synchronous interrupts)
in VxMicro on the IA-32 architecture.

This module provides the public routine nanoCpuExcConnect().

INTERNAL
An exception is defined as a synchronous interrupt, i.e. an interrupt
asserted as a direct result of program execution as opposed to a
hardware device asserting an interrupt.

Many (but not all) exceptions are handled by an "exception stub" whose code
is generated by the system itself.  The stub performs various actions before
and after invoking the application (or operating system) specific exception
handler; for example, a thread or ISR context save is performed prior to
invoking the exception handler.

The IA-32 code that makes up a "full" exception stub is shown below.  A full
exception stub is one that pushes a dummy error code at the start of
exception processing.  Exception types where the processor automatically
pushes an error code when handling an exception utilize similar exception
stubs, however the first instruction is omitted.  The use of the dummy error
code means that _ExcEnt() and _ExcExit() do not have to worry about whether
an error code is present on the stack or not.


  0x00   pushl   $0			/@ push dummy error code @/
  Machine code:  0x68, 0x00, 0x00, 0x00, 0x00

  0x05   call    _ExcEnt		/@ inform kernel of exception @/
  Machine code:  0xe8, 0x00, 0x00, 0x00, 0x00

  0x0a   call    ExcHandler		/@ invoke exception handler @/
  Machine code: 0xe8, 0x00, 0x00, 0x00, 0x00

  /@ _ExcExit() will adjust the stack to discard the error code @/

  0x0f  jmp	   _ExcExit		/@ restore context context @/
  Machine code: 0xe9, 0x00, 0x00, 0x00, 0x00

NOTE: Be sure to update the arch specific definition of the _EXC_STUB_SIZE
macro to reflect the size of the full exception stub (as shown above).
The _EXC_STUB_SIZE macro is defined in arch/x86/include/nanok.h.
*/


#include <nanokernel.h>
#include <nanok.h>


void _NanoCpuExcConnectAtDpl(unsigned int vector,
			     void (*routine)(NANO_ESF * pEsf),
			     NANO_EXC_STUB pExcStubMem,
			     unsigned int dpl);

/*******************************************************************************
*
* nanoCpuExcConnect - connect a C routine to an exception
*
* This routine connects an exception handler coded in C to the specified
* interrupt vector.  An exception is defined as a synchronous interrupt, i.e.
* an interrupt asserted as a direct result of program execution as opposed
* to a hardware device asserting an interrupt.
*
* When the exception specified by <vector> is asserted, the current context
* is saved on the current stack, i.e. a switch to some other stack is not
* performed, followed by executing <routine> which has the following signature:
*
*    void (*routine) (NANO_ESF *pEsf)
*
* The <pExcStubMem> argument points to memory that the system can use to
* synthesize the exception stub that calls <routine>.  The memory need not be
* initialized, but must be persistent (i.e. it cannot be on the caller's stack).
* Declaring a global or static variable of type NANO_EXC_STUB will provide a
* suitable area of the proper size.
*
* The handler is connected via an interrupt-gate descriptor having a
* descriptor privilege level (DPL) equal to zero.
*
* RETURNS: N/A
*
* INTERNAL
* The function prototype for nanoCpuExcConnect() only exists in nanok.h,
* in other words, it's still considered private since the definitions for
* the NANO_ESF structures have not been completed.
*/

void nanoCpuExcConnect(unsigned int vector, /* interrupt vector: 0 to 255 on
					       IA-32 */
		       void (*routine)(NANO_ESF * pEsf),
		       NANO_EXC_STUB pExcStubMem)
{
	_NanoCpuExcConnectAtDpl(vector, routine, pExcStubMem, 0);
}

/*******************************************************************************
*
* _NanoCpuExcConnectAtDpl - connect a C routine to an exception
*
* This routine connects an exception handler coded in C to the specified
* interrupt vector.  An exception is defined as a synchronous interrupt, i.e.
* an interrupt asserted as a direct result of program execution as opposed
* to a hardware device asserting an interrupt.
*
* When the exception specified by <vector> is asserted, the current context
* is saved on the current stack, i.e. a switch to some other stack is not
* performed, followed by executing <routine> which has the following signature:
*
*    void (*routine) (NANO_ESF *pEsf)
*
* The <pExcStubMem> argument points to memory that the system can use to
* synthesize the exception stub that calls <routine>.  The memory need not be
* initialized, but must be persistent (i.e. it cannot be on the caller's stack).
* Declaring a global or static variable of type NANO_EXC_STUB will provide a
* suitable area of the proper size.
*
* The handler is connected via an interrupt-gate descriptor having the supplied
* descriptor privilege level (DPL).
*
* RETURNS: N/A
*
* INTERNAL
* The function prototype for nanoCpuExcConnect() only exists in nanok.h,
* in other words, it's still considered private since the definitions for
* the NANO_ESF structures have not been completed.
*/

void _NanoCpuExcConnectAtDpl(
	unsigned int vector, /* interrupt vector: 0 to 255 on IA-32 */
	void (*routine)(NANO_ESF * pEsf),
	NANO_EXC_STUB pExcStubMem,
	unsigned int dpl /* priv level for interrupt-gate descriptor */
	)
{
	extern void _ExcEnt(void);
	extern void _ExcExit(void);
	unsigned int offsetAdjust = 0;

#define STUB_PTR pExcStubMem

	/*
	 * The <vector> parameter must be less than IV_INTEL_RESERVED_END,
	 * however, explicit validation will not be performed in this primitive.
	 */

	/*
	 * If the specified <vector> represents an exception type where the CPU
	 * does not push an error code onto the stack, then generate a stub that
	 * pushes a dummy code.  This results in a single implementation of
	 * _ExcEnt
	 * and _ExcExit which expects an error code to be pushed onto the stack
	 * (along with the faulting CS:EIP and EFLAGS).
	 */

	if (((1 << vector) & _EXC_ERROR_CODE_FAULTS) == 0) {
		STUB_PTR[0] = IA32_PUSH_OPCODE;

		UNALIGNED_WRITE((unsigned int *)&STUB_PTR[1],
				(unsigned int)0 /* value of dummy error code */
				);

		offsetAdjust = 5;
	}

	/* generate code that invokes _ExcEnt() */

	STUB_PTR[offsetAdjust] = IA32_CALL_OPCODE;
	UNALIGNED_WRITE((unsigned int *)&STUB_PTR[1 + offsetAdjust],
			(unsigned int)&_ExcEnt -
				(unsigned int)&pExcStubMem[5 + offsetAdjust]);
	offsetAdjust += 5;

	/* generate code that invokes the exception handler  */

	STUB_PTR[offsetAdjust] = IA32_CALL_OPCODE;
	UNALIGNED_WRITE((unsigned int *)&STUB_PTR[1 + offsetAdjust],
			(unsigned int)routine -
				(unsigned int)&pExcStubMem[5 + offsetAdjust]);
	offsetAdjust += 5;

	/*
	 * generate code that invokes _ExcExit(); note that a jump is used,
	 * since _ExcExit() takes care of popping the error code and returning
	 * back to the context that triggered the exception
	 */

	STUB_PTR[offsetAdjust] = IA32_JMP_OPCODE;
	UNALIGNED_WRITE((unsigned int *)&STUB_PTR[1 + offsetAdjust],
			(unsigned int)&_ExcExit -
				(unsigned int)&pExcStubMem[5 + offsetAdjust]);


	/*
	 * There is no need to explicitly synchronize or flush the instruction
	 * cache due to the above code synthesis.  See the Intel 64 and IA-32
	 * Architectures Software Developer's Manual: Volume 3A: System
	 *Programming
	 * Guide; specifically the section titled "Self Modifying Code".
	 *
	 * Cache synchronization/flushing is not required for the i386 as it
	 * does not contain any on-chip I-cache; likewise, post-i486 processors
	 * invalidate the I-cache automatically.  An i486 requires the CPU
	 * to perform a 'jmp' instruction before executing the synthesized code;
	 * however, the call and return that follows meets this requirement.
	 */

	_IntVecSet(vector, (void (*)(void *))pExcStubMem, dpl);
}

