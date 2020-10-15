/*
 * Copyright (c) 2016 Intel Corporation.
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_FS_FS_H_
#define ZEPHYR_INCLUDE_FS_FS_H_

#ifdef CONFIG_ARCH_POSIX
#ifndef __ssize_t_defined
typedef __SIZE_TYPE__ ssize_t;
#define __ssize_t_defined
#endif

#ifndef __off_t_defined
#ifndef __USE_FILE_OFFSET64
typedef long int off_t;
#else
typedef long long int off_t;
#endif
#define __off_t_defined
#endif

#else
#include <sys/types.h>
#endif

#include <sys/dlist.h>
#include <fs/fs_interface.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief File System APIs
 * @defgroup file_system_api File System APIs
 * @{
 */
struct fs_file_system_t;

enum fs_dir_entry_type {
	FS_DIR_ENTRY_FILE = 0,
	FS_DIR_ENTRY_DIR
};

/** @brief Enumeration to uniquely identify file system types.
 *
 * Zephyr supports in-tree file systems and external ones.  Each
 * requires a unique identifier used to register the file system
 * implementation and to associate a mount point with the file system
 * type.  This anonymous enum defines global identifiers for the
 * in-tree file systems.
 *
 * External file systems should be registered using unique identifiers
 * starting at @c FS_TYPE_EXTERNAL_BASE.  It is the responsibility of
 * applications that use external file systems to ensure that these
 * identifiers are unique if multiple file system implementations are
 * used by the application.
 */
enum {
	/** Identifier for in-tree FatFS file system. */
	FS_FATFS = 0,

	/** Identifier for in-tree LittleFS file system. */
	FS_LITTLEFS,

	/** Base identifier for external file systems. */
	FS_TYPE_EXTERNAL_BASE,
};

/**
 * @brief File system mount info structure
 *
 * @param node Entry for the fs_mount_list list
 * @param type File system type
 * @param mnt_point Mount point directory name (ex: "/fatfs")
 * @param fs_data Pointer to file system specific data
 * @param storage_dev Pointer to backend storage device
 * @param mountp_len Length of Mount point string
 * @param fs Pointer to File system interface of the mount point
 */
struct fs_mount_t {
	sys_dnode_t node;
	int type;
	const char *mnt_point;
	void *fs_data;
	void *storage_dev;
	/* fields filled by file system core */
	size_t mountp_len;
	const struct fs_file_system_t *fs;
};

/**
 * @brief Structure to receive file or directory information
 *
 * Used in functions that reads the directory entries to get
 * file or directory information.
 *
 * @param dir_entry_type Whether file or directory
 * - FS_DIR_ENTRY_FILE
 * - FS_DIR_ENTRY_DIR
 * @param name Name of directory or file
 * @param size Size of file. 0 if directory
 */
struct fs_dirent {
	enum fs_dir_entry_type type;
	char name[MAX_FILE_NAME + 1];
	size_t size;
};

/**
 * @brief Structure to receive volume statistics
 *
 * Used to retrieve information about total and available space
 * in the volume.
 *
 * @param f_bsize Optimal transfer block size
 * @param f_frsize Allocation unit size
 * @param f_blocks Size of FS in f_frsize units
 * @param f_bfree Number of free blocks
 */
struct fs_statvfs {
	unsigned long f_bsize;
	unsigned long f_frsize;
	unsigned long f_blocks;
	unsigned long f_bfree;
};

#define FS_O_READ       0x01
#define FS_O_WRITE      0x02
#define FS_O_RDWR       (FS_O_READ | FS_O_WRITE)
#define FS_O_MODE_MASK  0x03

#define FS_O_CREATE     0x10
#define FS_O_APPEND     0x20
#define FS_O_FLAGS_MASK 0x30

#define FS_O_MASK       (FS_O_MODE_MASK | FS_O_FLAGS_MASK)

#ifndef FS_SEEK_SET
#define FS_SEEK_SET	0	/* Seek from beginning of file. */
#endif
#ifndef FS_SEEK_CUR
#define FS_SEEK_CUR	1	/* Seek from current position. */
#endif
#ifndef FS_SEEK_END
#define FS_SEEK_END	2	/* Seek from end of file.  */
#endif

/**
 * @brief Open or create file
 *
 * Opens or possibly creates a file and associates a stream with it.
 *
 * @details
 * @p flags can be 0 or a binary combination of one or more of the following
 * identifiers:
 *   - @c FS_O_READ open for read
 *   - @c FS_O_WRITE open for write
 *   - @c FS_O_RDWR open for read/write (<tt>FS_O_READ | FS_O_WRITE</tt>)
 *   - @c FS_O_CREATE create file if it does not exist
 *   - @c FS_O_APPEND move to end of file before each write
 *
 * If @p flags are set to 0 the function will attempt to open an existing file
 * with no read/write access; this may be used to e.g. check if the file exists.
 *
 * @param zfp Pointer to a file object
 * @param file_name The name of a file to open
 * @param flags The mode flags
 *
 * @retval 0 on success;
 * @retval -EINVAL when a bad file name is given;
 * @retval -ENOENT when the file path is not possible (bad mount point);
 * @retval <0 an other negative errno code, depending on a file system back-end.
 */
