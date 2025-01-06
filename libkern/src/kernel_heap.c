/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <memory/kernel_heap.h>
#include <sched/sched.h>
#include <sys/errno.h>
#include <sys/sys.h>
#include <hw/mmap.h>
#include <hw/mmu.h>

/// @file kernel_heap.c
/// @brief Contains the kernel heap.

__COPYRIGHT("$kernel$");

/* last rev 09/11/23 */
/* prev rev 15/04/23 */
/* prev rev 18/04/23 */
/* last rev 12/05/23 */

struct sys_memory_hdr
{
    uint16_t h_magic; /* header magic */
    size_t   h_size; /* header size */
    ptr_t    h_ptr; /* the header's pointer */
    bool     h_used; /* is header used? */
    size_t   h_flags;
    size_t   h_prot;

    struct sys_memory_hdr* h_prev; /* previous header */
    struct sys_memory_hdr* h_next; /* next header */
};

/* @brief base memory header */
static struct sys_memory_hdr* g_base_block = null;

static size_t g_heap_nalloc = 0L;
static size_t g_heap_sz = 0L;

/* declarations */

/* is the heap enabled? */
static bool g_heap_enabled = false;

// internal memory calls
static int32_t sys_alloc_next_mem(struct sys_memory_hdr* block_ptr, struct sys_memory_hdr** ptr_block_ptr);
static voidptr_t sys_alloc_mem_block(struct sys_memory_hdr* header, size_t size, prot_t prot, int32_t map);
static voidptr_t sys_try_mem_block(struct sys_memory_hdr* header, size_t size, prot_t prot, int32_t map);

// memory allocation routines
static voidptr_t sys_alloc(size_t size, prot_t prot, int32_t flags);
static int32_t sys_free(voidptr_t ptr);

// mem stat
static bool sys_mem_enabled(void);
static bool sys_mem_init(void);
static bool sys_mem_disable(void);
static bool sys_mem_enable(void);

/* definitions */

// ----------------------------------------------------------------
// Function: sys_alloc_next_mem
// Purpose: allocates a new header.
// ----------------------------------------------------------------

static int32_t sys_alloc_next_mem(struct sys_memory_hdr* block_ptr, struct sys_memory_hdr** ptr_block_ptr)
{
    block_ptr->h_magic = HEAP_IDENT;
    block_ptr->h_size = 0;
    block_ptr->h_used = false;

    deref(ptr_block_ptr) = (block_ptr + sizeof(struct sys_memory_hdr));

    if (deref(ptr_block_ptr)->h_magic == HEAP_IDENT)
        return -1;

    deref(ptr_block_ptr)->h_prev = block_ptr;
    block_ptr->h_next = deref(ptr_block_ptr);

    return 0;
}

// ----------------------------------------------------------------
// Function: sys_mem_init
// Purpose: heap initialization.
// ----------------------------------------------------------------

static bool sys_mem_init(void)
{
    if (g_heap_enabled)
        return false;

    const int64_t heap_size = __sys_heap_start - __sys_memory_end;
    g_heap_sz = heap_size;

    g_base_block = (voidptr_t)sys_heap_start();

    struct sys_memory_hdr* block_ptr = g_base_block;

    int64_t index = 0UL;

    index = 0UL;

    while (block_ptr != null)
    {
        if ((g_heap_sz - (index * KIB)) < 1024)
            break;

        if (sys_alloc_next_mem(block_ptr, &block_ptr->h_next) == 1)
            break;

        block_ptr = block_ptr->h_next;

        ++index;
    }

    /* reset the previous values, we finished memory detection. */
    g_heap_sz = heap_size;
    g_heap_enabled = true;

    return true;
}

// ----------------------------------------------------------------
// Function: sys_mem_disable
// Purpose: heap disable.
// ----------------------------------------------------------------

