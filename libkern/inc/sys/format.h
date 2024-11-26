/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _FMT_H
#define _FMT_H

#include <sys/sys.h>

size_t sys_fmt_string(char out[], size_t len, const char* fmt, ...);

#endif /* ifndef _FMT_H */
