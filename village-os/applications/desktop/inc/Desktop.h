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
class Desktop : public Driver
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
	TextBox* textbox;
	Cursor*  cursor;

	//Methods
	void SetupWin(const char* screen);
	void UpdateKey(InputEvent::Key* input);
	void UpdateLoc(InputEvent::Loc* input);
public:
	//Methods
	Desktop();
	~Desktop();
	void Initialize(const char* screen);
	void Execute();

	//Driver
	bool Open();
	int Write(uint8_t* data, uint32_t size = 0, uint32_t offset = 0);
	int Read(uint8_t* data, uint32_t size = 0, uint32_t offset = 0);
	void Close();
};

#endif //!__DESKTOP_H__
