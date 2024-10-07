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


/// @brief Create item
/// @param name 
void Tabbar::CreateItem(const char* name)
{
	Button* item = (Button*)CreateWedget(Wedget::_Button);
	item->Resize((itemSize * 40) + 10, 5, 30, 30);
	item->SetText((char*)name);
	itemSize++;
}
