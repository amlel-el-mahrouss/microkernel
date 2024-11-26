/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _FS_PFS_H
#define _FS_PFS_H

#include <sys/errno.h>
#include <sys/sdctl.h>
#include <sys/stat.h>
#include <sys/pipe.h>
#include <sys/user.h>
#include <sys/dev.h>
#include <sys/fd.h>
#include <fs/types.h>

#include <quota.h>
#include <stdio.h>

#define FS_PATH_CURRENT_DIR (".")
#define FS_PATH_UPPER_DIR ("..")
#define FS_PATH_SEPARATOR ("/")
#define FS_PATH_MAX (256U)

struct pfs_range
{
  uint64_t pfs_start_paddr;
  size_t pfs_block_count;
};

struct pfs_mount_info
{
    char m_root[FS_PATH_MAX]; /* mount root directory */
    uint32_t m_filesystem; /* filesystem (id is always non-zero) */
    uint32_t m_flags; /* mount flags */
};

#define FS_OPTS_NAME_LEN (32U)

/* lower level than stat.h's file protocol */
/* it is used by physical filesystems to communicate with each other */

struct pfs_opt
{
    char f_name[FS_OPTS_NAME_LEN];
    int32_t f_id;

    int (*f_write)(fd_t fd, const char* bytes, size_t off, size_t len);
    int (*f_read)(fd_t fd, char* bytes, ssize_t off, size_t len);
    fd_t (*f_open)(const char* path, const char* r);
    void (*f_close)(fd_t fd);
    fd_t (*f_mkdir)(const char* dirname);
    void (*f_rmdir)(fd_t fd);
    void (*f_chdir)(fd_t fd, const char* path);
    struct pfs_mount_info* (*f_mount)(fd_t fd);
    int (*f_unmount)(struct pfs_mount_info* mount);
};

#define fs_alloc() sys_alloc_ptr(sizeof(struct pfs_opt), SYS_PROT_READ | SYS_PROT_WRITE)
#define fs_free(ptr) sys_free_ptr(ptr)

struct pfs_opt* sys_make_fs_opts(const char* name,
    int (*write)(fd_t fd, const char* bytes, size_t off, size_t len),
    int (*read)(fd_t fd, char* bytes, ssize_t off, size_t len),
    fd_t (*open)(const char* path, const char* r),
    void (*close)(fd_t fd),
    fd_t (*mkdir)(const char* dirname),
    void (*rmdir)(fd_t fd),
    struct pfs_mount_info* (*mount)(fd_t fd),
    int (*unmount)(struct pfs_mount_info* mount));

void sys_free_fs_opts(struct pfs_opt* desc);

#define fs_open(fs, path, r) fs->f_open(path, r)
#define fs_close(fs, fd) fs->f_close(fd)

#endif /* ifndef _FS_PFS_H */
