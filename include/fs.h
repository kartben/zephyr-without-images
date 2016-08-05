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

#ifndef _FS_H_
#define _FS_H_

#include <sys/types.h>
#include <fs/fs_interface.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Create a ZFILE type similar to FILE for familiarity */
typedef struct _zfile_object ZFILE;

/* Create a ZDIR type similar to DIR for familiarity */
typedef struct _zdir_object ZDIR;

enum dir_entry_type {
	DIR_ENTRY_FILE,
	DIR_ENTRY_DIR
};

/**
 * @brief File System Functions
 * @defgroup data_structures File System Data Structures
 * @ingroup file_system
 * @{
 */

/** @var ZFILE
 * @brief File object representing an open file
 */

/** @var ZDIR
 * @brief Directory object representing an open directory
 */

/**
 * @brief Structure to receive file or directory information
 *
 * Used in functions that reads the directory entries to get
 * file or directory information.
 *
 * @param dir_entry_type Whether file or directory
 * - DIR_ENTRY_FILE
 * - DIR_ENTRY_DIR
 * @param name Name of directory or file
 * @param size Size of file. 0 if directory
 */
struct zfs_dirent {
	enum dir_entry_type type;
	char name[MAX_FILE_NAME + 1];
	size_t size;
};

/**
 * @}
 */

#ifndef SEEK_SET
#define SEEK_SET	0	/* Seek from beginning of file. */
#endif
#ifndef SEEK_CUR
#define SEEK_CUR	1	/* Seek from current position. */
#endif
#ifndef SEEK_END
#define SEEK_END	2	/* Seek from end of file.  */
#endif

/**
 * @brief File System APIs
 * @defgroup file_system_api File System APIs
 * @ingroup file_system
 * @{
 */

/**
 * @brief File open
 *
 * Opens an existing file or create a new one and associates
 * a stream with it.
 *
 * @param zfp Pointer to file object
 * @param file_name The name of file to open
 *
 * @retval 0 Success
 * @retval -ERRNO errno code if error
 */
int fs_open(ZFILE *zfp, const char *file_name);

/**
 * @brief File close
 *
 * Flushes the associated stream and closes
 * the file.
 *
 * @param zfp Pointer to the file object
 *
 * @retval 0 Success
 * @retval -ERRNO errno code if error
 */
int fs_close(ZFILE *zfp);

/**
 * @brief File unlink
 *
 * Deletes the specified file or directory
 *
 * @param path Path to the file or directory to delete
 *
 * @retval 0 Success
 * @retval -ERRNO errno code if error
 */
int fs_unlink(const char *path);

/**
 * @brief File read
 *
 * Reads items of data of size bytes long.
 *
 * @param zfp Pointer to the file object
 * @param ptr Pointer to the data buffer
 * @param size Number of bytes to be read
 *
 * @return Number of bytes read. On success, it will be equal to number of
 * items requested to be read. Returns less than number of bytes
 * requested if there are not enough bytes available in file. Will return
 * -ERRNO code on error.
 */
ssize_t fs_read(ZFILE *zfp, void *ptr, size_t size);

/**
 * @brief File write
 *
 * Writes items of data of size bytes long.
 *
 * @param zfp Pointer to the file object
 * @param ptr Pointer to the data buffer
 * @param size Number of bytes to be write
 *
 * @return Number of bytes written. On success, it will be equal to the number
 * of bytes requested to be written. Any other value, indicates an error. Will
 * return -ERRNO code on error.
 * In the case where -ERRNO is returned, the file pointer will not be
 * advanced because it couldn't start the operation.
 * In the case where it is able to write, but is not able to complete writing
 * all of the requested number of bytes, then it is because the disk got full.
 * In that case, it returns less number of bytes written than requested, but
 * not a negative -ERRNO value as in regular error case.
 */
ssize_t fs_write(ZFILE *zfp, const void *ptr, size_t size);

/**
 * @brief File seek
 *
 * Moves the file position to a new location in the file. The offset is added
 * to file position based on the 'whence' parameter.
 *
 * @param zfp Pointer to the file object
 * @param offset Relative location to move the file pointer to
 * @param whence Relative location from where offset is to be calculated.
 * - SEEK_SET = from beginning of file
 * - SEEK_CUR = from current position,
 * - SEEK_END = from end of file.
 *
 * @retval 0 Success
 * @retval -ERRNO errno code if error.
 */
int fs_seek(ZFILE *zfp, off_t offset, int whence);

/**
 * @brief Get current file position.
 *
 * Retrieves the current position in the file.
 *
 * @param zfp Pointer to the file object
 *
 * @retval position Current position in file
 * Current revision does not validate the file object.
 */
off_t fs_tell(ZFILE *zfp);

/**
 * @brief Directory create
 *
 * Creates a new directory using specified path.
 *
 * @param path Path to the directory to create
 *
 * @retval 0 Success
 * @retval -ERRNO errno code if error
 */
int fs_mkdir(const char *path);

/**
 * @brief Directory open
 *
 * Opens an existing directory specified by the path.
 *
 * @param zdp Pointer to the directory object
 * @param path Path to the directory to open
 *
 * @retval 0 Success
 * @retval -ERRNO errno code if error
 */
int fs_opendir(ZDIR *zdp, const char *path);

/**
 * @brief Directory read entry
 *
 * Reads directory entries of a open directory
 *
 * @param zdp Pointer to the directory object
 * @param entry Pointer to zfs_dirent structure to read the entry into
 *
 * @retval 0 Success
 * @retval -ERRNO errno code if error
 * @return In end-of-dir condition, this will return 0 and set
 * entry->name[0] = 0
 */
int fs_readdir(ZDIR *zdp, struct zfs_dirent *entry);

/**
 * @brief Directory close
 *
 * Closes an open directory.
 *
 * @param zdp Pointer to the directory object
 *
 * @retval 0 Success
 * @retval -ERRNO errno code if error
 */
int fs_closedir(ZDIR *zdp);

/**
 * @brief File or directory status
 *
 * Checks the status of a file or directory specified by the path
 *
 * @param path Path to the file or directory
 * @param entry Pointer to zfs_dirent structure to fill if file or directory
 * exists.
 *
 * @retval 0 Success
 * @retval -ERRNO errno code if error
 */
int fs_stat(const char *path, struct zfs_dirent *entry);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* _FS_H_ */
