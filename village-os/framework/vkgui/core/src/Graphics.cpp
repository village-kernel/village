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
	if (fbdev)   delete fbdev;
	if (display) delete display;
	if (mainwin) delete mainwin;
}


/// @brief Setup
/// @param drvname 
bool Graphics::Setup(const char* screen)
{
	//Get the universal driver by driver name
	DrvStream screendrv;
	if (screendrv.Open(screen, FileMode::_Read))
	{
		//Get the specified lcd driver by driver ioctrl 
		screendrv.IOCtrl(0, (void*)&fbdev);
		
		//Setup display
		if (NULL != fbdev)
		{
			display = new Display();
			display->Setup(fbdev);
		}
	}
	return (NULL != display);
}


/// @brief Create main window
/// @return 
Wedget* Graphics::CreateMainWindow()
{
	if (NULL != display)
	{
		mainwin = new Window();
		mainwin->SetDisplay(display);
		mainwin->Setup();
		mainwin->SetLocation(0, 0, fbdev->device.width, fbdev->device.height);
		return mainwin;
	}
	return NULL;
}
