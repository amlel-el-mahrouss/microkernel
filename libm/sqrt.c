/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <libm/complex.h>
#include <sys/cdefs.h>

__COPYRIGHT("$kernel$");

extern Mnumber __asm_sqrt(Mnumber in);

Mnumber sqrt(long double num)
{
    return __asm_sqrt(num);
}
