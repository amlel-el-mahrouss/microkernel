/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _MPUX_MLD_H
#define _MPUX_MLD_H

#include <hw/cpu.h>
#include <stdint.h>
#include <string.h>
#include <sys/sys.h>
#include <sys/lock.h>
#include <sys/malloc.h>

/* include the pef header */
#include <pef.h>

#define MLD_FAT_MAG 0xFDFE

/**
 * @brief mach loader
 * @file mld.h
 */

/*
 * warning: this is not thread safe.
 * refer to the loader.h instead if you want to load a container.
 */

__BEGIN_DECLS

typedef struct sys_runtime_symbol
{
    /* metadata */
    char_t  s_name[PEF_SYMBOL_LEN];
    uint64_t s_len;

    /* is this a fat binary? */
    union
    {
        struct
        {
            uint16_t s_mag; // MLD_FAT_MAG
            uintptr_t s_dest;
            uintptr_t s_src;
            size_t s_size;
            int      s_arch;
        } s_fat_code;

        bool s_native;
    };

    /* flags and such */
    uint32_t s_flags;

    /* data */
    voidptr_t s_data;
    uint64_t s_data_len;

    struct sys_runtime_symbol* s_prev;
    struct sys_runtime_symbol* s_next;
} sys_runtime_symbol_t;

/*
 * what kind of code is this?
 * can be deduced from command or mld_reloc directive.
 * */
enum CODE_FLAGS
{
    CODE_NORMAL, /* standard code. */
    CODE_SHARED, /* can be shared between programs. */
    CODE_REL, /* code needs to be relocated */
	CODE_PIC, /* Position Independent Code */
    CODE_OFFSET = CODE_PIC, /* mld_reloc is using that. */
    CODE_DIFFERENT_ARCH, /* Code is not our target arch, call mach compiler */
    CODE_STRING, /* This isn't code it contains \", if unterminated abort program. */
	CODE_COUNT,
};

bool sys_free_symbol(struct sys_runtime_symbol* link);
bool sys_link_symbol(struct sys_runtime_symbol* prev, struct sys_runtime_symbol* cur);

size_t sys_symbol_copy(struct sys_runtime_symbol* src, voidptr_t dst, size_t sz);

/* makes a runtime symbol for any future executable that needs it. */
struct sys_runtime_symbol* sys_make_symbol(voidptr_t src, int64_t len, int32_t flags);

/* get symbol data */
voidptr_t sys_get_symbol_data(struct sys_runtime_symbol* rootSymbol, const char* name);

__END_DECLS

#endif // ifndef _MPUX_MLD_H
