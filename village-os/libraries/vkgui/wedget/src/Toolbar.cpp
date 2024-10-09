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


/// @brief Add item
/// @param name 
void Toolbar::AddItem(const char* name)
{
	Button* item = new Button();
	item->SetSize((itemSize * 40) + 10, 5, 30, 30);
	item->SetText((char*)name);
	itemSize++;
	AddWedget(item);
}
