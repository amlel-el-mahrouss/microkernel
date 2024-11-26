 #
 #	========================================================
 #
 #	MP MicroKernel
 # 	Copyright Amlal EL Mahrouss, all rights reserved.
 #
 # 	========================================================
 #

COMMON_BUILTINS=$(wildcard ../builtin/super_disk/*.c)\
                 $(wildcard ../builtin/teletype/*.c) $(wildcard ../builtin/universal_serial_bus/*.c) $(wildcard ../builtin/virt_disk/*.c) \
                 $(wildcard ../builtin/firewire/*.c) $(wildcard ../builtin/nvm_express/*.c) \
                 $(wildcard ../builtin/network_card/*.c) $(wildcard ../builtin/uptime/*.c) $(wildcard ../fs/*.c)


.PHONY: common
common:
	$(CROSS_CC) $(CC_INC) $(CC_FLAGS) $(COMMON_BUILTINS)
