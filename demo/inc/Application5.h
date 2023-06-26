//###########################################################################
// Application5.h
// The overall framework of the program
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __APPLICATION5_H__
#define __APPLICATION5_H__

#include "Module.h"
#include "WorkQueue.h"
#include "GUI.h"


///Application
class Application5 : public Module
{
private:
	//Static constants
	static const int work_delay = 10;

	//Members
	GUI              gui;
	WorkQueue::Work* work;
	uint8_t          keycode;

	//Methods
	void Test1();
	void Test2();
	void ExtHandler();
	void PrintLetter();
public:
	//Methods
	Application5();
	void Initialize();
	void Execute();
};

#endif //!__APPLICATION5_H__
