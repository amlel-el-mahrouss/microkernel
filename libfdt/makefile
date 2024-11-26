#
#	========================================================
#
#	MP MicroKernel
# 	Date Added: 14/11/2023
# 	Copyright Amlal EL Mahrouss, all rights reserved.
#
# 	========================================================
#

CC		= cc
CC_FLAGS= -I../libkern/inc -I../ -std=c17 -ffreestanding -nostdlib

.PHONY: compile-libfdt
compile-libfdt:
	$(CC) $(CC_FLAGS) $(wildcard *.c) -c
