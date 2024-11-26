/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _UXI_H
#define _UXI_H

//
// UNIX Identifier
// <os>.<type>-<id>
//

#include <stdint.h>

typedef int64_t uxi_t;

const char* uxistr(uxi_t uxi, const char* seed);
uxi_t struxi(const char* str);

#endif // _UXI_H
