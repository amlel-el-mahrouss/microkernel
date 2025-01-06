/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _MP_STDDEF_H
#define _MP_STDDEF_H

typedef __SIZE_TYPE__ size_t;

#ifdef __LP64__
typedef long int ssize_t;
#else
typedef int ssize_t;
#endif // __LP64__

typedef size_t ptrdiff_t;
typedef size_t uintptr_t;
typedef void *voidptr_t;
typedef void *any_t;
typedef char *caddr_t;

#ifndef null
#define null ((voidptr_t)0)
#endif // !null

#ifndef nil
#define nil ((voidptr_t)0)
#endif // !null

#define __unix__   (7)
#define __UNIX__   (__unix__)
#define __mpunix__ (__unix__)

#ifdef __MP_NEED_MEASUREMENTS

#define KIB (1024)
#define MIB (1024 * KIB)
#define GIB (1024 * MIB)

#define NS (1000U)
#define MS (NS * 1000U)
#define SECONDS (MS * 1000U)

#endif

#define __offset_of__(STRUCT, FIELD) __builtin_offsetof(STRUCT, FIELD)
#define __deprecated__(MSG) __attribute__((__deprecated__(MSG)))

#ifdef __riscv
#define __SYS_RISCV__ (1)
#elif defined(__x86_64__)
#define __SYS_AMD64__ (2)
#elif defined(__SYS_AARCH64__)
#define __SYS_NC64K__ (2)
#endif

#ifdef __SYS_RISCV__
#define __SYSTEM_ALIGN (4)
#elif defined(__SYS_AMD64__)
#define __SYSTEM_ALIGN (16)
#elif defined(__SYS_AARCH64__)
#define __SYSTEM_ALIGN (16)
#else
#error [kernel] not a valid arch
#endif

#define alloca(sz) __builtin_alloca(sz)
#define deref(ptr) (*(ptr))

#ifdef __cplusplus
#define __decl_begin() extern "C" {
#define __decl_fini() };
#else
#define __decl_begin()
#define __decl_fini()
#endif

#define mpux_no_reach() __builtin_unreachable()

typedef long long off_t;
typedef unsigned long long uoff_t;

typedef union
{
	struct
	{
		unsigned int mantisa : 23;
		unsigned int exponent : 8;
		unsigned int sign : 1;
	};

	float f;
} __attribute__((packed)) float_cast_t;

typedef union
{
	struct
	{
		unsigned long int mantisa : 52;
		unsigned int exponent : 11;
		unsigned int sign : 1;
	};

	double f;
} __attribute__((packed)) double_cast_t;

#define __IDSTRING(name, string) static const char name[] __attribute__((unused)) = string

#ifndef __COPYRIGHT
#define __COPYRIGHT(s) __IDSTRING(copyright, s)
#endif // ifndef __COPYRIGHT

#endif /* _MP_STDDEF_H */
