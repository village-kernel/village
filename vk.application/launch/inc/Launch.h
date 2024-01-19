//###########################################################################
// Launch.h
// The overall framework of the launch
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __LAUNCH_H__
#define __LAUNCH_H__

#include "Graphics.h"
#include "Village.h"

///Lanuch
class Launch
{
private:
	//Members
	Graphics graphics;
	Window*  mainwin;
	
	//Methods
	void Movement(Input::InputMove* inputMove);
public:
	//Methods
	Launch();
	~Launch();
	void Initialize(const char* drvname);
	void Execute();
};

#endif //!__LAUNCH_H__
