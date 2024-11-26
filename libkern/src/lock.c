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

#include <sys/lock.h>
#include <sys/malloc.h>

static lock_hdr_t g_mHarts[SYS_MAX_CORES];
static int32_t g_szHarts = 0;
static lock_t* g_pLastLock = null;
static lock_t* g_pCurlock = null;

lock_t* core_lock_acquire(void)
{
    if (g_pCurlock == null)
    {
        g_pCurlock = sys_alloc_ptr(sizeof(lock_t), SYS_PROT_READ | SYS_PROT_WRITE);
        g_pLastLock = g_pCurlock;
    }
    else
    {
        if (*g_pCurlock == 0)
            *g_pCurlock = 1;
    }

    if (g_pCurlock == null)
        mpux_panic("lock_t is null (bug!)\r\n");

    core_lock_notify_acquire(g_pCurlock);
    return g_pCurlock;
}

void core_lock_unlock(lock_t* lock)
{
    if (g_pCurlock == lock) g_pCurlock = null;

    if (lock)
    {
        if (g_pLastLock)
            sys_free_ptr(g_pLastLock);

        g_pLastLock = lock;
        core_lock_notify_free(lock);
    }
}

lock_t* core_lock_get(void) { return g_pCurlock; }
bool core_lock_is_acquired(lock_t* lock) { return lock == g_pCurlock; }

bool core_lock_notify_acquire(lock_t* lock)
{
    if (g_szHarts > SYS_MAX_CORES) return false;

    if (lock != null)
    {
        g_mHarts[g_szHarts].l_lock = lock;

        ++g_szHarts;

        return true;
    }

    IOLog("missed at core_lock_notify_acquire...\r\n");
    return false;
}

bool core_lock_notify_free(lock_t* lock)
{
    if (lock != null)
    {
        --g_szHarts;
        lock = null;

        return true;
    }

    return false;
}

lock_hdr_t* core_lock_get_hart(lock_t* lock)
{
    if (lock == null) return null;

    for (int i = 0; i < SYS_MAX_CORES; i++)
    {
        if (g_mHarts[i].l_lock == lock)
        {
            IOLog("[core_lock_notify_acquire] ok.\r\n");
            return &g_mHarts[i];
        }
    }

    IOLog("[core_lock_notify_acquire] miss...\r\n");
    return null;
}
