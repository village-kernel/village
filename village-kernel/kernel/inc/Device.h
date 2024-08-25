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
	List<InputDevice*>    inDevs;
	List<NetworkDevice*>  ntDevs;
	List<MiscDevice*>     miscDevs;
	List<PlatDevice*>     platDevs;
	List<PlatDriver*>     platDrvs;

	/// @brief Methods
	PlatDriver* PlatformMatch(PlatDevice* device);
	void PlatformProbe();
	void PlatformRemove();
	void DevicesRelease();
	void InputDevSetup();
	void InputDevExit();
public:
	/// @brief Methods
	ConcreteDevice();
	~ConcreteDevice();
	void Setup();
	void Exit();

	/// @brief Block device methods
	void RegisterBlockDevice(BlockDevice* device);
	void UnregisterBlockDevice(BlockDevice* device);

	/// @brief Char device methods
	void RegisterCharDevice(CharDevice* device);
	void UnregisterCharDevice(CharDevice* device);

	/// @brief Framebuffer device methods
	void RegisterFBDevice(FBDevice* device);
	void UnregisterFBDevice(FBDevice* device);

	/// @brief Input device methods
	void RegisterInputDevice(InputDevice* device);
	void UnregisterInputDevice(InputDevice* device);

	/// @brief Netwrok device methods
	void RegisterNetworkDevice(NetworkDevice* device);
	void UnregisterNetworkDevice(NetworkDevice* device);

	/// @brief Misc device methods
	void RegisterMiscDevice(MiscDevice* device);
	void UnregisterMiscDevice(MiscDevice* device);

	/// @brief Platform device methods
	void RegisterPlatDevice(PlatDevice* device);
	void UnregisterPlatDevice(PlatDevice* device);

	/// @brief Platform driver methods
	void RegisterPlatDriver(PlatDriver* driver);
	void UnregisterPlatDriver(PlatDriver* driver);

	/// @brief Data methods
	Fopts* GetDeviceFopts(const char* name);
	List<Base*> GetDevices(DriverID id);
};

#endif // !__DEVICE_H__
