//###########################################################################
// vg_window.h
// Declarations of the functions that manage window
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VG_WINDOW_H__
#define __VG_WINDOW_H__

#include "vg_math.h"
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

	enum ResizeSide
	{
		_LeftSide  = 1,
		_RightSide = 2,
		_UpSide    = 4,
		_DownSide  = 8,
	};
private:
	//Static constants members
	static const int navbar_height = 20;
	static const int resize_range = 5;

	//Members
	Navbar navbar;

	//Attribute members
	bool focus;
	Place place;
	int resizeSide;

	//Members
	Math math;
public:
	//Methods
	Window();
	~Window();
	
	//Area methods
	bool IsInMoveArea(int x, int y);
	bool IsInResizeArea(int x, int y);
	bool IsInMaximizeArea(int x, int y);
	bool IsInMinimizeArea(int x, int y);
	bool IsInCloseArea(int x, int y);
	void SetSize(int width, int height);
	void Adjust(int axisx, int axisy);
	void Maximize();
	void Minimize();
	void Close();

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
