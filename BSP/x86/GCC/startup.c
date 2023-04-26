
//###########################################################################
// startup.c
// Low level file that manages system boot entry
//
// $Copyright: Copyright (C) village
//###########################################################################
int main();

extern void *_sidata, *_sdata, *_edata;
extern void *_sbss, *_ebss;
extern void *__preinit_array_start;
extern void *__preinit_array_end;
extern void *__init_array_start;
extern void *__init_array_end;
extern void *__fini_array_start;
extern void *__fini_array_end;

void __attribute__((naked, noreturn)) _start()
{
	void **pSource, **pDest;
	for (pSource = &_sidata, pDest = &_sdata; pDest != &_edata; pSource++, pDest++)
		*pDest = *pSource;

	for (pDest = &_sbss; pDest != &_ebss; pDest++)
		*pDest = 0;

	for (pDest = &__preinit_array_start; pDest != &__preinit_array_end; pDest++)
		((void(*)())(*pDest))();

	for (pDest = &__init_array_start; pDest != &__init_array_end; pDest++)
		((void(*)())(*pDest))();

	(void)main();

	for (pDest = &__fini_array_start; pDest != &__fini_array_end; pDest++)
		((void(*)())(*pDest))();

	for (;;) ;
}
