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


/// @brief VgNavbar
class VgNavbar : public VgWedget
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
	VgButton exitbtn;
	VgButton minbtn;
	VgButton maxbtn;
public:
	//Methods
	VgNavbar();
	~VgNavbar();

	//Wedget methods
	VgButton* GetExitBtn();
	VgButton* GetMinBtn();
	VgButton* GetMaxBtn();

	//Area methods
	bool IsInMaximizeArea(int x, int y);
	bool IsInMinimizeArea(int x, int y);
	bool IsInCloseArea(int x, int y);
private:
	//Methods
	void InitContent(VgDevices* devices);
	void ExecContent(VgInputData input);
	void DrawContent(VgDrawArea drawArea);
};

#endif //!__VG_NAV_BAR_H__
