/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <sys/sys.h>
#include <sys/attr.h>
#include <sys/malloc.h>

struct attr(packed) sys_pte_64
{
    bool present : 1;
    bool rw : 1;
    bool user : 1;
    bool wt : 1;
    bool cache : 1;
    bool accessed : 1;
    int32_t resv : 6;
    uintptr_t paddr : 36;
    int32_t resv1 : 15;
    bool execd : 1;
};

const uintptr_t sys_heap_start(void) { return __sys_heap_start; }
