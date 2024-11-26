/*
 *	========================================================
 *
 *	MP MicroKernel - thread.h
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _SYS_THREAD_H
#define _SYS_THREAD_H

#include <sched/core/core.h>
#include <sys/env.h>

#define sched_process_stopped(STATUS) (STATUS == SCHED_STATUS_STOPPED)

/* TLS routines */
typedef int (*thread_free_t)(void* base, void* ptr, size_t sz);
typedef void* (*thread_malloc_t)(void* base, size_t sz);

struct sys_thread
{
    char t_name[SCHED_NAME_LEN];
    uint8_t* t_stack;

    struct sched_snapshot* t_snapshot;
    SCHED_AFFINITY t_affinity;
    thread_malloc_t t_malloc;
    thread_free_t t_free;
    reg_t t_entrypoint;

    // TODO: allocate them for user programs
    voidptr_t t_pool; // TODO, pool ptr
    size_t t_sz_pool; // TODO, total size of pool
    size_t t_used_pool; // TODO, used bytes in pool
    int32_t t_status;
    envpath_t* t_env;
    int32_t t_type;
    size_t t_envc;
    pid_t t_pid;
    uid_t t_uid;
    gid_t t_gid;
};

#endif // !_SYS_THREAD_H
