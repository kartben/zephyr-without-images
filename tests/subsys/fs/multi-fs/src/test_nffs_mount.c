/*
 * Copyright (c) 2018 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdint.h>
#include <stdio.h>
#include <device.h>
#include <fs/fs.h>
#include <ztest.h>
#include <ztest_assert.h>
#include "nffs_test_utils.h"
#include "test_fs_shell.h"

#if !defined(CONFIG_FILE_SYSTEM_SHELL)
/* NFFS work area strcut */
static struct nffs_flash_desc flash_desc;

/* mounting info */
static struct fs_mount_t nffs_mnt = {
	.type = FS_NFFS,
	.mnt_point = "/nffs",
	.fs_data = &flash_desc,
};

static int test_mount(void)
{
	struct device *flash_dev;
	int res;

	/*flash_dev = device_get_binding();*/
	if (!flash_dev) {
		return -ENODEV;
	}

	/* set backend storage dev */
	nffs_mnt.storage_dev = flash_dev;

	res = fs_mount(&nffs_mnt);
	if (res < 0) {
		TC_PRINT("Error mounting nffs [%d]\n", res);
		return TC_FAIL;
	}

	return TC_PASS;
}
#endif

void test_nffs_mount(void)
{
#ifdef CONFIG_FILE_SYSTEM_SHELL
	test_fs_nffs_mount();
#else
	zassert_true(test_mount() == TC_PASS, NULL);
#endif
}
