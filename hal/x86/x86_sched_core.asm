;
;   ========================================================
;
;   MP MicroKernel
;   Date Added: 08/01/2023
;   Copyright Amlal EL Mahrouss, all rights reserved.
;
;   ========================================================
;

[bits 64]
[global sys_sched_switch_context]
[global sys_sched_save_context]

sys_sched_switch_context:
    ;; Save the current context
    mov [rsi + 0], r15
    mov [rsi + 8], r14
    mov [rsi + 16], r13
    mov [rsi + 24], r12
    mov [rsi + 32], r11
    mov [rsi + 40], r10
    mov [rsi + 48], r9
    mov [rsi + 56], r8
    mov [rsi + 64], rbp
    mov [rsi + 72], rdi
    mov [rsi + 80], rsi
    mov [rsi + 88], rdx
    mov [rsi + 96], rcx
    mov [rsi + 104], rbx
    mov [rsi + 112], rax

    ;; Segment registers
    mov [rsi + 120], cs
    mov [rsi + 128], ds
    mov [rsi + 136], ss

    ;; Load the new context
    mov r15, [rdi + 0]
    mov r14, [rdi + 8]
    mov r13, [rdi + 16]
    mov r12, [rdi + 24]
    mov r11, [rdi + 32]
    mov r10, [rdi + 40]
    mov r9, [rdi + 48]
    mov r8, [rdi + 56]
    mov rbp, [rdi + 64]
    mov rdi, [rdi + 72]
    mov rsi, [rdi + 80]
    mov rdx, [rdi + 88]
    mov rcx, [rdi + 96]
    mov rbx, [rdi + 104]
    mov rax, [rdi + 112]

    ;; Segment registers
    mov cs, [rdi + 120]
    mov ds, [rdi + 128]
    mov ss, [rdi + 136]

    ret

sys_sched_save_context:
    ;; Save the context to the address in rax
    mov [rax + 0], r15
    mov [rax + 8], r14
    mov [rax + 16], r13
    mov [rax + 24], r12
    mov [rax + 32], r11
    mov [rax + 40], r10
    mov [rax + 48], r9
    mov [rax + 56], r8
    mov [rax + 64], rbp
    mov [rax + 72], rdi
    mov [rax + 80], rsi
    mov [rax + 88], rdx
    mov [rax + 96], rcx
    mov [rax + 104], rbx
    mov [rax + 112], rax

    ret
