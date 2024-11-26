/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _SYS_USR_H
#define _SYS_USR_H

#include <sys/sys.h>
#include <sys/sdctl.h>

typedef int32_t uid_t;
typedef int32_t gid_t;

#define SYS_USER_WDIR ("/usr/")

#define SYS_USER_STRLEN (256U)

typedef struct user_info
{
    uid_t u_uid;
    gid_t u_grp;
    struct sys_sdctl u_sdctl;
    char  u_name[SYS_USER_STRLEN];
} user_info_t;

bool sys_is_root(uid_t uid);
int sys_clear_user(uid_t uid);

uid_t sys_add_user(const char* username, gid_t grp);
struct sys_sdctl* sys_get_sdctl(uid_t uid);
const char* sys_get_user_name(void);
bool sys_set_user(uid_t uid);
uid_t sys_get_uid(void);
gid_t sys_get_gid(void);

#define SYS_USER_INVALID (-1)
#define SYS_USER_ROOT    (0)

#define SYS_SUPER_USER   "root"

extern char* g_super_user_name;

#endif /* ifndef _SYS_USR_H */
