//###########################################################################
// Wedget.h
// Declarations of the wedget
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_WEDGET_H__
#define __VK_WEDGET_H__

#include "Drawing.h"
#include "Indev.h"
#include "List.h"


/// @brief Wedget
class Wedget
{
public:
	/// @brief WedgetID
	enum WedgetID
	{
		_Button = 1,
		_Cursor,
		_Frame,
		_Label,
		_ListBox,
		_Menu,
		_MsgBox,
		_Navbar,
		_Scrollbar,
		_Tabbar,
		_TextBox,
		_Toolbar,
		_Window,
	};
protected:
	//Members
	Drawing* drawing;
	Indev*   indev;

	//Members
	List<Wedget*> wedgets;

	//Members
	int x;
	int y;
	int xoff;
	int yoff;
	int width;
	int height;
	bool isChange;
public:
	//Methods
	Wedget();
	virtual ~Wedget();

	//Wedget methods
	virtual void Setup(Drawing* drawing, Indev* indev);
	virtual void Offset(int xoff, int yoff);
	virtual void Resize(int x, int y, int width, int height);
	virtual int GetLocX();
	virtual int GetLocY();
	virtual int GetWidth();
	virtual int GetHeight();
	virtual void InitContent();
	virtual void DrawContent();
	virtual void DrawBorder();

	//Wedgets methods
	virtual Wedget* CreateWedget(WedgetID id);
	virtual bool DestroyWedget(Wedget* wedget);
	virtual void InputData(char* data, int size);
	virtual void InputAxis(int axisX, int axisY, int axisZ);
	virtual void Showing();
	virtual void Refresh();
};

#endif //!__VK_WEDGET_H__
