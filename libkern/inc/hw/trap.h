/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _TRAP_H
#define _TRAP_H

#include <sys/sys.h>
#include <hw/cpu.h>

bool sys_init_trap_system(void);
bool sys_trap_enabled(void);
void sys_reset_trap_system(void);

#ifdef __SYS_AMD64__

void idt_hook_add(void(*idt_hook)(stackframe_t* sf), int32_t id);
void idt_hook_remove(int32_t id);

#endif // ifdef __SYS_AMD64__

#ifdef __SYS_RISCV__

typedef uint32_t sys_isr_t;
typedef sys_isr_t int_threshold_t;

void sys_enable_interrupts(sys_isr_t* ints, size_t cnt);

#endif // ifdef __SYS_RISCV__

#endif // ifndef _TRAP_H
