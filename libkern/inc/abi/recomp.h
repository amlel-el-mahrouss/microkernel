/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _MP_RECOMP_H
#define _MP_RECOMP_H

/* EFAT */
#include <sys/errno.h>

/* @file recomp.h */
/* @brief kernel dynamic compiler */

struct sys_opcode_map;

enum MPUX_RECOMP_SOURCE
{
    /* Other RISC computers. */
    MPUX_RECOMP_SOURCE_POWERPC,
    MPUX_RECOMP_SOURCE_RISCV,
    MPUX_RECOMP_SOURCE_MIPS,
    MPUX_RECOMP_SOURCE_SPARC,
    /* NewCPU lineup */
    MPUX_RECOMP_SOURCE_NC32K, // mmu chip
    MPUX_RECOMP_SOURCE_NC64K, // main chip
    MPUX_RECOMP_SOURCE_NC128K, // vector chip
    /* CISC */
    MPUX_RECOMP_SOURCE_AMD64,
    MPUX_RECOMP_SOURCE_M68K,
    /* VM */
    MPUX_RECOMP_SOURCE_JAVA,
};

#endif /* _MP_RECOMP_H */
