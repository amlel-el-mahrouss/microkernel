/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Date Added: 04/28/2023
 *  Last Edited: 04/09/2023
 *
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * ========================================================
 */

#include <envvar.h>
#include <sys/thread_local.h>
#include <sys/errno.h>
#include <sched/sched.h>

__COPYRIGHT("$kernel$");

// -------------------------------------------------------------------------
// function: getenv
// purpose: Gets the running env value.
// -------------------------------------------------------------------------

static const uint16_t g_args_max = 256;

bool sys_init_env(void)
{
    struct sys_process* proc = sys_get_scheduled_process();

    assert(proc->p_thread != null);

    if (proc == null) return false;
    if (proc->p_thread->t_env != null) return false;

    assert(proc->p_thread->t_malloc != null);

    proc->p_thread->t_env = sys_tls_alloc(sizeof(struct envpath) * g_args_max);

    return true;
}

char* sys_get_env(const char* name)
{
    if (name == null ||
        *name == 0)
    {
        errno = EFAULT;
        return null;
    }

    struct sys_process* proc = sys_get_scheduled_process();

    if (proc == null) return (null);

    for (size_t i = 0; i < proc->p_thread->t_envc; i++)
    {
        if (strncmp(proc->p_thread->t_env[i].e_name, name, strlen(name)) == 0)
        {
            if (strnlen(proc->p_thread->t_env[i].e_value, ENV_VALUE_LEN) < 1)
                return null;

            errno = 0;
            return proc->p_thread->t_env[i].e_value;
        }
    }

    errno = ENOATTR;
    return null;
}

// -------------------------------------------------------------------------
// function: setenv
// purpose: Sets the running env value.
// -------------------------------------------------------------------------

int sys_set_env(const char* name, const char* value)
{
    if (name == null ||
        *name == 0)
    {
        errno = EFAULT;
        return -1;
    }

    if (value == null ||
        *value == 0)
    {
        errno = EFAULT;
        return 2;
    }

    struct sys_process* proc = sys_get_scheduled_process();
    if (proc == null) return -1;

    sys_print_format("%i", proc->p_thread->t_envc);

    for (size_t i = 0; i < proc->p_thread->t_envc; ++i)
    {
        if (strncmp(proc->p_thread->t_env[i].e_name, name, strlen(name)) == 0)
        {
            memncpy(proc->p_thread->t_env[i].e_value, value, strnlen(value, ENV_VALUE_LEN));
            return 0;
        }
    }

    return -1;
}
