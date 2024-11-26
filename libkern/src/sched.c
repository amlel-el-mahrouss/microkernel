/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <sched/sched.h>
#include <sys/errno.h>
#include <hw/cpu.h>
#include <kernel.h>
#include <smp.h>

/////////////////////////////////////////////////////////////////////////////////

// @file sched.c
// @brief Completely Unfair Scheduler

// A modified round-robbin algorithm to accept 'affinity' and multicore task switching.

// Maintainer: amlel

/////////////////////////////////////////////////////////////////////////////////

#ifndef SCHED_DEFAULT_AFFINITY
#define SCHED_DEFAULT_AFFINITY  (SCHED_AFFINITY_MEDIUM)
#endif /* ifndef SCHED_DEFAULT_AFFINITY */

static struct sched_snapshot*   g_current_snapshot = null;
static struct sys_process*      g_current_process = null;
static struct sys_process*      g_root_process = null;
static int32_t*                 g_time_share = null;
static bool                     g_enabled = false;

static struct sched_snapshot    g_os_snapshot = {};

static bool                     g_exit_requested = false;
static pid_t                    g_pid_counter = 0;
static size_t                   g_last_exit = 0;
static bool                     g_locked = false;

static void sys_sched_increment_pid(void)
{
    if (g_pid_counter < SCHED_PID_MAX)
       ++g_pid_counter;
}

static void sys_sched_decrement_pid(void)
{
    --g_pid_counter;

    if (g_pid_counter < 1)
        g_pid_counter = 0;
}

bool sys_sched_enabled(void) { return g_enabled; }

int32_t* get_scheduled_time(void) { return g_time_share; }

struct sys_process* sys_get_scheduled_process(void) { return g_current_process; }

struct sched_snapshot* sys_get_scheduled_snapshot(void) { return g_current_snapshot; }

struct sys_process* sys_get_root_process(void) { return g_root_process; }

// -------------------------------------------------------------------------
// function: sched_create_process
// purpose: N/A
// -------------------------------------------------------------------------

bool sys_sched_create_process(const char* proc_name, size_t type, uid_t uid, gid_t gid, struct sys_process* process)
{
    if (process == null) return false;

    struct sched_snapshot* snapshot = sys_alloc_ptr(sizeof(struct sched_snapshot), SYS_PROT_READ | SYS_PROT_WRITE);
    assert(snapshot != null);

    struct sys_thread* thread = sys_sched_thread_create(proc_name, type, snapshot);
    assert(thread != null);

    sys_sched_thread_configure(thread, uid, gid, g_pid_counter);

    process->p_sdctl.access = uid == g_kuid ? SD_ACCESS_SUPER : SD_ACCESS_STANDARD;
    process->p_sdctl.type = SD_TYPE_PROC;

    process->p_thread = thread;
    process->p_thread->t_snapshot = snapshot;

    buf_t* buf_in = sys_make_buffer(sys_alloc_ptr(sizeof(char) * PIPE_PROC_LENGTH, SYS_PROT_READ | SYS_PROT_WRITE),
                                    PIPE_PROC_LENGTH);

    buf_t* buf_out = sys_make_buffer(sys_alloc_ptr(sizeof(char) * PIPE_PROC_LENGTH, SYS_PROT_READ | SYS_PROT_WRITE),
                                    PIPE_PROC_LENGTH);

    process->p_pipe = sys_make_pipe(proc_name, strlen(proc_name), buf_in, buf_out);

    assert(process->p_pipe != null);

    sys_sched_increment_pid();

    return true;
}

// -------------------------------------------------------------------------
// function: sys_sched_prepare_process
// purpose: N/A
// -------------------------------------------------------------------------

