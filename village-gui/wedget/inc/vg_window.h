//###########################################################################
// vg_window.h
// Declarations of the functions that manage window
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_WINDOW_H__
#define __VG_WINDOW_H__

#include "vg_wedget.h"
#include "vg_navbar.h"


/// @brief Window
class Window : public Wedget
{
public:
	//Enumerations
	enum Place
	{
		_Top = 1,
		_Middle,
		_Bottom
	};
private:
	//Members
	Navbar navbar;

	//Attribute members
	bool focus;
	Place place;
public:
	//Methods
	Window();
	~Window();
	
	//Area methods
	void SetSize(int width, int height);
	void Resize(int x, int y, int axisx, int axisy);
	bool IsInMoveArea(int x, int y);
	bool IsInResizeArea(int x, int y);

	//Attribute methods
	void SetEnableNavbar(bool enable);
	bool IsEnableNavbar();

	void SetHiddenNavbar(bool hidden);
	bool IsHiddenNavbar();

	void SetAlwaysFocus(bool focus);
	bool IsAlwaysFocus();

	void SetPlace(Place place);
	Place GetPlace();

	//Methods
	void Initiate(VgDevices* devices);
	void Execute(IndevData input);
};

#endif //!__VG_WINDOW_H__
