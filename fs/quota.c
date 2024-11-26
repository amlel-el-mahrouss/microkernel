/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <quota.h>

ssize_t sys_quota_check(struct fs_quota* quota)
{
    if (quota != null)
    {
        ssize_t num_users = 0;

        for (ssize_t i = 0; i < quota->num_users; ++i)
        {
            if (quota->users[i].quota >= 100)
                ++num_users;
        }

        return num_users;
    }

    return -1;
}
