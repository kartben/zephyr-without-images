/* intconnect.c - interrupt management support for IA-32 arch */

/*
 * Copyright (c) 2010-2014 Wind River Systems, Inc.
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
 * DESCRIPTION
 * This module provides routines to manage asynchronous interrupts
 * on the IA-32 architecture.
 *
 * This module provides the public routine irq_connect(), the private
 * routine _IntVecSet(), and the support routines _IntVecAlloc(),
 * _IntVecMarkAllocated() and _IntVecMarkFree().
 *
 * INTERNAL
 * The _idt_base_address symbol is used to determine the base address of the
 * IDT.  (It is generated by the linker script, and doesn't correspond to an
 * actual global variable.)
 *
 * Interrupts are handled by an "interrupt stub" whose code is generated by the
 * system itself.  The stub performs various actions before and after invoking
 * the application (or operating system) specific interrupt handler; for
 * example, a thread context save is performed prior to invoking the interrupt
 * handler.
 *
 * The IA-32 code that makes up a "full" interrupt stub is shown below.  A full
 * interrupt stub is one that is associated with an interrupt vector that
 * requires a "beginning of interrupt" (BOI) callout and an "end of interrupt"
 * (EOI) callout (both of which require a parameter).
 *
 * 0x00   call    _IntEnt         /@ inform kernel of interrupt @/
 * Machine code:  0xe8, 0x00, 0x00, 0x00, 0x00
 *
 * 0x05   pushl   $BoiParameter   /@ optional: push BOI handler parameter @/
 * Machine code:  0x68, 0x00, 0x00, 0x00, 0x00
 *
 * 0x0a   call    BoiRoutine      /@ optional: callout to BOI rtn @/
 * Machine code:  0xe8, 0x00, 0x00, 0x00, 0x00
 *
 * 0x0f   pushl   $IsrParameter   /@ push ISR parameter @/
 * Machine code:  0x68, 0x00, 0x00, 0x00, 0x00
 *
 * 0x14   call    IsrRoutine      /@ invoke ISR @/
 * Machine code: 0xe8, 0x00, 0x00, 0x00, 0x00
 *
 * 0x19   pushl   $EoiParameter   /@ optional: push EOI handler parameter @/
 * Machine code: 0x68, 0x00, 0x00, 0x00, 0x00
 *
 * 0x1e   call    EoiRoutine      /@ optional: callout to EOI rtn @/
 * Machine code: 0xe8, 0x00, 0x00, 0x00, 0x00
 *
 * 0x23   addl    $(4 * numParams), %esp    /@ pop parameters @/
 * Machine code: 0x83, 0xc4, (4 * numParams)
 *
 * 0x26  jmp      _IntExit        /@ restore thread or reschedule @/
 * Machine code: 0xe9, 0x00, 0x00, 0x00, 0x00
 *
 * NOTE: Be sure to update the arch specific definition of the _INT_STUB_SIZE
 * macro to reflect the maximum potential size of the interrupt stub (as shown
 * above).
 * The _INT_STUB_SIZE macro is defined in include/nanokernel/x86/arch.h.
 */

#ifndef CONFIG_NO_ISRS

#include <nanokernel.h>
#include <arch/cpu.h>
#include <nano_private.h>
#include <misc/__assert.h>

/* the _idt_base_address symbol is generated via a linker script */

extern unsigned char _idt_base_address[];

extern void _SpuriousIntHandler(void *);
extern void _SpuriousIntNoErrCodeHandler(void *);

/*
 * These 'dummy' variables are used in nanoArchInit() to force the inclusion of
 * the spurious interrupt handlers. They *must* be declared in a module other
 * than the one they are used in to get around garbage collection issues and
 * warnings issued some compilers that they aren't used. Therefore care must
 * be taken if they are to be moved. See nano_private.h for more information.
 */
void *_dummy_spurious_interrupt;
void *_dummy_exception_vector_stub;

/*
 * Place the addresses of the spurious interrupt handlers into the intList
 * section. The genIdt tool can then populate any unused vectors with
 * these routines.
 */
void *__attribute__((section(".spurIsr"))) MK_ISR_NAME(_SpuriousIntHandler) =
	&_SpuriousIntHandler;
