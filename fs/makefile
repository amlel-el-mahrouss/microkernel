CC			= riscv64-unknown-elf-gcc
FLAGS		= -mcmodel=medany -mno-relax -mno-explicit-relocs -fno-builtin -nostdlib -c -D__MP_NEED_MEASUREMENTS
INC			= -I../ -I../builtin/ -I./ -I../libkern/inc

.PHONY: fs-all
fs-all:
	$(CC) $(FLAGS) $(INC) $(wildcard *.c) $(wildcard nsfs/*.c) $(wildcard nfs/*.c)

OBJ=$(wildcard *.o)

.PHONY: fs-clean
fs-clean:
	rm -f $(OBJ)