//###########################################################################
// BinExecutor.h
// Declarations of the functions that manage bin executor
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __BIN_EXECUTOR_H__
#define __BIN_EXECUTOR_H__

#include "BaseExecutor.h"
#include "Executor.h"
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
	int Initiate();
	void Sandbox();
	bool Release();
};


/// @brief BinExecutorFty
class BinExecutorFty : public Executor
{
public:
	List<char*> GetSuffixes();
	BaseExecutor* Create();
};
 
#endif //!__BIN_EXECUTOR_H__
