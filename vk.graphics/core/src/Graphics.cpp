//###########################################################################
// Graphics.cpp
// Definitions of the functions that manage graphics
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Graphics.h"
#include "Window.h"
#include "Village.h"


/// @brief Constructor
Graphics::Graphics()
	:lcdDriver(NULL),
	display(NULL),
	mainwin(NULL)
{
}


/// @brief Destructor
Graphics::~Graphics()
{
	delete lcdDriver;
	delete display;
	delete mainwin;
}


/// @brief Intialize
/// @param drvname 
void Graphics::Initialize(const char* drvname)
{
	//Get the universal driver by driver name
	Driver* driver = Village().GetDriverByName(drvname);

	//Get the specified lcd driver by driver ioctrl 
	if (NULL != driver)
	{
		driver->IOCtrl(0, (void*)&lcdDriver);
	}

	//Initialize display
	if (NULL != lcdDriver)
	{
		display = new Display();
		display->Initialize(lcdDriver);
	}
}


/// @brief Create main window
/// @return 
Wedget* Graphics::CreateMainWindow()
{
	mainwin = new Window();
	mainwin->SetDisplay(display);
	mainwin->Initialize();
	mainwin->SetLocation(0, 0, lcdDriver->device.width, lcdDriver->device.height);
	return mainwin;
}