void *__attribute__((section(".spurNoErrIsr")))
	MK_ISR_NAME(_SpuriousIntNoErrCodeHandler) =
		&_SpuriousIntNoErrCodeHandler;

/*
 * Array of interrupt stubs for dynamic interrupt connection.
 */
#ifdef CONFIG_MICROKERNEL

#define ALL_DYNAMIC_STUBS (CONFIG_NUM_DYNAMIC_STUBS + CONFIG_MAX_NUM_TASK_IRQS)

#elif defined (CONFIG_NANOKERNEL)

#define ALL_DYNAMIC_STUBS (CONFIG_NUM_DYNAMIC_STUBS)

#endif

#if ALL_DYNAMIC_STUBS > 0

#define _STUB_AVAIL 0xff

static NANO_INT_STUB dynamic_stubs[ALL_DYNAMIC_STUBS] = {
	[0 ... (ALL_DYNAMIC_STUBS - 1)] = { _STUB_AVAIL, }
};

/**
 * @brief Allocate dynamic interrupt stub
 *
 * @return index of the first available element of the STUB array or -1
 *          if all elements are used
 */
static int _int_stub_alloc(void)
{
	int i;
	int rv = -1;
	unsigned int key;

	key = irq_lock();
	for (i = 0; i < ALL_DYNAMIC_STUBS &&
		     dynamic_stubs[i][0] != _STUB_AVAIL; i++) {
	}

	/* Mark the stub as allocated by using the CALL opcode */
	if (i != ALL_DYNAMIC_STUBS) {
		dynamic_stubs[i][0] = IA32_CALL_OPCODE;
		rv = i;
	}

	irq_unlock(key);
	return rv;
}
#endif /* ALL_DYNAMIC_STUBS > 0 */

/**
 *
 * @brief Connect a routine to an interrupt vector
 *
 * @param vector interrupt vector: 0 to 255 on IA-32
 * @param routine a function pointer to the interrupt routine
 * @param dpl priv level for interrupt-gate descriptor
 *
 * This routine "connects" the specified <routine> to the specified interrupt
 * <vector>.  On the IA-32 architecture, an interrupt vector is a value from
 * 0 to 255.  This routine merely fills in the appropriate interrupt
 * descriptor table (IDT) with an interrupt-gate descriptor such that <routine>
 * is invoked when interrupt <vector> is asserted.  The <dpl> argument specifies
 * the privilege level for the interrupt-gate descriptor; (hardware) interrupts
 * and exceptions should specify a level of 0, whereas handlers for user-mode
 * software generated interrupts should specify 3.
 *
 * @return N/A
 *
 * INTERNAL
 * Unlike nanoCpuExcConnect() and irq_connect(), the _IntVecSet() routine
 * is a very basic API that simply updates the appropriate entry in Interrupt
 * Descriptor Table (IDT) such that the specified routine is invoked when the
 * specified interrupt vector is asserted.
 *
 */

void _IntVecSet(unsigned int vector, void (*routine)(void *), unsigned int dpl)
{
	unsigned long long *pIdtEntry;
	unsigned int key;

	/*
	 * The <vector> parameter must be less than the value of the
	 * CONFIG_IDT_NUM_VECTORS configuration parameter, however,
	 * explicit validation will not be performed in this primitive.
	 */

	pIdtEntry = (unsigned long long *)(_idt_base_address + (vector << 3));

	/*
	 * Lock interrupts to protect the IDT entry to which _IdtEntryCreate()
	 * will write.  They must be locked here because the _IdtEntryCreate()
	 * code is shared with the 'gen_idt' host tool.
	 */

	key = irq_lock();
	_IdtEntCreate(pIdtEntry, routine, dpl);
	irq_unlock(key);

	/* not required to synchronize the instruction and data caches */
}

/*
 * Guard against situations when ALL_DYNAMIC_STUBS is left equal to 0,
 * but irq_connect is still used, which causes system failure.
 * If ALL_DYNAMIC_STUBS is left 0, but irq_connect is used, linker
 * generates an error
 */
