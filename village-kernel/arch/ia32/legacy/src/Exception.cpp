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
	interrupt->AppendISR(Division_By_Zero_IRQn,            (Method)&Exception::DivisionByZeroHandler,            this);
	interrupt->AppendISR(Debug_IRQn,                       (Method)&Exception::DebugHandler,                     this);
	interrupt->AppendISR(Non_Maskable_Interrupt_IRQn,      (Method)&Exception::NonMaskableInterruptHandler,      this);
	interrupt->AppendISR(Breakpoint_IRQn,                  (Method)&Exception::BreakpointHandler,                this);
	interrupt->AppendISR(Into_Detected_Overflow_IRQn,      (Method)&Exception::IntoDetectedOverflowHandler,      this);
	interrupt->AppendISR(Out_Of_Bounds_IRQn,               (Method)&Exception::OutOfBoundsHandler,               this);
	interrupt->AppendISR(Invalid_Opcode_IRQn,              (Method)&Exception::InvalidOpcodeHandler,             this);
	interrupt->AppendISR(No_Coprocessor_IRQn,              (Method)&Exception::NoCoprocessorHandler,             this);
	interrupt->AppendISR(Doule_Fault_IRQn,                 (Method)&Exception::DouleFaultHandler,                this);
	interrupt->AppendISR(Coprocessor_Segment_Overrun_IRQn, (Method)&Exception::CoprocessorSegmentOverrunHandler, this);
	interrupt->AppendISR(Bad_TSS_IRQn,                     (Method)&Exception::BadTSSHandler,                    this);
	interrupt->AppendISR(Segment_Not_Present_IRQn,         (Method)&Exception::SegmentNotPresentHandler,         this);
	interrupt->AppendISR(Stack_Fault_IRQn,                 (Method)&Exception::StackFaultHandler,                this);
	interrupt->AppendISR(General_Protection_Fault_IRQn,    (Method)&Exception::GeneralProtectionFaultHandler,    this);
	interrupt->AppendISR(Page_Fault_IRQn,                  (Method)&Exception::PageFaultHandler,                 this);
	interrupt->AppendISR(Unknown_Interrupt_IRQn,           (Method)&Exception::UnknownInterruptHandler,          this);
	interrupt->AppendISR(Coprocessor_Fault_IRQn,           (Method)&Exception::CoprocessorFaultHandler,          this);
	interrupt->AppendISR(Alignment_Check_IRQn,             (Method)&Exception::AlignmentCheckHandler,            this);
	interrupt->AppendISR(Machine_Check_IRQn,               (Method)&Exception::MachineCheckHandler,              this);
}


/// @brief Exception Exit
void Exception::Exit()
{
	interrupt->RemoveISR(Division_By_Zero_IRQn,            (Method)&Exception::DivisionByZeroHandler,            this);
	interrupt->RemoveISR(Debug_IRQn,                       (Method)&Exception::DebugHandler,                     this);
	interrupt->RemoveISR(Non_Maskable_Interrupt_IRQn,      (Method)&Exception::NonMaskableInterruptHandler,      this);
	interrupt->RemoveISR(Breakpoint_IRQn,                  (Method)&Exception::BreakpointHandler,                this);
	interrupt->RemoveISR(Into_Detected_Overflow_IRQn,      (Method)&Exception::IntoDetectedOverflowHandler,      this);
	interrupt->RemoveISR(Out_Of_Bounds_IRQn,               (Method)&Exception::OutOfBoundsHandler,               this);
	interrupt->RemoveISR(Invalid_Opcode_IRQn,              (Method)&Exception::InvalidOpcodeHandler,             this);
	interrupt->RemoveISR(No_Coprocessor_IRQn,              (Method)&Exception::NoCoprocessorHandler,             this);
	interrupt->RemoveISR(Doule_Fault_IRQn,                 (Method)&Exception::DouleFaultHandler,                this);
	interrupt->RemoveISR(Coprocessor_Segment_Overrun_IRQn, (Method)&Exception::CoprocessorSegmentOverrunHandler, this);
	interrupt->RemoveISR(Bad_TSS_IRQn,                     (Method)&Exception::BadTSSHandler,                    this);
	interrupt->RemoveISR(Segment_Not_Present_IRQn,         (Method)&Exception::SegmentNotPresentHandler,         this);
	interrupt->RemoveISR(Stack_Fault_IRQn,                 (Method)&Exception::StackFaultHandler,                this);
	interrupt->RemoveISR(General_Protection_Fault_IRQn,    (Method)&Exception::GeneralProtectionFaultHandler,    this);
	interrupt->RemoveISR(Page_Fault_IRQn,                  (Method)&Exception::PageFaultHandler,                 this);
	interrupt->RemoveISR(Unknown_Interrupt_IRQn,           (Method)&Exception::UnknownInterruptHandler,          this);
	interrupt->RemoveISR(Coprocessor_Fault_IRQn,           (Method)&Exception::CoprocessorFaultHandler,          this);
	interrupt->RemoveISR(Alignment_Check_IRQn,             (Method)&Exception::AlignmentCheckHandler,            this);
	interrupt->RemoveISR(Machine_Check_IRQn,               (Method)&Exception::MachineCheckHandler,              this);
}


