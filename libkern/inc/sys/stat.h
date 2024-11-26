/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef __SYS_STAT_H__
#define __SYS_STAT_H__

#include <sys/sys.h>

#define S_IRWXU (0000700)    /* RWX mask for owner */
#define S_IRUSR (0000400)    /* R for owner */
#define S_IWUSR (0000200)    /* W for owner */
#define S_IXUSR (0000100)    /* X for owner */

#define S_IRWXG (0000070)    /* RWX mask for group */
#define S_IRGRP (0000040)    /* R for group */
#define S_IWGRP (0000020)    /* W for group */
#define S_IXGRP (0000010)    /* X for group */

#define S_IRWXO (0000007)    /* RWX mask for other */
#define S_IROTH (0000004)    /* R for other */
#define S_IWOTH (0000002)    /* W for other */
#define S_IXOTH (0000001)    /* X for other */

#define S_ISUID (0004000)    /* set user id on execution */
#define S_ISGID (0002000)    /* set group id on execution */
#define S_ISVTX (0001000)    /* save swapped text even after use */

typedef uint32_t mode_t;

typedef __FD_TYPE__ fd_t; /* file descriptor id */
typedef __FLAG_TYPE__ flag_t; /* flag type */

struct sys_dirent;

struct sys_mount_info
{
    char the_name[32];
    __FD_TYPE__ the_root; /* root directory */

    int32_t (*do_remove)(__FD_TYPE__ dir);
    __FD_TYPE__ (*do_create)(const char* name);
    __FD_TYPE__ (*do_createdir)(const char* name);
    struct sys_dirent* (*do_readdir)(fd_t fd);
    int32_t (*do_close)(fd_t fd);
    int32_t (*do_flush)(fd_t fd);
    int32_t (*do_eof)(fd_t fd);
    int32_t (*do_setflag)(fd_t fd, int32_t flag);
    __FD_TYPE__ (*do_opendir)(const char* name);
    __FD_TYPE__ (*do_open)(const char* name, const char* rest);
    int32_t (*do_move)(__FD_TYPE__ dir, const char* where);
    int32_t (*do_copy)(__FD_TYPE__ dst, __FD_TYPE__ src);
    int32_t (*do_write)(__FD_TYPE__ fd, const char* bytes, size_t off, size_t len);
    int32_t (*do_read)(__FD_TYPE__ fd, char* bytes, size_t off, size_t len);
    size_t  (*do_tell)(__FD_TYPE__ fd);
    int     (*do_seek)(__FD_TYPE__ fd, size_t offset, int whence);

    struct sys_mount_info* seek_next_fs;
};

struct sys_dirent
{
    char path[256]; /* /directory/or/a/sub/directory/ */
    __FD_TYPE__ fd; /* directory file descriptor */
    off_t off; /* record offset */
    size_t len; /* record length */
};

int32_t sys_mount(struct sys_mount_info* mountPoint, bool alsoMountCurrent);
int32_t sys_unmount_current(bool alsoFree);

struct sys_mount_info* sys_find_mount(const char* fs);
struct sys_mount_info* sys_get_mount(void);

// set flag for node
int32_t sys_flag_set(fd_t fd, int32_t flag);

#endif // !__SYS_STAT_H__
