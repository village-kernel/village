//###########################################################################
// vk_bochs_vbe.h
// Declarations of the functions that manage bochs vbe
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_BOCHS_VBE_H__
#define __VK_BOCHS_VBE_H__

#include "vk_hardware.h"
#include "vk_driver.h"
#include "vk_pci_controller.h"


/// @brief BochsVBE
class BochsVBE : public FBDriver
{
public:
    //Config
    struct Config
    {
        volatile uint16_t* vmap;
    };
private:
    //Members
    Config config;
    PCIController pci;

    /// @brief Methods
    void WriteData(uint32_t reg, uint16_t value);
    uint16_t ReadData(uint32_t reg);
    void WriteReg(uint16_t reg, uint16_t value);
    uint16_t ReadReg(uint16_t reg);
    bool IsBochsVBEAvailable();
    void SetVideoMode(uint16_t width, uint16_t height, uint16_t bitdepth, bool isUseLinearFrameBuffer, bool isClearVideoMemory);
    void SetBank(uint16_t bankNumber);
public:
    /// @brief Methods
    BochsVBE();
    ~BochsVBE();

    /// @brief Plat Methods
    void SetData(void* data);

    /// @brief FB Methods
    bool Setup();
    void DrawPoint(uint32_t x, uint32_t y, uint32_t color);
    uint32_t ReadPoint(uint32_t x, uint32_t y);
    void Fill(uint32_t sx, uint32_t sy, uint32_t ex, uint32_t ey, uint32_t color);
    void Fill(uint32_t sx, uint32_t sy, uint32_t ex, uint32_t ey, uint8_t* pxmap);
    void Clear(uint32_t color = 0);
    void Exit();

    /// @brief Fopts Methods
    bool Open();
    int IOCtrl(uint8_t cmd, void* data);
    void Close();
};


/// @brief BochsVBEDrv
class BochsVBEDrv : public PlatDriver
{
public:
    /// @brief Plat Methods
    bool Probe(PlatDevice* device);
    bool Remove(PlatDevice* device);
};

#endif //!__VK_BOCHS_VBE_H__