bool sys_sched_prepare_process(struct sys_process* process, sched_main_t main)
{
    if (process != null &&
        process->p_thread != null &&
        process->p_thread->t_snapshot != null &&
        main != null)
    {
        process->p_thread->t_stack = sys_alloc_ptr(sizeof(char) * SCHED_STACK_SIZE, SYS_PROT_READ | SYS_PROT_WRITE);

        //! the rest will be on disk
        process->p_thread->t_pool = sys_alloc_ptr(sizeof(char) * SCHED_POOL_SIZE, SYS_PROT_READ | SYS_PROT_WRITE);

        process->p_thread->t_entrypoint = (reg_t)main;
        process->p_thread->t_snapshot->ra = (reg_t)process->p_thread->t_entrypoint;

        process->p_thread->t_snapshot->sp = (reg_t)&process->p_thread->t_stack[SCHED_STACK_SIZE - 1];

        return true;
    }

    return false;
}

// -------------------------------------------------------------------------
// function: sys_sched_get_exit_code
// purpose: N/A
// -------------------------------------------------------------------------

size_t sys_sched_get_exit_code(void) { return g_last_exit; }

/* scheduler locking utilities */

void sys_sched_lock(void)
{
#if defined(__KSIMP__) || defined(__KMT__)
    g_locked = true;
#endif
}

void sys_sched_unlock(void)
{
#if defined(__KSIMP__) || defined(__KMT__)
    g_locked = false;
#endif
}

bool sys_sched_locked(void) { return g_locked; }

/* check if process's time is out */

bool sys_sched_should_switch(void)
{
    if (!g_enabled) return false;
    if (g_root_process == null) return false;

    int32_t* timeout = get_scheduled_time();
    assert(timeout != null);

    *timeout -= 1;
    return *timeout < 1;
}

bool sys_init_sched(void)
{
    if (g_time_share == null)
        g_time_share = sys_alloc_ptr(sizeof(int32_t), SYS_PROT_READ | SYS_PROT_WRITE);

    if (g_time_share == null)
        return false;

    *g_time_share = SCHED_DEFAULT_AFFINITY;

    // finally enable it
    g_enabled = true;

    return true;
}

// ----------------------------------------------------------------
// Function: sys_sched_get_os_snapshot
// Purpose: gets the operating system snapshot.
// ----------------------------------------------------------------

struct sched_snapshot* sys_sched_get_os_snapshot(void) { return &g_os_snapshot; }

// ----------------------------------------------------------------
// Function: sys_sched_switch_back
// Purpose: checks if the process should context switch.
// ----------------------------------------------------------------

void sys_sched_switch_back(void)
{
#ifdef __SYS_RISCV__
    if (g_current_snapshot == null || g_os_snapshot.ra == 0)
        return;
#elif defined(__SYS_AMD64__)
    if (g_current_snapshot == null || g_os_snapshot.rax == 0)
        return;
#endif

    sys_sched_switch_context(g_current_snapshot, &g_os_snapshot);
}

// ----------------------------------------------------------------
// Function: sys_sched_check_process
// Purpose: checks the scheduled process.
// ----------------------------------------------------------------

bool sys_sched_check_process(struct sys_process* process)
{
    if (process == null)
        return false;

    if (sched_process_stopped(process->p_thread->t_status))
        return false;

    if (process->p_thread == null)
        return false;

    if (process->p_thread != null)
        return true;

    return false;
}

// ----------------------------------------------------------------
// Function: sys_sched_exit
// Purpose: Exits the scheduled process.
// ----------------------------------------------------------------

void sys_sched_exit(exit_code_t exit_code)
{
    while (sys_sched_locked()) {}
    sys_sched_lock();

    g_last_exit = exit_code;
    g_exit_requested = true;

    sys_sched_decrement_pid();

    for (size_t i = 0; i < sys_get_scheduled_process()->p_fd_cnt; i++)
    {
        sys_close(sys_get_scheduled_process()->p_fd[i]);
    }

    sys_get_scheduled_process()->p_fd_cnt = 0;

    sys_free_ptr(sys_get_scheduled_process()->p_thread->t_pool);
    sys_get_scheduled_process()->p_thread->t_pool = nil;

    sys_sched_unlock();
    sys_sched_switch_back();
}

// ----------------------------------------------------------------
// Function: sys_start_sched
// Purpose: Schedules any pending process.
// ----------------------------------------------------------------

