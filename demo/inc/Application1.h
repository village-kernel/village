//###########################################################################
// Application1.h
// The overall framework of the program
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __APPLICATION1_H__
#define __APPLICATION1_H__

#include "Module.h"
#include "Gpo.h"
#include "Gpi.h"
#include "Exti.h"
#include "WorkQueue.h"


///Application
class Application1 : public Module
{
private:
	//Static constants
	static const int work_delay = 10;

	//Members
	Gpo  led;
	Gpo  extLed;
	Gpi  extKey;
	Exti exti;
	
	//WorkQueue
	WorkQueue::Work* work;

	//Methods
	void ExtHandler();
	void WorkHandler();
public:
	//Methods
	Application1();
	void Initialize();
	void Execute();
};

#endif //!__APPLICATION1_H__
