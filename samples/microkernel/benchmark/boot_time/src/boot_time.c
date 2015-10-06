/* boot_time.c - Boot Time measurement task */

/*
 * Copyright (c) 2013-2015 Wind River Systems, Inc.
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
Measure boot time for both nanokernel and microkernel project which includes
- from reset to kernel's _start
- from _start to main()
- from _start to task
- from _start to idle (for microkernel)
 */

#ifdef CONFIG_NANOKERNEL
#include <nanokernel.h>
#else
#include <zephyr.h>
#include <version.h>
#endif
#include <arch/cpu.h>
#include <tc_util.h>

/* externs */
extern uint64_t __start_tsc; /* timestamp when kernel begins executing */
extern uint64_t __main_tsc;  /* timestamp when main() begins executing */
extern uint64_t __idle_tsc;  /* timestamp when CPU went idle */

void bootTimeTask(void)
{
	uint64_t task_tsc;  /* timestamp at beginning of first task  */
	uint64_t _start_us; /* being of __start timestamp in us	 */
	uint64_t main_us;   /* begin of main timestamp in us	 */
	uint64_t task_us;   /* begin of task timestamp in us	 */
	uint64_t s_main_tsc; /* __start->main timestamp		 */
	uint64_t s_task_tsc;  /*__start->task timestamp		 */
#ifndef  CONFIG_NANOKERNEL
	uint64_t idle_us;	/* begin of idle timestamp in us	 */
	uint64_t s_idle_tsc;  /*__start->idle timestamp		 */
#endif /* ! CONFIG_NANOKERNEL */

	task_tsc = _NanoTscRead();
#ifndef  CONFIG_NANOKERNEL
	/* Go to sleep for 1 tick in order to timestamp when IdleTask halts. */
	task_sleep(1);
#endif /* ! CONFIG_NANOKERNEL */

	_start_us = __start_tsc / CONFIG_CPU_CLOCK_FREQ_MHZ;
	s_main_tsc = __main_tsc-__start_tsc;
	main_us   = s_main_tsc / CONFIG_CPU_CLOCK_FREQ_MHZ;
	s_task_tsc = task_tsc-__start_tsc;
	task_us   = s_task_tsc / CONFIG_CPU_CLOCK_FREQ_MHZ;
#ifndef  CONFIG_NANOKERNEL
	s_idle_tsc = __idle_tsc-__start_tsc;
	idle_us   =  s_idle_tsc / CONFIG_CPU_CLOCK_FREQ_MHZ;
#endif

	/* Indicate start for sanity test suite */
	TC_START("Boot Time Measurement");

	/* Only print lower 32bit of time result */
#ifdef CONFIG_NANOKERNEL
	TC_PRINT("NanoKernel Boot Result: Clock Frequency: %d MHz\n",
			 CONFIG_CPU_CLOCK_FREQ_MHZ);
#else	/* CONFIG_MICROKERNEL */
	TC_PRINT("MicroKernel Boot Result: Clock Frequency: %d MHz\n",
			 CONFIG_CPU_CLOCK_FREQ_MHZ);
#endif
	TC_PRINT("__start       : %d cycles, %d us\n",
			 (uint32_t)(__start_tsc & 0xFFFFFFFFULL),
			 (uint32_t) (_start_us  & 0xFFFFFFFFULL));
	TC_PRINT("_start->main(): %d cycles, %d us\n",
			 (uint32_t)(s_main_tsc & 0xFFFFFFFFULL),
			 (uint32_t)  (main_us  & 0xFFFFFFFFULL));
	TC_PRINT("_start->task  : %d cycles, %d us\n",
			 (uint32_t)(s_task_tsc & 0xFFFFFFFFULL),
			 (uint32_t)  (task_us  & 0xFFFFFFFFULL));
#ifndef  CONFIG_NANOKERNEL  /* CONFIG_MICROKERNEL */
	TC_PRINT("_start->idle  : %d cycles, %d us\n",
			 (uint32_t)(s_idle_tsc & 0xFFFFFFFFULL),
			 (uint32_t)  (idle_us  & 0xFFFFFFFFULL));

#endif

	TC_PRINT("Boot Time Measurement finished\n");

	// for sanity regression test utility.
	TC_END_RESULT(TC_PASS);
	TC_END_REPORT(TC_PASS);

}

#ifdef CONFIG_NANOKERNEL

char __stack fiberStack[512];

/**
 *
 * @brief Nanokernel entry point
 *
 * @return N/A
 */

void main(void)
{
	/* record timestamp for nanokernel's main() function */
	__main_tsc = _NanoTscRead();

	/* create bootTime fibers */
	task_fiber_start(fiberStack, 512,
					 (nano_fiber_entry_t) bootTimeTask, 0, 0, 6, 0);
}

#endif /*  CONFIG_NANOKERNEL */
