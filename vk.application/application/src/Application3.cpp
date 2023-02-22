//###########################################################################
// Application3.cpp
// The overall framework of the application
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "HWManager.h"
#include "Application3.h"
#include "ff.h"


///Constructor
Application3::Application3()
{
}


///Initialize
void Application3::Initialize()
{
	uint8_t wString[] = "hello vk.kernel";
	uint8_t rString[] = "";

	//HWManager::Instance()->spiFlash.Write(wString, 16, 0);
	HWManager::Instance()->spiFlash.Read(rString, 16, 0);

	gui.Initialize(&(HWManager::Instance()->ili9488));
	gui.disp.ShowString(0, 0, rString);

	FATFS fs; DIR file_dir; FILINFO fileinfo;

	if (f_mount(&fs, "1:", 1) == FR_OK)
	{
		if (f_opendir(&file_dir, "1:") == FR_OK)
		{
			uint16_t disp_y = 16;
			while(1)
			{
				FRESULT res = f_readdir(&file_dir, &fileinfo);
				if (res != FR_OK || fileinfo.fname[0] == 0) break;
				
				gui.disp.ShowString(0, disp_y, (uint8_t*)fileinfo.fname);
				disp_y += 16;
			}
		}
		f_closedir(&file_dir);
		f_unmount("1:");
	}
}


///Execute
void Application3::Execute()
{

}


///Register module
REGISTER_MODULE(new Application3(), FUNCTION_ID(2), app_3);
