//###########################################################################
// vk_exception.h
// Declarations of the functions that manage exception
//
// $Copyright: Copyright (C) village
//###########################################################################
#ifndef __VK_EXCEPTION_H__
#define __VK_EXCEPTION_H__

#include "vk_kernel.h"
#include "vk_class.h"


/// @brief Exception
class Exception : public Class
{
public:
    /// @brief Static constants
    static const uint32_t isr_num = 256;
    static const uint32_t rsvd_isr_size = 0;
private:
    /// @brief Structures
    struct IdtGate
    {
        uint16_t lowOffset;  /* Lower 16 bits of handler function address */
        uint16_t sel;        /* Kernel segment selector */
        uint8_t  rsvd;
        /* First byte
        * Bit 7: "Interrupt is present"
        * Bits 6-5: Privilege level of caller (0=kernel..3=user)
        * Bit 4: Set to 0 for interrupt gates
        * Bits 3-0: bits 1110 = decimal 14 = "32 bit interrupt gate" */
        uint8_t  flags; 
        uint16_t highOffset; /* Higher 16 bits of handler function address */

        IdtGate() :
            lowOffset(0),
            sel(0),
            rsvd(0),
            flags(0),
            highOffset(0)
        {}
    } __attribute__((packed));

    struct IdtRegister
    {
        uint16_t limit;
        uint32_t base;
        
        IdtRegister() :
            limit(0),
            base(0)
        {}
    } __attribute__((packed));

    /// @brief Static constants
    static const uint32_t kernel_code_segment = 8;
    static const uint32_t idt_entires = isr_num;

    /// @brief Members
    IdtGate idt[idt_entires];
    IdtRegister idtReg;
private:
    /// @brief Methods
    void SetIdt();
    void RemapPIC();
    uint16_t GetPicIrqReg(int ocw3);
    uint16_t GetPicIrr();
    uint16_t GetPicIsr();
private:
    /// @brief Methods
    void InstallHandlers();
    void UninstallHandlers();
    void DivisionByZeroHandler();
    void DebugHandler();
    void NonMaskableInterruptHandler();
    void BreakpointHandler();
    void IntoDetectedOverflowHandler();
    void OutOfBoundsHandler();
    void InvalidOpcodeHandler();
    void NoCoprocessorHandler();
    void DouleFaultHandler();
    void CoprocessorSegmentOverrunHandler();
    void BadTSSHandler();
    void SegmentNotPresentHandler();
    void StackFaultHandler();
    void GeneralProtectionFaultHandler();
    void PageFaultHandler();
    void UnknownInterruptHandler();
    void CoprocessorFaultHandler();
    void AlignmentCheckHandler();
    void MachineCheckHandler();
public:
    /// @brief Methods
    void Setup();
    void Exit();
    void Install(int irq, uint32_t handler);
};

#endif //!__VK_EXCEPTION_H__
