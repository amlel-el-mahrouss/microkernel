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

extern Mnumber hypot(libm_complex z);

double cabs(libm_complex z)
{
    return hypot(z);
}

float cabsf(libm_complex z)
{
    return hypot(z);
}

long double cabsl(libm_complex z)
{
    return hypot(z);
}
