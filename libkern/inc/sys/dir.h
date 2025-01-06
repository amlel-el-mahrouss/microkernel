/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Date Added: 14/04/2023
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _MP_DIR_H
#define _MP_DIR_H

#include <sys/sys.h>
#include <sys/stat.h>

struct sys_dirent* sys_read_directory(fd_t dir);
fd_t sys_create_directory(const char* path);
fd_t sys_open_directory(const char* path);
int32_t sys_close_directory(fd_t dir);
int32_t sys_remove_directory(fd_t dir);

#endif /* ifndef _MP_DIR_H */
