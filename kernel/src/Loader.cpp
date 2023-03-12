//###########################################################################
// Loader.cpp
// Definitions of the functions that manage loader
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Loader.h"
#include "Thread.h"
#include "ff.h"
#include "Gpi.h"


///Loader Initialize
void Loader::Initialize()
{
	Gpi key;
	key.Initialize(Gpio::_ChE, 3);

	if (0 == key.Read()) LoadModule();
}


///Loader module
void Loader::LoadModule()
{
	FATFS fs; FIL file; UINT br;

	uint32_t module = 0x20000000;

	if (f_mount(&fs, "1:", 1) == FR_OK)
	{
		if (f_open(&file, "1:test.bin", FA_READ) == FR_OK)
		{	
			f_read(&file, (void*)module, f_size(&file), &br);
			f_close(&file);

			f_unmount("1:");

			(*(void(*)())(*(uint32_t*)module))();

			//Thread::CreateTask((ThreadHandlerC)module);
		}
		f_unmount("1:");
	}
}


///Register module
REGISTER_MODULE(new Loader(), ModuleID::_loader, loader);
