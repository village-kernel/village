//###########################################################################
// Wedget.h
// Specifies the interface for all classes that contain wedget
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_WEDGET_H__
#define __VK_WEDGET_H__

#include "Display.h"
#include "List.h"


///Wedget
class Wedget
{
public:
	//Enumerations
	enum WedgetID
	{
		_Button = 1,
		_Cursor,
		_Frame,
		_Label,
		_ListBox,
		_Menu,
		_MsgBox,
		_Tabbar,
		_TextBox,
		_Toolbar,
		_Window,
	};

	enum Alignment
	{
		
	};
protected:
	//Display driver
	Display* display;

	//Wedget lists
	List<Wedget*> wedgets;

	//Attribute
	int      x;
	int      y;
	int      xoff;
	int      yoff;
	int      width;
	int      height;
	Wedget*  bg;

	//Methods
	int GetLocX();
	int GetLocY();
public:
	//Methods
	Wedget();
	virtual ~Wedget();
	virtual Wedget* CreateWedget(WedgetID id);
	virtual void SetDisplay(Display* display);
	virtual void SetLocation(int x, int y, int width, int height);
	virtual void SetLocationOffset(int xoff, int yoff);
	virtual void SetBackground(Wedget* bg);
	virtual void Initialize();
	virtual void Show();
};

#endif //!__VK_WEDGET_H__
