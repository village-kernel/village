//###########################################################################
// pinParser.h
// Parse pins configuration
//
// $Copyright: Copyright (C) jingwei
//###########################################################################
#include <stdlib.h>
#include <string>
#include "Gpo.h"


///PinParser
class PinParser
{
public:
	///Constructor
	PinParser()
	{}

	///Gets the pin channel
	static inline Gpio::GpioChannel Cha(std::string str)
	{
		if (str != "NULL")
			return Gpio::GpioChannel(str.substr(1, 2).c_str()[0] - 'A');
		else
			return Gpio::GpioChannel(__null);
	}

	///Gets the pin number
	static inline uint16_t Pin(std::string str)
	{
		if (str != "NULL")
			return atoi(str.substr(2, 2).c_str());
		else
			return 0;
	}

	///Gets the pin alt func number
	static inline uint16_t Alt(std::string str)
	{
		return atoi(str.c_str());
	}

	///Convert string to integer
	static inline int32_t Atoi(std::string str)
	{
		return atoi(str.c_str());
	}
};
