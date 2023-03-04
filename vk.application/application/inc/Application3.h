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
class Application3 : public Module, public ThreadEndpoint
{
private:

public:
	//Methods
	Application3();
	void Initialize();
	void Execute();

	//Static methods
	static void TaskHandler();
};

#endif //!__APPLICATION3_H__
