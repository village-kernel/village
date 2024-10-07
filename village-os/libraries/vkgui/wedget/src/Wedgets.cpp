//###########################################################################
// Wedgets.cpp
// Specifies the interface for all classes that contain wedget
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Wedgets.h"


/// @brief Create Wedget
/// @param id 
/// @return 
Wedget* Wedget::CreateWedget(Wedget::WedgetID id)
{
	Wedget* wedget = NULL;

	switch (id)
	{
		case Wedget::_Button:
			wedget = new Button();
			break;
		case Wedget::_Cursor:
			wedget = new Cursor();
			break;
		case Wedget::_Frame:
			wedget = new Frame();
			break;
		case Wedget::_Label:
			wedget = new Label();
			break;
		case Wedget::_ListBox:
			wedget = new ListBox();
			break;
		case Wedget::_Menu:
			wedget = new Menu();
			break;
		case Wedget::_MsgBox:
			wedget = new MsgBox();
			break;
		case Wedget::_Navbar:
			wedget = new Navbar();
			break;
		case Wedget::_Scrollbar:
			wedget = new Scrollbar();
			break;
		case Wedget::_Tabbar:
			wedget = new Tabbar();
			break;
		case Wedget::_TextBox:
			wedget = new TextBox();
			break;
		case Wedget::_Toolbar:
			wedget = new Toolbar();
			break;
		case Wedget::_Window:
			wedget = new Window();
			break;
		default: break;
	}

	if (NULL != wedget) 
	{
		wedget->Setup(drawing, indev);
		wedget->Offset(GetLocX(), GetLocY());
		wedgets.Add(wedget);
	}

	return wedget;
}


/// @brief 
/// @param wedget 
/// @return 
bool Wedget::DestroyWedget(Wedget* wedget)
{
	if (NULL == wedget)
	{
		wedgets.Remove(wedget);
		return true;
	}
	return false;
}


/// @brief Wedget default input text
/// @param data 
/// @param size 
void Wedget::InputData(char* data, int size)
{
	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		wedgets.Item()->InputData(data, size);
	}
}


/// @brief Wedget default input axis
/// @param axisX 
/// @param axisY 
/// @param axisZ 
void Wedget::InputAxis(int axisX, int axisY, int axisZ)
{
	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		wedgets.Item()->InputAxis(axisX, axisY, axisZ);
	}
}


/// @brief Wedget default showing
void Wedget::Showing()
{
	DrawBorder();
	InitContent();
	DrawContent();
	
	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		wedgets.Item()->Showing();
	}
}


/// @brief Wedget default refresh
void Wedget::Refresh()
{
	if (true == isChange)
	{
		DrawContent();
		isChange = false;
	}

	for (wedgets.Begin(); !wedgets.IsEnd(); wedgets.Next())
	{
		wedgets.Item()->Refresh();
	}
}