size_t sys_start_sched(void)
{
    size_t scheduled_count = 0UL;
    struct sys_process* process = g_root_process;

    while (process != null)
    {
        if (sys_sched_check_process(process))
        {
            while (sys_sched_locked());

            sys_sched_lock();

            g_current_process = process;

            g_current_snapshot = process->p_thread->t_snapshot;
            *g_time_share = process->p_thread->t_affinity;

            sys_sched_unlock();

            //! assign user ra to epc for user switch.
            process->p_thread->t_snapshot->mepc = process->p_thread->t_snapshot->ra;

            sys_sched_switch_context(&g_os_snapshot, process->p_thread->t_snapshot);

            /*
             * if we wish to exit
             * lock and do the exit.
             */

            if (g_exit_requested)
            {
                /// never let bro forgot to free his stuff!!!
                sys_free_ptr(process->p_thread->t_snapshot);
                process->p_thread->t_snapshot = nil;

                process->p_thread->t_status = SCHED_STATUS_STOPPED;

                sys_free_ptr(process->p_thread->t_stack);
                process->p_thread->t_stack = null;

                sys_free_ptr(process->p_thread);
                process->p_thread = null;


                g_exit_requested = false;

                struct sys_process* process_cpy = process;

                process->p_next->p_prev = process->p_prev;
                process->p_prev->p_next = process->p_next;

                process = process->p_next;

                sys_free_ptr(process_cpy);

                continue; // don't mark exiting process as scheduled.
            }

            process = process->p_next;
            ++scheduled_count;
        }
    }

    sys_sched_unlock();
    return scheduled_count;
}

size_t sys_sched_set_root_process(struct sys_process* process)
{
    if (g_enabled == false) return 0;
    if (process == null) return 1;

    g_root_process = process;

    return 0;
}

size_t sys_sched_start_run(void)
{
    assert(g_enabled);
    assert(g_root_process != null);

    size_t n_scheduled = 1;
    size_t schedule_total = 0;

    while (g_enabled)
    {
        if (n_scheduled < 1)
            break;

        n_scheduled = sys_start_sched();
        schedule_total += n_scheduled;
    }

    return schedule_total;
}

void sys_sched_yield(void)
{
    while (sys_sched_locked());
    sys_sched_lock();

    struct sys_process* process_header = g_current_process;

    while (process_header != null)
    {
        if (process_header->p_next == null)
            break;

        process_header = process_header->p_next;
    }

    if (process_header != null)
    {
        process_header->p_next = g_current_process;

        g_current_process->p_prev->p_next = g_current_process->p_next;
        g_current_process->p_next->p_prev = g_current_process->p_prev;

        g_current_process->p_prev = process_header;
        g_current_process->p_next = null;
    }

    sys_sched_unlock();

    if (process_header != null)
        sys_sched_switch_back();
}

struct sys_thread* sys_sched_thread_create(const char* name, SCHED_TYPE thread_type, struct sched_snapshot* snapshot)
{
    while (sys_sched_locked());
    sys_sched_lock();

	struct sys_thread* thread = sys_alloc_ptr(sizeof(struct sys_thread), SYS_PROT_READ | SYS_PROT_WRITE);
	assert(thread != null);

	thread->t_status = SCHED_STATUS_ZOMBIE; // just a zombie for now
	thread->t_type = thread_type; // set thread type according to user boolean
	thread->t_snapshot = snapshot;

	memncpy(thread->t_name, name, SCHED_NAME_LEN); // copies the name into thread;

    sys_sched_unlock();
	return thread;
}

// --------------------------------------------------------------------------------------
// function: sys_sched_thread_configure
// purpose: configures a thread with its associate permissions and affinity...
// --------------------------------------------------------------------------------------

void sys_sched_thread_configure(struct sys_thread* thread, uid_t uid, gid_t gid, pid_t pid)
{
    while (sys_sched_locked());
    sys_sched_lock();

    assert(thread);

    thread->t_affinity = SCHED_AFFINITY_MEDIUM;
    thread->t_status = SCHED_STATUS_STARTING;

    thread->t_gid = gid;
    thread->t_uid = uid;
    thread->t_pid = pid;

    sys_sched_unlock();
}

/// END OF CUS.
