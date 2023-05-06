
//###########################################################################
// startup.c
// Low level file that manages system boot entry
//
// $Copyright: Copyright (C) village
//###########################################################################
void __libc_init_array();
int main();

extern void *_sidata, *_sdata, *_edata;
extern void *_sbss, *_ebss;
extern void (*__preinit_array_start []) (void) __attribute__((weak));
extern void (*__preinit_array_end   []) (void) __attribute__((weak));
extern void (*__init_array_start    []) (void) __attribute__((weak));
extern void (*__init_array_end      []) (void) __attribute__((weak));


void __attribute__((naked, noreturn))_start()
{
	int count, i;
	void **pSource, **pDest;

	for (pSource = &_sidata, pDest = &_sdata; pDest != &_edata; pSource++, pDest++)
		*pDest = *pSource;

	for (pDest = &_sbss; pDest != &_ebss; pDest++)
		*pDest = 0;

	count = __preinit_array_end - __preinit_array_start;
	for (i = 0; i < count; i++)
		__preinit_array_start[i]();

	count = __init_array_end - __init_array_start;
	for (i = 0; i < count; i++)
		__init_array_start[i]();

	(void)main();

	for (;;) ;
}

void * g_pfnVectors[] __attribute__ ((section (".isr_vector"), used)) = 
{
	&_start
};