static bool sys_mem_disable(void)
{
    if (!g_heap_enabled)
        return false;

    g_heap_enabled = false;

    struct sys_memory_hdr* block_ptr = g_base_block;

    while (block_ptr != null)
    {
        if (block_ptr->h_magic != HEAP_IDENT)
        {
            block_ptr = block_ptr->h_next;
            continue;
        }

        // as we are removing that block from used memory, we don't need zero_memory anymore
        sys_delete_memory(block_ptr->h_ptr, block_ptr->h_size);

        g_heap_sz += block_ptr->h_size;
        g_heap_nalloc -= 1;

        block_ptr->h_magic = HEAP_IDENT;
        block_ptr->h_used = false;
        block_ptr->h_size = 0;

        break;
    }

    g_heap_sz = __sys_heap_start - __sys_memory_end;
    g_heap_nalloc = 0;

    return true;
}

// ----------------------------------------------------------------
// Function: sys_mem_enable
// Purpose: heap disable.
// ----------------------------------------------------------------

static bool sys_mem_enable(void)
{
    if (g_heap_enabled)
        return false;

    g_heap_enabled = true;

    return true;
}

// ----------------------------------------------------------------
// Function: sys_mem_enabled
// Purpose: Is the heap enabled?
// ----------------------------------------------------------------

static bool sys_mem_enabled(void) { return g_heap_enabled; }

// ----------------------------------------------------------------
// Function: sys_alloc_mem_block
// Purpose: Allocates a new header pointer (internal call)
// ----------------------------------------------------------------

static voidptr_t sys_alloc_mem_block(struct sys_memory_hdr* header, size_t size, prot_t prot, int32_t map)
{
    if (!g_heap_enabled)
        return null;

    if (!header->h_used &&
        header->h_magic == HEAP_IDENT)
    {
        header->h_size = size;
        header->h_used = true;

        g_heap_sz -= size;
        g_heap_nalloc += size;

        header->h_ptr = sys_alloc_memory(header, size, prot, map);
        return header->h_ptr;
    }

    return null;
}

// ----------------------------------------------------------------
// Function: sys_try_mem_block
// Purpose: Tries to allocate with this header.
// ----------------------------------------------------------------

static voidptr_t sys_try_mem_block(struct sys_memory_hdr* header, size_t size, prot_t prot, int32_t map)
{
    if (header == null)
        return null;

    return sys_alloc_mem_block(header, size, prot, map);
}

/* each block must align to 4 or 16 bytes */

#if __ARCH__ == __SYS_RISCV__
#   define SYS_ALIGN_BEST_FIT (4)
#elif __ARCH__ == __SYS_AMD64__
#   define SYS_ALIGN_BEST_FIT (16)
#else
#   error Please provide the platform best alignement!
#endif

// ----------------------------------------------------------------
// Function: sys_alloc
// Purpose: Internal allocation function
// ----------------------------------------------------------------

static voidptr_t sys_alloc(size_t size, prot_t prot, int32_t flags)
{
    if (!g_heap_enabled)
        return null;

    if (size < 1)
        return null;

    if (((size % SYS_ALIGN_BEST_FIT) != 0))
    {
        size += SYS_ALIGN_BEST_FIT;
    }
    else
    {
        assert((size % 2) == 0);
    }

#ifdef __KDEBUG__
    IOLogFormat("mem-size: %i\n", size);
#endif

    if (g_heap_sz < size)
    {
        errno = ENOMEM; /* Out of memory! */
        return null;
    }

    voidptr_t return_ptr = null;
    struct sys_memory_hdr* block_ptr = g_base_block;

    /* we gotta loop until it's non-null */
    while (return_ptr == null)
    {
        return_ptr = sys_try_mem_block(block_ptr, size, prot, flags);
    	block_ptr = block_ptr->h_next;
    }

    block_ptr->h_flags = flags;
    block_ptr->h_prot = prot;

    return return_ptr;
}

#undef SYS_MAX_SZ

// ----------------------------------------------------------------
// Function: sys_alloc_ptr
// Purpose: Allocates resource on the heap.
// ----------------------------------------------------------------

