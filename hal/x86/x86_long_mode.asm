 ;;
 ;;	========================================================
 ;;
 ;;		MP MicroKernel
 ;; 	Date Added: 08/01/2023
 ;; 	Copyright Amlal EL Mahrouss, all rights reserved.
 ;;
 ;;	========================================================
 ;;

[bits 64]

__sys_startup:
L0:
    cli
    hlt
    jmp $
