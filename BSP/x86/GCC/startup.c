
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

void __attribute__((naked, noreturn))_start()
{
	void **pSource, **pDest;
	for (pSource = &_sidata, pDest = &_sdata; pDest != &_edata; pSource++, pDest++)
		*pDest = *pSource;

	for (pDest = &_sbss; pDest != &_ebss; pDest++)
		*pDest = 0;

	void __libc_init_array();
	(void)main();

	for (;;) ;
}

void * g_pfnVectors[] __attribute__ ((section (".isr_vector"), used)) = 
{
	&_start
};
