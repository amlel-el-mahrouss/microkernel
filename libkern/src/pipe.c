/*
 *	========================================================
 *
 *	MP MicroKernel
 *
 * 	Date Added: 09/01/2023
 *	Date Edit: 22/01/2023
 *
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <sys/malloc.h>
#include <sys/errno.h>
#include <sys/pipe.h>
#include <stddef.h>
#include <string.h>

__COPYRIGHT("$kernel$");

// ----------------------------------------------------------------
// Function: sys_make_buffer
// Purpose: Makes a buffer
// ----------------------------------------------------------------

buf_t* sys_make_buffer(char* buffer, size_t size)
{
    if (size < 1) return null;
    if (buffer == null) return null;

    buf_t* buf = sys_alloc_ptr(sizeof(buf_t), SYS_PROT_WRITE | SYS_PROT_READ);
    if (buf == null) return null;

    buf->buf_size = size;
    buf->buf_cur = 0UL;
    buf->buf = buffer;

    return buf;
}

// ----------------------------------------------------------------
// Function: sys_make_pipe
// Purpose: Makes a pipe
// ----------------------------------------------------------------

pipe_t* sys_make_pipe(const char* name, size_t len, buf_t* in, buf_t* out)
{
    if (len < 1) return null;
    if (name == null || *name == 0) return null;

    pipe_t* pipe_ptr = sys_alloc_ptr(sizeof(pipe_t), SYS_PROT_WRITE | SYS_PROT_READ);
    if (pipe_ptr == null) return null;

    pipe_ptr->state = PIPE_STATUS_IDLE;

    if (in != null)
        pipe_ptr->in = in;

    if (out != null)
        pipe_ptr->out = out;

    pipe_ptr->desc.access = SD_ACCESS_STANDARD;
    pipe_ptr->desc.type = SD_TYPE_PIPE;
    pipe_ptr->desc.perms = 0;

    memncpy(pipe_ptr->name, name, len);

  	pipe_ptr->name_len = len;

  	return pipe_ptr;
}

// ----------------------------------------------------------------
// Function: sys_free_pipe
// Purpose: Frees a pipe
// ----------------------------------------------------------------

int32_t sys_free_pipe(pipe_t* pipe_ptr)
{
    if (pipe_ptr != null)
    {
        sys_free_ptr(pipe_ptr->in);
        sys_free_ptr(pipe_ptr->out);

        return sys_free_ptr(pipe_ptr);
    }

    return -1;
}

// ----------------------------------------------------------------
// Function: sys_free_buffer
// Purpose: Frees a buffer
// ----------------------------------------------------------------

int32_t sys_free_buffer(buf_t* buf)
{
    if (buf != null)
        return sys_free_ptr(buf);

    return -1;
}

// ----------------------------------------------------------------
// Function: sys_get_buffer
// Purpose: Gets the buffer of any pipe.
// ----------------------------------------------------------------

any_t sys_get_buffer(pipe_t* pipe_ptr, int in_or_out)
{
    if (pipe_ptr != null)
        return in_or_out ? pipe_ptr->in : pipe_ptr->out;

    return null;
}
