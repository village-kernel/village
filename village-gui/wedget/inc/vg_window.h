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


/// @brief VgWindow
class VgWindow : public VgWedget
{
public:
	//Enumerations
	enum Place
	{
		_Bottom = 1,
		_Middle,
		_Top,
	};

	enum ResizeMethod
	{
		_None = 0,
		_Move,
		_Adjust,
		_Maximize,
		_Minimize,
		_Close,
	};

	enum ResizeSide
	{
		_LeftSide  = 1,
		_RightSide = 2,
		_UpSide    = 4,
		_DownSide  = 8,
	};
protected:
	//Static constants members
	static const int navbar_height = 20;
	static const int resize_range = 5;

	//Members
	VgNavbar navbar;

	//Attribute members
	bool focus;
	Place place;
	
	//Members
	int           resizeSide;
	ResizeMethod  resizeMethod;
	VgUpdateAreas resizeAreas;

	//Members
	VgMath math;
public:
	//Methods
	VgWindow();
	~VgWindow();

	//Wedget methods
	VgNavbar* GetNavbar();

	//Area methods
	bool IsInMoveArea(int x, int y);
	bool IsInResizeArea(int x, int y);
	bool IsInMaximizeArea(int x, int y);
	bool IsInMinimizeArea(int x, int y);
	bool IsInCloseArea(int x, int y);
	void SetSize(int width, int height);
	void Adjust(int axisx, int axisy);
	void SetFullScreen();
	void ShowOnCenter();
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

	//Window methods
	bool IsCloseRequest();
	bool IsResizeRequest();
	void ClearResizeRequest();
	VgUpdateAreas GetResizeAreas();
protected:
	//Methods
	bool IsResizeMode(VgInputData input);
	ResizeMethod CheckResizeMethod(VgInputData input);
	VgDrawAreas GetResizeAreas(VgInputData input);
private:
	//Methods
	void InitContent(VgDevices* devices);
	void ExecContent(VgInputData input);
	void DrawContent(VgDrawArea drawArea);
};

#endif //!__VG_WINDOW_H__
