//###########################################################################
// Application3.cpp
// The overall framework of the application
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "Application3.h"
#include "ff.h"


///Constructor
Application3::Application3()
{
}


///Initialize
void Application3::Initialize()
{
	display = Device::GetDriver(DriverID::_display);

	gui.Initialize((ILI9488*)display);	
	gui.disp.ShowString((uint8_t*)"hello vk.kernel\r\n\r\n");

	Thread::CreateTaskCpp(this, (ThreadHandlerCpp)&Application3::ListFiles);
}


///Execute
void Application3::Execute()
{

}


///ListFiles
void Application3::ListFiles()
{
	if (NULL != display)
	{
		FATFS fs; DIR file_dir; FILINFO fileinfo;

		const TCHAR* path[] = { "0:", "1:" };
		
		for (uint8_t i = 0; i < 2; i++)
		{
			gui.disp.ShowString((uint8_t*)"storage ");
			gui.disp.ShowString((uint8_t*)path[i]);
			gui.disp.ShowString((uint8_t*)"\r\n");

			if (f_mount(&fs, path[i], 1) == FR_OK)
			{
				if (f_opendir(&file_dir, path[i]) == FR_OK)
				{
					while(1)
					{
						FRESULT res = f_readdir(&file_dir, &fileinfo);
						if (res != FR_OK || fileinfo.fname[0] == 0) break;
						
						gui.disp.ShowString((uint8_t*)fileinfo.fname);
						gui.disp.ShowString((uint8_t*)"\r\n");
					}
				}
				f_closedir(&file_dir);
				f_unmount(path[i]);
			}
			gui.disp.ShowString((uint8_t*)"\r\n");
		}
	}
}


///Register module
REGISTER_MODULE(new Application3(), (ModuleID::_application + 2), app_3);
