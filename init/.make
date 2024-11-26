.PHONY: all
all:
	@echo "You need to define the 'MACHINE' var! e.g: export MACHINE=riscv64"
	@echo "Sorry."

.PHONY: link
link: 
	@echo "Failed to link program! No such machine!"
	@echo "Sorry."
	
.PHONY: clean
clean: all
	