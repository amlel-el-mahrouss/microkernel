/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _SYS_SCHED_H
#define _SYS_SCHED_H

#include <sched/core/thread.h>
#include <sys/attr.h>
#include <sys/sdctl.h>
#include <sys/env.h>

struct sys_process;

// @brief MAX_FILE_DESCRIPTORS is a macro which tells how many master descriptors per process.

#define MAX_FILE_DESCRIPTORS 1000

// ----------------------------------------------------------------
// Structure: sys_process
// Purpose: process structure.
// ----------------------------------------------------------------

struct attr(packed) sys_process
{
    struct sys_thread* p_thread; /* thread information */
    struct sys_sdctl p_sdctl; /* permission descriptor */
    struct sys_pipe* p_pipe; /* our process pipe */

    /* file descriptor array */
    __FD_TYPE__       p_fd[MAX_FILE_DESCRIPTORS];
    size_t            p_fd_cnt;

    struct sys_process* p_prev; /* previous process in the list. */
    struct sys_process* p_next; /* next process in the list */
};

// ----------------------------------------------------------------
// Type: exit_code_t
// Purpose: Process exit status type.
// ----------------------------------------------------------------

typedef size_t exit_code_t; /* process exit code */

bool sys_sched_create_process(const char* process_name, size_t type, uid_t uid, gid_t gid, struct sys_process* process);
bool sys_sched_prepare_process(struct sys_process* header, sched_main_t main);

struct sys_thread* sys_sched_thread_create(const char* name, SCHED_TYPE process_type_, struct sched_snapshot* snapshot);

void sys_sched_thread_configure(struct sys_thread* thread, uid_t uid, gid_t gid, pid_t pid);

void sys_sched_yield(void);

void sys_sched_exit(exit_code_t exit_code);
void sys_sched_switch_back(void);

struct sched_snapshot* sys_sched_get_os_snapshot(void);
bool sys_sched_should_switch(void);
size_t sys_sched_start_run(void);

size_t sys_sched_set_root_process(struct sys_process* header);

struct sched_snapshot* sys_get_scheduled_snapshot(void);
int32_t* get_scheduled_time(void);

struct sys_process* sys_get_scheduled_process(void);
struct sys_process* sys_get_root_process(void);

size_t sys_sched_get_exit_code(void);
bool sys_init_sched(void);

bool sys_sched_enabled(void);
void sys_sched_lock(void);
void sys_sched_unlock(void);
bool sys_sched_locked(void);

/* external (assembly) routines */
extern reg_t sys_sched_switch_context(struct sched_snapshot* old, struct sched_snapshot* new_snap);
extern void sys_sched_get_snapshot(struct sched_snapshot* snap);

#define SCHED_EXIT_SUCCESS (0) /* process did perform as intended. */
#define SCHED_EXIT_FAILURE (1) /* failed to complete process, killing it */
#define SCHED_EXIT_DEBUG   (2) /* debug breakpoint hit */
#define SCHED_EXIT_ASSERT  (3) /* assertion failed */

#endif /* ifndef _SYS_SCHED_H */
