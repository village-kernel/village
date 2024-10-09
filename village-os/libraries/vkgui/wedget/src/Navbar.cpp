//###########################################################################
// Navbar.cpp
// Definitions of the functions that manage nav bar
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Navbar.h"


/// @brief 
Navbar::Navbar()
	:title(NULL),
	minbtn(NULL),
	maxbtn(NULL),
	exitbtn(NULL)
{
}


/// @brief 
/// @param title 
void Navbar::SetTitile(char* title)
{
	this->title = title;
}


/// @brief 
/// @return 
char* Navbar::GetTitle()
{
	return this->title;
}


/// @brief 
/// @param drawing 
/// @param x 
/// @param y 
void Navbar::InitContent()
{
	minbtn = new Button();
	minbtn->SetSize(40, 0, 20, 20);
	minbtn->SetText((char*)"-");
	AddWedget(minbtn);

	maxbtn = new Button();
	maxbtn->SetSize(20, 0, 20, 20);
	maxbtn->SetText((char*)"O");
	AddWedget(maxbtn);

	exitbtn = new Button();
	exitbtn->SetSize(0, 0, 20, 20);
	exitbtn->SetText((char*)"X");
	AddWedget(exitbtn);
}


/// @brief 
void Navbar::DrawContent()
{
	if (NULL != title)
	{
		int locX = GetLocX() + (GetWidth() / 2) - (strlen(title) * DrawingDefs::Font16 / 4);
		int locY = GetLocY() + (GetHeight() / 2 - DrawingDefs::Font16 / 2);
		drawing->string.Set(locX, locY, title);
	}
}
