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
	bool isRuntime;
	List<BlockDriver*>    blockDevs;
	List<CharDriver*>     charDevs;
	List<FBDriver*>       fbDevs;
	List<InputDriver*>    inDevs;
	List<NetworkDriver*>  ntDevs;
	List<MiscDriver*>     miscDevs;
	List<PlatDevice*>     platDevs;
	List<PlatDriver*>     platDrvs;

	/// @brief Methods
	bool PlatformMatch(PlatDevice* device, PlatDriver* driver);
	bool PlatformProbe(PlatDevice* device, PlatDriver* driver);
	bool PlatformRemove(PlatDevice* device, PlatDriver* driver);
	void PlatformDeviceProbe(PlatDriver* driver);
	void PlatformDeviceRemove(PlatDriver* driver);
	void PlatformDriverProbe(PlatDevice* device);
	void PlatformDriverRemove(PlatDevice* device);
	void PlatformProbe();
	void PlatformRemove();
	void DevicesRelease();
public:
	/// @brief Methods
	ConcreteDevice();
	~ConcreteDevice();
	void Setup();
	void Exit();

	/// @brief Block device methods
	void RegisterBlockDevice(BlockDriver* driver);
	void UnregisterBlockDevice(BlockDriver* driver);

	/// @brief Char device methods
	void RegisterCharDevice(CharDriver* driver);
	void UnregisterCharDevice(CharDriver* driver);

	/// @brief Framebuffer device methods
	void RegisterFBDevice(FBDriver* driver);
	void UnregisterFBDevice(FBDriver* driver);

	/// @brief Input device methods
	void RegisterInputDevice(InputDriver* driver);
	void UnregisterInputDevice(InputDriver* driver);

	/// @brief Netwrok device methods
	void RegisterNetworkDevice(NetworkDriver* driver);
	void UnregisterNetworkDevice(NetworkDriver* driver);

	/// @brief Misc device methods
	void RegisterMiscDevice(MiscDriver* driver);
	void UnregisterMiscDevice(MiscDriver* driver);

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
