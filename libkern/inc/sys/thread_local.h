/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _SYS_TLS_H
#define _SYS_TLS_H

#include <sys/sys.h>

#define SYS_BLUE_BIRD_0 (0x110)
#define SYS_BLUE_BIRD_1 (0x101)

/* adds the blue bird bits, if specified by fmt 'bluebird command' */
int32_t sys_tls_protect(voidptr_t ptr, size_t size);
bool sys_tls_assert(voidptr_t ptr, size_t size);

/* tls routine for the current process */
int32_t sys_tls_free(voidptr_t ptr, size_t sz);
voidptr_t sys_tls_alloc(size_t size);

#endif // !_SYS_TLS_H
