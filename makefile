#
#	========================================================
#
#	MP MicroKernel
# 	Last rev: 14/11/2023
# 	Copyright Amlal EL Mahrouss, all rights reserved.
#
# 	========================================================
#

export IMG					=qemu-img
export QEMU					=qemu-system-$(MACHINE)
export GDB 					=$(MACHINE)-unknown-elf-gdb

export QEMU_FLAGS_RISCV64	=-device VGA,vgamem_mb=32 -machine virt -bios none -kernel $(INIT) -m 8G -drive if=none,format=raw,file=os.dsk,id=x0 -global virtio-mmio.force-legacy=false \
							 -device virtio-blk-device,drive=x0,bus=virtio-mmio-bus.0,physical_block_size=4096,logical_block_size=512

.PHONY: help
help:
	@echo "create-hdd: Creates a new virtual disk."
	@echo "run-$$MACHINE-debug: Runs the OS in debug mode."
	@echo "run-$$MACHINE: Runs the OS in production mode."

.PHONY: run-riscv64
run-riscv64:
	$(QEMU) $(QEMU_FLAGS_RISCV64) -d int

.PHONY: run-riscv64-debug
run-riscv64-debug:
	$(QEMU) $(QEMU_FLAGS_RISCV64) -d int -s -S

.PHONY: run-debug
run-debug:
	$(GDB) -q -x ./gdbinit


.PHONY: create-hdd
create-hdd:
	$(IMG) create -f raw os.dsk 1M

.PHONY: project-clean
project-clean:
	@(shell ./clean.sh)
