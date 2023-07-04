//###########################################################################
// Exception.cpp
// Definitions of the functions that manage exception
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Exception.h"
#include "Interrupt.h"
#include "Hardware.h"
#include "Debug.h"


/// @brief Constructor
Exception::Exception()
{
}


/// @brief Deconstructor
Exception::~Exception()
{
}


/// @brief Singleton Instance
/// @return Exception instance
Exception& Exception::Instance()
{
	static Exception instance;
	return instance;
}


/// @brief Definitions exception
Exception& exception = Exception::Instance();


/// @brief Exception initialize
void Exception::Initialize()
{
	interrupt.AppendISR(IRQ_General_Protection_Fault, (Method)&Exception::GerneralFault, this);
}


/// @brief Exception gerneral fault
void Exception::GerneralFault()
{
	debug.Error("Gerneral Fault");
	while(1) {}
}
