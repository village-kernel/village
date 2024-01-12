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
	//Members
	GUI gui;
public:
	//Methods
	Launch();
	~Launch();
	void Initialize(const char* driver);
	void Execute();
};

#endif //!__LAUNCH_H__
