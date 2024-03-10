//###########################################################################
// BinExecutor.h
// Declarations of the functions that manage bin executor
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __BIN_EXECUTOR_H__
#define __BIN_EXECUTOR_H__

#include "BaseExecutor.h"
#include "BinLoader.h"
#include "Class.h"


/// @brief BinExecutor
class BinExecutor : public BaseExecutor, public Class
{
private:
	//Members
	BinLoader bin;
private:
	//Methods
	int Execute(const char* path);
	void Sandbox();
};

#endif //!__BIN_EXECUTOR_H__
