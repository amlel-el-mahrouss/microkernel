/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <hw/mmap.h>
#include <hw/cpu.h>
#include <hw/trap.h>
#include <sys/dev.h>
#include <sys/ext.h>
#include <sched/sched.h>
#include <memory/kernel_heap.h>

#define HW_POWEROFF (0x5555)
#define HW_REBOOT   (0x7777)

__COPYRIGHT("$kernel$");

/**
 * @brief Has rebooting been requested?
 */
bool g_reboot_requested = false;


/**
 * @brief Has shutdown been requested?
 */
bool g_shutdown_requested = false;

/**
 *
 * @brief does the steps needed before going down.
 */

static void hw_system_poweroff(void)
{
    sys_unload_ext();
    sys_reset_device_system();
    sys_reset_trap_system();
    sys_heap_ctl(HEAP_STAT_DISABLE, null, null);
}


///////////////////////////////////////////////////////////////////////

// @brief Power-off the motherboard.

///////////////////////////////////////////////////////////////////////

void sys_request_poweroff(void)
{
    g_shutdown_requested = true;

    hw_system_poweroff();

    struct sys_hw_memmap* memmap = sys_get_mmap();

    g_shutdown_requested = false;

    /* code 255 doesn't do any reboot, it does the shutdown as intended. */
    *(volatile uint32_t *)memmap[HW_MEMMAP_RESR].base_ptr = HW_POWEROFF;

    while (1)
        sys_halt_cpu();
}

///////////////////////////////////////////////////////////////////////

// @brief does a cold reboot of the machine.

///////////////////////////////////////////////////////////////////////


extern int64_t __sys_hart_present;

void sys_request_reboot(void)
{
    g_reboot_requested = true;

    hw_system_poweroff();

    struct sys_hw_memmap* memmap = sys_get_mmap();

    __sys_hart_present = 0;

    /* should be captured by hardware, which will cause a reboot */
    *(volatile uint32_t *)memmap[HW_MEMMAP_RESR].base_ptr = HW_REBOOT;

    while (1)
        sys_halt_cpu();
}
