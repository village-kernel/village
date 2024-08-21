 //###########################################################################
// Pit32Timer.cpp
// Definitions of the functions that manage pit32 timer
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Driver.h"
#include "Kernel.h"
#include "Hardware.h"


/// @brief Pit32Timer
class Pit32Timer : public CharDevice
{
private:
	//Members
	uint32_t timer;
	uint32_t TIMERX[3] = {TIMER_CH0, TIMER_CH1, TIMER_CH2};
public:
	/// @brief Constructor
	/// @param timer 
	Pit32Timer(uint32_t timer = 0)
		:timer(0)
	{
		if (timer >= 0 && timer <= 2) this->timer = timer;
	}


	/// @brief Open
	bool Open()
	{
		//uint32_t freq = 1000; //1000hz, 1ms
		//uint32_t divider = 1193182 / freq;
		//uint8_t low  = low_8(divider);
		//uint8_t high = high_8(divider);

		//PortByteOut(TIMERX[timer], 0x36); //Command port
		//PortByteOut(TIMERX[timer], low);
		//PortByteOut(TIMERX[timer], high);
	}


	/// @brief Close
	void Close()
	{

	}
};


///Register device
REGISTER_MISC_DEVICE(new Pit32Timer(), pit32Timer);
