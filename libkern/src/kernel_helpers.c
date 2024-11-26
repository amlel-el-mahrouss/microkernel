/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

/// @file kernel_helpers.c
/// @brief Contains helpers for the kernel.

#include <sched/helper.h>
#include <sys/errno.h>

/* last rev 23/12/23 */

__COPYRIGHT("$kernel$");

// -------------------------------------------------------------------------
// function: sched_get_current_info
// purpose: Gets the current process information.
// -------------------------------------------------------------------------

struct sys_process_info sys_sched_get_current_info(void)
{
    struct sys_process_info info;
    zero_memory(&info, sizeof(struct sys_process_info));

    if (sys_get_scheduled_process() == null) return info;

    struct sys_process* proc = sys_get_scheduled_process();

    strncpy(info.p_name, proc->p_thread->t_name, strlen(proc->p_thread->t_name));

    info.p_thread = proc->p_thread;
    info.p_sdctl = proc->p_sdctl;

    return info;
}
