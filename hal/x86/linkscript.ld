OUTPUT_FORMAT("elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)

ENTRY(__mach_start)

. = 1M;

PHDRS {
    null    PT_NULL    FLAGS(0) ;
    text    PT_LOAD    FLAGS((1 << 0) | (1 << 2) | (1 << 3));
    rodata  PT_LOAD    FLAGS((1 << 2)) ;
    data    PT_LOAD    FLAGS((1 << 1) | (1 << 2)) ;
}

SECTIONS {
    .text : {
        _text_start = .;

        *(.text .text.*)

        _text_end = .;
    } :text

    . += CONSTANT(MAXPAGESIZE);

    .rodata : {
        _rodata_start = .;

        *(.rodata .rodata.*)

        _rodata_end = .;
    } :rodata

    . += CONSTANT(MAXPAGESIZE);

    .data : {
        _bss_start = .;

        *(.data .data.*)
        _data_end = .;
    } :data

    .bss : {
        _bss_start = .;

        *(COMMON)
        *(.bss .bss.*)

        _bss_end = .;
    } :data
    
	PROVIDE(__sys_memory_start = 1M);

	PROVIDE(__sys_stack_start = _bss_end);
	PROVIDE(__sys_stack_end = __sys_stack_start + 0x8000);

	PROVIDE(__sys_memory_end = 1M + 128M);
    
	PROVIDE(__sys_heap_start = .);
}
