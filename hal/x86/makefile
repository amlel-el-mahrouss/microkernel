 #
 #	========================================================
 #
 #	MP MicroKernel
 # 	Date Added: 08/01/2023
 # 	Copyright Amlal EL Mahrouss, all rights reserved.
 #
 # 	========================================================
 #

.PHONY: hal
hal:
	x86_64-elf-gcc -Wall -Werror -fno-builtin -fno-pic -mcmodel=large -fno-builtin -fno-pie -O2 -ffreestanding -nostdlib  \
	-I./ -I../../init/inc -I../../ -I../../builtin/ -I../../fs -I../../libkern/inc $(wildcard *.S) $(wildcard *.c) -c
	nasm -f elf64 x86_feat.asm
	nasm -f elf64 x86_gdt.asm
	nasm -f elf64 x86_crt0.asm
	nasm -f elf64 x86_sched_core.asm
	nasm -f elf64 x86_mmu_core.asm

.PHONY: clean
clean:
	rm -f $(wildcard *.o)
