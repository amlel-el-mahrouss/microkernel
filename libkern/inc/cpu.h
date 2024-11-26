/*
 *	========================================================
 *
 *	MP MicroKernel
 * 	Date Added: 13/04/2023
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

#ifdef __riscv
#   define __arch__ "rv64"
#elif defined(__aarch64__)
#   define __arch__ "aarch64"
#elif defined(__x86_64)
#   define __arch__ "amd64"
#endif // __riscv || __aarch64__  || __x86_64

#define __uname__ "kernel"
#define __unknown__ "?"

// choose according to config
#ifdef __KDEBUG__
#define __release__ __uname__ ", DEBUG, MT, " __DATE__ ", " __arch__
#else
#   define __release__ __uname__ ", RELEASE, MT, " __DATE__ ", " __arch__
#endif /* ifdef __KDEBUG__ */
