//###########################################################################
// Application3.cpp
// The overall framework of the application
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Kernel.h"
#include "HWManager.h"
#include "Application3.h"


/// Constructor
Application3::Application3()
{
}


/// Initialize
void Application3::Initialize()
{
	gui.Initialize(&(HWManager::Instance()->ili9488));

	gui.disp.ShowString(0, 0, (uint8_t*)"hello world!");
}


/// Execute
void Application3::Execute()
{

}


///Register module
REGISTER_MODULE(new Application3(), FUNCTION_ID(2), app_3);
