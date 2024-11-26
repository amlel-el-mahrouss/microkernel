/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#define __ABI__ ("mpux.exec-pef")

#include <pef.h>

__BEGIN_DECLS

typedef struct mpux_glob
{
    char filename[255];
    void* glob;
    size_t glob_sz;
} mpux_glob_t;

int sys_exec_path(const char* path);
int sys_exec_env_path(const char* path, char* const argv[], char* const envp[]);

extern const caddr_t __abi;

__END_DECLS
