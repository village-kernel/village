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
	interrupt.AppendISR(IRQ_ATA_Channel1, (Method)&Exception::ATAChannel1, this);
	interrupt.AppendISR(IRQ_ATA_Channel2, (Method)&Exception::ATAChannel2, this);
	interrupt.AppendISR(IRQ_General_Protection_Fault, (Method)&Exception::GerneralFault, this);
}


/// @brief ATA channel isr
void Exception::ATAChannel1()
{

}


/// @brief ATA channel isr
void Exception::ATAChannel2()
{

}


/// @brief Exception gerneral fault
void Exception::GerneralFault()
{
	debug.Error("Gerneral Fault");
	while(1) {}
}
