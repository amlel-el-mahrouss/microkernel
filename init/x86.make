 #
 #	========================================================
 #
 #	MP MicroKernel
 # 	Copyright Amlal EL Mahrouss, all rights reserved.
 #
 # 	========================================================
 #

OUTPUT=kernel.out
LD_SCRIPT=../hal/x86/linkscript.ld
CROSS_LD=x86_64-elf-ld
LD_FLAGS=--script=$(LD_SCRIPT)
CROSS_CC=x86_64-elf-gcc
SOURCES=$(wildcard src/*.c) $(wildcard ../system_calls/*.c) $(wildcard ../libkern/src/*.c) $(wildcard ../system_calls/*.c) $(wildcard ../fs/procfs/*.c)
OBJECTS=$(wildcard *.o) $(wildcard ../libkern/src/*.o) $(wildcard ../libkern/*.o) $(wildcard ../hal/x86/*.o) $(wildcard ../system_calls/*.o)
CC_INC=-Iinc -I../libkern/inc -I../ -I../hal/x86/
CC_FLAGS=-Wall -Werror -c -nostdlib -ffreestanding -fno-builtin -mcmodel=kernel -mno-sse -mno-sse2 -D__KSTRICT__ -fstack-protector-all

.PHONY: all
all:
	$(CROSS_CC) $(CC_INC) $(CC_FLAGS) $(SOURCES)

.PHONY: link
link:
	$(CROSS_LD) $(LD_FLAGS) $(OBJECTS) -o $(OUTPUT)

.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(wildcard *.exe)
