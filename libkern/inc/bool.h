/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef __SYS_BOOL_H__
#define __SYS_BOOL_H__

#ifndef __cplusplus

#define bool uint8_t
#define true 1
#define false 0

#else

#ifdef __SYS_WARN_BOOL_CXX
#   warning You are using C++ this include is not needed.
#endif // __SYS_WARN_BOOL_CXX

#endif // !__cplusplus

#endif // !__SYS_BOOL_H__
