//###########################################################################
// VkGUI.cpp
// Definitions of the functions that manage vkgui
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "VkGUI.h"
#include "Window.h"


/// @brief Constructor
VkGUI::VkGUI()
	:fbdev(NULL),
	drawing(NULL),
	cursor(NULL)
{
}


/// @brief Destructor
VkGUI::~VkGUI()
{
	if (drawing) delete drawing;
}


/// @brief Setup
bool VkGUI::Setup(FBDriver* fbdev)
{
	this->fbdev = fbdev;

	if (NULL != fbdev)
	{
		//Setup drawing
		drawing = new Drawing();
		drawing->Setup(fbdev);

		//Setup indev
		indev = new Indev();
		indev->Setup();
	}

	return (NULL != fbdev);
}


/// @brief Execute
void VkGUI::Execute()
{
	if (NULL != cursor)
	{
		cursor->Refresh();
	}
}


/// @brief Exit
void VkGUI::Exit()
{
	if (NULL != drawing)
	{
		drawing->Exit();
		delete drawing;
	}

	if (NULL != indev)
	{
		indev->Exit();
		delete indev;
	}
}


/// @brief Input text
/// @param data 
/// @param size 
void VkGUI::InputText(char* data, int size)
{
	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		wedgets.Item()->InputData(data, size);
	}
}


/// @brief Input axis
/// @param axisX 
/// @param axisY 
/// @param axisZ 
void VkGUI::InputAxis(int axisX, int axisY, int axisZ)
{
	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		wedgets.Item()->InputAxis(axisX, axisY, axisZ);
	}
}


/// @brief Create main window
/// @return 
Wedget* VkGUI::CreateMainWindow()
{
	if (NULL != drawing)
	{
		Wedget* mainwin = new Window();
		mainwin->Setup(drawing, indev);
		mainwin->Resize(0, 0, fbdev->info.width, fbdev->info.height);
		wedgets.Add(mainwin);
		return mainwin;
	}
	return NULL;
}


/// @brief Destory main window
/// @param mainwin 
/// @return 
bool VkGUI::DestroyMainWindow(Wedget* mainwin)
{
	if (NULL != mainwin)
	{
		wedgets.Remove(mainwin);
		delete mainwin;
		return true;
	}
	return false;
}


/// @brief Create cursor
/// @return 
void VkGUI::EnableCursor()
{
	if (NULL != drawing && NULL == cursor)
	{
		cursor = new Cursor();
		cursor->Setup(drawing, indev);
		cursor->Resize(0, 0, fbdev->info.width, fbdev->info.height);
		cursor->InitContent();
		wedgets.Add(cursor);
	}
}


/// @brief Destory cursor
/// @param cursor 
/// @return 
void VkGUI::DisableCursor()
{
	if (NULL != cursor)
	{
		wedgets.Remove(cursor);
		delete cursor;
	}
}
