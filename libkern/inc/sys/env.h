/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#include <sys/sys.h>

#define ENV_VALUE_LEN (256U)
#define ENV_NAME_LEN  (256U)

#define sys_env_alloc() sys_alloc_ptr(sizeof(envpath_t), SYS_PROT_READ | SYS_PROT_WRITE)
#define sys_env_free(ptr) sys_free_ptr(ptr)

typedef struct envpath
{
    char e_name[ENV_NAME_LEN];
    char e_value[ENV_VALUE_LEN];
} envpath_t;

envpath_t* sys_make_env(const char* name, size_t nameLen, const char* value, size_t valueLen);
void sys_remove_env(envpath_t* path);
