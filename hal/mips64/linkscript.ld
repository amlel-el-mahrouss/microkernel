OUTPUT_FORMAT(elf32-littlemips)
OUTPUT_ARCH(mips:isa32)
ENTRY(__mach_start)

SECTIONS
{
	.text (0x80001000) :
	{
		*(.text)
		*(.text.*)
		*(.stub)
		*(.gnu.linkonce.t.*)
	}

	.rodata ALIGN(4K) :
	{
		*(.rodata*)
		*(.gnu.linkonce.r.*)
	}

	.data ALIGN(4K) :
	{
		*(.data*)
		*(.gnu.linkonce.d.*)
	}

	.bss ALIGN(4K) :
	{
		*(.common)
		*(.bss*)
		*(.gnu.linkonce.b.*)
	}

	/DISCARD/ :
	{
		*(.gcc_except_table)
		*(.eh_frame)
		*(.note)
		*(.comment)
		*(.rel.*)
		*(.rela.*)
	}
	
	__sys_heap_start = .;
}