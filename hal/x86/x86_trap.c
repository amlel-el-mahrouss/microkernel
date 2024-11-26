/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <hw/trap.h>

/* other includes needed for x86 traps */
#include <sched/sched.h>
#include <system_calls/system_calls.h>

typedef struct sys_idt
{
    uintptr_t reg_base;
    size_t reg_len;
} sys_idt_t;

typedef struct sys_idt_hook
{
    int32_t interrupt_id; /* interrupt identifier */
    void(*interrupt_hook)(struct _sys_snap* sf); /* interrupt function */
} sys_idt_hook_t;

static bool g_enabled = false;

void sys_trigger_fault(struct sys_snap_t* snap)
{
    struct sys_process* current_process = sys_get_scheduled_process();

    if (current_process == nil)
    {
        panic("kernel_fault");
    }

    if (sdctl_has_flag(current_process->p_sdctl, SD_ACCESS_SUPER))
    {
        sys_print_format("caused by: %s\r\n", sys_get_scheduled_process()->p_thread->t_name);
        panic("misbehaving_kernel_process");
    }

    sys_sched_exit(-3);
}

sys_idt_t g_sys_idtr = { 0, 0 };

bool sys_init_trap_system(void)
{
    if (g_enabled)
        return false;

    __asm__ volatile ("cli"); //! pause cpu

    const void* mem = (const void*)&g_sys_idtr;

    __asm__ volatile ("lidt %0" : : "m"(mem)); // load the new IDT.

    __asm__ volatile ("sti"); //! resume it

    g_enabled = true;
    return true;
}
