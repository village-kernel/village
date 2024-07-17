//###########################################################################
// Exception.cpp
// Definitions of the functions that manage exception
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Exception.h"
#include "Hardware.h"


/// @brief Constructor
Exception::Exception()
	:debug(NULL),
	interrupt(NULL)
{
}


/// @brief Destructor
Exception::~Exception()
{
}


/// @brief Exception Setup
void Exception::Setup()
{
	//Gets the debug pointer
	debug = (Debug*)&kernel->debug;

	//Gets the interrupt pointer
	interrupt = (Interrupt*)&kernel->interrupt;

	//Set interrupt service
	interrupt->AppendISR(NonMaskableInt_IRQn,              (Method)&Exception::NMIHandler,            this);
	interrupt->AppendISR(HardFault_IRQn,                   (Method)&Exception::HardFaultHandler,      this);
	interrupt->AppendISR(MemoryManagement_IRQn,            (Method)&Exception::MemManageHandler,      this);
	interrupt->AppendISR(BusFault_IRQn,                    (Method)&Exception::BusFaultHandler,       this);
	interrupt->AppendISR(UsageFault_IRQn,                  (Method)&Exception::UsageFaultHandler,     this);
	interrupt->AppendISR(DebugMonitor_IRQn,                (Method)&Exception::DebugMonHandler,       this);
}


/// @brief Exception Exit
void Exception::Exit()
{
	interrupt->RemoveISR(NonMaskableInt_IRQn,             (Method)&Exception::NMIHandler,            this);
	interrupt->RemoveISR(HardFault_IRQn,                  (Method)&Exception::HardFaultHandler,      this);
	interrupt->RemoveISR(MemoryManagement_IRQn,           (Method)&Exception::MemManageHandler,      this);
	interrupt->RemoveISR(BusFault_IRQn,                   (Method)&Exception::BusFaultHandler,       this);
	interrupt->RemoveISR(UsageFault_IRQn,                 (Method)&Exception::UsageFaultHandler,     this);
	interrupt->RemoveISR(DebugMonitor_IRQn,               (Method)&Exception::DebugMonHandler,       this);
}


/// @brief NMIHandler
void Exception::NMIHandler()
{
	debug->Error("NMI Handler");
	while(1) {}
}


/// @brief HardFaultHandler
void Exception::HardFaultHandler()
{
	debug->Error("Hard Fault Handler");
	while(1) {}
}


/// @brief MemManageHandler
void Exception::MemManageHandler()
{
	debug->Error("Mem Manage Handler");
	while(1) {}
}


/// @brief BusFaultHandler
void Exception::BusFaultHandler()
{
	debug->Error("Bus Fault Handler");
	while(1) {}
}


/// @brief UsageFaultHandler
void Exception::UsageFaultHandler()
{
	debug->Error("Usage Fault Handler");
	while(1) {}
}


/// @brief DebugMonHandler
void Exception::DebugMonHandler()
{
	debug->Error("Debug Mon Handler");
	while(1) {}
}
