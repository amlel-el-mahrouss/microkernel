/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

/**
 * @brief this file handles the vfs layer of the kernel.
 */

#include <sys/malloc.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <string.h>

__COPYRIGHT("$kernel$");

static struct sys_mount_info* g_mount_point = null; /* main mount point, always first */
static struct sys_mount_info* g_mount_list = null; /* the mount list */

static void sys_mount_add_filesystem_to_list(struct sys_mount_info* mountToAdd)
{
    /* this shouldn't fail */
    assert(mountToAdd != null);

    struct sys_mount_info* mountInfo = g_mount_list;

    do
    {
        if (mountInfo->seek_next_fs == mountToAdd)
            break;

        if (mountInfo->seek_next_fs == null)
            mountInfo->seek_next_fs = mountToAdd;

        mountInfo = mountInfo->seek_next_fs;
    } while (mountInfo != null);
}

// ----------------------------------------------------------------
// Function: sys_unmount_current
// Purpose: unmount current filesystem
// ----------------------------------------------------------------

int32_t sys_unmount_current(bool alsoFree)
{
    if (g_mount_point != null)
    {
        if (alsoFree)
            sys_free_ptr(g_mount_point);

        g_mount_point = null;
        return 0;
    }

    return -ENOTSUP;
}

// ----------------------------------------------------------------
// Function: sys_mount
// Purpose: mounts filesystem.
// ----------------------------------------------------------------

int32_t sys_mount(struct sys_mount_info* mountInfo, bool mountCurrent)
{
    if (mountInfo != null)
    {
        if (mountCurrent && g_mount_point == null)
            g_mount_point = mountInfo;

        sys_mount_add_filesystem_to_list(mountInfo);
        return 0;
    }

    return -1;
}

// ----------------------------------------------------------------
// Function: sys_get_mount
// Purpose: gets the current mount descriptor.
// ----------------------------------------------------------------

struct sys_mount_info* sys_get_mount(void)
{
    return g_mount_point;
}

// ----------------------------------------------------------------
// Function: sys_find_mount
// Purpose: finds a mount descriptor.
// ----------------------------------------------------------------

struct sys_mount_info* sys_find_mount(const char* fs)
{
    if (fs == null ||
        *fs == 0 ||
        strlen(fs) > 32)
        return null;

    struct sys_mount_info* mountInfo = g_mount_list;

    while (mountInfo != null)
    {
        if (strncmp(mountInfo->the_name, fs, strlen(fs)) == 0)
            return mountInfo;

        mountInfo = mountInfo->seek_next_fs;
    }

    return g_mount_point;
}

// ----------------------------------------------------------------
// Function: sys_flag_set
// Purpose: sets a flag for the file descriptor.
// ----------------------------------------------------------------

int32_t sys_flag_set(fd_t fd, int32_t flag)
{
    if (fd == -1)
        return -1;

    if (sys_get_mount() == null ||
        !sys_get_mount()->do_setflag)
        return ENOTSUP;

    return sys_get_mount()->do_setflag(fd, flag);
}
