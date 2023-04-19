ENTRY(_start)

MEMORY
{
	RAM (xrw)    : ORIGIN = 0x0000, LENGTH = 512
	FLASH (rx)   : ORIGIN = 0x0000, LENGTH = 512
}

SECTIONS
{
    .text :
	{
		. = ALIGN(8);
		*(.text)
		*(.text*)
		. = ALIGN(8);
	} > FLASH

	.rodata :
	{
		. = ALIGN(8);
		*(.rodata)
		*(.rodata*)
		. = ALIGN(8);
	} > FLASH

	.data :
	{
		. = ALIGN(8);
		*(.data)
		*(.data*)
		. = ALIGN(8);
	} > RAM AT> FLASH

	.bss :
	{
		. = ALIGN(8);
		*(.bss)
		*(.bss*)
		. = ALIGN(8);
	} > RAM AT> FLASH
}
