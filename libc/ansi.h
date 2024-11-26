//
//	========================================================
//
//	    MP MicroKernel
// 	    Copyright Amlal EL Mahrouss, all rights reserved.
//
// ========================================================
//

#ifndef _ANSI_H
#define _ANSI_H

#if __STDC__ == 1
#   define _ANSI (31459)
#endif

#ifdef __GNUC__
#   define _ANSI (31459)
#endif

#ifdef _ANSI

#define _PROTOYPE(function, params) function params
#define _ARGS(params) params

#define _VOIDSTAR void*
#define _VOID void

#define _CONST const
#define _VOLATILE volatile

#define _SIZE_T __SIZE_TYPE__

#else

#define _PROTOYPE(function, params) function()
#define _ARGS(params) ()

#define _VOIDSTAR void*
#define _VOID void

#define _CONST
#define _VOLATILE

#define _SIZE_T int

#endif // _ANSI

#define _RESTRICT

#endif // ifndef _ANSI_H
