//###########################################################################
// Exception.cpp
// Definitions of the functions that manage exception
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Exception.h"
#include "Hardware.h"
#include "Kernel.h"


/// @brief Constructor
Exception::Exception()
{
}


/// @brief Deconstructor
Exception::~Exception()
{
}


/// @brief Exception initialize
void Exception::Initialize()
{
	Kernel::interrupt.AppendISR(IRQ_Division_By_Zero,            (Method)&Exception::DivisionByZeroHandler,            this);
	Kernel::interrupt.AppendISR(IRQ_Debug,                       (Method)&Exception::DebugHandler,                     this);
	Kernel::interrupt.AppendISR(IRQ_Non_Maskable_Interrupt,      (Method)&Exception::NonMaskableInterruptHandler,      this);
	Kernel::interrupt.AppendISR(IRQ_Breakpoint,                  (Method)&Exception::BreakpointHandler,                this);
	Kernel::interrupt.AppendISR(IRQ_Into_Detected_Overflow,      (Method)&Exception::IntoDetectedOverflowHandler,      this);
	Kernel::interrupt.AppendISR(IRQ_Out_Of_Bounds,               (Method)&Exception::OutOfBoundsHandler,               this);
	Kernel::interrupt.AppendISR(IRQ_Invalid_Opcode,              (Method)&Exception::InvalidOpcodeHandler,             this);
	Kernel::interrupt.AppendISR(IRQ_No_Coprocessor,              (Method)&Exception::NoCoprocessorHandler,             this);
	Kernel::interrupt.AppendISR(IRQ_Doule_Fault,                 (Method)&Exception::DouleFaultHandler,                this);
	Kernel::interrupt.AppendISR(IRQ_Coprocessor_Segment_Overrun, (Method)&Exception::CoprocessorSegmentOverrunHandler, this);
	Kernel::interrupt.AppendISR(IRQ_Bad_TSS,                     (Method)&Exception::BadTSSHandler,                    this);
	Kernel::interrupt.AppendISR(IRQ_Segment_Not_Present,         (Method)&Exception::SegmentNotPresentHandler,         this);
	Kernel::interrupt.AppendISR(IRQ_Stack_Fault,                 (Method)&Exception::StackFaultHandler,                this);
	Kernel::interrupt.AppendISR(IRQ_General_Protection_Fault,    (Method)&Exception::GeneralProtectionFaultHandler,    this);
	Kernel::interrupt.AppendISR(IRQ_Page_Fault,                  (Method)&Exception::PageFaultHandler,                 this);
	Kernel::interrupt.AppendISR(IRQ_Unknown_Interrupt,           (Method)&Exception::UnknownInterruptHandler,          this);
	Kernel::interrupt.AppendISR(IRQ_Coprocessor_Fault,           (Method)&Exception::CoprocessorFaultHandler,          this);
	Kernel::interrupt.AppendISR(IRQ_Alignment_Check,             (Method)&Exception::AlignmentCheckHandler,            this);
	Kernel::interrupt.AppendISR(IRQ_Machine_Check,               (Method)&Exception::MachineCheckHandler,              this);
}


/// @brief DivisionByZeroHandler
void Exception::DivisionByZeroHandler()
{
	Kernel::debug.Error("Division By Zero");
	while(1) {}
}


/// @brief DebugHandler
void Exception::DebugHandler()
{
	Kernel::debug.Error("Debug");
	while(1) {}
}


/// @brief NonMaskableInterruptHandler
void Exception::NonMaskableInterruptHandler()
{
	Kernel::debug.Error("Non Maskable Interrupt");
	while(1) {}
}


/// @brief BreakpointHandler
void Exception::BreakpointHandler()
{
	Kernel::debug.Error("Breakpoint");
	while(1) {}
}


/// @brief IntoDetectedOverflowHandler
void Exception::IntoDetectedOverflowHandler()
{
	Kernel::debug.Error("Into Detected Overflow");
	while(1) {}
}


/// @brief OutOfBoundsHandler
void Exception::OutOfBoundsHandler()
{
	Kernel::debug.Error("Out Of Bounds");
	while(1) {}
}


/// @brief InvalidOpcodeHandler
void Exception::InvalidOpcodeHandler()
{
	Kernel::debug.Error("Invalid Opcode");
	while(1) {}
}


/// @brief NoCoprocessorHandler
void Exception::NoCoprocessorHandler()
{
	Kernel::debug.Error("No Coprocessor");
	while(1) {}
}


/// @brief DouleFaultHandler
void Exception::DouleFaultHandler()
{
	Kernel::debug.Error("Doule Fault");
	while(1) {}
}


/// @brief CoprocessorSegmentOverrunHandler
void Exception::CoprocessorSegmentOverrunHandler()
{
	Kernel::debug.Error("Coprocessor Segment Overrun");
	while(1) {}
}


/// @brief BadTSSHandler
void Exception::BadTSSHandler()
{
	Kernel::debug.Error("Bad TSS");
	while(1) {}
}


/// @brief SegmentNotPresentHandler
void Exception::SegmentNotPresentHandler()
{
	Kernel::debug.Error("Segment Not Present");
	while(1) {}
}


/// @brief StackFaultHandler
void Exception::StackFaultHandler()
{
	Kernel::debug.Error("Stack Fault");
	while(1) {}
}


/// @brief GeneralProtectionFaultHandler
void Exception::GeneralProtectionFaultHandler()
{
	Kernel::debug.Error("General Protection Fault");
	while(1) {}
}


/// @brief PageFaultHandler
void Exception::PageFaultHandler()
{
	Kernel::debug.Error("Page Fault");
	while(1) {}
}


/// @brief UnknownInterruptHandler
void Exception::UnknownInterruptHandler()
{
	Kernel::debug.Error("Unknown Interrupt");
	while(1) {}
}


/// @brief CoprocessorFaultHandler
void Exception::CoprocessorFaultHandler()
{
	Kernel::debug.Error("Coprocessor Fault");
	while(1) {}
}


/// @brief AlignmentCheckHandler
void Exception::AlignmentCheckHandler()
{
	Kernel::debug.Error("Alignment Check");
	while(1) {}
}


/// @brief MachineCheckHandler
void Exception::MachineCheckHandler()
{
	Kernel::debug.Error("Machine Check");
	while(1) {}
}
