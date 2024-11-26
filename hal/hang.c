/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <hw/cpu.h>
#include <sys/sys.h>
#include <mach_thread.h>

extern int64_t __sys_hart_present;

/**
 * @brief Some sort of intermission for harts/cores.
 * Waits here until they have a task.
 */

void __mach_go_hang(void)
{
    ++__sys_hart_present;

    sys_sync_synchronize();

    // TODO: jump to specific mach thread
    while (1)
    {
#ifdef __KMT__
        if (sys_read_hart_id() >= 2)
        {
            mach_spin_threads();
            continue;
        }

        break;
#else
        sys_halt_cpu();
#endif
    }
}
