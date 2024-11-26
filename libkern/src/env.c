/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <sys/malloc.h>
#include <sys/env.h>
#include <string.h>

__COPYRIGHT("$kernel$");

// -------------------------------------------------------------------------
// function: sys_make_env
// purpose: Makes a new envpath_t with values.
// -------------------------------------------------------------------------

envpath_t* sys_make_env(const char* name, size_t nameLen, const char* value, size_t valueLen)
{
    if (value == null || *value == 0 || valueLen > ENV_VALUE_LEN)
        return null;

    if (name == null || *name == 0 || nameLen > ENV_NAME_LEN)
        return null;

    envpath_t* path = sys_env_alloc();

    if (path == null)
        return null;

    strncpy(path->e_name, name, nameLen);
    strncpy(path->e_value, value, valueLen);

    return path;
}

// -------------------------------------------------------------------------
// function: sys_remove_env
// purpose: Frees the envpath_t.
// -------------------------------------------------------------------------

void sys_remove_env(envpath_t* path)
{
    if (path != null)
    {
        zero_memory(path->e_name, ENV_NAME_LEN);
        zero_memory(path->e_value, ENV_VALUE_LEN);

        sys_env_free(path);
    }
}
