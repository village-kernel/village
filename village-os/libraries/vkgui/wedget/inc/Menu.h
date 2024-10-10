//###########################################################################
// Menu.h
// Declarations of the functions that manage menu
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_MENU_H__
#define __VK_MENU_H__

#include "Wedget.h"


/// @brief Menu
class Menu : public Wedget
{
public:
	//Methods
	Menu();
	~Menu();

	void InitContent();
	void DrawContent();
};

#endif //!__VK_MENU_H__