int fs_open(struct fs_file_t *zfp, const char *file_name, fs_mode_t flags);

/**
 * @brief Close file
 *
 * Flushes the associated stream and closes the file.
 *
 * @param zfp Pointer to the file object
 *
 * @retval 0 on success;
 * @retval <0 a negative errno code on error.
 */
int fs_close(struct fs_file_t *zfp);

/**
 * @brief Unlink file
 *
 * Deletes the specified file or directory
 *
 * @param path Path to the file or directory to delete
 *
 * @retval 0 on success;
 * @retval <0 a negative errno code on error.
 */
int fs_unlink(const char *path);

/**
 * @brief Rename file or directory
 *
 * Performs a rename and / or move of the specified source path to the
 * specified destination.  The source path can refer to either a file or a
 * directory.  All intermediate directories in the destination path must
 * already exist.  If the source path refers to a file, the destination path
 * must contain a full filename path, rather than just the new parent
 * directory.  If an object already exists at the specified destination path,
 * this function causes it to be unlinked prior to the rename (i.e., the
 * destination gets clobbered).
 * @note Current implementation does not allow moving files between mount
 * points.
 *
 * @param from The source path
 * @param to The destination path
 *
 * @retval 0 on success;
 * @retval <0 a negative errno code on error.
 */
int fs_rename(const char *from, const char *to);

/**
 * @brief Read file
 *
 * Reads up to @p size bytes of data to @p ptr pointed buffer, returns number
 * of bytes read.  A returned value may be lower than @p size if there were
 * fewer bytes available than requested.
 *
 * @param zfp Pointer to the file object
 * @param ptr Pointer to the data buffer
 * @param size Number of bytes to be read
 *
 * @retval >=0 a number of bytes read, on success;
 * @retval <0 a negative errno code on error.
 */
ssize_t fs_read(struct fs_file_t *zfp, void *ptr, size_t size);

/**
 * @brief Write file
 *
 * Attempts to write @p size number of bytes to the specified file.
 * If a negative value is returned from the function, the file pointer has not
 * been advanced.
 * If the function returns a non-negative number that is lower than @p size,
 * the global @c errno variable should be checked for an error code,
 * as the device may have no free space for data.
 *
 * @param zfp Pointer to the file object
 * @param ptr Pointer to the data buffer
 * @param size Number of bytes to be written
 *
 * @retval >=0 a number of bytes written, on success;
 * @retval <0 a negative errno code on error.
 */
ssize_t fs_write(struct fs_file_t *zfp, const void *ptr, size_t size);

/**
 * @brief Seek file
 *
 * Moves the file position to a new location in the file. The @p offset is added
 * to file position based on the @p whence parameter.
 *
 * @param zfp Pointer to the file object
 * @param offset Relative location to move the file pointer to
 * @param whence Relative location from where offset is to be calculated.
 * - @c FS_SEEK_SET for the beginning of the file;
 * - @c FS_SEEK_CUR for the current position;
 * - @c FS_SEEK_END for the end of the file.
 *
 * @retval 0 on success;
 * @retval -ENOTSUP if not supported by underlying file system driver;
 * @retval <0 an other negative errno code on error.
 */
int fs_seek(struct fs_file_t *zfp, off_t offset, int whence);

/**
 * @brief Get current file position.
 *
 * Retrieves and returns the current position in the file stream.
 *
 * @param zfp Pointer to the file object
 *
 * @retval >= 0 a current position in file;
 * @retval -ENOTSUP if not supported by underlying file system driver;
 * @retval <0 an other negative errno code on error.
 *
 * The current revision does not validate the file object.
 */
off_t fs_tell(struct fs_file_t *zfp);

/**
 * @brief Truncate or extend an open file to a given size
 *
 * Truncates the file to the new length if it is shorter than the current
 * size of the file. Expands the file if the new length is greater than the
 * current size of the file. The expanded region would be filled with zeroes.
 *
 * @note In the case of expansion, if the volume got full during the
 * expansion process, the function will expand to the maximum possible length
 * and return success.  Caller should check if the expanded size matches the
 * requested length.
 *
 * @param zfp Pointer to the file object
 * @param length New size of the file in bytes
 *
 * @retval 0 on success;
 * @retval <0 a negative errno code on error.
 */
int fs_truncate(struct fs_file_t *zfp, off_t length);

/**
 * @brief Flush cached write data buffers of an open file
 *
 * The function flushes the cache of an open file; it can be invoked to ensure
 * data gets written to the storage media immediately, e.g. to avoid data loss
 * in case if power is removed unexpectedly.
 * @note Closing a file will cause caches to be flushed correctly so the
 * function need not be called when the file is being closed.
 *
 * @param zfp Pointer to the file object
 *
 * @retval 0 on success;
 * @retval <0 a negative errno code on error.
 */
