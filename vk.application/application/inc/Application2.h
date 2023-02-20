//###########################################################################
// Application2.h
// The overall framework of the program
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __APPLICATION2_H__
#define __APPLICATION2_H__

#include "Module.h"
#include "Gpo.h"


///Application
class Application2 : public Module, public ThreadEndpoint
{
private:
	Gpo led;
	static ThreadEndpoint* user;
	static ThreadHandlerCpp handler;

	//Methods
	void Task();
public:
	//Methods
	Application2();
	void Initialize();
	void Execute();

	//Static methods
	static void TaskHandler();
};

#endif //!__APPLICATION2_H__
