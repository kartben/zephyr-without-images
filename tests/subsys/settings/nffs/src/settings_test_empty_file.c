/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 * Copyright (c) 2015 Runtime Inc
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "settings_test.h"
#include "settings/settings_file.h"
#include <fs.h>

void test_config_empty_file(void)
{
	int rc;
	struct settings_file cf_mfg;
	struct settings_file cf_running;
	const char cf_mfg_test[] = "";
	const char cf_running_test[] = "\n\n";

	config_wipe_srcs();

	cf_mfg.cf_name = TEST_CONFIG_DIR "/mfg";
	cf_running.cf_name = TEST_CONFIG_DIR "/running";

	rc = settings_file_src(&cf_mfg);
	zassert_true(rc == 0, "can't register FS as configuration source\n");
	rc = settings_file_src(&cf_running);
	zassert_true(rc == 0, "can't register FS as configuration source\n");

	/*
	 * No files
	 */
	settings_load();

	rc = fs_mkdir(TEST_CONFIG_DIR);
	zassert_true(rc == 0, "can't create directory\n");

	rc = fsutil_write_file(TEST_CONFIG_DIR "/mfg", cf_mfg_test,
			       sizeof(cf_mfg_test));
	zassert_true(rc == 0, "can't write to file\n");

	rc = fsutil_write_file(TEST_CONFIG_DIR "/running", cf_running_test,
			       sizeof(cf_running_test));
	zassert_true(rc == 0, "can't write to file\n");

	settings_load();
	config_wipe_srcs();
	ctest_clear_call_state();
}
