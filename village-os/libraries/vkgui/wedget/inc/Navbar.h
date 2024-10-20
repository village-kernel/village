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
	~Navbar();

	void InitContent();
	void DrawContent();

	void SetTitile(char* title);
	char* GetTitle();
};

#endif //!__VK_NAV_BAR_H__
