//###########################################################################
// Taichi.h
// The overall framework of the taichi
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __TAICHI_H__
#define __TAICHI_H__

#include "Executor.h"

///Taichi
class Taichi
{
private:
	//Members
	Executor executor;
public:
	//Methods
	Taichi();
	~Taichi();
	void Initialize();
	void Execute();
};

#endif //!__TAICHI_H__
