/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _MP_FD_H
#define _MP_FD_H

#include <sys/stat.h>
#include <sys/attr.h>
#include <sys/pipe.h>

#define SEEK_SET (0U)
#define SEEK_CUR (1U)
#define SEEK_END (2U)

typedef enum
{
    // special files
	SYS_DEV = 11, // fd is a device
    SYS_PROC = 12, // fd contains process info
    SYS_ROOT = 13, // protected file needs elevation
    // standard files
    SYS_DIRECTORY = 14,
	SYS_SYMLINK = 15, // symbolic link
	SYS_FILE = 16,
    SYS_SOCK = 19, // treat as socket
    // Misc
    SYS_NO_EOF = 19, // no eof. (devices and sockets only)
} SYS_FLAGS;

#define SYS_FLAGS_COUNT (7U)

int32_t sys_write(fd_t fd, const char* bytes, size_t off, size_t len);
int32_t sys_read(fd_t fd, char* bytes, size_t off, size_t len);
fd_t sys_open(const char* path, const char* mode);
int32_t sys_flush(fd_t fd);
int32_t sys_close(fd_t fd);
int32_t sys_is_eof(fd_t fd);
size_t  sys_tell(fd_t fd);
int sys_seek(fd_t fd, size_t offset, int whence);

#endif /* ifndef _MP_FD_H */
