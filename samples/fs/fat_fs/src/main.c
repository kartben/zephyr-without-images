/*
 * Copyright (c) 2016 Intel Corporation.
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
#include <stdio.h>
#include <string.h>
#include <misc/printk.h>
#include <fs.h>

static void file_tests(void);
static void dir_tests(void);

#define TEST_SUB_DIR "sub1"
#define TEST_FILE "testfile.txt"

/*
 * @file
 * @brief File system demo
 * Demonstrates the ZEPHYR File System APIs
 */

void main(void)
{
	printk("File System Demo!\n\n");

	file_tests();
	dir_tests();
}

static int check_file_dir_exists(const char *path)
{
	int res;
	struct zfs_dirent entry;

	res = fs_stat(path, &entry);

	return !res;
}

static int open_file(ZFILE *fp, const char *path)
{
	int res;

	if (check_file_dir_exists(path)) {
		printk("Opening existing file %s\n", path);
	} else {
		printk("Creating new file %s\n", path);
	}

	res = fs_open(fp, path);
	if (res) {
		printk("Failed opening file [%d]\n", res);
		return res;
	}

	printk("Opened file %s\n", path);

	return res;
}

static const char test_str[] = "hello world!";

static int write_test(ZFILE *fp, off_t ofs, const char *str)
{
	ssize_t brw;
	int res;

	res = fs_seek(fp, ofs, SEEK_SET);
	if (res) {
		printk("fs_seek failed [%d]\n", res);
		fs_close(fp);
		return res;
	}

	brw = fs_write(fp, (char *)str, strlen(str));
	if (brw < 0) {
		printk("Failed writing to file [%d]\n", brw);
		fs_close(fp);
		return brw;
	}
	if (brw < strlen(str)) {
		printk("Unable to complete write. Volume full.\n");
		printk("Number of bytes written: [%d]\n", brw);
		fs_close(fp);
		return -1;
	}

	printk("Data successfully written!\n");
	printk("Data written:\"%s\"\n\n", str);

	return res;
}

static int read_test(ZFILE *fp, off_t ofs, size_t sz, char *read_buff)
{
	ssize_t brw;
	int res;

	res = fs_seek(fp, ofs, SEEK_SET);
	if (res) {
		printk("fs_seek failed [%d]\n", res);
		fs_close(fp);
		return res;
	}

	brw = fs_read(fp, read_buff, sz);
	if (brw < 0) {
		printk("Failed reading file [%d]\n", brw);
		fs_close(fp);
		return res;
	}

	printk("Data successfully read!\n");
	read_buff[brw] = 0;
	printk("Data read:\"%s\"\n\n", read_buff);

	return res;
}

static int close_file(ZFILE *fp, const char *path)
{
	int res;

	res = fs_close(fp);
	if (res) {
		printk("Error closing file [%d]\n", res);
		return res;
	}

	printk("Closed file %s\n", path);

	return res;
}

static int delete_test(const char *path)
{
	int res;

	/* Delete the file and verify checking its status */
	res = fs_unlink(path);
	if (res) {
		printk("Error deleting file [%d]\n", res);
		return res;
	}

	/* Check if file was deleted */
	if (check_file_dir_exists(path)) {
		printk("Failed deleting %s\n", path);
		return -1;
	}

	printk("File (%s) deleted successfully!\n", path);

	return 0;
}

static void file_tests(void)
{
	ZFILE fp;
	int res;
	char read_buff[80];

	res = open_file(&fp, TEST_FILE);
	if (res) {
		return;
	}

	res = write_test(&fp, 0, test_str);
	if (res) {
		return;
	}

	res = read_test(&fp, 0, strlen(test_str), read_buff);
	if (res) {
		return;
	}

	if (strcmp(test_str, read_buff)) {
		printk("Error - Data read does not match data written\n");
		return;
	}

	printk("Data read matches data written!\n");

	res = close_file(&fp, TEST_FILE);
	if (res) {
		return;
	}

	res = delete_test(TEST_FILE);
	if (res) {
		return;
	}
}

static int create_dir(const char *path)
{
	int res;

	res = fs_mkdir(path);
	if (res) {
		printk("Error creating dir[%d]\n", res);
		return res;
	}

	printk("Created dir %s!\n", path);

	return 0;
}

/* Deletes files and sub directories one level deep */
static int remove_dir(const char *path)
{
	int res;
	ZDIR dp;
	static struct zfs_dirent entry;
	char file_path[80];

	if (!check_file_dir_exists(path)) {
		return 0;
	}

	res = fs_opendir(&dp, path);
	if (res) {
		printk("Error opening dir[%d]\n", res);
		return res;
	}

	printk("\nRemoving files and sub directories in %s\n", path);
	for (;;) {
		res = fs_readdir(&dp, &entry);

		/* entry.name[0] == 0 means end-of-dir */
		if (res || entry.name[0] == 0) {
			break;
		}

		/* Delete file or sub directory */

		sprintf(file_path, "%s/%s", path, entry.name);
		printk("Removing %s\n", file_path);

		res = fs_unlink(file_path);
		if (res) {
			printk("Error deleting file/dir [%d]\n", res);
			fs_closedir(&dp);
			return res;
		}
	}

	fs_closedir(&dp);

	/* Remove the sub directory */
	res = fs_unlink(path);
	if (res) {
		printk("Error removing dir [%d]\n", res);
		return res;
	}

	printk("Removed dir %s!\n", path);

	return 0;
}

static int list_dir(const char *path)
{
	int res;
	ZDIR dp;
	static struct zfs_dirent entry;

	res = fs_opendir(&dp, path);
	if (res) {
		printk("Error opening dir[%d]\n", res);
		return res;
	}

	printk("\nListing dir %s:\n", path);
	for (;;) {
		res = fs_readdir(&dp, &entry);

		/* entry.name[0] == 0 means end-of-dir */
		if (res || entry.name[0] == 0) {
			break;
		}
		if (entry.type == DIR_ENTRY_DIR) {
			printk("[DIR ] %s\n", entry.name);
		} else {
			printk("[FILE] %s (size = %d)\n",
				entry.name, entry.size);
		}
	}

	fs_closedir(&dp);

	return 0;
}

static void dir_tests(void)
{
	ZFILE fp[2];
	int res;

	/* Remove sub dir if already exists */
	res = remove_dir(TEST_SUB_DIR);
	if (res) {
		return;
	}

	/* Create a sub directory */
	res = create_dir(TEST_SUB_DIR);
	if (res) {
		return;
	}

	/* Open or create files */

	res = open_file(&fp[0], TEST_FILE);
	if (res) {
		return;
	}

	res = open_file(&fp[1], TEST_SUB_DIR "/" TEST_FILE);
	if (res) {
		return;
	}

	/* Write to files to check size info */
	res = write_test(&fp[0], 0, "1");
	if (res) {
		return;
	}

	res = write_test(&fp[1], 0, "12");
	if (res) {
		return;
	}

	/* Close the files in the directories */

	res = close_file(&fp[0], TEST_FILE);
	if (res) {
		return;
	}

	res = close_file(&fp[1], TEST_SUB_DIR "/" TEST_FILE);
	if (res) {
		return;
	}

	/* List the files in root and sub dir */
	res = list_dir("/");
	if (res) {
		return;
	}

	res = list_dir(TEST_SUB_DIR);
	if (res) {
		return;
	}

	/* Remove sub dir */
	res = remove_dir(TEST_SUB_DIR);
	if (res) {
		return;
	}
}
