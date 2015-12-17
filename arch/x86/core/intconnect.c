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

/**
 * @file
 * @brief Interrupt management support for IA-32 arch
 *
 * This module provides routines to manage asynchronous interrupts
 * on the IA-32 architecture.
 *
 * This module provides the public routine irq_connect(), the private
 * routine _IntVecSet(), and the support routines _IntVecAlloc(),
 * _IntVecMarkAllocated() and _IntVecMarkFree().
 *
 * INTERNAL
 * The _idt_base_address symbol is used to determine the base address of the IDT.
 * (It is generated by the linker script, and doesn't correspond to an actual
 * global variable.)
 *
 * Dynamic interrupts are handled by a set of dynamic interrupt stubs defined
 * in intstub.S. Each one pushes a "stub id" onto the stack and calls
 * common_dynamic_handler, which uses the stub id to pull the details
 * about what to do with the dynamic IRQ out of the dyn_irq_list array.
 * This array is populated by calls to irq_connect(), which also installs
 * the associated dynamic stub in the IDT.
 */


#include <nanokernel.h>
#include <arch/cpu.h>
#include <nano_private.h>
#include <misc/__assert.h>
#include <idtEnt.h>

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

#ifdef CONFIG_MVIC
	/* Some nonstandard interrupt controllers may be doing some IDT
	 * caching for performance reasons and need the IDT reloaded if
	 * any changes are made to it
	 */
	__asm__ volatile ("lidt _Idt");
#endif

	irq_unlock(key);
}

/*
 * Guard against situations when ALL_DYN_IRQ_STUBS is left equal to 0,
 * but irq_connect is still used, which causes system failure.
 * If ALL_DYN_IRQ_STUBS is left 0, but irq_connect is used, linker
 * generates an error
 */
#if ALL_DYN_IRQ_STUBS > 0
struct dyn_irq_info {
	/** IRQ handler */
	void (*handler)(void *param);
	/** Parameter to pass to the handler */
	void *param;
};

/*
 * Instead of creating a large sparse table mapping all possible IDT vectors
 * to dyn_irq_info, the dynamic stubs push a "stub id" onto the stack
 * which is used by common_dynamic_handler() to fetch the appropriate
 * information out of this much smaller table
 */
static struct dyn_irq_info dyn_irq_list[ALL_DYN_IRQ_STUBS];
static unsigned int next_irq_stub;

/* Memory address pointing to where in ROM the code for the dynamic stubs are */
extern void *_DynIntStubsBegin;

/**
 *
 * @brief Connect a C routine to a hardware interrupt
 *
 * @param irq virtualized IRQ to connect to
 * @param priority requested priority of interrupt
 * @param routine the C interrupt handler
 * @param parameter parameter passed to C routine
 * @param flags IRQ flags
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
 * On some platforms <flags> parameter needs to be specified to indicate if
 * the irq is triggered by low or high level or by rising or falling edge.
 *
 * The routine searches for the first available element in the dynamic_stubs
 * array and uses it for the stub.
 *
 * @return the allocated interrupt vector
 *
 * WARNINGS
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
		void (*routine)(void *parameter), void *parameter,
		uint32_t flags)
{
	int vector;
	int stub_idx;

	/*
	 * Invoke the interrupt controller routine _SysIntVecAlloc() which will:
	 *  a) allocate a vector satisfying the requested priority,
	 *  b) create a new entry in the dynamic stub array
	 *  c) program the underlying interrupt controller device such that
	 *     when <irq> is asserted, the allocated interrupt vector will be
	 *     presented to the CPU.
	 *
	 * The _SysIntVecAlloc() routine will use the "utility" routine
	 * _IntVecAlloc() provided in this module to scan the
	 * _interrupt_vectors_allocated[] array for a suitable vector.
	 */

	vector = _SysIntVecAlloc(irq, priority, flags);
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

	stub_idx = _stub_alloc(&next_irq_stub, ALL_DYN_IRQ_STUBS);
	__ASSERT(stub_idx != -1, "No available interrupt stubs found");

	dyn_irq_list[stub_idx].handler = routine;
	dyn_irq_list[stub_idx].param = parameter;
	_IntVecSet(vector, _get_dynamic_stub(stub_idx, &_DynIntStubsBegin), 0);

	return vector;
}


/**
 * @brief Common dynamic IRQ handler function
 *
 * This gets called by _DynStubCommon with the stub index supplied as
 * an argument. Look up the required information in dyn_irq_list and
 * execute it.
 *
 * @param stub_idx Index into the dyn_irq_list array
 */
void _common_dynamic_irq_handler(uint32_t stub_idx)
{
	dyn_irq_list[stub_idx].handler(dyn_irq_list[stub_idx].param);
}

/**
 * @internal
 *
 * @brief Set the handler in an already connected stub
 *
 * This routine is used to modify an already fully constructed interrupt stub
 * to specify a new <routine> and/or <parameter>. This only works with
 * dynamic interrupt stubs.
 */
void _irq_handler_set(unsigned int vector, void (*routine)(void *parameter),
		      void *parameter)
{
	int key;
	uint8_t stub_idx;

	/*
	 * Disable IRQs so we can ensure that the associated interrupt
	 * doesn't run in an inconsistent state while we're doing this
	 */
	key = irq_lock();

	stub_idx = _stub_idx_from_vector(vector);

	__ASSERT(stub_idx < ALL_DYN_IRQ_STUBS, "Bad stub index");

	dyn_irq_list[stub_idx].handler = routine;
	dyn_irq_list[stub_idx].param = parameter;
	irq_unlock(key);
}

#endif /* ALL_DYN_IRQ_STUBS > 0 */

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
	 *
	 * Note: As _interrupt_vectors_allocated[] is initialized by the 'gen_idt'
	 * tool, it is critical that this routine use the same algorithm as the
	 * 'gen_idt' tool for allocating interrupt vectors.
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
