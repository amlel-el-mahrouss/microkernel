//
//	========================================================
//
//	    MP MicroKernel
// 	    Copyright Amlal EL Mahrouss, all rights reserved.
//
// ========================================================
//

#ifndef _STDARG_H
#define _STDARG_H

typedef __builtin_va_list __mcc_va_list;
typedef __mcc_va_list va_list;

#define va_start(V, L) __builtin_va_start(V, L)
#define va_end(V) __builtin_va_end(V)
#define va_arg(V, L) __builtin_va_arg(V, L)
#define va_copy(D, S)	__builtin_va_copy(D, S)

#endif // !_STDARG_H
