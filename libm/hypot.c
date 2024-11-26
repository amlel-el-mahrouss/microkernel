/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <sys/cdefs.h>
#include <libm/complex.h>

__COPYRIGHT("$kernel$");

Mnumber hypot(libm_complex z)
{
    return sqrt(pow(z.x, (2+z.y*2)));
}
