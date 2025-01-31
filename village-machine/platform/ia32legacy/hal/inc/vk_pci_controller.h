//###########################################################################
// vk_pci_controller.h
// Hardware Layer class that manages pci controller
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_PCI_CONTROLLER_H__
#define __VK_PCI_CONTROLLER_H__

#include "i386.h"


/// @brief PCIController
class PCIController
{
private:
    //Methods
    uint32_t ReadData(uint8_t bus, uint8_t dev, uint8_t func, uint8_t offset);
    uint16_t GetVendorID(uint8_t bus, uint8_t dev);
    uint16_t GetDeviceID(uint8_t bus, uint8_t dev);
    uint32_t GetBaseAddress(uint8_t bus, uint8_t dev, uint8_t BAR);
public:
    //Methods
    uint32_t ReadBAR(uint16_t vendorID, uint16_t deviceID, uint8_t BAR);
};

#endif //!__VK_PCI_CONTROLLER_H__
