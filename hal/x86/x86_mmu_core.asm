 ;
 ;	========================================================
 ;
 ;	MP MicroKernel
 ; 	Date Added: 08/01/2023
 ; 	Copyright Amlal EL Mahrouss, all rights reserved.
 ;
 ; 	========================================================
 ;

[global mmu_flush]
[bits 64]

mmu_flush:
    invlpg [rdi]
    ret
