//###########################################################################
// Feature.h
// Declarations of the functions that manage module object
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __FEATURE_H__
#define __FEATURE_H__

#include "Kernel.h"
#include "Module.h"
#include "List.h"


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
	void DeregisterModule(Module* module);

	/// @brief Data Methods
	Module* GetModule(const char* name);
};

#endif // !__FEATURE_H__
