//###########################################################################
// vk_hex_executor.h
// Declarations of the functions that manage hex executor
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_HEX_EXECUTOR_H__
#define __VK_HEX_EXECUTOR_H__

#include "vk_executor.h"
#include "vk_base_executor.h"
#include "vk_hex_loader.h"
#include "vk_class.h"


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
	VkList<char*> GetSuffixes();
	BaseExecutor* Create();
};
 
#endif //!__VK_HEX_EXECUTOR_H__
