/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _BUILTIN_UPTIME_H
#define _BUILTIN_UPTIME_H

#include <hw/mmap.h>

typedef long rtc_time_t;

/* @brief struct which hols the time results. */
struct _mpux_time
{
    rtc_time_t epoch_time;
    rtc_time_t epoch_date;
};

struct _mpux_time hw_uptime_fetch(void);

#endif /* ifndef _BUILTIN_UPTIME_H */
