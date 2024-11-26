/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <mach_thread.h>
#include <sys/timer.h>
#include <errno.h>

mach_thread_t* g_mach_thread = null;
struct sched_snapshot g_mach_current_snap;

mach_thread_t* mach_summon_thread(struct sched_snapshot* snap)
{
    struct sys_process* process = sys_get_scheduled_process();
	if (process == null) return null;

    mach_thread_t* thrd = sys_alloc_ptr(sizeof(mach_thread_t), SYS_PROT_WRITE | SYS_PROT_READ);

    if (thrd == null) return null;

    thrd->t_pid = process->p_thread->t_pid;
    thrd->t_snap = snap;

	IOLog("[mach_summon_thread] new thread allocated with success! returning thread...\n");
    return thrd;
}

/* @brief set current thread for mach task manager. */
void mach_set_thread(mach_thread_t* thrd)
{
	if (thrd != null &&
        g_mach_thread == null) // checks the thread pointer, and if g_mach_thread is free...
		g_mach_thread = thrd;
}

// spins and runs any threads specified on the first hardware thread.
void mach_spin_threads(void)
{
	if (g_mach_thread != null)
	{
		if (g_mach_thread->t_snap != null)
			sys_sched_switch_context(&g_mach_current_snap,
                                     g_mach_thread->t_snap);

		g_mach_thread = g_mach_thread->t_next;
	}
}

int mach_revert(void)
{
    if (g_mach_thread != null)
	{
		sys_sched_switch_context(g_mach_thread->t_snap,
                                 &g_mach_current_snap);

		IOLog("[mach_revert] Switched back context.\r\n");

		return 0;
	}

	return ESMP;
}
