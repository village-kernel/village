//###########################################################################
// Navbar.h
// Declarations of the functions that manage nav bar
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_NAV_BAR_H__
#define __VK_NAV_BAR_H__

#include "Wedget.h"
#include "Button.h"


/// @brief Navbar
class Navbar : public Wedget
{
private:
	//Members
	char* title;
	Button* minbtn;
	Button* maxbtn;
	Button* exitbtn;
public:
	//Methods
	Navbar();
	void SetTitile(char* title);
	char* GetTitle();
	void InitContent();
	void DrawContent();
};

#endif //!__VK_NAV_BAR_H__