/// @brief DivisionByZeroHandler
void Exception::DivisionByZeroHandler()
{
	debug->Error("Division By Zero");
	while(1) {}
}


/// @brief DebugHandler
void Exception::DebugHandler()
{
	debug->Error("Debug");
	while(1) {}
}


/// @brief NonMaskableInterruptHandler
void Exception::NonMaskableInterruptHandler()
{
	debug->Error("Non Maskable Interrupt");
	while(1) {}
}


/// @brief BreakpointHandler
void Exception::BreakpointHandler()
{
	debug->Error("Breakpoint");
	while(1) {}
}


/// @brief IntoDetectedOverflowHandler
void Exception::IntoDetectedOverflowHandler()
{
	debug->Error("Into Detected Overflow");
	while(1) {}
}


/// @brief OutOfBoundsHandler
void Exception::OutOfBoundsHandler()
{
	debug->Error("Out Of Bounds");
	while(1) {}
}


/// @brief InvalidOpcodeHandler
void Exception::InvalidOpcodeHandler()
{
	debug->Error("Invalid Opcode");
	while(1) {}
}


/// @brief NoCoprocessorHandler
void Exception::NoCoprocessorHandler()
{
	debug->Error("No Coprocessor");
	while(1) {}
}


/// @brief DouleFaultHandler
void Exception::DouleFaultHandler()
{
	debug->Error("Doule Fault");
	while(1) {}
}


/// @brief CoprocessorSegmentOverrunHandler
void Exception::CoprocessorSegmentOverrunHandler()
{
	debug->Error("Coprocessor Segment Overrun");
	while(1) {}
}


/// @brief BadTSSHandler
void Exception::BadTSSHandler()
{
	debug->Error("Bad TSS");
	while(1) {}
}


/// @brief SegmentNotPresentHandler
void Exception::SegmentNotPresentHandler()
{
	debug->Error("Segment Not Present");
	while(1) {}
}


/// @brief StackFaultHandler
void Exception::StackFaultHandler()
{
	debug->Error("Stack Fault");
	while(1) {}
}


/// @brief GeneralProtectionFaultHandler
void Exception::GeneralProtectionFaultHandler()
{
	debug->Error("General Protection Fault");
	while(1) {}
}


/// @brief PageFaultHandler
void Exception::PageFaultHandler()
{
	debug->Error("Page Fault");
	while(1) {}
}


/// @brief UnknownInterruptHandler
void Exception::UnknownInterruptHandler()
{
	debug->Error("Unknown Interrupt");
	while(1) {}
}


/// @brief CoprocessorFaultHandler
void Exception::CoprocessorFaultHandler()
{
	debug->Error("Coprocessor Fault");
	while(1) {}
}


/// @brief AlignmentCheckHandler
void Exception::AlignmentCheckHandler()
{
	debug->Error("Alignment Check");
	while(1) {}
}


/// @brief MachineCheckHandler
void Exception::MachineCheckHandler()
{
	debug->Error("Machine Check");
	while(1) {}
}
