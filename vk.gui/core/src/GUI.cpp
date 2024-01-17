//###########################################################################
// GUI.cpp
// Definitions of the functions that manage GUI
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "GUI.h"
#include "Window.h"
#include "Village.h"


/// @brief Constructor
GUI::GUI()
	:lcdDriver(NULL),
	display(NULL),
	mainwin(NULL)
{
}


/// @brief Destructor
GUI::~GUI()
{
	delete lcdDriver;
	delete display;
	delete mainwin;
}


/// @brief Intialize
/// @param drvname 
void GUI::Initialize(const char* drvname)
{
	//Get the universal driver by driver name
	Driver* driver = village.GetDriverByName(drvname);

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
Wedget* GUI::CreateMainWindow()
{
	mainwin = new Window();
	mainwin->SetDisplay(display);
	mainwin->Initialize();
	mainwin->SetLocation(0, 0, lcdDriver->device.width, lcdDriver->device.height);
	return mainwin;
}
