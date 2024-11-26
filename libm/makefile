 #
 #	========================================================
 #
 #	MP MicroKernel
 # 	Copyright Amlal EL Mahrouss, all rights reserved.
 #
 # 	========================================================
 #

.PHONY: libm-amd64
libm-amd64:
	nasm -f elf64 sqrt.amd64.asm
	x86_64-elf-gcc -nostdlib -ffreestanding -I../ -I../libkern/inc -I../hal/x86 -shared *.c sqrt.amd64.o -o libm.so
