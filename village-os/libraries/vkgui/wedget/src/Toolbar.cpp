//###########################################################################
// Toolbar.cpp
// Definitions of the functions that manage tool bar
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Toolbar.h"


/// @brief Constructor
Toolbar::Toolbar()
	:itemSize(0)
{
}


/// @brief Destructor
Toolbar::~Toolbar()
{
}


/// @brief Create item
/// @param name 
void Toolbar::CreateItem(const char* name)
{
	Button* item = (Button*)CreateWedget(Wedget::_Button);
	item->Resize((itemSize * 40) + 10, 5, 30, 30);
	item->SetText((char*)name);
	itemSize++;
}
