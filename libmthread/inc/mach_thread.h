/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _MTHREAD_THREAD_H
#define _MTHREAD_THREAD_H

#include <sys/sys.h>
#include <sys/lock.h>
#include <mach_hart.h>
#include <sched/sched.h>

typedef int64_t mach_thread_pid_t;

/* mach thread struct */
/* @brief thread header for a specific core. */
typedef struct mach_thread
{
    mach_thread_pid_t t_pid; /* the thread owner's pid */
    struct sched_snapshot* t_snap; /* the owner's stack */
	struct mach_thread* t_next; /* the next thread. */
} mach_thread_t;

/* @brief runs the scheduler for mach threads. */
void mach_spin_threads(void);

void mach_set_thread(mach_thread_t* thrd);
mach_thread_t* mach_summon_thread(struct sched_snapshot* snap);

/* sets a new runner for a specific mach thread. */
#define mach_set_next_thread(THRD, NXT) (THRD->next = NXT)

#endif /* !_MTHREAD_THREAD_H */
