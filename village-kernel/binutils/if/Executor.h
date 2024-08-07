//###########################################################################
// Executor.h
// Specifies the interface for all classes that contain executor logic
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __EXECUTOR_INTERFACE_H__
#define __EXECUTOR_INTERFACE_H__

#include "Defines.h"
#include "Class.h"
#include "List.h"


/// @brief BaseExecutor
class BaseExecutor;


/// @brief Executor
class Executor
{
public:
	//Constructor
	Executor() { }

	//Destructor
	virtual ~Executor() { }

	//Methods
	virtual List<char*> GetSuffixes() = 0;
	virtual BaseExecutor* Create() = 0;
};

#endif // !__EXECUTOR_INTERFACE_H__
