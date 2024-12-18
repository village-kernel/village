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
	Button exitbtn;
	Button minbtn;
	Button maxbtn;
public:
	//Methods
	Navbar();
	~Navbar();

	//Methods
	void Initiate(VgDevices* devices);
};

#endif //!__VG_NAV_BAR_H__
