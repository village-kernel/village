//###########################################################################
// Launch.h
// The overall framework of the launch
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __LAUNCH_H__
#define __LAUNCH_H__

#include "GUI.h"

///Lanuch
class Launch
{
private:
	GUI     gui;
public:
	//Methods
	Launch();
	~Launch();
	void Initialize();
	void Execute();
};

#endif //!__LAUNCH_H__
