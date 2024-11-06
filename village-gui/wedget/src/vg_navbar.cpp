//###########################################################################
// vg_navbar.cpp
// Definitions of the functions that manage nav bar
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "vg_navbar.h"


/// @brief Constructor
Navbar::Navbar()
	:title(NULL),
	minbtn(NULL),
	maxbtn(NULL),
	exitbtn(NULL)
{
}


/// @brief Destructor
Navbar::~Navbar()
{
}


/// @brief Init content
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


/// @brief Draw content
void Navbar::DrawContent()
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
