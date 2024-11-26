/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <mach_thread.h>
#include <sys/errno.h>
#include <sys/lock.h>
#include <sys/attr.h>
#include <sys/format.h>
#include <smp.h>

#define SMP_BUFFER_SIZE 32

__COPYRIGHT("$kernel$");

////////////////////////////////////////////////////////////////////////////////

// @brief Symmetric Multi Processing.

////////////////////////////////////////////////////////////////////////////////

bool g_smp_taken = false;
bool g_smp_stop = false;

int32_t g_smp_err = 0;

extern int64_t __sys_hart_present;
extern bool g_shutdown_requested;
extern bool g_reboot_requested;

static struct sys_cpu_desc g_smp_desc[SYS_MAX_CORES] = {};
static bool g_smp_enabled = false;
static size_t g_smp_counter = 0UL;

char_t* g_smp_last_stack = null;
char_t* g_smp_stack_list[SYS_MAX_CORES];

// @brief waits and context switch any harts that needs that.

static int32_t mach_smp_context_switch(struct sys_cpu_desc* descp)
{
    while (sys_get_scheduled_process() == null ||
        sys_get_scheduled_process()->p_thread == null)
    {}

    if (descp->machine_mode == false &&
        sys_get_scheduled_process()->p_sdctl.access == SD_ACCESS_SUPER)
    {
        return 0;
    }

    while (sys_sched_locked()) {}

    if (sys_sched_should_switch())
    {
        sys_sched_switch_back();
    }

    return g_smp_err;
}

bool mach_is_smp_enabled(void)
{
    return g_smp_enabled;
}

void mach_stop_sched_smp(void)
{
    if (!g_smp_stop)
        g_smp_stop = true;
}

// @brief prepare the hart to spin for any task which ends its schedule time.

int mach_start_sched_smp(void)
{
    sys_sync_synchronize();

    while (!sys_sched_enabled()) {}
    while (g_smp_taken) {}

    g_smp_taken = true;

    sys_print_format("[smp] hart %i\n", sys_read_hart_id());

    if (!g_smp_enabled)
        g_smp_enabled = true;

    g_smp_stop = false;

    g_smp_desc[g_smp_counter].cpu_id = sys_read_hart_id();
    g_smp_desc[g_smp_counter].machine_mode = true;
    g_smp_desc[g_smp_counter].used = true;

    char fmt[32];
    sys_fmt_string(fmt, SMP_BUFFER_SIZE, "hart%i", g_smp_counter + 1);

    memncpy(g_smp_desc[g_smp_counter].name, fmt, 32);

    sys_sched_get_snapshot(&g_smp_desc[g_smp_counter].hart_snap);

    ++g_smp_counter;

    struct sys_cpu_desc* descp = &g_smp_desc[g_smp_counter - 1];

    while (!g_smp_stop)
    {
        mach_smp_context_switch(descp);
    }

    g_smp_enabled = false;
    g_smp_taken = false;

    return g_smp_err;
}

#include <sys/errno.h>

/*
 * function: mach_smp_sched_hart_recv
 * purpose: libhart receive packet handler
 * last edited: N/A
 */

void mach_smp_sched_hart_recv(struct hart_msg* msg)
{
    if (msg != null &&
        msg->m_from != sys_read_hart_id())
    {
        do
        {
            // pointer check in order to not trigger a load_fault.
            if (msg == null)
                return;
        } while (msg->m_to != sys_read_hart_id());

        switch (msg->m_msg)
        {
        default:
            errno = ENOTSUP;
            break;
        }
    }

    errno = EFAULT;
}

#undef SMP_BUFFER_SIZE

/// @brief control mach thread.
/// @param hart the hardware thread.
/// @param flag flag to look for.
/// @param ... varargs.
void mach_ctl(int hart, int flag, ...)
{
    for (size_t i = 0; i < SYS_MAX_CORES; i++)
    {
        if (g_smp_desc[i].cpu_id == hart)
        {
            switch (flag)
            {
            case M_USER_MODE:
                g_smp_desc[i].machine_mode = !g_smp_desc[i].machine_mode;
                break;

            case M_USE:
                g_smp_desc[i].used = !g_smp_desc[i].used;
                break;

            default:
                break;
            }

            return;
        }
    }

}
