//###########################################################################
// vk_bin_executor.h
// Declarations of the functions that manage bin executor
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_BIN_EXECUTOR_H__
#define __VK_BIN_EXECUTOR_H__

#include "vk_executor.h"
#include "vk_base_executor.h"
#include "vk_bin_loader.h"
#include "vk_class.h"


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
	VkList<char*> GetSuffixes();
	BaseExecutor* Create();
};
 
#endif //!__VK_BIN_EXECUTOR_H__
