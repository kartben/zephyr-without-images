/* syskernel.c */

/*
 * Copyright (c) 1997-2010, 2012-2014 Wind River Systems, Inc.
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

#include <zephyr.h>
#include <tc_util.h>

#include "syskernel.h"

#include <string.h>

/* #define FLOAT */

char __stack fiber_stack1[STACK_SIZE];
char __stack fiber_stack2[STACK_SIZE];

char Msg[256];

FILE * output_file;

const char sz_success[] = "SUCCESSFUL";
const char sz_partial[] = "PARTIAL";
const char sz_fail[] = "FAILED";

const char sz_module_title_fmt[] = "\nMODULE: %s";
const char sz_module_result_fmt[] = "\n\nPROJECT EXECUTION %s\n";
const char sz_module_end_fmt[] = "\nEND MODULE";

const char sz_date_fmt[] = "\nBUILD_DATE: %s %s";
const char sz_kernel_ver_fmt[] = "\nKERNEL VERSION: 0x%x";
const char sz_description[] = "\nTEST COVERAGE: %s";

const char sz_test_case_fmt[] = "\n\nTEST CASE: %s";
const char sz_test_start_fmt[] = "\nStarting test. Please wait...";
const char sz_case_result_fmt[] = "\nTEST RESULT: %s";
const char sz_case_details_fmt[] = "\nDETAILS: %s";
const char sz_case_end_fmt[] = "\nEND TEST CASE";
#ifdef FLOAT
const char sz_case_timing_fmt[] = "%6.3f nSec";
#else
const char sz_case_timing_fmt[] = "%ld nSec";
#endif

/* time necessary to read the time */
uint32_t tm_off;

/**
 *
 * @brief Get the time ticks before test starts
 *
 * Routine does necessary preparations for the test to start
 *
 * @return N/A
 */
void begin_test(void)
{
	/*
	 * Invoke bench_test_start in order to be able to use
	 * tCheck static variable.
	 */
	bench_test_start();
}

/**
 *
 * @brief Checks number of tests and calculate average time
 *
 * @return 1 if success and 0 on failure
 *
 * @param i   Number of tests.
 * @param t   Time in ticks for the whole test.
 */
int check_result(int i, uint32_t t)
{
	/*
	 * bench_test_end checks tCheck static variable.
	 * bench_test_start modifies it
	 */
	if (bench_test_end() != 0) {
		fprintf(output_file, sz_case_result_fmt, sz_fail);
		fprintf(output_file, sz_case_details_fmt,
				"timer tick happened. Results are inaccurate");
		fprintf(output_file, sz_case_end_fmt);
		return 0;
	}
	if (i != NUMBER_OF_LOOPS) {
		fprintf(output_file, sz_case_result_fmt, sz_fail);
		fprintf(output_file, sz_case_details_fmt, "loop counter = ");
		fprintf(output_file, "%i !!!", i);
		fprintf(output_file, sz_case_end_fmt);
		return 0;
	}
	fprintf(output_file, sz_case_result_fmt, sz_success);
	fprintf(output_file, sz_case_details_fmt,
			"Average time for 1 iteration: ");
	fprintf(output_file, sz_case_timing_fmt,
			SYS_CLOCK_HW_CYCLES_TO_NS_AVG(t, NUMBER_OF_LOOPS));

	fprintf(output_file, sz_case_end_fmt);
	return 1;
}


/**
 *
 * @brief Check for a key press
 *
 * @return 1 when a keyboard key is pressed, or 0 if no keyboard support
 */
int kbhit(void)
{
	return 0;
}


/**
 *
 * @brief Prepares the test output
 *
 * @param continuously   Run test till the user presses the key.
 *
 * @return N/A
 */

void init_output(int *continuously)
{
	ARG_UNUSED(continuously);

	/*
	 * send all printf and fprintf to console
	 */
	output_file = stdout;
}


/**
 *
 * @brief Close output for the test
 *
 * @return N/A
 */
void output_close(void)
{
}

/**
 *
 * @brief Perform all selected benchmarks
 *
 * @return N/A
 */
#ifdef CONFIG_MICROKERNEL
void SysKernelBench(void)
#else
void main(void)
#endif
{
	int	    continuously = 0;
	int	    test_result;

	init_output(&continuously);
	bench_test_init();

	do {
		fprintf(output_file, sz_module_title_fmt, "Nanokernel API test");
		fprintf(output_file, sz_kernel_ver_fmt, sys_kernel_version_get());
		fprintf(output_file,
				"\n\nEach test below are repeated %d times and the average\n"
				"time for one iteration is displayed.", NUMBER_OF_LOOPS);

		test_result = 0;

		test_result += sema_test();
		test_result += lifo_test();
		test_result += fifo_test();
		test_result += stack_test();

		if (test_result) {
			/* sema, lifo, fifo, stack account for twelve tests in total */
			if (test_result == 12) {
				fprintf(output_file, sz_module_result_fmt, sz_success);
			} else {
				fprintf(output_file, sz_module_result_fmt, sz_partial);
			}
		} else {
			fprintf(output_file, sz_module_result_fmt, sz_fail);
		}
		TC_PRINT_RUNID;

	} while (continuously && !kbhit());

	output_close();
}
