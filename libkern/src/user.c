/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <errno.h>
#include <string.h>
#include <sys/user.h>
#include <sys/malloc.h>

/////////////////////////////////////////////////////////////////////////////////

// @file user.c
// @brief User Management Unit

/////////////////////////////////////////////////////////////////////////////////

#define SYS_USER_MAX (64U)

static size_t       g_user_list = 0UL; /* runtime user list, increments until SYS_USER_MAX is reached. */
static user_info_t* g_users[SYS_USER_MAX]; /* running users at the same time. */
static user_info_t* g_current_user = null; /* current running user */

char* g_super_user_name = SYS_SUPER_USER;

/// Hash index for the user table.
/// \param grp The user group.
/// \return The hashed index.
static size_t sys_user_hash_index(gid_t grp)
{
    return (g_user_list + grp) % SYS_USER_MAX;
}

static bool sys_check_user(uid_t usr)
{
    errno = EUSERS;

    if (usr > g_user_list) return false;

    errno = ENOMEM;

    if (g_users[usr] == null) return false;
    if (*g_users[usr]->u_name == 0) return false;

    return true;
}

uid_t sys_get_uid(void)
{
    if (g_current_user != null)
        return g_current_user->u_uid;

    return SYS_USER_INVALID;
}

/////////////////////////////////////////////////////////////////////////////////////

const char* sys_get_user_name(void)
{
    if (g_current_user != null)
        return g_current_user->u_name;

    return "(null)";
}


gid_t sys_get_gid(void)
{
    if (g_current_user != null)
        return g_current_user->u_grp;

    return -1;
}

/////////////////////////////////////////////////////////////////////////////////////

bool sys_set_user(uid_t uid)
{
    if (g_users[uid] == null) return false;

    g_current_user = g_users[uid];

    return true;
}

struct sys_sdctl* sys_get_sdctl(uid_t uid)
{
    if (g_users[uid] == null)
        return null;

    g_current_user = g_users[uid];
    return &g_current_user->u_sdctl;
}

/////////////////////////////////////////////////////////////////////////////////////

bool sys_is_root(uid_t usr)
{
    if (!sys_check_user(usr))
    {
        if (errno == EUSERS)
        {
            IOLog("[users] check failed, no such user\r\n");
        }

        return false;
    }

    return strncmp(g_users[usr]->u_name, SYS_SUPER_USER, strlen(SYS_SUPER_USER));
}

/////////////////////////////////////////////////////////////////////////////////////

uid_t sys_add_user(const char* username, gid_t grp)
{
    if (g_user_list > SYS_USER_MAX)
        return -ERANGE;

    if (username == null || *username == 0 || strlen(username) > SYS_USER_STRLEN)
        return -EACCES;

    if (grp == -1)
        return -EACCES;

    uid_t uid = sys_user_hash_index(grp);
    ++g_user_list;

    g_users[uid] = sys_alloc_ptr(sizeof(user_info_t), SYS_PROT_READ | SYS_PROT_WRITE);
    if (g_users[uid] == null) return -1;

    g_users[uid]->u_grp = grp;
    g_users[uid]->u_uid = uid;

    strncpy(g_users[uid]->u_name, username, strlen(username));

    return uid;
}

int sys_clear_user(uid_t uid)
{
    if (uid >= SYS_USER_MAX)
        return -1;

    if (g_users[uid]->u_uid == uid)
    {
        sys_free_ptr(g_users[uid]);
        return 0;
    }

    errno = ENOUSR;
    return -1;
}
