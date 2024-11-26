/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

/* This file handles processor and external interrupts */

#include <smp.h>
#include <launchdevil.h>
#include <hw/trap.h>
#include <sys/timer.h>
#include <sched/sched.h>
#include <errno.h>
#include <hw/mmap.h>
#include <system_calls/system_calls.h>

/* some memory offsets */

//////////////////////////////////////////////////////////////////////////////////////////

// @brief RISC-V Interrupt Management.

//////////////////////////////////////////////////////////////////////////////////////////

#define SYS_PLIC_BASE               (sys_get_mmap()[HW_MEMMAP_PLIC].base_ptr) /* plic address in memory */

#define SYS_PLIC_PRIORITY(id, base) (volatile uint32_t*)(SYS_PLIC_BASE + ((id) * 0x4 * base))

#define SYS_PLIC_PENDING(id)        (SYS_PLIC_BASE + 0x1000 + ((id) / 32))

#define SYS_PLIC_MENABLE(hart, base) (SYS_PLIC_BASE + 0x2000 + ((hart) * 0x80 * base / 32))

#define SYS_PLIC_MTHRESHOLD(hart)   (SYS_PLIC_BASE + 0x200000 + (hart) * 0x1000)

#define SYS_PLIC_MCLAIM(hart)       ((SYS_PLIC_BASE + 0x200000 + 0x1000 + 0x4 * hart))

#define SYS_PLIC_MCOMPLETE(hart)    SYS_PLIC_MCLAIM(hart)

/* external interrupts list */

#define SYS_PLIC_IRQ    (11)
#define SYS_UART_IRQ    (10)
#define SYS_VIRTIO_IRQ  (1)

__COPYRIGHT("$kernel$");

/* always keep fields on top of functions for clarity. */
static bool g_enabled = false;

/* main thread register */
reg_t g_thread_pointer = 0;

/* exports list */

extern void sys_timer_handler(void);
extern int64_t __sys_hart_present;

/* end of export list */

uint32_t sys_plic_claim(uint32_t hart)
{
    int irq = *(volatile uint32_t*)SYS_PLIC_MCLAIM(hart);
    return irq;
}

void sys_plic_complete(uint32_t irq, uint32_t hart)
{
    volatile uint32_t* bit = (volatile uint32_t*)SYS_PLIC_MCOMPLETE(hart);
    *bit = irq;
}

// external assembly routine to handle traps.
extern reg_t sys_trap_vector(void);

void sys_trigger_fault(uint32_t cause)
{
    if (sys_get_scheduled_process() != null)
    {
        sys_sched_exit(EFAULT);
    }

    panic("misbehaving_kernel");
}

/**
 * @brief Handles system calls, by setting a fake register frame.
 * And them calls 'sys_dispatch_system_call'
 */
void hw_handle_system_call(void)
{
    struct sched_snapshot* snapshot = sys_get_scheduled_process()->p_thread->t_snapshot;

    sys_snap_t translated_snapshot;

    zero_memory(&translated_snapshot, sizeof(sys_snap_t));

    /* Let's translate the sched snapshot to a syscall snapshot. */
	/* Because it is way easier to give a fake snapshot than the real one. */

    translated_snapshot.a0 = snapshot->s0;
    translated_snapshot.a1 = snapshot->s1;
    translated_snapshot.a2 = snapshot->s2;
    translated_snapshot.a3 = snapshot->s3;
    translated_snapshot.a4 = snapshot->s4;
    translated_snapshot.a5 = snapshot->s5;
    translated_snapshot.a6 = snapshot->s6;
    translated_snapshot.a7 = snapshot->s7;
    translated_snapshot.ra = snapshot->ra;
    translated_snapshot.sp = snapshot->sp;

    sys_dispatch_system_call(&translated_snapshot);
}

extern void virtio_disk_isr(void);

#define SYS_INTERRUPT_EXT   11
#define SYS_INTERRUPT_TIMER 7
#define SYS_INTERRUPT_SOFT  3

/* @brief risc-v interrupt handler. */
void sys_trap_handler(void)
{
    reg_t interrupts = sys_read_mie();
    sys_write_mie(0);

    reg_t hart = sys_read_hart_id();

    reg_t cause = sys_read_mcause() & 0xfff;

    if (((sys_read_mcause() >> 63) & 1)) /* async interrupt */
    {
        switch (cause)
        {
        case SYS_INTERRUPT_SOFT:
        {
            break;
        }
        case SYS_INTERRUPT_TIMER:
        {
            sys_timer_handler();
            break;
        }
        case SYS_PLIC_IRQ:
        {
            int irq = sys_plic_claim(hart);

            switch (irq)
            {
                case SYS_VIRTIO_IRQ:
                {
                    virtio_disk_isr();
                    break;
                }
                default:
                {
                    sys_print_format("[int] not recognized: %i\r\n", irq);
                    break;
                }
            }

            if (irq)
            {
                sys_plic_complete(irq, hart);
            }
        }
        default:
            sys_print_format("[int-ext] not recognized: %i\r\n", cause);
            break;
        }
    }
    else
    {
        switch (cause)
        {
            case 1:
            case 2:
            case 5:
            case 8:
            case 7:
            {
                sys_trigger_fault(cause);
                break;
            }
            case 9:
            case 11:
            {
                hw_handle_system_call();
                break;
            }
            default:
            {
                sys_print_format("[int] unrecognized interrupt: %i\r\n", cause);
                break;
            }
        }
    }

    sys_write_mie(interrupts);
}

//////////////////////////////////////////////////////////////////////////////////////////

bool sys_trap_enabled(void) { return g_enabled; }

// not exported by default, you can get them if you want.

void sys_enable_interrupts(sys_isr_t* ints, size_t cnt)
{
    (void)ints;

    if (cnt == 0)
        return;

    for (size_t i = 0; i < cnt; ++i)
    {
        if (ints[i] == 0xFF)
            break;

        *SYS_PLIC_PRIORITY(g_thread_pointer, ints[i]) = 1;
        *((volatile uint32_t *)SYS_PLIC_MENABLE(g_thread_pointer, ints[i])) = 1;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////

void sys_interrupt_threshold(const int_threshold_t threshold)
{
    (void)threshold;

    *(volatile uint32_t*)SYS_PLIC_MTHRESHOLD(g_thread_pointer) = threshold;
}

// ------------------------------------------- //
// name: sys_init_trap_system
// purpose: trap main function
// ------------------------------------------- //

bool sys_init_trap_system(void)
{
    if (g_enabled)
        return false;

    g_thread_pointer = sys_read_hart_id();

    sys_write_mtvec((reg_t)sys_trap_vector);

    sys_isr_t interrupts[3] = { SYS_VIRTIO_IRQ, SYS_UART_IRQ, 0xFF };

    // enable the following interrupts SYS_UART_IRQ and SYS_VIRTIO_IRQ.
    sys_enable_interrupts(interrupts, 3);

    sys_interrupt_threshold(0);

    sys_write_mie(sys_read_mie() | MIE_MEIE);
    sys_write_mstatus(sys_read_mstatus() | MSTATUS_MIE);

    sys_print_format("[int] thread_pointer at %x\r\n", g_thread_pointer, g_thread_pointer);

    g_enabled = true;
    return true;
}

// ------------------------------------------- //
// name: sys_reset_trap_system
// purpose: trap reset procedure
// ------------------------------------------- //

void sys_reset_trap_system(void)
{
    g_enabled = false;

    sys_write_mie(0);
    sys_write_mstatus(0);
}
