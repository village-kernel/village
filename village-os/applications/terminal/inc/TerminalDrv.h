//###########################################################################
// TerminalDrv.h
// Declarations of the termianl drv
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __TERMINAL_DRV_H__
#define __TERMINAL_DRV_H__

#include "TerminalView.h"
#include "Kernel.h"


/// @brief TerminalDrv
class TerminalDrv : public CharDriver
{
private:
	//Members
	TerminalView* view;
public:
	//Methods
	TerminalDrv();
	~TerminalDrv();
	void Setup(TerminalView* view);
	void Exit();

	//Fopts
	bool Open();
	int Write(uint8_t* data, uint32_t size = 0, uint32_t offset = 0);
	int Read(uint8_t* data, uint32_t size = 0, uint32_t offset = 0);
	void Close();
};

#endif //!__TERMINAL_DRV_H__
