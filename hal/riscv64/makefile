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
	riscv64-unknown-elf-gcc -D__KERNEL -Werror -Wall -c -nostdlib -ffreestanding -fno-builtin -D__MPUX_NEED_MEASUREMENTS -D__KSTRICT__ -D__KDEBUG__ -D__KSIMP__ -O2 -mcmodel=medany \
	-I./ -I../../init/inc -I../../ -I../../libhart -I../../builtin/ -I../../fs -I../../libkern/inc -I../../libmthread/inc $(wildcard *.S) $(wildcard *.c) ../start.c ../logger.c ../hang.c -c

.PHONY: clean
clean:
	rm -f $(wildcard *.o)
