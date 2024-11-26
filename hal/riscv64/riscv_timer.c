/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <sys/timer.h>
#include <hart_ipi.h>
#include <hw/cpu.h>
#include <sys/log.h>

#ifndef _HAL_TIMER
#define _HAL_TIMER (*(volatile int64_t*)(CLINT_MTIMECMP(g_thread_pointer)))
#endif // !_HAL_TIMER

extern reg_t g_thread_pointer;

static reg_t g_timer_scratch[_LIBHART_MAX][5];

void sys_timer_init(void)
{
    int id = g_thread_pointer;

    // prepare information in scratch[] for timervec.
    // scratch[0..2] : space for timervec to save registers.
    // scratch[3] : address of CLINT MTIMECMP register.
    // scratch[4] : desired SYS_INTERVAL_CLK (in cycles) between timer interrupts.

    reg_t* scratch = g_timer_scratch[id];

    scratch[3] = CLINT_MTIMECMP(id);
    scratch[4] = SYS_TIMER_INTERVAL;

    sys_write_mscratch((reg_t)scratch);

    // enable machine-mode timer interrupts.
    sys_write_mie(sys_read_mie() | MIE_MTIE);

    // trigger timer interrupt
    _HAL_TIMER = CLINT_MTIME + SYS_TIMER_INTERVAL;
}

// ----------------------------------------------------------------
// Function: sys_timer_handler
// Purpose: CLINT interrupt.
// ----------------------------------------------------------------

void sys_timer_handler(void)
{
    sys_write_mie(sys_read_mie() & ~MIE_MTIE);

    _HAL_TIMER = CLINT_MTIME + SYS_TIMER_INTERVAL;

    sys_write_mie(sys_read_mie() | MIE_MTIE);
}

const duration_t sys_get_time(void)
{
    int32_t id = g_thread_pointer;
    return CLINT_MTIMECMP(id);
}

void sys_sleep_for(duration_t ms)
{
    if (ms < 1)
        return;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"

    volatile uintptr_t* timer = (volatile uintptr_t*)CLINT_MTIMECMP(g_thread_pointer);
    *timer = ms;

#pragma GCC diagnostic pop
}
