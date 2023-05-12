#ifndef __I386_H__
#define __I386_H__

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

/* IRQ numbers */
#define IRQ_Division_By_Zero                 0
#define IRQ_Debug                            1
#define IRQ_Non_Maskable_Interrupt           2
#define IRQ_Breakpoint                       3
#define IRQ_Into_Detected_Overflow           4
#define IRQ_Out_Of_Bounds                    5
#define IRQ_Invalid_Opcode                   6
#define IRQ_No_Coprocessor                   7
#define IRQ_Doule_Fault                      8
#define IRQ_Coprocessor_Segment_Overrun      9
#define IRQ_Bad_TSS                          10
#define IRQ_Segment_Not_Present              11
#define IRQ_Stack_Fault                      12
#define IRQ_General_Protection_Fault         13
#define IRQ_Page_Fault                       14
#define IRQ_Unknown_Interrupt                15
#define IRQ_Coprocessor_Fault                16
#define IRQ_Alignment_Check                  17
#define IRQ_Machine_Check                    18
#define IRQ_31                               31

#define IRQ_Systick                          32
#define IRQ_Keyboard_Controller              33
#define IRQ_Serial_Port_COM2                 35
#define IRQ_Serial_Port_COM1                 36
#define IRQ_Line_Print_Terminal2             37
#define IRQ_Floppy_Controller                38
#define IRQ_Line_Print_Terminal1             39
#define IRQ_RTC_Timer                        40
#define IRQ_X86_Assembly_ACPI                41
#define IRQ_Mouse_Controller                 44
#define IRQ_Math_Coprocessor                 45
#define IRQ_ATA_Channel1                     46
#define IRQ_ATA_Channel2                     47

/* i386 utils */
#define low_16(address)  (uint16_t)( (address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

/* i386 low level function */
uint8_t PortByteIn(uint16_t port);
void PortByteOut(uint16_t port, uint8_t data);
uint16_t PortWordIn(uint16_t port);
void PortWordOut(uint16_t port, uint16_t data);

#ifdef __cplusplus
}
#endif

#endif //!__I386_H__
