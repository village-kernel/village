//###########################################################################
// Application3.h
// The overall framework of the program
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __APPLICATION3_H__
#define __APPLICATION3_H__

#include "Module.h"
#include "GUI.h"

///Application
class Application3 : public Module
{
private:
	//Members
	GUI     gui;

	//Methods
	void DisplayDir(const char* name);
public:
	//Methods
	Application3();
	void Initialize();
	void Execute();
};

#endif //!__APPLICATION3_H__
