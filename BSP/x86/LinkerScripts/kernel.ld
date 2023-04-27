ENTRY(_start)

_estack = ORIGIN(RAM) + LENGTH(RAM);
_Min_Heap_Size  = 0x400;
_Min_Stack_Size = 0x800;

MEMORY
{
	RAM (xrw)    : ORIGIN = 0x1000, LENGTH = 10M
}

SECTIONS
{
	_sivector = LOADADDR(.isr_vector);

	.isr_vector :
	{
		. = ALIGN(4);
		_svector = .;
		KEEP(*(.isr_vector))
		. = ALIGN(4);
		_evector = .;
	} > RAM

	.text :
	{
		. = ALIGN(4);
		*(.text)
		*(.text*)

		KEEP (*(.init))
		KEEP (*(.fini))

		. = ALIGN(4);
		 _etext = .; 
	} > RAM

	.rodata :
	{
		. = ALIGN(4);
		*(.rodata)
		*(.rodata*)
		. = ALIGN(4);
	} > RAM

	.preinit_array :
	{
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP (*(.preinit_array*))
		PROVIDE_HIDDEN (__preinit_array_end = .);
	} > RAM

	.init_array :
	{
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array*))
		PROVIDE_HIDDEN (__init_array_end = .);
	} > RAM

	.fini_array :
	{
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP (*(SORT(.fini_array.*)))
		KEEP (*(.fini_array*))
		PROVIDE_HIDDEN (__fini_array_end = .);
	} > RAM

	_sidata = LOADADDR(.data);

	.data :
	{
		. = ALIGN(4);
		_sdata = .;  
		*(.data)
		*(.data*)
		. = ALIGN(4);
		_edata = .; 
	} > RAM

	.bss :
	{
		. = ALIGN(4);
		_sbss = .; 
		*(.bss)
		*(.bss*)
		. = ALIGN(4);
		_ebss = .; 
	} > RAM

	._user_heap_stack :
	{
		. = ALIGN(4);
		PROVIDE ( end = . );
		PROVIDE ( _end = . );
		. = . + _Min_Heap_Size;
		. = . + _Min_Stack_Size;
		. = ALIGN(4);
	} > RAM
}
