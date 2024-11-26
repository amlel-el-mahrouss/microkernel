/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <sys/stat.h>
#include <sys/malloc.h>
#include <fs/pfs.h>

// @brief make filesystem operator.
struct pfs_opt* sys_make_fs_opts(const char* name,
    int (*write)(fd_t fd, const char* bytes, size_t off, size_t len),
    int (*read)(fd_t fd, char* bytes, ssize_t off, size_t len),
    fd_t (*open)(const char* path, const char* r),
    void (*close)(fd_t fd),
    fd_t (*mkdir)(const char* dirname),
    void (*rmdir)(fd_t fd),
    struct pfs_mount_info* (*mount)(fd_t fd),
    int (*unmount)(struct pfs_mount_info* mount))
{
    fd_t fd = sys_open(name, "rw");

    if (fd == -1)
        return null;

    struct pfs_opt* desc = fs_alloc();
    if (!desc) return null;

    desc->f_id = fd;

    strncpy(desc->f_name, name, strlen(name));

    desc->f_write = write;
    desc->f_read = read;
    desc->f_open = open;
    desc->f_close = close;
    desc->f_mkdir = mkdir;
    desc->f_rmdir = rmdir;
    desc->f_mount = mount;
    desc->f_unmount = unmount;

    return desc;
}

// @brief free filesystem operators.
void sys_free_fs_opts(struct pfs_opt* desc)
{
    if (desc != null)
        fs_free(desc);
}
