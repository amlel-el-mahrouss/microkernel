/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _SYSCALL_H
#define _SYSCALL_H

#include <sys/sys.h>

/* common execution flow */

/* exit program. */
void do_exit(int code);

/* execute from path */
int do_exec(const char* path);

/* io control */
int do_ioctl(int id, int cnt, voidptr_t val);

/* system control */
int do_sysctl(const char* name, int cnt, voidptr_t val);

/* execute with arguments and envrinoment variables. */
int do_execve(const char *path, char* const argv[], char *const envp[]);

/* read file descriptor */
int do_read(__FD_TYPE__ fd, char* bytes, size_t off, size_t len);

/* write file descriptor */
int do_write(__FD_TYPE__ fd, const char* bytes, size_t off, size_t len);

/* open file descriptor */
__FD_TYPE__ do_open(const char* path, const char* mode);

/* flush file descriptor */
int do_flush(__FD_TYPE__ fd);

/* set file descriptor flag */
int do_set_flag(__FD_TYPE__ fd, __FLAG_TYPE__ flags);

/* close file descriptor */
int do_close(__FD_TYPE__ fd);

/* eof check for file descriptor */
int do_is_eof(__FD_TYPE__ fd);

/* Main System call entrypoint */

void sys_dispatch_system_call(sys_snap_t* snapshot);

/* System call macros */

#define SYS_EXIT   0
#define SYS_EXEC   1
#define SYS_EXECVE 2
#define SYS_SYSCTL 3
#define SYS_IOCTL  4
#define SYS_PIPE   5

#endif // !_SYSCALL_H
