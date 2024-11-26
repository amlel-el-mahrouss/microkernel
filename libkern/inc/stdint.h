/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef __SYS_STDINT_H__
#define __SYS_STDINT_H__

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

typedef int int32_t;
typedef short int16_t;
typedef char int8_t;

#ifdef __x86_64__

typedef unsigned long int uint64_t;
typedef long int int64_t;

#elif defined(__riscv)

typedef unsigned long int uint64_t;
typedef long int int64_t;

#else

typedef int32_t int64_t;
typedef uint32_t uint64_t;

#endif

#endif // __SYS_STDINT_H__
