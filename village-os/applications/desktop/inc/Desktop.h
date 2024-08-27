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
class Desktop : public CharDriver, public Class
{
private:
	//Members
	Graphics graphics;
	Window*  mainwin;
	Toolbar* toolbar;
	Tabbar*  tabbar;
	Button*  button0;
	Button*  button1;
	Button*  button2;
	Button*  button3;
	Button*  button4;
	Frame*   frame;
	TextBox* textbox;
	Cursor*  cursor;

	//Members
	InputEvent::OutputText outText;

	//Methods
	bool SetupWin();
	void UpdateText(InputEvent::OutputText* input);
	void UpdateAxis(InputEvent::OutputAxis* input);
public:
	//Methods
	Desktop();
	~Desktop();
	void Setup();
	void Execute();
	void Exit();

	//Fopts
	bool Open();
	int Write(uint8_t* data, uint32_t size = 0, uint32_t offset = 0);
	int Read(uint8_t* data, uint32_t size = 0, uint32_t offset = 0);
	void Close();
};

#endif //!__DESKTOP_H__
