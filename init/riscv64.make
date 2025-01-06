OUTPUT=kernel.out

LD_SCRIPT=../hal/riscv64/linkscript.ld

CROSS_LD=riscv64-unknown-elf-ld

LD_FLAGS=--script=$(LD_SCRIPT)

CROSS_CC=riscv64-unknown-elf-gcc

SOURCES=$(wildcard src/*.c) \
	$(wildcard ../system_calls/*.c) $(wildcard ../libkern/src/*.c) \
	$(wildcard ../builtin/virt_disk/*.c) $(wildcard ../libhart/*.c) \
	$(wildcard ../libident/src/*.c) $(wildcard ../fs/ffs_2/*.c)  $(wildcard ../fs/procfs/*.c) $(wildcard ../libmthread/src/*.c) $(wildcard ../libmthread/riscv64/*.S)

OBJECTS=$(wildcard *.o) $(wildcard ../libkern/src/*.o) $(wildcard ../libkern/*.o) $(wildcard ../hal/riscv64/*.o) $(wildcard ../system_calls/*.o)

CC_INC=-Iinc -I../libkern/inc -I../ -I../builtin/ -I../fs/ -I../libhart -I../libident/inc -I../libmthread/inc

CC_FLAGS=-Wall -trigraphs -Werror -c -nostdlib -ffreestanding -fno-builtin -mcmodel=medany -mno-relax -mno-explicit-relocs -D__KDEBUG__ -D__MP_NEED_MEASUREMENTS -D__KERNEL -D__KSTRICT__ -D__KSIMP__ -O2 -fstack-protector-all

include common.make

.PHONY: all
all: common
	$(CROSS_CC) $(CC_INC) $(CC_FLAGS) $(SOURCES)

.PHONY: link
link:
	$(CROSS_LD) $(LD_FLAGS) $(OBJECTS) -o $(OUTPUT)

.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(wildcard *.elf)
