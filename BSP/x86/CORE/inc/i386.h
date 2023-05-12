#ifndef __I386_H__
#define __I386_H__

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

/* PIC defines */
#define PIC1                                 0x20             /* IO base address for master PIC */
#define PIC2                                 0xA0             /* IO base address for slave PIC */
#define PIC1_CMD                             PIC1
#define PIC1_DATA                            (PIC1 + 1)
#define PIC2_CMD                             PIC2
#define PIC2_DATA                            (PIC2 + 1)
#define PIC_EOI                              0x20

#define PIC_READ_IRR                         0x0a            /* OCW3 irq ready next CMD read */
#define PIC_READ_ISR                         0x0b            /* OCW3 irq service next CMD read */

#define ICW1_ICW4                            0x01            /* Indicates that ICW4 will be present */
#define ICW1_SINGLE                          0x02            /* Single (cascade) mode */
#define ICW1_INTERVAL4                       0x04            /* Call address interval 4 (8) */
#define ICW1_LEVEL                           0x08            /* Level triggered (edge) mode */
#define ICW1_INIT                            0x10            /* Initialization - required! */
 
#define ICW4_8086                            0x01            /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO                            0x02            /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE                       0x08            /* Buffered mode/slave */
#define ICW4_BUF_MASTER                      0x0C            /* Buffered mode/master */
#define ICW4_SFNM                            0x10            /* Special fully nested (not) */

/* Timer defines */
#define TIMER                                0x40
#define TIMER_CH0                            (TIMER + 0)
#define TIMER_CH1                            (TIMER + 1)
#define TIMER_CH2                            (TIMER + 2)
#define TIMER_CMD                            (TIMER + 3)

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
#define low_8(address)   (uint8_t) ( (address) & 0xFF)
#define high_8(address)  (uint8_t) (((address) >> 8) & 0xFF)

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
