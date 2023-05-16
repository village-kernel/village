//###########################################################################
// VGA.h
// Declarations of the functions that manage x86 VGA
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VGA_H__
#define __VGA_H__

#include "HalHeaders.h"
#include "LcdDriver.h"
#include "Driver.h"


///VGA
class VGA : public Driver, public LcdDriver
{
protected:
	//Methods
	void WriteData(uint16_t reg, uint16_t value);
	uint16_t ReadData(uint16_t reg);
public:
	//Device Methods
	VGA();
	void Initialize();
	
	//Display methods
	void DrawPoint(uint16_t x, uint16_t y, uint16_t color);
	uint16_t ReadPoint(uint16_t x, uint16_t y);
	void Clear(uint16_t color = 0);
};

#endif //!__X86_VGA_H__
