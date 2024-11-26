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

Mnumber pow(long double num, long by)
{
    float i;

    for (i = 1; i < by; ++i) {}

    return num * i;
}
