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
	if (fbdev)   delete fbdev;
	if (display) delete display;
	if (mainwin) delete mainwin;
}


/// @brief Setup
/// @param drvname 
bool Graphics::Setup(const char* screen)
{
	//Get the universal driver by driver name
	fbdev = kernel->device.GetDeviceFB(screen);

	//Setup display
	if (NULL != fbdev && fbdev->Setup())
	{
		display = new Display();
		display->Setup(fbdev);
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
		mainwin->SetLocation(0, 0, fbdev->fbinfo.width, fbdev->fbinfo.height);
		return mainwin;
	}
	return NULL;
}
