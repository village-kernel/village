//###########################################################################
// Exception.cpp
// Definitions of the functions that manage exception
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Exception.h"
#include "Hardware.h"
#include "Kernel.h"


/// @brief ConcreteException
class ConcreteException : public Exception
{
private:
	//Members
	Debug*     debug;
	Interrupt* interrupt;
private:
	/// @brief DivisionByZeroHandler
	void DivisionByZeroHandler()
	{
		debug->Error("Division By Zero");
		while(1) {}
	}


	/// @brief DebugHandler
	void DebugHandler()
	{
		debug->Error("Debug");
		while(1) {}
	}


	/// @brief NonMaskableInterruptHandler
	void NonMaskableInterruptHandler()
	{
		debug->Error("Non Maskable Interrupt");
		while(1) {}
	}


	/// @brief BreakpointHandler
	void BreakpointHandler()
	{
		debug->Error("Breakpoint");
		while(1) {}
	}


	/// @brief IntoDetectedOverflowHandler
	void IntoDetectedOverflowHandler()
	{
		debug->Error("Into Detected Overflow");
		while(1) {}
	}


	/// @brief OutOfBoundsHandler
	void OutOfBoundsHandler()
	{
		debug->Error("Out Of Bounds");
		while(1) {}
	}


	/// @brief InvalidOpcodeHandler
	void InvalidOpcodeHandler()
	{
		debug->Error("Invalid Opcode");
		while(1) {}
	}


	/// @brief NoCoprocessorHandler
	void NoCoprocessorHandler()
	{
		debug->Error("No Coprocessor");
		while(1) {}
	}


	/// @brief DouleFaultHandler
	void DouleFaultHandler()
	{
		debug->Error("Doule Fault");
		while(1) {}
	}


	/// @brief CoprocessorSegmentOverrunHandler
	void CoprocessorSegmentOverrunHandler()
	{
		debug->Error("Coprocessor Segment Overrun");
		while(1) {}
	}


	/// @brief BadTSSHandler
	void BadTSSHandler()
	{
		debug->Error("Bad TSS");
		while(1) {}
	}


	/// @brief SegmentNotPresentHandler
	void SegmentNotPresentHandler()
	{
		debug->Error("Segment Not Present");
		while(1) {}
	}


	/// @brief StackFaultHandler
	void StackFaultHandler()
	{
		debug->Error("Stack Fault");
		while(1) {}
	}


	/// @brief GeneralProtectionFaultHandler
	void GeneralProtectionFaultHandler()
	{
		debug->Error("General Protection Fault");
		while(1) {}
	}


	/// @brief PageFaultHandler
	void PageFaultHandler()
	{
		debug->Error("Page Fault");
		while(1) {}
	}


	/// @brief UnknownInterruptHandler
	void UnknownInterruptHandler()
	{
		debug->Error("Unknown Interrupt");
		while(1) {}
	}


	/// @brief CoprocessorFaultHandler
	void CoprocessorFaultHandler()
	{
		debug->Error("Coprocessor Fault");
		while(1) {}
	}


	/// @brief AlignmentCheckHandler
	void AlignmentCheckHandler()
	{
		debug->Error("Alignment Check");
		while(1) {}
	}


	/// @brief MachineCheckHandler
	void MachineCheckHandler()
	{
		debug->Error("Machine Check");
		while(1) {}
	}
public:
	/// @brief Constructor
	ConcreteException()
		:debug(NULL),
		interrupt(NULL)
	{
	}


	/// @brief Destructor
	~ConcreteException()
	{
	}


	/// @brief Exception Setup
	void Setup()
	{
		//Gets the debug pointer
		debug = (Debug*)kernel->modular->GetModule(ModuleID::_debug);

		//Gets the interrupt pointer
		interrupt = (Interrupt*)kernel->modular->GetModule(ModuleID::_interrupt);

		//Set interrupt service
		interrupt->AppendISR(IRQ_Division_By_Zero,            (Method)&ConcreteException::DivisionByZeroHandler,            this);
		interrupt->AppendISR(IRQ_Debug,                       (Method)&ConcreteException::DebugHandler,                     this);
		interrupt->AppendISR(IRQ_Non_Maskable_Interrupt,      (Method)&ConcreteException::NonMaskableInterruptHandler,      this);
		interrupt->AppendISR(IRQ_Breakpoint,                  (Method)&ConcreteException::BreakpointHandler,                this);
		interrupt->AppendISR(IRQ_Into_Detected_Overflow,      (Method)&ConcreteException::IntoDetectedOverflowHandler,      this);
		interrupt->AppendISR(IRQ_Out_Of_Bounds,               (Method)&ConcreteException::OutOfBoundsHandler,               this);
		interrupt->AppendISR(IRQ_Invalid_Opcode,              (Method)&ConcreteException::InvalidOpcodeHandler,             this);
		interrupt->AppendISR(IRQ_No_Coprocessor,              (Method)&ConcreteException::NoCoprocessorHandler,             this);
		interrupt->AppendISR(IRQ_Doule_Fault,                 (Method)&ConcreteException::DouleFaultHandler,                this);
		interrupt->AppendISR(IRQ_Coprocessor_Segment_Overrun, (Method)&ConcreteException::CoprocessorSegmentOverrunHandler, this);
		interrupt->AppendISR(IRQ_Bad_TSS,                     (Method)&ConcreteException::BadTSSHandler,                    this);
		interrupt->AppendISR(IRQ_Segment_Not_Present,         (Method)&ConcreteException::SegmentNotPresentHandler,         this);
		interrupt->AppendISR(IRQ_Stack_Fault,                 (Method)&ConcreteException::StackFaultHandler,                this);
		interrupt->AppendISR(IRQ_General_Protection_Fault,    (Method)&ConcreteException::GeneralProtectionFaultHandler,    this);
		interrupt->AppendISR(IRQ_Page_Fault,                  (Method)&ConcreteException::PageFaultHandler,                 this);
		interrupt->AppendISR(IRQ_Unknown_Interrupt,           (Method)&ConcreteException::UnknownInterruptHandler,          this);
		interrupt->AppendISR(IRQ_Coprocessor_Fault,           (Method)&ConcreteException::CoprocessorFaultHandler,          this);
		interrupt->AppendISR(IRQ_Alignment_Check,             (Method)&ConcreteException::AlignmentCheckHandler,            this);
		interrupt->AppendISR(IRQ_Machine_Check,               (Method)&ConcreteException::MachineCheckHandler,              this);
	}


	/// @brief Exception Exit
	void Exit()
	{

	}
};


///Register module
REGISTER_MODULE(ConcreteException, ModuleID::_exception, exception);
