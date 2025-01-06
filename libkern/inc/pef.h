/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

/**
 * @file pef.h
 * @author Amlal EL Mahrouss
 * @date 16 May 2023
 * @brief Portable Executable Format for MP MicroKernel
 */

#ifndef _MP_PEF_H
#define _MP_PEF_H

#include <sys/sys.h>
#include <machine/exec.h>

#define PEF_MAGIC       "PEF"
#define PEF_MAGIC_FAT   "FEP"
#define PEF_MAGIC_LEN   4

#define PEF_EXEC_EXT    ".out"
#define PEF_DYLIB_EXT   ".lib"
#define PEF_OBJECT_EXT  ".obj"
#define PEF_DEBUG_EXT   ".dbg"

enum PEF_CPU
{
    PEF_CPU_X86S = 100, /* x64 without the x86 */
    PEF_CPU_X86_64, /* x86_64 */
    PEF_CPU_RISCV, /* RISC-V */
    PEF_CPU_POWERPC,
    PEF_CPU_ARM64,
    PEF_CPU_INVALID = 0xFF,
};

enum PEF_KIND
{
    PEF_KIND_EXEC = 1, /* .exec */
    PEF_KIND_SHLIB = 2, /* .shlib */
    PEF_KIND_OBJECT = 4, /* .object */
    PEF_KIND_DEBUG = 5, /* .debug */
};

typedef uintptr_t pef_off_t;

struct pef_exec_header
{
    /* zero terminated ASCII magic */
    char_t   mag[PEF_MAGIC_LEN];
    uint32_t linker; /* linker version */
    uint32_t ver; /* program version */
    uint32_t abi; /* program ABI. */
    uint32_t kind; /* kind of executable */
    uint32_t cpu; /* the cpu we target */
    uint32_t sub_cpu; /* the sub architecture of it. */
    pef_off_t start; /* start code */
    size_t   count; /* container count */
    size_t   size; /* Header size */
    char_t   pad[8]; /* Header padding */
};

#define PEF_SYMBOL_LEN  64

struct pef_command_hdr
{
    char_t    name[PEF_SYMBOL_LEN]; /* command name */
    uint32_t  flags; /* command flags */
    uint16_t  kind; /* command type */
    pef_off_t file_off; /* command file offset */
    size_t    file_sz; /* command file size */
};

/* Our ABI. */
#define PEF_ABI         0xDEAD1
#define PEF_START       "__start"

struct mpux_glob sys_load_exec_glob(const char_t* filename);

#endif /* ifndef _MP_PEF_H */
