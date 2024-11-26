/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Date Edited: 16/01/2023 21:52
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <abi/mld.h>
#include <sys/errno.h>

__COPYRIGHT("$kernel$");

/* @brief Linked List helpers */
#define sys_get_next(LL)         (LL->s_next)
#define sys_get_prev(LL)         (LL->s_prev)
#define sys_get_data(LL)         (LL->s_data)
#define sys_has_flag(LL, TYP)    (TYP & LL->s_flags)
#define sys_add_flag(LL, TYP)    (LL->s_flags |= TYP)

bool sys_free_symbol(struct sys_runtime_symbol* sym)
{
    if (sym == null)
        return false;

    sys_free_ptr(sym->s_data);
    sys_free_ptr(sym);

    return true;
}

size_t sys_symbol_copy(struct sys_runtime_symbol* src, voidptr_t where, size_t sz)
{
    if (src != null && where != null && sz <= src->s_data_len)
    {
        return memncpy(where, src->s_data, sz);
    }

    return ~0;
}

bool sys_link_symbol(struct sys_runtime_symbol* prev, struct sys_runtime_symbol* cur)
{
    if (prev != null &&
        cur != null &&
        prev->s_next == null &&
        cur->s_prev == null)
    {
        cur->s_prev = prev;
        prev->s_next = cur;

        cur->s_prev->s_next = cur;
        prev->s_next->s_prev = prev;

        return true;
    }

    return false;
}

struct sys_runtime_symbol* sys_make_symbol(voidptr_t src, int64_t len, int32_t flags)
{
    struct sys_runtime_symbol* sym = sys_alloc_ptr(sizeof(struct sys_runtime_symbol), SYS_PROT_READ | SYS_PROT_WRITE);

    if (sym != null)
    {
        /*  fill out the newly allocated memory struct. */
        sym->s_data = src;
        sym->s_data_len = len;
        sym->s_flags |= flags;

        return sym;
    }

    return null;
}

// ----------------------------------------------------------------
// Function: sys_get_symbol_data
// Purpose: N/A
// ----------------------------------------------------------------

voidptr_t sys_get_symbol_data(struct sys_runtime_symbol* rootSymbol, const char* name)
{
    if (*name == 0 || rootSymbol == null) return null;

    struct sys_runtime_symbol* start_sym = rootSymbol;

    while (start_sym != null && start_sym->s_data_len > 0)
    {
        if (strncmp(start_sym->s_name, name, start_sym->s_len) == 0)
            return start_sym->s_data;

        start_sym = sys_get_next(start_sym);
    }

    return null;
}

#undef sys_get_next
#undef sys_get_prev
#undef sys_get_data
#undef sys_has_flag
#undef sys_add_flag
