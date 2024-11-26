/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Date Added: 09/01/2023 15:25
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 *  System Interface for Multi Processing
 *
 * 	========================================================
 */

#ifndef _LOCK_H
#define _LOCK_H

#include <sys/sys.h>

typedef int64_t lock_t;

typedef struct lock_hdr
{
    sys_snap_t l_snap;
    lock_t* l_lock;
} lock_hdr_t;

lock_t* core_lock_get(void);
lock_t* core_lock_acquire(void);
void core_lock_unlock(lock_t* lock);

bool core_lock_notify_acquire(lock_t* lock);
bool core_lock_notify_free(lock_t* lock);

#endif // ifndef _LOCK_H
