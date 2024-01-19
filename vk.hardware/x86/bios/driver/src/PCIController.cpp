//###########################################################################
// PCIController.cpp
// Definitions of the functions that manage PCI controller
//
// $Copyright: Copyright (C) village
//###########################################################################
#include "Hardware.h"


/// @brief PCIController
class PCIController
{
private:
	/// @brief Read data
	/// @param bus 
	/// @param dev 
	/// @param func 
	/// @param offset 
	/// @return 
	uint32_t ReadData(uint8_t bus, uint8_t dev, uint8_t func, uint8_t offset)
	{
		// Create configuration address
		uint32_t address =  ((uint32_t)bus << 16)     |
							((uint32_t)dev << 11)     |
							((uint32_t)func << 8)     |
							((uint32_t)offset & 0xFC) |
							((uint32_t)0x80000000);
		// Write out the address
		PortLongOut(0xCF8, address);
		// Read in the data
		return PortLongIn(0xCFC);
	}

	/// @brief Get vendor id
	/// @param bus 
	/// @param dev 
	/// @return 
	uint16_t GetVendorID(uint8_t bus, uint8_t dev)
	{
		uint32_t value = ReadData(bus, dev, 0, 0);
		return (uint16_t)(value & 0xFFFF);
	}


	/// @brief Get device id
	/// @param bus 
	/// @param dev 
	/// @return 
	uint16_t GetDeviceID(uint8_t bus, uint8_t dev)
	{
		uint32_t value = ReadData(bus, dev, 0, 2);
		return (uint16_t)((value >> 16) & 0xFFFF);
	}


	/// @brief Get base address
	/// @param bus 
	/// @param dev 
	/// @param BAR 
	/// @return 
	uint32_t GetBaseAddress(uint8_t bus, uint8_t dev, uint8_t BAR)
	{
		uint8_t offset = 0x4 << 2 << BAR;
		return (ReadData(bus, dev, 0, offset) & 0xFFFFFFF0);
	}
public:
	/// @brief ReadBAR
	/// @param vendorID 
	/// @param deviceID 
	/// @param BAR 
	/// @return 
	uint32_t ReadBAR(uint16_t vendorID, uint16_t deviceID, uint8_t BAR)
	{
		for (uint16_t bus = 0; bus < 256; bus++)
		{
			for (uint8_t dev = 0; dev < 32; dev++)
			{
				if (vendorID == GetVendorID(bus, dev))
				{
					if (deviceID == GetDeviceID(bus, dev))
					{
						return GetBaseAddress(bus, dev, BAR);
					}
				}
			}
		}
		return 0;
	}
};
