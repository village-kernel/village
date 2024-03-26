//###########################################################################
// Graphics.cpp
// Definitions of the functions that manage graphics
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Graphics.h"
#include "Window.h"
#include "Kernel.h"


/// @brief Constructor
Graphics::Graphics()
	:fbdev(NULL),
	display(NULL),
	mainwin(NULL)
{
}


/// @brief Destructor
Graphics::~Graphics()
{
	delete fbdev;
	delete display;
	delete mainwin;
}


/// @brief Intialize
/// @param drvname 
void Graphics::Initialize(const char* screen, const char* keyboard, const char* mouse)
{
	//Get the universal driver by driver name
	Driver* screendrv = kernel->device.GetDriver(screen);

	//Get the specified lcd driver by driver ioctrl 
	if (NULL != screendrv)
	{
		screendrv->Open();
		screendrv->IOCtrl(0, (void*)&fbdev);
	}

	//Initialize display
	if (NULL != fbdev)
	{
		display = new Display();
		display->Initialize(fbdev);
	}

	//Get the universal driver by driver name
	Driver* keyboarddrv = kernel->device.GetDriver(keyboard);

	//Initialize keyboard
	if (NULL != keyboarddrv)
	{
		keyboarddrv->Open();
	}

	//Get the universal driver by driver name
	Driver* mousedrv = kernel->device.GetDriver(mouse);

	//Initialize keyboard
	if (NULL != mousedrv)
	{
		mousedrv->Open();
	}
}


/// @brief Create main window
/// @return 
Wedget* Graphics::CreateMainWindow()
{
	mainwin = new Window();
	mainwin->SetDisplay(display);
	mainwin->Initialize();
	mainwin->SetLocation(0, 0, fbdev->device.width, fbdev->device.height);
	return mainwin;
}
