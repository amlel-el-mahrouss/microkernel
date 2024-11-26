/*
 *	========================================================
 *
 *	MP MicroKernel LibC
 * 	Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

.section .text.init
.global _start

.extern _crt_errno

#ifdef __riscv
.align 2
_start:
    xor _crt_errno, _crt_errno
    call main

    li a0, 2
    li a1, _crt_errno
    ecall /* call exit */
#elif defined(__x86_64__)
.align 8
_start:
    xor _crt_errno, _crt_errno
    call main

    mov rdi, 2
    mov rsi, _crt_errno
    syscall /* call exit routine */
#else
#   error Undefined symbol _start for libc!
#endif