#if ALL_DYNAMIC_STUBS > 0
/**
 *
 * @brief Connect a C routine to a hardware interrupt
 *
 * @param irq virtualized IRQ to connect to
 * @param priority requested priority of interrupt
 * @param routine the C interrupt handler
 * @param parameter parameter passed to C routine
 *
 * This routine connects an interrupt service routine (ISR) coded in C to
 * the specified hardware <irq>.  An interrupt vector will be allocated to
 * satisfy the specified <priority>.  If the interrupt service routine is being
 * connected to a software generated interrupt, then <irq> must be set to
 * NANO_SOFT_IRQ.
 *
 * The specified <irq> represents a virtualized IRQ, i.e. it does not
 * necessarily represent a specific IRQ line on a given interrupt controller
 * device.  The platform presents a virtualized set of IRQs from 0 to N, where
 * N is the total number of IRQs supported by all the interrupt controller
 * devices on the board.  See the platform's documentation for the mapping of
 * virtualized IRQ to physical IRQ.
 *
 * When the device asserts an interrupt on the specified <irq>, a switch to
 * the interrupt stack is performed (if not already executing on the interrupt
 * stack), followed by saving the integer (i.e. non-floating point) thread of
 * the currently executing task, fiber, or ISR.  The ISR specified by <routine>
 * will then be invoked with the single <parameter>.  When the ISR returns, a
 * context switch may occur.
 *
 * The routine searches for the first available element in the synamic_stubs
 * array and uses it for the stub.
 *
 * @return the allocated interrupt vector
 *
 * WARNINGS
 * Some boards utilize interrupt controllers where the interrupt vector
 * cannot be programmed on an IRQ basis; as a result, the vector assigned
 * to the <irq> during interrupt controller initialization will be returned.
 * In these cases, the requested <priority> is not honoured since the interrupt
 * prioritization is fixed by the interrupt controller (e.g. IRQ0 will always
 * be the highest priority interrupt regardless of what interrupt vector
 * was assigned to IRQ0).
 *
 * This routine does not perform range checking on the requested <priority>
 * and thus, depending on the underlying interrupt controller, may result
 * in the assignment of an interrupt vector located in the reserved range of
 * the processor.
 *
 * INTERNAL
 * For debug kernels, this routine shall return -1 when there are no
 * vectors remaining in the specified <priority> level.
 */

