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
class Application2 : public Module
{
private:
	//Members
	Gpo led;
public:
	//Methods
	Application2();
	void Initialize();
	void Execute();
};

#endif //!__APPLICATION2_H__
