//###########################################################################
// Device.cpp
// Definitions of the functions that manage driver
//
// $Copyright: Copyright (C) jingwei
//###########################################################################
#include "Device.h"

///Initialize module core
Device::DriverNode* Device::list = NULL;


///Constructor
Device::Device()
{
}


///Register driver object
void Device::RegisterDriver(Driver* driver, uint32_t id)
{
	DriverNode** nextNode = &list;

	if (driver) driver->SetID(id); else return;

	while (NULL != *nextNode)
	{
		uint32_t curDriverID = (*nextNode)->driver->GetID();
		uint32_t newDriverID = driver->GetID();

		if (newDriverID < curDriverID)
		{
			DriverNode* curNode = *nextNode;
			*nextNode = new DriverNode(driver);
			(*nextNode)->next = curNode;
			return;
		}

		nextNode = &(*nextNode)->next;
	}

	*nextNode = new DriverNode(driver);
}


///Deregister driver object
void Device::DeregisterDriver(Driver* driver, uint32_t id)
{
	DriverNode** prevNode = &list;
	DriverNode** currNode = &list;

	while (NULL != *currNode)
	{
		if (driver == (*currNode)->driver)
		{
			delete *currNode;

			if (*prevNode == *currNode)
				*prevNode = (*currNode)->next;
			else
				(*prevNode)->next = (*currNode)->next;

			break;
		}
		else
		{
			prevNode = currNode;
			currNode = &(*currNode)->next;
		}
	}
}


///Get the driver object
void Device::GetDriver(Driver* driver, uint32_t id)
{
	DriverNode** nextNode = &list;

	while (NULL != *nextNode)
	{
		uint32_t curDriverID = (*nextNode)->driver->GetID();
		uint32_t getDriverID = id;

		if (getDriverID == curDriverID)
		{
			driver = (*nextNode)->driver;
			return;
		}

		nextNode = &(*nextNode)->next;
	}
}
