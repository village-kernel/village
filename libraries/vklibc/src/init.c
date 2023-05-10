//###########################################################################
// init.c
// Source file for init classes
//
// $Copyright: Copyright (C) village
//###########################################################################

extern void (*__preinit_array_start []) (void) __attribute__((weak));
extern void (*__preinit_array_end   []) (void) __attribute__((weak));
extern void (*__init_array_start    []) (void) __attribute__((weak));
extern void (*__init_array_end      []) (void) __attribute__((weak));

void __libc_init_array(void)
{
	int count, i;
	count = __preinit_array_end - __preinit_array_start;
	for (i = 0; i < count; i++)
		__preinit_array_start[i]();

	count = __init_array_end - __init_array_start;
	for (i = 0; i < count; i++)
		__init_array_start[i]();
}
