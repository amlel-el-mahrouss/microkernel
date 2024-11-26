/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <sys/thread_local.h>
#include <sched/sched.h>
#include <sys/malloc.h>
#include <sys/errno.h>
#include <sys/lock.h>
#include <string.h>

/* last rev 23/12/23 */

// ----------------------------------------------------------------
// Function: sys_tls_free
// Purpose: frees a user allocated resource.
// ----------------------------------------------------------------

int32_t sys_tls_free(voidptr_t ptr, size_t sz)
{
	if (sz < 1 ||
		ptr == null)
		return -EFAULT;

    if (sz > sys_get_scheduled_process()->p_thread->t_sz_pool)
        return -ERANGE;

    int ret = sys_get_scheduled_process()->p_thread->t_free(sys_get_scheduled_process()->p_thread->t_pool, ptr, sz);

    return ret;
}

// ----------------------------------------------------------------
// Function: sys_tls_protect
// Purpose: places the blue bird bits at the end of the pointer.
// ----------------------------------------------------------------

int32_t sys_tls_protect(voidptr_t ptr, size_t size)
{
    if (ptr == null)
        return -1;

    uintptr_t* bluebird = (uintptr_t*)ptr;

    // the first two bytes are the blue birds which is checked, to detect any memory
    // corruptions on the process's heap.

    bluebird[size + 1] = SYS_BLUE_BIRD_0;
    bluebird[size + 2] = SYS_BLUE_BIRD_1;

    return 0;
}

// ----------------------------------------------------------------
// Function: sys_tls_alloc
// Purpose: allocates a user resource.
// ----------------------------------------------------------------

voidptr_t sys_tls_alloc(size_t size)
{
    if (size < 1) return null;

    voidptr_t ptr = sys_get_scheduled_process()->p_thread->t_malloc(
            sys_get_scheduled_process()->p_thread->t_pool,
            size);

    if (ptr != null)
    {
        sys_tls_protect(ptr, size);
    }
    else
    {
        sys_print_format("[tls] execution error: no more memory left.");
        sys_sched_exit(ENOMEM);
    }

    return ptr;
}

// ----------------------------------------------------------------
// Function: @name sys_tls_protect
// Purpose: @brief places the blue bird bits at the end of the pointer.
// ----------------------------------------------------------------

bool sys_tls_assert(voidptr_t ptr, size_t size)
{
    if (ptr == null)
        return false;

    uintptr_t* bluebird = (uintptr_t*)ptr;

    // the first two bytes are the blue birds which is checked, to detect any memory
    // corruptions on the process's heap.

    if (bluebird[size + 1] != SYS_BLUE_BIRD_0 ||
        bluebird[size + 2] != SYS_BLUE_BIRD_1)
    {
        sys_print_format("[tls] execution_error: heap corruption detected, exiting...");
        sys_sched_exit(-EACCES);
    }

    return true;
}