voidptr_t sys_alloc_ptr(size_t size, prot_t prot)
{
	if (size < 1)
		return null;

    return sys_alloc(size, prot, SYS_MAP_PRIVATE);
}

// ----------------------------------------------------------------
// Function: sys_alloc_ptr_shared
// Purpose: Allocates shared resource on the heap.
// ----------------------------------------------------------------

voidptr_t sys_alloc_ptr_shared(size_t size, prot_t prot)
{
	if (size < 1)
		return null;

    return sys_alloc(size, prot, SYS_MAP_SHARED);
}

// ----------------------------------------------------------------//
// Function: sys_free                                              //
// Purpose: Free resources on the heap (internal)                  //
// ----------------------------------------------------------------//

static int32_t sys_free(voidptr_t ptr)
{
    struct sys_memory_hdr* block_ptr = g_base_block;

    while (block_ptr != null)
    {
        if (block_ptr->h_magic != HEAP_IDENT ||
            block_ptr->h_ptr != ptr)
        {
            block_ptr = block_ptr->h_next;
            continue;
        }

        // as we are removing that block from used memory, we don't need zero_memory anymore
        sys_delete_memory(block_ptr->h_ptr, block_ptr->h_size);

        g_heap_sz += block_ptr->h_size;
        g_heap_nalloc -= 1;

        block_ptr->h_magic = HEAP_IDENT;
        block_ptr->h_used = false;
        block_ptr->h_size = 0;

        break;
    }

    return 0;
}

// ----------------------------------------------------------------//
// Function: sys_free_ptr                                          //
// Purpose: Free resources on the heap                             //
// ----------------------------------------------------------------//

int32_t sys_free_ptr(voidptr_t ptr)
{
    if (g_heap_enabled)
    {
        errno = sys_free(ptr);
        return errno;
    }

    errno = ENOTSUP;
    return -1;
}

// ----------------------------------------------------------------//
// Function: sys_realloc_ptr                                       //
// Purpose: reallocates a new pointer.                             //
// ----------------------------------------------------------------//

voidptr_t sys_realloc_ptr(voidptr_t ptr, size_t size, prot_t prot)
{
    if (!g_heap_enabled) return null;

    if (ptr == null) return sys_alloc_ptr(size, prot);
    if (size < 1) return ptr;

    struct sys_memory_hdr* header = g_base_block;

    while (header != null)
    {
        if (header->h_magic != HEAP_IDENT)
            goto seek;

        if (header->h_size == size && header->h_ptr == ptr)
	    {
            header->h_size = size;
            return ptr;
        }

        seek:
            header = header->h_next;
    }

    return sys_alloc_ptr(size, prot);
}

// ----------------------------------------------------------------//
// Function: sys_heap_ctl                                          //
// Purpose: heap control                                           //
// ----------------------------------------------------------------//

bool sys_heap_ctl(int cmd, voidptr_t data, size_t* size)
{
	switch (cmd)
	{
	case HEAP_STAT_INIT:
	{
        return sys_mem_init();
    }
    case HEAP_STAT_ENABLE:
    {
        return sys_mem_enable();
    }
    case HEAP_STAT_DISABLE:
	{
        return sys_mem_disable();
    }
	case HEAP_STAT_ENABLED:
	{
        return sys_mem_enabled();
    }
	case HEAP_STAT_STATUS:
	{
        *size = g_heap_sz;
	    return true;
	}
	default:
	    errno = EBADMSG;
	    return false;
	}
}

#include <sys/malloc.h>

// ----------------------------------------------------------------//
// Function: sys_get_mem_info                                      //
// Purpose: allocator info                                         //
// ----------------------------------------------------------------//

void sys_get_mem_info(struct sys_mem_info* inf)
{
    if (inf != null)
    {
        inf->heap_size = g_heap_nalloc;
        inf->heap_left = g_heap_sz;
    }
}
