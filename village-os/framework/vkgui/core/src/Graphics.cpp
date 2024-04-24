//###########################################################################
// Graphics.cpp
// Definitions of the functions that manage graphics
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Graphics.h"
#include "DrvStream.h"
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
void Graphics::Initialize(const char* screen)
{
	//Get the universal driver by driver name
	DrvStream screendrv;
	if (screendrv.Open(screen, FileMode::_Read))
	{
		//Get the specified lcd driver by driver ioctrl 
		screendrv.IOCtrl(0, (void*)&fbdev);
		
		//Initialize display
		if (NULL != fbdev)
		{
			display = new Display();
			display->Initialize(fbdev);
		}
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
