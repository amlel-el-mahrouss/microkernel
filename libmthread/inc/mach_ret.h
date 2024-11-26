/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

/* the purpose of this file, is providing an errno equivalent for mach threads. */

#include <sys/sys.h>
#include <sys/errno.h>

extern int64_t g_mach_ret;
