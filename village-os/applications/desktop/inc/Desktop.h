//###########################################################################
// Desktop.h
// The overall framework of the desktop
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DESKTOP_H__
#define __DESKTOP_H__

#include "Graphics.h"
#include "Kernel.h"


///Lanuch
class Desktop : public Class
{
private:
	//Members
	Graphics graphics;
	Window*  mainwin;
	Toolbar* toolbar;
	Tabbar*  tabbar;
	Label*   label;
	Button*  button1;
	Button*  button2;
	Button*  button3;
	Button*  button4;
	Cursor*  cursor;

	//Methods
	void UpdateKey(InputEvent::Key* input);
	void UpdateLoc(InputEvent::Loc* input);
public:
	//Methods
	Desktop();
	~Desktop();
	void Initialize(const char* screen, const char* keyboard, const char* mouse);
	void Execute();
};

#endif //!__DESKTOP_H__
