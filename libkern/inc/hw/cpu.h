/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _SYS_CPU_H
#define _SYS_CPU_H

#include <stdint.h>
#include <hw/mmap.h>

struct _sys_snap;

#ifdef __LP64__

typedef uintptr_t reg_t;

#elif defined(__LP128__)

typedef uint128_t reg_t;

#else

typedef uint32_t reg_t;

#endif // ifdef __LP64__ || __LP128__ || 32-bit

#ifdef __riscv

#define sys_halt_cpu() __asm__ volatile ("wfi")

#define sys_read_reg(reg) (volatile reg_t*)reg
#define sys_read_reg_32(reg) (volatile uint32_t*)reg

#define SYS_MAX_CORES              (16U)

#define CLINT                  (0x2000000)
#define CLINT_MTIMECMP(HART)   (((CLINT + 0x4000) + (4 * HART)))
#define CLINT_MTIME            (CLINT + 0xBFF8) // cycles since boot.

// Machine Status Register, mstatus
#define MSTATUS_MPP_MASK    (3 << 11) // previous mode.
#define MSTATUS_MPP_SET     (1 << 11)
#define MSTATUS_MPP_USE     (0 << 11)
#define MSTATUS_MIE         (1 << 3) // machine-mode interrupt enable.

// Machine-mode Interrupt Enable
#define MIE_MEIE (1 << 11) // external
#define MIE_MTIE (1 << 7)  // timer
#define MIE_MSIE (1 << 3)  // software

#define __USER__ __attribute__ ((interrupt ("user")))
#define __HYPERVISOR__ __attribute__ ((interrupt ("hypervisor")))
#define __MACHINE__ __attribute__ ((interrupt ("machine")))

typedef struct _sys_snap
{
	reg_t ra;
	reg_t sp;
	reg_t gp;
	reg_t tp;
	reg_t t0;
	reg_t t1;
	reg_t t2;
	reg_t a0;
	reg_t a1;
	reg_t a2;
	reg_t a3;
	reg_t a4;
	reg_t a5;
	reg_t a6;
	reg_t a7;
	reg_t s0;
	reg_t s1;
	reg_t s2;
	reg_t s3;
	reg_t s4;
	reg_t s5;
	reg_t s6;
	reg_t s7;
	reg_t s8;
	reg_t s9;
	reg_t s10;
	reg_t s11;
	reg_t t3;
	reg_t t4;
	reg_t t5;
} sys_snap_t;

reg_t sys_read_hart_id(void);
reg_t sys_read_mstatus(void);
void sys_write_mstatus(reg_t reg);
void sys_write_mepc(reg_t reg);
void sys_write_satp(reg_t reg);
reg_t sys_read_satp(void);
reg_t sys_read_mepc(void);

void sys_write_mscratch(reg_t reg);
void sys_write_mtvec(reg_t reg);

reg_t sys_read_mie(void);
void sys_write_mie(reg_t reg);

reg_t sys_read_mcause(void);

reg_t sys_read_sepc(void);
reg_t sys_read_scause(void);

void sys_timer_handler(void);

#elif defined(__x86_64__)

extern unsigned long int x86_strcmp(const char* str1, const char* str2);

#define SYS_MAX_CORES               (8U)

#define __USER__
#define __HYPERVISOR__
#define __MACHINE__

typedef struct _sys_snap
{
    reg_t r15;
    reg_t r14;
    reg_t r13;
    reg_t r12;
    reg_t r11;
    reg_t r10;
    reg_t r9;
    reg_t r8;
    reg_t rbp;
    reg_t rdi;
    reg_t rsi;
    reg_t rdx;
    reg_t rcx;
    reg_t rbx;
    reg_t rax;
} sys_snap_t;

typedef sys_snap_t stackframe_t;

#define sys_halt_cpu() __asm__ volatile ("hlt")

#include <x86_cpu.h>

#endif

/* Hardware specific timer, PIC, CLINT or whatever */
void sys_timer_init(void);

/**
 * @brief Request a system poweroff.
 * Memory gets cleaned up.
 */
void sys_request_poweroff(void);

/**
 * @brief Request a reboot from the kernel.
 * Set the computer into a reboot state.
 */
void sys_request_reboot(void);

#endif // __SYS_CPU_H__
