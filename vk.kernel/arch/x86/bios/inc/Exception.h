//###########################################################################
// Exception.h
// Declarations of the functions that manage exception
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include "Templates.h"


/// @brief Exception
class Exception : public Class
{
private:
	//Methods
	void DivisionByZeroHandler();
	void DebugHandler();
	void NonMaskableInterruptHandler();
	void BreakpointHandler();
	void IntoDetectedOverflowHandler();
	void OutOfBoundsHandler();
	void InvalidOpcodeHandler();
	void NoCoprocessorHandler();
	void DouleFaultHandler();
	void CoprocessorSegmentOverrunHandler();
	void BadTSSHandler();
	void SegmentNotPresentHandler();
	void StackFaultHandler();
	void GeneralProtectionFaultHandler();
	void PageFaultHandler();
	void UnknownInterruptHandler();
	void CoprocessorFaultHandler();
	void AlignmentCheckHandler();
	void MachineCheckHandler();
public:
	//Methods
	Exception();
	~Exception();
	void Initialize();
};

#endif //!__EXCEPTION_H__
