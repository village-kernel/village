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
	//Static constants members
	static const int btn_width = 20;
	static const int btn_height = 20;
	static const int btn_y = 0;
	static const int exit_btn_x = 0;
	static const int min_btn_x = exit_btn_x + btn_width;
	static const int max_btn_x = min_btn_x + btn_width;

	//Members
	Button exitbtn;
	Button minbtn;
	Button maxbtn;
public:
	//Methods
	Navbar();
	~Navbar();

	//Wedget methods
	Button* GetExitBtn();
	Button* GetMinBtn();
	Button* GetMaxBtn();

	//Area methods
	bool IsInMaximizeArea(int x, int y);
	bool IsInMinimizeArea(int x, int y);
	bool IsInCloseArea(int x, int y);

	//Methods
	void Initiate(VgDevices* devices);
};

#endif //!__VG_NAV_BAR_H__
