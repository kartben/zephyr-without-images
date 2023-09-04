/*
 * Copyright (c) 2017 Oticon A/S
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * Native simulator entry point (main)
 *
 * Documentation can be found starting in docs/README.md
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "nsi_cpun_if.h"
#include "nsi_tasks.h"
#include "nsi_cmdline_main_if.h"
#include "nsi_utils.h"
#include "nsi_hw_scheduler.h"
#include "nsi_config.h"
#include "nsi_cpu_ctrl.h"

int nsi_exit_inner(int exit_code)
{
	static int max_exit_code;
	int cpu_ret;

	max_exit_code = NSI_MAX(exit_code, max_exit_code);
	/*
	 * nsif_cpun_cleanup may not return if this is called from a SW thread,
	 * but instead it would get nsi_exit() recalled again
	 * ASAP from the HW thread
	 */
	for (int i = 0; i < NSI_N_CPUS; i++) {
		cpu_ret = nsif_cpun_cleanup(i);
		max_exit_code = NSI_MAX(cpu_ret, max_exit_code);
	}

	nsi_run_tasks(NSITASK_ON_EXIT_PRE_LEVEL);
	nsi_hws_cleanup();
	nsi_run_tasks(NSITASK_ON_EXIT_POST_LEVEL);
	return max_exit_code;
}

void nsi_exit(int exit_code)
{
	exit(nsi_exit_inner(exit_code));
}

/**
 * Run all early native_posix initialization steps, including command
 * line parsing and CPU start, until we are ready to let the HW models
 * run via hwm_one_event()
 */
static void nsi_init(int argc, char *argv[])
{
	/*
	 * Let's ensure that even if we are redirecting to a file, we get stdout
	 * and stderr line buffered (default for console)
	 * Note that glibc ignores size. But just in case we set a reasonable
	 * number in case somebody tries to compile against a different library
	 */
	setvbuf(stdout, NULL, _IOLBF, 512);
	setvbuf(stderr, NULL, _IOLBF, 512);

	nsi_run_tasks(NSITASK_PRE_BOOT_1_LEVEL);
	for (int i = 0; i < NSI_N_CPUS; i++) {
		nsif_cpun_pre_cmdline_hooks(i);
	}

	nsi_handle_cmd_line(argc, argv);

	nsi_run_tasks(NSITASK_PRE_BOOT_2_LEVEL);
	for (int i = 0; i < NSI_N_CPUS; i++) {
		nsif_cpun_pre_hw_init_hooks(i);
	}

	nsi_run_tasks(NSITASK_HW_INIT_LEVEL);
	nsi_hws_init();

	nsi_run_tasks(NSITASK_PRE_BOOT_3_LEVEL);

	nsi_cpu_auto_boot();

	nsi_run_tasks(NSITASK_FIRST_SLEEP_LEVEL);
}

/**
 * Execute the simulator for at least the specified timeout, then
 * return.  Note that this does not affect event timing, so the "next
 * event" may be significantly after the request if the hardware has
 * not been configured to e.g. send an interrupt when expected.
 */
void nsi_exec_for(uint64_t us)
{
	uint64_t start = nsi_hws_get_time();

	do {
		nsi_hws_one_event();
	} while (nsi_hws_get_time() < (start + us));
}

#ifndef NSI_LIBFUZZER

/**
 *
 * Note that this main() is not used when building fuzz cases,
 * as libfuzzer has its own main(),
 * and calls the "OS" through a per-case fuzz test entry point.
 */
int main(int argc, char *argv[])
{
	nsi_init(argc, argv);
	while (true) {
		nsi_hws_one_event();
	}

	/* This line should be unreachable */
	return 1; /* LCOV_EXCL_LINE */
}

#else /* NSI_LIBFUZZER */

/**
 * Entry point for fuzzing (when enabled). Works by placing the data
 * into two known symbols, triggering an app-visible interrupt, and
 * then letting the simulator run for a fixed amount of time (intended to be
 * "long enough" to handle the event and reach a quiescent state
 * again)
 */
uint8_t *nsi_fuzz_buf, nsi_fuzz_sz;

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t sz)
{
	static bool nsi_initialized;

	if (!nsi_initialized) {
		nsi_init(0, NULL);
		nsi_initialized = true;
	}

	/* Provide the fuzz data to the embedded OS as an interrupt, with
	 * "DMA-like" data placed into nsi_fuzz_buf/sz
	 */
	nsi_fuzz_buf = (void *)data;
	nsi_fuzz_sz = sz;
	hw_irq_ctrl_set_irq(NSI_FUZZ_IRQ);

	/* Give the OS time to process whatever happened in that
	 * interrupt and reach an idle state.
	 */
	nsi_exec_for(NSI_FUZZ_TIME);

	return 0;
}

#endif /* NSI_LIBFUZZER */
