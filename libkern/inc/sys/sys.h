/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef __SYS_H__
#define __SYS_H__

#ifndef __cplusplus
#define __BEGIN_DECLS
#define __END_DECLS
#else
#define __BEGIN_DECLS extern "C" {
#define __END_DECLS };
#endif

#include <bool.h>

#include <stddef.h>
#include <stdint.h>
#include <assert.h>

#include <hw/cpu.h>
#include <sys/array.h>
#include <sys/endian.h>

__BEGIN_DECLS

#if !__has_attribute(packed) || !__has_attribute(deprecated) || !__has_attribute(aligned) || !__has_attribute(noreturn) || !__has_attribute(noreturn)
#error [kernel] your compiler does not support these attributes!
#endif

#ifdef _POSIX_SOURCE
typedef off_t loff_t;
#endif

/* MP MicroKernel extensions */
#define __FD_TYPE__ long long int
#define __FLAG_TYPE__ unsigned

typedef char char_t;

__END_DECLS

#endif // __SYS_H__
