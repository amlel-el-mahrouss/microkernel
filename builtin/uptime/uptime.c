/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <uptime/uptime.h>
#include <stddef.h>


/////////////////////////////////////////////////////////////////////////////////

// @file uptime.c
// @brief RTC implementation from kernel

/////////////////////////////////////////////////////////////////////////////////

__COPYRIGHT("$kernel$");

#ifdef __riscv

/* https://www.five-embeddev.com//baremetal/timer/ */

#define RISCV_MTIMECMP_ADDR (0x2000000 + 0x4000)
#define RISCV_MTIME_ADDR    (0x2000000 + 0xBFF8)

/* @brief looks at both time and date registers. */

struct _mpux_time hw_uptime_fetch(void)
{
    struct _mpux_time time;
    time.epoch_time = *((volatile uint64_t*)RISCV_MTIME_ADDR);

    return time;
}

#endif
