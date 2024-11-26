/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Date Added: 14/04/2023
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <sys/dir.h>
#include <sys/errno.h>

__COPYRIGHT("$kernel$");

// ----------------------------------------------------------------
// Function: sys_open_directory
// Purpose: opens a new directory descriptor
// ----------------------------------------------------------------

fd_t sys_open_directory(const char* path)
{
    if (sys_get_mount() == null)
        return ENOTSUP;

    return sys_get_mount()->do_opendir(path);
}

// ----------------------------------------------------------------
// Function: sys_open_directory
// Purpose: opens a new directory descriptor
// ----------------------------------------------------------------

fd_t sys_create_directory(const char* path)
{
    if (sys_get_mount() == null)
        return ENOTSUP;

    return sys_get_mount()->do_createdir(path);
}

// ----------------------------------------------------------------
// Function: sys_read_directory
// Purpose: reads a directory descriptor
// ----------------------------------------------------------------

struct sys_dirent* sys_read_directory(fd_t dir)
{
    if (sys_get_mount() == null)
    {
        errno = ENOTSUP;
        return null;
    }

    return sys_get_mount()->do_readdir(dir);
}

// ----------------------------------------------------------------
// Function: sys_close_directory
// Purpose: closes a directory descriptor
// ----------------------------------------------------------------

int32_t sys_close_directory(fd_t dir)
{
    if (sys_get_mount() == null)
        return ENOTSUP;

    return sys_get_mount()->do_close(dir);
}

// ----------------------------------------------------------------
// Function: sys_remove_directory
// Purpose: removes a directory descriptor
// ----------------------------------------------------------------

int32_t sys_remove_directory(fd_t dir)
{
    if (sys_get_mount() == null)
        return ENOTSUP;

    return sys_get_mount()->do_remove(dir);
}
