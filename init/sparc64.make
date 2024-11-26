OUTPUT = kernel.out
LD_SCRIPT = ../hal/sparc64/linkscript.ld
CROSS_LD = sparc64-elf-ld
LD_FLAGS = --script=$(LD_SCRIPT)
CROSS_CC = sparc64-elf-gcc
SOURCES = $(wildcard init/*.c) $(wildcard ../libkern/src/*.c) $(wildcard ../system_calls/*.c) $(wildcard ../fs/procfs/*.c)

OBJECTS = $(wildcard *.o) $(wildcard ../libkern/src/*.o) $(wildcard ../libkern/*.o) $(wildcard ../hal/sparc64/*.o)

CC_INC = -Iinc -I../libkern/inc -I../
CC_FLAGS = -c -nostdlib -ffreestanding -fno-builtin -Wall -Werror

.PHONY: all
all:
	$(CROSS_CC) $(CC_INC) $(CC_FLAGS) $(SOURCES)

.PHONY: link
link:
	$(CROSS_LD) $(LD_FLAGS) $(OBJECTS) -o $(OUTPUT)

.PHONY: clean
clean:
	rm -rf $(OBJECTS) $(wildcard *.exe)
