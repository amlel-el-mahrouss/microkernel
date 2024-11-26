/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef __SYS_FDT_H__
#define __SYS_FDT_H__

/**
 * @file libfdt_env.h
 * @author Amlal EL Mahrouss (amlalelmahrouss@icloud.com)
 * @brief Reimplementation of libfdt_env.h
 * @version 0.1
 * @date 2023-11-14
 *
 * @copyright Copyright (c) 2023 Amlal EL Mahrouss
 *
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/**
 * @brief this macro is used for sparse, we don't use that.
 *
 */

#ifdef __USE_SPARSE__

#	define FDT_FORCE __attribute__((force))
#	define FDT_BITWISE __attribute__((bitwise))

#else

#	define FDT_FORCE
#	define FDT_BITWISE

#endif

typedef uint16_t FDT_BITWISE fdt16_t;
typedef uint32_t FDT_BITWISE fdt32_t;
typedef uint64_t FDT_BITWISE fdt64_t;

#define EXTRACT_BYTE(x, n)	((unsigned long long)((uint8_t *)&x)[n])

#define CPU_TO_FDT16(x) ((EXTRACT_BYTE(x, 0) << 8) | EXTRACT_BYTE(x, 1))

#define CPU_TO_FDT32(x) ((EXTRACT_BYTE(x, 0) << 24) | (EXTRACT_BYTE(x, 1) << 16) | \
			 (EXTRACT_BYTE(x, 2) << 8) | EXTRACT_BYTE(x, 3))




#define CPU_TO_FDT64(x) ((EXTRACT_BYTE(x, 0) << 56) | (EXTRACT_BYTE(x, 1) << 48) | \
			 (EXTRACT_BYTE(x, 2) << 40) | (EXTRACT_BYTE(x, 3) << 32) | \
			 (EXTRACT_BYTE(x, 4) << 24) | (EXTRACT_BYTE(x, 5) << 16) | \
			 (EXTRACT_BYTE(x, 6) << 8) | EXTRACT_BYTE(x, 7))




static inline uint16_t fdt16_to_cpu(fdt16_t x)
{
	return (FDT_FORCE uint16_t)CPU_TO_FDT16(x);
}

static inline fdt16_t cpu_to_fdt16(uint16_t x)
{
	return (FDT_FORCE fdt16_t)CPU_TO_FDT16(x);
}

static inline uint32_t fdt32_to_cpu(fdt32_t x)
{
	return (FDT_FORCE uint32_t)CPU_TO_FDT32(x);
}

static inline fdt32_t cpu_to_fdt32(uint32_t x)
{
	return (FDT_FORCE fdt32_t)CPU_TO_FDT32(x);
}

static inline uint64_t fdt64_to_cpu(fdt64_t x)
{
	return (FDT_FORCE uint64_t)CPU_TO_FDT64(x);
}

static inline fdt64_t cpu_to_fdt64(uint64_t x)
{
	return (FDT_FORCE fdt64_t)CPU_TO_FDT64(x);
}

// we don't need it anymore.
#undef CPU_TO_FDT64
#undef CPU_TO_FDT32
#undef CPU_TO_FDT16
#undef EXTRACT_BYTE

#endif //!__SYS_FDT_H__
