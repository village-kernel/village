//###########################################################################
// HexExecutor.h
// Declarations of the functions that manage hex executor
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __HEX_EXECUTOR_H__
#define __HEX_EXECUTOR_H__

#include "BaseExecutor.h"
#include "Executor.h"
#include "HexLoader.h"
#include "Class.h"


/// @brief HexExecutor
class HexExecutor : public BaseExecutor, public Class
{
private:
	//Members
	HexLoader hex;
private:
	//Methods
	int Initiate();
	void Sandbox();
	bool Release();
};


/// @brief HexExecutorFty
class HexExecutorFty : public Executor
{
public:
	List<char*> GetSuffixes();
	BaseExecutor* Create();
};
 
#endif //!__HEX_EXECUTOR_H__