int fs_sync(struct fs_file_t *zfp);

/**
 * @brief Directory create
 *
 * Creates a new directory using specified path.
 *
 * @param path Path to the directory to create
 *
 * @retval 0 on success;
 * @retval <0 a negative errno code on error
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
 * @retval 0 on success;
 * @retval <0 a negative errno code on error.
 */
int fs_opendir(struct fs_dir_t *zdp, const char *path);

/**
 * @brief Directory read entry
 *
 * Reads directory entries of an open directory. In end-of-dir condition,
 * the function will return 0 and set the <tt>entry->name[0]</tt> to 0.
 *
 * @note: Most existing underlying file systems do not generate POSIX
 * special directory entries "." or "..".  For consistency the
 * abstraction layer will remove these from lower layer results so
 * higher layers see consistent results.
 *
 * @param zdp Pointer to the directory object
 * @param entry Pointer to zfs_dirent structure to read the entry into
 *
 * @retval 0 on success or end-of-dir;;
 * @retval <0 a negative errno code on error.
 */
int fs_readdir(struct fs_dir_t *zdp, struct fs_dirent *entry);

/**
 * @brief Directory close
 *
 * Closes an open directory.
 *
 * @param zdp Pointer to the directory object
 *
 * @retval 0 on success;
 * @retval <0 a negative errno code on error.
 */
int fs_closedir(struct fs_dir_t *zdp);

/**
 * @brief Mount filesystem
 *
 * Perform steps needed for mounting a file system like
 * calling the file system specific mount function and adding
 * the mount point to mounted file system list.
 *
 * @param mp Pointer to the fs_mount_t structure.  Referenced object
 *	     is not changed if the mount operation failed.
 *	     A reference is captured in the fs infrastructure if the
 *	     mount operation succeeds, and the application must not
 *	     mutate the structure contents until fs_unmount is
 *	     successfully invoked on the same pointer.
 *
 * @retval 0 on success;
 * @retval -ENOENT when file system type has not been registered;
 * @retval -ENOTSUP when not supported by underlying file system driver;
 * @retval <0 a other negative errno code on error.
 */
int fs_mount(struct fs_mount_t *mp);

/**
 * @brief Unmount filesystem
 *
 * Perform steps needed to unmount a file system like
 * calling the file system specific unmount function and removing
 * the mount point from mounted file system list.
 *
 * @param mp Pointer to the fs_mount_t structure
 *
 * @retval 0 on success;
 * @retval <0 negative errno code on error.
 */
int fs_unmount(struct fs_mount_t *mp);

/**
 * @brief Get path of mount point at index
 *
 * This function iterates through the list of mount points and returns
 * the directory name of the mount point at the given @p index.
 * On success @p index is incremented and @p name is set to the mount directory
 * name.  If a mount point with the given @p index does not exist, @p name will
 * be set to @c NULL.
 *
 * @param index Pointer to mount point index
 * @param name Pointer to pointer to path name
 *
 * @retval 0 on success;
 * @retval -ENOENT if there is no mount point with given index.
 */
int fs_readmount(int *index, const char **name);

/**
 * @brief File or directory status
 *
 * Checks the status of a file or directory specified by the @p path.
 * @note The file on a storage device may not be updated until it is closed.
 *
 * @param path Path to the file or directory
 * @param entry Pointer to the zfs_dirent structure to fill if the file or
 * directory exists.
 *
 * @retval 0 on success;
 * @retval <0 negative errno code on error.
 */
int fs_stat(const char *path, struct fs_dirent *entry);

/**
 * @brief Retrieves statistics of the file system volume
 *
 * Returns the total and available space in the file system volume.
 *
 * @param path Path to the mounted directory
 * @param stat Pointer to the zfs_statvfs structure to receive the fs
 * statistics
 *
 * @retval 0 on success;
 * @retval <0 negative errno code on error.
 */
int fs_statvfs(const char *path, struct fs_statvfs *stat);

/**
 * @brief Register a file system
 *
 * Register file system with virtual file system.
 *
 * @param type Type of file system (ex: @c FS_FATFS)
 * @param fs Pointer to File system
 *
 * @retval 0 on success;
 * @retval <0 negative errno code on error.
 */
int fs_register(int type, const struct fs_file_system_t *fs);

/**
 * @brief Unregister a file system
 *
 * Unregister file system from virtual file system.
 *
 * @param type Type of file system (ex: @c FS_FATFS)
 * @param fs Pointer to File system
 *
 * @retval 0 on success;
 * @retval <0 negative errno code on error.
 */
int fs_unregister(int type, const struct fs_file_system_t *fs);

/**
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif /* ZEPHYR_INCLUDE_FS_FS_H_ */
