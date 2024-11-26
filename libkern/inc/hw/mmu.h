/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _HW_MMU_H
#define _HW_MMU_H

#include <sys/sys.h>

typedef size_t prot_t;

#if defined(__SYS_RISCV__)

#ifndef RISCV_PAGE_SIZE
#define RISCV_PAGE_SIZE (512U) /* Page-Based 48-bit Virtual-Memory System */
#endif /* ifndef !RISCV_PAGE_SIZE */

#define RISCV_PERM_PAGE_PTR         (0b000)
#define RISCV_PERM_READ             (0b001)
#define RISCV_PERM_WRITE            (0b010)
#define RISCV_PERM_RESERVED         (0b010)
#define RISCV_PERM_RW               (0b011)
#define RISCV_PERM_EXEC             (0b100)
#define RISCV_PERM_EXEC_WRITE       (0b101)
#define RISCV_PERM_RESERVED_FUTURE  (0b110)
#define RISCV_PERM_RWX              (0b111)

#define SATP_MODE_OFF   0
#define SATP_MODE_SV32   1
#define SATP_MODE_SV39   8
#define SATP_MODE_SV48   9
#define SATP_MODE_SV57   10
#define SATP_MODE_SV64   11

#define __PAGE_SIZE__ RISCV_PAGE_SIZE

void sys_set_satp(voidptr_t pool_ptr, prot_t prot);

struct sys_page_table_entry;

typedef uintptr_t sv48_vaddr_t;
typedef uintptr_t sv48_paddr_t;
typedef uint8_t sv48_gran_t;

struct sys_page_table_entry
{
    sv48_gran_t gran;
};

#define sys_map_page sys_set_satp

#elif defined(__SYS_AMD64__)

#ifndef AMD64_PAGE_SIZE
#define AMD64_PAGE_SIZE (512UL) /* 64-bit paging and 48-bit memory addressing  */
#endif // !AMD64_PAGE_SIZE

#define __PAGE_SIZE__ AMD64_PAGE_SIZE

#endif // defined(__riscv)

extern uintptr_t __sys_heap_start;
extern uintptr_t __sys_memory_end;
extern uintptr_t __sys_memory_start;

extern void sys_tlb_set(voidptr_t newVal, voidptr_t saveVal);
extern void sys_tlb_flush(voidptr_t satp);

const uintptr_t sys_heap_start(void);

voidptr_t sys_alloc_memory(voidptr_t addr, size_t length, prot_t prot, int32_t map);
int32_t sys_delete_memory(voidptr_t addr, size_t length);

enum
{
    SYS_PROT_EXEC = 0x02,
    SYS_PROT_READ = 0x04,
    SYS_PROT_WRITE = 0x08,
    SYS_PROT_NONE = 0xFF,
};

enum
{
    SYS_MAP_SHARED = 0x10,
    SYS_MAP_PRIVATE = 0xB,
    SYS_MAP_ANONYMOUS = 0xC,
    SYS_MAP_DENY_WRITE = 0xF,
    SYS_MAP_EXECUTABLE = 0x21,
};

#endif /* !_HW_MMU_H */
