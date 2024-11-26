/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <errno.h>

error_t __errno = 0;

error_t sys_get_errno(void) { return __errno; }
