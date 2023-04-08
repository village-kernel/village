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


///Application
class Application1 : public Module
{
private:
	//Members
	Gpo led;
	Gpo extLed;
	Gpi extKey;
	Exti exti;

	//Methods
	void ExtHandler();
public:
	//Methods
	Application1();
	void Initialize();
	void Execute();
};

#endif //!__APPLICATION1_H__
