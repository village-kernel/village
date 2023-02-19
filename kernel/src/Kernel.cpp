//###########################################################################
// kernel.cpp
// Definitions of the functions that manage module object
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "kernel.h"

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

//Test code
#include "Thread.h"
#include "Scheduler.h"
#include "Gpo.h"

void Task0(void)
{
	Gpo led;

	led.Initialize(Gpio::_ChE, 5, Gpio::_Low);

	while(1) 
	{
		led.Set();
		Thread::Sleep(500);
		led.Clear();
		Thread::Sleep(500);
	}
}

void Task1(void)
{
	Gpo led;

	led.Initialize(Gpio::_ChA, 8, Gpio::_Low);

	while (1)
	{
		led.Set();
		Thread::Sleep(500);
		led.Clear();
		Thread::Sleep(500);
	}
}


///Execute module object->Execute
void Kernel::Execute()
{
	//Create tasks
	Thread::CreateTask(Task0);
	Thread::CreateTask(Task1);

	//Initialize and start scheduler 
	Scheduler::Initialize();
	Scheduler::StartScheduler();

	while (1)
	{
		// if (isReady)
		// {
		// 	for (volatile ModuleNode* node = list; NULL != node; node = node->next)
		// 	{
		// 		node->module->Execute();
		// 	}
		// }
	}
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
