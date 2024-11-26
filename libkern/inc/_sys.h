/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * ========================================================
 */

#pragma once

#include <stddef.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <envvar.h>
#include <sys/errno.h>
#include <machine/exec.h>
#include <sys/malloc.h>
#include <sys/fd.h>
#include <stdio.h>
#include <sys/pipe.h>
#include <strerror.h>
#include <sys/stat.h>

__BEGIN_DECLS

#define ARCH_BAD    (~0)
#define ARCH_RISCV64 (1U)
#define ARCH_AMD64 (2U)

int sys_get_arch(void);

typedef struct cstr cstr_t;

#ifdef __SYS_RISCV__
#   define __ARCH__ __SYS_RISCV__
#elif defined(__SYS_AMD64__)
#   define __ARCH__ __SYS_AMD64__
#else
#   define __ARCH__ (0xFFFF)
#endif

__END_DECLS
