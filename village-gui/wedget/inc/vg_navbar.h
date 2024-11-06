//###########################################################################
// vg_navbar.h
// Declarations of the functions that manage nav bar
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_NAV_BAR_H__
#define __VG_NAV_BAR_H__

#include "vg_wedget.h"
#include "vg_button.h"


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

#endif //!__VG_NAV_BAR_H__
