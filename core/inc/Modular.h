//###########################################################################
// Modular.h
// Declarations of the functions that manage module object
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __MODULAR_H__
#define __MODULAR_H__

#include "Module.h"
#include "Templates.h"


///Modular
class Modular
{
private:
	//Members
	bool isRuntime;
	List<Module> modules;

	//Methods
	Modular();
	~Modular();
	void RegisterRuntime(Module* module);
	void DeregisterExit(Module* module);
	static void Handler(Module* module);
public:
	//Methods
	void Initialize();
	void UpdateParams();
	void Execute();
	void FailSafe(int arg);
	void RegisterModule(Module* module, uint32_t id = 0);
	void DeregisterModule(Module* module, uint32_t id = 0);

	//Singleton Instance
	static Modular& Instance();
};

///Declarations modular reference
extern Modular& modular;

#endif // !__MODULAR_H__
