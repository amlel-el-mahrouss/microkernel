/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Date Added: 11/01/2023
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#define sys_sync_synchronize() __sync_synchronize()

#ifdef __GNUC__
	#define attr(attr) __attribute__((attr))
#elif defined(_MSC_VER)
#	define attr(attr)
#	warning __attribute__ not supported on Microsoft Visual C++, please use GCC instead.
#endif
