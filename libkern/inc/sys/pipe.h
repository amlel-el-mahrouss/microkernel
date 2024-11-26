/*
 *	========================================================
 *
 *	MP MicroKernel
 *
 * Date Added: 08/01/2023
 * Last Edit: 27/04/2023
 * Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * ========================================================
 */

#ifndef _PIPE_H
#define _PIPE_H

#include <sys/sys.h>
#include <sys/lock.h>
#include <sys/sdctl.h>

#define PIPE_NAME_LENGTH 			(64U)

/* pipe is fine */
#define PIPE_STATUS_OK 				(100U)
/* pipe is idle */
#define PIPE_STATUS_IDLE            (126U)
/* previous pipe operation failed */
#define PIPE_STATUS_FAILURE			(127U)
/* pipe might contain stupid and bad data */
#define PIPE_STATUS_CORRUPTED       (128U)

typedef struct buf
{
   char* buf; // buffer pointer
   ssize_t buf_cur; // buffer cursor
   size_t buf_size; // buffer size
} buf_t;

typedef struct sys_pipe
{
   char name[PIPE_NAME_LENGTH]; // /pipe/stdout
   size_t name_len;
   size_t name_used; // used bytes for name
   any_t io_ptr; // I/O pointer
   struct sys_sdctl desc; // sdctl
   uint16_t state; // status
   buf_t* in; // input buffer
   buf_t* out; // output buffer
   lock_t* lock; // smp lock
} pipe_t;

/* Pipe and buffer functions */

pipe_t*  sys_make_pipe(const char* name, size_t len, buf_t* in, buf_t* out);
buf_t*   sys_make_buffer(char* buffer, size_t size);
any_t    sys_get_buffer(pipe_t* pipe, int in_or_out);
int32_t  sys_free_pipe(pipe_t* pipe);
int32_t  sys_free_buffer(buf_t* buf);

#define PIPE_PROC_LENGTH 1024

#endif // ifndef _PIPE_H
