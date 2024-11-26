 ;;
 ;;	========================================================
 ;;
 ;;		MP MicroKernel
 ;; 	Date Added: 08/01/2023
 ;; 	Copyright Amlal EL Mahrouss, all rights reserved.
 ;;
 ;;	========================================================
 ;;

[GLOBAL __sys_gdtr]
[BITS 32]

__sys_gdtr:
	dw __sys_gdt32_end - __sys_gdt32 - 1
	dd __sys_gdt32

[BITS 32]
__sys_gdt32:
	;; Entry 0x0: Null descriptor
	dq 0x0
__sys_gdt32_code:
	dw 0xffff          ; Limit
	dw 0x0000          ; Base 15:00
	db 0x00            ; Base 23:16
	dw 0xcf9a          ; Flags / Limit / Type [F,L,F,Type]
	db 0x00            ; Base 32:24
__sys_gdt32_data:
	dw 0xffff          ; Limit
	dw 0x0000          ; Base 15:00
	db 0x00            ; Base 23:16
	dw 0xcf92          ; Flags / Limit / Type [F,L,F,Type]
	db 0x00            ;Base 32:24
__sys_gdt32_gs:
	dw 0x0100          ; Limit
	dw 0x1000          ; Base 15:00
	db 0x00            ; Base 23:16
	dw 0x4092          ; Flags / Limit / Type [F,L,F,Type]
	db 0x00            ; Base 32:24
__sys_gdt32_end:
