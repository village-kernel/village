//###########################################################################
// vk_feature.h
// Declarations of the functions that manage module object
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_FEATURE_H__
#define __VK_FEATURE_H__

#include "vk_kernel.h"
#include "vk_module.h"
#include "vk_list.h"


/// @brief ConcreteFeature
class ConcreteFeature : public Feature
{
private:
	/// @brief Members
	bool isRuntime;
	List<Module*> modules;
public:
	/// @brief Methods
	ConcreteFeature();
	~ConcreteFeature();
	void Setup();
	void Exit();

	/// @brief Register Methods
	void RegisterModule(Module* module);
	void UnregisterModule(Module* module);

	/// @brief Data Methods
	Module* GetModule(const char* name);
};

#endif // !__VK_FEATURE_H__