int irq_connect(unsigned int irq, unsigned int priority,
	void (*routine)(void *parameter), void *parameter)
{
	unsigned char offsetAdjust;
	unsigned char numParameters = 1; /* stub always pushes ISR parameter */

	extern void _IntEnt(void);
	extern void _IntExit(void);

	int vector;
	NANO_EOI_GET_FUNC boiRtn;
	NANO_EOI_GET_FUNC eoiRtn;
	void *boiRtnParm;
	void *eoiRtnParm;
	unsigned char boiParamRequired;
	unsigned char eoiParamRequired;
	int stub_idx;

	/*
	 * Invoke the interrupt controller routine _SysIntVecAlloc() which will:
	 *  a) allocate a vector satisfying the requested priority,
	 *  b) return EOI and BOI related information for stub code synthesis,
	 *and
	 *  c) program the underlying interrupt controller device such that
	 *     when <irq> is asserted, the allocated interrupt vector will be
	 *     presented to the CPU.
	 *
	 * The _SysIntVecAlloc() routine will use the "utility" routine
	 * _IntVecAlloc() provided in this module to scan the
	 * _interrupt_vectors_allocated[] array for a suitable vector.
	 */

	vector = _SysIntVecAlloc(irq,
				 priority,
				 &boiRtn,
				 &eoiRtn,
				 &boiRtnParm,
				 &eoiRtnParm,
				 &boiParamRequired,
				 &eoiParamRequired);

#if defined(DEBUG)
	/*
	 * The return value from _SysIntVecAlloc() will be -1 if an invalid
	 * <irq> or <priority> was specified, or if a vector could not be
	 * allocated to honour the requested priority (for the boards that can
	 * support programming the interrupt vector for each IRQ).
	 */

	if (vector == -1)
		return (-1);
#endif /* DEBUG */

	stub_idx = _int_stub_alloc();
	__ASSERT(stub_idx != -1, "No available interrupt stubs found");

#define STUB_PTR dynamic_stubs[stub_idx]

	/*
	 * A minimal interrupt stub code will be synthesized based on the
	 * values of <boiRtn>, <eoiRtn>, <boiRtnParm>, <eoiRtnParm>,
	 * <boiParamRequired>, and <eoiParamRequired>.  The invocation of
	 * _IntEnt() and _IntExit() will always be required.
	 *
	 * NOTE: The 'call' opcode for the call to _IntEnt() has already been
	 * written by _int_stub_alloc() to mark the stub as allocated.
	 */

	UNALIGNED_WRITE((unsigned int *)&STUB_PTR[1],
			(unsigned int)&_IntEnt - (unsigned int)&STUB_PTR[5]);

	offsetAdjust = 5;

	/* IsrParameter and IsrRoutine always required */

	STUB_PTR[offsetAdjust] = IA32_PUSH_OPCODE;
	UNALIGNED_WRITE((unsigned int *)&STUB_PTR[1 + offsetAdjust],
			(unsigned int)parameter);

	STUB_PTR[5 + offsetAdjust] = IA32_CALL_OPCODE;
	UNALIGNED_WRITE((unsigned int *)&STUB_PTR[6 + offsetAdjust],
			(unsigned int)routine -
				(unsigned int)&STUB_PTR[10 + offsetAdjust]);

	offsetAdjust += 10;

#ifdef CONFIG_EOI_HANDLER_SUPPORTED

	/* poke in the EOI related opcodes */

	if (eoiRtn == NULL)
		/* no need to insert anything */;
	else if (eoiParamRequired != 0) {
		STUB_PTR[offsetAdjust] = IA32_PUSH_OPCODE;
		UNALIGNED_WRITE((unsigned int *)&STUB_PTR[1 + offsetAdjust],
				(unsigned int)eoiRtnParm);

		STUB_PTR[5 + offsetAdjust] = IA32_CALL_OPCODE;
		UNALIGNED_WRITE(
			(unsigned int *)&STUB_PTR[6 + offsetAdjust],
			(unsigned int)eoiRtn -
				(unsigned int)&STUB_PTR[10 + offsetAdjust]);

		offsetAdjust += 10;
		++numParameters;
	} else {
		STUB_PTR[offsetAdjust] = IA32_CALL_OPCODE;
		UNALIGNED_WRITE(
			(unsigned int *)&STUB_PTR[1 + offsetAdjust],
			(unsigned int)eoiRtn -
				(unsigned int)&STUB_PTR[5 + offsetAdjust]);

		offsetAdjust += 5;
	}

#endif /* CONFIG_EOI_HANDLER_SUPPORTED */

	/*
	 * Poke in the stack popping related opcode. Do it a byte at a time
	 * because &STUB_PTR[offsetAdjust] may not be aligned which does not
	 * work for all targets.
	 */

	STUB_PTR[offsetAdjust] = IA32_ADD_OPCODE & 0xFF;
	STUB_PTR[1 + offsetAdjust] = IA32_ADD_OPCODE >> 8;
	STUB_PTR[2 + offsetAdjust] = (unsigned char)(4 * numParameters);

	offsetAdjust += 3;

	/*
	 * generate code that invokes _IntExit(); note that a jump is used,
	 * since _IntExit() takes care of returning back to the execution
	 * context that experienced the interrupt (i.e. branch tail
	 * optimization)
	 */

	STUB_PTR[offsetAdjust] = IA32_JMP_OPCODE;
	UNALIGNED_WRITE((unsigned int *)&STUB_PTR[1 + offsetAdjust],
			(unsigned int)&_IntExit -
				(unsigned int)&STUB_PTR[5 + offsetAdjust]);


	/*
	 * There is no need to explicitly synchronize or flush the instruction
	 * cache due to the above code synthesis.  See the Intel 64 and IA-32
	 * Architectures Software Developer's Manual: Volume 3A: System
	 * Programming Guide; specifically the section titled "Self Modifying
	 * Code".
	 *
	 * Cache synchronization/flushing is not required for the i386 as it
	 * does not contain any on-chip I-cache; likewise, post-i486 processors
	 * invalidate the I-cache automatically.  An i486 requires the CPU
	 * to perform a 'jmp' instruction before executing the synthesized code;
	 * however, the call and return that follows meets this requirement.
	 */

	_IntVecSet(vector, (void (*)(void *))STUB_PTR, 0);

	return vector;
}
#endif /* ALL_DYNAMIC_STUBS > 0 */

