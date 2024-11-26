 ;;
 ;;	========================================================
 ;;
 ;;		MP MicroKernel
 ;; 	Date Added: 08/01/2023
 ;; 	Copyright Amlal EL Mahrouss, all rights reserved.
 ;;
 ;;	========================================================
 ;;

;; the purpose of this file is to enable all features needed by a modern operating system kernel.
;; like here SSE, and AVX

[bits 32]
[global __sys_enable_x86_feat]
[global hw_get_real_ptr]

__sys_enable_x86_feat:
    ;; enable SSE (pretty much always exists)
    mov eax, cr0
    and ax, 0xFFFB  ; clear coprocessor emulation CR0.EM
    or  ax, 0x2     ; set coprocessor monitoring  CR0.MP
    mov cr0, eax
    mov eax, cr4
    or ax, 3 << 9   ; set CR4.OSFXSR and CR4.OSXMMEXCPT at the same time
    or ax, 0x20     ; enable native FPU exception handling
    mov cr4, eax
    ;; read out CPU features
    mov eax, 1
    xor ecx, ecx
    cpuid
    mov edx, ecx
    ;; check for XSAVE support (bit 26)
    and ecx, 0x04000000
    jz __xsave
    ;; enable XSAVE
    mov eax, cr4
    or  eax, 0x40000
    mov cr4, eax
    ;; check for AVX support (bit 28)
    and edx, 0x10000000
    jz __xsave
    ;; enable AVX
    xor ecx, ecx
    xgetbv
    or eax, 0x7
    xsetbv
__xsave: ;; no such feature.
    ret
