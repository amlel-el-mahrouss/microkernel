/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

typedef long double Mnumber;

struct _complex_struct_
{
    long double x;
    long double y;
};

#ifndef libm_complex

#   undef I

#   define libm_complex struct _complex_struct_
#   define I (__extension__ 1.0iF)

#endif /* ifndef complex */

#include <sys/cdefs.h>

__BEGIN_DECLS

double cabs(libm_complex z);
float cabsf(libm_complex z);
long double cabsl(libm_complex z);

Mnumber sqrt(long double num);
Mnumber pow(long double num, long by);

__END_DECLS
