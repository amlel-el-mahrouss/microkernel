/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _SYS_QUOTA_H
#define _SYS_QUOTA_H

#include <sys/sys.h>
#include <sys/user.h>

struct fs_quota
{
    ssize_t num_users;

    struct
    {
        uid_t uid;
        gid_t gid;
        int32_t quota;
    }* users;
};

ssize_t sys_quota_check(struct fs_quota* quota);

#endif // !_SYS_QUOTA_H
