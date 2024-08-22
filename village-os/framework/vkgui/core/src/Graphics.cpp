//###########################################################################
// Graphics.cpp
// Definitions of the functions that manage graphics
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Graphics.h"
#include "DevStream.h"
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
bool Graphics::Setup()
{
	//Get all block device blockDevs
	List<Base*> fbDevs = kernel->device.GetDevices(DriverID::_framebuffer);

	//Get the universal driver by driver name
	DevStream screen;

	//Open the first screen 
	if (screen.Open(fbDevs.Begin()->GetName(), FileMode::_Read))
	{
		//Get the specified lcd driver by driver ioctrl 
		screen.IOCtrl(0, (void*)&fbdev);

		//Setup display
		if (NULL != fbdev)
		{
			display = new Display();
			display->Setup(fbdev);
		}
	}
	return (NULL != display);
}


/// @brief Exit
void Graphics::Exit()
{
	if (NULL != display)
	{
		display->Exit();
		delete display;
	}
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
