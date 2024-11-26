 //
 //	========================================================
 //
 //	    MP MicroKernel
 // 	Copyright Amlal EL Mahrouss, all rights reserved.
 //
 // ========================================================
 //

#include <sys/sys.h>
#include <sys/fd.h>
#include <string.h>
#include <sys/malloc.h>

//
// @brief this server consists of 3 rpc calls.
// mount, unmount -> unmount/mount filesystem to this instance.
// get -> mountpoint getter.
//

struct mpux_fs_server_info
{
    // @brief filesystem to mount for this instance.
    struct sys_mount_info* filesystemToMount;
    char instanceName[32];
};

struct sys_mount_info* g_mount = null;

int mpux_server_mount(struct mpux_fs_server_info* info_ptr)
{
    if (info_ptr->filesystemToMount != null)
    {
        sys_mount(info_ptr->filesystemToMount, false);
        g_mount = info_ptr->filesystemToMount;

        memncpy(info_ptr->filesystemToMount->the_name, info_ptr->instanceName, 32);

        return 0;
    }

    return -1;
}

int mpux_server_unmount(struct mpux_fs_server_info* info_ptr)
{
    struct sys_mount_info* mount = sys_find_mount(info_ptr->instanceName);

    if (info_ptr->filesystemToMount == mount)
    {
        sys_free_ptr(mount);
        info_ptr->filesystemToMount = null;

        return 0;
    }

    return -1;
}

int mpux_server_get(struct sys_mount_info** ppMount)
{
    *ppMount = g_mount;
}