/**
 *
 * @brief Allocate a free interrupt vector given <priority>
 *
 * This routine scans the _interrupt_vectors_allocated[] array for a free vector
 * that satisfies the specified <priority>.  It is a utility function for use
 * only by the interrupt controller's _SysIntVecAlloc() routine.
 *
 * This routine assumes that the relationship between interrupt priority and
 * interrupt vector is :
 *
 *      priority = vector / 16;
 *
 * Since vectors 0 to 31 are reserved by the IA-32 architecture, the priorities
 * of user defined interrupts range from 2 to 15.  Each interrupt priority level
 * contains 16 vectors, and the prioritization of interrupts within a priority
 * level is determined by the vector number; the higher the vector number, the
 * higher the priority within that priority level.
 *
 * It is also assumed that the interrupt controllers are capable of managing
 * interrupt requests on a per-vector level as opposed to a per-priority level.
 * For example, the local APIC on Pentium4 and later processors, the in-service
 * register (ISR) and the interrupt request register (IRR) are 256 bits wide.
 *
 * @return allocated interrupt vector
 *
 * INTERNAL
 * For debug kernels, this routine shall return -1 when there are no
 * vectors remaining in the specified <priority> level.
 */

int _IntVecAlloc(unsigned int priority)
{
	unsigned int key;
	unsigned int entryToScan;
	unsigned int fsb; /* first set bit in entry */
	unsigned int search_set;
	int vector;

	static unsigned int mask[2] = {0x0000ffff, 0xffff0000};

#if defined(DEBUG)
	/*
	 * check whether the IDT was configured with sufficient vectors to
	 * satisfy the priority request.
	 */

	if (((priority << 4) + 15) > CONFIG_IDT_NUM_VECTORS)
		return (-1);
#endif /* DEBUG */

	/*
	 * Atomically allocate a vector from the _interrupt_vectors_allocated[]
	 * array to prevent race conditions with other tasks/fibers attempting
	 * to allocate an interrupt vector.
	 */

	entryToScan = priority >> 1;

	/*
	 * The _interrupt_vectors_allocated[] entry indexed by 'entryToScan' is a
	 * 32-bit quantity and thus represents the vectors for a pair of priority
	 * levels. Mask out the unwanted priority level and then use find_lsb_set()
	 * to scan for an available vector of the requested priority.
	 *
	 * Note that find_lsb_set() returns bit position from 1 to 32,
	 * or 0 if the argument is zero.
	 */

	key = irq_lock();

	search_set = mask[priority & 1] & _interrupt_vectors_allocated[entryToScan];
	fsb = find_lsb_set(search_set);

#if defined(DEBUG)
	if (fsb == 0) {
		/* All vectors for this priority have been allocated. */

		irq_unlock(key);
		return (-1);
	}
#endif /* DEBUG */

	/*
	 * An available vector of the requested priority was found.
	 * Mark it as allocated.
	 */

	--fsb;
	_interrupt_vectors_allocated[entryToScan] &= ~(1 << fsb);

	irq_unlock(key);

	/* compute vector given allocated bit within the priority level */

	vector = (entryToScan << 5) + fsb;

	return vector;
}

/**
 *
 * @brief Mark interrupt vector as allocated
 *
 * This routine is used to "reserve" an interrupt vector that is allocated
 * or assigned by any means other than _IntVecAllocate().  This marks the vector
 * as allocated so that any future invocations of _IntVecAllocate() will not
 * return that vector.
 *
 * @return N/A
 *
 */

void _IntVecMarkAllocated(unsigned int vector)
{
	unsigned int entryToSet = vector / 32;
	unsigned int bitToSet = vector % 32;
	unsigned int imask;

	imask = irq_lock();
	_interrupt_vectors_allocated[entryToSet] &= ~(1 << bitToSet);
	irq_unlock(imask);
}

/**
 *
 * @brief Mark interrupt vector as free
 *
 * This routine is used to "free" an interrupt vector that is allocated
 * or assigned using _IntVecAllocate() or _IntVecMarkAllocated(). This marks the
 * vector as available so that any future allocations can return that vector.
 *
 */

void _IntVecMarkFree(unsigned int vector)
{
	unsigned int entryToSet = vector / 32;
	unsigned int bitToSet = vector % 32;
	unsigned int imask;

	imask = irq_lock();
	_interrupt_vectors_allocated[entryToSet] |= (1 << bitToSet);
	irq_unlock(imask);
}

#endif /* CONFIG_NO_ISRS */
