/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _SYS_MALLOC_H
#define _SYS_MALLOC_H

#include <memory/kernel_heap.h>

/* memory information */

struct sys_mem_info
{
    size_t heap_size;
    size_t heap_left;
};

void sys_get_mem_info(struct sys_mem_info* inf);

#define kalloc sys_alloc_ptr
#define kfree sys_free_ptr

#endif // _SYS_MALLOC_H
