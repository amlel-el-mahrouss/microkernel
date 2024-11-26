/*
 *	========================================================
 *
 *  MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <system_calls/system_call_impl.h>
#include <pef.h>

// -------------------------------------------------------------------------
// function: do_exit
// purpose: exits the current process.
// -------------------------------------------------------------------------

void do_exit(int code)
{
    sys_sched_exit(code);
}

//////////////////////////////////////////////////////////////////////////

// @brief Sleeps for an amount of seconds.

//////////////////////////////////////////////////////////////////////////

void do_sleep(int64_t seconds) { sys_sleep_for(seconds); }

//////////////////////////////////////////////////////////////////////////

// -------------------------------------------------------------------------
// function: do_execve
// purpose: executes from the path and more arguments such
// as argv and envp.
// -------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////

int do_execve(const char *path, char* const argv[], char *const envp[])
{
    // TODO: call mld server.

    return -1;
}

//////////////////////////////////////////////////////////////////////////

// -------------------------------------------------------------------------
// function: do_exec
// purpose: executes from the path.
// -------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////

int do_exec(const char* path)
{
    char* const envp[] = {
        "/bin/",
        "/usr/bin/",
        "/usr/local/bin/",
        "/usr/sbin/",
        "/usr/local/sbin/",
    };

    return do_execve(path, null, envp);
}

//////////////////////////////////////////////////////////////////////////

// @brief ioctl system call

//////////////////////////////////////////////////////////////////////////

int do_ioctl(int id, int cnt, voidptr_t val) { return 0; }


//////////////////////////////////////////////////////////////////////////

// @brief sysctl call

//////////////////////////////////////////////////////////////////////////

int do_sysctl(const char* name, int cnt, voidptr_t val) { return 0; }
