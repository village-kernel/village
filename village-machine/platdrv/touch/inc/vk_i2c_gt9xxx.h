//###########################################################################
// vk_i2c_gt9xxx.h
// Declarations of the functions that manage gt9xxx touch ic
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_I2C_GT9XXX_H__
#define __VK_I2C_GT9XXX_H__

#include "vk_hardware.h"
#include "vk_driver.h"
#include "vk_kernel.h"
#include "vk_drv_gpio.h"
#include "vk_drv_i2c.h"
#include "vk_drv_exti.h"


/// @brief GT9xxx
class GT9xxx : public InputDriver, public Class
{
public:
    //Structures
    struct Config
    {
        I2c::Config  i2cCfg;
        Gpio::Config rstGpio;
        Gpio::Config intGpio;
        uint16_t     intirq;
        const char*  gt9xxxid;
    };
private:
    //Status
    union Status
    {
        struct
        {
            uint8_t tpx : 4;
            uint8_t haveKey : 1;
            uint8_t reserved : 1;
            uint8_t largeDetect : 1;
            uint8_t buffer : 1;
        };
        uint8_t value;
    };

    struct TouchPoint
    {
        uint8_t  trackid;
        uint16_t x;
        uint16_t y;
        uint16_t size;
        uint8_t  reserved;
    } __attribute__((packed));
private:
    //Static constant members
    static const uint16_t sizeoftp = sizeof(TouchPoint);
    static const uint8_t  gt_wr_cmd = 0x28;
    static const uint8_t  gt_rd_cmd = 0x29;
    static const uint16_t gt_ctl_reg = 0x8040;
    static const uint16_t gt_pid_reg = 0x8140;
    static const uint16_t gt_status_reg = 0x814e;
    static const uint16_t gt_tp1_reg = 0x814f;

    //Members
    Config  config;
    I2c     i2c;
    Exti    exti;
    Gpio    rstGpio;
    Gpio    intGpio;

    //Work
    WorkQueue::Work* work;

    //Methods
    void PinConfig();
    bool GetAck();
    bool WriteReg(uint16_t reg, uint8_t* data, uint8_t size);
    bool ReadReg(uint16_t reg, uint8_t* data, uint8_t size);
    void ResetIC();
    bool CheckID();
    void ExtiConfig();
    void ExtiInputFunc();
    void ScanWorkFunc();
public:
    /// @brief Methods
    GT9xxx();
    ~GT9xxx();

    /// @brief Plat Methods
    void SetData(void* data);

    /// @brief Fopts Methods
    bool Open();
    void Close();
};


/// @brief Gt9xxxDrv
class Gt9xxxDrv : public PlatDriver
{
public:
    /// @brief Plat Methods
    bool Probe(PlatDevice* device);
    bool Remove(PlatDevice* device);
};

#endif //!__VK_I2C_GT9XXX_H__
