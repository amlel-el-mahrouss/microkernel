 #
 #	========================================================
 #
 #	MP MicroKernel
 # 	Date Added: 08/01/2023
 # 	Copyright Amlal EL Mahrouss, all rights reserved.
 #
 # 	========================================================
 #

CC=mips64-elf-gcc
FLAGS=-c -nostdlib -ffreestanding -fno-builtin -Wall -Werror -fno-builtin -O2 -D__KSTRICT__
INC=-I./ -I../../init/inc -I../../ -I../../libkern/inc

.PHONY: hal
hal:
	 $(CC) $(FLAGS) $(INC) $(wildcard *.S) $(wildcard *.c) -c

.PHONY: clean
clean:
	rm -f $(wildcard *.o)
