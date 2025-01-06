/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _MP_MEM_H
#define _MP_MEM_H

#include <sys/sys.h>
#include <string.h>
#include <hw/mmu.h>
#include <sys/log.h>

#define HEAP_STAT_INIT    (0U)
#define HEAP_STAT_ENABLE  (4U)
#define HEAP_STAT_ENABLED (1U)
#define HEAP_STAT_STATUS  (2U)
#define HEAP_STAT_DISABLE (3U)

#define HEAP_IDENT       (0xDEAF)
#define HEAP_MAX_PTR_SZ  (8192 * 16)

typedef voidptr_t ptr_t;

int32_t sys_free_ptr(voidptr_t ptr); /* kernel free */
voidptr_t sys_alloc_ptr_shared(size_t size, prot_t prot); /* shared memory alloc */
voidptr_t sys_alloc_ptr(size_t size, prot_t prot); /* kernel memory alloc */
voidptr_t sys_realloc_ptr(voidptr_t ptr, size_t siz, prot_t prot_t); /* kernel realloc */
bool sys_heap_ctl(int cmd, voidptr_t data, size_t* size); /* heap control */

#endif // !_MP_MEM_H
