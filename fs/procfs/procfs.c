/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <procfs/procfs.h>
#include <sys/errno.h>
#include <sys/lock.h>
#include <string.h>

//! @file procfs.c
//! @brief Process FileSystem implementation

#define PROCFS_TIMEOUT_MAX 10000U

static struct procfs_entry_hdr* g_root_dat = null;

static int32_t procfs_track_if_not(struct procfs_entry_hdr** procfs_hdr)
{
    if (*procfs_hdr != null)
        return -1;

    *procfs_hdr = sys_alloc_ptr(sizeof(struct procfs_entry_hdr), SYS_PROT_READ | SYS_PROT_WRITE);
    return *procfs_hdr != null;
}

struct procfs_entry_hdr* procfs_track_current_process(pid_t pid)
{
    static lock_t* lock = null;

    if (lock)
	return null;

    lock = core_lock_acquire();

    assert(sys_get_scheduled_process() != null);

    /* we have to check first what process we track. */
    size_t timeout = 0;
    while (sys_get_scheduled_process()->p_thread->t_pid != pid)
    {
        ++timeout;

        if (timeout > PROCFS_TIMEOUT_MAX)
        {
	        core_lock_unlock(lock);
            errno = ETIMEOUT;

            return null;
        }
    }

    struct procfs_entry_hdr* dat = g_root_dat;

    /* iterate until d_next is null. */
    while (dat != null)
    {
        if (dat->d_pid == pid)
        {
	   core_lock_unlock(lock);
           return dat;
        }

        dat = dat->d_next;
    }

    if (dat == null)
        procfs_track_if_not(&dat);

    dat->d_task = sys_get_scheduled_process()->p_thread;
    dat->d_pid = pid;

    memncpy(dat->d_name, sys_get_scheduled_process()->p_thread->t_name, 256);
    memncpy(dat->d_cwd, "/", 2);

    dat->d_status = sys_get_scheduled_process()->p_thread->t_status;
    dat->d_affinity = sys_get_scheduled_process()->p_thread->t_affinity;

    // finally add it to the list.
    if (g_root_dat == null)
    {
        g_root_dat = dat;
    }
    else
    {
        struct procfs_entry_hdr* data = g_root_dat;

        /* iterate until d_next is null. */
        while (data != null)
        {
            if (data->d_next == null)
            {
                data->d_next = dat;
                break;
            }
        }
    }

    core_lock_unlock(lock);
    return dat;
}

struct sys_thread* procfs_get_task(pid_t pid)
{
    static lock_t* lock = null;

    if (lock)
	    return null;

    lock = core_lock_acquire();

    while (g_root_dat != null)
    {
        if (g_root_dat->d_pid == pid)
            return g_root_dat->d_task;

        g_root_dat = g_root_dat->d_next;
    }

    /* extract data from current process. */
    struct procfs_entry_hdr* dat = procfs_track_current_process(pid);

    core_lock_unlock(lock);

    if (dat != null)
        return dat->d_task;

    return null;
}

int32_t procfs_get_status(pid_t pid)
{
    static lock_t* lock = null;

    while (lock != null);

    lock = core_lock_acquire();

    if (g_root_dat == null)
        g_root_dat = procfs_track_current_process(pid);

    struct procfs_entry_hdr* rootProcStat = g_root_dat;

    while (rootProcStat != null)
    {
        if (rootProcStat->d_pid == pid)
            return rootProcStat->d_status;

        rootProcStat = rootProcStat->d_next;
    }

    core_lock_unlock(lock);

    return (-1);
}

const char* procfs_get_cwd(pid_t pid)
{
    if (g_root_dat == null)
        g_root_dat = procfs_track_current_process(pid);

    struct procfs_entry_hdr* rootProcStat = g_root_dat;

    while (rootProcStat != null)
    {
        if (rootProcStat->d_pid == pid)
            return rootProcStat->d_cwd;

        rootProcStat = rootProcStat->d_next;
    }

    return ("(null)");
}

// eof
