//###########################################################################
// Application4.h
// The overall framework of the program
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __APPLICATION4_H__
#define __APPLICATION4_H__

#include "Module.h"
#include "Gpo.h"

class Application4 : public Module
{
private:
	//Gpo led;
public:
	Application4();
	void Initialize();
	void Execute();
};

#endif //!__APPLICATION4_H__
