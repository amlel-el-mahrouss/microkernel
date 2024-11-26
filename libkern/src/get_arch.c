/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <_sys.h>

__COPYRIGHT("$kernel$");

int sys_get_arch(void)
{
    return __ARCH__;
}
