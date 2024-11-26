/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _FS_PROCFS_H
#define _FS_PROCFS_H

#include <sys/sys.h>
#include <sched/sched.h>

struct procfs_entry_hdr;

struct procfs_entry_hdr
{
    char d_name[256];
    char d_cwd[256];

    uint32_t d_affinity;
    uint32_t d_status;
    uint64_t d_pid;

    struct sys_thread* d_task;
    struct procfs_entry_hdr* d_next;
};

struct procfs_entry_hdr* procfs_track_current_process(pid_t pid);
struct sys_thread* procfs_get_task(pid_t pid);
const char* procfs_get_cwd(pid_t pid);
int32_t procfs_get_status(pid_t pid);

#endif /* ifndef _FS_PROCFS_H */
