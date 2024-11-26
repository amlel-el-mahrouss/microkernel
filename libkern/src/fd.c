/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <sched/sched.h>
#include <sys/malloc.h>
#include <sys/errno.h>
#include <sys/fd.h>

__COPYRIGHT("$kernel$");

// ----------------------------------------------------------------
// Function: sys_find_descriptor
// Purpose: finds the specified process descriptor.
// ----------------------------------------------------------------

static int32_t sys_find_descriptor(fd_t fd)
{
    struct sys_process* proc = sys_get_scheduled_process();

    if (proc == nil)
        return -1;

    for (size_t i = 0; i < proc->p_fd_cnt; ++i)
    {
        if (proc->p_fd[i] == fd)
        {
            errno = 0;
            return 0;
        }
    }

    errno = EBADF;
    return -1;
}

// ----------------------------------------------------------------
// Function: sys_open_process_hook
// Purpose: open file process hook
// ----------------------------------------------------------------

static fd_t sys_open_process_hook(fd_t fd)
{
    struct sys_process* proc = sys_get_scheduled_process();

    if (proc->p_fd_cnt > MAX_FILE_DESCRIPTORS)
    {
        sys_close(fd);
        return -1;
    }

    proc->p_fd[proc->p_fd_cnt] = fd;
    ++proc->p_fd_cnt;

    return fd;
}

// ----------------------------------------------------------------
// Function: sys_close_process_hook
// Purpose: close file process hook
// ----------------------------------------------------------------

static fd_t sys_close_process_hook(fd_t fd)
{
    if (sys_find_descriptor(fd) == -1)
        return -1;

    struct sys_process* proc = sys_get_scheduled_process();

    for (size_t i = 0; i < proc->p_fd_cnt; ++i)
    {
        if (proc->p_fd[i] == fd)
        {
            proc->p_fd[i] = -1;
            break;
        }
    }

    return 0;
}

// ----------------------------------------------------------------
// Function: sys_write
// Purpose: writes from the file descriptor
// ----------------------------------------------------------------

int32_t sys_write(fd_t fd, const char* bytes, size_t off, size_t len)
{
    if (sys_find_descriptor(fd) == -1)
        return -1;

    if (sys_get_mount() == null)
        return ENOTSUP;

    return sys_get_mount()->do_write(fd, bytes, off, len);
}

// ----------------------------------------------------------------
// Function: sys_read
// Purpose: reads from the file descriptor
// ----------------------------------------------------------------

int32_t sys_read(fd_t fd, char* bytes, size_t off, size_t len)
{
    if (sys_find_descriptor(fd) == -1)
        return -1;

    if (sys_get_mount() == null)
        return ENOTSUP;

    return sys_get_mount()->do_read(fd, bytes, off, len);
}

// ----------------------------------------------------------------
// Function: sys_flush
// Purpose: flushes the current file descriptor
// ----------------------------------------------------------------

int32_t sys_flush(fd_t fd)
{
    if (sys_find_descriptor(fd) == -1)
        return -1;

    if (sys_get_mount() == null)
    {
        errno = ENOTSUP;
        return -1;
    }

    return sys_get_mount()->do_flush(fd);
}

// ----------------------------------------------------------------
// Function: sys_open
// Purpose: opens a file descriptor
// ----------------------------------------------------------------

fd_t sys_open(const char* path, const char* mode)
{
    if (sys_get_mount() == null)
    {
        errno = ENOTSUP;
        return -1;
    }

    return sys_open_process_hook(sys_get_mount()->do_open(path, mode));
}

// ----------------------------------------------------------------
// Function: sys_close
// Purpose: closes a file descriptor
// ----------------------------------------------------------------

int32_t sys_close(fd_t fd)
{
    if (sys_find_descriptor(fd) == -1)
        return -1;

    if (sys_get_mount() == null)
    {
        errno = ENOTSUP;
        return -1;
    }

    return sys_close_process_hook(sys_get_mount()->do_close(fd));
}

// ----------------------------------------------------------------
// Function: sys_is_eof
// Purpose: is fd at eof?
// ----------------------------------------------------------------

int32_t sys_is_eof(fd_t fd)
{
    if (sys_find_descriptor(fd) == -1)
        return -1;

    if (sys_get_mount() == null)
    {
        errno = ENOTSUP;
        return -1;
    }

    return sys_get_mount()->do_eof(fd);
}

size_t  sys_tell(fd_t fd)
{
    if (sys_find_descriptor(fd) == -1)
        return -1;

    if (sys_get_mount() == null)
    {
        errno = ENOTSUP;
        return -1;
    }

    return sys_get_mount()->do_tell(fd);
}

int sys_seek(fd_t fd, size_t offset, int whence)
{
    if (sys_find_descriptor(fd) == -1)
        return -1;

    if (sys_get_mount() == null)
    {
        errno = ENOTSUP;
        return -1;
    }

    return sys_get_mount()->do_seek(fd, offset, whence);
}
