 ;;
 ;;	========================================================
 ;;
 ;;		MP MicroKernel
 ;; 	Date Added: 08/01/2023
 ;; 	Copyright Amlal EL Mahrouss, all rights reserved.
 ;;
 ;;	========================================================
 ;;

[extern __sys_enable_x86_feat]
[extern __sys_clean_bss]
[extern __sys_startup]
[extern __sys_gdtr]
[extern __sys_stack_end]
[extern __sys_gdt32_data]
[global __mach_start]

[bits 32]

__mach_start:
	cli

	lgdt [__sys_gdtr]

	;; protected mode enable
	mov eax, cr0
	or eax, 1
	mov cr0, eax

	mov ax, __sys_gdt32_data
	mov ds, ax

	jmp 0x8:__sys_bootstrap

__sys_bootstrap:
	mov cx, 0x10
	mov ss, cx
	mov ds, cx
	mov es, cx
	mov fs, cx
	mov cx, 0x18
	mov gs, cx

	mov esp, __sys_stack_end
	mov ebp, esp

	call __sys_enable_x86_feat ; enable common x86 features.

	rdtsc
	mov DWORD [0x1014], eax

    call __sys_startup

.L0:
	cli
	hlt
	jmp .L0
