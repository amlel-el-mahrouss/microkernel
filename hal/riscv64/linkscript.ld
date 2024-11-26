ENTRY(__mach_start);
 
. = 0x80000000;

SECTIONS {
	.text : ALIGN(4K) {
		PROVIDE(_text_start = .);

		*(.init);
		*(.text);

		PROVIDE(_text_end = .);
	}

	PROVIDE(__sys_global_pointer = .);

	.bss : ALIGN(4K) {
		PROVIDE(_bss_start = .);
		
		*(.bss);

		PROVIDE(_bss_end = .);
	}

	.rodata : ALIGN(4K) {
		PROVIDE(_rodata_start = .);

		*(.rodata);
		
		PROVIDE(_rodata_end = .);
	}


	.data : ALIGN(4K) {
		PROVIDE(_data_start = .);

		*(.data);

		PROVIDE(_data_end = .);
	}

	PROVIDE(__sz = .);

	PROVIDE(__sys_memory_start = __sz);

	PROVIDE(__sys_stack_start = _bss_end);
	PROVIDE(__sys_stack_end = __sys_stack_start + 0x8000);

	PROVIDE(__sys_second_stack = __sys_stack_end + 0x10);
	PROVIDE(__sys_second_stack_end = __sys_second_stack + 0x8000);

	PROVIDE(__sys_memory_end = . + 128M);

	PROVIDE(__sys_heap_start = .);
}
