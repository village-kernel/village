//###########################################################################
// kernel.cpp
// Definitions of the functions that manage module object
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "kernel.h"
#include "Thread.h"
#include "Scheduler.h"


///Initialize module core
Kernel::ModuleNode* Kernel::list = NULL;

///Clear isReady flag
volatile bool Kernel::isReady = false;

///Constructor
Kernel::Kernel()
{
}


///Execute module object->Initialize
void Kernel::Initialize()
{
	isReady = false;

	//Initialize thread
	Thread::Initialize();

	//Add LoopFunc to thread task
	Thread::CreateTask(Kernel::LoopFunc);

	//Initialize modules
	for (volatile ModuleNode* node = list; NULL != node; node = node->next)
	{
		node->module->Initialize();
	}

	isReady = true;
}


///Execute module object->UpdateParams
void Kernel::UpdateParams()
{
	if (!isReady) return;

	for (volatile ModuleNode* node = list; NULL != node; node = node->next)
	{
		node->module->UpdateParams();
	}
}


///Execute module object->Execute
void Kernel::LoopFunc()
{
	while (1)
	{
		if (isReady)
		{
			for (volatile ModuleNode* node = list; NULL != node; node = node->next)
			{
				node->module->Execute();
			}
		}
	}
}


///Start scheduler
void Kernel::Execute()
{
	Scheduler::StartScheduler();

	while (1) {}
}


///Execute module object->FailSafe
void Kernel::FailSafe(int arg)
{
	if (!isReady) return;

	for (volatile ModuleNode* node = list; NULL != node; node = node->next)
	{
		node->module->FailSafe(arg);
	}
}


///Register module object
void Kernel::RegisterModule(Module* module, uint32_t id)
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


///Deregister module object
void Kernel::DeregisterModule(Module* module, uint32_t id)
{
	ModuleNode** prevNode = &list;
	ModuleNode** currNode = &list;

	while (NULL != *currNode)
	{
		if (module == (*currNode)->module)
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
