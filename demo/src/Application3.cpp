//###########################################################################
// Application3.cpp
// The overall framework of the application
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Application3.h"
#include "ILI9488.h"


///Constructor
Application3::Application3()
{
}


///Initialize
void Application3::Initialize()
{
	Driver* display = device.GetDriver(DriverID::_display);

	gui.Initialize((ILI9488*)display);	
	gui.Printf("hello vk.kernel\r\n");
}


///Execute
void Application3::Execute()
{
	const TCHAR* path[] = { "0:", "1:" };
	
	for (uint8_t i = 0; i < 2; i++)
	{
		gui.Printf("storage %s\r\n", path[i]);

		if (f_mount(&fs, path[i], 1) == FR_OK)
		{
			if (f_opendir(&filedir, path[i]) == FR_OK)
			{
				while(1)
				{
					FRESULT res = f_readdir(&filedir, &fileinfo);
					if (res != FR_OK || fileinfo.fname[0] == 0) break;
					
					gui.Printf("%s\r\n", fileinfo.fname);
				}
			}
			f_closedir(&filedir);
			f_unmount(path[i]);
		}
		gui.Printf("\r\n");
	}
}


///Register module
REGISTER_MODULE(new Application3(), (ModuleID::_application + 2), app_3);
