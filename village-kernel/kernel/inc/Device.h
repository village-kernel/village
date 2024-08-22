//###########################################################################
// Device.h
// Declarations of the functions that manage device
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "Kernel.h"
#include "Driver.h"
#include "List.h"


/// @brief ConcreteDevice
class ConcreteDevice : public Device
{
private:
	/// @brief Members
	List<BlockDevice*>    blockDevs;
	List<CharDevice*>     charDevs;
	List<FBDevice*>       fbDevs;
	List<NetworkDevice*>  ntDevs;
	List<MiscDevice*>     miscDevs;
	List<PlatDevice*>     platDevs;
	List<PlatDriver*>     platDrvs;
public:
	/// @brief Methods
	ConcreteDevice();
	~ConcreteDevice();
	void Setup();
	void Exit();

	/// @brief Block device methods
	void RegisterBlockDevice(BlockDevice* device);
	void DeregisterBlockDevice(BlockDevice* device);

	/// @brief Char device methods
	void RegisterCharDevice(CharDevice* device);
	void DeregisterCharDevice(CharDevice* device);

	/// @brief Framebuffer device methods
	void RegisterFBDevice(FBDevice* device);
	void DeregisterFBDevice(FBDevice* device);

	/// @brief Netwrok device methods
	void RegisterNetworkDevice(NetworkDevice* device);
	void DeregisterNetworkDevice(NetworkDevice* device);

	/// @brief Misc device methods
	void RegisterMiscDevice(MiscDevice* device);
	void DeregisterMiscDevice(MiscDevice* device);

	/// @brief Platform device methods
	void RegisterPlatDevice(PlatDevice* device);
	void DeregisterPlatDevice(PlatDevice* device);

	/// @brief Platform driver methods
	void RegisterPlatDriver(PlatDriver* driver);
	void DeregisterPlatDriver(PlatDriver* driver);

	/// @brief Data methods
	Fopts* GetDeviceFopts(const char* name);
	List<Base*> GetDevices(DriverID id);
};

#endif // !__DEVICE_H__
