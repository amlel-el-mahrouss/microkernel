;; *
;; *	========================================================
;; *
;; *	MP MicroKernel
;; * 	Copyright Amlal EL Mahrouss, all rights reserved.
;; *
;; * 	========================================================
;; *

section .text

[global __asm_sqrt]

__asm_sqrt:
    fld qword [rdi]
    fsqrt
    fstp qword [rax]
    ret
