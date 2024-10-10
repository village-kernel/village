//###########################################################################
// Tabbar.cpp
// Definitions of the functions that manage tab bar
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Tabbar.h"


/// @brief Constructor
Tabbar::Tabbar()
	:itemSize(0)
{
}


/// @brief Destructor
Tabbar::~Tabbar()
{
}


/// @brief Init content
void Tabbar::InitContent()
{

}


/// @brief Draw content
void Tabbar::DrawContent()
{

}


/// @brief Add item
/// @param name 
void Tabbar::AddItem(const char* name)
{
	Button* item = new Button();
	item->SetSize((itemSize * 40) + 10, 5, 30, 30);
	item->SetText((char*)name);
	itemSize++;
	AddWedget(item);
}
