/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef __SYS_STDARG_H__
#define __SYS_STDARG_H__

typedef __builtin_va_list __sys_va_list;
typedef __sys_va_list va_list;

#define va_start(V, L) __builtin_va_start(V, L)
#define va_end(V) __builtin_va_end(V)
#define va_arg(V, L) __builtin_va_arg(V, L)
#define va_copy(D, S)	__builtin_va_copy(D, S)

#endif // !__SYS_STDARG_H__
