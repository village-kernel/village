//###########################################################################
// Modular.cpp
// Definitions of the functions that manage module object
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Modular.h"
#include "Environment.h"


///Initialize module core
Modular::ModuleNode* Modular::list = NULL;


///Constructor
Modular::Modular()
{
}


///Execute module object->Initialize
void Modular::Initialize()
{
	for (volatile ModuleNode* node = list; NULL != node; node = node->next)
	{
		node->module->Initialize();
	}
}


///Execute module object->UpdateParams
void Modular::UpdateParams()
{
	for (volatile ModuleNode* node = list; NULL != node; node = node->next)
	{
		node->module->UpdateParams();
	}
}


///Create task threads for each module
void Modular::Execute()
{
	for (volatile ModuleNode* node = list; NULL != node; node = node->next)
	{
		Thread::CreateTask((ThreadHandler)&Modular::Handler, (char*)node->module);
	}
}


///Modular execute handler
void Modular::Handler(Module* module)
{
	module->Execute();
	Modular::DeregisterModule(module);
}


///Execute module object->FailSafe
void Modular::FailSafe(int arg)
{
	for (volatile ModuleNode* node = list; NULL != node; node = node->next)
	{
		node->module->FailSafe(arg);
	}
}


///Register module object
void Modular::RegisterModule(Module* module, uint32_t id)
{
	ModuleNode** nextNode = &list;

	if (module) module->SetID(id); else return;

	while (NULL != *nextNode)
	{
		uint32_t curModuleID = (*nextNode)->module->GetID();
		uint32_t newModuleID = module->GetID();

		if (newModuleID < curModuleID)
		{
			ModuleNode* curNode = *nextNode;
			*nextNode = new ModuleNode(module);
			(*nextNode)->next = curNode;
			return;
		}
		
		nextNode = &(*nextNode)->next;
	}

	*nextNode = new ModuleNode(module);
}
EXPORT_SYMBOL(Modular::RegisterModule, _ZN7Modular14RegisterModuleEP6Modulem);


///Deregister module object
void Modular::DeregisterModule(Module* module, uint32_t id)
{
	ModuleNode** prevNode = &list;
	ModuleNode** currNode = &list;

	if (NULL == module && 0 == id) return;

	while (NULL != *currNode)
	{
		if ((module == (*currNode)->module) || 
			(id == (*currNode)->module->GetID()))
		{
			delete *currNode;

			if (*prevNode == *currNode)
				*prevNode = (*currNode)->next;
			else
				(*prevNode)->next = (*currNode)->next;

			break;
		}
		else
		{
			prevNode = currNode;
			currNode = &(*currNode)->next;
		}
	}
}
EXPORT_SYMBOL(Modular::DeregisterModule, _ZN7Modular16DeregisterModuleEP6Modulem);
