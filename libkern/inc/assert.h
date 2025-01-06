/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef _MP_ASSERT_H
#define _MP_ASSERT_H

#include <sys/log.h>

#ifdef __x86_64__
#   define mpux_break_point() __asm__ volatile ("1: jmp 1b");
#elif defined(__riscv)
#   define mpux_break_point() __asm__ volatile ("1: j 1b");
#endif

#define mpux_panic(MSG) { sys_print_format("%s%s%s %s%n", BRED, "[ PANIC ]", RESET, MSG); while (1) { sys_halt_cpu(); } }
#define mpux_assert(EXPR) if (!(EXPR)) { sys_print_format(REDB WHT "[ASSERTION FAILED] : (" #EXPR ") File: " __FILE__ "\r\n" RESET); while (1); }

#define assert(expr) mpux_assert(expr)

#define panic(msg) mpux_panic(msg)

#define break_point() mpux_break_point()

#ifndef __cplusplus
#   define static_assert _Static_assert
#endif /* ifndef __cplusplus */

#endif // ifndef _MP_ASSERT_H
