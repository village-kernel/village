//###########################################################################
// Application3.cpp
// The overall framework of the application
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "HWManager.h"
#include "Application3.h"


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
}


///Execute
void Application3::Execute()
{

}


///Register module
REGISTER_MODULE(new Application3(), FUNCTION_ID(2), app_3);
