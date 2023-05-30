//###########################################################################
// Application5.h
// The overall framework of the program
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __APPLICATION5_H__
#define __APPLICATION5_H__

#include "Module.h"
#include "GUI.h"


///Application
class Application5 : public Module
{
private:
	//Members
	GUI     gui;

	//Methods
	void Test1();
	void Test2();
	void ExtHandler();
	void PrintLetter(uint8_t scancode);
public:
	//Methods
	Application5();
	void Initialize();
	void Execute();
};

#endif //!__APPLICATION5_H__
